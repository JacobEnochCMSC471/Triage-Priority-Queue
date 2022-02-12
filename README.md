# Triage-Priority-Queue
A priority queue data structure implemented in C++ with a scenario provided: a priority queue (heap style) for triage patients in a hospital. 
* A queue object uses a priority function to determine the priority for any given patient. This priority function takes a patients vital signs (O2 concentration, blood pressure, etc.) to assign a patient a priority number (1 = lowest, 5 = highest). 
* The structure of the queue is a node-based priority heap. Each node represents a patient in the queue.
* Inserting and removing a patient from the queue may require a re-shuffling or re-heaping to occur. This happens by recursively swapping nodes in the queue if one node is larger than another. This causes the largest values to "bubble up" near the top of the heap. mergeHelper() and swap() does most of the work for this functionality. 
** Insertion creates a new node using a Patient objects information and then treats this singluar node as an entire queue. The mergeWithQueue() function will then combine these queues together into one larger queue. 
* There are overloaded operators for printing a patient's data (<<) and ensuring that copies of an existing queue are deep rather than shallow (=). 
* getNextPatient() removes and returns the data of the highest priority (root) patient. Merging  of the left and right subtrees after the root is removed is then performed using the mergeWithQueue() function. 
* Reheaping will also occur if the priority function of the queue is changed - the nodes may have different calculated triage values after being put into the new triage function.
* There are implementations of deep copy constructors and deconstructors to ensure that no memory leaks occur.
* In-order and pre-order printing is available to help visualize the tree.
* Valgrind indicates that there are no memory leaks within this code. 
