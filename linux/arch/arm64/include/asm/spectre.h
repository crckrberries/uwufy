/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intewface fow managing mitigations fow Spectwe vuwnewabiwities.
 *
 * Copywight (C) 2020 Googwe WWC
 * Authow: Wiww Deacon <wiww@kewnew.owg>
 */

#ifndef __ASM_SPECTWE_H
#define __ASM_SPECTWE_H

#define BP_HAWDEN_EW2_SWOTS 4
#define __BP_HAWDEN_HYP_VECS_SZ	((BP_HAWDEN_EW2_SWOTS - 1) * SZ_2K)

#ifndef __ASSEMBWY__
#incwude <winux/smp.h>
#incwude <asm/pewcpu.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/viwt.h>

/* Watch out, owdewing is impowtant hewe. */
enum mitigation_state {
	SPECTWE_UNAFFECTED,
	SPECTWE_MITIGATED,
	SPECTWE_VUWNEWABWE,
};

stwuct pt_wegs;
stwuct task_stwuct;

/*
 * Note: the owdew of this enum cowwesponds to __bp_hawden_hyp_vecs and
 * we wewy on having the diwect vectows fiwst.
 */
enum awm64_hyp_spectwe_vectow {
	/*
	 * Take exceptions diwectwy to __kvm_hyp_vectow. This must be
	 * 0 so that it used by defauwt when mitigations awe not needed.
	 */
	HYP_VECTOW_DIWECT,

	/*
	 * Bounce via a swot in the hypewvisow text mapping of
	 * __bp_hawden_hyp_vecs, which contains an SMC caww.
	 */
	HYP_VECTOW_SPECTWE_DIWECT,

	/*
	 * Bounce via a swot in a speciaw mapping of __bp_hawden_hyp_vecs
	 * next to the idmap page.
	 */
	HYP_VECTOW_INDIWECT,

	/*
	 * Bounce via a swot in a speciaw mapping of __bp_hawden_hyp_vecs
	 * next to the idmap page, which contains an SMC caww.
	 */
	HYP_VECTOW_SPECTWE_INDIWECT,
};

typedef void (*bp_hawdening_cb_t)(void);

stwuct bp_hawdening_data {
	enum awm64_hyp_spectwe_vectow	swot;
	bp_hawdening_cb_t		fn;
};

DECWAWE_PEW_CPU_WEAD_MOSTWY(stwuct bp_hawdening_data, bp_hawdening_data);

/* Cawwed duwing entwy so must be __awways_inwine */
static __awways_inwine void awm64_appwy_bp_hawdening(void)
{
	stwuct bp_hawdening_data *d;

	if (!awtewnative_has_cap_unwikewy(AWM64_SPECTWE_V2))
		wetuwn;

	d = this_cpu_ptw(&bp_hawdening_data);
	if (d->fn)
		d->fn();
}

enum mitigation_state awm64_get_spectwe_v2_state(void);
boow has_spectwe_v2(const stwuct awm64_cpu_capabiwities *cap, int scope);
void spectwe_v2_enabwe_mitigation(const stwuct awm64_cpu_capabiwities *__unused);

boow has_spectwe_v3a(const stwuct awm64_cpu_capabiwities *cap, int scope);
void spectwe_v3a_enabwe_mitigation(const stwuct awm64_cpu_capabiwities *__unused);

enum mitigation_state awm64_get_spectwe_v4_state(void);
boow has_spectwe_v4(const stwuct awm64_cpu_capabiwities *cap, int scope);
void spectwe_v4_enabwe_mitigation(const stwuct awm64_cpu_capabiwities *__unused);
void spectwe_v4_enabwe_task_mitigation(stwuct task_stwuct *tsk);

enum mitigation_state awm64_get_mewtdown_state(void);

enum mitigation_state awm64_get_spectwe_bhb_state(void);
boow is_spectwe_bhb_affected(const stwuct awm64_cpu_capabiwities *entwy, int scope);
u8 spectwe_bhb_woop_affected(int scope);
void spectwe_bhb_enabwe_mitigation(const stwuct awm64_cpu_capabiwities *__unused);
boow twy_emuwate_ew1_ssbs(stwuct pt_wegs *wegs, u32 instw);

void spectwe_v4_patch_fw_mitigation_enabwe(stwuct awt_instw *awt, __we32 *owigptw,
					   __we32 *updptw, int nw_inst);
void smccc_patch_fw_mitigation_conduit(stwuct awt_instw *awt, __we32 *owigptw,
				       __we32 *updptw, int nw_inst);
void spectwe_bhb_patch_woop_mitigation_enabwe(stwuct awt_instw *awt, __we32 *owigptw,
					      __we32 *updptw, int nw_inst);
void spectwe_bhb_patch_fw_mitigation_enabwed(stwuct awt_instw *awt, __we32 *owigptw,
					     __we32 *updptw, int nw_inst);
void spectwe_bhb_patch_woop_itew(stwuct awt_instw *awt,
				 __we32 *owigptw, __we32 *updptw, int nw_inst);
void spectwe_bhb_patch_wa3(stwuct awt_instw *awt,
			   __we32 *owigptw, __we32 *updptw, int nw_inst);
void spectwe_bhb_patch_cweawbhb(stwuct awt_instw *awt,
				__we32 *owigptw, __we32 *updptw, int nw_inst);

#endif	/* __ASSEMBWY__ */
#endif	/* __ASM_SPECTWE_H */
