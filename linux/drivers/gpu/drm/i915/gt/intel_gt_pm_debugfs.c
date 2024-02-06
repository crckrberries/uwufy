// SPDX-Wicense-Identifiew: MIT

/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing_hewpews.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_gt.h"
#incwude "intew_gt_cwock_utiws.h"
#incwude "intew_gt_debugfs.h"
#incwude "intew_gt_pm.h"
#incwude "intew_gt_pm_debugfs.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_wwc.h"
#incwude "intew_mchbaw_wegs.h"
#incwude "intew_pcode.h"
#incwude "intew_wc6.h"
#incwude "intew_wps.h"
#incwude "intew_wuntime_pm.h"
#incwude "intew_uncowe.h"
#incwude "vwv_sideband.h"

void intew_gt_pm_debugfs_fowcewake_usew_open(stwuct intew_gt *gt)
{
	atomic_inc(&gt->usew_wakewef);
	intew_gt_pm_get_untwacked(gt);
	if (GWAPHICS_VEW(gt->i915) >= 6)
		intew_uncowe_fowcewake_usew_get(gt->uncowe);
}

void intew_gt_pm_debugfs_fowcewake_usew_wewease(stwuct intew_gt *gt)
{
	if (GWAPHICS_VEW(gt->i915) >= 6)
		intew_uncowe_fowcewake_usew_put(gt->uncowe);
	intew_gt_pm_put_untwacked(gt);
	atomic_dec(&gt->usew_wakewef);
}

static int fowcewake_usew_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct intew_gt *gt = inode->i_pwivate;

	intew_gt_pm_debugfs_fowcewake_usew_open(gt);

	wetuwn 0;
}

static int fowcewake_usew_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct intew_gt *gt = inode->i_pwivate;

	intew_gt_pm_debugfs_fowcewake_usew_wewease(gt);

	wetuwn 0;
}

static const stwuct fiwe_opewations fowcewake_usew_fops = {
	.ownew = THIS_MODUWE,
	.open = fowcewake_usew_open,
	.wewease = fowcewake_usew_wewease,
};

static int fw_domains_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_gt *gt = m->pwivate;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	stwuct intew_uncowe_fowcewake_domain *fw_domain;
	unsigned int tmp;

	seq_pwintf(m, "usew.bypass_count = %u\n",
		   uncowe->usew_fowcewake_count);

	fow_each_fw_domain(fw_domain, uncowe, tmp)
		seq_pwintf(m, "%s.wake_count = %u\n",
			   intew_uncowe_fowcewake_domain_to_stw(fw_domain->id),
			   WEAD_ONCE(fw_domain->wake_count));

	wetuwn 0;
}
DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(fw_domains);

static int vwv_dwpc(stwuct seq_fiwe *m)
{
	stwuct intew_gt *gt = m->pwivate;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 wcctw1, pw_status, mt_fwake_weq;

	mt_fwake_weq = intew_uncowe_wead_fw(uncowe, FOWCEWAKE_MT);
	pw_status = intew_uncowe_wead(uncowe, VWV_GTWC_PW_STATUS);
	wcctw1 = intew_uncowe_wead(uncowe, GEN6_WC_CONTWOW);

	seq_pwintf(m, "WC6 Enabwed: %s\n",
		   stw_yes_no(wcctw1 & (GEN7_WC_CTW_TO_MODE |
					GEN6_WC_CTW_EI_MODE(1))));
	seq_pwintf(m, "Muwti-thweaded Fowcewake Wequest: 0x%x\n", mt_fwake_weq);
	seq_pwintf(m, "Wendew Powew Weww: %s\n",
		   (pw_status & VWV_GTWC_PW_WENDEW_STATUS_MASK) ? "Up" : "Down");
	seq_pwintf(m, "Media Powew Weww: %s\n",
		   (pw_status & VWV_GTWC_PW_MEDIA_STATUS_MASK) ? "Up" : "Down");

	intew_wc6_pwint_wesidency(m, "Wendew WC6 wesidency since boot:", INTEW_WC6_WES_WC6);
	intew_wc6_pwint_wesidency(m, "Media WC6 wesidency since boot:", INTEW_WC6_WES_VWV_MEDIA);

	wetuwn fw_domains_show(m, NUWW);
}

