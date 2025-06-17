#pragma once
#include <iostream>
#include <raylib.h>
#include "DataManager.h"
#include "Editor.h"
#include "Home.h"
#include "RaylibGUI.h"

class LineDrawerProgram
{

	Page* currentPage = nullptr;
	DataManager dataManager;
	Vector2 startLine = { -1.0f, -1.0f }, mousePos;
	Color background{ 0, 10, 20 };

	void handleNewPage()
	{
		if (currentPage->newPage == nullptr) return;
		Page* newPage = currentPage->newPage;
		delete(currentPage);
		currentPage = newPage;
		currentPage->enterPage();
	}

public:

	int initProgram()
	{
		InitWindow(Page::pageWidth, Page::pageHeight, "Line Drawer");
		SetTargetFPS(30);

		dataManager.setupSoftware();
		currentPage = new Home(dataManager);
		currentPage->enterPage();

		while (!WindowShouldClose())
		{
			handleNewPage();

			// Input
			mousePos = GetMousePosition();
			currentPage->handleInput();

			// Render
			BeginDrawing();
				ClearBackground(background);
				currentPage->drawPage();
			EndDrawing();
		}

		delete(currentPage);
		CloseWindow();
		return 0;
	}
};