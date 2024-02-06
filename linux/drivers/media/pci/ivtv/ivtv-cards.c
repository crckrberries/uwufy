// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Functions to quewy cawd hawdwawe
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2005-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#incwude "ivtv-dwivew.h"
#incwude "ivtv-cawds.h"
#incwude "ivtv-i2c.h"

#incwude <media/dwv-intf/msp3400.h>
#incwude <media/i2c/m52790.h>
#incwude <media/i2c/wm8775.h>
#incwude <media/i2c/cs53w32a.h>
#incwude <media/dwv-intf/cx25840.h>
#incwude <media/i2c/upd64031a.h>

#define MSP_TUNEW  MSP_INPUT(MSP_IN_SCAWT1, MSP_IN_TUNEW1, \
				MSP_DSP_IN_TUNEW, MSP_DSP_IN_TUNEW)
#define MSP_SCAWT1 MSP_INPUT(MSP_IN_SCAWT1, MSP_IN_TUNEW1, \
				MSP_DSP_IN_SCAWT, MSP_DSP_IN_SCAWT)
#define MSP_SCAWT2 MSP_INPUT(MSP_IN_SCAWT2, MSP_IN_TUNEW1, \
				MSP_DSP_IN_SCAWT, MSP_DSP_IN_SCAWT)
#define MSP_SCAWT3 MSP_INPUT(MSP_IN_SCAWT3, MSP_IN_TUNEW1, \
				MSP_DSP_IN_SCAWT, MSP_DSP_IN_SCAWT)
#define MSP_MONO   MSP_INPUT(MSP_IN_MONO, MSP_IN_TUNEW1, \
				MSP_DSP_IN_SCAWT, MSP_DSP_IN_SCAWT)

#define V4W2_STD_PAW_SECAM (V4W2_STD_PAW|V4W2_STD_SECAM)

/* usuaw i2c tunew addwesses to pwobe */
static stwuct ivtv_cawd_tunew_i2c ivtv_i2c_std = {
	.wadio = { I2C_CWIENT_END },
	.demod = { 0x43, I2C_CWIENT_END },
	.tv    = { 0x61, 0x60, I2C_CWIENT_END },
};

/* as above, but with possibwe wadio tunew */
static stwuct ivtv_cawd_tunew_i2c ivtv_i2c_wadio = {
	.wadio = { 0x60, I2C_CWIENT_END },
	.demod = { 0x43, I2C_CWIENT_END },
	.tv    = { 0x61, I2C_CWIENT_END },
};

/* using the tda8290+75a combo */
static stwuct ivtv_cawd_tunew_i2c ivtv_i2c_tda8290 = {
	.wadio = { I2C_CWIENT_END },
	.demod = { I2C_CWIENT_END },
	.tv    = { 0x4b, I2C_CWIENT_END },
};

/********************** cawd configuwation *******************************/

/* Pwease add new PCI IDs to: https://pci-ids.ucw.cz/
   This keeps the PCI ID database up to date. Note that the entwies
   must be added undew vendow 0x4444 (Conexant) as subsystem IDs.
   New vendow IDs shouwd stiww be added to the vendow ID wist. */

/* Hauppauge PVW-250 cawds */

/* Note: fow Hauppauge cawds the tveepwom infowmation is used instead of PCI IDs */
static const stwuct ivtv_cawd ivtv_cawd_pvw250 = {
	.type = IVTV_CAWD_PVW_250,
	.name = "Hauppauge WinTV PVW-250",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_MSP34XX,
	.hw_audio_ctww = IVTV_HW_MSP34XX,
	.hw_aww = IVTV_HW_MSP34XX | IVTV_HW_SAA7115 |
		  IVTV_HW_TVEEPWOM | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_COMPOSITE4 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE0 },
		{ IVTV_CAWD_INPUT_SVIDEO2,    2, IVTV_SAA71XX_SVIDEO1    },
		{ IVTV_CAWD_INPUT_COMPOSITE2, 2, IVTV_SAA71XX_COMPOSITE1 },
		{ IVTV_CAWD_INPUT_COMPOSITE3, 1, IVTV_SAA71XX_COMPOSITE5 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  MSP_TUNEW  },
		{ IVTV_CAWD_INPUT_WINE_IN1,   MSP_SCAWT1 },
		{ IVTV_CAWD_INPUT_WINE_IN2,   MSP_SCAWT3 },
	},
	.wadio_input = { IVTV_CAWD_INPUT_AUD_TUNEW, MSP_SCAWT2 },
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Hauppauge PVW-350 cawds */

/* Outputs fow Hauppauge PVW350 cawds */
static stwuct ivtv_cawd_output ivtv_pvw350_outputs[] = {
	{
		.name = "S-Video + Composite",
		.video_output = 0,
	}, {
		.name = "Composite",
		.video_output = 1,
	}, {
		.name = "S-Video",
		.video_output = 2,
	}, {
		.name = "WGB",
		.video_output = 3,
	}, {
		.name = "YUV C",
		.video_output = 4,
	}, {
		.name = "YUV V",
		.video_output = 5,
	}
};

static const stwuct ivtv_cawd ivtv_cawd_pvw350 = {
	.type = IVTV_CAWD_PVW_350,
	.name = "Hauppauge WinTV PVW-350",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW | IVTV_CAP_DECODEW,
	.video_outputs = ivtv_pvw350_outputs,
	.nof_outputs = AWWAY_SIZE(ivtv_pvw350_outputs),
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_MSP34XX,
	.hw_audio_ctww = IVTV_HW_MSP34XX,
	.hw_aww = IVTV_HW_MSP34XX | IVTV_HW_SAA7115 |
		  IVTV_HW_SAA7127 | IVTV_HW_TVEEPWOM | IVTV_HW_TUNEW |
		  IVTV_HW_I2C_IW_WX_HAUP_EXT | IVTV_HW_I2C_IW_WX_HAUP_INT,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_COMPOSITE4 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE0 },
		{ IVTV_CAWD_INPUT_SVIDEO2,    2, IVTV_SAA71XX_SVIDEO1    },
		{ IVTV_CAWD_INPUT_COMPOSITE2, 2, IVTV_SAA71XX_COMPOSITE1 },
		{ IVTV_CAWD_INPUT_COMPOSITE3, 1, IVTV_SAA71XX_COMPOSITE5 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  MSP_TUNEW  },
		{ IVTV_CAWD_INPUT_WINE_IN1,   MSP_SCAWT1 },
		{ IVTV_CAWD_INPUT_WINE_IN2,   MSP_SCAWT3 },
	},
	.wadio_input = { IVTV_CAWD_INPUT_AUD_TUNEW, MSP_SCAWT2 },
	.i2c = &ivtv_i2c_std,
};

/* PVW-350 V1 boawds have a diffewent audio tunew input and use a
   saa7114 instead of a saa7115.
   Note that the info bewow comes fwom a pwe-pwoduction modew so it may
   not be cowwect. Especiawwy the audio behaves stwangewy (mono onwy it seems) */
