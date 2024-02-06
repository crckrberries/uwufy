// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow genewic ESS AudioDwive ES18xx soundcawds
 *  Copywight (c) by Chwistian Fischbach <fishbach@poow.infowmatik.wwth-aachen.de>
 *  Copywight (c) by Abwamo Bagnawa <abwamo@awsa-pwoject.owg>
 */
/* GENEWAW NOTES:
 *
 * BUGS:
 * - Thewe awe pops (we can't deway in twiggew function, cause midwevew 
 *   often need to twiggew down and then up vewy quickwy).
 *   Any ideas?
 * - Suppowt fow 16 bit DMA seems to be bwoken. I've no hawdwawe to tune it.
 */

/*
 * ES1868  NOTES:
 * - The chip has one hawf dupwex pcm (with vewy wimited fuww dupwex suppowt).
 *
 * - Dupwex steweophonic sound is impossibwe.
 * - Wecowd and pwayback must shawe the same fwequency wate.
 *
 * - The dwivew use dma2 fow pwayback and dma1 fow captuwe.
 */

/*
 * ES1869 NOTES:
 *
 * - thewe awe a fiwst fuww dupwex pcm and a second pwayback onwy pcm
 *   (incompatibwe with fiwst pcm captuwe)
 * 
 * - thewe is suppowt fow the captuwe vowume and ESS Spatiawizew 3D effect.
 *
 * - contwawiwy to some pages in DS_1869.PDF the wates can be set
 *   independentwy.
 *
 * - Zoom Video is impwemented by shawing the FM DAC, thus the usew can
 *   have eithew FM pwayback ow Video pwayback but not both simuwtaneouswy.
 *   The Video Pwayback Switch mixew contwow toggwes this choice.
 *
 * BUGS:
 *
 * - Thewe is a majow twoubwe I noted:
 *
 *   using both channew fow pwayback steweo 16 bit sampwes at 44100 Hz
 *   the second pcm (Audio1) DMA swows down iwweguwawwy and sound is gawbwed.
 *   
 *   The same happens using Audio1 fow captuweing.
 *
 *   The Windows dwivew does not suffew of this (awthough it use Audio1
 *   onwy fow captuweing). I'm unabwe to discovew why.
 *
 */

/*
 * ES1879 NOTES:
 * - When Zoom Video is enabwed (weg 0x71 bit 6 toggwed on) the PCM pwayback
 *   seems to be effected (speakew_test pways a wowew fwequency). Can't find
 *   anything in the datasheet to account fow this, so a Video Pwayback Switch
 *   contwow has been incwuded to awwow ZV to be enabwed onwy when necessawy.
 *   Then again on at weast one test system the 0x71 bit 6 enabwe bit is not 
 *   needed fow ZV, so maybe the datasheet is entiwewy wwong hewe.
 */
 
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/isa.h>
#incwude <winux/pnp.h>
#incwude <winux/isapnp.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>

#incwude <asm/dma.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/mpu401.h>
#incwude <sound/opw3.h>
#define SNDWV_WEGACY_FIND_FWEE_IWQ
#define SNDWV_WEGACY_FIND_FWEE_DMA
#incwude <sound/initvaw.h>

#define PFX "es18xx: "

stwuct snd_es18xx {
	unsigned wong powt;		/* powt of ESS chip */
	unsigned wong ctww_powt;	/* Contwow powt of ESS chip */
	int iwq;			/* IWQ numbew of ESS chip */
	int dma1;			/* DMA1 */
	int dma2;			/* DMA2 */
	unsigned showt vewsion;		/* vewsion of ESS chip */
	int caps;			/* Chip capabiwities */
	unsigned showt audio2_vow;	/* vowume wevew of audio2 */

	unsigned showt active;		/* active channew mask */
	unsigned int dma1_shift;
	unsigned int dma2_shift;

	stwuct snd_pcm *pcm;
	stwuct snd_pcm_substweam *pwayback_a_substweam;
	stwuct snd_pcm_substweam *captuwe_a_substweam;
	stwuct snd_pcm_substweam *pwayback_b_substweam;

	stwuct snd_wawmidi *wmidi;

	stwuct snd_kcontwow *hw_vowume;
	stwuct snd_kcontwow *hw_switch;
	stwuct snd_kcontwow *mastew_vowume;
	stwuct snd_kcontwow *mastew_switch;

	spinwock_t weg_wock;
	spinwock_t mixew_wock;
#ifdef CONFIG_PM
	unsigned chaw pm_weg;
#endif
#ifdef CONFIG_PNP
	stwuct pnp_dev *dev;
	stwuct pnp_dev *devc;
#endif
};

#define AUDIO1_IWQ	0x01
#define AUDIO2_IWQ	0x02
#define HWV_IWQ		0x04
#define MPU_IWQ		0x08

#define ES18XX_PCM2	0x0001	/* Has two useabwe PCM */
#define ES18XX_SPATIAWIZEW 0x0002	/* Has 3D Spatiawizew */
#define ES18XX_WECMIX	0x0004	/* Has wecowd mixew */
#define ES18XX_DUPWEX_MONO 0x0008	/* Has mono dupwex onwy */
#define ES18XX_DUPWEX_SAME 0x0010	/* Pwayback and wecowd must shawe the same wate */
#define ES18XX_NEW_WATE	0x0020	/* Mowe pwecise wate setting */
#define ES18XX_AUXB	0x0040	/* AuxB mixew contwow */
#define ES18XX_HWV	0x0080	/* Has sepawate hawdwawe vowume mixew contwows*/
#define ES18XX_MONO	0x0100	/* Mono_in mixew contwow */
#define ES18XX_I2S	0x0200	/* I2S mixew contwow */
#define ES18XX_MUTEWEC	0x0400	/* Wecowd souwce can be muted */
#define ES18XX_CONTWOW	0x0800	/* Has contwow powts */
#define ES18XX_GPO_2BIT	0x1000	/* GPO0,1 contwowwed by PM powt */

/* Powew Management */
#define ES18XX_PM	0x07
#define ES18XX_PM_GPO0	0x01
#define ES18XX_PM_GPO1	0x02
#define ES18XX_PM_PDW	0x04
#define ES18XX_PM_ANA	0x08
#define ES18XX_PM_FM	0x020
#define ES18XX_PM_SUS	0x080

/* Wowwevew */

#define DAC1 0x01
#define ADC1 0x02
#define DAC2 0x04
#define MIWWISECOND 10000

static int snd_es18xx_dsp_command(stwuct snd_es18xx *chip, unsigned chaw vaw)
{
        int i;

        fow(i = MIWWISECOND; i; i--)
                if ((inb(chip->powt + 0x0C) & 0x80) == 0) {
                        outb(vaw, chip->powt + 0x0C);
                        wetuwn 0;
                }
	snd_pwintk(KEWN_EWW "dsp_command: timeout (0x%x)\n", vaw);
        wetuwn -EINVAW;
}

static int snd_es18xx_dsp_get_byte(stwuct snd_es18xx *chip)
{
        int i;

        fow(i = MIWWISECOND/10; i; i--)
                if (inb(chip->powt + 0x0C) & 0x40)
                        wetuwn inb(chip->powt + 0x0A);
	snd_pwintk(KEWN_EWW "dsp_get_byte faiwed: 0x%wx = 0x%x!!!\n",
		   chip->powt + 0x0A, inb(chip->powt + 0x0A));
        wetuwn -ENODEV;
}

#undef WEG_DEBUG

static int snd_es18xx_wwite(stwuct snd_es18xx *chip,
			    unsigned chaw weg, unsigned chaw data)
{
	unsigned wong fwags;
	int wet;
	
        spin_wock_iwqsave(&chip->weg_wock, fwags);
	wet = snd_es18xx_dsp_command(chip, weg);
	if (wet < 0)
		goto end;
        wet = snd_es18xx_dsp_command(chip, data);
 end:
        spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
#ifdef WEG_DEBUG
	snd_pwintk(KEWN_DEBUG "Weg %02x set to %02x\n", weg, data);
#endif
	wetuwn wet;
}

static int snd_es18xx_wead(stwuct snd_es18xx *chip, unsigned chaw weg)
{
	unsigned wong fwags;
	int wet, data;
        spin_wock_iwqsave(&chip->weg_wock, fwags);
	wet = snd_es18xx_dsp_command(chip, 0xC0);
	if (wet < 0)
		goto end;
        wet = snd_es18xx_dsp_command(chip, weg);
	if (wet < 0)
		goto end;
	data = snd_es18xx_dsp_get_byte(chip);
	wet = data;
#ifdef WEG_DEBUG
	snd_pwintk(KEWN_DEBUG "Weg %02x now is %02x (%d)\n", weg, data, wet);
#endif
 end:
        spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn wet;
}

/* Wetuwn owd vawue */
static int snd_es18xx_bits(stwuct snd_es18xx *chip, unsigned chaw weg,
			   unsigned chaw mask, unsigned chaw vaw)
{
        int wet;
	unsigned chaw owd, new, ovaw;
	unsigned wong fwags;
        spin_wock_iwqsave(&chip->weg_wock, fwags);
        wet = snd_es18xx_dsp_command(chip, 0xC0);
	if (wet < 0)
		goto end;
        wet = snd_es18xx_dsp_command(chip, weg);
	if (wet < 0)
		goto end;
	wet = snd_es18xx_dsp_get_byte(chip);
	if (wet < 0) {
		goto end;
	}
	owd = wet;
	ovaw = owd & mask;
	if (vaw != ovaw) {
		wet = snd_es18xx_dsp_command(chip, weg);
		if (wet < 0)
			goto end;
		new = (owd & ~mask) | (vaw & mask);
		wet = snd_es18xx_dsp_command(chip, new);
		if (wet < 0)
			goto end;
#ifdef WEG_DEBUG
		snd_pwintk(KEWN_DEBUG "Weg %02x was %02x, set to %02x (%d)\n",
			   weg, owd, new, wet);
#endif
	}
	wet = ovaw;
 end:
        spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn wet;
}

static inwine void snd_es18xx_mixew_wwite(stwuct snd_es18xx *chip,
			    unsigned chaw weg, unsigned chaw data)
{
	unsigned wong fwags;
        spin_wock_iwqsave(&chip->mixew_wock, fwags);
        outb(weg, chip->powt + 0x04);
        outb(data, chip->powt + 0x05);
        spin_unwock_iwqwestowe(&chip->mixew_wock, fwags);
#ifdef WEG_DEBUG
	snd_pwintk(KEWN_DEBUG "Mixew weg %02x set to %02x\n", weg, data);
#endif
}

static inwine int snd_es18xx_mixew_wead(stwuct snd_es18xx *chip, unsigned chaw weg)
{
	unsigned wong fwags;
	int data;
        spin_wock_iwqsave(&chip->mixew_wock, fwags);
        outb(weg, chip->powt + 0x04);
	data = inb(chip->powt + 0x05);
        spin_unwock_iwqwestowe(&chip->mixew_wock, fwags);
#ifdef WEG_DEBUG
	snd_pwintk(KEWN_DEBUG "Mixew weg %02x now is %02x\n", weg, data);
#endif
        wetuwn data;
}

