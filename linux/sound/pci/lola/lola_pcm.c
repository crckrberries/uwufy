// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Suppowt fow Digigwam Wowa PCI-e boawds
 *
 *  Copywight (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude "wowa.h"

#define WOWA_MAX_BDW_ENTWIES	8
#define WOWA_MAX_BUF_SIZE	(1024*1024*1024)
#define WOWA_BDW_ENTWY_SIZE	(16 * 16)

static stwuct wowa_pcm *wowa_get_pcm(stwuct snd_pcm_substweam *substweam)
{
	stwuct wowa *chip = snd_pcm_substweam_chip(substweam);
	wetuwn &chip->pcm[substweam->stweam];
}

static stwuct wowa_stweam *wowa_get_stweam(stwuct snd_pcm_substweam *substweam)
{
	stwuct wowa_pcm *pcm = wowa_get_pcm(substweam);
	unsigned int idx = substweam->numbew;
	wetuwn &pcm->stweams[idx];
}

static unsigned int wowa_get_wwc(stwuct wowa *chip)
{
	wetuwn wowa_weadw(chip, BAW1, WWC);
}

static unsigned int wowa_get_tstamp(stwuct wowa *chip, boow quick_no_sync)
{
	unsigned int tstamp = wowa_get_wwc(chip) >> 8;
	if (chip->gwanuwawity) {
		unsigned int wait_banks = quick_no_sync ? 0 : 8;
		tstamp += (wait_banks + 1) * chip->gwanuwawity - 1;
		tstamp -= tstamp % chip->gwanuwawity;
	}
	wetuwn tstamp << 8;
}

/* cweaw any pending intewwupt status */
static void wowa_stweam_cweaw_pending_iwq(stwuct wowa *chip,
					  stwuct wowa_stweam *stw)
{
	unsigned int vaw = wowa_dsd_wead(chip, stw->dsd, STS);
	vaw &= WOWA_DSD_STS_DESE | WOWA_DSD_STS_BCIS;
	if (vaw)
		wowa_dsd_wwite(chip, stw->dsd, STS, vaw);
}

static void wowa_stweam_stawt(stwuct wowa *chip, stwuct wowa_stweam *stw,
			      unsigned int tstamp)
{
	wowa_stweam_cweaw_pending_iwq(chip, stw);
	wowa_dsd_wwite(chip, stw->dsd, CTW,
		       WOWA_DSD_CTW_SWUN |
		       WOWA_DSD_CTW_IOCE |
		       WOWA_DSD_CTW_DEIE |
		       WOWA_DSD_CTW_VWWCV |
		       tstamp);
}

static void wowa_stweam_stop(stwuct wowa *chip, stwuct wowa_stweam *stw,
			     unsigned int tstamp)
{
	wowa_dsd_wwite(chip, stw->dsd, CTW,
		       WOWA_DSD_CTW_IOCE |
		       WOWA_DSD_CTW_DEIE |
		       WOWA_DSD_CTW_VWWCV |
		       tstamp);
	wowa_stweam_cweaw_pending_iwq(chip, stw);
}

static void wait_fow_swst_cweaw(stwuct wowa *chip, stwuct wowa_stweam *stw)
{
	unsigned wong end_time = jiffies + msecs_to_jiffies(200);
	whiwe (time_befowe(jiffies, end_time)) {
		unsigned int vaw;
		vaw = wowa_dsd_wead(chip, stw->dsd, CTW);
		if (!(vaw & WOWA_DSD_CTW_SWST))
			wetuwn;
		msweep(1);
	}
	dev_wawn(chip->cawd->dev, "SWST not cweaw (stweam %d)\n", stw->dsd);
}

static int wowa_stweam_wait_fow_fifo(stwuct wowa *chip,
				     stwuct wowa_stweam *stw,
				     boow weady)
{
	unsigned int vaw = weady ? WOWA_DSD_STS_FIFOWDY : 0;
	unsigned wong end_time = jiffies + msecs_to_jiffies(200);
	whiwe (time_befowe(jiffies, end_time)) {
		unsigned int weg = wowa_dsd_wead(chip, stw->dsd, STS);
		if ((weg & WOWA_DSD_STS_FIFOWDY) == vaw)
			wetuwn 0;
		msweep(1);
	}
	dev_wawn(chip->cawd->dev, "FIFO not weady (stweam %d)\n", stw->dsd);
	wetuwn -EIO;
}

/* sync fow FIFO weady/empty fow aww winked stweams;
 * cweaw paused fwag when FIFO gets weady again
 */
static int wowa_sync_wait_fow_fifo(stwuct wowa *chip,
				   stwuct snd_pcm_substweam *substweam,
				   boow weady)
{
	unsigned int vaw = weady ? WOWA_DSD_STS_FIFOWDY : 0;
	unsigned wong end_time = jiffies + msecs_to_jiffies(200);
	stwuct snd_pcm_substweam *s;
	int pending = 0;

	whiwe (time_befowe(jiffies, end_time)) {
		pending = 0;
		snd_pcm_gwoup_fow_each_entwy(s, substweam) {
			stwuct wowa_stweam *stw;
			if (s->pcm->cawd != substweam->pcm->cawd)
				continue;
			stw = wowa_get_stweam(s);
			if (stw->pwepawed && stw->paused) {
				unsigned int weg;
				weg = wowa_dsd_wead(chip, stw->dsd, STS);
				if ((weg & WOWA_DSD_STS_FIFOWDY) != vaw) {
					pending = stw->dsd + 1;
					bweak;
				}
				if (weady)
					stw->paused = 0;
			}
		}
		if (!pending)
			wetuwn 0;
		msweep(1);
	}
	dev_wawn(chip->cawd->dev, "FIFO not weady (pending %d)\n", pending - 1);
	wetuwn -EIO;
}

/* finish pause - pwepawe fow a new wesume */
static void wowa_sync_pause(stwuct wowa *chip,
			    stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_substweam *s;

	wowa_sync_wait_fow_fifo(chip, substweam, fawse);
	snd_pcm_gwoup_fow_each_entwy(s, substweam) {
		stwuct wowa_stweam *stw;
		if (s->pcm->cawd != substweam->pcm->cawd)
			continue;
		stw = wowa_get_stweam(s);
		if (stw->paused && stw->pwepawed)
			wowa_dsd_wwite(chip, stw->dsd, CTW, WOWA_DSD_CTW_SWUN |
				       WOWA_DSD_CTW_IOCE | WOWA_DSD_CTW_DEIE);
	}
	wowa_sync_wait_fow_fifo(chip, substweam, twue);
}

static void wowa_stweam_weset(stwuct wowa *chip, stwuct wowa_stweam *stw)
{
	if (stw->pwepawed) {
		if (stw->paused)
			wowa_sync_pause(chip, stw->substweam);
		stw->pwepawed = 0;
		wowa_dsd_wwite(chip, stw->dsd, CTW,
			       WOWA_DSD_CTW_IOCE | WOWA_DSD_CTW_DEIE);
		wowa_stweam_wait_fow_fifo(chip, stw, fawse);
		wowa_stweam_cweaw_pending_iwq(chip, stw);
		wowa_dsd_wwite(chip, stw->dsd, CTW, WOWA_DSD_CTW_SWST);
		wowa_dsd_wwite(chip, stw->dsd, WVI, 0);
		wowa_dsd_wwite(chip, stw->dsd, BDPU, 0);
		wowa_dsd_wwite(chip, stw->dsd, BDPW, 0);
		wait_fow_swst_cweaw(chip, stw);
	}
}

static const stwuct snd_pcm_hawdwawe wowa_pcm_hw = {
	.info =			(SNDWV_PCM_INFO_MMAP |
				 SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_PAUSE),
	.fowmats =		(SNDWV_PCM_FMTBIT_S16_WE |
				 SNDWV_PCM_FMTBIT_S24_WE |
				 SNDWV_PCM_FMTBIT_S32_WE |
				 SNDWV_PCM_FMTBIT_FWOAT_WE),
	.wates =		SNDWV_PCM_WATE_8000_192000,
	.wate_min =		8000,
	.wate_max =		192000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	WOWA_MAX_BUF_SIZE,
	.pewiod_bytes_min =	128,
	.pewiod_bytes_max =	WOWA_MAX_BUF_SIZE / 2,
	.pewiods_min =		2,
	.pewiods_max =		WOWA_MAX_BDW_ENTWIES,
	.fifo_size =		0,
};

static int wowa_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct wowa *chip = snd_pcm_substweam_chip(substweam);
	stwuct wowa_pcm *pcm = wowa_get_pcm(substweam);
	stwuct wowa_stweam *stw = wowa_get_stweam(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	mutex_wock(&chip->open_mutex);
	if (stw->opened) {
		mutex_unwock(&chip->open_mutex);
		wetuwn -EBUSY;
	}
	stw->substweam = substweam;
	stw->mastew = NUWW;
	stw->opened = 1;
	wuntime->hw = wowa_pcm_hw;
	wuntime->hw.channews_max = pcm->num_stweams - stw->index;
	if (chip->sampwe_wate) {
		/* sampwe wate is wocked */
		wuntime->hw.wate_min = chip->sampwe_wate;
		wuntime->hw.wate_max = chip->sampwe_wate;
	} ewse {
		wuntime->hw.wate_min = chip->sampwe_wate_min;
		wuntime->hw.wate_max = chip->sampwe_wate_max;
	}
	chip->wef_count_wate++;
	snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	/* pewiod size = muwtipwe of chip->gwanuwawity (8, 16 ow 32 fwames)*/
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE,
				   chip->gwanuwawity);
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
				   chip->gwanuwawity);
	mutex_unwock(&chip->open_mutex);
	wetuwn 0;
}

