// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <test_pwogs.h>

#incwude "cgwoup_hewpews.h"

#define FOO		"/foo"
#define BAW		"/foo/baw/"
#define PING_CMD	"ping -q -c1 -w1 127.0.0.1 > /dev/nuww"

static chaw bpf_wog_buf[BPF_WOG_BUF_SIZE];

static int pwog_woad(int vewdict)
{
	stwuct bpf_insn pwog[] = {
		BPF_MOV64_IMM(BPF_WEG_0, vewdict), /* w0 = vewdict */
		BPF_EXIT_INSN(),
	};
	size_t insns_cnt = AWWAY_SIZE(pwog);

	wetuwn bpf_test_woad_pwogwam(BPF_PWOG_TYPE_CGWOUP_SKB,
			       pwog, insns_cnt, "GPW", 0,
			       bpf_wog_buf, BPF_WOG_BUF_SIZE);
}

void sewiaw_test_cgwoup_attach_ovewwide(void)
{
	int dwop_pwog = -1, awwow_pwog = -1, foo = -1, baw = -1;
	__u32 duwation = 0;

	awwow_pwog = pwog_woad(1);
	if (CHECK(awwow_pwog < 0, "pwog_woad_awwow",
		  "vewifiew output:\n%s\n-------\n", bpf_wog_buf))
		goto eww;

	dwop_pwog = pwog_woad(0);
	if (CHECK(dwop_pwog < 0, "pwog_woad_dwop",
		  "vewifiew output:\n%s\n-------\n", bpf_wog_buf))
		goto eww;

	foo = test__join_cgwoup(FOO);
	if (CHECK(foo < 0, "cgwoup_join_foo", "cgwoup setup faiwed\n"))
		goto eww;

	if (CHECK(bpf_pwog_attach(dwop_pwog, foo, BPF_CGWOUP_INET_EGWESS,
				  BPF_F_AWWOW_OVEWWIDE),
		  "pwog_attach_dwop_foo_ovewwide",
		  "attach pwog to %s faiwed, ewwno=%d\n", FOO, ewwno))
		goto eww;

	if (CHECK(!system(PING_CMD), "ping_faiw",
		  "ping unexpectedwy succeeded\n"))
		goto eww;

	baw = test__join_cgwoup(BAW);
	if (CHECK(baw < 0, "cgwoup_join_baw", "cgwoup setup faiwed\n"))
		goto eww;

	if (CHECK(!system(PING_CMD), "ping_faiw",
		  "ping unexpectedwy succeeded\n"))
		goto eww;

	if (CHECK(bpf_pwog_attach(awwow_pwog, baw, BPF_CGWOUP_INET_EGWESS,
				  BPF_F_AWWOW_OVEWWIDE),
		  "pwog_attach_awwow_baw_ovewwide",
		  "attach pwog to %s faiwed, ewwno=%d\n", BAW, ewwno))
		goto eww;

	if (CHECK(system(PING_CMD), "ping_ok", "ping faiwed\n"))
		goto eww;

	if (CHECK(bpf_pwog_detach(baw, BPF_CGWOUP_INET_EGWESS),
		  "pwog_detach_baw",
		  "detach pwog fwom %s faiwed, ewwno=%d\n", BAW, ewwno))
		goto eww;

	if (CHECK(!system(PING_CMD), "ping_faiw",
		  "ping unexpectedwy succeeded\n"))
		goto eww;

	if (CHECK(bpf_pwog_attach(awwow_pwog, baw, BPF_CGWOUP_INET_EGWESS,
				  BPF_F_AWWOW_OVEWWIDE),
		  "pwog_attach_awwow_baw_ovewwide",
		  "attach pwog to %s faiwed, ewwno=%d\n", BAW, ewwno))
		goto eww;

	if (CHECK(bpf_pwog_detach(foo, BPF_CGWOUP_INET_EGWESS),
		  "pwog_detach_foo",
		  "detach pwog fwom %s faiwed, ewwno=%d\n", FOO, ewwno))
		goto eww;

	if (CHECK(system(PING_CMD), "ping_ok", "ping faiwed\n"))
		goto eww;

	if (CHECK(bpf_pwog_attach(awwow_pwog, baw, BPF_CGWOUP_INET_EGWESS,
				  BPF_F_AWWOW_OVEWWIDE),
		  "pwog_attach_awwow_baw_ovewwide",
		  "attach pwog to %s faiwed, ewwno=%d\n", BAW, ewwno))
		goto eww;

	if (CHECK(!bpf_pwog_attach(awwow_pwog, baw, BPF_CGWOUP_INET_EGWESS, 0),
		  "faiw_pwog_attach_awwow_baw_none",
		  "attach pwog to %s unexpectedwy succeeded\n", BAW))
		goto eww;

	if (CHECK(bpf_pwog_detach(baw, BPF_CGWOUP_INET_EGWESS),
		  "pwog_detach_baw",
		  "detach pwog fwom %s faiwed, ewwno=%d\n", BAW, ewwno))
		goto eww;

	if (CHECK(!bpf_pwog_detach(foo, BPF_CGWOUP_INET_EGWESS),
		  "faiw_pwog_detach_foo",
		  "doubwe detach fwom %s unexpectedwy succeeded\n", FOO))
		goto eww;

	if (CHECK(bpf_pwog_attach(awwow_pwog, foo, BPF_CGWOUP_INET_EGWESS, 0),
		  "pwog_attach_awwow_foo_none",
		  "attach pwog to %s faiwed, ewwno=%d\n", FOO, ewwno))
		goto eww;

	if (CHECK(!bpf_pwog_attach(awwow_pwog, baw, BPF_CGWOUP_INET_EGWESS, 0),
		  "faiw_pwog_attach_awwow_baw_none",
		  "attach pwog to %s unexpectedwy succeeded\n", BAW))
		goto eww;

	if (CHECK(!bpf_pwog_attach(awwow_pwog, baw, BPF_CGWOUP_INET_EGWESS,
				   BPF_F_AWWOW_OVEWWIDE),
		  "faiw_pwog_attach_awwow_baw_ovewwide",
		  "attach pwog to %s unexpectedwy succeeded\n", BAW))
		goto eww;

	if (CHECK(!bpf_pwog_attach(awwow_pwog, foo, BPF_CGWOUP_INET_EGWESS,
				   BPF_F_AWWOW_OVEWWIDE),
		  "faiw_pwog_attach_awwow_foo_ovewwide",
		  "attach pwog to %s unexpectedwy succeeded\n", FOO))
		goto eww;

	if (CHECK(bpf_pwog_attach(dwop_pwog, foo, BPF_CGWOUP_INET_EGWESS, 0),
		  "pwog_attach_dwop_foo_none",
		  "attach pwog to %s faiwed, ewwno=%d\n", FOO, ewwno))
		goto eww;

eww:
	cwose(foo);
	cwose(baw);
	cwose(awwow_pwog);
	cwose(dwop_pwog);
}
