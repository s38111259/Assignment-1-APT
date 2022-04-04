#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printReachablePositions(Env env, NodeList* solution);
void printPath(Env env, NodeList* solution);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 
    Env env;
    readEnvStdin(env);
    
    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathPlanner* pathplanner = new PathPlanner(env, ENV_DIM, ENV_DIM);
    NodeList* reachablePositions = nullptr; 
    reachablePositions = pathplanner->getReachableNodes();  
    
    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathplanner->getPath();  

    //Reversing the path FROM Finish->Start TO Start->Finish
    NodeList* copysolution = new NodeList();
    for (int i = 0; i < solution->getLength(); ++i){
        copysolution->addBack(solution->get(solution->getLength()-i-1));
    }

    // printReachablePositions(env, solution);
    printPath(env, copysolution);
    delete pathplanner;
    delete reachablePositions;
    delete solution;
    delete copysolution;

}

void readEnvStdin(Env env){
    char input;
    for( int i =0 ; i<ENV_DIM ; i++ ){
        for( int j =0 ; j<ENV_DIM ; j++ ){
            std::cin>>input;
            env[i][j] = input;
        }
    } 
}

void printPath(Env env, NodeList* solution) {
    //TODO
    //Updates the Environment with Directions
    for (int i = 1; i<solution->getLength()-1; i++){
        if ( (i+1) < solution->getLength() ){
            int row = solution->get(i)->getRow();
            int col = solution->get(i)->getCol();
            int next_row = solution->get(i+1)->getRow();
            int next_col = solution->get(i+1)->getCol();

            if (next_row - row == -1 && next_col - col == 0){
                //up
                env[row][col]='^';
            }

            else if (next_row - row == 0 && next_col - col == 1){
                //right
                env[row][col]='>';
            }
            else if(next_row - row == 1 && next_col - col == 0){
                //down
                env[row][col]='v';
            }
            else{
                //left
                env[row][col]='<';
            }
        }
    }

    //Prints the Environment
    for (int i = 0; i < ENV_DIM; ++i){
        for (int j = 0; j < ENV_DIM; ++j){
            /* code */
            std::cout<<env[i][j];
        }
        std::cout<<"\n";
    }
}

void printReachablePositions(Env env, NodeList* solution){
    //TODO
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addBack(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addBack(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->get(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceToS() << std::endl;

    //Test containsNode method - return 1
    std::cout<<nodeList->containsNode(getB)<<std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}