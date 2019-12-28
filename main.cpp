#include <iostream>
#include <windows.h>

using namespace std;

class Exits {
	int exitTime;
	int duration;
	int waitingDuration;

public:
	Exits(int e = 0, int d = 0) {
		exitTime = e;
		duration = d;
		waitingDuration = 0;
	}
	Exits(const Exits & oldExits) {
		exitTime = oldExits.exitTime;
		duration = oldExits.duration;
		waitingDuration = oldExits.waitingDuration;
	}

	int getExitTime() {
		return exitTime;
	}
	void setExitTime(int e) {

		exitTime = e;
	}
	int getDuration() {
		return duration;
	}
	void setDuration(int d) {
		duration = d;
	}

	int getWaitingDuration() {
		return waitingDuration;
	}
	void setWaitingDuration(int w) {
		waitingDuration = w;
	}
	void increamentWaitingDurationOnExit() {
		waitingDuration++;
	}

	~Exits() {}
};

class Client {
	int id;
	string name;
	int enteringTime;
	int transactionTime;
	int transactionTimeCounter;
	int exitsCount;
	Exits ** clientExitsList;
	int waitingTime;
	int currentExit;
	bool finishedExits;
	bool isExiting;
	int queueNumber;

public:
	Client() {}
	Client(int _id, string _name, int _enteringTime, int _transactionTime, int _exitsCount) {
		id = _id;
		name = _name;
		enteringTime = _enteringTime;
		transactionTime = _transactionTime;
		exitsCount = _exitsCount;
		finishedExits = 0;
		transactionTimeCounter = 0;
		currentExit = false;
		waitingTime = 0;
		if (exitsCount > 0) {
			clientExitsList = new Exits*[exitsCount];
		}
	}
	Client(const Client & oldClient) {
		id = oldClient.id;
		name = oldClient.name;
		enteringTime = oldClient.enteringTime;
		transactionTime = oldClient.transactionTime;
		exitsCount = oldClient.exitsCount;
		waitingTime = oldClient.waitingTime;
		transactionTimeCounter = oldClient.transactionTimeCounter;
		finishedExits = oldClient.finishedExits;
		isExiting = oldClient.isExiting;
		currentExit = oldClient.currentExit;
		clientExitsList = new Exits*[exitsCount];
		for (int i = 0; i < exitsCount; i++) {
			clientExitsList[i]->setExitTime(oldClient.clientExitsList[i]->getExitTime());
			clientExitsList[i]->setDuration(oldClient.clientExitsList[i]->getDuration());
			clientExitsList[i]->setWaitingDuration(oldClient.clientExitsList[i]->getWaitingDuration());
		}
	}

	int getId() {
		return id;
	}
	void setId(int _id) {
		id = _id;
	}

	string getName() {
		return name;
	}
	void setName(string _name) {
		name = _name;
	}

	int getEnteringTime() {
		return enteringTime;
	}
	void setEnteringTime(int _enteringTime) {
		enteringTime = _enteringTime;
	}

	int getTransactionTime() {
		return transactionTime;
	}
	void setTransactionTime(int _transactionTime) {
		transactionTime = _transactionTime;
	}

	int getQueueNumber() {
		return queueNumber;
	}

	void setQueueNumber(int _queueNumber) {
		queueNumber = _queueNumber;
	}


	int getWaitingTime() {
		return waitingTime;
	}
	void setWaitingTime(int _waitingTime) {
		waitingTime = _waitingTime;
	}

	int getExitsCount() {
		return exitsCount;
	}
	void setExitsCount(int _exitsCount) {
		exitsCount = _exitsCount;
	}

	int getTransactionTimeCounter() {
		return transactionTimeCounter;
	}
	void setTransactionTimeCounter(int _transactionTimeCounter) {
		transactionTimeCounter = _transactionTimeCounter;
	}

	void increamentTransactionTimeCounter() {
		transactionTimeCounter++;
	}

	int getCurrentExit() {
		return currentExit;
	}
	void setCurrentExit(int _currentExit) {
		currentExit = _currentExit;
	}
	void increamentToNextExit() {
		if (currentExit < exitsCount - 1)
			currentExit++;
		else
			finishedExits = true;
	}


