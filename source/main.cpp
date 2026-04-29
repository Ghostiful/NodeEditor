#include "raylib.h"
#include <vector>
#include "../node-scripts/INode.h"
#include "../node-scripts/NodeManager.h"
#include "../node-scripts/SaveLoadManager.h"

int main() {
    // Initialization
	
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Node Editor");
    SetTargetFPS(60);
    NodeManager* nodeManager = new NodeManager();
    SaveLoadManager* saveLoadManager = new SaveLoadManager();
    bool draggingNode = false;
    bool drawingConnection = false;
    INode* selectedNode = nullptr;
    NodeBuilder* nodeBuilder = new NodeBuilder();

    if (nodeManager->LoadSaveData(saveLoadManager->LoadFromFile(DEFAULT_FILEPATH)))
    {

    }

	
	// `WindowShouldClose` detects window close
    while (!WindowShouldClose()) {
        // Update
        
        if (IsKeyPressed(KEY_N))
        {
            nodeBuilder->BuildPosition(GetMousePosition());
            nodeBuilder->BuildName("New Node");
            nodeBuilder->BuildText("Body Text");
            nodeBuilder->BuildConnectors();

            INode* newNode = nodeBuilder->BuildNode();
            nodeBuilder->ClearNodePtr();


            nodeManager->mNodeList.push_back(newNode);
            newNode = nullptr;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            if (!draggingNode)
            {
                selectedNode = nodeManager->MouseOnNode(GetMousePosition());
                if (selectedNode != nullptr)
                {
                    draggingNode = true;
                }
            }
            else
            {
                selectedNode->MoveNode(GetMousePosition());
            }
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
        {
            selectedNode = nullptr;
            draggingNode = false;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (!drawingConnection) 
            {
                selectedNode = nodeManager->MouseOnConnector(GetMousePosition());
                drawingConnection = true;
            }
            else
            {
                drawingConnection = false;
                /*NodeConnection newConnection;
                newConnection.startNode = selectedNode;*/

                INode* childNode = nodeManager->MouseOnInConnector(GetMousePosition());
                if (childNode != nullptr && selectedNode != nullptr)
                {
                    selectedNode->mChildren.push_back(childNode);
                    selectedNode->mChildGUIDs.push_back(childNode->mInConnector.id);
                    childNode = nullptr;
                }

                /*selectedNode = nodeManager->MouseOnConnector(GetMousePosition());
                newConnection.endNode = selectedNode;
                if (newConnection.startNode != nullptr && newConnection.endNode != nullptr)
                {
                    nodeManager->mConnections.push_back(newConnection);
                }*/

                

                selectedNode = nullptr;

            }
            
        }

        // Draw
        BeginDrawing();
        ClearBackground(DARKGRAY);
        nodeManager->DrawAllNodes();
        nodeManager->DrawAllConnections();
        if (drawingConnection && selectedNode != nullptr)
        {
            DrawLineBezier(selectedNode->mConnectorPos, GetMousePosition(), 2, WHITE);
        }
        
        EndDrawing();
    }

    saveLoadManager->SaveToFile(DEFAULT_FILEPATH, nodeManager->ConvertToSaveData());

    // De-Initialization
    delete nodeManager;
    delete nodeBuilder;
    delete saveLoadManager;
	
    CloseWindow(); // Close window and OpenGL context

    return 0;
}