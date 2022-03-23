//
// Created by rgr24 on 29/05/2021.
//

#include "dfs_traversal.h"
#include <exception>

dfs_traversal::dfs_traversal(const graph::vertex &start)
: m_start{start}, m_has_run{false} {

}

void dfs_traversal::run() {
    m_visited.clear();
    m_pre_order.clear();
    m_post_order.clear();

    m_cyclic = dfs(m_start);
    m_has_run = true;
}

bool dfs_traversal::cycle_found() const {
    if (!m_has_run)
        throw std::logic_error("Must call run() first!");

    return m_cyclic;
}

const std::vector<std::string> &dfs_traversal::pre_order() const {
    return m_pre_order;
}

const std::vector<std::string> &dfs_traversal::post_order() const {
    return m_post_order;
}

bool dfs_traversal::dfs(const graph::vertex &v) {
    bool cycle_found = false;
    m_visited[v.label()] = 1;
    m_pre_order.push_back(v.label());
    for (const auto& edge : v.edges()) {
        const auto& target = edge.target();
        auto kv_pair = m_visited.find(target.label());
        if (kv_pair == m_visited.end()) {
            cycle_found = dfs(target) || cycle_found;
        }
        else if (kv_pair->second == 1) {
            cycle_found = true;
        }
    }
    m_visited[v.label()] = 2;
    m_post_order.push_back(v.label());
    return cycle_found;
}
