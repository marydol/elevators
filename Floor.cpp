#include "Floor.h"

void Floor::addPerson(Person p, int request) {
	if (numPeople < MAX_PEOPLE_PER_FLOOR){
		people[numPeople] = p;
		numPeople++;
		if (request > 0){
			hasUpRequest = true;
		}
		if (request < 0){
			hasDownRequest = true;
		}
	}
}

void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove){
	for (int i = 0; i < numPeopleToRemove; i++){
		people[indicesToRemove[i]] = NULL;
		numPeople--;
	}
	for (int i = 0; i < MAX_PEOPLE_PER_FLOOR - 1; i++){
		while (people[i] == NULL){
			people[i] = people[i + 1];
		}
	}
}

int Floor::tick(int currentTime) {
	bool exploded = false;
	int count = 0;
	int indicesToRemove[MAX_PEOPLE_PER_FLOOR];
	for (int i = 0; i < numPeople; i++){
		exploded = people[i].tick(currentTime);
		if (exploded == true){
			indicesToRemove[count] = i;
			count++;
		}
	}
	int newIndicesToRemove[count];
	for (int i = 0; i < count; i++){
		newIndicesToRemove[i] = indicesToRemove[i];
	}
	removePeople(newIndicesToRemove, count);
	return count;
}

///////////////////////////////////////////////////////
///// DO NOT MODIFY ANY 😤 CODE BENEATH THIS LINE /////
///////////////////////////////////////////////////////

Floor::Floor() {

    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}
void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		// TODO: Make sure prints work correctly with down/up requests
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}

}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