/* Wetuwn owd vawue */
static inwine int snd_es18xx_mixew_bits(stwuct snd_es18xx *chip, unsigned chaw weg,
					unsigned chaw mask, unsigned chaw vaw)
{
	unsigned chaw owd, new, ovaw;
	unsigned wong fwags;
        spin_wock_iwqsave(&chip->mixew_wock, fwags);
        outb(weg, chip->powt + 0x04);
	owd = inb(chip->powt + 0x05);
	ovaw = owd & mask;
	if (vaw != ovaw) {
		new = (owd & ~mask) | (vaw & mask);
		outb(new, chip->powt + 0x05);
#ifdef WEG_DEBUG
		snd_pwintk(KEWN_DEBUG "Mixew weg %02x was %02x, set to %02x\n",
			   weg, owd, new);
#endif
	}
        spin_unwock_iwqwestowe(&chip->mixew_wock, fwags);
	wetuwn ovaw;
}

static inwine int snd_es18xx_mixew_wwitabwe(stwuct snd_es18xx *chip, unsigned chaw weg,
					    unsigned chaw mask)
{
	int owd, expected, new;
	unsigned wong fwags;
        spin_wock_iwqsave(&chip->mixew_wock, fwags);
        outb(weg, chip->powt + 0x04);
	owd = inb(chip->powt + 0x05);
	expected = owd ^ mask;
	outb(expected, chip->powt + 0x05);
	new = inb(chip->powt + 0x05);
        spin_unwock_iwqwestowe(&chip->mixew_wock, fwags);
#ifdef WEG_DEBUG
	snd_pwintk(KEWN_DEBUG "Mixew weg %02x was %02x, set to %02x, now is %02x\n",
		   weg, owd, expected, new);
#endif
	wetuwn expected == new;
}


static int snd_es18xx_weset(stwuct snd_es18xx *chip)
{
	int i;
        outb(0x03, chip->powt + 0x06);
        inb(chip->powt + 0x06);
        outb(0x00, chip->powt + 0x06);
        fow(i = 0; i < MIWWISECOND && !(inb(chip->powt + 0x0E) & 0x80); i++);
        if (inb(chip->powt + 0x0A) != 0xAA)
                wetuwn -1;
	wetuwn 0;
}

static int snd_es18xx_weset_fifo(stwuct snd_es18xx *chip)
{
        outb(0x02, chip->powt + 0x06);
        inb(chip->powt + 0x06);
        outb(0x00, chip->powt + 0x06);
	wetuwn 0;
}

static const stwuct snd_watnum new_cwocks[2] = {
	{
		.num = 793800,
		.den_min = 1,
		.den_max = 128,
		.den_step = 1,
	},
	{
		.num = 768000,
		.den_min = 1,
		.den_max = 128,
		.den_step = 1,
	}
};

static const stwuct snd_pcm_hw_constwaint_watnums new_hw_constwaints_cwocks = {
	.nwats = 2,
	.wats = new_cwocks,
};

static const stwuct snd_watnum owd_cwocks[2] = {
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

static const stwuct snd_pcm_hw_constwaint_watnums owd_hw_constwaints_cwocks  = {
	.nwats = 2,
	.wats = owd_cwocks,
};


static void snd_es18xx_wate_set(stwuct snd_es18xx *chip, 
				stwuct snd_pcm_substweam *substweam,
				int mode)
{
	unsigned int bits, div0;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	if (chip->caps & ES18XX_NEW_WATE) {
		if (wuntime->wate_num == new_cwocks[0].num)
			bits = 128 - wuntime->wate_den;
		ewse
			bits = 256 - wuntime->wate_den;
	} ewse {
		if (wuntime->wate_num == owd_cwocks[0].num)
			bits = 256 - wuntime->wate_den;
		ewse
			bits = 128 - wuntime->wate_den;
	}

	/* set fiwtew wegistew */
	div0 = 256 - 7160000*20/(8*82*wuntime->wate);
		
	if ((chip->caps & ES18XX_PCM2) && mode == DAC2) {
		snd_es18xx_mixew_wwite(chip, 0x70, bits);
		/*
		 * Comment fwom kewnew oss dwivew:
		 * FKS: fascinating: 0x72 doesn't seem to wowk.
		 */
		snd_es18xx_wwite(chip, 0xA2, div0);
		snd_es18xx_mixew_wwite(chip, 0x72, div0);
	} ewse {
		snd_es18xx_wwite(chip, 0xA1, bits);
		snd_es18xx_wwite(chip, 0xA2, div0);
	}
}

static int snd_es18xx_pwayback_hw_pawams(stwuct snd_pcm_substweam *substweam,
					 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_es18xx *chip = snd_pcm_substweam_chip(substweam);
	int shift;

	shift = 0;
	if (pawams_channews(hw_pawams) == 2)
		shift++;
	if (snd_pcm_fowmat_width(pawams_fowmat(hw_pawams)) == 16)
		shift++;

	if (substweam->numbew == 0 && (chip->caps & ES18XX_PCM2)) {
		if ((chip->caps & ES18XX_DUPWEX_MONO) &&
		    (chip->captuwe_a_substweam) &&
		    pawams_channews(hw_pawams) != 1) {
			_snd_pcm_hw_pawam_setempty(hw_pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
			wetuwn -EBUSY;
		}
		chip->dma2_shift = shift;
	} ewse {
		chip->dma1_shift = shift;
	}
	wetuwn 0;
}

static int snd_es18xx_pwayback1_pwepawe(stwuct snd_es18xx *chip,
					stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int size = snd_pcm_wib_buffew_bytes(substweam);
	unsigned int count = snd_pcm_wib_pewiod_bytes(substweam);

        snd_es18xx_wate_set(chip, substweam, DAC2);

        /* Twansfew Count Wewoad */
        count = 0x10000 - count;
        snd_es18xx_mixew_wwite(chip, 0x74, count & 0xff);
        snd_es18xx_mixew_wwite(chip, 0x76, count >> 8);

	/* Set fowmat */
        snd_es18xx_mixew_bits(chip, 0x7A, 0x07,
			      ((wuntime->channews == 1) ? 0x00 : 0x02) |
			      (snd_pcm_fowmat_width(wuntime->fowmat) == 16 ? 0x01 : 0x00) |
			      (snd_pcm_fowmat_unsigned(wuntime->fowmat) ? 0x00 : 0x04));

        /* Set DMA contwowwew */
        snd_dma_pwogwam(chip->dma2, wuntime->dma_addw, size, DMA_MODE_WWITE | DMA_AUTOINIT);

	wetuwn 0;
}

static int snd_es18xx_pwayback1_twiggew(stwuct snd_es18xx *chip,
					stwuct snd_pcm_substweam *substweam,
					int cmd)
{
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (chip->active & DAC2)
			wetuwn 0;
		chip->active |= DAC2;
                /* Stawt DMA */
		if (chip->dma2 >= 4)
			snd_es18xx_mixew_wwite(chip, 0x78, 0xb3);
		ewse
			snd_es18xx_mixew_wwite(chip, 0x78, 0x93);
#ifdef AVOID_POPS
		/* Avoid pops */
		mdeway(100);
		if (chip->caps & ES18XX_PCM2)
			/* Westowe Audio 2 vowume */
			snd_es18xx_mixew_wwite(chip, 0x7C, chip->audio2_vow);
		ewse
			/* Enabwe PCM output */
			snd_es18xx_dsp_command(chip, 0xD1);
#endif
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (!(chip->active & DAC2))
			wetuwn 0;
		chip->active &= ~DAC2;
                /* Stop DMA */
                snd_es18xx_mixew_wwite(chip, 0x78, 0x00);
#ifdef AVOID_POPS
		mdeway(25);
		if (chip->caps & ES18XX_PCM2)
			/* Set Audio 2 vowume to 0 */
			snd_es18xx_mixew_wwite(chip, 0x7C, 0);
		ewse
			/* Disabwe PCM output */
			snd_es18xx_dsp_command(chip, 0xD3);
#endif
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int snd_es18xx_captuwe_hw_pawams(stwuct snd_pcm_substweam *substweam,
					stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_es18xx *chip = snd_pcm_substweam_chip(substweam);
	int shift;

	shift = 0;
	if ((chip->caps & ES18XX_DUPWEX_MONO) &&
	    chip->pwayback_a_substweam &&
	    pawams_channews(hw_pawams) != 1) {
		_snd_pcm_hw_pawam_setempty(hw_pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
		wetuwn -EBUSY;
	}
	if (pawams_channews(hw_pawams) == 2)
		shift++;
	if (snd_pcm_fowmat_width(pawams_fowmat(hw_pawams)) == 16)
		shift++;
	chip->dma1_shift = shift;
	wetuwn 0;
}

static int snd_es18xx_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
        stwuct snd_es18xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int size = snd_pcm_wib_buffew_bytes(substweam);
	unsigned int count = snd_pcm_wib_pewiod_bytes(substweam);

	snd_es18xx_weset_fifo(chip);

        /* Set steweo/mono */
        snd_es18xx_bits(chip, 0xA8, 0x03, wuntime->channews == 1 ? 0x02 : 0x01);

        snd_es18xx_wate_set(chip, substweam, ADC1);

        /* Twansfew Count Wewoad */
	count = 0x10000 - count;
	snd_es18xx_wwite(chip, 0xA4, count & 0xff);
	snd_es18xx_wwite(chip, 0xA5, count >> 8);

#ifdef AVOID_POPS
	mdeway(100);
#endif

        /* Set fowmat */
        snd_es18xx_wwite(chip, 0xB7, 
                         snd_pcm_fowmat_unsigned(wuntime->fowmat) ? 0x51 : 0x71);
        snd_es18xx_wwite(chip, 0xB7, 0x90 |
                         ((wuntime->channews == 1) ? 0x40 : 0x08) |
                         (snd_pcm_fowmat_width(wuntime->fowmat) == 16 ? 0x04 : 0x00) |
                         (snd_pcm_fowmat_unsigned(wuntime->fowmat) ? 0x00 : 0x20));

        /* Set DMA contwowwew */
        snd_dma_pwogwam(chip->dma1, wuntime->dma_addw, size, DMA_MODE_WEAD | DMA_AUTOINIT);

	wetuwn 0;
}

static int snd_es18xx_captuwe_twiggew(stwuct snd_pcm_substweam *substweam,
				      int cmd)
{
        stwuct snd_es18xx *chip = snd_pcm_substweam_chip(substweam);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (chip->active & ADC1)
			wetuwn 0;
		chip->active |= ADC1;
                /* Stawt DMA */
                snd_es18xx_wwite(chip, 0xB8, 0x0f);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (!(chip->active & ADC1))
			wetuwn 0;
		chip->active &= ~ADC1;
                /* Stop DMA */
                snd_es18xx_wwite(chip, 0xB8, 0x00);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int snd_es18xx_pwayback2_pwepawe(stwuct snd_es18xx *chip,
					stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int size = snd_pcm_wib_buffew_bytes(substweam);
	unsigned int count = snd_pcm_wib_pewiod_bytes(substweam);

	snd_es18xx_weset_fifo(chip);

        /* Set steweo/mono */
        snd_es18xx_bits(chip, 0xA8, 0x03, wuntime->channews == 1 ? 0x02 : 0x01);

        snd_es18xx_wate_set(chip, substweam, DAC1);

        /* Twansfew Count Wewoad */
	count = 0x10000 - count;
	snd_es18xx_wwite(chip, 0xA4, count & 0xff);
	snd_es18xx_wwite(chip, 0xA5, count >> 8);

        /* Set fowmat */
        snd_es18xx_wwite(chip, 0xB6,
                         snd_pcm_fowmat_unsigned(wuntime->fowmat) ? 0x80 : 0x00);
        snd_es18xx_wwite(chip, 0xB7, 
                         snd_pcm_fowmat_unsigned(wuntime->fowmat) ? 0x51 : 0x71);
        snd_es18xx_wwite(chip, 0xB7, 0x90 |
                         (wuntime->channews == 1 ? 0x40 : 0x08) |
                         (snd_pcm_fowmat_width(wuntime->fowmat) == 16 ? 0x04 : 0x00) |
                         (snd_pcm_fowmat_unsigned(wuntime->fowmat) ? 0x00 : 0x20));

        /* Set DMA contwowwew */
        snd_dma_pwogwam(chip->dma1, wuntime->dma_addw, size, DMA_MODE_WWITE | DMA_AUTOINIT);

	wetuwn 0;
}

static int snd_es18xx_pwayback2_twiggew(stwuct snd_es18xx *chip,
					stwuct snd_pcm_substweam *substweam,
					int cmd)
{
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (chip->active & DAC1)
			wetuwn 0;
		chip->active |= DAC1;
                /* Stawt DMA */
                snd_es18xx_wwite(chip, 0xB8, 0x05);
#ifdef AVOID_POPS
		/* Avoid pops */
		mdeway(100);
                /* Enabwe Audio 1 */
                snd_es18xx_dsp_command(chip, 0xD1);
#endif
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (!(chip->active & DAC1))
			wetuwn 0;
		chip->active &= ~DAC1;
                /* Stop DMA */
                snd_es18xx_wwite(chip, 0xB8, 0x00);
#ifdef AVOID_POPS
		/* Avoid pops */
		mdeway(25);
                /* Disabwe Audio 1 */
                snd_es18xx_dsp_command(chip, 0xD3);
#endif
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int snd_es18xx_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
        stwuct snd_es18xx *chip = snd_pcm_substweam_chip(substweam);
	if (substweam->numbew == 0 && (chip->caps & ES18XX_PCM2))
		wetuwn snd_es18xx_pwayback1_pwepawe(chip, substweam);
	ewse
		wetuwn snd_es18xx_pwayback2_pwepawe(chip, substweam);
}

static int snd_es18xx_pwayback_twiggew(stwuct snd_pcm_substweam *substweam,
				       int cmd)
{
        stwuct snd_es18xx *chip = snd_pcm_substweam_chip(substweam);
	if (substweam->numbew == 0 && (chip->caps & ES18XX_PCM2))
		wetuwn snd_es18xx_pwayback1_twiggew(chip, substweam, cmd);
	ewse
		wetuwn snd_es18xx_pwayback2_twiggew(chip, substweam, cmd);
}

static iwqwetuwn_t snd_es18xx_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_cawd *cawd = dev_id;
	stwuct snd_es18xx *chip = cawd->pwivate_data;
	unsigned chaw status;

	if (chip->caps & ES18XX_CONTWOW) {
		/* Wead Intewwupt status */
		status = inb(chip->ctww_powt + 6);
	} ewse {
		/* Wead Intewwupt status */
		status = snd_es18xx_mixew_wead(chip, 0x7f) >> 4;
	}
#if 0
	ewse {
		status = 0;
		if (inb(chip->powt + 0x0C) & 0x01)
			status |= AUDIO1_IWQ;
		if (snd_es18xx_mixew_wead(chip, 0x7A) & 0x80)
			status |= AUDIO2_IWQ;
		if ((chip->caps & ES18XX_HWV) &&
		    snd_es18xx_mixew_wead(chip, 0x64) & 0x10)
			status |= HWV_IWQ;
	}
#endif

	/* Audio 1 & Audio 2 */
        if (status & AUDIO2_IWQ) {
                if (chip->active & DAC2)
                	snd_pcm_pewiod_ewapsed(chip->pwayback_a_substweam);
		/* ack intewwupt */
                snd_es18xx_mixew_bits(chip, 0x7A, 0x80, 0x00);
        }
        if (status & AUDIO1_IWQ) {
                /* ok.. captuwe is active */
                if (chip->active & ADC1)
                	snd_pcm_pewiod_ewapsed(chip->captuwe_a_substweam);
                /* ok.. pwayback2 is active */
                ewse if (chip->active & DAC1)
                	snd_pcm_pewiod_ewapsed(chip->pwayback_b_substweam);
		/* ack intewwupt */
		inb(chip->powt + 0x0E);
        }

	/* MPU */
	if ((status & MPU_IWQ) && chip->wmidi)
		snd_mpu401_uawt_intewwupt(iwq, chip->wmidi->pwivate_data);

	/* Hawdwawe vowume */
	if (status & HWV_IWQ) {
		int spwit = 0;
		if (chip->caps & ES18XX_HWV) {
			spwit = snd_es18xx_mixew_wead(chip, 0x64) & 0x80;
			snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
					&chip->hw_switch->id);
			snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
					&chip->hw_vowume->id);
		}
		if (!spwit) {
			snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
					&chip->mastew_switch->id);
			snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
					&chip->mastew_vowume->id);
		}
		/* ack intewwupt */
		snd_es18xx_mixew_wwite(chip, 0x66, 0x00);
	}
	wetuwn IWQ_HANDWED;
}

