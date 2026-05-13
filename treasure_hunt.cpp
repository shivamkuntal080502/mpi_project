#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

const int GRID_SIZE = 10;
const int MAX_TURNS = 50;

struct Player {
    int x;
    int y;
};

void printGrid(vector<Player>& players, int treasureX, int treasureY) {
    vector<vector<char>> grid(GRID_SIZE, vector<char>(GRID_SIZE, '.'));

    grid[treasureX][treasureY] = 'T';
for (int i = 0; i < players.size(); i++) {
        grid[players[i].x][players[i].y] = '0' + i;
    }

    cout << "\n========================\n";

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    cout << "========================\n";
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
srand(time(0) + rank);

    Player myPlayer;

    myPlayer.x = rand() % GRID_SIZE;
    myPlayer.y = rand() % GRID_SIZE;

    int treasureX, treasureY;

    if (rank == 0) {
        treasureX = rand() % GRID_SIZE;
        treasureY = rand() % GRID_SIZE;

        cout << "Treasure Hidden at Secret Location!" << endl;
    }

    MPI_Bcast(&treasureX, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&treasureY, 1, MPI_INT, 0, MPI_COMM_WORLD);

    vector<Player> allPlayers(size);

    int winner = -1;

    double startTime = MPI_Wtime();
 for (int turn = 1; turn <= MAX_TURNS; turn++) {

        // Parallel movement computation
        #pragma omp parallel
        {
            int move = rand() % 4;

            #pragma omp critical
            {
                if (move == 0 && myPlayer.x > 0)
                    myPlayer.x--;
                else if (move == 1 && myPlayer.x < GRID_SIZE - 1)
                    myPlayer.x++;
                else if (move == 2 && myPlayer.y > 0)
                    myPlayer.y--;
                else if (move == 3 && myPlayer.y < GRID_SIZE - 1)
                    myPlayer.y++;
            }
        }

        MPI_Gather(
            &myPlayer,
            sizeof(Player),
            MPI_BYTE,
           allPlayers.data(),
            sizeof(Player),
            MPI_BYTE,
            0,
            MPI_COMM_WORLD
        );

        if (rank == 0) {
            cout << "\nTurn " << turn << endl;

            printGrid(allPlayers, treasureX, treasureY);

            for (int i = 0; i < size; i++) {
                if (allPlayers[i].x == treasureX &&
                    allPlayers[i].y == treasureY) {

                    winner = i;
                    break;
                }
            }
        }

        MPI_Bcast(&winner, 1, MPI_INT, 0, MPI_COMM_WORLD);
if (winner != -1) {
            if (rank == 0) {
                cout << "\nPlayer " << winner
                     << " found the treasure!" << endl;
            }
            break;
        }

        sleep(1);
    }

    double endTime = MPI_Wtime();

    if (rank == 0) {
        cout << "\nGame Finished" << endl;
        cout << "Execution Time: "
             << endTime - startTime
             << " seconds" << endl;
    }

    MPI_Finalize();

    return 0;
}
