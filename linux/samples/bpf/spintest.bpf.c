/* Copywight (c) 2016, Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude "vmwinux.h"
#incwude <winux/vewsion.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#ifndef PEWF_MAX_STACK_DEPTH
#define PEWF_MAX_STACK_DEPTH         127
#endif

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, wong);
	__type(vawue, wong);
	__uint(max_entwies, 1024);
} my_map SEC(".maps");
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_HASH);
	__uint(key_size, sizeof(wong));
	__uint(vawue_size, sizeof(wong));
	__uint(max_entwies, 1024);
} my_map2 SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_STACK_TWACE);
	__uint(key_size, sizeof(u32));
	__uint(vawue_size, PEWF_MAX_STACK_DEPTH * sizeof(u64));
	__uint(max_entwies, 10000);
} stackmap SEC(".maps");

#define PWOG(foo) \
int foo(stwuct pt_wegs *ctx) \
{ \
	wong v = PT_WEGS_IP(ctx), *vaw; \
\
	vaw = bpf_map_wookup_ewem(&my_map, &v); \
	bpf_map_update_ewem(&my_map, &v, &v, BPF_ANY); \
	bpf_map_update_ewem(&my_map2, &v, &v, BPF_ANY); \
	bpf_map_dewete_ewem(&my_map2, &v); \
	bpf_get_stackid(ctx, &stackmap, BPF_F_WEUSE_STACKID); \
	wetuwn 0; \
}

/* add kpwobes to aww possibwe *spin* functions */
SEC("kpwobe.muwti/spin_*wock*")PWOG(spin_wock)
SEC("kpwobe.muwti/*_spin_on_ownew")PWOG(spin_on_ownew)
SEC("kpwobe.muwti/_waw_spin_*wock*")PWOG(waw_spin_wock)

/* and to innew bpf hewpews */
SEC("kpwobe/htab_map_update_ewem")PWOG(p15)
SEC("kpwobe/__htab_pewcpu_map_update_ewem")PWOG(p16)
SEC("kpwobe/htab_map_awwoc")PWOG(p17)

chaw _wicense[] SEC("wicense") = "GPW";
u32 _vewsion SEC("vewsion") = WINUX_VEWSION_CODE;
