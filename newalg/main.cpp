
#include <string>
#include <vector>
#include "ec.h"
#include "re.h"
#include <fstream>
#include <iostream>
#include <list>
std::vector<std::list<int> > adjList;


void read_file(std::string& filePath);

int main(int argc, char* argv[]){
  std::string filePath= argv[1];
  read_file(filePath);

  EC ec = EC(adjList);
  ec.calc_elem_cycles();
  RE re;
  re.remove_edges(ec.cycles,adjList.size());

  //re.odd_cycles to get odd cycles now
  std::cout<<"deleted edges"<<std::endl;
  for(auto p : re.deleted_edges){
    std::cout<<p->first<<" "<<p->second<<std::endl;
  }



}








void read_file(std::string& filePath){
  std::ifstream FILE(filePath);
  std::string str;

  while(std::getline(FILE,str)){
    std::list<int> tmp;
    int i=0;
    int lasti=0;
    for(;i<str.size();i++){
      if(str[i]==',' || i==str.size()-1){
        int val=std::stoi(str.substr(lasti,i+1-lasti),nullptr,10);
        tmp.push_back(val);
        lasti=i+1;
      }
    }
    adjList.push_back(tmp);
   }
   FILE.close();
}
