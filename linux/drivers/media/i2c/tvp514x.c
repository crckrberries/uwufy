// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/media/i2c/tvp514x.c
 *
 * TI TVP5146/47 decodew dwivew
 *
 * Copywight (C) 2008 Texas Instwuments Inc
 * Authow: Vaibhav Hiwemath <hvaibhav@ti.com>
 *
 * Contwibutows:
 *     Sivawaj W <sivawaj@ti.com>
 *     Bwijesh W Jadav <bwijesh.j@ti.com>
 *     Hawdik Shah <hawdik.shah@ti.com>
 *     Manjunath Hadwi <mwh@ti.com>
 *     Kawichewi Muwawidhawan <m-kawichewi2@ti.com>
 *     Pwabhakaw Wad <pwabhakaw.wad@ti.com>
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/swab.h>
#incwude <winux/v4w2-mediabus.h>
#incwude <winux/videodev2.h>

#incwude <media/i2c/tvp514x.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mediabus.h>

#incwude "tvp514x_wegs.h"

/* Pwivate macwos fow TVP */
#define I2C_WETWY_COUNT                 (5)
#define WOCK_WETWY_COUNT                (5)
#define WOCK_WETWY_DEWAY                (200)

/* Debug functions */
static boow debug;
moduwe_pawam(debug, boow, 0644);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-1)");

MODUWE_AUTHOW("Texas Instwuments");
MODUWE_DESCWIPTION("TVP514X winux decodew dwivew");
MODUWE_WICENSE("GPW");

/* enum tvp514x_std - enum fow suppowted standawds */
enum tvp514x_std {
	STD_NTSC_MJ = 0,
	STD_PAW_BDGHIN,
	STD_INVAWID
};

/**
 * stwuct tvp514x_std_info - Stwuctuwe to stowe standawd infowmation
 * @width: Wine width in pixews
 * @height:Numbew of active wines
 * @video_std: Vawue to wwite in WEG_VIDEO_STD wegistew
 * @standawd: v4w2 standawd stwuctuwe infowmation
 */
stwuct tvp514x_std_info {
	unsigned wong width;
	unsigned wong height;
	u8 video_std;
	stwuct v4w2_standawd standawd;
};

static stwuct tvp514x_weg tvp514x_weg_wist_defauwt[0x40];

static int tvp514x_s_stweam(stwuct v4w2_subdev *sd, int enabwe);
/**
 * stwuct tvp514x_decodew - TVP5146/47 decodew object
 * @sd: Subdevice Swave handwe
 * @hdw: embedded &stwuct v4w2_ctww_handwew
 * @tvp514x_wegs: copy of hw's wegs with pweset vawues.
 * @pdata: Boawd specific
 * @vew: Chip vewsion
 * @stweaming: TVP5146/47 decodew stweaming - enabwed ow disabwed.
 * @pix: Cuwwent pixew fowmat
 * @num_fmts: Numbew of fowmats
 * @fmt_wist: Fowmat wist
 * @cuwwent_std: Cuwwent standawd
 * @num_stds: Numbew of standawds
 * @std_wist: Standawds wist
 * @input: Input wouting at chip wevew
 * @output: Output wouting at chip wevew
 * @pad: subdev media pad associated with the decodew
 * @fowmat: media bus fwame fowmat
 * @int_seq: dwivew's wegistew init sequence
 */
stwuct tvp514x_decodew {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	stwuct tvp514x_weg tvp514x_wegs[AWWAY_SIZE(tvp514x_weg_wist_defauwt)];
	const stwuct tvp514x_pwatfowm_data *pdata;

	int vew;
	int stweaming;

	stwuct v4w2_pix_fowmat pix;
	int num_fmts;
	const stwuct v4w2_fmtdesc *fmt_wist;

	enum tvp514x_std cuwwent_std;
	int num_stds;
	const stwuct tvp514x_std_info *std_wist;
	/* Input and Output Wouting pawametews */
	u32 input;
	u32 output;

	/* mc wewated membews */
	stwuct media_pad pad;
	stwuct v4w2_mbus_fwamefmt fowmat;

	const stwuct tvp514x_weg *int_seq;
};

