#pragma once

#include "DataManager.h"
#include "GUI_Layer.h"

struct FileSelector : public GUI_Layer
{
	std::vector<std::filesystem::directory_entry> files;
	DataManager& dataManager;

	FileSelector(Rectangle bounds, DataManager& dataManager)
		: GUI_Layer(bounds), dataManager(dataManager) {
	}

	bool checkLayerActivation() override {
		return CheckCollisionPointRec(GetMousePosition(), bounds);
	}

	bool checkInput() override
	{
		bounds.y = std::min(0.0f, camera.offset.y + 40 * GetMouseWheelMove());
		camera.offset.y = bounds.y;
		input.button = checkButtonInput();

		return clickedInBounds();
	}

	void loadLayer() override
	{
		files = dataManager.getLineFiles();
		// Buttons are W:(pageWidth - 20)	H:200
		for (int i = 0; i < files.size(); i++) {
			buttons.push_back(Button("", Rectangle{ 10, 10.0f + 220 * i, Page::pageWidth - 20.0f, 200 }, i));
		}

		bounds.height = 10 + buttons.size() * 220;
	}

	void drawLayer() override
	{
		BeginMode2D(camera);
		for (int i = 0; i < buttons.size(); i++)
		{
			DrawRectangleRec(buttons[i].bounds, (buttons[i].isHovered) ? GRAY : WHITE);
			DrawText(("Name: " + files[i].path().string()).c_str(), 20, 20 + 220 * i, 20, BLACK);
			DrawText(("Size: " + std::to_string(files[i].file_size()) + " bytes").c_str(), 20, 50 + 220 * i, 20, BLACK);
		}
		EndMode2D();
	}
};