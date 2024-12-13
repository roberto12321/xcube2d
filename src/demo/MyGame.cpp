#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(5), gameWon(false), box(5, 5, 30, 30) {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	
	
	gfx->useFont(font);
	
	gfx->setVerticalSync(true);

    for (int i = 0; i < numKeys; i++) {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
        k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
        gameKeys.push_back(k);
    }
	//Construct button here
	for (int i = 0; i < 25; i++) {

		button[i].hoverCornerTexture = texture = ResourceManager::loadTexture("res/button_hover_corner.png", SDL_COLOR_GRAY);
		button[i].clickCornerTexture = texture = ResourceManager::loadTexture("res/button_click_corner.png", SDL_COLOR_GRAY);
		button[i].idleCornerTexture = texture = ResourceManager::loadTexture("res/button_idle_corner.png", SDL_COLOR_GRAY);

		button[i].hoverXEdgeTexture = texture = ResourceManager::loadTexture("res/button_hover_x_edge.png", SDL_COLOR_GRAY);
		button[i].clickXEdgeTexture = texture = ResourceManager::loadTexture("res/button_click_x_edge.png", SDL_COLOR_GRAY);
		button[i].idleXEdgeTexture = texture = ResourceManager::loadTexture("res/button_idle_x_edge.png", SDL_COLOR_GRAY);

		button[i].hoverYEdgeTexture = texture = ResourceManager::loadTexture("res/button_hover_y_edge.png", SDL_COLOR_GRAY);
		button[i].clickYEdgeTexture = texture = ResourceManager::loadTexture("res/button_click_y_edge.png", SDL_COLOR_GRAY);
		button[i].idleYEdgeTexture = texture = ResourceManager::loadTexture("res/button_idle_y_edge.png", SDL_COLOR_GRAY);
		
		button[i].idleCentreTexture = texture = ResourceManager::loadTexture("res/button_idle_centre.png", SDL_COLOR_GRAY);
		button[i].hoverCentreTexture = texture = ResourceManager::loadTexture("res/button_hover_centre.png", SDL_COLOR_GRAY);
		button[i].clickCentreTexture = texture = ResourceManager::loadTexture("res/button_click_centre.png", SDL_COLOR_GRAY);

		//button[i].text = "Sample Text";
		//button[i].textColor = SDL_COLOR_BLACK;
		button[i].xPos = 50;
		button[i].yPos = 100;
		button[i].width = 392;
		button[i].cornerSize = 32;
		button[i].height = 96;	
	}
	


	

	//Construct slider here
	slider[0].sliderXPos = 100;
	slider[0].sliderYPos = 400;
	slider[0].sliderWidth = 300;
	slider[0].sliderHeight = 10;
	slider[0].circleRadius = 25;
	slider[0].currentValue = 10;
	slider[0].maxValue = 10;
	slider[0].sliderColor = SDL_COLOR_BLUE;
	slider[0].circleColor = SDL_COLOR_YELLOW;
	slider[0].valueColor = SDL_COLOR_GREEN;

	//Construct loading bar here
	loadingBar[0].loadingBarXPos = 300;
	loadingBar[0].loadingBarYPos = 600;
	loadingBar[0].loadingBarWidth = 400;
	loadingBar[0].loadingBarHeight = 100;
	loadingBar[0].currentValue = 50.0;
	loadingBar[0].maxValue = 100.0;
	loadingBar[0].backgroundColor = SDL_COLOR_BLUE;
	loadingBar[0].barColor = SDL_COLOR_YELLOW;
	loadingBar[0].valueColor = SDL_COLOR_GREEN;

	//Construct 

	
}

MyGame::~MyGame() {

}

void MyGame::handleKeyEvents() {
	int speed = 3;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
	}
	if (eventSystem->isJustPressed(Mouse::BTN_LEFT))
	{
		std::cout << "Amogus" << std::endl;
	}

	button[0].buttonState = eventSystem->CheckButtonCollision(button[0]);
	slider[0].currentValue = eventSystem->CheckSliderCollision(slider[0]);
}

void MyGame::update() {
	box.x += velocity.x;
	box.y += velocity.y;

	for (auto key : gameKeys) {
		if (key->isAlive && box.contains(key->pos)) {
			score += 200;
			key->isAlive = false;
			numKeys--;
		}
	}

	velocity.x = 0;
    velocity.y = 0;

	if (numKeys == 0) {
		gameWon = true;
	}
}

void MyGame::render() {
	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box);
	gfx->fillRect(50,50,50,50);
	
	//mySystem->HoverDetection

	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : gameKeys)
        if (key->isAlive)
		    gfx->drawCircle(key->pos, 5);
}

void MyGame::renderUI() {
	SDL_Rect rect = {0,0,1280,720};
	texture = ResourceManager::loadTexture("res/fantasy_background.jpg", SDL_COLOR_BLACK);
	gfx->drawTexture(texture, &rect);
	gfx->setDrawColor(SDL_COLOR_AQUA);
	//mySystem->DrawButton(100, 150, 50, 50);
	

	
	/*if (eventSystem->getMousePos().x > button.xPos &&
		eventSystem->getMousePos().x < button.xPos + button.width &&
		eventSystem->getMousePos().y > button.yPos &&
		eventSystem->getMousePos().y < button.yPos + button.height &&
		eventSystem->isPressed(BTN_LEFT))
	{
		button.color = SDL_COLOR_BLUE;
	}
	else if(eventSystem->getMousePos().x > button.xPos &&
		eventSystem->getMousePos().x < button.xPos + button.width &&
		eventSystem->getMousePos().y > button.yPos &&
		eventSystem->getMousePos().y < button.yPos + button.height)
	{
		
		button.color = SDL_COLOR_YELLOW;
	}
	else 
	{
		button.color = SDL_COLOR_GREEN;
	}*/
	
	gfx->DrawButton(button[0]);
	gfx->DrawSlider(slider[0]);
	gfx->DrawLoadingBar(loadingBar[0]);
	
	/*gfx->fillRect(button.xPos, button.yPos, button.width, button.height);

	gfx->setDrawColor(SDL_COLOR_BLACK);


	gfx->drawText(button.text, button.xPos, button.yPos);*/
	
}