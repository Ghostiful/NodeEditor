#pragma once
#include "raylib.h"
#include "INode.h"
#include <vector>
#include <unordered_map>




struct NodeConnection
{
public:
	INode* startNode;
	INode* endNode;

	/*NodeConnection();
	~NodeConnection();*/
};

class NodeManager
{
public:
	std::vector<INode*> mNodeList;
	std::vector<NodeConnection> mConnections;
	


	// constructors
	NodeManager();

	// destructor
	~NodeManager();

	// helpers
	INode* MouseOnNode(Vector2 mousePos);
	INode* MouseOnConnector(Vector2 mousePos);
	void DrawAllNodes();
	void DrawAllConnections();

};


