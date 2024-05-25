#include "game.h"
#include "readerandwriter.h"
#include <typeinfo>

Game::Game() {
    status_session = false;
    status_word = false;
    QStringList words = (ReaderAndWriter::ReadRecord("Words.txt")).split("\r\n");
    cur_word = "";
    int cnt_test = 5;
    int cur_cnt_test = 5;
    SetDefault_();
}

void Game::SetDefault_(){
    this->words = (ReaderAndWriter::ReadRecord("Words.txt")).split("\r\n");
    this->cur_cnt_test = 5;
    this->cnt_test = 5;
}

void Game::NewGame(){
    if(status_session){
        EndGame();
    }
    this->status_session = true;
    int id = QRandomGenerator::global()->bounded(0, words.count()-1);
    cur_word = this->words[id];
    cur_cnt_test = cnt_test;
}

void Game::EndGame(){
    if(status_word){
        ReaderAndWriter::WriteRecord(QString::number(cur_cnt_test+1));
    }
    this->status_session = false;
    this->status_word = false;
    cur_word = "";
}

std::vector<QString> Game::UseAttempt(QString *atm) {
    this->cur_cnt_test--;
    QString template_word_1 = "";
    QString template_word_2 = "";
    std::string str_1 = atm->toLocal8Bit().constData();
    std::string str_2 = cur_word.toLocal8Bit().constData();

    if(std::equal(str_1.begin(), str_1.end(), str_2.begin())){
        int bal = this->cur_cnt_test;
        status_word = true;
        this->EndGame();
        return {"Вы отгадили слово и получили баллы в количестве: " + QString::number(bal + 1), *atm};
    }

    std::vector<bool> equl_1 = {false, false, false, false};
    std::vector<bool> equl_2 = {false, false, false, false};
    for (int i = 0; i < 4; i++) {
        if((int)str_1[i] == (int)str_2[i]){
            equl_1[i] = true;
        }
        for(int j = 0; j < 4; j++){
            if((int)str_1[i] == (int)str_2[j] && i != j){
                equl_2[i] = true;
            }
        }
    }

    for(int i = 0; i < 4; i++){
        if(!equl_1[i]){
            template_word_1 = this->MadeTemplate(equl_1, cur_word);
            template_word_2 = this->MadeTemplate(equl_2, *atm);
            if(cur_cnt_test <= 0){
                this->EndGame();
            }
            return {template_word_1, template_word_2};
        }
    }
}

QString Game::MadeTemplate(std::vector<bool> eq, QString word){
    QString w = "";
    for(int i = 0; i < 4; i++){
        if(eq[i]){
            w += word[i];
        }
        else{
            w += "*";
        }
    }
    return w;
}

bool Game::GetStatus(){
    return this->status_session;
}



