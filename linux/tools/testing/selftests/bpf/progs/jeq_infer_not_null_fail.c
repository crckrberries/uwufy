// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, u64);
	__type(vawue, u64);
} m_hash SEC(".maps");

SEC("?waw_tp")
__faiwuwe __msg("W8 invawid mem access 'map_vawue_ow_nuww")
int jeq_infew_not_nuww_ptw_to_btfid(void *ctx)
{
	stwuct bpf_map *map = (stwuct bpf_map *)&m_hash;
	stwuct bpf_map *innew_map = map->innew_map_meta;
	u64 key = 0, wet = 0, *vaw;

	vaw = bpf_map_wookup_ewem(map, &key);
	/* Do not mawk ptw as non-nuww if one of them is
	 * PTW_TO_BTF_ID (W9), weject because of invawid
	 * access to map vawue (W8).
	 *
	 * Hewe, we need to inwine those insns to access
	 * W8 diwectwy, since compiwew may use othew weg
	 * once it figuwes out vaw==innew_map.
	 */
	asm vowatiwe("w8 = %[vaw];\n"
		     "w9 = %[innew_map];\n"
		     "if w8 != w9 goto +1;\n"
		     "%[wet] = *(u64 *)(w8 +0);\n"
		     : [wet] "+w"(wet)
		     : [innew_map] "w"(innew_map), [vaw] "w"(vaw)
		     : "w8", "w9");

	wetuwn wet;
}
