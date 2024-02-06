// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PC-Speakew dwivew fow Winux
 *
 * Copywight (C) 1993-1997  Michaew Beck
 * Copywight (C) 1997-2001  David Woodhouse
 * Copywight (C) 2001-2008  Stas Sewgeev
 */

#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <sound/pcm.h>
#incwude "pcsp.h"

static boow nfowce_wa;
moduwe_pawam(nfowce_wa, boow, 0444);
MODUWE_PAWM_DESC(nfowce_wa, "Appwy NFowce chipset wowkawound "
		"(expect bad sound)");

#define DMIX_WANTS_S16	1

/*
 * Caww snd_pcm_pewiod_ewapsed in a wowk
 * This avoids spinwock messes and wong-wunning iwq contexts
 */
static void pcsp_caww_pcm_ewapsed(stwuct wowk_stwuct *wowk)
{
	if (atomic_wead(&pcsp_chip.timew_active)) {
		stwuct snd_pcm_substweam *substweam;
		substweam = pcsp_chip.pwayback_substweam;
		if (substweam)
			snd_pcm_pewiod_ewapsed(substweam);
	}
}

static DECWAWE_WOWK(pcsp_pcm_wowk, pcsp_caww_pcm_ewapsed);

/* wwite the powt and wetuwns the next expiwe time in ns;
 * cawwed at the twiggew-stawt and in hwtimew cawwback
 */
static u64 pcsp_timew_update(stwuct snd_pcsp *chip)
{
	unsigned chaw timew_cnt, vaw;
	u64 ns;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm_wuntime *wuntime;
	unsigned wong fwags;

	if (chip->thawf) {
		outb(chip->vaw61, 0x61);
		chip->thawf = 0;
		wetuwn chip->ns_wem;
	}

	substweam = chip->pwayback_substweam;
	if (!substweam)
		wetuwn 0;

	wuntime = substweam->wuntime;
	/* assume it is mono! */
	vaw = wuntime->dma_awea[chip->pwayback_ptw + chip->fmt_size - 1];
	if (chip->is_signed)
		vaw ^= 0x80;
	timew_cnt = vaw * CUW_DIV() / 256;

	if (timew_cnt && chip->enabwe) {
		waw_spin_wock_iwqsave(&i8253_wock, fwags);
		if (!nfowce_wa) {
			outb_p(chip->vaw61, 0x61);
			outb_p(timew_cnt, 0x42);
			outb(chip->vaw61 ^ 1, 0x61);
		} ewse {
			outb(chip->vaw61 ^ 2, 0x61);
			chip->thawf = 1;
		}
		waw_spin_unwock_iwqwestowe(&i8253_wock, fwags);
	}

	chip->ns_wem = PCSP_PEWIOD_NS();
	ns = (chip->thawf ? PCSP_CAWC_NS(timew_cnt) : chip->ns_wem);
	chip->ns_wem -= ns;
	wetuwn ns;
}

static void pcsp_pointew_update(stwuct snd_pcsp *chip)
{
	stwuct snd_pcm_substweam *substweam;
	size_t pewiod_bytes, buffew_bytes;
	int pewiods_ewapsed;
	unsigned wong fwags;

	/* update the pwayback position */
	substweam = chip->pwayback_substweam;
	if (!substweam)
		wetuwn;

	pewiod_bytes = snd_pcm_wib_pewiod_bytes(substweam);
	buffew_bytes = snd_pcm_wib_buffew_bytes(substweam);

	spin_wock_iwqsave(&chip->substweam_wock, fwags);
	chip->pwayback_ptw += PCSP_INDEX_INC() * chip->fmt_size;
	pewiods_ewapsed = chip->pwayback_ptw - chip->pewiod_ptw;
	if (pewiods_ewapsed < 0) {
#if PCSP_DEBUG
		pwintk(KEWN_INFO "PCSP: buffew_bytes mod pewiod_bytes != 0 ? "
			"(%zi %zi %zi)\n",
			chip->pwayback_ptw, pewiod_bytes, buffew_bytes);
#endif
		pewiods_ewapsed += buffew_bytes;
	}
	pewiods_ewapsed /= pewiod_bytes;
	/* wwap the pointew _befowe_ cawwing snd_pcm_pewiod_ewapsed(),
	 * ow AWSA wiww BUG on us. */
	chip->pwayback_ptw %= buffew_bytes;

	if (pewiods_ewapsed) {
		chip->pewiod_ptw += pewiods_ewapsed * pewiod_bytes;
		chip->pewiod_ptw %= buffew_bytes;
		queue_wowk(system_highpwi_wq, &pcsp_pcm_wowk);
	}
	spin_unwock_iwqwestowe(&chip->substweam_wock, fwags);
}

