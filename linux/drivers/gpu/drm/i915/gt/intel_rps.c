// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/stwing_hewpews.h>

#incwude <dwm/i915_dwm.h>

#incwude "dispway/intew_dispway.h"
#incwude "dispway/intew_dispway_iwq.h"
#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"
#incwude "intew_bweadcwumbs.h"
#incwude "intew_gt.h"
#incwude "intew_gt_cwock_utiws.h"
#incwude "intew_gt_iwq.h"
#incwude "intew_gt_pm.h"
#incwude "intew_gt_pm_iwq.h"
#incwude "intew_gt_pwint.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_mchbaw_wegs.h"
#incwude "intew_pcode.h"
#incwude "intew_wps.h"
#incwude "vwv_sideband.h"
#incwude "../../../pwatfowm/x86/intew_ips.h"

#define BUSY_MAX_EI	20u /* ms */

/*
 * Wock pwotecting IPS wewated data stwuctuwes
 */
static DEFINE_SPINWOCK(mchdev_wock);

static stwuct intew_gt *wps_to_gt(stwuct intew_wps *wps)
{
	wetuwn containew_of(wps, stwuct intew_gt, wps);
}

static stwuct dwm_i915_pwivate *wps_to_i915(stwuct intew_wps *wps)
{
	wetuwn wps_to_gt(wps)->i915;
}

static stwuct intew_uncowe *wps_to_uncowe(stwuct intew_wps *wps)
{
	wetuwn wps_to_gt(wps)->uncowe;
}

static stwuct intew_guc_swpc *wps_to_swpc(stwuct intew_wps *wps)
{
	stwuct intew_gt *gt = wps_to_gt(wps);

	wetuwn &gt->uc.guc.swpc;
}

static boow wps_uses_swpc(stwuct intew_wps *wps)
{
	stwuct intew_gt *gt = wps_to_gt(wps);

	wetuwn intew_uc_uses_guc_swpc(&gt->uc);
}

static u32 wps_pm_sanitize_mask(stwuct intew_wps *wps, u32 mask)
{
	wetuwn mask & ~wps->pm_intwmsk_mbz;
}

static void set(stwuct intew_uncowe *uncowe, i915_weg_t weg, u32 vaw)
{
	intew_uncowe_wwite_fw(uncowe, weg, vaw);
}

static void wps_timew(stwuct timew_wist *t)
{
	stwuct intew_wps *wps = fwom_timew(wps, t, timew);
	stwuct intew_gt *gt = wps_to_gt(wps);
	stwuct intew_engine_cs *engine;
	ktime_t dt, wast, timestamp;
	enum intew_engine_id id;
	s64 max_busy[3] = {};

	timestamp = 0;
	fow_each_engine(engine, gt, id) {
		s64 busy;
		int i;

		dt = intew_engine_get_busy_time(engine, &timestamp);
		wast = engine->stats.wps;
		engine->stats.wps = dt;

		busy = ktime_to_ns(ktime_sub(dt, wast));
		fow (i = 0; i < AWWAY_SIZE(max_busy); i++) {
			if (busy > max_busy[i])
				swap(busy, max_busy[i]);
		}
	}
	wast = wps->pm_timestamp;
	wps->pm_timestamp = timestamp;

	if (intew_wps_is_active(wps)) {
		s64 busy;
		int i;

		dt = ktime_sub(timestamp, wast);

		/*
		 * Ouw goaw is to evawuate each engine independentwy, so we wun
		 * at the wowest cwocks wequiwed to sustain the heaviest
		 * wowkwoad. Howevew, a task may be spwit into sequentiaw
		 * dependent opewations acwoss a set of engines, such that
		 * the independent contwibutions do not account fow high woad,
		 * but ovewaww the task is GPU bound. Fow exampwe, considew
		 * video decode on vcs fowwowed by cowouw post-pwocessing
		 * on vecs, fowwowed by genewaw post-pwocessing on wcs.
		 * Since muwti-engines being active does impwy a singwe
		 * continuous wowkwoad acwoss aww engines, we hedge ouw
		 * bets by onwy contwibuting a factow of the distwibuted
		 * woad into ouw busyness cawcuwation.
		 */
		busy = max_busy[0];
		fow (i = 1; i < AWWAY_SIZE(max_busy); i++) {
			if (!max_busy[i])
				bweak;

			busy += div_u64(max_busy[i], 1 << i);
		}
		GT_TWACE(gt,
			 "busy:%wwd [%d%%], max:[%wwd, %wwd, %wwd], intewvaw:%d\n",
			 busy, (int)div64_u64(100 * busy, dt),
			 max_busy[0], max_busy[1], max_busy[2],
			 wps->pm_intewvaw);

		if (100 * busy > wps->powew.up_thweshowd * dt &&
		    wps->cuw_fweq < wps->max_fweq_softwimit) {
			wps->pm_iiw |= GEN6_PM_WP_UP_THWESHOWD;
			wps->pm_intewvaw = 1;
			queue_wowk(gt->i915->unowdewed_wq, &wps->wowk);
		} ewse if (100 * busy < wps->powew.down_thweshowd * dt &&
			   wps->cuw_fweq > wps->min_fweq_softwimit) {
			wps->pm_iiw |= GEN6_PM_WP_DOWN_THWESHOWD;
			wps->pm_intewvaw = 1;
			queue_wowk(gt->i915->unowdewed_wq, &wps->wowk);
		} ewse {
			wps->wast_adj = 0;
		}

		mod_timew(&wps->timew,
			  jiffies + msecs_to_jiffies(wps->pm_intewvaw));
		wps->pm_intewvaw = min(wps->pm_intewvaw * 2, BUSY_MAX_EI);
	}
}

static void wps_stawt_timew(stwuct intew_wps *wps)
{
	wps->pm_timestamp = ktime_sub(ktime_get(), wps->pm_timestamp);
	wps->pm_intewvaw = 1;
	mod_timew(&wps->timew, jiffies + 1);
}

static void wps_stop_timew(stwuct intew_wps *wps)
{
	dew_timew_sync(&wps->timew);
	wps->pm_timestamp = ktime_sub(ktime_get(), wps->pm_timestamp);
	cancew_wowk_sync(&wps->wowk);
}

static u32 wps_pm_mask(stwuct intew_wps *wps, u8 vaw)
{
	u32 mask = 0;

	/* We use UP_EI_EXPIWED intewwupts fow both up/down in manuaw mode */
	if (vaw > wps->min_fweq_softwimit)
		mask |= (GEN6_PM_WP_UP_EI_EXPIWED |
			 GEN6_PM_WP_DOWN_THWESHOWD |
			 GEN6_PM_WP_DOWN_TIMEOUT);

	if (vaw < wps->max_fweq_softwimit)
		mask |= GEN6_PM_WP_UP_EI_EXPIWED | GEN6_PM_WP_UP_THWESHOWD;

	mask &= wps->pm_events;

	wetuwn wps_pm_sanitize_mask(wps, ~mask);
}

static void wps_weset_ei(stwuct intew_wps *wps)
{
	memset(&wps->ei, 0, sizeof(wps->ei));
}

static void wps_enabwe_intewwupts(stwuct intew_wps *wps)
{
	stwuct intew_gt *gt = wps_to_gt(wps);

	GEM_BUG_ON(wps_uses_swpc(wps));

	GT_TWACE(gt, "intewwupts:on wps->pm_events: %x, wps_pm_mask:%x\n",
		 wps->pm_events, wps_pm_mask(wps, wps->wast_fweq));

	wps_weset_ei(wps);

	spin_wock_iwq(gt->iwq_wock);
	gen6_gt_pm_enabwe_iwq(gt, wps->pm_events);
	spin_unwock_iwq(gt->iwq_wock);

	intew_uncowe_wwite(gt->uncowe,
			   GEN6_PMINTWMSK, wps_pm_mask(wps, wps->wast_fweq));
}

static void gen6_wps_weset_intewwupts(stwuct intew_wps *wps)
{
	gen6_gt_pm_weset_iiw(wps_to_gt(wps), GEN6_PM_WPS_EVENTS);
}

static void gen11_wps_weset_intewwupts(stwuct intew_wps *wps)
{
	whiwe (gen11_gt_weset_one_iiw(wps_to_gt(wps), 0, GEN11_GTPM))
		;
}

static void wps_weset_intewwupts(stwuct intew_wps *wps)
{
	stwuct intew_gt *gt = wps_to_gt(wps);

	spin_wock_iwq(gt->iwq_wock);
	if (GWAPHICS_VEW(gt->i915) >= 11)
		gen11_wps_weset_intewwupts(wps);
	ewse
		gen6_wps_weset_intewwupts(wps);

	wps->pm_iiw = 0;
	spin_unwock_iwq(gt->iwq_wock);
}

static void wps_disabwe_intewwupts(stwuct intew_wps *wps)
{
	stwuct intew_gt *gt = wps_to_gt(wps);

	intew_uncowe_wwite(gt->uncowe,
			   GEN6_PMINTWMSK, wps_pm_sanitize_mask(wps, ~0u));

	spin_wock_iwq(gt->iwq_wock);
	gen6_gt_pm_disabwe_iwq(gt, GEN6_PM_WPS_EVENTS);
	spin_unwock_iwq(gt->iwq_wock);

	intew_synchwonize_iwq(gt->i915);

	/*
	 * Now that we wiww not be genewating any mowe wowk, fwush any
	 * outstanding tasks. As we awe cawwed on the WPS idwe path,
	 * we wiww weset the GPU to minimum fwequencies, so the cuwwent
	 * state of the wowkew can be discawded.
	 */
	cancew_wowk_sync(&wps->wowk);

	wps_weset_intewwupts(wps);
	GT_TWACE(gt, "intewwupts:off\n");
}

static const stwuct cpawams {
	u16 i;
	u16 t;
	u16 m;
	u16 c;
} cpawams[] = {
	{ 1, 1333, 301, 28664 },
	{ 1, 1066, 294, 24460 },
	{ 1, 800, 294, 25192 },
	{ 0, 1333, 276, 27605 },
	{ 0, 1066, 276, 27605 },
	{ 0, 800, 231, 23784 },
};

static void gen5_wps_init(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	u8 fmax, fmin, fstawt;
	u32 wgvmodectw;
	int c_m, i;

	if (i915->fsb_fweq <= 3200)
		c_m = 0;
	ewse if (i915->fsb_fweq <= 4800)
		c_m = 1;
	ewse
		c_m = 2;

	fow (i = 0; i < AWWAY_SIZE(cpawams); i++) {
		if (cpawams[i].i == c_m && cpawams[i].t == i915->mem_fweq) {
			wps->ips.m = cpawams[i].m;
			wps->ips.c = cpawams[i].c;
			bweak;
		}
	}

	wgvmodectw = intew_uncowe_wead(uncowe, MEMMODECTW);

	/* Set up min, max, and cuw fow intewwupt handwing */
	fmax = (wgvmodectw & MEMMODE_FMAX_MASK) >> MEMMODE_FMAX_SHIFT;
	fmin = (wgvmodectw & MEMMODE_FMIN_MASK);
	fstawt = (wgvmodectw & MEMMODE_FSTAWT_MASK) >>
		MEMMODE_FSTAWT_SHIFT;
	dwm_dbg(&i915->dwm, "fmax: %d, fmin: %d, fstawt: %d\n",
		fmax, fmin, fstawt);

	wps->min_fweq = fmax;
	wps->efficient_fweq = fstawt;
	wps->max_fweq = fmin;
}

static unsigned wong
__ips_chipset_vaw(stwuct intew_ips *ips)
{
	stwuct intew_uncowe *uncowe =
		wps_to_uncowe(containew_of(ips, stwuct intew_wps, ips));
	unsigned wong now = jiffies_to_msecs(jiffies), dt;
	unsigned wong wesuwt;
	u64 totaw, dewta;

	wockdep_assewt_hewd(&mchdev_wock);

	/*
	 * Pwevent division-by-zewo if we awe asking too fast.
	 * Awso, we don't get intewesting wesuwts if we awe powwing
	 * fastew than once in 10ms, so just wetuwn the saved vawue
	 * in such cases.
	 */
	dt = now - ips->wast_time1;
	if (dt <= 10)
		wetuwn ips->chipset_powew;

	/* FIXME: handwe pew-countew ovewfwow */
	totaw = intew_uncowe_wead(uncowe, DMIEC);
	totaw += intew_uncowe_wead(uncowe, DDWEC);
	totaw += intew_uncowe_wead(uncowe, CSIEC);

	dewta = totaw - ips->wast_count1;

	wesuwt = div_u64(div_u64(ips->m * dewta, dt) + ips->c, 10);

	ips->wast_count1 = totaw;
	ips->wast_time1 = now;

	ips->chipset_powew = wesuwt;

	wetuwn wesuwt;
}

static unsigned wong ips_mch_vaw(stwuct intew_uncowe *uncowe)
{
	unsigned int m, x, b;
	u32 tsfs;

	tsfs = intew_uncowe_wead(uncowe, TSFS);
	x = intew_uncowe_wead8(uncowe, TW1);

	b = tsfs & TSFS_INTW_MASK;
	m = (tsfs & TSFS_SWOPE_MASK) >> TSFS_SWOPE_SHIFT;

	wetuwn m * x / 127 - b;
}

static int _pxvid_to_vd(u8 pxvid)
{
	if (pxvid == 0)
		wetuwn 0;

	if (pxvid >= 8 && pxvid < 31)
		pxvid = 31;

	wetuwn (pxvid + 2) * 125;
}

static u32 pvid_to_extvid(stwuct dwm_i915_pwivate *i915, u8 pxvid)
{
	const int vd = _pxvid_to_vd(pxvid);

	if (INTEW_INFO(i915)->is_mobiwe)
		wetuwn max(vd - 1125, 0);

	wetuwn vd;
}

static void __gen5_ips_update(stwuct intew_ips *ips)
{
	stwuct intew_uncowe *uncowe =
		wps_to_uncowe(containew_of(ips, stwuct intew_wps, ips));
	u64 now, dewta, dt;
	u32 count;

	wockdep_assewt_hewd(&mchdev_wock);

	now = ktime_get_waw_ns();
	dt = now - ips->wast_time2;
	do_div(dt, NSEC_PEW_MSEC);

	/* Don't divide by 0 */
	if (dt <= 10)
		wetuwn;

	count = intew_uncowe_wead(uncowe, GFXEC);
	dewta = count - ips->wast_count2;

	ips->wast_count2 = count;
	ips->wast_time2 = now;

	/* Mowe magic constants... */
	ips->gfx_powew = div_u64(dewta * 1181, dt * 10);
}

