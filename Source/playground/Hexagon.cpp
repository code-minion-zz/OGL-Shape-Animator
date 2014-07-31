#include <GL/glew.h>
#include "Hexagon.h"


CHexagon::CHexagon(void)
{
	miVertCount = 18;
}


CHexagon::~CHexagon(void)
{
}

void CHexagon::Draw()
{
	static GLfloat g_vertex_buffer_data[18] = {0};
	float fAngleInc = (6.28318530718f / static_cast<float>(miVertCount));
 
	for(int i = 0; i < miVertCount; i+=3)
	{
		float fAngle = fAngleInc * i;
  
		g_vertex_buffer_data[i] = mvecPosition.x + (cos(fAngle) * mfSize);
		g_vertex_buffer_data[i+1] = mvecPosition.y + (sin(fAngle) * mfSize);
		g_vertex_buffer_data[i+2] = 0;
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLE_FAN, 0, miVertCount);
}