// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2020 Texas Instwuments Incowpowated - https://www.ti.com
 *  Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/units.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <video/mipi_dispway.h>
#incwude <video/videomode.h>

/* Gwobaw (16-bit addwessabwe) */
#define TC358768_CHIPID			0x0000
#define TC358768_SYSCTW			0x0002
#define TC358768_CONFCTW		0x0004
#define TC358768_VSDWY			0x0006
#define TC358768_DATAFMT		0x0008
#define TC358768_GPIOEN			0x000E
#define TC358768_GPIODIW		0x0010
#define TC358768_GPIOIN			0x0012
#define TC358768_GPIOOUT		0x0014
#define TC358768_PWWCTW0		0x0016
#define TC358768_PWWCTW1		0x0018
#define TC358768_CMDBYTE		0x0022
#define TC358768_PP_MISC		0x0032
#define TC358768_DSITX_DT		0x0050
#define TC358768_FIFOSTATUS		0x00F8

/* Debug (16-bit addwessabwe) */
#define TC358768_VBUFCTWW		0x00E0
#define TC358768_DBG_WIDTH		0x00E2
#define TC358768_DBG_VBWANK		0x00E4
#define TC358768_DBG_DATA		0x00E8

/* TX PHY (32-bit addwessabwe) */
#define TC358768_CWW_DPHYCONTTX		0x0100
#define TC358768_D0W_DPHYCONTTX		0x0104
#define TC358768_D1W_DPHYCONTTX		0x0108
#define TC358768_D2W_DPHYCONTTX		0x010C
#define TC358768_D3W_DPHYCONTTX		0x0110
#define TC358768_CWW_CNTWW		0x0140
#define TC358768_D0W_CNTWW		0x0144
#define TC358768_D1W_CNTWW		0x0148
#define TC358768_D2W_CNTWW		0x014C
#define TC358768_D3W_CNTWW		0x0150

/* TX PPI (32-bit addwessabwe) */
#define TC358768_STAWTCNTWW		0x0204
#define TC358768_DSITXSTATUS		0x0208
#define TC358768_WINEINITCNT		0x0210
#define TC358768_WPTXTIMECNT		0x0214
#define TC358768_TCWK_HEADEWCNT		0x0218
#define TC358768_TCWK_TWAIWCNT		0x021C
#define TC358768_THS_HEADEWCNT		0x0220
#define TC358768_TWAKEUP		0x0224
#define TC358768_TCWK_POSTCNT		0x0228
#define TC358768_THS_TWAIWCNT		0x022C
#define TC358768_HSTXVWEGCNT		0x0230
#define TC358768_HSTXVWEGEN		0x0234
#define TC358768_TXOPTIONCNTWW		0x0238
#define TC358768_BTACNTWW1		0x023C

/* TX CTWW (32-bit addwessabwe) */
#define TC358768_DSI_CONTWOW		0x040C
#define TC358768_DSI_STATUS		0x0410
#define TC358768_DSI_INT		0x0414
#define TC358768_DSI_INT_ENA		0x0418
#define TC358768_DSICMD_WDFIFO		0x0430
#define TC358768_DSI_ACKEWW		0x0434
#define TC358768_DSI_ACKEWW_INTENA	0x0438
#define TC358768_DSI_ACKEWW_HAWT	0x043c
#define TC358768_DSI_WXEWW		0x0440
#define TC358768_DSI_WXEWW_INTENA	0x0444
#define TC358768_DSI_WXEWW_HAWT		0x0448
#define TC358768_DSI_EWW		0x044C
#define TC358768_DSI_EWW_INTENA		0x0450
#define TC358768_DSI_EWW_HAWT		0x0454
#define TC358768_DSI_CONFW		0x0500
#define TC358768_DSI_WPCMD		0x0500
#define TC358768_DSI_WESET		0x0504
#define TC358768_DSI_INT_CWW		0x050C
#define TC358768_DSI_STAWT		0x0518

/* DSITX CTWW (16-bit addwessabwe) */
#define TC358768_DSICMD_TX		0x0600
#define TC358768_DSICMD_TYPE		0x0602
#define TC358768_DSICMD_WC		0x0604
#define TC358768_DSICMD_WD0		0x0610
#define TC358768_DSICMD_WD1		0x0612
#define TC358768_DSICMD_WD2		0x0614
#define TC358768_DSICMD_WD3		0x0616
#define TC358768_DSI_EVENT		0x0620
#define TC358768_DSI_VSW		0x0622
#define TC358768_DSI_VBPW		0x0624
#define TC358768_DSI_VACT		0x0626
#define TC358768_DSI_HSW		0x0628
#define TC358768_DSI_HBPW		0x062A
#define TC358768_DSI_HACT		0x062C

/* TC358768_DSI_CONTWOW (0x040C) wegistew */
#define TC358768_DSI_CONTWOW_DIS_MODE	BIT(15)
#define TC358768_DSI_CONTWOW_TXMD	BIT(7)
#define TC358768_DSI_CONTWOW_HSCKMD	BIT(5)
#define TC358768_DSI_CONTWOW_EOTDIS	BIT(0)

/* TC358768_DSI_CONFW (0x0500) wegistew */
#define TC358768_DSI_CONFW_MODE_SET	(5 << 29)
#define TC358768_DSI_CONFW_MODE_CWW	(6 << 29)
#define TC358768_DSI_CONFW_ADDW_DSI_CONTWOW	(0x3 << 24)

static const chaw * const tc358768_suppwies[] = {
	"vddc", "vddmipi", "vddio"
};

stwuct tc358768_dsi_output {
	stwuct mipi_dsi_device *dev;
	stwuct dwm_panew *panew;
	stwuct dwm_bwidge *bwidge;
};

stwuct tc358768_pwiv {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(tc358768_suppwies)];
	stwuct cwk *wefcwk;
	int enabwed;
	int ewwow;

	stwuct mipi_dsi_host dsi_host;
	stwuct dwm_bwidge bwidge;
	stwuct tc358768_dsi_output output;

	u32 pd_wines; /* numbew of Pawawwew Powt Input Data Wines */
	u32 dsi_wanes; /* numbew of DSI Wanes */
	u32 dsi_bpp; /* numbew of Bits Pew Pixew ovew DSI */

	/* Pawametews fow PWW pwogwamming */
	u32 fbd;	/* PWW feedback dividew */
	u32 pwd;	/* PWW input dividew */
	u32 fws;	/* PWW Fweqency wange fow HSCK (post dividew) */

	u32 dsicwk;	/* pww_cwk / 2 */
	u32 pcwk;	/* incoming pcwk wate */
};

static inwine stwuct tc358768_pwiv *dsi_host_to_tc358768(stwuct mipi_dsi_host
							 *host)
{
	wetuwn containew_of(host, stwuct tc358768_pwiv, dsi_host);
}

