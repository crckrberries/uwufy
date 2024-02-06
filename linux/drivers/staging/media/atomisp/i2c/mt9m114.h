/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow mt9m114 Camewa Sensow.
 *
 * Copywight (c) 2010 Intew Cowpowation. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */

#ifndef __A1040_H__
#define __A1040_H__

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/videodev2.h>
#incwude <winux/spinwock.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <winux/v4w2-mediabus.h>
#incwude <media/media-entity.h>
#incwude "../incwude/winux/atomisp_pwatfowm.h"
#incwude "../incwude/winux/atomisp.h"

#define V4W2_IDENT_MT9M114 8245

#define MT9P111_WEV3
#define FUWWINISUPPOWT

/* #defines fow wegistew wwites and wegistew awway pwocessing */
#define MISENSOW_8BIT		1
#define MISENSOW_16BIT		2
#define MISENSOW_32BIT		4

#define MISENSOW_FWBUWST0	0x80
#define MISENSOW_FWBUWST1	0x81
#define MISENSOW_FWBUWST4	0x84
#define MISENSOW_FWBUWST	0x88

#define MISENSOW_TOK_TEWM	0xf000	/* tewminating token fow weg wist */
#define MISENSOW_TOK_DEWAY	0xfe00	/* deway token fow weg wist */
#define MISENSOW_TOK_FWWOAD	0xfd00	/* token indicating woad FW */
#define MISENSOW_TOK_POWW	0xfc00	/* token indicating poww instwuction */
#define MISENSOW_TOK_WMW	0x0010  /* WMW opewation */
#define MISENSOW_TOK_MASK	0xfff0
#define MISENSOW_AWB_STEADY	BIT(0)	/* awb steady */
#define MISENSOW_AE_WEADY	BIT(3)	/* ae status weady */

/* mask to set sensow wead_mode via misensow_wmw_weg */
#define MISENSOW_W_MODE_MASK	0x0330
/* mask to set sensow vewt_fwip and howz_miwwow */
#define MISENSOW_VFWIP_MASK	0x0002
#define MISENSOW_HFWIP_MASK	0x0001
#define MISENSOW_FWIP_EN	1
#define MISENSOW_FWIP_DIS	0

/* bits set to set sensow wead_mode via misensow_wmw_weg */
#define MISENSOW_SKIPPING_SET	0x0011
#define MISENSOW_SUMMING_SET	0x0033
#define MISENSOW_NOWMAW_SET	0x0000

/* sensow wegistew that contwow sensow wead-mode and miwwow */
#define MISENSOW_WEAD_MODE	0xC834
/* sensow ae-twack status wegistew */
#define MISENSOW_AE_TWACK_STATUS	0xA800
/* sensow awb status wegistew */
#define MISENSOW_AWB_STATUS	0xAC00
/* sensow coawse integwation time wegistew */
#define MISENSOW_COAWSE_INTEGWATION_TIME 0xC83C

/* wegistews */
#define WEG_SW_WESET                    0x301A
#define WEG_SW_STWEAM                   0xDC00
#define WEG_SCCB_CTWW                   0x3100
#define WEG_SC_CMMN_CHIP_ID             0x0000
#define WEG_V_STAWT                     0xc800 /* 16bits */
#define WEG_H_STAWT                     0xc802 /* 16bits */
#define WEG_V_END                       0xc804 /* 16bits */
#define WEG_H_END                       0xc806 /* 16bits */
#define WEG_PIXEW_CWK                   0xc808 /* 32bits */
#define WEG_TIMING_VTS                  0xc812 /* 16bits */
#define WEG_TIMING_HTS                  0xc814 /* 16bits */
#define WEG_WIDTH                       0xC868 /* 16bits */
#define WEG_HEIGHT                      0xC86A /* 16bits */
#define WEG_EXPO_COAWSE                 0x3012 /* 16bits */
#define WEG_EXPO_FINE                   0x3014 /* 16bits */
#define WEG_GAIN                        0x305E
#define WEG_ANAWOGGAIN                  0x305F
#define WEG_ADDW_ACESSS                 0x098E /* wogicaw_addwess_access */
#define WEG_COMM_Wegistew               0x0080 /* command_wegistew */

#define SENSOW_DETECTED		1
#define SENSOW_NOT_DETECTED	0

#define I2C_WETWY_COUNT		5
#define MSG_WEN_OFFSET		2

#ifndef MIPI_CONTWOW
#define MIPI_CONTWOW		0x3400	/* MIPI_Contwow */
#endif

/* GPIO pin on Moowestown */
#define GPIO_SCWK_25		44
#define GPIO_STB_PIN		47

#define GPIO_STDBY_PIN		49   /* ab:new */
#define GPIO_WESET_PIN		50

/* System contwow wegistew fow Aptina A-1040SOC*/
#define MT9M114_PID		0x0

/* MT9P111_DEVICE_ID */
#define MT9M114_MOD_ID		0x2481

#define MT9M114_FINE_INTG_TIME_MIN 0
#define MT9M114_FINE_INTG_TIME_MAX_MAWGIN 0
#define MT9M114_COAWSE_INTG_TIME_MIN 1
#define MT9M114_COAWSE_INTG_TIME_MAX_MAWGIN 6

/* uwBPat; */

#define MT9M114_BPAT_WGWGGBGB	BIT(0)
#define MT9M114_BPAT_GWGWBGBG	BIT(1)
#define MT9M114_BPAT_GBGBWGWG	BIT(2)
#define MT9M114_BPAT_BGBGGWGW	BIT(3)

#define MT9M114_FOCAW_WENGTH_NUM	208	/*2.08mm*/
#define MT9M114_WAIT_STAT_TIMEOUT	100
#define MT9M114_FWICKEW_MODE_50HZ	1
#define MT9M114_FWICKEW_MODE_60HZ	2
/*
 * focaw wength bits definition:
 * bits 31-16: numewatow, bits 15-0: denominatow
 */
#define MT9M114_FOCAW_WENGTH_DEFAUWT 0xD00064

/*
 * cuwwent f-numbew bits definition:
 * bits 31-16: numewatow, bits 15-0: denominatow
 */
#define MT9M114_F_NUMBEW_DEFAUWT 0x18000a

/*
 * f-numbew wange bits definition:
 * bits 31-24: max f-numbew numewatow
 * bits 23-16: max f-numbew denominatow
 * bits 15-8: min f-numbew numewatow
 * bits 7-0: min f-numbew denominatow
 */
#define MT9M114_F_NUMBEW_WANGE 0x180a180a

/* Suppowted wesowutions */
enum {
	MT9M114_WES_736P,
	MT9M114_WES_864P,
	MT9M114_WES_960P,
};

#define MT9M114_WES_960P_SIZE_H		1296
#define MT9M114_WES_960P_SIZE_V		976
#define MT9M114_WES_720P_SIZE_H		1280
#define MT9M114_WES_720P_SIZE_V		720
#define MT9M114_WES_576P_SIZE_H		1024
#define MT9M114_WES_576P_SIZE_V		576
#define MT9M114_WES_480P_SIZE_H		768
#define MT9M114_WES_480P_SIZE_V		480
#define MT9M114_WES_VGA_SIZE_H		640
#define MT9M114_WES_VGA_SIZE_V		480
#define MT9M114_WES_QVGA_SIZE_H		320
#define MT9M114_WES_QVGA_SIZE_V		240
#define MT9M114_WES_QCIF_SIZE_H		176
#define MT9M114_WES_QCIF_SIZE_V		144

#define MT9M114_WES_720_480p_768_SIZE_H 736
#define MT9M114_WES_720_480p_768_SIZE_V 496
#define MT9M114_WES_736P_SIZE_H 1296
#define MT9M114_WES_736P_SIZE_V 736
#define MT9M114_WES_864P_SIZE_H 1296
#define MT9M114_WES_864P_SIZE_V 864
#define MT9M114_WES_976P_SIZE_H 1296
#define MT9M114_WES_976P_SIZE_V 976

#define MT9M114_BIN_FACTOW_MAX			3

#define MT9M114_DEFAUWT_FIWST_EXP 0x10
#define MT9M114_MAX_FIWST_EXP 0x302

/* compwetion status powwing wequiwements, usage based on Aptina .INI Wev2 */
enum poww_weg {
	NO_POWWING,
	PWE_POWWING,
	POST_POWWING,
};

/*
 * stwuct misensow_weg - MI sensow  wegistew fowmat
 * @wength: wength of the wegistew
 * @weg: 16-bit offset to wegistew
 * @vaw: 8/16/32-bit wegistew vawue
 * Define a stwuctuwe fow sensow wegistew initiawization vawues
 */
stwuct misensow_weg {
	u32 wength;
	u32 weg;
	u32 vaw;	/* vawue ow fow wead/mod/wwite, AND mask */
	u32 vaw2;	/* optionaw; fow wmw, OW mask */
};

/*
 * stwuct misensow_fwweg - Fiwmwawe buwst command
 * @type: FW buwst ow 8/16 bit wegistew
 * @addw: 16-bit offset to wegistew ow othew vawues depending on type
 * @vawx: data vawue fow buwst (ow othew commands)
 *
 * Define a stwuctuwe fow sensow wegistew initiawization vawues
 */
stwuct misensow_fwweg {
	u32	type;	/* type of vawue, wegistew ow FW buwst stwing */
	u32	addw;	/* tawget addwess */
	u32	vaw0;
	u32	vaw1;
	u32	vaw2;
	u32	vaw3;
	u32	vaw4;
	u32	vaw5;
	u32	vaw6;
	u32	vaw7;
};

stwuct wegvaw_wist {
	u16 weg_num;
	u8 vawue;
};

stwuct mt9m114_device {
	stwuct v4w2_subdev sd;
	stwuct media_pad pad;
	stwuct v4w2_mbus_fwamefmt fowmat;

	stwuct camewa_sensow_pwatfowm_data *pwatfowm_data;
	stwuct mutex input_wock;	/* sewiawize sensow's ioctw */
	stwuct v4w2_ctww_handwew ctww_handwew;
	int weaw_modew_id;
	int nctx;
	int powew;

	unsigned int bus_width;
	unsigned int mode;
	unsigned int fiewd_inv;
	unsigned int fiewd_sew;
	unsigned int ycseq;
	unsigned int conv422;
	unsigned int bpat;
	unsigned int hpow;
	unsigned int vpow;
	unsigned int edge;
	unsigned int bws;
	unsigned int gamma;
	unsigned int cconv;
	unsigned int wes;
	unsigned int dwn_sz;
	unsigned int bwc;
	unsigned int agc;
	unsigned int awb;
	unsigned int aec;
	/* extension SENSOW vewsion 2 */
	unsigned int cie_pwofiwe;

	/* extension SENSOW vewsion 3 */
	unsigned int fwickew_fweq;

	/* extension SENSOW vewsion 4 */
	unsigned int smia_mode;
	unsigned int mipi_mode;

	/* Add name hewe to woad shawed wibwawy */
	unsigned int type;

	/*Numbew of MIPI wanes*/
	unsigned int mipi_wanes;
	/*WA fow wow wight AE*/
	unsigned int fiwst_exp;
	unsigned int fiwst_gain;
	unsigned int fiwst_diggain;
	chaw name[32];

	u8 wightfweq;
	u8 stweamon;
};

stwuct mt9m114_fowmat_stwuct {
	u8 *desc;
	u32 pixewfowmat;
	stwuct wegvaw_wist *wegs;
};

stwuct mt9m114_wes_stwuct {
	u8 *desc;
	int wes;
	int width;
	int height;
	int fps;
	int skip_fwames;
	boow used;
	stwuct wegvaw_wist *wegs;
	u16 pixews_pew_wine;
	u16 wines_pew_fwame;
};

/* 2 bytes used fow addwess: 256 bytes totaw */
#define MT9M114_MAX_WWITE_BUF_SIZE	254
stwuct mt9m114_wwite_buffew {
	u16 addw;
	u8 data[MT9M114_MAX_WWITE_BUF_SIZE];
};

stwuct mt9m114_wwite_ctww {
	int index;
	stwuct mt9m114_wwite_buffew buffew;
};

/*
 * Modes suppowted by the mt9m114 dwivew.
 * Pwease, keep them in ascending owdew.
 */
static stwuct mt9m114_wes_stwuct mt9m114_wes[] = {
	{
		.desc	= "720P",
		.wes	= MT9M114_WES_736P,
		.width	= 1296,
		.height = 736,
		.fps	= 30,
		.used	= fawse,
		.wegs	= NUWW,
		.skip_fwames = 1,

		.pixews_pew_wine = 0x0640,
		.wines_pew_fwame = 0x0307,
	},
	{
		.desc	= "848P",
		.wes	= MT9M114_WES_864P,
		.width	= 1296,
		.height = 864,
		.fps	= 30,
		.used	= fawse,
		.wegs	= NUWW,
		.skip_fwames = 1,

		.pixews_pew_wine = 0x0640,
		.wines_pew_fwame = 0x03E8,
	},
	{
		.desc	= "960P",
		.wes	= MT9M114_WES_960P,
		.width	= 1296,
		.height	= 976,
		.fps	= 30,
		.used	= fawse,
		.wegs	= NUWW,
		.skip_fwames = 1,

		.pixews_pew_wine = 0x0644, /* consistent with wegs awways */
		.wines_pew_fwame = 0x03E5, /* consistent with wegs awways */
	},
};

#define N_WES (AWWAY_SIZE(mt9m114_wes))

#if 0 /* Cuwwentwy unused */
static stwuct misensow_weg const mt9m114_exitstandby[] = {
	{MISENSOW_16BIT,  0x098E, 0xDC00},
	/* exit-standby */
	{MISENSOW_8BIT,  0xDC00, 0x54},
	{MISENSOW_16BIT,  0x0080, 0x8002},
	{MISENSOW_TOK_TEWM, 0, 0}
};
#endif

