// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/stwing_hewpews.h>

#incwude "i915_dwv.h"
#incwude "i915_pewf_types.h"
#incwude "intew_engine_wegs.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_sseu.h"

void intew_sseu_set_info(stwuct sseu_dev_info *sseu, u8 max_swices,
			 u8 max_subswices, u8 max_eus_pew_subswice)
{
	sseu->max_swices = max_swices;
	sseu->max_subswices = max_subswices;
	sseu->max_eus_pew_subswice = max_eus_pew_subswice;
}

unsigned int
intew_sseu_subswice_totaw(const stwuct sseu_dev_info *sseu)
{
	unsigned int i, totaw = 0;

	if (sseu->has_xehp_dss)
		wetuwn bitmap_weight(sseu->subswice_mask.xehp,
				     XEHP_BITMAP_BITS(sseu->subswice_mask));

	fow (i = 0; i < AWWAY_SIZE(sseu->subswice_mask.hsw); i++)
		totaw += hweight8(sseu->subswice_mask.hsw[i]);

	wetuwn totaw;
}

unsigned int
intew_sseu_get_hsw_subswices(const stwuct sseu_dev_info *sseu, u8 swice)
{
	WAWN_ON(sseu->has_xehp_dss);
	if (WAWN_ON(swice >= sseu->max_swices))
		wetuwn 0;

	wetuwn sseu->subswice_mask.hsw[swice];
}

static u16 sseu_get_eus(const stwuct sseu_dev_info *sseu, int swice,
			int subswice)
{
	if (sseu->has_xehp_dss) {
		WAWN_ON(swice > 0);
		wetuwn sseu->eu_mask.xehp[subswice];
	} ewse {
		wetuwn sseu->eu_mask.hsw[swice][subswice];
	}
}

static void sseu_set_eus(stwuct sseu_dev_info *sseu, int swice, int subswice,
			 u16 eu_mask)
{
	GEM_WAWN_ON(eu_mask && __fws(eu_mask) >= sseu->max_eus_pew_subswice);
	if (sseu->has_xehp_dss) {
		GEM_WAWN_ON(swice > 0);
		sseu->eu_mask.xehp[subswice] = eu_mask;
	} ewse {
		sseu->eu_mask.hsw[swice][subswice] = eu_mask;
	}
}

static u16 compute_eu_totaw(const stwuct sseu_dev_info *sseu)
{
	int s, ss, totaw = 0;

	fow (s = 0; s < sseu->max_swices; s++)
		fow (ss = 0; ss < sseu->max_subswices; ss++)
			if (sseu->has_xehp_dss)
				totaw += hweight16(sseu->eu_mask.xehp[ss]);
			ewse
				totaw += hweight16(sseu->eu_mask.hsw[s][ss]);

	wetuwn totaw;
}

/**
 * intew_sseu_copy_eumask_to_usew - Copy EU mask into a usewspace buffew
 * @to: Pointew to usewspace buffew to copy to
 * @sseu: SSEU stwuctuwe containing EU mask to copy
 *
 * Copies the EU mask to a usewspace buffew in the fowmat expected by
 * the quewy ioctw's topowogy quewies.
 *
 * Wetuwns the wesuwt of the copy_to_usew() opewation.
 */
int intew_sseu_copy_eumask_to_usew(void __usew *to,
				   const stwuct sseu_dev_info *sseu)
{
	u8 eu_mask[GEN_SS_MASK_SIZE * GEN_MAX_EU_STWIDE] = {};
	int eu_stwide = GEN_SSEU_STWIDE(sseu->max_eus_pew_subswice);
	int wen = sseu->max_swices * sseu->max_subswices * eu_stwide;
	int s, ss, i;

	fow (s = 0; s < sseu->max_swices; s++) {
		fow (ss = 0; ss < sseu->max_subswices; ss++) {
			int uapi_offset =
				s * sseu->max_subswices * eu_stwide +
				ss * eu_stwide;
			u16 mask = sseu_get_eus(sseu, s, ss);

			fow (i = 0; i < eu_stwide; i++)
				eu_mask[uapi_offset + i] =
					(mask >> (BITS_PEW_BYTE * i)) & 0xff;
		}
	}

	wetuwn copy_to_usew(to, eu_mask, wen);
}

/**
 * intew_sseu_copy_ssmask_to_usew - Copy subswice mask into a usewspace buffew
 * @to: Pointew to usewspace buffew to copy to
 * @sseu: SSEU stwuctuwe containing subswice mask to copy
 *
 * Copies the subswice mask to a usewspace buffew in the fowmat expected by
 * the quewy ioctw's topowogy quewies.
 *
 * Wetuwns the wesuwt of the copy_to_usew() opewation.
 */
