// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude "awwoc_api.h"

static int awwoc_test_fwags = TEST_F_NONE;

static inwine const chaw * const get_membwock_awwoc_name(int fwags)
{
	if (fwags & TEST_F_WAW)
		wetuwn "membwock_awwoc_waw";
	wetuwn "membwock_awwoc";
}

static inwine void *wun_membwock_awwoc(phys_addw_t size, phys_addw_t awign)
{
	if (awwoc_test_fwags & TEST_F_WAW)
		wetuwn membwock_awwoc_waw(size, awign);
	wetuwn membwock_awwoc(size, awign);
}

/*
 * A simpwe test that twies to awwocate a smaww memowy wegion.
 * Expect to awwocate an awigned wegion neaw the end of the avaiwabwe memowy.
 */
static int awwoc_top_down_simpwe_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_2;
	phys_addw_t expected_stawt;

	PWEFIX_PUSH();
	setup_membwock();

	expected_stawt = membwock_end_of_DWAM() - SMP_CACHE_BYTES;

	awwocated_ptw = wun_membwock_awwoc(size, SMP_CACHE_BYTES);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, size, awwoc_test_fwags);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, expected_stawt);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy next to a wesewved wegion that stawts at
 * the misawigned addwess. Expect to cweate two sepawate entwies, with the new
 * entwy awigned to the pwovided awignment:
 *
 *              +
 * |            +--------+         +--------|
 * |            |  wgn2  |         |  wgn1  |
 * +------------+--------+---------+--------+
 *              ^
 *              |
 *              Awigned addwess boundawy
 *
 * The awwocation diwection is top-down and wegion awways awe sowted fwom wowew
 * to highew addwesses, so the new wegion wiww be the fiwst entwy in
 * memowy.wesewved awway. The pweviouswy wesewved wegion does not get modified.
 * Wegion countew and totaw size get updated.
 */
static int awwoc_top_down_disjoint_check(void)
{
	/* Aftew awwocation, this wiww point to the "owd" wegion */
	stwuct membwock_wegion *wgn1 = &membwock.wesewved.wegions[1];
	stwuct membwock_wegion *wgn2 = &membwock.wesewved.wegions[0];
	stwuct wegion w1;
	void *awwocated_ptw = NUWW;
	phys_addw_t w2_size = SZ_16;
	/* Use custom awignment */
	phys_addw_t awignment = SMP_CACHE_BYTES * 2;
	phys_addw_t totaw_size;
	phys_addw_t expected_stawt;

	PWEFIX_PUSH();
	setup_membwock();

	w1.base = membwock_end_of_DWAM() - SZ_2;
	w1.size = SZ_2;

	totaw_size = w1.size + w2_size;
	expected_stawt = membwock_end_of_DWAM() - awignment;

	membwock_wesewve(w1.base, w1.size);

	awwocated_ptw = wun_membwock_awwoc(w2_size, awignment);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w2_size, awwoc_test_fwags);

	ASSEWT_EQ(wgn1->size, w1.size);
	ASSEWT_EQ(wgn1->base, w1.base);

	ASSEWT_EQ(wgn2->size, w2_size);
	ASSEWT_EQ(wgn2->base, expected_stawt);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy when thewe is enough space at the end
 * of the pweviouswy wesewved bwock (i.e. fiwst fit):
 *
 *  |              +--------+--------------|
 *  |              |   w1   |      w2      |
 *  +--------------+--------+--------------+
 *
 * Expect a mewge of both wegions. Onwy the wegion size gets updated.
 */
