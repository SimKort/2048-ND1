#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

class Game
{
    private:
        int board[4][4];
        int score = 0;
        int highScore;

    public:
        Game()
        {
            srand(time(0));
            int i1 = rand() % 4, y1 = rand() % 4;

            for (int i = 0; i < 4; i++)
                for (int y = 0; y < 4; y++)
                    board[i][y] = 0;

            int i2, y2;
            while (1)
            {
                i2 = rand() % 4;
                y2 = rand() % 4;
                if (i2 != i1 && y2 != y1)
                    break;
            }

            int number = rand() % 10;
            if (number == 9)
                board[i1][y1] = 4;
            else
                board[i1][y1] = 2;
            number = rand() % 10;
            if (number == 9)
                board[i2][y2] = 4;
            else
                board[i2][y2] = 2;

            ifstream ived("HighScore.txt");
            ived >> highScore;
            ived.close();
        }

        int(&getBoard())[4][4]
        {
            return board;
        }

        int getScore()
        {
            return highScore;
        }

        void display()
        {
            if (score > highScore)
                highScore = score;
            cout << "\n                      Press Esc to quit the game\n\n\n\n\n            Current Score: " << score << "\t\tHigh Score: " << highScore << "\n";
            for (int i = 0; i < 4; i++)
            {
                cout << "           ---------------------------------------------\n           ";
                for (int y = 0; y < 4; y++)
                {
                    if (board[i][y] == 0)
                        cout << "|          ";
                    else if (board[i][y] > 99999)
                        cout << "|  " << board[i][y] << "  ";
                    else if (board[i][y] > 9999)
                        cout << "|  " << board[i][y] << "   ";
                    else if (board[i][y] > 999)
                        cout << "|   " << board[i][y] << "   ";
                    else if (board[i][y] > 99)
                        cout << "|   " << board[i][y] << "    ";
                    else if (board[i][y] > 9)
                        cout << "|    " << board[i][y] << "    ";
                    else
                        cout << "|    " << board[i][y] << "     ";
                }
                cout << "|" << endl;
            }
            cout << "           ---------------------------------------------\n";
        }

        void addBlock()
        {
            srand(time(0));
            int i, y;
            while (1)
            {
                i = rand() % 4;
                y = rand() % 4;
                if (board[i][y] == 0)
                {
                    int number = rand() % 10;
                    if (number == 9)
                        board[i][y] = 4;
                    else
                        board[i][y] = 2;
                    break;
                }
            }
        }

        bool check(int tempBoard[4][4])
        {
            bool change = false;
            for (int i = 0; i < 4; i++)
                for (int y = 0; y < 4; y++)
                    if (tempBoard[i][y] != board[i][y])
                    {
                        change = true;
                        break;
                    }
            return change;
        }

        bool checkOver()
        {
            bool emptyBlock = false, adjacentBlocks = false;

            for (int i = 0; i < 4; i++)
                for (int y = 0; y < 4; y++)
                    if (board[i][y] == 0)
                    {
                        emptyBlock = true;
                        break;
                    }

            for (int i = 0; i < 3; i++)
                for (int y = 0; y < 3; y++)
                    if (board[i][y] == board[i + 1][y] || board[i][y] == board[i][y + 1])
                    {
                        adjacentBlocks = true;
                        break;
                    }

            return (emptyBlock || adjacentBlocks);
        }

        void updateScore(int mergedValue)
        {
            score += mergedValue;
        }
};


class Movement
{
    public:
        static void moveUp(Game& game)
        {
            int (&board)[4][4] = game.getBoard(), leftIndex, rightIndex;

            for (int y = 0; y < 4; y++)
            {
                leftIndex = 0, rightIndex = y;
                for (int i = 1; i < 4; i++)
                {
                    if (board[i][y] != 0)
                    {
                        if (board[i - 1][y] == 0 || board[i - 1][y] == board[i][y])
                        {
                            if (board[leftIndex][rightIndex] == board[i][y])
                            {
                                board[leftIndex][rightIndex] *= 2;
                                game.updateScore(board[leftIndex][rightIndex]);
                                board[i][y] = 0;
                            }
                            else
                            {
                                if (board[leftIndex][rightIndex] == 0)
                                {
                                    board[leftIndex][rightIndex] = board[i][y];
                                    board[i][y] = 0;
                                }
                                else
                                {
                                    board[++leftIndex][rightIndex] = board[i][y];
                                    board[i][y] = 0;
                                }
                            }
                        }
                        else
                            leftIndex++;
                    }
                }
            }
        }

