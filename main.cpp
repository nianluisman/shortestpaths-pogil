#include <iostream>
#include "graph.h"
#include "example_graphs.h"
#include "shortest_paths.h"
#include "shortest_paths_tester.h"

int main() {
    // Activity 2: edge relaxation
    shortest_paths_tester::test_relax();

    // Comment out...

    {
        // Activity 3, 4: acyclic graphs
        graph g = acyclic_graph();
        shortest_paths sp{g};
        sp.compute(g["a"]);
        sp.to_dot("activity-4.dot");

        if (shortest_paths_tester::verify_paths(sp)) {
            std::cerr << "Shortest paths are correct for acyclic graphs!" << std::endl;
        }
    }

    {
        // Activity 5 : apply topological order to two cyclic graphs
        graph g1 = cyclic_1();
        shortest_paths sp1{g1};
        sp1.compute(g1["a"]);
        sp1.to_dot("activity-5a.dot");

        graph g2 = cyclic_2();
        shortest_paths sp2{g2};
        sp2.compute(g2["a"]);
        sp2.to_dot("activity-5b.dot");
    }


    {
        // Activity 7, 9, 10: different implementations of Dijkstra
        shortest_paths_tester::test_find_next_dijkstra();

        graph g = cyclic_3();
        shortest_paths sp{g};
        sp.compute(g["a"]);
        sp.to_dot("dijkstra.dot");

        if (shortest_paths_tester::verify_paths(sp)) {
            std::cerr << "Shortest paths are correct for cyclic graph!" << std::endl;
        }
    }
    return 0;
}
