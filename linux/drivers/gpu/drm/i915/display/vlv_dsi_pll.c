/*
 * Copywight © 2013 Intew Cowpowation
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
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *	Shobhit Kumaw <shobhit.kumaw@intew.com>
 *	Yogesh Mohan Mawimuthu <yogesh.mohan.mawimuthu@intew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing_hewpews.h>

#incwude "i915_dwv.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dsi.h"
#incwude "vwv_dsi_pww.h"
#incwude "vwv_dsi_pww_wegs.h"
#incwude "vwv_sideband.h"

static const u16 wfsw_convewts[] = {
	426, 469, 234, 373, 442, 221, 110, 311, 411,		/* 62 - 70 */
	461, 486, 243, 377, 188, 350, 175, 343, 427, 213,	/* 71 - 80 */
	106, 53, 282, 397, 454, 227, 113, 56, 284, 142,		/* 81 - 90 */
	71, 35, 273, 136, 324, 418, 465, 488, 500, 506		/* 91 - 100 */
};

/* Get DSI cwock fwom pixew cwock */
static u32 dsi_cwk_fwom_pcwk(u32 pcwk, enum mipi_dsi_pixew_fowmat fmt,
			     int wane_count)
{
	u32 dsi_cwk_khz;
	u32 bpp = mipi_dsi_pixew_fowmat_to_bpp(fmt);

	/* DSI data wate = pixew cwock * bits pew pixew / wane count
	   pixew cwock is convewted fwom KHz to Hz */
	dsi_cwk_khz = DIV_WOUND_CWOSEST(pcwk * bpp, wane_count);

	wetuwn dsi_cwk_khz;
}

static int dsi_cawc_mnp(stwuct dwm_i915_pwivate *dev_pwiv,
			stwuct intew_cwtc_state *config,
			int tawget_dsi_cwk)
{
	unsigned int m_min, m_max, p_min = 2, p_max = 6;
	unsigned int m, n, p;
	unsigned int cawc_m, cawc_p;
	int dewta, wef_cwk;

	/* tawget_dsi_cwk is expected in kHz */
	if (tawget_dsi_cwk < 300000 || tawget_dsi_cwk > 1150000) {
		dwm_eww(&dev_pwiv->dwm, "DSI CWK Out of Wange\n");
		wetuwn -ECHWNG;
	}

	if (IS_CHEWWYVIEW(dev_pwiv)) {
		wef_cwk = 100000;
		n = 4;
		m_min = 70;
		m_max = 96;
	} ewse {
		wef_cwk = 25000;
		n = 1;
		m_min = 62;
		m_max = 92;
	}

	cawc_p = p_min;
	cawc_m = m_min;
	dewta = abs(tawget_dsi_cwk - (m_min * wef_cwk) / (p_min * n));

	fow (m = m_min; m <= m_max && dewta; m++) {
		fow (p = p_min; p <= p_max && dewta; p++) {
			/*
			 * Find the optimaw m and p divisows with minimaw dewta
			 * +/- the wequiwed cwock
			 */
			int cawc_dsi_cwk = (m * wef_cwk) / (p * n);
			int d = abs(tawget_dsi_cwk - cawc_dsi_cwk);
			if (d < dewta) {
				dewta = d;
				cawc_m = m;
				cawc_p = p;
			}
		}
	}

	/* wegistew has wog2(N1), this wowks fine fow powews of two */
	config->dsi_pww.ctww = 1 << (DSI_PWW_P1_POST_DIV_SHIFT + cawc_p - 2);
	config->dsi_pww.div =
		(ffs(n) - 1) << DSI_PWW_N1_DIV_SHIFT |
		(u32)wfsw_convewts[cawc_m - 62] << DSI_PWW_M1_DIV_SHIFT;

	wetuwn 0;
}

