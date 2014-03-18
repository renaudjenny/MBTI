#include "question.h"
#include "spectrum.h"
#include "typedescriptions.h"

Question::Question(QWidget *parent) :
    QWidget(parent)
{
    QFile xmlFile(":/MBTI.xml");
    if (!xmlFile.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Impossible d'ouvrir le fichier XML"), tr("Impossible d'ouvrir le fichier XML MBTI.xml"));
        return;
    }

    QDomDocument xml;
    if (!xml.setContent(&xmlFile)) {
        xmlFile.close();
        QMessageBox::critical(this, tr("Fichier XML invalide"), tr("Le fichier MBTI.xml n'est pas un fichier XML valide"));
        return;
    }
    xmlFile.close();

    setMinimumWidth(600);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QHBoxLayout *questionLayout = new QHBoxLayout;
    mainLayout->addLayout(questionLayout);
    questionLabel = new QLabel;
    questionLayout->addWidget(questionLabel);
    questionLayout->addStretch();

    previousQuestionButton = new QPushButton("<");
    questionLayout->addWidget(previousQuestionButton);
    previousQuestionButton->setEnabled(false);
    connect(previousQuestionButton, SIGNAL(clicked()), this, SLOT(previousQuestion()));
    questionNumberLabel = new QLabel;
    questionLayout->addWidget(questionNumberLabel);
    nextQuestionButton = new QPushButton(">");
    nextQuestionButton->setEnabled(false);
    questionLayout->addWidget(nextQuestionButton);
    connect(nextQuestionButton, SIGNAL(clicked()), this, SLOT(nextQuestion()));

    QHBoxLayout *answerALayout = new QHBoxLayout;
    mainLayout->addLayout(answerALayout);

    answerAButton = new QPushButton(tr("A"));
    answerAButton->setFixedWidth(40);
    answerALayout->addWidget(answerAButton);
    connect(answerAButton, SIGNAL(clicked()), this, SLOT(onAnswerA()));

    answerA = new QLabel;
    answerALayout->addWidget(answerA);

    QHBoxLayout *answerBLayout = new QHBoxLayout;
    mainLayout->addLayout(answerBLayout);

    answerBButton = new QPushButton(tr("B"));
    answerBButton->setFixedWidth(40);
    answerBLayout->addWidget(answerBButton);
    connect(answerBButton, SIGNAL(clicked()), this, SLOT(onAnswerB()));

    answerB = new QLabel;
    answerBLayout->addWidget(answerB);

    QPushButton *openTypeDescriptionsButton = new QPushButton(tr("Tableau des types"));
    mainLayout->addWidget(openTypeDescriptionsButton);
    connect(openTypeDescriptionsButton, SIGNAL(clicked()), this, SLOT(openTypeDescriptions()));

    questions = new QDomNodeList(xml.elementsByTagName("question"));
    questionNumber = 1;
    displayQuestion();
}

Question::~Question()
{
    delete questions;
}

void Question::displayQuestion()
{
    answerAButton->setEnabled(true);
    answerBButton->setEnabled(true);

    QDomNode question = questions->at(questionNumber - 1);

    questionLabel->setText(question.namedItem("questionText").firstChild().nodeValue());
    questionNumberLabel->setText(QString::number(questionNumber) + "/" + QString::number(questions->size()));
    answerA->setText(question.namedItem("answerA").firstChild().nodeValue());
    answerB->setText(question.namedItem("answerB").firstChild().nodeValue());

    //set button active when a choice is already done
    if (answers.contains(questionNumber)) {
        if (answers[questionNumber] == MBTI::answerA) {
            answerAButton->setEnabled(false);
        } else {
            answerBButton->setEnabled(false);
        }
    }
}

void Question::openSpectrum()
{
    QMap<QString, unsigned int> answerCount;

    answerCount["extraversion"] = 0;
    answerCount["introversion"] = 0;
    answerCount["sensing"] = 0;
    answerCount["intuition"] = 0;
    answerCount["thinking"] = 0;
    answerCount["feeling"] = 0;
    answerCount["judging"] = 0;
    answerCount["perception"] = 0;

    for (int i = 0; i < questions->size(); i++) {
        QDomNode question = questions->at(i);
        int number = question.attributes().namedItem("number").nodeValue().toInt();
        QString choice;
        if (answers[number] == MBTI::answerA) {
            answerCount[question.namedItem("answerTypeA").firstChild().nodeValue()]++;
        } else {
            answerCount[question.namedItem("answerTypeB").firstChild().nodeValue()]++;
        }
    }

    Spectrum *spectrum = new Spectrum(answerCount);
    spectrum->show();
}

void Question::onAnswerA()
{
    answers[questionNumber] = MBTI::answerA;
    nextQuestion();
}

void Question::onAnswerB()
{
    answers[questionNumber] = MBTI::answerB;
    nextQuestion();
}

void Question::openTypeDescriptions()
{
    TypeDescriptions *typeDescriptions = new TypeDescriptions;
    typeDescriptions->show();
}

void Question::previousQuestion()
{
    --questionNumber;
    previousQuestionButton->setEnabled(questionNumber != 1);
    displayQuestion();
    nextQuestionButton->setEnabled(true);
}

void Question::nextQuestion()
{
    ++questionNumber;
    if (questionNumber <= questions->size()) {
        displayQuestion();
        previousQuestionButton->setEnabled(true);
        nextQuestionButton->setEnabled(answers.contains(questionNumber));
    } else {
        openSpectrum();
    }
}

void Question::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A) {
        onAnswerA();
    } else if (event->key() == Qt::Key_B) {
        onAnswerB();
    }
}
