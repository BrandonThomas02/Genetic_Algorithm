#ifndef POPULATION_H
#define POPULATION_H

#include <string>
#include <vector>
#include <sstream>
#include "Individual.h"

using namespace std;



class population{
    private:
        string key;
        size_t pop_size;
        double _mutation_rate;
        int generation;
        vector<individual>* _population;

    public:
        population();
        population(string&, size_t, double);
        population(const population&);
        population(population&&);
        ~population();

        population& operator=(const population&);
        population& operator=(population&&);

        size_t size() const{return pop_size;}
        double mutation_rate() const{return pop_size;}
        int get_generations() const{return generation;}
        double average_score() const;
        double best_score() const;
        bool is_found() const;
        individual& best_individual() const;
        void print_individuals() const;
        void repopulate();
};

#endif