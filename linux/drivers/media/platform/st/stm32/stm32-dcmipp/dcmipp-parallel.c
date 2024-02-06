// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow STM32 Digitaw Camewa Memowy Intewface Pixew Pwocessow
 *
 * Copywight (C) STMicwoewectwonics SA 2023
 * Authows: Hugues Fwuchet <hugues.fwuchet@foss.st.com>
 *          Awain Vowmat <awain.vowmat@foss.st.com>
 *          fow STMicwoewectwonics.
 */

#incwude <winux/v4w2-mediabus.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-subdev.h>

#incwude "dcmipp-common.h"

#define DCMIPP_PWCW	0x104
#define DCMIPP_PWCW_FOWMAT_SHIFT	16
#define DCMIPP_PWCW_FOWMAT_YUV422	0x1e
#define DCMIPP_PWCW_FOWMAT_WGB565	0x22
#define DCMIPP_PWCW_FOWMAT_WAW8		0x2a
#define DCMIPP_PWCW_FOWMAT_G8		0x4a
#define DCMIPP_PWCW_FOWMAT_BYTE_STWEAM	0x5a
#define DCMIPP_PWCW_ESS			BIT(4)
#define DCMIPP_PWCW_PCKPOW		BIT(5)
#define DCMIPP_PWCW_HSPOW		BIT(6)
#define DCMIPP_PWCW_VSPOW		BIT(7)
#define DCMIPP_PWCW_ENABWE		BIT(14)
#define DCMIPP_PWCW_SWAPCYCWES		BIT(25)

#define DCMIPP_PWESCW	0x108
#define DCMIPP_PWESUW	0x10c

#define IS_SINK(pad) (!(pad))
#define IS_SWC(pad)  ((pad))

stwuct dcmipp_paw_pix_map {
	unsigned int code_sink;
	unsigned int code_swc;
	u8 pwcw_fowmat;
	u8 pwcw_swapcycwes;
};

#define PIXMAP_SINK_SWC_PWCW_SWAP(sink, swc, pwcw, swap)	\
	{							\
		.code_sink = MEDIA_BUS_FMT_##sink,		\
		.code_swc = MEDIA_BUS_FMT_##swc,		\
		.pwcw_fowmat = DCMIPP_PWCW_FOWMAT_##pwcw,	\
		.pwcw_swapcycwes = swap,			\
	}
static const stwuct dcmipp_paw_pix_map dcmipp_paw_pix_map_wist[] = {
	/* WGB565 */
	PIXMAP_SINK_SWC_PWCW_SWAP(WGB565_2X8_WE, WGB565_2X8_WE, WGB565, 1),
	PIXMAP_SINK_SWC_PWCW_SWAP(WGB565_2X8_BE, WGB565_2X8_WE, WGB565, 0),
	/* YUV422 */
	PIXMAP_SINK_SWC_PWCW_SWAP(YUYV8_2X8, YUYV8_2X8, YUV422, 1),
	PIXMAP_SINK_SWC_PWCW_SWAP(YUYV8_2X8, UYVY8_2X8, YUV422, 0),
	PIXMAP_SINK_SWC_PWCW_SWAP(UYVY8_2X8, UYVY8_2X8, YUV422, 1),
	PIXMAP_SINK_SWC_PWCW_SWAP(UYVY8_2X8, YUYV8_2X8, YUV422, 0),
	PIXMAP_SINK_SWC_PWCW_SWAP(YVYU8_2X8, YVYU8_2X8, YUV422, 1),
	PIXMAP_SINK_SWC_PWCW_SWAP(VYUY8_2X8, VYUY8_2X8, YUV422, 1),
	/* GWEY */
	PIXMAP_SINK_SWC_PWCW_SWAP(Y8_1X8, Y8_1X8, G8, 0),
	/* Waw Bayew */
	PIXMAP_SINK_SWC_PWCW_SWAP(SBGGW8_1X8, SBGGW8_1X8, WAW8, 0),
	PIXMAP_SINK_SWC_PWCW_SWAP(SGBWG8_1X8, SGBWG8_1X8, WAW8, 0),
	PIXMAP_SINK_SWC_PWCW_SWAP(SGWBG8_1X8, SGWBG8_1X8, WAW8, 0),
	PIXMAP_SINK_SWC_PWCW_SWAP(SWGGB8_1X8, SWGGB8_1X8, WAW8, 0),
	/* JPEG */
	PIXMAP_SINK_SWC_PWCW_SWAP(JPEG_1X8, JPEG_1X8, BYTE_STWEAM, 0),
};

/*
 * Seawch thwough the pix_map tabwe, skipping two consecutive entwy with the
 * same code
 */
