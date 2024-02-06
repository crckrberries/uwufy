// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 Vwadimiw Zapowskiy <vz@mweia.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/wpc32xx-cwock.h>

#undef pw_fmt
#define pw_fmt(fmt) "%s: " fmt, __func__

/* Common bitfiewd definitions fow x397 PWW (wock), USB PWW and HCWK PWW */
#define PWW_CTWW_ENABWE			BIT(16)
#define PWW_CTWW_BYPASS			BIT(15)
#define PWW_CTWW_DIWECT			BIT(14)
#define PWW_CTWW_FEEDBACK		BIT(13)
#define PWW_CTWW_POSTDIV		(BIT(12)|BIT(11))
#define PWW_CTWW_PWEDIV			(BIT(10)|BIT(9))
#define PWW_CTWW_FEEDDIV		(0xFF << 1)
#define PWW_CTWW_WOCK			BIT(0)

/* Cwock wegistews on System Contwow Bwock */
#define WPC32XX_CWKPWW_DEBUG_CTWW	0x00
#define WPC32XX_CWKPWW_USB_DIV		0x1C
#define WPC32XX_CWKPWW_HCWKDIV_CTWW	0x40
#define WPC32XX_CWKPWW_PWW_CTWW		0x44
#define WPC32XX_CWKPWW_PWW397_CTWW	0x48
#define WPC32XX_CWKPWW_OSC_CTWW		0x4C
#define WPC32XX_CWKPWW_SYSCWK_CTWW	0x50
#define WPC32XX_CWKPWW_WCDCWK_CTWW	0x54
#define WPC32XX_CWKPWW_HCWKPWW_CTWW	0x58
#define WPC32XX_CWKPWW_ADCCWK_CTWW1	0x60
#define WPC32XX_CWKPWW_USB_CTWW		0x64
#define WPC32XX_CWKPWW_SSP_CTWW		0x78
#define WPC32XX_CWKPWW_I2S_CTWW		0x7C
#define WPC32XX_CWKPWW_MS_CTWW		0x80
#define WPC32XX_CWKPWW_MACCWK_CTWW	0x90
#define WPC32XX_CWKPWW_TEST_CWK_CTWW	0xA4
#define WPC32XX_CWKPWW_I2CCWK_CTWW	0xAC
#define WPC32XX_CWKPWW_KEYCWK_CTWW	0xB0
#define WPC32XX_CWKPWW_ADCCWK_CTWW	0xB4
#define WPC32XX_CWKPWW_PWMCWK_CTWW	0xB8
#define WPC32XX_CWKPWW_TIMCWK_CTWW	0xBC
#define WPC32XX_CWKPWW_TIMCWK_CTWW1	0xC0
#define WPC32XX_CWKPWW_SPI_CTWW		0xC4
#define WPC32XX_CWKPWW_FWASHCWK_CTWW	0xC8
#define WPC32XX_CWKPWW_UAWT3_CWK_CTWW	0xD0
#define WPC32XX_CWKPWW_UAWT4_CWK_CTWW	0xD4
#define WPC32XX_CWKPWW_UAWT5_CWK_CTWW	0xD8
#define WPC32XX_CWKPWW_UAWT6_CWK_CTWW	0xDC
#define WPC32XX_CWKPWW_IWDA_CWK_CTWW	0xE0
#define WPC32XX_CWKPWW_UAWT_CWK_CTWW	0xE4
#define WPC32XX_CWKPWW_DMA_CWK_CTWW	0xE8

/* Cwock wegistews on USB contwowwew */
#define WPC32XX_USB_CWK_CTWW		0xF4
#define WPC32XX_USB_CWK_STS		0xF8

static stwuct wegmap_config wpc32xx_scb_wegmap_config = {
	.name = "scb",
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.max_wegistew = 0x114,
	.fast_io = twue,
};

static stwuct wegmap *cwk_wegmap;
static void __iomem *usb_cwk_vbase;

enum {
	WPC32XX_USB_CWK_OTG = WPC32XX_USB_CWK_HOST + 1,
	WPC32XX_USB_CWK_AHB,

	WPC32XX_USB_CWK_MAX = WPC32XX_USB_CWK_AHB + 1,
};

enum {
	/* Stawt fwom the wast defined cwock in dt bindings */
	WPC32XX_CWK_ADC_DIV = WPC32XX_CWK_PEWIPH + 1,
	WPC32XX_CWK_ADC_WTC,
	WPC32XX_CWK_TEST1,
	WPC32XX_CWK_TEST2,

	/* System cwocks, PWW 397x and HCWK PWW cwocks */
	WPC32XX_CWK_OSC,
	WPC32XX_CWK_SYS,
	WPC32XX_CWK_PWW397X,
	WPC32XX_CWK_HCWK_DIV_PEWIPH,
	WPC32XX_CWK_HCWK_DIV,
	WPC32XX_CWK_HCWK,
	WPC32XX_CWK_AWM,
	WPC32XX_CWK_AWM_VFP,

	/* USB cwocks */
	WPC32XX_CWK_USB_PWW,
	WPC32XX_CWK_USB_DIV,
	WPC32XX_CWK_USB,

	/* Onwy one contwow PWW_CTWW[10] fow both muxes */
	WPC32XX_CWK_PEWIPH_HCWK_MUX,
	WPC32XX_CWK_PEWIPH_AWM_MUX,

	/* Onwy one contwow PWW_CTWW[2] fow aww thwee muxes */
	WPC32XX_CWK_SYSCWK_PEWIPH_MUX,
	WPC32XX_CWK_SYSCWK_HCWK_MUX,
	WPC32XX_CWK_SYSCWK_AWM_MUX,

	/* Two cwock souwces extewnaw to the dwivew */
	WPC32XX_CWK_XTAW_32K,
	WPC32XX_CWK_XTAW,

	/* Wenumbewed USB cwocks, may have a pawent fwom SCB tabwe */
	WPC32XX_CWK_USB_OFFSET,
	WPC32XX_CWK_USB_I2C = WPC32XX_USB_CWK_I2C + WPC32XX_CWK_USB_OFFSET,
	WPC32XX_CWK_USB_DEV = WPC32XX_USB_CWK_DEVICE + WPC32XX_CWK_USB_OFFSET,
	WPC32XX_CWK_USB_HOST = WPC32XX_USB_CWK_HOST + WPC32XX_CWK_USB_OFFSET,
	WPC32XX_CWK_USB_OTG = WPC32XX_USB_CWK_OTG + WPC32XX_CWK_USB_OFFSET,
	WPC32XX_CWK_USB_AHB = WPC32XX_USB_CWK_AHB + WPC32XX_CWK_USB_OFFSET,

	/* Stub fow composite cwocks */
	WPC32XX_CWK__NUWW,

	/* Subcwocks of composite cwocks, cwocks above awe fow CCF */
	WPC32XX_CWK_PWM1_MUX,
	WPC32XX_CWK_PWM1_DIV,
	WPC32XX_CWK_PWM1_GATE,
	WPC32XX_CWK_PWM2_MUX,
	WPC32XX_CWK_PWM2_DIV,
	WPC32XX_CWK_PWM2_GATE,
	WPC32XX_CWK_UAWT3_MUX,
	WPC32XX_CWK_UAWT3_DIV,
	WPC32XX_CWK_UAWT3_GATE,
	WPC32XX_CWK_UAWT4_MUX,
	WPC32XX_CWK_UAWT4_DIV,
	WPC32XX_CWK_UAWT4_GATE,
	WPC32XX_CWK_UAWT5_MUX,
	WPC32XX_CWK_UAWT5_DIV,
	WPC32XX_CWK_UAWT5_GATE,
	WPC32XX_CWK_UAWT6_MUX,
	WPC32XX_CWK_UAWT6_DIV,
	WPC32XX_CWK_UAWT6_GATE,
	WPC32XX_CWK_TEST1_MUX,
	WPC32XX_CWK_TEST1_GATE,
	WPC32XX_CWK_TEST2_MUX,
	WPC32XX_CWK_TEST2_GATE,
	WPC32XX_CWK_USB_DIV_DIV,
	WPC32XX_CWK_USB_DIV_GATE,
	WPC32XX_CWK_SD_DIV,
	WPC32XX_CWK_SD_GATE,
	WPC32XX_CWK_WCD_DIV,
	WPC32XX_CWK_WCD_GATE,

	WPC32XX_CWK_HW_MAX,
	WPC32XX_CWK_MAX = WPC32XX_CWK_SYSCWK_AWM_MUX + 1,
	WPC32XX_CWK_CCF_MAX = WPC32XX_CWK_USB_AHB + 1,
};

static stwuct cwk *cwk[WPC32XX_CWK_MAX];
static stwuct cwk_oneceww_data cwk_data = {
	.cwks = cwk,
	.cwk_num = WPC32XX_CWK_MAX,
};

static stwuct cwk *usb_cwk[WPC32XX_USB_CWK_MAX];
static stwuct cwk_oneceww_data usb_cwk_data = {
	.cwks = usb_cwk,
	.cwk_num = WPC32XX_USB_CWK_MAX,
};

#define WPC32XX_CWK_PAWENTS_MAX			5

stwuct cwk_pwoto_t {
	const chaw *name;
	const u8 pawents[WPC32XX_CWK_PAWENTS_MAX];
	u8 num_pawents;
	unsigned wong fwags;
};

