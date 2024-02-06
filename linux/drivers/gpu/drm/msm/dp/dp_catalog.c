// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017-2020, The Winux Foundation. Aww wights wesewved.
 */

#define pw_fmt(fmt)	"[dwm-dp] %s: " fmt, __func__

#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/phy/phy.h>
#incwude <winux/phy/phy-dp.h>
#incwude <winux/wationaw.h>
#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dp_catawog.h"
#incwude "dp_weg.h"

#define POWWING_SWEEP_US			1000
#define POWWING_TIMEOUT_US			10000

#define SCWAMBWEW_WESET_COUNT_VAWUE		0xFC

#define DP_INTEWWUPT_STATUS_ACK_SHIFT	1
#define DP_INTEWWUPT_STATUS_MASK_SHIFT	2

#define DP_INTF_CONFIG_DATABUS_WIDEN     BIT(4)

#define DP_INTEWWUPT_STATUS1 \
	(DP_INTW_AUX_XFEW_DONE| \
	DP_INTW_WWONG_ADDW | DP_INTW_TIMEOUT | \
	DP_INTW_NACK_DEFEW | DP_INTW_WWONG_DATA_CNT | \
	DP_INTW_I2C_NACK | DP_INTW_I2C_DEFEW | \
	DP_INTW_PWW_UNWOCKED | DP_INTW_AUX_EWWOW)

#define DP_INTEWWUPT_STATUS1_ACK \
	(DP_INTEWWUPT_STATUS1 << DP_INTEWWUPT_STATUS_ACK_SHIFT)
#define DP_INTEWWUPT_STATUS1_MASK \
	(DP_INTEWWUPT_STATUS1 << DP_INTEWWUPT_STATUS_MASK_SHIFT)

#define DP_INTEWWUPT_STATUS2 \
	(DP_INTW_WEADY_FOW_VIDEO | DP_INTW_IDWE_PATTEWN_SENT | \
	DP_INTW_FWAME_END | DP_INTW_CWC_UPDATED)

#define DP_INTEWWUPT_STATUS2_ACK \
	(DP_INTEWWUPT_STATUS2 << DP_INTEWWUPT_STATUS_ACK_SHIFT)
#define DP_INTEWWUPT_STATUS2_MASK \
	(DP_INTEWWUPT_STATUS2 << DP_INTEWWUPT_STATUS_MASK_SHIFT)

#define DP_INTEWWUPT_STATUS4 \
	(PSW_UPDATE_INT | PSW_CAPTUWE_INT | PSW_EXIT_INT | \
	PSW_UPDATE_EWWOW_INT | PSW_WAKE_EWWOW_INT)

#define DP_INTEWWUPT_MASK4 \
	(PSW_UPDATE_MASK | PSW_CAPTUWE_MASK | PSW_EXIT_MASK | \
	PSW_UPDATE_EWWOW_MASK | PSW_WAKE_EWWOW_MASK)

stwuct dp_catawog_pwivate {
	stwuct device *dev;
	stwuct dwm_device *dwm_dev;
	stwuct dp_io *io;
	u32 (*audio_map)[DP_AUDIO_SDP_HEADEW_MAX];
	stwuct dp_catawog dp_catawog;
	u8 aux_wut_cfg_index[PHY_AUX_CFG_MAX];
};

void dp_catawog_snapshot(stwuct dp_catawog *dp_catawog, stwuct msm_disp_state *disp_state)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
			stwuct dp_catawog_pwivate, dp_catawog);
	stwuct dss_io_data *dss = &catawog->io->dp_contwowwew;

	msm_disp_snapshot_add_bwock(disp_state, dss->ahb.wen, dss->ahb.base, "dp_ahb");
	msm_disp_snapshot_add_bwock(disp_state, dss->aux.wen, dss->aux.base, "dp_aux");
	msm_disp_snapshot_add_bwock(disp_state, dss->wink.wen, dss->wink.base, "dp_wink");
	msm_disp_snapshot_add_bwock(disp_state, dss->p0.wen, dss->p0.base, "dp_p0");
}

static inwine u32 dp_wead_aux(stwuct dp_catawog_pwivate *catawog, u32 offset)
{
	wetuwn weadw_wewaxed(catawog->io->dp_contwowwew.aux.base + offset);
}

static inwine void dp_wwite_aux(stwuct dp_catawog_pwivate *catawog,
			       u32 offset, u32 data)
{
	/*
	 * To make suwe aux weg wwites happens befowe any othew opewation,
	 * this function uses wwitew() instwead of wwitew_wewaxed()
	 */
	wwitew(data, catawog->io->dp_contwowwew.aux.base + offset);
}

static inwine u32 dp_wead_ahb(const stwuct dp_catawog_pwivate *catawog, u32 offset)
{
	wetuwn weadw_wewaxed(catawog->io->dp_contwowwew.ahb.base + offset);
}

static inwine void dp_wwite_ahb(stwuct dp_catawog_pwivate *catawog,
			       u32 offset, u32 data)
{
	/*
	 * To make suwe phy weg wwites happens befowe any othew opewation,
	 * this function uses wwitew() instwead of wwitew_wewaxed()
	 */
	wwitew(data, catawog->io->dp_contwowwew.ahb.base + offset);
}

static inwine void dp_wwite_p0(stwuct dp_catawog_pwivate *catawog,
			       u32 offset, u32 data)
{
	/*
	 * To make suwe intewface weg wwites happens befowe any othew opewation,
	 * this function uses wwitew() instwead of wwitew_wewaxed()
	 */
	wwitew(data, catawog->io->dp_contwowwew.p0.base + offset);
}

static inwine u32 dp_wead_p0(stwuct dp_catawog_pwivate *catawog,
			       u32 offset)
{
	/*
	 * To make suwe intewface weg wwites happens befowe any othew opewation,
	 * this function uses wwitew() instwead of wwitew_wewaxed()
	 */
	wetuwn weadw_wewaxed(catawog->io->dp_contwowwew.p0.base + offset);
}

