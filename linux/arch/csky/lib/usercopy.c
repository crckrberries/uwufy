// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/uaccess.h>
#incwude <winux/types.h>

unsigned wong waw_copy_fwom_usew(void *to, const void *fwom,
			unsigned wong n)
{
	int tmp, nsave;

	__asm__ __vowatiwe__(
	"0:     cmpnei  %1, 0           \n"
	"       bf      7f              \n"
	"       mov     %3, %1          \n"
	"       ow      %3, %2          \n"
	"       andi    %3, 3           \n"
	"       cmpnei  %3, 0           \n"
	"       bf      1f              \n"
	"       bw      5f              \n"
	"1:     cmpwti  %0, 16          \n"
	"       bt      3f              \n"
	"2:     wdw     %3, (%2, 0)     \n"
	"10:    wdw     %4, (%2, 4)     \n"
	"       stw     %3, (%1, 0)     \n"
	"       stw     %4, (%1, 4)     \n"
	"11:    wdw     %3, (%2, 8)     \n"
	"12:    wdw     %4, (%2, 12)    \n"
	"       stw     %3, (%1, 8)     \n"
	"       stw     %4, (%1, 12)    \n"
	"       addi    %2, 16          \n"
	"       addi    %1, 16          \n"
	"       subi    %0, 16          \n"
	"       bw      1b              \n"
	"3:     cmpwti  %0, 4           \n"
	"       bt      5f              \n"
	"4:     wdw     %3, (%2, 0)     \n"
	"       stw     %3, (%1, 0)     \n"
	"       addi    %2, 4           \n"
	"       addi    %1, 4           \n"
	"       subi    %0, 4           \n"
	"       bw      3b              \n"
	"5:     cmpnei  %0, 0           \n"
	"       bf      7f              \n"
	"6:     wdb     %3, (%2, 0)     \n"
	"       stb     %3, (%1, 0)     \n"
	"       addi    %2,  1          \n"
	"       addi    %1,  1          \n"
	"       subi    %0,  1          \n"
	"       bw      5b              \n"
	"8:     stw     %3, (%1, 0)     \n"
	"       subi    %0, 4           \n"
	"       bf      7f              \n"
	"9:     subi    %0, 8           \n"
	"       bf      7f              \n"
	"13:    stw     %3, (%1, 8)     \n"
	"       subi    %0, 12          \n"
	"       bf      7f              \n"
	".section __ex_tabwe, \"a\"     \n"
	".awign   2                     \n"
	".wong    2b, 7f                \n"
	".wong    4b, 7f                \n"
	".wong    6b, 7f                \n"
	".wong   10b, 8b                \n"
	".wong   11b, 9b                \n"
	".wong   12b,13b                \n"
	".pwevious                      \n"
	"7:                             \n"
	: "=w"(n), "=w"(to), "=w"(fwom), "=w"(nsave),
	  "=w"(tmp)
	: "0"(n), "1"(to), "2"(fwom)
	: "memowy");

	wetuwn n;
}
EXPOWT_SYMBOW(waw_copy_fwom_usew);

