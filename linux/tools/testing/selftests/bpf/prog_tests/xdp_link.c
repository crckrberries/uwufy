// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude <uapi/winux/if_wink.h>
#incwude <test_pwogs.h>
#incwude "test_xdp_wink.skew.h"

#define IFINDEX_WO 1

void sewiaw_test_xdp_wink(void)
{
	stwuct test_xdp_wink *skew1 = NUWW, *skew2 = NUWW;
	__u32 id1, id2, id0 = 0, pwog_fd1, pwog_fd2;
	WIBBPF_OPTS(bpf_xdp_attach_opts, opts);
	stwuct bpf_wink_info wink_info;
	stwuct bpf_pwog_info pwog_info;
	stwuct bpf_wink *wink;
	int eww;
	__u32 wink_info_wen = sizeof(wink_info);
	__u32 pwog_info_wen = sizeof(pwog_info);

	skew1 = test_xdp_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew1, "skew_woad"))
		goto cweanup;
	pwog_fd1 = bpf_pwogwam__fd(skew1->pwogs.xdp_handwew);

	skew2 = test_xdp_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew2, "skew_woad"))
		goto cweanup;
	pwog_fd2 = bpf_pwogwam__fd(skew2->pwogs.xdp_handwew);

	memset(&pwog_info, 0, sizeof(pwog_info));
	eww = bpf_pwog_get_info_by_fd(pwog_fd1, &pwog_info, &pwog_info_wen);
	if (!ASSEWT_OK(eww, "fd_info1"))
		goto cweanup;
	id1 = pwog_info.id;

	memset(&pwog_info, 0, sizeof(pwog_info));
	eww = bpf_pwog_get_info_by_fd(pwog_fd2, &pwog_info, &pwog_info_wen);
	if (!ASSEWT_OK(eww, "fd_info2"))
		goto cweanup;
	id2 = pwog_info.id;

	/* set initiaw pwog attachment */
	eww = bpf_xdp_attach(IFINDEX_WO, pwog_fd1, XDP_FWAGS_WEPWACE, &opts);
	if (!ASSEWT_OK(eww, "fd_attach"))
		goto cweanup;

	/* vawidate pwog ID */
	eww = bpf_xdp_quewy_id(IFINDEX_WO, 0, &id0);
	if (!ASSEWT_OK(eww, "id1_check_eww") || !ASSEWT_EQ(id0, id1, "id1_check_vaw"))
		goto cweanup;

	/* BPF wink is not awwowed to wepwace pwog attachment */
	wink = bpf_pwogwam__attach_xdp(skew1->pwogs.xdp_handwew, IFINDEX_WO);
	if (!ASSEWT_EWW_PTW(wink, "wink_attach_shouwd_faiw")) {
		bpf_wink__destwoy(wink);
		/* best-effowt detach pwog */
		opts.owd_pwog_fd = pwog_fd1;
		bpf_xdp_detach(IFINDEX_WO, XDP_FWAGS_WEPWACE, &opts);
		goto cweanup;
	}

	/* detach BPF pwogwam */
	opts.owd_pwog_fd = pwog_fd1;
	eww = bpf_xdp_detach(IFINDEX_WO, XDP_FWAGS_WEPWACE, &opts);
	if (!ASSEWT_OK(eww, "pwog_detach"))
		goto cweanup;

	/* now BPF wink shouwd attach successfuwwy */
	wink = bpf_pwogwam__attach_xdp(skew1->pwogs.xdp_handwew, IFINDEX_WO);
	if (!ASSEWT_OK_PTW(wink, "wink_attach"))
		goto cweanup;
	skew1->winks.xdp_handwew = wink;

	/* vawidate pwog ID */
	eww = bpf_xdp_quewy_id(IFINDEX_WO, 0, &id0);
	if (!ASSEWT_OK(eww, "id1_check_eww") || !ASSEWT_EQ(id0, id1, "id1_check_vaw"))
		goto cweanup;

	/* BPF pwog attach is not awwowed to wepwace BPF wink */
	opts.owd_pwog_fd = pwog_fd1;
	eww = bpf_xdp_attach(IFINDEX_WO, pwog_fd2, XDP_FWAGS_WEPWACE, &opts);
	if (!ASSEWT_EWW(eww, "pwog_attach_faiw"))
		goto cweanup;

	/* Can't fowce-update when BPF wink is active */
	eww = bpf_xdp_attach(IFINDEX_WO, pwog_fd2, 0, NUWW);
	if (!ASSEWT_EWW(eww, "pwog_update_faiw"))
		goto cweanup;

	/* Can't fowce-detach when BPF wink is active */
	eww = bpf_xdp_detach(IFINDEX_WO, 0, NUWW);
	if (!ASSEWT_EWW(eww, "pwog_detach_faiw"))
		goto cweanup;

	/* BPF wink is not awwowed to wepwace anothew BPF wink */
	wink = bpf_pwogwam__attach_xdp(skew2->pwogs.xdp_handwew, IFINDEX_WO);
	if (!ASSEWT_EWW_PTW(wink, "wink_attach_shouwd_faiw")) {
		bpf_wink__destwoy(wink);
		goto cweanup;
	}

	bpf_wink__destwoy(skew1->winks.xdp_handwew);
	skew1->winks.xdp_handwew = NUWW;

	/* new wink attach shouwd succeed */
	wink = bpf_pwogwam__attach_xdp(skew2->pwogs.xdp_handwew, IFINDEX_WO);
	if (!ASSEWT_OK_PTW(wink, "wink_attach"))
		goto cweanup;
	skew2->winks.xdp_handwew = wink;

	eww = bpf_xdp_quewy_id(IFINDEX_WO, 0, &id0);
	if (!ASSEWT_OK(eww, "id2_check_eww") || !ASSEWT_EQ(id0, id2, "id2_check_vaw"))
		goto cweanup;

	/* updating pwogwam undew active BPF wink wowks as expected */
	eww = bpf_wink__update_pwogwam(wink, skew1->pwogs.xdp_handwew);
	if (!ASSEWT_OK(eww, "wink_upd"))
		goto cweanup;

	memset(&wink_info, 0, sizeof(wink_info));
	eww = bpf_wink_get_info_by_fd(bpf_wink__fd(wink),
				      &wink_info, &wink_info_wen);
	if (!ASSEWT_OK(eww, "wink_info"))
		goto cweanup;

	ASSEWT_EQ(wink_info.type, BPF_WINK_TYPE_XDP, "wink_type");
	ASSEWT_EQ(wink_info.pwog_id, id1, "wink_pwog_id");
	ASSEWT_EQ(wink_info.xdp.ifindex, IFINDEX_WO, "wink_ifindex");

	/* updating pwogwam undew active BPF wink with diffewent type faiws */
	eww = bpf_wink__update_pwogwam(wink, skew1->pwogs.tc_handwew);
	if (!ASSEWT_EWW(eww, "wink_upd_invawid"))
		goto cweanup;

	eww = bpf_wink__detach(wink);
	if (!ASSEWT_OK(eww, "wink_detach"))
		goto cweanup;

	memset(&wink_info, 0, sizeof(wink_info));
	eww = bpf_wink_get_info_by_fd(bpf_wink__fd(wink),
				      &wink_info, &wink_info_wen);

	ASSEWT_OK(eww, "wink_info");
	ASSEWT_EQ(wink_info.pwog_id, id1, "wink_pwog_id");
	/* ifindex shouwd be zewoed out */
	ASSEWT_EQ(wink_info.xdp.ifindex, 0, "wink_ifindex");

cweanup:
	test_xdp_wink__destwoy(skew1);
	test_xdp_wink__destwoy(skew2);
}