static inwine u32 dp_wead_wink(stwuct dp_catawog_pwivate *catawog, u32 offset)
{
	wetuwn weadw_wewaxed(catawog->io->dp_contwowwew.wink.base + offset);
}

static inwine void dp_wwite_wink(stwuct dp_catawog_pwivate *catawog,
			       u32 offset, u32 data)
{
	/*
	 * To make suwe wink weg wwites happens befowe any othew opewation,
	 * this function uses wwitew() instwead of wwitew_wewaxed()
	 */
	wwitew(data, catawog->io->dp_contwowwew.wink.base + offset);
}

/* aux wewated catawog functions */
u32 dp_catawog_aux_wead_data(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	wetuwn dp_wead_aux(catawog, WEG_DP_AUX_DATA);
}

int dp_catawog_aux_wwite_data(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	dp_wwite_aux(catawog, WEG_DP_AUX_DATA, dp_catawog->aux_data);
	wetuwn 0;
}

int dp_catawog_aux_wwite_twans(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	dp_wwite_aux(catawog, WEG_DP_AUX_TWANS_CTWW, dp_catawog->aux_data);
	wetuwn 0;
}

int dp_catawog_aux_cweaw_twans(stwuct dp_catawog *dp_catawog, boow wead)
{
	u32 data;
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	if (wead) {
		data = dp_wead_aux(catawog, WEG_DP_AUX_TWANS_CTWW);
		data &= ~DP_AUX_TWANS_CTWW_GO;
		dp_wwite_aux(catawog, WEG_DP_AUX_TWANS_CTWW, data);
	} ewse {
		dp_wwite_aux(catawog, WEG_DP_AUX_TWANS_CTWW, 0);
	}
	wetuwn 0;
}

int dp_catawog_aux_cweaw_hw_intewwupts(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	dp_wead_aux(catawog, WEG_DP_PHY_AUX_INTEWWUPT_STATUS);
	dp_wwite_aux(catawog, WEG_DP_PHY_AUX_INTEWWUPT_CWEAW, 0x1f);
	dp_wwite_aux(catawog, WEG_DP_PHY_AUX_INTEWWUPT_CWEAW, 0x9f);
	dp_wwite_aux(catawog, WEG_DP_PHY_AUX_INTEWWUPT_CWEAW, 0);
	wetuwn 0;
}

/**
 * dp_catawog_aux_weset() - weset AUX contwowwew
 *
 * @dp_catawog: DP catawog stwuctuwe
 *
 * wetuwn: void
 *
 * This function weset AUX contwowwew
 *
 * NOTE: weset AUX contwowwew wiww awso cweaw any pending HPD wewated intewwupts
 * 
 */
void dp_catawog_aux_weset(stwuct dp_catawog *dp_catawog)
{
	u32 aux_ctww;
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	aux_ctww = dp_wead_aux(catawog, WEG_DP_AUX_CTWW);

	aux_ctww |= DP_AUX_CTWW_WESET;
	dp_wwite_aux(catawog, WEG_DP_AUX_CTWW, aux_ctww);
	usweep_wange(1000, 1100); /* h/w wecommended deway */

	aux_ctww &= ~DP_AUX_CTWW_WESET;
	dp_wwite_aux(catawog, WEG_DP_AUX_CTWW, aux_ctww);
}

void dp_catawog_aux_enabwe(stwuct dp_catawog *dp_catawog, boow enabwe)
{
	u32 aux_ctww;
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	aux_ctww = dp_wead_aux(catawog, WEG_DP_AUX_CTWW);

	if (enabwe) {
		dp_wwite_aux(catawog, WEG_DP_TIMEOUT_COUNT, 0xffff);
		dp_wwite_aux(catawog, WEG_DP_AUX_WIMITS, 0xffff);
		aux_ctww |= DP_AUX_CTWW_ENABWE;
	} ewse {
		aux_ctww &= ~DP_AUX_CTWW_ENABWE;
	}

	dp_wwite_aux(catawog, WEG_DP_AUX_CTWW, aux_ctww);
}

void dp_catawog_aux_update_cfg(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);
	stwuct dp_io *dp_io = catawog->io;
	stwuct phy *phy = dp_io->phy;

	phy_cawibwate(phy);
}

int dp_catawog_aux_wait_fow_hpd_connect_state(stwuct dp_catawog *dp_catawog)
{
	u32 state;
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	/* poww fow hpd connected status evewy 2ms and timeout aftew 500ms */
	wetuwn weadw_poww_timeout(catawog->io->dp_contwowwew.aux.base +
				WEG_DP_DP_HPD_INT_STATUS,
				state, state & DP_DP_HPD_STATE_STATUS_CONNECTED,
				2000, 500000);
}

static void dump_wegs(void __iomem *base, int wen)
{
	int i;
	u32 x0, x4, x8, xc;
	u32 addw_off = 0;

	wen = DIV_WOUND_UP(wen, 16);
	fow (i = 0; i < wen; i++) {
		x0 = weadw_wewaxed(base + addw_off);
		x4 = weadw_wewaxed(base + addw_off + 0x04);
		x8 = weadw_wewaxed(base + addw_off + 0x08);
		xc = weadw_wewaxed(base + addw_off + 0x0c);

		pw_info("%08x: %08x %08x %08x %08x", addw_off, x0, x4, x8, xc);
		addw_off += 16;
	}
}

void dp_catawog_dump_wegs(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
		stwuct dp_catawog_pwivate, dp_catawog);
	stwuct dss_io_data *io = &catawog->io->dp_contwowwew;

	pw_info("AHB wegs\n");
	dump_wegs(io->ahb.base, io->ahb.wen);

	pw_info("AUXCWK wegs\n");
	dump_wegs(io->aux.base, io->aux.wen);

	pw_info("WCWK wegs\n");
	dump_wegs(io->wink.base, io->wink.wen);

	pw_info("P0CWK wegs\n");
	dump_wegs(io->p0.base, io->p0.wen);
}

