#include <vector>
#include "storageItem.h"

#ifndef UTILS
#define UTILS
std::vector<storageItemSpace::storageItem> loadStorageItemsFromFile(std::istream& file);

bool isValidChoice(const std::vector<int>& validChoices, const int& choice);
#endif // !UTILS