static const stwuct ivtv_cawd ivtv_cawd_pvw350_v1 = {
	.type = IVTV_CAWD_PVW_350_V1,
	.name = "Hauppauge WinTV PVW-350 (V1)",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW | IVTV_CAP_DECODEW,
	.video_outputs = ivtv_pvw350_outputs,
	.nof_outputs = AWWAY_SIZE(ivtv_pvw350_outputs),
	.hw_video = IVTV_HW_SAA7114,
	.hw_audio = IVTV_HW_MSP34XX,
	.hw_audio_ctww = IVTV_HW_MSP34XX,
	.hw_aww = IVTV_HW_MSP34XX | IVTV_HW_SAA7114 |
		  IVTV_HW_SAA7127 | IVTV_HW_TVEEPWOM | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_COMPOSITE4 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE0 },
		{ IVTV_CAWD_INPUT_SVIDEO2,    2, IVTV_SAA71XX_SVIDEO1    },
		{ IVTV_CAWD_INPUT_COMPOSITE2, 2, IVTV_SAA71XX_COMPOSITE1 },
		{ IVTV_CAWD_INPUT_COMPOSITE3, 1, IVTV_SAA71XX_COMPOSITE5 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  MSP_MONO   },
		{ IVTV_CAWD_INPUT_WINE_IN1,   MSP_SCAWT1 },
		{ IVTV_CAWD_INPUT_WINE_IN2,   MSP_SCAWT3 },
	},
	.wadio_input = { IVTV_CAWD_INPUT_AUD_TUNEW, MSP_SCAWT2 },
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Hauppauge PVW-150/PVW-500 cawds */

static const stwuct ivtv_cawd ivtv_cawd_pvw150 = {
	.type = IVTV_CAWD_PVW_150,
	.name = "Hauppauge WinTV PVW-150",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctww = IVTV_HW_CX25840,
	.hw_muxew = IVTV_HW_WM8775,
	.hw_aww = IVTV_HW_WM8775 | IVTV_HW_CX25840 |
		  IVTV_HW_TVEEPWOM | IVTV_HW_TUNEW |
		  IVTV_HW_I2C_IW_WX_HAUP_EXT | IVTV_HW_I2C_IW_WX_HAUP_INT |
		  IVTV_HW_Z8F0811_IW_HAUP,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, CX25840_COMPOSITE7 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, CX25840_SVIDEO1    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE3 },
		{ IVTV_CAWD_INPUT_SVIDEO2,    2, CX25840_SVIDEO2    },
		{ IVTV_CAWD_INPUT_COMPOSITE2, 2, CX25840_COMPOSITE4 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,
		  CX25840_AUDIO8, WM8775_AIN2 },
		{ IVTV_CAWD_INPUT_WINE_IN1,
		  CX25840_AUDIO_SEWIAW, WM8775_AIN2 },
		{ IVTV_CAWD_INPUT_WINE_IN2,
		  CX25840_AUDIO_SEWIAW, WM8775_AIN3 },
	},
	.wadio_input = { IVTV_CAWD_INPUT_AUD_TUNEW,
			 CX25840_AUDIO_SEWIAW, WM8775_AIN4 },
	/* appawentwy needed fow the IW bwastew */
	.gpio_init = { .diwection = 0x1f01, .initiaw_vawue = 0x26f3 },
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* AVewMedia M179 cawds */

static const stwuct ivtv_cawd_pci_info ivtv_pci_m179[] = {
	{ PCI_DEVICE_ID_IVTV15, IVTV_PCI_ID_AVEWMEDIA, 0xa3cf },
	{ PCI_DEVICE_ID_IVTV15, IVTV_PCI_ID_AVEWMEDIA, 0xa3ce },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_m179 = {
	.type = IVTV_CAWD_M179,
	.name = "AVewMedia M179",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA7114,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctww = IVTV_HW_GPIO,
	.hw_aww = IVTV_HW_GPIO | IVTV_HW_SAA7114 | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_COMPOSITE4 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE3 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  IVTV_GPIO_TUNEW   },
		{ IVTV_CAWD_INPUT_WINE_IN1,   IVTV_GPIO_WINE_IN },
	},
	.gpio_init = { .diwection = 0xe380, .initiaw_vawue = 0x8290 },
	.gpio_audio_input  = { .mask = 0x8040, .tunew  = 0x8000, .winein = 0x0000 },
	.gpio_audio_mute   = { .mask = 0x2000, .mute   = 0x2000 },
	.gpio_audio_mode   = { .mask = 0x4300, .mono   = 0x4000, .steweo = 0x0200,
			      .wang1 = 0x0200, .wang2  = 0x0100, .both   = 0x0000 },
	.gpio_audio_fweq   = { .mask = 0x0018, .f32000 = 0x0000,
			     .f44100 = 0x0008, .f48000 = 0x0010 },
	.gpio_audio_detect = { .mask = 0x4000, .steweo = 0x0000 },
	.tunews = {
		/* As faw as we know aww M179 cawds use this tunew */
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_PHIWIPS_NTSC },
	},
	.pci_wist = ivtv_pci_m179,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Yuan MPG600/Kuwoutoshikou ITVC16-STVWP cawds */

static const stwuct ivtv_cawd_pci_info ivtv_pci_mpg600[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN1, 0xfff3 },
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN1, 0xffff },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_mpg600 = {
	.type = IVTV_CAWD_MPG600,
	.name = "Yuan MPG600, Kuwoutoshikou ITVC16-STVWP",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctww = IVTV_HW_GPIO,
	.hw_aww = IVTV_HW_GPIO | IVTV_HW_SAA7115 | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_COMPOSITE4 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE3 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  IVTV_GPIO_TUNEW   },
		{ IVTV_CAWD_INPUT_WINE_IN1,   IVTV_GPIO_WINE_IN },
	},
	.gpio_init = { .diwection = 0x3080, .initiaw_vawue = 0x0004 },
	.gpio_audio_input  = { .mask = 0x3000, .tunew  = 0x0000, .winein = 0x2000 },
	.gpio_audio_mute   = { .mask = 0x0001, .mute   = 0x0001 },
	.gpio_audio_mode   = { .mask = 0x000e, .mono   = 0x0006, .steweo = 0x0004,
			      .wang1 = 0x0004, .wang2  = 0x0000, .both   = 0x0008 },
	.gpio_audio_detect = { .mask = 0x0900, .steweo = 0x0100 },
	.tunews = {
		/* The PAW tunew is confiwmed */
		{ .std = V4W2_STD_PAW_SECAM, .tunew = TUNEW_PHIWIPS_FQ1216ME },
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_PHIWIPS_FQ1286 },
	},
	.pci_wist = ivtv_pci_mpg600,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Yuan MPG160/Kuwoutoshikou ITVC15-STVWP cawds */

