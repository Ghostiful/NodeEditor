#pragma once
#include "raylib.h"
#include <string>

const float DEFAULT_NODE_HEIGHT = 100;
const float DEF_NODE_WIDTH = 200;
const float DEF_LABEL_HEIGHT = 25;

class INode
{
public:
	Vector2 mPosition;
	Rectangle* mBodyRect;
	Rectangle* mLabelRect;
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
	void MoveNode(Vector2 newPos);

};

