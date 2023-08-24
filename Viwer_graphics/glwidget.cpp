#include "glwidget.h"

GLWidget::GLWidget(QWidget * parent)
    :QOpenGLWidget (parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(20);
}

GLWidget::~GLWidget(){
//    delete &data_model;
}

void GLWidget::initializeGL()
{
    translate_curr_x = translate_x = 0.0;
    translate_curr_y = translate_y = 0.0;
    translate_curr_z = translate_z = 0.0;
    rotate_curr_x = rotate_x = 0.0;
    rotate_curr_y = rotate_y = 0.0;
    rotate_curr_z = rotate_z = 0.0;
    scale = scale_curr = 1.0;
    projection = projection_now = 0;
    create_gif_status = 0;
    create_jpeg_status = 0;
    read_settings();
    parse();
}

void GLWidget::paintGL()
{
   create_settings();
   update_view();
   rotate_translate();

   glClearColor(back_red, back_green, back_blue, 0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glVertexPointer(3, GL_DOUBLE, 0, data_model.vertices);

   draw_lines();

   if (display_methode != 0) {
       if (display_methode == 1 ){
            glEnable(GL_POINT_SMOOTH);
       }  else {
            glDisable(GL_POINT_SMOOTH);
       }
       glColor3d(v_red, v_green,v_blue);
       glPointSize(v_size);
       glDrawElements(GL_POINTS, data_model.triangle_cnt *3, GL_UNSIGNED_INT, data_model.triangle_coord);
       glDrawElements(GL_POINTS, data_model.square_cnt * 4, GL_UNSIGNED_INT, data_model.square_coord);
   }
   glDisableClientState(GL_VERTEX_ARRAY);
}


void GLWidget::update_view() {
   if(projection_now != projection) {
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       if (projection == 0) {
            glFrustum(-1, 1, -1, 1, 2, 15);
            glTranslated(0, 0, -7);
       } else {
           glOrtho(-1, 1, -1, 1, 100, -100);
       }
       projection_now = projection;
   }

   if (scale != scale_curr) {
       scaling(&data_model, scale / scale_curr);
       scale_curr = scale;
}
}

void GLWidget::rotate_translate() {

    move_obj(&data_model, translate_x - translate_curr_x, translate_y - translate_curr_y, translate_z - translate_curr_z);
    rotate(&data_model, rotate_x - rotate_curr_x, 1);
    rotate(&data_model, rotate_y - rotate_curr_y, 2);
    rotate(&data_model, rotate_z - rotate_curr_z, 3);

    translate_curr_x = translate_x;
    translate_curr_y = translate_y;
    translate_curr_z = translate_z;

    rotate_curr_x = rotate_x;
    rotate_curr_y = rotate_y;
    rotate_curr_z = rotate_z;
}

void GLWidget::draw_lines(){
    if (line_projection == 2) {
       glEnable(GL_LINE_STIPPLE);
       glLineStipple(1, 0x00F0);
    } else {
       glDisable(GL_LINE_STIPPLE);
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(l_red, l_green, l_blue);
    glLineWidth(l_size);
    glDrawElements(GL_LINE_LOOP, data_model.triangle_cnt * 3, GL_UNSIGNED_INT, data_model.triangle_coord);
    glDrawElements(GL_LINE_LOOP,data_model.square_cnt * 4, GL_UNSIGNED_INT, data_model.square_coord);
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

void GLWidget::create_settings(){
    QSettings settings("MyViwer");


    settings.setValue("color_back_blue", back_blue); // backgound
    settings.setValue("color_back_red", back_red);
    settings.setValue("color_back_green", back_green);

    settings.setValue("color_line_blue", l_blue); // line_color
    settings.setValue("color_line_red", l_red);
    settings.setValue("color_line_green", l_green);

    settings.setValue("color_dots_red", v_red); // vert_color
    settings.setValue("color_dots_blue", v_blue);
    settings.setValue("color_dots_green", v_green);

    settings.setValue("projection_dots", display_methode); //projection_dots
    settings.setValue("line_projection", line_projection); // line_projection
}

void GLWidget::read_settings(){
    QSettings settings("MyViwer"); //read settings

    back_blue = settings.value("color_back_blue").toDouble();
    back_red = settings.value("color_back_read").toDouble();
    back_green = settings.value("color_back_green").toDouble();

    l_blue = settings.value("color_line_blue").toDouble();
    l_red = settings.value("color_line_red").toDouble();
    l_green = settings.value("color_line_green").toDouble();

    v_blue = settings.value("color_dots_blue").toDouble();
    v_green = settings.value("color_dots_green").toDouble();
    v_red = settings.value("color_dots_red").toDouble();

    display_methode = settings.value("projection_dots").toInt();
    line_projection = settings.value("line_projection").toInt();
}


