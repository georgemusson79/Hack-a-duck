#include <Vector2>
#include <../UserInterface/Texture.h>
#include <../UserInterface/Cat.h>

class Path {
	Vector2 currentTilePos;
	Path nextTile;
	bool isLastTile;
}