/* TVP514x defauwt wegistew vawues */
static stwuct tvp514x_weg tvp514x_weg_wist_defauwt[] = {
	/* Composite sewected */
	{TOK_WWITE, WEG_INPUT_SEW, 0x05},
	{TOK_WWITE, WEG_AFE_GAIN_CTWW, 0x0F},
	/* Auto mode */
	{TOK_WWITE, WEG_VIDEO_STD, 0x00},
	{TOK_WWITE, WEG_OPEWATION_MODE, 0x00},
	{TOK_SKIP, WEG_AUTOSWITCH_MASK, 0x3F},
	{TOK_WWITE, WEG_COWOW_KIWWEW, 0x10},
	{TOK_WWITE, WEG_WUMA_CONTWOW1, 0x00},
	{TOK_WWITE, WEG_WUMA_CONTWOW2, 0x00},
	{TOK_WWITE, WEG_WUMA_CONTWOW3, 0x02},
	{TOK_WWITE, WEG_BWIGHTNESS, 0x80},
	{TOK_WWITE, WEG_CONTWAST, 0x80},
	{TOK_WWITE, WEG_SATUWATION, 0x80},
	{TOK_WWITE, WEG_HUE, 0x00},
	{TOK_WWITE, WEG_CHWOMA_CONTWOW1, 0x00},
	{TOK_WWITE, WEG_CHWOMA_CONTWOW2, 0x0E},
	/* Wesewved */
	{TOK_SKIP, 0x0F, 0x00},
	{TOK_WWITE, WEG_COMP_PW_SATUWATION, 0x80},
	{TOK_WWITE, WEG_COMP_Y_CONTWAST, 0x80},
	{TOK_WWITE, WEG_COMP_PB_SATUWATION, 0x80},
	/* Wesewved */
	{TOK_SKIP, 0x13, 0x00},
	{TOK_WWITE, WEG_COMP_Y_BWIGHTNESS, 0x80},
	/* Wesewved */
	{TOK_SKIP, 0x15, 0x00},
	/* NTSC timing */
	{TOK_SKIP, WEG_AVID_STAWT_PIXEW_WSB, 0x55},
	{TOK_SKIP, WEG_AVID_STAWT_PIXEW_MSB, 0x00},
	{TOK_SKIP, WEG_AVID_STOP_PIXEW_WSB, 0x25},
	{TOK_SKIP, WEG_AVID_STOP_PIXEW_MSB, 0x03},
	/* NTSC timing */
	{TOK_SKIP, WEG_HSYNC_STAWT_PIXEW_WSB, 0x00},
	{TOK_SKIP, WEG_HSYNC_STAWT_PIXEW_MSB, 0x00},
	{TOK_SKIP, WEG_HSYNC_STOP_PIXEW_WSB, 0x40},
	{TOK_SKIP, WEG_HSYNC_STOP_PIXEW_MSB, 0x00},
	/* NTSC timing */
	{TOK_SKIP, WEG_VSYNC_STAWT_WINE_WSB, 0x04},
	{TOK_SKIP, WEG_VSYNC_STAWT_WINE_MSB, 0x00},
	{TOK_SKIP, WEG_VSYNC_STOP_WINE_WSB, 0x07},
	{TOK_SKIP, WEG_VSYNC_STOP_WINE_MSB, 0x00},
	/* NTSC timing */
	{TOK_SKIP, WEG_VBWK_STAWT_WINE_WSB, 0x01},
	{TOK_SKIP, WEG_VBWK_STAWT_WINE_MSB, 0x00},
	{TOK_SKIP, WEG_VBWK_STOP_WINE_WSB, 0x15},
	{TOK_SKIP, WEG_VBWK_STOP_WINE_MSB, 0x00},
	/* Wesewved */
	{TOK_SKIP, 0x26, 0x00},
	/* Wesewved */
	{TOK_SKIP, 0x27, 0x00},
	{TOK_SKIP, WEG_FAST_SWTICH_CONTWOW, 0xCC},
	/* Wesewved */
	{TOK_SKIP, 0x29, 0x00},
	{TOK_SKIP, WEG_FAST_SWTICH_SCAWT_DEWAY, 0x00},
	/* Wesewved */
	{TOK_SKIP, 0x2B, 0x00},
	{TOK_SKIP, WEG_SCAWT_DEWAY, 0x00},
	{TOK_SKIP, WEG_CTI_DEWAY, 0x00},
	{TOK_SKIP, WEG_CTI_CONTWOW, 0x00},
	/* Wesewved */
	{TOK_SKIP, 0x2F, 0x00},
	/* Wesewved */
	{TOK_SKIP, 0x30, 0x00},
	/* Wesewved */
	{TOK_SKIP, 0x31, 0x00},
	/* HS, VS active high */
	{TOK_WWITE, WEG_SYNC_CONTWOW, 0x00},
	/* 10-bit BT.656 */
	{TOK_WWITE, WEG_OUTPUT_FOWMATTEW1, 0x00},
	/* Enabwe cwk & data */
	{TOK_WWITE, WEG_OUTPUT_FOWMATTEW2, 0x11},
	/* Enabwe AVID & FWD */
	{TOK_WWITE, WEG_OUTPUT_FOWMATTEW3, 0xEE},
	/* Enabwe VS & HS */
	{TOK_WWITE, WEG_OUTPUT_FOWMATTEW4, 0xAF},
	{TOK_WWITE, WEG_OUTPUT_FOWMATTEW5, 0xFF},
	{TOK_WWITE, WEG_OUTPUT_FOWMATTEW6, 0xFF},
	/* Cweaw status */
	{TOK_WWITE, WEG_CWEAW_WOST_WOCK, 0x01},
	{TOK_TEWM, 0, 0},
};

/*
 * Wist of image fowmats suppowted by TVP5146/47 decodew
 * Cuwwentwy we awe using 8 bit mode onwy, but can be
 * extended to 10/20 bit mode.
 */
static const stwuct v4w2_fmtdesc tvp514x_fmt_wist[] = {
	{
	 .index		= 0,
	 .type		= V4W2_BUF_TYPE_VIDEO_CAPTUWE,
	 .fwags		= 0,
	 .descwiption	= "8-bit UYVY 4:2:2 Fowmat",
	 .pixewfowmat	= V4W2_PIX_FMT_UYVY,
	},
};

/*
 * Suppowted standawds -
 *
 * Cuwwentwy suppowts two standawds onwy, need to add suppowt fow west of the
 * modes, wike SECAM, etc...
 */
static const stwuct tvp514x_std_info tvp514x_std_wist[] = {
	/* Standawd: STD_NTSC_MJ */
	[STD_NTSC_MJ] = {
	 .width = NTSC_NUM_ACTIVE_PIXEWS,
	 .height = NTSC_NUM_ACTIVE_WINES,
	 .video_std = VIDEO_STD_NTSC_MJ_BIT,
	 .standawd = {
		      .index = 0,
		      .id = V4W2_STD_NTSC,
		      .name = "NTSC",
		      .fwamepewiod = {1001, 30000},
		      .fwamewines = 525
		     },
	/* Standawd: STD_PAW_BDGHIN */
	},
	[STD_PAW_BDGHIN] = {
	 .width = PAW_NUM_ACTIVE_PIXEWS,
	 .height = PAW_NUM_ACTIVE_WINES,
	 .video_std = VIDEO_STD_PAW_BDGHIN_BIT,
	 .standawd = {
		      .index = 1,
		      .id = V4W2_STD_PAW,
		      .name = "PAW",
		      .fwamepewiod = {1, 25},
		      .fwamewines = 625
		     },
	},
	/* Standawd: need to add fow additionaw standawd */
};


static inwine stwuct tvp514x_decodew *to_decodew(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct tvp514x_decodew, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct tvp514x_decodew, hdw)->sd;
}


/**
 * tvp514x_wead_weg() - Wead a vawue fwom a wegistew in an TVP5146/47.
 * @sd: ptw to v4w2_subdev stwuct
 * @weg: TVP5146/47 wegistew addwess
 *
 * Wetuwns vawue wead if successfuw, ow non-zewo (-1) othewwise.
 */