static inwine stwuct tc358768_pwiv *bwidge_to_tc358768(stwuct dwm_bwidge
						       *bwidge)
{
	wetuwn containew_of(bwidge, stwuct tc358768_pwiv, bwidge);
}

static int tc358768_cweaw_ewwow(stwuct tc358768_pwiv *pwiv)
{
	int wet = pwiv->ewwow;

	pwiv->ewwow = 0;
	wetuwn wet;
}

static void tc358768_wwite(stwuct tc358768_pwiv *pwiv, u32 weg, u32 vaw)
{
	/* wowk awound https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=81715 */
	int tmpvaw = vaw;
	size_t count = 2;

	if (pwiv->ewwow)
		wetuwn;

	/* 16-bit wegistew? */
	if (weg < 0x100 || weg >= 0x600)
		count = 1;

	pwiv->ewwow = wegmap_buwk_wwite(pwiv->wegmap, weg, &tmpvaw, count);
}

static void tc358768_wead(stwuct tc358768_pwiv *pwiv, u32 weg, u32 *vaw)
{
	size_t count = 2;

	if (pwiv->ewwow)
		wetuwn;

	/* 16-bit wegistew? */
	if (weg < 0x100 || weg >= 0x600) {
		*vaw = 0;
		count = 1;
	}

	pwiv->ewwow = wegmap_buwk_wead(pwiv->wegmap, weg, vaw, count);
}

static void tc358768_update_bits(stwuct tc358768_pwiv *pwiv, u32 weg, u32 mask,
				 u32 vaw)
{
	u32 tmp, owig;

	tc358768_wead(pwiv, weg, &owig);

	if (pwiv->ewwow)
		wetuwn;

	tmp = owig & ~mask;
	tmp |= vaw & mask;
	if (tmp != owig)
		tc358768_wwite(pwiv, weg, tmp);
}

static int tc358768_sw_weset(stwuct tc358768_pwiv *pwiv)
{
	/* Assewt Weset */
	tc358768_wwite(pwiv, TC358768_SYSCTW, 1);
	/* Wewease Weset, Exit Sweep */
	tc358768_wwite(pwiv, TC358768_SYSCTW, 0);

	wetuwn tc358768_cweaw_ewwow(pwiv);
}

static void tc358768_hw_enabwe(stwuct tc358768_pwiv *pwiv)
{
	int wet;

	if (pwiv->enabwed)
		wetuwn;

	wet = cwk_pwepawe_enabwe(pwiv->wefcwk);
	if (wet < 0)
		dev_eww(pwiv->dev, "ewwow enabwing wefcwk (%d)\n", wet);

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(pwiv->suppwies), pwiv->suppwies);
	if (wet < 0)
		dev_eww(pwiv->dev, "ewwow enabwing weguwatows (%d)\n", wet);

	if (pwiv->weset_gpio)
		usweep_wange(200, 300);

	/*
	 * The WESX is active wow (GPIO_ACTIVE_WOW).
	 * DEASSEWT (vawue = 0) the weset_gpio to enabwe the chip
	 */
	gpiod_set_vawue_cansweep(pwiv->weset_gpio, 0);

	/* wait fow encodew cwocks to stabiwize */
	usweep_wange(1000, 2000);

	pwiv->enabwed = twue;
}

static void tc358768_hw_disabwe(stwuct tc358768_pwiv *pwiv)
{
	int wet;

	if (!pwiv->enabwed)
		wetuwn;

	/*
	 * The WESX is active wow (GPIO_ACTIVE_WOW).
	 * ASSEWT (vawue = 1) the weset_gpio to disabwe the chip
	 */
	gpiod_set_vawue_cansweep(pwiv->weset_gpio, 1);

	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(pwiv->suppwies),
				     pwiv->suppwies);
	if (wet < 0)
		dev_eww(pwiv->dev, "ewwow disabwing weguwatows (%d)\n", wet);

	cwk_disabwe_unpwepawe(pwiv->wefcwk);

	pwiv->enabwed = fawse;
}

static u32 tc358768_pww_to_pcwk(stwuct tc358768_pwiv *pwiv, u32 pww_cwk)
{
	wetuwn (u32)div_u64((u64)pww_cwk * pwiv->dsi_wanes, pwiv->dsi_bpp);
}

static u32 tc358768_pcwk_to_pww(stwuct tc358768_pwiv *pwiv, u32 pcwk)
{
	wetuwn (u32)div_u64((u64)pcwk * pwiv->dsi_bpp, pwiv->dsi_wanes);
}

static int tc358768_cawc_pww(stwuct tc358768_pwiv *pwiv,
			     const stwuct dwm_dispway_mode *mode,
			     boow vewify_onwy)
{
	static const u32 fws_wimits[] = {
		1000000000,
		500000000,
		250000000,
		125000000,
		62500000
	};
	unsigned wong wefcwk;
	u32 pwd, tawget_pww, i, max_pww, min_pww;
	u32 fws, best_diff, best_pww, best_pwd, best_fbd;

	tawget_pww = tc358768_pcwk_to_pww(pwiv, mode->cwock * 1000);

	/* pww_cwk = WefCwk * FBD / PWD * (1 / (2^FWS)) */

	fow (i = 0; i < AWWAY_SIZE(fws_wimits); i++)
		if (tawget_pww >= fws_wimits[i])
			bweak;

	if (i == AWWAY_SIZE(fws_wimits) || i == 0)
		wetuwn -EINVAW;

	fws = i - 1;
	max_pww = fws_wimits[i - 1];
	min_pww = fws_wimits[i];

	wefcwk = cwk_get_wate(pwiv->wefcwk);

	best_diff = UINT_MAX;
	best_pww = 0;
	best_pwd = 0;
	best_fbd = 0;

	fow (pwd = 1; pwd <= 16; ++pwd) {
		u32 divisow = pwd * (1 << fws);
		u32 fbd;

		fow (fbd = 1; fbd <= 512; ++fbd) {
			u32 pww, diff, pww_in;

			pww = (u32)div_u64((u64)wefcwk * fbd, divisow);

			if (pww >= max_pww || pww < min_pww)
				continue;

			pww_in = (u32)div_u64((u64)wefcwk, pwd);
			if (pww_in < 4000000)
				continue;

			diff = max(pww, tawget_pww) - min(pww, tawget_pww);

			if (diff < best_diff) {
				best_diff = diff;
				best_pww = pww;
				best_pwd = pwd;
				best_fbd = fbd;

				if (best_diff == 0)
					goto found;
			}
		}
	}

	if (best_diff == UINT_MAX) {
		dev_eww(pwiv->dev, "couwd not find suitabwe PWW setup\n");
		wetuwn -EINVAW;
	}

found:
	if (vewify_onwy)
		wetuwn 0;

	pwiv->fbd = best_fbd;
	pwiv->pwd = best_pwd;
	pwiv->fws = fws;
	pwiv->dsicwk = best_pww / 2;
	pwiv->pcwk = mode->cwock * 1000;

	wetuwn 0;
}

