#include "chemicaltextedit.h"
#include "qobjectdefs.h"
#include <QStack>
#include <QChar>


void ChemicalTextEdit::connectSlotsSignals()
{
    connect(this, SIGNAL(textChanged()), this, SLOT(changeText()));
}

void ChemicalTextEdit::disconnectSlotsSignals()
{
    disconnect(this, SIGNAL(textChanged()), this, SLOT(changeText()));
}

QString ChemicalTextEdit::plainToHtml(QString plaintext)
{
    QString htmltext;

    bool state_sup(false);
    bool state_sub(false);
    for(auto p = plaintext.cbegin(); p != plaintext.cend(); p++)
    {
        if((*p) == '^')
        {
            if(state_sub) htmltext.append("</sub>");
            state_sup = true;
            state_sub = false;
            htmltext.append(*p);
            htmltext.append("<sup>");
            continue;
        };
        if((*p).isLetter() || (*p) == ')' || (*p) == '(')
        {
            if(state_sup) htmltext.append("</sup>");
            if(state_sub) htmltext.append("</sub>");
            state_sup = false;
            state_sub = false;
            htmltext.append(*p);
            continue;
        }
        if((*p).isDigit() || (*p) == '.')
        {
            if(state_sub)
            {
                htmltext.append(*p);
                continue;
            }
            if((*(p-1)).isLetter() || (*(p-1)) == ')' || (*(p-1)) == '(')
            {
                htmltext.append("<sub>");
                htmltext.append(*p);
                state_sub = true;
                continue;
            }
        }
        htmltext.append(*p);
    }
    return htmltext;


}

ChemicalTextEdit::ChemicalTextEdit()
{

    connectSlotsSignals();
}

void ChemicalTextEdit::changeText()
{
    disconnectSlotsSignals();

    // qDebug() << this->textCursor().anchor();
    // auto curspos = this->textCursor().anchor();
    // auto cursorpos = this->textCursor();


    // this->setHtml(this->toPlainText());
    emit changeFormula(plainToHtml(this->toPlainText()));

    // cursorpos.setPosition(curspos);
    // setTextCursor(cursorpos);


    connectSlotsSignals();
}
