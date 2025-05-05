#pragma once

#include "Action.h"

struct DrawAction : public Action
{
	Line drawnLine;

	void redo(std::list<Line>& lines) override
	{
		lines.push_back(drawnLine);
	}
	
	void undo(std::list<Line>& lines) override
	{
		lines.remove(drawnLine);
	}
};

struct EraseAction : public Action
{
	Line erasedLine;

	void redo(std::list<Line>& lines) override
	{
		lines.remove(erasedLine);
	}
	
	void undo(std::list<Line>& lines) override
	{
		lines.push_back(erasedLine);
	}
};