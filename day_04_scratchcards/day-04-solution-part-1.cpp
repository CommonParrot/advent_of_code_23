#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

string FirstNumberString(string const &str, int &offset)
{
	char const *digits = "0123456789";
	size_t const n = str.find_first_of(digits, offset);
	if (n != string::npos)
	{
		size_t const m = str.find_first_not_of(digits, n);
		offset = m;
		return str.substr(n, m != string::npos ? m - n : m);
	}
	offset = string::npos;
	return string();
}

int GetPointsOfCard(string const &card)
{
	char resultSeparator = '|';
	char beginSeparator = ':';

	int cardBegin = card.find(beginSeparator);
	int resultBegin = card.find(resultSeparator);

	vector<int> numbers;
	vector<int> winningNumbers;

	int cursor = cardBegin + 1;

	while (cursor < resultBegin - 2)
	{
		// FirstNumberString changes the cursor position!
		winningNumbers.push_back(stoi(FirstNumberString(card, cursor)));
	}
	while (cursor != string::npos)
	{
		numbers.push_back(stoi(FirstNumberString(card, cursor)));
	}

	int points = 0;

	for (auto number : numbers)
	{
		if (find(winningNumbers.begin(), winningNumbers.end(), number) != winningNumbers.end())
		{
			points = max(1, points * 2);
		}
	}
	return points;
}

int main()
{
	ifstream infile("input.txt");
	if (infile.is_open())
	{
		string line;
		int sumOfPoints = 0;
		while (getline(infile, line))
		{
			int cursor = 0;
			int gameNumber = stoi(FirstNumberString(line, cursor));
			sumOfPoints += GetPointsOfCard(line);
		}
		cout << sumOfPoints << endl;
		infile.close();
	}
}