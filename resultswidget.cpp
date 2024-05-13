#include "resultswidget.h"

void ResultsWidget::initialize()
{
    main_layout = new QVBoxLayout();
    groupbox_layout = new QVBoxLayout();
    result_box = new QGroupBox();

    rl_sld = new ResultLine();
    rl_sld_im = new ResultLine();
    rl_pot_v = new ResultLine();
    rl_pot_v_im = new ResultLine();

    rl_ch_wl = new ResultLine();
    rl_cr_ang = new ResultLine();
    rl_cr_mom = new ResultLine();
    rl_atl_c = new ResultLine();
    rl_absorb = new ResultLine();
    rl_scatt = new ResultLine();

}

void ResultsWidget::set_resultlines()
{
    rl_sld->setText("Re(SLD)", "1/Å²");
    rl_sld->setTip("Real part of Scattering Length Density");

    rl_sld_im->setText("Im(SLD)", "1/Å²");
    rl_sld_im->setTip("Imaginary part of Scattering Length Density");

    rl_pot_v->setText("Re(V)", "neV");
    rl_pot_v->setTip("Real part of Potential");

    rl_pot_v_im->setText("Im(V)", "neV");
    rl_pot_v_im->setTip("Imaginary part of Potential");

    rl_ch_wl->setText("λ<sub>c</sub>", "Å");
    rl_ch_wl->setTip("Characteristic wavelength transfer");

    rl_cr_ang->setText("θ<sub>c</sub>", "mrad/Å");
    rl_cr_ang->setTip("Critical angle");

    rl_cr_mom->setText("q<sub>c</sub>", "1/Å");
    rl_cr_mom->setTip("Critical momentum");


    rl_absorb->setText("μ<sub>α</sub>", "1/cm");
    rl_absorb->setTip("True absorption coefficient");

    rl_scatt->setText("μ<sub>inc</sub>", "1/cm");
    rl_scatt->setTip("Incoherent scattering attenuation");

    rl_atl_c->setText("μ", "1/cm");
    rl_atl_c->setTip("Attenuation coefficient");

}

void ResultsWidget::construct()
{
    this->setLayout(main_layout);
    QFont font_resultbox;
    font_resultbox.setBold(true);
    result_box->setTitle("Results");
    result_box->setFlat(false);
    result_box->setStyleSheet("QGroupBox { font-weight: bold; font-size: 18px} ");
    result_box->setAlignment(Qt::AlignCenter);
    result_box->setFont(font_resultbox);

    main_layout->addStretch(10);

    main_layout->addWidget(result_box);
    result_box->setLayout(groupbox_layout);

    groupbox_layout->addWidget(rl_sld);
    groupbox_layout->addWidget(rl_sld_im);
    groupbox_layout->addWidget(rl_pot_v);
    groupbox_layout->addWidget(rl_pot_v_im);
    groupbox_layout->addWidget(rl_ch_wl);
    groupbox_layout->addWidget(rl_cr_ang);

    groupbox_layout->addWidget(rl_cr_mom);
    groupbox_layout->addWidget(rl_absorb);
    groupbox_layout->addWidget(rl_scatt);
    groupbox_layout->addWidget(rl_atl_c);
}

ResultsWidget::ResultsWidget(QWidget *parent)
    : QWidget{parent}
{
    initialize();
    set_resultlines();
    construct();

}

void ResultsWidget::clear()
{
    rl_sld->setResult("---");
    rl_sld_im->setResult("---");

    rl_pot_v->setResult("---");
    rl_pot_v_im->setResult("---");

    rl_ch_wl->setResult("---");
    rl_cr_ang->setResult("---");

    rl_cr_mom->setResult("---");
    rl_absorb->setResult("---");

    rl_scatt->setResult("---");
    rl_atl_c->setResult("---");
}
