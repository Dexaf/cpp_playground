#include "utils.h"
#include "constants.h"
#include "storageItem.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
	std::cout << "Loading data file..." << '\n';

	std::ifstream file{ "data.txt", std::ios::out };
	storageItemSpace::StorageItemContainer storageItems{};
	try {
		storageItems = loadStorageItemsFromFile(file);
	}
	catch (std::runtime_error exc) {
		std::cerr << exc.what() << '\n';
	}
	catch (...) {
		std::cerr << "SOMETHING WENT WRONG";
	}

	std::cout
		<< "File loaded! What do you want to do?" << '\n'
		<< "(1) order files by name" << '\n'
		<< "(2) order files by code" << '\n'
		<< "(3) order files by quantity" << '\n'
		<< "(4) order files by price" << '\n';

	int choice{};
	const std::vector validChoices{ 1, 2, 3, 4 };

	while (true) {
		std::cin >> choice;
		if (std::cin.good() && isValidChoice(validChoices, choice)) {
			std::cin.clear();
			break;
		}
		else {
			std::cout << "insert the number corresponding to the needed action please" << '\n';
			//clean the flags
			std::cin.clear();
			//clean the stream
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	storageItems.printStorageItems();
}