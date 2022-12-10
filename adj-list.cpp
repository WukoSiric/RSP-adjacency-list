#include <iostream> 
#include <list> 
#include <vector>
// Undirected graph using adjacency list
class Graph {
    int num_vertices;
    std::vector<std::list<int>> adj_list;
public: 
    std::vector<std::list<int>> * get_adj_list() {
        return &(this->adj_list);
    }

    Graph(int v) {
        this->num_vertices = v;
        this->adj_list.resize(v);
    }

    void add_edge(int src, int dest) {
        this->adj_list[src].push_back(dest);
        this->adj_list[dest].push_back(src);
    }
};

// Print Adj List Function
void print_graph(std::vector<std::list<int>> * adj_list) {
    for (int i = 0; i < adj_list->size(); i++) {
        std::cout << "VERTEX " << i << ":";
        for (auto x : (*adj_list)[i]) {
            std::cout << " -> " << x;
        }
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "Welcome to my graph program!" << std::endl;
    std::cout << "Creates an undirected graph, has BFS so far..." << std::endl;
    Graph g(5);
    g.add_edge(0, 1);
    g.add_edge(0, 4);
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 4);

    // Get adj list 
    print_graph(g.get_adj_list());
    return 0;
}