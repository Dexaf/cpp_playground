#include "storageItem.h"
#include <iostream>
#include <iomanip>

using namespace storageItemSpace;

//MOVE CTOR
StorageItemContainer::StorageItemContainer(std::vector<storageItemSpace::storageItem>&& data) :_data{ std::move(data) } {}
//MOVE ASSIGN
StorageItemContainer& StorageItemContainer::operator=(std::vector<storageItem>&& data) {
	this->_data = std::move(data);
	//to allow conc
	return *this;
}

//we use & for storageItems to pass the reference and not a copy
void StorageItemContainer::printStorageItems()
{
	// Set the width for each column
	const int nameWidth{ 30 };
	const int codeWidth{ 30 };
	const int qtaWidth{ 15 };
	const int priceWidth{ 10 };

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

	//we declare si as a constant auto reference to avoid copies
	for (const auto& storageItem : _data) {
		std::cout << std::left << std::setw(nameWidth) << storageItem.name
			<< std::setw(codeWidth) << storageItem.code
			<< std::setw(qtaWidth) << storageItem.qta
			<< std::setw(priceWidth) << storageItem.price
			<< '\n';
	}
};