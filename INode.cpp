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
}

void INode::MoveNode(Vector2 newPos)
{
	mPosition = newPos;
	mLabelRect->x = newPos.x;
	mLabelRect->y = newPos.y;
	mBodyRect->x = newPos.x;
	mBodyRect->y = newPos.y + mLabelRect->height;
}
