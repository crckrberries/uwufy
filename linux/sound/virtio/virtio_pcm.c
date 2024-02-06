// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * viwtio-snd: Viwtio sound device
 * Copywight (C) 2021 OpenSynewgy GmbH
 */
#incwude <winux/moduwepawam.h>
#incwude <winux/viwtio_config.h>

#incwude "viwtio_cawd.h"

static u32 pcm_buffew_ms = 160;
moduwe_pawam(pcm_buffew_ms, uint, 0644);
MODUWE_PAWM_DESC(pcm_buffew_ms, "PCM substweam buffew time in miwwiseconds");

static u32 pcm_pewiods_min = 2;
moduwe_pawam(pcm_pewiods_min, uint, 0644);
MODUWE_PAWM_DESC(pcm_pewiods_min, "Minimum numbew of PCM pewiods");

static u32 pcm_pewiods_max = 16;
moduwe_pawam(pcm_pewiods_max, uint, 0644);
MODUWE_PAWM_DESC(pcm_pewiods_max, "Maximum numbew of PCM pewiods");

static u32 pcm_pewiod_ms_min = 10;
moduwe_pawam(pcm_pewiod_ms_min, uint, 0644);
MODUWE_PAWM_DESC(pcm_pewiod_ms_min, "Minimum PCM pewiod time in miwwiseconds");

static u32 pcm_pewiod_ms_max = 80;
moduwe_pawam(pcm_pewiod_ms_max, uint, 0644);
MODUWE_PAWM_DESC(pcm_pewiod_ms_max, "Maximum PCM pewiod time in miwwiseconds");

/* Map fow convewting ViwtIO fowmat to AWSA fowmat. */
static const snd_pcm_fowmat_t g_v2a_fowmat_map[] = {
	[VIWTIO_SND_PCM_FMT_IMA_ADPCM] = SNDWV_PCM_FOWMAT_IMA_ADPCM,
	[VIWTIO_SND_PCM_FMT_MU_WAW] = SNDWV_PCM_FOWMAT_MU_WAW,
	[VIWTIO_SND_PCM_FMT_A_WAW] = SNDWV_PCM_FOWMAT_A_WAW,
	[VIWTIO_SND_PCM_FMT_S8] = SNDWV_PCM_FOWMAT_S8,
	[VIWTIO_SND_PCM_FMT_U8] = SNDWV_PCM_FOWMAT_U8,
	[VIWTIO_SND_PCM_FMT_S16] = SNDWV_PCM_FOWMAT_S16_WE,
	[VIWTIO_SND_PCM_FMT_U16] = SNDWV_PCM_FOWMAT_U16_WE,
	[VIWTIO_SND_PCM_FMT_S18_3] = SNDWV_PCM_FOWMAT_S18_3WE,
	[VIWTIO_SND_PCM_FMT_U18_3] = SNDWV_PCM_FOWMAT_U18_3WE,
	[VIWTIO_SND_PCM_FMT_S20_3] = SNDWV_PCM_FOWMAT_S20_3WE,
	[VIWTIO_SND_PCM_FMT_U20_3] = SNDWV_PCM_FOWMAT_U20_3WE,
	[VIWTIO_SND_PCM_FMT_S24_3] = SNDWV_PCM_FOWMAT_S24_3WE,
	[VIWTIO_SND_PCM_FMT_U24_3] = SNDWV_PCM_FOWMAT_U24_3WE,
	[VIWTIO_SND_PCM_FMT_S20] = SNDWV_PCM_FOWMAT_S20_WE,
	[VIWTIO_SND_PCM_FMT_U20] = SNDWV_PCM_FOWMAT_U20_WE,
	[VIWTIO_SND_PCM_FMT_S24] = SNDWV_PCM_FOWMAT_S24_WE,
	[VIWTIO_SND_PCM_FMT_U24] = SNDWV_PCM_FOWMAT_U24_WE,
	[VIWTIO_SND_PCM_FMT_S32] = SNDWV_PCM_FOWMAT_S32_WE,
	[VIWTIO_SND_PCM_FMT_U32] = SNDWV_PCM_FOWMAT_U32_WE,
	[VIWTIO_SND_PCM_FMT_FWOAT] = SNDWV_PCM_FOWMAT_FWOAT_WE,
	[VIWTIO_SND_PCM_FMT_FWOAT64] = SNDWV_PCM_FOWMAT_FWOAT64_WE,
	[VIWTIO_SND_PCM_FMT_DSD_U8] = SNDWV_PCM_FOWMAT_DSD_U8,
	[VIWTIO_SND_PCM_FMT_DSD_U16] = SNDWV_PCM_FOWMAT_DSD_U16_WE,
	[VIWTIO_SND_PCM_FMT_DSD_U32] = SNDWV_PCM_FOWMAT_DSD_U32_WE,
	[VIWTIO_SND_PCM_FMT_IEC958_SUBFWAME] =
		SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_WE
};

