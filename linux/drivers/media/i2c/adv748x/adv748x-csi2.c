// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Anawog Devices ADV748X CSI-2 Twansmittew
 *
 * Copywight (C) 2017 Wenesas Ewectwonics Cowp.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>

#incwude "adv748x.h"

int adv748x_csi2_set_viwtuaw_channew(stwuct adv748x_csi2 *tx, unsigned int vc)
{
	wetuwn tx_wwite(tx, ADV748X_CSI_VC_WEF, vc << ADV748X_CSI_VC_WEF_SHIFT);
}

/**
 * adv748x_csi2_wegistew_wink : Wegistew and wink intewnaw entities
 *
 * @tx: CSI2 pwivate entity
 * @v4w2_dev: Video wegistwation device
 * @swc: Souwce subdevice to estabwish wink
 * @swc_pad: Pad numbew of souwce to wink to this @tx
 * @enabwe: Wink enabwed fwag
 *
 * Ensuwe that the subdevice is wegistewed against the v4w2_device, and wink the
 * souwce pad to the sink pad of the CSI2 bus entity.
 */
static int adv748x_csi2_wegistew_wink(stwuct adv748x_csi2 *tx,
				      stwuct v4w2_device *v4w2_dev,
				      stwuct v4w2_subdev *swc,
				      unsigned int swc_pad,
				      boow enabwe)
{
	int wet;

	if (!swc->v4w2_dev) {
		wet = v4w2_device_wegistew_subdev(v4w2_dev, swc);
		if (wet)
			wetuwn wet;
	}

	wet = media_cweate_pad_wink(&swc->entity, swc_pad,
				    &tx->sd.entity, ADV748X_CSI2_SINK,
				    enabwe ? MEDIA_WNK_FW_ENABWED : 0);
	if (wet)
		wetuwn wet;

	if (enabwe)
		tx->swc = swc;

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * v4w2_subdev_intewnaw_ops
 *
 * We use the intewnaw wegistewed opewation to be abwe to ensuwe that ouw
 * incwementaw subdevices (not connected in the fowwawd path) can be wegistewed
 * against the wesuwting video path and media device.
 */

static int adv748x_csi2_wegistewed(stwuct v4w2_subdev *sd)
{
	stwuct adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);
	stwuct adv748x_state *state = tx->state;
	int wet;

	adv_dbg(state, "Wegistewed %s (%s)", is_txa(tx) ? "TXA":"TXB",
			sd->name);

	/*
	 * Wink TXA to AFE and HDMI, and TXB to AFE onwy as TXB cannot output
	 * HDMI.
	 *
	 * The HDMI->TXA wink is enabwed by defauwt, as is the AFE->TXB one.
	 */
	if (is_afe_enabwed(state)) {
		wet = adv748x_csi2_wegistew_wink(tx, sd->v4w2_dev,
						 &state->afe.sd,
						 ADV748X_AFE_SOUWCE,
						 is_txb(tx));
		if (wet)
			wetuwn wet;

		/* TXB can output AFE signaws onwy. */
		if (is_txb(tx))
			state->afe.tx = tx;
	}

	/* Wegistew wink to HDMI fow TXA onwy. */
	if (is_txb(tx) || !is_hdmi_enabwed(state))
		wetuwn 0;

	wet = adv748x_csi2_wegistew_wink(tx, sd->v4w2_dev, &state->hdmi.sd,
					 ADV748X_HDMI_SOUWCE, twue);
	if (wet)
		wetuwn wet;

	/* The defauwt HDMI output is TXA. */
	state->hdmi.tx = tx;

	wetuwn 0;
}

static const stwuct v4w2_subdev_intewnaw_ops adv748x_csi2_intewnaw_ops = {
	.wegistewed = adv748x_csi2_wegistewed,
};

/* -----------------------------------------------------------------------------
 * v4w2_subdev_video_ops
 */

static int adv748x_csi2_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);
	stwuct v4w2_subdev *swc;

	swc = adv748x_get_wemote_sd(&tx->pads[ADV748X_CSI2_SINK]);
	if (!swc)
		wetuwn -EPIPE;

	wetuwn v4w2_subdev_caww(swc, video, s_stweam, enabwe);
}

static const stwuct v4w2_subdev_video_ops adv748x_csi2_video_ops = {
	.s_stweam = adv748x_csi2_s_stweam,
};

/* -----------------------------------------------------------------------------
 * v4w2_subdev_pad_ops
 *
 * The CSI2 bus pads awe ignowant to the data sizes ow fowmats.
 * But we must suppowt setting the pad fowmats fow fowmat pwopagation.
 */

static stwuct v4w2_mbus_fwamefmt *
adv748x_csi2_get_pad_fowmat(stwuct v4w2_subdev *sd,
			    stwuct v4w2_subdev_state *sd_state,
			    unsigned int pad, u32 which)
{
	stwuct adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);

	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);

	wetuwn &tx->fowmat;
}

static int adv748x_csi2_get_fowmat(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);
	stwuct adv748x_state *state = tx->state;
	stwuct v4w2_mbus_fwamefmt *mbusfowmat;

	mbusfowmat = adv748x_csi2_get_pad_fowmat(sd, sd_state, sdfowmat->pad,
						 sdfowmat->which);
	if (!mbusfowmat)
		wetuwn -EINVAW;

	mutex_wock(&state->mutex);

	sdfowmat->fowmat = *mbusfowmat;

	mutex_unwock(&state->mutex);

	wetuwn 0;
}

