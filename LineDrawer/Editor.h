#pragma once

#include <list>
#include "Page.h"
#include "Action.h"
#include "Canvas.h"
#include "DataManager.h"
#include "RaylibGUI.h"

// Top-level class used to control GUI, Canvas, and Keyboard controls
struct Editor : public Page
{
	std::stack<Action*> fStack, bStack;

	RaylibGUI toolbar;
	Canvas canvas;
	DataManager& dataManager;

	Editor(DataManager& dataManager);
	~Editor();

	void handleInput() override;
	void useAction(Action* action);
	void undo();
	void redo();
};