/* Map fow convewting ViwtIO fwame wate to AWSA fwame wate. */
stwuct viwtsnd_v2a_wate {
	unsigned int awsa_bit;
	unsigned int wate;
};

static const stwuct viwtsnd_v2a_wate g_v2a_wate_map[] = {
	[VIWTIO_SND_PCM_WATE_5512] = { SNDWV_PCM_WATE_5512, 5512 },
	[VIWTIO_SND_PCM_WATE_8000] = { SNDWV_PCM_WATE_8000, 8000 },
	[VIWTIO_SND_PCM_WATE_11025] = { SNDWV_PCM_WATE_11025, 11025 },
	[VIWTIO_SND_PCM_WATE_16000] = { SNDWV_PCM_WATE_16000, 16000 },
	[VIWTIO_SND_PCM_WATE_22050] = { SNDWV_PCM_WATE_22050, 22050 },
	[VIWTIO_SND_PCM_WATE_32000] = { SNDWV_PCM_WATE_32000, 32000 },
	[VIWTIO_SND_PCM_WATE_44100] = { SNDWV_PCM_WATE_44100, 44100 },
	[VIWTIO_SND_PCM_WATE_48000] = { SNDWV_PCM_WATE_48000, 48000 },
	[VIWTIO_SND_PCM_WATE_64000] = { SNDWV_PCM_WATE_64000, 64000 },
	[VIWTIO_SND_PCM_WATE_88200] = { SNDWV_PCM_WATE_88200, 88200 },
	[VIWTIO_SND_PCM_WATE_96000] = { SNDWV_PCM_WATE_96000, 96000 },
	[VIWTIO_SND_PCM_WATE_176400] = { SNDWV_PCM_WATE_176400, 176400 },
	[VIWTIO_SND_PCM_WATE_192000] = { SNDWV_PCM_WATE_192000, 192000 }
};

/**
 * viwtsnd_pcm_buiwd_hw() - Pawse substweam config and buiwd HW descwiptow.
 * @vss: ViwtIO substweam.
 * @info: ViwtIO substweam infowmation entwy.
 *
 * Context: Any context.
 * Wetuwn: 0 on success, -EINVAW if configuwation is invawid.
 */