	bool getFinishedExits() {
		return finishedExits;
	}
	void setFinishedExits(bool _finishedExits) {
		finishedExits = _finishedExits;
	}

	bool getIsExiting() {
		return isExiting;
	}
	void setIsExiting(bool _isExiting) {
		isExiting = _isExiting;
	}

	Exits ** getClientExitsList() {
		return clientExitsList;
	}
	void setClientExitsList(Exits ** _clientExitsList) {
		clientExitsList = _clientExitsList;
	}

	void increamentCurrentExit() {
		clientExitsList[currentExit]->increamentWaitingDurationOnExit();
		waitingTime++;
	}

	void increamentWaitingTime() {
		waitingTime++;
	}

	~Client() {
		delete clientExitsList;
	}
};

class Node {
	Client * client;
	Node * next;
	Node * previous;

public:
	Node() {}
	Node(Client * _client) {
		client = _client;
		next = previous = NULL;
	}
	Node(const Node & oldNode) {
		client = oldNode.client;
		next = oldNode.next;
		previous = oldNode.previous;
	}

	Client * getClient() {
		return client;
	}
	void setClient(Client * _client) {
		client = _client;
	}

	Node * getNext() {
		return next;
	}
	void setNext(Node * _next) {
		next = _next;
	}

	Node * getPrevious() {
		return previous;
	}
	void setPrevious(Node * _previous) {
		previous = _previous;
	}

	void increamentWaitingExits() {
		client->increamentCurrentExit();
	}

	void increamentWaiting() {
		client->increamentWaitingTime();
	}

	void increamentTransactionTimeCounter() {
		client->increamentTransactionTimeCounter();
	}

	int getTransactionTimeCounter() {
		return client->getTransactionTimeCounter();
	}

	~Node() {
		delete client;
		delete next;
		delete previous;
	}
};

class LinkedList {
	Node * head;
	Node * tail;
	int length;

public:
	LinkedList() {
		head = tail = NULL;
		length = 0;
	}
	LinkedList(const LinkedList & oldLinkedList) {
		head = oldLinkedList.head;
		tail = oldLinkedList.tail;
		length = oldLinkedList.length;
	}

	Node * getHead() {
		return head;
	}

	Node * getTail() {
		return tail;
	}

	int getLength() {
		return length;
	}

	void addNode(Node * node) {
		if (head == NULL) {
			head = tail = node;
		}
		else {
			node->setPrevious(tail);
			tail->setNext(node);
			tail = node;
			node->setNext(NULL);
		}
		length++;
	}

	void removeNode(Node * node) {
		if (node == head) {
			if (node == tail) {
				head = tail = NULL;
			}
			else {
				head = node->getNext();
				head->setPrevious(NULL);
			}
		}
		else if (node == tail) {
			tail = node->getPrevious();
			tail->setNext(NULL);
		}
		else {
			node->getNext()->setPrevious(node->getPrevious());
			node->getPrevious()->setNext(node->getNext());
		}
		length--;
	}

	Node * pop() {
		Node * temp;
		if (head == NULL) {
			return NULL;
		}
		else {
			temp = head;
			removeNode(head);
			return temp;
		}
	}

	void insertNode(Node * newNode, Node * nodeAfter) {
		if (nodeAfter == tail) {
			addNode(newNode);
		}
		else {
			newNode->setNext(nodeAfter->getNext());
			newNode->setPrevious(nodeAfter);
			nodeAfter->getNext()->setPrevious(newNode);
			nodeAfter->setNext(newNode);
			length++;
		}
	}

	void increamentWaitingTime() {
		if (head != NULL) {
			Node * current = head->getNext();
			while (current != NULL) {
				current->increamentWaiting();
				current = current->getNext();
			}
		}
	}

	void increamentExitArea() {
		if (head != NULL) {
			Node * current = head;
			while (current != NULL) {
				current->increamentWaitingExits();
				current = current->getNext();
			}
		}
	}

	void increamentTransactionTimeCounter() {
		head->increamentTransactionTimeCounter();
	}

