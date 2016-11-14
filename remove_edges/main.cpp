


#include "etr.h"
#include <iostream>


int main (int argc, char* argv[]){
  std::string filePath= argv[1];
  ETR etr;
  etr.find_edges(filePath);
  
}
