#include "glwidget.h"

GLWidget::GLWidget(QWidget * parent)
    :QOpenGLWidget (parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(20);
}


void GLWidget::initializeGL()
{
    parse();
}

void GLWidget::resizeGL(int w, int h) {}

void GLWidget::parse(){
   data_model = {.vertices_count = 0,
                          .triangle_cnt = 0,
                          .square_cnt = 0,
                          .triangle_coord = NULL,
                          .square_coord = NULL,
                          .vertices = NULL};
   parser(&data_model, filename);
}
void GLWidget::paintGL()
{
   update_view();
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-1, 1, -1, 1, 2, 15);
   glTranslated(-0.25, -0.25, -4);
   glClearColor(back_red, back_green, back_blue, 0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnableClientState(GL_VERTEX_ARRAY);
   glColor3d(l_red, l_green, l_blue);
   glLineWidth(l_size);
   glVertexPointer(3, GL_DOUBLE, 0, data_model.vertices);
   glDrawElements(GL_LINE_LOOP, data_model.triangle_cnt * 3, GL_UNSIGNED_INT, data_model.triangle_coord);
   glColor3d(v_red, v_green,v_blue);
   glPointSize(v_size);
   glDrawElements(GL_POINTS, data_model.triangle_cnt *3, GL_UNSIGNED_INT, data_model.triangle_coord);
   glDrawElements(GL_LINE_LOOP,data_model.square_cnt * 4, GL_UNSIGNED_INT, data_model.square_coord);
   glDisableClientState(GL_VERTEX_ARRAY);
}


void GLWidget::update_view() {
   if (scale != scale_curr) {
      do_scaling();
      scale_curr = scale;
}
//   if (project_curr != projection) {
//       do_scaling();
//   }
//   project_curr = projection;
}

void GLWidget::do_scaling() {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   if (projection == 1) {
       glFrustum(-1, 1, -1, 1, 2, 15);
       glTranslated(0, 0, -7);
   } else {
       glOrtho(-1, 1, -1, 1, 100, -100);
   }

   scaling(&data_model, scale / scale_curr);
}



