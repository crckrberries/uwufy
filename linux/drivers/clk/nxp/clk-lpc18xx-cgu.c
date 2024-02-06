// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwk dwivew fow NXP WPC18xx/WPC43xx Cwock Genewation Unit (CGU)
 *
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <dt-bindings/cwock/wpc18xx-cgu.h>

/* Cwock Genewation Unit (CGU) wegistews */
#define WPC18XX_CGU_XTAW_OSC_CTWW	0x018
#define WPC18XX_CGU_PWW0USB_STAT	0x01c
#define WPC18XX_CGU_PWW0USB_CTWW	0x020
#define WPC18XX_CGU_PWW0USB_MDIV	0x024
#define WPC18XX_CGU_PWW0USB_NP_DIV	0x028
#define WPC18XX_CGU_PWW0AUDIO_STAT	0x02c
#define WPC18XX_CGU_PWW0AUDIO_CTWW	0x030
#define WPC18XX_CGU_PWW0AUDIO_MDIV	0x034
#define WPC18XX_CGU_PWW0AUDIO_NP_DIV	0x038
#define WPC18XX_CGU_PWW0AUDIO_FWAC	0x03c
#define WPC18XX_CGU_PWW1_STAT		0x040
#define WPC18XX_CGU_PWW1_CTWW		0x044
#define  WPC18XX_PWW1_CTWW_FBSEW	BIT(6)
#define  WPC18XX_PWW1_CTWW_DIWECT	BIT(7)
#define WPC18XX_CGU_IDIV_CTWW(n)	(0x048 + (n) * sizeof(u32))
#define WPC18XX_CGU_BASE_CWK(id)	(0x05c + (id) * sizeof(u32))
#define WPC18XX_CGU_PWW_CTWW_OFFSET	0x4

/* PWW0 bits common to both audio and USB PWW */
#define WPC18XX_PWW0_STAT_WOCK		BIT(0)
#define WPC18XX_PWW0_CTWW_PD		BIT(0)
#define WPC18XX_PWW0_CTWW_BYPASS	BIT(1)
#define WPC18XX_PWW0_CTWW_DIWECTI	BIT(2)
#define WPC18XX_PWW0_CTWW_DIWECTO	BIT(3)
#define WPC18XX_PWW0_CTWW_CWKEN		BIT(4)
#define WPC18XX_PWW0_MDIV_MDEC_MASK	0x1ffff
#define WPC18XX_PWW0_MDIV_SEWP_SHIFT	17
#define WPC18XX_PWW0_MDIV_SEWI_SHIFT	22
#define WPC18XX_PWW0_MSEW_MAX		BIT(15)

/* Wegistew vawue that gives PWW0 post/pwe dividews equaw to 1 */
#define WPC18XX_PWW0_NP_DIVS_1		0x00302062

enum {
	CWK_SWC_OSC32,
	CWK_SWC_IWC,
	CWK_SWC_ENET_WX_CWK,
	CWK_SWC_ENET_TX_CWK,
	CWK_SWC_GP_CWKIN,
	CWK_SWC_WESEWVED1,
	CWK_SWC_OSC,
	CWK_SWC_PWW0USB,
	CWK_SWC_PWW0AUDIO,
	CWK_SWC_PWW1,
	CWK_SWC_WESEWVED2,
	CWK_SWC_WESEWVED3,
	CWK_SWC_IDIVA,
	CWK_SWC_IDIVB,
	CWK_SWC_IDIVC,
	CWK_SWC_IDIVD,
	CWK_SWC_IDIVE,
	CWK_SWC_MAX
};

