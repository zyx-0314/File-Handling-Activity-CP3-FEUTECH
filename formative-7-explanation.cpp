#include <iostream>
#include <string>
#include <fstream>

// holds data of player
struct Player
{
	const static int MAX = 5;

	std::string nickname = "";
	int age = 0;
	double scores[MAX] = {};

	void Display()
	{
		std::cout
			<< nickname << " - " << age << "\n"
			<< "Scores:\n";
		for (size_t i = 0; i < this->MAX; i++)
			std::cout << "\t" << scores[i] << "\n";
	}
};

struct Node
{
	// address
	Node* next;

	// data
	Player player;
};

void MainMenu(int&);

void AddData(Player&);
void AddRecord(Player&, Node*&);
void ViewRecord(Node*&);
void OpenFile(Node*& head);
void ReadFile(Node*& head);
void CloseFile();

int main()
{
	int choice;
	// using principle of FILO
		// it only uses head
	Node* head = new Node;
	Player tempDataHolder;

	do
	{
		MainMenu(choice);


		switch (choice)
		{
		case 1:
			AddData(tempDataHolder);
			AddRecord(tempDataHolder, head);
			system("cls");
			break;
		case 2:
			ViewRecord(head);
			break;
		case 3:
			OpenFile(head);
			CloseFile();
			break;
		case 4:
			ReadFile(head);
			CloseFile();
		default:
			break;
		}

	} while (true);

}

void MainMenu(int& choice)
{
	do
	{
		std::cout
			<< "1. Add Record\n"
			<< "2. Check Record\n"
			<< "3. Save\n"
			<< "4. Read\n"
			<< "\n"
			<< ":: ";
		std::cin >> choice;
		system("cls");
	} while (choice < 1 && choice > 3);
}

void AddData(Player& tempDataHolder)
{
	// enter data nickname and age
	std::cout << "Enter Player Name: ";
	std::cin >> tempDataHolder.nickname;

	std::cout << "Enter Player Age: ";
	std::cin >> tempDataHolder.age;

	// enter scores, number of scores are based on MAX
	for (size_t i = 0; i < tempDataHolder.MAX; i++)
	{
		std::cout << "Enter Player Scores " << i + 1 << ": ";
		std::cin >> tempDataHolder.scores[i];
	}
}

void AddRecord(Player& tempDataHolder, Node*& head)
{
	// making node temporary
	Node* temp = new Node;

	// adding information to the node
	temp->player = tempDataHolder;

	// always set next on temp in null
	temp->next = NULL;

	// setting that the head will have next node
	head->next = temp;

	// stating that the new head are temp
	head = temp;
}

void ViewRecord(Node*& head)
{
	Node* temp = head;

	if (!head)
		std::cout << "-- No List Yet --";
	else
	{
		while (temp)
		{
			temp->player.Display();
			temp = temp->next;
		}
	}

	system("pause");
	system("cls");
}

void OpenFile(Node*& head) {
	std::ofstream outFile("player_records.txt");
	Node* current = head;

	while (current != nullptr) {
		outFile << "Name:: " << current->player.nickname << std::endl;
		outFile << "Age: " << current->player.age << std::endl;
		outFile << "Scores:";
		for (int i = 0; i < 5; ++i) {
			outFile << current->player.scores[i] << " ";
		}
		outFile << std::endl;
		current = current->next;
	}
	outFile.close();
	std::cout << "Records saved to 'player_records.txt'." << std::endl;
}

void ReadFile(Node*& head)
{
	std::ifstream inFile("player_records.txt");

	std::cout << inFile.rdbuf();

	system("pause");
	system("cls");
}

// Function to indicate closing the file
void CloseFile() {
	std::cout << "File closed." << std::endl;
}