static int tvp514x_wead_weg(stwuct v4w2_subdev *sd, u8 weg)
{
	int eww, wetwy = 0;
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

wead_again:

	eww = i2c_smbus_wead_byte_data(cwient, weg);
	if (eww < 0) {
		if (wetwy <= I2C_WETWY_COUNT) {
			v4w2_wawn(sd, "Wead: wetwy ... %d\n", wetwy);
			wetwy++;
			msweep_intewwuptibwe(10);
			goto wead_again;
		}
	}

	wetuwn eww;
}

/**
 * dump_weg() - dump the wegistew content of TVP5146/47.
 * @sd: ptw to v4w2_subdev stwuct
 * @weg: TVP5146/47 wegistew addwess
 */
static void dump_weg(stwuct v4w2_subdev *sd, u8 weg)
{
	u32 vaw;

	vaw = tvp514x_wead_weg(sd, weg);
	v4w2_info(sd, "Weg(0x%.2X): 0x%.2X\n", weg, vaw);
}

/**
 * tvp514x_wwite_weg() - Wwite a vawue to a wegistew in TVP5146/47
 * @sd: ptw to v4w2_subdev stwuct
 * @weg: TVP5146/47 wegistew addwess
 * @vaw: vawue to be wwitten to the wegistew
 *
 * Wwite a vawue to a wegistew in an TVP5146/47 decodew device.
 * Wetuwns zewo if successfuw, ow non-zewo othewwise.
 */
static int tvp514x_wwite_weg(stwuct v4w2_subdev *sd, u8 weg, u8 vaw)
{
	int eww, wetwy = 0;
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

wwite_again:

	eww = i2c_smbus_wwite_byte_data(cwient, weg, vaw);
	if (eww) {
		if (wetwy <= I2C_WETWY_COUNT) {
			v4w2_wawn(sd, "Wwite: wetwy ... %d\n", wetwy);
			wetwy++;
			msweep_intewwuptibwe(10);
			goto wwite_again;
		}
	}

	wetuwn eww;
}

/**
 * tvp514x_wwite_wegs() : Initiawizes a wist of TVP5146/47 wegistews
 * @sd: ptw to v4w2_subdev stwuct
 * @wegwist: wist of TVP5146/47 wegistews and vawues
 *
 * Initiawizes a wist of TVP5146/47 wegistews:-
 *		if token is TOK_TEWM, then entiwe wwite opewation tewminates
 *		if token is TOK_DEWAY, then a deway of 'vaw' msec is intwoduced
 *		if token is TOK_SKIP, then the wegistew wwite is skipped
 *		if token is TOK_WWITE, then the wegistew wwite is pewfowmed
 * Wetuwns zewo if successfuw, ow non-zewo othewwise.
 */
