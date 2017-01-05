



#include "re.h"

void RE::remove_edges(const std::vector<std::vector<int>* >& odd_cycles_,int size){

  for(std::vector<int>* v : odd_cycles_){
    std::vector<unsigned int> temp;
    for(int i : *v){
      temp.push_back(i);
    }
    odd_cycles.push_back(temp);
  }




  counts.resize(size);
  for(std::vector<Cell*>& c: counts){
    c.resize(size);
  }
  for(std::vector<Cell*>& c: counts){
    for(Cell*& cell : c){
      cell=nullptr;
    }
  }
  count();
  std::sort(cells.begin(),cells.end(),compareByCount);
  std::cout<<"Edge Counts:"<<std::endl;
  for(Cell* c : cells){
    std::cout<<c->count<<" ("<<c->from<<" ↔ "<<c->to<<"),"<<"(";
    for(int i : c->list){
      std::cout<<i<<" ";
    }
    std::cout<<"\b)"<<std::endl;

  }
  remove(odd_cycles.size());

  std::cout<<"\n\nBreaking edges"<<std::endl;
  std::cout<<"modified odd cycles:"<<std::endl;
  for(auto a : odd_cycles){
    for(auto i : a){
      if(i==-1){
        std::cout<<"\033[1;31mX\033[0m ";
      }else{
      std::cout<<i<<" ";
      }
    }
    std::cout<<std::endl;
  }
}




void RE::remove(int size){
    std::vector<bool> deleted;
    for(int b=0;b<size;b++){
      deleted.push_back(false);
    }
    int i=0;
    bool added=false;
    while(anyFalse(deleted)){
      bool newEdgeFound=false;
      while(!newEdgeFound){
        for(int k : cells[i]->list){
          if(deleted[k]==false){
            newEdgeFound=true;
          }
        }
        if(!newEdgeFound){
          ++i;
        }
      }
      for(int k : cells[i]->list){
        bool deleted2=false;
        for(auto itr=odd_cycles[k].begin();!deleted2;++itr){
          if((*itr)==(cells[i]->from) && (*(std::next(itr)))==(cells[i]->to) ||
          (*itr)==(cells[i]->to) && (*(std::next(itr)))==(cells[i]->from)){
            deleted2=true;
            deleted[k]=true;
            odd_cycles[k].insert(std::next(itr),-1);
            if(added==false){
              added=true;
              std::pair<int,int>* pair= new std::pair<int,int>();
              (pair->first)=cells[i]->from;
              (pair->second)=cells[i]->to;
              deleted_edges.push_back(pair);
            }
          }
        }
      }

      ++i;
      added=false;
    }
}

bool RE::anyFalse(const std::vector<bool> & bools){
  for(bool b : bools){
    if(b==false){
      return true;
    }
  }
  return false;
}


void RE::count(){
  for(int i=0;i<odd_cycles.size();i++){
    for(int j=0;j<odd_cycles[i].size()-1;j++){
      int l=odd_cycles[i][j];
      int k=odd_cycles[i][j+1];
      if(counts[l][k]==nullptr){
        counts[l][k]=new Cell();
        counts[k][l]=counts[l][k];
        cells.push_back(counts[l][k]);
        counts[l][k]->from=l;
        counts[l][k]->to=k;

      }
      counts[l][k]->count++;
      counts[l][k]->list.push_back(i);
    }
  }

}
