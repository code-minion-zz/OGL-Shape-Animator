#pragma once
#include "shape.h"
class CTriangle :
	public CShape
{
public:
	CTriangle(void);
	~CTriangle(void);
	
	void Initialize(ColorType _color, float _size, MovementType _movement, float _speed);
	void Draw();
};

