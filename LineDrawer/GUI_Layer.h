#pragma once

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

	int clickedAction() { return val; };
};

struct GUI_Layer
{
	std::vector<Button> buttons;
	Camera2D camera = { 0 };
	Rectangle bounds;

	GUI_Layer(Rectangle bounds) : bounds(bounds) {
		camera.zoom = 1.0f;
	}

	virtual void drawLayer() {};
	virtual void loadLayer() {};
	virtual int handleInput() { return -1; };

	void setLayerBounds(Rectangle bounds)
	{
		this->bounds = bounds;
		camera.offset = { bounds.width / 2.0f, bounds.height / 2.0f };
		camera.target = camera.offset;
	}

	int checkButtonInput()
	{
		Vector2 tMousePos = GetMousePosition();
		tMousePos.x -= bounds.x;
		tMousePos.y -= bounds.y;

		for (Button& b : buttons)
		{
			b.isHovered = CheckCollisionPointRec(tMousePos, b.bounds);
			if (b.isHovered && b.isClicked(tMousePos)) return b.val;
		}

		return -1;
	}
};