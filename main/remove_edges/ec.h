#ifndef EC_H
#define EC_H


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <stdexcept>

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
  std::vector<std::vector<int>* > bank;
  std::vector<std::vector<int>* > simp_cycles;
  int in_bank(std::vector<int>* test);
  bool equivalent(std::vector<int>* a,std::vector<int>* b);
  //void emptyBank(int start);
  std::vector<bool> flagged;
  bool min_output;

  static bool compareBySize(std::vector<int>* a,std::vector<int>* b){
    if(a->size() == b->size()){
      int sum_a=0;
      for(int i: *a){
        sum_a+=i;
      }
      int sum_b=0;
      for(int i: *b){
        sum_b+=i;
      }
      return sum_a < sum_b;
    }else{
      return a->size()<b->size();
    }
  }


public:
  void calc_elem_cycles();
  EC(const std::vector<std::list<int> > & A_,bool min_output_);
  std::vector<std::vector<int>* > cycles;


};













#endif
