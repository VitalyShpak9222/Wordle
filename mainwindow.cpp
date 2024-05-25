#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Wordle");
    this->ui->textEdit_2->setReadOnly(true);

    connect(this->ui->button_MenuRecord, SIGNAL(clicked()), this, SLOT(Press_buttom_MenuRecord()));
    connect(this->ui->button_NewGame, SIGNAL(clicked()), this, SLOT(Press_buttom_NewGame()));
    connect(this->ui->button_Test, SIGNAL(clicked()), this, SLOT(Press_buttom_Test()));
}

void MainWindow::Press_buttom_Test(){
    if(this->game.GetStatus()){
        QString text = this->ui->textEdit->toPlainText();
        std::vector<QString> answer = game.UseAttempt(&text);
        this->ui->textEdit_2->append("{player}: " + this->ui->textEdit->toPlainText());
        if(answer[0].length() > 4){
            this->ui->textEdit_2->append("{game}: " + answer[0]);
        }
        else{
            this->ui->textEdit_2->append("{game}: буквы отгаданные на данный момент " + answer[0]);
            this->ui->textEdit_2->append("{game} эти буквы есть в слове на других местах " + answer[1]);
            if(this->game.cur_cnt_test <= 0){
                this->ui->textEdit_2->append("Вы прогирали");
            }
        }
    }
}

void MainWindow::Press_buttom_MenuRecord(){
    if(this->ui->button_Test->isVisible()){
        this->ui->button_Test->setVisible(false);
        this->ui->textEdit->setVisible(false);
        int x = this->ui->textEdit_2->x(), y = this->ui->textEdit_2->y(),
            h = this->ui->textEdit_2->height(), w = this->ui->textEdit_2->width();
        this->ui->textEdit_2->setGeometry(x,y-40,w,h+40);
        this->game.EndGame();
        this->ui->button_MenuRecord->setDown(true);
        this->ui->button_MainMenu->setDown(false);
        QString str = this->ProcessingRecords(ReaderAndWriter::ReadRecord("Record history.txt"));
        this->ui->textEdit_2->clear();
        this->ui->textEdit_2->append(str);
    }

}

void MainWindow::Press_buttom_NewGame(){
    if(!this->ui->button_Test->isVisible()){
        this->ui->button_Test->setVisible(true);
        this->ui->textEdit->setVisible(true);
        int x = this->ui->textEdit_2->x(), y = this->ui->textEdit_2->y(),
            h = this->ui->textEdit_2->height(), w = this->ui->textEdit_2->width();
        this->ui->textEdit_2->setGeometry(x,y+40,w,h-40);
    }
    this->ui->button_MainMenu->setDown(true);
    this->game.NewGame();
    this->ui->textEdit_2->clear();
    this->ui->textEdit_2->append("{game}: Вы начали новую игру\n{game}: Загаданное слово ****");
}

QString MainWindow::ProcessingRecords(QString str){
    QStringList list = str.split("\n");
    QList <int> records;
    for(int i = 1; i < list.size(); i++)
    {
        records.append(list.at(i).toInt());
    }
    QString result = "";
    std::sort(records.begin(), records.end());
    for (int i = 0; i < records.size(); ++i) {
        result +=  QString::number(i+1) + " место: " + QString::number(records[records.size() - i-1]) + "\n";
    }
    return result;
}


MainWindow::~MainWindow()
{
    delete ui;
}