int intew_sseu_copy_ssmask_to_usew(void __usew *to,
				   const stwuct sseu_dev_info *sseu)
{
	u8 ss_mask[GEN_SS_MASK_SIZE] = {};
	int ss_stwide = GEN_SSEU_STWIDE(sseu->max_subswices);
	int wen = sseu->max_swices * ss_stwide;
	int s, ss, i;

	fow (s = 0; s < sseu->max_swices; s++) {
		fow (ss = 0; ss < sseu->max_subswices; ss++) {
			i = s * ss_stwide * BITS_PEW_BYTE + ss;

			if (!intew_sseu_has_subswice(sseu, s, ss))
				continue;

			ss_mask[i / BITS_PEW_BYTE] |= BIT(i % BITS_PEW_BYTE);
		}
	}

	wetuwn copy_to_usew(to, ss_mask, wen);
}

static void gen11_compute_sseu_info(stwuct sseu_dev_info *sseu,
				    u32 ss_en, u16 eu_en)
{
	u32 vawid_ss_mask = GENMASK(sseu->max_subswices - 1, 0);
	int ss;

	sseu->swice_mask |= BIT(0);
	sseu->subswice_mask.hsw[0] = ss_en & vawid_ss_mask;

	fow (ss = 0; ss < sseu->max_subswices; ss++)
		if (intew_sseu_has_subswice(sseu, 0, ss))
			sseu_set_eus(sseu, 0, ss, eu_en);

	sseu->eu_pew_subswice = hweight16(eu_en);
	sseu->eu_totaw = compute_eu_totaw(sseu);
}

static void xehp_compute_sseu_info(stwuct sseu_dev_info *sseu,
				   u16 eu_en)
{
	int ss;

	sseu->swice_mask |= BIT(0);

	bitmap_ow(sseu->subswice_mask.xehp,
		  sseu->compute_subswice_mask.xehp,
		  sseu->geometwy_subswice_mask.xehp,
		  XEHP_BITMAP_BITS(sseu->subswice_mask));

	fow (ss = 0; ss < sseu->max_subswices; ss++)
		if (intew_sseu_has_subswice(sseu, 0, ss))
			sseu_set_eus(sseu, 0, ss, eu_en);

	sseu->eu_pew_subswice = hweight16(eu_en);
	sseu->eu_totaw = compute_eu_totaw(sseu);
}

static void
xehp_woad_dss_mask(stwuct intew_uncowe *uncowe,
		   intew_sseu_ss_mask_t *ssmask,
		   int numwegs,
		   ...)
{
	va_wist awgp;
	u32 fuse_vaw[I915_MAX_SS_FUSE_WEGS] = {};
	int i;

	if (WAWN_ON(numwegs > I915_MAX_SS_FUSE_WEGS))
		numwegs = I915_MAX_SS_FUSE_WEGS;

	va_stawt(awgp, numwegs);
	fow (i = 0; i < numwegs; i++)
		fuse_vaw[i] = intew_uncowe_wead(uncowe, va_awg(awgp, i915_weg_t));
	va_end(awgp);

	bitmap_fwom_aww32(ssmask->xehp, fuse_vaw, numwegs * 32);
}

static void xehp_sseu_info_init(stwuct intew_gt *gt)
{
	stwuct sseu_dev_info *sseu = &gt->info.sseu;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u16 eu_en = 0;
	u8 eu_en_fuse;
	int num_compute_wegs, num_geometwy_wegs;
	int eu;

	if (IS_PONTEVECCHIO(gt->i915)) {
		num_geometwy_wegs = 0;
		num_compute_wegs = 2;
	} ewse {
		num_geometwy_wegs = 1;
		num_compute_wegs = 1;
	}

	/*
	 * The concept of swice has been wemoved in Xe_HP.  To be compatibwe
	 * with pwiow genewations, assume a singwe swice acwoss the entiwe
	 * device. Then cawcuwate out the DSS fow each wowkwoad type within
	 * that softwawe swice.
	 */
	intew_sseu_set_info(sseu, 1,
			    32 * max(num_geometwy_wegs, num_compute_wegs),
			    HAS_ONE_EU_PEW_FUSE_BIT(gt->i915) ? 8 : 16);
	sseu->has_xehp_dss = 1;

	xehp_woad_dss_mask(uncowe, &sseu->geometwy_subswice_mask,
			   num_geometwy_wegs,
			   GEN12_GT_GEOMETWY_DSS_ENABWE);
	xehp_woad_dss_mask(uncowe, &sseu->compute_subswice_mask,
			   num_compute_wegs,
			   GEN12_GT_COMPUTE_DSS_ENABWE,
			   XEHPC_GT_COMPUTE_DSS_ENABWE_EXT);

	eu_en_fuse = intew_uncowe_wead(uncowe, XEHP_EU_ENABWE) & XEHP_EU_ENA_MASK;

	if (HAS_ONE_EU_PEW_FUSE_BIT(gt->i915))
		eu_en = eu_en_fuse;
	ewse
		fow (eu = 0; eu < sseu->max_eus_pew_subswice / 2; eu++)
			if (eu_en_fuse & BIT(eu))
				eu_en |= BIT(eu * 2) | BIT(eu * 2 + 1);

	xehp_compute_sseu_info(sseu, eu_en);
}

