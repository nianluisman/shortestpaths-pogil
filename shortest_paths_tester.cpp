//
// Created by rgr24 on 31/05/2021.
//

#include <iostream>
#include <iomanip>
#include "shortest_paths_tester.h"
#include "graph.h"
#include "shortest_paths.h"

bool shortest_paths_tester::test_relax() {
    bool result = true;
    // create a directed graph
    graph g{true};
    g.add_vertex("a");
    g.add_vertex("b");
    g.add_vertex("c");

    g.add_edge("a", "b", 3);
    g.add_edge("a", "c", 5);
    g.add_edge("b", "c", 1);

    shortest_paths sp{g};
    sp.prepare(g["a"]);

    // relax (a, b) and verify distance to b has decreased to 3
    sp.relax(g["a"], g.find_edge("a", "b"));
    if (int dist = sp.get_data(g["b"])->distance(); dist != 3) {
        std::cerr << "After relaxing edge (a, b), distance to b must be 3, but it is " << dist << std::endl;
        result = false;
    }

    // relax (a, c) and verify distance to c has decreased to 5
    sp.relax(g["a"], g.find_edge("a", "c"));
    if (int dist = sp.get_data(g["c"])->distance(); dist != 5) {
        std::cerr << "After relaxing edge (a, c), distance to c must be 5, but it is " << dist << std::endl;
        result = false;
    }

    // relax (b, c) and verify distance to c has decreased to 4
    sp.relax(g["b"], g.find_edge("b", "c"));
    if (int dist = sp.get_data(g["c"])->distance(); dist != 4) {
        std::cerr << "After relaxing edges (a, b) and (b, c), distance to c must be 4, but it is " << dist << std::endl;
        result = false;
    }

    return result;
}

bool shortest_paths_tester::verify_paths(shortest_paths &paths) {
    for (const auto &vertex : paths.m_graph.vertices()) {
        auto distance = paths.get_data(vertex)->distance();

        for (const auto &edge : vertex.edges()) {
            const auto &target = edge.target();
            auto distance_to_target = paths.get_data(target)->distance();

            if (distance + edge.weight() < distance_to_target) {
                std::cerr << "Reported smallest distance to " << target.label() << " is " << distance_to_target;
                std::cerr << ", but taking path via " << vertex.label() << " to " << target.label();
                std::cerr << " is a shorter path!" << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool shortest_paths_tester::test_find_next_dijkstra() {
    // create a directed graph
    graph g{true};
    g.add_vertex("a");
    g.add_vertex("b");
    g.add_vertex("c");

    g.add_edge("a", "b", 3);
    g.add_edge("a", "c", 5);
    g.add_edge("b", "c", 1);

    shortest_paths sp{g};
    sp.prepare(g["a"]);

    const graph::vertex *vertex = sp.find_next_dijkstra();
    if (vertex->label() != "a") {
        std::cerr << "find_next_dijkstra expected to return vertex " << std::quoted("a") <<
                  ", but returned vertex " << std::quoted(vertex->label()) << std::endl;
        return false;
    }
    sp.relax(*vertex);
    sp.get_data(*vertex)->visit();

    vertex = sp.find_next_dijkstra();
    if (vertex->label() != "b") {
        std::cerr << "find_next_dijkstra expected to return vertex " << std::quoted("b") <<
                  ", but returned vertex " << std::quoted(vertex->label()) << std::endl;
        return false;
    }
    sp.relax(*vertex);
    sp.get_data(*vertex)->visit();

    vertex = sp.find_next_dijkstra();
    if (vertex->label() != "c") {
        std::cerr << "find_next_dijkstra expected to return vertex " << std::quoted("c") <<
                  ", but returned vertex " << std::quoted(vertex->label()) << std::endl;
        return false;
    }
    sp.relax(*vertex);
    sp.get_data(*vertex)->visit();

    vertex = sp.find_next_dijkstra();
    if (vertex != nullptr) {
        std::cerr << "find_next_dijkstra expected to return nullptr"
                  ", but returned vertex " << std::quoted(vertex->label()) << std::endl;
        return false;
    }

    return true;
}
