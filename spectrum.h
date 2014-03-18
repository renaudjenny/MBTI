#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <QtWidgets>

class Spectrum : public QWidget
{
    Q_OBJECT
public:
    explicit Spectrum(QMap<QString, unsigned int> answerCount, QWidget *parent = 0);

private:
    QSignalMapper *signalMapper;

signals:

public slots:
    void openTypeDescription(const QString &type);
    void openTypeDescriptions();
};

#endif // SPECTRUM_H
