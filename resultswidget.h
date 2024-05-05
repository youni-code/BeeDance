#ifndef RESULTSWIDGET_H
#define RESULTSWIDGET_H

#include <QWidget>
#include "resultline.h"
#include <QGroupBox>

class ResultsWidget : public QWidget
{
    Q_OBJECT


    QVBoxLayout *main_layout = nullptr;
    QGroupBox *result_box = nullptr;
    QVBoxLayout *groupbox_layout = nullptr;

    ResultLine *rl_sld = nullptr; ResultLine *rl_sld_im = nullptr;
    ResultLine *rl_pot_v = nullptr; ResultLine *rl_pot_v_im = nullptr;
    ResultLine *rl_ch_wl = nullptr; ResultLine *rl_cr_ang = nullptr;
    ResultLine *rl_cr_mom = nullptr; ResultLine *rl_atl_c = nullptr;
    ResultLine *rl_absorb = nullptr; ResultLine *rl_scatt = nullptr;


    void initialize();
    void set_resultlines();
    void construct();

public:
    explicit ResultsWidget(QWidget *parent = nullptr);

signals:
};

#endif // RESULTSWIDGET_H