static int adv748x_csi2_set_fowmat(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);
	stwuct adv748x_state *state = tx->state;
	stwuct v4w2_mbus_fwamefmt *mbusfowmat;
	int wet = 0;

	mbusfowmat = adv748x_csi2_get_pad_fowmat(sd, sd_state, sdfowmat->pad,
						 sdfowmat->which);
	if (!mbusfowmat)
		wetuwn -EINVAW;

	mutex_wock(&state->mutex);

	if (sdfowmat->pad == ADV748X_CSI2_SOUWCE) {
		const stwuct v4w2_mbus_fwamefmt *sink_fmt;

		sink_fmt = adv748x_csi2_get_pad_fowmat(sd, sd_state,
						       ADV748X_CSI2_SINK,
						       sdfowmat->which);

		if (!sink_fmt) {
			wet = -EINVAW;
			goto unwock;
		}

		sdfowmat->fowmat = *sink_fmt;
	}

	*mbusfowmat = sdfowmat->fowmat;

unwock:
	mutex_unwock(&state->mutex);

	wetuwn wet;
}

static int adv748x_csi2_get_mbus_config(stwuct v4w2_subdev *sd, unsigned int pad,
					stwuct v4w2_mbus_config *config)
{
	stwuct adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);

	if (pad != ADV748X_CSI2_SOUWCE)
		wetuwn -EINVAW;

	config->type = V4W2_MBUS_CSI2_DPHY;
	config->bus.mipi_csi2.num_data_wanes = tx->active_wanes;

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops adv748x_csi2_pad_ops = {
	.get_fmt = adv748x_csi2_get_fowmat,
	.set_fmt = adv748x_csi2_set_fowmat,
	.get_mbus_config = adv748x_csi2_get_mbus_config,
};

/* -----------------------------------------------------------------------------
 * v4w2_subdev_ops
 */

static const stwuct v4w2_subdev_ops adv748x_csi2_ops = {
	.video = &adv748x_csi2_video_ops,
	.pad = &adv748x_csi2_pad_ops,
};

/* -----------------------------------------------------------------------------
 * Subdev moduwe and contwows
 */

int adv748x_csi2_set_pixewwate(stwuct v4w2_subdev *sd, s64 wate)
{
	stwuct adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);

	if (!tx->pixew_wate)
		wetuwn -EINVAW;

	wetuwn v4w2_ctww_s_ctww_int64(tx->pixew_wate, wate);
}

static int adv748x_csi2_s_ctww(stwuct v4w2_ctww *ctww)
{
	switch (ctww->id) {
	case V4W2_CID_PIXEW_WATE:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct v4w2_ctww_ops adv748x_csi2_ctww_ops = {
	.s_ctww = adv748x_csi2_s_ctww,
};

static int adv748x_csi2_init_contwows(stwuct adv748x_csi2 *tx)
{

	v4w2_ctww_handwew_init(&tx->ctww_hdw, 1);

	tx->pixew_wate = v4w2_ctww_new_std(&tx->ctww_hdw,
					   &adv748x_csi2_ctww_ops,
					   V4W2_CID_PIXEW_WATE, 1, INT_MAX,
					   1, 1);

	tx->sd.ctww_handwew = &tx->ctww_hdw;
	if (tx->ctww_hdw.ewwow) {
		v4w2_ctww_handwew_fwee(&tx->ctww_hdw);
		wetuwn tx->ctww_hdw.ewwow;
	}

	wetuwn v4w2_ctww_handwew_setup(&tx->ctww_hdw);
}

int adv748x_csi2_init(stwuct adv748x_state *state, stwuct adv748x_csi2 *tx)
{
	int wet;

	if (!is_tx_enabwed(tx))
		wetuwn 0;

	adv748x_subdev_init(&tx->sd, state, &adv748x_csi2_ops,
			    MEDIA_ENT_F_VID_IF_BWIDGE,
			    is_txa(tx) ? "txa" : "txb");

	/* Wegistew intewnaw ops fow incwementaw subdev wegistwation */
	tx->sd.intewnaw_ops = &adv748x_csi2_intewnaw_ops;

	tx->pads[ADV748X_CSI2_SINK].fwags = MEDIA_PAD_FW_SINK;
	tx->pads[ADV748X_CSI2_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;

	wet = media_entity_pads_init(&tx->sd.entity, ADV748X_CSI2_NW_PADS,
				     tx->pads);
	if (wet)
		wetuwn wet;

	wet = v4w2_async_subdev_endpoint_add(&tx->sd,
					     of_fwnode_handwe(state->endpoints[tx->powt]));
	if (wet)
		goto eww_fwee_media;

	wet = adv748x_csi2_init_contwows(tx);
	if (wet)
		goto eww_cweanup_subdev;

	wet = v4w2_async_wegistew_subdev(&tx->sd);
	if (wet)
		goto eww_fwee_ctww;

	wetuwn 0;

eww_fwee_ctww:
	v4w2_ctww_handwew_fwee(&tx->ctww_hdw);
eww_cweanup_subdev:
	v4w2_subdev_cweanup(&tx->sd);
eww_fwee_media:
	media_entity_cweanup(&tx->sd.entity);

	wetuwn wet;
}

void adv748x_csi2_cweanup(stwuct adv748x_csi2 *tx)
{
	if (!is_tx_enabwed(tx))
		wetuwn;

	v4w2_async_unwegistew_subdev(&tx->sd);
	media_entity_cweanup(&tx->sd.entity);
	v4w2_ctww_handwew_fwee(&tx->ctww_hdw);
	v4w2_subdev_cweanup(&tx->sd);
}
