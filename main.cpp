#include "WorkWithFile.h"

int main(int argc, char* argv[])
{
	int *choice = new int();
	CheckingTheCommandSpelling(argc, argv);

	std::fstream fileStream(argv[1], std::ios::in | std::ios::out);
	if (!fileStream.is_open())
	{
		std::cerr << "This file does not exist. Do you want to create him? (1 - Yes, Another_key - No)\n";
		std::cin >> *choice;
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');
		if (*choice != 1)
		{
			std::remove(argv[1]);
			fileStream.close();
			return 0;
		}
	}

	system("cls");
	char character;
	std::cout << "Here is the file content:\n"
		<< "\n--------------------------\n";
	while (fileStream.get(character))
	{
		std::cout << character;
	}
	std::cout << "\n--------------------------\n";
	fileStream.clear();

	std::cout << "\nWhat do you want to do?\n"
		<< "1 - Close file;\n"
		<< "2 - Start writing a text from the end;\n"
		<< "3 - Start writing a text from specific point;\n"
		<< "4 - Delete some character;\n"
		<< "5 - Delete some word; (Does the same as option 4 for now)\n";
	std::cin >> *choice;
	std::cin.clear();
	std::cin.ignore(LLONG_MAX, '\n');

	switch (*choice)
	{
	case 1:
		std::cout << "\n\nClosing...\n";
		fileStream.close();
		break;

	case 2: 
	{
		StartWritingATextFromTheEnd(choice, fileStream);
		ReadingFile(argv[1], fileStream);
		std::cout << "\n\nClosing...\n";
		fileStream.close();
		break;
	}
	case 3:
	{
		StartWritingATextFromSpecificPoint(choice, argv[1], fileStream);
		ReadingFile(argv[1], fileStream);
		std::cout << "\n\nClosing...\n";
		fileStream.close();
		break;
	}
	case 4:
	{
		DeleteSomeCharacterFromFile(choice, argv[1], fileStream);
		ReadingFile(argv[1], fileStream);
		std::cout << "\n\nClosing...\n";
		fileStream.close();
		break;
	}
	case 5:
	{
		DeleteSomeWordFromFile(choice, argv[1], fileStream);
		ReadingFile(argv[1], fileStream);
		std::cout << "\n\nClosing...\n";
		fileStream.close();
		break;
	}
	default:
		std::cout << "You entered uncorrect choice. I will close your file :)\n";
		fileStream.close();
		break;
	}

	return 0;
}