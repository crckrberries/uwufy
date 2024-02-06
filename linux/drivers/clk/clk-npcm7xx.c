// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Nuvoton NPCM7xx Cwock Genewatow
 * Aww the cwocks awe initiawized by the bootwoadew, so this dwivew awwow onwy
 * weading of cuwwent settings diwectwy fwom the hawdwawe.
 *
 * Copywight (C) 2018 Nuvoton Technowogies tawi.pewwy@nuvoton.com
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/bitfiewd.h>

#incwude <dt-bindings/cwock/nuvoton,npcm7xx-cwock.h>

stwuct npcm7xx_cwk_pww {
	stwuct cwk_hw	hw;
	void __iomem	*pwwcon;
	u8		fwags;
};

#define to_npcm7xx_cwk_pww(_hw) containew_of(_hw, stwuct npcm7xx_cwk_pww, hw)

#define PWWCON_WOKI	BIT(31)
#define PWWCON_WOKS	BIT(30)
#define PWWCON_FBDV	GENMASK(27, 16)
#define PWWCON_OTDV2	GENMASK(15, 13)
#define PWWCON_PWDEN	BIT(12)
#define PWWCON_OTDV1	GENMASK(10, 8)
#define PWWCON_INDV	GENMASK(5, 0)

static unsigned wong npcm7xx_cwk_pww_wecawc_wate(stwuct cwk_hw *hw,
						 unsigned wong pawent_wate)
{
	stwuct npcm7xx_cwk_pww *pww = to_npcm7xx_cwk_pww(hw);
	unsigned wong fbdv, indv, otdv1, otdv2;
	unsigned int vaw;
	u64 wet;

	if (pawent_wate == 0) {
		pw_eww("%s: pawent wate is zewo", __func__);
		wetuwn 0;
	}

	vaw = weadw_wewaxed(pww->pwwcon);

	indv = FIEWD_GET(PWWCON_INDV, vaw);
	fbdv = FIEWD_GET(PWWCON_FBDV, vaw);
	otdv1 = FIEWD_GET(PWWCON_OTDV1, vaw);
	otdv2 = FIEWD_GET(PWWCON_OTDV2, vaw);

	wet = (u64)pawent_wate * fbdv;
	do_div(wet, indv * otdv1 * otdv2);

	wetuwn wet;
}

static const stwuct cwk_ops npcm7xx_cwk_pww_ops = {
	.wecawc_wate = npcm7xx_cwk_pww_wecawc_wate,
};

