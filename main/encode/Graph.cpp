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
Graph::Graph(const std::vector<std::list<int> >& adjList){
  vertices = std::vector<Node*>(adjList.size());
  for(unsigned int i =0; i< vertices.size();i++){
    vertices[i]=nullptr;
  }

  weights = std::vector< std::vector<int> >(adjList.size());
  for(unsigned int i=0;i<weights.size();i++){
    weights[i] = std::vector<int>(adjList.size());
    for(unsigned int j =0;j<weights[i].size();j++){
      weights[i][j] =0; //FOR NOW
    }
  }

  std::vector<std::vector<bool> > inserted;
  for(int i=0;i<adjList.size();i++){
    inserted.push_back(std::vector<bool>());
    for(int j=0;j<adjList.size();j++){
      inserted[i].push_back(false);
    }
  }

  for(int i=0;i<adjList.size();i++){
    for(int adj : adjList[i]){
      if(!inserted[i][adj]){
        inserted[i][adj]=true;
        inserted[adj][i]=true;
        insertEdge(i,adj);
        insertEdge(adj,i);
      }
    }
  }


}

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

  //**********add outer loop in case disconnected

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
    // for(Node* n3 : n->par){
    //   if(n3->visited==false){
    //     n3->enc = getBestNextEncoding(n->enc);
    //     n3->visited =true;
    //     to_add.push_back(n3);
    //   }
    // }
    sortByWeight(to_add);
    //sort by weight then add all to queue
    for(int i = to_add.size()-1;i>=0;i--){
      queue.push_back(to_add[i]);
    }
    queue.pop_front();
  }

  std::cout<<"\nEncoding:"<<std::endl;
  for(Node * n : vertices){
    std::cout<<(n->val)<<":"<<n->enc<<std::endl;
  }
  std::cout<<"("<<numFlipFlops<<" bits)"<<std::endl;

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
  int max_weight=0;
  for(int i=0;i<weights.size();i++){
    int tmp_weight=0;
    for(int t : weights[i]){
      tmp_weight+=t;
    }

    if(tmp_weight>max_weight){
      max_weight=tmp_weight;
    //  std::cout<<i<<" "<<max_weight<<std::endl;
    }
  }
  //  std::cout<<max_weight<<std::endl;
  //  std::cout<<numFlipFlops<<std::endl;
  if(max_weight>numFlipFlops){
    count<<=(max_weight-numFlipFlops);
    numFlipFlops=max_weight;
  }

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

  // for(std::vector<CodeStruct*> * v : codeStructs){
  //   for(CodeStruct* cl: *v ){
  //     for(Code * c : cl->codes){
  //
  //       std::bitset<4> b (c->val);
  //       std::cout<<b<<" ";
  //     }
  //     std::cout<<std::endl;
  //   }
  //   std::cout<<std::endl;
  // }


}

void Graph::remove_edges(const std::vector<std::pair<int,int>* >& deleted_edges){
  for(std::pair<int,int>* pp : deleted_edges){
    int from = pp->first;
    int to = pp->second;
    weights[from][to]=0;
    weights[to][from]=0;
    for(auto itr = vertices[from]->adj.begin();itr!=vertices[from]->adj.end();){
      if((*itr)->val == to){
        std::cout<<"erased "<< from<<(*itr)->val<<std::endl;
        itr=vertices[from]->adj.erase(itr);

      }else{
        ++itr;
      }
    }
    for(auto itr = vertices[to]->adj.begin();itr!=vertices[to]->adj.end();){
      if((*itr)->val == from){
        std::cout<<"erased "<< to<<(*itr)->val<<std::endl;
        itr=vertices[to]->adj.erase(itr);

      }else{
        ++itr;
      }
    }
  }
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
  //(ne->par).push_back(ns);

  //temp
  weights[startVal][endVal]=1;

}

void Graph::sortByWeight(std::vector<Node*>& v){
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

void Graph::write_to_dot_result(){
  std::ofstream FILE;
  std::string path ="result.dot";
  FILE.open(path);
  FILE<<"graph fsm {\n";
  std::vector< std::vector<bool> > added;
  for(int k=0;k<vertices.size();k++){
    added.push_back(std::vector<bool>());
    for(int i=0;i<vertices.size();i++){
      added[k].push_back(false);
    }
  }
  for(Node* n : vertices){
    for(Node* adj : n->adj){
      if(added[n->val][adj->val]==false){
        added[n->val][adj->val]=true;
        added[adj->val][n->val]=true;
        FILE<<"\""<<(n->val)<<"\\n(";
        for(int i = numFlipFlops-1; i>=0;i--){
          unsigned int x = ((n->enc) & (1<<i))>>i;
          FILE<<x;
        }
        FILE<<")\"--\""<<adj->val<<"\\n(";
        for(int i = numFlipFlops-1; i>=0;i--){
          unsigned int x = ((adj->enc) & (1<<i))>>i;
          FILE<<x;
        }
        FILE<<")\";\n";
    }


    }
  }
  FILE<<"}";
  FILE.close();

}
