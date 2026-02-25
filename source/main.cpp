#include "raylib.h"
#include <vector>
#include "../INode.h"

int main() {
    // Initialization
	
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Node Editor");
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second when possible
    std::vector<INode*> nodeList;


    // Main game loop
	
	// `WindowShouldClose` detects window close
    while (!WindowShouldClose()) {
        // Update
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
        {
            INode* newNode = new INode(GetMousePosition(), "New Node");
            nodeList.push_back(newNode);
        }

        // Draw
        BeginDrawing();
        ClearBackground(DARKGRAY);
        for (int i = 0; i < nodeList.size(); i++)
        {
            nodeList[i]->DrawNode();
        }
        EndDrawing();
    }

    // De-Initialization
    for (int i = 0; i < nodeList.size(); i++) 
    {
        delete nodeList[i];
    }
    nodeList.clear();
	
    CloseWindow(); // Close window and OpenGL context

    return 0;
}