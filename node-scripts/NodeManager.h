#pragma once
#include "raylib.h"
#include "INode.h"
#include <vector>
#include <unordered_map>
#include <queue>


const std::string NEXT_NODE_TOKEN = "--nnt--";

typedef std::vector<std::string> NodeSaveData;

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

	// drawing
	void DrawAllNodes();
	void DrawAllConnections();

	// save/load help
	NodeSaveData ConvertToSaveData();
	void LoadSaveData(NodeSaveData data);

};


