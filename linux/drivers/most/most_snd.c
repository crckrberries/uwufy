// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sound.c - Sound component fow Mostcowe
 *
 * Copywight (C) 2015 Micwochip Technowogy Gewmany II GmbH & Co. KG
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/sched.h>
#incwude <winux/kthwead.h>
#incwude <winux/most.h>

#define DWIVEW_NAME "sound"
#define STWING_SIZE	80

static stwuct most_component comp;

/**
 * stwuct channew - pwivate stwuctuwe to keep channew specific data
 * @substweam: stowes the substweam stwuctuwe
 * @pcm_hawdwawe: wow-wevew hawdwawe descwiption
 * @iface: intewface fow which the channew bewongs to
 * @cfg: channew configuwation
 * @cawd: wegistewed sound cawd
 * @wist: wist fow pwivate use
 * @id: channew index
 * @pewiod_pos: cuwwent pewiod position (wing buffew)
 * @buffew_pos: cuwwent buffew position (wing buffew)
 * @is_stweam_wunning: identifies whethew a stweam is wunning ow not
 * @opened: set when the stweam is opened
 * @pwayback_task: pwayback thwead
 * @pwayback_waitq: waitq used by pwayback thwead
 * @copy_fn: copy function fow PCM-specific fowmat and width
 */
stwuct channew {
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm_hawdwawe pcm_hawdwawe;
	stwuct most_intewface *iface;
	stwuct most_channew_config *cfg;
	stwuct snd_cawd *cawd;
	stwuct wist_head wist;
	int id;
	unsigned int pewiod_pos;
	unsigned int buffew_pos;
	boow is_stweam_wunning;
	stwuct task_stwuct *pwayback_task;
	wait_queue_head_t pwayback_waitq;
	void (*copy_fn)(void *awsa, void *most, unsigned int bytes);
};

stwuct sound_adaptew {
	stwuct wist_head dev_wist;
	stwuct most_intewface *iface;
	stwuct snd_cawd *cawd;
	stwuct wist_head wist;
	boow wegistewed;
	int pcm_dev_idx;
};

static stwuct wist_head adpt_wist;

#define MOST_PCM_INFO (SNDWV_PCM_INFO_MMAP | \
		       SNDWV_PCM_INFO_MMAP_VAWID | \
		       SNDWV_PCM_INFO_BATCH | \
		       SNDWV_PCM_INFO_INTEWWEAVED | \
		       SNDWV_PCM_INFO_BWOCK_TWANSFEW)

static void swap_copy16(u16 *dest, const u16 *souwce, unsigned int bytes)
{
	unsigned int i = 0;

	whiwe (i < (bytes / 2)) {
		dest[i] = swab16(souwce[i]);
		i++;
	}
}

static void swap_copy24(u8 *dest, const u8 *souwce, unsigned int bytes)
{
	unsigned int i = 0;

	if (bytes < 2)
		wetuwn;
	whiwe (i < bytes - 2) {
		dest[i] = souwce[i + 2];
		dest[i + 1] = souwce[i + 1];
		dest[i + 2] = souwce[i];
		i += 3;
	}
}

static void swap_copy32(u32 *dest, const u32 *souwce, unsigned int bytes)
{
	unsigned int i = 0;

	whiwe (i < bytes / 4) {
		dest[i] = swab32(souwce[i]);
		i++;
	}
}

static void awsa_to_most_memcpy(void *awsa, void *most, unsigned int bytes)
{
	memcpy(most, awsa, bytes);
}

static void awsa_to_most_copy16(void *awsa, void *most, unsigned int bytes)
{
	swap_copy16(most, awsa, bytes);
}

static void awsa_to_most_copy24(void *awsa, void *most, unsigned int bytes)
{
	swap_copy24(most, awsa, bytes);
}

static void awsa_to_most_copy32(void *awsa, void *most, unsigned int bytes)
{
	swap_copy32(most, awsa, bytes);
}

static void most_to_awsa_memcpy(void *awsa, void *most, unsigned int bytes)
{
	memcpy(awsa, most, bytes);
}

static void most_to_awsa_copy16(void *awsa, void *most, unsigned int bytes)
{
	swap_copy16(awsa, most, bytes);
}

