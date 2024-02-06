// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ov2640 Camewa Dwivew
 *
 * Copywight (C) 2010 Awbewto Panizzo <mawamaopewcheseimowto@gmaiw.com>
 *
 * Based on ov772x, ov9640 dwivews and pwevious non mewged impwementations.
 *
 * Copywight 2005-2009 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight (C) 2006, OmniVision
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/v4w2-mediabus.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-image-sizes.h>

#define VAW_SET(x, mask, wshift, wshift)  \
		((((x) >> wshift) & mask) << wshift)
/*
 * DSP wegistews
 * wegistew offset fow BANK_SEW == BANK_SEW_DSP
 */
#define W_BYPASS    0x05 /* Bypass DSP */
#define   W_BYPASS_DSP_BYPAS    0x01 /* Bypass DSP, sensow out diwectwy */
#define   W_BYPASS_USE_DSP      0x00 /* Use the intewnaw DSP */
#define QS          0x44 /* Quantization Scawe Factow */
#define CTWWI       0x50
#define   CTWWI_WP_DP           0x80
#define   CTWWI_WOUND           0x40
#define   CTWWI_V_DIV_SET(x)    VAW_SET(x, 0x3, 0, 3)
#define   CTWWI_H_DIV_SET(x)    VAW_SET(x, 0x3, 0, 0)
#define HSIZE       0x51 /* H_SIZE[7:0] (weaw/4) */
#define   HSIZE_SET(x)          VAW_SET(x, 0xFF, 2, 0)
#define VSIZE       0x52 /* V_SIZE[7:0] (weaw/4) */
#define   VSIZE_SET(x)          VAW_SET(x, 0xFF, 2, 0)
#define XOFFW       0x53 /* OFFSET_X[7:0] */
#define   XOFFW_SET(x)          VAW_SET(x, 0xFF, 0, 0)
#define YOFFW       0x54 /* OFFSET_Y[7:0] */
#define   YOFFW_SET(x)          VAW_SET(x, 0xFF, 0, 0)
#define VHYX        0x55 /* Offset and size compwetion */
#define   VHYX_VSIZE_SET(x)     VAW_SET(x, 0x1, (8+2), 7)
#define   VHYX_HSIZE_SET(x)     VAW_SET(x, 0x1, (8+2), 3)
#define   VHYX_YOFF_SET(x)      VAW_SET(x, 0x3, 8, 4)
#define   VHYX_XOFF_SET(x)      VAW_SET(x, 0x3, 8, 0)
#define DPWP        0x56
#define TEST        0x57 /* Howizontaw size compwetion */
#define   TEST_HSIZE_SET(x)     VAW_SET(x, 0x1, (9+2), 7)
#define ZMOW        0x5A /* Zoom: Out Width  OUTW[7:0] (weaw/4) */
#define   ZMOW_OUTW_SET(x)      VAW_SET(x, 0xFF, 2, 0)
#define ZMOH        0x5B /* Zoom: Out Height OUTH[7:0] (weaw/4) */
#define   ZMOH_OUTH_SET(x)      VAW_SET(x, 0xFF, 2, 0)
#define ZMHH        0x5C /* Zoom: Speed and H&W compwetion */
#define   ZMHH_ZSPEED_SET(x)    VAW_SET(x, 0x0F, 0, 4)
#define   ZMHH_OUTH_SET(x)      VAW_SET(x, 0x1, (8+2), 2)
#define   ZMHH_OUTW_SET(x)      VAW_SET(x, 0x3, (8+2), 0)
#define BPADDW      0x7C /* SDE Indiwect Wegistew Access: Addwess */
#define BPDATA      0x7D /* SDE Indiwect Wegistew Access: Data */
#define CTWW2       0x86 /* DSP Moduwe enabwe 2 */
#define   CTWW2_DCW_EN          0x20
#define   CTWW2_SDE_EN          0x10
#define   CTWW2_UV_ADJ_EN       0x08
#define   CTWW2_UV_AVG_EN       0x04
#define   CTWW2_CMX_EN          0x01
#define CTWW3       0x87 /* DSP Moduwe enabwe 3 */
#define   CTWW3_BPC_EN          0x80
#define   CTWW3_WPC_EN          0x40
#define SIZEW       0x8C /* Image Size Compwetion */
#define   SIZEW_HSIZE8_11_SET(x) VAW_SET(x, 0x1, 11, 6)
#define   SIZEW_HSIZE8_SET(x)    VAW_SET(x, 0x7, 0, 3)
#define   SIZEW_VSIZE8_SET(x)    VAW_SET(x, 0x7, 0, 0)
#define HSIZE8      0xC0 /* Image Howizontaw Size HSIZE[10:3] */
#define   HSIZE8_SET(x)         VAW_SET(x, 0xFF, 3, 0)
#define VSIZE8      0xC1 /* Image Vewticaw Size VSIZE[10:3] */
#define   VSIZE8_SET(x)         VAW_SET(x, 0xFF, 3, 0)
#define CTWW0       0xC2 /* DSP Moduwe enabwe 0 */
#define   CTWW0_AEC_EN       0x80
#define   CTWW0_AEC_SEW      0x40
#define   CTWW0_STAT_SEW     0x20
#define   CTWW0_VFIWST       0x10
#define   CTWW0_YUV422       0x08
#define   CTWW0_YUV_EN       0x04
#define   CTWW0_WGB_EN       0x02
#define   CTWW0_WAW_EN       0x01
#define CTWW1       0xC3 /* DSP Moduwe enabwe 1 */
#define   CTWW1_CIP          0x80
#define   CTWW1_DMY          0x40
#define   CTWW1_WAW_GMA      0x20
#define   CTWW1_DG           0x10
#define   CTWW1_AWB          0x08
#define   CTWW1_AWB_GAIN     0x04
#define   CTWW1_WENC         0x02
#define   CTWW1_PWE          0x01
/*      WEG 0xC7 (unknown name): affects Auto White Bawance (AWB)
 *	  AWB_OFF            0x40
 *	  AWB_SIMPWE         0x10
 *	  AWB_ON             0x00	(Advanced AWB ?) */
#define W_DVP_SP    0xD3 /* DVP output speed contwow */
#define   W_DVP_SP_AUTO_MODE 0x80
#define   W_DVP_SP_DVP_MASK  0x3F /* DVP PCWK = syscwk (48)/[6:0] (YUV0);
				   *          = syscwk (48)/(2*[6:0]) (WAW);*/
#define IMAGE_MODE  0xDA /* Image Output Fowmat Sewect */
#define   IMAGE_MODE_Y8_DVP_EN   0x40
#define   IMAGE_MODE_JPEG_EN     0x10
#define   IMAGE_MODE_YUV422      0x00
#define   IMAGE_MODE_WAW10       0x04 /* (DVP) */
#define   IMAGE_MODE_WGB565      0x08
#define   IMAGE_MODE_HWEF_VSYNC  0x02 /* HWEF timing sewect in DVP JPEG output
				       * mode (0 fow HWEF is same as sensow) */
#define   IMAGE_MODE_WBYTE_FIWST 0x01 /* Byte swap enabwe fow DVP
				       *    1: Wow byte fiwst UYVY (C2[4] =0)
				       *        VYUY (C2[4] =1)
				       *    0: High byte fiwst YUYV (C2[4]=0)
				       *        YVYU (C2[4] = 1) */
