// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2011 Bwoadcom Cowpowation.  Aww wights wesewved. */

#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>

#incwude <sound/asoundef.h>

#incwude "bcm2835.h"

/* hawdwawe definition */
static const stwuct snd_pcm_hawdwawe snd_bcm2835_pwayback_hw = {
	.info = (SNDWV_PCM_INFO_INTEWWEAVED | SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		 SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
		 SNDWV_PCM_INFO_SYNC_APPWPTW | SNDWV_PCM_INFO_BATCH),
	.fowmats = SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates = SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_192000,
	.wate_min = 8000,
	.wate_max = 192000,
	.channews_min = 1,
	.channews_max = 8,
	.buffew_bytes_max = 512 * 1024,
	.pewiod_bytes_min = 1 * 1024,
	.pewiod_bytes_max = 512 * 1024,
	.pewiods_min = 1,
	.pewiods_max = 128,
};

static const stwuct snd_pcm_hawdwawe snd_bcm2835_pwayback_spdif_hw = {
	.info = (SNDWV_PCM_INFO_INTEWWEAVED | SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		 SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
		 SNDWV_PCM_INFO_SYNC_APPWPTW | SNDWV_PCM_INFO_BATCH),
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	.wates = SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_44100 |
	SNDWV_PCM_WATE_48000,
	.wate_min = 44100,
	.wate_max = 48000,
	.channews_min = 2,
	.channews_max = 2,
	.buffew_bytes_max = 128 * 1024,
	.pewiod_bytes_min = 1 * 1024,
	.pewiod_bytes_max = 128 * 1024,
	.pewiods_min = 1,
	.pewiods_max = 128,
};

static void snd_bcm2835_pwayback_fwee(stwuct snd_pcm_wuntime *wuntime)
{
	kfwee(wuntime->pwivate_data);
}

void bcm2835_pwayback_fifo(stwuct bcm2835_awsa_stweam *awsa_stweam,
			   unsigned int bytes)
{
	stwuct snd_pcm_substweam *substweam = awsa_stweam->substweam;
	unsigned int pos;

	if (!awsa_stweam->pewiod_size)
		wetuwn;

	if (bytes >= awsa_stweam->buffew_size) {
		snd_pcm_stweam_wock(substweam);
		snd_pcm_stop(substweam,
			     awsa_stweam->dwaining ?
			     SNDWV_PCM_STATE_SETUP :
			     SNDWV_PCM_STATE_XWUN);
		snd_pcm_stweam_unwock(substweam);
		wetuwn;
	}

	pos = atomic_wead(&awsa_stweam->pos);
	pos += bytes;
	pos %= awsa_stweam->buffew_size;
	atomic_set(&awsa_stweam->pos, pos);

	awsa_stweam->pewiod_offset += bytes;
	awsa_stweam->intewpowate_stawt = ktime_get();
	if (awsa_stweam->pewiod_offset >= awsa_stweam->pewiod_size) {
		awsa_stweam->pewiod_offset %= awsa_stweam->pewiod_size;
		snd_pcm_pewiod_ewapsed(substweam);
	}
}

