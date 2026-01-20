//
// Created by shifat arman on 1/2/2026.
//
#ifndef MINI_FOOTBALL_PLAYER_H
#define MINI_FOOTBALL_PLAYER_H
class Ball;
class Player
{
public:
    // Position
    float x;
    float y;

    // Properties
    float radius;
    int team; // 0 = left (purple), 1 = right (red)

    // Constructor
    Player(float startX, float startY, int teamNumber);

    // Draw the player
    void draw();

    // Move the player
    void move(float dx, float dy);

    //later add-ons move
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    //kicking mecha
    bool iscollisionWithBall(Ball &ball);
    void kickBall(Ball &ball);
private:
    // Draw circle using Bresenham
    void drawCircleBresenham(int xc, int yc, int r);
    void plotCirclePoints(int xc, int yc, int x, int y);
};
#endif // MINI_FOOTBALL_PLAYER_H