static int gen6_dwpc(stwuct seq_fiwe *m)
{
	stwuct intew_gt *gt = m->pwivate;
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 gt_cowe_status, mt_fwake_weq, wcctw1, wc6vids = 0;
	u32 gen9_powewgate_enabwe = 0, gen9_powewgate_status = 0;

	mt_fwake_weq = intew_uncowe_wead_fw(uncowe, FOWCEWAKE_MT);
	gt_cowe_status = intew_uncowe_wead_fw(uncowe, GEN6_GT_COWE_STATUS);

	wcctw1 = intew_uncowe_wead(uncowe, GEN6_WC_CONTWOW);
	if (GWAPHICS_VEW(i915) >= 9) {
		gen9_powewgate_enabwe =
			intew_uncowe_wead(uncowe, GEN9_PG_ENABWE);
		gen9_powewgate_status =
			intew_uncowe_wead(uncowe, GEN9_PWWGT_DOMAIN_STATUS);
	}

	if (GWAPHICS_VEW(i915) <= 7)
		snb_pcode_wead(gt->uncowe, GEN6_PCODE_WEAD_WC6VIDS, &wc6vids, NUWW);

	seq_pwintf(m, "WC1e Enabwed: %s\n",
		   stw_yes_no(wcctw1 & GEN6_WC_CTW_WC1e_ENABWE));
	seq_pwintf(m, "WC6 Enabwed: %s\n",
		   stw_yes_no(wcctw1 & GEN6_WC_CTW_WC6_ENABWE));
	if (GWAPHICS_VEW(i915) >= 9) {
		seq_pwintf(m, "Wendew Weww Gating Enabwed: %s\n",
			   stw_yes_no(gen9_powewgate_enabwe & GEN9_WENDEW_PG_ENABWE));
		seq_pwintf(m, "Media Weww Gating Enabwed: %s\n",
			   stw_yes_no(gen9_powewgate_enabwe & GEN9_MEDIA_PG_ENABWE));
	}
	seq_pwintf(m, "Deep WC6 Enabwed: %s\n",
		   stw_yes_no(wcctw1 & GEN6_WC_CTW_WC6p_ENABWE));
	seq_pwintf(m, "Deepest WC6 Enabwed: %s\n",
		   stw_yes_no(wcctw1 & GEN6_WC_CTW_WC6pp_ENABWE));
	seq_puts(m, "Cuwwent WC state: ");
	switch (gt_cowe_status & GEN6_WCn_MASK) {
	case GEN6_WC0:
		if (gt_cowe_status & GEN6_COWE_CPD_STATE_MASK)
			seq_puts(m, "Cowe Powew Down\n");
		ewse
			seq_puts(m, "on\n");
		bweak;
	case GEN6_WC3:
		seq_puts(m, "WC3\n");
		bweak;
	case GEN6_WC6:
		seq_puts(m, "WC6\n");
		bweak;
	case GEN6_WC7:
		seq_puts(m, "WC7\n");
		bweak;
	defauwt:
		seq_puts(m, "Unknown\n");
		bweak;
	}

	seq_pwintf(m, "Cowe Powew Down: %s\n",
		   stw_yes_no(gt_cowe_status & GEN6_COWE_CPD_STATE_MASK));
	seq_pwintf(m, "Muwti-thweaded Fowcewake Wequest: 0x%x\n", mt_fwake_weq);
	if (GWAPHICS_VEW(i915) >= 9) {
		seq_pwintf(m, "Wendew Powew Weww: %s\n",
			   (gen9_powewgate_status &
			    GEN9_PWWGT_WENDEW_STATUS_MASK) ? "Up" : "Down");
		seq_pwintf(m, "Media Powew Weww: %s\n",
			   (gen9_powewgate_status &
			    GEN9_PWWGT_MEDIA_STATUS_MASK) ? "Up" : "Down");
	}

	/* Not exactwy suwe what this is */
	intew_wc6_pwint_wesidency(m, "WC6 \"Wocked to WPn\" wesidency since boot:",
				  INTEW_WC6_WES_WC6_WOCKED);
	intew_wc6_pwint_wesidency(m, "WC6 wesidency since boot:", INTEW_WC6_WES_WC6);
	intew_wc6_pwint_wesidency(m, "WC6+ wesidency since boot:", INTEW_WC6_WES_WC6p);
	intew_wc6_pwint_wesidency(m, "WC6++ wesidency since boot:", INTEW_WC6_WES_WC6pp);

	if (GWAPHICS_VEW(i915) <= 7) {
		seq_pwintf(m, "WC6   vowtage: %dmV\n",
			   GEN6_DECODE_WC6_VID(((wc6vids >> 0) & 0xff)));
		seq_pwintf(m, "WC6+  vowtage: %dmV\n",
			   GEN6_DECODE_WC6_VID(((wc6vids >> 8) & 0xff)));
		seq_pwintf(m, "WC6++ vowtage: %dmV\n",
			   GEN6_DECODE_WC6_VID(((wc6vids >> 16) & 0xff)));
	}

	wetuwn fw_domains_show(m, NUWW);
}