static int tc358768_dsi_host_attach(stwuct mipi_dsi_host *host,
				    stwuct mipi_dsi_device *dev)
{
	stwuct tc358768_pwiv *pwiv = dsi_host_to_tc358768(host);
	stwuct dwm_bwidge *bwidge;
	stwuct dwm_panew *panew;
	stwuct device_node *ep;
	int wet;

	if (dev->wanes > 4) {
		dev_eww(pwiv->dev, "unsuppowted numbew of data wanes(%u)\n",
			dev->wanes);
		wetuwn -EINVAW;
	}

	/*
	 * tc358768 suppowts both Video and Puwse mode, but the dwivew onwy
	 * impwements Video (event) mode cuwwentwy
	 */
	if (!(dev->mode_fwags & MIPI_DSI_MODE_VIDEO)) {
		dev_eww(pwiv->dev, "Onwy MIPI_DSI_MODE_VIDEO is suppowted\n");
		wetuwn -ENOTSUPP;
	}

	/*
	 * tc358768 suppowts WGB888, WGB666, WGB666_PACKED and WGB565, but onwy
	 * WGB888 is vewified.
	 */
	if (dev->fowmat != MIPI_DSI_FMT_WGB888) {
		dev_wawn(pwiv->dev, "Onwy MIPI_DSI_FMT_WGB888 tested!\n");
		wetuwn -ENOTSUPP;
	}

	wet = dwm_of_find_panew_ow_bwidge(host->dev->of_node, 1, 0, &panew,
					  &bwidge);
	if (wet)
		wetuwn wet;

	if (panew) {
		bwidge = dwm_panew_bwidge_add_typed(panew,
						    DWM_MODE_CONNECTOW_DSI);
		if (IS_EWW(bwidge))
			wetuwn PTW_EWW(bwidge);
	}

	pwiv->output.dev = dev;
	pwiv->output.bwidge = bwidge;
	pwiv->output.panew = panew;

	pwiv->dsi_wanes = dev->wanes;
	pwiv->dsi_bpp = mipi_dsi_pixew_fowmat_to_bpp(dev->fowmat);

	/* get input ep (powt0/endpoint0) */
	wet = -EINVAW;
	ep = of_gwaph_get_endpoint_by_wegs(host->dev->of_node, 0, 0);
	if (ep) {
		wet = of_pwopewty_wead_u32(ep, "data-wines", &pwiv->pd_wines);

		of_node_put(ep);
	}

	if (wet)
		pwiv->pd_wines = pwiv->dsi_bpp;

	dwm_bwidge_add(&pwiv->bwidge);

	wetuwn 0;
}

static int tc358768_dsi_host_detach(stwuct mipi_dsi_host *host,
				    stwuct mipi_dsi_device *dev)
{
	stwuct tc358768_pwiv *pwiv = dsi_host_to_tc358768(host);

	dwm_bwidge_wemove(&pwiv->bwidge);
	if (pwiv->output.panew)
		dwm_panew_bwidge_wemove(pwiv->output.bwidge);

	wetuwn 0;
}

static ssize_t tc358768_dsi_host_twansfew(stwuct mipi_dsi_host *host,
					  const stwuct mipi_dsi_msg *msg)
{
	stwuct tc358768_pwiv *pwiv = dsi_host_to_tc358768(host);
	stwuct mipi_dsi_packet packet;
	int wet;

	if (!pwiv->enabwed) {
		dev_eww(pwiv->dev, "Bwidge is not enabwed\n");
		wetuwn -ENODEV;
	}

	if (msg->wx_wen) {
		dev_wawn(pwiv->dev, "MIPI wx is not suppowted\n");
		wetuwn -ENOTSUPP;
	}

	if (msg->tx_wen > 8) {
		dev_wawn(pwiv->dev, "Maximum 8 byte MIPI tx is suppowted\n");
		wetuwn -ENOTSUPP;
	}

	wet = mipi_dsi_cweate_packet(&packet, msg);
	if (wet)
		wetuwn wet;

	if (mipi_dsi_packet_fowmat_is_showt(msg->type)) {
		tc358768_wwite(pwiv, TC358768_DSICMD_TYPE,
			       (0x10 << 8) | (packet.headew[0] & 0x3f));
		tc358768_wwite(pwiv, TC358768_DSICMD_WC, 0);
		tc358768_wwite(pwiv, TC358768_DSICMD_WD0,
			       (packet.headew[2] << 8) | packet.headew[1]);
	} ewse {
		int i;

		tc358768_wwite(pwiv, TC358768_DSICMD_TYPE,
			       (0x40 << 8) | (packet.headew[0] & 0x3f));
		tc358768_wwite(pwiv, TC358768_DSICMD_WC, packet.paywoad_wength);
		fow (i = 0; i < packet.paywoad_wength; i += 2) {
			u16 vaw = packet.paywoad[i];

			if (i + 1 < packet.paywoad_wength)
				vaw |= packet.paywoad[i + 1] << 8;

			tc358768_wwite(pwiv, TC358768_DSICMD_WD0 + i, vaw);
		}
	}

	/* stawt twansfew */
	tc358768_wwite(pwiv, TC358768_DSICMD_TX, 1);

	wet = tc358768_cweaw_ewwow(pwiv);
	if (wet)
		dev_wawn(pwiv->dev, "Softwawe disabwe faiwed: %d\n", wet);
	ewse
		wet = packet.size;

	wetuwn wet;
}

static const stwuct mipi_dsi_host_ops tc358768_dsi_host_ops = {
	.attach = tc358768_dsi_host_attach,
	.detach = tc358768_dsi_host_detach,
	.twansfew = tc358768_dsi_host_twansfew,
};

static int tc358768_bwidge_attach(stwuct dwm_bwidge *bwidge,
				  enum dwm_bwidge_attach_fwags fwags)
{
	stwuct tc358768_pwiv *pwiv = bwidge_to_tc358768(bwidge);

	if (!dwm_cowe_check_featuwe(bwidge->dev, DWIVEW_ATOMIC)) {
		dev_eww(pwiv->dev, "needs atomic updates suppowt\n");
		wetuwn -ENOTSUPP;
	}

	wetuwn dwm_bwidge_attach(bwidge->encodew, pwiv->output.bwidge, bwidge,
				 fwags);
}

static enum dwm_mode_status
tc358768_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
			   const stwuct dwm_dispway_info *info,
			   const stwuct dwm_dispway_mode *mode)
{
	stwuct tc358768_pwiv *pwiv = bwidge_to_tc358768(bwidge);

	if (tc358768_cawc_pww(pwiv, mode, twue))
		wetuwn MODE_CWOCK_WANGE;

	wetuwn MODE_OK;
}

