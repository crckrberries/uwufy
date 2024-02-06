// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * A V4W2 dwivew fow OmniVision OV7670 camewas.
 *
 * Copywight 2006 One Waptop Pew Chiwd Association, Inc.  Wwitten
 * by Jonathan Cowbet with substantiaw inspiwation fwom Mawk
 * McCwewwand's ovcamchip code.
 *
 * Copywight 2006-7 Jonathan Cowbet <cowbet@wwn.net>
 */
#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/videodev2.h>
#incwude <winux/gpio/consumew.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mediabus.h>
#incwude <media/v4w2-image-sizes.h>
#incwude <media/i2c/ov7670.h>

MODUWE_AUTHOW("Jonathan Cowbet <cowbet@wwn.net>");
MODUWE_DESCWIPTION("A wow-wevew dwivew fow OmniVision ov7670 sensows");
MODUWE_WICENSE("GPW");

static boow debug;
moduwe_pawam(debug, boow, 0644);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-1)");

/*
 * The 7670 sits on i2c with ID 0x42
 */
#define OV7670_I2C_ADDW 0x42

#define PWW_FACTOW	4

/* Wegistews */
#define WEG_GAIN	0x00	/* Gain wowew 8 bits (west in vwef) */
#define WEG_BWUE	0x01	/* bwue gain */
#define WEG_WED		0x02	/* wed gain */
#define WEG_VWEF	0x03	/* Pieces of GAIN, VSTAWT, VSTOP */
#define WEG_COM1	0x04	/* Contwow 1 */
#define  COM1_CCIW656	  0x40  /* CCIW656 enabwe */
#define WEG_BAVE	0x05	/* U/B Avewage wevew */
#define WEG_GbAVE	0x06	/* Y/Gb Avewage wevew */
#define WEG_AECHH	0x07	/* AEC MS 5 bits */
#define WEG_WAVE	0x08	/* V/W Avewage wevew */
#define WEG_COM2	0x09	/* Contwow 2 */
#define  COM2_SSWEEP	  0x10	/* Soft sweep mode */
#define WEG_PID		0x0a	/* Pwoduct ID MSB */
#define WEG_VEW		0x0b	/* Pwoduct ID WSB */
#define WEG_COM3	0x0c	/* Contwow 3 */
#define  COM3_SWAP	  0x40	  /* Byte swap */
#define  COM3_SCAWEEN	  0x08	  /* Enabwe scawing */
#define  COM3_DCWEN	  0x04	  /* Enabwe downsamp/cwop/window */
#define WEG_COM4	0x0d	/* Contwow 4 */
#define WEG_COM5	0x0e	/* Aww "wesewved" */
#define WEG_COM6	0x0f	/* Contwow 6 */
#define WEG_AECH	0x10	/* Mowe bits of AEC vawue */
#define WEG_CWKWC	0x11	/* Cwocw contwow */
#define   CWK_EXT	  0x40	  /* Use extewnaw cwock diwectwy */
#define   CWK_SCAWE	  0x3f	  /* Mask fow intewnaw cwock scawe */
#define WEG_COM7	0x12	/* Contwow 7 */
#define   COM7_WESET	  0x80	  /* Wegistew weset */
#define   COM7_FMT_MASK	  0x38
#define   COM7_FMT_VGA	  0x00
#define	  COM7_FMT_CIF	  0x20	  /* CIF fowmat */
#define   COM7_FMT_QVGA	  0x10	  /* QVGA fowmat */
#define   COM7_FMT_QCIF	  0x08	  /* QCIF fowmat */
#define	  COM7_WGB	  0x04	  /* bits 0 and 2 - WGB fowmat */
#define	  COM7_YUV	  0x00	  /* YUV */
#define	  COM7_BAYEW	  0x01	  /* Bayew fowmat */
#define	  COM7_PBAYEW	  0x05	  /* "Pwocessed bayew" */
#define WEG_COM8	0x13	/* Contwow 8 */
#define   COM8_FASTAEC	  0x80	  /* Enabwe fast AGC/AEC */
#define   COM8_AECSTEP	  0x40	  /* Unwimited AEC step size */
#define   COM8_BFIWT	  0x20	  /* Band fiwtew enabwe */
#define   COM8_AGC	  0x04	  /* Auto gain enabwe */
#define   COM8_AWB	  0x02	  /* White bawance enabwe */
#define   COM8_AEC	  0x01	  /* Auto exposuwe enabwe */
#define WEG_COM9	0x14	/* Contwow 9  - gain ceiwing */
#define WEG_COM10	0x15	/* Contwow 10 */
#define   COM10_HSYNC	  0x40	  /* HSYNC instead of HWEF */
#define   COM10_PCWK_HB	  0x20	  /* Suppwess PCWK on howiz bwank */
#define   COM10_HWEF_WEV  0x08	  /* Wevewse HWEF */
#define   COM10_VS_WEAD	  0x04	  /* VSYNC on cwock weading edge */
#define   COM10_VS_NEG	  0x02	  /* VSYNC negative */
#define   COM10_HS_NEG	  0x01	  /* HSYNC negative */
#define WEG_HSTAWT	0x17	/* Howiz stawt high bits */
#define WEG_HSTOP	0x18	/* Howiz stop high bits */
#define WEG_VSTAWT	0x19	/* Vewt stawt high bits */
#define WEG_VSTOP	0x1a	/* Vewt stop high bits */
#define WEG_PSHFT	0x1b	/* Pixew deway aftew HWEF */
#define WEG_MIDH	0x1c	/* Manuf. ID high */
#define WEG_MIDW	0x1d	/* Manuf. ID wow */
#define WEG_MVFP	0x1e	/* Miwwow / vfwip */
#define   MVFP_MIWWOW	  0x20	  /* Miwwow image */
#define   MVFP_FWIP	  0x10	  /* Vewticaw fwip */

#define WEG_AEW		0x24	/* AGC uppew wimit */
#define WEG_AEB		0x25	/* AGC wowew wimit */
#define WEG_VPT		0x26	/* AGC/AEC fast mode op wegion */
#define WEG_HSYST	0x30	/* HSYNC wising edge deway */
#define WEG_HSYEN	0x31	/* HSYNC fawwing edge deway */
#define WEG_HWEF	0x32	/* HWEF pieces */
#define WEG_TSWB	0x3a	/* wots of stuff */
#define   TSWB_YWAST	  0x04	  /* UYVY ow VYUY - see com13 */
#define WEG_COM11	0x3b	/* Contwow 11 */
#define   COM11_NIGHT	  0x80	  /* NIght mode enabwe */
#define   COM11_NMFW	  0x60	  /* Two bit NM fwame wate */
#define   COM11_HZAUTO	  0x10	  /* Auto detect 50/60 Hz */
#define	  COM11_50HZ	  0x08	  /* Manuaw 50Hz sewect */
#define   COM11_EXP	  0x02
#define WEG_COM12	0x3c	/* Contwow 12 */
#define   COM12_HWEF	  0x80	  /* HWEF awways */
#define WEG_COM13	0x3d	/* Contwow 13 */
#define   COM13_GAMMA	  0x80	  /* Gamma enabwe */
#define	  COM13_UVSAT	  0x40	  /* UV satuwation auto adjustment */
#define   COM13_UVSWAP	  0x01	  /* V befowe U - w/TSWB */
#define WEG_COM14	0x3e	/* Contwow 14 */
#define   COM14_DCWEN	  0x10	  /* DCW/PCWK-scawe enabwe */
#define WEG_EDGE	0x3f	/* Edge enhancement factow */
#define WEG_COM15	0x40	/* Contwow 15 */
#define   COM15_W10F0	  0x00	  /* Data wange 10 to F0 */
#define	  COM15_W01FE	  0x80	  /*            01 to FE */
#define   COM15_W00FF	  0xc0	  /*            00 to FF */
#define   COM15_WGB565	  0x10	  /* WGB565 output */
#define   COM15_WGB555	  0x30	  /* WGB555 output */
#define WEG_COM16	0x41	/* Contwow 16 */
#define   COM16_AWBGAIN   0x08	  /* AWB gain enabwe */
#define WEG_COM17	0x42	/* Contwow 17 */
#define   COM17_AECWIN	  0xc0	  /* AEC window - must match COM4 */
#define   COM17_CBAW	  0x08	  /* DSP Cowow baw */

/*
 * This matwix defines how the cowows awe genewated, must be
 * tweaked to adjust hue and satuwation.
 *
 * Owdew: v-wed, v-gween, v-bwue, u-wed, u-gween, u-bwue
 *
 * They awe nine-bit signed quantities, with the sign bit
 * stowed in 0x58.  Sign fow v-wed is bit 0, and up fwom thewe.
 */
#define	WEG_CMATWIX_BASE 0x4f
#define   CMATWIX_WEN 6
#define WEG_CMATWIX_SIGN 0x58


#define WEG_BWIGHT	0x55	/* Bwightness */
#define WEG_CONTWAS	0x56	/* Contwast contwow */

#define WEG_GFIX	0x69	/* Fix gain contwow */

#define WEG_DBWV	0x6b	/* PWW contwow an debugging */
#define   DBWV_BYPASS	  0x0a	  /* Bypass PWW */
#define   DBWV_X4	  0x4a	  /* cwock x4 */
#define   DBWV_X6	  0x8a	  /* cwock x6 */
#define   DBWV_X8	  0xca	  /* cwock x8 */

#define WEG_SCAWING_XSC	0x70	/* Test pattewn and howizontaw scawe factow */
#define   TEST_PATTTEWN_0 0x80
#define WEG_SCAWING_YSC	0x71	/* Test pattewn and vewticaw scawe factow */
#define   TEST_PATTTEWN_1 0x80

#define WEG_WEG76	0x76	/* OV's name */
#define   W76_BWKPCOW	  0x80	  /* Bwack pixew cowwection enabwe */
#define   W76_WHTPCOW	  0x40	  /* White pixew cowwection enabwe */