	Node * finishedWaiting() {
		Node * found = head;
		bool isFound = 1;
		while (found != NULL && isFound) {
			int time1 = found->getClient()->getClientExitsList()[found->getClient()->getCurrentExit()]->getDuration();
			int time2 = found->getClient()->getClientExitsList()[found->getClient()->getCurrentExit()]->getWaitingDuration();
			if (time1 == time2) {
				isFound = 0;
				found->getClient()->setFinishedExits(true);
				removeNode(found);
			}
			else {
				found = found->getNext();
			}
		}
		return found;
	}

	void bubbleSort() {
		Node * current = head;
		int i = 0;
		if (current != NULL) {
			while (i < length - 1) {
				current = head;
				for (int j = 0; j < length - i - 1; j++) {
					if (current->getClient()->getEnteringTime() > current->getNext()->getClient()->getEnteringTime()) {
						if (current == head) {
							if (current == tail) {
							}
							else if (current->getNext() == tail) {
								Node * temp = head;
								head = tail;
								tail = temp;
								delete temp;
							}
							else {
								removeNode(current);
								insertNode(current, head);
							}
						}
						else {
							removeNode(current);
							insertNode(current, current->getNext());
						}
					}
					else {
						current = current->getNext();
					}
				}
				i++;
			}
		}
	}

	~LinkedList() {
		Node * first = head;
		while (first != NULL) {
			removeNode(first);
			first->~Node();
			first = head;
		}
		delete head;
		delete tail;
	}
};

class Queue {
	LinkedList * myQueue;
	int length;

public:
	Queue() {
		length = 0;
		myQueue = new LinkedList();
	}

	Queue(const Queue & oldQueue) {
		length = oldQueue.length;
		myQueue = oldQueue.myQueue;
	}

	Node * getFirst() {
		return myQueue->getHead();
	}

	Node * getLast() {
		return myQueue->getTail();
	}

	int getLength() {
		return length;
	}

	void enqueue(Node * node) {
		myQueue->addNode(node);
		length++;
	}

	Node * dequeue() {
		length--;
		return myQueue->pop();
	}

	void removeNode(Node * node) {
		length--;
		myQueue->removeNode(node);
	}

	void increamentWaitingTime() {
		if (length > 1)
			myQueue->increamentWaitingTime();
	}

	void increamentServingClient() {
		if (length > 0)
			myQueue->increamentTransactionTimeCounter();
	}

	~Queue() {
		delete myQueue;
	}
};

class Teller {
	int number;
	Queue * myQueue;
	int totalWorkingTime;
	int totalNumberOfCustomers;
	int totalWaitingTime;

public:
	Teller() {}
	Teller(int _number) {
		number = _number;
		totalWorkingTime = 0;
		totalNumberOfCustomers = 0;
		totalWaitingTime = 0;
		myQueue = new Queue();
	}
	Teller(const Teller & oldTeller) {
		number = oldTeller.number;
		totalNumberOfCustomers = oldTeller.totalNumberOfCustomers;
		totalWorkingTime = oldTeller.totalWorkingTime;
		totalWaitingTime = oldTeller.totalWaitingTime;
		myQueue = new Queue();
		myQueue = oldTeller.myQueue;
	}

	int getNumber() {
		return number;
	}

	void setNumber(int _number) {
		number = _number;
	}

	int getTotalWorkingTime() {
		return totalWorkingTime;
	}

	void setTotalWorkingTime(int _totalWorkingTime) {
		totalWorkingTime = _totalWorkingTime;
	}

	void increamentTotalWorkingTime() {
		if (myQueue->getLength() != 0)
			totalWorkingTime++;
	}

	void increamentTotalWaitingTime() {
		if (myQueue->getLength() != 0)
			totalWaitingTime += myQueue->getLength() - 1;
	}

	int getTotalWaitingTime() {
		return totalWaitingTime;
	}

	int getTotalNumberOfCustomers() {
		return totalNumberOfCustomers;
	}

	void setTotalNumberOfCustomers(int _totalNumberOfCustomers) {
		totalNumberOfCustomers = _totalNumberOfCustomers;
	}

	void increamentTotlatNumberOfCustomer() {
		totalNumberOfCustomers++;
	}

