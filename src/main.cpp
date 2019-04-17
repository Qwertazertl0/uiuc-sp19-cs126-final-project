#include "ofMain.h"
#include "ofApp.h"
#include "../resource.h"

//========================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
  ofGLFWWindowSettings settings;
  settings.windowMode = OF_WINDOW;
  settings.setSize(1440, 960);
  settings.resizable = false;
  settings.title = "DOT: A Visual Experience";
  settings.setPosition(glm::vec2(0, 38)); //title bar is 38 pixels
  ofCreateWindow(settings);

  //Icon code from https://forum.openframeworks.cc/t/how-to-get-rid-of-console-and-set-proper-app-icon/24227
  HWND hwnd = ofGetWin32Window();
  HICON hMyIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
  SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hMyIcon);

  ofRunApp(new ofApp());
}