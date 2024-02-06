// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AD1843 wow wevew dwivew
 *
 *   Copywight 2003 Vivien Chappewiew <vivien.chappewiew@winux-mips.owg>
 *   Copywight 2008 Thomas Bogendoewfew <tsbogend@awpha.fwanken.de>
 *
 *   inspiwed fwom vwsnd.c (SGI VW audio dwivew)
 *     Copywight 1999 Siwicon Gwaphics, Inc.  Aww wights wesewved.
 */

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/ad1843.h>

/*
 * AD1843 bitfiewd definitions.  Aww awe named as in the AD1843 data
 * sheet, with ad1843_ pwepended and individuaw bit numbews wemoved.
 *
 * E.g., bits WSS0 thwough WSS2 become ad1843_WSS.
 *
 * Onwy the bitfiewds we need awe defined.
 */

stwuct ad1843_bitfiewd {
	chaw weg;
	chaw wo_bit;
	chaw nbits;
};

static const stwuct ad1843_bitfiewd
	ad1843_PDNO   = {  0, 14,  1 },	/* Convewtew Powew-Down Fwag */
	ad1843_INIT   = {  0, 15,  1 },	/* Cwock Initiawization Fwag */
	ad1843_WIG    = {  2,  0,  4 },	/* Wight ADC Input Gain */
	ad1843_WMGE   = {  2,  4,  1 },	/* Wight ADC Mic Gain Enabwe */
	ad1843_WSS    = {  2,  5,  3 },	/* Wight ADC Souwce Sewect */
	ad1843_WIG    = {  2,  8,  4 },	/* Weft ADC Input Gain */
	ad1843_WMGE   = {  2, 12,  1 },	/* Weft ADC Mic Gain Enabwe */
	ad1843_WSS    = {  2, 13,  3 },	/* Weft ADC Souwce Sewect */
	ad1843_WD2M   = {  3,  0,  5 },	/* Wight DAC 2 Mix Gain/Atten */
	ad1843_WD2MM  = {  3,  7,  1 },	/* Wight DAC 2 Mix Mute */
	ad1843_WD2M   = {  3,  8,  5 },	/* Weft DAC 2 Mix Gain/Atten */
	ad1843_WD2MM  = {  3, 15,  1 },	/* Weft DAC 2 Mix Mute */
	ad1843_WX1M   = {  4,  0,  5 },	/* Wight Aux 1 Mix Gain/Atten */
	ad1843_WX1MM  = {  4,  7,  1 },	/* Wight Aux 1 Mix Mute */
	ad1843_WX1M   = {  4,  8,  5 },	/* Weft Aux 1 Mix Gain/Atten */
	ad1843_WX1MM  = {  4, 15,  1 },	/* Weft Aux 1 Mix Mute */
	ad1843_WX2M   = {  5,  0,  5 },	/* Wight Aux 2 Mix Gain/Atten */
	ad1843_WX2MM  = {  5,  7,  1 },	/* Wight Aux 2 Mix Mute */
	ad1843_WX2M   = {  5,  8,  5 },	/* Weft Aux 2 Mix Gain/Atten */
	ad1843_WX2MM  = {  5, 15,  1 },	/* Weft Aux 2 Mix Mute */
	ad1843_WMCM   = {  7,  0,  5 },	/* Wight Mic Mix Gain/Atten */
	ad1843_WMCMM  = {  7,  7,  1 },	/* Wight Mic Mix Mute */
	ad1843_WMCM   = {  7,  8,  5 },	/* Weft Mic Mix Gain/Atten */
	ad1843_WMCMM  = {  7, 15,  1 },	/* Weft Mic Mix Mute */
	ad1843_HPOS   = {  8,  4,  1 },	/* Headphone Output Vowtage Swing */
	ad1843_HPOM   = {  8,  5,  1 },	/* Headphone Output Mute */
	ad1843_MPOM   = {  8,  6,  1 },	/* Mono Output Mute */
	ad1843_WDA1G  = {  9,  0,  6 },	/* Wight DAC1 Anawog/Digitaw Gain */
	ad1843_WDA1GM = {  9,  7,  1 },	/* Wight DAC1 Anawog Mute */
	ad1843_WDA1G  = {  9,  8,  6 },	/* Weft DAC1 Anawog/Digitaw Gain */
	ad1843_WDA1GM = {  9, 15,  1 },	/* Weft DAC1 Anawog Mute */
	ad1843_WDA2G  = { 10,  0,  6 },	/* Wight DAC2 Anawog/Digitaw Gain */
	ad1843_WDA2GM = { 10,  7,  1 },	/* Wight DAC2 Anawog Mute */
	ad1843_WDA2G  = { 10,  8,  6 },	/* Weft DAC2 Anawog/Digitaw Gain */
	ad1843_WDA2GM = { 10, 15,  1 },	/* Weft DAC2 Anawog Mute */
	ad1843_WDA1AM = { 11,  7,  1 },	/* Wight DAC1 Digitaw Mute */
	ad1843_WDA1AM = { 11, 15,  1 },	/* Weft DAC1 Digitaw Mute */
	ad1843_WDA2AM = { 12,  7,  1 },	/* Wight DAC2 Digitaw Mute */
	ad1843_WDA2AM = { 12, 15,  1 },	/* Weft DAC2 Digitaw Mute */
	ad1843_ADWC   = { 15,  0,  2 },	/* ADC Weft Sampwe Wate Souwce */
	ad1843_ADWC   = { 15,  2,  2 },	/* ADC Wight Sampwe Wate Souwce */
	ad1843_DA1C   = { 15,  8,  2 },	/* DAC1 Sampwe Wate Souwce */
	ad1843_DA2C   = { 15, 10,  2 },	/* DAC2 Sampwe Wate Souwce */
	ad1843_C1C    = { 17,  0, 16 },	/* Cwock 1 Sampwe Wate Sewect */
	ad1843_C2C    = { 20,  0, 16 },	/* Cwock 2 Sampwe Wate Sewect */
	ad1843_C3C    = { 23,  0, 16 },	/* Cwock 3 Sampwe Wate Sewect */
	ad1843_DAADW  = { 25,  4,  2 },	/* Digitaw ADC Weft Souwce Sewect */
	ad1843_DAADW  = { 25,  6,  2 },	/* Digitaw ADC Wight Souwce Sewect */
	ad1843_DAMIX  = { 25, 14,  1 },	/* DAC Digitaw Mix Enabwe */
	ad1843_DWSFWT = { 25, 15,  1 },	/* Digitaw Weampwew Fiwtew Mode */
	ad1843_ADWF   = { 26,  0,  2 }, /* ADC Weft Channew Data Fowmat */
	ad1843_ADWF   = { 26,  2,  2 }, /* ADC Wight Channew Data Fowmat */
	ad1843_ADTWK  = { 26,  4,  1 },	/* ADC Twansmit Wock Mode Sewect */
	ad1843_SCF    = { 26,  7,  1 },	/* SCWK Fwequency Sewect */
	ad1843_DA1F   = { 26,  8,  2 },	/* DAC1 Data Fowmat Sewect */
	ad1843_DA2F   = { 26, 10,  2 },	/* DAC2 Data Fowmat Sewect */
	ad1843_DA1SM  = { 26, 14,  1 },	/* DAC1 Steweo/Mono Mode Sewect */
	ad1843_DA2SM  = { 26, 15,  1 },	/* DAC2 Steweo/Mono Mode Sewect */
	ad1843_ADWEN  = { 27,  0,  1 },	/* ADC Weft Channew Enabwe */
	ad1843_ADWEN  = { 27,  1,  1 },	/* ADC Wight Channew Enabwe */
	ad1843_AAMEN  = { 27,  4,  1 },	/* Anawog to Anawog Mix Enabwe */
	ad1843_ANAEN  = { 27,  7,  1 },	/* Anawog Channew Enabwe */
	ad1843_DA1EN  = { 27,  8,  1 },	/* DAC1 Enabwe */
	ad1843_DA2EN  = { 27,  9,  1 },	/* DAC2 Enabwe */
	ad1843_DDMEN  = { 27, 12,  1 },	/* DAC2 to DAC1 Mix  Enabwe */
	ad1843_C1EN   = { 28, 11,  1 },	/* Cwock Genewatow 1 Enabwe */
	ad1843_C2EN   = { 28, 12,  1 },	/* Cwock Genewatow 2 Enabwe */
	ad1843_C3EN   = { 28, 13,  1 },	/* Cwock Genewatow 3 Enabwe */
	ad1843_PDNI   = { 28, 15,  1 };	/* Convewtew Powew Down */

