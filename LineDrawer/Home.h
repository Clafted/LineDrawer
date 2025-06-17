#pragma once

#include "DataManager.h"
#include "FileSelector.h"
#include "Page.h"
#include "GUI_Layer.h"
#include "HomeGUI.h"

struct Home : public Page
{
	DataManager& dataManager;
	FileSelector fSelector = FileSelector(Rectangle{ 0, 0, (float)Page::pageWidth, (float)Page::pageHeight }, dataManager);
	HomeGUI homeGUI = HomeGUI(Rectangle{ 0, 0, (float)Page::pageWidth, (float)Page::pageHeight });

	Home(DataManager& dataManager) : dataManager(dataManager) {}

	void enterPage() override
	{
		SetWindowTitle("Home | LineDrawer");
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
		
		if (clickedFile != -1) 
		{
			std::string file = fSelector.files[clickedFile].path().string();
			if (dataManager.loadFile(file.c_str())) {
				SetWindowTitle((file + " | LineDrawer").c_str());
				newPage = new Editor(dataManager);
			}
		}
	}
};