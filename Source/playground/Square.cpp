#include <GL/glew.h>
#include "Square.h"

CSquare::CSquare(void)
{
	miVertCount = 12;
}


CSquare::~CSquare(void)
{
}

void CSquare::Draw()
{	
	static GLfloat g_vertex_buffer_data[12] = {0};
		
	g_vertex_buffer_data[0] = mvecPosition.x + (-1.0f * mfSize);
	g_vertex_buffer_data[1] = mvecPosition.y + (-1.0f * mfSize);
	g_vertex_buffer_data[2] = 0.0f;
	g_vertex_buffer_data[3] = mvecPosition.x + (1.0f * mfSize);
	g_vertex_buffer_data[4] = mvecPosition.y + (-1.0f * mfSize);
	g_vertex_buffer_data[5] = 0.0f;
	g_vertex_buffer_data[6] = mvecPosition.x + (1.0f * mfSize);
	g_vertex_buffer_data[7] = mvecPosition.y + (1.0f * mfSize);
	g_vertex_buffer_data[8] = 0.0f ;
	g_vertex_buffer_data[9] = mvecPosition.x + (-1.0f * mfSize);
	g_vertex_buffer_data[10] = mvecPosition.y + (1.0f * mfSize);
	g_vertex_buffer_data[11] = 0.0f;

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLE_FAN, 0, miVertCount);
}