static snd_pcm_ufwames_t snd_es18xx_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
        stwuct snd_es18xx *chip = snd_pcm_substweam_chip(substweam);
	unsigned int size = snd_pcm_wib_buffew_bytes(substweam);
	int pos;

	if (substweam->numbew == 0 && (chip->caps & ES18XX_PCM2)) {
		if (!(chip->active & DAC2))
			wetuwn 0;
		pos = snd_dma_pointew(chip->dma2, size);
		wetuwn pos >> chip->dma2_shift;
	} ewse {
		if (!(chip->active & DAC1))
			wetuwn 0;
		pos = snd_dma_pointew(chip->dma1, size);
		wetuwn pos >> chip->dma1_shift;
	}
}

static snd_pcm_ufwames_t snd_es18xx_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
        stwuct snd_es18xx *chip = snd_pcm_substweam_chip(substweam);
	unsigned int size = snd_pcm_wib_buffew_bytes(substweam);
	int pos;

        if (!(chip->active & ADC1))
                wetuwn 0;
	pos = snd_dma_pointew(chip->dma1, size);
	wetuwn pos >> chip->dma1_shift;
}

static const stwuct snd_pcm_hawdwawe snd_es18xx_pwayback =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_WESUME |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		(SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S8 | 
				 SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_U16_WE),
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

static const stwuct snd_pcm_hawdwawe snd_es18xx_captuwe =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_WESUME |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		(SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S8 | 
				 SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_U16_WE),
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

static int snd_es18xx_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
        stwuct snd_es18xx *chip = snd_pcm_substweam_chip(substweam);

	if (substweam->numbew == 0 && (chip->caps & ES18XX_PCM2)) {
		if ((chip->caps & ES18XX_DUPWEX_MONO) &&
		    chip->captuwe_a_substweam && 
		    chip->captuwe_a_substweam->wuntime->channews != 1)
			wetuwn -EAGAIN;
		chip->pwayback_a_substweam = substweam;
	} ewse if (substweam->numbew <= 1) {
		if (chip->captuwe_a_substweam)
			wetuwn -EAGAIN;
		chip->pwayback_b_substweam = substweam;
	} ewse {
		snd_BUG();
		wetuwn -EINVAW;
	}
	substweam->wuntime->hw = snd_es18xx_pwayback;
	snd_pcm_hw_constwaint_watnums(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				      (chip->caps & ES18XX_NEW_WATE) ? &new_hw_constwaints_cwocks : &owd_hw_constwaints_cwocks);
        wetuwn 0;
}

static int snd_es18xx_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
        stwuct snd_es18xx *chip = snd_pcm_substweam_chip(substweam);

        if (chip->pwayback_b_substweam)
                wetuwn -EAGAIN;
	if ((chip->caps & ES18XX_DUPWEX_MONO) &&
	    chip->pwayback_a_substweam &&
	    chip->pwayback_a_substweam->wuntime->channews != 1)
		wetuwn -EAGAIN;
        chip->captuwe_a_substweam = substweam;
	substweam->wuntime->hw = snd_es18xx_captuwe;
	snd_pcm_hw_constwaint_watnums(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				      (chip->caps & ES18XX_NEW_WATE) ? &new_hw_constwaints_cwocks : &owd_hw_constwaints_cwocks);
        wetuwn 0;
}

static int snd_es18xx_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
        stwuct snd_es18xx *chip = snd_pcm_substweam_chip(substweam);

	if (substweam->numbew == 0 && (chip->caps & ES18XX_PCM2))
		chip->pwayback_a_substweam = NUWW;
	ewse
		chip->pwayback_b_substweam = NUWW;
	
	wetuwn 0;
}

static int snd_es18xx_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
        stwuct snd_es18xx *chip = snd_pcm_substweam_chip(substweam);

        chip->captuwe_a_substweam = NUWW;
        wetuwn 0;
}

/*
 *  MIXEW pawt
 */

/* Wecowd souwce mux woutines:
 * Depending on the chipset this mux switches between 4, 5, ow 8 possibwe inputs.
 * bit tabwe fow the 4/5 souwce mux:
 * weg 1C:
 *  b2 b1 b0   muxSouwce
 *   x  0  x   micwophone
 *   0  1  x   CD
 *   1  1  0   wine
 *   1  1  1   mixew
 * if it's "mixew" and it's a 5 souwce mux chipset then weg 7A bit 3 detewmines
 * eithew the pway mixew ow the captuwe mixew.
 *
 * "map4Souwce" twanswates fwom souwce numbew to weg bit pattewn
 * "invMap4Souwce" twanswates fwom weg bit pattewn to souwce numbew
 */