        static void moveRight(Game& game)
        {
            int(&board)[4][4] = game.getBoard(), leftIndex, rightIndex;
            for (int i = 0; i < 4; i++)
            {
                leftIndex = i, rightIndex = 3;
                for (int y = 2; y >= 0; y--)
                {
                    if (board[i][y] != 0)
                    {
                        if (board[i][y + 1] == 0 || board[i][y + 1] == board[i][y])
                        {
                            if (board[leftIndex][rightIndex] == board[i][y])
                            {
                                board[leftIndex][rightIndex] *= 2;
                                game.updateScore(board[leftIndex][rightIndex]);
                                board[i][y] = 0;
                            }
                            else
                            {
                                if (board[leftIndex][rightIndex] == 0)
                                {
                                    board[leftIndex][rightIndex] = board[i][y];
                                    board[i][y] = 0;
                                }
                                else
                                {
                                    board[leftIndex][--rightIndex] = board[i][y];
                                    board[i][y] = 0;
                                }
                            }
                        }
                        else
                            rightIndex--;
                    }
                }
            }
        }

        static void moveDown(Game& game)
        {
            int(&board)[4][4] = game.getBoard(), leftIndex, rightIndex;
            for (int y = 0; y < 4; y++)
            {
                leftIndex = 3, rightIndex = y;
                for (int i = 2; i >= 0; i--)
                {
                    if (board[i][y] != 0)
                    {
                        if (board[i + 1][y] == 0 || board[i + 1][y] == board[i][y])
                        {
                            if (board[leftIndex][rightIndex] == board[i][y])
                            {
                                board[leftIndex][rightIndex] *= 2;
                                game.updateScore(board[leftIndex][rightIndex]);
                                board[i][y] = 0;
                            }
                            else
                            {
                                if (board[leftIndex][rightIndex] == 0)
                                {
                                    board[leftIndex][rightIndex] = board[i][y];
                                    board[i][y] = 0;
                                }
                                else
                                {
                                    board[--leftIndex][rightIndex] = board[i][y];
                                    board[i][y] = 0;
                                }
                            }
                        }
                        else
                            leftIndex--;
                    }
                }
            }
        }

        static void moveLeft(Game& game)
        {
            int(&board)[4][4] = game.getBoard(), leftIndex, rightIndex;
            for (int i = 0; i < 4; i++)
            {
                leftIndex = i, rightIndex = 0;
                for (int y = 1; y < 4; y++)
                {
                    if (board[i][y] != 0)
                    {
                        if (board[i][y - 1] == 0 || board[i][y - 1] == board[i][y])
                        {
                            if (board[leftIndex][rightIndex] == board[i][y])
                            {
                                board[leftIndex][rightIndex] *= 2;
                                game.updateScore(board[leftIndex][rightIndex]);
                                board[i][y] = 0;
                            }
                            else
                            {
                                if (board[leftIndex][rightIndex] == 0)
                                {
                                    board[leftIndex][rightIndex] = board[i][y];
                                    board[i][y] = 0;
                                }
                                else
                                {
                                    board[leftIndex][++rightIndex] = board[i][y];
                                    board[i][y] = 0;
                                }
                            }
                        }
                        else
                            rightIndex++;
                    }
                }
            }
        }
};


class Start
{
    public:
        static void startMenu()
        {
            cout << "\n\n\n\                          2048 GAME\n\n\n            Use your arrow keys to move the tiles.\n   Tiles with the same number merge into one when they touch.\n                  Add them up to reach 2048!\n\n\n                    Press any key to start";
            _getch();
            system("cls");
        }
};


int main()
{
    Start::startMenu();
    Game game;
    game.display();
    int key;
    bool goal = true;
    while (1)
    {
        int(&board)[4][4] = game.getBoard(), tempBoard[4][4];
        for (int i = 0; i < 4; ++i)
            for (int y = 0; y < 4; ++y)
                tempBoard[i][y] = board[i][y];
        
        key = _getch();
        system("cls");

        if (key == 72)
            Movement::moveUp(game);
        else if (key == 77)
            Movement::moveRight(game);
        else if (key == 80)
            Movement::moveDown(game);
        else if (key == 75)
            Movement::moveLeft(game);
        else if (key == 27)
            break;
        
        if (game.check(tempBoard))
            game.addBlock();
        game.display();
        
        if (goal)
        {
            for (int i = 0; i < 4; ++i)
                for (int y = 0; y < 4; ++y)
                    if (board[i][y] == 2048)
                    {
                        system("Color 02");
                        cout << "\n\n                             You won!!!\n               If you want to continue press any key\n\n\n";
                        goal = false;
                        _getch();
                        system("Color 07");
                        break;
                    }
        }

        if (!game.checkOver())
        {
            system("Color 04");
            cout << "\n\n                           Game Over :(\n\n\n";
            _getch();
            break;
        }
    }

    int highScore = game.getScore();
    ofstream isved("HighScore.txt");
    isved << highScore;
    isved.close();
    return 0;
}