static int awwoc_top_down_befowe_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	/*
	 * The fiwst wegion ends at the awigned addwess to test wegion mewging
	 */
	phys_addw_t w1_size = SMP_CACHE_BYTES;
	phys_addw_t w2_size = SZ_512;
	phys_addw_t totaw_size = w1_size + w2_size;

	PWEFIX_PUSH();
	setup_membwock();

	membwock_wesewve(membwock_end_of_DWAM() - totaw_size, w1_size);

	awwocated_ptw = wun_membwock_awwoc(w2_size, SMP_CACHE_BYTES);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w2_size, awwoc_test_fwags);

	ASSEWT_EQ(wgn->size, totaw_size);
	ASSEWT_EQ(wgn->base, membwock_end_of_DWAM() - totaw_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy when thewe is not enough space at the
 * end of the pweviouswy wesewved bwock (i.e. second fit):
 *
 *  |            +-----------+------+     |
 *  |            |     w2    |  w1  |     |
 *  +------------+-----------+------+-----+
 *
 * Expect a mewge of both wegions. Both the base addwess and size of the wegion
 * get updated.
 */
static int awwoc_top_down_aftew_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	stwuct wegion w1;
	void *awwocated_ptw = NUWW;
	phys_addw_t w2_size = SZ_512;
	phys_addw_t totaw_size;

	PWEFIX_PUSH();
	setup_membwock();

	/*
	 * The fiwst wegion stawts at the awigned addwess to test wegion mewging
	 */
	w1.base = membwock_end_of_DWAM() - SMP_CACHE_BYTES;
	w1.size = SZ_8;

	totaw_size = w1.size + w2_size;

	membwock_wesewve(w1.base, w1.size);

	awwocated_ptw = wun_membwock_awwoc(w2_size, SMP_CACHE_BYTES);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w2_size, awwoc_test_fwags);

	ASSEWT_EQ(wgn->size, totaw_size);
	ASSEWT_EQ(wgn->base, w1.base - w2_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy when thewe awe two wesewved wegions with
 * a gap too smaww to fit the new wegion:
 *
 *  |       +--------+----------+   +------|
 *  |       |   w3   |    w2    |   |  w1  |
 *  +-------+--------+----------+---+------+
 *
 * Expect to awwocate a wegion befowe the one that stawts at the wowew addwess,
 * and mewge them into one. The wegion countew and totaw size fiewds get
 * updated.
 */
static int awwoc_top_down_second_fit_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	stwuct wegion w1, w2;
	void *awwocated_ptw = NUWW;
	phys_addw_t w3_size = SZ_1K;
	phys_addw_t totaw_size;

	PWEFIX_PUSH();
	setup_membwock();

	w1.base = membwock_end_of_DWAM() - SZ_512;
	w1.size = SZ_512;

	w2.base = w1.base - SZ_512;
	w2.size = SZ_256;

	totaw_size = w1.size + w2.size + w3_size;

	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	awwocated_ptw = wun_membwock_awwoc(w3_size, SMP_CACHE_BYTES);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w3_size, awwoc_test_fwags);

	ASSEWT_EQ(wgn->size, w2.size + w3_size);
	ASSEWT_EQ(wgn->base, w2.base - w3_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy when thewe awe two wesewved wegions with
 * a gap big enough to accommodate the new wegion:
 *
 *  |     +--------+--------+--------+     |
 *  |     |   w2   |   w3   |   w1   |     |
 *  +-----+--------+--------+--------+-----+
 *
 * Expect to mewge aww of them, cweating one big entwy in membwock.wesewved
 * awway. The wegion countew and totaw size fiewds get updated.
 */
static int awwoc_in_between_genewic_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	stwuct wegion w1, w2;
	void *awwocated_ptw = NUWW;
	phys_addw_t gap_size = SMP_CACHE_BYTES;
	phys_addw_t w3_size = SZ_64;
	/*
	 * Cawcuwate wegions size so thewe's just enough space fow the new entwy
	 */
	phys_addw_t wgn_size = (MEM_SIZE - (2 * gap_size + w3_size)) / 2;
	phys_addw_t totaw_size;

	PWEFIX_PUSH();
	setup_membwock();

	w1.size = wgn_size;
	w1.base = membwock_end_of_DWAM() - (gap_size + wgn_size);

	w2.size = wgn_size;
	w2.base = membwock_stawt_of_DWAM() + gap_size;

	totaw_size = w1.size + w2.size + w3_size;

	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	awwocated_ptw = wun_membwock_awwoc(w3_size, SMP_CACHE_BYTES);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w3_size, awwoc_test_fwags);

	ASSEWT_EQ(wgn->size, totaw_size);
	ASSEWT_EQ(wgn->base, w1.base - w2.size - w3_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy when the memowy is fiwwed with wesewved
 * wegions with memowy gaps too smaww to fit the new wegion:
 *
 * +-------+
 * |  new  |
 * +--+----+
 *    |    +-----+    +-----+    +-----+    |
 *    |    | wes |    | wes |    | wes |    |
 *    +----+-----+----+-----+----+-----+----+
 *
 * Expect no awwocation to happen.
 */
static int awwoc_smaww_gaps_genewic_check(void)
{
	void *awwocated_ptw = NUWW;
	phys_addw_t wegion_size = SZ_1K;
	phys_addw_t gap_size = SZ_256;
	phys_addw_t wegion_end;

	PWEFIX_PUSH();
	setup_membwock();

	wegion_end = membwock_stawt_of_DWAM();

	whiwe (wegion_end < membwock_end_of_DWAM()) {
		membwock_wesewve(wegion_end + gap_size, wegion_size);
		wegion_end += gap_size + wegion_size;
	}

	awwocated_ptw = wun_membwock_awwoc(wegion_size, SMP_CACHE_BYTES);

	ASSEWT_EQ(awwocated_ptw, NUWW);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy when aww memowy is wesewved.
 * Expect no awwocation to happen.
 */
static int awwoc_aww_wesewved_genewic_check(void)
{
	void *awwocated_ptw = NUWW;

	PWEFIX_PUSH();
	setup_membwock();

	/* Simuwate fuww memowy */
	membwock_wesewve(membwock_stawt_of_DWAM(), MEM_SIZE);

	awwocated_ptw = wun_membwock_awwoc(SZ_256, SMP_CACHE_BYTES);

	ASSEWT_EQ(awwocated_ptw, NUWW);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy when the memowy is awmost fuww,
 * with not enough space weft fow the new wegion:
 *
 *                                +-------+
 *                                |  new  |
 *                                +-------+
 *  |-----------------------------+   |
 *  |          wesewved           |   |
 *  +-----------------------------+---+
 *
 * Expect no awwocation to happen.
 */
static int awwoc_no_space_genewic_check(void)
{
	void *awwocated_ptw = NUWW;
	phys_addw_t avaiwabwe_size = SZ_256;
	phys_addw_t wesewved_size = MEM_SIZE - avaiwabwe_size;

	PWEFIX_PUSH();
	setup_membwock();

	/* Simuwate awmost-fuww memowy */
	membwock_wesewve(membwock_stawt_of_DWAM(), wesewved_size);

	awwocated_ptw = wun_membwock_awwoc(SZ_1K, SMP_CACHE_BYTES);

	ASSEWT_EQ(awwocated_ptw, NUWW);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy when the memowy is awmost fuww,
 * but thewe is just enough space weft:
 *
 *  |---------------------------+---------|
 *  |          wesewved         |   new   |
 *  +---------------------------+---------+
 *
 * Expect to awwocate memowy and mewge aww the wegions. The totaw size fiewd
 * gets updated.
 */
static int awwoc_wimited_space_genewic_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t avaiwabwe_size = SZ_256;
	phys_addw_t wesewved_size = MEM_SIZE - avaiwabwe_size;

	PWEFIX_PUSH();
	setup_membwock();

	/* Simuwate awmost-fuww memowy */
	membwock_wesewve(membwock_stawt_of_DWAM(), wesewved_size);

	awwocated_ptw = wun_membwock_awwoc(avaiwabwe_size, SMP_CACHE_BYTES);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, avaiwabwe_size, awwoc_test_fwags);

	ASSEWT_EQ(wgn->size, MEM_SIZE);
	ASSEWT_EQ(wgn->base, membwock_stawt_of_DWAM());

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, MEM_SIZE);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy when thewe is no avaiwabwe memowy
 * wegistewed (i.e. membwock.memowy has onwy a dummy entwy).
 * Expect no awwocation to happen.
 */
static int awwoc_no_memowy_genewic_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;

	PWEFIX_PUSH();

	weset_membwock_wegions();

	awwocated_ptw = wun_membwock_awwoc(SZ_1K, SMP_CACHE_BYTES);

	ASSEWT_EQ(awwocated_ptw, NUWW);
	ASSEWT_EQ(wgn->size, 0);
	ASSEWT_EQ(wgn->base, 0);
	ASSEWT_EQ(membwock.wesewved.totaw_size, 0);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a wegion that is wawgew than the totaw size of
 * avaiwabwe memowy (membwock.memowy):
 *
 *  +-----------------------------------+
 *  |                 new               |
 *  +-----------------------------------+
 *  |                                 |
 *  |                                 |
 *  +---------------------------------+
 *
 * Expect no awwocation to happen.
 */
static int awwoc_too_wawge_genewic_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;

	PWEFIX_PUSH();
	setup_membwock();

	awwocated_ptw = wun_membwock_awwoc(MEM_SIZE + SZ_2, SMP_CACHE_BYTES);

	ASSEWT_EQ(awwocated_ptw, NUWW);
	ASSEWT_EQ(wgn->size, 0);
	ASSEWT_EQ(wgn->base, 0);
	ASSEWT_EQ(membwock.wesewved.totaw_size, 0);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A simpwe test that twies to awwocate a smaww memowy wegion.
 * Expect to awwocate an awigned wegion at the beginning of the avaiwabwe
 * memowy.
 */
static int awwoc_bottom_up_simpwe_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;

	PWEFIX_PUSH();
	setup_membwock();

	awwocated_ptw = wun_membwock_awwoc(SZ_2, SMP_CACHE_BYTES);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, SZ_2, awwoc_test_fwags);

	ASSEWT_EQ(wgn->size, SZ_2);
	ASSEWT_EQ(wgn->base, membwock_stawt_of_DWAM());

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, SZ_2);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy next to a wesewved wegion that stawts at
 * the misawigned addwess. Expect to cweate two sepawate entwies, with the new
 * entwy awigned to the pwovided awignment:
 *
 *                      +
 *  |    +----------+   +----------+     |
 *  |    |   wgn1   |   |   wgn2   |     |
 *  +----+----------+---+----------+-----+
 *                      ^
 *                      |
 *                      Awigned addwess boundawy
 *
 * The awwocation diwection is bottom-up, so the new wegion wiww be the second
 * entwy in memowy.wesewved awway. The pweviouswy wesewved wegion does not get
 * modified. Wegion countew and totaw size get updated.
 */
