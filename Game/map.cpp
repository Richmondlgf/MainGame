#include "map.h"
#include "constants.h"

//const String ROCK_TEXTURE_PATH = "resources/images/Rock.png";
const String ROCK_TEXTURE_PATH = "resources/images/rock_test.png";
const String DOOR_CLOSED_TEXTURE_PATH = "resources/images/Door.png";
const String DOOR_OPENED_TEXTURE_PATH = "resources/images/openedDoor.png";

void tileMap::LoadMapSprites()
{
	//rock
	rockTexture.loadFromFile(ROCK_TEXTURE_PATH);
	rockSprite.setTexture(rockTexture);
	rockSprite.setScale(2, 2);

	//closed door
	closedDoorTexture.loadFromFile(DOOR_CLOSED_TEXTURE_PATH);
	closedDoorSprite.setTexture(closedDoorTexture);
	closedDoorSprite.setScale(2, 2);

	//opened door
	openedDoorTexture.loadFromFile(DOOR_OPENED_TEXTURE_PATH);
	openedDoorSprite.setTexture(openedDoorTexture);
	openedDoorSprite.setScale(2, 2);
}

void tileMap::setDoorType(Map& myMap, bool isRoomClear)
{
	if (isRoomClear == false)
	{
		myMap.sprite = closedDoorSprite;
		isOpened = false;
	}
	else
	{
		myMap.sprite = openedDoorSprite;
		isOpened = true;
	}
}

void tileMap::drawMap(vector<Map>& myMap, RenderWindow& window, bool isRoomClear)
{
	if (isMapSpritesLoaded == false)
	{
		LoadMapSprites();
		isMapSpritesLoaded = true;
	}

	int counter = 0;

	myMap.clear();

	Map map;

	for (int i = 0; i < HEIGHT_MAP; i++)
	{
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (mapString[i][j] == 's')
			{
				map.y = i * TILE_SIDE;
				map.x = j * TILE_SIDE;
				map.sprite = rockSprite;
				map.pos = NOTDOOR;
				myMap.push_back(map);
				counter++;
			}

			else if (mapString[i][j] == 'u')
			{
				setDoorType(map, isRoomClear);
				map.y = i * TILE_SIDE - TILE_SIDE;
				map.x = j * TILE_SIDE - TILE_SIDE / 2;
				map.pos = UP;
				myMap.push_back(map);
				counter++;
			}
			else if (mapString[i][j] == 'd')
			{
				setDoorType(map, isRoomClear);
				map.y = i * TILE_SIDE;
				map.x = j * TILE_SIDE - TILE_SIDE / 2;
				map.pos = DOWN;
				myMap.push_back(map);
				counter++;
			}
			else if (mapString[i][j] == 'r')
			{
				setDoorType(map, isRoomClear);
				map.y = i * TILE_SIDE;
				map.x = j * TILE_SIDE;
				map.pos = RIGHT;
				myMap.push_back(map);
				counter++;
			}
			else if (mapString[i][j] == 'l')
			{
				setDoorType(map, isRoomClear);
				map.y = i * TILE_SIDE;
				map.x = j * TILE_SIDE - TILE_SIDE;
				map.pos = LEFT;
				myMap.push_back(map);
				counter++;
			}
		}
	}
	drawTiles(myMap, window);
}

void tileMap::drawTiles(vector<Map>& myMap, RenderWindow& window)
{
	for (auto& map: myMap)
	{
		if (map.pos == 0)
		{
			map.sprite.setPosition(float(map.x), float(map.y));
		}
		else
		{
			if (map.pos == UP)
			{
				map.sprite.setTextureRect(IntRect(0, 0, 64, 64));
				map.sprite.setPosition(float(map.x), float(map.y));
			}
			else if (map.pos == DOWN)
			{
				map.sprite.setTextureRect(IntRect(64, 0, 64, 64));
				map.sprite.setPosition(float(map.x), float(map.y));
			}
			else if (map.pos == LEFT)
			{
				map.sprite.setTextureRect(IntRect(192, 0, 64, 64));
				map.sprite.setPosition(float(map.x), float(map.y));
			}
			else if (map.pos == RIGHT)
			{
				map.sprite.setTextureRect(IntRect(128, 0, 64, 64));
				map.sprite.setPosition(float(map.x), float(map.y));
			}
		}
		window.draw(map.sprite);
	}
}