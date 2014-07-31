#include <GL/glew.h>
#include "Circle.h"


CCircle::CCircle(void)
{
	miVertCount = 96;
}


CCircle::~CCircle(void)
{
}

void CCircle::Draw()
{
	static GLfloat g_vertex_buffer_data[96];
	float fAngleInc = (6.28318530718f / static_cast<float>(miVertCount));
 
	for(int i = 0; i < miVertCount; i+=3)
	{
		float fAngle = fAngleInc * i;
  
		g_vertex_buffer_data[i] = mvecPosition.x + (cos(fAngle) * mfSize);
		g_vertex_buffer_data[i+1] = mvecPosition.y + (sin(fAngle) * mfSize);
		g_vertex_buffer_data[i+2] = 0;
		//printf ("%f %f\n",g_vertex_buffer_data[i],g_vertex_buffer_data[i+1]);
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLE_FAN, 0, miVertCount);
}
