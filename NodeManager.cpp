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