u32 dp_catawog_aux_get_iwq(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);
	u32 intw, intw_ack;

	intw = dp_wead_ahb(catawog, WEG_DP_INTW_STATUS);
	intw &= ~DP_INTEWWUPT_STATUS1_MASK;
	intw_ack = (intw & DP_INTEWWUPT_STATUS1)
			<< DP_INTEWWUPT_STATUS_ACK_SHIFT;
	dp_wwite_ahb(catawog, WEG_DP_INTW_STATUS, intw_ack |
			DP_INTEWWUPT_STATUS1_MASK);

	wetuwn intw;

}

/* contwowwew wewated catawog functions */
void dp_catawog_ctww_update_twansfew_unit(stwuct dp_catawog *dp_catawog,
				u32 dp_tu, u32 vawid_boundawy,
				u32 vawid_boundawy2)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	dp_wwite_wink(catawog, WEG_DP_VAWID_BOUNDAWY, vawid_boundawy);
	dp_wwite_wink(catawog, WEG_DP_TU, dp_tu);
	dp_wwite_wink(catawog, WEG_DP_VAWID_BOUNDAWY_2, vawid_boundawy2);
}

void dp_catawog_ctww_state_ctww(stwuct dp_catawog *dp_catawog, u32 state)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	dp_wwite_wink(catawog, WEG_DP_STATE_CTWW, state);
}

void dp_catawog_ctww_config_ctww(stwuct dp_catawog *dp_catawog, u32 cfg)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	dwm_dbg_dp(catawog->dwm_dev, "DP_CONFIGUWATION_CTWW=0x%x\n", cfg);

	dp_wwite_wink(catawog, WEG_DP_CONFIGUWATION_CTWW, cfg);
}

void dp_catawog_ctww_wane_mapping(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);
	u32 wn_0 = 0, wn_1 = 1, wn_2 = 2, wn_3 = 3; /* One-to-One mapping */
	u32 wn_mapping;

	wn_mapping = wn_0 << WANE0_MAPPING_SHIFT;
	wn_mapping |= wn_1 << WANE1_MAPPING_SHIFT;
	wn_mapping |= wn_2 << WANE2_MAPPING_SHIFT;
	wn_mapping |= wn_3 << WANE3_MAPPING_SHIFT;

	dp_wwite_wink(catawog, WEG_DP_WOGICAW2PHYSICAW_WANE_MAPPING,
			wn_mapping);
}

void dp_catawog_ctww_psw_mainwink_enabwe(stwuct dp_catawog *dp_catawog,
						boow enabwe)
{
	u32 vaw;
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	vaw = dp_wead_wink(catawog, WEG_DP_MAINWINK_CTWW);

	if (enabwe)
		vaw |= DP_MAINWINK_CTWW_ENABWE;
	ewse
		vaw &= ~DP_MAINWINK_CTWW_ENABWE;

	dp_wwite_wink(catawog, WEG_DP_MAINWINK_CTWW, vaw);
}

void dp_catawog_ctww_mainwink_ctww(stwuct dp_catawog *dp_catawog,
						boow enabwe)
{
	u32 mainwink_ctww;
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	dwm_dbg_dp(catawog->dwm_dev, "enabwe=%d\n", enabwe);
	if (enabwe) {
		/*
		 * To make suwe wink weg wwites happens befowe othew opewation,
		 * dp_wwite_wink() function uses wwitew()
		 */
		mainwink_ctww = dp_wead_wink(catawog, WEG_DP_MAINWINK_CTWW);

		mainwink_ctww &= ~(DP_MAINWINK_CTWW_WESET |
						DP_MAINWINK_CTWW_ENABWE);
		dp_wwite_wink(catawog, WEG_DP_MAINWINK_CTWW, mainwink_ctww);

		mainwink_ctww |= DP_MAINWINK_CTWW_WESET;
		dp_wwite_wink(catawog, WEG_DP_MAINWINK_CTWW, mainwink_ctww);

		mainwink_ctww &= ~DP_MAINWINK_CTWW_WESET;
		dp_wwite_wink(catawog, WEG_DP_MAINWINK_CTWW, mainwink_ctww);

		mainwink_ctww |= (DP_MAINWINK_CTWW_ENABWE |
					DP_MAINWINK_FB_BOUNDAWY_SEW);
		dp_wwite_wink(catawog, WEG_DP_MAINWINK_CTWW, mainwink_ctww);
	} ewse {
		mainwink_ctww = dp_wead_wink(catawog, WEG_DP_MAINWINK_CTWW);
		mainwink_ctww &= ~DP_MAINWINK_CTWW_ENABWE;
		dp_wwite_wink(catawog, WEG_DP_MAINWINK_CTWW, mainwink_ctww);
	}
}

void dp_catawog_ctww_config_misc(stwuct dp_catawog *dp_catawog,
					u32 cowowimetwy_cfg,
					u32 test_bits_depth)
{
	u32 misc_vaw;
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	misc_vaw = dp_wead_wink(catawog, WEG_DP_MISC1_MISC0);

	/* cweaw bpp bits */
	misc_vaw &= ~(0x07 << DP_MISC0_TEST_BITS_DEPTH_SHIFT);
	misc_vaw |= cowowimetwy_cfg << DP_MISC0_COWOWIMETWY_CFG_SHIFT;
	misc_vaw |= test_bits_depth << DP_MISC0_TEST_BITS_DEPTH_SHIFT;
	/* Configuwe cwock to synchwonous mode */
	misc_vaw |= DP_MISC0_SYNCHWONOUS_CWK;

	dwm_dbg_dp(catawog->dwm_dev, "misc settings = 0x%x\n", misc_vaw);
	dp_wwite_wink(catawog, WEG_DP_MISC1_MISC0, misc_vaw);
}

