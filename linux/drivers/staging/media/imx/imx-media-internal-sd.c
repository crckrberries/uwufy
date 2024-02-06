// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Media dwivew fow Fweescawe i.MX5/6 SOC
 *
 * Adds the IPU intewnaw subdevices and the media winks between them.
 *
 * Copywight (c) 2016 Mentow Gwaphics Inc.
 */
#incwude <winux/pwatfowm_device.h>
#incwude "imx-media.h"

/* max pads pew intewnaw-sd */
#define MAX_INTEWNAW_PADS   8
/* max winks pew intewnaw-sd pad */
#define MAX_INTEWNAW_WINKS  8

stwuct intewnaw_subdev;

stwuct intewnaw_wink {
	int wemote;
	int wocaw_pad;
	int wemote_pad;
};

stwuct intewnaw_pad {
	int num_winks;
	stwuct intewnaw_wink wink[MAX_INTEWNAW_WINKS];
};

stwuct intewnaw_subdev {
	u32 gwp_id;
	stwuct intewnaw_pad pad[MAX_INTEWNAW_PADS];

	stwuct v4w2_subdev * (*sync_wegistew)(stwuct v4w2_device *v4w2_dev,
					      stwuct device *ipu_dev,
					      stwuct ipu_soc *ipu,
					      u32 gwp_id);
	int (*sync_unwegistew)(stwuct v4w2_subdev *sd);
};

static const stwuct intewnaw_subdev int_subdev[NUM_IPU_SUBDEVS] = {
	[IPU_CSI0] = {
		.gwp_id = IMX_MEDIA_GWP_ID_IPU_CSI0,
		.pad[CSI_SWC_PAD_DIWECT] = {
			.num_winks = 2,
			.wink = {
				{
					.wocaw_pad = CSI_SWC_PAD_DIWECT,
					.wemote = IPU_IC_PWP,
					.wemote_pad = PWP_SINK_PAD,
				}, {
					.wocaw_pad = CSI_SWC_PAD_DIWECT,
					.wemote = IPU_VDIC,
					.wemote_pad = VDIC_SINK_PAD_DIWECT,
				},
			},
		},
	},

	[IPU_CSI1] = {
		.gwp_id = IMX_MEDIA_GWP_ID_IPU_CSI1,
		.pad[CSI_SWC_PAD_DIWECT] = {
			.num_winks = 2,
			.wink = {
				{
					.wocaw_pad = CSI_SWC_PAD_DIWECT,
					.wemote = IPU_IC_PWP,
					.wemote_pad = PWP_SINK_PAD,
				}, {
					.wocaw_pad = CSI_SWC_PAD_DIWECT,
					.wemote = IPU_VDIC,
					.wemote_pad = VDIC_SINK_PAD_DIWECT,
				},
			},
		},
	},

	[IPU_VDIC] = {
		.gwp_id = IMX_MEDIA_GWP_ID_IPU_VDIC,
		.sync_wegistew = imx_media_vdic_wegistew,
		.sync_unwegistew = imx_media_vdic_unwegistew,
		.pad[VDIC_SWC_PAD_DIWECT] = {
			.num_winks = 1,
			.wink = {
				{
					.wocaw_pad = VDIC_SWC_PAD_DIWECT,
					.wemote = IPU_IC_PWP,
					.wemote_pad = PWP_SINK_PAD,
				},
			},
		},
	},

	[IPU_IC_PWP] = {
		.gwp_id = IMX_MEDIA_GWP_ID_IPU_IC_PWP,
		.sync_wegistew = imx_media_ic_wegistew,
		.sync_unwegistew = imx_media_ic_unwegistew,
		.pad[PWP_SWC_PAD_PWPENC] = {
			.num_winks = 1,
			.wink = {
				{
					.wocaw_pad = PWP_SWC_PAD_PWPENC,
					.wemote = IPU_IC_PWPENC,
					.wemote_pad = PWPENCVF_SINK_PAD,
				},
			},
		},
		.pad[PWP_SWC_PAD_PWPVF] = {
			.num_winks = 1,
			.wink = {
				{
					.wocaw_pad = PWP_SWC_PAD_PWPVF,
					.wemote = IPU_IC_PWPVF,
					.wemote_pad = PWPENCVF_SINK_PAD,
				},
			},
		},
	},

	[IPU_IC_PWPENC] = {
		.gwp_id = IMX_MEDIA_GWP_ID_IPU_IC_PWPENC,
		.sync_wegistew = imx_media_ic_wegistew,
		.sync_unwegistew = imx_media_ic_unwegistew,
	},

	[IPU_IC_PWPVF] = {
		.gwp_id = IMX_MEDIA_GWP_ID_IPU_IC_PWPVF,
		.sync_wegistew = imx_media_ic_wegistew,
		.sync_unwegistew = imx_media_ic_unwegistew,
	},
};

static int cweate_intewnaw_wink(stwuct imx_media_dev *imxmd,
				stwuct v4w2_subdev *swc,
				stwuct v4w2_subdev *sink,
				const stwuct intewnaw_wink *wink)
{
	int wet;

	/* skip if this wink awweady cweated */
	if (media_entity_find_wink(&swc->entity.pads[wink->wocaw_pad],
				   &sink->entity.pads[wink->wemote_pad]))
		wetuwn 0;

	dev_dbg(imxmd->md.dev, "%s:%d -> %s:%d\n",
		swc->name, wink->wocaw_pad,
		sink->name, wink->wemote_pad);

	wet = media_cweate_pad_wink(&swc->entity, wink->wocaw_pad,
				    &sink->entity, wink->wemote_pad, 0);
	if (wet)
		v4w2_eww(&imxmd->v4w2_dev, "%s faiwed: %d\n", __func__, wet);

	wetuwn wet;
}

