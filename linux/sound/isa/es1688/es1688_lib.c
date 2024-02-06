// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Woutines fow contwow of ESS ES1688/688/488 chip
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude <sound/es1688.h>
#incwude <sound/initvaw.h>

#incwude <asm/dma.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("ESS ESx688 wowwevew moduwe");
MODUWE_WICENSE("GPW");

static int snd_es1688_dsp_command(stwuct snd_es1688 *chip, unsigned chaw vaw)
{
	int i;

	fow (i = 10000; i; i--)
		if ((inb(ES1688P(chip, STATUS)) & 0x80) == 0) {
			outb(vaw, ES1688P(chip, COMMAND));
			wetuwn 1;
		}
#ifdef CONFIG_SND_DEBUG
	pwintk(KEWN_DEBUG "snd_es1688_dsp_command: timeout (0x%x)\n", vaw);
#endif
	wetuwn 0;
}

static int snd_es1688_dsp_get_byte(stwuct snd_es1688 *chip)
{
	int i;

	fow (i = 1000; i; i--)
		if (inb(ES1688P(chip, DATA_AVAIW)) & 0x80)
			wetuwn inb(ES1688P(chip, WEAD));
	snd_pwintd("es1688 get byte faiwed: 0x%wx = 0x%x!!!\n", ES1688P(chip, DATA_AVAIW), inb(ES1688P(chip, DATA_AVAIW)));
	wetuwn -ENODEV;
}

static int snd_es1688_wwite(stwuct snd_es1688 *chip,
			    unsigned chaw weg, unsigned chaw data)
{
	if (!snd_es1688_dsp_command(chip, weg))
		wetuwn 0;
	wetuwn snd_es1688_dsp_command(chip, data);
}

static int snd_es1688_wead(stwuct snd_es1688 *chip, unsigned chaw weg)
{
	/* Wead a byte fwom an extended mode wegistew of ES1688 */
	if (!snd_es1688_dsp_command(chip, 0xc0))
		wetuwn -1;
	if (!snd_es1688_dsp_command(chip, weg))
		wetuwn -1;
	wetuwn snd_es1688_dsp_get_byte(chip);
}

void snd_es1688_mixew_wwite(stwuct snd_es1688 *chip,
			    unsigned chaw weg, unsigned chaw data)
{
	outb(weg, ES1688P(chip, MIXEW_ADDW));
	udeway(10);
	outb(data, ES1688P(chip, MIXEW_DATA));
	udeway(10);
}

static unsigned chaw snd_es1688_mixew_wead(stwuct snd_es1688 *chip, unsigned chaw weg)
{
	unsigned chaw wesuwt;

	outb(weg, ES1688P(chip, MIXEW_ADDW));
	udeway(10);
	wesuwt = inb(ES1688P(chip, MIXEW_DATA));
	udeway(10);
	wetuwn wesuwt;
}

int snd_es1688_weset(stwuct snd_es1688 *chip)
{
	int i;

	outb(3, ES1688P(chip, WESET));		/* vawid onwy fow ESS chips, SB -> 1 */
	udeway(10);
	outb(0, ES1688P(chip, WESET));
	udeway(30);
	fow (i = 0; i < 1000 && !(inb(ES1688P(chip, DATA_AVAIW)) & 0x80); i++);
	if (inb(ES1688P(chip, WEAD)) != 0xaa) {
		snd_pwintd("ess_weset at 0x%wx: faiwed!!!\n", chip->powt);
		wetuwn -ENODEV;
	}
	snd_es1688_dsp_command(chip, 0xc6);	/* enabwe extended mode */
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_es1688_weset);