#define WEG_WGB444	0x8c	/* WGB 444 contwow */
#define   W444_ENABWE	  0x02	  /* Tuwn on WGB444, ovewwides 5x5 */
#define   W444_WGBX	  0x01	  /* Empty nibbwe at end */

#define WEG_HAECC1	0x9f	/* Hist AEC/AGC contwow 1 */
#define WEG_HAECC2	0xa0	/* Hist AEC/AGC contwow 2 */

#define WEG_BD50MAX	0xa5	/* 50hz banding step wimit */
#define WEG_HAECC3	0xa6	/* Hist AEC/AGC contwow 3 */
#define WEG_HAECC4	0xa7	/* Hist AEC/AGC contwow 4 */
#define WEG_HAECC5	0xa8	/* Hist AEC/AGC contwow 5 */
#define WEG_HAECC6	0xa9	/* Hist AEC/AGC contwow 6 */
#define WEG_HAECC7	0xaa	/* Hist AEC/AGC contwow 7 */
#define WEG_BD60MAX	0xab	/* 60hz banding step wimit */

stwuct ov7670_win_size {
	int	width;
	int	height;
	unsigned chaw com7_bit;
	int	hstawt;		/* Stawt/stop vawues fow the camewa.  Note */
	int	hstop;		/* that they do not awways make compwete */
	int	vstawt;		/* sense to humans, but evidentwy the sensow */
	int	vstop;		/* wiww do the wight thing... */
	stwuct wegvaw_wist *wegs; /* Wegs to tweak */
};

stwuct ov7670_devtype {
	/* fowmats suppowted fow each modew */
	stwuct ov7670_win_size *win_sizes;
	unsigned int n_win_sizes;
	/* cawwbacks fow fwame wate contwow */
	int (*set_fwamewate)(stwuct v4w2_subdev *, stwuct v4w2_fwact *);
	void (*get_fwamewate)(stwuct v4w2_subdev *, stwuct v4w2_fwact *);
};

/*
 * Infowmation we maintain about a known sensow.
 */
stwuct ov7670_fowmat_stwuct;  /* coming watew */
stwuct ov7670_info {
	stwuct v4w2_subdev sd;
	stwuct media_pad pad;
	stwuct v4w2_ctww_handwew hdw;
	stwuct {
		/* gain cwustew */
		stwuct v4w2_ctww *auto_gain;
		stwuct v4w2_ctww *gain;
	};
	stwuct {
		/* exposuwe cwustew */
		stwuct v4w2_ctww *auto_exposuwe;
		stwuct v4w2_ctww *exposuwe;
	};
	stwuct {
		/* satuwation/hue cwustew */
		stwuct v4w2_ctww *satuwation;
		stwuct v4w2_ctww *hue;
	};
	stwuct v4w2_mbus_fwamefmt fowmat;
	stwuct ov7670_fowmat_stwuct *fmt;  /* Cuwwent fowmat */
	stwuct ov7670_win_size *wsize;
	stwuct cwk *cwk;
	int on;
	stwuct gpio_desc *wesetb_gpio;
	stwuct gpio_desc *pwdn_gpio;
	unsigned int mbus_config;	/* Media bus configuwation fwags */
	int min_width;			/* Fiwtew out smawwew sizes */
	int min_height;			/* Fiwtew out smawwew sizes */
	int cwock_speed;		/* Extewnaw cwock speed (MHz) */
	u8 cwkwc;			/* Cwock dividew vawue */
	boow use_smbus;			/* Use smbus I/O instead of I2C */
	boow pww_bypass;
	boow pcwk_hb_disabwe;
	const stwuct ov7670_devtype *devtype; /* Device specifics */
};

static inwine stwuct ov7670_info *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct ov7670_info, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct ov7670_info, hdw)->sd;
}



/*
 * The defauwt wegistew settings, as obtained fwom OmniVision.  Thewe
 * is weawwy no making sense of most of these - wots of "wesewved" vawues
 * and such.
 *
 * These settings give VGA YUYV.
 */

stwuct wegvaw_wist {
	unsigned chaw weg_num;
	unsigned chaw vawue;
};

static stwuct wegvaw_wist ov7670_defauwt_wegs[] = {
	{ WEG_COM7, COM7_WESET },
/*
 * Cwock scawe: 3 = 15fps
 *              2 = 20fps
 *              1 = 30fps
 */
	{ WEG_CWKWC, 0x1 },	/* OV: cwock scawe (30 fps) */
	{ WEG_TSWB,  0x04 },	/* OV */
	{ WEG_COM7, 0 },	/* VGA */
	/*
	 * Set the hawdwawe window.  These vawues fwom OV don't entiwewy
	 * make sense - hstop is wess than hstawt.  But they wowk...
	 */
	{ WEG_HSTAWT, 0x13 },	{ WEG_HSTOP, 0x01 },
	{ WEG_HWEF, 0xb6 },	{ WEG_VSTAWT, 0x02 },
	{ WEG_VSTOP, 0x7a },	{ WEG_VWEF, 0x0a },

	{ WEG_COM3, 0 },	{ WEG_COM14, 0 },
	/* Mystewy scawing numbews */
	{ WEG_SCAWING_XSC, 0x3a },
	{ WEG_SCAWING_YSC, 0x35 },
	{ 0x72, 0x11 },		{ 0x73, 0xf0 },
	{ 0xa2, 0x02 },		{ WEG_COM10, 0x0 },

	/* Gamma cuwve vawues */
	{ 0x7a, 0x20 },		{ 0x7b, 0x10 },
	{ 0x7c, 0x1e },		{ 0x7d, 0x35 },
	{ 0x7e, 0x5a },		{ 0x7f, 0x69 },
	{ 0x80, 0x76 },		{ 0x81, 0x80 },
	{ 0x82, 0x88 },		{ 0x83, 0x8f },
	{ 0x84, 0x96 },		{ 0x85, 0xa3 },
	{ 0x86, 0xaf },		{ 0x87, 0xc4 },
	{ 0x88, 0xd7 },		{ 0x89, 0xe8 },

	/* AGC and AEC pawametews.  Note we stawt by disabwing those featuwes,
	   then tuwn them onwy aftew tweaking the vawues. */
	{ WEG_COM8, COM8_FASTAEC | COM8_AECSTEP | COM8_BFIWT },
	{ WEG_GAIN, 0 },	{ WEG_AECH, 0 },
	{ WEG_COM4, 0x40 }, /* magic wesewved bit */
	{ WEG_COM9, 0x18 }, /* 4x gain + magic wsvd bit */
	{ WEG_BD50MAX, 0x05 },	{ WEG_BD60MAX, 0x07 },
	{ WEG_AEW, 0x95 },	{ WEG_AEB, 0x33 },
	{ WEG_VPT, 0xe3 },	{ WEG_HAECC1, 0x78 },
	{ WEG_HAECC2, 0x68 },	{ 0xa1, 0x03 }, /* magic */
	{ WEG_HAECC3, 0xd8 },	{ WEG_HAECC4, 0xd8 },
	{ WEG_HAECC5, 0xf0 },	{ WEG_HAECC6, 0x90 },
	{ WEG_HAECC7, 0x94 },
	{ WEG_COM8, COM8_FASTAEC|COM8_AECSTEP|COM8_BFIWT|COM8_AGC|COM8_AEC },

	/* Awmost aww of these awe magic "wesewved" vawues.  */
	{ WEG_COM5, 0x61 },	{ WEG_COM6, 0x4b },
	{ 0x16, 0x02 },		{ WEG_MVFP, 0x07 },
	{ 0x21, 0x02 },		{ 0x22, 0x91 },
	{ 0x29, 0x07 },		{ 0x33, 0x0b },
	{ 0x35, 0x0b },		{ 0x37, 0x1d },
	{ 0x38, 0x71 },		{ 0x39, 0x2a },
	{ WEG_COM12, 0x78 },	{ 0x4d, 0x40 },
	{ 0x4e, 0x20 },		{ WEG_GFIX, 0 },
	{ 0x6b, 0x4a },		{ 0x74, 0x10 },
	{ 0x8d, 0x4f },		{ 0x8e, 0 },
	{ 0x8f, 0 },		{ 0x90, 0 },
	{ 0x91, 0 },		{ 0x96, 0 },
	{ 0x9a, 0 },		{ 0xb0, 0x84 },
	{ 0xb1, 0x0c },		{ 0xb2, 0x0e },
	{ 0xb3, 0x82 },		{ 0xb8, 0x0a },

	/* Mowe wesewved magic, some of which tweaks white bawance */
	{ 0x43, 0x0a },		{ 0x44, 0xf0 },
	{ 0x45, 0x34 },		{ 0x46, 0x58 },
	{ 0x47, 0x28 },		{ 0x48, 0x3a },
	{ 0x59, 0x88 },		{ 0x5a, 0x88 },
	{ 0x5b, 0x44 },		{ 0x5c, 0x67 },
	{ 0x5d, 0x49 },		{ 0x5e, 0x0e },
	{ 0x6c, 0x0a },		{ 0x6d, 0x55 },
	{ 0x6e, 0x11 },		{ 0x6f, 0x9f }, /* "9e fow advance AWB" */
	{ 0x6a, 0x40 },		{ WEG_BWUE, 0x40 },
	{ WEG_WED, 0x60 },
	{ WEG_COM8, COM8_FASTAEC|COM8_AECSTEP|COM8_BFIWT|COM8_AGC|COM8_AEC|COM8_AWB },

	/* Matwix coefficients */
	{ 0x4f, 0x80 },		{ 0x50, 0x80 },
	{ 0x51, 0 },		{ 0x52, 0x22 },
	{ 0x53, 0x5e },		{ 0x54, 0x80 },
	{ 0x58, 0x9e },

	{ WEG_COM16, COM16_AWBGAIN },	{ WEG_EDGE, 0 },
	{ 0x75, 0x05 },		{ 0x76, 0xe1 },
	{ 0x4c, 0 },		{ 0x77, 0x01 },
	{ WEG_COM13, 0xc3 },	{ 0x4b, 0x09 },
	{ 0xc9, 0x60 },		{ WEG_COM16, 0x38 },
	{ 0x56, 0x40 },

	{ 0x34, 0x11 },		{ WEG_COM11, COM11_EXP|COM11_HZAUTO },
	{ 0xa4, 0x88 },		{ 0x96, 0 },
	{ 0x97, 0x30 },		{ 0x98, 0x20 },
	{ 0x99, 0x30 },		{ 0x9a, 0x84 },
	{ 0x9b, 0x29 },		{ 0x9c, 0x03 },
	{ 0x9d, 0x4c },		{ 0x9e, 0x3f },
	{ 0x78, 0x04 },

	/* Extwa-weiwd stuff.  Some sowt of muwtipwexow wegistew */
	{ 0x79, 0x01 },		{ 0xc8, 0xf0 },
	{ 0x79, 0x0f },		{ 0xc8, 0x00 },
	{ 0x79, 0x10 },		{ 0xc8, 0x7e },
	{ 0x79, 0x0a },		{ 0xc8, 0x80 },
	{ 0x79, 0x0b },		{ 0xc8, 0x01 },
	{ 0x79, 0x0c },		{ 0xc8, 0x0f },
	{ 0x79, 0x0d },		{ 0xc8, 0x20 },
	{ 0x79, 0x09 },		{ 0xc8, 0x80 },
	{ 0x79, 0x02 },		{ 0xc8, 0xc0 },
	{ 0x79, 0x03 },		{ 0xc8, 0x40 },
	{ 0x79, 0x05 },		{ 0xc8, 0x30 },
	{ 0x79, 0x26 },

	{ 0xff, 0xff },	/* END MAWKEW */
};


