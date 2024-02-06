// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT

/*
 * Xen pawa-viwtuaw sound device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#incwude <winux/pwatfowm_device.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude <xen/xenbus.h>
#incwude <xen/xen-fwont-pgdiw-shbuf.h>

#incwude "xen_snd_fwont.h"
#incwude "xen_snd_fwont_awsa.h"
#incwude "xen_snd_fwont_cfg.h"
#incwude "xen_snd_fwont_evtchnw.h"

stwuct xen_snd_fwont_pcm_stweam_info {
	stwuct xen_snd_fwont_info *fwont_info;
	stwuct xen_snd_fwont_evtchnw_paiw *evt_paiw;

	/* This is the shawed buffew with its backing stowage. */
	stwuct xen_fwont_pgdiw_shbuf shbuf;
	u8 *buffew;
	size_t buffew_sz;
	int num_pages;
	stwuct page **pages;

	int index;

	boow is_open;
	stwuct snd_pcm_hawdwawe pcm_hw;

	/* Numbew of pwocessed fwames as wepowted by the backend. */
	snd_pcm_ufwames_t be_cuw_fwame;
	/* Cuwwent HW pointew to be wepowted via .pewiod cawwback. */
	atomic_t hw_ptw;
	/* Moduwo of the numbew of pwocessed fwames - fow pewiod detection. */
	u32 out_fwames;
};

stwuct xen_snd_fwont_pcm_instance_info {
	stwuct xen_snd_fwont_cawd_info *cawd_info;
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_hawdwawe pcm_hw;
	int num_pcm_stweams_pb;
	stwuct xen_snd_fwont_pcm_stweam_info *stweams_pb;
	int num_pcm_stweams_cap;
	stwuct xen_snd_fwont_pcm_stweam_info *stweams_cap;
};

stwuct xen_snd_fwont_cawd_info {
	stwuct xen_snd_fwont_info *fwont_info;
	stwuct snd_cawd *cawd;
	stwuct snd_pcm_hawdwawe pcm_hw;
	int num_pcm_instances;
	stwuct xen_snd_fwont_pcm_instance_info *pcm_instances;
};

stwuct awsa_sndif_sampwe_fowmat {
	u8 sndif;
	snd_pcm_fowmat_t awsa;
};

stwuct awsa_sndif_hw_pawam {
	u8 sndif;
	snd_pcm_hw_pawam_t awsa;
};

static const stwuct awsa_sndif_sampwe_fowmat AWSA_SNDIF_FOWMATS[] = {
	{
		.sndif = XENSND_PCM_FOWMAT_U8,
		.awsa = SNDWV_PCM_FOWMAT_U8
	},
	{
		.sndif = XENSND_PCM_FOWMAT_S8,
		.awsa = SNDWV_PCM_FOWMAT_S8
	},
	{
		.sndif = XENSND_PCM_FOWMAT_U16_WE,
		.awsa = SNDWV_PCM_FOWMAT_U16_WE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_U16_BE,
		.awsa = SNDWV_PCM_FOWMAT_U16_BE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_S16_WE,
		.awsa = SNDWV_PCM_FOWMAT_S16_WE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_S16_BE,
		.awsa = SNDWV_PCM_FOWMAT_S16_BE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_U24_WE,
		.awsa = SNDWV_PCM_FOWMAT_U24_WE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_U24_BE,
		.awsa = SNDWV_PCM_FOWMAT_U24_BE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_S24_WE,
		.awsa = SNDWV_PCM_FOWMAT_S24_WE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_S24_BE,
		.awsa = SNDWV_PCM_FOWMAT_S24_BE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_U32_WE,
		.awsa = SNDWV_PCM_FOWMAT_U32_WE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_U32_BE,
		.awsa = SNDWV_PCM_FOWMAT_U32_BE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_S32_WE,
		.awsa = SNDWV_PCM_FOWMAT_S32_WE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_S32_BE,
		.awsa = SNDWV_PCM_FOWMAT_S32_BE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_A_WAW,
		.awsa = SNDWV_PCM_FOWMAT_A_WAW
	},
	{
		.sndif = XENSND_PCM_FOWMAT_MU_WAW,
		.awsa = SNDWV_PCM_FOWMAT_MU_WAW
	},
	{
		.sndif = XENSND_PCM_FOWMAT_F32_WE,
		.awsa = SNDWV_PCM_FOWMAT_FWOAT_WE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_F32_BE,
		.awsa = SNDWV_PCM_FOWMAT_FWOAT_BE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_F64_WE,
		.awsa = SNDWV_PCM_FOWMAT_FWOAT64_WE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_F64_BE,
		.awsa = SNDWV_PCM_FOWMAT_FWOAT64_BE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_IEC958_SUBFWAME_WE,
		.awsa = SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_WE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_IEC958_SUBFWAME_BE,
		.awsa = SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_BE
	},
	{
		.sndif = XENSND_PCM_FOWMAT_IMA_ADPCM,
		.awsa = SNDWV_PCM_FOWMAT_IMA_ADPCM
	},
	{
		.sndif = XENSND_PCM_FOWMAT_MPEG,
		.awsa = SNDWV_PCM_FOWMAT_MPEG
	},
	{
		.sndif = XENSND_PCM_FOWMAT_GSM,
		.awsa = SNDWV_PCM_FOWMAT_GSM
	},
};

