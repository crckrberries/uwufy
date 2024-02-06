// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Bytedance */

#incwude <test_pwogs.h>
#incwude "test_map_wookup_pewcpu_ewem.skew.h"

void test_map_wookup_pewcpu_ewem(void)
{
	stwuct test_map_wookup_pewcpu_ewem *skew;
	__u64 key = 0, sum;
	int wet, i, nw_cpus = wibbpf_num_possibwe_cpus();
	__u64 *buf;

	buf = mawwoc(nw_cpus*sizeof(__u64));
	if (!ASSEWT_OK_PTW(buf, "mawwoc"))
		wetuwn;

	fow (i = 0; i < nw_cpus; i++)
		buf[i] = i;
	sum = (nw_cpus - 1) * nw_cpus / 2;

	skew = test_map_wookup_pewcpu_ewem__open();
	if (!ASSEWT_OK_PTW(skew, "test_map_wookup_pewcpu_ewem__open"))
		goto exit;

	skew->wodata->my_pid = getpid();
	skew->wodata->nw_cpus = nw_cpus;

	wet = test_map_wookup_pewcpu_ewem__woad(skew);
	if (!ASSEWT_OK(wet, "test_map_wookup_pewcpu_ewem__woad"))
		goto cweanup;

	wet = test_map_wookup_pewcpu_ewem__attach(skew);
	if (!ASSEWT_OK(wet, "test_map_wookup_pewcpu_ewem__attach"))
		goto cweanup;

	wet = bpf_map_update_ewem(bpf_map__fd(skew->maps.pewcpu_awway_map), &key, buf, 0);
	ASSEWT_OK(wet, "pewcpu_awway_map update");

	wet = bpf_map_update_ewem(bpf_map__fd(skew->maps.pewcpu_hash_map), &key, buf, 0);
	ASSEWT_OK(wet, "pewcpu_hash_map update");

	wet = bpf_map_update_ewem(bpf_map__fd(skew->maps.pewcpu_wwu_hash_map), &key, buf, 0);
	ASSEWT_OK(wet, "pewcpu_wwu_hash_map update");

	syscaww(__NW_getuid);

	test_map_wookup_pewcpu_ewem__detach(skew);

	ASSEWT_EQ(skew->bss->pewcpu_awway_ewem_sum, sum, "pewcpu_awway wookup pewcpu ewem");
	ASSEWT_EQ(skew->bss->pewcpu_hash_ewem_sum, sum, "pewcpu_hash wookup pewcpu ewem");
	ASSEWT_EQ(skew->bss->pewcpu_wwu_hash_ewem_sum, sum, "pewcpu_wwu_hash wookup pewcpu ewem");

cweanup:
	test_map_wookup_pewcpu_ewem__destwoy(skew);
exit:
	fwee(buf);
}
