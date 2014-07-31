#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include <vld.h>

#include <glfw3.h>
GLFWwindow* window;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common\iniparser.hpp>
#include <common\shader.hpp>
#include "Shape.h"
#include "Square.h"
#include "Circle.h"
#include "Triangle.h"
#include "Hexagon.h"

void PrepareColorBuffer(GLuint colorbuffer);
void PrepareVertexBuffer(GLuint vertexbuffer);
//void FillCircleVerts(float radius);
//void FillHexagonVerts(float size);
//void FillTriangleVerts(float size);
//void FillSquareVerts(float size);

// Define the vertices to draw
//GLfloat g_vertex_buffer_data[240];
//int vertcount = 0;

double lastTime = 0;
bool loadedINIrecently = false;
float loadINIdelay = 0.f;

CShape* currentShape;

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Playground", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Needed for core profile
	glewExperimental = true;
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Background clear color
	//glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	
	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	currentShape = new CSquare();
	currentShape->Initialize(Red,.8f, Circular, 0.6f);
	// Buffer identifier
	GLuint vertexbuffer;
	GLuint colorbuffer;
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &colorbuffer);

	// Send our vertices to GL
	do{		
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		
		// only check keypress once per second
		if (loadedINIrecently)
		{
			loadINIdelay += deltaTime;
			if (loadINIdelay > 1.0f)
			{
				loadINIdelay = 0.0f;
				loadedINIrecently = false;
			}
		}
		// check for keypress to load in INI
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			if (!loadedINIrecently)
			{
				loadedINIrecently = true;
				ShapeType shapeType = Square;
				float fSize=0, fSpeed=0;
				ColorType colorType = Red;
				MovementType movementType = None;
				// parse shape.ini, get a new shape
				bool success = loadINI("shape.ini", shapeType, fSize, colorType, movementType, fSpeed);
				
				if (!success)
				{
					// shape ini unreadable!
					printf("Shape Config Unreadable! Abort! Abort!");
				}
				else
				{
					printf("%d %f %d %d %f\n", shapeType, fSize, colorType, movementType, fSpeed);
					delete currentShape;

					switch (shapeType)
					{
					case Square:
						currentShape = new CSquare();
						break;
					case Triangle:
						currentShape = new CTriangle();
						break;
					case Circle:
						currentShape = new CCircle();
						break;
					case Hexagon:
						currentShape = new CHexagon();
						break;
					}

					currentShape->Initialize(colorType, fSize, movementType, fSpeed);
				}
			}
		}

		// Draw our shape
		if (currentShape != 0)
		{	
			PrepareColorBuffer(colorbuffer);
			currentShape->ApplyColor();
			currentShape->Animate(deltaTime);
			PrepareVertexBuffer(vertexbuffer);
			currentShape->Draw();
		}

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		
		lastTime = currentTime;
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	delete currentShape;

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}

void PrepareVertexBuffer(GLuint vertexbuffer)
{
	// 1rst attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);
}

void PrepareColorBuffer(GLuint colorbuffer)
{
	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
}

// Below this line are all prototype functions i made just to learn GL
// I would later replace them with classes

//void FillCircleVerts(float radius)
//{
//	vertcount = 0;
//	int verts = 32;
//	float fAngleInc = (6.28318530718f / static_cast<float>(verts));
// 
//	for(int i = 0; i < verts; ++i)
//	{
//		float fAngle = fAngleInc * i;
//  
//		g_vertex_buffer_data[vertcount++] = cos(fAngle) * radius;
//		printf("%f",g_vertex_buffer_data[(vertcount-1)]);
//		g_vertex_buffer_data[vertcount++] = sin(fAngle) * radius;
//		printf("%f",g_vertex_buffer_data[(vertcount-1)]);
//		g_vertex_buffer_data[vertcount++] = 0;
//	}
//}
//
//void FillHexagonVerts(float size)
//{
//	vertcount = 0;
//	int verts = 6;
//	float fAngleInc = (6.28318530718f / static_cast<float>(verts));
// 
//	for(int i = 0; i < verts; ++i)
//	{
//		float fAngle = fAngleInc * i;
//  
//		g_vertex_buffer_data[vertcount++] = cos(fAngle) * size;
//		printf("%f",g_vertex_buffer_data[(vertcount-1)]);
//		g_vertex_buffer_data[vertcount++] = sin(fAngle) * size;
//		printf("%f",g_vertex_buffer_data[(vertcount-1)]);
//		g_vertex_buffer_data[vertcount++] = 0;
//	}
//}
//
//void FillTriangleVerts(float size)
//{
//	g_vertex_buffer_data[0] = -1.0f * size;
//	g_vertex_buffer_data[1] = -1.0f * size;
//	g_vertex_buffer_data[2] = 0.0f * size;
//	g_vertex_buffer_data[3] = 1.0f * size;
//	g_vertex_buffer_data[4] = -1.0f * size;
//	g_vertex_buffer_data[5] = 0.0f * size;
//	g_vertex_buffer_data[6] = 0.0f * size;
//	g_vertex_buffer_data[7] = 1.0f * size;
//	g_vertex_buffer_data[8] = 1.0f * size;
//	vertcount = 9;
//}
//
//void FillSquareVerts(float size)
//{
//	g_vertex_buffer_data[0] = -1.0f * size;
//	g_vertex_buffer_data[1] = -1.0f * size;
//	g_vertex_buffer_data[2] = 0.0f * size;
//	g_vertex_buffer_data[3] = 1.0f * size;
//	g_vertex_buffer_data[4] = -1.0f * size;
//	g_vertex_buffer_data[5] = 0.0f * size;
//	g_vertex_buffer_data[6] = 1.0f * size;
//	g_vertex_buffer_data[7] = 1.0f * size;
//	g_vertex_buffer_data[8] = 0.0f * size;
//	g_vertex_buffer_data[9] = -1.0f * size;
//	g_vertex_buffer_data[10] = 1.0f * size;
//	g_vertex_buffer_data[11] = 0.0f * size;
//	vertcount = 12;
//}
