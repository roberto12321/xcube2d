#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__



#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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
		int cornerSize;
		int height;
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

		//SDL_Color textColor;
		//std::string text;
		int buttonState;
		
};

class Slider {
	friend class XCube2Engine;
private:


public:
	int sliderXPos;
	int sliderYPos;
	int sliderWidth;
	int sliderHeight;
	//Point2 circleCentre;
	int circleRadius;
	int currentValue;
	int maxValue;
	SDL_Color sliderColor;
	SDL_Color circleColor;
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
	float maxValue;
	SDL_Color backgroundColor;
	SDL_Color barColor;
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