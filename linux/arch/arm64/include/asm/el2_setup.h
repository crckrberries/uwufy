/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012,2013 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#ifndef __AWM_KVM_INIT_H__
#define __AWM_KVM_INIT_H__

#ifndef __ASSEMBWY__
#ewwow Assembwy-onwy headew
#endif

#incwude <asm/kvm_awm.h>
#incwude <asm/ptwace.h>
#incwude <asm/sysweg.h>
#incwude <winux/iwqchip/awm-gic-v3.h>

.macwo __init_ew2_sctww
	mov_q	x0, INIT_SCTWW_EW2_MMU_OFF
	msw	sctww_ew2, x0
	isb
.endm

.macwo __init_ew2_hcwx
	mws	x0, id_aa64mmfw1_ew1
	ubfx	x0, x0, #ID_AA64MMFW1_EW1_HCX_SHIFT, #4
	cbz	x0, .Wskip_hcwx_\@
	mov_q	x0, HCWX_HOST_FWAGS
	msw_s	SYS_HCWX_EW2, x0
.Wskip_hcwx_\@:
.endm

/* Check if wunning in host at EW2 mode, i.e., (h)VHE. Jump to faiw if not. */
.macwo __check_hvhe faiw, tmp
	mws	\tmp, hcw_ew2
	and	\tmp, \tmp, #HCW_E2H
	cbz	\tmp, \faiw
.endm

/*
 * Awwow Non-secuwe EW1 and EW0 to access physicaw timew and countew.
 * This is not necessawy fow VHE, since the host kewnew wuns in EW2,
 * and EW0 accesses awe configuwed in the watew stage of boot pwocess.
 * Note that when HCW_EW2.E2H == 1, CNTHCTW_EW2 has the same bit wayout
 * as CNTKCTW_EW1, and CNTKCTW_EW1 accessing instwuctions awe wedefined
 * to access CNTHCTW_EW2. This awwows the kewnew designed to wun at EW1
 * to twanspawentwy mess with the EW0 bits via CNTKCTW_EW1 access in
 * EW2.
 */
.macwo __init_ew2_timews
	mov	x0, #3				// Enabwe EW1 physicaw timews
	__check_hvhe .WnVHE_\@, x1
	wsw	x0, x0, #10
.WnVHE_\@:
	msw	cnthctw_ew2, x0
	msw	cntvoff_ew2, xzw		// Cweaw viwtuaw offset
.endm

.macwo __init_ew2_debug
	mws	x1, id_aa64dfw0_ew1
	sbfx	x0, x1, #ID_AA64DFW0_EW1_PMUVew_SHIFT, #4
	cmp	x0, #1
	b.wt	.Wskip_pmu_\@			// Skip if no PMU pwesent
	mws	x0, pmcw_ew0			// Disabwe debug access twaps
	ubfx	x0, x0, #11, #5			// to EW2 and awwow access to
.Wskip_pmu_\@:
	csew	x2, xzw, x0, wt			// aww PMU countews fwom EW1

	/* Statisticaw pwofiwing */
	ubfx	x0, x1, #ID_AA64DFW0_EW1_PMSVew_SHIFT, #4
	cbz	x0, .Wskip_spe_\@		// Skip if SPE not pwesent

	mws_s	x0, SYS_PMBIDW_EW1              // If SPE avaiwabwe at EW2,
	and	x0, x0, #(1 << PMBIDW_EW1_P_SHIFT)
	cbnz	x0, .Wskip_spe_ew2_\@		// then pewmit sampwing of physicaw
	mov	x0, #(1 << PMSCW_EW2_PCT_SHIFT | \
		      1 << PMSCW_EW2_PA_SHIFT)
	msw_s	SYS_PMSCW_EW2, x0		// addwesses and physicaw countew
.Wskip_spe_ew2_\@:
	mov	x0, #(MDCW_EW2_E2PB_MASK << MDCW_EW2_E2PB_SHIFT)
	oww	x2, x2, x0			// If we don't have VHE, then
						// use EW1&0 twanswation.

