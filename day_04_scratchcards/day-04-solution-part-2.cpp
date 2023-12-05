#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
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
	offset = -1;
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

	int winnerMatches = 0;

	for (auto number : numbers)
	{
		if (find(winningNumbers.begin(), winningNumbers.end(), number) != winningNumbers.end())
		{
			++winnerMatches;
		}
	}
	return winnerMatches;
}

int main()
{
	ifstream infile("input.txt");
	if (infile.is_open())
	{
		string line;
		int totalCards = 0;
		map<int, pair<int, int>> cardsToPointsAndCount;
		while (getline(infile, line))
		{
			int cursor = 0;
			int gameNumber = stoi(FirstNumberString(line, cursor));
			cardsToPointsAndCount[gameNumber] = {GetPointsOfCard(line), 1};
		}

		for (auto cardWithWinning : cardsToPointsAndCount)
		{
			int cardNumber = cardWithWinning.first;
			int cardPoints = cardWithWinning.second.first;
			int cardCount = cardWithWinning.second.second;
			for (int i = 1; i <= cardPoints; ++i)
			{
				if (cardNumber + i > cardsToPointsAndCount.size())
					break;
				cardsToPointsAndCount[cardNumber + i].second += cardCount;
			}
			totalCards += cardCount;
		}

		cout << totalCards << endl;
		infile.close();
	}
}