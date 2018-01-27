#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;

int distToStart (int start, int end, vector<int> adjGraph[], int N, vector<int> nodes, int &p) {
    int *distances = new int[N];
    bool *visited = new bool [N];
    vector <int> prev[N];
    for (int i = 0; i < N; i++) {
        distances[i] = 500;
        visited[i] = false;
    }
    
    distances [start] = 0;

    while (!nodes.empty()) {
        int minDist = 500;
        int curNode = -1;
        int delIndex = -1;
        for (int i = 0; i < nodes.size (); i++) {
            int n = nodes[i];
            if (distances[n] < minDist && !visited[n]) {
                curNode = n;
                minDist = distances[n];
                delIndex = i;
            }
        }
        if (delIndex == -1)
            break;
        if (curNode == end) {
            break;
        }
        nodes.erase (nodes.begin () + delIndex);
        visited[curNode] = true;
        vector<int> neighs = adjGraph[curNode];
        for (int i = 0; i < neighs.size(); i++) {
            int newDist = distances[curNode] + 1;
            if (newDist < distances[neighs[i]]) {
                distances[neighs[i]] = newDist;
                prev[neighs[i]].push_back(curNode);
            }
        }
    }
    cerr << "start" << start << " end " << end << endl;
    int retVal = distances[end];
    p = prev[end][0];
    cerr << "SADASD " << p << endl;
    for (int i = 0; i < N; i++) {
        vector<int> tmpVexc = prev[i];
        cerr << "for " << i << " ";
        for (int j = 0; j < tmpVexc.size (); j++) {
            cerr << tmpVexc[j];
            if (tmpVexc[j] == end) {
                p = tmpVexc[j];
                cerr << p << " PP " << endl;
                break;
            }
        }
        cerr << endl;
    }
    delete[]distances;
    delete[]visited;
    return retVal;
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
    
    bool *visited = new bool [N];
    
    vector<int> adjGraph[N]; 
    vector<int> gatewayNode;
    vector<int> nodes (N);
    
    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
        adjGraph[N1].push_back(N2);
        adjGraph[N2].push_back(N1);
        visited[N1] = false;
    }
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        gatewayNode.push_back(EI);
        
    }
    
    for (int i = 0; i < N; i++) {
        nodes.push_back(i);
    }
    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();
        int minVal = 500;
        int gateX = -1;
        int gateY = -1;
        int hh = -1;
        for (int i = 0; i < E; i++) {
            int curVal = distToStart(SI, gatewayNode[i], adjGraph, N, nodes, gateY);
            int gIndex = gatewayNode[i];
            if (curVal < minVal && (!visited[gateY])) {
                minVal = curVal;
                gateX = gatewayNode[i];
                hh = gateY;
            }
        }
        visited [gateY] = true;
        cout << gateX << " " << hh << endl;
   
    }
}