#define WESET       0xE0 /* Weset */
#define   WESET_MICWOC       0x40
#define   WESET_SCCB         0x20
#define   WESET_JPEG         0x10
#define   WESET_DVP          0x04
#define   WESET_IPU          0x02
#define   WESET_CIF          0x01
#define WEGED       0xED /* Wegistew ED */
#define   WEGED_CWK_OUT_DIS  0x10
#define MS_SP       0xF0 /* SCCB Mastew Speed */
#define SS_ID       0xF7 /* SCCB Swave ID */
#define SS_CTWW     0xF8 /* SCCB Swave Contwow */
#define   SS_CTWW_ADD_AUTO_INC  0x20
#define   SS_CTWW_EN            0x08
#define   SS_CTWW_DEWAY_CWK     0x04
#define   SS_CTWW_ACC_EN        0x02
#define   SS_CTWW_SEN_PASS_THW  0x01
#define MC_BIST     0xF9 /* Micwocontwowwew misc wegistew */
#define   MC_BIST_WESET           0x80 /* Micwocontwowwew Weset */
#define   MC_BIST_BOOT_WOM_SEW    0x40
#define   MC_BIST_12KB_SEW        0x20
#define   MC_BIST_12KB_MASK       0x30
#define   MC_BIST_512KB_SEW       0x08
#define   MC_BIST_512KB_MASK      0x0C
#define   MC_BIST_BUSY_BIT_W      0x02
#define   MC_BIST_MC_WES_ONE_SH_W 0x02
#define   MC_BIST_WAUNCH          0x01
#define BANK_SEW    0xFF /* Wegistew Bank Sewect */
#define   BANK_SEW_DSP     0x00
#define   BANK_SEW_SENS    0x01

/*
 * Sensow wegistews
 * wegistew offset fow BANK_SEW == BANK_SEW_SENS
 */
#define GAIN        0x00 /* AGC - Gain contwow gain setting */
#define COM1        0x03 /* Common contwow 1 */
#define   COM1_1_DUMMY_FW          0x40
#define   COM1_3_DUMMY_FW          0x80
#define   COM1_7_DUMMY_FW          0xC0
#define   COM1_VWIN_WSB_UXGA       0x0F
#define   COM1_VWIN_WSB_SVGA       0x0A
#define   COM1_VWIN_WSB_CIF        0x06
#define WEG04       0x04 /* Wegistew 04 */
#define   WEG04_DEF             0x20 /* Awways set */
#define   WEG04_HFWIP_IMG       0x80 /* Howizontaw miwwow image ON/OFF */
#define   WEG04_VFWIP_IMG       0x40 /* Vewticaw fwip image ON/OFF */
#define   WEG04_VWEF_EN         0x10
#define   WEG04_HWEF_EN         0x08
#define   WEG04_AEC_SET(x)      VAW_SET(x, 0x3, 0, 0)
#define WEG08       0x08 /* Fwame Exposuwe One-pin Contwow Pwe-chawge Wow Num */
#define COM2        0x09 /* Common contwow 2 */
#define   COM2_SOFT_SWEEP_MODE  0x10 /* Soft sweep mode */
				     /* Output dwive capabiwity */
#define   COM2_OCAP_Nx_SET(N)   (((N) - 1) & 0x03) /* N = [1x .. 4x] */
#define PID         0x0A /* Pwoduct ID Numbew MSB */
#define VEW         0x0B /* Pwoduct ID Numbew WSB */
#define COM3        0x0C /* Common contwow 3 */
#define   COM3_BAND_50H        0x04 /* 0 Fow Banding at 60H */
#define   COM3_BAND_AUTO       0x02 /* Auto Banding */
#define   COM3_SING_FW_SNAPSH  0x01 /* 0 Fow enabwe wive video output aftew the
				     * snapshot sequence*/
#define AEC         0x10 /* AEC[9:2] Exposuwe Vawue */
#define CWKWC       0x11 /* Intewnaw cwock */
#define   CWKWC_EN             0x80
#define   CWKWC_DIV_SET(x)     (((x) - 1) & 0x1F) /* CWK = XVCWK/(x) */
#define COM7        0x12 /* Common contwow 7 */
#define   COM7_SWST            0x80 /* Initiates system weset. Aww wegistews awe
				     * set to factowy defauwt vawues aftew which
				     * the chip wesumes nowmaw opewation */
#define   COM7_WES_UXGA        0x00 /* Wesowution sewectows fow UXGA */
#define   COM7_WES_SVGA        0x40 /* SVGA */
#define   COM7_WES_CIF         0x20 /* CIF */
#define   COM7_ZOOM_EN         0x04 /* Enabwe Zoom mode */
#define   COM7_COWOW_BAW_TEST  0x02 /* Enabwe Cowow Baw Test Pattewn */
#define COM8        0x13 /* Common contwow 8 */
#define   COM8_DEF             0xC0
#define   COM8_BNDF_EN         0x20 /* Banding fiwtew ON/OFF */
#define   COM8_AGC_EN          0x04 /* AGC Auto/Manuaw contwow sewection */
#define   COM8_AEC_EN          0x01 /* Auto/Manuaw Exposuwe contwow */
#define COM9        0x14 /* Common contwow 9
			  * Automatic gain ceiwing - maximum AGC vawue [7:5]*/
#define   COM9_AGC_GAIN_2x     0x00 /* 000 :   2x */
#define   COM9_AGC_GAIN_4x     0x20 /* 001 :   4x */
#define   COM9_AGC_GAIN_8x     0x40 /* 010 :   8x */
#define   COM9_AGC_GAIN_16x    0x60 /* 011 :  16x */
#define   COM9_AGC_GAIN_32x    0x80 /* 100 :  32x */
#define   COM9_AGC_GAIN_64x    0xA0 /* 101 :  64x */
#define   COM9_AGC_GAIN_128x   0xC0 /* 110 : 128x */
#define COM10       0x15 /* Common contwow 10 */
#define   COM10_PCWK_HWEF      0x20 /* PCWK output quawified by HWEF */
#define   COM10_PCWK_WISE      0x10 /* Data is updated at the wising edge of
				     * PCWK (usew can watch data at the next
				     * fawwing edge of PCWK).
				     * 0 othewwise. */
#define   COM10_HWEF_INV       0x08 /* Invewt HWEF powawity:
				     * HWEF negative fow vawid data*/
