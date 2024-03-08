#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FOOD_SCORE 10
#define MAX_GHOSTS 30
#define CAPSULE_DURATION 10
#define CAPSULE_SCORE 50
#define GHOST_SCORE 200
typedef enum gameState {
    losing, onGoing, winning
} GameState;
typedef enum direction {
    up, down, left, right, idle
} Direction;
typedef struct Pacman {
    int r;
    int c;
} pacman;
typedef struct ghost {
    int r;
    int c;
    Direction direction;
    int status;
    char cell;
} Ghost;
typedef struct game {
    char **grid;
    int rows;
    int columns;
    int foodCount;
    int ghostCount;
    int score;
    int power;
    int status;
    GameState state;
    pacman Pacman;
    Ghost ghost[MAX_GHOSTS];
} Game;

Game *NewGame(int rows, int columns) {
    Game *game = (Game *) malloc(sizeof(Game));
    game->grid = (char **) malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++)
        game->grid[i] = (char *) malloc(columns * sizeof(char));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            game->grid[i][j] = ' ';
    }
    game->rows = rows;
    game->columns = columns;
    game->foodCount = 0;
    game->ghostCount = 0;
    game->score = 0;
    game->power = 0;
    game->status = 1;
    game->state = onGoing;
    game->Pacman.r = -114514;
    for (int i = 0; i < MAX_GHOSTS; i++)
        game->ghost[i].status = 0;
    return game;
}

void EndGame(Game *game) {
    for (int i = 0; i < game->rows; i++)
        free(game->grid[i]);
    free(game->grid);
    free(game);
}

bool AddWall(Game *game, int r, int c) {
    if (r >= 0 && r < game->rows && c >= 0 && c < game->columns && game->grid[r][c] == ' ') {
        game->grid[r][c] = '#';
        return true;
    } else
        return false;
}

bool AddFood(Game *game, int r, int c) {
    if (r >= 0 && r < game->rows && c >= 0 && c < game->columns && game->grid[r][c] == ' ') {
        game->grid[r][c] = '.';
        game->foodCount++;
        return true;
    } else
        return false;
}

bool AddPacman(Game *game, int r, int c) {
    if (game->Pacman.r < 0 && r >= 0 && r < game->rows && c >= 0 && c < game->columns && game->grid[r][c] == ' ') {
        game->grid[r][c] = 'C';
        game->Pacman.r = r;
        game->Pacman.c = c;
        return true;
    } else
        return false;
}

bool judgePacman(Game *game, int r, int c) {
    return (r < 0 || c < 0 || r >= game->rows || c >= game->columns || game->grid[r][c] == '#') ? false : true;
}

void score(Game *game, int r, int c) {
    if (game->grid[r][c] == '@')
        game->state = losing;
    else {
        if (game->grid[r][c] == 'X') {
            game->score += GHOST_SCORE;
            for (int i = 0; i < MAX_GHOSTS; i++) {
                if (game->ghost[i].r == r && game->ghost[i].c == c && game->ghost[i].status) {
                    game->ghost[i].status = 0;
                    game->grid[r][c] = game->ghost[i].cell;
                    break;
                }
            }
        }
        if (game->grid[r][c] == '.') {
            game->score += FOOD_SCORE;
            game->foodCount--;
        } else if (game->grid[r][c] == 'o') {
            game->score += CAPSULE_SCORE;
            if (!game->power) {
                game->status++;
            }
            game->power = CAPSULE_DURATION + 1;
            game->foodCount--;
        }
        game->grid[r][c] = 'C';
    }
    if (game->foodCount <= 0)
        game->state = winning;
    game->score--;
}

void MovePacman(Game *game, Direction direction) {
    int r = game->Pacman.r, c = game->Pacman.c;
    switch (direction) {
        case up:
            if (judgePacman(game, r - 1, c))
                game->grid[r--][c] = ' ';
            break;
        case down:
            if (judgePacman(game, r + 1, c))
                game->grid[r++][c] = ' ';
            break;
        case left:
            if (judgePacman(game, r, c - 1))
                game->grid[r][c--] = ' ';
            break;
        case right:
            if (judgePacman(game, r, c + 1))
                game->grid[r][c++] = ' ';
            break;
        default:
            break;
    }
    score(game, r, c);
    if (game->power)
        game->status = --game->power ? ++game->status : 1;
    else
        game->status = 1;
    game->Pacman.r = r;
    game->Pacman.c = c;
}