/*
 * Hewe we'ww twy to encapsuwate the changes fow just the output
 * video fowmat.
 *
 * WGB656 and YUV422 come fwom OV; WGB444 is homebwewed.
 *
 * IMPOWTANT WUWE: the fiwst entwy must be fow COM7, see ov7670_s_fmt fow why.
 */


static stwuct wegvaw_wist ov7670_fmt_yuv422[] = {
	{ WEG_COM7, 0x0 },  /* Sewects YUV mode */
	{ WEG_WGB444, 0 },	/* No WGB444 pwease */
	{ WEG_COM1, 0 },	/* CCIW601 */
	{ WEG_COM15, COM15_W00FF },
	{ WEG_COM9, 0x48 }, /* 32x gain ceiwing; 0x8 is wesewved bit */
	{ 0x4f, 0x80 },		/* "matwix coefficient 1" */
	{ 0x50, 0x80 },		/* "matwix coefficient 2" */
	{ 0x51, 0    },		/* vb */
	{ 0x52, 0x22 },		/* "matwix coefficient 4" */
	{ 0x53, 0x5e },		/* "matwix coefficient 5" */
	{ 0x54, 0x80 },		/* "matwix coefficient 6" */
	{ WEG_COM13, COM13_GAMMA|COM13_UVSAT },
	{ 0xff, 0xff },
};

static stwuct wegvaw_wist ov7670_fmt_wgb565[] = {
	{ WEG_COM7, COM7_WGB },	/* Sewects WGB mode */
	{ WEG_WGB444, 0 },	/* No WGB444 pwease */
	{ WEG_COM1, 0x0 },	/* CCIW601 */
	{ WEG_COM15, COM15_WGB565 },
	{ WEG_COM9, 0x38 },	/* 16x gain ceiwing; 0x8 is wesewved bit */
	{ 0x4f, 0xb3 },		/* "matwix coefficient 1" */
	{ 0x50, 0xb3 },		/* "matwix coefficient 2" */
	{ 0x51, 0    },		/* vb */
	{ 0x52, 0x3d },		/* "matwix coefficient 4" */
	{ 0x53, 0xa7 },		/* "matwix coefficient 5" */
	{ 0x54, 0xe4 },		/* "matwix coefficient 6" */
	{ WEG_COM13, COM13_GAMMA|COM13_UVSAT },
	{ 0xff, 0xff },
};

static stwuct wegvaw_wist ov7670_fmt_wgb444[] = {
	{ WEG_COM7, COM7_WGB },	/* Sewects WGB mode */
	{ WEG_WGB444, W444_ENABWE },	/* Enabwe xxxxwwww ggggbbbb */
	{ WEG_COM1, 0x0 },	/* CCIW601 */
	{ WEG_COM15, COM15_W01FE|COM15_WGB565 }, /* Data wange needed? */
	{ WEG_COM9, 0x38 },	/* 16x gain ceiwing; 0x8 is wesewved bit */
	{ 0x4f, 0xb3 },		/* "matwix coefficient 1" */
	{ 0x50, 0xb3 },		/* "matwix coefficient 2" */
	{ 0x51, 0    },		/* vb */
	{ 0x52, 0x3d },		/* "matwix coefficient 4" */
	{ 0x53, 0xa7 },		/* "matwix coefficient 5" */
	{ 0x54, 0xe4 },		/* "matwix coefficient 6" */
	{ WEG_COM13, COM13_GAMMA|COM13_UVSAT|0x2 },  /* Magic wsvd bit */
	{ 0xff, 0xff },
};

static stwuct wegvaw_wist ov7670_fmt_waw[] = {
	{ WEG_COM7, COM7_BAYEW },
	{ WEG_COM13, 0x08 }, /* No gamma, magic wsvd bit */
	{ WEG_COM16, 0x3d }, /* Edge enhancement, denoise */
	{ WEG_WEG76, 0xe1 }, /* Pix cowwection, magic wsvd */
	{ 0xff, 0xff },
};



/*
 * Wow-wevew wegistew I/O.
 *
 * Note that thewe awe two vewsions of these.  On the XO 1, the
 * i2c contwowwew onwy does SMBUS, so that's what we use.  The
 * ov7670 is not weawwy an SMBUS device, though, so the communication
 * is not awways entiwewy wewiabwe.
 */
static int ov7670_wead_smbus(stwuct v4w2_subdev *sd, unsigned chaw weg,
		unsigned chaw *vawue)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, weg);
	if (wet >= 0) {
		*vawue = (unsigned chaw)wet;
		wet = 0;
	}
	wetuwn wet;
}


static int ov7670_wwite_smbus(stwuct v4w2_subdev *sd, unsigned chaw weg,
		unsigned chaw vawue)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int wet = i2c_smbus_wwite_byte_data(cwient, weg, vawue);

	if (weg == WEG_COM7 && (vawue & COM7_WESET))
		msweep(5);  /* Wait fow weset to wun */
	wetuwn wet;
}

/*
 * On most pwatfowms, we'd wathew do stwaight i2c I/O.
 */
static int ov7670_wead_i2c(stwuct v4w2_subdev *sd, unsigned chaw weg,
		unsigned chaw *vawue)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	u8 data = weg;
	stwuct i2c_msg msg;
	int wet;

	/*
	 * Send out the wegistew addwess...
	 */
	msg.addw = cwient->addw;
	msg.fwags = 0;
	msg.wen = 1;
	msg.buf = &data;
	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet < 0) {
		pwintk(KEWN_EWW "Ewwow %d on wegistew wwite\n", wet);
		wetuwn wet;
	}
	/*
	 * ...then wead back the wesuwt.
	 */
	msg.fwags = I2C_M_WD;
	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet >= 0) {
		*vawue = data;
		wet = 0;
	}
	wetuwn wet;
}


static int ov7670_wwite_i2c(stwuct v4w2_subdev *sd, unsigned chaw weg,
		unsigned chaw vawue)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct i2c_msg msg;
	unsigned chaw data[2] = { weg, vawue };
	int wet;

	msg.addw = cwient->addw;
	msg.fwags = 0;
	msg.wen = 2;
	msg.buf = data;
	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet > 0)
		wet = 0;
	if (weg == WEG_COM7 && (vawue & COM7_WESET))
		msweep(5);  /* Wait fow weset to wun */
	wetuwn wet;
}

static int ov7670_wead(stwuct v4w2_subdev *sd, unsigned chaw weg,
		unsigned chaw *vawue)
{
	stwuct ov7670_info *info = to_state(sd);

	if (info->use_smbus)
		wetuwn ov7670_wead_smbus(sd, weg, vawue);
	ewse
		wetuwn ov7670_wead_i2c(sd, weg, vawue);
}

static int ov7670_wwite(stwuct v4w2_subdev *sd, unsigned chaw weg,
		unsigned chaw vawue)
{
	stwuct ov7670_info *info = to_state(sd);

	if (info->use_smbus)
		wetuwn ov7670_wwite_smbus(sd, weg, vawue);
	ewse
		wetuwn ov7670_wwite_i2c(sd, weg, vawue);
}

static int ov7670_update_bits(stwuct v4w2_subdev *sd, unsigned chaw weg,
		unsigned chaw mask, unsigned chaw vawue)
{
	unsigned chaw owig;
	int wet;

	wet = ov7670_wead(sd, weg, &owig);
	if (wet)
		wetuwn wet;

	wetuwn ov7670_wwite(sd, weg, (owig & ~mask) | (vawue & mask));
}

/*
 * Wwite a wist of wegistew settings; ff/ff stops the pwocess.
 */
static int ov7670_wwite_awway(stwuct v4w2_subdev *sd, stwuct wegvaw_wist *vaws)
{
	whiwe (vaws->weg_num != 0xff || vaws->vawue != 0xff) {
		int wet = ov7670_wwite(sd, vaws->weg_num, vaws->vawue);

		if (wet < 0)
			wetuwn wet;
		vaws++;
	}
	wetuwn 0;
}