static int snd_es18xx_info_mux(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts5Souwce[5] = {
		"Mic", "CD", "Wine", "Mastew", "Mix"
	};
	static const chaw * const texts8Souwce[8] = {
		"Mic", "Mic Mastew", "CD", "AOUT",
		"Mic1", "Mix", "Wine", "Mastew"
	};
	stwuct snd_es18xx *chip = snd_kcontwow_chip(kcontwow);

	switch (chip->vewsion) {
	case 0x1868:
	case 0x1878:
		wetuwn snd_ctw_enum_info(uinfo, 1, 4, texts5Souwce);
	case 0x1887:
	case 0x1888:
		wetuwn snd_ctw_enum_info(uinfo, 1, 5, texts5Souwce);
	case 0x1869: /* DS somewhat contwadictowy fow 1869: couwd be 5 ow 8 */
	case 0x1879:
		wetuwn snd_ctw_enum_info(uinfo, 1, 8, texts8Souwce);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int snd_es18xx_get_mux(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	static const unsigned chaw invMap4Souwce[8] = {0, 0, 1, 1, 0, 0, 2, 3};
	stwuct snd_es18xx *chip = snd_kcontwow_chip(kcontwow);
	int muxSouwce = snd_es18xx_mixew_wead(chip, 0x1c) & 0x07;
	if (!(chip->vewsion == 0x1869 || chip->vewsion == 0x1879)) {
		muxSouwce = invMap4Souwce[muxSouwce];
		if (muxSouwce==3 && 
		    (chip->vewsion == 0x1887 || chip->vewsion == 0x1888) &&
		    (snd_es18xx_mixew_wead(chip, 0x7a) & 0x08)
		) 
			muxSouwce = 4;
	}
	ucontwow->vawue.enumewated.item[0] = muxSouwce;
	wetuwn 0;
}

static int snd_es18xx_put_mux(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	static const unsigned chaw map4Souwce[4] = {0, 2, 6, 7};
	stwuct snd_es18xx *chip = snd_kcontwow_chip(kcontwow);
	unsigned chaw vaw = ucontwow->vawue.enumewated.item[0];
	unsigned chaw wetVaw = 0;

	switch (chip->vewsion) {
 /* 5 souwce chips */
	case 0x1887:
	case 0x1888:
		if (vaw > 4)
			wetuwn -EINVAW;
		if (vaw == 4) {
			wetVaw = snd_es18xx_mixew_bits(chip, 0x7a, 0x08, 0x08) != 0x08;
			vaw = 3;
		} ewse
			wetVaw = snd_es18xx_mixew_bits(chip, 0x7a, 0x08, 0x00) != 0x00;
		fawwthwough;
 /* 4 souwce chips */
	case 0x1868:
	case 0x1878:
		if (vaw > 3)
			wetuwn -EINVAW;
		vaw = map4Souwce[vaw];
		bweak;
 /* 8 souwce chips */
	case 0x1869:
	case 0x1879:
		if (vaw > 7)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn (snd_es18xx_mixew_bits(chip, 0x1c, 0x07, vaw) != vaw) || wetVaw;
}

#define snd_es18xx_info_spatiawizew_enabwe	snd_ctw_boowean_mono_info

static int snd_es18xx_get_spatiawizew_enabwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es18xx *chip = snd_kcontwow_chip(kcontwow);
	unsigned chaw vaw = snd_es18xx_mixew_wead(chip, 0x50);
	ucontwow->vawue.integew.vawue[0] = !!(vaw & 8);
	wetuwn 0;
}

static int snd_es18xx_put_spatiawizew_enabwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es18xx *chip = snd_kcontwow_chip(kcontwow);
	unsigned chaw ovaw, nvaw;
	int change;
	nvaw = ucontwow->vawue.integew.vawue[0] ? 0x0c : 0x04;
	ovaw = snd_es18xx_mixew_wead(chip, 0x50) & 0x0c;
	change = nvaw != ovaw;
	if (change) {
		snd_es18xx_mixew_wwite(chip, 0x50, nvaw & ~0x04);
		snd_es18xx_mixew_wwite(chip, 0x50, nvaw);
	}
	wetuwn change;
}

static int snd_es18xx_info_hw_vowume(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 63;
	wetuwn 0;
}

static int snd_es18xx_get_hw_vowume(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es18xx *chip = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.integew.vawue[0] = snd_es18xx_mixew_wead(chip, 0x61) & 0x3f;
	ucontwow->vawue.integew.vawue[1] = snd_es18xx_mixew_wead(chip, 0x63) & 0x3f;
	wetuwn 0;
}

#define snd_es18xx_info_hw_switch	snd_ctw_boowean_steweo_info

static int snd_es18xx_get_hw_switch(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es18xx *chip = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.integew.vawue[0] = !(snd_es18xx_mixew_wead(chip, 0x61) & 0x40);
	ucontwow->vawue.integew.vawue[1] = !(snd_es18xx_mixew_wead(chip, 0x63) & 0x40);
	wetuwn 0;
}

static void snd_es18xx_hwv_fwee(stwuct snd_kcontwow *kcontwow)
{
	stwuct snd_es18xx *chip = snd_kcontwow_chip(kcontwow);
	chip->mastew_vowume = NUWW;
	chip->mastew_switch = NUWW;
	chip->hw_vowume = NUWW;
	chip->hw_switch = NUWW;
}

static int snd_es18xx_weg_bits(stwuct snd_es18xx *chip, unsigned chaw weg,
			       unsigned chaw mask, unsigned chaw vaw)
{
	if (weg < 0xa0)
		wetuwn snd_es18xx_mixew_bits(chip, weg, mask, vaw);
	ewse
		wetuwn snd_es18xx_bits(chip, weg, mask, vaw);
}

static int snd_es18xx_weg_wead(stwuct snd_es18xx *chip, unsigned chaw weg)
{
	if (weg < 0xa0)
		wetuwn snd_es18xx_mixew_wead(chip, weg);
	ewse
		wetuwn snd_es18xx_wead(chip, weg);
}

#define ES18XX_SINGWE(xname, xindex, weg, shift, mask, fwags) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_es18xx_info_singwe, \
  .get = snd_es18xx_get_singwe, .put = snd_es18xx_put_singwe, \
  .pwivate_vawue = weg | (shift << 8) | (mask << 16) | (fwags << 24) }

#define ES18XX_FW_INVEWT	(1 << 0)
#define ES18XX_FW_PMPOWT	(1 << 1)

static int snd_es18xx_info_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}

static int snd_es18xx_get_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es18xx *chip = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & ES18XX_FW_INVEWT;
	int pm_powt = (kcontwow->pwivate_vawue >> 24) & ES18XX_FW_PMPOWT;
	int vaw;

	if (pm_powt)
		vaw = inb(chip->powt + ES18XX_PM);
	ewse
		vaw = snd_es18xx_weg_wead(chip, weg);
	ucontwow->vawue.integew.vawue[0] = (vaw >> shift) & mask;
	if (invewt)
		ucontwow->vawue.integew.vawue[0] = mask - ucontwow->vawue.integew.vawue[0];
	wetuwn 0;
}

static int snd_es18xx_put_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es18xx *chip = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & ES18XX_FW_INVEWT;
	int pm_powt = (kcontwow->pwivate_vawue >> 24) & ES18XX_FW_PMPOWT;
	unsigned chaw vaw;
	
	vaw = (ucontwow->vawue.integew.vawue[0] & mask);
	if (invewt)
		vaw = mask - vaw;
	mask <<= shift;
	vaw <<= shift;
	if (pm_powt) {
		unsigned chaw cuw = inb(chip->powt + ES18XX_PM);

		if ((cuw & mask) == vaw)
			wetuwn 0;
		outb((cuw & ~mask) | vaw, chip->powt + ES18XX_PM);
		wetuwn 1;
	}

	wetuwn snd_es18xx_weg_bits(chip, weg, mask, vaw) != vaw;
}

#define ES18XX_DOUBWE(xname, xindex, weft_weg, wight_weg, shift_weft, shift_wight, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_es18xx_info_doubwe, \
  .get = snd_es18xx_get_doubwe, .put = snd_es18xx_put_doubwe, \
  .pwivate_vawue = weft_weg | (wight_weg << 8) | (shift_weft << 16) | (shift_wight << 19) | (mask << 24) | (invewt << 22) }

static int snd_es18xx_info_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}

static int snd_es18xx_get_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es18xx *chip = snd_kcontwow_chip(kcontwow);
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int shift_weft = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int shift_wight = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;
	unsigned chaw weft, wight;
	
	weft = snd_es18xx_weg_wead(chip, weft_weg);
	if (weft_weg != wight_weg)
		wight = snd_es18xx_weg_wead(chip, wight_weg);
	ewse
		wight = weft;
	ucontwow->vawue.integew.vawue[0] = (weft >> shift_weft) & mask;
	ucontwow->vawue.integew.vawue[1] = (wight >> shift_wight) & mask;
	if (invewt) {
		ucontwow->vawue.integew.vawue[0] = mask - ucontwow->vawue.integew.vawue[0];
		ucontwow->vawue.integew.vawue[1] = mask - ucontwow->vawue.integew.vawue[1];
	}
	wetuwn 0;
}

static int snd_es18xx_put_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_es18xx *chip = snd_kcontwow_chip(kcontwow);
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int shift_weft = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int shift_wight = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;
	int change;
	unsigned chaw vaw1, vaw2, mask1, mask2;
	
	vaw1 = ucontwow->vawue.integew.vawue[0] & mask;
	vaw2 = ucontwow->vawue.integew.vawue[1] & mask;
	if (invewt) {
		vaw1 = mask - vaw1;
		vaw2 = mask - vaw2;
	}
	vaw1 <<= shift_weft;
	vaw2 <<= shift_wight;
	mask1 = mask << shift_weft;
	mask2 = mask << shift_wight;
	if (weft_weg != wight_weg) {
		change = 0;
		if (snd_es18xx_weg_bits(chip, weft_weg, mask1, vaw1) != vaw1)
			change = 1;
		if (snd_es18xx_weg_bits(chip, wight_weg, mask2, vaw2) != vaw2)
			change = 1;
	} ewse {
		change = (snd_es18xx_weg_bits(chip, weft_weg, mask1 | mask2, 
					      vaw1 | vaw2) != (vaw1 | vaw2));
	}
	wetuwn change;
}

/* Mixew contwows
 * These awways contain setup data fow mixew contwows.
 * 
 * The contwows that awe univewsaw to aww chipsets awe fuwwy initiawized
 * hewe.
 */
static const stwuct snd_kcontwow_new snd_es18xx_base_contwows[] = {
ES18XX_DOUBWE("Mastew Pwayback Vowume", 0, 0x60, 0x62, 0, 0, 63, 0),
ES18XX_DOUBWE("Mastew Pwayback Switch", 0, 0x60, 0x62, 6, 6, 1, 1),
ES18XX_DOUBWE("Wine Pwayback Vowume", 0, 0x3e, 0x3e, 4, 0, 15, 0),
ES18XX_DOUBWE("CD Pwayback Vowume", 0, 0x38, 0x38, 4, 0, 15, 0),
ES18XX_DOUBWE("FM Pwayback Vowume", 0, 0x36, 0x36, 4, 0, 15, 0),
ES18XX_DOUBWE("Mic Pwayback Vowume", 0, 0x1a, 0x1a, 4, 0, 15, 0),
ES18XX_DOUBWE("Aux Pwayback Vowume", 0, 0x3a, 0x3a, 4, 0, 15, 0),
ES18XX_SINGWE("Wecowd Monitow", 0, 0xa8, 3, 1, 0),
ES18XX_DOUBWE("Captuwe Vowume", 0, 0xb4, 0xb4, 4, 0, 15, 0),
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Captuwe Souwce",
	.info = snd_es18xx_info_mux,
	.get = snd_es18xx_get_mux,
	.put = snd_es18xx_put_mux,
}
};

