#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>
#include <locale>
#include <cstring>

#include <glm/glm.hpp>

#include "../playground/Shape.h"
#include "iniparser.hpp"

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide : 
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

bool loadINI(
	const char * path,
	ShapeType &_shape,
	float &_size,
	ColorType &_color,
	MovementType &_movement,
	float &_speed
){
	printf("Loading INI file %s...\n", path);

	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "shape" ) == 0 ){
			char shape[128];
			fscanf(file, "%s\r\n", &shape);			

			if ( strcmp( shape, "square" ) == 0 ){
				// create a square
				_shape = Square;
			} else if ( strcmp( shape, "triangle" ) == 0 ){
				// create a triangle
				_shape = Triangle;
			} else if ( strcmp( shape, "circle" ) == 0 ){
				// create a circle
				_shape = Circle;
			} else if ( strcmp( shape, "hexagon" ) == 0 ){
				// create a hexagon
				_shape = Hexagon;
			}
		}else if ( strcmp( lineHeader, "size" ) == 0 ){
			float size = 0;
			fscanf(file, "%f\r\n", &size);

			_size = size;

		}else if ( strcmp( lineHeader, "color" ) == 0 ){
			char color[128];
			fscanf(file, "%s\r\n", &color);
			
			if ( strcmp( color, "red" ) == 0 ){
				// create a square
				_color = Red;
			} else if ( strcmp( color, "blue" ) == 0 ){
				// create a triangle
				_color = Blue;
			} else if ( strcmp( color, "green" ) == 0 ){
				// create a circle
				_color = Green;
			} else if ( strcmp( color, "yellow" ) == 0 ){
				// create a hexagon
				_color = Yellow;
			}
		}else if ( strcmp( lineHeader, "movement" ) == 0 ){
			char movement[128];
			fscanf(file, "%s\r\n", &movement);

			if ( strcmp( movement, "vertical" ) == 0 ){
				// create a square
				_movement = Vertical;
			} else if ( strcmp( movement, "horizontal" ) == 0 ){
				// create a triangle
				_movement = Horizontal;
			} else if ( strcmp( movement, "circular" ) == 0 ){
				// create a circle
				_movement = Circular;
			} else if ( strcmp( movement, "box" ) == 0 ){
				// create a hexagon
				_movement = Box;
			}
			else
			{
				_movement = None;
			}
		} else if (strcmp( lineHeader, "speed" ) == 0) {			
			float speed;
			fscanf(file, "%f\r\n", &speed);

			_speed = speed;

		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	return true;
}