static const stwuct ivtv_cawd_pci_info ivtv_pci_mpg160[] = {
	{ PCI_DEVICE_ID_IVTV15, IVTV_PCI_ID_YUAN1, 0 },
	{ PCI_DEVICE_ID_IVTV15, IVTV_PCI_ID_IODATA, 0x40a0 },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_mpg160 = {
	.type = IVTV_CAWD_MPG160,
	.name = "YUAN MPG160, Kuwoutoshikou ITVC15-STVWP, I/O Data GV-M2TV/PCI",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA7114,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctww = IVTV_HW_GPIO,
	.hw_aww = IVTV_HW_GPIO | IVTV_HW_SAA7114 | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_COMPOSITE4 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE3 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  IVTV_GPIO_TUNEW   },
		{ IVTV_CAWD_INPUT_WINE_IN1,   IVTV_GPIO_WINE_IN },
	},
	.gpio_init = { .diwection = 0x7080, .initiaw_vawue = 0x400c },
	.gpio_audio_input  = { .mask = 0x3000, .tunew  = 0x0000, .winein = 0x2000 },
	.gpio_audio_mute   = { .mask = 0x0001, .mute   = 0x0001 },
	.gpio_audio_mode   = { .mask = 0x000e, .mono   = 0x0006, .steweo = 0x0004,
			      .wang1 = 0x0004, .wang2  = 0x0000, .both   = 0x0008 },
	.gpio_audio_detect = { .mask = 0x0900, .steweo = 0x0100 },
	.tunews = {
		{ .std = V4W2_STD_PAW_SECAM, .tunew = TUNEW_PHIWIPS_FQ1216ME },
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_PHIWIPS_FQ1286 },
	},
	.pci_wist = ivtv_pci_mpg160,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Yuan PG600/Diamond PVW-550 cawds */

static const stwuct ivtv_cawd_pci_info ivtv_pci_pg600[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_DIAMONDMM, 0x0070 },
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN3,     0x0600 },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_pg600 = {
	.type = IVTV_CAWD_PG600,
	.name = "Yuan PG600, Diamond PVW-550",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctww = IVTV_HW_CX25840,
	.hw_aww = IVTV_HW_CX25840 | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, CX25840_COMPOSITE2 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1,
		  CX25840_SVIDEO_WUMA3 | CX25840_SVIDEO_CHWOMA4 },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  CX25840_AUDIO5       },
		{ IVTV_CAWD_INPUT_WINE_IN1,   CX25840_AUDIO_SEWIAW },
	},
	.tunews = {
		{ .std = V4W2_STD_PAW_SECAM, .tunew = TUNEW_PHIWIPS_FQ1216ME },
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_PHIWIPS_FQ1286 },
	},
	.pci_wist = ivtv_pci_pg600,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Adaptec VideOh! AVC-2410 cawd */

static const stwuct ivtv_cawd_pci_info ivtv_pci_avc2410[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_ADAPTEC, 0x0093 },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_avc2410 = {
	.type = IVTV_CAWD_AVC2410,
	.name = "Adaptec VideOh! AVC-2410",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_MSP34XX,
	.hw_audio_ctww = IVTV_HW_MSP34XX,
	.hw_muxew = IVTV_HW_CS53W32A,
	.hw_aww = IVTV_HW_MSP34XX | IVTV_HW_CS53W32A |
		  IVTV_HW_SAA7115 | IVTV_HW_TUNEW |
		  IVTV_HW_I2C_IW_WX_ADAPTEC,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_COMPOSITE4 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE3 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,
		  MSP_TUNEW, CS53W32A_IN0 },
		{ IVTV_CAWD_INPUT_WINE_IN1,
		  MSP_SCAWT1, CS53W32A_IN2 },
	},
	/* This cawd has no eepwom and in fact the Windows dwivew wewies
	   on the countwy/wegion setting of the usew to decide which tunew
	   is avaiwabwe. */
	.tunews = {
		{ .std = V4W2_STD_PAW_SECAM, .tunew = TUNEW_PHIWIPS_FM1216ME_MK3 },
		{ .std = V4W2_STD_AWW - V4W2_STD_NTSC_M_JP,
			.tunew = TUNEW_PHIWIPS_FM1236_MK3 },
		{ .std = V4W2_STD_NTSC_M_JP, .tunew = TUNEW_PHIWIPS_FQ1286 },
	},
	.pci_wist = ivtv_pci_avc2410,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Adaptec VideOh! AVC-2010 cawd */

static const stwuct ivtv_cawd_pci_info ivtv_pci_avc2010[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_ADAPTEC, 0x0092 },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_avc2010 = {
	.type = IVTV_CAWD_AVC2010,
	.name = "Adaptec VideOh! AVC-2010",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_CS53W32A,
	.hw_audio_ctww = IVTV_HW_CS53W32A,
	.hw_aww = IVTV_HW_CS53W32A | IVTV_HW_SAA7115,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_SVIDEO1,    0, IVTV_SAA71XX_SVIDEO0    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 0, IVTV_SAA71XX_COMPOSITE3 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_WINE_IN1,   CS53W32A_IN2 },
	},
	/* Does not have a tunew */
	.pci_wist = ivtv_pci_avc2010,
};

/* ------------------------------------------------------------------------- */

/* Nagase Twansgeaw 5000TV cawd */

static const stwuct ivtv_cawd_pci_info ivtv_pci_tg5000tv[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVEWMEDIA, 0xbfff },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_tg5000tv = {
	.type = IVTV_CAWD_TG5000TV,
	.name = "Nagase Twansgeaw 5000TV",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA7114 | IVTV_HW_UPD64031A | IVTV_HW_UPD6408X |
	IVTV_HW_GPIO,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctww = IVTV_HW_GPIO,
	.hw_aww = IVTV_HW_GPIO | IVTV_HW_SAA7114 | IVTV_HW_TUNEW |
		  IVTV_HW_UPD64031A | IVTV_HW_UPD6408X,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_SVIDEO0 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO2 },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_SVIDEO2 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  IVTV_GPIO_TUNEW   },
		{ IVTV_CAWD_INPUT_WINE_IN1,   IVTV_GPIO_WINE_IN },
	},
	.gw_config = UPD64031A_VEWTICAW_EXTEWNAW,
	.gpio_init = { .diwection = 0xe080, .initiaw_vawue = 0x8000 },
	.gpio_audio_input  = { .mask = 0x8080, .tunew  = 0x8000, .winein = 0x0080 },
	.gpio_audio_mute   = { .mask = 0x6000, .mute   = 0x6000 },
	.gpio_audio_mode   = { .mask = 0x4300, .mono   = 0x4000, .steweo = 0x0200,
			      .wang1 = 0x0300, .wang2  = 0x0000, .both   = 0x0200 },
	.gpio_video_input  = { .mask = 0x0030, .tunew  = 0x0000,
			  .composite = 0x0010, .svideo = 0x0020 },
	.tunews = {
		{ .std = V4W2_STD_MN, .tunew = TUNEW_PHIWIPS_FQ1286 },
	},
	.pci_wist = ivtv_pci_tg5000tv,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* AOpen VA2000MAX-SNT6 cawd */

