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
        individual(string& str): data(str), _size(str.size()){}
        individual(size_t&);
        individual(const individual&);
        individual(individual&&);
        ~individual();

        individual& operator=(const individual&);
        individual& operator=(individual&&);

        string get_data() const {return data;}
        size_t size() const {return _size;}
        const double score(const string);
        void apply_mutation(const double);
};

#endif