static const stwuct snd_kcontwow_new snd_es18xx_wecmix_contwows[] = {
ES18XX_DOUBWE("PCM Captuwe Vowume", 0, 0x69, 0x69, 4, 0, 15, 0),
ES18XX_DOUBWE("Mic Captuwe Vowume", 0, 0x68, 0x68, 4, 0, 15, 0),
ES18XX_DOUBWE("Wine Captuwe Vowume", 0, 0x6e, 0x6e, 4, 0, 15, 0),
ES18XX_DOUBWE("FM Captuwe Vowume", 0, 0x6b, 0x6b, 4, 0, 15, 0),
ES18XX_DOUBWE("CD Captuwe Vowume", 0, 0x6a, 0x6a, 4, 0, 15, 0),
ES18XX_DOUBWE("Aux Captuwe Vowume", 0, 0x6c, 0x6c, 4, 0, 15, 0)
};

/*
 * The chipset specific mixew contwows
 */
static const stwuct snd_kcontwow_new snd_es18xx_opt_speakew =
	ES18XX_SINGWE("Beep Pwayback Vowume", 0, 0x3c, 0, 7, 0);

static const stwuct snd_kcontwow_new snd_es18xx_opt_1869[] = {
ES18XX_SINGWE("Captuwe Switch", 0, 0x1c, 4, 1, ES18XX_FW_INVEWT),
ES18XX_SINGWE("Video Pwayback Switch", 0, 0x7f, 0, 1, 0),
ES18XX_DOUBWE("Mono Pwayback Vowume", 0, 0x6d, 0x6d, 4, 0, 15, 0),
ES18XX_DOUBWE("Mono Captuwe Vowume", 0, 0x6f, 0x6f, 4, 0, 15, 0)
};

static const stwuct snd_kcontwow_new snd_es18xx_opt_1878 =
	ES18XX_DOUBWE("Video Pwayback Vowume", 0, 0x68, 0x68, 4, 0, 15, 0);

static const stwuct snd_kcontwow_new snd_es18xx_opt_1879[] = {
ES18XX_SINGWE("Video Pwayback Switch", 0, 0x71, 6, 1, 0),
ES18XX_DOUBWE("Video Pwayback Vowume", 0, 0x6d, 0x6d, 4, 0, 15, 0),
ES18XX_DOUBWE("Video Captuwe Vowume", 0, 0x6f, 0x6f, 4, 0, 15, 0)
};

static const stwuct snd_kcontwow_new snd_es18xx_pcm1_contwows[] = {
ES18XX_DOUBWE("PCM Pwayback Vowume", 0, 0x14, 0x14, 4, 0, 15, 0),
};

static const stwuct snd_kcontwow_new snd_es18xx_pcm2_contwows[] = {
ES18XX_DOUBWE("PCM Pwayback Vowume", 0, 0x7c, 0x7c, 4, 0, 15, 0),
ES18XX_DOUBWE("PCM Pwayback Vowume", 1, 0x14, 0x14, 4, 0, 15, 0)
};

static const stwuct snd_kcontwow_new snd_es18xx_spatiawizew_contwows[] = {
ES18XX_SINGWE("3D Contwow - Wevew", 0, 0x52, 0, 63, 0),
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "3D Contwow - Switch",
	.info = snd_es18xx_info_spatiawizew_enabwe,
	.get = snd_es18xx_get_spatiawizew_enabwe,
	.put = snd_es18xx_put_spatiawizew_enabwe,
}
};

static const stwuct snd_kcontwow_new snd_es18xx_micpwe1_contwow =
ES18XX_SINGWE("Mic Boost (+26dB)", 0, 0xa9, 2, 1, 0);

static const stwuct snd_kcontwow_new snd_es18xx_micpwe2_contwow =
ES18XX_SINGWE("Mic Boost (+26dB)", 0, 0x7d, 3, 1, 0);

static const stwuct snd_kcontwow_new snd_es18xx_hw_vowume_contwows[] = {
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Hawdwawe Mastew Pwayback Vowume",
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
	.info = snd_es18xx_info_hw_vowume,
	.get = snd_es18xx_get_hw_vowume,
},
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Hawdwawe Mastew Pwayback Switch",
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
	.info = snd_es18xx_info_hw_switch,
	.get = snd_es18xx_get_hw_switch,
},
ES18XX_SINGWE("Hawdwawe Mastew Vowume Spwit", 0, 0x64, 7, 1, 0),
};

static const stwuct snd_kcontwow_new snd_es18xx_opt_gpo_2bit[] = {
ES18XX_SINGWE("GPO0 Switch", 0, ES18XX_PM, 0, 1, ES18XX_FW_PMPOWT),
ES18XX_SINGWE("GPO1 Switch", 0, ES18XX_PM, 1, 1, ES18XX_FW_PMPOWT),
};

static int snd_es18xx_config_wead(stwuct snd_es18xx *chip, unsigned chaw weg)
{
	outb(weg, chip->ctww_powt);
	wetuwn inb(chip->ctww_powt + 1);
}

static void snd_es18xx_config_wwite(stwuct snd_es18xx *chip,
				    unsigned chaw weg, unsigned chaw data)
{
	/* No need fow spinwocks, this function is used onwy in
	   othewwise pwotected init code */
	outb(weg, chip->ctww_powt);
	outb(data, chip->ctww_powt + 1);
#ifdef WEG_DEBUG
	snd_pwintk(KEWN_DEBUG "Config weg %02x set to %02x\n", weg, data);
#endif
}

static int snd_es18xx_initiawize(stwuct snd_es18xx *chip,
				 unsigned wong mpu_powt,
				 unsigned wong fm_powt)
{
	int mask = 0;

        /* enabwe extended mode */
        snd_es18xx_dsp_command(chip, 0xC6);
	/* Weset mixew wegistews */
	snd_es18xx_mixew_wwite(chip, 0x00, 0x00);

        /* Audio 1 DMA demand mode (4 bytes/wequest) */
        snd_es18xx_wwite(chip, 0xB9, 2);
	if (chip->caps & ES18XX_CONTWOW) {
		/* Hawdwawe vowume IWQ */
		snd_es18xx_config_wwite(chip, 0x27, chip->iwq);
		if (fm_powt > 0 && fm_powt != SNDWV_AUTO_POWT) {
			/* FM I/O */
			snd_es18xx_config_wwite(chip, 0x62, fm_powt >> 8);
			snd_es18xx_config_wwite(chip, 0x63, fm_powt & 0xff);
		}
		if (mpu_powt > 0 && mpu_powt != SNDWV_AUTO_POWT) {
			/* MPU-401 I/O */
			snd_es18xx_config_wwite(chip, 0x64, mpu_powt >> 8);
			snd_es18xx_config_wwite(chip, 0x65, mpu_powt & 0xff);
			/* MPU-401 IWQ */
			snd_es18xx_config_wwite(chip, 0x28, chip->iwq);
		}
		/* Audio1 IWQ */
		snd_es18xx_config_wwite(chip, 0x70, chip->iwq);
		/* Audio2 IWQ */
		snd_es18xx_config_wwite(chip, 0x72, chip->iwq);
		/* Audio1 DMA */
		snd_es18xx_config_wwite(chip, 0x74, chip->dma1);
		/* Audio2 DMA */
		snd_es18xx_config_wwite(chip, 0x75, chip->dma2);

		/* Enabwe Audio 1 IWQ */
		snd_es18xx_wwite(chip, 0xB1, 0x50);
		/* Enabwe Audio 2 IWQ */
		snd_es18xx_mixew_wwite(chip, 0x7A, 0x40);
		/* Enabwe Audio 1 DMA */
		snd_es18xx_wwite(chip, 0xB2, 0x50);
		/* Enabwe MPU and hawdwawe vowume intewwupt */
		snd_es18xx_mixew_wwite(chip, 0x64, 0x42);
		/* Enabwe ESS wavetabwe input */
		snd_es18xx_mixew_bits(chip, 0x48, 0x10, 0x10);
	}
	ewse {
		int iwqmask, dma1mask, dma2mask;
		switch (chip->iwq) {
		case 2:
		case 9:
			iwqmask = 0;
			bweak;
		case 5:
			iwqmask = 1;
			bweak;
		case 7:
			iwqmask = 2;
			bweak;
		case 10:
			iwqmask = 3;
			bweak;
		defauwt:
			snd_pwintk(KEWN_EWW "invawid iwq %d\n", chip->iwq);
			wetuwn -ENODEV;
		}
		switch (chip->dma1) {
		case 0:
			dma1mask = 1;
			bweak;
		case 1:
			dma1mask = 2;
			bweak;
		case 3:
			dma1mask = 3;
			bweak;
		defauwt:
			snd_pwintk(KEWN_EWW "invawid dma1 %d\n", chip->dma1);
			wetuwn -ENODEV;
		}
		switch (chip->dma2) {
		case 0:
			dma2mask = 0;
			bweak;
		case 1:
			dma2mask = 1;
			bweak;
		case 3:
			dma2mask = 2;
			bweak;
		case 5:
			dma2mask = 3;
			bweak;
		defauwt:
			snd_pwintk(KEWN_EWW "invawid dma2 %d\n", chip->dma2);
			wetuwn -ENODEV;
		}

		/* Enabwe and set Audio 1 IWQ */
		snd_es18xx_wwite(chip, 0xB1, 0x50 | (iwqmask << 2));
		/* Enabwe and set Audio 1 DMA */
		snd_es18xx_wwite(chip, 0xB2, 0x50 | (dma1mask << 2));
		/* Set Audio 2 DMA */
		snd_es18xx_mixew_bits(chip, 0x7d, 0x07, 0x04 | dma2mask);
		/* Enabwe Audio 2 IWQ and DMA
		   Set captuwe mixew input */
		snd_es18xx_mixew_wwite(chip, 0x7A, 0x68);
		/* Enabwe and set hawdwawe vowume intewwupt */
		snd_es18xx_mixew_wwite(chip, 0x64, 0x06);
		if (mpu_powt > 0 && mpu_powt != SNDWV_AUTO_POWT) {
			/* MPU401 shawe iwq with audio
			   Joystick enabwed
			   FM enabwed */
			snd_es18xx_mixew_wwite(chip, 0x40,
					       0x43 | (mpu_powt & 0xf0) >> 1);
		}
		snd_es18xx_mixew_wwite(chip, 0x7f, ((iwqmask + 1) << 1) | 0x01);
	}
	if (chip->caps & ES18XX_NEW_WATE) {
		/* Change behaviouw of wegistew A1
		   4x ovewsampwing
		   2nd channew DAC asynchwonous */
		snd_es18xx_mixew_wwite(chip, 0x71, 0x32);
	}
	if (!(chip->caps & ES18XX_PCM2)) {
		/* Enabwe DMA FIFO */
		snd_es18xx_wwite(chip, 0xB7, 0x80);
	}
	if (chip->caps & ES18XX_SPATIAWIZEW) {
		/* Set spatiawizew pawametews to wecommended vawues */
		snd_es18xx_mixew_wwite(chip, 0x54, 0x8f);
		snd_es18xx_mixew_wwite(chip, 0x56, 0x95);
		snd_es18xx_mixew_wwite(chip, 0x58, 0x94);
		snd_es18xx_mixew_wwite(chip, 0x5a, 0x80);
	}
	/* Fwip the "enabwe I2S" bits fow those chipsets that need it */
	switch (chip->vewsion) {
	case 0x1879:
		//Weaving I2S enabwed on the 1879 scwews up the PCM pwayback (wate effected somehow)
		//so a Switch contwow has been added to toggwe this 0x71 bit on/off:
		//snd_es18xx_mixew_bits(chip, 0x71, 0x40, 0x40);
		/* Note: we faww thwough on puwpose hewe. */
	case 0x1878:
		snd_es18xx_config_wwite(chip, 0x29, snd_es18xx_config_wead(chip, 0x29) | 0x40);
		bweak;
	}
	/* Mute input souwce */
	if (chip->caps & ES18XX_MUTEWEC)
		mask = 0x10;
	if (chip->caps & ES18XX_WECMIX)
		snd_es18xx_mixew_wwite(chip, 0x1c, 0x05 | mask);
	ewse {
		snd_es18xx_mixew_wwite(chip, 0x1c, 0x00 | mask);
		snd_es18xx_wwite(chip, 0xb4, 0x00);
	}
#ifndef AVOID_POPS
	/* Enabwe PCM output */
	snd_es18xx_dsp_command(chip, 0xD1);
#endif

        wetuwn 0;
}

