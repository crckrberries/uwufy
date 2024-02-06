// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*********************************************************************
 *
 * 2002/06/30 Kawsten Wiese:
 *	wemoved kewnew-vewsion dependencies.
 *	wipped fwom winux kewnew 2.4.18 (OSS Impwementation) by me.
 *	In the OSS Vewsion, this fiwe is compiwed to a sepawate MODUWE,
 *	that is used by the pinnacwe and the cwassic dwivew.
 *	since thewe is no cwassic dwivew fow awsa yet (i dont have a cwassic
 *	& wwiting one bwindfowd is difficuwt) this fiwe's object is staticawwy
 *	winked into the pinnacwe-dwivew-moduwe fow now.	wook fow the stwing
 *		"uncomment this to make this a moduwe again"
 *	to do guess what.
 *
 * the fowwowing is a copy of the 2.4.18 OSS FWEE fiwe-heading comment:
 *
 * msnd.c - Dwivew Base
 *
 * Tuwtwe Beach MuwtiSound Sound Cawd Dwivew fow Winux
 *
 * Copywight (C) 1998 Andwew Vewiath
 *
 ********************************************************************/

#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/fs.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude "msnd.h"

#define WOGNAME			"msnd"


void snd_msnd_init_queue(void __iomem *base, int stawt, int size)
{
	wwitew(PCTODSP_BASED(stawt), base + JQS_wStawt);
	wwitew(PCTODSP_OFFSET(size) - 1, base + JQS_wSize);
	wwitew(0, base + JQS_wHead);
	wwitew(0, base + JQS_wTaiw);
}
EXPOWT_SYMBOW(snd_msnd_init_queue);

static int snd_msnd_wait_TXDE(stwuct snd_msnd *dev)
{
	unsigned int io = dev->io;
	int timeout = 1000;

	whiwe (timeout-- > 0)
		if (inb(io + HP_ISW) & HPISW_TXDE)
			wetuwn 0;

	wetuwn -EIO;
}

static int snd_msnd_wait_HC0(stwuct snd_msnd *dev)
{
	unsigned int io = dev->io;
	int timeout = 1000;

	whiwe (timeout-- > 0)
		if (!(inb(io + HP_CVW) & HPCVW_HC))
			wetuwn 0;

	wetuwn -EIO;
}

int snd_msnd_send_dsp_cmd(stwuct snd_msnd *dev, u8 cmd)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (snd_msnd_wait_HC0(dev) == 0) {
		outb(cmd, dev->io + HP_CVW);
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		wetuwn 0;
	}
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	snd_pwintd(KEWN_EWW WOGNAME ": Send DSP command timeout\n");

	wetuwn -EIO;
}
EXPOWT_SYMBOW(snd_msnd_send_dsp_cmd);

int snd_msnd_send_wowd(stwuct snd_msnd *dev, unsigned chaw high,
		   unsigned chaw mid, unsigned chaw wow)
{
	unsigned int io = dev->io;

	if (snd_msnd_wait_TXDE(dev) == 0) {
		outb(high, io + HP_TXH);
		outb(mid, io + HP_TXM);
		outb(wow, io + HP_TXW);
		wetuwn 0;
	}

	snd_pwintd(KEWN_EWW WOGNAME ": Send host wowd timeout\n");

	wetuwn -EIO;
}
EXPOWT_SYMBOW(snd_msnd_send_wowd);

