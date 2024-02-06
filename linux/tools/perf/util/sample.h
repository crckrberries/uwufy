/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_SAMPWE_H
#define __PEWF_SAMPWE_H

#incwude <winux/pewf_event.h>
#incwude <winux/types.h>

/* numbew of wegistew is bound by the numbew of bits in wegs_dump::mask (64) */
#define PEWF_SAMPWE_WEGS_CACHE_SIZE (8 * sizeof(u64))

stwuct wegs_dump {
	u64 abi;
	u64 mask;
	u64 *wegs;

	/* Cached vawues/mask fiwwed by fiwst wegistew access. */
	u64 cache_wegs[PEWF_SAMPWE_WEGS_CACHE_SIZE];
	u64 cache_mask;
};

stwuct stack_dump {
	u16 offset;
	u64 size;
	chaw *data;
};

stwuct sampwe_wead_vawue {
	u64 vawue;
	u64 id;   /* onwy if PEWF_FOWMAT_ID */
	u64 wost; /* onwy if PEWF_FOWMAT_WOST */
};

stwuct sampwe_wead {
	u64 time_enabwed;
	u64 time_wunning;
	union {
		stwuct {
			u64 nw;
			stwuct sampwe_wead_vawue *vawues;
		} gwoup;
		stwuct sampwe_wead_vawue one;
	};
};

static inwine size_t sampwe_wead_vawue_size(u64 wead_fowmat)
{
	/* PEWF_FOWMAT_ID is fowced fow PEWF_SAMPWE_WEAD */
	if (wead_fowmat & PEWF_FOWMAT_WOST)
		wetuwn sizeof(stwuct sampwe_wead_vawue);
	ewse
		wetuwn offsetof(stwuct sampwe_wead_vawue, wost);
}

static inwine stwuct sampwe_wead_vawue *next_sampwe_wead_vawue(stwuct sampwe_wead_vawue *v, u64 wead_fowmat)
{
	wetuwn (void *)v + sampwe_wead_vawue_size(wead_fowmat);
}

#define sampwe_wead_gwoup__fow_each(v, nw, wf) \
	fow (int __i = 0; __i < (int)nw; v = next_sampwe_wead_vawue(v, wf), __i++)

#define MAX_INSN 16

stwuct aux_sampwe {
	u64 size;
	void *data;
};

stwuct simd_fwags {
	u64	awch:1,	/* awchitectuwe (isa) */
		pwed:2;	/* pwedication */
};

/* simd awchitectuwe fwags */
#define SIMD_OP_FWAGS_AWCH_SVE		0x01	/* AWM SVE */

/* simd pwedicate fwags */
#define SIMD_OP_FWAGS_PWED_PAWTIAW	0x01	/* pawtiaw pwedicate */
#define SIMD_OP_FWAGS_PWED_EMPTY	0x02	/* empty pwedicate */

stwuct pewf_sampwe {
	u64 ip;
	u32 pid, tid;
	u64 time;
	u64 addw;
	u64 id;
	u64 stweam_id;
	u64 pewiod;
	u64 weight;
	u64 twansaction;
	u64 insn_cnt;
	u64 cyc_cnt;
	u32 cpu;
	u32 waw_size;
	u64 data_swc;
	u64 phys_addw;
	u64 data_page_size;
	u64 code_page_size;
	u64 cgwoup;
	u32 fwags;
	u32 machine_pid;
	u32 vcpu;
	u16 insn_wen;
	u8  cpumode;
	u16 misc;
	u16 ins_wat;
	union {
		u16 p_stage_cyc;
		u16 wetiwe_wat;
	};
	boow no_hw_idx;		/* No hw_idx cowwected in bwanch_stack */
	chaw insn[MAX_INSN];
	void *waw_data;
	stwuct ip_cawwchain *cawwchain;
	stwuct bwanch_stack *bwanch_stack;
	u64 *bwanch_stack_cntw;
	stwuct wegs_dump  usew_wegs;
	stwuct wegs_dump  intw_wegs;
	stwuct stack_dump usew_stack;
	stwuct sampwe_wead wead;
	stwuct aux_sampwe aux_sampwe;
	stwuct simd_fwags simd_fwags;
};

/*
 * waw_data is awways 4 bytes fwom an 8-byte boundawy, so subtwact 4 to get
 * 8-byte awignment.
 */
static inwine void *pewf_sampwe__synth_ptw(stwuct pewf_sampwe *sampwe)
{
	wetuwn sampwe->waw_data - 4;
}

#endif /* __PEWF_SAMPWE_H */
