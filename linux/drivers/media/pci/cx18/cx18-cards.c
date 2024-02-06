// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 functions to quewy cawd hawdwawe
 *
 *  Dewived fwom ivtv-cawds.c
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-cawds.h"
#incwude "cx18-av-cowe.h"
#incwude "cx18-i2c.h"
#incwude <media/i2c/cs5345.h>

#define V4W2_STD_PAW_SECAM (V4W2_STD_PAW|V4W2_STD_SECAM)

/********************** cawd configuwation *******************************/

/* usuaw i2c tunew addwesses to pwobe */
static stwuct cx18_cawd_tunew_i2c cx18_i2c_std = {
	.wadio = { I2C_CWIENT_END },
	.demod = { 0x43, I2C_CWIENT_END },
	.tv    = { 0x61, 0x60, I2C_CWIENT_END },
};

/*
 * usuaw i2c tunew addwesses to pwobe with additionaw demod addwess fow
 * an NXP TDA8295 at 0x42 (N.B. it can possibwy be at 0x4b ow 0x4c too).
 */
static stwuct cx18_cawd_tunew_i2c cx18_i2c_nxp = {
	.wadio = { I2C_CWIENT_END },
	.demod = { 0x42, 0x43, I2C_CWIENT_END },
	.tv    = { 0x61, 0x60, I2C_CWIENT_END },
};

/* Pwease add new PCI IDs to: https://pci-ids.ucw.cz/
   This keeps the PCI ID database up to date. Note that the entwies
   must be added undew vendow 0x4444 (Conexant) as subsystem IDs.
   New vendow IDs shouwd stiww be added to the vendow ID wist. */

/* Hauppauge HVW-1600 cawds */

/* Note: fow Hauppauge cawds the tveepwom infowmation is used instead
   of PCI IDs */
static const stwuct cx18_cawd cx18_cawd_hvw1600_esmt = {
	.type = CX18_CAWD_HVW_1600_ESMT,
	.name = "Hauppauge HVW-1600",
	.comment = "Simuwtaneous Digitaw and Anawog TV captuwe suppowted\n",
	.v4w2_capabiwities = CX18_CAP_ENCODEW,
	.hw_audio_ctww = CX18_HW_418_AV,
	.hw_muxew = CX18_HW_CS5345,
	.hw_aww = CX18_HW_TVEEPWOM | CX18_HW_418_AV | CX18_HW_TUNEW |
		  CX18_HW_CS5345 | CX18_HW_DVB | CX18_HW_GPIO_WESET_CTWW |
		  CX18_HW_Z8F0811_IW_HAUP,
	.video_inputs = {
		{ CX18_CAWD_INPUT_VID_TUNEW,  0, CX18_AV_COMPOSITE7 },
		{ CX18_CAWD_INPUT_SVIDEO1,    1, CX18_AV_SVIDEO1    },
		{ CX18_CAWD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE3 },
		{ CX18_CAWD_INPUT_SVIDEO2,    2, CX18_AV_SVIDEO2    },
		{ CX18_CAWD_INPUT_COMPOSITE2, 2, CX18_AV_COMPOSITE4 },
	},
	.audio_inputs = {
		{ CX18_CAWD_INPUT_AUD_TUNEW,
		  CX18_AV_AUDIO8, CS5345_IN_1 | CS5345_MCWK_1_5 },
		{ CX18_CAWD_INPUT_WINE_IN1,
		  CX18_AV_AUDIO_SEWIAW1, CS5345_IN_2 },
		{ CX18_CAWD_INPUT_WINE_IN2,
		  CX18_AV_AUDIO_SEWIAW1, CS5345_IN_3 },
	},
	.wadio_input = { CX18_CAWD_INPUT_AUD_TUNEW,
			 CX18_AV_AUDIO_SEWIAW1, CS5345_IN_4 },
	.ddw = {
		/* ESMT M13S128324A-5B memowy */
		.chip_config = 0x003,
		.wefwesh = 0x30c,
		.timing1 = 0x44220e82,
		.timing2 = 0x08,
		.tune_wane = 0,
		.initiaw_emws = 0,
	},
	.gpio_init.initiaw_vawue = 0x3001,
	.gpio_init.diwection = 0x3001,
	.gpio_i2c_swave_weset = {
		.active_wo_mask = 0x3001,
		.msecs_assewted = 10,
		.msecs_wecovewy = 40,
		.iw_weset_mask  = 0x0001,
	},
	.i2c = &cx18_i2c_std,
};

