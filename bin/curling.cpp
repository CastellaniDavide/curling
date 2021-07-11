/**
 * @file curling.cpp
 *
 * @version 01.01 time_now
 *
 * @brief curling
 *
 * @ingroup curling
 * (Note: this needs exactly one @defgroup somewhere)
 *
 * @author Castellani Davide
 *
 * Contact: contacts@castellanidavide.it
 *
 */

// Includes
#include <bits/stdc++.h>
using namespace std;

#define DEBUG

// Variabiles
int N, tmp, tmp2;
bool ended;
vector<vector<int>> connections;
vector<vector<int>> olds;
vector<bool> viewed;

void solve(vector<int> previous, vector<bool> visited, int current)
{
  olds.push_back(previous);
  for (size_t i = 0; i < connections[current].size(); ++i)
  {
    if (viewed[i])
    {
      for (size_t j = 0; j < olds.size(); j++)
      {
        if (olds[j][0] == connections[current][i] && find(olds[j].begin(), olds[j].end(), connections[current][i]) == olds[j].end())
        {
          vector<int> tmp3;
          tmp3.push_back(current);
          for (size_t o = 0; o < olds[j].size(); ++o)
            tmp3.push_back(olds[j][o]);

          if (tmp3.size() == N)
          {
            cout << tmp3.size() - 1 << endl;
            for (size_t j = 0; j < tmp3.size() - 1; ++j)
            {
              cout << tmp3[j] + 1 << " " << tmp3[j + 1] + 1 << endl;
            }
            ended = true;
            exit(0);
          }
          olds.push_back(tmp3);
        }
      }
    }
    else
    {
      if (!visited[connections[current][i]])
      { // if not taken previously
        vector<int> p(previous);
        p.push_back(connections[current][i]);
        vector<bool> v(visited);
        v.push_back(connections[current][i]);
        if (p.size() == N)
        {
          cout << p.size() - 1 << endl;
          for (size_t j = 0; j < p.size() - 1; ++j)
          {
            cout << p[j] + 1 << " " << p[j + 1] + 1 << endl;
          }
          ended = true;
          exit(0);
        }
        solve(p, v, connections[current][i]);
      }
      viewed[i] = true;
    }
  }
}

// Main code
int main()
{
  // Cncomment the following lines if you want to read/write from files
  freopen("input.txt", "r", stdin);

#ifndef DEBUG
  freopen("output.txt", "w", stdout);
#endif // DEBUG

  // Input
  cin >> N;
  connections.resize(N);
  ended = false;
  viewed.resize(N, false);

  for (size_t i = 0; i < N * (N - 1) / 2; ++i)
  {
    cin >> tmp >> tmp2;
    connections[tmp - 1].push_back(tmp2 - 1);
  }

#ifdef DEBUG
  for (size_t i = 0; i < N; ++i)
  {
    cout << i << ": ";
    for (size_t j = 0; j < connections[i].size(); ++j)
    {
      cout << connections[i][j] << " ";
    }
    cout << endl;
  }
#endif // DEBUG

  for (size_t i = 1; i < N; ++i)
  {
    if (!ended)
    {
      vector<int> previous;
      previous.push_back(i);
      vector<bool> visited(N, false);
      visited[i] = true;
      solve(previous, visited, i);
    }
  }

  // End
  return 0;
}