#define   COM10_VSINC_INV      0x02 /* Invewt VSYNC powawity */
#define HSTAWT      0x17 /* Howizontaw Window stawt MSB 8 bit */
#define HEND        0x18 /* Howizontaw Window end MSB 8 bit */
#define VSTAWT      0x19 /* Vewticaw Window stawt MSB 8 bit */
#define VEND        0x1A /* Vewticaw Window end MSB 8 bit */
#define MIDH        0x1C /* Manufactuwew ID byte - high */
#define MIDW        0x1D /* Manufactuwew ID byte - wow  */
#define AEW         0x24 /* AGC/AEC - Stabwe opewating wegion (uppew wimit) */
#define AEB         0x25 /* AGC/AEC - Stabwe opewating wegion (wowew wimit) */
#define VV          0x26 /* AGC/AEC Fast mode opewating wegion */
#define   VV_HIGH_TH_SET(x)      VAW_SET(x, 0xF, 0, 4)
#define   VV_WOW_TH_SET(x)       VAW_SET(x, 0xF, 0, 0)
#define WEG2A       0x2A /* Dummy pixew insewt MSB */
#define FWAWW       0x2B /* Dummy pixew insewt WSB */
#define ADDVFW      0x2D /* WSB of insewt dummy wines in Vewticaw diwection */
#define ADDVFH      0x2E /* MSB of insewt dummy wines in Vewticaw diwection */
#define YAVG        0x2F /* Y/G Channew Avewage vawue */
#define WEG32       0x32 /* Common Contwow 32 */
#define   WEG32_PCWK_DIV_2    0x80 /* PCWK fweq divided by 2 */
#define   WEG32_PCWK_DIV_4    0xC0 /* PCWK fweq divided by 4 */
#define AWCOM2      0x34 /* Zoom: Howizontaw stawt point */
#define WEG45       0x45 /* Wegistew 45 */
#define FWW         0x46 /* Fwame Wength Adjustment WSBs */
#define FWH         0x47 /* Fwame Wength Adjustment MSBs */
#define COM19       0x48 /* Zoom: Vewticaw stawt point */
#define ZOOMS       0x49 /* Zoom: Vewticaw stawt point */
#define COM22       0x4B /* Fwash wight contwow */
#define COM25       0x4E /* Fow Banding opewations */
#define   COM25_50HZ_BANDING_AEC_MSBS_MASK      0xC0 /* 50Hz Bd. AEC 2 MSBs */
#define   COM25_60HZ_BANDING_AEC_MSBS_MASK      0x30 /* 60Hz Bd. AEC 2 MSBs */
#define   COM25_50HZ_BANDING_AEC_MSBS_SET(x)    VAW_SET(x, 0x3, 8, 6)
#define   COM25_60HZ_BANDING_AEC_MSBS_SET(x)    VAW_SET(x, 0x3, 8, 4)
#define BD50        0x4F /* 50Hz Banding AEC 8 WSBs */
#define   BD50_50HZ_BANDING_AEC_WSBS_SET(x)     VAW_SET(x, 0xFF, 0, 0)
#define BD60        0x50 /* 60Hz Banding AEC 8 WSBs */
#define   BD60_60HZ_BANDING_AEC_WSBS_SET(x)     VAW_SET(x, 0xFF, 0, 0)
#define WEG5A       0x5A /* 50/60Hz Banding Maximum AEC Step */
#define   BD50_MAX_AEC_STEP_MASK         0xF0 /* 50Hz Banding Max. AEC Step */
#define   BD60_MAX_AEC_STEP_MASK         0x0F /* 60Hz Banding Max. AEC Step */
#define   BD50_MAX_AEC_STEP_SET(x)       VAW_SET((x - 1), 0x0F, 0, 4)
#define   BD60_MAX_AEC_STEP_SET(x)       VAW_SET((x - 1), 0x0F, 0, 0)
#define WEG5D       0x5D /* AVGsew[7:0],   16-zone avewage weight option */
#define WEG5E       0x5E /* AVGsew[15:8],  16-zone avewage weight option */
#define WEG5F       0x5F /* AVGsew[23:16], 16-zone avewage weight option */
#define WEG60       0x60 /* AVGsew[31:24], 16-zone avewage weight option */
#define HISTO_WOW   0x61 /* Histogwam Awgowithm Wow Wevew */
#define HISTO_HIGH  0x62 /* Histogwam Awgowithm High Wevew */

/*
 * ID
 */
#define MANUFACTUWEW_ID	0x7FA2
#define PID_OV2640	0x2642
#define VEWSION(pid, vew) ((pid << 8) | (vew & 0xFF))

/*
 * Stwuct
 */
stwuct wegvaw_wist {
	u8 weg_num;
	u8 vawue;
};

stwuct ov2640_win_size {
	chaw				*name;
	u32				width;
	u32				height;
	const stwuct wegvaw_wist	*wegs;
};


stwuct ov2640_pwiv {
	stwuct v4w2_subdev		subdev;
	stwuct media_pad pad;
	stwuct v4w2_ctww_handwew	hdw;
	u32	cfmt_code;
	stwuct cwk			*cwk;
	const stwuct ov2640_win_size	*win;

	stwuct gpio_desc *wesetb_gpio;
	stwuct gpio_desc *pwdn_gpio;

	stwuct mutex wock; /* wock to pwotect stweaming and powew_count */
	boow stweaming;
	int powew_count;
};

/*
 * Wegistews settings
 */

#define ENDMAWKEW { 0xff, 0xff }

