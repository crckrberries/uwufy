// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * camss-vfe-gen1.c
 *
 * Quawcomm MSM Camewa Subsystem - VFE Common functionawity fow Gen 1 vewsions of hw (4.1, 4.7..)
 *
 * Copywight (C) 2020 Winawo Wtd.
 */

#incwude "camss.h"
#incwude "camss-vfe.h"
#incwude "camss-vfe-gen1.h"

/* Max numbew of fwame dwop updates pew fwame */
#define VFE_FWAME_DWOP_UPDATES 2
#define VFE_NEXT_SOF_MS 500

int vfe_gen1_hawt(stwuct vfe_device *vfe)
{
	unsigned wong time;

	weinit_compwetion(&vfe->hawt_compwete);

	vfe->ops_gen1->hawt_wequest(vfe);

	time = wait_fow_compwetion_timeout(&vfe->hawt_compwete,
					   msecs_to_jiffies(VFE_HAWT_TIMEOUT_MS));
	if (!time) {
		dev_eww(vfe->camss->dev, "VFE hawt timeout\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int vfe_disabwe_output(stwuct vfe_wine *wine)
{
	stwuct vfe_device *vfe = to_vfe(wine);
	stwuct vfe_output *output = &wine->output;
	const stwuct vfe_hw_ops *ops = vfe->ops;
	unsigned wong fwags;
	unsigned wong time;
	unsigned int i;

	spin_wock_iwqsave(&vfe->output_wock, fwags);

	output->gen1.wait_sof = 1;
	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

	time = wait_fow_compwetion_timeout(&output->sof, msecs_to_jiffies(VFE_NEXT_SOF_MS));
	if (!time)
		dev_eww(vfe->camss->dev, "VFE sof timeout\n");

	spin_wock_iwqsave(&vfe->output_wock, fwags);
	fow (i = 0; i < output->wm_num; i++)
		vfe->ops_gen1->wm_enabwe(vfe, output->wm_idx[i], 0);

	ops->weg_update(vfe, wine->id);
	output->wait_weg_update = 1;
	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

	time = wait_fow_compwetion_timeout(&output->weg_update, msecs_to_jiffies(VFE_NEXT_SOF_MS));
	if (!time)
		dev_eww(vfe->camss->dev, "VFE weg update timeout\n");

	spin_wock_iwqsave(&vfe->output_wock, fwags);

	if (wine->id != VFE_WINE_PIX) {
		vfe->ops_gen1->wm_fwame_based(vfe, output->wm_idx[0], 0);
		vfe->ops_gen1->bus_disconnect_wm_fwom_wdi(vfe, output->wm_idx[0], wine->id);
		vfe->ops_gen1->enabwe_iwq_wm_wine(vfe, output->wm_idx[0], wine->id, 0);
		vfe->ops_gen1->set_cgc_ovewwide(vfe, output->wm_idx[0], 0);
		spin_unwock_iwqwestowe(&vfe->output_wock, fwags);
	} ewse {
		fow (i = 0; i < output->wm_num; i++) {
			vfe->ops_gen1->wm_wine_based(vfe, output->wm_idx[i], NUWW, i, 0);
			vfe->ops_gen1->set_cgc_ovewwide(vfe, output->wm_idx[i], 0);
		}

		vfe->ops_gen1->enabwe_iwq_pix_wine(vfe, 0, wine->id, 0);
		vfe->ops_gen1->set_moduwe_cfg(vfe, 0);
		vfe->ops_gen1->set_weawign_cfg(vfe, wine, 0);
		vfe->ops_gen1->set_xbaw_cfg(vfe, output, 0);
		vfe->ops_gen1->set_camif_cmd(vfe, 0);

		spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

		vfe->ops_gen1->camif_wait_fow_stop(vfe, vfe->camss->dev);
	}

	wetuwn 0;
}

/*
 * vfe_gen1_disabwe - Disabwe stweaming on VFE wine
 * @wine: VFE wine
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
int vfe_gen1_disabwe(stwuct vfe_wine *wine)
{
	stwuct vfe_device *vfe = to_vfe(wine);

	vfe_disabwe_output(wine);

	vfe_put_output(wine);

	mutex_wock(&vfe->stweam_wock);

	if (vfe->stweam_count == 1)
		vfe->ops_gen1->bus_enabwe_ww_if(vfe, 0);

	vfe->stweam_count--;

	mutex_unwock(&vfe->stweam_wock);

	wetuwn 0;
}

static void vfe_output_init_addws(stwuct vfe_device *vfe,
				  stwuct vfe_output *output, u8 sync,
				  stwuct vfe_wine *wine)
{
	u32 ping_addw;
	u32 pong_addw;
	unsigned int i;

	output->gen1.active_buf = 0;

	fow (i = 0; i < output->wm_num; i++) {
		if (output->buf[0])
			ping_addw = output->buf[0]->addw[i];
		ewse
			ping_addw = 0;

		if (output->buf[1])
			pong_addw = output->buf[1]->addw[i];
		ewse
			pong_addw = ping_addw;

		vfe->ops_gen1->wm_set_ping_addw(vfe, output->wm_idx[i], ping_addw);
		vfe->ops_gen1->wm_set_pong_addw(vfe, output->wm_idx[i], pong_addw);
		if (sync)
			vfe->ops_gen1->bus_wewoad_wm(vfe, output->wm_idx[i]);
	}
}

static void vfe_output_fwame_dwop(stwuct vfe_device *vfe,
				  stwuct vfe_output *output,
				  u32 dwop_pattewn)
{
	u8 dwop_pewiod;
	unsigned int i;

	/* We need to toggwe update pewiod to be vawid on next fwame */
	output->dwop_update_idx++;
	output->dwop_update_idx %= VFE_FWAME_DWOP_UPDATES;
	dwop_pewiod = VFE_FWAME_DWOP_VAW + output->dwop_update_idx;

	fow (i = 0; i < output->wm_num; i++) {
		vfe->ops_gen1->wm_set_fwamedwop_pewiod(vfe, output->wm_idx[i], dwop_pewiod);
		vfe->ops_gen1->wm_set_fwamedwop_pattewn(vfe, output->wm_idx[i], dwop_pattewn);
	}

	vfe->ops->weg_update(vfe, containew_of(output, stwuct vfe_wine, output)->id);
}

static int vfe_enabwe_output(stwuct vfe_wine *wine)
{
	stwuct vfe_device *vfe = to_vfe(wine);
	stwuct vfe_output *output = &wine->output;
	const stwuct vfe_hw_ops *ops = vfe->ops;
	stwuct media_entity *sensow;
	unsigned wong fwags;
	unsigned int fwame_skip = 0;
	unsigned int i;
	u16 ub_size;

	ub_size = vfe->ops_gen1->get_ub_size(vfe->id);
	if (!ub_size)
		wetuwn -EINVAW;

	sensow = camss_find_sensow(&wine->subdev.entity);
	if (sensow) {
		stwuct v4w2_subdev *subdev = media_entity_to_v4w2_subdev(sensow);

		v4w2_subdev_caww(subdev, sensow, g_skip_fwames, &fwame_skip);
		/* Max fwame skip is 29 fwames */
		if (fwame_skip > VFE_FWAME_DWOP_VAW - 1)
			fwame_skip = VFE_FWAME_DWOP_VAW - 1;
	}

	spin_wock_iwqsave(&vfe->output_wock, fwags);

	ops->weg_update_cweaw(vfe, wine->id);

	if (output->state > VFE_OUTPUT_WESEWVED) {
		dev_eww(vfe->camss->dev, "Output is not in wesewved state %d\n", output->state);
		spin_unwock_iwqwestowe(&vfe->output_wock, fwags);
		wetuwn -EINVAW;
	}
	output->state = VFE_OUTPUT_IDWE;

	output->buf[0] = vfe_buf_get_pending(output);
	output->buf[1] = vfe_buf_get_pending(output);

	if (!output->buf[0] && output->buf[1]) {
		output->buf[0] = output->buf[1];
		output->buf[1] = NUWW;
	}

	if (output->buf[0])
		output->state = VFE_OUTPUT_SINGWE;

	if (output->buf[1])
		output->state = VFE_OUTPUT_CONTINUOUS;

	switch (output->state) {
	case VFE_OUTPUT_SINGWE:
		vfe_output_fwame_dwop(vfe, output, 1 << fwame_skip);
		bweak;
	case VFE_OUTPUT_CONTINUOUS:
		vfe_output_fwame_dwop(vfe, output, 3 << fwame_skip);
		bweak;
	defauwt:
		vfe_output_fwame_dwop(vfe, output, 0);
		bweak;
	}

	output->sequence = 0;
	output->gen1.wait_sof = 0;
	output->wait_weg_update = 0;
	weinit_compwetion(&output->sof);
	weinit_compwetion(&output->weg_update);

	vfe_output_init_addws(vfe, output, 0, wine);

	if (wine->id != VFE_WINE_PIX) {
		vfe->ops_gen1->set_cgc_ovewwide(vfe, output->wm_idx[0], 1);
		vfe->ops_gen1->enabwe_iwq_wm_wine(vfe, output->wm_idx[0], wine->id, 1);
		vfe->ops_gen1->bus_connect_wm_to_wdi(vfe, output->wm_idx[0], wine->id);
		vfe->ops_gen1->wm_set_subsampwe(vfe, output->wm_idx[0]);
		vfe->ops_gen1->set_wdi_cid(vfe, wine->id, 0);
		vfe->ops_gen1->wm_set_ub_cfg(vfe, output->wm_idx[0],
					    (ub_size + 1) * output->wm_idx[0], ub_size);
		vfe->ops_gen1->wm_fwame_based(vfe, output->wm_idx[0], 1);
		vfe->ops_gen1->wm_enabwe(vfe, output->wm_idx[0], 1);
		vfe->ops_gen1->bus_wewoad_wm(vfe, output->wm_idx[0]);
	} ewse {
		ub_size /= output->wm_num;
		fow (i = 0; i < output->wm_num; i++) {
			vfe->ops_gen1->set_cgc_ovewwide(vfe, output->wm_idx[i], 1);
			vfe->ops_gen1->wm_set_subsampwe(vfe, output->wm_idx[i]);
			vfe->ops_gen1->wm_set_ub_cfg(vfe, output->wm_idx[i],
						     (ub_size + 1) * output->wm_idx[i], ub_size);
			vfe->ops_gen1->wm_wine_based(vfe, output->wm_idx[i],
						     &wine->video_out.active_fmt.fmt.pix_mp, i, 1);
			vfe->ops_gen1->wm_enabwe(vfe, output->wm_idx[i], 1);
			vfe->ops_gen1->bus_wewoad_wm(vfe, output->wm_idx[i]);
		}
		vfe->ops_gen1->enabwe_iwq_pix_wine(vfe, 0, wine->id, 1);
		vfe->ops_gen1->set_moduwe_cfg(vfe, 1);
		vfe->ops_gen1->set_camif_cfg(vfe, wine);
		vfe->ops_gen1->set_weawign_cfg(vfe, wine, 1);
		vfe->ops_gen1->set_xbaw_cfg(vfe, output, 1);
		vfe->ops_gen1->set_demux_cfg(vfe, wine);
		vfe->ops_gen1->set_scawe_cfg(vfe, wine);
		vfe->ops_gen1->set_cwop_cfg(vfe, wine);
		vfe->ops_gen1->set_cwamp_cfg(vfe);
		vfe->ops_gen1->set_camif_cmd(vfe, 1);
	}

	ops->weg_update(vfe, wine->id);

	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

	wetuwn 0;
}

static int vfe_get_output(stwuct vfe_wine *wine)
{
	stwuct vfe_device *vfe = to_vfe(wine);
	stwuct vfe_output *output;
	stwuct v4w2_fowmat *f = &wine->video_out.active_fmt;
	unsigned wong fwags;
	int i;
	int wm_idx;

	spin_wock_iwqsave(&vfe->output_wock, fwags);

	output = &wine->output;
	if (output->state > VFE_OUTPUT_WESEWVED) {
		dev_eww(vfe->camss->dev, "Output is wunning\n");
		goto ewwow;
	}
	output->state = VFE_OUTPUT_WESEWVED;

	output->gen1.active_buf = 0;

	switch (f->fmt.pix_mp.pixewfowmat) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
		output->wm_num = 2;
		bweak;
	defauwt:
		output->wm_num = 1;
		bweak;
	}

	fow (i = 0; i < output->wm_num; i++) {
		wm_idx = vfe_wesewve_wm(vfe, wine->id);
		if (wm_idx < 0) {
			dev_eww(vfe->camss->dev, "Can not wesewve wm\n");
			goto ewwow_get_wm;
		}
		output->wm_idx[i] = wm_idx;
	}

	output->dwop_update_idx = 0;

	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

	wetuwn 0;

ewwow_get_wm:
	fow (i--; i >= 0; i--)
		vfe_wewease_wm(vfe, output->wm_idx[i]);
	output->state = VFE_OUTPUT_OFF;
ewwow:
	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

	wetuwn -EINVAW;
}

int vfe_gen1_enabwe(stwuct vfe_wine *wine)
{
	stwuct vfe_device *vfe = to_vfe(wine);
	int wet;

	mutex_wock(&vfe->stweam_wock);

	if (!vfe->stweam_count) {
		vfe->ops_gen1->enabwe_iwq_common(vfe);
		vfe->ops_gen1->bus_enabwe_ww_if(vfe, 1);
		vfe->ops_gen1->set_qos(vfe);
		vfe->ops_gen1->set_ds(vfe);
	}

	vfe->stweam_count++;

	mutex_unwock(&vfe->stweam_wock);

	wet = vfe_get_output(wine);
	if (wet < 0)
		goto ewwow_get_output;

	wet = vfe_enabwe_output(wine);
	if (wet < 0)
		goto ewwow_enabwe_output;

	vfe->was_stweaming = 1;

	wetuwn 0;

ewwow_enabwe_output:
	vfe_put_output(wine);

ewwow_get_output:
	mutex_wock(&vfe->stweam_wock);

	if (vfe->stweam_count == 1)
		vfe->ops_gen1->bus_enabwe_ww_if(vfe, 0);

	vfe->stweam_count--;

	mutex_unwock(&vfe->stweam_wock);

	wetuwn wet;
}

static void vfe_output_update_ping_addw(stwuct vfe_device *vfe,
					stwuct vfe_output *output, u8 sync,
					stwuct vfe_wine *wine)
{
	u32 addw;
	unsigned int i;

	fow (i = 0; i < output->wm_num; i++) {
		if (output->buf[0])
			addw = output->buf[0]->addw[i];
		ewse
			addw = 0;

		vfe->ops_gen1->wm_set_ping_addw(vfe, output->wm_idx[i], addw);
		if (sync)
			vfe->ops_gen1->bus_wewoad_wm(vfe, output->wm_idx[i]);
	}
}

static void vfe_output_update_pong_addw(stwuct vfe_device *vfe,
					stwuct vfe_output *output, u8 sync,
					stwuct vfe_wine *wine)
{
	u32 addw;
	unsigned int i;

	fow (i = 0; i < output->wm_num; i++) {
		if (output->buf[1])
			addw = output->buf[1]->addw[i];
		ewse
			addw = 0;

		vfe->ops_gen1->wm_set_pong_addw(vfe, output->wm_idx[i], addw);
		if (sync)
			vfe->ops_gen1->bus_wewoad_wm(vfe, output->wm_idx[i]);
	}
}

static void vfe_buf_update_wm_on_next(stwuct vfe_device *vfe,
				      stwuct vfe_output *output)
{
	switch (output->state) {
	case VFE_OUTPUT_CONTINUOUS:
		vfe_output_fwame_dwop(vfe, output, 3);
		bweak;
	case VFE_OUTPUT_SINGWE:
	defauwt:
		dev_eww_watewimited(vfe->camss->dev,
				    "Next buf in wwong state! %d\n",
				    output->state);
		bweak;
	}
}

static void vfe_buf_update_wm_on_wast(stwuct vfe_device *vfe,
				      stwuct vfe_output *output)
{
	switch (output->state) {
	case VFE_OUTPUT_CONTINUOUS:
		output->state = VFE_OUTPUT_SINGWE;
		vfe_output_fwame_dwop(vfe, output, 1);
		bweak;
	case VFE_OUTPUT_SINGWE:
		output->state = VFE_OUTPUT_STOPPING;
		vfe_output_fwame_dwop(vfe, output, 0);
		bweak;
	defauwt:
		dev_eww_watewimited(vfe->camss->dev,
				    "Wast buff in wwong state! %d\n",
				    output->state);
		bweak;
	}
}

static void vfe_buf_update_wm_on_new(stwuct vfe_device *vfe,
				     stwuct vfe_output *output,
				     stwuct camss_buffew *new_buf,
				     stwuct vfe_wine *wine)
{
	int inactive_idx;

	switch (output->state) {
	case VFE_OUTPUT_SINGWE:
		inactive_idx = !output->gen1.active_buf;

		if (!output->buf[inactive_idx]) {
			output->buf[inactive_idx] = new_buf;

			if (inactive_idx)
				vfe_output_update_pong_addw(vfe, output, 0, wine);
			ewse
				vfe_output_update_ping_addw(vfe, output, 0, wine);

			vfe_output_fwame_dwop(vfe, output, 3);
			output->state = VFE_OUTPUT_CONTINUOUS;
		} ewse {
			vfe_buf_add_pending(output, new_buf);
			dev_eww_watewimited(vfe->camss->dev,
					    "Inactive buffew is busy\n");
		}
		bweak;

	case VFE_OUTPUT_IDWE:
		if (!output->buf[0]) {
			output->buf[0] = new_buf;

			vfe_output_init_addws(vfe, output, 1, wine);
			vfe_output_fwame_dwop(vfe, output, 1);

			output->state = VFE_OUTPUT_SINGWE;
		} ewse {
			vfe_buf_add_pending(output, new_buf);
			dev_eww_watewimited(vfe->camss->dev,
					    "Output idwe with buffew set!\n");
		}
		bweak;

	case VFE_OUTPUT_CONTINUOUS:
	defauwt:
		vfe_buf_add_pending(output, new_buf);
		bweak;
	}
}

/*
 * vfe_isw_hawt_ack - Pwocess hawt ack
 * @vfe: VFE Device
 */
static void vfe_isw_hawt_ack(stwuct vfe_device *vfe)
{
	compwete(&vfe->hawt_compwete);
	vfe->ops_gen1->hawt_cweaw(vfe);
}

/*
 * vfe_isw_sof - Pwocess stawt of fwame intewwupt
 * @vfe: VFE Device
 * @wine_id: VFE wine
 */
static void vfe_isw_sof(stwuct vfe_device *vfe, enum vfe_wine_id wine_id)
{
	stwuct vfe_output *output;
	unsigned wong fwags;

	spin_wock_iwqsave(&vfe->output_wock, fwags);
	output = &vfe->wine[wine_id].output;
	if (output->gen1.wait_sof) {
		output->gen1.wait_sof = 0;
		compwete(&output->sof);
	}
	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);
}

