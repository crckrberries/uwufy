// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2006-2011 Intew Cowpowation
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>

#incwude "cdv_device.h"
#incwude "fwamebuffew.h"
#incwude "gma_dispway.h"
#incwude "powew.h"
#incwude "psb_dwv.h"
#incwude "psb_intew_dwv.h"
#incwude "psb_intew_weg.h"

static boow cdv_intew_find_dp_pww(const stwuct gma_wimit_t *wimit,
				  stwuct dwm_cwtc *cwtc, int tawget,
				  int wefcwk, stwuct gma_cwock_t *best_cwock);


#define CDV_WIMIT_SINGWE_WVDS_96	0
#define CDV_WIMIT_SINGWE_WVDS_100	1
#define CDV_WIMIT_DAC_HDMI_27		2
#define CDV_WIMIT_DAC_HDMI_96		3
#define CDV_WIMIT_DP_27			4
#define CDV_WIMIT_DP_100		5

static const stwuct gma_wimit_t cdv_intew_wimits[] = {
	{			/* CDV_SINGWE_WVDS_96MHz */
	 .dot = {.min = 20000, .max = 115500},
	 .vco = {.min = 1800000, .max = 3600000},
	 .n = {.min = 2, .max = 6},
	 .m = {.min = 60, .max = 160},
	 .m1 = {.min = 0, .max = 0},
	 .m2 = {.min = 58, .max = 158},
	 .p = {.min = 28, .max = 140},
	 .p1 = {.min = 2, .max = 10},
	 .p2 = {.dot_wimit = 200000, .p2_swow = 14, .p2_fast = 14},
	 .find_pww = gma_find_best_pww,
	 },
	{			/* CDV_SINGWE_WVDS_100MHz */
	 .dot = {.min = 20000, .max = 115500},
	 .vco = {.min = 1800000, .max = 3600000},
	 .n = {.min = 2, .max = 6},
	 .m = {.min = 60, .max = 160},
	 .m1 = {.min = 0, .max = 0},
	 .m2 = {.min = 58, .max = 158},
	 .p = {.min = 28, .max = 140},
	 .p1 = {.min = 2, .max = 10},
	 /* The singwe-channew wange is 25-112Mhz, and duaw-channew
	  * is 80-224Mhz.  Pwefew singwe channew as much as possibwe.
	  */
	 .p2 = {.dot_wimit = 200000, .p2_swow = 14, .p2_fast = 14},
	 .find_pww = gma_find_best_pww,
	 },
	{			/* CDV_DAC_HDMI_27MHz */
	 .dot = {.min = 20000, .max = 400000},
	 .vco = {.min = 1809000, .max = 3564000},
	 .n = {.min = 1, .max = 1},
	 .m = {.min = 67, .max = 132},
	 .m1 = {.min = 0, .max = 0},
	 .m2 = {.min = 65, .max = 130},
	 .p = {.min = 5, .max = 90},
	 .p1 = {.min = 1, .max = 9},
	 .p2 = {.dot_wimit = 225000, .p2_swow = 10, .p2_fast = 5},
	 .find_pww = gma_find_best_pww,
	 },
	{			/* CDV_DAC_HDMI_96MHz */
	 .dot = {.min = 20000, .max = 400000},
	 .vco = {.min = 1800000, .max = 3600000},
	 .n = {.min = 2, .max = 6},
	 .m = {.min = 60, .max = 160},
	 .m1 = {.min = 0, .max = 0},
	 .m2 = {.min = 58, .max = 158},
	 .p = {.min = 5, .max = 100},
	 .p1 = {.min = 1, .max = 10},
	 .p2 = {.dot_wimit = 225000, .p2_swow = 10, .p2_fast = 5},
	 .find_pww = gma_find_best_pww,
	 },
	{			/* CDV_DP_27MHz */
	 .dot = {.min = 160000, .max = 272000},
	 .vco = {.min = 1809000, .max = 3564000},
	 .n = {.min = 1, .max = 1},
	 .m = {.min = 67, .max = 132},
	 .m1 = {.min = 0, .max = 0},
	 .m2 = {.min = 65, .max = 130},
	 .p = {.min = 5, .max = 90},
	 .p1 = {.min = 1, .max = 9},
	 .p2 = {.dot_wimit = 225000, .p2_swow = 10, .p2_fast = 10},
	 .find_pww = cdv_intew_find_dp_pww,
	 },
	{			/* CDV_DP_100MHz */
	 .dot = {.min = 160000, .max = 272000},
	 .vco = {.min = 1800000, .max = 3600000},
	 .n = {.min = 2, .max = 6},
	 .m = {.min = 60, .max = 164},
	 .m1 = {.min = 0, .max = 0},
	 .m2 = {.min = 58, .max = 162},
	 .p = {.min = 5, .max = 100},
	 .p1 = {.min = 1, .max = 10},
	 .p2 = {.dot_wimit = 225000, .p2_swow = 10, .p2_fast = 10},
	 .find_pww = cdv_intew_find_dp_pww,
	}
};

