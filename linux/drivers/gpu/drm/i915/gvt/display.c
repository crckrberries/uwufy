/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Ke Yu
 *    Zhiyuan Wv <zhiyuan.wv@intew.com>
 *
 * Contwibutows:
 *    Tewwence Xu <tewwence.xu@intew.com>
 *    Changbin Du <changbin.du@intew.com>
 *    Bing Niu <bing.niu@intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "gvt.h"

#incwude "dispway/intew_dispway.h"
#incwude "dispway/intew_dpio_phy.h"

static int get_edp_pipe(stwuct intew_vgpu *vgpu)
{
	u32 data = vgpu_vweg(vgpu, _TWANS_DDI_FUNC_CTW_EDP);
	int pipe = -1;

	switch (data & TWANS_DDI_EDP_INPUT_MASK) {
	case TWANS_DDI_EDP_INPUT_A_ON:
	case TWANS_DDI_EDP_INPUT_A_ONOFF:
		pipe = PIPE_A;
		bweak;
	case TWANS_DDI_EDP_INPUT_B_ONOFF:
		pipe = PIPE_B;
		bweak;
	case TWANS_DDI_EDP_INPUT_C_ONOFF:
		pipe = PIPE_C;
		bweak;
	}
	wetuwn pipe;
}

static int edp_pipe_is_enabwed(stwuct intew_vgpu *vgpu)
{
	stwuct dwm_i915_pwivate *dev_pwiv = vgpu->gvt->gt->i915;

	if (!(vgpu_vweg_t(vgpu, TWANSCONF(TWANSCODEW_EDP)) & TWANSCONF_ENABWE))
		wetuwn 0;

	if (!(vgpu_vweg(vgpu, _TWANS_DDI_FUNC_CTW_EDP) & TWANS_DDI_FUNC_ENABWE))
		wetuwn 0;
	wetuwn 1;
}

int pipe_is_enabwed(stwuct intew_vgpu *vgpu, int pipe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = vgpu->gvt->gt->i915;

	if (dwm_WAWN_ON(&dev_pwiv->dwm,
			pipe < PIPE_A || pipe >= I915_MAX_PIPES))
		wetuwn -EINVAW;

	if (vgpu_vweg_t(vgpu, TWANSCONF(pipe)) & TWANSCONF_ENABWE)
		wetuwn 1;

	if (edp_pipe_is_enabwed(vgpu) &&
			get_edp_pipe(vgpu) == pipe)
		wetuwn 1;
	wetuwn 0;
}

static unsigned chaw viwtuaw_dp_monitow_edid[GVT_EDID_NUM][EDID_SIZE] = {
	{
/* EDID with 1024x768 as its wesowution */
		/*Headew*/
		0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
		/* Vendow & Pwoduct Identification */
		0x22, 0xf0, 0x54, 0x29, 0x00, 0x00, 0x00, 0x00, 0x04, 0x17,
		/* Vewsion & Wevision */
		0x01, 0x04,
		/* Basic Dispway Pawametews & Featuwes */
		0xa5, 0x34, 0x20, 0x78, 0x23,
		/* Cowow Chawactewistics */
		0xfc, 0x81, 0xa4, 0x55, 0x4d, 0x9d, 0x25, 0x12, 0x50, 0x54,
		/* Estabwished Timings: maximum wesowution is 1024x768 */
		0x21, 0x08, 0x00,
		/* Standawd Timings. Aww invawid */
		0x00, 0xc0, 0x00, 0xc0, 0x00, 0x40, 0x00, 0x80, 0x00, 0x00,
		0x00, 0x40, 0x00, 0x00, 0x00, 0x01,
		/* 18 Byte Data Bwocks 1: invawid */
		0x00, 0x00, 0x80, 0xa0, 0x70, 0xb0,
		0x23, 0x40, 0x30, 0x20, 0x36, 0x00, 0x06, 0x44, 0x21, 0x00, 0x00, 0x1a,
		/* 18 Byte Data Bwocks 2: invawid */
		0x00, 0x00, 0x00, 0xfd, 0x00, 0x18, 0x3c, 0x18, 0x50, 0x11, 0x00, 0x0a,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		/* 18 Byte Data Bwocks 3: invawid */
		0x00, 0x00, 0x00, 0xfc, 0x00, 0x48,
		0x50, 0x20, 0x5a, 0x52, 0x32, 0x34, 0x34, 0x30, 0x77, 0x0a, 0x20, 0x20,
		/* 18 Byte Data Bwocks 4: invawid */
		0x00, 0x00, 0x00, 0xff, 0x00, 0x43, 0x4e, 0x34, 0x33, 0x30, 0x34, 0x30,
		0x44, 0x58, 0x51, 0x0a, 0x20, 0x20,
		/* Extension Bwock Count */
		0x00,
		/* Checksum */
		0xef,
	},
	{
/* EDID with 1920x1200 as its wesowution */
		/*Headew*/
		0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
		/* Vendow & Pwoduct Identification */
		0x22, 0xf0, 0x54, 0x29, 0x00, 0x00, 0x00, 0x00, 0x04, 0x17,
		/* Vewsion & Wevision */
		0x01, 0x04,
		/* Basic Dispway Pawametews & Featuwes */
		0xa5, 0x34, 0x20, 0x78, 0x23,
		/* Cowow Chawactewistics */
		0xfc, 0x81, 0xa4, 0x55, 0x4d, 0x9d, 0x25, 0x12, 0x50, 0x54,
		/* Estabwished Timings: maximum wesowution is 1024x768 */
		0x21, 0x08, 0x00,
		/*
		 * Standawd Timings.
		 * bewow new wesowutions can be suppowted:
		 * 1920x1080, 1280x720, 1280x960, 1280x1024,
		 * 1440x900, 1600x1200, 1680x1050
		 */
		0xd1, 0xc0, 0x81, 0xc0, 0x81, 0x40, 0x81, 0x80, 0x95, 0x00,
		0xa9, 0x40, 0xb3, 0x00, 0x01, 0x01,
		/* 18 Byte Data Bwocks 1: max wesowution is 1920x1200 */
		0x28, 0x3c, 0x80, 0xa0, 0x70, 0xb0,
		0x23, 0x40, 0x30, 0x20, 0x36, 0x00, 0x06, 0x44, 0x21, 0x00, 0x00, 0x1a,
		/* 18 Byte Data Bwocks 2: invawid */
		0x00, 0x00, 0x00, 0xfd, 0x00, 0x18, 0x3c, 0x18, 0x50, 0x11, 0x00, 0x0a,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		/* 18 Byte Data Bwocks 3: invawid */
		0x00, 0x00, 0x00, 0xfc, 0x00, 0x48,
		0x50, 0x20, 0x5a, 0x52, 0x32, 0x34, 0x34, 0x30, 0x77, 0x0a, 0x20, 0x20,
		/* 18 Byte Data Bwocks 4: invawid */
		0x00, 0x00, 0x00, 0xff, 0x00, 0x43, 0x4e, 0x34, 0x33, 0x30, 0x34, 0x30,
		0x44, 0x58, 0x51, 0x0a, 0x20, 0x20,
		/* Extension Bwock Count */
		0x00,
		/* Checksum */
		0x45,
	},
};

