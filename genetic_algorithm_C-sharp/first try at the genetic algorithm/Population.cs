using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace first_try_at_the_genetic_algorithm
{
    class Population
    {
        private Random random;
        private float mutationRate;
        private DNA[] population;
        private List<DNA> matingPool;
        private string target;
        private int generations;
        private bool finished;
        private int perfectScore;

        public Population(string p, float m, int num)
        {
            random = new Random();
            string strRand = (random.ToString());

            target = p;
            mutationRate = m;
            population = new DNA[num];

            //creates num amount of DNA strands to fill the population
            for(int i = 0; i < num; i++)
            {
                population[i] = new DNA(target.Length , random);
            }

            CalcFitness();
            matingPool = new List<DNA>();
            finished = false;
            generations = 0;
            perfectScore = 1;

        }

        public int RandomInt(int min, int max)
        {
            return random.Next(min, max);

        }

        public void CalcFitness()
        {
            for( int i = 0; i < population.Length; i++)
            {
                population[i].Fitness(target);
            }
            //Console.WriteLine("Claculated the fitness");
        }

        //fills the mating pool such that the most fit individuals have the most likely chance of moving their genes on to the next generation
        public void NaturalSelection()
        {
            matingPool.Clear();

            float maxFitness = 0;
            //gets the highest fitness out of all of the individuals
            for(int i = 0; i < population.Length; i++)
            {
                if( population[i].GetFitness() > maxFitness)
                {
                    maxFitness = population[i].GetFitness();
                }
                
            }
            //Console.WriteLine(maxFitness);
            for (int i = 0; i < population.Length; i++)
            {
                float fitness = population[i].GetFitness()/maxFitness;
                int n = (int)fitness * 100;
                for(int j = 0; j < n; j++)
                {
                    matingPool.Add(population[i]);
                    //Console.WriteLine("Adding to the mating pool");
                }
                //Console.WriteLine("Mating Pool Size:" + matingPool.Count());
                //Console.ReadLine();
            }
        }

        //refills the population from the individuals in the mating pool
        public void Generate()
        {
            for( int i = 0; i < population.Length; i++)
            {
                //select two indexes from the mating pool to be the parents
                int a = RandomInt(0, matingPool.Count() - 1);
                int b = RandomInt(0, matingPool.Count() - 1);
                DNA partnerA = matingPool.ElementAt(a);
                DNA partnerB = matingPool.ElementAt(b);

                //mix the DNA from the parents to produce a 'unique offspring'
                DNA child = partnerA.Crossover(partnerB);
                child.Mutate(mutationRate);

                //add the child to the population
                population[i] = child;
            }
            generations++;

        }

        //returns the value of the most similar DNA strand to the key phrase
        public string GetBest()
        {
            float worldRecord = (float)0.0;
            int index = 0;
            for (int i = 0; i < population.Length; i++)
            {
                // sets the most similar individual
                if(population[i].GetFitness() > worldRecord)
                {
                    index = i;
                    worldRecord = population[i].GetFitness();
                }
            }
            //sees if a perfect DNA sequence has been found
            if( worldRecord == perfectScore)
            {
                finished = true;
            }
            return population[index].GetPhrase();
        }

        public bool Finished()
        { return finished; }

        public int Generations()
        { return generations; }

        //returns the average fitness score of all of the DNA strands
        public float GetAverageFitness()
        {
            float total = 0;
            for (int i = 0; i < population.Length; i++)
            {
                total += population[i].GetFitness();
            }
            return (total / population.Length);
        }

        public void DisplayAllPrases()
        {
            for( int i = 0; i < population.Length; i++)
            {
                Console.WriteLine(population[i].GetPhrase());
            }
        }
    }
}
