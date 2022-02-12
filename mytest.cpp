/*
  Jacob Enoch
  Prof. Kartchner
  CMSC341 - Section 90
  November 10, 2020
*/

#include <iostream>
#include "pqueue.h"
#include <chrono>
#include<iomanip>
using namespace std;

int main()
{
	const int MAXTEMP = 42;
	const int MAXOX = 101;
	const int MAXRR = 40;
	const int MAXHR = 140;
	const int MAXBP = 160;
	
	//Fnction Prototypes
	int priorityFn1(const Patient & patient);
	int priorityFn2(const Patient & patient);

	PQueue queue1(priorityFn1);
	PQueue queue2(priorityFn1);

	cout << "------Test 1: Creating Patients and Inserting Into Queue1------" << endl;
	cout << "Expected Output: (((4:Eva)2:Nick)1:Sam(5:Liz))" << "  Queue1 Size = 4" << endl << endl;

	Patient patient1("Sam", 1, 37, 79, 36, 133, 75);
	Patient patient2("Liz", 5, 37, 98, 26, 70, 100);
	Patient patient3("Nick", 2, 37, 85, 34, 125, 85);
	Patient patient4("Eva", 4, 37, 95, 22, 115, 95);
	
	Patient patient5("John", 3, 39, 91, 27, 115, 110);
	Patient patient6("Mia", 3, 33, 93, 28, 118, 98);

	Patient patient7;
	Patient patient8("Ringo", 2, 37, 85, 34, 125, 85);
	Patient patient9;
	Patient patient10("Jack", 1, 37, 79, 36, 133, 75);

	try
	{
		queue1.insertPatient(patient3);
		queue1.insertPatient(patient1);
		queue1.insertPatient(patient2);
		queue1.insertPatient(patient4);

		queue1.printPatientQueue();
		cout << endl;
		queue1.dump();
		cout << endl << "Queue1 Size = " << queue1.numPatients() << endl << endl;
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
		cout << endl << endl;
	}
	
	cout << "------Test 2: Inserting default Patient objects into Queue3------" << endl;
	cout << "Expected output: (((5:)2:Ringo(5:))1:Jack) " << "  Queue3 Size = 4" << endl << endl;
	
	PQueue queue3(priorityFn1);
	
	try 
	{
		queue3.insertPatient(patient7);
		queue3.insertPatient(patient8);
		queue3.insertPatient(patient9);
		queue3.insertPatient(patient10);

		queue3.printPatientQueue();
		cout << endl;
		queue3.dump();
		cout << endl << "Queue3 Size = " << queue1.numPatients() << endl << endl;
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}


	cout << "------Test 3: Creating Patients and Inserting Into Queue2, merging with Queue1------" << endl;
	cout << "Expected Output of Queue1:(((5:Liz)3:Mia(3:John))1:Sam((4:Eva)2:Nick))  Queue1 Size: 6 Queue2 Size: 0" << endl << endl;

	try
	{
		Patient patient5("John", 3, 39, 91, 27, 115, 110);
		Patient patient6("Mia", 3, 33, 93, 28, 118, 98);

		queue2.insertPatient(patient5);
		queue2.insertPatient(patient6);

		queue1.mergeWithQueue(queue2);

		queue1.printPatientQueue();
		cout << endl;
		queue1.dump();
		cout << endl << "Queue1 Size = " << queue1.numPatients() << " Queue2 Size = " << queue2.numPatients() << endl << endl;
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}

	cout << "------Test 4: Right Hand Side of Merge must be left empty following conclusion of merge------" << endl;
	cout << "Expected Output of Queue2: None Queue2 Size: 0" << endl << endl;

	queue2.printPatientQueue();
	cout << endl;
	queue2.dump();
	cout << endl << "Queue2 Size: " << queue2.numPatients() << endl << endl;

	cout << "------Test 5: Merging with an empty queue------" << endl;
	cout << "Expected Output of Queue1: (((5:Liz)3:Mia(3:John))1:Sam((4:Eva)2:Nick)) Queue1 Size: 6 Queue2 Size: 0" << endl << endl;

	try
	{
		queue1.mergeWithQueue(queue2);
		queue1.printPatientQueue();
		cout << endl;
		queue1.dump();
		cout << endl << "Queue1 Size = " << queue1.numPatients() << " Queue2 Size: " <<  queue2.numPatients() << endl << endl;
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}


	
	cout << "------Test 6: Self-merging------" << endl;
	cout << "Expected Output of Queue1: (((5:Liz)3:Mia(3:John))1:Sam((4:Eva)2:Nick)) Queue1 Size: 6 Queue2 Size: 0" << endl << endl;
	
	try
	{
		queue1.mergeWithQueue(queue1);
		queue1.printPatientQueue();
		cout << endl;
		queue1.dump();
		cout << endl << "Queue1 Size = " << queue1.numPatients() << " Queue2 Size: " << queue2.numPatients() << endl << endl;
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}


	cout << "------Test 7: Attempt to merge two queues with different priorities------" << endl;
	cout << "Expected Output: domain_exceptipn thrown, 'Queues do not have matching priority functions, merge is not possible.'"<< endl << endl;

	try
	{
		PQueue queue4(priorityFn2);
		queue1.mergeWithQueue(queue4);
		queue1.printPatientQueue();
		cout << endl;
		queue1.dump();
		cout << endl << "Queue1 Size = " << queue1.numPatients() << " Queue2 Size: " << queue2.numPatients() << endl << endl;
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}


	cout << "------Test 8: Attempt to remove root from queue1------" << endl;
	cout << "Expected Output: (((5:Liz)3:Mia(3:John))2:Nick(4:Eva)) Returns 1:Sam info, new root is Nick " << endl << endl;
	try
	{
		cout << queue1.getNextPatient() << endl;
		queue1.printPatientQueue();
		queue1.dump();
		cout << endl << endl;

	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}

	cout << "------Test 9: Test Clear Function------" << endl;
		
	try
	{

		cout << "Expected Output: None" << endl << endl;
		cout << "Queue1 before clear(): ";
		queue1.dump();
		cout << endl;
		queue1.clear();
		cout << "Queue1 after clear(): ";
		queue1.dump();
		cout << endl << endl;
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}


	cout << "------Test 10: Attempt to remove from empty queue------" << endl;
	cout << "Expected Output: domain_error thrown - Queue is empty." << endl << endl;

	try
	{
		queue1.getNextPatient();
		cout << endl << endl;
	}
	
	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}


	cout << "------Test 11: Attempt to traverse empty queue------" << endl;
	cout << "Expected Output: Queue is empty. " << endl << endl;

	try
	{
		queue1.dump();
		cout << endl << endl;
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}

	cout << "------Test 12: Copy Constructor------" << endl; //Also tests inserting and deleting from a previously cleared queue
	cout << "Expected Output of Queue5 following Queue1 Clear: (((4:Eva)2:Nick)1:Sam(5:Liz)) Queue5 Size = 4" << endl << endl;
	
	try
	{
		queue1.insertPatient(patient3);
		queue1.insertPatient(patient1);
		queue1.insertPatient(patient2);
		queue1.insertPatient(patient4);

		cout << "Queue1: ";
		queue1.dump();
		cout << endl << "Queue 1 Size = " << queue1.numPatients() << endl;
		PQueue queue5(queue1);
		cout << "Queue1 Cleared" << endl;
		queue1.clear();
		cout << "Queue5 Output: ";
		queue5.dump();
		cout << " Queue5 Size = " << queue5.numPatients() << endl << endl;
	}
	
	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}


	cout << "------Test 13: Copy Constructor on empty queue------" << endl; //Also tests inserting and deleting from a previously cleared queue
	cout << "Expected Output of Queue6 following Queue1 Clear: Queue is empty. Queue6 Size = 0" << endl << endl;

	try
	{
		PQueue queue6(queue1);
		queue6.dump();
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}

	cout << "------Test 14: Assignment Operator------" << endl; //Also tests inserting and deleting from a previously cleared queue
	cout << "Expected Output of Queue7 assignment to and subsequent clearing of Queue1: (((4:Eva)2:Nick)1:Sam(5:Liz))  Queue7 Size = 4" << endl << endl;

	try
	{
		PQueue queue7(priorityFn1);
		
		queue1.insertPatient(patient3);
		queue1.insertPatient(patient1);
		queue1.insertPatient(patient2);
		queue1.insertPatient(patient4);

		queue7 = queue1;

		queue1.clear();
		cout << "Queue1 Cleared" << endl;

		queue7.dump();
		cout << endl;
		cout << "Queue7 Size = " << queue7.numPatients() << endl << endl;
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}


	cout << "------Test 15: Assignment Operator on empty queue as well as attempting to clear an already empty queue------" << endl;
	cout << "Expected Output of Queue8 (assignment to and clearing of Queue1): Queue is empty. Queue8 Size = 0" << endl << endl;

	try
	{
		PQueue queue8(priorityFn1);

		queue8 = queue1;

		queue1.clear();
		cout << "Queue1 Cleared" << endl;

		queue8.dump();
		cout << endl;
		cout << "Queue8 Size = " << queue8.numPatients() << endl << endl;
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}


	cout << "------Test 16: Changing priority function of Queue1 after inserting values back into Queue1------" << endl;
	cout << "Expected Output of Queue1 following change in prifn_t: (((4:Eva)3:John(3:Mia))1:Sam((5:Liz)2:Nick)) " << endl << endl;
	
	try
	{
		queue1.insertPatient(patient3);
		queue1.insertPatient(patient1);
		queue1.insertPatient(patient2);
		queue1.insertPatient(patient4);
		PQueue queue9(priorityFn1);
		queue9.insertPatient(patient5);
		queue9.insertPatient(patient6);

		queue1.mergeWithQueue(queue9);

		cout << "Queue1 after merging with queue9: ";
		queue1.dump();
		cout << endl << "Queue1 after changing priority function from priorityFn1 to priorityFn2: ";
		queue1.setPriorityFn(priorityFn2);
		queue1.dump();
		cout << endl << endl;
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}


	cout << "------Test 17: Changing priority function of Queue1 back to PriorityFn1 after inserting initially changing it to PriorityFn2------" << endl;
	cout << "Expected Output of Queue1 following change in prifn_t: (((5:Liz)3:Mia(3:John))1:Sam((4:Eva)2:Nick))" << endl << endl;

	try
	{
		cout << "Queue1 before changing priority function from priorityFn2 to priorityFn1: ";
		queue1.dump();
		cout << endl << "Queue1 after changing priority function from priorityFn2 back to priorityFn1: ";
		queue1.setPriorityFn(priorityFn1);
		queue1.dump();
		cout << endl << endl;
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}


	cout << "------Test 18: Changing priority function of Queue1 back to PriorityFn2 after clearing Queue1------" << endl;
	cout << "Expected Output of Queue1 following change in prifn_t: Queue is empty." << endl << endl;
	
	try
	{
		cout << "Queue1 before changing priority function (priorityfn1->priorityfn2): ";
		queue1.dump();
		cout << endl << "Queue1 after clearing and changing priority function from priorityFn1 back to priorityFn2: ";
		queue1.clear();
		queue1.setPriorityFn(priorityFn2);
		queue1.dump();
		cout << endl << endl;
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}
	
	cout << "------Test 19: Attempting to insert a patient with invalid values------" << endl;
	cout << "Expected output: Bad value to Patient constructor." << endl << endl;
	try
	{
		Patient badPatient("Jack", 100, 100, 100, 100, 100, 100);
		queue1.insertPatient(badPatient);
	}

	catch (domain_error ex)
	{
		cout << ex.what() << endl << endl;
		cout << endl << endl;
	}

	catch (out_of_range ex)
	{
		cout << ex.what() << endl << endl;
	}

	queue1.clear();

	cout << "------Test 20: Inserting large amounts of items into the queue and testing time complexity------" << endl << endl; // Patient(string name, int triage, int temp, int ox, int rr, int hr, int bp)

	string patientName = "Patient";

	int triage = 0;
	queue1.clear();

	auto time1 = std::chrono::high_resolution_clock::now();

	
	//Inserting 100,000 items into the queue
	for (int i = 0; i < 100000; i++)
	{
		triage = (rand() % 5) + 1;
		Patient temp(patientName, triage, MAXTEMP, MAXOX, MAXRR, MAXHR, MAXBP);
		queue1.insertPatient(temp);
	}

	auto time2 = std::chrono::high_resolution_clock::now();

	auto totalTime = (std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count()) / 1000.00;

	cout << setw(20) << left << "Time to insert 100,000 Patients: " << setw(15) << right << std::fixed << totalTime << " seconds" << endl;

	queue1.clear();

	//Inserting 200,000 items into the queue
	time1 = std::chrono::high_resolution_clock::now();
	
	for (int i = 0; i < 200000; i++)
	{
		triage = (rand() % 5) + 1;
		Patient temp(patientName, triage, MAXTEMP, MAXOX, MAXRR, MAXHR, MAXBP);
		queue1.insertPatient(temp);
	}
	
	time2 = std::chrono::high_resolution_clock::now();

	totalTime = (std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count()) / 1000.00;

	cout << setw(20) << left << "Time to insert 200,000 Patients: " << setw(15) << right << std::fixed << totalTime << " seconds" << endl;

	queue1.clear();

	//Inserting 400,000 items into the queue
	time1 = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 400000; i++)
	{
		triage = (rand() % 5) + 1;
		Patient temp(patientName, triage, MAXTEMP, MAXOX, MAXRR, MAXHR, MAXBP);
		queue1.insertPatient(temp);
	}

	time2 = std::chrono::high_resolution_clock::now();

	totalTime = (std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count()) / 1000.00;

	cout << setw(20) << left << "Time to insert 400,000 Patients: " << setw(15) << right << std::fixed << totalTime << " seconds" << endl;

	//Inserting 800,000 items into the queue
	time1 = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 800000; i++)
	{
		triage = (rand() % 5) + 1;
		Patient temp(patientName, triage, MAXTEMP, MAXOX, MAXRR, MAXHR, MAXBP);
		queue1.insertPatient(temp);
	}

	time2 = std::chrono::high_resolution_clock::now();

	totalTime = (std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count()) / 1000.00;

	cout << setw(20) << left << "Time to insert 800,000 Patients: " << setw(15) << right << std::fixed << totalTime << " seconds" << endl;

	//Inserting 1,600,000 items into the queue
	time1 = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 1600000; i++)
	{
		triage = (rand() % 5) + 1;
		Patient temp(patientName, triage, MAXTEMP, MAXOX, MAXRR, MAXHR, MAXBP);
		queue1.insertPatient(temp);
	}

	time2 = std::chrono::high_resolution_clock::now();

	totalTime = (std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count()) / 1000.00;

	cout << setw(20) << left << "Time to insert 1,600,000 Patients: " << setw(13) << right << std::fixed << totalTime << " seconds" << endl;

	queue1.clear();

	cout << endl << endl << "------Test 21: Removing large amounts of items from the queue and testing time complexity------" << endl << endl;
	
	cout << "Clearing old queue..." << endl;
	queue1.clear();

	for (int i = 0; i < 100000; i++)
	{
		triage = (rand() % 5) + 1;
		Patient temp(patientName, triage, MAXTEMP, MAXOX, MAXRR, MAXHR, MAXBP);
		queue1.insertPatient(temp);
	}

	time1 = std::chrono::high_resolution_clock::now();

	queue1.clear();
	
	time2 = std::chrono::high_resolution_clock::now();

	totalTime = (std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count()) / 1000.00;

	cout << setw(20) << left << "Time to remove 100,000 Patients: " << setw(15) << right << std::fixed << totalTime << " seconds" << endl;

	cout << "Inserting items..." << endl;

	for (int i = 0; i < 200000; i++)
	{
		triage = (rand() % 5) + 1;
		Patient temp(patientName, triage, MAXTEMP, MAXOX, MAXRR, MAXHR, MAXBP);
		queue1.insertPatient(temp);
	}

	time1 = std::chrono::high_resolution_clock::now();

	queue1.clear();

	time2 = std::chrono::high_resolution_clock::now();

	totalTime = (std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count()) / 1000.00;

	cout << setw(20) << left << "Time to remove 200,000 Patients: " << setw(15) << right << std::fixed << totalTime << " seconds" << endl;

	cout << "Inserting items..." << endl;

	for (int i = 0; i < 400000; i++)
	{
		triage = (rand() % 5) + 1;
		Patient temp(patientName, triage, MAXTEMP, MAXOX, MAXRR, MAXHR, MAXBP);
		queue1.insertPatient(temp);
	}

	time1 = std::chrono::high_resolution_clock::now();

	queue1.clear();

	time2 = std::chrono::high_resolution_clock::now();

	totalTime = (std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count()) / 1000.00;

	cout << setw(20) << left << "Time to remove 400,000 Patients: " << setw(15) << right << std::fixed << totalTime << " seconds" << endl;

	cout << "Inserting items..." << endl;

	for (int i = 0; i < 800000; i++)
	{
		triage = (rand() % 5) + 1;
		Patient temp(patientName, triage, MAXTEMP, MAXOX, MAXRR, MAXHR, MAXBP);
		queue1.insertPatient(temp);
	}

	time1 = std::chrono::high_resolution_clock::now();

	queue1.clear();

	time2 = std::chrono::high_resolution_clock::now();

	totalTime = (std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count()) / 1000.00;

	cout << setw(20) << left << "Time to remove 800,000 Patients: " << setw(15) << right << std::fixed << totalTime << " seconds" << endl;

	cout << "Inserting items..." << endl;

	for (int i = 0; i < 1600000; i++)
	{
		triage = (rand() % 5) + 1;
		Patient temp(patientName, triage, MAXTEMP, MAXOX, MAXRR, MAXHR, MAXBP);
		queue1.insertPatient(temp);
	}

	time1 = std::chrono::high_resolution_clock::now();

	queue1.clear();

	time2 = std::chrono::high_resolution_clock::now();

	totalTime = (std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count()) / 1000.00;

	cout << setw(20) << left << "Time to remove 1,600,000 Patients: " << setw(13) << right << std::fixed << totalTime << " seconds" << endl;



}

int priorityFn1(const Patient& patient) {
	int pri = 5;
	if ((patient.getOxygen() < 80 && (patient.getRR() > 35 || patient.getRR() < 8)) ||
		(patient.getHR() > 130 && patient.getBP() < 80))
		pri = 1;
	else if (((patient.getOxygen() >= 80 && patient.getOxygen() <= 89) &&
		(patient.getRR() >= 31 && patient.getRR() <= 35)) ||
		(patient.getTemperature() >= 40 || patient.getTemperature() <= 32))
		pri = 2;
	else if ((patient.getOxygen() >= 90 && patient.getOxygen() <= 94) &&
		(patient.getRR() >= 26 && patient.getRR() <= 30))
		pri = 3;
	else if ((patient.getOxygen() >= 95 && patient.getOxygen() <= 97) &&
		(patient.getRR() >= 21 && patient.getRR() <= 25))
		pri = 4;
	else
		pri = 5;
	return pri;
}

int priorityFn2(const Patient& patient) {
	//priority only based on triage
	//traige is set by a health care professional
	return patient.getTriage();
}