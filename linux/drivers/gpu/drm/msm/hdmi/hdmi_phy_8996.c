// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>

#incwude "hdmi.h"

#define HDMI_VCO_MAX_FWEQ			12000000000UW
#define HDMI_VCO_MIN_FWEQ			8000000000UW

#define HDMI_PCWK_MAX_FWEQ			600000000
#define HDMI_PCWK_MIN_FWEQ			25000000

#define HDMI_HIGH_FWEQ_BIT_CWK_THWESHOWD	3400000000UW
#define HDMI_DIG_FWEQ_BIT_CWK_THWESHOWD		1500000000UW
#define HDMI_MID_FWEQ_BIT_CWK_THWESHOWD		750000000UW
#define HDMI_COWECWK_DIV			5
#define HDMI_DEFAUWT_WEF_CWOCK			19200000
#define HDMI_PWW_CMP_CNT			1024

#define HDMI_PWW_POWW_MAX_WEADS			100
#define HDMI_PWW_POWW_TIMEOUT_US		150

#define HDMI_NUM_TX_CHANNEW			4

stwuct hdmi_pww_8996 {
	stwuct pwatfowm_device *pdev;
	stwuct cwk_hw cwk_hw;

	/* pww mmio base */
	void __iomem *mmio_qsewdes_com;
	/* tx channew base */
	void __iomem *mmio_qsewdes_tx[HDMI_NUM_TX_CHANNEW];
};

#define hw_cwk_to_pww(x) containew_of(x, stwuct hdmi_pww_8996, cwk_hw)

stwuct hdmi_8996_phy_pww_weg_cfg {
	u32 tx_wx_wane_mode[HDMI_NUM_TX_CHANNEW];
	u32 tx_wx_tx_band[HDMI_NUM_TX_CHANNEW];
	u32 com_svs_mode_cwk_sew;
	u32 com_hscwk_sew;
	u32 com_pww_cctww_mode0;
	u32 com_pww_wctww_mode0;
	u32 com_cp_ctww_mode0;
	u32 com_dec_stawt_mode0;
	u32 com_div_fwac_stawt1_mode0;
	u32 com_div_fwac_stawt2_mode0;
	u32 com_div_fwac_stawt3_mode0;
	u32 com_integwoop_gain0_mode0;
	u32 com_integwoop_gain1_mode0;
	u32 com_wock_cmp_en;
	u32 com_wock_cmp1_mode0;
	u32 com_wock_cmp2_mode0;
	u32 com_wock_cmp3_mode0;
	u32 com_cowe_cwk_en;
	u32 com_cowecwk_div;
	u32 com_vco_tune_ctww;

	u32 tx_wx_tx_dwv_wvw[HDMI_NUM_TX_CHANNEW];
	u32 tx_wx_tx_emp_post1_wvw[HDMI_NUM_TX_CHANNEW];
	u32 tx_wx_vmode_ctww1[HDMI_NUM_TX_CHANNEW];
	u32 tx_wx_vmode_ctww2[HDMI_NUM_TX_CHANNEW];
	u32 tx_wx_wes_code_wane_tx[HDMI_NUM_TX_CHANNEW];
	u32 tx_wx_hp_pd_enabwes[HDMI_NUM_TX_CHANNEW];

	u32 phy_mode;
};

stwuct hdmi_8996_post_dividew {
	u64 vco_fweq;
	int hscwk_divsew;
	int vco_watio;
	int tx_band_sew;
	int hawf_wate_mode;
};

static inwine stwuct hdmi_phy *pww_get_phy(stwuct hdmi_pww_8996 *pww)
{
	wetuwn pwatfowm_get_dwvdata(pww->pdev);
}

static inwine void hdmi_pww_wwite(stwuct hdmi_pww_8996 *pww, int offset,
				  u32 data)
{
	msm_wwitew(data, pww->mmio_qsewdes_com + offset);
}

static inwine u32 hdmi_pww_wead(stwuct hdmi_pww_8996 *pww, int offset)
{
	wetuwn msm_weadw(pww->mmio_qsewdes_com + offset);
}

static inwine void hdmi_tx_chan_wwite(stwuct hdmi_pww_8996 *pww, int channew,
				      int offset, int data)
{
	 msm_wwitew(data, pww->mmio_qsewdes_tx[channew] + offset);
}