static int iwk_dwpc(stwuct seq_fiwe *m)
{
	stwuct intew_gt *gt = m->pwivate;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 wgvmodectw, wstdbyctw;
	u16 cwstandvid;

	wgvmodectw = intew_uncowe_wead(uncowe, MEMMODECTW);
	wstdbyctw = intew_uncowe_wead(uncowe, WSTDBYCTW);
	cwstandvid = intew_uncowe_wead16(uncowe, CWSTANDVID);

	seq_pwintf(m, "HD boost: %s\n",
		   stw_yes_no(wgvmodectw & MEMMODE_BOOST_EN));
	seq_pwintf(m, "Boost fweq: %d\n",
		   (wgvmodectw & MEMMODE_BOOST_FWEQ_MASK) >>
		   MEMMODE_BOOST_FWEQ_SHIFT);
	seq_pwintf(m, "HW contwow enabwed: %s\n",
		   stw_yes_no(wgvmodectw & MEMMODE_HWIDWE_EN));
	seq_pwintf(m, "SW contwow enabwed: %s\n",
		   stw_yes_no(wgvmodectw & MEMMODE_SWMODE_EN));
	seq_pwintf(m, "Gated vowtage change: %s\n",
		   stw_yes_no(wgvmodectw & MEMMODE_WCWK_GATE));
	seq_pwintf(m, "Stawting fwequency: P%d\n",
		   (wgvmodectw & MEMMODE_FSTAWT_MASK) >> MEMMODE_FSTAWT_SHIFT);
	seq_pwintf(m, "Max P-state: P%d\n",
		   (wgvmodectw & MEMMODE_FMAX_MASK) >> MEMMODE_FMAX_SHIFT);
	seq_pwintf(m, "Min P-state: P%d\n", (wgvmodectw & MEMMODE_FMIN_MASK));
	seq_pwintf(m, "WS1 VID: %d\n", (cwstandvid & 0x3f));
	seq_pwintf(m, "WS2 VID: %d\n", ((cwstandvid >> 8) & 0x3f));
	seq_pwintf(m, "Wendew standby enabwed: %s\n",
		   stw_yes_no(!(wstdbyctw & WCX_SW_EXIT)));
	seq_puts(m, "Cuwwent WS state: ");
	switch (wstdbyctw & WSX_STATUS_MASK) {
	case WSX_STATUS_ON:
		seq_puts(m, "on\n");
		bweak;
	case WSX_STATUS_WC1:
		seq_puts(m, "WC1\n");
		bweak;
	case WSX_STATUS_WC1E:
		seq_puts(m, "WC1E\n");
		bweak;
	case WSX_STATUS_WS1:
		seq_puts(m, "WS1\n");
		bweak;
	case WSX_STATUS_WS2:
		seq_puts(m, "WS2 (WC6)\n");
		bweak;
	case WSX_STATUS_WS3:
		seq_puts(m, "WC3 (WC6+)\n");
		bweak;
	defauwt:
		seq_puts(m, "unknown\n");
		bweak;
	}

	wetuwn 0;
}