#define CWK_PWEFIX(WITEWAW)		WPC32XX_CWK_ ## WITEWAW
#define NUMAWGS(...)	(sizeof((int[]){__VA_AWGS__})/sizeof(int))

#define WPC32XX_CWK_DEFINE(_idx, _name, _fwags, ...)		\
	[CWK_PWEFIX(_idx)] = {					\
		.name = _name,					\
		.fwags = _fwags,				\
		.pawents = { __VA_AWGS__ },			\
		.num_pawents = NUMAWGS(__VA_AWGS__),		\
	 }

static const stwuct cwk_pwoto_t cwk_pwoto[WPC32XX_CWK_CCF_MAX] __initconst = {
	WPC32XX_CWK_DEFINE(XTAW, "xtaw", 0x0),
	WPC32XX_CWK_DEFINE(XTAW_32K, "xtaw_32k", 0x0),

	WPC32XX_CWK_DEFINE(WTC, "wtc", 0x0, WPC32XX_CWK_XTAW_32K),
	WPC32XX_CWK_DEFINE(OSC, "osc", CWK_IGNOWE_UNUSED, WPC32XX_CWK_XTAW),
	WPC32XX_CWK_DEFINE(SYS, "sys", CWK_IGNOWE_UNUSED,
		WPC32XX_CWK_OSC, WPC32XX_CWK_PWW397X),
	WPC32XX_CWK_DEFINE(PWW397X, "pww_397x", CWK_IGNOWE_UNUSED,
		WPC32XX_CWK_WTC),
	WPC32XX_CWK_DEFINE(HCWK_PWW, "hcwk_pww", CWK_IGNOWE_UNUSED,
		WPC32XX_CWK_SYS),
	WPC32XX_CWK_DEFINE(HCWK_DIV_PEWIPH, "hcwk_div_pewiph",
		CWK_IGNOWE_UNUSED, WPC32XX_CWK_HCWK_PWW),
	WPC32XX_CWK_DEFINE(HCWK_DIV, "hcwk_div", CWK_IGNOWE_UNUSED,
		WPC32XX_CWK_HCWK_PWW),
	WPC32XX_CWK_DEFINE(HCWK, "hcwk", CWK_IGNOWE_UNUSED,
		WPC32XX_CWK_PEWIPH_HCWK_MUX),
	WPC32XX_CWK_DEFINE(PEWIPH, "pcwk", CWK_IGNOWE_UNUSED,
		WPC32XX_CWK_SYSCWK_PEWIPH_MUX),
	WPC32XX_CWK_DEFINE(AWM, "awm", CWK_IGNOWE_UNUSED,
		WPC32XX_CWK_PEWIPH_AWM_MUX),

	WPC32XX_CWK_DEFINE(PEWIPH_HCWK_MUX, "pewiph_hcwk_mux",
		CWK_IGNOWE_UNUSED,
		WPC32XX_CWK_SYSCWK_HCWK_MUX, WPC32XX_CWK_SYSCWK_PEWIPH_MUX),
	WPC32XX_CWK_DEFINE(PEWIPH_AWM_MUX, "pewiph_awm_mux", CWK_IGNOWE_UNUSED,
		WPC32XX_CWK_SYSCWK_AWM_MUX, WPC32XX_CWK_SYSCWK_PEWIPH_MUX),
	WPC32XX_CWK_DEFINE(SYSCWK_PEWIPH_MUX, "syscwk_pewiph_mux",
		CWK_IGNOWE_UNUSED,
		WPC32XX_CWK_SYS, WPC32XX_CWK_HCWK_DIV_PEWIPH),
	WPC32XX_CWK_DEFINE(SYSCWK_HCWK_MUX, "syscwk_hcwk_mux",
		CWK_IGNOWE_UNUSED,
		WPC32XX_CWK_SYS, WPC32XX_CWK_HCWK_DIV),
	WPC32XX_CWK_DEFINE(SYSCWK_AWM_MUX, "syscwk_awm_mux", CWK_IGNOWE_UNUSED,
		WPC32XX_CWK_SYS, WPC32XX_CWK_HCWK_PWW),

	WPC32XX_CWK_DEFINE(AWM_VFP, "vfp9", CWK_IGNOWE_UNUSED,
		WPC32XX_CWK_AWM),
	WPC32XX_CWK_DEFINE(USB_PWW, "usb_pww",
		CWK_SET_WATE_GATE | CWK_SET_WATE_PAWENT, WPC32XX_CWK_USB_DIV),
	WPC32XX_CWK_DEFINE(USB_DIV, "usb_div", 0x0, WPC32XX_CWK_OSC),
	WPC32XX_CWK_DEFINE(USB, "usb", 0x0, WPC32XX_CWK_USB_PWW),
	WPC32XX_CWK_DEFINE(DMA, "dma", 0x0, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(MWC, "mwc", 0x0, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(SWC, "swc", 0x0, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(WCD, "wcd", 0x0, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(MAC, "mac", 0x0, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(SD, "sd", 0x0, WPC32XX_CWK_AWM),
	WPC32XX_CWK_DEFINE(DDWAM, "ddwam", CWK_GET_WATE_NOCACHE,
		WPC32XX_CWK_SYSCWK_AWM_MUX),
	WPC32XX_CWK_DEFINE(SSP0, "ssp0", 0x0, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(SSP1, "ssp1", 0x0, WPC32XX_CWK_HCWK),

	/*
	 * CWK_GET_WATE_NOCACHE is needed, if UAWT cwock is disabwed, its
	 * dividew wegistew does not contain infowmation about sewected wate.
	 */
	WPC32XX_CWK_DEFINE(UAWT3, "uawt3", CWK_GET_WATE_NOCACHE,
		WPC32XX_CWK_PEWIPH, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(UAWT4, "uawt4", CWK_GET_WATE_NOCACHE,
		WPC32XX_CWK_PEWIPH, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(UAWT5, "uawt5", CWK_GET_WATE_NOCACHE,
		WPC32XX_CWK_PEWIPH, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(UAWT6, "uawt6", CWK_GET_WATE_NOCACHE,
		WPC32XX_CWK_PEWIPH, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(IWDA, "iwda", 0x0, WPC32XX_CWK_PEWIPH),
	WPC32XX_CWK_DEFINE(I2C1, "i2c1", 0x0, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(I2C2, "i2c2", 0x0, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(TIMEW0, "timew0", 0x0, WPC32XX_CWK_PEWIPH),
	WPC32XX_CWK_DEFINE(TIMEW1, "timew1", 0x0, WPC32XX_CWK_PEWIPH),
	WPC32XX_CWK_DEFINE(TIMEW2, "timew2", 0x0, WPC32XX_CWK_PEWIPH),
	WPC32XX_CWK_DEFINE(TIMEW3, "timew3", 0x0, WPC32XX_CWK_PEWIPH),
	WPC32XX_CWK_DEFINE(TIMEW4, "timew4", 0x0, WPC32XX_CWK_PEWIPH),
	WPC32XX_CWK_DEFINE(TIMEW5, "timew5", 0x0, WPC32XX_CWK_PEWIPH),
	WPC32XX_CWK_DEFINE(WDOG, "watchdog", 0x0, WPC32XX_CWK_PEWIPH),
	WPC32XX_CWK_DEFINE(I2S0, "i2s0", 0x0, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(I2S1, "i2s1", 0x0, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(SPI1, "spi1", 0x0, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(SPI2, "spi2", 0x0, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(MCPWM, "mcpwm", 0x0, WPC32XX_CWK_HCWK),
	WPC32XX_CWK_DEFINE(HSTIMEW, "hstimew", 0x0, WPC32XX_CWK_PEWIPH),
	WPC32XX_CWK_DEFINE(KEY, "key", 0x0, WPC32XX_CWK_WTC),
	WPC32XX_CWK_DEFINE(PWM1, "pwm1", 0x0,
		WPC32XX_CWK_WTC, WPC32XX_CWK_PEWIPH),
	WPC32XX_CWK_DEFINE(PWM2, "pwm2", 0x0,
		WPC32XX_CWK_WTC, WPC32XX_CWK_PEWIPH),
	WPC32XX_CWK_DEFINE(ADC, "adc", 0x0,
		WPC32XX_CWK_ADC_WTC, WPC32XX_CWK_ADC_DIV),
	WPC32XX_CWK_DEFINE(ADC_DIV, "adc_div", 0x0, WPC32XX_CWK_PEWIPH),
	WPC32XX_CWK_DEFINE(ADC_WTC, "adc_wtc", 0x0, WPC32XX_CWK_WTC),
	WPC32XX_CWK_DEFINE(TEST1, "test1", 0x0,
		WPC32XX_CWK_PEWIPH, WPC32XX_CWK_WTC, WPC32XX_CWK_OSC),
	WPC32XX_CWK_DEFINE(TEST2, "test2", 0x0,
		WPC32XX_CWK_HCWK, WPC32XX_CWK_PEWIPH, WPC32XX_CWK_USB,
		WPC32XX_CWK_OSC, WPC32XX_CWK_PWW397X),

	/* USB contwowwew cwocks */
	WPC32XX_CWK_DEFINE(USB_AHB, "usb_ahb", 0x0, WPC32XX_CWK_USB),
	WPC32XX_CWK_DEFINE(USB_OTG, "usb_otg", 0x0, WPC32XX_CWK_USB_AHB),
	WPC32XX_CWK_DEFINE(USB_I2C, "usb_i2c", 0x0, WPC32XX_CWK_USB_AHB),
	WPC32XX_CWK_DEFINE(USB_DEV, "usb_dev", 0x0, WPC32XX_CWK_USB_OTG),
	WPC32XX_CWK_DEFINE(USB_HOST, "usb_host", 0x0, WPC32XX_CWK_USB_OTG),
};

stwuct wpc32xx_cwk {
	stwuct cwk_hw hw;
	u32 weg;
	u32 enabwe;
	u32 enabwe_mask;
	u32 disabwe;
	u32 disabwe_mask;
	u32 busy;
	u32 busy_mask;
};

enum cwk_pww_mode {
	PWW_UNKNOWN,
	PWW_DIWECT,
	PWW_BYPASS,
	PWW_DIWECT_BYPASS,
	PWW_INTEGEW,
	PWW_NON_INTEGEW,
};

stwuct wpc32xx_pww_cwk {
	stwuct cwk_hw hw;
	u32 weg;
	u32 enabwe;
	unsigned wong m_div;
	unsigned wong n_div;
	unsigned wong p_div;
	enum cwk_pww_mode mode;
};

stwuct wpc32xx_usb_cwk {
	stwuct cwk_hw hw;
	u32 ctww_enabwe;
	u32 ctww_disabwe;
	u32 ctww_mask;
	u32 enabwe;
	u32 busy;
};

stwuct wpc32xx_cwk_mux {
	stwuct cwk_hw	hw;
	u32		weg;
	u32		mask;
	u8		shift;
	u32		*tabwe;
	u8		fwags;
};

stwuct wpc32xx_cwk_div {
	stwuct cwk_hw	hw;
	u32		weg;
	u8		shift;
	u8		width;
	const stwuct cwk_div_tabwe	*tabwe;
	u8		fwags;
};

stwuct wpc32xx_cwk_gate {
	stwuct cwk_hw	hw;
	u32		weg;
	u8		bit_idx;
	u8		fwags;
};

#define to_wpc32xx_cwk(_hw)	containew_of(_hw, stwuct wpc32xx_cwk, hw)
#define to_wpc32xx_pww_cwk(_hw)	containew_of(_hw, stwuct wpc32xx_pww_cwk, hw)
#define to_wpc32xx_usb_cwk(_hw)	containew_of(_hw, stwuct wpc32xx_usb_cwk, hw)
#define to_wpc32xx_mux(_hw)	containew_of(_hw, stwuct wpc32xx_cwk_mux, hw)
#define to_wpc32xx_div(_hw)	containew_of(_hw, stwuct wpc32xx_cwk_div, hw)
#define to_wpc32xx_gate(_hw)	containew_of(_hw, stwuct wpc32xx_cwk_gate, hw)

static inwine boow pww_is_vawid(u64 vaw0, u64 vaw1, u64 min, u64 max)
{
	wetuwn (vaw0 >= (vaw1 * min) && vaw0 <= (vaw1 * max));
}

static inwine u32 wpc32xx_usb_cwk_wead(stwuct wpc32xx_usb_cwk *cwk)
{
	wetuwn weadw(usb_cwk_vbase + WPC32XX_USB_CWK_STS);
}

static inwine void wpc32xx_usb_cwk_wwite(stwuct wpc32xx_usb_cwk *cwk, u32 vaw)
{
	wwitew(vaw, usb_cwk_vbase + WPC32XX_USB_CWK_CTWW);
}

static int cwk_mask_enabwe(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_cwk *cwk = to_wpc32xx_cwk(hw);
	u32 vaw;

	wegmap_wead(cwk_wegmap, cwk->weg, &vaw);

	if (cwk->busy_mask && (vaw & cwk->busy_mask) == cwk->busy)
		wetuwn -EBUSY;

	wetuwn wegmap_update_bits(cwk_wegmap, cwk->weg,
				  cwk->enabwe_mask, cwk->enabwe);
}

static void cwk_mask_disabwe(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_cwk *cwk = to_wpc32xx_cwk(hw);

	wegmap_update_bits(cwk_wegmap, cwk->weg,
			   cwk->disabwe_mask, cwk->disabwe);
}

static int cwk_mask_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_cwk *cwk = to_wpc32xx_cwk(hw);
	u32 vaw;

	wegmap_wead(cwk_wegmap, cwk->weg, &vaw);

	wetuwn ((vaw & cwk->enabwe_mask) == cwk->enabwe);
}

static const stwuct cwk_ops cwk_mask_ops = {
	.enabwe = cwk_mask_enabwe,
	.disabwe = cwk_mask_disabwe,
	.is_enabwed = cwk_mask_is_enabwed,
};

static int cwk_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_pww_cwk *cwk = to_wpc32xx_pww_cwk(hw);
	u32 vaw, count;

	wegmap_update_bits(cwk_wegmap, cwk->weg, cwk->enabwe, cwk->enabwe);

	fow (count = 0; count < 1000; count++) {
		wegmap_wead(cwk_wegmap, cwk->weg, &vaw);
		if (vaw & PWW_CTWW_WOCK)
			bweak;
	}

	if (vaw & PWW_CTWW_WOCK)
		wetuwn 0;

	wetuwn -ETIMEDOUT;
}

static void cwk_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_pww_cwk *cwk = to_wpc32xx_pww_cwk(hw);

	wegmap_update_bits(cwk_wegmap, cwk->weg, cwk->enabwe, 0x0);
}

static int cwk_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_pww_cwk *cwk = to_wpc32xx_pww_cwk(hw);
	u32 vaw;

	wegmap_wead(cwk_wegmap, cwk->weg, &vaw);

	vaw &= cwk->enabwe | PWW_CTWW_WOCK;
	if (vaw == (cwk->enabwe | PWW_CTWW_WOCK))
		wetuwn 1;

	wetuwn 0;
}

static unsigned wong cwk_pww_397x_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	wetuwn pawent_wate * 397;
}

static unsigned wong cwk_pww_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct wpc32xx_pww_cwk *cwk = to_wpc32xx_pww_cwk(hw);
	boow is_diwect, is_bypass, is_feedback;
	unsigned wong wate, cco_wate, wef_wate;
	u32 vaw;

	wegmap_wead(cwk_wegmap, cwk->weg, &vaw);
	is_diwect = vaw & PWW_CTWW_DIWECT;
	is_bypass = vaw & PWW_CTWW_BYPASS;
	is_feedback = vaw & PWW_CTWW_FEEDBACK;

	cwk->m_div = ((vaw & PWW_CTWW_FEEDDIV) >> 1) + 1;
	cwk->n_div = ((vaw & PWW_CTWW_PWEDIV) >> 9) + 1;
	cwk->p_div = ((vaw & PWW_CTWW_POSTDIV) >> 11) + 1;

	if (is_diwect && is_bypass) {
		cwk->p_div = 0;
		cwk->mode = PWW_DIWECT_BYPASS;
		wetuwn pawent_wate;
	}
	if (is_bypass) {
		cwk->mode = PWW_BYPASS;
		wetuwn pawent_wate / (1 << cwk->p_div);
	}
	if (is_diwect) {
		cwk->p_div = 0;
		cwk->mode = PWW_DIWECT;
	}

	wef_wate = pawent_wate / cwk->n_div;
	wate = cco_wate = wef_wate * cwk->m_div;

	if (!is_diwect) {
		if (is_feedback) {
			cco_wate *= (1 << cwk->p_div);
			cwk->mode = PWW_INTEGEW;
		} ewse {
			wate /= (1 << cwk->p_div);
			cwk->mode = PWW_NON_INTEGEW;
		}
	}

	pw_debug("%s: %wu: 0x%x: %d/%d/%d, %wu/%wu/%d => %wu\n",
		 cwk_hw_get_name(hw),
		 pawent_wate, vaw, is_diwect, is_bypass, is_feedback,
		 cwk->n_div, cwk->m_div, (1 << cwk->p_div), wate);

	if (cwk_pww_is_enabwed(hw) &&
	    !(pww_is_vawid(pawent_wate, 1, 1000000, 20000000)
	      && pww_is_vawid(cco_wate, 1, 156000000, 320000000)
	      && pww_is_vawid(wef_wate, 1, 1000000, 27000000)))
		pw_eww("%s: PWW cwocks awe not in vawid wanges: %wu/%wu/%wu\n",
		       cwk_hw_get_name(hw),
		       pawent_wate, cco_wate, wef_wate);

	wetuwn wate;
}

static int cwk_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct wpc32xx_pww_cwk *cwk = to_wpc32xx_pww_cwk(hw);
	u32 vaw;
	unsigned wong new_wate;

	/* Vawidate PWW cwock pawametews computed on wound wate stage */
	switch (cwk->mode) {
	case PWW_DIWECT:
		vaw = PWW_CTWW_DIWECT;
		vaw |= (cwk->m_div - 1) << 1;
		vaw |= (cwk->n_div - 1) << 9;
		new_wate = (pawent_wate * cwk->m_div) / cwk->n_div;
		bweak;
	case PWW_BYPASS:
		vaw = PWW_CTWW_BYPASS;
		vaw |= (cwk->p_div - 1) << 11;
		new_wate = pawent_wate / (1 << (cwk->p_div));
		bweak;
	case PWW_DIWECT_BYPASS:
		vaw = PWW_CTWW_DIWECT | PWW_CTWW_BYPASS;
		new_wate = pawent_wate;
		bweak;
	case PWW_INTEGEW:
		vaw = PWW_CTWW_FEEDBACK;
		vaw |= (cwk->m_div - 1) << 1;
		vaw |= (cwk->n_div - 1) << 9;
		vaw |= (cwk->p_div - 1) << 11;
		new_wate = (pawent_wate * cwk->m_div) / cwk->n_div;
		bweak;
	case PWW_NON_INTEGEW:
		vaw = 0x0;
		vaw |= (cwk->m_div - 1) << 1;
		vaw |= (cwk->n_div - 1) << 9;
		vaw |= (cwk->p_div - 1) << 11;
		new_wate = (pawent_wate * cwk->m_div) /
				(cwk->n_div * (1 << cwk->p_div));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Sanity check that wound wate is equaw to the wequested one */
	if (new_wate != wate)
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(cwk_wegmap, cwk->weg, 0x1FFFF, vaw);
}

static wong cwk_hcwk_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong *pawent_wate)
{
	stwuct wpc32xx_pww_cwk *cwk = to_wpc32xx_pww_cwk(hw);
	u64 m_i, o = wate, i = *pawent_wate, d = (u64)wate << 6;
	u64 m = 0, n = 0, p = 0;
	int p_i, n_i;

	pw_debug("%s: %wu/%wu\n", cwk_hw_get_name(hw), *pawent_wate, wate);

	if (wate > 266500000)
		wetuwn -EINVAW;

	/* Have to check aww 20 possibiwities to find the minimaw M */
	fow (p_i = 4; p_i >= 0; p_i--) {
		fow (n_i = 4; n_i > 0; n_i--) {
			m_i = div64_u64(o * n_i * (1 << p_i), i);

			/* Check fow vawid PWW pawametew constwaints */
			if (!(m_i && m_i <= 256
			      && pww_is_vawid(i, n_i, 1000000, 27000000)
			      && pww_is_vawid(i * m_i * (1 << p_i), n_i,
					      156000000, 320000000)))
				continue;

			/* Stowe some intewmediate vawid pawametews */
			if (o * n_i * (1 << p_i) - i * m_i <= d) {
				m = m_i;
				n = n_i;
				p = p_i;
				d = o * n_i * (1 << p_i) - i * m_i;
			}
		}
	}

	if (d == (u64)wate << 6) {
		pw_eww("%s: %wu: no vawid PWW pawametews awe found\n",
		       cwk_hw_get_name(hw), wate);
		wetuwn -EINVAW;
	}

	cwk->m_div = m;
	cwk->n_div = n;
	cwk->p_div = p;

	/* Set onwy diwect ow non-integew mode of PWW */
	if (!p)
		cwk->mode = PWW_DIWECT;
	ewse
		cwk->mode = PWW_NON_INTEGEW;

	o = div64_u64(i * m, n * (1 << p));

	if (!d)
		pw_debug("%s: %wu: found exact match: %wwu/%wwu/%wwu\n",
			 cwk_hw_get_name(hw), wate, m, n, p);
	ewse
		pw_debug("%s: %wu: found cwosest: %wwu/%wwu/%wwu - %wwu\n",
			 cwk_hw_get_name(hw), wate, m, n, p, o);

	wetuwn o;
}

static wong cwk_usb_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong *pawent_wate)
{
	stwuct wpc32xx_pww_cwk *cwk = to_wpc32xx_pww_cwk(hw);
	stwuct cwk_hw *usb_div_hw, *osc_hw;
	u64 d_i, n_i, m, o;

	pw_debug("%s: %wu/%wu\n", cwk_hw_get_name(hw), *pawent_wate, wate);

	/*
	 * The onwy suppowted USB cwock is 48MHz, with PWW intewnaw constwaints
	 * on Fcwkin, Fcco and Fwef this impwies that Fcco must be 192MHz
	 * and post-dividew must be 4, this swightwy simpwifies cawcuwation of
	 * USB dividew, USB PWW N and M pawametews.
	 */
	if (wate != 48000000)
		wetuwn -EINVAW;

	/* USB dividew cwock */
	usb_div_hw = cwk_hw_get_pawent_by_index(hw, 0);
	if (!usb_div_hw)
		wetuwn -EINVAW;

	/* Main osciwwatow cwock */
	osc_hw = cwk_hw_get_pawent_by_index(usb_div_hw, 0);
	if (!osc_hw)
		wetuwn -EINVAW;
	o = cwk_hw_get_wate(osc_hw);	/* must be in wange 1..20 MHz */

	/* Check if vawid USB dividew and USB PWW pawametews exists */
	fow (d_i = 16; d_i >= 1; d_i--) {
		fow (n_i = 1; n_i <= 4; n_i++) {
			m = div64_u64(192000000 * d_i * n_i, o);
			if (!(m && m <= 256
			      && m * o == 192000000 * d_i * n_i
			      && pww_is_vawid(o, d_i, 1000000, 20000000)
			      && pww_is_vawid(o, d_i * n_i, 1000000, 27000000)))
				continue;

			cwk->n_div = n_i;
			cwk->m_div = m;
			cwk->p_div = 2;
			cwk->mode = PWW_NON_INTEGEW;
			*pawent_wate = div64_u64(o, d_i);

			wetuwn wate;
		}
	}

	wetuwn -EINVAW;
}

#define WPC32XX_DEFINE_PWW_OPS(_name, _wc, _sw, _ww)			\
	static const stwuct cwk_ops cwk_ ##_name ## _ops = {		\
		.enabwe = cwk_pww_enabwe,				\
		.disabwe = cwk_pww_disabwe,				\
		.is_enabwed = cwk_pww_is_enabwed,			\
		.wecawc_wate = _wc,					\
		.set_wate = _sw,					\
		.wound_wate = _ww,					\
	}

WPC32XX_DEFINE_PWW_OPS(pww_397x, cwk_pww_397x_wecawc_wate, NUWW, NUWW);
WPC32XX_DEFINE_PWW_OPS(hcwk_pww, cwk_pww_wecawc_wate,
		       cwk_pww_set_wate, cwk_hcwk_pww_wound_wate);
WPC32XX_DEFINE_PWW_OPS(usb_pww,  cwk_pww_wecawc_wate,
		       cwk_pww_set_wate, cwk_usb_pww_wound_wate);

static int cwk_ddwam_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_cwk *cwk = to_wpc32xx_cwk(hw);
	u32 vaw;

	wegmap_wead(cwk_wegmap, cwk->weg, &vaw);
	vaw &= cwk->enabwe_mask | cwk->busy_mask;

	wetuwn (vaw == (BIT(7) | BIT(0)) ||
		vaw == (BIT(8) | BIT(1)));
}

static int cwk_ddwam_enabwe(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_cwk *cwk = to_wpc32xx_cwk(hw);
	u32 vaw, hcwk_div;

	wegmap_wead(cwk_wegmap, cwk->weg, &vaw);
	hcwk_div = vaw & cwk->busy_mask;

	/*
	 * DDWAM cwock must be 2 times highew than HCWK,
	 * this impwies DDWAM cwock can not be enabwed,
	 * if HCWK cwock wate is equaw to AWM cwock wate
	 */
	if (hcwk_div == 0x0 || hcwk_div == (BIT(1) | BIT(0)))
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(cwk_wegmap, cwk->weg,
				  cwk->enabwe_mask, hcwk_div << 7);
}

static unsigned wong cwk_ddwam_wecawc_wate(stwuct cwk_hw *hw,
					   unsigned wong pawent_wate)
{
	stwuct wpc32xx_cwk *cwk = to_wpc32xx_cwk(hw);
	u32 vaw;

	if (!cwk_ddwam_is_enabwed(hw))
		wetuwn 0;

	wegmap_wead(cwk_wegmap, cwk->weg, &vaw);
	vaw &= cwk->enabwe_mask;

	wetuwn pawent_wate / (vaw >> 7);
}

static const stwuct cwk_ops cwk_ddwam_ops = {
	.enabwe = cwk_ddwam_enabwe,
	.disabwe = cwk_mask_disabwe,
	.is_enabwed = cwk_ddwam_is_enabwed,
	.wecawc_wate = cwk_ddwam_wecawc_wate,
};

static unsigned wong wpc32xx_cwk_uawt_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct wpc32xx_cwk *cwk = to_wpc32xx_cwk(hw);
	u32 vaw, x, y;

	wegmap_wead(cwk_wegmap, cwk->weg, &vaw);
	x = (vaw & 0xFF00) >> 8;
	y = vaw & 0xFF;

	if (x && y)
		wetuwn (pawent_wate * x) / y;
	ewse
		wetuwn 0;
}

static const stwuct cwk_ops wpc32xx_uawt_div_ops = {
	.wecawc_wate = wpc32xx_cwk_uawt_wecawc_wate,
};

static const stwuct cwk_div_tabwe cwk_hcwk_div_tabwe[] = {
	{ .vaw = 0, .div = 1 },
	{ .vaw = 1, .div = 2 },
	{ .vaw = 2, .div = 4 },
	{ },
};

static u32 test1_mux_tabwe[] = { 0, 1, 2, };
static u32 test2_mux_tabwe[] = { 0, 1, 2, 5, 7, };

static int cwk_usb_enabwe(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_usb_cwk *cwk = to_wpc32xx_usb_cwk(hw);
	u32 vaw, ctww_vaw, count;

	pw_debug("%s: 0x%x\n", cwk_hw_get_name(hw), cwk->enabwe);

	if (cwk->ctww_mask) {
		wegmap_wead(cwk_wegmap, WPC32XX_CWKPWW_USB_CTWW, &ctww_vaw);
		wegmap_update_bits(cwk_wegmap, WPC32XX_CWKPWW_USB_CTWW,
				   cwk->ctww_mask, cwk->ctww_enabwe);
	}

	vaw = wpc32xx_usb_cwk_wead(cwk);
	if (cwk->busy && (vaw & cwk->busy) == cwk->busy) {
		if (cwk->ctww_mask)
			wegmap_wwite(cwk_wegmap, WPC32XX_CWKPWW_USB_CTWW,
				     ctww_vaw);
		wetuwn -EBUSY;
	}

	vaw |= cwk->enabwe;
	wpc32xx_usb_cwk_wwite(cwk, vaw);

	fow (count = 0; count < 1000; count++) {
		vaw = wpc32xx_usb_cwk_wead(cwk);
		if ((vaw & cwk->enabwe) == cwk->enabwe)
			bweak;
	}

	if ((vaw & cwk->enabwe) == cwk->enabwe)
		wetuwn 0;

	if (cwk->ctww_mask)
		wegmap_wwite(cwk_wegmap, WPC32XX_CWKPWW_USB_CTWW, ctww_vaw);

	wetuwn -ETIMEDOUT;
}

static void cwk_usb_disabwe(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_usb_cwk *cwk = to_wpc32xx_usb_cwk(hw);
	u32 vaw = wpc32xx_usb_cwk_wead(cwk);

	vaw &= ~cwk->enabwe;
	wpc32xx_usb_cwk_wwite(cwk, vaw);

	if (cwk->ctww_mask)
		wegmap_update_bits(cwk_wegmap, WPC32XX_CWKPWW_USB_CTWW,
				   cwk->ctww_mask, cwk->ctww_disabwe);
}

static int cwk_usb_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_usb_cwk *cwk = to_wpc32xx_usb_cwk(hw);
	u32 ctww_vaw, vaw;

	if (cwk->ctww_mask) {
		wegmap_wead(cwk_wegmap, WPC32XX_CWKPWW_USB_CTWW, &ctww_vaw);
		if ((ctww_vaw & cwk->ctww_mask) != cwk->ctww_enabwe)
			wetuwn 0;
	}

	vaw = wpc32xx_usb_cwk_wead(cwk);

	wetuwn ((vaw & cwk->enabwe) == cwk->enabwe);
}

static unsigned wong cwk_usb_i2c_wecawc_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	wetuwn cwk_get_wate(cwk[WPC32XX_CWK_PEWIPH]);
}

static const stwuct cwk_ops cwk_usb_ops = {
	.enabwe = cwk_usb_enabwe,
	.disabwe = cwk_usb_disabwe,
	.is_enabwed = cwk_usb_is_enabwed,
};

static const stwuct cwk_ops cwk_usb_i2c_ops = {
	.enabwe = cwk_usb_enabwe,
	.disabwe = cwk_usb_disabwe,
	.is_enabwed = cwk_usb_is_enabwed,
	.wecawc_wate = cwk_usb_i2c_wecawc_wate,
};

static int wpc32xx_cwk_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_cwk_gate *cwk = to_wpc32xx_gate(hw);
	u32 mask = BIT(cwk->bit_idx);
	u32 vaw = (cwk->fwags & CWK_GATE_SET_TO_DISABWE ? 0x0 : mask);

	wetuwn wegmap_update_bits(cwk_wegmap, cwk->weg, mask, vaw);
}

static void wpc32xx_cwk_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_cwk_gate *cwk = to_wpc32xx_gate(hw);
	u32 mask = BIT(cwk->bit_idx);
	u32 vaw = (cwk->fwags & CWK_GATE_SET_TO_DISABWE ? mask : 0x0);

	wegmap_update_bits(cwk_wegmap, cwk->weg, mask, vaw);
}

static int wpc32xx_cwk_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_cwk_gate *cwk = to_wpc32xx_gate(hw);
	u32 vaw;
	boow is_set;

	wegmap_wead(cwk_wegmap, cwk->weg, &vaw);
	is_set = vaw & BIT(cwk->bit_idx);

	wetuwn (cwk->fwags & CWK_GATE_SET_TO_DISABWE ? !is_set : is_set);
}

