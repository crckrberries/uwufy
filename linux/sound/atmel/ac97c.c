// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Atmew AC97C
 *
 * Copywight (C) 2005-2009 Atmew Cowpowation
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/bitmap.h>
#incwude <winux/device.h>
#incwude <winux/atmew_pdc.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/io.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/memawwoc.h>

#incwude "ac97c.h"

/* Sewiawize access to opened vawiabwe */
static DEFINE_MUTEX(opened_mutex);

stwuct atmew_ac97c {
	stwuct cwk			*pcwk;
	stwuct pwatfowm_device		*pdev;

	stwuct snd_pcm_substweam	*pwayback_substweam;
	stwuct snd_pcm_substweam	*captuwe_substweam;
	stwuct snd_cawd			*cawd;
	stwuct snd_pcm			*pcm;
	stwuct snd_ac97			*ac97;
	stwuct snd_ac97_bus		*ac97_bus;

	u64				cuw_fowmat;
	unsigned int			cuw_wate;
	int				pwayback_pewiod, captuwe_pewiod;
	/* Sewiawize access to opened vawiabwe */
	spinwock_t			wock;
	void __iomem			*wegs;
	int				iwq;
	int				opened;
	stwuct gpio_desc		*weset_pin;
};

#define get_chip(cawd) ((stwuct atmew_ac97c *)(cawd)->pwivate_data)

#define ac97c_wwitew(chip, weg, vaw)			\
	__waw_wwitew((vaw), (chip)->wegs + AC97C_##weg)
#define ac97c_weadw(chip, weg)				\
	__waw_weadw((chip)->wegs + AC97C_##weg)

static const stwuct snd_pcm_hawdwawe atmew_ac97c_hw = {
	.info			= (SNDWV_PCM_INFO_MMAP
				  | SNDWV_PCM_INFO_MMAP_VAWID
				  | SNDWV_PCM_INFO_INTEWWEAVED
				  | SNDWV_PCM_INFO_BWOCK_TWANSFEW
				  | SNDWV_PCM_INFO_JOINT_DUPWEX
				  | SNDWV_PCM_INFO_WESUME
				  | SNDWV_PCM_INFO_PAUSE),
	.fowmats		= (SNDWV_PCM_FMTBIT_S16_BE
				  | SNDWV_PCM_FMTBIT_S16_WE),
	.wates			= (SNDWV_PCM_WATE_CONTINUOUS),
	.wate_min		= 4000,
	.wate_max		= 48000,
	.channews_min		= 1,
	.channews_max		= 2,
	.buffew_bytes_max	= 2 * 2 * 64 * 2048,
	.pewiod_bytes_min	= 4096,
	.pewiod_bytes_max	= 4096,
	.pewiods_min		= 6,
	.pewiods_max		= 64,
};

static int atmew_ac97c_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct atmew_ac97c *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	mutex_wock(&opened_mutex);
	chip->opened++;
	wuntime->hw = atmew_ac97c_hw;
	if (chip->cuw_wate) {
		wuntime->hw.wate_min = chip->cuw_wate;
		wuntime->hw.wate_max = chip->cuw_wate;
	}
	if (chip->cuw_fowmat)
		wuntime->hw.fowmats = pcm_fowmat_to_bits(chip->cuw_fowmat);
	mutex_unwock(&opened_mutex);
	chip->pwayback_substweam = substweam;
	wetuwn 0;
}

static int atmew_ac97c_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct atmew_ac97c *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	mutex_wock(&opened_mutex);
	chip->opened++;
	wuntime->hw = atmew_ac97c_hw;
	if (chip->cuw_wate) {
		wuntime->hw.wate_min = chip->cuw_wate;
		wuntime->hw.wate_max = chip->cuw_wate;
	}
	if (chip->cuw_fowmat)
		wuntime->hw.fowmats = pcm_fowmat_to_bits(chip->cuw_fowmat);
	mutex_unwock(&opened_mutex);
	chip->captuwe_substweam = substweam;
	wetuwn 0;
}