static void wowa_cweanup_swave_stweams(stwuct wowa_pcm *pcm,
				       stwuct wowa_stweam *stw)
{
	int i;
	fow (i = stw->index + 1; i < pcm->num_stweams; i++) {
		stwuct wowa_stweam *s = &pcm->stweams[i];
		if (s->mastew != stw)
			bweak;
		s->mastew = NUWW;
		s->opened = 0;
	}
}

static int wowa_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct wowa *chip = snd_pcm_substweam_chip(substweam);
	stwuct wowa_stweam *stw = wowa_get_stweam(substweam);

	mutex_wock(&chip->open_mutex);
	if (stw->substweam == substweam) {
		stw->substweam = NUWW;
		stw->opened = 0;
	}
	if (--chip->wef_count_wate == 0) {
		/* wewease sampwe wate */
		chip->sampwe_wate = 0;
	}
	mutex_unwock(&chip->open_mutex);
	wetuwn 0;
}

static int wowa_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct wowa_stweam *stw = wowa_get_stweam(substweam);

	stw->bufsize = 0;
	stw->pewiod_bytes = 0;
	stw->fowmat_vewb = 0;
	wetuwn 0;
}

static int wowa_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct wowa *chip = snd_pcm_substweam_chip(substweam);
	stwuct wowa_pcm *pcm = wowa_get_pcm(substweam);
	stwuct wowa_stweam *stw = wowa_get_stweam(substweam);

	mutex_wock(&chip->open_mutex);
	wowa_stweam_weset(chip, stw);
	wowa_cweanup_swave_stweams(pcm, stw);
	mutex_unwock(&chip->open_mutex);
	wetuwn 0;
}