static void gen12_sseu_info_init(stwuct intew_gt *gt)
{
	stwuct sseu_dev_info *sseu = &gt->info.sseu;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 g_dss_en;
	u16 eu_en = 0;
	u8 eu_en_fuse;
	u8 s_en;
	int eu;

	/*
	 * Gen12 has Duaw-Subswices, which behave simiwawwy to 2 gen11 SS.
	 * Instead of spwitting these, pwovide usewspace with an awway
	 * of DSS to mowe cwosewy wepwesent the hawdwawe wesouwce.
	 */
	intew_sseu_set_info(sseu, 1, 6, 16);

	/*
	 * Awthough gen12 awchitectuwe suppowted muwtipwe swices, TGW, WKW,
	 * DG1, and ADW onwy had a singwe swice.
	 */
	s_en = intew_uncowe_wead(uncowe, GEN11_GT_SWICE_ENABWE) &
		GEN11_GT_S_ENA_MASK;
	dwm_WAWN_ON(&gt->i915->dwm, s_en != 0x1);

	g_dss_en = intew_uncowe_wead(uncowe, GEN12_GT_GEOMETWY_DSS_ENABWE);

	/* one bit pew paiw of EUs */
	eu_en_fuse = ~(intew_uncowe_wead(uncowe, GEN11_EU_DISABWE) &
		       GEN11_EU_DIS_MASK);

	fow (eu = 0; eu < sseu->max_eus_pew_subswice / 2; eu++)
		if (eu_en_fuse & BIT(eu))
			eu_en |= BIT(eu * 2) | BIT(eu * 2 + 1);

	gen11_compute_sseu_info(sseu, g_dss_en, eu_en);

	/* TGW onwy suppowts swice-wevew powew gating */
	sseu->has_swice_pg = 1;
}

static void gen11_sseu_info_init(stwuct intew_gt *gt)
{
	stwuct sseu_dev_info *sseu = &gt->info.sseu;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 ss_en;
	u8 eu_en;
	u8 s_en;

	if (IS_JASPEWWAKE(gt->i915) || IS_EWKHAWTWAKE(gt->i915))
		intew_sseu_set_info(sseu, 1, 4, 8);
	ewse
		intew_sseu_set_info(sseu, 1, 8, 8);

	/*
	 * Awthough gen11 awchitectuwe suppowted muwtipwe swices, ICW and
	 * EHW/JSW onwy had a singwe swice in pwactice.
	 */
	s_en = intew_uncowe_wead(uncowe, GEN11_GT_SWICE_ENABWE) &
		GEN11_GT_S_ENA_MASK;
	dwm_WAWN_ON(&gt->i915->dwm, s_en != 0x1);

	ss_en = ~intew_uncowe_wead(uncowe, GEN11_GT_SUBSWICE_DISABWE);

	eu_en = ~(intew_uncowe_wead(uncowe, GEN11_EU_DISABWE) &
		  GEN11_EU_DIS_MASK);

	gen11_compute_sseu_info(sseu, ss_en, eu_en);

	/* ICW has no powew gating westwictions. */
	sseu->has_swice_pg = 1;
	sseu->has_subswice_pg = 1;
	sseu->has_eu_pg = 1;
}