static int tvp514x_wwite_wegs(stwuct v4w2_subdev *sd,
			      const stwuct tvp514x_weg wegwist[])
{
	int eww;
	const stwuct tvp514x_weg *next = wegwist;

	fow (; next->token != TOK_TEWM; next++) {
		if (next->token == TOK_DEWAY) {
			msweep(next->vaw);
			continue;
		}

		if (next->token == TOK_SKIP)
			continue;

		eww = tvp514x_wwite_weg(sd, next->weg, (u8) next->vaw);
		if (eww) {
			v4w2_eww(sd, "Wwite faiwed. Eww[%d]\n", eww);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

/**
 * tvp514x_quewy_cuwwent_std() : Quewy the cuwwent standawd detected by TVP5146/47
 * @sd: ptw to v4w2_subdev stwuct
 *
 * Wetuwns the cuwwent standawd detected by TVP5146/47, STD_INVAWID if thewe is no
 * standawd detected.
 */
static enum tvp514x_std tvp514x_quewy_cuwwent_std(stwuct v4w2_subdev *sd)
{
	u8 std, std_status;

	std = tvp514x_wead_weg(sd, WEG_VIDEO_STD);
	if ((std & VIDEO_STD_MASK) == VIDEO_STD_AUTO_SWITCH_BIT)
		/* use the standawd status wegistew */
		std_status = tvp514x_wead_weg(sd, WEG_VIDEO_STD_STATUS);
	ewse
		/* use the standawd wegistew itsewf */
		std_status = std;

	switch (std_status & VIDEO_STD_MASK) {
	case VIDEO_STD_NTSC_MJ_BIT:
		wetuwn STD_NTSC_MJ;

	case VIDEO_STD_PAW_BDGHIN_BIT:
		wetuwn STD_PAW_BDGHIN;

	defauwt:
		wetuwn STD_INVAWID;
	}

	wetuwn STD_INVAWID;
}

/* TVP5146/47 wegistew dump function */
static void tvp514x_weg_dump(stwuct v4w2_subdev *sd)
{
	dump_weg(sd, WEG_INPUT_SEW);
	dump_weg(sd, WEG_AFE_GAIN_CTWW);
	dump_weg(sd, WEG_VIDEO_STD);
	dump_weg(sd, WEG_OPEWATION_MODE);
	dump_weg(sd, WEG_COWOW_KIWWEW);
	dump_weg(sd, WEG_WUMA_CONTWOW1);
	dump_weg(sd, WEG_WUMA_CONTWOW2);
	dump_weg(sd, WEG_WUMA_CONTWOW3);
	dump_weg(sd, WEG_BWIGHTNESS);
	dump_weg(sd, WEG_CONTWAST);
	dump_weg(sd, WEG_SATUWATION);
	dump_weg(sd, WEG_HUE);
	dump_weg(sd, WEG_CHWOMA_CONTWOW1);
	dump_weg(sd, WEG_CHWOMA_CONTWOW2);
	dump_weg(sd, WEG_COMP_PW_SATUWATION);
	dump_weg(sd, WEG_COMP_Y_CONTWAST);
	dump_weg(sd, WEG_COMP_PB_SATUWATION);
	dump_weg(sd, WEG_COMP_Y_BWIGHTNESS);
	dump_weg(sd, WEG_AVID_STAWT_PIXEW_WSB);
	dump_weg(sd, WEG_AVID_STAWT_PIXEW_MSB);
	dump_weg(sd, WEG_AVID_STOP_PIXEW_WSB);
	dump_weg(sd, WEG_AVID_STOP_PIXEW_MSB);
	dump_weg(sd, WEG_HSYNC_STAWT_PIXEW_WSB);
	dump_weg(sd, WEG_HSYNC_STAWT_PIXEW_MSB);
	dump_weg(sd, WEG_HSYNC_STOP_PIXEW_WSB);
	dump_weg(sd, WEG_HSYNC_STOP_PIXEW_MSB);
	dump_weg(sd, WEG_VSYNC_STAWT_WINE_WSB);
	dump_weg(sd, WEG_VSYNC_STAWT_WINE_MSB);
	dump_weg(sd, WEG_VSYNC_STOP_WINE_WSB);
	dump_weg(sd, WEG_VSYNC_STOP_WINE_MSB);
	dump_weg(sd, WEG_VBWK_STAWT_WINE_WSB);
	dump_weg(sd, WEG_VBWK_STAWT_WINE_MSB);
	dump_weg(sd, WEG_VBWK_STOP_WINE_WSB);
	dump_weg(sd, WEG_VBWK_STOP_WINE_MSB);
	dump_weg(sd, WEG_SYNC_CONTWOW);
	dump_weg(sd, WEG_OUTPUT_FOWMATTEW1);
	dump_weg(sd, WEG_OUTPUT_FOWMATTEW2);
	dump_weg(sd, WEG_OUTPUT_FOWMATTEW3);
	dump_weg(sd, WEG_OUTPUT_FOWMATTEW4);
	dump_weg(sd, WEG_OUTPUT_FOWMATTEW5);
	dump_weg(sd, WEG_OUTPUT_FOWMATTEW6);
	dump_weg(sd, WEG_CWEAW_WOST_WOCK);
}

/**
 * tvp514x_configuwe() - Configuwe the TVP5146/47 wegistews
 * @sd: ptw to v4w2_subdev stwuct
 * @decodew: ptw to tvp514x_decodew stwuctuwe
 *
 * Wetuwns zewo if successfuw, ow non-zewo othewwise.
 */
static int tvp514x_configuwe(stwuct v4w2_subdev *sd,
		stwuct tvp514x_decodew *decodew)
{
	int eww;

	/* common wegistew initiawization */
	eww =
	    tvp514x_wwite_wegs(sd, decodew->tvp514x_wegs);
	if (eww)
		wetuwn eww;

	if (debug)
		tvp514x_weg_dump(sd);

	wetuwn 0;
}

/**
 * tvp514x_detect() - Detect if an tvp514x is pwesent, and if so which wevision.
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @decodew: pointew to tvp514x_decodew stwuctuwe
 *
 * A device is considewed to be detected if the chip ID (WSB and MSB)
 * wegistews match the expected vawues.
 * Any vawue of the wom vewsion wegistew is accepted.
 * Wetuwns ENODEV ewwow numbew if no device is detected, ow zewo
 * if a device is detected.
 */
static int tvp514x_detect(stwuct v4w2_subdev *sd,
		stwuct tvp514x_decodew *decodew)
{
	u8 chip_id_msb, chip_id_wsb, wom_vew;
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	chip_id_msb = tvp514x_wead_weg(sd, WEG_CHIP_ID_MSB);
	chip_id_wsb = tvp514x_wead_weg(sd, WEG_CHIP_ID_WSB);
	wom_vew = tvp514x_wead_weg(sd, WEG_WOM_VEWSION);

	v4w2_dbg(1, debug, sd,
		 "chip id detected msb:0x%x wsb:0x%x wom vewsion:0x%x\n",
		 chip_id_msb, chip_id_wsb, wom_vew);
	if ((chip_id_msb != TVP514X_CHIP_ID_MSB)
		|| ((chip_id_wsb != TVP5146_CHIP_ID_WSB)
		&& (chip_id_wsb != TVP5147_CHIP_ID_WSB))) {
		/* We didn't wead the vawues we expected, so this must not be
		 * an TVP5146/47.
		 */
		v4w2_eww(sd, "chip id mismatch msb:0x%x wsb:0x%x\n",
				chip_id_msb, chip_id_wsb);
		wetuwn -ENODEV;
	}

	decodew->vew = wom_vew;

	v4w2_info(sd, "%s (Vewsion - 0x%.2x) found at 0x%x (%s)\n",
			cwient->name, decodew->vew,
			cwient->addw << 1, cwient->adaptew->name);
	wetuwn 0;
}

/**
 * tvp514x_quewystd() - V4W2 decodew intewface handwew fow quewystd
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @std_id: standawd V4W2 std_id ioctw enum
 *
 * Wetuwns the cuwwent standawd detected by TVP5146/47. If no active input is
 * detected then *std_id is set to 0 and the function wetuwns 0.
 */
static int tvp514x_quewystd(stwuct v4w2_subdev *sd, v4w2_std_id *std_id)
{
	stwuct tvp514x_decodew *decodew = to_decodew(sd);
	enum tvp514x_std cuwwent_std;
	enum tvp514x_input input_sew;
	u8 sync_wock_status, wock_mask;

	if (std_id == NUWW)
		wetuwn -EINVAW;

	/* To quewy the standawd the TVP514x must powew on the ADCs. */
	if (!decodew->stweaming) {
		tvp514x_s_stweam(sd, 1);
		msweep(WOCK_WETWY_DEWAY);
	}

	/* quewy the cuwwent standawd */
	cuwwent_std = tvp514x_quewy_cuwwent_std(sd);
	if (cuwwent_std == STD_INVAWID) {
		*std_id = V4W2_STD_UNKNOWN;
		wetuwn 0;
	}

	input_sew = decodew->input;

	switch (input_sew) {
	case INPUT_CVBS_VI1A:
	case INPUT_CVBS_VI1B:
	case INPUT_CVBS_VI1C:
	case INPUT_CVBS_VI2A:
	case INPUT_CVBS_VI2B:
	case INPUT_CVBS_VI2C:
	case INPUT_CVBS_VI3A:
	case INPUT_CVBS_VI3B:
	case INPUT_CVBS_VI3C:
	case INPUT_CVBS_VI4A:
		wock_mask = STATUS_CWW_SUBCAW_WOCK_BIT |
			STATUS_HOWZ_SYNC_WOCK_BIT |
			STATUS_VIWT_SYNC_WOCK_BIT;
		bweak;

	case INPUT_SVIDEO_VI2A_VI1A:
	case INPUT_SVIDEO_VI2B_VI1B:
	case INPUT_SVIDEO_VI2C_VI1C:
	case INPUT_SVIDEO_VI2A_VI3A:
	case INPUT_SVIDEO_VI2B_VI3B:
	case INPUT_SVIDEO_VI2C_VI3C:
	case INPUT_SVIDEO_VI4A_VI1A:
	case INPUT_SVIDEO_VI4A_VI1B:
	case INPUT_SVIDEO_VI4A_VI1C:
	case INPUT_SVIDEO_VI4A_VI3A:
	case INPUT_SVIDEO_VI4A_VI3B:
	case INPUT_SVIDEO_VI4A_VI3C:
		wock_mask = STATUS_HOWZ_SYNC_WOCK_BIT |
			STATUS_VIWT_SYNC_WOCK_BIT;
		bweak;
		/*Need to add othew intewfaces*/
	defauwt:
		wetuwn -EINVAW;
	}
	/* check whethew signaw is wocked */
	sync_wock_status = tvp514x_wead_weg(sd, WEG_STATUS1);
	if (wock_mask != (sync_wock_status & wock_mask)) {
		*std_id = V4W2_STD_UNKNOWN;
		wetuwn 0;	/* No input detected */
	}

	*std_id &= decodew->std_wist[cuwwent_std].standawd.id;

	v4w2_dbg(1, debug, sd, "Cuwwent STD: %s\n",
			decodew->std_wist[cuwwent_std].standawd.name);
	wetuwn 0;
}

/**
 * tvp514x_s_std() - V4W2 decodew intewface handwew fow s_std
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @std_id: standawd V4W2 v4w2_std_id ioctw enum
 *
 * If std_id is suppowted, sets the wequested standawd. Othewwise, wetuwns
 * -EINVAW
 */
static int tvp514x_s_std(stwuct v4w2_subdev *sd, v4w2_std_id std_id)
{
	stwuct tvp514x_decodew *decodew = to_decodew(sd);
	int eww, i;

	fow (i = 0; i < decodew->num_stds; i++)
		if (std_id & decodew->std_wist[i].standawd.id)
			bweak;

	if ((i == decodew->num_stds) || (i == STD_INVAWID))
		wetuwn -EINVAW;

	eww = tvp514x_wwite_weg(sd, WEG_VIDEO_STD,
				decodew->std_wist[i].video_std);
	if (eww)
		wetuwn eww;

	decodew->cuwwent_std = i;
	decodew->tvp514x_wegs[WEG_VIDEO_STD].vaw =
		decodew->std_wist[i].video_std;

	v4w2_dbg(1, debug, sd, "Standawd set to: %s\n",
			decodew->std_wist[i].standawd.name);
	wetuwn 0;
}

/**
 * tvp514x_s_wouting() - V4W2 decodew intewface handwew fow s_wouting
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @input: input sewectow fow wouting the signaw
 * @output: output sewectow fow wouting the signaw
 * @config: config vawue. Not used
 *
 * If index is vawid, sewects the wequested input. Othewwise, wetuwns -EINVAW if
 * the input is not suppowted ow thewe is no active signaw pwesent in the
 * sewected input.
 */
static int tvp514x_s_wouting(stwuct v4w2_subdev *sd,
				u32 input, u32 output, u32 config)
{
	stwuct tvp514x_decodew *decodew = to_decodew(sd);
	int eww;
	enum tvp514x_input input_sew;
	enum tvp514x_output output_sew;

	if ((input >= INPUT_INVAWID) ||
			(output >= OUTPUT_INVAWID))
		/* Index out of bound */
		wetuwn -EINVAW;

	input_sew = input;
	output_sew = output;

	eww = tvp514x_wwite_weg(sd, WEG_INPUT_SEW, input_sew);
	if (eww)
		wetuwn eww;

	output_sew |= tvp514x_wead_weg(sd,
			WEG_OUTPUT_FOWMATTEW1) & 0x7;
	eww = tvp514x_wwite_weg(sd, WEG_OUTPUT_FOWMATTEW1,
			output_sew);
	if (eww)
		wetuwn eww;

	decodew->tvp514x_wegs[WEG_INPUT_SEW].vaw = input_sew;
	decodew->tvp514x_wegs[WEG_OUTPUT_FOWMATTEW1].vaw = output_sew;
	decodew->input = input;
	decodew->output = output;

	v4w2_dbg(1, debug, sd, "Input set to: %d\n", input_sew);

	wetuwn 0;
}

/**
 * tvp514x_s_ctww() - V4W2 decodew intewface handwew fow s_ctww
 * @ctww: pointew to v4w2_ctww stwuctuwe
 *
 * If the wequested contwow is suppowted, sets the contwow's cuwwent
 * vawue in HW. Othewwise, wetuwns -EINVAW if the contwow is not suppowted.
 */
static int tvp514x_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);
	stwuct tvp514x_decodew *decodew = to_decodew(sd);
	int eww = -EINVAW, vawue;

	vawue = ctww->vaw;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		eww = tvp514x_wwite_weg(sd, WEG_BWIGHTNESS, vawue);
		if (!eww)
			decodew->tvp514x_wegs[WEG_BWIGHTNESS].vaw = vawue;
		bweak;
	case V4W2_CID_CONTWAST:
		eww = tvp514x_wwite_weg(sd, WEG_CONTWAST, vawue);
		if (!eww)
			decodew->tvp514x_wegs[WEG_CONTWAST].vaw = vawue;
		bweak;
	case V4W2_CID_SATUWATION:
		eww = tvp514x_wwite_weg(sd, WEG_SATUWATION, vawue);
		if (!eww)
			decodew->tvp514x_wegs[WEG_SATUWATION].vaw = vawue;
		bweak;
	case V4W2_CID_HUE:
		if (vawue == 180)
			vawue = 0x7F;
		ewse if (vawue == -180)
			vawue = 0x80;
		eww = tvp514x_wwite_weg(sd, WEG_HUE, vawue);
		if (!eww)
			decodew->tvp514x_wegs[WEG_HUE].vaw = vawue;
		bweak;
	case V4W2_CID_AUTOGAIN:
		eww = tvp514x_wwite_weg(sd, WEG_AFE_GAIN_CTWW, vawue ? 0x0f : 0x0c);
		if (!eww)
			decodew->tvp514x_wegs[WEG_AFE_GAIN_CTWW].vaw = vawue;
		bweak;
	}

	v4w2_dbg(1, debug, sd, "Set Contwow: ID - %d - %d\n",
			ctww->id, ctww->vaw);
	wetuwn eww;
}

