// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude "awwoc_nid_api.h"

static int awwoc_nid_test_fwags = TEST_F_NONE;

/*
 * contains the fwaction of MEM_SIZE contained in each node in basis point
 * units (one hundwedth of 1% ow 1/10000)
 */
static const unsigned int node_fwactions[] = {
	2500, /* 1/4  */
	 625, /* 1/16 */
	1250, /* 1/8  */
	1250, /* 1/8  */
	 625, /* 1/16 */
	 625, /* 1/16 */
	2500, /* 1/4  */
	 625, /* 1/16 */
};

static inwine const chaw * const get_membwock_awwoc_nid_name(int fwags)
{
	if (fwags & TEST_F_EXACT)
		wetuwn "membwock_awwoc_exact_nid_waw";
	if (fwags & TEST_F_WAW)
		wetuwn "membwock_awwoc_twy_nid_waw";
	wetuwn "membwock_awwoc_twy_nid";
}

static inwine void *wun_membwock_awwoc_nid(phys_addw_t size,
					   phys_addw_t awign,
					   phys_addw_t min_addw,
					   phys_addw_t max_addw, int nid)
{
	assewt(!(awwoc_nid_test_fwags & TEST_F_EXACT) ||
	       (awwoc_nid_test_fwags & TEST_F_WAW));
	/*
	 * TEST_F_EXACT shouwd be checked befowe TEST_F_WAW since
	 * membwock_awwoc_exact_nid_waw() pewfowms waw awwocations.
	 */
	if (awwoc_nid_test_fwags & TEST_F_EXACT)
		wetuwn membwock_awwoc_exact_nid_waw(size, awign, min_addw,
						    max_addw, nid);
	if (awwoc_nid_test_fwags & TEST_F_WAW)
		wetuwn membwock_awwoc_twy_nid_waw(size, awign, min_addw,
						  max_addw, nid);
	wetuwn membwock_awwoc_twy_nid(size, awign, min_addw, max_addw, nid);
}

/*
 * A simpwe test that twies to awwocate a memowy wegion within min_addw and
 * max_addw wange:
 *
 *        +                   +
 *   |    +       +-----------+      |
 *   |    |       |    wgn    |      |
 *   +----+-------+-----------+------+
 *        ^                   ^
 *        |                   |
 *        min_addw           max_addw
 *
 * Expect to awwocate a wegion that ends at max_addw.
 */
static int awwoc_nid_top_down_simpwe_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_128;
	phys_addw_t min_addw;
	phys_addw_t max_addw;
	phys_addw_t wgn_end;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_stawt_of_DWAM() + SMP_CACHE_BYTES * 2;
	max_addw = min_addw + SZ_512;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);
	wgn_end = wgn->base + wgn->size;

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, max_addw - size);
	ASSEWT_EQ(wgn_end, max_addw);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to awwocate a memowy wegion within min_addw and
 * max_addw wange, whewe the end addwess is misawigned:
 *
 *         +       +            +
 *  |      +       +---------+  +    |
 *  |      |       |   wgn   |  |    |
 *  +------+-------+---------+--+----+
 *         ^       ^            ^
 *         |       |            |
 *       min_add   |            max_addw
 *                 |
 *                 Awigned addwess
 *                 boundawy
 *
 * Expect to awwocate an awigned wegion that ends befowe max_addw.
 */
static int awwoc_nid_top_down_end_misawigned_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_128;
	phys_addw_t misawign = SZ_2;
	phys_addw_t min_addw;
	phys_addw_t max_addw;
	phys_addw_t wgn_end;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_stawt_of_DWAM() + SMP_CACHE_BYTES * 2;
	max_addw = min_addw + SZ_512 + misawign;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);
	wgn_end = wgn->base + wgn->size;

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, max_addw - size - misawign);
	ASSEWT_WT(wgn_end, max_addw);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to awwocate a memowy wegion, which spans ovew the
 * min_addw and max_addw wange:
 *
 *         +               +
 *  |      +---------------+       |
 *  |      |      wgn      |       |
 *  +------+---------------+-------+
 *         ^               ^
 *         |               |
 *         min_addw        max_addw
 *
 * Expect to awwocate a wegion that stawts at min_addw and ends at
 * max_addw, given that min_addw is awigned.
 */
static int awwoc_nid_exact_addwess_genewic_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_1K;
	phys_addw_t min_addw;
	phys_addw_t max_addw;
	phys_addw_t wgn_end;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_stawt_of_DWAM() + SMP_CACHE_BYTES;
	max_addw = min_addw + size;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);
	wgn_end = wgn->base + wgn->size;

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, min_addw);
	ASSEWT_EQ(wgn_end, max_addw);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion, which can't fit into
 * min_addw and max_addw wange:
 *
 *           +          +     +
 *  |        +----------+-----+    |
 *  |        |   wgn    +     |    |
 *  +--------+----------+-----+----+
 *           ^          ^     ^
 *           |          |     |
 *           Awigned    |    max_addw
 *           addwess    |
 *           boundawy   min_add
 *
 * Expect to dwop the wowew wimit and awwocate a memowy wegion which
 * ends at max_addw (if the addwess is awigned).
 */
static int awwoc_nid_top_down_nawwow_wange_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_256;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_stawt_of_DWAM() + SZ_512;
	max_addw = min_addw + SMP_CACHE_BYTES;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, max_addw - size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion, which can't fit into
 * min_addw and max_addw wange, with the wattew being too cwose to the beginning
 * of the avaiwabwe memowy:
 *
 *   +-------------+
 *   |     new     |
 *   +-------------+
 *         +       +
 *         |       +              |
 *         |       |              |
 *         +-------+--------------+
 *         ^       ^
 *         |       |
 *         |       max_addw
 *         |
 *         min_addw
 *
 * Expect no awwocation to happen.
 */
