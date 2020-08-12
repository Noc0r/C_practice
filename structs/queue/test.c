#include "priority_queue.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct cars
{
    unsigned int speed;
    unsigned int cost;
    unsigned int weight;
} cars;

long long car_prior(cars *a)
{
    return (((cars *)a)->cost + ((cars *)a)->weight) / ((cars *)a)->speed;
}

int compare(void *a, void *b)
{
    long long a_prior = car_prior((cars*)a);
    long long b_prior = car_prior((cars*)b);
    if (a_prior > b_prior)
        return 1;
    else if (a_prior == b_prior)
        return 0;
    return -1;
}

void print_car(cars *car)
{
    printf("Priority - %lld\n", car_prior((cars*)car));
    printf("Speed - %d\nWeight - %d\nCost - %d\n\n", car->speed, car->weight, car->cost);
}

int main()
{
    //QUEUE TESTS START
    queue_lib *queue_func = create_queue_library();
    queue *test_queue = queue_func->create_queue();
    for (int i = 0; i < 100; i++)
    {
        int *k = (int *)malloc(sizeof(int));
        *k = i;
        queue_func->push_back(test_queue, k);
    }
    printf("%d\n", *(int *)queue_func->top(test_queue));
    queue_func->pop_front(test_queue);
    queue_func->pop_front(test_queue);
    queue_func->pop_front(test_queue);
    queue_func->pop_front(test_queue);
    printf("%d\n", *(int *)queue_func->top(test_queue));
    free(queue_func);
    //QUEUE TESTS END

    //BINARY HEAP TESTS START
    srand(time(0));
    prior_queue_lib *bin_lib = create_priorqueue_library();
    prior_queue *bin_heap = bin_lib->create_prior_queue(compare);
    for (int i = 0; i < 10; i++)
    {
        cars *new_car = (cars *)malloc(sizeof(cars));
        new_car->cost = rand() % 10000 + 120000;
        new_car->speed = rand() % 100 + 80;
        new_car->weight = rand() % 100 + 700;
        bin_lib->insert(bin_heap, new_car);
    }
    for (int i = 0; i < 10; i++)
    {
        cars *new_car = (cars *)bin_lib->top(bin_heap);
        print_car(new_car);
        bin_lib->pop(bin_heap);
    }
    free(bin_lib);
    //BINARY HEAP TESTS END
    return 0;
}