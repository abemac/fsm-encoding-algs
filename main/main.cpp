



#include "remove_edges/etr.h"
#include <iostream>
#include <vector>
#include "encode/Graph.h"
#include "encode/Path.h"

int main (int argc, char* argv[]){
  std::string filePath= argv[1];
  bool min_output=false;
  if(argc>=3){
    std::string min_out=argv[2];
    if(min_out.compare("-minout")==0){
      min_output=true;
    }
  }
  ETR etr(min_output);
  std::cout<<"\nfinding odd cycles and edges to remove...\n"<<std::endl;
  etr.find_edges(filePath);
  std::cout<<std::endl;


  Graph g = Graph(etr.adjList);
  g.remove_edges(etr.removed_edges);
  g.encode();
  std::string graphname;
  if(argc>=4){
    graphname=argv[3];
  }else{
    graphname="";
  }
  g.write_to_dot_result(graphname);
  std::cout<<"\ndone"<<std::endl;

}
