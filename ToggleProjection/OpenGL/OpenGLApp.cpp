#include "OpenGLApp.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cmath>
#include "OpenGLApp.h"

OpenGLApp::OpenGLApp()
{
}


OpenGLApp::~OpenGLApp()
{
}


bool OpenGLApp::Initialize() // initialize your opengl scene
{
	//clear and change background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	xPos = 0.0f;
	yPos = 0.0f;
	zPos = -5.0f;
	xAxisAngle = 0.0f;
	yAxisAngle = 0.0f;
	zAxisAngle = 0.0f;

	return true;
} 

bool OpenGLApp::Shutdown() // shut down your scene
{
	return true;
}  

// used to setup your opengl camera and drawing area
void OpenGLApp::SetupProjection(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// you need 3 things to create a frustum
	// 1. Field of view (52.0f here)
	// 2. aspect ratio of screen (width/height of window)
	// 3. near and far plane (1, and 1000)
	gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_windowWidth = width;
	m_windowHeight = height;
}

void OpenGLApp::UpdateProjection(bool toggle)
{
	static bool usePerspective = true;

	//if the function has been passed true
	if (toggle)
		usePerspective != usePerspective; //then flip the bool value

	//select the projection matrix and clear it out
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//choose the apporpriate projection based on the current
	//toggle mode
	if (usePerspective)
		//use perspective projection
		glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 1000.0);
	else
		//set up orthrographic projection
		glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 1000.0);

	//set matrix mode back to modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void OpenGLApp::Prepare(float dt)
{
	//xAxisAngle += 0.05f;
	//yAxisAngle += 0.05f;
	//zAxisAngle += 0.05f;

}

void OpenGLApp::PositionAndRotate(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle)
{
	glTranslatef(xPos, yPos, zPos);

	//rotate z last
	glRotatef(xAxisAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(yAxisAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(zAxisAngle, 0.0f, 0.0f, 1.0f);

	
}


void OpenGLApp::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

	glEnable(GL_DEPTH_TEST);

	//do the translation and rotation of the current model view
	glTranslatef(0.4f, 0.0f, -1.5f);
	glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
	glScalef(0.75f, 0.75f, 0.75f);
	
	DrawCube();

	glEnd();
}

void OpenGLApp::DrawCube()
{
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);	// top face
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);	// front face
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);	// right face
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);	// left face
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(0.5f, 1.0f, 0.5f);
	glVertex3f(0.0f, -1.0f, 0.0f);	// bottom face
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);	// back face
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glEnd();

}

void OpenGLApp::ShowGrid()
{
	glPointSize(3.0f); //change the size of points drawn 

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f); //blue

	//draw vertical lines
	for (int x = -6; x <= 6; x++)
	{
		glVertex3f(x, 4.0f, 0.0f); //start of line (0, 4, 0)
		glVertex3f(x, -4.0f, 0.0f); //end of line  (0, -4, 0)
	}

	//draw horizontal lines
	for (int y = -4; y <= 4; y++)
	{
		glVertex3f(-6.0f, y, 0.0f); //start of line (, 4, 0)
		glVertex3f(6.0f, y, 0.0f); //end of line  (0, -4, 0)
	}
	glEnd();



	//draw points on grid
	glBegin(GL_POINTS);
	//X AXIS
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-6.0f, 0.0f, 0.0f);
	glVertex3f(-5.0f, 0.0f, 0.0f);
	glVertex3f(-4.0f, 0.0f, 0.0f);
	glVertex3f(-3.0f, 0.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); //origin
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glVertex3f(4.0f, 0.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(6.0f, 0.0f, 0.0f);

	//Y Axis
	glVertex3f(0.0f, -4.0f, 0.0f);
	glVertex3f(0.0f, -3.0f, 0.0f);
	glVertex3f(0.0f, -2.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glVertex3f(0.0f, 4.0f, 0.0f);

	glEnd();


}

void OpenGLApp::IncrementXAxis(float value)
{
	xAxisAngle += value;
	if (xAxisAngle >= 360.0f)
		xAxisAngle = 0.0f;
}

void OpenGLApp::IncrementYAxis(float value)
{
	yAxisAngle += value;
	if (yAxisAngle >= 360.0f)
		yAxisAngle = 0.0f;
}

void OpenGLApp::IncrementZAxis(float value)
{
	zAxisAngle += value;
	if (zAxisAngle >= 360.0f)
		zAxisAngle = 0.0f;
}
