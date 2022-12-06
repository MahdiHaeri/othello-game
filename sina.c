//* Sina Sahabi		40131063
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8
//!
//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define __RESET   "\033[0m"
#define __BLACK   "\033[30m"      /* Black */
#define __RED     "\033[31m"      /* Red */
#define __GREEN   "\033[32m"      /* Green */
#define __YELLOW  "\033[33m"      /* Yellow */
#define __BLUE    "\033[34m"      /* Blue */
#define __MAGENTA "\033[35m"      /* Magenta */
#define __CYAN    "\033[36m"      /* Cyan */
#define __WHITE   "\033[37m"      /* White */
#define __BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define __BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define __BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define __BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define __BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define __BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define __BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define __BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
//!

int rcnt, bcnt, cnt, rem, turn, P, flag;

int chrt [N][N];

int Get (int i, int j, int p, int q) {
	if (i < 0 || N <= i || j < 0 || N <= j) return -10;
	if (chrt[i][j] < 0) return -10;
	if ((chrt[i][j] & 1) == (turn & 1)) return 0;
	return 1 + Get(i + p, j + q, p, q);
}

int ok (int i, int j) {
	if (~chrt[i][j]) return 0;
	for (int p = -1; p < 2; p++) for (int q = -1; q < 2; q++) if (p || q) {
		int k = Get(i + p, j + q, p, q);
		if (k > 0) return 1;
	}
	return 0;
}

void cprt (int i, int j, int pm) {
	if (!~chrt[i][j]) {
		if (pm && ok(i, j)) printf(__BOLDGREEN), printf("*"), printf(__RESET), cnt++;
		else printf("-");
	} else if (chrt[i][j] & 1) printf(__BOLDBLUE), printf("B"), printf(__RESET);
	else printf(__BOLDRED), printf("R"), printf(__RESET);
}

void prt (int pm) {
	printf("Red: %d\tBlue: %d\n", rcnt, bcnt);
	printf("  A B C D E F G H\n");
	for (int i = 0; i < N; i++) {
		printf("%d ", i + 1);
		for (int j = 0; j < N; j++) cprt(i, j, pm), printf(" ");
		printf("\n");
	}
}

void findMoves () { cnt = 0; prt(1); }

void insert (int i, int j) {
	chrt[i][j] = turn & 1; rem--; rcnt += turn & 1 ? 0 : +1; bcnt += turn & 1 ? +1 : 0;
	for (int p = -1; p < 2; p++) for (int q = -1; q < 2; q++) if (p || q) {
		int k = Get(i + p, j + q, p, q);
		if (k > 0) {
			int ii = i, jj = j;
			while (k--) {
				rcnt += turn & 1 ? -1 : +1;
				bcnt += turn & 1 ? +1 : -1;
				ii += p; jj += q;
				chrt[ii][jj]++;
			}
		}
	}
}

void getMove () {
	printf("select a suitable position: ");
	int i, j; char c;
	scanf("%d %c", &i, &c);
	j = c - 'A'; i--;
	if (!ok(i, j)) return getMove();
	insert(i, j);
}

void endGame () {
	printf("\n<--------------------------------------->\n");
	prt(1);
	if (rcnt == bcnt) printf("\nDRAW\n");
	else if (rcnt > bcnt) printf("\n"__BOLDRED"RED WINS!"__RESET"\n");
	else printf("\n"__BOLDBLUE"BLUE WINS!"__RESET"\n");
	exit(0);
}

int safeCnt = 0;
void autoMove () {
	if (safeCnt > 10000) return endGame();
	safeCnt++;
	int i = rand() % N, j = rand() % N;
	if (!ok(i, j)) autoMove();
	else safeCnt = 0, insert(i, j);
}

void gameloop () {
	if (!rem) return endGame();
	printf(turn & 1 ? "\n\nplayer blue moves!\n" : "\n\nplayer red moves!\n");
	findMoves();
	if (!cnt) {
		if (flag) endGame();
		flag = 1; turn++; gameloop();
	} else flag = 0;
	if (turn & 1) {
		if (P > 1) getMove();
		else autoMove();
	} else {
		if (P) getMove();
		else autoMove();
	}
	turn++;
	gameloop();
}

void help () { printf("Read the rules here:\t[https://www.eothello.com/]\npress enter to countinue... "); getchar(); }

void init () {
	srand(time(0));
	rem = 64; cnt = rcnt = bcnt = turn = flag = 0; P = -1;
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) chrt[i][j] = -1;
	insert(3, 3); insert(4, 4); turn++;
	insert(3, 4); insert(4, 3); turn--;
}

void start () {
	help();
	init();
	while (P < 0 || 2 < P) {
		printf("select number of players! (0 or 1 or 2): ");
		scanf("%d", &P);
	}
	gameloop();
}

int main () {
	start();
	return 0;
}
