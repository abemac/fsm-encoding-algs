



#include "../remove_edges/etr.h"
#include <iostream>
#include <vector>
#include "../encode/Graph.h"
#include "../encode/Path.h"

int main (int argc, char* argv[]){
  std::string filePath= argv[1];
  ETR etr;
  std::cout<<"\nfinding odd cycles and edges to remove...\n"<<std::endl;
  etr.find_edges(filePath);
  std::cout<<std::endl;

  std::cout<<"\nEncoding...\n"<<std::endl;
  Graph g = Graph(etr.adjList);
  g.remove_edges(etr.removed_edges);
  g.encode();
  g.write_to_dot_result();
  std::cout<<"\ndone"<<std::endl;

}
