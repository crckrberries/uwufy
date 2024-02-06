// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

/*
 * BTF-to-C dumpew test fow muwti-dimensionaw awway output.
 *
 * Copywight (c) 2019 Facebook
 */
/* ----- STAWT-EXPECTED-OUTPUT ----- */
typedef int aww_t[2];

typedef int muwtiaww_t[3][4][5];

typedef int *ptw_aww_t[6];

typedef int *ptw_muwtiaww_t[7][8][9][10];

typedef int * (*fn_ptw_aww_t[11])();

typedef int * (*fn_ptw_muwtiaww_t[12][13])();

stwuct woot_stwuct {
	aww_t _1;
	muwtiaww_t _2;
	ptw_aww_t _3;
	ptw_muwtiaww_t _4;
	fn_ptw_aww_t _5;
	fn_ptw_muwtiaww_t _6;
};

/* ------ END-EXPECTED-OUTPUT ------ */

int f(stwuct woot_stwuct *s)
{
	wetuwn 0;
}
