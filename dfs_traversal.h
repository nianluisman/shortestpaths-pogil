//
// Created by rgr24 on 29/05/2021.
//

#ifndef GRAPHS_FULL_DFS_TRAVERSAL_H
#define GRAPHS_FULL_DFS_TRAVERSAL_H

#include <unordered_map>
#include <vector>
#include "graph.h"

class dfs_traversal {
public:
    dfs_traversal(const graph::vertex& start);
    void run();

    bool cycle_found() const;
    const std::vector<std::string>& pre_order() const;
    const std::vector<std::string>& post_order() const;
private:
    bool dfs(const graph::vertex& v);
    const graph::vertex& m_start;
    bool m_has_run;
    bool m_cyclic;
    std::unordered_map<std::string, int> m_visited;
    std::vector<std::string> m_pre_order;
    std::vector<std::string> m_post_order;
};


#endif //GRAPHS_FULL_DFS_TRAVERSAL_H
