#include <iostream>
#include <raylib.h>
#include "DataManager.h"
#include "Editor.h"
#include "RaylibGUI.h"

DataManager dataManager;
Editor editor(dataManager);
Vector2 startLine = { -1.0f, -1.0f }, mousePos;
Color background{ 200, 200, 200, 255 };

int main(int argc, char* argv[])
{
	InitWindow(1000, 700, "Line Drawer");
	SetTargetFPS(30);

	dataManager.setupSoftware();
	dataManager.loadFile(argv[1]);
	editor.uploadLines(dataManager.lines);
	editor.loadEditor();

	dataManager.listLineFiles();

	while (!WindowShouldClose())
	{
		mousePos = GetMousePosition();

		editor.handleInput();

		BeginDrawing();
			ClearBackground(background);
			editor.drawEditor();
		EndDrawing();
	}


	CloseWindow();
}