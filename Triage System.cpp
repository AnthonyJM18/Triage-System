/* Program		: Triage System.cpp
*  Author		: Anthony Merante
*  Date			: November 3, 2019
*  Description	: A hospital triage system that will keep track of all patients, there illnesses, and enqueue them based off there priority score
*/

// Library includes
#include <string>
#include <fstream>
// Header | Class file includes
#include "PriorityMap.hpp"
#include "LinkedList.hpp"
#include "PriorityQueue.hpp"
// Namespace because I am slightly lazy
using namespace std;

// Method declerations (see below main for specific information on each method)
void printOptions( ostream& os);
void saveFile(PriorityMap &p);

int main() {
	// 1. First we will read in from our CSV file and store all the illness and priority information of each in a map.
	ifstream csv("project 1 priorities input file.csv", ios::in);
	// If neither file names are found then tell the user neither file can be found and stop the program.
	if (!csv) {
		cout << "Error: failed to open <" << "'project 1 priorities input file.csv'" << ">\n"
			"The file may not exist.\n";
		cout << "\nNo injuries/illnesses will be pre-loaded.";
	}
	// Read the input file and load in the information to the map
	PriorityMap pMap;
	string diagnosis;
	int type, contagious, timeCrit;
	char eat;
	while (getline(csv, diagnosis, ',')) {
		for (int x = 0; x < diagnosis.size(); x++) {
			diagnosis[x] = tolower(diagnosis[x]);
		}
		// This will read in the type, time criticality, and contagious values while removing all newlines, commas, and whitespace
		csv >> type >> ws >> eat >> ws >> timeCrit >> ws >> eat >> ws>> contagious >> ws;
		// When all the data has been read, it will add it to the map
		pMap.addNode(diagnosis, type, contagious, timeCrit);
	}
	// Close the csv file as we do not need it opened anymore
	csv.close();

	// Create an empty patient list, and priority queue
	LinkedList<Patient>* patientList = new LinkedList<Patient>();
	PriorityQueue* pQueue = new PriorityQueue();
	// Declare variables to hold :
	// name = Patients name | clear = used to clear the buffer on bad input
	string name, clear;
	int severity;
	int position = 0;
	// Used for gathering input throught the program
	char yes_no, input, option;
	// Print program header
	cout << "Welcome to the Fanshawe EMERG Triage System\n" <<
		    "___________________________________________\n\n"<< endl;
	// Output options to the user
	printOptions(cout);
	// Take input from the user until they choose to exit the program
	do {
		cout << "\nPlease make a selection ( Enter L for a list of options )" << endl;
		cin >> option;
		option = tolower(option); // Lowercasing the users input so that both uppercase and lowercase letters may be inputted and work
		switch (option){
		case 'a':  // If the user wants to add a patient
			cout << "Please enter the patients name: ";
			cin >> ws;
			getline(cin, name);
			// Check to see if the patient is already in the queue
			if (pQueue->is_in_queue(name)) {
				cout << "That patient is already in the queue..." << endl;
				continue;
			}
			// if Patient not in the queue, then add them to the patient list
			patientList->addTail(new Patient(name));
			// Read in all illnesses and injuries the patient has
			while (true) {
				cout << "What is the Injury or illness: ";
				cin >> ws;
				getline(cin, diagnosis);
				for (int x = 0; x < diagnosis.size(); x++) {
					diagnosis[x] = tolower(diagnosis[x]);
				}
				// If the injury does not exist in the map it will ask for the type, time criticallity, and contagiousness
				/* So the way it is coded, the map will create a node when using the [] index of operator if the illness is not found, and assigns it a -1... so 
				 that is how it will validate that the ilness is not in the map*/
				if (pMap[diagnosis]->getType() == -1) {
					do {
						cout << "What is the type (Ailment = 1 | Injury = 2) : ";
						cin >> input;
						if (input > '2' || input <= '0') {
							cout << "Please enter a 1 or 2" << endl;
							getline(cin, clear);
						}
					} while (input != '1' && input != '2');
					type = input - '0';
					do {
						cout << "What is the time criticality 0-9 (lowest = 9 | highest = 0) : ";
						cin >> input;
						if (input > '9' || input < '0') {
							cout << "Please enter a number between 1-10!" << endl;
							getline(cin, clear);
						}
					} while (input > '9' || input < '0');
					timeCrit = (input - '0') + 1; // asking for a number between 0-9 instead of 1-10 because it makes input validation easier
					do {
						cout << "How contagious is it (Not Contgious = 0 | Contagious = 1 | Highly Contagious = 4) : ";
						cin >> input;
						if (input != '0' && input != '1' && input != '4') {
							cout << "Please enter a 0, 1, or 4" << endl;
							getline(cin, clear);
						}
					} while (input != '0' && input != '1' && input != '4');
					contagious = input - '0';
					// assign the information to the newly created map node 
					*(pMap[diagnosis]) = MapNode(diagnosis, type, contagious, timeCrit);
				}
				// If the illness/injury exists in the map node then load the information
				else {
					type = pMap[diagnosis]->getType();
					timeCrit = pMap[diagnosis]->getTimeCriticality();
					contagious = pMap[diagnosis]->getContagious();
				}
				// Get severity of the injury which will vary from person to person so that is why it is not stored in the map
				do {
					cout << "What is the severity 1-5 (lowest = 1 | highest = 5) : ";
					cin >> ws >> input;
					if (input > '5' || input < '1' || !isdigit(input)) {
						cout << "Please enter a number between 1-5!" << endl;
						getline(cin, clear);
					}
				} while (input > '5' || input < '1');
				severity = input - '0';
				// Add the illness/injury to the patients injury list
				patientList->getNode(patientList->getSize() - 1)->getData()->addToList(diagnosis, type, contagious, timeCrit, severity);
				// Check to see if the user has more injuries, and if so the loop continues, otherwise the loop breaks
				cout << "Would you like to add another injury/ailment ( yes = y | no = n ) : " << endl;
				do {
					cin >> yes_no;
					yes_no = tolower(yes_no);
					if (yes_no != 'y' && yes_no != 'n') {
						cout << "please enter a y or n" << endl;
						getline(cin, clear);
					}
				} while (yes_no != 'y' && yes_no != 'n');
				if (yes_no == 'y')
					continue;
				else break;
			}
			// Priority enqueue the patiens and report to the user there priority and position in the queue
			position = pQueue->priorityEnqueue(new Patient(*patientList->getNode(patientList->getSize() - 1)->getData() ));
			cout << "Patient " << patientList->getNode(patientList->getSize() - 1)->getData()->getName() << " Added to Queue with priority " << patientList->getNode(patientList->getSize() - 1)->getData()->getPriority() <<
					" at Position " << position + 1 << endl << endl;
			break;
		case 'p': // Process the next patient by dequeueing them from the queue
			pQueue->dequeue();
			break;
		case 'r': // Print the contents of the queue
			pQueue->printQueue();
			break;
		case 'h': // Print the history of processed patients with the oldest displayed first
			pQueue->printHistory();
			break;
		case 's': // Saves the priority map to the CSV
			cout << "New injuries and there priority scores have been saved." << endl;
			saveFile(pMap);
			break;
		case 'l': // This will display all options to the user
			cout << endl;
			printOptions(cout);
		case 'x': // Exits the program
			break;
		default: // Default case implies an incorrect command has been entered
			cout << "Invalid option" << endl;
			// clear the line so that if a string of characters was entered e.g "zzz" this will only print once
			getline(cin, clear);
		}
	} while (option != 'x');


	
	// Clean up the program by deleting the list and queue
	delete patientList;
	delete pQueue;
	// Program finishes succesfully
	return EXIT_SUCCESS;
}


/* Method name	: printOptions
*  Accepts		: ostream reference
*  Returns		: void
*  Description	: outputs to the ostream a list of all the options the user may take
*/
void printOptions(ostream& os){
	os << "-----------------------------------------------\n"
		<<"-A\tAdd a new patient to the queue        |\n"
		<< "-P\tProcess the next patient in the queue |\n"
		<< "-R\tReview the current queue              |\n"
		<< "-H\tPrint queue history (oldest first)    |\n"
		<< "-S\tSave priority map to csv              |\n"
		<< "-X\tExit the system                       |\n" 
		<< "-----------------------------------------------" << endl;
}


/* Method name	: saveFile
*  Accepts		: PriorityMap Reference
*  Returns		: void
*  Description	: Opens a csv file, truncates any existing information, and then writes all information stored in the map
*/
void saveFile(PriorityMap & p){
	ofstream csv("project 1 priorities input file.csv", ios::in | ios::trunc);
	if (!csv) {
		cerr << "Error: failed to open <" << "Priority_Input.csv or 'project 1 priorities input file.csv'" << ">\n"
			"The file may not exist.\n";
	}

	csv << p.to_String();
	csv.close();
}
