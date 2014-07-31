
#include <GL/glew.h>
#include "Shape.h"
#include <math.h>

CShape::CShape(void)
{
	miVertCount = 0;
}


CShape::~CShape(void)
{
}

void CShape::Initialize(ColorType _color, float _size, MovementType _movement, float _speed)
{
	switch (_color)
	{
	case Red:
		{
			mvecColor = glm::vec3(0.4,0,0);
		}
		break;
	case Blue:
		{
			mvecColor = glm::vec3(0,0,0.4);
		}
		break;
	case Green:
		{
			mvecColor = glm::vec3(0,0.4,0);
		}
		break;
	case Yellow:
		{
			mvecColor = glm::vec3(0.4,0.4,0);
		}
		break;
	default:
		break;
	}

	mfSize = _size;
	mMovementType = _movement;
	mfSpeed = _speed;
	mvecPosition.x = 0;
	mvecPosition.y = 0;
	mfAnimationPosition = 0;
}

void CShape::ApplyColor()
{
	static GLfloat g_color_buffer_data[120] = {0};
	for (int i = 0; i < miVertCount; i+=3)
	{
		g_color_buffer_data[i] = mvecColor.x;
		g_color_buffer_data[i+1] = mvecColor.y;
		g_color_buffer_data[i+2] = mvecColor.z;
	}
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_DYNAMIC_DRAW);
}

// alters Position based on movementType, speed and deltaTime
void CShape::Animate(float _deltaTime)
{
	mfAnimationPosition += _deltaTime * mfSpeed;
	
	if (mfAnimationPosition > 1)
	{
		while (mfAnimationPosition > 1)	mfAnimationPosition -= 1;
		mbReverse = !mbReverse;
	}

	// it makes sense for animation to be it's own class, but I had to cut that in order to save time
	switch (mMovementType)
	{
	case Vertical:
		{
			if (!mbReverse)	mvecPosition.y = mfAnimationPosition;
			else mvecPosition.y = 1 - mfAnimationPosition;
			mvecPosition.y -= 0.5f;
		}
		break;
	case Horizontal:
		{
			if (!mbReverse)	mvecPosition.x = mfAnimationPosition;
			else mvecPosition.x = 1 - mfAnimationPosition;
			mvecPosition.x -= 0.5f;
		}
		break;
	case Circular:
		{
			float fAngle = mfAnimationPosition * 6.28318530718f;
			mvecPosition.x = cos(fAngle) * mfSize * 0.5f; // distance from origin is half the size of the object
			mvecPosition.y = sin(fAngle) * mfSize * 0.5f; // distance from origin is half the size of the object
		}
		break;
	case Box:
		{
			float fAdjustedPosition = 0;
			if (mfAnimationPosition < 0.5f)
			{
				if (mfAnimationPosition < 0.25f)
				{
					fAdjustedPosition = mfAnimationPosition * 4;
					mvecPosition.x = (((1-fAdjustedPosition) * BoxVerts[0] + fAdjustedPosition * BoxVerts[2]) * mfSize * 0.5f);
					mvecPosition.y = (((1-fAdjustedPosition) * BoxVerts[1] + fAdjustedPosition * BoxVerts[3]) * mfSize * 0.5f);
				}
				else
				{
					fAdjustedPosition = (mfAnimationPosition - 0.25f) * 4;
					mvecPosition.x = (((1-fAdjustedPosition) * BoxVerts[2] + fAdjustedPosition * BoxVerts[4]) * mfSize * 0.5f);
					mvecPosition.y = (((1-fAdjustedPosition) * BoxVerts[3] + fAdjustedPosition * BoxVerts[5]) * mfSize * 0.5f);
				}
			}
			else
			{
				if (mfAnimationPosition < 0.75f)
				{
					fAdjustedPosition = (mfAnimationPosition - 0.5f) * 4;					
					mvecPosition.x = (((1-fAdjustedPosition) * BoxVerts[4] + fAdjustedPosition * BoxVerts[6]) * mfSize * 0.5f);
					mvecPosition.y = (((1-fAdjustedPosition) * BoxVerts[5] + fAdjustedPosition * BoxVerts[7]) * mfSize * 0.5f);
				}
				else
				{
					fAdjustedPosition = (mfAnimationPosition - 0.75f) * 4;					
					mvecPosition.x = (((1-fAdjustedPosition) * BoxVerts[6] + fAdjustedPosition * BoxVerts[0]) * mfSize * 0.5f);
					mvecPosition.y = (((1-fAdjustedPosition) * BoxVerts[7] + fAdjustedPosition * BoxVerts[1]) * mfSize * 0.5f);
				}
			}
		}
		break;
	default:
		{
			// do nothing
		}
		break;
	}
}