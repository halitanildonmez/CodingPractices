#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct GatewayNodeAndParent {
    int gatewayNode;
    int parentNode;
    int secondGateNode;
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
            int secondGate = -1;
            
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
                    if (count == 1)
                        secondGate = j;
                } // end inner if
            } // end inner for
            if (count >= 2 && count < 4) {
                GatewayNodeAndParent gp;
                gp.gatewayNode = gateNode;
                gp.parentNode = index;
                gp.containsClosestNode = containsClosestNode;
                gp.secondGateNode = secondGate;
                chokePoints.push_back(gp);
            }
        } // end if 
    }
    return chokePoints;
}

GatewayNodeAndParent getClosestNode (vector<GatewayNodeAndParent> chokePoints, int shortestPaths[]) {
    int maxDist = 0;
    GatewayNodeAndParent retVal = chokePoints[0];
    
    for (GatewayNodeAndParent cp : chokePoints) {
        if (shortestPaths[cp.parentNode] >= maxDist) {
            maxDist = shortestPaths[cp.parentNode];
            retVal = cp;
        }
    }
    
    return retVal;
}

int getMostCriticalChokePointIndex (vector<GatewayNodeAndParent> chokePoints, int shortestPaths[], int ** graph, 
                                    int N, int gatewayNodes[]) {
    GatewayNodeAndParent tmp;
    int index = -1;
    int tmpMin = 0;
    for (int i = 0; i < chokePoints.size(); i++) {
        tmp = chokePoints[i];
        
        int chokePointDangerDegree = 0;
        for (int neighOfParentNode = 0; neighOfParentNode < N; neighOfParentNode++) {
            if (graph[neighOfParentNode][tmp.parentNode] == 1 && neighOfParentNode != tmp.gatewayNode 
                && neighOfParentNode != tmp.secondGateNode) {
                
                if (graph[neighOfParentNode][tmp.gatewayNode] == 1 || graph[neighOfParentNode][tmp.secondGateNode] == 1
                    || gatewayNodes[neighOfParentNode] > 0) {
                    chokePointDangerDegree++;
                }
            }
        }
        if (chokePointDangerDegree >= tmpMin) {
            tmpMin = chokePointDangerDegree;
            index = i;
        }
    }
    return index;
}

void printClosestStruct (GatewayNodeAndParent cp, int point) {
    cerr << "NODE: " << cp.parentNode << " ----- " << cp.gatewayNode << " ---- " << cp.secondGateNode 
         << " ------- " << point << endl;
}

int getMostCriticalNode (int **map, int N, vector<GatewayNodeAndParent> chokes, int shortPaths[]) {
    
    int *arr = new int [chokes.size()];
    int min = 0;
    int selectedNodeIndex = -1;
    
    bool checkShortestPath = false;
    for (int i = 0; i < chokes.size(); i++) {
        int criticalPoint = 0;
        GatewayNodeAndParent cur = chokes[i];
        for (int j = 0; j < N; j++) {
            if (map[cur.parentNode][j] == 1) {
                for (int k = 0; k < N; k++) {
                    if (map[cur.secondGateNode][k] == 1) {
                        criticalPoint++;
                        if (map[k][cur.parentNode] == 1)
                            criticalPoint+=2;
                    }
                } // end for k
            } // end if
        } // end for j
        arr[i] = criticalPoint;
        if (min <= criticalPoint) {
            if (min == criticalPoint)
                checkShortestPath = true;
            min = criticalPoint;
            selectedNodeIndex = i;
            
        }
    }
    
    if (selectedNodeIndex == -1) {
        delete [] arr;
        return -1;   
    }
    
    if (checkShortestPath) {
        int minDistance = shortPaths[chokes[selectedNodeIndex].parentNode];
        for (int i = 0; i < chokes.size (); i++) {
            if (arr[i] == min && i != selectedNodeIndex) {
                GatewayNodeAndParent cur = chokes[i];
                if (shortPaths[cur.parentNode] < minDistance) {
                    selectedNodeIndex = i;
                    minDistance = shortPaths[cur.parentNode];
                }
            }
        }    
    }
    delete [] arr;
    arr = NULL;
    
    return selectedNodeIndex;
}

int analyzeChokePoint (GatewayNodeAndParent chokePoint, int parents[], int N, int **graph, int gatewayNodes[], int SI) {
    int curParent = chokePoint.parentNode;
    int turnNeededToAct = 1;
    
    for (int i = 0; i < N; i++) {
        int par = parents[curParent];
        
        for (int j = 0; j < N; j++) {
            if (graph[j][par] == 1 && gatewayNodes[j] > 0 && j != SI) {
                turnNeededToAct++;
            } 
        }
        curParent = par;
        if (curParent == SI)
            break;
    }
    return turnNeededToAct;
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
    
    int shortestPaths[N];
    int parents[N];
    
    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();
        
        dijsktra (map, SI, N, shortestPaths, parents);
        
        int closestGatewayNode = findNodeWithShortestPath (map, shortestPaths, N, gatewayNodes);
        int distanceToClosestNode = shortestPaths[closestGatewayNode];
        int parentNodeOfGatewayNode = parents[closestGatewayNode];
        
        vector<GatewayNodeAndParent> chokes = findClosestChokePoint(map, gatewayNodes, N, closestGatewayNode);
        GatewayNodeAndParent urgent;
        bool foundUrgent = false;
        for (int h = chokes.size() - 1; h >= 0; h--) {
            GatewayNodeAndParent test = chokes[h];
            if (analyzeChokePoint (test, parents, N, map, gatewayNodes, SI) == shortestPaths[test.parentNode]) {
                cerr << "Urgent node found " << test.parentNode << " ---- " << shortestPaths[test.parentNode] <<endl;
                urgent = test;
                foundUrgent = true;
                break;
            }
        }
        
        int mostCriticalNodeIndex = getMostCriticalChokePointIndex(chokes, shortestPaths, map, N, gatewayNodes);
        int testCompareIndex = getMostCriticalNode(map, N, chokes, shortestPaths);
        
        int gateX, gateY;
        if (distanceToClosestNode < 2) {
            // we need to cut the closest node
            gateX = parentNodeOfGatewayNode;
            gateY = closestGatewayNode;
        } else {
            if (chokes.size() > 0) {
                int minDist = 500;
                int chokeIndex = -1;
                for (int i = 0; i < chokes.size (); i++) {
                    GatewayNodeAndParent tmp = chokes[i];
                    if (shortestPaths[tmp.parentNode] <= minDist) {
                        chokeIndex = i;
                        minDist = shortestPaths[tmp.parentNode];
                    }
                }
                if (minDist < 3) {
                    gateX = chokes[chokeIndex].parentNode;
                    gateY = chokes[chokeIndex].gatewayNode;
                } 
                else if (foundUrgent) {
                    gateX = urgent.parentNode;
                    gateY = urgent.gatewayNode;
                }
                else if (mostCriticalNodeIndex != -1) {
                    gateX = chokes[mostCriticalNodeIndex].parentNode;
                    gateY = chokes[mostCriticalNodeIndex].gatewayNode;
                } 
                else if (testCompareIndex != -1) {
                    gateX = chokes[testCompareIndex].parentNode;
                    gateY = chokes[testCompareIndex].gatewayNode;
                }
            }
        }
        
        map[gateX][gateY] = -1;
        map[gateY][gateX] = -1;
        
        cout << gateX << " " << gateY << endl;
    }
}