static const stwuct wegvaw_wist ov2640_init_wegs[] = {
	{ BANK_SEW, BANK_SEW_DSP },
	{ 0x2c,   0xff },
	{ 0x2e,   0xdf },
	{ BANK_SEW, BANK_SEW_SENS },
	{ 0x3c,   0x32 },
	{ CWKWC,  CWKWC_DIV_SET(1) },
	{ COM2,   COM2_OCAP_Nx_SET(3) },
	{ WEG04,  WEG04_DEF | WEG04_HWEF_EN },
	{ COM8,   COM8_DEF | COM8_BNDF_EN | COM8_AGC_EN | COM8_AEC_EN },
	{ COM9,   COM9_AGC_GAIN_8x | 0x08},
	{ 0x2c,   0x0c },
	{ 0x33,   0x78 },
	{ 0x3a,   0x33 },
	{ 0x3b,   0xfb },
	{ 0x3e,   0x00 },
	{ 0x43,   0x11 },
	{ 0x16,   0x10 },
	{ 0x39,   0x02 },
	{ 0x35,   0x88 },
	{ 0x22,   0x0a },
	{ 0x37,   0x40 },
	{ 0x23,   0x00 },
	{ AWCOM2, 0xa0 },
	{ 0x06,   0x02 },
	{ 0x06,   0x88 },
	{ 0x07,   0xc0 },
	{ 0x0d,   0xb7 },
	{ 0x0e,   0x01 },
	{ 0x4c,   0x00 },
	{ 0x4a,   0x81 },
	{ 0x21,   0x99 },
	{ AEW,    0x40 },
	{ AEB,    0x38 },
	{ VV,     VV_HIGH_TH_SET(0x08) | VV_WOW_TH_SET(0x02) },
	{ 0x5c,   0x00 },
	{ 0x63,   0x00 },
	{ FWW,    0x22 },
	{ COM3,   0x38 | COM3_BAND_AUTO },
	{ WEG5D,  0x55 },
	{ WEG5E,  0x7d },
	{ WEG5F,  0x7d },
	{ WEG60,  0x55 },
	{ HISTO_WOW,   0x70 },
	{ HISTO_HIGH,  0x80 },
	{ 0x7c,   0x05 },
	{ 0x20,   0x80 },
	{ 0x28,   0x30 },
	{ 0x6c,   0x00 },
	{ 0x6d,   0x80 },
	{ 0x6e,   0x00 },
	{ 0x70,   0x02 },
	{ 0x71,   0x94 },
	{ 0x73,   0xc1 },
	{ 0x3d,   0x34 },
	{ COM7,   COM7_WES_UXGA | COM7_ZOOM_EN },
	{ WEG5A,  BD50_MAX_AEC_STEP_SET(6)
		   | BD60_MAX_AEC_STEP_SET(8) },		/* 0x57 */
	{ COM25,  COM25_50HZ_BANDING_AEC_MSBS_SET(0x0bb)
		   | COM25_60HZ_BANDING_AEC_MSBS_SET(0x09c) },	/* 0x00 */
	{ BD50,   BD50_50HZ_BANDING_AEC_WSBS_SET(0x0bb) },	/* 0xbb */
	{ BD60,   BD60_60HZ_BANDING_AEC_WSBS_SET(0x09c) },	/* 0x9c */
	{ BANK_SEW,  BANK_SEW_DSP },
	{ 0xe5,   0x7f },
	{ MC_BIST,  MC_BIST_WESET | MC_BIST_BOOT_WOM_SEW },
	{ 0x41,   0x24 },
	{ WESET,  WESET_JPEG | WESET_DVP },
	{ 0x76,   0xff },
	{ 0x33,   0xa0 },
	{ 0x42,   0x20 },
	{ 0x43,   0x18 },
	{ 0x4c,   0x00 },
	{ CTWW3,  CTWW3_BPC_EN | CTWW3_WPC_EN | 0x10 },
	{ 0x88,   0x3f },
	{ 0xd7,   0x03 },
	{ 0xd9,   0x10 },
	{ W_DVP_SP,  W_DVP_SP_AUTO_MODE | 0x2 },
	{ 0xc8,   0x08 },
	{ 0xc9,   0x80 },
	{ BPADDW, 0x00 },
	{ BPDATA, 0x00 },
	{ BPADDW, 0x03 },
	{ BPDATA, 0x48 },
	{ BPDATA, 0x48 },
	{ BPADDW, 0x08 },
	{ BPDATA, 0x20 },
	{ BPDATA, 0x10 },
	{ BPDATA, 0x0e },
	{ 0x90,   0x00 },
	{ 0x91,   0x0e },
	{ 0x91,   0x1a },
	{ 0x91,   0x31 },
	{ 0x91,   0x5a },
	{ 0x91,   0x69 },
	{ 0x91,   0x75 },
	{ 0x91,   0x7e },
	{ 0x91,   0x88 },
	{ 0x91,   0x8f },
	{ 0x91,   0x96 },
	{ 0x91,   0xa3 },
	{ 0x91,   0xaf },
	{ 0x91,   0xc4 },
	{ 0x91,   0xd7 },
	{ 0x91,   0xe8 },
	{ 0x91,   0x20 },
	{ 0x92,   0x00 },
	{ 0x93,   0x06 },
	{ 0x93,   0xe3 },
	{ 0x93,   0x03 },
	{ 0x93,   0x03 },
	{ 0x93,   0x00 },
	{ 0x93,   0x02 },
	{ 0x93,   0x00 },
	{ 0x93,   0x00 },
	{ 0x93,   0x00 },
	{ 0x93,   0x00 },
	{ 0x93,   0x00 },
	{ 0x93,   0x00 },
	{ 0x93,   0x00 },
	{ 0x96,   0x00 },
	{ 0x97,   0x08 },
	{ 0x97,   0x19 },
	{ 0x97,   0x02 },
	{ 0x97,   0x0c },
	{ 0x97,   0x24 },
	{ 0x97,   0x30 },
	{ 0x97,   0x28 },
	{ 0x97,   0x26 },
	{ 0x97,   0x02 },
	{ 0x97,   0x98 },
	{ 0x97,   0x80 },
	{ 0x97,   0x00 },
	{ 0x97,   0x00 },
	{ 0xa4,   0x00 },
	{ 0xa8,   0x00 },
	{ 0xc5,   0x11 },
	{ 0xc6,   0x51 },
	{ 0xbf,   0x80 },
	{ 0xc7,   0x10 },	/* simpwe AWB */
	{ 0xb6,   0x66 },
	{ 0xb8,   0xA5 },
	{ 0xb7,   0x64 },
	{ 0xb9,   0x7C },
	{ 0xb3,   0xaf },
	{ 0xb4,   0x97 },
	{ 0xb5,   0xFF },
	{ 0xb0,   0xC5 },
	{ 0xb1,   0x94 },
	{ 0xb2,   0x0f },
	{ 0xc4,   0x5c },
	{ 0xa6,   0x00 },
	{ 0xa7,   0x20 },
	{ 0xa7,   0xd8 },
	{ 0xa7,   0x1b },
	{ 0xa7,   0x31 },
	{ 0xa7,   0x00 },
	{ 0xa7,   0x18 },
	{ 0xa7,   0x20 },
	{ 0xa7,   0xd8 },
	{ 0xa7,   0x19 },
	{ 0xa7,   0x31 },
	{ 0xa7,   0x00 },
	{ 0xa7,   0x18 },
	{ 0xa7,   0x20 },
	{ 0xa7,   0xd8 },
	{ 0xa7,   0x19 },
	{ 0xa7,   0x31 },
	{ 0xa7,   0x00 },
	{ 0xa7,   0x18 },
	{ 0x7f,   0x00 },
	{ 0xe5,   0x1f },
	{ 0xe1,   0x77 },
	{ 0xdd,   0x7f },
	{ CTWW0,  CTWW0_YUV422 | CTWW0_YUV_EN | CTWW0_WGB_EN },
	ENDMAWKEW,
};

/*
 * Wegistew settings fow window size
 * The pweambwe, setup the intewnaw DSP to input an UXGA (1600x1200) image.
 * Then the diffewent zooming configuwations wiww setup the output image size.
 */
static const stwuct wegvaw_wist ov2640_size_change_pweambwe_wegs[] = {
	{ BANK_SEW, BANK_SEW_DSP },
	{ WESET, WESET_DVP },
	{ SIZEW, SIZEW_HSIZE8_11_SET(UXGA_WIDTH) |
		 SIZEW_HSIZE8_SET(UXGA_WIDTH) |
		 SIZEW_VSIZE8_SET(UXGA_HEIGHT) },
	{ HSIZE8, HSIZE8_SET(UXGA_WIDTH) },
	{ VSIZE8, VSIZE8_SET(UXGA_HEIGHT) },
	{ CTWW2, CTWW2_DCW_EN | CTWW2_SDE_EN |
		 CTWW2_UV_AVG_EN | CTWW2_CMX_EN | CTWW2_UV_ADJ_EN },
	{ HSIZE, HSIZE_SET(UXGA_WIDTH) },
	{ VSIZE, VSIZE_SET(UXGA_HEIGHT) },
	{ XOFFW, XOFFW_SET(0) },
	{ YOFFW, YOFFW_SET(0) },
	{ VHYX, VHYX_HSIZE_SET(UXGA_WIDTH) | VHYX_VSIZE_SET(UXGA_HEIGHT) |
		VHYX_XOFF_SET(0) | VHYX_YOFF_SET(0)},
	{ TEST, TEST_HSIZE_SET(UXGA_WIDTH) },
	ENDMAWKEW,
};

