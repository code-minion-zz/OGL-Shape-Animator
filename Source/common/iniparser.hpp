#ifndef INIPARSER_H
#define INIPARSER_H
#include "../playground/Shape.h"

bool loadINI(
	const char * path,
	ShapeType &shape,
	float &size,
	ColorType &color,
	MovementType &movement,
	float &speed
);


#endif