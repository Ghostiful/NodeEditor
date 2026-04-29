#include "NodeManager.h"

NodeManager::NodeManager()
{
}

NodeManager::~NodeManager()
{
	for (int i = 0; i < mNodeList.size(); i++) 
	{
		delete mNodeList[i];
	}
}

INode* NodeManager::MouseOnNode(Vector2 mousePos)
{
	for (int i = 0; i < mNodeList.size(); i++) 
	{
		if (mousePos.x >= mNodeList[i]->mPosition.x && mousePos.x <= mNodeList[i]->mPosition.x + mNodeList[i]->mLabelRect->width && mousePos.y >= mNodeList[i]->mPosition.y && mousePos.y <= mNodeList[i]->mPosition.y + mNodeList[i]->mLabelRect->height)
		{
			return mNodeList[i];
		}
	}
	return nullptr;
}

INode* NodeManager::MouseOnConnector(Vector2 mousePos)
{
	for (int i = 0; i < mNodeList.size(); i++)
	{
		if (mNodeList[i]->MouseOnConnector(mousePos))
		{
			return mNodeList[i];
		}
	}
	return nullptr;
}

void NodeManager::DrawAllNodes()
{
	for (int i = 0; i < mNodeList.size(); i++)
	{
		mNodeList[i]->DrawNode();
	}
}

void NodeManager::DrawAllConnections()
{
	for (int i = 0; i < mConnections.size(); i++)
	{
		DrawLineBezier(mConnections[i].startNode->mConnectorPos, mConnections[i].endNode->mConnectorPos, 2, WHITE);
	}
}

NodeSaveData NodeManager::ConvertToSaveData()
{
	NodeSaveData data;
	for (int i = 0; i < mNodeList.size(); i++)
	{
		data.push_back(std::to_string(mNodeList[i]->mPosition.x));
		data.push_back(std::to_string(mNodeList[i]->mPosition.y));
		data.push_back(mNodeList[i]->mName);
		data.push_back(mNodeList[i]->mText);
		for (int j = 0; j < mNodeList[i]->mChildren.size(); j++)
		{
			data.push_back(mNodeList[i]->mChildren[j]->mName);
		}
		data.push_back(NEXT_NODE_TOKEN);
	}
	return data;
}

void NodeManager::LoadSaveData(NodeSaveData data)
{
	if (data.empty())
		return;

	NodeBuilder nodeBuilder;

	for (int i = 0; i < mNodeList.size(); i++)
	{
		delete mNodeList[i];
	}

	std::queue<std::string> dataQ;

	for (int i = 0; i < data.size(); i++)
	{
		dataQ.push(data[i]);
	}

	while (!dataQ.empty())
	{
		Vector2 pos = Vector2();
		pos.x = std::stof(dataQ.front());
		dataQ.pop();
		pos.y = std::stof(dataQ.front());
		dataQ.pop();

		nodeBuilder.BuildPosition(pos);
		nodeBuilder.BuildName(dataQ.front());
		dataQ.pop();
		nodeBuilder.BuildText(dataQ.front());
		dataQ.pop();
		mNodeList.push_back(nodeBuilder.BuildNode());
		nodeBuilder.ClearNodePtr();
	}
}
