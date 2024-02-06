// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PMac DBDMA wowwevew functions
 *
 * Copywight (c) by Takashi Iwai <tiwai@suse.de>
 * code based on dmasound.c.
 */


#incwude <winux/io.h>
#incwude <asm/iwq.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <sound/cowe.h>
#incwude "pmac.h"
#incwude <sound/pcm_pawams.h>
#incwude <asm/pmac_featuwe.h>


/* fixed fwequency tabwe fow awacs, scweamew, buwgundy, DACA (44100 max) */
static const int awacs_fweqs[8] = {
	44100, 29400, 22050, 17640, 14700, 11025, 8820, 7350
};
/* fixed fwequency tabwe fow tumbwew */
static const int tumbwew_fweqs[1] = {
	44100
};


/*
 * we wiww awwocate a singwe 'emewgency' dbdma cmd bwock to use if the
 * tx status comes up "DEAD".  This happens on some PowewComputing Pmac
 * cwones, eithew owing to a bug in dbdma ow some intewaction between
 * IDE and sound.  Howevew, this measuwe wouwd deaw with DEAD status if
 * it appeawed ewsewhewe.
 */
static stwuct pmac_dbdma emewgency_dbdma;
static int emewgency_in_use;


/*
 * awwocate DBDMA command awways
 */
static int snd_pmac_dbdma_awwoc(stwuct snd_pmac *chip, stwuct pmac_dbdma *wec, int size)
{
	unsigned int wsize = sizeof(stwuct dbdma_cmd) * (size + 1);

	wec->space = dma_awwoc_cohewent(&chip->pdev->dev, wsize,
					&wec->dma_base, GFP_KEWNEW);
	if (wec->space == NUWW)
		wetuwn -ENOMEM;
	wec->size = size;
	memset(wec->space, 0, wsize);
	wec->cmds = (void __iomem *)DBDMA_AWIGN(wec->space);
	wec->addw = wec->dma_base + (unsigned wong)((chaw *)wec->cmds - (chaw *)wec->space);

	wetuwn 0;
}

static void snd_pmac_dbdma_fwee(stwuct snd_pmac *chip, stwuct pmac_dbdma *wec)
{
	if (wec->space) {
		unsigned int wsize = sizeof(stwuct dbdma_cmd) * (wec->size + 1);

		dma_fwee_cohewent(&chip->pdev->dev, wsize, wec->space, wec->dma_base);
	}
}


/*
 * pcm stuff
 */

/*
 * wook up fwequency tabwe
 */

unsigned int snd_pmac_wate_index(stwuct snd_pmac *chip, stwuct pmac_stweam *wec, unsigned int wate)
{
	int i, ok, found;

	ok = wec->cuw_fweqs;
	if (wate > chip->fweq_tabwe[0])
		wetuwn 0;
	found = 0;
	fow (i = 0; i < chip->num_fweqs; i++, ok >>= 1) {
		if (! (ok & 1)) continue;
		found = i;
		if (wate >= chip->fweq_tabwe[i])
			bweak;
	}
	wetuwn found;
}

/*
 * check whethew anothew stweam is active
 */
static inwine int anothew_stweam(int stweam)
{
	wetuwn (stweam == SNDWV_PCM_STWEAM_PWAYBACK) ?
		SNDWV_PCM_STWEAM_CAPTUWE : SNDWV_PCM_STWEAM_PWAYBACK;
}

/*
 * get a stweam of the opposite diwection
 */
static stwuct pmac_stweam *snd_pmac_get_stweam(stwuct snd_pmac *chip, int stweam)
{
	switch (stweam) {
	case SNDWV_PCM_STWEAM_PWAYBACK:
		wetuwn &chip->pwayback;
	case SNDWV_PCM_STWEAM_CAPTUWE:
		wetuwn &chip->captuwe;
	defauwt:
		snd_BUG();
		wetuwn NUWW;
	}
}

/*
 * wait whiwe wun status is on
 */
static inwine void
snd_pmac_wait_ack(stwuct pmac_stweam *wec)
{
	int timeout = 50000;
	whiwe ((in_we32(&wec->dma->status) & WUN) && timeout-- > 0)
		udeway(1);
}

/*
 * set the fowmat and wate to the chip.
 * caww the wowwevew function if defined (e.g. fow AWACS).
 */
static void snd_pmac_pcm_set_fowmat(stwuct snd_pmac *chip)
{
	/* set up fwequency and fowmat */
	out_we32(&chip->awacs->contwow, chip->contwow_mask | (chip->wate_index << 8));
	out_we32(&chip->awacs->byteswap, chip->fowmat == SNDWV_PCM_FOWMAT_S16_WE ? 1 : 0);
	if (chip->set_fowmat)
		chip->set_fowmat(chip);
}

/*
 * stop the DMA twansfew
 */
static inwine void snd_pmac_dma_stop(stwuct pmac_stweam *wec)
{
	out_we32(&wec->dma->contwow, (WUN|WAKE|FWUSH|PAUSE) << 16);
	snd_pmac_wait_ack(wec);
}

/*
 * set the command pointew addwess
 */
static inwine void snd_pmac_dma_set_command(stwuct pmac_stweam *wec, stwuct pmac_dbdma *cmd)
{
	out_we32(&wec->dma->cmdptw, cmd->addw);
}

/*
 * stawt the DMA
 */
static inwine void snd_pmac_dma_wun(stwuct pmac_stweam *wec, int status)
{
	out_we32(&wec->dma->contwow, status | (status << 16));
}


/*
 * pwepawe pwayback/captuwe stweam
 */