	void setQueue(Queue * _queue) {
		myQueue = _queue;
	}

	Queue * getQueue() {
		return myQueue;
	}

	void increamentTime() {
		myQueue->increamentWaitingTime();
		myQueue->increamentServingClient();
	}

	~Teller() {
		delete myQueue;
	}
};

class Bank {
	int totalBankTime;
	int numberOfTellers;
	int totalNumberOfCustomers;
	Teller ** myTellers;
	LinkedList * exitArea;

public:
	Bank() {}
	Bank(int _numberOfTellers) {
		totalBankTime = 0;
		totalNumberOfCustomers = 0;
		numberOfTellers = _numberOfTellers;
		exitArea = new LinkedList();
		myTellers = new Teller*[numberOfTellers];
	}
	Bank(const Bank & oldBank) {
		totalBankTime = oldBank.totalBankTime;
		numberOfTellers = oldBank.numberOfTellers;
		totalNumberOfCustomers = oldBank.totalNumberOfCustomers;
		exitArea = oldBank.exitArea;
		myTellers = new Teller*[numberOfTellers];
		for (int i = 0; i < numberOfTellers; i++) {
			myTellers[i]->setNumber(oldBank.myTellers[i]->getNumber());
			myTellers[i]->setQueue(oldBank.myTellers[i]->getQueue());
			myTellers[i]->setTotalNumberOfCustomers(oldBank.myTellers[i]->getTotalNumberOfCustomers());
			myTellers[i]->setTotalWorkingTime(oldBank.myTellers[i]->getTotalWorkingTime());
		}
	}

	int getTotalBankTime() {
		return totalBankTime;
	}

	void setTotalBankTime(int _totalBankTime) {
		totalBankTime = _totalBankTime;
	}

	void increamentTime() {
		totalBankTime++;
	}

	int getNumberOfTellers() {
		return numberOfTellers;
	}

	void setNumberOfTellers(int _numberOfTellers) {
		numberOfTellers = _numberOfTellers;
	}

	int getTotalNumberOfCustomers() {
		return totalNumberOfCustomers;
	}

	void setTotalNumberOfCustomers(int _totalNumberOfCustomers) {
		totalNumberOfCustomers = _totalNumberOfCustomers;
	}

	void increamentTotalNumberOfCustomers() {
		totalNumberOfCustomers++;
	}

	Teller ** getTellers() {
		return myTellers;
	}

	void setTellers(Teller ** _myTellers) {
		myTellers = _myTellers;
	}

	LinkedList * getExitArea() {
		return exitArea;
	}

	int getExitAreaLength() {
		return exitArea->getLength();
	}

};

Client * getClients();
bool checkForExits(int, int[], int);
void displayAllClients(LinkedList *);
int findShortestQueue(Bank *);
int findLongestQueue(Bank *);
int findIndex(Queue *, Node *);
void sortExitArray(Client *);
void popFinished(Bank *, LinkedList *);
void enqueueClient(LinkedList *, Bank *, int);
void rearrangeQueue(Bank *);
void getFinishedExit(Bank *);
void sendToExit(Bank *);
int getWaitingTime(LinkedList *);

