#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings settings("MyViwer");
    if (settings.value("projection").toInt() == 0) {
        ui->central_radioButton->setChecked(true);
    } else {
        ui->parallel_radioButton->setChecked(true);
    }

    if (settings.value("line_projection").toInt() == 1) {
        ui->solid_radioButton->setChecked(true);
    } else {
        ui->solid_radioButton->setChecked(true);
    }

    if (settings.value("display_methode").toInt() == 1) {
        ui->display_circle_radioButton->setChecked(true);
    } else if (settings.value("display_methode").toInt() == 2) {
        ui->display_square_radioButton->setChecked(true);
    } else {
        ui->display_none_radioButton->setChecked(true);
    }

    double savedScale = settings.value("scale").toDouble();
    ui->scale_SpinBox->setValue(savedScale);
    int savedSizeLines = settings.value("size_lines").toInt();
    ui->thickness_horizontalSlider->setValue(savedSizeLines);


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
   QString QString_file_name = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), "OBJ File (*.obj)");
   ui->lineEdit_file_name->setText(QString_file_name);
   std::string std_filename = QString_file_name.toStdString();
   ui->widget->filename = new char[std_filename.length() + 1];
   strcpy(ui->widget->filename, std_filename.c_str());

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


void MainWindow::on_parallel_radioButton_clicked()
{
    ui->widget->projection = 1;
}


void MainWindow::on_central_radioButton_clicked()
{
    ui->widget->projection = 0;
}


void MainWindow::on_x_axis_translate_spinBox_valueChanged(int arg1)
{
    ui->widget->translate_x = (double)arg1/100;
}


void MainWindow::on_y_axis_translate_spinBox_valueChanged(int arg1)
{
     ui->widget->translate_y = (double)arg1/100;
}


void MainWindow::on_z_axis_translate_spinBox_valueChanged(int arg1)
{
   ui->widget->translate_z = (double)arg1/100;
}


void MainWindow::on_x_axis_rotate_spinBox_valueChanged(int arg1)
{
    ui->widget->rotate_x = (double)arg1 * M_PI / 180.;
}


void MainWindow::on_y_axis_rotate_spinBox_valueChanged(int arg1)
{
    ui->widget->rotate_y = (double)arg1 * M_PI / 180.;
}


void MainWindow::on_z_axis_rotate_spinBox_valueChanged(int arg1)
{
    ui->widget->rotate_z = (double)arg1 * M_PI / 180.;
}


void MainWindow::on_scale_SpinBox_valueChanged(double arg1)
{
    ui->widget->scale = arg1;
}


void MainWindow::on_solid_radioButton_clicked()
{
    ui->widget->line_projection = 1;
}


void MainWindow::on_dashed_radioButton_clicked()
{
    ui->widget->line_projection = 2;
}


void MainWindow::on_display_circle_radioButton_clicked()
{
    ui->widget->display_methode = 1;
}


void MainWindow::on_display_square_radioButton_clicked()
{
    ui->widget->display_methode = 2;
}


void MainWindow::on_display_none_radioButton_clicked()
{
    ui->widget->display_methode = 0;
}


void MainWindow::on_save_img_pushButton_clicked()
{
    QString save = NULL;
    save = QFileDialog::getSaveFileName(this, NULL, NULL,
                                        "JPEG (*.jpeg)");
    if (!save.isNull()) ui->widget->grabFramebuffer().save(save, NULL, 100);
}


void MainWindow::on_save_gif_pushButton_clicked(){
    gif = new QGifImage;
    frame = new QImage;
    timer = new QTimer(this);
    count = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(save_video()));
    timer->start(50);
}

void MainWindow::save_video() {
        count++;
        *frame = ui->widget->grabFramebuffer().scaled(640, 480, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        gif->addFrame(*frame);
        if (count == 50) {
            timer->stop();
            QString save = NULL;
            save = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
            if (!save.isNull()) gif->save(save);
        }
    }