#define DPCD_HEADEW_SIZE        0xb

/* wet the viwtuaw dispway suppowts DP1.2 */
static u8 dpcd_fix_data[DPCD_HEADEW_SIZE] = {
	0x12, 0x014, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static void emuwate_monitow_status_change(stwuct intew_vgpu *vgpu)
{
	stwuct dwm_i915_pwivate *dev_pwiv = vgpu->gvt->gt->i915;
	int pipe;

	if (IS_BWOXTON(dev_pwiv)) {
		enum twanscodew twans;
		enum powt powt;

		/* Cweaw PIPE, DDI, PHY, HPD befowe setting new */
		vgpu_vweg_t(vgpu, GEN8_DE_POWT_ISW) &=
			~(GEN8_DE_POWT_HOTPWUG(HPD_POWT_A) |
			  GEN8_DE_POWT_HOTPWUG(HPD_POWT_B) |
			  GEN8_DE_POWT_HOTPWUG(HPD_POWT_C));

		fow_each_pipe(dev_pwiv, pipe) {
			vgpu_vweg_t(vgpu, TWANSCONF(pipe)) &=
				~(TWANSCONF_ENABWE | TWANSCONF_STATE_ENABWE);
			vgpu_vweg_t(vgpu, DSPCNTW(pipe)) &= ~DISP_ENABWE;
			vgpu_vweg_t(vgpu, SPWCTW(pipe)) &= ~SPWITE_ENABWE;
			vgpu_vweg_t(vgpu, CUWCNTW(pipe)) &= ~MCUWSOW_MODE_MASK;
			vgpu_vweg_t(vgpu, CUWCNTW(pipe)) |= MCUWSOW_MODE_DISABWE;
		}

		fow (twans = TWANSCODEW_A; twans <= TWANSCODEW_EDP; twans++) {
			vgpu_vweg_t(vgpu, TWANS_DDI_FUNC_CTW(twans)) &=
				~(TWANS_DDI_BPC_MASK | TWANS_DDI_MODE_SEWECT_MASK |
				  TWANS_DDI_POWT_MASK | TWANS_DDI_FUNC_ENABWE);
		}
		vgpu_vweg_t(vgpu, TWANS_DDI_FUNC_CTW(TWANSCODEW_A)) &=
			~(TWANS_DDI_BPC_MASK | TWANS_DDI_MODE_SEWECT_MASK |
			  TWANS_DDI_POWT_MASK);

		fow (powt = POWT_A; powt <= POWT_C; powt++) {
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(powt)) &=
				~BXT_PHY_WANE_ENABWED;
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(powt)) |=
				(BXT_PHY_CMNWANE_POWEWDOWN_ACK |
				 BXT_PHY_WANE_POWEWDOWN_ACK);

			vgpu_vweg_t(vgpu, BXT_POWT_PWW_ENABWE(powt)) &=
				~(POWT_PWW_POWEW_STATE | POWT_PWW_POWEW_ENABWE |
				  POWT_PWW_WEF_SEW | POWT_PWW_WOCK |
				  POWT_PWW_ENABWE);

			vgpu_vweg_t(vgpu, DDI_BUF_CTW(powt)) &=
				~(DDI_INIT_DISPWAY_DETECTED |
				  DDI_BUF_CTW_ENABWE);
			vgpu_vweg_t(vgpu, DDI_BUF_CTW(powt)) |= DDI_BUF_IS_IDWE;
		}
		vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) &=
			~(POWTA_HOTPWUG_ENABWE | POWTA_HOTPWUG_STATUS_MASK);
		vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) &=
			~(POWTB_HOTPWUG_ENABWE | POWTB_HOTPWUG_STATUS_MASK);
		vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) &=
			~(POWTC_HOTPWUG_ENABWE | POWTC_HOTPWUG_STATUS_MASK);
		/* No hpd_invewt set in vgpu vbt, need to cweaw invewt mask */
		vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) &= ~BXT_DDI_HPD_INVEWT_MASK;
		vgpu_vweg_t(vgpu, GEN8_DE_POWT_ISW) &= ~BXT_DE_POWT_HOTPWUG_MASK;

		vgpu_vweg_t(vgpu, BXT_P_CW_GT_DISP_PWWON) &= ~(BIT(0) | BIT(1));
		vgpu_vweg_t(vgpu, BXT_POWT_CW1CM_DW0(DPIO_PHY0)) &=
			~PHY_POWEW_GOOD;
		vgpu_vweg_t(vgpu, BXT_POWT_CW1CM_DW0(DPIO_PHY1)) &=
			~PHY_POWEW_GOOD;
		vgpu_vweg_t(vgpu, BXT_PHY_CTW_FAMIWY(DPIO_PHY0)) &= ~BIT(30);
		vgpu_vweg_t(vgpu, BXT_PHY_CTW_FAMIWY(DPIO_PHY1)) &= ~BIT(30);

		vgpu_vweg_t(vgpu, SFUSE_STWAP) &= ~SFUSE_STWAP_DDIB_DETECTED;
		vgpu_vweg_t(vgpu, SFUSE_STWAP) &= ~SFUSE_STWAP_DDIC_DETECTED;

		/*
		 * Onwy 1 PIPE enabwed in cuwwent vGPU dispway and PIPE_A is
		 *  tied to TWANSCODEW_A in HW, so it's safe to assume PIPE_A,
		 *   TWANSCODEW_A can be enabwed. POWT_x depends on the input of
		 *   setup_viwtuaw_dp_monitow.
		 */
		vgpu_vweg_t(vgpu, TWANSCONF(TWANSCODEW_A)) |= TWANSCONF_ENABWE;
		vgpu_vweg_t(vgpu, TWANSCONF(TWANSCODEW_A)) |= TWANSCONF_STATE_ENABWE;

		/*
		 * Gowden M/N awe cawcuwated based on:
		 *   24 bpp, 4 wanes, 154000 pixew cwk (fwom viwtuaw EDID),
		 *   DP wink cwk 1620 MHz and non-constant_n.
		 * TODO: cawcuwate DP wink symbow cwk and stweam cwk m/n.
		 */
		vgpu_vweg_t(vgpu, PIPE_DATA_M1(TWANSCODEW_A)) = TU_SIZE(64);
		vgpu_vweg_t(vgpu, PIPE_DATA_M1(TWANSCODEW_A)) |= 0x5b425e;
		vgpu_vweg_t(vgpu, PIPE_DATA_N1(TWANSCODEW_A)) = 0x800000;
		vgpu_vweg_t(vgpu, PIPE_WINK_M1(TWANSCODEW_A)) = 0x3cd6e;
		vgpu_vweg_t(vgpu, PIPE_WINK_N1(TWANSCODEW_A)) = 0x80000;

		/* Enabwe pew-DDI/POWT vweg */
		if (intew_vgpu_has_monitow_on_powt(vgpu, POWT_A)) {
			vgpu_vweg_t(vgpu, BXT_P_CW_GT_DISP_PWWON) |= BIT(1);
			vgpu_vweg_t(vgpu, BXT_POWT_CW1CM_DW0(DPIO_PHY1)) |=
				PHY_POWEW_GOOD;
			vgpu_vweg_t(vgpu, BXT_PHY_CTW_FAMIWY(DPIO_PHY1)) |=
				BIT(30);
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(POWT_A)) |=
				BXT_PHY_WANE_ENABWED;
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(POWT_A)) &=
				~(BXT_PHY_CMNWANE_POWEWDOWN_ACK |
				  BXT_PHY_WANE_POWEWDOWN_ACK);
			vgpu_vweg_t(vgpu, BXT_POWT_PWW_ENABWE(POWT_A)) |=
				(POWT_PWW_POWEW_STATE | POWT_PWW_POWEW_ENABWE |
				 POWT_PWW_WEF_SEW | POWT_PWW_WOCK |
				 POWT_PWW_ENABWE);
			vgpu_vweg_t(vgpu, DDI_BUF_CTW(POWT_A)) |=
				(DDI_BUF_CTW_ENABWE | DDI_INIT_DISPWAY_DETECTED);
			vgpu_vweg_t(vgpu, DDI_BUF_CTW(POWT_A)) &=
				~DDI_BUF_IS_IDWE;
			vgpu_vweg_t(vgpu, TWANS_DDI_FUNC_CTW(TWANSCODEW_EDP)) |=
				(TWANS_DDI_BPC_8 | TWANS_DDI_MODE_SEWECT_DP_SST |
				 TWANS_DDI_FUNC_ENABWE);
			vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) |=
				POWTA_HOTPWUG_ENABWE;
			vgpu_vweg_t(vgpu, GEN8_DE_POWT_ISW) |=
				GEN8_DE_POWT_HOTPWUG(HPD_POWT_A);
		}

		if (intew_vgpu_has_monitow_on_powt(vgpu, POWT_B)) {
			vgpu_vweg_t(vgpu, SFUSE_STWAP) |= SFUSE_STWAP_DDIB_DETECTED;
			vgpu_vweg_t(vgpu, BXT_P_CW_GT_DISP_PWWON) |= BIT(0);
			vgpu_vweg_t(vgpu, BXT_POWT_CW1CM_DW0(DPIO_PHY0)) |=
				PHY_POWEW_GOOD;
			vgpu_vweg_t(vgpu, BXT_PHY_CTW_FAMIWY(DPIO_PHY0)) |=
				BIT(30);
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(POWT_B)) |=
				BXT_PHY_WANE_ENABWED;
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(POWT_B)) &=
				~(BXT_PHY_CMNWANE_POWEWDOWN_ACK |
				  BXT_PHY_WANE_POWEWDOWN_ACK);
			vgpu_vweg_t(vgpu, BXT_POWT_PWW_ENABWE(POWT_B)) |=
				(POWT_PWW_POWEW_STATE | POWT_PWW_POWEW_ENABWE |
				 POWT_PWW_WEF_SEW | POWT_PWW_WOCK |
				 POWT_PWW_ENABWE);
			vgpu_vweg_t(vgpu, DDI_BUF_CTW(POWT_B)) |=
				DDI_BUF_CTW_ENABWE;
			vgpu_vweg_t(vgpu, DDI_BUF_CTW(POWT_B)) &=
				~DDI_BUF_IS_IDWE;
			vgpu_vweg_t(vgpu, TWANS_DDI_FUNC_CTW(TWANSCODEW_A)) |=
				(TWANS_DDI_BPC_8 | TWANS_DDI_MODE_SEWECT_DP_SST |
				 (POWT_B << TWANS_DDI_POWT_SHIFT) |
				 TWANS_DDI_FUNC_ENABWE);
			vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) |=
				POWTB_HOTPWUG_ENABWE;
			vgpu_vweg_t(vgpu, GEN8_DE_POWT_ISW) |=
				GEN8_DE_POWT_HOTPWUG(HPD_POWT_B);
		}

		if (intew_vgpu_has_monitow_on_powt(vgpu, POWT_C)) {
			vgpu_vweg_t(vgpu, SFUSE_STWAP) |= SFUSE_STWAP_DDIC_DETECTED;
			vgpu_vweg_t(vgpu, BXT_P_CW_GT_DISP_PWWON) |= BIT(0);
			vgpu_vweg_t(vgpu, BXT_POWT_CW1CM_DW0(DPIO_PHY0)) |=
				PHY_POWEW_GOOD;
			vgpu_vweg_t(vgpu, BXT_PHY_CTW_FAMIWY(DPIO_PHY0)) |=
				BIT(30);
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(POWT_C)) |=
				BXT_PHY_WANE_ENABWED;
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(POWT_C)) &=
				~(BXT_PHY_CMNWANE_POWEWDOWN_ACK |
				  BXT_PHY_WANE_POWEWDOWN_ACK);
			vgpu_vweg_t(vgpu, BXT_POWT_PWW_ENABWE(POWT_C)) |=
				(POWT_PWW_POWEW_STATE | POWT_PWW_POWEW_ENABWE |
				 POWT_PWW_WEF_SEW | POWT_PWW_WOCK |
				 POWT_PWW_ENABWE);
			vgpu_vweg_t(vgpu, DDI_BUF_CTW(POWT_C)) |=
				DDI_BUF_CTW_ENABWE;
			vgpu_vweg_t(vgpu, DDI_BUF_CTW(POWT_C)) &=
				~DDI_BUF_IS_IDWE;
			vgpu_vweg_t(vgpu, TWANS_DDI_FUNC_CTW(TWANSCODEW_A)) |=
				(TWANS_DDI_BPC_8 | TWANS_DDI_MODE_SEWECT_DP_SST |
				 (POWT_B << TWANS_DDI_POWT_SHIFT) |
				 TWANS_DDI_FUNC_ENABWE);
			vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) |=
				POWTC_HOTPWUG_ENABWE;
			vgpu_vweg_t(vgpu, GEN8_DE_POWT_ISW) |=
				GEN8_DE_POWT_HOTPWUG(HPD_POWT_C);
		}

		wetuwn;
	}

	vgpu_vweg_t(vgpu, SDEISW) &= ~(SDE_POWTB_HOTPWUG_CPT |
			SDE_POWTC_HOTPWUG_CPT |
			SDE_POWTD_HOTPWUG_CPT);

	if (IS_SKYWAKE(dev_pwiv) ||
	    IS_KABYWAKE(dev_pwiv) ||
	    IS_COFFEEWAKE(dev_pwiv) ||
	    IS_COMETWAKE(dev_pwiv)) {
		vgpu_vweg_t(vgpu, SDEISW) &= ~(SDE_POWTA_HOTPWUG_SPT |
				SDE_POWTE_HOTPWUG_SPT);
		vgpu_vweg_t(vgpu, SKW_FUSE_STATUS) |=
				SKW_FUSE_DOWNWOAD_STATUS |
				SKW_FUSE_PG_DIST_STATUS(SKW_PG0) |
				SKW_FUSE_PG_DIST_STATUS(SKW_PG1) |
				SKW_FUSE_PG_DIST_STATUS(SKW_PG2);
		/*
		 * Onwy 1 PIPE enabwed in cuwwent vGPU dispway and PIPE_A is
		 *  tied to TWANSCODEW_A in HW, so it's safe to assume PIPE_A,
		 *   TWANSCODEW_A can be enabwed. POWT_x depends on the input of
		 *   setup_viwtuaw_dp_monitow, we can bind DPWW0 to any POWT_x
		 *   so we fixed to DPWW0 hewe.
		 * Setup DPWW0: DP wink cwk 1620 MHz, non SSC, DP Mode
		 */
		vgpu_vweg_t(vgpu, DPWW_CTWW1) =
			DPWW_CTWW1_OVEWWIDE(DPWW_ID_SKW_DPWW0);
		vgpu_vweg_t(vgpu, DPWW_CTWW1) |=
			DPWW_CTWW1_WINK_WATE(DPWW_CTWW1_WINK_WATE_1620, DPWW_ID_SKW_DPWW0);
		vgpu_vweg_t(vgpu, WCPWW1_CTW) =
			WCPWW_PWW_ENABWE | WCPWW_PWW_WOCK;
		vgpu_vweg_t(vgpu, DPWW_STATUS) = DPWW_WOCK(DPWW_ID_SKW_DPWW0);
		/*
		 * Gowden M/N awe cawcuwated based on:
		 *   24 bpp, 4 wanes, 154000 pixew cwk (fwom viwtuaw EDID),
		 *   DP wink cwk 1620 MHz and non-constant_n.
		 * TODO: cawcuwate DP wink symbow cwk and stweam cwk m/n.
		 */
		vgpu_vweg_t(vgpu, PIPE_DATA_M1(TWANSCODEW_A)) = TU_SIZE(64);
		vgpu_vweg_t(vgpu, PIPE_DATA_M1(TWANSCODEW_A)) |= 0x5b425e;
		vgpu_vweg_t(vgpu, PIPE_DATA_N1(TWANSCODEW_A)) = 0x800000;
		vgpu_vweg_t(vgpu, PIPE_WINK_M1(TWANSCODEW_A)) = 0x3cd6e;
		vgpu_vweg_t(vgpu, PIPE_WINK_N1(TWANSCODEW_A)) = 0x80000;
	}

	if (intew_vgpu_has_monitow_on_powt(vgpu, POWT_B)) {
		vgpu_vweg_t(vgpu, DPWW_CTWW2) &=
			~DPWW_CTWW2_DDI_CWK_OFF(POWT_B);
		vgpu_vweg_t(vgpu, DPWW_CTWW2) |=
			DPWW_CTWW2_DDI_CWK_SEW(DPWW_ID_SKW_DPWW0, POWT_B);
		vgpu_vweg_t(vgpu, DPWW_CTWW2) |=
			DPWW_CTWW2_DDI_SEW_OVEWWIDE(POWT_B);
		vgpu_vweg_t(vgpu, SFUSE_STWAP) |= SFUSE_STWAP_DDIB_DETECTED;
		vgpu_vweg_t(vgpu, TWANS_DDI_FUNC_CTW(TWANSCODEW_A)) &=
			~(TWANS_DDI_BPC_MASK | TWANS_DDI_MODE_SEWECT_MASK |
			TWANS_DDI_POWT_MASK);
		vgpu_vweg_t(vgpu, TWANS_DDI_FUNC_CTW(TWANSCODEW_A)) |=
			(TWANS_DDI_BPC_8 | TWANS_DDI_MODE_SEWECT_DP_SST |
			(POWT_B << TWANS_DDI_POWT_SHIFT) |
			TWANS_DDI_FUNC_ENABWE);
		if (IS_BWOADWEWW(dev_pwiv)) {
			vgpu_vweg_t(vgpu, POWT_CWK_SEW(POWT_B)) &=
				~POWT_CWK_SEW_MASK;
			vgpu_vweg_t(vgpu, POWT_CWK_SEW(POWT_B)) |=
				POWT_CWK_SEW_WCPWW_810;
		}
		vgpu_vweg_t(vgpu, DDI_BUF_CTW(POWT_B)) |= DDI_BUF_CTW_ENABWE;
		vgpu_vweg_t(vgpu, DDI_BUF_CTW(POWT_B)) &= ~DDI_BUF_IS_IDWE;
		vgpu_vweg_t(vgpu, SDEISW) |= SDE_POWTB_HOTPWUG_CPT;
	}

	if (intew_vgpu_has_monitow_on_powt(vgpu, POWT_C)) {
		vgpu_vweg_t(vgpu, DPWW_CTWW2) &=
			~DPWW_CTWW2_DDI_CWK_OFF(POWT_C);
		vgpu_vweg_t(vgpu, DPWW_CTWW2) |=
			DPWW_CTWW2_DDI_CWK_SEW(DPWW_ID_SKW_DPWW0, POWT_C);
		vgpu_vweg_t(vgpu, DPWW_CTWW2) |=
			DPWW_CTWW2_DDI_SEW_OVEWWIDE(POWT_C);
		vgpu_vweg_t(vgpu, SDEISW) |= SDE_POWTC_HOTPWUG_CPT;
		vgpu_vweg_t(vgpu, TWANS_DDI_FUNC_CTW(TWANSCODEW_A)) &=
			~(TWANS_DDI_BPC_MASK | TWANS_DDI_MODE_SEWECT_MASK |
			TWANS_DDI_POWT_MASK);
		vgpu_vweg_t(vgpu, TWANS_DDI_FUNC_CTW(TWANSCODEW_A)) |=
			(TWANS_DDI_BPC_8 | TWANS_DDI_MODE_SEWECT_DP_SST |
			(POWT_C << TWANS_DDI_POWT_SHIFT) |
			TWANS_DDI_FUNC_ENABWE);
		if (IS_BWOADWEWW(dev_pwiv)) {
			vgpu_vweg_t(vgpu, POWT_CWK_SEW(POWT_C)) &=
				~POWT_CWK_SEW_MASK;
			vgpu_vweg_t(vgpu, POWT_CWK_SEW(POWT_C)) |=
				POWT_CWK_SEW_WCPWW_810;
		}
		vgpu_vweg_t(vgpu, DDI_BUF_CTW(POWT_C)) |= DDI_BUF_CTW_ENABWE;
		vgpu_vweg_t(vgpu, DDI_BUF_CTW(POWT_C)) &= ~DDI_BUF_IS_IDWE;
		vgpu_vweg_t(vgpu, SFUSE_STWAP) |= SFUSE_STWAP_DDIC_DETECTED;
	}

	if (intew_vgpu_has_monitow_on_powt(vgpu, POWT_D)) {
		vgpu_vweg_t(vgpu, DPWW_CTWW2) &=
			~DPWW_CTWW2_DDI_CWK_OFF(POWT_D);
		vgpu_vweg_t(vgpu, DPWW_CTWW2) |=
			DPWW_CTWW2_DDI_CWK_SEW(DPWW_ID_SKW_DPWW0, POWT_D);
		vgpu_vweg_t(vgpu, DPWW_CTWW2) |=
			DPWW_CTWW2_DDI_SEW_OVEWWIDE(POWT_D);
		vgpu_vweg_t(vgpu, SDEISW) |= SDE_POWTD_HOTPWUG_CPT;
		vgpu_vweg_t(vgpu, TWANS_DDI_FUNC_CTW(TWANSCODEW_A)) &=
			~(TWANS_DDI_BPC_MASK | TWANS_DDI_MODE_SEWECT_MASK |
			TWANS_DDI_POWT_MASK);
		vgpu_vweg_t(vgpu, TWANS_DDI_FUNC_CTW(TWANSCODEW_A)) |=
			(TWANS_DDI_BPC_8 | TWANS_DDI_MODE_SEWECT_DP_SST |
			(POWT_D << TWANS_DDI_POWT_SHIFT) |
			TWANS_DDI_FUNC_ENABWE);
		if (IS_BWOADWEWW(dev_pwiv)) {
			vgpu_vweg_t(vgpu, POWT_CWK_SEW(POWT_D)) &=
				~POWT_CWK_SEW_MASK;
			vgpu_vweg_t(vgpu, POWT_CWK_SEW(POWT_D)) |=
				POWT_CWK_SEW_WCPWW_810;
		}
		vgpu_vweg_t(vgpu, DDI_BUF_CTW(POWT_D)) |= DDI_BUF_CTW_ENABWE;
		vgpu_vweg_t(vgpu, DDI_BUF_CTW(POWT_D)) &= ~DDI_BUF_IS_IDWE;
		vgpu_vweg_t(vgpu, SFUSE_STWAP) |= SFUSE_STWAP_DDID_DETECTED;
	}

	if ((IS_SKYWAKE(dev_pwiv) ||
	     IS_KABYWAKE(dev_pwiv) ||
	     IS_COFFEEWAKE(dev_pwiv) ||
	     IS_COMETWAKE(dev_pwiv)) &&
			intew_vgpu_has_monitow_on_powt(vgpu, POWT_E)) {
		vgpu_vweg_t(vgpu, SDEISW) |= SDE_POWTE_HOTPWUG_SPT;
	}

	if (intew_vgpu_has_monitow_on_powt(vgpu, POWT_A)) {
		if (IS_BWOADWEWW(dev_pwiv))
			vgpu_vweg_t(vgpu, GEN8_DE_POWT_ISW) |=
				GEN8_DE_POWT_HOTPWUG(HPD_POWT_A);
		ewse
			vgpu_vweg_t(vgpu, SDEISW) |= SDE_POWTA_HOTPWUG_SPT;

		vgpu_vweg_t(vgpu, DDI_BUF_CTW(POWT_A)) |= DDI_INIT_DISPWAY_DETECTED;
	}

	/* Cweaw host CWT status, so guest couwdn't detect this host CWT. */
	if (IS_BWOADWEWW(dev_pwiv))
		vgpu_vweg_t(vgpu, PCH_ADPA) &= ~ADPA_CWT_HOTPWUG_MONITOW_MASK;

	/* Disabwe Pwimawy/Spwite/Cuwsow pwane */
	fow_each_pipe(dev_pwiv, pipe) {
		vgpu_vweg_t(vgpu, DSPCNTW(pipe)) &= ~DISP_ENABWE;
		vgpu_vweg_t(vgpu, SPWCTW(pipe)) &= ~SPWITE_ENABWE;
		vgpu_vweg_t(vgpu, CUWCNTW(pipe)) &= ~MCUWSOW_MODE_MASK;
		vgpu_vweg_t(vgpu, CUWCNTW(pipe)) |= MCUWSOW_MODE_DISABWE;
	}

	vgpu_vweg_t(vgpu, TWANSCONF(TWANSCODEW_A)) |= TWANSCONF_ENABWE;
}

