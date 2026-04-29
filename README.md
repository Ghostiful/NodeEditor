# Node-based Graph Editor
Implemented using Raylib in C++

## Usage
### Controls
- Press `N` to create a new node at the current mouse position
- `Right click` on the node header to drag the node around
- `Left click` on node sockets (the small circles) to start making a connection between two nodes
  - `Left click` again on an input socket (the socket on the left side of a node) to finalize a connection
  - `Left click` off of any node to stop making a connection between nodes
- `Left click` on a node's body to edit the text within the node
  - This will open a menu on the top right
  - Enter the new text for the node into the menu, then click `OK` to finalize the change
  - Click `Cancel` to cancel any changes and close the menu

### Saving/Loading Graphs
- Type a file name into the top left input area
- Click `Save` to save the current graph with that file name or `Load` to load a graph with that file name.

## Building and Running the Editor
You don't have to open VS to build the project. Just run `build-and-run.bat`.
