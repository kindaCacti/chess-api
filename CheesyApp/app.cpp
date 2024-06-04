#include "app.h"
#include <stdexcept>

App::App() {
  if (initWindow(800, 800, "Say Cheeseee") == -1) {
    throw "Failed to initialize the app!";
  }
  ImageRect::initializeImageRects();
  initializeBoard();

  mainLoop();
}

void App::initializeBoard() {
  pieceElements.push_back(new AppElement<ImageRect>(
      new ImageRect("res/textures/board.png", 800, 800), false, true,
      marginLeft, 0));

  int pawnRows[2] = {1, 6};
  int figureRows[2] = {0, 7};
  for (int c = 0; c < 2; ++c) {
    std::string color(c == 0 ? "white" : "black");
    std::string path = std::string("res/textures/") + color;
    for (int x = 0; x < 8; ++x) {
      pieceElements.push_back(new AppElement<ImageRect>(
          new ImageRect(path + std::string("/Pawn.png"), 100, 100), false, true,
          marginLeft + 100 * x, pawnRows[c] * 100));
    }
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Rook.png"), 100, 100), false, true,
        marginLeft, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Rook.png"), 100, 100), false, true,
        marginLeft + 700, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Knight.png"), 100, 100), false, true,
        marginLeft + 100, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Knight.png"), 100, 100), false, true,
        marginLeft + 600, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Bishop.png"), 100, 100), false, true,
        marginLeft + 200, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Bishop.png"), 100, 100), false, true,
        marginLeft + 500, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Queen.png"), 100, 100), false, true,
        marginLeft + 300, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/King.png"), 100, 100), false, true,
        marginLeft + 400, figureRows[c] * 100));
  }
}

Position App::notationToPosition(char x, char y) const {
  return Position(int(x - 'a') * 100, int(y - '1') * 100);
}

void App::tick(double delta) {
  // for (auto element : staticElements) {
  //   element->tick(delta);
  // }
  // for (auto element : highlightElements) {
  //   element->tick(delta);
  // }
  for (auto element : pieceElements) {
    element->tick(delta);
  }
}

void App::draw() {
  // for (auto element : staticElements) {
  //   element->draw();
  // }
  // for (auto element : highlightElements) {
  //   element->draw();
  // }
  for (auto element : pieceElements) {
    element->draw();
  }
}

void App::mainLoop() {
  Renderer renderer;
  double lastTime = glfwGetTime();
  while (!glfwWindowShouldClose(window)) {
    double now = glfwGetTime();
    double delta = now - lastTime;
    lastTime = now;

    renderer.clear();

    tick(delta);
    draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

int App::initWindow(int width, int height, const char *title) {
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));

  return 0;
}

App::~App() {
  // for (auto element : staticElements) {
  //   delete element;
  // }
  // staticElements.clear();
  // for (auto element : highlightElements) {
  //   delete element;
  // }
  // highlightElements.clear();
  for (auto element : pieceElements) {
    delete element;
  }
  pieceElements.clear();
  ImageRect::deinitializeImageRects();
  glfwTerminate();
}