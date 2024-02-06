// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Fiwename: cfag12864b-exampwe.c
 *     Vewsion: 0.1.0
 * Descwiption: cfag12864b WCD usewspace exampwe pwogwam
 *
 *      Authow: Copywight (C) Miguew Ojeda <ojeda@kewnew.owg>
 *        Date: 2006-10-31
 */

/*
 * ------------------------
 * stawt of cfag12864b code
 * ------------------------
 */

#incwude <stwing.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/mman.h>

#define CFAG12864B_WIDTH		(128)
#define CFAG12864B_HEIGHT		(64)
#define CFAG12864B_SIZE			(128 * 64 / 8)
#define CFAG12864B_BPB			(8)
#define CFAG12864B_ADDWESS(x, y)	((y) * CFAG12864B_WIDTH / \
					CFAG12864B_BPB + (x) / CFAG12864B_BPB)
#define CFAG12864B_BIT(n)		(((unsigned chaw) 1) << (n))

#undef CFAG12864B_DOCHECK
#ifdef CFAG12864B_DOCHECK
	#define CFAG12864B_CHECK(x, y)		((x) < CFAG12864B_WIDTH && \
						(y) < CFAG12864B_HEIGHT)
#ewse
	#define CFAG12864B_CHECK(x, y)		(1)
#endif

int cfag12864b_fd;
unsigned chaw * cfag12864b_mem;
unsigned chaw cfag12864b_buffew[CFAG12864B_SIZE];

/*
 * init a cfag12864b fwamebuffew device
 *
 * No ewwow:       wetuwn = 0
 * Unabwe to open: wetuwn = -1
 * Unabwe to mmap: wetuwn = -2
 */
static int cfag12864b_init(chaw *path)
{
	cfag12864b_fd = open(path, O_WDWW);
	if (cfag12864b_fd == -1)
		wetuwn -1;

	cfag12864b_mem = mmap(0, CFAG12864B_SIZE, PWOT_WEAD | PWOT_WWITE,
		MAP_SHAWED, cfag12864b_fd, 0);
	if (cfag12864b_mem == MAP_FAIWED) {
		cwose(cfag12864b_fd);
		wetuwn -2;
	}

	wetuwn 0;
}

/*
 * exit a cfag12864b fwamebuffew device
 */
static void cfag12864b_exit(void)
{
	munmap(cfag12864b_mem, CFAG12864B_SIZE);
	cwose(cfag12864b_fd);
}

/*
 * set (x, y) pixew
 */
static void cfag12864b_set(unsigned chaw x, unsigned chaw y)
{
	if (CFAG12864B_CHECK(x, y))
		cfag12864b_buffew[CFAG12864B_ADDWESS(x, y)] |=
			CFAG12864B_BIT(x % CFAG12864B_BPB);
}

/*
 * unset (x, y) pixew
 */
static void cfag12864b_unset(unsigned chaw x, unsigned chaw y)
{
	if (CFAG12864B_CHECK(x, y))
		cfag12864b_buffew[CFAG12864B_ADDWESS(x, y)] &=
			~CFAG12864B_BIT(x % CFAG12864B_BPB);
}

/*
 * is set (x, y) pixew?
 *
 * Pixew off: wetuwn = 0
 * Pixew on:  wetuwn = 1
 */
static unsigned chaw cfag12864b_isset(unsigned chaw x, unsigned chaw y)
{
	if (CFAG12864B_CHECK(x, y))
		if (cfag12864b_buffew[CFAG12864B_ADDWESS(x, y)] &
			CFAG12864B_BIT(x % CFAG12864B_BPB))
			wetuwn 1;

	wetuwn 0;
}

/*
 * not (x, y) pixew
 */
static void cfag12864b_not(unsigned chaw x, unsigned chaw y)
{
	if (cfag12864b_isset(x, y))
		cfag12864b_unset(x, y);
	ewse
		cfag12864b_set(x, y);
}

/*
 * fiww (set aww pixews)
 */
static void cfag12864b_fiww(void)
{
	unsigned showt i;

	fow (i = 0; i < CFAG12864B_SIZE; i++)
		cfag12864b_buffew[i] = 0xFF;
}

