#pragma once

#include <stack>
#include <list>
#include "Data.h"

struct Action
{
	virtual void press(Vector2 mousePos, std::list<Line>& lines) {};
	virtual void down(Vector2 mousePos, std::list<Line>& lines) {};
	virtual void release(Vector2 mousePos, std::list<Line>& lines) {};
	virtual void redo(std::list<Line>& lines) {};
	virtual void undo(std::list<Line>& lines) {};
};

enum ACTION_TYPE
{
	DRAW, ERASE, MOVE
};

struct DrawAction : public Action
{
	Line drawnLine;

	void press(Vector2 mousePos, std::list<Line>& lines) {
		drawnLine.start = mousePos;
	}

	void down(Vector2 mousePos, std::list<Line>& lines) {
		drawnLine.end = mousePos;
	}

	void release(Vector2 mousePos, std::list<Line>& lines) {
		drawnLine.end = mousePos;
	}

	void redo(std::list<Line>& lines) override {
		lines.push_back(drawnLine);
	}

	void undo(std::list<Line>& lines) override {
		lines.remove(drawnLine);
	}
};

struct EraseAction : public Action
{
	std::list<Line> erasedLines;

	// Erase any lines which make contact with the cursor
	void down(Vector2 mousePos, std::list<Line>& lines) override
	{
		for (Line& l : lines)
		{
			if (l.touchingLine(mousePos)) {
				erasedLines.push_back(l);
			}
		}

		for (Line& l : erasedLines) lines.remove(l);
	}

	// Remove erased lines from given list of lines lines, if they exist
	inline void redo(std::list<Line>& lines) override {
		for (Line l : erasedLines) lines.remove(l);
	}

	inline void undo(std::list<Line>& lines) override {
		for (Line l : erasedLines) lines.push_back(l);
	}
};

struct MoveAction : public Action
{
	Line *movedLine = nullptr;
	Vector2 startPos = {}, offset = {};

	void press(Vector2 mousePos, std::list<Line>& lines) override
	{
		for (Line& l : lines) {
			if (l.touchingLine(mousePos)) movedLine = &l;
		}
		startPos = mousePos;
	}

	inline void down(Vector2 mousePos, std::list<Line>& lines) override {
		offset = Vec2(mousePos) - startPos;
	}

	inline void release(Vector2 mousePos, std::list<Line>& lines) override {
		offset = Vec2(mousePos) - startPos;
	}

	void redo(std::list<Line>& lines) override
	{ 
		if (movedLine == nullptr) return;
		movedLine->end = movedLine->end + offset;
		movedLine->start = movedLine->start + offset;
	}

	void undo(std::list<Line>& lines) override
	{
		if (movedLine == nullptr) return;
		movedLine->end = movedLine->end - offset;
		movedLine->start = movedLine->start - offset;
	}
};