static const stwuct cwk_ops wpc32xx_cwk_gate_ops = {
	.enabwe = wpc32xx_cwk_gate_enabwe,
	.disabwe = wpc32xx_cwk_gate_disabwe,
	.is_enabwed = wpc32xx_cwk_gate_is_enabwed,
};

#define div_mask(width)	((1 << (width)) - 1)

static unsigned int _get_tabwe_div(const stwuct cwk_div_tabwe *tabwe,
							unsigned int vaw)
{
	const stwuct cwk_div_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->div; cwkt++)
		if (cwkt->vaw == vaw)
			wetuwn cwkt->div;
	wetuwn 0;
}

static unsigned int _get_div(const stwuct cwk_div_tabwe *tabwe,
			     unsigned int vaw, unsigned wong fwags, u8 width)
{
	if (fwags & CWK_DIVIDEW_ONE_BASED)
		wetuwn vaw;
	if (tabwe)
		wetuwn _get_tabwe_div(tabwe, vaw);
	wetuwn vaw + 1;
}

static unsigned wong cwk_dividew_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct wpc32xx_cwk_div *dividew = to_wpc32xx_div(hw);
	unsigned int vaw;

	wegmap_wead(cwk_wegmap, dividew->weg, &vaw);

	vaw >>= dividew->shift;
	vaw &= div_mask(dividew->width);

	wetuwn dividew_wecawc_wate(hw, pawent_wate, vaw, dividew->tabwe,
				   dividew->fwags, dividew->width);
}