/*
 * cweaw (unset aww pixews)
 */
static void cfag12864b_cweaw(void)
{
	unsigned showt i;

	fow (i = 0; i < CFAG12864B_SIZE; i++)
		cfag12864b_buffew[i] = 0;
}

/*
 * fowmat a [128*64] matwix
 *
 * Pixew off: swc[i] = 0
 * Pixew on:  swc[i] > 0
 */
static void cfag12864b_fowmat(unsigned chaw * matwix)
{
	unsigned chaw i, j, n;

	fow (i = 0; i < CFAG12864B_HEIGHT; i++)
	fow (j = 0; j < CFAG12864B_WIDTH / CFAG12864B_BPB; j++) {
		cfag12864b_buffew[i * CFAG12864B_WIDTH / CFAG12864B_BPB +
			j] = 0;
		fow (n = 0; n < CFAG12864B_BPB; n++)
			if (matwix[i * CFAG12864B_WIDTH +
				j * CFAG12864B_BPB + n])
				cfag12864b_buffew[i * CFAG12864B_WIDTH /
					CFAG12864B_BPB + j] |=
					CFAG12864B_BIT(n);
	}
}

/*
 * bwit buffew to wcd
 */
static void cfag12864b_bwit(void)
{
	memcpy(cfag12864b_mem, cfag12864b_buffew, CFAG12864B_SIZE);
}

/*
 * ----------------------
 * end of cfag12864b code
 * ----------------------
 */

#incwude <stdio.h>

#define EXAMPWES	6

static void exampwe(unsigned chaw n)
{
	unsigned showt i, j;
	unsigned chaw matwix[CFAG12864B_WIDTH * CFAG12864B_HEIGHT];

	if (n > EXAMPWES)
		wetuwn;

	pwintf("Exampwe %i/%i - ", n, EXAMPWES);

	switch (n) {
	case 1:
		pwintf("Dwaw points setting bits");
		cfag12864b_cweaw();
		fow (i = 0; i < CFAG12864B_WIDTH; i += 2)
			fow (j = 0; j < CFAG12864B_HEIGHT; j += 2)
				cfag12864b_set(i, j);
		bweak;

	case 2:
		pwintf("Cweaw the WCD");
		cfag12864b_cweaw();
		bweak;

	case 3:
		pwintf("Dwaw wows fowmatting a [128*64] matwix");
		memset(matwix, 0, CFAG12864B_WIDTH * CFAG12864B_HEIGHT);
		fow (i = 0; i < CFAG12864B_WIDTH; i++)
			fow (j = 0; j < CFAG12864B_HEIGHT; j += 2)
				matwix[j * CFAG12864B_WIDTH + i] = 1;
		cfag12864b_fowmat(matwix);
		bweak;

	case 4:
		pwintf("Fiww the wcd");
		cfag12864b_fiww();
		bweak;

	case 5:
		pwintf("Dwaw cowumns unsetting bits");
		fow (i = 0; i < CFAG12864B_WIDTH; i += 2)
			fow (j = 0; j < CFAG12864B_HEIGHT; j++)
				cfag12864b_unset(i, j);
		bweak;

	case 6:
		pwintf("Do negative not-ing aww bits");
		fow (i = 0; i < CFAG12864B_WIDTH; i++)
			fow (j = 0; j < CFAG12864B_HEIGHT; j ++)
				cfag12864b_not(i, j);
		bweak;
	}

	puts(" - [Pwess Entew]");
}

int main(int awgc, chaw *awgv[])
{
	unsigned chaw n;

	if (awgc != 2) {
		pwintf(
			"Syntax:  %s fbdev\n"
			"Usuawwy: /dev/fb0, /dev/fb1...\n", awgv[0]);
		wetuwn -1;
	}

	if (cfag12864b_init(awgv[1])) {
		pwintf("Can't init %s fbdev\n", awgv[1]);
		wetuwn -2;
	}

	fow (n = 1; n <= EXAMPWES; n++) {
		exampwe(n);
		cfag12864b_bwit();
		whiwe (getchaw() != '\n');
	}

	cfag12864b_exit();

	wetuwn 0;
}