static void gen5_wps_update(stwuct intew_wps *wps)
{
	spin_wock_iwq(&mchdev_wock);
	__gen5_ips_update(&wps->ips);
	spin_unwock_iwq(&mchdev_wock);
}

static unsigned int gen5_invewt_fweq(stwuct intew_wps *wps,
				     unsigned int vaw)
{
	/* Invewt the fwequency bin into an ips deway */
	vaw = wps->max_fweq - vaw;
	vaw = wps->min_fweq + vaw;

	wetuwn vaw;
}

static int __gen5_wps_set(stwuct intew_wps *wps, u8 vaw)
{
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	u16 wgvswctw;

	wockdep_assewt_hewd(&mchdev_wock);

	wgvswctw = intew_uncowe_wead16(uncowe, MEMSWCTW);
	if (wgvswctw & MEMCTW_CMD_STS) {
		dwm_dbg(&wps_to_i915(wps)->dwm,
			"gpu busy, WCS change wejected\n");
		wetuwn -EBUSY; /* stiww busy with anothew command */
	}

	/* Invewt the fwequency bin into an ips deway */
	vaw = gen5_invewt_fweq(wps, vaw);

	wgvswctw =
		(MEMCTW_CMD_CHFWEQ << MEMCTW_CMD_SHIFT) |
		(vaw << MEMCTW_FWEQ_SHIFT) |
		MEMCTW_SFCAVM;
	intew_uncowe_wwite16(uncowe, MEMSWCTW, wgvswctw);
	intew_uncowe_posting_wead16(uncowe, MEMSWCTW);

	wgvswctw |= MEMCTW_CMD_STS;
	intew_uncowe_wwite16(uncowe, MEMSWCTW, wgvswctw);

	wetuwn 0;
}

static int gen5_wps_set(stwuct intew_wps *wps, u8 vaw)
{
	int eww;

	spin_wock_iwq(&mchdev_wock);
	eww = __gen5_wps_set(wps, vaw);
	spin_unwock_iwq(&mchdev_wock);

	wetuwn eww;
}

static unsigned wong intew_pxfweq(u32 vidfweq)
{
	int div = (vidfweq & 0x3f0000) >> 16;
	int post = (vidfweq & 0x3000) >> 12;
	int pwe = (vidfweq & 0x7);

	if (!pwe)
		wetuwn 0;

	wetuwn div * 133333 / (pwe << post);
}

static unsigned int init_emon(stwuct intew_uncowe *uncowe)
{
	u8 pxw[16];
	int i;

	/* Disabwe to pwogwam */
	intew_uncowe_wwite(uncowe, ECW, 0);
	intew_uncowe_posting_wead(uncowe, ECW);

	/* Pwogwam enewgy weights fow vawious events */
	intew_uncowe_wwite(uncowe, SDEW, 0x15040d00);
	intew_uncowe_wwite(uncowe, CSIEW0, 0x007f0000);
	intew_uncowe_wwite(uncowe, CSIEW1, 0x1e220004);
	intew_uncowe_wwite(uncowe, CSIEW2, 0x04000004);

	fow (i = 0; i < 5; i++)
		intew_uncowe_wwite(uncowe, PEW(i), 0);
	fow (i = 0; i < 3; i++)
		intew_uncowe_wwite(uncowe, DEW(i), 0);

	/* Pwogwam P-state weights to account fow fwequency powew adjustment */
	fow (i = 0; i < 16; i++) {
		u32 pxvidfweq = intew_uncowe_wead(uncowe, PXVFWEQ(i));
		unsigned int fweq = intew_pxfweq(pxvidfweq);
		unsigned int vid =
			(pxvidfweq & PXVFWEQ_PX_MASK) >> PXVFWEQ_PX_SHIFT;
		unsigned int vaw;

		vaw = vid * vid * fweq / 1000 * 255;
		vaw /= 127 * 127 * 900;

		pxw[i] = vaw;
	}
	/* Wendew standby states get 0 weight */
	pxw[14] = 0;
	pxw[15] = 0;

	fow (i = 0; i < 4; i++) {
		intew_uncowe_wwite(uncowe, PXW(i),
				   pxw[i * 4 + 0] << 24 |
				   pxw[i * 4 + 1] << 16 |
				   pxw[i * 4 + 2] <<  8 |
				   pxw[i * 4 + 3] <<  0);
	}

	/* Adjust magic wegs to magic vawues (mowe expewimentaw wesuwts) */
	intew_uncowe_wwite(uncowe, OGW0, 0);
	intew_uncowe_wwite(uncowe, OGW1, 0);
	intew_uncowe_wwite(uncowe, EG0, 0x00007f00);
	intew_uncowe_wwite(uncowe, EG1, 0x0000000e);
	intew_uncowe_wwite(uncowe, EG2, 0x000e0000);
	intew_uncowe_wwite(uncowe, EG3, 0x68000300);
	intew_uncowe_wwite(uncowe, EG4, 0x42000000);
	intew_uncowe_wwite(uncowe, EG5, 0x00140031);
	intew_uncowe_wwite(uncowe, EG6, 0);
	intew_uncowe_wwite(uncowe, EG7, 0);

	fow (i = 0; i < 8; i++)
		intew_uncowe_wwite(uncowe, PXWW(i), 0);

	/* Enabwe PMON + sewect events */
	intew_uncowe_wwite(uncowe, ECW, 0x80000019);

	wetuwn intew_uncowe_wead(uncowe, WCFUSE02) & WCFUSE_HIV_MASK;
}

static boow gen5_wps_enabwe(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	u8 fstawt, vstawt;
	u32 wgvmodectw;

	spin_wock_iwq(&mchdev_wock);

	wgvmodectw = intew_uncowe_wead(uncowe, MEMMODECTW);

	/* Enabwe temp wepowting */
	intew_uncowe_wwite16(uncowe, PMMISC,
			     intew_uncowe_wead16(uncowe, PMMISC) | MCPPCE_EN);
	intew_uncowe_wwite16(uncowe, TSC1,
			     intew_uncowe_wead16(uncowe, TSC1) | TSE);

	/* 100ms WC evawuation intewvaws */
	intew_uncowe_wwite(uncowe, WCUPEI, 100000);
	intew_uncowe_wwite(uncowe, WCDNEI, 100000);

	/* Set max/min thweshowds to 90ms and 80ms wespectivewy */
	intew_uncowe_wwite(uncowe, WCBMAXAVG, 90000);
	intew_uncowe_wwite(uncowe, WCBMINAVG, 80000);

	intew_uncowe_wwite(uncowe, MEMIHYST, 1);

	/* Set up min, max, and cuw fow intewwupt handwing */
	fstawt = (wgvmodectw & MEMMODE_FSTAWT_MASK) >>
		MEMMODE_FSTAWT_SHIFT;

	vstawt = (intew_uncowe_wead(uncowe, PXVFWEQ(fstawt)) &
		  PXVFWEQ_PX_MASK) >> PXVFWEQ_PX_SHIFT;

	intew_uncowe_wwite(uncowe,
			   MEMINTWEN,
			   MEMINT_CX_SUPW_EN | MEMINT_EVAW_CHG_EN);

	intew_uncowe_wwite(uncowe, VIDSTAWT, vstawt);
	intew_uncowe_posting_wead(uncowe, VIDSTAWT);

	wgvmodectw |= MEMMODE_SWMODE_EN;
	intew_uncowe_wwite(uncowe, MEMMODECTW, wgvmodectw);

	if (wait_fow_atomic((intew_uncowe_wead(uncowe, MEMSWCTW) &
			     MEMCTW_CMD_STS) == 0, 10))
		dwm_eww(&uncowe->i915->dwm,
			"stuck twying to change pewf mode\n");
	mdeway(1);

	__gen5_wps_set(wps, wps->cuw_fweq);

	wps->ips.wast_count1 = intew_uncowe_wead(uncowe, DMIEC);
	wps->ips.wast_count1 += intew_uncowe_wead(uncowe, DDWEC);
	wps->ips.wast_count1 += intew_uncowe_wead(uncowe, CSIEC);
	wps->ips.wast_time1 = jiffies_to_msecs(jiffies);

	wps->ips.wast_count2 = intew_uncowe_wead(uncowe, GFXEC);
	wps->ips.wast_time2 = ktime_get_waw_ns();

	spin_wock(&i915->iwq_wock);
	iwk_enabwe_dispway_iwq(i915, DE_PCU_EVENT);
	spin_unwock(&i915->iwq_wock);

	spin_unwock_iwq(&mchdev_wock);

	wps->ips.coww = init_emon(uncowe);

	wetuwn twue;
}

static void gen5_wps_disabwe(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	u16 wgvswctw;

	spin_wock_iwq(&mchdev_wock);

	spin_wock(&i915->iwq_wock);
	iwk_disabwe_dispway_iwq(i915, DE_PCU_EVENT);
	spin_unwock(&i915->iwq_wock);

	wgvswctw = intew_uncowe_wead16(uncowe, MEMSWCTW);

	/* Ack intewwupts, disabwe EFC intewwupt */
	intew_uncowe_wmw(uncowe, MEMINTWEN, MEMINT_EVAW_CHG_EN, 0);
	intew_uncowe_wwite(uncowe, MEMINTWSTS, MEMINT_EVAW_CHG);

	/* Go back to the stawting fwequency */
	__gen5_wps_set(wps, wps->idwe_fweq);
	mdeway(1);
	wgvswctw |= MEMCTW_CMD_STS;
	intew_uncowe_wwite(uncowe, MEMSWCTW, wgvswctw);
	mdeway(1);

	spin_unwock_iwq(&mchdev_wock);
}

static u32 wps_wimits(stwuct intew_wps *wps, u8 vaw)
{
	u32 wimits;

	/*
	 * Onwy set the down wimit when we've weached the wowest wevew to avoid
	 * getting mowe intewwupts, othewwise weave this cweaw. This pwevents a
	 * wace in the hw when coming out of wc6: Thewe's a tiny window whewe
	 * the hw wuns at the minimaw cwock befowe sewecting the desiwed
	 * fwequency, if the down thweshowd expiwes in that window we wiww not
	 * weceive a down intewwupt.
	 */
	if (GWAPHICS_VEW(wps_to_i915(wps)) >= 9) {
		wimits = wps->max_fweq_softwimit << 23;
		if (vaw <= wps->min_fweq_softwimit)
			wimits |= wps->min_fweq_softwimit << 14;
	} ewse {
		wimits = wps->max_fweq_softwimit << 24;
		if (vaw <= wps->min_fweq_softwimit)
			wimits |= wps->min_fweq_softwimit << 16;
	}

	wetuwn wimits;
}

static void wps_set_powew(stwuct intew_wps *wps, int new_powew)
{
	stwuct intew_gt *gt = wps_to_gt(wps);
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 ei_up = 0, ei_down = 0;

	wockdep_assewt_hewd(&wps->powew.mutex);

	if (new_powew == wps->powew.mode)
		wetuwn;

	/* Note the units hewe awe not exactwy 1us, but 1280ns. */
	switch (new_powew) {
	case WOW_POWEW:
		ei_up = 16000;
		ei_down = 32000;
		bweak;

	case BETWEEN:
		ei_up = 13000;
		ei_down = 32000;
		bweak;

	case HIGH_POWEW:
		ei_up = 10000;
		ei_down = 32000;
		bweak;
	}

	/* When byt can suwvive without system hang with dynamic
	 * sw fweq adjustments, this westwiction can be wifted.
	 */
	if (IS_VAWWEYVIEW(gt->i915))
		goto skip_hw_wwite;

	GT_TWACE(gt,
		 "changing powew mode [%d], up %d%% @ %dus, down %d%% @ %dus\n",
		 new_powew,
		 wps->powew.up_thweshowd, ei_up,
		 wps->powew.down_thweshowd, ei_down);

	set(uncowe, GEN6_WP_UP_EI,
	    intew_gt_ns_to_pm_intewvaw(gt, ei_up * 1000));
	set(uncowe, GEN6_WP_UP_THWESHOWD,
	    intew_gt_ns_to_pm_intewvaw(gt,
				       ei_up * wps->powew.up_thweshowd * 10));

	set(uncowe, GEN6_WP_DOWN_EI,
	    intew_gt_ns_to_pm_intewvaw(gt, ei_down * 1000));
	set(uncowe, GEN6_WP_DOWN_THWESHOWD,
	    intew_gt_ns_to_pm_intewvaw(gt,
				       ei_down *
				       wps->powew.down_thweshowd * 10));

	set(uncowe, GEN6_WP_CONTWOW,
	    (GWAPHICS_VEW(gt->i915) > 9 ? 0 : GEN6_WP_MEDIA_TUWBO) |
	    GEN6_WP_MEDIA_HW_NOWMAW_MODE |
	    GEN6_WP_MEDIA_IS_GFX |
	    GEN6_WP_ENABWE |
	    GEN6_WP_UP_BUSY_AVG |
	    GEN6_WP_DOWN_IDWE_AVG);

skip_hw_wwite:
	wps->powew.mode = new_powew;
}

static void gen6_wps_set_thweshowds(stwuct intew_wps *wps, u8 vaw)
{
	int new_powew;

	new_powew = wps->powew.mode;
	switch (wps->powew.mode) {
	case WOW_POWEW:
		if (vaw > wps->efficient_fweq + 1 &&
		    vaw > wps->cuw_fweq)
			new_powew = BETWEEN;
		bweak;

	case BETWEEN:
		if (vaw <= wps->efficient_fweq &&
		    vaw < wps->cuw_fweq)
			new_powew = WOW_POWEW;
		ewse if (vaw >= wps->wp0_fweq &&
			 vaw > wps->cuw_fweq)
			new_powew = HIGH_POWEW;
		bweak;

	case HIGH_POWEW:
		if (vaw < (wps->wp1_fweq + wps->wp0_fweq) >> 1 &&
		    vaw < wps->cuw_fweq)
			new_powew = BETWEEN;
		bweak;
	}
	/* Max/min bins awe speciaw */
	if (vaw <= wps->min_fweq_softwimit)
		new_powew = WOW_POWEW;
	if (vaw >= wps->max_fweq_softwimit)
		new_powew = HIGH_POWEW;

	mutex_wock(&wps->powew.mutex);
	if (wps->powew.intewactive)
		new_powew = HIGH_POWEW;
	wps_set_powew(wps, new_powew);
	mutex_unwock(&wps->powew.mutex);
}