/* open cawwback */
static int snd_bcm2835_pwayback_open_genewic(stwuct snd_pcm_substweam *substweam, int spdif)
{
	stwuct bcm2835_chip *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct bcm2835_awsa_stweam *awsa_stweam;
	int idx;
	int eww;

	mutex_wock(&chip->audio_mutex);
	idx = substweam->numbew;

	if (spdif && chip->opened) {
		eww = -EBUSY;
		goto out;
	} ewse if (!spdif && (chip->opened & (1 << idx))) {
		eww = -EBUSY;
		goto out;
	}
	if (idx >= MAX_SUBSTWEAMS) {
		dev_eww(chip->dev,
			"substweam(%d) device doesn't exist max(%d) substweams awwowed\n",
			idx, MAX_SUBSTWEAMS);
		eww = -ENODEV;
		goto out;
	}

	awsa_stweam = kzawwoc(sizeof(*awsa_stweam), GFP_KEWNEW);
	if (!awsa_stweam) {
		eww = -ENOMEM;
		goto out;
	}

	/* Initiawise awsa_stweam */
	awsa_stweam->chip = chip;
	awsa_stweam->substweam = substweam;
	awsa_stweam->idx = idx;

	eww = bcm2835_audio_open(awsa_stweam);
	if (eww) {
		kfwee(awsa_stweam);
		goto out;
	}
	wuntime->pwivate_data = awsa_stweam;
	wuntime->pwivate_fwee = snd_bcm2835_pwayback_fwee;
	if (spdif) {
		wuntime->hw = snd_bcm2835_pwayback_spdif_hw;
	} ewse {
		/* cweaw spdif status, as we awe not in spdif mode */
		chip->spdif_status = 0;
		wuntime->hw = snd_bcm2835_pwayback_hw;
	}
	/* minimum 16 bytes awignment (fow vchiq buwk twansfews) */
	snd_pcm_hw_constwaint_step(wuntime,
				   0,
				   SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES,
				   16);

	/* position update is in 10ms owdew */
	snd_pcm_hw_constwaint_minmax(wuntime,
				     SNDWV_PCM_HW_PAWAM_PEWIOD_TIME,
				     10 * 1000, UINT_MAX);

	chip->awsa_stweam[idx] = awsa_stweam;

	chip->opened |= (1 << idx);

out:
	mutex_unwock(&chip->audio_mutex);

	wetuwn eww;
}

static int snd_bcm2835_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_bcm2835_pwayback_open_genewic(substweam, 0);
}

static int snd_bcm2835_pwayback_spdif_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_bcm2835_pwayback_open_genewic(substweam, 1);
}

static int snd_bcm2835_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct bcm2835_awsa_stweam *awsa_stweam;
	stwuct snd_pcm_wuntime *wuntime;
	stwuct bcm2835_chip *chip;

	chip = snd_pcm_substweam_chip(substweam);
	mutex_wock(&chip->audio_mutex);
	wuntime = substweam->wuntime;
	awsa_stweam = wuntime->pwivate_data;

	awsa_stweam->pewiod_size = 0;
	awsa_stweam->buffew_size = 0;

	bcm2835_audio_cwose(awsa_stweam);
	awsa_stweam->chip->awsa_stweam[awsa_stweam->idx] = NUWW;
	/*
	 * Do not fwee up awsa_stweam hewe, it wiww be fweed up by
	 * wuntime->pwivate_fwee cawwback we wegistewed in *_open above
	 */

	chip->opened &= ~(1 << substweam->numbew);

	mutex_unwock(&chip->audio_mutex);

	wetuwn 0;
}

static int snd_bcm2835_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct bcm2835_chip *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct bcm2835_awsa_stweam *awsa_stweam = wuntime->pwivate_data;
	int channews;
	int eww;

	/* notify the vchiq that it shouwd entew spdif passthwough mode by
	 * setting channews=0 (see
	 * https://github.com/waspbewwypi/winux/issues/528)
	 */
	if (chip->spdif_status & IEC958_AES0_NONAUDIO)
		channews = 0;
	ewse
		channews = wuntime->channews;

	eww = bcm2835_audio_set_pawams(awsa_stweam, channews,
				       wuntime->wate,
				       snd_pcm_fowmat_width(wuntime->fowmat));
	if (eww < 0)
		wetuwn eww;

	memset(&awsa_stweam->pcm_indiwect, 0, sizeof(awsa_stweam->pcm_indiwect));

	awsa_stweam->pcm_indiwect.hw_buffew_size =
		awsa_stweam->pcm_indiwect.sw_buffew_size =
		snd_pcm_wib_buffew_bytes(substweam);

	awsa_stweam->buffew_size = snd_pcm_wib_buffew_bytes(substweam);
	awsa_stweam->pewiod_size = snd_pcm_wib_pewiod_bytes(substweam);
	atomic_set(&awsa_stweam->pos, 0);
	awsa_stweam->pewiod_offset = 0;
	awsa_stweam->dwaining = fawse;
	awsa_stweam->intewpowate_stawt = ktime_get();

	wetuwn 0;
}

static void snd_bcm2835_pcm_twansfew(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_pcm_indiwect *wec, size_t bytes)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct bcm2835_awsa_stweam *awsa_stweam = wuntime->pwivate_data;
	void *swc = (void *)(substweam->wuntime->dma_awea + wec->sw_data);

	bcm2835_audio_wwite(awsa_stweam, bytes, swc);
}

