#include <iostream>
#include <string>
#include <fstream>

// holds data of player
struct Player
{
	const static int MAX = 10;

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
void AddRecord(Player&, Node*& head, Node*& tail);
void ViewRecord(Node*&);
void OpenFile(Node*& head);
void ReadFile(Node*& head);
void CloseFile();

int main()
{
	int choice;
	// using principle of FILO
		// it only uses head
	Node* head = NULL;
	Node* tail = NULL;
	Player tempDataHolder;

	do
	{
		MainMenu(choice);


		switch (choice)
		{
		case 1:
			AddData(tempDataHolder);
			AddRecord(tempDataHolder, head, tail);
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
			break;
		case 0:
			exit(0);
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
			<< "0. Exit\n"
			<< "\n"
			<< ":: ";
		std::cin >> choice;
		system("cls");
	} while (choice < 0 || choice > 4);
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

void AddRecord(Player& tempDataHolder, Node*& head, Node*& tail)
{
	Node* temp = new Node;
	

	temp->player = tempDataHolder;

	temp->next = NULL;

	if (head == NULL)
	{
		head = temp;
	}
	else {
		tail->next = temp;
	
	}
	tail = temp;
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
	std::ofstream outFile("player_recordz.txt");
	Node* current = head;

	if (current != nullptr && outFile.is_open()) {

		while (current)
		{
			outFile << "Name: " << current->player.nickname << std::endl;
			outFile << "Age: " << current->player.age << std::endl;
			outFile << "Scores: ";
			for (int i = 0; i < head->player.MAX; ++i) {
				outFile << current->player.scores[i] << " ";
			}
			outFile << std::endl;
			current = current->next;
		}

		std::cout << "Records saved to 'player_recordz.txt'." << std::endl;
	}
	else {
		std::cout << "Invalid" << std::endl;
	}
	
	outFile.close();
	
	
}

void ReadFile(Node*& head)
{
	std::ifstream inFile("player_recordz.txt");

	std::cout << inFile.rdbuf();

	inFile.close();

	system("pause");
	system("cls");
}

// Function to indicate closing the file
void CloseFile() {
	std::cout << "File closed." << std::endl;
}