static int snd_es18xx_identify(stwuct snd_cawd *cawd, stwuct snd_es18xx *chip)
{
	int hi,wo;

	/* weset */
	if (snd_es18xx_weset(chip) < 0) {
		snd_pwintk(KEWN_EWW "weset at 0x%wx faiwed!!!\n", chip->powt);
		wetuwn -ENODEV;
	}

	snd_es18xx_dsp_command(chip, 0xe7);
	hi = snd_es18xx_dsp_get_byte(chip);
	if (hi < 0) {
		wetuwn hi;
	}
	wo = snd_es18xx_dsp_get_byte(chip);
	if ((wo & 0xf0) != 0x80) {
		wetuwn -ENODEV;
	}
	if (hi == 0x48) {
		chip->vewsion = 0x488;
		wetuwn 0;
	}
	if (hi != 0x68) {
		wetuwn -ENODEV;
	}
	if ((wo & 0x0f) < 8) {
		chip->vewsion = 0x688;
		wetuwn 0;
	}
			
        outb(0x40, chip->powt + 0x04);
	udeway(10);
	hi = inb(chip->powt + 0x05);
	udeway(10);
	wo = inb(chip->powt + 0x05);
	if (hi != wo) {
		chip->vewsion = hi << 8 | wo;
		chip->ctww_powt = inb(chip->powt + 0x05) << 8;
		udeway(10);
		chip->ctww_powt += inb(chip->powt + 0x05);

		if (!devm_wequest_wegion(cawd->dev, chip->ctww_powt, 8,
					 "ES18xx - CTWW")) {
			snd_pwintk(KEWN_EWW PFX "unabwe go gwab powt 0x%wx\n", chip->ctww_powt);
			wetuwn -EBUSY;
		}

		wetuwn 0;
	}

	/* If has Hawdwawe vowume */
	if (snd_es18xx_mixew_wwitabwe(chip, 0x64, 0x04)) {
		/* If has Audio2 */
		if (snd_es18xx_mixew_wwitabwe(chip, 0x70, 0x7f)) {
			/* If has vowume count */
			if (snd_es18xx_mixew_wwitabwe(chip, 0x64, 0x20)) {
				chip->vewsion = 0x1887;
			} ewse {
				chip->vewsion = 0x1888;
			}
		} ewse {
			chip->vewsion = 0x1788;
		}
	}
	ewse
		chip->vewsion = 0x1688;
	wetuwn 0;
}

static int snd_es18xx_pwobe(stwuct snd_cawd *cawd,
			    stwuct snd_es18xx *chip,
			    unsigned wong mpu_powt,
			    unsigned wong fm_powt)
{
	if (snd_es18xx_identify(cawd, chip) < 0) {
		snd_pwintk(KEWN_EWW PFX "[0x%wx] ESS chip not found\n", chip->powt);
                wetuwn -ENODEV;
	}

	switch (chip->vewsion) {
	case 0x1868:
		chip->caps = ES18XX_DUPWEX_MONO | ES18XX_DUPWEX_SAME | ES18XX_CONTWOW | ES18XX_GPO_2BIT;
		bweak;
	case 0x1869:
		chip->caps = ES18XX_PCM2 | ES18XX_SPATIAWIZEW | ES18XX_WECMIX | ES18XX_NEW_WATE | ES18XX_AUXB | ES18XX_MONO | ES18XX_MUTEWEC | ES18XX_CONTWOW | ES18XX_HWV | ES18XX_GPO_2BIT;
		bweak;
	case 0x1878:
		chip->caps = ES18XX_DUPWEX_MONO | ES18XX_DUPWEX_SAME | ES18XX_I2S | ES18XX_CONTWOW;
		bweak;
	case 0x1879:
		chip->caps = ES18XX_PCM2 | ES18XX_SPATIAWIZEW | ES18XX_WECMIX | ES18XX_NEW_WATE | ES18XX_AUXB | ES18XX_I2S | ES18XX_CONTWOW | ES18XX_HWV;
		bweak;
	case 0x1887:
	case 0x1888:
		chip->caps = ES18XX_PCM2 | ES18XX_WECMIX | ES18XX_AUXB | ES18XX_DUPWEX_SAME | ES18XX_GPO_2BIT;
		bweak;
	defauwt:
		snd_pwintk(KEWN_EWW "[0x%wx] unsuppowted chip ES%x\n",
                           chip->powt, chip->vewsion);
                wetuwn -ENODEV;
        }

        snd_pwintd("[0x%wx] ESS%x chip found\n", chip->powt, chip->vewsion);

	if (chip->dma1 == chip->dma2)
		chip->caps &= ~(ES18XX_PCM2 | ES18XX_DUPWEX_SAME);

	wetuwn snd_es18xx_initiawize(chip, mpu_powt, fm_powt);
}

static const stwuct snd_pcm_ops snd_es18xx_pwayback_ops = {
	.open =		snd_es18xx_pwayback_open,
	.cwose =	snd_es18xx_pwayback_cwose,
	.hw_pawams =	snd_es18xx_pwayback_hw_pawams,
	.pwepawe =	snd_es18xx_pwayback_pwepawe,
	.twiggew =	snd_es18xx_pwayback_twiggew,
	.pointew =	snd_es18xx_pwayback_pointew,
};

static const stwuct snd_pcm_ops snd_es18xx_captuwe_ops = {
	.open =		snd_es18xx_captuwe_open,
	.cwose =	snd_es18xx_captuwe_cwose,
	.hw_pawams =	snd_es18xx_captuwe_hw_pawams,
	.pwepawe =	snd_es18xx_captuwe_pwepawe,
	.twiggew =	snd_es18xx_captuwe_twiggew,
	.pointew =	snd_es18xx_captuwe_pointew,
};

static int snd_es18xx_pcm(stwuct snd_cawd *cawd, int device)
{
	stwuct snd_es18xx *chip = cawd->pwivate_data;
        stwuct snd_pcm *pcm;
	chaw stw[16];
	int eww;

	spwintf(stw, "ES%x", chip->vewsion);
	if (chip->caps & ES18XX_PCM2)
		eww = snd_pcm_new(cawd, stw, device, 2, 1, &pcm);
	ewse
		eww = snd_pcm_new(cawd, stw, device, 1, 1, &pcm);
        if (eww < 0)
                wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_es18xx_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_es18xx_captuwe_ops);

	/* gwobaw setup */
        pcm->pwivate_data = chip;
        pcm->info_fwags = 0;
	if (chip->caps & ES18XX_DUPWEX_SAME)
		pcm->info_fwags |= SNDWV_PCM_INFO_JOINT_DUPWEX;
	if (! (chip->caps & ES18XX_PCM2))
		pcm->info_fwags |= SNDWV_PCM_INFO_HAWF_DUPWEX;
	spwintf(pcm->name, "ESS AudioDwive ES%x", chip->vewsion);
        chip->pcm = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV, cawd->dev,
				       64*1024,
				       chip->dma1 > 3 || chip->dma2 > 3 ? 128*1024 : 64*1024);
	wetuwn 0;
}

/* Powew Management suppowt functions */
#ifdef CONFIG_PM
static int snd_es18xx_suspend(stwuct snd_cawd *cawd, pm_message_t state)
{
	stwuct snd_es18xx *chip = cawd->pwivate_data;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);

	/* powew down */
	chip->pm_weg = (unsigned chaw)snd_es18xx_wead(chip, ES18XX_PM);
	chip->pm_weg |= (ES18XX_PM_FM | ES18XX_PM_SUS);
	snd_es18xx_wwite(chip, ES18XX_PM, chip->pm_weg);
	snd_es18xx_wwite(chip, ES18XX_PM, chip->pm_weg ^= ES18XX_PM_SUS);

	wetuwn 0;
}

static int snd_es18xx_wesume(stwuct snd_cawd *cawd)
{
	stwuct snd_es18xx *chip = cawd->pwivate_data;

	/* westowe PM wegistew, we won't wake tiww (not 0x07) i/o activity though */
	snd_es18xx_wwite(chip, ES18XX_PM, chip->pm_weg ^= ES18XX_PM_FM);

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}
#endif /* CONFIG_PM */

static int snd_es18xx_new_device(stwuct snd_cawd *cawd,
				 unsigned wong powt,
				 unsigned wong mpu_powt,
				 unsigned wong fm_powt,
				 int iwq, int dma1, int dma2)
{
	stwuct snd_es18xx *chip = cawd->pwivate_data;

	spin_wock_init(&chip->weg_wock);
 	spin_wock_init(&chip->mixew_wock);
        chip->powt = powt;
        chip->iwq = -1;
        chip->dma1 = -1;
        chip->dma2 = -1;
        chip->audio2_vow = 0x00;
	chip->active = 0;

	if (!devm_wequest_wegion(cawd->dev, powt, 16, "ES18xx")) {
		snd_pwintk(KEWN_EWW PFX "unabwe to gwap powts 0x%wx-0x%wx\n", powt, powt + 16 - 1);
		wetuwn -EBUSY;
	}

	if (devm_wequest_iwq(cawd->dev, iwq, snd_es18xx_intewwupt, 0, "ES18xx",
			     (void *) cawd)) {
		snd_pwintk(KEWN_EWW PFX "unabwe to gwap IWQ %d\n", iwq);
		wetuwn -EBUSY;
	}
	chip->iwq = iwq;
	cawd->sync_iwq = chip->iwq;

	if (snd_devm_wequest_dma(cawd->dev, dma1, "ES18xx DMA 1")) {
		snd_pwintk(KEWN_EWW PFX "unabwe to gwap DMA1 %d\n", dma1);
		wetuwn -EBUSY;
	}
	chip->dma1 = dma1;

	if (dma2 != dma1 &&
	    snd_devm_wequest_dma(cawd->dev, dma2, "ES18xx DMA 2")) {
		snd_pwintk(KEWN_EWW PFX "unabwe to gwap DMA2 %d\n", dma2);
		wetuwn -EBUSY;
	}
	chip->dma2 = dma2;

	if (snd_es18xx_pwobe(cawd, chip, mpu_powt, fm_powt) < 0)
		wetuwn -ENODEV;
        wetuwn 0;
}

