#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "server.h"

#define coming 1
#define going 0

/*This functions adds a flight to the end of a queue*/
void joinQueue(landing **headL, takeoff **headT, int *new_data, int status)
{
    if (status == coming)
    {
        landing *new_node = (landing *)malloc(sizeof(landing));
        landing *last = *headL;
        new_node->flightNumber = *new_data;
        new_node->next = NULL;
        if (*headL == NULL)
        {
            *headL = new_node;
            return;
        }
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = new_node;
        return;
    }
    else
    {
        takeoff *new_node = (takeoff *)malloc(sizeof(takeoff));
        takeoff *last = *headT;
        new_node->flightNumber = *new_data;
        new_node->next = NULL;
        if (*headT == NULL)
        {
            *headT = new_node;
            return;
        }
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = new_node;
        return;
    }
}

/*This function removes a flight from the queue when it has left*/
void leaveQueue(landing **headL, takeoff **headT, int status)
{
    if (status == coming)
    {
        if (*headL != NULL)
        {
            landing *temp = *headL;
            *headL = temp->next;
            free(temp);
        }
    }
    else
    {
        if (*headT != NULL)
        {
            takeoff *temp = *headT;
            *headT = temp->next;
            free(temp);
        }
    }
}

/*Creates a random time difference between lining up of flights for takeoff or landing*/
int randomTimeDiff(int *time_taken)
{
    int sec = rand() % 7;
    unsigned int ret_time = time(0) + sec;
    while (time(0) < ret_time)
        ;
    *time_taken = *time_taken + sec;
    return sec;
}

/*Assigns the flight number to a flight joining the landing or take off linked list, which it choses randomly*/
void flightGenerator(landing **headL, takeoff **headT, int *new_data)
{
    for (int i = 0; i < 4; i++)
    {
        int rand_num = rand();
        if (rand_num % 4 == 0 || rand_num % 7 == 0)
        {
            ++*new_data;
            joinQueue(headL, headT, new_data, going);
        }
        else if (rand_num % 5 == 0 || rand_num % 6 == 0)
        {
            ++*new_data;
            joinQueue(headL, headT, new_data, coming);
        }
    }
}

/*Displays the flights in queue for landing or takeoff*/
void dispWaiting(landing **headL, takeoff **headT, double *landing_waiting_time, double *takeoff_waiting_time, int random_time)
{
    landing *temp1 = *headL;
    takeoff *temp2 = *headT;
    printf("\nFLIGHTS IN QUEUE:\n\n");
    printf("Landing:\n");
    while (temp1 != NULL)
    {
        printf("Flight number: %d\n", temp1->flightNumber);
        temp1 = temp1->next;
        *landing_waiting_time = *landing_waiting_time + random_time;
    }
    printf("\n");
    printf("Takeoff:\n");
    while (temp2 != NULL)
    {
        printf("Flight number: %d\n", temp2->flightNumber);
        temp2 = temp2->next;
        *takeoff_waiting_time = *takeoff_waiting_time + random_time;
    }
}

/*Manages the runways and which one to chose for a flight from the queues*/
/*
    Runway 1: Landing
    Runway 2: Takeoff
    Runway 3: Both (landing given a higher preference)
*/
void flightToRunway(landing **headL, takeoff **headT, int *landed, int *tookoff, double *runway_idle_time)
{
    landing *temp1 = *headL;
    takeoff *temp2 = *headT;
    if (temp1 != NULL)
    {
        printf("Flight number %d landed on runway 1\n", temp1->flightNumber);
        temp1 = temp1->next;
        leaveQueue(headL, headT, coming);
        ++*landed;
    }
    else
    {
        printf("Runway 1 is free\n");
        ++*runway_idle_time;
    }
    if (temp2 != NULL)
    {
        printf("Flight number %d took off on runway 2\n", temp2->flightNumber);
        temp2 = temp2->next;
        leaveQueue(headL, headT, going);
        ++*tookoff;
    }
    else
    {
        printf("Runway 2 is free\n");
        ++*runway_idle_time;
    }
    if (temp1 != NULL)
    {
        printf("Flight number %d landed on runway 3\n", temp1->flightNumber);
        temp1 = temp1->next;
        leaveQueue(headL, headT, coming);
        ++*landed;
    }
    else if (temp2 != NULL)
    {
        printf("Flight number %d took off on runway 3\n", temp2->flightNumber);
        temp2 = temp2->next;
        leaveQueue(headL, headT, going);
        ++*tookoff;
    }
    else
    {
        printf("Runway 3 is free\n");
        ++*runway_idle_time;
    }
}

/*Creates a time difference of 1 sec between two pieces of code execution*/
void fixedTimeDiff(int *time_taken)
{
    int sec = 1;
    unsigned int ret_time = time(0) + sec;
    while (time(0) < ret_time)
        ;
    ++*time_taken;
}

/*Creates a time difference of 1 sec between two pieces of code execution*/
void startAirport()
{
    srand(time(0));
    landing *headL = NULL;
    takeoff *headT = NULL;
    int flight_number = 0;
    int landing_flights = 0;
    int takeoff_flights = 0;
    double runway_idle_time = 0;
    double landing_waiting_time = 0;
    double takeoff_waiting_time = 0;
    int landing_leftover = 0;
    int takeoff_leftover = 0;
    int time_before = 0;
    int total_runtime = 0;

    int i;
    for (i = 0; i < 30; i++)
    {
        flightGenerator(&headL, &headT, &flight_number);
        time_before = randomTimeDiff(&total_runtime);
        printf("____________________________\n");
        dispWaiting(&headL, &headT, &landing_waiting_time, &takeoff_waiting_time, time_before);
        printf("____________________________\n\n");
        fixedTimeDiff(&total_runtime);
        flightToRunway(&headL, &headT, &landing_flights, &takeoff_flights, &runway_idle_time);
    }

    while (headL != NULL)
    {
        ++landing_leftover;
        headL = headL->next;
    }
    while (headT != NULL)
    {
        ++takeoff_leftover;
        headT = headT->next;
    }

    runway_idle_time = runway_idle_time / (3 * i);
    landing_waiting_time = landing_waiting_time / total_runtime;
    takeoff_waiting_time = takeoff_waiting_time / total_runtime;

    printf("\nSimulation has concluded after %d units\n", i);
    printf("\nAnalysis:\n\n");
    printf("Total number of planes processed:     %d\n", flight_number);
    printf("Number of planes landed:              %d\n", landing_flights);
    printf("Number of planes took off:            %d\n", takeoff_flights);
    printf("Number of planes ready to land:       %d\n", landing_leftover);
    printf("Number of planes ready to takeoff:    %d\n", takeoff_leftover);
    printf("Percentage of time runway is idle:    %.2f\n", runway_idle_time);
    printf("Average wait time to land:            %.2f\n", landing_waiting_time);
    printf("Average wait time to take off:        %.2f\n", takeoff_waiting_time);
}