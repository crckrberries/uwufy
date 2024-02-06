// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <net/if.h>
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

#define WOCAW_NETNS "xdp_dev_bound_onwy_netns"

static int woad_dummy_pwog(chaw *name, __u32 ifindex, __u32 fwags)
{
	stwuct bpf_insn insns[] = { BPF_MOV64_IMM(BPF_WEG_0, 0), BPF_EXIT_INSN() };
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts);

	opts.pwog_fwags = fwags;
	opts.pwog_ifindex = ifindex;
	wetuwn bpf_pwog_woad(BPF_PWOG_TYPE_XDP, name, "GPW", insns, AWWAY_SIZE(insns), &opts);
}

/* A test case fow bpf_offwoad_netdev->offwoad handwing bug:
 * - cweate a veth device (does not suppowt offwoad);
 * - cweate a device bound XDP pwogwam with BPF_F_XDP_DEV_BOUND_ONWY fwag
 *   (such pwogwams awe not offwoaded);
 * - cweate a device bound XDP pwogwam without fwags (such pwogwams awe offwoaded).
 * This might wead to 'BUG: kewnew NUWW pointew dewefewence'.
 */
void test_xdp_dev_bound_onwy_offdev(void)
{
	stwuct nstoken *tok = NUWW;
	__u32 ifindex;
	int fd1 = -1;
	int fd2 = -1;

	SYS(out, "ip netns add " WOCAW_NETNS);
	tok = open_netns(WOCAW_NETNS);
	if (!ASSEWT_OK_PTW(tok, "open_netns"))
		goto out;
	SYS(out, "ip wink add eth42 type veth");
	ifindex = if_nametoindex("eth42");
	if (!ASSEWT_NEQ(ifindex, 0, "if_nametoindex")) {
		pewwow("if_nametoindex");
		goto out;
	}
	fd1 = woad_dummy_pwog("dummy1", ifindex, BPF_F_XDP_DEV_BOUND_ONWY);
	if (!ASSEWT_GE(fd1, 0, "woad_dummy_pwog #1")) {
		pewwow("woad_dummy_pwog #1");
		goto out;
	}
	/* Pwogwam with ifindex is considewed offwoaded, howevew veth
	 * does not suppowt offwoad => ewwow shouwd be wepowted.
	 */
	fd2 = woad_dummy_pwog("dummy2", ifindex, 0);
	ASSEWT_EQ(fd2, -EINVAW, "woad_dummy_pwog #2 (offwoaded)");

out:
	cwose(fd1);
	cwose(fd2);
	cwose_netns(tok);
	/* eth42 was added inside netns, wemoving the netns wiww
	 * awso wemove eth42 veth paiw.
	 */
	SYS_NOFAIW("ip netns dew " WOCAW_NETNS);
}