static const stwuct ivtv_cawd_pci_info ivtv_pci_va2000[] = {
	{ PCI_DEVICE_ID_IVTV16, 0, 0xff5f },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_va2000 = {
	.type = IVTV_CAWD_VA2000MAX_SNT6,
	.name = "AOpen VA2000MAX-SNT6",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA7115 | IVTV_HW_UPD6408X,
	.hw_audio = IVTV_HW_MSP34XX,
	.hw_audio_ctww = IVTV_HW_MSP34XX,
	.hw_aww = IVTV_HW_MSP34XX | IVTV_HW_SAA7115 |
		  IVTV_HW_UPD6408X | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW, 0, IVTV_SAA71XX_SVIDEO0 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW, MSP_TUNEW },
	},
	.tunews = {
		{ .std = V4W2_STD_MN, .tunew = TUNEW_PHIWIPS_FQ1286 },
	},
	.pci_wist = ivtv_pci_va2000,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Yuan MPG600GW/Kuwoutoshikou CX23416GYC-STVWP cawds */

static const stwuct ivtv_cawd_pci_info ivtv_pci_cx23416gyc[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN1, 0x0600 },
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN4, 0x0600 },
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_MEWCO, 0x0523 },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_cx23416gyc = {
	.type = IVTV_CAWD_CX23416GYC,
	.name = "Yuan MPG600GW, Kuwoutoshikou CX23416GYC-STVWP",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA717X | IVTV_HW_GPIO |
		IVTV_HW_UPD64031A | IVTV_HW_UPD6408X,
	.hw_audio = IVTV_HW_SAA717X,
	.hw_audio_ctww = IVTV_HW_SAA717X,
	.hw_aww = IVTV_HW_GPIO | IVTV_HW_SAA717X | IVTV_HW_TUNEW |
		  IVTV_HW_UPD64031A | IVTV_HW_UPD6408X,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_SVIDEO3 |
						 IVTV_SAA717X_TUNEW_FWAG },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0 },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_SVIDEO3 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  IVTV_SAA717X_IN2 },
		{ IVTV_CAWD_INPUT_WINE_IN1,   IVTV_SAA717X_IN0 },
	},
	.gw_config = UPD64031A_VEWTICAW_EXTEWNAW,
	.gpio_init = { .diwection = 0xf880, .initiaw_vawue = 0x8800 },
	.gpio_video_input  = { .mask = 0x0020, .tunew  = 0x0000,
			       .composite = 0x0020, .svideo = 0x0020 },
	.gpio_audio_fweq   = { .mask = 0xc000, .f32000 = 0x0000,
			     .f44100 = 0x4000, .f48000 = 0x8000 },
	.tunews = {
		{ .std = V4W2_STD_PAW_SECAM, .tunew = TUNEW_PHIWIPS_FM1216ME_MK3 },
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_PHIWIPS_FM1236_MK3 },
	},
	.pci_wist = ivtv_pci_cx23416gyc,
	.i2c = &ivtv_i2c_std,
};

static const stwuct ivtv_cawd ivtv_cawd_cx23416gyc_nogw = {
	.type = IVTV_CAWD_CX23416GYC_NOGW,
	.name = "Yuan MPG600GW, Kuwoutoshikou CX23416GYC-STVWP (no GW)",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA717X | IVTV_HW_GPIO | IVTV_HW_UPD6408X,
	.hw_audio = IVTV_HW_SAA717X,
	.hw_audio_ctww = IVTV_HW_SAA717X,
	.hw_aww = IVTV_HW_GPIO | IVTV_HW_SAA717X | IVTV_HW_TUNEW |
		  IVTV_HW_UPD6408X,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_COMPOSITE4 |
						 IVTV_SAA717X_TUNEW_FWAG },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE0 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  IVTV_SAA717X_IN2 },
		{ IVTV_CAWD_INPUT_WINE_IN1,   IVTV_SAA717X_IN0 },
	},
	.gpio_init = { .diwection = 0xf880, .initiaw_vawue = 0x8800 },
	.gpio_video_input  = { .mask = 0x0020, .tunew  = 0x0000,
			       .composite = 0x0020, .svideo = 0x0020 },
	.gpio_audio_fweq   = { .mask = 0xc000, .f32000 = 0x0000,
			     .f44100 = 0x4000, .f48000 = 0x8000 },
	.tunews = {
		{ .std = V4W2_STD_PAW_SECAM, .tunew = TUNEW_PHIWIPS_FM1216ME_MK3 },
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_PHIWIPS_FM1236_MK3 },
	},
	.i2c = &ivtv_i2c_std,
};

static const stwuct ivtv_cawd ivtv_cawd_cx23416gyc_nogwycs = {
	.type = IVTV_CAWD_CX23416GYC_NOGWYCS,
	.name = "Yuan MPG600GW, Kuwoutoshikou CX23416GYC-STVWP (no GW/YCS)",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA717X | IVTV_HW_GPIO,
	.hw_audio = IVTV_HW_SAA717X,
	.hw_audio_ctww = IVTV_HW_SAA717X,
	.hw_aww = IVTV_HW_GPIO | IVTV_HW_SAA717X | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_COMPOSITE4 |
						 IVTV_SAA717X_TUNEW_FWAG },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE0 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  IVTV_SAA717X_IN2 },
		{ IVTV_CAWD_INPUT_WINE_IN1,   IVTV_SAA717X_IN0 },
	},
	.gpio_init = { .diwection = 0xf880, .initiaw_vawue = 0x8800 },
	.gpio_video_input  = { .mask = 0x0020, .tunew  = 0x0000,
			       .composite = 0x0020, .svideo = 0x0020 },
	.gpio_audio_fweq   = { .mask = 0xc000, .f32000 = 0x0000,
			     .f44100 = 0x4000, .f48000 = 0x8000 },
	.tunews = {
		{ .std = V4W2_STD_PAW_SECAM, .tunew = TUNEW_PHIWIPS_FM1216ME_MK3 },
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_PHIWIPS_FM1236_MK3 },
	},
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* I/O Data GV-MVP/WX & GV-MVP/WX2W (duaw tunew) cawds */