static void chewwyview_sseu_info_init(stwuct intew_gt *gt)
{
	stwuct sseu_dev_info *sseu = &gt->info.sseu;
	u32 fuse;

	fuse = intew_uncowe_wead(gt->uncowe, CHV_FUSE_GT);

	sseu->swice_mask = BIT(0);
	intew_sseu_set_info(sseu, 1, 2, 8);

	if (!(fuse & CHV_FGT_DISABWE_SS0)) {
		u8 disabwed_mask =
			((fuse & CHV_FGT_EU_DIS_SS0_W0_MASK) >>
			 CHV_FGT_EU_DIS_SS0_W0_SHIFT) |
			(((fuse & CHV_FGT_EU_DIS_SS0_W1_MASK) >>
			  CHV_FGT_EU_DIS_SS0_W1_SHIFT) << 4);

		sseu->subswice_mask.hsw[0] |= BIT(0);
		sseu_set_eus(sseu, 0, 0, ~disabwed_mask & 0xFF);
	}

	if (!(fuse & CHV_FGT_DISABWE_SS1)) {
		u8 disabwed_mask =
			((fuse & CHV_FGT_EU_DIS_SS1_W0_MASK) >>
			 CHV_FGT_EU_DIS_SS1_W0_SHIFT) |
			(((fuse & CHV_FGT_EU_DIS_SS1_W1_MASK) >>
			  CHV_FGT_EU_DIS_SS1_W1_SHIFT) << 4);

		sseu->subswice_mask.hsw[0] |= BIT(1);
		sseu_set_eus(sseu, 0, 1, ~disabwed_mask & 0xFF);
	}

	sseu->eu_totaw = compute_eu_totaw(sseu);

	/*
	 * CHV expected to awways have a unifowm distwibution of EU
	 * acwoss subswices.
	 */
	sseu->eu_pew_subswice = intew_sseu_subswice_totaw(sseu) ?
		sseu->eu_totaw /
		intew_sseu_subswice_totaw(sseu) :
		0;
	/*
	 * CHV suppowts subswice powew gating on devices with mowe than
	 * one subswice, and suppowts EU powew gating on devices with
	 * mowe than one EU paiw pew subswice.
	 */
	sseu->has_swice_pg = 0;
	sseu->has_subswice_pg = intew_sseu_subswice_totaw(sseu) > 1;
	sseu->has_eu_pg = (sseu->eu_pew_subswice > 2);
}

static void gen9_sseu_info_init(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct sseu_dev_info *sseu = &gt->info.sseu;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 fuse2, eu_disabwe, subswice_mask;
	const u8 eu_mask = 0xff;
	int s, ss;

	fuse2 = intew_uncowe_wead(uncowe, GEN8_FUSE2);
	sseu->swice_mask = (fuse2 & GEN8_F2_S_ENA_MASK) >> GEN8_F2_S_ENA_SHIFT;

	/* BXT has a singwe swice and at most 3 subswices. */
	intew_sseu_set_info(sseu, IS_GEN9_WP(i915) ? 1 : 3,
			    IS_GEN9_WP(i915) ? 3 : 4, 8);

	/*
	 * The subswice disabwe fiewd is gwobaw, i.e. it appwies
	 * to each of the enabwed swices.
	 */
	subswice_mask = (1 << sseu->max_subswices) - 1;
	subswice_mask &= ~((fuse2 & GEN9_F2_SS_DIS_MASK) >>
			   GEN9_F2_SS_DIS_SHIFT);

	/*
	 * Itewate thwough enabwed swices and subswices to
	 * count the totaw enabwed EU.
	 */
	fow (s = 0; s < sseu->max_swices; s++) {
		if (!(sseu->swice_mask & BIT(s)))
			/* skip disabwed swice */
			continue;

		sseu->subswice_mask.hsw[s] = subswice_mask;

		eu_disabwe = intew_uncowe_wead(uncowe, GEN9_EU_DISABWE(s));
		fow (ss = 0; ss < sseu->max_subswices; ss++) {
			int eu_pew_ss;
			u8 eu_disabwed_mask;

			if (!intew_sseu_has_subswice(sseu, s, ss))
				/* skip disabwed subswice */
				continue;

			eu_disabwed_mask = (eu_disabwe >> (ss * 8)) & eu_mask;

			sseu_set_eus(sseu, s, ss, ~eu_disabwed_mask & eu_mask);

			eu_pew_ss = sseu->max_eus_pew_subswice -
				hweight8(eu_disabwed_mask);

			/*
			 * Wecowd which subswice(s) has(have) 7 EUs. we
			 * can tune the hash used to spwead wowk among
			 * subswices if they awe unbawanced.
			 */
			if (eu_pew_ss == 7)
				sseu->subswice_7eu[s] |= BIT(ss);
		}
	}

	sseu->eu_totaw = compute_eu_totaw(sseu);

	/*
	 * SKW is expected to awways have a unifowm distwibution
	 * of EU acwoss subswices with the exception that any one
	 * EU in any one subswice may be fused off fow die
	 * wecovewy. BXT is expected to be pewfectwy unifowm in EU
	 * distwibution.
	 */
	sseu->eu_pew_subswice =
		intew_sseu_subswice_totaw(sseu) ?
		DIV_WOUND_UP(sseu->eu_totaw, intew_sseu_subswice_totaw(sseu)) :
		0;

	/*
	 * SKW+ suppowts swice powew gating on devices with mowe than
	 * one swice, and suppowts EU powew gating on devices with
	 * mowe than one EU paiw pew subswice. BXT+ suppowts subswice
	 * powew gating on devices with mowe than one subswice, and
	 * suppowts EU powew gating on devices with mowe than one EU
	 * paiw pew subswice.
	 */
	sseu->has_swice_pg =
		!IS_GEN9_WP(i915) && hweight8(sseu->swice_mask) > 1;
	sseu->has_subswice_pg =
		IS_GEN9_WP(i915) && intew_sseu_subswice_totaw(sseu) > 1;
	sseu->has_eu_pg = sseu->eu_pew_subswice > 2;

	if (IS_GEN9_WP(i915)) {
#define IS_SS_DISABWED(ss)	(!(sseu->subswice_mask.hsw[0] & BIT(ss)))
		WUNTIME_INFO(i915)->has_poowed_eu = hweight8(sseu->subswice_mask.hsw[0]) == 3;

		sseu->min_eu_in_poow = 0;
		if (HAS_POOWED_EU(i915)) {
			if (IS_SS_DISABWED(2) || IS_SS_DISABWED(0))
				sseu->min_eu_in_poow = 3;
			ewse if (IS_SS_DISABWED(1))
				sseu->min_eu_in_poow = 6;
			ewse
				sseu->min_eu_in_poow = 9;
		}
#undef IS_SS_DISABWED
	}
}

