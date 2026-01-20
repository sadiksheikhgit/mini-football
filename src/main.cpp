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

// goal storing
int leftScore = 0;
int rightScore = 0;

// goal tracking
int lastScorer = -1;

// game state
bool gameOver = false;
int winner = -1;

void initPlayers()
{
    // Left team (purple)
    players[0] = new Player(-700, 0, 0);
    // right player(red)
    players[1] = new Player(700, 0, 1);
}


// winning  3 goals
void resetGame()
{
    leftScore = 0;
    rightScore = 0;
    lastScorer = -1;
    winner = -1;
    gameOver = false;

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
    // scale everything 120%
    glPushMatrix();
    glScalef(1.2f, 1.2f, 1.0f);

    glColor3f(1, 1, 1);
    // scoreboard
    glPushMatrix();
    glTranslatef(0.0f, 700.0f, 1.0f);
    glScalef(1.80f, 1.80f, 1.0f); // 180% bigger
    scoreboard.draw(leftScore, rightScore, lastScorer, gameOver, winner);
    glPopMatrix();

    // Draw the field
    glPushMatrix();
    field.draw();
    glPopMatrix();

    // draw DBox
    glPushMatrix();
    dBox.draw();
    glPopMatrix();

    // goal posts
    glPushMatrix();
    goalPost.draw();
    glPopMatrix();

    // players
    for (int i = 0; i < 2; i++)
    {
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

    glEnd();
    glPopMatrix();
    // ball
    glPushMatrix();
    ball.draw();
    glPopMatrix();
    glFlush();
    glPopMatrix();
}
void update(int value)
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastTime) / 1000.f;
    lastTime = currentTime;

    if (!gameOver)
    {
        ball.update(deltaTime);
        int goal = ball.checkGoalCollision();

        if (goal == 1)
        {
            leftScore++;
            lastScorer = 0; // red
            ball.reset();
            players[0]->x = -700.0f;
            players[0]->y = 0.0f;

            players[1]->x = 700.0f;
            players[1]->y = 0.0f;
            glutPostRedisplay();
        }
        else if (goal == 2)
        {
            rightScore++;
            lastScorer = 1; // purple
            ball.reset();
            players[0]->x = -700.0f;
            players[0]->y = 0.0f;

            players[1]->x = 700.0f;
            players[1]->y = 0.0f;
            glutPostRedisplay();
        }
        else if (leftScore == 3 || rightScore == 3)
        {
            // resetGame();
            gameOver = true;
            winner = (leftScore == 3) ? 0 : 1;
            glutPostRedisplay();
        }
        glutTimerFunc(16, update, 0); // approx 60 FPS
    }
    glutPostRedisplay();
    // glutTimerFunc(16, update, 0); // approx 60 FPS
}

// keyboard wasd for p1 and ijkl for p2

void keyboard(unsigned char key, int x, int y)
{
    if (!gameOver)
    {
        switch (key)
        {
            // for player[0]
        case 'w':
            players[0]->moveUp();
            break;
        case 's':
            players[0]->moveDown();
            break;
        case 'a':
            players[0]->moveLeft();
            break;
        case 'd':
            players[0]->moveRight();
            break;

            // for player[1]
        case 'i':
            players[1]->moveUp();
            break;
        case 'j':
            players[1]->moveLeft();
            break;
        case 'k':
            players[1]->moveDown();
            break;
        case 'l':
            players[1]->moveRight();
            break;
        case 27:
            exit(0);
        }
        glutPostRedisplay();
    }
    else if (gameOver)
    {
        switch (key)
        {
        case 'r':
            resetGame();
            lastTime = glutGet(GLUT_ELAPSED_TIME);
            glutTimerFunc(0, update, 0);
            break;
        case 27:
            exit(0);
        }
        glutPostRedisplay();
    }

    players[0]->kickBall(ball);
    players[1]->kickBall(ball);


    glutPostRedisplay(); // redrawafter exc.
}

void reshape(int w, int h)
{
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    float aspect = (float)w / (float)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (aspect >= 1.0f)
    {
        // Wide window
        gluOrtho2D(-1500 * aspect, 1500 * aspect, -1500, 1500);
    }
    else
    {
        // Tall window
        gluOrtho2D(-1500, 1500, -1500 / aspect, 1500 / aspect);
    }

    glMatrixMode(GL_MODELVIEW);
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
    glutReshapeFunc(reshape);
    // movement
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    // Start the main event loop
    glutMainLoop();
    return 0;
}
