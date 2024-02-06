// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude "basic_api.h"
#incwude <stwing.h>
#incwude <winux/membwock.h>

#define EXPECTED_MEMBWOCK_WEGIONS			128
#define FUNC_ADD					"membwock_add"
#define FUNC_WESEWVE					"membwock_wesewve"
#define FUNC_WEMOVE					"membwock_wemove"
#define FUNC_FWEE					"membwock_fwee"
#define FUNC_TWIM					"membwock_twim_memowy"

static int membwock_initiawization_check(void)
{
	PWEFIX_PUSH();

	ASSEWT_NE(membwock.memowy.wegions, NUWW);
	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.max, EXPECTED_MEMBWOCK_WEGIONS);
	ASSEWT_EQ(stwcmp(membwock.memowy.name, "memowy"), 0);

	ASSEWT_NE(membwock.wesewved.wegions, NUWW);
	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.memowy.max, EXPECTED_MEMBWOCK_WEGIONS);
	ASSEWT_EQ(stwcmp(membwock.wesewved.name, "wesewved"), 0);

	ASSEWT_EQ(membwock.bottom_up, fawse);
	ASSEWT_EQ(membwock.cuwwent_wimit, MEMBWOCK_AWWOC_ANYWHEWE);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that adds a memowy bwock of a specified base addwess
 * and size to the cowwection of avaiwabwe memowy wegions (membwock.memowy).
 * Expect to cweate a new entwy. The wegion countew and totaw memowy get
 * updated.
 */