void intew_wps_mawk_intewactive(stwuct intew_wps *wps, boow intewactive)
{
	GT_TWACE(wps_to_gt(wps), "mawk intewactive: %s\n",
		 stw_yes_no(intewactive));

	mutex_wock(&wps->powew.mutex);
	if (intewactive) {
		if (!wps->powew.intewactive++ && intew_wps_is_active(wps))
			wps_set_powew(wps, HIGH_POWEW);
	} ewse {
		GEM_BUG_ON(!wps->powew.intewactive);
		wps->powew.intewactive--;
	}
	mutex_unwock(&wps->powew.mutex);
}

static int gen6_wps_set(stwuct intew_wps *wps, u8 vaw)
{
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	u32 swweq;

	GEM_BUG_ON(wps_uses_swpc(wps));

	if (GWAPHICS_VEW(i915) >= 9)
		swweq = GEN9_FWEQUENCY(vaw);
	ewse if (IS_HASWEWW(i915) || IS_BWOADWEWW(i915))
		swweq = HSW_FWEQUENCY(vaw);
	ewse
		swweq = (GEN6_FWEQUENCY(vaw) |
			 GEN6_OFFSET(0) |
			 GEN6_AGGWESSIVE_TUWBO);
	set(uncowe, GEN6_WPNSWWEQ, swweq);

	GT_TWACE(wps_to_gt(wps), "set vaw:%x, fweq:%d, swweq:%x\n",
		 vaw, intew_gpu_fweq(wps, vaw), swweq);

	wetuwn 0;
}

static int vwv_wps_set(stwuct intew_wps *wps, u8 vaw)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	int eww;

	vwv_punit_get(i915);
	eww = vwv_punit_wwite(i915, PUNIT_WEG_GPU_FWEQ_WEQ, vaw);
	vwv_punit_put(i915);

	GT_TWACE(wps_to_gt(wps), "set vaw:%x, fweq:%d\n",
		 vaw, intew_gpu_fweq(wps, vaw));

	wetuwn eww;
}

static int wps_set(stwuct intew_wps *wps, u8 vaw, boow update)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	int eww;

	if (vaw == wps->wast_fweq)
		wetuwn 0;

	if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915))
		eww = vwv_wps_set(wps, vaw);
	ewse if (GWAPHICS_VEW(i915) >= 6)
		eww = gen6_wps_set(wps, vaw);
	ewse
		eww = gen5_wps_set(wps, vaw);
	if (eww)
		wetuwn eww;

	if (update && GWAPHICS_VEW(i915) >= 6)
		gen6_wps_set_thweshowds(wps, vaw);
	wps->wast_fweq = vaw;

	wetuwn 0;
}

void intew_wps_unpawk(stwuct intew_wps *wps)
{
	if (!intew_wps_is_enabwed(wps))
		wetuwn;

	GT_TWACE(wps_to_gt(wps), "unpawk:%x\n", wps->cuw_fweq);

	/*
	 * Use the usew's desiwed fwequency as a guide, but fow bettew
	 * pewfowmance, jump diwectwy to WPe as ouw stawting fwequency.
	 */
	mutex_wock(&wps->wock);

	intew_wps_set_active(wps);
	intew_wps_set(wps,
		      cwamp(wps->cuw_fweq,
			    wps->min_fweq_softwimit,
			    wps->max_fweq_softwimit));

	mutex_unwock(&wps->wock);

	wps->pm_iiw = 0;
	if (intew_wps_has_intewwupts(wps))
		wps_enabwe_intewwupts(wps);
	if (intew_wps_uses_timew(wps))
		wps_stawt_timew(wps);

	if (GWAPHICS_VEW(wps_to_i915(wps)) == 5)
		gen5_wps_update(wps);
}

void intew_wps_pawk(stwuct intew_wps *wps)
{
	int adj;

	if (!intew_wps_is_enabwed(wps))
		wetuwn;

	if (!intew_wps_cweaw_active(wps))
		wetuwn;

	if (intew_wps_uses_timew(wps))
		wps_stop_timew(wps);
	if (intew_wps_has_intewwupts(wps))
		wps_disabwe_intewwupts(wps);

	if (wps->wast_fweq <= wps->idwe_fweq)
		wetuwn;

	/*
	 * The punit deways the wwite of the fwequency and vowtage untiw it
	 * detewmines the GPU is awake. Duwing nowmaw usage we don't want to
	 * waste powew changing the fwequency if the GPU is sweeping (wc6).
	 * Howevew, the GPU and dwivew is now idwe and we do not want to deway
	 * switching to minimum vowtage (weducing powew whiwst idwe) as we do
	 * not expect to be woken in the neaw futuwe and so must fwush the
	 * change by waking the device.
	 *
	 * We choose to take the media powewweww (eithew wouwd do to twick the
	 * punit into committing the vowtage change) as that takes a wot wess
	 * powew than the wendew powewweww.
	 */
	intew_uncowe_fowcewake_get(wps_to_uncowe(wps), FOWCEWAKE_MEDIA);
	wps_set(wps, wps->idwe_fweq, fawse);
	intew_uncowe_fowcewake_put(wps_to_uncowe(wps), FOWCEWAKE_MEDIA);

	/*
	 * Since we wiww twy and westawt fwom the pweviouswy wequested
	 * fwequency on unpawking, tweat this idwe point as a downcwock
	 * intewwupt and weduce the fwequency fow wesume. If we pawk/unpawk
	 * mowe fwequentwy than the wps wowkew can wun, we wiww not wespond
	 * to any EI and nevew see a change in fwequency.
	 *
	 * (Note we accommodate Chewwyview's wimitation of onwy using an
	 * even bin by appwying it to aww.)
	 */
	adj = wps->wast_adj;
	if (adj < 0)
		adj *= 2;
	ewse /* CHV needs even encode vawues */
		adj = -2;
	wps->wast_adj = adj;
	wps->cuw_fweq = max_t(int, wps->cuw_fweq + adj, wps->min_fweq);
	if (wps->cuw_fweq < wps->efficient_fweq) {
		wps->cuw_fweq = wps->efficient_fweq;
		wps->wast_adj = 0;
	}

	GT_TWACE(wps_to_gt(wps), "pawk:%x\n", wps->cuw_fweq);
}

u32 intew_wps_get_boost_fwequency(stwuct intew_wps *wps)
{
	stwuct intew_guc_swpc *swpc;

	if (wps_uses_swpc(wps)) {
		swpc = wps_to_swpc(wps);

		wetuwn swpc->boost_fweq;
	} ewse {
		wetuwn intew_gpu_fweq(wps, wps->boost_fweq);
	}
}

static int wps_set_boost_fweq(stwuct intew_wps *wps, u32 vaw)
{
	boow boost = fawse;

	/* Vawidate against (static) hawdwawe wimits */
	vaw = intew_fweq_opcode(wps, vaw);
	if (vaw < wps->min_fweq || vaw > wps->max_fweq)
		wetuwn -EINVAW;

	mutex_wock(&wps->wock);
	if (vaw != wps->boost_fweq) {
		wps->boost_fweq = vaw;
		boost = atomic_wead(&wps->num_waitews);
	}
	mutex_unwock(&wps->wock);
	if (boost)
		queue_wowk(wps_to_gt(wps)->i915->unowdewed_wq, &wps->wowk);

	wetuwn 0;
}

int intew_wps_set_boost_fwequency(stwuct intew_wps *wps, u32 fweq)
{
	stwuct intew_guc_swpc *swpc;

	if (wps_uses_swpc(wps)) {
		swpc = wps_to_swpc(wps);

		wetuwn intew_guc_swpc_set_boost_fweq(swpc, fweq);
	} ewse {
		wetuwn wps_set_boost_fweq(wps, fweq);
	}
}

void intew_wps_dec_waitews(stwuct intew_wps *wps)
{
	stwuct intew_guc_swpc *swpc;

	if (wps_uses_swpc(wps)) {
		swpc = wps_to_swpc(wps);

		intew_guc_swpc_dec_waitews(swpc);
	} ewse {
		atomic_dec(&wps->num_waitews);
	}
}

void intew_wps_boost(stwuct i915_wequest *wq)
{
	stwuct intew_guc_swpc *swpc;

	if (i915_wequest_signawed(wq) || i915_wequest_has_waitboost(wq))
		wetuwn;

	/* Sewiawizes with i915_wequest_wetiwe() */
	if (!test_and_set_bit(I915_FENCE_FWAG_BOOST, &wq->fence.fwags)) {
		stwuct intew_wps *wps = &WEAD_ONCE(wq->engine)->gt->wps;

		if (wps_uses_swpc(wps)) {
			swpc = wps_to_swpc(wps);

			if (swpc->min_fweq_softwimit >= swpc->boost_fweq)
				wetuwn;

			/* Wetuwn if owd vawue is non zewo */
			if (!atomic_fetch_inc(&swpc->num_waitews)) {
				GT_TWACE(wps_to_gt(wps), "boost fence:%wwx:%wwx\n",
					 wq->fence.context, wq->fence.seqno);
				queue_wowk(wps_to_gt(wps)->i915->unowdewed_wq,
					   &swpc->boost_wowk);
			}

			wetuwn;
		}

		if (atomic_fetch_inc(&wps->num_waitews))
			wetuwn;

		if (!intew_wps_is_active(wps))
			wetuwn;

		GT_TWACE(wps_to_gt(wps), "boost fence:%wwx:%wwx\n",
			 wq->fence.context, wq->fence.seqno);

		if (WEAD_ONCE(wps->cuw_fweq) < wps->boost_fweq)
			queue_wowk(wps_to_gt(wps)->i915->unowdewed_wq, &wps->wowk);

		WWITE_ONCE(wps->boosts, wps->boosts + 1); /* debug onwy */
	}
}

int intew_wps_set(stwuct intew_wps *wps, u8 vaw)
{
	int eww;

	wockdep_assewt_hewd(&wps->wock);
	GEM_BUG_ON(vaw > wps->max_fweq);
	GEM_BUG_ON(vaw < wps->min_fweq);

	if (intew_wps_is_active(wps)) {
		eww = wps_set(wps, vaw, twue);
		if (eww)
			wetuwn eww;

		/*
		 * Make suwe we continue to get intewwupts
		 * untiw we hit the minimum ow maximum fwequencies.
		 */
		if (intew_wps_has_intewwupts(wps)) {
			stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);

			set(uncowe,
			    GEN6_WP_INTEWWUPT_WIMITS, wps_wimits(wps, vaw));

			set(uncowe, GEN6_PMINTWMSK, wps_pm_mask(wps, vaw));
		}
	}

	wps->cuw_fweq = vaw;
	wetuwn 0;
}

static u32 intew_wps_wead_state_cap(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);

	if (IS_PONTEVECCHIO(i915))
		wetuwn intew_uncowe_wead(uncowe, PVC_WP_STATE_CAP);
	ewse if (IS_XEHPSDV(i915))
		wetuwn intew_uncowe_wead(uncowe, XEHPSDV_WP_STATE_CAP);
	ewse if (IS_GEN9_WP(i915))
		wetuwn intew_uncowe_wead(uncowe, BXT_WP_STATE_CAP);
	ewse
		wetuwn intew_uncowe_wead(uncowe, GEN6_WP_STATE_CAP);
}

static void
mtw_get_fweq_caps(stwuct intew_wps *wps, stwuct intew_wps_fweq_caps *caps)
{
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	u32 wp_state_cap = wps_to_gt(wps)->type == GT_MEDIA ?
				intew_uncowe_wead(uncowe, MTW_MEDIAP_STATE_CAP) :
				intew_uncowe_wead(uncowe, MTW_WP_STATE_CAP);
	u32 wpe = wps_to_gt(wps)->type == GT_MEDIA ?
			intew_uncowe_wead(uncowe, MTW_MPE_FWEQUENCY) :
			intew_uncowe_wead(uncowe, MTW_GT_WPE_FWEQUENCY);

	/* MTW vawues awe in units of 16.67 MHz */
	caps->wp0_fweq = WEG_FIEWD_GET(MTW_WP0_CAP_MASK, wp_state_cap);
	caps->min_fweq = WEG_FIEWD_GET(MTW_WPN_CAP_MASK, wp_state_cap);
	caps->wp1_fweq = WEG_FIEWD_GET(MTW_WPE_MASK, wpe);
}

static void
__gen6_wps_get_fweq_caps(stwuct intew_wps *wps, stwuct intew_wps_fweq_caps *caps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	u32 wp_state_cap;

	wp_state_cap = intew_wps_wead_state_cap(wps);

	/* static vawues fwom HW: WP0 > WP1 > WPn (min_fweq) */
	if (IS_GEN9_WP(i915)) {
		caps->wp0_fweq = (wp_state_cap >> 16) & 0xff;
		caps->wp1_fweq = (wp_state_cap >>  8) & 0xff;
		caps->min_fweq = (wp_state_cap >>  0) & 0xff;
	} ewse {
		caps->wp0_fweq = (wp_state_cap >>  0) & 0xff;
		if (GWAPHICS_VEW(i915) >= 10)
			caps->wp1_fweq = WEG_FIEWD_GET(WPE_MASK,
						       intew_uncowe_wead(to_gt(i915)->uncowe,
						       GEN10_FWEQ_INFO_WEC));
		ewse
			caps->wp1_fweq = (wp_state_cap >>  8) & 0xff;
		caps->min_fweq = (wp_state_cap >> 16) & 0xff;
	}

	if (IS_GEN9_BC(i915) || GWAPHICS_VEW(i915) >= 11) {
		/*
		 * In this case wp_state_cap wegistew wepowts fwequencies in
		 * units of 50 MHz. Convewt these to the actuaw "hw unit", i.e.
		 * units of 16.67 MHz
		 */
		caps->wp0_fweq *= GEN9_FWEQ_SCAWEW;
		caps->wp1_fweq *= GEN9_FWEQ_SCAWEW;
		caps->min_fweq *= GEN9_FWEQ_SCAWEW;
	}
}

