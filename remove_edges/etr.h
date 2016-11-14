#ifndef ETR_H
#define ETR_H
#include <string>
#include <vector>
#include "ec.h"
#include "re.h"
#include <fstream>
#include <iostream>
#include <list>


class ETR{

private:

  std::vector<std::list<int> > adjList;

  void read_file(std::string& filePath);

public:
  void find_edges(std::string filePath);
  



};











#endif
