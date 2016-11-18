#ifndef GRAPH_H
#define GRAPH_H

#include "Path.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
class Graph{

public:

  Graph(int size);

  struct Node {
    int val;
    std::vector<Node*> adj;
    std::vector<Node*> par;
    bool visited;
    unsigned long long enc;
    Node(int val_){val=val_;}

  };


  void sortByWeight(std::vector<Node*>& v){
    std::vector<int> weight_sum(v.size());
    for(int i =0;i<v.size();i++){
      for(int t : weights[v[i]->val]){
        weight_sum[i]+=t;
      }
    }


    for(int i =1;i<v.size();i++){
      int t=i;
      while(weight_sum[t] < weight_sum[t-1] && t!=0){
        Node * tmp = v[t];
        v[t]=v[t-1];
        v[t-1]=tmp;
        int tmp_weight=weight_sum[t];
        weight_sum[t]=weight_sum[t-1];
        weight_sum[t-1]=tmp_weight;
        t--;
      }
    }
  }

  void insertEdge(int startVal,int endVal);

  void build_test_graph();
  void encode();



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