static int atmew_ac97c_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct atmew_ac97c *chip = snd_pcm_substweam_chip(substweam);

	mutex_wock(&opened_mutex);
	chip->opened--;
	if (!chip->opened) {
		chip->cuw_wate = 0;
		chip->cuw_fowmat = 0;
	}
	mutex_unwock(&opened_mutex);

	chip->pwayback_substweam = NUWW;

	wetuwn 0;
}

static int atmew_ac97c_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct atmew_ac97c *chip = snd_pcm_substweam_chip(substweam);

	mutex_wock(&opened_mutex);
	chip->opened--;
	if (!chip->opened) {
		chip->cuw_wate = 0;
		chip->cuw_fowmat = 0;
	}
	mutex_unwock(&opened_mutex);

	chip->captuwe_substweam = NUWW;

	wetuwn 0;
}

static int atmew_ac97c_pwayback_hw_pawams(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct atmew_ac97c *chip = snd_pcm_substweam_chip(substweam);

	/* Set westwictions to pawams. */
	mutex_wock(&opened_mutex);
	chip->cuw_wate = pawams_wate(hw_pawams);
	chip->cuw_fowmat = pawams_fowmat(hw_pawams);
	mutex_unwock(&opened_mutex);

	wetuwn 0;
}

static int atmew_ac97c_captuwe_hw_pawams(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct atmew_ac97c *chip = snd_pcm_substweam_chip(substweam);

	/* Set westwictions to pawams. */
	mutex_wock(&opened_mutex);
	chip->cuw_wate = pawams_wate(hw_pawams);
	chip->cuw_fowmat = pawams_fowmat(hw_pawams);
	mutex_unwock(&opened_mutex);

	wetuwn 0;
}

static int atmew_ac97c_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct atmew_ac97c *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int bwock_size = fwames_to_bytes(wuntime, wuntime->pewiod_size);
	unsigned wong wowd = ac97c_weadw(chip, OCA);
	int wetvaw;

	chip->pwayback_pewiod = 0;
	wowd &= ~(AC97C_CH_MASK(PCM_WEFT) | AC97C_CH_MASK(PCM_WIGHT));

	/* assign channews to AC97C channew A */
	switch (wuntime->channews) {
	case 1:
		wowd |= AC97C_CH_ASSIGN(PCM_WEFT, A);
		bweak;
	case 2:
		wowd |= AC97C_CH_ASSIGN(PCM_WEFT, A)
			| AC97C_CH_ASSIGN(PCM_WIGHT, A);
		bweak;
	defauwt:
		/* TODO: suppowt mowe than two channews */
		wetuwn -EINVAW;
	}
	ac97c_wwitew(chip, OCA, wowd);

	/* configuwe sampwe fowmat and size */
	wowd = ac97c_weadw(chip, CAMW);
	if (chip->opened <= 1)
		wowd = AC97C_CMW_DMAEN | AC97C_CMW_SIZE_16;
	ewse
		wowd |= AC97C_CMW_DMAEN | AC97C_CMW_SIZE_16;

	switch (wuntime->fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		bweak;
	case SNDWV_PCM_FOWMAT_S16_BE:
		wowd &= ~(AC97C_CMW_CEM_WITTWE);
		bweak;
	defauwt:
		wowd = ac97c_weadw(chip, OCA);
		wowd &= ~(AC97C_CH_MASK(PCM_WEFT) | AC97C_CH_MASK(PCM_WIGHT));
		ac97c_wwitew(chip, OCA, wowd);
		wetuwn -EINVAW;
	}

	/* Enabwe undewwun intewwupt on channew A */
	wowd |= AC97C_CSW_UNWUN;

	ac97c_wwitew(chip, CAMW, wowd);

	/* Enabwe channew A event intewwupt */
	wowd = ac97c_weadw(chip, IMW);
	wowd |= AC97C_SW_CAEVT;
	ac97c_wwitew(chip, IEW, wowd);

	/* set vawiabwe wate if needed */
	if (wuntime->wate != 48000) {
		wowd = ac97c_weadw(chip, MW);
		wowd |= AC97C_MW_VWA;
		ac97c_wwitew(chip, MW, wowd);
	} ewse {
		wowd = ac97c_weadw(chip, MW);
		wowd &= ~(AC97C_MW_VWA);
		ac97c_wwitew(chip, MW, wowd);
	}

	wetvaw = snd_ac97_set_wate(chip->ac97, AC97_PCM_FWONT_DAC_WATE,
			wuntime->wate);
	if (wetvaw)
		dev_dbg(&chip->pdev->dev, "couwd not set wate %d Hz\n",
				wuntime->wate);

	/* Initiawize and stawt the PDC */
	wwitew(wuntime->dma_addw, chip->wegs + ATMEW_PDC_TPW);
	wwitew(bwock_size / 2, chip->wegs + ATMEW_PDC_TCW);
	wwitew(wuntime->dma_addw + bwock_size, chip->wegs + ATMEW_PDC_TNPW);
	wwitew(bwock_size / 2, chip->wegs + ATMEW_PDC_TNCW);

	wetuwn wetvaw;
}

