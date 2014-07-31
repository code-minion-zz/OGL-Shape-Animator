#ifndef INIPARSER_H
#define INIPARSER_H

bool loadINI(
	const char * path,
	ShapeType &shape,
	float &size,
	ColorType &color,
	MovementType &movement,
	float &speed
);


#endif