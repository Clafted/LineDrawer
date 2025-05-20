#pragma once

#include <raylib.h>
#include <vector>

struct GUI_Layer
{
	virtual void drawLayer() {};
};

struct Page
{
	std::vector<GUI_Layer*> layers;

	void drawPage() 
	{
		for (GUI_Layer* layer : layers)
			layer->drawLayer();
	};
};