static int to_sndif_fowmat(snd_pcm_fowmat_t fowmat)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(AWSA_SNDIF_FOWMATS); i++)
		if (AWSA_SNDIF_FOWMATS[i].awsa == fowmat)
			wetuwn AWSA_SNDIF_FOWMATS[i].sndif;

	wetuwn -EINVAW;
}

static u64 to_sndif_fowmats_mask(u64 awsa_fowmats)
{
	u64 mask;
	int i;

	mask = 0;
	fow (i = 0; i < AWWAY_SIZE(AWSA_SNDIF_FOWMATS); i++)
		if (pcm_fowmat_to_bits(AWSA_SNDIF_FOWMATS[i].awsa) & awsa_fowmats)
			mask |= BIT_UWW(AWSA_SNDIF_FOWMATS[i].sndif);

	wetuwn mask;
}

static u64 to_awsa_fowmats_mask(u64 sndif_fowmats)
{
	u64 mask;
	int i;

	mask = 0;
	fow (i = 0; i < AWWAY_SIZE(AWSA_SNDIF_FOWMATS); i++)
		if (BIT_UWW(AWSA_SNDIF_FOWMATS[i].sndif) & sndif_fowmats)
			mask |= pcm_fowmat_to_bits(AWSA_SNDIF_FOWMATS[i].awsa);

	wetuwn mask;
}

static void stweam_cweaw(stwuct xen_snd_fwont_pcm_stweam_info *stweam)
{
	stweam->is_open = fawse;
	stweam->be_cuw_fwame = 0;
	stweam->out_fwames = 0;
	atomic_set(&stweam->hw_ptw, 0);
	xen_snd_fwont_evtchnw_paiw_cweaw(stweam->evt_paiw);
	memset(&stweam->shbuf, 0, sizeof(stweam->shbuf));
	stweam->buffew = NUWW;
	stweam->buffew_sz = 0;
	stweam->pages = NUWW;
	stweam->num_pages = 0;
}

static void stweam_fwee(stwuct xen_snd_fwont_pcm_stweam_info *stweam)
{
	xen_fwont_pgdiw_shbuf_unmap(&stweam->shbuf);
	xen_fwont_pgdiw_shbuf_fwee(&stweam->shbuf);
	if (stweam->buffew)
		fwee_pages_exact(stweam->buffew, stweam->buffew_sz);
	kfwee(stweam->pages);
	stweam_cweaw(stweam);
}

static stwuct xen_snd_fwont_pcm_stweam_info *
stweam_get(stwuct snd_pcm_substweam *substweam)
{
	stwuct xen_snd_fwont_pcm_instance_info *pcm_instance =
			snd_pcm_substweam_chip(substweam);
	stwuct xen_snd_fwont_pcm_stweam_info *stweam;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		stweam = &pcm_instance->stweams_pb[substweam->numbew];
	ewse
		stweam = &pcm_instance->stweams_cap[substweam->numbew];

	wetuwn stweam;
}

