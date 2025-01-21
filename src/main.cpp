#include <GL/glut.h>
#include <iostream> // Incluindo o cabeçalho necessário
#include <cmath>


float baseAngle = 0.0f;
float shoulderAngle = 90.0f;
float elbowAngle = 90.0f;

float wristAngleX = 0.0f; 
float wristAngleY = 0.0f;
float wristAngleZ = 0.0f;

float gripAngle = 0.0f;


float elbowExtension = 0.0f;           
const float elbowExtensionMin = -1.3f; 
const float elbowExtensionMax = 2.0f; 


float forearmRotationAngle = 0.0f;


float ballPosition[3] = {1.4f, 0.0f, 0.0f};

float ballVelocityY = 0.0f;
float ballPositionY = 0.0f;
bool isBallFalling = false;

const float gravity = -0.001f;
const float floorHeight = -10.0f;


void init()
{
   glEnable(GL_DEPTH_TEST);
}

void update(int value)
{
   if (isBallFalling)
   {
      ballVelocityY -= gravity;
      ballPositionY += ballVelocityY;

      if (ballPositionY <= floorHeight)
      {
         ballPositionY = floorHeight;
         ballVelocityY = 0.0f;
         isBallFalling = false;
      }
   }

   glutPostRedisplay();
   glutTimerFunc(16, update, 0);
}

// Desenha os dedos
void drawClaw(float offsetX, float offsetY, float rotation)
{
   glPushMatrix();

   glTranslatef(offsetX, offsetY, 0.0f);
   glRotatef(rotation, 0.0, 0.0, 1.0);
   glTranslatef(0.3f, 0.0f, 0.0f);
   glPushMatrix();
   glScalef(1.0f, 0.1f, 0.1f);
   glutSolidCube(1.0);
   glPopMatrix();

   glTranslatef(0.3f, 0.0f, 0.0f);
   glRotatef(rotation, 0.0, 0.0, 1.0);
   glTranslatef(0.3f, 0.0f, 0.0f);
   glPushMatrix();
   glScalef(1.0f, 0.1f, 0.1f);
   glutSolidCube(1.0);
   glPopMatrix();

   glPopMatrix();
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   // Ajuste da câmera
   gluLookAt(0.0, 6.0, 20.0,
             0.0, 0.0, 0.0,
             0.0, 1.0, 0.0);

   // Base fixa
   glPushMatrix();
   glRotatef(baseAngle, 0.0, 1.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   glPushMatrix();
   glScalef(5.0, 0.3, 5.0);
   glutSolidCube(1.0);
   glPopMatrix();

   // Ombro
   glPushMatrix();
   glTranslatef(0.0, 0.3, 0.0);
   glRotatef(shoulderAngle, 0.0, 0.0, 1.0);
   glRotatef(forearmRotationAngle, 1.0, 0.0, 0.0);
   glColor3f(0.5, 0.5, 0.5);
   glTranslatef(1.5, 0.0, 0.0);
   glPushMatrix();
   glScalef(4.0, 0.6, 0.6);
   glutSolidCube(1.0);
   glPopMatrix();

   // Cotovelo
   glTranslatef(elbowExtension, 0.0f, 0.0f);
   glRotatef(elbowAngle, 0.0, 0.0, 1.0);
   glColor3f(0.5, 0.5, 0.5);
   glTranslatef(2.0, 0.0, 0.0);
   glPushMatrix();
   glScalef(4.0, 0.6, 0.6);
   glutSolidCube(1.0);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-2.01, 0.0, 0.0);
   glColor3f(0.7, 0.7, 0.7);
   glutSolidSphere(0.5, 20, 20);
   glPopMatrix();

   // Mão
   glTranslatef(2.0, 0.0, 0.0);
   glRotatef(wristAngleX, 1.0, 0.0, 0.0);
   glRotatef(wristAngleY, 0.0, 1.0, 0.0);
   glRotatef(wristAngleZ, 0.0, 0.0, 1.0);
   glColor3f(0.7, 0.7, 0.7);
   glPushMatrix();
   glutSolidSphere(0.5, 20, 20);
   glPopMatrix();

   // Dedos
   glPushMatrix();
   glTranslatef(0.4, 0.3, 0.0);
   drawClaw(0.0, 0.0, gripAngle);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.4, -0.3, 0.0);
   drawClaw(0.0, 0.0, -gripAngle);
   glPopMatrix();

   if (gripAngle >= 1.0f && !isBallFalling)
   {
      isBallFalling = true;
   }

   if (isBallFalling)
   {
      glPushMatrix();
      glTranslatef(ballPosition[0], ballPositionY, ballPosition[2]);
      glColor3f(1.0, 0.0, 0.0);
      glutSolidSphere(0.3f, 20, 20);
      glPopMatrix();
   }
   else
   {
      glPushMatrix();
      glTranslatef(1.5, 0.0, 0.0);
      glColor3f(1.0, 0.0, 0.0);
      glutSolidSphere(0.3f, 20, 20);
      glPopMatrix();
   }

   glPopMatrix();

   glPopMatrix();

   glutSwapBuffers();
}

void reshape(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
   glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
      // BASE
   case 'b':
      baseAngle = fmod(baseAngle + 5.0f, 360.0f);
      break;
   case 'B':
      baseAngle = fmod(baseAngle - 5.0f + 360.0f, 360.0f);
      break;

   // PULSO
   case 'q':
      wristAngleX += 5.0f;
      break;
   case 'Q':
      wristAngleY += 5.0f;
      break;
   case 'w':
      wristAngleZ += 5.0f;
      break;
   case 'W':
      wristAngleZ -= 5.0f;
      break;

      // OMBRO
      break;
   case 's':
      forearmRotationAngle += 5.0f;
      break;
   case 'S':
      forearmRotationAngle -= 5.0f;
      break;

      // COTOVELO
   case 'd':
      if (elbowAngle < 90.0f)
         elbowAngle += 5.0f;
      break;
   case 'D':
      if (elbowAngle > -90.0f)
         elbowAngle -= 5.0f;
      break;

   case 'f': 
      if (elbowExtension < elbowExtensionMax)
         elbowExtension += 0.1f;
      break;
   case 'F': 
      if (elbowExtension > elbowExtensionMin)
         elbowExtension -= 0.1f;
      break;

      // DEDOS
   case 'z':
      if (gripAngle < 45.0f)
         gripAngle += 5.0f;
      break;
   case 'Z':
      if (gripAngle > 0.0f)
         gripAngle -= 5.0f;
      break;

      // ESC para sair
   case 27:
      exit(0);
      break;
   }
   glutPostRedisplay();
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(800, 600);
   glutCreateWindow("Trabalho CG - Braco Robotico");

   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutTimerFunc(16, update, 0);
   glutMainLoop();
   return 0;
}