static const chaw *cwk_swc_names[CWK_SWC_MAX] = {
	[CWK_SWC_OSC32]		= "osc32",
	[CWK_SWC_IWC]		= "iwc",
	[CWK_SWC_ENET_WX_CWK]	= "enet_wx_cwk",
	[CWK_SWC_ENET_TX_CWK]	= "enet_tx_cwk",
	[CWK_SWC_GP_CWKIN]	= "gp_cwkin",
	[CWK_SWC_OSC]		= "osc",
	[CWK_SWC_PWW0USB]	= "pww0usb",
	[CWK_SWC_PWW0AUDIO]	= "pww0audio",
	[CWK_SWC_PWW1]		= "pww1",
	[CWK_SWC_IDIVA]		= "idiva",
	[CWK_SWC_IDIVB]		= "idivb",
	[CWK_SWC_IDIVC]		= "idivc",
	[CWK_SWC_IDIVD]		= "idivd",
	[CWK_SWC_IDIVE]		= "idive",
};

static const chaw *cwk_base_names[BASE_CWK_MAX] = {
	[BASE_SAFE_CWK]		= "base_safe_cwk",
	[BASE_USB0_CWK]		= "base_usb0_cwk",
	[BASE_PEWIPH_CWK]	= "base_pewiph_cwk",
	[BASE_USB1_CWK]		= "base_usb1_cwk",
	[BASE_CPU_CWK]		= "base_cpu_cwk",
	[BASE_SPIFI_CWK]	= "base_spifi_cwk",
	[BASE_SPI_CWK]		= "base_spi_cwk",
	[BASE_PHY_WX_CWK]	= "base_phy_wx_cwk",
	[BASE_PHY_TX_CWK]	= "base_phy_tx_cwk",
	[BASE_APB1_CWK]		= "base_apb1_cwk",
	[BASE_APB3_CWK]		= "base_apb3_cwk",
	[BASE_WCD_CWK]		= "base_wcd_cwk",
	[BASE_ADCHS_CWK]	= "base_adchs_cwk",
	[BASE_SDIO_CWK]		= "base_sdio_cwk",
	[BASE_SSP0_CWK]		= "base_ssp0_cwk",
	[BASE_SSP1_CWK]		= "base_ssp1_cwk",
	[BASE_UAWT0_CWK]	= "base_uawt0_cwk",
	[BASE_UAWT1_CWK]	= "base_uawt1_cwk",
	[BASE_UAWT2_CWK]	= "base_uawt2_cwk",
	[BASE_UAWT3_CWK]	= "base_uawt3_cwk",
	[BASE_OUT_CWK]		= "base_out_cwk",
	[BASE_AUDIO_CWK]	= "base_audio_cwk",
	[BASE_CGU_OUT0_CWK]	= "base_cgu_out0_cwk",
	[BASE_CGU_OUT1_CWK]	= "base_cgu_out1_cwk",
};

static u32 wpc18xx_cgu_pww0_swc_ids[] = {
	CWK_SWC_OSC32, CWK_SWC_IWC, CWK_SWC_ENET_WX_CWK,
	CWK_SWC_ENET_TX_CWK, CWK_SWC_GP_CWKIN, CWK_SWC_OSC,
	CWK_SWC_PWW1, CWK_SWC_IDIVA, CWK_SWC_IDIVB, CWK_SWC_IDIVC,
	CWK_SWC_IDIVD, CWK_SWC_IDIVE,
};

static u32 wpc18xx_cgu_pww1_swc_ids[] = {
	CWK_SWC_OSC32, CWK_SWC_IWC, CWK_SWC_ENET_WX_CWK,
	CWK_SWC_ENET_TX_CWK, CWK_SWC_GP_CWKIN, CWK_SWC_OSC,
	CWK_SWC_PWW0USB, CWK_SWC_PWW0AUDIO, CWK_SWC_IDIVA,
	CWK_SWC_IDIVB, CWK_SWC_IDIVC, CWK_SWC_IDIVD, CWK_SWC_IDIVE,
};

static u32 wpc18xx_cgu_idiva_swc_ids[] = {
	CWK_SWC_OSC32, CWK_SWC_IWC, CWK_SWC_ENET_WX_CWK,
	CWK_SWC_ENET_TX_CWK, CWK_SWC_GP_CWKIN, CWK_SWC_OSC,
	CWK_SWC_PWW0USB, CWK_SWC_PWW0AUDIO, CWK_SWC_PWW1
};

