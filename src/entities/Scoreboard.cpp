//
// Created by ABN Technology on 20-Jan-26.
//

#include "../../include/entities/Scoreboard.h"
#include <GL/glut.h>

Scoreboard::Scoreboard() {
    // Position at bottom center
    x = -400.0f;
    y = -900.0f;
    width = 800.0f;
    height = 100.0f;
    boxWidth = 100.0f;
    boxHeight = 80.0f;
}

void Scoreboard::draw(int leftScore, int rightScore) {
    // Draw main scoreboard background (gray)
    glColor3f(0.5f, 0.5f, 0.5f);
    drawFilledRectangle(x, y, width, height);

    // Draw score boxes (blue boxes)
    glColor3f(0.3f, 0.5f, 0.8f);

    // Left team boxes - two boxes on left side
    float leftBox1X = x + 20;
    float leftBox2X = x + 130;
    float boxY = y + 10;

    drawFilledRectangle(leftBox1X, boxY, boxWidth, boxHeight);
    drawFilledRectangle(leftBox2X, boxY, boxWidth, boxHeight);

    // Right team boxes - two boxes on right side
    float rightBox1X = x + width - 230;
    float rightBox2X = x + width - 120;

    drawFilledRectangle(rightBox1X, boxY, boxWidth, boxHeight);
    drawFilledRectangle(rightBox2X, boxY, boxWidth, boxHeight);

    // Draw "Scoreboard" text area (darker rectangle in center)
    glColor3f(0.4f, 0.4f, 0.4f);
    float textBoxX = x + 250;
    float textBoxWidth = 300.0f;
    drawFilledRectangle(textBoxX, boxY, textBoxWidth, boxHeight);

    // Draw scores as white digits
    glColor3f(1.0f, 1.0f, 1.0f);

    // Left score (in second box from left)
    drawDigit(leftScore, leftBox2X + 35, boxY + 20);

    // Right score (in first box from right)
    drawDigit(rightScore, rightBox2X + 35, boxY + 20);
}

void Scoreboard::drawRectangle(float x, float y, float w, float h) {
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

void Scoreboard::drawFilledRectangle(float x, float y, float w, float h) {
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

void Scoreboard::drawDigit(int digit, float x, float y) {
    // Simple digit drawing using rectangles
    // Each digit is made of small rectangles

    float segWidth = 30.0f;
    float segHeight = 40.0f;

    glBegin(GL_QUADS);

    // Draw digit based on number
    switch(digit) {
        case 0:
            // Draw 0
            glVertex2f(x, y);
            glVertex2f(x + segWidth, y);
            glVertex2f(x + segWidth, y + segHeight);
            glVertex2f(x, y + segHeight);

            // Cut out center
            glColor3f(0.3f, 0.5f, 0.8f);  // Same as box color
            glVertex2f(x + 8, y + 8);
            glVertex2f(x + segWidth - 8, y + 8);
            glVertex2f(x + segWidth - 8, y + segHeight - 8);
            glVertex2f(x + 8, y + segHeight - 8);
            glColor3f(1.0f, 1.0f, 1.0f);  // Back to white
            break;

        case 1:
            // Draw 1 (vertical line on right)
            glVertex2f(x + segWidth - 10, y);
            glVertex2f(x + segWidth, y);
            glVertex2f(x + segWidth, y + segHeight);
            glVertex2f(x + segWidth - 10, y + segHeight);
            break;

        case 2:
            // Top horizontal
            glVertex2f(x, y + segHeight - 8);
            glVertex2f(x + segWidth, y + segHeight - 8);
            glVertex2f(x + segWidth, y + segHeight);
            glVertex2f(x, y + segHeight);

            // Right vertical top
            glVertex2f(x + segWidth - 10, y + segHeight / 2);
            glVertex2f(x + segWidth, y + segHeight / 2);
            glVertex2f(x + segWidth, y + segHeight);
            glVertex2f(x + segWidth - 10, y + segHeight);

            // Middle horizontal
            glVertex2f(x, y + segHeight / 2 - 4);
            glVertex2f(x + segWidth, y + segHeight / 2 - 4);
            glVertex2f(x + segWidth, y + segHeight / 2 + 4);
            glVertex2f(x, y + segHeight / 2 + 4);

            // Left vertical bottom
            glVertex2f(x, y);
            glVertex2f(x + 10, y);
            glVertex2f(x + 10, y + segHeight / 2);
            glVertex2f(x, y + segHeight / 2);

            // Bottom horizontal
            glVertex2f(x, y);
            glVertex2f(x + segWidth, y);
            glVertex2f(x + segWidth, y + 8);
            glVertex2f(x, y + 8);
            break;

        case 3:
            // Top
            glVertex2f(x, y + segHeight - 8);
            glVertex2f(x + segWidth, y + segHeight - 8);
            glVertex2f(x + segWidth, y + segHeight);
            glVertex2f(x, y + segHeight);

            // Right vertical
            glVertex2f(x + segWidth - 10, y);
            glVertex2f(x + segWidth, y);
            glVertex2f(x + segWidth, y + segHeight);
            glVertex2f(x + segWidth - 10, y + segHeight);

            // Middle
            glVertex2f(x, y + segHeight / 2 - 4);
            glVertex2f(x + segWidth, y + segHeight / 2 - 4);
            glVertex2f(x + segWidth, y + segHeight / 2 + 4);
            glVertex2f(x, y + segHeight / 2 + 4);

            // Bottom
            glVertex2f(x, y);
            glVertex2f(x + segWidth, y);
            glVertex2f(x + segWidth, y + 8);
            glVertex2f(x, y + 8);
            break;

        default:
            // For numbers 4-9, just draw the digit as-is
            // You can add more cases if needed
            glVertex2f(x, y);
            glVertex2f(x + segWidth, y);
            glVertex2f(x + segWidth, y + segHeight);
            glVertex2f(x, y + segHeight);
            break;
    }

    glEnd();
}