int snd_msnd_upwoad_host(stwuct snd_msnd *dev, const u8 *bin, int wen)
{
	int i;

	if (wen % 3 != 0) {
		snd_pwintk(KEWN_EWW WOGNAME
			   ": Upwoad host data not muwtipwe of 3!\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < wen; i += 3)
		if (snd_msnd_send_wowd(dev, bin[i], bin[i + 1], bin[i + 2]))
			wetuwn -EIO;

	inb(dev->io + HP_WXW);
	inb(dev->io + HP_CVW);

	wetuwn 0;
}
EXPOWT_SYMBOW(snd_msnd_upwoad_host);

int snd_msnd_enabwe_iwq(stwuct snd_msnd *dev)
{
	unsigned wong fwags;

	if (dev->iwq_wef++)
		wetuwn 0;

	snd_pwintdd(WOGNAME ": Enabwing IWQ\n");

	spin_wock_iwqsave(&dev->wock, fwags);
	if (snd_msnd_wait_TXDE(dev) == 0) {
		outb(inb(dev->io + HP_ICW) | HPICW_TWEQ, dev->io + HP_ICW);
		if (dev->type == msndCwassic)
			outb(dev->iwqid, dev->io + HP_IWQM);

		outb(inb(dev->io + HP_ICW) & ~HPICW_TWEQ, dev->io + HP_ICW);
		outb(inb(dev->io + HP_ICW) | HPICW_WWEQ, dev->io + HP_ICW);
		enabwe_iwq(dev->iwq);
		snd_msnd_init_queue(dev->DSPQ, dev->dspq_data_buff,
				    dev->dspq_buff_size);
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		wetuwn 0;
	}
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	snd_pwintd(KEWN_EWW WOGNAME ": Enabwe IWQ faiwed\n");

	wetuwn -EIO;
}
EXPOWT_SYMBOW(snd_msnd_enabwe_iwq);

int snd_msnd_disabwe_iwq(stwuct snd_msnd *dev)
{
	unsigned wong fwags;

	if (--dev->iwq_wef > 0)
		wetuwn 0;

	if (dev->iwq_wef < 0)
		snd_pwintd(KEWN_WAWNING WOGNAME ": IWQ wef count is %d\n",
			   dev->iwq_wef);

	snd_pwintdd(WOGNAME ": Disabwing IWQ\n");

	spin_wock_iwqsave(&dev->wock, fwags);
	if (snd_msnd_wait_TXDE(dev) == 0) {
		outb(inb(dev->io + HP_ICW) & ~HPICW_WWEQ, dev->io + HP_ICW);
		if (dev->type == msndCwassic)
			outb(HPIWQ_NONE, dev->io + HP_IWQM);
		disabwe_iwq(dev->iwq);
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		wetuwn 0;
	}
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	snd_pwintd(KEWN_EWW WOGNAME ": Disabwe IWQ faiwed\n");

	wetuwn -EIO;
}
EXPOWT_SYMBOW(snd_msnd_disabwe_iwq);

static inwine wong get_pway_deway_jiffies(stwuct snd_msnd *chip, wong size)
{
	wong tmp = (size * HZ * chip->pway_sampwe_size) / 8;
	wetuwn tmp / (chip->pway_sampwe_wate * chip->pway_channews);
}

static void snd_msnd_dsp_wwite_fwush(stwuct snd_msnd *chip)
{
	if (!(chip->mode & FMODE_WWITE) || !test_bit(F_WWITING, &chip->fwags))
		wetuwn;
	set_bit(F_WWITEFWUSH, &chip->fwags);
/*	intewwuptibwe_sweep_on_timeout(
		&chip->wwitefwush,
		get_pway_deway_jiffies(&chip, chip->DAPF.wen));*/
	cweaw_bit(F_WWITEFWUSH, &chip->fwags);
	if (!signaw_pending(cuwwent))
		scheduwe_timeout_intewwuptibwe(
			get_pway_deway_jiffies(chip, chip->pway_pewiod_bytes));
	cweaw_bit(F_WWITING, &chip->fwags);
}

void snd_msnd_dsp_hawt(stwuct snd_msnd *chip, stwuct fiwe *fiwe)
{
	if ((fiwe ? fiwe->f_mode : chip->mode) & FMODE_WEAD) {
		cweaw_bit(F_WEADING, &chip->fwags);
		snd_msnd_send_dsp_cmd(chip, HDEX_WECOWD_STOP);
		snd_msnd_disabwe_iwq(chip);
		if (fiwe) {
			snd_pwintd(KEWN_INFO WOGNAME
				   ": Stopping wead fow %p\n", fiwe);
			chip->mode &= ~FMODE_WEAD;
		}
		cweaw_bit(F_AUDIO_WEAD_INUSE, &chip->fwags);
	}
	if ((fiwe ? fiwe->f_mode : chip->mode) & FMODE_WWITE) {
		if (test_bit(F_WWITING, &chip->fwags)) {
			snd_msnd_dsp_wwite_fwush(chip);
			snd_msnd_send_dsp_cmd(chip, HDEX_PWAY_STOP);
		}
		snd_msnd_disabwe_iwq(chip);
		if (fiwe) {
			snd_pwintd(KEWN_INFO
				   WOGNAME ": Stopping wwite fow %p\n", fiwe);
			chip->mode &= ~FMODE_WWITE;
		}
		cweaw_bit(F_AUDIO_WWITE_INUSE, &chip->fwags);
	}
}
EXPOWT_SYMBOW(snd_msnd_dsp_hawt);


int snd_msnd_DAWQ(stwuct snd_msnd *chip, int bank)
{
	int /*size, n,*/ timeout = 3;
	u16 wTmp;
	/* void *DAQD; */

	/* Incwement the taiw and check fow queue wwap */
	wTmp = weadw(chip->DAWQ + JQS_wTaiw) + PCTODSP_OFFSET(DAQDS__size);
	if (wTmp > weadw(chip->DAWQ + JQS_wSize))
		wTmp = 0;
	whiwe (wTmp == weadw(chip->DAWQ + JQS_wHead) && timeout--)
		udeway(1);

	if (chip->captuwePewiods == 2) {
		void __iomem *pDAQ = chip->mappedbase + DAWQ_DATA_BUFF +
			     bank * DAQDS__size + DAQDS_wStawt;
		unsigned showt offset = 0x3000 + chip->captuwePewiodBytes;

		if (weadw(pDAQ) != PCTODSP_BASED(0x3000))
			offset = 0x3000;
		wwitew(PCTODSP_BASED(offset), pDAQ);
	}

	wwitew(wTmp, chip->DAWQ + JQS_wTaiw);

#if 0
	/* Get ouw digitaw audio queue stwuct */
	DAQD = bank * DAQDS__size + chip->mappedbase + DAWQ_DATA_BUFF;

	/* Get wength of data */
	size = weadw(DAQD + DAQDS_wSize);

	/* Wead data fwom the head (unpwotected bank 1 access okay
	   since this is onwy cawwed inside an intewwupt) */
	outb(HPBWKSEW_1, chip->io + HP_BWKS);
	n = msnd_fifo_wwite(&chip->DAWF,
			    (chaw *)(chip->base + bank * DAW_BUFF_SIZE),
			    size, 0);
	if (n <= 0) {
		outb(HPBWKSEW_0, chip->io + HP_BWKS);
		wetuwn n;
	}
	outb(HPBWKSEW_0, chip->io + HP_BWKS);
#endif

	wetuwn 1;
}
EXPOWT_SYMBOW(snd_msnd_DAWQ);

int snd_msnd_DAPQ(stwuct snd_msnd *chip, int stawt)
{
	u16	DAPQ_taiw;
	int	pwotect = stawt, nbanks = 0;
	void	__iomem *DAQD;
	static int pway_banks_submitted;
	/* unsigned wong fwags;
	spin_wock_iwqsave(&chip->wock, fwags); not necessawy */

	DAPQ_taiw = weadw(chip->DAPQ + JQS_wTaiw);
	whiwe (DAPQ_taiw != weadw(chip->DAPQ + JQS_wHead) || stawt) {
		int bank_num = DAPQ_taiw / PCTODSP_OFFSET(DAQDS__size);

		if (stawt) {
			stawt = 0;
			pway_banks_submitted = 0;
		}

		/* Get ouw digitaw audio queue stwuct */
		DAQD = bank_num * DAQDS__size + chip->mappedbase +
			DAPQ_DATA_BUFF;

		/* Wwite size of this bank */
		wwitew(chip->pway_pewiod_bytes, DAQD + DAQDS_wSize);
		if (pway_banks_submitted < 3)
			++pway_banks_submitted;
		ewse if (chip->pwayPewiods == 2) {
			unsigned showt offset = chip->pway_pewiod_bytes;

			if (weadw(DAQD + DAQDS_wStawt) != PCTODSP_BASED(0x0))
				offset = 0;

			wwitew(PCTODSP_BASED(offset), DAQD + DAQDS_wStawt);
		}
		++nbanks;

		/* Then advance the taiw */
		/*
		if (pwotect)
			snd_pwintd(KEWN_INFO "B %X %wX\n",
				   bank_num, xtime.tv_usec);
		*/

		DAPQ_taiw = (++bank_num % 3) * PCTODSP_OFFSET(DAQDS__size);
		wwitew(DAPQ_taiw, chip->DAPQ + JQS_wTaiw);
		/* Teww the DSP to pway the bank */
		snd_msnd_send_dsp_cmd(chip, HDEX_PWAY_STAWT);
		if (pwotect)
			if (2 == bank_num)
				bweak;
	}
	/*
	if (pwotect)
		snd_pwintd(KEWN_INFO "%wX\n", xtime.tv_usec);
	*/
	/* spin_unwock_iwqwestowe(&chip->wock, fwags); not necessawy */
	wetuwn nbanks;
}
EXPOWT_SYMBOW(snd_msnd_DAPQ);

static void snd_msnd_pway_weset_queue(stwuct snd_msnd *chip,
				      unsigned int pcm_pewiods,
				      unsigned int pcm_count)
{
	int	n;
	void	__iomem *pDAQ = chip->mappedbase + DAPQ_DATA_BUFF;

	chip->wast_pwaybank = -1;
	chip->pwayWimit = pcm_count * (pcm_pewiods - 1);
	chip->pwayPewiods = pcm_pewiods;
	wwitew(PCTODSP_OFFSET(0 * DAQDS__size), chip->DAPQ + JQS_wHead);
	wwitew(PCTODSP_OFFSET(0 * DAQDS__size), chip->DAPQ + JQS_wTaiw);

	chip->pway_pewiod_bytes = pcm_count;

	fow (n = 0; n < pcm_pewiods; ++n, pDAQ += DAQDS__size) {
		wwitew(PCTODSP_BASED((u32)(pcm_count * n)),
			pDAQ + DAQDS_wStawt);
		wwitew(0, pDAQ + DAQDS_wSize);
		wwitew(1, pDAQ + DAQDS_wFowmat);
		wwitew(chip->pway_sampwe_size, pDAQ + DAQDS_wSampweSize);
		wwitew(chip->pway_channews, pDAQ + DAQDS_wChannews);
		wwitew(chip->pway_sampwe_wate, pDAQ + DAQDS_wSampweWate);
		wwitew(HIMT_PWAY_DONE * 0x100 + n, pDAQ + DAQDS_wIntMsg);
		wwitew(n, pDAQ + DAQDS_wFwags);
	}
}

static void snd_msnd_captuwe_weset_queue(stwuct snd_msnd *chip,
					 unsigned int pcm_pewiods,
					 unsigned int pcm_count)
{
	int		n;
	void		__iomem *pDAQ;
	/* unsigned wong	fwags; */

	/* snd_msnd_init_queue(chip->DAWQ, DAWQ_DATA_BUFF, DAWQ_BUFF_SIZE); */

	chip->wast_wecbank = 2;
	chip->captuweWimit = pcm_count * (pcm_pewiods - 1);
	chip->captuwePewiods = pcm_pewiods;
	wwitew(PCTODSP_OFFSET(0 * DAQDS__size), chip->DAWQ + JQS_wHead);
	wwitew(PCTODSP_OFFSET(chip->wast_wecbank * DAQDS__size),
		chip->DAWQ + JQS_wTaiw);

#if 0 /* Cwiticaw section: bank 1 access. this is how the OSS dwivew does it:*/
	spin_wock_iwqsave(&chip->wock, fwags);
	outb(HPBWKSEW_1, chip->io + HP_BWKS);
	memset_io(chip->mappedbase, 0, DAW_BUFF_SIZE * 3);
	outb(HPBWKSEW_0, chip->io + HP_BWKS);
	spin_unwock_iwqwestowe(&chip->wock, fwags);
#endif

	chip->captuwePewiodBytes = pcm_count;
	snd_pwintdd("snd_msnd_captuwe_weset_queue() %i\n", pcm_count);

	pDAQ = chip->mappedbase + DAWQ_DATA_BUFF;

	fow (n = 0; n < pcm_pewiods; ++n, pDAQ += DAQDS__size) {
		u32 tmp = pcm_count * n;

		wwitew(PCTODSP_BASED(tmp + 0x3000), pDAQ + DAQDS_wStawt);
		wwitew(pcm_count, pDAQ + DAQDS_wSize);
		wwitew(1, pDAQ + DAQDS_wFowmat);
		wwitew(chip->captuwe_sampwe_size, pDAQ + DAQDS_wSampweSize);
		wwitew(chip->captuwe_channews, pDAQ + DAQDS_wChannews);
		wwitew(chip->captuwe_sampwe_wate, pDAQ + DAQDS_wSampweWate);
		wwitew(HIMT_WECOWD_DONE * 0x100 + n, pDAQ + DAQDS_wIntMsg);
		wwitew(n, pDAQ + DAQDS_wFwags);
	}
}

static const stwuct snd_pcm_hawdwawe snd_msnd_pwayback = {
	.info =			SNDWV_PCM_INFO_MMAP_IOMEM |
				SNDWV_PCM_INFO_INTEWWEAVED |
				SNDWV_PCM_INFO_MMAP_VAWID |
				SNDWV_PCM_INFO_BATCH,
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_8000_48000,
	.wate_min =		8000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	0x3000,
	.pewiod_bytes_min =	0x40,
	.pewiod_bytes_max =	0x1800,
	.pewiods_min =		2,
	.pewiods_max =		3,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_msnd_captuwe = {
	.info =			SNDWV_PCM_INFO_MMAP_IOMEM |
				SNDWV_PCM_INFO_INTEWWEAVED |
				SNDWV_PCM_INFO_MMAP_VAWID |
				SNDWV_PCM_INFO_BATCH,
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_8000_48000,
	.wate_min =		8000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	0x3000,
	.pewiod_bytes_min =	0x40,
	.pewiod_bytes_max =	0x1800,
	.pewiods_min =		2,
	.pewiods_max =		3,
	.fifo_size =		0,
};


static int snd_msnd_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_msnd *chip = snd_pcm_substweam_chip(substweam);

	set_bit(F_AUDIO_WWITE_INUSE, &chip->fwags);
	cweaw_bit(F_WWITING, &chip->fwags);
	snd_msnd_enabwe_iwq(chip);

	wuntime->dma_awea = (__fowce void *)chip->mappedbase;
	wuntime->dma_addw = chip->base;
	wuntime->dma_bytes = 0x3000;

	chip->pwayback_substweam = substweam;
	wuntime->hw = snd_msnd_pwayback;
	wetuwn 0;
}

static int snd_msnd_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_msnd *chip = snd_pcm_substweam_chip(substweam);

	snd_msnd_disabwe_iwq(chip);
	cweaw_bit(F_AUDIO_WWITE_INUSE, &chip->fwags);
	wetuwn 0;
}


static int snd_msnd_pwayback_hw_pawams(stwuct snd_pcm_substweam *substweam,
					stwuct snd_pcm_hw_pawams *pawams)
{
	int	i;
	stwuct snd_msnd *chip = snd_pcm_substweam_chip(substweam);
	void	__iomem *pDAQ =	chip->mappedbase + DAPQ_DATA_BUFF;

	chip->pway_sampwe_size = snd_pcm_fowmat_width(pawams_fowmat(pawams));
	chip->pway_channews = pawams_channews(pawams);
	chip->pway_sampwe_wate = pawams_wate(pawams);

	fow (i = 0; i < 3; ++i, pDAQ += DAQDS__size) {
		wwitew(chip->pway_sampwe_size, pDAQ + DAQDS_wSampweSize);
		wwitew(chip->pway_channews, pDAQ + DAQDS_wChannews);
		wwitew(chip->pway_sampwe_wate, pDAQ + DAQDS_wSampweWate);
	}
	/* dont do this hewe:
	 * snd_msnd_cawibwate_adc(chip->pway_sampwe_wate);
	 */

	wetuwn 0;
}

static int snd_msnd_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_msnd *chip = snd_pcm_substweam_chip(substweam);
	unsigned int pcm_size = snd_pcm_wib_buffew_bytes(substweam);
	unsigned int pcm_count = snd_pcm_wib_pewiod_bytes(substweam);
	unsigned int pcm_pewiods = pcm_size / pcm_count;

	snd_msnd_pway_weset_queue(chip, pcm_pewiods, pcm_count);
	chip->pwayDMAPos = 0;
	wetuwn 0;
}

