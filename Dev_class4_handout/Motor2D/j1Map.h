#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------

struct TileSet {

	uint firstgid = 0u;
	p2SString name;
	uint height=0u;
	uint tilewidth=0u;
	uint tileheigth=0u;
	uint spacing =0u;
	uint margin = 0u;

	//image source = "tmw_desert_spacing.png" width = "265" height = "199";
};

// TODO 1: Create a struct needed to hold the information to Map node


// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:


public:

	// TODO 1: Add your struct for map info as public for now
	struct Map {

		enum MapOrientation {

			OR_UNDEFINED,
			OR_ORTOGONAL,
			OR_ISOMETRIC

		};
		enum MapRenderOrder {

			RE_UNDEFINED,
			RE_RIGHT_DOWN,
			RE_RIGHT_UP,
			RE_LEFT_DOWN,
			RE_LEFT_UP,
		};

		uint width = 0u;
		uint height = 0u;
		uint tilewidth = 0u;
		uint tileheigth = 0u;
		uint nextobjective = 0u;

	};

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__