#include <iostream>
#include <stdio.h>

#include "globals.h"
#include "game_test.h"

using namespace std;

int main(int argc, char *argv[]) {
  //B2_NOT_USED(argc);
	//B2_NOT_USED(argv);

  /* Initialise game */
  GameTest game(800, 640, "My Game", false);
  game.Init();

  /* Start game loop */
  while(game.IsRunning()) {
    //Read input on new step
    input.ReadInput();
    game.Run();
  }

  /* Shutdown all subsystems */
  game.Shutdown();

  fprintf(stderr, "Quiting....\n");

  exit(0);
}
