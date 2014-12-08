#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef __int64 ll;
const int N = 100+5;

int a[N][N], vis[N][N], is[N<<1], s[N<<1];
int n, m;
ll K, dp[N<<1][N<<1];

inline void Add(ll &x, ll y) {
    x += y;
    if(x > K)   x = K+1;
}

int main() {
    scanf("%d%d%I64d", &n, &m, &K);
    for(int i = 1;i <= n; i++) {
        for(int j = 1;j <= m; j++)
            scanf("%d", &a[i][j]);
    }
    int tot = 0;
    for(int i = 1;i <= n; i++) {
        for(int j = 1;j <= m; j++) if(!vis[i][j]){
            int x = i, y = j;
            ++tot;
            is[tot] = 1<<30;
            while(x <= n && y >= 1) {
                vis[x][y] = tot;
                is[tot] = min(is[tot], a[x][y]);
                x ++; y --;
            }
        }
    }
    memset(s, -1, sizeof(s));
    s[1] = 0; s[tot] = 1;
    int sum = 2;
    while(sum < tot) {
        int id = -1;
        for(int i = 1;i <= tot; i++) if(s[i] == -1 && (id==-1 || is[id]>is[i]))
            id = i;
        s[id] = 0;
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for(int i = 1;i <= tot; i++) {
            for(int j = 0;j <= tot; j++) if(dp[i-1][j]) {
                if(s[i] != 1) {
                    Add(dp[i][j+1], dp[i-1][j]);
                }
                if(s[i] != 0 && j > 0) {
                    Add(dp[i][j-1], dp[i-1][j]);
                }
            }
        }
        if(dp[tot][0] < K) {
            K -= dp[tot][0];
            s[id] = 1;
        }
        sum++;
    }
    for(int i = 1;i <= n; i++) {
        for(int j = 1;j <= m; j++)
            printf("%c", s[vis[i][j]] ? ')' : '(');
        puts("");
    }
    return 0;
}

