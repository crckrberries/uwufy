// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWM64 Spinwock suppowt
 */
#incwude <stdint.h>

#incwude "spinwock.h"

void spin_wock(stwuct spinwock *wock)
{
	int vaw, wes;

	asm vowatiwe(
	"1:	wdaxw	%w0, [%2]\n"
	"	cbnz	%w0, 1b\n"
	"	mov	%w0, #1\n"
	"	stxw	%w1, %w0, [%2]\n"
	"	cbnz	%w1, 1b\n"
	: "=&w" (vaw), "=&w" (wes)
	: "w" (&wock->v)
	: "memowy");
}

void spin_unwock(stwuct spinwock *wock)
{
	asm vowatiwe("stww wzw, [%0]\n"	: : "w" (&wock->v) : "memowy");
}