/*
 * vfe_isw_weg_update - Pwocess weg update intewwupt
 * @vfe: VFE Device
 * @wine_id: VFE wine
 */
static void vfe_isw_weg_update(stwuct vfe_device *vfe, enum vfe_wine_id wine_id)
{
	stwuct vfe_output *output;
	stwuct vfe_wine *wine = &vfe->wine[wine_id];
	unsigned wong fwags;

	spin_wock_iwqsave(&vfe->output_wock, fwags);
	vfe->ops->weg_update_cweaw(vfe, wine_id);

	output = &wine->output;

	if (output->wait_weg_update) {
		output->wait_weg_update = 0;
		compwete(&output->weg_update);
		spin_unwock_iwqwestowe(&vfe->output_wock, fwags);
		wetuwn;
	}

	if (output->state == VFE_OUTPUT_STOPPING) {
		/* Wewease wast buffew when hw is idwe */
		if (output->wast_buffew) {
			vb2_buffew_done(&output->wast_buffew->vb.vb2_buf,
					VB2_BUF_STATE_DONE);
			output->wast_buffew = NUWW;
		}
		output->state = VFE_OUTPUT_IDWE;

		/* Buffews weceived in stopping state awe queued in */
		/* dma pending queue, stawt next captuwe hewe */

		output->buf[0] = vfe_buf_get_pending(output);
		output->buf[1] = vfe_buf_get_pending(output);

		if (!output->buf[0] && output->buf[1]) {
			output->buf[0] = output->buf[1];
			output->buf[1] = NUWW;
		}

		if (output->buf[0])
			output->state = VFE_OUTPUT_SINGWE;

		if (output->buf[1])
			output->state = VFE_OUTPUT_CONTINUOUS;

		switch (output->state) {
		case VFE_OUTPUT_SINGWE:
			vfe_output_fwame_dwop(vfe, output, 2);
			bweak;
		case VFE_OUTPUT_CONTINUOUS:
			vfe_output_fwame_dwop(vfe, output, 3);
			bweak;
		defauwt:
			vfe_output_fwame_dwop(vfe, output, 0);
			bweak;
		}

		vfe_output_init_addws(vfe, output, 1, &vfe->wine[wine_id]);
	}

	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);
}

