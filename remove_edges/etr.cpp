


#include "etr.h"


void ETR::find_edges(std::string filePath){
  read_file(filePath);
  std::cout<<"\nsimplified input:"<<std::endl;

  for(auto i : adjList){
    for (auto j : i){
      std::cout<<j<<" ";
    }
    std::cout<<std::endl;
  }
  std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
  EC ec = EC(adjList);
  ec.calc_elem_cycles();
  RE re;
  re.remove_edges(ec.cycles,adjList.size());

  //re.odd_cycles to get odd cycles now
  removed_edges=re.deleted_edges;
  std::cout<<"deleted edges:"<<std::endl;
  for(std::pair<int,int>* p : re.deleted_edges){
    std::cout<<p->first<<" "<<p->second<<std::endl;
  }
  std::cout<<"--------------------------------------------------------------------------------"<<std::endl;


}

void ETR::rm_dups(std::list<int>& tmp,int current_state){
  std::set<int> unique;
  for(int i : tmp){
    if(i!=current_state){
      unique.insert(i);
    }
  }
  tmp.clear();
  for(int i : unique){
      tmp.push_back(i);
  }
}






void ETR::read_file(std::string& filePath){
  std::ifstream FILE(filePath);
  std::string str;
  int count=0;
  while(std::getline(FILE,str)){
    std::list<int> tmp;
    int i=0;
    int lasti=0;
    for(;i<str.size();i++){
      if(str[i]==',' || i==str.size()-1){
        int val=std::stoi(str.substr(lasti,i+1-lasti),nullptr,10)-1;
        tmp.push_back(val);
        lasti=i+1;
      }
    }
    rm_dups(tmp,count);   //remove duplicates
    ++count;
    adjList.push_back(tmp);
   }
   FILE.close();







}