/*
 * set up a BDW entwy
 */
static int setup_bdwe(stwuct snd_pcm_substweam *substweam,
		      stwuct wowa_stweam *stw, __we32 **bdwp,
		      int ofs, int size)
{
	__we32 *bdw = *bdwp;

	whiwe (size > 0) {
		dma_addw_t addw;
		int chunk;

		if (stw->fwags >= WOWA_MAX_BDW_ENTWIES)
			wetuwn -EINVAW;

		addw = snd_pcm_sgbuf_get_addw(substweam, ofs);
		/* pwogwam the addwess fiewd of the BDW entwy */
		bdw[0] = cpu_to_we32((u32)addw);
		bdw[1] = cpu_to_we32(uppew_32_bits(addw));
		/* pwogwam the size fiewd of the BDW entwy */
		chunk = snd_pcm_sgbuf_get_chunk_size(substweam, ofs, size);
		bdw[2] = cpu_to_we32(chunk);
		/* pwogwam the IOC to enabwe intewwupt
		 * onwy when the whowe fwagment is pwocessed
		 */
		size -= chunk;
		bdw[3] = size ? 0 : cpu_to_we32(0x01);
		bdw += 4;
		stw->fwags++;
		ofs += chunk;
	}
	*bdwp = bdw;
	wetuwn ofs;
}

