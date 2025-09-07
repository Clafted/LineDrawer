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
	Rectangle tBounds=canvasBounds;
	Vec2 canvMousePos;


	Canvas(Rectangle bounds, std::list<Line>* lines) : GUI_Layer(bounds), lines(lines) 
	{
		camera.offset = { 0 };
		camera.target = Vector2{ (Page::pageWidth - canvasBounds.width) / -2.0f, (Page::pageHeight-canvasBounds.height) / -2.0f };
	}

	inline bool pointOnCanvas(Vec2 point) {
		return CheckCollisionPointRec(point, tBounds);
	}

	bool checkInput() override {
		return true;
	}

	void moveBy(Vec2 offset)
	{
		camera.target.x += offset.x;
		camera.target.y += offset.y;
	}

	void zoomBy(float zoom) {
		camera.zoom += zoom;
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
		canvMousePos = GetScreenToWorld2D(GetMousePosition(), camera);;

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
			for (Line l : *lines) {
				DrawLineV(l.start, l.end, l.touchingLine(canvMousePos) ? BLUE : BLACK);
			}

			// Currently-drawing line
			if (action != nullptr)
			{
				switch (actionType)
				{
				case DRAW:
				{
					DrawAction* a = (DrawAction*)action;
					DrawLineV(a->drawnLine.start, a->drawnLine.end, RED);
				}
					break;
				case MOVE:
				{
					MoveAction* b = (MoveAction*)action;
					if (b->movedLine == nullptr) break;
					DrawLine(b->movedLine->start.x + b->offset.x,
						b->movedLine->start.y + b->offset.y,
						b->movedLine->end.x + b->offset.x,
						b->movedLine->end.y + b->offset.y,
						RED);
				}
					break;
				}
			}

			DrawCircleLines(canvMousePos.x, canvMousePos.y, 5, BLACK);
			DrawRectangleLinesEx(canvasBounds, 1, RED);
		EndMode2D();

		// Tool info
		std::string str;
		switch (actionType)
		{
		case DRAW: str = "DRAW"; break;
		case ERASE: str = "ERASE"; break;
		case MOVE: str = "MOVE"; break;

		}

		DrawText(str.c_str(), bounds.x + 10, bounds.y + bounds.height - 30, 20, LIGHTGRAY);
		str = "(" + std::to_string((int)canvMousePos.x) + ", " + std::to_string((int)canvMousePos.y) + ")";
		DrawText(str.c_str(), bounds.x + 10, bounds.y + bounds.height - 55, 15, LIGHTGRAY);
	}

};