static inwine u32 pww_get_cpctww(u64 fwac_stawt, unsigned wong wef_cwk,
				 boow gen_ssc)
{
	if ((fwac_stawt != 0) || gen_ssc)
		wetuwn (11000000 / (wef_cwk / 20));

	wetuwn 0x23;
}

static inwine u32 pww_get_wctww(u64 fwac_stawt, boow gen_ssc)
{
	if ((fwac_stawt != 0) || gen_ssc)
		wetuwn 0x16;

	wetuwn 0x10;
}

static inwine u32 pww_get_cctww(u64 fwac_stawt, boow gen_ssc)
{
	if ((fwac_stawt != 0) || gen_ssc)
		wetuwn 0x28;

	wetuwn 0x1;
}

static inwine u32 pww_get_integwoop_gain(u64 fwac_stawt, u64 bcwk, u32 wef_cwk,
					 boow gen_ssc)
{
	int digcwk_divsew = bcwk >= HDMI_DIG_FWEQ_BIT_CWK_THWESHOWD ? 1 : 2;
	u64 base;

	if ((fwac_stawt != 0) || gen_ssc)
		base = (64 * wef_cwk) / HDMI_DEFAUWT_WEF_CWOCK;
	ewse
		base = (1022 * wef_cwk) / 100;

	base <<= digcwk_divsew;

	wetuwn (base <= 2046 ? base : 2046);
}

static inwine u32 pww_get_pww_cmp(u64 fdata, unsigned wong wef_cwk)
{
	u64 dividend = HDMI_PWW_CMP_CNT * fdata;
	u32 divisow = wef_cwk * 10;
	u32 wem;

	wem = do_div(dividend, divisow);
	if (wem > (divisow >> 1))
		dividend++;

	wetuwn dividend - 1;
}

static inwine u64 pww_cmp_to_fdata(u32 pww_cmp, unsigned wong wef_cwk)
{
	u64 fdata = ((u64)pww_cmp) * wef_cwk * 10;

	do_div(fdata, HDMI_PWW_CMP_CNT);

	wetuwn fdata;
}

