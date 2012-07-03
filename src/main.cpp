#include <iostream>
#include <stdio.h>
#include "SDL.h"

#include "globals.h"
#include "game.h"

using namespace std;

int main(int argc, char *argv[])
{
  //B2_NOT_USED(argc);
	//B2_NOT_USED(argv);

  fprintf(stderr, "Initializing SDL.\n");

  /* Initialise game */
  Game game;
  game.Init();
  game.SetWindowName("My Application");
  game.ResizeWindow(800, 640);

  /* Start game loop */
  while(game.IsRunning())
  {
    //Read input on new step
    input.ReadInput();
    game.Run();
  }

  /* Shutdown all subsystems */
  game.Shutdown();

  fprintf(stderr, "Quiting....\n");

  exit(0);
}
