#include "question.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Question w;




    /*
    w.setAnswerTypeA("thinking");
    w.setAnswerTypeA("feeling");
    w.setQuestion("Quelle est la plus grande faute");
    w.setAnswerA("Avoir trop de compassion");
    w.setAnswerB("Manquer de compassion");
    */
    w.show();

    return a.exec();
}
