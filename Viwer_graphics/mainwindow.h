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

    void on_parallel_radioButton_clicked();

    void on_central_radioButton_clicked();

    void on_x_axis_translate_spinBox_valueChanged(int arg1);

    void on_y_axis_translate_spinBox_valueChanged(int arg1);

    void on_z_axis_translate_spinBox_valueChanged(int arg1);

    void on_x_axis_rotate_spinBox_valueChanged(int arg1);

    void on_y_axis_rotate_spinBox_valueChanged(int arg1);

    void on_z_axis_rotate_spinBox_valueChanged(int arg1);

    void on_scale_SpinBox_valueChanged(double arg1);

    void on_solid_radioButton_clicked();

    void on_dashed_radioButton_clicked();

    void on_display_circle_radioButton_clicked();

    void on_display_square_radioButton_clicked();

    void on_display_none_radioButton_clicked();

    void on_save_img_pushButton_clicked();

    void on_save_gif_pushButton_clicked();

    void save_video();

private:
    Ui::MainWindow *ui;
    QGifImage *gif;
    QImage *frame;
    QTimer *timer;
    int count;
    QString file_name;
};
#endif // MAINWINDOW_H
