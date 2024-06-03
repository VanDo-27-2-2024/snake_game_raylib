#include "raylib.h"
#include "iostream"

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define SNAKE_LENGTH   50
#define SQUARE_SIZE     31

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct Snake {
    Vector2 position;
    Vector2 size;
    Vector2 speed;
    Color color;
} Snake;

typedef struct Food {
    Vector2 position;
    Vector2 size;
    bool active;
    Color color;
} Food;

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;

static int framesCounter = 0;
static bool gameOver = false;
static bool pause = false;

static Food fruit = { 0 };
static Snake snake[SNAKE_LENGTH] = { 0 };
static Vector2 snakePosition[SNAKE_LENGTH] = { 0 };
static bool allowMove = false;
static Vector2 offset = { 0 };
static int counterTail = 0;


//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "classic game: snake");

    InitGame();

    SetTargetFPS(10);
    //--------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        UpdateGame();

        snake[0].position.x += snake[0].speed.x;
        snake[0].position.y += snake[0].speed.y;
        DrawRectangleV(snake[0].position, snake[0].size, snake[0].color);




    // DrawRectangleV(, snake[i].size, snake[i].color);
    // DrawRectangle(screenWidth/2, 100, 120, 60, RED);

        EndDrawing();


        // Update and Draw
        //----------------------------------------------------------------------------------
        // UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    // UnloadGame();         // Unload loaded data (textures, sounds, models...)

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void UpdateGame(void)
{
    // check which key is pressed then change speed acordingly
    if (IsKeyPressed(KEY_RIGHT))
    {
        snake[0].speed = (Vector2){SQUARE_SIZE, 0};
    }
    else if (IsKeyPressed(KEY_LEFT))
    {
        snake[0].speed = (Vector2){-SQUARE_SIZE, 0};
    }
    else if (IsKeyPressed(KEY_UP))
    {
        snake[0].speed = (Vector2){0, -SQUARE_SIZE};
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        snake[0].speed = (Vector2){0, SQUARE_SIZE};
    }
}

// Initialize game variables
void InitGame(void)
{
    framesCounter = 0;
    gameOver = false;
    pause = false;

    counterTail = 1;


    for (int i = 0; i < SNAKE_LENGTH; i++)
    {
        snake[i].position = (Vector2){screenWidth/2 , screenHeight/2};
        snake[i].size = (Vector2){ SQUARE_SIZE, SQUARE_SIZE };
        snake[i].speed = (Vector2){ SQUARE_SIZE, 0 };

        if (i == 0) snake[i].color = DARKBLUE;
        else snake[i].color = BLUE;
    }

    for (int i = 0; i < SNAKE_LENGTH; i++)
    {
        snakePosition[i] = (Vector2){ 0.0f, 0.0f };
    }

    fruit.size = (Vector2){ SQUARE_SIZE, SQUARE_SIZE };
    fruit.color = SKYBLUE;
    fruit.active = false;
}



