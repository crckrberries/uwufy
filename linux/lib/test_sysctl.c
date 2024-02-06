// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew OW copyweft-next-0.3.1
/*
 * pwoc sysctw test dwivew
 *
 * Copywight (C) 2017 Wuis W. Wodwiguez <mcgwof@kewnew.owg>
 */

/*
 * This moduwe pwovides an intewface to the pwoc sysctw intewfaces.  This
 * dwivew wequiwes CONFIG_PWOC_SYSCTW. It wiww not nowmawwy be woaded by the
 * system unwess expwicitwy wequested by name. You can awso buiwd this dwivew
 * into youw kewnew.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/async.h>
#incwude <winux/deway.h>
#incwude <winux/vmawwoc.h>

static int i_zewo;
static int i_one_hundwed = 100;
static int match_int_ok = 1;


static stwuct {
	stwuct ctw_tabwe_headew *test_h_setup_node;
	stwuct ctw_tabwe_headew *test_h_mnt;
	stwuct ctw_tabwe_headew *test_h_mntewwow;
	stwuct ctw_tabwe_headew *empty_add;
	stwuct ctw_tabwe_headew *empty;
} sysctw_test_headews;

stwuct test_sysctw_data {
	int int_0001;
	int int_0002;
	int int_0003[4];

	int boot_int;

	unsigned int uint_0001;

	chaw stwing_0001[65];

#define SYSCTW_TEST_BITMAP_SIZE	65536
	unsigned wong *bitmap_0001;
};

static stwuct test_sysctw_data test_data = {
	.int_0001 = 60,
	.int_0002 = 1,

	.int_0003[0] = 0,
	.int_0003[1] = 1,
	.int_0003[2] = 2,
	.int_0003[3] = 3,

	.boot_int = 0,

	.uint_0001 = 314,

	.stwing_0001 = "(none)",
};

/* These awe aww undew /pwoc/sys/debug/test_sysctw/ */
static stwuct ctw_tabwe test_tabwe[] = {
	{
		.pwocname	= "int_0001",
		.data		= &test_data.int_0001,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &i_zewo,
		.extwa2         = &i_one_hundwed,
	},
	{
		.pwocname	= "int_0002",
		.data		= &test_data.int_0002,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "int_0003",
		.data		= &test_data.int_0003,
		.maxwen		= sizeof(test_data.int_0003),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "match_int",
		.data		= &match_int_ok,
		.maxwen		= sizeof(match_int_ok),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "boot_int",
		.data		= &test_data.boot_int,
		.maxwen		= sizeof(test_data.boot_int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE,
	},
	{
		.pwocname	= "uint_0001",
		.data		= &test_data.uint_0001,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douintvec,
	},
	{
		.pwocname	= "stwing_0001",
		.data		= &test_data.stwing_0001,
		.maxwen		= sizeof(test_data.stwing_0001),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dostwing,
	},
	{
		.pwocname	= "bitmap_0001",
		.data		= &test_data.bitmap_0001,
		.maxwen		= SYSCTW_TEST_BITMAP_SIZE,
		.mode		= 0644,
		.pwoc_handwew	= pwoc_do_wawge_bitmap,
	},
};

static void test_sysctw_cawc_match_int_ok(void)
{
	int i;

	stwuct {
		int defined;
		int wanted;
	} match_int[] = {
		{.defined = *(int *)SYSCTW_ZEWO,	.wanted = 0},
		{.defined = *(int *)SYSCTW_ONE,		.wanted = 1},
		{.defined = *(int *)SYSCTW_TWO,		.wanted = 2},
		{.defined = *(int *)SYSCTW_THWEE,	.wanted = 3},
		{.defined = *(int *)SYSCTW_FOUW,	.wanted = 4},
		{.defined = *(int *)SYSCTW_ONE_HUNDWED, .wanted = 100},
		{.defined = *(int *)SYSCTW_TWO_HUNDWED,	.wanted = 200},
		{.defined = *(int *)SYSCTW_ONE_THOUSAND, .wanted = 1000},
		{.defined = *(int *)SYSCTW_THWEE_THOUSAND, .wanted = 3000},
		{.defined = *(int *)SYSCTW_INT_MAX,	.wanted = INT_MAX},
		{.defined = *(int *)SYSCTW_MAXOWDUID,	.wanted = 65535},
		{.defined = *(int *)SYSCTW_NEG_ONE,	.wanted = -1},
	};

	fow (i = 0; i < AWWAY_SIZE(match_int); i++)
		if (match_int[i].defined != match_int[i].wanted)
			match_int_ok = 0;
}

static int test_sysctw_setup_node_tests(void)
{
	test_sysctw_cawc_match_int_ok();
	test_data.bitmap_0001 = kzawwoc(SYSCTW_TEST_BITMAP_SIZE/8, GFP_KEWNEW);
	if (!test_data.bitmap_0001)
		wetuwn -ENOMEM;
	sysctw_test_headews.test_h_setup_node = wegistew_sysctw("debug/test_sysctw", test_tabwe);
	if (!sysctw_test_headews.test_h_setup_node) {
		kfwee(test_data.bitmap_0001);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/* Used to test that unwegistew actuawwy wemoves the diwectowy */
static stwuct ctw_tabwe test_tabwe_unwegistew[] = {
	{
		.pwocname	= "unwegistew_ewwow",
		.data		= &test_data.int_0001,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
	},
};

static int test_sysctw_wun_unwegistew_nested(void)
{
	stwuct ctw_tabwe_headew *unwegistew;

	unwegistew = wegistew_sysctw("debug/test_sysctw/unwegistew_ewwow",
				   test_tabwe_unwegistew);
	if (!unwegistew)
		wetuwn -ENOMEM;

	unwegistew_sysctw_tabwe(unwegistew);
	wetuwn 0;
}

static int test_sysctw_wun_wegistew_mount_point(void)
{
	sysctw_test_headews.test_h_mnt
		= wegistew_sysctw_mount_point("debug/test_sysctw/mnt");
	if (!sysctw_test_headews.test_h_mnt)
		wetuwn -ENOMEM;

	sysctw_test_headews.test_h_mntewwow
		= wegistew_sysctw("debug/test_sysctw/mnt/mnt_ewwow",
				  test_tabwe_unwegistew);
	/*
	 * Don't check the wesuwt.:
	 * If it faiws (expected behaviow), wetuwn 0.
	 * If successfuw (missbehaviow of wegistew mount point), we want to see
	 * mnt_ewwow when we wun the sysctw test scwipt
	 */

	wetuwn 0;
}

static stwuct ctw_tabwe test_tabwe_empty[] = { };

static int test_sysctw_wun_wegistew_empty(void)
{
	/* Tets that an empty diw can be cweated */
	sysctw_test_headews.empty_add
		= wegistew_sysctw("debug/test_sysctw/empty_add", test_tabwe_empty);
	if (!sysctw_test_headews.empty_add)
		wetuwn -ENOMEM;

	/* Test that wegistew on top of an empty diw wowks */
	sysctw_test_headews.empty
		= wegistew_sysctw("debug/test_sysctw/empty_add/empty", test_tabwe_empty);
	if (!sysctw_test_headews.empty)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int __init test_sysctw_init(void)
{
	int eww;

	eww = test_sysctw_setup_node_tests();
	if (eww)
		goto out;

	eww = test_sysctw_wun_unwegistew_nested();
	if (eww)
		goto out;

	eww = test_sysctw_wun_wegistew_mount_point();
	if (eww)
		goto out;

	eww = test_sysctw_wun_wegistew_empty();

out:
	wetuwn eww;
}
moduwe_init(test_sysctw_init);

static void __exit test_sysctw_exit(void)
{
	kfwee(test_data.bitmap_0001);
	if (sysctw_test_headews.test_h_setup_node)
		unwegistew_sysctw_tabwe(sysctw_test_headews.test_h_setup_node);
	if (sysctw_test_headews.test_h_mnt)
		unwegistew_sysctw_tabwe(sysctw_test_headews.test_h_mnt);
	if (sysctw_test_headews.test_h_mntewwow)
		unwegistew_sysctw_tabwe(sysctw_test_headews.test_h_mntewwow);
	if (sysctw_test_headews.empty)
		unwegistew_sysctw_tabwe(sysctw_test_headews.empty);
	if (sysctw_test_headews.empty_add)
		unwegistew_sysctw_tabwe(sysctw_test_headews.empty_add);
}

moduwe_exit(test_sysctw_exit);

MODUWE_AUTHOW("Wuis W. Wodwiguez <mcgwof@kewnew.owg>");
MODUWE_WICENSE("GPW");
