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

long long StrategiesForRace(long long raceTime, long long raceRecord){
    long long winningStrategies = 0;
    for (long i = 0; i < raceTime; ++i){
        long long remainingTime = raceTime - i;
        if(remainingTime * i > raceRecord){
            ++winningStrategies;
        }
    }
    return winningStrategies;
}

int main()
{
	ifstream infile("input.txt");
	if (infile.is_open())
	{
		string line;
		// Get the seed values in the first line
		getline(infile, line);
		vector<long long> raceTimes = GetNumbersInLine(line);
		getline(infile, line);
		vector<long long> raceRecords = GetNumbersInLine(line);
        long long longRaceTime = 0;
        long long longRaceRecord = 0;
        for(int i=0; i < raceTimes.size(); ++i )
        {
            int timeTenners = 1;
            while((int) raceTimes[i] / pow(10,timeTenners) > 10){
                ++timeTenners;
            }
            int recordTenners = 1;
            while((int) raceRecords[i] / pow(10,recordTenners) > 10){
                ++recordTenners;
            }
            longRaceTime *= pow(10, timeTenners + 1);
            longRaceRecord *= pow(10, recordTenners + 1);
            longRaceTime += raceTimes[i];
            longRaceRecord += raceRecords[i];
        }
		long long winningStrategies = StrategiesForRace(longRaceTime, longRaceRecord);
        
		cout << winningStrategies << endl;
		infile.close();
	}
}