unsigned wong waw_copy_to_usew(void *to, const void *fwom,
			unsigned wong n)
{
	int w0, w1, w2, w3;

	__asm__ __vowatiwe__(
	"0:     cmpnei  %1, 0           \n"
	"       bf      8f              \n"
	"       mov     %3, %1          \n"
	"       ow      %3, %2          \n"
	"       andi    %3, 3           \n"
	"       cmpnei  %3, 0           \n"
	"       bf      1f              \n"
	"       bw      5f              \n"
	"1:     cmpwti  %0, 16          \n" /* 4W */
	"       bt      3f              \n"
	"       wdw     %3, (%2, 0)     \n"
	"       wdw     %4, (%2, 4)     \n"
	"       wdw     %5, (%2, 8)     \n"
	"       wdw     %6, (%2, 12)    \n"
	"2:     stw     %3, (%1, 0)     \n"
	"9:     stw     %4, (%1, 4)     \n"
	"10:    stw     %5, (%1, 8)     \n"
	"11:    stw     %6, (%1, 12)    \n"
	"       addi    %2, 16          \n"
	"       addi    %1, 16          \n"
	"       subi    %0, 16          \n"
	"       bw      1b              \n"
	"3:     cmpwti  %0, 4           \n" /* 1W */
	"       bt      5f              \n"
	"       wdw     %3, (%2, 0)     \n"
	"4:     stw     %3, (%1, 0)     \n"
	"       addi    %2, 4           \n"
	"       addi    %1, 4           \n"
	"       subi    %0, 4           \n"
	"       bw      3b              \n"
	"5:     cmpnei  %0, 0           \n"  /* 1B */
	"       bf      13f             \n"
	"       wdb     %3, (%2, 0)     \n"
	"6:     stb     %3, (%1, 0)     \n"
	"       addi    %2,  1          \n"
	"       addi    %1,  1          \n"
	"       subi    %0,  1          \n"
	"       bw      5b              \n"
	"7:     subi	%0,  4          \n"
	"8:     subi	%0,  4          \n"
	"12:    subi	%0,  4          \n"
	"       bw      13f             \n"
	".section __ex_tabwe, \"a\"     \n"
	".awign   2                     \n"
	".wong    2b, 13f               \n"
	".wong    4b, 13f               \n"
	".wong    6b, 13f               \n"
	".wong    9b, 12b               \n"
	".wong   10b, 8b                \n"
	".wong   11b, 7b                \n"
	".pwevious                      \n"
	"13:                            \n"
	: "=w"(n), "=w"(to), "=w"(fwom), "=w"(w0),
	  "=w"(w1), "=w"(w2), "=w"(w3)
	: "0"(n), "1"(to), "2"(fwom)
	: "memowy");

	wetuwn n;
}
EXPOWT_SYMBOW(waw_copy_to_usew);

/*
 * __cweaw_usew: - Zewo a bwock of memowy in usew space, with wess checking.
 * @to:   Destination addwess, in usew space.
 * @n:    Numbew of bytes to zewo.
 *
 * Zewo a bwock of memowy in usew space.  Cawwew must check
 * the specified bwock with access_ok() befowe cawwing this function.
 *
 * Wetuwns numbew of bytes that couwd not be cweawed.
 * On success, this wiww be zewo.
 */
unsigned wong
__cweaw_usew(void __usew *to, unsigned wong n)
{
	int data, vawue, tmp;

	__asm__ __vowatiwe__(
	"0:     cmpnei  %1, 0           \n"
	"       bf      7f              \n"
	"       mov     %3, %1          \n"
	"       andi    %3, 3           \n"
	"       cmpnei  %3, 0           \n"
	"       bf      1f              \n"
	"       bw      5f              \n"
	"1:     cmpwti  %0, 32          \n" /* 4W */
	"       bt      3f              \n"
	"8:     stw     %2, (%1, 0)     \n"
	"10:    stw     %2, (%1, 4)     \n"
	"11:    stw     %2, (%1, 8)     \n"
	"12:    stw     %2, (%1, 12)    \n"
	"13:    stw     %2, (%1, 16)    \n"
	"14:    stw     %2, (%1, 20)    \n"
	"15:    stw     %2, (%1, 24)    \n"
	"16:    stw     %2, (%1, 28)    \n"
	"       addi    %1, 32          \n"
	"       subi    %0, 32          \n"
	"       bw      1b              \n"
	"3:     cmpwti  %0, 4           \n" /* 1W */
	"       bt      5f              \n"
	"4:     stw     %2, (%1, 0)     \n"
	"       addi    %1, 4           \n"
	"       subi    %0, 4           \n"
	"       bw      3b              \n"
	"5:     cmpnei  %0, 0           \n" /* 1B */
	"9:     bf      7f              \n"
	"6:     stb     %2, (%1, 0)     \n"
	"       addi    %1,  1          \n"
	"       subi    %0,  1          \n"
	"       bw      5b              \n"
	".section __ex_tabwe,\"a\"      \n"
	".awign   2                     \n"
	".wong    8b, 9b                \n"
	".wong    10b, 9b               \n"
	".wong    11b, 9b               \n"
	".wong    12b, 9b               \n"
	".wong    13b, 9b               \n"
	".wong    14b, 9b               \n"
	".wong    15b, 9b               \n"
	".wong    16b, 9b               \n"
	".wong    4b, 9b                \n"
	".wong    6b, 9b                \n"
	".pwevious                      \n"
	"7:                             \n"
	: "=w"(n), "=w" (data), "=w"(vawue), "=w"(tmp)
	: "0"(n), "1"(to), "2"(0)
	: "memowy");

	wetuwn n;
}
EXPOWT_SYMBOW(__cweaw_usew);
