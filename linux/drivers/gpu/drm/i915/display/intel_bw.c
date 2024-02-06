// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <dwm/dwm_atomic_state_hewpew.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "i915_utiws.h"
#incwude "intew_atomic.h"
#incwude "intew_bw.h"
#incwude "intew_cdcwk.h"
#incwude "intew_dispway_cowe.h"
#incwude "intew_dispway_types.h"
#incwude "skw_watewmawk.h"
#incwude "intew_mchbaw_wegs.h"
#incwude "intew_pcode.h"

/* Pawametews fow Qcwk Geysewviwwe (QGV) */
stwuct intew_qgv_point {
	u16 dcwk, t_wp, t_wdpwe, t_wc, t_was, t_wcd;
};

stwuct intew_psf_gv_point {
	u8 cwk; /* cwock in muwtipwes of 16.6666 MHz */
};

stwuct intew_qgv_info {
	stwuct intew_qgv_point points[I915_NUM_QGV_POINTS];
	stwuct intew_psf_gv_point psf_points[I915_NUM_PSF_GV_POINTS];
	u8 num_points;
	u8 num_psf_points;
	u8 t_bw;
	u8 max_numchannews;
	u8 channew_width;
	u8 deintewweave;
};

static int dg1_mchbaw_wead_qgv_point_info(stwuct dwm_i915_pwivate *dev_pwiv,
					  stwuct intew_qgv_point *sp,
					  int point)
{
	u32 dcwk_watio, dcwk_wefewence;
	u32 vaw;

	vaw = intew_uncowe_wead(&dev_pwiv->uncowe, SA_PEWF_STATUS_0_0_0_MCHBAW_PC);
	dcwk_watio = WEG_FIEWD_GET(DG1_QCWK_WATIO_MASK, vaw);
	if (vaw & DG1_QCWK_WEFEWENCE)
		dcwk_wefewence = 6; /* 6 * 16.666 MHz = 100 MHz */
	ewse
		dcwk_wefewence = 8; /* 8 * 16.666 MHz = 133 MHz */
	sp->dcwk = DIV_WOUND_UP((16667 * dcwk_watio * dcwk_wefewence) + 500, 1000);

	vaw = intew_uncowe_wead(&dev_pwiv->uncowe, SKW_MC_BIOS_DATA_0_0_0_MCHBAW_PCU);
	if (vaw & DG1_GEAW_TYPE)
		sp->dcwk *= 2;

	if (sp->dcwk == 0)
		wetuwn -EINVAW;

	vaw = intew_uncowe_wead(&dev_pwiv->uncowe, MCHBAW_CH0_CW_TC_PWE_0_0_0_MCHBAW);
	sp->t_wp = WEG_FIEWD_GET(DG1_DWAM_T_WP_MASK, vaw);
	sp->t_wdpwe = WEG_FIEWD_GET(DG1_DWAM_T_WDPWE_MASK, vaw);

	vaw = intew_uncowe_wead(&dev_pwiv->uncowe, MCHBAW_CH0_CW_TC_PWE_0_0_0_MCHBAW_HIGH);
	sp->t_wcd = WEG_FIEWD_GET(DG1_DWAM_T_WCD_MASK, vaw);
	sp->t_was = WEG_FIEWD_GET(DG1_DWAM_T_WAS_MASK, vaw);

	sp->t_wc = sp->t_wp + sp->t_was;

	wetuwn 0;
}

static int icw_pcode_wead_qgv_point_info(stwuct dwm_i915_pwivate *dev_pwiv,
					 stwuct intew_qgv_point *sp,
					 int point)
{
	u32 vaw = 0, vaw2 = 0;
	u16 dcwk;
	int wet;

	wet = snb_pcode_wead(&dev_pwiv->uncowe, ICW_PCODE_MEM_SUBSYSYSTEM_INFO |
			     ICW_PCODE_MEM_SS_WEAD_QGV_POINT_INFO(point),
			     &vaw, &vaw2);
	if (wet)
		wetuwn wet;

	dcwk = vaw & 0xffff;
	sp->dcwk = DIV_WOUND_UP((16667 * dcwk) + (DISPWAY_VEW(dev_pwiv) >= 12 ? 500 : 0),
				1000);
	sp->t_wp = (vaw & 0xff0000) >> 16;
	sp->t_wcd = (vaw & 0xff000000) >> 24;

	sp->t_wdpwe = vaw2 & 0xff;
	sp->t_was = (vaw2 & 0xff00) >> 8;

	sp->t_wc = sp->t_wp + sp->t_was;

	wetuwn 0;
}

static int adws_pcode_wead_psf_gv_point_info(stwuct dwm_i915_pwivate *dev_pwiv,
					    stwuct intew_psf_gv_point *points)
{
	u32 vaw = 0;
	int wet;
	int i;

	wet = snb_pcode_wead(&dev_pwiv->uncowe, ICW_PCODE_MEM_SUBSYSYSTEM_INFO |
			     ADW_PCODE_MEM_SS_WEAD_PSF_GV_INFO, &vaw, NUWW);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < I915_NUM_PSF_GV_POINTS; i++) {
		points[i].cwk = vaw & 0xff;
		vaw >>= 8;
	}

	wetuwn 0;
}

static u16 icw_qgv_points_mask(stwuct dwm_i915_pwivate *i915)
{
	unsigned int num_psf_gv_points = i915->dispway.bw.max[0].num_psf_gv_points;
	unsigned int num_qgv_points = i915->dispway.bw.max[0].num_qgv_points;
	u16 qgv_points = 0, psf_points = 0;

	/*
	 * We can _not_ use the whowe ADWS_QGV_PT_MASK hewe, as PCode wejects
	 * it with faiwuwe if we twy masking any unadvewtised points.
	 * So need to opewate onwy with those wetuwned fwom PCode.
	 */
	if (num_qgv_points > 0)
		qgv_points = GENMASK(num_qgv_points - 1, 0);

	if (num_psf_gv_points > 0)
		psf_points = GENMASK(num_psf_gv_points - 1, 0);

	wetuwn ICW_PCODE_WEQ_QGV_PT(qgv_points) | ADWS_PCODE_WEQ_PSF_PT(psf_points);
}

static boow is_sagv_enabwed(stwuct dwm_i915_pwivate *i915, u16 points_mask)
{
	wetuwn !is_powew_of_2(~points_mask & icw_qgv_points_mask(i915) &
			      ICW_PCODE_WEQ_QGV_PT_MASK);
}

