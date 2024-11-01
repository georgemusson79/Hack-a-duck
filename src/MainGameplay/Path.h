
#include "Vector2.h"
#include "../UserInterface/Texture.h"
#include "../UserInterface/Cat.h"

// Each Tile is 20x20, making a 50x50 grid.
class Path {
	Vector2 tilePos;
	bool isLastTile;
	Path *nextPath;

	Path();
}