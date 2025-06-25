#include <bits/stdc++.h>

using namespace std;

class game2048

{

    // vector<vector<int>>matrix(4,vector<int>(4)); // Constructor-like syntax is not allowed for data member initialization

    // not allowed in the class

    vector<vector<int>> matrix = vector<vector<int>>(4, vector<int>(4));

    // char ch; //Take input from user like N,S,E,W

    set<int> st; // Keep the list of available space.

public:
    long long score = 0;

    static long long bestScore;

    game2048()

    {

        // Initializing the list of available space as all space are empty in the begining.

        for (int i = 0; i < 16; i++)

        {

            st.insert(i);
        }
    }

    void randomGeneration();

    void operation(char);

    void startGame(game2048 &);

    void displayBoard()

    {

        cout << '\n';

        for (auto ele : matrix)

        {

            for (auto ele : ele)

            {

                cout << setw(3) << ele << ' ';
            }

            cout << "\n\n\n";
        }

        cout << '\n';

        cout << "score = " << score << '\n';

        bestScore = max(bestScore, score);
    }

    int coordinate_to_number(pair<int, int> p)

    {

        return p.first * 4 + (p.second + 1) - 1;
    }

    pair<int, int> number_to_coordinate(int num)

    {

        int x = num / 4; // row index

        int y = num % 4; // column index

        return make_pair(x, y);
    }
};

long long game2048::bestScore = 0;

void game2048::randomGeneration()

{

    srand(time(0));

    int num = rand() % st.size(); // we will insert 2 at position (index) num in the set.

    auto itr = st.begin();

    for (int i = 0; i < num; i++)

    {

        itr++;
    }

    pair<int, int> index = number_to_coordinate(*itr);

    st.erase(itr);

    matrix[index.first][index.second] = 2;
}

void game2048::operation(char ch)

{

    if (ch == 'n')

    {

        for (int j = 0; j < 4; j++)

        {

            int limit = 0, value = 0;

            for (int i = 0; i < 4; i++)

            {

                if (matrix[i][j] != 0)

                {

                    // we need to check if the number is equal to the ajacent number or not.

                    // if(limit==0) //In this case, there is no adjacent number.

                    if (limit != 0 && matrix[i][j] == value)

                    {

                        matrix[limit - 1][j] += matrix[i][j];

                        score += matrix[limit - 1][j];

                        matrix[i][j] = 0;

                        value = -1;

                        st.insert(coordinate_to_number(make_pair(i, j))); // to insert the coordinate into the list of empty position
                    }

                    else

                    {

                        swap(matrix[i][j], matrix[limit][j]);

                        st.erase(coordinate_to_number(make_pair(limit, j))); // to remove the coordinate from the list of empty position

                        if (i != limit)

                        {

                            st.insert(coordinate_to_number(make_pair(i, j))); // to insert the coordinate into the list of empty position
                        }

                        value = matrix[limit][j];

                        limit++;
                    }
                }
            }
        }
    }

    else if (ch == 's')

    {

        for (int j = 0; j < 4; j++)

        {

            int limit = 3, value = 0;

            for (int i = 3; i >= 0; i--)

            {

                if (matrix[i][j] != 0)

                {

                    // we need to check if the number is equal to the ajacent number or not.

                    // if(limit==3) //In this case, there is no adjacent number.

                    if (limit != 3 && matrix[i][j] == value)

                    {

                        matrix[limit + 1][j] += matrix[i][j];

                        score += matrix[limit + 1][j];

                        matrix[i][j] = 0;

                        value = -1;

                        st.insert(coordinate_to_number(make_pair(i, j)));
                    }

                    else

                    {

                        swap(matrix[i][j], matrix[limit][j]);

                        st.erase(coordinate_to_number(make_pair(limit, j)));

                        if (i != limit)

                        {

                            st.insert(coordinate_to_number(make_pair(i, j)));
                        }

                        value = matrix[limit][j];

                        limit--;
                    }
                }
            }
        }
    }

    else if (ch == 'w')

    {

        for (int i = 0; i < 4; i++)

        {

            int limit = 0, value = 0;

            for (int j = 0; j < 4; j++)

            {

                if (matrix[i][j] != 0)

                {

                    // we need to check if the number is equal to the ajacent number or not.

                    // if(limit==0) //In this case, there is no adjacent number.

                    if (limit != 0 && matrix[i][j] == value)

                    {

                        matrix[i][limit - 1] += matrix[i][j];

                        score += matrix[i][limit - 1];

                        matrix[i][j] = 0;

                        value = -1;

                        st.insert(coordinate_to_number(make_pair(i, j)));
                    }

                    else

                    {

                        swap(matrix[i][j], matrix[i][limit]);

                        st.erase(coordinate_to_number(make_pair(i, limit)));

                        if (j != limit)

                        {

                            st.insert(coordinate_to_number(make_pair(i, j)));
                        }

                        value = matrix[i][limit];

                        limit++;
                    }
                }
            }
        }
    }

    else

    {

        for (int i = 0; i < 4; i++)

        {

            int limit = 3, value = 0;

            for (int j = 3; j >= 0; j--)

            {

                if (matrix[i][j] != 0)

                {

                    // we need to check if the number is equal to the ajacent number or not.

                    // if(limit==3) //In this case, there is no adjacent number.

                    if (limit != 3 && matrix[i][j] == matrix[i][limit + 1])

                    {

                        matrix[i][limit + 1] += matrix[i][j];

                        score += matrix[i][limit + 1];

                        matrix[i][j] = 0;

                        value = -1;

                        st.insert(coordinate_to_number(make_pair(i, j)));
                    }

                    else

                    {

                        swap(matrix[i][j], matrix[i][limit]);

                        st.erase(coordinate_to_number(make_pair(i, limit)));

                        if (j != limit)

                        {

                            st.insert(coordinate_to_number(make_pair(i, j)));
                        }

                        value = matrix[i][limit];

                        limit--;
                    }
                }
            }
        }
    }
}

void game2048::startGame(game2048 &obj)

{

    obj.randomGeneration();

    obj.randomGeneration();

    obj.displayBoard();

    while (!obj.st.empty())

    {

        char ch;

        cout << "Enter the command to play or press E to end\n";

        cin >> ch;

        if (ch == 'E')

        {

            return;
        }

        obj.operation(ch);

        obj.randomGeneration();

        obj.displayBoard();
    }
}

void solve()

{

    char ch = 'R';

    while (ch == 'R')

    {

        game2048 g1;

        g1.startGame(g1);

        cout << "\nGame Over\t score: " << g1.score << "\t Best Score: " << game2048::bestScore << '\n';

        cout << "Press R to restart or any other key to Exit\n";

        cin >> ch;
    }

    cout << "*** Thank You ***\n";
}

signed main()

{

    // ios_base::sync_with_stdio(0);

    // cin.tie(0);
    // cout.tie(0);

    solve();
}