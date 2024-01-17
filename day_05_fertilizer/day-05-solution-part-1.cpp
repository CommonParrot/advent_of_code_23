#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;

vector<long long> GetNumbersInLine(string line)
{
	vector<long long> containedNumbers;
	int firstDigitIndex = -1;
	int lastDigitIndex = -1;
	for (int i = 0; i < line.length(); i++)
	{
		int firstAsciiValue = (int)line.c_str()[i];
		if (57 >= firstAsciiValue && firstAsciiValue >= 48)
		{
			if (firstDigitIndex == -1)
			{
				firstDigitIndex = i;
			}
		}
		else if (firstDigitIndex != -1)
		{
			lastDigitIndex = i - 1;
		}
		if (i == line.length() - 1)
		{
			lastDigitIndex = i;
		}
		if (firstDigitIndex != -1 && lastDigitIndex != -1)
		{
			string numberString = line.substr(firstDigitIndex, lastDigitIndex - firstDigitIndex + 1);
			containedNumbers.push_back(stoll(numberString));
			firstDigitIndex = -1;
			lastDigitIndex = -1;
		}
	}
	return containedNumbers;
}

// Also detects some special characters
bool LineStartsWithLetter(string line)
{
	int firstValue = (int)line.c_str()[0];
	return firstValue >= 65 && firstValue <= 122;
}

bool LineStartsWithDigit(string line)
{
	int firstValue = (int)line.c_str()[0];
	return firstValue >= 48 && firstValue <= 57;
}

long long ApplyMappingToNumber(long long number, vector<long long> mapping)
{
	long long sourceBound = mapping[1];
	long long destinationBound = mapping[0];
	long long range = mapping[2];
	if (number < sourceBound)
	{
		return number;
	}
	if (number > sourceBound + range)
	{
		return number;
	}
	return (number - sourceBound) + destinationBound;
}

int main()
{
	ifstream infile("test-input.txt");
	if (infile.is_open())
	{
		string line;
		// Get the seed values in the first line
		getline(infile, line);
		vector<long long> seedNumbers = GetNumbersInLine(line);
		map<long long, long long> seedRanges;
		for (int i = 0; i < seedNumbers.size() - 1; i = i + 2)
		{
			seedRanges[seedNumbers[i]] = seedNumbers[i + 1];
		}
		vector<long long> locationNumbers = seedNumbers;
		vector<long long> intermediateNumbers = seedNumbers;
		vector<long long> currentMapping;
		bool newMapping = false;
		while (getline(infile, line))
		{
			if (LineStartsWithLetter(line))
			{
				locationNumbers = intermediateNumbers;
				continue;
			}
			if (LineStartsWithDigit(line))
			{
				currentMapping = GetNumbersInLine(line);
				for (int i = 0; i < intermediateNumbers.size(); i++)
				{
					if (intermediateNumbers[i] != locationNumbers[i])
					{
						continue;
					}
					long long mappedNumber = ApplyMappingToNumber(locationNumbers[i], currentMapping);
					if (mappedNumber != locationNumbers[i])
					{
						intermediateNumbers[i] = mappedNumber;
					}
				}
			}
		}
		locationNumbers = intermediateNumbers;

		cout << *min_element(locationNumbers.begin(), locationNumbers.end()) << endl;
		infile.close();
	}
}