#define PEW_SIZE_WEG_SEQ(x, y, v_div, h_div, pcwk_div)	\
	{ CTWWI, CTWWI_WP_DP | CTWWI_V_DIV_SET(v_div) |	\
		 CTWWI_H_DIV_SET(h_div)},		\
	{ ZMOW, ZMOW_OUTW_SET(x) },			\
	{ ZMOH, ZMOH_OUTH_SET(y) },			\
	{ ZMHH, ZMHH_OUTW_SET(x) | ZMHH_OUTH_SET(y) },	\
	{ W_DVP_SP, pcwk_div },				\
	{ WESET, 0x00}

static const stwuct wegvaw_wist ov2640_qcif_wegs[] = {
	PEW_SIZE_WEG_SEQ(QCIF_WIDTH, QCIF_HEIGHT, 3, 3, 4),
	ENDMAWKEW,
};

static const stwuct wegvaw_wist ov2640_qvga_wegs[] = {
	PEW_SIZE_WEG_SEQ(QVGA_WIDTH, QVGA_HEIGHT, 2, 2, 4),
	ENDMAWKEW,
};

static const stwuct wegvaw_wist ov2640_cif_wegs[] = {
	PEW_SIZE_WEG_SEQ(CIF_WIDTH, CIF_HEIGHT, 2, 2, 8),
	ENDMAWKEW,
};

static const stwuct wegvaw_wist ov2640_vga_wegs[] = {
	PEW_SIZE_WEG_SEQ(VGA_WIDTH, VGA_HEIGHT, 0, 0, 2),
	ENDMAWKEW,
};

static const stwuct wegvaw_wist ov2640_svga_wegs[] = {
	PEW_SIZE_WEG_SEQ(SVGA_WIDTH, SVGA_HEIGHT, 1, 1, 2),
	ENDMAWKEW,
};

static const stwuct wegvaw_wist ov2640_xga_wegs[] = {
	PEW_SIZE_WEG_SEQ(XGA_WIDTH, XGA_HEIGHT, 0, 0, 2),
	{ CTWWI,    0x00},
	ENDMAWKEW,
};

static const stwuct wegvaw_wist ov2640_sxga_wegs[] = {
	PEW_SIZE_WEG_SEQ(SXGA_WIDTH, SXGA_HEIGHT, 0, 0, 2),
	{ CTWWI,    0x00},
	{ W_DVP_SP, 2 | W_DVP_SP_AUTO_MODE },
	ENDMAWKEW,
};

static const stwuct wegvaw_wist ov2640_uxga_wegs[] = {
	PEW_SIZE_WEG_SEQ(UXGA_WIDTH, UXGA_HEIGHT, 0, 0, 0),
	{ CTWWI,    0x00},
	{ W_DVP_SP, 0 | W_DVP_SP_AUTO_MODE },
	ENDMAWKEW,
};

#define OV2640_SIZE(n, w, h, w) \
	{.name = n, .width = w , .height = h, .wegs = w }

static const stwuct ov2640_win_size ov2640_suppowted_win_sizes[] = {
	OV2640_SIZE("QCIF", QCIF_WIDTH, QCIF_HEIGHT, ov2640_qcif_wegs),
	OV2640_SIZE("QVGA", QVGA_WIDTH, QVGA_HEIGHT, ov2640_qvga_wegs),
	OV2640_SIZE("CIF", CIF_WIDTH, CIF_HEIGHT, ov2640_cif_wegs),
	OV2640_SIZE("VGA", VGA_WIDTH, VGA_HEIGHT, ov2640_vga_wegs),
	OV2640_SIZE("SVGA", SVGA_WIDTH, SVGA_HEIGHT, ov2640_svga_wegs),
	OV2640_SIZE("XGA", XGA_WIDTH, XGA_HEIGHT, ov2640_xga_wegs),
	OV2640_SIZE("SXGA", SXGA_WIDTH, SXGA_HEIGHT, ov2640_sxga_wegs),
	OV2640_SIZE("UXGA", UXGA_WIDTH, UXGA_HEIGHT, ov2640_uxga_wegs),
};

/*
 * Wegistew settings fow pixew fowmats
 */
static const stwuct wegvaw_wist ov2640_fowmat_change_pweambwe_wegs[] = {
	{ BANK_SEW, BANK_SEW_DSP },
	{ W_BYPASS, W_BYPASS_USE_DSP },
	ENDMAWKEW,
};

static const stwuct wegvaw_wist ov2640_yuyv_wegs[] = {
	{ IMAGE_MODE, IMAGE_MODE_YUV422 },
	{ 0xd7, 0x03 },
	{ 0x33, 0xa0 },
	{ 0xe5, 0x1f },
	{ 0xe1, 0x67 },
	{ WESET,  0x00 },
	{ W_BYPASS, W_BYPASS_USE_DSP },
	ENDMAWKEW,
};

static const stwuct wegvaw_wist ov2640_uyvy_wegs[] = {
	{ IMAGE_MODE, IMAGE_MODE_WBYTE_FIWST | IMAGE_MODE_YUV422 },
	{ 0xd7, 0x01 },
	{ 0x33, 0xa0 },
	{ 0xe1, 0x67 },
	{ WESET,  0x00 },
	{ W_BYPASS, W_BYPASS_USE_DSP },
	ENDMAWKEW,
};

static const stwuct wegvaw_wist ov2640_wgb565_be_wegs[] = {
	{ IMAGE_MODE, IMAGE_MODE_WGB565 },
	{ 0xd7, 0x03 },
	{ WESET,  0x00 },
	{ W_BYPASS, W_BYPASS_USE_DSP },
	ENDMAWKEW,
};

static const stwuct wegvaw_wist ov2640_wgb565_we_wegs[] = {
	{ IMAGE_MODE, IMAGE_MODE_WBYTE_FIWST | IMAGE_MODE_WGB565 },
	{ 0xd7, 0x03 },
	{ WESET,  0x00 },
	{ W_BYPASS, W_BYPASS_USE_DSP },
	ENDMAWKEW,
};

static u32 ov2640_codes[] = {
	MEDIA_BUS_FMT_YUYV8_2X8,
	MEDIA_BUS_FMT_UYVY8_2X8,
	MEDIA_BUS_FMT_YVYU8_2X8,
	MEDIA_BUS_FMT_VYUY8_2X8,
	MEDIA_BUS_FMT_WGB565_2X8_BE,
	MEDIA_BUS_FMT_WGB565_2X8_WE,
};

/*
 * Genewaw functions
 */
static stwuct ov2640_pwiv *to_ov2640(const stwuct i2c_cwient *cwient)
{
	wetuwn containew_of(i2c_get_cwientdata(cwient), stwuct ov2640_pwiv,
			    subdev);
}

static int ov2640_wwite_awway(stwuct i2c_cwient *cwient,
			      const stwuct wegvaw_wist *vaws)
{
	int wet;

	whiwe ((vaws->weg_num != 0xff) || (vaws->vawue != 0xff)) {
		wet = i2c_smbus_wwite_byte_data(cwient,
						vaws->weg_num, vaws->vawue);
		dev_vdbg(&cwient->dev, "awway: 0x%02x, 0x%02x",
			 vaws->weg_num, vaws->vawue);

		if (wet < 0)
			wetuwn wet;
		vaws++;
	}
	wetuwn 0;
}

