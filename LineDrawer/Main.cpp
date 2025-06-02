#include <iostream>
#include <raylib.h>
#include "DataManager.h"
#include "Editor.h"
#include "Home.h"
#include "RaylibGUI.h"

Page* currentPage = nullptr;
DataManager dataManager;
Vector2 startLine = { -1.0f, -1.0f }, mousePos;
Color background{ 200, 200, 200, 255 };

int Page::pageWidth = 1000;
int Page::pageHeight = 700;

int main(int argc, char* argv[])
{
	InitWindow(1000, 700, "Line Drawer");
	SetTargetFPS(30);

	dataManager.setupSoftware();
	currentPage = new Home(dataManager);
	currentPage->enterPage();

	while (!WindowShouldClose())
	{
		if (currentPage->newPage != nullptr)
		{
			Page* newPage = currentPage->newPage;
			delete(currentPage);
			currentPage = newPage;
			currentPage->enterPage();
		}
		mousePos = GetMousePosition();
		currentPage->handleInput();

		BeginDrawing();
			ClearBackground(background);
			currentPage->drawPage();
		EndDrawing();
	}
	delete(currentPage);

	CloseWindow();
}