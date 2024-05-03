#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chemicaltextedit.h"
#include "chemicallabel.h"
#include "resultline.h"

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include "coresld.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    CoreSLD *core = nullptr;
    QWidget *central_widget = nullptr;

    QMenuBar    *main_menubar = nullptr;
    QAction     *exit_action = nullptr;
    QAction     *open_action = nullptr;
    QAction     *saveas_action = nullptr;
    QAction     *help_action = nullptr;

    QStatusBar *main_statusbar = nullptr;


    QVBoxLayout         *chemical_layout = nullptr;
    ChemicalTextEdit    *formula_TextEdit = nullptr;
    ChemicalLabel       *formula_Label = nullptr;

    QHBoxLayout *density_sublayout = nullptr;
    QLabel      *density_label = nullptr;
    QLineEdit   *density_LineEdit = nullptr;
    QComboBox   *density_ComboBox = nullptr;

    QHBoxLayout *lambda_sublayout = nullptr;
    QLabel 		*lambda_label = nullptr;
    QLineEdit 	*lambda_LineEdit = nullptr;
    QComboBox 	*lambda_ComboBox = nullptr;

    QVBoxLayout *lamb_dens_sublayout = nullptr;
    QHBoxLayout *pushbutton_sublayout = nullptr;
    QPushButton *calculate_PushButton = nullptr;


    QHBoxLayout *inputdata_button_sublayout = nullptr;
    QVBoxLayout *inputdata_sublayout = nullptr;


    QGroupBox *result_box = nullptr;
    QVBoxLayout *groupbox_layout = nullptr;

    ResultLine *rl_sld = nullptr;
    ResultLine *rl_sld_im = nullptr;
    ResultLine *rl_pot_v = nullptr;
    ResultLine *rl_pot_v_im = nullptr;
    ResultLine *rl_ch_wl = nullptr;
    ResultLine *rl_cr_ang = nullptr;
    ResultLine *rl_cr_mom = nullptr;
    ResultLine *rl_atl_c = nullptr;
    ResultLine *rl_absorb = nullptr;
    ResultLine *rl_scatt = nullptr;


    void initialize();
    void set_menubar();

    void set_widgets();
    void set_chemicalline();
    void set_densityline();
    void set_results();

    void set_layouts();
    void set_formula_layout();
    void set_density_lambda_layout();
    void set_results_layout();

    void set_signals();


    void calculation();
    bool checking();
    QString errors_list();

    void non_results();

private slots:
    void press_calculate_button();

    void open_file_submenu();
    void saveas_file_submenu();
    void help_submenu();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
