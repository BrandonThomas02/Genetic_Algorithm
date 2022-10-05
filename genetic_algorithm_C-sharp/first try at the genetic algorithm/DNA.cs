using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace first_try_at_the_genetic_algorithm
{
    class DNA
    {
        //private List<int> used;
        private Random random;
        private float fitness;
        // the genetic sequence
        private char[] genes;

        // Constructor (makes random DNA)
        public DNA(int num , Random rand)
        {
            random = rand;
            genes = new char[num];
            //generate random charachters for every index in the DNA
            for(int i = 0; i < genes.Length ; i++ )
            {
                SetGenes(i);
            }
            //Console.WriteLine(new String(genes));
        }
        
        // Converts character array to string
        public string GetPhrase()
        {
            return new string(genes);
        }

        // Fitness function (returns floating point $ of "correct" characters
        public void Fitness(string target)
        {
            int score = 0;
            for(int i = 0; i < genes.Length; i++)
            {
                if(Convert.ToString( genes[i]).Equals( target.Substring(i , 1)))
                {
                    score++;
                }
            }
            fitness = (float)score / (float)target.Length;
            //Console.WriteLine("Fitness: " + fitness);
        }

        public float GetFitness()
        {
            return fitness;
        }

        //DNA Crossover: takes a random portion of the parent and combines it with the remaining length of the other parent to produce a new DNA strand
        public DNA Crossover(DNA partner)
        {
            // new child
            DNA child = new DNA(genes.Length , random);

            int midpoint = RandomInt(0, genes.Length);

            // half from one, half from the other
            for( int i = 0; i<genes.Length; i++)
            {
                if( i > midpoint)
                { child.genes[i] = genes[i]; }
                else
                { child.genes[i] = partner.genes[i]; }
            }
            return child;
        }

        // Based on mutation probability: goes through each charachter and has a 'mutation rate' chance to change it to a random charachter
        public void Mutate(float mutationRate)
        {
            for( int i = 0; i < genes.Length; i++)
            {
                if( RandomFloat() < mutationRate)
                {
                    SetGenes(i);
                }
            }
        }
        // gets a random number between min and max
        public int RandomInt(int min, int max)
        {

            return random.Next(min, max);
        }

        //returns a random float between 0 and 1
        public float RandomFloat()
        {
            float ret = (float)random.NextDouble();
            return ret;
        }

        //sets the charachter at index g to a random charachter
        public void SetGenes(int g)
        {
            genes[g] = (char)RandomInt(32, 128);
            //Console.WriteLine(genes[g]);
        }
    }
}
