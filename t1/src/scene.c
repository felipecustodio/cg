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


        /*--------------------WINDMILL--------------------*/

        // Refresh matrix for new object
        glLoadIdentity();
        Triangle *roof = createTriangle();
                setTriangleCoordinates(roof, -70.0f, 50.0f, 70.0f,50.0f, 0.0f,100.0f);
                setTriangleColor(roof, 1.0f, 1.0f, 1.0f);
                drawTriangleFilled(roof);
        freeTriangle(roof);

        // Refresh matrix for new object
        glLoadIdentity();
        Quadrilateral *building = createQuad();
                setQuadCoordinates(building, -50.0f, 50.0f, 50.0f, 50.0f, 100.0f, -250.0f, -100.0f, -250.0f);
                setQuadColor(building, 1.0f, 1.0f, 1.0f);
                drawQuadHollow(building);
        freeQuad(building);

        // Refresh matrix for new object
        glLoadIdentity();
        Quadrilateral *door = createQuad();
                setQuadCoordinates(door, -25.0f, -180.0f, 25.0f, -180.0f, 25.0f, -250.0f, -25.0f, -250.0f);
                setQuadColor(door, 1.0f, 1.0f, 1.0f);
                drawQuadHollow(door);
        freeQuad(door);

        /*--------------------END--------------------*/

        /*--------------------PADS--------------------*/

        // Refresh matrix for new object
        glLoadIdentity();
        Triangle *pad1 = createTriangle();
                setTriangleCoordinates(pad1, 0.0f, 0.0f, 100.0f, 200.0f, 0.0f, 100.0f);
                setTriangleColor(pad1, 204.0f, 153.0f, 0.0f);
                setTriangleThickness(pad1, 5.0f);
                rotateTriangleVertex(pad1, getCurAngle(), 1);
                drawTriangleFilled(pad1);
        freeTriangle(pad1);

        // Refresh matrix for new object
        glLoadIdentity();
        Triangle *pad2 = createTriangle();
                setTriangleCoordinates(pad2, 0.0f, 0.0f, 200.0f, -100.0f, 100.0f, 0.0f);
                setTriangleColor(pad2, 0.0f, 0.0f, 255.0f);
                setTriangleThickness(pad2, 5.0f);
                rotateTriangleVertex(pad2, getCurAngle(), 1);
                drawTriangleFilled(pad2);
        freeTriangle(pad2);

        // Refresh matrix for new object
        glLoadIdentity();
        Triangle *pad3 = createTriangle();
                setTriangleCoordinates(pad3, 0.0f, 0.0f, -100.0f, -200.0f, 0.0f, -100.0f);
                setTriangleColor(pad3, 255.0f, 0.0f, 0.0f);
                setTriangleThickness(pad3, 5.0f);
                rotateTriangleVertex(pad3, getCurAngle(), 1);
                drawTriangleFilled(pad3);
        freeTriangle(pad3);

        // Refresh matrix for new object
        glLoadIdentity();
        Triangle *pad4 = createTriangle();
                setTriangleCoordinates(pad4, 0.0f, 0.0f, -200.0f, 100.0f, -100.0f, 0.0f);
                setTriangleColor(pad4, 0.0f, 255.0f, 0.0f);
                setTriangleThickness(pad4, 5.0f);
                rotateTriangleVertex(pad4, getCurAngle(), 1);
                drawTriangleFilled(pad4);
        freeTriangle(pad4);

        /*--------------------END--------------------*/

        // Refresh matrix for new object
        glLoadIdentity();

        // Joint of windmill pole
        glBegin(GL_POINTS);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex2f(0, 0);
        glEnd();

        glPointSize(10.0); // Define dot size

        /*--------------------TEXT--------------------*/

        char* text = "- Diminui resistência do ar";
        Text* UI = createText(GLUT_BITMAP_9_BY_15, text);
        drawText(UI, -450, 200);
        freeText(UI);

        char* text2 = "+ Aumenta resistência do ar";
        Text* UI2 = createText(GLUT_BITMAP_9_BY_15, text2);
        drawText(UI2, -450, 220);
        freeText(UI2);

        char* text3 = "Trabalho 01 - Windmill";
        Text* UI3 = createText(GLUT_BITMAP_9_BY_15, text3);
        drawText(UI3, -450, 240);
        freeText(UI3);

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
