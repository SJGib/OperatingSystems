###Report

**4 process queues:**   
* realtime queue = First come, first serve
* priority 1 - 3 queues. Run for one second then move the process to lower priority queue. If it’s in the 3rd priority queue then re-add it to the third priority queue.

**struct resources:** 2 printers, 1 scanner, 1 modem, 2 CD drives, 1024MB memory. (initialized to res_available)

**int memory[1024]:** 
Memory will only be allocated if there is enough space to contain the data continguously. Last 64 bytes are reserved for real time processes at all times (priority queues may not allocate to it). Free memory when the allocated process dies.

**dispatchlist format**
Arrival, Priority, Runtime, Memory Needed, Printers,  Scanner, Modem, CD Drives