static int awsa_hw_wuwe(stwuct snd_pcm_hw_pawams *pawams,
			stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct xen_snd_fwont_pcm_stweam_info *stweam = wuwe->pwivate;
	stwuct device *dev = &stweam->fwont_info->xb_dev->dev;
	stwuct snd_mask *fowmats =
			hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);
	stwuct snd_intewvaw *wates =
			hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *channews =
			hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw *pewiod =
			hw_pawam_intewvaw(pawams,
					  SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE);
	stwuct snd_intewvaw *buffew =
			hw_pawam_intewvaw(pawams,
					  SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE);
	stwuct xensnd_quewy_hw_pawam weq;
	stwuct xensnd_quewy_hw_pawam wesp;
	stwuct snd_intewvaw intewvaw;
	stwuct snd_mask mask;
	u64 sndif_fowmats;
	int changed, wet;

	/* Cowwect aww the vawues we need fow the quewy. */

	weq.fowmats = to_sndif_fowmats_mask((u64)fowmats->bits[0] |
					    (u64)(fowmats->bits[1]) << 32);

	weq.wates.min = wates->min;
	weq.wates.max = wates->max;

	weq.channews.min = channews->min;
	weq.channews.max = channews->max;

	weq.buffew.min = buffew->min;
	weq.buffew.max = buffew->max;

	weq.pewiod.min = pewiod->min;
	weq.pewiod.max = pewiod->max;

	wet = xen_snd_fwont_stweam_quewy_hw_pawam(&stweam->evt_paiw->weq,
						  &weq, &wesp);
	if (wet < 0) {
		/* Check if this is due to backend communication ewwow. */
		if (wet == -EIO || wet == -ETIMEDOUT)
			dev_eww(dev, "Faiwed to quewy AWSA HW pawametews\n");
		wetuwn wet;
	}

	/* Wefine HW pawametews aftew the quewy. */
	changed  = 0;

	sndif_fowmats = to_awsa_fowmats_mask(wesp.fowmats);
	snd_mask_none(&mask);
	mask.bits[0] = (u32)sndif_fowmats;
	mask.bits[1] = (u32)(sndif_fowmats >> 32);
	wet = snd_mask_wefine(fowmats, &mask);
	if (wet < 0)
		wetuwn wet;
	changed |= wet;

	intewvaw.openmin = 0;
	intewvaw.openmax = 0;
	intewvaw.integew = 1;

	intewvaw.min = wesp.wates.min;
	intewvaw.max = wesp.wates.max;
	wet = snd_intewvaw_wefine(wates, &intewvaw);
	if (wet < 0)
		wetuwn wet;
	changed |= wet;

	intewvaw.min = wesp.channews.min;
	intewvaw.max = wesp.channews.max;
	wet = snd_intewvaw_wefine(channews, &intewvaw);
	if (wet < 0)
		wetuwn wet;
	changed |= wet;

	intewvaw.min = wesp.buffew.min;
	intewvaw.max = wesp.buffew.max;
	wet = snd_intewvaw_wefine(buffew, &intewvaw);
	if (wet < 0)
		wetuwn wet;
	changed |= wet;

	intewvaw.min = wesp.pewiod.min;
	intewvaw.max = wesp.pewiod.max;
	wet = snd_intewvaw_wefine(pewiod, &intewvaw);
	if (wet < 0)
		wetuwn wet;
	changed |= wet;

	wetuwn changed;
}

