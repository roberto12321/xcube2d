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
	//Initialize scene value
	scene = 1;

	//Assign textures
	bgTexture = ResourceManager::loadTexture("res/fantasy_background.jpg", SDL_COLOR_BLACK);
	playerTexture = ResourceManager::loadTexture("res/player.png", SDL_COLOR_BLACK);
	enemyTexture = ResourceManager::loadTexture("res/enemy.png", SDL_COLOR_BLACK);

	//Button
	for (int i = 0; i < 9; i++) {

		button[i].hoverCornerTexture = ResourceManager::loadTexture("res/button_hover_corner.png", SDL_COLOR_GRAY);
		button[i].clickCornerTexture = ResourceManager::loadTexture("res/button_click_corner.png", SDL_COLOR_GRAY);
		button[i].idleCornerTexture = ResourceManager::loadTexture("res/button_idle_corner.png", SDL_COLOR_GRAY);

		button[i].hoverXEdgeTexture = ResourceManager::loadTexture("res/button_hover_x_edge.png", SDL_COLOR_GRAY);
		button[i].clickXEdgeTexture = ResourceManager::loadTexture("res/button_click_x_edge.png", SDL_COLOR_GRAY);
		button[i].idleXEdgeTexture = ResourceManager::loadTexture("res/button_idle_x_edge.png", SDL_COLOR_GRAY);

		button[i].hoverYEdgeTexture = ResourceManager::loadTexture("res/button_hover_y_edge.png", SDL_COLOR_GRAY);
		button[i].clickYEdgeTexture = ResourceManager::loadTexture("res/button_click_y_edge.png", SDL_COLOR_GRAY);
		button[i].idleYEdgeTexture = ResourceManager::loadTexture("res/button_idle_y_edge.png", SDL_COLOR_GRAY);
		
		button[i].idleCentreTexture = ResourceManager::loadTexture("res/button_idle_centre.png", SDL_COLOR_GRAY);
		button[i].hoverCentreTexture = ResourceManager::loadTexture("res/button_hover_centre.png", SDL_COLOR_GRAY);
		button[i].clickCentreTexture = ResourceManager::loadTexture("res/button_click_centre.png", SDL_COLOR_GRAY);
		button[i].textTexture = ResourceManager::loadTexture("res/button_text_" + std::to_string(i) + ".png", SDL_COLOR_GRAY);
		button[i].buttonSound = ResourceManager::loadSound("res/Audio/click.wav");
		
		button[i].cornerSize = 32;
		button[i].xPos = 0;
		button[i].yPos = 0;
		button[i].width = 512;
		button[i].height = 128;	
	}

	music = ResourceManager::loadSound("res/Audio/synth.wav");

	//Button positions
	//Scene 1
	for (int i = 0; i < 3; i++)
	{
		button[i].xPos = 384;
		button[i].yPos = 120 + (i * 160);

	}
	//Scene 2
	for (int i = 0; i < 4; i++)
	{
		offset = 7;
		button[i + offset].xPos = 85 + (i * 597);
		button[i + offset].yPos = 537;
	}
	//Scene 3
	offset = 6;
	button[offset].xPos = 718;
	button[offset].yPos = 542;
	
	//Scene 4
	for (int i = 0; i < 3; i++)
	{
		offset = 3;
		button[i + offset].xPos = 384;
		button[i + offset].yPos = 120 + (i * 160);

	}
	
	//Slider
	for (int i = 0; i < 2; i++)
	{
		slider[i].sliderXPos = 384;
		slider[i].sliderYPos = 192 + (i * 128);
		slider[i].sliderWidth = 512;
		slider[i].sliderHeight = 32;
		slider[i].currentValue = 100;
		slider[i].maxValue = 100;
		slider[i].valueColor = SDL_COLOR_WHITE;
		slider[i].baseTexture = ResourceManager::loadTexture("res/slider_base.png", SDL_COLOR_GRAY);
		slider[i].fillTexture = ResourceManager::loadTexture("res/slider_fill.png", SDL_COLOR_GRAY);
		slider[i].notchTexture = ResourceManager::loadTexture("res/slider_notch.png", SDL_COLOR_GRAY);

	}
	//Loading bar
	for (int i = 0; i < 2; i++)
	{
		loadingBar[i].loadingBarXPos = 256 + (i * 512);
		loadingBar[i].loadingBarWidth = 256;
		loadingBar[i].loadingBarHeight = 64;
		loadingBar[i].currentValue = 50.0;
		loadingBar[i].loadingBarYPos = 422;
		loadingBar[i].maxValue = 100.0;
		loadingBar[i].fillTexture = ResourceManager::loadTexture("res/loading_bar_fill.png", SDL_COLOR_GRAY);
		loadingBar[i].coverTexture = ResourceManager::loadTexture("res/loading_bar_cover.png", SDL_COLOR_GRAY);
		loadingBar[i].valueColor = SDL_COLOR_WHITE;
	}
	

	
}

