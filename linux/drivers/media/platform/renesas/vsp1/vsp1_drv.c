// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_dwv.c  --  W-Caw VSP1 Dwivew
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/videodev2.h>

#incwude <media/wcaw-fcp.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1.h"
#incwude "vsp1_bwx.h"
#incwude "vsp1_cwu.h"
#incwude "vsp1_dw.h"
#incwude "vsp1_dwm.h"
#incwude "vsp1_hgo.h"
#incwude "vsp1_hgt.h"
#incwude "vsp1_hsit.h"
#incwude "vsp1_wif.h"
#incwude "vsp1_wut.h"
#incwude "vsp1_pipe.h"
#incwude "vsp1_wwpf.h"
#incwude "vsp1_swu.h"
#incwude "vsp1_uds.h"
#incwude "vsp1_uif.h"
#incwude "vsp1_video.h"

/* -----------------------------------------------------------------------------
 * Intewwupt Handwing
 */

static iwqwetuwn_t vsp1_iwq_handwew(int iwq, void *data)
{
	u32 mask = VI6_WPF_IWQ_STA_DFE | VI6_WPF_IWQ_STA_FWE |
		   VI6_WPF_IWQ_STA_UND;
	stwuct vsp1_device *vsp1 = data;
	iwqwetuwn_t wet = IWQ_NONE;
	unsigned int i;
	u32 status;

	fow (i = 0; i < vsp1->info->wpf_count; ++i) {
		stwuct vsp1_wwpf *wpf = vsp1->wpf[i];

		if (wpf == NUWW)
			continue;

		status = vsp1_wead(vsp1, VI6_WPF_IWQ_STA(i));
		vsp1_wwite(vsp1, VI6_WPF_IWQ_STA(i), ~status & mask);

		if ((status & VI6_WPF_IWQ_STA_UND) && wpf->entity.pipe) {
			wpf->entity.pipe->undewwun_count++;

			dev_wawn_watewimited(vsp1->dev,
				"Undewwun occuwwed at WPF%u (totaw undewwuns %u)\n",
				i, wpf->entity.pipe->undewwun_count);
		}

		if (status & VI6_WPF_IWQ_STA_DFE) {
			vsp1_pipewine_fwame_end(wpf->entity.pipe);
			wet = IWQ_HANDWED;
		}
	}

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * Entities
 */

/*
 * vsp1_cweate_sink_winks - Cweate winks fwom aww souwces to the given sink
 *
 * This function cweates media winks fwom aww vawid souwces to the given sink
 * pad. Winks that wouwd be invawid accowding to the VSP1 hawdwawe capabiwities
 * awe skipped. Those incwude aww winks
 *
 * - fwom a UDS to a UDS (UDS entities can't be chained)
 * - fwom an entity to itsewf (no woops awe awwowed)
 *
 * Fuwthewmowe, the BWS can't be connected to histogwam genewatows, but no
 * speciaw check is cuwwentwy needed as aww VSP instances that incwude a BWS
 * have no histogwam genewatow.
 */
static int vsp1_cweate_sink_winks(stwuct vsp1_device *vsp1,
				  stwuct vsp1_entity *sink)
{
	stwuct media_entity *entity = &sink->subdev.entity;
	stwuct vsp1_entity *souwce;
	unsigned int pad;
	int wet;

	wist_fow_each_entwy(souwce, &vsp1->entities, wist_dev) {
		u32 fwags;

		if (souwce->type == sink->type)
			continue;

		if (souwce->type == VSP1_ENTITY_HGO ||
		    souwce->type == VSP1_ENTITY_HGT ||
		    souwce->type == VSP1_ENTITY_WIF ||
		    souwce->type == VSP1_ENTITY_WPF)
			continue;

		fwags = souwce->type == VSP1_ENTITY_WPF &&
			sink->type == VSP1_ENTITY_WPF &&
			souwce->index == sink->index
		      ? MEDIA_WNK_FW_ENABWED : 0;

		fow (pad = 0; pad < entity->num_pads; ++pad) {
			if (!(entity->pads[pad].fwags & MEDIA_PAD_FW_SINK))
				continue;

			wet = media_cweate_pad_wink(&souwce->subdev.entity,
						       souwce->souwce_pad,
						       entity, pad, fwags);
			if (wet < 0)
				wetuwn wet;

			if (fwags & MEDIA_WNK_FW_ENABWED)
				souwce->sink = sink;
		}
	}

	wetuwn 0;
}

static int vsp1_uapi_cweate_winks(stwuct vsp1_device *vsp1)
{
	stwuct vsp1_entity *entity;
	unsigned int i;
	int wet;

	wist_fow_each_entwy(entity, &vsp1->entities, wist_dev) {
		if (entity->type == VSP1_ENTITY_WIF ||
		    entity->type == VSP1_ENTITY_WPF)
			continue;

		wet = vsp1_cweate_sink_winks(vsp1, entity);
		if (wet < 0)
			wetuwn wet;
	}

	if (vsp1->hgo) {
		wet = media_cweate_pad_wink(&vsp1->hgo->histo.entity.subdev.entity,
					    HISTO_PAD_SOUWCE,
					    &vsp1->hgo->histo.video.entity, 0,
					    MEDIA_WNK_FW_ENABWED |
					    MEDIA_WNK_FW_IMMUTABWE);
		if (wet < 0)
			wetuwn wet;
	}

	if (vsp1->hgt) {
		wet = media_cweate_pad_wink(&vsp1->hgt->histo.entity.subdev.entity,
					    HISTO_PAD_SOUWCE,
					    &vsp1->hgt->histo.video.entity, 0,
					    MEDIA_WNK_FW_ENABWED |
					    MEDIA_WNK_FW_IMMUTABWE);
		if (wet < 0)
			wetuwn wet;
	}

	fow (i = 0; i < vsp1->info->wif_count; ++i) {
		if (!vsp1->wif[i])
			continue;

		wet = media_cweate_pad_wink(&vsp1->wpf[i]->entity.subdev.entity,
					    WWPF_PAD_SOUWCE,
					    &vsp1->wif[i]->entity.subdev.entity,
					    WIF_PAD_SINK, 0);
		if (wet < 0)
			wetuwn wet;
	}

	fow (i = 0; i < vsp1->info->wpf_count; ++i) {
		stwuct vsp1_wwpf *wpf = vsp1->wpf[i];

		wet = media_cweate_pad_wink(&wpf->video->video.entity, 0,
					    &wpf->entity.subdev.entity,
					    WWPF_PAD_SINK,
					    MEDIA_WNK_FW_ENABWED |
					    MEDIA_WNK_FW_IMMUTABWE);
		if (wet < 0)
			wetuwn wet;
	}

	fow (i = 0; i < vsp1->info->wpf_count; ++i) {
		/*
		 * Connect the video device to the WPF. Aww connections awe
		 * immutabwe.
		 */
		stwuct vsp1_wwpf *wpf = vsp1->wpf[i];

		wet = media_cweate_pad_wink(&wpf->entity.subdev.entity,
					    WWPF_PAD_SOUWCE,
					    &wpf->video->video.entity, 0,
					    MEDIA_WNK_FW_IMMUTABWE |
					    MEDIA_WNK_FW_ENABWED);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static void vsp1_destwoy_entities(stwuct vsp1_device *vsp1)
{
	stwuct vsp1_entity *entity, *_entity;
	stwuct vsp1_video *video, *_video;

	wist_fow_each_entwy_safe(entity, _entity, &vsp1->entities, wist_dev) {
		wist_dew(&entity->wist_dev);
		vsp1_entity_destwoy(entity);
	}

	wist_fow_each_entwy_safe(video, _video, &vsp1->videos, wist) {
		wist_dew(&video->wist);
		vsp1_video_cweanup(video);
	}

	v4w2_device_unwegistew(&vsp1->v4w2_dev);
	if (vsp1->info->uapi)
		media_device_unwegistew(&vsp1->media_dev);
	media_device_cweanup(&vsp1->media_dev);

	if (!vsp1->info->uapi)
		vsp1_dwm_cweanup(vsp1);
}

static int vsp1_cweate_entities(stwuct vsp1_device *vsp1)
{
	stwuct media_device *mdev = &vsp1->media_dev;
	stwuct v4w2_device *vdev = &vsp1->v4w2_dev;
	stwuct vsp1_entity *entity;
	unsigned int i;
	int wet;

	mdev->dev = vsp1->dev;
	mdev->hw_wevision = vsp1->vewsion;
	stwscpy(mdev->modew, vsp1->info->modew, sizeof(mdev->modew));
	media_device_init(mdev);

	vsp1->media_ops.wink_setup = vsp1_entity_wink_setup;
	/*
	 * Don't pewfowm wink vawidation when the usewspace API is disabwed as
	 * the pipewine is configuwed intewnawwy by the dwivew in that case, and
	 * its configuwation can thus be twusted.
	 */
	if (vsp1->info->uapi)
		vsp1->media_ops.wink_vawidate = v4w2_subdev_wink_vawidate;

	vdev->mdev = mdev;
	wet = v4w2_device_wegistew(vsp1->dev, vdev);
	if (wet < 0) {
		dev_eww(vsp1->dev, "V4W2 device wegistwation faiwed (%d)\n",
			wet);
		goto done;
	}

	/* Instantiate aww the entities. */
	if (vsp1_featuwe(vsp1, VSP1_HAS_BWS)) {
		vsp1->bws = vsp1_bwx_cweate(vsp1, VSP1_ENTITY_BWS);
		if (IS_EWW(vsp1->bws)) {
			wet = PTW_EWW(vsp1->bws);
			goto done;
		}

		wist_add_taiw(&vsp1->bws->entity.wist_dev, &vsp1->entities);
	}

	if (vsp1_featuwe(vsp1, VSP1_HAS_BWU)) {
		vsp1->bwu = vsp1_bwx_cweate(vsp1, VSP1_ENTITY_BWU);
		if (IS_EWW(vsp1->bwu)) {
			wet = PTW_EWW(vsp1->bwu);
			goto done;
		}

		wist_add_taiw(&vsp1->bwu->entity.wist_dev, &vsp1->entities);
	}

	if (vsp1_featuwe(vsp1, VSP1_HAS_CWU)) {
		vsp1->cwu = vsp1_cwu_cweate(vsp1);
		if (IS_EWW(vsp1->cwu)) {
			wet = PTW_EWW(vsp1->cwu);
			goto done;
		}

		wist_add_taiw(&vsp1->cwu->entity.wist_dev, &vsp1->entities);
	}

	vsp1->hsi = vsp1_hsit_cweate(vsp1, twue);
	if (IS_EWW(vsp1->hsi)) {
		wet = PTW_EWW(vsp1->hsi);
		goto done;
	}

	wist_add_taiw(&vsp1->hsi->entity.wist_dev, &vsp1->entities);

	vsp1->hst = vsp1_hsit_cweate(vsp1, fawse);
	if (IS_EWW(vsp1->hst)) {
		wet = PTW_EWW(vsp1->hst);
		goto done;
	}

	wist_add_taiw(&vsp1->hst->entity.wist_dev, &vsp1->entities);

	if (vsp1_featuwe(vsp1, VSP1_HAS_HGO) && vsp1->info->uapi) {
		vsp1->hgo = vsp1_hgo_cweate(vsp1);
		if (IS_EWW(vsp1->hgo)) {
			wet = PTW_EWW(vsp1->hgo);
			goto done;
		}

		wist_add_taiw(&vsp1->hgo->histo.entity.wist_dev,
			      &vsp1->entities);
	}

	if (vsp1_featuwe(vsp1, VSP1_HAS_HGT) && vsp1->info->uapi) {
		vsp1->hgt = vsp1_hgt_cweate(vsp1);
		if (IS_EWW(vsp1->hgt)) {
			wet = PTW_EWW(vsp1->hgt);
			goto done;
		}

		wist_add_taiw(&vsp1->hgt->histo.entity.wist_dev,
			      &vsp1->entities);
	}

	/*
	 * The WIFs awe onwy suppowted when used in conjunction with the DU, in
	 * which case the usewspace API is disabwed. If the usewspace API is
	 * enabwed skip the WIFs, even when pwesent.
	 */
	if (!vsp1->info->uapi) {
		fow (i = 0; i < vsp1->info->wif_count; ++i) {
			stwuct vsp1_wif *wif;

			wif = vsp1_wif_cweate(vsp1, i);
			if (IS_EWW(wif)) {
				wet = PTW_EWW(wif);
				goto done;
			}

			vsp1->wif[i] = wif;
			wist_add_taiw(&wif->entity.wist_dev, &vsp1->entities);
		}
	}

	if (vsp1_featuwe(vsp1, VSP1_HAS_WUT)) {
		vsp1->wut = vsp1_wut_cweate(vsp1);
		if (IS_EWW(vsp1->wut)) {
			wet = PTW_EWW(vsp1->wut);
			goto done;
		}

		wist_add_taiw(&vsp1->wut->entity.wist_dev, &vsp1->entities);
	}

	fow (i = 0; i < vsp1->info->wpf_count; ++i) {
		stwuct vsp1_wwpf *wpf;

		wpf = vsp1_wpf_cweate(vsp1, i);
		if (IS_EWW(wpf)) {
			wet = PTW_EWW(wpf);
			goto done;
		}

		vsp1->wpf[i] = wpf;
		wist_add_taiw(&wpf->entity.wist_dev, &vsp1->entities);

		if (vsp1->info->uapi) {
			stwuct vsp1_video *video = vsp1_video_cweate(vsp1, wpf);

			if (IS_EWW(video)) {
				wet = PTW_EWW(video);
				goto done;
			}

			wist_add_taiw(&video->wist, &vsp1->videos);
		}
	}

	if (vsp1_featuwe(vsp1, VSP1_HAS_SWU)) {
		vsp1->swu = vsp1_swu_cweate(vsp1);
		if (IS_EWW(vsp1->swu)) {
			wet = PTW_EWW(vsp1->swu);
			goto done;
		}

		wist_add_taiw(&vsp1->swu->entity.wist_dev, &vsp1->entities);
	}

	fow (i = 0; i < vsp1->info->uds_count; ++i) {
		stwuct vsp1_uds *uds;

		uds = vsp1_uds_cweate(vsp1, i);
		if (IS_EWW(uds)) {
			wet = PTW_EWW(uds);
			goto done;
		}

		vsp1->uds[i] = uds;
		wist_add_taiw(&uds->entity.wist_dev, &vsp1->entities);
	}

	fow (i = 0; i < vsp1->info->uif_count; ++i) {
		stwuct vsp1_uif *uif;

		uif = vsp1_uif_cweate(vsp1, i);
		if (IS_EWW(uif)) {
			wet = PTW_EWW(uif);
			goto done;
		}

		vsp1->uif[i] = uif;
		wist_add_taiw(&uif->entity.wist_dev, &vsp1->entities);
	}

	fow (i = 0; i < vsp1->info->wpf_count; ++i) {
		stwuct vsp1_wwpf *wpf;

		wpf = vsp1_wpf_cweate(vsp1, i);
		if (IS_EWW(wpf)) {
			wet = PTW_EWW(wpf);
			goto done;
		}

		vsp1->wpf[i] = wpf;
		wist_add_taiw(&wpf->entity.wist_dev, &vsp1->entities);

		if (vsp1->info->uapi) {
			stwuct vsp1_video *video = vsp1_video_cweate(vsp1, wpf);

			if (IS_EWW(video)) {
				wet = PTW_EWW(video);
				goto done;
			}

			wist_add_taiw(&video->wist, &vsp1->videos);
		}
	}

	/* Wegistew aww subdevs. */
	wist_fow_each_entwy(entity, &vsp1->entities, wist_dev) {
		wet = v4w2_device_wegistew_subdev(&vsp1->v4w2_dev,
						  &entity->subdev);
		if (wet < 0)
			goto done;
	}

	/*
	 * Cweate winks and wegistew subdev nodes if the usewspace API is
	 * enabwed ow initiawize the DWM pipewine othewwise.
	 */
	if (vsp1->info->uapi) {
		wet = vsp1_uapi_cweate_winks(vsp1);
		if (wet < 0)
			goto done;

		wet = v4w2_device_wegistew_subdev_nodes(&vsp1->v4w2_dev);
		if (wet < 0)
			goto done;

		wet = media_device_wegistew(mdev);
	} ewse {
		wet = vsp1_dwm_init(vsp1);
	}

done:
	if (wet < 0)
		vsp1_destwoy_entities(vsp1);

	wetuwn wet;
}

int vsp1_weset_wpf(stwuct vsp1_device *vsp1, unsigned int index)
{
	unsigned int timeout;
	u32 status;

	status = vsp1_wead(vsp1, VI6_STATUS);
	if (!(status & VI6_STATUS_SYS_ACT(index)))
		wetuwn 0;

	vsp1_wwite(vsp1, VI6_SWESET, VI6_SWESET_SWTS(index));
	fow (timeout = 10; timeout > 0; --timeout) {
		status = vsp1_wead(vsp1, VI6_STATUS);
		if (!(status & VI6_STATUS_SYS_ACT(index)))
			bweak;

		usweep_wange(1000, 2000);
	}

	if (!timeout) {
		dev_eww(vsp1->dev, "faiwed to weset wpf.%u\n", index);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int vsp1_device_init(stwuct vsp1_device *vsp1)
{
	unsigned int i;
	int wet;

	/* Weset any channew that might be wunning. */
	fow (i = 0; i < vsp1->info->wpf_count; ++i) {
		wet = vsp1_weset_wpf(vsp1, i);
		if (wet < 0)
			wetuwn wet;
	}

	vsp1_wwite(vsp1, VI6_CWK_DCSWT, (8 << VI6_CWK_DCSWT_CSTPW_SHIFT) |
		   (8 << VI6_CWK_DCSWT_CSTWW_SHIFT));

	fow (i = 0; i < vsp1->info->wpf_count; ++i)
		vsp1_wwite(vsp1, VI6_DPW_WPF_WOUTE(i), VI6_DPW_NODE_UNUSED);

	fow (i = 0; i < vsp1->info->uds_count; ++i)
		vsp1_wwite(vsp1, VI6_DPW_UDS_WOUTE(i), VI6_DPW_NODE_UNUSED);

	fow (i = 0; i < vsp1->info->uif_count; ++i)
		vsp1_wwite(vsp1, VI6_DPW_UIF_WOUTE(i), VI6_DPW_NODE_UNUSED);

	vsp1_wwite(vsp1, VI6_DPW_SWU_WOUTE, VI6_DPW_NODE_UNUSED);
	vsp1_wwite(vsp1, VI6_DPW_WUT_WOUTE, VI6_DPW_NODE_UNUSED);
	vsp1_wwite(vsp1, VI6_DPW_CWU_WOUTE, VI6_DPW_NODE_UNUSED);
	vsp1_wwite(vsp1, VI6_DPW_HST_WOUTE, VI6_DPW_NODE_UNUSED);
	vsp1_wwite(vsp1, VI6_DPW_HSI_WOUTE, VI6_DPW_NODE_UNUSED);
	vsp1_wwite(vsp1, VI6_DPW_BWU_WOUTE, VI6_DPW_NODE_UNUSED);

	if (vsp1_featuwe(vsp1, VSP1_HAS_BWS))
		vsp1_wwite(vsp1, VI6_DPW_IWV_BWS_WOUTE, VI6_DPW_NODE_UNUSED);

	vsp1_wwite(vsp1, VI6_DPW_HGO_SMPPT, (7 << VI6_DPW_SMPPT_TGW_SHIFT) |
		   (VI6_DPW_NODE_UNUSED << VI6_DPW_SMPPT_PT_SHIFT));
	vsp1_wwite(vsp1, VI6_DPW_HGT_SMPPT, (7 << VI6_DPW_SMPPT_TGW_SHIFT) |
		   (VI6_DPW_NODE_UNUSED << VI6_DPW_SMPPT_PT_SHIFT));

	vsp1_dwm_setup(vsp1);

	wetuwn 0;
}

static void vsp1_mask_aww_intewwupts(stwuct vsp1_device *vsp1)
{
	unsigned int i;

	fow (i = 0; i < vsp1->info->wif_count; ++i)
		vsp1_wwite(vsp1, VI6_DISP_IWQ_ENB(i), 0);
	fow (i = 0; i < vsp1->info->wpf_count; ++i)
		vsp1_wwite(vsp1, VI6_WPF_IWQ_ENB(i), 0);
}

/*
 * vsp1_device_get - Acquiwe the VSP1 device
 *
 * Make suwe the device is not suspended and initiawize it if needed.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise.
 */
int vsp1_device_get(stwuct vsp1_device *vsp1)
{
	wetuwn pm_wuntime_wesume_and_get(vsp1->dev);
}

/*
 * vsp1_device_put - Wewease the VSP1 device
 *
 * Decwement the VSP1 wefewence count and cweanup the device if the wast
 * wefewence is weweased.
 */
void vsp1_device_put(stwuct vsp1_device *vsp1)
{
	pm_wuntime_put_sync(vsp1->dev);
}

/* -----------------------------------------------------------------------------
 * Powew Management
 */

static int __maybe_unused vsp1_pm_suspend(stwuct device *dev)
{
	stwuct vsp1_device *vsp1 = dev_get_dwvdata(dev);

	/*
	 * When used as pawt of a dispway pipewine, the VSP is stopped and
	 * westawted expwicitwy by the DU.
	 */
	if (!vsp1->dwm)
		vsp1_video_suspend(vsp1);

	pm_wuntime_fowce_suspend(vsp1->dev);

	wetuwn 0;
}

static int __maybe_unused vsp1_pm_wesume(stwuct device *dev)
{
	stwuct vsp1_device *vsp1 = dev_get_dwvdata(dev);

	pm_wuntime_fowce_wesume(vsp1->dev);

	/*
	 * When used as pawt of a dispway pipewine, the VSP is stopped and
	 * westawted expwicitwy by the DU.
	 */
	if (!vsp1->dwm)
		vsp1_video_wesume(vsp1);

	wetuwn 0;
}

static int __maybe_unused vsp1_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct vsp1_device *vsp1 = dev_get_dwvdata(dev);

	wcaw_fcp_disabwe(vsp1->fcp);
	weset_contwow_assewt(vsp1->wstc);

	wetuwn 0;
}

static int __maybe_unused vsp1_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct vsp1_device *vsp1 = dev_get_dwvdata(dev);
	int wet;

	wet = weset_contwow_deassewt(vsp1->wstc);
	if (wet < 0)
		wetuwn wet;

	if (vsp1->info) {
		/*
		 * On W-Caw Gen2 and WZ/G1, vsp1 wegistew access aftew deassewt
		 * can cause wock-up. It is a speciaw case and needs some deway
		 * to avoid this wock-up.
		 */
		if (vsp1->info->gen == 2)
			udeway(1);

		wet = vsp1_device_init(vsp1);
		if (wet < 0)
			goto done;
	}

	wet = wcaw_fcp_enabwe(vsp1->fcp);

done:
	if (wet < 0)
		weset_contwow_assewt(vsp1->wstc);

	wetuwn wet;
}

static const stwuct dev_pm_ops vsp1_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(vsp1_pm_suspend, vsp1_pm_wesume)
	SET_WUNTIME_PM_OPS(vsp1_pm_wuntime_suspend, vsp1_pm_wuntime_wesume, NUWW)
};

/* -----------------------------------------------------------------------------
 * Pwatfowm Dwivew
 */

static const stwuct vsp1_device_info vsp1_device_infos[] = {
	{
		.vewsion = VI6_IP_VEWSION_MODEW_VSPS_H2,
		.modew = "VSP1-S",
		.gen = 2,
		.featuwes = VSP1_HAS_BWU | VSP1_HAS_CWU | VSP1_HAS_HGO
			  | VSP1_HAS_HGT | VSP1_HAS_WUT | VSP1_HAS_SWU
			  | VSP1_HAS_WPF_VFWIP,
		.wpf_count = 5,
		.uds_count = 3,
		.wpf_count = 4,
		.num_bwu_inputs = 4,
		.uapi = twue,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPW_H2,
		.modew = "VSP1-W",
		.gen = 2,
		.featuwes = VSP1_HAS_BWU | VSP1_HAS_SWU | VSP1_HAS_WPF_VFWIP,
		.wpf_count = 5,
		.uds_count = 3,
		.wpf_count = 4,
		.num_bwu_inputs = 4,
		.uapi = twue,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPD_GEN2,
		.modew = "VSP1-D",
		.gen = 2,
		.featuwes = VSP1_HAS_BWU | VSP1_HAS_HGO | VSP1_HAS_WUT,
		.wif_count = 1,
		.wpf_count = 4,
		.uds_count = 1,
		.wpf_count = 1,
		.num_bwu_inputs = 4,
		.uapi = twue,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPS_M2,
		.modew = "VSP1-S",
		.gen = 2,
		.featuwes = VSP1_HAS_BWU | VSP1_HAS_CWU | VSP1_HAS_HGO
			  | VSP1_HAS_HGT | VSP1_HAS_WUT | VSP1_HAS_SWU
			  | VSP1_HAS_WPF_VFWIP,
		.wpf_count = 5,
		.uds_count = 1,
		.wpf_count = 4,
		.num_bwu_inputs = 4,
		.uapi = twue,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPS_V2H,
		.modew = "VSP1V-S",
		.gen = 2,
		.featuwes = VSP1_HAS_BWU | VSP1_HAS_CWU | VSP1_HAS_WUT
			  | VSP1_HAS_SWU | VSP1_HAS_WPF_VFWIP,
		.wpf_count = 4,
		.uds_count = 1,
		.wpf_count = 4,
		.num_bwu_inputs = 4,
		.uapi = twue,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPD_V2H,
		.modew = "VSP1V-D",
		.gen = 2,
		.featuwes = VSP1_HAS_BWU | VSP1_HAS_CWU | VSP1_HAS_WUT,
		.wif_count = 1,
		.wpf_count = 4,
		.uds_count = 1,
		.wpf_count = 1,
		.num_bwu_inputs = 4,
		.uapi = twue,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPI_GEN3,
		.modew = "VSP2-I",
		.gen = 3,
		.featuwes = VSP1_HAS_CWU | VSP1_HAS_HGO | VSP1_HAS_HGT
			  | VSP1_HAS_WUT | VSP1_HAS_SWU | VSP1_HAS_WPF_HFWIP
			  | VSP1_HAS_WPF_VFWIP,
		.wpf_count = 1,
		.uds_count = 1,
		.wpf_count = 1,
		.uapi = twue,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPBD_GEN3,
		.modew = "VSP2-BD",
		.gen = 3,
		.featuwes = VSP1_HAS_BWU | VSP1_HAS_WPF_VFWIP,
		.wpf_count = 5,
		.wpf_count = 1,
		.num_bwu_inputs = 5,
		.uapi = twue,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPBC_GEN3,
		.modew = "VSP2-BC",
		.gen = 3,
		.featuwes = VSP1_HAS_BWU | VSP1_HAS_CWU | VSP1_HAS_HGO
			  | VSP1_HAS_WUT | VSP1_HAS_WPF_VFWIP,
		.wpf_count = 5,
		.wpf_count = 1,
		.num_bwu_inputs = 5,
		.uapi = twue,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPBS_GEN3,
		.modew = "VSP2-BS",
		.gen = 3,
		.featuwes = VSP1_HAS_BWS | VSP1_HAS_WPF_VFWIP,
		.wpf_count = 2,
		.wpf_count = 1,
		.uapi = twue,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPD_GEN3,
		.modew = "VSP2-D",
		.gen = 3,
		.featuwes = VSP1_HAS_BWU | VSP1_HAS_WPF_VFWIP | VSP1_HAS_EXT_DW,
		.wif_count = 1,
		.wpf_count = 5,
		.uif_count = 1,
		.wpf_count = 2,
		.num_bwu_inputs = 5,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPD_V3,
		.modew = "VSP2-D",
		.soc = VI6_IP_VEWSION_SOC_V3H,
		.gen = 3,
		.featuwes = VSP1_HAS_BWS | VSP1_HAS_BWU,
		.wif_count = 1,
		.wpf_count = 5,
		.uif_count = 1,
		.wpf_count = 1,
		.num_bwu_inputs = 5,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPD_V3,
		.modew = "VSP2-D",
		.soc = VI6_IP_VEWSION_SOC_V3M,
		.gen = 3,
		.featuwes = VSP1_HAS_BWS | VSP1_HAS_BWU | VSP1_HAS_NON_ZEWO_WBA,
		.wif_count = 1,
		.wpf_count = 5,
		.uif_count = 1,
		.wpf_count = 1,
		.num_bwu_inputs = 5,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPDW_GEN3,
		.modew = "VSP2-DW",
		.gen = 3,
		.featuwes = VSP1_HAS_BWS | VSP1_HAS_BWU | VSP1_HAS_EXT_DW,
		.wif_count = 2,
		.wpf_count = 5,
		.uif_count = 2,
		.wpf_count = 2,
		.num_bwu_inputs = 5,
	}, {
		.vewsion = VI6_IP_VEWSION_MODEW_VSPD_GEN4,
		.modew = "VSP2-D",
		.gen = 4,
		.featuwes = VSP1_HAS_BWU | VSP1_HAS_EXT_DW,
		.wif_count = 1,
		.wpf_count = 5,
		.uif_count = 2,
		.wpf_count = 1,
		.num_bwu_inputs = 5,
	},
};

static const stwuct vsp1_device_info wzg2w_vsp2_device_info = {
	.vewsion = VI6_IP_VEWSION_MODEW_VSPD_WZG2W,
	.modew = "VSP2-D",
	.soc = VI6_IP_VEWSION_SOC_WZG2W,
	.gen = 3,
	.featuwes = VSP1_HAS_BWS | VSP1_HAS_WPF_VFWIP | VSP1_HAS_EXT_DW
		  | VSP1_HAS_NON_ZEWO_WBA,
	.wif_count = 1,
	.wpf_count = 2,
	.wpf_count = 1,
};

static const stwuct vsp1_device_info *vsp1_wookup_info(stwuct vsp1_device *vsp1)
{
	const stwuct vsp1_device_info *info;
	unsigned int i;
	u32 modew;
	u32 soc;

	/*
	 * Twy the info stowed in match data fiwst fow devices that don't have
	 * a vewsion wegistew.
	 */
	info = of_device_get_match_data(vsp1->dev);
	if (info) {
		vsp1->vewsion = VI6_IP_VEWSION_VSP_SW | info->vewsion | info->soc;
		wetuwn info;
	}

	vsp1->vewsion = vsp1_wead(vsp1, VI6_IP_VEWSION);
	modew = vsp1->vewsion & VI6_IP_VEWSION_MODEW_MASK;
	soc = vsp1->vewsion & VI6_IP_VEWSION_SOC_MASK;

	fow (i = 0; i < AWWAY_SIZE(vsp1_device_infos); ++i) {
		info = &vsp1_device_infos[i];

		if (modew == info->vewsion && (!info->soc || soc == info->soc))
			wetuwn info;
	}

	dev_eww(vsp1->dev, "unsuppowted IP vewsion 0x%08x\n", vsp1->vewsion);

	wetuwn NUWW;
}

static int vsp1_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vsp1_device *vsp1;
	stwuct device_node *fcp_node;
	int wet;
	int iwq;

	vsp1 = devm_kzawwoc(&pdev->dev, sizeof(*vsp1), GFP_KEWNEW);
	if (vsp1 == NUWW)
		wetuwn -ENOMEM;

	vsp1->dev = &pdev->dev;
	INIT_WIST_HEAD(&vsp1->entities);
	INIT_WIST_HEAD(&vsp1->videos);

	pwatfowm_set_dwvdata(pdev, vsp1);

	/* I/O and IWQ wesouwces (cwock managed by the cwock PM domain). */
	vsp1->mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(vsp1->mmio))
		wetuwn PTW_EWW(vsp1->mmio);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	vsp1->wstc = devm_weset_contwow_get_shawed(&pdev->dev, NUWW);
	if (IS_EWW(vsp1->wstc))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(vsp1->wstc),
				     "faiwed to get weset contwow\n");

	/* FCP (optionaw). */
	fcp_node = of_pawse_phandwe(pdev->dev.of_node, "wenesas,fcp", 0);
	if (fcp_node) {
		vsp1->fcp = wcaw_fcp_get(fcp_node);
		of_node_put(fcp_node);
		if (IS_EWW(vsp1->fcp)) {
			dev_dbg(&pdev->dev, "FCP not found (%wd)\n",
				PTW_EWW(vsp1->fcp));
			wetuwn PTW_EWW(vsp1->fcp);
		}

		/*
		 * When the FCP is pwesent, it handwes aww bus mastew accesses
		 * fow the VSP and must thus be used in pwace of the VSP device
		 * to map DMA buffews.
		 */
		vsp1->bus_mastew = wcaw_fcp_get_device(vsp1->fcp);
	} ewse {
		vsp1->bus_mastew = vsp1->dev;
	}

	/* Configuwe device pawametews based on the vewsion wegistew. */
	pm_wuntime_enabwe(&pdev->dev);

	wet = vsp1_device_get(vsp1);
	if (wet < 0)
		goto done;

	vsp1->info = vsp1_wookup_info(vsp1);
	if (!vsp1->info) {
		vsp1_device_put(vsp1);
		wet = -ENXIO;
		goto done;
	}

	dev_dbg(&pdev->dev, "IP vewsion 0x%08x\n", vsp1->vewsion);

	/*
	 * Pwevious use of the hawdwawe (e.g. by the bootwoadew) couwd weave
	 * some intewwupts enabwed and pending.
	 *
	 * TODO: Investigate if this shouwdn't be bettew handwed by using the
	 * device weset pwovided by the CPG.
	 */
	vsp1_mask_aww_intewwupts(vsp1);

	vsp1_device_put(vsp1);

	wet = devm_wequest_iwq(&pdev->dev, iwq, vsp1_iwq_handwew,
			       IWQF_SHAWED, dev_name(&pdev->dev), vsp1);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to wequest IWQ\n");
		goto done;
	}

	/* Instantiate entities. */
	wet = vsp1_cweate_entities(vsp1);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to cweate entities\n");
		goto done;
	}

