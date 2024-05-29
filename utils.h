#ifndef UTILS
#define UTILS

#include <vector>
#include <iostream>
#include "storageItem.h"

std::vector<storageItemSpace::storageItem> loadStorageItemsFromFile(std::istream& file);

bool isValidChoice(const std::vector<int>& validChoices, const int& choice);

template <typename T>
bool isBiggerThen(T& param1, T& param2) {
	return param1 > param2;
}

using stringFromClass = std::basic_string<char, struct std::char_traits<char>, class std::allocator<char> >;

bool isBiggerThen(const stringFromClass& param1, const stringFromClass& param2);

#endif // !UTILS