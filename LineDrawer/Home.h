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
	HomeGUI homeGUI = HomeGUI(Rectangle{ 0, Page::pageHeight - 60.0f, (float)Page::pageWidth, 60});

	Home(DataManager& dataManager) : dataManager(dataManager) {}

	void enterPage() override
	{
		SetWindowTitle("Home | LineDrawer");
		fSelector.loadLayer();
		homeGUI.loadLayer();
		gui.addLayer(&fSelector);
		gui.addLayer(&homeGUI);
	}

	void handleInput() override
	{
		GUI_Layer* activeLayer = gui.getActiveInputLayer();
		if (activeLayer == nullptr) return;
		
		int clickedButton = gui.getActiveInput().button;

		switch (clickedButton)
		{
		case 0:
			dataManager.loadNewFile();
			newPage = new Editor(dataManager);
			return;
		}
		
		if (clickedButton != -1) 
		{
			std::string file = fSelector.files[clickedButton].path().string();
			if (dataManager.loadFile(file.c_str())) {
				SetWindowTitle((file + " | LineDrawer").c_str());
				newPage = new Editor(dataManager);
			}
		}
	}
};