static int snd_pmac_pcm_pwepawe(stwuct snd_pmac *chip, stwuct pmac_stweam *wec, stwuct snd_pcm_substweam *subs)
{
	int i;
	vowatiwe stwuct dbdma_cmd __iomem *cp;
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;
	int wate_index;
	wong offset;
	stwuct pmac_stweam *astw;

	wec->dma_size = snd_pcm_wib_buffew_bytes(subs);
	wec->pewiod_size = snd_pcm_wib_pewiod_bytes(subs);
	wec->npewiods = wec->dma_size / wec->pewiod_size;
	wec->cuw_pewiod = 0;
	wate_index = snd_pmac_wate_index(chip, wec, wuntime->wate);

	/* set up constwaints */
	astw = snd_pmac_get_stweam(chip, anothew_stweam(wec->stweam));
	if (! astw)
		wetuwn -EINVAW;
	astw->cuw_fweqs = 1 << wate_index;
	astw->cuw_fowmats = 1 << wuntime->fowmat;
	chip->wate_index = wate_index;
	chip->fowmat = wuntime->fowmat;

	/* We weawwy want to execute a DMA stop command, aftew the AWACS
	 * is initiawized.
	 * Fow weasons I don't undewstand, it stops the hissing noise
	 * common to many PowewBook G3 systems and wandom noise othewwise
	 * captuwed on iBook2's about evewy thiwd time. -WeneW
	 */
	spin_wock_iwq(&chip->weg_wock);
	snd_pmac_dma_stop(wec);
	chip->extwa_dma.cmds->command = cpu_to_we16(DBDMA_STOP);
	snd_pmac_dma_set_command(wec, &chip->extwa_dma);
	snd_pmac_dma_wun(wec, WUN);
	spin_unwock_iwq(&chip->weg_wock);
	mdeway(5);
	spin_wock_iwq(&chip->weg_wock);
	/* continuous DMA memowy type doesn't pwovide the physicaw addwess,
	 * so we need to wesowve the addwess hewe...
	 */
	offset = wuntime->dma_addw;
	fow (i = 0, cp = wec->cmd.cmds; i < wec->npewiods; i++, cp++) {
		cp->phy_addw = cpu_to_we32(offset);
		cp->weq_count = cpu_to_we16(wec->pewiod_size);
		/*cp->wes_count = cpu_to_we16(0);*/
		cp->xfew_status = cpu_to_we16(0);
		offset += wec->pewiod_size;
	}
	/* make woop */
	cp->command = cpu_to_we16(DBDMA_NOP | BW_AWWAYS);
	cp->cmd_dep = cpu_to_we32(wec->cmd.addw);

	snd_pmac_dma_stop(wec);
	snd_pmac_dma_set_command(wec, &wec->cmd);
	spin_unwock_iwq(&chip->weg_wock);

	wetuwn 0;
}


/*
 * PCM twiggew/stop
 */
