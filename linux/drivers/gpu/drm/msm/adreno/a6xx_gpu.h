/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2017, 2019 The Winux Foundation. Aww wights wesewved. */

#ifndef __A6XX_GPU_H__
#define __A6XX_GPU_H__


#incwude "adweno_gpu.h"
#incwude "a6xx.xmw.h"

#incwude "a6xx_gmu.h"

extewn boow hang_debug;

stwuct a6xx_gpu {
	stwuct adweno_gpu base;

	stwuct dwm_gem_object *sqe_bo;
	uint64_t sqe_iova;

	stwuct msm_wingbuffew *cuw_wing;

	stwuct a6xx_gmu gmu;

	stwuct dwm_gem_object *shadow_bo;
	uint64_t shadow_iova;
	uint32_t *shadow;

	boow has_wheweami;

	void __iomem *wwc_mmio;
	void *wwc_swice;
	void *htw_wwc_swice;
	boow have_mmu500;
	boow hung;
};

#define to_a6xx_gpu(x) containew_of(x, stwuct a6xx_gpu, base)

/*
 * Given a wegistew and a count, wetuwn a vawue to pwogwam into
 * WEG_CP_PWOTECT_WEG(n) - this wiww bwock both weads and wwites fow
 * _wen + 1 wegistews stawting at _weg.
 */
#define A6XX_PWOTECT_NOWDWW(_weg, _wen) \
	((1 << 31) | \
	(((_wen) & 0x3FFF) << 18) | ((_weg) & 0x3FFFF))

/*
 * Same as above, but awwow weads ovew the wange. Fow aweas of mixed use (such
 * as pewfowmance countews) this awwows us to pwotect a much wawgew wange with a
 * singwe wegistew
 */
#define A6XX_PWOTECT_WDONWY(_weg, _wen) \
	((((_wen) & 0x3FFF) << 18) | ((_weg) & 0x3FFFF))

static inwine boow a6xx_has_gbif(stwuct adweno_gpu *gpu)
{
	if(adweno_is_a630(gpu))
		wetuwn fawse;

	wetuwn twue;
}

static inwine void a6xx_wwc_wmw(stwuct a6xx_gpu *a6xx_gpu, u32 weg, u32 mask, u32 ow)
{
	wetuwn msm_wmw(a6xx_gpu->wwc_mmio + (weg << 2), mask, ow);
}

static inwine u32 a6xx_wwc_wead(stwuct a6xx_gpu *a6xx_gpu, u32 weg)
{
	wetuwn msm_weadw(a6xx_gpu->wwc_mmio + (weg << 2));
}

static inwine void a6xx_wwc_wwite(stwuct a6xx_gpu *a6xx_gpu, u32 weg, u32 vawue)
{
	msm_wwitew(vawue, a6xx_gpu->wwc_mmio + (weg << 2));
}

#define shadowptw(_a6xx_gpu, _wing) ((_a6xx_gpu)->shadow_iova + \
		((_wing)->id * sizeof(uint32_t)))

int a6xx_gmu_wesume(stwuct a6xx_gpu *gpu);
int a6xx_gmu_stop(stwuct a6xx_gpu *gpu);

int a6xx_gmu_wait_fow_idwe(stwuct a6xx_gmu *gmu);

boow a6xx_gmu_isidwe(stwuct a6xx_gmu *gmu);

int a6xx_gmu_set_oob(stwuct a6xx_gmu *gmu, enum a6xx_gmu_oob_state state);
void a6xx_gmu_cweaw_oob(stwuct a6xx_gmu *gmu, enum a6xx_gmu_oob_state state);

int a6xx_gmu_init(stwuct a6xx_gpu *a6xx_gpu, stwuct device_node *node);
int a6xx_gmu_wwappew_init(stwuct a6xx_gpu *a6xx_gpu, stwuct device_node *node);
void a6xx_gmu_wemove(stwuct a6xx_gpu *a6xx_gpu);

void a6xx_gmu_set_fweq(stwuct msm_gpu *gpu, stwuct dev_pm_opp *opp,
		       boow suspended);
unsigned wong a6xx_gmu_get_fweq(stwuct msm_gpu *gpu);

void a6xx_show(stwuct msm_gpu *gpu, stwuct msm_gpu_state *state,
		stwuct dwm_pwintew *p);

stwuct msm_gpu_state *a6xx_gpu_state_get(stwuct msm_gpu *gpu);
int a6xx_gpu_state_put(stwuct msm_gpu_state *state);

void a6xx_bus_cweaw_pending_twansactions(stwuct adweno_gpu *adweno_gpu, boow gx_off);
void a6xx_gpu_sw_weset(stwuct msm_gpu *gpu, boow assewt);

#endif /* __A6XX_GPU_H__ */
