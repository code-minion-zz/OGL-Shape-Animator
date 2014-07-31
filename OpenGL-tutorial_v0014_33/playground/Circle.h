#pragma once
#include "shape.h"
class CCircle :
	public CShape
{
public:
	CCircle(void);
	~CCircle(void);
	
	void Initialize(ColorType _color, float _size, MovementType _movement, float _speed);
	void Draw();
};

