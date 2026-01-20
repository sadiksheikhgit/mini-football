//
// Created by shifat arman on 1/2/2026.
//

#include "../../include/entities/Field.h"
#include <GL/glut.h>
<<<<<<< Updated upstream
=======
#include <cmath>

// Animation variable
float jumpTime = 0.0f; // Advances every frame
>>>>>>> Stashed changes

Field::Field()
{
    fieldWidth = 900.0f;
    fieldHeight = 600.0f;
}

void Field::draw()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFieldBoundary();
    drawCenterLine();
<<<<<<< Updated upstream
=======
    drawStadium();

    // Increment jump animation
    jumpTime += 0.05f;
    glutPostRedisplay(); // Continuous redraw
>>>>>>> Stashed changes
}

void Field::drawFieldBoundary() const
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(-fieldWidth, -fieldHeight);
    glVertex2f(fieldWidth, -fieldHeight);
    glVertex2f(fieldWidth, fieldHeight);
    glVertex2f(-fieldWidth, fieldHeight);
    glEnd();
}

void Field::drawCenterLine() const
{
    glBegin(GL_LINES);
    glVertex2f(0.0f, -fieldHeight);
    glVertex2f(0.0f, fieldHeight);
    glEnd();
}

void Field::drawRectangle(float x, float y, float width, float height)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y); // Bottom-left
    glVertex2f(x + width, y); // Bottom-right
    glVertex2f(x + width, y + height); // Top-right
    glVertex2f(x, y + height); // Top-left
    glEnd();
}
<<<<<<< Updated upstream
=======

void Field::drawStadium() const
{
    float marginX = 260.0f;
    float stadiumHeight = 240.0f;
    float baseY = fieldHeight;
    float topY  = baseY + stadiumHeight;

    // Stadium outer boundary
    glColor3f(0.35f, 0.35f, 0.35f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-fieldWidth - marginX, baseY);
    glVertex2f(fieldWidth + marginX, baseY);
    glVertex2f(fieldWidth + marginX, topY);
    glVertex2f(-fieldWidth - marginX, topY);
    glEnd();

    // Rows
    int rows = 10;
    float rowHeight = stadiumHeight / rows;
    for (int r = 0; r <= rows; r++)
    {
        float y = baseY + r * rowHeight;
        float inset = marginX * (0.25f + 0.55f * ((float)r / rows));
        glColor3f(0.45f, 0.45f, 0.45f);
        glBegin(GL_LINES);
        glVertex2f(-fieldWidth - inset, y);
        glVertex2f(fieldWidth + inset, y);
        glEnd();
    }

    // Aisles
    glColor3f(0.55f, 0.55f, 0.55f);
    int aisles = 6;
    for (int i = 1; i < aisles; i++)
    {
        float x = -fieldWidth - marginX + (2.0f * (fieldWidth + marginX) * i / aisles);
        glBegin(GL_LINES);
        glVertex2f(x, baseY);
        glVertex2f(x, topY);
        glEnd();
    }

    // People in the stadium
    float headR = 20.0f;
    int peopleRows[] = {2, 4, 6};
    int rowCount = 3;
    int peoplePerRow = 8;

    for (int i = 0; i < rowCount; i++)
    {
        int r = peopleRows[i];
        float y = baseY + r * rowHeight + headR * 0.9f;
        float inset = marginX * (0.25f + 0.55f * ((float)r / rows));
        float leftX  = -fieldWidth - inset + headR * 2.0f;
        float rightX = fieldWidth + inset - headR * 2.0f;
        float spacing = (rightX - leftX) / (peoplePerRow - 1);

        for (int p = 0; p < peoplePerRow; p++)
        {
            float x = leftX + p * spacing;
            if (i % 2 == 1) x += spacing * 0.35f;
            if (x < leftX || x > rightX) continue;

            if (x < 0) glColor3f(0.7f, 0.1f, 0.9f);
            else glColor3f(1.0f, 0.1f, 0.1f);

            // Jumping effect
            float jumpAmplitude = headR * 0.3f;
            float jumpSpeed = 1.0f;
            float animatedY = y + sin(jumpTime * jumpSpeed + x) * jumpAmplitude;

            // Head
            glBegin(GL_POLYGON);
            for (int k = 0; k < 16; k++)
            {
                float a = 2.0f * 3.14159f * k / 16;
                glVertex2f(x + cos(a) * headR, animatedY + sin(a) * headR);
            }
            glEnd();

            // Body
            glBegin(GL_POLYGON);
            glVertex2f(x - headR * 0.4f, animatedY - headR * 0.9f);
            glVertex2f(x + headR * 0.4f, animatedY - headR * 0.9f);
            glVertex2f(x + headR * 0.3f, animatedY - headR * 1.8f);
            glVertex2f(x - headR * 0.3f, animatedY - headR * 1.8f);
            glEnd();

            // Arms
            glColor3f(0.9f, 0.7f, 0.5f);
            // Left arm
            glBegin(GL_POLYGON);
            glVertex2f(x - headR * 0.4f, animatedY - headR * 1.0f);
            glVertex2f(x - headR * 0.5f, animatedY - headR * 1.0f);
            glVertex2f(x - headR * 0.9f, animatedY - headR * 1.5f);
            glVertex2f(x - headR * 0.8f, animatedY - headR * 1.6f);
            glEnd();
            // Right arm
            glBegin(GL_POLYGON);
            glVertex2f(x + headR * 0.4f, animatedY - headR * 1.0f);
            glVertex2f(x + headR * 0.5f, animatedY - headR * 1.0f);
            glVertex2f(x + headR * 0.9f, animatedY - headR * 1.5f);
            glVertex2f(x + headR * 0.8f, animatedY - headR * 1.6f);
            glEnd();
        }
    }

    // First row line
    glColor3f(0.7f, 0.7f, 0.7f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-fieldWidth - marginX * 0.25f, baseY + rowHeight);
    glVertex2f(fieldWidth + marginX * 0.25f, baseY + rowHeight);
    glEnd();
    glLineWidth(1.0f);
}
>>>>>>> Stashed changes