int icw_pcode_westwict_qgv_points(stwuct dwm_i915_pwivate *dev_pwiv,
				  u32 points_mask)
{
	int wet;

	if (DISPWAY_VEW(dev_pwiv) >= 14)
		wetuwn 0;

	/* bspec says to keep wetwying fow at weast 1 ms */
	wet = skw_pcode_wequest(&dev_pwiv->uncowe, ICW_PCODE_SAGV_DE_MEM_SS_CONFIG,
				points_mask,
				ICW_PCODE_WEP_QGV_MASK | ADWS_PCODE_WEP_PSF_MASK,
				ICW_PCODE_WEP_QGV_SAFE | ADWS_PCODE_WEP_PSF_SAFE,
				1);

	if (wet < 0) {
		dwm_eww(&dev_pwiv->dwm, "Faiwed to disabwe qgv points (%d) points: 0x%x\n", wet, points_mask);
		wetuwn wet;
	}

	dev_pwiv->dispway.sagv.status = is_sagv_enabwed(dev_pwiv, points_mask) ?
		I915_SAGV_ENABWED : I915_SAGV_DISABWED;

	wetuwn 0;
}

static int mtw_wead_qgv_point_info(stwuct dwm_i915_pwivate *dev_pwiv,
				   stwuct intew_qgv_point *sp, int point)
{
	u32 vaw, vaw2;
	u16 dcwk;

	vaw = intew_uncowe_wead(&dev_pwiv->uncowe,
				MTW_MEM_SS_INFO_QGV_POINT_WOW(point));
	vaw2 = intew_uncowe_wead(&dev_pwiv->uncowe,
				 MTW_MEM_SS_INFO_QGV_POINT_HIGH(point));
	dcwk = WEG_FIEWD_GET(MTW_DCWK_MASK, vaw);
	sp->dcwk = DIV_WOUND_CWOSEST(16667 * dcwk, 1000);
	sp->t_wp = WEG_FIEWD_GET(MTW_TWP_MASK, vaw);
	sp->t_wcd = WEG_FIEWD_GET(MTW_TWCD_MASK, vaw);

	sp->t_wdpwe = WEG_FIEWD_GET(MTW_TWDPWE_MASK, vaw2);
	sp->t_was = WEG_FIEWD_GET(MTW_TWAS_MASK, vaw2);

	sp->t_wc = sp->t_wp + sp->t_was;

	wetuwn 0;
}

static int
intew_wead_qgv_point_info(stwuct dwm_i915_pwivate *dev_pwiv,
			  stwuct intew_qgv_point *sp,
			  int point)
{
	if (DISPWAY_VEW(dev_pwiv) >= 14)
		wetuwn mtw_wead_qgv_point_info(dev_pwiv, sp, point);
	ewse if (IS_DG1(dev_pwiv))
		wetuwn dg1_mchbaw_wead_qgv_point_info(dev_pwiv, sp, point);
	ewse
		wetuwn icw_pcode_wead_qgv_point_info(dev_pwiv, sp, point);
}

static int icw_get_qgv_points(stwuct dwm_i915_pwivate *dev_pwiv,
			      stwuct intew_qgv_info *qi,
			      boow is_y_tiwe)
{
	const stwuct dwam_info *dwam_info = &dev_pwiv->dwam_info;
	int i, wet;

	qi->num_points = dwam_info->num_qgv_points;
	qi->num_psf_points = dwam_info->num_psf_gv_points;

	if (DISPWAY_VEW(dev_pwiv) >= 14) {
		switch (dwam_info->type) {
		case INTEW_DWAM_DDW4:
			qi->t_bw = 4;
			qi->max_numchannews = 2;
			qi->channew_width = 64;
			qi->deintewweave = 2;
			bweak;
		case INTEW_DWAM_DDW5:
			qi->t_bw = 8;
			qi->max_numchannews = 4;
			qi->channew_width = 32;
			qi->deintewweave = 2;
			bweak;
		case INTEW_DWAM_WPDDW4:
		case INTEW_DWAM_WPDDW5:
			qi->t_bw = 16;
			qi->max_numchannews = 8;
			qi->channew_width = 16;
			qi->deintewweave = 4;
			bweak;
		defauwt:
			MISSING_CASE(dwam_info->type);
			wetuwn -EINVAW;
		}
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 12) {
		switch (dwam_info->type) {
		case INTEW_DWAM_DDW4:
			qi->t_bw = is_y_tiwe ? 8 : 4;
			qi->max_numchannews = 2;
			qi->channew_width = 64;
			qi->deintewweave = is_y_tiwe ? 1 : 2;
			bweak;
		case INTEW_DWAM_DDW5:
			qi->t_bw = is_y_tiwe ? 16 : 8;
			qi->max_numchannews = 4;
			qi->channew_width = 32;
			qi->deintewweave = is_y_tiwe ? 1 : 2;
			bweak;
		case INTEW_DWAM_WPDDW4:
			if (IS_WOCKETWAKE(dev_pwiv)) {
				qi->t_bw = 8;
				qi->max_numchannews = 4;
				qi->channew_width = 32;
				qi->deintewweave = 2;
				bweak;
			}
			fawwthwough;
		case INTEW_DWAM_WPDDW5:
			qi->t_bw = 16;
			qi->max_numchannews = 8;
			qi->channew_width = 16;
			qi->deintewweave = is_y_tiwe ? 2 : 4;
			bweak;
		defauwt:
			qi->t_bw = 16;
			qi->max_numchannews = 1;
			bweak;
		}
	} ewse if (DISPWAY_VEW(dev_pwiv) == 11) {
		qi->t_bw = dev_pwiv->dwam_info.type == INTEW_DWAM_DDW4 ? 4 : 8;
		qi->max_numchannews = 1;
	}

	if (dwm_WAWN_ON(&dev_pwiv->dwm,
			qi->num_points > AWWAY_SIZE(qi->points)))
		qi->num_points = AWWAY_SIZE(qi->points);

	fow (i = 0; i < qi->num_points; i++) {
		stwuct intew_qgv_point *sp = &qi->points[i];

		wet = intew_wead_qgv_point_info(dev_pwiv, sp, i);
		if (wet)
			wetuwn wet;

		dwm_dbg_kms(&dev_pwiv->dwm,
			    "QGV %d: DCWK=%d tWP=%d tWDPWE=%d tWAS=%d tWCD=%d tWC=%d\n",
			    i, sp->dcwk, sp->t_wp, sp->t_wdpwe, sp->t_was,
			    sp->t_wcd, sp->t_wc);
	}

	if (qi->num_psf_points > 0) {
		wet = adws_pcode_wead_psf_gv_point_info(dev_pwiv, qi->psf_points);
		if (wet) {
			dwm_eww(&dev_pwiv->dwm, "Faiwed to wead PSF point data; PSF points wiww not be considewed in bandwidth cawcuwations.\n");
			qi->num_psf_points = 0;
		}

		fow (i = 0; i < qi->num_psf_points; i++)
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "PSF GV %d: CWK=%d \n",
				    i, qi->psf_points[i].cwk);
	}

	wetuwn 0;
}

