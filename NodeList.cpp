#include "NodeList.h"
#include <iostream>



NodeList::NodeList(){
   for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++){
      nodes[i] = nullptr;
   }
}


NodeList::~NodeList(){
   
}

NodeList::NodeList(NodeList& other){
   // TODO
   for (int i = 0; i < other.length; ++i){
      nodes[i] = other.nodes[i];
   }
   length = other.length;
}


int NodeList::getLength(){
   return length;
}


NodePtr NodeList::get(int i){
   return nodes[i];
}

void NodeList::addBack(NodePtr newNode){
   bool itsempty=true;
   int i=0;
   while (itsempty == true){
      if (nodes[i]==nullptr){
         nodes[i] = newNode;
         itsempty = false;
         length++;
         ++i;
      }
      else{
         ++i;
      }
   }
}

bool NodeList::containsNode(NodePtr node){
   for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; ++i){
      if (nodes[i] == node){
         return true;
      }
   }
   return false;
}

void NodeList::clear(){
   
}