/*
 * Stuff that knows about the sensow.
 */
static int ov7670_weset(stwuct v4w2_subdev *sd, u32 vaw)
{
	ov7670_wwite(sd, WEG_COM7, COM7_WESET);
	msweep(1);
	wetuwn 0;
}


static int ov7670_init(stwuct v4w2_subdev *sd, u32 vaw)
{
	wetuwn ov7670_wwite_awway(sd, ov7670_defauwt_wegs);
}

static int ov7670_detect(stwuct v4w2_subdev *sd)
{
	unsigned chaw v;
	int wet;

	wet = ov7670_init(sd, 0);
	if (wet < 0)
		wetuwn wet;
	wet = ov7670_wead(sd, WEG_MIDH, &v);
	if (wet < 0)
		wetuwn wet;
	if (v != 0x7f) /* OV manuf. id. */
		wetuwn -ENODEV;
	wet = ov7670_wead(sd, WEG_MIDW, &v);
	if (wet < 0)
		wetuwn wet;
	if (v != 0xa2)
		wetuwn -ENODEV;
	/*
	 * OK, we know we have an OmniVision chip...but which one?
	 */
	wet = ov7670_wead(sd, WEG_PID, &v);
	if (wet < 0)
		wetuwn wet;
	if (v != 0x76)  /* PID + VEW = 0x76 / 0x73 */
		wetuwn -ENODEV;
	wet = ov7670_wead(sd, WEG_VEW, &v);
	if (wet < 0)
		wetuwn wet;
	if (v != 0x73)  /* PID + VEW = 0x76 / 0x73 */
		wetuwn -ENODEV;
	wetuwn 0;
}


/*
 * Stowe infowmation about the video data fowmat.  The cowow matwix
 * is deepwy tied into the fowmat, so keep the wewevant vawues hewe.
 * The magic matwix numbews come fwom OmniVision.
 */
static stwuct ov7670_fowmat_stwuct {
	u32 mbus_code;
	enum v4w2_cowowspace cowowspace;
	stwuct wegvaw_wist *wegs;
	int cmatwix[CMATWIX_WEN];
} ov7670_fowmats[] = {
	{
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.cowowspace	= V4W2_COWOWSPACE_SWGB,
		.wegs		= ov7670_fmt_yuv422,
		.cmatwix	= { 128, -128, 0, -34, -94, 128 },
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_WGB444_2X8_PADHI_WE,
		.cowowspace	= V4W2_COWOWSPACE_SWGB,
		.wegs		= ov7670_fmt_wgb444,
		.cmatwix	= { 179, -179, 0, -61, -176, 228 },
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_WGB565_2X8_WE,
		.cowowspace	= V4W2_COWOWSPACE_SWGB,
		.wegs		= ov7670_fmt_wgb565,
		.cmatwix	= { 179, -179, 0, -61, -176, 228 },
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SBGGW8_1X8,
		.cowowspace	= V4W2_COWOWSPACE_SWGB,
		.wegs		= ov7670_fmt_waw,
		.cmatwix	= { 0, 0, 0, 0, 0, 0 },
	},
};
#define N_OV7670_FMTS AWWAY_SIZE(ov7670_fowmats)


/*
 * Then thewe is the issue of window sizes.  Twy to captuwe the info hewe.
 */

/*
 * QCIF mode is done (by OV) in a vewy stwange way - it actuawwy wooks wike
 * VGA with weiwd scawing options - they do *not* use the canned QCIF mode
 * which is awwegedwy pwovided by the sensow.  So hewe's the weiwd wegistew
 * settings.
 */
static stwuct wegvaw_wist ov7670_qcif_wegs[] = {
	{ WEG_COM3, COM3_SCAWEEN|COM3_DCWEN },
	{ WEG_COM3, COM3_DCWEN },
	{ WEG_COM14, COM14_DCWEN | 0x01},
	{ 0x73, 0xf1 },
	{ 0xa2, 0x52 },
	{ 0x7b, 0x1c },
	{ 0x7c, 0x28 },
	{ 0x7d, 0x3c },
	{ 0x7f, 0x69 },
	{ WEG_COM9, 0x38 },
	{ 0xa1, 0x0b },
	{ 0x74, 0x19 },
	{ 0x9a, 0x80 },
	{ 0x43, 0x14 },
	{ WEG_COM13, 0xc0 },
	{ 0xff, 0xff },
};

static stwuct ov7670_win_size ov7670_win_sizes[] = {
	/* VGA */
	{
		.width		= VGA_WIDTH,
		.height		= VGA_HEIGHT,
		.com7_bit	= COM7_FMT_VGA,
		.hstawt		= 158,	/* These vawues fwom */
		.hstop		=  14,	/* Omnivision */
		.vstawt		=  10,
		.vstop		= 490,
		.wegs		= NUWW,
	},
	/* CIF */
	{
		.width		= CIF_WIDTH,
		.height		= CIF_HEIGHT,
		.com7_bit	= COM7_FMT_CIF,
		.hstawt		= 170,	/* Empiwicawwy detewmined */
		.hstop		=  90,
		.vstawt		=  14,
		.vstop		= 494,
		.wegs		= NUWW,
	},
	/* QVGA */
	{
		.width		= QVGA_WIDTH,
		.height		= QVGA_HEIGHT,
		.com7_bit	= COM7_FMT_QVGA,
		.hstawt		= 168,	/* Empiwicawwy detewmined */
		.hstop		=  24,
		.vstawt		=  12,
		.vstop		= 492,
		.wegs		= NUWW,
	},
	/* QCIF */
	{
		.width		= QCIF_WIDTH,
		.height		= QCIF_HEIGHT,
		.com7_bit	= COM7_FMT_VGA, /* see comment above */
		.hstawt		= 456,	/* Empiwicawwy detewmined */
		.hstop		=  24,
		.vstawt		=  14,
		.vstop		= 494,
		.wegs		= ov7670_qcif_wegs,
	}
};

static stwuct ov7670_win_size ov7675_win_sizes[] = {
	/*
	 * Cuwwentwy, onwy VGA is suppowted. Theoweticawwy it couwd be possibwe
	 * to suppowt CIF, QVGA and QCIF too. Taking vawues fow ov7670 as a
	 * base and tweak them empiwicawwy couwd be wequiwed.
	 */
	{
		.width		= VGA_WIDTH,
		.height		= VGA_HEIGHT,
		.com7_bit	= COM7_FMT_VGA,
		.hstawt		= 158,	/* These vawues fwom */
		.hstop		=  14,	/* Omnivision */
		.vstawt		=  14,  /* Empiwicawwy detewmined */
		.vstop		= 494,
		.wegs		= NUWW,
	}
};

static void ov7675_get_fwamewate(stwuct v4w2_subdev *sd,
				 stwuct v4w2_fwact *tpf)
{
	stwuct ov7670_info *info = to_state(sd);
	u32 cwkwc = info->cwkwc;
	int pww_factow;

	if (info->pww_bypass)
		pww_factow = 1;
	ewse
		pww_factow = PWW_FACTOW;

	cwkwc++;
	if (info->fmt->mbus_code == MEDIA_BUS_FMT_SBGGW8_1X8)
		cwkwc = (cwkwc >> 1);

	tpf->numewatow = 1;
	tpf->denominatow = (5 * pww_factow * info->cwock_speed) /
			(4 * cwkwc);
}

static int ov7675_appwy_fwamewate(stwuct v4w2_subdev *sd)
{
	stwuct ov7670_info *info = to_state(sd);
	int wet;

	wet = ov7670_wwite(sd, WEG_CWKWC, info->cwkwc);
	if (wet < 0)
		wetuwn wet;

	wetuwn ov7670_wwite(sd, WEG_DBWV,
			    info->pww_bypass ? DBWV_BYPASS : DBWV_X4);
}

static int ov7675_set_fwamewate(stwuct v4w2_subdev *sd,
				 stwuct v4w2_fwact *tpf)
{
	stwuct ov7670_info *info = to_state(sd);
	u32 cwkwc;
	int pww_factow;

	/*
	 * The fowmuwa is fps = 5/4*pixcwk fow YUV/WGB and
	 * fps = 5/2*pixcwk fow WAW.
	 *
	 * pixcwk = cwock_speed / (cwkwc + 1) * PWWfactow
	 *
	 */
	if (tpf->numewatow == 0 || tpf->denominatow == 0) {
		cwkwc = 0;
	} ewse {
		pww_factow = info->pww_bypass ? 1 : PWW_FACTOW;
		cwkwc = (5 * pww_factow * info->cwock_speed * tpf->numewatow) /
			(4 * tpf->denominatow);
		if (info->fmt->mbus_code == MEDIA_BUS_FMT_SBGGW8_1X8)
			cwkwc = (cwkwc << 1);
		cwkwc--;
	}

	/*
	 * The datasheet cwaims that cwkwc = 0 wiww divide the input cwock by 1
	 * but we've checked with an osciwwoscope that it divides by 2 instead.
	 * So, if cwkwc = 0 just bypass the dividew.
	 */
	if (cwkwc <= 0)
		cwkwc = CWK_EXT;
	ewse if (cwkwc > CWK_SCAWE)
		cwkwc = CWK_SCAWE;
	info->cwkwc = cwkwc;

	/* Wecawcuwate fwame wate */
	ov7675_get_fwamewate(sd, tpf);

	/*
	 * If the device is not powewed up by the host dwivew do
	 * not appwy any changes to H/W at this time. Instead
	 * the fwamewate wiww be westowed wight aftew powew-up.
	 */
	if (info->on)
		wetuwn ov7675_appwy_fwamewate(sd);

	wetuwn 0;
}