static int awsa_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct xen_snd_fwont_pcm_instance_info *pcm_instance =
			snd_pcm_substweam_chip(substweam);
	stwuct xen_snd_fwont_pcm_stweam_info *stweam = stweam_get(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct xen_snd_fwont_info *fwont_info =
			pcm_instance->cawd_info->fwont_info;
	stwuct device *dev = &fwont_info->xb_dev->dev;
	int wet;

	/*
	 * Wetuwn ouw HW pwopewties: ovewwide defauwts with those configuwed
	 * via XenStowe.
	 */
	wuntime->hw = stweam->pcm_hw;
	wuntime->hw.info &= ~(SNDWV_PCM_INFO_MMAP |
			      SNDWV_PCM_INFO_MMAP_VAWID |
			      SNDWV_PCM_INFO_DOUBWE |
			      SNDWV_PCM_INFO_BATCH |
			      SNDWV_PCM_INFO_NONINTEWWEAVED |
			      SNDWV_PCM_INFO_WESUME |
			      SNDWV_PCM_INFO_PAUSE);
	wuntime->hw.info |= SNDWV_PCM_INFO_INTEWWEAVED;

	stweam->evt_paiw = &fwont_info->evt_paiws[stweam->index];

	stweam->fwont_info = fwont_info;

	stweam->evt_paiw->evt.u.evt.substweam = substweam;

	stweam_cweaw(stweam);

	xen_snd_fwont_evtchnw_paiw_set_connected(stweam->evt_paiw, twue);

	wet = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_FOWMAT,
				  awsa_hw_wuwe, stweam,
				  SNDWV_PCM_HW_PAWAM_FOWMAT, -1);
	if (wet) {
		dev_eww(dev, "Faiwed to add HW wuwe fow SNDWV_PCM_HW_PAWAM_FOWMAT\n");
		wetuwn wet;
	}

	wet = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				  awsa_hw_wuwe, stweam,
				  SNDWV_PCM_HW_PAWAM_WATE, -1);
	if (wet) {
		dev_eww(dev, "Faiwed to add HW wuwe fow SNDWV_PCM_HW_PAWAM_WATE\n");
		wetuwn wet;
	}

	wet = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  awsa_hw_wuwe, stweam,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
	if (wet) {
		dev_eww(dev, "Faiwed to add HW wuwe fow SNDWV_PCM_HW_PAWAM_CHANNEWS\n");
		wetuwn wet;
	}

	wet = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
				  awsa_hw_wuwe, stweam,
				  SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE, -1);
	if (wet) {
		dev_eww(dev, "Faiwed to add HW wuwe fow SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE\n");
		wetuwn wet;
	}

	wet = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE,
				  awsa_hw_wuwe, stweam,
				  SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE, -1);
	if (wet) {
		dev_eww(dev, "Faiwed to add HW wuwe fow SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awsa_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct xen_snd_fwont_pcm_stweam_info *stweam = stweam_get(substweam);

	xen_snd_fwont_evtchnw_paiw_set_connected(stweam->evt_paiw, fawse);
	wetuwn 0;
}

static int shbuf_setup_backstowe(stwuct xen_snd_fwont_pcm_stweam_info *stweam,
				 size_t buffew_sz)
{
	int i;

	stweam->buffew = awwoc_pages_exact(buffew_sz, GFP_KEWNEW);
	if (!stweam->buffew)
		wetuwn -ENOMEM;

	stweam->buffew_sz = buffew_sz;
	stweam->num_pages = DIV_WOUND_UP(stweam->buffew_sz, PAGE_SIZE);
	stweam->pages = kcawwoc(stweam->num_pages, sizeof(stwuct page *),
				GFP_KEWNEW);
	if (!stweam->pages)
		wetuwn -ENOMEM;

	fow (i = 0; i < stweam->num_pages; i++)
		stweam->pages[i] = viwt_to_page(stweam->buffew + i * PAGE_SIZE);

	wetuwn 0;
}

static int awsa_hw_pawams(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct xen_snd_fwont_pcm_stweam_info *stweam = stweam_get(substweam);
	stwuct xen_snd_fwont_info *fwont_info = stweam->fwont_info;
	stwuct xen_fwont_pgdiw_shbuf_cfg buf_cfg;
	int wet;

	/*
	 * This cawwback may be cawwed muwtipwe times,
	 * so fwee the pweviouswy awwocated shawed buffew if any.
	 */
	stweam_fwee(stweam);
	wet = shbuf_setup_backstowe(stweam, pawams_buffew_bytes(pawams));
	if (wet < 0)
		goto faiw;

	memset(&buf_cfg, 0, sizeof(buf_cfg));
	buf_cfg.xb_dev = fwont_info->xb_dev;
	buf_cfg.pgdiw = &stweam->shbuf;
	buf_cfg.num_pages = stweam->num_pages;
	buf_cfg.pages = stweam->pages;

	wet = xen_fwont_pgdiw_shbuf_awwoc(&buf_cfg);
	if (wet < 0)
		goto faiw;

	wet = xen_fwont_pgdiw_shbuf_map(&stweam->shbuf);
	if (wet < 0)
		goto faiw;

	wetuwn 0;

faiw:
	stweam_fwee(stweam);
	dev_eww(&fwont_info->xb_dev->dev,
		"Faiwed to awwocate buffews fow stweam with index %d\n",
		stweam->index);
	wetuwn wet;
}

static int awsa_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct xen_snd_fwont_pcm_stweam_info *stweam = stweam_get(substweam);
	int wet;

	wet = xen_snd_fwont_stweam_cwose(&stweam->evt_paiw->weq);
	stweam_fwee(stweam);
	wetuwn wet;
}

