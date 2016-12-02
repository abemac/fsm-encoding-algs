#include "ec.h"

EC::EC(const std::vector<std::list<int> > &A_){
  A=A_;
  init();
}



void EC::calc_elem_cycles(){

  s=0;

  while (s < A.size()){
    std::cout<<s<<"/"<<A.size()<<std::endl;
    CIRCUIT(s);
    A[s].clear();
    for (int i =0;i<A.size();++i){
      A[i].remove(s);
    }
    for (int i =0;i<A.size();++i){
      blocked[i]=false;
      B[i].clear();
    }
    ++s;
  }

  for(std::vector<int>* v : cycles){
    for(int i : *v){
      std::cout<<i<<" ";
    }
    std::cout<<std::endl;
  }

  std::cout<<"simplifying..."<<std::endl;
  simpflipy_cycles();
  std::cout<<"simplified"<<std::endl;
  for(std::vector<int>* v : cycles){
    for(int i : *v){
      std::cout<<i<<" ";
    }
    std::cout<<std::endl;
  }
  std::cout<<"done with finding odd cycles."<<std::endl;

}

bool EC::CIRCUIT(int v){
  bool f = false;
  stack.push_back(v);
  blocked[v]=true;

  for(auto itr = A[v].begin();itr!=A[v].end();++itr){
    int w = *itr;
    if(w==s){
      SAVE_CYCLE();
      f=true;
    }else if (!blocked[w]){
      if(CIRCUIT(w)){
        f=true;
      }
    }
  }
  if(f){
    UNBLOCK(v);
  }
  else{
    for(auto itr = A[v].begin();itr!=A[v].end();++itr){
      int w = *itr;
      if(std::find(B[w].begin(),B[w].end(),v)== B[w].end()){
        B[w].push_back(v);
      }
    }
  }
  stack.pop_back();
  return f;



}

void EC::UNBLOCK(int u){
  blocked[u]=false;
  for(auto itr = B[u].begin();itr!=B[u].end();){
    int w = *itr;
    itr=B[u].erase(itr);
    if(blocked[w]){
      UNBLOCK(w);
    }
  }
}


void EC::SAVE_CYCLE(){
    int w=0;
    std::vector<int>* cycle = new std::vector<int>();
    for (auto iw = stack.begin(); iw != stack.end(); ++iw)
        {
           w++;
        }
    if(w%2==1 && w>2)//yuan changed
      {
    for (auto iw = stack.begin(); iw != stack.end(); ++iw)
        cycle->push_back(*iw);

    //std::cout <<s<< std::endl;
    cycle->push_back(s);
    cycles.push_back(cycle);
  }
    return;
}

void EC::init(){

   B.resize(A.size());
   blocked.resize(A.size());
   for(int i = 0;i<A.size();i++){
     blocked[i]=false;
   }

}

void EC::simpflipy_cycles(){
  bool same=false;
  int b=0;
  for(auto i=cycles.begin();i!=cycles.end();++i){
    b++;
    std::cout<<b<<"/"<<cycles.size()<<std::endl;
    for(auto j=cycles.begin();j!=cycles.end();){
      if((i!=j) && (((*i))->size() == ((*j))->size())){
        //std::cout<<"here"<<std::endl;
        same=true;
        int k=0;
        int l=(*i)->size()-1;
        std::vector<int>* v1 = (*i);
        std::vector<int>* v2=(*j);
        // for(int asdf : v1){
        //   std::cout<<asdf<<" ";
        // }
        // std::cout<<std::endl;
        // for(int qwerty : v2){
        //   std::cout<<qwerty<<" ";
        // }
        // std::cout<<std::endl;
        while(same && l>=0){
          //std::cout<<v1[k]<<" "<<v2[l]<<std::endl;
          if(v1->operator[](k)!=v2->operator[](l)){
            same=false;
          }
          ++k;--l;
        }
        // std::cout<<same<<std::endl;
        if(same){
          j=cycles.erase(j);
        }

      }
      if(!same){
        ++j;
      }else{
        same=false;
      }
    }
  }
}
