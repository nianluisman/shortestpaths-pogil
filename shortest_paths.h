//
// Created by rgr24 on 29/05/2021.
//

#ifndef GRAPHS_FULL_SHORTEST_PATHS_H
#define GRAPHS_FULL_SHORTEST_PATHS_H

#include "graph.h"
#include "shortest_path_data.h"

class shortest_paths {
    friend class shortest_paths_tester;
public:
    shortest_paths(const graph& graph);

    // computes the shortest paths from the source vertex
    void compute(const graph::vertex& source);

    // writes the graph and found shortest paths + distances to a dot file
    bool to_dot(const std::string& filename);
private:
    // prepares the computation of shortest paths
    void prepare(const graph::vertex& source);

    // retrieves the shortest_path_data element corresponding to the given vertex
    shortest_path_data * get_data(const graph::vertex& vertex);

    // finds the next unvisited vertex that has the smallest distance known so far
    const graph::vertex * find_next_dijkstra();

    // relaxes a vertex by relaxing all its edges
    bool relax(const graph::vertex &vertex);

    // relaxes the given (outgoing) edge of the given vertex
    bool relax(const graph::vertex &vertex, const graph::edge& edge);

    // relaxes all the vertices (indicated by label) in the vector
    void relax_all(std::vector<std::string> vector, bool reversed);

    // performs the array-based Dijkstra algorithm
    void array_based_dijkstra(const graph::vertex& source);

    // performs the heap-based Dijkstra algorithm
    void heap_based_dijkstra(const graph::vertex& source);

    const graph& m_graph;
    std::vector<shortest_path_data> m_data;
};


#endif //GRAPHS_FULL_SHORTEST_PATHS_H