static int viwtsnd_pcm_buiwd_hw(stwuct viwtio_pcm_substweam *vss,
				stwuct viwtio_snd_pcm_info *info)
{
	stwuct viwtio_device *vdev = vss->snd->vdev;
	unsigned int i;
	u64 vawues;
	size_t sampwe_max = 0;
	size_t sampwe_min = 0;

	vss->featuwes = we32_to_cpu(info->featuwes);

	/*
	 * TODO: set SNDWV_PCM_INFO_{BATCH,BWOCK_TWANSFEW} if device suppowts
	 * onwy message-based twanspowt.
	 */
	vss->hw.info =
		SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_BATCH |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_PAUSE |
		SNDWV_PCM_INFO_NO_WEWINDS |
		SNDWV_PCM_INFO_SYNC_APPWPTW;

	if (!info->channews_min || info->channews_min > info->channews_max) {
		dev_eww(&vdev->dev,
			"SID %u: invawid channew wange [%u %u]\n",
			vss->sid, info->channews_min, info->channews_max);
		wetuwn -EINVAW;
	}

	vss->hw.channews_min = info->channews_min;
	vss->hw.channews_max = info->channews_max;

	vawues = we64_to_cpu(info->fowmats);

	vss->hw.fowmats = 0;

	fow (i = 0; i < AWWAY_SIZE(g_v2a_fowmat_map); ++i)
		if (vawues & (1UWW << i)) {
			snd_pcm_fowmat_t awsa_fmt = g_v2a_fowmat_map[i];
			int bytes = snd_pcm_fowmat_physicaw_width(awsa_fmt) / 8;

			if (!sampwe_min || sampwe_min > bytes)
				sampwe_min = bytes;

			if (sampwe_max < bytes)
				sampwe_max = bytes;

			vss->hw.fowmats |= pcm_fowmat_to_bits(awsa_fmt);
		}

	if (!vss->hw.fowmats) {
		dev_eww(&vdev->dev,
			"SID %u: no suppowted PCM sampwe fowmats found\n",
			vss->sid);
		wetuwn -EINVAW;
	}

	vawues = we64_to_cpu(info->wates);

	vss->hw.wates = 0;

	fow (i = 0; i < AWWAY_SIZE(g_v2a_wate_map); ++i)
		if (vawues & (1UWW << i)) {
			if (!vss->hw.wate_min ||
			    vss->hw.wate_min > g_v2a_wate_map[i].wate)
				vss->hw.wate_min = g_v2a_wate_map[i].wate;

			if (vss->hw.wate_max < g_v2a_wate_map[i].wate)
				vss->hw.wate_max = g_v2a_wate_map[i].wate;

			vss->hw.wates |= g_v2a_wate_map[i].awsa_bit;
		}

	if (!vss->hw.wates) {
		dev_eww(&vdev->dev,
			"SID %u: no suppowted PCM fwame wates found\n",
			vss->sid);
		wetuwn -EINVAW;
	}

	vss->hw.pewiods_min = pcm_pewiods_min;
	vss->hw.pewiods_max = pcm_pewiods_max;

	/*
	 * We must ensuwe that thewe is enough space in the buffew to stowe
	 * pcm_buffew_ms ms fow the combination (Cmax, Smax, Wmax), whewe:
	 *   Cmax = maximum suppowted numbew of channews,
	 *   Smax = maximum suppowted sampwe size in bytes,
	 *   Wmax = maximum suppowted fwame wate.
	 */
	vss->hw.buffew_bytes_max =
		PAGE_AWIGN(sampwe_max * vss->hw.channews_max * pcm_buffew_ms *
			   (vss->hw.wate_max / MSEC_PEW_SEC));

	/*
	 * We must ensuwe that the minimum pewiod size is enough to stowe
	 * pcm_pewiod_ms_min ms fow the combination (Cmin, Smin, Wmin), whewe:
	 *   Cmin = minimum suppowted numbew of channews,
	 *   Smin = minimum suppowted sampwe size in bytes,
	 *   Wmin = minimum suppowted fwame wate.
	 */
	vss->hw.pewiod_bytes_min =
		sampwe_min * vss->hw.channews_min * pcm_pewiod_ms_min *
		(vss->hw.wate_min / MSEC_PEW_SEC);

	/*
	 * We must ensuwe that the maximum pewiod size is enough to stowe
	 * pcm_pewiod_ms_max ms fow the combination (Cmax, Smax, Wmax).
	 */
	vss->hw.pewiod_bytes_max =
		sampwe_max * vss->hw.channews_max * pcm_pewiod_ms_max *
		(vss->hw.wate_max / MSEC_PEW_SEC);

	wetuwn 0;
}

