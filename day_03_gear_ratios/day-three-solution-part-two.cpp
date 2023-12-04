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
	return c == '*';
}

pair<bool, int> HasSuroundingStarCharacter(string const &fileString, int const &numberOfLines, int const &lineLength, int const &position)
{
	int currentLine = position / lineLength;
	int previousLine = floor((float(position) - float(lineLength)) / float(lineLength));
	int nextLine = (position + lineLength) / lineLength;
	int positionInLine = position - currentLine * lineLength;
	bool isAtLeftEdge = positionInLine == 0;
	bool isAtRightEdge = positionInLine == lineLength;
	if (!isAtLeftEdge && IsStarCharacter(fileString[position - 1]))
	{
		return {true, position - 1};
	}
	if (!isAtRightEdge != lineLength && IsStarCharacter(fileString[position + 1]))
	{
		return {true, position + 1};
	}
	if (previousLine != -1)
	{
		if (IsStarCharacter(fileString[position - lineLength]))
		{
			return {true, position - lineLength};
		}
		if (!isAtLeftEdge && IsStarCharacter(fileString[position - 1 - lineLength]))
		{
			return {true, position - 1 - lineLength};
		}
		if (!isAtRightEdge && IsStarCharacter(fileString[position + 1 - lineLength]))
		{
			return {true, position + 1 - lineLength};
		}
	}
	if (nextLine != numberOfLines)
	{
		if (IsStarCharacter(fileString[position + lineLength]))
		{
			return {true, position + lineLength};
		}
		if (!isAtLeftEdge && IsStarCharacter(fileString[position - 1 + lineLength]))
		{
			return {true, position - 1 + lineLength};
		}
		if (!isAtRightEdge && IsStarCharacter(fileString[position + 1 + lineLength]))
		{
			return {true, position + 1 + lineLength};
		}
	}
	return {false, 0};
}

int CalculateSumOfPartNumbers(string const &fileString, int const &numberOfLines, int const &lineLength)
{
	int fileLength = fileString.size();
	int cursorPosition = 0;
	string gearNumber = "";
	pair<bool, int> isGearWithPosition;
	map<int, pair<int, int>> gearToRatioMap;
	for (auto character : fileString)
	{
		if (isdigit(fileString[cursorPosition]))
		{
			gearNumber += fileString[cursorPosition];
			if (!isGearWithPosition.first)
				isGearWithPosition = HasSuroundingStarCharacter(fileString, numberOfLines, lineLength, cursorPosition);
		}
		else if (gearNumber != "" && isGearWithPosition.first)
		{
			if (gearToRatioMap.find(isGearWithPosition.second) == gearToRatioMap.end())
			{
				gearToRatioMap[isGearWithPosition.second] = {1, stoi(gearNumber)};
			}
			else
			{
				int gearCount = gearToRatioMap[isGearWithPosition.second].first;
				int storedGearNumber = gearToRatioMap[isGearWithPosition.second].second;
				gearToRatioMap[isGearWithPosition.second] = {++gearCount, stoi(gearNumber) * storedGearNumber};
			}
			gearNumber = "";
			isGearWithPosition = {false, 0};
		}
		else
		{
			gearNumber = "";
			isGearWithPosition = {false, 0};
		}
		++cursorPosition;
	}

	int totalGearRatio = 0;

	for (auto gearRatio : gearToRatioMap)
	{
		if (gearRatio.second.first == 2)
		{
			totalGearRatio += gearRatio.second.second;
		}
	}

	return totalGearRatio;
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
		infile.seekg(0, ios::beg);
		string fileString;

		fileString.assign((istreambuf_iterator<char>(infile)),
						  istreambuf_iterator<char>());

		fileString.erase(remove(fileString.begin(), fileString.end(), '\n'), fileString.cend());

		sumOfPartNumbers = CalculateSumOfPartNumbers(fileString, numberOfLines, lineLength);
		cout << sumOfPartNumbers << endl;
		cout << numberOfLines << endl;
		cout << lineLength << endl;
	}
}
