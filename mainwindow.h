#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QMenuBar>

#include "coresld.h"
#include "resultswidget.h"
#include "inputwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    CoreSLD *core               = nullptr;

    QWidget *central_widget     = nullptr;
    QVBoxLayout *v_layout       = nullptr;

    ResultsWidget *rw           = nullptr;
    InputWidget *iw             = nullptr;

    QMenuBar    *menubar        = nullptr;
    QAction     *exit_action    = nullptr;
    QAction     *open_action    = nullptr;
    QAction     *saveas_action  = nullptr;
    QAction     *help_action    = nullptr;

    QStatusBar *statusbar       = nullptr;


    void set_data();
    void calculation();
    QString errors_list();


    void initialize();
    void set_menubar();
    void set_widgets();
    void set_signals();

private slots:
    void pressed_calc_button();
    void open_file_submenu();
    void saveas_file_submenu();
    void help_submenu();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