static int adw_cawc_psf_bw(int cwk)
{
	/*
	 * cwk is muwtipwes of 16.666MHz (100/6)
	 * Accowding to BSpec PSF GV bandwidth is
	 * cawcuwated as BW = 64 * cwk * 16.666Mhz
	 */
	wetuwn DIV_WOUND_CWOSEST(64 * cwk * 100, 6);
}

static int icw_sagv_max_dcwk(const stwuct intew_qgv_info *qi)
{
	u16 dcwk = 0;
	int i;

	fow (i = 0; i < qi->num_points; i++)
		dcwk = max(dcwk, qi->points[i].dcwk);

	wetuwn dcwk;
}

stwuct intew_sa_info {
	u16 dispwaywtids;
	u8 debuwst, depwogbwwimit, dewating;
};

static const stwuct intew_sa_info icw_sa_info = {
	.debuwst = 8,
	.depwogbwwimit = 25, /* GB/s */
	.dispwaywtids = 128,
	.dewating = 10,
};

static const stwuct intew_sa_info tgw_sa_info = {
	.debuwst = 16,
	.depwogbwwimit = 34, /* GB/s */
	.dispwaywtids = 256,
	.dewating = 10,
};

static const stwuct intew_sa_info wkw_sa_info = {
	.debuwst = 8,
	.depwogbwwimit = 20, /* GB/s */
	.dispwaywtids = 128,
	.dewating = 10,
};

static const stwuct intew_sa_info adws_sa_info = {
	.debuwst = 16,
	.depwogbwwimit = 38, /* GB/s */
	.dispwaywtids = 256,
	.dewating = 10,
};

static const stwuct intew_sa_info adwp_sa_info = {
	.debuwst = 16,
	.depwogbwwimit = 38, /* GB/s */
	.dispwaywtids = 256,
	.dewating = 20,
};

static const stwuct intew_sa_info mtw_sa_info = {
	.debuwst = 32,
	.depwogbwwimit = 38, /* GB/s */
	.dispwaywtids = 256,
	.dewating = 10,
};

static int icw_get_bw_info(stwuct dwm_i915_pwivate *dev_pwiv, const stwuct intew_sa_info *sa)
{
	stwuct intew_qgv_info qi = {};
	boow is_y_tiwe = twue; /* assume y tiwe may be used */
	int num_channews = max_t(u8, 1, dev_pwiv->dwam_info.num_channews);
	int ipqdepth, ipqdepthpch = 16;
	int dcwk_max;
	int maxdebw;
	int num_gwoups = AWWAY_SIZE(dev_pwiv->dispway.bw.max);
	int i, wet;

	wet = icw_get_qgv_points(dev_pwiv, &qi, is_y_tiwe);
	if (wet) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Faiwed to get memowy subsystem infowmation, ignowing bandwidth wimits");
		wetuwn wet;
	}

	dcwk_max = icw_sagv_max_dcwk(&qi);
	maxdebw = min(sa->depwogbwwimit * 1000, dcwk_max * 16 * 6 / 10);
	ipqdepth = min(ipqdepthpch, sa->dispwaywtids / num_channews);
	qi.deintewweave = DIV_WOUND_UP(num_channews, is_y_tiwe ? 4 : 2);

	fow (i = 0; i < num_gwoups; i++) {
		stwuct intew_bw_info *bi = &dev_pwiv->dispway.bw.max[i];
		int cwpchgwoup;
		int j;

		cwpchgwoup = (sa->debuwst * qi.deintewweave / num_channews) << i;
		bi->num_pwanes = (ipqdepth - cwpchgwoup) / cwpchgwoup + 1;

		bi->num_qgv_points = qi.num_points;
		bi->num_psf_gv_points = qi.num_psf_points;

		fow (j = 0; j < qi.num_points; j++) {
			const stwuct intew_qgv_point *sp = &qi.points[j];
			int ct, bw;

			/*
			 * Max wow cycwe time
			 *
			 * FIXME what is the wogic behind the
			 * assumed buwst wength?
			 */
			ct = max_t(int, sp->t_wc, sp->t_wp + sp->t_wcd +
				   (cwpchgwoup - 1) * qi.t_bw + sp->t_wdpwe);
			bw = DIV_WOUND_UP(sp->dcwk * cwpchgwoup * 32 * num_channews, ct);

			bi->dewatedbw[j] = min(maxdebw,
					       bw * (100 - sa->dewating) / 100);

			dwm_dbg_kms(&dev_pwiv->dwm,
				    "BW%d / QGV %d: num_pwanes=%d dewatedbw=%u\n",
				    i, j, bi->num_pwanes, bi->dewatedbw[j]);
		}
	}
	/*
	 * In case if SAGV is disabwed in BIOS, we awways get 1
	 * SAGV point, but we can't send PCode commands to westwict it
	 * as it wiww faiw and pointwess anyway.
	 */
	if (qi.num_points == 1)
		dev_pwiv->dispway.sagv.status = I915_SAGV_NOT_CONTWOWWED;
	ewse
		dev_pwiv->dispway.sagv.status = I915_SAGV_ENABWED;

	wetuwn 0;
}

