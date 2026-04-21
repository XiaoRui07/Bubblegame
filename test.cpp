#include "raylib.h"
#include <vector>
#include <cmath>
#include <iostream>
class Bubble {
private:
    Vector2 position;
    float radius;
    Color color;
    bool active;
    float speedY;

public:
    Bubble() {
        reset();
    }

    void reset() {
        position.x = GetRandomValue(50, GetScreenWidth() - 50);
        position.y = GetScreenHeight() + GetRandomValue(10, 100); 
        radius = GetRandomValue(20, 40);
        color = (Color){ (unsigned char)GetRandomValue(50, 255), 
                         (unsigned char)GetRandomValue(50, 255), 
                         (unsigned char)GetRandomValue(50, 255), 200 };
        speedY = (float)GetRandomValue(2, 8);
        active = true;
    }

    void update() {
        if (!active) return;
        position.y -= speedY;

        if (position.y < -radius) {
            reset();
        }
    }

    void draw() {
        if (active) {
            DrawCircleV(position, radius, color);
            DrawCircleLines(position.x, position.y, radius, WHITE);
        }
    }

    bool checkClicked(Vector2 mousePos) {
        if (!active) return false;
        
        if (CheckCollisionPointCircle(mousePos, position, radius)) {
            active = false;
            return true;
        }
        return false;
    }

    bool isActive() const { return active; }
};

int main() {
    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0);

    InitWindow(screenWidth, screenHeight, "EX06 - Click the Bubble");
    SetTargetFPS(60);

    std::vector<Bubble> bubbles(15); 
    int score = 0;

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        for (int i = 0; i < bubbles.size(); i++) {
            bubbles[i].update();

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (bubbles[i].checkClicked(mousePos)) {
                    score += 10;
                    bubbles[i].reset();
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < bubbles.size(); i++) {
            bubbles[i].draw();
        }

        DrawText(TextFormat("SCORE: %04d", score), 20, 20, 30, RAYWHITE);
        DrawText("Click the rising bubbles!", 20, 60, 20, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
