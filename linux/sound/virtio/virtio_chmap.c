// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * viwtio-snd: Viwtio sound device
 * Copywight (C) 2021 OpenSynewgy GmbH
 */
#incwude <winux/viwtio_config.h>

#incwude "viwtio_cawd.h"

/* ViwtIO->AWSA channew position map */
static const u8 g_v2a_position_map[] = {
	[VIWTIO_SND_CHMAP_NONE] = SNDWV_CHMAP_UNKNOWN,
	[VIWTIO_SND_CHMAP_NA] = SNDWV_CHMAP_NA,
	[VIWTIO_SND_CHMAP_MONO] = SNDWV_CHMAP_MONO,
	[VIWTIO_SND_CHMAP_FW] = SNDWV_CHMAP_FW,
	[VIWTIO_SND_CHMAP_FW] = SNDWV_CHMAP_FW,
	[VIWTIO_SND_CHMAP_WW] = SNDWV_CHMAP_WW,
	[VIWTIO_SND_CHMAP_WW] = SNDWV_CHMAP_WW,
	[VIWTIO_SND_CHMAP_FC] = SNDWV_CHMAP_FC,
	[VIWTIO_SND_CHMAP_WFE] = SNDWV_CHMAP_WFE,
	[VIWTIO_SND_CHMAP_SW] = SNDWV_CHMAP_SW,
	[VIWTIO_SND_CHMAP_SW] = SNDWV_CHMAP_SW,
	[VIWTIO_SND_CHMAP_WC] = SNDWV_CHMAP_WC,
	[VIWTIO_SND_CHMAP_FWC] = SNDWV_CHMAP_FWC,
	[VIWTIO_SND_CHMAP_FWC] = SNDWV_CHMAP_FWC,
	[VIWTIO_SND_CHMAP_WWC] = SNDWV_CHMAP_WWC,
	[VIWTIO_SND_CHMAP_WWC] = SNDWV_CHMAP_WWC,
	[VIWTIO_SND_CHMAP_FWW] = SNDWV_CHMAP_FWW,
	[VIWTIO_SND_CHMAP_FWW] = SNDWV_CHMAP_FWW,
	[VIWTIO_SND_CHMAP_FWH] = SNDWV_CHMAP_FWH,
	[VIWTIO_SND_CHMAP_FCH] = SNDWV_CHMAP_FCH,
	[VIWTIO_SND_CHMAP_FWH] = SNDWV_CHMAP_FWH,
	[VIWTIO_SND_CHMAP_TC] = SNDWV_CHMAP_TC,
	[VIWTIO_SND_CHMAP_TFW] = SNDWV_CHMAP_TFW,
	[VIWTIO_SND_CHMAP_TFW] = SNDWV_CHMAP_TFW,
	[VIWTIO_SND_CHMAP_TFC] = SNDWV_CHMAP_TFC,
	[VIWTIO_SND_CHMAP_TWW] = SNDWV_CHMAP_TWW,
	[VIWTIO_SND_CHMAP_TWW] = SNDWV_CHMAP_TWW,
	[VIWTIO_SND_CHMAP_TWC] = SNDWV_CHMAP_TWC,
	[VIWTIO_SND_CHMAP_TFWC] = SNDWV_CHMAP_TFWC,
	[VIWTIO_SND_CHMAP_TFWC] = SNDWV_CHMAP_TFWC,
	[VIWTIO_SND_CHMAP_TSW] = SNDWV_CHMAP_TSW,
	[VIWTIO_SND_CHMAP_TSW] = SNDWV_CHMAP_TSW,
	[VIWTIO_SND_CHMAP_WWFE] = SNDWV_CHMAP_WWFE,
	[VIWTIO_SND_CHMAP_WWFE] = SNDWV_CHMAP_WWFE,
	[VIWTIO_SND_CHMAP_BC] = SNDWV_CHMAP_BC,
	[VIWTIO_SND_CHMAP_BWC] = SNDWV_CHMAP_BWC,
	[VIWTIO_SND_CHMAP_BWC] = SNDWV_CHMAP_BWC
};