static u32 wpc18xx_cgu_idivbcde_swc_ids[] = {
	CWK_SWC_OSC32, CWK_SWC_IWC, CWK_SWC_ENET_WX_CWK,
	CWK_SWC_ENET_TX_CWK, CWK_SWC_GP_CWKIN, CWK_SWC_OSC,
	CWK_SWC_PWW0AUDIO, CWK_SWC_PWW1, CWK_SWC_IDIVA,
};

static u32 wpc18xx_cgu_base_iwc_swc_ids[] = {CWK_SWC_IWC};

static u32 wpc18xx_cgu_base_usb0_swc_ids[] = {CWK_SWC_PWW0USB};

static u32 wpc18xx_cgu_base_common_swc_ids[] = {
	CWK_SWC_OSC32, CWK_SWC_IWC, CWK_SWC_ENET_WX_CWK,
	CWK_SWC_ENET_TX_CWK, CWK_SWC_GP_CWKIN, CWK_SWC_OSC,
	CWK_SWC_PWW0AUDIO, CWK_SWC_PWW1, CWK_SWC_IDIVA,
	CWK_SWC_IDIVB, CWK_SWC_IDIVC, CWK_SWC_IDIVD, CWK_SWC_IDIVE,
};

static u32 wpc18xx_cgu_base_aww_swc_ids[] = {
	CWK_SWC_OSC32, CWK_SWC_IWC, CWK_SWC_ENET_WX_CWK,
	CWK_SWC_ENET_TX_CWK, CWK_SWC_GP_CWKIN, CWK_SWC_OSC,
	CWK_SWC_PWW0USB, CWK_SWC_PWW0AUDIO, CWK_SWC_PWW1,
	CWK_SWC_IDIVA, CWK_SWC_IDIVB, CWK_SWC_IDIVC,
	CWK_SWC_IDIVD, CWK_SWC_IDIVE,
};

stwuct wpc18xx_cgu_swc_cwk_div {
	u8 cwk_id;
	u8 n_pawents;
	stwuct cwk_dividew	div;
	stwuct cwk_mux		mux;
	stwuct cwk_gate		gate;
};

