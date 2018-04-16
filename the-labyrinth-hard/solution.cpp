#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
using namespace std;

#define RIGHT "RIGHT"
#define LEFT "LEFT"
#define UP "UP"
#define DOWN "DOWN"

int rowNum[] = { -1, 0, 0, 1 };
int colNum[] = { 0, -1, 1, 0 };

struct Node {
    int row;
    int col;
    // for BFS
    bool visited;
    // for random traversal
    bool random_visited;
    // for second pass random, detect cycles
    bool random_visited_again;
    int type;
    
    // a star structs. At the moment, just for test
    int fScore;
    int gScore;
    int prevRow, prevCol;
    int priority;
    
    inline bool operator==(const Node &left) {
        return row == left.row && col == left.col;
    }
    inline bool operator< (const Node &left) const {
        return left.fScore > fScore;
    }
};

// for using with the vector min element
bool minElemFunction (Node i, Node j) {
    return i.fScore < j.fScore;
}

/**
BFS implementation. Will return the start node if nothing is found.

@param graph graph with nodes
@param R Row
@param C Col
@param tx Start position row
@param ty Start position col
@param sx Current position row
@param sy Current position col

@return Found node. We are looking for the C here.
*/
Node BFS_Search (Node **graph, int R, int C, int tx, int ty, int sx, int sy) {
    Node startNode = graph[sx][sy];
    queue<Node> q;
    q.push(startNode);
    while (!q.empty()) {
        Node n = q.front();
        int val = n.type;
        if (val == 10) {
            // found the control room
            return n;
        }
        n.visited = true;
        q.pop();
        // traverse the neighbours. Have 4 possible move
        for (int i = 0; i < 4; i++) {
            int neigh_row = rowNum[i] + n.row;
            int neigh_col = colNum[i] + n.col;
            // be safe. Check the indicies. TODO: should not be needed maybe ?
            if ((neigh_row >= 0 && neigh_row < R) && (neigh_col >= 0 && neigh_col < C)) {
                Node neigh_val = graph [neigh_row][neigh_col];
                if (!neigh_val.visited && neigh_val.type > 0) {
                    graph [neigh_row][neigh_col].visited = true;
                    neigh_val.visited = true;
                    q.push(neigh_val);
                }
            }
        }
    }
    return startNode;
}

int manhattanDistance (int sx, int sy, int gx, int gy) {
    return abs (sx - gx) + abs (sy - gy);
}

// from 2d to 1D coord. Used to store integer indicies for nodes
int transformCoord(int x, int y, int width) {
    return x + (y * width);
}

int detransformX (int oneDCoord, int W) {
    return oneDCoord % W;
}

int detransformY (int oneDCoord, int W) {
    return oneDCoord / W;
}

Node astar_pathfind (Node **graph, int R, int C, int gx, int gy, int sx, int sy, map<int, int> &cameFrom) {
    Node start = graph[sx][sy];
    int startNodeTransPos = transformCoord (sx, sy, R);
    
    set<Node> closedSet;
    int *gScores = new int [R*C];
    for (int i = 0; i < R*C; i++) {
        gScores[i] = 10000;
    }
    gScores[startNodeTransPos] = 0;
    
    priority_queue<Node> pq;
    start.fScore = manhattanDistance(sx,sy,gx,gy);
    pq.push(start);
    
    while (!pq.empty()) {
        Node cur = pq.top ();
        if (cur.row == gx && cur.col == gy) {
            cerr << "FOUND SOL" <<endl;
            int transG = transformCoord(gx,gy,R);
            int curN = cameFrom[transG];
            int prevX = detransformX (curN,R);
            int prevY = detransformY (curN,R);
            return graph[prevX][prevY];
        }
        pq.pop();
         // traverse the neighbours. Have 4 possible move
        for (int i = 0; i < 4; i++) {
            int neigh_row = rowNum[i] + cur.row;
            int neigh_col = colNum[i] + cur.col;
            // be safe. Check the indicies. TODO: should not be needed maybe ?
            if ((neigh_row >= 0 && neigh_row < R) && (neigh_col >= 0 && neigh_col < C)) {
                Node next = graph [neigh_row][neigh_col];
                if (next.type > 0) {
                    int newCost = gScores[transformCoord (cur.row, cur.col, R)] + 1;
                    if (newCost < gScores[transformCoord (next.row, next.col, R)] ) {
                        int newF = newCost + manhattanDistance(next.row,next.col,gx,gy);
                        gScores[transformCoord(next.row, next.col, R)] = newCost;
                        next.fScore = newF;
                        pq.push(next);
                        cameFrom[transformCoord(next.row, next.col, R)] = transformCoord (cur.row, cur.col, R);
                    }
                }
            }
        }       
    }
    
    cerr << "EPIC FAIL" << endl;
    return start;
}

/**
Helper method to get the direciton string. 

@param foundNode node we have found doing something (after bfs, random traversal etc)
@param KR player pos Row
@param KC player pos Col

@return string either up down left right or none
*/
string getDirection (Node foundNode, int KR, int KC) {
    string direction;
    int rr = foundNode.row - KR;
    int rc = foundNode.col - KC;
    if (rr == 0) {
        // can only be up or down
        return rc < 0 ? LEFT : RIGHT;
    } 
    if (rc == 0) {
        // can only be left or right
        return rr < 0 ? UP : DOWN;
    }
    return "";
}

