#include "Editor.h"


void Editor::useAction(Action* action)
{
	action->redo(*lines);
	fStack.push(action);
}

void Editor::undo()
{
	if (fStack.size() < 1) return;
	fStack.top()->undo(*lines);
	bStack.push(fStack.top());
	fStack.pop();
}

void Editor::redo()
{
	if (bStack.size() < 1) return;
	bStack.top()->redo(*lines);
	fStack.push(bStack.top());
	bStack.pop();
}