#pragma once

#include <list>
#include "Action.h"
#include "Canvas.h"
#include "DataManager.h"
#include "RaylibGUI.h"

// Top-level class used to control GUI, Canvas, and Keyboard controls
struct Editor
{
	std::stack<Action*> fStack, bStack;
	std::list<Line>* lines = nullptr;

	RaylibGUI gui;
	Canvas canvas;
	DataManager& dataManager;

	Editor(DataManager& dataManager) : dataManager(dataManager) {}

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

	void loadEditor();
	void uploadLines(std::list<Line>& lines) { this->lines = &lines; }
	void handleInput();
	void useAction(Action* action);
	void undo();
	void redo();
	void drawEditor();
};

