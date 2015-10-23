// Draw an Icosahedron
// ECE6122 Project 4: OpenGL
// Neha Kadam

#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h> 
#include <time.h>
#include <map>

using namespace std;

#define NFACE 20
#define NVERTEX 12

#define X .525731112119133606 
#define Z .850650808352039932

/* Function Declarations */
void drawTriangle(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3]);
void normalize(GLfloat v[3]);
void sub_divide(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int depth);
void timer();

// These are the 12 vertices for the icosahedron
static GLfloat vdata[NVERTEX][3] = {    
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
};

// These are the 20 faces.  Each of the three entries for each 
// vertex gives the 3 vertices that make the face.
static GLint tindices[NFACE][3] = { 
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
   {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

int testNumber; // Global variable indicating which test number is desired
int g_depth; //global depth
int updateRate;
float r1, r2, r3; // for random colors

//static int first = 1; //to indicate whether current execution is the first time
//static GLuint dispList = 1;

// Test cases.  Fill in your code for each test case
void Test1()
{  
  
  int i;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  
  // set viewing transformation
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 10.0, 0.0);
  glTranslatef(250, 250, 0);
  glScalef(150.0, 150.0, 150.0);
 
  //if(first) glNewList(dispList, GL_COMPILE);
  
  //now draw triangles
  for(i = 0; i < NFACE; i++)
  {
	srand(i * 300);		
	sub_divide(&vdata[tindices[i][0]][0],
			&vdata[tindices[i][1]][0],
			&vdata[tindices[i][2]][0],
			g_depth);
  }
  //glEndList();
  //first = 0;
  //glCallList(dispList);

  // Flush buffer
  //glFlush(); //if single buffering in Display Mode
  glutSwapBuffers();


}

void Test2()
{

  int i;
  //glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glPushMatrix();
  glLoadIdentity();
  glPushMatrix();
  
  // set viewing transformation
  gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  
  glTranslatef(250.0, 250.0, 0); 
  glScalef(150.0, 150.0, 150.0);
  
  // rotation
  static GLfloat rotX = 0.0;
  static GLfloat rotY = 0.0;
  static GLfloat rotZ = 0.0;
  
  glRotatef(rotX, 1.0, 0.0, 0.0);
  glRotatef(rotY, 0.0, 1.0, 0.0);
  glRotatef(rotZ, 0.0, 0.0, 1.0);

  rotX += 1.0;
  rotY += 1.0;
  rotZ += 1.0;
  
  //if(first) glNewList(dispList, GL_COMPILE);

  // Now draw the triangles 
  for(i = 0; i < NFACE; i++)
  {
	srand(i * 200);
	sub_divide(&vdata[tindices[i][0]][0],
			&vdata[tindices[i][1]][0],
			&vdata[tindices[i][2]][0],
			g_depth);

  }

  //glEndList();
  //first = 0;
  //glCallList(dispList);
  glPopMatrix();
  
  // Flush buffer
  //glFlush(); //if single buffering in Display Mode
  glutSwapBuffers();
}

void Test3()
{

  int i;
  g_depth = 1;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  // set viewing transformation
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 10.0, 0.0);
  glTranslatef(250, 250, 0);
  glScalef(150.0, 150.0, 150.0);

  //if(first) glNewList(dispList, GL_COMPILE);
  //now draw triangles
  for(i = 0; i < NFACE; i++)
  {
	srand(i * 300);
	sub_divide(&vdata[tindices[i][0]][0],
			&vdata[tindices[i][1]][0],
			&vdata[tindices[i][2]][0],
			g_depth);
  }
  //glEndList();
  //first = 0;
  //glCallList(dispList);

  // Flush buffer
  //glFlush(); //if single buffering in Display Mode
  glutSwapBuffers();

}

void Test4()
{

  int i;
  //glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glPushMatrix();
  glLoadIdentity();
  glPushMatrix();
  
  // set viewing transformation
  gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  
  glTranslatef(250.0, 250.0, 0); 
  glScalef(150.0, 150.0, 150.0);
  
  // rotation
  static GLfloat rotX = 0.0;
  static GLfloat rotY = 0.0;
  static GLfloat rotZ = 0.0;
  
  glRotatef(rotX, 1.0, 0.0, 0.0);
  glRotatef(rotY, 0.0, 1.0, 0.0);
  glRotatef(rotZ, 0.0, 0.0, 1.0);

  rotX += 1.0;
  rotY += 1.0;
  rotZ += 1.0;
  
  //if(first) glNewList(dispList, GL_COMPILE);
  g_depth = 1;
  // Now draw the triangles 
  for(i = 0; i < NFACE; i++)
  {
	srand(i * 350);
	sub_divide(&vdata[tindices[i][0]][0],
			&vdata[tindices[i][1]][0],
			&vdata[tindices[i][2]][0],
			g_depth);

  }

  //glEndList();
  //first = 0;
  //glCallList(dispList);
  glPopMatrix();
  //glFlush(); //if single buffering in Display Mode
  glutSwapBuffers();

}

void Test5(void)
{

  Test1();

}

void Test6(void)
{
  Test2();
}

void drawTriangle(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3])
{

  glBegin(GL_TRIANGLES);
  
  //glColor3f(0.0, 0.0 , 1.0); // blue triangles

  //randomizing colors
  r1 = rand() /((float)RAND_MAX + 1);
  r2 = rand() /((float)RAND_MAX + 1);
  r3 = rand() /((float)RAND_MAX + 1);
   
  glColor3f(r1, r2, r3); // random colors

  glNormal3fv(v1);
  glVertex3fv(v1);

  glNormal3fv(v2);
  glVertex3fv(v2);

  glNormal3fv(v3);
  glVertex3fv(v3);
  glEnd();

  // Now draw triangle edges
  glBegin(GL_LINE_LOOP);
 
  glColor3f(1.0, 1.0, 1.0); // white edges
  glVertex3fv(v1);
  glVertex3fv(v2);
  glVertex3fv(v3);

  glEnd();

}

