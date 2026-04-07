#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define POS_MAX 1e18
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
template <class T> void _print(queue <T> v) {cerr << "[ "; while(v.size()) {_print(v.front()); cerr << " "; v.pop();} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

const pair<char, pair<int, int>> dir[4] = {{'L', {0, -1}}, {'R', {0, 1}}, {'D', {1, 0}}, {'U', {-1, 0}}};

bool isValid(int x, int y, int n, int m)
{
    return x >= 0 && y >= 0 && x < n && y < m;
}

void bfs(int n, vector<vector<int>> &connections, vector<int> &dist, vector<int> &par)
{
    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> computers;
    // queue<array<int, 3>> cordinates;
    computers.push({dist[1], 1});
     
    while(!computers.empty()){
        auto curr = computers.top();
        computers.pop();
        int curr_dist = curr[0];
        int comp = curr[1];

        
        for(int neigh : connections[comp]){
            if((curr_dist+1) < dist[neigh])
            {
                dist[neigh] = curr_dist+1;
                par[neigh] = comp;
                computers.push({dist[neigh], neigh});
            }
        }
    }
}

class DSU
{
public:
    vector<int> size;
    vector<int> par;
    DSU(int n)
    {
        size.resize(n+1, 0);
        par.resize(n+1);
        for(int i = 0; i <= n; i++)
        {
            par[i] = i;
        }
    }

    int findPar(int u)
    {
        if(par[u] == u) return u;
        return par[u] = findPar(par[u]);
    }

    void doUnion(int u, int v)
    {
        int u_par = findPar(u);
        int v_par = findPar(v);

        if(u_par == v_par) return;
        if(size[u_par] > size[v_par])
        {
            size[u_par]++;
            par[v_par] = u_par;
        }
        else
        {
            size[v_par]++;
            par[u_par] = v_par;
        }
    }

    vector<int> getUniquePar()
    {
        set<int> uni_set_par;
        for(int it : par)
        {
            uni_set_par.insert(findPar(it));
        }
        uni_set_par.erase(0);
        vector<int> uni_par(uni_set_par.begin(), uni_set_par.end());

        return uni_par;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> connections(n+1);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        connections[a].push_back(b);
        connections[b].push_back(a);
    }

    vector<int> team(n+1, -1);
    int curr_team = 0;
    for(int i = 1; i <= n; i++)
    {
        if(team[i] == -1)
        {
            // perform bfs
            queue<int> pupil;
            pupil.push(i);
            team[i] = curr_team;
            
            while(pupil.size())
            {
                curr_team = !curr_team;
                int curr_size = pupil.size();
                for(int x = 0; x < curr_size; x++)
                {
                    int curr_pupil = pupil.front();
                    pupil.pop();
                    for(int friend_p : connections[curr_pupil])
                    {
                        if(team[friend_p] == -1)
                        {
                            team[friend_p] = curr_team;
                            pupil.push(friend_p);
                        }
                        else if(team[friend_p] == !curr_team)
                        {
                            cout << "IMPOSSIBLE" << endl;
                            return;
                        }
                    }
                }
            }
        }
    }

    for(int i = 1; i <= n; i++)
    {
        cout << (team[i] ? 1 : 2) << " ";
    }
    cout << endl;
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