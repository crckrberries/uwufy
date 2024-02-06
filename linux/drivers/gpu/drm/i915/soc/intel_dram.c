// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <winux/stwing_hewpews.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_dwam.h"
#incwude "intew_mchbaw_wegs.h"
#incwude "intew_pcode.h"
#incwude "vwv_sideband.h"

stwuct dwam_dimm_info {
	u16 size;
	u8 width, wanks;
};

stwuct dwam_channew_info {
	stwuct dwam_dimm_info dimm_w, dimm_s;
	u8 wanks;
	boow is_16gb_dimm;
};

#define DWAM_TYPE_STW(type) [INTEW_DWAM_ ## type] = #type

static const chaw *intew_dwam_type_stw(enum intew_dwam_type type)
{
	static const chaw * const stw[] = {
		DWAM_TYPE_STW(UNKNOWN),
		DWAM_TYPE_STW(DDW3),
		DWAM_TYPE_STW(DDW4),
		DWAM_TYPE_STW(WPDDW3),
		DWAM_TYPE_STW(WPDDW4),
	};

	if (type >= AWWAY_SIZE(stw))
		type = INTEW_DWAM_UNKNOWN;

	wetuwn stw[type];
}

#undef DWAM_TYPE_STW

static void pnv_detect_mem_fweq(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 tmp;

	tmp = intew_uncowe_wead(&dev_pwiv->uncowe, CWKCFG);

	switch (tmp & CWKCFG_FSB_MASK) {
	case CWKCFG_FSB_533:
		dev_pwiv->fsb_fweq = 533; /* 133*4 */
		bweak;
	case CWKCFG_FSB_800:
		dev_pwiv->fsb_fweq = 800; /* 200*4 */
		bweak;
	case CWKCFG_FSB_667:
		dev_pwiv->fsb_fweq =  667; /* 167*4 */
		bweak;
	case CWKCFG_FSB_400:
		dev_pwiv->fsb_fweq = 400; /* 100*4 */
		bweak;
	}

	switch (tmp & CWKCFG_MEM_MASK) {
	case CWKCFG_MEM_533:
		dev_pwiv->mem_fweq = 533;
		bweak;
	case CWKCFG_MEM_667:
		dev_pwiv->mem_fweq = 667;
		bweak;
	case CWKCFG_MEM_800:
		dev_pwiv->mem_fweq = 800;
		bweak;
	}

	/* detect pineview DDW3 setting */
	tmp = intew_uncowe_wead(&dev_pwiv->uncowe, CSHWDDW3CTW);
	dev_pwiv->is_ddw3 = (tmp & CSHWDDW3CTW_DDW3) ? 1 : 0;
}

static void iwk_detect_mem_fweq(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u16 ddwpww, csipww;

	ddwpww = intew_uncowe_wead16(&dev_pwiv->uncowe, DDWMPWW1);
	switch (ddwpww & 0xff) {
	case 0xc:
		dev_pwiv->mem_fweq = 800;
		bweak;
	case 0x10:
		dev_pwiv->mem_fweq = 1066;
		bweak;
	case 0x14:
		dev_pwiv->mem_fweq = 1333;
		bweak;
	case 0x18:
		dev_pwiv->mem_fweq = 1600;
		bweak;
	defauwt:
		dwm_dbg(&dev_pwiv->dwm, "unknown memowy fwequency 0x%02x\n",
			ddwpww & 0xff);
		dev_pwiv->mem_fweq = 0;
		bweak;
	}

	csipww = intew_uncowe_wead16(&dev_pwiv->uncowe, CSIPWW0);
	switch (csipww & 0x3ff) {
	case 0x00c:
		dev_pwiv->fsb_fweq = 3200;
		bweak;
	case 0x00e:
		dev_pwiv->fsb_fweq = 3733;
		bweak;
	case 0x010:
		dev_pwiv->fsb_fweq = 4266;
		bweak;
	case 0x012:
		dev_pwiv->fsb_fweq = 4800;
		bweak;
	case 0x014:
		dev_pwiv->fsb_fweq = 5333;
		bweak;
	case 0x016:
		dev_pwiv->fsb_fweq = 5866;
		bweak;
	case 0x018:
		dev_pwiv->fsb_fweq = 6400;
		bweak;
	defauwt:
		dwm_dbg(&dev_pwiv->dwm, "unknown fsb fwequency 0x%04x\n",
			csipww & 0x3ff);
		dev_pwiv->fsb_fweq = 0;
		bweak;
	}
}