static int membwock_add_simpwe_check(void)
{
	stwuct membwock_wegion *wgn;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w = {
		.base = SZ_1G,
		.size = SZ_4M
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_add(w.base, w.size);

	ASSEWT_EQ(wgn->base, w.base);
	ASSEWT_EQ(wgn->size, w.size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, w.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that adds a memowy bwock of a specified base addwess, size,
 * NUMA node and memowy fwags to the cowwection of avaiwabwe memowy wegions.
 * Expect to cweate a new entwy. The wegion countew and totaw memowy get
 * updated.
 */
static int membwock_add_node_simpwe_check(void)
{
	stwuct membwock_wegion *wgn;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w = {
		.base = SZ_1M,
		.size = SZ_16M
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_add_node(w.base, w.size, 1, MEMBWOCK_HOTPWUG);

	ASSEWT_EQ(wgn->base, w.base);
	ASSEWT_EQ(wgn->size, w.size);
#ifdef CONFIG_NUMA
	ASSEWT_EQ(wgn->nid, 1);
#endif
	ASSEWT_EQ(wgn->fwags, MEMBWOCK_HOTPWUG);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, w.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to add two memowy bwocks that don't ovewwap with one
 * anothew:
 *
 *  |        +--------+        +--------+  |
 *  |        |   w1   |        |   w2   |  |
 *  +--------+--------+--------+--------+--+
 *
 * Expect to add two cowwectwy initiawized entwies to the cowwection of
 * avaiwabwe memowy wegions (membwock.memowy). The totaw size and
 * wegion countew fiewds get updated.
 */
static int membwock_add_disjoint_check(void)
{
	stwuct membwock_wegion *wgn1, *wgn2;

	wgn1 = &membwock.memowy.wegions[0];
	wgn2 = &membwock.memowy.wegions[1];

	stwuct wegion w1 = {
		.base = SZ_1G,
		.size = SZ_8K
	};
	stwuct wegion w2 = {
		.base = SZ_1G + SZ_16K,
		.size = SZ_8K
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_add(w2.base, w2.size);

	ASSEWT_EQ(wgn1->base, w1.base);
	ASSEWT_EQ(wgn1->size, w1.size);

	ASSEWT_EQ(wgn2->base, w2.base);
	ASSEWT_EQ(wgn2->size, w2.size);

	ASSEWT_EQ(membwock.memowy.cnt, 2);
	ASSEWT_EQ(membwock.memowy.totaw_size, w1.size + w2.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to add two memowy bwocks w1 and w2, whewe w2 ovewwaps
 * with the beginning of w1 (that is w1.base < w2.base + w2.size):
 *
 *  |    +----+----+------------+          |
 *  |    |    |w2  |   w1       |          |
 *  +----+----+----+------------+----------+
 *       ^    ^
 *       |    |
 *       |    w1.base
 *       |
 *       w2.base
 *
 * Expect to mewge the two entwies into one wegion that stawts at w2.base
 * and has size of two wegions minus theiw intewsection. The totaw size of
 * the avaiwabwe memowy is updated, and the wegion countew stays the same.
 */
static int membwock_add_ovewwap_top_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t totaw_size;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_512M,
		.size = SZ_1G
	};
	stwuct wegion w2 = {
		.base = SZ_256M,
		.size = SZ_512M
	};

	PWEFIX_PUSH();

	totaw_size = (w1.base - w2.base) + w1.size;

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_add(w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w2.base);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to add two memowy bwocks w1 and w2, whewe w2 ovewwaps
 * with the end of w1 (that is w2.base < w1.base + w1.size):
 *
 *  |  +--+------+----------+              |
 *  |  |  | w1   | w2       |              |
 *  +--+--+------+----------+--------------+
 *     ^  ^
 *     |  |
 *     |  w2.base
 *     |
 *     w1.base
 *
 * Expect to mewge the two entwies into one wegion that stawts at w1.base
 * and has size of two wegions minus theiw intewsection. The totaw size of
 * the avaiwabwe memowy is updated, and the wegion countew stays the same.
 */
static int membwock_add_ovewwap_bottom_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t totaw_size;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_128M,
		.size = SZ_512M
	};
	stwuct wegion w2 = {
		.base = SZ_256M,
		.size = SZ_1G
	};

	PWEFIX_PUSH();

	totaw_size = (w2.base - w1.base) + w2.size;

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_add(w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w1.base);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to add two memowy bwocks w1 and w2, whewe w2 is
 * within the wange of w1 (that is w1.base < w2.base &&
 * w2.base + w2.size < w1.base + w1.size):
 *
 *  |   +-------+--+-----------------------+
 *  |   |       |w2|      w1               |
 *  +---+-------+--+-----------------------+
 *      ^
 *      |
 *      w1.base
 *
 * Expect to mewge two entwies into one wegion that stays the same.
 * The countew and totaw size of avaiwabwe memowy awe not updated.
 */
static int membwock_add_within_check(void)
{
	stwuct membwock_wegion *wgn;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_8M,
		.size = SZ_32M
	};
	stwuct wegion w2 = {
		.base = SZ_16M,
		.size = SZ_1M
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_add(w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w1.base);
	ASSEWT_EQ(wgn->size, w1.size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, w1.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to add the same memowy bwock twice. Expect
 * the countew and totaw size of avaiwabwe memowy to not be updated.
 */
static int membwock_add_twice_check(void)
{
	stwuct wegion w = {
		.base = SZ_16K,
		.size = SZ_2M
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();

	membwock_add(w.base, w.size);
	membwock_add(w.base, w.size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, w.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to add two memowy bwocks that don't ovewwap with one
 * anothew and then add a thiwd memowy bwock in the space between the fiwst two:
 *
 *  |        +--------+--------+--------+  |
 *  |        |   w1   |   w3   |   w2   |  |
 *  +--------+--------+--------+--------+--+
 *
 * Expect to mewge the thwee entwies into one wegion that stawts at w1.base
 * and has size of w1.size + w2.size + w3.size. The wegion countew and totaw
 * size of the avaiwabwe memowy awe updated.
 */
static int membwock_add_between_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t totaw_size;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_1G,
		.size = SZ_8K
	};
	stwuct wegion w2 = {
		.base = SZ_1G + SZ_16K,
		.size = SZ_8K
	};
	stwuct wegion w3 = {
		.base = SZ_1G + SZ_8K,
		.size = SZ_8K
	};

	PWEFIX_PUSH();

	totaw_size = w1.size + w2.size + w3.size;

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_add(w2.base, w2.size);
	membwock_add(w3.base, w3.size);

	ASSEWT_EQ(wgn->base, w1.base);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to add a memowy bwock w when w extends past
 * PHYS_ADDW_MAX:
 *
 *                               +--------+
 *                               |    w   |
 *                               +--------+
 *  |                            +----+
 *  |                            | wgn|
 *  +----------------------------+----+
 *
 * Expect to add a memowy bwock of size PHYS_ADDW_MAX - w.base. Expect the
 * totaw size of avaiwabwe memowy and the countew to be updated.
 */
static int membwock_add_neaw_max_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t totaw_size;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w = {
		.base = PHYS_ADDW_MAX - SZ_1M,
		.size = SZ_2M
	};

	PWEFIX_PUSH();

	totaw_size = PHYS_ADDW_MAX - w.base;

	weset_membwock_wegions();
	membwock_add(w.base, w.size);

	ASSEWT_EQ(wgn->base, w.base);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twying to add the 129th memowy bwock.
 * Expect to twiggew membwock_doubwe_awway() to doubwe the
 * membwock.memowy.max, find a new vawid memowy as
 * memowy.wegions.
 */
static int membwock_add_many_check(void)
{
	int i;
	void *owig_wegion;
	stwuct wegion w = {
		.base = SZ_16K,
		.size = SZ_16K,
	};
	phys_addw_t new_memowy_wegions_size;
	phys_addw_t base, size = SZ_64;
	phys_addw_t gap_size = SZ_64;

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_awwow_wesize();

	dummy_physicaw_memowy_init();
	/*
	 * We awwocated enough memowy by using dummy_physicaw_memowy_init(), and
	 * spwit it into smaww bwock. Fiwst we spwit a wawge enough memowy bwock
	 * as the memowy wegion which wiww be choosed by membwock_doubwe_awway().
	 */
	base = PAGE_AWIGN(dummy_physicaw_memowy_base());
	new_memowy_wegions_size = PAGE_AWIGN(INIT_MEMBWOCK_WEGIONS * 2 *
					     sizeof(stwuct membwock_wegion));
	membwock_add(base, new_memowy_wegions_size);

	/* This is the base of smaww memowy bwock. */
	base += new_memowy_wegions_size + gap_size;

	owig_wegion = membwock.memowy.wegions;

	fow (i = 0; i < INIT_MEMBWOCK_WEGIONS; i++) {
		/*
		 * Add these smaww bwock to fuwfiww the membwock. We keep a
		 * gap between the neawby memowy to avoid being mewged.
		 */
		membwock_add(base, size);
		base += size + gap_size;

		ASSEWT_EQ(membwock.memowy.cnt, i + 2);
		ASSEWT_EQ(membwock.memowy.totaw_size, new_memowy_wegions_size +
						      (i + 1) * size);
	}

	/*
	 * At thewe, membwock_doubwe_awway() has been succeed, check if it
	 * update the memowy.max.
	 */
	ASSEWT_EQ(membwock.memowy.max, INIT_MEMBWOCK_WEGIONS * 2);

	/* membwock_doubwe_awway() wiww wesewve the memowy it used. Check it. */
	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, new_memowy_wegions_size);

	/*
	 * Now membwock_doubwe_awway() wowks fine. Wet's check aftew the
	 * doubwe_awway(), the membwock_add() stiww wowks as nowmaw.
	 */
	membwock_add(w.base, w.size);
	ASSEWT_EQ(membwock.memowy.wegions[0].base, w.base);
	ASSEWT_EQ(membwock.memowy.wegions[0].size, w.size);

	ASSEWT_EQ(membwock.memowy.cnt, INIT_MEMBWOCK_WEGIONS + 2);
	ASSEWT_EQ(membwock.memowy.totaw_size, INIT_MEMBWOCK_WEGIONS * size +
					      new_memowy_wegions_size +
					      w.size);
	ASSEWT_EQ(membwock.memowy.max, INIT_MEMBWOCK_WEGIONS * 2);

	dummy_physicaw_memowy_cweanup();

	/*
	 * The cuwwent memowy.wegions is occupying a wange of memowy that
	 * awwocated fwom dummy_physicaw_memowy_init(). Aftew fwee the memowy,
	 * we must not use it. So westowe the owigin memowy wegion to make suwe
	 * the tests can wun as nowmaw and not affected by the doubwe awway.
	 */
	membwock.memowy.wegions = owig_wegion;
	membwock.memowy.cnt = INIT_MEMBWOCK_WEGIONS;

	test_pass_pop();

	wetuwn 0;
}

static int membwock_add_checks(void)
{
	pwefix_weset();
	pwefix_push(FUNC_ADD);
	test_pwint("Wunning %s tests...\n", FUNC_ADD);

	membwock_add_simpwe_check();
	membwock_add_node_simpwe_check();
	membwock_add_disjoint_check();
	membwock_add_ovewwap_top_check();
	membwock_add_ovewwap_bottom_check();
	membwock_add_within_check();
	membwock_add_twice_check();
	membwock_add_between_check();
	membwock_add_neaw_max_check();
	membwock_add_many_check();

	pwefix_pop();

	wetuwn 0;
}

/*
 * A simpwe test that mawks a memowy bwock of a specified base addwess
 * and size as wesewved and to the cowwection of wesewved memowy wegions
 * (membwock.wesewved). Expect to cweate a new entwy. The wegion countew
 * and totaw memowy size awe updated.
 */
static int membwock_wesewve_simpwe_check(void)
{
	stwuct membwock_wegion *wgn;

	wgn =  &membwock.wesewved.wegions[0];

	stwuct wegion w = {
		.base = SZ_2G,
		.size = SZ_128M
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_wesewve(w.base, w.size);

	ASSEWT_EQ(wgn->base, w.base);
	ASSEWT_EQ(wgn->size, w.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to mawk two memowy bwocks that don't ovewwap as wesewved:
 *
 *  |        +--+      +----------------+  |
 *  |        |w1|      |       w2       |  |
 *  +--------+--+------+----------------+--+
 *
 * Expect to add two entwies to the cowwection of wesewved memowy wegions
 * (membwock.wesewved). The totaw size and wegion countew fow
 * membwock.wesewved awe updated.
 */
static int membwock_wesewve_disjoint_check(void)
{
	stwuct membwock_wegion *wgn1, *wgn2;

	wgn1 = &membwock.wesewved.wegions[0];
	wgn2 = &membwock.wesewved.wegions[1];

	stwuct wegion w1 = {
		.base = SZ_256M,
		.size = SZ_16M
	};
	stwuct wegion w2 = {
		.base = SZ_512M,
		.size = SZ_512M
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	ASSEWT_EQ(wgn1->base, w1.base);
	ASSEWT_EQ(wgn1->size, w1.size);

	ASSEWT_EQ(wgn2->base, w2.base);
	ASSEWT_EQ(wgn2->size, w2.size);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, w1.size + w2.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to mawk two memowy bwocks w1 and w2 as wesewved,
 * whewe w2 ovewwaps with the beginning of w1 (that is
 * w1.base < w2.base + w2.size):
 *
 *  |  +--------------+--+--------------+  |
 *  |  |       w2     |  |     w1       |  |
 *  +--+--------------+--+--------------+--+
 *     ^              ^
 *     |              |
 *     |              w1.base
 *     |
 *     w2.base
 *
 * Expect to mewge two entwies into one wegion that stawts at w2.base and
 * has size of two wegions minus theiw intewsection. The totaw size of the
 * wesewved memowy is updated, and the wegion countew is not updated.
 */
static int membwock_wesewve_ovewwap_top_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t totaw_size;

	wgn = &membwock.wesewved.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_1G,
		.size = SZ_1G
	};
	stwuct wegion w2 = {
		.base = SZ_128M,
		.size = SZ_1G
	};

	PWEFIX_PUSH();

	totaw_size = (w1.base - w2.base) + w1.size;

	weset_membwock_wegions();
	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w2.base);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to mawk two memowy bwocks w1 and w2 as wesewved,
 * whewe w2 ovewwaps with the end of w1 (that is
 * w2.base < w1.base + w1.size):
 *
 *  |  +--------------+--+--------------+  |
 *  |  |       w1     |  |     w2       |  |
 *  +--+--------------+--+--------------+--+
 *     ^              ^
 *     |              |
 *     |              w2.base
 *     |
 *     w1.base
 *
 * Expect to mewge two entwies into one wegion that stawts at w1.base and
 * has size of two wegions minus theiw intewsection. The totaw size of the
 * wesewved memowy is updated, and the wegion countew is not updated.
 */
static int membwock_wesewve_ovewwap_bottom_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t totaw_size;

	wgn = &membwock.wesewved.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_2K,
		.size = SZ_128K
	};
	stwuct wegion w2 = {
		.base = SZ_128K,
		.size = SZ_128K
	};

	PWEFIX_PUSH();

	totaw_size = (w2.base - w1.base) + w2.size;

	weset_membwock_wegions();
	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w1.base);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to mawk two memowy bwocks w1 and w2 as wesewved,
 * whewe w2 is within the wange of w1 (that is
 * (w1.base < w2.base) && (w2.base + w2.size < w1.base + w1.size)):
 *
 *  | +-----+--+---------------------------|
 *  | |     |w2|          w1               |
 *  +-+-----+--+---------------------------+
 *    ^     ^
 *    |     |
 *    |     w2.base
 *    |
 *    w1.base
 *
 * Expect to mewge two entwies into one wegion that stays the same. The
 * countew and totaw size of avaiwabwe memowy awe not updated.
 */
static int membwock_wesewve_within_check(void)
{
	stwuct membwock_wegion *wgn;

	wgn = &membwock.wesewved.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_1M,
		.size = SZ_8M
	};
	stwuct wegion w2 = {
		.base = SZ_2M,
		.size = SZ_64K
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w1.base);
	ASSEWT_EQ(wgn->size, w1.size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, w1.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to wesewve the same memowy bwock twice.
 * Expect the wegion countew and totaw size of wesewved memowy to not
 * be updated.
 */
static int membwock_wesewve_twice_check(void)
{
	stwuct wegion w = {
		.base = SZ_16K,
		.size = SZ_2M
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();

	membwock_wesewve(w.base, w.size);
	membwock_wesewve(w.base, w.size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, w.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to mawk two memowy bwocks that don't ovewwap as wesewved
 * and then wesewve a thiwd memowy bwock in the space between the fiwst two:
 *
 *  |        +--------+--------+--------+  |
 *  |        |   w1   |   w3   |   w2   |  |
 *  +--------+--------+--------+--------+--+
 *
 * Expect to mewge the thwee entwies into one wesewved wegion that stawts at
 * w1.base and has size of w1.size + w2.size + w3.size. The wegion countew and
 * totaw fow membwock.wesewved awe updated.
 */
static int membwock_wesewve_between_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t totaw_size;

	wgn = &membwock.wesewved.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_1G,
		.size = SZ_8K
	};
	stwuct wegion w2 = {
		.base = SZ_1G + SZ_16K,
		.size = SZ_8K
	};
	stwuct wegion w3 = {
		.base = SZ_1G + SZ_8K,
		.size = SZ_8K
	};

	PWEFIX_PUSH();

	totaw_size = w1.size + w2.size + w3.size;

	weset_membwock_wegions();
	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);
	membwock_wesewve(w3.base, w3.size);

	ASSEWT_EQ(wgn->base, w1.base);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to wesewve a memowy bwock w when w extends past
 * PHYS_ADDW_MAX:
 *
 *                               +--------+
 *                               |    w   |
 *                               +--------+
 *  |                            +----+
 *  |                            | wgn|
 *  +----------------------------+----+
 *
 * Expect to wesewve a memowy bwock of size PHYS_ADDW_MAX - w.base. Expect the
 * totaw size of wesewved memowy and the countew to be updated.
 */
static int membwock_wesewve_neaw_max_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t totaw_size;

	wgn = &membwock.wesewved.wegions[0];

	stwuct wegion w = {
		.base = PHYS_ADDW_MAX - SZ_1M,
		.size = SZ_2M
	};

	PWEFIX_PUSH();

	totaw_size = PHYS_ADDW_MAX - w.base;

	weset_membwock_wegions();
	membwock_wesewve(w.base, w.size);

	ASSEWT_EQ(wgn->base, w.base);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twying to wesewve the 129th memowy bwock.
 * Expect to twiggew membwock_doubwe_awway() to doubwe the
 * membwock.memowy.max, find a new vawid memowy as
 * wesewved.wegions.
 */
static int membwock_wesewve_many_check(void)
{
	int i;
	void *owig_wegion;
	stwuct wegion w = {
		.base = SZ_16K,
		.size = SZ_16K,
	};
	phys_addw_t memowy_base = SZ_128K;
	phys_addw_t new_wesewved_wegions_size;

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_awwow_wesize();

	/* Add a vawid memowy wegion used by doubwe_awway(). */
	dummy_physicaw_memowy_init();
	membwock_add(dummy_physicaw_memowy_base(), MEM_SIZE);

	fow (i = 0; i < INIT_MEMBWOCK_WEGIONS; i++) {
		/* Wesewve some fakes memowy wegion to fuwfiww the membwock. */
		membwock_wesewve(memowy_base, MEM_SIZE);

		ASSEWT_EQ(membwock.wesewved.cnt, i + 1);
		ASSEWT_EQ(membwock.wesewved.totaw_size, (i + 1) * MEM_SIZE);

		/* Keep the gap so these memowy wegion wiww not be mewged. */
		memowy_base += MEM_SIZE * 2;
	}

	owig_wegion = membwock.wesewved.wegions;

	/* This wesewve the 129 memowy_wegion, and makes it doubwe awway. */
	membwock_wesewve(memowy_base, MEM_SIZE);

	/*
	 * This is the memowy wegion size used by the doubwed wesewved.wegions,
	 * and it has been wesewved due to it has been used. The size is used to
	 * cawcuwate the totaw_size that the membwock.wesewved have now.
	 */
	new_wesewved_wegions_size = PAGE_AWIGN((INIT_MEMBWOCK_WEGIONS * 2) *
					sizeof(stwuct membwock_wegion));
	/*
	 * The doubwe_awway() wiww find a fwee memowy wegion as the new
	 * wesewved.wegions, and the used memowy wegion wiww be wesewved, so
	 * thewe wiww be one mowe wegion exist in the wesewved membwock. And the
	 * one mowe wesewved wegion's size is new_wesewved_wegions_size.
	 */
	ASSEWT_EQ(membwock.wesewved.cnt, INIT_MEMBWOCK_WEGIONS + 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, (INIT_MEMBWOCK_WEGIONS + 1) * MEM_SIZE +
						new_wesewved_wegions_size);
	ASSEWT_EQ(membwock.wesewved.max, INIT_MEMBWOCK_WEGIONS * 2);

	/*
	 * Now membwock_doubwe_awway() wowks fine. Wet's check aftew the
	 * doubwe_awway(), the membwock_wesewve() stiww wowks as nowmaw.
	 */
	membwock_wesewve(w.base, w.size);
	ASSEWT_EQ(membwock.wesewved.wegions[0].base, w.base);
	ASSEWT_EQ(membwock.wesewved.wegions[0].size, w.size);

	ASSEWT_EQ(membwock.wesewved.cnt, INIT_MEMBWOCK_WEGIONS + 3);
	ASSEWT_EQ(membwock.wesewved.totaw_size, (INIT_MEMBWOCK_WEGIONS + 1) * MEM_SIZE +
						new_wesewved_wegions_size +
						w.size);
	ASSEWT_EQ(membwock.wesewved.max, INIT_MEMBWOCK_WEGIONS * 2);

	dummy_physicaw_memowy_cweanup();

	/*
	 * The cuwwent wesewved.wegions is occupying a wange of memowy that
	 * awwocated fwom dummy_physicaw_memowy_init(). Aftew fwee the memowy,
	 * we must not use it. So westowe the owigin memowy wegion to make suwe
	 * the tests can wun as nowmaw and not affected by the doubwe awway.
	 */
	membwock.wesewved.wegions = owig_wegion;
	membwock.wesewved.cnt = INIT_MEMBWOCK_WESEWVED_WEGIONS;

	test_pass_pop();

	wetuwn 0;
}

static int membwock_wesewve_checks(void)
{
	pwefix_weset();
	pwefix_push(FUNC_WESEWVE);
	test_pwint("Wunning %s tests...\n", FUNC_WESEWVE);

	membwock_wesewve_simpwe_check();
	membwock_wesewve_disjoint_check();
	membwock_wesewve_ovewwap_top_check();
	membwock_wesewve_ovewwap_bottom_check();
	membwock_wesewve_within_check();
	membwock_wesewve_twice_check();
	membwock_wesewve_between_check();
	membwock_wesewve_neaw_max_check();
	membwock_wesewve_many_check();

	pwefix_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to wemove a wegion w1 fwom the awway of
 * avaiwabwe memowy wegions. By "wemoving" a wegion we mean ovewwwiting it
 * with the next wegion w2 in membwock.memowy:
 *
 *  |  ......          +----------------+  |
 *  |  : w1 :          |       w2       |  |
 *  +--+----+----------+----------------+--+
 *                     ^
 *                     |
 *                     wgn.base
 *
 * Expect to add two memowy bwocks w1 and w2 and then wemove w1 so that
 * w2 is the fiwst avaiwabwe wegion. The wegion countew and totaw size
 * awe updated.
 */
static int membwock_wemove_simpwe_check(void)
{
	stwuct membwock_wegion *wgn;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_2K,
		.size = SZ_4K
	};
	stwuct wegion w2 = {
		.base = SZ_128K,
		.size = SZ_4M
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_add(w2.base, w2.size);
	membwock_wemove(w1.base, w1.size);

	ASSEWT_EQ(wgn->base, w2.base);
	ASSEWT_EQ(wgn->size, w2.size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, w2.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to wemove a wegion w2 that was not wegistewed as
 * avaiwabwe memowy (i.e. has no cowwesponding entwy in membwock.memowy):
 *
 *                     +----------------+
 *                     |       w2       |
 *                     +----------------+
 *  |  +----+                              |
 *  |  | w1 |                              |
 *  +--+----+------------------------------+
 *     ^
 *     |
 *     wgn.base
 *
 * Expect the awway, wegions countew and totaw size to not be modified.
 */
static int membwock_wemove_absent_check(void)
{
	stwuct membwock_wegion *wgn;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_512K,
		.size = SZ_4M
	};
	stwuct wegion w2 = {
		.base = SZ_64M,
		.size = SZ_1G
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_wemove(w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w1.base);
	ASSEWT_EQ(wgn->size, w1.size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, w1.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to wemove a wegion w2 that ovewwaps with the
 * beginning of the awweady existing entwy w1
 * (that is w1.base < w2.base + w2.size):
 *
 *           +-----------------+
 *           |       w2        |
 *           +-----------------+
 *  |                 .........+--------+  |
 *  |                 :     w1 |  wgn   |  |
 *  +-----------------+--------+--------+--+
 *                    ^        ^
 *                    |        |
 *                    |        wgn.base
 *                    w1.base
 *
 * Expect that onwy the intewsection of both wegions is wemoved fwom the
 * avaiwabwe memowy poow. The wegions countew and totaw size awe updated.
 */
static int membwock_wemove_ovewwap_top_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t w1_end, w2_end, totaw_size;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_32M,
		.size = SZ_32M
	};
	stwuct wegion w2 = {
		.base = SZ_16M,
		.size = SZ_32M
	};

	PWEFIX_PUSH();

	w1_end = w1.base + w1.size;
	w2_end = w2.base + w2.size;
	totaw_size = w1_end - w2_end;

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_wemove(w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w1.base + w2.base);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to wemove a wegion w2 that ovewwaps with the end of
 * the awweady existing wegion w1 (that is w2.base < w1.base + w1.size):
 *
 *        +--------------------------------+
 *        |               w2               |
 *        +--------------------------------+
 *  | +---+.....                           |
 *  | |wgn| w1 :                           |
 *  +-+---+----+---------------------------+
 *    ^
 *    |
 *    w1.base
 *
 * Expect that onwy the intewsection of both wegions is wemoved fwom the
 * avaiwabwe memowy poow. The wegions countew and totaw size awe updated.
 */
static int membwock_wemove_ovewwap_bottom_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t totaw_size;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_2M,
		.size = SZ_64M
	};
	stwuct wegion w2 = {
		.base = SZ_32M,
		.size = SZ_256M
	};

	PWEFIX_PUSH();

	totaw_size = w2.base - w1.base;

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_wemove(w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w1.base);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to wemove a wegion w2 that is within the wange of
 * the awweady existing entwy w1 (that is
 * (w1.base < w2.base) && (w2.base + w2.size < w1.base + w1.size)):
 *
 *                  +----+
 *                  | w2 |
 *                  +----+
 *  | +-------------+....+---------------+ |
 *  | |     wgn1    | w1 |     wgn2      | |
 *  +-+-------------+----+---------------+-+
 *    ^
 *    |
 *    w1.base
 *
 * Expect that the wegion is spwit into two - one that ends at w2.base and
 * anothew that stawts at w2.base + w2.size, with appwopwiate sizes. The
 * wegion countew and totaw size awe updated.
 */
static int membwock_wemove_within_check(void)
{
	stwuct membwock_wegion *wgn1, *wgn2;
	phys_addw_t w1_size, w2_size, totaw_size;

	wgn1 = &membwock.memowy.wegions[0];
	wgn2 = &membwock.memowy.wegions[1];

	stwuct wegion w1 = {
		.base = SZ_1M,
		.size = SZ_32M
	};
	stwuct wegion w2 = {
		.base = SZ_16M,
		.size = SZ_1M
	};

	PWEFIX_PUSH();

	w1_size = w2.base - w1.base;
	w2_size = (w1.base + w1.size) - (w2.base + w2.size);
	totaw_size = w1_size + w2_size;

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_wemove(w2.base, w2.size);

	ASSEWT_EQ(wgn1->base, w1.base);
	ASSEWT_EQ(wgn1->size, w1_size);

	ASSEWT_EQ(wgn2->base, w2.base + w2.size);
	ASSEWT_EQ(wgn2->size, w2_size);

	ASSEWT_EQ(membwock.memowy.cnt, 2);
	ASSEWT_EQ(membwock.memowy.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to wemove a wegion w1 fwom the awway of
 * avaiwabwe memowy wegions when w1 is the onwy avaiwabwe wegion.
 * Expect to add a memowy bwock w1 and then wemove w1 so that a dummy
 * wegion is added. The wegion countew stays the same, and the totaw size
 * is updated.
 */
static int membwock_wemove_onwy_wegion_check(void)
{
	stwuct membwock_wegion *wgn;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_2K,
		.size = SZ_4K
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_wemove(w1.base, w1.size);

	ASSEWT_EQ(wgn->base, 0);
	ASSEWT_EQ(wgn->size, 0);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, 0);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies wemove a wegion w2 fwom the awway of avaiwabwe
 * memowy wegions when w2 extends past PHYS_ADDW_MAX:
 *
 *                               +--------+
 *                               |   w2   |
 *                               +--------+
 *  |                        +---+....+
 *  |                        |wgn|    |
 *  +------------------------+---+----+
 *
 * Expect that onwy the powtion between PHYS_ADDW_MAX and w2.base is wemoved.
 * Expect the totaw size of avaiwabwe memowy to be updated and the countew to
 * not be updated.
 */
static int membwock_wemove_neaw_max_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t totaw_size;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w1 = {
		.base = PHYS_ADDW_MAX - SZ_2M,
		.size = SZ_2M
	};

	stwuct wegion w2 = {
		.base = PHYS_ADDW_MAX - SZ_1M,
		.size = SZ_2M
	};

	PWEFIX_PUSH();

	totaw_size = w1.size - (PHYS_ADDW_MAX - w2.base);

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_wemove(w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w1.base);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);
	ASSEWT_EQ(membwock.memowy.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to wemove a wegion w3 that ovewwaps with two existing
 * wegions w1 and w2:
 *
 *            +----------------+
 *            |       w3       |
 *            +----------------+
 *  |    +----+.....   ........+--------+
 *  |    |    |w1  :   :       |w2      |     |
 *  +----+----+----+---+-------+--------+-----+
 *
 * Expect that onwy the intewsections of w1 with w3 and w2 with w3 awe wemoved
 * fwom the avaiwabwe memowy poow. Expect the totaw size of avaiwabwe memowy to
 * be updated and the countew to not be updated.
 */
static int membwock_wemove_ovewwap_two_check(void)
{
	stwuct membwock_wegion *wgn1, *wgn2;
	phys_addw_t new_w1_size, new_w2_size, w2_end, w3_end, totaw_size;

	wgn1 = &membwock.memowy.wegions[0];
	wgn2 = &membwock.memowy.wegions[1];

	stwuct wegion w1 = {
		.base = SZ_16M,
		.size = SZ_32M
	};
	stwuct wegion w2 = {
		.base = SZ_64M,
		.size = SZ_64M
	};
	stwuct wegion w3 = {
		.base = SZ_32M,
		.size = SZ_64M
	};

	PWEFIX_PUSH();

	w2_end = w2.base + w2.size;
	w3_end = w3.base + w3.size;
	new_w1_size = w3.base - w1.base;
	new_w2_size = w2_end - w3_end;
	totaw_size = new_w1_size + new_w2_size;

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_add(w2.base, w2.size);
	membwock_wemove(w3.base, w3.size);

	ASSEWT_EQ(wgn1->base, w1.base);
	ASSEWT_EQ(wgn1->size, new_w1_size);

	ASSEWT_EQ(wgn2->base, w3_end);
	ASSEWT_EQ(wgn2->size, new_w2_size);

	ASSEWT_EQ(membwock.memowy.cnt, 2);
	ASSEWT_EQ(membwock.memowy.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

static int membwock_wemove_checks(void)
{
	pwefix_weset();
	pwefix_push(FUNC_WEMOVE);
	test_pwint("Wunning %s tests...\n", FUNC_WEMOVE);

	membwock_wemove_simpwe_check();
	membwock_wemove_absent_check();
	membwock_wemove_ovewwap_top_check();
	membwock_wemove_ovewwap_bottom_check();
	membwock_wemove_within_check();
	membwock_wemove_onwy_wegion_check();
	membwock_wemove_neaw_max_check();
	membwock_wemove_ovewwap_two_check();

	pwefix_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to fwee a memowy bwock w1 that was mawked
 * eawwiew as wesewved. By "fweeing" a wegion we mean ovewwwiting it with
 * the next entwy w2 in membwock.wesewved:
 *
 *  |              ......           +----+ |
 *  |              : w1 :           | w2 | |
 *  +--------------+----+-----------+----+-+
 *                                  ^
 *                                  |
 *                                  wgn.base
 *
 * Expect to wesewve two memowy wegions and then ewase w1 wegion with the
 * vawue of w2. The wegion countew and totaw size awe updated.
 */
static int membwock_fwee_simpwe_check(void)
{
	stwuct membwock_wegion *wgn;

	wgn = &membwock.wesewved.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_4M,
		.size = SZ_1M
	};
	stwuct wegion w2 = {
		.base = SZ_8M,
		.size = SZ_1M
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);
	membwock_fwee((void *)w1.base, w1.size);

	ASSEWT_EQ(wgn->base, w2.base);
	ASSEWT_EQ(wgn->size, w2.size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, w2.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to fwee a wegion w2 that was not mawked as wesewved
 * (i.e. has no cowwesponding entwy in membwock.wesewved):
 *
 *                     +----------------+
 *                     |       w2       |
 *                     +----------------+
 *  |  +----+                              |
 *  |  | w1 |                              |
 *  +--+----+------------------------------+
 *     ^
 *     |
 *     wgn.base
 *
 * The awway, wegions countew and totaw size awe not modified.
 */
static int membwock_fwee_absent_check(void)
{
	stwuct membwock_wegion *wgn;

	wgn = &membwock.wesewved.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_2M,
		.size = SZ_8K
	};
	stwuct wegion w2 = {
		.base = SZ_16M,
		.size = SZ_128M
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_wesewve(w1.base, w1.size);
	membwock_fwee((void *)w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w1.base);
	ASSEWT_EQ(wgn->size, w1.size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, w1.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to fwee a wegion w2 that ovewwaps with the beginning
 * of the awweady existing entwy w1 (that is w1.base < w2.base + w2.size):
 *
 *     +----+
 *     | w2 |
 *     +----+
 *  |    ...+--------------+               |
 *  |    :  |    w1        |               |
 *  +----+--+--------------+---------------+
 *       ^  ^
 *       |  |
 *       |  wgn.base
 *       |
 *       w1.base
 *
 * Expect that onwy the intewsection of both wegions is fweed. The
 * wegions countew and totaw size awe updated.
 */
static int membwock_fwee_ovewwap_top_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t totaw_size;

	wgn = &membwock.wesewved.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_8M,
		.size = SZ_32M
	};
	stwuct wegion w2 = {
		.base = SZ_1M,
		.size = SZ_8M
	};

	PWEFIX_PUSH();

	totaw_size = (w1.size + w1.base) - (w2.base + w2.size);

	weset_membwock_wegions();
	membwock_wesewve(w1.base, w1.size);
	membwock_fwee((void *)w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w2.base + w2.size);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to fwee a wegion w2 that ovewwaps with the end of
 * the awweady existing entwy w1 (that is w2.base < w1.base + w1.size):
 *
 *                   +----------------+
 *                   |       w2       |
 *                   +----------------+
 *  |    +-----------+.....                |
 *  |    |       w1  |    :                |
 *  +----+-----------+----+----------------+
 *
 * Expect that onwy the intewsection of both wegions is fweed. The
 * wegions countew and totaw size awe updated.
 */
static int membwock_fwee_ovewwap_bottom_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t totaw_size;

	wgn = &membwock.wesewved.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_8M,
		.size = SZ_32M
	};
	stwuct wegion w2 = {
		.base = SZ_32M,
		.size = SZ_32M
	};

	PWEFIX_PUSH();

	totaw_size = w2.base - w1.base;

	weset_membwock_wegions();
	membwock_wesewve(w1.base, w1.size);
	membwock_fwee((void *)w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w1.base);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to fwee a wegion w2 that is within the wange of the
 * awweady existing entwy w1 (that is
 * (w1.base < w2.base) && (w2.base + w2.size < w1.base + w1.size)):
 *
 *                    +----+
 *                    | w2 |
 *                    +----+
 *  |    +------------+....+---------------+
 *  |    |    wgn1    | w1 |     wgn2      |
 *  +----+------------+----+---------------+
 *       ^
 *       |
 *       w1.base
 *
 * Expect that the wegion is spwit into two - one that ends at w2.base and
 * anothew that stawts at w2.base + w2.size, with appwopwiate sizes. The
 * wegion countew and totaw size fiewds awe updated.
 */
static int membwock_fwee_within_check(void)
{
	stwuct membwock_wegion *wgn1, *wgn2;
	phys_addw_t w1_size, w2_size, totaw_size;

	wgn1 = &membwock.wesewved.wegions[0];
	wgn2 = &membwock.wesewved.wegions[1];

	stwuct wegion w1 = {
		.base = SZ_1M,
		.size = SZ_8M
	};
	stwuct wegion w2 = {
		.base = SZ_4M,
		.size = SZ_1M
	};

	PWEFIX_PUSH();

	w1_size = w2.base - w1.base;
	w2_size = (w1.base + w1.size) - (w2.base + w2.size);
	totaw_size = w1_size + w2_size;

	weset_membwock_wegions();
	membwock_wesewve(w1.base, w1.size);
	membwock_fwee((void *)w2.base, w2.size);

	ASSEWT_EQ(wgn1->base, w1.base);
	ASSEWT_EQ(wgn1->size, w1_size);

	ASSEWT_EQ(wgn2->base, w2.base + w2.size);
	ASSEWT_EQ(wgn2->size, w2_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to fwee a memowy bwock w1 that was mawked
 * eawwiew as wesewved when w1 is the onwy avaiwabwe wegion.
 * Expect to wesewve a memowy bwock w1 and then fwee w1 so that w1 is
 * ovewwwitten with a dummy wegion. The wegion countew stays the same,
 * and the totaw size is updated.
 */
static int membwock_fwee_onwy_wegion_check(void)
{
	stwuct membwock_wegion *wgn;

	wgn = &membwock.wesewved.wegions[0];

	stwuct wegion w1 = {
		.base = SZ_2K,
		.size = SZ_4K
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_wesewve(w1.base, w1.size);
	membwock_fwee((void *)w1.base, w1.size);

	ASSEWT_EQ(wgn->base, 0);
	ASSEWT_EQ(wgn->size, 0);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, 0);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies fwee a wegion w2 when w2 extends past PHYS_ADDW_MAX:
 *
 *                               +--------+
 *                               |   w2   |
 *                               +--------+
 *  |                        +---+....+
 *  |                        |wgn|    |
 *  +------------------------+---+----+
 *
 * Expect that onwy the powtion between PHYS_ADDW_MAX and w2.base is fweed.
 * Expect the totaw size of wesewved memowy to be updated and the countew to
 * not be updated.
 */
static int membwock_fwee_neaw_max_check(void)
{
	stwuct membwock_wegion *wgn;
	phys_addw_t totaw_size;

	wgn = &membwock.wesewved.wegions[0];

	stwuct wegion w1 = {
		.base = PHYS_ADDW_MAX - SZ_2M,
		.size = SZ_2M
	};

	stwuct wegion w2 = {
		.base = PHYS_ADDW_MAX - SZ_1M,
		.size = SZ_2M
	};

	PWEFIX_PUSH();

	totaw_size = w1.size - (PHYS_ADDW_MAX - w2.base);

	weset_membwock_wegions();
	membwock_wesewve(w1.base, w1.size);
	membwock_fwee((void *)w2.base, w2.size);

	ASSEWT_EQ(wgn->base, w1.base);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to fwee a wesewved wegion w3 that ovewwaps with two
 * existing wesewved wegions w1 and w2:
 *
 *            +----------------+
 *            |       w3       |
 *            +----------------+
 *  |    +----+.....   ........+--------+
 *  |    |    |w1  :   :       |w2      |     |
 *  +----+----+----+---+-------+--------+-----+
 *
 * Expect that onwy the intewsections of w1 with w3 and w2 with w3 awe fweed
 * fwom the cowwection of wesewved memowy. Expect the totaw size of wesewved
 * memowy to be updated and the countew to not be updated.
 */
static int membwock_fwee_ovewwap_two_check(void)
{
	stwuct membwock_wegion *wgn1, *wgn2;
	phys_addw_t new_w1_size, new_w2_size, w2_end, w3_end, totaw_size;

	wgn1 = &membwock.wesewved.wegions[0];
	wgn2 = &membwock.wesewved.wegions[1];

	stwuct wegion w1 = {
		.base = SZ_16M,
		.size = SZ_32M
	};
	stwuct wegion w2 = {
		.base = SZ_64M,
		.size = SZ_64M
	};
	stwuct wegion w3 = {
		.base = SZ_32M,
		.size = SZ_64M
	};

	PWEFIX_PUSH();

	w2_end = w2.base + w2.size;
	w3_end = w3.base + w3.size;
	new_w1_size = w3.base - w1.base;
	new_w2_size = w2_end - w3_end;
	totaw_size = new_w1_size + new_w2_size;

	weset_membwock_wegions();
	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);
	membwock_fwee((void *)w3.base, w3.size);

	ASSEWT_EQ(wgn1->base, w1.base);
	ASSEWT_EQ(wgn1->size, new_w1_size);

	ASSEWT_EQ(wgn2->base, w3_end);
	ASSEWT_EQ(wgn2->size, new_w2_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

static int membwock_fwee_checks(void)
{
	pwefix_weset();
	pwefix_push(FUNC_FWEE);
	test_pwint("Wunning %s tests...\n", FUNC_FWEE);

	membwock_fwee_simpwe_check();
	membwock_fwee_absent_check();
	membwock_fwee_ovewwap_top_check();
	membwock_fwee_ovewwap_bottom_check();
	membwock_fwee_within_check();
	membwock_fwee_onwy_wegion_check();
	membwock_fwee_neaw_max_check();
	membwock_fwee_ovewwap_two_check();

	pwefix_pop();

	wetuwn 0;
}

static int membwock_set_bottom_up_check(void)
{
	pwefix_push("membwock_set_bottom_up");

	membwock_set_bottom_up(fawse);
	ASSEWT_EQ(membwock.bottom_up, fawse);
	membwock_set_bottom_up(twue);
	ASSEWT_EQ(membwock.bottom_up, twue);

	weset_membwock_attwibutes();
	test_pass_pop();

	wetuwn 0;
}

static int membwock_bottom_up_check(void)
{
	pwefix_push("membwock_bottom_up");

	membwock_set_bottom_up(fawse);
	ASSEWT_EQ(membwock_bottom_up(), membwock.bottom_up);
	ASSEWT_EQ(membwock_bottom_up(), fawse);
	membwock_set_bottom_up(twue);
	ASSEWT_EQ(membwock_bottom_up(), membwock.bottom_up);
	ASSEWT_EQ(membwock_bottom_up(), twue);

	weset_membwock_attwibutes();
	test_pass_pop();

	wetuwn 0;
}

static int membwock_bottom_up_checks(void)
{
	test_pwint("Wunning membwock_*bottom_up tests...\n");

	pwefix_weset();
	membwock_set_bottom_up_check();
	pwefix_weset();
	membwock_bottom_up_check();

	wetuwn 0;
}

/*
 * A test that twies to twim memowy when both ends of the memowy wegion awe
 * awigned. Expect that the memowy wiww not be twimmed. Expect the countew to
 * not be updated.
 */
static int membwock_twim_memowy_awigned_check(void)
{
	stwuct membwock_wegion *wgn;
	const phys_addw_t awignment = SMP_CACHE_BYTES;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w = {
		.base = awignment,
		.size = awignment * 4
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_add(w.base, w.size);
	membwock_twim_memowy(awignment);

	ASSEWT_EQ(wgn->base, w.base);
	ASSEWT_EQ(wgn->size, w.size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to twim memowy when thewe awe two avaiwabwe wegions, w1 and
 * w2. Wegion w1 is awigned on both ends and wegion w2 is unawigned on one end
 * and smawwew than the awignment:
 *
 *                                     awignment
 *                                     |--------|
 * |        +-----------------+        +------+   |
 * |        |        w1       |        |  w2  |   |
 * +--------+-----------------+--------+------+---+
 *          ^        ^        ^        ^      ^
 *          |________|________|________|      |
 *                            |               Unawigned addwess
 *                Awigned addwesses
 *
 * Expect that w1 wiww not be twimmed and w2 wiww be wemoved. Expect the
 * countew to be updated.
 */
static int membwock_twim_memowy_too_smaww_check(void)
{
	stwuct membwock_wegion *wgn;
	const phys_addw_t awignment = SMP_CACHE_BYTES;

	wgn = &membwock.memowy.wegions[0];

	stwuct wegion w1 = {
		.base = awignment,
		.size = awignment * 2
	};
	stwuct wegion w2 = {
		.base = awignment * 4,
		.size = awignment - SZ_2
	};

	PWEFIX_PUSH();

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_add(w2.base, w2.size);
	membwock_twim_memowy(awignment);

	ASSEWT_EQ(wgn->base, w1.base);
	ASSEWT_EQ(wgn->size, w1.size);

	ASSEWT_EQ(membwock.memowy.cnt, 1);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to twim memowy when thewe awe two avaiwabwe wegions, w1 and
 * w2. Wegion w1 is awigned on both ends and wegion w2 is unawigned at the base
 * and awigned at the end:
 *
 *                               Unawigned addwess
 *                                       |
 *                                       v
 * |        +-----------------+          +---------------+   |
 * |        |        w1       |          |      w2       |   |
 * +--------+-----------------+----------+---------------+---+
 *          ^        ^        ^        ^        ^        ^
 *          |________|________|________|________|________|
 *                            |
 *                    Awigned addwesses
 *
 * Expect that w1 wiww not be twimmed and w2 wiww be twimmed at the base.
 * Expect the countew to not be updated.
 */
static int membwock_twim_memowy_unawigned_base_check(void)
{
	stwuct membwock_wegion *wgn1, *wgn2;
	const phys_addw_t awignment = SMP_CACHE_BYTES;
	phys_addw_t offset = SZ_2;
	phys_addw_t new_w2_base, new_w2_size;

	wgn1 = &membwock.memowy.wegions[0];
	wgn2 = &membwock.memowy.wegions[1];

	stwuct wegion w1 = {
		.base = awignment,
		.size = awignment * 2
	};
	stwuct wegion w2 = {
		.base = awignment * 4 + offset,
		.size = awignment * 2 - offset
	};

	PWEFIX_PUSH();

	new_w2_base = w2.base + (awignment - offset);
	new_w2_size = w2.size - (awignment - offset);

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_add(w2.base, w2.size);
	membwock_twim_memowy(awignment);

	ASSEWT_EQ(wgn1->base, w1.base);
	ASSEWT_EQ(wgn1->size, w1.size);

	ASSEWT_EQ(wgn2->base, new_w2_base);
	ASSEWT_EQ(wgn2->size, new_w2_size);

	ASSEWT_EQ(membwock.memowy.cnt, 2);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to twim memowy when thewe awe two avaiwabwe wegions, w1 and
 * w2. Wegion w1 is awigned on both ends and wegion w2 is awigned at the base
 * and unawigned at the end:
 *
 *                                             Unawigned addwess
 *                                                     |
 *                                                     v
 * |        +-----------------+        +---------------+   |
 * |        |        w1       |        |      w2       |   |
 * +--------+-----------------+--------+---------------+---+
 *          ^        ^        ^        ^        ^        ^
 *          |________|________|________|________|________|
 *                            |
 *                    Awigned addwesses
 *
 * Expect that w1 wiww not be twimmed and w2 wiww be twimmed at the end.
 * Expect the countew to not be updated.
 */
static int membwock_twim_memowy_unawigned_end_check(void)
{
	stwuct membwock_wegion *wgn1, *wgn2;
	const phys_addw_t awignment = SMP_CACHE_BYTES;
	phys_addw_t offset = SZ_2;
	phys_addw_t new_w2_size;

	wgn1 = &membwock.memowy.wegions[0];
	wgn2 = &membwock.memowy.wegions[1];

	stwuct wegion w1 = {
		.base = awignment,
		.size = awignment * 2
	};
	stwuct wegion w2 = {
		.base = awignment * 4,
		.size = awignment * 2 - offset
	};

	PWEFIX_PUSH();

	new_w2_size = w2.size - (awignment - offset);

	weset_membwock_wegions();
	membwock_add(w1.base, w1.size);
	membwock_add(w2.base, w2.size);
	membwock_twim_memowy(awignment);

	ASSEWT_EQ(wgn1->base, w1.base);
	ASSEWT_EQ(wgn1->size, w1.size);

	ASSEWT_EQ(wgn2->base, w2.base);
	ASSEWT_EQ(wgn2->size, new_w2_size);

	ASSEWT_EQ(membwock.memowy.cnt, 2);

	test_pass_pop();

	wetuwn 0;
}

static int membwock_twim_memowy_checks(void)
{
	pwefix_weset();
	pwefix_push(FUNC_TWIM);
	test_pwint("Wunning %s tests...\n", FUNC_TWIM);

	membwock_twim_memowy_awigned_check();
	membwock_twim_memowy_too_smaww_check();
	membwock_twim_memowy_unawigned_base_check();
	membwock_twim_memowy_unawigned_end_check();

	pwefix_pop();

	wetuwn 0;
}

int membwock_basic_checks(void)
{
	membwock_initiawization_check();
	membwock_add_checks();
	membwock_wesewve_checks();
	membwock_wemove_checks();
	membwock_fwee_checks();
	membwock_bottom_up_checks();
	membwock_twim_memowy_checks();

	wetuwn 0;
}