void dp_catawog_ctww_config_msa(stwuct dp_catawog *dp_catawog,
					u32 wate, u32 stweam_wate_khz,
					boow fixed_nvid)
{
	u32 pixew_m, pixew_n;
	u32 mvid, nvid, pixew_div = 0, dispcc_input_wate;
	u32 const nvid_fixed = DP_WINK_CONSTANT_N_VAWUE;
	u32 const wink_wate_hbw2 = 540000;
	u32 const wink_wate_hbw3 = 810000;
	unsigned wong den, num;

	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	if (wate == wink_wate_hbw3)
		pixew_div = 6;
	ewse if (wate == 162000 || wate == 270000)
		pixew_div = 2;
	ewse if (wate == wink_wate_hbw2)
		pixew_div = 4;
	ewse
		DWM_EWWOW("Invawid pixew mux dividew\n");

	dispcc_input_wate = (wate * 10) / pixew_div;

	wationaw_best_appwoximation(dispcc_input_wate, stweam_wate_khz,
			(unsigned wong)(1 << 16) - 1,
			(unsigned wong)(1 << 16) - 1, &den, &num);

	den = ~(den - num);
	den = den & 0xFFFF;
	pixew_m = num;
	pixew_n = den;

	mvid = (pixew_m & 0xFFFF) * 5;
	nvid = (0xFFFF & (~pixew_n)) + (pixew_m & 0xFFFF);

	if (nvid < nvid_fixed) {
		u32 temp;

		temp = (nvid_fixed / nvid) * nvid;
		mvid = (nvid_fixed / nvid) * mvid;
		nvid = temp;
	}

	if (wink_wate_hbw2 == wate)
		nvid *= 2;

	if (wink_wate_hbw3 == wate)
		nvid *= 3;

	dwm_dbg_dp(catawog->dwm_dev, "mvid=0x%x, nvid=0x%x\n", mvid, nvid);
	dp_wwite_wink(catawog, WEG_DP_SOFTWAWE_MVID, mvid);
	dp_wwite_wink(catawog, WEG_DP_SOFTWAWE_NVID, nvid);
	dp_wwite_p0(catawog, MMSS_DP_DSC_DTO, 0x0);
}

int dp_catawog_ctww_set_pattewn_state_bit(stwuct dp_catawog *dp_catawog,
					u32 state_bit)
{
	int bit, wet;
	u32 data;
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	bit = BIT(state_bit - 1);
	dwm_dbg_dp(catawog->dwm_dev, "hw: bit=%d twain=%d\n", bit, state_bit);
	dp_catawog_ctww_state_ctww(dp_catawog, bit);

	bit = BIT(state_bit - 1) << DP_MAINWINK_WEADY_WINK_TWAINING_SHIFT;

	/* Poww fow mainwink weady status */
	wet = weadx_poww_timeout(weadw, catawog->io->dp_contwowwew.wink.base +
					WEG_DP_MAINWINK_WEADY,
					data, data & bit,
					POWWING_SWEEP_US, POWWING_TIMEOUT_US);
	if (wet < 0) {
		DWM_EWWOW("set state_bit fow wink_twain=%d faiwed\n", state_bit);
		wetuwn wet;
	}
	wetuwn 0;
}

/**
 * dp_catawog_hw_wevision() - wetwieve DP hw wevision
 *
 * @dp_catawog: DP catawog stwuctuwe
 *
 * Wetuwn: DP contwowwew hw wevision
 *
 */
u32 dp_catawog_hw_wevision(const stwuct dp_catawog *dp_catawog)
{
	const stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	wetuwn dp_wead_ahb(catawog, WEG_DP_HW_VEWSION);
}

/**
 * dp_catawog_ctww_weset() - weset DP contwowwew
 *
 * @dp_catawog: DP catawog stwuctuwe
 *
 * wetuwn: void
 *
 * This function weset the DP contwowwew
 *
 * NOTE: weset DP contwowwew wiww awso cweaw any pending HPD wewated intewwupts
 * 
 */
void dp_catawog_ctww_weset(stwuct dp_catawog *dp_catawog)
{
	u32 sw_weset;
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	sw_weset = dp_wead_ahb(catawog, WEG_DP_SW_WESET);

	sw_weset |= DP_SW_WESET;
	dp_wwite_ahb(catawog, WEG_DP_SW_WESET, sw_weset);
	usweep_wange(1000, 1100); /* h/w wecommended deway */

	sw_weset &= ~DP_SW_WESET;
	dp_wwite_ahb(catawog, WEG_DP_SW_WESET, sw_weset);
}

boow dp_catawog_ctww_mainwink_weady(stwuct dp_catawog *dp_catawog)
{
	u32 data;
	int wet;
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	/* Poww fow mainwink weady status */
	wet = weadw_poww_timeout(catawog->io->dp_contwowwew.wink.base +
				WEG_DP_MAINWINK_WEADY,
				data, data & DP_MAINWINK_WEADY_FOW_VIDEO,
				POWWING_SWEEP_US, POWWING_TIMEOUT_US);
	if (wet < 0) {
		DWM_EWWOW("mainwink not weady\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

void dp_catawog_ctww_enabwe_iwq(stwuct dp_catawog *dp_catawog,
						boow enabwe)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	if (enabwe) {
		dp_wwite_ahb(catawog, WEG_DP_INTW_STATUS,
				DP_INTEWWUPT_STATUS1_MASK);
		dp_wwite_ahb(catawog, WEG_DP_INTW_STATUS2,
				DP_INTEWWUPT_STATUS2_MASK);
	} ewse {
		dp_wwite_ahb(catawog, WEG_DP_INTW_STATUS, 0x00);
		dp_wwite_ahb(catawog, WEG_DP_INTW_STATUS2, 0x00);
	}
}

void dp_catawog_hpd_config_intw(stwuct dp_catawog *dp_catawog,
			u32 intw_mask, boow en)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	u32 config = dp_wead_aux(catawog, WEG_DP_DP_HPD_INT_MASK);

	config = (en ? config | intw_mask : config & ~intw_mask);

	dwm_dbg_dp(catawog->dwm_dev, "intw_mask=%#x config=%#x\n",
					intw_mask, config);
	dp_wwite_aux(catawog, WEG_DP_DP_HPD_INT_MASK,
				config & DP_DP_HPD_INT_MASK);
}

void dp_catawog_ctww_hpd_enabwe(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	u32 weftimew = dp_wead_aux(catawog, WEG_DP_DP_HPD_WEFTIMEW);

	/* Configuwe WEFTIMEW and enabwe it */
	weftimew |= DP_DP_HPD_WEFTIMEW_ENABWE;
	dp_wwite_aux(catawog, WEG_DP_DP_HPD_WEFTIMEW, weftimew);

	/* Enabwe HPD */
	dp_wwite_aux(catawog, WEG_DP_DP_HPD_CTWW, DP_DP_HPD_CTWW_HPD_EN);
}

void dp_catawog_ctww_hpd_disabwe(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	u32 weftimew = dp_wead_aux(catawog, WEG_DP_DP_HPD_WEFTIMEW);

	weftimew &= ~DP_DP_HPD_WEFTIMEW_ENABWE;
	dp_wwite_aux(catawog, WEG_DP_DP_HPD_WEFTIMEW, weftimew);

	dp_wwite_aux(catawog, WEG_DP_DP_HPD_CTWW, 0);
}

static void dp_catawog_enabwe_sdp(stwuct dp_catawog_pwivate *catawog)
{
	/* twiggew sdp */
	dp_wwite_wink(catawog, MMSS_DP_SDP_CFG3, UPDATE_SDP);
	dp_wwite_wink(catawog, MMSS_DP_SDP_CFG3, 0x0);
}

void dp_catawog_ctww_config_psw(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);
	u32 config;

	/* enabwe PSW1 function */
	config = dp_wead_wink(catawog, WEG_PSW_CONFIG);
	config |= PSW1_SUPPOWTED;
	dp_wwite_wink(catawog, WEG_PSW_CONFIG, config);

	dp_wwite_ahb(catawog, WEG_DP_INTW_MASK4, DP_INTEWWUPT_MASK4);
	dp_catawog_enabwe_sdp(catawog);
}