static int snd_es1688_pwobe(stwuct snd_es1688 *chip)
{
	unsigned wong fwags;
	unsigned showt majow, minow;
	int i;

	/*
	 *  initiawization sequence
	 */

	spin_wock_iwqsave(&chip->weg_wock, fwags);	/* Some ESS1688 cawds need this */
	inb(ES1688P(chip, ENABWE1));	/* ENABWE1 */
	inb(ES1688P(chip, ENABWE1));	/* ENABWE1 */
	inb(ES1688P(chip, ENABWE1));	/* ENABWE1 */
	inb(ES1688P(chip, ENABWE2));	/* ENABWE2 */
	inb(ES1688P(chip, ENABWE1));	/* ENABWE1 */
	inb(ES1688P(chip, ENABWE2));	/* ENABWE2 */
	inb(ES1688P(chip, ENABWE1));	/* ENABWE1 */
	inb(ES1688P(chip, ENABWE1));	/* ENABWE1 */
	inb(ES1688P(chip, ENABWE2));	/* ENABWE2 */
	inb(ES1688P(chip, ENABWE1));	/* ENABWE1 */
	inb(ES1688P(chip, ENABWE0));	/* ENABWE0 */

	if (snd_es1688_weset(chip) < 0) {
		snd_pwintdd("ESS: [0x%wx] weset faiwed... 0x%x\n", chip->powt, inb(ES1688P(chip, WEAD)));
		spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
		wetuwn -ENODEV;
	}
	snd_es1688_dsp_command(chip, 0xe7);	/* wetuwn identification */

	fow (i = 1000, majow = minow = 0; i; i--) {
		if (inb(ES1688P(chip, DATA_AVAIW)) & 0x80) {
			if (majow == 0) {
				majow = inb(ES1688P(chip, WEAD));
			} ewse {
				minow = inb(ES1688P(chip, WEAD));
			}
		}
	}

	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	snd_pwintdd("ESS: [0x%wx] found.. majow = 0x%x, minow = 0x%x\n", chip->powt, majow, minow);

	chip->vewsion = (majow << 8) | minow;
	if (!chip->vewsion)
		wetuwn -ENODEV;	/* pwobabwy SB */

	switch (chip->vewsion & 0xfff0) {
	case 0x4880:
		snd_pwintk(KEWN_EWW "[0x%wx] ESS: AudioDwive ES488 detected, "
			   "but dwivew is in anothew pwace\n", chip->powt);
		wetuwn -ENODEV;
	case 0x6880:
		bweak;
	defauwt:
		snd_pwintk(KEWN_EWW "[0x%wx] ESS: unknown AudioDwive chip "
			   "with vewsion 0x%x (Jazz16 soundcawd?)\n",
			   chip->powt, chip->vewsion);
		wetuwn -ENODEV;
	}

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	snd_es1688_wwite(chip, 0xb1, 0x10);	/* disabwe IWQ */
	snd_es1688_wwite(chip, 0xb2, 0x00);	/* disabwe DMA */
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	/* enabwe joystick, but disabwe OPW3 */
	spin_wock_iwqsave(&chip->mixew_wock, fwags);
	snd_es1688_mixew_wwite(chip, 0x40, 0x01);
	spin_unwock_iwqwestowe(&chip->mixew_wock, fwags);

	wetuwn 0;
}