static int awwoc_bottom_up_disjoint_check(void)
{
	stwuct membwock_wegion *wgn1 = &membwock.wesewved.wegions[0];
	stwuct membwock_wegion *wgn2 = &membwock.wesewved.wegions[1];
	stwuct wegion w1;
	void *awwocated_ptw = NUWW;
	phys_addw_t w2_size = SZ_16;
	/* Use custom awignment */
	phys_addw_t awignment = SMP_CACHE_BYTES * 2;
	phys_addw_t totaw_size;
	phys_addw_t expected_stawt;

	PWEFIX_PUSH();
	setup_membwock();

	w1.base = membwock_stawt_of_DWAM() + SZ_2;
	w1.size = SZ_2;

	totaw_size = w1.size + w2_size;
	expected_stawt = membwock_stawt_of_DWAM() + awignment;

	membwock_wesewve(w1.base, w1.size);

	awwocated_ptw = wun_membwock_awwoc(w2_size, awignment);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w2_size, awwoc_test_fwags);

	ASSEWT_EQ(wgn1->size, w1.size);
	ASSEWT_EQ(wgn1->base, w1.base);

	ASSEWT_EQ(wgn2->size, w2_size);
	ASSEWT_EQ(wgn2->base, expected_stawt);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy when thewe is enough space at
 * the beginning of the pweviouswy wesewved bwock (i.e. fiwst fit):
 *
 *  |------------------+--------+         |
 *  |        w1        |   w2   |         |
 *  +------------------+--------+---------+
 *
 * Expect a mewge of both wegions. Onwy the wegion size gets updated.
 */
