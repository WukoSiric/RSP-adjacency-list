#include <iostream> 
#include <list> 
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include "vector_utils.cpp"

enum STATE {UNDISCOVERED, DISCOVERED, PROCESSED};
class Graph {
    int num_vertices;
    std::vector<std::list<int>> adj_list;
public: 
    int get_num_vertices() {
        return this->num_vertices;
    }

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

class GraphSearch {
public:
    void print_graph(std::vector<std::list<int>> * adj_list) {
        for (int i = 0; i < adj_list->size(); i++) {
            std::cout << "VERTEX " << i << ":";
            for (auto x : (*adj_list)[i]) {
                std::cout << " -> " << x;
            }
            std::cout << std::endl;
        }
    }

    std::pair<std::vector<int>, std::vector<int>> BFS(Graph * graph, int start) {
        // Array of enums 
        std::vector<int> process_order;
        std::vector<STATE> vertex_states(graph->get_num_vertices(), UNDISCOVERED);
        std::vector<int> vertex_parents(graph->get_num_vertices(), -1); //Parent list for each node, size-1 because start node has no parent 

        // Creating a queue
        std::queue<int> q;

        // Marking first as visited, adding to queue 
        vertex_states[start] = DISCOVERED;
        vertex_parents[start] = -1;
        q.push(start);

        std::vector<std::list<int>> * adj_list = graph->get_adj_list();
        while(!q.empty()) {
            int current = q.front();
            q.pop(); 
            // Processing node
            process_order.push_back(current);
            for (auto x : (*adj_list)[current]) {
                // Could process edge here
                if (vertex_states[x] == UNDISCOVERED) {
                    vertex_states[x] = DISCOVERED;
                    vertex_parents[x] = current; 
                    q.push(x);
                }
            }
            vertex_states[current] = PROCESSED;
            // Do after processing here
        }
        return std::pair(process_order, vertex_parents); 
    }
    void DFS(Graph * graph, int start) {
        std::vector<STATE> vertex_states(graph->get_num_vertices(), UNDISCOVERED);

        //Creating a stack
        std::stack<int> s;

        // Mark first as visited, add to stack 
        vertex_states[start] = DISCOVERED; 
        s.push(start); 

        std::vector<std::list<int>> * adj_list = graph->get_adj_list(); 
        while(!s.empty()) {
            int current = s.top(); 
            s.pop(); 
            std::cout << current << " ";
            // Exploring adjacent nodes
            for (auto x : (*adj_list)[current]) {
                if (vertex_states[x] == UNDISCOVERED) {
                    vertex_states[x] = DISCOVERED; 
                    s.push(x); 
                }
            }
            vertex_states[current] = PROCESSED;
        }
    }

    void find_path(int start, int end, std::vector<int> parents) {
        if ((start == end) || (end == -1)) {
            std::cout << start;
        } else {
            find_path(start, parents[end], parents);
            std::cout << " " << end;
        }
    }
};

// Print Adj List Function


int main() {
    std::cout << "Welcome to my graph program!" << std::endl;
    std::cout << "Creates an undirected graph, has BFS so far..." << std::endl;

    // Creating the graph
    Graph g(10);
    g.add_edge(0, 1);
    g.add_edge(0, 4);
    g.add_edge(4, 5);
    g.add_edge(5, 6);
    g.add_edge(6, 7);
    g.add_edge(6, 3);
    g.add_edge(7, 8);
    g.add_edge(8, 9);
    g.add_edge(9, 2);

    // Doing BFS, storing results
    GraphSearch gs;
    std::pair<std::vector<int>, std::vector<int>> bfs_result = gs.BFS(&g, 0);
    std::vector<int> order = bfs_result.first;
    std::vector<int> parents = bfs_result.second;

    // Printing results
    std::cout << "BFS Order:    ";
    print_vector(order);
    std::cout << "BFS Parents: ";
    print_vector(parents);
    // gs.find_path(0, 2, parents);

    std::cout << "DFS: "; 
    gs.DFS(&g, 0);
    std::cout << std::endl;

    return 0;
}