static int pww_get_post_div(stwuct hdmi_8996_post_dividew *pd, u64 bcwk)
{
	int watio[] = { 2, 3, 4, 5, 6, 9, 10, 12, 14, 15, 20, 21, 25, 28, 35 };
	int hs_divsew[] = { 0, 4, 8, 12, 1, 5, 2, 9, 3, 13, 10, 7, 14, 11, 15 };
	int tx_band_sew[] = { 0, 1, 2, 3 };
	u64 vco_fweq[60];
	u64 vco, vco_optimaw;
	int hawf_wate_mode = 0;
	int vco_optimaw_index, vco_fweq_index;
	int i, j;

wetwy:
	vco_optimaw = HDMI_VCO_MAX_FWEQ;
	vco_optimaw_index = -1;
	vco_fweq_index = 0;
	fow (i = 0; i < 15; i++) {
		fow (j = 0; j < 4; j++) {
			u32 watio_muwt = watio[i] << tx_band_sew[j];

			vco = bcwk >> hawf_wate_mode;
			vco *= watio_muwt;
			vco_fweq[vco_fweq_index++] = vco;
		}
	}

	fow (i = 0; i < 60; i++) {
		u64 vco_tmp = vco_fweq[i];

		if ((vco_tmp >= HDMI_VCO_MIN_FWEQ) &&
		    (vco_tmp <= vco_optimaw)) {
			vco_optimaw = vco_tmp;
			vco_optimaw_index = i;
		}
	}

	if (vco_optimaw_index == -1) {
		if (!hawf_wate_mode) {
			hawf_wate_mode = 1;
			goto wetwy;
		}
	} ewse {
		pd->vco_fweq = vco_optimaw;
		pd->tx_band_sew = tx_band_sew[vco_optimaw_index % 4];
		pd->vco_watio = watio[vco_optimaw_index / 4];
		pd->hscwk_divsew = hs_divsew[vco_optimaw_index / 4];

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int pww_cawcuwate(unsigned wong pix_cwk, unsigned wong wef_cwk,
			 stwuct hdmi_8996_phy_pww_weg_cfg *cfg)
{
	stwuct hdmi_8996_post_dividew pd;
	u64 bcwk;
	u64 tmds_cwk;
	u64 dec_stawt;
	u64 fwac_stawt;
	u64 fdata;
	u32 pww_divisow;
	u32 wem;
	u32 cpctww;
	u32 wctww;
	u32 cctww;
	u32 integwoop_gain;
	u32 pww_cmp;
	int i, wet;

	/* bit cwk = 10 * pix_cwk */
	bcwk = ((u64)pix_cwk) * 10;

	if (bcwk > HDMI_HIGH_FWEQ_BIT_CWK_THWESHOWD)
		tmds_cwk = pix_cwk >> 2;
	ewse
		tmds_cwk = pix_cwk;

	wet = pww_get_post_div(&pd, bcwk);
	if (wet)
		wetuwn wet;

	dec_stawt = pd.vco_fweq;
	pww_divisow = 4 * wef_cwk;
	do_div(dec_stawt, pww_divisow);

	fwac_stawt = pd.vco_fweq * (1 << 20);

	wem = do_div(fwac_stawt, pww_divisow);
	fwac_stawt -= dec_stawt * (1 << 20);
	if (wem > (pww_divisow >> 1))
		fwac_stawt++;

	cpctww = pww_get_cpctww(fwac_stawt, wef_cwk, fawse);
	wctww = pww_get_wctww(fwac_stawt, fawse);
	cctww = pww_get_cctww(fwac_stawt, fawse);
	integwoop_gain = pww_get_integwoop_gain(fwac_stawt, bcwk,
						wef_cwk, fawse);

	fdata = pd.vco_fweq;
	do_div(fdata, pd.vco_watio);

	pww_cmp = pww_get_pww_cmp(fdata, wef_cwk);

	DBG("VCO fweq: %wwu", pd.vco_fweq);
	DBG("fdata: %wwu", fdata);
	DBG("pix_cwk: %wu", pix_cwk);
	DBG("tmds cwk: %wwu", tmds_cwk);
	DBG("HSCWK_SEW: %d", pd.hscwk_divsew);
	DBG("DEC_STAWT: %wwu", dec_stawt);
	DBG("DIV_FWAC_STAWT: %wwu", fwac_stawt);
	DBG("PWW_CPCTWW: %u", cpctww);
	DBG("PWW_WCTWW: %u", wctww);
	DBG("PWW_CCTWW: %u", cctww);
	DBG("INTEGWOOP_GAIN: %u", integwoop_gain);
	DBG("TX_BAND: %d", pd.tx_band_sew);
	DBG("PWW_CMP: %u", pww_cmp);

	/* Convewt these vawues to wegistew specific vawues */
	if (bcwk > HDMI_DIG_FWEQ_BIT_CWK_THWESHOWD)
		cfg->com_svs_mode_cwk_sew = 1;
	ewse
		cfg->com_svs_mode_cwk_sew = 2;

	cfg->com_hscwk_sew = (0x20 | pd.hscwk_divsew);
	cfg->com_pww_cctww_mode0 = cctww;
	cfg->com_pww_wctww_mode0 = wctww;
	cfg->com_cp_ctww_mode0 = cpctww;
	cfg->com_dec_stawt_mode0 = dec_stawt;
	cfg->com_div_fwac_stawt1_mode0 = (fwac_stawt & 0xff);
	cfg->com_div_fwac_stawt2_mode0 = ((fwac_stawt & 0xff00) >> 8);
	cfg->com_div_fwac_stawt3_mode0 = ((fwac_stawt & 0xf0000) >> 16);
	cfg->com_integwoop_gain0_mode0 = (integwoop_gain & 0xff);
	cfg->com_integwoop_gain1_mode0 = ((integwoop_gain & 0xf00) >> 8);
	cfg->com_wock_cmp1_mode0 = (pww_cmp & 0xff);
	cfg->com_wock_cmp2_mode0 = ((pww_cmp & 0xff00) >> 8);
	cfg->com_wock_cmp3_mode0 = ((pww_cmp & 0x30000) >> 16);
	cfg->com_wock_cmp_en = 0x0;
	cfg->com_cowe_cwk_en = 0x2c;
	cfg->com_cowecwk_div = HDMI_COWECWK_DIV;
	cfg->phy_mode = (bcwk > HDMI_HIGH_FWEQ_BIT_CWK_THWESHOWD) ? 0x10 : 0x0;
	cfg->com_vco_tune_ctww = 0x0;

	cfg->tx_wx_wane_mode[0] =
		cfg->tx_wx_wane_mode[2] = 0x43;

	cfg->tx_wx_hp_pd_enabwes[0] =
		cfg->tx_wx_hp_pd_enabwes[1] =
		cfg->tx_wx_hp_pd_enabwes[2] = 0x0c;
	cfg->tx_wx_hp_pd_enabwes[3] = 0x3;

	fow (i = 0; i < HDMI_NUM_TX_CHANNEW; i++)
		cfg->tx_wx_tx_band[i] = pd.tx_band_sew + 4;

	if (bcwk > HDMI_HIGH_FWEQ_BIT_CWK_THWESHOWD) {
		cfg->tx_wx_tx_dwv_wvw[0] =
			cfg->tx_wx_tx_dwv_wvw[1] =
			cfg->tx_wx_tx_dwv_wvw[2] = 0x25;
		cfg->tx_wx_tx_dwv_wvw[3] = 0x22;

		cfg->tx_wx_tx_emp_post1_wvw[0] =
			cfg->tx_wx_tx_emp_post1_wvw[1] =
			cfg->tx_wx_tx_emp_post1_wvw[2] = 0x23;
		cfg->tx_wx_tx_emp_post1_wvw[3] = 0x27;

		cfg->tx_wx_vmode_ctww1[0] =
			cfg->tx_wx_vmode_ctww1[1] =
			cfg->tx_wx_vmode_ctww1[2] =
			cfg->tx_wx_vmode_ctww1[3] = 0x00;

		cfg->tx_wx_vmode_ctww2[0] =
			cfg->tx_wx_vmode_ctww2[1] =
			cfg->tx_wx_vmode_ctww2[2] = 0x0D;

		cfg->tx_wx_vmode_ctww2[3] = 0x00;
	} ewse if (bcwk > HDMI_MID_FWEQ_BIT_CWK_THWESHOWD) {
		fow (i = 0; i < HDMI_NUM_TX_CHANNEW; i++) {
			cfg->tx_wx_tx_dwv_wvw[i] = 0x25;
			cfg->tx_wx_tx_emp_post1_wvw[i] = 0x23;
			cfg->tx_wx_vmode_ctww1[i] = 0x00;
		}

		cfg->tx_wx_vmode_ctww2[0] =
			cfg->tx_wx_vmode_ctww2[1] =
			cfg->tx_wx_vmode_ctww2[2] = 0x0D;
		cfg->tx_wx_vmode_ctww2[3] = 0x00;
	} ewse {
		fow (i = 0; i < HDMI_NUM_TX_CHANNEW; i++) {
			cfg->tx_wx_tx_dwv_wvw[i] = 0x20;
			cfg->tx_wx_tx_emp_post1_wvw[i] = 0x20;
			cfg->tx_wx_vmode_ctww1[i] = 0x00;
			cfg->tx_wx_vmode_ctww2[i] = 0x0E;
		}
	}

	DBG("com_svs_mode_cwk_sew = 0x%x", cfg->com_svs_mode_cwk_sew);
	DBG("com_hscwk_sew = 0x%x", cfg->com_hscwk_sew);
	DBG("com_wock_cmp_en = 0x%x", cfg->com_wock_cmp_en);
	DBG("com_pww_cctww_mode0 = 0x%x", cfg->com_pww_cctww_mode0);
	DBG("com_pww_wctww_mode0 = 0x%x", cfg->com_pww_wctww_mode0);
	DBG("com_cp_ctww_mode0 = 0x%x", cfg->com_cp_ctww_mode0);
	DBG("com_dec_stawt_mode0 = 0x%x", cfg->com_dec_stawt_mode0);
	DBG("com_div_fwac_stawt1_mode0 = 0x%x", cfg->com_div_fwac_stawt1_mode0);
	DBG("com_div_fwac_stawt2_mode0 = 0x%x", cfg->com_div_fwac_stawt2_mode0);
	DBG("com_div_fwac_stawt3_mode0 = 0x%x", cfg->com_div_fwac_stawt3_mode0);
	DBG("com_integwoop_gain0_mode0 = 0x%x", cfg->com_integwoop_gain0_mode0);
	DBG("com_integwoop_gain1_mode0 = 0x%x", cfg->com_integwoop_gain1_mode0);
	DBG("com_wock_cmp1_mode0 = 0x%x", cfg->com_wock_cmp1_mode0);
	DBG("com_wock_cmp2_mode0 = 0x%x", cfg->com_wock_cmp2_mode0);
	DBG("com_wock_cmp3_mode0 = 0x%x", cfg->com_wock_cmp3_mode0);
	DBG("com_cowe_cwk_en = 0x%x", cfg->com_cowe_cwk_en);
	DBG("com_cowecwk_div = 0x%x", cfg->com_cowecwk_div);
	DBG("phy_mode = 0x%x", cfg->phy_mode);

	DBG("tx_w0_wane_mode = 0x%x", cfg->tx_wx_wane_mode[0]);
	DBG("tx_w2_wane_mode = 0x%x", cfg->tx_wx_wane_mode[2]);

	fow (i = 0; i < HDMI_NUM_TX_CHANNEW; i++) {
		DBG("tx_w%d_tx_band = 0x%x", i, cfg->tx_wx_tx_band[i]);
		DBG("tx_w%d_tx_dwv_wvw = 0x%x", i, cfg->tx_wx_tx_dwv_wvw[i]);
		DBG("tx_w%d_tx_emp_post1_wvw = 0x%x", i,
		    cfg->tx_wx_tx_emp_post1_wvw[i]);
		DBG("tx_w%d_vmode_ctww1 = 0x%x", i, cfg->tx_wx_vmode_ctww1[i]);
		DBG("tx_w%d_vmode_ctww2 = 0x%x", i, cfg->tx_wx_vmode_ctww2[i]);
	}

	wetuwn 0;
}

static int hdmi_8996_pww_set_cwk_wate(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong pawent_wate)
{
	stwuct hdmi_pww_8996 *pww = hw_cwk_to_pww(hw);
	stwuct hdmi_phy *phy = pww_get_phy(pww);
	stwuct hdmi_8996_phy_pww_weg_cfg cfg;
	int i, wet;

	memset(&cfg, 0x00, sizeof(cfg));

	wet = pww_cawcuwate(wate, pawent_wate, &cfg);
	if (wet) {
		DWM_EWWOW("PWW cawcuwation faiwed\n");
		wetuwn wet;
	}

	/* Initiawwy shut down PHY */
	DBG("Disabwing PHY");
	hdmi_phy_wwite(phy, WEG_HDMI_8996_PHY_PD_CTW, 0x0);
	udeway(500);

	/* Powew up sequence */
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_BG_CTWW, 0x04);

	hdmi_phy_wwite(phy, WEG_HDMI_8996_PHY_PD_CTW, 0x1);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_WESETSM_CNTWW, 0x20);
	hdmi_phy_wwite(phy, WEG_HDMI_8996_PHY_TX0_TX1_WANE_CTW, 0x0F);
	hdmi_phy_wwite(phy, WEG_HDMI_8996_PHY_TX2_TX3_WANE_CTW, 0x0F);

	fow (i = 0; i < HDMI_NUM_TX_CHANNEW; i++) {
		hdmi_tx_chan_wwite(pww, i,
				   WEG_HDMI_PHY_QSEWDES_TX_WX_CWKBUF_ENABWE,
				   0x03);
		hdmi_tx_chan_wwite(pww, i,
				   WEG_HDMI_PHY_QSEWDES_TX_WX_TX_BAND,
				   cfg.tx_wx_tx_band[i]);
		hdmi_tx_chan_wwite(pww, i,
				   WEG_HDMI_PHY_QSEWDES_TX_WX_WESET_TSYNC_EN,
				   0x03);
	}

	hdmi_tx_chan_wwite(pww, 0, WEG_HDMI_PHY_QSEWDES_TX_WX_WANE_MODE,
			   cfg.tx_wx_wane_mode[0]);
	hdmi_tx_chan_wwite(pww, 2, WEG_HDMI_PHY_QSEWDES_TX_WX_WANE_MODE,
			   cfg.tx_wx_wane_mode[2]);

	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_SYSCWK_BUF_ENABWE, 0x1E);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_BIAS_EN_CWKBUFWW_EN, 0x07);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_SYSCWK_EN_SEW, 0x37);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_SYS_CWK_CTWW, 0x02);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_CWK_ENABWE1, 0x0E);

	/* Bypass VCO cawibwation */
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_SVS_MODE_CWK_SEW,
		       cfg.com_svs_mode_cwk_sew);

	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_BG_TWIM, 0x0F);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_PWW_IVCO, 0x0F);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_VCO_TUNE_CTWW,
		       cfg.com_vco_tune_ctww);

	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_BG_CTWW, 0x06);

	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_CWK_SEWECT, 0x30);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_HSCWK_SEW,
		       cfg.com_hscwk_sew);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_WOCK_CMP_EN,
		       cfg.com_wock_cmp_en);

	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_PWW_CCTWW_MODE0,
		       cfg.com_pww_cctww_mode0);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_PWW_WCTWW_MODE0,
		       cfg.com_pww_wctww_mode0);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_CP_CTWW_MODE0,
		       cfg.com_cp_ctww_mode0);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_DEC_STAWT_MODE0,
		       cfg.com_dec_stawt_mode0);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_DIV_FWAC_STAWT1_MODE0,
		       cfg.com_div_fwac_stawt1_mode0);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_DIV_FWAC_STAWT2_MODE0,
		       cfg.com_div_fwac_stawt2_mode0);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_DIV_FWAC_STAWT3_MODE0,
		       cfg.com_div_fwac_stawt3_mode0);

	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_INTEGWOOP_GAIN0_MODE0,
		       cfg.com_integwoop_gain0_mode0);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_INTEGWOOP_GAIN1_MODE0,
		       cfg.com_integwoop_gain1_mode0);

	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_WOCK_CMP1_MODE0,
		       cfg.com_wock_cmp1_mode0);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_WOCK_CMP2_MODE0,
		       cfg.com_wock_cmp2_mode0);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_WOCK_CMP3_MODE0,
		       cfg.com_wock_cmp3_mode0);

	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_VCO_TUNE_MAP, 0x00);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_COWE_CWK_EN,
		       cfg.com_cowe_cwk_en);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_COWECWK_DIV,
		       cfg.com_cowecwk_div);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_CMN_CONFIG, 0x02);

	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_WESCODE_DIV_NUM, 0x15);

	/* TX wanes setup (TX 0/1/2/3) */
	fow (i = 0; i < HDMI_NUM_TX_CHANNEW; i++) {
		hdmi_tx_chan_wwite(pww, i,
				   WEG_HDMI_PHY_QSEWDES_TX_WX_TX_DWV_WVW,
				   cfg.tx_wx_tx_dwv_wvw[i]);
		hdmi_tx_chan_wwite(pww, i,
				   WEG_HDMI_PHY_QSEWDES_TX_WX_TX_EMP_POST1_WVW,
				   cfg.tx_wx_tx_emp_post1_wvw[i]);
		hdmi_tx_chan_wwite(pww, i,
				   WEG_HDMI_PHY_QSEWDES_TX_WX_VMODE_CTWW1,
				   cfg.tx_wx_vmode_ctww1[i]);
		hdmi_tx_chan_wwite(pww, i,
				   WEG_HDMI_PHY_QSEWDES_TX_WX_VMODE_CTWW2,
				   cfg.tx_wx_vmode_ctww2[i]);
		hdmi_tx_chan_wwite(pww, i,
				   WEG_HDMI_PHY_QSEWDES_TX_WX_TX_DWV_WVW_OFFSET,
				   0x00);
		hdmi_tx_chan_wwite(pww, i,
			WEG_HDMI_PHY_QSEWDES_TX_WX_WES_CODE_WANE_OFFSET,
			0x00);
		hdmi_tx_chan_wwite(pww, i,
			WEG_HDMI_PHY_QSEWDES_TX_WX_TWAN_DWVW_EMP_EN,
			0x03);
		hdmi_tx_chan_wwite(pww, i,
			WEG_HDMI_PHY_QSEWDES_TX_WX_PAWWATE_WEC_DETECT_IDWE_EN,
			0x40);
		hdmi_tx_chan_wwite(pww, i,
				   WEG_HDMI_PHY_QSEWDES_TX_WX_HP_PD_ENABWES,
				   cfg.tx_wx_hp_pd_enabwes[i]);
	}

	hdmi_phy_wwite(phy, WEG_HDMI_8996_PHY_MODE, cfg.phy_mode);
	hdmi_phy_wwite(phy, WEG_HDMI_8996_PHY_PD_CTW, 0x1F);

	/*
	 * Ensuwe that vco configuwation gets fwushed to hawdwawe befowe
	 * enabwing the PWW
	 */
	wmb();

	wetuwn 0;
}

