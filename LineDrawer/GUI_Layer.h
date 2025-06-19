#pragma once
#include <string>
#include <iostream>
#include <raylib.h>

struct Button
{
	Rectangle bounds;
	Texture2D texture;
	int val = 0;
	bool isHovered = false;

	Button(const char* texturePath, Rectangle bounds, int val)
		: bounds(bounds), val(val)
	{
		texture = LoadTexture(texturePath);
		texture.width = bounds.width;
		texture.height = bounds.height;
	}

	inline bool isClicked(Vector2 mousePos)
	{
		return CheckCollisionPointRec(mousePos, bounds)
				&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
	}

	inline int clickedAction() { return val; };

};

class TextField
{

	Rectangle bounds;
	std::string text = "";
	int cursor = 0;

public:

	inline const std::string getText() {
		return text;
	}

	TextField(Rectangle bounds) : bounds(bounds) {}

	void checkInput()
	{
		int keyPressed = GetKeyPressed();
		if (keyPressed == KEY_NULL) return;
		switch (keyPressed)
		{
		case KEY_BACKSPACE:
			if (cursor == 0) break;
			text.erase(--cursor);
			break;
		default:
			text = text.substr(0, cursor) + (char)keyPressed + text.substr(cursor++);
			break;
		}
	}

	void draw()
	{
		DrawRectangleRec(bounds, WHITE);
		DrawRectangleLinesEx(bounds, 2, BLACK);
		DrawText(text.c_str(), bounds.x, bounds.y + 2, bounds.height-4, BLACK);
	}
};

struct Input
{
	int key;
	int mouse;
	int button;
	Vector2 mousePos;
};

class GUI_Layer
{
protected:

	std::vector<Button> buttons;
	Camera2D camera = { 0 };
	Rectangle bounds;
	Input input;

public:

	GUI_Layer(Rectangle bounds) : bounds(bounds) { camera.zoom = 1.0f; }

	virtual void drawLayer() {};
	virtual void loadLayer() {};
	virtual bool checkInput() { return false; };
	virtual bool checkLayerActivation() { return clickedInBounds(); }

	inline bool clickedInBounds() {
		return (CheckCollisionPointRec(GetMousePosition(), bounds)
			&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
	}

	const inline Input getInput() { return input; }
	const inline Rectangle getBounds() { return bounds;}

	void setLayerBounds(Rectangle bounds)
	{
		this->bounds = bounds;
		camera.offset = { bounds.width / 2.0f, bounds.height / 2.0f };
		camera.target = camera.offset;
	}

	bool checkButtonInput()
	{
		Vector2 worldMousePos = GetScreenToWorld2D(GetMousePosition(), camera);

		for (Button& b : buttons)
		{
			b.isHovered = CheckCollisionPointRec(worldMousePos, b.bounds);
			if (b.isHovered && b.isClicked(worldMousePos)) {
				input.button = b.val;
				return true;
			}
		}

		return false;
	}
};