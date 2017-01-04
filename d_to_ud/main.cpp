
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <list>
#include <tuple>
#include <set>

void readFile(std::string& filePath);
void writeFile(std::string& filePath);
void rm_current_state(std::set<int>& tmp,int current_state);
void to_und();
std::vector<std::set<int> > adjList;


int main (int argc, char* argv[]){
  if(argc!=2){
    std::cout<<"incorrect usage. enter filepath."<<std::endl;
    return 1;
  }

  std::string filePath=argv[1];
  readFile(filePath);

  // for(auto i : adjList){
  //   for(auto j : i){
  //     std::cout<<j<<" ";
  //   }
  //   std::cout<<std::endl;
  // }
  to_und();
  //std::cout<<"undirected:"<<std::endl;
  // for(auto i : adjList){
  //   for(auto j : i){
  //     std::cout<<j<<" ";
  //   }
  //   std::cout<<std::endl;
  // }
  filePath.pop_back();
  filePath.pop_back();
  filePath.pop_back();
  filePath.pop_back();
  filePath.append("_und.csv");
  std::string pre="undirected_benchmarks";
  filePath= pre + filePath.substr(10,filePath.size()-10);
  writeFile(filePath);
}


void to_und(){
  for(int i =0;i<adjList.size();i++){
    for(int j : adjList[i]){
      if(adjList[j].count(i)==0){
        adjList[j].insert(i);
      }
    }
  }
}

void readFile(std::string& filePath){
  std::ifstream FILE(filePath);
  std::string str;
  int count=0;
  while(std::getline(FILE,str)){
    std::set<int> tmp;
    int i=0;
    int lasti=0;
    for(;i<str.size();i++){
      if(str[i]==',' || i==str.size()-1){
        int val=std::stoi(str.substr(lasti,i+1-lasti),nullptr,10)-1;
        tmp.insert(val);
        lasti=i+1;
      }
    }
    rm_current_state(tmp,count);   //remove duplicates
    ++count;
    adjList.push_back(tmp);
   }
   FILE.close();


}
void rm_current_state(std::set<int>& tmp,int current_state){
  tmp.erase(current_state);
}

void writeFile(std::string& filePath){
  std::ofstream FILE(filePath);
  for(auto set : adjList){
    bool first=true;
    for(int j: set){
      if(first){
        FILE << j;
        first=false;
      }
      else{
        FILE<<","<<j;
      }

    }
    FILE<<"\n";
  }

  FILE.close();
}
