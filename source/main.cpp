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
    std::string fileInputButtonText = "Save;Load";
    char fileNameEntry[25] = "graph-save";
    bool flagT = true;

    Rectangle nodeInputRect = Rectangle();
    nodeInputRect.x = screenWidth - N_BORDER_WIDTH - 275;
    nodeInputRect.y = N_BORDER_WIDTH;
    nodeInputRect.width = 275;
    nodeInputRect.height = 200;
    std::string nInputLabel = "Change Node Text";
    std::string nInputMessage = "Enter the new body text of the selected node";
    std::string nodeInputButtonText = "OK;Cancel";
    char nodeTextEntry[MAX_NODE_BODY_CHARS] = "Enter Text";
    bool showNodeInputBox = false;

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
            if (nodeManager->MouseOnAnyConnector(GetMousePosition()))
            {
                if (!drawingConnection)
                {
                    selectedNode = nodeManager->MouseOnConnector(GetMousePosition());
                    if (selectedNode != nullptr)
                        drawingConnection = true;
                }
            }
            else if (drawingConnection)
            {
                drawingConnection = false;

                INode* childNode = nodeManager->MouseOnInConnector(GetMousePosition());
                if (childNode != nullptr && selectedNode != nullptr)
                {
                    selectedNode->mChildren.push_back(childNode);
                    selectedNode->mChildGUIDs.push_back(childNode->mInConnector.id);
                    childNode = nullptr;
                }

                selectedNode = nullptr;
            }
            else if (!showNodeInputBox)
            {
                selectedNode = nodeManager->MouseOnNode(GetMousePosition());
                if (selectedNode != nullptr)
                {
                    // open text change input box

                    showNodeInputBox = true;

                }
                else 
                {
                    showNodeInputBox = false;
                }
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
        
        if (showNodeInputBox)
        {
            int res = GuiTextInputBox(nodeInputRect, nInputLabel.c_str(), nInputMessage.c_str(), nodeInputButtonText.c_str(), nodeTextEntry, MAX_NODE_BODY_CHARS, &flagT);
            if (res == 1)
                selectedNode->EditText(nodeTextEntry);
            else if (res == 2)
            {
                selectedNode = nullptr;
                showNodeInputBox = false;
            }
        }
        else
        {
            int result = GuiTextInputBox(fileInputRect, inputLabel.c_str(), inputMessage.c_str(), fileInputButtonText.c_str(), fileNameEntry, 25, &flagT);
            if (result == 1)
                saveLoadManager->SaveToFile(fileNameEntry + DEFAULT_EXTENSION, nodeManager->ConvertToSaveData());
            else if (result == 2)
                nodeManager->LoadSaveData(saveLoadManager->LoadFromFile(fileNameEntry + DEFAULT_EXTENSION));
        }
        
        
        
        
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