int main()
{
	double totalTransactionTime = 0;
	double totalWaitingTime = 0;
	double totalQueueWaitingTime = 0;
	double averageQueueWaitingTime = 0;
	double totalNumberOfClients = 0;
	double averageWaitingTime = 0;
	double averageTransactionTime = 0;
	double numberOfQueueClients = 0;
	double totalQueueWorkTime = 0;
	double averageQueue = 0;
	int time = 0;

	int userInput;
	Client * client;
	Node * node;
	LinkedList * allClients = new LinkedList();
	LinkedList * finishedClients = new LinkedList();

	Queue * queue1 = new Queue();
	Queue * queue2 = new Queue();
	Queue * queue3 = new Queue();

	Teller * teller1 = new Teller(1);
	teller1->setQueue(queue1);
	Teller * teller2 = new Teller(2);
	teller2->setQueue(queue2);
	Teller * teller3 = new Teller(3);
	teller3->setQueue(queue3);

	Teller ** tellers = new Teller*[3];
	tellers[0] = teller1;
	tellers[1] = teller2;
	tellers[2] = teller3;

	Bank * myBank = new Bank(3);
	myBank->setTellers(tellers);

	//################################################### GATHER ALL CLIENTS ######################################################

	// Fill all Clients in LinkedList
	do {
		client = getClients();
		totalTransactionTime += client->getTransactionTime();
		node = new Node(client);
		allClients->addNode(node);
		myBank->increamentTotalNumberOfCustomers();
		cout << endl << "Another client?" << endl << "Enter 0 if yes, ";
		cin >> userInput;
		system("cls");
	} while (userInput == 0);
	allClients->bubbleSort();

	//################################################### START ######################################################

	while (myBank->getTellers()[0]->getQueue()->getLength() > 0
		|| myBank->getTellers()[1]->getQueue()->getLength() > 0
		|| myBank->getTellers()[2]->getQueue()->getLength() > 0
		|| myBank->getExitAreaLength() > 0
		|| allClients->getLength() > 0)
	{
		int t1 = myBank->getTellers()[0]->getQueue()->getLength();
		int t2 = myBank->getTellers()[1]->getQueue()->getLength();
		int t3 = myBank->getTellers()[2]->getQueue()->getLength();
		int ex = myBank->getExitAreaLength();
		int remaining = allClients->getLength();

		// POP FINISHED
		popFinished(myBank, finishedClients);

		// RETURN FROM EXIT
		getFinishedExit(myBank);

		// SEND EXITS OUT
		sendToExit(myBank);

		// ADD CLIENTS
		enqueueClient(allClients, myBank, time);

		// SORT QUEUES
		rearrangeQueue(myBank);

		// WHEN TIME IS DONE
		time++;
		for (int i = 0; i < myBank->getNumberOfTellers(); i++) {
			myBank->getTellers()[i]->increamentTotalWorkingTime();
			myBank->getTellers()[i]->increamentTotalWaitingTime();
			myBank->getTellers()[i]->increamentTime();
		}
		if (myBank->getExitAreaLength() > 0)
			myBank->getExitArea()->increamentExitArea();
	}


	//#################################################### REPORT #############################################################

	totalNumberOfClients = myBank->getTotalNumberOfCustomers();
	totalWaitingTime = getWaitingTime(finishedClients);
	averageWaitingTime = totalWaitingTime / totalNumberOfClients;
	averageTransactionTime = totalTransactionTime / totalNumberOfClients;

	cout << "Total Number of Clients: " << totalNumberOfClients << endl;
	cout << "Total Waiting Time of Clients: " << totalWaitingTime << endl;
	cout << "Average Waiting Time of Clients: " << averageWaitingTime << endl;
	cout << "Total Transaction Time of Clients: " << totalTransactionTime << endl;
	cout << "Average Transaction Time of Clients: " << averageTransactionTime << endl;

	for (int i = 0; i < myBank->getNumberOfTellers(); i++) {
		cout << endl;
		numberOfQueueClients = myBank->getTellers()[i]->getTotalNumberOfCustomers();
		totalQueueWorkTime = myBank->getTellers()[i]->getTotalWorkingTime();
		averageQueue = totalQueueWorkTime / numberOfQueueClients;
		totalQueueWaitingTime = myBank->getTellers()[i]->getTotalWaitingTime();
		averageQueueWaitingTime = totalQueueWaitingTime / numberOfQueueClients;
		cout << "Queue number: " << i + 1 << endl;
		cout << "Number of Clients Served: " << numberOfQueueClients << endl;
		cout << "Total Working Time: " << totalQueueWorkTime << endl;
		cout << "Average Time per Client: " << averageQueue << endl;
		cout << "Total Waiting Time: " << totalQueueWaitingTime << endl;
		cout << "Average Waiting Time per Client: " << averageQueueWaitingTime << endl;

	}

	return 1;
}

int getWaitingTime(LinkedList * finishedClients) {
	Node * current = finishedClients->getHead();
	int totalWaitingTime = 0;
	while (current != NULL) {
		totalWaitingTime += current->getClient()->getWaitingTime();
		current = current->getNext();
	}
	return totalWaitingTime;
}