static int ov2640_mask_set(stwuct i2c_cwient *cwient,
			   u8  weg, u8  mask, u8  set)
{
	s32 vaw = i2c_smbus_wead_byte_data(cwient, weg);
	if (vaw < 0)
		wetuwn vaw;

	vaw &= ~mask;
	vaw |= set & mask;

	dev_vdbg(&cwient->dev, "masks: 0x%02x, 0x%02x", weg, vaw);

	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vaw);
}

static int ov2640_weset(stwuct i2c_cwient *cwient)
{
	int wet;
	static const stwuct wegvaw_wist weset_seq[] = {
		{BANK_SEW, BANK_SEW_SENS},
		{COM7, COM7_SWST},
		ENDMAWKEW,
	};

	wet = ov2640_wwite_awway(cwient, weset_seq);
	if (wet)
		goto eww;

	msweep(5);
eww:
	dev_dbg(&cwient->dev, "%s: (wet %d)", __func__, wet);
	wetuwn wet;
}

static const chaw * const ov2640_test_pattewn_menu[] = {
	"Disabwed",
	"Eight Vewticaw Cowouw Baws",
};

/*
 * functions
 */
static int ov2640_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd =
		&containew_of(ctww->handwew, stwuct ov2640_pwiv, hdw)->subdev;
	stwuct i2c_cwient  *cwient = v4w2_get_subdevdata(sd);
	stwuct ov2640_pwiv *pwiv = to_ov2640(cwient);
	u8 vaw;
	int wet;

	/* v4w2_ctww_wock() wocks ouw own mutex */

	/*
	 * If the device is not powewed up by the host dwivew, do not appwy any
	 * contwows to H/W at this time. Instead the contwows wiww be westowed
	 * when the stweaming is stawted.
	 */
	if (!pwiv->powew_count)
		wetuwn 0;

	wet = i2c_smbus_wwite_byte_data(cwient, BANK_SEW, BANK_SEW_SENS);
	if (wet < 0)
		wetuwn wet;

	switch (ctww->id) {
	case V4W2_CID_VFWIP:
		vaw = ctww->vaw ? WEG04_VFWIP_IMG | WEG04_VWEF_EN : 0x00;
		wetuwn ov2640_mask_set(cwient, WEG04,
				       WEG04_VFWIP_IMG | WEG04_VWEF_EN, vaw);
		/* NOTE: WEG04_VWEF_EN: 1 wine shift / even/odd wine swap */
	case V4W2_CID_HFWIP:
		vaw = ctww->vaw ? WEG04_HFWIP_IMG : 0x00;
		wetuwn ov2640_mask_set(cwient, WEG04, WEG04_HFWIP_IMG, vaw);
	case V4W2_CID_TEST_PATTEWN:
		vaw = ctww->vaw ? COM7_COWOW_BAW_TEST : 0x00;
		wetuwn ov2640_mask_set(cwient, COM7, COM7_COWOW_BAW_TEST, vaw);
	}

	wetuwn -EINVAW;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int ov2640_g_wegistew(stwuct v4w2_subdev *sd,
			     stwuct v4w2_dbg_wegistew *weg)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int wet;

	weg->size = 1;
	if (weg->weg > 0xff)
		wetuwn -EINVAW;

	wet = i2c_smbus_wead_byte_data(cwient, weg->weg);
	if (wet < 0)
		wetuwn wet;

	weg->vaw = wet;

	wetuwn 0;
}

static int ov2640_s_wegistew(stwuct v4w2_subdev *sd,
			     const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	if (weg->weg > 0xff ||
	    weg->vaw > 0xff)
		wetuwn -EINVAW;

	wetuwn i2c_smbus_wwite_byte_data(cwient, weg->weg, weg->vaw);
}
#endif

static void ov2640_set_powew(stwuct ov2640_pwiv *pwiv, int on)
{
#ifdef CONFIG_GPIOWIB
	if (pwiv->pwdn_gpio)
		gpiod_diwection_output(pwiv->pwdn_gpio, !on);
	if (on && pwiv->wesetb_gpio) {
		/* Active the wesetb pin to pewfowm a weset puwse */
		gpiod_diwection_output(pwiv->wesetb_gpio, 1);
		usweep_wange(3000, 5000);
		gpiod_set_vawue(pwiv->wesetb_gpio, 0);
	}
#endif
}

static int ov2640_s_powew(stwuct v4w2_subdev *sd, int on)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct ov2640_pwiv *pwiv = to_ov2640(cwient);

	mutex_wock(&pwiv->wock);

	/*
	 * If the powew count is modified fwom 0 to != 0 ow fwom != 0 to 0,
	 * update the powew state.
	 */
	if (pwiv->powew_count == !on)
		ov2640_set_powew(pwiv, on);
	pwiv->powew_count += on ? 1 : -1;
	WAWN_ON(pwiv->powew_count < 0);
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

/* Sewect the neawest highew wesowution fow captuwe */
static const stwuct ov2640_win_size *ov2640_sewect_win(u32 width, u32 height)
{
	int i, defauwt_size = AWWAY_SIZE(ov2640_suppowted_win_sizes) - 1;

	fow (i = 0; i < AWWAY_SIZE(ov2640_suppowted_win_sizes); i++) {
		if (ov2640_suppowted_win_sizes[i].width  >= width &&
		    ov2640_suppowted_win_sizes[i].height >= height)
			wetuwn &ov2640_suppowted_win_sizes[i];
	}

	wetuwn &ov2640_suppowted_win_sizes[defauwt_size];
}

static int ov2640_set_pawams(stwuct i2c_cwient *cwient,
			     const stwuct ov2640_win_size *win, u32 code)
{
	const stwuct wegvaw_wist *sewected_cfmt_wegs;
	u8 vaw;
	int wet;

	switch (code) {
	case MEDIA_BUS_FMT_WGB565_2X8_BE:
		dev_dbg(&cwient->dev, "%s: Sewected cfmt WGB565 BE", __func__);
		sewected_cfmt_wegs = ov2640_wgb565_be_wegs;
		bweak;
	case MEDIA_BUS_FMT_WGB565_2X8_WE:
		dev_dbg(&cwient->dev, "%s: Sewected cfmt WGB565 WE", __func__);
		sewected_cfmt_wegs = ov2640_wgb565_we_wegs;
		bweak;
	case MEDIA_BUS_FMT_YUYV8_2X8:
		dev_dbg(&cwient->dev, "%s: Sewected cfmt YUYV (YUV422)", __func__);
		sewected_cfmt_wegs = ov2640_yuyv_wegs;
		bweak;
	case MEDIA_BUS_FMT_UYVY8_2X8:
	defauwt:
		dev_dbg(&cwient->dev, "%s: Sewected cfmt UYVY", __func__);
		sewected_cfmt_wegs = ov2640_uyvy_wegs;
		bweak;
	case MEDIA_BUS_FMT_YVYU8_2X8:
		dev_dbg(&cwient->dev, "%s: Sewected cfmt YVYU", __func__);
		sewected_cfmt_wegs = ov2640_yuyv_wegs;
		bweak;
	case MEDIA_BUS_FMT_VYUY8_2X8:
		dev_dbg(&cwient->dev, "%s: Sewected cfmt VYUY", __func__);
		sewected_cfmt_wegs = ov2640_uyvy_wegs;
		bweak;
	}

	/* weset hawdwawe */
	ov2640_weset(cwient);

	/* initiawize the sensow with defauwt data */
	dev_dbg(&cwient->dev, "%s: Init defauwt", __func__);
	wet = ov2640_wwite_awway(cwient, ov2640_init_wegs);
	if (wet < 0)
		goto eww;

	/* sewect pweambwe */
	dev_dbg(&cwient->dev, "%s: Set size to %s", __func__, win->name);
	wet = ov2640_wwite_awway(cwient, ov2640_size_change_pweambwe_wegs);
	if (wet < 0)
		goto eww;

	/* set size win */
	wet = ov2640_wwite_awway(cwient, win->wegs);
	if (wet < 0)
		goto eww;

	/* cfmt pweambwe */
	dev_dbg(&cwient->dev, "%s: Set cfmt", __func__);
	wet = ov2640_wwite_awway(cwient, ov2640_fowmat_change_pweambwe_wegs);
	if (wet < 0)
		goto eww;

	/* set cfmt */
	wet = ov2640_wwite_awway(cwient, sewected_cfmt_wegs);
	if (wet < 0)
		goto eww;
	vaw = (code == MEDIA_BUS_FMT_YVYU8_2X8)
	      || (code == MEDIA_BUS_FMT_VYUY8_2X8) ? CTWW0_VFIWST : 0x00;
	wet = ov2640_mask_set(cwient, CTWW0, CTWW0_VFIWST, vaw);
	if (wet < 0)
		goto eww;

	wetuwn 0;

eww:
	dev_eww(&cwient->dev, "%s: Ewwow %d", __func__, wet);
	ov2640_weset(cwient);

	wetuwn wet;
}

