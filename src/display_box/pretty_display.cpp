#include <string>
#include <vector>

#include "display_box/pretty_display.hpp"
#include "graph.hpp"
#include <algorithm>

void printGraph(const Graph& graph, std::ostream& os) {
    std::vector<Graph::Vertex> keys = graph.getVertices();

    if (keys.empty()) {
        os << "# Graph is empty\n";
        return;
    }

    os << "# directed: " << (graph.isDirected() ? "true" : "false") << "\n";

    std::sort(keys.begin(), keys.end());

    for (const auto& u : keys) {
        os << u << ":\n";

        const auto& neighbors = graph.getNeighbors(u);
        for (const auto& e : neighbors) {
            os << "  " << e << "\n";
        }

        os << "\n";
    }
}