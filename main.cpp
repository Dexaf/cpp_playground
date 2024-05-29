#include "utils.h"
#include "tree.h"
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

	std::cout << "File loaded! What do you want to do?" << '\n';

	int choice{ -1 };

	do {
		std::cout
			<< std::endl
			<< "(0) exit" << '\n'
			<< "(1) order files by name" << '\n'
			<< "(2) order files by code" << '\n'
			<< "(3) order files by quantity" << '\n'
			<< "(4) order files by price" << '\n';

		const std::vector validChoices{ 0, 1, 2, 3, 4 };

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

		std::unique_ptr<TreeNode<storageItemSpace::storageItem>> treeRootPntr = nullptr;

		//assegnare dinamicamente??
		switch (choice)
		{
		case 0:
			continue;
			break;
		case 1:
			treeRootPntr = std::move(makeTreeFromVect(storageItems.getData(), &storageItemSpace::storageItem::name));
			break;
		case 2:
			treeRootPntr = std::move(makeTreeFromVect(storageItems.getData(), &storageItemSpace::storageItem::code));
			break;
		case 3:
			treeRootPntr = std::move(makeTreeFromVect(storageItems.getData(), &storageItemSpace::storageItem::qta));
			break;
		case 4:
			treeRootPntr = std::move(makeTreeFromVect(storageItems.getData(), &storageItemSpace::storageItem::price));
			break;
		}

		//print table layout
		// Set the width for each column
		constexpr int nameWidth{ 30 };
		constexpr int codeWidth{ 30 };
		constexpr int qtaWidth{ 15 };
		constexpr int priceWidth{ 10 };

		// Print header
		//stdleft aligns data, setw gives a "column space"
		std::cout << std::left << std::setw(nameWidth) << "Name"
			<< std::setw(codeWidth) << "Code"
			<< std::setw(qtaWidth) << "Quantity"
			<< std::setw(priceWidth) << "Price"
			<< '\n';

		// Print a separator
		std::cout << std::string(nameWidth - 1, '-') << " "
			<< std::string(codeWidth - 1, '-') << " "
			<< std::string(qtaWidth - 1, '-') << " "
			<< std::string(priceWidth, '-')
			<< '\n';

		TreeNode<storageItemSpace::storageItem>::orderedPrint(treeRootPntr.get());

		std::cout << '\n' << "want to do something else?";
	} while (choice != 0);
}