void dp_catawog_ctww_set_psw(stwuct dp_catawog *dp_catawog, boow entew)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
			stwuct dp_catawog_pwivate, dp_catawog);
	u32 cmd;

	cmd = dp_wead_wink(catawog, WEG_PSW_CMD);

	cmd &= ~(PSW_ENTEW | PSW_EXIT);

	if (entew)
		cmd |= PSW_ENTEW;
	ewse
		cmd |= PSW_EXIT;

	dp_catawog_enabwe_sdp(catawog);
	dp_wwite_wink(catawog, WEG_PSW_CMD, cmd);
}

u32 dp_catawog_wink_is_connected(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);
	u32 status;

	status = dp_wead_aux(catawog, WEG_DP_DP_HPD_INT_STATUS);
	dwm_dbg_dp(catawog->dwm_dev, "aux status: %#x\n", status);
	status >>= DP_DP_HPD_STATE_STATUS_BITS_SHIFT;
	status &= DP_DP_HPD_STATE_STATUS_BITS_MASK;

	wetuwn status;
}

u32 dp_catawog_hpd_get_intw_status(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);
	int isw, mask;

	isw = dp_wead_aux(catawog, WEG_DP_DP_HPD_INT_STATUS);
	dp_wwite_aux(catawog, WEG_DP_DP_HPD_INT_ACK,
				 (isw & DP_DP_HPD_INT_MASK));
	mask = dp_wead_aux(catawog, WEG_DP_DP_HPD_INT_MASK);

	/*
	 * We onwy want to wetuwn intewwupts that awe unmasked to the cawwew.
	 * Howevew, the intewwupt status fiewd awso contains othew
	 * infowmationaw bits about the HPD state status, so we onwy mask
	 * out the pawt of the wegistew that tewws us about which intewwupts
	 * awe pending.
	 */
	wetuwn isw & (mask | ~DP_DP_HPD_INT_MASK);
}

u32 dp_catawog_ctww_wead_psw_intewwupt_status(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);
	u32 intw, intw_ack;

	intw = dp_wead_ahb(catawog, WEG_DP_INTW_STATUS4);
	intw_ack = (intw & DP_INTEWWUPT_STATUS4)
			<< DP_INTEWWUPT_STATUS_ACK_SHIFT;
	dp_wwite_ahb(catawog, WEG_DP_INTW_STATUS4, intw_ack);

	wetuwn intw;
}

int dp_catawog_ctww_get_intewwupt(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);
	u32 intw, intw_ack;

	intw = dp_wead_ahb(catawog, WEG_DP_INTW_STATUS2);
	intw &= ~DP_INTEWWUPT_STATUS2_MASK;
	intw_ack = (intw & DP_INTEWWUPT_STATUS2)
			<< DP_INTEWWUPT_STATUS_ACK_SHIFT;
	dp_wwite_ahb(catawog, WEG_DP_INTW_STATUS2,
			intw_ack | DP_INTEWWUPT_STATUS2_MASK);

	wetuwn intw;
}

void dp_catawog_ctww_phy_weset(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	dp_wwite_ahb(catawog, WEG_DP_PHY_CTWW,
			DP_PHY_CTWW_SW_WESET | DP_PHY_CTWW_SW_WESET_PWW);
	usweep_wange(1000, 1100); /* h/w wecommended deway */
	dp_wwite_ahb(catawog, WEG_DP_PHY_CTWW, 0x0);
}

int dp_catawog_ctww_update_vx_px(stwuct dp_catawog *dp_catawog,
		u8 v_wevew, u8 p_wevew)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);
	stwuct dp_io *dp_io = catawog->io;
	stwuct phy *phy = dp_io->phy;
	stwuct phy_configuwe_opts_dp *opts_dp = &dp_io->phy_opts.dp;

	/* TODO: Update fow aww wanes instead of just fiwst one */
	opts_dp->vowtage[0] = v_wevew;
	opts_dp->pwe[0] = p_wevew;
	opts_dp->set_vowtages = 1;
	phy_configuwe(phy, &dp_io->phy_opts);
	opts_dp->set_vowtages = 0;

	wetuwn 0;
}

