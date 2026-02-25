#pragma once
#include "raylib.h"
#include "INode.h"
#include <vector>

class NodeManager
{
public:
	std::vector<INode*> mNodeList;


	// constructors
	NodeManager();

	// destructor
	~NodeManager();

	// helpers
	INode* MouseOnNode(Vector2 mousePos);
	INode* MouseOnConnector(Vector2 mousePos);
	void DrawAllNodes();

};
