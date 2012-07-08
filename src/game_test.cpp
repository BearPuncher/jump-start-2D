#include "game_test.h"
#include "entity.h"
#include "graphic.h"

using namespace std;
using namespace geometry;

GameTest::GameTest() : Game() {
  game_status_ = GameTest::GAME_RUNNING;
}

GameTest::GameTest(int screen_width, int screen_height, 
           std::string window_name, bool full_screen) :
Game(screen_width, screen_height, window_name, full_screen) {
  game_status_ = GameTest::GAME_RUNNING;
}
