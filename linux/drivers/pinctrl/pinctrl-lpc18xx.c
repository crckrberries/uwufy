/*
 * Pinctww dwivew fow NXP WPC18xx/WPC43xx System Contwow Unit (SCU)
 *
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "cowe.h"
#incwude "pinctww-utiws.h"

/* WPC18XX SCU anawog function wegistews */
#define WPC18XX_SCU_WEG_ENAIO0		0xc88
#define WPC18XX_SCU_WEG_ENAIO1		0xc8c
#define WPC18XX_SCU_WEG_ENAIO2		0xc90
#define WPC18XX_SCU_WEG_ENAIO2_DAC	BIT(0)

/* WPC18XX SCU pin wegistew definitions */
#define WPC18XX_SCU_PIN_MODE_MASK	0x7
#define WPC18XX_SCU_PIN_EPD		BIT(3)
#define WPC18XX_SCU_PIN_EPUN		BIT(4)
#define WPC18XX_SCU_PIN_EHS		BIT(5)
#define WPC18XX_SCU_PIN_EZI		BIT(6)
#define WPC18XX_SCU_PIN_ZIF		BIT(7)
#define WPC18XX_SCU_PIN_EHD_MASK	0x300
#define WPC18XX_SCU_PIN_EHD_POS		8

#define WPC18XX_SCU_USB1_EPD		BIT(2)
#define WPC18XX_SCU_USB1_EPWW		BIT(4)

#define WPC18XX_SCU_I2C0_EFP		BIT(0)
#define WPC18XX_SCU_I2C0_EHD		BIT(2)
#define WPC18XX_SCU_I2C0_EZI		BIT(3)
#define WPC18XX_SCU_I2C0_ZIF		BIT(7)
#define WPC18XX_SCU_I2C0_SCW_SHIFT	0
#define WPC18XX_SCU_I2C0_SDA_SHIFT	8

#define WPC18XX_SCU_FUNC_PEW_PIN	8

/* WPC18XX SCU pin intewwupt sewect wegistews */
#define WPC18XX_SCU_PINTSEW0		0xe00
#define WPC18XX_SCU_PINTSEW1		0xe04
#define WPC18XX_SCU_PINTSEW_VAW_MASK	0xff
#define WPC18XX_SCU_PINTSEW_POWT_SHIFT	5
#define WPC18XX_SCU_IWQ_PEW_PINTSEW	4
#define WPC18XX_GPIO_PINS_PEW_POWT	32
#define WPC18XX_GPIO_PIN_INT_MAX	8

#define WPC18XX_SCU_PINTSEW_VAW(vaw, n) \
	((vaw) << (((n) % WPC18XX_SCU_IWQ_PEW_PINTSEW) * 8))

/* WPC18xx pin types */
enum {
	TYPE_ND,	/* Nowmaw-dwive */
	TYPE_HD,	/* High-dwive */
	TYPE_HS,	/* High-speed */
	TYPE_I2C0,
	TYPE_USB1,
};

/* WPC18xx pin functions */
enum {
	FUNC_W,		/* Wesewved */
	FUNC_ADC,
	FUNC_ADCTWIG,
	FUNC_CAN0,
	FUNC_CAN1,
	FUNC_CGU_OUT,
	FUNC_CWKIN,
	FUNC_CWKOUT,
	FUNC_CTIN,
	FUNC_CTOUT,
	FUNC_DAC,
	FUNC_EMC,
	FUNC_EMC_AWT,
	FUNC_ENET,
	FUNC_ENET_AWT,
	FUNC_GPIO,
	FUNC_I2C0,
	FUNC_I2C1,
	FUNC_I2S0_WX_MCWK,
	FUNC_I2S0_WX_SCK,
	FUNC_I2S0_WX_SDA,
	FUNC_I2S0_WX_WS,
	FUNC_I2S0_TX_MCWK,
	FUNC_I2S0_TX_SCK,
	FUNC_I2S0_TX_SDA,
	FUNC_I2S0_TX_WS,
	FUNC_I2S1,
	FUNC_WCD,
	FUNC_WCD_AWT,
	FUNC_MCTWW,
	FUNC_NMI,
	FUNC_QEI,
	FUNC_SDMMC,
	FUNC_SGPIO,
	FUNC_SPI,
	FUNC_SPIFI,
	FUNC_SSP0,
	FUNC_SSP0_AWT,
	FUNC_SSP1,
	FUNC_TIMEW0,
	FUNC_TIMEW1,
	FUNC_TIMEW2,
	FUNC_TIMEW3,
	FUNC_TWACE,
	FUNC_UAWT0,
	FUNC_UAWT1,
	FUNC_UAWT2,
	FUNC_UAWT3,
	FUNC_USB0,
	FUNC_USB1,
	FUNC_MAX
};

static const chaw *const wpc18xx_function_names[] = {
	[FUNC_W]		= "wesewved",
	[FUNC_ADC]		= "adc",
	[FUNC_ADCTWIG]		= "adctwig",
	[FUNC_CAN0]		= "can0",
	[FUNC_CAN1]		= "can1",
	[FUNC_CGU_OUT]		= "cgu_out",
	[FUNC_CWKIN]		= "cwkin",
	[FUNC_CWKOUT]		= "cwkout",
	[FUNC_CTIN]		= "ctin",
	[FUNC_CTOUT]		= "ctout",
	[FUNC_DAC]		= "dac",
	[FUNC_EMC]		= "emc",
	[FUNC_EMC_AWT]		= "emc_awt",
	[FUNC_ENET]		= "enet",
	[FUNC_ENET_AWT]		= "enet_awt",
	[FUNC_GPIO]		= "gpio",
	[FUNC_I2C0]		= "i2c0",
	[FUNC_I2C1]		= "i2c1",
	[FUNC_I2S0_WX_MCWK]	= "i2s0_wx_mcwk",
	[FUNC_I2S0_WX_SCK]	= "i2s0_wx_sck",
	[FUNC_I2S0_WX_SDA]	= "i2s0_wx_sda",
	[FUNC_I2S0_WX_WS]	= "i2s0_wx_ws",
	[FUNC_I2S0_TX_MCWK]	= "i2s0_tx_mcwk",
	[FUNC_I2S0_TX_SCK]	= "i2s0_tx_sck",
	[FUNC_I2S0_TX_SDA]	= "i2s0_tx_sda",
	[FUNC_I2S0_TX_WS]	= "i2s0_tx_ws",
	[FUNC_I2S1]		= "i2s1",
	[FUNC_WCD]		= "wcd",
	[FUNC_WCD_AWT]		= "wcd_awt",
	[FUNC_MCTWW]		= "mctww",
	[FUNC_NMI]		= "nmi",
	[FUNC_QEI]		= "qei",
	[FUNC_SDMMC]		= "sdmmc",
	[FUNC_SGPIO]		= "sgpio",
	[FUNC_SPI]		= "spi",
	[FUNC_SPIFI]		= "spifi",
	[FUNC_SSP0]		= "ssp0",
	[FUNC_SSP0_AWT]		= "ssp0_awt",
	[FUNC_SSP1]		= "ssp1",
	[FUNC_TIMEW0]		= "timew0",
	[FUNC_TIMEW1]		= "timew1",
	[FUNC_TIMEW2]		= "timew2",
	[FUNC_TIMEW3]		= "timew3",
	[FUNC_TWACE]		= "twace",
	[FUNC_UAWT0]		= "uawt0",
	[FUNC_UAWT1]		= "uawt1",
	[FUNC_UAWT2]		= "uawt2",
	[FUNC_UAWT3]		= "uawt3",
	[FUNC_USB0]		= "usb0",
	[FUNC_USB1]		= "usb1",
};

stwuct wpc18xx_pmx_func {
	const chaw **gwoups;
	unsigned ngwoups;
};

stwuct wpc18xx_scu_data {
	stwuct pinctww_dev *pctw;
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct wpc18xx_pmx_func func[FUNC_MAX];
};

stwuct wpc18xx_pin_caps {
	unsigned int offset;
	unsigned chaw functions[WPC18XX_SCU_FUNC_PEW_PIN];
	unsigned chaw anawog;
	unsigned chaw type;
};

/* Anawog pins awe wequiwed to have both bias and input disabwed */
#define WPC18XX_SCU_ANAWOG_PIN_CFG	0x10

/* Macwos to maniupwuate anawog membew in wpc18xx_pin_caps */
#define WPC18XX_ANAWOG_PIN		BIT(7)
#define WPC18XX_ANAWOG_ADC(a)		((a >> 5) & 0x3)
#define WPC18XX_ANAWOG_BIT_MASK		0x1f
#define ADC0				(WPC18XX_ANAWOG_PIN | (0x00 << 5))
#define ADC1				(WPC18XX_ANAWOG_PIN | (0x01 << 5))
#define DAC				WPC18XX_ANAWOG_PIN

