#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::LoadLevel(string fileName)
{
	xml_document doc;
	doc.load_file("map.tmx");

	int widthMap, tileWidth;
	int heightMap, tileHeight;

	widthMap = atoi(doc.child("map").attribute("width").value());
	heightMap = atoi(doc.child("map").attribute("height").value());
	
	tileWidth = atoi(doc.child("map").attribute("tilewidth").value());
	tileHeight = atoi(doc.child("map").attribute("tileheight").value());

	_levelSize = Vector2i(widthMap*tileWidth, heightMap*tileHeight);

	int columnsTileset = atoi(doc.child("map").child("tileset").attribute("columns").value());

	string sourceTileset = doc.child("map").child("tileset").child("image").attribute("source").value();

	//�������� ����� ���������, ����� �� ��������� ������� ���� �����
	Texture *tileset = new Texture();
	tileset->loadFromFile(sourceTileset);

	string data = doc.child("map").child("layer").child("data").text().as_string();

	for (int i = 0; i < data.length(); i++)
	{
		if (data[i] == '\n') { data.erase(i, 1); }
		if (data[i] == ',') {data[i] = ' '; }
	}

	vector<int> tilesNumbers;
	istringstream ss(data);
	string temp;
	while (ss >> temp)
	{
		tilesNumbers.push_back(atoi(temp.c_str()));
	}
	for (int  k = 0; k < tilesNumbers.size(); k++)
	{
		if (tilesNumbers[k] != 0)
		{
			int iTile = (tilesNumbers[k] - 1) / columnsTileset;
			int jTile = (tilesNumbers[k] - 1) % columnsTileset;

			//�������� ����� ���������, ����� �� ��������� ������� ���� �����
			Sprite *temp = new Sprite();
			temp->setTexture(*tileset);
			temp->setTextureRect(IntRect(jTile*tileWidth, iTile*tileHeight, tileWidth, tileHeight));

			int iSprite = k / widthMap;
			int jSprite = k % widthMap;

			temp->setPosition(jSprite*tileWidth, iSprite*tileHeight);

			_tiles.push_back(temp);
		}
	}
}

Sprite Level::GetTileByIndex(int index)
{
	return *_tiles[index];
}

int Level::GetTilesCount()
{
	return _tiles.size();
}

Vector2i Level::GetLevelSize()
{
	return _levelSize;
}
