#ifndef ETR_H
#define ETR_H
#include <string>
#include <vector>
#include "ec.h"
#include "re.h"
#include <fstream>
#include <iostream>
#include <list>
#include <tuple>
#include <set>

class ETR{

private:



  void read_file(std::string& filePath);
  bool min_output;
public:
  void find_edges(std::string filePath);
  std::vector<std::list<int> > adjList;
  std::vector<std::pair<int,int>* > removed_edges;
  ETR(bool min_output_);

};











#endif