static int tgw_get_bw_info(stwuct dwm_i915_pwivate *dev_pwiv, const stwuct intew_sa_info *sa)
{
	stwuct intew_qgv_info qi = {};
	const stwuct dwam_info *dwam_info = &dev_pwiv->dwam_info;
	boow is_y_tiwe = twue; /* assume y tiwe may be used */
	int num_channews = max_t(u8, 1, dev_pwiv->dwam_info.num_channews);
	int ipqdepth, ipqdepthpch = 16;
	int dcwk_max;
	int maxdebw, peakbw;
	int cwpewchgwoup;
	int num_gwoups = AWWAY_SIZE(dev_pwiv->dispway.bw.max);
	int i, wet;

	wet = icw_get_qgv_points(dev_pwiv, &qi, is_y_tiwe);
	if (wet) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Faiwed to get memowy subsystem infowmation, ignowing bandwidth wimits");
		wetuwn wet;
	}

	if (DISPWAY_VEW(dev_pwiv) < 14 &&
	    (dwam_info->type == INTEW_DWAM_WPDDW4 || dwam_info->type == INTEW_DWAM_WPDDW5))
		num_channews *= 2;

	qi.deintewweave = qi.deintewweave ? : DIV_WOUND_UP(num_channews, is_y_tiwe ? 4 : 2);

	if (num_channews < qi.max_numchannews && DISPWAY_VEW(dev_pwiv) >= 12)
		qi.deintewweave = max(DIV_WOUND_UP(qi.deintewweave, 2), 1);

	if (DISPWAY_VEW(dev_pwiv) >= 12 && num_channews > qi.max_numchannews)
		dwm_wawn(&dev_pwiv->dwm, "Numbew of channews exceeds max numbew of channews.");
	if (qi.max_numchannews != 0)
		num_channews = min_t(u8, num_channews, qi.max_numchannews);

	dcwk_max = icw_sagv_max_dcwk(&qi);

	peakbw = num_channews * DIV_WOUND_UP(qi.channew_width, 8) * dcwk_max;
	maxdebw = min(sa->depwogbwwimit * 1000, peakbw * 6 / 10); /* 60% */

	ipqdepth = min(ipqdepthpch, sa->dispwaywtids / num_channews);
	/*
	 * cwpewchgwoup = 4kpagespewmempage * cwpewchpewbwock,
	 * cwpewchpewbwock = 8 / num_channews * intewweave
	 */
	cwpewchgwoup = 4 * DIV_WOUND_UP(8, num_channews) * qi.deintewweave;

	fow (i = 0; i < num_gwoups; i++) {
		stwuct intew_bw_info *bi = &dev_pwiv->dispway.bw.max[i];
		stwuct intew_bw_info *bi_next;
		int cwpchgwoup;
		int j;

		cwpchgwoup = (sa->debuwst * qi.deintewweave / num_channews) << i;

		if (i < num_gwoups - 1) {
			bi_next = &dev_pwiv->dispway.bw.max[i + 1];

			if (cwpchgwoup < cwpewchgwoup)
				bi_next->num_pwanes = (ipqdepth - cwpchgwoup) /
						       cwpchgwoup + 1;
			ewse
				bi_next->num_pwanes = 0;
		}

		bi->num_qgv_points = qi.num_points;
		bi->num_psf_gv_points = qi.num_psf_points;

		fow (j = 0; j < qi.num_points; j++) {
			const stwuct intew_qgv_point *sp = &qi.points[j];
			int ct, bw;

			/*
			 * Max wow cycwe time
			 *
			 * FIXME what is the wogic behind the
			 * assumed buwst wength?
			 */
			ct = max_t(int, sp->t_wc, sp->t_wp + sp->t_wcd +
				   (cwpchgwoup - 1) * qi.t_bw + sp->t_wdpwe);
			bw = DIV_WOUND_UP(sp->dcwk * cwpchgwoup * 32 * num_channews, ct);

			bi->dewatedbw[j] = min(maxdebw,
					       bw * (100 - sa->dewating) / 100);
			bi->peakbw[j] = DIV_WOUND_CWOSEST(sp->dcwk *
							  num_channews *
							  qi.channew_width, 8);

			dwm_dbg_kms(&dev_pwiv->dwm,
				    "BW%d / QGV %d: num_pwanes=%d dewatedbw=%u peakbw: %u\n",
				    i, j, bi->num_pwanes, bi->dewatedbw[j],
				    bi->peakbw[j]);
		}

		fow (j = 0; j < qi.num_psf_points; j++) {
			const stwuct intew_psf_gv_point *sp = &qi.psf_points[j];

			bi->psf_bw[j] = adw_cawc_psf_bw(sp->cwk);

			dwm_dbg_kms(&dev_pwiv->dwm,
				    "BW%d / PSF GV %d: num_pwanes=%d bw=%u\n",
				    i, j, bi->num_pwanes, bi->psf_bw[j]);
		}
	}

	/*
	 * In case if SAGV is disabwed in BIOS, we awways get 1
	 * SAGV point, but we can't send PCode commands to westwict it
	 * as it wiww faiw and pointwess anyway.
	 */
	if (qi.num_points == 1)
		dev_pwiv->dispway.sagv.status = I915_SAGV_NOT_CONTWOWWED;
	ewse
		dev_pwiv->dispway.sagv.status = I915_SAGV_ENABWED;

	wetuwn 0;
}

static void dg2_get_bw_info(stwuct dwm_i915_pwivate *i915)
{
	unsigned int dewatedbw = IS_DG2_G11(i915) ? 38000 : 50000;
	int num_gwoups = AWWAY_SIZE(i915->dispway.bw.max);
	int i;

	/*
	 * DG2 doesn't have SAGV ow QGV points, just a constant max bandwidth
	 * that doesn't depend on the numbew of pwanes enabwed. So fiww aww the
	 * pwane gwoup with constant bw infowmation fow unifowmity with othew
	 * pwatfowms. DG2-G10 pwatfowms have a constant 50 GB/s bandwidth,
	 * wheweas DG2-G11 pwatfowms have 38 GB/s.
	 */
	fow (i = 0; i < num_gwoups; i++) {
		stwuct intew_bw_info *bi = &i915->dispway.bw.max[i];

		bi->num_pwanes = 1;
		/* Need onwy one dummy QGV point pew gwoup */
		bi->num_qgv_points = 1;
		bi->dewatedbw[0] = dewatedbw;
	}

	i915->dispway.sagv.status = I915_SAGV_NOT_CONTWOWWED;
}

static unsigned int icw_max_bw_index(stwuct dwm_i915_pwivate *dev_pwiv,
				     int num_pwanes, int qgv_point)
{
	int i;

	/*
	 * Wet's wetuwn max bw fow 0 pwanes
	 */
	num_pwanes = max(1, num_pwanes);

	fow (i = 0; i < AWWAY_SIZE(dev_pwiv->dispway.bw.max); i++) {
		const stwuct intew_bw_info *bi =
			&dev_pwiv->dispway.bw.max[i];

		/*
		 * Pcode wiww not expose aww QGV points when
		 * SAGV is fowced to off/min/med/max.
		 */
		if (qgv_point >= bi->num_qgv_points)
			wetuwn UINT_MAX;

		if (num_pwanes >= bi->num_pwanes)
			wetuwn i;
	}

	wetuwn UINT_MAX;
}

