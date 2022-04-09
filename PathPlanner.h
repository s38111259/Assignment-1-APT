
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

   //Checks for Empty spaces
   bool is_a_Dot_There(Node* node, Env env);

   //Checks for the Goal Position/Node
   bool is_Goal_There(Node* node, Env env);

   //Method for Milestone 2
   // Adds available nodes present around the particular node to OpenList
   void availableNodes(Node* p, Env env);

   //Return the count of available nodes present around the particular nodes
   int getAvailableNodeCount(Node* p, Env env);

   //Checks if Node is present in OpenList or not
   bool check_q_in_OpenList(Node* q);

   //Checks if Node is present in PathList or not
   bool check_q_in_PathList(Node* q);

   //Return Node present in OpenList that is not present in CloseList
   Node* get_Node_fOpen_NClose();

   //Adds available Nodes to getpathList
   void getPathNodes(Node* p, Env env);

   //Return the count of available nodes present around the particular nodes
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