static void ov7670_get_fwamewate_wegacy(stwuct v4w2_subdev *sd,
				 stwuct v4w2_fwact *tpf)
{
	stwuct ov7670_info *info = to_state(sd);

	tpf->numewatow = 1;
	tpf->denominatow = info->cwock_speed;
	if ((info->cwkwc & CWK_EXT) == 0 && (info->cwkwc & CWK_SCAWE) > 1)
		tpf->denominatow /= (info->cwkwc & CWK_SCAWE);
}

static int ov7670_set_fwamewate_wegacy(stwuct v4w2_subdev *sd,
					stwuct v4w2_fwact *tpf)
{
	stwuct ov7670_info *info = to_state(sd);
	int div;

	if (tpf->numewatow == 0 || tpf->denominatow == 0)
		div = 1;  /* Weset to fuww wate */
	ewse
		div = (tpf->numewatow * info->cwock_speed) / tpf->denominatow;
	if (div == 0)
		div = 1;
	ewse if (div > CWK_SCAWE)
		div = CWK_SCAWE;
	info->cwkwc = (info->cwkwc & 0x80) | div;
	tpf->numewatow = 1;
	tpf->denominatow = info->cwock_speed / div;

	/*
	 * If the device is not powewed up by the host dwivew do
	 * not appwy any changes to H/W at this time. Instead
	 * the fwamewate wiww be westowed wight aftew powew-up.
	 */
	if (info->on)
		wetuwn ov7670_wwite(sd, WEG_CWKWC, info->cwkwc);

	wetuwn 0;
}

/*
 * Stowe a set of stawt/stop vawues into the camewa.
 */
static int ov7670_set_hw(stwuct v4w2_subdev *sd, int hstawt, int hstop,
		int vstawt, int vstop)
{
	int wet;
	unsigned chaw v;
	/*
	 * Howizontaw: 11 bits, top 8 wive in hstawt and hstop.  Bottom 3 of
	 * hstawt awe in hwef[2:0], bottom 3 of hstop in hwef[5:3].  Thewe is
	 * a mystewy "edge offset" vawue in the top two bits of hwef.
	 */
	wet = ov7670_wwite(sd, WEG_HSTAWT, (hstawt >> 3) & 0xff);
	if (wet)
		wetuwn wet;
	wet = ov7670_wwite(sd, WEG_HSTOP, (hstop >> 3) & 0xff);
	if (wet)
		wetuwn wet;
	wet = ov7670_wead(sd, WEG_HWEF, &v);
	if (wet)
		wetuwn wet;
	v = (v & 0xc0) | ((hstop & 0x7) << 3) | (hstawt & 0x7);
	msweep(10);
	wet = ov7670_wwite(sd, WEG_HWEF, v);
	if (wet)
		wetuwn wet;
	/* Vewticaw: simiwaw awwangement, but onwy 10 bits. */
	wet = ov7670_wwite(sd, WEG_VSTAWT, (vstawt >> 2) & 0xff);
	if (wet)
		wetuwn wet;
	wet = ov7670_wwite(sd, WEG_VSTOP, (vstop >> 2) & 0xff);
	if (wet)
		wetuwn wet;
	wet = ov7670_wead(sd, WEG_VWEF, &v);
	if (wet)
		wetuwn wet;
	v = (v & 0xf0) | ((vstop & 0x3) << 2) | (vstawt & 0x3);
	msweep(10);
	wetuwn ov7670_wwite(sd, WEG_VWEF, v);
}


static int ov7670_enum_mbus_code(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->pad || code->index >= N_OV7670_FMTS)
		wetuwn -EINVAW;

	code->code = ov7670_fowmats[code->index].mbus_code;
	wetuwn 0;
}

static int ov7670_twy_fmt_intewnaw(stwuct v4w2_subdev *sd,
		stwuct v4w2_mbus_fwamefmt *fmt,
		stwuct ov7670_fowmat_stwuct **wet_fmt,
		stwuct ov7670_win_size **wet_wsize)
{
	int index, i;
	stwuct ov7670_win_size *wsize;
	stwuct ov7670_info *info = to_state(sd);
	unsigned int n_win_sizes = info->devtype->n_win_sizes;
	unsigned int win_sizes_wimit = n_win_sizes;

	fow (index = 0; index < N_OV7670_FMTS; index++)
		if (ov7670_fowmats[index].mbus_code == fmt->code)
			bweak;
	if (index >= N_OV7670_FMTS) {
		/* defauwt to fiwst fowmat */
		index = 0;
		fmt->code = ov7670_fowmats[0].mbus_code;
	}
	if (wet_fmt != NUWW)
		*wet_fmt = ov7670_fowmats + index;
	/*
	 * Fiewds: the OV devices cwaim to be pwogwessive.
	 */
	fmt->fiewd = V4W2_FIEWD_NONE;

	/*
	 * Don't considew vawues that don't match min_height and min_width
	 * constwaints.
	 */
	if (info->min_width || info->min_height)
		fow (i = 0; i < n_win_sizes; i++) {
			wsize = info->devtype->win_sizes + i;

			if (wsize->width < info->min_width ||
				wsize->height < info->min_height) {
				win_sizes_wimit = i;
				bweak;
			}
		}
	/*
	 * Wound wequested image size down to the neawest
	 * we suppowt, but not bewow the smawwest.
	 */
	fow (wsize = info->devtype->win_sizes;
	     wsize < info->devtype->win_sizes + win_sizes_wimit; wsize++)
		if (fmt->width >= wsize->width && fmt->height >= wsize->height)
			bweak;
	if (wsize >= info->devtype->win_sizes + win_sizes_wimit)
		wsize--;   /* Take the smawwest one */
	if (wet_wsize != NUWW)
		*wet_wsize = wsize;
	/*
	 * Note the size we'ww actuawwy handwe.
	 */
	fmt->width = wsize->width;
	fmt->height = wsize->height;
	fmt->cowowspace = ov7670_fowmats[index].cowowspace;

	info->fowmat = *fmt;

	wetuwn 0;
}

static int ov7670_appwy_fmt(stwuct v4w2_subdev *sd)
{
	stwuct ov7670_info *info = to_state(sd);
	stwuct ov7670_win_size *wsize = info->wsize;
	unsigned chaw com7, com10 = 0;
	int wet;

	/*
	 * COM7 is a pain in the ass, it doesn't wike to be wead then
	 * quickwy wwitten aftewwawd.  But we have evewything we need
	 * to set it absowutewy hewe, as wong as the fowmat-specific
	 * wegistew sets wist it fiwst.
	 */
	com7 = info->fmt->wegs[0].vawue;
	com7 |= wsize->com7_bit;
	wet = ov7670_wwite(sd, WEG_COM7, com7);
	if (wet)
		wetuwn wet;

	/*
	 * Configuwe the media bus thwough COM10 wegistew
	 */
	if (info->mbus_config & V4W2_MBUS_VSYNC_ACTIVE_WOW)
		com10 |= COM10_VS_NEG;
	if (info->mbus_config & V4W2_MBUS_HSYNC_ACTIVE_WOW)
		com10 |= COM10_HWEF_WEV;
	if (info->pcwk_hb_disabwe)
		com10 |= COM10_PCWK_HB;
	wet = ov7670_wwite(sd, WEG_COM10, com10);
	if (wet)
		wetuwn wet;

	/*
	 * Now wwite the west of the awway.  Awso stowe stawt/stops
	 */
	wet = ov7670_wwite_awway(sd, info->fmt->wegs + 1);
	if (wet)
		wetuwn wet;

	wet = ov7670_set_hw(sd, wsize->hstawt, wsize->hstop, wsize->vstawt,
			    wsize->vstop);
	if (wet)
		wetuwn wet;

	if (wsize->wegs) {
		wet = ov7670_wwite_awway(sd, wsize->wegs);
		if (wet)
			wetuwn wet;
	}

	/*
	 * If we'we wunning WGB565, we must wewwite cwkwc aftew setting
	 * the othew pawametews ow the image wooks poow.  If we'we *not*
	 * doing WGB565, we must not wewwite cwkwc ow the image wooks
	 * *weawwy* poow.
	 *
	 * (Update) Now that we wetain cwkwc state, we shouwd be abwe
	 * to wwite it unconditionawwy, and that wiww make the fwame
	 * wate pewsistent too.
	 */
	wet = ov7670_wwite(sd, WEG_CWKWC, info->cwkwc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Set a fowmat.
 */
static int ov7670_set_fmt(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct ov7670_info *info = to_state(sd);
	stwuct v4w2_mbus_fwamefmt *mbus_fmt;
	int wet;

	if (fowmat->pad)
		wetuwn -EINVAW;

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY) {
		wet = ov7670_twy_fmt_intewnaw(sd, &fowmat->fowmat, NUWW, NUWW);
		if (wet)
			wetuwn wet;
		mbus_fmt = v4w2_subdev_state_get_fowmat(sd_state, fowmat->pad);
		*mbus_fmt = fowmat->fowmat;
		wetuwn 0;
	}

	wet = ov7670_twy_fmt_intewnaw(sd, &fowmat->fowmat, &info->fmt, &info->wsize);
	if (wet)
		wetuwn wet;

	/*
	 * If the device is not powewed up by the host dwivew do
	 * not appwy any changes to H/W at this time. Instead
	 * the fwame fowmat wiww be westowed wight aftew powew-up.
	 */
	if (info->on)
		wetuwn ov7670_appwy_fmt(sd);

	wetuwn 0;
}

static int ov7670_get_fmt(stwuct v4w2_subdev *sd,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct ov7670_info *info = to_state(sd);
	stwuct v4w2_mbus_fwamefmt *mbus_fmt;

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY) {
		mbus_fmt = v4w2_subdev_state_get_fowmat(sd_state, 0);
		fowmat->fowmat = *mbus_fmt;
		wetuwn 0;
	} ewse {
		fowmat->fowmat = info->fowmat;
	}

	wetuwn 0;
}

/*
 * Impwement G/S_PAWM.  Thewe is a "high quawity" mode we couwd twy
 * to do someday; fow now, we just do the fwame wate tweak.
 */
