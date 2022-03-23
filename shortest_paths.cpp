//
// Created by rgr24 on 29/05/2021.
//

#include <algorithm>
#include <iomanip>
#include <fstream>
#include <set>
#include <iostream>
#include "shortest_paths.h"
#include "dfs_traversal.h"
#include "heap_data.h"

shortest_paths::shortest_paths(const graph &graph)
        : m_graph{graph} {
}

bool shortest_paths::to_dot(const std::string &filename) {
    std::ofstream file{filename};
    if (file.is_open()) {
        file << "digraph {" << std::endl
             << "\trankdir = LR;" << std::endl
             << "\tnode[shape=oval];" << std::endl;

        // go over vertices, emit their label and colour
        for (const auto &v : m_graph.vertices()) {
            file << "\t" << v.label() << "[label=\"" << v.label();
            if (get_data(v)->distance() < shortest_path_data::VERY_FAR)
                file << "\\nd: " << get_data(v)->distance();
            file << "\"];" << std::endl;
        }

        // find shortest path edges
        std::set<const graph::edge*> shortest_path_edges {};
        for (const auto& spdata : m_data) {
            if (spdata.parent() != nullptr)
                shortest_path_edges.insert(spdata.parent());
        }
        // go over edges
        file << std::endl << "\tedge[dir = " << (m_graph.is_directed() ? "forward" : "none") << "];" << std::endl;
        for (const auto &v : m_graph.vertices()) {
            for (const auto &edge : v.edges()) {
                if (m_graph.is_directed() || v.label() < edge.target().label())
                {
                    file << "\t" << v.label() << " -> " << edge.target().label() << " [";
                    if (shortest_path_edges.find(&edge) == shortest_path_edges.end())
                        file << "style=" << std::quoted("dashed");
                    else
                        file << "penwidth=5";

                    file << ", label=\"" << edge.weight() << "\"];" << std::endl;
                }
            }
        }
        file << "}" << std::endl;
        return true;
    } else
        return false;
}

void shortest_paths::prepare(const graph::vertex &source) {
    // initialize the shortest paths data
    m_data.resize(m_graph.num_vertices());
    for (const auto &v : m_graph.vertices()) {
        m_data[v.id()] = shortest_path_data{&v};
    }

    // assign source vertex a distance of 0
    get_data(source)->set_distance(nullptr, 0);
}

// This is the compute method.
void shortest_paths::compute(const graph::vertex &source) {
    // initialize the shortest paths data
    prepare(source);

    // Perform depth-first traversal.
    auto traversal = dfs_traversal(source); // Create a graph.
    traversal.run(); // Run the traversal.
    auto containsCycle = traversal.cycle_found(); // Check if a cycle was found.

    // The graph contains no cycle.
    if (!containsCycle)
        relax_all(traversal.pre_order(), true); // Call the relax all function.
    // The graph contains a cycle.
    else
        heap_based_dijkstra(source);
}

// This is the 'find_next_dijkstra' method.
const graph::vertex *shortest_paths::find_next_dijkstra() {
    auto min = INT_MAX; // Maximum value to start with.
    unsigned long long minIdx = 0; // A variable to store your minimum index element.
    auto isChanged = false; // A boolean to check weather a minimum value is found.

    // Loop through your 'm_date' member.
    for (unsigned long long i = 0; i < m_data.size(); i++) {
        // Check if the element in 'm_data' is already visited, and smaller than the minimum value.
        if (!m_data[i].visited() && m_data[i].distance() < min) {
            min = m_data[i].distance(); // Change the minimum value.
            minIdx = i; // Change the minimum index.
            isChanged = true; // A minimum unvisited value is found.
        }
    }

    // Check if a new minimum unvisited element is found.
    if (isChanged)
        return m_data[minIdx].vertex(); // Return the vertex.
    else
        return nullptr; // There's is no new unvisited element, return a nullptr.
}

// This is the 'array_based_dijkstra' method.
void shortest_paths::array_based_dijkstra(const graph::vertex & source) {
    const graph::vertex *next = &source; // Get the source vertex.

    // Loop while your next vertex is not a nullptr.
    while (next != nullptr) {
        next = find_next_dijkstra(); // Find the next dijkstra.

        // Check if 'next' is not a nullptr, if this is true we're done.
        if (next == nullptr)
            return; // We're done.

        relax(*next); // Relax the vertex.
        get_data(*next)->visit(); // Mark your vertex as visited.
    }
}

// This is the heap_based_dijkstra method.
void shortest_paths::heap_based_dijkstra(const graph::vertex & source) {
    std::vector<heap_data> heap = {get_data(source)}; // This is your heap.

    // While your heap is not empty.
    while (!heap.empty()) {
        auto element = heap_data::delete_min(heap);
        auto boolElement = relax(*element.vertex());
        
    }
}

shortest_path_data *shortest_paths::get_data(const graph::vertex &vertex) {
    return &m_data[vertex.id()];
}

bool shortest_paths::relax(const graph::vertex &vertex) {
    bool an_edge_was_relaxed = false;
    for (const graph::edge &edge : vertex.edges()) {
        if (relax(vertex, edge))
            an_edge_was_relaxed = true;
    }
    return an_edge_was_relaxed;
}

// This is the relax method.
bool shortest_paths::relax(const graph::vertex& vertex, const graph::edge& edge) {
    auto data = get_data(vertex); // Get the data of your vertex.
    auto destination_data = get_data(edge.target()); // Get the data of your destination.

    // Check if the current distance is smaller than the sum of your current distance plus the weight of your edge.
    // If this is true, you can relax your edge.
    if (data->distance() + edge.weight() < destination_data->distance()) {
        get_data(edge.target())->set_distance(&edge, data->distance() + edge.weight()); // First, get the data of the target of the edge, than change it's distance.
        return true; // Edge is relaxed, return true.
    }
    return false; // Edge is not relaxed, return false.
}

// This is the 'relax_all' method.
void shortest_paths::relax_all(std::vector<std::string> vector, bool reversed) {
     // If the order is not reversed.
     if (!reversed) {
         for (auto &label : vector) {
             relax(m_graph[label]); // Relax the label.
         }
     }
    // The order is reversed.
     else {
         for (auto &label : vector) {
             auto lastLabel = vector.back();
             relax(m_graph[lastLabel]); // Relax the label.
             vector.pop_back();
         }
     }
}