#include <GL/glut.h>
#include <cmath>

// =====================
// Game Structures
// =====================
struct Player {
    float x, y;
    float radius;
};

struct Ball {
    float x, y;
    float vx, vy;
    float radius;
};

// =====================
// Game Objects
// =====================
Player p1 = { -0.6f, 0.0f, 0.08f };
Player p2 = {  0.6f, 0.0f, 0.08f };
Ball ball  = { 0.0f, 0.0f, 0.01f, 0.015f, 0.05f };

// =====================
// Utility
// =====================
float clamp(float v, float min, float max) {
    if (v < min) return min;
    if (v > max) return max;
    return v;
}

// =====================
// Draw Circle
// =====================
void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++) {
        float a = i * 3.14159f / 180.0f;
        glVertex2f(cx + cos(a) * r, cy + sin(a) * r);
    }
    glEnd();
}

// =====================
// Collision
// =====================
void ballPlayerCollision(Player &p) {
    float dx = ball.x - p.x;
    float dy = ball.y - p.y;
    float dist = sqrt(dx * dx + dy * dy);

    if (dist < ball.radius + p.radius) {
        float nx = dx / dist;
        float ny = dy / dist;

        ball.vx += nx * 0.02f;
        ball.vy += ny * 0.02f;
    }
}

// =====================
// Update (Game Loop)
// =====================
void update(int) {
    // Move ball
    ball.x += ball.vx;
    ball.y += ball.vy;

    // Friction
    ball.vx *= 0.995f;
    ball.vy *= 0.995f;

    // Wall collision
    if (ball.x > 0.95f || ball.x < -0.95f) ball.vx *= -1;
    if (ball.y > 0.95f || ball.y < -0.95f) ball.vy *= -1;

    // Player collisions
    ballPlayerCollision(p1);
    ballPlayerCollision(p2);

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

// =====================
// Input
// =====================
void keyboard(unsigned char key, int, int) {
    float speed = 0.07f;

    // Player 1 (WASD)
    if (key == 'w') p1.y += speed;
    if (key == 's') p1.y -= speed;
    if (key == 'a') p1.x -= speed;
    if (key == 'd') p1.x += speed;

    // Player 2 (IJKL)
    if (key == 'i') p2.y += speed;
    if (key == 'k') p2.y -= speed;
    if (key == 'j') p2.x -= speed;
    if (key == 'l') p2.x += speed;

    // Clamp players inside field
    p1.x = clamp(p1.x, -0.9f, 0.9f);
    p1.y = clamp(p1.y, -0.9f, 0.9f);
    p2.x = clamp(p2.x, -0.9f, 0.9f);
    p2.y = clamp(p2.y, -0.9f, 0.9f);
}

// =====================
// Rendering
// =====================
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Field border
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.95f, -0.95f);
    glVertex2f( 0.95f, -0.95f);
    glVertex2f( 0.95f,  0.95f);
    glVertex2f(-0.95f,  0.95f);
    glEnd();

    // Player 1
    glColor3f(0, 0, 1);
    drawCircle(p1.x, p1.y, p1.radius);

    // Player 2
    glColor3f(1, 0, 0);
    drawCircle(p2.x, p2.y, p2.radius);

    // Ball
    glColor3f(1, 1, 1);
    drawCircle(ball.x, ball.y, ball.radius);

    glFlush();
}

// =====================
// Projection
// =====================
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

// =====================
// Main
// =====================
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Minimal Offline HaxBall");

    glClearColor(0, 0.5f, 0, 1); // Green field

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
