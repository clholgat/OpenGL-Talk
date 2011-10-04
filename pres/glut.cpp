//nescesary headers for everything
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


/*
 * The GLUT handles window abstraction, this is a basic example of what you need
 * to set up a window for rendering.
 */
 
//handler functions
void drawScene();
void handleMotion(int x, int y);
void handleMouse(int button, int state, int x, int y);
void handleMenu(int item);

//movement modes
typedef enum{
	TRANSLATE,
	ROTATE_X,
	ROTATE_Y,
	ROTATE_Z,
} Mode;

//global state variables
int mouseButton[3] = {0};
Mode currentMode = TRANSLATE;
double translate[3] = {0};
double rotate[3] = {0};
int mouseX;
int mouseY;

int main(int argc, char *argv[]){
	//Initialize the GLUT window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutCreateWindow("GLUT Window Title");
	
	//Register callbacks for different events
	glutDisplayFunc(drawScene);
	glutMotionFunc(handleMotion);
	glutMouseFunc(handleMouse);
	
	//Setup a simple menu with a handler
	glutCreateMenu(handleMenu);
	glutAddMenuEntry("Translate", 0);
	glutAddMenuEntry("Rotate X", 1);
	glutAddMenuEntry("Rotate Y", 2);
	glutAddMenuEntry("Rotate Z", 3);
	glutAddMenuEntry("Quit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	//Setup a perspective view of the scene
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1, 1, 40);
	
	//Focus the view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 5, 0, 0, -1, 0, 1, 0);
	
	//Smooth shading
	glShadeModel(GL_SMOOTH);
	
	//Reset depth buffer and allow for depth calculation
	glClearDepth(1);
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	
	//kick off GLUT window loop	
	glutMainLoop();
	return 1;
}

void drawScene(){
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(translate[0], translate[1], translate[2]);
	glRotatef(rotate[0], 1, 0, 0);
	glRotatef(rotate[1], 0, 1, 0);
	glRotatef(rotate[2], 0, 0, 1);
	
	glColor3f(1, 1, 0);
	glutWireCube(2);
	
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void handleMotion(int x, int y){
	//if the right mouse button isn't pressed don't do anything
	if(!mouseButton[0]){
		return;
	}
	
	//get the window size from Glut
	double xRachet = glutGet(GLUT_WINDOW_WIDTH)/10.0;
	double yRachet = glutGet(GLUT_WINDOW_HEIGHT)/10.0;
	
	//y is reversed so flip it
	y = glutGet(GLUT_WINDOW_HEIGHT)-y;
	
	switch(currentMode){
		case TRANSLATE:
			translate[0] += (double)(x-mouseX)/xRachet;
			translate[1] += (double)(y-mouseY)/yRachet;
			break;
		case ROTATE_X:
			yRachet = yRachet/10.0;
			rotate[0] -= (double)(y-mouseY)/yRachet;
			break;
		case ROTATE_Y:
			xRachet = xRachet/10.0;
			rotate[1] += (double)(x-mouseX)/xRachet;
			break;
		case ROTATE_Z:
			yRachet = yRachet/10.0;
			rotate[2] += (double)(y-mouseY)/yRachet;
			break;
		default:
			break;
	}
	
	//update mouse position
	mouseX = x;
	mouseY = y;
	
	//redraw with new state
	glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y){
	if(state == GLUT_DOWN){
		mouseButton[button] = 1;
	} else {
		mouseButton[button] = 0;
	}
	
	//update mouse position
	mouseX = x;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT)-y;
}

void handleMenu(int item){
	switch(item){
		case 0:
			currentMode = TRANSLATE;
			break;
		case 1:
			currentMode = ROTATE_X;
			break;
		case 2:
			currentMode = ROTATE_Y;
			break;
		case 3:
			currentMode = ROTATE_Z;
			break;
		default:
			exit(0);
	}
}

	