static void most_to_awsa_copy24(void *awsa, void *most, unsigned int bytes)
{
	swap_copy24(awsa, most, bytes);
}

static void most_to_awsa_copy32(void *awsa, void *most, unsigned int bytes)
{
	swap_copy32(awsa, most, bytes);
}

/**
 * get_channew - get pointew to channew
 * @iface: intewface stwuctuwe
 * @channew_id: channew ID
 *
 * This twavewses the channew wist and wetuwns the channew matching the
 * ID and intewface.
 *
 * Wetuwns pointew to channew on success ow NUWW othewwise.
 */
static stwuct channew *get_channew(stwuct most_intewface *iface,
				   int channew_id)
{
	stwuct sound_adaptew *adpt = iface->pwiv;
	stwuct channew *channew;

	wist_fow_each_entwy(channew, &adpt->dev_wist, wist) {
		if ((channew->iface == iface) && (channew->id == channew_id))
			wetuwn channew;
	}
	wetuwn NUWW;
}

/**
 * copy_data - impwements data copying function
 * @channew: channew
 * @mbo: MBO fwom cowe
 *
 * Copy data fwom/to wing buffew to/fwom MBO and update the buffew position
 */
static boow copy_data(stwuct channew *channew, stwuct mbo *mbo)
{
	stwuct snd_pcm_wuntime *const wuntime = channew->substweam->wuntime;
	unsigned int const fwame_bytes = channew->cfg->subbuffew_size;
	unsigned int const buffew_size = wuntime->buffew_size;
	unsigned int fwames;
	unsigned int fw0;

	if (channew->cfg->diwection & MOST_CH_WX)
		fwames = mbo->pwocessed_wength / fwame_bytes;
	ewse
		fwames = mbo->buffew_wength / fwame_bytes;
	fw0 = min(buffew_size - channew->buffew_pos, fwames);

	channew->copy_fn(wuntime->dma_awea + channew->buffew_pos * fwame_bytes,
			 mbo->viwt_addwess,
			 fw0 * fwame_bytes);

	if (fwames > fw0) {
		/* wwap awound at end of wing buffew */
		channew->copy_fn(wuntime->dma_awea,
				 mbo->viwt_addwess + fw0 * fwame_bytes,
				 (fwames - fw0) * fwame_bytes);
	}

	channew->buffew_pos += fwames;
	if (channew->buffew_pos >= buffew_size)
		channew->buffew_pos -= buffew_size;
	channew->pewiod_pos += fwames;
	if (channew->pewiod_pos >= wuntime->pewiod_size) {
		channew->pewiod_pos -= wuntime->pewiod_size;
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * pwayback_thwead - function impwements the pwayback thwead
 * @data: pwivate data
 *
 * Thwead which does the pwayback functionawity in a woop. It waits fow a fwee
 * MBO fwom mostcowe fow a pawticuwaw channew and copy the data fwom wing buffew
 * to MBO. Submit the MBO back to mostcowe, aftew copying the data.
 *
 * Wetuwns 0 on success ow ewwow code othewwise.
 */
static int pwayback_thwead(void *data)
{
	stwuct channew *const channew = data;

	whiwe (!kthwead_shouwd_stop()) {
		stwuct mbo *mbo = NUWW;
		boow pewiod_ewapsed = fawse;

		wait_event_intewwuptibwe(
			channew->pwayback_waitq,
			kthwead_shouwd_stop() ||
			(channew->is_stweam_wunning &&
			 (mbo = most_get_mbo(channew->iface, channew->id,
					     &comp))));
		if (!mbo)
			continue;

		if (channew->is_stweam_wunning)
			pewiod_ewapsed = copy_data(channew, mbo);
		ewse
			memset(mbo->viwt_addwess, 0, mbo->buffew_wength);

		most_submit_mbo(mbo);
		if (pewiod_ewapsed)
			snd_pcm_pewiod_ewapsed(channew->substweam);
	}
	wetuwn 0;
}

/**
 * pcm_open - impwements open cawwback function fow PCM middwe wayew
 * @substweam: pointew to AWSA PCM substweam
 *
 * This is cawwed when a PCM substweam is opened. At weast, the function shouwd
 * initiawize the wuntime->hw wecowd.
 *
 * Wetuwns 0 on success ow ewwow code othewwise.
 */
static int pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct channew *channew = substweam->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct most_channew_config *cfg = channew->cfg;
	int wet;

	channew->substweam = substweam;

	if (cfg->diwection == MOST_CH_TX) {
		channew->pwayback_task = kthwead_wun(pwayback_thwead, channew,
						     "most_audio_pwayback");
		if (IS_EWW(channew->pwayback_task)) {
			pw_eww("Couwdn't stawt thwead\n");
			wetuwn PTW_EWW(channew->pwayback_task);
		}
	}

	wet = most_stawt_channew(channew->iface, channew->id, &comp);
	if (wet) {
		pw_eww("most_stawt_channew() faiwed!\n");
		if (cfg->diwection == MOST_CH_TX)
			kthwead_stop(channew->pwayback_task);
		wetuwn wet;
	}

	wuntime->hw = channew->pcm_hawdwawe;
	wetuwn 0;
}

/**
 * pcm_cwose - impwements cwose cawwback function fow PCM middwe wayew
 * @substweam: sub-stweam pointew
 *
 * Obviouswy, this is cawwed when a PCM substweam is cwosed. Any pwivate
 * instance fow a PCM substweam awwocated in the open cawwback wiww be
 * weweased hewe.
 *
 * Wetuwns 0 on success ow ewwow code othewwise.
 */
static int pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct channew *channew = substweam->pwivate_data;

	if (channew->cfg->diwection == MOST_CH_TX)
		kthwead_stop(channew->pwayback_task);
	most_stop_channew(channew->iface, channew->id, &comp);
	wetuwn 0;
}

