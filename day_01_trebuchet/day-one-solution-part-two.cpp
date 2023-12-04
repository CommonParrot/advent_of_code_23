#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int getDigitFromString(string digitString)
{
	map<string, int> digits{{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};
	for (auto digit : digits)
	{
		// Edge case for twone at the start of a line
		if (digitString.find("twone") != string::npos)
		{
			return 2;
		}
		if (digitString.find(digit.first) != string::npos)
		{
			return digit.second;
		}
	}
	return 0;
}

int ReadCalibrationValue(string line)
{
	// List of all digits in the string
	vector<int> containedDigits;
	int firstDigit = 0;
	int lastDigit = 0;
	for (int i = 0; i < line.length(); i++)
	{
		int firstAsciiValue = (int)line.c_str()[i];
		int secondAsciiValue = 0;
		if (i < line.length() - 1)
		{
			secondAsciiValue = (int)line.c_str()[i + 1];
		}
		// If the first character is already a digit, add to the list
		if (57 >= firstAsciiValue && firstAsciiValue >= 48)
		{
			containedDigits.push_back(firstAsciiValue - 48);
		}
		// Also check the second character
		else if (57 >= secondAsciiValue && secondAsciiValue >= 48)
		{
			containedDigits.push_back(secondAsciiValue - 48);
		}
		// Look for a spelled out digit in the next five characters
		else
		{
			int digit = getDigitFromString(line.substr(i, 5));
			if (digit != 0)
			{
				containedDigits.push_back(digit);
			}
		}
	}
	if (containedDigits.size() > 0)
	{
		firstDigit = containedDigits[0];
		lastDigit = containedDigits[containedDigits.size() - 1];
	}
	cout << firstDigit * 10 + lastDigit << endl;
	return firstDigit * 10 + lastDigit;
}

int main()
{
	ifstream infile("input.txt");
	if (infile.is_open())
	{
		string line;
		int calibrationValueSum = 0;
		while (getline(infile, line))
		{
			calibrationValueSum += ReadCalibrationValue(line);
		}
		cout << calibrationValueSum << endl;
		infile.close();
	}
}
