//
// Created by rgr24 on 28/05/2021.
//

#include "shortest_path_data.h"
#include <algorithm>

shortest_path_data::shortest_path_data(const graph::vertex *vertex, int distance, const graph::edge *edge)
        : m_visited{false},
          m_distance{distance},
          m_vertex{vertex},
          m_edge{edge} {
}

int shortest_path_data::distance() const {
    return m_distance;
}

const graph::edge *shortest_path_data::parent() const {
    return m_edge;
}

const graph::vertex *shortest_path_data::vertex() const {
    return m_vertex;
}

bool shortest_path_data::visited() const {
    return m_visited;
}

void shortest_path_data::visit() {
    m_visited = true;
}

void shortest_path_data::set_distance(const graph::edge* via_edge, int distance) {
    m_distance = distance;
    m_edge = via_edge;
}

