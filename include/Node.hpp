#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <unordered_map>

#include "any.hpp"

using namespace linb;
using HashMap = std::unordered_map<std::string, any>;

class Node
{
public:
	enum {
		DEFAULT_IDENTIFIER = 0
	};

	Node();
	explicit Node(Node *parent);
	explicit Node(int identifier);
	Node(int identifier, Node *parent);

        // TODO: Copy constructor - set parent to nullptr
        // TODO: Move constructor - set parent
        // TODO: Move assignment constructor - set parent ?

	~Node();

// Children management
	void append(Node *child);

	std::vector<Node*>& children();
	Node* getChildById(int identifier) const;
	std::vector<Node*> getChildrenByGroup(int group);
	bool hasChild(Node *child);
	bool hasChild(int identifier);

	std::size_t childrenCount() const;

// Siblings
	std::vector<Node*> siblings();
	Node* getSiblingById(int identifier);
	std::vector<Node*> getSiblingsByGroup(int group);

	std::size_t siblingCount() const;

// Parent management
	Node* parent() const
	{
		return parent_;
	}
	Node* parent(int identifier) const;
	std::vector<Node*> parents();
	Node* root();

	void removeChild(Node *child);
	void removeChild(int identifier);
	void removeAllChildren();

	void attach(Node *parent);
	void detach();

// Current node management
	int getId() const
	{
		return identifier_;
	}

	std::vector<int> groups() const
	{
		return groups_;
	}

	void addGroup(int group);
	void addGroup(std::vector<int> groups);
	void removeFromGroup(int group);
	void removeAllGroups();
	bool hasGroup(int group);

// Properties
        HashMap properties;

protected:
        // TODO: Reorder (check ctor)
	std::vector<Node*> children_;
	Node *parent_;

	int identifier_;
	std::vector<int> groups_;
};
