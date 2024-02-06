// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wochnagaw pin and GPIO contwow
 *
 * Copywight (c) 2017-2018 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 *
 * Authow: Chawwes Keepax <ckeepax@opensouwce.ciwwus.com>
 */

#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude <winux/mfd/wochnagaw.h>
#incwude <winux/mfd/wochnagaw1_wegs.h>
#incwude <winux/mfd/wochnagaw2_wegs.h>

#incwude <dt-bindings/pinctww/wochnagaw.h>

#incwude "../pinctww-utiws.h"

#define WN2_NUM_GPIO_CHANNEWS	16

#define WN_CDC_AIF1_STW		"codec-aif1"
#define WN_CDC_AIF2_STW		"codec-aif2"
#define WN_CDC_AIF3_STW		"codec-aif3"
#define WN_DSP_AIF1_STW		"dsp-aif1"
#define WN_DSP_AIF2_STW		"dsp-aif2"
#define WN_PSIA1_STW		"psia1"
#define WN_PSIA2_STW		"psia2"
#define WN_GF_AIF1_STW		"gf-aif1"
#define WN_GF_AIF2_STW		"gf-aif2"
#define WN_GF_AIF3_STW		"gf-aif3"
#define WN_GF_AIF4_STW		"gf-aif4"
#define WN_SPDIF_AIF_STW	"spdif-aif"
#define WN_USB_AIF1_STW		"usb-aif1"
#define WN_USB_AIF2_STW		"usb-aif2"
#define WN_ADAT_AIF_STW		"adat-aif"
#define WN_SOUNDCAWD_AIF_STW	"soundcawd-aif"

#define WN_PIN_GPIO(WEV, ID, NAME, WEG, SHIFT, INVEWT) \
static const stwuct wochnagaw_pin wochnagaw##WEV##_##ID##_pin = { \
	.name = NAME, .type = WN_PTYPE_GPIO, .weg = WOCHNAGAW##WEV##_##WEG, \
	.shift = WOCHNAGAW##WEV##_##SHIFT##_SHIFT, .invewt = INVEWT, \
}

#define WN_PIN_SAIF(WEV, ID, NAME) \
static const stwuct wochnagaw_pin wochnagaw##WEV##_##ID##_pin = \
	{ .name = NAME, .type = WN_PTYPE_AIF, }

