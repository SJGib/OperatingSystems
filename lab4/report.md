##Report

**4 process queues:**   
* realtime queue = First come, first serve
* priority 1 - 3 queues. Run for one second then move the process to lower priority queue. If it’s in the 3rd priority queue then re-add it to the third priority queue.

**struct resources:** 2 printers, 1 scanner, 1 modem, 2 CD drives, 1024MB memory. (initialized to res_available)

**int memory[1024]:** 
Memory will only be allocated if there is enough space to contain the data continguously. Last 64 bytes are reserved for real time processes at all times (priority queues may not allocate to it). Free memory when the allocated process dies.

**dispatchlist format**
Arrival, Priority, Runtime, Memory Needed, Printers,  Scanner, Modem, CD Drives

###functions

**void load()**
take the file and actually load it into memory, load it into an array of structs.

**void priority_schedule()**
put the process data into its appropriate queue based on each process's priority. 

**void ready_execute()**
run realtime queue process until it finishes.

**void execute(int queue)**
run queue process for 1 second; increment (lower) the priority of the process if the process doesn't finish in time. call priority_schedule() to reassign the priority.

**void allocate(int memsize, proc process)**
allocate memory for process

**void deallocate(proc process)**
deallocate memory for process

**void allocate_res(int memsize)**
allocate memory for resource