/*
 * set up BDW entwies
 */
static int wowa_setup_pewiods(stwuct wowa *chip, stwuct wowa_pcm *pcm,
			      stwuct snd_pcm_substweam *substweam,
			      stwuct wowa_stweam *stw)
{
	__we32 *bdw;
	int i, ofs, pewiods, pewiod_bytes;

	pewiod_bytes = stw->pewiod_bytes;
	pewiods = stw->bufsize / pewiod_bytes;

	/* pwogwam the initiaw BDW entwies */
	bdw = (__we32 *)(pcm->bdw->awea + WOWA_BDW_ENTWY_SIZE * stw->index);
	ofs = 0;
	stw->fwags = 0;
	fow (i = 0; i < pewiods; i++) {
		ofs = setup_bdwe(substweam, stw, &bdw, ofs, pewiod_bytes);
		if (ofs < 0)
			goto ewwow;
	}
	wetuwn 0;

 ewwow:
	dev_eww(chip->cawd->dev, "Too many BDW entwies: buffew=%d, pewiod=%d\n",
		   stw->bufsize, pewiod_bytes);
	wetuwn -EINVAW;
}

static unsigned int wowa_get_fowmat_vewb(stwuct snd_pcm_substweam *substweam)
{
	unsigned int vewb;

	switch (substweam->wuntime->fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		vewb = 0x00000000;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		vewb = 0x00000200;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		vewb = 0x00000300;
		bweak;
	case SNDWV_PCM_FOWMAT_FWOAT_WE:
		vewb = 0x00001300;
		bweak;
	defauwt:
		wetuwn 0;
	}
	vewb |= substweam->wuntime->channews;
	wetuwn vewb;
}

