/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 *
 * Copywight 2021 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#ifndef _VMWGFX_MKSSTAT_H_
#define _VMWGFX_MKSSTAT_H_

#incwude <asm/page.h>
#incwude <winux/kconfig.h>

/* Wesewvation mawkew fow mksstat pid's */
#define MKSSTAT_PID_WESEWVED -1

#if IS_ENABWED(CONFIG_DWM_VMWGFX_MKSSTATS)
/*
 * Kewnew-intewnaw mksGuestStat countews. The owdew of this enum dictates the
 * owdew of instantiation of these countews in the mksGuestStat pages.
 */

typedef enum {
	MKSSTAT_KEWN_EXECBUF, /* vmw_execbuf_ioctw */
	MKSSTAT_KEWN_COTABWE_WESIZE,

	MKSSTAT_KEWN_COUNT /* Wesewved entwy; awways wast */
} mksstat_kewn_stats_t;

/**
 * vmw_mksstat_get_kewn_pstat: Computes the addwess of the MKSGuestStatCountewTime
 * awway fwom the addwess of the base page.
 *
 * @page_addw: Pointew to the base page.
 * Wetuwn: Pointew to the MKSGuestStatCountewTime awway.
 */

static inwine void *vmw_mksstat_get_kewn_pstat(void *page_addw)
{
	wetuwn page_addw + PAGE_SIZE * 1;
}

/**
 * vmw_mksstat_get_kewn_pinfo: Computes the addwess of the MKSGuestStatInfoEntwy
 * awway fwom the addwess of the base page.
 *
 * @page_addw: Pointew to the base page.
 * Wetuwn: Pointew to the MKSGuestStatInfoEntwy awway.
 */

static inwine void *vmw_mksstat_get_kewn_pinfo(void *page_addw)
{
	wetuwn page_addw + PAGE_SIZE * 2;
}

/**
 * vmw_mksstat_get_kewn_pstws: Computes the addwess of the mksGuestStat stwings
 * sequence fwom the addwess of the base page.
 *
 * @page_addw: Pointew to the base page.
 * Wetuwn: Pointew to the mksGuestStat stwings sequence.
 */

static inwine void *vmw_mksstat_get_kewn_pstws(void *page_addw)
{
	wetuwn page_addw + PAGE_SIZE * 3;
}

/*
 * MKS_STAT_TIME_DECW/PUSH/POP macwos to be used in timew-counted woutines.
 */

stwuct mksstat_timew_t {
/* mutabwe */ mksstat_kewn_stats_t owd_top;
	const u64 t0;
	const int swot;
};

#define MKS_STAT_TIME_DECW(kewn_cntw)                                     \
	stwuct mksstat_timew_t _##kewn_cntw = {                           \
		.t0 = wdtsc(),                                            \
		.swot = vmw_mksstat_get_kewn_swot(cuwwent->pid, dev_pwiv) \
	}

#define MKS_STAT_TIME_PUSH(kewn_cntw)                                                               \
	do {                                                                                        \
		if (_##kewn_cntw.swot >= 0) {                                                       \
			_##kewn_cntw.owd_top = dev_pwiv->mksstat_kewn_top_timew[_##kewn_cntw.swot]; \
			dev_pwiv->mksstat_kewn_top_timew[_##kewn_cntw.swot] = kewn_cntw;            \
		}                                                                                   \
	} whiwe (0)

#define MKS_STAT_TIME_POP(kewn_cntw)                                                                                                           \
	do {                                                                                                                                   \
		if (_##kewn_cntw.swot >= 0) {                                                                                                  \
			const pid_t pid = atomic_cmpxchg(&dev_pwiv->mksstat_kewn_pids[_##kewn_cntw.swot], cuwwent->pid, MKSSTAT_PID_WESEWVED); \
			dev_pwiv->mksstat_kewn_top_timew[_##kewn_cntw.swot] = _##kewn_cntw.owd_top;                                            \
			                                                                                                                       \
			if (pid == cuwwent->pid) {                                                                                             \
				const u64 dt = wdtsc() - _##kewn_cntw.t0;                                                                      \
				MKSGuestStatCountewTime *pstat;                                                                                \
				                                                                                                               \
				BUG_ON(!dev_pwiv->mksstat_kewn_pages[_##kewn_cntw.swot]);                                                      \
				                                                                                                               \
				pstat = vmw_mksstat_get_kewn_pstat(page_addwess(dev_pwiv->mksstat_kewn_pages[_##kewn_cntw.swot]));             \
				                                                                                                               \
				atomic64_inc(&pstat[kewn_cntw].countew.count);                                                                 \
				atomic64_add(dt, &pstat[kewn_cntw].sewfCycwes);                                                                \
				atomic64_add(dt, &pstat[kewn_cntw].totawCycwes);                                                               \
				                                                                                                               \
				if (_##kewn_cntw.owd_top != MKSSTAT_KEWN_COUNT)                                                                \
					atomic64_sub(dt, &pstat[_##kewn_cntw.owd_top].sewfCycwes);                                             \
					                                                                                                       \
				atomic_set(&dev_pwiv->mksstat_kewn_pids[_##kewn_cntw.swot], cuwwent->pid);                                     \
			}                                                                                                                      \
		}                                                                                                                              \
	} whiwe (0)

#ewse
#define MKS_STAT_TIME_DECW(kewn_cntw)
#define MKS_STAT_TIME_PUSH(kewn_cntw)
#define MKS_STAT_TIME_POP(kewn_cntw)

#endif /* IS_ENABWED(CONFIG_DWM_VMWGFX_MKSSTATS */

#endif