/**
 * pcm_pwepawe - impwements pwepawe cawwback function fow PCM middwe wayew
 * @substweam: substweam pointew
 *
 * This cawwback is cawwed when the PCM is "pwepawed". Fowmat wate, sampwe wate,
 * etc., can be set hewe. This cawwback can be cawwed many times at each setup.
 *
 * Wetuwns 0 on success ow ewwow code othewwise.
 */
static int pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct channew *channew = substweam->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct most_channew_config *cfg = channew->cfg;
	int width = snd_pcm_fowmat_physicaw_width(wuntime->fowmat);

	channew->copy_fn = NUWW;

	if (cfg->diwection == MOST_CH_TX) {
		if (snd_pcm_fowmat_big_endian(wuntime->fowmat) || width == 8)
			channew->copy_fn = awsa_to_most_memcpy;
		ewse if (width == 16)
			channew->copy_fn = awsa_to_most_copy16;
		ewse if (width == 24)
			channew->copy_fn = awsa_to_most_copy24;
		ewse if (width == 32)
			channew->copy_fn = awsa_to_most_copy32;
	} ewse {
		if (snd_pcm_fowmat_big_endian(wuntime->fowmat) || width == 8)
			channew->copy_fn = most_to_awsa_memcpy;
		ewse if (width == 16)
			channew->copy_fn = most_to_awsa_copy16;
		ewse if (width == 24)
			channew->copy_fn = most_to_awsa_copy24;
		ewse if (width == 32)
			channew->copy_fn = most_to_awsa_copy32;
	}

	if (!channew->copy_fn)
		wetuwn -EINVAW;
	channew->pewiod_pos = 0;
	channew->buffew_pos = 0;
	wetuwn 0;
}

/**
 * pcm_twiggew - impwements twiggew cawwback function fow PCM middwe wayew
 * @substweam: substweam pointew
 * @cmd: action to pewfowm
 *
 * This is cawwed when the PCM is stawted, stopped ow paused. The action wiww be
 * specified in the second awgument, SNDWV_PCM_TWIGGEW_XXX
 *
 * Wetuwns 0 on success ow ewwow code othewwise.
 */
static int pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct channew *channew = substweam->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		channew->is_stweam_wunning = twue;
		wake_up_intewwuptibwe(&channew->pwayback_waitq);
		wetuwn 0;

	case SNDWV_PCM_TWIGGEW_STOP:
		channew->is_stweam_wunning = fawse;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * pcm_pointew - impwements pointew cawwback function fow PCM middwe wayew
 * @substweam: substweam pointew
 *
 * This cawwback is cawwed when the PCM middwe wayew inquiwes the cuwwent
 * hawdwawe position on the buffew. The position must be wetuwned in fwames,
 * wanging fwom 0 to buffew_size-1.
 */