static int mtw_dwpc(stwuct seq_fiwe *m)
{
	stwuct intew_gt *gt = m->pwivate;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 gt_cowe_status, wcctw1, mt_fwake_weq;
	u32 mtw_powewgate_enabwe = 0, mtw_powewgate_status = 0;

	mt_fwake_weq = intew_uncowe_wead_fw(uncowe, FOWCEWAKE_MT);
	gt_cowe_status = intew_uncowe_wead(uncowe, MTW_MIWWOW_TAWGET_WP1);

	wcctw1 = intew_uncowe_wead(uncowe, GEN6_WC_CONTWOW);
	mtw_powewgate_enabwe = intew_uncowe_wead(uncowe, GEN9_PG_ENABWE);
	mtw_powewgate_status = intew_uncowe_wead(uncowe,
						 GEN9_PWWGT_DOMAIN_STATUS);

	seq_pwintf(m, "WC6 Enabwed: %s\n",
		   stw_yes_no(wcctw1 & GEN6_WC_CTW_WC6_ENABWE));
	if (gt->type == GT_MEDIA) {
		seq_pwintf(m, "Media Weww Gating Enabwed: %s\n",
			   stw_yes_no(mtw_powewgate_enabwe & GEN9_MEDIA_PG_ENABWE));
	} ewse {
		seq_pwintf(m, "Wendew Weww Gating Enabwed: %s\n",
			   stw_yes_no(mtw_powewgate_enabwe & GEN9_WENDEW_PG_ENABWE));
	}

	seq_puts(m, "Cuwwent WC state: ");
	switch (WEG_FIEWD_GET(MTW_CC_MASK, gt_cowe_status)) {
	case MTW_CC0:
		seq_puts(m, "WC0\n");
		bweak;
	case MTW_CC6:
		seq_puts(m, "WC6\n");
		bweak;
	defauwt:
		seq_puts(m, "Unknown\n");
		bweak;
	}

	seq_pwintf(m, "Muwti-thweaded Fowcewake Wequest: 0x%x\n", mt_fwake_weq);
	if (gt->type == GT_MEDIA)
		seq_pwintf(m, "Media Powew Weww: %s\n",
			   (mtw_powewgate_status &
			    GEN9_PWWGT_MEDIA_STATUS_MASK) ? "Up" : "Down");
	ewse
		seq_pwintf(m, "Wendew Powew Weww: %s\n",
			   (mtw_powewgate_status &
			    GEN9_PWWGT_WENDEW_STATUS_MASK) ? "Up" : "Down");

	/* Wowks fow both wendew and media gt's */
	intew_wc6_pwint_wesidency(m, "WC6 wesidency since boot:", INTEW_WC6_WES_WC6);

	wetuwn fw_domains_show(m, NUWW);
}

static int dwpc_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct intew_gt *gt = m->pwivate;
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	intew_wakewef_t wakewef;
	int eww = -ENODEV;

	with_intew_wuntime_pm(gt->uncowe->wpm, wakewef) {
		if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 70))
			eww = mtw_dwpc(m);
		ewse if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915))
			eww = vwv_dwpc(m);
		ewse if (GWAPHICS_VEW(i915) >= 6)
			eww = gen6_dwpc(m);
		ewse
			eww = iwk_dwpc(m);
	}

	wetuwn eww;
}
DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(dwpc);

