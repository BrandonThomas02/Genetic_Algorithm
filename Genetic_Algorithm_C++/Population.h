#ifndef POPULATION_H
#define POPULATION_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "Individual.h"

using namespace std;

class population{
    private:
        string key;
        size_t pop_size;
        double _mutation_rate;
        size_t generation;
        vector<individual>* _population;

    public:
        //Default Constructor
        population(): key(""), pop_size(1000), _mutation_rate(.02),generation(0){
            _population = new vector<individual>();
        }   

        //Paramataraized constructor
        population(string& arg_key, size_t arg_size = 1000, double arg_mut_rate = .02):
                                    key(arg_key), pop_size(arg_size), _mutation_rate(arg_mut_rate),generation(0){
            _population = new vector<individual>();
            for(size_t i = 0; i < arg_size; i++){
                size_t ind_size = key.size();
                individual ind(ind_size);
                _population->push_back(ind);
            }
        }

        //copy constructor
        population(const population& arg_pop){
            _population = new vector<individual>();
            for(size_t i = 0; i < arg_pop.pop_size; i++){
                _population->push_back(arg_pop._population->at(i));
            }
            pop_size = arg_pop.pop_size;
            generation = arg_pop.generation;
        }

        //move constructor
        population(population&& arg_pop){
            this->pop_size = std::move(arg_pop.pop_size);
            this->_population = std::move(arg_pop._population);
            this->key = std::move(arg_pop.key);
            this->_mutation_rate = std::move(arg_pop._mutation_rate);
            this->generation = std::move(arg_pop.generation);
        }

        //destructor
        ~population(){
            delete _population;
        }

        // copy assignment
        population& operator=(const population& arg_pop){
            if(&arg_pop == this){return *this;}
            delete _population;
            _population = new vector<individual>();
            for(size_t i = 0; i < arg_pop.pop_size; i++){
                _population->push_back(arg_pop._population->at(i));
            }
            pop_size = arg_pop.pop_size;
            generation = arg_pop.generation;
            return *this;
        }

        //move assignment
        population& operator=(population&& arg_pop){
            if(&arg_pop == this){return *this;}
            delete _population;
            this->pop_size = std::move(arg_pop.pop_size);
            this->_population = std::move(arg_pop._population);
            this->key = std::move(arg_pop.key);
            this->_mutation_rate = std::move(arg_pop._mutation_rate);
            this->generation = std::move(arg_pop.generation);
            return *this;
        }

        size_t size() const{
            return pop_size;
        }

        size_t get_generations() const{
            return generation;
        }

        double average_score() const{
            double sum = 0;
            for(size_t i = 0; i < pop_size; i++){
                sum += _population->at(i).score(key);
            }
            double ret = sum / ((double)(pop_size));
            return ret;
        }

        double best_score() const{
            return this->best_individual().score(key);
        }

        bool is_found() const{
            return this->best_score() == 1;
        }

        individual& best_individual() const{
            double best_score = 0;
            individual& best = _population->at(0);
            for(size_t i = 0; i < pop_size; i++){
                if(_population->at(i).score(key) > best_score){
                    best_score = _population->at(i).score(key);
                    best = _population->at(i);
                }
            }
            return best;
        }

        void print_individuals() const{
            for(size_t i = 0; i < _population->size(); i++){
                cout << _population->at(i).get_data() << "\n"
                    << "\t score: " << _population->at(i).score(key) << "\n\n";
            }
        }

        void repopulate(){
            vector<individual> mating_pool;

            for(size_t i = 0; i < pop_size; i++){
                int fitness = _population->at(i).score(key) * 100;

                for(int j = 0; j < fitness; j++){
                    mating_pool.push_back(_population->at(i));
                }

                individual parentA = mating_pool.at(rand()%mating_pool.size());
                individual parentB = mating_pool.at(rand()%mating_pool.size());

                int split_ind = rand() % key.size();
                string child_data = parentA.get_data().substr(0,split_ind) +
                                    parentB.get_data().substr(split_ind,key.size() - split_ind);
                individual child(child_data);
                child.apply_mutation(_mutation_rate);
                _population->at(i) = child;
            }
            generation++;
        }

        
};

#endif