#pragma once

#include <raylib.h>
#include <list>
#include "Data.h"
#include "GUI_Layer.h"

// Class for modifying line data directly with mouse-controls
struct Canvas : public GUI_Layer
{
	std::list<Line>* lines;
	Action* action = nullptr, *finishedAction = nullptr;
	ACTION_TYPE actionType = DRAW;
	Rectangle bounds{ 0, 0, 800, 600 };
	Rectangle tBounds{ 0,0,800, 600 };
	Vec2 offset;

	float zoom = 1.0f;

	Canvas(Rectangle bounds, std::list<Line>* lines) : GUI_Layer(bounds), lines(lines) {}

	inline bool pointOnCanvas(Vec2 point) {
		return CheckCollisionPointRec(point, tBounds);
	}

	void zoomOnPoint(Vec2 point, float zoom)
	{
		this->zoom += zoom;
		tBounds.width = bounds.width * this->zoom;
		tBounds.height = bounds.height * this->zoom;
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
		if (!pointOnCanvas(GetMousePosition())) {
			return nullptr;
		}

		Vector2 tMousePos = ((Vec2)GetMousePosition()
							- Vec2(tBounds.x, tBounds.y)
							- offset) * (1.0f/zoom);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			action = createAction(actionType);
			action->press(tMousePos, *lines);
		}

		if (action == nullptr) return nullptr;

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			action->down(tMousePos, *lines);
		}
		else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			action->release(tMousePos, *lines);
			finishedAction = action;
			action = nullptr;
			return finishedAction;
		}

		return nullptr;
	}

	void drawLayer() override
	{
		camera.offset = offset;
		camera.zoom = zoom;
		BeginMode2D(camera);
			DrawRectangleRec(tBounds, WHITE);
		
			// Lines
			for (Line l : *lines)
			{
				l.start *= zoom;
				l.end *= zoom;
				DrawLineV(l.start, l.end, l.touchingLine(GetMousePosition()) ? BLUE : BLACK);
			}

			// Currently-drawing line
			if (actionType == DRAW && action != nullptr)
			{
				DrawAction* a = (DrawAction*)action;
				DrawLineV(a->drawnLine.start, a->drawnLine.end, RED);
			}

			DrawRectangleLinesEx(tBounds,1, DARKBLUE);
		EndMode2D();
	}

};