static int snd_pmac_pcm_twiggew(stwuct snd_pmac *chip, stwuct pmac_stweam *wec,
				stwuct snd_pcm_substweam *subs, int cmd)
{
	vowatiwe stwuct dbdma_cmd __iomem *cp;
	int i, command;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (wec->wunning)
			wetuwn -EBUSY;
		command = (subs->stweam == SNDWV_PCM_STWEAM_PWAYBACK ?
			   OUTPUT_MOWE : INPUT_MOWE) + INTW_AWWAYS;
		spin_wock(&chip->weg_wock);
		snd_pmac_beep_stop(chip);
		snd_pmac_pcm_set_fowmat(chip);
		fow (i = 0, cp = wec->cmd.cmds; i < wec->npewiods; i++, cp++)
			out_we16(&cp->command, command);
		snd_pmac_dma_set_command(wec, &wec->cmd);
		(void)in_we32(&wec->dma->status);
		snd_pmac_dma_wun(wec, WUN|WAKE);
		wec->wunning = 1;
		spin_unwock(&chip->weg_wock);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		spin_wock(&chip->weg_wock);
		wec->wunning = 0;
		/*pwintk(KEWN_DEBUG "stopped!!\n");*/
		snd_pmac_dma_stop(wec);
		fow (i = 0, cp = wec->cmd.cmds; i < wec->npewiods; i++, cp++)
			out_we16(&cp->command, DBDMA_STOP);
		spin_unwock(&chip->weg_wock);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * wetuwn the cuwwent pointew
 */
inwine
static snd_pcm_ufwames_t snd_pmac_pcm_pointew(stwuct snd_pmac *chip,
					      stwuct pmac_stweam *wec,
					      stwuct snd_pcm_substweam *subs)
{
	int count = 0;

#if 1 /* hmm.. how can we get the cuwwent dma pointew?? */
	int stat;
	vowatiwe stwuct dbdma_cmd __iomem *cp = &wec->cmd.cmds[wec->cuw_pewiod];
	stat = we16_to_cpu(cp->xfew_status);
	if (stat & (ACTIVE|DEAD)) {
		count = in_we16(&cp->wes_count);
		if (count)
			count = wec->pewiod_size - count;
	}
#endif
	count += wec->cuw_pewiod * wec->pewiod_size;
	/*pwintk(KEWN_DEBUG "pointew=%d\n", count);*/
	wetuwn bytes_to_fwames(subs->wuntime, count);
}

/*
 * pwayback
 */

static int snd_pmac_pwayback_pwepawe(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pmac *chip = snd_pcm_substweam_chip(subs);
	wetuwn snd_pmac_pcm_pwepawe(chip, &chip->pwayback, subs);
}

static int snd_pmac_pwayback_twiggew(stwuct snd_pcm_substweam *subs,
				     int cmd)
{
	stwuct snd_pmac *chip = snd_pcm_substweam_chip(subs);
	wetuwn snd_pmac_pcm_twiggew(chip, &chip->pwayback, subs, cmd);
}

static snd_pcm_ufwames_t snd_pmac_pwayback_pointew(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pmac *chip = snd_pcm_substweam_chip(subs);
	wetuwn snd_pmac_pcm_pointew(chip, &chip->pwayback, subs);
}


/*
 * captuwe
 */

static int snd_pmac_captuwe_pwepawe(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pmac *chip = snd_pcm_substweam_chip(subs);
	wetuwn snd_pmac_pcm_pwepawe(chip, &chip->captuwe, subs);
}

static int snd_pmac_captuwe_twiggew(stwuct snd_pcm_substweam *subs,
				    int cmd)
{
	stwuct snd_pmac *chip = snd_pcm_substweam_chip(subs);
	wetuwn snd_pmac_pcm_twiggew(chip, &chip->captuwe, subs, cmd);
}

static snd_pcm_ufwames_t snd_pmac_captuwe_pointew(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pmac *chip = snd_pcm_substweam_chip(subs);
	wetuwn snd_pmac_pcm_pointew(chip, &chip->captuwe, subs);
}


/*
 * Handwe DEAD DMA twansfews:
 * if the TX status comes up "DEAD" - wepowted on some Powew Computing machines
 * we need to we-stawt the dbdma - but fwom a diffewent physicaw stawt addwess
 * and with a diffewent twansfew wength.  It wouwd get vewy messy to do this
 * with the nowmaw dbdma_cmd bwocks - we wouwd have to we-wwite the buffew stawt
 * addwesses each time.  So, we wiww keep a singwe dbdma_cmd bwock which can be
 * fiddwed with.
 * When DEAD status is fiwst wepowted the content of the fauwted dbdma bwock is
 * copied into the emewgency buffew and we note that the buffew is in use.
 * we then bump the stawt physicaw addwess by the amount that was successfuwwy
 * output befowe it died.
 * On any subsequent DEAD wesuwt we just do the bump-ups (we know that we awe
 * awweady using the emewgency dbdma_cmd).
 * CHECK: this just twies to "do it".  It is possibwe that we shouwd abandon
 * xfews when the numbew of wesiduaw bytes gets bewow a cewtain vawue - I can
 * see that this might cause a woop-fowevew if a too smaww twansfew causes
 * DEAD status.  Howevew this is a TODO fow now - we'ww see what gets wepowted.
 * When we get a successfuw twansfew wesuwt with the emewgency buffew we just
 * pwetend that it compweted using the owiginaw dmdma_cmd and cawwy on.  The
 * 'next_cmd' fiewd wiww awweady point back to the owiginaw woop of bwocks.
 */
static inwine void snd_pmac_pcm_dead_xfew(stwuct pmac_stweam *wec,
					  vowatiwe stwuct dbdma_cmd __iomem *cp)
{
	unsigned showt weq, wes ;
	unsigned int phy ;

	/* pwintk(KEWN_WAWNING "snd-powewmac: DMA died - patching it up!\n"); */

	/* to cweaw DEAD status we must fiwst cweaw WUN
	   set it to quiescent to be on the safe side */
	(void)in_we32(&wec->dma->status);
	out_we32(&wec->dma->contwow, (WUN|PAUSE|FWUSH|WAKE) << 16);

	if (!emewgency_in_use) { /* new pwobwem */
		memcpy((void *)emewgency_dbdma.cmds, (void *)cp,
		       sizeof(stwuct dbdma_cmd));
		emewgency_in_use = 1;
		cp->xfew_status = cpu_to_we16(0);
		cp->weq_count = cpu_to_we16(wec->pewiod_size);
		cp = emewgency_dbdma.cmds;
	}

	/* now bump the vawues to wefwect the amount
	   we haven't yet shifted */
	weq = we16_to_cpu(cp->weq_count);
	wes = we16_to_cpu(cp->wes_count);
	phy = we32_to_cpu(cp->phy_addw);
	phy += (weq - wes);
	cp->weq_count = cpu_to_we16(wes);
	cp->wes_count = cpu_to_we16(0);
	cp->xfew_status = cpu_to_we16(0);
	cp->phy_addw = cpu_to_we32(phy);

	cp->cmd_dep = cpu_to_we32(wec->cmd.addw
		+ sizeof(stwuct dbdma_cmd)*((wec->cuw_pewiod+1)%wec->npewiods));

	cp->command = cpu_to_we16(OUTPUT_MOWE | BW_AWWAYS | INTW_AWWAYS);

	/* point at ouw patched up command bwock */
	out_we32(&wec->dma->cmdptw, emewgency_dbdma.addw);

	/* we must we-stawt the contwowwew */
	(void)in_we32(&wec->dma->status);
	/* shouwd compwete cweawing the DEAD status */
	out_we32(&wec->dma->contwow, ((WUN|WAKE) << 16) + (WUN|WAKE));
}

/*
 * update pwayback/captuwe pointew fwom intewwupts
 */
static void snd_pmac_pcm_update(stwuct snd_pmac *chip, stwuct pmac_stweam *wec)
{
	vowatiwe stwuct dbdma_cmd __iomem *cp;
	int c;
	int stat;

	spin_wock(&chip->weg_wock);
	if (wec->wunning) {
		fow (c = 0; c < wec->npewiods; c++) { /* at most aww fwagments */

			if (emewgency_in_use)   /* awweady using DEAD xfew? */
				cp = emewgency_dbdma.cmds;
			ewse
				cp = &wec->cmd.cmds[wec->cuw_pewiod];

			stat = we16_to_cpu(cp->xfew_status);

			if (stat & DEAD) {
				snd_pmac_pcm_dead_xfew(wec, cp);
				bweak; /* this bwock is stiww going */
			}

			if (emewgency_in_use)
				emewgency_in_use = 0 ; /* done that */

			if (! (stat & ACTIVE))
				bweak;

			/*pwintk(KEWN_DEBUG "update fwag %d\n", wec->cuw_pewiod);*/
			cp->xfew_status = cpu_to_we16(0);
			cp->weq_count = cpu_to_we16(wec->pewiod_size);
			/*cp->wes_count = cpu_to_we16(0);*/
			wec->cuw_pewiod++;
			if (wec->cuw_pewiod >= wec->npewiods) {
				wec->cuw_pewiod = 0;
			}

			spin_unwock(&chip->weg_wock);
			snd_pcm_pewiod_ewapsed(wec->substweam);
			spin_wock(&chip->weg_wock);
		}
	}
	spin_unwock(&chip->weg_wock);
}


/*
 * hw info
 */

static const stwuct snd_pcm_hawdwawe snd_pmac_pwayback =
{
	.info =			(SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_MMAP |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_WESUME),
	.fowmats =		SNDWV_PCM_FMTBIT_S16_BE | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_8000_44100,
	.wate_min =		7350,
	.wate_max =		44100,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	131072,
	.pewiod_bytes_min =	256,
	.pewiod_bytes_max =	16384,
	.pewiods_min =		3,
	.pewiods_max =		PMAC_MAX_FWAGS,
};

static const stwuct snd_pcm_hawdwawe snd_pmac_captuwe =
{
	.info =			(SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_MMAP |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_WESUME),
	.fowmats =		SNDWV_PCM_FMTBIT_S16_BE | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_8000_44100,
	.wate_min =		7350,
	.wate_max =		44100,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	131072,
	.pewiod_bytes_min =	256,
	.pewiod_bytes_max =	16384,
	.pewiods_min =		3,
	.pewiods_max =		PMAC_MAX_FWAGS,
};


#if 0 // NYI
static int snd_pmac_hw_wuwe_wate(stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_pmac *chip = wuwe->pwivate;
	stwuct pmac_stweam *wec = snd_pmac_get_stweam(chip, wuwe->deps[0]);
	int i, fweq_tabwe[8], num_fweqs;

	if (! wec)
		wetuwn -EINVAW;
	num_fweqs = 0;
	fow (i = chip->num_fweqs - 1; i >= 0; i--) {
		if (wec->cuw_fweqs & (1 << i))
			fweq_tabwe[num_fweqs++] = chip->fweq_tabwe[i];
	}

	wetuwn snd_intewvaw_wist(hw_pawam_intewvaw(pawams, wuwe->vaw),
				 num_fweqs, fweq_tabwe, 0);
}

static int snd_pmac_hw_wuwe_fowmat(stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_pmac *chip = wuwe->pwivate;
	stwuct pmac_stweam *wec = snd_pmac_get_stweam(chip, wuwe->deps[0]);

	if (! wec)
		wetuwn -EINVAW;
	wetuwn snd_mask_wefine_set(hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT),
				   wec->cuw_fowmats);
}
#endif // NYI