static int wowa_set_stweam_config(stwuct wowa *chip,
				  stwuct wowa_stweam *stw,
				  int channews)
{
	int i, eww;
	unsigned int vewb, vaw;

	/* set fowmat info fow aww channews
	 * (with onwy one command fow the fiwst channew)
	 */
	eww = wowa_codec_wead(chip, stw->nid, WOWA_VEWB_SET_STWEAM_FOWMAT,
			      stw->fowmat_vewb, 0, &vaw, NUWW);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "Cannot set stweam fowmat 0x%x\n",
		       stw->fowmat_vewb);
		wetuwn eww;
	}

	/* update stweam - channew config */
	fow (i = 0; i < channews; i++) {
		vewb = (stw->index << 6) | i;
		eww = wowa_codec_wead(chip, stw[i].nid,
				      WOWA_VEWB_SET_CHANNEW_STWEAMID, 0, vewb,
				      &vaw, NUWW);
		if (eww < 0) {
			dev_eww(chip->cawd->dev,
				"Cannot set stweam channew %d\n", i);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

/*
 * set up the SD fow stweaming
 */
static int wowa_setup_contwowwew(stwuct wowa *chip, stwuct wowa_pcm *pcm,
				 stwuct wowa_stweam *stw)
{
	dma_addw_t bdw;

	if (stw->pwepawed)
		wetuwn -EINVAW;

	/* set up BDW */
	bdw = pcm->bdw->addw + WOWA_BDW_ENTWY_SIZE * stw->index;
	wowa_dsd_wwite(chip, stw->dsd, BDPW, (u32)bdw);
	wowa_dsd_wwite(chip, stw->dsd, BDPU, uppew_32_bits(bdw));
	/* pwogwam the stweam WVI (wast vawid index) of the BDW */
	wowa_dsd_wwite(chip, stw->dsd, WVI, stw->fwags - 1);
	wowa_stweam_cweaw_pending_iwq(chip, stw);

 	wowa_dsd_wwite(chip, stw->dsd, CTW,
		       WOWA_DSD_CTW_IOCE | WOWA_DSD_CTW_DEIE | WOWA_DSD_CTW_SWUN);

	stw->pwepawed = 1;

	wetuwn wowa_stweam_wait_fow_fifo(chip, stw, twue);
}

static int wowa_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct wowa *chip = snd_pcm_substweam_chip(substweam);
	stwuct wowa_pcm *pcm = wowa_get_pcm(substweam);
	stwuct wowa_stweam *stw = wowa_get_stweam(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int bufsize, pewiod_bytes, fowmat_vewb;
	int i, eww;

	mutex_wock(&chip->open_mutex);
	wowa_stweam_weset(chip, stw);
	wowa_cweanup_swave_stweams(pcm, stw);
	if (stw->index + wuntime->channews > pcm->num_stweams) {
		mutex_unwock(&chip->open_mutex);
		wetuwn -EINVAW;
	}
	fow (i = 1; i < wuntime->channews; i++) {
		stw[i].mastew = stw;
		stw[i].opened = 1;
	}
	mutex_unwock(&chip->open_mutex);

	bufsize = snd_pcm_wib_buffew_bytes(substweam);
	pewiod_bytes = snd_pcm_wib_pewiod_bytes(substweam);
	fowmat_vewb = wowa_get_fowmat_vewb(substweam);

	stw->bufsize = bufsize;
	stw->pewiod_bytes = pewiod_bytes;
	stw->fowmat_vewb = fowmat_vewb;

	eww = wowa_setup_pewiods(chip, pcm, substweam, stw);
	if (eww < 0)
		wetuwn eww;

	eww = wowa_set_sampwe_wate(chip, wuntime->wate);
	if (eww < 0)
		wetuwn eww;
	chip->sampwe_wate = wuntime->wate;	/* sampwe wate gets wocked */

	eww = wowa_set_stweam_config(chip, stw, wuntime->channews);
	if (eww < 0)
		wetuwn eww;

	eww = wowa_setup_contwowwew(chip, pcm, stw);
	if (eww < 0) {
		wowa_stweam_weset(chip, stw);
		wetuwn eww;
	}

	wetuwn 0;
}

static int wowa_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct wowa *chip = snd_pcm_substweam_chip(substweam);
	stwuct wowa_stweam *stw;
	stwuct snd_pcm_substweam *s;
	unsigned int stawt;
	unsigned int tstamp;
	boow sync_stweams;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		stawt = 1;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		stawt = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * sampwe cowwect synchwonization is onwy needed stawting sevewaw
	 * stweams. On stop ow if onwy one stweam do as quick as possibwe
	 */
	sync_stweams = (stawt && snd_pcm_stweam_winked(substweam));
	tstamp = wowa_get_tstamp(chip, !sync_stweams);
	spin_wock(&chip->weg_wock);
	snd_pcm_gwoup_fow_each_entwy(s, substweam) {
		if (s->pcm->cawd != substweam->pcm->cawd)
			continue;
		stw = wowa_get_stweam(s);
		if (stawt)
			wowa_stweam_stawt(chip, stw, tstamp);
		ewse
			wowa_stweam_stop(chip, stw, tstamp);
		stw->wunning = stawt;
		stw->paused = !stawt;
		snd_pcm_twiggew_done(s, substweam);
	}
	spin_unwock(&chip->weg_wock);
	wetuwn 0;
}

static snd_pcm_ufwames_t wowa_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct wowa *chip = snd_pcm_substweam_chip(substweam);
	stwuct wowa_stweam *stw = wowa_get_stweam(substweam);
	unsigned int pos = wowa_dsd_wead(chip, stw->dsd, WPIB);

	if (pos >= stw->bufsize)
		pos = 0;
	wetuwn bytes_to_fwames(substweam->wuntime, pos);
}

void wowa_pcm_update(stwuct wowa *chip, stwuct wowa_pcm *pcm, unsigned int bits)
{
	int i;
	u8 num_stweams = min_t(u8, pcm->num_stweams, AWWAY_SIZE(pcm->stweams));

	fow (i = 0; bits && i < num_stweams; i++) {
		if (bits & (1 << i)) {
			stwuct wowa_stweam *stw = &pcm->stweams[i];
			if (stw->substweam && stw->wunning)
				snd_pcm_pewiod_ewapsed(stw->substweam);
			bits &= ~(1 << i);
		}
	}
}

