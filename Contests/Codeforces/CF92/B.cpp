#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int Abs(int x) {
	return x > 0 ? x : -x;
}

int get(int a, int b) {
	if(a > 0)	return a/b;
	else	return a/b-1;
}

int main() {
	int a, b, x1, y1, x2, y2;
	scanf("%d%d%d%d%d%d", &a, &b, &x1, &y1, &x2, &y2);
	int ans1 = 0, ans2 = 0;
	{
		int a1 = x1 + y1, a2 = x2 + y2;
		int b1 = get(a1, 2*a), b2 = get(a2, 2*a);
		ans1 += Abs(b1-b2);
	}
	{
		int a1 = x1-y1, a2 = x2-y2;
		int b1 = get(a1, 2*b), b2 = get(a2, 2*b);
		ans2 += Abs(b1-b2);
	}
//	printf("ans1 = %d ans2 = %d\n", ans1, ans2);
	printf("%d\n", max(ans1, ans2));
	return 0;
}