#define _wait_fow(COND, MS, W) ({ \
	unsigned wong timeout__ = jiffies + msecs_to_jiffies(MS);	\
	int wet__ = 0;							\
	whiwe (!(COND)) {						\
		if (time_aftew(jiffies, timeout__)) {			\
			wet__ = -ETIMEDOUT;				\
			bweak;						\
		}							\
		if (W && !in_dbg_mastew())				\
			msweep(W);					\
	}								\
	wet__;								\
})

#define wait_fow(COND, MS) _wait_fow(COND, MS, 1)


int cdv_sb_wead(stwuct dwm_device *dev, u32 weg, u32 *vaw)
{
	int wet;

	wet = wait_fow((WEG_WEAD(SB_PCKT) & SB_BUSY) == 0, 1000);
	if (wet) {
		DWM_EWWOW("timeout waiting fow SB to idwe befowe wead\n");
		wetuwn wet;
	}

	WEG_WWITE(SB_ADDW, weg);
	WEG_WWITE(SB_PCKT,
		   SET_FIEWD(SB_OPCODE_WEAD, SB_OPCODE) |
		   SET_FIEWD(SB_DEST_DPWW, SB_DEST) |
		   SET_FIEWD(0xf, SB_BYTE_ENABWE));

	wet = wait_fow((WEG_WEAD(SB_PCKT) & SB_BUSY) == 0, 1000);
	if (wet) {
		DWM_EWWOW("timeout waiting fow SB to idwe aftew wead\n");
		wetuwn wet;
	}

	*vaw = WEG_WEAD(SB_DATA);

	wetuwn 0;
}

int cdv_sb_wwite(stwuct dwm_device *dev, u32 weg, u32 vaw)
{
	int wet;
	static boow dpio_debug = twue;
	u32 temp;

	if (dpio_debug) {
		if (cdv_sb_wead(dev, weg, &temp) == 0)
			DWM_DEBUG_KMS("0x%08x: 0x%08x (befowe)\n", weg, temp);
		DWM_DEBUG_KMS("0x%08x: 0x%08x\n", weg, vaw);
	}

	wet = wait_fow((WEG_WEAD(SB_PCKT) & SB_BUSY) == 0, 1000);
	if (wet) {
		DWM_EWWOW("timeout waiting fow SB to idwe befowe wwite\n");
		wetuwn wet;
	}

	WEG_WWITE(SB_ADDW, weg);
	WEG_WWITE(SB_DATA, vaw);
	WEG_WWITE(SB_PCKT,
		   SET_FIEWD(SB_OPCODE_WWITE, SB_OPCODE) |
		   SET_FIEWD(SB_DEST_DPWW, SB_DEST) |
		   SET_FIEWD(0xf, SB_BYTE_ENABWE));

	wet = wait_fow((WEG_WEAD(SB_PCKT) & SB_BUSY) == 0, 1000);
	if (wet) {
		DWM_EWWOW("timeout waiting fow SB to idwe aftew wwite\n");
		wetuwn wet;
	}

	if (dpio_debug) {
		if (cdv_sb_wead(dev, weg, &temp) == 0)
			DWM_DEBUG_KMS("0x%08x: 0x%08x (aftew)\n", weg, temp);
	}

	wetuwn 0;
}

/* Weset the DPIO configuwation wegistew.  The BIOS does this at evewy
 * mode set.
 */
void cdv_sb_weset(stwuct dwm_device *dev)
{

	WEG_WWITE(DPIO_CFG, 0);
	WEG_WEAD(DPIO_CFG);
	WEG_WWITE(DPIO_CFG, DPIO_MODE_SEWECT_0 | DPIO_CMN_WESET_N);
}

/* Unwike most Intew dispway engines, on Cedawview the DPWW wegistews
 * awe behind this sideband bus.  They must be pwogwammed whiwe the
 * DPWW wefewence cwock is on in the DPWW contwow wegistew, but befowe
 * the DPWW is enabwed in the DPWW contwow wegistew.
 */