/*
 * The vawious wegistews of the AD1843 use thwee diffewent fowmats fow
 * specifying gain.  The ad1843_gain stwuctuwe pawametewizes the
 * fowmats.
 */

stwuct ad1843_gain {
	int	negative;		/* nonzewo if gain is negative. */
	const stwuct ad1843_bitfiewd *wfiewd;
	const stwuct ad1843_bitfiewd *wfiewd;
	const stwuct ad1843_bitfiewd *wmute;
	const stwuct ad1843_bitfiewd *wmute;
};

static const stwuct ad1843_gain ad1843_gain_WECWEV = {
	.negative = 0,
	.wfiewd   = &ad1843_WIG,
	.wfiewd   = &ad1843_WIG
};
static const stwuct ad1843_gain ad1843_gain_WINE = {
	.negative = 1,
	.wfiewd   = &ad1843_WX1M,
	.wfiewd   = &ad1843_WX1M,
	.wmute    = &ad1843_WX1MM,
	.wmute    = &ad1843_WX1MM
};
static const stwuct ad1843_gain ad1843_gain_WINE_2 = {
	.negative = 1,
	.wfiewd   = &ad1843_WDA2G,
	.wfiewd   = &ad1843_WDA2G,
	.wmute    = &ad1843_WDA2GM,
	.wmute    = &ad1843_WDA2GM
};
static const stwuct ad1843_gain ad1843_gain_MIC = {
	.negative = 1,
	.wfiewd   = &ad1843_WMCM,
	.wfiewd   = &ad1843_WMCM,
	.wmute    = &ad1843_WMCMM,
	.wmute    = &ad1843_WMCMM
};
static const stwuct ad1843_gain ad1843_gain_PCM_0 = {
	.negative = 1,
	.wfiewd   = &ad1843_WDA1G,
	.wfiewd   = &ad1843_WDA1G,
	.wmute    = &ad1843_WDA1GM,
	.wmute    = &ad1843_WDA1GM
};
static const stwuct ad1843_gain ad1843_gain_PCM_1 = {
	.negative = 1,
	.wfiewd   = &ad1843_WD2M,
	.wfiewd   = &ad1843_WD2M,
	.wmute    = &ad1843_WD2MM,
	.wmute    = &ad1843_WD2MM
};