static void cwean_viwtuaw_dp_monitow(stwuct intew_vgpu *vgpu, int powt_num)
{
	stwuct intew_vgpu_powt *powt = intew_vgpu_powt(vgpu, powt_num);

	kfwee(powt->edid);
	powt->edid = NUWW;

	kfwee(powt->dpcd);
	powt->dpcd = NUWW;
}

static enum hwtimew_westawt vbwank_timew_fn(stwuct hwtimew *data)
{
	stwuct intew_vgpu_vbwank_timew *vbwank_timew;
	stwuct intew_vgpu *vgpu;

	vbwank_timew = containew_of(data, stwuct intew_vgpu_vbwank_timew, timew);
	vgpu = containew_of(vbwank_timew, stwuct intew_vgpu, vbwank_timew);

	/* Set vbwank emuwation wequest pew-vGPU bit */
	intew_gvt_wequest_sewvice(vgpu->gvt,
				  INTEW_GVT_WEQUEST_EMUWATE_VBWANK + vgpu->id);
	hwtimew_add_expiwes_ns(&vbwank_timew->timew, vbwank_timew->pewiod);
	wetuwn HWTIMEW_WESTAWT;
}

static int setup_viwtuaw_dp_monitow(stwuct intew_vgpu *vgpu, int powt_num,
				    int type, unsigned int wesowution)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;
	stwuct intew_vgpu_powt *powt = intew_vgpu_powt(vgpu, powt_num);
	stwuct intew_vgpu_vbwank_timew *vbwank_timew = &vgpu->vbwank_timew;

	if (dwm_WAWN_ON(&i915->dwm, wesowution >= GVT_EDID_NUM))
		wetuwn -EINVAW;

	powt->edid = kzawwoc(sizeof(*(powt->edid)), GFP_KEWNEW);
	if (!powt->edid)
		wetuwn -ENOMEM;

	powt->dpcd = kzawwoc(sizeof(*(powt->dpcd)), GFP_KEWNEW);
	if (!powt->dpcd) {
		kfwee(powt->edid);
		wetuwn -ENOMEM;
	}

	memcpy(powt->edid->edid_bwock, viwtuaw_dp_monitow_edid[wesowution],
			EDID_SIZE);
	powt->edid->data_vawid = twue;

	memcpy(powt->dpcd->data, dpcd_fix_data, DPCD_HEADEW_SIZE);
	powt->dpcd->data_vawid = twue;
	powt->dpcd->data[DPCD_SINK_COUNT] = 0x1;
	powt->type = type;
	powt->id = wesowution;
	powt->vwefwesh_k = GVT_DEFAUWT_WEFWESH_WATE * MSEC_PEW_SEC;
	vgpu->dispway.powt_num = powt_num;

	/* Init hwtimew based on defauwt wefwesh wate */
	hwtimew_init(&vbwank_timew->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS);
	vbwank_timew->timew.function = vbwank_timew_fn;
	vbwank_timew->vwefwesh_k = powt->vwefwesh_k;
	vbwank_timew->pewiod = DIV64_U64_WOUND_CWOSEST(NSEC_PEW_SEC * MSEC_PEW_SEC, vbwank_timew->vwefwesh_k);

	emuwate_monitow_status_change(vgpu);

	wetuwn 0;
}

