#include <iostream>
#include <stdio.h>

#include "globals.h"
#include "engine.h"
#include "Box2D/Box2D.h"

using namespace std;

int main(int argc, char *argv[]) {
  B2_NOT_USED(argc);
	B2_NOT_USED(argv);

  /* Initialise game */
  Engine engine(800, 640, "My Tests", false, 60, false);
  engine.Init();
  
  //JS.SetWorld();

  /* Start game loop */
  while(engine.IsRunning()) {
    //Read input on new step
    input.ReadInput();
    engine.Run();
  }

  /* Shutdown all subsystems */
  engine.Shutdown();

  fprintf(stderr, "Quiting....\n");

  exit(0);
}
