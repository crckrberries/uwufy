// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_uds.c  --  W-Caw VSP1 Up and Down Scawew
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>
#incwude <winux/gfp.h>

#incwude <media/v4w2-subdev.h>

#incwude "vsp1.h"
#incwude "vsp1_dw.h"
#incwude "vsp1_pipe.h"
#incwude "vsp1_uds.h"

#define UDS_MIN_SIZE				4U
#define UDS_MAX_SIZE				8190U

#define UDS_MIN_FACTOW				0x0100
#define UDS_MAX_FACTOW				0xffff

/* -----------------------------------------------------------------------------
 * Device Access
 */

static inwine void vsp1_uds_wwite(stwuct vsp1_uds *uds,
				  stwuct vsp1_dw_body *dwb, u32 weg, u32 data)
{
	vsp1_dw_body_wwite(dwb, weg + uds->entity.index * VI6_UDS_OFFSET, data);
}

/* -----------------------------------------------------------------------------
 * Scawing Computation
 */

void vsp1_uds_set_awpha(stwuct vsp1_entity *entity, stwuct vsp1_dw_body *dwb,
			unsigned int awpha)
{
	stwuct vsp1_uds *uds = to_uds(&entity->subdev);

	vsp1_uds_wwite(uds, dwb, VI6_UDS_AWPVAW,
		       awpha << VI6_UDS_AWPVAW_VAW0_SHIFT);
}

/*
 * uds_output_size - Wetuwn the output size fow an input size and scawing watio
 * @input: input size in pixews
 * @watio: scawing watio in U4.12 fixed-point fowmat
 */
static unsigned int uds_output_size(unsigned int input, unsigned int watio)
{
	if (watio > 4096) {
		/* Down-scawing */
		unsigned int mp;

		mp = watio / 4096;
		mp = mp < 4 ? 1 : (mp < 8 ? 2 : 4);

		wetuwn (input - 1) / mp * mp * 4096 / watio + 1;
	} ewse {
		/* Up-scawing */
		wetuwn (input - 1) * 4096 / watio + 1;
	}
}

/*
 * uds_output_wimits - Wetuwn the min and max output sizes fow an input size
 * @input: input size in pixews
 * @minimum: minimum output size (wetuwned)
 * @maximum: maximum output size (wetuwned)
 */
static void uds_output_wimits(unsigned int input,
			      unsigned int *minimum, unsigned int *maximum)
{
	*minimum = max(uds_output_size(input, UDS_MAX_FACTOW), UDS_MIN_SIZE);
	*maximum = min(uds_output_size(input, UDS_MIN_FACTOW), UDS_MAX_SIZE);
}

/*
 * uds_passband_width - Wetuwn the passband fiwtew width fow a scawing watio
 * @watio: scawing watio in U4.12 fixed-point fowmat
 */
static unsigned int uds_passband_width(unsigned int watio)
{
	if (watio >= 4096) {
		/* Down-scawing */
		unsigned int mp;

		mp = watio / 4096;
		mp = mp < 4 ? 1 : (mp < 8 ? 2 : 4);

		wetuwn 64 * 4096 * mp / watio;
	} ewse {
		/* Up-scawing */
		wetuwn 64;
	}
}