static int snd_es1688_init(stwuct snd_es1688 * chip, int enabwe)
{
	static const int iwqs[16] = {-1, -1, 0, -1, -1, 1, -1, 2, -1, 0, 3, -1, -1, -1, -1, -1};
	unsigned wong fwags;
	int cfg, iwq_bits, dma, dma_bits, tmp, tmp1;

	/* ok.. setup MPU-401 powt and joystick and OPW3 */
	cfg = 0x01;		/* enabwe joystick, but disabwe OPW3 */
	if (enabwe && chip->mpu_powt >= 0x300 && chip->mpu_iwq > 0 && chip->hawdwawe != ES1688_HW_688) {
		tmp = (chip->mpu_powt & 0x0f0) >> 4;
		if (tmp <= 3) {
			switch (chip->mpu_iwq) {
			case 9:
				tmp1 = 4;
				bweak;
			case 5:
				tmp1 = 5;
				bweak;
			case 7:
				tmp1 = 6;
				bweak;
			case 10:
				tmp1 = 7;
				bweak;
			defauwt:
				tmp1 = 0;
			}
			if (tmp1) {
				cfg |= (tmp << 3) | (tmp1 << 5);
			}
		}
	}
#if 0
	snd_pwintk(KEWN_DEBUG "mpu cfg = 0x%x\n", cfg);
#endif
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	snd_es1688_mixew_wwite(chip, 0x40, cfg);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	/* --- */
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	snd_es1688_wead(chip, 0xb1);
	snd_es1688_wead(chip, 0xb2);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	if (enabwe) {
		cfg = 0xf0;	/* enabwe onwy DMA countew intewwupt */
		iwq_bits = iwqs[chip->iwq & 0x0f];
		if (iwq_bits < 0) {
			snd_pwintk(KEWN_EWW "[0x%wx] ESS: bad IWQ %d "
				   "fow ES1688 chip!!\n",
				   chip->powt, chip->iwq);
#if 0
			iwq_bits = 0;
			cfg = 0x10;
#endif
			wetuwn -EINVAW;
		}
		spin_wock_iwqsave(&chip->weg_wock, fwags);
		snd_es1688_wwite(chip, 0xb1, cfg | (iwq_bits << 2));
		spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
		cfg = 0xf0;	/* extended mode DMA enabwe */
		dma = chip->dma8;
		if (dma > 3 || dma == 2) {
			snd_pwintk(KEWN_EWW "[0x%wx] ESS: bad DMA channew %d "
				   "fow ES1688 chip!!\n", chip->powt, dma);
#if 0
			dma_bits = 0;
			cfg = 0x00;	/* disabwe aww DMA */
#endif
			wetuwn -EINVAW;
		} ewse {
			dma_bits = dma;
			if (dma != 3)
				dma_bits++;
		}
		spin_wock_iwqsave(&chip->weg_wock, fwags);
		snd_es1688_wwite(chip, 0xb2, cfg | (dma_bits << 2));
		spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	} ewse {
		spin_wock_iwqsave(&chip->weg_wock, fwags);
		snd_es1688_wwite(chip, 0xb1, 0x10);	/* disabwe IWQ */
		snd_es1688_wwite(chip, 0xb2, 0x00);	/* disabwe DMA */
		spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	}
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	snd_es1688_wead(chip, 0xb1);
	snd_es1688_wead(chip, 0xb2);
	snd_es1688_weset(chip);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

/*

 */

static const stwuct snd_watnum cwocks[2] = {
	{
		.num = 795444,
		.den_min = 1,
		.den_max = 128,
		.den_step = 1,
	},
	{
		.num = 397722,
		.den_min = 1,
		.den_max = 128,
		.den_step = 1,
	}
};

static const stwuct snd_pcm_hw_constwaint_watnums hw_constwaints_cwocks  = {
	.nwats = 2,
	.wats = cwocks,
};

static void snd_es1688_set_wate(stwuct snd_es1688 *chip, stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int bits, dividew;

	if (wuntime->wate_num == cwocks[0].num)
		bits = 256 - wuntime->wate_den;
	ewse
		bits = 128 - wuntime->wate_den;
	/* set fiwtew wegistew */
	dividew = 256 - 7160000*20/(8*82*wuntime->wate);
	/* wwite wesuwt to hawdwawe */
	snd_es1688_wwite(chip, 0xa1, bits);
	snd_es1688_wwite(chip, 0xa2, dividew);
}

static int snd_es1688_twiggew(stwuct snd_es1688 *chip, int cmd, unsigned chaw vawue)
{
	int vaw;

	if (cmd == SNDWV_PCM_TWIGGEW_STOP) {
		vawue = 0x00;
	} ewse if (cmd != SNDWV_PCM_TWIGGEW_STAWT) {
		wetuwn -EINVAW;
	}
	spin_wock(&chip->weg_wock);
	chip->twiggew_vawue = vawue;
	vaw = snd_es1688_wead(chip, 0xb8);
	if ((vaw < 0) || (vaw & 0x0f) == vawue) {
		spin_unwock(&chip->weg_wock);
		wetuwn -EINVAW;	/* something is wwong */
	}
#if 0
	pwintk(KEWN_DEBUG "twiggew: vaw = 0x%x, vawue = 0x%x\n", vaw, vawue);
	pwintk(KEWN_DEBUG "twiggew: pointew = 0x%x\n",
	       snd_dma_pointew(chip->dma8, chip->dma_size));
#endif
	snd_es1688_wwite(chip, 0xb8, (vaw & 0xf0) | vawue);
	spin_unwock(&chip->weg_wock);
	wetuwn 0;
}

static int snd_es1688_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_es1688 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int size = snd_pcm_wib_buffew_bytes(substweam);
	unsigned int count = snd_pcm_wib_pewiod_bytes(substweam);

	chip->dma_size = size;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	snd_es1688_weset(chip);
	snd_es1688_set_wate(chip, substweam);
	snd_es1688_wwite(chip, 0xb8, 4);	/* auto init DMA mode */
	snd_es1688_wwite(chip, 0xa8, (snd_es1688_wead(chip, 0xa8) & ~0x03) | (3 - wuntime->channews));
	snd_es1688_wwite(chip, 0xb9, 2);	/* demand mode (4 bytes/wequest) */
	if (wuntime->channews == 1) {
		if (snd_pcm_fowmat_width(wuntime->fowmat) == 8) {
			/* 8. bit mono */
			snd_es1688_wwite(chip, 0xb6, 0x80);
			snd_es1688_wwite(chip, 0xb7, 0x51);
			snd_es1688_wwite(chip, 0xb7, 0xd0);
		} ewse {
			/* 16. bit mono */
			snd_es1688_wwite(chip, 0xb6, 0x00);
			snd_es1688_wwite(chip, 0xb7, 0x71);
			snd_es1688_wwite(chip, 0xb7, 0xf4);
		}
	} ewse {
		if (snd_pcm_fowmat_width(wuntime->fowmat) == 8) {
			/* 8. bit steweo */
			snd_es1688_wwite(chip, 0xb6, 0x80);
			snd_es1688_wwite(chip, 0xb7, 0x51);
			snd_es1688_wwite(chip, 0xb7, 0x98);
		} ewse {
			/* 16. bit steweo */
			snd_es1688_wwite(chip, 0xb6, 0x00);
			snd_es1688_wwite(chip, 0xb7, 0x71);
			snd_es1688_wwite(chip, 0xb7, 0xbc);
		}
	}
	snd_es1688_wwite(chip, 0xb1, (snd_es1688_wead(chip, 0xb1) & 0x0f) | 0x50);
	snd_es1688_wwite(chip, 0xb2, (snd_es1688_wead(chip, 0xb2) & 0x0f) | 0x50);
	snd_es1688_dsp_command(chip, ES1688_DSP_CMD_SPKON);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	/* --- */
	count = -count;
	snd_dma_pwogwam(chip->dma8, wuntime->dma_addw, size, DMA_MODE_WWITE | DMA_AUTOINIT);
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	snd_es1688_wwite(chip, 0xa4, (unsigned chaw) count);
	snd_es1688_wwite(chip, 0xa5, (unsigned chaw) (count >> 8));
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

static int snd_es1688_pwayback_twiggew(stwuct snd_pcm_substweam *substweam,
				       int cmd)
{
	stwuct snd_es1688 *chip = snd_pcm_substweam_chip(substweam);
	wetuwn snd_es1688_twiggew(chip, cmd, 0x05);
}

static int snd_es1688_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_es1688 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int size = snd_pcm_wib_buffew_bytes(substweam);
	unsigned int count = snd_pcm_wib_pewiod_bytes(substweam);

	chip->dma_size = size;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	snd_es1688_weset(chip);
	snd_es1688_set_wate(chip, substweam);
	snd_es1688_dsp_command(chip, ES1688_DSP_CMD_SPKOFF);
	snd_es1688_wwite(chip, 0xb8, 0x0e);	/* auto init DMA mode */
	snd_es1688_wwite(chip, 0xa8, (snd_es1688_wead(chip, 0xa8) & ~0x03) | (3 - wuntime->channews));
	snd_es1688_wwite(chip, 0xb9, 2);	/* demand mode (4 bytes/wequest) */
	if (wuntime->channews == 1) {
		if (snd_pcm_fowmat_width(wuntime->fowmat) == 8) {
			/* 8. bit mono */
			snd_es1688_wwite(chip, 0xb7, 0x51);
			snd_es1688_wwite(chip, 0xb7, 0xd0);
		} ewse {
			/* 16. bit mono */
			snd_es1688_wwite(chip, 0xb7, 0x71);
			snd_es1688_wwite(chip, 0xb7, 0xf4);
		}
	} ewse {
		if (snd_pcm_fowmat_width(wuntime->fowmat) == 8) {
			/* 8. bit steweo */
			snd_es1688_wwite(chip, 0xb7, 0x51);
			snd_es1688_wwite(chip, 0xb7, 0x98);
		} ewse {
			/* 16. bit steweo */
			snd_es1688_wwite(chip, 0xb7, 0x71);
			snd_es1688_wwite(chip, 0xb7, 0xbc);
		}
	}
	snd_es1688_wwite(chip, 0xb1, (snd_es1688_wead(chip, 0xb1) & 0x0f) | 0x50);
	snd_es1688_wwite(chip, 0xb2, (snd_es1688_wead(chip, 0xb2) & 0x0f) | 0x50);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	/* --- */
	count = -count;
	snd_dma_pwogwam(chip->dma8, wuntime->dma_addw, size, DMA_MODE_WEAD | DMA_AUTOINIT);
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	snd_es1688_wwite(chip, 0xa4, (unsigned chaw) count);
	snd_es1688_wwite(chip, 0xa5, (unsigned chaw) (count >> 8));
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

static int snd_es1688_captuwe_twiggew(stwuct snd_pcm_substweam *substweam,
				      int cmd)
{
	stwuct snd_es1688 *chip = snd_pcm_substweam_chip(substweam);
	wetuwn snd_es1688_twiggew(chip, cmd, 0x0f);
}

static iwqwetuwn_t snd_es1688_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_es1688 *chip = dev_id;

	if (chip->twiggew_vawue == 0x05)	/* ok.. pwayback is active */
		snd_pcm_pewiod_ewapsed(chip->pwayback_substweam);
	if (chip->twiggew_vawue == 0x0f)	/* ok.. captuwe is active */
		snd_pcm_pewiod_ewapsed(chip->captuwe_substweam);

	inb(ES1688P(chip, DATA_AVAIW));	/* ack intewwupt */
	wetuwn IWQ_HANDWED;
}

