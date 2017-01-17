#include "ec.h"

EC::EC(const std::vector<std::list<int> > &A_,bool min_output_){
  A=A_;
  min_output=min_output_;
  init();

}



void EC::calc_elem_cycles(){

  s=0;
  std::cout<<"\n\nFinding elementary cycles"<<std::endl;
  std::cout<<"Progress ("<<A.size()-1<<" is done): 0"<<std::endl;
  while (s < A.size()){
    std::cout<<"\e[AProgress ("<<A.size()-1<<" is done): "<<s<<std::endl;
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

  //std::cout<<"Sorting cycles"<<std::endl;
  //std::sort(cycles.begin(),cycles.end(),compareBySize);
  //  int k=0;
  // std::cout<<"unsimplified cycles"<<std::endl;
  // for(std::vector<int>* v : cycles){
  //   for(int i : *v){
  //     std::cout<<i<<" ";
  //   }
  //   std::cout<<std::endl;
  //   k++;
  // }

  //std::cout<<"simplifying..."<<std::endl;
  //simpflipy_cycles();

  if(!min_output){
    std::cout<<"\nodd numbered cycles:"<<std::endl;
    for(std::vector<int>* v : cycles){
      for(int i : *v){
        std::cout<<i<<" ";
      }
      std::cout<<std::endl;
    }
   }
  std::cout<<"--------------------------------------------------------------------------------"<<std::endl;

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
    for (auto iw = stack.begin(); iw != stack.end(); ++iw){
        cycle->push_back(*iw);
    }

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

  for(int j=0;j<cycles.size();j++){
    flagged.push_back(false);
  }
  std::vector<std::vector<int>* > simp_cycles;
  for(int i=0;i<cycles.size();i++){
    std::cout<<"\e[Asimplifying ("<<i<<"/"<<cycles.size()<<") bank size:"<<bank.size()<<std::endl;

    if(!flagged[i]){
      int index =in_bank(cycles[i]);
      if(index==-1){
        bank.push_back(cycles[i]);
        flagged[i]=true;
      }else{
        simp_cycles.push_back(cycles[i]);
        flagged[i]=true;
        bank.erase(bank.begin()+index);
      }
    }
    //  if(bank.size()>2){
    //    emptyBank(0);
    //  }

  }
  cycles=simp_cycles;

}
// void EC::emptyBank(int start){
//   for(int i=start;i<cycles.size();i++){
//     if(!flagged[i]){
//       int index =in_bank(cycles[i]);
//       if(index!=-1){
//         simp_cycles.push_back(cycles[i]);
//         flagged[i]=true;
//         bank.erase(bank.begin()+index);
//       }
//     }
//   }
//   if(bank.size()!=0){
//     throw std::runtime_error("Bank size should be zero");
//   }
// }
int EC::in_bank(std::vector<int>* test){
  for(int i=0;i<bank.size();i++){
    if(equivalent(test,bank[i])){
      return i;//index in bank
    }
  }
  return -1;//not in bank
}

bool EC::equivalent(std::vector<int>* a,std::vector<int>* b){
  if(a->size() != b->size()){
    return false;
  }
  bool same=true;
  int k=0;
  int l=b->size()-1;
  while(same && l>=0){
    if(a->operator[](k)!=b->operator[](l)){
      same=false;
    }
    ++k;--l;
  }
  return same;
}
