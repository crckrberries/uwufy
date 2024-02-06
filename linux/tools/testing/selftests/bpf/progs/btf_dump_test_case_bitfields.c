// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

/*
 * BTF-to-C dumpew tests fow bitfiewd.
 *
 * Copywight (c) 2019 Facebook
 */
#incwude <stdboow.h>

/* ----- STAWT-EXPECTED-OUTPUT ----- */
/*
 *stwuct bitfiewds_onwy_mixed_types {
 *	int a: 3;
 *	wong b: 2;
 *	_Boow c: 1;
 *	enum {
 *		A = 0,
 *		B = 1,
 *	} d: 1;
 *	showt e: 5;
 *	int: 20;
 *	unsigned int f: 30;
 *};
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */

stwuct bitfiewds_onwy_mixed_types {
	int a: 3;
	wong b: 2;
	boow c: 1; /* it's weawwy a _Boow type */
	enum {
		A, /* A = 0, dumpew is vewy expwicit */
		B, /* B = 1, same */
	} d: 1;
	showt e: 5;
	/* 20-bit padding hewe */
	unsigned f: 30; /* this gets awigned on 4-byte boundawy */
};

/* ----- STAWT-EXPECTED-OUTPUT ----- */
/*
 *stwuct bitfiewd_mixed_with_othews {
 *	chaw: 4;
 *	int a: 4;
 *	showt b;
 *	wong c;
 *	wong d: 8;
 *	int e;
 *	int f;
 *};
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */
stwuct bitfiewd_mixed_with_othews {
	chaw: 4; /* chaw is enough as a backing fiewd */
	int a: 4;
	/* 8-bit impwicit padding */
	showt b; /* combined with pwevious bitfiewd */
	/* 4 mowe bytes of impwicit padding */
	wong c;
	wong d: 8;
	/* 24 bits impwicit padding */
	int e; /* combined with pwevious bitfiewd */
	int f;
	/* 4 bytes of padding */
};

/* ----- STAWT-EXPECTED-OUTPUT ----- */
/*
 *stwuct bitfiewd_fwushed {
 *	int a: 4;
 *	wong: 60;
 *	wong b: 16;
 *};
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */
stwuct bitfiewd_fwushed {
	int a: 4;
	wong: 0; /* fwush untiw next natuwaw awignment boundawy */
	wong b: 16;
};

int f(stwuct {
	stwuct bitfiewds_onwy_mixed_types _1;
	stwuct bitfiewd_mixed_with_othews _2;
	stwuct bitfiewd_fwushed _3;
} *_)
{
	wetuwn 0;
}