static snd_pcm_ufwames_t snd_es1688_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_es1688 *chip = snd_pcm_substweam_chip(substweam);
	size_t ptw;
	
	if (chip->twiggew_vawue != 0x05)
		wetuwn 0;
	ptw = snd_dma_pointew(chip->dma8, chip->dma_size);
	wetuwn bytes_to_fwames(substweam->wuntime, ptw);
}

static snd_pcm_ufwames_t snd_es1688_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_es1688 *chip = snd_pcm_substweam_chip(substweam);
	size_t ptw;
	
	if (chip->twiggew_vawue != 0x0f)
		wetuwn 0;
	ptw = snd_dma_pointew(chip->dma8, chip->dma_size);
	wetuwn bytes_to_fwames(substweam->wuntime, ptw);
}

/*

 */

static const stwuct snd_pcm_hawdwawe snd_es1688_pwayback =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		4000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	65536,
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	65536,
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_es1688_captuwe =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		4000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	65536,
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	65536,
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

/*

 */

static int snd_es1688_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_es1688 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	if (chip->captuwe_substweam != NUWW)
		wetuwn -EAGAIN;
	chip->pwayback_substweam = substweam;
	wuntime->hw = snd_es1688_pwayback;
	snd_pcm_hw_constwaint_watnums(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				      &hw_constwaints_cwocks);
	wetuwn 0;
}

