#include "typedescription.h"
#include <QtXml>

TypeDescription::TypeDescription(QString type, QWidget *parent) :
    QWidget(parent), type(type)
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

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(5);
    setLayout(mainLayout);

    //we can't use directly QDomNode description = new QDomNode(xml.elementById(type.toLower())) because elementById return always null
    //Because that don't work currently :
    //"Since the QDomClasses do not know which attributes are element IDs, this function returns always a null element.
    //This may change in a future version."
    QDomNodeList *descriptions = new QDomNodeList(xml.elementsByTagName("description"));
    QDomNode description;
    for (int i = 0; i < descriptions->size(); i++) {
        QDomNode candidate = descriptions->at(i);
        if (candidate.attributes().namedItem("id").nodeValue() == type.toLower()) {
            description = candidate;
            break;
        }
    }
    if (description.isNull()) {
        QLabel *errorText = new QLabel(tr("Il n'y a pas de description disponible pour le type : <strong>%1</strong>").arg(type));
        mainLayout->addWidget(errorText);
        return;
    }

    QPushButton *typeButton = new QPushButton(type);
    mainLayout->addWidget(typeButton);
    connect(typeButton, SIGNAL(clicked()), this, SLOT(openWikipedia()));

    QTextEdit *descriptionText = new QTextEdit;
    descriptionText->setReadOnly(true);
    descriptionText->setPlainText(description.firstChild().nodeValue());
    mainLayout->addWidget(descriptionText);
}

void TypeDescription::openWikipedia()
{
    QDesktopServices::openUrl(QUrl(tr("http://fr.wikipedia.org/wiki/") + type));
}