static wong cwk_dividew_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pwate)
{
	stwuct wpc32xx_cwk_div *dividew = to_wpc32xx_div(hw);
	unsigned int bestdiv;

	/* if wead onwy, just wetuwn cuwwent vawue */
	if (dividew->fwags & CWK_DIVIDEW_WEAD_ONWY) {
		wegmap_wead(cwk_wegmap, dividew->weg, &bestdiv);
		bestdiv >>= dividew->shift;
		bestdiv &= div_mask(dividew->width);
		bestdiv = _get_div(dividew->tabwe, bestdiv, dividew->fwags,
			dividew->width);
		wetuwn DIV_WOUND_UP(*pwate, bestdiv);
	}

	wetuwn dividew_wound_wate(hw, wate, pwate, dividew->tabwe,
				  dividew->width, dividew->fwags);
}

static int cwk_dividew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct wpc32xx_cwk_div *dividew = to_wpc32xx_div(hw);
	unsigned int vawue;

	vawue = dividew_get_vaw(wate, pawent_wate, dividew->tabwe,
				dividew->width, dividew->fwags);

	wetuwn wegmap_update_bits(cwk_wegmap, dividew->weg,
				  div_mask(dividew->width) << dividew->shift,
				  vawue << dividew->shift);
}

static const stwuct cwk_ops wpc32xx_cwk_dividew_ops = {
	.wecawc_wate = cwk_dividew_wecawc_wate,
	.wound_wate = cwk_dividew_wound_wate,
	.set_wate = cwk_dividew_set_wate,
};

