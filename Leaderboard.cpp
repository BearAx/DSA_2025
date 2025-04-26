#include <iostream>
#include <string>
using namespace std;

void Sort (string players[], int scores[], int N, int c)
{
    for (int i = 0; i < c; i++)
    {
        int var = scores[i];
        int a = i;

        for (int j = i + 1; j < N; j++)
        {
            if (var < scores[j])
            {
                var = scores[j];
                a = j;
            }
        }

        if (a != i)
        {
            swap(players[i], players[a]);
            swap(scores[i], scores[a]);
        }
    }
}

int main()
{
    int N;
    cin >> N;

    int c;
    cin >> c;

    if (c > N) c = N;

    string players[N];
    int scores[N];

    for (int i = 0; i < N; i++)
        cin >> players[i] >> scores[i];

    Sort(players, scores, N, c);

    for (int i = 0; i < c; i++)
        cout << players[i] << " " << scores[i] << endl;

    return  0;
}