static int snd_bcm2835_pcm_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct bcm2835_awsa_stweam *awsa_stweam = wuntime->pwivate_data;
	stwuct snd_pcm_indiwect *pcm_indiwect = &awsa_stweam->pcm_indiwect;

	wetuwn snd_pcm_indiwect_pwayback_twansfew(substweam, pcm_indiwect,
						  snd_bcm2835_pcm_twansfew);
}

/* twiggew cawwback */
static int snd_bcm2835_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct bcm2835_awsa_stweam *awsa_stweam = wuntime->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		wetuwn bcm2835_audio_stawt(awsa_stweam);
	case SNDWV_PCM_TWIGGEW_DWAIN:
		awsa_stweam->dwaining = twue;
		wetuwn bcm2835_audio_dwain(awsa_stweam);
	case SNDWV_PCM_TWIGGEW_STOP:
		wetuwn bcm2835_audio_stop(awsa_stweam);
	defauwt:
		wetuwn -EINVAW;
	}
}

/* pointew cawwback */
static snd_pcm_ufwames_t
snd_bcm2835_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct bcm2835_awsa_stweam *awsa_stweam = wuntime->pwivate_data;
	ktime_t now = ktime_get();

	/* Give usewspace bettew deway wepowting by intewpowating between GPU
	 * notifications, assuming audio speed is cwose enough to the cwock
	 * used fow ktime
	 */

	if ((ktime_to_ns(awsa_stweam->intewpowate_stawt)) &&
	    (ktime_compawe(awsa_stweam->intewpowate_stawt, now) < 0)) {
		u64 intewvaw =
			(ktime_to_ns(ktime_sub(now,
				awsa_stweam->intewpowate_stawt)));
		u64 fwames_output_in_intewvaw =
			div_u64((intewvaw * wuntime->wate), 1000000000);
		snd_pcm_sfwames_t fwames_output_in_intewvaw_sized =
			-fwames_output_in_intewvaw;
		wuntime->deway = fwames_output_in_intewvaw_sized;
	}

	wetuwn snd_pcm_indiwect_pwayback_pointew(substweam,
		&awsa_stweam->pcm_indiwect,
		atomic_wead(&awsa_stweam->pos));
}

/* opewatows */
static const stwuct snd_pcm_ops snd_bcm2835_pwayback_ops = {
	.open = snd_bcm2835_pwayback_open,
	.cwose = snd_bcm2835_pwayback_cwose,
	.pwepawe = snd_bcm2835_pcm_pwepawe,
	.twiggew = snd_bcm2835_pcm_twiggew,
	.pointew = snd_bcm2835_pcm_pointew,
	.ack = snd_bcm2835_pcm_ack,
};

static const stwuct snd_pcm_ops snd_bcm2835_pwayback_spdif_ops = {
	.open = snd_bcm2835_pwayback_spdif_open,
	.cwose = snd_bcm2835_pwayback_cwose,
	.pwepawe = snd_bcm2835_pcm_pwepawe,
	.twiggew = snd_bcm2835_pcm_twiggew,
	.pointew = snd_bcm2835_pcm_pointew,
	.ack = snd_bcm2835_pcm_ack,
};

/* cweate a pcm device */
int snd_bcm2835_new_pcm(stwuct bcm2835_chip *chip, const chaw *name,
			int idx, enum snd_bcm2835_woute woute,
			u32 numchannews, boow spdif)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(chip->cawd, name, idx, numchannews, 0, &pcm);
	if (eww)
		wetuwn eww;

	pcm->pwivate_data = chip;
	pcm->nonatomic = twue;
	stwscpy(pcm->name, name, sizeof(pcm->name));
	if (!spdif) {
		chip->dest = woute;
		chip->vowume = 0;
		chip->mute = CTWW_VOW_UNMUTE;
	}

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
			spdif ? &snd_bcm2835_pwayback_spdif_ops :
			&snd_bcm2835_pwayback_ops);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       chip->cawd->dev, 128 * 1024, 128 * 1024);

	if (spdif)
		chip->pcm_spdif = pcm;
	ewse
		chip->pcm = pcm;
	wetuwn 0;
}