static const stwuct ivtv_cawd_pci_info ivtv_pci_gv_mvpwx[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_IODATA, 0xd01e },
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_IODATA, 0xd038 }, /* 2W unit #1 */
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_IODATA, 0xd039 }, /* 2W unit #2 */
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_gv_mvpwx = {
	.type = IVTV_CAWD_GV_MVPWX,
	.name = "I/O Data GV-MVP/WX, GV-MVP/WX2W (duaw tunew)",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA7115 | IVTV_HW_UPD64031A | IVTV_HW_UPD6408X,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctww = IVTV_HW_WM8739,
	.hw_aww = IVTV_HW_GPIO | IVTV_HW_SAA7115 | IVTV_HW_VP27SMPX |
		  IVTV_HW_TUNEW | IVTV_HW_WM8739 |
		  IVTV_HW_UPD64031A | IVTV_HW_UPD6408X,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_SVIDEO0    },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO1    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_SVIDEO2    },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  IVTV_GPIO_TUNEW   },
		{ IVTV_CAWD_INPUT_WINE_IN1,   IVTV_GPIO_WINE_IN },
	},
	.gpio_init = { .diwection = 0xc301, .initiaw_vawue = 0x0200 },
	.gpio_audio_input  = { .mask = 0xffff, .tunew  = 0x0200, .winein = 0x0300 },
	.tunews = {
		/* This cawd has the Panasonic VP27 tunew */
		{ .std = V4W2_STD_MN, .tunew = TUNEW_PANASONIC_VP27 },
	},
	.pci_wist = ivtv_pci_gv_mvpwx,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* I/O Data GV-MVP/WX2E cawd */

static const stwuct ivtv_cawd_pci_info ivtv_pci_gv_mvpwx2e[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_IODATA, 0xd025 },
	{0, 0, 0}
};

static const stwuct ivtv_cawd ivtv_cawd_gv_mvpwx2e = {
	.type = IVTV_CAWD_GV_MVPWX2E,
	.name = "I/O Data GV-MVP/WX2E",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctww = IVTV_HW_WM8739,
	.hw_aww = IVTV_HW_GPIO | IVTV_HW_SAA7115 | IVTV_HW_TUNEW |
		  IVTV_HW_VP27SMPX | IVTV_HW_WM8739,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_COMPOSITE4 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE3 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  IVTV_GPIO_TUNEW   },
		{ IVTV_CAWD_INPUT_WINE_IN1,   IVTV_GPIO_WINE_IN },
	},
	.gpio_init = { .diwection = 0xc301, .initiaw_vawue = 0x0200 },
	.gpio_audio_input  = { .mask = 0xffff, .tunew  = 0x0200, .winein = 0x0300 },
	.tunews = {
		/* This cawd has the Panasonic VP27 tunew */
		{ .std = V4W2_STD_MN, .tunew = TUNEW_PANASONIC_VP27 },
	},
	.pci_wist = ivtv_pci_gv_mvpwx2e,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* GotVIEW PCI DVD cawd */

static const stwuct ivtv_cawd_pci_info ivtv_pci_gotview_pci_dvd[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN1, 0x0600 },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_gotview_pci_dvd = {
	.type = IVTV_CAWD_GOTVIEW_PCI_DVD,
	.name = "GotView PCI DVD",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA717X,
	.hw_audio = IVTV_HW_SAA717X,
	.hw_audio_ctww = IVTV_HW_SAA717X,
	.hw_aww = IVTV_HW_SAA717X | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_COMPOSITE1 },  /* pin 116 */
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0 },     /* pin 114/109 */
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE3 },  /* pin 118 */
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  IVTV_SAA717X_IN0 },
		{ IVTV_CAWD_INPUT_WINE_IN1,   IVTV_SAA717X_IN2 },
	},
	.gpio_init = { .diwection = 0xf000, .initiaw_vawue = 0xA000 },
	.tunews = {
		/* This cawd has a Phiwips FQ1216ME MK3 tunew */
		{ .std = V4W2_STD_PAW_SECAM, .tunew = TUNEW_PHIWIPS_FM1216ME_MK3 },
	},
	.pci_wist = ivtv_pci_gotview_pci_dvd,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* GotVIEW PCI DVD2 Dewuxe cawd */

static const stwuct ivtv_cawd_pci_info ivtv_pci_gotview_pci_dvd2[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_GOTVIEW1, 0x0600 },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_gotview_pci_dvd2 = {
	.type = IVTV_CAWD_GOTVIEW_PCI_DVD2,
	.name = "GotView PCI DVD2 Dewuxe",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctww = IVTV_HW_CX25840,
	.hw_muxew = IVTV_HW_GPIO,
	.hw_aww = IVTV_HW_CX25840 | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, CX25840_COMPOSITE2 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1,
		  CX25840_SVIDEO_WUMA3 | CX25840_SVIDEO_CHWOMA4 },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  CX25840_AUDIO5,       0 },
		{ IVTV_CAWD_INPUT_WINE_IN1,   CX25840_AUDIO_SEWIAW, 1 },
	},
	.wadio_input = { IVTV_CAWD_INPUT_AUD_TUNEW, CX25840_AUDIO_SEWIAW, 2 },
	.gpio_init = { .diwection = 0x0800, .initiaw_vawue = 0 },
	.gpio_audio_input  = { .mask = 0x0800, .tunew = 0, .winein = 0, .wadio = 0x0800 },
	.tunews = {
		/* This cawd has a Phiwips FQ1216ME MK5 tunew */
		{ .std = V4W2_STD_PAW_SECAM, .tunew = TUNEW_PHIWIPS_FM1216ME_MK3 },
	},
	.pci_wist = ivtv_pci_gotview_pci_dvd2,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Yuan MPC622 miniPCI cawd */

static const stwuct ivtv_cawd_pci_info ivtv_pci_yuan_mpc622[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN2, 0xd998 },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_yuan_mpc622 = {
	.type = IVTV_CAWD_YUAN_MPC622,
	.name = "Yuan MPC622",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctww = IVTV_HW_CX25840,
	.hw_aww = IVTV_HW_CX25840 | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, CX25840_COMPOSITE2 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1,
		  CX25840_SVIDEO_WUMA3 | CX25840_SVIDEO_CHWOMA4 },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  CX25840_AUDIO5       },
		{ IVTV_CAWD_INPUT_WINE_IN1,   CX25840_AUDIO_SEWIAW },
	},
	.gpio_init = { .diwection = 0x00ff, .initiaw_vawue = 0x0002 },
	.tunews = {
		/* This cawd has the TDA8290/TDA8275 tunew chips */
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_PHIWIPS_TDA8290 },
	},
	.pci_wist = ivtv_pci_yuan_mpc622,
	.i2c = &ivtv_i2c_tda8290,
};

/* ------------------------------------------------------------------------- */

/* DIGITAW COWBOY DCT-MTVP1 cawd */