void sendToExit(Bank * myBank) {
	Client * client;
	for (int i = 0; i < myBank->getNumberOfTellers(); i++) {
		if (myBank->getTellers()[i]->getQueue()->getLength() != 0) {
			client = myBank->getTellers()[i]->getQueue()->getFirst()->getClient();
			if (client->getExitsCount() > 0) {
				if (!client->getFinishedExits()) {
					if (client->getClientExitsList()[client->getCurrentExit()]->getExitTime() == client->getTransactionTimeCounter()) {
						myBank->getExitArea()->addNode(myBank->getTellers()[i]->getQueue()->dequeue());
						client->setIsExiting(true);
					}
				}
			}
		}
	}
}

void getFinishedExit(Bank * myBank) {
	Node * current = myBank->getExitArea()->finishedWaiting();
	while (current != NULL) {
		myBank->getTellers()[current->getClient()->getQueueNumber()]->getQueue()->enqueue(current);
		current->getClient()->increamentToNextExit();
		current = myBank->getExitArea()->finishedWaiting();
	}
}

void rearrangeQueue(Bank * myBank) {
	int shortestQueueIndex = findShortestQueue(myBank);
	Node * current = NULL;
	Node * tempNode = NULL;
	bool queueDone = true;
	for (int i = 0; i < myBank->getNumberOfTellers(); i++) {
		current = myBank->getTellers()[i]->getQueue()->getLast();
		while (queueDone && current != NULL && current != myBank->getTellers()[i]->getQueue()->getFirst()) {
			if (!current->getClient()->getIsExiting()) {
				int currentIndex = findIndex(myBank->getTellers()[i]->getQueue(), current);
				if (currentIndex > myBank->getTellers()[shortestQueueIndex]->getQueue()->getLength()) {
					tempNode = current->getNext();
					myBank->getTellers()[i]->getQueue()->removeNode(current);
					myBank->getTellers()[shortestQueueIndex]->getQueue()->enqueue(current);
					shortestQueueIndex = findShortestQueue(myBank);
				}
				else {
					queueDone = false;
				}
				current = tempNode;
			}
			else {
				current = current->getPrevious();
			}
		}
	}
}

void enqueueClient(LinkedList * allClients, Bank * myBank, int time) {
	Node * current = allClients->getHead();
	while (current != NULL && current->getClient()->getEnteringTime() == time) {
		int index = findShortestQueue(myBank);
		myBank->getTellers()[index]->getQueue()->enqueue(allClients->pop());
		current->getClient()->setQueueNumber(index);
		current = allClients->getHead();
	}
}

void popFinished(Bank * myBank, LinkedList * finishedClients) {
	for (int i = 0; i < myBank->getNumberOfTellers(); i++) {
		if (myBank->getTellers()[i]->getQueue()->getLength() != 0) {
			if (myBank->getTellers()[i]->getQueue()->getFirst()->getTransactionTimeCounter() ==
				myBank->getTellers()[i]->getQueue()->getFirst()->getClient()->getTransactionTime()) {
				myBank->getTellers()[i]->increamentTotlatNumberOfCustomer();
				finishedClients->addNode(myBank->getTellers()[i]->getQueue()->dequeue());
			}
		}
	}
}

void sortExitArray(Client * client) {
	Exits * current = NULL;
	Exits * temp = NULL;
	int isSorted = 0, i = 0;
	while (i < client->getExitsCount() - 1 && !isSorted) {
		current = client->getClientExitsList()[i];
		for (int j = 0; j < client->getExitsCount() - i - 1; j++) {
			isSorted = 1;
			if (current->getExitTime() > client->getClientExitsList()[j + 1]->getExitTime()) {
				temp = client->getClientExitsList()[j + 1];
				client->getClientExitsList()[j + 1] = current;
				current = temp;
				isSorted = 0;
			}
		}
		i++;
	}
}

int findIndex(Queue * myQueue, Node * node) {
	Node * current = myQueue->getFirst();
	int counter = 0;
	while (current != NULL) {
		if (current == node) {
			return counter;
		}
		counter++;
		current = current->getNext();
	}
	return -1;
}

