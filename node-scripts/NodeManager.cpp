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

INode* NodeManager::MouseOnInConnector(Vector2 mousePos)
{
	for (int i = 0; i < mNodeList.size(); i++)
	{
		if (mNodeList[i]->MouseOnInConnector(mousePos))
		{
			return mNodeList[i];
		}
	}
	return nullptr;
}

INode* NodeManager::GetNodeFromGUID(GUID id)
{
	for (int i = 0; i < mNodeList.size(); i++)
	{
		if (mNodeList[i]->GetInputGUID() == id)
			return mNodeList[i];
	}
	
	return nullptr;
}

std::vector<INode*> NodeManager::GetChildListFromGUIDList(std::vector<GUID> idList)
{
	std::vector<INode*> nodeList;
	for (auto id : idList)
	{
		INode* n = GetNodeFromGUID(id);
		if (n != nullptr)
			nodeList.push_back(n);
	}
	return nodeList;
}

void NodeManager::ReconnectAllNodes()
{
	for (INode* n : mNodeList)
	{
		n->ReconnectAllChildren(GetChildListFromGUIDList(n->mChildGUIDs));
	}
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
	for (INode* node : mNodeList)
	{
		node->DrawConnections();
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

		LPOLESTR str;
		HRESULT res = StringFromCLSID(mNodeList[i]->mInConnector.id, &str);
		USES_CONVERSION;
		std::string s = OLE2A(str);
		data.push_back(s);

		res = StringFromCLSID(mNodeList[i]->mOutConnector.id, &str);
		s = OLE2A(str);
		data.push_back(s);

		for (int j = 0; j < mNodeList[i]->mChildren.size(); j++)
		{
			LPOLESTR str;
			HRESULT res = StringFromCLSID(mNodeList[i]->mChildren[j]->mInConnector.id, &str);
			USES_CONVERSION;
			std::string s = OLE2A(str);
			data.push_back(s);
		}
		data.push_back(NEXT_NODE_TOKEN);
	}
	return data;
}

bool NodeManager::LoadSaveData(NodeSaveData data)
{
	if (data.empty())
		return false;

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

		std::string str = dataQ.front();
		USES_CONVERSION;
		LPOLESTR sIn = A2OLE(str.c_str());
		dataQ.pop();
		str = dataQ.front();
		LPOLESTR sOut = A2OLE(str.c_str());
		nodeBuilder.BuildConnectors(sIn, sOut);
		dataQ.pop();

		while (dataQ.front() != NEXT_NODE_TOKEN)
		{
			std::string str = dataQ.front();
			LPOLESTR s = A2OLE(str.c_str());
			GUID id;
			HRESULT res = CLSIDFromString(s, &id);
			nodeBuilder.AddChildGUID(id);
			dataQ.pop();
		}

		mNodeList.push_back(nodeBuilder.BuildNode());
		nodeBuilder.ClearNodePtr();
		dataQ.pop();
	}

	ReconnectAllNodes();
	return true;
}
