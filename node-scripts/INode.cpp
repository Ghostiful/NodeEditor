#include "INode.h"

INode::INode() 
{
	mPosition.x = 0;
	mPosition.y = 0;
	mLabelRect = new Rectangle();
	mLabelRect->x = mPosition.x;
	mLabelRect->y = mPosition.y;
	mLabelRect->width = DEF_NODE_WIDTH;
	mLabelRect->height = DEF_LABEL_HEIGHT;
	mBodyRect = new Rectangle();
	mBodyRect->x = mPosition.x;
	mBodyRect->y = mPosition.y + DEF_LABEL_HEIGHT;
	mBodyRect->width = DEF_NODE_WIDTH;
	mBodyRect->height = DEFAULT_NODE_HEIGHT;
	mConnectorPos.x = mPosition.x + DEF_NODE_WIDTH - BORDER_WIDTH - CONNECTOR_RADIUS;
	mConnectorPos.y = mPosition.y + DEF_LABEL_HEIGHT + DEFAULT_NODE_HEIGHT / 2;
	mInputPos.x = mPosition.x + BORDER_WIDTH + CONNECTOR_RADIUS;
	mInputPos.y = mPosition.y + DEF_LABEL_HEIGHT + DEFAULT_NODE_HEIGHT / 2;
	mName = "New Node";
	mText = "Body Text";

}

INode::INode(Vector2 position, std::string name)
{
	mPosition = position;
	mLabelRect = new Rectangle();
	mLabelRect->x = mPosition.x;
	mLabelRect->y = mPosition.y;
	mLabelRect->width = DEF_NODE_WIDTH;
	mLabelRect->height = DEF_LABEL_HEIGHT;
	mBodyRect = new Rectangle();
	mBodyRect->x = mPosition.x;
	mBodyRect->y = mPosition.y + DEF_LABEL_HEIGHT;
	mBodyRect->width = DEF_NODE_WIDTH;
	mBodyRect->height = DEFAULT_NODE_HEIGHT;
	mConnectorPos = position;
	mConnectorPos.x = mPosition.x + DEF_NODE_WIDTH - BORDER_WIDTH - CONNECTOR_RADIUS;
	mConnectorPos.y = mPosition.y + DEF_LABEL_HEIGHT + DEFAULT_NODE_HEIGHT / 2;
	mInputPos.x = mPosition.x + BORDER_WIDTH + CONNECTOR_RADIUS;
	mInputPos.y = mPosition.y + DEF_LABEL_HEIGHT + DEFAULT_NODE_HEIGHT / 2;
	mName = name;
}

INode::INode(float x, float y, std::string name)
{
	mPosition.x = x;
	mPosition.y = y;
	mLabelRect = new Rectangle();
	mLabelRect->x = mPosition.x;
	mLabelRect->y = mPosition.y;
	mLabelRect->width = DEF_NODE_WIDTH;
	mLabelRect->height = DEF_LABEL_HEIGHT;
	mBodyRect = new Rectangle();
	mBodyRect->x = mPosition.x;
	mBodyRect->y = mPosition.y + DEF_LABEL_HEIGHT;
	mBodyRect->width = DEF_NODE_WIDTH;
	mBodyRect->height = DEFAULT_NODE_HEIGHT;
	mConnectorPos.x = mPosition.x + DEF_NODE_WIDTH - BORDER_WIDTH - CONNECTOR_RADIUS;
	mConnectorPos.y = mPosition.y + DEF_LABEL_HEIGHT + DEFAULT_NODE_HEIGHT / 2;
	mInputPos.x = mPosition.x + BORDER_WIDTH + CONNECTOR_RADIUS;
	mInputPos.y = mPosition.y + DEF_LABEL_HEIGHT + DEFAULT_NODE_HEIGHT / 2;
	mName = name;
}

INode::INode(Vector2 position)
{
	mPosition = position;
	mLabelRect = new Rectangle();
	mLabelRect->x = mPosition.x;
	mLabelRect->y = mPosition.y;
	mLabelRect->width = DEF_NODE_WIDTH;
	mLabelRect->height = DEF_LABEL_HEIGHT;
	mBodyRect = new Rectangle();
	mBodyRect->x = mPosition.x;
	mBodyRect->y = mPosition.y + DEF_LABEL_HEIGHT;
	mBodyRect->width = DEF_NODE_WIDTH;
	mBodyRect->height = DEFAULT_NODE_HEIGHT;
	mConnectorPos = position;
	mConnectorPos.x = mPosition.x + DEF_NODE_WIDTH - BORDER_WIDTH - CONNECTOR_RADIUS;
	mConnectorPos.y = mPosition.y + DEF_LABEL_HEIGHT + DEFAULT_NODE_HEIGHT / 2;
	mInputPos.x = mPosition.x + BORDER_WIDTH + CONNECTOR_RADIUS;
	mInputPos.y = mPosition.y + DEF_LABEL_HEIGHT + DEFAULT_NODE_HEIGHT / 2;
	mInConnector.position = mInputPos;
	mOutConnector.position = mConnectorPos;
	mInConnector.type = tINPUT;
	mOutConnector.type = tOUTPUT;
	mName = "New Node";
}

INode::INode(INode& node) 
{
	mPosition = node.mPosition;
	mLabelRect = new Rectangle(*node.mLabelRect);
	mBodyRect = new Rectangle(*node.mBodyRect);
	mConnectorPos = node.mConnectorPos;
	mInputPos = node.mInputPos;
	mName = node.mName;
	mText = node.mText;
}

INode::~INode()
{
	delete mLabelRect;
	delete mBodyRect;
}

void INode::DrawNode()
{
	DrawRectangleRec(*mBodyRect, BLACK);
	DrawRectangleRec(*mLabelRect, LIGHTGRAY);
	DrawText(mName.c_str(), mPosition.x + BORDER_WIDTH, mPosition.y + BORDER_WIDTH, 18, BLACK);
	DrawCircleLines(mConnectorPos.x, mConnectorPos.y, CONNECTOR_RADIUS, WHITE);
	DrawCircleLines(mInputPos.x, mInputPos.y, CONNECTOR_RADIUS, WHITE);

	// Text Field
	DrawText(mText.c_str(), mPosition.x + BORDER_WIDTH, mPosition.y + DEF_LABEL_HEIGHT + BORDER_WIDTH, 18, WHITE);
}

void INode::DrawConnectors()
{
	for (int i = 0; i < mConnectorList.size(); i++)
	{
		DrawCircleLines(mConnectorList[i].position.x, mConnectorList[i].position.y, CONNECTOR_RADIUS, WHITE);
	}
}

void INode::MoveNode(Vector2 newPos)
{
	
	mLabelRect->x = newPos.x;
	mLabelRect->y = newPos.y;
	mBodyRect->x = newPos.x;
	mBodyRect->y = newPos.y + mLabelRect->height;
	mConnectorPos.x += newPos.x - mPosition.x;
	mConnectorPos.y += newPos.y - mPosition.y;
	mInputPos.x += newPos.x - mPosition.x;
	mInputPos.y += newPos.y - mPosition.y;
	mPosition = newPos;
}

bool INode::MouseOnConnector(Vector2 mousePos)
{
	if (mousePos.x >= mConnectorPos.x - CONNECTOR_RADIUS && mousePos.x <= mConnectorPos.x + CONNECTOR_RADIUS && mousePos.y >= mConnectorPos.y - CONNECTOR_RADIUS && mousePos.y <= mConnectorPos.y + CONNECTOR_RADIUS)
	{
		return true;
	}
	return false;
}

void INode::EditText(std::string newText)
{
	//CoCreate
}