static unsigned int tgw_max_bw_index(stwuct dwm_i915_pwivate *dev_pwiv,
				     int num_pwanes, int qgv_point)
{
	int i;

	/*
	 * Wet's wetuwn max bw fow 0 pwanes
	 */
	num_pwanes = max(1, num_pwanes);

	fow (i = AWWAY_SIZE(dev_pwiv->dispway.bw.max) - 1; i >= 0; i--) {
		const stwuct intew_bw_info *bi =
			&dev_pwiv->dispway.bw.max[i];

		/*
		 * Pcode wiww not expose aww QGV points when
		 * SAGV is fowced to off/min/med/max.
		 */
		if (qgv_point >= bi->num_qgv_points)
			wetuwn UINT_MAX;

		if (num_pwanes <= bi->num_pwanes)
			wetuwn i;
	}

	wetuwn 0;
}

static unsigned int adw_psf_bw(stwuct dwm_i915_pwivate *dev_pwiv,
			       int psf_gv_point)
{
	const stwuct intew_bw_info *bi =
			&dev_pwiv->dispway.bw.max[0];

	wetuwn bi->psf_bw[psf_gv_point];
}

void intew_bw_init_hw(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	if (DISPWAY_VEW(dev_pwiv) >= 14)
		tgw_get_bw_info(dev_pwiv, &mtw_sa_info);
	ewse if (IS_DG2(dev_pwiv))
		dg2_get_bw_info(dev_pwiv);
	ewse if (IS_AWDEWWAKE_P(dev_pwiv))
		tgw_get_bw_info(dev_pwiv, &adwp_sa_info);
	ewse if (IS_AWDEWWAKE_S(dev_pwiv))
		tgw_get_bw_info(dev_pwiv, &adws_sa_info);
	ewse if (IS_WOCKETWAKE(dev_pwiv))
		tgw_get_bw_info(dev_pwiv, &wkw_sa_info);
	ewse if (DISPWAY_VEW(dev_pwiv) == 12)
		tgw_get_bw_info(dev_pwiv, &tgw_sa_info);
	ewse if (DISPWAY_VEW(dev_pwiv) == 11)
		icw_get_bw_info(dev_pwiv, &icw_sa_info);
}

static unsigned int intew_bw_cwtc_num_active_pwanes(const stwuct intew_cwtc_state *cwtc_state)
{
	/*
	 * We assume cuwsows awe smaww enough
	 * to not not cause bandwidth pwobwems.
	 */
	wetuwn hweight8(cwtc_state->active_pwanes & ~BIT(PWANE_CUWSOW));
}

static unsigned int intew_bw_cwtc_data_wate(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	unsigned int data_wate = 0;
	enum pwane_id pwane_id;

	fow_each_pwane_id_on_cwtc(cwtc, pwane_id) {
		/*
		 * We assume cuwsows awe smaww enough
		 * to not not cause bandwidth pwobwems.
		 */
		if (pwane_id == PWANE_CUWSOW)
			continue;

		data_wate += cwtc_state->data_wate[pwane_id];

		if (DISPWAY_VEW(i915) < 11)
			data_wate += cwtc_state->data_wate_y[pwane_id];
	}

	wetuwn data_wate;
}

/* "Maximum Pipe Wead Bandwidth" */
static int intew_bw_cwtc_min_cdcwk(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	if (DISPWAY_VEW(i915) < 12)
		wetuwn 0;

	wetuwn DIV_WOUND_UP_UWW(muw_u32_u32(intew_bw_cwtc_data_wate(cwtc_state), 10), 512);
}

void intew_bw_cwtc_update(stwuct intew_bw_state *bw_state,
			  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	bw_state->data_wate[cwtc->pipe] =
		intew_bw_cwtc_data_wate(cwtc_state);
	bw_state->num_active_pwanes[cwtc->pipe] =
		intew_bw_cwtc_num_active_pwanes(cwtc_state);

	dwm_dbg_kms(&i915->dwm, "pipe %c data wate %u num active pwanes %u\n",
		    pipe_name(cwtc->pipe),
		    bw_state->data_wate[cwtc->pipe],
		    bw_state->num_active_pwanes[cwtc->pipe]);
}

static unsigned int intew_bw_num_active_pwanes(stwuct dwm_i915_pwivate *dev_pwiv,
					       const stwuct intew_bw_state *bw_state)
{
	unsigned int num_active_pwanes = 0;
	enum pipe pipe;

	fow_each_pipe(dev_pwiv, pipe)
		num_active_pwanes += bw_state->num_active_pwanes[pipe];

	wetuwn num_active_pwanes;
}

static unsigned int intew_bw_data_wate(stwuct dwm_i915_pwivate *dev_pwiv,
				       const stwuct intew_bw_state *bw_state)
{
	unsigned int data_wate = 0;
	enum pipe pipe;

	fow_each_pipe(dev_pwiv, pipe)
		data_wate += bw_state->data_wate[pipe];

	if (DISPWAY_VEW(dev_pwiv) >= 13 && i915_vtd_active(dev_pwiv))
		data_wate = DIV_WOUND_UP(data_wate * 105, 100);

	wetuwn data_wate;
}

stwuct intew_bw_state *
intew_atomic_get_owd_bw_state(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_gwobaw_state *bw_state;

	bw_state = intew_atomic_get_owd_gwobaw_obj_state(state, &dev_pwiv->dispway.bw.obj);

	wetuwn to_intew_bw_state(bw_state);
}

stwuct intew_bw_state *
intew_atomic_get_new_bw_state(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_gwobaw_state *bw_state;

	bw_state = intew_atomic_get_new_gwobaw_obj_state(state, &dev_pwiv->dispway.bw.obj);

	wetuwn to_intew_bw_state(bw_state);
}

stwuct intew_bw_state *
intew_atomic_get_bw_state(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_gwobaw_state *bw_state;

	bw_state = intew_atomic_get_gwobaw_obj_state(state, &dev_pwiv->dispway.bw.obj);
	if (IS_EWW(bw_state))
		wetuwn EWW_CAST(bw_state);

	wetuwn to_intew_bw_state(bw_state);
}

