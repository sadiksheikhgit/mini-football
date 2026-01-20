//
// Created by shifat arman on 1/2/2026.
//

#include "../../include/entities/Player.h"
#include "../../include/entities/Ball.h"

#include <GL/glut.h>
#include <cmath>


Player::Player(float startX, float startY, int teamNumber) {
    x = startX; //horPos
    y = startY; //verPos
    team = teamNumber;
    radius = 40.0f;
}

void Player::draw() {
    // Set color based on team
    if (team == 0) {
        // Left team - Purple
        glColor3f(0.6f, 0.2f, 0.8f);
    } else {
        // Right team - Red
        glColor3f(0.8f, 0.2f, 0.2f);
    }
    
    // Draw filled circle
    drawCircleBresenham((int)x, (int)y, (int)radius);
}

void Player::move(float dx, float dy) {
    x += dx;
    y += dy;
}

void Player::drawCircleBresenham(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    
    plotCirclePoints(xc, yc, x, y);
    
    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
        plotCirclePoints(xc, yc, x, y);
    }
}

void Player::plotCirclePoints(int xc, int yc, int x, int y) {
    glBegin(GL_LINES);
    glVertex2f(xc - x, yc + y);
    glVertex2f(xc + x, yc + y);
        
    glVertex2f(xc - x, yc - y);
    glVertex2f(xc + x, yc - y);
        
    glVertex2f(xc - y, yc + x);
    glVertex2f(xc + y, yc + x);
        
    glVertex2f(xc - y, yc - x);
    glVertex2f(xc + y, yc - x);
    glEnd();
}

// later move add-ons implementation
void Player::moveUp()
{
    y+=20.0f;
}
void Player::moveDown()
{
    y-=20.0f;
}

void Player::moveLeft()
{
    x-=20.0f;
}

void Player::moveRight()
{
    x+=20.0f;
}

bool Player::iscollisionWithBall (Ball &ball){
    float dx= x-ball.x;  // player distance-ball distance logic
    float dy = y-ball.y;

    float distance = sqrt(dx*dx + dy*dy); // player to ball straight line
    return distance< (radius +ball.radius); // if touch, collison.

}

// kick suii

void Player::kickBall(Ball& ball)
{
    if (iscollisionWithBall(ball))
    {


        float dx = ball.x - x;
        float dy = ball.y - y;

        float distance = sqrt(dx*dx + dy*dy);

        if (distance==0)
            return;


        dx/=distance;
        dy/=distance;

        float kicPower =100.0f;

        ball.x += dx*kicPower;
        ball.y += dy*kicPower;
    }
}