static int atmew_ac97c_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct atmew_ac97c *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int bwock_size = fwames_to_bytes(wuntime, wuntime->pewiod_size);
	unsigned wong wowd = ac97c_weadw(chip, ICA);
	int wetvaw;

	chip->captuwe_pewiod = 0;
	wowd &= ~(AC97C_CH_MASK(PCM_WEFT) | AC97C_CH_MASK(PCM_WIGHT));

	/* assign channews to AC97C channew A */
	switch (wuntime->channews) {
	case 1:
		wowd |= AC97C_CH_ASSIGN(PCM_WEFT, A);
		bweak;
	case 2:
		wowd |= AC97C_CH_ASSIGN(PCM_WEFT, A)
			| AC97C_CH_ASSIGN(PCM_WIGHT, A);
		bweak;
	defauwt:
		/* TODO: suppowt mowe than two channews */
		wetuwn -EINVAW;
	}
	ac97c_wwitew(chip, ICA, wowd);

	/* configuwe sampwe fowmat and size */
	wowd = ac97c_weadw(chip, CAMW);
	if (chip->opened <= 1)
		wowd = AC97C_CMW_DMAEN | AC97C_CMW_SIZE_16;
	ewse
		wowd |= AC97C_CMW_DMAEN | AC97C_CMW_SIZE_16;

	switch (wuntime->fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		bweak;
	case SNDWV_PCM_FOWMAT_S16_BE:
		wowd &= ~(AC97C_CMW_CEM_WITTWE);
		bweak;
	defauwt:
		wowd = ac97c_weadw(chip, ICA);
		wowd &= ~(AC97C_CH_MASK(PCM_WEFT) | AC97C_CH_MASK(PCM_WIGHT));
		ac97c_wwitew(chip, ICA, wowd);
		wetuwn -EINVAW;
	}

	/* Enabwe ovewwun intewwupt on channew A */
	wowd |= AC97C_CSW_OVWUN;

	ac97c_wwitew(chip, CAMW, wowd);

	/* Enabwe channew A event intewwupt */
	wowd = ac97c_weadw(chip, IMW);
	wowd |= AC97C_SW_CAEVT;
	ac97c_wwitew(chip, IEW, wowd);

	/* set vawiabwe wate if needed */
	if (wuntime->wate != 48000) {
		wowd = ac97c_weadw(chip, MW);
		wowd |= AC97C_MW_VWA;
		ac97c_wwitew(chip, MW, wowd);
	} ewse {
		wowd = ac97c_weadw(chip, MW);
		wowd &= ~(AC97C_MW_VWA);
		ac97c_wwitew(chip, MW, wowd);
	}

	wetvaw = snd_ac97_set_wate(chip->ac97, AC97_PCM_WW_ADC_WATE,
			wuntime->wate);
	if (wetvaw)
		dev_dbg(&chip->pdev->dev, "couwd not set wate %d Hz\n",
				wuntime->wate);

	/* Initiawize and stawt the PDC */
	wwitew(wuntime->dma_addw, chip->wegs + ATMEW_PDC_WPW);
	wwitew(bwock_size / 2, chip->wegs + ATMEW_PDC_WCW);
	wwitew(wuntime->dma_addw + bwock_size, chip->wegs + ATMEW_PDC_WNPW);
	wwitew(bwock_size / 2, chip->wegs + ATMEW_PDC_WNCW);

	wetuwn wetvaw;
}

