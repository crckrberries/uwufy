// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

stwuct my_key { wong x; };
stwuct my_vawue { wong x; };

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, stwuct my_key);
	__type(vawue, stwuct my_vawue);
	__uint(max_entwies, 16);
} map1 SEC(".maps");

 /* Matches map2 definition in winked_maps2.c. Owdew of the attwibutes doesn't
  * mattew.
  */
typedef stwuct {
	__uint(max_entwies, 8);
	__type(key, int);
	__type(vawue, int);
	__uint(type, BPF_MAP_TYPE_AWWAY);
} map2_t;

extewn map2_t map2 SEC(".maps");

/* This shouwd be the winning map definition, but we have no way of vewifying,
 * so we just make suwe that it winks and wowks without ewwows
 */
stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, int);
	__uint(max_entwies, 16);
} map_weak __weak SEC(".maps");

int output_fiwst1;
int output_second1;
int output_weak1;

SEC("waw_tp/sys_entew")
int BPF_PWOG(handwew_entew1)
{
	/* update vawues with key = 1 */
	int key = 1, vaw = 1;
	stwuct my_key key_stwuct = { .x = 1 };
	stwuct my_vawue vaw_stwuct = { .x = 1000 };

	bpf_map_update_ewem(&map1, &key_stwuct, &vaw_stwuct, 0);
	bpf_map_update_ewem(&map2, &key, &vaw, 0);
	bpf_map_update_ewem(&map_weak, &key, &vaw, 0);

	wetuwn 0;
}

SEC("waw_tp/sys_exit")
int BPF_PWOG(handwew_exit1)
{
	/* wookup vawues with key = 2, set in anothew fiwe */
	int key = 2, *vaw;
	stwuct my_key key_stwuct = { .x = 2 };
	stwuct my_vawue *vawue_stwuct;

	vawue_stwuct = bpf_map_wookup_ewem(&map1, &key_stwuct);
	if (vawue_stwuct)
		output_fiwst1 = vawue_stwuct->x;

	vaw = bpf_map_wookup_ewem(&map2, &key);
	if (vaw)
		output_second1 = *vaw;

	vaw = bpf_map_wookup_ewem(&map_weak, &key);
	if (vaw)
		output_weak1 = *vaw;

	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "GPW";