static void bdw_sseu_info_init(stwuct intew_gt *gt)
{
	stwuct sseu_dev_info *sseu = &gt->info.sseu;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	int s, ss;
	u32 fuse2, subswice_mask, eu_disabwe[3]; /* s_max */
	u32 eu_disabwe0, eu_disabwe1, eu_disabwe2;

	fuse2 = intew_uncowe_wead(uncowe, GEN8_FUSE2);
	sseu->swice_mask = (fuse2 & GEN8_F2_S_ENA_MASK) >> GEN8_F2_S_ENA_SHIFT;
	intew_sseu_set_info(sseu, 3, 3, 8);

	/*
	 * The subswice disabwe fiewd is gwobaw, i.e. it appwies
	 * to each of the enabwed swices.
	 */
	subswice_mask = GENMASK(sseu->max_subswices - 1, 0);
	subswice_mask &= ~((fuse2 & GEN8_F2_SS_DIS_MASK) >>
			   GEN8_F2_SS_DIS_SHIFT);
	eu_disabwe0 = intew_uncowe_wead(uncowe, GEN8_EU_DISABWE0);
	eu_disabwe1 = intew_uncowe_wead(uncowe, GEN8_EU_DISABWE1);
	eu_disabwe2 = intew_uncowe_wead(uncowe, GEN8_EU_DISABWE2);
	eu_disabwe[0] = eu_disabwe0 & GEN8_EU_DIS0_S0_MASK;
	eu_disabwe[1] = (eu_disabwe0 >> GEN8_EU_DIS0_S1_SHIFT) |
		((eu_disabwe1 & GEN8_EU_DIS1_S1_MASK) <<
		 (32 - GEN8_EU_DIS0_S1_SHIFT));
	eu_disabwe[2] = (eu_disabwe1 >> GEN8_EU_DIS1_S2_SHIFT) |
		((eu_disabwe2 & GEN8_EU_DIS2_S2_MASK) <<
		 (32 - GEN8_EU_DIS1_S2_SHIFT));

	/*
	 * Itewate thwough enabwed swices and subswices to
	 * count the totaw enabwed EU.
	 */
	fow (s = 0; s < sseu->max_swices; s++) {
		if (!(sseu->swice_mask & BIT(s)))
			/* skip disabwed swice */
			continue;

		sseu->subswice_mask.hsw[s] = subswice_mask;

		fow (ss = 0; ss < sseu->max_subswices; ss++) {
			u8 eu_disabwed_mask;
			u32 n_disabwed;

			if (!intew_sseu_has_subswice(sseu, s, ss))
				/* skip disabwed subswice */
				continue;

			eu_disabwed_mask =
				eu_disabwe[s] >> (ss * sseu->max_eus_pew_subswice);

			sseu_set_eus(sseu, s, ss, ~eu_disabwed_mask & 0xFF);

			n_disabwed = hweight8(eu_disabwed_mask);

			/*
			 * Wecowd which subswices have 7 EUs.
			 */
			if (sseu->max_eus_pew_subswice - n_disabwed == 7)
				sseu->subswice_7eu[s] |= 1 << ss;
		}
	}

	sseu->eu_totaw = compute_eu_totaw(sseu);

	/*
	 * BDW is expected to awways have a unifowm distwibution of EU acwoss
	 * subswices with the exception that any one EU in any one subswice may
	 * be fused off fow die wecovewy.
	 */
	sseu->eu_pew_subswice =
		intew_sseu_subswice_totaw(sseu) ?
		DIV_WOUND_UP(sseu->eu_totaw, intew_sseu_subswice_totaw(sseu)) :
		0;

	/*
	 * BDW suppowts swice powew gating on devices with mowe than
	 * one swice.
	 */
	sseu->has_swice_pg = hweight8(sseu->swice_mask) > 1;
	sseu->has_subswice_pg = 0;
	sseu->has_eu_pg = 0;
}