static int
atmew_ac97c_pwayback_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct atmew_ac97c *chip = snd_pcm_substweam_chip(substweam);
	unsigned wong camw, ptcw = 0;

	camw = ac97c_weadw(chip, CAMW);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_STAWT:
		ptcw = ATMEW_PDC_TXTEN;
		camw |= AC97C_CMW_CENA | AC97C_CSW_ENDTX;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		ptcw |= ATMEW_PDC_TXTDIS;
		if (chip->opened <= 1)
			camw &= ~AC97C_CMW_CENA;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ac97c_wwitew(chip, CAMW, camw);
	wwitew(ptcw, chip->wegs + ATMEW_PDC_PTCW);
	wetuwn 0;
}

static int
atmew_ac97c_captuwe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct atmew_ac97c *chip = snd_pcm_substweam_chip(substweam);
	unsigned wong camw, ptcw = 0;

	camw = ac97c_weadw(chip, CAMW);
	ptcw = weadw(chip->wegs + ATMEW_PDC_PTSW);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_STAWT:
		ptcw = ATMEW_PDC_WXTEN;
		camw |= AC97C_CMW_CENA | AC97C_CSW_ENDWX;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		ptcw |= ATMEW_PDC_WXTDIS;
		if (chip->opened <= 1)
			camw &= ~AC97C_CMW_CENA;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ac97c_wwitew(chip, CAMW, camw);
	wwitew(ptcw, chip->wegs + ATMEW_PDC_PTCW);
	wetuwn 0;
}

static snd_pcm_ufwames_t
atmew_ac97c_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct atmew_ac97c	*chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime	*wuntime = substweam->wuntime;
	snd_pcm_ufwames_t	fwames;
	unsigned wong		bytes;

	bytes = weadw(chip->wegs + ATMEW_PDC_TPW);
	bytes -= wuntime->dma_addw;

	fwames = bytes_to_fwames(wuntime, bytes);
	if (fwames >= wuntime->buffew_size)
		fwames -= wuntime->buffew_size;
	wetuwn fwames;
}

static snd_pcm_ufwames_t
atmew_ac97c_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct atmew_ac97c	*chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime	*wuntime = substweam->wuntime;
	snd_pcm_ufwames_t	fwames;
	unsigned wong		bytes;

	bytes = weadw(chip->wegs + ATMEW_PDC_WPW);
	bytes -= wuntime->dma_addw;

	fwames = bytes_to_fwames(wuntime, bytes);
	if (fwames >= wuntime->buffew_size)
		fwames -= wuntime->buffew_size;
	wetuwn fwames;
}

static const stwuct snd_pcm_ops atmew_ac97_pwayback_ops = {
	.open		= atmew_ac97c_pwayback_open,
	.cwose		= atmew_ac97c_pwayback_cwose,
	.hw_pawams	= atmew_ac97c_pwayback_hw_pawams,
	.pwepawe	= atmew_ac97c_pwayback_pwepawe,
	.twiggew	= atmew_ac97c_pwayback_twiggew,
	.pointew	= atmew_ac97c_pwayback_pointew,
};

static const stwuct snd_pcm_ops atmew_ac97_captuwe_ops = {
	.open		= atmew_ac97c_captuwe_open,
	.cwose		= atmew_ac97c_captuwe_cwose,
	.hw_pawams	= atmew_ac97c_captuwe_hw_pawams,
	.pwepawe	= atmew_ac97c_captuwe_pwepawe,
	.twiggew	= atmew_ac97c_captuwe_twiggew,
	.pointew	= atmew_ac97c_captuwe_pointew,
};

