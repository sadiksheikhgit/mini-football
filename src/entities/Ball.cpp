//
// Created by shifat arman on 1/2/2026.
//

#include "../../include/entities/Ball.h"
#include <GL/glut.h>
#include <cmath>

Ball::Ball() {
    // Start at center
    x = 0.0f;
    y = 0.0f;
    
    // No initial velocity
    vx = 0.0f;
    vy = 0.0f;
    
    // Ball properties
    radius = 30.0f;
    friction = 0.98f;  // Slow down gradually
    
    // Field boundaries (matching Field.cpp dimensions)
    fieldLeft = -900.0f;
    fieldRight = 900.0f;
    fieldTop = 600.0f;
    fieldBottom = -600.0f;
}

void Ball::update(float deltaTime) {
    // Update position based on velocity
    x += vx * deltaTime;
    y += vy * deltaTime;
    
    // Apply friction to slow down the ball
    applyFriction();
    
    // Check collision with field boundaries
    checkBoundaryCollision();
}

void Ball::draw() {
    // Set ball color to orange
    glColor3f(1.0f, 0.6f, 0.0f);
    
    // Draw filled circle using Bresenham algorithm
    drawCircleBresenham((int)x, (int)y, (int)radius);
}

void Ball::reset() {
    // Reset to center with no velocity
    x = 0.0f;
    y = 0.0f;
    vx = 0.0f;
    vy = 0.0f;
}

void Ball::kick(float kickVx, float kickVy) {
    // Give the ball velocity
    vx = kickVx;
    vy = kickVy;
}

void Ball::applyFriction() {
    // Gradually reduce velocity
    vx *= friction;
    vy *= friction;
    
    // Stop completely if velocity is very small
    if (fabs(vx) < 0.1f) vx = 0.0f;
    if (fabs(vy) < 0.1f) vy = 0.0f;
}

void Ball::checkBoundaryCollision() {
    // Check left boundary
    if (x - radius < fieldLeft) {
        x = fieldLeft + radius;
        vx = -vx * 0.8f;  // Bounce back with energy loss
    }
    
    // Check right boundary
    if (x + radius > fieldRight) {
        x = fieldRight - radius;
        vx = -vx * 0.8f;
    }
    
    // Check top boundary
    if (y + radius > fieldTop) {
        y = fieldTop - radius;
        vy = -vy * 0.8f;
    }
    
    // Check bottom boundary
    if (y - radius < fieldBottom) {
        y = fieldBottom + radius;
        vy = -vy * 0.8f;
    }
}

// Bresenham's Circle Drawing Algorithm
void Ball::drawCircleBresenham(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    
    // Draw initial points
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

void Ball::plotCirclePoints(int xc, int yc, int x, int y) {
    // Draw all 8 octants of the circle
    // This creates a filled circle by drawing horizontal lines
    
    // Draw horizontal lines to fill the circle
    glBegin(GL_LINES);
        // Octant 1 and 4
        glVertex2f(xc - x, yc + y);
        glVertex2f(xc + x, yc + y);
        
        // Octant 5 and 8
        glVertex2f(xc - x, yc - y);
        glVertex2f(xc + x, yc - y);
        
        // Octant 2 and 3
        glVertex2f(xc - y, yc + x);
        glVertex2f(xc + y, yc + x);
        
        // Octant 6 and 7
        glVertex2f(xc - y, yc - x);
        glVertex2f(xc + y, yc - x);
    glEnd();
}
// goal post goal checking with ball collison
int Ball::checkGoalCollision()
{
    float leftGoalX=-1100.0f+200.0f;
    float goalTop = 250.0f;
    float goalBottom = -250.0f;

    if (x-radius <= leftGoalX &&
        y >=goalBottom &&
        y <= goalTop)
    {
        return 2;  //for right team
    }


    float rightGoalX = 900.0f;
    if (x+radius >= rightGoalX &&
        y >=goalBottom &&
        y <= goalTop)
    {
        return 1; //for left team
    }
    return 0;

}
