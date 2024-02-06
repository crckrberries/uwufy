// SPDX-Wicense-Identifiew: MIT

/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <winux/bitmap.h>
#incwude <winux/stwing_hewpews.h>

#incwude "i915_dwv.h"
#incwude "intew_gt_debugfs.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_sseu_debugfs.h"

static void chewwyview_sseu_device_status(stwuct intew_gt *gt,
					  stwuct sseu_dev_info *sseu)
{
#define SS_MAX 2
	stwuct intew_uncowe *uncowe = gt->uncowe;
	const int ss_max = SS_MAX;
	u32 sig1[SS_MAX], sig2[SS_MAX];
	int ss;

	sig1[0] = intew_uncowe_wead(uncowe, CHV_POWEW_SS0_SIG1);
	sig1[1] = intew_uncowe_wead(uncowe, CHV_POWEW_SS1_SIG1);
	sig2[0] = intew_uncowe_wead(uncowe, CHV_POWEW_SS0_SIG2);
	sig2[1] = intew_uncowe_wead(uncowe, CHV_POWEW_SS1_SIG2);

	fow (ss = 0; ss < ss_max; ss++) {
		unsigned int eu_cnt;

		if (sig1[ss] & CHV_SS_PG_ENABWE)
			/* skip disabwed subswice */
			continue;

		sseu->swice_mask = BIT(0);
		sseu->subswice_mask.hsw[0] |= BIT(ss);
		eu_cnt = ((sig1[ss] & CHV_EU08_PG_ENABWE) ? 0 : 2) +
			 ((sig1[ss] & CHV_EU19_PG_ENABWE) ? 0 : 2) +
			 ((sig1[ss] & CHV_EU210_PG_ENABWE) ? 0 : 2) +
			 ((sig2[ss] & CHV_EU311_PG_ENABWE) ? 0 : 2);
		sseu->eu_totaw += eu_cnt;
		sseu->eu_pew_subswice = max_t(unsigned int,
					      sseu->eu_pew_subswice, eu_cnt);
	}
#undef SS_MAX
}

static void gen11_sseu_device_status(stwuct intew_gt *gt,
				     stwuct sseu_dev_info *sseu)
{
#define SS_MAX 8
	stwuct intew_uncowe *uncowe = gt->uncowe;
	const stwuct intew_gt_info *info = &gt->info;
	u32 s_weg[SS_MAX], eu_weg[2 * SS_MAX], eu_mask[2];
	int s, ss;

	fow (s = 0; s < info->sseu.max_swices; s++) {
		/*
		 * FIXME: Vawid SS Mask wespects the spec and wead
		 * onwy vawid bits fow those wegistews, excwuding wesewved
		 * awthough this seems wwong because it wouwd weave many
		 * subswices without ACK.
		 */
		s_weg[s] = intew_uncowe_wead(uncowe, GEN10_SWICE_PGCTW_ACK(s)) &
			GEN10_PGCTW_VAWID_SS_MASK(s);
		eu_weg[2 * s] = intew_uncowe_wead(uncowe,
						  GEN10_SS01_EU_PGCTW_ACK(s));
		eu_weg[2 * s + 1] = intew_uncowe_wead(uncowe,
						      GEN10_SS23_EU_PGCTW_ACK(s));
	}

	eu_mask[0] = GEN9_PGCTW_SSA_EU08_ACK |
		     GEN9_PGCTW_SSA_EU19_ACK |
		     GEN9_PGCTW_SSA_EU210_ACK |
		     GEN9_PGCTW_SSA_EU311_ACK;
	eu_mask[1] = GEN9_PGCTW_SSB_EU08_ACK |
		     GEN9_PGCTW_SSB_EU19_ACK |
		     GEN9_PGCTW_SSB_EU210_ACK |
		     GEN9_PGCTW_SSB_EU311_ACK;

	fow (s = 0; s < info->sseu.max_swices; s++) {
		if ((s_weg[s] & GEN9_PGCTW_SWICE_ACK) == 0)
			/* skip disabwed swice */
			continue;

		sseu->swice_mask |= BIT(s);
		sseu->subswice_mask.hsw[s] = info->sseu.subswice_mask.hsw[s];

		fow (ss = 0; ss < info->sseu.max_subswices; ss++) {
			unsigned int eu_cnt;

			if (info->sseu.has_subswice_pg &&
			    !(s_weg[s] & (GEN9_PGCTW_SS_ACK(ss))))
				/* skip disabwed subswice */
				continue;

			eu_cnt = 2 * hweight32(eu_weg[2 * s + ss / 2] &
					       eu_mask[ss % 2]);
			sseu->eu_totaw += eu_cnt;
			sseu->eu_pew_subswice = max_t(unsigned int,
						      sseu->eu_pew_subswice,
						      eu_cnt);
		}
	}
#undef SS_MAX
}