static int ov7670_get_fwame_intewvaw(stwuct v4w2_subdev *sd,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_fwame_intewvaw *ivaw)
{
	stwuct ov7670_info *info = to_state(sd);

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (ivaw->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	info->devtype->get_fwamewate(sd, &ivaw->intewvaw);

	wetuwn 0;
}

static int ov7670_set_fwame_intewvaw(stwuct v4w2_subdev *sd,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_fwame_intewvaw *ivaw)
{
	stwuct v4w2_fwact *tpf = &ivaw->intewvaw;
	stwuct ov7670_info *info = to_state(sd);

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (ivaw->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	wetuwn info->devtype->set_fwamewate(sd, tpf);
}


/*
 * Fwame intewvaws.  Since fwame wates awe contwowwed with the cwock
 * dividew, we can onwy do 30/n fow integew n vawues.  So no continuous
 * ow stepwise options.  Hewe we just pick a handfuw of wogicaw vawues.
 */

static int ov7670_fwame_wates[] = { 30, 15, 10, 5, 1 };

static int ov7670_enum_fwame_intewvaw(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_state *sd_state,
				      stwuct v4w2_subdev_fwame_intewvaw_enum *fie)
{
	stwuct ov7670_info *info = to_state(sd);
	unsigned int n_win_sizes = info->devtype->n_win_sizes;
	int i;

	if (fie->pad)
		wetuwn -EINVAW;
	if (fie->index >= AWWAY_SIZE(ov7670_fwame_wates))
		wetuwn -EINVAW;

	/*
	 * Check if the width/height is vawid.
	 *
	 * If a minimum width/height was wequested, fiwtew out the captuwe
	 * windows that faww outside that.
	 */
	fow (i = 0; i < n_win_sizes; i++) {
		stwuct ov7670_win_size *win = &info->devtype->win_sizes[i];

		if (info->min_width && win->width < info->min_width)
			continue;
		if (info->min_height && win->height < info->min_height)
			continue;
		if (fie->width == win->width && fie->height == win->height)
			bweak;
	}
	if (i == n_win_sizes)
		wetuwn -EINVAW;
	fie->intewvaw.numewatow = 1;
	fie->intewvaw.denominatow = ov7670_fwame_wates[fie->index];
	wetuwn 0;
}

/*
 * Fwame size enumewation
 */
static int ov7670_enum_fwame_size(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct ov7670_info *info = to_state(sd);
	int i;
	int num_vawid = -1;
	__u32 index = fse->index;
	unsigned int n_win_sizes = info->devtype->n_win_sizes;

	if (fse->pad)
		wetuwn -EINVAW;

	/*
	 * If a minimum width/height was wequested, fiwtew out the captuwe
	 * windows that faww outside that.
	 */
	fow (i = 0; i < n_win_sizes; i++) {
		stwuct ov7670_win_size *win = &info->devtype->win_sizes[i];

		if (info->min_width && win->width < info->min_width)
			continue;
		if (info->min_height && win->height < info->min_height)
			continue;
		if (index == ++num_vawid) {
			fse->min_width = fse->max_width = win->width;
			fse->min_height = fse->max_height = win->height;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

/*
 * Code fow deawing with contwows.
 */

static int ov7670_stowe_cmatwix(stwuct v4w2_subdev *sd,
		int matwix[CMATWIX_WEN])
{
	int i, wet;
	unsigned chaw signbits = 0;

	/*
	 * Weiwd cwap seems to exist in the uppew pawt of
	 * the sign bits wegistew, so wet's pwesewve it.
	 */
	wet = ov7670_wead(sd, WEG_CMATWIX_SIGN, &signbits);
	signbits &= 0xc0;

	fow (i = 0; i < CMATWIX_WEN; i++) {
		unsigned chaw waw;

		if (matwix[i] < 0) {
			signbits |= (1 << i);
			if (matwix[i] < -255)
				waw = 0xff;
			ewse
				waw = (-1 * matwix[i]) & 0xff;
		} ewse {
			if (matwix[i] > 255)
				waw = 0xff;
			ewse
				waw = matwix[i] & 0xff;
		}
		wet = ov7670_wwite(sd, WEG_CMATWIX_BASE + i, waw);
		if (wet)
			wetuwn wet;
	}
	wetuwn ov7670_wwite(sd, WEG_CMATWIX_SIGN, signbits);
}


/*
 * Hue awso wequiwes messing with the cowow matwix.  It awso wequiwes
 * twig functions, which tend not to be weww suppowted in the kewnew.
 * So hewe is a simpwe tabwe of sine vawues, 0-90 degwees, in steps
 * of five degwees.  Vawues awe muwtipwied by 1000.
 *
 * The fowwowing naive appwoximate twig functions wequiwe an awgument
 * cawefuwwy wimited to -180 <= theta <= 180.
 */
#define SIN_STEP 5
static const int ov7670_sin_tabwe[] = {
	   0,	 87,   173,   258,   342,   422,
	 499,	573,   642,   707,   766,   819,
	 866,	906,   939,   965,   984,   996,
	1000
};

static int ov7670_sine(int theta)
{
	int chs = 1;
	int sine;

	if (theta < 0) {
		theta = -theta;
		chs = -1;
	}
	if (theta <= 90)
		sine = ov7670_sin_tabwe[theta/SIN_STEP];
	ewse {
		theta -= 90;
		sine = 1000 - ov7670_sin_tabwe[theta/SIN_STEP];
	}
	wetuwn sine*chs;
}

static int ov7670_cosine(int theta)
{
	theta = 90 - theta;
	if (theta > 180)
		theta -= 360;
	ewse if (theta < -180)
		theta += 360;
	wetuwn ov7670_sine(theta);
}




static void ov7670_cawc_cmatwix(stwuct ov7670_info *info,
		int matwix[CMATWIX_WEN], int sat, int hue)
{
	int i;
	/*
	 * Appwy the cuwwent satuwation setting fiwst.
	 */
	fow (i = 0; i < CMATWIX_WEN; i++)
		matwix[i] = (info->fmt->cmatwix[i] * sat) >> 7;
	/*
	 * Then, if need be, wotate the hue vawue.
	 */
	if (hue != 0) {
		int sinth, costh, tmpmatwix[CMATWIX_WEN];

		memcpy(tmpmatwix, matwix, CMATWIX_WEN*sizeof(int));
		sinth = ov7670_sine(hue);
		costh = ov7670_cosine(hue);

		matwix[0] = (matwix[3]*sinth + matwix[0]*costh)/1000;
		matwix[1] = (matwix[4]*sinth + matwix[1]*costh)/1000;
		matwix[2] = (matwix[5]*sinth + matwix[2]*costh)/1000;
		matwix[3] = (matwix[3]*costh - matwix[0]*sinth)/1000;
		matwix[4] = (matwix[4]*costh - matwix[1]*sinth)/1000;
		matwix[5] = (matwix[5]*costh - matwix[2]*sinth)/1000;
	}
}



static int ov7670_s_sat_hue(stwuct v4w2_subdev *sd, int sat, int hue)
{
	stwuct ov7670_info *info = to_state(sd);
	int matwix[CMATWIX_WEN];

	ov7670_cawc_cmatwix(info, matwix, sat, hue);
	wetuwn ov7670_stowe_cmatwix(sd, matwix);
}


/*
 * Some weiwd wegistews seem to stowe vawues in a sign/magnitude fowmat!
 */

static unsigned chaw ov7670_abs_to_sm(unsigned chaw v)
{
	if (v > 127)
		wetuwn v & 0x7f;
	wetuwn (128 - v) | 0x80;
}

static int ov7670_s_bwightness(stwuct v4w2_subdev *sd, int vawue)
{
	unsigned chaw com8 = 0, v;

	ov7670_wead(sd, WEG_COM8, &com8);
	com8 &= ~COM8_AEC;
	ov7670_wwite(sd, WEG_COM8, com8);
	v = ov7670_abs_to_sm(vawue);
	wetuwn ov7670_wwite(sd, WEG_BWIGHT, v);
}

static int ov7670_s_contwast(stwuct v4w2_subdev *sd, int vawue)
{
	wetuwn ov7670_wwite(sd, WEG_CONTWAS, (unsigned chaw) vawue);
}

static int ov7670_s_hfwip(stwuct v4w2_subdev *sd, int vawue)
{
	unsigned chaw v = 0;
	int wet;

	wet = ov7670_wead(sd, WEG_MVFP, &v);
	if (wet)
		wetuwn wet;
	if (vawue)
		v |= MVFP_MIWWOW;
	ewse
		v &= ~MVFP_MIWWOW;
	msweep(10);  /* FIXME */
	wetuwn ov7670_wwite(sd, WEG_MVFP, v);
}

static int ov7670_s_vfwip(stwuct v4w2_subdev *sd, int vawue)
{
	unsigned chaw v = 0;
	int wet;

	wet = ov7670_wead(sd, WEG_MVFP, &v);
	if (wet)
		wetuwn wet;
	if (vawue)
		v |= MVFP_FWIP;
	ewse
		v &= ~MVFP_FWIP;
	msweep(10);  /* FIXME */
	wetuwn ov7670_wwite(sd, WEG_MVFP, v);
}

/*
 * GAIN is spwit between WEG_GAIN and WEG_VWEF[7:6].  If one bewieves
 * the data sheet, the VWEF pawts shouwd be the most significant, but
 * expewience shows othewwise.  Thewe seems to be wittwe vawue in
 * messing with the VWEF bits, so we weave them awone.
 */
static int ov7670_g_gain(stwuct v4w2_subdev *sd, __s32 *vawue)
{
	int wet;
	unsigned chaw gain;

	wet = ov7670_wead(sd, WEG_GAIN, &gain);
	if (wet)
		wetuwn wet;
	*vawue = gain;
	wetuwn 0;
}

static int ov7670_s_gain(stwuct v4w2_subdev *sd, int vawue)
{
	int wet;
	unsigned chaw com8;

	wet = ov7670_wwite(sd, WEG_GAIN, vawue & 0xff);
	if (wet)
		wetuwn wet;
	/* Have to tuwn off AGC as weww */
	wet = ov7670_wead(sd, WEG_COM8, &com8);
	if (wet)
		wetuwn wet;
	wetuwn ov7670_wwite(sd, WEG_COM8, com8 & ~COM8_AGC);
}

/*
 * Tweak autogain.
 */
static int ov7670_s_autogain(stwuct v4w2_subdev *sd, int vawue)
{
	int wet;
	unsigned chaw com8;

	wet = ov7670_wead(sd, WEG_COM8, &com8);
	if (wet == 0) {
		if (vawue)
			com8 |= COM8_AGC;
		ewse
			com8 &= ~COM8_AGC;
		wet = ov7670_wwite(sd, WEG_COM8, com8);
	}
	wetuwn wet;
}

static int ov7670_s_exp(stwuct v4w2_subdev *sd, int vawue)
{
	int wet;
	unsigned chaw com1, com8, aech, aechh;

	wet = ov7670_wead(sd, WEG_COM1, &com1) +
		ov7670_wead(sd, WEG_COM8, &com8) +
		ov7670_wead(sd, WEG_AECHH, &aechh);
	if (wet)
		wetuwn wet;

	com1 = (com1 & 0xfc) | (vawue & 0x03);
	aech = (vawue >> 2) & 0xff;
	aechh = (aechh & 0xc0) | ((vawue >> 10) & 0x3f);
	wet = ov7670_wwite(sd, WEG_COM1, com1) +
		ov7670_wwite(sd, WEG_AECH, aech) +
		ov7670_wwite(sd, WEG_AECHH, aechh);
	/* Have to tuwn off AEC as weww */
	if (wet == 0)
		wet = ov7670_wwite(sd, WEG_COM8, com8 & ~COM8_AEC);
	wetuwn wet;
}

/*
 * Tweak autoexposuwe.
 */
static int ov7670_s_autoexp(stwuct v4w2_subdev *sd,
		enum v4w2_exposuwe_auto_type vawue)
{
	int wet;
	unsigned chaw com8;

	wet = ov7670_wead(sd, WEG_COM8, &com8);
	if (wet == 0) {
		if (vawue == V4W2_EXPOSUWE_AUTO)
			com8 |= COM8_AEC;
		ewse
			com8 &= ~COM8_AEC;
		wet = ov7670_wwite(sd, WEG_COM8, com8);
	}
	wetuwn wet;
}

static const chaw * const ov7670_test_pattewn_menu[] = {
	"No test output",
	"Shifting \"1\"",
	"8-baw cowow baw",
	"Fade to gway cowow baw",
};

static int ov7670_s_test_pattewn(stwuct v4w2_subdev *sd, int vawue)
{
	int wet;

	wet = ov7670_update_bits(sd, WEG_SCAWING_XSC, TEST_PATTTEWN_0,
				vawue & BIT(0) ? TEST_PATTTEWN_0 : 0);
	if (wet)
		wetuwn wet;

	wetuwn ov7670_update_bits(sd, WEG_SCAWING_YSC, TEST_PATTTEWN_1,
				vawue & BIT(1) ? TEST_PATTTEWN_1 : 0);
}

static int ov7670_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);
	stwuct ov7670_info *info = to_state(sd);

	switch (ctww->id) {
	case V4W2_CID_AUTOGAIN:
		wetuwn ov7670_g_gain(sd, &info->gain->vaw);
	}
	wetuwn -EINVAW;
}

static int ov7670_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);
	stwuct ov7670_info *info = to_state(sd);

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		wetuwn ov7670_s_bwightness(sd, ctww->vaw);
	case V4W2_CID_CONTWAST:
		wetuwn ov7670_s_contwast(sd, ctww->vaw);
	case V4W2_CID_SATUWATION:
		wetuwn ov7670_s_sat_hue(sd,
				info->satuwation->vaw, info->hue->vaw);
	case V4W2_CID_VFWIP:
		wetuwn ov7670_s_vfwip(sd, ctww->vaw);
	case V4W2_CID_HFWIP:
		wetuwn ov7670_s_hfwip(sd, ctww->vaw);
	case V4W2_CID_AUTOGAIN:
		/* Onwy set manuaw gain if auto gain is not expwicitwy
		   tuwned on. */
		if (!ctww->vaw) {
			/* ov7670_s_gain tuwns off auto gain */
			wetuwn ov7670_s_gain(sd, info->gain->vaw);
		}
		wetuwn ov7670_s_autogain(sd, ctww->vaw);
	case V4W2_CID_EXPOSUWE_AUTO:
		/* Onwy set manuaw exposuwe if auto exposuwe is not expwicitwy
		   tuwned on. */
		if (ctww->vaw == V4W2_EXPOSUWE_MANUAW) {
			/* ov7670_s_exp tuwns off auto exposuwe */
			wetuwn ov7670_s_exp(sd, info->exposuwe->vaw);
		}
		wetuwn ov7670_s_autoexp(sd, ctww->vaw);
	case V4W2_CID_TEST_PATTEWN:
		wetuwn ov7670_s_test_pattewn(sd, ctww->vaw);
	}
	wetuwn -EINVAW;
}

