#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QColor>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL/QtOpenGL>
#include <QWidget>
#include <QImage>
#include "qgifimage.h"

extern "C" {
#include "../s21_parser.h"
}

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget * parent = nullptr);
    char *filename;
    model_data data_model = {.vertices_count = 0,
                             .triangle_cnt = 0,
                             .square_cnt = 0,
                             .triangle_coord = NULL,
                             .square_coord = NULL,
                             .vertices = NULL};
    void parse();
    double v_red;
    double v_green;
    double v_blue;
    double v_size;
    double l_red;
    double l_green;
    double l_blue;
    double l_size;
    double back_blue = 1;
    double back_red = 1;
    double back_green = 1;
    double scale;
    double scale_curr;
    int projection; // 1 - parallel, 0 - central
    int projection_now;
    int line_projection; // 1- solid, 2 - dashed
    int display_methode; // 1 - circle, 2 - sqare , none - 0
    double translate_x;
    double translate_y;
    double translate_z;
    double translate_curr_x;
    double translate_curr_y;
    double translate_curr_z;
    double rotate_curr_x;
    double rotate_curr_y;
    double rotate_curr_z;
    double rotate_x;
    double rotate_y;
    double rotate_z;
    int create_gif_status;
    int create_jpeg_status;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void update_view();
    void rotate_translate();
    void draw_lines();
    void create_settings();
    void read_settings();
    ~GLWidget();

private:
    QTimer timer;

};

#endif // GLWIDGET_H