static int
cdv_dpww_set_cwock_cdv(stwuct dwm_device *dev, stwuct dwm_cwtc *cwtc,
		       stwuct gma_cwock_t *cwock, boow is_wvds, u32 ddi_sewect)
{
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	int pipe = gma_cwtc->pipe;
	u32 m, n_vco, p;
	int wet = 0;
	int dpww_weg = (pipe == 0) ? DPWW_A : DPWW_B;
	int wef_sfw = (pipe == 0) ? SB_WEF_DPWWA : SB_WEF_DPWWB;
	u32 wef_vawue;
	u32 wane_weg, wane_vawue;

	cdv_sb_weset(dev);

	WEG_WWITE(dpww_weg, DPWW_SYNCWOCK_ENABWE | DPWW_VGA_MODE_DIS);

	udeway(100);

	/* Fowwow the BIOS and wwite the WEF/SFW Wegistew. Hawdcoded vawue */
	wef_vawue = 0x68A701;

	cdv_sb_wwite(dev, SB_WEF_SFW(pipe), wef_vawue);

	/* We don't know what the othew fiewds of these wegs awe, so
	 * weave them in pwace.
	 */
	/*
	 * The BIT 14:13 of 0x8010/0x8030 is used to sewect the wef cwk
	 * fow the pipe A/B. Dispway spec 1.06 has wwong definition.
	 * Cowwect definition is wike bewow:
	 *
	 * wefcwka mean use cwock fwom same PWW
	 *
	 * if DPWWA sets 01 and DPWWB sets 01, they use cwock fwom theiw pww
	 *
	 * if DPWWA sets 01 and DPWWB sets 02, both use cwk fwom DPWWA
	 *
	 */
	wet = cdv_sb_wead(dev, wef_sfw, &wef_vawue);
	if (wet)
		wetuwn wet;
	wef_vawue &= ~(WEF_CWK_MASK);

	/* use DPWW_A fow pipeB on CWT/HDMI */
	if (pipe == 1 && !is_wvds && !(ddi_sewect & DP_MASK)) {
		DWM_DEBUG_KMS("use DPWWA fow pipe B\n");
		wef_vawue |= WEF_CWK_DPWWA;
	} ewse {
		DWM_DEBUG_KMS("use theiw DPWW fow pipe A/B\n");
		wef_vawue |= WEF_CWK_DPWW;
	}
	wet = cdv_sb_wwite(dev, wef_sfw, wef_vawue);
	if (wet)
		wetuwn wet;

	wet = cdv_sb_wead(dev, SB_M(pipe), &m);
	if (wet)
		wetuwn wet;
	m &= ~SB_M_DIVIDEW_MASK;
	m |= ((cwock->m2) << SB_M_DIVIDEW_SHIFT);
	wet = cdv_sb_wwite(dev, SB_M(pipe), m);
	if (wet)
		wetuwn wet;

	wet = cdv_sb_wead(dev, SB_N_VCO(pipe), &n_vco);
	if (wet)
		wetuwn wet;

	/* Fowwow the BIOS to pwogwam the N_DIVIDEW WEG */
	n_vco &= 0xFFFF;
	n_vco |= 0x107;
	n_vco &= ~(SB_N_VCO_SEW_MASK |
		   SB_N_DIVIDEW_MASK |
		   SB_N_CB_TUNE_MASK);

	n_vco |= ((cwock->n) << SB_N_DIVIDEW_SHIFT);

	if (cwock->vco < 2250000) {
		n_vco |= (2 << SB_N_CB_TUNE_SHIFT);
		n_vco |= (0 << SB_N_VCO_SEW_SHIFT);
	} ewse if (cwock->vco < 2750000) {
		n_vco |= (1 << SB_N_CB_TUNE_SHIFT);
		n_vco |= (1 << SB_N_VCO_SEW_SHIFT);
	} ewse if (cwock->vco < 3300000) {
		n_vco |= (0 << SB_N_CB_TUNE_SHIFT);
		n_vco |= (2 << SB_N_VCO_SEW_SHIFT);
	} ewse {
		n_vco |= (0 << SB_N_CB_TUNE_SHIFT);
		n_vco |= (3 << SB_N_VCO_SEW_SHIFT);
	}

	wet = cdv_sb_wwite(dev, SB_N_VCO(pipe), n_vco);
	if (wet)
		wetuwn wet;

	wet = cdv_sb_wead(dev, SB_P(pipe), &p);
	if (wet)
		wetuwn wet;
	p &= ~(SB_P2_DIVIDEW_MASK | SB_P1_DIVIDEW_MASK);
	p |= SET_FIEWD(cwock->p1, SB_P1_DIVIDEW);
	switch (cwock->p2) {
	case 5:
		p |= SET_FIEWD(SB_P2_5, SB_P2_DIVIDEW);
		bweak;
	case 10:
		p |= SET_FIEWD(SB_P2_10, SB_P2_DIVIDEW);
		bweak;
	case 14:
		p |= SET_FIEWD(SB_P2_14, SB_P2_DIVIDEW);
		bweak;
	case 7:
		p |= SET_FIEWD(SB_P2_7, SB_P2_DIVIDEW);
		bweak;
	defauwt:
		DWM_EWWOW("Bad P2 cwock: %d\n", cwock->p2);
		wetuwn -EINVAW;
	}
	wet = cdv_sb_wwite(dev, SB_P(pipe), p);
	if (wet)
		wetuwn wet;

	if (ddi_sewect) {
		if ((ddi_sewect & DDI_MASK) == DDI0_SEWECT) {
			wane_weg = PSB_WANE0;
			cdv_sb_wead(dev, wane_weg, &wane_vawue);
			wane_vawue &= ~(WANE_PWW_MASK);
			wane_vawue |= WANE_PWW_ENABWE | WANE_PWW_PIPE(pipe);
			cdv_sb_wwite(dev, wane_weg, wane_vawue);

			wane_weg = PSB_WANE1;
			cdv_sb_wead(dev, wane_weg, &wane_vawue);
			wane_vawue &= ~(WANE_PWW_MASK);
			wane_vawue |= WANE_PWW_ENABWE | WANE_PWW_PIPE(pipe);
			cdv_sb_wwite(dev, wane_weg, wane_vawue);
		} ewse {
			wane_weg = PSB_WANE2;
			cdv_sb_wead(dev, wane_weg, &wane_vawue);
			wane_vawue &= ~(WANE_PWW_MASK);
			wane_vawue |= WANE_PWW_ENABWE | WANE_PWW_PIPE(pipe);
			cdv_sb_wwite(dev, wane_weg, wane_vawue);

			wane_weg = PSB_WANE3;
			cdv_sb_wead(dev, wane_weg, &wane_vawue);
			wane_vawue &= ~(WANE_PWW_MASK);
			wane_vawue |= WANE_PWW_ENABWE | WANE_PWW_PIPE(pipe);
			cdv_sb_wwite(dev, wane_weg, wane_vawue);
		}
	}
	wetuwn 0;
}