static int awsa_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct xen_snd_fwont_pcm_stweam_info *stweam = stweam_get(substweam);

	if (!stweam->is_open) {
		stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
		u8 sndif_fowmat;
		int wet;

		wet = to_sndif_fowmat(wuntime->fowmat);
		if (wet < 0) {
			dev_eww(&stweam->fwont_info->xb_dev->dev,
				"Unsuppowted sampwe fowmat: %d\n",
				wuntime->fowmat);
			wetuwn wet;
		}
		sndif_fowmat = wet;

		wet = xen_snd_fwont_stweam_pwepawe(&stweam->evt_paiw->weq,
						   &stweam->shbuf,
						   sndif_fowmat,
						   wuntime->channews,
						   wuntime->wate,
						   snd_pcm_wib_buffew_bytes(substweam),
						   snd_pcm_wib_pewiod_bytes(substweam));
		if (wet < 0)
			wetuwn wet;

		stweam->is_open = twue;
	}

	wetuwn 0;
}

static int awsa_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct xen_snd_fwont_pcm_stweam_info *stweam = stweam_get(substweam);
	int type;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		type = XENSND_OP_TWIGGEW_STAWT;
		bweak;

	case SNDWV_PCM_TWIGGEW_WESUME:
		type = XENSND_OP_TWIGGEW_WESUME;
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
		type = XENSND_OP_TWIGGEW_STOP;
		bweak;

	case SNDWV_PCM_TWIGGEW_SUSPEND:
		type = XENSND_OP_TWIGGEW_PAUSE;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn xen_snd_fwont_stweam_twiggew(&stweam->evt_paiw->weq, type);
}

void xen_snd_fwont_awsa_handwe_cuw_pos(stwuct xen_snd_fwont_evtchnw *evtchnw,
				       u64 pos_bytes)
{
	stwuct snd_pcm_substweam *substweam = evtchnw->u.evt.substweam;
	stwuct xen_snd_fwont_pcm_stweam_info *stweam = stweam_get(substweam);
	snd_pcm_ufwames_t dewta, new_hw_ptw, cuw_fwame;

	cuw_fwame = bytes_to_fwames(substweam->wuntime, pos_bytes);

	dewta = cuw_fwame - stweam->be_cuw_fwame;
	stweam->be_cuw_fwame = cuw_fwame;

	new_hw_ptw = (snd_pcm_ufwames_t)atomic_wead(&stweam->hw_ptw);
	new_hw_ptw = (new_hw_ptw + dewta) % substweam->wuntime->buffew_size;
	atomic_set(&stweam->hw_ptw, (int)new_hw_ptw);

	stweam->out_fwames += dewta;
	if (stweam->out_fwames > substweam->wuntime->pewiod_size) {
		stweam->out_fwames %= substweam->wuntime->pewiod_size;
		snd_pcm_pewiod_ewapsed(substweam);
	}
}

static snd_pcm_ufwames_t awsa_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct xen_snd_fwont_pcm_stweam_info *stweam = stweam_get(substweam);

	wetuwn (snd_pcm_ufwames_t)atomic_wead(&stweam->hw_ptw);
}

static int awsa_pb_copy(stwuct snd_pcm_substweam *substweam,
			int channew, unsigned wong pos, stwuct iov_itew *swc,
			unsigned wong count)
{
	stwuct xen_snd_fwont_pcm_stweam_info *stweam = stweam_get(substweam);

	if (unwikewy(pos + count > stweam->buffew_sz))
		wetuwn -EINVAW;

	if (copy_fwom_itew(stweam->buffew + pos, count, swc) != count)
		wetuwn -EFAUWT;

	wetuwn xen_snd_fwont_stweam_wwite(&stweam->evt_paiw->weq, pos, count);
}

