#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int ReadCalibrationValue(string line)
{
	int firstDigit = 0;
	int lastDigit = 0;
	// string lineFlipped = strrev(line);
	for (auto &character : line)
	{
		int asciiValue = (int)character;
		if (57 >= asciiValue && asciiValue >= 48)
		{
			firstDigit = asciiValue - 48;
			break;
		}
	}
	for (int i = line.length() - 1; i >= 0; i--)
	{
		int asciiValue = (int)line.c_str()[i];
		if (57 >= asciiValue && asciiValue >= 48)
		{
			lastDigit = asciiValue - 48;
			break;
		}
	}
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