bool AddGhost(Game *game, int r, int c, Direction direction) {
    int i = game->ghostCount;
    if (r >= 0 && r < game->rows && c >= 0 && c < game->columns &&
        (game->grid[r][c] == ' ' || game->grid[r][c] == '.' || game->grid[r][c] == 'o')) {
        game->ghost[i].r = r;
        game->ghost[i].c = c;
        game->ghost[i].direction = direction;
        game->ghost[i].status = 1;
        game->ghost[game->ghostCount++].cell = game->grid[r][c];
        game->grid[r][c] = '@';
        return true;
    } else
        return false;
}

bool judgeGhosts(Game *game, int r, int c) {
    return (r < 0 || c < 0 || r >= game->rows || c >= game->columns || game->grid[r][c] == '#' ||
            game->grid[r][c] == '@' || game->grid[r][c] == 'X') ? false : true;
}

void crash(Game *game, int i, int r, int c) {
    if (game->power) {
        game->score += GHOST_SCORE;
        game->ghost[i].status = 0;
    } else {
        game->state = losing;
        game->grid[r][c] = '@';
    }
}

void shape(Game *game, int i, int r, int c, bool move) {
    if (move)
        game->ghost[i].cell = game->grid[r][c];
    game->grid[r][c] = game->power ? 'X' : '@';
}

void MoveGhosts(Game *game) {
    for (int i = 0; i < MAX_GHOSTS; i++) {
        if (game->ghost[i].status)
            shape(game, i, game->ghost[i].r, game->ghost[i].c, false);
    }
    if (game->status % 2) {
        for (int i = 0; i < MAX_GHOSTS; i++) {
            int r = game->ghost[i].r;
            int c = game->ghost[i].c;
            if (game->ghost[i].status) {
                game->grid[r][c] = game->ghost[i].cell;
                switch (game->ghost[i].direction) {
                    case up:
                        if (judgeGhosts(game, r - 1, c)) {
                            if (game->grid[r - 1][c] == 'C')
                                crash(game, i, --r, c);
                            else
                                shape(game, i, --r, c, true);
                        } else if (judgeGhosts(game, r + 1, c)) {
                            game->ghost[i].direction = down;
                            if (game->grid[r + 1][c] == 'C')
                                crash(game, i, ++r, c);
                            else
                                shape(game, i, ++r, c, true);
                        } else {
                            game->ghost[i].direction = down;
                            shape(game, i, r, c, true);
                        }
                        break;
                    case down:
                        if (judgeGhosts(game, r + 1, c)) {
                            if (game->grid[r + 1][c] == 'C')
                                crash(game, i, ++r, c);
                            else
                                shape(game, i, ++r, c, true);
                        } else if (judgeGhosts(game, r - 1, c)) {
                            game->ghost[i].direction = up;
                            if (game->grid[r - 1][c] == 'C')
                                crash(game, i, --r, c);
                            else
                                shape(game, i, --r, c, true);
                        } else {
                            game->ghost[i].direction = up;
                            shape(game, i, r, c, true);
                        }
                        break;
                    case left:
                        if (judgeGhosts(game, r, c - 1)) {
                            if (game->grid[r][c - 1] == 'C')
                                crash(game, i, r, --c);
                            else
                                shape(game, i, r, --c, true);
                        } else if (judgeGhosts(game, r, c + 1)) {
                            game->ghost[i].direction = right;
                            if (game->grid[r][c + 1] == 'C')
                                crash(game, i, r, ++c);
                            else
                                shape(game, i, r, ++c, true);
                        } else {
                            game->ghost[i].direction = right;
                            shape(game, i, r, c, true);
                        }
                        break;
                    case right:
                        if (judgeGhosts(game, r, c + 1)) {
                            if (game->grid[r][c + 1] == 'C')
                                crash(game, i, r, ++c);
                            else
                                shape(game, i, r, ++c, true);
                        } else if (judgeGhosts(game, r, c - 1)) {
                            game->ghost[i].direction = left;
                            if (game->grid[r][c - 1] == 'C')
                                crash(game, i, r, --c);
                            else
                                shape(game, i, r, --c, true);
                        } else {
                            game->ghost[i].direction = left;
                            shape(game, i, r, c, true);
                        }
                        break;
                    default:
                        break;
                }
                game->ghost[i].r = r;
                game->ghost[i].c = c;
            }
        }
    }
}