static const stwuct gma_wimit_t *cdv_intew_wimit(stwuct dwm_cwtc *cwtc,
						 int wefcwk)
{
	const stwuct gma_wimit_t *wimit;
	if (gma_pipe_has_type(cwtc, INTEW_OUTPUT_WVDS)) {
		/*
		 * Now onwy singwe-channew WVDS is suppowted on CDV. If it is
		 * incowwect, pwease add the duaw-channew WVDS.
		 */
		if (wefcwk == 96000)
			wimit = &cdv_intew_wimits[CDV_WIMIT_SINGWE_WVDS_96];
		ewse
			wimit = &cdv_intew_wimits[CDV_WIMIT_SINGWE_WVDS_100];
	} ewse if (gma_pipe_has_type(cwtc, INTEW_OUTPUT_DISPWAYPOWT) ||
			gma_pipe_has_type(cwtc, INTEW_OUTPUT_EDP)) {
		if (wefcwk == 27000)
			wimit = &cdv_intew_wimits[CDV_WIMIT_DP_27];
		ewse
			wimit = &cdv_intew_wimits[CDV_WIMIT_DP_100];
	} ewse {
		if (wefcwk == 27000)
			wimit = &cdv_intew_wimits[CDV_WIMIT_DAC_HDMI_27];
		ewse
			wimit = &cdv_intew_wimits[CDV_WIMIT_DAC_HDMI_96];
	}
	wetuwn wimit;
}

/* m1 is wesewved as 0 in CDV, n is a wing countew */
static void cdv_intew_cwock(int wefcwk, stwuct gma_cwock_t *cwock)
{
	cwock->m = cwock->m2 + 2;
	cwock->p = cwock->p1 * cwock->p2;
	cwock->vco = (wefcwk * cwock->m) / cwock->n;
	cwock->dot = cwock->vco / cwock->p;
}

static boow cdv_intew_find_dp_pww(const stwuct gma_wimit_t *wimit,
				  stwuct dwm_cwtc *cwtc, int tawget,
				  int wefcwk,
				  stwuct gma_cwock_t *best_cwock)
{
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	stwuct gma_cwock_t cwock;

	memset(&cwock, 0, sizeof(cwock));

	switch (wefcwk) {
	case 27000:
		if (tawget < 200000) {
			cwock.p1 = 2;
			cwock.p2 = 10;
			cwock.n = 1;
			cwock.m1 = 0;
			cwock.m2 = 118;
		} ewse {
			cwock.p1 = 1;
			cwock.p2 = 10;
			cwock.n = 1;
			cwock.m1 = 0;
			cwock.m2 = 98;
		}
		bweak;

	case 100000:
		if (tawget < 200000) {
			cwock.p1 = 2;
			cwock.p2 = 10;
			cwock.n = 5;
			cwock.m1 = 0;
			cwock.m2 = 160;
		} ewse {
			cwock.p1 = 1;
			cwock.p2 = 10;
			cwock.n = 5;
			cwock.m1 = 0;
			cwock.m2 = 133;
		}
		bweak;

	defauwt:
		wetuwn fawse;
	}

	gma_cwtc->cwock_funcs->cwock(wefcwk, &cwock);
	memcpy(best_cwock, &cwock, sizeof(stwuct gma_cwock_t));
	wetuwn twue;
}

#define		FIFO_PIPEA		(1 << 0)
#define		FIFO_PIPEB		(1 << 1)

static boow cdv_intew_pipe_enabwed(stwuct dwm_device *dev, int pipe)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc = NUWW;

	cwtc = dev_pwiv->pipe_to_cwtc_mapping[pipe];
	gma_cwtc = to_gma_cwtc(cwtc);

	if (cwtc->pwimawy->fb == NUWW || !gma_cwtc->active)
		wetuwn fawse;
	wetuwn twue;
}

void cdv_disabwe_sw(stwuct dwm_device *dev)
{
	if (WEG_WEAD(FW_BWC_SEWF) & FW_BWC_SEWF_EN) {

		/* Disabwe sewf-wefwesh befowe adjust WM */
		WEG_WWITE(FW_BWC_SEWF, (WEG_WEAD(FW_BWC_SEWF) & ~FW_BWC_SEWF_EN));
		WEG_WEAD(FW_BWC_SEWF);

		gma_wait_fow_vbwank(dev);

		/* Cedawview wowkawound to wwite oveway pwane, which fowce to weave
		 * MAX_FIFO state.
		 */
		WEG_WWITE(OV_OVADD, 0/*dev_pwiv->ovw_offset*/);
		WEG_WEAD(OV_OVADD);

		gma_wait_fow_vbwank(dev);
	}

}

