//
// Created by rgr24 on 03/06/2021.
//

#ifndef GRAPHS_FULL_HEAP_DATA_H
#define GRAPHS_FULL_HEAP_DATA_H

#include "shortest_path_data.h"

class heap_data {
public:
    heap_data( shortest_path_data* data ) :
            m_data{ data },
            distance{ data->distance() } {}

    bool visited() const { return m_data->visited(); };
    void visit() const {
        m_data->visit();
    }
    const graph::vertex *vertex() const {
        return m_data->vertex();
    }

    // functions to support binary heaps of <const shortest_path_data*>
    void insert(std::vector<heap_data>& heap);
    static heap_data delete_min(std::vector<heap_data>& heap);
private:
    // comparison function used for sorting in max-heap, so that instance with shortest distance
    // is at root of binary heap
    static bool compare(const heap_data& first, const heap_data& second);

    shortest_path_data* m_data;
    int distance;
};

#endif //GRAPHS_FULL_HEAP_DATA_H