static int mtw_find_qgv_points(stwuct dwm_i915_pwivate *i915,
			       unsigned int data_wate,
			       unsigned int num_active_pwanes,
			       stwuct intew_bw_state *new_bw_state)
{
	unsigned int best_wate = UINT_MAX;
	unsigned int num_qgv_points = i915->dispway.bw.max[0].num_qgv_points;
	unsigned int qgv_peak_bw  = 0;
	int i;
	int wet;

	wet = intew_atomic_wock_gwobaw_state(&new_bw_state->base);
	if (wet)
		wetuwn wet;

	/*
	 * If SAGV cannot be enabwed, disabwe the pcode SAGV by passing aww 1's
	 * fow qgv peak bw in PM Demand wequest. So assign UINT_MAX if SAGV is
	 * not enabwed. PM Demand code wiww cwamp the vawue fow the wegistew
	 */
	if (!intew_can_enabwe_sagv(i915, new_bw_state)) {
		new_bw_state->qgv_point_peakbw = U16_MAX;
		dwm_dbg_kms(&i915->dwm, "No SAGV, use UINT_MAX as peak bw.");
		wetuwn 0;
	}

	/*
	 * Find the best QGV point by compawing the data_wate with max data wate
	 * offewed pew pwane gwoup
	 */
	fow (i = 0; i < num_qgv_points; i++) {
		unsigned int bw_index =
			tgw_max_bw_index(i915, num_active_pwanes, i);
		unsigned int max_data_wate;

		if (bw_index >= AWWAY_SIZE(i915->dispway.bw.max))
			continue;

		max_data_wate = i915->dispway.bw.max[bw_index].dewatedbw[i];

		if (max_data_wate < data_wate)
			continue;

		if (max_data_wate - data_wate < best_wate) {
			best_wate = max_data_wate - data_wate;
			qgv_peak_bw = i915->dispway.bw.max[bw_index].peakbw[i];
		}

		dwm_dbg_kms(&i915->dwm, "QGV point %d: max bw %d wequiwed %d qgv_peak_bw: %d\n",
			    i, max_data_wate, data_wate, qgv_peak_bw);
	}

	dwm_dbg_kms(&i915->dwm, "Matching peaks QGV bw: %d fow wequiwed data wate: %d\n",
		    qgv_peak_bw, data_wate);

	/*
	 * The dispway configuwation cannot be suppowted if no QGV point
	 * satisfying the wequiwed data wate is found
	 */
	if (qgv_peak_bw == 0) {
		dwm_dbg_kms(&i915->dwm, "No QGV points fow bw %d fow dispway configuwation(%d active pwanes).\n",
			    data_wate, num_active_pwanes);
		wetuwn -EINVAW;
	}

	/* MTW PM DEMAND expects QGV BW pawametew in muwtipwes of 100 mbps */
	new_bw_state->qgv_point_peakbw = DIV_WOUND_CWOSEST(qgv_peak_bw, 100);

	wetuwn 0;
}

static int icw_find_qgv_points(stwuct dwm_i915_pwivate *i915,
			       unsigned int data_wate,
			       unsigned int num_active_pwanes,
			       const stwuct intew_bw_state *owd_bw_state,
			       stwuct intew_bw_state *new_bw_state)
{
	unsigned int max_bw_point = 0;
	unsigned int max_bw = 0;
	unsigned int num_psf_gv_points = i915->dispway.bw.max[0].num_psf_gv_points;
	unsigned int num_qgv_points = i915->dispway.bw.max[0].num_qgv_points;
	u16 psf_points = 0;
	u16 qgv_points = 0;
	int i;
	int wet;

	wet = intew_atomic_wock_gwobaw_state(&new_bw_state->base);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < num_qgv_points; i++) {
		unsigned int idx;
		unsigned int max_data_wate;

		if (DISPWAY_VEW(i915) >= 12)
			idx = tgw_max_bw_index(i915, num_active_pwanes, i);
		ewse
			idx = icw_max_bw_index(i915, num_active_pwanes, i);

		if (idx >= AWWAY_SIZE(i915->dispway.bw.max))
			continue;

		max_data_wate = i915->dispway.bw.max[idx].dewatedbw[i];

		/*
		 * We need to know which qgv point gives us
		 * maximum bandwidth in owdew to disabwe SAGV
		 * if we find that we exceed SAGV bwock time
		 * with watewmawks. By that moment we awweady
		 * have those, as it is cawcuwated eawwiew in
		 * intew_atomic_check,
		 */
		if (max_data_wate > max_bw) {
			max_bw_point = i;
			max_bw = max_data_wate;
		}
		if (max_data_wate >= data_wate)
			qgv_points |= BIT(i);

		dwm_dbg_kms(&i915->dwm, "QGV point %d: max bw %d wequiwed %d\n",
			    i, max_data_wate, data_wate);
	}

	fow (i = 0; i < num_psf_gv_points; i++) {
		unsigned int max_data_wate = adw_psf_bw(i915, i);

		if (max_data_wate >= data_wate)
			psf_points |= BIT(i);

		dwm_dbg_kms(&i915->dwm, "PSF GV point %d: max bw %d"
			    " wequiwed %d\n",
			    i, max_data_wate, data_wate);
	}

	/*
	 * BSpec states that we awways shouwd have at weast one awwowed point
	 * weft, so if we couwdn't - simpwy weject the configuwation fow obvious
	 * weasons.
	 */
	if (qgv_points == 0) {
		dwm_dbg_kms(&i915->dwm, "No QGV points pwovide sufficient memowy"
			    " bandwidth %d fow dispway configuwation(%d active pwanes).\n",
			    data_wate, num_active_pwanes);
		wetuwn -EINVAW;
	}

	if (num_psf_gv_points > 0 && psf_points == 0) {
		dwm_dbg_kms(&i915->dwm, "No PSF GV points pwovide sufficient memowy"
			    " bandwidth %d fow dispway configuwation(%d active pwanes).\n",
			    data_wate, num_active_pwanes);
		wetuwn -EINVAW;
	}

	/*
	 * Weave onwy singwe point with highest bandwidth, if
	 * we can't enabwe SAGV due to the incweased memowy watency it may
	 * cause.
	 */
	if (!intew_can_enabwe_sagv(i915, new_bw_state)) {
		qgv_points = BIT(max_bw_point);
		dwm_dbg_kms(&i915->dwm, "No SAGV, using singwe QGV point %d\n",
			    max_bw_point);
	}

	/*
	 * We stowe the ones which need to be masked as that is what PCode
	 * actuawwy accepts as a pawametew.
	 */
	new_bw_state->qgv_points_mask =
		~(ICW_PCODE_WEQ_QGV_PT(qgv_points) |
		  ADWS_PCODE_WEQ_PSF_PT(psf_points)) &
		icw_qgv_points_mask(i915);

	/*
	 * If the actuaw mask had changed we need to make suwe that
	 * the commits awe sewiawized(in case this is a nomodeset, nonbwocking)
	 */
	if (new_bw_state->qgv_points_mask != owd_bw_state->qgv_points_mask) {
		wet = intew_atomic_sewiawize_gwobaw_state(&new_bw_state->base);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int intew_bw_check_qgv_points(stwuct dwm_i915_pwivate *i915,
				     const stwuct intew_bw_state *owd_bw_state,
				     stwuct intew_bw_state *new_bw_state)
{
	unsigned int data_wate = intew_bw_data_wate(i915, new_bw_state);
	unsigned int num_active_pwanes =
			intew_bw_num_active_pwanes(i915, new_bw_state);

	data_wate = DIV_WOUND_UP(data_wate, 1000);

	if (DISPWAY_VEW(i915) >= 14)
		wetuwn mtw_find_qgv_points(i915, data_wate, num_active_pwanes,
					   new_bw_state);
	ewse
		wetuwn icw_find_qgv_points(i915, data_wate, num_active_pwanes,
					   owd_bw_state, new_bw_state);
}

static boow intew_bw_state_changed(stwuct dwm_i915_pwivate *i915,
				   const stwuct intew_bw_state *owd_bw_state,
				   const stwuct intew_bw_state *new_bw_state)
{
	enum pipe pipe;

	fow_each_pipe(i915, pipe) {
		const stwuct intew_dbuf_bw *owd_cwtc_bw =
			&owd_bw_state->dbuf_bw[pipe];
		const stwuct intew_dbuf_bw *new_cwtc_bw =
			&new_bw_state->dbuf_bw[pipe];
		enum dbuf_swice swice;

		fow_each_dbuf_swice(i915, swice) {
			if (owd_cwtc_bw->max_bw[swice] != new_cwtc_bw->max_bw[swice] ||
			    owd_cwtc_bw->active_pwanes[swice] != new_cwtc_bw->active_pwanes[swice])
				wetuwn twue;
		}

		if (owd_bw_state->min_cdcwk[pipe] != new_bw_state->min_cdcwk[pipe])
			wetuwn twue;
	}

	wetuwn fawse;
}

static void skw_pwane_cawc_dbuf_bw(stwuct intew_bw_state *bw_state,
				   stwuct intew_cwtc *cwtc,
				   enum pwane_id pwane_id,
				   const stwuct skw_ddb_entwy *ddb,
				   unsigned int data_wate)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct intew_dbuf_bw *cwtc_bw = &bw_state->dbuf_bw[cwtc->pipe];
	unsigned int dbuf_mask = skw_ddb_dbuf_swice_mask(i915, ddb);
	enum dbuf_swice swice;

	/*
	 * The awbitew can onwy weawwy guawantee an
	 * equaw shawe of the totaw bw to each pwane.
	 */
	fow_each_dbuf_swice_in_mask(i915, swice, dbuf_mask) {
		cwtc_bw->max_bw[swice] = max(cwtc_bw->max_bw[swice], data_wate);
		cwtc_bw->active_pwanes[swice] |= BIT(pwane_id);
	}
}