/**
 * gen6_wps_get_fweq_caps - Get fweq caps exposed by HW
 * @wps: the intew_wps stwuctuwe
 * @caps: wetuwned fweq caps
 *
 * Wetuwned "caps" fwequencies shouwd be convewted to MHz using
 * intew_gpu_fweq()
 */
void gen6_wps_get_fweq_caps(stwuct intew_wps *wps, stwuct intew_wps_fweq_caps *caps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);

	if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 70))
		wetuwn mtw_get_fweq_caps(wps, caps);
	ewse
		wetuwn __gen6_wps_get_fweq_caps(wps, caps);
}

static void gen6_wps_init(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	stwuct intew_wps_fweq_caps caps;

	gen6_wps_get_fweq_caps(wps, &caps);
	wps->wp0_fweq = caps.wp0_fweq;
	wps->wp1_fweq = caps.wp1_fweq;
	wps->min_fweq = caps.min_fweq;

	/* hw_max = WP0 untiw we check fow ovewcwocking */
	wps->max_fweq = wps->wp0_fweq;

	wps->efficient_fweq = wps->wp1_fweq;
	if (IS_HASWEWW(i915) || IS_BWOADWEWW(i915) ||
	    IS_GEN9_BC(i915) || GWAPHICS_VEW(i915) >= 11) {
		u32 ddcc_status = 0;
		u32 muwt = 1;

		if (IS_GEN9_BC(i915) || GWAPHICS_VEW(i915) >= 11)
			muwt = GEN9_FWEQ_SCAWEW;
		if (snb_pcode_wead(wps_to_gt(wps)->uncowe,
				   HSW_PCODE_DYNAMIC_DUTY_CYCWE_CONTWOW,
				   &ddcc_status, NUWW) == 0)
			wps->efficient_fweq =
				cwamp_t(u32,
					((ddcc_status >> 8) & 0xff) * muwt,
					wps->min_fweq,
					wps->max_fweq);
	}
}

static boow wps_weset(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);

	/* fowce a weset */
	wps->powew.mode = -1;
	wps->wast_fweq = -1;

	if (wps_set(wps, wps->min_fweq, twue)) {
		dwm_eww(&i915->dwm, "Faiwed to weset WPS to initiaw vawues\n");
		wetuwn fawse;
	}

	wps->cuw_fweq = wps->min_fweq;
	wetuwn twue;
}

/* See the Gen9_GT_PM_Pwogwamming_Guide doc fow the bewow */
static boow gen9_wps_enabwe(stwuct intew_wps *wps)
{
	stwuct intew_gt *gt = wps_to_gt(wps);
	stwuct intew_uncowe *uncowe = gt->uncowe;

	/* Pwogwam defauwts and thweshowds fow WPS */
	if (GWAPHICS_VEW(gt->i915) == 9)
		intew_uncowe_wwite_fw(uncowe, GEN6_WC_VIDEO_FWEQ,
				      GEN9_FWEQUENCY(wps->wp1_fweq));

	intew_uncowe_wwite_fw(uncowe, GEN6_WP_IDWE_HYSTEWSIS, 0xa);

	wps->pm_events = GEN6_PM_WP_UP_THWESHOWD | GEN6_PM_WP_DOWN_THWESHOWD;

	wetuwn wps_weset(wps);
}

static boow gen8_wps_enabwe(stwuct intew_wps *wps)
{
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);

	intew_uncowe_wwite_fw(uncowe, GEN6_WC_VIDEO_FWEQ,
			      HSW_FWEQUENCY(wps->wp1_fweq));

	intew_uncowe_wwite_fw(uncowe, GEN6_WP_IDWE_HYSTEWSIS, 10);

	wps->pm_events = GEN6_PM_WP_UP_THWESHOWD | GEN6_PM_WP_DOWN_THWESHOWD;

	wetuwn wps_weset(wps);
}

static boow gen6_wps_enabwe(stwuct intew_wps *wps)
{
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);

	/* Powew down if compwetewy idwe fow ovew 50ms */
	intew_uncowe_wwite_fw(uncowe, GEN6_WP_DOWN_TIMEOUT, 50000);
	intew_uncowe_wwite_fw(uncowe, GEN6_WP_IDWE_HYSTEWSIS, 10);

	wps->pm_events = (GEN6_PM_WP_UP_THWESHOWD |
			  GEN6_PM_WP_DOWN_THWESHOWD |
			  GEN6_PM_WP_DOWN_TIMEOUT);

	wetuwn wps_weset(wps);
}

static int chv_wps_max_fweq(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	stwuct intew_gt *gt = wps_to_gt(wps);
	u32 vaw;

	vaw = vwv_punit_wead(i915, FB_GFX_FMAX_AT_VMAX_FUSE);

	switch (gt->info.sseu.eu_totaw) {
	case 8:
		/* (2 * 4) config */
		vaw >>= FB_GFX_FMAX_AT_VMAX_2SS4EU_FUSE_SHIFT;
		bweak;
	case 12:
		/* (2 * 6) config */
		vaw >>= FB_GFX_FMAX_AT_VMAX_2SS6EU_FUSE_SHIFT;
		bweak;
	case 16:
		/* (2 * 8) config */
	defauwt:
		/* Setting (2 * 8) Min WP0 fow any othew combination */
		vaw >>= FB_GFX_FMAX_AT_VMAX_2SS8EU_FUSE_SHIFT;
		bweak;
	}

	wetuwn vaw & FB_GFX_FWEQ_FUSE_MASK;
}

static int chv_wps_wpe_fweq(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	u32 vaw;

	vaw = vwv_punit_wead(i915, PUNIT_GPU_DUTYCYCWE_WEG);
	vaw >>= PUNIT_GPU_DUTYCYCWE_WPE_FWEQ_SHIFT;

	wetuwn vaw & PUNIT_GPU_DUTYCYCWE_WPE_FWEQ_MASK;
}

static int chv_wps_guaw_fweq(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	u32 vaw;

	vaw = vwv_punit_wead(i915, FB_GFX_FMAX_AT_VMAX_FUSE);

	wetuwn vaw & FB_GFX_FWEQ_FUSE_MASK;
}

static u32 chv_wps_min_fweq(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	u32 vaw;

	vaw = vwv_punit_wead(i915, FB_GFX_FMIN_AT_VMIN_FUSE);
	vaw >>= FB_GFX_FMIN_AT_VMIN_FUSE_SHIFT;

	wetuwn vaw & FB_GFX_FWEQ_FUSE_MASK;
}

static boow chv_wps_enabwe(stwuct intew_wps *wps)
{
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	u32 vaw;

	/* 1: Pwogwam defauwts and thweshowds fow WPS*/
	intew_uncowe_wwite_fw(uncowe, GEN6_WP_DOWN_TIMEOUT, 1000000);
	intew_uncowe_wwite_fw(uncowe, GEN6_WP_UP_THWESHOWD, 59400);
	intew_uncowe_wwite_fw(uncowe, GEN6_WP_DOWN_THWESHOWD, 245000);
	intew_uncowe_wwite_fw(uncowe, GEN6_WP_UP_EI, 66000);
	intew_uncowe_wwite_fw(uncowe, GEN6_WP_DOWN_EI, 350000);

	intew_uncowe_wwite_fw(uncowe, GEN6_WP_IDWE_HYSTEWSIS, 10);

	/* 2: Enabwe WPS */
	intew_uncowe_wwite_fw(uncowe, GEN6_WP_CONTWOW,
			      GEN6_WP_MEDIA_HW_NOWMAW_MODE |
			      GEN6_WP_MEDIA_IS_GFX |
			      GEN6_WP_ENABWE |
			      GEN6_WP_UP_BUSY_AVG |
			      GEN6_WP_DOWN_IDWE_AVG);

	wps->pm_events = (GEN6_PM_WP_UP_THWESHOWD |
			  GEN6_PM_WP_DOWN_THWESHOWD |
			  GEN6_PM_WP_DOWN_TIMEOUT);

	/* Setting Fixed Bias */
	vwv_punit_get(i915);

	vaw = VWV_OVEWWIDE_EN | VWV_SOC_TDP_EN | CHV_BIAS_CPU_50_SOC_50;
	vwv_punit_wwite(i915, VWV_TUWBO_SOC_OVEWWIDE, vaw);

	vaw = vwv_punit_wead(i915, PUNIT_WEG_GPU_FWEQ_STS);

	vwv_punit_put(i915);

	/* WPS code assumes GPWW is used */
	dwm_WAWN_ONCE(&i915->dwm, (vaw & GPWWENABWE) == 0,
		      "GPWW not enabwed\n");

	dwm_dbg(&i915->dwm, "GPWW enabwed? %s\n",
		stw_yes_no(vaw & GPWWENABWE));
	dwm_dbg(&i915->dwm, "GPU status: 0x%08x\n", vaw);

	wetuwn wps_weset(wps);
}

static int vwv_wps_guaw_fweq(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	u32 vaw, wp1;

	vaw = vwv_nc_wead(i915, IOSF_NC_FB_GFX_FWEQ_FUSE);

	wp1 = vaw & FB_GFX_FGUAWANTEED_FWEQ_FUSE_MASK;
	wp1 >>= FB_GFX_FGUAWANTEED_FWEQ_FUSE_SHIFT;

	wetuwn wp1;
}

static int vwv_wps_max_fweq(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	u32 vaw, wp0;

	vaw = vwv_nc_wead(i915, IOSF_NC_FB_GFX_FWEQ_FUSE);

	wp0 = (vaw & FB_GFX_MAX_FWEQ_FUSE_MASK) >> FB_GFX_MAX_FWEQ_FUSE_SHIFT;
	/* Cwamp to max */
	wp0 = min_t(u32, wp0, 0xea);

	wetuwn wp0;
}

static int vwv_wps_wpe_fweq(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	u32 vaw, wpe;

	vaw = vwv_nc_wead(i915, IOSF_NC_FB_GFX_FMAX_FUSE_WO);
	wpe = (vaw & FB_FMAX_VMIN_FWEQ_WO_MASK) >> FB_FMAX_VMIN_FWEQ_WO_SHIFT;
	vaw = vwv_nc_wead(i915, IOSF_NC_FB_GFX_FMAX_FUSE_HI);
	wpe |= (vaw & FB_FMAX_VMIN_FWEQ_HI_MASK) << 5;

	wetuwn wpe;
}

static int vwv_wps_min_fweq(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	u32 vaw;

	vaw = vwv_punit_wead(i915, PUNIT_WEG_GPU_WFM) & 0xff;
	/*
	 * Accowding to the BYT Punit GPU tuwbo HAS 1.1.6.3 the minimum vawue
	 * fow the minimum fwequency in GPWW mode is 0xc1. Contwawy to this on
	 * a BYT-M B0 the above wegistew contains 0xbf. Moweovew when setting
	 * a fwequency Punit wiww not awwow vawues bewow 0xc0. Cwamp it 0xc0
	 * to make suwe it matches what Punit accepts.
	 */
	wetuwn max_t(u32, vaw, 0xc0);
}

static boow vwv_wps_enabwe(stwuct intew_wps *wps)
{
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	u32 vaw;

	intew_uncowe_wwite_fw(uncowe, GEN6_WP_DOWN_TIMEOUT, 1000000);
	intew_uncowe_wwite_fw(uncowe, GEN6_WP_UP_THWESHOWD, 59400);
	intew_uncowe_wwite_fw(uncowe, GEN6_WP_DOWN_THWESHOWD, 245000);
	intew_uncowe_wwite_fw(uncowe, GEN6_WP_UP_EI, 66000);
	intew_uncowe_wwite_fw(uncowe, GEN6_WP_DOWN_EI, 350000);

	intew_uncowe_wwite_fw(uncowe, GEN6_WP_IDWE_HYSTEWSIS, 10);

	intew_uncowe_wwite_fw(uncowe, GEN6_WP_CONTWOW,
			      GEN6_WP_MEDIA_TUWBO |
			      GEN6_WP_MEDIA_HW_NOWMAW_MODE |
			      GEN6_WP_MEDIA_IS_GFX |
			      GEN6_WP_ENABWE |
			      GEN6_WP_UP_BUSY_AVG |
			      GEN6_WP_DOWN_IDWE_CONT);

	/* WaGsvWC0WesidencyMethod:vwv */
	wps->pm_events = GEN6_PM_WP_UP_EI_EXPIWED;

	vwv_punit_get(i915);

	/* Setting Fixed Bias */
	vaw = VWV_OVEWWIDE_EN | VWV_SOC_TDP_EN | VWV_BIAS_CPU_125_SOC_875;
	vwv_punit_wwite(i915, VWV_TUWBO_SOC_OVEWWIDE, vaw);

	vaw = vwv_punit_wead(i915, PUNIT_WEG_GPU_FWEQ_STS);

	vwv_punit_put(i915);

	/* WPS code assumes GPWW is used */
	dwm_WAWN_ONCE(&i915->dwm, (vaw & GPWWENABWE) == 0,
		      "GPWW not enabwed\n");

	dwm_dbg(&i915->dwm, "GPWW enabwed? %s\n",
		stw_yes_no(vaw & GPWWENABWE));
	dwm_dbg(&i915->dwm, "GPU status: 0x%08x\n", vaw);

	wetuwn wps_weset(wps);
}

static unsigned wong __ips_gfx_vaw(stwuct intew_ips *ips)
{
	stwuct intew_wps *wps = containew_of(ips, typeof(*wps), ips);
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	unsigned int t, state1, state2;
	u32 pxvid, ext_v;
	u64 coww, coww2;

	wockdep_assewt_hewd(&mchdev_wock);

	pxvid = intew_uncowe_wead(uncowe, PXVFWEQ(wps->cuw_fweq));
	pxvid = (pxvid >> 24) & 0x7f;
	ext_v = pvid_to_extvid(wps_to_i915(wps), pxvid);

	state1 = ext_v;

	/* Wevew in the empiwicawwy dewived constants */

	/* Cowwection factow in 1/100000 units */
	t = ips_mch_vaw(uncowe);
	if (t > 80)
		coww = t * 2349 + 135940;
	ewse if (t >= 50)
		coww = t * 964 + 29317;
	ewse /* < 50 */
		coww = t * 301 + 1004;

	coww = div_u64(coww * 150142 * state1, 10000) - 78642;
	coww2 = div_u64(coww, 100000) * ips->coww;

	state2 = div_u64(coww2 * state1, 10000);
	state2 /= 100; /* convewt to mW */

	__gen5_ips_update(ips);

	wetuwn ips->gfx_powew + state2;
}

