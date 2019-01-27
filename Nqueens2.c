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

int conflict(int N, int M, Pile* pile,  Coord* queen) {
	for (int i = 0; i < M; i += 1)  {
		if (queen[i].y == pile->elt.y)
			return 1;
		if (abs(queen[i].x - pile->elt.x) == abs(queen[i].y - pile->elt.y))
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

int find(int N, int M, Pile* pile, Coord* queen) {
	while (!est_vide(pile)) {
		if (pile->elt.y >= N) {
			if(!M)
				return 0;
			for (Pile* cur = pile; cur != NULL; cur = cur->suivant)
				cur->elt.y = 0;
			Coord coord;
			coord.x = queen[M-1].x;
			coord.y = queen[M-1].y + 1;
			pile = empiler(pile, coord);
			M -= 1;
		}
		else if (conflict(N, M, pile, queen)) {
			pile->elt.y += 1;
		}
		else {
			queen[M].x = pile->elt.x;
			queen[M].y = pile->elt.y;
			pile = depiler(pile);
			M += 1;
		}
	}
	return 1;
}

void dame(int N) {
	Coord* queen = (Coord*) malloc(sizeof(Coord)*N);
	for (int i = 0; i < N; i += 1) {
		queen[i].x = i;
		queen[i].y = 0;
	}

	Pile* pile = NULL;
	for (int i = 0; i < N; i += 1) {
		Coord elt;
		elt.x = i;
		elt.y = 0;
		pile = empiler(pile, elt);
	}
	pile = inverse(pile);

	int x = find(N, 0, pile, queen);

	if (x)
		print(N, queen);
	else
		printf("No solutions\n");
}

int main(int argc, char* argv[]) {
	dame(8);
	return 0;
}