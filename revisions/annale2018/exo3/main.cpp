#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

#define N 3

int main () {
	pid_t pids [N];
	memset(pids,0,N*sizeof(pid_t));
	pid_t p;

	for (int i = 0 ; i < N ; i++) {
		p = fork();
		pids [i] = p;
		if (p && i == N-1) {
			for (int j = 0 ; j < N ; j++) {
				if (pids[j] != 0)
					waitpid(pids[j],0,0);
			}
		} else if (!p) {
			pids [i] = fork();
		}
	}
	for (int j = 0 ; j < N ; j++) {
		if (pids[j] != 0)
			waitpid(pids[j],0,0);
	}

	return 0;
}