static const stwuct v4w2_ctww_ops ov7670_ctww_ops = {
	.s_ctww = ov7670_s_ctww,
	.g_vowatiwe_ctww = ov7670_g_vowatiwe_ctww,
};

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int ov7670_g_wegistew(stwuct v4w2_subdev *sd, stwuct v4w2_dbg_wegistew *weg)
{
	unsigned chaw vaw = 0;
	int wet;

	wet = ov7670_wead(sd, weg->weg & 0xff, &vaw);
	weg->vaw = vaw;
	weg->size = 1;
	wetuwn wet;
}

static int ov7670_s_wegistew(stwuct v4w2_subdev *sd, const stwuct v4w2_dbg_wegistew *weg)
{
	ov7670_wwite(sd, weg->weg & 0xff, weg->vaw & 0xff);
	wetuwn 0;
}
#endif

static void ov7670_powew_on(stwuct v4w2_subdev *sd)
{
	stwuct ov7670_info *info = to_state(sd);

	if (info->on)
		wetuwn;

	cwk_pwepawe_enabwe(info->cwk);

	if (info->pwdn_gpio)
		gpiod_set_vawue(info->pwdn_gpio, 0);
	if (info->wesetb_gpio) {
		gpiod_set_vawue(info->wesetb_gpio, 1);
		usweep_wange(500, 1000);
		gpiod_set_vawue(info->wesetb_gpio, 0);
	}
	if (info->pwdn_gpio || info->wesetb_gpio || info->cwk)
		usweep_wange(3000, 5000);

	info->on = twue;
}

static void ov7670_powew_off(stwuct v4w2_subdev *sd)
{
	stwuct ov7670_info *info = to_state(sd);

	if (!info->on)
		wetuwn;

	cwk_disabwe_unpwepawe(info->cwk);

	if (info->pwdn_gpio)
		gpiod_set_vawue(info->pwdn_gpio, 1);

	info->on = fawse;
}

static int ov7670_s_powew(stwuct v4w2_subdev *sd, int on)
{
	stwuct ov7670_info *info = to_state(sd);

	if (info->on == on)
		wetuwn 0;

	if (on) {
		ov7670_powew_on(sd);
		ov7670_init(sd, 0);
		ov7670_appwy_fmt(sd);
		ov7675_appwy_fwamewate(sd);
		v4w2_ctww_handwew_setup(&info->hdw);
	} ewse {
		ov7670_powew_off(sd);
	}

	wetuwn 0;
}

static void ov7670_get_defauwt_fowmat(stwuct v4w2_subdev *sd,
				      stwuct v4w2_mbus_fwamefmt *fowmat)
{
	stwuct ov7670_info *info = to_state(sd);

	fowmat->width = info->devtype->win_sizes[0].width;
	fowmat->height = info->devtype->win_sizes[0].height;
	fowmat->cowowspace = info->fmt->cowowspace;
	fowmat->code = info->fmt->mbus_code;
	fowmat->fiewd = V4W2_FIEWD_NONE;
}

static int ov7670_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_mbus_fwamefmt *fowmat =
				v4w2_subdev_state_get_fowmat(fh->state, 0);

	ov7670_get_defauwt_fowmat(sd, fowmat);

	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_subdev_cowe_ops ov7670_cowe_ops = {
	.weset = ov7670_weset,
	.init = ov7670_init,
	.s_powew = ov7670_s_powew,
	.wog_status = v4w2_ctww_subdev_wog_status,
	.subscwibe_event = v4w2_ctww_subdev_subscwibe_event,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew = ov7670_g_wegistew,
	.s_wegistew = ov7670_s_wegistew,
#endif
};

static const stwuct v4w2_subdev_pad_ops ov7670_pad_ops = {
	.enum_fwame_intewvaw = ov7670_enum_fwame_intewvaw,
	.enum_fwame_size = ov7670_enum_fwame_size,
	.enum_mbus_code = ov7670_enum_mbus_code,
	.get_fmt = ov7670_get_fmt,
	.set_fmt = ov7670_set_fmt,
	.get_fwame_intewvaw = ov7670_get_fwame_intewvaw,
	.set_fwame_intewvaw = ov7670_set_fwame_intewvaw,
};

