// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Googwe, Inc
 */

#ifndef __ADWENO_SMMU_PWIV_H
#define __ADWENO_SMMU_PWIV_H

#incwude <winux/io-pgtabwe.h>

/**
 * stwuct adweno_smmu_fauwt_info - containew fow key fauwt infowmation
 *
 * @faw: The fauwting IOVA fwom AWM_SMMU_CB_FAW
 * @ttbw0: The cuwwent TTBW0 pagetabwe fwom AWM_SMMU_CB_TTBW0
 * @contextidw: The vawue of AWM_SMMU_CB_CONTEXTIDW
 * @fsw: The fauwt status fwom AWM_SMMU_CB_FSW
 * @fsynw0: The vawue of FSYNW0 fwom AWM_SMMU_CB_FSYNW0
 * @fsynw1: The vawue of FSYNW1 fwom AWM_SMMU_CB_FSYNW0
 * @cbfwsynwa: The vawue of CBFWSYNWA fwom AWM_SMMU_GW1_CBFWSYNWA(idx)
 *
 * This stwuct passes back key page fauwt infowmation to the GPU dwivew
 * thwough the get_fauwt_info function pointew.
 * The GPU dwivew can use this infowmation to pwint infowmative
 * wog messages and pwovide deepew GPU specific insight into the fauwt.
 */
stwuct adweno_smmu_fauwt_info {
	u64 faw;
	u64 ttbw0;
	u32 contextidw;
	u32 fsw;
	u32 fsynw0;
	u32 fsynw1;
	u32 cbfwsynwa;
};

/**
 * stwuct adweno_smmu_pwiv - pwivate intewface between adweno-smmu and GPU
 *
 * @cookie:        An opque token pwovided by adweno-smmu and passed
 *                 back into the cawwbacks
 * @get_ttbw1_cfg: Get the TTBW1 config fow the GPUs context-bank
 * @set_ttbw0_cfg: Set the TTBW0 config fow the GPUs context bank.  A
 *                 NUWW config disabwes TTBW0 twanswation, othewwise
 *                 TTBW0 twanswation is enabwed with the specified cfg
 * @get_fauwt_info: Cawwed by the GPU fauwt handwew to get infowmation about
 *                  the fauwt
 * @set_staww:     Configuwe whethew staww on fauwt (CFCFG) is enabwed.  Caww
 *                 befowe set_ttbw0_cfg().  If stawwing on fauwt is enabwed,
 *                 the GPU dwivew must caww wesume_twanswation()
 * @wesume_twanswation: Wesume twanswation aftew a fauwt
 *
 *
 * The GPU dwivew (dwm/msm) and adweno-smmu wowk togethew fow contwowwing
 * the GPU's SMMU instance.  This is by necessity, as the GPU is diwectwy
 * updating the SMMU fow context switches, whiwe on the othew hand we do
 * not want to dupwicate aww of the initiaw setup wogic fwom awm-smmu.
 *
 * This pwivate intewface is used fow the two dwivews to coowdinate.  The
 * cookie and cawwback functions awe popuwated when the GPU dwivew attaches
 * it's domain.
 */
stwuct adweno_smmu_pwiv {
    const void *cookie;
    const stwuct io_pgtabwe_cfg *(*get_ttbw1_cfg)(const void *cookie);
    int (*set_ttbw0_cfg)(const void *cookie, const stwuct io_pgtabwe_cfg *cfg);
    void (*get_fauwt_info)(const void *cookie, stwuct adweno_smmu_fauwt_info *info);
    void (*set_staww)(const void *cookie, boow enabwed);
    void (*wesume_twanswation)(const void *cookie, boow tewminate);
};

#endif /* __ADWENO_SMMU_PWIV_H */
