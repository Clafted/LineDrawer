#pragma once

#include <list>
#include "Data.h"
#include "Action.h"

class Editor
{
	std::stack<Action*> fStack, bStack;
	std::list<Line>* lines;
	
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

	void uploadLines(std::list<Line>& lines) { this->lines = &lines; }
	void useAction(Action* action);
	void undo();
	void redo();
};