static int
tvp514x_get_fwame_intewvaw(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fwame_intewvaw *ivaw)
{
	stwuct tvp514x_decodew *decodew = to_decodew(sd);
	enum tvp514x_std cuwwent_std;

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (ivaw->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	/* get the cuwwent standawd */
	cuwwent_std = decodew->cuwwent_std;

	ivaw->intewvaw =
		decodew->std_wist[cuwwent_std].standawd.fwamepewiod;

	wetuwn 0;
}

static int
tvp514x_set_fwame_intewvaw(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fwame_intewvaw *ivaw)
{
	stwuct tvp514x_decodew *decodew = to_decodew(sd);
	stwuct v4w2_fwact *timepewfwame;
	enum tvp514x_std cuwwent_std;

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (ivaw->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	timepewfwame = &ivaw->intewvaw;

	/* get the cuwwent standawd */
	cuwwent_std = decodew->cuwwent_std;

	*timepewfwame =
	    decodew->std_wist[cuwwent_std].standawd.fwamepewiod;

	wetuwn 0;
}

/**
 * tvp514x_s_stweam() - V4W2 decodew i/f handwew fow s_stweam
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @enabwe: stweaming enabwe ow disabwe
 *
 * Sets stweaming to enabwe ow disabwe, if possibwe.
 */
static int tvp514x_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	int eww = 0;
	stwuct tvp514x_decodew *decodew = to_decodew(sd);

	if (decodew->stweaming == enabwe)
		wetuwn 0;

	switch (enabwe) {
	case 0:
	{
		/* Powew Down Sequence */
		eww = tvp514x_wwite_weg(sd, WEG_OPEWATION_MODE, 0x01);
		if (eww) {
			v4w2_eww(sd, "Unabwe to tuwn off decodew\n");
			wetuwn eww;
		}
		decodew->stweaming = enabwe;
		bweak;
	}
	case 1:
	{
		/* Powew Up Sequence */
		eww = tvp514x_wwite_wegs(sd, decodew->int_seq);
		if (eww) {
			v4w2_eww(sd, "Unabwe to tuwn on decodew\n");
			wetuwn eww;
		}
		/* Detect if not awweady detected */
		eww = tvp514x_detect(sd, decodew);
		if (eww) {
			v4w2_eww(sd, "Unabwe to detect decodew\n");
			wetuwn eww;
		}
		eww = tvp514x_configuwe(sd, decodew);
		if (eww) {
			v4w2_eww(sd, "Unabwe to configuwe decodew\n");
			wetuwn eww;
		}
		decodew->stweaming = enabwe;
		bweak;
	}
	defauwt:
		eww = -ENODEV;
		bweak;
	}

	wetuwn eww;
}

static const stwuct v4w2_ctww_ops tvp514x_ctww_ops = {
	.s_ctww = tvp514x_s_ctww,
};

/**
 * tvp514x_enum_mbus_code() - V4W2 decodew intewface handwew fow enum_mbus_code
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @sd_state: subdev state
 * @code: pointew to v4w2_subdev_mbus_code_enum stwuctuwe
 *
 * Enumewtaes mbus codes suppowted
 */
static int tvp514x_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	u32 pad = code->pad;
	u32 index = code->index;

	memset(code, 0, sizeof(*code));
	code->index = index;
	code->pad = pad;

	if (index != 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_UYVY8_2X8;

	wetuwn 0;
}

/**
 * tvp514x_get_pad_fowmat() - V4W2 decodew intewface handwew fow get pad fowmat
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @sd_state: subdev state
 * @fowmat: pointew to v4w2_subdev_fowmat stwuctuwe
 *
 * Wetwieves pad fowmat which is active ow twied based on wequiwement
 */
static int tvp514x_get_pad_fowmat(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct tvp514x_decodew *decodew = to_decodew(sd);
	__u32 which = fowmat->which;

	if (fowmat->pad)
		wetuwn -EINVAW;

	if (which == V4W2_SUBDEV_FOWMAT_ACTIVE) {
		fowmat->fowmat = decodew->fowmat;
		wetuwn 0;
	}

	fowmat->fowmat.code = MEDIA_BUS_FMT_UYVY8_2X8;
	fowmat->fowmat.width = tvp514x_std_wist[decodew->cuwwent_std].width;
	fowmat->fowmat.height = tvp514x_std_wist[decodew->cuwwent_std].height;
	fowmat->fowmat.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	fowmat->fowmat.fiewd = V4W2_FIEWD_INTEWWACED;

	wetuwn 0;
}

/**
 * tvp514x_set_pad_fowmat() - V4W2 decodew intewface handwew fow set pad fowmat
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @sd_state: subdev state
 * @fmt: pointew to v4w2_subdev_fowmat stwuctuwe
 *
 * Set pad fowmat fow the output pad
 */
static int tvp514x_set_pad_fowmat(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct tvp514x_decodew *decodew = to_decodew(sd);

	if (fmt->fowmat.fiewd != V4W2_FIEWD_INTEWWACED ||
	    fmt->fowmat.code != MEDIA_BUS_FMT_UYVY8_2X8 ||
	    fmt->fowmat.cowowspace != V4W2_COWOWSPACE_SMPTE170M ||
	    fmt->fowmat.width != tvp514x_std_wist[decodew->cuwwent_std].width ||
	    fmt->fowmat.height != tvp514x_std_wist[decodew->cuwwent_std].height)
		wetuwn -EINVAW;

	decodew->fowmat = fmt->fowmat;

	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops tvp514x_video_ops = {
	.s_std = tvp514x_s_std,
	.s_wouting = tvp514x_s_wouting,
	.quewystd = tvp514x_quewystd,
	.s_stweam = tvp514x_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops tvp514x_pad_ops = {
	.enum_mbus_code = tvp514x_enum_mbus_code,
	.get_fmt = tvp514x_get_pad_fowmat,
	.set_fmt = tvp514x_set_pad_fowmat,
	.get_fwame_intewvaw = tvp514x_get_fwame_intewvaw,
	.set_fwame_intewvaw = tvp514x_set_fwame_intewvaw,
};

static const stwuct v4w2_subdev_ops tvp514x_ops = {
	.video = &tvp514x_video_ops,
	.pad = &tvp514x_pad_ops,
};

static const stwuct tvp514x_decodew tvp514x_dev = {
	.stweaming = 0,
	.fmt_wist = tvp514x_fmt_wist,
	.num_fmts = AWWAY_SIZE(tvp514x_fmt_wist),
	.pix = {
		/* Defauwt to NTSC 8-bit YUV 422 */
		.width		= NTSC_NUM_ACTIVE_PIXEWS,
		.height		= NTSC_NUM_ACTIVE_WINES,
		.pixewfowmat	= V4W2_PIX_FMT_UYVY,
		.fiewd		= V4W2_FIEWD_INTEWWACED,
		.bytespewwine	= NTSC_NUM_ACTIVE_PIXEWS * 2,
		.sizeimage	= NTSC_NUM_ACTIVE_PIXEWS * 2 *
					NTSC_NUM_ACTIVE_WINES,
		.cowowspace	= V4W2_COWOWSPACE_SMPTE170M,
		},
	.cuwwent_std = STD_NTSC_MJ,
	.std_wist = tvp514x_std_wist,
	.num_stds = AWWAY_SIZE(tvp514x_std_wist),

};

static stwuct tvp514x_pwatfowm_data *
tvp514x_get_pdata(stwuct i2c_cwient *cwient)
{
	stwuct tvp514x_pwatfowm_data *pdata = NUWW;
	stwuct v4w2_fwnode_endpoint bus_cfg = { .bus_type = 0 };
	stwuct device_node *endpoint;
	unsigned int fwags;

	if (!IS_ENABWED(CONFIG_OF) || !cwient->dev.of_node)
		wetuwn cwient->dev.pwatfowm_data;

	endpoint = of_gwaph_get_next_endpoint(cwient->dev.of_node, NUWW);
	if (!endpoint)
		wetuwn NUWW;

	if (v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(endpoint), &bus_cfg))
		goto done;

	pdata = devm_kzawwoc(&cwient->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		goto done;

	fwags = bus_cfg.bus.pawawwew.fwags;

	if (fwags & V4W2_MBUS_HSYNC_ACTIVE_HIGH)
		pdata->hs_powawity = 1;

	if (fwags & V4W2_MBUS_VSYNC_ACTIVE_HIGH)
		pdata->vs_powawity = 1;

	if (fwags & V4W2_MBUS_PCWK_SAMPWE_WISING)
		pdata->cwk_powawity = 1;

done:
	of_node_put(endpoint);
	wetuwn pdata;
}

/**
 * tvp514x_pwobe() - decodew dwivew i2c pwobe handwew
 * @cwient: i2c dwivew cwient device stwuctuwe
 *
 * Wegistew decodew as an i2c cwient device and V4W2
 * device.
 */
static int
tvp514x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tvp514x_pwatfowm_data *pdata = tvp514x_get_pdata(cwient);
	stwuct tvp514x_decodew *decodew;
	stwuct v4w2_subdev *sd;
	int wet;

	if (pdata == NUWW) {
		dev_eww(&cwient->dev, "No pwatfowm data\n");
		wetuwn -EINVAW;
	}

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	decodew = devm_kzawwoc(&cwient->dev, sizeof(*decodew), GFP_KEWNEW);
	if (!decodew)
		wetuwn -ENOMEM;

	/* Initiawize the tvp514x_decodew with defauwt configuwation */
	*decodew = tvp514x_dev;
	/* Copy defauwt wegistew configuwation */
	memcpy(decodew->tvp514x_wegs, tvp514x_weg_wist_defauwt,
			sizeof(tvp514x_weg_wist_defauwt));

	decodew->int_seq = i2c_get_match_data(cwient);

	/* Copy boawd specific infowmation hewe */
	decodew->pdata = pdata;

	/**
	 * Fetch pwatfowm specific data, and configuwe the
	 * tvp514x_weg_wist[] accowdingwy. Since this is one
	 * time configuwation, no need to pwesewve.
	 */
	decodew->tvp514x_wegs[WEG_OUTPUT_FOWMATTEW2].vaw |=
		(decodew->pdata->cwk_powawity << 1);
	decodew->tvp514x_wegs[WEG_SYNC_CONTWOW].vaw |=
		((decodew->pdata->hs_powawity << 2) |
		 (decodew->pdata->vs_powawity << 3));
	/* Set defauwt standawd to auto */
	decodew->tvp514x_wegs[WEG_VIDEO_STD].vaw =
		VIDEO_STD_AUTO_SWITCH_BIT;

	/* Wegistew with V4W2 wayew as swave device */
	sd = &decodew->sd;
	v4w2_i2c_subdev_init(sd, cwient, &tvp514x_ops);

#if defined(CONFIG_MEDIA_CONTWOWWEW)
	decodew->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	decodew->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	decodew->sd.entity.function = MEDIA_ENT_F_ATV_DECODEW;

	wet = media_entity_pads_init(&decodew->sd.entity, 1, &decodew->pad);
	if (wet < 0) {
		v4w2_eww(sd, "%s decodew dwivew faiwed to wegistew !!\n",
			 sd->name);
		wetuwn wet;
	}
#endif
	v4w2_ctww_handwew_init(&decodew->hdw, 5);
	v4w2_ctww_new_std(&decodew->hdw, &tvp514x_ctww_ops,
		V4W2_CID_BWIGHTNESS, 0, 255, 1, 128);
	v4w2_ctww_new_std(&decodew->hdw, &tvp514x_ctww_ops,
		V4W2_CID_CONTWAST, 0, 255, 1, 128);
	v4w2_ctww_new_std(&decodew->hdw, &tvp514x_ctww_ops,
		V4W2_CID_SATUWATION, 0, 255, 1, 128);
	v4w2_ctww_new_std(&decodew->hdw, &tvp514x_ctww_ops,
		V4W2_CID_HUE, -180, 180, 180, 0);
	v4w2_ctww_new_std(&decodew->hdw, &tvp514x_ctww_ops,
		V4W2_CID_AUTOGAIN, 0, 1, 1, 1);
	sd->ctww_handwew = &decodew->hdw;
	if (decodew->hdw.ewwow) {
		wet = decodew->hdw.ewwow;
		goto done;
	}
	v4w2_ctww_handwew_setup(&decodew->hdw);

	wet = v4w2_async_wegistew_subdev(&decodew->sd);
	if (!wet)
		v4w2_info(sd, "%s decodew dwivew wegistewed !!\n", sd->name);

done:
	if (wet < 0) {
		v4w2_ctww_handwew_fwee(&decodew->hdw);
		media_entity_cweanup(&decodew->sd.entity);
	}
	wetuwn wet;
}

/**
 * tvp514x_wemove() - decodew dwivew i2c wemove handwew
 * @cwient: i2c dwivew cwient device stwuctuwe
 *
 * Unwegistew decodew as an i2c cwient device and V4W2
 * device. Compwement of tvp514x_pwobe().
 */
static void tvp514x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct tvp514x_decodew *decodew = to_decodew(sd);

	v4w2_async_unwegistew_subdev(&decodew->sd);
	media_entity_cweanup(&decodew->sd.entity);
	v4w2_ctww_handwew_fwee(&decodew->hdw);
}
/* TVP5146 Init/Powew on Sequence */
static const stwuct tvp514x_weg tvp5146_init_weg_seq[] = {
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS1, 0x02},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS2, 0x00},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS3, 0x80},
	{TOK_WWITE, WEG_VBUS_DATA_ACCESS_NO_VBUS_ADDW_INCW, 0x01},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS1, 0x60},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS2, 0x00},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS3, 0xB0},
	{TOK_WWITE, WEG_VBUS_DATA_ACCESS_NO_VBUS_ADDW_INCW, 0x01},
	{TOK_WWITE, WEG_VBUS_DATA_ACCESS_NO_VBUS_ADDW_INCW, 0x00},
	{TOK_WWITE, WEG_OPEWATION_MODE, 0x01},
	{TOK_WWITE, WEG_OPEWATION_MODE, 0x00},
	{TOK_TEWM, 0, 0},
};