bool AddCapsule(Game *game, int r, int c) {
    if (r >= 0 && r < game->rows && c >= 0 && c < game->columns &&
        (game->grid[r][c] == ' ' || game->grid[r][c] == '.')) {
        if (game->grid[r][c] == ' ')
            game->foodCount++;
        game->grid[r][c] = 'o';
        return true;
    } else
        return false;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////// Please submit all code above to OJ ////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Declarations of provided functions
void PlayGame(Game *game);

int main() {
    Game *game = NewGame(9, 18);
    // Add walls, foods, and pacman here.
    PlayGame(game);
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////// DO NOT MODIFY ANY CODE BELOW! ////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* This function prints the game grid with boundary,
 * and any message depending on game state.
 * Please make sure that, after any action is done,
 * game->state, game->score, and game->foodCount
 * are correctly updated.
 */
#ifdef _WIN32

#include <windows.h>

#endif // _WIN32

void PrintGame(Game *game) {
    if (!game || !game->grid) return;

// If Windows, clear console.
#ifdef _WIN32
    system("cls");
#else
    // Clears terminal screen
    fflush(stdout);
    system("clear");
#endif

    // The game grid
    printf(" ");
    for (int i = 0; i < game->columns; i++)
        printf("_");
    printf(" \n");

    for (int i = 0; i < game->rows; i++) {
        printf("|");
        for (int j = 0; j < game->columns; j++)
            printf("%c", game->grid[i][j]);
        printf("|\n");
    }
    printf("\\");
    for (int i = 0; i < game->columns; i++)
        printf("-");
    printf("/\n\n");

    // Messages on different states
    switch (game->state) {
        case losing:
            printf("Pacman died! Your score: %d\n", game->score);
            break;
        case onGoing:
            printf("Score: %d\n", game->score);
            printf("There are %d foods remaining!\n", game->foodCount);
            printf("Pacman wants food! (control by w/a/s/d/i, confirm by Enter)\n\n");
            break;
        case winning:
            printf("Victory! Your score: %d\n", game->score);
            break;
        default:
            printf("ERROR: invalid game state!\n");
    }
}

/* Plays the game, and calls EndGame on winning or losing.
 */
void PlayGame(Game *game) {

    // Prints the initial grid
    PrintGame(game);

    // Main loop of game. Terminates when the game ends.
    while (true) {
        // We only care about one character, but should eat the whole line of input.
        char input[127];
        input[0] = '\0';
        scanf("%[^\n]", input);
        // Handles the '\n'.
        getchar();
        Direction direction;
        switch (input[0]) {
            case 'w':
            case 'W':
                direction = up;
                break;
            case 'a':
            case 'A':
                direction = left;
                break;
            case 's':
            case 'S':
                direction = down;
                break;
            case 'd':
            case 'D':
                direction = right;
                break;
            case 'i':
            case 'I':
                direction = idle;
                break;
            default:
                PrintGame(game);
                continue;
        }

        // Pacman moves first.
        MovePacman(game, direction);

        // Wins if Pacman eats all the food, loses if Pacman bumps into a ghost.
        if (game->state != onGoing) {
            break;
        }

        // If you haven't implemented ghosts, this does nothing.
        MoveGhosts(game);

        // Loses if a ghost kills Pacman.
        if (game->state != onGoing) {
            break;
        }
        PrintGame(game);
    }

    // End game message
    PrintGame(game);
    printf("Press Enter to exit.\n");
    EndGame(game);
    getchar();
}