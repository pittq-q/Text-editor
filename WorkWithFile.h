#pragma once
#include <fstream>
#include <iostream>

void CheckingTheCommandSpelling(const int argc, char* argv[]);

void CheckingForFileOpening(std::fstream& fileStream);

void ReadingFile(std::fstream& fileStream);

void WritingIntoFile(int SIZE, std::fstream& fileStream);

void StartWritingATextFromTheEnd(int* choice, std::fstream& fileStream);

void StartWritingATextFromSpecificPoint(int* choice, std::fstream& fileStream);

void DeleteSomeCharacterFromFile(int* choice, const char* argv, std::fstream& fileStream);

void DeleteSomeWordFromFile(int* choice, const char* argv, std::fstream& fileStream);

