//
// Created by rgr24 on 18/05/2021.
//

#ifndef GRAPHS_FULL_GRAPH_H
#define GRAPHS_FULL_GRAPH_H

#include <ostream>
#include <string>
#include <vector>
#include <map>

class graph {
public:
    class vertex;

    class edge {
        friend class graph;
    public:
        int weight() const;
        const graph::vertex& source() const;
        const graph::vertex& target() const;
    private:
        edge(const graph* g, int source, int target, int weight);

        const graph *m_graph;
        int m_source;
        int m_target;
        int m_weight;
    };

    class vertex {
        friend class graph;

    public:
        int id() const;
        const std::string &label() const;
        const std::string &colour() const;

        const std::vector<edge> &edges() const;
        std::vector<edge> &edges();

    private:
        vertex(const std::string &label, int id);

        std::string m_label;
        int m_id;
        std::string m_colour{"white"};
        std::vector<edge> m_edges;
    };

    graph(bool is_directed);

    bool is_directed() const;
    int num_vertices() const;
    const std::vector<vertex> &vertices() const;
    int num_edges() const;

    int add_vertex(std::string label);
    void add_edge(std::string from, std::string to, int weight);

    const vertex& find_vertex(const std::string& label) const;
    const vertex& operator[](const std::string& label) const;
    const edge& find_edge(const std::string& label_from, const std::string& label_to) const;

    void colour_vertex(const std::string& label, const std::string& colour = "black");
    bool has_cycle() const;

    bool to_dot(const std::string& filename) const;
private:
    int find_id(const std::string &label) const;

    std::map<std::string, int> m_label_to_id;
    std::vector<vertex> m_vertices;

    int m_num_edges{}, m_num_vertices{};
    bool m_directed;
};

#endif //GRAPHS_FULL_GRAPH_H