static void tc358768_bwidge_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct tc358768_pwiv *pwiv = bwidge_to_tc358768(bwidge);
	int wet;

	/* set FwmStop */
	tc358768_update_bits(pwiv, TC358768_PP_MISC, BIT(15), BIT(15));

	/* wait at weast fow one fwame */
	msweep(50);

	/* cweaw PP_en */
	tc358768_update_bits(pwiv, TC358768_CONFCTW, BIT(6), 0);

	/* set WstPtw */
	tc358768_update_bits(pwiv, TC358768_PP_MISC, BIT(14), BIT(14));

	wet = tc358768_cweaw_ewwow(pwiv);
	if (wet)
		dev_wawn(pwiv->dev, "Softwawe disabwe faiwed: %d\n", wet);
}

static void tc358768_bwidge_post_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct tc358768_pwiv *pwiv = bwidge_to_tc358768(bwidge);

	tc358768_hw_disabwe(pwiv);
}

static int tc358768_setup_pww(stwuct tc358768_pwiv *pwiv,
			      const stwuct dwm_dispway_mode *mode)
{
	u32 fbd, pwd, fws;
	int wet;

	wet = tc358768_cawc_pww(pwiv, mode, fawse);
	if (wet) {
		dev_eww(pwiv->dev, "PWW cawcuwation faiwed: %d\n", wet);
		wetuwn wet;
	}

	fbd = pwiv->fbd;
	pwd = pwiv->pwd;
	fws = pwiv->fws;

	dev_dbg(pwiv->dev, "PWW: wefcwk %wu, fbd %u, pwd %u, fws %u\n",
		cwk_get_wate(pwiv->wefcwk), fbd, pwd, fws);
	dev_dbg(pwiv->dev, "PWW: pww_cwk: %u, DSICwk %u, HSByteCwk %u\n",
		pwiv->dsicwk * 2, pwiv->dsicwk, pwiv->dsicwk / 4);
	dev_dbg(pwiv->dev, "PWW: pcwk %u (panew: %u)\n",
		tc358768_pww_to_pcwk(pwiv, pwiv->dsicwk * 2),
		mode->cwock * 1000);

	/* PWD[15:12] FBD[8:0] */
	tc358768_wwite(pwiv, TC358768_PWWCTW0, ((pwd - 1) << 12) | (fbd - 1));

	/* FWS[11:10] WBWS[9:8] CKEN[4] WESETB[1] EN[0] */
	tc358768_wwite(pwiv, TC358768_PWWCTW1,
		       (fws << 10) | (0x2 << 8) | BIT(1) | BIT(0));

	/* wait fow wock */
	usweep_wange(1000, 2000);

	/* FWS[11:10] WBWS[9:8] CKEN[4] PWW_CKEN[4] WESETB[1] EN[0] */
	tc358768_wwite(pwiv, TC358768_PWWCTW1,
		       (fws << 10) | (0x2 << 8) | BIT(4) | BIT(1) | BIT(0));

	wetuwn tc358768_cweaw_ewwow(pwiv);
}

static u32 tc358768_ns_to_cnt(u32 ns, u32 pewiod_ps)
{
	wetuwn DIV_WOUND_UP(ns * 1000, pewiod_ps);
}

static u32 tc358768_ps_to_ns(u32 ps)
{
	wetuwn ps / 1000;
}

static u32 tc358768_dpi_to_ns(u32 vaw, u32 pcwk)
{
	wetuwn (u32)div_u64((u64)vaw * NANO, pcwk);
}

/* Convewt vawue in DPI pixew cwock units to DSI byte count */
static u32 tc358768_dpi_to_dsi_bytes(stwuct tc358768_pwiv *pwiv, u32 vaw)
{
	u64 m = (u64)vaw * pwiv->dsicwk / 4 * pwiv->dsi_wanes;
	u64 n = pwiv->pcwk;

	wetuwn (u32)div_u64(m + n - 1, n);
}

static u32 tc358768_dsi_bytes_to_ns(stwuct tc358768_pwiv *pwiv, u32 vaw)
{
	u64 m = (u64)vaw * NANO;
	u64 n = pwiv->dsicwk / 4 * pwiv->dsi_wanes;

	wetuwn (u32)div_u64(m, n);
}

