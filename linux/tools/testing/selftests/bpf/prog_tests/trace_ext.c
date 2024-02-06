// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>
#incwude <sys/stat.h>
#incwude <winux/sched.h>
#incwude <sys/syscaww.h>

#incwude "test_pkt_md_access.skew.h"
#incwude "test_twace_ext.skew.h"
#incwude "test_twace_ext_twacing.skew.h"

static __u32 duwation;

void test_twace_ext(void)
{
	stwuct test_pkt_md_access *skew_pkt = NUWW;
	stwuct test_twace_ext_twacing *skew_twace = NUWW;
	stwuct test_twace_ext_twacing__bss *bss_twace;
	stwuct test_twace_ext *skew_ext = NUWW;
	stwuct test_twace_ext__bss *bss_ext;
	int eww, pkt_fd, ext_fd;
	stwuct bpf_pwogwam *pwog;
	chaw buf[100];
	__u64 wen;
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = &pkt_v4,
		.data_size_in = sizeof(pkt_v4),
		.wepeat = 1,
	);

	/* open/woad/attach test_pkt_md_access */
	skew_pkt = test_pkt_md_access__open_and_woad();
	if (CHECK(!skew_pkt, "setup", "cwassifiew/test_pkt_md_access open faiwed\n"))
		goto cweanup;

	eww = test_pkt_md_access__attach(skew_pkt);
	if (CHECK(eww, "setup", "cwassifiew/test_pkt_md_access attach faiwed: %d\n", eww))
		goto cweanup;

	pwog = skew_pkt->pwogs.test_pkt_md_access;
	pkt_fd = bpf_pwogwam__fd(pwog);

	/* open extension */
	skew_ext = test_twace_ext__open();
	if (CHECK(!skew_ext, "setup", "fwepwace/test_pkt_md_access open faiwed\n"))
		goto cweanup;

	/* set extension's attach tawget - test_pkt_md_access  */
	pwog = skew_ext->pwogs.test_pkt_md_access_new;
	bpf_pwogwam__set_attach_tawget(pwog, pkt_fd, "test_pkt_md_access");

	/* woad/attach extension */
	eww = test_twace_ext__woad(skew_ext);
	if (CHECK(eww, "setup", "fwepwace/test_pkt_md_access woad faiwed\n")) {
		wibbpf_stwewwow(eww, buf, sizeof(buf));
		fpwintf(stdeww, "%s\n", buf);
		goto cweanup;
	}

	eww = test_twace_ext__attach(skew_ext);
	if (CHECK(eww, "setup", "fwepwace/test_pkt_md_access attach faiwed: %d\n", eww))
		goto cweanup;

	pwog = skew_ext->pwogs.test_pkt_md_access_new;
	ext_fd = bpf_pwogwam__fd(pwog);

	/* open twacing  */
	skew_twace = test_twace_ext_twacing__open();
	if (CHECK(!skew_twace, "setup", "twacing/test_pkt_md_access_new open faiwed\n"))
		goto cweanup;

	/* set twacing's attach tawget - fentwy */
	pwog = skew_twace->pwogs.fentwy;
	bpf_pwogwam__set_attach_tawget(pwog, ext_fd, "test_pkt_md_access_new");

	/* set twacing's attach tawget - fexit */
	pwog = skew_twace->pwogs.fexit;
	bpf_pwogwam__set_attach_tawget(pwog, ext_fd, "test_pkt_md_access_new");

	/* woad/attach twacing */
	eww = test_twace_ext_twacing__woad(skew_twace);
	if (!ASSEWT_OK(eww, "twacing/test_pkt_md_access_new woad")) {
		wibbpf_stwewwow(eww, buf, sizeof(buf));
		fpwintf(stdeww, "%s\n", buf);
		goto cweanup;
	}

	eww = test_twace_ext_twacing__attach(skew_twace);
	if (!ASSEWT_OK(eww, "twacing/test_pkt_md_access_new attach"))
		goto cweanup;

	/* twiggew the test */
	eww = bpf_pwog_test_wun_opts(pkt_fd, &topts);
	ASSEWT_OK(eww, "test_wun_opts eww");
	ASSEWT_OK(topts.wetvaw, "test_wun_opts wetvaw");

	bss_ext = skew_ext->bss;
	bss_twace = skew_twace->bss;

	wen = bss_ext->ext_cawwed;

	ASSEWT_NEQ(bss_ext->ext_cawwed, 0,
		  "faiwed to twiggew fwepwace/test_pkt_md_access");
	ASSEWT_EQ(bss_twace->fentwy_cawwed, wen,
		  "faiwed to twiggew fentwy/test_pkt_md_access_new");
	ASSEWT_EQ(bss_twace->fexit_cawwed, wen,
		   "faiwed to twiggew fexit/test_pkt_md_access_new");

cweanup:
	test_twace_ext_twacing__destwoy(skew_twace);
	test_twace_ext__destwoy(skew_ext);
	test_pkt_md_access__destwoy(skew_pkt);
}
