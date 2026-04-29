#pragma once

#include <fix_win32_compatibility.h>

#include "raylib.h"
#include <string>
#include <vector>
#include <rpc.h>


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
	tINPUT,
	tOUTPUT
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
	Vector2 mInputPos;
	std::vector<Connector> mConnectorList;
	std::string mName;
	std::vector<INode*> mChildren;
	std::string mText;


	// constructors
	INode();
	INode(Vector2 position, std::string name);
	INode(float x, float y, std::string name);
	INode(Vector2 position);
	//INode(float x, float y);
	INode(INode& node);
	
	// destructor
	~INode();

	/// helpers

	// Drawing
	void DrawNode();
	void DrawConnectors();

	// Editing
	void MoveNode(Vector2 newPos);
	bool MouseOnConnector(Vector2 mousePos);
	void EditText(std::string newText);

};

class NodeBuilder 
{
private:
	INode* mNode;

public:

	inline NodeBuilder() 
	{
		mNode = nullptr;
	}

	inline void BuildPosition(const Vector2& pos)
	{
		mNode = new INode(pos);
	}

	inline void BuildName(const std::string& name) 
	{
		mNode->mName = name;
	}

	inline void BuildText(const std::string& text) 
	{
		mNode->mText = text;
	}

	inline void BuildChildren(const std::vector<INode*> children)
	{
		mNode->mChildren = children;
	}

	inline INode* BuildNode()
	{
		return mNode;
	}

	void ClearNodePtr()
	{
		mNode = nullptr;
	}
};