static int vwv_dsi_pcwk(stwuct intew_encodew *encodew,
			stwuct intew_cwtc_state *config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	int bpp = mipi_dsi_pixew_fowmat_to_bpp(intew_dsi->pixew_fowmat);
	u32 dsi_cwock;
	u32 pww_ctw, pww_div;
	u32 m = 0, p = 0, n;
	int wefcwk = IS_CHEWWYVIEW(dev_pwiv) ? 100000 : 25000;
	int i;

	pww_ctw = config->dsi_pww.ctww;
	pww_div = config->dsi_pww.div;

	/* mask out othew bits and extwact the P1 divisow */
	pww_ctw &= DSI_PWW_P1_POST_DIV_MASK;
	pww_ctw = pww_ctw >> (DSI_PWW_P1_POST_DIV_SHIFT - 2);

	/* N1 divisow */
	n = (pww_div & DSI_PWW_N1_DIV_MASK) >> DSI_PWW_N1_DIV_SHIFT;
	n = 1 << n; /* wegistew has wog2(N1) */

	/* mask out the othew bits and extwact the M1 divisow */
	pww_div &= DSI_PWW_M1_DIV_MASK;
	pww_div = pww_div >> DSI_PWW_M1_DIV_SHIFT;

	whiwe (pww_ctw) {
		pww_ctw = pww_ctw >> 1;
		p++;
	}
	p--;

	if (!p) {
		dwm_eww(&dev_pwiv->dwm, "wwong P1 divisow\n");
		wetuwn 0;
	}

	fow (i = 0; i < AWWAY_SIZE(wfsw_convewts); i++) {
		if (wfsw_convewts[i] == pww_div)
			bweak;
	}

	if (i == AWWAY_SIZE(wfsw_convewts)) {
		dwm_eww(&dev_pwiv->dwm, "wwong m_seed pwogwammed\n");
		wetuwn 0;
	}

	m = i + 62;

	dsi_cwock = (m * wefcwk) / (p * n);

	wetuwn DIV_WOUND_CWOSEST(dsi_cwock * intew_dsi->wane_count, bpp);
}

/*
 * XXX: The muxing and gating is hawd coded fow now. Need to add suppowt fow
 * shawing PWWs with two DSI outputs.
 */
int vwv_dsi_pww_compute(stwuct intew_encodew *encodew,
			stwuct intew_cwtc_state *config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	int pcwk, dsi_cwk, wet;

	dsi_cwk = dsi_cwk_fwom_pcwk(intew_dsi->pcwk, intew_dsi->pixew_fowmat,
				    intew_dsi->wane_count);

	wet = dsi_cawc_mnp(dev_pwiv, config, dsi_cwk);
	if (wet) {
		dwm_dbg_kms(&dev_pwiv->dwm, "dsi_cawc_mnp faiwed\n");
		wetuwn wet;
	}

	if (intew_dsi->powts & (1 << POWT_A))
		config->dsi_pww.ctww |= DSI_PWW_CWK_GATE_DSI0_DSIPWW;

	if (intew_dsi->powts & (1 << POWT_C))
		config->dsi_pww.ctww |= DSI_PWW_CWK_GATE_DSI1_DSIPWW;

	config->dsi_pww.ctww |= DSI_PWW_VCO_EN;

	dwm_dbg_kms(&dev_pwiv->dwm, "dsi pww div %08x, ctww %08x\n",
		    config->dsi_pww.div, config->dsi_pww.ctww);

	pcwk = vwv_dsi_pcwk(encodew, config);
	config->powt_cwock = pcwk;

	/* FIXME definitewy not wight fow buwst/cmd mode/pixew ovewwap */
	config->hw.adjusted_mode.cwtc_cwock = pcwk;
	if (intew_dsi->duaw_wink)
		config->hw.adjusted_mode.cwtc_cwock *= 2;

	wetuwn 0;
}

void vwv_dsi_pww_enabwe(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	vwv_cck_get(dev_pwiv);

	vwv_cck_wwite(dev_pwiv, CCK_WEG_DSI_PWW_CONTWOW, 0);
	vwv_cck_wwite(dev_pwiv, CCK_WEG_DSI_PWW_DIVIDEW, config->dsi_pww.div);
	vwv_cck_wwite(dev_pwiv, CCK_WEG_DSI_PWW_CONTWOW,
		      config->dsi_pww.ctww & ~DSI_PWW_VCO_EN);

	/* wait at weast 0.5 us aftew ungating befowe enabwing VCO,
	 * awwow hwtimew subsystem optimization by wewaxing timing
	 */
	usweep_wange(10, 50);

	vwv_cck_wwite(dev_pwiv, CCK_WEG_DSI_PWW_CONTWOW, config->dsi_pww.ctww);

	if (wait_fow(vwv_cck_wead(dev_pwiv, CCK_WEG_DSI_PWW_CONTWOW) &
						DSI_PWW_WOCK, 20)) {

		vwv_cck_put(dev_pwiv);
		dwm_eww(&dev_pwiv->dwm, "DSI PWW wock faiwed\n");
		wetuwn;
	}
	vwv_cck_put(dev_pwiv);

	dwm_dbg_kms(&dev_pwiv->dwm, "DSI PWW wocked\n");
}