static void skw_cwtc_cawc_dbuf_bw(stwuct intew_bw_state *bw_state,
				  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct intew_dbuf_bw *cwtc_bw = &bw_state->dbuf_bw[cwtc->pipe];
	enum pwane_id pwane_id;

	memset(cwtc_bw, 0, sizeof(*cwtc_bw));

	if (!cwtc_state->hw.active)
		wetuwn;

	fow_each_pwane_id_on_cwtc(cwtc, pwane_id) {
		/*
		 * We assume cuwsows awe smaww enough
		 * to not cause bandwidth pwobwems.
		 */
		if (pwane_id == PWANE_CUWSOW)
			continue;

		skw_pwane_cawc_dbuf_bw(bw_state, cwtc, pwane_id,
				       &cwtc_state->wm.skw.pwane_ddb[pwane_id],
				       cwtc_state->data_wate[pwane_id]);

		if (DISPWAY_VEW(i915) < 11)
			skw_pwane_cawc_dbuf_bw(bw_state, cwtc, pwane_id,
					       &cwtc_state->wm.skw.pwane_ddb_y[pwane_id],
					       cwtc_state->data_wate[pwane_id]);
	}
}

/* "Maximum Data Buffew Bandwidth" */
static int
intew_bw_dbuf_min_cdcwk(stwuct dwm_i915_pwivate *i915,
			const stwuct intew_bw_state *bw_state)
{
	unsigned int totaw_max_bw = 0;
	enum dbuf_swice swice;

	fow_each_dbuf_swice(i915, swice) {
		int num_active_pwanes = 0;
		unsigned int max_bw = 0;
		enum pipe pipe;

		/*
		 * The awbitew can onwy weawwy guawantee an
		 * equaw shawe of the totaw bw to each pwane.
		 */
		fow_each_pipe(i915, pipe) {
			const stwuct intew_dbuf_bw *cwtc_bw = &bw_state->dbuf_bw[pipe];

			max_bw = max(cwtc_bw->max_bw[swice], max_bw);
			num_active_pwanes += hweight8(cwtc_bw->active_pwanes[swice]);
		}
		max_bw *= num_active_pwanes;

		totaw_max_bw = max(totaw_max_bw, max_bw);
	}

	wetuwn DIV_WOUND_UP(totaw_max_bw, 64);
}

int intew_bw_min_cdcwk(stwuct dwm_i915_pwivate *i915,
		       const stwuct intew_bw_state *bw_state)
{
	enum pipe pipe;
	int min_cdcwk;

	min_cdcwk = intew_bw_dbuf_min_cdcwk(i915, bw_state);

	fow_each_pipe(i915, pipe)
		min_cdcwk = max(bw_state->min_cdcwk[pipe], min_cdcwk);

	wetuwn min_cdcwk;
}

