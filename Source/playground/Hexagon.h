#pragma once
#include "shape.h"
class CHexagon :
	public CShape
{
public:
	CHexagon(void);
	~CHexagon(void);
	
	void Initialize(ColorType _color, float _size, MovementType _movement, float _speed);
	void Draw();
};

