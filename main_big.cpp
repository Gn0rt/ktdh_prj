#include <GL/glut.h>
#include <math.h>

float angle = 0.0; // Góc xoay ban d?u
bool rotateLight = false;

void init() {
    glEnable(GL_DEPTH_TEST); // kiem tra do sau
    glClearColor(0.1, 0.1, 0.1, 1.0); // thiet lap mau nen
}
void rotateScene(int value) {
    angle += 0.05f;
    if (angle > 360) angle = 0;
    glutPostRedisplay();
    if (rotateLight) glutTimerFunc(25, rotateScene, 0);
}
void DrawChessboardFloor() {
    int tiles = 10; // S? lu?ng ô vuông trên m?i hàng/c?t
    float size = 10.0f / tiles; // Kích thu?c c?a m?i ô vuông
    bool colorToggle = false;

    glBegin(GL_QUADS);
    for (int row = 0; row < tiles; ++row) {
        for (int col = 0; col < tiles; ++col) {
            colorToggle = !colorToggle; // Ð?i màu cho m?i ô
            if (colorToggle)
                glColor3f(0.0f, 0.0f, 0.0f); // Màu den
            else
                glColor3f(1.0f, 1.0f, 1.0f); // Màu tr?ng

            float x = -5.0f + col * size;
            float z = -5.0f + row * size;
            glVertex3f(x, -1.0f, z);
            glVertex3f(x, -1.0f, z + size);
            glVertex3f(x + size, -1.0f, z + size);
            glVertex3f(x + size, -1.0f, z);
        }
        colorToggle = !colorToggle; // Ð?i màu cho m?i hàng m?i
    }
    glEnd();
}



void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // C?p nh?t v? trí camera d?a vào góc xoay
    float x = 5.0 * sin(angle);
    float z = 5.0 * cos(angle);
    gluLookAt(x, 0.0, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


	if (rotateLight) {
        glDisable(GL_LIGHTING);
    }
    //glColor3f(0.8, 0.8, 0.8); // Màu s?c cho tu?ng

     DrawChessboardFloor();

    glBegin(GL_QUADS);
    // Sàn nhà
    glVertex3f(-5.0, -1.0, 5.0);
    glVertex3f(-5.0, -1.0, -5.0);
    glVertex3f(5.0, -1.0, -5.0);
    glVertex3f(5.0, -1.0, 5.0);
    // Tr?n nhà
    glColor3f(0.5f, 0.35f, 0.05f);
    glVertex3f(-5.0, 1.0, 5.0);
    glVertex3f(-5.0, 1.0, -5.0);
    glVertex3f(5.0, 1.0, -5.0);
    glVertex3f(5.0, 1.0, 5.0);
    // Các b?c tu?ng
    glColor3f(0.8, 0.8, 0.8);
    glVertex3f(-5.0, -1.0, -5.0);
    glVertex3f(-5.0, 1.0, -5.0);
    glVertex3f(5.0, 1.0, -5.0);
    glVertex3f(5.0, -1.0, -5.0);
    glVertex3f(5.0, -1.0, -5.0);
    glVertex3f(5.0, 1.0, -5.0);
    glVertex3f(5.0, 1.0, 5.0);
    glVertex3f(5.0, -1.0, 5.0);
    glVertex3f(5.0, -1.0, 5.0);
    glVertex3f(5.0, 1.0, 5.0);
    glVertex3f(-5.0, 1.0, 5.0);
    glVertex3f(-5.0, -1.0, 5.0);
    glVertex3f(-5.0, -1.0, 5.0);
    glVertex3f(-5.0, 1.0, 5.0);
    glVertex3f(-5.0, 1.0, -5.0);
    glVertex3f(-5.0, -1.0, -5.0);
    glEnd();

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

//void keyboard(unsigned char key, int x, int y) {
//    if (key == 'a') {
//        angle -= 0.05;
//    } else if (key == 'd') {
//        angle += 0.05;
//    }
//    glutPostRedisplay();
//}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            angle -= 0.05f;
            break;
        case 'd':
            angle += 0.05f;
            break;
        case 'r':
        case 'R':
            rotateLight = !rotateLight;
            if (rotateLight) {
                glutTimerFunc(25, rotateScene, 0);
            }
            break;
        case 27: // Escape key
            exit(0);
            break;
    }
    glutPostRedisplay();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("360 Degree Room View");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