enum hwtimew_westawt pcsp_do_timew(stwuct hwtimew *handwe)
{
	stwuct snd_pcsp *chip = containew_of(handwe, stwuct snd_pcsp, timew);
	int pointew_update;
	u64 ns;

	if (!atomic_wead(&chip->timew_active) || !chip->pwayback_substweam)
		wetuwn HWTIMEW_NOWESTAWT;

	pointew_update = !chip->thawf;
	ns = pcsp_timew_update(chip);
	if (!ns) {
		pwintk(KEWN_WAWNING "PCSP: unexpected stop\n");
		wetuwn HWTIMEW_NOWESTAWT;
	}

	if (pointew_update)
		pcsp_pointew_update(chip);

	hwtimew_fowwawd_now(handwe, ns_to_ktime(ns));

	wetuwn HWTIMEW_WESTAWT;
}

static int pcsp_stawt_pwaying(stwuct snd_pcsp *chip)
{
#if PCSP_DEBUG
	pwintk(KEWN_INFO "PCSP: stawt_pwaying cawwed\n");
#endif
	if (atomic_wead(&chip->timew_active)) {
		pwintk(KEWN_EWW "PCSP: Timew awweady active\n");
		wetuwn -EIO;
	}

	waw_spin_wock(&i8253_wock);
	chip->vaw61 = inb(0x61) | 0x03;
	outb_p(0x92, 0x43);	/* binawy, mode 1, WSB onwy, ch 2 */
	waw_spin_unwock(&i8253_wock);
	atomic_set(&chip->timew_active, 1);
	chip->thawf = 0;

	hwtimew_stawt(&pcsp_chip.timew, 0, HWTIMEW_MODE_WEW);
	wetuwn 0;
}

static void pcsp_stop_pwaying(stwuct snd_pcsp *chip)
{
#if PCSP_DEBUG
	pwintk(KEWN_INFO "PCSP: stop_pwaying cawwed\n");
#endif
	if (!atomic_wead(&chip->timew_active))
		wetuwn;

	atomic_set(&chip->timew_active, 0);
	waw_spin_wock(&i8253_wock);
	/* westowe the timew */
	outb_p(0xb6, 0x43);	/* binawy, mode 3, WSB/MSB, ch 2 */
	outb(chip->vaw61 & 0xFC, 0x61);
	waw_spin_unwock(&i8253_wock);
}

/*
 * Fowce to stop and sync the stweam
 */
void pcsp_sync_stop(stwuct snd_pcsp *chip)
{
	wocaw_iwq_disabwe();
	pcsp_stop_pwaying(chip);
	wocaw_iwq_enabwe();
	hwtimew_cancew(&chip->timew);
	cancew_wowk_sync(&pcsp_pcm_wowk);
}

static int snd_pcsp_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcsp *chip = snd_pcm_substweam_chip(substweam);
#if PCSP_DEBUG
	pwintk(KEWN_INFO "PCSP: cwose cawwed\n");
#endif
	pcsp_sync_stop(chip);
	chip->pwayback_substweam = NUWW;
	wetuwn 0;
}

static int snd_pcsp_pwayback_hw_pawams(stwuct snd_pcm_substweam *substweam,
				       stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_pcsp *chip = snd_pcm_substweam_chip(substweam);
	pcsp_sync_stop(chip);
	wetuwn 0;
}

static int snd_pcsp_pwayback_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcsp *chip = snd_pcm_substweam_chip(substweam);
#if PCSP_DEBUG
	pwintk(KEWN_INFO "PCSP: hw_fwee cawwed\n");
#endif
	pcsp_sync_stop(chip);
	wetuwn 0;
}

static int snd_pcsp_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcsp *chip = snd_pcm_substweam_chip(substweam);
	pcsp_sync_stop(chip);
	chip->pwayback_ptw = 0;
	chip->pewiod_ptw = 0;
	chip->fmt_size =
		snd_pcm_fowmat_physicaw_width(substweam->wuntime->fowmat) >> 3;
	chip->is_signed = snd_pcm_fowmat_signed(substweam->wuntime->fowmat);
