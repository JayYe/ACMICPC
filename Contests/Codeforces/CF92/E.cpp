#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100000+5;
const double eps = 1e-8;

struct Edge { int v, next; }edge[N<<1];

int head[N], E, n, x[N], y[N], son[N];

double dp[N], go[N], ext[N], entr[N], sum_e[N];

void init() {
    memset(head, -1, sizeof(head));
    E = 0;
}

void newedge(int u, int v) {
    edge[E].v = v; edge[E].next = head[u];
    head[u] = E++;
}

void dfs(int u, int pre) {
    son[u] = 1;
    sum_e[u] = ext[u];
    for(int i = head[u];i != -1;i = edge[i].next) {
        int v = edge[i].v;
        if(v == pre)    continue;
        dfs(v, u);
        son[u] += son[v];
        sum_e[u] += sum_e[v];
    }
    dp[u] = 0;
    for(int i = head[u];i != -1;i = edge[i].next) {
        int v = edge[i].v;
        if(v == pre)    continue;
        dp[u] += dp[v] + sum_e[v]*(son[u] - son[v]);
    }
//    printf("dp[%d] = %f\n", u, dp[u]);
}

void DFS(int u, int pre, double tmp) {
    go[u] = 0;
    for(int i = head[u];i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if(v == pre)    continue;
        go[u] += dp[v] + sum_e[v]*(n - son[v]);
    }
    go[u] += tmp + (1.0-sum_e[u])*son[u];
//    printf("go[%d] = %f\n", u, go[u]);
    for(int i = head[u];i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if(v == pre)    continue;
        double fk = go[u] - (dp[v] + sum_e[v]*(n-son[v]));
        fk -= (1.0-sum_e[v]-ext[u])*(son[v]);
        DFS(v, u, fk);
        /*
        double fk = 0;
        int sum = n - son[v];
        for(int j = head[u];j != -1;j = edge[j].next) {
            int vv = edge[j].v;
            if(vv == v || vv == pre) continue;
            fk += dp[vv] + sum_e[vv]*(sum - son[vv]);
        }
        fk += tmp + (1.0 - sum_e[u])*(son[u]-son[v]);
        DFS(v, u, fk);
        */
    }
}

int main() {
    init();
    scanf("%d", &n);
    int u, v;
    for(int i = 0;i < n-1; i++) {
        scanf("%d%d", &u, &v);
        newedge(u, v);
        newedge(v, u);
    }
    int sumx = 0, sumy = 0;
    for(int i = 1;i <= n; i++) {
        scanf("%d%d", &x[i], &y[i]);
        sumx += x[i]; sumy += y[i];
    }
    for(int i = 1;i <= n; i++) {
        entr[i] = 1.0*x[i]/sumx;
        ext[i] = 1.0*y[i]/sumy;
    }
    dfs(1, -1);
    DFS(1, -1, 0);
    double ans = 0;
    for(int i = 1;i <= n; i++)  ans += entr[i]*go[i];
    printf("%.15f\n", ans);
    return 0;
}

