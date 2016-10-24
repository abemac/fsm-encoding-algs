
//http://www.cs.tufts.edu/comp/150GA/homeworks/hw1/Johnson%2075.PDF
#include <iostream>
#include <string>
#include <fstream>
#include <vector>


std::vector<std::vector<unsigned long long> > src_file;

void read_in_file(std::string path);

int main(){
  



}


void read_in_file(const std::string& filePath){
  std::ifstream FILE(filePath);
  std::string str;

  while(std::getline(FILE,str)){
    std::vector<unsigned long long> tmp;
    unsigned long long i=0;
    unsigned long long lasti=0;
    for(;i<str.size();i++){
      if(str[i]==',' || i==str.size()-1){
        unsigned long long val=std::stoull(str.substr(lasti,i+1-lasti),nullptr,10);
        tmp.push_back(val);
        lasti=i+1;
      }
    }
    src_file.push_back(tmp);
   }

   FILE.close();

}
