//
// Created by ABN Technology on 20-Jan-26.
//

#ifndef MINI_FOOTBALL_SCOREBOARD_H
#define MINI_FOOTBALL_SCOREBOARD_H
class Scoreboard {
public:
    // Constructor
    Scoreboard();

    // Draw the scoreboard
    void draw(int leftScore, int rightScore);

private:
    // Scoreboard position and size
    float x;
    float y;
    float width;
    float height;
    float boxWidth;
    float boxHeight;

    // Helper functions
    void drawRectangle(float x, float y, float w, float h);
    void drawFilledRectangle(float x, float y, float w, float h);
    void drawDigit(int digit, float x, float y);
};
#endif // MINI_FOOTBALL_SCOREBOARD_H
