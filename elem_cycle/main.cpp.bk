
//http://www.cs.tufts.edu/comp/150GA/homeworks/hw1/Johnson%2075.PDF
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

std::vector<std::list<int> > A,B;
std::vector<bool> blocked;
int s;

std::list<int> stack;


void init(const std::string& filePath);
void UNBLOCK(int u);
bool CIRCUIT(int v);
void OUTPUT();


int main(){
  init("test_graphs/test3.csv");

  s=0;

  while (s < A.size()){
    CIRCUIT(s);
    A[s].clear();
    for (int i =0;i<A.size();++i){
      A[i].remove(s);
    }
    for (int i =0;i<A.size();++i){
      blocked[i]=false;
      B[i].clear();
    }
    ++s;
  }





}

bool CIRCUIT(int v){
  bool f = false;
  stack.push_back(v);
  blocked[v]=true;

  for(auto itr = A[v].begin();itr!=A[v].end();++itr){
    int w = *itr;
    if(w==s){
      OUTPUT();
      f=true;
    }else if (!blocked[w]){
      if(CIRCUIT(w)){
        f=true;
      }
    }
  }
  if(f){
    UNBLOCK(v);
  }
  else{
    for(auto itr = A[v].begin();itr!=A[v].end();++itr){
      int w = *itr;
      if(std::find(B[w].begin(),B[w].end(),v)== B[w].end()){
        B[w].push_back(v);
      }
    }
  }
  stack.pop_back();
  return f;



}

void UNBLOCK(int u){
  blocked[u]=false;
  for(auto itr = B[u].begin();itr!=B[u].end();){
    int w = *itr;
    itr=B[u].erase(itr);
    if(blocked[w]){
      UNBLOCK(w);
    }
  }
}


void OUTPUT(){
    int w=0;
    for (auto iw = stack.begin(); iw != stack.end(); ++iw)
        {
           w++;
        }
    if(w%2==1 && w>2)//yuan changed
      {
    for (auto iw = stack.begin(); iw != stack.end(); ++iw)
        std::cout << *iw << "->";

    std::cout <<s<< std::endl;
  }
    return;
}

void init(const std::string& filePath){
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
    A.push_back(tmp);
   }
   B.resize(A.size());
   blocked.resize(A.size());
   for(int i = 0;i<A.size();i++){
     blocked[i]=false;
   }
   FILE.close();

}
