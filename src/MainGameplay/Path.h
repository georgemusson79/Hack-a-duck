#include <vector>
#include <../UserInterface/Texture.h>
#include <../UserInterface/Cat.h>

class PathTile {
	public:
		int[] location;
}

struct Path {
	int[] startTile;
	int[] currentTile;
	int[] nextTile = findMove(currentTile, );
	int[] endTile;
}