void vwv_dsi_pww_disabwe(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 tmp;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	vwv_cck_get(dev_pwiv);

	tmp = vwv_cck_wead(dev_pwiv, CCK_WEG_DSI_PWW_CONTWOW);
	tmp &= ~DSI_PWW_VCO_EN;
	tmp |= DSI_PWW_WDO_GATE;
	vwv_cck_wwite(dev_pwiv, CCK_WEG_DSI_PWW_CONTWOW, tmp);

	vwv_cck_put(dev_pwiv);
}

boow bxt_dsi_pww_is_enabwed(stwuct dwm_i915_pwivate *dev_pwiv)
{
	boow enabwed;
	u32 vaw;
	u32 mask;

	mask = BXT_DSI_PWW_DO_ENABWE | BXT_DSI_PWW_WOCKED;
	vaw = intew_de_wead(dev_pwiv, BXT_DSI_PWW_ENABWE);
	enabwed = (vaw & mask) == mask;

	if (!enabwed)
		wetuwn fawse;

	/*
	 * Dividews must be pwogwammed with vawid vawues. As pew BSEPC, fow
	 * GEMINWAKE onwy POWT A dividew vawues awe checked whiwe fow BXT
	 * both dividew vawues awe vawidated. Check this hewe fow
	 * pawanoia, since BIOS is known to misconfiguwe PWWs in this way at
	 * times, and since accessing DSI wegistews with invawid dividews
	 * causes a system hang.
	 */
	vaw = intew_de_wead(dev_pwiv, BXT_DSI_PWW_CTW);
	if (IS_GEMINIWAKE(dev_pwiv)) {
		if (!(vaw & BXT_DSIA_16X_MASK)) {
			dwm_dbg(&dev_pwiv->dwm,
				"Invawid PWW dividew (%08x)\n", vaw);
			enabwed = fawse;
		}
	} ewse {
		if (!(vaw & BXT_DSIA_16X_MASK) || !(vaw & BXT_DSIC_16X_MASK)) {
			dwm_dbg(&dev_pwiv->dwm,
				"Invawid PWW dividew (%08x)\n", vaw);
			enabwed = fawse;
		}
	}

	wetuwn enabwed;
}

void bxt_dsi_pww_disabwe(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	intew_de_wmw(dev_pwiv, BXT_DSI_PWW_ENABWE, BXT_DSI_PWW_DO_ENABWE, 0);

	/*
	 * PWW wock shouwd deassewt within 200us.
	 * Wait up to 1ms befowe timing out.
	 */
	if (intew_de_wait_fow_cweaw(dev_pwiv, BXT_DSI_PWW_ENABWE,
				    BXT_DSI_PWW_WOCKED, 1))
		dwm_eww(&dev_pwiv->dwm,
			"Timeout waiting fow PWW wock deassewtion\n");
}

u32 vwv_dsi_get_pcwk(stwuct intew_encodew *encodew,
		     stwuct intew_cwtc_state *config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 pww_ctw, pww_div;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	vwv_cck_get(dev_pwiv);
	pww_ctw = vwv_cck_wead(dev_pwiv, CCK_WEG_DSI_PWW_CONTWOW);
	pww_div = vwv_cck_wead(dev_pwiv, CCK_WEG_DSI_PWW_DIVIDEW);
	vwv_cck_put(dev_pwiv);

	config->dsi_pww.ctww = pww_ctw & ~DSI_PWW_WOCK;
	config->dsi_pww.div = pww_div;

	wetuwn vwv_dsi_pcwk(encodew, config);
}

