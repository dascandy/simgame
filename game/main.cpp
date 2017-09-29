#include "Window.h"
#include "GameState.h"
#include "GameScene.h"
#include <unistd.h>

#ifdef _MSC_VER
#include "windows.h"

int main();

int __stdcall WinMain(HINSTANCE, HINSTANCE, char*, int) {
  return main();
}
#endif

int main() {
  Window win("TestWindow", 640, 480);
  GameState state;
  win.SetScene([&state]{ return new GameScene(&state); });
  win.MainLoop();
  win.SetScene([]{ return nullptr; });
}

