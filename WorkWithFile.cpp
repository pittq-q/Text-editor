#include "WorkWithFile.h"

void CheckingTheCommandSpelling(const int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "You didn't enter file for editing!";
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

void ReadingFile(char* argv, std::fstream& fileStream)
{
	if (fileStream.is_open())
	{
		fileStream.close();
	}
	fileStream.open(argv, std::ios::in);
	char character;
	std::cout << "\nHere is the new file content:\n"
		<< "\n--------------------------\n";
	while (fileStream.get(character))
	{
		std::cout << character;
	}
	std::cout << "\n--------------------------\n";
	fileStream.clear();
}

char* WritingYourText(int choice, std::fstream& fileStream)
{
	std::cout << "Choose a size of your text: ";

	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	std::cout << "Now, you can write (Double \"enter\" for completion (max - 5): \n";
	char* line = new char[choice]();
	char* fullNewText = new char[choice * 5]();
	do
	{
		std::cin.getline(line, choice);
		if (line[0] == '\0')
		{
			break;
		}
		strcat_s(fullNewText, choice * 5, line);
		strcat_s(fullNewText, choice * 5, "\n");
		memset(line, 0, choice);
	} while (true);

	std::cout << "Your file has been changed.\n";

	delete[] line;
	return fullNewText;
	delete[] fullNewText;
}

void StartWritingATextFromTheEnd(int* choice, std::fstream& fileStream)
{
	fileStream.seekp(0, std::ios::end);
	fileStream << WritingYourText(*choice, fileStream);
}

void StartWritingATextFromSpecificPoint(int* choice, char* argv, std::fstream& fileStream)
{
	std::cout << "Enter the position you want to do from (start from 0): ";
	std::cin >> *choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	fileStream.seekg(0, std::ios::end);
	std::streamsize fileSize = fileStream.tellg();

	if (*choice >= fileSize) {
		std::cerr << "Error: Choice is out of file bounds.\n";
		return;
	}

	char* fileText = new char[fileSize + 1]();

	fileStream.close();
	fileStream.open(argv, std::ios::in | std::ios::binary);
	CheckingForFileOpening(fileStream);
	fileStream.read(fileText, fileSize);
	fileStream.clear();
	fileText[fileSize] = '\0';
	fileStream.close();

	fileStream.open(argv, std::ios::out | std::ios::binary);
	CheckingForFileOpening(fileStream);

	int count = 0;
	for (size_t i = 0; i < *choice + 1; i++)
	{
		if (fileText[i] == '\r')
		{
			count += 2;
		}
	}

	for (size_t i = *choice + 1; i < *choice + count; i++)
	{
		if (fileText[i] == '\r')
		{
			count += 2;
		}
	}
	*choice += count;

	if (fileText[*choice] == '\n')
	{
		*choice += 1;
	}
	else if (fileText[*choice] == '\r')
	{
		*choice += 2;
	}

	fileStream.write(fileText, *choice);
	char* userText = WritingYourText(*choice, fileStream);
	fileStream.write(userText, strlen(userText));
	fileStream.write(fileText + *choice, fileSize - *choice);
}

void DeleteSomeCharacterFromFile(int* choice, const char* argv, std::fstream& fileStream)
{
	std::cout << "Enter the position of the character you want to delete (start from 0): ";
	std::cin >> *choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	fileStream.seekg(0, std::ios::end);
	std::streamsize fileSize = fileStream.tellg();

	if (*choice >= fileSize) {
		std::cerr << "Error: Choice is out of file bounds.\n";
		return;
	}

	char* fileText = new char[fileSize + 1]();

	fileStream.close();
	fileStream.open(argv, std::ios::in | std::ios::binary);
	CheckingForFileOpening(fileStream);
	fileStream.read(fileText, fileSize);
	fileStream.clear();
	fileText[fileSize] = '\0';
	fileStream.close();

	fileStream.open(argv, std::ios::out | std::ios::binary);
	CheckingForFileOpening(fileStream);

	int count = 0;
	for (size_t i = 0; i < *choice; i++)
	{
		if (fileText[i] == '\r')
		{
			count += 2;
		}
	}

	for (size_t i = *choice; i < *choice + count; i++)
	{
		if (fileText[i] == '\r')
		{
			count += 2;
		}
	}
	*choice += count;

	if (fileText[*choice] == '\n')
	{
		*choice += 1;
	}
	else if (fileText[*choice] == '\r')
	{
		*choice += 2;
	}

	fileStream.write(fileText, *choice);

	fileStream.write(fileText + *choice + 1, fileSize - *choice - 1);

	std::cout << "Your file has been changed.\n";
	delete[] fileText;
}

void DeleteSomeWordFromFile(int* choice, const char* argv, std::fstream& fileStream)
{
	std::cout << "Enter the position of the word you want to delete (start from 0): ";
	std::cin >> *choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	fileStream.seekg(0, std::ios::end);
	std::streamsize fileSize = fileStream.tellg();

	if (*choice >= fileSize) {
		std::cerr << "Error: Choice is out of file bounds.\n";
		return;
	}

	char* fileText = new char[fileSize + 1]();

	fileStream.close();

	fileStream.open(argv, std::ios::in | std::ios::binary);
	CheckingForFileOpening(fileStream);

	fileStream.read(fileText, fileSize);
	fileStream.clear();
	fileText[fileSize] = '\0';
	fileStream.close();

	fileStream.open(argv, std::ios::out | std::ios::binary);
	CheckingForFileOpening(fileStream);

	int count = 0;
	for (size_t i = 0; i < *choice; i++)
	{
		if (fileText[i] == '\r')
		{
			count += 2;
		}
	}

	for (size_t i = *choice; i < *choice + count; i++)
	{
		if (fileText[i] == '\r')
		{
			count += 2;
		}
	}
	*choice += count;

	if (fileText[*choice] == '\n')
	{
		*choice += 1;
	}
	else if (fileText[*choice] == '\r')
	{
		*choice += 2;
	}
	fileStream.write(fileText, *choice);

	do
	{
		(*choice)++;
		if (fileText[*choice] == ' ' || fileText[*choice] == '\n')
		{
			fileStream.write(fileText + *choice, fileSize - *choice);
			break;
		}
	} while (fileText[*choice] != '\0');

	std::cout << "Your file has been changed.\n";
	delete[] fileText;
}