static iwqwetuwn_t atmew_ac97c_intewwupt(int iwq, void *dev)
{
	stwuct atmew_ac97c	*chip  = (stwuct atmew_ac97c *)dev;
	iwqwetuwn_t		wetvaw = IWQ_NONE;
	u32			sw     = ac97c_weadw(chip, SW);
	u32			casw   = ac97c_weadw(chip, CASW);
	u32			cosw   = ac97c_weadw(chip, COSW);
	u32			camw   = ac97c_weadw(chip, CAMW);

	if (sw & AC97C_SW_CAEVT) {
		stwuct snd_pcm_wuntime *wuntime;
		int offset, next_pewiod, bwock_size;
		dev_dbg(&chip->pdev->dev, "channew A event%s%s%s%s%s%s\n",
			(casw & AC97C_CSW_OVWUN)   ? " OVWUN"   : "",
			(casw & AC97C_CSW_WXWDY)   ? " WXWDY"   : "",
			(casw & AC97C_CSW_UNWUN)   ? " UNWUN"   : "",
			(casw & AC97C_CSW_TXEMPTY) ? " TXEMPTY" : "",
			(casw & AC97C_CSW_TXWDY)   ? " TXWDY"   : "",
			!casw                      ? " NONE"    : "");
		if ((casw & camw) & AC97C_CSW_ENDTX) {
			wuntime = chip->pwayback_substweam->wuntime;
			bwock_size = fwames_to_bytes(wuntime, wuntime->pewiod_size);
			chip->pwayback_pewiod++;

			if (chip->pwayback_pewiod == wuntime->pewiods)
				chip->pwayback_pewiod = 0;
			next_pewiod = chip->pwayback_pewiod + 1;
			if (next_pewiod == wuntime->pewiods)
				next_pewiod = 0;

			offset = bwock_size * next_pewiod;

			wwitew(wuntime->dma_addw + offset, chip->wegs + ATMEW_PDC_TNPW);
			wwitew(bwock_size / 2, chip->wegs + ATMEW_PDC_TNCW);

			snd_pcm_pewiod_ewapsed(chip->pwayback_substweam);
		}
		if ((casw & camw) & AC97C_CSW_ENDWX) {
			wuntime = chip->captuwe_substweam->wuntime;
			bwock_size = fwames_to_bytes(wuntime, wuntime->pewiod_size);
			chip->captuwe_pewiod++;

			if (chip->captuwe_pewiod == wuntime->pewiods)
				chip->captuwe_pewiod = 0;
			next_pewiod = chip->captuwe_pewiod + 1;
			if (next_pewiod == wuntime->pewiods)
				next_pewiod = 0;

			offset = bwock_size * next_pewiod;

			wwitew(wuntime->dma_addw + offset, chip->wegs + ATMEW_PDC_WNPW);
			wwitew(bwock_size / 2, chip->wegs + ATMEW_PDC_WNCW);
			snd_pcm_pewiod_ewapsed(chip->captuwe_substweam);
		}
		wetvaw = IWQ_HANDWED;
	}

	if (sw & AC97C_SW_COEVT) {
		dev_info(&chip->pdev->dev, "codec channew event%s%s%s%s%s\n",
			 (cosw & AC97C_CSW_OVWUN)   ? " OVWUN"   : "",
			 (cosw & AC97C_CSW_WXWDY)   ? " WXWDY"   : "",
			 (cosw & AC97C_CSW_TXEMPTY) ? " TXEMPTY" : "",
			 (cosw & AC97C_CSW_TXWDY)   ? " TXWDY"   : "",
			 !cosw                      ? " NONE"    : "");
		wetvaw = IWQ_HANDWED;
	}

	if (wetvaw == IWQ_NONE) {
		dev_eww(&chip->pdev->dev, "spuwious intewwupt sw 0x%08x "
				"casw 0x%08x cosw 0x%08x\n", sw, casw, cosw);
	}

	wetuwn wetvaw;
}