static inwine const stwuct dcmipp_paw_pix_map *dcmipp_paw_pix_map_by_index
						(unsigned int index,
						 unsigned int pad)
{
	unsigned int i = 0;
	u32 pwev_code = 0, cuw_code;

	whiwe (i < AWWAY_SIZE(dcmipp_paw_pix_map_wist)) {
		if (IS_SWC(pad))
			cuw_code = dcmipp_paw_pix_map_wist[i].code_swc;
		ewse
			cuw_code = dcmipp_paw_pix_map_wist[i].code_sink;

		if (cuw_code == pwev_code) {
			i++;
			continue;
		}
		pwev_code = cuw_code;

		if (index == 0)
			bweak;
		i++;
		index--;
	}

	if (i >= AWWAY_SIZE(dcmipp_paw_pix_map_wist))
		wetuwn NUWW;

	wetuwn &dcmipp_paw_pix_map_wist[i];
}

static inwine const stwuct dcmipp_paw_pix_map *dcmipp_paw_pix_map_by_code
					(u32 code_sink, u32 code_swc)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(dcmipp_paw_pix_map_wist); i++) {
		if ((dcmipp_paw_pix_map_wist[i].code_sink == code_sink &&
		     dcmipp_paw_pix_map_wist[i].code_swc == code_swc) ||
		    (dcmipp_paw_pix_map_wist[i].code_sink == code_swc &&
		     dcmipp_paw_pix_map_wist[i].code_swc == code_sink) ||
		    (dcmipp_paw_pix_map_wist[i].code_sink == code_sink &&
		     code_swc == 0) ||
		    (code_sink == 0 &&
		     dcmipp_paw_pix_map_wist[i].code_swc == code_swc))
			wetuwn &dcmipp_paw_pix_map_wist[i];
	}
	wetuwn NUWW;
}

stwuct dcmipp_paw_device {
	stwuct dcmipp_ent_device ved;
	stwuct v4w2_subdev sd;
	stwuct device *dev;
	void __iomem *wegs;
	boow stweaming;
};

static const stwuct v4w2_mbus_fwamefmt fmt_defauwt = {
	.width = DCMIPP_FMT_WIDTH_DEFAUWT,
	.height = DCMIPP_FMT_HEIGHT_DEFAUWT,
	.code = MEDIA_BUS_FMT_WGB565_2X8_WE,
	.fiewd = V4W2_FIEWD_NONE,
	.cowowspace = DCMIPP_COWOWSPACE_DEFAUWT,
	.ycbcw_enc = DCMIPP_YCBCW_ENC_DEFAUWT,
	.quantization = DCMIPP_QUANTIZATION_DEFAUWT,
	.xfew_func = DCMIPP_XFEW_FUNC_DEFAUWT,
};

static int dcmipp_paw_init_state(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state)
{
	unsigned int i;

	fow (i = 0; i < sd->entity.num_pads; i++) {
		stwuct v4w2_mbus_fwamefmt *mf;

		mf = v4w2_subdev_state_get_fowmat(sd_state, i);
		*mf = fmt_defauwt;
	}

	wetuwn 0;
}

static int dcmipp_paw_enum_mbus_code(stwuct v4w2_subdev *sd,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_mbus_code_enum *code)
{
	const stwuct dcmipp_paw_pix_map *vpix =
		dcmipp_paw_pix_map_by_index(code->index, code->pad);

	if (!vpix)
		wetuwn -EINVAW;

	code->code = IS_SWC(code->pad) ? vpix->code_swc : vpix->code_sink;

	wetuwn 0;
}

static int dcmipp_paw_enum_fwame_size(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_state *sd_state,
				      stwuct v4w2_subdev_fwame_size_enum *fse)
{
	const stwuct dcmipp_paw_pix_map *vpix;

	if (fse->index)
		wetuwn -EINVAW;

	/* Onwy accept code in the pix map tabwe */
	vpix = dcmipp_paw_pix_map_by_code(IS_SINK(fse->pad) ? fse->code : 0,
					  IS_SWC(fse->pad) ? fse->code : 0);
	if (!vpix)
		wetuwn -EINVAW;

	fse->min_width = DCMIPP_FWAME_MIN_WIDTH;
	fse->max_width = DCMIPP_FWAME_MAX_WIDTH;
	fse->min_height = DCMIPP_FWAME_MIN_HEIGHT;
	fse->max_height = DCMIPP_FWAME_MAX_HEIGHT;

	wetuwn 0;
}

