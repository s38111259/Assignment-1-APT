#include "PathPlanner.h"
#include <iostream>

PathPlanner::PathPlanner(Env env, int rows, int cols){ // row amd col is the current position of the robot 
// the use of it is that it will return all the possible nodewith respect to this position 
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            this->env[i][j] = env[i][j];
        }
    }
    
    this->rows = rows;
    this->cols = cols;
    openList = new NodeList();
    closeList = new NodeList();
    getpathList = new NodeList();
    getpathCloseList = new NodeList();
}

PathPlanner::~PathPlanner(){
   
}

//set the initial position
void PathPlanner::initialPosition(int row, int col){
   for (int i = 0; i < row; ++i){
       for (int j = 0; j < col; ++j){
           if(env[i][j]=='S'){
                Node* StartNode = new Node(i, j, 0);
                openList->addBack(StartNode);
            }            
       }
   }
}

//checks for empty places where robot can go
bool PathPlanner::is_a_dot_there(Node* node, Env env){
    int i = node->getRow();
    int j = node->getCol();
    if(env[i][j] == '.'){
        return true;
    }
    return false;
}

//checks if Goal 'G' is there or not
bool PathPlanner::is_goal_there(Node* node, Env env){
    int i = node->getRow();
    int j = node->getCol();
    if(env[i][j] == 'G'){
        return true;
    }
    return false;
}

//Checks and Adds the nodes available around the current location of Robot
void PathPlanner::available_Nodes(Node* p, Env env){
    Node* up = new Node(p->getRow()-1,p->getCol(),p->getDistanceToS()+1);       //These are actually node q
    Node* right = new Node(p->getRow(), p->getCol()+1,p->getDistanceToS()+1);
    Node* down = new Node(p->getRow()+1,p->getCol(),p->getDistanceToS()+1);
    Node* left = new Node(p->getRow(),p->getCol()-1,p->getDistanceToS()+1);

    if(is_a_dot_there(up, env) || is_goal_there(up, env)){
        if (!check_q_in_OpenList(up)){
            openList->addBack(up);
        }
    }

    if(is_a_dot_there(right,env) || is_goal_there(right, env)){
        if (!check_q_in_OpenList(right)){
            openList->addBack(right);
        }
    }

    if(is_a_dot_there(down,env) || is_goal_there(down, env)){
        if (!check_q_in_OpenList(down)){
            openList->addBack(down);
        }
    } 

    if(is_a_dot_there(left,env) || is_goal_there(left, env)){
        if (!check_q_in_OpenList(left)){
            openList->addBack(left);
        }
    }

    // This is implemented for Milestone 3
    // When it sees the Goal node, it adds it into 'getpathList' and thus 'getpathList' is initialized and
    // contains only one node that is the goal node at 0th index which helps in backtracking.

    if(is_goal_there(up, env)){
        if (!check_q_in_PathList(up)){
            getpathList->addBack(up);
        }
    }

    if(is_goal_there(right,env)){
        if (!check_q_in_PathList(right)){
            getpathList->addBack(right);
        }
    }

    if(is_goal_there(down,env)){
        if (!check_q_in_PathList(down)){
            getpathList->addBack(down);
        }
    } 

    if(is_goal_there(left,env)){
        if (!check_q_in_PathList(left)){
            getpathList->addBack(left);
        }
    } 
 }

//Returns the count of available nodes present around the current location.
int PathPlanner::get_available_node_count(Node* p, Env env) {
    int count =0;
    Node* up = new Node(p->getRow()-1,p->getCol(),0);                           //These are actually node q
    Node* right = new Node(p->getRow(), p->getCol()+1,0);
    Node* down = new Node(p->getRow()+1,p->getCol(),0);
    Node* left = new Node(p->getRow(),p->getCol()-1,0);

    if((is_a_dot_there(up, env) || is_goal_there(up, env))&& !check_q_in_OpenList(up)){
        ++count;
    }

    if((is_a_dot_there(right,env) || is_goal_there(right, env))&& !check_q_in_OpenList(right)){
        ++count;
    } 

    if((is_a_dot_there(down,env) || is_goal_there(down, env))&& !check_q_in_OpenList(down)){
        ++count;
    }

    if((is_a_dot_there(left,env) || is_goal_there(left, env)) && !check_q_in_OpenList(left)){
        ++count;
    }

    //Milestone 3 Implementation
    if(is_goal_there(up, env) && !check_q_in_PathList(up)){
        ++count;
    }

    if(is_goal_there(right,env) && !check_q_in_PathList(right)){
        ++count;
    } 

    if(is_goal_there(down,env) && !check_q_in_PathList(down)){
        ++count;
    }

    if(is_goal_there(left,env) && !check_q_in_PathList(left)){
        ++count;
    }
    return count;
 }


