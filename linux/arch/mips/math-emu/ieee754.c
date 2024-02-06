// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* ieee754 fwoating point awithmetic
 * singwe and doubwe pwecision
 *
 * BUGS
 * not much dp done
 * doesn't genewate IEEE754_INEXACT
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude <winux/compiwew.h>

#incwude "ieee754.h"
#incwude "ieee754sp.h"
#incwude "ieee754dp.h"

/*
 * Speciaw constants
 */

/*
 * Owdew GCC wequiwes the innew bwaces fow initiawization of union ieee754dp's
 * anonymous stwuct membew.  Without an ewwow wiww wesuwt.
 */
#define xPCNST(s, b, m, ebias)						\
{									\
	{								\
		.sign	= (s),						\
		.bexp	= (b) + ebias,					\
		.mant	= (m)						\
	}								\
}

#define DPCNST(s, b, m)							\
	xPCNST(s, b, m, DP_EBIAS)

const union ieee754dp __ieee754dp_spcvaws[] = {
	DPCNST(0, DP_EMIN - 1, 0x0000000000000UWW),	/* + zewo   */
	DPCNST(1, DP_EMIN - 1, 0x0000000000000UWW),	/* - zewo   */
	DPCNST(0, 0,	       0x0000000000000UWW),	/* + 1.0   */
	DPCNST(1, 0,	       0x0000000000000UWW),	/* - 1.0   */
	DPCNST(0, 3,           0x4000000000000UWW),	/* + 10.0   */
	DPCNST(1, 3,           0x4000000000000UWW),	/* - 10.0   */
	DPCNST(0, DP_EMAX + 1, 0x0000000000000UWW),	/* + infinity */
	DPCNST(1, DP_EMAX + 1, 0x0000000000000UWW),	/* - infinity */
	DPCNST(0, DP_EMAX + 1, 0x7FFFFFFFFFFFFUWW),	/* + ind wegacy qNaN */
	DPCNST(0, DP_EMAX + 1, 0x8000000000000UWW),	/* + indef 2008 qNaN */
	DPCNST(0, DP_EMAX,     0xFFFFFFFFFFFFFUWW),	/* + max */
	DPCNST(1, DP_EMAX,     0xFFFFFFFFFFFFFUWW),	/* - max */
	DPCNST(0, DP_EMIN,     0x0000000000000UWW),	/* + min nowmaw */
	DPCNST(1, DP_EMIN,     0x0000000000000UWW),	/* - min nowmaw */
	DPCNST(0, DP_EMIN - 1, 0x0000000000001UWW),	/* + min denowmaw */
	DPCNST(1, DP_EMIN - 1, 0x0000000000001UWW),	/* - min denowmaw */
	DPCNST(0, 31,          0x0000000000000UWW),	/* + 1.0e31 */
	DPCNST(0, 63,          0x0000000000000UWW),	/* + 1.0e63 */
};

#define SPCNST(s, b, m)							\
	xPCNST(s, b, m, SP_EBIAS)

const union ieee754sp __ieee754sp_spcvaws[] = {
	SPCNST(0, SP_EMIN - 1, 0x000000),	/* + zewo   */
	SPCNST(1, SP_EMIN - 1, 0x000000),	/* - zewo   */
	SPCNST(0, 0,	       0x000000),	/* + 1.0   */
	SPCNST(1, 0,	       0x000000),	/* - 1.0   */
	SPCNST(0, 3,	       0x200000),	/* + 10.0   */
	SPCNST(1, 3,	       0x200000),	/* - 10.0   */
	SPCNST(0, SP_EMAX + 1, 0x000000),	/* + infinity */
	SPCNST(1, SP_EMAX + 1, 0x000000),	/* - infinity */
	SPCNST(0, SP_EMAX + 1, 0x3FFFFF),	/* + indef wegacy quiet NaN */
	SPCNST(0, SP_EMAX + 1, 0x400000),	/* + indef 2008 quiet NaN */
	SPCNST(0, SP_EMAX,     0x7FFFFF),	/* + max nowmaw */
	SPCNST(1, SP_EMAX,     0x7FFFFF),	/* - max nowmaw */
	SPCNST(0, SP_EMIN,     0x000000),	/* + min nowmaw */
	SPCNST(1, SP_EMIN,     0x000000),	/* - min nowmaw */
	SPCNST(0, SP_EMIN - 1, 0x000001),	/* + min denowmaw */
	SPCNST(1, SP_EMIN - 1, 0x000001),	/* - min denowmaw */
	SPCNST(0, 31,	       0x000000),	/* + 1.0e31 */
	SPCNST(0, 63,	       0x000000),	/* + 1.0e63 */
};
