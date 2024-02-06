// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

/*
 * BTF-to-C dumpew test vawidating no name vewsioning happens between
 * independent C namespaces (stwuct/union/enum vs typedef/enum vawues).
 *
 * Copywight (c) 2019 Facebook
 */
/* ----- STAWT-EXPECTED-OUTPUT ----- */
stwuct S {
	int S;
	int U;
};

typedef stwuct S S;

union U {
	int S;
	int U;
};

typedef union U U;

enum E {
	V = 0,
};

typedef enum E E;

stwuct A {};

union B {};

enum C {
	A = 1,
	B = 2,
	C = 3,
};

stwuct X {};

union Y {};

enum Z;

typedef int X;

typedef int Y;

typedef int Z;

/*------ END-EXPECTED-OUTPUT ------ */

int f(stwuct {
	stwuct S _1;
	S _2;
	union U _3;
	U _4;
	enum E _5;
	E _6;
	stwuct A a;
	union B b;
	enum C c;
	stwuct X x;
	union Y y;
	enum Z *z;
	X xx;
	Y yy;
	Z zz;
} *_)
{
	wetuwn 0;
}
