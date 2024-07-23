/*
 * Copyright 2024 Oleg Borodin <onborodin@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int64_t* measures;
    int capa;
    int posn;
} integrator_t;

void integrator_init(integrator_t* integrator, int capa) {
        integrator->capa = capa;
        integrator->posn = 0;
        size_t memsize = integrator->capa * sizeof(int64_t);
        integrator->measures = malloc(memsize);
        for (int i = 0; i < integrator->capa; i++) {
                integrator->measures[i] = 0;
        }
}

void integrator_addmeasure(integrator_t* integrator, int64_t measure, int64_t period) {
        if (++integrator->posn >= integrator->capa) {
                integrator->posn = 0;
        }
        integrator->measures[integrator->posn] = measure * period;
}

int64_t integrator_calcmeasure(integrator_t* integrator) {
        int64_t intgsum = 0;
        for (int i = 0; i < integrator->capa; i++) {
                intgsum += integrator->measures[i];
        }
        return intgsum;
}

int64_t getfakemeasure(int64_t min, int64_t max) {
        return rand() % (max - min) + min;
}

int main(int argc, char **argv){

        integrator_t integrator;
        int integrator_capa = 128;
        int integrator_meascount = 64 * 1024;

        int64_t minl_measure = 120;
        int64_t maxl_measure = 150;
        int64_t integdevider = 1000;

        integrator_init(&integrator, integrator_capa);
        for (int i = 0; i < integrator_meascount; i++) {

                int64_t measure = getfakemeasure(minl_measure, maxl_measure);
                int64_t period = 16;
                integrator_addmeasure(&integrator, measure, period);

                if ((i % (integrator_capa * 16)) == 1) {
                        int64_t integsum = integrator_calcmeasure(&integrator);
                        printf("%12ld\n", integsum / integdevider);
                }
        }
	return 0;
}

