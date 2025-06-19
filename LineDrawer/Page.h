#pragma once

#include <raylib.h>
#include <vector>
#include "GUI.h"

struct Page
{
	static int pageWidth, pageHeight;
	std::vector<GUI_Layer*> layers;
	GUI_Layer* activeLayer = nullptr;
	GUI gui;
	Page* newPage = nullptr;

	virtual void enterPage() {};
	virtual void handleInput() {};

	void drawPage() 
	{
		gui.drawGUI();
	};
};