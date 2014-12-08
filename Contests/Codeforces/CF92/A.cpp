#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int cnt[33], ans[1111], vis[1111];
char s[1111];

int main() {
	scanf("%s", s);
	int len = strlen(s);
	for(int i = 0;i < len; i++)	cnt[s[i]-'a']++;
	int mx = 0, id = -1;
	for(int i = 0;i < 26; i++) if(mx < cnt[i]) {
		mx = cnt[i]; id = i;
	}
	for(int i = 2;i <= len; i++) {
		if(!vis[i]) {
			for(int j = i*2;j <= len; j += i)
				vis[j] = 1;
		}
		if(!vis[i]) {
			if(i*2 <= len) {
				mx--;
				ans[i] = id+1;
			}
		}
		else {
			mx--;
			ans[i] = id+1;
		}
	}
	if(mx < 0)	return puts("NO") , 0;
	cnt[id] = mx;
	for(int i = 1;i <= len; i++) if(!ans[i]) {
		for(int j = 0;j < 26; j++) if(cnt[j] > 0) {
			cnt[j]--;
			ans[i] = j+1;
			break;
		}
	}
	puts("YES");
	for(int i = 1;i <= len; i++)
		printf("%c", ans[i]-1+'a');
	puts("");
	return 0;
}