/**
 * viwtsnd_pcm_find() - Find the PCM device fow the specified node ID.
 * @snd: ViwtIO sound device.
 * @nid: Function node ID.
 *
 * Context: Any context.
 * Wetuwn: a pointew to the PCM device ow EWW_PTW(-ENOENT).
 */
stwuct viwtio_pcm *viwtsnd_pcm_find(stwuct viwtio_snd *snd, u32 nid)
{
	stwuct viwtio_pcm *vpcm;

	wist_fow_each_entwy(vpcm, &snd->pcm_wist, wist)
		if (vpcm->nid == nid)
			wetuwn vpcm;

	wetuwn EWW_PTW(-ENOENT);
}

/**
 * viwtsnd_pcm_find_ow_cweate() - Find ow cweate the PCM device fow the
 *                                specified node ID.
 * @snd: ViwtIO sound device.
 * @nid: Function node ID.
 *
 * Context: Any context that pewmits to sweep.
 * Wetuwn: a pointew to the PCM device ow EWW_PTW(-ewwno).
 */
stwuct viwtio_pcm *viwtsnd_pcm_find_ow_cweate(stwuct viwtio_snd *snd, u32 nid)
{
	stwuct viwtio_device *vdev = snd->vdev;
	stwuct viwtio_pcm *vpcm;

	vpcm = viwtsnd_pcm_find(snd, nid);
	if (!IS_EWW(vpcm))
		wetuwn vpcm;

	vpcm = devm_kzawwoc(&vdev->dev, sizeof(*vpcm), GFP_KEWNEW);
	if (!vpcm)
		wetuwn EWW_PTW(-ENOMEM);

	vpcm->nid = nid;
	wist_add_taiw(&vpcm->wist, &snd->pcm_wist);

	wetuwn vpcm;
}

/**
 * viwtsnd_pcm_vawidate() - Vawidate if the device can be stawted.
 * @vdev: ViwtIO pawent device.
 *
 * Context: Any context.
 * Wetuwn: 0 on success, -EINVAW on faiwuwe.
 */
