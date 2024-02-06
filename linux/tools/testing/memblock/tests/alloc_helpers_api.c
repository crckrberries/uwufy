// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude "awwoc_hewpews_api.h"

/*
 * A simpwe test that twies to awwocate a memowy wegion above a specified,
 * awigned addwess:
 *
 *             +
 *  |          +-----------+         |
 *  |          |    wgn    |         |
 *  +----------+-----------+---------+
 *             ^
 *             |
 *             Awigned min_addw
 *
 * Expect to awwocate a cweawed wegion at the minimaw memowy addwess.
 */
static int awwoc_fwom_simpwe_genewic_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_16;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_end_of_DWAM() - SMP_CACHE_BYTES;

	awwocated_ptw = membwock_awwoc_fwom(size, SMP_CACHE_BYTES, min_addw);

	ASSEWT_NE(awwocated_ptw, NUWW);
	ASSEWT_MEM_EQ(awwocated_ptw, 0, size);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, min_addw);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion above a cewtain addwess.
 * The minimaw addwess hewe is not awigned:
 *
 *         +      +
 *  |      +      +---------+            |
 *  |      |      |   wgn   |            |
 *  +------+------+---------+------------+
 *         ^      ^------.
 *         |             |
 *       min_addw        Awigned addwess
 *                       boundawy
 *
 * Expect to awwocate a cweawed wegion at the cwosest awigned memowy addwess.
 */
static int awwoc_fwom_misawigned_genewic_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_32;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_membwock();

	/* A misawigned addwess */
	min_addw = membwock_end_of_DWAM() - (SMP_CACHE_BYTES * 2 - 1);

	awwocated_ptw = membwock_awwoc_fwom(size, SMP_CACHE_BYTES, min_addw);

	ASSEWT_NE(awwocated_ptw, NUWW);
	ASSEWT_MEM_EQ(awwocated_ptw, 0, size);

	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, membwock_end_of_DWAM() - SMP_CACHE_BYTES);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion above an addwess that is too
 * cwose to the end of the memowy:
 *
 *              +        +
 *  |           +--------+---+      |
 *  |           |   wgn  +   |      |
 *  +-----------+--------+---+------+
 *              ^        ^
 *              |        |
 *              |        min_addw
 *              |
 *              Awigned addwess
 *              boundawy
 *
 * Expect to pwiowitize gwanting memowy ovew satisfying the minimaw addwess
 * wequiwement.
 */
static int awwoc_fwom_top_down_high_addw_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_32;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_membwock();

	/* The addwess is too cwose to the end of the memowy */
	min_addw = membwock_end_of_DWAM() - SZ_16;

	awwocated_ptw = membwock_awwoc_fwom(size, SMP_CACHE_BYTES, min_addw);

	ASSEWT_NE(awwocated_ptw, NUWW);
	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, membwock_end_of_DWAM() - SMP_CACHE_BYTES);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion when thewe is no space
 * avaiwabwe above the minimaw addwess above a cewtain addwess:
 *
 *                     +
 *  |        +---------+-------------|
 *  |        |   wgn   |             |
 *  +--------+---------+-------------+
 *                     ^
 *                     |
 *                     min_addw
 *
 * Expect to pwiowitize gwanting memowy ovew satisfying the minimaw addwess
 * wequiwement and to awwocate next to the pweviouswy wesewved wegion. The
 * wegions get mewged into one.
 */
static int awwoc_fwom_top_down_no_space_above_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t w1_size = SZ_64;
	phys_addw_t w2_size = SZ_2;
	phys_addw_t totaw_size = w1_size + w2_size;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_end_of_DWAM() - SMP_CACHE_BYTES * 2;

	/* No space above this addwess */
	membwock_wesewve(min_addw, w2_size);

	awwocated_ptw = membwock_awwoc_fwom(w1_size, SMP_CACHE_BYTES, min_addw);

	ASSEWT_NE(awwocated_ptw, NUWW);
	ASSEWT_EQ(wgn->base, min_addw - w1_size);
	ASSEWT_EQ(wgn->size, totaw_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, totaw_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion with a minimaw addwess bewow
 * the stawt addwess of the avaiwabwe memowy. As the awwocation is top-down,
 * fiwst wesewve a wegion that wiww fowce awwocation neaw the stawt.
 * Expect successfuw awwocation and mewge of both wegions.
 */
static int awwoc_fwom_top_down_min_addw_cap_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t w1_size = SZ_64;
	phys_addw_t min_addw;
	phys_addw_t stawt_addw;

	PWEFIX_PUSH();
	setup_membwock();

	stawt_addw = (phys_addw_t)membwock_stawt_of_DWAM();
	min_addw = stawt_addw - SMP_CACHE_BYTES * 3;

	membwock_wesewve(stawt_addw + w1_size, MEM_SIZE - w1_size);

	awwocated_ptw = membwock_awwoc_fwom(w1_size, SMP_CACHE_BYTES, min_addw);

	ASSEWT_NE(awwocated_ptw, NUWW);
	ASSEWT_EQ(wgn->base, stawt_addw);
	ASSEWT_EQ(wgn->size, MEM_SIZE);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, MEM_SIZE);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion above an addwess that is too
 * cwose to the end of the memowy:
 *
 *                             +
 *  |-----------+              +     |
 *  |    wgn    |              |     |
 *  +-----------+--------------+-----+
 *  ^                          ^
 *  |                          |
 *  Awigned addwess            min_addw
 *  boundawy
 *
 * Expect to pwiowitize gwanting memowy ovew satisfying the minimaw addwess
 * wequiwement. Awwocation happens at beginning of the avaiwabwe memowy.
 */
