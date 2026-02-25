#include "raylib.h"
#include <vector>
#include "../INode.h"
#include "../NodeManager.h"

int main() {
    // Initialization
	
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Node Editor");
    SetTargetFPS(60);
    NodeManager* nodeManager = new NodeManager();
    bool draggingNode = false;
    bool drawingConnection = false;
    INode* selectedNode = nullptr;

	
	// `WindowShouldClose` detects window close
    while (!WindowShouldClose()) {
        // Update
        
        if (IsKeyPressed(KEY_N))
        {
            INode* newNode = new INode(GetMousePosition(), "New Node");
            nodeManager->mNodeList.push_back(newNode);
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
                selectedNode = nullptr;
            }
            
        }

        // Draw
        BeginDrawing();
        ClearBackground(DARKGRAY);
        nodeManager->DrawAllNodes();
        if (drawingConnection && selectedNode != nullptr)
        {
            DrawLineBezier(selectedNode->mConnectorPos, GetMousePosition(), 2, WHITE);
        }
        EndDrawing();
    }

    // De-Initialization
    delete nodeManager;
	
    CloseWindow(); // Close window and OpenGL context

    return 0;
}