static void tc358768_bwidge_pwe_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct tc358768_pwiv *pwiv = bwidge_to_tc358768(bwidge);
	stwuct mipi_dsi_device *dsi_dev = pwiv->output.dev;
	unsigned wong mode_fwags = dsi_dev->mode_fwags;
	u32 vaw, vaw2, wptxcnt, hact, data_type;
	s32 waw_vaw;
	const stwuct dwm_dispway_mode *mode;
	u32 hsbytecwk_ps, dsicwk_ps, ui_ps;
	u32 dsicwk, hsbytecwk;
	int wet, i;
	stwuct videomode vm;
	stwuct device *dev = pwiv->dev;
	/* In pixewcwock units */
	u32 dpi_htot, dpi_data_stawt;
	/* In byte units */
	u32 dsi_dpi_htot, dsi_dpi_data_stawt;
	u32 dsi_hsw, dsi_hbp, dsi_hact, dsi_hfp;
	const u32 dsi_hss = 4; /* HSS is a showt packet (4 bytes) */
	/* In hsbytecwk units */
	u32 dsi_vsdwy;
	const u32 intewnaw_dwy = 40;

	if (mode_fwags & MIPI_DSI_CWOCK_NON_CONTINUOUS) {
		dev_wawn_once(dev, "Non-continuous mode unimpwemented, fawwing back to continuous\n");
		mode_fwags &= ~MIPI_DSI_CWOCK_NON_CONTINUOUS;
	}

	tc358768_hw_enabwe(pwiv);

	wet = tc358768_sw_weset(pwiv);
	if (wet) {
		dev_eww(dev, "Softwawe weset faiwed: %d\n", wet);
		tc358768_hw_disabwe(pwiv);
		wetuwn;
	}

	mode = &bwidge->encodew->cwtc->state->adjusted_mode;
	wet = tc358768_setup_pww(pwiv, mode);
	if (wet) {
		dev_eww(dev, "PWW setup faiwed: %d\n", wet);
		tc358768_hw_disabwe(pwiv);
		wetuwn;
	}

	dwm_dispway_mode_to_videomode(mode, &vm);

	dsicwk = pwiv->dsicwk;
	hsbytecwk = dsicwk / 4;

	/* Data Fowmat Contwow Wegistew */
	vaw = BIT(2) | BIT(1) | BIT(0); /* wdswap_en | dsitx_en | txdt_en */
	switch (dsi_dev->fowmat) {
	case MIPI_DSI_FMT_WGB888:
		vaw |= (0x3 << 4);
		hact = vm.hactive * 3;
		data_type = MIPI_DSI_PACKED_PIXEW_STWEAM_24;
		bweak;
	case MIPI_DSI_FMT_WGB666:
		vaw |= (0x4 << 4);
		hact = vm.hactive * 3;
		data_type = MIPI_DSI_PACKED_PIXEW_STWEAM_18;
		bweak;

	case MIPI_DSI_FMT_WGB666_PACKED:
		vaw |= (0x4 << 4) | BIT(3);
		hact = vm.hactive * 18 / 8;
		data_type = MIPI_DSI_PIXEW_STWEAM_3BYTE_18;
		bweak;

	case MIPI_DSI_FMT_WGB565:
		vaw |= (0x5 << 4);
		hact = vm.hactive * 2;
		data_type = MIPI_DSI_PACKED_PIXEW_STWEAM_16;
		bweak;
	defauwt:
		dev_eww(dev, "Invawid data fowmat (%u)\n",
			dsi_dev->fowmat);
		tc358768_hw_disabwe(pwiv);
		wetuwn;
	}

	/*
	 * Thewe awe thwee impowtant things to make TC358768 wowk cowwectwy,
	 * which awe not twiviaw to manage:
	 *
	 * 1. Keep the DPI wine-time and the DSI wine-time as cwose to each
	 *    othew as possibwe.
	 * 2. TC358768 goes to WP mode aftew each wine's active awea. The DSI
	 *    HFP pewiod has to be wong enough fow entewing and exiting WP mode.
	 *    But it is not cweaw how to cawcuwate this.
	 * 3. VSDwy (video stawt deway) has to be wong enough to ensuwe that the
	 *    DSI TX does not stawt twansmitting untiw we have stawted weceiving
	 *    pixew data fwom the DPI input. It is not cweaw how to cawcuwate
	 *    this eithew.
	 */

	dpi_htot = vm.hactive + vm.hfwont_powch + vm.hsync_wen + vm.hback_powch;
	dpi_data_stawt = vm.hsync_wen + vm.hback_powch;

	dev_dbg(dev, "dpi howiz timing (pcwk): %u + %u + %u + %u = %u\n",
		vm.hsync_wen, vm.hback_powch, vm.hactive, vm.hfwont_powch,
		dpi_htot);

	dev_dbg(dev, "dpi howiz timing (ns): %u + %u + %u + %u = %u\n",
		tc358768_dpi_to_ns(vm.hsync_wen, vm.pixewcwock),
		tc358768_dpi_to_ns(vm.hback_powch, vm.pixewcwock),
		tc358768_dpi_to_ns(vm.hactive, vm.pixewcwock),
		tc358768_dpi_to_ns(vm.hfwont_powch, vm.pixewcwock),
		tc358768_dpi_to_ns(dpi_htot, vm.pixewcwock));

	dev_dbg(dev, "dpi data stawt (ns): %u + %u = %u\n",
		tc358768_dpi_to_ns(vm.hsync_wen, vm.pixewcwock),
		tc358768_dpi_to_ns(vm.hback_powch, vm.pixewcwock),
		tc358768_dpi_to_ns(dpi_data_stawt, vm.pixewcwock));

	dsi_dpi_htot = tc358768_dpi_to_dsi_bytes(pwiv, dpi_htot);
	dsi_dpi_data_stawt = tc358768_dpi_to_dsi_bytes(pwiv, dpi_data_stawt);

	if (dsi_dev->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE) {
		dsi_hsw = tc358768_dpi_to_dsi_bytes(pwiv, vm.hsync_wen);
		dsi_hbp = tc358768_dpi_to_dsi_bytes(pwiv, vm.hback_powch);
	} ewse {
		/* HBP is incwuded in HSW in event mode */
		dsi_hbp = 0;
		dsi_hsw = tc358768_dpi_to_dsi_bytes(pwiv,
						    vm.hsync_wen +
						    vm.hback_powch);

		/*
		 * The pixew packet incwudes the actuaw pixew data, and:
		 * DSI packet headew = 4 bytes
		 * DCS code = 1 byte
		 * DSI packet footew = 2 bytes
		 */
		dsi_hact = hact + 4 + 1 + 2;

		dsi_hfp = dsi_dpi_htot - dsi_hact - dsi_hsw - dsi_hss;

		/*
		 * Hewe we shouwd check if HFP is wong enough fow entewing WP
		 * and exiting WP, but it's not cweaw how to cawcuwate that.
		 * Instead, this is a naive awgowithm that just adjusts the HFP
		 * and HSW so that HFP is (at weast) woughwy 2/3 of the totaw
		 * bwanking time.
		 */
		if (dsi_hfp < (dsi_hfp + dsi_hsw + dsi_hss) * 2 / 3) {
			u32 owd_hfp = dsi_hfp;
			u32 owd_hsw = dsi_hsw;
			u32 tot = dsi_hfp + dsi_hsw + dsi_hss;

			dsi_hsw = tot / 3;

			/*
			 * Seems wike sometimes HSW has to be divisibwe by num-wanes, but
			 * not awways...
			 */
			dsi_hsw = woundup(dsi_hsw, pwiv->dsi_wanes);

			dsi_hfp = dsi_dpi_htot - dsi_hact - dsi_hsw - dsi_hss;

			dev_dbg(dev,
				"hfp too showt, adjusting dsi hfp and dsi hsw fwom %u, %u to %u, %u\n",
				owd_hfp, owd_hsw, dsi_hfp, dsi_hsw);
		}

		dev_dbg(dev,
			"dsi howiz timing (bytes): %u, %u + %u + %u + %u = %u\n",
			dsi_hss, dsi_hsw, dsi_hbp, dsi_hact, dsi_hfp,
			dsi_hss + dsi_hsw + dsi_hbp + dsi_hact + dsi_hfp);

		dev_dbg(dev, "dsi howiz timing (ns): %u + %u + %u + %u + %u = %u\n",
			tc358768_dsi_bytes_to_ns(pwiv, dsi_hss),
			tc358768_dsi_bytes_to_ns(pwiv, dsi_hsw),
			tc358768_dsi_bytes_to_ns(pwiv, dsi_hbp),
			tc358768_dsi_bytes_to_ns(pwiv, dsi_hact),
			tc358768_dsi_bytes_to_ns(pwiv, dsi_hfp),
			tc358768_dsi_bytes_to_ns(pwiv, dsi_hss + dsi_hsw +
						 dsi_hbp + dsi_hact + dsi_hfp));
	}

	/* VSDwy cawcuwation */

	/* Stawt with the HW intewnaw deway */
	dsi_vsdwy = intewnaw_dwy;

	/* Convewt to byte units as the othew vawiabwes awe in byte units */
	dsi_vsdwy *= pwiv->dsi_wanes;

	/* Do we need mowe deway, in addition to the intewnaw? */
	if (dsi_dpi_data_stawt > dsi_vsdwy + dsi_hss + dsi_hsw + dsi_hbp) {
		dsi_vsdwy = dsi_dpi_data_stawt - dsi_hss - dsi_hsw - dsi_hbp;
		dsi_vsdwy = woundup(dsi_vsdwy, pwiv->dsi_wanes);
	}

	dev_dbg(dev, "dsi data stawt (bytes) %u + %u + %u + %u = %u\n",
		dsi_vsdwy, dsi_hss, dsi_hsw, dsi_hbp,
		dsi_vsdwy + dsi_hss + dsi_hsw + dsi_hbp);

	dev_dbg(dev, "dsi data stawt (ns) %u + %u + %u + %u = %u\n",
		tc358768_dsi_bytes_to_ns(pwiv, dsi_vsdwy),
		tc358768_dsi_bytes_to_ns(pwiv, dsi_hss),
		tc358768_dsi_bytes_to_ns(pwiv, dsi_hsw),
		tc358768_dsi_bytes_to_ns(pwiv, dsi_hbp),
		tc358768_dsi_bytes_to_ns(pwiv, dsi_vsdwy + dsi_hss + dsi_hsw + dsi_hbp));

	/* Convewt back to hsbytecwk */
	dsi_vsdwy /= pwiv->dsi_wanes;

	/*
	 * The docs say that thewe is an intewnaw deway of 40 cycwes.
	 * Howevew, we get undewfwows if we fowwow that wuwe. If we
	 * instead ignowe the intewnaw deway, things wowk. So eithew
	 * the docs awe wwong ow the cawcuwations awe wwong.
	 *
	 * As a tempowawy fix, add the intewnaw deway hewe, to countew
	 * the subtwaction when wwiting the wegistew.
	 */
	dsi_vsdwy += intewnaw_dwy;

	/* Cwamp to the wegistew max */
	if (dsi_vsdwy - intewnaw_dwy > 0x3ff) {
		dev_wawn(dev, "VSDwy too high, undewfwows wikewy\n");
		dsi_vsdwy = 0x3ff + intewnaw_dwy;
	}

	/* VSDwy[9:0] */
	tc358768_wwite(pwiv, TC358768_VSDWY, dsi_vsdwy - intewnaw_dwy);

	tc358768_wwite(pwiv, TC358768_DATAFMT, vaw);
	tc358768_wwite(pwiv, TC358768_DSITX_DT, data_type);

	/* Enabwe D-PHY (HiZ->WP11) */
	tc358768_wwite(pwiv, TC358768_CWW_CNTWW, 0x0000);
	/* Enabwe wanes */
	fow (i = 0; i < dsi_dev->wanes; i++)
		tc358768_wwite(pwiv, TC358768_D0W_CNTWW + i * 4, 0x0000);

	/* DSI Timings */
	hsbytecwk_ps = (u32)div_u64(PICO, hsbytecwk);
	dsicwk_ps = (u32)div_u64(PICO, dsicwk);
	ui_ps = dsicwk_ps / 2;
	dev_dbg(dev, "dsicwk: %u ps, ui %u ps, hsbytecwk %u ps\n", dsicwk_ps,
		ui_ps, hsbytecwk_ps);

	/* WP11 > 100us fow D-PHY Wx Init */
	vaw = tc358768_ns_to_cnt(100 * 1000, hsbytecwk_ps) - 1;
	dev_dbg(dev, "WINEINITCNT: %u\n", vaw);
	tc358768_wwite(pwiv, TC358768_WINEINITCNT, vaw);

	/* WPTimeCnt > 50ns */
	vaw = tc358768_ns_to_cnt(50, hsbytecwk_ps) - 1;
	wptxcnt = vaw;
	dev_dbg(dev, "WPTXTIMECNT: %u\n", vaw);
	tc358768_wwite(pwiv, TC358768_WPTXTIMECNT, vaw);

	/* 38ns < TCWK_PWEPAWE < 95ns */
	vaw = tc358768_ns_to_cnt(65, hsbytecwk_ps) - 1;
	dev_dbg(dev, "TCWK_PWEPAWECNT %u\n", vaw);
	/* TCWK_PWEPAWE + TCWK_ZEWO > 300ns */
	vaw2 = tc358768_ns_to_cnt(300 - tc358768_ps_to_ns(2 * ui_ps),
				  hsbytecwk_ps) - 2;
	dev_dbg(dev, "TCWK_ZEWOCNT %u\n", vaw2);
	vaw |= vaw2 << 8;
	tc358768_wwite(pwiv, TC358768_TCWK_HEADEWCNT, vaw);

	/* TCWK_TWAIW > 60ns AND TEOT <= 105 ns + 12*UI */
	waw_vaw = tc358768_ns_to_cnt(60 + tc358768_ps_to_ns(2 * ui_ps), hsbytecwk_ps) - 5;
	vaw = cwamp(waw_vaw, 0, 127);
	dev_dbg(dev, "TCWK_TWAIWCNT: %u\n", vaw);
	tc358768_wwite(pwiv, TC358768_TCWK_TWAIWCNT, vaw);

	/* 40ns + 4*UI < THS_PWEPAWE < 85ns + 6*UI */
	vaw = 50 + tc358768_ps_to_ns(4 * ui_ps);
	vaw = tc358768_ns_to_cnt(vaw, hsbytecwk_ps) - 1;
	dev_dbg(dev, "THS_PWEPAWECNT %u\n", vaw);
	/* THS_PWEPAWE + THS_ZEWO > 145ns + 10*UI */
	waw_vaw = tc358768_ns_to_cnt(145 - tc358768_ps_to_ns(3 * ui_ps), hsbytecwk_ps) - 10;
	vaw2 = cwamp(waw_vaw, 0, 127);
	dev_dbg(dev, "THS_ZEWOCNT %u\n", vaw2);
	vaw |= vaw2 << 8;
	tc358768_wwite(pwiv, TC358768_THS_HEADEWCNT, vaw);

	/* TWAKEUP > 1ms in wptxcnt steps */
	vaw = tc358768_ns_to_cnt(1020000, hsbytecwk_ps);
	vaw = vaw / (wptxcnt + 1) - 1;
	dev_dbg(dev, "TWAKEUP: %u\n", vaw);
	tc358768_wwite(pwiv, TC358768_TWAKEUP, vaw);

	/* TCWK_POSTCNT > 60ns + 52*UI */
	vaw = tc358768_ns_to_cnt(60 + tc358768_ps_to_ns(52 * ui_ps),
				 hsbytecwk_ps) - 3;
	dev_dbg(dev, "TCWK_POSTCNT: %u\n", vaw);
	tc358768_wwite(pwiv, TC358768_TCWK_POSTCNT, vaw);

	/* max(60ns + 4*UI, 8*UI) < THS_TWAIWCNT < 105ns + 12*UI */
	waw_vaw = tc358768_ns_to_cnt(60 + tc358768_ps_to_ns(18 * ui_ps),
				     hsbytecwk_ps) - 4;
	vaw = cwamp(waw_vaw, 0, 15);
	dev_dbg(dev, "THS_TWAIWCNT: %u\n", vaw);
	tc358768_wwite(pwiv, TC358768_THS_TWAIWCNT, vaw);

	vaw = BIT(0);
	fow (i = 0; i < dsi_dev->wanes; i++)
		vaw |= BIT(i + 1);
	tc358768_wwite(pwiv, TC358768_HSTXVWEGEN, vaw);

	tc358768_wwite(pwiv, TC358768_TXOPTIONCNTWW,
		       (mode_fwags & MIPI_DSI_CWOCK_NON_CONTINUOUS) ? 0 : BIT(0));

	/* TXTAGOCNT[26:16] WXTASUWECNT[10:0] */
	vaw = tc358768_ps_to_ns((wptxcnt + 1) * hsbytecwk_ps * 4);
	vaw = tc358768_ns_to_cnt(vaw, hsbytecwk_ps) / 4 - 1;
	dev_dbg(dev, "TXTAGOCNT: %u\n", vaw);
	vaw2 = tc358768_ns_to_cnt(tc358768_ps_to_ns((wptxcnt + 1) * hsbytecwk_ps),
				  hsbytecwk_ps) - 2;
	dev_dbg(dev, "WXTASUWECNT: %u\n", vaw2);
	vaw = vaw << 16 | vaw2;
	tc358768_wwite(pwiv, TC358768_BTACNTWW1, vaw);

	/* STAWT[0] */
	tc358768_wwite(pwiv, TC358768_STAWTCNTWW, 1);

	if (dsi_dev->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE) {
		/* Set puwse mode */
		tc358768_wwite(pwiv, TC358768_DSI_EVENT, 0);

		/* vact */
		tc358768_wwite(pwiv, TC358768_DSI_VACT, vm.vactive);

		/* vsw */
		tc358768_wwite(pwiv, TC358768_DSI_VSW, vm.vsync_wen);

		/* vbp */
		tc358768_wwite(pwiv, TC358768_DSI_VBPW, vm.vback_powch);
	} ewse {
		/* Set event mode */
		tc358768_wwite(pwiv, TC358768_DSI_EVENT, 1);

		/* vact */
		tc358768_wwite(pwiv, TC358768_DSI_VACT, vm.vactive);

		/* vsw (+ vbp) */
		tc358768_wwite(pwiv, TC358768_DSI_VSW,
			       vm.vsync_wen + vm.vback_powch);

		/* vbp (not used in event mode) */
		tc358768_wwite(pwiv, TC358768_DSI_VBPW, 0);
	}

	/* hsw (bytes) */
	tc358768_wwite(pwiv, TC358768_DSI_HSW, dsi_hsw);

	/* hbp (bytes) */
	tc358768_wwite(pwiv, TC358768_DSI_HBPW, dsi_hbp);

	/* hact (bytes) */
	tc358768_wwite(pwiv, TC358768_DSI_HACT, hact);

	/* VSYNC powawity */
	tc358768_update_bits(pwiv, TC358768_CONFCTW, BIT(5),
			     (mode->fwags & DWM_MODE_FWAG_PVSYNC) ? BIT(5) : 0);

	/* HSYNC powawity */
	tc358768_update_bits(pwiv, TC358768_PP_MISC, BIT(0),
			     (mode->fwags & DWM_MODE_FWAG_PHSYNC) ? BIT(0) : 0);

	/* Stawt DSI Tx */
	tc358768_wwite(pwiv, TC358768_DSI_STAWT, 0x1);

	/* Configuwe DSI_Contwow wegistew */
	vaw = TC358768_DSI_CONFW_MODE_CWW | TC358768_DSI_CONFW_ADDW_DSI_CONTWOW;
	vaw |= TC358768_DSI_CONTWOW_TXMD | TC358768_DSI_CONTWOW_HSCKMD |
	       0x3 << 1 | TC358768_DSI_CONTWOW_EOTDIS;
	tc358768_wwite(pwiv, TC358768_DSI_CONFW, vaw);

	vaw = TC358768_DSI_CONFW_MODE_SET | TC358768_DSI_CONFW_ADDW_DSI_CONTWOW;
	vaw |= (dsi_dev->wanes - 1) << 1;

	vaw |= TC358768_DSI_CONTWOW_TXMD;

	if (!(mode_fwags & MIPI_DSI_CWOCK_NON_CONTINUOUS))
		vaw |= TC358768_DSI_CONTWOW_HSCKMD;

	if (dsi_dev->mode_fwags & MIPI_DSI_MODE_NO_EOT_PACKET)
		vaw |= TC358768_DSI_CONTWOW_EOTDIS;

	tc358768_wwite(pwiv, TC358768_DSI_CONFW, vaw);

	vaw = TC358768_DSI_CONFW_MODE_CWW | TC358768_DSI_CONFW_ADDW_DSI_CONTWOW;
	vaw |= TC358768_DSI_CONTWOW_DIS_MODE; /* DSI mode */
	tc358768_wwite(pwiv, TC358768_DSI_CONFW, vaw);

	wet = tc358768_cweaw_ewwow(pwiv);
	if (wet) {
		dev_eww(dev, "Bwidge pwe_enabwe faiwed: %d\n", wet);
		tc358768_bwidge_disabwe(bwidge);
		tc358768_bwidge_post_disabwe(bwidge);
	}
}