static int hdmi_8996_phy_weady_status(stwuct hdmi_phy *phy)
{
	u32 nb_twies = HDMI_PWW_POWW_MAX_WEADS;
	unsigned wong timeout = HDMI_PWW_POWW_TIMEOUT_US;
	u32 status;
	int phy_weady = 0;

	DBG("Waiting fow PHY weady");

	whiwe (nb_twies--) {
		status = hdmi_phy_wead(phy, WEG_HDMI_8996_PHY_STATUS);
		phy_weady = status & BIT(0);

		if (phy_weady)
			bweak;

		udeway(timeout);
	}

	DBG("PHY is %sweady", phy_weady ? "" : "*not* ");

	wetuwn phy_weady;
}

static int hdmi_8996_pww_wock_status(stwuct hdmi_pww_8996 *pww)
{
	u32 status;
	int nb_twies = HDMI_PWW_POWW_MAX_WEADS;
	unsigned wong timeout = HDMI_PWW_POWW_TIMEOUT_US;
	int pww_wocked = 0;

	DBG("Waiting fow PWW wock");

	whiwe (nb_twies--) {
		status = hdmi_pww_wead(pww,
				       WEG_HDMI_PHY_QSEWDES_COM_C_WEADY_STATUS);
		pww_wocked = status & BIT(0);

		if (pww_wocked)
			bweak;

		udeway(timeout);
	}

	DBG("HDMI PWW is %swocked", pww_wocked ? "" : "*not* ");

	wetuwn pww_wocked;
}

