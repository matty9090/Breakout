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

const int kScreenWidth = 640;
const int kScreenHeight = 520;
const int kBatWidth = 86;
const int kBatHeight = 26;

const float kBatSpeed = 300.f;

const string kGameName = "Breakout";
const string kMediaFolder = "res";
const EEngineType kEngineType = kTLX;

map<string, string> spriteIndex;
map<string, EKeyCode> keyMap;

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

		virtual void update(float dt) = 0;

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

		void update(float dt) {
			position = Vec<float>(position.x + velocity.x * dt, position.y + velocity.y * dt);
			spr->SetPosition(position.x, position.y);
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

		void update(float dt) {

		}

	private:
		I3DEngine *engine;
};

/* Ball */

class Ball : public DynamicObj {
	public:
		Ball(I3DEngine *e, Vec<float> p) {
			engine = e;
			position = p;
		}

		void update(float dt) {

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

			player = make_shared<Bat>(engine, Vec<float>(kScreenWidth / 2 - kBatWidth / 2, kScreenHeight - 2 * kBatHeight));
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

				player->setVel(Vec<float>()); // reset velocity

				handleEvents();

				float dt = engine->Timer();

				player->update(dt);
			}
		}

		void handleEvents() {
			if (engine->KeyHeld(keyMap["BatRight"]))
				player->setVel(Vec<float>(kBatSpeed, 0.0f));

			if (engine->KeyHeld(keyMap["BatLeft"]))
				player->setVel(Vec<float>(-kBatSpeed, 0.0f));
		}

	private:
		I3DEngine *engine;

		shared_ptr<Bat> player;
		vector<shared_ptr<Block>> blocks;
};

/* Entry point */

void main() {
	/* Initialise sprite index */
	
	spriteIndex["bat"] = "Bat.png";

	/* Initialise key map */

	keyMap["BatRight"] = Key_D;
	keyMap["BatLeft"] = Key_A;

	Breakout game;
	game.run();
}
