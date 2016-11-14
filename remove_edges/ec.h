#ifndef EC_H
#define EC_H


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>


class EC{

private:
  std::vector<std::list<int> > A,B;
  std::vector<bool> blocked;
  int s;

  std::list<int> stack;


  void init();
  void UNBLOCK(int u);
  bool CIRCUIT(int v);
  void SAVE_CYCLE();

  void simpflipy_cycles();


public:
  void calc_elem_cycles();
  EC(const std::vector<std::list<int> > & A_);
  std::vector<std::vector<int>* > cycles;


};













#endif