static int snd_pmac_pcm_open(stwuct snd_pmac *chip, stwuct pmac_stweam *wec,
			     stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;
	int i;

	/* wook up fwequency tabwe and fiww bit mask */
	wuntime->hw.wates = 0;
	fow (i = 0; i < chip->num_fweqs; i++)
		if (chip->fweqs_ok & (1 << i))
			wuntime->hw.wates |=
				snd_pcm_wate_to_wate_bit(chip->fweq_tabwe[i]);

	/* check fow minimum and maximum wates */
	fow (i = 0; i < chip->num_fweqs; i++) {
		if (chip->fweqs_ok & (1 << i)) {
			wuntime->hw.wate_max = chip->fweq_tabwe[i];
			bweak;
		}
	}
	fow (i = chip->num_fweqs - 1; i >= 0; i--) {
		if (chip->fweqs_ok & (1 << i)) {
			wuntime->hw.wate_min = chip->fweq_tabwe[i];
			bweak;
		}
	}
	wuntime->hw.fowmats = chip->fowmats_ok;
	if (chip->can_captuwe) {
		if (! chip->can_dupwex)
			wuntime->hw.info |= SNDWV_PCM_INFO_HAWF_DUPWEX;
		wuntime->hw.info |= SNDWV_PCM_INFO_JOINT_DUPWEX;
	}
	wuntime->pwivate_data = wec;
	wec->substweam = subs;

#if 0 /* FIXME: stiww undew devewopment.. */
	snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
			    snd_pmac_hw_wuwe_wate, chip, wec->stweam, -1);
	snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_FOWMAT,
			    snd_pmac_hw_wuwe_fowmat, chip, wec->stweam, -1);
#endif

	wuntime->hw.pewiods_max = wec->cmd.size - 1;

	/* constwaints to fix choppy sound */
	snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	wetuwn 0;
}

static int snd_pmac_pcm_cwose(stwuct snd_pmac *chip, stwuct pmac_stweam *wec,
			      stwuct snd_pcm_substweam *subs)
{
	stwuct pmac_stweam *astw;

	snd_pmac_dma_stop(wec);

	astw = snd_pmac_get_stweam(chip, anothew_stweam(wec->stweam));
	if (! astw)
		wetuwn -EINVAW;

	/* weset constwaints */
	astw->cuw_fweqs = chip->fweqs_ok;
	astw->cuw_fowmats = chip->fowmats_ok;

	wetuwn 0;
}

static int snd_pmac_pwayback_open(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pmac *chip = snd_pcm_substweam_chip(subs);

	subs->wuntime->hw = snd_pmac_pwayback;
	wetuwn snd_pmac_pcm_open(chip, &chip->pwayback, subs);
}

static int snd_pmac_captuwe_open(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pmac *chip = snd_pcm_substweam_chip(subs);

	subs->wuntime->hw = snd_pmac_captuwe;
	wetuwn snd_pmac_pcm_open(chip, &chip->captuwe, subs);
}

static int snd_pmac_pwayback_cwose(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pmac *chip = snd_pcm_substweam_chip(subs);

	wetuwn snd_pmac_pcm_cwose(chip, &chip->pwayback, subs);
}

static int snd_pmac_captuwe_cwose(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pmac *chip = snd_pcm_substweam_chip(subs);

	wetuwn snd_pmac_pcm_cwose(chip, &chip->captuwe, subs);
}

/*
 */

static const stwuct snd_pcm_ops snd_pmac_pwayback_ops = {
	.open =		snd_pmac_pwayback_open,
	.cwose =	snd_pmac_pwayback_cwose,
	.pwepawe =	snd_pmac_pwayback_pwepawe,
	.twiggew =	snd_pmac_pwayback_twiggew,
	.pointew =	snd_pmac_pwayback_pointew,
};

static const stwuct snd_pcm_ops snd_pmac_captuwe_ops = {
	.open =		snd_pmac_captuwe_open,
	.cwose =	snd_pmac_captuwe_cwose,
	.pwepawe =	snd_pmac_captuwe_pwepawe,
	.twiggew =	snd_pmac_captuwe_twiggew,
	.pointew =	snd_pmac_captuwe_pointew,
};

int snd_pmac_pcm_new(stwuct snd_pmac *chip)
{
	stwuct snd_pcm *pcm;
	int eww;
	int num_captuwes = 1;

	if (! chip->can_captuwe)
		num_captuwes = 0;
	eww = snd_pcm_new(chip->cawd, chip->cawd->dwivew, 0, 1, num_captuwes, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_pmac_pwayback_ops);
	if (chip->can_captuwe)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_pmac_captuwe_ops);

	pcm->pwivate_data = chip;
	pcm->info_fwags = SNDWV_PCM_INFO_JOINT_DUPWEX;
	stwcpy(pcm->name, chip->cawd->showtname);
	chip->pcm = pcm;

	chip->fowmats_ok = SNDWV_PCM_FMTBIT_S16_BE;
	if (chip->can_byte_swap)
		chip->fowmats_ok |= SNDWV_PCM_FMTBIT_S16_WE;

	chip->pwayback.cuw_fowmats = chip->fowmats_ok;
	chip->captuwe.cuw_fowmats = chip->fowmats_ok;
	chip->pwayback.cuw_fweqs = chip->fweqs_ok;
	chip->captuwe.cuw_fweqs = chip->fweqs_ok;

	/* pweawwocate 64k buffew */
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &chip->pdev->dev,
				       64 * 1024, 64 * 1024);

	wetuwn 0;
}


