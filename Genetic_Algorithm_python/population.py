import random as rand

from individual import Individual


class Population:

    key = ""
    key_size = 0
    size = 0
    mutation_rate = 0
    individual_list = []

    def __init__(self, key_string, pop_size=10000, mutation=.02):
        self.size = pop_size
        self.mutation_rate = mutation
        self.key = key_string
        self.key_size = len(key_string)
        for i in range(0, self.size):
            ind = Individual(self.key_size)
            self.individual_list.insert(0, ind)

    """returns the size of the population"""
    def get_population_size(self):
        return self.size

    """returns the population mutation rate"""
    def get_mutation_rate(self):
        return self.mutation_rate

    """returns the average score of each individual in the population"""
    def get_average_score(self):
        total = 0.0
        for ind in self.individual_list:
            total += ind.get_score(self.key)
        return total / self.size

    """returns the score of the most similar individual to the key"""
    def get_best_score(self):
        best_score = self.individual_list[0].get_score(self.key)
        for ind in self.individual_list:
            if ind.get_score(self.key) > best_score:
                best_score = ind.get_score(self.key)
        return best_score

    def get_best_individual(self):
        best_score = self.individual_list[0].get_score(self.key)
        best_individual = self.individual_list[0]
        for ind in self.individual_list:
            if ind.get_score(self.key) > best_score:
                best_score = ind.get_score(self.key)
                best_individual = ind

        return best_individual

    """returns if an individual matches the key"""
    def is_found(self):
        for ind in self.individual_list:
            if ind.get_score(self.key) == 1:
                return True
        return False

    """prints all of the individuals values"""
    def print_individuals(self):
        for ind in self.individual_list:
            print(ind.get_value())

    """start the mutation process for every individual"""
    def mutate_individuals(self):
        for ind in self.individual_list:
            ind.apply_mutation(self.mutation_rate)

    """repopulates the population by randomly pulling from a list of individuals with a proportionate
     amount of copies of an individual based on that individuals score"""
    def repopulate(self):
        best_score = self.get_best_score()

        parent_list = []
        for ind in self.individual_list:
            percent_score = int((ind.get_score(self.key)/best_score) * 100)
            parent_list.extend([ind]*percent_score)

        midpoint = rand.randint(0, len(self.key))
        for i in range(self.size):
            parent_1 = parent_list[rand.randint(0, len(parent_list) - 1)]
            parent_2 = parent_list[rand.randint(0, len(parent_list) - 1)]

            new_value = parent_1.value[:midpoint] + parent_2.value[midpoint:]
            self.individual_list[i].value = new_value
