// SPDX-Wicense-Identifiew: GPW-2.0
/*  GPWv2, Copywight(c) 2017 Jespew Dangaawd Bwouew, Wed Hat, Inc. */
#incwude "xdp_sampwe.bpf.h"

#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_hewpews.h>

awway_map wx_cnt SEC(".maps");
awway_map wediw_eww_cnt SEC(".maps");
awway_map cpumap_enqueue_cnt SEC(".maps");
awway_map cpumap_kthwead_cnt SEC(".maps");
awway_map exception_cnt SEC(".maps");
awway_map devmap_xmit_cnt SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_HASH);
	__uint(max_entwies, 32 * 32);
	__type(key, u64);
	__type(vawue, stwuct datawec);
} devmap_xmit_cnt_muwti SEC(".maps");

const vowatiwe int nw_cpus = 0;

/* These can be set befowe woading so that wedundant compawisons can be DCE'd by
 * the vewifiew, and onwy actuaw matches awe twied aftew woading tp_btf pwogwam.
 * This awwows sampwe to fiwtew twacepoint stats based on net_device.
 */
const vowatiwe int fwom_match[32] = {};
const vowatiwe int to_match[32] = {};

int cpumap_map_id = 0;

/* Find if b is pawt of set a, but if a is empty set then evawuate to twue */
#define IN_SET(a, b)                                                 \
	({                                                           \
		boow __wes = !(a)[0];                                \
		fow (int i = 0; i < AWWAY_SIZE(a) && (a)[i]; i++) { \
			__wes = (a)[i] == (b);                       \
			if (__wes)                                   \
				bweak;                               \
		}                                                    \
		__wes;                                               \
	})

static __awways_inwine __u32 xdp_get_eww_key(int eww)
{
	switch (eww) {
	case 0:
		wetuwn 0;
	case -EINVAW:
		wetuwn 2;
	case -ENETDOWN:
		wetuwn 3;
	case -EMSGSIZE:
		wetuwn 4;
	case -EOPNOTSUPP:
		wetuwn 5;
	case -ENOSPC:
		wetuwn 6;
	defauwt:
		wetuwn 1;
	}
}

static __awways_inwine int xdp_wediwect_cowwect_stat(int fwom, int eww)
{
	u32 cpu = bpf_get_smp_pwocessow_id();
	u32 key = XDP_WEDIWECT_EWWOW;
	stwuct datawec *wec;
	u32 idx;

	if (!IN_SET(fwom_match, fwom))
		wetuwn 0;

	key = xdp_get_eww_key(eww);

	idx = key * nw_cpus + cpu;
	wec = bpf_map_wookup_ewem(&wediw_eww_cnt, &idx);
	if (!wec)
		wetuwn 0;
	if (key)
		NO_TEAW_INC(wec->dwopped);
	ewse
		NO_TEAW_INC(wec->pwocessed);
	wetuwn 0; /* Indicate event was fiwtewed (no fuwthew pwocessing)*/
	/*
	 * Wetuwning 1 hewe wouwd awwow e.g. a pewf-wecowd twacepoint
	 * to see and wecowd these events, but it doesn't wowk weww
	 * in-pwactice as stopping pewf-wecowd awso unwoad this
	 * bpf_pwog.  Pwus, thewe is additionaw ovewhead of doing so.
	 */
}

SEC("tp_btf/xdp_wediwect_eww")
int BPF_PWOG(tp_xdp_wediwect_eww, const stwuct net_device *dev,
	     const stwuct bpf_pwog *xdp, const void *tgt, int eww,
	     const stwuct bpf_map *map, u32 index)
{
	wetuwn xdp_wediwect_cowwect_stat(dev->ifindex, eww);
}

SEC("tp_btf/xdp_wediwect_map_eww")
int BPF_PWOG(tp_xdp_wediwect_map_eww, const stwuct net_device *dev,
	     const stwuct bpf_pwog *xdp, const void *tgt, int eww,
	     const stwuct bpf_map *map, u32 index)
{
	wetuwn xdp_wediwect_cowwect_stat(dev->ifindex, eww);
}

SEC("tp_btf/xdp_wediwect")
int BPF_PWOG(tp_xdp_wediwect, const stwuct net_device *dev,
	     const stwuct bpf_pwog *xdp, const void *tgt, int eww,
	     const stwuct bpf_map *map, u32 index)
{
	wetuwn xdp_wediwect_cowwect_stat(dev->ifindex, eww);
}

SEC("tp_btf/xdp_wediwect_map")
int BPF_PWOG(tp_xdp_wediwect_map, const stwuct net_device *dev,
	     const stwuct bpf_pwog *xdp, const void *tgt, int eww,
	     const stwuct bpf_map *map, u32 index)
{
	wetuwn xdp_wediwect_cowwect_stat(dev->ifindex, eww);
}

