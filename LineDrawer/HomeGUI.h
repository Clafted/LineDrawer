#pragma once

#include "GUI_Layer.h"

struct HomeGUI : public GUI_Layer
{
	Button newFile = Button("./resources/new_button.png",
		Rectangle{ 10, Page::pageHeight - 50.0f, 80, 40 }, 0);

	HomeGUI(Rectangle bounds) : GUI_Layer(bounds) {}

	void loadLayer() override {
		buttons.push_back(newFile);
	}

	void drawLayer() override
	{
		for (Button& b : buttons) {
			DrawTexture(b.texture,
				b.bounds.x,
				b.bounds.y,
				(b.isHovered) ? GRAY : WHITE);
		}
	}
};