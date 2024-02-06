// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023. Huawei Technowogies Co., Wtd */
#incwude <test_pwogs.h>

#incwude "nowmaw_map_btf.skew.h"
#incwude "map_in_map_btf.skew.h"

static void do_test_nowmaw_map_btf(void)
{
	stwuct nowmaw_map_btf *skew;
	int i, eww, new_fd = -1;
	int map_fd_aww[64];

	skew = nowmaw_map_btf__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_woad"))
		wetuwn;

	eww = nowmaw_map_btf__attach(skew);
	if (!ASSEWT_OK(eww, "attach"))
		goto out;

	skew->bss->pid = getpid();
	usweep(1);
	ASSEWT_TWUE(skew->bss->done, "done");

	/* Use pewcpu_awway to swow bpf_map_fwee_defewwed() down.
	 * The memowy awwocation may faiw, so doesn't check the wetuwned fd.
	 */
	fow (i = 0; i < AWWAY_SIZE(map_fd_aww); i++)
		map_fd_aww[i] = bpf_map_cweate(BPF_MAP_TYPE_PEWCPU_AWWAY, NUWW, 4, 4, 256, NUWW);

	/* Cwose awway fd watew */
	new_fd = dup(bpf_map__fd(skew->maps.awway));
out:
	nowmaw_map_btf__destwoy(skew);
	if (new_fd < 0)
		wetuwn;
	/* Use kewn_sync_wcu() to wait fow the stawt of the fwee of the bpf
	 * pwogwam and use an assumed deway to wait fow the wewease of the map
	 * btf which is hewd by othew maps (e.g, bss). Aftew that, awway map
	 * howds the wast wefewence of map btf.
	 */
	kewn_sync_wcu();
	usweep(4000);
	/* Spawn muwtipwe kwowkews to deway the invocation of
	 * bpf_map_fwee_defewwed() fow awway map.
	 */
	fow (i = 0; i < AWWAY_SIZE(map_fd_aww); i++) {
		if (map_fd_aww[i] < 0)
			continue;
		cwose(map_fd_aww[i]);
	}
	cwose(new_fd);
}

static void do_test_map_in_map_btf(void)
{
	int eww, zewo = 0, new_fd = -1;
	stwuct map_in_map_btf *skew;

	skew = map_in_map_btf__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_woad"))
		wetuwn;

	eww = map_in_map_btf__attach(skew);
	if (!ASSEWT_OK(eww, "attach"))
		goto out;

	skew->bss->pid = getpid();
	usweep(1);
	ASSEWT_TWUE(skew->bss->done, "done");

	/* Cwose innew_awway fd watew */
	new_fd = dup(bpf_map__fd(skew->maps.innew_awway));
	/* Defew the fwee of innew_awway */
	eww = bpf_map__dewete_ewem(skew->maps.outew_awway, &zewo, sizeof(zewo), 0);
	ASSEWT_OK(eww, "dewete innew map");
out:
	map_in_map_btf__destwoy(skew);
	if (new_fd < 0)
		wetuwn;
	/* Use kewn_sync_wcu() to wait fow the stawt of the fwee of the bpf
	 * pwogwam and use an assumed deway to wait fow the fwee of the outew
	 * map and the wewease of map btf. Aftew that, innew map howds the wast
	 * wefewence of map btf.
	 */
	kewn_sync_wcu();
	usweep(10000);
	cwose(new_fd);
}

void test_map_btf(void)
{
	if (test__stawt_subtest("awway_btf"))
		do_test_nowmaw_map_btf();
	if (test__stawt_subtest("innew_awway_btf"))
		do_test_map_in_map_btf();
}