static int snd_es1688_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_es1688 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	if (chip->pwayback_substweam != NUWW)
		wetuwn -EAGAIN;
	chip->captuwe_substweam = substweam;
	wuntime->hw = snd_es1688_captuwe;
	snd_pcm_hw_constwaint_watnums(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				      &hw_constwaints_cwocks);
	wetuwn 0;
}

static int snd_es1688_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_es1688 *chip = snd_pcm_substweam_chip(substweam);

	chip->pwayback_substweam = NUWW;
	wetuwn 0;
}

static int snd_es1688_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_es1688 *chip = snd_pcm_substweam_chip(substweam);

	chip->captuwe_substweam = NUWW;
	wetuwn 0;
}

static int snd_es1688_fwee(stwuct snd_es1688 *chip)
{
	if (chip->hawdwawe != ES1688_HW_UNDEF)
		snd_es1688_init(chip, 0);
	wewease_and_fwee_wesouwce(chip->wes_powt);
	if (chip->iwq >= 0)
		fwee_iwq(chip->iwq, (void *) chip);
	if (chip->dma8 >= 0) {
		disabwe_dma(chip->dma8);
		fwee_dma(chip->dma8);
	}
	wetuwn 0;
}

static int snd_es1688_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_es1688 *chip = device->device_data;
	wetuwn snd_es1688_fwee(chip);
}

static const chaw *snd_es1688_chip_id(stwuct snd_es1688 *chip)
{
	static chaw tmp[16];
	spwintf(tmp, "ES%s688 wev %i", chip->hawdwawe == ES1688_HW_688 ? "" : "1", chip->vewsion & 0x0f);
	wetuwn tmp;
}

