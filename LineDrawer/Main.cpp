#include <iostream>
#include <raylib.h>

#include "DataManager.h"

DataManager dataManager;
Vector2 startLine = { -1.0f, -1.0f }, mousePos;
Color background{ 220, 220, 220, 255 };

void handleInput()
{
	if (IsKeyDown(KEY_LEFT_CONTROL))
	{
		if (IsKeyPressed(KEY_Z)) dataManager.undo();
		else if (IsKeyPressed(KEY_Y)) dataManager.redo();

		if (IsKeyPressed(KEY_S)) dataManager.saveData();
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) startLine = GetMousePosition();
	else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		dataManager.addLine(Line{ startLine, mousePos });
		startLine = { -1.0f, -1.0f };
	}
}

int main()
{
	InitWindow(1000, 700, "Line Drawer");

	SetTargetFPS(30);

	while (!WindowShouldClose())
	{
		mousePos = GetMousePosition();
		handleInput();

		BeginDrawing();
			ClearBackground(background);

			for (Line l : dataManager.getLines())
				DrawLine(l.start.x, l.start.y, l.end.x, l.end.y, BLACK);

			if (startLine.x != -1.0f && startLine.y != -1.0f)
				DrawLine(startLine.x, startLine.y, GetMousePosition().x, GetMousePosition().y, RED);
		EndDrawing();
	}

	CloseWindow();
}