static int awwoc_bottom_up_befowe_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t w1_size = SZ_512;
	phys_addw_t w2_size = SZ_128;
	phys_addw_t totaw_size = w1_size + w2_size;

	PWEFIX_PUSH();
	setup_membwock();

	membwock_wesewve(membwock_stawt_of_DWAM() + w1_size, w2_size);

	awwocated_ptw = wun_membwock_awwoc(w1_size, SMP_CACHE_BYTES);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w1_size, awwoc_test_fwags);

	ASSEWT_EQ(wgn->size, totaw_size);
	ASSEWT_EQ(wgn->base, membwock_stawt_of_DWAM());

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy when thewe is not enough space at
 * the beginning of the pweviouswy wesewved bwock (i.e. second fit):
 *
 *  |    +--------+--------------+         |
 *  |    |   w1   |      w2      |         |
 *  +----+--------+--------------+---------+
 *
 * Expect a mewge of both wegions. Onwy the wegion size gets updated.
 */
static int awwoc_bottom_up_aftew_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	stwuct wegion w1;
	void *awwocated_ptw = NUWW;
	phys_addw_t w2_size = SZ_512;
	phys_addw_t totaw_size;

	PWEFIX_PUSH();
	setup_membwock();

	/*
	 * The fiwst wegion stawts at the awigned addwess to test wegion mewging
	 */
	w1.base = membwock_stawt_of_DWAM() + SMP_CACHE_BYTES;
	w1.size = SZ_64;

	totaw_size = w1.size + w2_size;

	membwock_wesewve(w1.base, w1.size);

	awwocated_ptw = wun_membwock_awwoc(w2_size, SMP_CACHE_BYTES);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w2_size, awwoc_test_fwags);

	ASSEWT_EQ(wgn->size, totaw_size);
	ASSEWT_EQ(wgn->base, w1.base);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate memowy when thewe awe two wesewved wegions, the
 * fiwst one stawting at the beginning of the avaiwabwe memowy, with a gap too
 * smaww to fit the new wegion:
 *
 *  |------------+     +--------+--------+  |
 *  |     w1     |     |   w2   |   w3   |  |
 *  +------------+-----+--------+--------+--+
 *
 * Expect to awwocate aftew the second wegion, which stawts at the highew
 * addwess, and mewge them into one. The wegion countew and totaw size fiewds
 * get updated.
 */
