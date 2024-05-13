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
#include <QLabel>
#include <QComboBox>
#include "coresld.h"
#include "resultswidget.h"
#include "inputwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT


    ResultsWidget *rw;
    InputWidget *iw;

    CoreSLD *core = nullptr;
    QWidget *central_widget = nullptr;

    QMenuBar    *main_menubar = nullptr;
    QAction     *exit_action = nullptr;
    QAction     *open_action = nullptr;
    QAction     *saveas_action = nullptr;
    QAction     *help_action = nullptr;

    QAction     *light_theme = nullptr;
    QAction     *dark_theme = nullptr;

    QStatusBar *main_statusbar = nullptr;

    QVBoxLayout         *chemical_layout = nullptr;

    void initialize();
    void set_menubar();

    void set_widgets();

    void set_signals();

    void calculation();
    QString errors_list();

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