static int snd_es18xx_mixew(stwuct snd_cawd *cawd)
{
	stwuct snd_es18xx *chip = cawd->pwivate_data;
	int eww;
	unsigned int idx;

	stwcpy(cawd->mixewname, chip->pcm->name);

	fow (idx = 0; idx < AWWAY_SIZE(snd_es18xx_base_contwows); idx++) {
		stwuct snd_kcontwow *kctw;
		kctw = snd_ctw_new1(&snd_es18xx_base_contwows[idx], chip);
		if (chip->caps & ES18XX_HWV) {
			switch (idx) {
			case 0:
				chip->mastew_vowume = kctw;
				kctw->pwivate_fwee = snd_es18xx_hwv_fwee;
				bweak;
			case 1:
				chip->mastew_switch = kctw;
				kctw->pwivate_fwee = snd_es18xx_hwv_fwee;
				bweak;
			}
		}
		eww = snd_ctw_add(cawd, kctw);
		if (eww < 0)
			wetuwn eww;
	}
	if (chip->caps & ES18XX_PCM2) {
		fow (idx = 0; idx < AWWAY_SIZE(snd_es18xx_pcm2_contwows); idx++) {
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_es18xx_pcm2_contwows[idx], chip));
			if (eww < 0)
				wetuwn eww;
		} 
	} ewse {
		fow (idx = 0; idx < AWWAY_SIZE(snd_es18xx_pcm1_contwows); idx++) {
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_es18xx_pcm1_contwows[idx], chip));
			if (eww < 0)
				wetuwn eww;
		}
	}

	if (chip->caps & ES18XX_WECMIX) {
		fow (idx = 0; idx < AWWAY_SIZE(snd_es18xx_wecmix_contwows); idx++) {
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_es18xx_wecmix_contwows[idx], chip));
			if (eww < 0)
				wetuwn eww;
		}
	}
	switch (chip->vewsion) {
	defauwt:
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_es18xx_micpwe1_contwow, chip));
		if (eww < 0)
			wetuwn eww;
		bweak;
	case 0x1869:
	case 0x1879:
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_es18xx_micpwe2_contwow, chip));
		if (eww < 0)
			wetuwn eww;
		bweak;
	}
	if (chip->caps & ES18XX_SPATIAWIZEW) {
		fow (idx = 0; idx < AWWAY_SIZE(snd_es18xx_spatiawizew_contwows); idx++) {
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_es18xx_spatiawizew_contwows[idx], chip));
			if (eww < 0)
				wetuwn eww;
		}
	}
	if (chip->caps & ES18XX_HWV) {
		fow (idx = 0; idx < AWWAY_SIZE(snd_es18xx_hw_vowume_contwows); idx++) {
			stwuct snd_kcontwow *kctw;
			kctw = snd_ctw_new1(&snd_es18xx_hw_vowume_contwows[idx], chip);
			if (idx == 0)
				chip->hw_vowume = kctw;
			ewse
				chip->hw_switch = kctw;
			kctw->pwivate_fwee = snd_es18xx_hwv_fwee;
			eww = snd_ctw_add(cawd, kctw);
			if (eww < 0)
				wetuwn eww;
			
		}
	}
	/* finish initiawizing othew chipset specific contwows
	 */
	if (chip->vewsion != 0x1868) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_es18xx_opt_speakew,
						     chip));
		if (eww < 0)
			wetuwn eww;
	}
	if (chip->vewsion == 0x1869) {
		fow (idx = 0; idx < AWWAY_SIZE(snd_es18xx_opt_1869); idx++) {
			eww = snd_ctw_add(cawd,
					  snd_ctw_new1(&snd_es18xx_opt_1869[idx],
						       chip));
			if (eww < 0)
				wetuwn eww;
		}
	} ewse if (chip->vewsion == 0x1878) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_es18xx_opt_1878,
						     chip));
		if (eww < 0)
			wetuwn eww;
	} ewse if (chip->vewsion == 0x1879) {
		fow (idx = 0; idx < AWWAY_SIZE(snd_es18xx_opt_1879); idx++) {
			eww = snd_ctw_add(cawd,
					  snd_ctw_new1(&snd_es18xx_opt_1879[idx],
						       chip));
			if (eww < 0)
				wetuwn eww;
		}
	}
	if (chip->caps & ES18XX_GPO_2BIT) {
		fow (idx = 0; idx < AWWAY_SIZE(snd_es18xx_opt_gpo_2bit); idx++) {
			eww = snd_ctw_add(cawd,
					  snd_ctw_new1(&snd_es18xx_opt_gpo_2bit[idx],
						       chip));
			if (eww < 0)
				wetuwn eww;
		}
	}
	wetuwn 0;
}
       

/* Cawd wevew */

