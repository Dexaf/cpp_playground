#ifndef STORAGEITEMS
#define STORAGEITEMS
#include <string>
#include <vector>

namespace storageItemSpace {
	struct storageItem {
		std::string name{ "" };
		std::string code{ "" };
		unsigned int qta{ 0 };
		double price{ 0 };
	};

	class StorageItemContainer {
	private:
		std::vector<storageItemSpace::storageItem> _data{};

	public:
		StorageItemContainer() = default;

		//Move constructor
		//we take vector rvalue and use && to reference it and move to transfer the ownership without copying it
		StorageItemContainer(std::vector<storageItemSpace::storageItem>&& data);

		//Move assignment
		StorageItemContainer& operator=(std::vector<storageItemSpace::storageItem>&& data);

		//METHODS
		void printStorageItems();

		const std::vector<storageItemSpace::storageItem>& getData();
	};
}
#endif