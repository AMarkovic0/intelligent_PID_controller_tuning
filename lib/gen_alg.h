/* **************************************************************************************************************
 * Genetic algorithm library header. This software was made as a part of the PID controller tuning program. 
 * The code is has been written in ANSI C, all memory is allocated staticaly using data types of constant size.
 * The library use floating point aritmetic. 
 * This software is free to use.
 *
 * Created by: Aleksa Markovic
 * Date: May 2020
**************************************************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdint.h>

#define GENE_LEN 3

// Chromosome structure:
//      genetic_code -> gene (array of Kp, Ti, Td)
//      fitness -> Fitness value of the gene
typedef struct Chromosome
{
        float genetic_code[GENE_LEN];
        float fitness;
}_chromosome;

// Algorithm parameters structure:
//      target -> Wanted value of the fitness function
//      possibile_gene_values -> min and max number gene elements could take
//      max_itterations -> maximal number of iterations (generations created)
//      mutation_rate -> chanse to perform mutation on some chromosome
typedef struct AlgorithmParameters
{
        float target;
        int possible_gene_values[2];
        int max_iterations;
        float mutation_rate;
}_parameters;

// ADITIONAL FUNCTIONS:
//
// Random number generator:
//      Generator seed is called in main function (based on CPU clock)
//      Input:
//              lower -> integer value of min number function can generate
//              upper -> integer value of max number function can generate
//      Output:
//              generated random integer
int randomX(int lower, int upper);
//
// Quick sort algorithm function set (sorting from bigger to smaller):
void swap(_chromosome* a, _chromosome* b);
int Qsort_partition(_chromosome* arr, int low, int high);
void Qsort(_chromosome* arr, int low, int high);

// GENETIC ALGORITHM FUNCTION SET:
//
// Function which creates initial chromosome population - creates random genes and calculates fitness for each gene
//      Input:
//              init_pop -> array of chromosome where population chromosomes will be stored
//              fitness_function -> pointer (addres) to fitness function
void initial_population(_chromosome* init_pop, float (*fitness_function)(float*));
//
// Function selectes population for reproduction (n best chromosomes). Sorting is included (Quick sort)
//      Input:
//              population -> array of defined chromosomes
//              selected -> array of chromosomes where selected population will be stored
void selection(_chromosome* population, _chromosome* selected);
//
// Performs crossover combination of two float arrays (genes in our case)
//      Input:
//              parent1 -> float array of parent1 values (first gene)
//              patent2 -> float array of perent2 values (second gene)
//              break_point -> element of parent arrays where parent arrays will be broken and mixed
//      Output:
//              float array of with mixed gene values
//      NOTE: Function returns only one gene [parent1[0:break_point], parent2[break_point:end]]
float* crossover(float parent1[GENE_LEN], float parent2[GENE_LEN], int brek_point);
//
// Creates new generation from selected chromosomes
//      Input:
//              selected_population -> population selected in selection function
//              generation -> chromosome array where new generation will be stored
//              fitness_function
void create_generation(_chromosome* selected_population, _chromosome* generation, float (*fitness_function)(float*));
//
// Function performs algorithm, creates generations and prforms selection. Returns global best chromosome after all iterations
//      Input:
//              population -> initialized chromosome array where population of each generation will be stored
//              selected -> initialized chromosome array where selected chromosomes for reproduction will be stored
//              fitness_funtion -> function which calculates fitness
//      Output:
//              Global best chromosome
_chromosome best_global_chromosome(_chromosome* population, _chromosome* selected, float (*fitness_function)(float*));

// Global parameters structure, necessary to define
extern const _parameters params;

// Array size parameters:
extern const int32_t GENERATION_SIZE;  		// Size of a generation
extern const int32_t REPRODUCTION_SIZE;		// Size of selected genes for reproduction
extern const int32_t SIMULATION_SIZE;		// Size of the simulation time array