MyGame::~MyGame() {

}

void MyGame::handleKeyEvents() {
	
	//Set volume
	musicVolume = slider[0].currentValue;
	sfxVolume = slider[1].currentValue;
	
	//Scenes
	switch (scene) {
	case 1:
		//Menu Scene
		for (int i = 0; i < 3; i++) {
			button[i].buttonState = eventSystem->CheckButtonCollision(button[i]);
		}
		if (button[0].buttonState == 1)
		{
			//Reset values of combat scene
			for (int i = 0; i < 2; i++) 
			{
				loadingBar[i].currentValue = loadingBar[i].maxValue;
			}
			turn = 1;
			scene = 2;
			
			
		}
		if (button[1].buttonState == 1)
		{
			scene = 3;
			lastScene = 1;	
		}
		if (button[2].buttonState == 1)
		{
			running = false;	
		}
		break;
	case 2:
		//Combat Scene
		offset = 7;
		if (turnEndTime < time && (loadingBar[0].currentValue <= 0 || loadingBar[1].currentValue <= 0))
		{
			scene = 1;
		}

		for (int i = 0; i < 2; i++) {
			button[i + offset].buttonState = eventSystem->CheckButtonCollision(button[i + offset]);
		
		}
		if (button[offset].buttonState == 1 && turnEndTime < time)
		{
			turnEndTime = time + turnDuration;
			loadingBar[1].currentValue = loadingBar[1].currentValue - 11;
		}
		if (button[offset + 1].buttonState == 1 && turnEndTime < time)
		{
			turnEndTime = time + turnDuration;	
			loadingBar[0].currentValue = loadingBar[0].currentValue + 13;
		}
		if (turnEndTime == time)
		{
			loadingBar[0].currentValue = loadingBar[0].currentValue - 9;
			turn += 1;
		}
		if (eventSystem->isPressed(Key::ESC) && turnEndTime < time ) {
			scene = 4;
		}
		break;
	case 3:
		//Options menu scene
		offset = 6;
		button[offset].buttonState = eventSystem->CheckButtonCollision(button[offset]);
		if (button[offset].buttonState == 1)
		{
			scene = lastScene;
			
		}
		for (int i = 0; i < 2; i++) 
		{
			slider[i].currentValue = eventSystem->CheckSliderCollision(slider[i]);
		}
	
		break;
	case 4:
		//Pause menu scene
		offset = 3;
		for (int i = 0; i < 3; i++) {
			button[i + offset].buttonState = eventSystem->CheckButtonCollision(button[i + offset]);
		}
		if (button[offset].buttonState == 1)
		{
			scene = 2;
			
		}
		if (button[offset + 1].buttonState == 1)
		{
			lastScene = 4;
			scene = 3;
			
		}
		if (button[offset + 2].buttonState == 1)
		{
			scene = 1;
			
		}
		break;
	}
	for (int i = 0; i < 9; i++) {
		if (button[i].buttonState == 1)
		{
			sfx->PlayButtonSound(button[i], sfxVolume);
			button[i].buttonState = 0;
		}
	}
	
}

void MyGame::update() {
	time += 1;

	if (lastMusicPlay + 350 < time)
	{
		lastMusicPlay = time;
		sfx->PlayMusic(music, musicVolume);
	}

}

void MyGame::render() {
	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box);
	gfx->fillRect(50,50,50,50);
	

	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : gameKeys)
        if (key->isAlive)
		    gfx->drawCircle(key->pos, 5);
}

void MyGame::renderUI() {

	//Background
	SDL_Rect bgRect = { 0,0,1280,720 };
	gfx->drawTexture(bgTexture, &bgRect);
	
	
	SDL_Rect playerRect = { 256,132,256,256 };
	SDL_Rect enemyRect = { 768,132,256,256 };
	//Scenes
	std::string turnText = "Turn: " + std::to_string(turn);
	switch (scene) {
	case 1:
		for (int i = 0; i < 3; i++) {
			gfx->DrawButton(button[i]);
		}
		break;
	case 2:
		offset = 7;
		
		gfx->drawText(turnText, 540, 0);
		for (int i = 0; i < 2; i++) {
			
			gfx->DrawButton(button[i + offset]);
		}
		gfx->drawTexture(playerTexture, &playerRect);
		gfx->drawTexture(enemyTexture, &enemyRect);
		for (int i = 0; i < 2; i++) {
			gfx->DrawLoadingBar(loadingBar[i]);
		}
		
		break;
	case 3:
		offset = 6;
		for (int i = 0; i < 2; i++) {
			gfx->DrawSlider(slider[i]);
		}
		gfx->DrawButton(button[offset]);
		break;
	case 4:
		for (int i = 0; i < 3; i++) {
			offset = 3;
			gfx->DrawButton(button[i + offset]);
		}
		break;
	
	}

	
	std::string sceneText = "Scene: " + std::to_string(scene);
	gfx->drawText(sceneText, 0, 0);
	
	
}