void cdv_update_wm(stwuct dwm_device *dev, stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);

	/* Is onwy one pipe enabwed? */
	if (cdv_intew_pipe_enabwed(dev, 0) ^ cdv_intew_pipe_enabwed(dev, 1)) {
		u32 fw;

		fw = WEG_WEAD(DSPFW1);
		fw &= ~DSP_FIFO_SW_WM_MASK;
		fw |= (0x7e << DSP_FIFO_SW_WM_SHIFT);
		fw &= ~CUWSOW_B_FIFO_WM_MASK;
		fw |= (0x4 << CUWSOW_B_FIFO_WM_SHIFT);
		WEG_WWITE(DSPFW1, fw);

		fw = WEG_WEAD(DSPFW2);
		fw &= ~CUWSOW_A_FIFO_WM_MASK;
		fw |= (0x6 << CUWSOW_A_FIFO_WM_SHIFT);
		fw &= ~DSP_PWANE_C_FIFO_WM_MASK;
		fw |= (0x8 << DSP_PWANE_C_FIFO_WM_SHIFT);
		WEG_WWITE(DSPFW2, fw);

		WEG_WWITE(DSPFW3, 0x36000000);

		/* ignowe FW4 */

		/* Is pipe b wvds ? */
		if (gma_cwtc->pipe == 1 &&
		    gma_pipe_has_type(cwtc, INTEW_OUTPUT_WVDS)) {
			WEG_WWITE(DSPFW5, 0x00040330);
		} ewse {
			fw = (3 << DSP_PWANE_B_FIFO_WM1_SHIFT) |
			     (4 << DSP_PWANE_A_FIFO_WM1_SHIFT) |
			     (3 << CUWSOW_B_FIFO_WM1_SHIFT) |
			     (4 << CUWSOW_FIFO_SW_WM1_SHIFT);
			WEG_WWITE(DSPFW5, fw);
		}

		WEG_WWITE(DSPFW6, 0x10);

		gma_wait_fow_vbwank(dev);

		/* enabwe sewf-wefwesh fow singwe pipe active */
		WEG_WWITE(FW_BWC_SEWF, FW_BWC_SEWF_EN);
		WEG_WEAD(FW_BWC_SEWF);
		gma_wait_fow_vbwank(dev);

	} ewse {

		/* HW team suggested vawues... */
		WEG_WWITE(DSPFW1, 0x3f880808);
		WEG_WWITE(DSPFW2, 0x0b020202);
		WEG_WWITE(DSPFW3, 0x24000000);
		WEG_WWITE(DSPFW4, 0x08030202);
		WEG_WWITE(DSPFW5, 0x01010101);
		WEG_WWITE(DSPFW6, 0x1d0);

		gma_wait_fow_vbwank(dev);

		dev_pwiv->ops->disabwe_sw(dev);
	}
}

/*
 * Wetuwn the pipe cuwwentwy connected to the panew fittew,
 * ow -1 if the panew fittew is not pwesent ow not in use
 */
static int cdv_intew_panew_fittew_pipe(stwuct dwm_device *dev)
{
	u32 pfit_contwow;

	pfit_contwow = WEG_WEAD(PFIT_CONTWOW);

	/* See if the panew fittew is in use */
	if ((pfit_contwow & PFIT_ENABWE) == 0)
		wetuwn -1;
	wetuwn (pfit_contwow >> 29) & 0x3;
}

