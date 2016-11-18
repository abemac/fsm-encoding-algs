#include "Graph.h"
#include <fstream>
#include <list>
#include <limits>
#include <string>
#include <iterator>
#include <bitset>

Graph::Graph(int size){
  vertices = std::vector<Node*>(size);
  for(unsigned int i =0; i< vertices.size();i++){
    vertices[i]=nullptr;
  }

  weights = std::vector< std::vector<int> >(size);
  for(unsigned int i=0;i<weights.size();i++){
    weights[i] = std::vector<int>(size);
    for(unsigned int j =0;j<weights[i].size();j++){
      weights[i][j] =0; //FOR NOW
    }
  }


}
//new method remove edges (go through vertices, deleted only from par,adj lists)
//don't delete vertices themselves

void Graph::encode(){
  createCodeVector();
  for(Node * v : vertices){
    v->visited=false;
  }
  std::list<Node*> queue;

  //choose node with max weight
  //whichever row in weights has max sum is vertix with most weight

  int sum=0;
  int loc=0;

  for(unsigned int i =0;i<weights.size();i++){
    int tmp_sum=0;
    for(int j : weights[i]){
      tmp_sum+=j;
    }
    if(tmp_sum > sum){
      sum=tmp_sum;
      loc=i;
    }
  }



  queue.push_back(vertices[loc]);
  vertices[loc]->visited=true;
  vertices[loc]->enc=0;
  vertices[loc]->visited=true;
  allCodes[0]->used=true;

  //add outer loop in case disconnected
  while(queue.size()!=0){
    Node * n = queue.front();
    std::vector<Node*> to_add;
    for(Node* n2 : n->adj){
      if(n2->visited==false){
        n2->enc = getBestNextEncoding(n->enc);
        n2->visited =true;
        to_add.push_back(n2);
      }
    }
    for(Node* n3 : n->par){
      if(n3->visited==false){
        n3->enc = getBestNextEncoding(n->enc);
        n3->visited =true;
        to_add.push_back(n3);
      }
    }
    sortByWeight(to_add);
    for(Node * n : to_add){
      int sum=0;
      for(int t : weights[n->val]){
        sum+=t;
      }
      std::cout<<sum<<std::endl;
    }
    //sort by weight then add all to queue
    return;
    queue.pop_front();
  }

  for(Node * n : vertices){
    std::cout<<n->enc<<std::endl;
  }

}

unsigned long long Graph::getBestNextEncoding(unsigned long long current_enc){
  unsigned long long distanceAway=1;
  while(distanceAway <= numFlipFlops){
    for(Code * c : codeStructs[current_enc]->operator[](distanceAway)->codes){
      if(c->used==false){
        c->used=true;
        return c->val;
      }
    }
    distanceAway++;

  }
  return -1;
}

void Graph::createCodeVector(){
  numFlipFlops=0;
  unsigned long long count=1;

  while(count<vertices.size()){
    numFlipFlops++;
    count<<=1;//multiply by two
  }
  //TODO check here if FF needs to be increased

  usedCodes=std::vector<bool>(count);
  for(unsigned long long j=0;j<usedCodes.size();j++){
    usedCodes[j]=false;
  }
  allCodes=std::vector<Code*>(count);
  for(unsigned long long i =0; i<count;i++){
    allCodes[i]=new Code(i);
  }
  codeStructs=std::vector< std::vector<CodeStruct*>* >();

  for(unsigned long long num=0;num<count;num++){
    for(unsigned long long j=0;j<usedCodes.size();j++){
      usedCodes[j]=false;
    }
    std::vector<CodeStruct*>* codeLevel_current= new std::vector<CodeStruct*>;
    CodeStruct* cl1=new CodeStruct();
    cl1->codes.push_back(allCodes[num]);
    usedCodes[num]=true;
    codeLevel_current->push_back(cl1);

    unsigned long long workingVal=0;
    unsigned long long baseVal=0;
    while(codeLevel_current->size()<numFlipFlops+1){
      CodeStruct * prev = codeLevel_current->back();
      CodeStruct * next = new CodeStruct();
      for(Code * c : prev->codes){
        baseVal=c->val;
        for(unsigned long long i=0;i<numFlipFlops;i++){
          workingVal=baseVal ^ (1<<i);
          if(!usedCodes[workingVal]){
            next->codes.push_back(allCodes[workingVal]);
            usedCodes[workingVal]=true;
          }
        }
      }

      codeLevel_current->push_back(next);

    }
    codeStructs.push_back(codeLevel_current);
  }
  //
  // for(std::vector<CodeStruct*> * v : codeStructs){
  //   for(CodeStruct* cl: *v ){
  //     for(Code * c : cl->codes){
  //
  //       std::bitset<7> b (c->val);
  //       std::cout<<b<<" ";
  //     }
  //     std::cout<<std::endl;
  //   }
  //   std::cout<<std::endl;
  // }


}


void Graph::build_test_graph(){
  insertEdge(0,1);
  insertEdge(0,3);
  insertEdge(1,0);
  insertEdge(1,2);
  insertEdge(1,4);
  insertEdge(2,1);
  insertEdge(2,3);
  insertEdge(2,5);
  insertEdge(2,6);
  insertEdge(3,0);
  insertEdge(3,2);
  insertEdge(4,1);
  insertEdge(4,5);
  insertEdge(5,2);
  insertEdge(5,4);
  insertEdge(5,6);
  insertEdge(6,2);
  insertEdge(6,5);


}


void Graph::insertEdge(int startVal, int endVal){
  Node * ns = vertices[startVal];

  if(ns==nullptr){
    ns = new Node(startVal);
    vertices[startVal]=ns;
  }

  Node* ne = vertices[endVal];
  if(ne==nullptr){
    ne = new Node(endVal);
    vertices[endVal]= ne;
  }

  (ns->adj).push_back(ne);
  (ne->par).push_back(ns);

  //temp
  weights[startVal][endVal]=1;

}
