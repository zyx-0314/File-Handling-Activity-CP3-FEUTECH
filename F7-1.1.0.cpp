#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

struct Player
{
  const static int MAX = 10;

  std::string nickname = "";
  int age = 0;
  double scores[MAX] = {};

  std::string Format()
  {
    std::string data = "";
    
    data = "Name: " + this->nickname + "\n"
         + "Age: " + std::to_string(this->age) + "\n"
         + "Scores: ";
    for (size_t i = 0; i < this->MAX; i++) {
      data += std::to_string(this->scores[i]);

      if (i == this->MAX - 1)
        data += "\n";
      else
        data += ", ";
    }

    return data;
  }

  void Display()
  {
    std::cout << this->Format();
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
void SaveFile(Node *&, std::string&);
void ReadFile(std::string);
void SetFileName(std::string &);
void RecordFileName(std::string, std::string);

int main()
{
  int choice;
  Player tempDataHolder;
  std::string recordFile, fileNameList = "FileNameList.txt";
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
      RecordFileName(fileNameList, recordFile);
      SaveFile(head, recordFile);
      break;
    case 4:
      ReadFile(fileNameList);
      SetFileName(recordFile);
      ReadFile(recordFile);
      system("pause");
      system("cls");
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

void SaveFile(Node *&head, std::string& recordFile)
{
  Node *current = head;
  std::ofstream outFile;

  if (current == nullptr)
  {
    std::cout << "No Record Yet\n";
    system("pause");
    system("cls");
    return;
  }
  else
  {
    SetFileName(recordFile);

    outFile.open(recordFile);
    
    if (outFile.is_open())
    {
      while (current)
      {
        // call the format function of the player structure
        outFile << current->player.Format();

        // Move to the next node
        current = current->next;
      }

      // display message that the records are saved
      std::cout << "Records saved to " << recordFile << "." << std::endl;
    }
    else
      std::cout << "Invalid" << std::endl;

    outFile.close();
  }

  system("pause");
  system("cls");
}

void ReadFile(std::string fileName)
{
  std::ifstream inFile(fileName);

  if (!inFile.is_open())
    std::cout << "File not found." << std::endl;
  else
    std::cout << inFile.rdbuf();

  // Close file connection
  inFile.close();
}

void SetFileName(std::string & recordFile)
{
    std::cout << "Enter File Name: ";
    std::cin >> recordFile;

    system("cls");
  
    if (recordFile.find(".txt")  == std::string::npos)
      recordFile = recordFile + ".txt";
}

void RecordFileName(std::string listOfFile, std::string fileName)
{
  std::ofstream outFile(listOfFile, std::ios::app);
  std::ifstream inFile;
  std::string temp;

  if (outFile)
  {
    inFile.open(listOfFile);

    while (inFile >> temp)
      if (temp == fileName)
        return;

    outFile << fileName << std::endl;
  }
  else
  {
    outFile.open(listOfFile);

    if (outFile)
      outFile << fileName << std::endl;
    else
      std::cout << "Invalid" << std::endl;
  }
}
