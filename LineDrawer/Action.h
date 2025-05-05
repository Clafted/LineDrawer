#pragma once

#include <stack>
#include <list>
#include "Data.h"

struct Action
{
	virtual void redo(std::list<Line>& lines) {};
	virtual void undo(std::list<Line>& lines) {};
};