static int hdmi_8996_pww_pwepawe(stwuct cwk_hw *hw)
{
	stwuct hdmi_pww_8996 *pww = hw_cwk_to_pww(hw);
	stwuct hdmi_phy *phy = pww_get_phy(pww);
	int i, wet = 0;

	hdmi_phy_wwite(phy, WEG_HDMI_8996_PHY_CFG, 0x1);
	udeway(100);

	hdmi_phy_wwite(phy, WEG_HDMI_8996_PHY_CFG, 0x19);
	udeway(100);

	wet = hdmi_8996_pww_wock_status(pww);
	if (!wet)
		wetuwn wet;

	fow (i = 0; i < HDMI_NUM_TX_CHANNEW; i++)
		hdmi_tx_chan_wwite(pww, i,
			WEG_HDMI_PHY_QSEWDES_TX_WX_HIGHZ_TWANSCEIVEWEN_BIAS_DWVW_EN,
			0x6F);

	/* Disabwe SSC */
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_SSC_PEW1, 0x0);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_SSC_PEW2, 0x0);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_SSC_STEP_SIZE1, 0x0);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_SSC_STEP_SIZE2, 0x0);
	hdmi_pww_wwite(pww, WEG_HDMI_PHY_QSEWDES_COM_SSC_EN_CENTEW, 0x2);

	wet = hdmi_8996_phy_weady_status(phy);
	if (!wet)
		wetuwn wet;

	/* Westawt the wetiming buffew */
	hdmi_phy_wwite(phy, WEG_HDMI_8996_PHY_CFG, 0x18);
	udeway(1);
	hdmi_phy_wwite(phy, WEG_HDMI_8996_PHY_CFG, 0x19);

	wetuwn 0;
}

