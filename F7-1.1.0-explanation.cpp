#include <cstdlib>
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

  // Function used to format data
    // following DRY principle
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

  // Function used to display data stored
  void Display()
  {
    std::cout << this->Format();
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
void SaveFile(Node *&head, std::string& recordFile)
{
  // create temporary node(current) for traversing the linked list
  Node *current = head;
  // creates or connect to file
  std::ofstream outFile;

  // checks if there is no data in the linked list
  if (current == nullptr)
  {
    std::cout << "No Record Yet\n";
    system("pause");
    system("cls");
    return;
  }
  // if there is data in the linked list
  else
  {
    // set the file name
    SetFileName(recordFile);

    // connect to file
    outFile.open(recordFile);
    
    // checks if the file is open and if there is data in the linked list
    if (outFile.is_open())
    {
      // traverse while there is data in the linked list
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

// Read Permanent File
void ReadFile(std::string fileName)
{
  // Read from fileName
  std::ifstream inFile(fileName);

  // Check if file is open
  if (!inFile.is_open())
    std::cout << "File not found." << std::endl;
  else
    // Convert Data
    std::cout << inFile.rdbuf();

  // Close file connection
  inFile.close();
}

// Set File Name
void SetFileName(std::string & recordFile)
{
    std::cout << "Enter File Name: ";
    std::cin >> recordFile;

    system("cls");
  
    // check if .txt is not in the input, then add the ,txt
    if (recordFile.find(".txt")  == std::string::npos)
      recordFile = recordFile + ".txt";
}

// creates record of file names
void RecordFileName(std::string listOfFile, std::string fileName)
{
  // connects to file and appends data
  std::ofstream outFile(listOfFile, std::ios::app);
  std::ifstream inFile;
  std::string temp;

  // checks if the file is open to append
  if (outFile)
  {
    // connects to file and reads data
    inFile.open(listOfFile);

    // traverse and check if the file name is already in the list
    while (inFile >> temp)
      if (temp == fileName)
        return;

    // if file name is not in the list, append the file name
    outFile << fileName << std::endl;
  }
  else
  {
    // if file is not open, create a new file
    outFile.open(listOfFile);

    // checks if the file is open
    if (outFile)
      outFile << fileName << std::endl;
    else
      std::cout << "Invalid" << std::endl;
  }
}