// Method for Milestone 2
// Return a DEEP COPY of the NodeList of all node's 
// that the robot can reach
NodeList* PathPlanner::getReachableNodes(){
    initialPosition(rows, cols);
    Node* p = openList->get(0);

    do{
        for (int i = 0; i < get_available_node_count(p, env); ++i){
            available_Nodes(p, env);
        }
        closeList->addBack(p);
        p = get_Node_fOpen_NClose();
    } while (p!=nullptr);

    //Deep Copy
    NodeList* copyOpenList = new NodeList(*openList);
    return copyOpenList;
}

//Return nodes available in Open List and not in Close List
Node* PathPlanner::get_Node_fOpen_NClose() {
    for (int i = 0; i < openList->getLength(); ++i){
        if (closeList->containsNode(openList->get(i))){
        }
        else{
            return openList->get(i);
        }
    }
    return nullptr;
}

//Checks if Node is in Open List or not
bool PathPlanner::check_q_in_OpenList(Node* q){
    bool check = false;
    int q_row = q->getRow();
    int q_col = q->getCol();
    for (int i = 0; i < openList->getLength(); i++){
        int curr_node_row = openList->get(i)->getRow();
        int curr_node_col = openList->get(i)->getCol();
        if (q_row == curr_node_row && q_col == curr_node_col){
            check = true;
            return check;
        }
    }
    return check;
}

//Checks if Node is in Path List or not
bool PathPlanner::check_q_in_PathList(Node* q){
    bool check = false;
    int q_row = q->getRow();
    int q_col = q->getCol();
    for (int i = 0; i < getpathList->getLength(); ++i){
        int curr_node_row = getpathList->get(i)->getRow();
        int curr_node_col = getpathList->get(i)->getCol();
        if (q_row == curr_node_row && q_col == curr_node_col){
            check = true;
            return check;
        }
    }
    return check;
}


//Milestone 3 Implementation
void PathPlanner::getPathNodes(Node* p, Env env) {
    Node* up = new Node(p->getRow()-1,p->getCol(),p->getDistanceToS());     
    Node* right = new Node(p->getRow(), p->getCol()+1,p->getDistanceToS());
    Node* down = new Node(p->getRow()+1,p->getCol(),p->getDistanceToS());
    Node* left = new Node(p->getRow(),p->getCol()-1,p->getDistanceToS());

    if (is_a_dot_there(up, env) && !check_q_in_PathList(up) && check_q_in_OpenList(up)){
        getpathList->addBack(up);
    }

    if (is_a_dot_there(right, env) && !check_q_in_PathList(right) && check_q_in_OpenList(right)){
        getpathList->addBack(right);
    }

    if (is_a_dot_there(down, env) && !check_q_in_PathList(down) && check_q_in_OpenList(down)){
        getpathList->addBack(down);
    }

    if (is_a_dot_there(left, env) && !check_q_in_PathList(left) && check_q_in_OpenList(left)){
        getpathList->addBack(left);
    }
}

int PathPlanner::getPathNodesCount(Node* p, Env env) {
    int count = 0;
    Node* up = new Node(p->getRow()-1,p->getCol(),p->getDistanceToS());     //These are actually node q
    Node* right = new Node(p->getRow(), p->getCol()+1,p->getDistanceToS());
    Node* down = new Node(p->getRow()+1,p->getCol(),p->getDistanceToS());
    Node* left = new Node(p->getRow(),p->getCol()-1,p->getDistanceToS());

    if(is_a_dot_there(up, env) && !check_q_in_PathList(up) && check_q_in_OpenList(up)){
        ++count;
    }

    if(is_a_dot_there(right, env) && !check_q_in_PathList(right) && check_q_in_OpenList(right)){
        ++count;
    } 

    if(is_a_dot_there(down, env) && !check_q_in_PathList(down) && check_q_in_OpenList(down)){
        ++count;
    }

    if(is_a_dot_there(left, env) && !check_q_in_PathList(left) && check_q_in_OpenList(left)){
        ++count;
    }
    return count;
}



NodeList* PathPlanner::getPath(){
    Node* endNode = getpathList->get(0);
    
    do{
        int dist = endNode->getDistanceToS();
        for (int i = 0; i < openList->getLength(); ++i){
            int d = openList->get(i)->getDistanceToS();
            if (d == (dist-1) && (endNode->getRow()==openList->get(i)->getRow() || endNode->getCol()==openList->get(i)->getCol())){
                getpathList->addBack(openList->get(i));
                endNode = openList->get(i);                
            }
        }
    } while (endNode!=openList->get(0));

    //Deep Copy
    NodeList* copyPathList = new NodeList(*getpathList);
    return copyPathList;
}
