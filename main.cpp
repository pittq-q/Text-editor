#include <iostream>
#include <fstream>

void CheckingTheCommandSpelling(const int argc, const char* argv[]);

template<typename StreamType>
void CheckingForFileOpening(StreamType& fileStream);


int main(int argc, char* argv[])
{
	int choice = 0;
	CheckingTheCommandSpelling(argc, argv);

	std::ifstream fileStreamin(argv[1]);
	if (!fileStreamin.is_open())
	{
		std::cerr << "This file does not exist. Do you want to create him? (1 - Yes, Another_key - No)\n";
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');
		if (choice != 1)
		{
			fileStreamin.close();
			return 0;
		}
	}

	system("cls");
	char character;
	while (fileStreamin.get(character))
	{
		std::cout << character;
	}
	fileStreamin.close();

	std::ofstream fileStreamout(argv[1], std::ios::app);
	CheckingForFileOpening(fileStreamout);

	std::cout << "\n\nWhat do you want to do?\n"
		<< "1 - Close file;\n"
		<< "2 - Start writing a text from the end;\n"
		<< "3 - Start writing a text from specific point;\n"
		<< "4 - Delete some character;\n"
		<< "5 - Delete some word;\n";
	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	switch (choice)
	{
	case 1:
		fileStreamout.close();
		break;

	case 2: 
	{
		std::cout << "!Warning: You can writing 1 line only (In next update, i going to fix it)." << std::endl
			<< "Choose a size of your text: ";

		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');

		char* text = new char[choice];
		std::cin.getline(text, choice);

		fileStreamout << text;

		std::cout << "Your file has been changed. I will close it.\n";

		delete[] text;
		fileStreamout.close();
		break;
	}
	case 3:
	{
		std::cout << "Enter the position you want to do from (start from 0): ";
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');

		fileStreamout.seekp(std::ios::beg, choice);

		std::cout << "!Warning: You can writing 1 line only (In next update, i will fix it)." << std::endl
			<< "Choose a size of your text: ";

		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');

		char* text = new char[choice];
		std::cin.getline(text, choice);

		fileStreamout << text;

		std::cout << "Your file has been changed. I will close it.\n";

		delete[] text;
		fileStreamout.close();
		break;
	}
	case 4:
	{
		std::cout << "Enter the position of the character you want to delete (start from 0): ";
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');

		fileStreamout.close();
		fileStreamin.open(argv[1]);
		CheckingForFileOpening(fileStreamin);

		fileStreamin.seekg(std::ios::beg, choice);
		int firstPos = fileStreamin.peek();
		fileStreamin.seekg(std::ios::end);
		int lastPos = fileStreamin.peek();

		char* text = new char[lastPos - firstPos];

		for (size_t i = 0; i < lastPos - firstPos; i++)
		{
			text[i] = fileStreamin.get();
		}
		fileStreamin.close();

		fileStreamout.open(argv[1]);
		CheckingForFileOpening(fileStreamout);
		fileStreamout.seekp(std::ios::beg, choice);

		for (size_t i = 1; i < lastPos - firstPos; i++)
		{
			fileStreamout.put(text[i]);
		}

		std::cout << "Your file has been changed. I will close it.\n";
		delete[] text;
		fileStreamout.close();
		break;
	}
	case 5:
	{
		std::cout << "Enter the position of the character you want to delete (start from 0): ";
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');

		fileStreamout.close();
		fileStreamin.open(argv[1]);
		CheckingForFileOpening(fileStreamin);

		fileStreamin.seekg(std::ios::beg, choice);
		int firstPos = fileStreamin.peek();
		fileStreamin.seekg(std::ios::end);
		int lastPos = fileStreamin.peek();

		char* text = new char[lastPos - firstPos];
		int posOfTheSelectedWord = 0;

		for (size_t i = 0; i < lastPos - firstPos; i++)
		{
			text[i] = fileStreamin.get();
			if (text[i] == ' ' || text[i] == '\n')
			{
				posOfTheSelectedWord = i;
			}
		}
		fileStreamin.close();

		fileStreamout.open(argv[1]);
		CheckingForFileOpening(fileStreamout);
		fileStreamout.seekp(std::ios::beg, choice);

		for (size_t i = posOfTheSelectedWord; i < lastPos - firstPos; i++)
		{
			fileStreamout.put(text[i]);
		}

		std::cout << "Your file has been changed. I will close it.\n";
		delete[] text;
		fileStreamout.close();
		break;
	}
	default:
		std::cout << "You entered uncorrect choice. I will close your file :)\n";
		fileStreamout.close();
		break;
	}

	return 0;
}

void CheckingTheCommandSpelling(const int argc, const char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "You didn't entered file for editing!";
		exit(1);
	}

	if (argc > 2)
	{
		std::cerr << "You entered too many arguments!";
		exit(1);
	}

	int count = 0;
	while (argv[1][count] != '.')
	{
		if (argv[1][count] == '\0')
		{
			std::cerr << "Your file doesn't have extension!";
			exit(1);
		}
		count++;
	}
}

template<typename StreamType>
void CheckingForFileOpening(StreamType& fileStream)
{
	if (!fileStream.is_open())
	{
		std::cerr << "Couldn't open the file. I will stop program.\n";
		exit(1);
	}
}