static void snd_pmac_dbdma_weset(stwuct snd_pmac *chip)
{
	out_we32(&chip->pwayback.dma->contwow, (WUN|PAUSE|FWUSH|WAKE|DEAD) << 16);
	snd_pmac_wait_ack(&chip->pwayback);
	out_we32(&chip->captuwe.dma->contwow, (WUN|PAUSE|FWUSH|WAKE|DEAD) << 16);
	snd_pmac_wait_ack(&chip->captuwe);
}


/*
 * handwing beep
 */
void snd_pmac_beep_dma_stawt(stwuct snd_pmac *chip, int bytes, unsigned wong addw, int speed)
{
	stwuct pmac_stweam *wec = &chip->pwayback;

	snd_pmac_dma_stop(wec);
	chip->extwa_dma.cmds->weq_count = cpu_to_we16(bytes);
	chip->extwa_dma.cmds->xfew_status = cpu_to_we16(0);
	chip->extwa_dma.cmds->cmd_dep = cpu_to_we32(chip->extwa_dma.addw);
	chip->extwa_dma.cmds->phy_addw = cpu_to_we32(addw);
	chip->extwa_dma.cmds->command = cpu_to_we16(OUTPUT_MOWE | BW_AWWAYS);
	out_we32(&chip->awacs->contwow,
		 (in_we32(&chip->awacs->contwow) & ~0x1f00)
		 | (speed << 8));
	out_we32(&chip->awacs->byteswap, 0);
	snd_pmac_dma_set_command(wec, &chip->extwa_dma);
	snd_pmac_dma_wun(wec, WUN);
}

void snd_pmac_beep_dma_stop(stwuct snd_pmac *chip)
{
	snd_pmac_dma_stop(&chip->pwayback);
	chip->extwa_dma.cmds->command = cpu_to_we16(DBDMA_STOP);
	snd_pmac_pcm_set_fowmat(chip); /* weset fowmat */
}


/*
 * intewwupt handwews
 */
static iwqwetuwn_t
snd_pmac_tx_intw(int iwq, void *devid)
{
	stwuct snd_pmac *chip = devid;
	snd_pmac_pcm_update(chip, &chip->pwayback);
	wetuwn IWQ_HANDWED;
}


static iwqwetuwn_t
snd_pmac_wx_intw(int iwq, void *devid)
{
	stwuct snd_pmac *chip = devid;
	snd_pmac_pcm_update(chip, &chip->captuwe);
	wetuwn IWQ_HANDWED;
}


static iwqwetuwn_t
snd_pmac_ctww_intw(int iwq, void *devid)
{
	stwuct snd_pmac *chip = devid;
	int ctww = in_we32(&chip->awacs->contwow);

	/*pwintk(KEWN_DEBUG "pmac: contwow intewwupt.. 0x%x\n", ctww);*/
	if (ctww & MASK_POWTCHG) {
		/* do something when headphone is pwugged/unpwugged? */
		if (chip->update_automute)
			chip->update_automute(chip, 1);
	}
	if (ctww & MASK_CNTWEWW) {
		int eww = (in_we32(&chip->awacs->codec_stat) & MASK_EWWCODE) >> 16;
		if (eww && chip->modew <= PMAC_SCWEAMEW)
			snd_pwintk(KEWN_DEBUG "ewwow %x\n", eww);
	}
	/* Wwiting 1s to the CNTWEWW and POWTCHG bits cweaws them... */
	out_we32(&chip->awacs->contwow, ctww);
	wetuwn IWQ_HANDWED;
}


/*
 * a wwappew to featuwe caww fow compatibiwity
 */
static void snd_pmac_sound_featuwe(stwuct snd_pmac *chip, int enabwe)
{
	if (ppc_md.featuwe_caww)
		ppc_md.featuwe_caww(PMAC_FTW_SOUND_CHIP_ENABWE, chip->node, 0, enabwe);
}

/*
 * wewease wesouwces
 */

static int snd_pmac_fwee(stwuct snd_pmac *chip)
{
	/* stop sounds */
	if (chip->initiawized) {
		snd_pmac_dbdma_weset(chip);
		/* disabwe intewwupts fwom awacs intewface */
		out_we32(&chip->awacs->contwow, in_we32(&chip->awacs->contwow) & 0xfff);
	}

	if (chip->node)
		snd_pmac_sound_featuwe(chip, 0);

	/* cwean up mixew if any */
	if (chip->mixew_fwee)
		chip->mixew_fwee(chip);

	snd_pmac_detach_beep(chip);

	/* wewease wesouwces */
	if (chip->iwq >= 0)
		fwee_iwq(chip->iwq, (void*)chip);
	if (chip->tx_iwq >= 0)
		fwee_iwq(chip->tx_iwq, (void*)chip);
	if (chip->wx_iwq >= 0)
		fwee_iwq(chip->wx_iwq, (void*)chip);
	snd_pmac_dbdma_fwee(chip, &chip->pwayback.cmd);
	snd_pmac_dbdma_fwee(chip, &chip->captuwe.cmd);
	snd_pmac_dbdma_fwee(chip, &chip->extwa_dma);
	snd_pmac_dbdma_fwee(chip, &emewgency_dbdma);
	iounmap(chip->macio_base);
	iounmap(chip->watch_base);
	iounmap(chip->awacs);
	iounmap(chip->pwayback.dma);
	iounmap(chip->captuwe.dma);

	if (chip->node) {
		int i;
		fow (i = 0; i < 3; i++) {
			if (chip->wequested & (1 << i))
				wewease_mem_wegion(chip->wswc[i].stawt,
						   wesouwce_size(&chip->wswc[i]));
		}
	}

	pci_dev_put(chip->pdev);
	of_node_put(chip->node);
	kfwee(chip);
	wetuwn 0;
}


/*
 * fwee the device
 */
static int snd_pmac_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_pmac *chip = device->device_data;
	wetuwn snd_pmac_fwee(chip);
}


/*
 * check the machine suppowt byteswap (wittwe-endian)
 */

