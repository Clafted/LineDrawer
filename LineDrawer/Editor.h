#pragma once

#include <list>
#include "Data.h"
#include "Action.h"

class Editor
{
	std::list<Line> lines;
	std::stack<Action*> fStack, bStack;
	
public:
	
	~Editor()
	{
		while (!fStack.empty())
		{
			delete(fStack.top());
			fStack.pop();
		}

		while (!bStack.empty())
		{
			delete(bStack.top());
			bStack.pop();
		}
	}

	inline const std::list<Line>& getLines() { return lines; }
	inline void uploadLines(std::list<Line> lines) { this->lines = lines; }
	void useAction(Action* action);
	void undo();
	void redo();
};

