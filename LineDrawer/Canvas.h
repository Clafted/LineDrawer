#pragma once

#include <raylib.h>
#include <list>
#include <string>
#include "Data.h"
#include "GUI_Layer.h"

// Class for modifying line data directly with mouse-controls
struct Canvas : public GUI_Layer
{
	std::list<Line>* lines;
	Action* action = nullptr, *finishedAction = nullptr;
	ACTION_TYPE actionType = DRAW;
	Rectangle canvasBounds{ 0, 0, 800, 600 };
	Rectangle tBounds{ 0,0,800, 600 };
	Vec2 canvMousePos;


	Canvas(Rectangle bounds, std::list<Line>* lines) : GUI_Layer(bounds), lines(lines) {}

	inline bool pointOnCanvas(Vec2 point) {
		return CheckCollisionPointRec(point, tBounds);
	}

	void moveBy(Vec2 offset)
	{
		tBounds.x += offset.x;
		tBounds.y += offset.y;
		camera.offset = Vector2{ tBounds.x, tBounds.y };
	}

	void zoomBy(float zoom)
	{
		camera.zoom += zoom;
		tBounds.width = canvasBounds.width * camera.zoom;
		tBounds.height = canvasBounds.height * camera.zoom;
	}

	Action* createAction(ACTION_TYPE type)
	{
		switch (type) 
		{
		case DRAW: return new DrawAction();
		case ERASE: return new EraseAction();
		case MOVE: return new MoveAction();
		}
	}

	Action* getAction()
	{
		canvMousePos = ((Vec2)GetMousePosition()
							- Vec2(tBounds.x, tBounds.y))
							* (1.0f/camera.zoom);

		if (!pointOnCanvas(canvMousePos)) {
			return nullptr;
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			action = createAction(actionType);
			action->press(canvMousePos, *lines);
		}

		if (action == nullptr) return nullptr;

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			action->down(canvMousePos, *lines);
		}
		else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			action->release(canvMousePos, *lines);
			finishedAction = action;
			action = nullptr;
			return finishedAction;
		}

		return nullptr;
	}

	void drawLayer() override
	{
		BeginMode2D(camera);
			DrawRectangleRec(canvasBounds, WHITE);
		
			// Lines
			for (Line l : *lines)
			{
				DrawLineV(l.start, l.end, l.touchingLine(canvMousePos) ? BLUE : BLACK);
			}

			// Currently-drawing line
			if (actionType == DRAW && action != nullptr)
			{
				DrawAction* a = (DrawAction*)action;
				DrawLineV(a->drawnLine.start, a->drawnLine.end, RED);
			}

			DrawCircleLines(canvMousePos.x, canvMousePos.y, 5, BLACK);

			DrawRectangleLinesEx(canvasBounds,1, DARKBLUE);
		EndMode2D();

		DrawRectangleLinesEx(tBounds, 1, RED);
		std::string actionName;
		switch (actionType)
		{
		case DRAW: actionName = "DRAW"; break;
		case ERASE: actionName = "ERASE"; break;
		case MOVE: actionName = "MOVE"; break;

		}
		DrawText(actionName.c_str(), bounds.x + 10, bounds.y + bounds.height - 30, 20, BLACK);
	}

};