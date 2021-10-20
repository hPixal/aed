#include <iostream>
#include <vector>
using namespace std;
typedef int iterator;
typedef int range_t;

class map {
private:
  vector<int> vals;
public:
  map(int N_) { 
    this->vals.resize(N_);
    for(auto x : vals){
        x = -1;
    }};
  iterator find(int key) { 
      if(key>this->vals.size())
      { return -99999; }
      return vals[key];}

  range_t & operator[](int key) { return this->vals[key]; }
  void erase(iterator p) { *p = -1; }
  int erase(int key) { vals[key] = -1 }
};

map::map(int N_){
    this->vals.resize(N_);
    for(auto x : vals){
        x = -1;
    }
}

iterator map::find(int key){
    if(key>this->vals.size()){
        return -99999;
    }
    return vals[key];
}


 //(8 (1 (8 0 6) (16 (16 (13 13 16 (0 1))))))