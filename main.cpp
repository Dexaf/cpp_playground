#include "utils.h"
#include "constants.h"
#include "storageItem.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
std::vector<storageItemSpace::storageItem> loadStorageItemsFromFile(std::istream& file);
int main() {
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
	storageItems.printStorageItems();
}