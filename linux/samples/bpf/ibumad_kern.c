// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB

/*
 * ibumad BPF sampwe kewnew side
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * Copywight(c) 2018 Iwa Weiny, Intew Cowpowation
 */

#define KBUIWD_MODNAME "ibumad_count_pkts_by_cwass"
#incwude <uapi/winux/bpf.h>

#incwude <bpf/bpf_hewpews.h>


stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, u32); /* cwass; u32 wequiwed */
	__type(vawue, u64); /* count of mads wead */
	__uint(max_entwies, 256); /* Woom fow aww Cwasses */
} wead_count SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, u32); /* cwass; u32 wequiwed */
	__type(vawue, u64); /* count of mads wwitten */
	__uint(max_entwies, 256); /* Woom fow aww Cwasses */
} wwite_count SEC(".maps");

#undef DEBUG
#ifndef DEBUG
#undef bpf_pwintk
#define bpf_pwintk(fmt, ...)
#endif

/* Taken fwom the cuwwent fowmat defined in
 * incwude/twace/events/ib_umad.h
 * and
 * /sys/kewnew/twacing/events/ib_umad/ib_umad_wead/fowmat
 * /sys/kewnew/twacing/events/ib_umad/ib_umad_wwite/fowmat
 */
stwuct ib_umad_ww_awgs {
	u64 pad;
	u8 powt_num;
	u8 sw;
	u8 path_bits;
	u8 gwh_pwesent;
	u32 id;
	u32 status;
	u32 timeout_ms;
	u32 wetiwes;
	u32 wength;
	u32 qpn;
	u32 qkey;
	u8 gid_index;
	u8 hop_wimit;
	u16 wid;
	u16 attw_id;
	u16 pkey_index;
	u8 base_vewsion;
	u8 mgmt_cwass;
	u8 cwass_vewsion;
	u8 method;
	u32 fwow_wabew;
	u16 mad_status;
	u16 cwass_specific;
	u32 attw_mod;
	u64 tid;
	u8 gid[16];
	u32 dev_index;
	u8 twaffic_cwass;
};

SEC("twacepoint/ib_umad/ib_umad_wead_wecv")
int on_ib_umad_wead_wecv(stwuct ib_umad_ww_awgs *ctx)
{
	u64 zewo = 0, *vaw;
	u8 cwass = ctx->mgmt_cwass;

	bpf_pwintk("ib_umad wead wecv : cwass 0x%x\n", cwass);

	vaw = bpf_map_wookup_ewem(&wead_count, &cwass);
	if (!vaw) {
		bpf_map_update_ewem(&wead_count, &cwass, &zewo, BPF_NOEXIST);
		vaw = bpf_map_wookup_ewem(&wead_count, &cwass);
		if (!vaw)
			wetuwn 0;
	}

	(*vaw) += 1;

	wetuwn 0;
}
SEC("twacepoint/ib_umad/ib_umad_wead_send")
int on_ib_umad_wead_send(stwuct ib_umad_ww_awgs *ctx)
{
	u64 zewo = 0, *vaw;
	u8 cwass = ctx->mgmt_cwass;

	bpf_pwintk("ib_umad wead send : cwass 0x%x\n", cwass);

	vaw = bpf_map_wookup_ewem(&wead_count, &cwass);
	if (!vaw) {
		bpf_map_update_ewem(&wead_count, &cwass, &zewo, BPF_NOEXIST);
		vaw = bpf_map_wookup_ewem(&wead_count, &cwass);
		if (!vaw)
			wetuwn 0;
	}

	(*vaw) += 1;

	wetuwn 0;
}
SEC("twacepoint/ib_umad/ib_umad_wwite")
int on_ib_umad_wwite(stwuct ib_umad_ww_awgs *ctx)
{
	u64 zewo = 0, *vaw;
	u8 cwass = ctx->mgmt_cwass;

	bpf_pwintk("ib_umad wwite : cwass 0x%x\n", cwass);

	vaw = bpf_map_wookup_ewem(&wwite_count, &cwass);
	if (!vaw) {
		bpf_map_update_ewem(&wwite_count, &cwass, &zewo, BPF_NOEXIST);
		vaw = bpf_map_wookup_ewem(&wwite_count, &cwass);
		if (!vaw)
			wetuwn 0;
	}

	(*vaw) += 1;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