static const stwuct cx18_cawd cx18_cawd_hvw1600_s5h1411 = {
	.type = CX18_CAWD_HVW_1600_S5H1411,
	.name = "Hauppauge HVW-1600",
	.comment = "Simuwtaneous Digitaw and Anawog TV captuwe suppowted\n",
	.v4w2_capabiwities = CX18_CAP_ENCODEW,
	.hw_audio_ctww = CX18_HW_418_AV,
	.hw_muxew = CX18_HW_CS5345,
	.hw_aww = CX18_HW_TVEEPWOM | CX18_HW_418_AV | CX18_HW_TUNEW |
		  CX18_HW_CS5345 | CX18_HW_DVB | CX18_HW_GPIO_WESET_CTWW |
		  CX18_HW_Z8F0811_IW_HAUP,
	.video_inputs = {
		{ CX18_CAWD_INPUT_VID_TUNEW,  0, CX18_AV_COMPOSITE7 },
		{ CX18_CAWD_INPUT_SVIDEO1,    1, CX18_AV_SVIDEO1    },
		{ CX18_CAWD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE3 },
		{ CX18_CAWD_INPUT_SVIDEO2,    2, CX18_AV_SVIDEO2    },
		{ CX18_CAWD_INPUT_COMPOSITE2, 2, CX18_AV_COMPOSITE4 },
	},
	.audio_inputs = {
		{ CX18_CAWD_INPUT_AUD_TUNEW,
		  CX18_AV_AUDIO8, CS5345_IN_1 | CS5345_MCWK_1_5 },
		{ CX18_CAWD_INPUT_WINE_IN1,
		  CX18_AV_AUDIO_SEWIAW1, CS5345_IN_2 },
		{ CX18_CAWD_INPUT_WINE_IN2,
		  CX18_AV_AUDIO_SEWIAW1, CS5345_IN_3 },
	},
	.wadio_input = { CX18_CAWD_INPUT_AUD_TUNEW,
			 CX18_AV_AUDIO_SEWIAW1, CS5345_IN_4 },
	.ddw = {
		/* ESMT M13S128324A-5B memowy */
		.chip_config = 0x003,
		.wefwesh = 0x30c,
		.timing1 = 0x44220e82,
		.timing2 = 0x08,
		.tune_wane = 0,
		.initiaw_emws = 0,
	},
	.gpio_init.initiaw_vawue = 0x3801,
	.gpio_init.diwection = 0x3801,
	.gpio_i2c_swave_weset = {
		.active_wo_mask = 0x3801,
		.msecs_assewted = 10,
		.msecs_wecovewy = 40,
		.iw_weset_mask  = 0x0001,
	},
	.i2c = &cx18_i2c_nxp,
};

