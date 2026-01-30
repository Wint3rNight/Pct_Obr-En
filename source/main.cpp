#include "Game.h"
#include <ene.h>

int main()
{
    Game* game = new Game();
    ene::Engine engine;
    engine.SetApplication(game);
    
    if (engine.Init(1280, 720))
    {
        engine.Run();
    }
    
    engine.Destroy();
    return 0;
}