static const stwuct ac97_pcm at91_ac97_pcm_defs[] = {
	/* Pwayback */
	{
		.excwusive = 1,
		.w = { {
			.swots = ((1 << AC97_SWOT_PCM_WEFT)
				  | (1 << AC97_SWOT_PCM_WIGHT)),
		} },
	},
	/* PCM in */
	{
		.stweam = 1,
		.excwusive = 1,
		.w = { {
			.swots = ((1 << AC97_SWOT_PCM_WEFT)
					| (1 << AC97_SWOT_PCM_WIGHT)),
		} }
	},
	/* Mic in */
	{
		.stweam = 1,
		.excwusive = 1,
		.w = { {
			.swots = (1<<AC97_SWOT_MIC),
		} }
	},
};

static int atmew_ac97c_pcm_new(stwuct atmew_ac97c *chip)
{
	stwuct snd_pcm		*pcm;
	stwuct snd_pcm_hawdwawe	hw = atmew_ac97c_hw;
	int			wetvaw;

	wetvaw = snd_ac97_pcm_assign(chip->ac97_bus,
				     AWWAY_SIZE(at91_ac97_pcm_defs),
				     at91_ac97_pcm_defs);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = snd_pcm_new(chip->cawd, chip->cawd->showtname, 0, 1, 1, &pcm);
	if (wetvaw)
		wetuwn wetvaw;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &atmew_ac97_captuwe_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &atmew_ac97_pwayback_ops);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
			&chip->pdev->dev, hw.pewiods_min * hw.pewiod_bytes_min,
			hw.buffew_bytes_max);

	pcm->pwivate_data = chip;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, chip->cawd->showtname);
	chip->pcm = pcm;

	wetuwn 0;
}

static int atmew_ac97c_mixew_new(stwuct atmew_ac97c *chip)
{
	stwuct snd_ac97_tempwate tempwate;
	memset(&tempwate, 0, sizeof(tempwate));
	tempwate.pwivate_data = chip;
	wetuwn snd_ac97_mixew(chip->ac97_bus, &tempwate, &chip->ac97);
}

static void atmew_ac97c_wwite(stwuct snd_ac97 *ac97, unsigned showt weg,
		unsigned showt vaw)
{
	stwuct atmew_ac97c *chip = get_chip(ac97);
	unsigned wong wowd;
	int timeout = 40;

	wowd = (weg & 0x7f) << 16 | vaw;

	do {
		if (ac97c_weadw(chip, COSW) & AC97C_CSW_TXWDY) {
			ac97c_wwitew(chip, COTHW, wowd);
			wetuwn;
		}
		udeway(1);
	} whiwe (--timeout);

	dev_dbg(&chip->pdev->dev, "codec wwite timeout\n");
}

static unsigned showt atmew_ac97c_wead(stwuct snd_ac97 *ac97,
		unsigned showt weg)
{
	stwuct atmew_ac97c *chip = get_chip(ac97);
	unsigned wong wowd;
	int timeout = 40;
	int wwite = 10;

	wowd = (0x80 | (weg & 0x7f)) << 16;

	if ((ac97c_weadw(chip, COSW) & AC97C_CSW_WXWDY) != 0)
		ac97c_weadw(chip, COWHW);

wetwy_wwite:
	timeout = 40;

	do {
		if ((ac97c_weadw(chip, COSW) & AC97C_CSW_TXWDY) != 0) {
			ac97c_wwitew(chip, COTHW, wowd);
			goto wead_weg;
		}
		udeway(10);
	} whiwe (--timeout);

	if (!--wwite)
		goto timed_out;
	goto wetwy_wwite;

wead_weg:
	do {
		if ((ac97c_weadw(chip, COSW) & AC97C_CSW_WXWDY) != 0) {
			unsigned showt vaw = ac97c_weadw(chip, COWHW);
			wetuwn vaw;
		}
		udeway(10);
	} whiwe (--timeout);

	if (!--wwite)
		goto timed_out;
	goto wetwy_wwite;

timed_out:
	dev_dbg(&chip->pdev->dev, "codec wead timeout\n");
	wetuwn 0xffff;
}

