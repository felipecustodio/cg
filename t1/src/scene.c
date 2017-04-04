#include "../includes/scene.h"

/* -------------------------------- INPUT ----------------------------------- */

/* ------ INPUT STATUS -----*/
int leftMouseButtonDown = 0;
int rightMouseButtonDown = 0;

void on_mouseClick(int button, int click_state,
        int x_mouse_position, int y_mouse_position)
{

	if (button == GLUT_RIGHT_BUTTON) {
                if (CONSOLE == 1 && DEBUG == 1) printf(">[INPUT]: Right Mouse Button");
                rightMouseButtonDown = (click_state == GLUT_DOWN);

        } else if (button == GLUT_LEFT_BUTTON) {
                        if (CONSOLE == 1 && DEBUG == 1) printf(">[INPUT]: Left Mouse Button");
                        leftMouseButtonDown = (click_state == GLUT_DOWN);
	}
	glutPostRedisplay(); // Forces scene redraw
}

void mouseHold() {
        if (leftMouseButtonDown) {
                accelerateLeft();
        } else if (rightMouseButtonDown) {
                accelerateRight();
        }
}

/* -------------------------------- INPUT ----------------------------------- */

/* -------------------------------- WINDOW ---------------------------------- */
void reshape(int width, int height)
{
    // Screen can't be smaller than 0
    if(height == 0)
        height = 1;

    float ratio = width * 1.0/height;

    // Changes matrix mode to projection
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Viewport correction
    glViewport(0, 0, width, height);

    // Perspective and projection correction
    //gluPerspective(45, ratio, -1, 1);
    gluOrtho2D(-ORTHO_X * ratio, ORTHO_X * ratio, -ORTHO_Y, ORTHO_Y);

    // Switches matrix mode back to modelview
    glMatrixMode(GL_MODELVIEW);
}
/* -------------------------------- WINDOW ---------------------------------- */

/* ----------------------------- TEXTURES ------------------------------ */



/* ----------------------------- TEXTURES ------------------------------ */


/* ----------------------------- SCENE DRAWING ------------------------------ */
void drawScene()
{

        // Load matrix mode
        glMatrixMode(GL_MODELVIEW);

        // Refresh matrix for new object
        glLoadIdentity();

        // Draw background

        // Joint of windmill pole
        glBegin(GL_POINTS);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex2f(0, 0);
        glEnd();

        glPointSize(10.0); // Define dot size

        // Refresh matrix for new object
        glLoadIdentity();

        Quadrilateral *quad = createQuad(0.0f, 0.0f, 25.0f, 200.0f, 5.0f);
                setQuadColor(quad, 0.6f, 0.4f, 0.0f);
                glTranslatef(0.0, -100.0f, 0.0f);
                //rotateQuadCenter(quad, -getCurAngle());
                drawQuadHollow(quad);
        freeQuad(quad);

        // Refresh matrix for new object
        glLoadIdentity();

        Triangle *tri = createTriangle();
                setTriangleCoordinates(tri, 0.0f, 0.0f, 150.0f, 0.0f, 0.0f, 150.0f);
                setTriangleColor(tri, 0.0f, 0.4f, 0.6f);
                setTriangleThickness(tri, 5.0f);
                rotateTriangleVertex(tri, getCurAngle(), 1);
                drawTriangleHollow(tri);
        freeTriangle(tri);

        Triangle *tri2 = createTriangle();
                setTriangleCoordinates(tri2, 0.0f, 0.0f, -150.0f, 0.0f, 0.0f, -150.0f);
                setTriangleColor(tri2, 0.6f, 0.4f, 0.6f);
                setTriangleThickness(tri2, 5.0f);
                drawTriangleHollow(tri2);
        freeTriangle(tri2);

        Circle *circle = createCircle(25.0f, 5.0f);
                setCircleColor(circle, 0.75f, 0.75f, 0.75f);
                drawCircleFilled(circle);
        freeCircle(circle);

        Circle *circle2 = createCircle(15.0f, 5.0f);
                setCircleColor(circle2, 0.9f, 0.9f, 0.9f);
                drawCircleFilled(circle2);
        freeCircle(circle2);
}

void drawLoop()
{
        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1);

        // Repaint screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw scene
        drawScene();

        // Check mouse event
        mouseHold();

        // Animator
        physicsAnimator();

        // Clear buffer
        glutSwapBuffers();
}
/* ----------------------------- SCENE DRAWING ------------------------------ */