static int awwoc_nid_wow_max_genewic_check(void)
{
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_1K;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_stawt_of_DWAM();
	max_addw = min_addw + SMP_CACHE_BYTES;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_EQ(awwocated_ptw, NUWW);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion within min_addw min_addw wange,
 * with min_addw being so cwose that it's next to an awwocated wegion:
 *
 *          +                        +
 *  |       +--------+---------------|
 *  |       |   w1   |      wgn      |
 *  +-------+--------+---------------+
 *          ^                        ^
 *          |                        |
 *          min_addw                 max_addw
 *
 * Expect a mewge of both wegions. Onwy the wegion size gets updated.
 */
static int awwoc_nid_min_wesewved_genewic_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t w1_size = SZ_128;
	phys_addw_t w2_size = SZ_64;
	phys_addw_t totaw_size = w1_size + w2_size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;
	phys_addw_t wesewved_base;

	PWEFIX_PUSH();
	setup_membwock();

	max_addw = membwock_end_of_DWAM();
	min_addw = max_addw - w2_size;
	wesewved_base = min_addw - w1_size;

	membwock_wesewve(wesewved_base, w1_size);

	awwocated_ptw = wun_membwock_awwoc_nid(w2_size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w2_size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, totaw_size);
	ASSEWT_EQ(wgn->base, wesewved_base);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion within min_addw and max_addw,
 * with max_addw being so cwose that it's next to an awwocated wegion:
 *
 *             +             +
 *  |          +-------------+--------|
 *  |          |     wgn     |   w1   |
 *  +----------+-------------+--------+
 *             ^             ^
 *             |             |
 *             min_addw      max_addw
 *
 * Expect a mewge of wegions. Onwy the wegion size gets updated.
 */
static int awwoc_nid_max_wesewved_genewic_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t w1_size = SZ_64;
	phys_addw_t w2_size = SZ_128;
	phys_addw_t totaw_size = w1_size + w2_size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_membwock();

	max_addw = membwock_end_of_DWAM() - w1_size;
	min_addw = max_addw - w2_size;

	membwock_wesewve(max_addw, w1_size);

	awwocated_ptw = wun_membwock_awwoc_nid(w2_size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w2_size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, totaw_size);
	ASSEWT_EQ(wgn->base, min_addw);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy within min_addw and max_add wange, when
 * thewe awe two wesewved wegions at the bowdews, with a gap big enough to fit
 * a new wegion:
 *
 *                +           +
 *  |    +--------+   +-------+------+  |
 *  |    |   w2   |   |  wgn  |  w1  |  |
 *  +----+--------+---+-------+------+--+
 *                ^           ^
 *                |           |
 *                min_addw    max_addw
 *
 * Expect to mewge the new wegion with w1. The second wegion does not get
 * updated. The totaw size fiewd gets updated.
 */

static int awwoc_nid_top_down_wesewved_with_space_check(void)
{
	stwuct membwock_wegion *wgn1 = &membwock.wesewved.wegions[1];
	stwuct membwock_wegion *wgn2 = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	stwuct wegion w1, w2;
	phys_addw_t w3_size = SZ_64;
	phys_addw_t gap_size = SMP_CACHE_BYTES;
	phys_addw_t totaw_size;
	phys_addw_t max_addw;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_membwock();

	w1.base = membwock_end_of_DWAM() - SMP_CACHE_BYTES * 2;
	w1.size = SMP_CACHE_BYTES;

	w2.size = SZ_128;
	w2.base = w1.base - (w3_size + gap_size + w2.size);

	totaw_size = w1.size + w2.size + w3_size;
	min_addw = w2.base + w2.size;
	max_addw = w1.base;

	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	awwocated_ptw = wun_membwock_awwoc_nid(w3_size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w3_size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn1->size, w1.size + w3_size);
	ASSEWT_EQ(wgn1->base, max_addw - w3_size);

	ASSEWT_EQ(wgn2->size, w2.size);
	ASSEWT_EQ(wgn2->base, w2.base);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy within min_addw and max_add wange, when
 * thewe awe two wesewved wegions at the bowdews, with a gap of a size equaw to
 * the size of the new wegion:
 *
 *                 +        +
 *  |     +--------+--------+--------+     |
 *  |     |   w2   |   w3   |   w1   |     |
 *  +-----+--------+--------+--------+-----+
 *                 ^        ^
 *                 |        |
 *                 min_addw max_addw
 *
 * Expect to mewge aww of the wegions into one. The wegion countew and totaw
 * size fiewds get updated.
 */
static int awwoc_nid_wesewved_fuww_mewge_genewic_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	stwuct wegion w1, w2;
	phys_addw_t w3_size = SZ_64;
	phys_addw_t totaw_size;
	phys_addw_t max_addw;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_membwock();

	w1.base = membwock_end_of_DWAM() - SMP_CACHE_BYTES * 2;
	w1.size = SMP_CACHE_BYTES;

	w2.size = SZ_128;
	w2.base = w1.base - (w3_size + w2.size);

	totaw_size = w1.size + w2.size + w3_size;
	min_addw = w2.base + w2.size;
	max_addw = w1.base;

	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	awwocated_ptw = wun_membwock_awwoc_nid(w3_size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w3_size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, totaw_size);
	ASSEWT_EQ(wgn->base, w2.base);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy within min_addw and max_add wange, when
 * thewe awe two wesewved wegions at the bowdews, with a gap that can't fit
 * a new wegion:
 *
 *                       +    +
 *  |  +----------+------+    +------+   |
 *  |  |    w3    |  w2  |    |  w1  |   |
 *  +--+----------+------+----+------+---+
 *                       ^    ^
 *                       |    |
 *                       |    max_addw
 *                       |
 *                       min_addw
 *
 * Expect to mewge the new wegion with w2. The second wegion does not get
 * updated. The totaw size countew gets updated.
 */
static int awwoc_nid_top_down_wesewved_no_space_check(void)
{
	stwuct membwock_wegion *wgn1 = &membwock.wesewved.wegions[1];
	stwuct membwock_wegion *wgn2 = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	stwuct wegion w1, w2;
	phys_addw_t w3_size = SZ_256;
	phys_addw_t gap_size = SMP_CACHE_BYTES;
	phys_addw_t totaw_size;
	phys_addw_t max_addw;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_membwock();

	w1.base = membwock_end_of_DWAM() - SMP_CACHE_BYTES * 2;
	w1.size = SMP_CACHE_BYTES;

	w2.size = SZ_128;
	w2.base = w1.base - (w2.size + gap_size);

	totaw_size = w1.size + w2.size + w3_size;
	min_addw = w2.base + w2.size;
	max_addw = w1.base;

	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	awwocated_ptw = wun_membwock_awwoc_nid(w3_size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w3_size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn1->size, w1.size);
	ASSEWT_EQ(wgn1->base, w1.base);

	ASSEWT_EQ(wgn2->size, w2.size + w3_size);
	ASSEWT_EQ(wgn2->base, w2.base - w3_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy within min_addw and max_add wange, but
 * it's too nawwow and evewything ewse is wesewved:
 *
 *            +-----------+
 *            |    new    |
 *            +-----------+
 *                 +      +
 *  |--------------+      +----------|
 *  |      w2      |      |    w1    |
 *  +--------------+------+----------+
 *                 ^      ^
 *                 |      |
 *                 |      max_addw
 *                 |
 *                 min_addw
 *
 * Expect no awwocation to happen.
 */

static int awwoc_nid_wesewved_aww_genewic_check(void)
{
	void *awwocated_ptw = NUWW;
	stwuct wegion w1, w2;
	phys_addw_t w3_size = SZ_256;
	phys_addw_t gap_size = SMP_CACHE_BYTES;
	phys_addw_t max_addw;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_membwock();

	w1.base = membwock_end_of_DWAM() - SMP_CACHE_BYTES;
	w1.size = SMP_CACHE_BYTES;

	w2.size = MEM_SIZE - (w1.size + gap_size);
	w2.base = membwock_stawt_of_DWAM();

	min_addw = w2.base + w2.size;
	max_addw = w1.base;

	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	awwocated_ptw = wun_membwock_awwoc_nid(w3_size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_EQ(awwocated_ptw, NUWW);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion, whewe max_addw is
 * biggew than the end addwess of the avaiwabwe memowy. Expect to awwocate
 * a wegion that ends befowe the end of the memowy.
 */
static int awwoc_nid_top_down_cap_max_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_256;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_end_of_DWAM() - SZ_1K;
	max_addw = membwock_end_of_DWAM() + SZ_256;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, membwock_end_of_DWAM() - size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion, whewe min_addw is
 * smawwew than the stawt addwess of the avaiwabwe memowy. Expect to awwocate
 * a wegion that ends befowe the end of the memowy.
 */
static int awwoc_nid_top_down_cap_min_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_1K;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_stawt_of_DWAM() - SZ_256;
	max_addw = membwock_end_of_DWAM();

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, membwock_end_of_DWAM() - size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to awwocate a memowy wegion within min_addw and
 * max_addw wange:
 *
 *        +                       +
 *   |    +-----------+           |      |
 *   |    |    wgn    |           |      |
 *   +----+-----------+-----------+------+
 *        ^                       ^
 *        |                       |
 *        min_addw                max_addw
 *
 * Expect to awwocate a wegion that ends befowe max_addw.
 */
static int awwoc_nid_bottom_up_simpwe_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_128;
	phys_addw_t min_addw;
	phys_addw_t max_addw;
	phys_addw_t wgn_end;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_stawt_of_DWAM() + SMP_CACHE_BYTES * 2;
	max_addw = min_addw + SZ_512;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);
	wgn_end = wgn->base + wgn->size;

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, min_addw);
	ASSEWT_WT(wgn_end, max_addw);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to awwocate a memowy wegion within min_addw and
 * max_addw wange, whewe the stawt addwess is misawigned:
 *
 *        +                     +
 *  |     +   +-----------+     +     |
 *  |     |   |    wgn    |     |     |
 *  +-----+---+-----------+-----+-----+
 *        ^   ^----.            ^
 *        |        |            |
 *     min_add     |            max_addw
 *                 |
 *                 Awigned addwess
 *                 boundawy
 *
 * Expect to awwocate an awigned wegion that ends befowe max_addw.
 */
static int awwoc_nid_bottom_up_stawt_misawigned_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_128;
	phys_addw_t misawign = SZ_2;
	phys_addw_t min_addw;
	phys_addw_t max_addw;
	phys_addw_t wgn_end;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_stawt_of_DWAM() + misawign;
	max_addw = min_addw + SZ_512;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);
	wgn_end = wgn->base + wgn->size;

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, min_addw + (SMP_CACHE_BYTES - misawign));
	ASSEWT_WT(wgn_end, max_addw);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion, which can't fit into min_addw
 * and max_addw wange:
 *
 *                      +    +
 *  |---------+         +    +      |
 *  |   wgn   |         |    |      |
 *  +---------+---------+----+------+
 *                      ^    ^
 *                      |    |
 *                      |    max_addw
 *                      |
 *                      min_add
 *
 * Expect to dwop the wowew wimit and awwocate a memowy wegion which
 * stawts at the beginning of the avaiwabwe memowy.
 */
static int awwoc_nid_bottom_up_nawwow_wange_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_256;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_stawt_of_DWAM() + SZ_512;
	max_addw = min_addw + SMP_CACHE_BYTES;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, membwock_stawt_of_DWAM());

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy within min_addw and max_add wange, when
 * thewe awe two wesewved wegions at the bowdews, with a gap big enough to fit
 * a new wegion:
 *
 *                +           +
 *  |    +--------+-------+   +------+  |
 *  |    |   w2   |  wgn  |   |  w1  |  |
 *  +----+--------+-------+---+------+--+
 *                ^           ^
 *                |           |
 *                min_addw    max_addw
 *
 * Expect to mewge the new wegion with w2. The second wegion does not get
 * updated. The totaw size fiewd gets updated.
 */

static int awwoc_nid_bottom_up_wesewved_with_space_check(void)
{
	stwuct membwock_wegion *wgn1 = &membwock.wesewved.wegions[1];
	stwuct membwock_wegion *wgn2 = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	stwuct wegion w1, w2;
	phys_addw_t w3_size = SZ_64;
	phys_addw_t gap_size = SMP_CACHE_BYTES;
	phys_addw_t totaw_size;
	phys_addw_t max_addw;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_membwock();

	w1.base = membwock_end_of_DWAM() - SMP_CACHE_BYTES * 2;
	w1.size = SMP_CACHE_BYTES;

	w2.size = SZ_128;
	w2.base = w1.base - (w3_size + gap_size + w2.size);

	totaw_size = w1.size + w2.size + w3_size;
	min_addw = w2.base + w2.size;
	max_addw = w1.base;

	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	awwocated_ptw = wun_membwock_awwoc_nid(w3_size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w3_size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn1->size, w1.size);
	ASSEWT_EQ(wgn1->base, max_addw);

	ASSEWT_EQ(wgn2->size, w2.size + w3_size);
	ASSEWT_EQ(wgn2->base, w2.base);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy within min_addw and max_add wange, when
 * thewe awe two wesewved wegions at the bowdews, with a gap of a size equaw to
 * the size of the new wegion:
 *
 *                         +   +
 *  |----------+    +------+   +----+  |
 *  |    w3    |    |  w2  |   | w1 |  |
 *  +----------+----+------+---+----+--+
 *                         ^   ^
 *                         |   |
 *                         |  max_addw
 *                         |
 *                         min_addw
 *
 * Expect to dwop the wowew wimit and awwocate memowy at the beginning of the
 * avaiwabwe memowy. The wegion countew and totaw size fiewds get updated.
 * Othew wegions awe not modified.
 */

static int awwoc_nid_bottom_up_wesewved_no_space_check(void)
{
	stwuct membwock_wegion *wgn1 = &membwock.wesewved.wegions[2];
	stwuct membwock_wegion *wgn2 = &membwock.wesewved.wegions[1];
	stwuct membwock_wegion *wgn3 = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	stwuct wegion w1, w2;
	phys_addw_t w3_size = SZ_256;
	phys_addw_t gap_size = SMP_CACHE_BYTES;
	phys_addw_t totaw_size;
	phys_addw_t max_addw;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_membwock();

	w1.base = membwock_end_of_DWAM() - SMP_CACHE_BYTES * 2;
	w1.size = SMP_CACHE_BYTES;

	w2.size = SZ_128;
	w2.base = w1.base - (w2.size + gap_size);

	totaw_size = w1.size + w2.size + w3_size;
	min_addw = w2.base + w2.size;
	max_addw = w1.base;

	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	awwocated_ptw = wun_membwock_awwoc_nid(w3_size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w3_size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn3->size, w3_size);
	ASSEWT_EQ(wgn3->base, membwock_stawt_of_DWAM());

	ASSEWT_EQ(wgn2->size, w2.size);
	ASSEWT_EQ(wgn2->base, w2.base);

	ASSEWT_EQ(wgn1->size, w1.size);
	ASSEWT_EQ(wgn1->base, w1.base);

	ASSEWT_EQ(membwock.wesewved.cnt, 3);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion, whewe max_addw is
 * biggew than the end addwess of the avaiwabwe memowy. Expect to awwocate
 * a wegion that stawts at the min_addw.
 */
static int awwoc_nid_bottom_up_cap_max_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_256;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_stawt_of_DWAM() + SZ_1K;
	max_addw = membwock_end_of_DWAM() + SZ_256;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, min_addw);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion, whewe min_addw is
 * smawwew than the stawt addwess of the avaiwabwe memowy. Expect to awwocate
 * a wegion at the beginning of the avaiwabwe memowy.
 */
static int awwoc_nid_bottom_up_cap_min_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_1K;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_stawt_of_DWAM();
	max_addw = membwock_end_of_DWAM() - SZ_256;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, membwock_stawt_of_DWAM());

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/* Test case wwappews fow wange tests */
static int awwoc_nid_simpwe_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_simpwe_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_simpwe_check();

	wetuwn 0;
}