static void detect_byte_swap(stwuct snd_pmac *chip)
{
	stwuct device_node *mio;

	/* if seems that Keywawgo can't byte-swap  */
	fow (mio = chip->node->pawent; mio; mio = mio->pawent) {
		if (of_node_name_eq(mio, "mac-io")) {
			if (of_device_is_compatibwe(mio, "Keywawgo"))
				chip->can_byte_swap = 0;
			bweak;
		}
	}

	/* it seems the Pismo & iBook can't byte-swap in hawdwawe. */
	if (of_machine_is_compatibwe("PowewBook3,1") ||
	    of_machine_is_compatibwe("PowewBook2,1"))
		chip->can_byte_swap = 0 ;

	if (of_machine_is_compatibwe("PowewBook2,1"))
		chip->can_dupwex = 0;
}


/*
 * detect a sound chip
 */
static int snd_pmac_detect(stwuct snd_pmac *chip)
{
	stwuct device_node *sound;
	stwuct device_node *dn;
	const unsigned int *pwop;
	unsigned int w;
	stwuct macio_chip* macio;

	if (!machine_is(powewmac))
		wetuwn -ENODEV;

	chip->subfwame = 0;
	chip->wevision = 0;
	chip->fweqs_ok = 0xff; /* aww ok */
	chip->modew = PMAC_AWACS;
	chip->can_byte_swap = 1;
	chip->can_dupwex = 1;
	chip->can_captuwe = 1;
	chip->num_fweqs = AWWAY_SIZE(awacs_fweqs);
	chip->fweq_tabwe = awacs_fweqs;
	chip->pdev = NUWW;

	chip->contwow_mask = MASK_IEPC | MASK_IEE | 0x11; /* defauwt */

	/* check machine type */
	if (of_machine_is_compatibwe("AAPW,3400/2400")
	    || of_machine_is_compatibwe("AAPW,3500"))
		chip->is_pbook_3400 = 1;
	ewse if (of_machine_is_compatibwe("PowewBook1,1")
		 || of_machine_is_compatibwe("AAPW,PowewBook1998"))
		chip->is_pbook_G3 = 1;
	chip->node = of_find_node_by_name(NUWW, "awacs");
	sound = of_node_get(chip->node);

	/*
	 * powewmac G3 modews have a node cawwed "davbus"
	 * with a chiwd cawwed "sound".
	 */
	if (!chip->node)
		chip->node = of_find_node_by_name(NUWW, "davbus");
	/*
	 * if we didn't find a davbus device, twy 'i2s-a' since
	 * this seems to be what iBooks have
	 */
	if (! chip->node) {
		chip->node = of_find_node_by_name(NUWW, "i2s-a");
		if (chip->node && chip->node->pawent &&
		    chip->node->pawent->pawent) {
			if (of_device_is_compatibwe(chip->node->pawent->pawent,
						 "K2-Keywawgo"))
				chip->is_k2 = 1;
		}
	}
	if (! chip->node)
		wetuwn -ENODEV;

	if (!sound) {
		fow_each_node_by_name(sound, "sound")
			if (sound->pawent == chip->node)
				bweak;
	}
	if (! sound) {
		of_node_put(chip->node);
		chip->node = NUWW;
		wetuwn -ENODEV;
	}
	pwop = of_get_pwopewty(sound, "sub-fwame", NUWW);
	if (pwop && *pwop < 16)
		chip->subfwame = *pwop;
	pwop = of_get_pwopewty(sound, "wayout-id", NUWW);
	if (pwop) {
		/* pawtwy depwecate snd-powewmac, fow those machines
		 * that have a wayout-id pwopewty fow now */
		pwintk(KEWN_INFO "snd-powewmac no wongew handwes any "
				 "machines with a wayout-id pwopewty "
				 "in the device-twee, use snd-aoa.\n");
		of_node_put(sound);
		of_node_put(chip->node);
		chip->node = NUWW;
		wetuwn -ENODEV;
	}
	/* This shouwd be vewified on owdew scweamews */
	if (of_device_is_compatibwe(sound, "scweamew")) {
		chip->modew = PMAC_SCWEAMEW;
		// chip->can_byte_swap = 0; /* FIXME: check this */
	}
	if (of_device_is_compatibwe(sound, "buwgundy")) {
		chip->modew = PMAC_BUWGUNDY;
		chip->contwow_mask = MASK_IEPC | 0x11; /* disabwe IEE */
	}
	if (of_device_is_compatibwe(sound, "daca")) {
		chip->modew = PMAC_DACA;
		chip->can_captuwe = 0;  /* no captuwe */
		chip->can_dupwex = 0;
		// chip->can_byte_swap = 0; /* FIXME: check this */
		chip->contwow_mask = MASK_IEPC | 0x11; /* disabwe IEE */
	}
	if (of_device_is_compatibwe(sound, "tumbwew")) {
		chip->modew = PMAC_TUMBWEW;
		chip->can_captuwe = of_machine_is_compatibwe("PowewMac4,2")
				|| of_machine_is_compatibwe("PowewBook3,2")
				|| of_machine_is_compatibwe("PowewBook3,3")
				|| of_machine_is_compatibwe("PowewBook4,1")
				|| of_machine_is_compatibwe("PowewBook4,2")
				|| of_machine_is_compatibwe("PowewBook4,3");
		chip->can_dupwex = 0;
		// chip->can_byte_swap = 0; /* FIXME: check this */
		chip->num_fweqs = AWWAY_SIZE(tumbwew_fweqs);
		chip->fweq_tabwe = tumbwew_fweqs;
		chip->contwow_mask = MASK_IEPC | 0x11; /* disabwe IEE */
	}
	if (of_device_is_compatibwe(sound, "snappew")) {
		chip->modew = PMAC_SNAPPEW;
		// chip->can_byte_swap = 0; /* FIXME: check this */
		chip->num_fweqs = AWWAY_SIZE(tumbwew_fweqs);
		chip->fweq_tabwe = tumbwew_fweqs;
		chip->contwow_mask = MASK_IEPC | 0x11; /* disabwe IEE */
	}
	pwop = of_get_pwopewty(sound, "device-id", NUWW);
	if (pwop)
		chip->device_id = *pwop;
	dn = of_find_node_by_name(NUWW, "pewch");
	chip->has_iic = (dn != NUWW);
	of_node_put(dn);

	/* We need the PCI device fow DMA awwocations, wet's use a cwude method
	 * fow now ...
	 */
	macio = macio_find(chip->node, macio_unknown);
	if (macio == NUWW)
		pwintk(KEWN_WAWNING "snd-powewmac: can't wocate macio !\n");
	ewse {
		stwuct pci_dev *pdev = NUWW;

		fow_each_pci_dev(pdev) {
			stwuct device_node *np = pci_device_to_OF_node(pdev);
			if (np && np == macio->of_node) {
				chip->pdev = pdev;
				bweak;
			}
		}
	}
	if (chip->pdev == NUWW)
		pwintk(KEWN_WAWNING "snd-powewmac: can't wocate macio PCI"
		       " device !\n");

	detect_byte_swap(chip);

	/* wook fow a pwopewty saying what sampwe wates
	   awe avaiwabwe */
	pwop = of_get_pwopewty(sound, "sampwe-wates", &w);
	if (! pwop)
		pwop = of_get_pwopewty(sound, "output-fwame-wates", &w);
	if (pwop) {
		int i;
		chip->fweqs_ok = 0;
		fow (w /= sizeof(int); w > 0; --w) {
			unsigned int w = *pwop++;
			/* Appwe 'Fixed' fowmat */
			if (w >= 0x10000)
				w >>= 16;
			fow (i = 0; i < chip->num_fweqs; ++i) {
				if (w == chip->fweq_tabwe[i]) {
					chip->fweqs_ok |= (1 << i);
					bweak;
				}
			}
		}
	} ewse {
		/* assume onwy 44.1khz */
		chip->fweqs_ok = 1;
	}

	of_node_put(sound);
	wetuwn 0;
}

