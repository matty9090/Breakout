// Breakout - UCLan Game
// Nathan Williams, Jack Hamilton, Matthew Lowe

#include <TL-Engine.h>

#include <string>
#include <vector>
#include <memory>
#include <map>

using namespace tle;
using namespace std;

/* Constants */

const int kScreenWidth = 1024;
const int kScreenHeight = 768;

const string kGameName = "Breakout";
const string kMediaFolder = "res";
const EEngineType kEngineType = kTLX;

map<string, string> spriteIndex;

/* 2D Vector */

template <class T> struct Vec {
	T x;
	T y;

	Vec() { x = 0; y = 0; }
	Vec(T u, T v) { x = u, y = v; }
};

/* Object with position + velocity */

class DynamicObj {
	public:
		Vec<float> getPos() { return position; }
		Vec<float> getVel() { return velocity; }

		void setPos(Vec<float> p) { position = p; }
		void setVel(Vec<float> v) { velocity = v; }

	protected:
		Vec<float> position;
		Vec<float> velocity;
};

/* Player/Bat */

class Bat : public DynamicObj {
	public:
		Bat(I3DEngine *e, Vec<float> p) {
			engine = e;
			position = p;

			spr = engine->CreateSprite(spriteIndex["bat"], position.x, position.y);
		}

	private:
		I3DEngine *engine;
		ISprite *spr;
};

/* Destructable Block */

class Block : public DynamicObj {
	public:
		Block(I3DEngine *e, Vec<float> p) {
			engine = e;
			position = p;
		}

	private:
		I3DEngine *engine;
};

/* Game class */

class Breakout {
	public:
		Breakout() {
			engine = New3DEngine(kEngineType);

			setupEngine();
			addBlocks();

			player = make_shared<Bat>(engine, Vec<float>(10, 10));
		}

		void setupEngine() {
			engine->StartWindowed(kScreenWidth, kScreenHeight);
			engine->SetWindowCaption(kGameName);
			engine->AddMediaFolder(kMediaFolder);
		}

		void addBlocks() {

		}

		void run() {
			while (engine->IsRunning()) {
				engine->DrawScene();
			}
		}

	private:
		I3DEngine *engine;

		shared_ptr<Bat> player;
		vector<shared_ptr<Block>> blocks;
};

/* Entry point */

void main() {
	spriteIndex["bat"] = "Bat.png";

	Breakout game;
	game.run();
}