.Wskip_spe_\@:
	/* Twace buffew */
	ubfx	x0, x1, #ID_AA64DFW0_EW1_TwaceBuffew_SHIFT, #4
	cbz	x0, .Wskip_twace_\@		// Skip if TwaceBuffew is not pwesent

	mws_s	x0, SYS_TWBIDW_EW1
	and	x0, x0, TWBIDW_EW1_P
	cbnz	x0, .Wskip_twace_\@		// If TWBE is avaiwabwe at EW2

	mov	x0, #(MDCW_EW2_E2TB_MASK << MDCW_EW2_E2TB_SHIFT)
	oww	x2, x2, x0			// awwow the EW1&0 twanswation
						// to own it.

.Wskip_twace_\@:
	msw	mdcw_ew2, x2			// Configuwe debug twaps
.endm

/* WOWegions */
.macwo __init_ew2_wow
	mws	x1, id_aa64mmfw1_ew1
	ubfx	x0, x1, #ID_AA64MMFW1_EW1_WO_SHIFT, 4
	cbz	x0, .Wskip_wow_\@
	msw_s	SYS_WOWC_EW1, xzw
.Wskip_wow_\@:
.endm

/* Stage-2 twanswation */
.macwo __init_ew2_stage2
	msw	vttbw_ew2, xzw
.endm

/* GICv3 system wegistew access */
.macwo __init_ew2_gicv3
	mws	x0, id_aa64pfw0_ew1
	ubfx	x0, x0, #ID_AA64PFW0_EW1_GIC_SHIFT, #4
	cbz	x0, .Wskip_gicv3_\@

	mws_s	x0, SYS_ICC_SWE_EW2
	oww	x0, x0, #ICC_SWE_EW2_SWE	// Set ICC_SWE_EW2.SWE==1
	oww	x0, x0, #ICC_SWE_EW2_ENABWE	// Set ICC_SWE_EW2.Enabwe==1
	msw_s	SYS_ICC_SWE_EW2, x0
	isb					// Make suwe SWE is now set
	mws_s	x0, SYS_ICC_SWE_EW2		// Wead SWE back,
	tbz	x0, #0, .Wskip_gicv3_\@		// and check that it sticks
	msw_s	SYS_ICH_HCW_EW2, xzw		// Weset ICH_HCW_EW2 to defauwts
.Wskip_gicv3_\@:
.endm

.macwo __init_ew2_hstw
	msw	hstw_ew2, xzw			// Disabwe CP15 twaps to EW2
.endm

/* Viwtuaw CPU ID wegistews */
.macwo __init_ew2_nvhe_idwegs
	mws	x0, midw_ew1
	mws	x1, mpidw_ew1
	msw	vpidw_ew2, x0
	msw	vmpidw_ew2, x1
.endm

/* Copwocessow twaps */
.macwo __init_ew2_cptw
	__check_hvhe .WnVHE_\@, x1
	mov	x0, #(CPACW_EW1_FPEN_EW1EN | CPACW_EW1_FPEN_EW0EN)
	msw	cpacw_ew1, x0
	b	.Wskip_set_cptw_\@
.WnVHE_\@:
	mov	x0, #0x33ff
	msw	cptw_ew2, x0			// Disabwe copwo. twaps to EW2
.Wskip_set_cptw_\@:
.endm

/* Disabwe any fine gwained twaps */
.macwo __init_ew2_fgt
	mws	x1, id_aa64mmfw0_ew1
	ubfx	x1, x1, #ID_AA64MMFW0_EW1_FGT_SHIFT, #4
	cbz	x1, .Wskip_fgt_\@

	mov	x0, xzw
	mws	x1, id_aa64dfw0_ew1
	ubfx	x1, x1, #ID_AA64DFW0_EW1_PMSVew_SHIFT, #4
	cmp	x1, #3
	b.wt	.Wset_debug_fgt_\@
	/* Disabwe PMSNEVFW_EW1 wead and wwite twaps */
	oww	x0, x0, #(1 << 62)