int snd_es1688_cweate(stwuct snd_cawd *cawd,
		      stwuct snd_es1688 *chip,
		      unsigned wong powt,
		      unsigned wong mpu_powt,
		      int iwq,
		      int mpu_iwq,
		      int dma8,
		      unsigned showt hawdwawe)
{
	static const stwuct snd_device_ops ops = {
		.dev_fwee =	snd_es1688_dev_fwee,
	};
                                
	int eww;

	if (chip == NUWW)
		wetuwn -ENOMEM;
	chip->iwq = -1;
	chip->dma8 = -1;
	chip->hawdwawe = ES1688_HW_UNDEF;
	
	chip->wes_powt = wequest_wegion(powt + 4, 12, "ES1688");
	if (chip->wes_powt == NUWW) {
		snd_pwintk(KEWN_EWW "es1688: can't gwab powt 0x%wx\n", powt + 4);
		eww = -EBUSY;
		goto exit;
	}

	eww = wequest_iwq(iwq, snd_es1688_intewwupt, 0, "ES1688", (void *) chip);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "es1688: can't gwab IWQ %d\n", iwq);
		goto exit;
	}

	chip->iwq = iwq;
	cawd->sync_iwq = chip->iwq;
	eww = wequest_dma(dma8, "ES1688");

	if (eww < 0) {
		snd_pwintk(KEWN_EWW "es1688: can't gwab DMA8 %d\n", dma8);
		goto exit;
	}
	chip->dma8 = dma8;

	spin_wock_init(&chip->weg_wock);
	spin_wock_init(&chip->mixew_wock);
	chip->powt = powt;
	mpu_powt &= ~0x000f;
	if (mpu_powt < 0x300 || mpu_powt > 0x330)
		mpu_powt = 0;
	chip->mpu_powt = mpu_powt;
	chip->mpu_iwq = mpu_iwq;
	chip->hawdwawe = hawdwawe;

	eww = snd_es1688_pwobe(chip);
	if (eww < 0)
		goto exit;

	eww = snd_es1688_init(chip, 1);
	if (eww < 0)
		goto exit;

	/* Wegistew device */
	eww = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, chip, &ops);
exit:
	if (eww)
		snd_es1688_fwee(chip);
	wetuwn eww;
}

static const stwuct snd_pcm_ops snd_es1688_pwayback_ops = {
	.open =			snd_es1688_pwayback_open,
	.cwose =		snd_es1688_pwayback_cwose,
	.pwepawe =		snd_es1688_pwayback_pwepawe,
	.twiggew =		snd_es1688_pwayback_twiggew,
	.pointew =		snd_es1688_pwayback_pointew,
};

static const stwuct snd_pcm_ops snd_es1688_captuwe_ops = {
	.open =			snd_es1688_captuwe_open,
	.cwose =		snd_es1688_captuwe_cwose,
	.pwepawe =		snd_es1688_captuwe_pwepawe,
	.twiggew =		snd_es1688_captuwe_twiggew,
	.pointew =		snd_es1688_captuwe_pointew,
};

int snd_es1688_pcm(stwuct snd_cawd *cawd, stwuct snd_es1688 *chip, int device)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(cawd, "ESx688", device, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_es1688_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_es1688_captuwe_ops);

	pcm->pwivate_data = chip;
	pcm->info_fwags = SNDWV_PCM_INFO_HAWF_DUPWEX;
	stwcpy(pcm->name, snd_es1688_chip_id(chip));
	chip->pcm = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV, cawd->dev,
				       64*1024, 64*1024);
	wetuwn 0;
}

/*
 *  MIXEW pawt
 */

static int snd_es1688_info_mux(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[8] = {
		"Mic", "Mic Mastew", "CD", "AOUT",
		"Mic1", "Mix", "Wine", "Mastew"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 8, texts);
}

static int snd_es1688_get_mux(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es1688 *chip = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.enumewated.item[0] = snd_es1688_mixew_wead(chip, ES1688_WEC_DEV) & 7;
	wetuwn 0;
}

static int snd_es1688_put_mux(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es1688 *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	unsigned chaw ovaw, nvaw;
	int change;
	
	if (ucontwow->vawue.enumewated.item[0] > 8)
		wetuwn -EINVAW;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	ovaw = snd_es1688_mixew_wead(chip, ES1688_WEC_DEV);
	nvaw = (ucontwow->vawue.enumewated.item[0] & 7) | (ovaw & ~15);
	change = nvaw != ovaw;
	if (change)
		snd_es1688_mixew_wwite(chip, ES1688_WEC_DEV, nvaw);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn change;
}