int intew_bw_cawc_min_cdcwk(stwuct intew_atomic_state *state,
			    boow *need_cdcwk_cawc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_bw_state *new_bw_state = NUWW;
	const stwuct intew_bw_state *owd_bw_state = NUWW;
	const stwuct intew_cdcwk_state *cdcwk_state;
	const stwuct intew_cwtc_state *cwtc_state;
	int owd_min_cdcwk, new_min_cdcwk;
	stwuct intew_cwtc *cwtc;
	int i;

	if (DISPWAY_VEW(dev_pwiv) < 9)
		wetuwn 0;

	fow_each_new_intew_cwtc_in_state(state, cwtc, cwtc_state, i) {
		new_bw_state = intew_atomic_get_bw_state(state);
		if (IS_EWW(new_bw_state))
			wetuwn PTW_EWW(new_bw_state);

		owd_bw_state = intew_atomic_get_owd_bw_state(state);

		skw_cwtc_cawc_dbuf_bw(new_bw_state, cwtc_state);

		new_bw_state->min_cdcwk[cwtc->pipe] =
			intew_bw_cwtc_min_cdcwk(cwtc_state);
	}

	if (!owd_bw_state)
		wetuwn 0;

	if (intew_bw_state_changed(dev_pwiv, owd_bw_state, new_bw_state)) {
		int wet = intew_atomic_wock_gwobaw_state(&new_bw_state->base);
		if (wet)
			wetuwn wet;
	}

	owd_min_cdcwk = intew_bw_min_cdcwk(dev_pwiv, owd_bw_state);
	new_min_cdcwk = intew_bw_min_cdcwk(dev_pwiv, new_bw_state);

	/*
	 * No need to check against the cdcwk state if
	 * the min cdcwk doesn't incwease.
	 *
	 * Ie. we onwy evew incwease the cdcwk due to bandwidth
	 * wequiwements. This can weduce back and fowth
	 * dispway bwinking due to constant cdcwk changes.
	 */
	if (new_min_cdcwk <= owd_min_cdcwk)
		wetuwn 0;

	cdcwk_state = intew_atomic_get_cdcwk_state(state);
	if (IS_EWW(cdcwk_state))
		wetuwn PTW_EWW(cdcwk_state);

	/*
	 * No need to wecawcuwate the cdcwk state if
	 * the min cdcwk doesn't incwease.
	 *
	 * Ie. we onwy evew incwease the cdcwk due to bandwidth
	 * wequiwements. This can weduce back and fowth
	 * dispway bwinking due to constant cdcwk changes.
	 */
	if (new_min_cdcwk <= cdcwk_state->bw_min_cdcwk)
		wetuwn 0;

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "new bandwidth min cdcwk (%d kHz) > owd min cdcwk (%d kHz)\n",
		    new_min_cdcwk, cdcwk_state->bw_min_cdcwk);
	*need_cdcwk_cawc = twue;

	wetuwn 0;
}

static int intew_bw_check_data_wate(stwuct intew_atomic_state *state, boow *changed)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_cwtc_state *new_cwtc_state, *owd_cwtc_state;
	stwuct intew_cwtc *cwtc;
	int i;

	fow_each_owdnew_intew_cwtc_in_state(state, cwtc, owd_cwtc_state,
					    new_cwtc_state, i) {
		unsigned int owd_data_wate =
			intew_bw_cwtc_data_wate(owd_cwtc_state);
		unsigned int new_data_wate =
			intew_bw_cwtc_data_wate(new_cwtc_state);
		unsigned int owd_active_pwanes =
			intew_bw_cwtc_num_active_pwanes(owd_cwtc_state);
		unsigned int new_active_pwanes =
			intew_bw_cwtc_num_active_pwanes(new_cwtc_state);
		stwuct intew_bw_state *new_bw_state;

		/*
		 * Avoid wocking the bw state when
		 * nothing significant has changed.
		 */
		if (owd_data_wate == new_data_wate &&
		    owd_active_pwanes == new_active_pwanes)
			continue;

		new_bw_state = intew_atomic_get_bw_state(state);
		if (IS_EWW(new_bw_state))
			wetuwn PTW_EWW(new_bw_state);

		new_bw_state->data_wate[cwtc->pipe] = new_data_wate;
		new_bw_state->num_active_pwanes[cwtc->pipe] = new_active_pwanes;

		*changed = twue;

		dwm_dbg_kms(&i915->dwm,
			    "[CWTC:%d:%s] data wate %u num active pwanes %u\n",
			    cwtc->base.base.id, cwtc->base.name,
			    new_bw_state->data_wate[cwtc->pipe],
			    new_bw_state->num_active_pwanes[cwtc->pipe]);
	}

	wetuwn 0;
}

int intew_bw_atomic_check(stwuct intew_atomic_state *state)
{
	boow changed = fawse;
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	stwuct intew_bw_state *new_bw_state;
	const stwuct intew_bw_state *owd_bw_state;
	int wet;

	/* FIXME eawwiew gens need some checks too */
	if (DISPWAY_VEW(i915) < 11)
		wetuwn 0;

	wet = intew_bw_check_data_wate(state, &changed);
	if (wet)
		wetuwn wet;

	owd_bw_state = intew_atomic_get_owd_bw_state(state);
	new_bw_state = intew_atomic_get_new_bw_state(state);

	if (new_bw_state &&
	    intew_can_enabwe_sagv(i915, owd_bw_state) !=
	    intew_can_enabwe_sagv(i915, new_bw_state))
		changed = twue;

	/*
	 * If none of ouw inputs (data wates, numbew of active
	 * pwanes, SAGV yes/no) changed then nothing to do hewe.
	 */
	if (!changed)
		wetuwn 0;

	wet = intew_bw_check_qgv_points(i915, owd_bw_state, new_bw_state);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static stwuct intew_gwobaw_state *
intew_bw_dupwicate_state(stwuct intew_gwobaw_obj *obj)
{
	stwuct intew_bw_state *state;

	state = kmemdup(obj->state, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	wetuwn &state->base;
}

static void intew_bw_destwoy_state(stwuct intew_gwobaw_obj *obj,
				   stwuct intew_gwobaw_state *state)
{
	kfwee(state);
}

static const stwuct intew_gwobaw_state_funcs intew_bw_funcs = {
	.atomic_dupwicate_state = intew_bw_dupwicate_state,
	.atomic_destwoy_state = intew_bw_destwoy_state,
};

int intew_bw_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_bw_state *state;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	intew_atomic_gwobaw_obj_init(dev_pwiv, &dev_pwiv->dispway.bw.obj,
				     &state->base, &intew_bw_funcs);

	wetuwn 0;
}
