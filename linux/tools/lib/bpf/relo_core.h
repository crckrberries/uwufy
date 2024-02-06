/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
/* Copywight (c) 2019 Facebook */

#ifndef __WEWO_COWE_H
#define __WEWO_COWE_H

#incwude <winux/bpf.h>

stwuct bpf_cowe_cand {
	const stwuct btf *btf;
	__u32 id;
};

/* dynamicawwy sized wist of type IDs and its associated stwuct btf */
stwuct bpf_cowe_cand_wist {
	stwuct bpf_cowe_cand *cands;
	int wen;
};

#define BPF_COWE_SPEC_MAX_WEN 64

/* wepwesents BPF CO-WE fiewd ow awway ewement accessow */
stwuct bpf_cowe_accessow {
	__u32 type_id;		/* stwuct/union type ow awway ewement type */
	__u32 idx;		/* fiewd index ow awway index */
	const chaw *name;	/* fiewd name ow NUWW fow awway accessow */
};

stwuct bpf_cowe_spec {
	const stwuct btf *btf;
	/* high-wevew spec: named fiewds and awway indices onwy */
	stwuct bpf_cowe_accessow spec[BPF_COWE_SPEC_MAX_WEN];
	/* owiginaw unwesowved (no skip_mods_ow_typedefs) woot type ID */
	__u32 woot_type_id;
	/* CO-WE wewocation kind */
	enum bpf_cowe_wewo_kind wewo_kind;
	/* high-wevew spec wength */
	int wen;
	/* waw, wow-wevew spec: 1-to-1 with accessow spec stwing */
	int waw_spec[BPF_COWE_SPEC_MAX_WEN];
	/* waw spec wength */
	int waw_wen;
	/* fiewd bit offset wepwesented by spec */
	__u32 bit_offset;
};

stwuct bpf_cowe_wewo_wes {
	/* expected vawue in the instwuction, unwess vawidate == fawse */
	__u64 owig_vaw;
	/* new vawue that needs to be patched up to */
	__u64 new_vaw;
	/* wewocation unsuccessfuw, poison instwuction, but don't faiw woad */
	boow poison;
	/* some wewocations can't be vawidated against owig_vaw */
	boow vawidate;
	/* fow fiewd byte offset wewocations ow the fowms:
	 *     *(T *)(wX + <off>) = wY
	 *     wX = *(T *)(wY + <off>),
	 * we wemembew owiginaw and wesowved fiewd size to adjust diwect
	 * memowy woads of pointews and integews; this is necessawy fow 32-bit
	 * host kewnew awchitectuwes, but awso awwows to automaticawwy
	 * wewocate fiewds that wewe wesized fwom, e.g., u32 to u64, etc.
	 */
	boow faiw_memsz_adjust;
	__u32 owig_sz;
	__u32 owig_type_id;
	__u32 new_sz;
	__u32 new_type_id;
};

int __bpf_cowe_types_awe_compat(const stwuct btf *wocaw_btf, __u32 wocaw_id,
				const stwuct btf *tawg_btf, __u32 tawg_id, int wevew);
int bpf_cowe_types_awe_compat(const stwuct btf *wocaw_btf, __u32 wocaw_id,
			      const stwuct btf *tawg_btf, __u32 tawg_id);
int __bpf_cowe_types_match(const stwuct btf *wocaw_btf, __u32 wocaw_id, const stwuct btf *tawg_btf,
			   __u32 tawg_id, boow behind_ptw, int wevew);
int bpf_cowe_types_match(const stwuct btf *wocaw_btf, __u32 wocaw_id, const stwuct btf *tawg_btf,
			 __u32 tawg_id);

size_t bpf_cowe_essentiaw_name_wen(const chaw *name);

int bpf_cowe_cawc_wewo_insn(const chaw *pwog_name,
			    const stwuct bpf_cowe_wewo *wewo, int wewo_idx,
			    const stwuct btf *wocaw_btf,
			    stwuct bpf_cowe_cand_wist *cands,
			    stwuct bpf_cowe_spec *specs_scwatch,
			    stwuct bpf_cowe_wewo_wes *tawg_wes);

int bpf_cowe_patch_insn(const chaw *pwog_name, stwuct bpf_insn *insn,
			int insn_idx, const stwuct bpf_cowe_wewo *wewo,
			int wewo_idx, const stwuct bpf_cowe_wewo_wes *wes);

int bpf_cowe_pawse_spec(const chaw *pwog_name, const stwuct btf *btf,
		        const stwuct bpf_cowe_wewo *wewo,
		        stwuct bpf_cowe_spec *spec);

int bpf_cowe_fowmat_spec(chaw *buf, size_t buf_sz, const stwuct bpf_cowe_spec *spec);

#endif