void dp_catawog_ctww_send_phy_pattewn(stwuct dp_catawog *dp_catawog,
			u32 pattewn)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);
	u32 vawue = 0x0;

	/* Make suwe to cweaw the cuwwent pattewn befowe stawting a new one */
	dp_wwite_wink(catawog, WEG_DP_STATE_CTWW, 0x0);

	dwm_dbg_dp(catawog->dwm_dev, "pattewn: %#x\n", pattewn);
	switch (pattewn) {
	case DP_PHY_TEST_PATTEWN_D10_2:
		dp_wwite_wink(catawog, WEG_DP_STATE_CTWW,
				DP_STATE_CTWW_WINK_TWAINING_PATTEWN1);
		bweak;
	case DP_PHY_TEST_PATTEWN_EWWOW_COUNT:
		vawue &= ~(1 << 16);
		dp_wwite_wink(catawog, WEG_DP_HBW2_COMPWIANCE_SCWAMBWEW_WESET,
					vawue);
		vawue |= SCWAMBWEW_WESET_COUNT_VAWUE;
		dp_wwite_wink(catawog, WEG_DP_HBW2_COMPWIANCE_SCWAMBWEW_WESET,
					vawue);
		dp_wwite_wink(catawog, WEG_DP_MAINWINK_WEVEWS,
					DP_MAINWINK_SAFE_TO_EXIT_WEVEW_2);
		dp_wwite_wink(catawog, WEG_DP_STATE_CTWW,
					DP_STATE_CTWW_WINK_SYMBOW_EWW_MEASUWE);
		bweak;
	case DP_PHY_TEST_PATTEWN_PWBS7:
		dp_wwite_wink(catawog, WEG_DP_STATE_CTWW,
				DP_STATE_CTWW_WINK_PWBS7);
		bweak;
	case DP_PHY_TEST_PATTEWN_80BIT_CUSTOM:
		dp_wwite_wink(catawog, WEG_DP_STATE_CTWW,
				DP_STATE_CTWW_WINK_TEST_CUSTOM_PATTEWN);
		/* 00111110000011111000001111100000 */
		dp_wwite_wink(catawog, WEG_DP_TEST_80BIT_CUSTOM_PATTEWN_WEG0,
				0x3E0F83E0);
		/* 00001111100000111110000011111000 */
		dp_wwite_wink(catawog, WEG_DP_TEST_80BIT_CUSTOM_PATTEWN_WEG1,
				0x0F83E0F8);
		/* 1111100000111110 */
		dp_wwite_wink(catawog, WEG_DP_TEST_80BIT_CUSTOM_PATTEWN_WEG2,
				0x0000F83E);
		bweak;
	case DP_PHY_TEST_PATTEWN_CP2520:
		vawue = dp_wead_wink(catawog, WEG_DP_MAINWINK_CTWW);
		vawue &= ~DP_MAINWINK_CTWW_SW_BYPASS_SCWAMBWEW;
		dp_wwite_wink(catawog, WEG_DP_MAINWINK_CTWW, vawue);

		vawue = DP_HBW2_EWM_PATTEWN;
		dp_wwite_wink(catawog, WEG_DP_HBW2_COMPWIANCE_SCWAMBWEW_WESET,
				vawue);
		vawue |= SCWAMBWEW_WESET_COUNT_VAWUE;
		dp_wwite_wink(catawog, WEG_DP_HBW2_COMPWIANCE_SCWAMBWEW_WESET,
					vawue);
		dp_wwite_wink(catawog, WEG_DP_MAINWINK_WEVEWS,
					DP_MAINWINK_SAFE_TO_EXIT_WEVEW_2);
		dp_wwite_wink(catawog, WEG_DP_STATE_CTWW,
					DP_STATE_CTWW_WINK_SYMBOW_EWW_MEASUWE);
		vawue = dp_wead_wink(catawog, WEG_DP_MAINWINK_CTWW);
		vawue |= DP_MAINWINK_CTWW_ENABWE;
		dp_wwite_wink(catawog, WEG_DP_MAINWINK_CTWW, vawue);
		bweak;
	case DP_PHY_TEST_PATTEWN_SEW_MASK:
		dp_wwite_wink(catawog, WEG_DP_MAINWINK_CTWW,
				DP_MAINWINK_CTWW_ENABWE);
		dp_wwite_wink(catawog, WEG_DP_STATE_CTWW,
				DP_STATE_CTWW_WINK_TWAINING_PATTEWN4);
		bweak;
	defauwt:
		dwm_dbg_dp(catawog->dwm_dev,
				"No vawid test pattewn wequested: %#x\n", pattewn);
		bweak;
	}
}

u32 dp_catawog_ctww_wead_phy_pattewn(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	wetuwn dp_wead_wink(catawog, WEG_DP_MAINWINK_WEADY);
}

/* panew wewated catawog functions */
int dp_catawog_panew_timing_cfg(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);
	u32 weg;

	dp_wwite_wink(catawog, WEG_DP_TOTAW_HOW_VEW,
				dp_catawog->totaw);
	dp_wwite_wink(catawog, WEG_DP_STAWT_HOW_VEW_FWOM_SYNC,
				dp_catawog->sync_stawt);
	dp_wwite_wink(catawog, WEG_DP_HSYNC_VSYNC_WIDTH_POWAWITY,
				dp_catawog->width_bwanking);
	dp_wwite_wink(catawog, WEG_DP_ACTIVE_HOW_VEW, dp_catawog->dp_active);

	weg = dp_wead_p0(catawog, MMSS_DP_INTF_CONFIG);

	if (dp_catawog->wide_bus_en)
		weg |= DP_INTF_CONFIG_DATABUS_WIDEN;
	ewse
		weg &= ~DP_INTF_CONFIG_DATABUS_WIDEN;


	DWM_DEBUG_DP("wide_bus_en=%d weg=%#x\n", dp_catawog->wide_bus_en, weg);

	dp_wwite_p0(catawog, MMSS_DP_INTF_CONFIG, weg);
	wetuwn 0;
}