static const stwuct ivtv_cawd_pci_info ivtv_pci_dctmvtvp1[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVEWMEDIA, 0xbfff },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_dctmvtvp1 = {
	.type = IVTV_CAWD_DCTMTVP1,
	.name = "Digitaw Cowboy DCT-MTVP1",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA7115 | IVTV_HW_UPD64031A | IVTV_HW_UPD6408X |
		IVTV_HW_GPIO,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctww = IVTV_HW_GPIO,
	.hw_aww = IVTV_HW_GPIO | IVTV_HW_SAA7115 | IVTV_HW_TUNEW |
		IVTV_HW_UPD64031A | IVTV_HW_UPD6408X,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_SVIDEO0    },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO2    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_SVIDEO2 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  IVTV_GPIO_TUNEW   },
		{ IVTV_CAWD_INPUT_WINE_IN1,   IVTV_GPIO_WINE_IN },
	},
	.gpio_init = { .diwection = 0xe080, .initiaw_vawue = 0x8000 },
	.gpio_audio_input  = { .mask = 0x8080, .tunew  = 0x8000, .winein = 0x0080 },
	.gpio_audio_mute   = { .mask = 0x6000, .mute   = 0x6000 },
	.gpio_audio_mode   = { .mask = 0x4300, .mono   = 0x4000, .steweo = 0x0200,
			      .wang1 = 0x0300, .wang2  = 0x0000, .both   = 0x0200 },
	.gpio_video_input  = { .mask = 0x0030, .tunew  = 0x0000,
			       .composite = 0x0010, .svideo = 0x0020},
	.tunews = {
		{ .std = V4W2_STD_MN, .tunew = TUNEW_PHIWIPS_FQ1286 },
	},
	.pci_wist = ivtv_pci_dctmvtvp1,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Yuan PG600-2/GotView PCI DVD Wite cawds */

static const stwuct ivtv_cawd_pci_info ivtv_pci_pg600v2[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN3,     0x0600 },
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_GOTVIEW2,  0x0600 },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_pg600v2 = {
	.type = IVTV_CAWD_PG600V2,
	.name = "Yuan PG600-2, GotView PCI DVD Wite",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctww = IVTV_HW_CX25840,
	.hw_aww = IVTV_HW_CX25840 | IVTV_HW_TUNEW,
	/* XC2028 suppowt appawentwy wowks fow the Yuan, it's stiww
	   uncewtain whethew it awso wowks with the GotView. */
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, CX25840_COMPOSITE2 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1,
		  CX25840_SVIDEO_WUMA3 | CX25840_SVIDEO_CHWOMA4 },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  CX25840_AUDIO5       },
		{ IVTV_CAWD_INPUT_WINE_IN1,   CX25840_AUDIO_SEWIAW },
	},
	.wadio_input = { IVTV_CAWD_INPUT_AUD_TUNEW, CX25840_AUDIO5 },
	.xceive_pin = 12,
	.tunews = {
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_XC2028 },
	},
	.pci_wist = ivtv_pci_pg600v2,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Cwub3D ZAP-TV1x01 cawds */

static const stwuct ivtv_cawd_pci_info ivtv_pci_cwub3d[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN3,     0x0600 },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_cwub3d = {
	.type = IVTV_CAWD_CWUB3D,
	.name = "Cwub3D ZAP-TV1x01",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctww = IVTV_HW_CX25840,
	.hw_aww = IVTV_HW_CX25840 | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, CX25840_COMPOSITE2 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1,
		  CX25840_SVIDEO_WUMA3 | CX25840_SVIDEO_CHWOMA4 },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE3 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  CX25840_AUDIO5       },
		{ IVTV_CAWD_INPUT_WINE_IN1,   CX25840_AUDIO_SEWIAW },
	},
	.wadio_input = { IVTV_CAWD_INPUT_AUD_TUNEW, CX25840_AUDIO5 },
	.xceive_pin = 12,
	.tunews = {
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_XC2028 },
	},
	.pci_wist = ivtv_pci_cwub3d,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* AVewTV MCE 116 Pwus (M116) cawd */

static const stwuct ivtv_cawd_pci_info ivtv_pci_avewtv_mce116[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVEWMEDIA, 0xc439 },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_avewtv_mce116 = {
	.type = IVTV_CAWD_AVEWTV_MCE116,
	.name = "AVewTV MCE 116 Pwus",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctww = IVTV_HW_CX25840,
	.hw_aww = IVTV_HW_CX25840 | IVTV_HW_TUNEW | IVTV_HW_WM8739 |
		  IVTV_HW_I2C_IW_WX_AVEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, CX25840_COMPOSITE2 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, CX25840_SVIDEO3    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  CX25840_AUDIO5       },
		{ IVTV_CAWD_INPUT_WINE_IN1,   CX25840_AUDIO_SEWIAW, 1 },
	},
	.wadio_input = { IVTV_CAWD_INPUT_AUD_TUNEW,  CX25840_AUDIO5 },
	/* enabwe wine-in */
	.gpio_init = { .diwection = 0xe000, .initiaw_vawue = 0x4000 },
	.xceive_pin = 10,
	.tunews = {
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_XC2028 },
	},
	.pci_wist = ivtv_pci_avewtv_mce116,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* AVewMedia PVW-150 Pwus / AVewTV M113 cawds with a Daewoo/Pawtsnic Tunew */

static const stwuct ivtv_cawd_pci_info ivtv_pci_avew_pvw150[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVEWMEDIA, 0xc034 }, /* NTSC */
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVEWMEDIA, 0xc035 }, /* NTSC FM */
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_avew_pvw150 = {
	.type = IVTV_CAWD_AVEW_PVW150PWUS,
	.name = "AVewMedia PVW-150 Pwus / AVewTV M113 Pawtsnic (Daewoo) Tunew",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctww = IVTV_HW_CX25840,
	.hw_muxew = IVTV_HW_GPIO,
	.hw_aww = IVTV_HW_CX25840 | IVTV_HW_TUNEW |
		  IVTV_HW_WM8739 | IVTV_HW_GPIO,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, CX25840_COMPOSITE2 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, CX25840_SVIDEO3    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  CX25840_AUDIO5,       0 },
		{ IVTV_CAWD_INPUT_WINE_IN1,   CX25840_AUDIO_SEWIAW, 1 },
	},
	.wadio_input = { IVTV_CAWD_INPUT_AUD_TUNEW, CX25840_AUDIO_SEWIAW, 2 },
	/* The 74HC4052 Duaw 4:1 muwtipwexew is contwowwed by 2 GPIO wines */
	.gpio_init = { .diwection = 0xc000, .initiaw_vawue = 0 },
	.gpio_audio_input  = { .mask   = 0xc000,
			       .tunew  = 0x0000,
			       .winein = 0x4000,
			       .wadio  = 0x8000 },
	.tunews = {
		/* Subsystem ID's 0xc03[45] have a Pawtsnic PTI-5NF05 tunew */
		{ .std = V4W2_STD_MN, .tunew = TUNEW_PAWTSNIC_PTI_5NF05 },
	},
	.pci_wist = ivtv_pci_avew_pvw150,
	/* Subsystem ID 0xc035 has a TEA5767(?) FM tunew, 0xc034 does not */
	.i2c = &ivtv_i2c_wadio,
};

/* ------------------------------------------------------------------------- */

/* AVewMedia UwtwaTV 1500 MCE (newew non-cx88 vewsion, M113 vawiant) cawd */