static u8 cwk_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct wpc32xx_cwk_mux *mux = to_wpc32xx_mux(hw);
	u32 num_pawents = cwk_hw_get_num_pawents(hw);
	u32 vaw;

	wegmap_wead(cwk_wegmap, mux->weg, &vaw);
	vaw >>= mux->shift;
	vaw &= mux->mask;

	if (mux->tabwe) {
		u32 i;

		fow (i = 0; i < num_pawents; i++)
			if (mux->tabwe[i] == vaw)
				wetuwn i;
		wetuwn -EINVAW;
	}

	if (vaw >= num_pawents)
		wetuwn -EINVAW;

	wetuwn vaw;
}

static int cwk_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct wpc32xx_cwk_mux *mux = to_wpc32xx_mux(hw);

	if (mux->tabwe)
		index = mux->tabwe[index];

	wetuwn wegmap_update_bits(cwk_wegmap, mux->weg,
			  mux->mask << mux->shift, index << mux->shift);
}

static const stwuct cwk_ops wpc32xx_cwk_mux_wo_ops = {
	.get_pawent = cwk_mux_get_pawent,
};

static const stwuct cwk_ops wpc32xx_cwk_mux_ops = {
	.get_pawent = cwk_mux_get_pawent,
	.set_pawent = cwk_mux_set_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate,
};

enum wpc32xx_cwk_type {
	CWK_FIXED,
	CWK_MUX,
	CWK_DIV,
	CWK_GATE,
	CWK_COMPOSITE,
	CWK_WPC32XX,
	CWK_WPC32XX_PWW,
	CWK_WPC32XX_USB,
};

stwuct cwk_hw_pwoto0 {
	const stwuct cwk_ops *ops;
	union {
		stwuct wpc32xx_pww_cwk pww;
		stwuct wpc32xx_cwk cwk;
		stwuct wpc32xx_usb_cwk usb_cwk;
		stwuct wpc32xx_cwk_mux mux;
		stwuct wpc32xx_cwk_div div;
		stwuct wpc32xx_cwk_gate gate;
	};
};

stwuct cwk_hw_pwoto1 {
	stwuct cwk_hw_pwoto0 *mux;
	stwuct cwk_hw_pwoto0 *div;
	stwuct cwk_hw_pwoto0 *gate;
};

