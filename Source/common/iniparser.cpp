#include <stdio.h>
#include <string>
#include <cstring>

#include <glm/glm.hpp>

#include "iniparser.hpp"

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
		printf("Impossible to open the file ! Are you in the right path ?\n");
		getchar();
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		
		if ( strcmp( lineHeader, "shape" ) == 0 ){
			char shape[128];
			fscanf(file, "%s\r\n", &shape);			

			if ( strcmp( shape, "square" ) == 0 ){
				_shape = Square;
			} else if ( strcmp( shape, "triangle" ) == 0 ){
				_shape = Triangle;
			} else if ( strcmp( shape, "circle" ) == 0 ){
				_shape = Circle;
			} else if ( strcmp( shape, "hexagon" ) == 0 ){
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
				_color = Red;
			} else if ( strcmp( color, "blue" ) == 0 ){
				_color = Blue;
			} else if ( strcmp( color, "green" ) == 0 ){
				_color = Green;
			} else if ( strcmp( color, "yellow" ) == 0 ){
				_color = Yellow;
			}
		}else if ( strcmp( lineHeader, "movement" ) == 0 ){
			char movement[128];
			fscanf(file, "%s\r\n", &movement);

			if ( strcmp( movement, "vertical" ) == 0 ){
				_movement = Vertical;
			} else if ( strcmp( movement, "horizontal" ) == 0 ){
				_movement = Horizontal;
			} else if ( strcmp( movement, "circular" ) == 0 ){
				_movement = Circular;
			} else if ( strcmp( movement, "box" ) == 0 ){
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
