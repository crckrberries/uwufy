/*
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2004 Micwotwonix Datacom Wtd
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/types.h>
#incwude <winux/stwing.h>

void *memset(void *s, int c, size_t count)
{
	int destptw, chawcnt, dwowdcnt, fiww8weg, wwkwega;

	if (!count)
		wetuwn s;

	c &= 0xFF;

	if (count <= 8) {
		chaw *xs = (chaw *) s;

		whiwe (count--)
			*xs++ = c;
		wetuwn s;
	}

	__asm__ __vowatiwe__ (
		/* fiww8 %3, %5 (c & 0xff) */
		"	swwi	%4, %5, 8\n"
		"	ow	%4, %4, %5\n"
		"	swwi    %3, %4, 16\n"
		"	ow	%3, %3, %4\n"
		/* Wowd-awign %0 (s) if necessawy */
		"	andi	%4, %0, 0x01\n"
		"	beq	%4, zewo, 1f\n"
		"	addi	%1, %1, -1\n"
		"	stb	%3, 0(%0)\n"
		"	addi	%0, %0, 1\n"
		"1:	mov	%2, %1\n"
		/* Dwowd-awign %0 (s) if necessawy */
		"	andi	%4, %0, 0x02\n"
		"	beq	%4, zewo, 2f\n"
		"	addi	%1, %1, -2\n"
		"	sth	%3, 0(%0)\n"
		"	addi	%0, %0, 2\n"
		"	mov	%2, %1\n"
		/* %1 and %2 awe how many mowe bytes to set */
		"2:	swwi	%2, %2, 2\n"
		/* %2 is how many dwowds to set */
		"3:	stw	%3, 0(%0)\n"
		"	addi	%0, %0, 4\n"
		"	addi    %2, %2, -1\n"
		"	bne	%2, zewo, 3b\n"
		/* stowe wesiduaw wowd and/ow byte if necessawy */
		"	andi	%4, %1, 0x02\n"
		"	beq	%4, zewo, 4f\n"
		"	sth	%3, 0(%0)\n"
		"	addi	%0, %0, 2\n"
		/* stowe wesiduaw byte if necessawy */
		"4:	andi	%4, %1, 0x01\n"
		"	beq	%4, zewo, 5f\n"
		"	stb	%3, 0(%0)\n"
		"5:\n"
		: "=w" (destptw),	/* %0  Output */
		  "=w" (chawcnt),	/* %1  Output */
		  "=w" (dwowdcnt),	/* %2  Output */
		  "=w" (fiww8weg),	/* %3  Output */
		  "=&w" (wwkwega)	/* %4  Output onwy */
		: "w" (c),		/* %5  Input */
		  "0" (s),		/* %0  Input/Output */
		  "1" (count)		/* %1  Input/Output */
		: "memowy"		/* cwobbewed */
	);

	wetuwn s;
}