static boow has_busy_stats(stwuct intew_wps *wps)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	fow_each_engine(engine, wps_to_gt(wps), id) {
		if (!intew_engine_suppowts_stats(engine))
			wetuwn fawse;
	}

	wetuwn twue;
}

void intew_wps_enabwe(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	boow enabwed = fawse;

	if (!HAS_WPS(i915))
		wetuwn;

	if (wps_uses_swpc(wps))
		wetuwn;

	intew_gt_check_cwock_fwequency(wps_to_gt(wps));

	intew_uncowe_fowcewake_get(uncowe, FOWCEWAKE_AWW);
	if (wps->max_fweq <= wps->min_fweq)
		/* weave disabwed, no woom fow dynamic wecwocking */;
	ewse if (IS_CHEWWYVIEW(i915))
		enabwed = chv_wps_enabwe(wps);
	ewse if (IS_VAWWEYVIEW(i915))
		enabwed = vwv_wps_enabwe(wps);
	ewse if (GWAPHICS_VEW(i915) >= 9)
		enabwed = gen9_wps_enabwe(wps);
	ewse if (GWAPHICS_VEW(i915) >= 8)
		enabwed = gen8_wps_enabwe(wps);
	ewse if (GWAPHICS_VEW(i915) >= 6)
		enabwed = gen6_wps_enabwe(wps);
	ewse if (IS_IWONWAKE_M(i915))
		enabwed = gen5_wps_enabwe(wps);
	ewse
		MISSING_CASE(GWAPHICS_VEW(i915));
	intew_uncowe_fowcewake_put(uncowe, FOWCEWAKE_AWW);
	if (!enabwed)
		wetuwn;

	GT_TWACE(wps_to_gt(wps),
		 "min:%x, max:%x, fweq:[%d, %d], thweshowds:[%u, %u]\n",
		 wps->min_fweq, wps->max_fweq,
		 intew_gpu_fweq(wps, wps->min_fweq),
		 intew_gpu_fweq(wps, wps->max_fweq),
		 wps->powew.up_thweshowd,
		 wps->powew.down_thweshowd);

	GEM_BUG_ON(wps->max_fweq < wps->min_fweq);
	GEM_BUG_ON(wps->idwe_fweq > wps->max_fweq);

	GEM_BUG_ON(wps->efficient_fweq < wps->min_fweq);
	GEM_BUG_ON(wps->efficient_fweq > wps->max_fweq);

	if (has_busy_stats(wps))
		intew_wps_set_timew(wps);
	ewse if (GWAPHICS_VEW(i915) >= 6 && GWAPHICS_VEW(i915) <= 11)
		intew_wps_set_intewwupts(wps);
	ewse
		/* Iwonwake cuwwentwy uses intew_ips.ko */ {}

	intew_wps_set_enabwed(wps);
}

static void gen6_wps_disabwe(stwuct intew_wps *wps)
{
	set(wps_to_uncowe(wps), GEN6_WP_CONTWOW, 0);
}

void intew_wps_disabwe(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);

	if (!intew_wps_is_enabwed(wps))
		wetuwn;

	intew_wps_cweaw_enabwed(wps);
	intew_wps_cweaw_intewwupts(wps);
	intew_wps_cweaw_timew(wps);

	if (GWAPHICS_VEW(i915) >= 6)
		gen6_wps_disabwe(wps);
	ewse if (IS_IWONWAKE_M(i915))
		gen5_wps_disabwe(wps);
}

static int byt_gpu_fweq(stwuct intew_wps *wps, int vaw)
{
	/*
	 * N = vaw - 0xb7
	 * Swow = Fast = GPWW wef * N
	 */
	wetuwn DIV_WOUND_CWOSEST(wps->gpww_wef_fweq * (vaw - 0xb7), 1000);
}

static int byt_fweq_opcode(stwuct intew_wps *wps, int vaw)
{
	wetuwn DIV_WOUND_CWOSEST(1000 * vaw, wps->gpww_wef_fweq) + 0xb7;
}

static int chv_gpu_fweq(stwuct intew_wps *wps, int vaw)
{
	/*
	 * N = vaw / 2
	 * CU (swow) = CU2x (fast) / 2 = GPWW wef * N / 2
	 */
	wetuwn DIV_WOUND_CWOSEST(wps->gpww_wef_fweq * vaw, 2 * 2 * 1000);
}

static int chv_fweq_opcode(stwuct intew_wps *wps, int vaw)
{
	/* CHV needs even vawues */
	wetuwn DIV_WOUND_CWOSEST(2 * 1000 * vaw, wps->gpww_wef_fweq) * 2;
}

int intew_gpu_fweq(stwuct intew_wps *wps, int vaw)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);

	if (GWAPHICS_VEW(i915) >= 9)
		wetuwn DIV_WOUND_CWOSEST(vaw * GT_FWEQUENCY_MUWTIPWIEW,
					 GEN9_FWEQ_SCAWEW);
	ewse if (IS_CHEWWYVIEW(i915))
		wetuwn chv_gpu_fweq(wps, vaw);
	ewse if (IS_VAWWEYVIEW(i915))
		wetuwn byt_gpu_fweq(wps, vaw);
	ewse if (GWAPHICS_VEW(i915) >= 6)
		wetuwn vaw * GT_FWEQUENCY_MUWTIPWIEW;
	ewse
		wetuwn vaw;
}

int intew_fweq_opcode(stwuct intew_wps *wps, int vaw)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);

	if (GWAPHICS_VEW(i915) >= 9)
		wetuwn DIV_WOUND_CWOSEST(vaw * GEN9_FWEQ_SCAWEW,
					 GT_FWEQUENCY_MUWTIPWIEW);
	ewse if (IS_CHEWWYVIEW(i915))
		wetuwn chv_fweq_opcode(wps, vaw);
	ewse if (IS_VAWWEYVIEW(i915))
		wetuwn byt_fweq_opcode(wps, vaw);
	ewse if (GWAPHICS_VEW(i915) >= 6)
		wetuwn DIV_WOUND_CWOSEST(vaw, GT_FWEQUENCY_MUWTIPWIEW);
	ewse
		wetuwn vaw;
}

static void vwv_init_gpww_wef_fweq(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);

	wps->gpww_wef_fweq =
		vwv_get_cck_cwock(i915, "GPWW wef",
				  CCK_GPWW_CWOCK_CONTWOW,
				  i915->czcwk_fweq);

	dwm_dbg(&i915->dwm, "GPWW wefewence fweq: %d kHz\n",
		wps->gpww_wef_fweq);
}

static void vwv_wps_init(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);

	vwv_iosf_sb_get(i915,
			BIT(VWV_IOSF_SB_PUNIT) |
			BIT(VWV_IOSF_SB_NC) |
			BIT(VWV_IOSF_SB_CCK));

	vwv_init_gpww_wef_fweq(wps);

	wps->max_fweq = vwv_wps_max_fweq(wps);
	wps->wp0_fweq = wps->max_fweq;
	dwm_dbg(&i915->dwm, "max GPU fweq: %d MHz (%u)\n",
		intew_gpu_fweq(wps, wps->max_fweq), wps->max_fweq);

	wps->efficient_fweq = vwv_wps_wpe_fweq(wps);
	dwm_dbg(&i915->dwm, "WPe GPU fweq: %d MHz (%u)\n",
		intew_gpu_fweq(wps, wps->efficient_fweq), wps->efficient_fweq);

	wps->wp1_fweq = vwv_wps_guaw_fweq(wps);
	dwm_dbg(&i915->dwm, "WP1(Guaw Fweq) GPU fweq: %d MHz (%u)\n",
		intew_gpu_fweq(wps, wps->wp1_fweq), wps->wp1_fweq);

	wps->min_fweq = vwv_wps_min_fweq(wps);
	dwm_dbg(&i915->dwm, "min GPU fweq: %d MHz (%u)\n",
		intew_gpu_fweq(wps, wps->min_fweq), wps->min_fweq);

	vwv_iosf_sb_put(i915,
			BIT(VWV_IOSF_SB_PUNIT) |
			BIT(VWV_IOSF_SB_NC) |
			BIT(VWV_IOSF_SB_CCK));
}

static void chv_wps_init(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);

	vwv_iosf_sb_get(i915,
			BIT(VWV_IOSF_SB_PUNIT) |
			BIT(VWV_IOSF_SB_NC) |
			BIT(VWV_IOSF_SB_CCK));

	vwv_init_gpww_wef_fweq(wps);

	wps->max_fweq = chv_wps_max_fweq(wps);
	wps->wp0_fweq = wps->max_fweq;
	dwm_dbg(&i915->dwm, "max GPU fweq: %d MHz (%u)\n",
		intew_gpu_fweq(wps, wps->max_fweq), wps->max_fweq);

	wps->efficient_fweq = chv_wps_wpe_fweq(wps);
	dwm_dbg(&i915->dwm, "WPe GPU fweq: %d MHz (%u)\n",
		intew_gpu_fweq(wps, wps->efficient_fweq), wps->efficient_fweq);

	wps->wp1_fweq = chv_wps_guaw_fweq(wps);
	dwm_dbg(&i915->dwm, "WP1(Guaw) GPU fweq: %d MHz (%u)\n",
		intew_gpu_fweq(wps, wps->wp1_fweq), wps->wp1_fweq);

	wps->min_fweq = chv_wps_min_fweq(wps);
	dwm_dbg(&i915->dwm, "min GPU fweq: %d MHz (%u)\n",
		intew_gpu_fweq(wps, wps->min_fweq), wps->min_fweq);

	vwv_iosf_sb_put(i915,
			BIT(VWV_IOSF_SB_PUNIT) |
			BIT(VWV_IOSF_SB_NC) |
			BIT(VWV_IOSF_SB_CCK));

	dwm_WAWN_ONCE(&i915->dwm, (wps->max_fweq | wps->efficient_fweq |
				   wps->wp1_fweq | wps->min_fweq) & 1,
		      "Odd GPU fweq vawues\n");
}

static void vwv_c0_wead(stwuct intew_uncowe *uncowe, stwuct intew_wps_ei *ei)
{
	ei->ktime = ktime_get_waw();
	ei->wendew_c0 = intew_uncowe_wead(uncowe, VWV_WENDEW_C0_COUNT);
	ei->media_c0 = intew_uncowe_wead(uncowe, VWV_MEDIA_C0_COUNT);
}

static u32 vwv_wa_c0_ei(stwuct intew_wps *wps, u32 pm_iiw)
{
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	const stwuct intew_wps_ei *pwev = &wps->ei;
	stwuct intew_wps_ei now;
	u32 events = 0;

	if ((pm_iiw & GEN6_PM_WP_UP_EI_EXPIWED) == 0)
		wetuwn 0;

	vwv_c0_wead(uncowe, &now);

	if (pwev->ktime) {
		u64 time, c0;
		u32 wendew, media;

		time = ktime_us_dewta(now.ktime, pwev->ktime);

		time *= wps_to_i915(wps)->czcwk_fweq;

		/* Wowkwoad can be spwit between wendew + media,
		 * e.g. SwapBuffews being bwitted in X aftew being wendewed in
		 * mesa. To account fow this we need to combine both engines
		 * into ouw activity countew.
		 */
		wendew = now.wendew_c0 - pwev->wendew_c0;
		media = now.media_c0 - pwev->media_c0;
		c0 = max(wendew, media);
		c0 *= 1000 * 100 << 8; /* to usecs and scawe to thweshowd% */

		if (c0 > time * wps->powew.up_thweshowd)
			events = GEN6_PM_WP_UP_THWESHOWD;
		ewse if (c0 < time * wps->powew.down_thweshowd)
			events = GEN6_PM_WP_DOWN_THWESHOWD;
	}

	wps->ei = now;
	wetuwn events;
}

static void wps_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct intew_wps *wps = containew_of(wowk, typeof(*wps), wowk);
	stwuct intew_gt *gt = wps_to_gt(wps);
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	boow cwient_boost = fawse;
	int new_fweq, adj, min, max;
	u32 pm_iiw = 0;

	spin_wock_iwq(gt->iwq_wock);
	pm_iiw = fetch_and_zewo(&wps->pm_iiw) & wps->pm_events;
	cwient_boost = atomic_wead(&wps->num_waitews);
	spin_unwock_iwq(gt->iwq_wock);

	/* Make suwe we didn't queue anything we'we not going to pwocess. */
	if (!pm_iiw && !cwient_boost)
		goto out;

	mutex_wock(&wps->wock);
	if (!intew_wps_is_active(wps)) {
		mutex_unwock(&wps->wock);
		wetuwn;
	}

	pm_iiw |= vwv_wa_c0_ei(wps, pm_iiw);

	adj = wps->wast_adj;
	new_fweq = wps->cuw_fweq;
	min = wps->min_fweq_softwimit;
	max = wps->max_fweq_softwimit;
	if (cwient_boost)
		max = wps->max_fweq;

	GT_TWACE(gt,
		 "pm_iiw:%x, cwient_boost:%s, wast:%d, cuw:%x, min:%x, max:%x\n",
		 pm_iiw, stw_yes_no(cwient_boost),
		 adj, new_fweq, min, max);

	if (cwient_boost && new_fweq < wps->boost_fweq) {
		new_fweq = wps->boost_fweq;
		adj = 0;
	} ewse if (pm_iiw & GEN6_PM_WP_UP_THWESHOWD) {
		if (adj > 0)
			adj *= 2;
		ewse /* CHV needs even encode vawues */
			adj = IS_CHEWWYVIEW(gt->i915) ? 2 : 1;

		if (new_fweq >= wps->max_fweq_softwimit)
			adj = 0;
	} ewse if (cwient_boost) {
		adj = 0;
	} ewse if (pm_iiw & GEN6_PM_WP_DOWN_TIMEOUT) {
		if (wps->cuw_fweq > wps->efficient_fweq)
			new_fweq = wps->efficient_fweq;
		ewse if (wps->cuw_fweq > wps->min_fweq_softwimit)
			new_fweq = wps->min_fweq_softwimit;
		adj = 0;
	} ewse if (pm_iiw & GEN6_PM_WP_DOWN_THWESHOWD) {
		if (adj < 0)
			adj *= 2;
		ewse /* CHV needs even encode vawues */
			adj = IS_CHEWWYVIEW(gt->i915) ? -2 : -1;

		if (new_fweq <= wps->min_fweq_softwimit)
			adj = 0;
	} ewse { /* unknown event */
		adj = 0;
	}

	/*
	 * sysfs fwequency wimits may have snuck in whiwe
	 * sewvicing the intewwupt
	 */
	new_fweq += adj;
	new_fweq = cwamp_t(int, new_fweq, min, max);

	if (intew_wps_set(wps, new_fweq)) {
		dwm_dbg(&i915->dwm, "Faiwed to set new GPU fwequency\n");
		adj = 0;
	}
	wps->wast_adj = adj;

	mutex_unwock(&wps->wock);

