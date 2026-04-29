#pragma once

#include <fix_win32_compatibility.h>

#include "raylib.h"
#include <string>
#include <vector>
#include <combaseapi.h>


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
	GUID id;
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
	Connector mInConnector;
	Connector mOutConnector;
	std::string mName;
	std::vector<INode*> mChildren;
	std::vector<GUID> mChildGUIDs;
	std::string mText;

	// inline
	inline bool HasChild() const { return !mChildren.empty(); }
	inline GUID GetInputGUID() const { return mInConnector.id; }

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
	bool GetConnectorFromGUID(GUID id, OUT Connector con);
	void ReconnectAllChildren(std::vector<INode*> children);

	// Drawing
	void DrawNode();
	void DrawConnectors();
	void DrawConnections();

	// Editing
	void MoveNode(Vector2 newPos);
	bool MouseOnConnector(Vector2 mousePos);
	bool MouseOnInConnector(Vector2 mousePos);
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

	inline void BuildChildren(const std::vector<GUID> children)
	{
		mNode->mChildGUIDs = children;
	}

	inline void AddChildGUID(const GUID id)
	{
		mNode->mChildGUIDs.push_back(id);
	}

	inline void BuildConnectors(LPOLESTR inID, LPOLESTR outID)
	{
		HRESULT res = CLSIDFromString(inID, &mNode->mInConnector.id);
		HRESULT res2 = CLSIDFromString(outID, &mNode->mOutConnector.id);
	}

	inline void BuildConnectors()
	{
		HRESULT res = CoCreateGuid(&mNode->mInConnector.id);
		HRESULT res2 = CoCreateGuid(&mNode->mOutConnector.id);
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

