// CMSC 341 - Fall 2020 - Project 3
// PQueue: an ER triage queue using a skew heap and function pointers
/*
  Jacob Enoch
  Prof. Kartchner
  CMSC341 - Section 90
  November 10, 2020
*/


#include "pqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

PQueue::PQueue(prifn_t priFn) //Constructor
{
    this->priority = priFn;
    this->_heap = nullptr;
    this->_size = 0;
}

PQueue::~PQueue() //Destructor - uses a helper function to traverse through the tree and deallocate memory
{
    clear();
}


PQueue::PQueue(const PQueue& rhs) //Copy constructor - Sets *this non-pointer members equal to rhs, calls preOrderCopy to recursively deep copy node pointers (working)
{
    this->priority = rhs.priority;
    this->_heap = nullptr;
    this->_size = 0;
    
    if (rhs._heap == nullptr) //If rhs is empty, nothing can be copied so the constructor returns
    {
        return;
    }
    
    this->priority = rhs.priority;
    this->_size = rhs._size;
    preOrderCopy(rhs._heap, this->_heap);
}


PQueue& PQueue::operator=(const PQueue& rhs) //= override -> checks if objects are equivalent - if not, set non-pointers equal to rhs and call preOrderCopy (working)
{
    if (this == &rhs)
    {
        return *this;
    }

    destructorHelper(this->_heap);
    this->priority = rhs.priority;
    this->_size = rhs._size;
    preOrderCopy(rhs._heap, this->_heap);

    return *this;
}

void PQueue::insertPatient(const Patient& input) //Inserts a patient by merging 2 queues together - uses merge to insert a queue with a single node in it (working)
{
        Node* newNode = new Node(input); //New node, must be deallocated eventually 
        PQueue temp(this->priority);
        temp._heap = newNode;

        this->mergeWithQueue(temp);

        this->_size++;
}

Patient PQueue::getNextPatient() //Returns the next patient in the queue and removes it -> merges 2 subtrees together after removal (working)
{

    if (this->_heap == nullptr)
    {
        throw domain_error("Queue is empty - removal is impossible");
    }

    Node* temp = this->_heap;

    Patient temp1 = temp->_patient;

    PQueue rightSubtree(this->priority); //Holds the right subtree of the old root
    rightSubtree._heap = this->_heap->_right;

    this->_heap = _heap->_left; //Sets this->heap to the leftSubTree heap

    this->mergeWithQueue(rightSubtree); //Merges left and right subtrees

    this->_size--;

    delete temp;


    return temp1;

}

void PQueue::mergeWithQueue(PQueue& rhs) //Merges two queues together -> used in insertion/deletion (working)
{
        if (this->priority != rhs.priority) //If the priority functions of the queues are not the same, merge is not possibe -> throw domain_error
        {
            throw domain_error("Queues do not have matching priority functions, merge is not possible.");
        }

        if (this->_heap == rhs._heap) //Prevents self-merging by comparing each node's memory address
        {
            return;
        }

        this->_heap = mergeHelper(this->_heap, rhs._heap, this->priority); //Sets heap of lhs queue equal to mergehelper return node (merged trees)

        this->_size += rhs._size; //Increments size by rhs._size

        rhs._heap = nullptr; //Empties rhs queue

        rhs._size = 0;
    }

void PQueue::clear() //Empties the queue (working)
{
    while (this->_heap != nullptr)
    {
        this->getNextPatient();
    }
    return;
}

int PQueue::numPatients() const //Determines the number of patients in the tree 
{
    return this->_size;
}

void PQueue::printPatientQueue() const //Prints entire queue in preorder
{
    if (this->_heap == nullptr) 
    {
        cout << "Queue is empty.";
        return;
    }
    
    preorderPrint(this->_heap);
}

prifn_t PQueue::getPriorityFn() const //Returns the priority function pointer of the queue 
{
    return priority;
}

void PQueue::setPriorityFn(prifn_t priFn) //Sets the priority of a queue - must rebuild heap! - heapify & set equal
{
    PQueue temp(priFn);
    reheapQueue(this->_heap, temp);
    *this = temp;
    temp.clear();
}