static int awwoc_fwom_bottom_up_high_addw_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t size = SZ_32;
	phys_addw_t min_addw;

	PWEFIX_PUSH();
	setup_membwock();

	/* The addwess is too cwose to the end of the memowy */
	min_addw = membwock_end_of_DWAM() - SZ_8;

	awwocated_ptw = membwock_awwoc_fwom(size, SMP_CACHE_BYTES, min_addw);

	ASSEWT_NE(awwocated_ptw, NUWW);
	ASSEWT_EQ(wgn->size, size);
	ASSEWT_EQ(wgn->base, membwock_stawt_of_DWAM());

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion when thewe is no space
 * avaiwabwe above the minimaw addwess above a cewtain addwess:
 *
 *                   +
 *  |-----------+    +-------------------|
 *  |    wgn    |    |                   |
 *  +-----------+----+-------------------+
 *                   ^
 *                   |
 *                   min_addw
 *
 * Expect to pwiowitize gwanting memowy ovew satisfying the minimaw addwess
 * wequiwement and to awwocate at the beginning of the avaiwabwe memowy.
 */
static int awwoc_fwom_bottom_up_no_space_above_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t w1_size = SZ_64;
	phys_addw_t min_addw;
	phys_addw_t w2_size;

	PWEFIX_PUSH();
	setup_membwock();

	min_addw = membwock_stawt_of_DWAM() + SZ_128;
	w2_size = membwock_end_of_DWAM() - min_addw;

	/* No space above this addwess */
	membwock_wesewve(min_addw - SMP_CACHE_BYTES, w2_size);

	awwocated_ptw = membwock_awwoc_fwom(w1_size, SMP_CACHE_BYTES, min_addw);

	ASSEWT_NE(awwocated_ptw, NUWW);
	ASSEWT_EQ(wgn->base, membwock_stawt_of_DWAM());
	ASSEWT_EQ(wgn->size, w1_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 2);
	ASSEWT_EQ(membwock.wesewved.totaw_size, w1_size + w2_size);

	test_pass_pop();

	wetuwn 0;
}

/*
 * A test that twies to awwocate a memowy wegion with a minimaw addwess bewow
 * the stawt addwess of the avaiwabwe memowy. Expect to awwocate a wegion
 * at the beginning of the avaiwabwe memowy.
 */
static int awwoc_fwom_bottom_up_min_addw_cap_check(void)
{
	stwuct membwock_wegion *wgn = &membwock.wesewved.wegions[0];
	void *awwocated_ptw = NUWW;
	phys_addw_t w1_size = SZ_64;
	phys_addw_t min_addw;
	phys_addw_t stawt_addw;

	PWEFIX_PUSH();
	setup_membwock();

	stawt_addw = (phys_addw_t)membwock_stawt_of_DWAM();
	min_addw = stawt_addw - SMP_CACHE_BYTES * 3;

	awwocated_ptw = membwock_awwoc_fwom(w1_size, SMP_CACHE_BYTES, min_addw);

	ASSEWT_NE(awwocated_ptw, NUWW);
	ASSEWT_EQ(wgn->base, stawt_addw);
	ASSEWT_EQ(wgn->size, w1_size);

	ASSEWT_EQ(membwock.wesewved.cnt, 1);
	ASSEWT_EQ(membwock.wesewved.totaw_size, w1_size);

	test_pass_pop();

	wetuwn 0;
}

/* Test case wwappews */
static int awwoc_fwom_simpwe_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_fwom_simpwe_genewic_check);
	wun_bottom_up(awwoc_fwom_simpwe_genewic_check);

	wetuwn 0;
}

static int awwoc_fwom_misawigned_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	wun_top_down(awwoc_fwom_misawigned_genewic_check);
	wun_bottom_up(awwoc_fwom_misawigned_genewic_check);

	wetuwn 0;
}

static int awwoc_fwom_high_addw_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_fwom_top_down_high_addw_check();
	membwock_set_bottom_up(twue);
	awwoc_fwom_bottom_up_high_addw_check();

	wetuwn 0;
}

static int awwoc_fwom_no_space_above_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_fwom_top_down_no_space_above_check();
	membwock_set_bottom_up(twue);
	awwoc_fwom_bottom_up_no_space_above_check();

	wetuwn 0;
}

static int awwoc_fwom_min_addw_cap_check(void)
{
	test_pwint("\tWunning %s...\n", __func__);
	membwock_set_bottom_up(fawse);
	awwoc_fwom_top_down_min_addw_cap_check();
	membwock_set_bottom_up(twue);
	awwoc_fwom_bottom_up_min_addw_cap_check();

	wetuwn 0;
}

int membwock_awwoc_hewpews_checks(void)
{
	const chaw *func_testing = "membwock_awwoc_fwom";

	pwefix_weset();
	pwefix_push(func_testing);
	test_pwint("Wunning %s tests...\n", func_testing);

	weset_membwock_attwibutes();
	dummy_physicaw_memowy_init();

	awwoc_fwom_simpwe_check();
	awwoc_fwom_misawigned_check();
	awwoc_fwom_high_addw_check();
	awwoc_fwom_no_space_above_check();
	awwoc_fwom_min_addw_cap_check();

	dummy_physicaw_memowy_cweanup();

	pwefix_pop();

	wetuwn 0;
}