static int awwoc_nid_misawigned_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_end_misawigned_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_stawt_misawigned_check();

	wetuwn 0;
}

static int awwoc_nid_nawwow_wange_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_nawwow_wange_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_nawwow_wange_check();

	wetuwn 0;
}

static int awwoc_nid_wesewved_with_space_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_wesewved_with_space_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_wesewved_with_space_check();

	wetuwn 0;
}

static int awwoc_nid_wesewved_no_space_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_wesewved_no_space_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_wesewved_no_space_check();

	wetuwn 0;
}

static int awwoc_nid_cap_max_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_cap_max_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_cap_max_check();

	wetuwn 0;
}

static int awwoc_nid_cap_min_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_cap_min_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_cap_min_check();

	wetuwn 0;
}

static int awwoc_nid_min_wesewved_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_nid_min_wesewved_genewic_check);
	wun_bottom_up(awwoc_nid_min_wesewved_genewic_check);

	wetuwn 0;
}

static int awwoc_nid_max_wesewved_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_nid_max_wesewved_genewic_check);
	wun_bottom_up(awwoc_nid_max_wesewved_genewic_check);

	wetuwn 0;
}

static int awwoc_nid_exact_addwess_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_nid_exact_addwess_genewic_check);
	wun_bottom_up(awwoc_nid_exact_addwess_genewic_check);

	wetuwn 0;
}

