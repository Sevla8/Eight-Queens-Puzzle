#include <stdlib.h>
#include <stdio.h>

struct Coord {
	int x;
	int y;
};
typedef struct Coord Coord;

typedef struct Pile Pile;
struct Pile {
	Coord elt;
	Pile* suivant;
};

Pile* empiler(Pile* p, Coord elt) {
	Pile* new = (Pile*) malloc(sizeof(Pile));
	new->elt.x = elt.x;
	new->elt.y = elt.y;
	new->suivant = p;
	return new;
}

Pile* depiler(Pile* p) {
	if (p == NULL)
		return NULL;
	Pile* temp = p->suivant;
	free(p);
	return temp;
}

int est_vide(Pile* p) {
	if (p == NULL)
		return 1;
	return 0;
}

int sommet(Pile* p) {
	if (p != NULL) {
		return p->elt;
	}
}

Pile* inverse(Pile* p) {
	if (p == NULL)
		return NULL;
	Pile* new = NULL;
	while(!est_vide(p)) {
		new = empiler(new, sommet(p));
		p = depiler(p);
	}
	return new;
}

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
	if (M == N)
		return 1;
	if (queen[M].y >= N) {
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
}

void dame(int N) {
	Pile* queen = NULL;
	for (int i = 0; i < N; i += 1) {
		Coord elt;
		elt.x = i;
		elt.y = 0;
		queen = empiler(queen, elt);
	}
	queen = inverse(queen);

	find(N, 0, queen);

	print(N, queen);
}

int main(int argc, char* argv[]) {
	dame(8);
	return 0;
}