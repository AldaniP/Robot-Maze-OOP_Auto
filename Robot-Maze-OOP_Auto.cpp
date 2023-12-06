#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Robot {
public:
    Robot(int N, int M) : N(N), M(M), arena(N, vector<char>(M)), start_row(-1), start_col(-1), finish_row(-1), finish_col(-1) {}

    void readArena() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> arena[i][j];
                if (arena[i][j] == '*') {
                    start_row = i;
                    start_col = j;
                } else if (arena[i][j] == '$') {
                    finish_row = i;
                    finish_col = j;
                }
            }
        }
    }

    void printArena() const {
        for (size_t i = 0; i < arena.size(); ++i) {
            const vector<char>& row = arena[i];
            for (size_t j = 0; j < row.size(); ++j) {
                cout << row[j];
            }
            cout << endl;
        }
    }

    bool isValidMove(int row, int col) const {
        return row >= 0 && row < N && col >= 0 && col < M && arena[row][col] != '#' && arena[row][col] != 'o';
    }

    bool bfs() {
        queue<pair<int, int> > q;
        vector<vector<bool> > visited(N, vector<bool>(M, false));
        vector<vector<pair<int, int> > > parent(N, vector<pair<int, int> >(M, make_pair(-1, -1)));

        q.push(make_pair(start_row, start_col));
        visited[start_row][start_col] = true;

        while (!q.empty()) {
            int current_row = q.front().first;
            int current_col = q.front().second;
            q.pop();

            if (current_row == finish_row && current_col == finish_col) {
                // Reconstruct path
                int row = finish_row;
                int col = finish_col;
                while (row != -1 && col != -1) {
                    path.push_back(make_pair(row, col));
                    int temp_row = parent[row][col].first;
                    int temp_col = parent[row][col].second;
                    row = temp_row;
                    col = temp_col;
                }
                reverse(path.begin(), path.end());
                return true; // Finish found
            }

            // Explore neighbors (up, down, left, right)
            int dr[] = {-1, 1, 0, 0};
            int dc[] = {0, 0, -1, 1};

            for (int i = 0; i < 4; ++i) {
                int new_row = current_row + dr[i];
                int new_col = current_col + dc[i];

                if (isValidMove(new_row, new_col) && !visited[new_row][new_col]) {
                    q.push(make_pair(new_row, new_col));
                    visited[new_row][new_col] = true;
                    parent[new_row][new_col] = make_pair(current_row, current_col);
                }
            }
        }

        return false; // Finish not found
    }

    void markPath() {
        for (size_t i = 0; i < path.size(); ++i) {
            int row = path[i].first;
            int col = path[i].second;
            if (arena[row][col] != '*' && arena[row][col] != '$') {
                arena[row][col] = '#';
            }
        }

        arena[start_row][start_col] = '#'; // Change the start symbol to "#"
        arena[finish_row][finish_col] = '*'; // Change the finish symbol to represent the robot
    }

private:
    int N, M;
    vector<vector<char> > arena;
    int start_row, start_col, finish_row, finish_col;
    vector<pair<int, int> > path;
};

int main() {
    int N, M;
    cin >> N >> M;

    if (N < 2 || N > 100 || M < 2 || M > 100) {
        cerr << "Input tidak sesuai batasan" << endl;
        return 1;
    }

    Robot robot(N, M);
    robot.readArena();

    // Use BFS to check if there is a path to the finish and find the path
    if (!robot.bfs()) {
        cerr << "Robot Tidak Mencapai Finish" << endl;
        return 1;
    }

    // Mark the path in the arena
    robot.markPath();

    // Print the arena with the path
    cout << endl;
    robot.printArena();

    cout << "Robot Mencapai Finish" << endl;

    return 0;
}
