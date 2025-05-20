#pragma once

#include <raylib.h>

enum GUI_INPUT
{
	NONE, UNDO, REDO, SAVE
};

struct Button
{
	Rectangle bounds;
	GUI_INPUT val = NONE;
	Texture2D texture;
	bool isHovered = false;

	Button(const char* texturePath, Rectangle bounds, GUI_INPUT val)
		: bounds(bounds), val(val)
	{
		texture = LoadTexture(texturePath);
		texture.width = bounds.width;
		texture.height = bounds.height;
	}

	inline bool isClicked(Vector2 mousePos)
	{ 
		return CheckCollisionPointRec(mousePos, bounds) 
				&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT); 
	}

	GUI_INPUT clickedAction() { return val; };
};

#define MAX_BUTTONS 10

struct RaylibGUI
{
	std::vector<Button> buttons;
	Color bg{ 20, 30, 40, 255 };

	GUI_INPUT handleInput()
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

		return NONE;
	}

	void drawGUI()
	{
		DrawRectangle(0, 0, 100, GetScreenHeight(), bg);
		for (Button& b : buttons)
		{
			DrawTexture(b.texture, b.bounds.x, b.bounds.y, (b.isHovered) ? GRAY : WHITE);
		}
	}
};
