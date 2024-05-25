#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QStringList>
#include <QRandomGenerator>
#include <QArrayData>

class Game
{
public:
    Game();
    void NewGame();
    void EndGame();
    std::vector<QString> UseAttempt(QString *atm);
    bool GetStatus();
    int cur_cnt_test;

private:
    bool status_session;
    bool status_word;
    QStringList words;
    QString cur_word;
    int cnt_test;

    void SetDefault_();
    void ReadWords();
    QString MadeTemplate(std::vector<bool> eq, QString word);

};

#endif // GAME_H