void normalize(GLfloat v[3])
{
  GLfloat m = sqrt(v[0] * v[0] + v[1]*v[1] + v[2]*v[2]);
  v[0] = v[0] / m;
  v[1] = v[1] / m;
  v[2] = v[2] / m;
}

void sub_divide(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int depth)
{

  if (depth == 0)
  {
	drawTriangle(v1, v2, v3);
	return;
  }	

  // to subdivide calculate midpoints
  GLfloat v12[3], v23[3], v31[3];
  int i;
  for(i = 0; i < 3; i++)
  {
	v12[i] = 0.5 * (v1[i] + v2[i]);
	v23[i] = 0.5 * (v2[i] + v3[i]);
	v31[i] = 0.5 * (v3[i] + v1[i]);
  }

  //now normalize the midpoints
  normalize(v12);
  normalize(v23);
  normalize(v31);
  
  //now recurse till depth 0
  sub_divide(v1, v12, v31, (depth-1));
  sub_divide(v2, v23, v12, (depth-1));
  sub_divide(v3, v31, v23, (depth-1));
  sub_divide(v12, v23, v31, (depth-1));
}

void display(void)
{

  int i;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glLoadIdentity();
  glPushMatrix();
  
  // set viewing transformation
  gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  
  //translation
  static GLfloat transX = 100.0;
  static GLfloat transY = 100.0;
  static GLfloat transZ = 100.0;
  static bool    adding = true;
  glTranslatef(transX, transY, transZ);
  //glTranslatef(transX, transY, 0.0);
  if (adding)
    {
      transX += 3.0;
      transY += 3.0;
      transZ += 3.0;
      if (transX > 400) adding = false;
    }
  else
    {
      transX -= 3.0;
      transY -= 3.0;
      transZ -= 3.0;
      if (transX < 0.0) adding = true;
    }

  
  //glTranslatef(250.0, 250.0, 0); 
  glScalef(150.0, 150.0, 150.0);
  
  // rotation
  static GLfloat rotX = 0.0;
  static GLfloat rotY = 0.0;
  static GLfloat rotZ = 0.0;
  glRotatef(rotX, 1.0, 0.0, 0.0);
  glRotatef(rotY, 0.0, 1.0, 0.0);
  glRotatef(rotZ, 0.0, 0.0, 1.0);

  rotX += 1.0;
  rotY += 1.0;
  rotZ += 1.0;
  
  //if(first) glNewList(dispList, GL_COMPILE);
  
  //now draw the triangles 
  for(i = 0; i < NFACE; i++)
  {
	srand(i * 100);
	sub_divide(&vdata[tindices[i][0]][0],
			&vdata[tindices[i][1]][0],
			&vdata[tindices[i][2]][0],
			g_depth);

  }

  //glEndList();
  //first = 0;
  //glCallList(dispList);
  glPopMatrix();

  //glFlush(); //if single buffering in Display Mode
  glutSwapBuffers();

}

void timer(int)
{

  glutPostRedisplay();
  glutTimerFunc(1000.0/updateRate, timer, 0);
}


void reshape(int w, int h)
{

  glViewport(0,0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, (GLdouble)w, (GLdouble)0.0, h, (GLdouble)-w, (GLdouble)w);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();


}

void init()
{
  glShadeModel(GL_FLAT);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_LINE_SMOOTH);

}	

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      std::cout << "Usage: icosahedron testnumber" << endl;
      exit(1);
    }

  // Set the global test number
  testNumber = atol(argv[1]);
  
  // Initialize glut  and create your window here
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Icosahedron");
  init();
  
  if( argc > 2) 
  {
	g_depth = atol(argv[2]);
	if(g_depth > 5) 
	{
		cout << "Enter depth less than 6\n";
		exit(1);
		//g_depth = 3; // do not allow depth > 5
	}
  }
  else
	g_depth = 0;
 
  // Set your glut callbacks here
  
  switch (testNumber)
  {
    case 1:
  	g_depth = 0;
  	glutDisplayFunc(Test1);
  	break;

    case 2:
  	g_depth = 0;
  	glutDisplayFunc(Test2);
  	break;

    case 3:
	g_depth = 1;
	glutDisplayFunc(Test3);
	break;

    case 4:
  	g_depth = 1;
  	glutDisplayFunc(Test4);
  	break;


    case 5:
	if(argc < 3)
	{
		std::cout << "Usage: icosahedron 5 <depth>" << endl;
		exit(1);
 
	}
	
	g_depth = atol(argv[2]);
	glutDisplayFunc(Test5);
	break;
 
    case 6:
	if(argc < 3)
	{
		std::cout << "Usage: icosahedron 6 <depth>" << endl;
		exit(1);
 
	}
	
	g_depth = atol(argv[2]);
	glutDisplayFunc(Test6);
	break;
 
  
    default:
  	if(argc > 2) g_depth = atoi(argv[2]); 
	else g_depth = 2;
  	glutDisplayFunc(display);
	break;
  }

  glutReshapeFunc(reshape);
  updateRate = 10;
  glutTimerFunc(1000.0/ updateRate, timer, 0);
  
  // Enter the glut main loop here
  glutMainLoop();
  return 0;

}

