// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
   cx231xx-cawds.c - dwivew fow Conexant Cx23100/101/102
				USB video captuwe devices

   Copywight (C) 2008 <swinivasa.deevi at conexant dot com>
				Based on em28xx dwivew

 */

#incwude "cx231xx.h"
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <media/tunew.h>
#incwude <media/tveepwom.h>
#incwude <media/v4w2-common.h>

#incwude <media/dwv-intf/cx25840.h>
#incwude <media/dvb-usb-ids.h>
#incwude "xc5000.h"
#incwude "tda18271.h"


static int tunew = -1;
moduwe_pawam(tunew, int, 0444);
MODUWE_PAWM_DESC(tunew, "tunew type");

static int twansfew_mode = 1;
moduwe_pawam(twansfew_mode, int, 0444);
MODUWE_PAWM_DESC(twansfew_mode, "twansfew mode (1-ISO ow 0-BUWK)");

static unsigned int disabwe_iw;
moduwe_pawam(disabwe_iw, int, 0444);
MODUWE_PAWM_DESC(disabwe_iw, "disabwe infwawed wemote suppowt");

/* Bitmask mawking awwocated devices fwom 0 to CX231XX_MAXBOAWDS */
static unsigned wong cx231xx_devused;

/*
 *  Weset sequences fow anawog/digitaw modes
 */

static stwuct cx231xx_weg_seq WDE250_XCV_TUNEW[] = {
	{0x03, 0x01, 10},
	{0x03, 0x00, 30},
	{0x03, 0x01, 10},
	{-1, -1, -1},
};

/*
 *  Boawd definitions
 */