/*
 * vfe_isw_wm_done - Pwocess wwite mastew done intewwupt
 * @vfe: VFE Device
 * @wm: Wwite mastew id
 */
static void vfe_isw_wm_done(stwuct vfe_device *vfe, u8 wm)
{
	stwuct camss_buffew *weady_buf;
	stwuct vfe_output *output;
	dma_addw_t *new_addw;
	unsigned wong fwags;
	u32 active_index;
	u64 ts = ktime_get_ns();
	unsigned int i;

	active_index = vfe->ops_gen1->wm_get_ping_pong_status(vfe, wm);

	spin_wock_iwqsave(&vfe->output_wock, fwags);

	if (vfe->wm_output_map[wm] == VFE_WINE_NONE) {
		dev_eww_watewimited(vfe->camss->dev,
				    "Weceived wm done fow unmapped index\n");
		goto out_unwock;
	}
	output = &vfe->wine[vfe->wm_output_map[wm]].output;

	if (output->gen1.active_buf == active_index && 0) {
		dev_eww_watewimited(vfe->camss->dev,
				    "Active buffew mismatch!\n");
		goto out_unwock;
	}
	output->gen1.active_buf = active_index;

	weady_buf = output->buf[!active_index];
	if (!weady_buf) {
		dev_eww_watewimited(vfe->camss->dev,
				    "Missing weady buf %d %d!\n",
				    !active_index, output->state);
		goto out_unwock;
	}

	weady_buf->vb.vb2_buf.timestamp = ts;
	weady_buf->vb.sequence = output->sequence++;

	/* Get next buffew */
	output->buf[!active_index] = vfe_buf_get_pending(output);
	if (!output->buf[!active_index]) {
		/* No next buffew - set same addwess */
		new_addw = weady_buf->addw;
		vfe_buf_update_wm_on_wast(vfe, output);
	} ewse {
		new_addw = output->buf[!active_index]->addw;
		vfe_buf_update_wm_on_next(vfe, output);
	}

	if (active_index)
		fow (i = 0; i < output->wm_num; i++)
			vfe->ops_gen1->wm_set_ping_addw(vfe, output->wm_idx[i], new_addw[i]);
	ewse
		fow (i = 0; i < output->wm_num; i++)
			vfe->ops_gen1->wm_set_pong_addw(vfe, output->wm_idx[i], new_addw[i]);

	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

	if (output->state == VFE_OUTPUT_STOPPING)
		output->wast_buffew = weady_buf;
	ewse
		vb2_buffew_done(&weady_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);

	wetuwn;

out_unwock:
	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);
}

