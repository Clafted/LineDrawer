#pragma once

#include <raylib.h>
#include <vector>
#include "GUI_Layer.h"

struct Page
{
	static int pageWidth, pageHeight;

	std::vector<GUI_Layer*> layers;
	Page* newPage = nullptr;

	virtual void enterPage() {};
	virtual void handleInput() {};

	void drawPage() 
	{
		for (GUI_Layer* layer : layers) {
			layer->drawLayer();
		}
	};
};