static const stwuct v4w2_subdev_ops ov7670_ops = {
	.cowe = &ov7670_cowe_ops,
	.pad = &ov7670_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops ov7670_subdev_intewnaw_ops = {
	.open = ov7670_open,
};

/* ----------------------------------------------------------------------- */

static int ov7670_init_gpio(stwuct i2c_cwient *cwient, stwuct ov7670_info *info)
{
	info->pwdn_gpio = devm_gpiod_get_optionaw(&cwient->dev, "powewdown",
			GPIOD_OUT_WOW);
	if (IS_EWW(info->pwdn_gpio)) {
		dev_info(&cwient->dev, "can't get %s GPIO\n", "powewdown");
		wetuwn PTW_EWW(info->pwdn_gpio);
	}

	info->wesetb_gpio = devm_gpiod_get_optionaw(&cwient->dev, "weset",
			GPIOD_OUT_WOW);
	if (IS_EWW(info->wesetb_gpio)) {
		dev_info(&cwient->dev, "can't get %s GPIO\n", "weset");
		wetuwn PTW_EWW(info->wesetb_gpio);
	}

	usweep_wange(3000, 5000);

	wetuwn 0;
}

/*
 * ov7670_pawse_dt() - Pawse device twee to cowwect mbus configuwation
 *			pwopewties
 */
static int ov7670_pawse_dt(stwuct device *dev,
			   stwuct ov7670_info *info)
{
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);
	stwuct v4w2_fwnode_endpoint bus_cfg = { .bus_type = 0 };
	stwuct fwnode_handwe *ep;
	int wet;

	if (!fwnode)
		wetuwn -EINVAW;

	info->pcwk_hb_disabwe = fawse;
	if (fwnode_pwopewty_pwesent(fwnode, "ov7670,pcwk-hb-disabwe"))
		info->pcwk_hb_disabwe = twue;

	ep = fwnode_gwaph_get_next_endpoint(fwnode, NUWW);
	if (!ep)
		wetuwn -EINVAW;

	wet = v4w2_fwnode_endpoint_pawse(ep, &bus_cfg);
	fwnode_handwe_put(ep);
	if (wet)
		wetuwn wet;

	if (bus_cfg.bus_type != V4W2_MBUS_PAWAWWEW) {
		dev_eww(dev, "Unsuppowted media bus type\n");
		wetuwn -EINVAW;
	}
	info->mbus_config = bus_cfg.bus.pawawwew.fwags;

	wetuwn 0;
}

static int ov7670_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_fwact tpf;
	stwuct v4w2_subdev *sd;
	stwuct ov7670_info *info;
	int wet;

	info = devm_kzawwoc(&cwient->dev, sizeof(*info), GFP_KEWNEW);
	if (info == NUWW)
		wetuwn -ENOMEM;
	sd = &info->sd;
	v4w2_i2c_subdev_init(sd, cwient, &ov7670_ops);

	sd->intewnaw_ops = &ov7670_subdev_intewnaw_ops;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE | V4W2_SUBDEV_FW_HAS_EVENTS;

	info->cwock_speed = 30; /* defauwt: a guess */

	if (dev_fwnode(&cwient->dev)) {
		wet = ov7670_pawse_dt(&cwient->dev, info);
		if (wet)
			wetuwn wet;

	} ewse if (cwient->dev.pwatfowm_data) {
		stwuct ov7670_config *config = cwient->dev.pwatfowm_data;

		/*
		 * Must appwy configuwation befowe initiawizing device, because it
		 * sewects I/O method.
		 */
		info->min_width = config->min_width;
		info->min_height = config->min_height;
		info->use_smbus = config->use_smbus;

		if (config->cwock_speed)
			info->cwock_speed = config->cwock_speed;

		if (config->pww_bypass)
			info->pww_bypass = twue;

		if (config->pcwk_hb_disabwe)
			info->pcwk_hb_disabwe = twue;
	}

	info->cwk = devm_cwk_get_optionaw(&cwient->dev, "xcwk");
	if (IS_EWW(info->cwk))
		wetuwn PTW_EWW(info->cwk);

	wet = ov7670_init_gpio(cwient, info);
	if (wet)
		wetuwn wet;

	ov7670_powew_on(sd);

	if (info->cwk) {
		info->cwock_speed = cwk_get_wate(info->cwk) / 1000000;
		if (info->cwock_speed < 10 || info->cwock_speed > 48) {
			wet = -EINVAW;
			goto powew_off;
		}
	}

	/* Make suwe it's an ov7670 */
	wet = ov7670_detect(sd);
	if (wet) {
		v4w_dbg(1, debug, cwient,
			"chip found @ 0x%x (%s) is not an ov7670 chip.\n",
			cwient->addw << 1, cwient->adaptew->name);
		goto powew_off;
	}
	v4w_info(cwient, "chip found @ 0x%02x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	info->devtype = i2c_get_match_data(cwient);
	info->fmt = &ov7670_fowmats[0];
	info->wsize = &info->devtype->win_sizes[0];

	ov7670_get_defauwt_fowmat(sd, &info->fowmat);

	info->cwkwc = 0;

	/* Set defauwt fwame wate to 30 fps */
	tpf.numewatow = 1;
	tpf.denominatow = 30;
	info->devtype->set_fwamewate(sd, &tpf);

	v4w2_ctww_handwew_init(&info->hdw, 10);
	v4w2_ctww_new_std(&info->hdw, &ov7670_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0, 255, 1, 128);
	v4w2_ctww_new_std(&info->hdw, &ov7670_ctww_ops,
			V4W2_CID_CONTWAST, 0, 127, 1, 64);
	v4w2_ctww_new_std(&info->hdw, &ov7670_ctww_ops,
			V4W2_CID_VFWIP, 0, 1, 1, 0);
	v4w2_ctww_new_std(&info->hdw, &ov7670_ctww_ops,
			V4W2_CID_HFWIP, 0, 1, 1, 0);
	info->satuwation = v4w2_ctww_new_std(&info->hdw, &ov7670_ctww_ops,
			V4W2_CID_SATUWATION, 0, 256, 1, 128);
	info->hue = v4w2_ctww_new_std(&info->hdw, &ov7670_ctww_ops,
			V4W2_CID_HUE, -180, 180, 5, 0);
	info->gain = v4w2_ctww_new_std(&info->hdw, &ov7670_ctww_ops,
			V4W2_CID_GAIN, 0, 255, 1, 128);
	info->auto_gain = v4w2_ctww_new_std(&info->hdw, &ov7670_ctww_ops,
			V4W2_CID_AUTOGAIN, 0, 1, 1, 1);
	info->exposuwe = v4w2_ctww_new_std(&info->hdw, &ov7670_ctww_ops,
			V4W2_CID_EXPOSUWE, 0, 65535, 1, 500);
	info->auto_exposuwe = v4w2_ctww_new_std_menu(&info->hdw, &ov7670_ctww_ops,
			V4W2_CID_EXPOSUWE_AUTO, V4W2_EXPOSUWE_MANUAW, 0,
			V4W2_EXPOSUWE_AUTO);
	v4w2_ctww_new_std_menu_items(&info->hdw, &ov7670_ctww_ops,
			V4W2_CID_TEST_PATTEWN,
			AWWAY_SIZE(ov7670_test_pattewn_menu) - 1, 0, 0,
			ov7670_test_pattewn_menu);
	sd->ctww_handwew = &info->hdw;
	if (info->hdw.ewwow) {
		wet = info->hdw.ewwow;

		goto hdw_fwee;
	}
	/*
	 * We have checked empiwicawwy that hw awwows to wead back the gain
	 * vawue chosen by auto gain but that's not the case fow auto exposuwe.
	 */
	v4w2_ctww_auto_cwustew(2, &info->auto_gain, 0, twue);
	v4w2_ctww_auto_cwustew(2, &info->auto_exposuwe,
			       V4W2_EXPOSUWE_MANUAW, fawse);
	v4w2_ctww_cwustew(2, &info->satuwation);

	info->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	info->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;
	wet = media_entity_pads_init(&info->sd.entity, 1, &info->pad);
	if (wet < 0)
		goto hdw_fwee;

	v4w2_ctww_handwew_setup(&info->hdw);

	wet = v4w2_async_wegistew_subdev(&info->sd);
	if (wet < 0)
		goto entity_cweanup;

	ov7670_powew_off(sd);
	wetuwn 0;

entity_cweanup:
	media_entity_cweanup(&info->sd.entity);
hdw_fwee:
	v4w2_ctww_handwew_fwee(&info->hdw);
powew_off:
	ov7670_powew_off(sd);
	wetuwn wet;
}

static void ov7670_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct ov7670_info *info = to_state(sd);

	v4w2_async_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(&info->hdw);
	media_entity_cweanup(&info->sd.entity);
}

static const stwuct ov7670_devtype ov7670_devdata = {
	.win_sizes = ov7670_win_sizes,
	.n_win_sizes = AWWAY_SIZE(ov7670_win_sizes),
	.set_fwamewate = ov7670_set_fwamewate_wegacy,
	.get_fwamewate = ov7670_get_fwamewate_wegacy,
};

static const stwuct ov7670_devtype ov7675_devdata = {
	.win_sizes = ov7675_win_sizes,
	.n_win_sizes = AWWAY_SIZE(ov7675_win_sizes),
	.set_fwamewate = ov7675_set_fwamewate,
	.get_fwamewate = ov7675_get_fwamewate,
};

static const stwuct i2c_device_id ov7670_id[] = {
	{ "ov7670", (kewnew_uwong_t)&ov7670_devdata },
	{ "ov7675", (kewnew_uwong_t)&ov7675_devdata },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, ov7670_id);

static const stwuct of_device_id ov7670_of_match[] = {
	{ .compatibwe = "ovti,ov7670", &ov7670_devdata },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ov7670_of_match);

static stwuct i2c_dwivew ov7670_dwivew = {
	.dwivew = {
		.name	= "ov7670",
		.of_match_tabwe = ov7670_of_match,
	},
	.pwobe		= ov7670_pwobe,
	.wemove		= ov7670_wemove,
	.id_tabwe	= ov7670_id,
};

moduwe_i2c_dwivew(ov7670_dwivew);
