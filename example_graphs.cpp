//
// Created by rgr24 on 27/05/2021.
//

#include "example_graphs.h"

graph cyclic_3() {
    graph g{true};
    for (auto& label : {"a", "b", "c", "d", "e", "f", "g", "h"})
        g.add_vertex(label);

    g.add_edge("a", "b", 11);
    g.add_edge("a", "g", 2);

    g.add_edge("b", "c", 15);
    g.add_edge("b", "h", 1);

    g.add_edge("c", "b", 1);
    g.add_edge("c", "d", 1);

    g.add_edge("d", "c", 2);
    g.add_edge("d", "e", 1);

    g.add_edge("e", "d", 7);
    g.add_edge("e", "f", 4);

    g.add_edge("f", "h", 1);
    g.add_edge("f", "c", 6);

    g.add_edge("g", "b", 9);
    g.add_edge("g", "f", 18);
    g.add_edge("g", "h", 5);

    g.add_edge("h", "a", 5);
    g.add_edge("h", "b", 3);
    g.add_edge("h", "c", 18);
    g.add_edge("h", "d", 16);
    g.add_edge("h", "e", 8);

    return g;
}

graph acyclic_graph() {
    graph g{true};
    for (auto& label : {"a", "b", "c", "d", "e", "f", "g", "h"})
        g.add_vertex(label);

    g.add_edge("a", "b", 1);
    g.add_edge("a", "c", 3);
    g.add_edge("a", "d", 4);

    g.add_edge("b", "e", 4);
    g.add_edge("b", "f", 5);
    g.add_edge("b", "c", 1);

    g.add_edge("c", "e", 3);
    g.add_edge("c", "d", 1);

    g.add_edge("d", "f", 3);
    g.add_edge("d", "e", 1);

    g.add_edge("e", "g", 3);
    g.add_edge("e", "h", 4);
    g.add_edge("e", "f", 1);

    g.add_edge("f", "g", 1);

    g.add_edge("g", "h", 1);

    return g;
}

graph cyclic_1() {
    graph g{true};
    for (auto& label : {"a", "b", "c", "d", "e", "f", "g", "h"})
        g.add_vertex(label);

    g.add_edge("a", "b", 2);
    g.add_edge("a", "e", 5);
    g.add_edge("a", "h", 1);

    g.add_edge("b", "c", 4);
    g.add_edge("c", "d", 1);

    g.add_edge("e", "c", 1);
    g.add_edge("e", "f", 0);

    g.add_edge("f", "g", 1);
    g.add_edge("g", "e", 1);
    g.add_edge("h", "f", 1);

    return g;
}

graph cyclic_2() {
    graph g{true};
    for (auto& label : {"a", "b", "c", "d", "e", "f", "g", "h"})
        g.add_vertex(label);

    g.add_edge("a", "h", 1);
    g.add_edge("a", "b", 2);
    g.add_edge("a", "e", 5);

    g.add_edge("b", "c", 4);
    g.add_edge("c", "d", 1);

    g.add_edge("e", "c", 1);
    g.add_edge("e", "f", 0);

    g.add_edge("f", "g", 1);
    g.add_edge("g", "e", 1);
    g.add_edge("h", "f", 1);

    return g;
}