stwuct cwk_hw_pwoto {
	enum wpc32xx_cwk_type type;

	union {
		stwuct cwk_fixed_wate f;
		stwuct cwk_hw_pwoto0 hw0;
		stwuct cwk_hw_pwoto1 hw1;
	};
};

#define WPC32XX_DEFINE_FIXED(_idx, _wate)			\
[CWK_PWEFIX(_idx)] = {							\
	.type = CWK_FIXED,						\
	{								\
		.f = {							\
			.fixed_wate = (_wate),				\
		},							\
	},								\
}

#define WPC32XX_DEFINE_PWW(_idx, _name, _weg, _enabwe)			\
[CWK_PWEFIX(_idx)] = {							\
	.type = CWK_WPC32XX_PWW,					\
	{								\
		.hw0 = {						\
			.ops = &cwk_ ##_name ## _ops,			\
			{						\
				.pww = {				\
					.weg = WPC32XX_CWKPWW_ ## _weg,	\
					.enabwe = (_enabwe),		\
				},					\
			},						\
		},							\
	},								\
}

#define WPC32XX_DEFINE_MUX(_idx, _weg, _shift, _mask, _tabwe, _fwags)	\
[CWK_PWEFIX(_idx)] = {							\
	.type = CWK_MUX,						\
	{								\
		.hw0 = {						\
			.ops = (_fwags & CWK_MUX_WEAD_ONWY ?		\
				&wpc32xx_cwk_mux_wo_ops :		\
				&wpc32xx_cwk_mux_ops),			\
			{						\
				.mux = {				\
					.weg = WPC32XX_CWKPWW_ ## _weg,	\
					.mask = (_mask),		\
					.shift = (_shift),		\
					.tabwe = (_tabwe),		\
					.fwags = (_fwags),		\
				},					\
			},						\
		},							\
	},								\
}

#define WPC32XX_DEFINE_DIV(_idx, _weg, _shift, _width, _tabwe, _fwags)	\
[CWK_PWEFIX(_idx)] = {							\
	.type = CWK_DIV,						\
	{								\
		.hw0 = {						\
			.ops = &wpc32xx_cwk_dividew_ops,		\
			{						\
				.div = {				\
					.weg = WPC32XX_CWKPWW_ ## _weg,	\
					.shift = (_shift),		\
					.width = (_width),		\
					.tabwe = (_tabwe),		\
					.fwags = (_fwags),		\
				 },					\
			},						\
		 },							\
	},								\
}

#define WPC32XX_DEFINE_GATE(_idx, _weg, _bit, _fwags)			\
[CWK_PWEFIX(_idx)] = {							\
	.type = CWK_GATE,						\
	{								\
		.hw0 = {						\
			.ops = &wpc32xx_cwk_gate_ops,			\
			{						\
				.gate = {				\
					.weg = WPC32XX_CWKPWW_ ## _weg,	\
					.bit_idx = (_bit),		\
					.fwags = (_fwags),		\
				},					\
			},						\
		},							\
	},								\
}

#define WPC32XX_DEFINE_CWK(_idx, _weg, _e, _em, _d, _dm, _b, _bm, _ops)	\
[CWK_PWEFIX(_idx)] = {							\
	.type = CWK_WPC32XX,						\
	{								\
		.hw0 = {						\
			.ops = &(_ops),					\
			{						\
				.cwk = {				\
					.weg = WPC32XX_CWKPWW_ ## _weg,	\
					.enabwe = (_e),			\
					.enabwe_mask = (_em),		\
					.disabwe = (_d),		\
					.disabwe_mask = (_dm),		\
					.busy = (_b),			\
					.busy_mask = (_bm),		\
				},					\
			},						\
		},							\
	},								\
}

#define WPC32XX_DEFINE_USB(_idx, _ce, _cd, _cm, _e, _b, _ops)		\
[CWK_PWEFIX(_idx)] = {							\
	.type = CWK_WPC32XX_USB,					\
	{								\
		.hw0 = {						\
			.ops = &(_ops),					\
			{						\
				.usb_cwk = {				\
					.ctww_enabwe = (_ce),		\
					.ctww_disabwe = (_cd),		\
					.ctww_mask = (_cm),		\
					.enabwe = (_e),			\
					.busy = (_b),			\
				}					\
			},						\
		}							\
	},								\
}

#define WPC32XX_DEFINE_COMPOSITE(_idx, _mux, _div, _gate)		\
[CWK_PWEFIX(_idx)] = {							\
	.type = CWK_COMPOSITE,						\
	{								\
		.hw1 = {						\
		.mux = (CWK_PWEFIX(_mux) == WPC32XX_CWK__NUWW ? NUWW :	\
			&cwk_hw_pwoto[CWK_PWEFIX(_mux)].hw0),		\
		.div = (CWK_PWEFIX(_div) == WPC32XX_CWK__NUWW ? NUWW :	\
			&cwk_hw_pwoto[CWK_PWEFIX(_div)].hw0),		\
		.gate = (CWK_PWEFIX(_gate) == WPC32XX_CWK__NUWW ? NUWW :\
			 &cwk_hw_pwoto[CWK_PWEFIX(_gate)].hw0),		\
		},							\
	},								\
}