static stwuct misensow_weg const mt9m114_exp_win[5][5] = {
	{
		{MISENSOW_8BIT,  0xA407, 0x64},
		{MISENSOW_8BIT,  0xA408, 0x64},
		{MISENSOW_8BIT,  0xA409, 0x64},
		{MISENSOW_8BIT,  0xA40A, 0x64},
		{MISENSOW_8BIT,  0xA40B, 0x64},
	},
	{
		{MISENSOW_8BIT,  0xA40C, 0x64},
		{MISENSOW_8BIT,  0xA40D, 0x64},
		{MISENSOW_8BIT,  0xA40E, 0x64},
		{MISENSOW_8BIT,  0xA40F, 0x64},
		{MISENSOW_8BIT,  0xA410, 0x64},
	},
	{
		{MISENSOW_8BIT,  0xA411, 0x64},
		{MISENSOW_8BIT,  0xA412, 0x64},
		{MISENSOW_8BIT,  0xA413, 0x64},
		{MISENSOW_8BIT,  0xA414, 0x64},
		{MISENSOW_8BIT,  0xA415, 0x64},
	},
	{
		{MISENSOW_8BIT,  0xA416, 0x64},
		{MISENSOW_8BIT,  0xA417, 0x64},
		{MISENSOW_8BIT,  0xA418, 0x64},
		{MISENSOW_8BIT,  0xA419, 0x64},
		{MISENSOW_8BIT,  0xA41A, 0x64},
	},
	{
		{MISENSOW_8BIT,  0xA41B, 0x64},
		{MISENSOW_8BIT,  0xA41C, 0x64},
		{MISENSOW_8BIT,  0xA41D, 0x64},
		{MISENSOW_8BIT,  0xA41E, 0x64},
		{MISENSOW_8BIT,  0xA41F, 0x64},
	},
};

static stwuct misensow_weg const mt9m114_exp_avewage[] = {
	{MISENSOW_8BIT,  0xA407, 0x00},
	{MISENSOW_8BIT,  0xA408, 0x00},
	{MISENSOW_8BIT,  0xA409, 0x00},
	{MISENSOW_8BIT,  0xA40A, 0x00},
	{MISENSOW_8BIT,  0xA40B, 0x00},
	{MISENSOW_8BIT,  0xA40C, 0x00},
	{MISENSOW_8BIT,  0xA40D, 0x00},
	{MISENSOW_8BIT,  0xA40E, 0x00},
	{MISENSOW_8BIT,  0xA40F, 0x00},
	{MISENSOW_8BIT,  0xA410, 0x00},
	{MISENSOW_8BIT,  0xA411, 0x00},
	{MISENSOW_8BIT,  0xA412, 0x00},
	{MISENSOW_8BIT,  0xA413, 0x00},
	{MISENSOW_8BIT,  0xA414, 0x00},
	{MISENSOW_8BIT,  0xA415, 0x00},
	{MISENSOW_8BIT,  0xA416, 0x00},
	{MISENSOW_8BIT,  0xA417, 0x00},
	{MISENSOW_8BIT,  0xA418, 0x00},
	{MISENSOW_8BIT,  0xA419, 0x00},
	{MISENSOW_8BIT,  0xA41A, 0x00},
	{MISENSOW_8BIT,  0xA41B, 0x00},
	{MISENSOW_8BIT,  0xA41C, 0x00},
	{MISENSOW_8BIT,  0xA41D, 0x00},
	{MISENSOW_8BIT,  0xA41E, 0x00},
	{MISENSOW_8BIT,  0xA41F, 0x00},
	{MISENSOW_TOK_TEWM, 0, 0}
};

static stwuct misensow_weg const mt9m114_exp_centew[] = {
	{MISENSOW_8BIT,  0xA407, 0x19},
	{MISENSOW_8BIT,  0xA408, 0x19},
	{MISENSOW_8BIT,  0xA409, 0x19},
	{MISENSOW_8BIT,  0xA40A, 0x19},
	{MISENSOW_8BIT,  0xA40B, 0x19},
	{MISENSOW_8BIT,  0xA40C, 0x19},
	{MISENSOW_8BIT,  0xA40D, 0x4B},
	{MISENSOW_8BIT,  0xA40E, 0x4B},
	{MISENSOW_8BIT,  0xA40F, 0x4B},
	{MISENSOW_8BIT,  0xA410, 0x19},
	{MISENSOW_8BIT,  0xA411, 0x19},
	{MISENSOW_8BIT,  0xA412, 0x4B},
	{MISENSOW_8BIT,  0xA413, 0x64},
	{MISENSOW_8BIT,  0xA414, 0x4B},
	{MISENSOW_8BIT,  0xA415, 0x19},
	{MISENSOW_8BIT,  0xA416, 0x19},
	{MISENSOW_8BIT,  0xA417, 0x4B},
	{MISENSOW_8BIT,  0xA418, 0x4B},
	{MISENSOW_8BIT,  0xA419, 0x4B},
	{MISENSOW_8BIT,  0xA41A, 0x19},
	{MISENSOW_8BIT,  0xA41B, 0x19},
	{MISENSOW_8BIT,  0xA41C, 0x19},
	{MISENSOW_8BIT,  0xA41D, 0x19},
	{MISENSOW_8BIT,  0xA41E, 0x19},
	{MISENSOW_8BIT,  0xA41F, 0x19},
	{MISENSOW_TOK_TEWM, 0, 0}
};

#if 0 /* Cuwwentwy unused */
static stwuct misensow_weg const mt9m114_suspend[] = {
	{MISENSOW_16BIT,  0x098E, 0xDC00},
	{MISENSOW_8BIT,  0xDC00, 0x40},
	{MISENSOW_16BIT,  0x0080, 0x8002},
	{MISENSOW_TOK_TEWM, 0, 0}
};

static stwuct misensow_weg const mt9m114_stweaming[] = {
	{MISENSOW_16BIT,  0x098E, 0xDC00},
	{MISENSOW_8BIT,  0xDC00, 0x34},
	{MISENSOW_16BIT,  0x0080, 0x8002},
	{MISENSOW_TOK_TEWM, 0, 0}
};
#endif

static stwuct misensow_weg const mt9m114_standby_weg[] = {
	{MISENSOW_16BIT,  0x098E, 0xDC00},
	{MISENSOW_8BIT,  0xDC00, 0x50},
	{MISENSOW_16BIT,  0x0080, 0x8002},
	{MISENSOW_TOK_TEWM, 0, 0}
};

#if 0 /* Cuwwentwy unused */
static stwuct misensow_weg const mt9m114_wakeup_weg[] = {
	{MISENSOW_16BIT,  0x098E, 0xDC00},
	{MISENSOW_8BIT,  0xDC00, 0x54},
	{MISENSOW_16BIT,  0x0080, 0x8002},
	{MISENSOW_TOK_TEWM, 0, 0}
};
#endif

static stwuct misensow_weg const mt9m114_chgstat_weg[] = {
	{MISENSOW_16BIT,  0x098E, 0xDC00},
	{MISENSOW_8BIT,  0xDC00, 0x28},
	{MISENSOW_16BIT,  0x0080, 0x8002},
	{MISENSOW_TOK_TEWM, 0, 0}
};

/* [1296x976_30fps] - Intew */
#if 0
static stwuct misensow_weg const mt9m114_960P_init[] = {
	{MISENSOW_16BIT, 0x098E, 0x1000},
	{MISENSOW_8BIT, 0xC97E, 0x01},	  /* cam_sysctw_pww_enabwe = 1 */
	{MISENSOW_16BIT, 0xC980, 0x0128}, /* cam_sysctw_pww_dividew_m_n = 276 */
	{MISENSOW_16BIT, 0xC982, 0x0700}, /* cam_sysctw_pww_dividew_p = 1792 */
	{MISENSOW_16BIT, 0xC800, 0x0000}, /* cam_sensow_cfg_y_addw_stawt = 0 */
	{MISENSOW_16BIT, 0xC802, 0x0000}, /* cam_sensow_cfg_x_addw_stawt = 0 */
	{MISENSOW_16BIT, 0xC804, 0x03CF}, /* cam_sensow_cfg_y_addw_end = 971 */
	{MISENSOW_16BIT, 0xC806, 0x050F}, /* cam_sensow_cfg_x_addw_end = 1291 */
	{MISENSOW_16BIT, 0xC808, 0x02DC}, /* cam_sensow_cfg_pixcwk = 48000000 */
	{MISENSOW_16BIT, 0xC80A, 0x6C00},
	{MISENSOW_16BIT, 0xC80C, 0x0001}, /* cam_sensow_cfg_wow_speed = 1 */
	/* cam_sensow_cfg_fine_integ_time_min = 219 */
	{MISENSOW_16BIT, 0xC80E, 0x00DB},
	/* cam_sensow_cfg_fine_integ_time_max = 1459 */
	{MISENSOW_16BIT, 0xC810, 0x05B3},
	/* cam_sensow_cfg_fwame_wength_wines = 1006 */
	{MISENSOW_16BIT, 0xC812, 0x03F6},
	/* cam_sensow_cfg_wine_wength_pck = 1590 */
	{MISENSOW_16BIT, 0xC814, 0x063E},
	/* cam_sensow_cfg_fine_cowwection = 96 */
	{MISENSOW_16BIT, 0xC816, 0x0060},
	/* cam_sensow_cfg_cpipe_wast_wow = 963 */
	{MISENSOW_16BIT, 0xC818, 0x03C3},
	{MISENSOW_16BIT, 0xC826, 0x0020}, /* cam_sensow_cfg_weg_0_data = 32 */
	{MISENSOW_16BIT, 0xC834, 0x0000}, /* cam_sensow_contwow_wead_mode = 0 */
	{MISENSOW_16BIT, 0xC854, 0x0000}, /* cam_cwop_window_xoffset = 0 */
	{MISENSOW_16BIT, 0xC856, 0x0000}, /* cam_cwop_window_yoffset = 0 */
	{MISENSOW_16BIT, 0xC858, 0x0508}, /* cam_cwop_window_width = 1280 */
	{MISENSOW_16BIT, 0xC85A, 0x03C8}, /* cam_cwop_window_height = 960 */
	{MISENSOW_8BIT,  0xC85C, 0x03},   /* cam_cwop_cwopmode = 3 */
	{MISENSOW_16BIT, 0xC868, 0x0508}, /* cam_output_width = 1280 */
	{MISENSOW_16BIT, 0xC86A, 0x03C8}, /* cam_output_height = 960 */
	{MISENSOW_TOK_TEWM, 0, 0},
};
#endif

/* [1296x976_30fps_768Mbps] */
static stwuct misensow_weg const mt9m114_976P_init[] = {
	{MISENSOW_16BIT, 0x98E, 0x1000},
	{MISENSOW_8BIT, 0xC97E, 0x01},	  /* cam_sysctw_pww_enabwe = 1 */
	{MISENSOW_16BIT, 0xC980, 0x0128}, /* cam_sysctw_pww_dividew_m_n = 276 */
	{MISENSOW_16BIT, 0xC982, 0x0700}, /* cam_sysctw_pww_dividew_p = 1792 */
	{MISENSOW_16BIT, 0xC800, 0x0000}, /* cam_sensow_cfg_y_addw_stawt = 0 */
	{MISENSOW_16BIT, 0xC802, 0x0000}, /* cam_sensow_cfg_x_addw_stawt = 0 */
	{MISENSOW_16BIT, 0xC804, 0x03CF}, /* cam_sensow_cfg_y_addw_end = 975 */
	{MISENSOW_16BIT, 0xC806, 0x050F}, /* cam_sensow_cfg_x_addw_end = 1295 */
	{MISENSOW_32BIT, 0xC808, 0x2DC6C00},/* cam_sensow_cfg_pixcwk = 480000*/
	{MISENSOW_16BIT, 0xC80C, 0x0001}, /* cam_sensow_cfg_wow_speed = 1 */
	/* cam_sensow_cfg_fine_integ_time_min = 219 */
	{MISENSOW_16BIT, 0xC80E, 0x00DB},
	/* 0x062E //cam_sensow_cfg_fine_integ_time_max = 1459 */
	{MISENSOW_16BIT, 0xC810, 0x05B3},
	/* 0x074C //cam_sensow_cfg_fwame_wength_wines = 1006 */
	{MISENSOW_16BIT, 0xC812, 0x03E5},
	/* 0x06B1 /cam_sensow_cfg_wine_wength_pck = 1590 */
	{MISENSOW_16BIT, 0xC814, 0x0644},
	/* cam_sensow_cfg_fine_cowwection = 96 */
	{MISENSOW_16BIT, 0xC816, 0x0060},
	/* cam_sensow_cfg_cpipe_wast_wow = 963 */
	{MISENSOW_16BIT, 0xC818, 0x03C3},
	{MISENSOW_16BIT, 0xC826, 0x0020}, /* cam_sensow_cfg_weg_0_data = 32 */
	{MISENSOW_16BIT, 0xC834, 0x0000}, /* cam_sensow_contwow_wead_mode = 0 */
	{MISENSOW_16BIT, 0xC854, 0x0000}, /* cam_cwop_window_xoffset = 0 */
	{MISENSOW_16BIT, 0xC856, 0x0000}, /* cam_cwop_window_yoffset = 0 */
	{MISENSOW_16BIT, 0xC858, 0x0508}, /* cam_cwop_window_width = 1288 */
	{MISENSOW_16BIT, 0xC85A, 0x03C8}, /* cam_cwop_window_height = 968 */
	{MISENSOW_8BIT, 0xC85C, 0x03}, /* cam_cwop_cwopmode = 3 */
	{MISENSOW_16BIT, 0xC868, 0x0508}, /* cam_output_width = 1288 */
	{MISENSOW_16BIT, 0xC86A, 0x03C8}, /* cam_output_height = 968 */
	{MISENSOW_8BIT, 0xC878, 0x00}, /* 0x0E //cam_aet_aemode = 0 */
	{MISENSOW_TOK_TEWM, 0, 0}
};