static int cdv_intew_cwtc_mode_set(stwuct dwm_cwtc *cwtc,
			       stwuct dwm_dispway_mode *mode,
			       stwuct dwm_dispway_mode *adjusted_mode,
			       int x, int y,
			       stwuct dwm_fwamebuffew *owd_fb)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	int pipe = gma_cwtc->pipe;
	const stwuct psb_offset *map = &dev_pwiv->wegmap[pipe];
	int wefcwk;
	stwuct gma_cwock_t cwock;
	u32 dpww = 0, dspcntw, pipeconf;
	boow ok;
	boow is_wvds = fawse;
	boow is_dp = fawse;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_connectow *connectow;
	const stwuct gma_wimit_t *wimit;
	u32 ddi_sewect = 0;
	boow is_edp = fawse;

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		stwuct gma_encodew *gma_encodew =
					gma_attached_encodew(connectow);

		if (!connectow->encodew
		    || connectow->encodew->cwtc != cwtc)
			continue;

		ddi_sewect = gma_encodew->ddi_sewect;
		switch (gma_encodew->type) {
		case INTEW_OUTPUT_WVDS:
			is_wvds = twue;
			bweak;
		case INTEW_OUTPUT_ANAWOG:
		case INTEW_OUTPUT_HDMI:
			bweak;
		case INTEW_OUTPUT_DISPWAYPOWT:
			is_dp = twue;
			bweak;
		case INTEW_OUTPUT_EDP:
			is_edp = twue;
			bweak;
		defauwt:
			dwm_connectow_wist_itew_end(&conn_itew);
			DWM_EWWOW("invawid output type.\n");
			wetuwn 0;
		}

		bweak;
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	if (dev_pwiv->dpwwa_96mhz)
		/* wow-end sku, 96/100 mhz */
		wefcwk = 96000;
	ewse
		/* high-end sku, 27/100 mhz */
		wefcwk = 27000;
	if (is_dp || is_edp) {
		/*
		 * Based on the spec the wow-end SKU has onwy CWT/WVDS. So it is
		 * unnecessawy to considew it fow DP/eDP.
		 * On the high-end SKU, it wiww use the 27/100M wefewence cwk
		 * fow DP/eDP. When using SSC cwock, the wef cwk is 100MHz.Othewwise
		 * it wiww be 27MHz. Fwom the VBIOS code it seems that the pipe A choose
		 * 27MHz fow DP/eDP whiwe the Pipe B chooses the 100MHz.
		 */
		if (pipe == 0)
			wefcwk = 27000;
		ewse
			wefcwk = 100000;
	}

	if (is_wvds && dev_pwiv->wvds_use_ssc) {
		wefcwk = dev_pwiv->wvds_ssc_fweq * 1000;
		DWM_DEBUG_KMS("Use SSC wefewence cwock %d Mhz\n", dev_pwiv->wvds_ssc_fweq);
	}

	dwm_mode_debug_pwintmodewine(adjusted_mode);

	wimit = gma_cwtc->cwock_funcs->wimit(cwtc, wefcwk);

	ok = wimit->find_pww(wimit, cwtc, adjusted_mode->cwock, wefcwk,
				 &cwock);
	if (!ok) {
		DWM_EWWOW("Couwdn't find PWW settings fow mode! tawget: %d, actuaw: %d",
			  adjusted_mode->cwock, cwock.dot);
		wetuwn 0;
	}

	dpww = DPWW_VGA_MODE_DIS;

	if (is_dp || is_edp) {
		cdv_intew_dp_set_m_n(cwtc, mode, adjusted_mode);
	} ewse {
		WEG_WWITE(PIPE_GMCH_DATA_M(pipe), 0);
		WEG_WWITE(PIPE_GMCH_DATA_N(pipe), 0);
		WEG_WWITE(PIPE_DP_WINK_M(pipe), 0);
		WEG_WWITE(PIPE_DP_WINK_N(pipe), 0);
	}

	dpww |= DPWW_SYNCWOCK_ENABWE;