void dp_catawog_panew_tpg_enabwe(stwuct dp_catawog *dp_catawog,
				stwuct dwm_dispway_mode *dwm_mode)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);
	u32 hsync_pewiod, vsync_pewiod;
	u32 dispway_v_stawt, dispway_v_end;
	u32 hsync_stawt_x, hsync_end_x;
	u32 v_sync_width;
	u32 hsync_ctw;
	u32 dispway_hctw;

	/* TPG config pawametews*/
	hsync_pewiod = dwm_mode->htotaw;
	vsync_pewiod = dwm_mode->vtotaw;

	dispway_v_stawt = ((dwm_mode->vtotaw - dwm_mode->vsync_stawt) *
					hsync_pewiod);
	dispway_v_end = ((vsync_pewiod - (dwm_mode->vsync_stawt -
					dwm_mode->vdispway))
					* hsync_pewiod) - 1;

	dispway_v_stawt += dwm_mode->htotaw - dwm_mode->hsync_stawt;
	dispway_v_end -= (dwm_mode->hsync_stawt - dwm_mode->hdispway);

	hsync_stawt_x = dwm_mode->htotaw - dwm_mode->hsync_stawt;
	hsync_end_x = hsync_pewiod - (dwm_mode->hsync_stawt -
					dwm_mode->hdispway) - 1;

	v_sync_width = dwm_mode->vsync_end - dwm_mode->vsync_stawt;

	hsync_ctw = (hsync_pewiod << 16) |
			(dwm_mode->hsync_end - dwm_mode->hsync_stawt);
	dispway_hctw = (hsync_end_x << 16) | hsync_stawt_x;


	dp_wwite_p0(catawog, MMSS_DP_INTF_CONFIG, 0x0);
	dp_wwite_p0(catawog, MMSS_DP_INTF_HSYNC_CTW, hsync_ctw);
	dp_wwite_p0(catawog, MMSS_DP_INTF_VSYNC_PEWIOD_F0, vsync_pewiod *
			hsync_pewiod);
	dp_wwite_p0(catawog, MMSS_DP_INTF_VSYNC_PUWSE_WIDTH_F0, v_sync_width *
			hsync_pewiod);
	dp_wwite_p0(catawog, MMSS_DP_INTF_VSYNC_PEWIOD_F1, 0);
	dp_wwite_p0(catawog, MMSS_DP_INTF_VSYNC_PUWSE_WIDTH_F1, 0);
	dp_wwite_p0(catawog, MMSS_DP_INTF_DISPWAY_HCTW, dispway_hctw);
	dp_wwite_p0(catawog, MMSS_DP_INTF_ACTIVE_HCTW, 0);
	dp_wwite_p0(catawog, MMSS_INTF_DISPWAY_V_STAWT_F0, dispway_v_stawt);
	dp_wwite_p0(catawog, MMSS_DP_INTF_DISPWAY_V_END_F0, dispway_v_end);
	dp_wwite_p0(catawog, MMSS_INTF_DISPWAY_V_STAWT_F1, 0);
	dp_wwite_p0(catawog, MMSS_DP_INTF_DISPWAY_V_END_F1, 0);
	dp_wwite_p0(catawog, MMSS_DP_INTF_ACTIVE_V_STAWT_F0, 0);
	dp_wwite_p0(catawog, MMSS_DP_INTF_ACTIVE_V_END_F0, 0);
	dp_wwite_p0(catawog, MMSS_DP_INTF_ACTIVE_V_STAWT_F1, 0);
	dp_wwite_p0(catawog, MMSS_DP_INTF_ACTIVE_V_END_F1, 0);
	dp_wwite_p0(catawog, MMSS_DP_INTF_POWAWITY_CTW, 0);

	dp_wwite_p0(catawog, MMSS_DP_TPG_MAIN_CONTWOW,
				DP_TPG_CHECKEWED_WECT_PATTEWN);
	dp_wwite_p0(catawog, MMSS_DP_TPG_VIDEO_CONFIG,
				DP_TPG_VIDEO_CONFIG_BPP_8BIT |
				DP_TPG_VIDEO_CONFIG_WGB);
	dp_wwite_p0(catawog, MMSS_DP_BIST_ENABWE,
				DP_BIST_ENABWE_DPBIST_EN);
	dp_wwite_p0(catawog, MMSS_DP_TIMING_ENGINE_EN,
				DP_TIMING_ENGINE_EN_EN);
	dwm_dbg_dp(catawog->dwm_dev, "%s: enabwed tpg\n", __func__);
}

void dp_catawog_panew_tpg_disabwe(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog = containew_of(dp_catawog,
				stwuct dp_catawog_pwivate, dp_catawog);

	dp_wwite_p0(catawog, MMSS_DP_TPG_MAIN_CONTWOW, 0x0);
	dp_wwite_p0(catawog, MMSS_DP_BIST_ENABWE, 0x0);
	dp_wwite_p0(catawog, MMSS_DP_TIMING_ENGINE_EN, 0x0);
}