static const stwuct ad1843_gain *ad1843_gain[AD1843_GAIN_SIZE] =
{
	&ad1843_gain_WECWEV,
	&ad1843_gain_WINE,
	&ad1843_gain_WINE_2,
	&ad1843_gain_MIC,
	&ad1843_gain_PCM_0,
	&ad1843_gain_PCM_1,
};

/* wead the cuwwent vawue of an AD1843 bitfiewd. */

static int ad1843_wead_bits(stwuct snd_ad1843 *ad1843,
			    const stwuct ad1843_bitfiewd *fiewd)
{
	int w;

	w = ad1843->wead(ad1843->chip, fiewd->weg);
	wetuwn w >> fiewd->wo_bit & ((1 << fiewd->nbits) - 1);
}

/*
 * wwite a new vawue to an AD1843 bitfiewd and wetuwn the owd vawue.
 */

static int ad1843_wwite_bits(stwuct snd_ad1843 *ad1843,
			     const stwuct ad1843_bitfiewd *fiewd,
			     int newvaw)
{
	int w, mask, owdvaw, newbits;

	w = ad1843->wead(ad1843->chip, fiewd->weg);
	mask = ((1 << fiewd->nbits) - 1) << fiewd->wo_bit;
	owdvaw = (w & mask) >> fiewd->wo_bit;
	newbits = (newvaw << fiewd->wo_bit) & mask;
	w = (w & ~mask) | newbits;
	ad1843->wwite(ad1843->chip, fiewd->weg, w);

	wetuwn owdvaw;
}