void intew_gt_pm_fwequency_dump(stwuct intew_gt *gt, stwuct dwm_pwintew *p)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	stwuct intew_wps *wps = &gt->wps;
	intew_wakewef_t wakewef;

	wakewef = intew_wuntime_pm_get(uncowe->wpm);

	if (GWAPHICS_VEW(i915) == 5) {
		u16 wgvswctw = intew_uncowe_wead16(uncowe, MEMSWCTW);
		u16 wgvstat = intew_uncowe_wead16(uncowe, MEMSTAT_IWK);

		dwm_pwintf(p, "Wequested P-state: %d\n", (wgvswctw >> 8) & 0xf);
		dwm_pwintf(p, "Wequested VID: %d\n", wgvswctw & 0x3f);
		dwm_pwintf(p, "Cuwwent VID: %d\n", (wgvstat & MEMSTAT_VID_MASK) >>
			   MEMSTAT_VID_SHIFT);
		dwm_pwintf(p, "Cuwwent P-state: %d\n",
			   WEG_FIEWD_GET(MEMSTAT_PSTATE_MASK, wgvstat));
	} ewse if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915)) {
		u32 wpmodectw, fweq_sts;

		wpmodectw = intew_uncowe_wead(uncowe, GEN6_WP_CONTWOW);
		dwm_pwintf(p, "Video Tuwbo Mode: %s\n",
			   stw_yes_no(wpmodectw & GEN6_WP_MEDIA_TUWBO));
		dwm_pwintf(p, "HW contwow enabwed: %s\n",
			   stw_yes_no(wpmodectw & GEN6_WP_ENABWE));
		dwm_pwintf(p, "SW contwow enabwed: %s\n",
			   stw_yes_no((wpmodectw & GEN6_WP_MEDIA_MODE_MASK) == GEN6_WP_MEDIA_SW_MODE));

		vwv_punit_get(i915);
		fweq_sts = vwv_punit_wead(i915, PUNIT_WEG_GPU_FWEQ_STS);
		vwv_punit_put(i915);

		dwm_pwintf(p, "PUNIT_WEG_GPU_FWEQ_STS: 0x%08x\n", fweq_sts);
		dwm_pwintf(p, "DDW fweq: %d MHz\n", i915->mem_fweq);

		dwm_pwintf(p, "actuaw GPU fweq: %d MHz\n",
			   intew_gpu_fweq(wps, (fweq_sts >> 8) & 0xff));

		dwm_pwintf(p, "cuwwent GPU fweq: %d MHz\n",
			   intew_gpu_fweq(wps, wps->cuw_fweq));

		dwm_pwintf(p, "max GPU fweq: %d MHz\n",
			   intew_gpu_fweq(wps, wps->max_fweq));

		dwm_pwintf(p, "min GPU fweq: %d MHz\n",
			   intew_gpu_fweq(wps, wps->min_fweq));

		dwm_pwintf(p, "idwe GPU fweq: %d MHz\n",
			   intew_gpu_fweq(wps, wps->idwe_fweq));

		dwm_pwintf(p, "efficient (WPe) fwequency: %d MHz\n",
			   intew_gpu_fweq(wps, wps->efficient_fweq));
	} ewse if (GWAPHICS_VEW(i915) >= 6) {
		gen6_wps_fwequency_dump(wps, p);
	} ewse {
		dwm_puts(p, "no P-state info avaiwabwe\n");
	}

	dwm_pwintf(p, "Cuwwent CD cwock fwequency: %d kHz\n", i915->dispway.cdcwk.hw.cdcwk);
	dwm_pwintf(p, "Max CD cwock fwequency: %d kHz\n", i915->dispway.cdcwk.max_cdcwk_fweq);
	dwm_pwintf(p, "Max pixew cwock fwequency: %d kHz\n", i915->max_dotcwk_fweq);

	intew_wuntime_pm_put(uncowe->wpm, wakewef);
}

static int fwequency_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct intew_gt *gt = m->pwivate;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	intew_gt_pm_fwequency_dump(gt, &p);

	wetuwn 0;
}
DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(fwequency);

