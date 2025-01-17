#include <GL/glut.h>
#include <cmath>

// Ângulos de rotação para cada parte
float baseAngle = 0.0f;
float shoulderAngle = 90.0f;
float armRotation = 0.0f;
float elbowAngle = 100.0f;
float wristAngle = 0.0f;
float wristRotationAngle = 0.0f;
float wristRotationAngleZ = 0.0f;
float gripAngle = 0.0f;                     // Ângulo de fechamento das garras
float ballPosition[3] = {2.5f, 0.0f, 0.0f}; // Posição inicial da bolinha na mão
bool holdingBall = true;                    // A bolinha já começa na mão

void init()
{
   glEnable(GL_DEPTH_TEST);
}

// Desenha uma garra (dedo) do robô, mais afiada e curvada
void drawClaw(float offsetX, float offsetY, float rotation)
{
   glPushMatrix();

   // Primeira parte da garra
   glTranslatef(offsetX, offsetY, 0.0f);
   glRotatef(rotation, 0.0, 0.0, 1.0);
   glTranslatef(0.3f, 0.0f, 0.0f);
   glPushMatrix();
   glScalef(1.0f, 0.1f, 0.1f); // Forma mais estreita e afiada
   glutSolidCube(1.0);
   glPopMatrix();

   // Segunda parte da garra
   glTranslatef(0.3f, 0.0f, 0.0f);
   glRotatef(rotation, 0.0, 0.0, 1.0);
   glTranslatef(0.3f, 0.0f, 0.0f);
   glPushMatrix();
   glScalef(1.0f, 0.1f, 0.1f); // Forma mais estreita e afiada
   glutSolidCube(1.0);
   glPopMatrix();

   glPopMatrix();
}

// Desenha a bolinha
void drawBall()
{
   glPushMatrix();
   glTranslatef(ballPosition[0], ballPosition[1], ballPosition[2]);
   glColor3f(1.0, 0.0, 0.0);
   glutSolidSphere(0.3f, 20, 20);
   glPopMatrix();
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   // Ajuste da câmera
   gluLookAt(0.0, 6.0, 20.0, // Posição da câmera
             0.0, 0.0, 0.0,  // Ponto para onde a câmera está olhando
             0.0, 1.0, 0.0); // Vetor "up"

   // Base fixa
   glPushMatrix();
   glRotatef(baseAngle, 0.0, 1.0, 0.0); // Rotação da base
   glColor3f(0.3, 0.3, 0.3);
   glPushMatrix();
   glScalef(5.0, 0.3, 5.0); // Formato da base
   glutSolidCube(1.0);
   glPopMatrix();

   // Articulação do Ombro
   glPushMatrix();
   glTranslatef(0.0, 0.3, 0.0);
   glRotatef(shoulderAngle, 0.0, 0.0, 1.0);
   glColor3f(0.5, 0.5, 0.5);
   glTranslatef(1.5, 0.0, 0.0);
   glPushMatrix();
   glScalef(4.0, 0.6, 0.6);
   glutSolidCube(1.0);
   glPopMatrix();

   // Articulação do Cotovelo
   glTranslatef(2.0, 0.0, 0.0);
   glRotatef(elbowAngle, 0.0, 0.0, 1.0);
   glColor3f(0.5, 0.5, 0.5);
   glTranslatef(2.0, 0.0, 0.0);
   glPushMatrix();
   glScalef(4.0, 0.6, 0.6);
   glutSolidCube(1.0);
   glPopMatrix();

   // Mão do robô
   glTranslatef(2.0, 0.0, 0.0);
   glRotatef(wristAngle, 0.0, 1.0, 0.0);
   glRotatef(wristRotationAngle, 1.0, 0.0, 0.0);
   glRotatef(wristRotationAngleZ, 0.0, 0.0, 1.0);
   glColor3f(0.7, 0.7, 0.7);
   glPushMatrix();
   glScalef(0.8, 0.8, 0.8);
   glutSolidCube(1.0);
   glPopMatrix();

   // Garras do robô (modificadas para parecerem mais afiadas)
   glPushMatrix();
   glTranslatef(0.4, 0.3, 0.0); // Ajuste para a posição correta
   drawClaw(0.0, 0.0, gripAngle);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.4, -0.3, 0.0); // Ajuste para a posição correta
   drawClaw(0.0, 0.0, -gripAngle);
   glPopMatrix();

   glPopMatrix(); // Finaliza o braço completo
   glPopMatrix(); // Finaliza a base

   // Bolinha já na mão
   if (holdingBall)
   {
      ballPosition[0] = 3.0f; // Ajuste para a posição exata da mão
      ballPosition[1] = 0.0f;
      ballPosition[2] = 0.0f;
   }
   drawBall();

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
   case 'b':
      baseAngle = fmod(baseAngle + 5.0f, 360.0f);
      break;
   case 'B':
      baseAngle = fmod(baseAngle - 5.0f + 360.0f, 360.0f);
      break;

   case 'w':                  // Aumenta o ângulo do pulso
      if (wristAngle < 90.0f) // Limita a rotação do pulso para que ele não ultrapasse a posição inicial
         wristAngle = wristAngle + 5.0f;
      break;
   case 'W':                   // Diminui o ângulo do pulso
      if (wristAngle > -90.0f) // Limita a rotação do pulso para que ele não ultrapasse a posição inicial
         wristAngle = wristAngle - 5.0f;
      break;
   case 'z':                  // Aumenta o ângulo do pulso
      if (wristRotationAngleZ < 90.0f) // Limita a rotação do pulso para que ele não ultrapasse a posição inicial
         wristRotationAngleZ = wristRotationAngleZ + 5.0f;
      break;
   case 'Z':                   // Diminui o ângulo do pulso
      if (wristRotationAngleZ > -90.0f) // Limita a rotação do pulso para que ele não ultrapasse a posição inicial
         wristRotationAngleZ = wristRotationAngleZ - 5.0f;
      break;
   case 't':
      wristRotationAngle = fmod(wristRotationAngle + 5.0f, 360.0f);
      break;
   case 'T':
      wristRotationAngle = fmod(wristRotationAngle - 5.0f + 360.0f, 360.0f);
      break;
   case 'h':
      armRotation = fmod(armRotation + 5.0f, 360.0f);
      break;
   case 'H':
      armRotation = fmod(armRotation - 5.0f + 360.0f, 360.0f);
      break;
   case 's':
      if (shoulderAngle < 160.0f)
         shoulderAngle += 5.0f;
      break;
   case 'S':
      if (shoulderAngle > 30.0f)
         shoulderAngle -= 5.0f;
      break;
   case 'e':
      if (elbowAngle < 135.0f)
         elbowAngle += 5.0f;
      break;
   case 'E':
      if (elbowAngle > -135.0f)
         elbowAngle -= 5.0f;
      break;
   case 'g': // Fechar as garras
      if (gripAngle < 45.0f)
         gripAngle += 5.0f;
      break;
   case 'G': // Abrir as garras
      if (gripAngle > -2.0f)
         gripAngle -= 5.0f;
      break;
   case 'p': // Pegar a bolinha
      if (!holdingBall && fabs(ballPosition[0] - 6.0f) < 0.5f && fabs(ballPosition[1] - 0.5f) < 0.5f)
      {
         holdingBall = true;
         ballPosition[0] = 6.5f;
         ballPosition[1] = 0.0f;
         ballPosition[2] = 0.0f;
      }
      break;
   case 27: // ESC para sair
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
   glutCreateWindow("Braço Robótico com Garras");

   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
