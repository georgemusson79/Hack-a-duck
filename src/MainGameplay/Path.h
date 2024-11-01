<<<<<<< HEAD
#include <../MainGameplay/Cat.h>
#include <../UserInterface/Texture.h>

#include "Vector2.h"
=======
#include "Vector2.h"
#include "../UserInterface/Texture.h"
#include "../UserInterface/Cat.h"
>>>>>>> cced3c2 (Updated Path.h)

// Each Tile is 20x20, making a 50x50 grid.
class Path {
<<<<<<< HEAD
    Vector2 currentTilePos;
    Path* nextTile;
    bool isLastTile;
    Path();
=======
	Vector2 tilePos;
	bool isLastTile;
	Path *nextPath;

	Path();
>>>>>>> cced3c2 (Updated Path.h)
}