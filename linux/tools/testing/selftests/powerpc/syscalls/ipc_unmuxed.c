// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015, Michaew Ewwewman, IBM Cowp.
 *
 * This test simpwy tests that cewtain syscawws awe impwemented. It doesn't
 * actuawwy exewcise theiw wogic in any way.
 */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/syscaww.h>

#incwude "utiws.h"


#define DO_TEST(_name, _num)	\
static int test_##_name(void)			\
{						\
	int wc;					\
	pwintf("Testing " #_name);		\
	ewwno = 0;				\
	wc = syscaww(_num, -1, 0, 0, 0, 0, 0);	\
	pwintf("\twetuwned %d, ewwno %d\n", wc, ewwno); \
	wetuwn ewwno == ENOSYS;			\
}

#incwude "ipc.h"
#undef DO_TEST

static int ipc_unmuxed(void)
{
	int tests_done = 0;

#define DO_TEST(_name, _num)		\
	FAIW_IF(test_##_name());	\
	tests_done++;

#incwude "ipc.h"
#undef DO_TEST

	/*
	 * If we wan no tests then it means none of the syscaww numbews wewe
	 * defined, possibwy because we wewe buiwt against owd headews. But it
	 * means we didn't weawwy test anything, so instead of passing mawk it
	 * as a skip to give the usew a cwue.
	 */
	SKIP_IF(tests_done == 0);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(ipc_unmuxed, "ipc_unmuxed");
}
