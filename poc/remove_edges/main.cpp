


#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
std::vector<std::vector <int> > odd_cycles;



void count();
void remove();

struct Cell{
  int from=-1;
  int to=-1;
  int count=0;
  std::vector<int> list;
};
bool compareByCount(const Cell* c1, const Cell* c2){
  return (c1->count)>(c2->count);
}
std::vector<std::vector<Cell*> > counts;
std::vector<Cell*> cells;


int main(){
  std::vector<int> a;
  a.push_back(0);
  a.push_back(1);
  a.push_back(4);
  a.push_back(5);
  a.push_back(6);
  a.push_back(2);
  a.push_back(3);
  a.push_back(0);

  std::vector<int> b;
  b.push_back(1);
  b.push_back(2);
  b.push_back(6);
  b.push_back(5);
  b.push_back(4);
  b.push_back(1);

  std::vector<int> c;
  c.push_back(2);
  c.push_back(5);
  c.push_back(6);
  c.push_back(2);

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
    std::cout<<c->count<<" ("<<c->from<<"->"<<c->to<<"),"<<"(";
    for(int i : c->list){
      std::cout<<i<<" ";
    }
    std::cout<<"\b)"<<std::endl;

  }
  remove();

 std::cout<<"modified odd cycles:"<<std::endl;
  for(auto a : odd_cycles){
    for(auto i : a){
      std::cout<<i<<" ";
    }
    std::cout<<std::endl;
  }
}




void remove(){
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
            itr=odd_cycles[k].erase(itr);
            odd_cycles[k].erase(itr);
          }
        }
      }
      ++i;
    }
}

void count(){
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
