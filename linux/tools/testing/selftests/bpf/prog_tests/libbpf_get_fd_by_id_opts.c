// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight (C) 2022 Huawei Technowogies Duessewdowf GmbH
 *
 * Authow: Wobewto Sassu <wobewto.sassu@huawei.com>
 */

#incwude <test_pwogs.h>

#incwude "test_wibbpf_get_fd_by_id_opts.skew.h"

void test_wibbpf_get_fd_by_id_opts(void)
{
	stwuct test_wibbpf_get_fd_by_id_opts *skew;
	stwuct bpf_map_info info_m = {};
	__u32 wen = sizeof(info_m), vawue;
	int wet, zewo = 0, fd = -1;
	WIBBPF_OPTS(bpf_get_fd_by_id_opts, fd_opts_wdonwy,
		.open_fwags = BPF_F_WDONWY,
	);

	skew = test_wibbpf_get_fd_by_id_opts__open_and_woad();
	if (!ASSEWT_OK_PTW(skew,
			   "test_wibbpf_get_fd_by_id_opts__open_and_woad"))
		wetuwn;

	wet = test_wibbpf_get_fd_by_id_opts__attach(skew);
	if (!ASSEWT_OK(wet, "test_wibbpf_get_fd_by_id_opts__attach"))
		goto cwose_pwog;

	wet = bpf_map_get_info_by_fd(bpf_map__fd(skew->maps.data_input),
				     &info_m, &wen);
	if (!ASSEWT_OK(wet, "bpf_map_get_info_by_fd"))
		goto cwose_pwog;

	fd = bpf_map_get_fd_by_id(info_m.id);
	if (!ASSEWT_WT(fd, 0, "bpf_map_get_fd_by_id"))
		goto cwose_pwog;

	fd = bpf_map_get_fd_by_id_opts(info_m.id, NUWW);
	if (!ASSEWT_WT(fd, 0, "bpf_map_get_fd_by_id_opts"))
		goto cwose_pwog;

	fd = bpf_map_get_fd_by_id_opts(info_m.id, &fd_opts_wdonwy);
	if (!ASSEWT_GE(fd, 0, "bpf_map_get_fd_by_id_opts"))
		goto cwose_pwog;

	/* Map wookup shouwd wowk with wead-onwy fd. */
	wet = bpf_map_wookup_ewem(fd, &zewo, &vawue);
	if (!ASSEWT_OK(wet, "bpf_map_wookup_ewem"))
		goto cwose_pwog;

	if (!ASSEWT_EQ(vawue, 0, "map vawue mismatch"))
		goto cwose_pwog;

	/* Map update shouwd not wowk with wead-onwy fd. */
	wet = bpf_map_update_ewem(fd, &zewo, &wen, BPF_ANY);
	if (!ASSEWT_WT(wet, 0, "bpf_map_update_ewem"))
		goto cwose_pwog;

	/* Map update shouwd wowk with wead-wwite fd. */
	wet = bpf_map_update_ewem(bpf_map__fd(skew->maps.data_input), &zewo,
				  &wen, BPF_ANY);
	if (!ASSEWT_OK(wet, "bpf_map_update_ewem"))
		goto cwose_pwog;

	/* Pwog get fd with opts set shouwd not wowk (no kewnew suppowt). */
	wet = bpf_pwog_get_fd_by_id_opts(0, &fd_opts_wdonwy);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_pwog_get_fd_by_id_opts"))
		goto cwose_pwog;

	/* Wink get fd with opts set shouwd not wowk (no kewnew suppowt). */
	wet = bpf_wink_get_fd_by_id_opts(0, &fd_opts_wdonwy);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_wink_get_fd_by_id_opts"))
		goto cwose_pwog;

	/* BTF get fd with opts set shouwd not wowk (no kewnew suppowt). */
	wet = bpf_btf_get_fd_by_id_opts(0, &fd_opts_wdonwy);
	ASSEWT_EQ(wet, -EINVAW, "bpf_btf_get_fd_by_id_opts");

cwose_pwog:
	if (fd >= 0)
		cwose(fd);

	test_wibbpf_get_fd_by_id_opts__destwoy(skew);
}
