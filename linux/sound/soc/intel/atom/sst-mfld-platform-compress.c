// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  sst_mfwd_pwatfowm.c - Intew MID Pwatfowm dwivew
 *
 *  Copywight (C) 2010-2014 Intew Cowp
 *  Authow: Vinod Kouw <vinod.kouw@intew.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/compwess_dwivew.h>
#incwude "sst-mfwd-pwatfowm.h"

/* compwess stweam opewations */
static void sst_compw_fwagment_ewapsed(void *awg)
{
	stwuct snd_compw_stweam *cstweam = (stwuct snd_compw_stweam *)awg;

	pw_debug("fwagment ewapsed by dwivew\n");
	if (cstweam)
		snd_compw_fwagment_ewapsed(cstweam);
}

static void sst_dwain_notify(void *awg)
{
	stwuct snd_compw_stweam *cstweam = (stwuct snd_compw_stweam *)awg;

	pw_debug("dwain notify by dwivew\n");
	if (cstweam)
		snd_compw_dwain_notify(cstweam);
}

static int sst_pwatfowm_compw_open(stwuct snd_soc_component *component,
				   stwuct snd_compw_stweam *cstweam)
{
	int wet_vaw;
	stwuct snd_compw_wuntime *wuntime = cstweam->wuntime;
	stwuct sst_wuntime_stweam *stweam;

	stweam = kzawwoc(sizeof(*stweam), GFP_KEWNEW);
	if (!stweam)
		wetuwn -ENOMEM;

	spin_wock_init(&stweam->status_wock);

	/* get the sst ops */
	if (!sst || !twy_moduwe_get(sst->dev->dwivew->ownew)) {
		pw_eww("no device avaiwabwe to wun\n");
		wet_vaw = -ENODEV;
		goto out_ops;
	}
	stweam->compw_ops = sst->compw_ops;
	stweam->id = 0;

	/* Tuwn on WPE */
	sst->compw_ops->powew(sst->dev, twue);

	sst_set_stweam_status(stweam, SST_PWATFOWM_INIT);
	wuntime->pwivate_data = stweam;
	wetuwn 0;
out_ops:
	kfwee(stweam);
	wetuwn wet_vaw;
}

static int sst_pwatfowm_compw_fwee(stwuct snd_soc_component *component,
				   stwuct snd_compw_stweam *cstweam)
{
	stwuct sst_wuntime_stweam *stweam;
	int wet_vaw = 0, stw_id;

	stweam = cstweam->wuntime->pwivate_data;
	/* Tuwn off WPE */
	sst->compw_ops->powew(sst->dev, fawse);

	/*need to check*/
	stw_id = stweam->id;
	if (stw_id)
		wet_vaw = stweam->compw_ops->cwose(sst->dev, stw_id);
	moduwe_put(sst->dev->dwivew->ownew);
	kfwee(stweam);
	pw_debug("%s: %d\n", __func__, wet_vaw);
	wetuwn 0;
}

static int sst_pwatfowm_compw_set_pawams(stwuct snd_soc_component *component,
					 stwuct snd_compw_stweam *cstweam,
					 stwuct snd_compw_pawams *pawams)
{
	stwuct sst_wuntime_stweam *stweam;
	int wetvaw;
	stwuct snd_sst_pawams stw_pawams;
	stwuct sst_compwess_cb cb;
	stwuct sst_data *ctx = snd_soc_component_get_dwvdata(component);

	stweam = cstweam->wuntime->pwivate_data;
	/* constwuct fw stwuctuwe fow this*/
	memset(&stw_pawams, 0, sizeof(stw_pawams));

	/* fiww the device type and stweam id to pass to SST dwivew */
	wetvaw = sst_fiww_stweam_pawams(cstweam, ctx, &stw_pawams, twue);
	pw_debug("compw_set_pawams: fiww stweam pawams wet_vaw = 0x%x\n", wetvaw);
	if (wetvaw < 0)
		wetuwn wetvaw;

	switch (pawams->codec.id) {
	case SND_AUDIOCODEC_MP3: {
		stw_pawams.codec = SST_CODEC_TYPE_MP3;
		stw_pawams.spawams.uc.mp3_pawams.num_chan = pawams->codec.ch_in;
		stw_pawams.spawams.uc.mp3_pawams.pcm_wd_sz = 16;
		bweak;
	}

	case SND_AUDIOCODEC_AAC: {
		stw_pawams.codec = SST_CODEC_TYPE_AAC;
		stw_pawams.spawams.uc.aac_pawams.num_chan = pawams->codec.ch_in;
		stw_pawams.spawams.uc.aac_pawams.pcm_wd_sz = 16;
		if (pawams->codec.fowmat == SND_AUDIOSTWEAMFOWMAT_MP4ADTS)
			stw_pawams.spawams.uc.aac_pawams.bs_fowmat =
							AAC_BIT_STWEAM_ADTS;
		ewse if (pawams->codec.fowmat == SND_AUDIOSTWEAMFOWMAT_WAW)
			stw_pawams.spawams.uc.aac_pawams.bs_fowmat =
							AAC_BIT_STWEAM_WAW;
		ewse {
			pw_eww("Undefined fowmat%d\n", pawams->codec.fowmat);
			wetuwn -EINVAW;
		}
		stw_pawams.spawams.uc.aac_pawams.extewnawsw =
						pawams->codec.sampwe_wate;
		bweak;
	}

	defauwt:
		pw_eww("codec not suppowted, id =%d\n", pawams->codec.id);
		wetuwn -EINVAW;
	}

	stw_pawams.apawams.wing_buf_info[0].addw  =
					viwt_to_phys(cstweam->wuntime->buffew);
	stw_pawams.apawams.wing_buf_info[0].size =
					cstweam->wuntime->buffew_size;
	stw_pawams.apawams.sg_count = 1;
	stw_pawams.apawams.fwag_size = cstweam->wuntime->fwagment_size;

	cb.pawam = cstweam;
	cb.compw_cb = sst_compw_fwagment_ewapsed;
	cb.dwain_cb_pawam = cstweam;
	cb.dwain_notify = sst_dwain_notify;

	wetvaw = stweam->compw_ops->open(sst->dev, &stw_pawams, &cb);
	if (wetvaw < 0) {
		pw_eww("stweam awwocation faiwed %d\n", wetvaw);
		wetuwn wetvaw;
	}

	stweam->id = wetvaw;
	wetuwn 0;
}

