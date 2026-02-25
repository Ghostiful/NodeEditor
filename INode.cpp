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
	mName = "New Node";

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
	mName = name;
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
	DrawCircleLines(mConnectorPos.x, mConnectorPos.y, CONNECTOR_RADIUS, WHITE);
}

void INode::MoveNode(Vector2 newPos)
{
	
	mLabelRect->x = newPos.x;
	mLabelRect->y = newPos.y;
	mBodyRect->x = newPos.x;
	mBodyRect->y = newPos.y + mLabelRect->height;
	mConnectorPos.x += newPos.x - mPosition.x;
	mConnectorPos.y += newPos.y - mPosition.y;
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