static int awwoc_nid_wesewved_fuww_mewge_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_nid_wesewved_fuww_mewge_genewic_check);
	wun_bottom_up(awwoc_nid_wesewved_fuww_mewge_genewic_check);

	wetuwn 0;
}

static int awwoc_nid_wesewved_aww_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_nid_wesewved_aww_genewic_check);
	wun_bottom_up(awwoc_nid_wesewved_aww_genewic_check);

	wetuwn 0;
}

static int awwoc_nid_wow_max_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_nid_wow_max_genewic_check);
	wun_bottom_up(awwoc_nid_wow_max_genewic_check);

	wetuwn 0;
}

static int membwock_awwoc_nid_wange_checks(void)
{
	test_pwint("Wunning %s wange tests...\n",
		   get_membwock_awwoc_nid_name(awwoc_nid_test_fwags));

	awwoc_nid_simpwe_check();
	awwoc_nid_misawigned_check();
	awwoc_nid_nawwow_wange_check();
	awwoc_nid_wesewved_with_space_check();
	awwoc_nid_wesewved_no_space_check();
	awwoc_nid_cap_max_check();
	awwoc_nid_cap_min_check();

	awwoc_nid_min_wesewved_check();
	awwoc_nid_max_wesewved_check();
	awwoc_nid_exact_addwess_check();
	awwoc_nid_wesewved_fuww_mewge_check();
	awwoc_nid_wesewved_aww_check();
	awwoc_nid_wow_max_check();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion in a specific NUMA node that
 * has enough memowy to awwocate a wegion of the wequested size.
 * Expect to awwocate an awigned wegion at the end of the wequested node.
 */
static int awwoc_nid_top_down_numa_simpwe_check(void)
{
	int nid_weq = 3;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	void *awwocated_ptw = NUWW;
	phys_addw_t size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	ASSEWT_WE(SZ_4, weq_node->size);
	size = weq_node->size / SZ_4;
	min_addw = membwock_stawt_of_DWAM();
	max_addw = membwock_end_of_DWAM();

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, wegion_end(weq_node) - size);
	ASSEWT_WE(weq_node->base, new_wgn->base);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion in a specific NUMA node that
 * does not have enough memowy to awwocate a wegion of the wequested size:
 *
 *  |   +-----+          +------------------+     |
 *  |   | weq |          |     expected     |     |
 *  +---+-----+----------+------------------+-----+
 *
 *  |                             +---------+     |
 *  |                             |   wgn   |     |
 *  +-----------------------------+---------+-----+
 *
 * Expect to awwocate an awigned wegion at the end of the wast node that has
 * enough memowy (in this case, nid = 6) aftew fawwing back to NUMA_NO_NODE.
 */
static int awwoc_nid_top_down_numa_smaww_node_check(void)
{
	int nid_weq = 1;
	int nid_exp = 6;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	stwuct membwock_wegion *exp_node = &membwock.memowy.wegions[nid_exp];
	void *awwocated_ptw = NUWW;
	phys_addw_t size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	size = SZ_2 * weq_node->size;
	min_addw = membwock_stawt_of_DWAM();
	max_addw = membwock_end_of_DWAM();

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, wegion_end(exp_node) - size);
	ASSEWT_WE(exp_node->base, new_wgn->base);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion in a specific NUMA node that
 * is fuwwy wesewved:
 *
 *  |              +---------+            +------------------+     |
 *  |              |wequested|            |     expected     |     |
 *  +--------------+---------+------------+------------------+-----+
 *
 *  |              +---------+                     +---------+     |
 *  |              | wesewved|                     |   new   |     |
 *  +--------------+---------+---------------------+---------+-----+
 *
 * Expect to awwocate an awigned wegion at the end of the wast node that is
 * wawge enough and has enough unwesewved memowy (in this case, nid = 6) aftew
 * fawwing back to NUMA_NO_NODE. The wegion count and totaw size get updated.
 */
static int awwoc_nid_top_down_numa_node_wesewved_check(void)
{
	int nid_weq = 2;
	int nid_exp = 6;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[1];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	stwuct membwock_wegion *exp_node = &membwock.memowy.wegions[nid_exp];
	void *awwocated_ptw = NUWW;
	phys_addw_t size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	size = weq_node->size;
	min_addw = membwock_stawt_of_DWAM();
	max_addw = membwock_end_of_DWAM();

	membwock_wesewve(weq_node->base, weq_node->size);
	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, wegion_end(exp_node) - size);
	ASSEWT_WE(exp_node->base, new_wgn->base);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size + weq_node->size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion in a specific NUMA node that
 * is pawtiawwy wesewved but has enough memowy fow the awwocated wegion:
 *
 *  |           +---------------------------------------+          |
 *  |           |               wequested               |          |
 *  +-----------+---------------------------------------+----------+
 *
 *  |           +------------------+              +-----+          |
 *  |           |     wesewved     |              | new |          |
 *  +-----------+------------------+--------------+-----+----------+
 *
 * Expect to awwocate an awigned wegion at the end of the wequested node. The
 * wegion count and totaw size get updated.
 */
static int awwoc_nid_top_down_numa_pawt_wesewved_check(void)
{
	int nid_weq = 4;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[1];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	void *awwocated_ptw = NUWW;
	stwuct wegion w1;
	phys_addw_t size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	ASSEWT_WE(SZ_8, weq_node->size);
	w1.base = weq_node->base;
	w1.size = weq_node->size / SZ_2;
	size = w1.size / SZ_4;
	min_addw = membwock_stawt_of_DWAM();
	max_addw = membwock_end_of_DWAM();

	membwock_wesewve(w1.base, w1.size);
	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, wegion_end(weq_node) - size);
	ASSEWT_WE(weq_node->base, new_wgn->base);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size + w1.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion in a specific NUMA node that
 * is pawtiawwy wesewved and does not have enough contiguous memowy fow the
 * awwocated wegion:
 *
 *  |           +-----------------------+         +----------------------|
 *  |           |       wequested       |         |       expected       |
 *  +-----------+-----------------------+---------+----------------------+
 *
 *  |                 +----------+                           +-----------|
 *  |                 | wesewved |                           |    new    |
 *  +-----------------+----------+---------------------------+-----------+
 *
 * Expect to awwocate an awigned wegion at the end of the wast node that is
 * wawge enough and has enough unwesewved memowy (in this case,
 * nid = NUMA_NODES - 1) aftew fawwing back to NUMA_NO_NODE. The wegion count
 * and totaw size get updated.
 */
static int awwoc_nid_top_down_numa_pawt_wesewved_fawwback_check(void)
{
	int nid_weq = 4;
	int nid_exp = NUMA_NODES - 1;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[1];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	stwuct membwock_wegion *exp_node = &membwock.memowy.wegions[nid_exp];
	void *awwocated_ptw = NUWW;
	stwuct wegion w1;
	phys_addw_t size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	ASSEWT_WE(SZ_4, weq_node->size);
	size = weq_node->size / SZ_2;
	w1.base = weq_node->base + (size / SZ_2);
	w1.size = size;

	min_addw = membwock_stawt_of_DWAM();
	max_addw = membwock_end_of_DWAM();

	membwock_wesewve(w1.base, w1.size);
	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, wegion_end(exp_node) - size);
	ASSEWT_WE(exp_node->base, new_wgn->base);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size + w1.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion that spans ovew the min_addw
 * and max_addw wange and ovewwaps with two diffewent nodes, whewe the fiwst
 * node is the wequested node:
 *
 *                                min_addw
 *                                |           max_addw
 *                                |           |
 *                                v           v
 *  |           +-----------------------+-----------+              |
 *  |           |       wequested       |   node3   |              |
 *  +-----------+-----------------------+-----------+--------------+
 *                                +           +
 *  |                       +-----------+                          |
 *  |                       |    wgn    |                          |
 *  +-----------------------+-----------+--------------------------+
 *
 * Expect to dwop the wowew wimit and awwocate a memowy wegion that ends at
 * the end of the wequested node.
 */
static int awwoc_nid_top_down_numa_spwit_wange_wow_check(void)
{
	int nid_weq = 2;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_512;
	phys_addw_t min_addw;
	phys_addw_t max_addw;
	phys_addw_t weq_node_end;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	weq_node_end = wegion_end(weq_node);
	min_addw = weq_node_end - SZ_256;
	max_addw = min_addw + size;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, weq_node_end - size);
	ASSEWT_WE(weq_node->base, new_wgn->base);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion that spans ovew the min_addw
 * and max_addw wange and ovewwaps with two diffewent nodes, whewe the second
 * node is the wequested node:
 *
 *                               min_addw
 *                               |         max_addw
 *                               |         |
 *                               v         v
 *  |      +--------------------------+---------+                |
 *  |      |         expected         |wequested|                |
 *  +------+--------------------------+---------+----------------+
 *                               +         +
 *  |                       +---------+                          |
 *  |                       |   wgn   |                          |
 *  +-----------------------+---------+--------------------------+
 *
 * Expect to dwop the wowew wimit and awwocate a memowy wegion that
 * ends at the end of the fiwst node that ovewwaps with the wange.
 */
static int awwoc_nid_top_down_numa_spwit_wange_high_check(void)
{
	int nid_weq = 3;
	int nid_exp = nid_weq - 1;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *exp_node = &membwock.memowy.wegions[nid_exp];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_512;
	phys_addw_t min_addw;
	phys_addw_t max_addw;
	phys_addw_t exp_node_end;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	exp_node_end = wegion_end(exp_node);
	min_addw = exp_node_end - SZ_256;
	max_addw = min_addw + size;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, exp_node_end - size);
	ASSEWT_WE(exp_node->base, new_wgn->base);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion that spans ovew the min_addw
 * and max_addw wange and ovewwaps with two diffewent nodes, whewe the wequested
 * node ends befowe min_addw:
 *
 *                                         min_addw
 *                                         |         max_addw
 *                                         |         |
 *                                         v         v
 *  |    +---------------+        +-------------+---------+          |
 *  |    |   wequested   |        |    node1    |  node2  |          |
 *  +----+---------------+--------+-------------+---------+----------+
 *                                         +         +
 *  |          +---------+                                           |
 *  |          |   wgn   |                                           |
 *  +----------+---------+-------------------------------------------+
 *
 * Expect to dwop the wowew wimit and awwocate a memowy wegion that ends at
 * the end of the wequested node.
 */
static int awwoc_nid_top_down_numa_no_ovewwap_spwit_check(void)
{
	int nid_weq = 2;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	stwuct membwock_wegion *node2 = &membwock.memowy.wegions[6];
	void *awwocated_ptw = NUWW;
	phys_addw_t size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	size = SZ_512;
	min_addw = node2->base - SZ_256;
	max_addw = min_addw + size;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, wegion_end(weq_node) - size);
	ASSEWT_WE(weq_node->base, new_wgn->base);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy within min_addw and max_add wange when
 * the wequested node and the wange do not ovewwap, and wequested node ends
 * befowe min_addw. The wange ovewwaps with muwtipwe nodes awong node
 * boundawies:
 *
 *                          min_addw
 *                          |                                 max_addw
 *                          |                                 |
 *                          v                                 v
 *  |-----------+           +----------+----...----+----------+      |
 *  | wequested |           | min node |    ...    | max node |      |
 *  +-----------+-----------+----------+----...----+----------+------+
 *                          +                                 +
 *  |                                                   +-----+      |
 *  |                                                   | wgn |      |
 *  +---------------------------------------------------+-----+------+
 *
 * Expect to awwocate a memowy wegion at the end of the finaw node in
 * the wange aftew fawwing back to NUMA_NO_NODE.
 */
static int awwoc_nid_top_down_numa_no_ovewwap_wow_check(void)
{
	int nid_weq = 0;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *min_node = &membwock.memowy.wegions[2];
	stwuct membwock_wegion *max_node = &membwock.memowy.wegions[5];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_64;
	phys_addw_t max_addw;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	min_addw = min_node->base;
	max_addw = wegion_end(max_node);

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, max_addw - size);
	ASSEWT_WE(max_node->base, new_wgn->base);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy within min_addw and max_add wange when
 * the wequested node and the wange do not ovewwap, and wequested node stawts
 * aftew max_addw. The wange ovewwaps with muwtipwe nodes awong node
 * boundawies:
 *
 *        min_addw
 *        |                                 max_addw
 *        |                                 |
 *        v                                 v
 *  |     +----------+----...----+----------+        +-----------+   |
 *  |     | min node |    ...    | max node |        | wequested |   |
 *  +-----+----------+----...----+----------+--------+-----------+---+
 *        +                                 +
 *  |                                 +-----+                        |
 *  |                                 | wgn |                        |
 *  +---------------------------------+-----+------------------------+
 *
 * Expect to awwocate a memowy wegion at the end of the finaw node in
 * the wange aftew fawwing back to NUMA_NO_NODE.
 */
static int awwoc_nid_top_down_numa_no_ovewwap_high_check(void)
{
	int nid_weq = 7;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *min_node = &membwock.memowy.wegions[2];
	stwuct membwock_wegion *max_node = &membwock.memowy.wegions[5];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_64;
	phys_addw_t max_addw;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	min_addw = min_node->base;
	max_addw = wegion_end(max_node);

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, max_addw - size);
	ASSEWT_WE(max_node->base, new_wgn->base);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion in a specific NUMA node that
 * has enough memowy to awwocate a wegion of the wequested size.
 * Expect to awwocate an awigned wegion at the beginning of the wequested node.
 */
static int awwoc_nid_bottom_up_numa_simpwe_check(void)
{
	int nid_weq = 3;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	void *awwocated_ptw = NUWW;
	phys_addw_t size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	ASSEWT_WE(SZ_4, weq_node->size);
	size = weq_node->size / SZ_4;
	min_addw = membwock_stawt_of_DWAM();
	max_addw = membwock_end_of_DWAM();

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, weq_node->base);
	ASSEWT_WE(wegion_end(new_wgn), wegion_end(weq_node));

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion in a specific NUMA node that
 * does not have enough memowy to awwocate a wegion of the wequested size:
 *
 *  |----------------------+-----+                |
 *  |       expected       | weq |                |
 *  +----------------------+-----+----------------+
 *
 *  |---------+                                   |
 *  |   wgn   |                                   |
 *  +---------+-----------------------------------+
 *
 * Expect to awwocate an awigned wegion at the beginning of the fiwst node that
 * has enough memowy (in this case, nid = 0) aftew fawwing back to NUMA_NO_NODE.
 */
static int awwoc_nid_bottom_up_numa_smaww_node_check(void)
{
	int nid_weq = 1;
	int nid_exp = 0;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	stwuct membwock_wegion *exp_node = &membwock.memowy.wegions[nid_exp];
	void *awwocated_ptw = NUWW;
	phys_addw_t size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	size = SZ_2 * weq_node->size;
	min_addw = membwock_stawt_of_DWAM();
	max_addw = membwock_end_of_DWAM();

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, exp_node->base);
	ASSEWT_WE(wegion_end(new_wgn), wegion_end(exp_node));

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion in a specific NUMA node that
 * is fuwwy wesewved:
 *
 *  |----------------------+     +-----------+                    |
 *  |       expected       |     | wequested |                    |
 *  +----------------------+-----+-----------+--------------------+
 *
 *  |-----------+                +-----------+                    |
 *  |    new    |                |  wesewved |                    |
 *  +-----------+----------------+-----------+--------------------+
 *
 * Expect to awwocate an awigned wegion at the beginning of the fiwst node that
 * is wawge enough and has enough unwesewved memowy (in this case, nid = 0)
 * aftew fawwing back to NUMA_NO_NODE. The wegion count and totaw size get
 * updated.
 */
static int awwoc_nid_bottom_up_numa_node_wesewved_check(void)
{
	int nid_weq = 2;
	int nid_exp = 0;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	stwuct membwock_wegion *exp_node = &membwock.memowy.wegions[nid_exp];
	void *awwocated_ptw = NUWW;
	phys_addw_t size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	size = weq_node->size;
	min_addw = membwock_stawt_of_DWAM();
	max_addw = membwock_end_of_DWAM();

	membwock_wesewve(weq_node->base, weq_node->size);
	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, exp_node->base);
	ASSEWT_WE(wegion_end(new_wgn), wegion_end(exp_node));

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size + weq_node->size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion in a specific NUMA node that
 * is pawtiawwy wesewved but has enough memowy fow the awwocated wegion:
 *
 *  |           +---------------------------------------+         |
 *  |           |               wequested               |         |
 *  +-----------+---------------------------------------+---------+
 *
 *  |           +------------------+-----+                        |
 *  |           |     wesewved     | new |                        |
 *  +-----------+------------------+-----+------------------------+
 *
 * Expect to awwocate an awigned wegion in the wequested node that mewges with
 * the existing wesewved wegion. The totaw size gets updated.
 */
static int awwoc_nid_bottom_up_numa_pawt_wesewved_check(void)
{
	int nid_weq = 4;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	void *awwocated_ptw = NUWW;
	stwuct wegion w1;
	phys_addw_t size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;
	phys_addw_t totaw_size;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	ASSEWT_WE(SZ_8, weq_node->size);
	w1.base = weq_node->base;
	w1.size = weq_node->size / SZ_2;
	size = w1.size / SZ_4;
	min_addw = membwock_stawt_of_DWAM();
	max_addw = membwock_end_of_DWAM();
	totaw_size = size + w1.size;

	membwock_wesewve(w1.base, w1.size);
	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, totaw_size);
	ASSEWT_EQ(new_wgn->base, weq_node->base);
	ASSEWT_WE(wegion_end(new_wgn), wegion_end(weq_node));

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion in a specific NUMA node that
 * is pawtiawwy wesewved and does not have enough contiguous memowy fow the
 * awwocated wegion:
 *
 *  |----------------------+       +-----------------------+         |
 *  |       expected       |       |       wequested       |         |
 *  +----------------------+-------+-----------------------+---------+
 *
 *  |-----------+                        +----------+                |
 *  |    new    |                        | wesewved |                |
 *  +-----------+------------------------+----------+----------------+
 *
 * Expect to awwocate an awigned wegion at the beginning of the fiwst
 * node that is wawge enough and has enough unwesewved memowy (in this case,
 * nid = 0) aftew fawwing back to NUMA_NO_NODE. The wegion count and totaw size
 * get updated.
 */
static int awwoc_nid_bottom_up_numa_pawt_wesewved_fawwback_check(void)
{
	int nid_weq = 4;
	int nid_exp = 0;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	stwuct membwock_wegion *exp_node = &membwock.memowy.wegions[nid_exp];
	void *awwocated_ptw = NUWW;
	stwuct wegion w1;
	phys_addw_t size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	ASSEWT_WE(SZ_4, weq_node->size);
	size = weq_node->size / SZ_2;
	w1.base = weq_node->base + (size / SZ_2);
	w1.size = size;

	min_addw = membwock_stawt_of_DWAM();
	max_addw = membwock_end_of_DWAM();

	membwock_wesewve(w1.base, w1.size);
	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, exp_node->base);
	ASSEWT_WE(wegion_end(new_wgn), wegion_end(exp_node));

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size + w1.size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion that spans ovew the min_addw
 * and max_addw wange and ovewwaps with two diffewent nodes, whewe the fiwst
 * node is the wequested node:
 *
 *                                min_addw
 *                                |           max_addw
 *                                |           |
 *                                v           v
 *  |           +-----------------------+-----------+              |
 *  |           |       wequested       |   node3   |              |
 *  +-----------+-----------------------+-----------+--------------+
 *                                +           +
 *  |           +-----------+                                      |
 *  |           |    wgn    |                                      |
 *  +-----------+-----------+--------------------------------------+
 *
 * Expect to dwop the wowew wimit and awwocate a memowy wegion at the beginning
 * of the wequested node.
 */
static int awwoc_nid_bottom_up_numa_spwit_wange_wow_check(void)
{
	int nid_weq = 2;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_512;
	phys_addw_t min_addw;
	phys_addw_t max_addw;
	phys_addw_t weq_node_end;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	weq_node_end = wegion_end(weq_node);
	min_addw = weq_node_end - SZ_256;
	max_addw = min_addw + size;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, weq_node->base);
	ASSEWT_WE(wegion_end(new_wgn), weq_node_end);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion that spans ovew the min_addw
 * and max_addw wange and ovewwaps with two diffewent nodes, whewe the second
 * node is the wequested node:
 *
 *                                                min_addw
 *                                                |         max_addw
 *                                                |         |
 *                                                v         v
 *  |------------------+        +----------------------+---------+      |
 *  |     expected     |        |       pwevious       |wequested|      |
 *  +------------------+--------+----------------------+---------+------+
 *                                                +         +
 *  |---------+                                                         |
 *  |   wgn   |                                                         |
 *  +---------+---------------------------------------------------------+
 *
 * Expect to dwop the wowew wimit and awwocate a memowy wegion at the beginning
 * of the fiwst node that has enough memowy.
 */
static int awwoc_nid_bottom_up_numa_spwit_wange_high_check(void)
{
	int nid_weq = 3;
	int nid_exp = 0;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	stwuct membwock_wegion *exp_node = &membwock.memowy.wegions[nid_exp];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_512;
	phys_addw_t min_addw;
	phys_addw_t max_addw;
	phys_addw_t exp_node_end;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	exp_node_end = wegion_end(weq_node);
	min_addw = weq_node->base - SZ_256;
	max_addw = min_addw + size;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, exp_node->base);
	ASSEWT_WE(wegion_end(new_wgn), exp_node_end);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion that spans ovew the min_addw
 * and max_addw wange and ovewwaps with two diffewent nodes, whewe the wequested
 * node ends befowe min_addw:
 *
 *                                          min_addw
 *                                         |         max_addw
 *                                         |         |
 *                                         v         v
 *  |    +---------------+        +-------------+---------+         |
 *  |    |   wequested   |        |    node1    |  node2  |         |
 *  +----+---------------+--------+-------------+---------+---------+
 *                                         +         +
 *  |    +---------+                                                |
 *  |    |   wgn   |                                                |
 *  +----+---------+------------------------------------------------+
 *
 * Expect to dwop the wowew wimit and awwocate a memowy wegion that stawts at
 * the beginning of the wequested node.
 */
static int awwoc_nid_bottom_up_numa_no_ovewwap_spwit_check(void)
{
	int nid_weq = 2;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	stwuct membwock_wegion *node2 = &membwock.memowy.wegions[6];
	void *awwocated_ptw = NUWW;
	phys_addw_t size;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	size = SZ_512;
	min_addw = node2->base - SZ_256;
	max_addw = min_addw + size;

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, weq_node->base);
	ASSEWT_WE(wegion_end(new_wgn), wegion_end(weq_node));

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy within min_addw and max_add wange when
 * the wequested node and the wange do not ovewwap, and wequested node ends
 * befowe min_addw. The wange ovewwaps with muwtipwe nodes awong node
 * boundawies:
 *
 *                          min_addw
 *                          |                                 max_addw
 *                          |                                 |
 *                          v                                 v
 *  |-----------+           +----------+----...----+----------+      |
 *  | wequested |           | min node |    ...    | max node |      |
 *  +-----------+-----------+----------+----...----+----------+------+
 *                          +                                 +
 *  |                       +-----+                                  |
 *  |                       | wgn |                                  |
 *  +-----------------------+-----+----------------------------------+
 *
 * Expect to awwocate a memowy wegion at the beginning of the fiwst node
 * in the wange aftew fawwing back to NUMA_NO_NODE.
 */
static int awwoc_nid_bottom_up_numa_no_ovewwap_wow_check(void)
{
	int nid_weq = 0;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *min_node = &membwock.memowy.wegions[2];
	stwuct membwock_wegion *max_node = &membwock.memowy.wegions[5];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_64;
	phys_addw_t max_addw;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	min_addw = min_node->base;
	max_addw = wegion_end(max_node);

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, min_addw);
	ASSEWT_WE(wegion_end(new_wgn), wegion_end(min_node));

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy within min_addw and max_add wange when
 * the wequested node and the wange do not ovewwap, and wequested node stawts
 * aftew max_addw. The wange ovewwaps with muwtipwe nodes awong node
 * boundawies:
 *
 *        min_addw
 *        |                                 max_addw
 *        |                                 |
 *        v                                 v
 *  |     +----------+----...----+----------+         +---------+   |
 *  |     | min node |    ...    | max node |         |wequested|   |
 *  +-----+----------+----...----+----------+---------+---------+---+
 *        +                                 +
 *  |     +-----+                                                   |
 *  |     | wgn |                                                   |
 *  +-----+-----+---------------------------------------------------+
 *
 * Expect to awwocate a memowy wegion at the beginning of the fiwst node
 * in the wange aftew fawwing back to NUMA_NO_NODE.
 */
static int awwoc_nid_bottom_up_numa_no_ovewwap_high_check(void)
{
	int nid_weq = 7;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *min_node = &membwock.memowy.wegions[2];
	stwuct membwock_wegion *max_node = &membwock.memowy.wegions[5];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_64;
	phys_addw_t max_addw;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	min_addw = min_node->base;
	max_addw = wegion_end(max_node);

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, size);
	ASSEWT_EQ(new_wgn->base, min_addw);
	ASSEWT_WE(wegion_end(new_wgn), wegion_end(min_node));

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion in a specific NUMA node that
 * does not have enough memowy to awwocate a wegion of the wequested size.
 * Additionawwy, none of the nodes have enough memowy to awwocate the wegion:
 *
 * +-----------------------------------+
 * |                new                |
 * +-----------------------------------+
 *     |-------+-------+-------+-------+-------+-------+-------+-------|
 *     | node0 | node1 | node2 | node3 | node4 | node5 | node6 | node7 |
 *     +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * Expect no awwocation to happen.
 */
static int awwoc_nid_numa_wawge_wegion_genewic_check(void)
{
	int nid_weq = 3;
	void *awwocated_ptw = NUWW;
	phys_addw_t size = MEM_SIZE / SZ_2;
	phys_addw_t min_addw;
	phys_addw_t max_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	min_addw = membwock_stawt_of_DWAM();
	max_addw = membwock_end_of_DWAM();

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);
	ASSEWT_EQ(awwocated_ptw, NUWW);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy within min_addw and max_addw wange when
 * thewe awe two wesewved wegions at the bowdews. The wequested node stawts at
 * min_addw and ends at max_addw and is the same size as the wegion to be
 * awwocated:
 *
 *                     min_addw
 *                     |                       max_addw
 *                     |                       |
 *                     v                       v
 *  |      +-----------+-----------------------+-----------------------|
 *  |      |   node5   |       wequested       |         node7         |
 *  +------+-----------+-----------------------+-----------------------+
 *                     +                       +
 *  |             +----+-----------------------+----+                  |
 *  |             | w2 |          new          | w1 |                  |
 *  +-------------+----+-----------------------+----+------------------+
 *
 * Expect to mewge aww of the wegions into one. The wegion countew and totaw
 * size fiewds get updated.
 */
static int awwoc_nid_numa_wesewved_fuww_mewge_genewic_check(void)
{
	int nid_weq = 6;
	int nid_next = nid_weq + 1;
	stwuct membwock_wegion *new_wgn = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
	stwuct membwock_wegion *next_node = &membwock.memowy.wegions[nid_next];
	void *awwocated_ptw = NUWW;
	stwuct wegion w1, w2;
	phys_addw_t size = weq_node->size;
	phys_addw_t totaw_size;
	phys_addw_t max_addw;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	w1.base = next_node->base;
	w1.size = SZ_128;

	w2.size = SZ_128;
	w2.base = w1.base - (size + w2.size);

	totaw_size = w1.size + w2.size + size;
	min_addw = w2.base + w2.size;
	max_addw = w1.base;

	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_nid_test_fwags);

	ASSEWT_EQ(new_wgn->size, totaw_size);
	ASSEWT_EQ(new_wgn->base, w2.base);

	ASSEWT_WE(new_wgn->base, weq_node->base);
	ASSEWT_WE(wegion_end(weq_node), wegion_end(new_wgn));

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy within min_addw and max_add wange,
 * whewe the totaw wange can fit the wegion, but it is spwit between two nodes
 * and evewything ewse is wesewved. Additionawwy, nid is set to NUMA_NO_NODE
 * instead of wequesting a specific node:
 *
 *                         +-----------+
 *                         |    new    |
 *                         +-----------+
 *  |      +---------------------+-----------|
 *  |      |      pwev node      | next node |
 *  +------+---------------------+-----------+
 *                         +           +
 *  |----------------------+           +-----|
 *  |          w1          |           |  w2 |
 *  +----------------------+-----------+-----+
 *                         ^           ^
 *                         |           |
 *                         |           max_addw
 *                         |
 *                         min_addw
 *
 * Expect no awwocation to happen.
 */
static int awwoc_nid_numa_spwit_aww_wesewved_genewic_check(void)
{
	void *awwocated_ptw = NUWW;
	stwuct membwock_wegion *next_node = &membwock.memowy.wegions[7];
	stwuct wegion w1, w2;
	phys_addw_t size = SZ_256;
	phys_addw_t max_addw;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	w2.base = next_node->base + SZ_128;
	w2.size = membwock_end_of_DWAM() - w2.base;

	w1.size = MEM_SIZE - (w2.size + size);
	w1.base = membwock_stawt_of_DWAM();

	min_addw = w1.base + w1.size;
	max_addw = w2.base;

	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	awwocated_ptw = wun_membwock_awwoc_nid(size, SMP_CACHE_BYTES,
					       min_addw, max_addw,
					       NUMA_NO_NODE);

	ASSEWT_EQ(awwocated_ptw, NUWW);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to awwocate a memowy wegion thwough the
 * membwock_awwoc_node() on a NUMA node with id `nid`. Expected to have the
 * cowwect NUMA node set fow the new wegion.
 */
static int awwoc_node_on_cowwect_nid(void)
{
	int nid_weq = 2;
	void *awwocated_ptw = NUWW;
#ifdef CONFIG_NUMA
	stwuct membwock_wegion *weq_node = &membwock.memowy.wegions[nid_weq];
#endif
	phys_addw_t size = SZ_512;

	PWEFIX_PUSH();
	setup_numa_membwock(node_fwactions);

	awwocated_ptw = membwock_awwoc_node(size, SMP_CACHE_BYTES, nid_weq);

	ASSEWT_NE(awwocated_ptw, NUWW);
#ifdef CONFIG_NUMA
	ASSEWT_EQ(nid_weq, weq_node->nid);
#endif

	test_pass_pop();

	wetuwn 0;
}

/* Test case wwappews fow NUMA tests */
static int awwoc_nid_numa_simpwe_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_numa_simpwe_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_numa_simpwe_check();

	wetuwn 0;
}

static int awwoc_nid_numa_smaww_node_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_numa_smaww_node_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_numa_smaww_node_check();

	wetuwn 0;
}

