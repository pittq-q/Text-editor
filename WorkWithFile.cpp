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

void WritingIntoFile(int SIZE, std::fstream& fileStream)
{
	std::cout << "Now, you can write (Double \"enter\" for completion): \n";
	char* text = new char[SIZE];
	do
	{
		std::cin.getline(text, SIZE);
		if (text[0] == '\0')
		{
			break;
		}
		fileStream << text << '\n';
		memset(text, 0, SIZE);
	} while (true);

	std::cout << "Your file has been changed. I will close it.\n";

	delete[] text;
}

void StartWritingATextFromTheEnd(int* choice, std::fstream& fileStream)
{
	std::cout << "Choose a size of your text: ";

	std::cin >> *choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	fileStream.seekp(0, std::ios::end);

	WritingIntoFile(*choice, fileStream);
}

void StartWritingATextFromSpecificPoint(int* choice, std::fstream& fileStream)
{
	std::cout << "Enter the position you want to do from (start from 0): ";
	std::cin >> *choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	fileStream.seekp(*choice, std::ios::beg);

	std::cout << "Choose a size of your text: ";

	std::cin >> *choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	WritingIntoFile(*choice, fileStream);
}

void DeleteSomeCharacterFromFile(int* choice, const char* argv, std::fstream& fileStream)
{
	std::cout << "Enter the position of the character you want to delete (start from 0): ";
	std::cin >> *choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	fileStream.seekg(0, std::ios::end);
	std::streamsize fileSize = fileStream.tellg();

	char* text = new char[fileSize];

	fileStream.close();
	fileStream.open(argv, std::ios::in | std::ios::binary);
	fileStream.read(text, fileSize);
	fileStream.clear();
	fileStream.close();

	fileStream.open(argv, std::ios::out | std::ios::binary);
	CheckingForFileOpening(fileStream);

	fileStream.write(text, *choice);
	fileStream.write(text + *choice + 1, fileSize - *choice - 1);

	std::cout << "Your file has been changed. I will close it.\n";
	delete[] text;
}

void DeleteSomeWordFromFile(int* choice, const char* argv, std::fstream& fileStream)
{
	std::cout << "Enter the position of the word you want to delete (start from 0): ";
	std::cin >> *choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	fileStream.seekg(0, std::ios::end);
	std::streamsize fileSize = fileStream.tellg();

	char* text = new char[fileSize];

	fileStream.close();
	fileStream.open(argv, std::ios::in | std::ios::binary);
	fileStream.read(text, fileSize);
	fileStream.clear();
	fileStream.close();

	fileStream.open(argv, std::ios::out | std::ios::binary);
	CheckingForFileOpening(fileStream);

	fileStream.write(text, *choice);

	do
	{
		(*choice)++;
		if (text[*choice] == ' ' || text[*choice] == '\n')
		{
			fileStream.write(text + *choice, fileSize - *choice);
			break;
		}
	} while (text[*choice] != '\0');

	std::cout << "Your file has been changed. I will close it.\n";
	delete[] text;
}