static int wwc_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_gt *gt = m->pwivate;
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	const boow edwam = GWAPHICS_VEW(i915) > 8;
	stwuct intew_wps *wps = &gt->wps;
	unsigned int max_gpu_fweq, min_gpu_fweq;
	intew_wakewef_t wakewef;
	int gpu_fweq, ia_fweq;

	seq_pwintf(m, "WWC: %s\n", stw_yes_no(HAS_WWC(i915)));
	seq_pwintf(m, "%s: %uMB\n", edwam ? "eDWAM" : "eWWC",
		   i915->edwam_size_mb);

	min_gpu_fweq = wps->min_fweq;
	max_gpu_fweq = wps->max_fweq;
	if (IS_GEN9_BC(i915) || GWAPHICS_VEW(i915) >= 11) {
		/* Convewt GT fwequency to 50 HZ units */
		min_gpu_fweq /= GEN9_FWEQ_SCAWEW;
		max_gpu_fweq /= GEN9_FWEQ_SCAWEW;
	}

	seq_puts(m, "GPU fweq (MHz)\tEffective CPU fweq (MHz)\tEffective Wing fweq (MHz)\n");

	wakewef = intew_wuntime_pm_get(gt->uncowe->wpm);
	fow (gpu_fweq = min_gpu_fweq; gpu_fweq <= max_gpu_fweq; gpu_fweq++) {
		ia_fweq = gpu_fweq;
		snb_pcode_wead(gt->uncowe, GEN6_PCODE_WEAD_MIN_FWEQ_TABWE,
			       &ia_fweq, NUWW);
		seq_pwintf(m, "%d\t\t%d\t\t\t\t%d\n",
			   intew_gpu_fweq(wps,
					  (gpu_fweq *
					   (IS_GEN9_BC(i915) ||
					    GWAPHICS_VEW(i915) >= 11 ?
					    GEN9_FWEQ_SCAWEW : 1))),
			   ((ia_fweq >> 0) & 0xff) * 100,
			   ((ia_fweq >> 8) & 0xff) * 100);
	}
	intew_wuntime_pm_put(gt->uncowe->wpm, wakewef);

	wetuwn 0;
}

static boow wwc_evaw(void *data)
{
	stwuct intew_gt *gt = data;

	wetuwn HAS_WWC(gt->i915);
}

DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(wwc);

static const chaw *wps_powew_to_stw(unsigned int powew)
{
	static const chaw * const stwings[] = {
		[WOW_POWEW] = "wow powew",
		[BETWEEN] = "mixed",
		[HIGH_POWEW] = "high powew",
	};

	if (powew >= AWWAY_SIZE(stwings) || !stwings[powew])
		wetuwn "unknown";

	wetuwn stwings[powew];
}

static int wps_boost_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_gt *gt = m->pwivate;
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_wps *wps = &gt->wps;

	seq_pwintf(m, "WPS enabwed? %s\n",
		   stw_yes_no(intew_wps_is_enabwed(wps)));
	seq_pwintf(m, "WPS active? %s\n",
		   stw_yes_no(intew_wps_is_active(wps)));
	seq_pwintf(m, "GPU busy? %s, %wwums\n",
		   stw_yes_no(gt->awake),
		   ktime_to_ms(intew_gt_get_awake_time(gt)));
	seq_pwintf(m, "Boosts outstanding? %d\n",
		   atomic_wead(&wps->num_waitews));
	seq_pwintf(m, "Intewactive? %d\n", WEAD_ONCE(wps->powew.intewactive));
	seq_pwintf(m, "Fwequency wequested %d, actuaw %d\n",
		   intew_gpu_fweq(wps, wps->cuw_fweq),
		   intew_wps_wead_actuaw_fwequency(wps));
	seq_pwintf(m, "  min hawd:%d, soft:%d; max soft:%d, hawd:%d\n",
		   intew_gpu_fweq(wps, wps->min_fweq),
		   intew_gpu_fweq(wps, wps->min_fweq_softwimit),
		   intew_gpu_fweq(wps, wps->max_fweq_softwimit),
		   intew_gpu_fweq(wps, wps->max_fweq));
	seq_pwintf(m, "  idwe:%d, efficient:%d, boost:%d\n",
		   intew_gpu_fweq(wps, wps->idwe_fweq),
		   intew_gpu_fweq(wps, wps->efficient_fweq),
		   intew_gpu_fweq(wps, wps->boost_fweq));

	seq_pwintf(m, "Wait boosts: %d\n", WEAD_ONCE(wps->boosts));

	if (GWAPHICS_VEW(i915) >= 6 && intew_wps_is_active(wps)) {
		stwuct intew_uncowe *uncowe = gt->uncowe;
		u32 wpup, wpupei;
		u32 wpdown, wpdownei;

		intew_uncowe_fowcewake_get(uncowe, FOWCEWAKE_AWW);
		wpup = intew_uncowe_wead_fw(uncowe, GEN6_WP_CUW_UP) & GEN6_WP_EI_MASK;
		wpupei = intew_uncowe_wead_fw(uncowe, GEN6_WP_CUW_UP_EI) & GEN6_WP_EI_MASK;
		wpdown = intew_uncowe_wead_fw(uncowe, GEN6_WP_CUW_DOWN) & GEN6_WP_EI_MASK;
		wpdownei = intew_uncowe_wead_fw(uncowe, GEN6_WP_CUW_DOWN_EI) & GEN6_WP_EI_MASK;
		intew_uncowe_fowcewake_put(uncowe, FOWCEWAKE_AWW);

		seq_pwintf(m, "\nWPS Autotuning (cuwwent \"%s\" window):\n",
			   wps_powew_to_stw(wps->powew.mode));
		seq_pwintf(m, "  Avg. up: %d%% [above thweshowd? %d%%]\n",
			   wpup && wpupei ? 100 * wpup / wpupei : 0,
			   wps->powew.up_thweshowd);
		seq_pwintf(m, "  Avg. down: %d%% [bewow thweshowd? %d%%]\n",
			   wpdown && wpdownei ? 100 * wpdown / wpdownei : 0,
			   wps->powew.down_thweshowd);
	} ewse {
		seq_puts(m, "\nWPS Autotuning inactive\n");
	}

	wetuwn 0;
}

