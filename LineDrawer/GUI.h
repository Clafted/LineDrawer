#pragma once

#include <vector>
#include <raylib.h>
#include "GUI_Layer.h"

class GUI 
{
	std::vector<GUI_Layer> layers;
	int activeLayer;

	// Get input from current or new active layer
	Input getActiveInput()
	{
		layers[activeLayer].handleInput();
		
	}
};