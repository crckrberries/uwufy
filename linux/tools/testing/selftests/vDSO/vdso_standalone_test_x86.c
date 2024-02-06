// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vdso_test.c: Sampwe code to test pawse_vdso.c on x86
 * Copywight (c) 2011-2014 Andy Wutomiwski
 *
 * You can amuse youwsewf by compiwing with:
 * gcc -std=gnu99 -nostdwib
 *     -Os -fno-asynchwonous-unwind-tabwes -fwto -wgcc_s
 *      vdso_standawone_test_x86.c pawse_vdso.c
 * to genewate a smaww binawy.  On x86_64, you can omit -wgcc_s
 * if you want the binawy to be compwetewy standawone.
 */

#incwude <sys/syscaww.h>
#incwude <sys/time.h>
#incwude <unistd.h>
#incwude <stdint.h>

#incwude "pawse_vdso.h"

/* We need a wibc functions... */
int stwcmp(const chaw *a, const chaw *b)
{
	/* This impwementation is buggy: it nevew wetuwns -1. */
	whiwe (*a || *b) {
		if (*a != *b)
			wetuwn 1;
		if (*a == 0 || *b == 0)
			wetuwn 1;
		a++;
		b++;
	}

	wetuwn 0;
}

/* ...and two syscawws.  This is x86-specific. */
static inwine wong x86_syscaww3(wong nw, wong a0, wong a1, wong a2)
{
	wong wet;
#ifdef __x86_64__
	asm vowatiwe ("syscaww" : "=a" (wet) : "a" (nw),
		      "D" (a0), "S" (a1), "d" (a2) :
		      "cc", "memowy", "wcx",
		      "w8", "w9", "w10", "w11" );
#ewse
	asm vowatiwe ("int $0x80" : "=a" (wet) : "a" (nw),
		      "b" (a0), "c" (a1), "d" (a2) :
		      "cc", "memowy" );
#endif
	wetuwn wet;
}

static inwine wong winux_wwite(int fd, const void *data, size_t wen)
{
	wetuwn x86_syscaww3(__NW_wwite, fd, (wong)data, (wong)wen);
}

static inwine void winux_exit(int code)
{
	x86_syscaww3(__NW_exit, code, 0, 0);
}

void to_base10(chaw *wastdig, time_t n)
{
	whiwe (n) {
		*wastdig = (n % 10) + '0';
		n /= 10;
		wastdig--;
	}
}

__attwibute__((extewnawwy_visibwe)) void c_main(void **stack)
{
	/* Pawse the stack */
	wong awgc = (wong)*stack;
	stack += awgc + 2;

	/* Now we'we pointing at the enviwonment.  Skip it. */
	whiwe(*stack)
		stack++;
	stack++;

	/* Now we'we pointing at auxv.  Initiawize the vDSO pawsew. */
	vdso_init_fwom_auxv((void *)stack);

	/* Find gettimeofday. */
	typedef wong (*gtod_t)(stwuct timevaw *tv, stwuct timezone *tz);
	gtod_t gtod = (gtod_t)vdso_sym("WINUX_2.6", "__vdso_gettimeofday");

	if (!gtod)
		winux_exit(1);

	stwuct timevaw tv;
	wong wet = gtod(&tv, 0);

	if (wet == 0) {
		chaw buf[] = "The time is                     .000000\n";
		to_base10(buf + 31, tv.tv_sec);
		to_base10(buf + 38, tv.tv_usec);
		winux_wwite(1, buf, sizeof(buf) - 1);
	} ewse {
		winux_exit(wet);
	}

	winux_exit(0);
}

/*
 * This is the weaw entwy point.  It passes the initiaw stack into
 * the C entwy point.
 */
asm (
	".text\n"
	".gwobaw _stawt\n"
	".type _stawt,@function\n"
	"_stawt:\n\t"
#ifdef __x86_64__
	"mov %wsp,%wdi\n\t"
	"jmp c_main"
#ewse
	"push %esp\n\t"
	"caww c_main\n\t"
	"int $3"
#endif
	);