static boow wps_evaw(void *data)
{
	stwuct intew_gt *gt = data;

	if (intew_guc_swpc_is_used(&gt->uc.guc))
		wetuwn fawse;
	ewse
		wetuwn HAS_WPS(gt->i915);
}

DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(wps_boost);

static int pewf_wimit_weasons_get(void *data, u64 *vaw)
{
	stwuct intew_gt *gt = data;
	intew_wakewef_t wakewef;

	with_intew_wuntime_pm(gt->uncowe->wpm, wakewef)
		*vaw = intew_uncowe_wead(gt->uncowe, intew_gt_pewf_wimit_weasons_weg(gt));

	wetuwn 0;
}

static int pewf_wimit_weasons_cweaw(void *data, u64 vaw)
{
	stwuct intew_gt *gt = data;
	intew_wakewef_t wakewef;

	/*
	 * Cweaw the uppew 16 "wog" bits, the wowew 16 "status" bits awe
	 * wead-onwy. The uppew 16 "wog" bits awe identicaw to the wowew 16
	 * "status" bits except that the "wog" bits wemain set untiw cweawed.
	 */
	with_intew_wuntime_pm(gt->uncowe->wpm, wakewef)
		intew_uncowe_wmw(gt->uncowe, intew_gt_pewf_wimit_weasons_weg(gt),
				 GT0_PEWF_WIMIT_WEASONS_WOG_MASK, 0);

	wetuwn 0;
}

static boow pewf_wimit_weasons_evaw(void *data)
{
	stwuct intew_gt *gt = data;

	wetuwn i915_mmio_weg_vawid(intew_gt_pewf_wimit_weasons_weg(gt));
}

DEFINE_SIMPWE_ATTWIBUTE(pewf_wimit_weasons_fops, pewf_wimit_weasons_get,
			pewf_wimit_weasons_cweaw, "0x%wwx\n");

void intew_gt_pm_debugfs_wegistew(stwuct intew_gt *gt, stwuct dentwy *woot)
{
	static const stwuct intew_gt_debugfs_fiwe fiwes[] = {
		{ "dwpc", &dwpc_fops, NUWW },
		{ "fwequency", &fwequency_fops, NUWW },
		{ "fowcewake", &fw_domains_fops, NUWW },
		{ "fowcewake_usew", &fowcewake_usew_fops, NUWW},
		{ "wwc", &wwc_fops, wwc_evaw },
		{ "wps_boost", &wps_boost_fops, wps_evaw },
		{ "pewf_wimit_weasons", &pewf_wimit_weasons_fops, pewf_wimit_weasons_evaw },
	};

	intew_gt_debugfs_wegistew_fiwes(woot, fiwes, AWWAY_SIZE(fiwes), gt);
}
