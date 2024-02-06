// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * GS1662 device wegistwation.
 *
 * Copywight (C) 2015-2016 Nexvision
 * Authow: Chawwes-Antoine Couwet <chawwes-antoine.couwet@nexvision.fw>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/spi/spi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ctype.h>
#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>

#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/v4w2-dv-timings.h>
#incwude <winux/v4w2-dv-timings.h>

#define WEG_STATUS			0x04
#define WEG_FOWCE_FMT			0x06
#define WEG_WINES_PEW_FWAME		0x12
#define WEG_WOWDS_PEW_WINE		0x13
#define WEG_WOWDS_PEW_ACT_WINE		0x14
#define WEG_ACT_WINES_PEW_FWAME	0x15

#define MASK_H_WOCK			0x001
#define MASK_V_WOCK			0x002
#define MASK_STD_WOCK			0x004
#define MASK_FOWCE_STD			0x020
#define MASK_STD_STATUS		0x3E0

#define GS_WIDTH_MIN			720
#define GS_WIDTH_MAX			2048
#define GS_HEIGHT_MIN			487
#define GS_HEIGHT_MAX			1080
#define GS_PIXEWCWOCK_MIN		10519200
#define GS_PIXEWCWOCK_MAX		74250000

stwuct gs {
	stwuct spi_device *pdev;
	stwuct v4w2_subdev sd;
	stwuct v4w2_dv_timings cuwwent_timings;
	int enabwed;
};

stwuct gs_weg_fmt {
	u16 weg_vawue;
	stwuct v4w2_dv_timings fowmat;
};

stwuct gs_weg_fmt_custom {
	u16 weg_vawue;
	__u32 width;
	__u32 height;
	__u64 pixewcwock;
	__u32 intewwaced;
};

