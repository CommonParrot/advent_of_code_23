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
		if (digitString.find(digit.first) != string::npos)
		{
			return digit.second;
		}
	}
	return 0;
}

int ReadCalibrationValue(string line)
{
	vector<int> containedDigits;
	int firstDigit = 0;
	int lastDigit = 0;
	// string lineFlipped = strrev(line);
	for (int i = 0; i < line.size(); i++)
	{
		int asciiValue = (int)line.c_str()[i];
		if (57 >= asciiValue && asciiValue >= 48)
		{
			containedDigits.push_back(asciiValue - 48);
		}
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
	return firstDigit * 10 + lastDigit;
}

int main()
{
	ifstream infile("input-part-two.txt");
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
