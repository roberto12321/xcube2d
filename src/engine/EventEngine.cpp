#include "EventEngine.h"

EventEngine::EventEngine() : running(true) {
	for (int i = 0; i < Key::LAST; ++i) {
		keys[i] = false;
	}

	buttons[Mouse::BTN_LEFT] = false;
	buttons[Mouse::BTN_RIGHT] = false;
}

EventEngine::~EventEngine() {}

void EventEngine::pollEvents() {
	while (SDL_PollEvent(&event)) {
		if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat == 0) {
			updateKeys(event.key.keysym.sym, event.type == SDL_KEYDOWN);
		}

		if (event.type == SDL_QUIT) {
			keys[QUIT] = true;
		}

		buttons[Mouse::BTN_LEFT]  = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
		buttons[Mouse::BTN_RIGHT] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
	}
}

void EventEngine::updateKeys(const SDL_Keycode &key, bool keyDown) {
	Key index;

	switch (key) {
		case SDLK_RIGHT:	index = Key::RIGHT; break;
		case SDLK_d:		index = Key::D; break;
		case SDLK_LEFT:		index = Key::LEFT; break; 
		case SDLK_a:		index = Key::A; break;
		case SDLK_UP:		index = Key::UP; break;
		case SDLK_w:		index = Key::W; break;
		case SDLK_DOWN:		index = Key::DOWN; break;
		case SDLK_s:		index = Key::S; break;
		case SDLK_ESCAPE:	index = Key::ESC; break;
		case SDLK_SPACE:	index = Key::SPACE; break;
		default:
			return;	// we don't care about other keys, at least now
	}

	keys[index] = keyDown;
}

void EventEngine::setPressed(Key key) {
    keys[key] = true;
}

void EventEngine::setPressed(Mouse btn) {
    buttons[btn] = true;
}

bool EventEngine::isPressed(Key key) {
	return keys[key];
}

bool EventEngine::isPressed(Mouse btn) {
	return buttons[btn];
}

void EventEngine::setMouseRelative(bool b) {
	if (SDL_SetRelativeMouseMode(b ? SDL_TRUE : SDL_FALSE) < 0) {
#ifdef __DEBUG
		debug("Warning: SDL_SetRelativeMouseMode() isn't supported");
#endif
	}
}

Point2 EventEngine::getMouseDPos() {
	Point2 mouseDPos;
	SDL_GetRelativeMouseState(&mouseDPos.x, &mouseDPos.y);
	return mouseDPos;
}

Point2 EventEngine::getMousePos() {
	Point2 pos;
	SDL_GetMouseState(&pos.x, &pos.y);
	return pos;
}


//My code

//Button code

int EventEngine::CheckButtonCollision(Button button) {
	int output;
	if (getMousePos().x > button.xPos &&
		getMousePos().x < button.xPos + button.width &&
		getMousePos().y > button.yPos &&
		getMousePos().y < button.yPos + button.height &&
		isPressed(BTN_LEFT))
	{
		//Output one is when hovering and clicked
		output = 1;
	}

	else if (getMousePos().x > button.xPos &&
		getMousePos().x < button.xPos + button.width &&
		getMousePos().y > button.yPos &&
		getMousePos().y < button.yPos + button.height)
	{
		//Output two is when hovering and not clicked
		output = 2;
	}
	else 
	{
		//Output zero is when not hovered or clicked
		output = 0;
	}
	return output;
}

//Slider code

int EventEngine::CheckSliderCollision(Slider slider){
	int output;



	if (getMousePos().x > slider.sliderXPos &&
		getMousePos().x < slider.sliderXPos + slider.sliderWidth &&
		getMousePos().y > slider.sliderYPos &&
		getMousePos().y < slider.sliderYPos + slider.sliderHeight &&
		isPressed(BTN_LEFT))
	{
		//std::cout << "slider clicked" << std::endl;
		float mouseXValue = getMousePos().x - slider.sliderXPos;
		//std::cout << "mousexvalue" << mouseXValue << std::endl;
		output = std::ceil(((mouseXValue / slider.sliderWidth) * slider.maxValue) - 0.49);
		//std::cout << "slider clicked" << output << std::endl;
	}



	else
	{
		output = slider.currentValue;
	}

	return output;
}

//Event code

bool EventEngine::isJustPressed(Mouse btn) {
	
	if (isPressed(btn))
	{
		justPressedInt++;
		if (justPressedInt == 1) return true;	
	}
	else
	{
		justPressedInt = 0;
	}
	return false;
}