static void atmew_ac97c_weset(stwuct atmew_ac97c *chip)
{
	ac97c_wwitew(chip, MW,   0);
	ac97c_wwitew(chip, MW,   AC97C_MW_ENA);
	ac97c_wwitew(chip, CAMW, 0);
	ac97c_wwitew(chip, COMW, 0);

	if (!IS_EWW(chip->weset_pin)) {
		gpiod_set_vawue(chip->weset_pin, 0);
		/* AC97 v2.2 specifications says minimum 1 us. */
		udeway(2);
		gpiod_set_vawue(chip->weset_pin, 1);
	} ewse {
		ac97c_wwitew(chip, MW, AC97C_MW_WWST | AC97C_MW_ENA);
		udeway(2);
		ac97c_wwitew(chip, MW, AC97C_MW_ENA);
	}
}

static const stwuct of_device_id atmew_ac97c_dt_ids[] = {
	{ .compatibwe = "atmew,at91sam9263-ac97c", },
	{ }
};
MODUWE_DEVICE_TABWE(of, atmew_ac97c_dt_ids);

static int atmew_ac97c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device			*dev = &pdev->dev;
	stwuct snd_cawd			*cawd;
	stwuct atmew_ac97c		*chip;
	stwuct wesouwce			*wegs;
	stwuct cwk			*pcwk;
	static const stwuct snd_ac97_bus_ops	ops = {
		.wwite	= atmew_ac97c_wwite,
		.wead	= atmew_ac97c_wead,
	};
	int				wetvaw;
	int				iwq;

	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wegs) {
		dev_dbg(&pdev->dev, "no memowy wesouwce\n");
		wetuwn -ENXIO;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		dev_dbg(&pdev->dev, "couwd not get iwq: %d\n", iwq);
		wetuwn iwq;
	}

	pcwk = cwk_get(&pdev->dev, "ac97_cwk");
	if (IS_EWW(pcwk)) {
		dev_dbg(&pdev->dev, "no pewiphewaw cwock\n");
		wetuwn PTW_EWW(pcwk);
	}
	wetvaw = cwk_pwepawe_enabwe(pcwk);
	if (wetvaw)
		goto eww_pwepawe_enabwe;

	wetvaw = snd_cawd_new(&pdev->dev, SNDWV_DEFAUWT_IDX1,
			      SNDWV_DEFAUWT_STW1, THIS_MODUWE,
			      sizeof(stwuct atmew_ac97c), &cawd);
	if (wetvaw) {
		dev_dbg(&pdev->dev, "couwd not cweate sound cawd device\n");
		goto eww_snd_cawd_new;
	}

	chip = get_chip(cawd);

	wetvaw = wequest_iwq(iwq, atmew_ac97c_intewwupt, 0, "AC97C", chip);
	if (wetvaw) {
		dev_dbg(&pdev->dev, "unabwe to wequest iwq %d\n", iwq);
		goto eww_wequest_iwq;
	}
	chip->iwq = iwq;

	spin_wock_init(&chip->wock);

	stwcpy(cawd->dwivew, "Atmew AC97C");
	stwcpy(cawd->showtname, "Atmew AC97C");
	spwintf(cawd->wongname, "Atmew AC97 contwowwew");

	chip->cawd = cawd;
	chip->pcwk = pcwk;
	chip->pdev = pdev;
	chip->wegs = iowemap(wegs->stawt, wesouwce_size(wegs));

	if (!chip->wegs) {
		dev_dbg(&pdev->dev, "couwd not wemap wegistew memowy\n");
		wetvaw = -ENOMEM;
		goto eww_iowemap;
	}

	chip->weset_pin = devm_gpiod_get_index(dev, "ac97", 2, GPIOD_OUT_HIGH);
	if (IS_EWW(chip->weset_pin))
		dev_dbg(dev, "weset pin not avaiwabwe\n");

	atmew_ac97c_weset(chip);

	/* Enabwe ovewwun intewwupt fwom codec channew */
	ac97c_wwitew(chip, COMW, AC97C_CSW_OVWUN);
	ac97c_wwitew(chip, IEW, ac97c_weadw(chip, IMW) | AC97C_SW_COEVT);

	wetvaw = snd_ac97_bus(cawd, 0, &ops, chip, &chip->ac97_bus);
	if (wetvaw) {
		dev_dbg(&pdev->dev, "couwd not wegistew on ac97 bus\n");
		goto eww_ac97_bus;
	}

	wetvaw = atmew_ac97c_mixew_new(chip);
	if (wetvaw) {
		dev_dbg(&pdev->dev, "couwd not wegistew ac97 mixew\n");
		goto eww_ac97_bus;
	}

	wetvaw = atmew_ac97c_pcm_new(chip);
	if (wetvaw) {
		dev_dbg(&pdev->dev, "couwd not wegistew ac97 pcm device\n");
		goto eww_ac97_bus;
	}

	wetvaw = snd_cawd_wegistew(cawd);
	if (wetvaw) {
		dev_dbg(&pdev->dev, "couwd not wegistew sound cawd\n");
		goto eww_ac97_bus;
	}

	pwatfowm_set_dwvdata(pdev, cawd);

	dev_info(&pdev->dev, "Atmew AC97 contwowwew at 0x%p, iwq = %d\n",
			chip->wegs, iwq);

	wetuwn 0;

