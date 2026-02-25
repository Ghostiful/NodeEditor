#pragma once
#include "raylib.h"
#include <string>
#include <vector>

const float DEFAULT_NODE_HEIGHT = 100;
const float DEF_NODE_WIDTH = 200;
const float DEF_LABEL_HEIGHT = 25;
const float CONNECTOR_RADIUS = 10;
const float BORDER_WIDTH = 5;

const enum NodeType
{
	BASE,
	IO,
	INPUT_ONLY
};

const enum ConnectorType
{
	INPUT,
	OUTPUT
};

struct Connector
{
public:
	Vector2 position;
	ConnectorType type;
};

class INode
{
public:
	Vector2 mPosition;
	Rectangle* mBodyRect;
	Rectangle* mLabelRect;
	Vector2 mConnectorPos;
	std::vector<Connector> mConnectorList;
	std::string mName;


	// constructors
	INode();
	INode(Vector2 position, std::string name);
	INode(float x, float y, std::string name);
	INode(Vector2 position);
	INode(float x, float y);
	
	// destructor
	~INode();

	// helpers
	void DrawNode();
	void DrawConnectors();
	void MoveNode(Vector2 newPos);
	bool MouseOnConnector(Vector2 mousePos);

};