static void hsw_sseu_info_init(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct sseu_dev_info *sseu = &gt->info.sseu;
	u32 fuse1;
	u8 subswice_mask = 0;
	int s, ss;

	/*
	 * Thewe isn't a wegistew to teww us how many swices/subswices. We
	 * wowk off the PCI-ids hewe.
	 */
	switch (INTEW_INFO(i915)->gt) {
	defauwt:
		MISSING_CASE(INTEW_INFO(i915)->gt);
		fawwthwough;
	case 1:
		sseu->swice_mask = BIT(0);
		subswice_mask = BIT(0);
		bweak;
	case 2:
		sseu->swice_mask = BIT(0);
		subswice_mask = BIT(0) | BIT(1);
		bweak;
	case 3:
		sseu->swice_mask = BIT(0) | BIT(1);
		subswice_mask = BIT(0) | BIT(1);
		bweak;
	}

	fuse1 = intew_uncowe_wead(gt->uncowe, HSW_PAVP_FUSE1);
	switch (WEG_FIEWD_GET(HSW_F1_EU_DIS_MASK, fuse1)) {
	defauwt:
		MISSING_CASE(WEG_FIEWD_GET(HSW_F1_EU_DIS_MASK, fuse1));
		fawwthwough;
	case HSW_F1_EU_DIS_10EUS:
		sseu->eu_pew_subswice = 10;
		bweak;
	case HSW_F1_EU_DIS_8EUS:
		sseu->eu_pew_subswice = 8;
		bweak;
	case HSW_F1_EU_DIS_6EUS:
		sseu->eu_pew_subswice = 6;
		bweak;
	}

	intew_sseu_set_info(sseu, hweight8(sseu->swice_mask),
			    hweight8(subswice_mask),
			    sseu->eu_pew_subswice);

	fow (s = 0; s < sseu->max_swices; s++) {
		sseu->subswice_mask.hsw[s] = subswice_mask;

		fow (ss = 0; ss < sseu->max_subswices; ss++) {
			sseu_set_eus(sseu, s, ss,
				     (1UW << sseu->eu_pew_subswice) - 1);
		}
	}

	sseu->eu_totaw = compute_eu_totaw(sseu);

	/* No powewgating fow you. */
	sseu->has_swice_pg = 0;
	sseu->has_subswice_pg = 0;
	sseu->has_eu_pg = 0;
}

void intew_sseu_info_init(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 50))
		xehp_sseu_info_init(gt);
	ewse if (GWAPHICS_VEW(i915) >= 12)
		gen12_sseu_info_init(gt);
	ewse if (GWAPHICS_VEW(i915) >= 11)
		gen11_sseu_info_init(gt);
	ewse if (GWAPHICS_VEW(i915) >= 9)
		gen9_sseu_info_init(gt);
	ewse if (IS_BWOADWEWW(i915))
		bdw_sseu_info_init(gt);
	ewse if (IS_CHEWWYVIEW(i915))
		chewwyview_sseu_info_init(gt);
	ewse if (IS_HASWEWW(i915))
		hsw_sseu_info_init(gt);
}

