#include <GL/gl.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

double x[10000];
double y[10000];
double dx[10000];
double dy[10000];
double new_dx[10000];
double new_dy[10000];
int n = 6000;
double radius = 0.005;

double distance2(int i, int j) {
    return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

void drawCircle(double x, double y) {
    double vertices[9] = {};
    // glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);

    glColor3f(0.0f, 1.0f, 1.0f);
    vertices[0] = x;
    vertices[1] = y;
    int circleEdge = 12;
    double twicePi = 2.0 * 3.142;
    for (int i = 0; i < circleEdge; i++) {
        vertices[3] = (x + (radius * cos(i * twicePi / circleEdge)));
        vertices[4] = (y + (radius * sin(i * twicePi / circleEdge)));
        vertices[6] = (x + (radius * cos((i + 1) * twicePi / circleEdge)));
        vertices[7] = (y + (radius * sin((i + 1) * twicePi / circleEdge)));
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    // glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    glEnableClientState(GL_VERTEX_ARRAY);
    for (int i = 0; i < n; i++) {
        drawCircle(x[i], y[i]);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

void init() {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        x[i] = (rand() % (2000 - 1) - 1000) / 1000.0;
        y[i] = (rand() % (2000 - 1) - 1000) / 1000.0;
        dx[i] = (rand() % 2000 - 1000) / 200000.0;;
        dy[i] = (rand() % 2000 - 1000) / 200000.0;;
        new_dx[i] = dx[i];
        new_dy[i] = dy[i];
    }
}

void update() {
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
          if (i == j) continue;
          if (distance2(i, j) <= 4 * radius * radius) {
              if ((x[i] - x[j]) * (dx[i] - dx[j]) + (y[i] - y[j]) * (dy[i] - dy[j]) <= 0) {
                double dot = (dx[i] - dx[j]) * (x[i] - x[j]) + (dy[i] - dy[j]) * (y[i] - y[j]);
                new_dx[i] = dx[i] - dot / distance2(i, j) * (x[i] - x[j]);
                new_dy[i] = dy[i] - dot / distance2(i, j) * (y[i] - y[j]);
                new_dx[j] = dx[j] - dot / distance2(i, j) * (x[j] - x[i]);
                new_dy[j] = dy[j] - dot / distance2(i, j) * (y[j] - y[i]);
              }
          }
      }
  }
  for (int i = 0; i < n; i++) {
      if (x[i] + radius >= 1) new_dx[i] = -abs(new_dx[i]);
      if (x[i] - radius <= -1) new_dx[i] = abs(new_dx[i]);
      if (y[i] + radius >= 1) new_dy[i] = -abs(new_dy[i]);
      if (y[i] - radius <= -1) new_dy[i] = abs(new_dy[i]);

      dx[i] = new_dx[i];
      dy[i] = new_dy[i];
      x[i] += dx[i];
      y[i] += dy[i];
  }

  // glutPostRedisplay();
  // glutTimerFunc(33, timerFunc, 1);
}

void loop() {
    init();
    while (1) {
        // vertices[0] += -0.001;
        display();
        update();
        // break;

        int T = 1000000;
        while (T--);
    }
}

int main(int argc, char** argv) {
    int width = 800;
    int height = 800;
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitWindowSize(width, height);   // Set the window's initial width & height
    // glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutDisplayFunc(loop); // Register display callback handler for window re-paint
    // ---
    // glViewport(0, 0, 0.2, 0.2);
    // glMatrixMode(GL_PROJECTION);
    // glEnable(GL_DEPTH_TEST);
    // gluPerspective(45, (float)width / height, .1, 100);
    // glMatrixMode(GL_MODELVIEW);
    // ---
    // glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutMainLoop();           // Enter the infinitely event-processing loop
    return 0;
}