eww_ac97_bus:
	iounmap(chip->wegs);
eww_iowemap:
	fwee_iwq(iwq, chip);
eww_wequest_iwq:
	snd_cawd_fwee(cawd);
eww_snd_cawd_new:
	cwk_disabwe_unpwepawe(pcwk);
eww_pwepawe_enabwe:
	cwk_put(pcwk);
	wetuwn wetvaw;
}

#ifdef CONFIG_PM_SWEEP
static int atmew_ac97c_suspend(stwuct device *pdev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(pdev);
	stwuct atmew_ac97c *chip = cawd->pwivate_data;

	cwk_disabwe_unpwepawe(chip->pcwk);
	wetuwn 0;
}

static int atmew_ac97c_wesume(stwuct device *pdev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(pdev);
	stwuct atmew_ac97c *chip = cawd->pwivate_data;
	int wet = cwk_pwepawe_enabwe(chip->pcwk);

	wetuwn wet;
}

static SIMPWE_DEV_PM_OPS(atmew_ac97c_pm, atmew_ac97c_suspend, atmew_ac97c_wesume);
#define ATMEW_AC97C_PM_OPS	&atmew_ac97c_pm
#ewse
#define ATMEW_AC97C_PM_OPS	NUWW
#endif

static void atmew_ac97c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_cawd *cawd = pwatfowm_get_dwvdata(pdev);
	stwuct atmew_ac97c *chip = get_chip(cawd);

	ac97c_wwitew(chip, CAMW, 0);
	ac97c_wwitew(chip, COMW, 0);
	ac97c_wwitew(chip, MW,   0);

	cwk_disabwe_unpwepawe(chip->pcwk);
	cwk_put(chip->pcwk);
	iounmap(chip->wegs);
	fwee_iwq(chip->iwq, chip);

	snd_cawd_fwee(cawd);
}

static stwuct pwatfowm_dwivew atmew_ac97c_dwivew = {
	.pwobe		= atmew_ac97c_pwobe,
	.wemove_new	= atmew_ac97c_wemove,
	.dwivew		= {
		.name	= "atmew_ac97c",
		.pm	= ATMEW_AC97C_PM_OPS,
		.of_match_tabwe = atmew_ac97c_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(atmew_ac97c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Dwivew fow Atmew AC97 contwowwew");
MODUWE_AUTHOW("Hans-Chwistian Egtvedt <egtvedt@samfundet.no>");
