#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>          

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
    
    int parent_row;
    int parent_col;
    
	inline bool operator==(const Node &left) {
		return row == left.row && col == left.col;
	}
	inline bool operator< (const Node &left) const {
		return left.fScore > fScore;
	}
	
	Node *parent;
	
	Node *left;
	Node *right;
	Node *up;
	Node *down;
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

Node find_first_available_neigh (Node parent) {
    if (parent.up != NULL && parent.up->type > 0 && !parent.up->visited)
        return *parent.up;
    if (parent.down != NULL && parent.down->type > 0 && !parent.down->visited)
        return *parent.down;
        
    if (parent.left != NULL && parent.left->type > 0 && !parent.left->visited)
        return *parent.left;
    if (parent.right != NULL && parent.right->type > 0 && !parent.right->visited)
        return *parent.right;
    cerr << "RETURN NOTHING" << endl;
}

Node* dfs_algo (Node **graph, Node v) 
{
        stack<Node> S;
        S.push(v);
        
        while (!S.empty()) {
            Node cur_node = S.top();
            S.pop();
            
            if (cur_node.type == 10) {
                cerr << "DFS FOUND A SOLUTION" << endl;
                return &cur_node;
            }
            
            if (!cur_node.visited){
                
                cur_node.visited = true;
                Node* adjNodes[] = {cur_node.left, cur_node.right, cur_node.up, cur_node.down};
                for (int i = 0; i < 4; i++) {
                    Node *w = adjNodes[i];
                    if (!w->visited && w->type > 0) {
                        S.push(*w);
                    }
                }
            }
        }

        return NULL;
} 