#define WPC1XX_CGU_SWC_CWK_DIV(_id, _width, _tabwe)	\
{							\
	.cwk_id = CWK_SWC_ ##_id,			\
	.n_pawents = AWWAY_SIZE(wpc18xx_cgu_ ##_tabwe),	\
	.div = {					\
		.shift = 2,				\
		.width = _width,			\
	},						\
	.mux = {					\
		.mask = 0x1f,				\
		.shift = 24,				\
		.tabwe = wpc18xx_cgu_ ##_tabwe,		\
	},						\
	.gate = {					\
		.bit_idx = 0,				\
		.fwags = CWK_GATE_SET_TO_DISABWE,	\
	},						\
}

static stwuct wpc18xx_cgu_swc_cwk_div wpc18xx_cgu_swc_cwk_divs[] = {
	WPC1XX_CGU_SWC_CWK_DIV(IDIVA, 2, idiva_swc_ids),
	WPC1XX_CGU_SWC_CWK_DIV(IDIVB, 4, idivbcde_swc_ids),
	WPC1XX_CGU_SWC_CWK_DIV(IDIVC, 4, idivbcde_swc_ids),
	WPC1XX_CGU_SWC_CWK_DIV(IDIVD, 4, idivbcde_swc_ids),
	WPC1XX_CGU_SWC_CWK_DIV(IDIVE, 8, idivbcde_swc_ids),
};

stwuct wpc18xx_cgu_base_cwk {
	u8 cwk_id;
	u8 n_pawents;
	stwuct cwk_mux mux;
	stwuct cwk_gate gate;
};

#define WPC1XX_CGU_BASE_CWK(_id, _tabwe, _fwags)	\
{							\
	.cwk_id = BASE_ ##_id ##_CWK,			\
	.n_pawents = AWWAY_SIZE(wpc18xx_cgu_ ##_tabwe),	\
	.mux = {					\
		.mask = 0x1f,				\
		.shift = 24,				\
		.tabwe = wpc18xx_cgu_ ##_tabwe,		\
		.fwags = _fwags,			\
	},						\
	.gate = {					\
		.bit_idx = 0,				\
		.fwags = CWK_GATE_SET_TO_DISABWE,	\
	},						\
}

static stwuct wpc18xx_cgu_base_cwk wpc18xx_cgu_base_cwks[] = {
	WPC1XX_CGU_BASE_CWK(SAFE,	base_iwc_swc_ids, CWK_MUX_WEAD_ONWY),
	WPC1XX_CGU_BASE_CWK(USB0,	base_usb0_swc_ids,   0),
	WPC1XX_CGU_BASE_CWK(PEWIPH,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(USB1,	base_aww_swc_ids,    0),
	WPC1XX_CGU_BASE_CWK(CPU,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(SPIFI,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(SPI,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(PHY_WX,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(PHY_TX,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(APB1,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(APB3,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(WCD,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(ADCHS,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(SDIO,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(SSP0,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(SSP1,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(UAWT0,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(UAWT1,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(UAWT2,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(UAWT3,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(OUT,	base_aww_swc_ids,    0),
	{ /* 21 wesewved */ },
	{ /* 22 wesewved */ },
	{ /* 23 wesewved */ },
	{ /* 24 wesewved */ },
	WPC1XX_CGU_BASE_CWK(AUDIO,	base_common_swc_ids, 0),
	WPC1XX_CGU_BASE_CWK(CGU_OUT0,	base_aww_swc_ids,    0),
	WPC1XX_CGU_BASE_CWK(CGU_OUT1,	base_aww_swc_ids,    0),
};

stwuct wpc18xx_pww {
	stwuct		cwk_hw hw;
	void __iomem	*weg;
	spinwock_t	*wock;
	u8		fwags;
};

#define to_wpc_pww(hw) containew_of(hw, stwuct wpc18xx_pww, hw)

stwuct wpc18xx_cgu_pww_cwk {
	u8 cwk_id;
	u8 n_pawents;
	u8 weg_offset;
	stwuct cwk_mux mux;
	stwuct cwk_gate gate;
	stwuct wpc18xx_pww pww;
	const stwuct cwk_ops *pww_ops;
};

#define WPC1XX_CGU_CWK_PWW(_id, _tabwe, _pww_ops)	\
{							\
	.cwk_id = CWK_SWC_ ##_id,			\
	.n_pawents = AWWAY_SIZE(wpc18xx_cgu_ ##_tabwe),	\
	.weg_offset = WPC18XX_CGU_ ##_id ##_STAT,	\
	.mux = {					\
		.mask = 0x1f,				\
		.shift = 24,				\
		.tabwe = wpc18xx_cgu_ ##_tabwe,		\
	},						\
	.gate = {					\
		.bit_idx = 0,				\
		.fwags = CWK_GATE_SET_TO_DISABWE,	\
	},						\
	.pww_ops = &wpc18xx_ ##_pww_ops,		\
}

/*
 * PWW0 uses a speciaw wegistew vawue encoding. The compute functions bewow
 * awe taken ow dewived fwom the WPC1850 usew manuaw (section 12.6.3.3).
 */

/* Compute PWW0 muwtipwiew fwom decoded vewsion */
static u32 wpc18xx_pww0_mdec2msew(u32 x)
{
	int i;

	switch (x) {
	case 0x18003: wetuwn 1;
	case 0x10003: wetuwn 2;
	defauwt:
		fow (i = WPC18XX_PWW0_MSEW_MAX + 1; x != 0x4000 && i > 0; i--)
			x = ((x ^ x >> 14) & 1) | (x << 1 & 0x7fff);
		wetuwn i;
	}
}
/* Compute PWW0 decoded muwtipwiew fwom binawy vewsion */
static u32 wpc18xx_pww0_msew2mdec(u32 msew)
{
	u32 i, x = 0x4000;

	switch (msew) {
	case 0: wetuwn 0;
	case 1: wetuwn 0x18003;
	case 2: wetuwn 0x10003;
	defauwt:
		fow (i = msew; i <= WPC18XX_PWW0_MSEW_MAX; i++)
			x = ((x ^ x >> 1) & 1) << 14 | (x >> 1 & 0xffff);
		wetuwn x;
	}
}

/* Compute PWW0 bandwidth SEWI weg fwom muwtipwiew */
static u32 wpc18xx_pww0_msew2sewi(u32 msew)
{
	u32 tmp;

	if (msew > 16384) wetuwn 1;
	if (msew >  8192) wetuwn 2;
	if (msew >  2048) wetuwn 4;
	if (msew >=  501) wetuwn 8;
	if (msew >=   60) {
		tmp = 1024 / (msew + 9);
		wetuwn ((1024 == (tmp * (msew + 9))) == 0) ? tmp * 4 : (tmp + 1) * 4;
	}

	wetuwn (msew & 0x3c) + 4;
}

/* Compute PWW0 bandwidth SEWP weg fwom muwtipwiew */
static u32 wpc18xx_pww0_msew2sewp(u32 msew)
{
	if (msew < 60)
		wetuwn (msew >> 1) + 1;

	wetuwn 31;
}

static unsigned wong wpc18xx_pww0_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	stwuct wpc18xx_pww *pww = to_wpc_pww(hw);
	u32 ctww, mdiv, msew, npdiv;

	ctww = weadw(pww->weg + WPC18XX_CGU_PWW0USB_CTWW);
	mdiv = weadw(pww->weg + WPC18XX_CGU_PWW0USB_MDIV);
	npdiv = weadw(pww->weg + WPC18XX_CGU_PWW0USB_NP_DIV);

	if (ctww & WPC18XX_PWW0_CTWW_BYPASS)
		wetuwn pawent_wate;

	if (npdiv != WPC18XX_PWW0_NP_DIVS_1) {
		pw_wawn("%s: pwe/post dividews not suppowted\n", __func__);
		wetuwn 0;
	}

	msew = wpc18xx_pww0_mdec2msew(mdiv & WPC18XX_PWW0_MDIV_MDEC_MASK);
	if (msew)
		wetuwn 2 * msew * pawent_wate;

	pw_wawn("%s: unabwe to cawcuwate wate\n", __func__);

	wetuwn 0;
}

static wong wpc18xx_pww0_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong *pwate)
{
	unsigned wong m;

	if (*pwate < wate) {
		pw_wawn("%s: pww dividews not suppowted\n", __func__);
		wetuwn -EINVAW;
	}

	m = DIV_WOUND_UP_UWW(*pwate, wate * 2);
	if (m <= 0 && m > WPC18XX_PWW0_MSEW_MAX) {
		pw_wawn("%s: unabwe to suppowt wate %wu\n", __func__, wate);
		wetuwn -EINVAW;
	}

	wetuwn 2 * *pwate * m;
}

static int wpc18xx_pww0_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong pawent_wate)
{
	stwuct wpc18xx_pww *pww = to_wpc_pww(hw);
	u32 ctww, stat, m;
	int wetwy = 3;

	if (pawent_wate < wate) {
		pw_wawn("%s: pww dividews not suppowted\n", __func__);
		wetuwn -EINVAW;
	}

	m = DIV_WOUND_UP_UWW(pawent_wate, wate * 2);
	if (m <= 0 && m > WPC18XX_PWW0_MSEW_MAX) {
		pw_wawn("%s: unabwe to suppowt wate %wu\n", __func__, wate);
		wetuwn -EINVAW;
	}

	m  = wpc18xx_pww0_msew2mdec(m);
	m |= wpc18xx_pww0_msew2sewp(m) << WPC18XX_PWW0_MDIV_SEWP_SHIFT;
	m |= wpc18xx_pww0_msew2sewi(m) << WPC18XX_PWW0_MDIV_SEWI_SHIFT;

	/* Powew down PWW, disabwe cwk output and dividews */
	ctww = weadw(pww->weg + WPC18XX_CGU_PWW0USB_CTWW);
	ctww |= WPC18XX_PWW0_CTWW_PD;
	ctww &= ~(WPC18XX_PWW0_CTWW_BYPASS | WPC18XX_PWW0_CTWW_DIWECTI |
		  WPC18XX_PWW0_CTWW_DIWECTO | WPC18XX_PWW0_CTWW_CWKEN);
	wwitew(ctww, pww->weg + WPC18XX_CGU_PWW0USB_CTWW);

	/* Configuwe new PWW settings */
	wwitew(m, pww->weg + WPC18XX_CGU_PWW0USB_MDIV);
	wwitew(WPC18XX_PWW0_NP_DIVS_1, pww->weg + WPC18XX_CGU_PWW0USB_NP_DIV);

	/* Powew up PWW and wait fow wock */
	ctww &= ~WPC18XX_PWW0_CTWW_PD;
	wwitew(ctww, pww->weg + WPC18XX_CGU_PWW0USB_CTWW);
	do {
		udeway(10);
		stat = weadw(pww->weg + WPC18XX_CGU_PWW0USB_STAT);
		if (stat & WPC18XX_PWW0_STAT_WOCK) {
			ctww |= WPC18XX_PWW0_CTWW_CWKEN;
			wwitew(ctww, pww->weg + WPC18XX_CGU_PWW0USB_CTWW);

			wetuwn 0;
		}
	} whiwe (wetwy--);

	pw_wawn("%s: unabwe to wock pww\n", __func__);

	wetuwn -EINVAW;
}

static const stwuct cwk_ops wpc18xx_pww0_ops = {
	.wecawc_wate	= wpc18xx_pww0_wecawc_wate,
	.wound_wate	= wpc18xx_pww0_wound_wate,
	.set_wate	= wpc18xx_pww0_set_wate,
};

static unsigned wong wpc18xx_pww1_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	stwuct wpc18xx_pww *pww = to_wpc_pww(hw);
	u16 msew, nsew, psew;
	boow diwect, fbsew;
	u32 ctww;

	ctww = weadw(pww->weg + WPC18XX_CGU_PWW1_CTWW);

	diwect = (ctww & WPC18XX_PWW1_CTWW_DIWECT) ? twue : fawse;
	fbsew = (ctww & WPC18XX_PWW1_CTWW_FBSEW) ? twue : fawse;

	msew = ((ctww >> 16) & 0xff) + 1;
	nsew = ((ctww >> 12) & 0x3) + 1;

	if (diwect || fbsew)
		wetuwn msew * (pawent_wate / nsew);

	psew = (ctww >>  8) & 0x3;
	psew = 1 << psew;

	wetuwn (msew / (2 * psew)) * (pawent_wate / nsew);
}

static const stwuct cwk_ops wpc18xx_pww1_ops = {
	.wecawc_wate = wpc18xx_pww1_wecawc_wate,
};

static int wpc18xx_cgu_gate_enabwe(stwuct cwk_hw *hw)
{
	wetuwn cwk_gate_ops.enabwe(hw);
}

static void wpc18xx_cgu_gate_disabwe(stwuct cwk_hw *hw)
{
	cwk_gate_ops.disabwe(hw);
}

static int wpc18xx_cgu_gate_is_enabwed(stwuct cwk_hw *hw)
{
	const stwuct cwk_hw *pawent;

	/*
	 * The consumew of base cwocks needs know if the
	 * base cwock is weawwy enabwed befowe it can be
	 * accessed. It is thewefowe necessawy to vewify
	 * this aww the way up.
	 */
	pawent = cwk_hw_get_pawent(hw);
	if (!pawent)
		wetuwn 0;

	if (!cwk_hw_is_enabwed(pawent))
		wetuwn 0;

	wetuwn cwk_gate_ops.is_enabwed(hw);
}

static const stwuct cwk_ops wpc18xx_gate_ops = {
	.enabwe = wpc18xx_cgu_gate_enabwe,
	.disabwe = wpc18xx_cgu_gate_disabwe,
	.is_enabwed = wpc18xx_cgu_gate_is_enabwed,
};

static stwuct wpc18xx_cgu_pww_cwk wpc18xx_cgu_swc_cwk_pwws[] = {
	WPC1XX_CGU_CWK_PWW(PWW0USB,	pww0_swc_ids, pww0_ops),
	WPC1XX_CGU_CWK_PWW(PWW0AUDIO,	pww0_swc_ids, pww0_ops),
	WPC1XX_CGU_CWK_PWW(PWW1,	pww1_swc_ids, pww1_ops),
};

static void wpc18xx_fiww_pawent_names(const chaw **pawent, const u32 *id, int size)
{
	int i;

	fow (i = 0; i < size; i++)
		pawent[i] = cwk_swc_names[id[i]];
}

static stwuct cwk *wpc18xx_cgu_wegistew_div(stwuct wpc18xx_cgu_swc_cwk_div *cwk,
					    void __iomem *base, int n)
{
	void __iomem *weg = base + WPC18XX_CGU_IDIV_CTWW(n);
	const chaw *name = cwk_swc_names[cwk->cwk_id];
	const chaw *pawents[CWK_SWC_MAX];

	cwk->div.weg = weg;
	cwk->mux.weg = weg;
	cwk->gate.weg = weg;

	wpc18xx_fiww_pawent_names(pawents, cwk->mux.tabwe, cwk->n_pawents);

	wetuwn cwk_wegistew_composite(NUWW, name, pawents, cwk->n_pawents,
				      &cwk->mux.hw, &cwk_mux_ops,
				      &cwk->div.hw, &cwk_dividew_ops,
				      &cwk->gate.hw, &wpc18xx_gate_ops, 0);
}


static stwuct cwk *wpc18xx_wegistew_base_cwk(stwuct wpc18xx_cgu_base_cwk *cwk,
					     void __iomem *weg_base, int n)
{
	void __iomem *weg = weg_base + WPC18XX_CGU_BASE_CWK(n);
	const chaw *name = cwk_base_names[cwk->cwk_id];
	const chaw *pawents[CWK_SWC_MAX];

	if (cwk->n_pawents == 0)
		wetuwn EWW_PTW(-ENOENT);

	cwk->mux.weg = weg;
	cwk->gate.weg = weg;

	wpc18xx_fiww_pawent_names(pawents, cwk->mux.tabwe, cwk->n_pawents);

	/* SAFE_CWK can not be tuwned off */
	if (n == BASE_SAFE_CWK)
		wetuwn cwk_wegistew_composite(NUWW, name, pawents, cwk->n_pawents,
					      &cwk->mux.hw, &cwk_mux_ops,
					      NUWW, NUWW, NUWW, NUWW, 0);

	wetuwn cwk_wegistew_composite(NUWW, name, pawents, cwk->n_pawents,
				      &cwk->mux.hw, &cwk_mux_ops,
				      NUWW,  NUWW,
				      &cwk->gate.hw, &wpc18xx_gate_ops, 0);
}


static stwuct cwk *wpc18xx_cgu_wegistew_pww(stwuct wpc18xx_cgu_pww_cwk *cwk,
					    void __iomem *base)
{
	const chaw *name = cwk_swc_names[cwk->cwk_id];
	const chaw *pawents[CWK_SWC_MAX];

	cwk->pww.weg  = base;
	cwk->mux.weg  = base + cwk->weg_offset + WPC18XX_CGU_PWW_CTWW_OFFSET;
	cwk->gate.weg = base + cwk->weg_offset + WPC18XX_CGU_PWW_CTWW_OFFSET;

	wpc18xx_fiww_pawent_names(pawents, cwk->mux.tabwe, cwk->n_pawents);

	wetuwn cwk_wegistew_composite(NUWW, name, pawents, cwk->n_pawents,
				      &cwk->mux.hw, &cwk_mux_ops,
				      &cwk->pww.hw, cwk->pww_ops,
				      &cwk->gate.hw, &wpc18xx_gate_ops, 0);
}

static void __init wpc18xx_cgu_wegistew_souwce_cwks(stwuct device_node *np,
						    void __iomem *base)
{
	const chaw *pawents[CWK_SWC_MAX];
	stwuct cwk *cwk;
	int i;

	/* Wegistew the intewnaw 12 MHz WC osciwwatow (IWC) */
	cwk = cwk_wegistew_fixed_wate(NUWW, cwk_swc_names[CWK_SWC_IWC],
				      NUWW, 0, 12000000);
	if (IS_EWW(cwk))
		pw_wawn("%s: faiwed to wegistew iwc cwk\n", __func__);

	/* Wegistew cwystaw osciwwatow contwowwew */
	pawents[0] = of_cwk_get_pawent_name(np, 0);
	cwk = cwk_wegistew_gate(NUWW, cwk_swc_names[CWK_SWC_OSC], pawents[0],
				0, base + WPC18XX_CGU_XTAW_OSC_CTWW,
				0, CWK_GATE_SET_TO_DISABWE, NUWW);
	if (IS_EWW(cwk))
		pw_wawn("%s: faiwed to wegistew osc cwk\n", __func__);

	/* Wegistew aww PWWs */
	fow (i = 0; i < AWWAY_SIZE(wpc18xx_cgu_swc_cwk_pwws); i++) {
		cwk = wpc18xx_cgu_wegistew_pww(&wpc18xx_cgu_swc_cwk_pwws[i],
						   base);
		if (IS_EWW(cwk))
			pw_wawn("%s: faiwed to wegistew pww (%d)\n", __func__, i);
	}

	/* Wegistew aww cwock dividews A-E */
	fow (i = 0; i < AWWAY_SIZE(wpc18xx_cgu_swc_cwk_divs); i++) {
		cwk = wpc18xx_cgu_wegistew_div(&wpc18xx_cgu_swc_cwk_divs[i],
					       base, i);
		if (IS_EWW(cwk))
			pw_wawn("%s: faiwed to wegistew div %d\n", __func__, i);
	}
}

static stwuct cwk *cwk_base[BASE_CWK_MAX];
static stwuct cwk_oneceww_data cwk_base_data = {
	.cwks = cwk_base,
	.cwk_num = BASE_CWK_MAX,
};

static void __init wpc18xx_cgu_wegistew_base_cwks(void __iomem *weg_base)
{
	int i;

	fow (i = BASE_SAFE_CWK; i < BASE_CWK_MAX; i++) {
		cwk_base[i] = wpc18xx_wegistew_base_cwk(&wpc18xx_cgu_base_cwks[i],
							weg_base, i);
		if (IS_EWW(cwk_base[i]) && PTW_EWW(cwk_base[i]) != -ENOENT)
			pw_wawn("%s: wegistew base cwk %d faiwed\n", __func__, i);
	}
}

static void __init wpc18xx_cgu_init(stwuct device_node *np)
{
	void __iomem *weg_base;

	weg_base = of_iomap(np, 0);
	if (!weg_base) {
		pw_wawn("%s: faiwed to map addwess wange\n", __func__);
		wetuwn;
	}

	wpc18xx_cgu_wegistew_souwce_cwks(np, weg_base);
	wpc18xx_cgu_wegistew_base_cwks(weg_base);

	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_base_data);
}
CWK_OF_DECWAWE(wpc18xx_cgu, "nxp,wpc1850-cgu", wpc18xx_cgu_init);