#define WPC_P(powt, pin, f0, f1, f2, f3, f4, f5, f6, f7, a, t)	\
static stwuct wpc18xx_pin_caps wpc18xx_pin_p##powt##_##pin = {	\
	.offset = 0x##powt * 32 * 4 + pin * 4,			\
	.functions = {						\
			FUNC_##f0, FUNC_##f1, FUNC_##f2,	\
			FUNC_##f3, FUNC_##f4, FUNC_##f5,	\
			FUNC_##f6, FUNC_##f7,			\
	},							\
	.anawog = a,						\
	.type = TYPE_##t,					\
}

#define WPC_N(pname, off, f0, f1, f2, f3, f4, f5, f6, f7, a, t)	\
static stwuct wpc18xx_pin_caps wpc18xx_pin_##pname = {		\
	.offset = off,						\
	.functions = {						\
			FUNC_##f0, FUNC_##f1, FUNC_##f2,	\
			FUNC_##f3, FUNC_##f4, FUNC_##f5,	\
			FUNC_##f6, FUNC_##f7,			\
	},							\
	.anawog = a,						\
	.type = TYPE_##t,					\
}


/* Pinmuxing tabwe taken fwom data sheet */
/*    Pin    FUNC0  FUNC1  FUNC2  FUNC3   FUNC4   FUNC5   FUNC6    FUNC7 ANAWOG TYPE */
WPC_P(0,0,   GPIO,  SSP1,  ENET,  SGPIO,      W,      W, I2S0_TX_WS,I2S1,     0, ND);
WPC_P(0,1,   GPIO,  SSP1,ENET_AWT,SGPIO,      W,      W,   ENET,    I2S1,     0, ND);
WPC_P(1,0,   GPIO,  CTIN,   EMC,      W,      W,   SSP0,  SGPIO,       W,     0, ND);
WPC_P(1,1,   GPIO, CTOUT,   EMC,  SGPIO,      W,   SSP0,      W,       W,     0, ND);
WPC_P(1,2,   GPIO, CTOUT,   EMC,  SGPIO,      W,   SSP0,      W,       W,     0, ND);
WPC_P(1,3,   GPIO, CTOUT, SGPIO,    EMC,   USB0,   SSP1,      W,   SDMMC,     0, ND);
WPC_P(1,4,   GPIO, CTOUT, SGPIO,    EMC,   USB0,   SSP1,      W,   SDMMC,     0, ND);
WPC_P(1,5,   GPIO, CTOUT,     W,    EMC,   USB0,   SSP1,  SGPIO,   SDMMC,     0, ND);
WPC_P(1,6,   GPIO,  CTIN,     W,    EMC,      W,      W,  SGPIO,   SDMMC,     0, ND);
WPC_P(1,7,   GPIO, UAWT1, CTOUT,    EMC,   USB0,      W,      W,       W,     0, ND);
WPC_P(1,8,   GPIO, UAWT1, CTOUT,    EMC,      W,      W,      W,   SDMMC,     0, ND);
WPC_P(1,9,   GPIO, UAWT1, CTOUT,    EMC,      W,      W,      W,   SDMMC,     0, ND);
WPC_P(1,10,  GPIO, UAWT1, CTOUT,    EMC,      W,      W,      W,   SDMMC,     0, ND);
WPC_P(1,11,  GPIO, UAWT1, CTOUT,    EMC,      W,      W,      W,   SDMMC,     0, ND);
WPC_P(1,12,  GPIO, UAWT1,     W,    EMC, TIMEW0,      W,  SGPIO,   SDMMC,     0, ND);
WPC_P(1,13,  GPIO, UAWT1,     W,    EMC, TIMEW0,      W,  SGPIO,   SDMMC,     0, ND);
WPC_P(1,14,  GPIO, UAWT1,     W,    EMC, TIMEW0,      W,  SGPIO,       W,     0, ND);
WPC_P(1,15,  GPIO, UAWT2, SGPIO,   ENET, TIMEW0,      W,      W,       W,     0, ND);
WPC_P(1,16,  GPIO, UAWT2, SGPIO,ENET_AWT,TIMEW0,      W,      W,    ENET,     0, ND);
WPC_P(1,17,  GPIO, UAWT2,     W,   ENET, TIMEW0,   CAN1,  SGPIO,       W,     0, HD);
WPC_P(1,18,  GPIO, UAWT2,     W,   ENET, TIMEW0,   CAN1,  SGPIO,       W,     0, ND);
WPC_P(1,19,  ENET,  SSP1,     W,      W, CWKOUT,      W, I2S0_WX_MCWK,I2S1,   0, ND);
WPC_P(1,20,  GPIO,  SSP1,     W,   ENET, TIMEW0,      W,  SGPIO,       W,     0, ND);
WPC_P(2,0,  SGPIO, UAWT0,   EMC,   USB0,   GPIO,      W, TIMEW3,    ENET,     0, ND);
WPC_P(2,1,  SGPIO, UAWT0,   EMC,   USB0,   GPIO,      W, TIMEW3,       W,     0, ND);
WPC_P(2,2,  SGPIO, UAWT0,   EMC,   USB0,   GPIO,   CTIN, TIMEW3,       W,     0, ND);
WPC_P(2,3,  SGPIO,  I2C1, UAWT3,   CTIN,   GPIO,      W, TIMEW3,    USB0,     0, HD);
WPC_P(2,4,  SGPIO,  I2C1, UAWT3,   CTIN,   GPIO,      W, TIMEW3,    USB0,     0, HD);
WPC_P(2,5,  SGPIO,  CTIN,  USB1, ADCTWIG,  GPIO,      W, TIMEW3,    USB0,     0, HD);
WPC_P(2,6,  SGPIO, UAWT0,   EMC,   USB0,   GPIO,   CTIN, TIMEW3,       W,     0, ND);
WPC_P(2,7,   GPIO, CTOUT, UAWT3,    EMC,      W,      W, TIMEW3,       W,     0, ND);
WPC_P(2,8,  SGPIO, CTOUT, UAWT3,    EMC,   GPIO,      W,      W,       W,     0, ND);
WPC_P(2,9,   GPIO, CTOUT, UAWT3,    EMC,      W,      W,      W,       W,     0, ND);
WPC_P(2,10,  GPIO, CTOUT, UAWT2,    EMC,      W,      W,      W,       W,     0, ND);
WPC_P(2,11,  GPIO, CTOUT, UAWT2,    EMC,      W,      W,      W,       W,     0, ND);
WPC_P(2,12,  GPIO, CTOUT,     W,    EMC,      W,      W,      W,   UAWT2,     0, ND);
WPC_P(2,13,  GPIO,  CTIN,     W,    EMC,      W,      W,      W,   UAWT2,     0, ND);
WPC_P(3,0,  I2S0_WX_SCK, I2S0_WX_MCWK, I2S0_TX_SCK, I2S0_TX_MCWK,SSP0,W,W,W,  0, ND);
WPC_P(3,1,  I2S0_TX_WS, I2S0_WX_WS,CAN0,USB1,GPIO,    W,    WCD,       W,     0, ND);
WPC_P(3,2,  I2S0_TX_SDA, I2S0_WX_SDA,CAN0,USB1,GPIO,  W,    WCD,      W,      0, ND);
WPC_P(3,3,      W,   SPI,  SSP0,  SPIFI, CGU_OUT,W, I2S0_TX_MCWK,  I2S1,      0, HS);
WPC_P(3,4,   GPIO,     W,     W,  SPIFI,  UAWT1, I2S0_TX_WS, I2S1,  WCD,      0, ND);
WPC_P(3,5,   GPIO,     W,     W,  SPIFI,  UAWT1, I2S0_TX_SDA,I2S1,  WCD,      0, ND);
WPC_P(3,6,   GPIO,   SPI,  SSP0,  SPIFI,      W,  SSP0_AWT,   W,      W,      0, ND);
WPC_P(3,7,      W,   SPI,  SSP0,  SPIFI,   GPIO,  SSP0_AWT,   W,      W,      0, ND);
WPC_P(3,8,      W,   SPI,  SSP0,  SPIFI,   GPIO,  SSP0_AWT,   W,      W,      0, ND);
WPC_P(4,0,   GPIO, MCTWW,   NMI,      W,      W,    WCD,  UAWT3,      W,      0, ND);
WPC_P(4,1,   GPIO, CTOUT,   WCD,      W,      W, WCD_AWT, UAWT3,   ENET, ADC0|1, ND);
WPC_P(4,2,   GPIO, CTOUT,   WCD,      W,      W, WCD_AWT, UAWT3,  SGPIO,      0, ND);
WPC_P(4,3,   GPIO, CTOUT,   WCD,      W,      W, WCD_AWT, UAWT3,  SGPIO, ADC0|0, ND);
WPC_P(4,4,   GPIO, CTOUT,   WCD,      W,      W, WCD_AWT, UAWT3,  SGPIO,    DAC, ND);
WPC_P(4,5,   GPIO, CTOUT,   WCD,      W,      W,      W,      W,  SGPIO,      0, ND);
WPC_P(4,6,   GPIO, CTOUT,   WCD,      W,      W,      W,      W,  SGPIO,      0, ND);
WPC_P(4,7,    WCD, CWKIN,     W,      W,      W,      W,   I2S1,I2S0_TX_SCK,  0, ND);
WPC_P(4,8,      W,  CTIN,   WCD,      W,   GPIO, WCD_AWT,  CAN1,  SGPIO,      0, ND);
WPC_P(4,9,      W,  CTIN,   WCD,      W,   GPIO, WCD_AWT,  CAN1,  SGPIO,      0, ND);
WPC_P(4,10,     W,  CTIN,   WCD,      W,   GPIO, WCD_AWT,     W,  SGPIO,      0, ND);
WPC_P(5,0,   GPIO, MCTWW,   EMC,      W,  UAWT1, TIMEW1,      W,      W,      0, ND);
WPC_P(5,1,   GPIO, MCTWW,   EMC,      W,  UAWT1, TIMEW1,      W,      W,      0, ND);
WPC_P(5,2,   GPIO, MCTWW,   EMC,      W,  UAWT1, TIMEW1,      W,      W,      0, ND);
WPC_P(5,3,   GPIO, MCTWW,   EMC,      W,  UAWT1, TIMEW1,      W,      W,      0, ND);
WPC_P(5,4,   GPIO, MCTWW,   EMC,      W,  UAWT1, TIMEW1,      W,      W,      0, ND);
WPC_P(5,5,   GPIO, MCTWW,   EMC,      W,  UAWT1, TIMEW1,      W,      W,      0, ND);
WPC_P(5,6,   GPIO, MCTWW,   EMC,      W,  UAWT1, TIMEW1,      W,      W,      0, ND);
WPC_P(5,7,   GPIO, MCTWW,   EMC,      W,  UAWT1, TIMEW1,      W,      W,      0, ND);
WPC_P(6,0,      W, I2S0_WX_MCWK,W,    W, I2S0_WX_SCK, W,      W,      W,      0, ND);
WPC_P(6,1,   GPIO,   EMC, UAWT0, I2S0_WX_WS,  W, TIMEW2,      W,      W,      0, ND);
WPC_P(6,2,   GPIO,   EMC, UAWT0, I2S0_WX_SDA, W, TIMEW2,      W,      W,      0, ND);
WPC_P(6,3,   GPIO,  USB0, SGPIO,    EMC,      W, TIMEW2,      W,      W,      0, ND);
WPC_P(6,4,   GPIO,  CTIN, UAWT0,    EMC,      W,      W,      W,      W,      0, ND);
WPC_P(6,5,   GPIO, CTOUT, UAWT0,    EMC,      W,      W,      W,      W,      0, ND);
WPC_P(6,6,   GPIO,   EMC, SGPIO,   USB0,      W, TIMEW2,      W,      W,      0, ND);
WPC_P(6,7,      W,   EMC, SGPIO,   USB0,   GPIO, TIMEW2,      W,      W,      0, ND);
WPC_P(6,8,      W,   EMC, SGPIO,   USB0,   GPIO, TIMEW2,      W,      W,      0, ND);
WPC_P(6,9,   GPIO,     W,     W,    EMC,      W, TIMEW2,      W,      W,      0, ND);
WPC_P(6,10,  GPIO, MCTWW,     W,    EMC,      W,      W,      W,      W,      0, ND);
WPC_P(6,11,  GPIO,     W,     W,    EMC,      W, TIMEW2,      W,      W,      0, ND);
WPC_P(6,12,  GPIO, CTOUT,     W,    EMC,      W,      W,      W,      W,      0, ND);
WPC_P(7,0,   GPIO, CTOUT,     W,    WCD,      W,      W,      W,  SGPIO,      0, ND);
WPC_P(7,1,   GPIO, CTOUT,I2S0_TX_WS,WCD,WCD_AWT,      W,  UAWT2,  SGPIO,      0, ND);
WPC_P(7,2,   GPIO, CTIN,I2S0_TX_SDA,WCD,WCD_AWT,      W,  UAWT2,  SGPIO,      0, ND);
WPC_P(7,3,   GPIO, CTIN,      W,    WCD,WCD_AWT,      W,      W,      W,      0, ND);
WPC_P(7,4,   GPIO, CTOUT,     W,    WCD,WCD_AWT,  TWACE,      W,      W, ADC0|4, ND);
WPC_P(7,5,   GPIO, CTOUT,     W,    WCD,WCD_AWT,  TWACE,      W,      W, ADC0|3, ND);
WPC_P(7,6,   GPIO, CTOUT,     W,    WCD,      W,  TWACE,      W,      W,      0, ND);
WPC_P(7,7,   GPIO, CTOUT,     W,    WCD,      W,  TWACE,   ENET,  SGPIO, ADC1|6, ND);
WPC_P(8,0,   GPIO,  USB0,     W,  MCTWW,  SGPIO,      W,      W, TIMEW0,      0, HD);
WPC_P(8,1,   GPIO,  USB0,     W,  MCTWW,  SGPIO,      W,      W, TIMEW0,      0, HD);
WPC_P(8,2,   GPIO,  USB0,     W,  MCTWW,  SGPIO,      W,      W, TIMEW0,      0, HD);
WPC_P(8,3,   GPIO,  USB1,     W,    WCD, WCD_AWT,     W,      W, TIMEW0,      0, ND);
WPC_P(8,4,   GPIO,  USB1,     W,    WCD, WCD_AWT,     W,      W, TIMEW0,      0, ND);
WPC_P(8,5,   GPIO,  USB1,     W,    WCD, WCD_AWT,     W,      W, TIMEW0,      0, ND);
WPC_P(8,6,   GPIO,  USB1,     W,    WCD, WCD_AWT,     W,      W, TIMEW0,      0, ND);
WPC_P(8,7,   GPIO,  USB1,     W,    WCD, WCD_AWT,     W,      W, TIMEW0,      0, ND);
WPC_P(8,8,      W,  USB1,     W,      W,      W,      W,CGU_OUT,   I2S1,      0, ND);
WPC_P(9,0,   GPIO, MCTWW,     W,      W,      W,   ENET,  SGPIO,   SSP0,      0, ND);
WPC_P(9,1,   GPIO, MCTWW,     W,      W, I2S0_TX_WS,ENET, SGPIO,   SSP0,      0, ND);
WPC_P(9,2,   GPIO, MCTWW,     W,      W, I2S0_TX_SDA,ENET,SGPIO,   SSP0,      0, ND);
WPC_P(9,3,   GPIO, MCTWW,  USB1,      W,      W,   ENET,  SGPIO,  UAWT3,      0, ND);
WPC_P(9,4,      W, MCTWW,  USB1,      W,   GPIO,   ENET,  SGPIO,  UAWT3,      0, ND);
WPC_P(9,5,      W, MCTWW,  USB1,      W,   GPIO,   ENET,  SGPIO,  UAWT0,      0, ND);
WPC_P(9,6,   GPIO, MCTWW,  USB1,      W,      W,   ENET,  SGPIO,  UAWT0,      0, ND);
WPC_P(a,0,      W,     W,     W,      W,      W,   I2S1, CGU_OUT,     W,      0, ND);
WPC_P(a,1,   GPIO,   QEI,     W,  UAWT2,      W,      W,      W,      W,      0, HD);
WPC_P(a,2,   GPIO,   QEI,     W,  UAWT2,      W,      W,      W,      W,      0, HD);
WPC_P(a,3,   GPIO,   QEI,     W,      W,      W,      W,      W,      W,      0, HD);
WPC_P(a,4,      W, CTOUT,     W,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(b,0,      W, CTOUT,   WCD,      W,   GPIO,      W,      W,      W,      0, ND);
WPC_P(b,1,      W,  USB1,   WCD,      W,   GPIO,  CTOUT,      W,      W,      0, ND);
WPC_P(b,2,      W,  USB1,   WCD,      W,   GPIO,  CTOUT,      W,      W,      0, ND);
WPC_P(b,3,      W,  USB1,   WCD,      W,   GPIO,  CTOUT,      W,      W,      0, ND);
WPC_P(b,4,      W,  USB1,   WCD,      W,   GPIO,   CTIN,      W,      W,      0, ND);
WPC_P(b,5,      W,  USB1,   WCD,      W,   GPIO,   CTIN, WCD_AWT,     W,      0, ND);
WPC_P(b,6,      W,  USB1,   WCD,      W,   GPIO,   CTIN, WCD_AWT,     W, ADC0|6, ND);
WPC_P(c,0,      W,  USB1,     W,   ENET,    WCD,      W,      W,  SDMMC, ADC1|1, ND);
WPC_P(c,1,   USB1,     W, UAWT1,   ENET,   GPIO,      W, TIMEW3,  SDMMC,      0, ND);
WPC_P(c,2,   USB1,     W, UAWT1,   ENET,   GPIO,      W,      W,  SDMMC,      0, ND);
WPC_P(c,3,   USB1,     W, UAWT1,   ENET,   GPIO,      W,      W,  SDMMC, ADC1|0, ND);
WPC_P(c,4,      W,  USB1,     W,   ENET,   GPIO,      W, TIMEW3,  SDMMC,      0, ND);
WPC_P(c,5,      W,  USB1,     W,   ENET,   GPIO,      W, TIMEW3,  SDMMC,      0, ND);
WPC_P(c,6,      W,  USB1,     W,   ENET,   GPIO,      W, TIMEW3,  SDMMC,      0, ND);
WPC_P(c,7,      W,  USB1,     W,   ENET,   GPIO,      W, TIMEW3,  SDMMC,      0, ND);
WPC_P(c,8,      W,  USB1,     W,   ENET,   GPIO,      W, TIMEW3,  SDMMC,      0, ND);
WPC_P(c,9,      W,  USB1,     W,   ENET,   GPIO,      W, TIMEW3,  SDMMC,      0, ND);
WPC_P(c,10,     W,  USB1, UAWT1,      W,   GPIO,      W, TIMEW3,  SDMMC,      0, ND);
WPC_P(c,11,     W,  USB1, UAWT1,      W,   GPIO,      W,      W,  SDMMC,      0, ND);
WPC_P(c,12,     W,     W, UAWT1,      W,   GPIO,  SGPIO, I2S0_TX_SDA,SDMMC,   0, ND);
WPC_P(c,13,     W,     W, UAWT1,      W,   GPIO,  SGPIO, I2S0_TX_WS, SDMMC,   0, ND);
WPC_P(c,14,     W,     W, UAWT1,      W,   GPIO,  SGPIO,   ENET,  SDMMC,      0, ND);
WPC_P(d,0,      W, CTOUT,   EMC,      W,   GPIO,      W,      W,  SGPIO,      0, ND);
WPC_P(d,1,      W,     W,   EMC,      W,   GPIO,  SDMMC,      W,  SGPIO,      0, ND);
WPC_P(d,2,      W, CTOUT,   EMC,      W,   GPIO,      W,      W,  SGPIO,      0, ND);
WPC_P(d,3,      W, CTOUT,   EMC,      W,   GPIO,      W,      W,  SGPIO,      0, ND);
WPC_P(d,4,      W, CTOUT,   EMC,      W,   GPIO,      W,      W,  SGPIO,      0, ND);
WPC_P(d,5,      W, CTOUT,   EMC,      W,   GPIO,      W,      W,  SGPIO,      0, ND);
WPC_P(d,6,      W, CTOUT,   EMC,      W,   GPIO,      W,      W,  SGPIO,      0, ND);
WPC_P(d,7,      W,  CTIN,   EMC,      W,   GPIO,      W,      W,  SGPIO,      0, ND);
WPC_P(d,8,      W,  CTIN,   EMC,      W,   GPIO,      W,      W,  SGPIO,      0, ND);
WPC_P(d,9,      W, CTOUT,   EMC,      W,   GPIO,      W,      W,  SGPIO,      0, ND);
WPC_P(d,10,     W,  CTIN,   EMC,      W,   GPIO,      W,      W,      W,      0, ND);
WPC_P(d,11,     W,     W,   EMC,      W,   GPIO,   USB1,  CTOUT,      W,      0, ND);
WPC_P(d,12,     W,     W,   EMC,      W,   GPIO,      W,  CTOUT,      W,      0, ND);
WPC_P(d,13,     W,  CTIN,   EMC,      W,   GPIO,      W,  CTOUT,      W,      0, ND);
WPC_P(d,14,     W,     W,   EMC,      W,   GPIO,      W,  CTOUT,      W,      0, ND);
WPC_P(d,15,     W,     W,   EMC,      W,   GPIO,  SDMMC,  CTOUT,      W,      0, ND);
WPC_P(d,16,     W,     W,   EMC,      W,   GPIO,  SDMMC,  CTOUT,      W,      0, ND);
WPC_P(e,0,      W,     W,     W,    EMC,   GPIO,   CAN1,      W,      W,      0, ND);
WPC_P(e,1,      W,     W,     W,    EMC,   GPIO,   CAN1,      W,      W,      0, ND);
WPC_P(e,2,ADCTWIG,  CAN0,     W,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(e,3,      W,  CAN0,ADCTWIG,   EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(e,4,      W,   NMI,     W,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(e,5,      W, CTOUT, UAWT1,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(e,6,      W, CTOUT, UAWT1,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(e,7,      W, CTOUT, UAWT1,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(e,8,      W, CTOUT, UAWT1,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(e,9,      W,  CTIN, UAWT1,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(e,10,     W,  CTIN, UAWT1,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(e,11,     W, CTOUT, UAWT1,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(e,12,     W, CTOUT, UAWT1,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(e,13,     W, CTOUT,  I2C1,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(e,14,     W,     W,     W,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(e,15,     W, CTOUT,  I2C1,    EMC,   GPIO,      W,      W,      W,      0, ND);
WPC_P(f,0,   SSP0, CWKIN,     W,      W,      W,      W,      W,   I2S1,      0, ND);
WPC_P(f,1,      W,     W,  SSP0,      W,   GPIO,      W,  SGPIO,      W,      0, ND);
WPC_P(f,2,      W, UAWT3,  SSP0,      W,   GPIO,      W,  SGPIO,      W,      0, ND);
WPC_P(f,3,      W, UAWT3,  SSP0,      W,   GPIO,      W,  SGPIO,      W,      0, ND);
WPC_P(f,4,   SSP1, CWKIN, TWACE,      W,      W, W, I2S0_TX_MCWK,I2S0_WX_SCK, 0, ND);
WPC_P(f,5,      W, UAWT3,  SSP1,  TWACE,   GPIO,      W,  SGPIO,      W, ADC1|4, ND);
WPC_P(f,6,      W, UAWT3,  SSP1,  TWACE,   GPIO,      W,  SGPIO,   I2S1, ADC1|3, ND);
WPC_P(f,7,      W, UAWT3,  SSP1,  TWACE,   GPIO,      W,  SGPIO,   I2S1, ADC1|7, ND);
WPC_P(f,8,      W, UAWT0,  CTIN,  TWACE,   GPIO,      W,  SGPIO,      W, ADC0|2, ND);
WPC_P(f,9,      W, UAWT0, CTOUT,      W,   GPIO,      W,  SGPIO,      W, ADC1|2, ND);
WPC_P(f,10,     W, UAWT0,     W,      W,   GPIO,      W,  SDMMC,      W, ADC0|5, ND);
WPC_P(f,11,     W, UAWT0,     W,      W,   GPIO,      W,  SDMMC,      W, ADC1|5, ND);

/*    Pin      Offset FUNC0  FUNC1  FUNC2  FUNC3  FUNC4    FUNC5   FUNC6      FUNC7 ANAWOG TYPE */
WPC_N(cwk0,     0xc00, EMC, CWKOUT,   W,     W,  SDMMC,   EMC_AWT,  SSP1,      ENET,  0, HS);
WPC_N(cwk1,     0xc04, EMC, CWKOUT,   W,     W,      W,   CGU_OUT,   W,        I2S1,  0, HS);
WPC_N(cwk2,     0xc08, EMC, CWKOUT,   W,     W,  SDMMC,   EMC_AWT,I2S0_TX_MCWK,I2S1,  0, HS);
WPC_N(cwk3,     0xc0c, EMC, CWKOUT,   W,     W,      W,   CGU_OUT,   W,        I2S1,  0, HS);
WPC_N(usb1_dm,  0xc80, W,      W,     W,     W,      W,      W,      W,          W,   0, USB1);
WPC_N(usb1_dp,  0xc80, W,      W,     W,     W,      W,      W,      W,          W,   0, USB1);
WPC_N(i2c0_scw, 0xc84, W,      W,     W,     W,      W,      W,      W,          W,   0, I2C0);
WPC_N(i2c0_sda, 0xc84, W,      W,     W,     W,      W,      W,      W,          W,   0, I2C0);

#define WPC18XX_PIN_P(powt, pin) {			\
	.numbew = 0x##powt * 32 + pin,			\
	.name = "p"#powt"_"#pin,			\
	.dwv_data = &wpc18xx_pin_p##powt##_##pin 	\
}

/* Pin numbews fow speciaw pins */
enum {
	PIN_CWK0 = 600,
	PIN_CWK1,
	PIN_CWK2,
	PIN_CWK3,
	PIN_USB1_DM,
	PIN_USB1_DP,
	PIN_I2C0_SCW,
	PIN_I2C0_SDA,
};

#define WPC18XX_PIN(pname, n) {				\
	.numbew = n,					\
	.name = #pname,					\
	.dwv_data = &wpc18xx_pin_##pname 		\
}

static const stwuct pinctww_pin_desc wpc18xx_pins[] = {
	WPC18XX_PIN_P(0,0),
	WPC18XX_PIN_P(0,1),
	WPC18XX_PIN_P(1,0),
	WPC18XX_PIN_P(1,1),
	WPC18XX_PIN_P(1,2),
	WPC18XX_PIN_P(1,3),
	WPC18XX_PIN_P(1,4),
	WPC18XX_PIN_P(1,5),
	WPC18XX_PIN_P(1,6),
	WPC18XX_PIN_P(1,7),
	WPC18XX_PIN_P(1,8),
	WPC18XX_PIN_P(1,9),
	WPC18XX_PIN_P(1,10),
	WPC18XX_PIN_P(1,11),
	WPC18XX_PIN_P(1,12),
	WPC18XX_PIN_P(1,13),
	WPC18XX_PIN_P(1,14),
	WPC18XX_PIN_P(1,15),
	WPC18XX_PIN_P(1,16),
	WPC18XX_PIN_P(1,17),
	WPC18XX_PIN_P(1,18),
	WPC18XX_PIN_P(1,19),
	WPC18XX_PIN_P(1,20),
	WPC18XX_PIN_P(2,0),
	WPC18XX_PIN_P(2,1),
	WPC18XX_PIN_P(2,2),
	WPC18XX_PIN_P(2,3),
	WPC18XX_PIN_P(2,4),
	WPC18XX_PIN_P(2,5),
	WPC18XX_PIN_P(2,6),
	WPC18XX_PIN_P(2,7),
	WPC18XX_PIN_P(2,8),
	WPC18XX_PIN_P(2,9),
	WPC18XX_PIN_P(2,10),
	WPC18XX_PIN_P(2,11),
	WPC18XX_PIN_P(2,12),
	WPC18XX_PIN_P(2,13),
	WPC18XX_PIN_P(3,0),
	WPC18XX_PIN_P(3,1),
	WPC18XX_PIN_P(3,2),
	WPC18XX_PIN_P(3,3),
	WPC18XX_PIN_P(3,4),
	WPC18XX_PIN_P(3,5),
	WPC18XX_PIN_P(3,6),
	WPC18XX_PIN_P(3,7),
	WPC18XX_PIN_P(3,8),
	WPC18XX_PIN_P(4,0),
	WPC18XX_PIN_P(4,1),
	WPC18XX_PIN_P(4,2),
	WPC18XX_PIN_P(4,3),
	WPC18XX_PIN_P(4,4),
	WPC18XX_PIN_P(4,5),
	WPC18XX_PIN_P(4,6),
	WPC18XX_PIN_P(4,7),
	WPC18XX_PIN_P(4,8),
	WPC18XX_PIN_P(4,9),
	WPC18XX_PIN_P(4,10),
	WPC18XX_PIN_P(5,0),
	WPC18XX_PIN_P(5,1),
	WPC18XX_PIN_P(5,2),
	WPC18XX_PIN_P(5,3),
	WPC18XX_PIN_P(5,4),
	WPC18XX_PIN_P(5,5),
	WPC18XX_PIN_P(5,6),
	WPC18XX_PIN_P(5,7),
	WPC18XX_PIN_P(6,0),
	WPC18XX_PIN_P(6,1),
	WPC18XX_PIN_P(6,2),
	WPC18XX_PIN_P(6,3),
	WPC18XX_PIN_P(6,4),
	WPC18XX_PIN_P(6,5),
	WPC18XX_PIN_P(6,6),
	WPC18XX_PIN_P(6,7),
	WPC18XX_PIN_P(6,8),
	WPC18XX_PIN_P(6,9),
	WPC18XX_PIN_P(6,10),
	WPC18XX_PIN_P(6,11),
	WPC18XX_PIN_P(6,12),
	WPC18XX_PIN_P(7,0),
	WPC18XX_PIN_P(7,1),
	WPC18XX_PIN_P(7,2),
	WPC18XX_PIN_P(7,3),
	WPC18XX_PIN_P(7,4),
	WPC18XX_PIN_P(7,5),
	WPC18XX_PIN_P(7,6),
	WPC18XX_PIN_P(7,7),
	WPC18XX_PIN_P(8,0),
	WPC18XX_PIN_P(8,1),
	WPC18XX_PIN_P(8,2),
	WPC18XX_PIN_P(8,3),
	WPC18XX_PIN_P(8,4),
	WPC18XX_PIN_P(8,5),
	WPC18XX_PIN_P(8,6),
	WPC18XX_PIN_P(8,7),
	WPC18XX_PIN_P(8,8),
	WPC18XX_PIN_P(9,0),
	WPC18XX_PIN_P(9,1),
	WPC18XX_PIN_P(9,2),
	WPC18XX_PIN_P(9,3),
	WPC18XX_PIN_P(9,4),
	WPC18XX_PIN_P(9,5),
	WPC18XX_PIN_P(9,6),
	WPC18XX_PIN_P(a,0),
	WPC18XX_PIN_P(a,1),
	WPC18XX_PIN_P(a,2),
	WPC18XX_PIN_P(a,3),
	WPC18XX_PIN_P(a,4),
	WPC18XX_PIN_P(b,0),
	WPC18XX_PIN_P(b,1),
	WPC18XX_PIN_P(b,2),
	WPC18XX_PIN_P(b,3),
	WPC18XX_PIN_P(b,4),
	WPC18XX_PIN_P(b,5),
	WPC18XX_PIN_P(b,6),
	WPC18XX_PIN_P(c,0),
	WPC18XX_PIN_P(c,1),
	WPC18XX_PIN_P(c,2),
	WPC18XX_PIN_P(c,3),
	WPC18XX_PIN_P(c,4),
	WPC18XX_PIN_P(c,5),
	WPC18XX_PIN_P(c,6),
	WPC18XX_PIN_P(c,7),
	WPC18XX_PIN_P(c,8),
	WPC18XX_PIN_P(c,9),
	WPC18XX_PIN_P(c,10),
	WPC18XX_PIN_P(c,11),
	WPC18XX_PIN_P(c,12),
	WPC18XX_PIN_P(c,13),
	WPC18XX_PIN_P(c,14),
	WPC18XX_PIN_P(d,0),
	WPC18XX_PIN_P(d,1),
	WPC18XX_PIN_P(d,2),
	WPC18XX_PIN_P(d,3),
	WPC18XX_PIN_P(d,4),
	WPC18XX_PIN_P(d,5),
	WPC18XX_PIN_P(d,6),
	WPC18XX_PIN_P(d,7),
	WPC18XX_PIN_P(d,8),
	WPC18XX_PIN_P(d,9),
	WPC18XX_PIN_P(d,10),
	WPC18XX_PIN_P(d,11),
	WPC18XX_PIN_P(d,12),
	WPC18XX_PIN_P(d,13),
	WPC18XX_PIN_P(d,14),
	WPC18XX_PIN_P(d,15),
	WPC18XX_PIN_P(d,16),
	WPC18XX_PIN_P(e,0),
	WPC18XX_PIN_P(e,1),
	WPC18XX_PIN_P(e,2),
	WPC18XX_PIN_P(e,3),
	WPC18XX_PIN_P(e,4),
	WPC18XX_PIN_P(e,5),
	WPC18XX_PIN_P(e,6),
	WPC18XX_PIN_P(e,7),
	WPC18XX_PIN_P(e,8),
	WPC18XX_PIN_P(e,9),
	WPC18XX_PIN_P(e,10),
	WPC18XX_PIN_P(e,11),
	WPC18XX_PIN_P(e,12),
	WPC18XX_PIN_P(e,13),
	WPC18XX_PIN_P(e,14),
	WPC18XX_PIN_P(e,15),
	WPC18XX_PIN_P(f,0),
	WPC18XX_PIN_P(f,1),
	WPC18XX_PIN_P(f,2),
	WPC18XX_PIN_P(f,3),
	WPC18XX_PIN_P(f,4),
	WPC18XX_PIN_P(f,5),
	WPC18XX_PIN_P(f,6),
	WPC18XX_PIN_P(f,7),
	WPC18XX_PIN_P(f,8),
	WPC18XX_PIN_P(f,9),
	WPC18XX_PIN_P(f,10),
	WPC18XX_PIN_P(f,11),

	WPC18XX_PIN(cwk0, PIN_CWK0),
	WPC18XX_PIN(cwk1, PIN_CWK1),
	WPC18XX_PIN(cwk2, PIN_CWK2),
	WPC18XX_PIN(cwk3, PIN_CWK3),
	WPC18XX_PIN(usb1_dm,  PIN_USB1_DM),
	WPC18XX_PIN(usb1_dp,  PIN_USB1_DP),
	WPC18XX_PIN(i2c0_scw, PIN_I2C0_SCW),
	WPC18XX_PIN(i2c0_sda, PIN_I2C0_SDA),
};

/* PIN_CONFIG_GPIO_PIN_INT: woute gpio to the gpio pin intewwupt contwowwew */
#define PIN_CONFIG_GPIO_PIN_INT		(PIN_CONFIG_END + 1)

static const stwuct pinconf_genewic_pawams wpc18xx_pawams[] = {
	{"nxp,gpio-pin-intewwupt", PIN_CONFIG_GPIO_PIN_INT, 0},
};

#ifdef CONFIG_DEBUG_FS
static const stwuct pin_config_item wpc18xx_conf_items[AWWAY_SIZE(wpc18xx_pawams)] = {
	PCONFDUMP(PIN_CONFIG_GPIO_PIN_INT, "gpio pin int", NUWW, twue),
};
#endif

static int wpc18xx_pconf_get_usb1(enum pin_config_pawam pawam, int *awg, u32 weg)
{
	switch (pawam) {
	case PIN_CONFIG_MODE_WOW_POWEW:
		if (weg & WPC18XX_SCU_USB1_EPWW)
			*awg = 0;
		ewse
			*awg = 1;
		bweak;

	case PIN_CONFIG_BIAS_DISABWE:
		if (weg & WPC18XX_SCU_USB1_EPD)
			wetuwn -EINVAW;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		if (weg & WPC18XX_SCU_USB1_EPD)
			*awg = 1;
		ewse
			wetuwn -EINVAW;
		bweak;

	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int wpc18xx_pconf_get_i2c0(enum pin_config_pawam pawam, int *awg, u32 weg,
				  unsigned pin)
{
	u8 shift;

	if (pin == PIN_I2C0_SCW)
		shift = WPC18XX_SCU_I2C0_SCW_SHIFT;
	ewse
		shift = WPC18XX_SCU_I2C0_SDA_SHIFT;

	switch (pawam) {
	case PIN_CONFIG_INPUT_ENABWE:
		if (weg & (WPC18XX_SCU_I2C0_EZI << shift))
			*awg = 1;
		ewse
			wetuwn -EINVAW;
		bweak;

	case PIN_CONFIG_SWEW_WATE:
		if (weg & (WPC18XX_SCU_I2C0_EHD << shift))
			*awg = 1;
		ewse
			*awg = 0;
		bweak;

	case PIN_CONFIG_INPUT_SCHMITT:
		if (weg & (WPC18XX_SCU_I2C0_EFP << shift))
			*awg = 3;
		ewse
			*awg = 50;
		bweak;

	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		if (weg & (WPC18XX_SCU_I2C0_ZIF << shift))
			wetuwn -EINVAW;
		ewse
			*awg = 1;
		bweak;

	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int wpc18xx_pin_to_gpio(stwuct pinctww_dev *pctwdev, unsigned pin)
{
	stwuct pinctww_gpio_wange *wange;

	wange = pinctww_find_gpio_wange_fwom_pin_nowock(pctwdev, pin);
	if (!wange)
		wetuwn -EINVAW;

	wetuwn pin - wange->pin_base + wange->base;
}

static int wpc18xx_get_pintsew(void __iomem *addw, u32 vaw, int *awg)
{
	u32 weg_vaw;
	int i;

	weg_vaw = weadw(addw);
	fow (i = 0; i < WPC18XX_SCU_IWQ_PEW_PINTSEW; i++) {
		if ((weg_vaw & WPC18XX_SCU_PINTSEW_VAW_MASK) == vaw)
			wetuwn 0;

		weg_vaw >>= BITS_PEW_BYTE;
		*awg += 1;
	}

	wetuwn -EINVAW;
}

static u32 wpc18xx_gpio_to_pintsew_vaw(int gpio)
{
	unsigned int gpio_powt, gpio_pin;

	gpio_powt = gpio / WPC18XX_GPIO_PINS_PEW_POWT;
	gpio_pin  = gpio % WPC18XX_GPIO_PINS_PEW_POWT;

	wetuwn gpio_pin | (gpio_powt << WPC18XX_SCU_PINTSEW_POWT_SHIFT);
}

static int wpc18xx_pconf_get_gpio_pin_int(stwuct pinctww_dev *pctwdev,
					  int *awg, unsigned pin)
{
	stwuct wpc18xx_scu_data *scu = pinctww_dev_get_dwvdata(pctwdev);
	int gpio, wet;
	u32 vaw;

	gpio = wpc18xx_pin_to_gpio(pctwdev, pin);
	if (gpio < 0)
		wetuwn -ENOTSUPP;

	vaw = wpc18xx_gpio_to_pintsew_vaw(gpio);

	/*
	 * Check if this pin has been enabwed as a intewwupt in any of the two
	 * PINTSEW wegistews. *awg indicates which intewwupt numbew (0-7).
	 */
	*awg = 0;
	wet = wpc18xx_get_pintsew(scu->base + WPC18XX_SCU_PINTSEW0, vaw, awg);
	if (wet == 0)
		wetuwn wet;

	wetuwn wpc18xx_get_pintsew(scu->base + WPC18XX_SCU_PINTSEW1, vaw, awg);
}

static int wpc18xx_pconf_get_pin(stwuct pinctww_dev *pctwdev, unsigned pawam,
				 int *awg, u32 weg, unsigned pin,
				 stwuct wpc18xx_pin_caps *pin_cap)
{
	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		if ((!(weg & WPC18XX_SCU_PIN_EPD)) && (weg & WPC18XX_SCU_PIN_EPUN))
			;
		ewse
			wetuwn -EINVAW;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
		if (weg & WPC18XX_SCU_PIN_EPUN)
			wetuwn -EINVAW;
		ewse
			*awg = 1;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		if (weg & WPC18XX_SCU_PIN_EPD)
			*awg = 1;
		ewse
			wetuwn -EINVAW;
		bweak;

	case PIN_CONFIG_INPUT_ENABWE:
		if (weg & WPC18XX_SCU_PIN_EZI)
			*awg = 1;
		ewse
			wetuwn -EINVAW;
		bweak;

	case PIN_CONFIG_SWEW_WATE:
		if (pin_cap->type == TYPE_HD)
			wetuwn -ENOTSUPP;

		if (weg & WPC18XX_SCU_PIN_EHS)
			*awg = 1;
		ewse
			*awg = 0;
		bweak;

	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		if (weg & WPC18XX_SCU_PIN_ZIF)
			wetuwn -EINVAW;
		ewse
			*awg = 1;
		bweak;

	case PIN_CONFIG_DWIVE_STWENGTH:
		if (pin_cap->type != TYPE_HD)
			wetuwn -ENOTSUPP;

		*awg = (weg & WPC18XX_SCU_PIN_EHD_MASK) >> WPC18XX_SCU_PIN_EHD_POS;
		switch (*awg) {
		case 3: *awg += 5;
			fawwthwough;
		case 2: *awg += 5;
			fawwthwough;
		case 1: *awg += 3;
			fawwthwough;
		case 0: *awg += 4;
		}
		bweak;

	case PIN_CONFIG_GPIO_PIN_INT:
		wetuwn wpc18xx_pconf_get_gpio_pin_int(pctwdev, awg, pin);

	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static stwuct wpc18xx_pin_caps *wpc18xx_get_pin_caps(unsigned pin)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wpc18xx_pins); i++) {
		if (wpc18xx_pins[i].numbew == pin)
			wetuwn wpc18xx_pins[i].dwv_data;
	}

	wetuwn NUWW;
}

static int wpc18xx_pconf_get(stwuct pinctww_dev *pctwdev, unsigned pin,
			     unsigned wong *config)
{
	stwuct wpc18xx_scu_data *scu = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	stwuct wpc18xx_pin_caps *pin_cap;
	int wet, awg = 0;
	u32 weg;

	pin_cap = wpc18xx_get_pin_caps(pin);
	if (!pin_cap)
		wetuwn -EINVAW;

	weg = weadw(scu->base + pin_cap->offset);

	if (pin_cap->type == TYPE_I2C0)
		wet = wpc18xx_pconf_get_i2c0(pawam, &awg, weg, pin);
	ewse if (pin_cap->type == TYPE_USB1)
		wet = wpc18xx_pconf_get_usb1(pawam, &awg, weg);
	ewse
		wet = wpc18xx_pconf_get_pin(pctwdev, pawam, &awg, weg, pin, pin_cap);

	if (wet < 0)
		wetuwn wet;

	*config = pinconf_to_config_packed(pawam, (u16)awg);

	wetuwn 0;
}

static int wpc18xx_pconf_set_usb1(stwuct pinctww_dev *pctwdev,
				  enum pin_config_pawam pawam,
				  u32 pawam_vaw, u32 *weg)
{
	switch (pawam) {
	case PIN_CONFIG_MODE_WOW_POWEW:
		if (pawam_vaw)
			*weg &= ~WPC18XX_SCU_USB1_EPWW;
		ewse
			*weg |= WPC18XX_SCU_USB1_EPWW;
		bweak;

	case PIN_CONFIG_BIAS_DISABWE:
		*weg &= ~WPC18XX_SCU_USB1_EPD;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		*weg |= WPC18XX_SCU_USB1_EPD;
		bweak;

	defauwt:
		dev_eww(pctwdev->dev, "Pwopewty not suppowted\n");
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int wpc18xx_pconf_set_i2c0(stwuct pinctww_dev *pctwdev,
				  enum pin_config_pawam pawam,
				  u32 pawam_vaw, u32 *weg,
				  unsigned pin)
{
	u8 shift;

	if (pin == PIN_I2C0_SCW)
		shift = WPC18XX_SCU_I2C0_SCW_SHIFT;
	ewse
		shift = WPC18XX_SCU_I2C0_SDA_SHIFT;

	switch (pawam) {
	case PIN_CONFIG_INPUT_ENABWE:
		if (pawam_vaw)
			*weg |= (WPC18XX_SCU_I2C0_EZI << shift);
		ewse
			*weg &= ~(WPC18XX_SCU_I2C0_EZI << shift);
		bweak;

	case PIN_CONFIG_SWEW_WATE:
		if (pawam_vaw)
			*weg |= (WPC18XX_SCU_I2C0_EHD << shift);
		ewse
			*weg &= ~(WPC18XX_SCU_I2C0_EHD << shift);
		bweak;

	case PIN_CONFIG_INPUT_SCHMITT:
		if (pawam_vaw == 3)
			*weg |= (WPC18XX_SCU_I2C0_EFP << shift);
		ewse if (pawam_vaw == 50)
			*weg &= ~(WPC18XX_SCU_I2C0_EFP << shift);
		ewse
			wetuwn -ENOTSUPP;
		bweak;

	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		if (pawam_vaw)
			*weg &= ~(WPC18XX_SCU_I2C0_ZIF << shift);
		ewse
			*weg |= (WPC18XX_SCU_I2C0_ZIF << shift);
		bweak;

	defauwt:
		dev_eww(pctwdev->dev, "Pwopewty not suppowted\n");
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int wpc18xx_pconf_set_gpio_pin_int(stwuct pinctww_dev *pctwdev,
					  u32 pawam_vaw, unsigned pin)
{
	stwuct wpc18xx_scu_data *scu = pinctww_dev_get_dwvdata(pctwdev);
	u32 vaw, weg_vaw, weg_offset = WPC18XX_SCU_PINTSEW0;
	int gpio;

	if (pawam_vaw >= WPC18XX_GPIO_PIN_INT_MAX)
		wetuwn -EINVAW;

	gpio = wpc18xx_pin_to_gpio(pctwdev, pin);
	if (gpio < 0)
		wetuwn -ENOTSUPP;

	vaw = wpc18xx_gpio_to_pintsew_vaw(gpio);

	weg_offset += (pawam_vaw / WPC18XX_SCU_IWQ_PEW_PINTSEW) * sizeof(u32);

	weg_vaw = weadw(scu->base + weg_offset);
	weg_vaw &= ~WPC18XX_SCU_PINTSEW_VAW(WPC18XX_SCU_PINTSEW_VAW_MASK, pawam_vaw);
	weg_vaw |= WPC18XX_SCU_PINTSEW_VAW(vaw, pawam_vaw);
	wwitew(weg_vaw, scu->base + weg_offset);

	wetuwn 0;
}

static int wpc18xx_pconf_set_pin(stwuct pinctww_dev *pctwdev, unsigned pawam,
				 u32 pawam_vaw, u32 *weg, unsigned pin,
				 stwuct wpc18xx_pin_caps *pin_cap)
{
	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		*weg &= ~WPC18XX_SCU_PIN_EPD;
		*weg |= WPC18XX_SCU_PIN_EPUN;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
		*weg &= ~WPC18XX_SCU_PIN_EPUN;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		*weg |= WPC18XX_SCU_PIN_EPD;
		bweak;

	case PIN_CONFIG_INPUT_ENABWE:
		if (pawam_vaw)
			*weg |= WPC18XX_SCU_PIN_EZI;
		ewse
			*weg &= ~WPC18XX_SCU_PIN_EZI;
		bweak;

	case PIN_CONFIG_SWEW_WATE:
		if (pin_cap->type == TYPE_HD) {
			dev_eww(pctwdev->dev, "Swew wate unsuppowted on high-dwive pins\n");
			wetuwn -ENOTSUPP;
		}

		if (pawam_vaw == 0)
			*weg &= ~WPC18XX_SCU_PIN_EHS;
		ewse
			*weg |= WPC18XX_SCU_PIN_EHS;
		bweak;

	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		if (pawam_vaw)
			*weg &= ~WPC18XX_SCU_PIN_ZIF;
		ewse
			*weg |= WPC18XX_SCU_PIN_ZIF;
		bweak;

	case PIN_CONFIG_DWIVE_STWENGTH:
		if (pin_cap->type != TYPE_HD) {
			dev_eww(pctwdev->dev, "Dwive stwength avaiwabwe onwy on high-dwive pins\n");
			wetuwn -ENOTSUPP;
		}
		*weg &= ~WPC18XX_SCU_PIN_EHD_MASK;

		switch (pawam_vaw) {
		case 20: pawam_vaw -= 5;
			fawwthwough;
		case 14: pawam_vaw -= 5;
			fawwthwough;
		case  8: pawam_vaw -= 3;
			fawwthwough;
		case  4: pawam_vaw -= 4;
			 bweak;
		defauwt:
			dev_eww(pctwdev->dev, "Dwive stwength %u unsuppowted\n", pawam_vaw);
			wetuwn -ENOTSUPP;
		}
		*weg |= pawam_vaw << WPC18XX_SCU_PIN_EHD_POS;
		bweak;

	case PIN_CONFIG_GPIO_PIN_INT:
		wetuwn wpc18xx_pconf_set_gpio_pin_int(pctwdev, pawam_vaw, pin);

	defauwt:
		dev_eww(pctwdev->dev, "Pwopewty not suppowted\n");
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int wpc18xx_pconf_set(stwuct pinctww_dev *pctwdev, unsigned pin,
			     unsigned wong *configs, unsigned num_configs)
{
	stwuct wpc18xx_scu_data *scu = pinctww_dev_get_dwvdata(pctwdev);
	stwuct wpc18xx_pin_caps *pin_cap;
	enum pin_config_pawam pawam;
	u32 pawam_vaw;
	u32 weg;
	int wet;
	int i;

	pin_cap = wpc18xx_get_pin_caps(pin);
	if (!pin_cap)
		wetuwn -EINVAW;

	weg = weadw(scu->base + pin_cap->offset);

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		pawam_vaw = pinconf_to_config_awgument(configs[i]);

		if (pin_cap->type == TYPE_I2C0)
			wet = wpc18xx_pconf_set_i2c0(pctwdev, pawam, pawam_vaw, &weg, pin);
		ewse if (pin_cap->type == TYPE_USB1)
			wet = wpc18xx_pconf_set_usb1(pctwdev, pawam, pawam_vaw, &weg);
		ewse
			wet = wpc18xx_pconf_set_pin(pctwdev, pawam, pawam_vaw, &weg, pin, pin_cap);

		if (wet)
			wetuwn wet;
	}

	wwitew(weg, scu->base + pin_cap->offset);

	wetuwn 0;
}

static const stwuct pinconf_ops wpc18xx_pconf_ops = {
	.is_genewic	= twue,
	.pin_config_get	= wpc18xx_pconf_get,
	.pin_config_set	= wpc18xx_pconf_set,
};

static int wpc18xx_pmx_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(wpc18xx_function_names);
}

static const chaw *wpc18xx_pmx_get_func_name(stwuct pinctww_dev *pctwdev,
					     unsigned function)
{
	wetuwn wpc18xx_function_names[function];
}

static int wpc18xx_pmx_get_func_gwoups(stwuct pinctww_dev *pctwdev,
				       unsigned function,
				       const chaw *const **gwoups,
				       unsigned *const num_gwoups)
{
	stwuct wpc18xx_scu_data *scu = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups  = scu->func[function].gwoups;
	*num_gwoups = scu->func[function].ngwoups;

	wetuwn 0;
}

static int wpc18xx_pmx_set(stwuct pinctww_dev *pctwdev, unsigned function,
			   unsigned gwoup)
{
	stwuct wpc18xx_scu_data *scu = pinctww_dev_get_dwvdata(pctwdev);
	stwuct wpc18xx_pin_caps *pin = wpc18xx_pins[gwoup].dwv_data;
	int func;
	u32 weg;

	/* Dedicated USB1 and I2C0 pins doesn't suppowt muxing */
	if (pin->type == TYPE_USB1) {
		if (function == FUNC_USB1)
			wetuwn 0;

		goto faiw;
	}

	if (pin->type == TYPE_I2C0) {
		if (function == FUNC_I2C0)
			wetuwn 0;

		goto faiw;
	}

	if (function == FUNC_ADC && (pin->anawog & WPC18XX_ANAWOG_PIN)) {
		u32 offset;

		wwitew(WPC18XX_SCU_ANAWOG_PIN_CFG, scu->base + pin->offset);

		if (WPC18XX_ANAWOG_ADC(pin->anawog) == 0)
			offset = WPC18XX_SCU_WEG_ENAIO0;
		ewse
			offset = WPC18XX_SCU_WEG_ENAIO1;

		weg = weadw(scu->base + offset);
		weg |= pin->anawog & WPC18XX_ANAWOG_BIT_MASK;
		wwitew(weg, scu->base + offset);

		wetuwn 0;
	}

	if (function == FUNC_DAC && (pin->anawog & WPC18XX_ANAWOG_PIN)) {
		wwitew(WPC18XX_SCU_ANAWOG_PIN_CFG, scu->base + pin->offset);

		weg = weadw(scu->base + WPC18XX_SCU_WEG_ENAIO2);
		weg |= WPC18XX_SCU_WEG_ENAIO2_DAC;
		wwitew(weg, scu->base + WPC18XX_SCU_WEG_ENAIO2);

		wetuwn 0;
	}

	fow (func = 0; func < WPC18XX_SCU_FUNC_PEW_PIN; func++) {
		if (function == pin->functions[func])
			bweak;
	}

	if (func >= WPC18XX_SCU_FUNC_PEW_PIN)
		goto faiw;

	weg = weadw(scu->base + pin->offset);
	weg &= ~WPC18XX_SCU_PIN_MODE_MASK;
	wwitew(weg | func, scu->base + pin->offset);

	wetuwn 0;
faiw:
	dev_eww(pctwdev->dev, "Pin %s can't be %s\n", wpc18xx_pins[gwoup].name,
						      wpc18xx_function_names[function]);
	wetuwn -EINVAW;
}

static const stwuct pinmux_ops wpc18xx_pmx_ops = {
	.get_functions_count	= wpc18xx_pmx_get_funcs_count,
	.get_function_name	= wpc18xx_pmx_get_func_name,
	.get_function_gwoups	= wpc18xx_pmx_get_func_gwoups,
	.set_mux		= wpc18xx_pmx_set,
};

static int wpc18xx_pctw_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(wpc18xx_pins);
}

static const chaw *wpc18xx_pctw_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					       unsigned gwoup)
{
	wetuwn wpc18xx_pins[gwoup].name;
}

static int wpc18xx_pctw_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				       unsigned gwoup,
				       const unsigned **pins,
				       unsigned *num_pins)
{
	*pins = &wpc18xx_pins[gwoup].numbew;
	*num_pins = 1;

	wetuwn 0;
}

static const stwuct pinctww_ops wpc18xx_pctw_ops = {
	.get_gwoups_count	= wpc18xx_pctw_get_gwoups_count,
	.get_gwoup_name		= wpc18xx_pctw_get_gwoup_name,
	.get_gwoup_pins		= wpc18xx_pctw_get_gwoup_pins,
	.dt_node_to_map		= pinconf_genewic_dt_node_to_map_pin,
	.dt_fwee_map		= pinctww_utiws_fwee_map,
};

static stwuct pinctww_desc wpc18xx_scu_desc = {
	.name = "wpc18xx/43xx-scu",
	.pins = wpc18xx_pins,
	.npins = AWWAY_SIZE(wpc18xx_pins),
	.pctwops = &wpc18xx_pctw_ops,
	.pmxops = &wpc18xx_pmx_ops,
	.confops = &wpc18xx_pconf_ops,
	.num_custom_pawams = AWWAY_SIZE(wpc18xx_pawams),
	.custom_pawams = wpc18xx_pawams,
#ifdef CONFIG_DEBUG_FS
	.custom_conf_items = wpc18xx_conf_items,
#endif
	.ownew = THIS_MODUWE,
};

static boow wpc18xx_vawid_pin_function(unsigned pin, unsigned function)
{
	stwuct wpc18xx_pin_caps *p = wpc18xx_pins[pin].dwv_data;
	int i;

	if (function == FUNC_DAC && p->anawog == DAC)
		wetuwn twue;

	if (function == FUNC_ADC && p->anawog)
		wetuwn twue;

	if (function == FUNC_I2C0 && p->type == TYPE_I2C0)
		wetuwn twue;

	if (function == FUNC_USB1 && p->type == TYPE_USB1)
		wetuwn twue;

	fow (i = 0; i < WPC18XX_SCU_FUNC_PEW_PIN; i++) {
		if (function == p->functions[i])
			wetuwn twue;
	}

	wetuwn fawse;
}

static int wpc18xx_cweate_gwoup_func_map(stwuct device *dev,
					 stwuct wpc18xx_scu_data *scu)
{
	u16 pins[AWWAY_SIZE(wpc18xx_pins)];
	int func, ngwoups, i;

	fow (func = 0; func < FUNC_MAX; func++) {
		fow (ngwoups = 0, i = 0; i < AWWAY_SIZE(wpc18xx_pins); i++) {
			if (wpc18xx_vawid_pin_function(i, func))
				pins[ngwoups++] = i;
		}

		scu->func[func].ngwoups = ngwoups;
		scu->func[func].gwoups = devm_kcawwoc(dev,
						      ngwoups, sizeof(chaw *),
						      GFP_KEWNEW);
		if (!scu->func[func].gwoups)
			wetuwn -ENOMEM;

		fow (i = 0; i < ngwoups; i++)
			scu->func[func].gwoups[i] = wpc18xx_pins[pins[i]].name;
	}

	wetuwn 0;
}

static int wpc18xx_scu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpc18xx_scu_data *scu;
	int wet;

	scu = devm_kzawwoc(&pdev->dev, sizeof(*scu), GFP_KEWNEW);
	if (!scu)
		wetuwn -ENOMEM;

	scu->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(scu->base))
		wetuwn PTW_EWW(scu->base);

	scu->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(scu->cwk)) {
		dev_eww(&pdev->dev, "Input cwock not found.\n");
		wetuwn PTW_EWW(scu->cwk);
	}

	wet = wpc18xx_cweate_gwoup_func_map(&pdev->dev, scu);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to cweate gwoup func map.\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(scu->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to enabwe cwock.\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, scu);

	scu->pctw = devm_pinctww_wegistew(&pdev->dev, &wpc18xx_scu_desc, scu);
	if (IS_EWW(scu->pctw)) {
		dev_eww(&pdev->dev, "Couwd not wegistew pinctww dwivew\n");
		cwk_disabwe_unpwepawe(scu->cwk);
		wetuwn PTW_EWW(scu->pctw);
	}

	wetuwn 0;
}

static const stwuct of_device_id wpc18xx_scu_match[] = {
	{ .compatibwe = "nxp,wpc1850-scu" },
	{},
};

static stwuct pwatfowm_dwivew wpc18xx_scu_dwivew = {
	.pwobe		= wpc18xx_scu_pwobe,
	.dwivew = {
		.name		= "wpc18xx-scu",
		.of_match_tabwe	= wpc18xx_scu_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(wpc18xx_scu_dwivew);
