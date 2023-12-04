#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

bool IsStarCharacter(char const &c)
{
	return !isdigit(c) && c != '.';
}

bool HasSurroundingSpecialCharacters(string const &fileString, int const &numberOfLines, int const &lineLength, int const &position)
{
	int currentLine = position / lineLength;
	int previousLine = floor((float(position) - float(lineLength)) / float(lineLength));
	int nextLine = (position + lineLength) / lineLength;
	int positionInLine = position - currentLine * lineLength;
	bool isAtLeftEdge = positionInLine == 0;
	bool isAtRightEdge = positionInLine == lineLength;
	if (!isAtLeftEdge && IsStarCharacter(fileString[position - 1]))
	{
		return true;
	}
	if (!isAtRightEdge != lineLength && IsStarCharacter(fileString[position + 1]))
	{
		return true;
	}
	if (previousLine != -1)
	{
		bool specialAbove = false;
		specialAbove = IsStarCharacter(fileString[position - lineLength]);
		if (!isAtLeftEdge && !specialAbove)
		{
			specialAbove = IsStarCharacter(fileString[position - 1 - lineLength]);
		}
		if (!isAtRightEdge && !specialAbove)
		{
			specialAbove = IsStarCharacter(fileString[position + 1 - lineLength]);
		}
		if (specialAbove)
			return true;
	}
	if (nextLine != numberOfLines)
	{
		bool specialBelow = false;
		specialBelow = IsStarCharacter(fileString[position + lineLength]);
		if (!isAtLeftEdge && !specialBelow)
		{
			specialBelow = IsStarCharacter(fileString[position - 1 + lineLength]);
		}
		if (!isAtRightEdge && !specialBelow)
		{
			specialBelow = IsStarCharacter(fileString[position + 1 + lineLength]);
		}
		if (specialBelow)
			return true;
	}
	return false;
}

int CalculateSumOfPartNumbers(string const &fileString, int const &numberOfLines, int const &lineLength)
{
	int sumOfPartNumbers = 0;

	int fileLength = fileString.size();
	int cursorPosition = 0;
	string partNumber = "";
	bool partNumberValid = false;
	for (auto character : fileString)
	{
		if (isdigit(fileString[cursorPosition]))
		{
			partNumber += fileString[cursorPosition];
			if (!partNumberValid)
				partNumberValid = HasSurroundingSpecialCharacters(fileString, numberOfLines, lineLength, cursorPosition);
		}
		else if (partNumber != "" && partNumberValid)
		{
			sumOfPartNumbers += stoi(partNumber);
			partNumber = "";
			partNumberValid = false;
		}
		else
		{
			partNumber = "";
			partNumberValid = false;
		}
		++cursorPosition;
	}

	return sumOfPartNumbers;
}

int main()
{
	ifstream infile("input.txt");
	if (infile.is_open())
	{
		int sumOfPartNumbers;
		string line;
		int numberOfLines = 0;
		while (getline(infile, line))
		{
			++numberOfLines;
		}
		int lineLength = line.size();
		infile.clear();
		infile.seekg(0);
		string fileString;
		fileString.reserve(infile.tellg());
		infile.seekg(0, std::ios::beg);

		fileString.assign((std::istreambuf_iterator<char>(infile)),
						  std::istreambuf_iterator<char>());

		fileString.erase(remove(fileString.begin(), fileString.end(), '\n'), fileString.cend());

		sumOfPartNumbers = CalculateSumOfPartNumbers(fileString, numberOfLines, lineLength);
		cout << sumOfPartNumbers << endl;
		cout << numberOfLines << endl;
		cout << lineLength << endl;
	}
}