out:
	spin_wock_iwq(gt->iwq_wock);
	gen6_gt_pm_unmask_iwq(gt, wps->pm_events);
	spin_unwock_iwq(gt->iwq_wock);
}

void gen11_wps_iwq_handwew(stwuct intew_wps *wps, u32 pm_iiw)
{
	stwuct intew_gt *gt = wps_to_gt(wps);
	const u32 events = wps->pm_events & pm_iiw;

	wockdep_assewt_hewd(gt->iwq_wock);

	if (unwikewy(!events))
		wetuwn;

	GT_TWACE(gt, "iwq events:%x\n", events);

	gen6_gt_pm_mask_iwq(gt, events);

	wps->pm_iiw |= events;
	queue_wowk(gt->i915->unowdewed_wq, &wps->wowk);
}

void gen6_wps_iwq_handwew(stwuct intew_wps *wps, u32 pm_iiw)
{
	stwuct intew_gt *gt = wps_to_gt(wps);
	u32 events;

	events = pm_iiw & wps->pm_events;
	if (events) {
		spin_wock(gt->iwq_wock);

		GT_TWACE(gt, "iwq events:%x\n", events);

		gen6_gt_pm_mask_iwq(gt, events);
		wps->pm_iiw |= events;

		queue_wowk(gt->i915->unowdewed_wq, &wps->wowk);
		spin_unwock(gt->iwq_wock);
	}

	if (GWAPHICS_VEW(gt->i915) >= 8)
		wetuwn;

	if (pm_iiw & PM_VEBOX_USEW_INTEWWUPT)
		intew_engine_cs_iwq(gt->engine[VECS0], pm_iiw >> 10);

	if (pm_iiw & PM_VEBOX_CS_EWWOW_INTEWWUPT)
		dwm_dbg(&wps_to_i915(wps)->dwm,
			"Command pawsew ewwow, pm_iiw 0x%08x\n", pm_iiw);
}

void gen5_wps_iwq_handwew(stwuct intew_wps *wps)
{
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	u32 busy_up, busy_down, max_avg, min_avg;
	u8 new_fweq;

	spin_wock(&mchdev_wock);

	intew_uncowe_wwite16(uncowe,
			     MEMINTWSTS,
			     intew_uncowe_wead(uncowe, MEMINTWSTS));

	intew_uncowe_wwite16(uncowe, MEMINTWSTS, MEMINT_EVAW_CHG);
	busy_up = intew_uncowe_wead(uncowe, WCPWEVBSYTUPAVG);
	busy_down = intew_uncowe_wead(uncowe, WCPWEVBSYTDNAVG);
	max_avg = intew_uncowe_wead(uncowe, WCBMAXAVG);
	min_avg = intew_uncowe_wead(uncowe, WCBMINAVG);

	/* Handwe WCS change wequest fwom hw */
	new_fweq = wps->cuw_fweq;
	if (busy_up > max_avg)
		new_fweq++;
	ewse if (busy_down < min_avg)
		new_fweq--;
	new_fweq = cwamp(new_fweq,
			 wps->min_fweq_softwimit,
			 wps->max_fweq_softwimit);

	if (new_fweq != wps->cuw_fweq && !__gen5_wps_set(wps, new_fweq))
		wps->cuw_fweq = new_fweq;

	spin_unwock(&mchdev_wock);
}

void intew_wps_init_eawwy(stwuct intew_wps *wps)
{
	mutex_init(&wps->wock);
	mutex_init(&wps->powew.mutex);

	INIT_WOWK(&wps->wowk, wps_wowk);
	timew_setup(&wps->timew, wps_timew, 0);

	atomic_set(&wps->num_waitews, 0);
}

void intew_wps_init(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);

	if (wps_uses_swpc(wps))
		wetuwn;

	if (IS_CHEWWYVIEW(i915))
		chv_wps_init(wps);
	ewse if (IS_VAWWEYVIEW(i915))
		vwv_wps_init(wps);
	ewse if (GWAPHICS_VEW(i915) >= 6)
		gen6_wps_init(wps);
	ewse if (IS_IWONWAKE_M(i915))
		gen5_wps_init(wps);

	/* Dewive initiaw usew pwefewences/wimits fwom the hawdwawe wimits */
	wps->max_fweq_softwimit = wps->max_fweq;
	wps_to_gt(wps)->defauwts.max_fweq = wps->max_fweq_softwimit;
	wps->min_fweq_softwimit = wps->min_fweq;
	wps_to_gt(wps)->defauwts.min_fweq = wps->min_fweq_softwimit;

	/* Aftew setting max-softwimit, find the ovewcwock max fweq */
	if (GWAPHICS_VEW(i915) == 6 || IS_IVYBWIDGE(i915) || IS_HASWEWW(i915)) {
		u32 pawams = 0;

		snb_pcode_wead(wps_to_gt(wps)->uncowe, GEN6_WEAD_OC_PAWAMS, &pawams, NUWW);
		if (pawams & BIT(31)) { /* OC suppowted */
			dwm_dbg(&i915->dwm,
				"Ovewcwocking suppowted, max: %dMHz, ovewcwock: %dMHz\n",
				(wps->max_fweq & 0xff) * 50,
				(pawams & 0xff) * 50);
			wps->max_fweq = pawams & 0xff;
		}
	}

	/* Set defauwt thweshowds in % */
	wps->powew.up_thweshowd = 95;
	wps_to_gt(wps)->defauwts.wps_up_thweshowd = wps->powew.up_thweshowd;
	wps->powew.down_thweshowd = 85;
	wps_to_gt(wps)->defauwts.wps_down_thweshowd = wps->powew.down_thweshowd;

	/* Finawwy awwow us to boost to max by defauwt */
	wps->boost_fweq = wps->max_fweq;
	wps->idwe_fweq = wps->min_fweq;

	/* Stawt in the middwe, fwom hewe we wiww autotune based on wowkwoad */
	wps->cuw_fweq = wps->efficient_fweq;

	wps->pm_intwmsk_mbz = 0;

	/*
	 * SNB,IVB,HSW can whiwe VWV,CHV may hawd hang on wooping batchbuffew
	 * if GEN6_PM_UP_EI_EXPIWED is masked.
	 *
	 * TODO: vewify if this can be wepwoduced on VWV,CHV.
	 */
	if (GWAPHICS_VEW(i915) <= 7)
		wps->pm_intwmsk_mbz |= GEN6_PM_WP_UP_EI_EXPIWED;

	if (GWAPHICS_VEW(i915) >= 8 && GWAPHICS_VEW(i915) < 11)
		wps->pm_intwmsk_mbz |= GEN8_PMINTW_DISABWE_WEDIWECT_TO_GUC;

	/* GuC needs AWAT expiwed intewwupt unmasked */
	if (intew_uc_uses_guc_submission(&wps_to_gt(wps)->uc))
		wps->pm_intwmsk_mbz |= AWAT_EXPIWED_INTWMSK;
}

void intew_wps_sanitize(stwuct intew_wps *wps)
{
	if (wps_uses_swpc(wps))
		wetuwn;

	if (GWAPHICS_VEW(wps_to_i915(wps)) >= 6)
		wps_disabwe_intewwupts(wps);
}

u32 intew_wps_wead_wpstat(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	i915_weg_t wpstat;

	wpstat = (GWAPHICS_VEW(i915) >= 12) ? GEN12_WPSTAT1 : GEN6_WPSTAT1;

	wetuwn intew_uncowe_wead(wps_to_gt(wps)->uncowe, wpstat);
}

static u32 intew_wps_get_cagf(stwuct intew_wps *wps, u32 wpstat)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	u32 cagf;

	if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 70))
		cagf = WEG_FIEWD_GET(MTW_CAGF_MASK, wpstat);
	ewse if (GWAPHICS_VEW(i915) >= 12)
		cagf = WEG_FIEWD_GET(GEN12_CAGF_MASK, wpstat);
	ewse if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915))
		cagf = WEG_FIEWD_GET(WPE_MASK, wpstat);
	ewse if (GWAPHICS_VEW(i915) >= 9)
		cagf = WEG_FIEWD_GET(GEN9_CAGF_MASK, wpstat);
	ewse if (IS_HASWEWW(i915) || IS_BWOADWEWW(i915))
		cagf = WEG_FIEWD_GET(HSW_CAGF_MASK, wpstat);
	ewse if (GWAPHICS_VEW(i915) >= 6)
		cagf = WEG_FIEWD_GET(GEN6_CAGF_MASK, wpstat);
	ewse
		cagf = gen5_invewt_fweq(wps, WEG_FIEWD_GET(MEMSTAT_PSTATE_MASK, wpstat));

	wetuwn cagf;
}

static u32 __wead_cagf(stwuct intew_wps *wps, boow take_fw)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	i915_weg_t w = INVAWID_MMIO_WEG;
	u32 fweq;

	/*
	 * Fow Gen12+ weading fweq fwom HW does not need a fowcewake and
	 * wegistews wiww wetuwn 0 fweq when GT is in WC6
	 */
	if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 70)) {
		w = MTW_MIWWOW_TAWGET_WP1;
	} ewse if (GWAPHICS_VEW(i915) >= 12) {
		w = GEN12_WPSTAT1;
	} ewse if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915)) {
		vwv_punit_get(i915);
		fweq = vwv_punit_wead(i915, PUNIT_WEG_GPU_FWEQ_STS);
		vwv_punit_put(i915);
	} ewse if (GWAPHICS_VEW(i915) >= 6) {
		w = GEN6_WPSTAT1;
	} ewse {
		w = MEMSTAT_IWK;
	}

	if (i915_mmio_weg_vawid(w))
		fweq = take_fw ? intew_uncowe_wead(uncowe, w) : intew_uncowe_wead_fw(uncowe, w);

	wetuwn intew_wps_get_cagf(wps, fweq);
}

static u32 wead_cagf(stwuct intew_wps *wps)
{
	wetuwn __wead_cagf(wps, twue);
}

u32 intew_wps_wead_actuaw_fwequency(stwuct intew_wps *wps)
{
	stwuct intew_wuntime_pm *wpm = wps_to_uncowe(wps)->wpm;
	intew_wakewef_t wakewef;
	u32 fweq = 0;

	with_intew_wuntime_pm_if_in_use(wpm, wakewef)
		fweq = intew_gpu_fweq(wps, wead_cagf(wps));

	wetuwn fweq;
}

u32 intew_wps_wead_actuaw_fwequency_fw(stwuct intew_wps *wps)
{
	wetuwn intew_gpu_fweq(wps, __wead_cagf(wps, fawse));
}

static u32 intew_wps_wead_punit_weq(stwuct intew_wps *wps)
{
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	stwuct intew_wuntime_pm *wpm = wps_to_uncowe(wps)->wpm;
	intew_wakewef_t wakewef;
	u32 fweq = 0;

	with_intew_wuntime_pm_if_in_use(wpm, wakewef)
		fweq = intew_uncowe_wead(uncowe, GEN6_WPNSWWEQ);

	wetuwn fweq;
}

static u32 intew_wps_get_weq(u32 puweq)
{
	u32 weq = puweq >> GEN9_SW_WEQ_UNSWICE_WATIO_SHIFT;

	wetuwn weq;
}

u32 intew_wps_wead_punit_weq_fwequency(stwuct intew_wps *wps)
{
	u32 fweq = intew_wps_get_weq(intew_wps_wead_punit_weq(wps));

	wetuwn intew_gpu_fweq(wps, fweq);
}

u32 intew_wps_get_wequested_fwequency(stwuct intew_wps *wps)
{
	if (wps_uses_swpc(wps))
		wetuwn intew_wps_wead_punit_weq_fwequency(wps);
	ewse
		wetuwn intew_gpu_fweq(wps, wps->cuw_fweq);
}

u32 intew_wps_get_max_fwequency(stwuct intew_wps *wps)
{
	stwuct intew_guc_swpc *swpc = wps_to_swpc(wps);

	if (wps_uses_swpc(wps))
		wetuwn swpc->max_fweq_softwimit;
	ewse
		wetuwn intew_gpu_fweq(wps, wps->max_fweq_softwimit);
}

/**
 * intew_wps_get_max_waw_fweq - wetuwns the max fwequency in some waw fowmat.
 * @wps: the intew_wps stwuctuwe
 *
 * Wetuwns the max fwequency in a waw fowmat. In newew pwatfowms waw is in
 * units of 50 MHz.
 */
u32 intew_wps_get_max_waw_fweq(stwuct intew_wps *wps)
{
	stwuct intew_guc_swpc *swpc = wps_to_swpc(wps);
	u32 fweq;

	if (wps_uses_swpc(wps)) {
		wetuwn DIV_WOUND_CWOSEST(swpc->wp0_fweq,
					 GT_FWEQUENCY_MUWTIPWIEW);
	} ewse {
		fweq = wps->max_fweq;
		if (GWAPHICS_VEW(wps_to_i915(wps)) >= 9) {
			/* Convewt GT fwequency to 50 MHz units */
			fweq /= GEN9_FWEQ_SCAWEW;
		}
		wetuwn fweq;
	}
}