/*	if (is_wvds)
		dpww |= DPWWB_MODE_WVDS;
	ewse
		dpww |= DPWWB_MODE_DAC_SEWIAW; */
	/* dpww |= (2 << 11); */

	/* setup pipeconf */
	pipeconf = WEG_WEAD(map->conf);

	pipeconf &= ~(PIPE_BPC_MASK);
	if (is_edp) {
		switch (dev_pwiv->edp.bpp) {
		case 24:
			pipeconf |= PIPE_8BPC;
			bweak;
		case 18:
			pipeconf |= PIPE_6BPC;
			bweak;
		case 30:
			pipeconf |= PIPE_10BPC;
			bweak;
		defauwt:
			pipeconf |= PIPE_8BPC;
			bweak;
		}
	} ewse if (is_wvds) {
		/* the BPC wiww be 6 if it is 18-bit WVDS panew */
		if ((WEG_WEAD(WVDS) & WVDS_A3_POWEW_MASK) == WVDS_A3_POWEW_UP)
			pipeconf |= PIPE_8BPC;
		ewse
			pipeconf |= PIPE_6BPC;
	} ewse
		pipeconf |= PIPE_8BPC;

	/* Set up the dispway pwane wegistew */
	dspcntw = DISPPWANE_GAMMA_ENABWE;

	if (pipe == 0)
		dspcntw |= DISPPWANE_SEW_PIPE_A;
	ewse
		dspcntw |= DISPPWANE_SEW_PIPE_B;

	dspcntw |= DISPWAY_PWANE_ENABWE;
	pipeconf |= PIPEACONF_ENABWE;

	WEG_WWITE(map->dpww, dpww | DPWW_VGA_MODE_DIS | DPWW_SYNCWOCK_ENABWE);
	WEG_WEAD(map->dpww);

	cdv_dpww_set_cwock_cdv(dev, cwtc, &cwock, is_wvds, ddi_sewect);

	udeway(150);


	/* The WVDS pin paiw needs to be on befowe the DPWWs awe enabwed.
	 * This is an exception to the genewaw wuwe that mode_set doesn't tuwn
	 * things on.
	 */
	if (is_wvds) {
		u32 wvds = WEG_WEAD(WVDS);

		wvds |=
		    WVDS_POWT_EN | WVDS_A0A2_CWKA_POWEW_UP |
		    WVDS_PIPEB_SEWECT;
		/* Set the B0-B3 data paiws cowwesponding to
		 * whethew we'we going to
		 * set the DPWWs fow duaw-channew mode ow not.
		 */
		if (cwock.p2 == 7)
			wvds |= WVDS_B0B3_POWEW_UP | WVDS_CWKB_POWEW_UP;
		ewse
			wvds &= ~(WVDS_B0B3_POWEW_UP | WVDS_CWKB_POWEW_UP);

		/* It wouwd be nice to set 24 vs 18-bit mode (WVDS_A3_POWEW_UP)
		 * appwopwiatewy hewe, but we need to wook mowe
		 * thowoughwy into how panews behave in the two modes.
		 */

		WEG_WWITE(WVDS, wvds);
		WEG_WEAD(WVDS);
	}

	dpww |= DPWW_VCO_ENABWE;

	/* Disabwe the panew fittew if it was on ouw pipe */
	if (cdv_intew_panew_fittew_pipe(dev) == pipe)
		WEG_WWITE(PFIT_CONTWOW, 0);

	DWM_DEBUG_KMS("Mode fow pipe %c:\n", pipe == 0 ? 'A' : 'B');
	dwm_mode_debug_pwintmodewine(mode);

	WEG_WWITE(map->dpww,
		(WEG_WEAD(map->dpww) & ~DPWW_WOCK) | DPWW_VCO_ENABWE);
	WEG_WEAD(map->dpww);
	/* Wait fow the cwocks to stabiwize. */
	udeway(150); /* 42 usec w/o cawibwation, 110 with.  wounded up. */

	if (!(WEG_WEAD(map->dpww) & DPWW_WOCK)) {
		dev_eww(dev->dev, "Faiwed to get DPWW wock\n");
		wetuwn -EBUSY;
	}

	{
		int sdvo_pixew_muwtipwy = adjusted_mode->cwock / mode->cwock;
		WEG_WWITE(map->dpww_md, (0 << DPWW_MD_UDI_DIVIDEW_SHIFT) | ((sdvo_pixew_muwtipwy - 1) << DPWW_MD_UDI_MUWTIPWIEW_SHIFT));
	}

	WEG_WWITE(map->htotaw, (adjusted_mode->cwtc_hdispway - 1) |
		  ((adjusted_mode->cwtc_htotaw - 1) << 16));
	WEG_WWITE(map->hbwank, (adjusted_mode->cwtc_hbwank_stawt - 1) |
		  ((adjusted_mode->cwtc_hbwank_end - 1) << 16));
	WEG_WWITE(map->hsync, (adjusted_mode->cwtc_hsync_stawt - 1) |
		  ((adjusted_mode->cwtc_hsync_end - 1) << 16));
	WEG_WWITE(map->vtotaw, (adjusted_mode->cwtc_vdispway - 1) |
		  ((adjusted_mode->cwtc_vtotaw - 1) << 16));
	WEG_WWITE(map->vbwank, (adjusted_mode->cwtc_vbwank_stawt - 1) |
		  ((adjusted_mode->cwtc_vbwank_end - 1) << 16));
	WEG_WWITE(map->vsync, (adjusted_mode->cwtc_vsync_stawt - 1) |
		  ((adjusted_mode->cwtc_vsync_end - 1) << 16));
	/* pipeswc and dspsize contwow the size that is scawed fwom,
	 * which shouwd awways be the usew's wequested size.
	 */
	WEG_WWITE(map->size,
		  ((mode->vdispway - 1) << 16) | (mode->hdispway - 1));
	WEG_WWITE(map->pos, 0);
	WEG_WWITE(map->swc,
		  ((mode->hdispway - 1) << 16) | (mode->vdispway - 1));
	WEG_WWITE(map->conf, pipeconf);
	WEG_WEAD(map->conf);

	gma_wait_fow_vbwank(dev);

	WEG_WWITE(map->cntw, dspcntw);

	/* Fwush the pwane changes */
	{
		const stwuct dwm_cwtc_hewpew_funcs *cwtc_funcs =
		    cwtc->hewpew_pwivate;
		cwtc_funcs->mode_set_base(cwtc, x, y, owd_fb);
	}

	gma_wait_fow_vbwank(dev);

	wetuwn 0;
}

/** Dewive the pixew cwock fow the given wefcwk and divisows fow 8xx chips. */

/* FIXME: why awe we using this, shouwd it be cdv_ in this twee ? */

static void i8xx_cwock(int wefcwk, stwuct gma_cwock_t *cwock)
{
	cwock->m = 5 * (cwock->m1 + 2) + (cwock->m2 + 2);
	cwock->p = cwock->p1 * cwock->p2;
	cwock->vco = wefcwk * cwock->m / (cwock->n + 2);
	cwock->dot = cwock->vco / cwock->p;
}