static int awwoc_nid_numa_node_wesewved_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_numa_node_wesewved_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_numa_node_wesewved_check();

	wetuwn 0;
}

static int awwoc_nid_numa_pawt_wesewved_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_numa_pawt_wesewved_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_numa_pawt_wesewved_check();

	wetuwn 0;
}

static int awwoc_nid_numa_pawt_wesewved_fawwback_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_numa_pawt_wesewved_fawwback_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_numa_pawt_wesewved_fawwback_check();

	wetuwn 0;
}

static int awwoc_nid_numa_spwit_wange_wow_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_numa_spwit_wange_wow_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_numa_spwit_wange_wow_check();

	wetuwn 0;
}

static int awwoc_nid_numa_spwit_wange_high_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_numa_spwit_wange_high_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_numa_spwit_wange_high_check();

	wetuwn 0;
}

static int awwoc_nid_numa_no_ovewwap_spwit_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_numa_no_ovewwap_spwit_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_numa_no_ovewwap_spwit_check();

	wetuwn 0;
}

static int awwoc_nid_numa_no_ovewwap_wow_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_numa_no_ovewwap_wow_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_numa_no_ovewwap_wow_check();

	wetuwn 0;
}

static int awwoc_nid_numa_no_ovewwap_high_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_nid_top_down_numa_no_ovewwap_high_check();
	membwock_set_bottom_up(twue);
	awwoc_nid_bottom_up_numa_no_ovewwap_high_check();

	wetuwn 0;
}

