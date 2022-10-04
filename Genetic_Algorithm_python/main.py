from population import Population
import timeit


def main():
    key = input("input the target string: ")
    mutation_rate = float(input("enter mutation rate (percent): "))/100
    population_size = int(input("enter a population size: "))
    pop = Population(key, population_size, mutation_rate)

    # pop.print_individuals()

    sum_time = 0.0
    num_generations = 0
    while not pop.is_found():
        start = timeit.default_timer()
        pop.repopulate()
        pop.mutate_individuals()
        stop = timeit.default_timer()
        print("Generation:", num_generations)
        print("Average Population Score:", pop.get_average_score())
        print("Best Individual Score:", pop.get_best_score())
        print("Best Individual", pop.get_best_individual().get_value())
        print("Generation Time: ", (stop-start), "seconds")
        sum_time += stop-start
        num_generations += 1

    print("Final Generation")
    print("Generation:", num_generations)
    print("Average Population Score:", pop.get_average_score())
    print("Best Individual Score:", pop.get_best_score())
    print("Best Individual", pop.get_best_individual().get_value())
    print("Average Generation Time:", sum_time/num_generations, "seconds")


if __name__ == '__main__':
    main()