void PQueue::dump() const //Prints entire tree (inorder - special formatting) 
{
    if (this->_heap == nullptr)
    {
        cout << "Queue is empty.";
        return;
    }
    
    inorderPrint(this->_heap, this->priority);
}

ostream& operator<<(ostream& sout, const Patient& patient) //Used to output a Patient's information
{
    sout << "Patient: " << patient.getPatient() << ", triage: " << patient.getTriage()
        << ", temperature: " << patient.getTemperature() << ", oxygen: " << patient.getOxygen() << ", RR: "
        << patient.getRR() << ", HR: " << patient.getHR() << ", BP: " << patient.getBP();
    return sout;
}

ostream& operator<<(ostream& sout, const Node& node) //Used to output a node's Patient info
{
    sout << node.getPatient();
    return sout;
}

void PQueue::swap(Node*& node1, Node*& node2) //Swaps the pointers of two nodes -> used during merging to swap left and right children of a given node 
{
    Node* temp = node1;
    
    node1 = node2;
    node2 = temp; 
    
    return;
}

Node* PQueue::mergeHelper(Node* node1, Node* node2, prifn_t functionPointer) //Function where merging occurs -> exceptions caught in main merge function (wprking)
{
    if (node1 == nullptr) //Returns node2 since node1 == nullptr
    {
        return node2;
    }

    if (node2 == nullptr) //Returns node2 since node1 == nullptr
    {
        return node1;
    }

    if ((*functionPointer)(node1->_patient) >= (*functionPointer)(node2->_patient)) //If the calculated priority of node1 is >= node2, swap node1 and node2
    {
        swap(node1, node2);
    }
    
    swap(node1->_left, node1->_right); //Swap the children of node1
    node1->_left = mergeHelper(node1->_left, node2, functionPointer); //Call mergeHelper on left child

    return node1;
}

void PQueue::preorderPrint(Node* nodeToPrint) const //Prints out the queue in preorder fashion
{
    if (nodeToPrint != nullptr)
    {
        cout << "[" << nodeToPrint->getPatient().getTriage() << "] " << *nodeToPrint << endl;
        preorderPrint(nodeToPrint->_left);
        preorderPrint(nodeToPrint->_right);
    }

    return;
}

void PQueue::inorderPrint(Node* nodeToPrint, prifn_t functionPointer) const //Prints the queue in inorder fashion - special formatting for the dump() function
{
    if (nodeToPrint != nullptr)
    {
        cout << "(";
        inorderPrint(nodeToPrint->_left, this->priority);
        cout << (*functionPointer)(nodeToPrint->getPatient()) << ":" << nodeToPrint->getPatient().getPatient();
        inorderPrint(nodeToPrint->_right, this->priority);
        cout << ")";
    }
}

void PQueue::destructorHelper(Node*& nodeToDelete) //Deletes nodes in postorder (root deleted last) - used in destructor
{
    if (nodeToDelete != nullptr)
    {
        destructorHelper(nodeToDelete->_left);
        destructorHelper(nodeToDelete->_right);
        delete(nodeToDelete);
    }
    
    return;
}

void PQueue::preOrderCopy(Node* rhsNode, Node*& lhsNode) //Traverses both trees recursively, creating a new node for the lhs (new lhsNode->getPatient() = rhs->getPatient())
{
    if (rhsNode != nullptr)
    {
        lhsNode = new Node(rhsNode->getPatient());
        preOrderCopy(rhsNode->_left, lhsNode->_left);
        preOrderCopy(rhsNode->_right, lhsNode->_right);
    }

    return;
}

void PQueue::reheapQueue(Node* root, PQueue& newQueue) //Sorts the existing queue based off of a new priority function -> used in the setPriority function
{
    if (root == nullptr)
    {
        return;
    }

    newQueue.insertPatient(root->getPatient());
    reheapQueue(root->_left, newQueue);
    reheapQueue(root->_right, newQueue);

    return;
}





