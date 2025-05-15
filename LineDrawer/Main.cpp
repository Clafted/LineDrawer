#include <iostream>
#include <raylib.h>
#include "DataManager.h"
#include "Editor.h"
#include "RaylibGUI.h"

DataManager dataManager;
Editor editor;
RaylibGUI gui;
Vector2 startLine = { -1.0f, -1.0f }, mousePos;
Color background{ 200, 200, 200, 255 };
ACTION_TYPE actionType = DRAW;
Action* action;



Action* createAction(ACTION_TYPE type)
{
	switch (type) {
	case DRAW: return new DrawAction();
	case ERASE: return new EraseAction();
	case MOVE: return new MoveAction();
	}
}

// Handles editor input (kbm input)
void handleInput()
{
	if (IsKeyDown(KEY_LEFT_CONTROL))
	{
		switch (GetKeyPressed())
		{
		case KEY_Z:	editor.undo(); break;
		case KEY_Y: editor.redo(); break;
		case KEY_S:	dataManager.saveData(); break;
		}
	}
	else
	{
		switch (GetKeyPressed())
		{
		case KEY_M: actionType = MOVE; break;
		case KEY_E: actionType = ERASE; break;
		case KEY_D: actionType = DRAW; break;
		}
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		action = createAction(actionType);
		action->press(GetMousePosition(), dataManager.lines);
	}
	if (action == nullptr) return;
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) action->down(GetMousePosition(), dataManager.lines);
	else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		action->release(GetMousePosition(), dataManager.lines);
		editor.useAction(action);
		action = nullptr;
	}
}

int main(int argc, char* argv[])
{
	dataManager.loadFile(argv[1]);
	editor.uploadLines(dataManager.lines);

	struct undoButton : Button 
	{ void clickedAction() override { editor.undo(); } } undo;
	struct redoButton : Button 
	{ void clickedAction() override { editor.redo(); } } redo;

	undo.bounds = Rectangle{ 20.0f, 20.0f, 40.0f, 40.0f };
	redo.bounds = Rectangle{ 20.0f, 80.0f, 40.0f, 40.0f };
	gui.buttons[0] = &undo;
	gui.buttons[1] = &redo;

	InitWindow(1000, 700, "Line Drawer");
	SetTargetFPS(30);

	while (!WindowShouldClose())
	{
		mousePos = GetMousePosition();

		if (!gui.checkInputs())
			handleInput();

		BeginDrawing();
			ClearBackground(background);

			// Lines
			for (Line l : dataManager.lines)
				DrawLineV(l.start, l.end, l.touchingLine(mousePos)? BLUE : BLACK);

			// Currently-drawing line
			if (actionType == DRAW && action != nullptr)
				DrawLineV(((DrawAction*)action)->drawnLine.start, ((DrawAction*)action)->drawnLine.end, RED);

			gui.drawGUI();
		EndDrawing();
	}

	CloseWindow();
}