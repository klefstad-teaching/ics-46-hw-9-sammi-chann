#include "dijkstras.h"

int main(int argc, char *argv[]) {
    string filename = get_arg(argc, argv, "../src/small.txt");
    Graph G;

    vector<int> dijkstras_distances;
    vector<int> previous;
    vector<int> path;

    file_to_graph(filename, G);

    cout << filename << endl;
    for (vector<Edge> edge_list : G)
    {
        for (Edge edge : edge_list)
            cout << edge << " ";
        cout << endl;
    }
    dijkstras_distances = dijkstra_shortest_path(G, 0, previous);
    for (int i = 0; i < G.numVertices; ++i)
    {
        cout << "Path to vertex " << i << ":\n";
        path = extract_shortest_path(dijkstras_distances, previous, i);
        print_path(path, dijkstras_distances[i]);
        cout << endl;
    }
    return 0;
}

