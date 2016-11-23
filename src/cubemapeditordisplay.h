#ifndef CUBEMAPEDITORDISPLAY_H
#define CUBEMAPEDITORDISPLAY_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QWheelEvent>

#include "cubemapeditor.h"
#include "cubemapeditorimage.h"
#include <vector>
/*
 * This class provides an interactive display
 * of the cube map in CubeMapEditor.
 */

typedef struct {
    enum Orientation { Horizontal, Vertical };

    Orientation orientation;
    double normalized_offset;
} DisplayRuler;

class CubeMapEditorDisplay : public QOpenGLWidget,
                             protected QOpenGLFunctions
{
    Q_OBJECT


public:

    explicit CubeMapEditorDisplay(QWidget *parent = 0);
    ~CubeMapEditorDisplay();

    // The following four methods operate on selected_face
    //   selected_face = Face::NONE  -->  operate on this display instead (no loadImage)

    void selectFace(CubeMapEditor::Face face);

    // Focus: positioning & zoom
    void getFocus(double& zoom, QPointF& offset);
    void setFocus(double zoom, QPointF offset);

    void loadImage(QImage image);
    CubeMapEditorImage* getImage();
    //vector<vector<uint8_t*>> getWeight();

protected:
    void initializeGL();
    void paintGL();

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLShaderProgram* program;

    QMatrix4x4 matrix_model;
    QMatrix4x4 matrix_view;
    QMatrix4x4 matrix_projection;

    // Cube map images
    CubeMapEditorImage* images;

    // Display rulers
    QList<DisplayRuler> rulers;

    // Focus
    double zoom;
    QPointF offset;

    // Shader uniform locations
    GLuint uniform_model;
    GLuint uniform_view;
    GLuint uniform_projection;
    GLuint uniform_haveTexture;
    GLuint uniform_zoom;
    GLuint uniform_offset;

    CubeMapEditor::Face selected_face;

    QPoint last_mouse_pos;

    // Rulers
    void addRuler(DisplayRuler r);
    void removeRuler(DisplayRuler r);
    void drawRulers(QPainter& p);
};

#endif // CUBEMAPEDITORDISPLAY_H