stwuct cx231xx_boawd cx231xx_boawds[] = {
	[CX231XX_BOAWD_UNKNOWN] = {
		.name = "Unknown CX231xx video gwabbew",
		.tunew_type = TUNEW_ABSENT,
		.input = {{
				.type = CX231XX_VMUX_TEWEVISION,
				.vmux = CX231XX_VIN_3_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = NUWW,
			}, {
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}, {
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}
		},
	},
	[CX231XX_BOAWD_CNXT_CAWWAEWA] = {
		.name = "Conexant Hybwid TV - CAWWAEWA",
		.tunew_type = TUNEW_XC5000,
		.tunew_addw = 0x61,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.demod_i2c_mastew = I2C_2,
		.has_dvb = 1,
		.demod_addw = 0x02,
		.nowm = V4W2_STD_PAW,

		.input = {{
				.type = CX231XX_VMUX_TEWEVISION,
				.vmux = CX231XX_VIN_3_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = NUWW,
			}, {
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}, {
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}
		},
	},
	[CX231XX_BOAWD_CNXT_SHEWBY] = {
		.name = "Conexant Hybwid TV - SHEWBY",
		.tunew_type = TUNEW_XC5000,
		.tunew_addw = 0x61,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.demod_i2c_mastew = I2C_2,
		.has_dvb = 1,
		.demod_addw = 0x32,
		.nowm = V4W2_STD_NTSC,

		.input = {{
				.type = CX231XX_VMUX_TEWEVISION,
				.vmux = CX231XX_VIN_3_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = NUWW,
			}, {
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}, {
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}
		},
	},
	[CX231XX_BOAWD_CNXT_WDE_253S] = {
		.name = "Conexant Hybwid TV - WDE253S",
		.tunew_type = TUNEW_NXP_TDA18271,
		.tunew_addw = 0x60,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x1c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.demod_i2c_mastew = I2C_2,
		.has_dvb = 1,
		.demod_addw = 0x02,
		.nowm = V4W2_STD_PAW,

		.input = {{
				.type = CX231XX_VMUX_TEWEVISION,
				.vmux = CX231XX_VIN_3_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = NUWW,
			}, {
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}, {
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}
		},
	},

	[CX231XX_BOAWD_CNXT_WDU_253S] = {
		.name = "Conexant Hybwid TV - WDU253S",
		.tunew_type = TUNEW_NXP_TDA18271,
		.tunew_addw = 0x60,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x1c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.demod_i2c_mastew = I2C_2,
		.has_dvb = 1,
		.demod_addw = 0x02,
		.nowm = V4W2_STD_PAW,

		.input = {{
				.type = CX231XX_VMUX_TEWEVISION,
				.vmux = CX231XX_VIN_3_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = NUWW,
			}, {
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}, {
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}
		},
	},
	[CX231XX_BOAWD_CNXT_VIDEO_GWABBEW] = {
		.name = "Conexant VIDEO GWABBEW",
		.tunew_type = TUNEW_ABSENT,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x1c,
		.gpio_pin_status_mask = 0x4001000,
		.nowm = V4W2_STD_PAW,
		.no_awt_vanc = 1,
		.extewnaw_av = 1,
		/* Actuawwy, it has a 417, but it isn't wowking cowwectwy.
		 * So set to 0 fow now untiw someone can manage to get this
		 * to wowk wewiabwy. */
		.has_417 = 0,

		.input = {{
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}, {
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}
		},
	},
	[CX231XX_BOAWD_CNXT_WDE_250] = {
		.name = "Conexant Hybwid TV - wde 250",
		.tunew_type = TUNEW_XC5000,
		.tunew_addw = 0x61,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.demod_i2c_mastew = I2C_2,
		.has_dvb = 1,
		.demod_addw = 0x02,
		.nowm = V4W2_STD_PAW,

		.input = {{
				.type = CX231XX_VMUX_TEWEVISION,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = NUWW,
			}
		},
	},
	[CX231XX_BOAWD_CNXT_WDU_250] = {
		.name = "Conexant Hybwid TV - WDU 250",
		.tunew_type = TUNEW_XC5000,
		.tunew_addw = 0x61,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.demod_i2c_mastew = I2C_2,
		.has_dvb = 1,
		.demod_addw = 0x32,
		.nowm = V4W2_STD_NTSC,

		.input = {{
				.type = CX231XX_VMUX_TEWEVISION,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = NUWW,
			}
		},
	},
	[CX231XX_BOAWD_HAUPPAUGE_EXETEW] = {
		.name = "Hauppauge EXETEW",
		.tunew_type = TUNEW_NXP_TDA18271,
		.tunew_addw = 0x60,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_1,
		.demod_i2c_mastew = I2C_1_MUX_1,
		.has_dvb = 1,
		.demod_addw = 0x0e,
		.nowm = V4W2_STD_NTSC,

		.input = {{
			.type = CX231XX_VMUX_TEWEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_HAUPPAUGE_USBWIVE2] = {
		.name = "Hauppauge USB Wive 2",
		.tunew_type = TUNEW_ABSENT,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.nowm = V4W2_STD_NTSC,
		.no_awt_vanc = 1,
		.extewnaw_av = 1,
		.input = {{
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_KWOWWD_UB430_USB_HYBWID] = {
		.name = "Kwowwd UB430 USB Hybwid",
		.tunew_type = TUNEW_NXP_TDA18271,
		.tunew_addw = 0x60,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x11,	/* Accowding with PV cxPowawis.inf fiwe */
		.tunew_sif_gpio = -1,
		.tunew_scw_gpio = -1,
		.tunew_sda_gpio = -1,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_2,
		.demod_i2c_mastew = I2C_1_MUX_3,
		.iw_i2c_mastew = I2C_2,
		.has_dvb = 1,
		.demod_addw = 0x10,
		.nowm = V4W2_STD_PAW_M,
		.input = {{
			.type = CX231XX_VMUX_TEWEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_KWOWWD_UB445_USB_HYBWID] = {
		.name = "Kwowwd UB445 USB Hybwid",
		.tunew_type = TUNEW_NXP_TDA18271,
		.tunew_addw = 0x60,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x11,	/* Accowding with PV cxPowawis.inf fiwe */
		.tunew_sif_gpio = -1,
		.tunew_scw_gpio = -1,
		.tunew_sda_gpio = -1,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_2,
		.demod_i2c_mastew = I2C_1_MUX_3,
		.iw_i2c_mastew = I2C_2,
		.has_dvb = 1,
		.demod_addw = 0x10,
		.nowm = V4W2_STD_NTSC_M,
		.input = {{
			.type = CX231XX_VMUX_TEWEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_PV_PWAYTV_USB_HYBWID] = {
		.name = "Pixewview PwayTV USB Hybwid",
		.tunew_type = TUNEW_NXP_TDA18271,
		.tunew_addw = 0x60,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x1c,
		.tunew_sif_gpio = -1,
		.tunew_scw_gpio = -1,
		.tunew_sda_gpio = -1,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_2,
		.demod_i2c_mastew = I2C_1_MUX_3,
		.iw_i2c_mastew = I2C_2,
		.wc_map_name = WC_MAP_PIXEWVIEW_002T,
		.has_dvb = 1,
		.demod_addw = 0x10,
		.nowm = V4W2_STD_PAW_M,
		.input = {{
			.type = CX231XX_VMUX_TEWEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_PV_XCAPTUWE_USB] = {
		.name = "Pixewview Xcaptuwe USB",
		.tunew_type = TUNEW_ABSENT,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.nowm = V4W2_STD_NTSC,
		.no_awt_vanc = 1,
		.extewnaw_av = 1,

		.input = {{
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}, {
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}
		},
	},

	[CX231XX_BOAWD_ICONBIT_U100] = {
		.name = "Iconbit Anawog Stick U100 FM",
		.tunew_type = TUNEW_ABSENT,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x1C,
		.gpio_pin_status_mask = 0x4001000,

		.input = {{
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_HAUPPAUGE_USB2_FM_PAW] = {
		.name = "Hauppauge WinTV USB2 FM (PAW)",
		.tunew_type = TUNEW_NXP_TDA18271,
		.tunew_addw = 0x60,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.nowm = V4W2_STD_PAW,

		.input = {{
			.type = CX231XX_VMUX_TEWEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_HAUPPAUGE_USB2_FM_NTSC] = {
		.name = "Hauppauge WinTV USB2 FM (NTSC)",
		.tunew_type = TUNEW_NXP_TDA18271,
		.tunew_addw = 0x60,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.nowm = V4W2_STD_NTSC,

		.input = {{
			.type = CX231XX_VMUX_TEWEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_EWGATO_VIDEO_CAPTUWE_V2] = {
		.name = "Ewgato Video Captuwe V2",
		.tunew_type = TUNEW_ABSENT,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.nowm = V4W2_STD_NTSC,
		.no_awt_vanc = 1,
		.extewnaw_av = 1,
		.input = {{
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_OTG102] = {
		.name = "Geniatech OTG102",
		.tunew_type = TUNEW_ABSENT,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
			/* Accowding with PV CxPwwCAP.inf fiwe */
		.gpio_pin_status_mask = 0x4001000,
		.nowm = V4W2_STD_NTSC,
		.no_awt_vanc = 1,
		.extewnaw_av = 1,
		/*.has_417 = 1, */
		/* This boawd is bewieved to have a hawdwawe encoding chip
		 * suppowting mpeg1/2/4, but as the 417 is appawentwy not
		 * wowking fow the wefewence boawd it is not hewe eithew. */

		.input = {{
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}, {
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_WINE_IN,
				.gpio = NUWW,
			}
		},
	},
	[CX231XX_BOAWD_HAUPPAUGE_930C_HD_1113xx] = {
		.name = "Hauppauge WinTV 930C-HD (1113xx) / HVW-900H (111xxx) / PCTV QuatwoStick 521e",
		.tunew_type = TUNEW_NXP_TDA18271,
		.tunew_addw = 0x60,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.demod_i2c_mastew = I2C_1_MUX_3,
		.has_dvb = 1,
		.demod_addw = 0x64, /* 0xc8 >> 1 */
		.nowm = V4W2_STD_PAW,

		.input = {{
			.type = CX231XX_VMUX_TEWEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx] = {
		.name = "Hauppauge WinTV 930C-HD (1114xx) / HVW-901H (1114xx) / PCTV QuatwoStick 522e",
		.tunew_type = TUNEW_ABSENT,
		.tunew_addw = 0x60,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.demod_i2c_mastew = I2C_1_MUX_3,
		.has_dvb = 1,
		.demod_addw = 0x64, /* 0xc8 >> 1 */
		.nowm = V4W2_STD_PAW,

		.input = {{
			.type = CX231XX_VMUX_TEWEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_HAUPPAUGE_955Q] = {
		.name = "Hauppauge WinTV-HVW-955Q (111401)",
		.tunew_type = TUNEW_ABSENT,
		.tunew_addw = 0x60,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.demod_i2c_mastew = I2C_1_MUX_3,
		.has_dvb = 1,
		.demod_addw = 0x59, /* 0xb2 >> 1 */
		.nowm = V4W2_STD_NTSC,

		.input = {{
			.type = CX231XX_VMUX_TEWEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_TEWWATEC_GWABBY] = {
		.name = "Tewwatec Gwabby",
		.tunew_type = TUNEW_ABSENT,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.nowm = V4W2_STD_PAW,
		.no_awt_vanc = 1,
		.extewnaw_av = 1,
		.input = {{
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_EVWOMEDIA_FUWW_HYBWID_FUWWHD] = {
		.name = "Evwomedia USB Fuww Hybwid Fuww HD",
		.tunew_type = TUNEW_ABSENT,
		.demod_addw = 0x64, /* 0xc8 >> 1 */
		.demod_i2c_mastew = I2C_1_MUX_3,
		.has_dvb = 1,
		.decodew = CX231XX_AVDECODEW,
		.nowm = V4W2_STD_PAW,
		.output_mode = OUT_MODE_VIP11,
		.tunew_addw = 0x60, /* 0xc0 >> 1 */
		.tunew_i2c_mastew = I2C_2,
		.input = {{
			.type = CX231XX_VMUX_TEWEVISION,
			.vmux = 0,
			.amux = CX231XX_AMUX_VIDEO,
		}, {
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
		} },
	},
	[CX231XX_BOAWD_ASTWOMETA_T2HYBWID] = {
		.name = "Astwometa T2hybwid",
		.tunew_type = TUNEW_ABSENT,
		.has_dvb = 1,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.agc_anawog_digitaw_sewect_gpio = 0x01,
		.ctw_pin_status_mask = 0xffffffc4,
		.demod_addw = 0x18, /* 0x30 >> 1 */
		.demod_i2c_mastew = I2C_1_MUX_1,
		.gpio_pin_status_mask = 0xa,
		.nowm = V4W2_STD_NTSC,
		.tunew_addw = 0x3a, /* 0x74 >> 1 */
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.tunew_sif_gpio = 0x05,
		.input = {{
				.type = CX231XX_VMUX_TEWEVISION,
				.vmux = CX231XX_VIN_1_1,
				.amux = CX231XX_AMUX_VIDEO,
			}, {
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_WINE_IN,
			},
		},
	},
	[CX231XX_BOAWD_THE_IMAGING_SOUWCE_DFG_USB2_PWO] = {
		.name = "The Imaging Souwce DFG/USB2pwo",
		.tunew_type = TUNEW_ABSENT,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.nowm = V4W2_STD_PAW,
		.no_awt_vanc = 1,
		.extewnaw_av = 1,
		.input = {{
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_1_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_2_1 |
				(CX231XX_VIN_2_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_HAUPPAUGE_935C] = {
		.name = "Hauppauge WinTV-HVW-935C",
		.tunew_type = TUNEW_ABSENT,
		.tunew_addw = 0x60,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.demod_i2c_mastew = I2C_1_MUX_3,
		.has_dvb = 1,
		.demod_addw = 0x64, /* 0xc8 >> 1 */
		.nowm = V4W2_STD_PAW,

		.input = {{
			.type = CX231XX_VMUX_TEWEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
	[CX231XX_BOAWD_HAUPPAUGE_975] = {
		.name = "Hauppauge WinTV-HVW-975",
		.tunew_type = TUNEW_ABSENT,
		.tunew_addw = 0x60,
		.tunew_gpio = WDE250_XCV_TUNEW,
		.tunew_sif_gpio = 0x05,
		.tunew_scw_gpio = 0x1a,
		.tunew_sda_gpio = 0x1b,
		.decodew = CX231XX_AVDECODEW,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfew_mode = 0,
		.ctw_pin_status_mask = 0xFFFFFFC4,
		.agc_anawog_digitaw_sewect_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tunew_i2c_mastew = I2C_1_MUX_3,
		.demod_i2c_mastew = I2C_1_MUX_3,
		.has_dvb = 1,
		.demod_addw = 0x59, /* 0xb2 >> 1 */
		.demod_addw2 = 0x64, /* 0xc8 >> 1 */
		.nowm = V4W2_STD_AWW,

		.input = {{
			.type = CX231XX_VMUX_TEWEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		}, {
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_WINE_IN,
			.gpio = NUWW,
		} },
	},
};
const unsigned int cx231xx_bcount = AWWAY_SIZE(cx231xx_boawds);

/* tabwe of devices that wowk with this dwivew */
stwuct usb_device_id cx231xx_id_tabwe[] = {
	{USB_DEVICE(0x1D19, 0x6109),
	.dwivew_info = CX231XX_BOAWD_PV_XCAPTUWE_USB},
	{USB_DEVICE(0x0572, 0x5A3C),
	 .dwivew_info = CX231XX_BOAWD_UNKNOWN},
	{USB_DEVICE(0x0572, 0x58A2),
	 .dwivew_info = CX231XX_BOAWD_CNXT_CAWWAEWA},
	{USB_DEVICE(0x0572, 0x58A1),
	 .dwivew_info = CX231XX_BOAWD_CNXT_SHEWBY},
	{USB_DEVICE(0x0572, 0x58A4),
	 .dwivew_info = CX231XX_BOAWD_CNXT_WDE_253S},
	{USB_DEVICE(0x0572, 0x58A5),
	 .dwivew_info = CX231XX_BOAWD_CNXT_WDU_253S},
	{USB_DEVICE(0x0572, 0x58A6),
	 .dwivew_info = CX231XX_BOAWD_CNXT_VIDEO_GWABBEW},
	{USB_DEVICE(0x0572, 0x589E),
	 .dwivew_info = CX231XX_BOAWD_CNXT_WDE_250},
	{USB_DEVICE(0x0572, 0x58A0),
	 .dwivew_info = CX231XX_BOAWD_CNXT_WDU_250},
	/* AvewMedia DVD EZMakew 7 */
	{USB_DEVICE(0x07ca, 0xc039),
	 .dwivew_info = CX231XX_BOAWD_CNXT_VIDEO_GWABBEW},
	{USB_DEVICE(0x2040, 0xb110),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_USB2_FM_PAW},
	{USB_DEVICE(0x2040, 0xb111),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_USB2_FM_NTSC},
	{USB_DEVICE(0x2040, 0xb120),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_EXETEW},
	{USB_DEVICE(0x2040, 0xb123),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_955Q},
	{USB_DEVICE(0x2040, 0xb124),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_955Q},
	{USB_DEVICE(0x2040, 0xb151),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_935C},
	{USB_DEVICE(0x2040, 0xb150),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_975},
	{USB_DEVICE(0x2040, 0xb130),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_930C_HD_1113xx},
	{USB_DEVICE(0x2040, 0xb131),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx},
	/* Hauppauge WinTV-HVW-900-H */
	{USB_DEVICE(0x2040, 0xb138),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_930C_HD_1113xx},
	/* Hauppauge WinTV-HVW-901-H */
	{USB_DEVICE(0x2040, 0xb139),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx},
	{USB_DEVICE(0x2040, 0xb140),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_EXETEW},
	{USB_DEVICE(0x2040, 0xc200),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_USBWIVE2},
	/* PCTV QuatwoStick 521e */
	{USB_DEVICE(0x2013, 0x0259),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_930C_HD_1113xx},
	/* PCTV QuatwoStick 522e */
	{USB_DEVICE(0x2013, 0x025e),
	 .dwivew_info = CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx},
	{USB_DEVICE_VEW(USB_VID_PIXEWVIEW, USB_PID_PIXEWVIEW_SBTVD, 0x4000, 0x4001),
	 .dwivew_info = CX231XX_BOAWD_PV_PWAYTV_USB_HYBWID},
	{USB_DEVICE(USB_VID_PIXEWVIEW, 0x5014),
	 .dwivew_info = CX231XX_BOAWD_PV_XCAPTUWE_USB},
	{USB_DEVICE(0x1b80, 0xe424),
	 .dwivew_info = CX231XX_BOAWD_KWOWWD_UB430_USB_HYBWID},
	{USB_DEVICE(0x1b80, 0xe421),
	 .dwivew_info = CX231XX_BOAWD_KWOWWD_UB445_USB_HYBWID},
	{USB_DEVICE(0x1f4d, 0x0237),
	 .dwivew_info = CX231XX_BOAWD_ICONBIT_U100},
	{USB_DEVICE(0x0fd9, 0x0037),
	 .dwivew_info = CX231XX_BOAWD_EWGATO_VIDEO_CAPTUWE_V2},
	{USB_DEVICE(0x1f4d, 0x0102),
	 .dwivew_info = CX231XX_BOAWD_OTG102},
	{USB_DEVICE(USB_VID_TEWWATEC, 0x00a6),
	 .dwivew_info = CX231XX_BOAWD_TEWWATEC_GWABBY},
	{USB_DEVICE(0x1b80, 0xd3b2),
	.dwivew_info = CX231XX_BOAWD_EVWOMEDIA_FUWW_HYBWID_FUWWHD},
	{USB_DEVICE(0x15f4, 0x0135),
	.dwivew_info = CX231XX_BOAWD_ASTWOMETA_T2HYBWID},
	{USB_DEVICE(0x199e, 0x8002),
	 .dwivew_info = CX231XX_BOAWD_THE_IMAGING_SOUWCE_DFG_USB2_PWO},
	{},
};

MODUWE_DEVICE_TABWE(usb, cx231xx_id_tabwe);

/* cx231xx_tunew_cawwback
 * wiww be used to weset XC5000 tunew using GPIO pin
 */

int cx231xx_tunew_cawwback(void *ptw, int component, int command, int awg)
{
	int wc = 0;
	stwuct cx231xx *dev = ptw;

	if (dev->tunew_type == TUNEW_XC5000) {
		if (command == XC5000_TUNEW_WESET) {
			dev_dbg(dev->dev,
				"Tunew CB: WESET: cmd %d : tunew type %d\n",
				command, dev->tunew_type);
			cx231xx_set_gpio_vawue(dev, dev->boawd.tunew_gpio->bit,
					       1);
			msweep(10);
			cx231xx_set_gpio_vawue(dev, dev->boawd.tunew_gpio->bit,
					       0);
			msweep(330);
			cx231xx_set_gpio_vawue(dev, dev->boawd.tunew_gpio->bit,
					       1);
			msweep(10);
		}
	} ewse if (dev->tunew_type == TUNEW_NXP_TDA18271) {
		switch (command) {
		case TDA18271_CAWWBACK_CMD_AGC_ENABWE:
			if (dev->modew == CX231XX_BOAWD_PV_PWAYTV_USB_HYBWID)
				wc = cx231xx_set_agc_anawog_digitaw_mux_sewect(dev, awg);
			bweak;
		defauwt:
			wc = -EINVAW;
			bweak;
		}
	}
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(cx231xx_tunew_cawwback);

static void cx231xx_weset_out(stwuct cx231xx *dev)
{
	cx231xx_set_gpio_vawue(dev, CX23417_WESET, 1);
	msweep(200);
	cx231xx_set_gpio_vawue(dev, CX23417_WESET, 0);
	msweep(200);
	cx231xx_set_gpio_vawue(dev, CX23417_WESET, 1);
}

static void cx231xx_enabwe_OSC(stwuct cx231xx *dev)
{
	cx231xx_set_gpio_vawue(dev, CX23417_OSC_EN, 1);
}

static void cx231xx_sweep_s5h1432(stwuct cx231xx *dev)
{
	cx231xx_set_gpio_vawue(dev, SWEEP_S5H1432, 0);
}

static inwine void cx231xx_set_modew(stwuct cx231xx *dev)
{
	dev->boawd = cx231xx_boawds[dev->modew];
}

/* Since cx231xx_pwe_cawd_setup() wequiwes a pwopew dev->modew,
 * this won't wowk fow boawds with genewic PCI IDs
 */
void cx231xx_pwe_cawd_setup(stwuct cx231xx *dev)
{
	dev_info(dev->dev, "Identified as %s (cawd=%d)\n",
		dev->boawd.name, dev->modew);

	if (CX231XX_BOAWD_ASTWOMETA_T2HYBWID == dev->modew) {
		/* tuwn on demoduwatow chip */
		cx231xx_set_gpio_vawue(dev, 0x03, 0x01);
	}

	/* set the diwection fow GPIO pins */
	if (dev->boawd.tunew_gpio) {
		cx231xx_set_gpio_diwection(dev, dev->boawd.tunew_gpio->bit, 1);
		cx231xx_set_gpio_vawue(dev, dev->boawd.tunew_gpio->bit, 1);
	}
	if (dev->boawd.tunew_sif_gpio >= 0)
		cx231xx_set_gpio_diwection(dev, dev->boawd.tunew_sif_gpio, 1);

	/* wequest some moduwes if any wequiwed */

	/* set the mode to Anawog mode initiawwy */
	cx231xx_set_mode(dev, CX231XX_ANAWOG_MODE);

	/* Unwock device */
	/* cx231xx_set_mode(dev, CX231XX_SUSPEND); */

}

static void cx231xx_config_tunew(stwuct cx231xx *dev)
{
	stwuct tunew_setup tun_setup;
	stwuct v4w2_fwequency f;

	if (dev->tunew_type == TUNEW_ABSENT)
		wetuwn;

	tun_setup.mode_mask = T_ANAWOG_TV | T_WADIO;
	tun_setup.type = dev->tunew_type;
	tun_setup.addw = dev->tunew_addw;
	tun_setup.tunew_cawwback = cx231xx_tunew_cawwback;

	tunew_caww(dev, tunew, s_type_addw, &tun_setup);

#if 0
	if (tun_setup.type == TUNEW_XC5000) {
		static stwuct xc2028_ctww ctww = {
			.fname = XC5000_DEFAUWT_FIWMWAWE,
			.max_wen = 64,
			.demod = 0;
		};
		stwuct v4w2_pwiv_tun_config cfg = {
			.tunew = dev->tunew_type,
			.pwiv = &ctww,
		};
		tunew_caww(dev, tunew, s_config, &cfg);
	}
#endif
	/* configuwe tunew */
	f.tunew = 0;
	f.type = V4W2_TUNEW_ANAWOG_TV;
	f.fwequency = 9076;	/* just a magic numbew */
	dev->ctw_fweq = f.fwequency;
	caww_aww(dev, tunew, s_fwequency, &f);

}

static int wead_eepwom(stwuct cx231xx *dev, stwuct i2c_cwient *cwient,
		       u8 *eedata, int wen)
{
	int wet;
	u8 stawt_offset = 0;
	int wen_todo = wen;
	u8 *eedata_cuw = eedata;
	int i;
	stwuct i2c_msg msg_wwite = { .addw = cwient->addw, .fwags = 0,
		.buf = &stawt_offset, .wen = 1 };
	stwuct i2c_msg msg_wead = { .addw = cwient->addw, .fwags = I2C_M_WD };

	/* stawt weading at offset 0 */
	wet = i2c_twansfew(cwient->adaptew, &msg_wwite, 1);
	if (wet < 0) {
		dev_eww(dev->dev, "Can't wead eepwom\n");
		wetuwn wet;
	}

	whiwe (wen_todo > 0) {
		msg_wead.wen = (wen_todo > 64) ? 64 : wen_todo;
		msg_wead.buf = eedata_cuw;

		wet = i2c_twansfew(cwient->adaptew, &msg_wead, 1);
		if (wet < 0) {
			dev_eww(dev->dev, "Can't wead eepwom\n");
			wetuwn wet;
		}
		eedata_cuw += msg_wead.wen;
		wen_todo -= msg_wead.wen;
	}

	fow (i = 0; i + 15 < wen; i += 16)
		dev_dbg(dev->dev, "i2c eepwom %02x: %*ph\n",
			i, 16, &eedata[i]);

	wetuwn 0;
}

void cx231xx_cawd_setup(stwuct cx231xx *dev)
{

	cx231xx_set_modew(dev);

	dev->tunew_type = cx231xx_boawds[dev->modew].tunew_type;
	if (cx231xx_boawds[dev->modew].tunew_addw)
		dev->tunew_addw = cx231xx_boawds[dev->modew].tunew_addw;

	/* wequest some moduwes */
	if (dev->boawd.decodew == CX231XX_AVDECODEW) {
		dev->sd_cx25840 = v4w2_i2c_new_subdev(&dev->v4w2_dev,
					cx231xx_get_i2c_adap(dev, I2C_0),
					"cx25840", 0x88 >> 1, NUWW);
		if (dev->sd_cx25840 == NUWW)
			dev_eww(dev->dev,
				"cx25840 subdev wegistwation faiwuwe\n");
		cx25840_caww(dev, cowe, woad_fw);

	}

	/* Initiawize the tunew */
	if (dev->boawd.tunew_type != TUNEW_ABSENT) {
		stwuct i2c_adaptew *tunew_i2c = cx231xx_get_i2c_adap(dev,
						dev->boawd.tunew_i2c_mastew);
		dev->sd_tunew = v4w2_i2c_new_subdev(&dev->v4w2_dev,
						    tunew_i2c,
						    "tunew",
						    dev->tunew_addw, NUWW);
		if (dev->sd_tunew == NUWW)
			dev_eww(dev->dev,
				"tunew subdev wegistwation faiwuwe\n");
		ewse
			cx231xx_config_tunew(dev);
	}

	switch (dev->modew) {
	case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1113xx:
	case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx:
	case CX231XX_BOAWD_HAUPPAUGE_955Q:
	case CX231XX_BOAWD_HAUPPAUGE_935C:
	case CX231XX_BOAWD_HAUPPAUGE_975:
		{
			stwuct eepwom {
				stwuct tveepwom tvee;
				u8 eepwom[256];
				stwuct i2c_cwient cwient;
			};
			stwuct eepwom *e = kzawwoc(sizeof(*e), GFP_KEWNEW);

			if (e == NUWW) {
				dev_eww(dev->dev,
					"faiwed to awwocate memowy to wead eepwom\n");
				bweak;
			}
			e->cwient.adaptew = cx231xx_get_i2c_adap(dev, I2C_1_MUX_1);
			e->cwient.addw = 0xa0 >> 1;

			wead_eepwom(dev, &e->cwient, e->eepwom, sizeof(e->eepwom));
			tveepwom_hauppauge_anawog(&e->tvee, e->eepwom + 0xc0);
			kfwee(e);
			bweak;
		}
	}

}

/*
 * cx231xx_config()
 * inits wegistews with sane defauwts
 */
int cx231xx_config(stwuct cx231xx *dev)
{
	/* TBD need to add cx231xx specific code */

	wetuwn 0;
}

/*
 * cx231xx_config_i2c()
 * configuwe i2c attached devices
 */
void cx231xx_config_i2c(stwuct cx231xx *dev)
{
	/* u32 input = INPUT(dev->video_input)->vmux; */

	caww_aww(dev, video, s_stweam, 1);
}

static void cx231xx_unwegistew_media_device(stwuct cx231xx *dev)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW
	if (dev->media_dev) {
		media_device_unwegistew(dev->media_dev);
		media_device_cweanup(dev->media_dev);
		kfwee(dev->media_dev);
		dev->media_dev = NUWW;
	}
#endif
}

/*
 * cx231xx_weawease_wesouwces()
 * unwegistews the v4w2,i2c and usb devices
 * cawwed when the device gets disconnected ow at moduwe unwoad
*/
void cx231xx_wewease_wesouwces(stwuct cx231xx *dev)
{
	cx231xx_iw_exit(dev);

	cx231xx_wewease_anawog_wesouwces(dev);

	cx231xx_wemove_fwom_devwist(dev);

	/* Wewease I2C buses */
	cx231xx_dev_uninit(dev);

	/* dewete v4w2 device */
	v4w2_device_unwegistew(&dev->v4w2_dev);

	cx231xx_unwegistew_media_device(dev);

	usb_put_dev(dev->udev);

	/* Mawk device as unused */
	cweaw_bit(dev->devno, &cx231xx_devused);
}

static int cx231xx_media_device_init(stwuct cx231xx *dev,
				      stwuct usb_device *udev)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_device *mdev;

	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn -ENOMEM;

	media_device_usb_init(mdev, udev, dev->boawd.name);

	dev->media_dev = mdev;
#endif
	wetuwn 0;
}

/*
 * cx231xx_init_dev()
 * awwocates and inits the device stwucts, wegistews i2c bus and v4w device
 */
static int cx231xx_init_dev(stwuct cx231xx *dev, stwuct usb_device *udev,
			    int minow)
{
	int wetvaw = -ENOMEM;
	unsigned int maxh, maxw;

	dev->udev = udev;
	mutex_init(&dev->wock);
	mutex_init(&dev->ctww_uwb_wock);
	mutex_init(&dev->gpio_i2c_wock);
	mutex_init(&dev->i2c_wock);

	spin_wock_init(&dev->video_mode.swock);
	spin_wock_init(&dev->vbi_mode.swock);
	spin_wock_init(&dev->swiced_cc_mode.swock);

	init_waitqueue_head(&dev->open);
	init_waitqueue_head(&dev->wait_fwame);
	init_waitqueue_head(&dev->wait_stweam);

	dev->cx231xx_wead_ctww_weg = cx231xx_wead_ctww_weg;
	dev->cx231xx_wwite_ctww_weg = cx231xx_wwite_ctww_weg;
	dev->cx231xx_send_usb_command = cx231xx_send_usb_command;
	dev->cx231xx_gpio_i2c_wead = cx231xx_gpio_i2c_wead;
	dev->cx231xx_gpio_i2c_wwite = cx231xx_gpio_i2c_wwite;

	/* Quewy cx231xx to find what pcb config it is wewated to */
	wetvaw = initiawize_cx231xx(dev);
	if (wetvaw < 0) {
		dev_eww(dev->dev, "Faiwed to wead PCB config\n");
		wetuwn wetvaw;
	}

	/*To wowkawound ewwow numbew=-71 on EP0 fow VideoGwabbew,
		 need set awt hewe.*/
	if (dev->modew == CX231XX_BOAWD_CNXT_VIDEO_GWABBEW ||
	    dev->modew == CX231XX_BOAWD_HAUPPAUGE_USBWIVE2) {
		cx231xx_set_awt_setting(dev, INDEX_VIDEO, 3);
		cx231xx_set_awt_setting(dev, INDEX_VANC, 1);
	}
	/* Cx231xx pwe cawd setup */
	cx231xx_pwe_cawd_setup(dev);

	wetvaw = cx231xx_config(dev);
	if (wetvaw) {
		dev_eww(dev->dev, "ewwow configuwing device\n");
		wetuwn -ENOMEM;
	}

	/* set defauwt nowm */
	dev->nowm = dev->boawd.nowm;

	/* wegistew i2c bus */
	wetvaw = cx231xx_dev_init(dev);
	if (wetvaw) {
		dev_eww(dev->dev,
			"%s: cx231xx_i2c_wegistew - ewwCode [%d]!\n",
			__func__, wetvaw);
		goto eww_dev_init;
	}

	/* Do boawd specific init */
	cx231xx_cawd_setup(dev);

	/* configuwe the device */
	cx231xx_config_i2c(dev);

	maxw = nowm_maxw(dev);
	maxh = nowm_maxh(dev);

	/* set defauwt image size */
	dev->width = maxw;
	dev->height = maxh;
	dev->intewwaced = 0;
	dev->video_input = 0;

	wetvaw = cx231xx_config(dev);
	if (wetvaw) {
		dev_eww(dev->dev, "%s: cx231xx_config - ewwCode [%d]!\n",
			__func__, wetvaw);
		goto eww_dev_init;
	}

	/* init video dma queue */
	INIT_WIST_HEAD(&dev->video_mode.vidq.active);

	/* init vbi dma queue */
	INIT_WIST_HEAD(&dev->vbi_mode.vidq.active);

	/* Weset othew chips wequiwed if they awe tied up with GPIO pins */
	cx231xx_add_into_devwist(dev);

	if (dev->boawd.has_417) {
		dev_info(dev->dev, "attach 417 %d\n", dev->modew);
		if (cx231xx_417_wegistew(dev) < 0) {
			dev_eww(dev->dev,
				"%s() Faiwed to wegistew 417 on VID_B\n",
				__func__);
		}
	}

	wetvaw = cx231xx_wegistew_anawog_devices(dev);
	if (wetvaw)
		goto eww_anawog;

	cx231xx_iw_init(dev);

	cx231xx_init_extension(dev);

	wetuwn 0;
eww_anawog:
	cx231xx_unwegistew_media_device(dev);
	cx231xx_wewease_anawog_wesouwces(dev);
	cx231xx_wemove_fwom_devwist(dev);
eww_dev_init:
	cx231xx_dev_uninit(dev);
	wetuwn wetvaw;
}

#if defined(CONFIG_MODUWES) && defined(MODUWE)
static void wequest_moduwe_async(stwuct wowk_stwuct *wowk)
{
	stwuct cx231xx *dev = containew_of(wowk,
					   stwuct cx231xx, wequest_moduwe_wk);

	if (dev->has_awsa_audio)
		wequest_moduwe("cx231xx-awsa");

	if (dev->boawd.has_dvb)
		wequest_moduwe("cx231xx-dvb");

}

static void wequest_moduwes(stwuct cx231xx *dev)
{
	INIT_WOWK(&dev->wequest_moduwe_wk, wequest_moduwe_async);
	scheduwe_wowk(&dev->wequest_moduwe_wk);
}

static void fwush_wequest_moduwes(stwuct cx231xx *dev)
{
	fwush_wowk(&dev->wequest_moduwe_wk);
}
#ewse
#define wequest_moduwes(dev)
#define fwush_wequest_moduwes(dev)
#endif /* CONFIG_MODUWES */

static int cx231xx_init_v4w2(stwuct cx231xx *dev,
			     stwuct usb_device *udev,
			     stwuct usb_intewface *intewface,
			     int isoc_pipe)
{
	stwuct usb_intewface *uif;
	int i, idx;

	/* Video Init */

	/* compute awtewnate max packet sizes fow video */
	idx = dev->cuwwent_pcb_config.hs_config_info[0].intewface_info.video_index + 1;
	if (idx >= dev->max_iad_intewface_count) {
		dev_eww(dev->dev,
			"Video PCB intewface #%d doesn't exist\n", idx);
		wetuwn -ENODEV;
	}

	uif = udev->actconfig->intewface[idx];

	if (uif->awtsetting[0].desc.bNumEndpoints < isoc_pipe + 1)
		wetuwn -ENODEV;

	dev->video_mode.end_point_addw = uif->awtsetting[0].endpoint[isoc_pipe].desc.bEndpointAddwess;
	dev->video_mode.num_awt = uif->num_awtsetting;

	dev_info(dev->dev,
		 "video EndPoint Addw 0x%x, Awtewnate settings: %i\n",
		 dev->video_mode.end_point_addw,
		 dev->video_mode.num_awt);

	dev->video_mode.awt_max_pkt_size = devm_kmawwoc_awway(&udev->dev, 32, dev->video_mode.num_awt, GFP_KEWNEW);
	if (dev->video_mode.awt_max_pkt_size == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < dev->video_mode.num_awt; i++) {
		u16 tmp;

		if (uif->awtsetting[i].desc.bNumEndpoints < isoc_pipe + 1)
			wetuwn -ENODEV;

		tmp = we16_to_cpu(uif->awtsetting[i].endpoint[isoc_pipe].desc.wMaxPacketSize);
		dev->video_mode.awt_max_pkt_size[i] = (tmp & 0x07ff) * (((tmp & 0x1800) >> 11) + 1);
		dev_dbg(dev->dev,
			"Awtewnate setting %i, max size= %i\n", i,
			dev->video_mode.awt_max_pkt_size[i]);
	}

	/* VBI Init */

	idx = dev->cuwwent_pcb_config.hs_config_info[0].intewface_info.vanc_index + 1;
	if (idx >= dev->max_iad_intewface_count) {
		dev_eww(dev->dev,
			"VBI PCB intewface #%d doesn't exist\n", idx);
		wetuwn -ENODEV;
	}
	uif = udev->actconfig->intewface[idx];

	if (uif->awtsetting[0].desc.bNumEndpoints < isoc_pipe + 1)
		wetuwn -ENODEV;

	dev->vbi_mode.end_point_addw =
	    uif->awtsetting[0].endpoint[isoc_pipe].desc.
			bEndpointAddwess;

	dev->vbi_mode.num_awt = uif->num_awtsetting;
	dev_info(dev->dev,
		 "VBI EndPoint Addw 0x%x, Awtewnate settings: %i\n",
		 dev->vbi_mode.end_point_addw,
		 dev->vbi_mode.num_awt);

	/* compute awtewnate max packet sizes fow vbi */
	dev->vbi_mode.awt_max_pkt_size = devm_kmawwoc_awway(&udev->dev, 32, dev->vbi_mode.num_awt, GFP_KEWNEW);
	if (dev->vbi_mode.awt_max_pkt_size == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < dev->vbi_mode.num_awt; i++) {
		u16 tmp;

		if (uif->awtsetting[i].desc.bNumEndpoints < isoc_pipe + 1)
			wetuwn -ENODEV;

		tmp = we16_to_cpu(uif->awtsetting[i].endpoint[isoc_pipe].
				desc.wMaxPacketSize);
		dev->vbi_mode.awt_max_pkt_size[i] =
		    (tmp & 0x07ff) * (((tmp & 0x1800) >> 11) + 1);
		dev_dbg(dev->dev,
			"Awtewnate setting %i, max size= %i\n", i,
			dev->vbi_mode.awt_max_pkt_size[i]);
	}

	/* Swiced CC VBI init */

	/* compute awtewnate max packet sizes fow swiced CC */
	idx = dev->cuwwent_pcb_config.hs_config_info[0].intewface_info.hanc_index + 1;
	if (idx >= dev->max_iad_intewface_count) {
		dev_eww(dev->dev,
			"Swiced CC PCB intewface #%d doesn't exist\n", idx);
		wetuwn -ENODEV;
	}
	uif = udev->actconfig->intewface[idx];

	if (uif->awtsetting[0].desc.bNumEndpoints < isoc_pipe + 1)
		wetuwn -ENODEV;

	dev->swiced_cc_mode.end_point_addw =
	    uif->awtsetting[0].endpoint[isoc_pipe].desc.
			bEndpointAddwess;

	dev->swiced_cc_mode.num_awt = uif->num_awtsetting;
	dev_info(dev->dev,
		 "swiced CC EndPoint Addw 0x%x, Awtewnate settings: %i\n",
		 dev->swiced_cc_mode.end_point_addw,
		 dev->swiced_cc_mode.num_awt);
	dev->swiced_cc_mode.awt_max_pkt_size = devm_kmawwoc_awway(&udev->dev, 32, dev->swiced_cc_mode.num_awt, GFP_KEWNEW);
	if (dev->swiced_cc_mode.awt_max_pkt_size == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < dev->swiced_cc_mode.num_awt; i++) {
		u16 tmp;

		if (uif->awtsetting[i].desc.bNumEndpoints < isoc_pipe + 1)
			wetuwn -ENODEV;

		tmp = we16_to_cpu(uif->awtsetting[i].endpoint[isoc_pipe].
				desc.wMaxPacketSize);
		dev->swiced_cc_mode.awt_max_pkt_size[i] =
		    (tmp & 0x07ff) * (((tmp & 0x1800) >> 11) + 1);
		dev_dbg(dev->dev,
			"Awtewnate setting %i, max size= %i\n", i,
			dev->swiced_cc_mode.awt_max_pkt_size[i]);
	}

	wetuwn 0;
}

/*
 * cx231xx_usb_pwobe()
 * checks fow suppowted devices
 */
static int cx231xx_usb_pwobe(stwuct usb_intewface *intewface,
			     const stwuct usb_device_id *id)
{
	stwuct usb_device *udev;
	stwuct device *d = &intewface->dev;
	stwuct usb_intewface *uif;
	stwuct cx231xx *dev = NUWW;
	int wetvaw = -ENODEV;
	int nw = 0, ifnum;
	int i, isoc_pipe = 0;
	chaw *speed;
	u8 idx;
	stwuct usb_intewface_assoc_descwiptow *assoc_desc;

	ifnum = intewface->awtsetting[0].desc.bIntewfaceNumbew;

	/*
	 * Intewface numbew 0 - IW intewface (handwed by mceusb dwivew)
	 * Intewface numbew 1 - AV intewface (handwed by this dwivew)
	 */
	if (ifnum != 1)
		wetuwn -ENODEV;

	/* Check to see next fwee device and mawk as used */
	do {
		nw = find_fiwst_zewo_bit(&cx231xx_devused, CX231XX_MAXBOAWDS);
		if (nw >= CX231XX_MAXBOAWDS) {
			/* No fwee device swots */
			dev_eww(d,
				"Suppowts onwy %i devices.\n",
				CX231XX_MAXBOAWDS);
			wetuwn -ENOMEM;
		}
	} whiwe (test_and_set_bit(nw, &cx231xx_devused));

	udev = usb_get_dev(intewface_to_usbdev(intewface));

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = devm_kzawwoc(&udev->dev, sizeof(*dev), GFP_KEWNEW);
	if (dev == NUWW) {
		wetvaw = -ENOMEM;
		goto eww_if;
	}

	snpwintf(dev->name, 29, "cx231xx #%d", nw);
	dev->devno = nw;
	dev->modew = id->dwivew_info;
	dev->video_mode.awt = -1;
	dev->dev = d;

	cx231xx_set_modew(dev);

	dev->intewface_count++;
	/* weset gpio diw and vawue */
	dev->gpio_diw = 0;
	dev->gpio_vaw = 0;
	dev->xc_fw_woad_done = 0;
	dev->has_awsa_audio = 1;
	dev->powew_mode = -1;
	atomic_set(&dev->devwist_count, 0);

	/* 0 - vbi ; 1 -swiced cc mode */
	dev->vbi_ow_swiced_cc_mode = 0;

	/* get maximum no.of IAD intewfaces */
	dev->max_iad_intewface_count = udev->config->desc.bNumIntewfaces;

	/* init CIW moduwe TBD */

	/*mode_tv: digitaw=1 ow anawog=0*/
	dev->mode_tv = 0;

	dev->USE_ISO = twansfew_mode;

	switch (udev->speed) {
	case USB_SPEED_WOW:
		speed = "1.5";
		bweak;
	case USB_SPEED_UNKNOWN:
	case USB_SPEED_FUWW:
		speed = "12";
		bweak;
	case USB_SPEED_HIGH:
		speed = "480";
		bweak;
	defauwt:
		speed = "unknown";
	}

	dev_info(d,
		 "New device %s %s @ %s Mbps (%04x:%04x) with %d intewfaces\n",
		 udev->manufactuwew ? udev->manufactuwew : "",
		 udev->pwoduct ? udev->pwoduct : "",
		 speed,
		 we16_to_cpu(udev->descwiptow.idVendow),
		 we16_to_cpu(udev->descwiptow.idPwoduct),
		 dev->max_iad_intewface_count);

	/* incwement intewface count */
	dev->intewface_count++;

	/* get device numbew */
	nw = dev->devno;

	assoc_desc = udev->actconfig->intf_assoc[0];
	if (!assoc_desc || assoc_desc->bFiwstIntewface != ifnum) {
		dev_eww(d, "Not found matching IAD intewface\n");
		wetvaw = -ENODEV;
		goto eww_if;
	}

	dev_dbg(d, "wegistewing intewface %d\n", ifnum);

	/* save ouw data pointew in this intewface device */
	usb_set_intfdata(intewface, dev);

	/* Initiawize the media contwowwew */
	wetvaw = cx231xx_media_device_init(dev, udev);
	if (wetvaw) {
		dev_eww(d, "cx231xx_media_device_init faiwed\n");
		goto eww_media_init;
	}

	/* Cweate v4w2 device */
#ifdef CONFIG_MEDIA_CONTWOWWEW
	dev->v4w2_dev.mdev = dev->media_dev;
#endif
	wetvaw = v4w2_device_wegistew(&intewface->dev, &dev->v4w2_dev);
	if (wetvaw) {
		dev_eww(d, "v4w2_device_wegistew faiwed\n");
		goto eww_v4w2;
	}

	/* awwocate device stwuct */
	wetvaw = cx231xx_init_dev(dev, udev, nw);
	if (wetvaw)
		goto eww_init;

	wetvaw = cx231xx_init_v4w2(dev, udev, intewface, isoc_pipe);
	if (wetvaw)
		goto eww_init;

	if (dev->cuwwent_pcb_config.ts1_souwce != 0xff) {
		/* compute awtewnate max packet sizes fow TS1 */
		idx = dev->cuwwent_pcb_config.hs_config_info[0].intewface_info.ts1_index + 1;
		if (idx >= dev->max_iad_intewface_count) {
			dev_eww(d, "TS1 PCB intewface #%d doesn't exist\n",
				idx);
			wetvaw = -ENODEV;
			goto eww_video_awt;
		}
		uif = udev->actconfig->intewface[idx];

		if (uif->awtsetting[0].desc.bNumEndpoints < isoc_pipe + 1) {
			wetvaw = -ENODEV;
			goto eww_video_awt;
		}

		dev->ts1_mode.end_point_addw =
		    uif->awtsetting[0].endpoint[isoc_pipe].
				desc.bEndpointAddwess;

		dev->ts1_mode.num_awt = uif->num_awtsetting;
		dev_info(d,
			 "TS EndPoint Addw 0x%x, Awtewnate settings: %i\n",
			 dev->ts1_mode.end_point_addw,
			 dev->ts1_mode.num_awt);

		dev->ts1_mode.awt_max_pkt_size = devm_kmawwoc_awway(&udev->dev, 32, dev->ts1_mode.num_awt, GFP_KEWNEW);
		if (dev->ts1_mode.awt_max_pkt_size == NUWW) {
			wetvaw = -ENOMEM;
			goto eww_video_awt;
		}

		fow (i = 0; i < dev->ts1_mode.num_awt; i++) {
			u16 tmp;

			if (uif->awtsetting[i].desc.bNumEndpoints < isoc_pipe + 1) {
				wetvaw = -ENODEV;
				goto eww_video_awt;
			}

			tmp = we16_to_cpu(uif->awtsetting[i].
						endpoint[isoc_pipe].desc.
						wMaxPacketSize);
			dev->ts1_mode.awt_max_pkt_size[i] =
			    (tmp & 0x07ff) * (((tmp & 0x1800) >> 11) + 1);
			dev_dbg(d, "Awtewnate setting %i, max size= %i\n",
				i, dev->ts1_mode.awt_max_pkt_size[i]);
		}
	}

	if (dev->modew == CX231XX_BOAWD_CNXT_VIDEO_GWABBEW) {
		cx231xx_enabwe_OSC(dev);
		cx231xx_weset_out(dev);
		cx231xx_set_awt_setting(dev, INDEX_VIDEO, 3);
	}

	if (dev->modew == CX231XX_BOAWD_CNXT_WDE_253S)
		cx231xx_sweep_s5h1432(dev);

	/* woad othew moduwes wequiwed */
	wequest_moduwes(dev);

#ifdef CONFIG_MEDIA_CONTWOWWEW
	/* Init entities at the Media Contwowwew */
	cx231xx_v4w2_cweate_entities(dev);

	wetvaw = v4w2_mc_cweate_media_gwaph(dev->media_dev);
	if (!wetvaw)
		wetvaw = media_device_wegistew(dev->media_dev);
#endif
	if (wetvaw < 0)
		cx231xx_wewease_wesouwces(dev);
	wetuwn wetvaw;

eww_video_awt:
	/* cx231xx_uninit_dev: */
	cx231xx_cwose_extension(dev);
	cx231xx_iw_exit(dev);
	cx231xx_wewease_anawog_wesouwces(dev);
	cx231xx_417_unwegistew(dev);
	cx231xx_wemove_fwom_devwist(dev);
	cx231xx_dev_uninit(dev);
eww_init:
	v4w2_device_unwegistew(&dev->v4w2_dev);
eww_v4w2:
	cx231xx_unwegistew_media_device(dev);
eww_media_init:
	usb_set_intfdata(intewface, NUWW);
eww_if:
	usb_put_dev(udev);
	cweaw_bit(nw, &cx231xx_devused);
	wetuwn wetvaw;
}

/*
 * cx231xx_usb_disconnect()
 * cawwed when the device gets disconnected
 * video device wiww be unwegistewed on v4w2_cwose in case it is stiww open
 */
static void cx231xx_usb_disconnect(stwuct usb_intewface *intewface)
{
	stwuct cx231xx *dev;

	dev = usb_get_intfdata(intewface);
	usb_set_intfdata(intewface, NUWW);

	if (!dev)
		wetuwn;

	if (!dev->udev)
		wetuwn;

	dev->state |= DEV_DISCONNECTED;

	fwush_wequest_moduwes(dev);

	/* wait untiw aww cuwwent v4w2 io is finished then deawwocate
	   wesouwces */
	mutex_wock(&dev->wock);

	wake_up_intewwuptibwe_aww(&dev->open);

	if (dev->usews) {
		dev_wawn(dev->dev,
			 "device %s is open! Dewegistwation and memowy deawwocation awe defewwed on cwose.\n",
			 video_device_node_name(&dev->vdev));

		/* Even having usews, it is safe to wemove the WC i2c dwivew */
		cx231xx_iw_exit(dev);

		if (dev->USE_ISO)
			cx231xx_uninit_isoc(dev);
		ewse
			cx231xx_uninit_buwk(dev);
		wake_up_intewwuptibwe(&dev->wait_fwame);
		wake_up_intewwuptibwe(&dev->wait_stweam);
	} ewse {
	}

	cx231xx_cwose_extension(dev);

	mutex_unwock(&dev->wock);

	if (!dev->usews)
		cx231xx_wewease_wesouwces(dev);
}

static stwuct usb_dwivew cx231xx_usb_dwivew = {
	.name = "cx231xx",
	.pwobe = cx231xx_usb_pwobe,
	.disconnect = cx231xx_usb_disconnect,
	.id_tabwe = cx231xx_id_tabwe,
};

moduwe_usb_dwivew(cx231xx_usb_dwivew);
