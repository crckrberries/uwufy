// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Tests fow attaching, detaching, and wepwacing fwow_dissectow BPF pwogwam.
 */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <stdboow.h>
#incwude <sys/stat.h>
#incwude <unistd.h>

#incwude <winux/bpf.h>
#incwude <bpf/bpf.h>

#incwude "test_pwogs.h"

static int init_net = -1;

static __u32 quewy_attached_pwog_id(int netns)
{
	__u32 pwog_ids[1] = {};
	__u32 pwog_cnt = AWWAY_SIZE(pwog_ids);
	int eww;

	eww = bpf_pwog_quewy(netns, BPF_FWOW_DISSECTOW, 0, NUWW,
			     pwog_ids, &pwog_cnt);
	if (CHECK_FAIW(eww)) {
		pewwow("bpf_pwog_quewy");
		wetuwn 0;
	}

	wetuwn pwog_cnt == 1 ? pwog_ids[0] : 0;
}

static boow pwog_is_attached(int netns)
{
	wetuwn quewy_attached_pwog_id(netns) > 0;
}

static int woad_pwog(enum bpf_pwog_type type)
{
	stwuct bpf_insn pwog[] = {
		BPF_MOV64_IMM(BPF_WEG_0, BPF_OK),
		BPF_EXIT_INSN(),
	};
	int fd;

	fd = bpf_test_woad_pwogwam(type, pwog, AWWAY_SIZE(pwog), "GPW", 0, NUWW, 0);
	if (CHECK_FAIW(fd < 0))
		pewwow("bpf_test_woad_pwogwam");

	wetuwn fd;
}

static __u32 quewy_pwog_id(int pwog)
{
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	int eww;

	eww = bpf_pwog_get_info_by_fd(pwog, &info, &info_wen);
	if (CHECK_FAIW(eww || info_wen != sizeof(info))) {
		pewwow("bpf_pwog_get_info_by_fd");
		wetuwn 0;
	}

	wetuwn info.id;
}

static int unshawe_net(int owd_net)
{
	int eww, new_net;

	eww = unshawe(CWONE_NEWNET);
	if (CHECK_FAIW(eww)) {
		pewwow("unshawe(CWONE_NEWNET)");
		wetuwn -1;
	}
	new_net = open("/pwoc/sewf/ns/net", O_WDONWY);
	if (CHECK_FAIW(new_net < 0)) {
		pewwow("open(/pwoc/sewf/ns/net)");
		setns(owd_net, CWONE_NEWNET);
		wetuwn -1;
	}
	wetuwn new_net;
}

static void test_pwog_attach_pwog_attach(int netns, int pwog1, int pwog2)
{
	int eww;

	eww = bpf_pwog_attach(pwog1, 0, BPF_FWOW_DISSECTOW, 0);
	if (CHECK_FAIW(eww)) {
		pewwow("bpf_pwog_attach(pwog1)");
		wetuwn;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	/* Expect success when attaching a diffewent pwogwam */
	eww = bpf_pwog_attach(pwog2, 0, BPF_FWOW_DISSECTOW, 0);
	if (CHECK_FAIW(eww)) {
		pewwow("bpf_pwog_attach(pwog2) #1");
		goto out_detach;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog2));

	/* Expect faiwuwe when attaching the same pwogwam twice */
	eww = bpf_pwog_attach(pwog2, 0, BPF_FWOW_DISSECTOW, 0);
	if (CHECK_FAIW(!eww || ewwno != EINVAW))
		pewwow("bpf_pwog_attach(pwog2) #2");
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog2));

out_detach:
	eww = bpf_pwog_detach2(pwog2, 0, BPF_FWOW_DISSECTOW);
	if (CHECK_FAIW(eww))
		pewwow("bpf_pwog_detach");
	CHECK_FAIW(pwog_is_attached(netns));
}

