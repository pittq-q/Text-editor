#include "WorkWithFile.h"

void CheckingTheCommandSpelling(const int argc, char* argv[])
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

void CheckingForFileOpening(std::fstream& fileStream)
{
	if (!fileStream.is_open())
	{
		std::cerr << "Couldn't open the file. I will stop program.\n";
		exit(1);
	}
}

void ReadingFile(std::fstream& fileStream)
{
	char character;
	while (fileStream.get(character))
	{
		std::cout << character;
	}

	fileStream.clear();
}

void StartWritingATextFromTheEnd(int choice, std::fstream& fileStream)
{
	std::cout << "!Warning: You can writing 1 line only (In next update, i going to fix it)." << std::endl
		<< "Choose a size of your text: ";

	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	char* text = new char[choice];
	std::cin.getline(text, choice);

	fileStream.seekp(0, std::ios::end);
	fileStream << text;

	std::cout << "Your file has been changed. I will close it.\n";

	delete[] text;
}

void StartWritingATextFromSpecificPoint(int choice, std::fstream& fileStream)
{
	std::cout << "Enter the position you want to do from (start from 0): ";
	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	fileStream.seekp(choice, std::ios::beg);

	std::cout << "!Warning: You can writing 1 line only (In next update, i will fix it)." << std::endl
		<< "Choose a size of your text: ";

	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	char* text = new char[choice];
	std::cin.getline(text, choice);

	fileStream << text << '\n';

	std::cout << "Your file has been changed. I will close it.\n";

	delete[] text;
}

void DeleteSomeCharacterFromFile(int choice, const char* argv, std::fstream& fileStream)
{
	std::cout << "Enter the position of the character you want to delete (start from 0): ";
	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	fileStream.seekg(std::ios::beg, choice);
	int firstPos = fileStream.peek();
	fileStream.seekg(std::ios::end);
	int lastPos = fileStream.peek();

	char* text = new char[lastPos - firstPos];

	for (size_t i = 0; i < lastPos - firstPos; i++)
	{
		text[i] = fileStream.get();
	}

	fileStream.seekp(std::ios::beg, choice);

	for (size_t i = 1; i < lastPos - firstPos; i++)
	{
		fileStream.put(text[i]);
	}

	std::cout << "Your file has been changed. I will close it.\n";
	delete[] text;
}

void DeleteSomeWordFromFile(int choice, const char* argv, std::fstream& fileStream)
{
	std::cout << "Enter the position of the character you want to delete (start from 0): ";
	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	fileStream.seekg(std::ios::beg, choice);
	int firstPos = fileStream.peek();
	fileStream.seekg(std::ios::end);
	int lastPos = fileStream.peek();

	char* text = new char[lastPos - firstPos];
	int posOfTheSelectedWord = 0;

	for (size_t i = 0; i < lastPos - firstPos; i++)
	{
		text[i] = fileStream.get();
		if (text[i] == ' ' || text[i] == '\n')
		{
			posOfTheSelectedWord = i;
		}
	}

	fileStream.seekp(std::ios::beg, choice);

	for (size_t i = posOfTheSelectedWord; i < lastPos - firstPos; i++)
	{
		fileStream.put(text[i]);
	}

	std::cout << "Your file has been changed. I will close it.\n";
	delete[] text;
}