#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	int choice = 0;

	if (argc < 2)
	{
		std::cerr << "You didn't entered file for editing!";
		return 1;
	}

	if (argc > 2)
	{
		std::cerr << "You entered too many arguments!";
		return 1;
	}
	
	int count = 0;
	while (argv[1][count] != '.')
	{
		if (argv[1][count] == '\0')
		{
			std::cerr << "Your file doesn't have extension!";
			return 1;
		}
		count++;
	}

	std::ifstream fileStreamin(argv[1]);
	if (!fileStreamin.is_open())
	{
		std::cerr << "This file does not exist. Do you want to create him? (1 - Yes, Another_key - No)\n";
		std::cin >> choice;
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

	std::ofstream fileStreamout(argv[1]);
	if (!fileStreamout.is_open())
	{
		std::cerr << "Couldn't open the file.\n";
		return 1;
	}

	std::cout << "What do you want to do?\n"
		<< "1 - Close file;\n"
		<< "2 - Start writing a text from the end;\n"
		<< "3 - Start writing a text from specific point;\n"
		<< "4 - Delete some character;\n"
		<< "5 - Delete some word;\n";
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		fileStreamout.close();
		return 0;
		break;

	case 2:
		std::ofstream fileStreamout(argv[1], std::ios::app);
		if (!fileStreamout.is_open())
		{
			std::cerr << "Couldn't open the file.\n";
			return 1;
		}
		
		std::cout << "!Warning: You can writing 1 line only (In next update, i will fix it)." << std::endl 
			<< "Choose a size of your text : ";

		std::cin >> choice;
		char* text = new char[choice];
		std::cin.getline(text, choice);

		for (size_t i = 0; i < choice; i++)
		{
			fileStreamout.put(text[i]);
		}
		std::cout << "Your text has been adding in file. I will close it.\n";

		fileStreamout.close();
		break;

	case 3:
		std::ofstream fileStreamout(argv[1]);
		if (!fileStreamout.is_open())
		{
			std::cerr << "Couldn't open the file.\n";
			return 1;
		}

		std::cout << "Enter the position you want to do from (start from 0): ";
		std::cin >> choice;
		fileStreamout.seekp(std::ios::beg, choice);


	default:
		std::cout << "You entered uncorrect choice. I will close your file :)\n";
		fileStreamout.close();
		break;
	}

	return 0;
}