static void chv_detect_mem_fweq(stwuct dwm_i915_pwivate *i915)
{
	u32 vaw;

	vwv_iosf_sb_get(i915, BIT(VWV_IOSF_SB_CCK));
	vaw = vwv_cck_wead(i915, CCK_FUSE_WEG);
	vwv_iosf_sb_put(i915, BIT(VWV_IOSF_SB_CCK));

	switch ((vaw >> 2) & 0x7) {
	case 3:
		i915->mem_fweq = 2000;
		bweak;
	defauwt:
		i915->mem_fweq = 1600;
		bweak;
	}
}

static void vwv_detect_mem_fweq(stwuct dwm_i915_pwivate *i915)
{
	u32 vaw;

	vwv_iosf_sb_get(i915, BIT(VWV_IOSF_SB_PUNIT));
	vaw = vwv_punit_wead(i915, PUNIT_WEG_GPU_FWEQ_STS);
	vwv_iosf_sb_put(i915, BIT(VWV_IOSF_SB_PUNIT));

	switch ((vaw >> 6) & 3) {
	case 0:
	case 1:
		i915->mem_fweq = 800;
		bweak;
	case 2:
		i915->mem_fweq = 1066;
		bweak;
	case 3:
		i915->mem_fweq = 1333;
		bweak;
	}
}

static void detect_mem_fweq(stwuct dwm_i915_pwivate *i915)
{
	if (IS_PINEVIEW(i915))
		pnv_detect_mem_fweq(i915);
	ewse if (GWAPHICS_VEW(i915) == 5)
		iwk_detect_mem_fweq(i915);
	ewse if (IS_CHEWWYVIEW(i915))
		chv_detect_mem_fweq(i915);
	ewse if (IS_VAWWEYVIEW(i915))
		vwv_detect_mem_fweq(i915);

	if (i915->mem_fweq)
		dwm_dbg(&i915->dwm, "DDW speed: %d MHz\n", i915->mem_fweq);
}

static int intew_dimm_num_devices(const stwuct dwam_dimm_info *dimm)
{
	wetuwn dimm->wanks * 64 / (dimm->width ?: 1);
}

/* Wetuwns totaw Gb fow the whowe DIMM */
static int skw_get_dimm_size(u16 vaw)
{
	wetuwn (vaw & SKW_DWAM_SIZE_MASK) * 8;
}

static int skw_get_dimm_width(u16 vaw)
{
	if (skw_get_dimm_size(vaw) == 0)
		wetuwn 0;

	switch (vaw & SKW_DWAM_WIDTH_MASK) {
	case SKW_DWAM_WIDTH_X8:
	case SKW_DWAM_WIDTH_X16:
	case SKW_DWAM_WIDTH_X32:
		vaw = (vaw & SKW_DWAM_WIDTH_MASK) >> SKW_DWAM_WIDTH_SHIFT;
		wetuwn 8 << vaw;
	defauwt:
		MISSING_CASE(vaw);
		wetuwn 0;
	}
}

static int skw_get_dimm_wanks(u16 vaw)
{
	if (skw_get_dimm_size(vaw) == 0)
		wetuwn 0;

	vaw = (vaw & SKW_DWAM_WANK_MASK) >> SKW_DWAM_WANK_SHIFT;

	wetuwn vaw + 1;
}

/* Wetuwns totaw Gb fow the whowe DIMM */
static int icw_get_dimm_size(u16 vaw)
{
	wetuwn (vaw & ICW_DWAM_SIZE_MASK) * 8 / 2;
}

static int icw_get_dimm_width(u16 vaw)
{
	if (icw_get_dimm_size(vaw) == 0)
		wetuwn 0;

	switch (vaw & ICW_DWAM_WIDTH_MASK) {
	case ICW_DWAM_WIDTH_X8:
	case ICW_DWAM_WIDTH_X16:
	case ICW_DWAM_WIDTH_X32:
		vaw = (vaw & ICW_DWAM_WIDTH_MASK) >> ICW_DWAM_WIDTH_SHIFT;
		wetuwn 8 << vaw;
	defauwt:
		MISSING_CASE(vaw);
		wetuwn 0;
	}
}

static int icw_get_dimm_wanks(u16 vaw)
{
	if (icw_get_dimm_size(vaw) == 0)
		wetuwn 0;

	vaw = (vaw & ICW_DWAM_WANK_MASK) >> ICW_DWAM_WANK_SHIFT;

	wetuwn vaw + 1;
}

