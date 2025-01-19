#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"

struct GameKey {
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame {
	private:
		Rect box;
		Button button[25];
		Slider slider[25];
		LoadingBar loadingBar[25];
		int scene;
		int lastScene;
		int offset;
		int musicVolume;
		int sfxVolume;
		int time = 0;
		int turnEndTime;
		int turn = 1;
		int lastMusicPlay = 0;
		int turnDuration = 50;
		//int lastScene;


		Vector2i velocity;
		SDL_Texture * bgTexture;
		SDL_Texture* playerTexture;
		SDL_Texture* enemyTexture;
		Mix_Chunk* music;
		std::vector<std::shared_ptr<GameKey>> gameKeys;

		/* GAMEPLAY */
		int score, numKeys, lives;
		bool gameWon;

		void handleKeyEvents();
		void update();
		void render();
		void renderUI();
		
	public:
        MyGame();
		~MyGame();

};

#endif