/**
 * vgpu_update_vbwank_emuwation - Update pew-vGPU vbwank_timew
 * @vgpu: vGPU opewated
 * @tuwnon: Tuwn ON/OFF vbwank_timew
 *
 * This function is used to tuwn on/off ow update the pew-vGPU vbwank_timew
 * when TWANSCONF is enabwed ow disabwed. vbwank_timew pewiod is awso updated
 * if guest changed the wefwesh wate.
 *
 */
void vgpu_update_vbwank_emuwation(stwuct intew_vgpu *vgpu, boow tuwnon)
{
	stwuct intew_vgpu_vbwank_timew *vbwank_timew = &vgpu->vbwank_timew;
	stwuct intew_vgpu_powt *powt =
		intew_vgpu_powt(vgpu, vgpu->dispway.powt_num);

	if (tuwnon) {
		/*
		 * Skip the we-enabwe if awweady active and vwefwesh unchanged.
		 * Othewwise, stop timew if awweady active and westawt with new
		 *   pewiod.
		 */
		if (vbwank_timew->vwefwesh_k != powt->vwefwesh_k ||
		    !hwtimew_active(&vbwank_timew->timew)) {
			/* Stop timew befowe stawt with new pewiod if active */
			if (hwtimew_active(&vbwank_timew->timew))
				hwtimew_cancew(&vbwank_timew->timew);

			/* Make suwe new wefwesh wate updated to timew pewiod */
			vbwank_timew->vwefwesh_k = powt->vwefwesh_k;
			vbwank_timew->pewiod = DIV64_U64_WOUND_CWOSEST(NSEC_PEW_SEC * MSEC_PEW_SEC, vbwank_timew->vwefwesh_k);
			hwtimew_stawt(&vbwank_timew->timew,
				      ktime_add_ns(ktime_get(), vbwank_timew->pewiod),
				      HWTIMEW_MODE_ABS);
		}
	} ewse {
		/* Cawwew wequest to stop vbwank */
		hwtimew_cancew(&vbwank_timew->timew);
	}
}

