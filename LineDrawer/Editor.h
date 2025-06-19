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

	Editor(DataManager& dataManager) 
		: dataManager(dataManager), 
		canvas(Rectangle{ 100, 0, (float)Page::pageWidth - 100, (float)Page::pageHeight }, & dataManager.lines), 
		toolbar(Rectangle{ 0, 0, 100, (float)Page::pageHeight })
	{	
		layers.push_back(&canvas);
		layers.push_back(&toolbar);
		gui.addLayer(&canvas);
		gui.addLayer(&toolbar);
	}

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

	void handleInput() override;
	void useAction(Action* action);
	void undo();
	void redo();
};

