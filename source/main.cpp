#include "raylib.h"
#include <vector>
#include "../node-scripts/INode.h"
#include "../node-scripts/NodeManager.h"
#include "../node-scripts/SaveLoadManager.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

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
    Rectangle fileInputRect = Rectangle();
    fileInputRect.x = N_BORDER_WIDTH;
    fileInputRect.y = N_BORDER_WIDTH;
    fileInputRect.width = 275;
    fileInputRect.height = 200;
    std::string inputLabel = "Save/Load Graph";
    std::string inputMessage = "Enter a file name (without the extension)";
    std::string textInputButtonText = "Save;Load";
    char textToChange[25] = "graph-save";
    bool flagT = false;

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
        
        
        int result = GuiTextInputBox(fileInputRect, inputLabel.c_str(), inputMessage.c_str(), textInputButtonText.c_str(), textToChange, 25, &flagT);
        if (result == 1)
            saveLoadManager->SaveToFile(textToChange + DEFAULT_EXTENSION, nodeManager->ConvertToSaveData());
        else if (result == 2)
            nodeManager->LoadSaveData(saveLoadManager->LoadFromFile(textToChange + DEFAULT_EXTENSION));
        
        
        EndDrawing();
    }

    //saveLoadManager->SaveToFile(DEFAULT_FILEPATH, nodeManager->ConvertToSaveData());

    // De-Initialization
    delete nodeManager;
    delete nodeBuilder;
    delete saveLoadManager;
	
    CloseWindow(); // Close window and OpenGL context

    return 0;
}