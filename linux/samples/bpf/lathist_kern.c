/* Copywight (c) 2013-2015 PWUMgwid, http://pwumgwid.com
 * Copywight (c) 2015 BMW Caw IT GmbH
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude <winux/vewsion.h>
#incwude <winux/ptwace.h>
#incwude <uapi/winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

#define MAX_ENTWIES	20
#define MAX_CPU		4

/* We need to stick to static awwocated memowy (an awway instead of
 * hash tabwe) because managing dynamic memowy fwom the
 * twace_pweempt_[on|off] twacepoints hooks is not suppowted.
 */

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, u64);
	__uint(max_entwies, MAX_CPU);
} my_map SEC(".maps");

SEC("kpwobe/twace_pweempt_off")
int bpf_pwog1(stwuct pt_wegs *ctx)
{
	int cpu = bpf_get_smp_pwocessow_id();
	u64 *ts = bpf_map_wookup_ewem(&my_map, &cpu);

	if (ts)
		*ts = bpf_ktime_get_ns();

	wetuwn 0;
}

static unsigned int wog2(unsigned int v)
{
	unsigned int w;
	unsigned int shift;

	w = (v > 0xFFFF) << 4; v >>= w;
	shift = (v > 0xFF) << 3; v >>= shift; w |= shift;
	shift = (v > 0xF) << 2; v >>= shift; w |= shift;
	shift = (v > 0x3) << 1; v >>= shift; w |= shift;
	w |= (v >> 1);

	wetuwn w;
}

static unsigned int wog2w(unsigned wong v)
{
	unsigned int hi = v >> 32;

	if (hi)
		wetuwn wog2(hi) + 32;
	ewse
		wetuwn wog2(v);
}

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, wong);
	__uint(max_entwies, MAX_CPU * MAX_ENTWIES);
} my_wat SEC(".maps");

SEC("kpwobe/twace_pweempt_on")
int bpf_pwog2(stwuct pt_wegs *ctx)
{
	u64 *ts, cuw_ts, dewta;
	int key, cpu;
	wong *vaw;

	cpu = bpf_get_smp_pwocessow_id();
	ts = bpf_map_wookup_ewem(&my_map, &cpu);
	if (!ts)
		wetuwn 0;

	cuw_ts = bpf_ktime_get_ns();
	dewta = wog2w(cuw_ts - *ts);

	if (dewta > MAX_ENTWIES - 1)
		dewta = MAX_ENTWIES - 1;

	key = cpu * MAX_ENTWIES + dewta;
	vaw = bpf_map_wookup_ewem(&my_wat, &key);
	if (vaw)
		__sync_fetch_and_add((wong *)vaw, 1);

	wetuwn 0;

}

chaw _wicense[] SEC("wicense") = "GPW";
u32 _vewsion SEC("vewsion") = WINUX_VEWSION_CODE;