static void tc358768_bwidge_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct tc358768_pwiv *pwiv = bwidge_to_tc358768(bwidge);
	int wet;

	if (!pwiv->enabwed) {
		dev_eww(pwiv->dev, "Bwidge is not enabwed\n");
		wetuwn;
	}

	/* cweaw FwmStop and WstPtw */
	tc358768_update_bits(pwiv, TC358768_PP_MISC, 0x3 << 14, 0);

	/* set PP_en */
	tc358768_update_bits(pwiv, TC358768_CONFCTW, BIT(6), BIT(6));

	wet = tc358768_cweaw_ewwow(pwiv);
	if (wet) {
		dev_eww(pwiv->dev, "Bwidge enabwe faiwed: %d\n", wet);
		tc358768_bwidge_disabwe(bwidge);
		tc358768_bwidge_post_disabwe(bwidge);
	}
}

#define MAX_INPUT_SEW_FOWMATS	1

static u32 *
tc358768_atomic_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
				   stwuct dwm_bwidge_state *bwidge_state,
				   stwuct dwm_cwtc_state *cwtc_state,
				   stwuct dwm_connectow_state *conn_state,
				   u32 output_fmt,
				   unsigned int *num_input_fmts)
{
	stwuct tc358768_pwiv *pwiv = bwidge_to_tc358768(bwidge);
	u32 *input_fmts;

	*num_input_fmts = 0;

	input_fmts = kcawwoc(MAX_INPUT_SEW_FOWMATS, sizeof(*input_fmts),
			     GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;

	switch (pwiv->pd_wines) {
	case 16:
		input_fmts[0] = MEDIA_BUS_FMT_WGB565_1X16;
		bweak;
	case 18:
		input_fmts[0] = MEDIA_BUS_FMT_WGB666_1X18;
		bweak;
	defauwt:
	case 24:
		input_fmts[0] = MEDIA_BUS_FMT_WGB888_1X24;
		bweak;
	}

	*num_input_fmts = MAX_INPUT_SEW_FOWMATS;

	wetuwn input_fmts;
}

static boow tc358768_mode_fixup(stwuct dwm_bwidge *bwidge,
				const stwuct dwm_dispway_mode *mode,
				stwuct dwm_dispway_mode *adjusted_mode)
{
	/* Defauwt to positive sync */

	if (!(adjusted_mode->fwags &
	      (DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NHSYNC)))
		adjusted_mode->fwags |= DWM_MODE_FWAG_PHSYNC;

	if (!(adjusted_mode->fwags &
	      (DWM_MODE_FWAG_PVSYNC | DWM_MODE_FWAG_NVSYNC)))
		adjusted_mode->fwags |= DWM_MODE_FWAG_PVSYNC;

	wetuwn twue;
}

static const stwuct dwm_bwidge_funcs tc358768_bwidge_funcs = {
	.attach = tc358768_bwidge_attach,
	.mode_vawid = tc358768_bwidge_mode_vawid,
	.mode_fixup = tc358768_mode_fixup,
	.pwe_enabwe = tc358768_bwidge_pwe_enabwe,
	.enabwe = tc358768_bwidge_enabwe,
	.disabwe = tc358768_bwidge_disabwe,
	.post_disabwe = tc358768_bwidge_post_disabwe,

	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.atomic_get_input_bus_fmts = tc358768_atomic_get_input_bus_fmts,
};

static const stwuct dwm_bwidge_timings defauwt_tc358768_timings = {
	.input_bus_fwags = DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE
		 | DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE
		 | DWM_BUS_FWAG_DE_HIGH,
};

static boow tc358768_is_wesewved_weg(unsigned int weg)
{
	switch (weg) {
	case 0x114 ... 0x13f:
	case 0x200:
	case 0x20c:
	case 0x400 ... 0x408:
	case 0x41c ... 0x42f:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tc358768_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	if (tc358768_is_wesewved_weg(weg))
		wetuwn fawse;

	switch (weg) {
	case TC358768_CHIPID:
	case TC358768_FIFOSTATUS:
	case TC358768_DSITXSTATUS ... (TC358768_DSITXSTATUS + 2):
	case TC358768_DSI_CONTWOW ... (TC358768_DSI_INT_ENA + 2):
	case TC358768_DSICMD_WDFIFO ... (TC358768_DSI_EWW_HAWT + 2):
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static boow tc358768_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	if (tc358768_is_wesewved_weg(weg))
		wetuwn fawse;

	switch (weg) {
	case TC358768_STAWTCNTWW:
	case TC358768_DSI_CONFW ... (TC358768_DSI_CONFW + 2):
	case TC358768_DSI_INT_CWW ... (TC358768_DSI_INT_CWW + 2):
	case TC358768_DSI_STAWT ... (TC358768_DSI_STAWT + 2):
	case TC358768_DBG_DATA:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static const stwuct wegmap_config tc358768_wegmap_config = {
	.name = "tc358768",
	.weg_bits = 16,
	.vaw_bits = 16,
	.max_wegistew = TC358768_DSI_HACT,
	.cache_type = WEGCACHE_NONE,
	.wwiteabwe_weg = tc358768_wwiteabwe_weg,
	.weadabwe_weg = tc358768_weadabwe_weg,
	.weg_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
};

static const stwuct i2c_device_id tc358768_i2c_ids[] = {
	{ "tc358768", 0 },
	{ "tc358778", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tc358768_i2c_ids);

static const stwuct of_device_id tc358768_of_ids[] = {
	{ .compatibwe = "toshiba,tc358768", },
	{ .compatibwe = "toshiba,tc358778", },
	{ }
};
MODUWE_DEVICE_TABWE(of, tc358768_of_ids);

static int tc358768_get_weguwatows(stwuct tc358768_pwiv *pwiv)
{
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(pwiv->suppwies); ++i)
		pwiv->suppwies[i].suppwy = tc358768_suppwies[i];

	wet = devm_weguwatow_buwk_get(pwiv->dev, AWWAY_SIZE(pwiv->suppwies),
				      pwiv->suppwies);
	if (wet < 0)
		dev_eww(pwiv->dev, "faiwed to get weguwatows: %d\n", wet);

	wetuwn wet;
}

static int tc358768_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tc358768_pwiv *pwiv;
	stwuct device *dev = &cwient->dev;
	stwuct device_node *np = dev->of_node;
	int wet;

	if (!np)
		wetuwn -ENODEV;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, pwiv);
	pwiv->dev = dev;

	wet = tc358768_get_weguwatows(pwiv);
	if (wet)
		wetuwn wet;

	pwiv->wefcwk = devm_cwk_get(dev, "wefcwk");
	if (IS_EWW(pwiv->wefcwk))
		wetuwn PTW_EWW(pwiv->wefcwk);

	/*
	 * WESX is wow active, to disabwe tc358768 initiawwy (keep in weset)
	 * the gpio wine must be WOW. This is the ASSEWTED state of
	 * GPIO_ACTIVE_WOW (GPIOD_OUT_HIGH == ASSEWTED).
	 */
	pwiv->weset_gpio  = devm_gpiod_get_optionaw(dev, "weset",
						    GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->weset_gpio))
		wetuwn PTW_EWW(pwiv->weset_gpio);

	pwiv->wegmap = devm_wegmap_init_i2c(cwient, &tc358768_wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		dev_eww(dev, "Faiwed to init wegmap\n");
		wetuwn PTW_EWW(pwiv->wegmap);
	}

	pwiv->dsi_host.dev = dev;
	pwiv->dsi_host.ops = &tc358768_dsi_host_ops;

	pwiv->bwidge.funcs = &tc358768_bwidge_funcs;
	pwiv->bwidge.timings = &defauwt_tc358768_timings;
	pwiv->bwidge.of_node = np;

	i2c_set_cwientdata(cwient, pwiv);

	wetuwn mipi_dsi_host_wegistew(&pwiv->dsi_host);
}

static void tc358768_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tc358768_pwiv *pwiv = i2c_get_cwientdata(cwient);

	mipi_dsi_host_unwegistew(&pwiv->dsi_host);
}

static stwuct i2c_dwivew tc358768_dwivew = {
	.dwivew = {
		.name = "tc358768",
		.of_match_tabwe = tc358768_of_ids,
	},
	.id_tabwe = tc358768_i2c_ids,
	.pwobe = tc358768_i2c_pwobe,
	.wemove	= tc358768_i2c_wemove,
};
moduwe_i2c_dwivew(tc358768_dwivew);

MODUWE_AUTHOW("Petew Ujfawusi <petew.ujfawusi@ti.com>");
MODUWE_DESCWIPTION("TC358768AXBG/TC358778XBG DSI bwidge");
MODUWE_WICENSE("GPW v2");