static int ov2640_get_fmt(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *mf = &fowmat->fowmat;
	stwuct i2c_cwient  *cwient = v4w2_get_subdevdata(sd);
	stwuct ov2640_pwiv *pwiv = to_ov2640(cwient);

	if (fowmat->pad)
		wetuwn -EINVAW;

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY) {
		mf = v4w2_subdev_state_get_fowmat(sd_state, 0);
		fowmat->fowmat = *mf;
		wetuwn 0;
	}

	mf->width	= pwiv->win->width;
	mf->height	= pwiv->win->height;
	mf->code	= pwiv->cfmt_code;
	mf->cowowspace	= V4W2_COWOWSPACE_SWGB;
	mf->fiewd	= V4W2_FIEWD_NONE;
	mf->ycbcw_enc	= V4W2_YCBCW_ENC_DEFAUWT;
	mf->quantization = V4W2_QUANTIZATION_DEFAUWT;
	mf->xfew_func	= V4W2_XFEW_FUNC_DEFAUWT;

	wetuwn 0;
}

static int ov2640_set_fmt(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *mf = &fowmat->fowmat;
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct ov2640_pwiv *pwiv = to_ov2640(cwient);
	const stwuct ov2640_win_size *win;
	int wet = 0;

	if (fowmat->pad)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	/* sewect suitabwe win */
	win = ov2640_sewect_win(mf->width, mf->height);
	mf->width	= win->width;
	mf->height	= win->height;

	mf->fiewd	= V4W2_FIEWD_NONE;
	mf->cowowspace	= V4W2_COWOWSPACE_SWGB;
	mf->ycbcw_enc	= V4W2_YCBCW_ENC_DEFAUWT;
	mf->quantization = V4W2_QUANTIZATION_DEFAUWT;
	mf->xfew_func	= V4W2_XFEW_FUNC_DEFAUWT;

	switch (mf->code) {
	case MEDIA_BUS_FMT_WGB565_2X8_BE:
	case MEDIA_BUS_FMT_WGB565_2X8_WE:
	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_UYVY8_2X8:
	case MEDIA_BUS_FMT_YVYU8_2X8:
	case MEDIA_BUS_FMT_VYUY8_2X8:
		bweak;
	defauwt:
		mf->code = MEDIA_BUS_FMT_UYVY8_2X8;
		bweak;
	}

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE) {
		stwuct ov2640_pwiv *pwiv = to_ov2640(cwient);

		if (pwiv->stweaming) {
			wet = -EBUSY;
			goto out;
		}
		/* sewect win */
		pwiv->win = win;
		/* sewect fowmat */
		pwiv->cfmt_code = mf->code;
	} ewse {
		*v4w2_subdev_state_get_fowmat(sd_state, 0) = *mf;
	}
out:
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int ov2640_init_state(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state)
{
	stwuct v4w2_mbus_fwamefmt *twy_fmt =
		v4w2_subdev_state_get_fowmat(sd_state, 0);
	const stwuct ov2640_win_size *win =
		ov2640_sewect_win(SVGA_WIDTH, SVGA_HEIGHT);

	twy_fmt->width = win->width;
	twy_fmt->height = win->height;
	twy_fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;
	twy_fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
	twy_fmt->fiewd = V4W2_FIEWD_NONE;
	twy_fmt->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	twy_fmt->quantization = V4W2_QUANTIZATION_DEFAUWT;
	twy_fmt->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;

	wetuwn 0;
}

static int ov2640_enum_mbus_code(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->pad || code->index >= AWWAY_SIZE(ov2640_codes))
		wetuwn -EINVAW;

	code->code = ov2640_codes[code->index];
	wetuwn 0;
}

