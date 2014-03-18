#ifndef QUESTION_H
#define QUESTION_H

#include <QWidget>
#include <QtWidgets>
#include <QtXml>

namespace MBTI {
enum answerType {
    answerA, answerB
};
}

class Question : public QWidget
{
    Q_OBJECT

public:
    explicit Question(QWidget *parent = 0);

    ~Question();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QMap<unsigned int, unsigned int> answers;
    QDomNodeList *questions;
    unsigned int questionNumber;

    QLabel *questionLabel;
    QLabel *questionNumberLabel;
    QLabel *answerA;
    QLabel *answerB;
    QPushButton *answerAButton;
    QPushButton *answerBButton;
    QPushButton *previousQuestionButton;
    QPushButton *nextQuestionButton;

    void displayQuestion();
    void openSpectrum();
private slots:
    void onAnswerA();
    void onAnswerB();
    void openTypeDescriptions();
    void previousQuestion();
    void nextQuestion();
};

#endif // QUESTION_H
