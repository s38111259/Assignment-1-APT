
#ifndef COSC_ASS_ONE_PATH_PLANNING
#define COSC_ASS_ONE_PATH_PLANNING

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathPlanner {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Initialise with a given Env of size (rows,cols)
   PathPlanner(Env env, int rows, int cols);

   // Clean-up
   ~PathPlanner();

   // Set The initial position
   void initialPosition(int row, int col);


   // Method for Milestone 2
   // Return a DEEP COPY of the NodeList of all node's
   //    that the robot can reach with distances
   NodeList* getReachableNodes();


   // Method for Milestone 3
   // Get the path from the starting position to the given goal co-ordinate
   //    The path should be a DEEP COPY
   NodeList* getPath();


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */
   bool is_a_dot_there(Node* node, Env env);
   bool is_goal_there(Node* node, Env env);
   void available_Nodes(Node* p, Env env);
   int get_available_node_count(Node* p, Env env);
   bool check_q_in_OpenList(Node* q);
   bool check_q_in_PathList(Node* q);
   Node* get_Node_fOpen_NClose();
   void getPathNodes(Node* p, Env env);
   int getPathNodesCount(Node* p, Env env);



private:
   Env env;
   int rows;
   int cols;
   NodeList* openList;
   NodeList* closeList;
   NodeList* getpathList;
   NodeList* getpathCloseList;
};

#endif // COSC_ASS_ONE_PATH_PLANNING