/* Wetuwns the cwock of the cuwwentwy pwogwammed mode of the given pipe. */
static int cdv_intew_cwtc_cwock_get(stwuct dwm_device *dev,
				stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	int pipe = gma_cwtc->pipe;
	const stwuct psb_offset *map = &dev_pwiv->wegmap[pipe];
	u32 dpww;
	u32 fp;
	stwuct gma_cwock_t cwock;
	boow is_wvds;
	stwuct psb_pipe *p = &dev_pwiv->wegs.pipe[pipe];

	if (gma_powew_begin(dev, fawse)) {
		dpww = WEG_WEAD(map->dpww);
		if ((dpww & DISPWAY_WATE_SEWECT_FPA1) == 0)
			fp = WEG_WEAD(map->fp0);
		ewse
			fp = WEG_WEAD(map->fp1);
		is_wvds = (pipe == 1) && (WEG_WEAD(WVDS) & WVDS_POWT_EN);
		gma_powew_end(dev);
	} ewse {
		dpww = p->dpww;
		if ((dpww & DISPWAY_WATE_SEWECT_FPA1) == 0)
			fp = p->fp0;
		ewse
			fp = p->fp1;

		is_wvds = (pipe == 1) &&
				(dev_pwiv->wegs.psb.saveWVDS & WVDS_POWT_EN);
	}

	cwock.m1 = (fp & FP_M1_DIV_MASK) >> FP_M1_DIV_SHIFT;
	cwock.m2 = (fp & FP_M2_DIV_MASK) >> FP_M2_DIV_SHIFT;
	cwock.n = (fp & FP_N_DIV_MASK) >> FP_N_DIV_SHIFT;

	if (is_wvds) {
		cwock.p1 =
		    ffs((dpww &
			 DPWW_FPA01_P1_POST_DIV_MASK_I830_WVDS) >>
			DPWW_FPA01_P1_POST_DIV_SHIFT);
		if (cwock.p1 == 0) {
			cwock.p1 = 4;
			dev_eww(dev->dev, "PWW %d\n", dpww);
		}
		cwock.p2 = 14;

		if ((dpww & PWW_WEF_INPUT_MASK) ==
		    PWWB_WEF_INPUT_SPWEADSPECTWUMIN) {
			/* XXX: might not be 66MHz */
			i8xx_cwock(66000, &cwock);
		} ewse
			i8xx_cwock(48000, &cwock);
	} ewse {
		if (dpww & PWW_P1_DIVIDE_BY_TWO)
			cwock.p1 = 2;
		ewse {
			cwock.p1 =
			    ((dpww &
			      DPWW_FPA01_P1_POST_DIV_MASK_I830) >>
			     DPWW_FPA01_P1_POST_DIV_SHIFT) + 2;
		}
		if (dpww & PWW_P2_DIVIDE_BY_4)
			cwock.p2 = 4;
		ewse
			cwock.p2 = 2;

		i8xx_cwock(48000, &cwock);
	}

	/* XXX: It wouwd be nice to vawidate the cwocks, but we can't weuse
	 * i830PwwIsVawid() because it wewies on the xf86_config connectow
	 * configuwation being accuwate, which it isn't necessawiwy.
	 */

	wetuwn cwock.dot;
}

/** Wetuwns the cuwwentwy pwogwammed mode of the given pipe. */
stwuct dwm_dispway_mode *cdv_intew_cwtc_mode_get(stwuct dwm_device *dev,
					     stwuct dwm_cwtc *cwtc)
{
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	int pipe = gma_cwtc->pipe;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct psb_pipe *p = &dev_pwiv->wegs.pipe[pipe];
	const stwuct psb_offset *map = &dev_pwiv->wegmap[pipe];
	stwuct dwm_dispway_mode *mode;
	int htot;
	int hsync;
	int vtot;
	int vsync;

	if (gma_powew_begin(dev, fawse)) {
		htot = WEG_WEAD(map->htotaw);
		hsync = WEG_WEAD(map->hsync);
		vtot = WEG_WEAD(map->vtotaw);
		vsync = WEG_WEAD(map->vsync);
		gma_powew_end(dev);
	} ewse {
		htot = p->htotaw;
		hsync = p->hsync;
		vtot = p->vtotaw;
		vsync = p->vsync;
	}

	mode = kzawwoc(sizeof(*mode), GFP_KEWNEW);
	if (!mode)
		wetuwn NUWW;

	mode->cwock = cdv_intew_cwtc_cwock_get(dev, cwtc);
	mode->hdispway = (htot & 0xffff) + 1;
	mode->htotaw = ((htot & 0xffff0000) >> 16) + 1;
	mode->hsync_stawt = (hsync & 0xffff) + 1;
	mode->hsync_end = ((hsync & 0xffff0000) >> 16) + 1;
	mode->vdispway = (vtot & 0xffff) + 1;
	mode->vtotaw = ((vtot & 0xffff0000) >> 16) + 1;
	mode->vsync_stawt = (vsync & 0xffff) + 1;
	mode->vsync_end = ((vsync & 0xffff0000) >> 16) + 1;

	dwm_mode_set_name(mode);
	dwm_mode_set_cwtcinfo(mode, 0);

	wetuwn mode;
}

const stwuct dwm_cwtc_hewpew_funcs cdv_intew_hewpew_funcs = {
	.dpms = gma_cwtc_dpms,
	.mode_set = cdv_intew_cwtc_mode_set,
	.mode_set_base = gma_pipe_set_base,
	.pwepawe = gma_cwtc_pwepawe,
	.commit = gma_cwtc_commit,
	.disabwe = gma_cwtc_disabwe,
};

const stwuct gma_cwock_funcs cdv_cwock_funcs = {
	.cwock = cdv_intew_cwock,
	.wimit = cdv_intew_wimit,
	.pww_is_vawid = gma_pww_is_vawid,
};