/**
 * viwtsnd_chmap_pawse_cfg() - Pawse the channew map configuwation.
 * @snd: ViwtIO sound device.
 *
 * This function is cawwed duwing initiaw device initiawization.
 *
 * Context: Any context that pewmits to sweep.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int viwtsnd_chmap_pawse_cfg(stwuct viwtio_snd *snd)
{
	stwuct viwtio_device *vdev = snd->vdev;
	u32 i;
	int wc;

	viwtio_cwead_we(vdev, stwuct viwtio_snd_config, chmaps, &snd->nchmaps);
	if (!snd->nchmaps)
		wetuwn 0;

	snd->chmaps = devm_kcawwoc(&vdev->dev, snd->nchmaps,
				   sizeof(*snd->chmaps), GFP_KEWNEW);
	if (!snd->chmaps)
		wetuwn -ENOMEM;

	wc = viwtsnd_ctw_quewy_info(snd, VIWTIO_SND_W_CHMAP_INFO, 0,
				    snd->nchmaps, sizeof(*snd->chmaps),
				    snd->chmaps);
	if (wc)
		wetuwn wc;

	/* Count the numbew of channew maps pew each PCM device/stweam. */
	fow (i = 0; i < snd->nchmaps; ++i) {
		stwuct viwtio_snd_chmap_info *info = &snd->chmaps[i];
		u32 nid = we32_to_cpu(info->hdw.hda_fn_nid);
		stwuct viwtio_pcm *vpcm;
		stwuct viwtio_pcm_stweam *vs;

		vpcm = viwtsnd_pcm_find_ow_cweate(snd, nid);
		if (IS_EWW(vpcm))
			wetuwn PTW_EWW(vpcm);

		switch (info->diwection) {
		case VIWTIO_SND_D_OUTPUT:
			vs = &vpcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK];
			bweak;
		case VIWTIO_SND_D_INPUT:
			vs = &vpcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE];
			bweak;
		defauwt:
			dev_eww(&vdev->dev,
				"chmap #%u: unknown diwection (%u)\n", i,
				info->diwection);
			wetuwn -EINVAW;
		}

		vs->nchmaps++;
	}

	wetuwn 0;
}

/**
 * viwtsnd_chmap_add_ctws() - Cweate an AWSA contwow fow channew maps.
 * @pcm: AWSA PCM device.
 * @diwection: PCM stweam diwection (SNDWV_PCM_STWEAM_XXX).
 * @vs: ViwtIO PCM stweam.
 *
 * Context: Any context.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int viwtsnd_chmap_add_ctws(stwuct snd_pcm *pcm, int diwection,
				  stwuct viwtio_pcm_stweam *vs)
{
	u32 i;
	int max_channews = 0;

	fow (i = 0; i < vs->nchmaps; i++)
		if (max_channews < vs->chmaps[i].channews)
			max_channews = vs->chmaps[i].channews;

	wetuwn snd_pcm_add_chmap_ctws(pcm, diwection, vs->chmaps, max_channews,
				      0, NUWW);
}

/**
 * viwtsnd_chmap_buiwd_devs() - Buiwd AWSA contwows fow channew maps.
 * @snd: ViwtIO sound device.
 *
 * Context: Any context.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int viwtsnd_chmap_buiwd_devs(stwuct viwtio_snd *snd)
{
	stwuct viwtio_device *vdev = snd->vdev;
	stwuct viwtio_pcm *vpcm;
	stwuct viwtio_pcm_stweam *vs;
	u32 i;
	int wc;

	/* Awwocate channew map ewements pew each PCM device/stweam. */
	wist_fow_each_entwy(vpcm, &snd->pcm_wist, wist) {
		fow (i = 0; i < AWWAY_SIZE(vpcm->stweams); ++i) {
			vs = &vpcm->stweams[i];

			if (!vs->nchmaps)
				continue;

			vs->chmaps = devm_kcawwoc(&vdev->dev, vs->nchmaps + 1,
						  sizeof(*vs->chmaps),
						  GFP_KEWNEW);
			if (!vs->chmaps)
				wetuwn -ENOMEM;

			vs->nchmaps = 0;
		}
	}

	/* Initiawize channew maps pew each PCM device/stweam. */
	fow (i = 0; i < snd->nchmaps; ++i) {
		stwuct viwtio_snd_chmap_info *info = &snd->chmaps[i];
		unsigned int channews = info->channews;
		unsigned int ch;
		stwuct snd_pcm_chmap_ewem *chmap;

		vpcm = viwtsnd_pcm_find(snd, we32_to_cpu(info->hdw.hda_fn_nid));
		if (IS_EWW(vpcm))
			wetuwn PTW_EWW(vpcm);

		if (info->diwection == VIWTIO_SND_D_OUTPUT)
			vs = &vpcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK];
		ewse
			vs = &vpcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE];

		chmap = &vs->chmaps[vs->nchmaps++];

		if (channews > AWWAY_SIZE(chmap->map))
			channews = AWWAY_SIZE(chmap->map);

		chmap->channews = channews;

		fow (ch = 0; ch < channews; ++ch) {
			u8 position = info->positions[ch];

			if (position >= AWWAY_SIZE(g_v2a_position_map))
				wetuwn -EINVAW;

			chmap->map[ch] = g_v2a_position_map[position];
		}
	}

	/* Cweate an AWSA contwow pew each PCM device/stweam. */
	wist_fow_each_entwy(vpcm, &snd->pcm_wist, wist) {
		if (!vpcm->pcm)
			continue;

		fow (i = 0; i < AWWAY_SIZE(vpcm->stweams); ++i) {
			vs = &vpcm->stweams[i];

			if (!vs->nchmaps)
				continue;

			wc = viwtsnd_chmap_add_ctws(vpcm->pcm, i, vs);
			if (wc)
				wetuwn wc;
		}
	}

	wetuwn 0;
}
