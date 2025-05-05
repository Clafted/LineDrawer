#include <iostream>
#include <raylib.h>
#include "DataManager.h"
#include "Editor.h"
#include "DrawAction.h"
#include "RaylibGUI.h"

DataManager dataManager;
Editor editor;
RaylibGUI gui;
Vector2 startLine = { -1.0f, -1.0f }, mousePos;
Color background{ 200, 200, 200, 255 };

bool touchingLine(const Line& line, Vec2 pos)
{
	Vec2 startP(pos.x - line.start.x, pos.y - line.start.y );
	Vec2 endP(pos.x - line.end.x, pos.y - line.end.y);
	Vec2 lineV(line.start.x - line.end.x, line.start.y - line.end.y);

	return startP.getLength() + endP.getLength() - lineV.getLength() < 2.0f;
}

void handleInput()
{
	if (IsKeyDown(KEY_LEFT_CONTROL))
	{
		switch (GetKeyPressed())
		{
		case KEY_Z:	editor.undo(); break;
		case KEY_Y: editor.redo(); break;
		case KEY_S:	dataManager.saveData(editor.getLines()); break;
		}
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) startLine = GetMousePosition(); // Start line
	else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))							 // End line
	{
		DrawAction* draw = new DrawAction();
		draw->drawnLine = Line{ startLine, GetMousePosition() };
		editor.useAction(draw);
		startLine = { -1.0f, -1.0f };
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		for (Line l : editor.getLines())
		{
			if (!touchingLine(l, GetMousePosition())) continue;
			EraseAction* erase = new EraseAction();
			erase->erasedLine = l;
			editor.useAction(erase);
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	editor.uploadLines(dataManager.loadFile(argv[1]));

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
			for (Line l : editor.getLines())
				DrawLineV(l.start, l.end, touchingLine(l, mousePos)? BLUE : BLACK);

			// Currently-drawing line
			if (startLine.x != -1.0f && startLine.y != -1.0f)
				DrawLineV(startLine, mousePos, RED);

			gui.drawGUI();
		EndDrawing();
	}

	CloseWindow();
}