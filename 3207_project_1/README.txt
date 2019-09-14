========================================================================================================
Giorgio's Discrete Event Simulator
CIS-3207
Jordan Steacker
========================================================================================================

    In order to create the event simulator, I broke the project into multiple C files. These files include:

"main.c", "Event.c", "PriorityQueue.c", and "FIFOQueue.c". Each of these C files, excluding "main.c",

has a corresponding header file so they can be accessed by the other files as needed. Lastly, the

project includes some text based files: "config.txt", "log.log", "README.txt", and "runs.txt".

config stores values for the constants used in main. log stores the written results of main, and

runs is documentation of test runs of the program. This README file will include documentation on

each C file and its functions.


========================================================================================================
Event.c
========================================================================================================
    This file deals with the Event struct, which is used to keep track details of a job in the

simulator. The Event struct itself stores int values for an ID, a type, and a time. There are two

functions in the Event.c file: createEvent() and printEvent().


    createEvent() takes three ints in the parameters for ID, type, and time. The function then returns

a Event with those parameters as its data values. This function is how jobs will be created throughout

the simulation.


    printEvent() takes an Event parameter and prints out different messages depending on the Event's type

value. If the Event is not of type 0 or 1, which is the designated type for the START and END of the

simulation, then the ID will be displayed as well. Regardless of type, the Event's time is always displayed.


========================================================================================================
PriorityQueue.c
========================================================================================================
    This file deals with the PriorityQueue struct, which is used to manage the event queue of the main

function. The PriorityQueue struct stores two int values for its capacity and current size. It also

contains an Event array to store the jobs that will be used in the queue.


    *initializePQ() is used for the initializing of a PriorityQueue struct. It takes an int parameter

as capacity and sets that as the struct's capacity. The current size is set to 0 and space is allocated

for the struct and its Event array.


    priorityQInsert() takes a PriorityQueue and an Event as parameters. If the PriorityQueue is not full,

then the Event is inserted into it. The heapBotTop() function is then called to re-sort the PriorityQueue.

Lastly, the current size of the PriorityQueue is incremented by 1.


    heapBotTop() takes a PriorityQueue and an int for index as parameters. The function heapifies from

the bottom to the top by comparing the node at the queue's indexed value to its parent. It also compares

it to the indexed value's previous entry. If either the parent or previous entry are larger than the indexed

value, they are swapped and heapBotTop() is recursively called.


    popMin() takes a PriorityQueue as a parameter. If the queue is not empty, the event at index 0 is

returned and all entries are shifted to fill in the gap. The current size of the queue is also

subtracted by 1.


    printPQ() takes a PriorityQueue as a parameter. It calls the printEvent() function for every Event

in the queue.


    destroy() takes a PriorityQueue as a parameter. It frees the space allocated to the queue entered.


    isFull() and isEmpty() each take a PriorityQueue as a parameter. They check if the queue is either full

or empty respectively.


========================================================================================================
FIFOQueue.c
========================================================================================================
    This file deals with the FIFOQueue struct, which is used to manage the queues of the the CPU and

Disks. The FIFOQueue struct stores three int values for its capacity, front, and rear. It also

contains an Event array to store the jobs that will be used in the queue.


    *initialize() is used for the initializing of a FIFOQueue struct. It takes an int parameter

as capacity and sets that as the struct's capacity. The current size, front, and rear are set to 0 and

space is allocated for the struct and its Event array.


    insertFIFO() takes a FIFOQueue and an Event as parameters. If the queue is not full, it inserts the

Event in the rear and increments the rear value by 1.


    removeFIFO() takes a FIFOQueue as a parameter. It returns the Event stored at the front index. It

then shifts the rest of the queue and subtracts one from the rear.


    printFIFO() takes a FIFOQueue as a parameter. It increments through the queue and prints each Event's

ID.


    destroyFIFO() takes a FIFOQueue as a parameter. It frees the space allocated to the queue entered.


    isFull() and isEmpty() each take a FIFOQueue as a parameter. They check if the queue is either full

or empty respectively.


========================================================================================================
main.c
========================================================================================================
    This file deals with most of the logic for the program. It contains two functions, randGen() and

main().


    randGen() takes two int values: min and max. a random integer between the min value and max value

is returned from the function.

-------------------------------------------------------------------------------------------------------
    main() is the event simulator. It utilizes all the other C files in order to create the simulation.
-------------------------------------------------------------------------------------------------------

    First, the config file is read and all of the constants are assigned values. Then, the log file

is opened and the constants and values are written to it.

    Next, variables keeping track of runtime, job IDs, business, and statistics are created. After that,

the queues for the event queue, CPU, Disk1, and Disk2 are initialized.

    The function then goes through a while loop, which runs until the event queue is empty or the SIM_END

Event is reached. The first job in the event queue is popped and the runtime is set to that job's time

value. A switch statement determines what to do next depending on the job's ID integer.

        In the case of a 0 (SIM_START), 1 (SIM_END), or 8 (EXIT): nothing happens.

        In the case of a 2 (CPU ARRIVE): increment job ID counter by one, create a new arrival Event

    using a random arrival time. Insert the current job into the CPU's queue.

        In the case of a 3 (CPU FINISH): set the CPU to idle. Determine whether the job quits depending on

    chance. If it doesn't quit, determine which disk to send the current job. If the disk queues are equal in length,

    it is decided randomly. If one's shorter than the other, it is sent to the shorter one.

        In the case of a 4 (DISK1 ARRIVE), or 6 (DISK2 ARRIVE): Send the current job to the respective disk's

    queue.

        In the case of a 5 (DISK1 FINISH), or 7 (DISK2 FINISH): Set the disk to idle and send the job back to

    arrive at the CPU.


    After the switch statement, it checks whether the CPU is idle and has a job in the queue. If that's the case,

the job is removed from the queue, it's finishing time is determined by a random interval and it is sent back

into the event queue. The CPU is then set to busy. This process is identical for Disk1 and Disk2.


    When the simulation ends, the log file is closed and all the memory that was allocated is freed and statistics

are printed to the screen.