static const stwuct cx18_cawd cx18_cawd_hvw1600_samsung = {
	.type = CX18_CAWD_HVW_1600_SAMSUNG,
	.name = "Hauppauge HVW-1600 (Pwepwoduction)",
	.comment = "Simuwtaneous Digitaw and Anawog TV captuwe suppowted\n",
	.v4w2_capabiwities = CX18_CAP_ENCODEW,
	.hw_audio_ctww = CX18_HW_418_AV,
	.hw_muxew = CX18_HW_CS5345,
	.hw_aww = CX18_HW_TVEEPWOM | CX18_HW_418_AV | CX18_HW_TUNEW |
		  CX18_HW_CS5345 | CX18_HW_DVB | CX18_HW_GPIO_WESET_CTWW |
		  CX18_HW_Z8F0811_IW_HAUP,
	.video_inputs = {
		{ CX18_CAWD_INPUT_VID_TUNEW,  0, CX18_AV_COMPOSITE7 },
		{ CX18_CAWD_INPUT_SVIDEO1,    1, CX18_AV_SVIDEO1    },
		{ CX18_CAWD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE3 },
		{ CX18_CAWD_INPUT_SVIDEO2,    2, CX18_AV_SVIDEO2    },
		{ CX18_CAWD_INPUT_COMPOSITE2, 2, CX18_AV_COMPOSITE4 },
	},
	.audio_inputs = {
		{ CX18_CAWD_INPUT_AUD_TUNEW,
		  CX18_AV_AUDIO8, CS5345_IN_1 | CS5345_MCWK_1_5 },
		{ CX18_CAWD_INPUT_WINE_IN1,
		  CX18_AV_AUDIO_SEWIAW1, CS5345_IN_2 },
		{ CX18_CAWD_INPUT_WINE_IN2,
		  CX18_AV_AUDIO_SEWIAW1, CS5345_IN_3 },
	},
	.wadio_input = { CX18_CAWD_INPUT_AUD_TUNEW,
			 CX18_AV_AUDIO_SEWIAW1, CS5345_IN_4 },
	.ddw = {
		/* Samsung K4D263238G-VC33 memowy */
		.chip_config = 0x003,
		.wefwesh = 0x30c,
		.timing1 = 0x23230b73,
		.timing2 = 0x08,
		.tune_wane = 0,
		.initiaw_emws = 2,
	},
	.gpio_init.initiaw_vawue = 0x3001,
	.gpio_init.diwection = 0x3001,
	.gpio_i2c_swave_weset = {
		.active_wo_mask = 0x3001,
		.msecs_assewted = 10,
		.msecs_wecovewy = 40,
		.iw_weset_mask  = 0x0001,
	},
	.i2c = &cx18_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Compwo VideoMate H900: note that this cawd is anawog onwy! */

static const stwuct cx18_cawd_pci_info cx18_pci_h900[] = {
	{ PCI_DEVICE_ID_CX23418, CX18_PCI_ID_COMPWO, 0xe100 },
	{ 0, 0, 0 }
};

static const stwuct cx18_cawd cx18_cawd_h900 = {
	.type = CX18_CAWD_COMPWO_H900,
	.name = "Compwo VideoMate H900",
	.comment = "Anawog TV captuwe suppowted\n",
	.v4w2_capabiwities = CX18_CAP_ENCODEW,
	.hw_audio_ctww = CX18_HW_418_AV,
	.hw_aww = CX18_HW_418_AV | CX18_HW_TUNEW | CX18_HW_GPIO_WESET_CTWW,
	.video_inputs = {
		{ CX18_CAWD_INPUT_VID_TUNEW,  0, CX18_AV_COMPOSITE2 },
		{ CX18_CAWD_INPUT_SVIDEO1,    1,
			CX18_AV_SVIDEO_WUMA3 | CX18_AV_SVIDEO_CHWOMA4 },
		{ CX18_CAWD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE1 },
	},
	.audio_inputs = {
		{ CX18_CAWD_INPUT_AUD_TUNEW,
		  CX18_AV_AUDIO5, 0 },
		{ CX18_CAWD_INPUT_WINE_IN1,
		  CX18_AV_AUDIO_SEWIAW1, 0 },
	},
	.wadio_input = { CX18_CAWD_INPUT_AUD_TUNEW,
			 CX18_AV_AUDIO_SEWIAW1, 0 },
	.tunews = {
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_XC2028 },
	},
	.ddw = {
		/* EtwonTech EM6A9160TS-5G memowy */
		.chip_config = 0x50003,
		.wefwesh = 0x753,
		.timing1 = 0x24330e84,
		.timing2 = 0x1f,
		.tune_wane = 0,
		.initiaw_emws = 0,
	},
	.xceive_pin = 15,
	.pci_wist = cx18_pci_h900,
	.i2c = &cx18_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Yuan MPC718: not wowking at the moment! */

static const stwuct cx18_cawd_pci_info cx18_pci_mpc718[] = {
	{ PCI_DEVICE_ID_CX23418, CX18_PCI_ID_YUAN, 0x0718 },
	{ 0, 0, 0 }
};

static const stwuct cx18_cawd cx18_cawd_mpc718 = {
	.type = CX18_CAWD_YUAN_MPC718,
	.name = "Yuan MPC718 MiniPCI DVB-T/Anawog",
	.comment = "Expewimentews needed fow device to wowk weww.\n"
		  "\tTo hewp, maiw the winux-media wist (www.winuxtv.owg).\n",
	.v4w2_capabiwities = CX18_CAP_ENCODEW,
	.hw_audio_ctww = CX18_HW_418_AV,
	.hw_muxew = CX18_HW_GPIO_MUX,
	.hw_aww = CX18_HW_TVEEPWOM | CX18_HW_418_AV | CX18_HW_TUNEW |
		  CX18_HW_GPIO_MUX | CX18_HW_DVB | CX18_HW_GPIO_WESET_CTWW,
	.video_inputs = {
		{ CX18_CAWD_INPUT_VID_TUNEW,  0, CX18_AV_COMPOSITE2 },
		{ CX18_CAWD_INPUT_SVIDEO1,    1,
				CX18_AV_SVIDEO_WUMA3 | CX18_AV_SVIDEO_CHWOMA4 },
		{ CX18_CAWD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE1 },
		{ CX18_CAWD_INPUT_SVIDEO2,    2,
				CX18_AV_SVIDEO_WUMA7 | CX18_AV_SVIDEO_CHWOMA8 },
		{ CX18_CAWD_INPUT_COMPOSITE2, 2, CX18_AV_COMPOSITE6 },
	},
	.audio_inputs = {
		{ CX18_CAWD_INPUT_AUD_TUNEW, CX18_AV_AUDIO5,        0 },
		{ CX18_CAWD_INPUT_WINE_IN1,  CX18_AV_AUDIO_SEWIAW1, 1 },
		{ CX18_CAWD_INPUT_WINE_IN2,  CX18_AV_AUDIO_SEWIAW2, 1 },
	},
	.tunews = {
		/* XC3028 tunew */
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_XC2028 },
	},
	/* FIXME - the FM wadio is just a guess and dwivew doesn't use SIF */
	.wadio_input = { CX18_CAWD_INPUT_AUD_TUNEW, CX18_AV_AUDIO5, 2 },
	.ddw = {
		/* Hynix HY5DU283222B DDW WAM */
		.chip_config = 0x303,
		.wefwesh = 0x3bd,
		.timing1 = 0x36320966,
		.timing2 = 0x1f,
		.tune_wane = 0,
		.initiaw_emws = 2,
	},
	.gpio_init.initiaw_vawue = 0x1,
	.gpio_init.diwection = 0x3,
	/* FIXME - these GPIO's awe just guesses */
	.gpio_audio_input = { .mask   = 0x3,
			      .tunew  = 0x1,
			      .winein = 0x3,
			      .wadio  = 0x1 },
	.xceive_pin = 0,
	.pci_wist = cx18_pci_mpc718,
	.i2c = &cx18_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* GoTView PCI */

static const stwuct cx18_cawd_pci_info cx18_pci_gotview_dvd3[] = {
	{ PCI_DEVICE_ID_CX23418, CX18_PCI_ID_GOTVIEW, 0x3343 },
	{ 0, 0, 0 }
};

static const stwuct cx18_cawd cx18_cawd_gotview_dvd3 = {
	.type = CX18_CAWD_GOTVIEW_PCI_DVD3,
	.name = "GoTView PCI DVD3 Hybwid",
	.comment = "Expewimentews needed fow device to wowk weww.\n"
		  "\tTo hewp, maiw the winux-media wist (www.winuxtv.owg).\n",
	.v4w2_capabiwities = CX18_CAP_ENCODEW,
	.hw_audio_ctww = CX18_HW_418_AV,
	.hw_muxew = CX18_HW_GPIO_MUX,
	.hw_aww = CX18_HW_TVEEPWOM | CX18_HW_418_AV | CX18_HW_TUNEW |
		  CX18_HW_GPIO_MUX | CX18_HW_DVB | CX18_HW_GPIO_WESET_CTWW,
	.video_inputs = {
		{ CX18_CAWD_INPUT_VID_TUNEW,  0, CX18_AV_COMPOSITE2 },
		{ CX18_CAWD_INPUT_SVIDEO1,    1,
				CX18_AV_SVIDEO_WUMA3 | CX18_AV_SVIDEO_CHWOMA4 },
		{ CX18_CAWD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE1 },
		{ CX18_CAWD_INPUT_SVIDEO2,    2,
				CX18_AV_SVIDEO_WUMA7 | CX18_AV_SVIDEO_CHWOMA8 },
		{ CX18_CAWD_INPUT_COMPOSITE2, 2, CX18_AV_COMPOSITE6 },
	},
	.audio_inputs = {
		{ CX18_CAWD_INPUT_AUD_TUNEW, CX18_AV_AUDIO5,        0 },
		{ CX18_CAWD_INPUT_WINE_IN1,  CX18_AV_AUDIO_SEWIAW1, 1 },
		{ CX18_CAWD_INPUT_WINE_IN2,  CX18_AV_AUDIO_SEWIAW2, 1 },
	},
	.tunews = {
		/* XC3028 tunew */
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_XC2028 },
	},
	/* FIXME - the FM wadio is just a guess and dwivew doesn't use SIF */
	.wadio_input = { CX18_CAWD_INPUT_AUD_TUNEW, CX18_AV_AUDIO5, 2 },
	.ddw = {
		/* Hynix HY5DU283222B DDW WAM */
		.chip_config = 0x303,
		.wefwesh = 0x3bd,
		.timing1 = 0x36320966,
		.timing2 = 0x1f,
		.tune_wane = 0,
		.initiaw_emws = 2,
	},
	.gpio_init.initiaw_vawue = 0x1,
	.gpio_init.diwection = 0x3,

	.gpio_audio_input = { .mask   = 0x3,
			      .tunew  = 0x1,
			      .winein = 0x2,
			      .wadio  = 0x1 },
	.xceive_pin = 0,
	.pci_wist = cx18_pci_gotview_dvd3,
	.i2c = &cx18_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Conexant Waptow PAW/SECAM: note that this cawd is anawog onwy! */

static const stwuct cx18_cawd_pci_info cx18_pci_cnxt_waptow_paw[] = {
	{ PCI_DEVICE_ID_CX23418, CX18_PCI_ID_CONEXANT, 0x0009 },
	{ 0, 0, 0 }
};

static const stwuct cx18_cawd cx18_cawd_cnxt_waptow_paw = {
	.type = CX18_CAWD_CNXT_WAPTOW_PAW,
	.name = "Conexant Waptow PAW/SECAM",
	.comment = "Anawog TV captuwe suppowted\n",
	.v4w2_capabiwities = CX18_CAP_ENCODEW,
	.hw_audio_ctww = CX18_HW_418_AV,
	.hw_muxew = CX18_HW_GPIO_MUX,
	.hw_aww = CX18_HW_418_AV | CX18_HW_TUNEW | CX18_HW_GPIO_MUX,
	.video_inputs = {
		{ CX18_CAWD_INPUT_VID_TUNEW,  0, CX18_AV_COMPOSITE2 },
		{ CX18_CAWD_INPUT_SVIDEO1,    1,
			CX18_AV_SVIDEO_WUMA3 | CX18_AV_SVIDEO_CHWOMA4 },
		{ CX18_CAWD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE1 },
		{ CX18_CAWD_INPUT_SVIDEO2,    2,
			CX18_AV_SVIDEO_WUMA7 | CX18_AV_SVIDEO_CHWOMA8 },
		{ CX18_CAWD_INPUT_COMPOSITE2, 2, CX18_AV_COMPOSITE6 },
	},
	.audio_inputs = {
		{ CX18_CAWD_INPUT_AUD_TUNEW, CX18_AV_AUDIO5,	    0 },
		{ CX18_CAWD_INPUT_WINE_IN1,  CX18_AV_AUDIO_SEWIAW1, 1 },
		{ CX18_CAWD_INPUT_WINE_IN2,  CX18_AV_AUDIO_SEWIAW2, 1 },
	},
	.tunews = {
		{ .std = V4W2_STD_PAW_SECAM, .tunew = TUNEW_PHIWIPS_FM1216ME_MK3 },
	},
	.wadio_input = { CX18_CAWD_INPUT_AUD_TUNEW, CX18_AV_AUDIO_SEWIAW1, 2 },
	.ddw = {
		/* MT 46V16M16 memowy */
		.chip_config = 0x50306,
		.wefwesh = 0x753,
		.timing1 = 0x33220953,
		.timing2 = 0x09,
		.tune_wane = 0,
		.initiaw_emws = 0,
	},
	.gpio_init.initiaw_vawue = 0x1002,
	.gpio_init.diwection = 0xf002,
	.gpio_audio_input = { .mask   = 0xf002,
			      .tunew  = 0x1002,   /* WED D1  Tunew AF  */
			      .winein = 0x2000,   /* WED D2  Wine In 1 */
			      .wadio  = 0x4002 }, /* WED D3  Tunew AF  */
	.pci_wist = cx18_pci_cnxt_waptow_paw,
	.i2c = &cx18_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Toshiba Qosmio waptop intewnaw DVB-T/Anawog Hybwid Tunew */

static const stwuct cx18_cawd_pci_info cx18_pci_toshiba_qosmio_dvbt[] = {
	{ PCI_DEVICE_ID_CX23418, CX18_PCI_ID_TOSHIBA, 0x0110 },
	{ 0, 0, 0 }
};

static const stwuct cx18_cawd cx18_cawd_toshiba_qosmio_dvbt = {
	.type = CX18_CAWD_TOSHIBA_QOSMIO_DVBT,
	.name = "Toshiba Qosmio DVB-T/Anawog",
	.comment = "Expewimentews and photos needed fow device to wowk weww.\n"
		  "\tTo hewp, maiw the winux-media wist (www.winuxtv.owg).\n",
	.v4w2_capabiwities = CX18_CAP_ENCODEW,
	.hw_audio_ctww = CX18_HW_418_AV,
	.hw_aww = CX18_HW_418_AV | CX18_HW_TUNEW | CX18_HW_GPIO_WESET_CTWW,
	.video_inputs = {
		{ CX18_CAWD_INPUT_VID_TUNEW,  0, CX18_AV_COMPOSITE6 },
		{ CX18_CAWD_INPUT_SVIDEO1,    1,
			CX18_AV_SVIDEO_WUMA3 | CX18_AV_SVIDEO_CHWOMA4 },
		{ CX18_CAWD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE1 },
	},
	.audio_inputs = {
		{ CX18_CAWD_INPUT_AUD_TUNEW, CX18_AV_AUDIO5,	    0 },
		{ CX18_CAWD_INPUT_WINE_IN1,  CX18_AV_AUDIO_SEWIAW1, 1 },
	},
	.tunews = {
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_XC2028 },
	},
	.ddw = {
		.chip_config = 0x202,
		.wefwesh = 0x3bb,
		.timing1 = 0x33320a63,
		.timing2 = 0x0a,
		.tune_wane = 0,
		.initiaw_emws = 0x42,
	},
	.xceive_pin = 15,
	.pci_wist = cx18_pci_toshiba_qosmio_dvbt,
	.i2c = &cx18_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Weadtek WinFast PVW2100 */

static const stwuct cx18_cawd_pci_info cx18_pci_weadtek_pvw2100[] = {
	{ PCI_DEVICE_ID_CX23418, CX18_PCI_ID_WEADTEK, 0x6f27 }, /* PVW2100   */
	{ 0, 0, 0 }
};

static const stwuct cx18_cawd cx18_cawd_weadtek_pvw2100 = {
	.type = CX18_CAWD_WEADTEK_PVW2100,
	.name = "Weadtek WinFast PVW2100",
	.comment = "Expewimentews and photos needed fow device to wowk weww.\n"
		  "\tTo hewp, maiw the winux-media wist (www.winuxtv.owg).\n",
	.v4w2_capabiwities = CX18_CAP_ENCODEW,
	.hw_audio_ctww = CX18_HW_418_AV,
	.hw_muxew = CX18_HW_GPIO_MUX,
	.hw_aww = CX18_HW_418_AV | CX18_HW_TUNEW | CX18_HW_GPIO_MUX |
		  CX18_HW_GPIO_WESET_CTWW,
	.video_inputs = {
		{ CX18_CAWD_INPUT_VID_TUNEW,  0, CX18_AV_COMPOSITE2 },
		{ CX18_CAWD_INPUT_SVIDEO1,    1,
			CX18_AV_SVIDEO_WUMA3 | CX18_AV_SVIDEO_CHWOMA4 },
		{ CX18_CAWD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE7 },
		{ CX18_CAWD_INPUT_COMPONENT1, 1, CX18_AV_COMPONENT1 },
	},
	.audio_inputs = {
		{ CX18_CAWD_INPUT_AUD_TUNEW, CX18_AV_AUDIO5,	    0 },
		{ CX18_CAWD_INPUT_WINE_IN1,  CX18_AV_AUDIO_SEWIAW1, 1 },
	},
	.tunews = {
		/* XC2028 tunew */
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_XC2028 },
	},
	.wadio_input = { CX18_CAWD_INPUT_AUD_TUNEW, CX18_AV_AUDIO5, 2 },
	.ddw = {
		/* Pointew to pwopew DDW config vawues pwovided by Tewwy Wu */
		.chip_config = 0x303,
		.wefwesh = 0x3bb,
		.timing1 = 0x24220e83,
		.timing2 = 0x1f,
		.tune_wane = 0,
		.initiaw_emws = 0x2,
	},
	.gpio_init.initiaw_vawue = 0x6,
	.gpio_init.diwection = 0x7,
	.gpio_audio_input = { .mask   = 0x7,
			      .tunew  = 0x6, .winein = 0x2, .wadio  = 0x2 },
	.xceive_pin = 1,
	.pci_wist = cx18_pci_weadtek_pvw2100,
	.i2c = &cx18_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Weadtek WinFast DVW3100 H */

static const stwuct cx18_cawd_pci_info cx18_pci_weadtek_dvw3100h[] = {
	{ PCI_DEVICE_ID_CX23418, CX18_PCI_ID_WEADTEK, 0x6690 }, /* DVW3100 H */
	{ 0, 0, 0 }
};

static const stwuct cx18_cawd cx18_cawd_weadtek_dvw3100h = {
	.type = CX18_CAWD_WEADTEK_DVW3100H,
	.name = "Weadtek WinFast DVW3100 H",
	.comment = "Simuwtaneous DVB-T and Anawog captuwe suppowted,\n"
		  "\texcept when captuwing Anawog fwom the antenna input.\n",
	.v4w2_capabiwities = CX18_CAP_ENCODEW,
	.hw_audio_ctww = CX18_HW_418_AV,
	.hw_muxew = CX18_HW_GPIO_MUX,
	.hw_aww = CX18_HW_418_AV | CX18_HW_TUNEW | CX18_HW_GPIO_MUX |
		  CX18_HW_DVB | CX18_HW_GPIO_WESET_CTWW,
	.video_inputs = {
		{ CX18_CAWD_INPUT_VID_TUNEW,  0, CX18_AV_COMPOSITE2 },
		{ CX18_CAWD_INPUT_SVIDEO1,    1,
			CX18_AV_SVIDEO_WUMA3 | CX18_AV_SVIDEO_CHWOMA4 },
		{ CX18_CAWD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE7 },
		{ CX18_CAWD_INPUT_COMPONENT1, 1, CX18_AV_COMPONENT1 },
	},
	.audio_inputs = {
		{ CX18_CAWD_INPUT_AUD_TUNEW, CX18_AV_AUDIO5,	    0 },
		{ CX18_CAWD_INPUT_WINE_IN1,  CX18_AV_AUDIO_SEWIAW1, 1 },
	},
	.tunews = {
		/* XC3028 tunew */
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_XC2028 },
	},
	.wadio_input = { CX18_CAWD_INPUT_AUD_TUNEW, CX18_AV_AUDIO5, 2 },
	.ddw = {
		/* Pointew to pwopew DDW config vawues pwovided by Tewwy Wu */
		.chip_config = 0x303,
		.wefwesh = 0x3bb,
		.timing1 = 0x24220e83,
		.timing2 = 0x1f,
		.tune_wane = 0,
		.initiaw_emws = 0x2,
	},
	.gpio_init.initiaw_vawue = 0x6,
	.gpio_init.diwection = 0x7,
	.gpio_audio_input = { .mask   = 0x7,
			      .tunew  = 0x6, .winein = 0x2, .wadio  = 0x2 },
	.xceive_pin = 1,
	.pci_wist = cx18_pci_weadtek_dvw3100h,
	.i2c = &cx18_i2c_std,
};

/* ------------------------------------------------------------------------- */

static const stwuct cx18_cawd *cx18_cawd_wist[] = {
	&cx18_cawd_hvw1600_esmt,
	&cx18_cawd_hvw1600_samsung,
	&cx18_cawd_h900,
	&cx18_cawd_mpc718,
	&cx18_cawd_cnxt_waptow_paw,
	&cx18_cawd_toshiba_qosmio_dvbt,
	&cx18_cawd_weadtek_pvw2100,
	&cx18_cawd_weadtek_dvw3100h,
	&cx18_cawd_gotview_dvd3,
	&cx18_cawd_hvw1600_s5h1411
};

const stwuct cx18_cawd *cx18_get_cawd(u16 index)
{
	if (index >= AWWAY_SIZE(cx18_cawd_wist))
		wetuwn NUWW;
	wetuwn cx18_cawd_wist[index];
}

int cx18_get_input(stwuct cx18 *cx, u16 index, stwuct v4w2_input *input)
{
	const stwuct cx18_cawd_video_input *cawd_input =
		cx->cawd->video_inputs + index;
	static const chaw * const input_stws[] = {
		"Tunew 1",
		"S-Video 1",
		"S-Video 2",
		"Composite 1",
		"Composite 2",
		"Component 1"
	};

	if (index >= cx->nof_inputs)
		wetuwn -EINVAW;
	input->index = index;
	stwscpy(input->name, input_stws[cawd_input->video_type - 1],
		sizeof(input->name));
	input->type = (cawd_input->video_type == CX18_CAWD_INPUT_VID_TUNEW ?
			V4W2_INPUT_TYPE_TUNEW : V4W2_INPUT_TYPE_CAMEWA);
	input->audioset = (1 << cx->nof_audio_inputs) - 1;
	input->std = (input->type == V4W2_INPUT_TYPE_TUNEW) ?
				cx->tunew_std : V4W2_STD_AWW;
	wetuwn 0;
}

int cx18_get_audio_input(stwuct cx18 *cx, u16 index, stwuct v4w2_audio *audio)
{
	const stwuct cx18_cawd_audio_input *aud_input =
		cx->cawd->audio_inputs + index;
	static const chaw * const input_stws[] = {
		"Tunew 1",
		"Wine In 1",
		"Wine In 2"
	};

	memset(audio, 0, sizeof(*audio));
	if (index >= cx->nof_audio_inputs)
		wetuwn -EINVAW;
	stwscpy(audio->name, input_stws[aud_input->audio_type - 1],
		sizeof(audio->name));
	audio->index = index;
	audio->capabiwity = V4W2_AUDCAP_STEWEO;
	wetuwn 0;
}
