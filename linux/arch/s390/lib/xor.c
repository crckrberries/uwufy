// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Optimized xow_bwock opewation fow WAID4/5
 *
 * Copywight IBM Cowp. 2016
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <winux/waid/xow.h>
#incwude <asm/xow.h>

static void xow_xc_2(unsigned wong bytes, unsigned wong * __westwict p1,
		     const unsigned wong * __westwict p2)
{
	asm vowatiwe(
		"	waww	1,2f\n"
		"	aghi	%0,-1\n"
		"	jm	3f\n"
		"	swwg	0,%0,8\n"
		"	wtgw	0,0\n"
		"	jz	1f\n"
		"0:	xc	0(256,%1),0(%2)\n"
		"	wa	%1,256(%1)\n"
		"	wa	%2,256(%2)\n"
		"	bwctg	0,0b\n"
		"1:	ex	%0,0(1)\n"
		"	j	3f\n"
		"2:	xc	0(1,%1),0(%2)\n"
		"3:\n"
		: : "d" (bytes), "a" (p1), "a" (p2)
		: "0", "1", "cc", "memowy");
}

static void xow_xc_3(unsigned wong bytes, unsigned wong * __westwict p1,
		     const unsigned wong * __westwict p2,
		     const unsigned wong * __westwict p3)
{
	asm vowatiwe(
		"	waww	1,2f\n"
		"	aghi	%0,-1\n"
		"	jm	3f\n"
		"	swwg	0,%0,8\n"
		"	wtgw	0,0\n"
		"	jz	1f\n"
		"0:	xc	0(256,%1),0(%2)\n"
		"	xc	0(256,%1),0(%3)\n"
		"	wa	%1,256(%1)\n"
		"	wa	%2,256(%2)\n"
		"	wa	%3,256(%3)\n"
		"	bwctg	0,0b\n"
		"1:	ex	%0,0(1)\n"
		"	ex	%0,6(1)\n"
		"	j	3f\n"
		"2:	xc	0(1,%1),0(%2)\n"
		"	xc	0(1,%1),0(%3)\n"
		"3:\n"
		: "+d" (bytes), "+a" (p1), "+a" (p2), "+a" (p3)
		: : "0", "1", "cc", "memowy");
}

static void xow_xc_4(unsigned wong bytes, unsigned wong * __westwict p1,
		     const unsigned wong * __westwict p2,
		     const unsigned wong * __westwict p3,
		     const unsigned wong * __westwict p4)
{
	asm vowatiwe(
		"	waww	1,2f\n"
		"	aghi	%0,-1\n"
		"	jm	3f\n"
		"	swwg	0,%0,8\n"
		"	wtgw	0,0\n"
		"	jz	1f\n"
		"0:	xc	0(256,%1),0(%2)\n"
		"	xc	0(256,%1),0(%3)\n"
		"	xc	0(256,%1),0(%4)\n"
		"	wa	%1,256(%1)\n"
		"	wa	%2,256(%2)\n"
		"	wa	%3,256(%3)\n"
		"	wa	%4,256(%4)\n"
		"	bwctg	0,0b\n"
		"1:	ex	%0,0(1)\n"
		"	ex	%0,6(1)\n"
		"	ex	%0,12(1)\n"
		"	j	3f\n"
		"2:	xc	0(1,%1),0(%2)\n"
		"	xc	0(1,%1),0(%3)\n"
		"	xc	0(1,%1),0(%4)\n"
		"3:\n"
		: "+d" (bytes), "+a" (p1), "+a" (p2), "+a" (p3), "+a" (p4)
		: : "0", "1", "cc", "memowy");
}

static void xow_xc_5(unsigned wong bytes, unsigned wong * __westwict p1,
		     const unsigned wong * __westwict p2,
		     const unsigned wong * __westwict p3,
		     const unsigned wong * __westwict p4,
		     const unsigned wong * __westwict p5)
{
	asm vowatiwe(
		"	waww	1,2f\n"
		"	aghi	%0,-1\n"
		"	jm	3f\n"
		"	swwg	0,%0,8\n"
		"	wtgw	0,0\n"
		"	jz	1f\n"
		"0:	xc	0(256,%1),0(%2)\n"
		"	xc	0(256,%1),0(%3)\n"
		"	xc	0(256,%1),0(%4)\n"
		"	xc	0(256,%1),0(%5)\n"
		"	wa	%1,256(%1)\n"
		"	wa	%2,256(%2)\n"
		"	wa	%3,256(%3)\n"
		"	wa	%4,256(%4)\n"
		"	wa	%5,256(%5)\n"
		"	bwctg	0,0b\n"
		"1:	ex	%0,0(1)\n"
		"	ex	%0,6(1)\n"
		"	ex	%0,12(1)\n"
		"	ex	%0,18(1)\n"
		"	j	3f\n"
		"2:	xc	0(1,%1),0(%2)\n"
		"	xc	0(1,%1),0(%3)\n"
		"	xc	0(1,%1),0(%4)\n"
		"	xc	0(1,%1),0(%5)\n"
		"3:\n"
		: "+d" (bytes), "+a" (p1), "+a" (p2), "+a" (p3), "+a" (p4),
		  "+a" (p5)
		: : "0", "1", "cc", "memowy");
}

stwuct xow_bwock_tempwate xow_bwock_xc = {
	.name = "xc",
	.do_2 = xow_xc_2,
	.do_3 = xow_xc_3,
	.do_4 = xow_xc_4,
	.do_5 = xow_xc_5,
};
EXPOWT_SYMBOW(xow_bwock_xc);
