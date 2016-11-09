



#include "re.h"

void RE::remove_edges(){
  std::vector<char> a;
  a.push_back('0');
  a.push_back('1');
  a.push_back('4');
  a.push_back('5');
  a.push_back('6');
  a.push_back('2');
  a.push_back('3');
  a.push_back('0');

  std::vector<char> b;
  b.push_back('1');
  b.push_back('2');
  b.push_back('6');
  b.push_back('5');
  b.push_back('4');
  b.push_back('1');

  std::vector<char> c;
  c.push_back('2');
  c.push_back('5');
  c.push_back('6');
  c.push_back('2');

  odd_cycles.push_back(a);
  odd_cycles.push_back(b);
  odd_cycles.push_back(c);

  counts.resize(7);
  for(std::vector<Cell*>& c: counts){
    c.resize(7);
  }
  for(std::vector<Cell*>& c: counts){
    for(Cell*& cell : c){
      cell=nullptr;
    }
  }
  count();
  std::sort(cells.begin(),cells.end(),compareByCount);
  for(Cell* c : cells){
    std::cout<<c->count<<" ("<<c->from-48<<"->"<<c->to-48<<"),"<<"(";
    for(int i : c->list){
      std::cout<<i<<" ";
    }
    std::cout<<"\b)"<<std::endl;

  }
  remove();

 std::cout<<"modified odd cycles:"<<std::endl;
  for(auto a : odd_cycles){
    for(auto i : a){
      if(i=='X'){
        std::cout<<"\033[1;31mX\033[0m ";
      }else{
      std::cout<<i<<" ";
      }
    }
    std::cout<<std::endl;
  }
}




void RE::remove(){
    bool deleted[]={false,false,false};
    int i=0;
    while((!deleted[0] || !deleted[1] || !deleted[2])){
      for(int k : cells[i]->list){
        bool deleted2=false;
        for(auto itr=odd_cycles[k].begin();!deleted2;++itr){
          if((*itr)==(cells[i]->from) && (*(std::next(itr)))==(cells[i]->to) ||
          (*itr)==(cells[i]->to) && (*(std::next(itr)))==(cells[i]->from)){
            deleted2=true;
            deleted[k]=true;
            odd_cycles[k].insert(std::next(itr),'X');
          }
        }
      }
      ++i;
    }
}

void RE::count(){
  for(int i=0;i<odd_cycles.size();i++){
    for(int j=0;j<odd_cycles[i].size()-1;j++){
      int l=odd_cycles[i][j]-48;
      int k=odd_cycles[i][j+1]-48;
      if(counts[l][k]==nullptr){
        counts[l][k]=new Cell();
        counts[k][l]=counts[l][k];
        cells.push_back(counts[l][k]);
        counts[l][k]->from=l+48;
        counts[l][k]->to=k+48;

      }
      counts[l][k]->count++;
      counts[l][k]->list.push_back(i);
    }
  }

}
