// Breakout - UCLan Game
// Nathan Williams, Jack Hamilton, Matthew Lowe

#include <TL-Engine.h>

#include <string>

using namespace tle;
using namespace std;

/* Constants */

const int kScreenWidth = 1024;
const int kScreenHeight = 768;

const string kMediaFolder = "res";
const EEngineType kEngineType = kTLX;

/* Player/Bat */

class Bat {
	public:


	private:

};

/* Game class */

class Breakout {
	public:
		Breakout() {
			engine = New3DEngine(kEngineType);

			setupEngine();
		}

		void setupEngine() {
			engine->StartWindowed(kScreenWidth, kScreenHeight);
			engine->AddMediaFolder(kMediaFolder);
		}

		void run() {
			while (engine->IsRunning()) {
				engine->DrawScene();
			}
		}

	private:
		Bat player;
		I3DEngine *engine;
};

/* Entry point */

void main() {
	Breakout game;

	game.run();
}
