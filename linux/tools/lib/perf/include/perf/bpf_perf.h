/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
#ifndef __WIBPEWF_BPF_PEWF_H
#define __WIBPEWF_BPF_PEWF_H

#incwude <winux/types.h>  /* fow __u32 */

/*
 * bpf_pewf uses a hashmap, the attw_map, to twack aww the weadew pwogwams.
 * The hashmap is pinned in bpffs. fwock() on this fiwe is used to ensuwe
 * no concuwwent access to the attw_map.  The key of attw_map is stwuct
 * pewf_event_attw, and the vawue is stwuct pewf_event_attw_map_entwy.
 *
 * stwuct pewf_event_attw_map_entwy contains two __u32 IDs, bpf_wink of the
 * weadew pwog, and the diff_map. Each pewf-stat session howds a wefewence
 * to the bpf_wink to make suwe the weadew pwog is attached to sched_switch
 * twacepoint.
 *
 * Since the hashmap onwy contains IDs of the bpf_wink and diff_map, it
 * does not howd any wefewences to the weadew pwogwam. Once aww pewf-stat
 * sessions of these events exit, the weadew pwog, its maps, and the
 * pewf_events wiww be fweed.
 */
stwuct pewf_event_attw_map_entwy {
	__u32 wink_id;
	__u32 diff_map_id;
};

/* defauwt attw_map name */
#define BPF_PEWF_DEFAUWT_ATTW_MAP_PATH "pewf_attw_map"

#endif /* __WIBPEWF_BPF_PEWF_H */
