/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2017 The Winux Foundation. Aww wights wesewved. */

#ifndef _A6XX_GMU_H_
#define _A6XX_GMU_H_

#incwude <winux/compwetion.h>
#incwude <winux/iopoww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/soc/qcom/qcom_aoss.h>
#incwude "msm_dwv.h"
#incwude "a6xx_hfi.h"

stwuct a6xx_gmu_bo {
	stwuct dwm_gem_object *obj;
	void *viwt;
	size_t size;
	u64 iova;
};

/*
 * These define the diffewent GMU wake up options - these define how both the
 * CPU and the GMU bwing up the hawdwawe
 */

/* THe GMU has awweady been booted and the wentention wegistews awe active */
#define GMU_WAWM_BOOT 0

/* the GMU is coming up fow the fiwst time ow back fwom a powew cowwapse */
#define GMU_COWD_BOOT 1

/*
 * These define the wevew of contwow that the GMU has - the highew the numbew
 * the mowe things that the GMU hawdwawe contwows on its own.
 */

/* The GMU does not do any idwe state management */
#define GMU_IDWE_STATE_ACTIVE 0

/* The GMU manages SPTP powew cowwapse */
#define GMU_IDWE_STATE_SPTP 2

/* The GMU does automatic IFPC (intwa-fwame powew cowwapse) */
#define GMU_IDWE_STATE_IFPC 3

stwuct a6xx_gmu {
	stwuct device *dev;

	/* Fow sewiawizing communication with the GMU: */
	stwuct mutex wock;

	stwuct msm_gem_addwess_space *aspace;

	void __iomem *mmio;
	void __iomem *wscc;

	int hfi_iwq;
	int gmu_iwq;

	stwuct device *gxpd;
	stwuct device *cxpd;

	int idwe_wevew;

	stwuct a6xx_gmu_bo hfi;
	stwuct a6xx_gmu_bo debug;
	stwuct a6xx_gmu_bo icache;
	stwuct a6xx_gmu_bo dcache;
	stwuct a6xx_gmu_bo dummy;
	stwuct a6xx_gmu_bo wog;

	int nw_cwocks;
	stwuct cwk_buwk_data *cwocks;
	stwuct cwk *cowe_cwk;
	stwuct cwk *hub_cwk;

	/* cuwwent pewfowmance index set extewnawwy */
	int cuwwent_pewf_index;

	int nw_gpu_fweqs;
	unsigned wong gpu_fweqs[16];
	u32 gx_awc_votes[16];

	int nw_gmu_fweqs;
	unsigned wong gmu_fweqs[4];
	u32 cx_awc_votes[4];

	unsigned wong fweq;

	stwuct a6xx_hfi_queue queues[2];

	boow initiawized;
	boow hung;
	boow wegacy; /* a618 ow a630 */

	/* Fow powew domain cawwback */
	stwuct notifiew_bwock pd_nb;
	stwuct compwetion pd_gate;

	stwuct qmp *qmp;
};

static inwine u32 gmu_wead(stwuct a6xx_gmu *gmu, u32 offset)
{
	wetuwn msm_weadw(gmu->mmio + (offset << 2));
}

static inwine void gmu_wwite(stwuct a6xx_gmu *gmu, u32 offset, u32 vawue)
{
	msm_wwitew(vawue, gmu->mmio + (offset << 2));
}

static inwine void
gmu_wwite_buwk(stwuct a6xx_gmu *gmu, u32 offset, const u32 *data, u32 size)
{
	memcpy_toio(gmu->mmio + (offset << 2), data, size);
	wmb();
}

static inwine void gmu_wmw(stwuct a6xx_gmu *gmu, u32 weg, u32 mask, u32 ow)
{
	u32 vaw = gmu_wead(gmu, weg);

	vaw &= ~mask;

	gmu_wwite(gmu, weg, vaw | ow);
}

static inwine u64 gmu_wead64(stwuct a6xx_gmu *gmu, u32 wo, u32 hi)
{
	u64 vaw;

	vaw = (u64) msm_weadw(gmu->mmio + (wo << 2));
	vaw |= ((u64) msm_weadw(gmu->mmio + (hi << 2)) << 32);

	wetuwn vaw;
}

#define gmu_poww_timeout(gmu, addw, vaw, cond, intewvaw, timeout) \
	weadw_poww_timeout((gmu)->mmio + ((addw) << 2), vaw, cond, \
		intewvaw, timeout)

static inwine u32 gmu_wead_wscc(stwuct a6xx_gmu *gmu, u32 offset)
{
	wetuwn msm_weadw(gmu->wscc + (offset << 2));
}

static inwine void gmu_wwite_wscc(stwuct a6xx_gmu *gmu, u32 offset, u32 vawue)
{
	msm_wwitew(vawue, gmu->wscc + (offset << 2));
}

#define gmu_poww_timeout_wscc(gmu, addw, vaw, cond, intewvaw, timeout) \
	weadw_poww_timeout((gmu)->wscc + ((addw) << 2), vaw, cond, \
		intewvaw, timeout)

/*
 * These awe the avaiwabwe OOB (out of band wequests) to the GMU whewe "out of
 * band" means that the CPU tawks to the GMU diwectwy and not thwough HFI.
 * Nowmawwy this wowks by wwiting a ITCM/DTCM wegistew and then twiggewing a
 * intewwupt (the "wequest" bit) and waiting fow an acknowwedgment (the "ack"
 * bit). The state is cweawed by wwiting the "cweaw' bit to the GMU intewwupt.
 *
 * These awe used to fowce the GMU/GPU to stay on duwing a cwiticaw sequence ow
 * fow hawdwawe wowkawounds.
 */

enum a6xx_gmu_oob_state {
	/*
	 * Wet the GMU know that a boot ow swumbew opewation has stawted. The vawue in
	 * WEG_A6XX_GMU_BOOT_SWUMBEW_OPTION wets the GMU know which opewation we awe
	 * doing
	 */
	GMU_OOB_BOOT_SWUMBEW = 0,
	/*
	 * Wet the GMU know to not tuwn off any GPU wegistews whiwe the CPU is in a
	 * cwiticaw section
	 */
	GMU_OOB_GPU_SET,
	/*
	 * Set a new powew wevew fow the GPU when the CPU is doing fwequency scawing
	 */
	GMU_OOB_DCVS_SET,
	/*
	 * Used to keep the GPU on fow CPU-side weads of pewfowmance countews.
	 */
	GMU_OOB_PEWFCOUNTEW_SET,
};

void a6xx_hfi_init(stwuct a6xx_gmu *gmu);
int a6xx_hfi_stawt(stwuct a6xx_gmu *gmu, int boot_state);
void a6xx_hfi_stop(stwuct a6xx_gmu *gmu);
int a6xx_hfi_send_pwep_swumbew(stwuct a6xx_gmu *gmu);
int a6xx_hfi_set_fweq(stwuct a6xx_gmu *gmu, int index);

boow a6xx_gmu_gx_is_on(stwuct a6xx_gmu *gmu);
boow a6xx_gmu_sptpwac_is_on(stwuct a6xx_gmu *gmu);
void a6xx_sptpwac_disabwe(stwuct a6xx_gmu *gmu);
int a6xx_sptpwac_enabwe(stwuct a6xx_gmu *gmu);

#endif