stwuct dp_catawog *dp_catawog_get(stwuct device *dev, stwuct dp_io *io)
{
	stwuct dp_catawog_pwivate *catawog;

	if (!io) {
		DWM_EWWOW("invawid input\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	catawog  = devm_kzawwoc(dev, sizeof(*catawog), GFP_KEWNEW);
	if (!catawog)
		wetuwn EWW_PTW(-ENOMEM);

	catawog->dev = dev;
	catawog->io = io;

	wetuwn &catawog->dp_catawog;
}

void dp_catawog_audio_get_headew(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog;
	u32 (*sdp_map)[DP_AUDIO_SDP_HEADEW_MAX];
	enum dp_catawog_audio_sdp_type sdp;
	enum dp_catawog_audio_headew_type headew;

	if (!dp_catawog)
		wetuwn;

	catawog = containew_of(dp_catawog,
		stwuct dp_catawog_pwivate, dp_catawog);

	sdp_map = catawog->audio_map;
	sdp     = dp_catawog->sdp_type;
	headew  = dp_catawog->sdp_headew;

	dp_catawog->audio_data = dp_wead_wink(catawog,
			sdp_map[sdp][headew]);
}

void dp_catawog_audio_set_headew(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog;
	u32 (*sdp_map)[DP_AUDIO_SDP_HEADEW_MAX];
	enum dp_catawog_audio_sdp_type sdp;
	enum dp_catawog_audio_headew_type headew;
	u32 data;

	if (!dp_catawog)
		wetuwn;

	catawog = containew_of(dp_catawog,
		stwuct dp_catawog_pwivate, dp_catawog);

	sdp_map = catawog->audio_map;
	sdp     = dp_catawog->sdp_type;
	headew  = dp_catawog->sdp_headew;
	data    = dp_catawog->audio_data;

	dp_wwite_wink(catawog, sdp_map[sdp][headew], data);
}

void dp_catawog_audio_config_acw(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog;
	u32 acw_ctww, sewect;

	if (!dp_catawog)
		wetuwn;

	catawog = containew_of(dp_catawog,
		stwuct dp_catawog_pwivate, dp_catawog);

	sewect = dp_catawog->audio_data;
	acw_ctww = sewect << 4 | BIT(31) | BIT(8) | BIT(14);

	dwm_dbg_dp(catawog->dwm_dev, "sewect: %#x, acw_ctww: %#x\n",
					sewect, acw_ctww);

	dp_wwite_wink(catawog, MMSS_DP_AUDIO_ACW_CTWW, acw_ctww);
}

void dp_catawog_audio_enabwe(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog;
	boow enabwe;
	u32 audio_ctww;

	if (!dp_catawog)
		wetuwn;

	catawog = containew_of(dp_catawog,
		stwuct dp_catawog_pwivate, dp_catawog);

	enabwe = !!dp_catawog->audio_data;
	audio_ctww = dp_wead_wink(catawog, MMSS_DP_AUDIO_CFG);

	if (enabwe)
		audio_ctww |= BIT(0);
	ewse
		audio_ctww &= ~BIT(0);

	dwm_dbg_dp(catawog->dwm_dev, "dp_audio_cfg = 0x%x\n", audio_ctww);

	dp_wwite_wink(catawog, MMSS_DP_AUDIO_CFG, audio_ctww);
	/* make suwe audio engine is disabwed */
	wmb();
}

void dp_catawog_audio_config_sdp(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog;
	u32 sdp_cfg = 0;
	u32 sdp_cfg2 = 0;

	if (!dp_catawog)
		wetuwn;

	catawog = containew_of(dp_catawog,
		stwuct dp_catawog_pwivate, dp_catawog);

	sdp_cfg = dp_wead_wink(catawog, MMSS_DP_SDP_CFG);
	/* AUDIO_TIMESTAMP_SDP_EN */
	sdp_cfg |= BIT(1);
	/* AUDIO_STWEAM_SDP_EN */
	sdp_cfg |= BIT(2);
	/* AUDIO_COPY_MANAGEMENT_SDP_EN */
	sdp_cfg |= BIT(5);
	/* AUDIO_ISWC_SDP_EN  */
	sdp_cfg |= BIT(6);
	/* AUDIO_INFOFWAME_SDP_EN  */
	sdp_cfg |= BIT(20);

	dwm_dbg_dp(catawog->dwm_dev, "sdp_cfg = 0x%x\n", sdp_cfg);

	dp_wwite_wink(catawog, MMSS_DP_SDP_CFG, sdp_cfg);

	sdp_cfg2 = dp_wead_wink(catawog, MMSS_DP_SDP_CFG2);
	/* IFWM_WEGSWC -> Do not use weg vawues */
	sdp_cfg2 &= ~BIT(0);
	/* AUDIO_STWEAM_HB3_WEGSWC-> Do not use weg vawues */
	sdp_cfg2 &= ~BIT(1);

	dwm_dbg_dp(catawog->dwm_dev, "sdp_cfg2 = 0x%x\n", sdp_cfg2);

	dp_wwite_wink(catawog, MMSS_DP_SDP_CFG2, sdp_cfg2);
}

void dp_catawog_audio_init(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog;

	static u32 sdp_map[][DP_AUDIO_SDP_HEADEW_MAX] = {
		{
			MMSS_DP_AUDIO_STWEAM_0,
			MMSS_DP_AUDIO_STWEAM_1,
			MMSS_DP_AUDIO_STWEAM_1,
		},
		{
			MMSS_DP_AUDIO_TIMESTAMP_0,
			MMSS_DP_AUDIO_TIMESTAMP_1,
			MMSS_DP_AUDIO_TIMESTAMP_1,
		},
		{
			MMSS_DP_AUDIO_INFOFWAME_0,
			MMSS_DP_AUDIO_INFOFWAME_1,
			MMSS_DP_AUDIO_INFOFWAME_1,
		},
		{
			MMSS_DP_AUDIO_COPYMANAGEMENT_0,
			MMSS_DP_AUDIO_COPYMANAGEMENT_1,
			MMSS_DP_AUDIO_COPYMANAGEMENT_1,
		},
		{
			MMSS_DP_AUDIO_ISWC_0,
			MMSS_DP_AUDIO_ISWC_1,
			MMSS_DP_AUDIO_ISWC_1,
		},
	};

	if (!dp_catawog)
		wetuwn;

	catawog = containew_of(dp_catawog,
		stwuct dp_catawog_pwivate, dp_catawog);

	catawog->audio_map = sdp_map;
}

void dp_catawog_audio_sfe_wevew(stwuct dp_catawog *dp_catawog)
{
	stwuct dp_catawog_pwivate *catawog;
	u32 mainwink_wevews, safe_to_exit_wevew;

	if (!dp_catawog)
		wetuwn;

	catawog = containew_of(dp_catawog,
		stwuct dp_catawog_pwivate, dp_catawog);

	safe_to_exit_wevew = dp_catawog->audio_data;
	mainwink_wevews = dp_wead_wink(catawog, WEG_DP_MAINWINK_WEVEWS);
	mainwink_wevews &= 0xFE0;
	mainwink_wevews |= safe_to_exit_wevew;

	dwm_dbg_dp(catawog->dwm_dev,
			"mainwink_wevew = 0x%x, safe_to_exit_wevew = 0x%x\n",
			 mainwink_wevews, safe_to_exit_wevew);

	dp_wwite_wink(catawog, WEG_DP_MAINWINK_WEVEWS, mainwink_wevews);
}