Node astar_pathfind (Node **graph, int R, int C, int gx, int gy, int sx, int sy, map<int, int> &cameFrom, bool return_start) {
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
            int transG = transformCoord(gx,gy,R);
            int curN = cameFrom[transG];
            int prevX = detransformX (curN,R);
            int prevY = detransformY (curN,R);
            
            cerr << "FOUND SOL " << prevX << " -- " << prevY << " " << gx <<  "  " << gy << endl;
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
                    int newCost = next.gScore + 1;//gScores[transformCoord (cur.row, cur.col, R)] + 1;
                    next.fScore = next.gScore + manhattanDistance(next.row,next.col,gx,gy);
                    
                    for (int i = 0; i < 4; i++) {
                        int neigh_row_2 = rowNum[i] + next.row;
                        int neigh_col_2 = colNum[i] + next.col;
                        // be safe. Check the indicies. TODO: should not be needed maybe ?
                        if ((neigh_row_2 >= 0 && neigh_row_2 < R) && (neigh_col_2 >= 0 && neigh_col_2 < C)) {
                            Node next_2 = graph [neigh_row_2][neigh_col_2];
                            if (next.type > 0 && next_2 == next && next_2.gScore > next.gScore) {
                                continue;
                            }
                            
                        }
                    }           
                    
                    if (newCost > next.gScore) {
                    //if (newCost < gScores[transformCoord (next.row, next.col, R)] ) {
                        int newF = newCost + manhattanDistance(next.row,next.col,gx,gy);
                        gScores[transformCoord(next.row, next.col, R)] = newCost;
                        
                        next.parent = &cur;
                        
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
    cerr << "Found node x: " << foundNode.row << " node y: " << foundNode.col << endl;
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

string getDirection_vol2 (int startX, int startY, int goalX, int goalY) {
    string direction;
    cerr << "StartX: " << startX << " Start Y: " << startY << " Goal X " << goalX << " Goal Y " << goalY << endl;
    int rr = goalX - startX;
    int rc = goalY - startY;
    
    cerr << "RR " << rr << " RC " << rc << endl;
    
    if (rr <= 0) {
        // can only be up or down
        if (rc == 0)
            return DOWN;
        return rc <= 0 ? LEFT : DOWN;
    } 
    if (rc <= 0) {
        if (rr == 0)
            return LEFT;
        // can only be left or right
        return rr <= 0 ? RIGHT : UP;
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

void convertFrom1dTo2D (int i, int width, int* x, int* y)
{
    *x = i % width;    // % is the "modulo operator", the remainder of i / width;
    *y = i / width;    // where "/" is an integer division
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
    
    int graph_int[R][C];

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
            n.parent_row = -1;
            n.parent_col = -1;
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
    bool returnHome = false;
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
            for (int k = 0; k < C; k++) {
                int type = -50;
                char c = ROW[k];
                if (c == '#') // wall
                    type = -10;
                else if (c == '.') // moveable
                    type = 1;
                else if (c == 'C') // control room
                    type = 10;
                else if (c == 'T') // start position
                    type = 2;
                graph_int[i][k] = type;
            }
            
            bool isA= false;
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
                    else
                        type = -100;
                    graphNode.type = type;
                    graph[i][j] = graphNode;
                }
            }
            string tmpp = ROW;
            if (i == KR)
                tmpp[KC] = 'A';
            cerr << tmpp << endl;
        }
        
        
        Node cur_node = graph[KR][KC];
        if (KR > 0 && graph_int[KR-1][KC] > 0){
            cur_node.up = new Node;
            cur_node.up->row = graph[KR-1][KC].row;
            cur_node.up->col = graph[KR-1][KC].col;
            cur_node.up->visited = graph[KR-1][KC].visited;
            cur_node.up->type = graph[KR-1][KC].type;
            
            cerr << "Add up" << endl;
        }
        if (KR < R - 1 && graph_int[KR+1][KC] > 0){
            cur_node.down = new Node;
            cur_node.down->row = graph[KR+1][KC].row;
            cur_node.down->col = graph[KR+1][KC].col;
            cur_node.down->visited = graph[KR+1][KC].visited;
            cur_node.down->type = graph[KR+1][KC].type;
            cerr << "Add down" << endl;
        }
        if (KC > 0 && graph_int[KR][KC-1] > 0){
            cur_node.left = new Node;
            cur_node.left->row = graph[KR][KC-1].row;
            cur_node.left->col = graph[KR][KC-1].col;
            cur_node.left->visited = graph[KR][KC-1].visited;
            cur_node.left->type = graph[KR][KC-1].type;
            cerr << "Add left" << endl;
        }
        if (KC < C - 1 && graph_int[KR][KC+1] > 0){
            cur_node.right = new Node;
            cur_node.right->row = graph[KR][KC+1].row;
            cur_node.right->col = graph[KR][KC+1].col;
            cur_node.right->visited = graph[KR][KC+1].visited;
            cur_node.right->type = graph[KR][KC+1].type;
            cerr << "Add right" << endl;
        }
        
        cerr << cur_node.right->row << " -- " << cur_node.right->col << endl;
        
        Node *tt = dfs_algo(graph, cur_node);
        if (tt != NULL)
            cout << getDirection(*tt, KR, KC) << endl;
        else{
            cerr << "RETURN NULL" << endl;
            
            cout << getDirection(find_first_available_neigh(cur_node), KR, KC) << endl;
        }
    } // end while
}