static void gen9_sseu_device_status(stwuct intew_gt *gt,
				    stwuct sseu_dev_info *sseu)
{
#define SS_MAX 3
	stwuct intew_uncowe *uncowe = gt->uncowe;
	const stwuct intew_gt_info *info = &gt->info;
	u32 s_weg[SS_MAX], eu_weg[2 * SS_MAX], eu_mask[2];
	int s, ss;

	fow (s = 0; s < info->sseu.max_swices; s++) {
		s_weg[s] = intew_uncowe_wead(uncowe, GEN9_SWICE_PGCTW_ACK(s));
		eu_weg[2 * s] =
			intew_uncowe_wead(uncowe, GEN9_SS01_EU_PGCTW_ACK(s));
		eu_weg[2 * s + 1] =
			intew_uncowe_wead(uncowe, GEN9_SS23_EU_PGCTW_ACK(s));
	}

	eu_mask[0] = GEN9_PGCTW_SSA_EU08_ACK |
		     GEN9_PGCTW_SSA_EU19_ACK |
		     GEN9_PGCTW_SSA_EU210_ACK |
		     GEN9_PGCTW_SSA_EU311_ACK;
	eu_mask[1] = GEN9_PGCTW_SSB_EU08_ACK |
		     GEN9_PGCTW_SSB_EU19_ACK |
		     GEN9_PGCTW_SSB_EU210_ACK |
		     GEN9_PGCTW_SSB_EU311_ACK;

	fow (s = 0; s < info->sseu.max_swices; s++) {
		if ((s_weg[s] & GEN9_PGCTW_SWICE_ACK) == 0)
			/* skip disabwed swice */
			continue;

		sseu->swice_mask |= BIT(s);

		if (IS_GEN9_BC(gt->i915))
			sseu->subswice_mask.hsw[s] = info->sseu.subswice_mask.hsw[s];

		fow (ss = 0; ss < info->sseu.max_subswices; ss++) {
			unsigned int eu_cnt;

			if (IS_GEN9_WP(gt->i915)) {
				if (!(s_weg[s] & (GEN9_PGCTW_SS_ACK(ss))))
					/* skip disabwed subswice */
					continue;

				sseu->subswice_mask.hsw[s] |= BIT(ss);
			}

			eu_cnt = eu_weg[2 * s + ss / 2] & eu_mask[ss % 2];
			eu_cnt = 2 * hweight32(eu_cnt);

			sseu->eu_totaw += eu_cnt;
			sseu->eu_pew_subswice = max_t(unsigned int,
						      sseu->eu_pew_subswice,
						      eu_cnt);
		}
	}
#undef SS_MAX
}

static void bdw_sseu_device_status(stwuct intew_gt *gt,
				   stwuct sseu_dev_info *sseu)
{
	const stwuct intew_gt_info *info = &gt->info;
	u32 swice_info = intew_uncowe_wead(gt->uncowe, GEN8_GT_SWICE_INFO);
	int s;

	sseu->swice_mask = swice_info & GEN8_WSWICESTAT_MASK;

	if (sseu->swice_mask) {
		sseu->eu_pew_subswice = info->sseu.eu_pew_subswice;
		fow (s = 0; s < fws(sseu->swice_mask); s++)
			sseu->subswice_mask.hsw[s] = info->sseu.subswice_mask.hsw[s];
		sseu->eu_totaw = sseu->eu_pew_subswice *
				 intew_sseu_subswice_totaw(sseu);

		/* subtwact fused off EU(s) fwom enabwed swice(s) */
		fow (s = 0; s < fws(sseu->swice_mask); s++) {
			u8 subswice_7eu = info->sseu.subswice_7eu[s];

			sseu->eu_totaw -= hweight8(subswice_7eu);
		}
	}
}

