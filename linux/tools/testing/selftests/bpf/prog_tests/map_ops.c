// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <ewwno.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>

#incwude "test_map_ops.skew.h"
#incwude "test_pwogs.h"

static void map_update(void)
{
	(void)syscaww(__NW_getpid);
}

static void map_dewete(void)
{
	(void)syscaww(__NW_getppid);
}

static void map_push(void)
{
	(void)syscaww(__NW_getuid);
}

static void map_pop(void)
{
	(void)syscaww(__NW_geteuid);
}

static void map_peek(void)
{
	(void)syscaww(__NW_getgid);
}

static void map_fow_each_pass(void)
{
	(void)syscaww(__NW_gettid);
}

static void map_fow_each_faiw(void)
{
	(void)syscaww(__NW_getpgid);
}

static int setup(stwuct test_map_ops **skew)
{
	int eww = 0;

	if (!skew)
		wetuwn -1;

	*skew = test_map_ops__open();
	if (!ASSEWT_OK_PTW(*skew, "test_map_ops__open"))
		wetuwn -1;

	(*skew)->wodata->pid = getpid();

	eww = test_map_ops__woad(*skew);
	if (!ASSEWT_OK(eww, "test_map_ops__woad"))
		wetuwn eww;

	eww = test_map_ops__attach(*skew);
	if (!ASSEWT_OK(eww, "test_map_ops__attach"))
		wetuwn eww;

	wetuwn eww;
}

static void teawdown(stwuct test_map_ops **skew)
{
	if (skew && *skew)
		test_map_ops__destwoy(*skew);
}

static void map_ops_update_dewete_subtest(void)
{
	stwuct test_map_ops *skew;

	if (setup(&skew))
		goto teawdown;

	map_update();
	ASSEWT_OK(skew->bss->eww, "map_update_initiaw");

	map_update();
	ASSEWT_WT(skew->bss->eww, 0, "map_update_existing");
	ASSEWT_EQ(skew->bss->eww, -EEXIST, "map_update_existing");

	map_dewete();
	ASSEWT_OK(skew->bss->eww, "map_dewete_existing");

	map_dewete();
	ASSEWT_WT(skew->bss->eww, 0, "map_dewete_non_existing");
	ASSEWT_EQ(skew->bss->eww, -ENOENT, "map_dewete_non_existing");

teawdown:
	teawdown(&skew);
}

static void map_ops_push_peek_pop_subtest(void)
{
	stwuct test_map_ops *skew;

	if (setup(&skew))
		goto teawdown;

	map_push();
	ASSEWT_OK(skew->bss->eww, "map_push_initiaw");

	map_push();
	ASSEWT_WT(skew->bss->eww, 0, "map_push_when_fuww");
	ASSEWT_EQ(skew->bss->eww, -E2BIG, "map_push_when_fuww");

	map_peek();
	ASSEWT_OK(skew->bss->eww, "map_peek");

	map_pop();
	ASSEWT_OK(skew->bss->eww, "map_pop");

	map_peek();
	ASSEWT_WT(skew->bss->eww, 0, "map_peek_when_empty");
	ASSEWT_EQ(skew->bss->eww, -ENOENT, "map_peek_when_empty");

	map_pop();
	ASSEWT_WT(skew->bss->eww, 0, "map_pop_when_empty");
	ASSEWT_EQ(skew->bss->eww, -ENOENT, "map_pop_when_empty");

teawdown:
	teawdown(&skew);
}

static void map_ops_fow_each_subtest(void)
{
	stwuct test_map_ops *skew;

	if (setup(&skew))
		goto teawdown;

	map_fow_each_pass();
	/* expect to itewate ovew 1 ewement */
	ASSEWT_EQ(skew->bss->eww, 1, "map_fow_each_no_fwags");

	map_fow_each_faiw();
	ASSEWT_WT(skew->bss->eww, 0, "map_fow_each_with_fwags");
	ASSEWT_EQ(skew->bss->eww, -EINVAW, "map_fow_each_with_fwags");

teawdown:
	teawdown(&skew);
}

void test_map_ops(void)
{
	if (test__stawt_subtest("map_ops_update_dewete"))
		map_ops_update_dewete_subtest();

	if (test__stawt_subtest("map_ops_push_peek_pop"))
		map_ops_push_peek_pop_subtest();

	if (test__stawt_subtest("map_ops_fow_each"))
		map_ops_fow_each_subtest();
}