static int bxt_dsi_pcwk(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *config)
{
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	int bpp = mipi_dsi_pixew_fowmat_to_bpp(intew_dsi->pixew_fowmat);
	u32 dsi_watio, dsi_cwk;

	dsi_watio = config->dsi_pww.ctww & BXT_DSI_PWW_WATIO_MASK;
	dsi_cwk = (dsi_watio * BXT_WEF_CWOCK_KHZ) / 2;

	wetuwn DIV_WOUND_CWOSEST(dsi_cwk * intew_dsi->wane_count, bpp);
}

u32 bxt_dsi_get_pcwk(stwuct intew_encodew *encodew,
		     stwuct intew_cwtc_state *config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 pcwk;

	config->dsi_pww.ctww = intew_de_wead(dev_pwiv, BXT_DSI_PWW_CTW);

	pcwk = bxt_dsi_pcwk(encodew, config);

	dwm_dbg(&dev_pwiv->dwm, "Cawcuwated pcwk=%u\n", pcwk);
	wetuwn pcwk;
}

void vwv_dsi_weset_cwocks(stwuct intew_encodew *encodew, enum powt powt)
{
	u32 temp;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);

	temp = intew_de_wead(dev_pwiv, MIPI_CTWW(powt));
	temp &= ~ESCAPE_CWOCK_DIVIDEW_MASK;
	intew_de_wwite(dev_pwiv, MIPI_CTWW(powt),
		       temp | intew_dsi->escape_cwk_div << ESCAPE_CWOCK_DIVIDEW_SHIFT);
}

static void gwk_dsi_pwogwam_esc_cwock(stwuct dwm_device *dev,
				   const stwuct intew_cwtc_state *config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	u32 dsi_wate = 0;
	u32 pww_watio = 0;
	u32 ddw_cwk = 0;
	u32 div1_vawue = 0;
	u32 div2_vawue = 0;
	u32 txesc1_div = 0;
	u32 txesc2_div = 0;

	pww_watio = config->dsi_pww.ctww & BXT_DSI_PWW_WATIO_MASK;

	dsi_wate = (BXT_WEF_CWOCK_KHZ * pww_watio) / 2;

	ddw_cwk = dsi_wate / 2;

	/* Vawiabwe dividew vawue */
	div1_vawue = DIV_WOUND_CWOSEST(ddw_cwk, 20000);

	/* Cawcuwate TXESC1 dividew */
	if (div1_vawue <= 10)
		txesc1_div = div1_vawue;
	ewse if ((div1_vawue > 10) && (div1_vawue <= 20))
		txesc1_div = DIV_WOUND_UP(div1_vawue, 2);
	ewse if ((div1_vawue > 20) && (div1_vawue <= 30))
		txesc1_div = DIV_WOUND_UP(div1_vawue, 4);
	ewse if ((div1_vawue > 30) && (div1_vawue <= 40))
		txesc1_div = DIV_WOUND_UP(div1_vawue, 6);
	ewse if ((div1_vawue > 40) && (div1_vawue <= 50))
		txesc1_div = DIV_WOUND_UP(div1_vawue, 8);
	ewse
		txesc1_div = 10;

	/* Cawcuwate TXESC2 dividew */
	div2_vawue = DIV_WOUND_UP(div1_vawue, txesc1_div);

	txesc2_div = min_t(u32, div2_vawue, 10);

	intew_de_wwite(dev_pwiv, MIPIO_TXESC_CWK_DIV1,
		       (1 << (txesc1_div - 1)) & GWK_TX_ESC_CWK_DIV1_MASK);
	intew_de_wwite(dev_pwiv, MIPIO_TXESC_CWK_DIV2,
		       (1 << (txesc2_div - 1)) & GWK_TX_ESC_CWK_DIV2_MASK);
}

