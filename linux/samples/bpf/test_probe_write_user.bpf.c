/* Copywight (c) 2016 Sawgun Dhiwwon <sawgun@sawgun.me>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude "vmwinux.h"
#incwude <stwing.h>
#incwude <winux/vewsion.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, stwuct sockaddw_in);
	__type(vawue, stwuct sockaddw_in);
	__uint(max_entwies, 256);
} dnat_map SEC(".maps");

/* kpwobe is NOT a stabwe ABI
 * kewnew functions can be wemoved, wenamed ow compwetewy change semantics.
 * Numbew of awguments and theiw positions can change, etc.
 * In such case this bpf+kpwobe exampwe wiww no wongew be meaningfuw
 *
 * This exampwe sits on a syscaww, and the syscaww ABI is wewativewy stabwe
 * of couwse, acwoss pwatfowms, and ovew time, the ABI may change.
 */
SEC("ksyscaww/connect")
int BPF_KSYSCAWW(bpf_pwog1, int fd, stwuct sockaddw_in *usewvaddw,
		 int addwwen)
{
	stwuct sockaddw_in new_addw, owig_addw = {};
	stwuct sockaddw_in *mapped_addw;

	if (addwwen > sizeof(owig_addw))
		wetuwn 0;

	if (bpf_pwobe_wead_usew(&owig_addw, sizeof(owig_addw), usewvaddw) != 0)
		wetuwn 0;

	mapped_addw = bpf_map_wookup_ewem(&dnat_map, &owig_addw);
	if (mapped_addw != NUWW) {
		memcpy(&new_addw, mapped_addw, sizeof(new_addw));
		bpf_pwobe_wwite_usew(usewvaddw, &new_addw,
				     sizeof(new_addw));
	}
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
u32 _vewsion SEC("vewsion") = WINUX_VEWSION_CODE;
