#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

string first_numberstring(string const &str)
{
	char const *digits = "0123456789";
	size_t const n = str.find_first_of(digits);
	if (n != string::npos)
	{
		size_t const m = str.find_first_not_of(digits, n);
		return str.substr(n, m != string::npos ? m - n : m);
	}
	return string();
}

map<string, int> ParsePull(string const &pull)
{
	map<string, int> coloredCubeMap;
	char const colorDelimiter = ',';
	size_t restPullStringLength = pull.size();
	for (int i = 0; i <= count(pull.begin(), pull.end(), colorDelimiter); i++)
	{
		size_t offset = pull.size() - restPullStringLength;
		size_t coloredCubeLength = pull.find_first_of(colorDelimiter, offset) - offset;
		string coloredCube = pull.substr(offset, coloredCubeLength);
		if (coloredCube.find("red") != string::npos)
		{
			coloredCubeMap["red"] = stoi(first_numberstring(coloredCube));
		}
		if (coloredCube.find("green") != string::npos)
		{
			coloredCubeMap["green"] = stoi(first_numberstring(coloredCube));
		}
		if (coloredCube.find("blue") != string::npos)
		{
			coloredCubeMap["blue"] = stoi(first_numberstring(coloredCube));
		}
		restPullStringLength -= coloredCubeLength + 2;
	}
	return coloredCubeMap;
}

int CheckPossibleGame(string line, map<string, int> const &restrictionMap)
{
	int gameID = stoi(first_numberstring(line));
	char const gameBeginDelimiter = ':';
	char const pullDelimiter = ';';

	string const pullsString = line.substr(line.find(gameBeginDelimiter) + 2, line.size() - 1);
	cout << pullsString << endl;

	vector<string> pulls;
	size_t restPullsStringLength = pullsString.size();
	for (int i = 0; i <= count(pullsString.begin(), pullsString.end(), pullDelimiter); i++)
	{
		size_t offset = pullsString.size() - restPullsStringLength;
		size_t pullStringLength = pullsString.find_first_of(pullDelimiter, offset) - offset;
		pulls.push_back(pullsString.substr(offset, pullStringLength));
		restPullsStringLength -= pullStringLength + 2;
	}

	for (auto pull : pulls)
	{
		map<string, int> coloredCubeMap;
		coloredCubeMap = ParsePull(pull);
		for (auto restriction : restrictionMap)
		{
			if (coloredCubeMap[restriction.first] > restriction.second)
			{
				return 0;
			}
		}
	}
	return gameID;
}

int main()
{
	ifstream infile("input.txt");
	if (infile.is_open())
	{
		string line;
		int sumOfIDs = 0;
		map<string, int> restrictionMap{{"red", 12}, {"green", 13}, {"blue", 14}};
		while (getline(infile, line))
		{
			sumOfIDs += CheckPossibleGame(line, restrictionMap);
		}
		cout << sumOfIDs << endl;
		infile.close();
	}
}