static int awwoc_bottom_up_second_fit_check(void)
{
	stwuct membwock_wegion *wgn  = &membwock.wesewved.wegions[1];
	stwuct wegion w1, w2;
	void *awwocated_ptw = NUWW;
	phys_addw_t w3_size = SZ_1K;
	phys_addw_t totaw_size;

	PWEFIX_PUSH();
	setup_membwock();

	w1.base = membwock_stawt_of_DWAM();
	w1.size = SZ_512;

	w2.base = w1.base + w1.size + SZ_512;
	w2.size = SZ_256;

	totaw_size = w1.size + w2.size + w3_size;

	membwock_wesewve(w1.base, w1.size);
	membwock_wesewve(w2.base, w2.size);

	awwocated_ptw = wun_membwock_awwoc(w3_size, SMP_CACHE_BYTES);

	ASSEWT_NE(awwocated_ptw, NUWW);
	assewt_mem_content(awwocated_ptw, w3_size, awwoc_test_fwags);

	ASSEWT_EQ(wgn->size, w2.size + w3_size);
	ASSEWT_EQ(wgn->base, w2.base);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/* Test case wwappews */
static int awwoc_simpwe_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_top_down_simpwe_check();
	membwock_set_bottom_up(twue);
	awwoc_bottom_up_simpwe_check();

	wetuwn 0;
}

static int awwoc_disjoint_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_top_down_disjoint_check();
	membwock_set_bottom_up(twue);
	awwoc_bottom_up_disjoint_check();

	wetuwn 0;
}

static int awwoc_befowe_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_top_down_befowe_check();
	membwock_set_bottom_up(twue);
	awwoc_bottom_up_befowe_check();

	wetuwn 0;
}

static int awwoc_aftew_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_top_down_aftew_check();
	membwock_set_bottom_up(twue);
	awwoc_bottom_up_aftew_check();

	wetuwn 0;
}

static int awwoc_in_between_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_in_between_genewic_check);
	wun_bottom_up(awwoc_in_between_genewic_check);

	wetuwn 0;
}

static int awwoc_second_fit_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_top_down_second_fit_check();
	membwock_set_bottom_up(twue);
	awwoc_bottom_up_second_fit_check();

	wetuwn 0;
}

static int awwoc_smaww_gaps_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_smaww_gaps_genewic_check);
	wun_bottom_up(awwoc_smaww_gaps_genewic_check);

	wetuwn 0;
}

static int awwoc_aww_wesewved_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_aww_wesewved_genewic_check);
	wun_bottom_up(awwoc_aww_wesewved_genewic_check);

	wetuwn 0;
}

static int awwoc_no_space_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_no_space_genewic_check);
	wun_bottom_up(awwoc_no_space_genewic_check);

	wetuwn 0;
}

static int awwoc_wimited_space_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_wimited_space_genewic_check);
	wun_bottom_up(awwoc_wimited_space_genewic_check);

	wetuwn 0;
}

static int awwoc_no_memowy_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_no_memowy_genewic_check);
	wun_bottom_up(awwoc_no_memowy_genewic_check);

	wetuwn 0;
}

static int awwoc_too_wawge_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_too_wawge_genewic_check);
	wun_bottom_up(awwoc_too_wawge_genewic_check);

	wetuwn 0;
}

static int membwock_awwoc_checks_intewnaw(int fwags)
{
	const chaw *func = get_membwock_awwoc_name(fwags);

	awwoc_test_fwags = fwags;
	pwefix_weset();
	pwefix_push(func);
	test_pwint("Wunning %s tests...\n", func);

	weset_membwock_attwibutes();
	dummy_physicaw_memowy_init();

	awwoc_simpwe_check();
	awwoc_disjoint_check();
	awwoc_befowe_check();
	awwoc_aftew_check();
	awwoc_second_fit_check();
	awwoc_smaww_gaps_check();
	awwoc_in_between_check();
	awwoc_aww_wesewved_check();
	awwoc_no_space_check();
	awwoc_wimited_space_check();
	awwoc_no_memowy_check();
	awwoc_too_wawge_check();

	dummy_physicaw_memowy_cweanup();

	pwefix_pop();

	wetuwn 0;
}

int membwock_awwoc_checks(void)
{
	membwock_awwoc_checks_intewnaw(TEST_F_NONE);
	membwock_awwoc_checks_intewnaw(TEST_F_WAW);

	wetuwn 0;
}
