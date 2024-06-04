#include "raylib.h"
#include "iostream"

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define SNAKE_LENGTH   50
#define SQUARE_SIZE     20

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
static const int screenWidth = 810;
static const int screenHeight = 410;

static int framesCounter = 0;
static bool gameOver = false;
static bool pause = false;

static Food fruit = { 0 };
static Snake snake[SNAKE_LENGTH] = { 0 };
static Vector2 snakePosition[SNAKE_LENGTH] = { 0 };
static bool allowMove = false;
static Vector2 offset = { 0 };
static int counterTail = 0;

static int x_random = 0;
static int y_random = 0;

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
        ClearBackground(MAGENTA);

        UpdateGame();

        DrawGame();



        EndDrawing();

    }

    CloseWindow();

    return 0;
}

void UpdateGame(void)
{
    // check which key is pressed then change speed acordingly
    if (IsKeyPressed(KEY_RIGHT))
    {
        snake[1].speed = (Vector2){SQUARE_SIZE, 0};
    }
    else if (IsKeyPressed(KEY_LEFT))
    {
        snake[1].speed = (Vector2){-SQUARE_SIZE, 0};
    }
    else if (IsKeyPressed(KEY_UP))
    {
        snake[1].speed = (Vector2){0, -SQUARE_SIZE};
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        snake[1].speed = (Vector2){0, SQUARE_SIZE};
    }

    // Interaction between snake and fruit
    if ((snake[1].position.x == fruit.position.x) && (snake[1].position.y == fruit.position.y))
    {
        fruit.active = false;

        counterTail++;
    }

    // Fruit
    if (fruit.active == false)
    {
        x_random = GetRandomValue(1, (screenWidth - 2*offset.x)/SQUARE_SIZE);
        y_random = GetRandomValue(1, (screenHeight - 2*offset.y)/SQUARE_SIZE);
        fruit.position.x = SQUARE_SIZE * x_random + offset.x;
        fruit.position.y = SQUARE_SIZE * y_random + offset.y;

        fruit.active = true;
    }

}

void DrawGame()
{
    // Draw the wall
    DrawRectangleV( { offset.x, offset.y }, { screenWidth - 2 * offset.x, screenHeight -  2 * offset.y }, RAYWHITE);

    // Draw Snake
    for (int i = counterTail; i >= 1; i--)
    {
        if (i == 1)
        {
            std::cout << "vando\n";
            snake[i].position.x += snake[i].speed.x;
            snake[i].position.y += snake[i].speed.y;
        }
        else
        {
            snake[i].position.x = snake[i - 1].position.x;
            snake[i].position.y = snake[i - 1].position.y;
        }


    }

    for (int i = 1; i <= counterTail; i++)
    {
        DrawRectangleV(snake[i].position, snake[i].size, snake[i].color);
    }

    // Draw Fruit
    DrawRectangleV(fruit.position, fruit.size, fruit.color);


}

// Initialize game variables
void InitGame(void)
{
    framesCounter = 0;
    gameOver = false;
    pause = false;

    counterTail = 1;

    offset.x = screenWidth % SQUARE_SIZE;
    offset.y = screenHeight % SQUARE_SIZE;

    for (int i = 1; i < SNAKE_LENGTH; i++)
    {
        snake[i].position = (Vector2){ offset.x, offset.y};
        snake[i].size = (Vector2){ SQUARE_SIZE, SQUARE_SIZE };
        snake[i].speed = (Vector2){ SQUARE_SIZE, 0 };

        if (i == 1) snake[i].color = DARKBLUE;
        else snake[i].color = BLUE;
    }

    // for (int i = 0; i < SNAKE_LENGTH; i++)
    // {
    //     snakePosition[i] = (Vector2){ 0.0f, 0.0f };
    // }

    fruit.size = (Vector2){ SQUARE_SIZE, SQUARE_SIZE };
    fruit.color = SKYBLUE;
    fruit.active = false;
}



