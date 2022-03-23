//
// Created by rgr24 on 28/05/2021.
//

#ifndef GRAPHS_FULL_SHORTEST_PATH_DATA_H
#define GRAPHS_FULL_SHORTEST_PATH_DATA_H

#include "graph.h"

struct heap_data;

class shortest_path_data {
public:
    shortest_path_data(const graph::vertex * vertex = nullptr, int distance = VERY_FAR, const graph::edge * path = nullptr);

    bool visited() const;

    int distance() const;
    void visit();

    void set_distance(const graph::edge* via_edge, int distance);
    const graph::vertex * vertex() const;
    const graph::edge * parent() const;


    static const int VERY_FAR = std::numeric_limits<int>::max();
private:
    bool m_visited;
    int m_distance;
    const graph::vertex *m_vertex;
    const graph::edge *m_edge;
};


#endif //GRAPHS_FULL_SHORTEST_PATH_DATA_H