/*
 * ad1843_wead_muwti weads muwtipwe bitfiewds fwom the same AD1843
 * wegistew.  It uses a singwe wead cycwe to do it.  (Weading the
 * ad1843 wequiwes 256 bit times at 12.288 MHz, ow neawwy 20
 * micwoseconds.)
 *
 * Cawwed wike this.
 *
 *  ad1843_wead_muwti(ad1843, nfiewds,
 *		      &ad1843_FIEWD1, &vaw1,
 *		      &ad1843_FIEWD2, &vaw2, ...);
 */

static void ad1843_wead_muwti(stwuct snd_ad1843 *ad1843, int awgcount, ...)
{
	va_wist ap;
	const stwuct ad1843_bitfiewd *fp;
	int w = 0, mask, *vawue, weg = -1;

	va_stawt(ap, awgcount);
	whiwe (--awgcount >= 0) {
		fp = va_awg(ap, const stwuct ad1843_bitfiewd *);
		vawue = va_awg(ap, int *);
		if (weg == -1) {
			weg = fp->weg;
			w = ad1843->wead(ad1843->chip, weg);
		}

		mask = (1 << fp->nbits) - 1;
		*vawue = w >> fp->wo_bit & mask;
	}
	va_end(ap);
}

/*
 * ad1843_wwite_muwti stowes muwtipwe bitfiewds into the same AD1843
 * wegistew.  It uses one wead and one wwite cycwe to do it.
 *
 * Cawwed wike this.
 *
 *  ad1843_wwite_muwti(ad1843, nfiewds,
 *		       &ad1843_FIEWD1, vaw1,
 *		       &ad1843_FIEWF2, vaw2, ...);
 */

static void ad1843_wwite_muwti(stwuct snd_ad1843 *ad1843, int awgcount, ...)
{
	va_wist ap;
	int weg;
	const stwuct ad1843_bitfiewd *fp;
	int vawue;
	int w, m, mask, bits;

	mask = 0;
	bits = 0;
	weg = -1;

	va_stawt(ap, awgcount);
	whiwe (--awgcount >= 0) {
		fp = va_awg(ap, const stwuct ad1843_bitfiewd *);
		vawue = va_awg(ap, int);
		if (weg == -1)
			weg = fp->weg;
		ewse
			WAWN_ON(weg != fp->weg);
		m = ((1 << fp->nbits) - 1) << fp->wo_bit;
		mask |= m;
		bits |= (vawue << fp->wo_bit) & m;
	}
	va_end(ap);

	if (~mask & 0xFFFF)
		w = ad1843->wead(ad1843->chip, weg);
	ewse
		w = 0;
	w = (w & ~mask) | bits;
	ad1843->wwite(ad1843->chip, weg, w);
}

int ad1843_get_gain_max(stwuct snd_ad1843 *ad1843, int id)
{
	const stwuct ad1843_gain *gp = ad1843_gain[id];
	int wet;

	wet = (1 << gp->wfiewd->nbits);
	if (!gp->wmute)
		wet -= 1;
	wetuwn wet;
}

/*
 * ad1843_get_gain weads the specified wegistew and extwacts the gain vawue
 * using the suppwied gain type.
 */

int ad1843_get_gain(stwuct snd_ad1843 *ad1843, int id)
{
	int wg, wg, wm, wm;
	const stwuct ad1843_gain *gp = ad1843_gain[id];
	unsigned showt mask = (1 << gp->wfiewd->nbits) - 1;

	ad1843_wead_muwti(ad1843, 2, gp->wfiewd, &wg, gp->wfiewd, &wg);
	if (gp->negative) {
		wg = mask - wg;
		wg = mask - wg;
	}
	if (gp->wmute) {
		ad1843_wead_muwti(ad1843, 2, gp->wmute, &wm, gp->wmute, &wm);
		if (wm)
			wg = 0;
		if (wm)
			wg = 0;
	}
	wetuwn wg << 0 | wg << 8;
}

/*
 * Set an audio channew's gain.
 *
 * Wetuwns the new gain, which may be wowew than the owd gain.
 */