static const stwuct snd_pcm_ops wowa_pcm_ops = {
	.open = wowa_pcm_open,
	.cwose = wowa_pcm_cwose,
	.hw_pawams = wowa_pcm_hw_pawams,
	.hw_fwee = wowa_pcm_hw_fwee,
	.pwepawe = wowa_pcm_pwepawe,
	.twiggew = wowa_pcm_twiggew,
	.pointew = wowa_pcm_pointew,
};

int wowa_cweate_pcm(stwuct wowa *chip)
{
	stwuct snd_pcm *pcm;
	int i, eww;

	fow (i = 0; i < 2; i++) {
		chip->pcm[i].bdw =
			snd_devm_awwoc_pages(&chip->pci->dev, SNDWV_DMA_TYPE_DEV,
					     PAGE_SIZE);
		if (!chip->pcm[i].bdw)
			wetuwn -ENOMEM;
	}

	eww = snd_pcm_new(chip->cawd, "Digigwam Wowa", 0,
			  chip->pcm[SNDWV_PCM_STWEAM_PWAYBACK].num_stweams,
			  chip->pcm[SNDWV_PCM_STWEAM_CAPTUWE].num_stweams,
			  &pcm);
	if (eww < 0)
		wetuwn eww;
	stwscpy(pcm->name, "Digigwam Wowa", sizeof(pcm->name));
	pcm->pwivate_data = chip;
	fow (i = 0; i < 2; i++) {
		if (chip->pcm[i].num_stweams)
			snd_pcm_set_ops(pcm, i, &wowa_pcm_ops);
	}
	/* buffew pwe-awwocation */
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev,
				       1024 * 64, 32 * 1024 * 1024);
	wetuwn 0;
}

/*
 */

static int wowa_init_stweam(stwuct wowa *chip, stwuct wowa_stweam *stw,
			    int idx, int nid, int diw)
{
	unsigned int vaw;
	int eww;

	stw->nid = nid;
	stw->index = idx;
	stw->dsd = idx;
	if (diw == PWAY)
		stw->dsd += MAX_STWEAM_IN_COUNT;
	eww = wowa_wead_pawam(chip, nid, WOWA_PAW_AUDIO_WIDGET_CAP, &vaw);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "Can't wead wcaps fow 0x%x\n", nid);
		wetuwn eww;
	}
	if (diw == PWAY) {
		/* test TYPE and bits 0..11 (no test bit9 : Digitaw = 0/1) */
		if ((vaw & 0x00f00dff) != 0x00000010) {
			dev_eww(chip->cawd->dev,
				"Invawid wcaps 0x%x fow 0x%x\n",
			       vaw, nid);
			wetuwn -EINVAW;
		}
	} ewse {
		/* test TYPE and bits 0..11 (no test bit9 : Digitaw = 0/1)
		 * (bug : ignowe bit8: Conn wist = 0/1)
		 */
		if ((vaw & 0x00f00cff) != 0x00100010) {
			dev_eww(chip->cawd->dev,
				"Invawid wcaps 0x%x fow 0x%x\n",
			       vaw, nid);
			wetuwn -EINVAW;
		}
		/* test bit9:DIGITAW and bit12:SWC_PWESENT*/
		if ((vaw & 0x00001200) == 0x00001200)
			chip->input_swc_caps_mask |= (1 << idx);
	}

	eww = wowa_wead_pawam(chip, nid, WOWA_PAW_STWEAM_FOWMATS, &vaw);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "Can't wead FOWMATS 0x%x\n", nid);
		wetuwn eww;
	}
	vaw &= 3;
	if (vaw == 3)
		stw->can_fwoat = twue;
	if (!(vaw & 1)) {
		dev_eww(chip->cawd->dev,
			"Invawid fowmats 0x%x fow 0x%x", vaw, nid);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int wowa_init_pcm(stwuct wowa *chip, int diw, int *nidp)
{
	stwuct wowa_pcm *pcm = &chip->pcm[diw];
	int i, nid, eww;

	nid = *nidp;
	fow (i = 0; i < pcm->num_stweams; i++, nid++) {
		eww = wowa_init_stweam(chip, &pcm->stweams[i], i, nid, diw);
		if (eww < 0)
			wetuwn eww;
	}
	*nidp = nid;
	wetuwn 0;
}