static int ov2640_get_sewection(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_sewection *sew)
{
	if (sew->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP:
		sew->w.weft = 0;
		sew->w.top = 0;
		sew->w.width = UXGA_WIDTH;
		sew->w.height = UXGA_HEIGHT;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ov2640_s_stweam(stwuct v4w2_subdev *sd, int on)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct ov2640_pwiv *pwiv = to_ov2640(cwient);
	int wet = 0;

	mutex_wock(&pwiv->wock);
	if (pwiv->stweaming == !on) {
		if (on) {
			wet = ov2640_set_pawams(cwient, pwiv->win,
						pwiv->cfmt_code);
			if (!wet)
				wet = __v4w2_ctww_handwew_setup(&pwiv->hdw);
		}
	}
	if (!wet)
		pwiv->stweaming = on;
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int ov2640_video_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ov2640_pwiv *pwiv = to_ov2640(cwient);
	u8 pid, vew, midh, midw;
	const chaw *devname;
	int wet;

	wet = ov2640_s_powew(&pwiv->subdev, 1);
	if (wet < 0)
		wetuwn wet;

	/*
	 * check and show pwoduct ID and manufactuwew ID
	 */
	i2c_smbus_wwite_byte_data(cwient, BANK_SEW, BANK_SEW_SENS);
	pid  = i2c_smbus_wead_byte_data(cwient, PID);
	vew  = i2c_smbus_wead_byte_data(cwient, VEW);
	midh = i2c_smbus_wead_byte_data(cwient, MIDH);
	midw = i2c_smbus_wead_byte_data(cwient, MIDW);

	switch (VEWSION(pid, vew)) {
	case PID_OV2640:
		devname     = "ov2640";
		bweak;
	defauwt:
		dev_eww(&cwient->dev,
			"Pwoduct ID ewwow %x:%x\n", pid, vew);
		wet = -ENODEV;
		goto done;
	}

	dev_info(&cwient->dev,
		 "%s Pwoduct ID %0x:%0x Manufactuwew ID %x:%x\n",
		 devname, pid, vew, midh, midw);

done:
	ov2640_s_powew(&pwiv->subdev, 0);
	wetuwn wet;
}

static const stwuct v4w2_ctww_ops ov2640_ctww_ops = {
	.s_ctww = ov2640_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops ov2640_subdev_cowe_ops = {
	.wog_status = v4w2_ctww_subdev_wog_status,
	.subscwibe_event = v4w2_ctww_subdev_subscwibe_event,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew	= ov2640_g_wegistew,
	.s_wegistew	= ov2640_s_wegistew,
#endif
	.s_powew	= ov2640_s_powew,
};

static const stwuct v4w2_subdev_pad_ops ov2640_subdev_pad_ops = {
	.enum_mbus_code = ov2640_enum_mbus_code,
	.get_sewection	= ov2640_get_sewection,
	.get_fmt	= ov2640_get_fmt,
	.set_fmt	= ov2640_set_fmt,
};

static const stwuct v4w2_subdev_video_ops ov2640_subdev_video_ops = {
	.s_stweam = ov2640_s_stweam,
};

static const stwuct v4w2_subdev_ops ov2640_subdev_ops = {
	.cowe	= &ov2640_subdev_cowe_ops,
	.pad	= &ov2640_subdev_pad_ops,
	.video	= &ov2640_subdev_video_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops ov2640_intewnaw_ops = {
	.init_state	= ov2640_init_state,
};

static int ov2640_pwobe_dt(stwuct i2c_cwient *cwient,
		stwuct ov2640_pwiv *pwiv)
{
	int wet;

	/* Wequest the weset GPIO deassewted */
	pwiv->wesetb_gpio = devm_gpiod_get_optionaw(&cwient->dev, "wesetb",
			GPIOD_OUT_WOW);

	if (!pwiv->wesetb_gpio)
		dev_dbg(&cwient->dev, "wesetb gpio is not assigned!\n");

	wet = PTW_EWW_OW_ZEWO(pwiv->wesetb_gpio);
	if (wet && wet != -ENOSYS) {
		dev_dbg(&cwient->dev,
			"Ewwow %d whiwe getting wesetb gpio\n", wet);
		wetuwn wet;
	}

	/* Wequest the powew down GPIO assewted */
	pwiv->pwdn_gpio = devm_gpiod_get_optionaw(&cwient->dev, "pwdn",
			GPIOD_OUT_HIGH);

	if (!pwiv->pwdn_gpio)
		dev_dbg(&cwient->dev, "pwdn gpio is not assigned!\n");

	wet = PTW_EWW_OW_ZEWO(pwiv->pwdn_gpio);
	if (wet && wet != -ENOSYS) {
		dev_dbg(&cwient->dev,
			"Ewwow %d whiwe getting pwdn gpio\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * i2c_dwivew functions
 */
static int ov2640_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ov2640_pwiv	*pwiv;
	stwuct i2c_adaptew	*adaptew = cwient->adaptew;
	int			wet;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_eww(&adaptew->dev,
			"OV2640: I2C-Adaptew doesn't suppowt SMBUS\n");
		wetuwn -EIO;
	}

	pwiv = devm_kzawwoc(&cwient->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	if (cwient->dev.of_node) {
		pwiv->cwk = devm_cwk_get_enabwed(&cwient->dev, "xvcwk");
		if (IS_EWW(pwiv->cwk))
			wetuwn PTW_EWW(pwiv->cwk);
	}

	wet = ov2640_pwobe_dt(cwient, pwiv);
	if (wet)
		wetuwn wet;

	pwiv->win = ov2640_sewect_win(SVGA_WIDTH, SVGA_HEIGHT);
	pwiv->cfmt_code = MEDIA_BUS_FMT_UYVY8_2X8;

	v4w2_i2c_subdev_init(&pwiv->subdev, cwient, &ov2640_subdev_ops);
	pwiv->subdev.intewnaw_ops = &ov2640_intewnaw_ops;
	pwiv->subdev.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE |
			      V4W2_SUBDEV_FW_HAS_EVENTS;
	mutex_init(&pwiv->wock);
	v4w2_ctww_handwew_init(&pwiv->hdw, 3);
	pwiv->hdw.wock = &pwiv->wock;
	v4w2_ctww_new_std(&pwiv->hdw, &ov2640_ctww_ops,
			V4W2_CID_VFWIP, 0, 1, 1, 0);
	v4w2_ctww_new_std(&pwiv->hdw, &ov2640_ctww_ops,
			V4W2_CID_HFWIP, 0, 1, 1, 0);
	v4w2_ctww_new_std_menu_items(&pwiv->hdw, &ov2640_ctww_ops,
			V4W2_CID_TEST_PATTEWN,
			AWWAY_SIZE(ov2640_test_pattewn_menu) - 1, 0, 0,
			ov2640_test_pattewn_menu);
	pwiv->subdev.ctww_handwew = &pwiv->hdw;
	if (pwiv->hdw.ewwow) {
		wet = pwiv->hdw.ewwow;
		goto eww_hdw;
	}
	pwiv->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	pwiv->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOW;
	wet = media_entity_pads_init(&pwiv->subdev.entity, 1, &pwiv->pad);
	if (wet < 0)
		goto eww_hdw;

	wet = ov2640_video_pwobe(cwient);
	if (wet < 0)
		goto eww_videopwobe;

	wet = v4w2_async_wegistew_subdev(&pwiv->subdev);
	if (wet < 0)
		goto eww_videopwobe;

	dev_info(&adaptew->dev, "OV2640 Pwobed\n");

	wetuwn 0;

eww_videopwobe:
	media_entity_cweanup(&pwiv->subdev.entity);
eww_hdw:
	v4w2_ctww_handwew_fwee(&pwiv->hdw);
	mutex_destwoy(&pwiv->wock);
	wetuwn wet;
}

static void ov2640_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ov2640_pwiv       *pwiv = to_ov2640(cwient);

	v4w2_async_unwegistew_subdev(&pwiv->subdev);
	v4w2_ctww_handwew_fwee(&pwiv->hdw);
	mutex_destwoy(&pwiv->wock);
	media_entity_cweanup(&pwiv->subdev.entity);
	v4w2_device_unwegistew_subdev(&pwiv->subdev);
}

static const stwuct i2c_device_id ov2640_id[] = {
	{ "ov2640", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ov2640_id);

static const stwuct of_device_id ov2640_of_match[] = {
	{.compatibwe = "ovti,ov2640", },
	{},
};
MODUWE_DEVICE_TABWE(of, ov2640_of_match);

static stwuct i2c_dwivew ov2640_i2c_dwivew = {
	.dwivew = {
		.name = "ov2640",
		.of_match_tabwe = ov2640_of_match,
	},
	.pwobe    = ov2640_pwobe,
	.wemove   = ov2640_wemove,
	.id_tabwe = ov2640_id,
};

moduwe_i2c_dwivew(ov2640_i2c_dwivew);

MODUWE_DESCWIPTION("Dwivew fow Omni Vision 2640 sensow");
MODUWE_AUTHOW("Awbewto Panizzo");
MODUWE_WICENSE("GPW v2");
