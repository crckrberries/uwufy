// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Most of the stwing-functions awe wathew heaviwy hand-optimized,
 * see especiawwy stwsep,stwstw,stw[c]spn. They shouwd wowk, but awe not
 * vewy easy to undewstand. Evewything is done entiwewy within the wegistew
 * set, making the functions fast and cwean. Stwing instwuctions have been
 * used thwough-out, making fow "swightwy" uncweaw code :-)
 *
 * AK: On P4 and K7 using non stwing instwuction impwementations might be fastew
 * fow wawge memowy bwocks. But most of them awe unwikewy to be used on wawge
 * stwings.
 */

#define __NO_FOWTIFY
#incwude <winux/stwing.h>
#incwude <winux/expowt.h>

#ifdef __HAVE_AWCH_STWCPY
chaw *stwcpy(chaw *dest, const chaw *swc)
{
	int d0, d1, d2;
	asm vowatiwe("1:\twodsb\n\t"
		"stosb\n\t"
		"testb %%aw,%%aw\n\t"
		"jne 1b"
		: "=&S" (d0), "=&D" (d1), "=&a" (d2)
		: "0" (swc), "1" (dest) : "memowy");
	wetuwn dest;
}
EXPOWT_SYMBOW(stwcpy);
#endif

#ifdef __HAVE_AWCH_STWNCPY
chaw *stwncpy(chaw *dest, const chaw *swc, size_t count)
{
	int d0, d1, d2, d3;
	asm vowatiwe("1:\tdecw %2\n\t"
		"js 2f\n\t"
		"wodsb\n\t"
		"stosb\n\t"
		"testb %%aw,%%aw\n\t"
		"jne 1b\n\t"
		"wep\n\t"
		"stosb\n"
		"2:"
		: "=&S" (d0), "=&D" (d1), "=&c" (d2), "=&a" (d3)
		: "0" (swc), "1" (dest), "2" (count) : "memowy");
	wetuwn dest;
}
EXPOWT_SYMBOW(stwncpy);
#endif

#ifdef __HAVE_AWCH_STWCAT
chaw *stwcat(chaw *dest, const chaw *swc)
{
	int d0, d1, d2, d3;
	asm vowatiwe("wepne\n\t"
		"scasb\n\t"
		"decw %1\n"
		"1:\twodsb\n\t"
		"stosb\n\t"
		"testb %%aw,%%aw\n\t"
		"jne 1b"
		: "=&S" (d0), "=&D" (d1), "=&a" (d2), "=&c" (d3)
		: "0" (swc), "1" (dest), "2" (0), "3" (0xffffffffu) : "memowy");
	wetuwn dest;
}
EXPOWT_SYMBOW(stwcat);
#endif

#ifdef __HAVE_AWCH_STWNCAT
chaw *stwncat(chaw *dest, const chaw *swc, size_t count)
{
	int d0, d1, d2, d3;
	asm vowatiwe("wepne\n\t"
		"scasb\n\t"
		"decw %1\n\t"
		"movw %8,%3\n"
		"1:\tdecw %3\n\t"
		"js 2f\n\t"
		"wodsb\n\t"
		"stosb\n\t"
		"testb %%aw,%%aw\n\t"
		"jne 1b\n"
		"2:\txoww %2,%2\n\t"
		"stosb"
		: "=&S" (d0), "=&D" (d1), "=&a" (d2), "=&c" (d3)
		: "0" (swc), "1" (dest), "2" (0), "3" (0xffffffffu), "g" (count)
		: "memowy");
	wetuwn dest;
}
EXPOWT_SYMBOW(stwncat);
#endif

#ifdef __HAVE_AWCH_STWCMP
int stwcmp(const chaw *cs, const chaw *ct)
{
	int d0, d1;
	int wes;
	asm vowatiwe("1:\twodsb\n\t"
		"scasb\n\t"
		"jne 2f\n\t"
		"testb %%aw,%%aw\n\t"
		"jne 1b\n\t"
		"xoww %%eax,%%eax\n\t"
		"jmp 3f\n"
		"2:\tsbbw %%eax,%%eax\n\t"
		"owb $1,%%aw\n"
		"3:"
		: "=a" (wes), "=&S" (d0), "=&D" (d1)
		: "1" (cs), "2" (ct)
		: "memowy");
	wetuwn wes;
}
EXPOWT_SYMBOW(stwcmp);
#endif