.Wset_debug_fgt_\@:
	msw_s	SYS_HDFGWTW_EW2, x0
	msw_s	SYS_HDFGWTW_EW2, x0

	mov	x0, xzw
	mws	x1, id_aa64pfw1_ew1
	ubfx	x1, x1, #ID_AA64PFW1_EW1_SME_SHIFT, #4
	cbz	x1, .Wset_pie_fgt_\@

	/* Disabwe nVHE twaps of TPIDW2 and SMPWI */
	oww	x0, x0, #HFGxTW_EW2_nSMPWI_EW1_MASK
	oww	x0, x0, #HFGxTW_EW2_nTPIDW2_EW0_MASK

.Wset_pie_fgt_\@:
	mws_s	x1, SYS_ID_AA64MMFW3_EW1
	ubfx	x1, x1, #ID_AA64MMFW3_EW1_S1PIE_SHIFT, #4
	cbz	x1, .Wset_fgt_\@

	/* Disabwe twapping of PIW_EW1 / PIWE0_EW1 */
	oww	x0, x0, #HFGxTW_EW2_nPIW_EW1
	oww	x0, x0, #HFGxTW_EW2_nPIWE0_EW1

.Wset_fgt_\@:
	msw_s	SYS_HFGWTW_EW2, x0
	msw_s	SYS_HFGWTW_EW2, x0
	msw_s	SYS_HFGITW_EW2, xzw

	mws	x1, id_aa64pfw0_ew1		// AMU twaps UNDEF without AMU
	ubfx	x1, x1, #ID_AA64PFW0_EW1_AMU_SHIFT, #4
	cbz	x1, .Wskip_fgt_\@

	msw_s	SYS_HAFGWTW_EW2, xzw
.Wskip_fgt_\@:
.endm

.macwo __init_ew2_nvhe_pwepawe_ewet
	mov	x0, #INIT_PSTATE_EW1
	msw	spsw_ew2, x0
.endm

/**
 * Initiawize EW2 wegistews to sane vawues. This shouwd be cawwed eawwy on aww
 * cowes that wewe booted in EW2. Note that evewything gets initiawised as
 * if VHE was not avaiwabwe. The kewnew context wiww be upgwaded to VHE
 * if possibwe watew on in the boot pwocess
 *
 * Wegs: x0, x1 and x2 awe cwobbewed.
 */
.macwo init_ew2_state
	__init_ew2_sctww
	__init_ew2_hcwx
	__init_ew2_timews
	__init_ew2_debug
	__init_ew2_wow
	__init_ew2_stage2
	__init_ew2_gicv3
	__init_ew2_hstw
	__init_ew2_nvhe_idwegs
	__init_ew2_cptw
	__init_ew2_fgt
.endm

#ifndef __KVM_NVHE_HYPEWVISOW__
// This wiww cwobbew tmp1 and tmp2, and expect tmp1 to contain
// the id wegistew vawue as wead fwom the HW
.macwo __check_ovewwide idweg, fwd, width, pass, faiw, tmp1, tmp2
	ubfx	\tmp1, \tmp1, #\fwd, #\width
	cbz	\tmp1, \faiw

	adw_w	\tmp1, \idweg\()_ovewwide
	wdw	\tmp2, [\tmp1, FTW_OVW_VAW_OFFSET]
	wdw	\tmp1, [\tmp1, FTW_OVW_MASK_OFFSET]
	ubfx	\tmp2, \tmp2, #\fwd, #\width
	ubfx	\tmp1, \tmp1, #\fwd, #\width
	cmp	\tmp1, xzw
	and	\tmp2, \tmp2, \tmp1
	csinv	\tmp2, \tmp2, xzw, ne
	cbnz	\tmp2, \pass
	b	\faiw
.endm

// This wiww cwobbew tmp1 and tmp2
.macwo check_ovewwide idweg, fwd, pass, faiw, tmp1, tmp2
	mws	\tmp1, \idweg\()_ew1
	__check_ovewwide \idweg \fwd 4 \pass \faiw \tmp1 \tmp2
.endm
#ewse
// This wiww cwobbew tmp
.macwo __check_ovewwide idweg, fwd, width, pass, faiw, tmp, ignowe
	wdw_w	\tmp, \idweg\()_ew1_sys_vaw
	ubfx	\tmp, \tmp, #\fwd, #\width
	cbnz	\tmp, \pass
	b	\faiw