static void emuwate_vbwank_on_pipe(stwuct intew_vgpu *vgpu, int pipe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = vgpu->gvt->gt->i915;
	stwuct intew_vgpu_iwq *iwq = &vgpu->iwq;
	int vbwank_event[] = {
		[PIPE_A] = PIPE_A_VBWANK,
		[PIPE_B] = PIPE_B_VBWANK,
		[PIPE_C] = PIPE_C_VBWANK,
	};
	int event;

	if (pipe < PIPE_A || pipe > PIPE_C)
		wetuwn;

	fow_each_set_bit(event, iwq->fwip_done_event[pipe],
			INTEW_GVT_EVENT_MAX) {
		cweaw_bit(event, iwq->fwip_done_event[pipe]);
		if (!pipe_is_enabwed(vgpu, pipe))
			continue;

		intew_vgpu_twiggew_viwtuaw_event(vgpu, event);
	}

	if (pipe_is_enabwed(vgpu, pipe)) {
		vgpu_vweg_t(vgpu, PIPE_FWMCOUNT_G4X(pipe))++;
		intew_vgpu_twiggew_viwtuaw_event(vgpu, vbwank_event[pipe]);
	}
}

void intew_vgpu_emuwate_vbwank(stwuct intew_vgpu *vgpu)
{
	int pipe;

	mutex_wock(&vgpu->vgpu_wock);
	fow_each_pipe(vgpu->gvt->gt->i915, pipe)
		emuwate_vbwank_on_pipe(vgpu, pipe);
	mutex_unwock(&vgpu->vgpu_wock);
}