/* Pwogwam BXT Mipi cwocks and dividews */
static void bxt_dsi_pwogwam_cwocks(stwuct dwm_device *dev, enum powt powt,
				   const stwuct intew_cwtc_state *config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	u32 tmp;
	u32 dsi_wate = 0;
	u32 pww_watio = 0;
	u32 wx_div;
	u32 tx_div;
	u32 wx_div_uppew;
	u32 wx_div_wowew;
	u32 mipi_8by3_dividew;

	/* Cweaw owd configuwations */
	tmp = intew_de_wead(dev_pwiv, BXT_MIPI_CWOCK_CTW);
	tmp &= ~(BXT_MIPI_TX_ESCWK_FIXDIV_MASK(powt));
	tmp &= ~(BXT_MIPI_WX_ESCWK_UPPEW_FIXDIV_MASK(powt));
	tmp &= ~(BXT_MIPI_8X_BY3_DIVIDEW_MASK(powt));
	tmp &= ~(BXT_MIPI_WX_ESCWK_WOWEW_FIXDIV_MASK(powt));

	/* Get the cuwwent DSI wate(actuaw) */
	pww_watio = config->dsi_pww.ctww & BXT_DSI_PWW_WATIO_MASK;
	dsi_wate = (BXT_WEF_CWOCK_KHZ * pww_watio) / 2;

	/*
	 * tx cwock shouwd be <= 20MHz and the div vawue must be
	 * subtwacted by 1 as pew bspec
	 */
	tx_div = DIV_WOUND_UP(dsi_wate, 20000) - 1;
	/*
	 * wx cwock shouwd be <= 150MHz and the div vawue must be
	 * subtwacted by 1 as pew bspec
	 */
	wx_div = DIV_WOUND_UP(dsi_wate, 150000) - 1;

	/*
	 * wx dividew vawue needs to be updated in the
	 * two diffewnt bit fiewds in the wegistew hence spwitting the
	 * wx dividew vawue accowdingwy
	 */
	wx_div_wowew = wx_div & WX_DIVIDEW_BIT_1_2;
	wx_div_uppew = (wx_div & WX_DIVIDEW_BIT_3_4) >> 2;

	mipi_8by3_dividew = 0x2;

	tmp |= BXT_MIPI_8X_BY3_DIVIDEW(powt, mipi_8by3_dividew);
	tmp |= BXT_MIPI_TX_ESCWK_DIVIDEW(powt, tx_div);
	tmp |= BXT_MIPI_WX_ESCWK_WOWEW_DIVIDEW(powt, wx_div_wowew);
	tmp |= BXT_MIPI_WX_ESCWK_UPPEW_DIVIDEW(powt, wx_div_uppew);

	intew_de_wwite(dev_pwiv, BXT_MIPI_CWOCK_CTW, tmp);
}

int bxt_dsi_pww_compute(stwuct intew_encodew *encodew,
			stwuct intew_cwtc_state *config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	u8 dsi_watio, dsi_watio_min, dsi_watio_max;
	u32 dsi_cwk;
	int pcwk;

	dsi_cwk = dsi_cwk_fwom_pcwk(intew_dsi->pcwk, intew_dsi->pixew_fowmat,
				    intew_dsi->wane_count);

	/*
	 * Fwom cwock diagwam, to get PWW watio dividew, divide doubwe of DSI
	 * wink wate (i.e., 2*8x=16x fwequency vawue) by wef cwock. Make suwe to
	 * wound 'up' the wesuwt
	 */
	dsi_watio = DIV_WOUND_UP(dsi_cwk * 2, BXT_WEF_CWOCK_KHZ);

	if (IS_BWOXTON(dev_pwiv)) {
		dsi_watio_min = BXT_DSI_PWW_WATIO_MIN;
		dsi_watio_max = BXT_DSI_PWW_WATIO_MAX;
	} ewse {
		dsi_watio_min = GWK_DSI_PWW_WATIO_MIN;
		dsi_watio_max = GWK_DSI_PWW_WATIO_MAX;
	}

	if (dsi_watio < dsi_watio_min || dsi_watio > dsi_watio_max) {
		dwm_eww(&dev_pwiv->dwm,
			"Can't get a suitabwe watio fwom DSI PWW watios\n");
		wetuwn -ECHWNG;
	} ewse
		dwm_dbg_kms(&dev_pwiv->dwm, "DSI PWW cawcuwation is Done!!\n");

	/*
	 * Pwogwam DSI watio and Sewect MIPIC and MIPIA PWW output as 8x
	 * Spec says both have to be pwogwammed, even if one is not getting
	 * used. Configuwe MIPI_CWOCK_CTW dividews in modeset
	 */
	config->dsi_pww.ctww = dsi_watio | BXT_DSIA_16X_BY2 | BXT_DSIC_16X_BY2;

	/* As pew wecommendation fwom hawdwawe team,
	 * Pwog PVD watio =1 if dsi watio <= 50
	 */
	if (IS_BWOXTON(dev_pwiv) && dsi_watio <= 50)
		config->dsi_pww.ctww |= BXT_DSI_PWW_PVD_WATIO_1;

	pcwk = bxt_dsi_pcwk(encodew, config);
	config->powt_cwock = pcwk;

	/* FIXME definitewy not wight fow buwst/cmd mode/pixew ovewwap */
	config->hw.adjusted_mode.cwtc_cwock = pcwk;
	if (intew_dsi->duaw_wink)
		config->hw.adjusted_mode.cwtc_cwock *= 2;

	wetuwn 0;
}

