#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "You didn't entered file for editing!";
		return 1;
	}

	if (argc > 2)
	{
		std::cout << "You entered too many arguments!";
		return 1;
	}
	
	int count = 0;
	while (argv[1][count] != '.')
	{
		if (argv[1][count] == '\0')
		{
			std::cout << "Your file doesn't have extension!";
			return 1;
		}
		count++;
	}


}