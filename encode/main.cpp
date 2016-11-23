


#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "Graph.h"
#include "Path.h"
int main(){
  Graph g = Graph(7);
  g.build_test_graph();
  g.encode();
  g.write_to_dot_result();






}