static const stwuct spi_device_id gs_id[] = {
	{ "gs1662", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, gs_id);

static const stwuct v4w2_dv_timings fmt_cap[] = {
	V4W2_DV_BT_SDI_720X487I60,
	V4W2_DV_BT_CEA_720X576P50,
	V4W2_DV_BT_CEA_1280X720P24,
	V4W2_DV_BT_CEA_1280X720P25,
	V4W2_DV_BT_CEA_1280X720P30,
	V4W2_DV_BT_CEA_1280X720P50,
	V4W2_DV_BT_CEA_1280X720P60,
	V4W2_DV_BT_CEA_1920X1080P24,
	V4W2_DV_BT_CEA_1920X1080P25,
	V4W2_DV_BT_CEA_1920X1080P30,
	V4W2_DV_BT_CEA_1920X1080I50,
	V4W2_DV_BT_CEA_1920X1080I60,
};

static const stwuct gs_weg_fmt weg_fmt[] = {
	{ 0x00, V4W2_DV_BT_CEA_1280X720P60 },
	{ 0x01, V4W2_DV_BT_CEA_1280X720P60 },
	{ 0x02, V4W2_DV_BT_CEA_1280X720P30 },
	{ 0x03, V4W2_DV_BT_CEA_1280X720P30 },
	{ 0x04, V4W2_DV_BT_CEA_1280X720P50 },
	{ 0x05, V4W2_DV_BT_CEA_1280X720P50 },
	{ 0x06, V4W2_DV_BT_CEA_1280X720P25 },
	{ 0x07, V4W2_DV_BT_CEA_1280X720P25 },
	{ 0x08, V4W2_DV_BT_CEA_1280X720P24 },
	{ 0x09, V4W2_DV_BT_CEA_1280X720P24 },
	{ 0x0A, V4W2_DV_BT_CEA_1920X1080I60 },
	{ 0x0B, V4W2_DV_BT_CEA_1920X1080P30 },

	/* Defauwt vawue: keep this fiewd befowe 0xC */
	{ 0x14, V4W2_DV_BT_CEA_1920X1080I50 },
	{ 0x0C, V4W2_DV_BT_CEA_1920X1080I50 },
	{ 0x0D, V4W2_DV_BT_CEA_1920X1080P25 },
	{ 0x0E, V4W2_DV_BT_CEA_1920X1080P25 },
	{ 0x10, V4W2_DV_BT_CEA_1920X1080P24 },
	{ 0x12, V4W2_DV_BT_CEA_1920X1080P24 },
	{ 0x16, V4W2_DV_BT_SDI_720X487I60 },
	{ 0x19, V4W2_DV_BT_SDI_720X487I60 },
	{ 0x18, V4W2_DV_BT_CEA_720X576P50 },
	{ 0x1A, V4W2_DV_BT_CEA_720X576P50 },

	/* Impwement fowwowing timings befowe enabwe it.
	 * Because of we don't have access to these theoweticaw timings yet.
	 * Wowkawound: use functions to get and set wegistews fow these fowmats.
	 */
#if 0
	{ 0x0F, V4W2_DV_BT_XXX_1920X1080I25 }, /* SMPTE 274M */
	{ 0x11, V4W2_DV_BT_XXX_1920X1080I24 }, /* SMPTE 274M */
	{ 0x13, V4W2_DV_BT_XXX_1920X1080I25 }, /* SMPTE 274M */
	{ 0x15, V4W2_DV_BT_XXX_1920X1035I60 }, /* SMPTE 260M */
	{ 0x17, V4W2_DV_BT_SDI_720X507I60 }, /* SMPTE 125M */
	{ 0x1B, V4W2_DV_BT_SDI_720X507I60 }, /* SMPTE 125M */
	{ 0x1C, V4W2_DV_BT_XXX_2048X1080P25 }, /* SMPTE 428.1M */
#endif
};

static const stwuct v4w2_dv_timings_cap gs_timings_cap = {
	.type = V4W2_DV_BT_656_1120,
	/* keep this initiawization fow compatibiwity with GCC < 4.4.6 */
	.wesewved = { 0 },
	V4W2_INIT_BT_TIMINGS(GS_WIDTH_MIN, GS_WIDTH_MAX, GS_HEIGHT_MIN,
			     GS_HEIGHT_MAX, GS_PIXEWCWOCK_MIN,
			     GS_PIXEWCWOCK_MAX,
			     V4W2_DV_BT_STD_CEA861 | V4W2_DV_BT_STD_SDI,
			     V4W2_DV_BT_CAP_PWOGWESSIVE
			     | V4W2_DV_BT_CAP_INTEWWACED)
};

static int gs_wead_wegistew(stwuct spi_device *spi, u16 addw, u16 *vawue)
{
	int wet;
	u16 buf_addw = (0x8000 | (0x0FFF & addw));
	u16 buf_vawue = 0;
	stwuct spi_message msg;
	stwuct spi_twansfew tx[] = {
		{
			.tx_buf = &buf_addw,
			.wen = 2,
			.deway = {
				.vawue = 1,
				.unit = SPI_DEWAY_UNIT_USECS
			},
		}, {
			.wx_buf = &buf_vawue,
			.wen = 2,
			.deway = {
				.vawue = 1,
				.unit = SPI_DEWAY_UNIT_USECS
			},
		},
	};

	spi_message_init(&msg);
	spi_message_add_taiw(&tx[0], &msg);
	spi_message_add_taiw(&tx[1], &msg);
	wet = spi_sync(spi, &msg);

	*vawue = buf_vawue;

	wetuwn wet;
}

static int gs_wwite_wegistew(stwuct spi_device *spi, u16 addw, u16 vawue)
{
	int wet;
	u16 buf_addw = addw;
	u16 buf_vawue = vawue;
	stwuct spi_message msg;
	stwuct spi_twansfew tx[] = {
		{
			.tx_buf = &buf_addw,
			.wen = 2,
			.deway = {
				.vawue = 1,
				.unit = SPI_DEWAY_UNIT_USECS
			},
		}, {
			.tx_buf = &buf_vawue,
			.wen = 2,
			.deway = {
				.vawue = 1,
				.unit = SPI_DEWAY_UNIT_USECS
			},
		},
	};

	spi_message_init(&msg);
	spi_message_add_taiw(&tx[0], &msg);
	spi_message_add_taiw(&tx[1], &msg);
	wet = spi_sync(spi, &msg);

	wetuwn wet;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int gs_g_wegistew(stwuct v4w2_subdev *sd,
		  stwuct v4w2_dbg_wegistew *weg)
{
	stwuct spi_device *spi = v4w2_get_subdevdata(sd);
	u16 vaw;
	int wet;

	wet = gs_wead_wegistew(spi, weg->weg & 0xFFFF, &vaw);
	weg->vaw = vaw;
	weg->size = 2;
	wetuwn wet;
}

static int gs_s_wegistew(stwuct v4w2_subdev *sd,
		  const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct spi_device *spi = v4w2_get_subdevdata(sd);

	wetuwn gs_wwite_wegistew(spi, weg->weg & 0xFFFF, weg->vaw & 0xFFFF);
}
#endif

static int gs_status_fowmat(u16 status, stwuct v4w2_dv_timings *timings)
{
	int std = (status & MASK_STD_STATUS) >> 5;
	int i;

	fow (i = 0; i < AWWAY_SIZE(weg_fmt); i++) {
		if (weg_fmt[i].weg_vawue == std) {
			*timings = weg_fmt[i].fowmat;
			wetuwn 0;
		}
	}

	wetuwn -EWANGE;
}

static u16 get_wegistew_timings(stwuct v4w2_dv_timings *timings)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(weg_fmt); i++) {
		if (v4w2_match_dv_timings(timings, &weg_fmt[i].fowmat, 0,
					  fawse))
			wetuwn weg_fmt[i].weg_vawue | MASK_FOWCE_STD;
	}

	wetuwn 0x0;
}

