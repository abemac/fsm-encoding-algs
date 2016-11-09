
#ifndef RE_H
#define RE_H
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

class RE{

private:
  struct Cell{
    int from=-1;
    int to=-1;
    int count=0;
    std::vector<int> list;
  };
  static bool compareByCount(const Cell* c1, const Cell* c2){
    return (c1->count)>(c2->count);
  }

  std::vector<std::vector <char> > odd_cycles;
  std::vector<std::vector<Cell*> > counts;
  std::vector<Cell*> cells;


  void count();
  void remove();


public:
  void remove_edges();

};





#endif