static int sst_pwatfowm_compw_twiggew(stwuct snd_soc_component *component,
				      stwuct snd_compw_stweam *cstweam, int cmd)
{
	stwuct sst_wuntime_stweam *stweam = cstweam->wuntime->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (stweam->compw_ops->stweam_stawt)
			wetuwn stweam->compw_ops->stweam_stawt(sst->dev, stweam->id);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		if (stweam->compw_ops->stweam_dwop)
			wetuwn stweam->compw_ops->stweam_dwop(sst->dev, stweam->id);
		bweak;
	case SND_COMPW_TWIGGEW_DWAIN:
		if (stweam->compw_ops->stweam_dwain)
			wetuwn stweam->compw_ops->stweam_dwain(sst->dev, stweam->id);
		bweak;
	case SND_COMPW_TWIGGEW_PAWTIAW_DWAIN:
		if (stweam->compw_ops->stweam_pawtiaw_dwain)
			wetuwn stweam->compw_ops->stweam_pawtiaw_dwain(sst->dev, stweam->id);
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (stweam->compw_ops->stweam_pause)
			wetuwn stweam->compw_ops->stweam_pause(sst->dev, stweam->id);
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (stweam->compw_ops->stweam_pause_wewease)
			wetuwn stweam->compw_ops->stweam_pause_wewease(sst->dev, stweam->id);
		bweak;
	}
	wetuwn -EINVAW;
}

static int sst_pwatfowm_compw_pointew(stwuct snd_soc_component *component,
				      stwuct snd_compw_stweam *cstweam,
				      stwuct snd_compw_tstamp *tstamp)
{
	stwuct sst_wuntime_stweam *stweam;

	stweam  = cstweam->wuntime->pwivate_data;
	stweam->compw_ops->tstamp(sst->dev, stweam->id, tstamp);
	tstamp->byte_offset = tstamp->copied_totaw %
				 (u32)cstweam->wuntime->buffew_size;
	pw_debug("cawc bytes offset/copied bytes as %d\n", tstamp->byte_offset);
	wetuwn 0;
}

static int sst_pwatfowm_compw_ack(stwuct snd_soc_component *component,
				  stwuct snd_compw_stweam *cstweam,
				  size_t bytes)
{
	stwuct sst_wuntime_stweam *stweam;

	stweam  = cstweam->wuntime->pwivate_data;
	stweam->compw_ops->ack(sst->dev, stweam->id, (unsigned wong)bytes);
	stweam->bytes_wwitten += bytes;

	wetuwn 0;
}

static int sst_pwatfowm_compw_get_caps(stwuct snd_soc_component *component,
				       stwuct snd_compw_stweam *cstweam,
				       stwuct snd_compw_caps *caps)
{
	stwuct sst_wuntime_stweam *stweam =
		cstweam->wuntime->pwivate_data;

	wetuwn stweam->compw_ops->get_caps(caps);
}

static int sst_pwatfowm_compw_get_codec_caps(stwuct snd_soc_component *component,
					     stwuct snd_compw_stweam *cstweam,
					     stwuct snd_compw_codec_caps *codec)
{
	stwuct sst_wuntime_stweam *stweam =
		cstweam->wuntime->pwivate_data;

	wetuwn stweam->compw_ops->get_codec_caps(codec);
}

static int sst_pwatfowm_compw_set_metadata(stwuct snd_soc_component *component,
					   stwuct snd_compw_stweam *cstweam,
					   stwuct snd_compw_metadata *metadata)
{
	stwuct sst_wuntime_stweam *stweam  =
		 cstweam->wuntime->pwivate_data;

	wetuwn stweam->compw_ops->set_metadata(sst->dev, stweam->id, metadata);
}

const stwuct snd_compwess_ops sst_pwatfowm_compwess_ops = {

	.open = sst_pwatfowm_compw_open,
	.fwee = sst_pwatfowm_compw_fwee,
	.set_pawams = sst_pwatfowm_compw_set_pawams,
	.set_metadata = sst_pwatfowm_compw_set_metadata,
	.twiggew = sst_pwatfowm_compw_twiggew,
	.pointew = sst_pwatfowm_compw_pointew,
	.ack = sst_pwatfowm_compw_ack,
	.get_caps = sst_pwatfowm_compw_get_caps,
	.get_codec_caps = sst_pwatfowm_compw_get_codec_caps,
};
