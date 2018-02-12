#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int minDistance (int dist[], bool visited[], int N) {
    int min = 500;
    int minIndex = -1;
    for (int i = 0; i < N; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijsktra (int ** graph, int source, int N, int dist[], int parents[]) {

    bool visited[N];
    int distances[N];
    int parent[N];
    for (int i = 0; i < N; i++) {
        distances[i] = 500;
        visited[i] = false;
        dist[i] = 0;
        parents[i] = 0;
    }
    
    distances[source] = 0;
    
    for (int i = 0; i < N-1; i++) {
        int selectedNode = minDistance (distances, visited, N);
        visited[selectedNode] = true;
        for (int j = 0; j < N; j++) {
            if (!visited[j] && graph[selectedNode][j] >= 1 
                    && distances[selectedNode] + graph[selectedNode][j] < distances[j]) {
                parent[j] = selectedNode;
                parents[j] = selectedNode;
                
                distances[j] = graph[selectedNode][j] + distances[selectedNode];
                dist[j] = distances[j];
                
            }
        }
    }
}

int findNodeWithShortestPath (int nodes[], int N, int gateways[]) {
    int min = 500;
    int index = -1;
    for (int i = 0; i < N; i++) {
        if (min >= nodes[i] && gateways[i] == 1) {
            min = nodes[i];
            index = i;
        }
    }
    return index;
}

int findClosestChokePoint (int ** graph, int gatewayNodes[], int N, int closestNode) {
    for (int i = 0; i < N; i++) {
        if (gatewayNodes[i] == 1) {
            // neighs of the gateway node
            for (int j = 0; j < N; j++) {
                if (graph[i][j] == 1)  {
                    for (int k = 0; k < N; k++) {
                        if (graph[j][k] == 1 && gatewayNodes[k] == 1 && closestNode == i) {
                            return j;
                        }
                    }    
                }
            }
        }
    }
    return -1;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    cin >> N >> L >> E; cin.ignore();
    
    int gatewayNodes[N];
    
    int **map;
    map = new int *[N];
    for(int i = 0; i < N; i++) {
        map[i] = new int[N];   
        gatewayNodes[i] = 0;
    }

    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
        map[N1][N2] = 1;
        map[N2][N1] = 1;
    }
    
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        gatewayNodes[EI] = 1;
    }
    

    bool isFirstIteration = true;
    int shortestPaths[N];
    int parents[N];
    
    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
        dijsktra (map, SI, N, shortestPaths, parents);
        
        int closestGatewayNode = findNodeWithShortestPath (shortestPaths, N, gatewayNodes);
        cerr << "Closest gateway node " << closestGatewayNode << endl;
        
        int chokes = findClosestChokePoint(map, gatewayNodes, N, closestGatewayNode);
        cerr << "Choke point: " << chokes << endl;
        
        int gateX, gateY;
        if (chokes == -1) {
            // we are not in danger
            gateX = parents[closestGatewayNode];
            gateY = closestGatewayNode;
        } else {
            gateX = chokes;
            gateY = 12;
        }
        
        cout << gateX << " " << gateY << endl;
    }
}