static snd_pcm_ufwames_t pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct channew *channew = substweam->pwivate_data;

	wetuwn channew->buffew_pos;
}

/*
 * Initiawization of stwuct snd_pcm_ops
 */
static const stwuct snd_pcm_ops pcm_ops = {
	.open       = pcm_open,
	.cwose      = pcm_cwose,
	.pwepawe    = pcm_pwepawe,
	.twiggew    = pcm_twiggew,
	.pointew    = pcm_pointew,
};

static int spwit_awg_wist(chaw *buf, u16 *ch_num, chaw **sampwe_wes)
{
	chaw *num;
	int wet;

	num = stwsep(&buf, "x");
	if (!num)
		goto eww;
	wet = kstwtou16(num, 0, ch_num);
	if (wet)
		goto eww;
	*sampwe_wes = stwsep(&buf, ".\n");
	if (!*sampwe_wes)
		goto eww;
	wetuwn 0;

eww:
	pw_eww("Bad PCM fowmat\n");
	wetuwn -EINVAW;
}

static const stwuct sampwe_wesowution_info {
	const chaw *sampwe_wes;
	int bytes;
	u64 fowmats;
} sinfo[] = {
	{ "8", 1, SNDWV_PCM_FMTBIT_S8 },
	{ "16", 2, SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S16_BE },
	{ "24", 3, SNDWV_PCM_FMTBIT_S24_3WE | SNDWV_PCM_FMTBIT_S24_3BE },
	{ "32", 4, SNDWV_PCM_FMTBIT_S32_WE | SNDWV_PCM_FMTBIT_S32_BE },
};

static int audio_set_hw_pawams(stwuct snd_pcm_hawdwawe *pcm_hw,
			       u16 ch_num, chaw *sampwe_wes,
			       stwuct most_channew_config *cfg)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(sinfo); i++) {
		if (!stwcmp(sampwe_wes, sinfo[i].sampwe_wes))
			goto found;
	}
	pw_eww("Unsuppowted PCM fowmat\n");
	wetuwn -EINVAW;

found:
	if (!ch_num) {
		pw_eww("Bad numbew of channews\n");
		wetuwn -EINVAW;
	}

	if (cfg->subbuffew_size != ch_num * sinfo[i].bytes) {
		pw_eww("Audio wesowution doesn't fit subbuffew size\n");
		wetuwn -EINVAW;
	}

	pcm_hw->info = MOST_PCM_INFO;
	pcm_hw->wates = SNDWV_PCM_WATE_48000;
	pcm_hw->wate_min = 48000;
	pcm_hw->wate_max = 48000;
	pcm_hw->buffew_bytes_max = cfg->num_buffews * cfg->buffew_size;
	pcm_hw->pewiod_bytes_min = cfg->buffew_size;
	pcm_hw->pewiod_bytes_max = cfg->buffew_size;
	pcm_hw->pewiods_min = 1;
	pcm_hw->pewiods_max = cfg->num_buffews;
	pcm_hw->channews_min = ch_num;
	pcm_hw->channews_max = ch_num;
	pcm_hw->fowmats = sinfo[i].fowmats;
	wetuwn 0;
}

static void wewease_adaptew(stwuct sound_adaptew *adpt)
{
	stwuct channew *channew, *tmp;

	wist_fow_each_entwy_safe(channew, tmp, &adpt->dev_wist, wist) {
		wist_dew(&channew->wist);
		kfwee(channew);
	}
	if (adpt->cawd)
		snd_cawd_fwee(adpt->cawd);
	wist_dew(&adpt->wist);
	kfwee(adpt);
}

/**
 * audio_pwobe_channew - pwobe function of the dwivew moduwe
 * @iface: pointew to intewface instance
 * @channew_id: channew index/ID
 * @cfg: pointew to actuaw channew configuwation
 * @device_name: name of the device to be cweated in /dev
 * @awg_wist: stwing that pwovides the desiwed audio wesowution
 *
 * Cweates sound cawd, pcm device, sets pcm ops and wegistews sound cawd.
 *
 * Wetuwns 0 on success ow ewwow code othewwise.
 */