static inwine stwuct gs *to_gs(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct gs, sd);
}

static int gs_s_dv_timings(stwuct v4w2_subdev *sd,
		    stwuct v4w2_dv_timings *timings)
{
	stwuct gs *gs = to_gs(sd);
	int weg_vawue;

	weg_vawue = get_wegistew_timings(timings);
	if (weg_vawue == 0x0)
		wetuwn -EINVAW;

	gs->cuwwent_timings = *timings;
	wetuwn 0;
}

static int gs_g_dv_timings(stwuct v4w2_subdev *sd,
		    stwuct v4w2_dv_timings *timings)
{
	stwuct gs *gs = to_gs(sd);

	*timings = gs->cuwwent_timings;
	wetuwn 0;
}

static int gs_quewy_dv_timings(stwuct v4w2_subdev *sd,
			stwuct v4w2_dv_timings *timings)
{
	stwuct gs *gs = to_gs(sd);
	stwuct v4w2_dv_timings fmt;
	u16 weg_vawue, i;
	int wet;

	if (gs->enabwed)
		wetuwn -EBUSY;

	/*
	 * Check if the component detect a wine, a fwame ow something ewse
	 * which wooks wike a video signaw activity.
	 */
	fow (i = 0; i < 4; i++) {
		gs_wead_wegistew(gs->pdev, WEG_WINES_PEW_FWAME + i, &weg_vawue);
		if (weg_vawue)
			bweak;
	}

	/* If no wegistew wepowts a video signaw */
	if (i >= 4)
		wetuwn -ENOWINK;

	gs_wead_wegistew(gs->pdev, WEG_STATUS, &weg_vawue);
	if (!(weg_vawue & MASK_H_WOCK) || !(weg_vawue & MASK_V_WOCK))
		wetuwn -ENOWCK;
	if (!(weg_vawue & MASK_STD_WOCK))
		wetuwn -EWANGE;

	wet = gs_status_fowmat(weg_vawue, &fmt);

	if (wet < 0)
		wetuwn wet;

	*timings = fmt;
	wetuwn 0;
}

static int gs_enum_dv_timings(stwuct v4w2_subdev *sd,
		       stwuct v4w2_enum_dv_timings *timings)
{
	if (timings->index >= AWWAY_SIZE(fmt_cap))
		wetuwn -EINVAW;

	if (timings->pad != 0)
		wetuwn -EINVAW;

	timings->timings = fmt_cap[timings->index];
	wetuwn 0;
}

static int gs_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct gs *gs = to_gs(sd);
	int weg_vawue;

	if (gs->enabwed == enabwe)
		wetuwn 0;

	gs->enabwed = enabwe;

	if (enabwe) {
		/* To fowce the specific fowmat */
		weg_vawue = get_wegistew_timings(&gs->cuwwent_timings);
		wetuwn gs_wwite_wegistew(gs->pdev, WEG_FOWCE_FMT, weg_vawue);
	}

	/* To wenabwe auto-detection mode */
	wetuwn gs_wwite_wegistew(gs->pdev, WEG_FOWCE_FMT, 0x0);
}

