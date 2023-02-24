#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <string>
#include <vector>
#include <sstream>

using namespace std;


class individual{
    private:
        string data;
        size_t _size;
    public:
        individual(): data(""), _size(0){};

        individual(size_t& size):_size(size){
            data = "";
            for(size_t i = 0; i < size; i++){
                data += char((rand() % 95) + 32);
            }
        }

        individual(string other_data){
            data = other_data;
            _size = data.size();
        }

        individual(const individual& ind){
            _size = ind._size;
            data = ind.data;
        }
        individual(individual&& ind){
            _size = move(ind._size);
            data = move(ind.data);
        }
        ~individual(){
            _size = 0;
            data = string();
        }

        individual& operator=(const individual& ind){
            _size = ind._size;
            data = ind.data;
            return *this;
        }
        individual& operator=(individual&& ind){
            _size = move(ind._size);
            data = move(ind.data);
            return *this;
        }

        double score(const string key) const{
            int num_correct = 0;
            for(size_t i = 0; i < data.size(); i++){
                if(key.at(i) == data.at(i)){num_correct++;}
            }
            return ((double)(num_correct)/(double)(_size));
        }
        void apply_mutation(double mut_rate){
            int mod = 1/mut_rate;
            for(size_t i = 0; i < _size; i++){
                if(rand() % mod == 0){
                    data.at(i) = char(rand()%95 + 32);
                }
            }
        }

        size_t size() const{
            return _size;
        }

        string get_data() const{
            return data;
        }
};

#endif