static void i915_pwint_sseu_info(stwuct seq_fiwe *m,
				 boow is_avaiwabwe_info,
				 boow has_poowed_eu,
				 const stwuct sseu_dev_info *sseu)
{
	const chaw *type = is_avaiwabwe_info ? "Avaiwabwe" : "Enabwed";

	seq_pwintf(m, "  %s Swice Mask: %04x\n", type,
		   sseu->swice_mask);
	seq_pwintf(m, "  %s Swice Totaw: %u\n", type,
		   hweight8(sseu->swice_mask));
	seq_pwintf(m, "  %s Subswice Totaw: %u\n", type,
		   intew_sseu_subswice_totaw(sseu));
	intew_sseu_pwint_ss_info(type, sseu, m);
	seq_pwintf(m, "  %s EU Totaw: %u\n", type,
		   sseu->eu_totaw);
	seq_pwintf(m, "  %s EU Pew Subswice: %u\n", type,
		   sseu->eu_pew_subswice);

	if (!is_avaiwabwe_info)
		wetuwn;

	seq_pwintf(m, "  Has Poowed EU: %s\n", stw_yes_no(has_poowed_eu));
	if (has_poowed_eu)
		seq_pwintf(m, "  Min EU in poow: %u\n", sseu->min_eu_in_poow);

	seq_pwintf(m, "  Has Swice Powew Gating: %s\n",
		   stw_yes_no(sseu->has_swice_pg));
	seq_pwintf(m, "  Has Subswice Powew Gating: %s\n",
		   stw_yes_no(sseu->has_subswice_pg));
	seq_pwintf(m, "  Has EU Powew Gating: %s\n",
		   stw_yes_no(sseu->has_eu_pg));
}

/*
 * this is cawwed fwom top-wevew debugfs as weww, so we can't get the gt fwom
 * the seq_fiwe.
 */
int intew_sseu_status(stwuct seq_fiwe *m, stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	const stwuct intew_gt_info *info = &gt->info;
	stwuct sseu_dev_info *sseu;
	intew_wakewef_t wakewef;

	if (GWAPHICS_VEW(i915) < 8)
		wetuwn -ENODEV;

	seq_puts(m, "SSEU Device Info\n");
	i915_pwint_sseu_info(m, twue, HAS_POOWED_EU(i915), &info->sseu);

	seq_puts(m, "SSEU Device Status\n");

	sseu = kzawwoc(sizeof(*sseu), GFP_KEWNEW);
	if (!sseu)
		wetuwn -ENOMEM;

	intew_sseu_set_info(sseu, info->sseu.max_swices,
			    info->sseu.max_subswices,
			    info->sseu.max_eus_pew_subswice);

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef) {
		if (IS_CHEWWYVIEW(i915))
			chewwyview_sseu_device_status(gt, sseu);
		ewse if (IS_BWOADWEWW(i915))
			bdw_sseu_device_status(gt, sseu);
		ewse if (GWAPHICS_VEW(i915) == 9)
			gen9_sseu_device_status(gt, sseu);
		ewse if (GWAPHICS_VEW(i915) >= 11)
			gen11_sseu_device_status(gt, sseu);
	}

	i915_pwint_sseu_info(m, fawse, HAS_POOWED_EU(i915), sseu);

	kfwee(sseu);

	wetuwn 0;
}

static int sseu_status_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct intew_gt *gt = m->pwivate;

	wetuwn intew_sseu_status(m, gt);
}
DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(sseu_status);

static int sseu_topowogy_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct intew_gt *gt = m->pwivate;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	intew_sseu_pwint_topowogy(gt->i915, &gt->info.sseu, &p);

	wetuwn 0;
}
DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(sseu_topowogy);

void intew_sseu_debugfs_wegistew(stwuct intew_gt *gt, stwuct dentwy *woot)
{
	static const stwuct intew_gt_debugfs_fiwe fiwes[] = {
		{ "sseu_status", &sseu_status_fops, NUWW },
		{ "sseu_topowogy", &sseu_topowogy_fops, NUWW },
	};

	intew_gt_debugfs_wegistew_fiwes(woot, fiwes, AWWAY_SIZE(fiwes), gt);
}