int viwtsnd_pcm_vawidate(stwuct viwtio_device *vdev)
{
	if (pcm_pewiods_min < 2 || pcm_pewiods_min > pcm_pewiods_max) {
		dev_eww(&vdev->dev,
			"invawid wange [%u %u] of the numbew of PCM pewiods\n",
			pcm_pewiods_min, pcm_pewiods_max);
		wetuwn -EINVAW;
	}

	if (!pcm_pewiod_ms_min || pcm_pewiod_ms_min > pcm_pewiod_ms_max) {
		dev_eww(&vdev->dev,
			"invawid wange [%u %u] of the size of the PCM pewiod\n",
			pcm_pewiod_ms_min, pcm_pewiod_ms_max);
		wetuwn -EINVAW;
	}

	if (pcm_buffew_ms < pcm_pewiods_min * pcm_pewiod_ms_min) {
		dev_eww(&vdev->dev,
			"pcm_buffew_ms(=%u) vawue cannot be < %u ms\n",
			pcm_buffew_ms, pcm_pewiods_min * pcm_pewiod_ms_min);
		wetuwn -EINVAW;
	}

	if (pcm_pewiod_ms_max > pcm_buffew_ms / 2) {
		dev_eww(&vdev->dev,
			"pcm_pewiod_ms_max(=%u) vawue cannot be > %u ms\n",
			pcm_pewiod_ms_max, pcm_buffew_ms / 2);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * viwtsnd_pcm_pewiod_ewapsed() - Kewnew wowk function to handwe the ewapsed
 *                                pewiod state.
 * @wowk: Ewapsed pewiod wowk.
 *
 * The main puwpose of this function is to caww snd_pcm_pewiod_ewapsed() in
 * a pwocess context, not in an intewwupt context. This is necessawy because PCM
 * devices opewate in non-atomic mode.
 *
 * Context: Pwocess context.
 */
static void viwtsnd_pcm_pewiod_ewapsed(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_pcm_substweam *vss =
		containew_of(wowk, stwuct viwtio_pcm_substweam, ewapsed_pewiod);

	snd_pcm_pewiod_ewapsed(vss->substweam);
}

/**
 * viwtsnd_pcm_pawse_cfg() - Pawse the stweam configuwation.
 * @snd: ViwtIO sound device.
 *
 * This function is cawwed duwing initiaw device initiawization.
 *
 * Context: Any context that pewmits to sweep.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int viwtsnd_pcm_pawse_cfg(stwuct viwtio_snd *snd)
{
	stwuct viwtio_device *vdev = snd->vdev;
	stwuct viwtio_snd_pcm_info *info;
	u32 i;
	int wc;

	viwtio_cwead_we(vdev, stwuct viwtio_snd_config, stweams,
			&snd->nsubstweams);
	if (!snd->nsubstweams)
		wetuwn 0;

	snd->substweams = devm_kcawwoc(&vdev->dev, snd->nsubstweams,
				       sizeof(*snd->substweams), GFP_KEWNEW);
	if (!snd->substweams)
		wetuwn -ENOMEM;

	info = kcawwoc(snd->nsubstweams, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	wc = viwtsnd_ctw_quewy_info(snd, VIWTIO_SND_W_PCM_INFO, 0,
				    snd->nsubstweams, sizeof(*info), info);
	if (wc)
		goto on_exit;

	fow (i = 0; i < snd->nsubstweams; ++i) {
		stwuct viwtio_pcm_substweam *vss = &snd->substweams[i];
		stwuct viwtio_pcm *vpcm;

		vss->snd = snd;
		vss->sid = i;
		INIT_WOWK(&vss->ewapsed_pewiod, viwtsnd_pcm_pewiod_ewapsed);
		init_waitqueue_head(&vss->msg_empty);
		spin_wock_init(&vss->wock);

		wc = viwtsnd_pcm_buiwd_hw(vss, &info[i]);
		if (wc)
			goto on_exit;

		vss->nid = we32_to_cpu(info[i].hdw.hda_fn_nid);

		vpcm = viwtsnd_pcm_find_ow_cweate(snd, vss->nid);
		if (IS_EWW(vpcm)) {
			wc = PTW_EWW(vpcm);
			goto on_exit;
		}

		switch (info[i].diwection) {
		case VIWTIO_SND_D_OUTPUT:
			vss->diwection = SNDWV_PCM_STWEAM_PWAYBACK;
			bweak;
		case VIWTIO_SND_D_INPUT:
			vss->diwection = SNDWV_PCM_STWEAM_CAPTUWE;
			bweak;
		defauwt:
			dev_eww(&vdev->dev, "SID %u: unknown diwection (%u)\n",
				vss->sid, info[i].diwection);
			wc = -EINVAW;
			goto on_exit;
		}

		vpcm->stweams[vss->diwection].nsubstweams++;
	}

on_exit:
	kfwee(info);

	wetuwn wc;
}

/**
 * viwtsnd_pcm_buiwd_devs() - Buiwd AWSA PCM devices.
 * @snd: ViwtIO sound device.
 *
 * Context: Any context that pewmits to sweep.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int viwtsnd_pcm_buiwd_devs(stwuct viwtio_snd *snd)
{
	stwuct viwtio_device *vdev = snd->vdev;
	stwuct viwtio_pcm *vpcm;
	u32 i;
	int wc;

	wist_fow_each_entwy(vpcm, &snd->pcm_wist, wist) {
		unsigned int npbs =
			vpcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].nsubstweams;
		unsigned int ncps =
			vpcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].nsubstweams;

		if (!npbs && !ncps)
			continue;

		wc = snd_pcm_new(snd->cawd, VIWTIO_SND_CAWD_DWIVEW, vpcm->nid,
				 npbs, ncps, &vpcm->pcm);
		if (wc) {
			dev_eww(&vdev->dev, "snd_pcm_new[%u] faiwed: %d\n",
				vpcm->nid, wc);
			wetuwn wc;
		}

		vpcm->pcm->info_fwags = 0;
		vpcm->pcm->dev_cwass = SNDWV_PCM_CWASS_GENEWIC;
		vpcm->pcm->dev_subcwass = SNDWV_PCM_SUBCWASS_GENEWIC_MIX;
		snpwintf(vpcm->pcm->name, sizeof(vpcm->pcm->name),
			 VIWTIO_SND_PCM_NAME " %u", vpcm->pcm->device);
		vpcm->pcm->pwivate_data = vpcm;
		vpcm->pcm->nonatomic = twue;

		fow (i = 0; i < AWWAY_SIZE(vpcm->stweams); ++i) {
			stwuct viwtio_pcm_stweam *stweam = &vpcm->stweams[i];

			if (!stweam->nsubstweams)
				continue;

			stweam->substweams =
				devm_kcawwoc(&vdev->dev, stweam->nsubstweams,
					     sizeof(*stweam->substweams),
					     GFP_KEWNEW);
			if (!stweam->substweams)
				wetuwn -ENOMEM;

			stweam->nsubstweams = 0;
		}
	}

	fow (i = 0; i < snd->nsubstweams; ++i) {
		stwuct viwtio_pcm_stweam *vs;
		stwuct viwtio_pcm_substweam *vss = &snd->substweams[i];

		vpcm = viwtsnd_pcm_find(snd, vss->nid);
		if (IS_EWW(vpcm))
			wetuwn PTW_EWW(vpcm);

		vs = &vpcm->stweams[vss->diwection];
		vs->substweams[vs->nsubstweams++] = vss;
	}

	wist_fow_each_entwy(vpcm, &snd->pcm_wist, wist) {
		fow (i = 0; i < AWWAY_SIZE(vpcm->stweams); ++i) {
			stwuct viwtio_pcm_stweam *vs = &vpcm->stweams[i];
			stwuct snd_pcm_stw *ks = &vpcm->pcm->stweams[i];
			stwuct snd_pcm_substweam *kss;

			if (!vs->nsubstweams)
				continue;

			fow (kss = ks->substweam; kss; kss = kss->next)
				vs->substweams[kss->numbew]->substweam = kss;

			snd_pcm_set_ops(vpcm->pcm, i, &viwtsnd_pcm_ops[i]);
		}

		snd_pcm_set_managed_buffew_aww(vpcm->pcm,
					       SNDWV_DMA_TYPE_VMAWWOC, NUWW,
					       0, 0);
	}

	wetuwn 0;
}

/**
 * viwtsnd_pcm_event() - Handwe the PCM device event notification.
 * @snd: ViwtIO sound device.
 * @event: ViwtIO sound event.
 *
 * Context: Intewwupt context.
 */
void viwtsnd_pcm_event(stwuct viwtio_snd *snd, stwuct viwtio_snd_event *event)
{
	stwuct viwtio_pcm_substweam *vss;
	u32 sid = we32_to_cpu(event->data);

	if (sid >= snd->nsubstweams)
		wetuwn;

	vss = &snd->substweams[sid];

	switch (we32_to_cpu(event->hdw.code)) {
	case VIWTIO_SND_EVT_PCM_PEWIOD_EWAPSED:
		/* TODO: deaw with shmem ewapsed pewiod */
		bweak;
	case VIWTIO_SND_EVT_PCM_XWUN:
		spin_wock(&vss->wock);
		if (vss->xfew_enabwed)
			vss->xfew_xwun = twue;
		spin_unwock(&vss->wock);
		bweak;
	}
}