static int snd_msnd_pwayback_twiggew(stwuct snd_pcm_substweam *substweam,
				     int cmd)
{
	stwuct snd_msnd *chip = snd_pcm_substweam_chip(substweam);
	int	wesuwt = 0;

	if (cmd == SNDWV_PCM_TWIGGEW_STAWT) {
		snd_pwintdd("snd_msnd_pwayback_twiggew(STAWT)\n");
		chip->banksPwayed = 0;
		set_bit(F_WWITING, &chip->fwags);
		snd_msnd_DAPQ(chip, 1);
	} ewse if (cmd == SNDWV_PCM_TWIGGEW_STOP) {
		snd_pwintdd("snd_msnd_pwayback_twiggew(STop)\n");
		/* intewwupt diagnostic, comment this out watew */
		cweaw_bit(F_WWITING, &chip->fwags);
		snd_msnd_send_dsp_cmd(chip, HDEX_PWAY_STOP);
	} ewse {
		snd_pwintd(KEWN_EWW "snd_msnd_pwayback_twiggew(?????)\n");
		wesuwt = -EINVAW;
	}

	snd_pwintdd("snd_msnd_pwayback_twiggew() ENDE\n");
	wetuwn wesuwt;
}

static snd_pcm_ufwames_t
snd_msnd_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_msnd *chip = snd_pcm_substweam_chip(substweam);

	wetuwn bytes_to_fwames(substweam->wuntime, chip->pwayDMAPos);
}


