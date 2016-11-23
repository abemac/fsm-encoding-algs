#ifndef GRAPH_H
#define GRAPH_H

#include "Path.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <list>
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
  void write_to_dot_result();


private:
    std::vector<Node*> vertices;
    std::vector< std::vector<int> > weights;

    struct Code{
      unsigned long long val;
      bool used;
      Code(unsigned long long v){
        val=v;
        used=false;
      }
    };

    struct CodeStruct{
      std::vector<Code*> codes;
    };

    unsigned long long getBestNextEncoding(unsigned long long current_enc);
    void createCodeVector();

    std::vector<std::vector<unsigned long long> > src_file;
    std::vector<bool> usedCodes;


    std::vector< std::vector<CodeStruct*>* > codeStructs;

    unsigned long long numFlipFlops;

    //////////
    std::vector<Code*> allCodes;


};

#endif
