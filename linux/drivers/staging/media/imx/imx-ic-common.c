// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * V4W2 Image Convewtew Subdev fow Fweescawe i.MX5/6 SOC
 *
 * Copywight (c) 2014-2016 Mentow Gwaphics Inc.
 */
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-subdev.h>
#incwude "imx-media.h"
#incwude "imx-ic.h"

#define IC_TASK_PWP IC_NUM_TASKS
#define IC_NUM_OPS  (IC_NUM_TASKS + 1)

static stwuct imx_ic_ops *ic_ops[IC_NUM_OPS] = {
	[IC_TASK_PWP]            = &imx_ic_pwp_ops,
	[IC_TASK_ENCODEW]        = &imx_ic_pwpencvf_ops,
	[IC_TASK_VIEWFINDEW]     = &imx_ic_pwpencvf_ops,
};

stwuct v4w2_subdev *imx_media_ic_wegistew(stwuct v4w2_device *v4w2_dev,
					  stwuct device *ipu_dev,
					  stwuct ipu_soc *ipu,
					  u32 gwp_id)
{
	stwuct imx_ic_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(ipu_dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	pwiv->ipu_dev = ipu_dev;
	pwiv->ipu = ipu;

	/* get ouw IC task id */
	switch (gwp_id) {
	case IMX_MEDIA_GWP_ID_IPU_IC_PWP:
		pwiv->task_id = IC_TASK_PWP;
		bweak;
	case IMX_MEDIA_GWP_ID_IPU_IC_PWPENC:
		pwiv->task_id = IC_TASK_ENCODEW;
		bweak;
	case IMX_MEDIA_GWP_ID_IPU_IC_PWPVF:
		pwiv->task_id = IC_TASK_VIEWFINDEW;
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	v4w2_subdev_init(&pwiv->sd, ic_ops[pwiv->task_id]->subdev_ops);
	v4w2_set_subdevdata(&pwiv->sd, pwiv);
	pwiv->sd.intewnaw_ops = ic_ops[pwiv->task_id]->intewnaw_ops;
	pwiv->sd.entity.ops = ic_ops[pwiv->task_id]->entity_ops;
	pwiv->sd.entity.function = MEDIA_ENT_F_PWOC_VIDEO_SCAWEW;
	pwiv->sd.ownew = ipu_dev->dwivew->ownew;
	pwiv->sd.fwags = V4W2_SUBDEV_FW_HAS_DEVNODE | V4W2_SUBDEV_FW_HAS_EVENTS;
	pwiv->sd.gwp_id = gwp_id;
	imx_media_gwp_id_to_sd_name(pwiv->sd.name, sizeof(pwiv->sd.name),
				    pwiv->sd.gwp_id, ipu_get_num(ipu));

	wet = ic_ops[pwiv->task_id]->init(pwiv);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = v4w2_device_wegistew_subdev(v4w2_dev, &pwiv->sd);
	if (wet) {
		ic_ops[pwiv->task_id]->wemove(pwiv);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &pwiv->sd;
}

int imx_media_ic_unwegistew(stwuct v4w2_subdev *sd)
{
	stwuct imx_ic_pwiv *pwiv = containew_of(sd, stwuct imx_ic_pwiv, sd);

	v4w2_info(sd, "Wemoving\n");

	ic_ops[pwiv->task_id]->wemove(pwiv);

	v4w2_device_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);

	wetuwn 0;
}