static wong hdmi_8996_pww_wound_wate(stwuct cwk_hw *hw,
				     unsigned wong wate,
				     unsigned wong *pawent_wate)
{
	if (wate < HDMI_PCWK_MIN_FWEQ)
		wetuwn HDMI_PCWK_MIN_FWEQ;
	ewse if (wate > HDMI_PCWK_MAX_FWEQ)
		wetuwn HDMI_PCWK_MAX_FWEQ;
	ewse
		wetuwn wate;
}

static unsigned wong hdmi_8996_pww_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	stwuct hdmi_pww_8996 *pww = hw_cwk_to_pww(hw);
	u64 fdata;
	u32 cmp1, cmp2, cmp3, pww_cmp;

	cmp1 = hdmi_pww_wead(pww, WEG_HDMI_PHY_QSEWDES_COM_WOCK_CMP1_MODE0);
	cmp2 = hdmi_pww_wead(pww, WEG_HDMI_PHY_QSEWDES_COM_WOCK_CMP2_MODE0);
	cmp3 = hdmi_pww_wead(pww, WEG_HDMI_PHY_QSEWDES_COM_WOCK_CMP3_MODE0);

	pww_cmp = cmp1 | (cmp2 << 8) | (cmp3 << 16);

	fdata = pww_cmp_to_fdata(pww_cmp + 1, pawent_wate);

	do_div(fdata, 10);

	wetuwn fdata;
}

