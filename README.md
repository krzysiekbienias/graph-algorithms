### Graph API 🕸️

The project provides a simple Graph class implemented using an adjacency list representation.
It serves as the canonical structure for explicit graph problems where vertices and edges are defined directly.

#### Design rationale

Graph problems are often defined using different input representations. Even within the same category, the input may
appear as:

* an edge list ([[u, v], ...] or [[u, v, w], ...])
* an adjacency list
* an adjacency matrix
* other problem-specific formats (coordinates, grids, etc.)

To avoid coupling algorithms to a specific input format, this project introduces a simple Graph API implemented with an
adjacency list representation. Builder utilities convert various raw representations into this canonical structure,
allowing algorithms to operate on a single, unified interface.

At the same time, not every graph problem requires constructing an explicit graph object. In many cases the graph is
implicit (for example, grid-based problems like Number of Islands), where vertices and edges are derived dynamically
during traversal. In such situations the problem is still approached with graph techniques (BFS/DFS), but without
converting the input into a Graph instance.

#### Core capabilities

The Graph API exposes a minimal set of operations needed by most graph algorithms:

* `addVertex(v)` – inserts a vertex if it does not already exist
* `addEdge(u, v, w)` – adds an edge with an optional weight (missing vertices are created automatically)
* `containsVertex(v)` – checks if a vertex exists in the graph
* `getVertices()` – returns the list of all vertices in the graph
* `getNeighbors(v)` – returns the outgoing edges from a given vertex
* `vertexCount()` – returns the total number of vertices

Edges are stored using the internal structure:

```c++
struct Edge {
    Vertex to;
    Weight weight;
};
```

### Design note

This Graph class represents explicit graphs (e.g., edge lists, weighted graphs, etc.).

Some problems, such as grid-based traversal (e.g., Number of Islands), represent implicit graphs where neighbors are
derived dynamically from the input structure.
In those cases, algorithms operate directly on the grid rather than constructing a Graph instance.