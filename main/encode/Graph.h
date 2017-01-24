#ifndef GRAPH_H
#define GRAPH_H

#include "Path.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <list>
#include <set>
class Graph{

public:

  Graph(int size);
  Graph(const std::vector<std::list<int> >& adjList);
  struct Node {
    int val;
    std::vector<Node*> adj;
    std::vector<Node*> par;
    bool visited;
    unsigned long long enc;
    Node(int val_){val=val_;}

  };


  void sortByWeight(std::vector<Node*>& v);

  void insertEdge(int startVal,int endVal);

  void build_test_graph();
  void encode();
  void remove_edges(const std::vector<std::pair<int,int>* >& deleted_edges);
  void write_to_dot_result(std::string& name);


private:
    std::vector<Node*> vertices;
    std::vector< std::vector<int> > weights;


    unsigned long long getBestNextEncoding(unsigned long long current_enc);

    std::vector<std::vector<unsigned long long> > src_file;
    std::set<unsigned long long> usedCodes;

    unsigned long long numFlipFlops;

    //////////


};

#endif