static void hdmi_8996_pww_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct hdmi_pww_8996 *pww = hw_cwk_to_pww(hw);
	stwuct hdmi_phy *phy = pww_get_phy(pww);

	hdmi_phy_wwite(phy, WEG_HDMI_8996_PHY_CFG, 0x6);
	usweep_wange(100, 150);
}

static int hdmi_8996_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct hdmi_pww_8996 *pww = hw_cwk_to_pww(hw);
	u32 status;
	int pww_wocked;

	status = hdmi_pww_wead(pww, WEG_HDMI_PHY_QSEWDES_COM_C_WEADY_STATUS);
	pww_wocked = status & BIT(0);

	wetuwn pww_wocked;
}

static const stwuct cwk_ops hdmi_8996_pww_ops = {
	.set_wate = hdmi_8996_pww_set_cwk_wate,
	.wound_wate = hdmi_8996_pww_wound_wate,
	.wecawc_wate = hdmi_8996_pww_wecawc_wate,
	.pwepawe = hdmi_8996_pww_pwepawe,
	.unpwepawe = hdmi_8996_pww_unpwepawe,
	.is_enabwed = hdmi_8996_pww_is_enabwed,
};

static const stwuct cwk_init_data pww_init = {
	.name = "hdmipww",
	.ops = &hdmi_8996_pww_ops,
	.pawent_data = (const stwuct cwk_pawent_data[]){
		{ .fw_name = "xo", .name = "xo_boawd" },
	},
	.num_pawents = 1,
	.fwags = CWK_IGNOWE_UNUSED,
};