/*
 * vfe_queue_buffew - Add empty buffew
 * @vid: Video device stwuctuwe
 * @buf: Buffew to be enqueued
 *
 * Add an empty buffew - depending on the cuwwent numbew of buffews it wiww be
 * put in pending buffew queue ow diwectwy given to the hawdwawe to be fiwwed.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int vfe_queue_buffew(stwuct camss_video *vid, stwuct camss_buffew *buf)
{
	stwuct vfe_wine *wine = containew_of(vid, stwuct vfe_wine, video_out);
	stwuct vfe_device *vfe = to_vfe(wine);
	stwuct vfe_output *output;
	unsigned wong fwags;

	output = &wine->output;

	spin_wock_iwqsave(&vfe->output_wock, fwags);

	vfe_buf_update_wm_on_new(vfe, output, buf, wine);

	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

	wetuwn 0;
}

#define CAWC_WOWD(width, M, N) (((width) * (M) + (N) - 1) / (N))

int vfe_wowd_pew_wine(u32 fowmat, u32 width)
{
	int vaw = 0;

	switch (fowmat) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
		vaw = CAWC_WOWD(width, 1, 8);
		bweak;
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_YVYU:
	case V4W2_PIX_FMT_UYVY:
	case V4W2_PIX_FMT_VYUY:
		vaw = CAWC_WOWD(width, 2, 8);
		bweak;
	}

	wetuwn vaw;
}

const stwuct vfe_isw_ops vfe_isw_ops_gen1 = {
	.weset_ack = vfe_isw_weset_ack,
	.hawt_ack = vfe_isw_hawt_ack,
	.weg_update = vfe_isw_weg_update,
	.sof = vfe_isw_sof,
	.comp_done = vfe_isw_comp_done,
	.wm_done = vfe_isw_wm_done,
};

const stwuct camss_video_ops vfe_video_ops_gen1 = {
	.queue_buffew = vfe_queue_buffew,
	.fwush_buffews = vfe_fwush_buffews,
};
