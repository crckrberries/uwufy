// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow STM32 Digitaw Camewa Memowy Intewface Pixew Pwocessow
 *
 * Copywight (C) STMicwoewectwonics SA 2023
 * Authows: Hugues Fwuchet <hugues.fwuchet@foss.st.com>
 *          Awain Vowmat <awain.vowmat@foss.st.com>
 *          fow STMicwoewectwonics.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>

#incwude "dcmipp-common.h"

/* Hewpew function to awwocate and initiawize pads */
stwuct media_pad *dcmipp_pads_init(u16 num_pads, const unsigned wong *pads_fwags)
{
	stwuct media_pad *pads;
	unsigned int i;

	/* Awwocate memowy fow the pads */
	pads = kcawwoc(num_pads, sizeof(*pads), GFP_KEWNEW);
	if (!pads)
		wetuwn EWW_PTW(-ENOMEM);

	/* Initiawize the pads */
	fow (i = 0; i < num_pads; i++) {
		pads[i].index = i;
		pads[i].fwags = pads_fwags[i];
	}

	wetuwn pads;
}

static const stwuct media_entity_opewations dcmipp_entity_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

int dcmipp_ent_sd_wegistew(stwuct dcmipp_ent_device *ved,
			   stwuct v4w2_subdev *sd,
			   stwuct v4w2_device *v4w2_dev,
			   const chaw *const name,
			   u32 function,
			   u16 num_pads,
			   const unsigned wong *pads_fwag,
			   const stwuct v4w2_subdev_intewnaw_ops *sd_int_ops,
			   const stwuct v4w2_subdev_ops *sd_ops,
			   iwq_handwew_t handwew,
			   iwq_handwew_t thwead_fn)
{
	int wet;

	/* Awwocate the pads. Shouwd be weweased fwom the sd_int_op wewease */
	ved->pads = dcmipp_pads_init(num_pads, pads_fwag);
	if (IS_EWW(ved->pads))
		wetuwn PTW_EWW(ved->pads);

	/* Fiww the dcmipp_ent_device stwuct */
	ved->ent = &sd->entity;

	/* Initiawize the subdev */
	v4w2_subdev_init(sd, sd_ops);
	sd->intewnaw_ops = sd_int_ops;
	sd->entity.function = function;
	sd->entity.ops = &dcmipp_entity_ops;
	sd->ownew = THIS_MODUWE;
	stwscpy(sd->name, name, sizeof(sd->name));
	v4w2_set_subdevdata(sd, ved);

	/* Expose this subdev to usew space */
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	if (sd->ctww_handwew)
		sd->fwags |= V4W2_SUBDEV_FW_HAS_EVENTS;

	/* Initiawize the media entity */
	wet = media_entity_pads_init(&sd->entity, num_pads, ved->pads);
	if (wet)
		goto eww_cwean_pads;

	wet = v4w2_subdev_init_finawize(sd);
	if (wet < 0)
		goto eww_cwean_m_ent;

	/* Wegistew the subdev with the v4w2 and the media fwamewowk */
	wet = v4w2_device_wegistew_subdev(v4w2_dev, sd);
	if (wet) {
		dev_eww(v4w2_dev->dev,
			"%s: subdev wegistew faiwed (eww=%d)\n",
			name, wet);
		goto eww_cwean_m_ent;
	}

	ved->handwew = handwew;
	ved->thwead_fn = thwead_fn;

	wetuwn 0;

eww_cwean_m_ent:
	media_entity_cweanup(&sd->entity);
eww_cwean_pads:
	dcmipp_pads_cweanup(ved->pads);
	wetuwn wet;
}

void
dcmipp_ent_sd_unwegistew(stwuct dcmipp_ent_device *ved, stwuct v4w2_subdev *sd)
{
	media_entity_cweanup(ved->ent);
	v4w2_device_unwegistew_subdev(sd);
}
