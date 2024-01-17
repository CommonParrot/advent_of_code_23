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

map<long long, pair<bool, long long>> ApplyMappingToRange(pair<long long, long long> range, vector<long long> mapping)
{
	long long mappingStart = mapping[1];
	long long mappingDestination = mapping[0];
	long long mappingRange = mapping[2];
	long long mappingEnd = mappingStart + mappingRange;

	long long inputStart = range.first;
	long long inputRange = range.second;
	long long inputEnd = inputStart + inputRange;

	map<long long, pair<bool, long long>> mappedRanges;
	mappedRanges[inputStart] = {false, inputRange};

	if (inputEnd < mappingStart)
	{
		return mappedRanges;
	}
	if (inputStart > mappingEnd)
	{
		return mappedRanges;
	}
	if (mappingStart <= inputStart && mappingEnd >= inputEnd)
	{
		mappedRanges.clear();
		long long mappedStart = (inputStart - mappingStart) + mappingDestination;
		mappedRanges[mappedStart] = {true, inputRange};
	}
	else if (inputStart < mappingStart && inputEnd <= mappingEnd)
	{
		mappedRanges.clear();
		long long frontRange = mappingStart - inputStart;
		long long mappedStart = mappingDestination;
		mappedRanges[mappedStart] = {true, inputRange - frontRange};
		mappedRanges[inputStart] = {false, frontRange};
	}
	else if (mappingStart <= inputStart && mappingEnd < inputEnd)
	{
		mappedRanges.clear();
		long long endRange = inputEnd - mappingEnd;
		long long mappedStart = (inputStart - mappingStart) + mappingDestination;
		mappedRanges[mappedStart] = {true, inputRange - endRange};
		mappedRanges[mappingEnd] = {false, endRange};
	}
	else if (inputStart < mappingStart && mappingEnd < inputEnd)
	{
		mappedRanges.clear();
		long long frontRange = mappingStart - inputStart;
		long long endRange = inputEnd - mappingEnd;
		long long mappedStart = mappingDestination;
		mappedRanges[mappedStart] = {true, (inputRange - endRange) - frontRange};
		mappedRanges[mappingEnd] = {false, endRange};
		mappedRanges[inputStart] = {false, frontRange};
	}
	return mappedRanges;
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
		// This is the first seed in the range as a key for the range value and if this range has been
		// affected by a mapping
		map<long long, pair<bool, long long>> sourceRanges;
		for (int i = 0; i < seedNumbers.size() - 1; i = i + 2)
		{
			sourceRanges[seedNumbers[i]] = {false, seedNumbers[i + 1]};
		}
		map<long long, pair<bool, long long>> locationRanges = sourceRanges;
		vector<long long> currentMapping;
		while (getline(infile, line))
		{
			// Reset the flag that a seed was mapped, when new mapping arrives
			if (LineStartsWithLetter(line))
			{
				for (auto locationRange : locationRanges)
				{
					locationRanges[locationRange.first] = {false, locationRange.second.second};
				}
				continue;
			}
			// Read and apply the new mapping
			if (LineStartsWithDigit(line))
			{
				currentMapping = GetNumbersInLine(line);
				sourceRanges = locationRanges;
				for (auto sourceRange : sourceRanges)
				{
					if (sourceRange.second.first)
						continue;
					map<long long, pair<bool, long long>> mappedRanges = ApplyMappingToRange({sourceRange.first, sourceRange.second.second}, currentMapping);
					locationRanges.erase(sourceRange.first);
					for (auto mappedRange : mappedRanges)
					{
						long long newRange = mappedRange.second.second;
						if (locationRanges.count(mappedRange.first) == 0 || locationRanges[mappedRange.first].second < newRange)
						{
							locationRanges[mappedRange.first] = mappedRange.second;
						}
					}
				}
			}
		}
		long long minLocationRange = (*min_element(locationRanges.begin(), locationRanges.end())).first;

		cout << minLocationRange << endl;
		infile.close();
	}
}