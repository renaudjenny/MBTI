#include "typedescriptions.h"
#include "typedescription.h"
#include <QtXml>

TypeDescriptions::TypeDescriptions(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(1000, 700);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

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

    QDomNodeList *descriptions = new QDomNodeList(xml.elementsByTagName("description"));
    for (int i = 0; i < descriptions->size(); i++) {
        QString type = descriptions->at(i).attributes().namedItem("id").nodeValue().toUpper();
        TypeDescription *typeDescription = new TypeDescription(type);
        mainLayout->addWidget(typeDescription, i / 4, i % 4);
    }
}
