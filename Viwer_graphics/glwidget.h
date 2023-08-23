#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QColor>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL/QtOpenGL>
#include <QWidget>

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
    double back_blue;
    double back_red;
    double back_green;
    int scale;
    int scale_curr;
    int projection; // 1 - perspective, 2 - central

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void do_scaling();
    void update_view();

private:
    QTimer timer;

};

#endif // GLWIDGET_H
