//linked list for maintaining the queue of landing flights
typedef struct Landing
{
    int flightNumber;
    struct Landing *next;
} landing;

//linked list for maintaining the queue of taking off flights
typedef struct Takeoff
{
    int flightNumber;
    struct Takeoff *next;
} takeoff;

void joinQueue(landing **, takeoff **, int *, int);

void leaveQueue(landing **, takeoff **, int);

int randomTimeDiff(int *);

void fixedTimeDiff(int *);

void flightGenerator(landing **, takeoff **, int *);

void dispWaiting(landing **, takeoff **, double *, double *, int);

void flightToRunway(landing **, takeoff **, int *, int *, double *);

void startAirport();