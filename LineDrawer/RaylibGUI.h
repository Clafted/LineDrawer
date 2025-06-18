#pragma once

#include <raylib.h>
#include "GUI_Layer.h"

#define MAX_BUTTONS 10

struct RaylibGUI : public GUI_Layer
{
	Color bg{ 20, 30, 40, 255 };

	TextField field;

	RaylibGUI(Rectangle bounds) : GUI_Layer(bounds), field(Rectangle{ 100, 100, 200, 30 })
	{
		// Buttons 20 pixels apart
		Button undo("./resources/undo_button.png", Rectangle{ 20.0f, 20.0f, 60.0f, 40.0f }, 1),
			redo("./resources/redo_button.png", Rectangle{ 20.0f, 80.0f, 60.0f, 40.0f }, 2),
			save("./resources/save_button.png", Rectangle{ 20.0f, 140.0f, 60, 30.0f }, 3),
			draw("./resources/pencil_button.png", Rectangle{ 20.0f, 190.0f, 60, 60.0f }, 4),
			erase("./resources/eraser_button.png", Rectangle{ 20.0f, 270.0f, 60, 60.0f }, 5),
			move("./resources/move_button.png", Rectangle{ 20.0f, 350.0f, 60, 60.0f }, 6),
			home("./resources/home_button.png", Rectangle{ 20.0f, 430.0f, 60, 60.0f }, 7);

		buttons.push_back(undo);
		buttons.push_back(redo);
		buttons.push_back(save);
		buttons.push_back(home);
		buttons.push_back(draw);
		buttons.push_back(erase);
		buttons.push_back(move);
	}

	int handleInput() override
	{
		bool isHovered = false;
		field.checkInput();
		// Check button inputs
		for (Button& b : buttons)
		{
			b.isHovered = CheckCollisionPointRec(GetMousePosition(), b.bounds);
			isHovered = (isHovered || b.isHovered);
			if (isHovered && b.isClicked(GetMousePosition())) {
				return b.clickedAction();
			}
		}

		return -1;
	}

	void drawLayer() override
	{
		DrawRectangle(0, 0, 100, GetScreenHeight(), bg);
		for (Button& b : buttons) {
			DrawTexture(b.texture, b.bounds.x, b.bounds.y, 
						(b.isHovered) ? GRAY : WHITE);
		}

		field.draw();
	}
};