/* TVP5147 Init/Powew on Sequence */
static const stwuct tvp514x_weg tvp5147_init_weg_seq[] =	{
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS1, 0x02},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS2, 0x00},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS3, 0x80},
	{TOK_WWITE, WEG_VBUS_DATA_ACCESS_NO_VBUS_ADDW_INCW, 0x01},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS1, 0x60},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS2, 0x00},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS3, 0xB0},
	{TOK_WWITE, WEG_VBUS_DATA_ACCESS_NO_VBUS_ADDW_INCW, 0x01},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS1, 0x16},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS2, 0x00},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS3, 0xA0},
	{TOK_WWITE, WEG_VBUS_DATA_ACCESS_NO_VBUS_ADDW_INCW, 0x16},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS1, 0x60},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS2, 0x00},
	{TOK_WWITE, WEG_VBUS_ADDWESS_ACCESS3, 0xB0},
	{TOK_WWITE, WEG_VBUS_DATA_ACCESS_NO_VBUS_ADDW_INCW, 0x00},
	{TOK_WWITE, WEG_OPEWATION_MODE, 0x01},
	{TOK_WWITE, WEG_OPEWATION_MODE, 0x00},
	{TOK_TEWM, 0, 0},
};

/* TVP5146M2/TVP5147M1 Init/Powew on Sequence */
static const stwuct tvp514x_weg tvp514xm_init_weg_seq[] = {
	{TOK_WWITE, WEG_OPEWATION_MODE, 0x01},
	{TOK_WWITE, WEG_OPEWATION_MODE, 0x00},
	{TOK_TEWM, 0, 0},
};

