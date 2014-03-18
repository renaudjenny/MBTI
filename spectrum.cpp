#include "spectrum.h"
#include "typedescription.h"
#include "typedescriptions.h"

Spectrum::Spectrum(QMap<QString, unsigned int> answerCount, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QLabel *title = new QLabel(tr("Spectre"));
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    QHBoxLayout *extraversionIntroversionLayout = new QHBoxLayout;
    mainLayout->addLayout(extraversionIntroversionLayout);

    QLabel *extraversion = new QLabel(tr("Extraversion"));
    extraversion->setMinimumWidth(100);
    extraversion->setAlignment(Qt::AlignRight);
    extraversionIntroversionLayout->addWidget(extraversion);
    QProgressBar *extraversionProgressBar = new QProgressBar;
    extraversionProgressBar->setInvertedAppearance(true);
    extraversionProgressBar->setMaximum(10);
    extraversionIntroversionLayout->addWidget(extraversionProgressBar);
    QProgressBar *introversionProgressBar = new QProgressBar;
    introversionProgressBar->setMaximum(10);
    extraversionIntroversionLayout->addWidget(introversionProgressBar);
    QLabel *introversion = new QLabel(tr("Introversion"));
    introversion->setMinimumWidth(100);
    extraversionIntroversionLayout->addWidget(introversion);

    QHBoxLayout *sensingIntuitionLayout = new QHBoxLayout;
    mainLayout->addLayout(sensingIntuitionLayout);

    QLabel *sensing = new QLabel(tr("Sensation"));
    sensing->setMinimumWidth(100);
    sensing->setAlignment(Qt::AlignRight);
    sensingIntuitionLayout->addWidget(sensing);
    QProgressBar *sensingProgressBar = new QProgressBar;
    sensingProgressBar->setInvertedAppearance(true);
    sensingProgressBar->setMaximum(20);
    sensingIntuitionLayout->addWidget(sensingProgressBar);
    QProgressBar *intuitionProgressBar = new QProgressBar;
    intuitionProgressBar->setMaximum(20);
    sensingIntuitionLayout->addWidget(intuitionProgressBar);
    QLabel *intuition = new QLabel(tr("Intuition"));
    intuition->setMinimumWidth(100);
    sensingIntuitionLayout->addWidget(intuition);

    QHBoxLayout *thinkingFeelingLayout = new QHBoxLayout;
    mainLayout->addLayout(thinkingFeelingLayout);

    QLabel *thinking = new QLabel(tr("Pensée"));
    thinking->setAlignment(Qt::AlignRight);
    thinking->setMinimumWidth(100);
    thinkingFeelingLayout->addWidget(thinking);
    QProgressBar *thinkingProgressBar = new QProgressBar;
    thinkingProgressBar->setInvertedAppearance(true);
    thinkingProgressBar->setMaximum(20);
    thinkingFeelingLayout->addWidget(thinkingProgressBar);
    QProgressBar *feelingProgressBar = new QProgressBar;
    feelingProgressBar->setMaximum(20);
    thinkingFeelingLayout->addWidget(feelingProgressBar);
    QLabel *feeling = new QLabel(tr("Sentiment"));
    feeling->setMinimumWidth(100);
    thinkingFeelingLayout->addWidget(feeling);

    QHBoxLayout *judgingPerceptionLayout = new QHBoxLayout;
    mainLayout->addLayout(judgingPerceptionLayout);

    QLabel *judging = new QLabel(tr("Jugement"));
    judging->setAlignment(Qt::AlignRight);
    judging->setMinimumWidth(100);
    judgingPerceptionLayout->addWidget(judging);
    QProgressBar *judgingProgressBar = new QProgressBar;
    judgingProgressBar->setInvertedAppearance(true);
    judgingProgressBar->setMaximum(20);
    judgingPerceptionLayout->addWidget(judgingProgressBar);
    QProgressBar *perceptionProgressBar = new QProgressBar;
    perceptionProgressBar->setMaximum(20);
    judgingPerceptionLayout->addWidget(perceptionProgressBar);
    QLabel *perception = new QLabel(tr("Perception"));
    perception->setMinimumWidth(100);
    judgingPerceptionLayout->addWidget(perception);

    QLabel *result = new QLabel(tr("Resultat"));
    result->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(result);

    QHBoxLayout *resultLayout = new QHBoxLayout;
    mainLayout->addLayout(resultLayout);

    //search result, if there is equal result, we have to
    //set several button.

    QList<QString> firstLetters;
    if (answerCount["extraversion"] < answerCount["introversion"]) {
        firstLetters.append("I");
    } else if (answerCount["extraversion"] > answerCount["introversion"]) {
        firstLetters.append("E");
    } else {
        firstLetters.append("I");
        firstLetters.append("E");
    }

    QList<QString> secondLetters;
    if (answerCount["sensing"] < answerCount["intuition"]) {
        secondLetters.append("N");
    } else if (answerCount["sensing"] > answerCount["intuition"]) {
        secondLetters.append("S");
    } else {
        secondLetters.append("N");
        secondLetters.append("S");
    }

    QList<QString> thirdLetters;
    if (answerCount["thinking"] < answerCount["feeling"]) {
        thirdLetters.append("F");
    } else if (answerCount["thinking"] > answerCount["feeling"]) {
        thirdLetters.append("T");
    } else {
        thirdLetters.append("F");
        thirdLetters.append("T");
    }

    QList<QString> fourthLetters;
    if (answerCount["judging"] < answerCount["perception"]) {
        fourthLetters.append("P");
    } else if (answerCount["judging"] > answerCount["perception"]) {
        fourthLetters.append("J");
    } else {
        fourthLetters.append("P");
        fourthLetters.append("J");
    }

    signalMapper = new QSignalMapper(this);

    //release the cartesian product of letters, and create a button
    //for each case
    for (int i = 0; i < firstLetters.size(); i++) {
        for (int j = 0; j < secondLetters.size(); j++) {
            for (int k = 0; k < thirdLetters.size(); k++) {
                for (int l = 0; l < fourthLetters.size(); l++) {
                    QString type = firstLetters[i] + secondLetters[j] + thirdLetters[k] + fourthLetters[l];
                    QPushButton *resultButton = new QPushButton(type);
                    resultLayout->addWidget(resultButton);
                    connect(resultButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
                    signalMapper->setMapping(resultButton, type);
                }
            }
        }
    }
    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(openTypeDescription(QString)));

    extraversionProgressBar->setValue(answerCount["extraversion"]);
    introversionProgressBar->setValue(answerCount["introversion"]);
    sensingProgressBar->setValue(answerCount["sensing"]);
    intuitionProgressBar->setValue(answerCount["intuition"]);
    thinkingProgressBar->setValue(answerCount["thinking"]);
    feelingProgressBar->setValue(answerCount["feeling"]);
    judgingProgressBar->setValue(answerCount["judging"]);
    perceptionProgressBar->setValue(answerCount["perception"]);

    QPushButton *openTypeDescriptionsButton = new QPushButton(tr("Tableau des types"));
    mainLayout->addWidget(openTypeDescriptionsButton);
    connect(openTypeDescriptionsButton, SIGNAL(clicked()), this, SLOT(openTypeDescriptions()));
}

void Spectrum::openTypeDescription(const QString &type)
{
    TypeDescription *typeDescription = new TypeDescription(type);
    typeDescription->show();
}

void Spectrum::openTypeDescriptions()
{
    TypeDescriptions *typeDescriptions = new TypeDescriptions();
    typeDescriptions->show();
}