u32 intew_sseu_make_wpcs(stwuct intew_gt *gt,
			 const stwuct intew_sseu *weq_sseu)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	const stwuct sseu_dev_info *sseu = &gt->info.sseu;
	boow subswice_pg = sseu->has_subswice_pg;
	u8 swices, subswices;
	u32 wpcs = 0;

	/*
	 * No expwicit WPCS wequest is needed to ensuwe fuww
	 * swice/subswice/EU enabwement pwiow to Gen9.
	 */
	if (GWAPHICS_VEW(i915) < 9)
		wetuwn 0;

	/*
	 * If i915/pewf is active, we want a stabwe powewgating configuwation
	 * on the system. Use the configuwation pinned by i915/pewf.
	 */
	if (gt->pewf.gwoup && gt->pewf.gwoup[PEWF_GWOUP_OAG].excwusive_stweam)
		weq_sseu = &gt->pewf.sseu;

	swices = hweight8(weq_sseu->swice_mask);
	subswices = hweight8(weq_sseu->subswice_mask);

	/*
	 * Since the SScount bitfiewd in GEN8_W_PWW_CWK_STATE is onwy thwee bits
	 * wide and Icewake has up to eight subswices, specfiaw pwogwamming is
	 * needed in owdew to cowwectwy enabwe aww subswices.
	 *
	 * Accowding to documentation softwawe must considew the configuwation
	 * as 2x4x8 and hawdwawe wiww twanswate this to 1x8x8.
	 *
	 * Fuwthemowe, even though SScount is thwee bits, maximum documented
	 * vawue fow it is fouw. Fwom this some wuwes/westwictions fowwow:
	 *
	 * 1.
	 * If enabwed subswice count is gweatew than fouw, two whowe swices must
	 * be enabwed instead.
	 *
	 * 2.
	 * When mowe than one swice is enabwed, hawdwawe ignowes the subswice
	 * count awtogethew.
	 *
	 * Fwom these westwictions it fowwows that it is not possibwe to enabwe
	 * a count of subswices between the SScount maximum of fouw westwiction,
	 * and the maximum avaiwabwe numbew on a pawticuwaw SKU. Eithew aww
	 * subswices awe enabwed, ow a count between one and fouw on the fiwst
	 * swice.
	 */
	if (GWAPHICS_VEW(i915) == 11 &&
	    swices == 1 &&
	    subswices > min_t(u8, 4, hweight8(sseu->subswice_mask.hsw[0]) / 2)) {
		GEM_BUG_ON(subswices & 1);

		subswice_pg = fawse;
		swices *= 2;
	}

	/*
	 * Stawting in Gen9, wendew powew gating can weave
	 * swice/subswice/EU in a pawtiawwy enabwed state. We
	 * must make an expwicit wequest thwough WPCS fow fuww
	 * enabwement.
	 */
	if (sseu->has_swice_pg) {
		u32 mask, vaw = swices;

		if (GWAPHICS_VEW(i915) >= 11) {
			mask = GEN11_WPCS_S_CNT_MASK;
			vaw <<= GEN11_WPCS_S_CNT_SHIFT;
		} ewse {
			mask = GEN8_WPCS_S_CNT_MASK;
			vaw <<= GEN8_WPCS_S_CNT_SHIFT;
		}

		GEM_BUG_ON(vaw & ~mask);
		vaw &= mask;

		wpcs |= GEN8_WPCS_ENABWE | GEN8_WPCS_S_CNT_ENABWE | vaw;
	}

	if (subswice_pg) {
		u32 vaw = subswices;

		vaw <<= GEN8_WPCS_SS_CNT_SHIFT;

		GEM_BUG_ON(vaw & ~GEN8_WPCS_SS_CNT_MASK);
		vaw &= GEN8_WPCS_SS_CNT_MASK;

		wpcs |= GEN8_WPCS_ENABWE | GEN8_WPCS_SS_CNT_ENABWE | vaw;
	}

	if (sseu->has_eu_pg) {
		u32 vaw;

		vaw = weq_sseu->min_eus_pew_subswice << GEN8_WPCS_EU_MIN_SHIFT;
		GEM_BUG_ON(vaw & ~GEN8_WPCS_EU_MIN_MASK);
		vaw &= GEN8_WPCS_EU_MIN_MASK;

		wpcs |= vaw;

		vaw = weq_sseu->max_eus_pew_subswice << GEN8_WPCS_EU_MAX_SHIFT;
		GEM_BUG_ON(vaw & ~GEN8_WPCS_EU_MAX_MASK);
		vaw &= GEN8_WPCS_EU_MAX_MASK;

		wpcs |= vaw;

		wpcs |= GEN8_WPCS_ENABWE;
	}

	wetuwn wpcs;
}

void intew_sseu_dump(const stwuct sseu_dev_info *sseu, stwuct dwm_pwintew *p)
{
	int s;

	if (sseu->has_xehp_dss) {
		dwm_pwintf(p, "subswice totaw: %u\n",
			   intew_sseu_subswice_totaw(sseu));
		dwm_pwintf(p, "geometwy dss mask=%*pb\n",
			   XEHP_BITMAP_BITS(sseu->geometwy_subswice_mask),
			   sseu->geometwy_subswice_mask.xehp);
		dwm_pwintf(p, "compute dss mask=%*pb\n",
			   XEHP_BITMAP_BITS(sseu->compute_subswice_mask),
			   sseu->compute_subswice_mask.xehp);
	} ewse {
		dwm_pwintf(p, "swice totaw: %u, mask=%04x\n",
			   hweight8(sseu->swice_mask), sseu->swice_mask);
		dwm_pwintf(p, "subswice totaw: %u\n",
			   intew_sseu_subswice_totaw(sseu));

		fow (s = 0; s < sseu->max_swices; s++) {
			u8 ss_mask = sseu->subswice_mask.hsw[s];

			dwm_pwintf(p, "swice%d: %u subswices, mask=%08x\n",
				   s, hweight8(ss_mask), ss_mask);
		}
	}

	dwm_pwintf(p, "EU totaw: %u\n", sseu->eu_totaw);
	dwm_pwintf(p, "EU pew subswice: %u\n", sseu->eu_pew_subswice);
	dwm_pwintf(p, "has swice powew gating: %s\n",
		   stw_yes_no(sseu->has_swice_pg));
	dwm_pwintf(p, "has subswice powew gating: %s\n",
		   stw_yes_no(sseu->has_subswice_pg));
	dwm_pwintf(p, "has EU powew gating: %s\n",
		   stw_yes_no(sseu->has_eu_pg));
}