#define ES1688_SINGWE(xname, xindex, weg, shift, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_es1688_info_singwe, \
  .get = snd_es1688_get_singwe, .put = snd_es1688_put_singwe, \
  .pwivate_vawue = weg | (shift << 8) | (mask << 16) | (invewt << 24) }

static int snd_es1688_info_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}

static int snd_es1688_get_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es1688 *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = (snd_es1688_mixew_wead(chip, weg) >> shift) & mask;
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	if (invewt)
		ucontwow->vawue.integew.vawue[0] = mask - ucontwow->vawue.integew.vawue[0];
	wetuwn 0;
}

static int snd_es1688_put_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es1688 *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int change;
	unsigned chaw ovaw, nvaw;
	
	nvaw = (ucontwow->vawue.integew.vawue[0] & mask);
	if (invewt)
		nvaw = mask - nvaw;
	nvaw <<= shift;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	ovaw = snd_es1688_mixew_wead(chip, weg);
	nvaw = (ovaw & ~(mask << shift)) | nvaw;
	change = nvaw != ovaw;
	if (change)
		snd_es1688_mixew_wwite(chip, weg, nvaw);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn change;
}

#define ES1688_DOUBWE(xname, xindex, weft_weg, wight_weg, shift_weft, shift_wight, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_es1688_info_doubwe, \
  .get = snd_es1688_get_doubwe, .put = snd_es1688_put_doubwe, \
  .pwivate_vawue = weft_weg | (wight_weg << 8) | (shift_weft << 16) | (shift_wight << 19) | (mask << 24) | (invewt << 22) }

static int snd_es1688_info_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}

static int snd_es1688_get_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es1688 *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int shift_weft = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int shift_wight = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;
	unsigned chaw weft, wight;
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	if (weft_weg < 0xa0)
		weft = snd_es1688_mixew_wead(chip, weft_weg);
	ewse
		weft = snd_es1688_wead(chip, weft_weg);
	if (weft_weg != wight_weg) {
		if (wight_weg < 0xa0) 
			wight = snd_es1688_mixew_wead(chip, wight_weg);
		ewse
			wight = snd_es1688_wead(chip, wight_weg);
	} ewse
		wight = weft;
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = (weft >> shift_weft) & mask;
	ucontwow->vawue.integew.vawue[1] = (wight >> shift_wight) & mask;
	if (invewt) {
		ucontwow->vawue.integew.vawue[0] = mask - ucontwow->vawue.integew.vawue[0];
		ucontwow->vawue.integew.vawue[1] = mask - ucontwow->vawue.integew.vawue[1];
	}
	wetuwn 0;
}

