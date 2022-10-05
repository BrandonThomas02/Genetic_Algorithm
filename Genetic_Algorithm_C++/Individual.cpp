#include <string>
#include <vector>
#include <sstream>
#include "Individual.h"

using namespace std;


individual::individual(size_t& size):_size(size){
    data = "";
    for(size_t i = 0; i < size; i++){
        data += char((rand() % 95) + 32);
    }
}
individual::individual(const individual& ind){
    _size = ind.size();
    data = ind.get_data();
}
individual::individual(individual&& ind){
    _size = move(ind._size);
    data = move(ind.data);
}
individual::~individual(){
    _size = 0;
    data = string();
}

individual& individual::operator=(const individual& ind){
    _size = ind.size();
    data = ind.get_data();
    return *this;
}
individual& individual::operator=(individual&& ind){
    _size = move(ind._size);
    data = move(ind.data);
    return *this;
}

const double individual::score(const string key){
    int num_correct = 0;
    for(size_t i = 0; i < data.size(); i++){
        if(key.at(i) == data.at(i)){num_correct++;}
    }
    return ((double)(num_correct)/(double)(_size));
}
void individual::apply_mutation(double mut_rate){
    int mod = 1/mut_rate;
    for(size_t i = 0; i < _size; i++){
        if(rand() % mod == 0){
            data.at(i) = char(rand()%95 + 32);
        }
    }
}