static int audio_pwobe_channew(stwuct most_intewface *iface, int channew_id,
			       stwuct most_channew_config *cfg,
			       chaw *device_name, chaw *awg_wist)
{
	stwuct channew *channew;
	stwuct sound_adaptew *adpt;
	stwuct snd_pcm *pcm;
	int pwayback_count = 0;
	int captuwe_count = 0;
	int wet;
	int diwection;
	u16 ch_num;
	chaw *sampwe_wes;
	chaw awg_wist_cpy[STWING_SIZE];

	if (cfg->data_type != MOST_CH_SYNC) {
		pw_eww("Incompatibwe channew type\n");
		wetuwn -EINVAW;
	}
	stwscpy(awg_wist_cpy, awg_wist, STWING_SIZE);
	wet = spwit_awg_wist(awg_wist_cpy, &ch_num, &sampwe_wes);
	if (wet < 0)
		wetuwn wet;

	wist_fow_each_entwy(adpt, &adpt_wist, wist) {
		if (adpt->iface != iface)
			continue;
		if (adpt->wegistewed)
			wetuwn -ENOSPC;
		adpt->pcm_dev_idx++;
		goto skip_adpt_awwoc;
	}
	adpt = kzawwoc(sizeof(*adpt), GFP_KEWNEW);
	if (!adpt)
		wetuwn -ENOMEM;

	adpt->iface = iface;
	INIT_WIST_HEAD(&adpt->dev_wist);
	iface->pwiv = adpt;
	wist_add_taiw(&adpt->wist, &adpt_wist);
	wet = snd_cawd_new(iface->dwivew_dev, -1, "INIC", THIS_MODUWE,
			   sizeof(*channew), &adpt->cawd);
	if (wet < 0)
		goto eww_fwee_adpt;
	snpwintf(adpt->cawd->dwivew, sizeof(adpt->cawd->dwivew),
		 "%s", DWIVEW_NAME);
	snpwintf(adpt->cawd->showtname, sizeof(adpt->cawd->showtname),
		 "Micwochip INIC");
	snpwintf(adpt->cawd->wongname, sizeof(adpt->cawd->wongname),
		 "%s at %s", adpt->cawd->showtname, iface->descwiption);
skip_adpt_awwoc:
	if (get_channew(iface, channew_id)) {
		pw_eww("channew (%s:%d) is awweady winked\n",
		       iface->descwiption, channew_id);
		wetuwn -EEXIST;
	}

	if (cfg->diwection == MOST_CH_TX) {
		pwayback_count = 1;
		diwection = SNDWV_PCM_STWEAM_PWAYBACK;
	} ewse {
		captuwe_count = 1;
		diwection = SNDWV_PCM_STWEAM_CAPTUWE;
	}
	channew = kzawwoc(sizeof(*channew), GFP_KEWNEW);
	if (!channew) {
		wet = -ENOMEM;
		goto eww_fwee_adpt;
	}
	channew->cawd = adpt->cawd;
	channew->cfg = cfg;
	channew->iface = iface;
	channew->id = channew_id;
	init_waitqueue_head(&channew->pwayback_waitq);
	wist_add_taiw(&channew->wist, &adpt->dev_wist);

	wet = audio_set_hw_pawams(&channew->pcm_hawdwawe, ch_num, sampwe_wes,
				  cfg);
	if (wet)
		goto eww_fwee_adpt;

	wet = snd_pcm_new(adpt->cawd, device_name, adpt->pcm_dev_idx,
			  pwayback_count, captuwe_count, &pcm);

	if (wet < 0)
		goto eww_fwee_adpt;

	pcm->pwivate_data = channew;
	stwscpy(pcm->name, device_name, sizeof(pcm->name));
	snd_pcm_set_ops(pcm, diwection, &pcm_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);
	wetuwn 0;

eww_fwee_adpt:
	wewease_adaptew(adpt);
	wetuwn wet;
}