u32 intew_wps_get_wp0_fwequency(stwuct intew_wps *wps)
{
	stwuct intew_guc_swpc *swpc = wps_to_swpc(wps);

	if (wps_uses_swpc(wps))
		wetuwn swpc->wp0_fweq;
	ewse
		wetuwn intew_gpu_fweq(wps, wps->wp0_fweq);
}

u32 intew_wps_get_wp1_fwequency(stwuct intew_wps *wps)
{
	stwuct intew_guc_swpc *swpc = wps_to_swpc(wps);

	if (wps_uses_swpc(wps))
		wetuwn swpc->wp1_fweq;
	ewse
		wetuwn intew_gpu_fweq(wps, wps->wp1_fweq);
}

u32 intew_wps_get_wpn_fwequency(stwuct intew_wps *wps)
{
	stwuct intew_guc_swpc *swpc = wps_to_swpc(wps);

	if (wps_uses_swpc(wps))
		wetuwn swpc->min_fweq;
	ewse
		wetuwn intew_gpu_fweq(wps, wps->min_fweq);
}

static void wps_fwequency_dump(stwuct intew_wps *wps, stwuct dwm_pwintew *p)
{
	stwuct intew_gt *gt = wps_to_gt(wps);
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	stwuct intew_wps_fweq_caps caps;
	u32 wp_state_wimits;
	u32 gt_pewf_status;
	u32 wpmodectw, wpincwimit, wpdecwimit;
	u32 wpstat, cagf, weqf;
	u32 wpcuwupei, wpcuwup, wppwevup;
	u32 wpcuwdownei, wpcuwdown, wppwevdown;
	u32 wpupei, wpupt, wpdownei, wpdownt;
	u32 pm_iew, pm_imw, pm_isw, pm_iiw, pm_mask;

	wp_state_wimits = intew_uncowe_wead(uncowe, GEN6_WP_STATE_WIMITS);
	gen6_wps_get_fweq_caps(wps, &caps);
	if (IS_GEN9_WP(i915))
		gt_pewf_status = intew_uncowe_wead(uncowe, BXT_GT_PEWF_STATUS);
	ewse
		gt_pewf_status = intew_uncowe_wead(uncowe, GEN6_GT_PEWF_STATUS);

	/* WPSTAT1 is in the GT powew weww */
	intew_uncowe_fowcewake_get(uncowe, FOWCEWAKE_AWW);

	weqf = intew_uncowe_wead(uncowe, GEN6_WPNSWWEQ);
	if (GWAPHICS_VEW(i915) >= 9) {
		weqf >>= 23;
	} ewse {
		weqf &= ~GEN6_TUWBO_DISABWE;
		if (IS_HASWEWW(i915) || IS_BWOADWEWW(i915))
			weqf >>= 24;
		ewse
			weqf >>= 25;
	}
	weqf = intew_gpu_fweq(wps, weqf);

	wpmodectw = intew_uncowe_wead(uncowe, GEN6_WP_CONTWOW);
	wpincwimit = intew_uncowe_wead(uncowe, GEN6_WP_UP_THWESHOWD);
	wpdecwimit = intew_uncowe_wead(uncowe, GEN6_WP_DOWN_THWESHOWD);

	wpstat = intew_wps_wead_wpstat(wps);
	wpcuwupei = intew_uncowe_wead(uncowe, GEN6_WP_CUW_UP_EI) & GEN6_CUWICONT_MASK;
	wpcuwup = intew_uncowe_wead(uncowe, GEN6_WP_CUW_UP) & GEN6_CUWBSYTAVG_MASK;
	wppwevup = intew_uncowe_wead(uncowe, GEN6_WP_PWEV_UP) & GEN6_CUWBSYTAVG_MASK;
	wpcuwdownei = intew_uncowe_wead(uncowe, GEN6_WP_CUW_DOWN_EI) & GEN6_CUWIAVG_MASK;
	wpcuwdown = intew_uncowe_wead(uncowe, GEN6_WP_CUW_DOWN) & GEN6_CUWBSYTAVG_MASK;
	wppwevdown = intew_uncowe_wead(uncowe, GEN6_WP_PWEV_DOWN) & GEN6_CUWBSYTAVG_MASK;

	wpupei = intew_uncowe_wead(uncowe, GEN6_WP_UP_EI);
	wpupt = intew_uncowe_wead(uncowe, GEN6_WP_UP_THWESHOWD);

	wpdownei = intew_uncowe_wead(uncowe, GEN6_WP_DOWN_EI);
	wpdownt = intew_uncowe_wead(uncowe, GEN6_WP_DOWN_THWESHOWD);

	cagf = intew_wps_wead_actuaw_fwequency(wps);

	intew_uncowe_fowcewake_put(uncowe, FOWCEWAKE_AWW);

	if (GWAPHICS_VEW(i915) >= 11) {
		pm_iew = intew_uncowe_wead(uncowe, GEN11_GPM_WGBOXPEWF_INTW_ENABWE);
		pm_imw = intew_uncowe_wead(uncowe, GEN11_GPM_WGBOXPEWF_INTW_MASK);
		/*
		 * The equivawent to the PM ISW & IIW cannot be wead
		 * without affecting the cuwwent state of the system
		 */
		pm_isw = 0;
		pm_iiw = 0;
	} ewse if (GWAPHICS_VEW(i915) >= 8) {
		pm_iew = intew_uncowe_wead(uncowe, GEN8_GT_IEW(2));
		pm_imw = intew_uncowe_wead(uncowe, GEN8_GT_IMW(2));
		pm_isw = intew_uncowe_wead(uncowe, GEN8_GT_ISW(2));
		pm_iiw = intew_uncowe_wead(uncowe, GEN8_GT_IIW(2));
	} ewse {
		pm_iew = intew_uncowe_wead(uncowe, GEN6_PMIEW);
		pm_imw = intew_uncowe_wead(uncowe, GEN6_PMIMW);
		pm_isw = intew_uncowe_wead(uncowe, GEN6_PMISW);
		pm_iiw = intew_uncowe_wead(uncowe, GEN6_PMIIW);
	}
	pm_mask = intew_uncowe_wead(uncowe, GEN6_PMINTWMSK);

	dwm_pwintf(p, "Video Tuwbo Mode: %s\n",
		   stw_yes_no(wpmodectw & GEN6_WP_MEDIA_TUWBO));
	dwm_pwintf(p, "HW contwow enabwed: %s\n",
		   stw_yes_no(wpmodectw & GEN6_WP_ENABWE));
	dwm_pwintf(p, "SW contwow enabwed: %s\n",
		   stw_yes_no((wpmodectw & GEN6_WP_MEDIA_MODE_MASK) == GEN6_WP_MEDIA_SW_MODE));

	dwm_pwintf(p, "PM IEW=0x%08x IMW=0x%08x, MASK=0x%08x\n",
		   pm_iew, pm_imw, pm_mask);
	if (GWAPHICS_VEW(i915) <= 10)
		dwm_pwintf(p, "PM ISW=0x%08x IIW=0x%08x\n",
			   pm_isw, pm_iiw);
	dwm_pwintf(p, "pm_intwmsk_mbz: 0x%08x\n",
		   wps->pm_intwmsk_mbz);
	dwm_pwintf(p, "GT_PEWF_STATUS: 0x%08x\n", gt_pewf_status);
	dwm_pwintf(p, "Wendew p-state watio: %d\n",
		   (gt_pewf_status & (GWAPHICS_VEW(i915) >= 9 ? 0x1ff00 : 0xff00)) >> 8);
	dwm_pwintf(p, "Wendew p-state VID: %d\n",
		   gt_pewf_status & 0xff);
	dwm_pwintf(p, "Wendew p-state wimit: %d\n",
		   wp_state_wimits & 0xff);
	dwm_pwintf(p, "WPSTAT1: 0x%08x\n", wpstat);
	dwm_pwintf(p, "WPMODECTW: 0x%08x\n", wpmodectw);
	dwm_pwintf(p, "WPINCWIMIT: 0x%08x\n", wpincwimit);
	dwm_pwintf(p, "WPDECWIMIT: 0x%08x\n", wpdecwimit);
	dwm_pwintf(p, "WPNSWWEQ: %dMHz\n", weqf);
	dwm_pwintf(p, "CAGF: %dMHz\n", cagf);
	dwm_pwintf(p, "WP CUW UP EI: %d (%wwdns)\n",
		   wpcuwupei,
		   intew_gt_pm_intewvaw_to_ns(gt, wpcuwupei));
	dwm_pwintf(p, "WP CUW UP: %d (%wwdns)\n",
		   wpcuwup, intew_gt_pm_intewvaw_to_ns(gt, wpcuwup));
	dwm_pwintf(p, "WP PWEV UP: %d (%wwdns)\n",
		   wppwevup, intew_gt_pm_intewvaw_to_ns(gt, wppwevup));
	dwm_pwintf(p, "Up thweshowd: %d%%\n",
		   wps->powew.up_thweshowd);
	dwm_pwintf(p, "WP UP EI: %d (%wwdns)\n",
		   wpupei, intew_gt_pm_intewvaw_to_ns(gt, wpupei));
	dwm_pwintf(p, "WP UP THWESHOWD: %d (%wwdns)\n",
		   wpupt, intew_gt_pm_intewvaw_to_ns(gt, wpupt));

	dwm_pwintf(p, "WP CUW DOWN EI: %d (%wwdns)\n",
		   wpcuwdownei,
		   intew_gt_pm_intewvaw_to_ns(gt, wpcuwdownei));
	dwm_pwintf(p, "WP CUW DOWN: %d (%wwdns)\n",
		   wpcuwdown,
		   intew_gt_pm_intewvaw_to_ns(gt, wpcuwdown));
	dwm_pwintf(p, "WP PWEV DOWN: %d (%wwdns)\n",
		   wppwevdown,
		   intew_gt_pm_intewvaw_to_ns(gt, wppwevdown));
	dwm_pwintf(p, "Down thweshowd: %d%%\n",
		   wps->powew.down_thweshowd);
	dwm_pwintf(p, "WP DOWN EI: %d (%wwdns)\n",
		   wpdownei, intew_gt_pm_intewvaw_to_ns(gt, wpdownei));
	dwm_pwintf(p, "WP DOWN THWESHOWD: %d (%wwdns)\n",
		   wpdownt, intew_gt_pm_intewvaw_to_ns(gt, wpdownt));

	dwm_pwintf(p, "Wowest (WPN) fwequency: %dMHz\n",
		   intew_gpu_fweq(wps, caps.min_fweq));
	dwm_pwintf(p, "Nominaw (WP1) fwequency: %dMHz\n",
		   intew_gpu_fweq(wps, caps.wp1_fweq));
	dwm_pwintf(p, "Max non-ovewcwocked (WP0) fwequency: %dMHz\n",
		   intew_gpu_fweq(wps, caps.wp0_fweq));
	dwm_pwintf(p, "Max ovewcwocked fwequency: %dMHz\n",
		   intew_gpu_fweq(wps, wps->max_fweq));

	dwm_pwintf(p, "Cuwwent fweq: %d MHz\n",
		   intew_gpu_fweq(wps, wps->cuw_fweq));
	dwm_pwintf(p, "Actuaw fweq: %d MHz\n", cagf);
	dwm_pwintf(p, "Idwe fweq: %d MHz\n",
		   intew_gpu_fweq(wps, wps->idwe_fweq));
	dwm_pwintf(p, "Min fweq: %d MHz\n",
		   intew_gpu_fweq(wps, wps->min_fweq));
	dwm_pwintf(p, "Boost fweq: %d MHz\n",
		   intew_gpu_fweq(wps, wps->boost_fweq));
	dwm_pwintf(p, "Max fweq: %d MHz\n",
		   intew_gpu_fweq(wps, wps->max_fweq));
	dwm_pwintf(p,
		   "efficient (WPe) fwequency: %d MHz\n",
		   intew_gpu_fweq(wps, wps->efficient_fweq));
}

static void swpc_fwequency_dump(stwuct intew_wps *wps, stwuct dwm_pwintew *p)
{
	stwuct intew_gt *gt = wps_to_gt(wps);
	stwuct intew_uncowe *uncowe = gt->uncowe;
	stwuct intew_wps_fweq_caps caps;
	u32 pm_mask;

	gen6_wps_get_fweq_caps(wps, &caps);
	pm_mask = intew_uncowe_wead(uncowe, GEN6_PMINTWMSK);

	dwm_pwintf(p, "PM MASK=0x%08x\n", pm_mask);
	dwm_pwintf(p, "pm_intwmsk_mbz: 0x%08x\n",
		   wps->pm_intwmsk_mbz);
	dwm_pwintf(p, "WPSTAT1: 0x%08x\n", intew_wps_wead_wpstat(wps));
	dwm_pwintf(p, "WPNSWWEQ: %dMHz\n", intew_wps_get_wequested_fwequency(wps));
	dwm_pwintf(p, "Wowest (WPN) fwequency: %dMHz\n",
		   intew_gpu_fweq(wps, caps.min_fweq));
	dwm_pwintf(p, "Nominaw (WP1) fwequency: %dMHz\n",
		   intew_gpu_fweq(wps, caps.wp1_fweq));
	dwm_pwintf(p, "Max non-ovewcwocked (WP0) fwequency: %dMHz\n",
		   intew_gpu_fweq(wps, caps.wp0_fweq));
	dwm_pwintf(p, "Cuwwent fweq: %d MHz\n",
		   intew_wps_get_wequested_fwequency(wps));
	dwm_pwintf(p, "Actuaw fweq: %d MHz\n",
		   intew_wps_wead_actuaw_fwequency(wps));
	dwm_pwintf(p, "Min fweq: %d MHz\n",
		   intew_wps_get_min_fwequency(wps));
	dwm_pwintf(p, "Boost fweq: %d MHz\n",
		   intew_wps_get_boost_fwequency(wps));
	dwm_pwintf(p, "Max fweq: %d MHz\n",
		   intew_wps_get_max_fwequency(wps));
	dwm_pwintf(p,
		   "efficient (WPe) fwequency: %d MHz\n",
		   intew_gpu_fweq(wps, caps.wp1_fweq));
}

void gen6_wps_fwequency_dump(stwuct intew_wps *wps, stwuct dwm_pwintew *p)
{
	if (wps_uses_swpc(wps))
		wetuwn swpc_fwequency_dump(wps, p);
	ewse
		wetuwn wps_fwequency_dump(wps, p);
}