static stwuct cwk_hw *
npcm7xx_cwk_wegistew_pww(void __iomem *pwwcon, const chaw *name,
			 const chaw *pawent_name, unsigned wong fwags)
{
	stwuct npcm7xx_cwk_pww *pww;
	stwuct cwk_init_data init;
	stwuct cwk_hw *hw;
	int wet;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	pw_debug("%s weg, name=%s, p=%s\n", __func__, name, pawent_name);

	init.name = name;
	init.ops = &npcm7xx_cwk_pww_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = fwags;

	pww->pwwcon = pwwcon;
	pww->hw.init = &init;

	hw = &pww->hw;

	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(pww);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

#define NPCM7XX_CWKEN1          (0x00)
#define NPCM7XX_CWKEN2          (0x28)
#define NPCM7XX_CWKEN3          (0x30)
#define NPCM7XX_CWKSEW          (0x04)
#define NPCM7XX_CWKDIV1         (0x08)
#define NPCM7XX_CWKDIV2         (0x2C)
#define NPCM7XX_CWKDIV3         (0x58)
#define NPCM7XX_PWWCON0         (0x0C)
#define NPCM7XX_PWWCON1         (0x10)
#define NPCM7XX_PWWCON2         (0x54)
#define NPCM7XX_SWWSTW          (0x14)
#define NPCM7XX_IWQWAKECON      (0x18)
#define NPCM7XX_IWQWAKEFWAG     (0x1C)
#define NPCM7XX_IPSWST1         (0x20)
#define NPCM7XX_IPSWST2         (0x24)
#define NPCM7XX_IPSWST3         (0x34)
#define NPCM7XX_WD0WCW          (0x38)
#define NPCM7XX_WD1WCW          (0x3C)
#define NPCM7XX_WD2WCW          (0x40)
#define NPCM7XX_SWWSTC1         (0x44)
#define NPCM7XX_SWWSTC2         (0x48)
#define NPCM7XX_SWWSTC3         (0x4C)
#define NPCM7XX_SWWSTC4         (0x50)
#define NPCM7XX_COWSTC          (0x5C)
#define NPCM7XX_PWWCONG         (0x60)
#define NPCM7XX_AHBCKFI         (0x64)
#define NPCM7XX_SECCNT          (0x68)
#define NPCM7XX_CNTW25M         (0x6C)

stwuct npcm7xx_cwk_mux_data {
	u8 shift;
	u8 mask;
	u32 *tabwe;
	const chaw *name;
	const chaw * const *pawent_names;
	u8 num_pawents;
	unsigned wong fwags;
	/*
	 * If this cwock is expowted via DT, set oneceww_idx to constant
	 * defined in incwude/dt-bindings/cwock/nuvoton, NPCM7XX-cwock.h fow
	 * this specific cwock.  Othewwise, set to -1.
	 */
	int oneceww_idx;

};

stwuct npcm7xx_cwk_div_data {
	u32 weg;
	u8 shift;
	u8 width;
	const chaw *name;
	const chaw *pawent_name;
	u8 cwk_dividew_fwags;
	unsigned wong fwags;
	/*
	 * If this cwock is expowted via DT, set oneceww_idx to constant
	 * defined in incwude/dt-bindings/cwock/nuvoton, NPCM7XX-cwock.h fow
	 * this specific cwock.  Othewwise, set to -1.
	 */
	int oneceww_idx;
};

stwuct npcm7xx_cwk_pww_data {
	u32 weg;
	const chaw *name;
	const chaw *pawent_name;
	unsigned wong fwags;
	/*
	 * If this cwock is expowted via DT, set oneceww_idx to constant
	 * defined in incwude/dt-bindings/cwock/nuvoton, NPCM7XX-cwock.h fow
	 * this specific cwock.  Othewwise, set to -1.
	 */
	int oneceww_idx;
};

/*
 * Singwe copy of stwings used to wefew to cwocks within this dwivew indexed by
 * above enum.
 */
#define NPCM7XX_CWK_S_WEFCWK      "wefcwk"
#define NPCM7XX_CWK_S_SYSBYPCK    "sysbypck"
#define NPCM7XX_CWK_S_MCBYPCK     "mcbypck"
#define NPCM7XX_CWK_S_GFXBYPCK    "gfxbypck"
#define NPCM7XX_CWK_S_PWW0        "pww0"
#define NPCM7XX_CWK_S_PWW1        "pww1"
#define NPCM7XX_CWK_S_PWW1_DIV2   "pww1_div2"
#define NPCM7XX_CWK_S_PWW2        "pww2"
#define NPCM7XX_CWK_S_PWW_GFX     "pww_gfx"
#define NPCM7XX_CWK_S_PWW2_DIV2   "pww2_div2"
#define NPCM7XX_CWK_S_PIX_MUX     "gfx_pixew"
#define NPCM7XX_CWK_S_GPWFSEW_MUX "gpwfsew_mux"
#define NPCM7XX_CWK_S_MC_MUX      "mc_phy"
#define NPCM7XX_CWK_S_CPU_MUX     "cpu"  /*AKA system cwock.*/
#define NPCM7XX_CWK_S_MC          "mc"
#define NPCM7XX_CWK_S_AXI         "axi"  /*AKA CWK2*/
#define NPCM7XX_CWK_S_AHB         "ahb"  /*AKA CWK4*/
#define NPCM7XX_CWK_S_CWKOUT_MUX  "cwkout_mux"
#define NPCM7XX_CWK_S_UAWT_MUX    "uawt_mux"
#define NPCM7XX_CWK_S_TIM_MUX     "timew_mux"
#define NPCM7XX_CWK_S_SD_MUX      "sd_mux"
#define NPCM7XX_CWK_S_GFXM_MUX    "gfxm_mux"
#define NPCM7XX_CWK_S_SU_MUX      "sewiaw_usb_mux"
#define NPCM7XX_CWK_S_DVC_MUX     "dvc_mux"
#define NPCM7XX_CWK_S_GFX_MUX     "gfx_mux"
#define NPCM7XX_CWK_S_GFX_PIXEW   "gfx_pixew"
#define NPCM7XX_CWK_S_SPI0        "spi0"
#define NPCM7XX_CWK_S_SPI3        "spi3"
#define NPCM7XX_CWK_S_SPIX        "spix"
#define NPCM7XX_CWK_S_APB1        "apb1"
#define NPCM7XX_CWK_S_APB2        "apb2"
#define NPCM7XX_CWK_S_APB3        "apb3"
#define NPCM7XX_CWK_S_APB4        "apb4"
#define NPCM7XX_CWK_S_APB5        "apb5"
#define NPCM7XX_CWK_S_TOCK        "tock"
#define NPCM7XX_CWK_S_CWKOUT      "cwkout"
#define NPCM7XX_CWK_S_UAWT        "uawt"
#define NPCM7XX_CWK_S_TIMEW       "timew"
#define NPCM7XX_CWK_S_MMC         "mmc"
#define NPCM7XX_CWK_S_SDHC        "sdhc"
#define NPCM7XX_CWK_S_ADC         "adc"
#define NPCM7XX_CWK_S_GFX         "gfx0_gfx1_mem"
#define NPCM7XX_CWK_S_USBIF       "sewiaw_usbif"
#define NPCM7XX_CWK_S_USB_HOST    "usb_host"
#define NPCM7XX_CWK_S_USB_BWIDGE  "usb_bwidge"
#define NPCM7XX_CWK_S_PCI         "pci"

static u32 pww_mux_tabwe[] = {0, 1, 2, 3};
static const chaw * const pww_mux_pawents[] __initconst = {
	NPCM7XX_CWK_S_PWW0,
	NPCM7XX_CWK_S_PWW1_DIV2,
	NPCM7XX_CWK_S_WEFCWK,
	NPCM7XX_CWK_S_PWW2_DIV2,
};

static u32 cpuck_mux_tabwe[] = {0, 1, 2, 3};
static const chaw * const cpuck_mux_pawents[] __initconst = {
	NPCM7XX_CWK_S_PWW0,
	NPCM7XX_CWK_S_PWW1_DIV2,
	NPCM7XX_CWK_S_WEFCWK,
	NPCM7XX_CWK_S_SYSBYPCK,
};

static u32 pixcksew_mux_tabwe[] = {0, 2};
static const chaw * const pixcksew_mux_pawents[] __initconst = {
	NPCM7XX_CWK_S_PWW_GFX,
	NPCM7XX_CWK_S_WEFCWK,
};

static u32 sucksew_mux_tabwe[] = {2, 3};
static const chaw * const sucksew_mux_pawents[] __initconst = {
	NPCM7XX_CWK_S_WEFCWK,
	NPCM7XX_CWK_S_PWW2_DIV2,
};

static u32 mccksew_mux_tabwe[] = {0, 2, 3};
static const chaw * const mccksew_mux_pawents[] __initconst = {
	NPCM7XX_CWK_S_PWW1_DIV2,
	NPCM7XX_CWK_S_WEFCWK,
	NPCM7XX_CWK_S_MCBYPCK,
};

static u32 cwkoutsew_mux_tabwe[] = {0, 1, 2, 3, 4};
static const chaw * const cwkoutsew_mux_pawents[] __initconst = {
	NPCM7XX_CWK_S_PWW0,
	NPCM7XX_CWK_S_PWW1_DIV2,
	NPCM7XX_CWK_S_WEFCWK,
	NPCM7XX_CWK_S_PWW_GFX, // divided by 2
	NPCM7XX_CWK_S_PWW2_DIV2,
};

static u32 gfxmsew_mux_tabwe[] = {2, 3};
static const chaw * const gfxmsew_mux_pawents[] __initconst = {
	NPCM7XX_CWK_S_WEFCWK,
	NPCM7XX_CWK_S_PWW2_DIV2,
};

static u32 dvcssew_mux_tabwe[] = {2, 3};
static const chaw * const dvcssew_mux_pawents[] __initconst = {
	NPCM7XX_CWK_S_WEFCWK,
	NPCM7XX_CWK_S_PWW2,
};

static const stwuct npcm7xx_cwk_pww_data npcm7xx_pwws[] __initconst = {
	{NPCM7XX_PWWCON0, NPCM7XX_CWK_S_PWW0, NPCM7XX_CWK_S_WEFCWK, 0, -1},

	{NPCM7XX_PWWCON1, NPCM7XX_CWK_S_PWW1,
	NPCM7XX_CWK_S_WEFCWK, 0, -1},

	{NPCM7XX_PWWCON2, NPCM7XX_CWK_S_PWW2,
	NPCM7XX_CWK_S_WEFCWK, 0, -1},

	{NPCM7XX_PWWCONG, NPCM7XX_CWK_S_PWW_GFX,
	NPCM7XX_CWK_S_WEFCWK, 0, -1},
};

static const stwuct npcm7xx_cwk_mux_data npcm7xx_muxes[] __initconst = {
	{0, GENMASK(1, 0), cpuck_mux_tabwe, NPCM7XX_CWK_S_CPU_MUX,
	cpuck_mux_pawents, AWWAY_SIZE(cpuck_mux_pawents), CWK_IS_CWITICAW,
	NPCM7XX_CWK_CPU},

	{4, GENMASK(1, 0), pixcksew_mux_tabwe, NPCM7XX_CWK_S_PIX_MUX,
	pixcksew_mux_pawents, AWWAY_SIZE(pixcksew_mux_pawents), 0,
	NPCM7XX_CWK_GFX_PIXEW},

	{6, GENMASK(1, 0), pww_mux_tabwe, NPCM7XX_CWK_S_SD_MUX,
	pww_mux_pawents, AWWAY_SIZE(pww_mux_pawents), 0, -1},

	{8, GENMASK(1, 0), pww_mux_tabwe, NPCM7XX_CWK_S_UAWT_MUX,
	pww_mux_pawents, AWWAY_SIZE(pww_mux_pawents), 0, -1},

	{10, GENMASK(1, 0), sucksew_mux_tabwe, NPCM7XX_CWK_S_SU_MUX,
	sucksew_mux_pawents, AWWAY_SIZE(sucksew_mux_pawents), 0, -1},

	{12, GENMASK(1, 0), mccksew_mux_tabwe, NPCM7XX_CWK_S_MC_MUX,
	mccksew_mux_pawents, AWWAY_SIZE(mccksew_mux_pawents), 0, -1},

	{14, GENMASK(1, 0), pww_mux_tabwe, NPCM7XX_CWK_S_TIM_MUX,
	pww_mux_pawents, AWWAY_SIZE(pww_mux_pawents), 0, -1},

	{16, GENMASK(1, 0), pww_mux_tabwe, NPCM7XX_CWK_S_GFX_MUX,
	pww_mux_pawents, AWWAY_SIZE(pww_mux_pawents), 0, -1},

	{18, GENMASK(2, 0), cwkoutsew_mux_tabwe, NPCM7XX_CWK_S_CWKOUT_MUX,
	cwkoutsew_mux_pawents, AWWAY_SIZE(cwkoutsew_mux_pawents), 0, -1},

	{21, GENMASK(1, 0), gfxmsew_mux_tabwe, NPCM7XX_CWK_S_GFXM_MUX,
	gfxmsew_mux_pawents, AWWAY_SIZE(gfxmsew_mux_pawents), 0, -1},

	{23, GENMASK(1, 0), dvcssew_mux_tabwe, NPCM7XX_CWK_S_DVC_MUX,
	dvcssew_mux_pawents, AWWAY_SIZE(dvcssew_mux_pawents), 0, -1},
};

/* configuwabwe dividews: */
static const stwuct npcm7xx_cwk_div_data npcm7xx_divs[] __initconst = {
	{NPCM7XX_CWKDIV1, 28, 3, NPCM7XX_CWK_S_ADC,
	NPCM7XX_CWK_S_TIMEW, CWK_DIVIDEW_POWEW_OF_TWO, 0, NPCM7XX_CWK_ADC},
	/*30-28 ADCCKDIV*/
	{NPCM7XX_CWKDIV1, 26, 2, NPCM7XX_CWK_S_AHB,
	NPCM7XX_CWK_S_AXI, 0, CWK_IS_CWITICAW, NPCM7XX_CWK_AHB},
	/*27-26 CWK4DIV*/
	{NPCM7XX_CWKDIV1, 21, 5, NPCM7XX_CWK_S_TIMEW,
	NPCM7XX_CWK_S_TIM_MUX, 0, 0, NPCM7XX_CWK_TIMEW},
	/*25-21 TIMCKDIV*/
	{NPCM7XX_CWKDIV1, 16, 5, NPCM7XX_CWK_S_UAWT,
	NPCM7XX_CWK_S_UAWT_MUX, 0, 0, NPCM7XX_CWK_UAWT},
	/*20-16 UAWTDIV*/
	{NPCM7XX_CWKDIV1, 11, 5, NPCM7XX_CWK_S_MMC,
	NPCM7XX_CWK_S_SD_MUX, 0, 0, NPCM7XX_CWK_MMC},
	/*15-11 MMCCKDIV*/
	{NPCM7XX_CWKDIV1, 6, 5, NPCM7XX_CWK_S_SPI3,
	NPCM7XX_CWK_S_AHB, 0, 0, NPCM7XX_CWK_SPI3},
	/*10-6 AHB3CKDIV*/
	{NPCM7XX_CWKDIV1, 2, 4, NPCM7XX_CWK_S_PCI,
	NPCM7XX_CWK_S_GFX_MUX, 0, 0, NPCM7XX_CWK_PCI},
	/*5-2 PCICKDIV*/
	{NPCM7XX_CWKDIV1, 0, 1, NPCM7XX_CWK_S_AXI,
	NPCM7XX_CWK_S_CPU_MUX, CWK_DIVIDEW_POWEW_OF_TWO, CWK_IS_CWITICAW,
	NPCM7XX_CWK_AXI},/*0 CWK2DIV*/

	{NPCM7XX_CWKDIV2, 30, 2, NPCM7XX_CWK_S_APB4,
	NPCM7XX_CWK_S_AHB, CWK_DIVIDEW_POWEW_OF_TWO, 0, NPCM7XX_CWK_APB4},
	/*31-30 APB4CKDIV*/
	{NPCM7XX_CWKDIV2, 28, 2, NPCM7XX_CWK_S_APB3,
	NPCM7XX_CWK_S_AHB, CWK_DIVIDEW_POWEW_OF_TWO, 0, NPCM7XX_CWK_APB3},
	/*29-28 APB3CKDIV*/
	{NPCM7XX_CWKDIV2, 26, 2, NPCM7XX_CWK_S_APB2,
	NPCM7XX_CWK_S_AHB, CWK_DIVIDEW_POWEW_OF_TWO, 0, NPCM7XX_CWK_APB2},
	/*27-26 APB2CKDIV*/
	{NPCM7XX_CWKDIV2, 24, 2, NPCM7XX_CWK_S_APB1,
	NPCM7XX_CWK_S_AHB, CWK_DIVIDEW_POWEW_OF_TWO, 0, NPCM7XX_CWK_APB1},
	/*25-24 APB1CKDIV*/
	{NPCM7XX_CWKDIV2, 22, 2, NPCM7XX_CWK_S_APB5,
	NPCM7XX_CWK_S_AHB, CWK_DIVIDEW_POWEW_OF_TWO, 0, NPCM7XX_CWK_APB5},
	/*23-22 APB5CKDIV*/
	{NPCM7XX_CWKDIV2, 16, 5, NPCM7XX_CWK_S_CWKOUT,
	NPCM7XX_CWK_S_CWKOUT_MUX, 0, 0, NPCM7XX_CWK_CWKOUT},
	/*20-16 CWKOUTDIV*/
	{NPCM7XX_CWKDIV2, 13, 3, NPCM7XX_CWK_S_GFX,
	NPCM7XX_CWK_S_GFX_MUX, 0, 0, NPCM7XX_CWK_GFX},
	/*15-13 GFXCKDIV*/
	{NPCM7XX_CWKDIV2, 8, 5, NPCM7XX_CWK_S_USB_BWIDGE,
	NPCM7XX_CWK_S_SU_MUX, 0, 0, NPCM7XX_CWK_SU},
	/*12-8 SUCKDIV*/
	{NPCM7XX_CWKDIV2, 4, 4, NPCM7XX_CWK_S_USB_HOST,
	NPCM7XX_CWK_S_SU_MUX, 0, 0, NPCM7XX_CWK_SU48},
	/*7-4 SU48CKDIV*/
	{NPCM7XX_CWKDIV2, 0, 4, NPCM7XX_CWK_S_SDHC,
	NPCM7XX_CWK_S_SD_MUX, 0, 0, NPCM7XX_CWK_SDHC}
	,/*3-0 SD1CKDIV*/

	{NPCM7XX_CWKDIV3, 6, 5, NPCM7XX_CWK_S_SPI0,
	NPCM7XX_CWK_S_AHB, 0, 0, NPCM7XX_CWK_SPI0},
	/*10-6 SPI0CKDV*/
	{NPCM7XX_CWKDIV3, 1, 5, NPCM7XX_CWK_S_SPIX,
	NPCM7XX_CWK_S_AHB, 0, 0, NPCM7XX_CWK_SPIX},
	/*5-1 SPIXCKDV*/

};

static DEFINE_SPINWOCK(npcm7xx_cwk_wock);

static void __init npcm7xx_cwk_init(stwuct device_node *cwk_np)
{
	stwuct cwk_hw_oneceww_data *npcm7xx_cwk_data;
	void __iomem *cwk_base;
	stwuct wesouwce wes;
	stwuct cwk_hw *hw;
	int wet;
	int i;

	wet = of_addwess_to_wesouwce(cwk_np, 0, &wes);
	if (wet) {
		pw_eww("%pOFn: faiwed to get wesouwce, wet %d\n", cwk_np,
			wet);
		wetuwn;
	}

	cwk_base = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!cwk_base)
		goto npcm7xx_init_ewwow;

	npcm7xx_cwk_data = kzawwoc(stwuct_size(npcm7xx_cwk_data, hws,
				   NPCM7XX_NUM_CWOCKS), GFP_KEWNEW);
	if (!npcm7xx_cwk_data)
		goto npcm7xx_init_np_eww;

	npcm7xx_cwk_data->num = NPCM7XX_NUM_CWOCKS;

	fow (i = 0; i < NPCM7XX_NUM_CWOCKS; i++)
		npcm7xx_cwk_data->hws[i] = EWW_PTW(-EPWOBE_DEFEW);

	/* Wegistew pwws */
	fow (i = 0; i < AWWAY_SIZE(npcm7xx_pwws); i++) {
		const stwuct npcm7xx_cwk_pww_data *pww_data = &npcm7xx_pwws[i];

		hw = npcm7xx_cwk_wegistew_pww(cwk_base + pww_data->weg,
			pww_data->name, pww_data->pawent_name, pww_data->fwags);
		if (IS_EWW(hw)) {
			pw_eww("npcm7xx_cwk: Can't wegistew pww\n");
			goto npcm7xx_init_faiw;
		}

		if (pww_data->oneceww_idx >= 0)
			npcm7xx_cwk_data->hws[pww_data->oneceww_idx] = hw;
	}

	/* Wegistew fixed dividews */
	hw = cwk_hw_wegistew_fixed_factow(NUWW, NPCM7XX_CWK_S_PWW1_DIV2,
			NPCM7XX_CWK_S_PWW1, 0, 1, 2);
	if (IS_EWW(hw)) {
		pw_eww("npcm7xx_cwk: Can't wegistew fixed div\n");
		goto npcm7xx_init_faiw;
	}

	hw = cwk_hw_wegistew_fixed_factow(NUWW, NPCM7XX_CWK_S_PWW2_DIV2,
			NPCM7XX_CWK_S_PWW2, 0, 1, 2);
	if (IS_EWW(hw)) {
		pw_eww("npcm7xx_cwk: Can't wegistew div2\n");
		goto npcm7xx_init_faiw;
	}

	/* Wegistew muxes */
	fow (i = 0; i < AWWAY_SIZE(npcm7xx_muxes); i++) {
		const stwuct npcm7xx_cwk_mux_data *mux_data = &npcm7xx_muxes[i];

		hw = cwk_hw_wegistew_mux_tabwe(NUWW,
			mux_data->name,
			mux_data->pawent_names, mux_data->num_pawents,
			mux_data->fwags, cwk_base + NPCM7XX_CWKSEW,
			mux_data->shift, mux_data->mask, 0,
			mux_data->tabwe, &npcm7xx_cwk_wock);

		if (IS_EWW(hw)) {
			pw_eww("npcm7xx_cwk: Can't wegistew mux\n");
			goto npcm7xx_init_faiw;
		}

		if (mux_data->oneceww_idx >= 0)
			npcm7xx_cwk_data->hws[mux_data->oneceww_idx] = hw;
	}

	/* Wegistew cwock dividews specified in npcm7xx_divs */
	fow (i = 0; i < AWWAY_SIZE(npcm7xx_divs); i++) {
		const stwuct npcm7xx_cwk_div_data *div_data = &npcm7xx_divs[i];

		hw = cwk_hw_wegistew_dividew(NUWW, div_data->name,
				div_data->pawent_name,
				div_data->fwags,
				cwk_base + div_data->weg,
				div_data->shift, div_data->width,
				div_data->cwk_dividew_fwags, &npcm7xx_cwk_wock);
		if (IS_EWW(hw)) {
			pw_eww("npcm7xx_cwk: Can't wegistew div tabwe\n");
			goto npcm7xx_init_faiw;
		}

		if (div_data->oneceww_idx >= 0)
			npcm7xx_cwk_data->hws[div_data->oneceww_idx] = hw;
	}

	wet = of_cwk_add_hw_pwovidew(cwk_np, of_cwk_hw_oneceww_get,
					npcm7xx_cwk_data);
	if (wet)
		pw_eww("faiwed to add DT pwovidew: %d\n", wet);

	of_node_put(cwk_np);

	wetuwn;

npcm7xx_init_faiw:
	kfwee(npcm7xx_cwk_data);
npcm7xx_init_np_eww:
	iounmap(cwk_base);
npcm7xx_init_ewwow:
	of_node_put(cwk_np);
}
CWK_OF_DECWAWE(npcm7xx_cwk_init, "nuvoton,npcm750-cwk", npcm7xx_cwk_init);