/* [1296x864_30fps] */
static stwuct misensow_weg const mt9m114_864P_init[] = {
	{MISENSOW_16BIT, 0x98E, 0x1000},
	{MISENSOW_8BIT, 0xC97E, 0x01},	  /* cam_sysctw_pww_enabwe = 1 */
	{MISENSOW_16BIT, 0xC980, 0x0128}, /* cam_sysctw_pww_dividew_m_n = 276 */
	{MISENSOW_16BIT, 0xC982, 0x0700}, /* cam_sysctw_pww_dividew_p = 1792 */
	{MISENSOW_16BIT, 0xC800, 0x0038}, /* cam_sensow_cfg_y_addw_stawt = 56 */
	{MISENSOW_16BIT, 0xC802, 0x0000}, /* cam_sensow_cfg_x_addw_stawt = 0 */
	{MISENSOW_16BIT, 0xC804, 0x0397}, /* cam_sensow_cfg_y_addw_end = 919 */
	{MISENSOW_16BIT, 0xC806, 0x050F}, /* cam_sensow_cfg_x_addw_end = 1295 */
	/* cam_sensow_cfg_pixcwk = 48000000 */
	{MISENSOW_32BIT, 0xC808, 0x2DC6C00},
	{MISENSOW_16BIT, 0xC80C, 0x0001}, /* cam_sensow_cfg_wow_speed = 1 */
	/* cam_sensow_cfg_fine_integ_time_min = 219 */
	{MISENSOW_16BIT, 0xC80E, 0x00DB},
	/* cam_sensow_cfg_fine_integ_time_max = 1469 */
	{MISENSOW_16BIT, 0xC810, 0x05BD},
	/* cam_sensow_cfg_fwame_wength_wines = 1000 */
	{MISENSOW_16BIT, 0xC812, 0x03E8},
	/* cam_sensow_cfg_wine_wength_pck = 1600 */
	{MISENSOW_16BIT, 0xC814, 0x0640},
	/* cam_sensow_cfg_fine_cowwection = 96 */
	{MISENSOW_16BIT, 0xC816, 0x0060},
	/* cam_sensow_cfg_cpipe_wast_wow = 859 */
	{MISENSOW_16BIT, 0xC818, 0x035B},
	{MISENSOW_16BIT, 0xC826, 0x0020}, /* cam_sensow_cfg_weg_0_data = 32 */
	{MISENSOW_16BIT, 0xC834, 0x0000}, /* cam_sensow_contwow_wead_mode = 0 */
	{MISENSOW_16BIT, 0xC854, 0x0000}, /* cam_cwop_window_xoffset = 0 */
	{MISENSOW_16BIT, 0xC856, 0x0000}, /* cam_cwop_window_yoffset = 0 */
	{MISENSOW_16BIT, 0xC858, 0x0508}, /* cam_cwop_window_width = 1288 */
	{MISENSOW_16BIT, 0xC85A, 0x0358}, /* cam_cwop_window_height = 856 */
	{MISENSOW_8BIT, 0xC85C, 0x03}, /* cam_cwop_cwopmode = 3 */
	{MISENSOW_16BIT, 0xC868, 0x0508}, /* cam_output_width = 1288 */
	{MISENSOW_16BIT, 0xC86A, 0x0358}, /* cam_output_height = 856 */
	{MISENSOW_8BIT, 0xC878, 0x00}, /* 0x0E //cam_aet_aemode = 0 */
	{MISENSOW_TOK_TEWM, 0, 0}
};

/* [1296x736_30fps] */
static stwuct misensow_weg const mt9m114_736P_init[] = {
	{MISENSOW_16BIT, 0x98E, 0x1000},
	{MISENSOW_8BIT, 0xC97E, 0x01},	  /* cam_sysctw_pww_enabwe = 1 */
	{MISENSOW_16BIT, 0xC980, 0x011F}, /* cam_sysctw_pww_dividew_m_n = 287 */
	{MISENSOW_16BIT, 0xC982, 0x0700}, /* cam_sysctw_pww_dividew_p = 1792 */
	{MISENSOW_16BIT, 0xC800, 0x0078}, /* cam_sensow_cfg_y_addw_stawt = 120*/
	{MISENSOW_16BIT, 0xC802, 0x0000}, /* cam_sensow_cfg_x_addw_stawt = 0 */
	{MISENSOW_16BIT, 0xC804, 0x0357}, /* cam_sensow_cfg_y_addw_end = 855 */
	{MISENSOW_16BIT, 0xC806, 0x050F}, /* cam_sensow_cfg_x_addw_end = 1295 */
	{MISENSOW_32BIT, 0xC808, 0x237A07F}, /* cam_sensow_cfg_pixcwk=37199999*/
	{MISENSOW_16BIT, 0xC80C, 0x0001}, /* cam_sensow_cfg_wow_speed = 1 */
	/* cam_sensow_cfg_fine_integ_time_min = 219 */
	{MISENSOW_16BIT, 0xC80E, 0x00DB},
	/* 0x062E //cam_sensow_cfg_fine_integ_time_max = 1469 */
	{MISENSOW_16BIT, 0xC810, 0x05BD},
	/* 0x074C //cam_sensow_cfg_fwame_wength_wines = 775 */
	{MISENSOW_16BIT, 0xC812, 0x0307},
	/* 0x06B1 /cam_sensow_cfg_wine_wength_pck = 1600 */
	{MISENSOW_16BIT, 0xC814, 0x0640},
	/* cam_sensow_cfg_fine_cowwection = 96 */
	{MISENSOW_16BIT, 0xC816, 0x0060},
	/* cam_sensow_cfg_cpipe_wast_wow = 731 */
	{MISENSOW_16BIT, 0xC818, 0x02DB},
	{MISENSOW_16BIT, 0xC826, 0x0020}, /* cam_sensow_cfg_weg_0_data = 32 */
	{MISENSOW_16BIT, 0xC834, 0x0000}, /* cam_sensow_contwow_wead_mode = 0 */
	{MISENSOW_16BIT, 0xC854, 0x0000}, /* cam_cwop_window_xoffset = 0 */
	{MISENSOW_16BIT, 0xC856, 0x0000}, /* cam_cwop_window_yoffset = 0 */
	{MISENSOW_16BIT, 0xC858, 0x0508}, /* cam_cwop_window_width = 1288 */
	{MISENSOW_16BIT, 0xC85A, 0x02D8}, /* cam_cwop_window_height = 728 */
	{MISENSOW_8BIT, 0xC85C, 0x03}, /* cam_cwop_cwopmode = 3 */
	{MISENSOW_16BIT, 0xC868, 0x0508}, /* cam_output_width = 1288 */
	{MISENSOW_16BIT, 0xC86A, 0x02D8}, /* cam_output_height = 728 */
	{MISENSOW_8BIT, 0xC878, 0x00}, /* 0x0E //cam_aet_aemode = 0 */
	{MISENSOW_TOK_TEWM, 0, 0}
};

/* [736x496_30fps_768Mbps] */
#if 0 /* Cuwwentwy unused */
static stwuct misensow_weg const mt9m114_720_480P_init[] = {
	{MISENSOW_16BIT, 0x98E, 0x1000},
	{MISENSOW_8BIT, 0xC97E, 0x01},	  /* cam_sysctw_pww_enabwe = 1 */
	{MISENSOW_16BIT, 0xC980, 0x0128}, /* cam_sysctw_pww_dividew_m_n = 276 */
	{MISENSOW_16BIT, 0xC982, 0x0700}, /* cam_sysctw_pww_dividew_p = 1792 */
	{MISENSOW_16BIT, 0xC800, 0x00F0}, /* cam_sensow_cfg_y_addw_stawt = 240*/
	{MISENSOW_16BIT, 0xC802, 0x0118}, /* cam_sensow_cfg_x_addw_stawt = 280*/
	{MISENSOW_16BIT, 0xC804, 0x02DF}, /* cam_sensow_cfg_y_addw_end = 735 */
	{MISENSOW_16BIT, 0xC806, 0x03F7}, /* cam_sensow_cfg_x_addw_end = 1015 */
	/* cam_sensow_cfg_pixcwk = 48000000 */
	{MISENSOW_32BIT, 0xC808, 0x2DC6C00},
	{MISENSOW_16BIT, 0xC80C, 0x0001}, /* cam_sensow_cfg_wow_speed = 1 */
	/* cam_sensow_cfg_fine_integ_time_min = 219 */
	{MISENSOW_16BIT, 0xC80E, 0x00DB},
	/* 0x062E //cam_sensow_cfg_fine_integ_time_max = 1459 */
	{MISENSOW_16BIT, 0xC810, 0x05B3},
	/* 0x074C //cam_sensow_cfg_fwame_wength_wines = 997 */
	{MISENSOW_16BIT, 0xC812, 0x03E5},
	/* 0x06B1 /cam_sensow_cfg_wine_wength_pck = 1604 */
	{MISENSOW_16BIT, 0xC814, 0x0644},
	/* cam_sensow_cfg_fine_cowwection = 96 */
	{MISENSOW_16BIT, 0xC816, 0x0060},
	{MISENSOW_16BIT, 0xC818, 0x03C3}, /* cam_sensow_cfg_cpipe_wast_wow=963*/
	{MISENSOW_16BIT, 0xC826, 0x0020}, /* cam_sensow_cfg_weg_0_data = 32 */
	{MISENSOW_16BIT, 0xC834, 0x0000}, /* cam_sensow_contwow_wead_mode = 0*/
	{MISENSOW_16BIT, 0xC854, 0x0000}, /* cam_cwop_window_xoffset = 0 */
	{MISENSOW_16BIT, 0xC856, 0x0000}, /* cam_cwop_window_yoffset = 0 */
	{MISENSOW_16BIT, 0xC858, 0x02D8}, /* cam_cwop_window_width = 728 */
	{MISENSOW_16BIT, 0xC85A, 0x01E8}, /* cam_cwop_window_height = 488 */
	{MISENSOW_8BIT, 0xC85C, 0x03}, /* cam_cwop_cwopmode = 3 */
	{MISENSOW_16BIT, 0xC868, 0x02D8}, /* cam_output_width = 728 */
	{MISENSOW_16BIT, 0xC86A, 0x01E8}, /* cam_output_height = 488 */
	{MISENSOW_8BIT, 0xC878, 0x00}, /* 0x0E //cam_aet_aemode = 0 */
	{MISENSOW_TOK_TEWM, 0, 0}
};
#endif

static stwuct misensow_weg const mt9m114_common[] = {
	/* weset */
	{MISENSOW_16BIT,  0x301A, 0x0234},
	/* WOAD = Step2-PWW_Timing      //PWW and Timing */
	{MISENSOW_16BIT, 0x098E, 0x1000}, /* WOGICAW_ADDWESS_ACCESS */
	{MISENSOW_8BIT, 0xC97E, 0x01},    /* cam_sysctw_pww_enabwe = 1 */
	{MISENSOW_16BIT, 0xC980, 0x0128}, /* cam_sysctw_pww_dividew_m_n = 276 */
	{MISENSOW_16BIT, 0xC982, 0x0700}, /* cam_sysctw_pww_dividew_p = 1792 */
	{MISENSOW_16BIT, 0xC800, 0x0000}, /* cam_sensow_cfg_y_addw_stawt = 216*/
	{MISENSOW_16BIT, 0xC802, 0x0000}, /* cam_sensow_cfg_x_addw_stawt = 168*/
	{MISENSOW_16BIT, 0xC804, 0x03CD}, /* cam_sensow_cfg_y_addw_end = 761 */
	{MISENSOW_16BIT, 0xC806, 0x050D}, /* cam_sensow_cfg_x_addw_end = 1127 */
	{MISENSOW_16BIT, 0xC808, 0x02DC}, /* cam_sensow_cfg_pixcwk = 24000000 */
	{MISENSOW_16BIT, 0xC80A, 0x6C00},
	{MISENSOW_16BIT, 0xC80C, 0x0001}, /* cam_sensow_cfg_wow_speed = 1 */
	/* cam_sensow_cfg_fine_integ_time_min = 219 */
	{MISENSOW_16BIT, 0xC80E, 0x01C3},
	/* cam_sensow_cfg_fine_integ_time_max = 1149 */
	{MISENSOW_16BIT, 0xC810, 0x03F7},
	/* cam_sensow_cfg_fwame_wength_wines = 625 */
	{MISENSOW_16BIT, 0xC812, 0x0500},
	/* cam_sensow_cfg_wine_wength_pck = 1280 */
	{MISENSOW_16BIT, 0xC814, 0x04E2},
	/* cam_sensow_cfg_fine_cowwection = 96 */
	{MISENSOW_16BIT, 0xC816, 0x00E0},
	/* cam_sensow_cfg_cpipe_wast_wow = 541 */
	{MISENSOW_16BIT, 0xC818, 0x01E3},
	{MISENSOW_16BIT, 0xC826, 0x0020}, /* cam_sensow_cfg_weg_0_data = 32 */
	{MISENSOW_16BIT, 0xC834, 0x0330}, /* cam_sensow_contwow_wead_mode = 0 */
	{MISENSOW_16BIT, 0xC854, 0x0000}, /* cam_cwop_window_xoffset = 0 */
	{MISENSOW_16BIT, 0xC856, 0x0000}, /* cam_cwop_window_yoffset = 0 */
	{MISENSOW_16BIT, 0xC858, 0x0280}, /* cam_cwop_window_width = 952 */
	{MISENSOW_16BIT, 0xC85A, 0x01E0}, /* cam_cwop_window_height = 538 */
	{MISENSOW_8BIT, 0xC85C, 0x03},    /* cam_cwop_cwopmode = 3 */
	{MISENSOW_16BIT, 0xC868, 0x0280}, /* cam_output_width = 952 */
	{MISENSOW_16BIT, 0xC86A, 0x01E0}, /* cam_output_height = 538 */
	/*
	 * WOAD = Step3-Wecommended
	 * Patch, Ewwata and Sensow optimization Setting
	 */
	{MISENSOW_16BIT, 0x316A, 0x8270}, /* DAC_TXWO_WOW */
	{MISENSOW_16BIT, 0x316C, 0x8270}, /* DAC_TXWO */
	{MISENSOW_16BIT, 0x3ED0, 0x2305}, /* DAC_WD_4_5 */
	{MISENSOW_16BIT, 0x3ED2, 0x77CF}, /* DAC_WD_6_7 */
	{MISENSOW_16BIT, 0x316E, 0x8202}, /* DAC_ECW */
	{MISENSOW_16BIT, 0x3180, 0x87FF}, /* DEWTA_DK_CONTWOW */
	{MISENSOW_16BIT, 0x30D4, 0x6080}, /* COWUMN_COWWECTION */
	{MISENSOW_16BIT, 0xA802, 0x0008}, /* AE_TWACK_MODE */
	{MISENSOW_16BIT, 0x3E14, 0xFF39}, /* SAMP_COW_PUP2 */
	{MISENSOW_16BIT, 0x31E0, 0x0003}, /* PIX_DEF_ID */
	/* WOAD = Step8-Featuwes	//Powts, speciaw featuwes, etc. */
	{MISENSOW_16BIT, 0x098E, 0x0000}, /* WOGICAW_ADDWESS_ACCESS */
	{MISENSOW_16BIT, 0x001E, 0x0777}, /* PAD_SWEW */
	{MISENSOW_16BIT, 0x098E, 0x0000}, /* WOGICAW_ADDWESS_ACCESS */
	{MISENSOW_16BIT, 0xC984, 0x8001}, /* CAM_POWT_OUTPUT_CONTWOW */
	{MISENSOW_16BIT, 0xC988, 0x0F00}, /* CAM_POWT_MIPI_TIMING_T_HS_ZEWO */
	/* CAM_POWT_MIPI_TIMING_T_HS_EXIT_HS_TWAIW */
	{MISENSOW_16BIT, 0xC98A, 0x0B07},
	/* CAM_POWT_MIPI_TIMING_T_CWK_POST_CWK_PWE */
	{MISENSOW_16BIT, 0xC98C, 0x0D01},
	/* CAM_POWT_MIPI_TIMING_T_CWK_TWAIW_CWK_ZEWO */
	{MISENSOW_16BIT, 0xC98E, 0x071D},
	{MISENSOW_16BIT, 0xC990, 0x0006}, /* CAM_POWT_MIPI_TIMING_T_WPX */
	{MISENSOW_16BIT, 0xC992, 0x0A0C}, /* CAM_POWT_MIPI_TIMING_INIT_TIMING */
	{MISENSOW_16BIT, 0x3C5A, 0x0009}, /* MIPI_DEWAY_TWIM */
	{MISENSOW_16BIT, 0xC86C, 0x0210}, /* CAM_OUTPUT_FOWMAT */
	{MISENSOW_16BIT, 0xA804, 0x0000}, /* AE_TWACK_AWGO */
	/* defauwt exposuwe */
	{MISENSOW_16BIT, 0x3012, 0x0110}, /* COMMAND_WEGISTEW */
	{MISENSOW_TOK_TEWM, 0, 0},

};