/**
For getting a random node. Rules here will change a lot. Called when the C is not found. 

TODO: maybe use 'hug the wall logic ?'
*/
Node findALocationUnTraversed (Node **graph, int R, int C, int KR, int KC) {
    Node n;
    n.row = R;
    n.col = C;
    bool isFound = false;
    for (int i = 0; i < 4; i++) {
        int neigh_row = rowNum[i] + KR;
        int neigh_col = colNum[i] + KC;
        if ((neigh_row >= 0 && neigh_row < R) && (neigh_col >= 0 && neigh_col < C) && graph[neigh_row][neigh_col].type > 0) 
        {
            Node curNeigh = graph[neigh_row][neigh_col];
            if (!curNeigh.random_visited && !curNeigh.random_visited_again) {
                n = curNeigh;
                graph[neigh_row][neigh_col].random_visited = true;
                isFound = true;
                break;
            } else {
                // we have marked the path. Cycle detected
                cerr << "CYCLE DETECTED AT " << KR << " " << KC << endl;
                if ((curNeigh.random_visited && !curNeigh.random_visited_again)) {
                    n = curNeigh;
                    graph[neigh_row][neigh_col].random_visited_again = true;
                }
            }
        }
    }
    if (!isFound) {
        cerr << "NOT FOUND" << endl;
    }
    return n;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int R; // number of rows.
    int C; // number of columns.
    int A; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
    cin >> R >> C >> A; cin.ignore();

    // TODO: Maybe graph should be of Nodes. So that the check for visited can be done easier 
    Node ** graph = new Node *[R];
    for (int i = 0; i < R; i++) {
        graph[i] = new Node[C];
        for (int j = 0; j < C; j++) {
            Node n;
            n.row = i;
            n.col = j;
            n.visited = false;
            n.random_visited = false;
            n.random_visited_again = false;
            n.type = 0;
            n.fScore = 1000;
            n.gScore = 1000;
            n.priority = 0;
            graph[i][j] = n; // assume everything is unknown. All fog 
        }
    }
    
    // Start coordinates. Needs to be saved initially
    int tx = -1;
    int ty = -1;
    
    // control room coordinates. So we do not have to go ver and over again
    int cx = -1;
    int cy = -1;
    
    bool isAStarRanOnce = false;
    map<int, int> cameFrom;
    // game loop
    while (1) {
        int KR; // row where Kirk is located.
        int KC; // column where Kirk is located.
        cin >> KR >> KC; cin.ignore();
        
        // save the start coords
        if (tx == -1 && ty == -1) {
            tx = KR;
            ty = KC;
        }
        
        // min row and max row col indicies. It is a 5x5 square with current position in center
        int minRI = KR - 2 <= 0 ? 0 : KR - 2;
        int maxRI = KR + 2 >= R - 1 ? R : KR + 2;
        int minCI = KC - 2 <= 0 ? 0 : KC - 2;
        int maxCI = KC + 2 >= C - 1 ? C - 1 : KC + 2;
        
        graph[KR][KC].type = 3; // player location
        graph[KR][KC].visited = true;
        graph[KR][KC].random_visited = true;
        for (int i = 0; i < R; i++) {
            string ROW; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
            cin >> ROW; cin.ignore();
            // only range of 5
            if (i >= minRI && i <= maxRI) {
                for (int j = minCI; j <= maxCI; j++) {
                    Node graphNode = graph[i][j];
                    int type = 0;
                    char c = ROW[j];
                    if (c == '#') // wall
                        type = -10;
                    else if (c == '.') // moveable
                        type = 1;
                    else if (c == 'C') // control room
                        type = 10;
                    else if (c == 'T') // start position
                        type = 2;
                    graphNode.type = type;
                    graph[i][j] = graphNode;
                }
                ROW[KC] = 'A';
            }
        }
        
        if (cx == -1) {
            // have not found the C yet. So use BFS and keep looking
            Node res = BFS_Search(graph, R, C, tx, ty, KR, KC);
            if (res.type == 10) {
                cerr << "RESULT FOUND" << endl;
                cx = res.row;
                cy = res.col;
            } else {
                // randomly traverse the graph. We need to discover the map
                Node randomNode = findALocationUnTraversed (graph, R, C, KR, KC);
                cout << getDirection(randomNode, KR, KC) << endl;  
            }
        }
        
        if (cx == -1) {
            
        }
        else {
            if (!isAStarRanOnce) {
                Node pathNode = astar_pathfind(graph, R, C, cx, cy, tx, ty, cameFrom);
                cout << getDirection(pathNode, KR, KC) << endl;
                isAStarRanOnce = true;
            } else {
                int oneDCur = transformCoord(KR,KC,R);
                int prevOneD = cameFrom[oneDCur];
                int prevX = detransformX(prevOneD, R);
                int prevY = detransformY(prevOneD, R);
                cerr << KR << " " << KC << " " << prevX << " " << prevY << endl;
                cout << getDirection(graph[prevX][prevY], KR, KC) << endl;
            }

        }
    }
}