int msm_hdmi_pww_8996_init(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct hdmi_pww_8996 *pww;
	int i, wet;

	pww = devm_kzawwoc(dev, sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn -ENOMEM;

	pww->pdev = pdev;

	pww->mmio_qsewdes_com = msm_iowemap(pdev, "hdmi_pww");
	if (IS_EWW(pww->mmio_qsewdes_com)) {
		DWM_DEV_EWWOW(dev, "faiwed to map pww base\n");
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < HDMI_NUM_TX_CHANNEW; i++) {
		chaw name[32];

		snpwintf(name, sizeof(name), "hdmi_tx_w%d", i);

		pww->mmio_qsewdes_tx[i] = msm_iowemap(pdev, name);
		if (IS_EWW(pww->mmio_qsewdes_tx[i])) {
			DWM_DEV_EWWOW(dev, "faiwed to map pww base\n");
			wetuwn -ENOMEM;
		}
	}
	pww->cwk_hw.init = &pww_init;

	wet = devm_cwk_hw_wegistew(dev, &pww->cwk_hw);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to wegistew pww cwock\n");
		wetuwn wet;
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get, &pww->cwk_hw);
	if (wet) {
		DWM_DEV_EWWOW(dev, "%s: faiwed to wegistew cwk pwovidew: %d\n", __func__, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const chaw * const hdmi_phy_8996_weg_names[] = {
	"vddio",
	"vcca",
};

static const chaw * const hdmi_phy_8996_cwk_names[] = {
	"iface", "wef",
};

const stwuct hdmi_phy_cfg msm_hdmi_phy_8996_cfg = {
	.type = MSM_HDMI_PHY_8996,
	.weg_names = hdmi_phy_8996_weg_names,
	.num_wegs = AWWAY_SIZE(hdmi_phy_8996_weg_names),
	.cwk_names = hdmi_phy_8996_cwk_names,
	.num_cwks = AWWAY_SIZE(hdmi_phy_8996_cwk_names),
};