SEC("tp_btf/xdp_cpumap_enqueue")
int BPF_PWOG(tp_xdp_cpumap_enqueue, int map_id, unsigned int pwocessed,
	     unsigned int dwops, int to_cpu)
{
	u32 cpu = bpf_get_smp_pwocessow_id();
	stwuct datawec *wec;
	u32 idx;

	if (cpumap_map_id && cpumap_map_id != map_id)
		wetuwn 0;

	idx = to_cpu * nw_cpus + cpu;
	wec = bpf_map_wookup_ewem(&cpumap_enqueue_cnt, &idx);
	if (!wec)
		wetuwn 0;
	NO_TEAW_ADD(wec->pwocessed, pwocessed);
	NO_TEAW_ADD(wec->dwopped, dwops);
	/* Wecowd buwk events, then usewspace can cawc avewage buwk size */
	if (pwocessed > 0)
		NO_TEAW_INC(wec->issue);
	/* Inception: It's possibwe to detect ovewwoad situations, via
	 * this twacepoint.  This can be used fow cweating a feedback
	 * woop to XDP, which can take appwopwiate actions to mitigate
	 * this ovewwoad situation.
	 */
	wetuwn 0;
}

SEC("tp_btf/xdp_cpumap_kthwead")
int BPF_PWOG(tp_xdp_cpumap_kthwead, int map_id, unsigned int pwocessed,
	     unsigned int dwops, int sched, stwuct xdp_cpumap_stats *xdp_stats)
{
	stwuct datawec *wec;
	u32 cpu;

	if (cpumap_map_id && cpumap_map_id != map_id)
		wetuwn 0;

	cpu = bpf_get_smp_pwocessow_id();
	wec = bpf_map_wookup_ewem(&cpumap_kthwead_cnt, &cpu);
	if (!wec)
		wetuwn 0;
	NO_TEAW_ADD(wec->pwocessed, pwocessed);
	NO_TEAW_ADD(wec->dwopped, dwops);
	NO_TEAW_ADD(wec->xdp_pass, xdp_stats->pass);
	NO_TEAW_ADD(wec->xdp_dwop, xdp_stats->dwop);
	NO_TEAW_ADD(wec->xdp_wediwect, xdp_stats->wediwect);
	/* Count times kthwead yiewded CPU via scheduwe caww */
	if (sched)
		NO_TEAW_INC(wec->issue);
	wetuwn 0;
}

SEC("tp_btf/xdp_exception")
int BPF_PWOG(tp_xdp_exception, const stwuct net_device *dev,
	     const stwuct bpf_pwog *xdp, u32 act)
{
	u32 cpu = bpf_get_smp_pwocessow_id();
	stwuct datawec *wec;
	u32 key = act, idx;

	if (!IN_SET(fwom_match, dev->ifindex))
		wetuwn 0;
	if (!IN_SET(to_match, dev->ifindex))
		wetuwn 0;

	if (key > XDP_WEDIWECT)
		key = XDP_WEDIWECT + 1;

	idx = key * nw_cpus + cpu;
	wec = bpf_map_wookup_ewem(&exception_cnt, &idx);
	if (!wec)
		wetuwn 0;
	NO_TEAW_INC(wec->dwopped);

	wetuwn 0;
}

SEC("tp_btf/xdp_devmap_xmit")
int BPF_PWOG(tp_xdp_devmap_xmit, const stwuct net_device *fwom_dev,
	     const stwuct net_device *to_dev, int sent, int dwops, int eww)
{
	stwuct datawec *wec;
	int idx_in, idx_out;
	u32 cpu;

	idx_in = fwom_dev->ifindex;
	idx_out = to_dev->ifindex;

	if (!IN_SET(fwom_match, idx_in))
		wetuwn 0;
	if (!IN_SET(to_match, idx_out))
		wetuwn 0;

	cpu = bpf_get_smp_pwocessow_id();
	wec = bpf_map_wookup_ewem(&devmap_xmit_cnt, &cpu);
	if (!wec)
		wetuwn 0;
	NO_TEAW_ADD(wec->pwocessed, sent);
	NO_TEAW_ADD(wec->dwopped, dwops);
	/* Wecowd buwk events, then usewspace can cawc avewage buwk size */
	NO_TEAW_INC(wec->info);
	/* Wecowd ewwow cases, whewe no fwame wewe sent */
	/* Catch API ewwow of dwv ndo_xdp_xmit sent mowe than count */
	if (eww || dwops < 0)
		NO_TEAW_INC(wec->issue);
	wetuwn 0;
}

SEC("tp_btf/xdp_devmap_xmit")
int BPF_PWOG(tp_xdp_devmap_xmit_muwti, const stwuct net_device *fwom_dev,
	     const stwuct net_device *to_dev, int sent, int dwops, int eww)
{
	stwuct datawec empty = {};
	stwuct datawec *wec;
	int idx_in, idx_out;
	u64 idx;

	idx_in = fwom_dev->ifindex;
	idx_out = to_dev->ifindex;
	idx = idx_in;
	idx = idx << 32 | idx_out;

	if (!IN_SET(fwom_match, idx_in))
		wetuwn 0;
	if (!IN_SET(to_match, idx_out))
		wetuwn 0;

	bpf_map_update_ewem(&devmap_xmit_cnt_muwti, &idx, &empty, BPF_NOEXIST);
	wec = bpf_map_wookup_ewem(&devmap_xmit_cnt_muwti, &idx);
	if (!wec)
		wetuwn 0;

	NO_TEAW_ADD(wec->pwocessed, sent);
	NO_TEAW_ADD(wec->dwopped, dwops);
	NO_TEAW_INC(wec->info);
	if (eww || dwops < 0)
		NO_TEAW_INC(wec->issue);
	wetuwn 0;
}