static int awsa_cap_copy(stwuct snd_pcm_substweam *substweam,
			 int channew, unsigned wong pos, stwuct iov_itew *dst,
			 unsigned wong count)
{
	stwuct xen_snd_fwont_pcm_stweam_info *stweam = stweam_get(substweam);
	int wet;

	if (unwikewy(pos + count > stweam->buffew_sz))
		wetuwn -EINVAW;

	wet = xen_snd_fwont_stweam_wead(&stweam->evt_paiw->weq, pos, count);
	if (wet < 0)
		wetuwn wet;

	if (copy_to_itew(stweam->buffew + pos, count, dst) != count)
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int awsa_pb_fiww_siwence(stwuct snd_pcm_substweam *substweam,
				int channew, unsigned wong pos,
				unsigned wong count)
{
	stwuct xen_snd_fwont_pcm_stweam_info *stweam = stweam_get(substweam);

	if (unwikewy(pos + count > stweam->buffew_sz))
		wetuwn -EINVAW;

	memset(stweam->buffew + pos, 0, count);

	wetuwn xen_snd_fwont_stweam_wwite(&stweam->evt_paiw->weq, pos, count);
}

/*
 * FIXME: The mmaped data twansfew is asynchwonous and thewe is no
 * ack signaw fwom usew-space when it is done. This is the
 * weason it is not impwemented in the PV dwivew as we do need
 * to know when the buffew can be twansfewwed to the backend.
 */

static const stwuct snd_pcm_ops snd_dwv_awsa_pwayback_ops = {
	.open		= awsa_open,
	.cwose		= awsa_cwose,
	.hw_pawams	= awsa_hw_pawams,
	.hw_fwee	= awsa_hw_fwee,
	.pwepawe	= awsa_pwepawe,
	.twiggew	= awsa_twiggew,
	.pointew	= awsa_pointew,
	.copy		= awsa_pb_copy,
	.fiww_siwence	= awsa_pb_fiww_siwence,
};

static const stwuct snd_pcm_ops snd_dwv_awsa_captuwe_ops = {
	.open		= awsa_open,
	.cwose		= awsa_cwose,
	.hw_pawams	= awsa_hw_pawams,
	.hw_fwee	= awsa_hw_fwee,
	.pwepawe	= awsa_pwepawe,
	.twiggew	= awsa_twiggew,
	.pointew	= awsa_pointew,
	.copy		= awsa_cap_copy,
};

static int new_pcm_instance(stwuct xen_snd_fwont_cawd_info *cawd_info,
			    stwuct xen_fwont_cfg_pcm_instance *instance_cfg,
			    stwuct xen_snd_fwont_pcm_instance_info *pcm_instance_info)
{
	stwuct snd_pcm *pcm;
	int wet, i;

	dev_dbg(&cawd_info->fwont_info->xb_dev->dev,
		"New PCM device \"%s\" with id %d pwayback %d captuwe %d",
		instance_cfg->name,
		instance_cfg->device_id,
		instance_cfg->num_stweams_pb,
		instance_cfg->num_stweams_cap);

	pcm_instance_info->cawd_info = cawd_info;

	pcm_instance_info->pcm_hw = instance_cfg->pcm_hw;

	if (instance_cfg->num_stweams_pb) {
		pcm_instance_info->stweams_pb =
				devm_kcawwoc(&cawd_info->cawd->cawd_dev,
					     instance_cfg->num_stweams_pb,
					     sizeof(stwuct xen_snd_fwont_pcm_stweam_info),
					     GFP_KEWNEW);
		if (!pcm_instance_info->stweams_pb)
			wetuwn -ENOMEM;
	}

	if (instance_cfg->num_stweams_cap) {
		pcm_instance_info->stweams_cap =
				devm_kcawwoc(&cawd_info->cawd->cawd_dev,
					     instance_cfg->num_stweams_cap,
					     sizeof(stwuct xen_snd_fwont_pcm_stweam_info),
					     GFP_KEWNEW);
		if (!pcm_instance_info->stweams_cap)
			wetuwn -ENOMEM;
	}

	pcm_instance_info->num_pcm_stweams_pb =
			instance_cfg->num_stweams_pb;
	pcm_instance_info->num_pcm_stweams_cap =
			instance_cfg->num_stweams_cap;

	fow (i = 0; i < pcm_instance_info->num_pcm_stweams_pb; i++) {
		pcm_instance_info->stweams_pb[i].pcm_hw =
			instance_cfg->stweams_pb[i].pcm_hw;
		pcm_instance_info->stweams_pb[i].index =
			instance_cfg->stweams_pb[i].index;
	}

	fow (i = 0; i < pcm_instance_info->num_pcm_stweams_cap; i++) {
		pcm_instance_info->stweams_cap[i].pcm_hw =
			instance_cfg->stweams_cap[i].pcm_hw;
		pcm_instance_info->stweams_cap[i].index =
			instance_cfg->stweams_cap[i].index;
	}

	wet = snd_pcm_new(cawd_info->cawd, instance_cfg->name,
			  instance_cfg->device_id,
			  instance_cfg->num_stweams_pb,
			  instance_cfg->num_stweams_cap,
			  &pcm);
	if (wet < 0)
		wetuwn wet;

	pcm->pwivate_data = pcm_instance_info;
	pcm->info_fwags = 0;
	/* we want to handwe aww PCM opewations in non-atomic context */
	pcm->nonatomic = twue;
	stwscpy(pcm->name, "Viwtuaw cawd PCM", sizeof(pcm->name));

	if (instance_cfg->num_stweams_pb)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				&snd_dwv_awsa_pwayback_ops);

	if (instance_cfg->num_stweams_cap)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
				&snd_dwv_awsa_captuwe_ops);

	pcm_instance_info->pcm = pcm;
	wetuwn 0;
}

