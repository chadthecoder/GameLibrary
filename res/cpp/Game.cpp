#include "Game.hpp"

#include <iostream>
// using namespace std;

// SDL_Texture *textLeftScore, *textRightScore;

Game::Game(std::string ip, char *sound) : /* socket_(this->io_context), send_buf({{0}}), */ mIsRunning(true), /*  mTicksCount(0), */ gameBall(1500.0f, 500.0f, -100.0f, 117.5f, 15, 15), leftPoints(0), rightPoints(0)
{
  // print the ref of io_context to show that it worked for now
  // this->io_context = io_context;
  this->ip = ip;
  this->sound = sound;
  std::string funny = "res/cpp/snd/diceRoll.mp3";
  const char *str = funny.c_str();
  // PlaySound(this->sound);
  PlaySound(str);

  // std::cout << &this->io_context << " " << ip << std::endl;
  // this->StartSend();
}

// ma_engine_uninit(&this->engine);
Game::~Game()
{
  ma_engine_uninit(&this->engine);
}

int Game::CreateWindow()
{
  /* Initialize the library */
  if (!glfwInit())
  {
    return -1;
  }

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(1366, 768, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  return 0;
}

std::string Game::InitGLEW()
{
  // Init glew
  if (glewInit() != GLEW_OK)
  {
    std::cout << "Error\n";
  }

  openglVersion =
      reinterpret_cast<const char *>(glGetString(GL_VERSION));

  return openglVersion;
}

int Game::PlaySound(const char *filePath)
{
  this->result = ma_engine_init(NULL, &this->engine);
  if (this->result != MA_SUCCESS)
  {
    std::cout << "you fucked up\n";
    return -1;
  }

  std::cout << this->result << " " << filePath << "\n";
  // const char *cstr = filePath.c_str();
  //   const char *cstr = filePath.data();
  //  std::cout << cstr << "\n";
  const char *testy = "snd/diceRoll.mp3";
  this->result = ma_engine_play_sound(&this->engine, filePath, NULL); // this->sound
  if (this->result != MA_SUCCESS)
  {
    std::cout << "you fucked up 2\n"
              << this->result //-7 == resource does not exist
              << "\n";
    return -1;
  }

  // ma_engine_uninit(&this->engine);
  std::cout << "you good\n";
  return 0;
}

/* void Game::StartSend()
{
  udp::resolver resolver(this->io_context);
  std::cout << this->ip << std::endl;
  this->receiver_endpoint =
      *resolver.resolve(udp::v4(), this->ip, "1024").begin();

  this->socket_.open(udp::v4());

  this->socket_.send_to(boost::asio::buffer(this->send_buf), this->receiver_endpoint);
  std::cout << "0 buff sent to server" << std::endl;
  StartReceive();
}

void Game::StartReceive()
{
  std::cout << "In startreceive\n"
            << std::endl;
  this->len = socket_.receive_from(
      boost::asio::buffer(this->recv_buf), this->sender_endpoint);
  std::cout << "lh[dshlfihdsilfhl;ds\n"
            << len << "\n"
            << std::endl;

  std::cout.write(recv_buf.data(), len);
} */

void Game::centerVector2(Vector2 vec)
{
  vec.x = this->screenWidth / 2;
  vec.y = this->screenHeight / 2;
}

bool Game::Initialize()
{
  CreateWindow();
  InitGLEW();
  this->thickness = this->screenWidth / 100;
  this->paddleHeight = this->thickness * 6;
  this->paddleU.height = paddleHeight;
  this->paddleWidth = this->thickness;
  this->paddleU.width = this->paddleWidth;

  /* Making it fullscreen only is the only non complicated way   *
   * to make it look good on Ubuntu because of Ubuntu's top bar. */
  /*   this->mWindow = SDL_CreateWindow(
        "Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->screenWidth,
        this->screenHeight,
        SDL_WINDOW_FULLSCREEN);

    if (!this->mWindow)
    {
      SDL_Log("Error: %s", SDL_GetError());
      return false;
    }

    // make window icon
    SDL_Surface *icon = IMG_Load("pongIcon.png");

    if (!icon)
    {
      std::cout << "icon failed/n" << std::endl;
      // return error? or should be break?
      return 1;
    }

    SDL_SetWindowIcon(mWindow, icon);

    mRenderer = SDL_CreateRenderer(
        this->mWindow,
        -1,
        SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);

    if (!mRenderer)
    {
      SDL_Log("Failed to create renderer: %s", SDL_GetError());
      return false;
    } */

  // mBallPos.x = this->screenWidth / 2;
  // mBallPos.y = this->screenHeight / 2;
  // this->centerVector2(this->mBallPos);
  gameBall.x = this->screenWidth / 2;
  gameBall.y = this->screenHeight / 2;

  paddleU.x = this->screenWidth / 16;
  paddleU.y = this->screenHeight / 2;

  // funny.x = this->screenWidth * 15 / 16;
  // funny.y = this->screenHeight / 2;

  // keep this and remove initalize objects function?
  this->funny = this->createPaddle(
      this->screenWidth * 15 / 16, // static_cast<int>(paddleU.x - this->thickness / 2),
      this->screenHeight / 2,      // static_cast<int>(paddleU.y - this->thickness / 2),
      this->paddleU.width,
      this->paddleU.height,
      0);

  // scorekeeper?

  rectLeftSrc.h = 32;
  rectLeftSrc.w = 32;
  rectLeftSrc.x = 50;
  rectLeftSrc.y = 50;

  rectScoreLine = {
      static_cast<int>(100),
      static_cast<int>(65),
      20,
      5};

  rectRightSrc.h = 32;
  rectRightSrc.w = 32;
  rectRightSrc.x = 130;
  rectRightSrc.y = 50;

  return true;
}

void Game::Shutdown()
{
  /*   SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit(); */
}

void Game::RunLoop()
{
  while (this->mIsRunning)
  {
    this->ProcessInput();
    if (!this->UpdateGame())
    {
      break;
    }
    this->Render();
    if (glfwWindowShouldClose(this->window))
      this->mIsRunning = false;
  }
}

void Game::UpdateScore()
{
  // this->leftPoints, this->rightPoints

  std::string fileLeft = "assets/imgs/num" + std::to_string(this->leftPoints) + ".png";
  std::string fileRight = "assets/imgs/num" + std::to_string(this->rightPoints) + ".png";
  /*
    SDL_Surface *surfaceLeftScore = IMG_Load(fileLeft.c_str());
    textLeftScore = SDL_CreateTextureFromSurface(mRenderer, surfaceLeftScore);
    SDL_FreeSurface(surfaceLeftScore);

    SDL_Surface *surfaceRightScore = IMG_Load(fileRight.c_str());
    textRightScore = SDL_CreateTextureFromSurface(mRenderer, surfaceRightScore);
    SDL_FreeSurface(surfaceRightScore); */
}

void Game::ProcessInput()
{
  /* while (SDL_PollEvent(&this->event))
  {
    switch (this->event.type)
    {
    case SDL_QUIT:
      mIsRunning = false;
      break;
    }
  }

  const Uint8 *state = SDL_GetKeyboardState(NULL);

  if (state[SDL_SCANCODE_ESCAPE])
  {
    mIsRunning = false;
  }

  // paddle direction
  this->paddleU.direction = 0;
  if (state[SDL_SCANCODE_W])
  {
    this->paddleU.direction -= 1;
  }

  if (state[SDL_SCANCODE_S])
  {
    this->paddleU.direction += 1;
  }

  // paddle2, funny
  this->funny.direction = 0;
  if (state[SDL_SCANCODE_I])
  {
    this->funny.direction -= 1;
  }

  if (state[SDL_SCANCODE_K])
  {
    this->funny.direction += 1;
  } */
  glfwPollEvents();
}

bool Game::UpdateGame()
{
  /* while (!SDL_TICKS_PASSED(SDL_GetTicks(), this->mTicksCount + 16))
    ;

  this->deltaTime = (SDL_GetTicks() - this->mTicksCount);
  this->mTicksCount = SDL_GetTicks(); */
  if (this->deltaTime > 0.05f)
  {
    this->deltaTime = 0.05f;
  }

  this->UpdateScore();

  return true;
}

Paddle Game::createPaddle(float xq, float yq, int widthq, int heightq, int directionq)
{
  Paddle mPaddle;
  mPaddle.x = xq;
  mPaddle.y = yq;
  mPaddle.width = widthq;
  mPaddle.height = heightq;
  mPaddle.direction = directionq;
  return mPaddle;
}

void Game::drawPaddle(Paddle mPaddle)
{
  Rectangle rectMPaddle{
      static_cast<int>(mPaddle.x - (mPaddle.width / 2.0f)),
      static_cast<int>(mPaddle.y - (mPaddle.height / 2.0f)),
      mPaddle.width,
      mPaddle.height};
  // SDL_RenderFillRect(this->mRenderer, &rectMPaddle);
}

Rectangle Game::createPaddleU()
{
  Rectangle myPaddle{
      static_cast<int>(paddleU.x - (paddleU.width / 2.0f)),
      static_cast<int>(paddleU.y - (paddleU.height / 2.0f)),
      this->paddleU.width,
      this->paddleU.height};
  return myPaddle;
}
void Game::drawPaddleU(Rectangle myPaddle)
{
  // SDL_RenderFillRect(this->mRenderer, &myPaddle);
}

void Game::Render()
{
  // renderer, rgba; black
  /*   SDL_SetRenderDrawColor(
        this->mRenderer,
        0,
        0,
        0,
        255); */

  // draw scene

  // background
  // SDL_RenderClear(this->mRenderer);

  // white for walls
  /* SDL_SetRenderDrawColor(
      this->mRenderer,
      255,
      255,
      255,
      255); */
  Rectangle wall_left{
      0,
      0,
      this->thickness,
      this->screenHeight};
  Rectangle wall_right{
      this->screenWidth - (this->thickness),
      0,
      this->thickness,
      this->screenHeight};
  Rectangle wall_top{
      0,
      0,
      this->screenWidth,
      this->thickness};
  Rectangle wall_bottom{
      0,
      this->screenHeight - (this->thickness),
      this->screenWidth,
      this->thickness};
  /*  SDL_RenderFillRect(this->mRenderer, &wall_left);
   SDL_RenderFillRect(this->mRenderer, &wall_right);
   SDL_RenderFillRect(this->mRenderer, &wall_top);
   SDL_RenderFillRect(this->mRenderer, &wall_bottom);

   SDL_RenderFillRect(this->mRenderer, &rectScoreLine); */

  // create sdl rect for ball
  Rectangle ball{
      static_cast<int>(gameBall.x - (gameBall.width / 2.0f)),
      static_cast<int>(gameBall.y - (gameBall.height / 2.0f)),
      gameBall.width,
      gameBall.height};
  // fill sdl rect info into render
  //  SDL_RenderFillRect(this->mRenderer, &ball);

  /*//sdl drawing test
  Rectangle ball2{
      static_cast<int>(0),
      static_cast<int>(0),
      100,
      100};
  SDL_RenderFillRect(this->mRenderer, &ball2);
  */

  Rectangle myPaddle = this->createPaddleU();
  this->drawPaddleU(myPaddle);

  // this->funny.x += 5;
  this->drawPaddle(this->funny);

  /*   SDL_RenderCopy(mRenderer, textLeftScore, NULL, &rectLeftSrc);
    SDL_RenderCopy(mRenderer, textRightScore, NULL, &rectRightSrc);

    SDL_RenderPresent(this->mRenderer); */
}
