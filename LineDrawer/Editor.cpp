#include "Editor.h"
#include "Home.h"


Editor::Editor(DataManager& dataManager)
	: dataManager(dataManager),
	canvas(Rectangle{ 100, 0, (float)Page::pageWidth - 100, (float)Page::pageHeight }, & dataManager.lines),
	toolbar(Rectangle{ 0, 0, 100, (float)Page::pageHeight })
{
	layers.push_back(&canvas);
	layers.push_back(&toolbar);
	gui.addLayer(&canvas);
	gui.addLayer(&toolbar);
}

Editor::~Editor()
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

void Editor::useAction(Action* action)
{
	action->redo(dataManager.lines);
	fStack.push(action);
}

void Editor::handleInput()
{
	GUI_Layer* activeLayer = gui.getActiveInputLayer();
	if (activeLayer == nullptr) return;
	if (activeLayer == &toolbar)
	{
		switch (gui.getActiveInput().button)
		{
		case 1: undo(); break;
		case 2: redo(); break;
		case 3: dataManager.saveData(); break;
		case 4: canvas.actionType = DRAW; break;
		case 5: canvas.actionType = ERASE; break;
		case 6: canvas.actionType = MOVE; break;
		case 7: newPage = new Home(dataManager); break;
		}
	}
	else if (activeLayer == &canvas) 
	{
		Action* action = canvas.getAction();
		if (action != nullptr) useAction(action);
	}

	if (IsKeyDown(KEY_LEFT_CONTROL))
	{
		switch (GetKeyPressed())
		{
		case KEY_Z:	undo(); break;
		case KEY_Y: redo(); break;
		case KEY_S:	dataManager.saveData(); break;
		}
	}
	else
	{
		switch (GetKeyPressed())
		{
		case KEY_M: canvas.actionType = MOVE; break;
		case KEY_E: canvas.actionType = ERASE; break;
		case KEY_D: canvas.actionType = DRAW; break;
		}

		if (IsKeyDown(KEY_LEFT)) canvas.moveBy(Vector2{ 10,0 });
		if (IsKeyDown(KEY_RIGHT)) canvas.moveBy(Vector2{ -10, 0 });
		if (IsKeyDown(KEY_UP)) canvas.moveBy(Vector2{ 0, 10 });
		if (IsKeyDown(KEY_DOWN)) canvas.moveBy(Vector2{ 0, -10 });
	}

	canvas.zoomBy(GetMouseWheelMove() * 0.1f);
}

void Editor::undo()
{
	if (fStack.size() < 1) return;
	fStack.top()->undo(dataManager.lines);
	bStack.push(fStack.top());
	fStack.pop();
}

void Editor::redo()
{
	if (bStack.size() < 1) return;
	bStack.top()->redo(dataManager.lines);
	fStack.push(bStack.top());
	bStack.pop();
}