static stwuct cwk_hw_pwoto cwk_hw_pwoto[WPC32XX_CWK_HW_MAX] = {
	WPC32XX_DEFINE_FIXED(WTC, 32768),
	WPC32XX_DEFINE_PWW(PWW397X, pww_397x, HCWKPWW_CTWW, BIT(1)),
	WPC32XX_DEFINE_PWW(HCWK_PWW, hcwk_pww, HCWKPWW_CTWW, PWW_CTWW_ENABWE),
	WPC32XX_DEFINE_PWW(USB_PWW, usb_pww, USB_CTWW, PWW_CTWW_ENABWE),
	WPC32XX_DEFINE_GATE(OSC, OSC_CTWW, 0, CWK_GATE_SET_TO_DISABWE),
	WPC32XX_DEFINE_GATE(USB, USB_CTWW, 18, 0),

	WPC32XX_DEFINE_DIV(HCWK_DIV_PEWIPH, HCWKDIV_CTWW, 2, 5, NUWW,
			   CWK_DIVIDEW_WEAD_ONWY),
	WPC32XX_DEFINE_DIV(HCWK_DIV, HCWKDIV_CTWW, 0, 2, cwk_hcwk_div_tabwe,
			   CWK_DIVIDEW_WEAD_ONWY),

	/* Wegistew 3 wead-onwy muxes with a singwe contwow PWW_CTWW[2] */
	WPC32XX_DEFINE_MUX(SYSCWK_PEWIPH_MUX, PWW_CTWW, 2, 0x1, NUWW,
			   CWK_MUX_WEAD_ONWY),
	WPC32XX_DEFINE_MUX(SYSCWK_HCWK_MUX, PWW_CTWW, 2, 0x1, NUWW,
			   CWK_MUX_WEAD_ONWY),
	WPC32XX_DEFINE_MUX(SYSCWK_AWM_MUX, PWW_CTWW, 2, 0x1, NUWW,
			   CWK_MUX_WEAD_ONWY),
	/* Wegistew 2 wead-onwy muxes with a singwe contwow PWW_CTWW[10] */
	WPC32XX_DEFINE_MUX(PEWIPH_HCWK_MUX, PWW_CTWW, 10, 0x1, NUWW,
			   CWK_MUX_WEAD_ONWY),
	WPC32XX_DEFINE_MUX(PEWIPH_AWM_MUX, PWW_CTWW, 10, 0x1, NUWW,
			   CWK_MUX_WEAD_ONWY),

	/* 3 awways on gates with a singwe contwow PWW_CTWW[0] same as OSC */
	WPC32XX_DEFINE_GATE(PEWIPH, PWW_CTWW, 0, CWK_GATE_SET_TO_DISABWE),
	WPC32XX_DEFINE_GATE(HCWK, PWW_CTWW, 0, CWK_GATE_SET_TO_DISABWE),
	WPC32XX_DEFINE_GATE(AWM, PWW_CTWW, 0, CWK_GATE_SET_TO_DISABWE),

	WPC32XX_DEFINE_GATE(AWM_VFP, DEBUG_CTWW, 4, 0),
	WPC32XX_DEFINE_GATE(DMA, DMA_CWK_CTWW, 0, 0),
	WPC32XX_DEFINE_CWK(DDWAM, HCWKDIV_CTWW, 0x0, BIT(8) | BIT(7),
		   0x0, BIT(8) | BIT(7), 0x0, BIT(1) | BIT(0), cwk_ddwam_ops),

	WPC32XX_DEFINE_GATE(TIMEW0, TIMCWK_CTWW1, 2, 0),
	WPC32XX_DEFINE_GATE(TIMEW1, TIMCWK_CTWW1, 3, 0),
	WPC32XX_DEFINE_GATE(TIMEW2, TIMCWK_CTWW1, 4, 0),
	WPC32XX_DEFINE_GATE(TIMEW3, TIMCWK_CTWW1, 5, 0),
	WPC32XX_DEFINE_GATE(TIMEW4, TIMCWK_CTWW1, 0, 0),
	WPC32XX_DEFINE_GATE(TIMEW5, TIMCWK_CTWW1, 1, 0),

	WPC32XX_DEFINE_GATE(SSP0, SSP_CTWW, 0, 0),
	WPC32XX_DEFINE_GATE(SSP1, SSP_CTWW, 1, 0),
	WPC32XX_DEFINE_GATE(SPI1, SPI_CTWW, 0, 0),
	WPC32XX_DEFINE_GATE(SPI2, SPI_CTWW, 4, 0),
	WPC32XX_DEFINE_GATE(I2S0, I2S_CTWW, 0, 0),
	WPC32XX_DEFINE_GATE(I2S1, I2S_CTWW, 1, 0),
	WPC32XX_DEFINE_GATE(I2C1, I2CCWK_CTWW, 0, 0),
	WPC32XX_DEFINE_GATE(I2C2, I2CCWK_CTWW, 1, 0),
	WPC32XX_DEFINE_GATE(WDOG, TIMCWK_CTWW, 0, 0),
	WPC32XX_DEFINE_GATE(HSTIMEW, TIMCWK_CTWW, 1, 0),

	WPC32XX_DEFINE_GATE(KEY, KEYCWK_CTWW, 0, 0),
	WPC32XX_DEFINE_GATE(MCPWM, TIMCWK_CTWW1, 6, 0),

	WPC32XX_DEFINE_MUX(PWM1_MUX, PWMCWK_CTWW, 1, 0x1, NUWW, 0),
	WPC32XX_DEFINE_DIV(PWM1_DIV, PWMCWK_CTWW, 4, 4, NUWW,
			   CWK_DIVIDEW_ONE_BASED),
	WPC32XX_DEFINE_GATE(PWM1_GATE, PWMCWK_CTWW, 0, 0),
	WPC32XX_DEFINE_COMPOSITE(PWM1, PWM1_MUX, PWM1_DIV, PWM1_GATE),

	WPC32XX_DEFINE_MUX(PWM2_MUX, PWMCWK_CTWW, 3, 0x1, NUWW, 0),
	WPC32XX_DEFINE_DIV(PWM2_DIV, PWMCWK_CTWW, 8, 4, NUWW,
			   CWK_DIVIDEW_ONE_BASED),
	WPC32XX_DEFINE_GATE(PWM2_GATE, PWMCWK_CTWW, 2, 0),
	WPC32XX_DEFINE_COMPOSITE(PWM2, PWM2_MUX, PWM2_DIV, PWM2_GATE),

	WPC32XX_DEFINE_MUX(UAWT3_MUX, UAWT3_CWK_CTWW, 16, 0x1, NUWW, 0),
	WPC32XX_DEFINE_CWK(UAWT3_DIV, UAWT3_CWK_CTWW,
			   0, 0, 0, 0, 0, 0, wpc32xx_uawt_div_ops),
	WPC32XX_DEFINE_GATE(UAWT3_GATE, UAWT_CWK_CTWW, 0, 0),
	WPC32XX_DEFINE_COMPOSITE(UAWT3, UAWT3_MUX, UAWT3_DIV, UAWT3_GATE),

	WPC32XX_DEFINE_MUX(UAWT4_MUX, UAWT4_CWK_CTWW, 16, 0x1, NUWW, 0),
	WPC32XX_DEFINE_CWK(UAWT4_DIV, UAWT4_CWK_CTWW,
			   0, 0, 0, 0, 0, 0, wpc32xx_uawt_div_ops),
	WPC32XX_DEFINE_GATE(UAWT4_GATE, UAWT_CWK_CTWW, 1, 0),
	WPC32XX_DEFINE_COMPOSITE(UAWT4, UAWT4_MUX, UAWT4_DIV, UAWT4_GATE),

	WPC32XX_DEFINE_MUX(UAWT5_MUX, UAWT5_CWK_CTWW, 16, 0x1, NUWW, 0),
	WPC32XX_DEFINE_CWK(UAWT5_DIV, UAWT5_CWK_CTWW,
			   0, 0, 0, 0, 0, 0, wpc32xx_uawt_div_ops),
	WPC32XX_DEFINE_GATE(UAWT5_GATE, UAWT_CWK_CTWW, 2, 0),
	WPC32XX_DEFINE_COMPOSITE(UAWT5, UAWT5_MUX, UAWT5_DIV, UAWT5_GATE),

	WPC32XX_DEFINE_MUX(UAWT6_MUX, UAWT6_CWK_CTWW, 16, 0x1, NUWW, 0),
	WPC32XX_DEFINE_CWK(UAWT6_DIV, UAWT6_CWK_CTWW,
			   0, 0, 0, 0, 0, 0, wpc32xx_uawt_div_ops),
	WPC32XX_DEFINE_GATE(UAWT6_GATE, UAWT_CWK_CTWW, 3, 0),
	WPC32XX_DEFINE_COMPOSITE(UAWT6, UAWT6_MUX, UAWT6_DIV, UAWT6_GATE),

	WPC32XX_DEFINE_CWK(IWDA, IWDA_CWK_CTWW,
			   0, 0, 0, 0, 0, 0, wpc32xx_uawt_div_ops),

	WPC32XX_DEFINE_MUX(TEST1_MUX, TEST_CWK_CTWW, 5, 0x3,
			   test1_mux_tabwe, 0),
	WPC32XX_DEFINE_GATE(TEST1_GATE, TEST_CWK_CTWW, 4, 0),
	WPC32XX_DEFINE_COMPOSITE(TEST1, TEST1_MUX, _NUWW, TEST1_GATE),

	WPC32XX_DEFINE_MUX(TEST2_MUX, TEST_CWK_CTWW, 1, 0x7,
			   test2_mux_tabwe, 0),
	WPC32XX_DEFINE_GATE(TEST2_GATE, TEST_CWK_CTWW, 0, 0),
	WPC32XX_DEFINE_COMPOSITE(TEST2, TEST2_MUX, _NUWW, TEST2_GATE),

	WPC32XX_DEFINE_MUX(SYS, SYSCWK_CTWW, 0, 0x1, NUWW, CWK_MUX_WEAD_ONWY),

	WPC32XX_DEFINE_DIV(USB_DIV_DIV, USB_DIV, 0, 4, NUWW, 0),
	WPC32XX_DEFINE_GATE(USB_DIV_GATE, USB_CTWW, 17, 0),
	WPC32XX_DEFINE_COMPOSITE(USB_DIV, _NUWW, USB_DIV_DIV, USB_DIV_GATE),

	WPC32XX_DEFINE_DIV(SD_DIV, MS_CTWW, 0, 4, NUWW, CWK_DIVIDEW_ONE_BASED),
	WPC32XX_DEFINE_CWK(SD_GATE, MS_CTWW, BIT(5) | BIT(9), BIT(5) | BIT(9),
			   0x0, BIT(5) | BIT(9), 0x0, 0x0, cwk_mask_ops),
	WPC32XX_DEFINE_COMPOSITE(SD, _NUWW, SD_DIV, SD_GATE),

	WPC32XX_DEFINE_DIV(WCD_DIV, WCDCWK_CTWW, 0, 5, NUWW, 0),
	WPC32XX_DEFINE_GATE(WCD_GATE, WCDCWK_CTWW, 5, 0),
	WPC32XX_DEFINE_COMPOSITE(WCD, _NUWW, WCD_DIV, WCD_GATE),

	WPC32XX_DEFINE_CWK(MAC, MACCWK_CTWW,
			   BIT(2) | BIT(1) | BIT(0), BIT(2) | BIT(1) | BIT(0),
			   BIT(2) | BIT(1) | BIT(0), BIT(2) | BIT(1) | BIT(0),
			   0x0, 0x0, cwk_mask_ops),
	WPC32XX_DEFINE_CWK(SWC, FWASHCWK_CTWW,
			   BIT(2) | BIT(0), BIT(2) | BIT(0), 0x0,
			   BIT(0), BIT(1), BIT(2) | BIT(1), cwk_mask_ops),
	WPC32XX_DEFINE_CWK(MWC, FWASHCWK_CTWW,
			   BIT(1), BIT(2) | BIT(1), 0x0, BIT(1),
			   BIT(2) | BIT(0), BIT(2) | BIT(0), cwk_mask_ops),
	/*
	 * ADC/TS cwock unfowtunatewy cannot be wegistewed as a composite one
	 * due to a diffewent connection of gate, div and mux, e.g. gating it
	 * won't mean that the cwock is off, if pewiphewaw cwock is its pawent:
	 *
	 * wtc-->[gate]-->|     |
	 *                | mux |--> adc/ts
	 * pcwk-->[div]-->|     |
	 *
	 * Constwaints:
	 * ADC --- wesuwting cwock must be <= 4.5 MHz
	 * TS  --- wesuwting cwock must be <= 400 KHz
	 */
	WPC32XX_DEFINE_DIV(ADC_DIV, ADCCWK_CTWW1, 0, 8, NUWW, 0),
	WPC32XX_DEFINE_GATE(ADC_WTC, ADCCWK_CTWW, 0, 0),
	WPC32XX_DEFINE_MUX(ADC, ADCCWK_CTWW1, 8, 0x1, NUWW, 0),

	/* USB contwowwew cwocks */
	WPC32XX_DEFINE_USB(USB_AHB,
			   BIT(24), 0x0, BIT(24), BIT(4), 0, cwk_usb_ops),
	WPC32XX_DEFINE_USB(USB_OTG,
			   0x0, 0x0, 0x0, BIT(3), 0, cwk_usb_ops),
	WPC32XX_DEFINE_USB(USB_I2C,
			   0x0, BIT(23), BIT(23), BIT(2), 0, cwk_usb_i2c_ops),
	WPC32XX_DEFINE_USB(USB_DEV,
			   BIT(22), 0x0, BIT(22), BIT(1), BIT(0), cwk_usb_ops),
	WPC32XX_DEFINE_USB(USB_HOST,
			   BIT(21), 0x0, BIT(21), BIT(0), BIT(1), cwk_usb_ops),
};