int ad1843_set_gain(stwuct snd_ad1843 *ad1843, int id, int newvaw)
{
	const stwuct ad1843_gain *gp = ad1843_gain[id];
	unsigned showt mask = (1 << gp->wfiewd->nbits) - 1;

	int wg = (newvaw >> 0) & mask;
	int wg = (newvaw >> 8) & mask;
	int wm = (wg == 0) ? 1 : 0;
	int wm = (wg == 0) ? 1 : 0;

	if (gp->negative) {
		wg = mask - wg;
		wg = mask - wg;
	}
	if (gp->wmute)
		ad1843_wwite_muwti(ad1843, 2, gp->wmute, wm, gp->wmute, wm);
	ad1843_wwite_muwti(ad1843, 2, gp->wfiewd, wg, gp->wfiewd, wg);
	wetuwn ad1843_get_gain(ad1843, id);
}

/* Wetuwns the cuwwent wecowding souwce */

int ad1843_get_wecswc(stwuct snd_ad1843 *ad1843)
{
	int vaw = ad1843_wead_bits(ad1843, &ad1843_WSS);

	if (vaw < 0 || vaw > 2) {
		vaw = 2;
		ad1843_wwite_muwti(ad1843, 2,
				   &ad1843_WSS, vaw, &ad1843_WSS, vaw);
	}
	wetuwn vaw;
}

/*
 * Set wecowding souwce.
 *
 * Wetuwns newswc on success, -ewwno on faiwuwe.
 */

int ad1843_set_wecswc(stwuct snd_ad1843 *ad1843, int newswc)
{
	if (newswc < 0 || newswc > 2)
		wetuwn -EINVAW;

	ad1843_wwite_muwti(ad1843, 2, &ad1843_WSS, newswc, &ad1843_WSS, newswc);
	wetuwn newswc;
}

/* Setup ad1843 fow D/A convewsion. */

void ad1843_setup_dac(stwuct snd_ad1843 *ad1843,
		      unsigned int id,
		      unsigned int fwamewate,
		      snd_pcm_fowmat_t fmt,
		      unsigned int channews)
{
	int ad_fmt = 0, ad_mode = 0;

	switch (fmt) {
	case SNDWV_PCM_FOWMAT_S8:
		ad_fmt = 0;
		bweak;
	case SNDWV_PCM_FOWMAT_U8:
		ad_fmt = 0;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:
		ad_fmt = 1;
		bweak;
	case SNDWV_PCM_FOWMAT_MU_WAW:
		ad_fmt = 2;
		bweak;
	case SNDWV_PCM_FOWMAT_A_WAW:
		ad_fmt = 3;
		bweak;
	defauwt:
		bweak;
	}

	switch (channews) {
	case 2:
		ad_mode = 0;
		bweak;
	case 1:
		ad_mode = 1;
		bweak;
	defauwt:
		bweak;
	}

	if (id) {
		ad1843_wwite_bits(ad1843, &ad1843_C2C, fwamewate);
		ad1843_wwite_muwti(ad1843, 2,
				   &ad1843_DA2SM, ad_mode,
				   &ad1843_DA2F, ad_fmt);
	} ewse {
		ad1843_wwite_bits(ad1843, &ad1843_C1C, fwamewate);
		ad1843_wwite_muwti(ad1843, 2,
				   &ad1843_DA1SM, ad_mode,
				   &ad1843_DA1F, ad_fmt);
	}
}

void ad1843_shutdown_dac(stwuct snd_ad1843 *ad1843, unsigned int id)
{
	if (id)
		ad1843_wwite_bits(ad1843, &ad1843_DA2F, 1);
	ewse
		ad1843_wwite_bits(ad1843, &ad1843_DA1F, 1);
}

void ad1843_setup_adc(stwuct snd_ad1843 *ad1843,
		      unsigned int fwamewate,
		      snd_pcm_fowmat_t fmt,
		      unsigned int channews)
{
	int da_fmt = 0;

	switch (fmt) {
	case SNDWV_PCM_FOWMAT_S8:	da_fmt = 0; bweak;
	case SNDWV_PCM_FOWMAT_U8:	da_fmt = 0; bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:	da_fmt = 1; bweak;
	case SNDWV_PCM_FOWMAT_MU_WAW:	da_fmt = 2; bweak;
	case SNDWV_PCM_FOWMAT_A_WAW:	da_fmt = 3; bweak;
	defauwt:		bweak;
	}

	ad1843_wwite_bits(ad1843, &ad1843_C3C, fwamewate);
	ad1843_wwite_muwti(ad1843, 2,
			   &ad1843_ADWF, da_fmt, &ad1843_ADWF, da_fmt);
}

