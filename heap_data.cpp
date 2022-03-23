//
// Created by rgr24 on 03/06/2021.
//

#include "heap_data.h"
#include <algorithm>

heap_data heap_data::delete_min(std::vector<heap_data>& heap) {
    // delete the first element from the (max-)heap, using the compare function to determine the ordering
    // this will remove the element with the shortest distance from the heap, and place it at the end of the vector
    std::pop_heap(heap.begin(), heap.end(), heap_data::compare);

    // the element with the shortest distance was moved to the back of the vector, remove & return it
    heap_data data = heap.back();
    heap.pop_back();
    return data;
}

bool heap_data::compare(const heap_data &first, const heap_data &second) {
    return second.distance < first.distance;
}

void heap_data::insert(std::vector<heap_data> &heap) {
    // add the element to
    heap.push_back(*this);
    std::push_heap(heap.begin(), heap.end(), heap_data::compare);
}
