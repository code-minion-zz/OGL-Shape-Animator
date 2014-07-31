#pragma once
#include "glfw3.h"
#include "glm/glm.hpp"

enum ShapeType
{
	Square,
	Triangle,
	Circle,
	Hexagon
};
enum ColorType
{
	Red,
	Blue,
	Green,
	Yellow
};
enum MovementType
{
	None,
	Vertical,
	Horizontal,
	Circular,
	Box,
};

static float BoxVerts[] =
{
	-1.0f,-1.0f,
	1.0f,-1.0f,
	1.0f,1.0f,
	-1.0f,1.0f,
};

class CShape
{
public:
	CShape(void);
	~CShape(void);
	void Initialize(ColorType _color, float _size, MovementType _movement, float _speed);
	void Animate(float _deltaTime);
	virtual void Draw() = 0;
	void ApplyColor();

protected:
	glm::vec2		mvecPosition;
	glm::vec3		mvecColor;	
	float			mfSize;
	int				miVertCount;

	// Variables concerning Animation
	MovementType	mMovementType;
	float			mfSpeed;
	float			mfAnimationPosition;
	float			mfLastTime;
	bool			mbReverse;
};