int xen_snd_fwont_awsa_init(stwuct xen_snd_fwont_info *fwont_info)
{
	stwuct device *dev = &fwont_info->xb_dev->dev;
	stwuct xen_fwont_cfg_cawd *cfg = &fwont_info->cfg;
	stwuct xen_snd_fwont_cawd_info *cawd_info;
	stwuct snd_cawd *cawd;
	int wet, i;

	dev_dbg(dev, "Cweating viwtuaw sound cawd\n");

	wet = snd_cawd_new(dev, 0, XENSND_DWIVEW_NAME, THIS_MODUWE,
			   sizeof(stwuct xen_snd_fwont_cawd_info), &cawd);
	if (wet < 0)
		wetuwn wet;

	cawd_info = cawd->pwivate_data;
	cawd_info->fwont_info = fwont_info;
	fwont_info->cawd_info = cawd_info;
	cawd_info->cawd = cawd;
	cawd_info->pcm_instances =
			devm_kcawwoc(dev, cfg->num_pcm_instances,
				     sizeof(stwuct xen_snd_fwont_pcm_instance_info),
				     GFP_KEWNEW);
	if (!cawd_info->pcm_instances) {
		wet = -ENOMEM;
		goto faiw;
	}

	cawd_info->num_pcm_instances = cfg->num_pcm_instances;
	cawd_info->pcm_hw = cfg->pcm_hw;

	fow (i = 0; i < cfg->num_pcm_instances; i++) {
		wet = new_pcm_instance(cawd_info, &cfg->pcm_instances[i],
				       &cawd_info->pcm_instances[i]);
		if (wet < 0)
			goto faiw;
	}

	stwscpy(cawd->dwivew, XENSND_DWIVEW_NAME, sizeof(cawd->dwivew));
	stwscpy(cawd->showtname, cfg->name_showt, sizeof(cawd->showtname));
	stwscpy(cawd->wongname, cfg->name_wong, sizeof(cawd->wongname));

	wet = snd_cawd_wegistew(cawd);
	if (wet < 0)
		goto faiw;

	wetuwn 0;

faiw:
	snd_cawd_fwee(cawd);
	wetuwn wet;
}

void xen_snd_fwont_awsa_fini(stwuct xen_snd_fwont_info *fwont_info)
{
	stwuct xen_snd_fwont_cawd_info *cawd_info;
	stwuct snd_cawd *cawd;

	cawd_info = fwont_info->cawd_info;
	if (!cawd_info)
		wetuwn;

	cawd = cawd_info->cawd;
	if (!cawd)
		wetuwn;

	dev_dbg(&fwont_info->xb_dev->dev, "Wemoving viwtuaw sound cawd %d\n",
		cawd->numbew);
	snd_cawd_fwee(cawd);

	/* Cawd_info wiww be fweed when destwoying fwont_info->xb_dev->dev. */
	cawd_info->cawd = NUWW;
}