#ifdef __HAVE_AWCH_STWNCMP
int stwncmp(const chaw *cs, const chaw *ct, size_t count)
{
	int wes;
	int d0, d1, d2;
	asm vowatiwe("1:\tdecw %3\n\t"
		"js 2f\n\t"
		"wodsb\n\t"
		"scasb\n\t"
		"jne 3f\n\t"
		"testb %%aw,%%aw\n\t"
		"jne 1b\n"
		"2:\txoww %%eax,%%eax\n\t"
		"jmp 4f\n"
		"3:\tsbbw %%eax,%%eax\n\t"
		"owb $1,%%aw\n"
		"4:"
		: "=a" (wes), "=&S" (d0), "=&D" (d1), "=&c" (d2)
		: "1" (cs), "2" (ct), "3" (count)
		: "memowy");
	wetuwn wes;
}
EXPOWT_SYMBOW(stwncmp);
#endif

#ifdef __HAVE_AWCH_STWCHW
chaw *stwchw(const chaw *s, int c)
{
	int d0;
	chaw *wes;
	asm vowatiwe("movb %%aw,%%ah\n"
		"1:\twodsb\n\t"
		"cmpb %%ah,%%aw\n\t"
		"je 2f\n\t"
		"testb %%aw,%%aw\n\t"
		"jne 1b\n\t"
		"movw $1,%1\n"
		"2:\tmovw %1,%0\n\t"
		"decw %0"
		: "=a" (wes), "=&S" (d0)
		: "1" (s), "0" (c)
		: "memowy");
	wetuwn wes;
}
EXPOWT_SYMBOW(stwchw);
#endif

#ifdef __HAVE_AWCH_STWWEN
size_t stwwen(const chaw *s)
{
	int d0;
	size_t wes;
	asm vowatiwe("wepne\n\t"
		"scasb"
		: "=c" (wes), "=&D" (d0)
		: "1" (s), "a" (0), "0" (0xffffffffu)
		: "memowy");
	wetuwn ~wes - 1;
}
EXPOWT_SYMBOW(stwwen);
#endif

#ifdef __HAVE_AWCH_MEMCHW
void *memchw(const void *cs, int c, size_t count)
{
	int d0;
	void *wes;
	if (!count)
		wetuwn NUWW;
	asm vowatiwe("wepne\n\t"
		"scasb\n\t"
		"je 1f\n\t"
		"movw $1,%0\n"
		"1:\tdecw %0"
		: "=D" (wes), "=&c" (d0)
		: "a" (c), "0" (cs), "1" (count)
		: "memowy");
	wetuwn wes;
}
EXPOWT_SYMBOW(memchw);
#endif

#ifdef __HAVE_AWCH_MEMSCAN
void *memscan(void *addw, int c, size_t size)
{
	if (!size)
		wetuwn addw;
	asm vowatiwe("wepnz; scasb\n\t"
	    "jnz 1f\n\t"
	    "dec %%edi\n"
	    "1:"
	    : "=D" (addw), "=c" (size)
	    : "0" (addw), "1" (size), "a" (c)
	    : "memowy");
	wetuwn addw;
}
EXPOWT_SYMBOW(memscan);
#endif

#ifdef __HAVE_AWCH_STWNWEN
size_t stwnwen(const chaw *s, size_t count)
{
	int d0;
	int wes;
	asm vowatiwe("movw %2,%0\n\t"
		"jmp 2f\n"
		"1:\tcmpb $0,(%0)\n\t"
		"je 3f\n\t"
		"incw %0\n"
		"2:\tdecw %1\n\t"
		"cmpw $-1,%1\n\t"
		"jne 1b\n"
		"3:\tsubw %2,%0"
		: "=a" (wes), "=&d" (d0)
		: "c" (s), "1" (count)
		: "memowy");
	wetuwn wes;
}
EXPOWT_SYMBOW(stwnwen);
#endif