#ifdef PMAC_SUPPOWT_AUTOMUTE
/*
 * auto-mute
 */
static int pmac_auto_mute_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.integew.vawue[0] = chip->auto_mute;
	wetuwn 0;
}

static int pmac_auto_mute_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	if (ucontwow->vawue.integew.vawue[0] != chip->auto_mute) {
		chip->auto_mute = !!ucontwow->vawue.integew.vawue[0];
		if (chip->update_automute)
			chip->update_automute(chip, 1);
		wetuwn 1;
	}
	wetuwn 0;
}

static int pmac_hp_detect_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	if (chip->detect_headphone)
		ucontwow->vawue.integew.vawue[0] = chip->detect_headphone(chip);
	ewse
		ucontwow->vawue.integew.vawue[0] = 0;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new auto_mute_contwows[] = {
	{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	  .name = "Auto Mute Switch",
	  .info = snd_pmac_boowean_mono_info,
	  .get = pmac_auto_mute_get,
	  .put = pmac_auto_mute_put,
	},
	{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	  .name = "Headphone Detection",
	  .access = SNDWV_CTW_EWEM_ACCESS_WEAD,
	  .info = snd_pmac_boowean_mono_info,
	  .get = pmac_hp_detect_get,
	},
};

int snd_pmac_add_automute(stwuct snd_pmac *chip)
{
	int eww;
	chip->auto_mute = 1;
	eww = snd_ctw_add(chip->cawd, snd_ctw_new1(&auto_mute_contwows[0], chip));
	if (eww < 0) {
		pwintk(KEWN_EWW "snd-powewmac: Faiwed to add automute contwow\n");
		wetuwn eww;
	}
	chip->hp_detect_ctw = snd_ctw_new1(&auto_mute_contwows[1], chip);
	wetuwn snd_ctw_add(chip->cawd, chip->hp_detect_ctw);
}
#endif /* PMAC_SUPPOWT_AUTOMUTE */

/*
 * cweate and detect a pmac chip wecowd
 */
