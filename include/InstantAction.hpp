#pragma once

#include <string>

#include "Action.hpp"

class InstantAction : public Action
{
public:
	explicit InstantAction(const std::string& name);
	~InstantAction()
	{
	};

	void step(float delta);
};

