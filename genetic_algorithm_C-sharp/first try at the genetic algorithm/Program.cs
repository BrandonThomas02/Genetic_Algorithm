using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace first_try_at_the_genetic_algorithm
{
    public class Program
    {
        static void Main(string[] args)
        {
            new Program();
        }

        private string target;
        private int popmax;
        private float mutationRate;
        private Population population;

        public Program()
        {
            do
            {
                //get user input for target phrase
                Console.WriteLine("Enter Phrase");
                target = Console.ReadLine();
                while(target == "")
                {
                    Console.WriteLine("please enter a value:");
                    target = Console.ReadLine();
                }


                popmax = 10000;
                mutationRate = (float)0.02;
                population = new Population(target, mutationRate, popmax);
                Console.WriteLine("Starting!");

                Stopwatch sw = Stopwatch.StartNew();

                while (!population.Finished())
                {

                    Draw();

                }

                sw.Stop();

                DisplayInfo(sw.ElapsedMilliseconds, true);
                Console.ReadLine();

                Console.WriteLine("run another? Y/N");
                string answer = Console.ReadLine();
                if (answer.ToLower() == "n")
                {
                    break;
                }
            } while (true);
        }

        public void Draw()
        {
            Stopwatch sw = Stopwatch.StartNew();
            //fills the mating pool with individuals
            population.NaturalSelection();

            //generates a new population based on the mating poop
            population.Generate();

            population.CalcFitness();
            sw.Stop();
            long time = sw.ElapsedMilliseconds;
            sw.Reset();

            DisplayInfo(time,false);
            //Console.ReadLine();
            //Console.Clear();

        }

        public void DisplayInfo(long time,bool finished)
        {
            if (finished)
            {
                Console.WriteLine("Finished!");
            }
            Console.WriteLine("Generation: " + population.Generations());
            Console.WriteLine("Best Phrase: " + population.GetBest());
            Console.WriteLine("Average Fitness: " + (int)(population.GetAverageFitness()*100) + "%");
            if (!finished){
                Console.WriteLine("Geteation Time: " + ((float)time / (float)1000.0) + " sec");
            }
            else
            {
                Console.WriteLine("Average Time/Generation: " + ((float)time / (float)1000.0 / (float)population.Generations()) + " sec");
            }
            Console.WriteLine();
            //Console.WriteLine("Mutation rate: " + (mutationRate * 100) + "%");


        }

    }
}