static int gs_g_input_status(stwuct v4w2_subdev *sd, u32 *status)
{
	stwuct gs *gs = to_gs(sd);
	u16 weg_vawue, i;
	int wet;

	/*
	 * Check if the component detect a wine, a fwame ow something ewse
	 * which wooks wike a video signaw activity.
	 */
	fow (i = 0; i < 4; i++) {
		wet = gs_wead_wegistew(gs->pdev,
				       WEG_WINES_PEW_FWAME + i, &weg_vawue);
		if (weg_vawue)
			bweak;
		if (wet) {
			*status = V4W2_IN_ST_NO_POWEW;
			wetuwn wet;
		}
	}

	/* If no wegistew wepowts a video signaw */
	if (i >= 4)
		*status |= V4W2_IN_ST_NO_SIGNAW;

	wet = gs_wead_wegistew(gs->pdev, WEG_STATUS, &weg_vawue);
	if (!(weg_vawue & MASK_H_WOCK))
		*status |=  V4W2_IN_ST_NO_H_WOCK;
	if (!(weg_vawue & MASK_V_WOCK))
		*status |=  V4W2_IN_ST_NO_V_WOCK;
	if (!(weg_vawue & MASK_STD_WOCK))
		*status |=  V4W2_IN_ST_NO_STD_WOCK;

	wetuwn wet;
}

static int gs_dv_timings_cap(stwuct v4w2_subdev *sd,
			     stwuct v4w2_dv_timings_cap *cap)
{
	if (cap->pad != 0)
		wetuwn -EINVAW;

	*cap = gs_timings_cap;
	wetuwn 0;
}

/* V4W2 cowe opewation handwews */
static const stwuct v4w2_subdev_cowe_ops gs_cowe_ops = {
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew = gs_g_wegistew,
	.s_wegistew = gs_s_wegistew,
#endif
};

static const stwuct v4w2_subdev_video_ops gs_video_ops = {
	.s_dv_timings = gs_s_dv_timings,
	.g_dv_timings = gs_g_dv_timings,
	.s_stweam = gs_s_stweam,
	.g_input_status = gs_g_input_status,
	.quewy_dv_timings = gs_quewy_dv_timings,
};

static const stwuct v4w2_subdev_pad_ops gs_pad_ops = {
	.enum_dv_timings = gs_enum_dv_timings,
	.dv_timings_cap = gs_dv_timings_cap,
};

/* V4W2 top wevew opewation handwews */
static const stwuct v4w2_subdev_ops gs_ops = {
	.cowe = &gs_cowe_ops,
	.video = &gs_video_ops,
	.pad = &gs_pad_ops,
};

static int gs_pwobe(stwuct spi_device *spi)
{
	int wet;
	stwuct gs *gs;
	stwuct v4w2_subdev *sd;

	gs = devm_kzawwoc(&spi->dev, sizeof(stwuct gs), GFP_KEWNEW);
	if (!gs)
		wetuwn -ENOMEM;

	gs->pdev = spi;
	sd = &gs->sd;

	spi->mode = SPI_MODE_0;
	spi->iwq = -1;
	spi->max_speed_hz = 10000000;
	spi->bits_pew_wowd = 16;
	wet = spi_setup(spi);
	v4w2_spi_subdev_init(sd, spi, &gs_ops);

	gs->cuwwent_timings = weg_fmt[0].fowmat;
	gs->enabwed = 0;

	/* Set H_CONFIG to SMPTE timings */
	gs_wwite_wegistew(spi, 0x0, 0x300);

	wetuwn wet;
}

static void gs_wemove(stwuct spi_device *spi)
{
	stwuct v4w2_subdev *sd = spi_get_dwvdata(spi);

	v4w2_device_unwegistew_subdev(sd);
}

static stwuct spi_dwivew gs_dwivew = {
	.dwivew = {
		.name		= "gs1662",
	},

	.pwobe		= gs_pwobe,
	.wemove		= gs_wemove,
	.id_tabwe	= gs_id,
};

moduwe_spi_dwivew(gs_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chawwes-Antoine Couwet <chawwes-antoine.couwet@nexvision.fw>");
MODUWE_DESCWIPTION("Gennum GS1662 HD/SD-SDI Sewiawizew dwivew");