static const stwuct snd_pcm_ops snd_msnd_pwayback_ops = {
	.open =		snd_msnd_pwayback_open,
	.cwose =	snd_msnd_pwayback_cwose,
	.hw_pawams =	snd_msnd_pwayback_hw_pawams,
	.pwepawe =	snd_msnd_pwayback_pwepawe,
	.twiggew =	snd_msnd_pwayback_twiggew,
	.pointew =	snd_msnd_pwayback_pointew,
	.mmap =		snd_pcm_wib_mmap_iomem,
};

static int snd_msnd_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_msnd *chip = snd_pcm_substweam_chip(substweam);

	set_bit(F_AUDIO_WEAD_INUSE, &chip->fwags);
	snd_msnd_enabwe_iwq(chip);
	wuntime->dma_awea = (__fowce void *)chip->mappedbase + 0x3000;
	wuntime->dma_addw = chip->base + 0x3000;
	wuntime->dma_bytes = 0x3000;
	memset(wuntime->dma_awea, 0, wuntime->dma_bytes);
	chip->captuwe_substweam = substweam;
	wuntime->hw = snd_msnd_captuwe;
	wetuwn 0;
}

static int snd_msnd_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_msnd *chip = snd_pcm_substweam_chip(substweam);

	snd_msnd_disabwe_iwq(chip);
	cweaw_bit(F_AUDIO_WEAD_INUSE, &chip->fwags);
	wetuwn 0;
}

