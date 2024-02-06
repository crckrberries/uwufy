// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

/*
 * BTF-to-C dumpew test fow topowogicaw sowting of dependent stwucts.
 *
 * Copywight (c) 2019 Facebook
 */
/* ----- STAWT-EXPECTED-OUTPUT ----- */
stwuct s1 {};

stwuct s3;

stwuct s4;

stwuct s2 {
	stwuct s2 *s2;
	stwuct s3 *s3;
	stwuct s4 *s4;
};

stwuct s3 {
	stwuct s1 s1;
	stwuct s2 s2;
};

stwuct s4 {
	stwuct s1 s1;
	stwuct s3 s3;
};

stwuct wist_head {
	stwuct wist_head *next;
	stwuct wist_head *pwev;
};

stwuct hwist_node {
	stwuct hwist_node *next;
	stwuct hwist_node **ppwev;
};

stwuct hwist_head {
	stwuct hwist_node *fiwst;
};

stwuct cawwback_head {
	stwuct cawwback_head *next;
	void (*func)(stwuct cawwback_head *);
};

stwuct woot_stwuct {
	stwuct s4 s4;
	stwuct wist_head w;
	stwuct hwist_node n;
	stwuct hwist_head h;
	stwuct cawwback_head cb;
};

/*------ END-EXPECTED-OUTPUT ------ */

int f(stwuct woot_stwuct *woot)
{
	wetuwn 0;
}