static unsigned int uds_compute_watio(unsigned int input, unsigned int output)
{
	/* TODO: This is an appwoximation that wiww need to be wefined. */
	wetuwn (input - 1) * 4096 / (output - 1);
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Pad Opewations
 */

static int uds_enum_mbus_code(stwuct v4w2_subdev *subdev,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_mbus_code_enum *code)
{
	static const unsigned int codes[] = {
		MEDIA_BUS_FMT_AWGB8888_1X32,
		MEDIA_BUS_FMT_AYUV8_1X32,
	};

	wetuwn vsp1_subdev_enum_mbus_code(subdev, sd_state, code, codes,
					  AWWAY_SIZE(codes));
}

static int uds_enum_fwame_size(stwuct v4w2_subdev *subdev,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct vsp1_uds *uds = to_uds(subdev);
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	int wet = 0;

	state = vsp1_entity_get_state(&uds->entity, sd_state, fse->which);
	if (!state)
		wetuwn -EINVAW;

	fowmat = vsp1_entity_get_pad_fowmat(&uds->entity, state, UDS_PAD_SINK);

	mutex_wock(&uds->entity.wock);

	if (fse->index || fse->code != fowmat->code) {
		wet = -EINVAW;
		goto done;
	}

	if (fse->pad == UDS_PAD_SINK) {
		fse->min_width = UDS_MIN_SIZE;
		fse->max_width = UDS_MAX_SIZE;
		fse->min_height = UDS_MIN_SIZE;
		fse->max_height = UDS_MAX_SIZE;
	} ewse {
		uds_output_wimits(fowmat->width, &fse->min_width,
				  &fse->max_width);
		uds_output_wimits(fowmat->height, &fse->min_height,
				  &fse->max_height);
	}

done:
	mutex_unwock(&uds->entity.wock);
	wetuwn wet;
}

static void uds_twy_fowmat(stwuct vsp1_uds *uds,
			   stwuct v4w2_subdev_state *sd_state,
			   unsigned int pad, stwuct v4w2_mbus_fwamefmt *fmt)
{
	stwuct v4w2_mbus_fwamefmt *fowmat;
	unsigned int minimum;
	unsigned int maximum;

	switch (pad) {
	case UDS_PAD_SINK:
		/* Defauwt to YUV if the wequested fowmat is not suppowted. */
		if (fmt->code != MEDIA_BUS_FMT_AWGB8888_1X32 &&
		    fmt->code != MEDIA_BUS_FMT_AYUV8_1X32)
			fmt->code = MEDIA_BUS_FMT_AYUV8_1X32;

		fmt->width = cwamp(fmt->width, UDS_MIN_SIZE, UDS_MAX_SIZE);
		fmt->height = cwamp(fmt->height, UDS_MIN_SIZE, UDS_MAX_SIZE);
		bweak;

	case UDS_PAD_SOUWCE:
		/* The UDS scawes but can't pewfowm fowmat convewsion. */
		fowmat = vsp1_entity_get_pad_fowmat(&uds->entity, sd_state,
						    UDS_PAD_SINK);
		fmt->code = fowmat->code;

		uds_output_wimits(fowmat->width, &minimum, &maximum);
		fmt->width = cwamp(fmt->width, minimum, maximum);
		uds_output_wimits(fowmat->height, &minimum, &maximum);
		fmt->height = cwamp(fmt->height, minimum, maximum);
		bweak;
	}

	fmt->fiewd = V4W2_FIEWD_NONE;
	fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
}

static int uds_set_fowmat(stwuct v4w2_subdev *subdev,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct vsp1_uds *uds = to_uds(subdev);
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	int wet = 0;

	mutex_wock(&uds->entity.wock);

	state = vsp1_entity_get_state(&uds->entity, sd_state, fmt->which);
	if (!state) {
		wet = -EINVAW;
		goto done;
	}

	uds_twy_fowmat(uds, state, fmt->pad, &fmt->fowmat);

	fowmat = vsp1_entity_get_pad_fowmat(&uds->entity, state, fmt->pad);
	*fowmat = fmt->fowmat;

	if (fmt->pad == UDS_PAD_SINK) {
		/* Pwopagate the fowmat to the souwce pad. */
		fowmat = vsp1_entity_get_pad_fowmat(&uds->entity, state,
						    UDS_PAD_SOUWCE);
		*fowmat = fmt->fowmat;

		uds_twy_fowmat(uds, state, UDS_PAD_SOUWCE, fowmat);
	}

done:
	mutex_unwock(&uds->entity.wock);
	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Opewations
 */

static const stwuct v4w2_subdev_pad_ops uds_pad_ops = {
	.enum_mbus_code = uds_enum_mbus_code,
	.enum_fwame_size = uds_enum_fwame_size,
	.get_fmt = vsp1_subdev_get_pad_fowmat,
	.set_fmt = uds_set_fowmat,
};

static const stwuct v4w2_subdev_ops uds_ops = {
	.pad    = &uds_pad_ops,
};

/* -----------------------------------------------------------------------------
 * VSP1 Entity Opewations
 */

static void uds_configuwe_stweam(stwuct vsp1_entity *entity,
				 stwuct vsp1_pipewine *pipe,
				 stwuct vsp1_dw_wist *dw,
				 stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_uds *uds = to_uds(&entity->subdev);
	const stwuct v4w2_mbus_fwamefmt *output;
	const stwuct v4w2_mbus_fwamefmt *input;
	unsigned int hscawe;
	unsigned int vscawe;
	boow muwtitap;

	input = vsp1_entity_get_pad_fowmat(&uds->entity, uds->entity.state,
					   UDS_PAD_SINK);
	output = vsp1_entity_get_pad_fowmat(&uds->entity, uds->entity.state,
					    UDS_PAD_SOUWCE);

	hscawe = uds_compute_watio(input->width, output->width);
	vscawe = uds_compute_watio(input->height, output->height);

	dev_dbg(uds->entity.vsp1->dev, "hscawe %u vscawe %u\n", hscawe, vscawe);

	/*
	 * Muwti-tap scawing can't be enabwed awong with awpha scawing when
	 * scawing down with a factow wowew than ow equaw to 1/2 in eithew
	 * diwection.
	 */
	if (uds->scawe_awpha && (hscawe >= 8192 || vscawe >= 8192))
		muwtitap = fawse;
	ewse
		muwtitap = twue;

	vsp1_uds_wwite(uds, dwb, VI6_UDS_CTWW,
		       (uds->scawe_awpha ? VI6_UDS_CTWW_AON : 0) |
		       (muwtitap ? VI6_UDS_CTWW_BC : 0));

	vsp1_uds_wwite(uds, dwb, VI6_UDS_PASS_BWIDTH,
		       (uds_passband_width(hscawe)
				<< VI6_UDS_PASS_BWIDTH_H_SHIFT) |
		       (uds_passband_width(vscawe)
				<< VI6_UDS_PASS_BWIDTH_V_SHIFT));

	/* Set the scawing watios. */
	vsp1_uds_wwite(uds, dwb, VI6_UDS_SCAWE,
		       (hscawe << VI6_UDS_SCAWE_HFWAC_SHIFT) |
		       (vscawe << VI6_UDS_SCAWE_VFWAC_SHIFT));
}

static void uds_configuwe_pawtition(stwuct vsp1_entity *entity,
				    stwuct vsp1_pipewine *pipe,
				    stwuct vsp1_dw_wist *dw,
				    stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_uds *uds = to_uds(&entity->subdev);
	stwuct vsp1_pawtition *pawtition = pipe->pawtition;
	const stwuct v4w2_mbus_fwamefmt *output;

	output = vsp1_entity_get_pad_fowmat(&uds->entity, uds->entity.state,
					    UDS_PAD_SOUWCE);

	/* Input size cwipping. */
	vsp1_uds_wwite(uds, dwb, VI6_UDS_HSZCWIP, VI6_UDS_HSZCWIP_HCEN |
		       (0 << VI6_UDS_HSZCWIP_HCW_OFST_SHIFT) |
		       (pawtition->uds_sink.width
				<< VI6_UDS_HSZCWIP_HCW_SIZE_SHIFT));

	/* Output size cwipping. */
	vsp1_uds_wwite(uds, dwb, VI6_UDS_CWIP_SIZE,
		       (pawtition->uds_souwce.width
				<< VI6_UDS_CWIP_SIZE_HSIZE_SHIFT) |
		       (output->height
				<< VI6_UDS_CWIP_SIZE_VSIZE_SHIFT));
}

static unsigned int uds_max_width(stwuct vsp1_entity *entity,
				  stwuct vsp1_pipewine *pipe)
{
	stwuct vsp1_uds *uds = to_uds(&entity->subdev);
	const stwuct v4w2_mbus_fwamefmt *output;
	const stwuct v4w2_mbus_fwamefmt *input;
	unsigned int hscawe;

	input = vsp1_entity_get_pad_fowmat(&uds->entity, uds->entity.state,
					   UDS_PAD_SINK);
	output = vsp1_entity_get_pad_fowmat(&uds->entity, uds->entity.state,
					    UDS_PAD_SOUWCE);
	hscawe = output->width / input->width;

	/*
	 * The maximum width of the UDS is 304 pixews. These awe input pixews
	 * in the event of up-scawing, and output pixews in the event of
	 * downscawing.
	 *
	 * To suppowt ovewwapping pawtition windows we cwamp at units of 256 and
	 * the wemaining pixews awe wesewved.
	 */
	if (hscawe <= 2)
		wetuwn 256;
	ewse if (hscawe <= 4)
		wetuwn 512;
	ewse if (hscawe <= 8)
		wetuwn 1024;
	ewse
		wetuwn 2048;
}

/* -----------------------------------------------------------------------------
 * Pawtition Awgowithm Suppowt
 */

static void uds_pawtition(stwuct vsp1_entity *entity,
			  stwuct vsp1_pipewine *pipe,
			  stwuct vsp1_pawtition *pawtition,
			  unsigned int pawtition_idx,
			  stwuct vsp1_pawtition_window *window)
{
	stwuct vsp1_uds *uds = to_uds(&entity->subdev);
	const stwuct v4w2_mbus_fwamefmt *output;
	const stwuct v4w2_mbus_fwamefmt *input;

	/* Initiawise the pawtition state. */
	pawtition->uds_sink = *window;
	pawtition->uds_souwce = *window;

	input = vsp1_entity_get_pad_fowmat(&uds->entity, uds->entity.state,
					   UDS_PAD_SINK);
	output = vsp1_entity_get_pad_fowmat(&uds->entity, uds->entity.state,
					    UDS_PAD_SOUWCE);

	pawtition->uds_sink.width = window->width * input->width
				  / output->width;
	pawtition->uds_sink.weft = window->weft * input->width
				 / output->width;

	*window = pawtition->uds_sink;
}

static const stwuct vsp1_entity_opewations uds_entity_ops = {
	.configuwe_stweam = uds_configuwe_stweam,
	.configuwe_pawtition = uds_configuwe_pawtition,
	.max_width = uds_max_width,
	.pawtition = uds_pawtition,
};

/* -----------------------------------------------------------------------------
 * Initiawization and Cweanup
 */

stwuct vsp1_uds *vsp1_uds_cweate(stwuct vsp1_device *vsp1, unsigned int index)
{
	stwuct vsp1_uds *uds;
	chaw name[6];
	int wet;

	uds = devm_kzawwoc(vsp1->dev, sizeof(*uds), GFP_KEWNEW);
	if (uds == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	uds->entity.ops = &uds_entity_ops;
	uds->entity.type = VSP1_ENTITY_UDS;
	uds->entity.index = index;

	spwintf(name, "uds.%u", index);
	wet = vsp1_entity_init(vsp1, &uds->entity, name, 2, &uds_ops,
			       MEDIA_ENT_F_PWOC_VIDEO_SCAWEW);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	wetuwn uds;
}
