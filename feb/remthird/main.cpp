

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <list>
#include <tuple>
#include <set>



void read_file(std::string& filePath);
void write_file(std::string& output_path);
void skim();
std::vector<std::vector<int> > adjList;



int main(int argc, char* argv[]){
  std::string filePath= argv[1];
  read_file(filePath);
  skim();
  std::string outputpath="new.txt";
  write_file(outputpath);
}


void skim(){
  int totalStates= adjList.size();
  std::vector<int> counts = std::vector<int>(totalStates);

  for(int i =0;i<totalStates;i++){
    for(int j =0;j<adjList[i].size();j++){
      if(counts[adjList[i][j]] > totalStates/3.0){
        for(int k=0;k<adjList[adjList[i][j]].size() && adjList[adjList[i][j]].size()>1 ;k++){
          if(adjList[adjList[i][j]][k] == i){
            adjList[adjList[i][j]].erase(adjList[adjList[i][j]].begin()+k);

            break;
          }
        }
        if(adjList[i].size()>1){
          adjList[i].erase(adjList[i].begin()+j);
          j--;
        }

      }else{
      counts[adjList[i][j]]++;
      }
    }
  }
  for (int i : counts){
    std::cout<<i;
  }
  std::cout<<std::endl;
}









void read_file(std::string& filePath){
  std::ifstream FILE(filePath);
  std::string str;

  while(std::getline(FILE,str)){
    std::vector<int> tmp;
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



void write_file(std::string & output_path){
  std::ofstream FILE;
  FILE.open(output_path);
  for (unsigned long long i = 0; i < adjList.size(); i++) {
    for (unsigned long long j = 0; j < adjList[i].size(); j++) {
      FILE<<adjList[i][j];
      if(j!=(adjList[i].size()-1)){
        FILE<<",";
      }else{
        FILE<<"\n";
      }
    }
  }

  FILE.close();

}