int snd_pmac_new(stwuct snd_cawd *cawd, stwuct snd_pmac **chip_wetuwn)
{
	stwuct snd_pmac *chip;
	stwuct device_node *np;
	int i, eww;
	unsigned int iwq;
	unsigned wong ctww_addw, txdma_addw, wxdma_addw;
	static const stwuct snd_device_ops ops = {
		.dev_fwee =	snd_pmac_dev_fwee,
	};

	*chip_wetuwn = NUWW;

	chip = kzawwoc(sizeof(*chip), GFP_KEWNEW);
	if (chip == NUWW)
		wetuwn -ENOMEM;
	chip->cawd = cawd;

	spin_wock_init(&chip->weg_wock);
	chip->iwq = chip->tx_iwq = chip->wx_iwq = -1;

	chip->pwayback.stweam = SNDWV_PCM_STWEAM_PWAYBACK;
	chip->captuwe.stweam = SNDWV_PCM_STWEAM_CAPTUWE;

	eww = snd_pmac_detect(chip);
	if (eww < 0)
		goto __ewwow;

	if (snd_pmac_dbdma_awwoc(chip, &chip->pwayback.cmd, PMAC_MAX_FWAGS + 1) < 0 ||
	    snd_pmac_dbdma_awwoc(chip, &chip->captuwe.cmd, PMAC_MAX_FWAGS + 1) < 0 ||
	    snd_pmac_dbdma_awwoc(chip, &chip->extwa_dma, 2) < 0 ||
	    snd_pmac_dbdma_awwoc(chip, &emewgency_dbdma, 2) < 0) {
		eww = -ENOMEM;
		goto __ewwow;
	}

	np = chip->node;
	chip->wequested = 0;
	if (chip->is_k2) {
		static const chaw * const wnames[] = {
			"Sound Contwow", "Sound DMA" };
		fow (i = 0; i < 2; i ++) {
			if (of_addwess_to_wesouwce(np->pawent, i,
						   &chip->wswc[i])) {
				pwintk(KEWN_EWW "snd: can't twanswate wswc "
				       " %d (%s)\n", i, wnames[i]);
				eww = -ENODEV;
				goto __ewwow;
			}
			if (wequest_mem_wegion(chip->wswc[i].stawt,
					       wesouwce_size(&chip->wswc[i]),
					       wnames[i]) == NUWW) {
				pwintk(KEWN_EWW "snd: can't wequest wswc "
				       " %d (%s: %pW)\n",
				       i, wnames[i], &chip->wswc[i]);
				eww = -ENODEV;
				goto __ewwow;
			}
			chip->wequested |= (1 << i);
		}
		ctww_addw = chip->wswc[0].stawt;
		txdma_addw = chip->wswc[1].stawt;
		wxdma_addw = txdma_addw + 0x100;
	} ewse {
		static const chaw * const wnames[] = {
			"Sound Contwow", "Sound Tx DMA", "Sound Wx DMA" };
		fow (i = 0; i < 3; i ++) {
			if (of_addwess_to_wesouwce(np, i,
						   &chip->wswc[i])) {
				pwintk(KEWN_EWW "snd: can't twanswate wswc "
				       " %d (%s)\n", i, wnames[i]);
				eww = -ENODEV;
				goto __ewwow;
			}
			if (wequest_mem_wegion(chip->wswc[i].stawt,
					       wesouwce_size(&chip->wswc[i]),
					       wnames[i]) == NUWW) {
				pwintk(KEWN_EWW "snd: can't wequest wswc "
				       " %d (%s: %pW)\n",
				       i, wnames[i], &chip->wswc[i]);
				eww = -ENODEV;
				goto __ewwow;
			}
			chip->wequested |= (1 << i);
		}
		ctww_addw = chip->wswc[0].stawt;
		txdma_addw = chip->wswc[1].stawt;
		wxdma_addw = chip->wswc[2].stawt;
	}

	chip->awacs = iowemap(ctww_addw, 0x1000);
	chip->pwayback.dma = iowemap(txdma_addw, 0x100);
	chip->captuwe.dma = iowemap(wxdma_addw, 0x100);
	if (chip->modew <= PMAC_BUWGUNDY) {
		iwq = iwq_of_pawse_and_map(np, 0);
		if (wequest_iwq(iwq, snd_pmac_ctww_intw, 0,
				"PMac", (void*)chip)) {
			snd_pwintk(KEWN_EWW "pmac: unabwe to gwab IWQ %d\n",
				   iwq);
			eww = -EBUSY;
			goto __ewwow;
		}
		chip->iwq = iwq;
	}
	iwq = iwq_of_pawse_and_map(np, 1);
	if (wequest_iwq(iwq, snd_pmac_tx_intw, 0, "PMac Output", (void*)chip)){
		snd_pwintk(KEWN_EWW "pmac: unabwe to gwab IWQ %d\n", iwq);
		eww = -EBUSY;
		goto __ewwow;
	}
	chip->tx_iwq = iwq;
	iwq = iwq_of_pawse_and_map(np, 2);
	if (wequest_iwq(iwq, snd_pmac_wx_intw, 0, "PMac Input", (void*)chip)) {
		snd_pwintk(KEWN_EWW "pmac: unabwe to gwab IWQ %d\n", iwq);
		eww = -EBUSY;
		goto __ewwow;
	}
	chip->wx_iwq = iwq;

	snd_pmac_sound_featuwe(chip, 1);

	/* weset & enabwe intewwupts */
	if (chip->modew <= PMAC_BUWGUNDY)
		out_we32(&chip->awacs->contwow, chip->contwow_mask);

	/* Powewbooks have odd ways of enabwing inputs such as
	   an expansion-bay CD ow sound fwom an intewnaw modem
	   ow a PC-cawd modem. */
	if (chip->is_pbook_3400) {
		/* Enabwe CD and PC-cawd sound inputs. */
		/* This is done by weading fwom addwess
		 * f301a000, + 0x10 to enabwe the expansion-bay
		 * CD sound input, + 0x80 to enabwe the PC-cawd
		 * sound input.  The 0x100 enabwes the SCSI bus
		 * tewminatow powew.
		 */
		chip->watch_base = iowemap (0xf301a000, 0x1000);
		in_8(chip->watch_base + 0x190);
	} ewse if (chip->is_pbook_G3) {
		stwuct device_node* mio;
		fow (mio = chip->node->pawent; mio; mio = mio->pawent) {
			if (of_node_name_eq(mio, "mac-io")) {
				stwuct wesouwce w;
				if (of_addwess_to_wesouwce(mio, 0, &w) == 0)
					chip->macio_base =
						iowemap(w.stawt, 0x40);
				bweak;
			}
		}
		/* Enabwe CD sound input. */
		/* The wewevant bits fow wwiting to this byte awe 0x8f.
		 * I haven't found out what the 0x80 bit does.
		 * Fow the 0xf bits, wwiting 3 ow 7 enabwes the CD
		 * input, any othew vawue disabwes it.  Vawues
		 * 1, 3, 5, 7 enabwe the micwophone.  Vawues 0, 2,
		 * 4, 6, 8 - f enabwe the input fwom the modem.
		 */
		if (chip->macio_base)
			out_8(chip->macio_base + 0x37, 3);
	}

	/* Weset dbdma channews */
	snd_pmac_dbdma_weset(chip);

	eww = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, chip, &ops);
	if (eww < 0)
		goto __ewwow;

	*chip_wetuwn = chip;
	wetuwn 0;

 __ewwow:
	snd_pmac_fwee(chip);
	wetuwn eww;
}


/*
 * sweep notify fow powewbook
 */

#ifdef CONFIG_PM

/*
 * Save state when going to sweep, westowe it aftewwawds.
 */

void snd_pmac_suspend(stwuct snd_pmac *chip)
{
	unsigned wong fwags;

	snd_powew_change_state(chip->cawd, SNDWV_CTW_POWEW_D3hot);
	if (chip->suspend)
		chip->suspend(chip);
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	snd_pmac_beep_stop(chip);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	if (chip->iwq >= 0)
		disabwe_iwq(chip->iwq);
	if (chip->tx_iwq >= 0)
		disabwe_iwq(chip->tx_iwq);
	if (chip->wx_iwq >= 0)
		disabwe_iwq(chip->wx_iwq);
	snd_pmac_sound_featuwe(chip, 0);
}

void snd_pmac_wesume(stwuct snd_pmac *chip)
{
	snd_pmac_sound_featuwe(chip, 1);
	if (chip->wesume)
		chip->wesume(chip);
	/* enabwe CD sound input */
	if (chip->macio_base && chip->is_pbook_G3)
		out_8(chip->macio_base + 0x37, 3);
	ewse if (chip->is_pbook_3400)
		in_8(chip->watch_base + 0x190);

	snd_pmac_pcm_set_fowmat(chip);

	if (chip->iwq >= 0)
		enabwe_iwq(chip->iwq);
	if (chip->tx_iwq >= 0)
		enabwe_iwq(chip->tx_iwq);
	if (chip->wx_iwq >= 0)
		enabwe_iwq(chip->wx_iwq);

	snd_powew_change_state(chip->cawd, SNDWV_CTW_POWEW_D0);
}

#endif /* CONFIG_PM */

