#include<stdio.h>
#include<math.h>

#include"lib/gen_alg.h"

// Definition of PI number
#define PI acos(-1.0f)

float calculate_fitness(float genetic_code[GENE_LEN]);

const int32_t GENERATION_SIZE = 300;
const int32_t REPRODUCTION_SIZE = 30;
const int32_t SIMULATION_SIZE = 10000;

const _parameters params = {0.0f, {0,20}, 5, 0.2f};

int main( int argc , char* argv[] )
{
	// Random seed
        clock_t t_begin = clock();
        srand((int32_t)time(0));

        // Initialize population and selected chromosome arrays
        _chromosome population[GENERATION_SIZE];
        _chromosome selected[REPRODUCTION_SIZE];

        // Initialize global best chromosome
        _chromosome GLOBAL_BEST;

        // Perform algorithm and find global best chromosome
        GLOBAL_BEST = best_global_chromosome(population, selected, &calculate_fitness);

        // Print Chromosome values and fitness function
        printf("Fitness function of the best chromosome: %.8f\n", GLOBAL_BEST.fitness);
        for(int32_t j = 0; j < GENE_LEN; j++)
                printf("%f ", GLOBAL_BEST.genetic_code[j]);
        printf("\n");

        // Stop timer and print executing time
        clock_t t_end = clock();
        double Time = (double)(t_end - t_begin) / CLOCKS_PER_SEC;
        printf("Time taken: %f[s]\n", Time);

        return 0;

}

/****************************************************************************************************************************
 *
 * FITNESS FUNCTION
 *
 * ************************************************************************************************************************* */
float calculate_fitness(float genetic_code[GENE_LEN])
{
        float fitness_value = 0.0f;
        float dt = 0.0002f; // dt value IMPORTANT VARIABLE

        // System parameters:
        float Vmax = 10.0f;
        float Vmin = -10.0f;
        float C1 = 0.1284f/0.0021f;
        float C2 = 0.084f/0.0021f;

        float omega_z = PI/2.0f;

        // System variables:
        float errX = omega_z;
        float err_int = 0.0f;
        float err_dot = 0.0f;
        float Kp = genetic_code[0];
        float Ti = genetic_code[1];
        float Td = genetic_code[2];

        float Vp = 0.0f;
        float omega[3] = {0.0f};
        float theta = 0.0f;
        float theta_dot = 0.0f;

        float Udot = 0.0f;
        float U = 0.0f;

        float sum = 0.0f;
        for(int32_t i = 0; i < SIMULATION_SIZE-1; i++)
        {
                // Error calculations:
                errX =  omega_z - omega[1];
                err_int = err_int + errX*dt;
                err_dot = (errX - (omega_z - omega[0]))/dt;

                if(i % 10 == 0 || i == 0)
                {
                        // Calculate control (PID):
                        Vp = Kp*(errX + 1/Ti*err_int + Td*err_dot);

                        // Anti-windup implementation
                        if(Vp > Vmax)
                        {
                                err_int = err_int + (-Vp + Vmax);
                                Vp = Kp*(errX + 1/Ti*err_int + Td*err_dot);
                        }
                        if(Vp < Vmin)
                        {
                                err_int = err_int + (-Vp + Vmin);
                                Vp = Kp*(errX + 1/Ti*err_int + Td*err_dot);
                        }

                        // Low-pass filter:
                        Udot = 1/(40*PI)*Vp - 1/(40*PI)*U;
                        U = U + Udot*0.002;
                        Vp = U;

                }

                // Solve equations:
                theta_dot = C1*Vp - C2*theta;
                theta = theta + theta_dot*dt;
                omega[2] = omega[1] + theta*dt;

                // Shift time:
                omega[0] = omega[1];
                omega[1] = omega[2];
                omega[2] = 0;
		
		if(errX < 0)
                        sum = sum - errX/10.0f;
                else
                        sum = sum + errX*100.0f;
        }

        // Calculate fitness:
        fitness_value = params.target - sum/SIMULATION_SIZE;
        // If NaN, discard
        if(fitness_value != fitness_value)
                fitness_value = -100000.0f;

        return fitness_value;

}

