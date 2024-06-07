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
    rl_sld->set_text("Re(SLD)", "1/Å²");
    rl_sld->set_tip("Real part of Scattering Length Density");

    rl_sld_im->set_text("Im(SLD)", "1/Å²");
    rl_sld_im->set_tip("Imaginary part of Scattering Length Density");

    rl_pot_v->set_text("Re(V)", "neV");
    rl_pot_v->set_tip("Real part of Potential");

    rl_pot_v_im->set_text("Im(V)", "neV");
    rl_pot_v_im->set_tip("Imaginary part of Potential");

    rl_ch_wl->set_text("λ<sub>c</sub>", "Å");
    rl_ch_wl->set_tip("Characteristic wavelength transfer");

    rl_cr_ang->set_text("θ<sub>c</sub>", "mrad/Å");
    rl_cr_ang->set_tip("Critical angle");

    rl_cr_mom->set_text("q<sub>c</sub>", "1/Å");
    rl_cr_mom->set_tip("Critical momentum");


    rl_absorb->set_text("μ<sub>α</sub>", "1/cm");
    rl_absorb->set_tip("True absorption coefficient");

    rl_scatt->set_text("μ<sub>inc</sub>", "1/cm");
    rl_scatt->set_tip("Incoherent scattering attenuation");

    rl_atl_c->set_text("μ", "1/cm");
    rl_atl_c->set_tip("Attenuation coefficient");

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
    rl_sld->set_result("---");
    rl_sld_im->set_result("---");

    rl_pot_v->set_result("---");
    rl_pot_v_im->set_result("---");

    rl_ch_wl->set_result("---");
    rl_cr_ang->set_result("---");

    rl_cr_mom->set_result("---");
    rl_absorb->set_result("---");

    rl_scatt->set_result("---");
    rl_atl_c->set_result("---");
}
