#include "utils.h"
#include "constants.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>
/*
Check if the file exists and it's valid (every row has 4 values)
while loading file.
if the file is invalid we throw error
*/
std::vector<storageItemSpace::storageItem> loadStorageItemsFromFile(std::istream& file) {
	std::vector<storageItemSpace::storageItem> data{};

	if (!file) {
		throw std::runtime_error{ "UNABLE TO OPEN FILE" };
	}

	std::string stringFromFile{};
	int dataInCurrRow{ 0 };
	int currentLine{ 1 };
	storageItemSpace::storageItem storageItem{};
	//reading line to line inside of file
	while (file >> stringFromFile) {
		++dataInCurrRow;
		if (dataInCurrRow > 4) {
			throw std::runtime_error{ "ROW " + std::to_string(currentLine) + " HAVE TOO MUCH DATA (SHOULD BE " + std::to_string(constants::DATA_PER_ROW) + " ELEMENTS)" };
		}

		switch (dataInCurrRow)
		{
			//name
		case 1:
			storageItem.name = stringFromFile;
			break;
			//code
		case 2:
			storageItem.code = stringFromFile;
			break;
			//qta
		case 3:
			try {
				storageItem.qta = std::stoi(stringFromFile);
			}
			catch (...) {
				throw std::runtime_error{ "ROW " + std::to_string(currentLine) + " ERROR WHILE CONVERTING QTA" };
			}
			break;
			//price
		case 4:
			try {
				storageItem.price = std::stod(stringFromFile);
			}
			catch (...) {
				throw std::runtime_error{ "ROW " + std::to_string(currentLine) + " ERROR WHILE CONVERTING PRICE" };
			}
			break;
		}

		int filePeek{ file.peek() };
		if (filePeek == '\n' || filePeek == EOF) {
			//uh oh not enough data
			if (dataInCurrRow != constants::DATA_PER_ROW) {
				throw std::runtime_error{ "ROW " + std::to_string(currentLine) + " DOESN'T HAVE ENOUGH DATA (SHOULD BE " + std::to_string(constants::DATA_PER_ROW) + " ELEMENTS)" };
			}
			//we go to new line and reset the counter
			++currentLine;
			dataInCurrRow = 0;
			data.push_back(storageItem);
		}
	}
	return data;
}

bool isValidChoice(const std::vector<int>& validChoices, const int& choice) {
	//for (const auto& vc : validChoices) {
	//	if (vc == choice) {
	//		return true;
	//	}
	//}

	//return false;

	//this is the "smart" alternative
	//we iterate from begin() [pointer from first elem]
	//to end() [pointer one pos after last elem]
	//to find choice, if not found we get .end() hence false [as per !=]
	return std::find(validChoices.begin(), validChoices.end(), choice) != validChoices.end();
}

using stringFromClass = std::basic_string<char, struct std::char_traits<char>, class std::allocator<char> >;

bool isBiggerThen(const stringFromClass& param1, const stringFromClass& param2) {
	return param1.compare(param2) > 0;
}