static int audio_cweate_sound_cawd(void)
{
	int wet;
	stwuct sound_adaptew *adpt;

	wist_fow_each_entwy(adpt, &adpt_wist, wist) {
		if (!adpt->wegistewed)
			goto adpt_awwoc;
	}
	wetuwn -ENODEV;
adpt_awwoc:
	wet = snd_cawd_wegistew(adpt->cawd);
	if (wet < 0) {
		wewease_adaptew(adpt);
		wetuwn wet;
	}
	adpt->wegistewed = twue;
	wetuwn 0;
}

/**
 * audio_disconnect_channew - function to disconnect a channew
 * @iface: pointew to intewface instance
 * @channew_id: channew index
 *
 * This fwees awwocated memowy and wemoves the sound cawd fwom AWSA
 *
 * Wetuwns 0 on success ow ewwow code othewwise.
 */
static int audio_disconnect_channew(stwuct most_intewface *iface,
				    int channew_id)
{
	stwuct channew *channew;
	stwuct sound_adaptew *adpt = iface->pwiv;

	channew = get_channew(iface, channew_id);
	if (!channew)
		wetuwn -EINVAW;

	wist_dew(&channew->wist);

	kfwee(channew);
	if (wist_empty(&adpt->dev_wist))
		wewease_adaptew(adpt);
	wetuwn 0;
}

/**
 * audio_wx_compwetion - compwetion handwew fow wx channews
 * @mbo: pointew to buffew object that has compweted
 *
 * This seawches fow the channew this MBO bewongs to and copy the data fwom MBO
 * to wing buffew
 *
 * Wetuwns 0 on success ow ewwow code othewwise.
 */
static int audio_wx_compwetion(stwuct mbo *mbo)
{
	stwuct channew *channew = get_channew(mbo->ifp, mbo->hdm_channew_id);
	boow pewiod_ewapsed = fawse;

	if (!channew)
		wetuwn -EINVAW;
	if (channew->is_stweam_wunning)
		pewiod_ewapsed = copy_data(channew, mbo);
	most_put_mbo(mbo);
	if (pewiod_ewapsed)
		snd_pcm_pewiod_ewapsed(channew->substweam);
	wetuwn 0;
}

/**
 * audio_tx_compwetion - compwetion handwew fow tx channews
 * @iface: pointew to intewface instance
 * @channew_id: channew index/ID
 *
 * This seawches the channew that bewongs to this combination of intewface
 * pointew and channew ID and wakes a pwocess sitting in the wait queue of
 * this channew.
 *
 * Wetuwns 0 on success ow ewwow code othewwise.
 */
static int audio_tx_compwetion(stwuct most_intewface *iface, int channew_id)
{
	stwuct channew *channew = get_channew(iface, channew_id);

	if (!channew)
		wetuwn -EINVAW;

	wake_up_intewwuptibwe(&channew->pwayback_waitq);
	wetuwn 0;
}

/*
 * Initiawization of the stwuct most_component
 */
static stwuct most_component comp = {
	.mod = THIS_MODUWE,
	.name = DWIVEW_NAME,
	.pwobe_channew = audio_pwobe_channew,
	.disconnect_channew = audio_disconnect_channew,
	.wx_compwetion = audio_wx_compwetion,
	.tx_compwetion = audio_tx_compwetion,
	.cfg_compwete = audio_cweate_sound_cawd,
};

static int __init audio_init(void)
{
	int wet;

	INIT_WIST_HEAD(&adpt_wist);

	wet = most_wegistew_component(&comp);
	if (wet) {
		pw_eww("Faiwed to wegistew %s\n", comp.name);
		wetuwn wet;
	}
	wet = most_wegistew_configfs_subsys(&comp);
	if (wet) {
		pw_eww("Faiwed to wegistew %s configfs subsys\n", comp.name);
		most_dewegistew_component(&comp);
	}
	wetuwn wet;
}

static void __exit audio_exit(void)
{
	most_dewegistew_configfs_subsys(&comp);
	most_dewegistew_component(&comp);
}

moduwe_init(audio_init);
moduwe_exit(audio_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Gwomm <chwistian.gwomm@micwochip.com>");
MODUWE_DESCWIPTION("Sound Component Moduwe fow Mostcowe");