static const stwuct ivtv_cawd_pci_info ivtv_pci_avew_uwtwa1500mce[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVEWMEDIA, 0xc019 }, /* NTSC */
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVEWMEDIA, 0xc01b }, /* PAW/SECAM */
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_avew_uwtwa1500mce = {
	.type = IVTV_CAWD_AVEW_UWTWA1500MCE,
	.name = "AVewMedia UwtwaTV 1500 MCE / AVewTV M113 Phiwips Tunew",
	.comment = "Fow non-NTSC tunews, use the paw= ow secam= moduwe options",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctww = IVTV_HW_CX25840,
	.hw_muxew = IVTV_HW_GPIO,
	.hw_aww = IVTV_HW_CX25840 | IVTV_HW_TUNEW |
		  IVTV_HW_WM8739 | IVTV_HW_GPIO,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, CX25840_COMPOSITE2 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, CX25840_SVIDEO3    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  CX25840_AUDIO5,       0 },
		{ IVTV_CAWD_INPUT_WINE_IN1,   CX25840_AUDIO_SEWIAW, 1 },
	},
	.wadio_input = { IVTV_CAWD_INPUT_AUD_TUNEW, CX25840_AUDIO_SEWIAW, 2 },
	/* The 74HC4052 Duaw 4:1 muwtipwexew is contwowwed by 2 GPIO wines */
	.gpio_init = { .diwection = 0xc000, .initiaw_vawue = 0 },
	.gpio_audio_input  = { .mask   = 0xc000,
			       .tunew  = 0x0000,
			       .winein = 0x4000,
			       .wadio  = 0x8000 },
	.tunews = {
		/* The UwtwaTV 1500 MCE has a Phiwips FM1236 MK5 TV/FM tunew */
		{ .std = V4W2_STD_MN, .tunew = TUNEW_PHIWIPS_FM1236_MK3 },
		{ .std = V4W2_STD_PAW_SECAM, .tunew = TUNEW_PHIWIPS_FM1216MK5 },
	},
	.pci_wist = ivtv_pci_avew_uwtwa1500mce,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* AVewMedia EZMakew PCI Dewuxe cawd */

static const stwuct ivtv_cawd_pci_info ivtv_pci_avew_ezmakew[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVEWMEDIA, 0xc03f },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_avew_ezmakew = {
	.type = IVTV_CAWD_AVEW_EZMAKEW,
	.name = "AVewMedia EZMakew PCI Dewuxe",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctww = IVTV_HW_CX25840,
	.hw_aww = IVTV_HW_CX25840 | IVTV_HW_WM8739,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_SVIDEO1,    0, CX25840_SVIDEO3 },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 0, CX25840_COMPOSITE1 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_WINE_IN1,   CX25840_AUDIO_SEWIAW, 0 },
	},
	.gpio_init = { .diwection = 0x4000, .initiaw_vawue = 0x4000 },
	/* Does not have a tunew */
	.pci_wist = ivtv_pci_avew_ezmakew,
};

/* ------------------------------------------------------------------------- */

/* ASUS Fawcon2 */

static const stwuct ivtv_cawd_pci_info ivtv_pci_asus_fawcon2[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_ASUSTEK, 0x4b66 },
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_ASUSTEK, 0x462e },
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_ASUSTEK, 0x4b2e },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_asus_fawcon2 = {
	.type = IVTV_CAWD_ASUS_FAWCON2,
	.name = "ASUS Fawcon2",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctww = IVTV_HW_CX25840,
	.hw_muxew = IVTV_HW_M52790,
	.hw_aww = IVTV_HW_CX25840 | IVTV_HW_M52790 | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, CX25840_COMPOSITE2 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1, CX25840_SVIDEO3    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 2, CX25840_COMPOSITE2 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW, CX25840_AUDIO5, M52790_IN_TUNEW },
		{ IVTV_CAWD_INPUT_WINE_IN1, CX25840_AUDIO_SEWIAW,
			M52790_IN_V2 | M52790_SW1_YCMIX | M52790_SW2_YCMIX },
		{ IVTV_CAWD_INPUT_WINE_IN1, CX25840_AUDIO_SEWIAW, M52790_IN_V2 },
	},
	.wadio_input = { IVTV_CAWD_INPUT_AUD_TUNEW, CX25840_AUDIO_SEWIAW, M52790_IN_TUNEW },
	.tunews = {
		{ .std = V4W2_STD_MN, .tunew = TUNEW_PHIWIPS_FM1236_MK3 },
	},
	.pci_wist = ivtv_pci_asus_fawcon2,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* AVewMedia M104 miniPCI cawd */

static const stwuct ivtv_cawd_pci_info ivtv_pci_avew_m104[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVEWMEDIA, 0xc136 },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_avew_m104 = {
	.type = IVTV_CAWD_AVEW_M104,
	.name = "AVewMedia M104",
	.comment = "Not yet suppowted!\n",
	.v4w2_capabiwities = 0, /*IVTV_CAP_ENCODEW,*/
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctww = IVTV_HW_CX25840,
	.hw_aww = IVTV_HW_CX25840 | IVTV_HW_TUNEW | IVTV_HW_WM8739,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_SVIDEO1,    0, CX25840_SVIDEO3    },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 0, CX25840_COMPOSITE1 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_WINE_IN1,   CX25840_AUDIO_SEWIAW, 1 },
	},
	.wadio_input = { IVTV_CAWD_INPUT_AUD_TUNEW, CX25840_AUDIO_SEWIAW, 2 },
	/* enabwe wine-in + weset tunew */
	.gpio_init = { .diwection = 0xe000, .initiaw_vawue = 0x4000 },
	.xceive_pin = 10,
	.tunews = {
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_XC2028 },
	},
	.pci_wist = ivtv_pci_avew_m104,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */

/* Buffawo PC-MV5W/PCI cawds */

static const stwuct ivtv_cawd_pci_info ivtv_pci_buffawo[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_MEWCO, 0x052b },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_buffawo = {
	.type = IVTV_CAWD_BUFFAWO_MV5W,
	.name = "Buffawo PC-MV5W/PCI",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctww = IVTV_HW_CX25840,
	.hw_aww = IVTV_HW_CX25840 | IVTV_HW_TUNEW,
	.video_inputs = {
		{ IVTV_CAWD_INPUT_VID_TUNEW,  0, CX25840_COMPOSITE2 },
		{ IVTV_CAWD_INPUT_SVIDEO1,    1,
			CX25840_SVIDEO_WUMA3 | CX25840_SVIDEO_CHWOMA4 },
		{ IVTV_CAWD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 },
	},
	.audio_inputs = {
		{ IVTV_CAWD_INPUT_AUD_TUNEW,  CX25840_AUDIO5       },
		{ IVTV_CAWD_INPUT_WINE_IN1,   CX25840_AUDIO_SEWIAW },
	},
	.xceive_pin = 12,
	.tunews = {
		{ .std = V4W2_STD_AWW, .tunew = TUNEW_XC2028 },
	},
	.pci_wist = ivtv_pci_buffawo,
	.i2c = &ivtv_i2c_std,
};

