#include "graph.h"
#include "vertex.h"
#include <exception>
#include <fstream>
#include <iomanip>
#include "colours.h"

bool graph::is_directed() const {
    return m_directed;
}

int graph::num_vertices() const {
    return m_vertices.size();
}

int graph::num_edges() const {
    return m_num_edges;
}

int graph::add_vertex(std::string label) {
    if (m_label_to_id.find(label) != m_label_to_id.end())
        throw new std::invalid_argument("Vertex with label \"" + label + "\" already exists");

    m_label_to_id[label] = m_num_vertices;
    m_vertices.push_back(graph::vertex{label, m_num_vertices});
    m_num_vertices++;

    return 0;
}

void graph::add_edge(std::string from, std::string to, int weight) {
    // lookup source
    int source_id = find_id(from);

    // lookup target
    int target_id = find_id(to);

    // add edge (source -> to)
    m_vertices[source_id].m_edges.push_back(graph::edge{this, source_id, target_id, weight});

    if (!m_directed) {
        // add an edge from 'to' to from
        m_vertices[target_id].m_edges.push_back(graph::edge{this, target_id, source_id, weight});
    }
    m_num_edges++;
}

const std::vector<graph::vertex> &graph::vertices() const {
    return m_vertices;
}

int graph::find_id(const std::string &label) const {
    auto entry = m_label_to_id.find(label);
    if (entry == m_label_to_id.end())
        throw std::invalid_argument("No vertex with label " + label + " present");

    return entry->second;
}

const graph::vertex &graph::find_vertex(const std::string &label) const {
    return m_vertices[find_id(label)];
}

const graph::vertex & graph::operator[](const std::string &label) const {
    return m_vertices[find_id(label)];
}

const graph::edge & graph::find_edge(const std::string &label_from, const std::string &label_to) const {
    const auto& from = find_vertex(label_from);
    const auto& to = find_vertex(label_to);
    for (const auto& edge : from.edges()) {
        if (edge.m_target == to.m_id)
            return edge;
    }

    throw std::invalid_argument("No edge (" + label_from + "," + label_to + ") present");
}

bool graph::to_dot(const std::string &filename) const {
    std::ofstream file{filename};
    if (file.is_open()) {
        file << "digraph g {" << std::endl
             << "\trankdir = LR;"
             << "\tnode[shape=oval style=filled];" << std::endl;

        // go over vertices, emit their label and colour
        for (const auto &v : m_vertices) {
            file << "\t" << v.label() << "[label=" << std::quoted(v.label())
                 << ", fillcolor=" << std::quoted(v.colour()) << "];" << std::endl;
        }

        // go over edges
        file << std::endl << "\tedge[dir = " << (m_directed ? "forward" : "none") << "];" << std::endl;
        for (const auto &v : m_vertices) {
            for (const auto &edge : v.m_edges) {
                if (m_directed || v.label() < edge.target().label())
                    file << "\t" << v.label() << " -> " << edge.target().label() << ";" << std::endl;
            }
        }
        file << "}" << std::endl;
        return true;
    } else
        return false;
}

void graph::colour_vertex(const std::string &label, const std::string &colour) {
    m_vertices[find_id(label)].m_colour = colour;
}

graph::graph(bool is_directed)
        : m_num_edges{0},
          m_num_vertices{0},
          m_directed{is_directed} {
}

int graph::edge::weight() const {
    return m_weight;
}

const graph::vertex &graph::edge::source() const {
    return m_graph->m_vertices[m_source];
}

const graph::vertex &graph::edge::target() const {
    return m_graph->m_vertices[m_target];
}

graph::edge::edge(const graph *g, int source, int adjacent_vertex, int weight)
        : m_graph{g},
          m_source{source},
          m_target{adjacent_vertex},
          m_weight{weight} {

}

graph::vertex::vertex(const std::string &label, int id)
        : m_label{label},
          m_id{id},
          m_colour{colour::white} {

}

const std::string &graph::vertex::label() const {
    return m_label;
}

const std::vector<graph::edge> &graph::vertex::edges() const {
    return m_edges;
}

std::vector<graph::edge> &graph::vertex::edges() {
    return m_edges;
}

const std::string &graph::vertex::colour() const {
    return m_colour;
}

int graph::vertex::id() const {
    return m_id;
}