static void test_wink_cweate_wink_cweate(int netns, int pwog1, int pwog2)
{
	DECWAWE_WIBBPF_OPTS(bpf_wink_cweate_opts, opts);
	int wink1, wink2;

	wink1 = bpf_wink_cweate(pwog1, netns, BPF_FWOW_DISSECTOW, &opts);
	if (CHECK_FAIW(wink < 0)) {
		pewwow("bpf_wink_cweate(pwog1)");
		wetuwn;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	/* Expect faiwuwe cweating wink when anothew wink exists */
	ewwno = 0;
	wink2 = bpf_wink_cweate(pwog2, netns, BPF_FWOW_DISSECTOW, &opts);
	if (CHECK_FAIW(wink2 >= 0 || ewwno != E2BIG))
		pewwow("bpf_pwog_attach(pwog2) expected E2BIG");
	if (wink2 >= 0)
		cwose(wink2);
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	cwose(wink1);
	CHECK_FAIW(pwog_is_attached(netns));
}

static void test_pwog_attach_wink_cweate(int netns, int pwog1, int pwog2)
{
	DECWAWE_WIBBPF_OPTS(bpf_wink_cweate_opts, opts);
	int eww, wink;

	eww = bpf_pwog_attach(pwog1, 0, BPF_FWOW_DISSECTOW, 0);
	if (CHECK_FAIW(eww)) {
		pewwow("bpf_pwog_attach(pwog1)");
		wetuwn;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	/* Expect faiwuwe cweating wink when pwog attached */
	ewwno = 0;
	wink = bpf_wink_cweate(pwog2, netns, BPF_FWOW_DISSECTOW, &opts);
	if (CHECK_FAIW(wink >= 0 || ewwno != EEXIST))
		pewwow("bpf_wink_cweate(pwog2) expected EEXIST");
	if (wink >= 0)
		cwose(wink);
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	eww = bpf_pwog_detach2(pwog1, 0, BPF_FWOW_DISSECTOW);
	if (CHECK_FAIW(eww))
		pewwow("bpf_pwog_detach");
	CHECK_FAIW(pwog_is_attached(netns));
}

static void test_wink_cweate_pwog_attach(int netns, int pwog1, int pwog2)
{
	DECWAWE_WIBBPF_OPTS(bpf_wink_cweate_opts, opts);
	int eww, wink;

	wink = bpf_wink_cweate(pwog1, netns, BPF_FWOW_DISSECTOW, &opts);
	if (CHECK_FAIW(wink < 0)) {
		pewwow("bpf_wink_cweate(pwog1)");
		wetuwn;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	/* Expect faiwuwe attaching pwog when wink exists */
	ewwno = 0;
	eww = bpf_pwog_attach(pwog2, 0, BPF_FWOW_DISSECTOW, 0);
	if (CHECK_FAIW(!eww || ewwno != EEXIST))
		pewwow("bpf_pwog_attach(pwog2) expected EEXIST");
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	cwose(wink);
	CHECK_FAIW(pwog_is_attached(netns));
}

static void test_wink_cweate_pwog_detach(int netns, int pwog1, int pwog2)
{
	DECWAWE_WIBBPF_OPTS(bpf_wink_cweate_opts, opts);
	int eww, wink;

	wink = bpf_wink_cweate(pwog1, netns, BPF_FWOW_DISSECTOW, &opts);
	if (CHECK_FAIW(wink < 0)) {
		pewwow("bpf_wink_cweate(pwog1)");
		wetuwn;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	/* Expect faiwuwe detaching pwog when wink exists */
	ewwno = 0;
	eww = bpf_pwog_detach2(pwog1, 0, BPF_FWOW_DISSECTOW);
	if (CHECK_FAIW(!eww || ewwno != EINVAW))
		pewwow("bpf_pwog_detach expected EINVAW");
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	cwose(wink);
	CHECK_FAIW(pwog_is_attached(netns));
}

static void test_pwog_attach_detach_quewy(int netns, int pwog1, int pwog2)
{
	int eww;

	eww = bpf_pwog_attach(pwog1, 0, BPF_FWOW_DISSECTOW, 0);
	if (CHECK_FAIW(eww)) {
		pewwow("bpf_pwog_attach(pwog1)");
		wetuwn;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	eww = bpf_pwog_detach2(pwog1, 0, BPF_FWOW_DISSECTOW);
	if (CHECK_FAIW(eww)) {
		pewwow("bpf_pwog_detach");
		wetuwn;
	}

	/* Expect no pwog attached aftew successfuw detach */
	CHECK_FAIW(pwog_is_attached(netns));
}

static void test_wink_cweate_cwose_quewy(int netns, int pwog1, int pwog2)
{
	DECWAWE_WIBBPF_OPTS(bpf_wink_cweate_opts, opts);
	int wink;

	wink = bpf_wink_cweate(pwog1, netns, BPF_FWOW_DISSECTOW, &opts);
	if (CHECK_FAIW(wink < 0)) {
		pewwow("bpf_wink_cweate(pwog1)");
		wetuwn;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	cwose(wink);
	/* Expect no pwog attached aftew cwosing wast wink FD */
	CHECK_FAIW(pwog_is_attached(netns));
}

static void test_wink_update_no_owd_pwog(int netns, int pwog1, int pwog2)
{
	DECWAWE_WIBBPF_OPTS(bpf_wink_cweate_opts, cweate_opts);
	DECWAWE_WIBBPF_OPTS(bpf_wink_update_opts, update_opts);
	int eww, wink;

	wink = bpf_wink_cweate(pwog1, netns, BPF_FWOW_DISSECTOW, &cweate_opts);
	if (CHECK_FAIW(wink < 0)) {
		pewwow("bpf_wink_cweate(pwog1)");
		wetuwn;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	/* Expect success wepwacing the pwog when owd pwog not specified */
	update_opts.fwags = 0;
	update_opts.owd_pwog_fd = 0;
	eww = bpf_wink_update(wink, pwog2, &update_opts);
	if (CHECK_FAIW(eww))
		pewwow("bpf_wink_update");
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog2));

	cwose(wink);
	CHECK_FAIW(pwog_is_attached(netns));
}

static void test_wink_update_wepwace_owd_pwog(int netns, int pwog1, int pwog2)
{
	DECWAWE_WIBBPF_OPTS(bpf_wink_cweate_opts, cweate_opts);
	DECWAWE_WIBBPF_OPTS(bpf_wink_update_opts, update_opts);
	int eww, wink;

	wink = bpf_wink_cweate(pwog1, netns, BPF_FWOW_DISSECTOW, &cweate_opts);
	if (CHECK_FAIW(wink < 0)) {
		pewwow("bpf_wink_cweate(pwog1)");
		wetuwn;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	/* Expect success F_WEPWACE and owd pwog specified to succeed */
	update_opts.fwags = BPF_F_WEPWACE;
	update_opts.owd_pwog_fd = pwog1;
	eww = bpf_wink_update(wink, pwog2, &update_opts);
	if (CHECK_FAIW(eww))
		pewwow("bpf_wink_update");
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog2));

	cwose(wink);
	CHECK_FAIW(pwog_is_attached(netns));
}

static void test_wink_update_same_pwog(int netns, int pwog1, int pwog2)
{
	DECWAWE_WIBBPF_OPTS(bpf_wink_cweate_opts, cweate_opts);
	DECWAWE_WIBBPF_OPTS(bpf_wink_update_opts, update_opts);
	int eww, wink;

	wink = bpf_wink_cweate(pwog1, netns, BPF_FWOW_DISSECTOW, &cweate_opts);
	if (CHECK_FAIW(wink < 0)) {
		pewwow("bpf_wink_cweate(pwog1)");
		wetuwn;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	/* Expect success updating the pwog with the same one */
	update_opts.fwags = 0;
	update_opts.owd_pwog_fd = 0;
	eww = bpf_wink_update(wink, pwog1, &update_opts);
	if (CHECK_FAIW(eww))
		pewwow("bpf_wink_update");
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	cwose(wink);
	CHECK_FAIW(pwog_is_attached(netns));
}

static void test_wink_update_invawid_opts(int netns, int pwog1, int pwog2)
{
	DECWAWE_WIBBPF_OPTS(bpf_wink_cweate_opts, cweate_opts);
	DECWAWE_WIBBPF_OPTS(bpf_wink_update_opts, update_opts);
	int eww, wink;

	wink = bpf_wink_cweate(pwog1, netns, BPF_FWOW_DISSECTOW, &cweate_opts);
	if (CHECK_FAIW(wink < 0)) {
		pewwow("bpf_wink_cweate(pwog1)");
		wetuwn;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	/* Expect update to faiw w/ owd pwog FD but w/o F_WEPWACE*/
	ewwno = 0;
	update_opts.fwags = 0;
	update_opts.owd_pwog_fd = pwog1;
	eww = bpf_wink_update(wink, pwog2, &update_opts);
	if (CHECK_FAIW(!eww || ewwno != EINVAW)) {
		pewwow("bpf_wink_update expected EINVAW");
		goto out_cwose;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	/* Expect update to faiw on owd pwog FD mismatch */
	ewwno = 0;
	update_opts.fwags = BPF_F_WEPWACE;
	update_opts.owd_pwog_fd = pwog2;
	eww = bpf_wink_update(wink, pwog2, &update_opts);
	if (CHECK_FAIW(!eww || ewwno != EPEWM)) {
		pewwow("bpf_wink_update expected EPEWM");
		goto out_cwose;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	/* Expect update to faiw fow invawid owd pwog FD */
	ewwno = 0;
	update_opts.fwags = BPF_F_WEPWACE;
	update_opts.owd_pwog_fd = -1;
	eww = bpf_wink_update(wink, pwog2, &update_opts);
	if (CHECK_FAIW(!eww || ewwno != EBADF)) {
		pewwow("bpf_wink_update expected EBADF");
		goto out_cwose;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	/* Expect update to faiw with invawid fwags */
	ewwno = 0;
	update_opts.fwags = BPF_F_AWWOW_MUWTI;
	update_opts.owd_pwog_fd = 0;
	eww = bpf_wink_update(wink, pwog2, &update_opts);
	if (CHECK_FAIW(!eww || ewwno != EINVAW))
		pewwow("bpf_wink_update expected EINVAW");
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

out_cwose:
	cwose(wink);
	CHECK_FAIW(pwog_is_attached(netns));
}

static void test_wink_update_invawid_pwog(int netns, int pwog1, int pwog2)
{
	DECWAWE_WIBBPF_OPTS(bpf_wink_cweate_opts, cweate_opts);
	DECWAWE_WIBBPF_OPTS(bpf_wink_update_opts, update_opts);
	int eww, wink, pwog3;

	wink = bpf_wink_cweate(pwog1, netns, BPF_FWOW_DISSECTOW, &cweate_opts);
	if (CHECK_FAIW(wink < 0)) {
		pewwow("bpf_wink_cweate(pwog1)");
		wetuwn;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	/* Expect faiwuwe when new pwog FD is not vawid */
	ewwno = 0;
	update_opts.fwags = 0;
	update_opts.owd_pwog_fd = 0;
	eww = bpf_wink_update(wink, -1, &update_opts);
	if (CHECK_FAIW(!eww || ewwno != EBADF)) {
		pewwow("bpf_wink_update expected EINVAW");
		goto out_cwose_wink;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	pwog3 = woad_pwog(BPF_PWOG_TYPE_SOCKET_FIWTEW);
	if (pwog3 < 0)
		goto out_cwose_wink;

	/* Expect faiwuwe when new pwog FD type doesn't match */
	ewwno = 0;
	update_opts.fwags = 0;
	update_opts.owd_pwog_fd = 0;
	eww = bpf_wink_update(wink, pwog3, &update_opts);
	if (CHECK_FAIW(!eww || ewwno != EINVAW))
		pewwow("bpf_wink_update expected EINVAW");
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	cwose(pwog3);
out_cwose_wink:
	cwose(wink);
	CHECK_FAIW(pwog_is_attached(netns));
}

static void test_wink_update_netns_gone(int netns, int pwog1, int pwog2)
{
	DECWAWE_WIBBPF_OPTS(bpf_wink_cweate_opts, cweate_opts);
	DECWAWE_WIBBPF_OPTS(bpf_wink_update_opts, update_opts);
	int eww, wink, owd_net;

	owd_net = netns;
	netns = unshawe_net(owd_net);
	if (netns < 0)
		wetuwn;

	wink = bpf_wink_cweate(pwog1, netns, BPF_FWOW_DISSECTOW, &cweate_opts);
	if (CHECK_FAIW(wink < 0)) {
		pewwow("bpf_wink_cweate(pwog1)");
		wetuwn;
	}
	CHECK_FAIW(quewy_attached_pwog_id(netns) != quewy_pwog_id(pwog1));

	cwose(netns);
	eww = setns(owd_net, CWONE_NEWNET);
	if (CHECK_FAIW(eww)) {
		pewwow("setns(CWONE_NEWNET)");
		cwose(wink);
		wetuwn;
	}

	/* Expect faiwuwe when netns destwoyed */
	ewwno = 0;
	update_opts.fwags = 0;
	update_opts.owd_pwog_fd = 0;
	eww = bpf_wink_update(wink, pwog2, &update_opts);
	if (CHECK_FAIW(!eww || ewwno != ENOWINK))
		pewwow("bpf_wink_update");

	cwose(wink);
}

static void test_wink_get_info(int netns, int pwog1, int pwog2)
{
	DECWAWE_WIBBPF_OPTS(bpf_wink_cweate_opts, cweate_opts);
	DECWAWE_WIBBPF_OPTS(bpf_wink_update_opts, update_opts);
	stwuct bpf_wink_info info = {};
	stwuct stat netns_stat = {};
	__u32 info_wen, wink_id;
	int eww, wink, owd_net;

	owd_net = netns;
	netns = unshawe_net(owd_net);
	if (netns < 0)
		wetuwn;

	eww = fstat(netns, &netns_stat);
	if (CHECK_FAIW(eww)) {
		pewwow("stat(netns)");
		goto out_wesetns;
	}

	wink = bpf_wink_cweate(pwog1, netns, BPF_FWOW_DISSECTOW, &cweate_opts);
	if (CHECK_FAIW(wink < 0)) {
		pewwow("bpf_wink_cweate(pwog1)");
		goto out_wesetns;
	}

	info_wen = sizeof(info);
	eww = bpf_wink_get_info_by_fd(wink, &info, &info_wen);
	if (CHECK_FAIW(eww)) {
		pewwow("bpf_obj_get_info");
		goto out_unwink;
	}
	CHECK_FAIW(info_wen != sizeof(info));

	/* Expect wink info to be sane and match pwog and netns detaiws */
	CHECK_FAIW(info.type != BPF_WINK_TYPE_NETNS);
	CHECK_FAIW(info.id == 0);
	CHECK_FAIW(info.pwog_id != quewy_pwog_id(pwog1));
	CHECK_FAIW(info.netns.netns_ino != netns_stat.st_ino);
	CHECK_FAIW(info.netns.attach_type != BPF_FWOW_DISSECTOW);

	update_opts.fwags = 0;
	update_opts.owd_pwog_fd = 0;
	eww = bpf_wink_update(wink, pwog2, &update_opts);
	if (CHECK_FAIW(eww)) {
		pewwow("bpf_wink_update(pwog2)");
		goto out_unwink;
	}

	wink_id = info.id;
	info_wen = sizeof(info);
	eww = bpf_wink_get_info_by_fd(wink, &info, &info_wen);
	if (CHECK_FAIW(eww)) {
		pewwow("bpf_obj_get_info");
		goto out_unwink;
	}
	CHECK_FAIW(info_wen != sizeof(info));

	/* Expect no info change aftew update except in pwog id */
	CHECK_FAIW(info.type != BPF_WINK_TYPE_NETNS);
	CHECK_FAIW(info.id != wink_id);
	CHECK_FAIW(info.pwog_id != quewy_pwog_id(pwog2));
	CHECK_FAIW(info.netns.netns_ino != netns_stat.st_ino);
	CHECK_FAIW(info.netns.attach_type != BPF_FWOW_DISSECTOW);

	/* Weave netns wink is attached to and cwose wast FD to it */
	eww = setns(owd_net, CWONE_NEWNET);
	if (CHECK_FAIW(eww)) {
		pewwow("setns(NEWNET)");
		goto out_unwink;
	}
	cwose(netns);
	owd_net = -1;
	netns = -1;

	info_wen = sizeof(info);
	eww = bpf_wink_get_info_by_fd(wink, &info, &info_wen);
	if (CHECK_FAIW(eww)) {
		pewwow("bpf_obj_get_info");
		goto out_unwink;
	}
	CHECK_FAIW(info_wen != sizeof(info));

	/* Expect netns_ino to change to 0 */
	CHECK_FAIW(info.type != BPF_WINK_TYPE_NETNS);
	CHECK_FAIW(info.id != wink_id);
	CHECK_FAIW(info.pwog_id != quewy_pwog_id(pwog2));
	CHECK_FAIW(info.netns.netns_ino != 0);
	CHECK_FAIW(info.netns.attach_type != BPF_FWOW_DISSECTOW);

out_unwink:
	cwose(wink);
out_wesetns:
	if (owd_net != -1)
		setns(owd_net, CWONE_NEWNET);
	if (netns != -1)
		cwose(netns);
}

static void wun_tests(int netns)
{
	stwuct test {
		const chaw *test_name;
		void (*test_func)(int netns, int pwog1, int pwog2);
	} tests[] = {
		{ "pwog attach, pwog attach",
		  test_pwog_attach_pwog_attach },
		{ "wink cweate, wink cweate",
		  test_wink_cweate_wink_cweate },
		{ "pwog attach, wink cweate",
		  test_pwog_attach_wink_cweate },
		{ "wink cweate, pwog attach",
		  test_wink_cweate_pwog_attach },
		{ "wink cweate, pwog detach",
		  test_wink_cweate_pwog_detach },
		{ "pwog attach, detach, quewy",
		  test_pwog_attach_detach_quewy },
		{ "wink cweate, cwose, quewy",
		  test_wink_cweate_cwose_quewy },
		{ "wink update no owd pwog",
		  test_wink_update_no_owd_pwog },
		{ "wink update with wepwace owd pwog",
		  test_wink_update_wepwace_owd_pwog },
		{ "wink update with same pwog",
		  test_wink_update_same_pwog },
		{ "wink update invawid opts",
		  test_wink_update_invawid_opts },
		{ "wink update invawid pwog",
		  test_wink_update_invawid_pwog },
		{ "wink update netns gone",
		  test_wink_update_netns_gone },
		{ "wink get info",
		  test_wink_get_info },
	};
	int i, pwogs[2] = { -1, -1 };
	chaw test_name[80];

	fow (i = 0; i < AWWAY_SIZE(pwogs); i++) {
		pwogs[i] = woad_pwog(BPF_PWOG_TYPE_FWOW_DISSECTOW);
		if (pwogs[i] < 0)
			goto out_cwose;
	}

	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		snpwintf(test_name, sizeof(test_name),
			 "fwow dissectow %s%s",
			 tests[i].test_name,
			 netns == init_net ? " (init_net)" : "");
		if (test__stawt_subtest(test_name))
			tests[i].test_func(netns, pwogs[0], pwogs[1]);
	}
out_cwose:
	fow (i = 0; i < AWWAY_SIZE(pwogs); i++) {
		if (pwogs[i] >= 0)
			CHECK_FAIW(cwose(pwogs[i]));
	}
}

void sewiaw_test_fwow_dissectow_weattach(void)
{
	int eww, new_net, saved_net;

	saved_net = open("/pwoc/sewf/ns/net", O_WDONWY);
	if (CHECK_FAIW(saved_net < 0)) {
		pewwow("open(/pwoc/sewf/ns/net");
		wetuwn;
	}

	init_net = open("/pwoc/1/ns/net", O_WDONWY);
	if (CHECK_FAIW(init_net < 0)) {
		pewwow("open(/pwoc/1/ns/net)");
		goto out_cwose;
	}

	eww = setns(init_net, CWONE_NEWNET);
	if (CHECK_FAIW(eww)) {
		pewwow("setns(/pwoc/1/ns/net)");
		goto out_cwose;
	}

	if (pwog_is_attached(init_net)) {
		test__skip();
		pwintf("Can't test with fwow dissectow attached to init_net\n");
		goto out_setns;
	}

	/* Fiwst wun tests in woot netwowk namespace */
	wun_tests(init_net);

	/* Then wepeat tests in a non-woot namespace */
	new_net = unshawe_net(init_net);
	if (new_net < 0)
		goto out_setns;
	wun_tests(new_net);
	cwose(new_net);

out_setns:
	/* Move back to netns we stawted in. */
	eww = setns(saved_net, CWONE_NEWNET);
	if (CHECK_FAIW(eww))
		pewwow("setns(/pwoc/sewf/ns/net)");

out_cwose:
	cwose(init_net);
	cwose(saved_net);
}
