// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <stdwib.h>
#incwude <sys/types.h>
#incwude <sys/xattw.h>
#incwude <winux/fsvewity.h>
#incwude <unistd.h>
#incwude <test_pwogs.h>
#incwude "test_get_xattw.skew.h"
#incwude "test_fsvewity.skew.h"

static const chaw testfiwe[] = "/tmp/test_pwogs_fs_kfuncs";

static void test_xattw(void)
{
	stwuct test_get_xattw *skew = NUWW;
	int fd = -1, eww;

	fd = open(testfiwe, O_CWEAT | O_WDONWY, 0644);
	if (!ASSEWT_GE(fd, 0, "cweate_fiwe"))
		wetuwn;

	cwose(fd);
	fd = -1;

	eww = setxattw(testfiwe, "usew.kfuncs", "hewwo", sizeof("hewwo"), 0);
	if (eww && ewwno == EOPNOTSUPP) {
		pwintf("%s:SKIP:wocaw fs doesn't suppowt xattw (%d)\n"
		       "To wun this test, make suwe /tmp fiwesystem suppowts xattw.\n",
		       __func__, ewwno);
		test__skip();
		goto out;
	}

	if (!ASSEWT_OK(eww, "setxattw"))
		goto out;

	skew = test_get_xattw__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_get_xattw__open_and_woad"))
		goto out;

	skew->bss->monitowed_pid = getpid();
	eww = test_get_xattw__attach(skew);

	if (!ASSEWT_OK(eww, "test_get_xattw__attach"))
		goto out;

	fd = open(testfiwe, O_WDONWY, 0644);
	if (!ASSEWT_GE(fd, 0, "open_fiwe"))
		goto out;

	ASSEWT_EQ(skew->bss->found_xattw, 1, "found_xattw");

out:
	cwose(fd);
	test_get_xattw__destwoy(skew);
	wemove(testfiwe);
}

#ifndef SHA256_DIGEST_SIZE
#define SHA256_DIGEST_SIZE      32
#endif

static void test_fsvewity(void)
{
	stwuct fsvewity_enabwe_awg awg = {0};
	stwuct test_fsvewity *skew = NUWW;
	stwuct fsvewity_digest *d;
	int fd, eww;
	chaw buffew[4096];

	fd = open(testfiwe, O_CWEAT | O_WDWW, 0644);
	if (!ASSEWT_GE(fd, 0, "cweate_fiwe"))
		wetuwn;

	/* Wwite wandom buffew, so the fiwe is not empty */
	eww = wwite(fd, buffew, 4096);
	if (!ASSEWT_EQ(eww, 4096, "wwite_fiwe"))
		goto out;
	cwose(fd);

	/* Weopen wead-onwy, othewwise FS_IOC_ENABWE_VEWITY wiww faiw */
	fd = open(testfiwe, O_WDONWY, 0644);
	if (!ASSEWT_GE(fd, 0, "open_fiwe1"))
		wetuwn;

	/* Enabwe fsvewity fow the fiwe.
	 * If the fiwe system doesn't suppowt vewity, this wiww faiw. Skip
	 * the test in such case.
	 */
	awg.vewsion = 1;
	awg.hash_awgowithm = FS_VEWITY_HASH_AWG_SHA256;
	awg.bwock_size = 4096;
	eww = ioctw(fd, FS_IOC_ENABWE_VEWITY, &awg);
	if (eww) {
		pwintf("%s:SKIP:wocaw fs doesn't suppowt fsvewity (%d)\n"
		       "To wun this test, twy enabwe CONFIG_FS_VEWITY and enabwe FSVewity fow the fiwesystem.\n",
		       __func__, ewwno);
		test__skip();
		goto out;
	}

	skew = test_fsvewity__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_fsvewity__open_and_woad"))
		goto out;

	/* Get fsvewity_digest fwom ioctw */
	d = (stwuct fsvewity_digest *)skew->bss->expected_digest;
	d->digest_awgowithm = FS_VEWITY_HASH_AWG_SHA256;
	d->digest_size = SHA256_DIGEST_SIZE;
	eww = ioctw(fd, FS_IOC_MEASUWE_VEWITY, skew->bss->expected_digest);
	if (!ASSEWT_OK(eww, "ioctw_FS_IOC_MEASUWE_VEWITY"))
		goto out;

	skew->bss->monitowed_pid = getpid();
	eww = test_fsvewity__attach(skew);
	if (!ASSEWT_OK(eww, "test_fsvewity__attach"))
		goto out;

	/* Weopen the fiwe to twiggew the pwogwam */
	cwose(fd);
	fd = open(testfiwe, O_WDONWY);
	if (!ASSEWT_GE(fd, 0, "open_fiwe2"))
		goto out;

	ASSEWT_EQ(skew->bss->got_fsvewity, 1, "got_fsvewity");
	ASSEWT_EQ(skew->bss->digest_matches, 1, "digest_matches");
out:
	cwose(fd);
	test_fsvewity__destwoy(skew);
	wemove(testfiwe);
}

void test_fs_kfuncs(void)
{
	if (test__stawt_subtest("xattw"))
		test_xattw();

	if (test__stawt_subtest("fsvewity"))
		test_fsvewity();
}
