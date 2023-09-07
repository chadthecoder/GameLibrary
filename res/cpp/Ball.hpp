#ifndef BALL_H
#define BALL_H

struct Paddle
{
    float x, y;
    int width, height, direction;
};

class Ball
{
public:
    Ball(float x, float y, float xVel, float yVel, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->xVelocity = xVel;
        this->yVelocity = xVel;
        this->width = width;
        this->height = height;
    }

    /*bool collidesWith(Ball ball)
    {
      int xDist = abs(ball.x - this->x);
      int yDist = abs(ball.y - this->y);
      int actualDist = sqrt(pow(xDist, 2) + pow(yDist, 2));
      //std::cout << "yeeeeeeeeet" << actualDist << std::endl;
      if(actualDist<60)
      {
        std::cout << "collision\n";
        return true;
      }
      return false;
    }*/

    bool collidesWith(Paddle paddle)
    {

        // new collision detection method?
        // fix to work so mattter what side of the paddle it hits?

        // Did we intersect with the paddle?
        float diff = paddle.y - this->y;
        // Take absolute value of difference
        diff = (diff > 0.0f) ? diff : -diff;
        if (
            // Our y-difference is small enough
            diff <= paddle.height / 2.0f &&
            // We are in the correct x-position, this needs changing to be able to work with any paddle as opposed to hard coding for every paddle
            (
                this->x <= paddle.x + (paddle.width / 2) && this->x >= (paddle.x + (paddle.width / 2) - 5.0f)) &&
            // The ball is moving to the left
            this->xVelocity < 0.0f)
        {
            this->xVelocity *= -1.0f;
        }
        else if (
            // Our y-difference is small enough
            diff <= paddle.height / 2.0f &&
            // We are in the correct x-position, this needs changing to be able to work with any paddle as opposed to hard coding for every paddle
            (
                // this->x <= paddle.x-(paddle.width/2) && this->x >= (paddle.x-(paddle.width/2)-5.0f)
                this->x >= paddle.x - (paddle.width / 2) && this->x <= (paddle.x - (paddle.width / 2) + 5.0f)) &&
            // The ball is moving to the right
            this->xVelocity > 0.0f)
        {
            this->xVelocity *= -1.0f;
        }

        // old collision detection way, find new way that works no matter what direction the ball hits the paddle?
        /*bool test1 = false, test2 = false, test3 = false, test4 = false;
        if((paddle.x - (paddle.width/2.0f)) < (this->x + (this->width/2.0f)))
        {
          std::cout << "1 ";
          test1 = true;
        }
        if((this->x - (this->width/2.0f)) < (paddle.x + (paddle.width/2.0f)))
        {
          std::cout << "2 ";
          test2 = true;;
        }
        if((paddle.y - (paddle.height/2.0f)) < (this->y + (this->height/2.0f)))
        {
          std::cout << "3 ";
          test3 = true;
        }
        if((this->y - (this->height/2.0f)) < (paddle.y + (paddle.height/2.0f)))
        {
          std::cout << "4 ";
          test4 = true;
        }
        std::cout << std::endl;
        std::cout << "this->: " << this->x << " " << this->y << " " << this->width << " " << this->height << std::endl;
        std::cout << "paddle.: " << paddle.x << " " << paddle.y << " " << paddle.width << " " << paddle.height << std::endl;

        if(test1 && test2 && test3 && test4)
        {
          if(this->x+this->width/2.0f >= paddle.x-paddle.width/2.0f || this->x-this->width/2.0f <= paddle.x+paddle.width/2.0f)
          {
            this->xVelocity *= -1;
          }
          else if(this->y+this->height/2.0f >= paddle.y-paddle.height/2.0f || this->y-this->height/2.0f <= paddle.y+paddle.height/2.0f)
          {
            this->yVelocity *= -1;
          }
          std::cout << "collision\n";
          return true;
        }
        else
        {
          return false;
        }
        */
        // temp placeholder to run
        return false;
    }

    float x, y, xVelocity, yVelocity;
    int width, height;
};

#endif