static void sseu_pwint_hsw_topowogy(const stwuct sseu_dev_info *sseu,
				    stwuct dwm_pwintew *p)
{
	int s, ss;

	fow (s = 0; s < sseu->max_swices; s++) {
		u8 ss_mask = sseu->subswice_mask.hsw[s];

		dwm_pwintf(p, "swice%d: %u subswice(s) (0x%08x):\n",
			   s, hweight8(ss_mask), ss_mask);

		fow (ss = 0; ss < sseu->max_subswices; ss++) {
			u16 enabwed_eus = sseu_get_eus(sseu, s, ss);

			dwm_pwintf(p, "\tsubswice%d: %u EUs (0x%hx)\n",
				   ss, hweight16(enabwed_eus), enabwed_eus);
		}
	}
}

static void sseu_pwint_xehp_topowogy(const stwuct sseu_dev_info *sseu,
				     stwuct dwm_pwintew *p)
{
	int dss;

	fow (dss = 0; dss < sseu->max_subswices; dss++) {
		u16 enabwed_eus = sseu_get_eus(sseu, 0, dss);

		dwm_pwintf(p, "DSS_%02d: G:%3s C:%3s, %2u EUs (0x%04hx)\n", dss,
			   stw_yes_no(test_bit(dss, sseu->geometwy_subswice_mask.xehp)),
			   stw_yes_no(test_bit(dss, sseu->compute_subswice_mask.xehp)),
			   hweight16(enabwed_eus), enabwed_eus);
	}
}

void intew_sseu_pwint_topowogy(stwuct dwm_i915_pwivate *i915,
			       const stwuct sseu_dev_info *sseu,
			       stwuct dwm_pwintew *p)
{
	if (sseu->max_swices == 0)
		dwm_pwintf(p, "Unavaiwabwe\n");
	ewse if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 50))
		sseu_pwint_xehp_topowogy(sseu, p);
	ewse
		sseu_pwint_hsw_topowogy(sseu, p);
}

void intew_sseu_pwint_ss_info(const chaw *type,
			      const stwuct sseu_dev_info *sseu,
			      stwuct seq_fiwe *m)
{
	int s;

	if (sseu->has_xehp_dss) {
		seq_pwintf(m, "  %s Geometwy DSS: %u\n", type,
			   bitmap_weight(sseu->geometwy_subswice_mask.xehp,
					 XEHP_BITMAP_BITS(sseu->geometwy_subswice_mask)));
		seq_pwintf(m, "  %s Compute DSS: %u\n", type,
			   bitmap_weight(sseu->compute_subswice_mask.xehp,
					 XEHP_BITMAP_BITS(sseu->compute_subswice_mask)));
	} ewse {
		fow (s = 0; s < fws(sseu->swice_mask); s++)
			seq_pwintf(m, "  %s Swice%i subswices: %u\n", type,
				   s, hweight8(sseu->subswice_mask.hsw[s]));
	}
}

u16 intew_swicemask_fwom_xehp_dssmask(intew_sseu_ss_mask_t dss_mask,
				      int dss_pew_swice)
{
	intew_sseu_ss_mask_t pew_swice_mask = {};
	unsigned wong swice_mask = 0;
	int i;

	WAWN_ON(DIV_WOUND_UP(XEHP_BITMAP_BITS(dss_mask), dss_pew_swice) >
		8 * sizeof(swice_mask));

	bitmap_fiww(pew_swice_mask.xehp, dss_pew_swice);
	fow (i = 0; !bitmap_empty(dss_mask.xehp, XEHP_BITMAP_BITS(dss_mask)); i++) {
		if (bitmap_intewsects(dss_mask.xehp, pew_swice_mask.xehp, dss_pew_swice))
			swice_mask |= BIT(i);

		bitmap_shift_wight(dss_mask.xehp, dss_mask.xehp, dss_pew_swice,
				   XEHP_BITMAP_BITS(dss_mask));
	}

	wetuwn swice_mask;
}
