#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include "RgbImage.h"

GLuint *textures;
int xRot;
int yRot;
int zRot;
float xMove;
float yMove;
float zMove;
float zoom;


double xLastClick, yLastClick;
double xCurrentPos, yCurrentPos;
double xDifPos, yDifPos;

int mouseButton;

int window_width, window_height;




void initialization();


/*
* Read a texture map from a BMP bitmap file.
*/
void loadTextureFromFile()
{   
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   RgbImage theTexMap[6] = { "./cho1.bmp", "./cho2.bmp", "./cho3.bmp", "./cho4.bmp", "./cho5.bmp", "./cho6.bmp" };
   // Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
   //    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );

	// Typical Texture Generation Using Data From The Bitmap
	textures = new GLuint[6];
	glGenTextures(6, textures);

	for (int i = 0; i < 6; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap[i].GetNumCols(), theTexMap[i].GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap[i].ImageData());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	}

}

/*
* Draw the texture in the OpenGL graphics window
*/
float xLen=5.93;
float yLen=3.59;
float zLen=2.26;


void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glBindTexture(GL_TEXTURE_2D, texture1);
  
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap2.GetNumCols(), theTexMap2.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap2.ImageData());

	glLoadIdentity();
	glTranslatef(0.0,0.0,-20);
	//glTranslatef(xMove, yMove, zMove);
	glRotatef(xRot, 1.0, 0.0, 0.0);
	glRotatef(yRot, 0.0, 1.0, 0.0);
	// glRotatef(zRot, 0.0, 0.0, 1.0);
	glScalef(zoom, zoom, zoom);
		
   // Front Face
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glEnable(GL_TEXTURE_2D);	
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-xLen, -yLen, zLen);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(xLen, -yLen, zLen);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(xLen, yLen, zLen);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-xLen, yLen, zLen);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// Back Face
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-xLen, -yLen, -zLen);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-xLen, yLen, -zLen);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xLen, yLen, -zLen);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xLen, -yLen, -zLen);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	// Top Face
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(xLen, -yLen, -zLen);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(xLen, yLen, -zLen);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xLen, yLen, zLen);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xLen, -yLen, zLen);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	// Bottom Face
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-xLen, -yLen, -zLen);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-xLen, -yLen, zLen);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-xLen, yLen, zLen);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-xLen, yLen, -zLen);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// Right face
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-xLen, yLen, -zLen);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-xLen, yLen, zLen);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(xLen, yLen, zLen);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(xLen, yLen, -zLen);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	// Left Face
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-xLen, -yLen, -zLen);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xLen, -yLen, -zLen);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xLen, -yLen, zLen);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-xLen, -yLen, zLen);
	glEnd();
	glDisable(GL_TEXTURE_2D);

   glFlush();
  
  
}

void resizeWindow(int x, int y)
{
 if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
     
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,30.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'r': //reset rotation and zoom
		  initialization();
         break;
      default:
         break;
   }
}

void mouse(int button, int state, int x, int y)
{
	//double xNew = (double)x / (double)window_width;
	//double yNew = 1.0 - (double)y / (double)window_height;


	if (state == GLUT_DOWN)
	{
		mouseButton = button; //remember which right or left click done
		xLastClick = x;
		yLastClick = y;
	}
	else if (state == GLUT_UP)
	{
		mouseButton = -1;//remember if mouse drag is done
	}


}
void mousemove(int x, int y)
{
	xCurrentPos = x;
	yCurrentPos = y;

	xDifPos = xCurrentPos - xLastClick;
	yDifPos = yCurrentPos - yLastClick;

	if (mouseButton == GLUT_LEFT_BUTTON) 
	{
		//rotation
		xRot += yDifPos;
		yRot += xDifPos;

		if (xRot >= 360) xRot = 0;
		else if (xRot <= -360) xRot = 0;

		if (yRot >= 360) yRot = 0;
		else if (yRot <= -360) yRot = 0;

		//printf("rot  %d,%d \n", xRot, yRot);
	}
	else if (mouseButton == GLUT_RIGHT_BUTTON)
	{
		//zoom

		zoom += (yDifPos*0.01);

		//printf("zoom  %.2f \n", zoom);
	}
	xLastClick = xCurrentPos;
	yLastClick = yCurrentPos;
}

void idleFunc(void)
{
    drawScene();
}

void initialization()
{
	xRot = 30;
	yRot = 30;
	zRot = 0;

	xMove = 0;
	yMove = 0;
	zMove = 0;

	zoom = 1.0;

}

int main(int argc, char** argv)
{
	window_width = 300;
	window_height = 300;

	initialization();



   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(window_width, window_height);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);

   loadTextureFromFile( );
   
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resizeWindow);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutMotionFunc(mousemove);
   glutIdleFunc(idleFunc);
   glutMainLoop();
   return 0;
}
