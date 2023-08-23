#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <glwidget.h>
#include <OpenGL/gl.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionwidget_triggered();

    void on_open_pushButton_clicked();

    void on_change_color_pushButton_clicked();

    void on_change_color_vertices_pushButton_clicked();

    void on_size_horizontalSlider_valueChanged(int value);

    void on_thickness_horizontalSlider_valueChanged(int value);

    void on_change_color_background_pushButton_clicked();

    void on_scale_spinBox_valueChanged(int arg1);

    void on_parallel_radioButton_clicked();

    void on_central_radioButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
