#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;

int findMin (int *arr, int N) {
    int maxVal = 100;
    int index = -1;
    for (int i = 0; i < N; i++) {
        if (arr [i] < maxVal) {
            maxVal = arr [i];
            index = i;
        }
    }
    return index;
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
    
    //Graph graph (N);
    vector<int> adjGraph[N]; 
    vector<int> gatewayNode;
    
    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
        adjGraph[N1].push_back(N2);
        adjGraph[N2].push_back(N1);
    }
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        gatewayNode.push_back(EI);
    }
    
    vector<int> q;
    bool *visited = new bool[N];
    int *distances = new int [N];
    for(int i = 0; i < N; i++) {
        visited[i] = false;
        distances [i] = 100;
        q.push_back (i);
    }
        
    
    int startNode = gatewayNode[0];
    
    
    vector<int> prev[N];
    distances[startNode] = 0;
    
    visited[startNode] = true;
    
    while (!q.empty()) {
        int u = findMin (distances, N);
        vector <int>::iterator minElem = q.begin();
        minElem = std::find (q.begin (), q.end(), u);
        if (minElem != q.end ()) {
            q.erase (q.begin () + std::distance (q.begin (), minElem));
        }
        for (std::vector<int>::iterator it = adjGraph[u].begin() ; it != adjGraph[u].end(); ++it) {
            int dist = distances [u] + 1;
            if (dist < distances [*it]) {
                distances [*it] = dist;
                prev [*it].push_back(u);
            }
        }
    }
    
    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();
        
        bool alreadySevered = false;
        vector <int> placesAgentCanGo = adjGraph [SI];
        int index = 0;
        for (std::vector<int>::iterator it = placesAgentCanGo.begin() ; it != placesAgentCanGo.end(); ++it) {
            int y = *it;
            if (std::find(gatewayNode.begin(), gatewayNode.end(), y) != gatewayNode.end()) {
                index = y;
                alreadySevered = true;
                break;
            }
        }
        if (alreadySevered) {
            cout << SI << " " << index << endl;
        }
        else{
            std::queue<int> queue;
            cerr << "entered here for " << SI << endl;

            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;
            // Example: 3 4 are the indices of the nodes you wish to sever the link between
            cout << gatewayNode.at (0) << " " << adjGraph[gatewayNode.at (0)][0] << endl;   
        }
 
    }
}
/*
            queue.push(SI);
            visited [SI] = true;
            while (!queue.empty()) {
                int cur = queue.front();
                queue.pop ();
                if (std::find(gatewayNode.begin(), gatewayNode.end(), cur) != gatewayNode.end()) {
                    vector<int> allAdj = adjGraph[cur];
                    int tmp = allAdj.at (0);
                    for (std::vector<int>::iterator it2 = allAdj.begin() ; it2 != allAdj.end(); ++it2) {
                        int curNeigh = *it2;
                        if ( curNeigh == SI) {
                            tmp = curNeigh;
                        }
                    }
                    if (!alreadySevered) {
                        cerr << "HUH" << endl;
                        cout << cur << " " << tmp << endl;
                    }
                        
                }
                
                vector <int> adjacentNodes = adjGraph[cur];
                for (std::vector<int>::iterator it3 = adjacentNodes.begin() ; it3 != adjacentNodes.end(); ++it3) {
                    int neigh = *it3;
                    if (!visited[neigh]) {
                        queue.push (neigh);
                        visited [neigh] = true;
                    }
                }
                
            }
*/
/*
            queue.push(SI);
            visited [SI] = true;
            while (!queue.empty()) {
                int cur = queue.front();
                queue.pop ();
                if (std::find(gatewayNode.begin(), gatewayNode.end(), cur) != gatewayNode.end()) {
                    vector<int> allAdj = adjGraph[cur];
                    int tmp = allAdj.at (0);
                    for (std::vector<int>::iterator it2 = allAdj.begin() ; it2 != allAdj.end(); ++it2) {
                        int curNeigh = *it2;
                        if ( curNeigh == SI) {
                            tmp = curNeigh;
                        }
                    }
                    if (!alreadySevered) {
                        cerr << "HUH" << endl;
                        cout << cur << " " << tmp << endl;
                    }
                        
                }
                
                vector <int> adjacentNodes = adjGraph[cur];
                for (std::vector<int>::iterator it3 = adjacentNodes.begin() ; it3 != adjacentNodes.end(); ++it3) {
                    int neigh = *it3;
                    if (!visited[neigh]) {
                        queue.push (neigh);
                        visited [neigh] = true;
                    }
                }
                
            }
*/