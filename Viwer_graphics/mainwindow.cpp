#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionwidget_triggered()
{
    close();
}


 void MainWindow::on_open_pushButton_clicked()
{
    QString QString_filename = QFileDialog::getOpenFileName(
        this, tr("Open .obj file:"), "~/", tr("Obj Files (*.obj)"));
    ui->lineEdit_file_name->setText(QString_filename);
    std::string std_filename = ui->lineEdit_file_name->text().toStdString();
    ui->widget->filename = (char *)std_filename.c_str();
    ui->widget->parse();
 }


void MainWindow::on_change_color_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color.isValid()) {
        ui->widget->l_blue = color.blueF();
        ui->widget->l_green = color.greenF();
        ui->widget->l_red = color.redF();
    }
}


void MainWindow::on_change_color_vertices_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color.isValid()) {
        ui->widget->v_blue = color.blueF();
        ui->widget->v_green = color.greenF();
        ui->widget->v_red = color.redF();
    }
}


void MainWindow::on_size_horizontalSlider_valueChanged(int value)
{
    ui->widget->v_size = value;
}


void MainWindow::on_thickness_horizontalSlider_valueChanged(int value)
{
    ui->widget->l_size = value;
}


void MainWindow::on_change_color_background_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color.isValid()) {
        ui->widget->back_blue = color.blueF();
        ui->widget->back_green = color.greenF();
        ui->widget->back_red = color.redF();
    }
}


void MainWindow::on_scale_spinBox_valueChanged(int arg1)
{
    ui->widget->scale = arg1;
}



void MainWindow::on_parallel_radioButton_clicked()
{
    ui->widget->projection = 1;
}


void MainWindow::on_central_radioButton_clicked()
{
    ui->widget->projection =2;
}

