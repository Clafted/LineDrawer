#include "Editor.h"


void Editor::useAction(Action* action)
{
	action->redo(*lines);
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

		if (IsKeyDown(KEY_LEFT)) canvas.offset.x -= 10;
		if (IsKeyDown(KEY_RIGHT)) canvas.offset.x += 10;
		if (IsKeyDown(KEY_UP)) canvas.offset.y -= 10;
		if (IsKeyDown(KEY_DOWN)) canvas.offset.y += 10;
	}

	canvas.zoomOnPoint(GetMousePosition(), GetMouseWheelMove() * 0.1f);
	

	switch (gui.handleInput())
	{
	case UNDO: undo(); break;
	case REDO: redo(); break;
	case SAVE: dataManager.saveData(); break;
	case NONE:
		Action *action = canvas.handleInput(*lines);
		if (action != nullptr) useAction(action);
	}
}

void Editor::undo()
{
	if (fStack.size() < 1) return;
	fStack.top()->undo(*lines);
	bStack.push(fStack.top());
	fStack.pop();
}

void Editor::redo()
{
	if (bStack.size() < 1) return;
	bStack.top()->redo(*lines);
	fStack.push(bStack.top());
	bStack.pop();
}

void Editor::drawEditor()
{
	canvas.drawCanvas(*lines);
	gui.drawGUI();
}

void Editor::loadEditor()
{
	Button undo("./resources/undo_button.png", Rectangle{ 20.0f, 20.0f, 60.0f, 40.0f }, UNDO),
		redo("./resources/redo_button.png", Rectangle{ 20.0f, 80.0f, 60.0f, 40.0f }, REDO),
		save("./resources/save_button.png", Rectangle{20.0f, 140.0f, 60, 30.0f}, SAVE);

	gui.buttons.push_back(undo);
	gui.buttons.push_back(redo);
	gui.buttons.push_back(save);
}