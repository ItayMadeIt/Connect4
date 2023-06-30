#include "Helper.h"


void Helper::PrintBoard(bitset<42> b)
{
	for (int rank = 5; rank >= 0; --rank) {
		for (int file = 0; file < 7; ++file) {
			int bitPosition = rank * 7 + file;
			bitset<42> mask = 1ULL << bitPosition;
			bool isSet = (b & mask) != 0;
			cout << (isSet ? "1 " : "0 ") << " ";
		}
		cout << std::endl;
	}
	cout << std::endl;
}

void Helper::PrintBoard(State<7, 6> state)
{
	for (int rank = 5; rank >= 0; --rank) {
		for (int file = 0; file < 7; ++file) {
			int bitPosition = rank * 7 + file;
			if (state.board.test(bitPosition)){
				if (state.blue.test(bitPosition))
					cout << "B ";
				if (state.red.test(bitPosition))
					cout << "R ";
			}
			else {
				cout << "U ";
			}
		}
		cout << std::endl;
	}
	cout << std::endl;
}

vector<bitset<42>> Helper::fileMasks = {};
vector<bitset<42>> Helper::FileMasks()
{
	if (fileMasks.empty()) {
		// Six times
		bitset<42> aFile = 1ul << 7 * 0 | 1ul << 7 * 1 | 1ul << 7 * 2 | 1ul << 7 * 3 | 1ul << 7 * 4 | 1ull<< 7 * 5;

		for (size_t i = 0; i < 7; i++)
		{
			fileMasks.push_back(aFile << i);
		}
	}

	return fileMasks;
}


vector<bitset<42>> Helper::horizontalWins = {};
vector<bitset<42>> Helper::HorizontalWins()
{

	if (horizontalWins.empty()) {
		bitset<42> basicLine = 0;

		for (size_t j = 0; j < 6; j++)
		{
			if (j == 0)
				basicLine = 1ull << 0 | 1ull << 1 | 1ull << 2 | 1ull << 3;
			else
				basicLine = basicLine << 4;
			horizontalWins.push_back(basicLine);

			for (size_t i = 0; i < 3; i++)
			{
				basicLine = basicLine << 1;
				horizontalWins.push_back(basicLine);
			}
		}

	}

	return horizontalWins;
}

vector<bitset<42>> Helper::verticalWins = {};
vector<bitset<42>> Helper::VerticalWins()
{
	if (verticalWins.empty()) {

		bitset<42> basicLine = 0;

		for (size_t j = 0; j < 2; j++)
		{
			if (j == 0) 
				basicLine = 1ull << 7 * 0 | 1ull << 7 * 1 | 1ull << 7 * 2 | 1ull << 7 * 3;
			else 
				basicLine = basicLine << 1;
			
			verticalWins.push_back(basicLine);
			
			
			for (size_t i = 0; i < 7; i++) {
				basicLine = basicLine << 1;
				verticalWins.push_back(basicLine);
			}
		}
	}

	return verticalWins;
}

vector<bitset<42>> Helper::uprightWins = {};
vector<bitset<42>> Helper::UprightWins()
{
	if (uprightWins.empty()) {

		bitset<42> basicLine = 0;

		for (size_t j = 0; j < 3; j++)
		{
			if (j == 0)
				basicLine = 1ull << (1 + 7) * 0 | 1ull << (1 + 7) * 1 | 1ull << (1 + 7) * 2 | 1ull << (1 + 7) * 3;
			else
				basicLine = basicLine << 4;
			uprightWins.push_back(basicLine);

			for (size_t i = 0; i < 3; i++)
			{
				basicLine = basicLine << 1;
				uprightWins.push_back(basicLine);
			}
		}
	}

	return uprightWins;
}

vector<bitset<42>> Helper::downrightWins = {};
vector<bitset<42>> Helper::DownrightWins()
{
	if (downrightWins.empty()) {

		bitset<42> basicLine = 0;

		for (size_t j = 0; j < 3; j++)
		{
			if (j == 0)
				basicLine = 1ull << (41 - 6) - (7-1) * 0 | 1ull << (41 - 6) - (7-1) * 1 | 1ull << (41 - 6) - (7-1) * 2 | 1ull << (41 - 6) - ( 7-1) * 3;
			else
				basicLine = (basicLine >> 7) >> 3;
			downrightWins.push_back(basicLine);

			for (size_t i = 0; i < 3; i++)
			{
				basicLine = basicLine << 1;
				downrightWins.push_back(basicLine);
			}
		}
	}

	return downrightWins;
}
