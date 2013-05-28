#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#Variables
static int year = 0, day = 0, viewDistance = -10;
static float sunSize = 2,
						 mercurySize = 0.007,
						 venusSize = 0.017,
						 earthSize = 0.019,
						 marsSize = 0.01,
						 jupiterSize = 0.2,
						 saturnSize = 0.173,
						 uranusSize = 0.15,
						 neptuneSize = 0.14;
static int mercuryYear = 0,
					 venusYear = 0,
					 marsYear = 0,
					 jupiterYear = 0,
					 saturnYear = 0,
					 uranusYear = 0,
					 neptuneYear = 0;
//static float mercuryYear = 0.24, venusYear = 0.62, earthYear = 1, marthYear = 1.88, jupiterYear = 12, saturnYear = 29, uranusYear = 84, neptuneYear = 165;
static int mercuryYearStep = 1, venusYearStep = 1, earthYearStep = 1, marsYearStep = 2, jupiterYearStep = 4, saturnYearStep = 6, uranusYearStep = 10, neptuneYearStep = 15;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
   glShadeModel (GL_SMOOTH);
}

void drawPlanet(float year, float day, float translation, float planetSize, float r, float g, float b)
{
	glPushMatrix();
	glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
	glTranslatef (translation, 0.0, 0.0);
	glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
	glColor3f(r, g, b);
	glutSolidSphere(planetSize, 10, 8);    /* draw smaller planet */
	glPopMatrix();
}

void display(void)
{
   glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   
   glPushMatrix();
   glTranslatef(0, 0, -10);
   glPushMatrix();
   glColor3f (1, 1, 0);
   //glutSolidSphere(1.0, 20, 16);   /* draw sun */
   glutSolidSphere(sunSize, 20, 16);   /* draw sun */
   glPopMatrix();
   
   //Sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune;
   drawPlanet(mercuryYear, day, 3, mercurySize, 0, 1, 1);
   drawPlanet(venusYear, day, 4, venusSize, 1, 1, 1);
   drawPlanet(year, day, 5, earthSize, 0, 0, 1);
   drawPlanet(marsYear, day, 6, marsSize, 1, 0, 0);
   drawPlanet(jupiterYear, day, 7, jupiterSize, 0, 1, 1);
   drawPlanet(saturnYear, day, 8, saturnSize, 0, 1, 1);
   drawPlanet(uranusYear, day, 9, uranusSize, 0, 0.8, 1);
   drawPlanet(neptuneYear, day, 10, neptuneSize, 0, 0, 0.8);
   glPopMatrix();
   
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'd':
         day = (day + 10) % 360;
         glutPostRedisplay();
         break;
      case 'D':
         day = (day - 10) % 360;
         glutPostRedisplay();
         break;
      case 'y':
         //year = (year + 5) % 360;
         //Sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune;
         mercuryYear = (mercuryYear + mercuryYearStep) % 360;
         venusYear = (venusYear + venusYearStep) % 360;
         year = (year + earthYearStep) % 360;
         marsYear = (marsYear + marsYearStep) % 360;
         jupiterYear = (jupiterYear + jupiterYearStep) % 360;
         saturnYear = (saturnYear + saturnYearStep) % 360;
         uranusYear = (uranusYear + uranusYearStep) % 360;
         neptuneYear = (neptuneYear + neptuneYearStep) % 360;
         glutPostRedisplay();
         break;
      case 'Y':
         //year = (year - 5) % 360;
         glutPostRedisplay();
         mercuryYear = (mercuryYear - mercuryYearStep) % 360;
         venusYear = (venusYear - venusYearStep) % 360;
         year = (year - earthYearStep) % 360;
         marsYear = (marsYear - marsYearStep) % 360;
         jupiterYear = (jupiterYear - jupiterYearStep) % 360;
         saturnYear = (saturnYear - saturnYearStep) % 360;
         uranusYear = (uranusYear - uranusYearStep) % 360;
         neptuneYear = (neptuneYear - neptuneYearStep) % 360;
         break;
      case 'v':
			   viewDistance -= 1;
				 break;
	  case 'V':
				 break;
    default:
         break;
   }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return EXIT_SUCCESS;
}
