#include <iostream>
#include <raylib.h>

#include "DataManager.h"

DataManager dataManager;
Vector2 startLine = { -1.0f, -1.0f }, mousePos;

void handleInput()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) startLine = GetMousePosition();
	else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		dataManager.addLine(Line{ Vec2{startLine.x, startLine.y}, Vec2{mousePos.x, mousePos.y} });
		startLine = { -1.0f, -1.0f };
	}
}

int main()
{
	InitWindow(1000, 700, "Line Drawer");

	while (!WindowShouldClose())
	{
		mousePos = GetMousePosition();

		handleInput();

		BeginDrawing();
		ClearBackground(BLACK);

		for (Line l : dataManager.getLines())
			DrawLine(l.start.x, l.start.y, l.end.x, l.end.y, WHITE);

		if (startLine.x != -1.0f && startLine.y != -1.0f)
			DrawLine(startLine.x, startLine.y, GetMousePosition().x, GetMousePosition().y, GREEN);

		EndDrawing();
	}

	dataManager.saveData();

	CloseWindow();
}