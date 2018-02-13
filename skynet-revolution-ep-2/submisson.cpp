#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct GatewayNodeAndParent {
    int gatewayNode;
    int parentNode;
    bool containsClosestNode;
};

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
                distances[j] = graph[selectedNode][j] + distances[selectedNode];
                
                dist[j] = distances[j];
                parents[j] = selectedNode;
            }
        }
    }
}

/**
 Find the gateway nodes with shortest path
*/
int findNodeWithShortestPath (int ** graph, int nodes[], int N, int gateways[]) {
    int min = 500;
    int index = -1;
    for (int i = 0; i < N; i++) {
        if (min >= nodes[i] && gateways[i] == 1 && nodes[i] > 0) {
            min = nodes[i];
            index = i;
        }
    }
    return index;
}

vector<GatewayNodeAndParent> findClosestChokePoint (int ** graph, int gatewayNodes[], int N, int closestNode) {
    vector<GatewayNodeAndParent> chokePoints;
    for (int i = 0; i < N; i++) {
        if (gatewayNodes[i] != 1) {
            int count = 0;
            int index = -1;
            int gateNode = -1;
            bool containsClosestNode = false;
            for (int j = 0; j < N; j++) {
                if (graph[i][j] > 0 && gatewayNodes[j] == 1) {
                    count++;
                    // parent of the gate node
                    index = i;
                    // gate node. 
                    gateNode = j;
                    if (gateNode == closestNode)
                        containsClosestNode = true;
                } // end inner if
            } // end inner for
            if (count >= 2 && count < 4) {
                GatewayNodeAndParent gp;
                gp.gatewayNode = gateNode;
                gp.parentNode = index;
                gp.containsClosestNode = containsClosestNode;
                
                chokePoints.push_back(gp);
            }
        } // end if 
    }
    return chokePoints;
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
        
        dijsktra (map, SI, N, shortestPaths, parents);
        
        /*cerr << " ---- SHORTEST PATHS ---- " << endl;
        for (int i = 0; i < N; i++)
            cerr << i << " " << shortestPaths[i] << endl;
        cerr << " ---- SHORTEST PATHS END ---- " << endl;*/
        
        int closestGatewayNode = findNodeWithShortestPath (map, shortestPaths, N, gatewayNodes);
        int distanceToClosestNode = shortestPaths[closestGatewayNode];
        int parentNodeOfGatewayNode = parents[closestGatewayNode];
        
        cerr << "Closest gateway node " << closestGatewayNode << " distance to it is " << distanceToClosestNode << endl;
        cerr << "Dijkstra previous node: " << parentNodeOfGatewayNode << endl;
        
        vector<GatewayNodeAndParent> chokes = findClosestChokePoint(map, gatewayNodes, N, closestGatewayNode);
        
        // TODO: if distance < 2 we need to cut the link to the closest node
        // TODO: if not we need to check the choke points and cut from there
        int gateX, gateY;
        if (distanceToClosestNode < 2) {
            // we need to cut the closest node
            gateX = parentNodeOfGatewayNode;
            gateY = closestGatewayNode;
        } else {
            if (chokes.size() > 0) {
                bool foundAMatch = false;
                for (GatewayNodeAndParent gp : chokes) {
                    if (gp.containsClosestNode) {
                        cerr << "found a choke point which is a close node " << gp.parentNode << endl;
                        gateX = gp.parentNode;
                        gateY = gp.gatewayNode;
                        foundAMatch = true;
                        break;
                    }    
                }
                if (!foundAMatch) {
                    // we can chill and there is a choke point to cut
                    GatewayNodeAndParent choke = chokes[0];
                    gateX = choke.parentNode;
                    gateY = choke.gatewayNode;    
                }
            }
        }
        
        map[gateX][gateY] = -1;
        map[gateY][gateX] = -1;
        
        cout << gateX << " " << gateY << endl;
    }
}