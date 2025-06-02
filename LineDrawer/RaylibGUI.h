#pragma once

#include <raylib.h>
#include "Page.h"

#define MAX_BUTTONS 10

struct RaylibGUI : public GUI_Layer
{
	Color bg{ 20, 30, 40, 255 };

	RaylibGUI(Rectangle bounds) : GUI_Layer(bounds) {}

	int handleInput() override
	{
		bool isHovered = false;

		// Check button inputs
		for (Button& b : buttons)
		{
			b.isHovered = CheckCollisionPointRec(GetMousePosition(), b.bounds);
			isHovered = (isHovered || b.isHovered);
			if (isHovered && b.isClicked(GetMousePosition())) 
				return b.clickedAction();
		}

		return -1;
	}

	void drawLayer() override
	{
		DrawRectangle(0, 0, 100, GetScreenHeight(), bg);
		for (Button& b : buttons)
		{
			DrawTexture(b.texture, b.bounds.x, b.bounds.y, (b.isHovered) ? GRAY : WHITE);
		}
	}
};
