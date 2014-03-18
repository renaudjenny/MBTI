#ifndef TYPEDESCRIPTION_H
#define TYPEDESCRIPTION_H

#include <QDialog>
#include <QtWidgets>

class TypeDescription : public QWidget
{
    Q_OBJECT
public:
    explicit TypeDescription(QString type, QWidget *parent = 0);

private:
    QString type;

signals:

public slots:
    void openWikipedia();
};

#endif // TYPEDESCRIPTION_H