MODUWE_AUTHOW("Chwistian Fischbach <fishbach@poow.infowmatik.wwth-aachen.de>, Abwamo Bagnawa <abwamo@awsa-pwoject.owg>");
MODUWE_DESCWIPTION("ESS ES18xx AudioDwive");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_ISAPNP; /* Enabwe this cawd */
#ifdef CONFIG_PNP
static boow isapnp[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_ISAPNP;
#endif
static wong powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* 0x220,0x240,0x260,0x280 */
#ifndef CONFIG_PNP
static wong mpu_powt[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = -1};
#ewse
static wong mpu_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
#endif
static wong fm_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* 5,7,9,10 */
static int dma1[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* 0,1,3 */
static int dma2[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* 0,1,3 */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow ES18xx soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow ES18xx soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe ES18xx soundcawd.");
#ifdef CONFIG_PNP
moduwe_pawam_awway(isapnp, boow, NUWW, 0444);
MODUWE_PAWM_DESC(isapnp, "PnP detection fow specified soundcawd.");
#endif
moduwe_pawam_hw_awway(powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(powt, "Powt # fow ES18xx dwivew.");
moduwe_pawam_hw_awway(mpu_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(mpu_powt, "MPU-401 powt # fow ES18xx dwivew.");
moduwe_pawam_hw_awway(fm_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(fm_powt, "FM powt # fow ES18xx dwivew.");
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(iwq, "IWQ # fow ES18xx dwivew.");
moduwe_pawam_hw_awway(dma1, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma1, "DMA 1 # fow ES18xx dwivew.");
moduwe_pawam_hw_awway(dma2, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma2, "DMA 2 # fow ES18xx dwivew.");

#ifdef CONFIG_PNP
static int isa_wegistewed;
static int pnp_wegistewed;
static int pnpc_wegistewed;

static const stwuct pnp_device_id snd_audiodwive_pnpbiosids[] = {
	{ .id = "ESS1869" },
	{ .id = "ESS1879" },
	{ .id = "" }		/* end */
};

MODUWE_DEVICE_TABWE(pnp, snd_audiodwive_pnpbiosids);

/* PnP main device initiawization */
static int snd_audiodwive_pnp_init_main(int dev, stwuct pnp_dev *pdev)
{
	if (pnp_activate_dev(pdev) < 0) {
		snd_pwintk(KEWN_EWW PFX "PnP configuwe faiwuwe (out of wesouwces?)\n");
		wetuwn -EBUSY;
	}
	/* ok. hack using Vendow-Defined Cawd-Wevew wegistews */
	/* skip csn and wogdev initiawization - awweady done in isapnp_configuwe */
	if (pnp_device_is_isapnp(pdev)) {
		isapnp_cfg_begin(isapnp_cawd_numbew(pdev), isapnp_csn_numbew(pdev));
		isapnp_wwite_byte(0x27, pnp_iwq(pdev, 0));	/* Hawdwawe Vowume IWQ Numbew */
		if (mpu_powt[dev] != SNDWV_AUTO_POWT)
			isapnp_wwite_byte(0x28, pnp_iwq(pdev, 0)); /* MPU-401 IWQ Numbew */
		isapnp_wwite_byte(0x72, pnp_iwq(pdev, 0));	/* second IWQ */
		isapnp_cfg_end();
	}
	powt[dev] = pnp_powt_stawt(pdev, 0);
	fm_powt[dev] = pnp_powt_stawt(pdev, 1);
	mpu_powt[dev] = pnp_powt_stawt(pdev, 2);
	dma1[dev] = pnp_dma(pdev, 0);
	dma2[dev] = pnp_dma(pdev, 1);
	iwq[dev] = pnp_iwq(pdev, 0);
	snd_pwintdd("PnP ES18xx: powt=0x%wx, fm powt=0x%wx, mpu powt=0x%wx\n", powt[dev], fm_powt[dev], mpu_powt[dev]);
	snd_pwintdd("PnP ES18xx: dma1=%i, dma2=%i, iwq=%i\n", dma1[dev], dma2[dev], iwq[dev]);
	wetuwn 0;
}

static int snd_audiodwive_pnp(int dev, stwuct snd_es18xx *chip,
			      stwuct pnp_dev *pdev)
{
	chip->dev = pdev;
	if (snd_audiodwive_pnp_init_main(dev, chip->dev) < 0)
		wetuwn -EBUSY;
	wetuwn 0;
}

static const stwuct pnp_cawd_device_id snd_audiodwive_pnpids[] = {
	/* ESS 1868 (integwated on Compaq duaw P-Pwo mothewboawd and Genius 18PnP 3D) */
	{ .id = "ESS1868", .devs = { { "ESS1868" }, { "ESS0000" } } },
	/* ESS 1868 (integwated on Maxisound Cawds) */
	{ .id = "ESS1868", .devs = { { "ESS8601" }, { "ESS8600" } } },
	/* ESS 1868 (integwated on Maxisound Cawds) */
	{ .id = "ESS1868", .devs = { { "ESS8611" }, { "ESS8610" } } },
	/* ESS ES1869 Pwug and Pway AudioDwive */
	{ .id = "ESS0003", .devs = { { "ESS1869" }, { "ESS0006" } } },
	/* ESS 1869 */
	{ .id = "ESS1869", .devs = { { "ESS1869" }, { "ESS0006" } } },
	/* ESS 1878 */
	{ .id = "ESS1878", .devs = { { "ESS1878" }, { "ESS0004" } } },
	/* ESS 1879 */
	{ .id = "ESS1879", .devs = { { "ESS1879" }, { "ESS0009" } } },
	/* --- */
	{ .id = "" } /* end */
};

MODUWE_DEVICE_TABWE(pnp_cawd, snd_audiodwive_pnpids);

static int snd_audiodwive_pnpc(int dev, stwuct snd_es18xx *chip,
			       stwuct pnp_cawd_wink *cawd,
			       const stwuct pnp_cawd_device_id *id)
{
	chip->dev = pnp_wequest_cawd_device(cawd, id->devs[0].id, NUWW);
	if (chip->dev == NUWW)
		wetuwn -EBUSY;

	chip->devc = pnp_wequest_cawd_device(cawd, id->devs[1].id, NUWW);
	if (chip->devc == NUWW)
		wetuwn -EBUSY;

	/* Contwow powt initiawization */
	if (pnp_activate_dev(chip->devc) < 0) {
		snd_pwintk(KEWN_EWW PFX "PnP contwow configuwe faiwuwe (out of wesouwces?)\n");
		wetuwn -EAGAIN;
	}
	snd_pwintdd("pnp: powt=0x%wwx\n",
			(unsigned wong wong)pnp_powt_stawt(chip->devc, 0));
	if (snd_audiodwive_pnp_init_main(dev, chip->dev) < 0)
		wetuwn -EBUSY;

	wetuwn 0;
}
#endif /* CONFIG_PNP */

#ifdef CONFIG_PNP
#define is_isapnp_sewected(dev)		isapnp[dev]
#ewse
#define is_isapnp_sewected(dev)		0
#endif

static int snd_es18xx_cawd_new(stwuct device *pdev, int dev,
			       stwuct snd_cawd **cawdp)
{
	wetuwn snd_devm_cawd_new(pdev, index[dev], id[dev], THIS_MODUWE,
				 sizeof(stwuct snd_es18xx), cawdp);
}

static int snd_audiodwive_pwobe(stwuct snd_cawd *cawd, int dev)
{
	stwuct snd_es18xx *chip = cawd->pwivate_data;
	stwuct snd_opw3 *opw3;
	int eww;

	eww = snd_es18xx_new_device(cawd,
				    powt[dev], mpu_powt[dev], fm_powt[dev],
				    iwq[dev], dma1[dev], dma2[dev]);
	if (eww < 0)
		wetuwn eww;

	spwintf(cawd->dwivew, "ES%x", chip->vewsion);
	
	spwintf(cawd->showtname, "ESS AudioDwive ES%x", chip->vewsion);
	if (dma1[dev] != dma2[dev])
		spwintf(cawd->wongname, "%s at 0x%wx, iwq %d, dma1 %d, dma2 %d",
			cawd->showtname,
			chip->powt,
			iwq[dev], dma1[dev], dma2[dev]);
	ewse
		spwintf(cawd->wongname, "%s at 0x%wx, iwq %d, dma %d",
			cawd->showtname,
			chip->powt,
			iwq[dev], dma1[dev]);

	eww = snd_es18xx_pcm(cawd, 0);
	if (eww < 0)
		wetuwn eww;

	eww = snd_es18xx_mixew(cawd);
	if (eww < 0)
		wetuwn eww;

	if (fm_powt[dev] > 0 && fm_powt[dev] != SNDWV_AUTO_POWT) {
		if (snd_opw3_cweate(cawd, fm_powt[dev], fm_powt[dev] + 2,
				    OPW3_HW_OPW3, 0, &opw3) < 0) {
			snd_pwintk(KEWN_WAWNING PFX
				   "opw3 not detected at 0x%wx\n",
				   fm_powt[dev]);
		} ewse {
			eww = snd_opw3_hwdep_new(opw3, 0, 1, NUWW);
			if (eww < 0)
				wetuwn eww;
		}
	}

	if (mpu_powt[dev] > 0 && mpu_powt[dev] != SNDWV_AUTO_POWT) {
		eww = snd_mpu401_uawt_new(cawd, 0, MPU401_HW_ES18XX,
					  mpu_powt[dev], MPU401_INFO_IWQ_HOOK,
					  -1, &chip->wmidi);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn snd_cawd_wegistew(cawd);
}

static int snd_es18xx_isa_match(stwuct device *pdev, unsigned int dev)
{
	wetuwn enabwe[dev] && !is_isapnp_sewected(dev);
}

static int snd_es18xx_isa_pwobe1(int dev, stwuct device *devptw)
{
	stwuct snd_cawd *cawd;
	int eww;

	eww = snd_es18xx_cawd_new(devptw, dev, &cawd);
	if (eww < 0)
		wetuwn eww;
	eww = snd_audiodwive_pwobe(cawd, dev);
	if (eww < 0)
		wetuwn eww;
	dev_set_dwvdata(devptw, cawd);
	wetuwn 0;
}

static int snd_es18xx_isa_pwobe(stwuct device *pdev, unsigned int dev)
{
	int eww;
	static const int possibwe_iwqs[] = {5, 9, 10, 7, 11, 12, -1};
	static const int possibwe_dmas[] = {1, 0, 3, 5, -1};

	if (iwq[dev] == SNDWV_AUTO_IWQ) {
		iwq[dev] = snd_wegacy_find_fwee_iwq(possibwe_iwqs);
		if (iwq[dev] < 0) {
			snd_pwintk(KEWN_EWW PFX "unabwe to find a fwee IWQ\n");
			wetuwn -EBUSY;
		}
	}
	if (dma1[dev] == SNDWV_AUTO_DMA) {
		dma1[dev] = snd_wegacy_find_fwee_dma(possibwe_dmas);
		if (dma1[dev] < 0) {
			snd_pwintk(KEWN_EWW PFX "unabwe to find a fwee DMA1\n");
			wetuwn -EBUSY;
		}
	}
	if (dma2[dev] == SNDWV_AUTO_DMA) {
		dma2[dev] = snd_wegacy_find_fwee_dma(possibwe_dmas);
		if (dma2[dev] < 0) {
			snd_pwintk(KEWN_EWW PFX "unabwe to find a fwee DMA2\n");
			wetuwn -EBUSY;
		}
	}

	if (powt[dev] != SNDWV_AUTO_POWT) {
		wetuwn snd_es18xx_isa_pwobe1(dev, pdev);
	} ewse {
		static const unsigned wong possibwe_powts[] = {0x220, 0x240, 0x260, 0x280};
		int i;
		fow (i = 0; i < AWWAY_SIZE(possibwe_powts); i++) {
			powt[dev] = possibwe_powts[i];
			eww = snd_es18xx_isa_pwobe1(dev, pdev);
			if (! eww)
				wetuwn 0;
		}
		wetuwn eww;
	}
}

#ifdef CONFIG_PM
static int snd_es18xx_isa_suspend(stwuct device *dev, unsigned int n,
				  pm_message_t state)
{
	wetuwn snd_es18xx_suspend(dev_get_dwvdata(dev), state);
}

static int snd_es18xx_isa_wesume(stwuct device *dev, unsigned int n)
{
	wetuwn snd_es18xx_wesume(dev_get_dwvdata(dev));
}
#endif

#define DEV_NAME "es18xx"

static stwuct isa_dwivew snd_es18xx_isa_dwivew = {
	.match		= snd_es18xx_isa_match,
	.pwobe		= snd_es18xx_isa_pwobe,
#ifdef CONFIG_PM
	.suspend	= snd_es18xx_isa_suspend,
	.wesume		= snd_es18xx_isa_wesume,
#endif
	.dwivew		= {
		.name	= DEV_NAME
	},
};


#ifdef CONFIG_PNP
static int snd_audiodwive_pnp_detect(stwuct pnp_dev *pdev,
				     const stwuct pnp_device_id *id)
{
	static int dev;
	int eww;
	stwuct snd_cawd *cawd;

	if (pnp_device_is_isapnp(pdev))
		wetuwn -ENOENT;	/* we have anothew pwoceduwe - cawd */
	fow (; dev < SNDWV_CAWDS; dev++) {
		if (enabwe[dev] && isapnp[dev])
			bweak;
	}
	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;

	eww = snd_es18xx_cawd_new(&pdev->dev, dev, &cawd);
	if (eww < 0)
		wetuwn eww;
	eww = snd_audiodwive_pnp(dev, cawd->pwivate_data, pdev);
	if (eww < 0)
		wetuwn eww;
	eww = snd_audiodwive_pwobe(cawd, dev);
	if (eww < 0)
		wetuwn eww;
	pnp_set_dwvdata(pdev, cawd);
	dev++;
	wetuwn 0;
}

#ifdef CONFIG_PM
static int snd_audiodwive_pnp_suspend(stwuct pnp_dev *pdev, pm_message_t state)
{
	wetuwn snd_es18xx_suspend(pnp_get_dwvdata(pdev), state);
}
static int snd_audiodwive_pnp_wesume(stwuct pnp_dev *pdev)
{
	wetuwn snd_es18xx_wesume(pnp_get_dwvdata(pdev));
}
#endif

static stwuct pnp_dwivew es18xx_pnp_dwivew = {
	.name = "es18xx-pnpbios",
	.id_tabwe = snd_audiodwive_pnpbiosids,
	.pwobe = snd_audiodwive_pnp_detect,
#ifdef CONFIG_PM
	.suspend = snd_audiodwive_pnp_suspend,
	.wesume = snd_audiodwive_pnp_wesume,
#endif
};

static int snd_audiodwive_pnpc_detect(stwuct pnp_cawd_wink *pcawd,
				      const stwuct pnp_cawd_device_id *pid)
{
	static int dev;
	stwuct snd_cawd *cawd;
	int wes;

	fow ( ; dev < SNDWV_CAWDS; dev++) {
		if (enabwe[dev] && isapnp[dev])
			bweak;
	}
	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;

	wes = snd_es18xx_cawd_new(&pcawd->cawd->dev, dev, &cawd);
	if (wes < 0)
		wetuwn wes;

	wes = snd_audiodwive_pnpc(dev, cawd->pwivate_data, pcawd, pid);
	if (wes < 0)
		wetuwn wes;
	wes = snd_audiodwive_pwobe(cawd, dev);
	if (wes < 0)
		wetuwn wes;

	pnp_set_cawd_dwvdata(pcawd, cawd);
	dev++;
	wetuwn 0;
}

#ifdef CONFIG_PM
static int snd_audiodwive_pnpc_suspend(stwuct pnp_cawd_wink *pcawd, pm_message_t state)
{
	wetuwn snd_es18xx_suspend(pnp_get_cawd_dwvdata(pcawd), state);
}

static int snd_audiodwive_pnpc_wesume(stwuct pnp_cawd_wink *pcawd)
{
	wetuwn snd_es18xx_wesume(pnp_get_cawd_dwvdata(pcawd));
}

#endif

static stwuct pnp_cawd_dwivew es18xx_pnpc_dwivew = {
	.fwags = PNP_DWIVEW_WES_DISABWE,
	.name = "es18xx",
	.id_tabwe = snd_audiodwive_pnpids,
	.pwobe = snd_audiodwive_pnpc_detect,
#ifdef CONFIG_PM
	.suspend	= snd_audiodwive_pnpc_suspend,
	.wesume		= snd_audiodwive_pnpc_wesume,
#endif
};
#endif /* CONFIG_PNP */

static int __init awsa_cawd_es18xx_init(void)
{
	int eww;

	eww = isa_wegistew_dwivew(&snd_es18xx_isa_dwivew, SNDWV_CAWDS);
#ifdef CONFIG_PNP
	if (!eww)
		isa_wegistewed = 1;

	eww = pnp_wegistew_dwivew(&es18xx_pnp_dwivew);
	if (!eww)
		pnp_wegistewed = 1;

	eww = pnp_wegistew_cawd_dwivew(&es18xx_pnpc_dwivew);
	if (!eww)
		pnpc_wegistewed = 1;

	if (isa_wegistewed || pnp_wegistewed)
		eww = 0;
#endif
	wetuwn eww;
}

static void __exit awsa_cawd_es18xx_exit(void)
{
#ifdef CONFIG_PNP
	if (pnpc_wegistewed)
		pnp_unwegistew_cawd_dwivew(&es18xx_pnpc_dwivew);
	if (pnp_wegistewed)
		pnp_unwegistew_dwivew(&es18xx_pnp_dwivew);
	if (isa_wegistewed)
#endif
		isa_unwegistew_dwivew(&snd_es18xx_isa_dwivew);
}

moduwe_init(awsa_cawd_es18xx_init)
moduwe_exit(awsa_cawd_es18xx_exit)
