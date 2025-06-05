#pragma once

#include "DataManager.h"
#include "Page.h"
#include "GUI_Layer.h"

struct FileSelector : public GUI_Layer
{
	std::vector<std::filesystem::directory_entry> files;
	DataManager& dataManager;

	FileSelector(Rectangle bounds, DataManager& dataManager) 
		: GUI_Layer(bounds), dataManager(dataManager) {}

	int handleInput() override
	{
		bounds.y = std::min(0.0f, bounds.y + 40 * GetMouseWheelMove());
		camera.offset.y = bounds.y;

		return checkButtonInput();
	}

	void loadLayer() override
	{

		files = dataManager.getLineFiles();
		for (int i = 0; i < files.size(); i++)
			buttons.push_back(Button("", Rectangle{ 10, 10.0f + 220 * i, Page::pageWidth - 20.0f, 200 }, i));
	}

	void drawLayer() override
	{
		BeginMode2D(camera);
			for (int i = 0; i < buttons.size(); i++)
			{
				DrawRectangleRec(buttons[i].bounds, (buttons[i].isHovered) ? GRAY: WHITE);
				DrawText(("Name: " + files[i].path().string()).c_str(), 20, 20 + 220 * i, 20, BLACK);
				DrawText(("Size: " + std::to_string(files[i].file_size()) + " bytes").c_str(), 20, 50 + 220 * i, 20, BLACK);
			}
		EndMode2D();
	}
};

struct HomeGUI : public GUI_Layer
{
	Button newFile = Button("./resources/new_button.png",
							Rectangle{ 10, Page::pageHeight - 50.0f, 80, 40 }, 
							0);

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

struct Home : public Page
{
	DataManager& dataManager;
	FileSelector fSelector = FileSelector(Rectangle{ 0, 0, (float)Page::pageWidth, (float)Page::pageHeight }, dataManager);
	HomeGUI homeGUI = HomeGUI(Rectangle{ 0, 0, (float)Page::pageWidth, (float)Page::pageHeight });

	Home(DataManager& dataManager) : dataManager(dataManager) {}

	void enterPage() override
	{
		fSelector.loadLayer();
		homeGUI.loadLayer();
		layers.push_back(&fSelector);
		layers.push_back(&homeGUI);
	}

	void handleInput() override
	{
		switch (homeGUI.checkButtonInput())
		{
		case 0:
			dataManager.loadNewFile();
			newPage = new Editor(dataManager);
			return;
		}

		int clickedFile = fSelector.handleInput();
		if (clickedFile != -1 
			&& dataManager
				.loadFile(fSelector
						.files[clickedFile]
						.path().string().c_str())) 
		{
			newPage = new Editor(dataManager);
		}
	}
};