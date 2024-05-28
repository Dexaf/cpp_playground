#ifndef TREE
#define TREE
#include <memory>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <optional>
#include "storageItem.h"

template <typename T>
class TreeNode {
private:
	const T* _self;
	TreeNode<T>* _lChild;
	TreeNode<T>* _rChild;
public:
	TreeNode(const T* self)
		: _self{ self },
		_lChild{ nullptr },
		_rChild{ nullptr }
	{}

	//should provide move assign and del
	//move constructor
	TreeNode(TreeNode&& assignedNode) {
		_self = std::move(assignedNode._self);
		_lChild = std::move(assignedNode._lChild);
		_rChild = std::move(assignedNode._rChild);
	}
	//move assign
	TreeNode& operator=(TreeNode&& assignedNode) {
		if (this != &assignedNode) {
			//delete current pnt
			delete this->_self;
			//pass assignedNode pnt to self
			_self = assignedNode._self;
			//move the childs
			_lChild = std::move(assignedNode._lChild);
			_rChild = std::move(assignedNode._rChild);

			//remove pnt to assignedNode
			assignedNode._self = nullptr;
		}
		return *this;
	}

	// Deleted Copy Constructor and Copy Assignment Operator
	TreeNode(const TreeNode&) = delete;
	TreeNode& operator=(const TreeNode&) = delete;

	//SELF
	const T*& getSelf() {
		return this->_self;
	}
	void setSelf(const T* self) {
		this->_self = self;
	}
	//LCHILD
	TreeNode<T>*& getLChild() {
		return this->_lChild;
	}
	void setLChild(TreeNode<T>* child) {
		this->_lChild = child;
	}
	//RCHILD
	TreeNode<T>*& getRChild() {
		return this->_rChild;
	}
	void setRChild(TreeNode<T>* child) {
		this->_rChild = child;
	}
	//METHODS
	//Print the tree in order using ordered deep search
	/*
		ex: if we have R:5 lc:3 rc:4

		- we check if lc exists
		- yes, call the fn passing lc
		- we check if there's a child
		- no so we print ourself -> 3
		- we go back to 5
		- we check if rc exists
		- yes, call the fn passing rc
		- we check if there's a child
		- no so we print ourself -> 4
		- we go back to 5
		- ifs ended, we print ourself -> 5
	*/
	static void orderedPrint(TreeNode<T>* currNode) {
		//if there's a sx child we go there
		if (currNode->_lChild) {
			orderedPrint(currNode->_lChild);
		}
		//if there's a sx child we go there
		if (currNode->_rChild) {
			orderedPrint(currNode->_rChild);
		}
		//in the end we printourselfs
		std::cout << *(currNode->_self) << '\n';
	}
};

//NOTE T::* points to a member of a field (ex root.*memberField)
//we return a smrt pntr to have move semantics
template <typename T, typename MemberField>
std::unique_ptr<TreeNode<T>> makeTreeFromVect(const std::vector<T>& rootElemVect, MemberField T::* memberField) {
	//declaring a pointer to a tree node
	std::unique_ptr<TreeNode<T>> rootNodePtr(new TreeNode<T>{ &(*rootElemVect.begin()) });

	//start treefication from the second element
	auto vectIter = rootElemVect.begin() + 1;

	//cycle through vect
	while (vectIter != rootElemVect.end()) {
		//get current element ref
		const T& currElemRef{ *vectIter };
		//find current element soon to be parent
		TreeNode<T>* parentForElem = getParent(rootNodePtr.get(), memberField, currElemRef);

		//extract field to be confronted to understand child position
		auto& parMemberField{ parentForElem->getSelf()->*memberField };
		auto& childMemberField{ currElemRef.*memberField };

		//TODO - string fileds need to be confronted with .compare which gives < 0 if smaller 
		//		 i should make a fn to confront with specializations for string
		//congratulations! it's a right child!
		if (parMemberField > childMemberField) {
			parentForElem->setLChild(new TreeNode<T>{ &currElemRef }); //se lo passiamo cosi non muore???
		}
		else {
			//congratulations! it's a left child!
			parentForElem->setRChild(new TreeNode<T>{ &currElemRef });
		}
		//go to next
		vectIter++;
	}

	return rootNodePtr;
}

template <typename T, typename MemberField>
//we extract the ref to the parent of out child
//std::unique_ptr<TreeNode<T>>& 
TreeNode<T>* getParent(TreeNode<T>* currParent, MemberField T::* confrontMemberField, const T& child) {
	const T*& currParentSelf{ currParent->getSelf()}; //ref to a pntr.
	/*
		if the confrontated value of the current parent is
		bigger then the c.v. of the child we search in the
		parent's right child, othwerwise we do next routine
		mirrored for the left child
	*/
	if (*(currParentSelf).*confrontMemberField > child.*confrontMemberField) {
		TreeNode<T>* currLChild{ currParent->getLChild() };
		if (currLChild) {
			return getParent(currLChild, confrontMemberField, child);
		}
		else {
			return currParent;
		}
	}
	else {
		TreeNode<T>* currRChild{ currParent->getRChild() };
		if (currRChild) {
			return getParent(currRChild, confrontMemberField, child);
		}
		else {
			return currParent;
		}
	}
}
#endif // !TREE