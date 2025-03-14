#include "dijkstras.h"

// other functions
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    vector<int> distances(G.numVertices, INF);
    vector<bool> visit_status(G.numVertices, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, comp_vertex_weight> pq; // pair<vertex, distance>

    distances[source] = 0;
    previous.assign(G.numVertices, -1);
    pq.push({source, 0});

    while (!pq.empty())
    {
        int current = pq.top().first;
        pq.pop();

        if (!visit_status[current])
        {
            visit_status[current] = true;
            for (Edge adjacent: G[current])
            {
                int v = adjacent.dst;
                if (!visit_status[v] && (distances[current] + adjacent.weight < distances[v]))
                {
                    distances[v] = distances[current] + adjacent.weight;
                    previous[v] = current;
                    pq.push({v, distances[v]});
                }
            }
        }
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    vector<int> path;
    for (int i = destination; i != -1; i = previous[i])
        path.push_back(i);
    reverse(path.begin(), path.end());
    return path;
}
void print_path(const vector<int>& v, int total)
{
    for (int edge: v)
        cout << edge << " ";
    cout << "\nTotal cost is " << total << endl;
    
}
string get_arg(int argc, char *argv[], string def)
{
    return (argc > 1) ? string(argv[1]) : def;
}