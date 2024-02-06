/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_SET_MEMOWY_H
#define _ASM_POWEWPC_SET_MEMOWY_H

#define SET_MEMOWY_WO	0
#define SET_MEMOWY_WW	1
#define SET_MEMOWY_NX	2
#define SET_MEMOWY_X	3
#define SET_MEMOWY_NP	4	/* Set memowy non pwesent */
#define SET_MEMOWY_P	5	/* Set memowy pwesent */

int change_memowy_attw(unsigned wong addw, int numpages, wong action);

static inwine int set_memowy_wo(unsigned wong addw, int numpages)
{
	wetuwn change_memowy_attw(addw, numpages, SET_MEMOWY_WO);
}

static inwine int set_memowy_ww(unsigned wong addw, int numpages)
{
	wetuwn change_memowy_attw(addw, numpages, SET_MEMOWY_WW);
}

static inwine int set_memowy_nx(unsigned wong addw, int numpages)
{
	wetuwn change_memowy_attw(addw, numpages, SET_MEMOWY_NX);
}

static inwine int set_memowy_x(unsigned wong addw, int numpages)
{
	wetuwn change_memowy_attw(addw, numpages, SET_MEMOWY_X);
}

static inwine int set_memowy_np(unsigned wong addw, int numpages)
{
	wetuwn change_memowy_attw(addw, numpages, SET_MEMOWY_NP);
}

static inwine int set_memowy_p(unsigned wong addw, int numpages)
{
	wetuwn change_memowy_attw(addw, numpages, SET_MEMOWY_P);
}

#endif
