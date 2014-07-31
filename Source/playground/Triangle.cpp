#include <GL/glew.h>
#include "Triangle.h"


CTriangle::CTriangle(void)
{
	miVertCount = 9;
}


CTriangle::~CTriangle(void)
{
}

void CTriangle::Draw()
{	
	static GLfloat g_vertex_buffer_data[9];
		
	g_vertex_buffer_data[0] = mvecPosition.x + (-1.0f * mfSize);
	g_vertex_buffer_data[1] = mvecPosition.y + (-1.0f * mfSize);
	g_vertex_buffer_data[2] = 0.0f;
	g_vertex_buffer_data[3] = mvecPosition.x + (1.0f * mfSize);
	g_vertex_buffer_data[4] = mvecPosition.y + (-1.0f * mfSize);
	g_vertex_buffer_data[5] = 0.0f;
	g_vertex_buffer_data[6] = mvecPosition.x + (1.0f * mfSize);
	g_vertex_buffer_data[7] = mvecPosition.y + (1.0f * mfSize);
	g_vertex_buffer_data[8] = 0.0f ;

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLE_FAN, 0, miVertCount);
}