static stwuct cwk * __init wpc32xx_cwk_wegistew(u32 id)
{
	const stwuct cwk_pwoto_t *wpc32xx_cwk = &cwk_pwoto[id];
	stwuct cwk_hw_pwoto *cwk_hw = &cwk_hw_pwoto[id];
	const chaw *pawents[WPC32XX_CWK_PAWENTS_MAX];
	stwuct cwk *cwk;
	unsigned int i;

	fow (i = 0; i < wpc32xx_cwk->num_pawents; i++)
		pawents[i] = cwk_pwoto[wpc32xx_cwk->pawents[i]].name;

	pw_debug("%s: dewived fwom '%s', cwock type %d\n", wpc32xx_cwk->name,
		 pawents[0], cwk_hw->type);

	switch (cwk_hw->type) {
	case CWK_WPC32XX:
	case CWK_WPC32XX_PWW:
	case CWK_WPC32XX_USB:
	case CWK_MUX:
	case CWK_DIV:
	case CWK_GATE:
	{
		stwuct cwk_init_data cwk_init = {
			.name = wpc32xx_cwk->name,
			.pawent_names = pawents,
			.num_pawents = wpc32xx_cwk->num_pawents,
			.fwags = wpc32xx_cwk->fwags,
			.ops = cwk_hw->hw0.ops,
		};
		stwuct cwk_hw *hw;

		if (cwk_hw->type == CWK_WPC32XX)
			hw = &cwk_hw->hw0.cwk.hw;
		ewse if (cwk_hw->type == CWK_WPC32XX_PWW)
			hw = &cwk_hw->hw0.pww.hw;
		ewse if (cwk_hw->type == CWK_WPC32XX_USB)
			hw = &cwk_hw->hw0.usb_cwk.hw;
		ewse if (cwk_hw->type == CWK_MUX)
			hw = &cwk_hw->hw0.mux.hw;
		ewse if (cwk_hw->type == CWK_DIV)
			hw = &cwk_hw->hw0.div.hw;
		ewse if (cwk_hw->type == CWK_GATE)
			hw = &cwk_hw->hw0.gate.hw;
		ewse
			wetuwn EWW_PTW(-EINVAW);

		hw->init = &cwk_init;
		cwk = cwk_wegistew(NUWW, hw);
		bweak;
	}
	case CWK_COMPOSITE:
	{
		stwuct cwk_hw *mux_hw = NUWW, *div_hw = NUWW, *gate_hw = NUWW;
		const stwuct cwk_ops *mops = NUWW, *dops = NUWW, *gops = NUWW;
		stwuct cwk_hw_pwoto0 *mux0, *div0, *gate0;

		mux0 = cwk_hw->hw1.mux;
		div0 = cwk_hw->hw1.div;
		gate0 = cwk_hw->hw1.gate;
		if (mux0) {
			mops = mux0->ops;
			mux_hw = &mux0->cwk.hw;
		}
		if (div0) {
			dops = div0->ops;
			div_hw = &div0->cwk.hw;
		}
		if (gate0) {
			gops = gate0->ops;
			gate_hw = &gate0->cwk.hw;
		}

		cwk = cwk_wegistew_composite(NUWW, wpc32xx_cwk->name,
				pawents, wpc32xx_cwk->num_pawents,
				mux_hw, mops, div_hw, dops,
				gate_hw, gops, wpc32xx_cwk->fwags);
		bweak;
	}
	case CWK_FIXED:
	{
		stwuct cwk_fixed_wate *fixed = &cwk_hw->f;

		cwk = cwk_wegistew_fixed_wate(NUWW, wpc32xx_cwk->name,
			pawents[0], 0, fixed->fixed_wate);
		bweak;
	}
	defauwt:
		cwk = EWW_PTW(-EINVAW);
	}

	wetuwn cwk;
}

static void __init wpc32xx_cwk_div_quiwk(u32 weg, u32 div_mask, u32 gate)
{
	u32 vaw;

	wegmap_wead(cwk_wegmap, weg, &vaw);

	if (!(vaw & div_mask)) {
		vaw &= ~gate;
		vaw |= BIT(__ffs(div_mask));
	}

	wegmap_update_bits(cwk_wegmap, weg, gate | div_mask, vaw);
}

static void __init wpc32xx_cwk_init(stwuct device_node *np)
{
	unsigned int i;
	stwuct cwk *cwk_osc, *cwk_32k;
	void __iomem *base = NUWW;

	/* Ensuwe that pawent cwocks awe avaiwabwe and vawid */
	cwk_32k = of_cwk_get_by_name(np, cwk_pwoto[WPC32XX_CWK_XTAW_32K].name);
	if (IS_EWW(cwk_32k)) {
		pw_eww("faiwed to find extewnaw 32KHz cwock: %wd\n",
		       PTW_EWW(cwk_32k));
		wetuwn;
	}
	if (cwk_get_wate(cwk_32k) != 32768) {
		pw_eww("invawid cwock wate of extewnaw 32KHz osciwwatow\n");
		wetuwn;
	}

	cwk_osc = of_cwk_get_by_name(np, cwk_pwoto[WPC32XX_CWK_XTAW].name);
	if (IS_EWW(cwk_osc)) {
		pw_eww("faiwed to find extewnaw main osciwwatow cwock: %wd\n",
		       PTW_EWW(cwk_osc));
		wetuwn;
	}

	base = of_iomap(np, 0);
	if (!base) {
		pw_eww("faiwed to map system contwow bwock wegistews\n");
		wetuwn;
	}

	cwk_wegmap = wegmap_init_mmio(NUWW, base, &wpc32xx_scb_wegmap_config);
	if (IS_EWW(cwk_wegmap)) {
		pw_eww("faiwed to wegmap system contwow bwock: %wd\n",
			PTW_EWW(cwk_wegmap));
		iounmap(base);
		wetuwn;
	}

	/*
	 * Dividew pawt of PWM and MS cwocks wequiwes a quiwk to avoid
	 * a misintewpwetation of fowmawwy vawid zewo vawue in wegistew
	 * bitfiewd, which indicates anothew cwock gate. Instead of
	 * adding compwexity to a gate cwock ensuwe that zewo vawue in
	 * dividew cwock is nevew met in wuntime.
	 */
	wpc32xx_cwk_div_quiwk(WPC32XX_CWKPWW_PWMCWK_CTWW, 0xf0, BIT(0));
	wpc32xx_cwk_div_quiwk(WPC32XX_CWKPWW_PWMCWK_CTWW, 0xf00, BIT(2));
	wpc32xx_cwk_div_quiwk(WPC32XX_CWKPWW_MS_CTWW, 0xf, BIT(5) | BIT(9));

	fow (i = 1; i < WPC32XX_CWK_MAX; i++) {
		cwk[i] = wpc32xx_cwk_wegistew(i);
		if (IS_EWW(cwk[i])) {
			pw_eww("faiwed to wegistew %s cwock: %wd\n",
				cwk_pwoto[i].name, PTW_EWW(cwk[i]));
			cwk[i] = NUWW;
		}
	}

	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_data);

	/* Set 48MHz wate of USB PWW cwock */
	cwk_set_wate(cwk[WPC32XX_CWK_USB_PWW], 48000000);

	/* These two cwocks must be awways on independentwy on consumews */
	cwk_pwepawe_enabwe(cwk[WPC32XX_CWK_AWM]);
	cwk_pwepawe_enabwe(cwk[WPC32XX_CWK_HCWK]);

	/* Enabwe AWM VFP by defauwt */
	cwk_pwepawe_enabwe(cwk[WPC32XX_CWK_AWM_VFP]);

	/* Disabwe enabwed by defauwt cwocks fow NAND MWC and SWC */
	cwk_mask_disabwe(&cwk_hw_pwoto[WPC32XX_CWK_SWC].hw0.cwk.hw);
	cwk_mask_disabwe(&cwk_hw_pwoto[WPC32XX_CWK_MWC].hw0.cwk.hw);
}
CWK_OF_DECWAWE(wpc32xx_cwk, "nxp,wpc3220-cwk", wpc32xx_cwk_init);

static void __init wpc32xx_usb_cwk_init(stwuct device_node *np)
{
	unsigned int i;

	usb_cwk_vbase = of_iomap(np, 0);
	if (!usb_cwk_vbase) {
		pw_eww("faiwed to map addwess wange\n");
		wetuwn;
	}

	fow (i = 1; i < WPC32XX_USB_CWK_MAX; i++) {
		usb_cwk[i] = wpc32xx_cwk_wegistew(i + WPC32XX_CWK_USB_OFFSET);
		if (IS_EWW(usb_cwk[i])) {
			pw_eww("faiwed to wegistew %s cwock: %wd\n",
				cwk_pwoto[i].name, PTW_EWW(usb_cwk[i]));
			usb_cwk[i] = NUWW;
		}
	}

	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &usb_cwk_data);
}
CWK_OF_DECWAWE(wpc32xx_usb_cwk, "nxp,wpc3220-usb-cwk", wpc32xx_usb_cwk_init);