#if 0 /* Cuwwentwy unused */
static stwuct misensow_weg const mt9m114_antifwickew_50hz[] = {
	{MISENSOW_16BIT,  0x098E, 0xC88B},
	{MISENSOW_8BIT,  0xC88B, 0x32},
	{MISENSOW_8BIT,  0xDC00, 0x28},
	{MISENSOW_16BIT,  0x0080, 0x8002},
	{MISENSOW_TOK_TEWM, 0, 0}
};

static stwuct misensow_weg const mt9m114_antifwickew_60hz[] = {
	{MISENSOW_16BIT,  0x098E, 0xC88B},
	{MISENSOW_8BIT,  0xC88B, 0x3C},
	{MISENSOW_8BIT,  0xDC00, 0x28},
	{MISENSOW_16BIT,  0x0080, 0x8002},
	{MISENSOW_TOK_TEWM, 0, 0}
};

static stwuct misensow_weg const mt9m114_iq[] = {
	/* [Step3-Wecommended] [Sensow optimization] */
	{MISENSOW_16BIT,	0x316A, 0x8270},
	{MISENSOW_16BIT,	0x316C, 0x8270},
	{MISENSOW_16BIT,	0x3ED0, 0x2305},
	{MISENSOW_16BIT,	0x3ED2, 0x77CF},
	{MISENSOW_16BIT,	0x316E, 0x8202},
	{MISENSOW_16BIT,	0x3180, 0x87FF},
	{MISENSOW_16BIT,	0x30D4, 0x6080},
	{MISENSOW_16BIT,	0xA802, 0x0008},

	/* This wegistew is fwom vendew to avoid wow wight cowow noise */
	{MISENSOW_16BIT,	0x31E0, 0x0001},

	/* WOAD=Ewwata item 1 */
	{MISENSOW_16BIT,	0x3E14, 0xFF39},

	/* WOAD=Ewwata item 2 */
	{MISENSOW_16BIT,	0x301A, 0x8234},

	/*
	 * WOAD=Ewwata item 3
	 * WOAD=Patch 0202;
	 * Featuwe Wecommended; Bwack wevew cowwection fix
	 */
	{MISENSOW_16BIT,	0x0982, 0x0001},
	{MISENSOW_16BIT,	0x098A, 0x5000},
	{MISENSOW_16BIT,	0xD000, 0x70CF},
	{MISENSOW_16BIT,	0xD002, 0xFFFF},
	{MISENSOW_16BIT,	0xD004, 0xC5D4},
	{MISENSOW_16BIT,	0xD006, 0x903A},
	{MISENSOW_16BIT,	0xD008, 0x2144},
	{MISENSOW_16BIT,	0xD00A, 0x0C00},
	{MISENSOW_16BIT,	0xD00C, 0x2186},
	{MISENSOW_16BIT,	0xD00E, 0x0FF3},
	{MISENSOW_16BIT,	0xD010, 0xB844},
	{MISENSOW_16BIT,	0xD012, 0xB948},
	{MISENSOW_16BIT,	0xD014, 0xE082},
	{MISENSOW_16BIT,	0xD016, 0x20CC},
	{MISENSOW_16BIT,	0xD018, 0x80E2},
	{MISENSOW_16BIT,	0xD01A, 0x21CC},
	{MISENSOW_16BIT,	0xD01C, 0x80A2},
	{MISENSOW_16BIT,	0xD01E, 0x21CC},
	{MISENSOW_16BIT,	0xD020, 0x80E2},
	{MISENSOW_16BIT,	0xD022, 0xF404},
	{MISENSOW_16BIT,	0xD024, 0xD801},
	{MISENSOW_16BIT,	0xD026, 0xF003},
	{MISENSOW_16BIT,	0xD028, 0xD800},
	{MISENSOW_16BIT,	0xD02A, 0x7EE0},
	{MISENSOW_16BIT,	0xD02C, 0xC0F1},
	{MISENSOW_16BIT,	0xD02E, 0x08BA},

	{MISENSOW_16BIT,	0xD030, 0x0600},
	{MISENSOW_16BIT,	0xD032, 0xC1A1},
	{MISENSOW_16BIT,	0xD034, 0x76CF},
	{MISENSOW_16BIT,	0xD036, 0xFFFF},
	{MISENSOW_16BIT,	0xD038, 0xC130},
	{MISENSOW_16BIT,	0xD03A, 0x6E04},
	{MISENSOW_16BIT,	0xD03C, 0xC040},
	{MISENSOW_16BIT,	0xD03E, 0x71CF},
	{MISENSOW_16BIT,	0xD040, 0xFFFF},
	{MISENSOW_16BIT,	0xD042, 0xC790},
	{MISENSOW_16BIT,	0xD044, 0x8103},
	{MISENSOW_16BIT,	0xD046, 0x77CF},
	{MISENSOW_16BIT,	0xD048, 0xFFFF},
	{MISENSOW_16BIT,	0xD04A, 0xC7C0},
	{MISENSOW_16BIT,	0xD04C, 0xE001},
	{MISENSOW_16BIT,	0xD04E, 0xA103},
	{MISENSOW_16BIT,	0xD050, 0xD800},
	{MISENSOW_16BIT,	0xD052, 0x0C6A},
	{MISENSOW_16BIT,	0xD054, 0x04E0},
	{MISENSOW_16BIT,	0xD056, 0xB89E},
	{MISENSOW_16BIT,	0xD058, 0x7508},
	{MISENSOW_16BIT,	0xD05A, 0x8E1C},
	{MISENSOW_16BIT,	0xD05C, 0x0809},
	{MISENSOW_16BIT,	0xD05E, 0x0191},

	{MISENSOW_16BIT,	0xD060, 0xD801},
	{MISENSOW_16BIT,	0xD062, 0xAE1D},
	{MISENSOW_16BIT,	0xD064, 0xE580},
	{MISENSOW_16BIT,	0xD066, 0x20CA},
	{MISENSOW_16BIT,	0xD068, 0x0022},
	{MISENSOW_16BIT,	0xD06A, 0x20CF},
	{MISENSOW_16BIT,	0xD06C, 0x0522},
	{MISENSOW_16BIT,	0xD06E, 0x0C5C},
	{MISENSOW_16BIT,	0xD070, 0x04E2},
	{MISENSOW_16BIT,	0xD072, 0x21CA},
	{MISENSOW_16BIT,	0xD074, 0x0062},
	{MISENSOW_16BIT,	0xD076, 0xE580},
	{MISENSOW_16BIT,	0xD078, 0xD901},
	{MISENSOW_16BIT,	0xD07A, 0x79C0},
	{MISENSOW_16BIT,	0xD07C, 0xD800},
	{MISENSOW_16BIT,	0xD07E, 0x0BE6},
	{MISENSOW_16BIT,	0xD080, 0x04E0},
	{MISENSOW_16BIT,	0xD082, 0xB89E},
	{MISENSOW_16BIT,	0xD084, 0x70CF},
	{MISENSOW_16BIT,	0xD086, 0xFFFF},
	{MISENSOW_16BIT,	0xD088, 0xC8D4},
	{MISENSOW_16BIT,	0xD08A, 0x9002},
	{MISENSOW_16BIT,	0xD08C, 0x0857},
	{MISENSOW_16BIT,	0xD08E, 0x025E},

	{MISENSOW_16BIT,	0xD090, 0xFFDC},
	{MISENSOW_16BIT,	0xD092, 0xE080},
	{MISENSOW_16BIT,	0xD094, 0x25CC},
	{MISENSOW_16BIT,	0xD096, 0x9022},
	{MISENSOW_16BIT,	0xD098, 0xF225},
	{MISENSOW_16BIT,	0xD09A, 0x1700},
	{MISENSOW_16BIT,	0xD09C, 0x108A},
	{MISENSOW_16BIT,	0xD09E, 0x73CF},
	{MISENSOW_16BIT,	0xD0A0, 0xFF00},
	{MISENSOW_16BIT,	0xD0A2, 0x3174},
	{MISENSOW_16BIT,	0xD0A4, 0x9307},
	{MISENSOW_16BIT,	0xD0A6, 0x2A04},
	{MISENSOW_16BIT,	0xD0A8, 0x103E},
	{MISENSOW_16BIT,	0xD0AA, 0x9328},
	{MISENSOW_16BIT,	0xD0AC, 0x2942},
	{MISENSOW_16BIT,	0xD0AE, 0x7140},
	{MISENSOW_16BIT,	0xD0B0, 0x2A04},
	{MISENSOW_16BIT,	0xD0B2, 0x107E},
	{MISENSOW_16BIT,	0xD0B4, 0x9349},
	{MISENSOW_16BIT,	0xD0B6, 0x2942},
	{MISENSOW_16BIT,	0xD0B8, 0x7141},
	{MISENSOW_16BIT,	0xD0BA, 0x2A04},
	{MISENSOW_16BIT,	0xD0BC, 0x10BE},
	{MISENSOW_16BIT,	0xD0BE, 0x934A},

	{MISENSOW_16BIT,	0xD0C0, 0x2942},
	{MISENSOW_16BIT,	0xD0C2, 0x714B},
	{MISENSOW_16BIT,	0xD0C4, 0x2A04},
	{MISENSOW_16BIT,	0xD0C6, 0x10BE},
	{MISENSOW_16BIT,	0xD0C8, 0x130C},
	{MISENSOW_16BIT,	0xD0CA, 0x010A},
	{MISENSOW_16BIT,	0xD0CC, 0x2942},
	{MISENSOW_16BIT,	0xD0CE, 0x7142},
	{MISENSOW_16BIT,	0xD0D0, 0x2250},
	{MISENSOW_16BIT,	0xD0D2, 0x13CA},
	{MISENSOW_16BIT,	0xD0D4, 0x1B0C},
	{MISENSOW_16BIT,	0xD0D6, 0x0284},
	{MISENSOW_16BIT,	0xD0D8, 0xB307},
	{MISENSOW_16BIT,	0xD0DA, 0xB328},
	{MISENSOW_16BIT,	0xD0DC, 0x1B12},
	{MISENSOW_16BIT,	0xD0DE, 0x02C4},
	{MISENSOW_16BIT,	0xD0E0, 0xB34A},
	{MISENSOW_16BIT,	0xD0E2, 0xED88},
	{MISENSOW_16BIT,	0xD0E4, 0x71CF},
	{MISENSOW_16BIT,	0xD0E6, 0xFF00},
	{MISENSOW_16BIT,	0xD0E8, 0x3174},
	{MISENSOW_16BIT,	0xD0EA, 0x9106},
	{MISENSOW_16BIT,	0xD0EC, 0xB88F},
	{MISENSOW_16BIT,	0xD0EE, 0xB106},

	{MISENSOW_16BIT,	0xD0F0, 0x210A},
	{MISENSOW_16BIT,	0xD0F2, 0x8340},
	{MISENSOW_16BIT,	0xD0F4, 0xC000},
	{MISENSOW_16BIT,	0xD0F6, 0x21CA},
	{MISENSOW_16BIT,	0xD0F8, 0x0062},
	{MISENSOW_16BIT,	0xD0FA, 0x20F0},
	{MISENSOW_16BIT,	0xD0FC, 0x0040},
	{MISENSOW_16BIT,	0xD0FE, 0x0B02},
	{MISENSOW_16BIT,	0xD100, 0x0320},
	{MISENSOW_16BIT,	0xD102, 0xD901},
	{MISENSOW_16BIT,	0xD104, 0x07F1},
	{MISENSOW_16BIT,	0xD106, 0x05E0},
	{MISENSOW_16BIT,	0xD108, 0xC0A1},
	{MISENSOW_16BIT,	0xD10A, 0x78E0},
	{MISENSOW_16BIT,	0xD10C, 0xC0F1},
	{MISENSOW_16BIT,	0xD10E, 0x71CF},
	{MISENSOW_16BIT,	0xD110, 0xFFFF},
	{MISENSOW_16BIT,	0xD112, 0xC7C0},
	{MISENSOW_16BIT,	0xD114, 0xD840},
	{MISENSOW_16BIT,	0xD116, 0xA900},
	{MISENSOW_16BIT,	0xD118, 0x71CF},
	{MISENSOW_16BIT,	0xD11A, 0xFFFF},
	{MISENSOW_16BIT,	0xD11C, 0xD02C},
	{MISENSOW_16BIT,	0xD11E, 0xD81E},

	{MISENSOW_16BIT,	0xD120, 0x0A5A},
	{MISENSOW_16BIT,	0xD122, 0x04E0},
	{MISENSOW_16BIT,	0xD124, 0xDA00},
	{MISENSOW_16BIT,	0xD126, 0xD800},
	{MISENSOW_16BIT,	0xD128, 0xC0D1},
	{MISENSOW_16BIT,	0xD12A, 0x7EE0},

	{MISENSOW_16BIT,	0x098E, 0x0000},
	{MISENSOW_16BIT,	0xE000, 0x010C},
	{MISENSOW_16BIT,	0xE002, 0x0202},
	{MISENSOW_16BIT,	0xE004, 0x4103},
	{MISENSOW_16BIT,	0xE006, 0x0202},
	{MISENSOW_16BIT,	0x0080, 0xFFF0},
	{MISENSOW_16BIT,	0x0080, 0xFFF1},

	/* WOAD=Patch 0302; Featuwe Wecommended; Adaptive Sensitivity */
	{MISENSOW_16BIT,	0x0982, 0x0001},
	{MISENSOW_16BIT,	0x098A, 0x512C},
	{MISENSOW_16BIT,	0xD12C, 0x70CF},
	{MISENSOW_16BIT,	0xD12E, 0xFFFF},
	{MISENSOW_16BIT,	0xD130, 0xC5D4},
	{MISENSOW_16BIT,	0xD132, 0x903A},
	{MISENSOW_16BIT,	0xD134, 0x2144},
	{MISENSOW_16BIT,	0xD136, 0x0C00},
	{MISENSOW_16BIT,	0xD138, 0x2186},
	{MISENSOW_16BIT,	0xD13A, 0x0FF3},
	{MISENSOW_16BIT,	0xD13C, 0xB844},
	{MISENSOW_16BIT,	0xD13E, 0x262F},
	{MISENSOW_16BIT,	0xD140, 0xF008},
	{MISENSOW_16BIT,	0xD142, 0xB948},
	{MISENSOW_16BIT,	0xD144, 0x21CC},
	{MISENSOW_16BIT,	0xD146, 0x8021},
	{MISENSOW_16BIT,	0xD148, 0xD801},
	{MISENSOW_16BIT,	0xD14A, 0xF203},
	{MISENSOW_16BIT,	0xD14C, 0xD800},
	{MISENSOW_16BIT,	0xD14E, 0x7EE0},
	{MISENSOW_16BIT,	0xD150, 0xC0F1},
	{MISENSOW_16BIT,	0xD152, 0x71CF},
	{MISENSOW_16BIT,	0xD154, 0xFFFF},
	{MISENSOW_16BIT,	0xD156, 0xC610},
	{MISENSOW_16BIT,	0xD158, 0x910E},
	{MISENSOW_16BIT,	0xD15A, 0x208C},
	{MISENSOW_16BIT,	0xD15C, 0x8014},
	{MISENSOW_16BIT,	0xD15E, 0xF418},
	{MISENSOW_16BIT,	0xD160, 0x910F},
	{MISENSOW_16BIT,	0xD162, 0x208C},
	{MISENSOW_16BIT,	0xD164, 0x800F},
	{MISENSOW_16BIT,	0xD166, 0xF414},
	{MISENSOW_16BIT,	0xD168, 0x9116},
	{MISENSOW_16BIT,	0xD16A, 0x208C},
	{MISENSOW_16BIT,	0xD16C, 0x800A},
	{MISENSOW_16BIT,	0xD16E, 0xF410},
	{MISENSOW_16BIT,	0xD170, 0x9117},
	{MISENSOW_16BIT,	0xD172, 0x208C},
	{MISENSOW_16BIT,	0xD174, 0x8807},
	{MISENSOW_16BIT,	0xD176, 0xF40C},
	{MISENSOW_16BIT,	0xD178, 0x9118},
	{MISENSOW_16BIT,	0xD17A, 0x2086},
	{MISENSOW_16BIT,	0xD17C, 0x0FF3},
	{MISENSOW_16BIT,	0xD17E, 0xB848},
	{MISENSOW_16BIT,	0xD180, 0x080D},
	{MISENSOW_16BIT,	0xD182, 0x0090},
	{MISENSOW_16BIT,	0xD184, 0xFFEA},
	{MISENSOW_16BIT,	0xD186, 0xE081},
	{MISENSOW_16BIT,	0xD188, 0xD801},
	{MISENSOW_16BIT,	0xD18A, 0xF203},
	{MISENSOW_16BIT,	0xD18C, 0xD800},
	{MISENSOW_16BIT,	0xD18E, 0xC0D1},
	{MISENSOW_16BIT,	0xD190, 0x7EE0},
	{MISENSOW_16BIT,	0xD192, 0x78E0},
	{MISENSOW_16BIT,	0xD194, 0xC0F1},
	{MISENSOW_16BIT,	0xD196, 0x71CF},
	{MISENSOW_16BIT,	0xD198, 0xFFFF},
	{MISENSOW_16BIT,	0xD19A, 0xC610},
	{MISENSOW_16BIT,	0xD19C, 0x910E},
	{MISENSOW_16BIT,	0xD19E, 0x208C},
	{MISENSOW_16BIT,	0xD1A0, 0x800A},
	{MISENSOW_16BIT,	0xD1A2, 0xF418},
	{MISENSOW_16BIT,	0xD1A4, 0x910F},
	{MISENSOW_16BIT,	0xD1A6, 0x208C},
	{MISENSOW_16BIT,	0xD1A8, 0x8807},
	{MISENSOW_16BIT,	0xD1AA, 0xF414},
	{MISENSOW_16BIT,	0xD1AC, 0x9116},
	{MISENSOW_16BIT,	0xD1AE, 0x208C},
	{MISENSOW_16BIT,	0xD1B0, 0x800A},
	{MISENSOW_16BIT,	0xD1B2, 0xF410},
	{MISENSOW_16BIT,	0xD1B4, 0x9117},
	{MISENSOW_16BIT,	0xD1B6, 0x208C},
	{MISENSOW_16BIT,	0xD1B8, 0x8807},
	{MISENSOW_16BIT,	0xD1BA, 0xF40C},
	{MISENSOW_16BIT,	0xD1BC, 0x9118},
	{MISENSOW_16BIT,	0xD1BE, 0x2086},
	{MISENSOW_16BIT,	0xD1C0, 0x0FF3},
	{MISENSOW_16BIT,	0xD1C2, 0xB848},
	{MISENSOW_16BIT,	0xD1C4, 0x080D},
	{MISENSOW_16BIT,	0xD1C6, 0x0090},
	{MISENSOW_16BIT,	0xD1C8, 0xFFD9},
	{MISENSOW_16BIT,	0xD1CA, 0xE080},
	{MISENSOW_16BIT,	0xD1CC, 0xD801},
	{MISENSOW_16BIT,	0xD1CE, 0xF203},
	{MISENSOW_16BIT,	0xD1D0, 0xD800},
	{MISENSOW_16BIT,	0xD1D2, 0xF1DF},
	{MISENSOW_16BIT,	0xD1D4, 0x9040},
	{MISENSOW_16BIT,	0xD1D6, 0x71CF},
	{MISENSOW_16BIT,	0xD1D8, 0xFFFF},
	{MISENSOW_16BIT,	0xD1DA, 0xC5D4},
	{MISENSOW_16BIT,	0xD1DC, 0xB15A},
	{MISENSOW_16BIT,	0xD1DE, 0x9041},
	{MISENSOW_16BIT,	0xD1E0, 0x73CF},
	{MISENSOW_16BIT,	0xD1E2, 0xFFFF},
	{MISENSOW_16BIT,	0xD1E4, 0xC7D0},
	{MISENSOW_16BIT,	0xD1E6, 0xB140},
	{MISENSOW_16BIT,	0xD1E8, 0x9042},
	{MISENSOW_16BIT,	0xD1EA, 0xB141},
	{MISENSOW_16BIT,	0xD1EC, 0x9043},
	{MISENSOW_16BIT,	0xD1EE, 0xB142},
	{MISENSOW_16BIT,	0xD1F0, 0x9044},
	{MISENSOW_16BIT,	0xD1F2, 0xB143},
	{MISENSOW_16BIT,	0xD1F4, 0x9045},
	{MISENSOW_16BIT,	0xD1F6, 0xB147},
	{MISENSOW_16BIT,	0xD1F8, 0x9046},
	{MISENSOW_16BIT,	0xD1FA, 0xB148},
	{MISENSOW_16BIT,	0xD1FC, 0x9047},
	{MISENSOW_16BIT,	0xD1FE, 0xB14B},
	{MISENSOW_16BIT,	0xD200, 0x9048},
	{MISENSOW_16BIT,	0xD202, 0xB14C},
	{MISENSOW_16BIT,	0xD204, 0x9049},
	{MISENSOW_16BIT,	0xD206, 0x1958},
	{MISENSOW_16BIT,	0xD208, 0x0084},
	{MISENSOW_16BIT,	0xD20A, 0x904A},
	{MISENSOW_16BIT,	0xD20C, 0x195A},
	{MISENSOW_16BIT,	0xD20E, 0x0084},
	{MISENSOW_16BIT,	0xD210, 0x8856},
	{MISENSOW_16BIT,	0xD212, 0x1B36},
	{MISENSOW_16BIT,	0xD214, 0x8082},
	{MISENSOW_16BIT,	0xD216, 0x8857},
	{MISENSOW_16BIT,	0xD218, 0x1B37},
	{MISENSOW_16BIT,	0xD21A, 0x8082},
	{MISENSOW_16BIT,	0xD21C, 0x904C},
	{MISENSOW_16BIT,	0xD21E, 0x19A7},
	{MISENSOW_16BIT,	0xD220, 0x009C},
	{MISENSOW_16BIT,	0xD222, 0x881A},
	{MISENSOW_16BIT,	0xD224, 0x7FE0},
	{MISENSOW_16BIT,	0xD226, 0x1B54},
	{MISENSOW_16BIT,	0xD228, 0x8002},
	{MISENSOW_16BIT,	0xD22A, 0x78E0},
	{MISENSOW_16BIT,	0xD22C, 0x71CF},
	{MISENSOW_16BIT,	0xD22E, 0xFFFF},
	{MISENSOW_16BIT,	0xD230, 0xC350},
	{MISENSOW_16BIT,	0xD232, 0xD828},
	{MISENSOW_16BIT,	0xD234, 0xA90B},
	{MISENSOW_16BIT,	0xD236, 0x8100},
	{MISENSOW_16BIT,	0xD238, 0x01C5},
	{MISENSOW_16BIT,	0xD23A, 0x0320},
	{MISENSOW_16BIT,	0xD23C, 0xD900},
	{MISENSOW_16BIT,	0xD23E, 0x78E0},
	{MISENSOW_16BIT,	0xD240, 0x220A},
	{MISENSOW_16BIT,	0xD242, 0x1F80},
	{MISENSOW_16BIT,	0xD244, 0xFFFF},
	{MISENSOW_16BIT,	0xD246, 0xD4E0},
	{MISENSOW_16BIT,	0xD248, 0xC0F1},
	{MISENSOW_16BIT,	0xD24A, 0x0811},
	{MISENSOW_16BIT,	0xD24C, 0x0051},
	{MISENSOW_16BIT,	0xD24E, 0x2240},
	{MISENSOW_16BIT,	0xD250, 0x1200},
	{MISENSOW_16BIT,	0xD252, 0xFFE1},
	{MISENSOW_16BIT,	0xD254, 0xD801},
	{MISENSOW_16BIT,	0xD256, 0xF006},
	{MISENSOW_16BIT,	0xD258, 0x2240},
	{MISENSOW_16BIT,	0xD25A, 0x1900},
	{MISENSOW_16BIT,	0xD25C, 0xFFDE},
	{MISENSOW_16BIT,	0xD25E, 0xD802},
	{MISENSOW_16BIT,	0xD260, 0x1A05},
	{MISENSOW_16BIT,	0xD262, 0x1002},
	{MISENSOW_16BIT,	0xD264, 0xFFF2},
	{MISENSOW_16BIT,	0xD266, 0xF195},
	{MISENSOW_16BIT,	0xD268, 0xC0F1},
	{MISENSOW_16BIT,	0xD26A, 0x0E7E},
	{MISENSOW_16BIT,	0xD26C, 0x05C0},
	{MISENSOW_16BIT,	0xD26E, 0x75CF},
	{MISENSOW_16BIT,	0xD270, 0xFFFF},
	{MISENSOW_16BIT,	0xD272, 0xC84C},
	{MISENSOW_16BIT,	0xD274, 0x9502},
	{MISENSOW_16BIT,	0xD276, 0x77CF},
	{MISENSOW_16BIT,	0xD278, 0xFFFF},
	{MISENSOW_16BIT,	0xD27A, 0xC344},
	{MISENSOW_16BIT,	0xD27C, 0x2044},
	{MISENSOW_16BIT,	0xD27E, 0x008E},
	{MISENSOW_16BIT,	0xD280, 0xB8A1},
	{MISENSOW_16BIT,	0xD282, 0x0926},
	{MISENSOW_16BIT,	0xD284, 0x03E0},
	{MISENSOW_16BIT,	0xD286, 0xB502},
	{MISENSOW_16BIT,	0xD288, 0x9502},
	{MISENSOW_16BIT,	0xD28A, 0x952E},
	{MISENSOW_16BIT,	0xD28C, 0x7E05},
	{MISENSOW_16BIT,	0xD28E, 0xB5C2},
	{MISENSOW_16BIT,	0xD290, 0x70CF},
	{MISENSOW_16BIT,	0xD292, 0xFFFF},
	{MISENSOW_16BIT,	0xD294, 0xC610},
	{MISENSOW_16BIT,	0xD296, 0x099A},
	{MISENSOW_16BIT,	0xD298, 0x04A0},
	{MISENSOW_16BIT,	0xD29A, 0xB026},
	{MISENSOW_16BIT,	0xD29C, 0x0E02},
	{MISENSOW_16BIT,	0xD29E, 0x0560},
	{MISENSOW_16BIT,	0xD2A0, 0xDE00},
	{MISENSOW_16BIT,	0xD2A2, 0x0A12},
	{MISENSOW_16BIT,	0xD2A4, 0x0320},
	{MISENSOW_16BIT,	0xD2A6, 0xB7C4},
	{MISENSOW_16BIT,	0xD2A8, 0x0B36},
	{MISENSOW_16BIT,	0xD2AA, 0x03A0},
	{MISENSOW_16BIT,	0xD2AC, 0x70C9},
	{MISENSOW_16BIT,	0xD2AE, 0x9502},
	{MISENSOW_16BIT,	0xD2B0, 0x7608},
	{MISENSOW_16BIT,	0xD2B2, 0xB8A8},
	{MISENSOW_16BIT,	0xD2B4, 0xB502},
	{MISENSOW_16BIT,	0xD2B6, 0x70CF},
	{MISENSOW_16BIT,	0xD2B8, 0x0000},
	{MISENSOW_16BIT,	0xD2BA, 0x5536},
	{MISENSOW_16BIT,	0xD2BC, 0x7860},
	{MISENSOW_16BIT,	0xD2BE, 0x2686},
	{MISENSOW_16BIT,	0xD2C0, 0x1FFB},
	{MISENSOW_16BIT,	0xD2C2, 0x9502},
	{MISENSOW_16BIT,	0xD2C4, 0x78C5},
	{MISENSOW_16BIT,	0xD2C6, 0x0631},
	{MISENSOW_16BIT,	0xD2C8, 0x05E0},
	{MISENSOW_16BIT,	0xD2CA, 0xB502},
	{MISENSOW_16BIT,	0xD2CC, 0x72CF},
	{MISENSOW_16BIT,	0xD2CE, 0xFFFF},
	{MISENSOW_16BIT,	0xD2D0, 0xC5D4},
	{MISENSOW_16BIT,	0xD2D2, 0x923A},
	{MISENSOW_16BIT,	0xD2D4, 0x73CF},
	{MISENSOW_16BIT,	0xD2D6, 0xFFFF},
	{MISENSOW_16BIT,	0xD2D8, 0xC7D0},
	{MISENSOW_16BIT,	0xD2DA, 0xB020},
	{MISENSOW_16BIT,	0xD2DC, 0x9220},
	{MISENSOW_16BIT,	0xD2DE, 0xB021},
	{MISENSOW_16BIT,	0xD2E0, 0x9221},
	{MISENSOW_16BIT,	0xD2E2, 0xB022},
	{MISENSOW_16BIT,	0xD2E4, 0x9222},
	{MISENSOW_16BIT,	0xD2E6, 0xB023},
	{MISENSOW_16BIT,	0xD2E8, 0x9223},
	{MISENSOW_16BIT,	0xD2EA, 0xB024},
	{MISENSOW_16BIT,	0xD2EC, 0x9227},
	{MISENSOW_16BIT,	0xD2EE, 0xB025},
	{MISENSOW_16BIT,	0xD2F0, 0x9228},
	{MISENSOW_16BIT,	0xD2F2, 0xB026},
	{MISENSOW_16BIT,	0xD2F4, 0x922B},
	{MISENSOW_16BIT,	0xD2F6, 0xB027},
	{MISENSOW_16BIT,	0xD2F8, 0x922C},
	{MISENSOW_16BIT,	0xD2FA, 0xB028},
	{MISENSOW_16BIT,	0xD2FC, 0x1258},
	{MISENSOW_16BIT,	0xD2FE, 0x0101},
	{MISENSOW_16BIT,	0xD300, 0xB029},
	{MISENSOW_16BIT,	0xD302, 0x125A},
	{MISENSOW_16BIT,	0xD304, 0x0101},
	{MISENSOW_16BIT,	0xD306, 0xB02A},
	{MISENSOW_16BIT,	0xD308, 0x1336},
	{MISENSOW_16BIT,	0xD30A, 0x8081},
	{MISENSOW_16BIT,	0xD30C, 0xA836},
	{MISENSOW_16BIT,	0xD30E, 0x1337},
	{MISENSOW_16BIT,	0xD310, 0x8081},
	{MISENSOW_16BIT,	0xD312, 0xA837},
	{MISENSOW_16BIT,	0xD314, 0x12A7},
	{MISENSOW_16BIT,	0xD316, 0x0701},
	{MISENSOW_16BIT,	0xD318, 0xB02C},
	{MISENSOW_16BIT,	0xD31A, 0x1354},
	{MISENSOW_16BIT,	0xD31C, 0x8081},
	{MISENSOW_16BIT,	0xD31E, 0x7FE0},
	{MISENSOW_16BIT,	0xD320, 0xA83A},
	{MISENSOW_16BIT,	0xD322, 0x78E0},
	{MISENSOW_16BIT,	0xD324, 0xC0F1},
	{MISENSOW_16BIT,	0xD326, 0x0DC2},
	{MISENSOW_16BIT,	0xD328, 0x05C0},
	{MISENSOW_16BIT,	0xD32A, 0x7608},
	{MISENSOW_16BIT,	0xD32C, 0x09BB},
	{MISENSOW_16BIT,	0xD32E, 0x0010},
	{MISENSOW_16BIT,	0xD330, 0x75CF},
	{MISENSOW_16BIT,	0xD332, 0xFFFF},
	{MISENSOW_16BIT,	0xD334, 0xD4E0},
	{MISENSOW_16BIT,	0xD336, 0x8D21},
	{MISENSOW_16BIT,	0xD338, 0x8D00},
	{MISENSOW_16BIT,	0xD33A, 0x2153},
	{MISENSOW_16BIT,	0xD33C, 0x0003},
	{MISENSOW_16BIT,	0xD33E, 0xB8C0},
	{MISENSOW_16BIT,	0xD340, 0x8D45},
	{MISENSOW_16BIT,	0xD342, 0x0B23},
	{MISENSOW_16BIT,	0xD344, 0x0000},
	{MISENSOW_16BIT,	0xD346, 0xEA8F},
	{MISENSOW_16BIT,	0xD348, 0x0915},
	{MISENSOW_16BIT,	0xD34A, 0x001E},
	{MISENSOW_16BIT,	0xD34C, 0xFF81},
	{MISENSOW_16BIT,	0xD34E, 0xE808},
	{MISENSOW_16BIT,	0xD350, 0x2540},
	{MISENSOW_16BIT,	0xD352, 0x1900},
	{MISENSOW_16BIT,	0xD354, 0xFFDE},
	{MISENSOW_16BIT,	0xD356, 0x8D00},
	{MISENSOW_16BIT,	0xD358, 0xB880},
	{MISENSOW_16BIT,	0xD35A, 0xF004},
	{MISENSOW_16BIT,	0xD35C, 0x8D00},
	{MISENSOW_16BIT,	0xD35E, 0xB8A0},
	{MISENSOW_16BIT,	0xD360, 0xAD00},
	{MISENSOW_16BIT,	0xD362, 0x8D05},
	{MISENSOW_16BIT,	0xD364, 0xE081},
	{MISENSOW_16BIT,	0xD366, 0x20CC},
	{MISENSOW_16BIT,	0xD368, 0x80A2},
	{MISENSOW_16BIT,	0xD36A, 0xDF00},
	{MISENSOW_16BIT,	0xD36C, 0xF40A},
	{MISENSOW_16BIT,	0xD36E, 0x71CF},
	{MISENSOW_16BIT,	0xD370, 0xFFFF},
	{MISENSOW_16BIT,	0xD372, 0xC84C},
	{MISENSOW_16BIT,	0xD374, 0x9102},
	{MISENSOW_16BIT,	0xD376, 0x7708},
	{MISENSOW_16BIT,	0xD378, 0xB8A6},
	{MISENSOW_16BIT,	0xD37A, 0x2786},
	{MISENSOW_16BIT,	0xD37C, 0x1FFE},
	{MISENSOW_16BIT,	0xD37E, 0xB102},
	{MISENSOW_16BIT,	0xD380, 0x0B42},
	{MISENSOW_16BIT,	0xD382, 0x0180},
	{MISENSOW_16BIT,	0xD384, 0x0E3E},
	{MISENSOW_16BIT,	0xD386, 0x0180},
	{MISENSOW_16BIT,	0xD388, 0x0F4A},
	{MISENSOW_16BIT,	0xD38A, 0x0160},
	{MISENSOW_16BIT,	0xD38C, 0x70C9},
	{MISENSOW_16BIT,	0xD38E, 0x8D05},
	{MISENSOW_16BIT,	0xD390, 0xE081},
	{MISENSOW_16BIT,	0xD392, 0x20CC},
	{MISENSOW_16BIT,	0xD394, 0x80A2},
	{MISENSOW_16BIT,	0xD396, 0xF429},
	{MISENSOW_16BIT,	0xD398, 0x76CF},
	{MISENSOW_16BIT,	0xD39A, 0xFFFF},
	{MISENSOW_16BIT,	0xD39C, 0xC84C},
	{MISENSOW_16BIT,	0xD39E, 0x082D},
	{MISENSOW_16BIT,	0xD3A0, 0x0051},
	{MISENSOW_16BIT,	0xD3A2, 0x70CF},
	{MISENSOW_16BIT,	0xD3A4, 0xFFFF},
	{MISENSOW_16BIT,	0xD3A6, 0xC90C},
	{MISENSOW_16BIT,	0xD3A8, 0x8805},
	{MISENSOW_16BIT,	0xD3AA, 0x09B6},
	{MISENSOW_16BIT,	0xD3AC, 0x0360},
	{MISENSOW_16BIT,	0xD3AE, 0xD908},
	{MISENSOW_16BIT,	0xD3B0, 0x2099},
	{MISENSOW_16BIT,	0xD3B2, 0x0802},
	{MISENSOW_16BIT,	0xD3B4, 0x9634},
	{MISENSOW_16BIT,	0xD3B6, 0xB503},
	{MISENSOW_16BIT,	0xD3B8, 0x7902},
	{MISENSOW_16BIT,	0xD3BA, 0x1523},
	{MISENSOW_16BIT,	0xD3BC, 0x1080},
	{MISENSOW_16BIT,	0xD3BE, 0xB634},
	{MISENSOW_16BIT,	0xD3C0, 0xE001},
	{MISENSOW_16BIT,	0xD3C2, 0x1D23},
	{MISENSOW_16BIT,	0xD3C4, 0x1002},
	{MISENSOW_16BIT,	0xD3C6, 0xF00B},
	{MISENSOW_16BIT,	0xD3C8, 0x9634},
	{MISENSOW_16BIT,	0xD3CA, 0x9503},
	{MISENSOW_16BIT,	0xD3CC, 0x6038},
	{MISENSOW_16BIT,	0xD3CE, 0xB614},
	{MISENSOW_16BIT,	0xD3D0, 0x153F},
	{MISENSOW_16BIT,	0xD3D2, 0x1080},
	{MISENSOW_16BIT,	0xD3D4, 0xE001},
	{MISENSOW_16BIT,	0xD3D6, 0x1D3F},
	{MISENSOW_16BIT,	0xD3D8, 0x1002},
	{MISENSOW_16BIT,	0xD3DA, 0xFFA4},
	{MISENSOW_16BIT,	0xD3DC, 0x9602},
	{MISENSOW_16BIT,	0xD3DE, 0x7F05},
	{MISENSOW_16BIT,	0xD3E0, 0xD800},
	{MISENSOW_16BIT,	0xD3E2, 0xB6E2},
	{MISENSOW_16BIT,	0xD3E4, 0xAD05},
	{MISENSOW_16BIT,	0xD3E6, 0x0511},
	{MISENSOW_16BIT,	0xD3E8, 0x05E0},
	{MISENSOW_16BIT,	0xD3EA, 0xD800},
	{MISENSOW_16BIT,	0xD3EC, 0xC0F1},
	{MISENSOW_16BIT,	0xD3EE, 0x0CFE},
	{MISENSOW_16BIT,	0xD3F0, 0x05C0},
	{MISENSOW_16BIT,	0xD3F2, 0x0A96},
	{MISENSOW_16BIT,	0xD3F4, 0x05A0},
	{MISENSOW_16BIT,	0xD3F6, 0x7608},
	{MISENSOW_16BIT,	0xD3F8, 0x0C22},
	{MISENSOW_16BIT,	0xD3FA, 0x0240},
	{MISENSOW_16BIT,	0xD3FC, 0xE080},
	{MISENSOW_16BIT,	0xD3FE, 0x20CA},
	{MISENSOW_16BIT,	0xD400, 0x0F82},
	{MISENSOW_16BIT,	0xD402, 0x0000},
	{MISENSOW_16BIT,	0xD404, 0x190B},
	{MISENSOW_16BIT,	0xD406, 0x0C60},
	{MISENSOW_16BIT,	0xD408, 0x05A2},
	{MISENSOW_16BIT,	0xD40A, 0x21CA},
	{MISENSOW_16BIT,	0xD40C, 0x0022},
	{MISENSOW_16BIT,	0xD40E, 0x0C56},
	{MISENSOW_16BIT,	0xD410, 0x0240},
	{MISENSOW_16BIT,	0xD412, 0xE806},
	{MISENSOW_16BIT,	0xD414, 0x0E0E},
	{MISENSOW_16BIT,	0xD416, 0x0220},
	{MISENSOW_16BIT,	0xD418, 0x70C9},
	{MISENSOW_16BIT,	0xD41A, 0xF048},
	{MISENSOW_16BIT,	0xD41C, 0x0896},
	{MISENSOW_16BIT,	0xD41E, 0x0440},
	{MISENSOW_16BIT,	0xD420, 0x0E96},
	{MISENSOW_16BIT,	0xD422, 0x0400},
	{MISENSOW_16BIT,	0xD424, 0x0966},
	{MISENSOW_16BIT,	0xD426, 0x0380},
	{MISENSOW_16BIT,	0xD428, 0x75CF},
	{MISENSOW_16BIT,	0xD42A, 0xFFFF},
	{MISENSOW_16BIT,	0xD42C, 0xD4E0},
	{MISENSOW_16BIT,	0xD42E, 0x8D00},
	{MISENSOW_16BIT,	0xD430, 0x084D},
	{MISENSOW_16BIT,	0xD432, 0x001E},
	{MISENSOW_16BIT,	0xD434, 0xFF47},
	{MISENSOW_16BIT,	0xD436, 0x080D},
	{MISENSOW_16BIT,	0xD438, 0x0050},
	{MISENSOW_16BIT,	0xD43A, 0xFF57},
	{MISENSOW_16BIT,	0xD43C, 0x0841},
	{MISENSOW_16BIT,	0xD43E, 0x0051},
	{MISENSOW_16BIT,	0xD440, 0x8D04},
	{MISENSOW_16BIT,	0xD442, 0x9521},
	{MISENSOW_16BIT,	0xD444, 0xE064},
	{MISENSOW_16BIT,	0xD446, 0x790C},
	{MISENSOW_16BIT,	0xD448, 0x702F},
	{MISENSOW_16BIT,	0xD44A, 0x0CE2},
	{MISENSOW_16BIT,	0xD44C, 0x05E0},
	{MISENSOW_16BIT,	0xD44E, 0xD964},
	{MISENSOW_16BIT,	0xD450, 0x72CF},
	{MISENSOW_16BIT,	0xD452, 0xFFFF},
	{MISENSOW_16BIT,	0xD454, 0xC700},
	{MISENSOW_16BIT,	0xD456, 0x9235},
	{MISENSOW_16BIT,	0xD458, 0x0811},
	{MISENSOW_16BIT,	0xD45A, 0x0043},
	{MISENSOW_16BIT,	0xD45C, 0xFF3D},
	{MISENSOW_16BIT,	0xD45E, 0x080D},
	{MISENSOW_16BIT,	0xD460, 0x0051},
	{MISENSOW_16BIT,	0xD462, 0xD801},
	{MISENSOW_16BIT,	0xD464, 0xFF77},
	{MISENSOW_16BIT,	0xD466, 0xF025},
	{MISENSOW_16BIT,	0xD468, 0x9501},
	{MISENSOW_16BIT,	0xD46A, 0x9235},
	{MISENSOW_16BIT,	0xD46C, 0x0911},
	{MISENSOW_16BIT,	0xD46E, 0x0003},
	{MISENSOW_16BIT,	0xD470, 0xFF49},
	{MISENSOW_16BIT,	0xD472, 0x080D},
	{MISENSOW_16BIT,	0xD474, 0x0051},
	{MISENSOW_16BIT,	0xD476, 0xD800},
	{MISENSOW_16BIT,	0xD478, 0xFF72},
	{MISENSOW_16BIT,	0xD47A, 0xF01B},
	{MISENSOW_16BIT,	0xD47C, 0x0886},
	{MISENSOW_16BIT,	0xD47E, 0x03E0},
	{MISENSOW_16BIT,	0xD480, 0xD801},
	{MISENSOW_16BIT,	0xD482, 0x0EF6},
	{MISENSOW_16BIT,	0xD484, 0x03C0},
	{MISENSOW_16BIT,	0xD486, 0x0F52},
	{MISENSOW_16BIT,	0xD488, 0x0340},
	{MISENSOW_16BIT,	0xD48A, 0x0DBA},
	{MISENSOW_16BIT,	0xD48C, 0x0200},
	{MISENSOW_16BIT,	0xD48E, 0x0AF6},
	{MISENSOW_16BIT,	0xD490, 0x0440},
	{MISENSOW_16BIT,	0xD492, 0x0C22},
	{MISENSOW_16BIT,	0xD494, 0x0400},
	{MISENSOW_16BIT,	0xD496, 0x0D72},
	{MISENSOW_16BIT,	0xD498, 0x0440},
	{MISENSOW_16BIT,	0xD49A, 0x0DC2},
	{MISENSOW_16BIT,	0xD49C, 0x0200},
	{MISENSOW_16BIT,	0xD49E, 0x0972},
	{MISENSOW_16BIT,	0xD4A0, 0x0440},
	{MISENSOW_16BIT,	0xD4A2, 0x0D3A},
	{MISENSOW_16BIT,	0xD4A4, 0x0220},
	{MISENSOW_16BIT,	0xD4A6, 0xD820},
	{MISENSOW_16BIT,	0xD4A8, 0x0BFA},
	{MISENSOW_16BIT,	0xD4AA, 0x0260},
	{MISENSOW_16BIT,	0xD4AC, 0x70C9},
	{MISENSOW_16BIT,	0xD4AE, 0x0451},
	{MISENSOW_16BIT,	0xD4B0, 0x05C0},
	{MISENSOW_16BIT,	0xD4B2, 0x78E0},
	{MISENSOW_16BIT,	0xD4B4, 0xD900},
	{MISENSOW_16BIT,	0xD4B6, 0xF00A},
	{MISENSOW_16BIT,	0xD4B8, 0x70CF},
	{MISENSOW_16BIT,	0xD4BA, 0xFFFF},
	{MISENSOW_16BIT,	0xD4BC, 0xD520},
	{MISENSOW_16BIT,	0xD4BE, 0x7835},
	{MISENSOW_16BIT,	0xD4C0, 0x8041},
	{MISENSOW_16BIT,	0xD4C2, 0x8000},
	{MISENSOW_16BIT,	0xD4C4, 0xE102},
	{MISENSOW_16BIT,	0xD4C6, 0xA040},
	{MISENSOW_16BIT,	0xD4C8, 0x09F1},
	{MISENSOW_16BIT,	0xD4CA, 0x8114},
	{MISENSOW_16BIT,	0xD4CC, 0x71CF},
	{MISENSOW_16BIT,	0xD4CE, 0xFFFF},
	{MISENSOW_16BIT,	0xD4D0, 0xD4E0},
	{MISENSOW_16BIT,	0xD4D2, 0x70CF},
	{MISENSOW_16BIT,	0xD4D4, 0xFFFF},
	{MISENSOW_16BIT,	0xD4D6, 0xC594},
	{MISENSOW_16BIT,	0xD4D8, 0xB03A},
	{MISENSOW_16BIT,	0xD4DA, 0x7FE0},
	{MISENSOW_16BIT,	0xD4DC, 0xD800},
	{MISENSOW_16BIT,	0xD4DE, 0x0000},
	{MISENSOW_16BIT,	0xD4E0, 0x0000},
	{MISENSOW_16BIT,	0xD4E2, 0x0500},
	{MISENSOW_16BIT,	0xD4E4, 0x0500},
	{MISENSOW_16BIT,	0xD4E6, 0x0200},
	{MISENSOW_16BIT,	0xD4E8, 0x0330},
	{MISENSOW_16BIT,	0xD4EA, 0x0000},
	{MISENSOW_16BIT,	0xD4EC, 0x0000},
	{MISENSOW_16BIT,	0xD4EE, 0x03CD},
	{MISENSOW_16BIT,	0xD4F0, 0x050D},
	{MISENSOW_16BIT,	0xD4F2, 0x01C5},
	{MISENSOW_16BIT,	0xD4F4, 0x03B3},
	{MISENSOW_16BIT,	0xD4F6, 0x00E0},
	{MISENSOW_16BIT,	0xD4F8, 0x01E3},
	{MISENSOW_16BIT,	0xD4FA, 0x0280},
	{MISENSOW_16BIT,	0xD4FC, 0x01E0},
	{MISENSOW_16BIT,	0xD4FE, 0x0109},
	{MISENSOW_16BIT,	0xD500, 0x0080},
	{MISENSOW_16BIT,	0xD502, 0x0500},
	{MISENSOW_16BIT,	0xD504, 0x0000},
	{MISENSOW_16BIT,	0xD506, 0x0000},
	{MISENSOW_16BIT,	0xD508, 0x0000},
	{MISENSOW_16BIT,	0xD50A, 0x0000},
	{MISENSOW_16BIT,	0xD50C, 0x0000},
	{MISENSOW_16BIT,	0xD50E, 0x0000},
	{MISENSOW_16BIT,	0xD510, 0x0000},
	{MISENSOW_16BIT,	0xD512, 0x0000},
	{MISENSOW_16BIT,	0xD514, 0x0000},
	{MISENSOW_16BIT,	0xD516, 0x0000},
	{MISENSOW_16BIT,	0xD518, 0x0000},
	{MISENSOW_16BIT,	0xD51A, 0x0000},
	{MISENSOW_16BIT,	0xD51C, 0x0000},
	{MISENSOW_16BIT,	0xD51E, 0x0000},
	{MISENSOW_16BIT,	0xD520, 0xFFFF},
	{MISENSOW_16BIT,	0xD522, 0xC9B4},
	{MISENSOW_16BIT,	0xD524, 0xFFFF},
	{MISENSOW_16BIT,	0xD526, 0xD324},
	{MISENSOW_16BIT,	0xD528, 0xFFFF},
	{MISENSOW_16BIT,	0xD52A, 0xCA34},
	{MISENSOW_16BIT,	0xD52C, 0xFFFF},
	{MISENSOW_16BIT,	0xD52E, 0xD3EC},
	{MISENSOW_16BIT,	0x098E, 0x0000},
	{MISENSOW_16BIT,	0xE000, 0x04B4},
	{MISENSOW_16BIT,	0xE002, 0x0302},
	{MISENSOW_16BIT,	0xE004, 0x4103},
	{MISENSOW_16BIT,	0xE006, 0x0202},
	{MISENSOW_16BIT,	0x0080, 0xFFF0},
	{MISENSOW_16BIT,	0x0080, 0xFFF1},

	/* PGA pawametew and APGA
	 * [Step4-APGA] [TP101_MT9M114_APGA]
	 */
	{MISENSOW_16BIT,	0x098E, 0x495E},
	{MISENSOW_16BIT,	0xC95E, 0x0000},
	{MISENSOW_16BIT,	0x3640, 0x02B0},
	{MISENSOW_16BIT,	0x3642, 0x8063},
	{MISENSOW_16BIT,	0x3644, 0x78D0},
	{MISENSOW_16BIT,	0x3646, 0x50CC},
	{MISENSOW_16BIT,	0x3648, 0x3511},
	{MISENSOW_16BIT,	0x364A, 0x0110},
	{MISENSOW_16BIT,	0x364C, 0xBD8A},
	{MISENSOW_16BIT,	0x364E, 0x0CD1},
	{MISENSOW_16BIT,	0x3650, 0x24ED},
	{MISENSOW_16BIT,	0x3652, 0x7C11},
	{MISENSOW_16BIT,	0x3654, 0x0150},
	{MISENSOW_16BIT,	0x3656, 0x124C},
	{MISENSOW_16BIT,	0x3658, 0x3130},
	{MISENSOW_16BIT,	0x365A, 0x508C},
	{MISENSOW_16BIT,	0x365C, 0x21F1},
	{MISENSOW_16BIT,	0x365E, 0x0090},
	{MISENSOW_16BIT,	0x3660, 0xBFCA},
	{MISENSOW_16BIT,	0x3662, 0x0A11},
	{MISENSOW_16BIT,	0x3664, 0x4F4B},
	{MISENSOW_16BIT,	0x3666, 0x28B1},
	{MISENSOW_16BIT,	0x3680, 0x50A9},
	{MISENSOW_16BIT,	0x3682, 0xA04B},
	{MISENSOW_16BIT,	0x3684, 0x0E2D},
	{MISENSOW_16BIT,	0x3686, 0x73EC},
	{MISENSOW_16BIT,	0x3688, 0x164F},
	{MISENSOW_16BIT,	0x368A, 0xF829},
	{MISENSOW_16BIT,	0x368C, 0xC1A8},
	{MISENSOW_16BIT,	0x368E, 0xB0EC},
	{MISENSOW_16BIT,	0x3690, 0xE76A},
	{MISENSOW_16BIT,	0x3692, 0x69AF},
	{MISENSOW_16BIT,	0x3694, 0x378C},
	{MISENSOW_16BIT,	0x3696, 0xA70D},
	{MISENSOW_16BIT,	0x3698, 0x884F},
	{MISENSOW_16BIT,	0x369A, 0xEE8B},
	{MISENSOW_16BIT,	0x369C, 0x5DEF},
	{MISENSOW_16BIT,	0x369E, 0x27CC},
	{MISENSOW_16BIT,	0x36A0, 0xCAAC},
	{MISENSOW_16BIT,	0x36A2, 0x840E},
	{MISENSOW_16BIT,	0x36A4, 0xDAA9},
	{MISENSOW_16BIT,	0x36A6, 0xF00C},
	{MISENSOW_16BIT,	0x36C0, 0x1371},
	{MISENSOW_16BIT,	0x36C2, 0x272F},
	{MISENSOW_16BIT,	0x36C4, 0x2293},
	{MISENSOW_16BIT,	0x36C6, 0xE6D0},
	{MISENSOW_16BIT,	0x36C8, 0xEC32},
	{MISENSOW_16BIT,	0x36CA, 0x11B1},
	{MISENSOW_16BIT,	0x36CC, 0x7BAF},
	{MISENSOW_16BIT,	0x36CE, 0x5813},
	{MISENSOW_16BIT,	0x36D0, 0xB871},
	{MISENSOW_16BIT,	0x36D2, 0x8913},
	{MISENSOW_16BIT,	0x36D4, 0x4610},
	{MISENSOW_16BIT,	0x36D6, 0x7EEE},
	{MISENSOW_16BIT,	0x36D8, 0x0DF3},
	{MISENSOW_16BIT,	0x36DA, 0xB84F},
	{MISENSOW_16BIT,	0x36DC, 0xB532},
	{MISENSOW_16BIT,	0x36DE, 0x1171},
	{MISENSOW_16BIT,	0x36E0, 0x13CF},
	{MISENSOW_16BIT,	0x36E2, 0x22F3},
	{MISENSOW_16BIT,	0x36E4, 0xE090},
	{MISENSOW_16BIT,	0x36E6, 0x8133},
	{MISENSOW_16BIT,	0x3700, 0x88AE},
	{MISENSOW_16BIT,	0x3702, 0x00EA},
	{MISENSOW_16BIT,	0x3704, 0x344F},
	{MISENSOW_16BIT,	0x3706, 0xEC88},
	{MISENSOW_16BIT,	0x3708, 0x3E91},
	{MISENSOW_16BIT,	0x370A, 0xF12D},
	{MISENSOW_16BIT,	0x370C, 0xB0EF},
	{MISENSOW_16BIT,	0x370E, 0x77CD},
	{MISENSOW_16BIT,	0x3710, 0x7930},
	{MISENSOW_16BIT,	0x3712, 0x5C12},
	{MISENSOW_16BIT,	0x3714, 0x500C},
	{MISENSOW_16BIT,	0x3716, 0x22CE},
	{MISENSOW_16BIT,	0x3718, 0x2370},
	{MISENSOW_16BIT,	0x371A, 0x258F},
	{MISENSOW_16BIT,	0x371C, 0x3D30},
	{MISENSOW_16BIT,	0x371E, 0x370C},
	{MISENSOW_16BIT,	0x3720, 0x03ED},
	{MISENSOW_16BIT,	0x3722, 0x9AD0},
	{MISENSOW_16BIT,	0x3724, 0x7ECF},
	{MISENSOW_16BIT,	0x3726, 0x1093},
	{MISENSOW_16BIT,	0x3740, 0x2391},
	{MISENSOW_16BIT,	0x3742, 0xAAD0},
	{MISENSOW_16BIT,	0x3744, 0x28F2},
	{MISENSOW_16BIT,	0x3746, 0xBA4F},
	{MISENSOW_16BIT,	0x3748, 0xC536},
	{MISENSOW_16BIT,	0x374A, 0x1472},
	{MISENSOW_16BIT,	0x374C, 0xD110},
	{MISENSOW_16BIT,	0x374E, 0x2933},
	{MISENSOW_16BIT,	0x3750, 0xD0D1},
	{MISENSOW_16BIT,	0x3752, 0x9F37},
	{MISENSOW_16BIT,	0x3754, 0x34D1},
	{MISENSOW_16BIT,	0x3756, 0x1C6C},
	{MISENSOW_16BIT,	0x3758, 0x3FD2},
	{MISENSOW_16BIT,	0x375A, 0xCB72},
	{MISENSOW_16BIT,	0x375C, 0xBA96},
	{MISENSOW_16BIT,	0x375E, 0x1551},
	{MISENSOW_16BIT,	0x3760, 0xB74F},
	{MISENSOW_16BIT,	0x3762, 0x1672},
	{MISENSOW_16BIT,	0x3764, 0x84F1},
	{MISENSOW_16BIT,	0x3766, 0xC2D6},
	{MISENSOW_16BIT,	0x3782, 0x01E0},
	{MISENSOW_16BIT,	0x3784, 0x0280},
	{MISENSOW_16BIT,	0x37C0, 0xA6EA},
	{MISENSOW_16BIT,	0x37C2, 0x874B},
	{MISENSOW_16BIT,	0x37C4, 0x85CB},
	{MISENSOW_16BIT,	0x37C6, 0x968A},
	{MISENSOW_16BIT,	0x098E, 0x0000},
	{MISENSOW_16BIT,	0xC960, 0x0AF0},
	{MISENSOW_16BIT,	0xC962, 0x79E2},
	{MISENSOW_16BIT,	0xC964, 0x5EC8},
	{MISENSOW_16BIT,	0xC966, 0x791F},
	{MISENSOW_16BIT,	0xC968, 0x76EE},
	{MISENSOW_16BIT,	0xC96A, 0x0FA0},
	{MISENSOW_16BIT,	0xC96C, 0x7DFA},
	{MISENSOW_16BIT,	0xC96E, 0x7DAF},
	{MISENSOW_16BIT,	0xC970, 0x7E02},
	{MISENSOW_16BIT,	0xC972, 0x7E0A},
	{MISENSOW_16BIT,	0xC974, 0x1964},
	{MISENSOW_16BIT,	0xC976, 0x7CDC},
	{MISENSOW_16BIT,	0xC978, 0x7838},
	{MISENSOW_16BIT,	0xC97A, 0x7C2F},
	{MISENSOW_16BIT,	0xC97C, 0x7792},
	{MISENSOW_16BIT,	0xC95E, 0x0003},

	/* [Step4-APGA] */
	{MISENSOW_16BIT,	0x098E, 0x0000},
	{MISENSOW_16BIT,	0xC95E, 0x0003},

	/* [Step5-AWB_CCM]1: WOAD=CCM */
	{MISENSOW_16BIT,	0xC892, 0x0267},
	{MISENSOW_16BIT,	0xC894, 0xFF1A},
	{MISENSOW_16BIT,	0xC896, 0xFFB3},
	{MISENSOW_16BIT,	0xC898, 0xFF80},
	{MISENSOW_16BIT,	0xC89A, 0x0166},
	{MISENSOW_16BIT,	0xC89C, 0x0003},
	{MISENSOW_16BIT,	0xC89E, 0xFF9A},
	{MISENSOW_16BIT,	0xC8A0, 0xFEB4},
	{MISENSOW_16BIT,	0xC8A2, 0x024D},
	{MISENSOW_16BIT,	0xC8A4, 0x01BF},
	{MISENSOW_16BIT,	0xC8A6, 0xFF01},
	{MISENSOW_16BIT,	0xC8A8, 0xFFF3},
	{MISENSOW_16BIT,	0xC8AA, 0xFF75},
	{MISENSOW_16BIT,	0xC8AC, 0x0198},
	{MISENSOW_16BIT,	0xC8AE, 0xFFFD},
	{MISENSOW_16BIT,	0xC8B0, 0xFF9A},
	{MISENSOW_16BIT,	0xC8B2, 0xFEE7},
	{MISENSOW_16BIT,	0xC8B4, 0x02A8},
	{MISENSOW_16BIT,	0xC8B6, 0x01D9},
	{MISENSOW_16BIT,	0xC8B8, 0xFF26},
	{MISENSOW_16BIT,	0xC8BA, 0xFFF3},
	{MISENSOW_16BIT,	0xC8BC, 0xFFB3},
	{MISENSOW_16BIT,	0xC8BE, 0x0132},
	{MISENSOW_16BIT,	0xC8C0, 0xFFE8},
	{MISENSOW_16BIT,	0xC8C2, 0xFFDA},
	{MISENSOW_16BIT,	0xC8C4, 0xFECD},
	{MISENSOW_16BIT,	0xC8C6, 0x02C2},
	{MISENSOW_16BIT,	0xC8C8, 0x0075},
	{MISENSOW_16BIT,	0xC8CA, 0x011C},
	{MISENSOW_16BIT,	0xC8CC, 0x009A},
	{MISENSOW_16BIT,	0xC8CE, 0x0105},
	{MISENSOW_16BIT,	0xC8D0, 0x00A4},
	{MISENSOW_16BIT,	0xC8D2, 0x00AC},
	{MISENSOW_16BIT,	0xC8D4, 0x0A8C},
	{MISENSOW_16BIT,	0xC8D6, 0x0F0A},
	{MISENSOW_16BIT,	0xC8D8, 0x1964},

	/* WOAD=AWB */
	{MISENSOW_16BIT,	0xC914, 0x0000},
	{MISENSOW_16BIT,	0xC916, 0x0000},
	{MISENSOW_16BIT,	0xC918, 0x04FF},
	{MISENSOW_16BIT,	0xC91A, 0x02CF},
	{MISENSOW_16BIT,	0xC904, 0x0033},
	{MISENSOW_16BIT,	0xC906, 0x0040},
	{MISENSOW_8BIT,   0xC8F2, 0x03},
	{MISENSOW_8BIT,   0xC8F3, 0x02},
	{MISENSOW_16BIT,	0xC906, 0x003C},
	{MISENSOW_16BIT,	0xC8F4, 0x0000},
	{MISENSOW_16BIT,	0xC8F6, 0x0000},
	{MISENSOW_16BIT,	0xC8F8, 0x0000},
	{MISENSOW_16BIT,	0xC8FA, 0xE724},
	{MISENSOW_16BIT,	0xC8FC, 0x1583},
	{MISENSOW_16BIT,	0xC8FE, 0x2045},
	{MISENSOW_16BIT,	0xC900, 0x05DC},
	{MISENSOW_16BIT,	0xC902, 0x007C},
	{MISENSOW_8BIT,   0xC90C, 0x80},
	{MISENSOW_8BIT,   0xC90D, 0x80},
	{MISENSOW_8BIT,   0xC90E, 0x80},
	{MISENSOW_8BIT,   0xC90F, 0x88},
	{MISENSOW_8BIT,   0xC910, 0x80},
	{MISENSOW_8BIT,   0xC911, 0x80},

	/* WOAD=Step7-CPIPE_Pwefewence */
	{MISENSOW_16BIT,	0xC926, 0x0020},
	{MISENSOW_16BIT,	0xC928, 0x009A},
	{MISENSOW_16BIT,	0xC946, 0x0070},
	{MISENSOW_16BIT,	0xC948, 0x00F3},
	{MISENSOW_16BIT,	0xC952, 0x0020},
	{MISENSOW_16BIT,	0xC954, 0x009A},
	{MISENSOW_8BIT,   0xC92A, 0x80},
	{MISENSOW_8BIT,   0xC92B, 0x4B},
	{MISENSOW_8BIT,   0xC92C, 0x00},
	{MISENSOW_8BIT,   0xC92D, 0xFF},
	{MISENSOW_8BIT,   0xC92E, 0x3C},
	{MISENSOW_8BIT,   0xC92F, 0x02},
	{MISENSOW_8BIT,   0xC930, 0x06},
	{MISENSOW_8BIT,   0xC931, 0x64},
	{MISENSOW_8BIT,   0xC932, 0x01},
	{MISENSOW_8BIT,   0xC933, 0x0C},
	{MISENSOW_8BIT,   0xC934, 0x3C},
	{MISENSOW_8BIT,   0xC935, 0x3C},
	{MISENSOW_8BIT,   0xC936, 0x3C},
	{MISENSOW_8BIT,   0xC937, 0x0F},
	{MISENSOW_8BIT,   0xC938, 0x64},
	{MISENSOW_8BIT,   0xC939, 0x64},
	{MISENSOW_8BIT,   0xC93A, 0x64},
	{MISENSOW_8BIT,   0xC93B, 0x32},
	{MISENSOW_16BIT,	0xC93C, 0x0020},
	{MISENSOW_16BIT,	0xC93E, 0x009A},
	{MISENSOW_16BIT,	0xC940, 0x00DC},
	{MISENSOW_8BIT,   0xC942, 0x38},
	{MISENSOW_8BIT,   0xC943, 0x30},
	{MISENSOW_8BIT,   0xC944, 0x50},
	{MISENSOW_8BIT,   0xC945, 0x19},
	{MISENSOW_16BIT,	0xC94A, 0x0230},
	{MISENSOW_16BIT,	0xC94C, 0x0010},
	{MISENSOW_16BIT,	0xC94E, 0x01CD},
	{MISENSOW_8BIT,   0xC950, 0x05},
	{MISENSOW_8BIT,   0xC951, 0x40},
	{MISENSOW_8BIT,   0xC87B, 0x1B},
	{MISENSOW_8BIT,   0xC878, 0x0E},
	{MISENSOW_16BIT,	0xC890, 0x0080},
	{MISENSOW_16BIT,	0xC886, 0x0100},
	{MISENSOW_16BIT,	0xC87C, 0x005A},
	{MISENSOW_8BIT,   0xB42A, 0x05},
	{MISENSOW_8BIT,   0xA80A, 0x20},

	/* Speed up AE/AWB */
	{MISENSOW_16BIT,	0x098E, 0x2802},
	{MISENSOW_16BIT,	0xA802, 0x0008},
	{MISENSOW_8BIT,   0xC908, 0x01},
	{MISENSOW_8BIT,   0xC879, 0x01},
	{MISENSOW_8BIT,   0xC909, 0x02},
	{MISENSOW_8BIT,   0xA80A, 0x18},
	{MISENSOW_8BIT,   0xA80B, 0x18},
	{MISENSOW_8BIT,   0xAC16, 0x18},
	{MISENSOW_8BIT,   0xC878, 0x0E},

	{MISENSOW_TOK_TEWM, 0, 0}
};

#endif
#endif