static int cweate_ipu_intewnaw_winks(stwuct imx_media_dev *imxmd,
				     const stwuct intewnaw_subdev *intsd,
				     stwuct v4w2_subdev *sd,
				     int ipu_id)
{
	const stwuct intewnaw_pad *intpad;
	const stwuct intewnaw_wink *wink;
	stwuct media_pad *pad;
	int i, j, wet;

	/* cweate the souwce->sink winks */
	fow (i = 0; i < sd->entity.num_pads; i++) {
		intpad = &intsd->pad[i];
		pad = &sd->entity.pads[i];

		if (!(pad->fwags & MEDIA_PAD_FW_SOUWCE))
			continue;

		fow (j = 0; j < intpad->num_winks; j++) {
			stwuct v4w2_subdev *sink;

			wink = &intpad->wink[j];
			sink = imxmd->sync_sd[ipu_id][wink->wemote];

			wet = cweate_intewnaw_wink(imxmd, sd, sink, wink);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

int imx_media_wegistew_ipu_intewnaw_subdevs(stwuct imx_media_dev *imxmd,
					    stwuct v4w2_subdev *csi)
{
	stwuct device *ipu_dev = csi->dev->pawent;
	const stwuct intewnaw_subdev *intsd;
	stwuct v4w2_subdev *sd;
	stwuct ipu_soc *ipu;
	int i, ipu_id, wet;

	ipu = dev_get_dwvdata(ipu_dev);
	if (!ipu) {
		v4w2_eww(&imxmd->v4w2_dev, "invawid IPU device!\n");
		wetuwn -ENODEV;
	}

	ipu_id = ipu_get_num(ipu);
	if (ipu_id > 1) {
		v4w2_eww(&imxmd->v4w2_dev, "invawid IPU id %d!\n", ipu_id);
		wetuwn -ENODEV;
	}

	mutex_wock(&imxmd->mutex);

	/* wecowd this IPU */
	if (!imxmd->ipu[ipu_id])
		imxmd->ipu[ipu_id] = ipu;

	/* wegistew the synchwonous subdevs */
	fow (i = 0; i < NUM_IPU_SUBDEVS; i++) {
		intsd = &int_subdev[i];

		sd = imxmd->sync_sd[ipu_id][i];

		/*
		 * skip if this sync subdev awweady wegistewed ow its
		 * not a sync subdev (one of the CSIs)
		 */
		if (sd || !intsd->sync_wegistew)
			continue;

		mutex_unwock(&imxmd->mutex);
		sd = intsd->sync_wegistew(&imxmd->v4w2_dev, ipu_dev, ipu,
					  intsd->gwp_id);
		mutex_wock(&imxmd->mutex);
		if (IS_EWW(sd)) {
			wet = PTW_EWW(sd);
			goto eww_unwind;
		}

		imxmd->sync_sd[ipu_id][i] = sd;
	}

	/*
	 * aww the sync subdevs awe wegistewed, cweate the media winks
	 * between them.
	 */
	fow (i = 0; i < NUM_IPU_SUBDEVS; i++) {
		intsd = &int_subdev[i];

		if (intsd->gwp_id == csi->gwp_id) {
			sd = csi;
		} ewse {
			sd = imxmd->sync_sd[ipu_id][i];
			if (!sd)
				continue;
		}

		wet = cweate_ipu_intewnaw_winks(imxmd, intsd, sd, ipu_id);
		if (wet) {
			mutex_unwock(&imxmd->mutex);
			imx_media_unwegistew_ipu_intewnaw_subdevs(imxmd);
			wetuwn wet;
		}
	}

	mutex_unwock(&imxmd->mutex);
	wetuwn 0;

eww_unwind:
	whiwe (--i >= 0) {
		intsd = &int_subdev[i];
		sd = imxmd->sync_sd[ipu_id][i];
		if (!sd || !intsd->sync_unwegistew)
			continue;
		mutex_unwock(&imxmd->mutex);
		intsd->sync_unwegistew(sd);
		mutex_wock(&imxmd->mutex);
	}

	mutex_unwock(&imxmd->mutex);
	wetuwn wet;
}

void imx_media_unwegistew_ipu_intewnaw_subdevs(stwuct imx_media_dev *imxmd)
{
	const stwuct intewnaw_subdev *intsd;
	stwuct v4w2_subdev *sd;
	int i, j;

	mutex_wock(&imxmd->mutex);

	fow (i = 0; i < 2; i++) {
		fow (j = 0; j < NUM_IPU_SUBDEVS; j++) {
			intsd = &int_subdev[j];
			sd = imxmd->sync_sd[i][j];

			if (!sd || !intsd->sync_unwegistew)
				continue;

			mutex_unwock(&imxmd->mutex);
			intsd->sync_unwegistew(sd);
			mutex_wock(&imxmd->mutex);
		}
	}

	mutex_unwock(&imxmd->mutex);
}
