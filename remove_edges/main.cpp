


#include <vector>
#include <iostream>

std::vector<std::vector <int> > odd_cycles;



void count();

struct Cell{
  int count=0;
  std::vector<int> list;
};

std::vector<std::vector<Cell> > counts;



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
  for(std::vector<Cell>& c: counts){
    c.resize(7);
  }

  count();
  for(std::vector<Cell>& c: counts){
    for(Cell cell : c){
      std::cout<<cell.count<<" ";
    }
    std::cout<<std::endl;
  }

  bool deleted[]={false,false,false};


}


void count(){
  for(int i=0;i<odd_cycles.size();i++){
    for(int j=0;j<odd_cycles[i].size()-1;j++){
      int l=odd_cycles[i][j];
      int k=odd_cycles[i][j+1];
      counts[l][k].count++;
      counts[l][k].list.push_back(i);
      counts[k][l].count++;
      counts[k][l].list.push_back(i);
    }
  }

}