/**

        graph[KR][KC].type = 3; // player location
        graph[KR][KC].visited = true;
        graph[KR][KC].random_visited = true;
        for (int i = 0; i < R; i++) {
            string ROW; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
            cin >> ROW; cin.ignore();
            cerr << ROW << endl;
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
                    else
                        type = -100;
                    graphNode.type = type;
                    graph[i][j] = graphNode;
                }
                ROW[KC] = 'A';
            }
        }
        
        if (cx == -1 && !isAStarRanOnce) {
            // have not found the C yet. So use BFS and keep looking
            Node res = BFS_Search(graph, R, C, tx, ty, KR, KC);
            if (res.type == 10) {
                cx = res.row;
                cy = res.col;
                isAStarRanOnce = true;
                cerr << "RESULT FOUND AT " << cx << " " << cy << "   " << tx << " --- " << ty << endl;
                cerr << "Current Position " << KR << " --- " << KC << endl;
            } else {
                // randomly traverse the graph. We need to discover the map
                Node randomNode = findALocationUnTraversed (graph, R, C, KR, KC);
                cout << getDirection(randomNode, KR, KC) << endl;
            }
        }
        
        if (isAStarRanOnce) {
            Node pathNode = astar_pathfind(graph, R, C, cx, cy, KR, KC, cameFrom, false);
            if (KR == cx && KC == cy) {
                returnHome = true;
                isAStarRanOnce = false;
            }
            // COMMENT OUT else if (manhattanDistance (pathNode.row, pathNode.col, cx, cy) < 2) 
            {
                cerr << pathNode.row << " " << pathNode.col << endl;
                Node tt;
                tt.row = cx;
                tt.col = cy;
                cout << getDirection(tt, pathNode.row, pathNode.col) << endl;
            }//COMMENT OUT END
            else {
                cout << getDirection_vol2(KR, KC, cx, cy) << endl;
                
            }
        
        } 

        if (returnHome) {
            int tt = cameFrom[transformCoord(KR, KC, R)];
            int f_x = -1;
            int f_y = -1;
            convertFrom1dTo2D(tt, R, &f_x, &f_y);
            
            Node pathNode = astar_pathfind(graph, R, C, tx, ty, KR, KC, cameFrom, true);
            //Node pathNode = BFS_Search(graph, R, C, tx, ty, KR, KC);
            cerr << "SHOULD GO: " << pathNode.row << " " << pathNode.col << endl;
            cerr << "Touched the wall thingy to it will try to go back now " << tt  << " " << f_x << " - " << f_y << endl;
            cerr << "Current position: " << KR << " - " << KC << " Destination: " << tx << " - " << ty << endl;
            if (pathNode.type > 0)
                cout << getDirection_vol2(KR, KC, pathNode.row, pathNode.col) << endl;
            else{
                    
            }
            /*if ((ty - KC == 0 && abs(KR-tx) == 1))
            {
                cerr << "1" << endl;
                cout << getDirection_vol2(KR, KC, tx, ty) << endl;
            }
            else if (tx - KR == 0 && abs(KC - ty) == 1)
            {
                cerr << "3" << endl;
                cout << getDirection_vol2(KR, KC, tx, ty) << endl;
            }
            else 
            {
                cout << getDirection_vol2(KR, KC, pathNode.row, pathNode.col) << endl;    
            }*/
            
        /*}

*/
/*
                    //
                    
                    if (i == 1 && j == 1)
                        isA = true;
                    else 
                        isA = false;
                        
                    if(isA)   cerr << i << " -- " << j << endl;
                    if(isA)   cerr << ROW << endl;
                    if(isA)   cerr << graph[i][j+1].type << " main type " << type << endl;
                    
                    if (i > 0 && graph[i-1][j].type > 0) {
                        graphNode.up = &graph[i-1][j];
                        if (isA)
                            cerr << "Add left" << endl;
                    }
                    else
                        graphNode.up = NULL;
                        
                    if (i < R - 1 && graph[i+1][j].type > 0 ) {
                        if (isA) cerr << "Add right" << endl;
                        graphNode.down = &graph[i+1][j];
                    }
                    else
                        graphNode.down = NULL;
                    
                    if (j > 0 && graph[i][j-1].type > 0 ){
                        graphNode.left = &graph[i][j-1];
                         if (isA) cerr << "Add up" << endl;
                    }
                    else
                        graphNode.left = NULL;
                        
                    if (j < C - 1 && graph[i][j+1].type > 0) {
                        graphNode.right = &graph[i][j+1];
                        if (isA) cerr << "Add down" << endl;
                    }
                    else
                        graphNode.right = NULL;
*/