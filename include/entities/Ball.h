//
// Created by shifat arman on 1/2/2026.
//

#ifndef MINI_FOOTBALL_BALL_H
#define MINI_FOOTBALL_BALL_H
class Ball {
public:
    // Constructor
    Ball();
    
    // Update ball position and physics
    void update(float deltaTime);
    
    // Draw the ball
    void draw();
    
    // Reset ball to center
    void reset();
    
    // Kick the ball (give it velocity)
    void kick(float vx, float vy);
    
    // Position
    float x;
    float y;
    
    // Velocity
    float vx;
    float vy;
    // Ball properties
    float radius;
    float friction;

    //goalpost collision:
    int checkGoalCollision();

private:
    
    
    
    // Field boundaries
    float fieldLeft;
    float fieldRight;
    float fieldTop;
    float fieldBottom;
    
    // Helper functions
    void applyFriction();
    void checkBoundaryCollision();
    void drawCircleBresenham(int xc, int yc, int r);
    void plotCirclePoints(int xc, int yc, int x, int y);
};
#endif // MINI_FOOTBALL_BALL_H