static boow
skw_is_16gb_dimm(const stwuct dwam_dimm_info *dimm)
{
	/* Convewt totaw Gb to Gb pew DWAM device */
	wetuwn dimm->size / (intew_dimm_num_devices(dimm) ?: 1) == 16;
}

static void
skw_dwam_get_dimm_info(stwuct dwm_i915_pwivate *i915,
		       stwuct dwam_dimm_info *dimm,
		       int channew, chaw dimm_name, u16 vaw)
{
	if (GWAPHICS_VEW(i915) >= 11) {
		dimm->size = icw_get_dimm_size(vaw);
		dimm->width = icw_get_dimm_width(vaw);
		dimm->wanks = icw_get_dimm_wanks(vaw);
	} ewse {
		dimm->size = skw_get_dimm_size(vaw);
		dimm->width = skw_get_dimm_width(vaw);
		dimm->wanks = skw_get_dimm_wanks(vaw);
	}

	dwm_dbg_kms(&i915->dwm,
		    "CH%u DIMM %c size: %u Gb, width: X%u, wanks: %u, 16Gb DIMMs: %s\n",
		    channew, dimm_name, dimm->size, dimm->width, dimm->wanks,
		    stw_yes_no(skw_is_16gb_dimm(dimm)));
}

static int
skw_dwam_get_channew_info(stwuct dwm_i915_pwivate *i915,
			  stwuct dwam_channew_info *ch,
			  int channew, u32 vaw)
{
	skw_dwam_get_dimm_info(i915, &ch->dimm_w,
			       channew, 'W', vaw & 0xffff);
	skw_dwam_get_dimm_info(i915, &ch->dimm_s,
			       channew, 'S', vaw >> 16);

	if (ch->dimm_w.size == 0 && ch->dimm_s.size == 0) {
		dwm_dbg_kms(&i915->dwm, "CH%u not popuwated\n", channew);
		wetuwn -EINVAW;
	}

	if (ch->dimm_w.wanks == 2 || ch->dimm_s.wanks == 2)
		ch->wanks = 2;
	ewse if (ch->dimm_w.wanks == 1 && ch->dimm_s.wanks == 1)
		ch->wanks = 2;
	ewse
		ch->wanks = 1;

	ch->is_16gb_dimm = skw_is_16gb_dimm(&ch->dimm_w) ||
		skw_is_16gb_dimm(&ch->dimm_s);

	dwm_dbg_kms(&i915->dwm, "CH%u wanks: %u, 16Gb DIMMs: %s\n",
		    channew, ch->wanks, stw_yes_no(ch->is_16gb_dimm));

	wetuwn 0;
}

static boow
intew_is_dwam_symmetwic(const stwuct dwam_channew_info *ch0,
			const stwuct dwam_channew_info *ch1)
{
	wetuwn !memcmp(ch0, ch1, sizeof(*ch0)) &&
		(ch0->dimm_s.size == 0 ||
		 !memcmp(&ch0->dimm_w, &ch0->dimm_s, sizeof(ch0->dimm_w)));
}

static int
skw_dwam_get_channews_info(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwam_info *dwam_info = &i915->dwam_info;
	stwuct dwam_channew_info ch0 = {}, ch1 = {};
	u32 vaw;
	int wet;

	vaw = intew_uncowe_wead(&i915->uncowe,
				SKW_MAD_DIMM_CH0_0_0_0_MCHBAW_MCMAIN);
	wet = skw_dwam_get_channew_info(i915, &ch0, 0, vaw);
	if (wet == 0)
		dwam_info->num_channews++;

	vaw = intew_uncowe_wead(&i915->uncowe,
				SKW_MAD_DIMM_CH1_0_0_0_MCHBAW_MCMAIN);
	wet = skw_dwam_get_channew_info(i915, &ch1, 1, vaw);
	if (wet == 0)
		dwam_info->num_channews++;

	if (dwam_info->num_channews == 0) {
		dwm_info(&i915->dwm, "Numbew of memowy channews is zewo\n");
		wetuwn -EINVAW;
	}

	if (ch0.wanks == 0 && ch1.wanks == 0) {
		dwm_info(&i915->dwm, "couwdn't get memowy wank infowmation\n");
		wetuwn -EINVAW;
	}

	dwam_info->wm_wv_0_adjust_needed = ch0.is_16gb_dimm || ch1.is_16gb_dimm;

	dwam_info->symmetwic_memowy = intew_is_dwam_symmetwic(&ch0, &ch1);

	dwm_dbg_kms(&i915->dwm, "Memowy configuwation is symmetwic? %s\n",
		    stw_yes_no(dwam_info->symmetwic_memowy));

	wetuwn 0;
}

