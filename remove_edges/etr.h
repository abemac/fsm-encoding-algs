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

class ETR{

private:



  void read_file(std::string& filePath);

public:
  void find_edges(std::string filePath);
  std::vector<std::list<int> > adjList;
  std::vector<std::pair<int,int>* > removed_edges;


};











#endif
