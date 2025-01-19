#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__



#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


#include <string>


class MyEngineSystem {
	friend class XCube2Engine;
	private:

		




	public:
		
		
};

class Button {
	friend class XCube2Engine;
	private:
		
	public:
		int xPos;
		int yPos;
		int width;
		int height;
		int cornerSize;
		
		int buttonState;
		bool pressed;
		bool released;

		Mix_Chunk* buttonSound;

		SDL_Texture* textTexture;

		//9Slice textures
		SDL_Texture* hoverCornerTexture;
		SDL_Texture* clickCornerTexture;
		SDL_Texture* idleCornerTexture;

		SDL_Texture* hoverXEdgeTexture;
		SDL_Texture* clickXEdgeTexture;
		SDL_Texture* idleXEdgeTexture;

		SDL_Texture* hoverYEdgeTexture;
		SDL_Texture* clickYEdgeTexture;
		SDL_Texture* idleYEdgeTexture;

		SDL_Texture* hoverCentreTexture;
		SDL_Texture* clickCentreTexture;
		SDL_Texture* idleCentreTexture;
		
		
};

class Slider {
	friend class XCube2Engine;
private:


public:
	int sliderXPos;
	int sliderYPos;
	int sliderWidth;
	int sliderHeight;
	float currentValue;
	float maxValue;
	bool heldDown = false;
	SDL_Texture* baseTexture;
	SDL_Texture* fillTexture;
	SDL_Texture* notchTexture;
	SDL_Color valueColor;
	std::string valueText;

};

class LoadingBar {
	friend class XCube2Engine;

private:

public:
	int loadingBarXPos;
	int loadingBarYPos;
	int loadingBarWidth;
	int loadingBarHeight;
	float currentValue;
	int maxValue;
	SDL_Texture* fillTexture;
	SDL_Texture* coverTexture;
	SDL_Color valueColor;
	std::string valueText;

};

class NineSliceTexture {
	friend class XCube2Engine;

private:


public:
	SDL_Texture* cornerTexture;
	SDL_Texture* edgeXTexture;
	SDL_Texture* edgeYTexture;
	SDL_Texture* centreTexture;

};



#endif