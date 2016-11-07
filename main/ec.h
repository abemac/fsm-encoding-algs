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
  std::vector<std::vector<int>* > cycles;

  void init();
  void UNBLOCK(int u);
  bool CIRCUIT(int v);
  void SAVE_CYCLE();

  void simpflipy_cycles();


public:
  void print_elem_cycles();
  EC(const std::vector<std::list<int> > & A_);



};













#endif