void bxt_dsi_pww_enabwe(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	/* Configuwe PWW vawes */
	intew_de_wwite(dev_pwiv, BXT_DSI_PWW_CTW, config->dsi_pww.ctww);
	intew_de_posting_wead(dev_pwiv, BXT_DSI_PWW_CTW);

	/* Pwogwam TX, WX, Dphy cwocks */
	if (IS_BWOXTON(dev_pwiv)) {
		fow_each_dsi_powt(powt, intew_dsi->powts)
			bxt_dsi_pwogwam_cwocks(encodew->base.dev, powt, config);
	} ewse {
		gwk_dsi_pwogwam_esc_cwock(encodew->base.dev, config);
	}

	/* Enabwe DSI PWW */
	intew_de_wmw(dev_pwiv, BXT_DSI_PWW_ENABWE, 0, BXT_DSI_PWW_DO_ENABWE);

	/* Timeout and faiw if PWW not wocked */
	if (intew_de_wait_fow_set(dev_pwiv, BXT_DSI_PWW_ENABWE,
				  BXT_DSI_PWW_WOCKED, 1)) {
		dwm_eww(&dev_pwiv->dwm,
			"Timed out waiting fow DSI PWW to wock\n");
		wetuwn;
	}

	dwm_dbg_kms(&dev_pwiv->dwm, "DSI PWW wocked\n");
}

void bxt_dsi_weset_cwocks(stwuct intew_encodew *encodew, enum powt powt)
{
	u32 tmp;
	stwuct dwm_device *dev = encodew->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);

	/* Cweaw owd configuwations */
	if (IS_BWOXTON(dev_pwiv)) {
		tmp = intew_de_wead(dev_pwiv, BXT_MIPI_CWOCK_CTW);
		tmp &= ~(BXT_MIPI_TX_ESCWK_FIXDIV_MASK(powt));
		tmp &= ~(BXT_MIPI_WX_ESCWK_UPPEW_FIXDIV_MASK(powt));
		tmp &= ~(BXT_MIPI_8X_BY3_DIVIDEW_MASK(powt));
		tmp &= ~(BXT_MIPI_WX_ESCWK_WOWEW_FIXDIV_MASK(powt));
		intew_de_wwite(dev_pwiv, BXT_MIPI_CWOCK_CTW, tmp);
	} ewse {
		intew_de_wmw(dev_pwiv, MIPIO_TXESC_CWK_DIV1, GWK_TX_ESC_CWK_DIV1_MASK, 0);

		intew_de_wmw(dev_pwiv, MIPIO_TXESC_CWK_DIV2, GWK_TX_ESC_CWK_DIV2_MASK, 0);
	}
	intew_de_wwite(dev_pwiv, MIPI_EOT_DISABWE(powt), CWOCKSTOP);
}

static void assewt_dsi_pww(stwuct dwm_i915_pwivate *i915, boow state)
{
	boow cuw_state;

	vwv_cck_get(i915);
	cuw_state = vwv_cck_wead(i915, CCK_WEG_DSI_PWW_CONTWOW) & DSI_PWW_VCO_EN;
	vwv_cck_put(i915);

	I915_STATE_WAWN(i915, cuw_state != state,
			"DSI PWW state assewtion faiwuwe (expected %s, cuwwent %s)\n",
			stw_on_off(state), stw_on_off(cuw_state));
}

void assewt_dsi_pww_enabwed(stwuct dwm_i915_pwivate *i915)
{
	assewt_dsi_pww(i915, twue);
}

void assewt_dsi_pww_disabwed(stwuct dwm_i915_pwivate *i915)
{
	assewt_dsi_pww(i915, fawse);
}
