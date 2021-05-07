#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define window_width 1080
#define window_height 720

double x[10000];
double y[10000];
double dx[10000];
double dy[10000];
double new_dx[10000];
double new_dy[10000];
int n = 600;
double radius = 0.02;

double distance2(int i, int j) {
    return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

double nextDistance2(int i, int j) {
    double c = 0.01;
    double x1 = x[i] + c * dx[i];
    double y1 = y[i] + c * dy[i];
    double x2 = x[j] + c * dx[j];
    double y2 = y[j] + c * dy[j];
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

void drawCircle(double x, double y) {
  glLoadIdentity();
  glTranslatef(0, 0, -10);
  glColor3ub(0, 255, 255);
  double twicePi = 2.0 * 3.142;
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(x, y);
  int circleEdge = 12;
  for (int i = 0; i <= circleEdge; i++) {
    glVertex2f((x + (radius * cos(i * twicePi / circleEdge))),
               (y + (radius * sin(i * twicePi / circleEdge))));
  }
  glEnd();
}

void displayFunc() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (int i = 0; i < n; i++) {
      drawCircle(x[i], y[i]);
  }
  glutSwapBuffers();
}

void init() {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        x[i] = (rand() % (2000 - 1) - 1000) / 1000.0;
        y[i] = (rand() % (2000 - 1) - 1000) / 1000.0;
        dx[i] = (rand() % 2000 - 1000) / 10000.0;;
        dy[i] = (rand() % 2000 - 1000) / 10000.0;;
        new_dx[i] = dx[i];
        new_dy[i] = dy[i];
    }
}

void timerFunc(int id) {
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
      if (x[i] + radius >= 3) new_dx[i] = -abs(new_dx[i]);
      if (x[i] - radius <= -3) new_dx[i] = abs(new_dx[i]);
      if (y[i] + radius >= 3) new_dy[i] = -abs(new_dy[i]);
      if (y[i] - radius <= -3) new_dy[i] = abs(new_dy[i]);

      dx[i] = new_dx[i];
      dy[i] = new_dy[i];
      x[i] += dx[i];
      y[i] += dy[i];
  }

  glutPostRedisplay();
  glutTimerFunc(33, timerFunc, 1);
}

void GL_Setup(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glEnable(GL_DEPTH_TEST);
  gluPerspective(45, (float)width / height, .1, 100);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(window_width, window_height);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutCreateWindow("GPU Final");
  glutDisplayFunc(displayFunc);
  glutTimerFunc(33, timerFunc, 1);
  GL_Setup(window_width, window_height);
  init();
  glutMainLoop();
}