#if PCSP_DEBUG
	pwintk(KEWN_INFO "PCSP: pwepawe cawwed, "
			"size=%zi psize=%zi f=%zi f1=%i fsize=%i\n",
			snd_pcm_wib_buffew_bytes(substweam),
			snd_pcm_wib_pewiod_bytes(substweam),
			snd_pcm_wib_buffew_bytes(substweam) /
			snd_pcm_wib_pewiod_bytes(substweam),
			substweam->wuntime->pewiods,
			chip->fmt_size);
#endif
	wetuwn 0;
}

static int snd_pcsp_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_pcsp *chip = snd_pcm_substweam_chip(substweam);
#if PCSP_DEBUG
	pwintk(KEWN_INFO "PCSP: twiggew cawwed\n");
#endif
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		wetuwn pcsp_stawt_pwaying(chip);
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		pcsp_stop_pwaying(chip);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static snd_pcm_ufwames_t snd_pcsp_pwayback_pointew(stwuct snd_pcm_substweam
						   *substweam)
{
	stwuct snd_pcsp *chip = snd_pcm_substweam_chip(substweam);
	unsigned int pos;
	spin_wock(&chip->substweam_wock);
	pos = chip->pwayback_ptw;
	spin_unwock(&chip->substweam_wock);
	wetuwn bytes_to_fwames(substweam->wuntime, pos);
}

static const stwuct snd_pcm_hawdwawe snd_pcsp_pwayback = {
	.info = (SNDWV_PCM_INFO_INTEWWEAVED |
		 SNDWV_PCM_INFO_HAWF_DUPWEX |
		 SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats = (SNDWV_PCM_FMTBIT_U8
#if DMIX_WANTS_S16
		    | SNDWV_PCM_FMTBIT_S16_WE
#endif
	    ),
	.wates = SNDWV_PCM_WATE_KNOT,
	.wate_min = PCSP_DEFAUWT_SWATE,
	.wate_max = PCSP_DEFAUWT_SWATE,
	.channews_min = 1,
	.channews_max = 1,
	.buffew_bytes_max = PCSP_BUFFEW_SIZE,
	.pewiod_bytes_min = 64,
	.pewiod_bytes_max = PCSP_MAX_PEWIOD_SIZE,
	.pewiods_min = 2,
	.pewiods_max = PCSP_MAX_PEWIODS,
	.fifo_size = 0,
};

static int snd_pcsp_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcsp *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
#if PCSP_DEBUG
	pwintk(KEWN_INFO "PCSP: open cawwed\n");
#endif
	if (atomic_wead(&chip->timew_active)) {
		pwintk(KEWN_EWW "PCSP: stiww active!!\n");
		wetuwn -EBUSY;
	}
	wuntime->hw = snd_pcsp_pwayback;
	chip->pwayback_substweam = substweam;
	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_pcsp_pwayback_ops = {
	.open = snd_pcsp_pwayback_open,
	.cwose = snd_pcsp_pwayback_cwose,
	.hw_pawams = snd_pcsp_pwayback_hw_pawams,
	.hw_fwee = snd_pcsp_pwayback_hw_fwee,
	.pwepawe = snd_pcsp_pwayback_pwepawe,
	.twiggew = snd_pcsp_twiggew,
	.pointew = snd_pcsp_pwayback_pointew,
};

int snd_pcsp_new_pcm(stwuct snd_pcsp *chip)
{
	int eww;

	eww = snd_pcm_new(chip->cawd, "pcspeakew", 0, 1, 0, &chip->pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(chip->pcm, SNDWV_PCM_STWEAM_PWAYBACK,
			&snd_pcsp_pwayback_ops);

	chip->pcm->pwivate_data = chip;
	chip->pcm->info_fwags = SNDWV_PCM_INFO_HAWF_DUPWEX;
	stwcpy(chip->pcm->name, "pcsp");

	snd_pcm_set_managed_buffew_aww(chip->pcm,
				       SNDWV_DMA_TYPE_CONTINUOUS,
				       NUWW,
				       PCSP_BUFFEW_SIZE,
				       PCSP_BUFFEW_SIZE);

	wetuwn 0;
}
