#include "Editor.h"
#include "Home.h"

void Editor::useAction(Action* action)
{
	action->redo(dataManager.lines);
	fStack.push(action);
}

void Editor::handleInput()
{
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

		if (IsKeyDown(KEY_LEFT)) canvas.offset.x += 10;
		if (IsKeyDown(KEY_RIGHT)) canvas.offset.x -= 10;
		if (IsKeyDown(KEY_UP)) canvas.offset.y += 10;
		if (IsKeyDown(KEY_DOWN)) canvas.offset.y -= 10;
	}

	canvas.zoomOnPoint(GetMousePosition(), GetMouseWheelMove() * 0.1f);
	

	switch (gui.handleInput())
	{
	case 1: undo(); break;
	case 2: redo(); break;
	case 3: dataManager.saveData(); break;
	case 4: newPage = new Home(dataManager); break;
	case -1:
		Action *action = canvas.getAction();
		if (action != nullptr) useAction(action);
	}
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