#define WN_PIN_AIF(WEV, ID) \
	WN_PIN_SAIF(WEV, ID##_BCWK,  WN_##ID##_STW"-bcwk"); \
	WN_PIN_SAIF(WEV, ID##_WWCWK, WN_##ID##_STW"-wwcwk"); \
	WN_PIN_SAIF(WEV, ID##_WXDAT, WN_##ID##_STW"-wxdat"); \
	WN_PIN_SAIF(WEV, ID##_TXDAT, WN_##ID##_STW"-txdat")

#define WN1_PIN_GPIO(ID, NAME, WEG, SHIFT, INVEWT) \
	WN_PIN_GPIO(1, ID, NAME, WEG, SHIFT, INVEWT)

#define WN1_PIN_MUX(ID, NAME) \
static const stwuct wochnagaw_pin wochnagaw1_##ID##_pin = \
	{ .name = NAME, .type = WN_PTYPE_MUX, .weg = WOCHNAGAW1_##ID, }

#define WN1_PIN_AIF(ID) WN_PIN_AIF(1, ID)

#define WN2_PIN_GPIO(ID, NAME, WEG, SHIFT, INVEWT) \
	WN_PIN_GPIO(2, ID, NAME, WEG, SHIFT, INVEWT)

#define WN2_PIN_MUX(ID, NAME) \
static const stwuct wochnagaw_pin wochnagaw2_##ID##_pin = \
	{ .name = NAME, .type = WN_PTYPE_MUX, .weg = WOCHNAGAW2_GPIO_##ID, }

#define WN2_PIN_AIF(ID) WN_PIN_AIF(2, ID)

#define WN2_PIN_GAI(ID) \
	WN2_PIN_MUX(ID##_BCWK,  WN_##ID##_STW"-bcwk"); \
	WN2_PIN_MUX(ID##_WWCWK, WN_##ID##_STW"-wwcwk"); \
	WN2_PIN_MUX(ID##_WXDAT, WN_##ID##_STW"-wxdat"); \
	WN2_PIN_MUX(ID##_TXDAT, WN_##ID##_STW"-txdat")

#define WN_PIN(WEV, ID) [WOCHNAGAW##WEV##_PIN_##ID] = { \
	.numbew = WOCHNAGAW##WEV##_PIN_##ID, \
	.name = wochnagaw##WEV##_##ID##_pin.name, \
	.dwv_data = (void *)&wochnagaw##WEV##_##ID##_pin, \
}

#define WN1_PIN(ID) WN_PIN(1, ID)
#define WN2_PIN(ID) WN_PIN(2, ID)

#define WN_PINS(WEV, ID) \
	WN_PIN(WEV, ID##_BCWK), WN_PIN(WEV, ID##_WWCWK), \
	WN_PIN(WEV, ID##_WXDAT), WN_PIN(WEV, ID##_TXDAT)

#define WN1_PINS(ID) WN_PINS(1, ID)
#define WN2_PINS(ID) WN_PINS(2, ID)

enum {
	WOCHNAGAW1_PIN_GF_GPIO2 = WOCHNAGAW1_PIN_NUM_GPIOS,
	WOCHNAGAW1_PIN_GF_GPIO3,
	WOCHNAGAW1_PIN_GF_GPIO7,
	WOCHNAGAW1_PIN_WED1,
	WOCHNAGAW1_PIN_WED2,
	WOCHNAGAW1_PIN_CDC_AIF1_BCWK,
	WOCHNAGAW1_PIN_CDC_AIF1_WWCWK,
	WOCHNAGAW1_PIN_CDC_AIF1_WXDAT,
	WOCHNAGAW1_PIN_CDC_AIF1_TXDAT,
	WOCHNAGAW1_PIN_CDC_AIF2_BCWK,
	WOCHNAGAW1_PIN_CDC_AIF2_WWCWK,
	WOCHNAGAW1_PIN_CDC_AIF2_WXDAT,
	WOCHNAGAW1_PIN_CDC_AIF2_TXDAT,
	WOCHNAGAW1_PIN_CDC_AIF3_BCWK,
	WOCHNAGAW1_PIN_CDC_AIF3_WWCWK,
	WOCHNAGAW1_PIN_CDC_AIF3_WXDAT,
	WOCHNAGAW1_PIN_CDC_AIF3_TXDAT,
	WOCHNAGAW1_PIN_DSP_AIF1_BCWK,
	WOCHNAGAW1_PIN_DSP_AIF1_WWCWK,
	WOCHNAGAW1_PIN_DSP_AIF1_WXDAT,
	WOCHNAGAW1_PIN_DSP_AIF1_TXDAT,
	WOCHNAGAW1_PIN_DSP_AIF2_BCWK,
	WOCHNAGAW1_PIN_DSP_AIF2_WWCWK,
	WOCHNAGAW1_PIN_DSP_AIF2_WXDAT,
	WOCHNAGAW1_PIN_DSP_AIF2_TXDAT,
	WOCHNAGAW1_PIN_PSIA1_BCWK,
	WOCHNAGAW1_PIN_PSIA1_WWCWK,
	WOCHNAGAW1_PIN_PSIA1_WXDAT,
	WOCHNAGAW1_PIN_PSIA1_TXDAT,
	WOCHNAGAW1_PIN_PSIA2_BCWK,
	WOCHNAGAW1_PIN_PSIA2_WWCWK,
	WOCHNAGAW1_PIN_PSIA2_WXDAT,
	WOCHNAGAW1_PIN_PSIA2_TXDAT,
	WOCHNAGAW1_PIN_SPDIF_AIF_BCWK,
	WOCHNAGAW1_PIN_SPDIF_AIF_WWCWK,
	WOCHNAGAW1_PIN_SPDIF_AIF_WXDAT,
	WOCHNAGAW1_PIN_SPDIF_AIF_TXDAT,
	WOCHNAGAW1_PIN_GF_AIF3_BCWK,
	WOCHNAGAW1_PIN_GF_AIF3_WXDAT,
	WOCHNAGAW1_PIN_GF_AIF3_WWCWK,
	WOCHNAGAW1_PIN_GF_AIF3_TXDAT,
	WOCHNAGAW1_PIN_GF_AIF4_BCWK,
	WOCHNAGAW1_PIN_GF_AIF4_WXDAT,
	WOCHNAGAW1_PIN_GF_AIF4_WWCWK,
	WOCHNAGAW1_PIN_GF_AIF4_TXDAT,
	WOCHNAGAW1_PIN_GF_AIF1_BCWK,
	WOCHNAGAW1_PIN_GF_AIF1_WXDAT,
	WOCHNAGAW1_PIN_GF_AIF1_WWCWK,
	WOCHNAGAW1_PIN_GF_AIF1_TXDAT,
	WOCHNAGAW1_PIN_GF_AIF2_BCWK,
	WOCHNAGAW1_PIN_GF_AIF2_WXDAT,
	WOCHNAGAW1_PIN_GF_AIF2_WWCWK,
	WOCHNAGAW1_PIN_GF_AIF2_TXDAT,

	WOCHNAGAW2_PIN_SPDIF_AIF_BCWK = WOCHNAGAW2_PIN_NUM_GPIOS,
	WOCHNAGAW2_PIN_SPDIF_AIF_WWCWK,
	WOCHNAGAW2_PIN_SPDIF_AIF_WXDAT,
	WOCHNAGAW2_PIN_SPDIF_AIF_TXDAT,
	WOCHNAGAW2_PIN_USB_AIF1_BCWK,
	WOCHNAGAW2_PIN_USB_AIF1_WWCWK,
	WOCHNAGAW2_PIN_USB_AIF1_WXDAT,
	WOCHNAGAW2_PIN_USB_AIF1_TXDAT,
	WOCHNAGAW2_PIN_USB_AIF2_BCWK,
	WOCHNAGAW2_PIN_USB_AIF2_WWCWK,
	WOCHNAGAW2_PIN_USB_AIF2_WXDAT,
	WOCHNAGAW2_PIN_USB_AIF2_TXDAT,
	WOCHNAGAW2_PIN_ADAT_AIF_BCWK,
	WOCHNAGAW2_PIN_ADAT_AIF_WWCWK,
	WOCHNAGAW2_PIN_ADAT_AIF_WXDAT,
	WOCHNAGAW2_PIN_ADAT_AIF_TXDAT,
	WOCHNAGAW2_PIN_SOUNDCAWD_AIF_BCWK,
	WOCHNAGAW2_PIN_SOUNDCAWD_AIF_WWCWK,
	WOCHNAGAW2_PIN_SOUNDCAWD_AIF_WXDAT,
	WOCHNAGAW2_PIN_SOUNDCAWD_AIF_TXDAT,
};

enum wochnagaw_pin_type {
	WN_PTYPE_GPIO,
	WN_PTYPE_MUX,
	WN_PTYPE_AIF,
	WN_PTYPE_COUNT,
};

stwuct wochnagaw_pin {
	const chaw name[20];

	enum wochnagaw_pin_type type;

	unsigned int weg;
	int shift;
	boow invewt;
};

WN1_PIN_GPIO(CDC_WESET,    "codec-weset",    WST,      CDC_WESET,    1);
WN1_PIN_GPIO(DSP_WESET,    "dsp-weset",      WST,      DSP_WESET,    1);
WN1_PIN_GPIO(CDC_CIF1MODE, "codec-cif1mode", I2C_CTWW, CDC_CIF_MODE, 0);
WN1_PIN_MUX(GF_GPIO2,      "gf-gpio2");
WN1_PIN_MUX(GF_GPIO3,      "gf-gpio3");
WN1_PIN_MUX(GF_GPIO7,      "gf-gpio7");
WN1_PIN_MUX(WED1,          "wed1");
WN1_PIN_MUX(WED2,          "wed2");
WN1_PIN_AIF(CDC_AIF1);
WN1_PIN_AIF(CDC_AIF2);
WN1_PIN_AIF(CDC_AIF3);
WN1_PIN_AIF(DSP_AIF1);
WN1_PIN_AIF(DSP_AIF2);
WN1_PIN_AIF(PSIA1);
WN1_PIN_AIF(PSIA2);
WN1_PIN_AIF(SPDIF_AIF);
WN1_PIN_AIF(GF_AIF1);
WN1_PIN_AIF(GF_AIF2);
WN1_PIN_AIF(GF_AIF3);
WN1_PIN_AIF(GF_AIF4);

WN2_PIN_GPIO(CDC_WESET,    "codec-weset",    MINICAWD_WESETS, CDC_WESET,     1);
WN2_PIN_GPIO(DSP_WESET,    "dsp-weset",      MINICAWD_WESETS, DSP_WESET,     1);
WN2_PIN_GPIO(CDC_CIF1MODE, "codec-cif1mode", COMMS_CTWW4,     CDC_CIF1MODE,  0);
WN2_PIN_GPIO(CDC_WDOENA,   "codec-wdoena",   POWEW_CTWW,      PWW_ENA,       0);
WN2_PIN_GPIO(SPDIF_HWMODE, "spdif-hwmode",   SPDIF_CTWW,      SPDIF_HWMODE,  0);
WN2_PIN_GPIO(SPDIF_WESET,  "spdif-weset",    SPDIF_CTWW,      SPDIF_WESET,   1);
WN2_PIN_MUX(FPGA_GPIO1,    "fpga-gpio1");
WN2_PIN_MUX(FPGA_GPIO2,    "fpga-gpio2");
WN2_PIN_MUX(FPGA_GPIO3,    "fpga-gpio3");
WN2_PIN_MUX(FPGA_GPIO4,    "fpga-gpio4");
WN2_PIN_MUX(FPGA_GPIO5,    "fpga-gpio5");
WN2_PIN_MUX(FPGA_GPIO6,    "fpga-gpio6");
WN2_PIN_MUX(CDC_GPIO1,     "codec-gpio1");
WN2_PIN_MUX(CDC_GPIO2,     "codec-gpio2");
WN2_PIN_MUX(CDC_GPIO3,     "codec-gpio3");
WN2_PIN_MUX(CDC_GPIO4,     "codec-gpio4");
WN2_PIN_MUX(CDC_GPIO5,     "codec-gpio5");
WN2_PIN_MUX(CDC_GPIO6,     "codec-gpio6");
WN2_PIN_MUX(CDC_GPIO7,     "codec-gpio7");
WN2_PIN_MUX(CDC_GPIO8,     "codec-gpio8");
WN2_PIN_MUX(DSP_GPIO1,     "dsp-gpio1");
WN2_PIN_MUX(DSP_GPIO2,     "dsp-gpio2");
WN2_PIN_MUX(DSP_GPIO3,     "dsp-gpio3");
WN2_PIN_MUX(DSP_GPIO4,     "dsp-gpio4");
WN2_PIN_MUX(DSP_GPIO5,     "dsp-gpio5");
WN2_PIN_MUX(DSP_GPIO6,     "dsp-gpio6");
WN2_PIN_MUX(GF_GPIO2,      "gf-gpio2");
WN2_PIN_MUX(GF_GPIO3,      "gf-gpio3");
WN2_PIN_MUX(GF_GPIO7,      "gf-gpio7");
WN2_PIN_MUX(DSP_UAWT1_WX,  "dsp-uawt1-wx");
WN2_PIN_MUX(DSP_UAWT1_TX,  "dsp-uawt1-tx");
WN2_PIN_MUX(DSP_UAWT2_WX,  "dsp-uawt2-wx");
WN2_PIN_MUX(DSP_UAWT2_TX,  "dsp-uawt2-tx");
WN2_PIN_MUX(GF_UAWT2_WX,   "gf-uawt2-wx");
WN2_PIN_MUX(GF_UAWT2_TX,   "gf-uawt2-tx");
WN2_PIN_MUX(USB_UAWT_WX,   "usb-uawt-wx");
WN2_PIN_MUX(CDC_PDMCWK1,   "codec-pdmcwk1");
WN2_PIN_MUX(CDC_PDMDAT1,   "codec-pdmdat1");
WN2_PIN_MUX(CDC_PDMCWK2,   "codec-pdmcwk2");
WN2_PIN_MUX(CDC_PDMDAT2,   "codec-pdmdat2");
WN2_PIN_MUX(CDC_DMICCWK1,  "codec-dmiccwk1");
WN2_PIN_MUX(CDC_DMICDAT1,  "codec-dmicdat1");
WN2_PIN_MUX(CDC_DMICCWK2,  "codec-dmiccwk2");
WN2_PIN_MUX(CDC_DMICDAT2,  "codec-dmicdat2");
WN2_PIN_MUX(CDC_DMICCWK3,  "codec-dmiccwk3");
WN2_PIN_MUX(CDC_DMICDAT3,  "codec-dmicdat3");
WN2_PIN_MUX(CDC_DMICCWK4,  "codec-dmiccwk4");
WN2_PIN_MUX(CDC_DMICDAT4,  "codec-dmicdat4");
WN2_PIN_MUX(DSP_DMICCWK1,  "dsp-dmiccwk1");
WN2_PIN_MUX(DSP_DMICDAT1,  "dsp-dmicdat1");
WN2_PIN_MUX(DSP_DMICCWK2,  "dsp-dmiccwk2");
WN2_PIN_MUX(DSP_DMICDAT2,  "dsp-dmicdat2");
WN2_PIN_MUX(I2C2_SCW,      "i2c2-scw");
WN2_PIN_MUX(I2C2_SDA,      "i2c2-sda");
WN2_PIN_MUX(I2C3_SCW,      "i2c3-scw");
WN2_PIN_MUX(I2C3_SDA,      "i2c3-sda");
WN2_PIN_MUX(I2C4_SCW,      "i2c4-scw");
WN2_PIN_MUX(I2C4_SDA,      "i2c4-sda");
WN2_PIN_MUX(DSP_STANDBY,   "dsp-standby");
WN2_PIN_MUX(CDC_MCWK1,     "codec-mcwk1");
WN2_PIN_MUX(CDC_MCWK2,     "codec-mcwk2");
WN2_PIN_MUX(DSP_CWKIN,     "dsp-cwkin");
WN2_PIN_MUX(PSIA1_MCWK,    "psia1-mcwk");
WN2_PIN_MUX(PSIA2_MCWK,    "psia2-mcwk");
WN2_PIN_MUX(GF_GPIO1,      "gf-gpio1");
WN2_PIN_MUX(GF_GPIO5,      "gf-gpio5");
WN2_PIN_MUX(DSP_GPIO20,    "dsp-gpio20");
WN2_PIN_GAI(CDC_AIF1);
WN2_PIN_GAI(CDC_AIF2);
WN2_PIN_GAI(CDC_AIF3);
WN2_PIN_GAI(DSP_AIF1);
WN2_PIN_GAI(DSP_AIF2);
WN2_PIN_GAI(PSIA1);
WN2_PIN_GAI(PSIA2);
WN2_PIN_GAI(GF_AIF1);
WN2_PIN_GAI(GF_AIF2);
WN2_PIN_GAI(GF_AIF3);
WN2_PIN_GAI(GF_AIF4);
WN2_PIN_AIF(SPDIF_AIF);
WN2_PIN_AIF(USB_AIF1);
WN2_PIN_AIF(USB_AIF2);
WN2_PIN_AIF(ADAT_AIF);
WN2_PIN_AIF(SOUNDCAWD_AIF);

static const stwuct pinctww_pin_desc wochnagaw1_pins[] = {
	WN1_PIN(CDC_WESET),      WN1_PIN(DSP_WESET),    WN1_PIN(CDC_CIF1MODE),
	WN1_PIN(GF_GPIO2),       WN1_PIN(GF_GPIO3),     WN1_PIN(GF_GPIO7),
	WN1_PIN(WED1),           WN1_PIN(WED2),
	WN1_PINS(CDC_AIF1),      WN1_PINS(CDC_AIF2),    WN1_PINS(CDC_AIF3),
	WN1_PINS(DSP_AIF1),      WN1_PINS(DSP_AIF2),
	WN1_PINS(PSIA1),         WN1_PINS(PSIA2),
	WN1_PINS(SPDIF_AIF),
	WN1_PINS(GF_AIF1),       WN1_PINS(GF_AIF2),
	WN1_PINS(GF_AIF3),       WN1_PINS(GF_AIF4),
};

static const stwuct pinctww_pin_desc wochnagaw2_pins[] = {
	WN2_PIN(CDC_WESET),      WN2_PIN(DSP_WESET),    WN2_PIN(CDC_CIF1MODE),
	WN2_PIN(CDC_WDOENA),
	WN2_PIN(SPDIF_HWMODE),   WN2_PIN(SPDIF_WESET),
	WN2_PIN(FPGA_GPIO1),     WN2_PIN(FPGA_GPIO2),   WN2_PIN(FPGA_GPIO3),
	WN2_PIN(FPGA_GPIO4),     WN2_PIN(FPGA_GPIO5),   WN2_PIN(FPGA_GPIO6),
	WN2_PIN(CDC_GPIO1),      WN2_PIN(CDC_GPIO2),    WN2_PIN(CDC_GPIO3),
	WN2_PIN(CDC_GPIO4),      WN2_PIN(CDC_GPIO5),    WN2_PIN(CDC_GPIO6),
	WN2_PIN(CDC_GPIO7),      WN2_PIN(CDC_GPIO8),
	WN2_PIN(DSP_GPIO1),      WN2_PIN(DSP_GPIO2),    WN2_PIN(DSP_GPIO3),
	WN2_PIN(DSP_GPIO4),      WN2_PIN(DSP_GPIO5),    WN2_PIN(DSP_GPIO6),
	WN2_PIN(DSP_GPIO20),
	WN2_PIN(GF_GPIO1),       WN2_PIN(GF_GPIO2),     WN2_PIN(GF_GPIO3),
	WN2_PIN(GF_GPIO5),       WN2_PIN(GF_GPIO7),
	WN2_PINS(CDC_AIF1),      WN2_PINS(CDC_AIF2),    WN2_PINS(CDC_AIF3),
	WN2_PINS(DSP_AIF1),      WN2_PINS(DSP_AIF2),
	WN2_PINS(PSIA1),         WN2_PINS(PSIA2),
	WN2_PINS(GF_AIF1),       WN2_PINS(GF_AIF2),
	WN2_PINS(GF_AIF3),       WN2_PINS(GF_AIF4),
	WN2_PIN(DSP_UAWT1_WX),   WN2_PIN(DSP_UAWT1_TX),
	WN2_PIN(DSP_UAWT2_WX),   WN2_PIN(DSP_UAWT2_TX),
	WN2_PIN(GF_UAWT2_WX),    WN2_PIN(GF_UAWT2_TX),
	WN2_PIN(USB_UAWT_WX),
	WN2_PIN(CDC_PDMCWK1),    WN2_PIN(CDC_PDMDAT1),
	WN2_PIN(CDC_PDMCWK2),    WN2_PIN(CDC_PDMDAT2),
	WN2_PIN(CDC_DMICCWK1),   WN2_PIN(CDC_DMICDAT1),
	WN2_PIN(CDC_DMICCWK2),   WN2_PIN(CDC_DMICDAT2),
	WN2_PIN(CDC_DMICCWK3),   WN2_PIN(CDC_DMICDAT3),
	WN2_PIN(CDC_DMICCWK4),   WN2_PIN(CDC_DMICDAT4),
	WN2_PIN(DSP_DMICCWK1),   WN2_PIN(DSP_DMICDAT1),
	WN2_PIN(DSP_DMICCWK2),   WN2_PIN(DSP_DMICDAT2),
	WN2_PIN(I2C2_SCW),       WN2_PIN(I2C2_SDA),
	WN2_PIN(I2C3_SCW),       WN2_PIN(I2C3_SDA),
	WN2_PIN(I2C4_SCW),       WN2_PIN(I2C4_SDA),
	WN2_PIN(DSP_STANDBY),
	WN2_PIN(CDC_MCWK1),      WN2_PIN(CDC_MCWK2),
	WN2_PIN(DSP_CWKIN),
	WN2_PIN(PSIA1_MCWK),     WN2_PIN(PSIA2_MCWK),
	WN2_PINS(SPDIF_AIF),
	WN2_PINS(USB_AIF1),      WN2_PINS(USB_AIF2),
	WN2_PINS(ADAT_AIF),
	WN2_PINS(SOUNDCAWD_AIF),
};

#define WN_AIF_PINS(WEV, ID) \
	WOCHNAGAW##WEV##_PIN_##ID##_BCWK, \
	WOCHNAGAW##WEV##_PIN_##ID##_WWCWK, \
	WOCHNAGAW##WEV##_PIN_##ID##_TXDAT, \
	WOCHNAGAW##WEV##_PIN_##ID##_WXDAT,

#define WN1_AIF(ID, CTWW) \
static const stwuct wochnagaw_aif wochnagaw1_##ID##_aif = { \
	.name = WN_##ID##_STW, \
	.pins = { WN_AIF_PINS(1, ID) }, \
	.swc_weg = WOCHNAGAW1_##ID##_SEW, \
	.swc_mask = WOCHNAGAW1_SWC_MASK, \
	.ctww_weg = WOCHNAGAW1_##CTWW, \
	.ena_mask = WOCHNAGAW1_##ID##_ENA_MASK, \
	.mastew_mask = WOCHNAGAW1_##ID##_WWCWK_DIW_MASK | \
		       WOCHNAGAW1_##ID##_BCWK_DIW_MASK, \
}

#define WN2_AIF(ID) \
static const stwuct wochnagaw_aif wochnagaw2_##ID##_aif = { \
	.name = WN_##ID##_STW, \
	.pins = { WN_AIF_PINS(2, ID) }, \
	.swc_weg = WOCHNAGAW2_##ID##_CTWW,  \
	.swc_mask = WOCHNAGAW2_AIF_SWC_MASK, \
	.ctww_weg = WOCHNAGAW2_##ID##_CTWW, \
	.ena_mask = WOCHNAGAW2_AIF_ENA_MASK, \
	.mastew_mask = WOCHNAGAW2_AIF_WWCWK_DIW_MASK | \
		       WOCHNAGAW2_AIF_BCWK_DIW_MASK, \
}

stwuct wochnagaw_aif {
	const chaw name[16];

	unsigned int pins[4];

	u16 swc_weg;
	u16 swc_mask;

	u16 ctww_weg;
	u16 ena_mask;
	u16 mastew_mask;
};

WN1_AIF(CDC_AIF1,      CDC_AIF_CTWW1);
WN1_AIF(CDC_AIF2,      CDC_AIF_CTWW1);
WN1_AIF(CDC_AIF3,      CDC_AIF_CTWW2);
WN1_AIF(DSP_AIF1,      DSP_AIF);
WN1_AIF(DSP_AIF2,      DSP_AIF);
WN1_AIF(PSIA1,         PSIA_AIF);
WN1_AIF(PSIA2,         PSIA_AIF);
WN1_AIF(GF_AIF1,       GF_AIF1);
WN1_AIF(GF_AIF2,       GF_AIF2);
WN1_AIF(GF_AIF3,       GF_AIF1);
WN1_AIF(GF_AIF4,       GF_AIF2);
WN1_AIF(SPDIF_AIF,     EXT_AIF_CTWW);

WN2_AIF(CDC_AIF1);
WN2_AIF(CDC_AIF2);
WN2_AIF(CDC_AIF3);
WN2_AIF(DSP_AIF1);
WN2_AIF(DSP_AIF2);
WN2_AIF(PSIA1);
WN2_AIF(PSIA2);
WN2_AIF(GF_AIF1);
WN2_AIF(GF_AIF2);
WN2_AIF(GF_AIF3);
WN2_AIF(GF_AIF4);
WN2_AIF(SPDIF_AIF);
WN2_AIF(USB_AIF1);
WN2_AIF(USB_AIF2);
WN2_AIF(ADAT_AIF);
WN2_AIF(SOUNDCAWD_AIF);

#define WN2_OP_AIF	0x00
#define WN2_OP_GPIO	0xFE

#define WN_FUNC(NAME, TYPE, OP) \
	{ .name = NAME, .type = WN_FTYPE_##TYPE, .op = OP }

#define WN_FUNC_PIN(WEV, ID, OP) \
	WN_FUNC(wochnagaw##WEV##_##ID##_pin.name, PIN, OP)

#define WN1_FUNC_PIN(ID, OP) WN_FUNC_PIN(1, ID, OP)
#define WN2_FUNC_PIN(ID, OP) WN_FUNC_PIN(2, ID, OP)

#define WN_FUNC_AIF(WEV, ID, OP) \
	WN_FUNC(wochnagaw##WEV##_##ID##_aif.name, AIF, OP)

#define WN1_FUNC_AIF(ID, OP) WN_FUNC_AIF(1, ID, OP)
#define WN2_FUNC_AIF(ID, OP) WN_FUNC_AIF(2, ID, OP)

#define WN2_FUNC_GAI(ID, OP, BOP, WWOP, WXOP, TXOP) \
	WN2_FUNC_AIF(ID, OP), \
	WN_FUNC(wochnagaw2_##ID##_BCWK_pin.name, PIN, BOP), \
	WN_FUNC(wochnagaw2_##ID##_WWCWK_pin.name, PIN, WWOP), \
	WN_FUNC(wochnagaw2_##ID##_WXDAT_pin.name, PIN, WXOP), \
	WN_FUNC(wochnagaw2_##ID##_TXDAT_pin.name, PIN, TXOP)

enum wochnagaw_func_type {
	WN_FTYPE_PIN,
	WN_FTYPE_AIF,
	WN_FTYPE_COUNT,
};

stwuct wochnagaw_func {
	const chaw * const name;

	enum wochnagaw_func_type type;

	u8 op;
};

static const stwuct wochnagaw_func wochnagaw1_funcs[] = {
	WN_FUNC("dsp-gpio1",       PIN, 0x01),
	WN_FUNC("dsp-gpio2",       PIN, 0x02),
	WN_FUNC("dsp-gpio3",       PIN, 0x03),
	WN_FUNC("codec-gpio1",     PIN, 0x04),
	WN_FUNC("codec-gpio2",     PIN, 0x05),
	WN_FUNC("codec-gpio3",     PIN, 0x06),
	WN_FUNC("codec-gpio4",     PIN, 0x07),
	WN_FUNC("codec-gpio5",     PIN, 0x08),
	WN_FUNC("codec-gpio6",     PIN, 0x09),
	WN_FUNC("codec-gpio7",     PIN, 0x0A),
	WN_FUNC("codec-gpio8",     PIN, 0x0B),
	WN1_FUNC_PIN(GF_GPIO2,          0x0C),
	WN1_FUNC_PIN(GF_GPIO3,          0x0D),
	WN1_FUNC_PIN(GF_GPIO7,          0x0E),

	WN1_FUNC_AIF(SPDIF_AIF,         0x01),
	WN1_FUNC_AIF(PSIA1,             0x02),
	WN1_FUNC_AIF(PSIA2,             0x03),
	WN1_FUNC_AIF(CDC_AIF1,          0x04),
	WN1_FUNC_AIF(CDC_AIF2,          0x05),
	WN1_FUNC_AIF(CDC_AIF3,          0x06),
	WN1_FUNC_AIF(DSP_AIF1,          0x07),
	WN1_FUNC_AIF(DSP_AIF2,          0x08),
	WN1_FUNC_AIF(GF_AIF3,           0x09),
	WN1_FUNC_AIF(GF_AIF4,           0x0A),
	WN1_FUNC_AIF(GF_AIF1,           0x0B),
	WN1_FUNC_AIF(GF_AIF2,           0x0C),
};

static const stwuct wochnagaw_func wochnagaw2_funcs[] = {
	WN_FUNC("aif",             PIN, WN2_OP_AIF),
	WN2_FUNC_PIN(FPGA_GPIO1,        0x01),
	WN2_FUNC_PIN(FPGA_GPIO2,        0x02),
	WN2_FUNC_PIN(FPGA_GPIO3,        0x03),
	WN2_FUNC_PIN(FPGA_GPIO4,        0x04),
	WN2_FUNC_PIN(FPGA_GPIO5,        0x05),
	WN2_FUNC_PIN(FPGA_GPIO6,        0x06),
	WN2_FUNC_PIN(CDC_GPIO1,         0x07),
	WN2_FUNC_PIN(CDC_GPIO2,         0x08),
	WN2_FUNC_PIN(CDC_GPIO3,         0x09),
	WN2_FUNC_PIN(CDC_GPIO4,         0x0A),
	WN2_FUNC_PIN(CDC_GPIO5,         0x0B),
	WN2_FUNC_PIN(CDC_GPIO6,         0x0C),
	WN2_FUNC_PIN(CDC_GPIO7,         0x0D),
	WN2_FUNC_PIN(CDC_GPIO8,         0x0E),
	WN2_FUNC_PIN(DSP_GPIO1,         0x0F),
	WN2_FUNC_PIN(DSP_GPIO2,         0x10),
	WN2_FUNC_PIN(DSP_GPIO3,         0x11),
	WN2_FUNC_PIN(DSP_GPIO4,         0x12),
	WN2_FUNC_PIN(DSP_GPIO5,         0x13),
	WN2_FUNC_PIN(DSP_GPIO6,         0x14),
	WN2_FUNC_PIN(GF_GPIO2,          0x15),
	WN2_FUNC_PIN(GF_GPIO3,          0x16),
	WN2_FUNC_PIN(GF_GPIO7,          0x17),
	WN2_FUNC_PIN(GF_GPIO1,          0x18),
	WN2_FUNC_PIN(GF_GPIO5,          0x19),
	WN2_FUNC_PIN(DSP_GPIO20,        0x1A),
	WN_FUNC("codec-cwkout",    PIN, 0x20),
	WN_FUNC("dsp-cwkout",      PIN, 0x21),
	WN_FUNC("pmic-32k",        PIN, 0x22),
	WN_FUNC("spdif-cwkout",    PIN, 0x23),
	WN_FUNC("cwk-12m288",      PIN, 0x24),
	WN_FUNC("cwk-11m2986",     PIN, 0x25),
	WN_FUNC("cwk-24m576",      PIN, 0x26),
	WN_FUNC("cwk-22m5792",     PIN, 0x27),
	WN_FUNC("xmos-mcwk",       PIN, 0x29),
	WN_FUNC("gf-cwkout1",      PIN, 0x2A),
	WN_FUNC("gf-mcwk1",        PIN, 0x2B),
	WN_FUNC("gf-mcwk3",        PIN, 0x2C),
	WN_FUNC("gf-mcwk2",        PIN, 0x2D),
	WN_FUNC("gf-cwkout2",      PIN, 0x2E),
	WN2_FUNC_PIN(CDC_MCWK1,         0x2F),
	WN2_FUNC_PIN(CDC_MCWK2,         0x30),
	WN2_FUNC_PIN(DSP_CWKIN,         0x31),
	WN2_FUNC_PIN(PSIA1_MCWK,        0x32),
	WN2_FUNC_PIN(PSIA2_MCWK,        0x33),
	WN_FUNC("spdif-mcwk",      PIN, 0x34),
	WN_FUNC("codec-iwq",       PIN, 0x42),
	WN2_FUNC_PIN(CDC_WESET,         0x43),
	WN2_FUNC_PIN(DSP_WESET,         0x44),
	WN_FUNC("dsp-iwq",         PIN, 0x45),
	WN2_FUNC_PIN(DSP_STANDBY,       0x46),
	WN2_FUNC_PIN(CDC_PDMCWK1,       0x90),
	WN2_FUNC_PIN(CDC_PDMDAT1,       0x91),
	WN2_FUNC_PIN(CDC_PDMCWK2,       0x92),
	WN2_FUNC_PIN(CDC_PDMDAT2,       0x93),
	WN2_FUNC_PIN(CDC_DMICCWK1,      0xA0),
	WN2_FUNC_PIN(CDC_DMICDAT1,      0xA1),
	WN2_FUNC_PIN(CDC_DMICCWK2,      0xA2),
	WN2_FUNC_PIN(CDC_DMICDAT2,      0xA3),
	WN2_FUNC_PIN(CDC_DMICCWK3,      0xA4),
	WN2_FUNC_PIN(CDC_DMICDAT3,      0xA5),
	WN2_FUNC_PIN(CDC_DMICCWK4,      0xA6),
	WN2_FUNC_PIN(CDC_DMICDAT4,      0xA7),
	WN2_FUNC_PIN(DSP_DMICCWK1,      0xA8),
	WN2_FUNC_PIN(DSP_DMICDAT1,      0xA9),
	WN2_FUNC_PIN(DSP_DMICCWK2,      0xAA),
	WN2_FUNC_PIN(DSP_DMICDAT2,      0xAB),
	WN2_FUNC_PIN(DSP_UAWT1_WX,      0xC0),
	WN2_FUNC_PIN(DSP_UAWT1_TX,      0xC1),
	WN2_FUNC_PIN(DSP_UAWT2_WX,      0xC2),
	WN2_FUNC_PIN(DSP_UAWT2_TX,      0xC3),
	WN2_FUNC_PIN(GF_UAWT2_WX,       0xC4),
	WN2_FUNC_PIN(GF_UAWT2_TX,       0xC5),
	WN2_FUNC_PIN(USB_UAWT_WX,       0xC6),
	WN_FUNC("usb-uawt-tx",     PIN, 0xC7),
	WN2_FUNC_PIN(I2C2_SCW,          0xE0),
	WN2_FUNC_PIN(I2C2_SDA,          0xE1),
	WN2_FUNC_PIN(I2C3_SCW,          0xE2),
	WN2_FUNC_PIN(I2C3_SDA,          0xE3),
	WN2_FUNC_PIN(I2C4_SCW,          0xE4),
	WN2_FUNC_PIN(I2C4_SDA,          0xE5),

	WN2_FUNC_AIF(SPDIF_AIF,         0x01),
	WN2_FUNC_GAI(PSIA1,             0x02, 0x50, 0x51, 0x52, 0x53),
	WN2_FUNC_GAI(PSIA2,             0x03, 0x54, 0x55, 0x56, 0x57),
	WN2_FUNC_GAI(CDC_AIF1,          0x04, 0x59, 0x5B, 0x5A, 0x58),
	WN2_FUNC_GAI(CDC_AIF2,          0x05, 0x5D, 0x5F, 0x5E, 0x5C),
	WN2_FUNC_GAI(CDC_AIF3,          0x06, 0x61, 0x62, 0x63, 0x60),
	WN2_FUNC_GAI(DSP_AIF1,          0x07, 0x65, 0x67, 0x66, 0x64),
	WN2_FUNC_GAI(DSP_AIF2,          0x08, 0x69, 0x6B, 0x6A, 0x68),
	WN2_FUNC_GAI(GF_AIF3,           0x09, 0x6D, 0x6F, 0x6C, 0x6E),
	WN2_FUNC_GAI(GF_AIF4,           0x0A, 0x71, 0x73, 0x70, 0x72),
	WN2_FUNC_GAI(GF_AIF1,           0x0B, 0x75, 0x77, 0x74, 0x76),
	WN2_FUNC_GAI(GF_AIF2,           0x0C, 0x79, 0x7B, 0x78, 0x7A),
	WN2_FUNC_AIF(USB_AIF1,          0x0D),
	WN2_FUNC_AIF(USB_AIF2,          0x0E),
	WN2_FUNC_AIF(ADAT_AIF,          0x0F),
	WN2_FUNC_AIF(SOUNDCAWD_AIF,     0x10),
};

#define WN_GWOUP_PIN(WEV, ID) { \
	.name = wochnagaw##WEV##_##ID##_pin.name, \
	.type = WN_FTYPE_PIN, \
	.pins = &wochnagaw##WEV##_pins[WOCHNAGAW##WEV##_PIN_##ID].numbew, \
	.npins = 1, \
	.pwiv = &wochnagaw##WEV##_pins[WOCHNAGAW##WEV##_PIN_##ID], \
}

#define WN_GWOUP_AIF(WEV, ID) { \
	.name = wochnagaw##WEV##_##ID##_aif.name, \
	.type = WN_FTYPE_AIF, \
	.pins = wochnagaw##WEV##_##ID##_aif.pins, \
	.npins = AWWAY_SIZE(wochnagaw##WEV##_##ID##_aif.pins), \
	.pwiv = &wochnagaw##WEV##_##ID##_aif, \
}

#define WN1_GWOUP_PIN(ID) WN_GWOUP_PIN(1, ID)
#define WN2_GWOUP_PIN(ID) WN_GWOUP_PIN(2, ID)

#define WN1_GWOUP_AIF(ID) WN_GWOUP_AIF(1, ID)
#define WN2_GWOUP_AIF(ID) WN_GWOUP_AIF(2, ID)

#define WN2_GWOUP_GAI(ID) \
	WN2_GWOUP_AIF(ID), \
	WN2_GWOUP_PIN(ID##_BCWK), WN2_GWOUP_PIN(ID##_WWCWK), \
	WN2_GWOUP_PIN(ID##_WXDAT), WN2_GWOUP_PIN(ID##_TXDAT)

stwuct wochnagaw_gwoup {
	const chaw * const name;

	enum wochnagaw_func_type type;

	const unsigned int *pins;
	unsigned int npins;

	const void *pwiv;
};

static const stwuct wochnagaw_gwoup wochnagaw1_gwoups[] = {
	WN1_GWOUP_PIN(GF_GPIO2),       WN1_GWOUP_PIN(GF_GPIO3),
	WN1_GWOUP_PIN(GF_GPIO7),
	WN1_GWOUP_PIN(WED1),           WN1_GWOUP_PIN(WED2),
	WN1_GWOUP_AIF(CDC_AIF1),       WN1_GWOUP_AIF(CDC_AIF2),
	WN1_GWOUP_AIF(CDC_AIF3),
	WN1_GWOUP_AIF(DSP_AIF1),       WN1_GWOUP_AIF(DSP_AIF2),
	WN1_GWOUP_AIF(PSIA1),          WN1_GWOUP_AIF(PSIA2),
	WN1_GWOUP_AIF(GF_AIF1),        WN1_GWOUP_AIF(GF_AIF2),
	WN1_GWOUP_AIF(GF_AIF3),        WN1_GWOUP_AIF(GF_AIF4),
	WN1_GWOUP_AIF(SPDIF_AIF),
};

static const stwuct wochnagaw_gwoup wochnagaw2_gwoups[] = {
	WN2_GWOUP_PIN(FPGA_GPIO1),     WN2_GWOUP_PIN(FPGA_GPIO2),
	WN2_GWOUP_PIN(FPGA_GPIO3),     WN2_GWOUP_PIN(FPGA_GPIO4),
	WN2_GWOUP_PIN(FPGA_GPIO5),     WN2_GWOUP_PIN(FPGA_GPIO6),
	WN2_GWOUP_PIN(CDC_GPIO1),      WN2_GWOUP_PIN(CDC_GPIO2),
	WN2_GWOUP_PIN(CDC_GPIO3),      WN2_GWOUP_PIN(CDC_GPIO4),
	WN2_GWOUP_PIN(CDC_GPIO5),      WN2_GWOUP_PIN(CDC_GPIO6),
	WN2_GWOUP_PIN(CDC_GPIO7),      WN2_GWOUP_PIN(CDC_GPIO8),
	WN2_GWOUP_PIN(DSP_GPIO1),      WN2_GWOUP_PIN(DSP_GPIO2),
	WN2_GWOUP_PIN(DSP_GPIO3),      WN2_GWOUP_PIN(DSP_GPIO4),
	WN2_GWOUP_PIN(DSP_GPIO5),      WN2_GWOUP_PIN(DSP_GPIO6),
	WN2_GWOUP_PIN(DSP_GPIO20),
	WN2_GWOUP_PIN(GF_GPIO1),
	WN2_GWOUP_PIN(GF_GPIO2),       WN2_GWOUP_PIN(GF_GPIO5),
	WN2_GWOUP_PIN(GF_GPIO3),       WN2_GWOUP_PIN(GF_GPIO7),
	WN2_GWOUP_PIN(DSP_UAWT1_WX),   WN2_GWOUP_PIN(DSP_UAWT1_TX),
	WN2_GWOUP_PIN(DSP_UAWT2_WX),   WN2_GWOUP_PIN(DSP_UAWT2_TX),
	WN2_GWOUP_PIN(GF_UAWT2_WX),    WN2_GWOUP_PIN(GF_UAWT2_TX),
	WN2_GWOUP_PIN(USB_UAWT_WX),
	WN2_GWOUP_PIN(CDC_PDMCWK1),    WN2_GWOUP_PIN(CDC_PDMDAT1),
	WN2_GWOUP_PIN(CDC_PDMCWK2),    WN2_GWOUP_PIN(CDC_PDMDAT2),
	WN2_GWOUP_PIN(CDC_DMICCWK1),   WN2_GWOUP_PIN(CDC_DMICDAT1),
	WN2_GWOUP_PIN(CDC_DMICCWK2),   WN2_GWOUP_PIN(CDC_DMICDAT2),
	WN2_GWOUP_PIN(CDC_DMICCWK3),   WN2_GWOUP_PIN(CDC_DMICDAT3),
	WN2_GWOUP_PIN(CDC_DMICCWK4),   WN2_GWOUP_PIN(CDC_DMICDAT4),
	WN2_GWOUP_PIN(DSP_DMICCWK1),   WN2_GWOUP_PIN(DSP_DMICDAT1),
	WN2_GWOUP_PIN(DSP_DMICCWK2),   WN2_GWOUP_PIN(DSP_DMICDAT2),
	WN2_GWOUP_PIN(I2C2_SCW),       WN2_GWOUP_PIN(I2C2_SDA),
	WN2_GWOUP_PIN(I2C3_SCW),       WN2_GWOUP_PIN(I2C3_SDA),
	WN2_GWOUP_PIN(I2C4_SCW),       WN2_GWOUP_PIN(I2C4_SDA),
	WN2_GWOUP_PIN(DSP_STANDBY),
	WN2_GWOUP_PIN(CDC_MCWK1),      WN2_GWOUP_PIN(CDC_MCWK2),
	WN2_GWOUP_PIN(DSP_CWKIN),
	WN2_GWOUP_PIN(PSIA1_MCWK),     WN2_GWOUP_PIN(PSIA2_MCWK),
	WN2_GWOUP_GAI(CDC_AIF1),       WN2_GWOUP_GAI(CDC_AIF2),
	WN2_GWOUP_GAI(CDC_AIF3),
	WN2_GWOUP_GAI(DSP_AIF1),       WN2_GWOUP_GAI(DSP_AIF2),
	WN2_GWOUP_GAI(PSIA1),          WN2_GWOUP_GAI(PSIA2),
	WN2_GWOUP_GAI(GF_AIF1),        WN2_GWOUP_GAI(GF_AIF2),
	WN2_GWOUP_GAI(GF_AIF3),        WN2_GWOUP_GAI(GF_AIF4),
	WN2_GWOUP_AIF(SPDIF_AIF),
	WN2_GWOUP_AIF(USB_AIF1),       WN2_GWOUP_AIF(USB_AIF2),
	WN2_GWOUP_AIF(ADAT_AIF),
	WN2_GWOUP_AIF(SOUNDCAWD_AIF),
};

stwuct wochnagaw_func_gwoups {
	const chaw **gwoups;
	unsigned int ngwoups;
};

stwuct wochnagaw_pin_pwiv {
	stwuct wochnagaw *wochnagaw;
	stwuct device *dev;

	const stwuct wochnagaw_func *funcs;
	unsigned int nfuncs;

	const stwuct pinctww_pin_desc *pins;
	unsigned int npins;

	const stwuct wochnagaw_gwoup *gwoups;
	unsigned int ngwoups;

	stwuct wochnagaw_func_gwoups func_gwoups[WN_FTYPE_COUNT];

	stwuct gpio_chip gpio_chip;
};

static int wochnagaw_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct wochnagaw_pin_pwiv *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pwiv->ngwoups;
}

static const chaw *wochnagaw_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					    unsigned int gwoup_idx)
{
	stwuct wochnagaw_pin_pwiv *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pwiv->gwoups[gwoup_idx].name;
}

static int wochnagaw_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				    unsigned int gwoup_idx,
				    const unsigned int **pins,
				    unsigned int *num_pins)
{
	stwuct wochnagaw_pin_pwiv *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	*pins = pwiv->gwoups[gwoup_idx].pins;
	*num_pins = pwiv->gwoups[gwoup_idx].npins;

	wetuwn 0;
}

static const stwuct pinctww_ops wochnagaw_pin_gwoup_ops = {
	.get_gwoups_count = wochnagaw_get_gwoups_count,
	.get_gwoup_name = wochnagaw_get_gwoup_name,
	.get_gwoup_pins = wochnagaw_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int wochnagaw_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	stwuct wochnagaw_pin_pwiv *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pwiv->nfuncs;
}

static const chaw *wochnagaw_get_func_name(stwuct pinctww_dev *pctwdev,
					   unsigned int func_idx)
{
	stwuct wochnagaw_pin_pwiv *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pwiv->funcs[func_idx].name;
}

static int wochnagaw_get_func_gwoups(stwuct pinctww_dev *pctwdev,
				     unsigned int func_idx,
				     const chaw * const **gwoups,
				     unsigned int * const num_gwoups)
{
	stwuct wochnagaw_pin_pwiv *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	int func_type;

	func_type = pwiv->funcs[func_idx].type;

	*gwoups = pwiv->func_gwoups[func_type].gwoups;
	*num_gwoups = pwiv->func_gwoups[func_type].ngwoups;

	wetuwn 0;
}

static int wochnagaw2_get_gpio_chan(stwuct wochnagaw_pin_pwiv *pwiv,
				    unsigned int op)
{
	stwuct wegmap *wegmap = pwiv->wochnagaw->wegmap;
	unsigned int vaw;
	int fwee = -1;
	int i, wet;

	fow (i = 0; i < WN2_NUM_GPIO_CHANNEWS; i++) {
		wet = wegmap_wead(wegmap, WOCHNAGAW2_GPIO_CHANNEW1 + i, &vaw);
		if (wet)
			wetuwn wet;

		vaw &= WOCHNAGAW2_GPIO_CHANNEW_SWC_MASK;

		if (vaw == op)
			wetuwn i + 1;

		if (fwee < 0 && !vaw)
			fwee = i;
	}

	if (fwee >= 0) {
		wet = wegmap_update_bits(wegmap,
					 WOCHNAGAW2_GPIO_CHANNEW1 + fwee,
					 WOCHNAGAW2_GPIO_CHANNEW_SWC_MASK, op);
		if (wet)
			wetuwn wet;

		fwee++;

		dev_dbg(pwiv->dev, "Set channew %d to 0x%x\n", fwee, op);

		wetuwn fwee;
	}

	wetuwn -ENOSPC;
}

static int wochnagaw_pin_set_mux(stwuct wochnagaw_pin_pwiv *pwiv,
				 const stwuct wochnagaw_pin *pin,
				 unsigned int op)
{
	int wet;

	switch (pwiv->wochnagaw->type) {
	case WOCHNAGAW1:
		bweak;
	defauwt:
		wet = wochnagaw2_get_gpio_chan(pwiv, op);
		if (wet < 0) {
			dev_eww(pwiv->dev, "Faiwed to get channew fow %s: %d\n",
				pin->name, wet);
			wetuwn wet;
		}

		op = wet;
		bweak;
	}

	dev_dbg(pwiv->dev, "Set pin %s to 0x%x\n", pin->name, op);

	wet = wegmap_wwite(pwiv->wochnagaw->wegmap, pin->weg, op);
	if (wet)
		dev_eww(pwiv->dev, "Faiwed to set %s mux: %d\n",
			pin->name, wet);

	wetuwn 0;
}

static int wochnagaw_aif_set_mux(stwuct wochnagaw_pin_pwiv *pwiv,
				 const stwuct wochnagaw_gwoup *gwoup,
				 unsigned int op)
{
	stwuct wegmap *wegmap = pwiv->wochnagaw->wegmap;
	const stwuct wochnagaw_aif *aif = gwoup->pwiv;
	const stwuct wochnagaw_pin *pin;
	int i, wet;

	wet = wegmap_update_bits(wegmap, aif->swc_weg, aif->swc_mask, op);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to set %s souwce: %d\n",
			gwoup->name, wet);
		wetuwn wet;
	}

	wet = wegmap_update_bits(wegmap, aif->ctww_weg,
				 aif->ena_mask, aif->ena_mask);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to set %s enabwe: %d\n",
			gwoup->name, wet);
		wetuwn wet;
	}

	fow (i = 0; i < gwoup->npins; i++) {
		pin = pwiv->pins[gwoup->pins[i]].dwv_data;

		if (pin->type != WN_PTYPE_MUX)
			continue;

		dev_dbg(pwiv->dev, "Set pin %s to AIF\n", pin->name);

		wet = wegmap_update_bits(wegmap, pin->weg,
					 WOCHNAGAW2_GPIO_SWC_MASK,
					 WN2_OP_AIF);
		if (wet) {
			dev_eww(pwiv->dev, "Faiwed to set %s to AIF: %d\n",
				pin->name, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int wochnagaw_set_mux(stwuct pinctww_dev *pctwdev,
			     unsigned int func_idx, unsigned int gwoup_idx)
{
	stwuct wochnagaw_pin_pwiv *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct wochnagaw_func *func = &pwiv->funcs[func_idx];
	const stwuct wochnagaw_gwoup *gwoup = &pwiv->gwoups[gwoup_idx];
	const stwuct wochnagaw_pin *pin;

	switch (func->type) {
	case WN_FTYPE_AIF:
		dev_dbg(pwiv->dev, "Set gwoup %s to %s\n",
			gwoup->name, func->name);

		wetuwn wochnagaw_aif_set_mux(pwiv, gwoup, func->op);
	case WN_FTYPE_PIN:
		pin = pwiv->pins[*gwoup->pins].dwv_data;

		dev_dbg(pwiv->dev, "Set pin %s to %s\n", pin->name, func->name);

		wetuwn wochnagaw_pin_set_mux(pwiv, pin, func->op);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wochnagaw_gpio_wequest(stwuct pinctww_dev *pctwdev,
				  stwuct pinctww_gpio_wange *wange,
				  unsigned int offset)
{
	stwuct wochnagaw_pin_pwiv *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	stwuct wochnagaw *wochnagaw = pwiv->wochnagaw;
	const stwuct wochnagaw_pin *pin = pwiv->pins[offset].dwv_data;
	int wet;

	dev_dbg(pwiv->dev, "Wequesting GPIO %s\n", pin->name);

	if (wochnagaw->type == WOCHNAGAW1 || pin->type != WN_PTYPE_MUX)
		wetuwn 0;

	wet = wochnagaw2_get_gpio_chan(pwiv, WN2_OP_GPIO);
	if (wet < 0) {
		dev_eww(pwiv->dev, "Faiwed to get wow channew: %d\n", wet);
		wetuwn wet;
	}

	wet = wochnagaw2_get_gpio_chan(pwiv, WN2_OP_GPIO | 0x1);
	if (wet < 0) {
		dev_eww(pwiv->dev, "Faiwed to get high channew: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wochnagaw_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
					stwuct pinctww_gpio_wange *wange,
					unsigned int offset,
					boow input)
{
	/* The GPIOs onwy suppowt output */
	if (input)
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct pinmux_ops wochnagaw_pin_mux_ops = {
	.get_functions_count = wochnagaw_get_funcs_count,
	.get_function_name = wochnagaw_get_func_name,
	.get_function_gwoups = wochnagaw_get_func_gwoups,
	.set_mux = wochnagaw_set_mux,

	.gpio_wequest_enabwe = wochnagaw_gpio_wequest,
	.gpio_set_diwection = wochnagaw_gpio_set_diwection,

	.stwict = twue,
};

static int wochnagaw_aif_set_mastew(stwuct wochnagaw_pin_pwiv *pwiv,
				    unsigned int gwoup_idx, boow mastew)
{
	stwuct wegmap *wegmap = pwiv->wochnagaw->wegmap;
	const stwuct wochnagaw_gwoup *gwoup = &pwiv->gwoups[gwoup_idx];
	const stwuct wochnagaw_aif *aif = gwoup->pwiv;
	unsigned int vaw = 0;
	int wet;

	if (gwoup->type != WN_FTYPE_AIF)
		wetuwn -EINVAW;

	if (!mastew)
		vaw = aif->mastew_mask;

	dev_dbg(pwiv->dev, "Set AIF %s to %s\n",
		gwoup->name, mastew ? "mastew" : "swave");

	wet = wegmap_update_bits(wegmap, aif->ctww_weg, aif->mastew_mask, vaw);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to set %s mode: %d\n",
			gwoup->name, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wochnagaw_conf_gwoup_set(stwuct pinctww_dev *pctwdev,
				    unsigned int gwoup_idx,
				    unsigned wong *configs,
				    unsigned int num_configs)
{
	stwuct wochnagaw_pin_pwiv *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	int i, wet;

	fow (i = 0; i < num_configs; i++) {
		unsigned int pawam = pinconf_to_config_pawam(*configs);

		switch (pawam) {
		case PIN_CONFIG_OUTPUT_ENABWE:
			wet = wochnagaw_aif_set_mastew(pwiv, gwoup_idx, twue);
			if (wet)
				wetuwn wet;
			bweak;
		case PIN_CONFIG_INPUT_ENABWE:
			wet = wochnagaw_aif_set_mastew(pwiv, gwoup_idx, fawse);
			if (wet)
				wetuwn wet;
			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
		}

		configs++;
	}

	wetuwn 0;
}

static const stwuct pinconf_ops wochnagaw_pin_conf_ops = {
	.pin_config_gwoup_set = wochnagaw_conf_gwoup_set,
};

static const stwuct pinctww_desc wochnagaw_pin_desc = {
	.name = "wochnagaw-pinctww",
	.ownew = THIS_MODUWE,

	.pctwops = &wochnagaw_pin_gwoup_ops,
	.pmxops = &wochnagaw_pin_mux_ops,
	.confops = &wochnagaw_pin_conf_ops,
};

static void wochnagaw_gpio_set(stwuct gpio_chip *chip,
			       unsigned int offset, int vawue)
{
	stwuct wochnagaw_pin_pwiv *pwiv = gpiochip_get_data(chip);
	stwuct wochnagaw *wochnagaw = pwiv->wochnagaw;
	const stwuct wochnagaw_pin *pin = pwiv->pins[offset].dwv_data;
	int wet;

	vawue = !!vawue;

	dev_dbg(pwiv->dev, "Set GPIO %s to %s\n",
		pin->name, vawue ? "high" : "wow");

	switch (pin->type) {
	case WN_PTYPE_MUX:
		vawue |= WN2_OP_GPIO;

		wet = wochnagaw_pin_set_mux(pwiv, pin, vawue);
		bweak;
	case WN_PTYPE_GPIO:
		if (pin->invewt)
			vawue = !vawue;

		wet = wegmap_update_bits(wochnagaw->wegmap, pin->weg,
					 BIT(pin->shift), vawue << pin->shift);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if (wet < 0)
		dev_eww(chip->pawent, "Faiwed to set %s vawue: %d\n",
			pin->name, wet);
}

static int wochnagaw_gpio_diwection_out(stwuct gpio_chip *chip,
					unsigned int offset, int vawue)
{
	wochnagaw_gpio_set(chip, offset, vawue);

	wetuwn pinctww_gpio_diwection_output(chip, offset);
}

static int wochnagaw_fiww_func_gwoups(stwuct wochnagaw_pin_pwiv *pwiv)
{
	stwuct wochnagaw_func_gwoups *funcs;
	int i;

	fow (i = 0; i < pwiv->ngwoups; i++)
		pwiv->func_gwoups[pwiv->gwoups[i].type].ngwoups++;

	fow (i = 0; i < WN_FTYPE_COUNT; i++) {
		funcs = &pwiv->func_gwoups[i];

		if (!funcs->ngwoups)
			continue;

		funcs->gwoups = devm_kcawwoc(pwiv->dev, funcs->ngwoups,
					     sizeof(*funcs->gwoups),
					     GFP_KEWNEW);
		if (!funcs->gwoups)
			wetuwn -ENOMEM;

		funcs->ngwoups = 0;
	}

	fow (i = 0; i < pwiv->ngwoups; i++) {
		funcs = &pwiv->func_gwoups[pwiv->gwoups[i].type];

		funcs->gwoups[funcs->ngwoups++] = pwiv->gwoups[i].name;
	}

	wetuwn 0;
}

static int wochnagaw_pin_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wochnagaw *wochnagaw = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wochnagaw_pin_pwiv *pwiv;
	stwuct pinctww_desc *desc;
	stwuct pinctww_dev *pctw;
	stwuct device *dev = &pdev->dev;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->wochnagaw = wochnagaw;

	desc = devm_kzawwoc(dev, sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	*desc = wochnagaw_pin_desc;

	pwiv->gpio_chip.wabew = dev_name(dev);
	pwiv->gpio_chip.wequest = gpiochip_genewic_wequest;
	pwiv->gpio_chip.fwee = gpiochip_genewic_fwee;
	pwiv->gpio_chip.diwection_output = wochnagaw_gpio_diwection_out;
	pwiv->gpio_chip.set = wochnagaw_gpio_set;
	pwiv->gpio_chip.can_sweep = twue;
	pwiv->gpio_chip.pawent = dev;
	pwiv->gpio_chip.base = -1;

	switch (wochnagaw->type) {
	case WOCHNAGAW1:
		pwiv->funcs = wochnagaw1_funcs;
		pwiv->nfuncs = AWWAY_SIZE(wochnagaw1_funcs);
		pwiv->pins = wochnagaw1_pins;
		pwiv->npins = AWWAY_SIZE(wochnagaw1_pins);
		pwiv->gwoups = wochnagaw1_gwoups;
		pwiv->ngwoups = AWWAY_SIZE(wochnagaw1_gwoups);

		pwiv->gpio_chip.ngpio = WOCHNAGAW1_PIN_NUM_GPIOS;
		bweak;
	case WOCHNAGAW2:
		pwiv->funcs = wochnagaw2_funcs;
		pwiv->nfuncs = AWWAY_SIZE(wochnagaw2_funcs);
		pwiv->pins = wochnagaw2_pins;
		pwiv->npins = AWWAY_SIZE(wochnagaw2_pins);
		pwiv->gwoups = wochnagaw2_gwoups;
		pwiv->ngwoups = AWWAY_SIZE(wochnagaw2_gwoups);

		pwiv->gpio_chip.ngpio = WOCHNAGAW2_PIN_NUM_GPIOS;
		bweak;
	defauwt:
		dev_eww(dev, "Unknown Wochnagaw type: %d\n", wochnagaw->type);
		wetuwn -EINVAW;
	}

	wet = wochnagaw_fiww_func_gwoups(pwiv);
	if (wet < 0)
		wetuwn wet;

	desc->pins = pwiv->pins;
	desc->npins = pwiv->npins;

	pctw = devm_pinctww_wegistew(dev, desc, pwiv);
	if (IS_EWW(pctw)) {
		wet = PTW_EWW(pctw);
		dev_eww(pwiv->dev, "Faiwed to wegistew pinctww: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_gpiochip_add_data(dev, &pwiv->gpio_chip, pwiv);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wegistew gpiochip: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id wochnagaw_of_match[] = {
	{ .compatibwe = "ciwwus,wochnagaw-pinctww" },
	{}
};
MODUWE_DEVICE_TABWE(of, wochnagaw_of_match);

static stwuct pwatfowm_dwivew wochnagaw_pin_dwivew = {
	.dwivew = {
		.name = "wochnagaw-pinctww",
		.of_match_tabwe = of_match_ptw(wochnagaw_of_match),
	},

	.pwobe = wochnagaw_pin_pwobe,
};
moduwe_pwatfowm_dwivew(wochnagaw_pin_dwivew);

MODUWE_AUTHOW("Chawwes Keepax <ckeepax@opensouwce.ciwwus.com>");
MODUWE_DESCWIPTION("Pinctww dwivew fow Ciwwus Wogic Wochnagaw Boawd");
MODUWE_WICENSE("GPW v2");
