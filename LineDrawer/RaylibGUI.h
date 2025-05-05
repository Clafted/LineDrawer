#pragma once

#include <raylib.h>

struct Button
{
	Rectangle bounds;
	bool isHovered = false;

	inline bool isClicked(Vector2 mousePos)
	{ 
		return CheckCollisionPointRec(mousePos, bounds) 
				&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT); 
	}

	virtual void clickedAction() {};
};

#define MAX_BUTTONS 10

struct RaylibGUI
{
	Button* buttons[MAX_BUTTONS];

	bool checkInputs()
	{
		bool isHovered = false;
		for (Button* b : buttons)
		{
			if (b == nullptr) continue;
			b->isHovered = false;
			if (!CheckCollisionPointRec(GetMousePosition(), b->bounds)) continue;
			isHovered = b->isHovered = true;
			if (b->isClicked(GetMousePosition())) b->clickedAction();
		}

		return isHovered;
	}

	void drawGUI()
	{
		for (Button* b : buttons)
		{
			if (b != nullptr) 
				DrawRectangleRec(b->bounds, (b->isHovered) ? DARKGRAY : BLACK);
		}
	}
};