static enum intew_dwam_type
skw_get_dwam_type(stwuct dwm_i915_pwivate *i915)
{
	u32 vaw;

	vaw = intew_uncowe_wead(&i915->uncowe,
				SKW_MAD_INTEW_CHANNEW_0_0_0_MCHBAW_MCMAIN);

	switch (vaw & SKW_DWAM_DDW_TYPE_MASK) {
	case SKW_DWAM_DDW_TYPE_DDW3:
		wetuwn INTEW_DWAM_DDW3;
	case SKW_DWAM_DDW_TYPE_DDW4:
		wetuwn INTEW_DWAM_DDW4;
	case SKW_DWAM_DDW_TYPE_WPDDW3:
		wetuwn INTEW_DWAM_WPDDW3;
	case SKW_DWAM_DDW_TYPE_WPDDW4:
		wetuwn INTEW_DWAM_WPDDW4;
	defauwt:
		MISSING_CASE(vaw);
		wetuwn INTEW_DWAM_UNKNOWN;
	}
}

static int
skw_get_dwam_info(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwam_info *dwam_info = &i915->dwam_info;
	int wet;

	dwam_info->type = skw_get_dwam_type(i915);
	dwm_dbg_kms(&i915->dwm, "DWAM type: %s\n",
		    intew_dwam_type_stw(dwam_info->type));

	wet = skw_dwam_get_channews_info(i915);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/* Wetuwns Gb pew DWAM device */
static int bxt_get_dimm_size(u32 vaw)
{
	switch (vaw & BXT_DWAM_SIZE_MASK) {
	case BXT_DWAM_SIZE_4GBIT:
		wetuwn 4;
	case BXT_DWAM_SIZE_6GBIT:
		wetuwn 6;
	case BXT_DWAM_SIZE_8GBIT:
		wetuwn 8;
	case BXT_DWAM_SIZE_12GBIT:
		wetuwn 12;
	case BXT_DWAM_SIZE_16GBIT:
		wetuwn 16;
	defauwt:
		MISSING_CASE(vaw);
		wetuwn 0;
	}
}

static int bxt_get_dimm_width(u32 vaw)
{
	if (!bxt_get_dimm_size(vaw))
		wetuwn 0;

	vaw = (vaw & BXT_DWAM_WIDTH_MASK) >> BXT_DWAM_WIDTH_SHIFT;

	wetuwn 8 << vaw;
}

static int bxt_get_dimm_wanks(u32 vaw)
{
	if (!bxt_get_dimm_size(vaw))
		wetuwn 0;

	switch (vaw & BXT_DWAM_WANK_MASK) {
	case BXT_DWAM_WANK_SINGWE:
		wetuwn 1;
	case BXT_DWAM_WANK_DUAW:
		wetuwn 2;
	defauwt:
		MISSING_CASE(vaw);
		wetuwn 0;
	}
}

static enum intew_dwam_type bxt_get_dimm_type(u32 vaw)
{
	if (!bxt_get_dimm_size(vaw))
		wetuwn INTEW_DWAM_UNKNOWN;

	switch (vaw & BXT_DWAM_TYPE_MASK) {
	case BXT_DWAM_TYPE_DDW3:
		wetuwn INTEW_DWAM_DDW3;
	case BXT_DWAM_TYPE_WPDDW3:
		wetuwn INTEW_DWAM_WPDDW3;
	case BXT_DWAM_TYPE_DDW4:
		wetuwn INTEW_DWAM_DDW4;
	case BXT_DWAM_TYPE_WPDDW4:
		wetuwn INTEW_DWAM_WPDDW4;
	defauwt:
		MISSING_CASE(vaw);
		wetuwn INTEW_DWAM_UNKNOWN;
	}
}

static void bxt_get_dimm_info(stwuct dwam_dimm_info *dimm, u32 vaw)
{
	dimm->width = bxt_get_dimm_width(vaw);
	dimm->wanks = bxt_get_dimm_wanks(vaw);

	/*
	 * Size in wegistew is Gb pew DWAM device. Convewt to totaw
	 * Gb to match the way we wepowt this fow non-WP pwatfowms.
	 */
	dimm->size = bxt_get_dimm_size(vaw) * intew_dimm_num_devices(dimm);
}

static int bxt_get_dwam_info(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwam_info *dwam_info = &i915->dwam_info;
	u32 vaw;
	u8 vawid_wanks = 0;
	int i;

	/*
	 * Now wead each DUNIT8/9/10/11 to check the wank of each dimms.
	 */
	fow (i = BXT_D_CW_DWP0_DUNIT_STAWT; i <= BXT_D_CW_DWP0_DUNIT_END; i++) {
		stwuct dwam_dimm_info dimm;
		enum intew_dwam_type type;

		vaw = intew_uncowe_wead(&i915->uncowe, BXT_D_CW_DWP0_DUNIT(i));
		if (vaw == 0xFFFFFFFF)
			continue;

		dwam_info->num_channews++;

		bxt_get_dimm_info(&dimm, vaw);
		type = bxt_get_dimm_type(vaw);

		dwm_WAWN_ON(&i915->dwm, type != INTEW_DWAM_UNKNOWN &&
			    dwam_info->type != INTEW_DWAM_UNKNOWN &&
			    dwam_info->type != type);

		dwm_dbg_kms(&i915->dwm,
			    "CH%u DIMM size: %u Gb, width: X%u, wanks: %u, type: %s\n",
			    i - BXT_D_CW_DWP0_DUNIT_STAWT,
			    dimm.size, dimm.width, dimm.wanks,
			    intew_dwam_type_stw(type));

		if (vawid_wanks == 0)
			vawid_wanks = dimm.wanks;

		if (type != INTEW_DWAM_UNKNOWN)
			dwam_info->type = type;
	}

	if (dwam_info->type == INTEW_DWAM_UNKNOWN || vawid_wanks == 0) {
		dwm_info(&i915->dwm, "couwdn't get memowy infowmation\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int icw_pcode_wead_mem_gwobaw_info(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct dwam_info *dwam_info = &dev_pwiv->dwam_info;
	u32 vaw = 0;
	int wet;

	wet = snb_pcode_wead(&dev_pwiv->uncowe, ICW_PCODE_MEM_SUBSYSYSTEM_INFO |
			     ICW_PCODE_MEM_SS_WEAD_GWOBAW_INFO, &vaw, NUWW);
	if (wet)
		wetuwn wet;

	if (GWAPHICS_VEW(dev_pwiv) == 12) {
		switch (vaw & 0xf) {
		case 0:
			dwam_info->type = INTEW_DWAM_DDW4;
			bweak;
		case 1:
			dwam_info->type = INTEW_DWAM_DDW5;
			bweak;
		case 2:
			dwam_info->type = INTEW_DWAM_WPDDW5;
			bweak;
		case 3:
			dwam_info->type = INTEW_DWAM_WPDDW4;
			bweak;
		case 4:
			dwam_info->type = INTEW_DWAM_DDW3;
			bweak;
		case 5:
			dwam_info->type = INTEW_DWAM_WPDDW3;
			bweak;
		defauwt:
			MISSING_CASE(vaw & 0xf);
			wetuwn -EINVAW;
		}
	} ewse {
		switch (vaw & 0xf) {
		case 0:
			dwam_info->type = INTEW_DWAM_DDW4;
			bweak;
		case 1:
			dwam_info->type = INTEW_DWAM_DDW3;
			bweak;
		case 2:
			dwam_info->type = INTEW_DWAM_WPDDW3;
			bweak;
		case 3:
			dwam_info->type = INTEW_DWAM_WPDDW4;
			bweak;
		defauwt:
			MISSING_CASE(vaw & 0xf);
			wetuwn -EINVAW;
		}
	}

	dwam_info->num_channews = (vaw & 0xf0) >> 4;
	dwam_info->num_qgv_points = (vaw & 0xf00) >> 8;
	dwam_info->num_psf_gv_points = (vaw & 0x3000) >> 12;

	wetuwn 0;
}

static int gen11_get_dwam_info(stwuct dwm_i915_pwivate *i915)
{
	int wet = skw_get_dwam_info(i915);

	if (wet)
		wetuwn wet;

	wetuwn icw_pcode_wead_mem_gwobaw_info(i915);
}

static int gen12_get_dwam_info(stwuct dwm_i915_pwivate *i915)
{
	i915->dwam_info.wm_wv_0_adjust_needed = fawse;

	wetuwn icw_pcode_wead_mem_gwobaw_info(i915);
}

static int xewpdp_get_dwam_info(stwuct dwm_i915_pwivate *i915)
{
	u32 vaw = intew_uncowe_wead(&i915->uncowe, MTW_MEM_SS_INFO_GWOBAW);
	stwuct dwam_info *dwam_info = &i915->dwam_info;

	switch (WEG_FIEWD_GET(MTW_DDW_TYPE_MASK, vaw)) {
	case 0:
		dwam_info->type = INTEW_DWAM_DDW4;
		bweak;
	case 1:
		dwam_info->type = INTEW_DWAM_DDW5;
		bweak;
	case 2:
		dwam_info->type = INTEW_DWAM_WPDDW5;
		bweak;
	case 3:
		dwam_info->type = INTEW_DWAM_WPDDW4;
		bweak;
	case 4:
		dwam_info->type = INTEW_DWAM_DDW3;
		bweak;
	case 5:
		dwam_info->type = INTEW_DWAM_WPDDW3;
		bweak;
	defauwt:
		MISSING_CASE(vaw);
		wetuwn -EINVAW;
	}

	dwam_info->num_channews = WEG_FIEWD_GET(MTW_N_OF_POPUWATED_CH_MASK, vaw);
	dwam_info->num_qgv_points = WEG_FIEWD_GET(MTW_N_OF_ENABWED_QGV_POINTS_MASK, vaw);
	/* PSF GV points not suppowted in D14+ */

	wetuwn 0;
}

void intew_dwam_detect(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwam_info *dwam_info = &i915->dwam_info;
	int wet;

	detect_mem_fweq(i915);

	if (GWAPHICS_VEW(i915) < 9 || IS_DG2(i915) || !HAS_DISPWAY(i915))
		wetuwn;

	/*
	 * Assume wevew 0 watewmawk watency adjustment is needed untiw pwoven
	 * othewwise, this w/a is not needed by bxt/gwk.
	 */
	dwam_info->wm_wv_0_adjust_needed = !IS_GEN9_WP(i915);

	if (DISPWAY_VEW(i915) >= 14)
		wet = xewpdp_get_dwam_info(i915);
	ewse if (GWAPHICS_VEW(i915) >= 12)
		wet = gen12_get_dwam_info(i915);
	ewse if (GWAPHICS_VEW(i915) >= 11)
		wet = gen11_get_dwam_info(i915);
	ewse if (IS_GEN9_WP(i915))
		wet = bxt_get_dwam_info(i915);
	ewse
		wet = skw_get_dwam_info(i915);
	if (wet)
		wetuwn;

	dwm_dbg_kms(&i915->dwm, "DWAM channews: %u\n", dwam_info->num_channews);

	dwm_dbg_kms(&i915->dwm, "Watewmawk wevew 0 adjustment needed: %s\n",
		    stw_yes_no(dwam_info->wm_wv_0_adjust_needed));
}

static u32 gen9_edwam_size_mb(stwuct dwm_i915_pwivate *i915, u32 cap)
{
	static const u8 ways[8] = { 4, 8, 12, 16, 16, 16, 16, 16 };
	static const u8 sets[4] = { 1, 1, 2, 2 };

	wetuwn EDWAM_NUM_BANKS(cap) *
		ways[EDWAM_WAYS_IDX(cap)] *
		sets[EDWAM_SETS_IDX(cap)];
}

void intew_dwam_edwam_detect(stwuct dwm_i915_pwivate *i915)
{
	u32 edwam_cap = 0;

	if (!(IS_HASWEWW(i915) || IS_BWOADWEWW(i915) || GWAPHICS_VEW(i915) >= 9))
		wetuwn;

	edwam_cap = intew_uncowe_wead_fw(&i915->uncowe, HSW_EDWAM_CAP);

	/* NB: We can't wwite IDICW yet because we don't have gt funcs set up */

	if (!(edwam_cap & EDWAM_ENABWED))
		wetuwn;

	/*
	 * The needed capabiwity bits fow size cawcuwation awe not thewe with
	 * pwe gen9 so wetuwn 128MB awways.
	 */
	if (GWAPHICS_VEW(i915) < 9)
		i915->edwam_size_mb = 128;
	ewse
		i915->edwam_size_mb = gen9_edwam_size_mb(i915, edwam_cap);

	dwm_info(&i915->dwm, "Found %uMB of eDWAM\n", i915->edwam_size_mb);
}
