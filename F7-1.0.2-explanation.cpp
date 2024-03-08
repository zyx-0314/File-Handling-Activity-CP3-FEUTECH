#include <iostream>
#include <string>
#include <fstream>

// Structure that holds Data
struct Player
{
  // Controls Maximum Scores that can be hold
  const static int MAX = 10;

  std::string nickname = "";
  int age = 0;
  double scores[MAX] = {};

  // Function used to display data stored
  void Display()
  {
    std::cout
        << "Name: " << this->nickname << std::endl
        << "Age: " << this->age << std::endl
        << "Scores: ";
    for (size_t i = 0; i < this->MAX; i++)
    {
      std::cout << scores[i];

      if (i == this->MAX - 1)
        std::cout << std::endl;
      else
        std::cout << ", ";
    }
  }
};

// Used to create node inside the LinkedList
struct Node
{
  // Address of Following Node
  Node *next;

  // Data Node Holds
  Player player;
};

// Functions that is used for Menus
void MainMenu(int &);

void AddData(Player &);
void AddRecord(Player &, Node *&head, Node *&tail);
void ViewRecord(Node *&);
void OpenFile(Node *&, std::string);
void ReadFile(std::string);

int main()
{
  int choice;
  Player tempDataHolder;
  std::string recordFile = "Formative-7.txt";
  Node *head = NULL, *tail = NULL;

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
      OpenFile(head, recordFile);
      break;
    case 4:
      ReadFile(recordFile);
      break;
    case 0:
      exit(0);
    default:
      break;
    }

  } while (true);
}

void MainMenu(int &choice)
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

// THis Function add Information inside the Node
void AddData(Player &tempDataHolder)
{
  // Enter data nickname and age
  std::cout << "Enter Player Name: ";
  std::cin >> tempDataHolder.nickname;

  std::cout << "Enter Player Age: ";
  std::cin >> tempDataHolder.age;

  // Enter scores, number of scores are based on MAX
  for (size_t i = 0; i < tempDataHolder.MAX; i++)
  {
    std::cout << "Enter Player Scores " << i + 1 << ": ";
    std::cin >> tempDataHolder.scores[i];
  }
}

// This function adds Node in the Linked List
void AddRecord(Player &tempDataHolder, Node *&head, Node *&tail)
{
  Node *temp = new Node;

  // Preparing the node, by storing Data and Setting it next as NULL
  temp->player = tempDataHolder;
  temp->next = NULL;

  // If there is no Head(No Linked List yet)
  if (!head)
    head = temp;
  // If there is Head
  else
    tail->next = temp;

  // Set the new tail
  tail = temp;
}

// Traverse Records
void ViewRecord(Node *&head)
{
  // create temporary node(current) for traversing the linked list
  Node *temp = head;

  if (!head)
    std::cout << "-- No List Yet --";
  else
  {
    // traverse while there is data in the linked list
    while (temp)
    {
      // call the display function of the player structure
      temp->player.Display();
      // Move to the next node
      temp = temp->next;
    }
  }

  system("pause");
  system("cls");
}

// Create Permanent File and Stores Data hold in the LinkedList
void OpenFile(Node *&head, std::string recordFile)
{
  // create temporary node(current) for traversing the linked list
  Node *current = head;
  // creates or connect to file
  std::ofstream outFile(recordFile);

  // checks if the file is open and if there is data in the linked list
  if (current != nullptr && outFile.is_open())
  {
    // traverse while there is data in the linked list
    while (current)
    {
      outFile
          << "Name: " << current->player.nickname << std::endl
          << "Age: " << current->player.age << std::endl
          << "Scores: ";

      for (int i = 0; i < head->player.MAX; ++i)
      {
        outFile << current->player.scores[i];
        if (i == current->player.MAX - 1)
          outFile << std::endl;
        else
          outFile << ", ";
      }

      // Move to the next node
      current = current->next;
    }

    std::cout << "Records saved to 'player_recordz.txt'." << std::endl;
  }
  else
    std::cout << "Invalid" << std::endl;

  outFile.close();
  system("pause");
  system("cls");
}

// Read Permanent File
void ReadFile(std::string recordFile)
{
  // Read from recordFile
  std::ifstream inFile(recordFile);

  // Check if file is open
  if (!inFile.is_open())
    std::cout << "File not found." << std::endl;
  else
    // Convert Data
    std::cout << inFile.rdbuf();

  // Close file connection
  inFile.close();

  system("pause");
  system("cls");
}