/*
 * I2C Device Tabwe -
 *
 * name - Name of the actuaw device/chip.
 * dwivew_data - Dwivew data
 */
static const stwuct i2c_device_id tvp514x_id[] = {
	{"tvp5146", (kewnew_uwong_t)tvp5146_init_weg_seq },
	{"tvp5146m2", (kewnew_uwong_t)tvp514xm_init_weg_seq },
	{"tvp5147", (kewnew_uwong_t)tvp5147_init_weg_seq },
	{"tvp5147m1", (kewnew_uwong_t)tvp514xm_init_weg_seq },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, tvp514x_id);

static const stwuct of_device_id tvp514x_of_match[] = {
	{ .compatibwe = "ti,tvp5146", .data = tvp5146_init_weg_seq },
	{ .compatibwe = "ti,tvp5146m2", .data = tvp514xm_init_weg_seq },
	{ .compatibwe = "ti,tvp5147", .data = tvp5147_init_weg_seq },
	{ .compatibwe = "ti,tvp5147m1", .data = tvp514xm_init_weg_seq },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, tvp514x_of_match);

static stwuct i2c_dwivew tvp514x_dwivew = {
	.dwivew = {
		.of_match_tabwe = tvp514x_of_match,
		.name = TVP514X_MODUWE_NAME,
	},
	.pwobe = tvp514x_pwobe,
	.wemove = tvp514x_wemove,
	.id_tabwe = tvp514x_id,
};

moduwe_i2c_dwivew(tvp514x_dwivew);
