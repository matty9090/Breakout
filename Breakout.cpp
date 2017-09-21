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

const int kScreenWidth = 750;
const int kScreenHeight = 560;

const int kBatWidth = 86;
const int kBatHeight = 26;

const int kBlockWidth = 64;
const int kBlockHeight = 32;

const int kBallRadius = 8;
const int kNumBlocks = 7;
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
	Vec(T _x, T _y) { x = _x, y = _y; }
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

/* Ball */

class Ball : public DynamicObj {
	public:
		Ball(I3DEngine *e, Vec<float> p) {
			engine = e;
			position = p;

			velocity = Vec<float>(0, -150.f);

			spr = engine->CreateSprite(spriteIndex["ball"], position.x, position.y);
		}

		void update(float dt) {
			position = Vec<float>(position.x + velocity.x * dt, position.y + velocity.y * dt);
			spr->SetPosition(position.x, position.y);
		}

		float getRadius() { return radius; }

	private:
		I3DEngine *engine;
		ISprite *spr;

		float radius;
};

/* Destructable Block */

class Block : public DynamicObj {
	public:
		Block(I3DEngine *e, Vec<float> p, int blockType) {
			engine = e;
			position = p;

			spr = engine->CreateSprite(spriteIndex["block" + to_string(blockType)], position.x, position.y);
		}

		void update(float dt) {

		}

		bool collided(shared_ptr<Ball> ball) {

		}
		
	private:
		I3DEngine *engine;
		ISprite *spr;
};

/* Game class */

class Breakout {
	public:
		Breakout() {
			engine = New3DEngine(kEngineType);

			setupEngine();
			addBlocks();

			player = make_shared<Bat>(engine, Vec<float>(kScreenWidth / 2 - kBatWidth / 2, kScreenHeight - 2 * kBatHeight));
			ball = make_shared<Ball>(engine, Vec<float>(kScreenWidth / 2 - kBallRadius / 2, player->getPos().y - 80));
		}

		void setupEngine() {
			engine->StartWindowed(kScreenWidth, kScreenHeight);
			engine->SetWindowCaption(kGameName);
			engine->AddMediaFolder(kMediaFolder);
		}

		void addBlocks() {
			for (int y = 0; y < 7; y++) {
				for (int x = 0; x < 10; x++) {
					Vec<float> position(10 + x * (kBlockWidth + 10), 10 + y * (kBlockHeight + 10));

					shared_ptr<Block> block = make_shared<Block>(engine, position, y);
					
					blocks.push_back(block);
				}
			}
		}

		void run() {
			while (engine->IsRunning()) {
				engine->DrawScene();

				player->setVel(Vec<float>()); // reset velocity

				handleEvents();

				float dt = engine->Timer();

				player->update(dt);
				ball->update(dt);
			}
		}

		void handleEvents() {
			if (engine->KeyHeld(keyMap["BatRight"]))
				player->setVel(Vec<float>(kBatSpeed, 0.0f));

			if (engine->KeyHeld(keyMap["BatLeft"]))
				player->setVel(Vec<float>(-kBatSpeed, 0.0f));

			if (engine->KeyHit(keyMap["ExitGame"]))
				engine->Stop();
		}

	private:
		I3DEngine *engine;

		shared_ptr<Bat> player;
		shared_ptr<Ball> ball;

		vector<shared_ptr<Block>> blocks;
};

/* Entry point */

void main() {
	/* Initialise sprite index */
	
	spriteIndex["bat"] = "Bat.png";
	spriteIndex["ball"] = "TinyBall.png";

	for(int i = 0; i < kNumBlocks; i++)
		spriteIndex["block" + to_string(i)] = "Block" + to_string(i + 1) + ".png";

	/* Initialise key map */

	keyMap["ExitGame"] = Key_Escape;
	keyMap["BatRight"] = Key_D;
	keyMap["BatLeft"] = Key_A;

	Breakout game;
	game.run();
}