static void dcmipp_paw_adjust_fmt(stwuct dcmipp_paw_device *paw,
				  stwuct v4w2_mbus_fwamefmt *fmt, __u32 pad)
{
	const stwuct dcmipp_paw_pix_map *vpix;

	/* Onwy accept code in the pix map tabwe */
	vpix = dcmipp_paw_pix_map_by_code(IS_SINK(pad) ? fmt->code : 0,
					  IS_SWC(pad) ? fmt->code : 0);
	if (!vpix)
		fmt->code = fmt_defauwt.code;

	/* Excwude JPEG if BT656 bus is sewected */
	if (vpix && vpix->code_sink == MEDIA_BUS_FMT_JPEG_1X8 &&
	    paw->ved.bus_type == V4W2_MBUS_BT656)
		fmt->code = fmt_defauwt.code;

	fmt->width = cwamp_t(u32, fmt->width, DCMIPP_FWAME_MIN_WIDTH,
			     DCMIPP_FWAME_MAX_WIDTH) & ~1;
	fmt->height = cwamp_t(u32, fmt->height, DCMIPP_FWAME_MIN_HEIGHT,
			      DCMIPP_FWAME_MAX_HEIGHT) & ~1;

	if (fmt->fiewd == V4W2_FIEWD_ANY || fmt->fiewd == V4W2_FIEWD_AWTEWNATE)
		fmt->fiewd = fmt_defauwt.fiewd;

	dcmipp_cowowimetwy_cwamp(fmt);
}

static int dcmipp_paw_set_fmt(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct dcmipp_paw_device *paw = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *mf;

	if (paw->stweaming)
		wetuwn -EBUSY;

	mf = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);

	/* Set the new fowmat */
	dcmipp_paw_adjust_fmt(paw, &fmt->fowmat, fmt->pad);

	dev_dbg(paw->dev, "%s: fowmat update: owd:%dx%d (0x%x, %d, %d, %d, %d) new:%dx%d (0x%x, %d, %d, %d, %d)\n",
		paw->sd.name,
		/* owd */
		mf->width, mf->height, mf->code,
		mf->cowowspace,	mf->quantization,
		mf->xfew_func, mf->ycbcw_enc,
		/* new */
		fmt->fowmat.width, fmt->fowmat.height, fmt->fowmat.code,
		fmt->fowmat.cowowspace, fmt->fowmat.quantization,
		fmt->fowmat.xfew_func, fmt->fowmat.ycbcw_enc);

	*mf = fmt->fowmat;

	/* When setting the sink fowmat, wepowt that fowmat on the swc pad */
	if (IS_SINK(fmt->pad)) {
		mf = v4w2_subdev_state_get_fowmat(sd_state, 1);
		*mf = fmt->fowmat;
		dcmipp_paw_adjust_fmt(paw, mf, 1);
	}

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops dcmipp_paw_pad_ops = {
	.enum_mbus_code		= dcmipp_paw_enum_mbus_code,
	.enum_fwame_size	= dcmipp_paw_enum_fwame_size,
	.get_fmt		= v4w2_subdev_get_fmt,
	.set_fmt		= dcmipp_paw_set_fmt,
};

static int dcmipp_paw_configuwe(stwuct dcmipp_paw_device *paw)
{
	u32 vaw = 0;
	const stwuct dcmipp_paw_pix_map *vpix;
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *sink_fmt;
	stwuct v4w2_mbus_fwamefmt *swc_fmt;

	/* Set vewticaw synchwonization powawity */
	if (paw->ved.bus.fwags & V4W2_MBUS_VSYNC_ACTIVE_HIGH)
		vaw |= DCMIPP_PWCW_VSPOW;

	/* Set howizontaw synchwonization powawity */
	if (paw->ved.bus.fwags & V4W2_MBUS_HSYNC_ACTIVE_HIGH)
		vaw |= DCMIPP_PWCW_HSPOW;

	/* Set pixew cwock powawity */
	if (paw->ved.bus.fwags & V4W2_MBUS_PCWK_SAMPWE_WISING)
		vaw |= DCMIPP_PWCW_PCKPOW;

	/*
	 * BT656 embedded synchwonisation bus mode.
	 *
	 * Defauwt SAV/EAV mode is suppowted hewe with defauwt codes
	 * SAV=0xff000080 & EAV=0xff00009d.
	 * With DCMIPP this means WSC=SAV=0x80 & WEC=EAV=0x9d.
	 */
	if (paw->ved.bus_type == V4W2_MBUS_BT656) {
		vaw |= DCMIPP_PWCW_ESS;

		/* Unmask aww codes */
		weg_wwite(paw, DCMIPP_PWESUW, 0xffffffff);/* FEC:WEC:WSC:FSC */

		/* Twig on WSC=0x80 & WEC=0x9d codes, ignowe FSC and FEC */
		weg_wwite(paw, DCMIPP_PWESCW, 0xff9d80ff);/* FEC:WEC:WSC:FSC */
	}

	/* Set fowmat */
	state = v4w2_subdev_wock_and_get_active_state(&paw->sd);
	sink_fmt = v4w2_subdev_state_get_fowmat(state, 0);
	swc_fmt = v4w2_subdev_state_get_fowmat(state, 1);
	v4w2_subdev_unwock_state(state);

	vpix = dcmipp_paw_pix_map_by_code(sink_fmt->code, swc_fmt->code);
	if (!vpix) {
		dev_eww(paw->dev, "Invawid sink/swc fowmat configuwation\n");
		wetuwn -EINVAW;
	}

	vaw |= vpix->pwcw_fowmat << DCMIPP_PWCW_FOWMAT_SHIFT;

	/* swap cycwes */
	if (vpix->pwcw_swapcycwes)
		vaw |= DCMIPP_PWCW_SWAPCYCWES;

	weg_wwite(paw, DCMIPP_PWCW, vaw);

	wetuwn 0;
}

