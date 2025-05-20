#pragma once

#include <raylib.h>
#include <list>
#include "Data.h"

// Class for modifying line data directly with mouse-controls
struct Canvas
{
	Action* action = nullptr, *finishedAction = nullptr;
	ACTION_TYPE actionType = DRAW;
	Rectangle bounds{ 0, 0, 800, 600 };
	Rectangle tBounds{ 0,0,800, 600 };
	Vec2 offset;
	float zoom = 1.0f;

	bool pointOnCanvas(Vec2 point)
	{
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

	Action* handleInput(std::list<Line>& lines)
	{
		if (!pointOnCanvas(GetMousePosition())) 
			return nullptr;

		Vector2 tMousePos = (Vec2)GetMousePosition() 
							* (1.0f/zoom) 
							+ Vec2(tBounds.x, tBounds.y);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			action = createAction(actionType);
			action->press(tMousePos, lines);
		}

		if (action == nullptr) return nullptr;

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			action->down(tMousePos, lines); 
		else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			action->release(tMousePos, lines);
			finishedAction = action;
			action = nullptr;
			return finishedAction;
		}

		return nullptr;
	}

	void drawCanvas(std::list<Line>& lines)
	{
		DrawRectangle(tBounds.x + 10 + offset.x*zoom, tBounds.y + 10 + offset.y*zoom, tBounds.width, tBounds.height, Color{ 0, 0, 0, 120 });
		DrawRectangle(tBounds.x + offset.x*zoom, tBounds.y + offset.y*zoom, tBounds.width, tBounds.height, WHITE);
		
		// Lines
		for (Line l : lines)
		{
			l.start *= zoom;
			l.end *= zoom;
			DrawLineV(l.start, l.end, l.touchingLine(GetMousePosition()) ? BLUE : BLACK);
		}

		// Currently-drawing line
		if (actionType == DRAW && action != nullptr)
		{
			DrawAction* a = (DrawAction*)action;
			Line l{ a->drawnLine.start*zoom, a->drawnLine.end*zoom};
			DrawLineV(l.start, l.end, RED);
		}
	}
};