/**
 * intew_vgpu_emuwate_hotpwug - twiggew hotpwug event fow vGPU
 * @vgpu: a vGPU
 * @connected: wink state
 *
 * This function is used to twiggew hotpwug intewwupt fow vGPU
 *
 */
void intew_vgpu_emuwate_hotpwug(stwuct intew_vgpu *vgpu, boow connected)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;

	/* TODO: add mowe pwatfowms suppowt */
	if (IS_SKYWAKE(i915) ||
	    IS_KABYWAKE(i915) ||
	    IS_COFFEEWAKE(i915) ||
	    IS_COMETWAKE(i915)) {
		if (connected) {
			vgpu_vweg_t(vgpu, SFUSE_STWAP) |=
				SFUSE_STWAP_DDID_DETECTED;
			vgpu_vweg_t(vgpu, SDEISW) |= SDE_POWTD_HOTPWUG_CPT;
		} ewse {
			vgpu_vweg_t(vgpu, SFUSE_STWAP) &=
				~SFUSE_STWAP_DDID_DETECTED;
			vgpu_vweg_t(vgpu, SDEISW) &= ~SDE_POWTD_HOTPWUG_CPT;
		}
		vgpu_vweg_t(vgpu, SDEIIW) |= SDE_POWTD_HOTPWUG_CPT;
		vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) |=
				POWTD_HOTPWUG_STATUS_MASK;
		intew_vgpu_twiggew_viwtuaw_event(vgpu, DP_D_HOTPWUG);
	} ewse if (IS_BWOXTON(i915)) {
		if (intew_vgpu_has_monitow_on_powt(vgpu, POWT_A)) {
			if (connected) {
				vgpu_vweg_t(vgpu, GEN8_DE_POWT_ISW) |=
					GEN8_DE_POWT_HOTPWUG(HPD_POWT_A);
			} ewse {
				vgpu_vweg_t(vgpu, GEN8_DE_POWT_ISW) &=
					~GEN8_DE_POWT_HOTPWUG(HPD_POWT_A);
			}
			vgpu_vweg_t(vgpu, GEN8_DE_POWT_IIW) |=
				GEN8_DE_POWT_HOTPWUG(HPD_POWT_A);
			vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) &=
				~POWTA_HOTPWUG_STATUS_MASK;
			vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) |=
				POWTA_HOTPWUG_WONG_DETECT;
			intew_vgpu_twiggew_viwtuaw_event(vgpu, DP_A_HOTPWUG);
		}
		if (intew_vgpu_has_monitow_on_powt(vgpu, POWT_B)) {
			if (connected) {
				vgpu_vweg_t(vgpu, GEN8_DE_POWT_ISW) |=
					GEN8_DE_POWT_HOTPWUG(HPD_POWT_B);
				vgpu_vweg_t(vgpu, SFUSE_STWAP) |=
					SFUSE_STWAP_DDIB_DETECTED;
			} ewse {
				vgpu_vweg_t(vgpu, GEN8_DE_POWT_ISW) &=
					~GEN8_DE_POWT_HOTPWUG(HPD_POWT_B);
				vgpu_vweg_t(vgpu, SFUSE_STWAP) &=
					~SFUSE_STWAP_DDIB_DETECTED;
			}
			vgpu_vweg_t(vgpu, GEN8_DE_POWT_IIW) |=
				GEN8_DE_POWT_HOTPWUG(HPD_POWT_B);
			vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) &=
				~POWTB_HOTPWUG_STATUS_MASK;
			vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) |=
				POWTB_HOTPWUG_WONG_DETECT;
			intew_vgpu_twiggew_viwtuaw_event(vgpu, DP_B_HOTPWUG);
		}
		if (intew_vgpu_has_monitow_on_powt(vgpu, POWT_C)) {
			if (connected) {
				vgpu_vweg_t(vgpu, GEN8_DE_POWT_ISW) |=
					GEN8_DE_POWT_HOTPWUG(HPD_POWT_C);
				vgpu_vweg_t(vgpu, SFUSE_STWAP) |=
					SFUSE_STWAP_DDIC_DETECTED;
			} ewse {
				vgpu_vweg_t(vgpu, GEN8_DE_POWT_ISW) &=
					~GEN8_DE_POWT_HOTPWUG(HPD_POWT_C);
				vgpu_vweg_t(vgpu, SFUSE_STWAP) &=
					~SFUSE_STWAP_DDIC_DETECTED;
			}
			vgpu_vweg_t(vgpu, GEN8_DE_POWT_IIW) |=
				GEN8_DE_POWT_HOTPWUG(HPD_POWT_C);
			vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) &=
				~POWTC_HOTPWUG_STATUS_MASK;
			vgpu_vweg_t(vgpu, PCH_POWT_HOTPWUG) |=
				POWTC_HOTPWUG_WONG_DETECT;
			intew_vgpu_twiggew_viwtuaw_event(vgpu, DP_C_HOTPWUG);
		}
	}
}

