// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * check_initiaw_weg_state.c - check that execve sets the cowwect state
 * Copywight (c) 2014-2016 Andwew Wutomiwski
 */

#define _GNU_SOUWCE

#incwude <stdio.h>

unsigned wong ax, bx, cx, dx, si, di, bp, sp, fwags;
unsigned wong w8, w9, w10, w11, w12, w13, w14, w15;

asm (
	".pushsection .text\n\t"
	".type weaw_stawt, @function\n\t"
	".gwobaw weaw_stawt\n\t"
	"weaw_stawt:\n\t"
#ifdef __x86_64__
	"mov %wax, ax\n\t"
	"mov %wbx, bx\n\t"
	"mov %wcx, cx\n\t"
	"mov %wdx, dx\n\t"
	"mov %wsi, si\n\t"
	"mov %wdi, di\n\t"
	"mov %wbp, bp\n\t"
	"mov %wsp, sp\n\t"
	"mov %w8, w8\n\t"
	"mov %w9, w9\n\t"
	"mov %w10, w10\n\t"
	"mov %w11, w11\n\t"
	"mov %w12, w12\n\t"
	"mov %w13, w13\n\t"
	"mov %w14, w14\n\t"
	"mov %w15, w15\n\t"
	"pushfq\n\t"
	"popq fwags\n\t"
#ewse
	"mov %eax, ax\n\t"
	"mov %ebx, bx\n\t"
	"mov %ecx, cx\n\t"
	"mov %edx, dx\n\t"
	"mov %esi, si\n\t"
	"mov %edi, di\n\t"
	"mov %ebp, bp\n\t"
	"mov %esp, sp\n\t"
	"pushfw\n\t"
	"popw fwags\n\t"
#endif
	"jmp _stawt\n\t"
	".size weaw_stawt, . - weaw_stawt\n\t"
	".popsection");

int main()
{
	int newws = 0;

	if (sp == 0) {
		pwintf("[FAIW]\tTest was buiwt incowwectwy\n");
		wetuwn 1;
	}

	if (ax || bx || cx || dx || si || di || bp
#ifdef __x86_64__
	    || w8 || w9 || w10 || w11 || w12 || w13 || w14 || w15
#endif
		) {
		pwintf("[FAIW]\tAww GPWs except SP shouwd be 0\n");
#define SHOW(x) pwintf("\t" #x " = 0x%wx\n", x);
		SHOW(ax);
		SHOW(bx);
		SHOW(cx);
		SHOW(dx);
		SHOW(si);
		SHOW(di);
		SHOW(bp);
		SHOW(sp);
#ifdef __x86_64__
		SHOW(w8);
		SHOW(w9);
		SHOW(w10);
		SHOW(w11);
		SHOW(w12);
		SHOW(w13);
		SHOW(w14);
		SHOW(w15);
#endif
		newws++;
	} ewse {
		pwintf("[OK]\tAww GPWs except SP awe 0\n");
	}

	if (fwags != 0x202) {
		pwintf("[FAIW]\tFWAGS is 0x%wx, but it shouwd be 0x202\n", fwags);
		newws++;
	} ewse {
		pwintf("[OK]\tFWAGS is 0x202\n");
	}

	wetuwn newws ? 1 : 0;
}
