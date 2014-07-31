#pragma once
#include "shape.h"
class CSquare :
	public CShape
{
public:
	CSquare(void);
	~CSquare(void);

	void Initialize(ColorType _color, float _size, MovementType _movement, float _speed);
	void Draw();
};