int findShortestQueue(Bank * myBank) {
	int minimum = myBank->getTellers()[0]->getQueue()->getLength();
	int index = 0;
	for (int i = 0; i < myBank->getNumberOfTellers(); i++) {
		if (minimum > myBank->getTellers()[i]->getQueue()->getLength()) {
			minimum = myBank->getTellers()[i]->getQueue()->getLength();
			index = i;
		}
	}
	return index;
}

int findLongestQueue(Bank * myBank) {
	int maximum = myBank->getTellers()[0]->getQueue()->getLength();
	int index = 0;
	for (int i = 0; i < myBank->getNumberOfTellers(); i++) {
		if (maximum < myBank->getTellers()[i]->getQueue()->getLength()) {
			maximum = myBank->getTellers()[i]->getQueue()->getLength();
			index = i;
		}
	}
	return index;
}

void displayAllClients(LinkedList * allClients) {
	Node * current = allClients->getHead();
	Client * tempClient;

	while (current != NULL) {
		tempClient = current->getClient();
		cout << endl << "*****CLIENT*****" << endl;
		cout << "client ID: " << tempClient->getId() << endl;
		//cout << "client Name: " << tempClient->getName() << endl;
		cout << "client entering time: " << tempClient->getEnteringTime() << endl;
		cout << "client duration: " << tempClient->getTransactionTime() << endl;
		cout << "client exits count: " << tempClient->getExitsCount() << endl;

		for (int i = 0; i < tempClient->getExitsCount(); i++) {
			cout << "exit number " << i + 1 << ":" << endl;
			cout << tempClient->getClientExitsList()[i]->getDuration() << endl;
			cout << tempClient->getClientExitsList()[i]->getExitTime() << endl;
			cout << tempClient->getClientExitsList()[i]->getWaitingDuration() << endl;
		}
		current = current->getNext();
	}
}

Client * getClients() {
	Client * client;
	Exits * exit;
	Exits ** exitArray;
	int id;
	string name;
	int enterTime;
	int totalDuration;
	int numberOfExits;
	int exitMoment;
	int exitDuration;
	int userInput;

	cout << "Please enter the client Data: " << endl;
	cout << "ID: ";
	cin >> id;
	cout << "Name: ";
	cin >> name;
	do {
		cout << "Enter Time: ";
		cin >> enterTime;
	} while (enterTime < 0);
	do {
		cout << "Enter the duration: ";
		cin >> totalDuration;
	} while (totalDuration < 1);
	if (totalDuration != 1) {
		cout << "Does the Client Have Exits?" << endl;
		cout << "if yes enter 0: ";
		cin >> userInput;
	}
	else {
		userInput = 1;
	}
	if (userInput == 0) {
		do {
			cout << "How many exits?" << endl << "Note: he can only have " << totalDuration - 1 << " exits." << endl;
			cin >> numberOfExits;
		} while (numberOfExits >= totalDuration || numberOfExits < 0);
		exitArray = new Exits*[numberOfExits];

		int * exitIndexs = new int[numberOfExits];
		for (int i = 0; i < numberOfExits; i++) {
			cout << endl << "Exit number -> " << i + 1 << ":" << endl;
			do {
				cout << "Please enter the right exit moment: ";
				cin >> exitMoment;
			} while (exitMoment >= totalDuration || exitMoment < 0 || checkForExits(exitMoment, exitIndexs, numberOfExits));
			exitIndexs[i] = exitMoment;
			do {
				cout << "Please enter the Exit duration: ";
				cin >> exitDuration;
			} while (exitDuration <= 0);
			exit = new Exits(exitMoment, exitDuration);
			exitArray[i] = exit;
		}
		client = new Client(id, name, enterTime, totalDuration, numberOfExits);
		client->setClientExitsList(exitArray);
		sortExitArray(client);
	}
	else {
		client = new Client(id, name, enterTime, totalDuration, 0);
	}
	return client;
}

bool checkForExits(int x, int arr[], int _size) {
	for (int i = 0; i < _size; i++) {
		if (arr[i] == x)
			return true;
	}
	return false;
}

