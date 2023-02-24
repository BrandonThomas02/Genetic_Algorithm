#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Population.h"

using namespace std;

int main(){
    cout << "Welcome to the Genetic Algorithm!\n";

    bool quit = false;
    while (!quit){
        //get key phrase
        cout << "Enter a phrase to try to match to: ";
        string key;
        getline(cin,key);

        //get population size
        cout << "\nEnter a population size (integer): ";
        int pop_size;
        cin >> pop_size;
        
        //get population mutation rate and convert from percentage to decimal;
        cout << "\nEnter a mutation rate (0-100)%: ";
        double mutation_rate;
        cin >> mutation_rate;
        mutation_rate /= 100;

        cout << "\n Would you like to pause at the end of every generation? (y/n)";
        string result;
        cin >> result;
        result[0] = tolower(result[0]);
        bool pause = (result[0] == 'y')? true : false;

        cout << "\n Would you like to see the results of every generation? (y/n)";
        cin >> result;
        result[0] = tolower(result[0]);
        bool results = (result[0] == 'y')? true : false;

        population* pop = new population(key,pop_size,mutation_rate);
        cout << "Starting the generations!\n";

        while(!pop->is_found()){
            pop->repopulate();
            if(results){
                cout << "Generation: " << pop->get_generations() << "\n"
                    << "\t Best Individual: " << pop->best_individual().get_data() << "\n"
                    << "\t\t Score: " << pop->best_individual().score(key) << "\n"
                    << "\t Average Score: " << pop->average_score() << "\n"
                    << "\n";
            }
            if(pause){
                cout << "Process Paused:\n \ttype any charachter and press enter to continue\n";
                char temp;
                cin >> temp;
            }
        }
        cout << "The Algorithm has finished!\n";
        cout << "Generation: " << pop->get_generations() << "\n"
                    << "\t Best Individual: " << pop->best_individual().get_data() << "\n"
                    << "\t\t Score: " << pop->best_individual().score(key) << "\n"
                    << "\t Average Score: " << pop->average_score() << "\n"
                    << "\n";

        cout << "Would you like to continue? (y/n)";
        cin >> result;
        result[0] = tolower(result[0]);
        results = (result[0] == 'y')? true : false;
        if(results){cout <<'\n'; continue; }
        else{break;}
    }
}