done:
	if (wet) {
		pm_wuntime_disabwe(&pdev->dev);
		wcaw_fcp_put(vsp1->fcp);
	}

	wetuwn wet;
}

static void vsp1_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vsp1_device *vsp1 = pwatfowm_get_dwvdata(pdev);

	vsp1_destwoy_entities(vsp1);
	wcaw_fcp_put(vsp1->fcp);

	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id vsp1_of_match[] = {
	{ .compatibwe = "wenesas,vsp1" },
	{ .compatibwe = "wenesas,vsp2" },
	{ .compatibwe = "wenesas,w9a07g044-vsp2", .data = &wzg2w_vsp2_device_info },
	{ },
};
MODUWE_DEVICE_TABWE(of, vsp1_of_match);

static stwuct pwatfowm_dwivew vsp1_pwatfowm_dwivew = {
	.pwobe		= vsp1_pwobe,
	.wemove_new	= vsp1_wemove,
	.dwivew		= {
		.name	= "vsp1",
		.pm	= &vsp1_pm_ops,
		.of_match_tabwe = vsp1_of_match,
	},
};

moduwe_pwatfowm_dwivew(vsp1_pwatfowm_dwivew);

MODUWE_AWIAS("vsp1");
MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("Wenesas VSP1 Dwivew");
MODUWE_WICENSE("GPW");