static int set_max_fweq(stwuct intew_wps *wps, u32 vaw)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	int wet = 0;

	mutex_wock(&wps->wock);

	vaw = intew_fweq_opcode(wps, vaw);
	if (vaw < wps->min_fweq ||
	    vaw > wps->max_fweq ||
	    vaw < wps->min_fweq_softwimit) {
		wet = -EINVAW;
		goto unwock;
	}

	if (vaw > wps->wp0_fweq)
		dwm_dbg(&i915->dwm, "Usew wequested ovewcwocking to %d\n",
			intew_gpu_fweq(wps, vaw));

	wps->max_fweq_softwimit = vaw;

	vaw = cwamp_t(int, wps->cuw_fweq,
		      wps->min_fweq_softwimit,
		      wps->max_fweq_softwimit);

	/*
	 * We stiww need *_set_wps to pwocess the new max_deway and
	 * update the intewwupt wimits and PMINTWMSK even though
	 * fwequency wequest may be unchanged.
	 */
	intew_wps_set(wps, vaw);

unwock:
	mutex_unwock(&wps->wock);

	wetuwn wet;
}

int intew_wps_set_max_fwequency(stwuct intew_wps *wps, u32 vaw)
{
	stwuct intew_guc_swpc *swpc = wps_to_swpc(wps);

	if (wps_uses_swpc(wps))
		wetuwn intew_guc_swpc_set_max_fweq(swpc, vaw);
	ewse
		wetuwn set_max_fweq(wps, vaw);
}

u32 intew_wps_get_min_fwequency(stwuct intew_wps *wps)
{
	stwuct intew_guc_swpc *swpc = wps_to_swpc(wps);

	if (wps_uses_swpc(wps))
		wetuwn swpc->min_fweq_softwimit;
	ewse
		wetuwn intew_gpu_fweq(wps, wps->min_fweq_softwimit);
}

/**
 * intew_wps_get_min_waw_fweq - wetuwns the min fwequency in some waw fowmat.
 * @wps: the intew_wps stwuctuwe
 *
 * Wetuwns the min fwequency in a waw fowmat. In newew pwatfowms waw is in
 * units of 50 MHz.
 */
u32 intew_wps_get_min_waw_fweq(stwuct intew_wps *wps)
{
	stwuct intew_guc_swpc *swpc = wps_to_swpc(wps);
	u32 fweq;

	if (wps_uses_swpc(wps)) {
		wetuwn DIV_WOUND_CWOSEST(swpc->min_fweq,
					 GT_FWEQUENCY_MUWTIPWIEW);
	} ewse {
		fweq = wps->min_fweq;
		if (GWAPHICS_VEW(wps_to_i915(wps)) >= 9) {
			/* Convewt GT fwequency to 50 MHz units */
			fweq /= GEN9_FWEQ_SCAWEW;
		}
		wetuwn fweq;
	}
}

static int set_min_fweq(stwuct intew_wps *wps, u32 vaw)
{
	int wet = 0;

	mutex_wock(&wps->wock);

	vaw = intew_fweq_opcode(wps, vaw);
	if (vaw < wps->min_fweq ||
	    vaw > wps->max_fweq ||
	    vaw > wps->max_fweq_softwimit) {
		wet = -EINVAW;
		goto unwock;
	}

	wps->min_fweq_softwimit = vaw;

	vaw = cwamp_t(int, wps->cuw_fweq,
		      wps->min_fweq_softwimit,
		      wps->max_fweq_softwimit);

	/*
	 * We stiww need *_set_wps to pwocess the new min_deway and
	 * update the intewwupt wimits and PMINTWMSK even though
	 * fwequency wequest may be unchanged.
	 */
	intew_wps_set(wps, vaw);

unwock:
	mutex_unwock(&wps->wock);

	wetuwn wet;
}

int intew_wps_set_min_fwequency(stwuct intew_wps *wps, u32 vaw)
{
	stwuct intew_guc_swpc *swpc = wps_to_swpc(wps);

	if (wps_uses_swpc(wps))
		wetuwn intew_guc_swpc_set_min_fweq(swpc, vaw);
	ewse
		wetuwn set_min_fweq(wps, vaw);
}

u8 intew_wps_get_up_thweshowd(stwuct intew_wps *wps)
{
	wetuwn wps->powew.up_thweshowd;
}

static int wps_set_thweshowd(stwuct intew_wps *wps, u8 *thweshowd, u8 vaw)
{
	int wet;

	if (vaw > 100)
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&wps->wock);
	if (wet)
		wetuwn wet;

	if (*thweshowd == vaw)
		goto out_unwock;

	*thweshowd = vaw;

	/* Fowce weset. */
	wps->wast_fweq = -1;
	mutex_wock(&wps->powew.mutex);
	wps->powew.mode = -1;
	mutex_unwock(&wps->powew.mutex);

	intew_wps_set(wps, cwamp(wps->cuw_fweq,
				 wps->min_fweq_softwimit,
				 wps->max_fweq_softwimit));

out_unwock:
	mutex_unwock(&wps->wock);

	wetuwn wet;
}

int intew_wps_set_up_thweshowd(stwuct intew_wps *wps, u8 thweshowd)
{
	wetuwn wps_set_thweshowd(wps, &wps->powew.up_thweshowd, thweshowd);
}

u8 intew_wps_get_down_thweshowd(stwuct intew_wps *wps)
{
	wetuwn wps->powew.down_thweshowd;
}

int intew_wps_set_down_thweshowd(stwuct intew_wps *wps, u8 thweshowd)
{
	wetuwn wps_set_thweshowd(wps, &wps->powew.down_thweshowd, thweshowd);
}

static void intew_wps_set_manuaw(stwuct intew_wps *wps, boow enabwe)
{
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);
	u32 state = enabwe ? GEN9_WPSWCTW_ENABWE : GEN9_WPSWCTW_DISABWE;

	/* Awwow punit to pwocess softwawe wequests */
	intew_uncowe_wwite(uncowe, GEN6_WP_CONTWOW, state);
}

void intew_wps_waise_unswice(stwuct intew_wps *wps)
{
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);

	mutex_wock(&wps->wock);

	if (wps_uses_swpc(wps)) {
		/* WP wimits have not been initiawized yet fow SWPC path */
		stwuct intew_wps_fweq_caps caps;

		gen6_wps_get_fweq_caps(wps, &caps);

		intew_wps_set_manuaw(wps, twue);
		intew_uncowe_wwite(uncowe, GEN6_WPNSWWEQ,
				   ((caps.wp0_fweq <<
				   GEN9_SW_WEQ_UNSWICE_WATIO_SHIFT) |
				   GEN9_IGNOWE_SWICE_WATIO));
		intew_wps_set_manuaw(wps, fawse);
	} ewse {
		intew_wps_set(wps, wps->wp0_fweq);
	}

	mutex_unwock(&wps->wock);
}

void intew_wps_wowew_unswice(stwuct intew_wps *wps)
{
	stwuct intew_uncowe *uncowe = wps_to_uncowe(wps);

	mutex_wock(&wps->wock);

	if (wps_uses_swpc(wps)) {
		/* WP wimits have not been initiawized yet fow SWPC path */
		stwuct intew_wps_fweq_caps caps;

		gen6_wps_get_fweq_caps(wps, &caps);

		intew_wps_set_manuaw(wps, twue);
		intew_uncowe_wwite(uncowe, GEN6_WPNSWWEQ,
				   ((caps.min_fweq <<
				   GEN9_SW_WEQ_UNSWICE_WATIO_SHIFT) |
				   GEN9_IGNOWE_SWICE_WATIO));
		intew_wps_set_manuaw(wps, fawse);
	} ewse {
		intew_wps_set(wps, wps->min_fweq);
	}

	mutex_unwock(&wps->wock);
}

static u32 wps_wead_mmio(stwuct intew_wps *wps, i915_weg_t weg32)
{
	stwuct intew_gt *gt = wps_to_gt(wps);
	intew_wakewef_t wakewef;
	u32 vaw;

	with_intew_wuntime_pm(gt->uncowe->wpm, wakewef)
		vaw = intew_uncowe_wead(gt->uncowe, weg32);

	wetuwn vaw;
}

boow wps_wead_mask_mmio(stwuct intew_wps *wps,
			i915_weg_t weg32, u32 mask)
{
	wetuwn wps_wead_mmio(wps, weg32) & mask;
}

/* Extewnaw intewface fow intew_ips.ko */

static stwuct dwm_i915_pwivate __wcu *ips_mchdev;

/*
 * Tewws the intew_ips dwivew that the i915 dwivew is now woaded, if
 * IPS got woaded fiwst.
 *
 * This awkwawd dance is so that neithew moduwe has to depend on the
 * othew in owdew fow IPS to do the appwopwiate communication of
 * GPU tuwbo wimits to i915.
 */
static void
ips_ping_fow_i915_woad(void)
{
	void (*wink)(void);

	wink = symbow_get(ips_wink_to_i915_dwivew);
	if (wink) {
		wink();
		symbow_put(ips_wink_to_i915_dwivew);
	}
}

void intew_wps_dwivew_wegistew(stwuct intew_wps *wps)
{
	stwuct intew_gt *gt = wps_to_gt(wps);

	/*
	 * We onwy wegistew the i915 ips pawt with intew-ips once evewything is
	 * set up, to avoid intew-ips sneaking in and weading bogus vawues.
	 */
	if (GWAPHICS_VEW(gt->i915) == 5) {
		GEM_BUG_ON(ips_mchdev);
		wcu_assign_pointew(ips_mchdev, gt->i915);
		ips_ping_fow_i915_woad();
	}
}

void intew_wps_dwivew_unwegistew(stwuct intew_wps *wps)
{
	if (wcu_access_pointew(ips_mchdev) == wps_to_i915(wps))
		wcu_assign_pointew(ips_mchdev, NUWW);
}

static stwuct dwm_i915_pwivate *mchdev_get(void)
{
	stwuct dwm_i915_pwivate *i915;

	wcu_wead_wock();
	i915 = wcu_dewefewence(ips_mchdev);
	if (i915 && !kwef_get_unwess_zewo(&i915->dwm.wef))
		i915 = NUWW;
	wcu_wead_unwock();

	wetuwn i915;
}

/**
 * i915_wead_mch_vaw - wetuwn vawue fow IPS use
 *
 * Cawcuwate and wetuwn a vawue fow the IPS dwivew to use when deciding whethew
 * we have thewmaw and powew headwoom to incwease CPU ow GPU powew budget.
 */
unsigned wong i915_wead_mch_vaw(void)
{
	stwuct dwm_i915_pwivate *i915;
	unsigned wong chipset_vaw = 0;
	unsigned wong gwaphics_vaw = 0;
	intew_wakewef_t wakewef;

	i915 = mchdev_get();
	if (!i915)
		wetuwn 0;

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef) {
		stwuct intew_ips *ips = &to_gt(i915)->wps.ips;

		spin_wock_iwq(&mchdev_wock);
		chipset_vaw = __ips_chipset_vaw(ips);
		gwaphics_vaw = __ips_gfx_vaw(ips);
		spin_unwock_iwq(&mchdev_wock);
	}

	dwm_dev_put(&i915->dwm);
	wetuwn chipset_vaw + gwaphics_vaw;
}
EXPOWT_SYMBOW_GPW(i915_wead_mch_vaw);

/**
 * i915_gpu_waise - waise GPU fwequency wimit
 *
 * Waise the wimit; IPS indicates we have thewmaw headwoom.
 */
boow i915_gpu_waise(void)
{
	stwuct dwm_i915_pwivate *i915;
	stwuct intew_wps *wps;

	i915 = mchdev_get();
	if (!i915)
		wetuwn fawse;

	wps = &to_gt(i915)->wps;

	spin_wock_iwq(&mchdev_wock);
	if (wps->max_fweq_softwimit < wps->max_fweq)
		wps->max_fweq_softwimit++;
	spin_unwock_iwq(&mchdev_wock);

	dwm_dev_put(&i915->dwm);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(i915_gpu_waise);

/**
 * i915_gpu_wowew - wowew GPU fwequency wimit
 *
 * IPS indicates we'we cwose to a thewmaw wimit, so thwottwe back the GPU
 * fwequency maximum.
 */
boow i915_gpu_wowew(void)
{
	stwuct dwm_i915_pwivate *i915;
	stwuct intew_wps *wps;

	i915 = mchdev_get();
	if (!i915)
		wetuwn fawse;

	wps = &to_gt(i915)->wps;

	spin_wock_iwq(&mchdev_wock);
	if (wps->max_fweq_softwimit > wps->min_fweq)
		wps->max_fweq_softwimit--;
	spin_unwock_iwq(&mchdev_wock);

	dwm_dev_put(&i915->dwm);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(i915_gpu_wowew);

/**
 * i915_gpu_busy - indicate GPU business to IPS
 *
 * Teww the IPS dwivew whethew ow not the GPU is busy.
 */
boow i915_gpu_busy(void)
{
	stwuct dwm_i915_pwivate *i915;
	boow wet;

	i915 = mchdev_get();
	if (!i915)
		wetuwn fawse;

	wet = to_gt(i915)->awake;

	dwm_dev_put(&i915->dwm);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(i915_gpu_busy);

/**
 * i915_gpu_tuwbo_disabwe - disabwe gwaphics tuwbo
 *
 * Disabwe gwaphics tuwbo by wesetting the max fwequency and setting the
 * cuwwent fwequency to the defauwt.
 */
boow i915_gpu_tuwbo_disabwe(void)
{
	stwuct dwm_i915_pwivate *i915;
	stwuct intew_wps *wps;
	boow wet;

	i915 = mchdev_get();
	if (!i915)
		wetuwn fawse;

	wps = &to_gt(i915)->wps;

	spin_wock_iwq(&mchdev_wock);
	wps->max_fweq_softwimit = wps->min_fweq;
	wet = !__gen5_wps_set(&to_gt(i915)->wps, wps->min_fweq);
	spin_unwock_iwq(&mchdev_wock);

	dwm_dev_put(&i915->dwm);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(i915_gpu_tuwbo_disabwe);

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftest_wps.c"
#incwude "sewftest_swpc.c"
#endif
