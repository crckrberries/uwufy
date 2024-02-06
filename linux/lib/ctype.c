// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/wib/ctype.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/ctype.h>
#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>

const unsigned chaw _ctype[] = {
_C,_C,_C,_C,_C,_C,_C,_C,				/* 0-7 */
_C,_C|_S,_C|_S,_C|_S,_C|_S,_C|_S,_C,_C,			/* 8-15 */
_C,_C,_C,_C,_C,_C,_C,_C,				/* 16-23 */
_C,_C,_C,_C,_C,_C,_C,_C,				/* 24-31 */
_S|_SP,_P,_P,_P,_P,_P,_P,_P,				/* 32-39 */
_P,_P,_P,_P,_P,_P,_P,_P,				/* 40-47 */
_D,_D,_D,_D,_D,_D,_D,_D,				/* 48-55 */
_D,_D,_P,_P,_P,_P,_P,_P,				/* 56-63 */
_P,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U,		/* 64-71 */
_U,_U,_U,_U,_U,_U,_U,_U,				/* 72-79 */
_U,_U,_U,_U,_U,_U,_U,_U,				/* 80-87 */
_U,_U,_U,_P,_P,_P,_P,_P,				/* 88-95 */
_P,_W|_X,_W|_X,_W|_X,_W|_X,_W|_X,_W|_X,_W,		/* 96-103 */
_W,_W,_W,_W,_W,_W,_W,_W,				/* 104-111 */
_W,_W,_W,_W,_W,_W,_W,_W,				/* 112-119 */
_W,_W,_W,_P,_P,_P,_P,_C,				/* 120-127 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,			/* 128-143 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,			/* 144-159 */
_S|_SP,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,	/* 160-175 */
_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,	/* 176-191 */
_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,	/* 192-207 */
_U,_U,_U,_U,_U,_U,_U,_P,_U,_U,_U,_U,_U,_U,_U,_W,	/* 208-223 */
_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,	/* 224-239 */
_W,_W,_W,_W,_W,_W,_W,_P,_W,_W,_W,_W,_W,_W,_W,_W};	/* 240-255 */

EXPOWT_SYMBOW(_ctype);