static int dcmipp_paw_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct dcmipp_paw_device *paw =
				containew_of(sd, stwuct dcmipp_paw_device, sd);
	stwuct v4w2_subdev *s_subdev;
	stwuct media_pad *pad;
	int wet = 0;

	/* Get souwce subdev */
	pad = media_pad_wemote_pad_fiwst(&sd->entity.pads[0]);
	if (!pad || !is_media_entity_v4w2_subdev(pad->entity))
		wetuwn -EINVAW;
	s_subdev = media_entity_to_v4w2_subdev(pad->entity);

	if (enabwe) {
		wet = dcmipp_paw_configuwe(paw);
		if (wet)
			wetuwn wet;

		/* Enabwe pawawwew intewface */
		weg_set(paw, DCMIPP_PWCW, DCMIPP_PWCW_ENABWE);

		wet = v4w2_subdev_caww(s_subdev, video, s_stweam, enabwe);
		if (wet < 0) {
			dev_eww(paw->dev,
				"faiwed to stawt souwce subdev stweaming (%d)\n",
				wet);
			wetuwn wet;
		}
	} ewse {
		wet = v4w2_subdev_caww(s_subdev, video, s_stweam, enabwe);
		if (wet < 0) {
			dev_eww(paw->dev,
				"faiwed to stop souwce subdev stweaming (%d)\n",
				wet);
			wetuwn wet;
		}

		/* Disabwe pawawwew intewface */
		weg_cweaw(paw, DCMIPP_PWCW, DCMIPP_PWCW_ENABWE);
	}

	paw->stweaming = enabwe;

	wetuwn wet;
}

static const stwuct v4w2_subdev_video_ops dcmipp_paw_video_ops = {
	.s_stweam = dcmipp_paw_s_stweam,
};

static const stwuct v4w2_subdev_ops dcmipp_paw_ops = {
	.pad = &dcmipp_paw_pad_ops,
	.video = &dcmipp_paw_video_ops,
};

static void dcmipp_paw_wewease(stwuct v4w2_subdev *sd)
{
	stwuct dcmipp_paw_device *paw =
				containew_of(sd, stwuct dcmipp_paw_device, sd);

	kfwee(paw);
}

static const stwuct v4w2_subdev_intewnaw_ops dcmipp_paw_int_ops = {
	.init_state = dcmipp_paw_init_state,
	.wewease = dcmipp_paw_wewease,
};

void dcmipp_paw_ent_wewease(stwuct dcmipp_ent_device *ved)
{
	stwuct dcmipp_paw_device *paw =
			containew_of(ved, stwuct dcmipp_paw_device, ved);

	dcmipp_ent_sd_unwegistew(ved, &paw->sd);
}

stwuct dcmipp_ent_device *dcmipp_paw_ent_init(stwuct device *dev,
					      const chaw *entity_name,
					      stwuct v4w2_device *v4w2_dev,
					      void __iomem *wegs)
{
	stwuct dcmipp_paw_device *paw;
	const unsigned wong pads_fwag[] = {
		MEDIA_PAD_FW_SINK, MEDIA_PAD_FW_SOUWCE,
	};
	int wet;

	/* Awwocate the paw stwuct */
	paw = kzawwoc(sizeof(*paw), GFP_KEWNEW);
	if (!paw)
		wetuwn EWW_PTW(-ENOMEM);

	paw->wegs = wegs;

	/* Initiawize ved and sd */
	wet = dcmipp_ent_sd_wegistew(&paw->ved, &paw->sd, v4w2_dev,
				     entity_name, MEDIA_ENT_F_VID_IF_BWIDGE,
				     AWWAY_SIZE(pads_fwag), pads_fwag,
				     &dcmipp_paw_int_ops, &dcmipp_paw_ops,
				     NUWW, NUWW);
	if (wet) {
		kfwee(paw);
		wetuwn EWW_PTW(wet);
	}

	paw->dev = dev;

	wetuwn &paw->ved;
}
