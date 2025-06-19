#pragma once

#include <deque>
#include <raylib.h>
#include "GUI_Layer.h"

#define SHOW_BOUNDS false
#define SHADE_ACTIVE false

class GUI 
{
	std::vector<GUI_Layer*> layers;		// Hierarchy increases from 0
	int activeLayer = -1;
	Input activeInput;

	void evaluateActiveLayer() 
	{
		for (int i = 0; i < layers.size(); i++) {
			if (layers[i]->checkLayerActivation()) activeLayer = i;
		}
	}

public:

	void addLayer(GUI_Layer* layer) {
		layers.push_back(layer);
	}

	/* Get pointer to active layer if it has new input.
	 * Returns null otherwise. */
	GUI_Layer* getActiveInputLayer()
	{
		evaluateActiveLayer();
		if (activeLayer != -1 && layers[activeLayer]->checkInput()) {
			activeInput = layers[activeLayer]->getInput();
			return layers[activeLayer];
		}

		return nullptr;
	}

	inline const Input getActiveInput() {
		return activeInput;
	}

	void drawGUI()
	{
		for (int i = 0; i < layers.size(); i++) 
		{
			layers[i]->drawLayer();
			
			if (SHADE_ACTIVE)
			{
				DrawRectangleRec(layers[i]->getBounds(),
					(i == activeLayer) ? Color{ 255, 0, 0, 20 } : Color{0});
			}

			if (SHOW_BOUNDS) {
				DrawRectangleLinesEx(layers[i]->getBounds(), 1, (i == activeLayer) ? RED : GREEN);
			}
		}
	}
};