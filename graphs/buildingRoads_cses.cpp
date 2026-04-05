#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MOD 1000000007
#define endl '\n'
#define ll long long
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
typedef unsigned long long ull;
typedef long double lld;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif


mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]" << endl;}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

const pair<char, pair<int, int>> dir[4] = {{'L', {0, -1}}, {'R', {0, 1}}, {'D', {1, 0}}, {'U', {-1, 0}}};

bool isValid(int x, int y, int n, int m)
{
    return x >= 0 && y >= 0 && x < n && y < m;
}

void bfs(int x, int y, int n, int m, vector<vector<int>> &vis, vector<vector<char>> &grid, vector<vector<char>> &par)
{
    // priority_queue<int[3], vector<int[3]>, greater<int[3]>> cordinates;
    queue<array<int, 3>> cordinates;
    cordinates.push({vis[x][y], x, y});
     
    while(!cordinates.empty()){
        auto cords = cordinates.front();
        cordinates.pop();
        int dist = cords[0];
        int cord_x = cords[1];
        int cord_y = cords[2];

        for(auto dir_it : dir){
            char dir_char = dir_it.first;
            int new_x = cord_x + dir_it.second.first;
            int new_y = cord_y + dir_it.second.second;
            
            if(isValid(new_x, new_y, n, m) && grid[new_x][new_y] != '#' && (dist+1 < vis[new_x][new_y])) 
            {
                cordinates.push({dist+1 ,new_x, new_y});
                vis[new_x][new_y] = dist+1;
                par[new_x][new_y] = dir_char;
            }
        }
    }
}

void solve()
{
    int n, m;
    int st_x, st_y, end_x, end_y;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
        {
            char x;
            cin >> x;
            grid[i][j] = x;
            if(x == 'A')
            {
                st_x = i;
                st_y = j;
            }
            if(x == 'B'){
                end_x = i;
                end_y = j;
            }
        }
    }
    
    vector<vector<int>> vis(n, vector<int>(m, INT_MAX));
    vector<vector<char>> par(n, vector<char>(m));
    vis[st_x][st_y] = 0;
    
    bfs(st_x, st_y, n, m, vis, grid, par);

    debug(vis);
    debug(grid);
    debug(par);

    if(vis[end_x][end_y] != INT_MAX)
    {
        cout << "YES" << endl;
        cout << vis[end_x][end_y] << endl;

        string path = "";
        while(end_x != st_x || end_y != st_y)
        {
            path += par[end_x][end_y];
            switch (par[end_x][end_y])
            {
                case 'L':
                    end_y++;
                    break;
                case 'R':
                    end_y--;
                    break;
                case 'U':
                    end_x++;
                    break;
                case 'D':
                    end_x--;
                    break;
                default:
                    break;
            }
        }
        reverse(path.begin(), path.end());
        cout << path << endl;
    }
    else cout << "NO" << endl;
}


signed main() {
    auto begin = std::chrono::high_resolution_clock::now();
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

#ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  freopen("Error.txt", "w", stderr);
#endif
    // int t;
    // cin >> t;
    // while (t--) {
        solve(); 
    // }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
    return 0;
}