#ifndef GAME_H
#define GAME_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "libsWin\glew\include\GL\glew.h"
#include "libsWin\glfw\include\GLFW\glfw3.h"
#include "libsWin\SDL2\i686-w64-mingw32\include\SDL2\SDL.h"
#include "libsWin\SDL2_image-2.0.3\i686-w64-mingw32\include\SDL2\SDL_image.h"
#else
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#endif

#include "Rectangle.hpp"
#include "Ball.hpp"

#include "miniaudio.h"

#include <string>
#include <iostream>
#include <cmath>

/* #define ASIO_STANDALONE
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

 #include "asio/include/asio.hpp"

using asio::ip::udp;
 */
struct Vector2
{
  float x, y;
  Vector2() {}
  Vector2(float x, float y)
  {
    this->x = x;
    this->y = y;
  }
};

class Game
{
public:
  Game(std::string ip, char *sound);
  ~Game();
  bool Initialize();
  void RunLoop();
  void Shutdown();

private:
  int CreateWindow();     // creates glfw window
  std::string InitGLEW(); // returns opengl version
  int PlaySound(const char *filePath);
  void ProcessInput();
  bool UpdateGame();
  void Render();
  void UpdateScore();
  // void StartSend();
  // void StartReceive();

  void centerVector2(Vector2 vec);

  Paddle createPaddle(float x, float y, int width, int height, int direction);
  void drawPaddle(Paddle mPaddle);

  Rectangle createPaddleU();
  void drawPaddleU(Rectangle myPaddle);

  GLFWwindow *window;
  std::string openglVersion;

  Rectangle rectLeftSrc, rectRightSrc, rectDest;

  ma_result result;
  ma_engine engine;
  char *sound;

  // SDL_Window *mWindow;
  // SDL_Renderer *mRenderer;
  Paddle paddleU, funny;
  Ball gameBall;
  // Uint32 mTicksCount;
  // SDL_DisplayMode DM;
  // SDL_Event event;
  float deltaTime;
  bool mIsRunning;
  int screenHeight, screenWidth, thickness, paddleWidth, paddleHeight;
  int testyFunny = 400, leftPoints = 0, rightPoints = 0;
  Rectangle rectScoreLine;
  // asio::io_context io_context;
  std::string ip;
  // udp::socket socket_;
  // array<char, 1> send_buf;
  // udp::endpoint receiver_endpoint;
  //  boost::array<char, 128> recv_buf;
  // asio::ip::udp::endpoint sender_endpoint;
  // size_t len;
};

#endif // GAME_H