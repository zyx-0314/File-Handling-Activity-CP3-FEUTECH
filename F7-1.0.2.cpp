#include <iostream>
#include <string>
#include <fstream>

struct Player
{
  const static int MAX = 10;

  std::string nickname = "";
  int age = 0;
  double scores[MAX] = {};

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

struct Node
{
  Node *next;

  Player player;
};

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

void AddData(Player &tempDataHolder)
{
  std::cout << "Enter Player Name: ";
  std::cin >> tempDataHolder.nickname;

  std::cout << "Enter Player Age: ";
  std::cin >> tempDataHolder.age;

  for (size_t i = 0; i < tempDataHolder.MAX; i++)
  {
    std::cout << "Enter Player Scores " << i + 1 << ": ";
    std::cin >> tempDataHolder.scores[i];
  }
}

void AddRecord(Player &tempDataHolder, Node *&head, Node *&tail)
{
  Node *temp = new Node;

  temp->player = tempDataHolder;
  temp->next = NULL;

  if (!head)
    head = temp;
  else
    tail->next = temp;

  tail = temp;
}

void ViewRecord(Node *&head)
{
  Node *temp = head;

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

void OpenFile(Node *&head, std::string recordFile)
{
  Node *current = head;
  std::ofstream outFile(recordFile);

  if (current != nullptr && outFile.is_open())
  {
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

void ReadFile(std::string recordFile)
{
  std::ifstream inFile(recordFile);

  if (!inFile.is_open())
    std::cout << "File not found." << std::endl;
  else
    std::cout << inFile.rdbuf();

  inFile.close();

  system("pause");
  system("cls");
}