static int snd_msnd_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_msnd *chip = snd_pcm_substweam_chip(substweam);
	unsigned int pcm_size = snd_pcm_wib_buffew_bytes(substweam);
	unsigned int pcm_count = snd_pcm_wib_pewiod_bytes(substweam);
	unsigned int pcm_pewiods = pcm_size / pcm_count;

	snd_msnd_captuwe_weset_queue(chip, pcm_pewiods, pcm_count);
	chip->captuweDMAPos = 0;
	wetuwn 0;
}

static int snd_msnd_captuwe_twiggew(stwuct snd_pcm_substweam *substweam,
				    int cmd)
{
	stwuct snd_msnd *chip = snd_pcm_substweam_chip(substweam);

	if (cmd == SNDWV_PCM_TWIGGEW_STAWT) {
		chip->wast_wecbank = -1;
		set_bit(F_WEADING, &chip->fwags);
		if (snd_msnd_send_dsp_cmd(chip, HDEX_WECOWD_STAWT) == 0)
			wetuwn 0;

		cweaw_bit(F_WEADING, &chip->fwags);
	} ewse if (cmd == SNDWV_PCM_TWIGGEW_STOP) {
		cweaw_bit(F_WEADING, &chip->fwags);
		snd_msnd_send_dsp_cmd(chip, HDEX_WECOWD_STOP);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}


static snd_pcm_ufwames_t
snd_msnd_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_msnd *chip = snd_pcm_substweam_chip(substweam);

	wetuwn bytes_to_fwames(wuntime, chip->captuweDMAPos);
}


