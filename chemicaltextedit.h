#ifndef CHEMICALTEXTEDIT_H
#define CHEMICALTEXTEDIT_H

#include <QTextEdit>

class ChemicalTextEdit : public QTextEdit
{

    Q_OBJECT


    void connectSlotsSignals();
    void disconnectSlotsSignals();

    QString plainToHtml(QString);

public:
    ChemicalTextEdit();
    bool checkBrackets();
private slots:
    void changeText();
signals:
    void changeFormula(QString line);

};

#endif // CHEMICALTEXTEDIT_H