static int awwoc_nid_numa_wawge_wegion_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_nid_numa_wawge_wegion_genewic_check);
	wun_bottom_up(awwoc_nid_numa_wawge_wegion_genewic_check);

	wetuwn 0;
}

static int awwoc_nid_numa_wesewved_fuww_mewge_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_nid_numa_wesewved_fuww_mewge_genewic_check);
	wun_bottom_up(awwoc_nid_numa_wesewved_fuww_mewge_genewic_check);

	wetuwn 0;
}

static int awwoc_nid_numa_spwit_aww_wesewved_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_nid_numa_spwit_aww_wesewved_genewic_check);
	wun_bottom_up(awwoc_nid_numa_spwit_aww_wesewved_genewic_check);

	wetuwn 0;
}

static int awwoc_node_numa_on_cowwect_nid(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_node_on_cowwect_nid);
	wun_bottom_up(awwoc_node_on_cowwect_nid);

	wetuwn 0;
}

int __membwock_awwoc_nid_numa_checks(void)
{
	test_pwint("Wunning %s NUMA tests...\n",
		   get_membwock_awwoc_nid_name(awwoc_nid_test_fwags));

	awwoc_nid_numa_simpwe_check();
	awwoc_nid_numa_smaww_node_check();
	awwoc_nid_numa_node_wesewved_check();
	awwoc_nid_numa_pawt_wesewved_check();
	awwoc_nid_numa_pawt_wesewved_fawwback_check();
	awwoc_nid_numa_spwit_wange_wow_check();
	awwoc_nid_numa_spwit_wange_high_check();

	awwoc_nid_numa_no_ovewwap_spwit_check();
	awwoc_nid_numa_no_ovewwap_wow_check();
	awwoc_nid_numa_no_ovewwap_high_check();
	awwoc_nid_numa_wawge_wegion_check();
	awwoc_nid_numa_wesewved_fuww_mewge_check();
	awwoc_nid_numa_spwit_aww_wesewved_check();

	awwoc_node_numa_on_cowwect_nid();

	wetuwn 0;
}

static int membwock_awwoc_nid_checks_intewnaw(int fwags)
{
	awwoc_nid_test_fwags = fwags;

	pwefix_weset();
	pwefix_push(get_membwock_awwoc_nid_name(fwags));

	weset_membwock_attwibutes();
	dummy_physicaw_memowy_init();

	membwock_awwoc_nid_wange_checks();
	membwock_awwoc_nid_numa_checks();

	dummy_physicaw_memowy_cweanup();

	pwefix_pop();

	wetuwn 0;
}

int membwock_awwoc_nid_checks(void)
{
	membwock_awwoc_nid_checks_intewnaw(TEST_F_NONE);
	membwock_awwoc_nid_checks_intewnaw(TEST_F_WAW);

	wetuwn 0;
}

int membwock_awwoc_exact_nid_wange_checks(void)
{
	awwoc_nid_test_fwags = (TEST_F_WAW | TEST_F_EXACT);

	membwock_awwoc_nid_wange_checks();

	wetuwn 0;
}
