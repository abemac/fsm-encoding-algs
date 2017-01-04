
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <list>
#include <tuple>
#include <set>

void readFile(std::string& filePath);
void rm_dups(std::list<int>& tmp,int current_state);
std::vector<std::list<int> > adjList;


int main (int argc, char* argv[]){
  if(argc!=2){
    std::cout<<"incorrect usage. enter filepath."<<std::endl;
    return 1;
  }

  std::string filePath=argv[1];
  readFile(filePath);

  for(auto i : adjList){
    for(auto j : i){
      std::cout<<j<<" ";
    }
    std::cout<<std::endl;
  }

}

void readFile(std::string& filePath){
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
void rm_dups(std::list<int>& tmp,int current_state){
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
