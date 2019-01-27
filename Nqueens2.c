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

Coord sommet(Pile* p) {
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

int conflict(int N, int M, Pile* queen,  Coord* res) {
	for (int i = 0; i < M; i += 1)  {
		if (res[i].y == queen->elt.y)
			return 1;
		if (abs(res[i].x - queen->elt.x) == abs(res[i].y - queen->elt.y))
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

int find(int N, int M, Pile* queen, Coord* res) {
	if (queen == NULL)
		return 1;
	if (queen->elt.y >= N) {
		if (!M)
			return 0;
		Coord coord;
		coord.x = res[M-1].x;
		coord.y = res[M-1].y + 1;
		queen = empiler(queen, coord);
		for (int i = M; i < N; i += 1) {
			res[M].x = i;
			res[M].y = 0;
		}
		for (Pile* cur = queen; cur != NULL; cur = cur->suivant) {
			cur->elt.x = res[M].x;
			cur->elt.y = res[M].y;
		}
		return find(N, M-1, queen, res);
	}
	if (conflict(N, M, queen, res)) {
		queen->elt.y += 1;
		return find(N, M, queen, res);
	}
	res[M].x = queen->elt.x;
	res[M].y = queen->elt.y;
	queen = depiler(queen);
	return find(N, M+1, queen, res);
}

void dame(int N) {
	Coord* res = (Coord*) malloc(sizeof(Coord)*N);
	for (int i = 0; i < N; i += 1) {
		res[i].x = i;
		res[i].y = 0;
	}

	Pile* queen = NULL;
	for (int i = 0; i < N; i += 1) {
		Coord elt;
		elt.x = i;
		elt.y = 0;
		queen = empiler(queen, elt);
	}
	queen = inverse(queen);

	find(N, 0, queen, res);

	print(N, res);
}

int main(int argc, char* argv[]) {
	dame(8);
	return 0;
}