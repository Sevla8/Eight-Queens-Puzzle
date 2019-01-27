#include <stdio.h>
#include <stdlib.h>

struct Coord {
	int x;
	int y;
};
typedef struct Coord Coord;

int abs(int x) {
   if (x < 0)
      return -x;
   return x;
}

int conflict(int N, int M, Coord* queen) {
	for (int i = 0; i < M; i += 1)  {
		if (queen[i].y == queen[M].y)
			return 1;
		if (abs(queen[i].x - queen[M].x) == abs(queen[i].y - queen[M].y))
			return 1;
	}
	return 0;
}

void print(int N, Coord* queen) {
	for (int i = 0; i < N; i += 1) {
		for (int j = 0; j < N; j += 1) {
			if (queen[i].x == i && queen[i].y == j)
				printf("D");
			else
				printf("*");
		}
		printf("\n");
	}
}

int find(int N, int M, Coord* queen) {
	// version #1
	if (M == N)
		return 1;
	if (queen[M].y >= N) {
		if (!M)
			return 0;
		queen[M-1].y += 1;
		for (int i = M; i < N; i += 1) {
			queen[i].x = i;
			queen[i].y = 0;
		}
		return find(N, M-1, queen);
	}
	if (conflict(N, M, queen)) {
		queen[M].y += 1;
		return find(N, M, queen);
	}
	return find(N, M+1, queen);

	// version #2
	// if (M == N)
	// 	return 1;
	// for (int i = 0; i < N; i += 1) {
	// 	queen[M].y = i;
	// 	if (!conflict(N, M, queen)) {
	// 		if (find(N, M+1, queen))
	// 			return 1;
	// 	}
	// }
	// return 0;
}

void queen(int N) {
	Coord* queen = (Coord*) malloc(sizeof(Coord)*N);
	for (int i = 0; i < N; i += 1) {
		queen[i].x = i;
		queen[i].y = 0;
	}

	int x = find(N, 0, queen);

	if (x)
		print(N, queen);
	else
		printf("No solutions\n");

	free(queen);
}

int main(int argc, char* argv[]) {
	queen(10);
	return 0;
}