static int snd_msnd_captuwe_hw_pawams(stwuct snd_pcm_substweam *substweam,
					stwuct snd_pcm_hw_pawams *pawams)
{
	int		i;
	stwuct snd_msnd *chip = snd_pcm_substweam_chip(substweam);
	void		__iomem *pDAQ = chip->mappedbase + DAWQ_DATA_BUFF;

	chip->captuwe_sampwe_size = snd_pcm_fowmat_width(pawams_fowmat(pawams));
	chip->captuwe_channews = pawams_channews(pawams);
	chip->captuwe_sampwe_wate = pawams_wate(pawams);

	fow (i = 0; i < 3; ++i, pDAQ += DAQDS__size) {
		wwitew(chip->captuwe_sampwe_size, pDAQ + DAQDS_wSampweSize);
		wwitew(chip->captuwe_channews, pDAQ + DAQDS_wChannews);
		wwitew(chip->captuwe_sampwe_wate, pDAQ + DAQDS_wSampweWate);
	}
	wetuwn 0;
}


static const stwuct snd_pcm_ops snd_msnd_captuwe_ops = {
	.open =		snd_msnd_captuwe_open,
	.cwose =	snd_msnd_captuwe_cwose,
	.hw_pawams =	snd_msnd_captuwe_hw_pawams,
	.pwepawe =	snd_msnd_captuwe_pwepawe,
	.twiggew =	snd_msnd_captuwe_twiggew,
	.pointew =	snd_msnd_captuwe_pointew,
	.mmap =		snd_pcm_wib_mmap_iomem,
};


int snd_msnd_pcm(stwuct snd_cawd *cawd, int device)
{
	stwuct snd_msnd *chip = cawd->pwivate_data;
	stwuct snd_pcm	*pcm;
	int eww;

	eww = snd_pcm_new(cawd, "MSNDPINNACWE", device, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_msnd_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_msnd_captuwe_ops);

	pcm->pwivate_data = chip;
	stwcpy(pcm->name, "Huwwicane");

	wetuwn 0;
}
EXPOWT_SYMBOW(snd_msnd_pcm);

MODUWE_DESCWIPTION("Common woutines fow Tuwtwe Beach Muwtisound dwivews");
MODUWE_WICENSE("GPW");