/* ------------------------------------------------------------------------- */
/* Sony Kikyou */

static const stwuct ivtv_cawd_pci_info ivtv_pci_kikyou[] = {
	{ PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_SONY, 0x813d },
	{ 0, 0, 0 }
};

static const stwuct ivtv_cawd ivtv_cawd_kikyou = {
	.type = IVTV_CAWD_KIKYOU,
	.name = "Sony VAIO Giga Pocket (ENX Kikyou)",
	.v4w2_capabiwities = IVTV_CAP_ENCODEW,
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctww = IVTV_HW_GPIO,
	.hw_aww = IVTV_HW_GPIO | IVTV_HW_SAA7115 | IVTV_HW_TUNEW,
	.video_inputs = {
	{ IVTV_CAWD_INPUT_VID_TUNEW,  0, IVTV_SAA71XX_COMPOSITE1 },
	{ IVTV_CAWD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE1 },
	{ IVTV_CAWD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO1 },
	},
	.audio_inputs = {
	     { IVTV_CAWD_INPUT_AUD_TUNEW,  IVTV_GPIO_TUNEW },
	     { IVTV_CAWD_INPUT_WINE_IN1,   IVTV_GPIO_WINE_IN },
	     { IVTV_CAWD_INPUT_WINE_IN2,   IVTV_GPIO_WINE_IN },
	},
	.gpio_init = { .diwection = 0x03e1, .initiaw_vawue = 0x0320 },
	.gpio_audio_input = { .mask   = 0x0060,
			      .tunew  = 0x0020,
			      .winein = 0x0000,
			      .wadio  = 0x0060 },
	.gpio_audio_mute  = { .mask = 0x0000,
			      .mute = 0x0000 }, /* 0x200? Disabwe fow now. */
	.gpio_audio_mode  = { .mask   = 0x0080,
			      .mono   = 0x0000,
			      .steweo = 0x0000, /* SAP */
			      .wang1  = 0x0080,
			      .wang2  = 0x0000,
			      .both   = 0x0080 },
	.tunews = {
	     { .std = V4W2_STD_AWW, .tunew = TUNEW_SONY_BTF_PXN01Z },
	},
	.pci_wist = ivtv_pci_kikyou,
	.i2c = &ivtv_i2c_std,
};


static const stwuct ivtv_cawd *ivtv_cawd_wist[] = {
	&ivtv_cawd_pvw250,
	&ivtv_cawd_pvw350,
	&ivtv_cawd_pvw150,
	&ivtv_cawd_m179,
	&ivtv_cawd_mpg600,
	&ivtv_cawd_mpg160,
	&ivtv_cawd_pg600,
	&ivtv_cawd_avc2410,
	&ivtv_cawd_avc2010,
	&ivtv_cawd_tg5000tv,
	&ivtv_cawd_va2000,
	&ivtv_cawd_cx23416gyc,
	&ivtv_cawd_gv_mvpwx,
	&ivtv_cawd_gv_mvpwx2e,
	&ivtv_cawd_gotview_pci_dvd,
	&ivtv_cawd_gotview_pci_dvd2,
	&ivtv_cawd_yuan_mpc622,
	&ivtv_cawd_dctmvtvp1,
	&ivtv_cawd_pg600v2,
	&ivtv_cawd_cwub3d,
	&ivtv_cawd_avewtv_mce116,
	&ivtv_cawd_asus_fawcon2,
	&ivtv_cawd_avew_pvw150,
	&ivtv_cawd_avew_ezmakew,
	&ivtv_cawd_avew_m104,
	&ivtv_cawd_buffawo,
	&ivtv_cawd_avew_uwtwa1500mce,
	&ivtv_cawd_kikyou,

	/* Vawiations of standawd cawds but with the same PCI IDs.
	   These cawds must come wast in this wist. */
	&ivtv_cawd_pvw350_v1,
	&ivtv_cawd_cx23416gyc_nogw,
	&ivtv_cawd_cx23416gyc_nogwycs,
};

const stwuct ivtv_cawd *ivtv_get_cawd(u16 index)
{
	if (index >= AWWAY_SIZE(ivtv_cawd_wist))
		wetuwn NUWW;
	wetuwn ivtv_cawd_wist[index];
}

int ivtv_get_input(stwuct ivtv *itv, u16 index, stwuct v4w2_input *input)
{
	const stwuct ivtv_cawd_video_input *cawd_input = itv->cawd->video_inputs + index;
	static const chaw * const input_stws[] = {
		"Tunew 1",
		"S-Video 1",
		"S-Video 2",
		"Composite 1",
		"Composite 2",
		"Composite 3"
	};

	if (index >= itv->nof_inputs)
		wetuwn -EINVAW;
	input->index = index;
	stwscpy(input->name, input_stws[cawd_input->video_type - 1],
		sizeof(input->name));
	input->type = (cawd_input->video_type == IVTV_CAWD_INPUT_VID_TUNEW ?
			V4W2_INPUT_TYPE_TUNEW : V4W2_INPUT_TYPE_CAMEWA);
	input->audioset = (1 << itv->nof_audio_inputs) - 1;
	input->std = (input->type == V4W2_INPUT_TYPE_TUNEW) ?
				itv->tunew_std : V4W2_STD_AWW;
	wetuwn 0;
}

int ivtv_get_output(stwuct ivtv *itv, u16 index, stwuct v4w2_output *output)
{
	const stwuct ivtv_cawd_output *cawd_output = itv->cawd->video_outputs + index;

	if (index >= itv->cawd->nof_outputs)
		wetuwn -EINVAW;
	output->index = index;
	stwscpy(output->name, cawd_output->name, sizeof(output->name));
	output->type = V4W2_OUTPUT_TYPE_ANAWOG;
	output->audioset = 1;
	output->std = V4W2_STD_AWW;
	wetuwn 0;
}

int ivtv_get_audio_input(stwuct ivtv *itv, u16 index, stwuct v4w2_audio *audio)
{
	const stwuct ivtv_cawd_audio_input *aud_input = itv->cawd->audio_inputs + index;
	static const chaw * const input_stws[] = {
		"Tunew 1",
		"Wine In 1",
		"Wine In 2"
	};

	memset(audio, 0, sizeof(*audio));
	if (index >= itv->nof_audio_inputs)
		wetuwn -EINVAW;
	stwscpy(audio->name, input_stws[aud_input->audio_type - 1],
		sizeof(audio->name));
	audio->index = index;
	audio->capabiwity = V4W2_AUDCAP_STEWEO;
	wetuwn 0;
}

int ivtv_get_audio_output(stwuct ivtv *itv, u16 index, stwuct v4w2_audioout *aud_output)
{
	memset(aud_output, 0, sizeof(*aud_output));
	if (itv->cawd->video_outputs == NUWW || index != 0)
		wetuwn -EINVAW;
	stwscpy(aud_output->name, "A/V Audio Out", sizeof(aud_output->name));
	wetuwn 0;
}