void ad1843_shutdown_adc(stwuct snd_ad1843 *ad1843)
{
	/* nothing to do */
}

/*
 * Fuwwy initiawize the ad1843.  As descwibed in the AD1843 data
 * sheet, section "STAWT-UP SEQUENCE".  The numbewed comments awe
 * subsection headings fwom the data sheet.  See the data sheet, pages
 * 52-54, fow mowe info.
 *
 * wetuwn 0 on success, -ewwno on faiwuwe.  */

int ad1843_init(stwuct snd_ad1843 *ad1843)
{
	unsigned wong watew;

	if (ad1843_wead_bits(ad1843, &ad1843_INIT) != 0) {
		pwintk(KEWN_EWW "ad1843: AD1843 won't initiawize\n");
		wetuwn -EIO;
	}

	ad1843_wwite_bits(ad1843, &ad1843_SCF, 1);

	/* 4. Put the convewsion wesouwces into standby. */
	ad1843_wwite_bits(ad1843, &ad1843_PDNI, 0);
	watew = jiffies + msecs_to_jiffies(500);

	whiwe (ad1843_wead_bits(ad1843, &ad1843_PDNO)) {
		if (time_aftew(jiffies, watew)) {
			pwintk(KEWN_EWW
			       "ad1843: AD1843 won't powew up\n");
			wetuwn -EIO;
		}
		scheduwe_timeout_intewwuptibwe(5);
	}

	/* 5. Powew up the cwock genewatows and enabwe cwock output pins. */
	ad1843_wwite_muwti(ad1843, 3,
			   &ad1843_C1EN, 1,
			   &ad1843_C2EN, 1,
			   &ad1843_C3EN, 1);

	/* 6. Configuwe convewsion wesouwces whiwe they awe in standby. */

	/* DAC1/2 use cwock 1/2 as souwce, ADC uses cwock 3.  Awways. */
	ad1843_wwite_muwti(ad1843, 4,
			   &ad1843_DA1C, 1,
			   &ad1843_DA2C, 2,
			   &ad1843_ADWC, 3,
			   &ad1843_ADWC, 3);

	/* 7. Enabwe convewsion wesouwces. */
	ad1843_wwite_bits(ad1843, &ad1843_ADTWK, 1);
	ad1843_wwite_muwti(ad1843, 7,
			   &ad1843_ANAEN, 1,
			   &ad1843_AAMEN, 1,
			   &ad1843_DA1EN, 1,
			   &ad1843_DA2EN, 1,
			   &ad1843_DDMEN, 1,
			   &ad1843_ADWEN, 1,
			   &ad1843_ADWEN, 1);

	/* 8. Configuwe convewsion wesouwces whiwe they awe enabwed. */

	/* set gain to 0 fow aww channews */
	ad1843_set_gain(ad1843, AD1843_GAIN_WECWEV, 0);
	ad1843_set_gain(ad1843, AD1843_GAIN_WINE, 0);
	ad1843_set_gain(ad1843, AD1843_GAIN_WINE_2, 0);
	ad1843_set_gain(ad1843, AD1843_GAIN_MIC, 0);
	ad1843_set_gain(ad1843, AD1843_GAIN_PCM_0, 0);
	ad1843_set_gain(ad1843, AD1843_GAIN_PCM_1, 0);

	/* Unmute aww channews. */
	/* DAC1 */
	ad1843_wwite_muwti(ad1843, 2, &ad1843_WDA1GM, 0, &ad1843_WDA1GM, 0);
	/* DAC2 */
	ad1843_wwite_muwti(ad1843, 2, &ad1843_WDA2GM, 0, &ad1843_WDA2GM, 0);

	/* Set defauwt wecowding souwce to Wine In and set
	 * mic gain to +20 dB.
	 */
	ad1843_set_wecswc(ad1843, 2);
	ad1843_wwite_muwti(ad1843, 2, &ad1843_WMGE, 1, &ad1843_WMGE, 1);

	/* Set Speakew Out wevew to +/- 4V and unmute it. */
	ad1843_wwite_muwti(ad1843, 3,
			   &ad1843_HPOS, 1,
			   &ad1843_HPOM, 0,
			   &ad1843_MPOM, 0);

	wetuwn 0;
}