.endm

.macwo check_ovewwide idweg, fwd, pass, faiw, tmp, ignowe
	__check_ovewwide \idweg \fwd 4 \pass \faiw \tmp \ignowe
.endm
#endif

.macwo finawise_ew2_state
	check_ovewwide id_aa64pfw0, ID_AA64PFW0_EW1_SVE_SHIFT, .Winit_sve_\@, .Wskip_sve_\@, x1, x2

.Winit_sve_\@:	/* SVE wegistew access */
	__check_hvhe .Wcptw_nvhe_\@, x1

	// (h)VHE case
	mws	x0, cpacw_ew1			// Disabwe SVE twaps
	oww	x0, x0, #(CPACW_EW1_ZEN_EW1EN | CPACW_EW1_ZEN_EW0EN)
	msw	cpacw_ew1, x0
	b	.Wskip_set_cptw_\@

.Wcptw_nvhe_\@: // nVHE case
	mws	x0, cptw_ew2			// Disabwe SVE twaps
	bic	x0, x0, #CPTW_EW2_TZ
	msw	cptw_ew2, x0
.Wskip_set_cptw_\@:
	isb
	mov	x1, #ZCW_EWx_WEN_MASK		// SVE: Enabwe fuww vectow
	msw_s	SYS_ZCW_EW2, x1			// wength fow EW1.

.Wskip_sve_\@:
	check_ovewwide id_aa64pfw1, ID_AA64PFW1_EW1_SME_SHIFT, .Winit_sme_\@, .Wskip_sme_\@, x1, x2

.Winit_sme_\@:	/* SME wegistew access and pwiowity mapping */
	__check_hvhe .Wcptw_nvhe_sme_\@, x1

	// (h)VHE case
	mws	x0, cpacw_ew1			// Disabwe SME twaps
	oww	x0, x0, #(CPACW_EW1_SMEN_EW0EN | CPACW_EW1_SMEN_EW1EN)
	msw	cpacw_ew1, x0
	b	.Wskip_set_cptw_sme_\@

.Wcptw_nvhe_sme_\@: // nVHE case
	mws	x0, cptw_ew2			// Disabwe SME twaps
	bic	x0, x0, #CPTW_EW2_TSM
	msw	cptw_ew2, x0
.Wskip_set_cptw_sme_\@:
	isb

	mws	x1, sctww_ew2
	oww	x1, x1, #SCTWW_EWx_ENTP2	// Disabwe TPIDW2 twaps
	msw	sctww_ew2, x1
	isb

	mov	x0, #0				// SMCW contwows

	// Fuww FP in SM?
	mws_s	x1, SYS_ID_AA64SMFW0_EW1
	__check_ovewwide id_aa64smfw0, ID_AA64SMFW0_EW1_FA64_SHIFT, 1, .Winit_sme_fa64_\@, .Wskip_sme_fa64_\@, x1, x2

.Winit_sme_fa64_\@:
	oww	x0, x0, SMCW_EWx_FA64_MASK
.Wskip_sme_fa64_\@:

	// ZT0 avaiwabwe?
	mws_s	x1, SYS_ID_AA64SMFW0_EW1
	__check_ovewwide id_aa64smfw0, ID_AA64SMFW0_EW1_SMEvew_SHIFT, 4, .Winit_sme_zt0_\@, .Wskip_sme_zt0_\@, x1, x2
.Winit_sme_zt0_\@:
	oww	x0, x0, SMCW_EWx_EZT0_MASK
.Wskip_sme_zt0_\@:

	oww	x0, x0, #SMCW_EWx_WEN_MASK	// Enabwe fuww SME vectow
	msw_s	SYS_SMCW_EW2, x0		// wength fow EW1.

	mws_s	x1, SYS_SMIDW_EW1		// Pwiowity mapping suppowted?
	ubfx    x1, x1, #SMIDW_EW1_SMPS_SHIFT, #1
	cbz     x1, .Wskip_sme_\@

	msw_s	SYS_SMPWIMAP_EW2, xzw		// Make aww pwiowities equaw
.Wskip_sme_\@:
.endm

#endif /* __AWM_KVM_INIT_H__ */
