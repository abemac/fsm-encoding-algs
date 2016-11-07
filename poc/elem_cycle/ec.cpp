#include "ec.h"

void EC::print_elem_cycles(){
  init("test_graphs/test3.csv");

  s=0;

  while (s < A.size()){
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

  simpflipy_cycles();
  std::cout<<"simplified"<<std::endl;
  for(std::vector<int>* v : cycles){
    for(int i : *v){
      std::cout<<i<<" ";
    }
    std::cout<<std::endl;
  }


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

void EC::init(const std::string& filePath){
  std::ifstream FILE(filePath);
  std::string str;

  while(std::getline(FILE,str)){
    std::list<int> tmp;
    int i=0;
    int lasti=0;
    for(;i<str.size();i++){
      if(str[i]==',' || i==str.size()-1){
        int val=std::stoi(str.substr(lasti,i+1-lasti),nullptr,10);
        tmp.push_back(val);
        lasti=i+1;
      }
    }
    A.push_back(tmp);
   }
   B.resize(A.size());
   blocked.resize(A.size());
   for(int i = 0;i<A.size();i++){
     blocked[i]=false;
   }
   FILE.close();

}

void EC::simpflipy_cycles(){
  bool same=false;
  for(auto i=cycles.begin();i!=cycles.end();++i){
    for(auto j=cycles.begin();j!=cycles.end();){
      if(i!=j && ((*i)->size()) == ((*j)->size())){
        same=true;
        int k=0;
        int l=(*i)->size()-1;
        std::vector<int> v1 = *(*i);
        std::vector<int> v2=*(*j);
        //std::cout<<"here"<<std::endl;
        while(same && k<l){
          if(v1[k]!=v2[l]){
            same=false;
          }
          ++k;--l;
        }
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
