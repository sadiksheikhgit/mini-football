#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>

#include "../include/entities/Ball.h"
#include "../include/entities/DBox.h"
#include "../include/entities/Field.h"
#include "../include/entities/GoalPost.h"
#include "../include/entities/Player.h"
#include "../include/entities/Scoreboard.h"

Field field;
DBox dBox;
GoalPost goalPost;
Ball ball;
Scoreboard scoreboard;
Player* players[2];

int controlledPlayerIndex = 0; // Index of the currently controlled player

// Time tracking
int lastTime = 0;

// Keyboard state
bool keyW = false;
bool keyA = false;
bool keyS = false;
bool keyD = false;

//goal storing
int leftScore=0;
int rightScore=0;


void initPlayers()
{
    // Left team (purple)
    players[0] = new Player(-700,0,0);
    //right player(red)
    players[1] = new Player(700,0,1);

}

//score cirlces showing

void drawGoalCircles(int score, float startX)
{
    float y=-1000.0f;
    float radius = 50.0f;

    glColor3f(1.0f, 1.0f, 0.0f);

    for (int i = 0; i < score; i++)
    {
        float x = startX + i *50.0f;

        glBegin(GL_POLYGON);
        for (int j = 0; j < 20; j++)
        {
            float angle = 2.0f * 3.14159f * j / 20;
            glVertex2f(x+cos(angle)*radius,
                y+sin(angle)*radius);
        }
        glEnd();
    }
}

//winning  2 goals
void resetGame()
{
    leftScore = 0;
    rightScore = 0;

    ball.reset();

    players[0]->x = -700.0f;
    players[0]->y = 0.0f;

    players[1]->x = 700.0f;
    players[1]->y = 0.0f;

    glutPostRedisplay();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glPointSize(10.0f);
    // Draw the field
    glPushMatrix();
    field.draw();
    glPopMatrix();

    // scoreboard
    glPushMatrix();
    glTranslatef(0.0f, 700.0f, 1.0f);
    glScalef(1.80f, 1.80f, 1.0f); // 180% bigger
    scoreboard.draw(leftScore, rightScore);
    glPopMatrix();

    // draw DBox
    glPushMatrix();
    dBox.draw();
    glPopMatrix();

    //goal posts
    glPushMatrix();
    goalPost.draw();
    glPopMatrix();

    //players
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        players[i]->draw();
        glPopMatrix();
    }
    glPushMatrix();
    glColor3f(1, 1, 0);
    glLineWidth(2.0f);
    float px = players[controlledPlayerIndex]->x;
    float py = players[controlledPlayerIndex]->y;
    float pr = players[controlledPlayerIndex]->radius + 10;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 20; i++) {
        float angle = 2.0f * 3.14159f * i / 20;
        float cx = px + pr * cos(angle);
        float cy = py + pr * sin(angle);
        glVertex2f(cx, cy);
    }
    glEnd();

    glPopMatrix();
    //ball
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastTime) / 1000.f;
    lastTime = currentTime;

    ball.update(deltaTime);

    int goal=ball.checkGoalCollision();

    if (goal==1)
    {
        leftScore++;
        ball.reset();
        players[0]->x = -700.0f;
        players[0]->y = 0.0f;

        players[1]->x = 700.0f;
        players[1]->y = 0.0f;
        glutPostRedisplay();
    }else if (goal==2)
    {
        rightScore++;
        ball.reset();
        players[0]->x = -700.0f;
        players[0]->y = 0.0f;

        players[1]->x = 700.0f;
        players[1]->y = 0.0f;
        glutPostRedisplay();
    }
    if (leftScore >=2 || rightScore >=2)
    {
        resetGame();
        glutPostRedisplay();
    }
    glPushMatrix();
    ball.draw();
    glPopMatrix();

    //score circles draw
    drawGoalCircles(leftScore, -1400.0f);
    drawGoalCircles(rightScore, 1000.0f);

    glFlush();


}

// keyboard wasd for p1 and ijkl for p2

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        //for player[0]
    case 'w': players[0]->moveUp();break;
    case 's': players[0]->moveDown();break;
    case 'a': players[0]->moveLeft();break;
    case 'd': players[0]->moveRight();break;

        //for player[1]
    case 'i': players[1]->moveUp();break;
    case 'j': players[1]->moveLeft();break;
    case 'k': players[1]->moveDown();break;
    case 'l': players[1]->moveRight();break;

    case 27: exit(0);
    }

    players[0]->kickBall(ball);
    players[1]->kickBall(ball);


    glutPostRedisplay(); //redrawafter exc.
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL 64-bit FreeGLUT Test");

    // Set black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Set up the projection (simple orthographic 2D)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1500, 1500, -1500, 1500);

    // Initialize players
    initPlayers();

    // Initialize time
    lastTime = glutGet(GLUT_ELAPSED_TIME);


    glutDisplayFunc(display);
    //movement
    glutKeyboardFunc(keyboard);
    // Start the main event loop
    glutMainLoop();
    return 0;
}
