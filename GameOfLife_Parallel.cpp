/*
 * Pongpihit Poonpiriyasup
 * Shaista Usman
 * CPSC 5600, Seattle University
 */

#include <iostream>
#include <chrono>
#include <time.h>
#include <future>

using namespace std;

const int GAME_TIME     = 5;     // game simulation period in second
const int GRID_ROW_SIZE = 20;    // the number of row for the game grid
const int GRID_COL_SIZE = 10000; // the number of column for the game grid

/**
 * a class for handling the computation of the Game of Life algorithm using the parallel approach
 */
class GameOfLife {
public:
    
    
    // an array of thread for computing the algorithm in parallel
    thread threadArray[GRID_ROW_SIZE];

    // an array for computing the state of the next generation
    int living_condition[2][9] = {
        { 0, 0, 0, 1, 0, 0, 0, 0, 0 }, // condition on dead
        { 0, 0, 1, 1, 0, 0, 0, 0, 0 }, // condition on alive
    };

    // an array of current generation of the game
    int current_gen[GRID_ROW_SIZE][GRID_COL_SIZE];
    
    // an array of next generation of the game
    int next_gen[GRID_ROW_SIZE][GRID_COL_SIZE];

    /**
     * a function for setting up the initial values for the game.
     */
    void setValues() {
        for(int i = 0; i < GRID_ROW_SIZE; i++)
            for(int j = 0; j< GRID_COL_SIZE; j++)
                current_gen[i][j] = 0;

        srand(time(NULL));
        for(int i = 1; i < GRID_ROW_SIZE-1; i++)
            for(int j = 1; j< GRID_COL_SIZE-1; j++)
                current_gen[i][j] = rand() % 100 > 50 ? 1 : 0;

        for(int i = 0; i < GRID_ROW_SIZE; i++)
            for(int j = 0; j< GRID_COL_SIZE; j++)
                next_gen[i][j] = 0;
    }

    /**
     * a function for computing the Game of Life algorithm.
     */
    void start() {
        long count = 0;
        auto start = chrono::steady_clock::now();
        while(chrono::duration<double,milli>(chrono::steady_clock::now() - start).count() < (GAME_TIME * 1000)){
            count++;
            // animation(250);

            for(int row = 1; row < GRID_ROW_SIZE-1; row++)
                threadArray[row] = thread(&GameOfLife::updateNextGen, this, row);
            for(int row = 1; row < GRID_ROW_SIZE-1; row++)
                threadArray[row].join();
            
            for(int row = 1; row < GRID_ROW_SIZE-1; row++)
                threadArray[row] = thread(&GameOfLife::swapNextGen, this, row);
            for(int row = 1; row < GRID_ROW_SIZE-1; row++)
                threadArray[row].join();

        }
        
        cout << "generations: " << count << endl;
    }
    
private:

    /**
     * a function for counting the number of live cell surrounding the input cell
     * @param row    input row index
     * @param col    input column index
     */
    int aliveNeighbourCount(int row, int col){
        int count = 0;
        for(int i = row-1; i <= row+1; i++)
            for(int j = col-1; j <= col+1; j++)
                count += current_gen[i][j];
        return count > 0 ? count - current_gen[row][col] : count;
    }

    /**
     * a function for computing the next generation based on the current generation on the input row
     * @param row    input row index
     */
    void updateNextGen(int row){
        for(int col = 1; col < GRID_COL_SIZE-1; col++)
            next_gen[row][col] = living_condition[current_gen[row][col]][aliveNeighbourCount(row,col)];
    }

    /**
     * a function for replacing the value of the current generation with the next generation on the input row
     * @param row    input row index
     */
    void swapNextGen(int row){
        for(int col = 1; col < GRID_COL_SIZE-1; col++)
            current_gen[row][col] = next_gen[row][col];
    }

    /**
     * a function for displaying the current generation
     * @param delay    the milliseconds delay on the display
     */
    void animation(int delay) {
        int count = 0;
        while(++count < GRID_ROW_SIZE)
            cout << endl;

        for(int i = 0; i < GRID_ROW_SIZE; i++){
            for(int j = 0; j < GRID_COL_SIZE; j++){
                if(i == 0 || i == GRID_ROW_SIZE-1)
                    cout << "--";
                else if(j == 0 || j == GRID_COL_SIZE-1)
                    cout << "| ";
                else
                    cout << (current_gen[i][j] ? "*" : " ") << " ";
            }
            cout << endl;
        }

        auto start = chrono::steady_clock::now();
        while(chrono::duration<double,milli>(chrono::steady_clock::now() - start).count() < delay);
    }
    
};


/**
 * The main function for computing the Game of Life algorithm
 */
int main() {
    
    cout << "game time:   " << GAME_TIME << " second(s)" << endl;
    cout << "game size:   " << GRID_ROW_SIZE << "x" << GRID_COL_SIZE << endl;

    GameOfLife game;
    game.setValues();
    game.start();

    return 0;
}