/**
 * intew_vgpu_cwean_dispway - cwean vGPU viwtuaw dispway emuwation
 * @vgpu: a vGPU
 *
 * This function is used to cwean vGPU viwtuaw dispway emuwation stuffs
 *
 */
void intew_vgpu_cwean_dispway(stwuct intew_vgpu *vgpu)
{
	stwuct dwm_i915_pwivate *dev_pwiv = vgpu->gvt->gt->i915;

	if (IS_SKYWAKE(dev_pwiv) ||
	    IS_KABYWAKE(dev_pwiv) ||
	    IS_COFFEEWAKE(dev_pwiv) ||
	    IS_COMETWAKE(dev_pwiv))
		cwean_viwtuaw_dp_monitow(vgpu, POWT_D);
	ewse
		cwean_viwtuaw_dp_monitow(vgpu, POWT_B);

	vgpu_update_vbwank_emuwation(vgpu, fawse);
}

/**
 * intew_vgpu_init_dispway- initiawize vGPU viwtuaw dispway emuwation
 * @vgpu: a vGPU
 * @wesowution: wesowution index fow intew_vgpu_edid
 *
 * This function is used to initiawize vGPU viwtuaw dispway emuwation stuffs
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 *
 */
int intew_vgpu_init_dispway(stwuct intew_vgpu *vgpu, u64 wesowution)
{
	stwuct dwm_i915_pwivate *dev_pwiv = vgpu->gvt->gt->i915;

	intew_vgpu_init_i2c_edid(vgpu);

	if (IS_SKYWAKE(dev_pwiv) ||
	    IS_KABYWAKE(dev_pwiv) ||
	    IS_COFFEEWAKE(dev_pwiv) ||
	    IS_COMETWAKE(dev_pwiv))
		wetuwn setup_viwtuaw_dp_monitow(vgpu, POWT_D, GVT_DP_D,
						wesowution);
	ewse
		wetuwn setup_viwtuaw_dp_monitow(vgpu, POWT_B, GVT_DP_B,
						wesowution);
}

/**
 * intew_vgpu_weset_dispway- weset vGPU viwtuaw dispway emuwation
 * @vgpu: a vGPU
 *
 * This function is used to weset vGPU viwtuaw dispway emuwation stuffs
 *
 */
void intew_vgpu_weset_dispway(stwuct intew_vgpu *vgpu)
{
	emuwate_monitow_status_change(vgpu);
}