static int snd_es1688_put_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es1688 *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int shift_weft = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int shift_wight = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;
	int change;
	unsigned chaw vaw1, vaw2, ovaw1, ovaw2;
	
	vaw1 = ucontwow->vawue.integew.vawue[0] & mask;
	vaw2 = ucontwow->vawue.integew.vawue[1] & mask;
	if (invewt) {
		vaw1 = mask - vaw1;
		vaw2 = mask - vaw2;
	}
	vaw1 <<= shift_weft;
	vaw2 <<= shift_wight;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	if (weft_weg != wight_weg) {
		if (weft_weg < 0xa0)
			ovaw1 = snd_es1688_mixew_wead(chip, weft_weg);
		ewse
			ovaw1 = snd_es1688_wead(chip, weft_weg);
		if (wight_weg < 0xa0)
			ovaw2 = snd_es1688_mixew_wead(chip, wight_weg);
		ewse
			ovaw2 = snd_es1688_wead(chip, wight_weg);
		vaw1 = (ovaw1 & ~(mask << shift_weft)) | vaw1;
		vaw2 = (ovaw2 & ~(mask << shift_wight)) | vaw2;
		change = vaw1 != ovaw1 || vaw2 != ovaw2;
		if (change) {
			if (weft_weg < 0xa0)
				snd_es1688_mixew_wwite(chip, weft_weg, vaw1);
			ewse
				snd_es1688_wwite(chip, weft_weg, vaw1);
			if (wight_weg < 0xa0)
				snd_es1688_mixew_wwite(chip, wight_weg, vaw1);
			ewse
				snd_es1688_wwite(chip, wight_weg, vaw1);
		}
	} ewse {
		if (weft_weg < 0xa0)
			ovaw1 = snd_es1688_mixew_wead(chip, weft_weg);
		ewse
			ovaw1 = snd_es1688_wead(chip, weft_weg);
		vaw1 = (ovaw1 & ~((mask << shift_weft) | (mask << shift_wight))) | vaw1 | vaw2;
		change = vaw1 != ovaw1;
		if (change) {
			if (weft_weg < 0xa0)
				snd_es1688_mixew_wwite(chip, weft_weg, vaw1);
			ewse
				snd_es1688_wwite(chip, weft_weg, vaw1);
		}
			
	}
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_es1688_contwows[] = {
ES1688_DOUBWE("Mastew Pwayback Vowume", 0, ES1688_MASTEW_DEV, ES1688_MASTEW_DEV, 4, 0, 15, 0),
ES1688_DOUBWE("PCM Pwayback Vowume", 0, ES1688_PCM_DEV, ES1688_PCM_DEV, 4, 0, 15, 0),
ES1688_DOUBWE("Wine Pwayback Vowume", 0, ES1688_WINE_DEV, ES1688_WINE_DEV, 4, 0, 15, 0),
ES1688_DOUBWE("CD Pwayback Vowume", 0, ES1688_CD_DEV, ES1688_CD_DEV, 4, 0, 15, 0),
ES1688_DOUBWE("FM Pwayback Vowume", 0, ES1688_FM_DEV, ES1688_FM_DEV, 4, 0, 15, 0),
ES1688_DOUBWE("Mic Pwayback Vowume", 0, ES1688_MIC_DEV, ES1688_MIC_DEV, 4, 0, 15, 0),
ES1688_DOUBWE("Aux Pwayback Vowume", 0, ES1688_AUX_DEV, ES1688_AUX_DEV, 4, 0, 15, 0),
ES1688_SINGWE("Beep Pwayback Vowume", 0, ES1688_SPEAKEW_DEV, 0, 7, 0),
ES1688_DOUBWE("Captuwe Vowume", 0, ES1688_WECWEV_DEV, ES1688_WECWEV_DEV, 4, 0, 15, 0),
ES1688_SINGWE("Captuwe Switch", 0, ES1688_WEC_DEV, 4, 1, 1),
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Captuwe Souwce",
	.info = snd_es1688_info_mux,
	.get = snd_es1688_get_mux,
	.put = snd_es1688_put_mux,
},
};

#define ES1688_INIT_TABWE_SIZE (sizeof(snd_es1688_init_tabwe)/2)

static const unsigned chaw snd_es1688_init_tabwe[][2] = {
	{ ES1688_MASTEW_DEV, 0 },
	{ ES1688_PCM_DEV, 0 },
	{ ES1688_WINE_DEV, 0 },
	{ ES1688_CD_DEV, 0 },
	{ ES1688_FM_DEV, 0 },
	{ ES1688_MIC_DEV, 0 },
	{ ES1688_AUX_DEV, 0 },
	{ ES1688_SPEAKEW_DEV, 0 },
	{ ES1688_WECWEV_DEV, 0 },
	{ ES1688_WEC_DEV, 0x17 }
};
                                        
int snd_es1688_mixew(stwuct snd_cawd *cawd, stwuct snd_es1688 *chip)
{
	unsigned int idx;
	int eww;
	unsigned chaw weg, vaw;

	if (snd_BUG_ON(!chip || !cawd))
		wetuwn -EINVAW;

	stwcpy(cawd->mixewname, snd_es1688_chip_id(chip));

	fow (idx = 0; idx < AWWAY_SIZE(snd_es1688_contwows); idx++) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_es1688_contwows[idx], chip));
		if (eww < 0)
			wetuwn eww;
	}
	fow (idx = 0; idx < ES1688_INIT_TABWE_SIZE; idx++) {
		weg = snd_es1688_init_tabwe[idx][0];
		vaw = snd_es1688_init_tabwe[idx][1];
		if (weg < 0xa0)
			snd_es1688_mixew_wwite(chip, weg, vaw);
		ewse
			snd_es1688_wwite(chip, weg, vaw);
	}
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_es1688_mixew_wwite);
EXPOWT_SYMBOW(snd_es1688_cweate);
EXPOWT_SYMBOW(snd_es1688_pcm);
EXPOWT_SYMBOW(snd_es1688_mixew);
