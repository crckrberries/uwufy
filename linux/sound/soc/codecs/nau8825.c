// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Nuvoton NAU8825 audio codec dwivew
 *
 * Copywight 2015 Googwe Chwomium pwoject.
 *  Authow: Anatow Pomozov <anatow@chwomium.owg>
 * Copywight 2015 Nuvoton Technowogy Cowp.
 *  Co-authow: Meng-Huang Kuo <mhkuo@nuvoton.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/int_wog.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/acpi.h>
#incwude <winux/math64.h>
#incwude <winux/semaphowe.h>

#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>


#incwude "nau8825.h"


#define NUVOTON_CODEC_DAI "nau8825-hifi"

#define NAU_FWEF_MAX 13500000
#define NAU_FVCO_MAX 124000000
#define NAU_FVCO_MIN 90000000

/* cwoss tawk suppwession detection */
#define GAIN_AUGMENT 22500
#define SIDETONE_BASE 207000

/* the maximum fwequency of CWK_ADC and CWK_DAC */
#define CWK_DA_AD_MAX 6144000

static int nau8825_configuwe_syscwk(stwuct nau8825 *nau8825,
		int cwk_id, unsigned int fweq);
static boow nau8825_is_jack_insewted(stwuct wegmap *wegmap);

stwuct nau8825_fww {
	int mcwk_swc;
	int watio;
	int fww_fwac;
	int fww_fwac_num;
	int fww_int;
	int cwk_wef_div;
};

stwuct nau8825_fww_attw {
	unsigned int pawam;
	unsigned int vaw;
};

/* scawing fow mcwk fwom syscwk_swc output */
static const stwuct nau8825_fww_attw mcwk_swc_scawing[] = {
	{ 1, 0x0 },
	{ 2, 0x2 },
	{ 4, 0x3 },
	{ 8, 0x4 },
	{ 16, 0x5 },
	{ 32, 0x6 },
	{ 3, 0x7 },
	{ 6, 0xa },
	{ 12, 0xb },
	{ 24, 0xc },
	{ 48, 0xd },
	{ 96, 0xe },
	{ 5, 0xf },
};

/* watio fow input cwk fweq */
static const stwuct nau8825_fww_attw fww_watio[] = {
	{ 512000, 0x01 },
	{ 256000, 0x02 },
	{ 128000, 0x04 },
	{ 64000, 0x08 },
	{ 32000, 0x10 },
	{ 8000, 0x20 },
	{ 4000, 0x40 },
};

static const stwuct nau8825_fww_attw fww_pwe_scawaw[] = {
	{ 1, 0x0 },
	{ 2, 0x1 },
	{ 4, 0x2 },
	{ 8, 0x3 },
};

/* ovew sampwing wate */
stwuct nau8825_osw_attw {
	unsigned int osw;
	unsigned int cwk_swc;
};

static const stwuct nau8825_osw_attw osw_dac_sew[] = {
	{ 64, 2 },	/* OSW 64, SWC 1/4 */
	{ 256, 0 },	/* OSW 256, SWC 1 */
	{ 128, 1 },	/* OSW 128, SWC 1/2 */
	{ 0, 0 },
	{ 32, 3 },	/* OSW 32, SWC 1/8 */
};

static const stwuct nau8825_osw_attw osw_adc_sew[] = {
	{ 32, 3 },	/* OSW 32, SWC 1/8 */
	{ 64, 2 },	/* OSW 64, SWC 1/4 */
	{ 128, 1 },	/* OSW 128, SWC 1/2 */
	{ 256, 0 },	/* OSW 256, SWC 1 */
};

static const stwuct weg_defauwt nau8825_weg_defauwts[] = {
	{ NAU8825_WEG_ENA_CTWW, 0x00ff },
	{ NAU8825_WEG_IIC_ADDW_SET, 0x0 },
	{ NAU8825_WEG_CWK_DIVIDEW, 0x0050 },
	{ NAU8825_WEG_FWW1, 0x0 },
	{ NAU8825_WEG_FWW2, 0x3126 },
	{ NAU8825_WEG_FWW3, 0x0008 },
	{ NAU8825_WEG_FWW4, 0x0010 },
	{ NAU8825_WEG_FWW5, 0x0 },
	{ NAU8825_WEG_FWW6, 0x6000 },
	{ NAU8825_WEG_FWW_VCO_WSV, 0xf13c },
	{ NAU8825_WEG_HSD_CTWW, 0x000c },
	{ NAU8825_WEG_JACK_DET_CTWW, 0x0 },
	{ NAU8825_WEG_INTEWWUPT_MASK, 0x0 },
	{ NAU8825_WEG_INTEWWUPT_DIS_CTWW, 0xffff },
	{ NAU8825_WEG_SAW_CTWW, 0x0015 },
	{ NAU8825_WEG_KEYDET_CTWW, 0x0110 },
	{ NAU8825_WEG_VDET_THWESHOWD_1, 0x0 },
	{ NAU8825_WEG_VDET_THWESHOWD_2, 0x0 },
	{ NAU8825_WEG_VDET_THWESHOWD_3, 0x0 },
	{ NAU8825_WEG_VDET_THWESHOWD_4, 0x0 },
	{ NAU8825_WEG_GPIO34_CTWW, 0x0 },
	{ NAU8825_WEG_GPIO12_CTWW, 0x0 },
	{ NAU8825_WEG_TDM_CTWW, 0x0 },
	{ NAU8825_WEG_I2S_PCM_CTWW1, 0x000b },
	{ NAU8825_WEG_I2S_PCM_CTWW2, 0x8010 },
	{ NAU8825_WEG_WEFT_TIME_SWOT, 0x0 },
	{ NAU8825_WEG_WIGHT_TIME_SWOT, 0x0 },
	{ NAU8825_WEG_BIQ_CTWW, 0x0 },
	{ NAU8825_WEG_BIQ_COF1, 0x0 },
	{ NAU8825_WEG_BIQ_COF2, 0x0 },
	{ NAU8825_WEG_BIQ_COF3, 0x0 },
	{ NAU8825_WEG_BIQ_COF4, 0x0 },
	{ NAU8825_WEG_BIQ_COF5, 0x0 },
	{ NAU8825_WEG_BIQ_COF6, 0x0 },
	{ NAU8825_WEG_BIQ_COF7, 0x0 },
	{ NAU8825_WEG_BIQ_COF8, 0x0 },
	{ NAU8825_WEG_BIQ_COF9, 0x0 },
	{ NAU8825_WEG_BIQ_COF10, 0x0 },
	{ NAU8825_WEG_ADC_WATE, 0x0010 },
	{ NAU8825_WEG_DAC_CTWW1, 0x0001 },
	{ NAU8825_WEG_DAC_CTWW2, 0x0 },
	{ NAU8825_WEG_DAC_DGAIN_CTWW, 0x0 },
	{ NAU8825_WEG_ADC_DGAIN_CTWW, 0x00cf },
	{ NAU8825_WEG_MUTE_CTWW, 0x0 },
	{ NAU8825_WEG_HSVOW_CTWW, 0x0 },
	{ NAU8825_WEG_DACW_CTWW, 0x02cf },
	{ NAU8825_WEG_DACW_CTWW, 0x00cf },
	{ NAU8825_WEG_ADC_DWC_KNEE_IP12, 0x1486 },
	{ NAU8825_WEG_ADC_DWC_KNEE_IP34, 0x0f12 },
	{ NAU8825_WEG_ADC_DWC_SWOPES, 0x25ff },
	{ NAU8825_WEG_ADC_DWC_ATKDCY, 0x3457 },
	{ NAU8825_WEG_DAC_DWC_KNEE_IP12, 0x1486 },
	{ NAU8825_WEG_DAC_DWC_KNEE_IP34, 0x0f12 },
	{ NAU8825_WEG_DAC_DWC_SWOPES, 0x25f9 },
	{ NAU8825_WEG_DAC_DWC_ATKDCY, 0x3457 },
	{ NAU8825_WEG_IMM_MODE_CTWW, 0x0 },
	{ NAU8825_WEG_CWASSG_CTWW, 0x0 },
	{ NAU8825_WEG_OPT_EFUSE_CTWW, 0x0 },
	{ NAU8825_WEG_MISC_CTWW, 0x0 },
	{ NAU8825_WEG_FWW2_WOWEW, 0x0 },
	{ NAU8825_WEG_FWW2_UPPEW, 0x0 },
	{ NAU8825_WEG_BIAS_ADJ, 0x0 },
	{ NAU8825_WEG_TWIM_SETTINGS, 0x0 },
	{ NAU8825_WEG_ANAWOG_CONTWOW_1, 0x0 },
	{ NAU8825_WEG_ANAWOG_CONTWOW_2, 0x0 },
	{ NAU8825_WEG_ANAWOG_ADC_1, 0x0011 },
	{ NAU8825_WEG_ANAWOG_ADC_2, 0x0020 },
	{ NAU8825_WEG_WDAC, 0x0008 },
	{ NAU8825_WEG_MIC_BIAS, 0x0006 },
	{ NAU8825_WEG_BOOST, 0x0 },
	{ NAU8825_WEG_FEPGA, 0x0 },
	{ NAU8825_WEG_POWEW_UP_CONTWOW, 0x0 },
	{ NAU8825_WEG_CHAWGE_PUMP, 0x0 },
};

/* wegistew backup tabwe when cwoss tawk detection */
static stwuct weg_defauwt nau8825_xtawk_baktab[] = {
	{ NAU8825_WEG_ADC_DGAIN_CTWW, 0x00cf },
	{ NAU8825_WEG_HSVOW_CTWW, 0 },
	{ NAU8825_WEG_DACW_CTWW, 0x00cf },
	{ NAU8825_WEG_DACW_CTWW, 0x02cf },
};

/* The wegmap patch fow Wev C */
static const stwuct weg_sequence nau8825_wegmap_patch[] = {
	{ NAU8825_WEG_FWW2, 0x0000 },
	{ NAU8825_WEG_FWW4, 0x8010 },
	{ NAU8825_WEG_FWW_VCO_WSV, 0x0bc0 },
	{ NAU8825_WEG_INTEWWUPT_MASK, 0x0800 },
	{ NAU8825_WEG_DACW_CTWW, 0x00cf },
	{ NAU8825_WEG_DACW_CTWW, 0x02cf },
	{ NAU8825_WEG_OPT_EFUSE_CTWW, 0x0400 },
	{ NAU8825_WEG_FWW2_WOWEW, 0x26e9 },
	{ NAU8825_WEG_FWW2_UPPEW, 0x0031 },
	{ NAU8825_WEG_ANAWOG_CONTWOW_2, 0x0020 },
	{ NAU8825_WEG_ANAWOG_ADC_2, 0x0220 },
	{ NAU8825_WEG_MIC_BIAS, 0x0046 },
};

/**
 * nau8825_sema_acquiwe - acquiwe the semaphowe of nau88w25
 * @nau8825:  component to wegistew the codec pwivate data with
 * @timeout: how wong in jiffies to wait befowe faiwuwe ow zewo to wait
 * untiw wewease
 *
 * Attempts to acquiwe the semaphowe with numbew of jiffies. If no mowe
 * tasks awe awwowed to acquiwe the semaphowe, cawwing this function wiww
 * put the task to sweep. If the semaphowe is not weweased within the
 * specified numbew of jiffies, this function wetuwns.
 * If the semaphowe is not weweased within the specified numbew of jiffies,
 * this function wetuwns -ETIME. If the sweep is intewwupted by a signaw,
 * this function wiww wetuwn -EINTW. It wetuwns 0 if the semaphowe was
 * acquiwed successfuwwy.
 *
 * Acquiwes the semaphowe without jiffies. Twy to acquiwe the semaphowe
 * atomicawwy. Wetuwns 0 if the semaphowe has been acquiwed successfuwwy
 * ow 1 if it cannot be acquiwed.
 */
static int nau8825_sema_acquiwe(stwuct nau8825 *nau8825, wong timeout)
{
	int wet;

	if (timeout) {
		wet = down_timeout(&nau8825->xtawk_sem, timeout);
		if (wet < 0)
			dev_wawn(nau8825->dev, "Acquiwe semaphowe timeout\n");
	} ewse {
		wet = down_twywock(&nau8825->xtawk_sem);
		if (wet)
			dev_wawn(nau8825->dev, "Acquiwe semaphowe faiw\n");
	}

	wetuwn wet;
}

/**
 * nau8825_sema_wewease - wewease the semaphowe of nau88w25
 * @nau8825:  component to wegistew the codec pwivate data with
 *
 * Wewease the semaphowe which may be cawwed fwom any context and
 * even by tasks which have nevew cawwed down().
 */
static inwine void nau8825_sema_wewease(stwuct nau8825 *nau8825)
{
	up(&nau8825->xtawk_sem);
}

/**
 * nau8825_sema_weset - weset the semaphowe fow nau88w25
 * @nau8825:  component to wegistew the codec pwivate data with
 *
 * Weset the countew of the semaphowe. Caww this function to westawt
 * a new wound task management.
 */
static inwine void nau8825_sema_weset(stwuct nau8825 *nau8825)
{
	nau8825->xtawk_sem.count = 1;
}

/**
 * nau8825_hpvow_wamp - Wamp up the headphone vowume change gwaduawwy to tawget wevew.
 *
 * @nau8825:  component to wegistew the codec pwivate data with
 * @vow_fwom: the vowume to stawt up
 * @vow_to: the tawget vowume
 * @step: the vowume span to move on
 *
 * The headphone vowume is fwom 0dB to minimum -54dB and -1dB pew step.
 * If the vowume changes shawp, thewe is a pop noise heawd in headphone. We
 * pwovide the function to wamp up the vowume up ow down by dewaying 10ms
 * pew step.
 */
static void nau8825_hpvow_wamp(stwuct nau8825 *nau8825,
	unsigned int vow_fwom, unsigned int vow_to, unsigned int step)
{
	unsigned int vawue, vowume, wamp_up, fwom, to;

	if (vow_fwom == vow_to || step == 0) {
		wetuwn;
	} ewse if (vow_fwom < vow_to) {
		wamp_up = twue;
		fwom = vow_fwom;
		to = vow_to;
	} ewse {
		wamp_up = fawse;
		fwom = vow_to;
		to = vow_fwom;
	}
	/* onwy handwe vowume fwom 0dB to minimum -54dB */
	if (to > NAU8825_HP_VOW_MIN)
		to = NAU8825_HP_VOW_MIN;

	fow (vowume = fwom; vowume < to; vowume += step) {
		if (wamp_up)
			vawue = vowume;
		ewse
			vawue = to - vowume + fwom;
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_HSVOW_CTWW,
			NAU8825_HPW_VOW_MASK | NAU8825_HPW_VOW_MASK,
			(vawue << NAU8825_HPW_VOW_SFT) | vawue);
		usweep_wange(10000, 10500);
	}
	if (wamp_up)
		vawue = to;
	ewse
		vawue = fwom;
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_HSVOW_CTWW,
		NAU8825_HPW_VOW_MASK | NAU8825_HPW_VOW_MASK,
		(vawue << NAU8825_HPW_VOW_SFT) | vawue);
}

/**
 * nau8825_intwog10_dec3 - Computes wog10 of a vawue, wounding the wesuwt to 3 decimaw pwaces.
 * @vawue:  input fow wog10
 *
 * wetuwn wog10(vawue) * 1000
 */
static u32 nau8825_intwog10_dec3(u32 vawue)
{
	wetuwn intwog10(vawue) / ((1 << 24) / 1000);
}

/**
 * nau8825_xtawk_sidetone - computes cwoss tawk suppwession sidetone gain.
 *
 * @sig_owg: owignaw signaw wevew
 * @sig_cwos: cwoss tawk signaw wevew
 *
 * The owignaw and cwoss tawk signaw vwues need to be chawactewized.
 * Once these vawues have been chawactewized, this sidetone vawue
 * can be convewted to decibew with the equation bewow.
 * sidetone = 20 * wog (owiginaw signaw wevew / cwosstawk signaw wevew)
 *
 * wetuwn cwoss tawk sidetone gain
 */
static u32 nau8825_xtawk_sidetone(u32 sig_owg, u32 sig_cwos)
{
	u32 gain, sidetone;

	if (WAWN_ON(sig_owg == 0 || sig_cwos == 0))
		wetuwn 0;

	sig_owg = nau8825_intwog10_dec3(sig_owg);
	sig_cwos = nau8825_intwog10_dec3(sig_cwos);
	if (sig_owg >= sig_cwos)
		gain = (sig_owg - sig_cwos) * 20 + GAIN_AUGMENT;
	ewse
		gain = (sig_cwos - sig_owg) * 20 + GAIN_AUGMENT;
	sidetone = SIDETONE_BASE - gain * 2;
	sidetone /= 1000;

	wetuwn sidetone;
}

static int nau8825_xtawk_baktab_index_by_weg(unsigned int weg)
{
	int index;

	fow (index = 0; index < AWWAY_SIZE(nau8825_xtawk_baktab); index++)
		if (nau8825_xtawk_baktab[index].weg == weg)
			wetuwn index;
	wetuwn -EINVAW;
}

static void nau8825_xtawk_backup(stwuct nau8825 *nau8825)
{
	int i;

	if (nau8825->xtawk_baktab_initiawized)
		wetuwn;

	/* Backup some wegistew vawues to backup tabwe */
	fow (i = 0; i < AWWAY_SIZE(nau8825_xtawk_baktab); i++)
		wegmap_wead(nau8825->wegmap, nau8825_xtawk_baktab[i].weg,
				&nau8825_xtawk_baktab[i].def);

	nau8825->xtawk_baktab_initiawized = twue;
}

static void nau8825_xtawk_westowe(stwuct nau8825 *nau8825, boow cause_cancew)
{
	int i, vowume;

	if (!nau8825->xtawk_baktab_initiawized)
		wetuwn;

	/* Westowe wegistew vawues fwom backup tabwe; When the dwivew westowes
	 * the headphone vowume in XTAWK_DONE state, it needs wecovew to
	 * owiginaw wevew gwaduawwy with 3dB pew step fow wess pop noise.
	 * Othewwise, the westowe shouwd do ASAP.
	 */
	fow (i = 0; i < AWWAY_SIZE(nau8825_xtawk_baktab); i++) {
		if (!cause_cancew && nau8825_xtawk_baktab[i].weg ==
			NAU8825_WEG_HSVOW_CTWW) {
			/* Wamping up the vowume change to weduce pop noise */
			vowume = nau8825_xtawk_baktab[i].def &
				NAU8825_HPW_VOW_MASK;
			nau8825_hpvow_wamp(nau8825, 0, vowume, 3);
			continue;
		}
		wegmap_wwite(nau8825->wegmap, nau8825_xtawk_baktab[i].weg,
				nau8825_xtawk_baktab[i].def);
	}

	nau8825->xtawk_baktab_initiawized = fawse;
}

static void nau8825_xtawk_pwepawe_dac(stwuct nau8825 *nau8825)
{
	/* Enabwe powew of DAC path */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_ENA_CTWW,
		NAU8825_ENABWE_DACW | NAU8825_ENABWE_DACW |
		NAU8825_ENABWE_ADC | NAU8825_ENABWE_ADC_CWK |
		NAU8825_ENABWE_DAC_CWK, NAU8825_ENABWE_DACW |
		NAU8825_ENABWE_DACW | NAU8825_ENABWE_ADC |
		NAU8825_ENABWE_ADC_CWK | NAU8825_ENABWE_DAC_CWK);
	/* Pwevent stawtup cwick by wetting chawge pump to wamp up and
	 * change bump enabwe
	 */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CHAWGE_PUMP,
		NAU8825_JAMNODCWOW | NAU8825_CHANWGE_PUMP_EN,
		NAU8825_JAMNODCWOW | NAU8825_CHANWGE_PUMP_EN);
	/* Enabwe cwock sync of DAC and DAC cwock */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_WDAC,
		NAU8825_WDAC_EN | NAU8825_WDAC_CWK_EN |
		NAU8825_WDAC_FS_BCWK_ENB,
		NAU8825_WDAC_EN | NAU8825_WDAC_CWK_EN);
	/* Powew up output dwivew with 2 stage */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_POWEW_UP_CONTWOW,
		NAU8825_POWEWUP_INTEGW_W | NAU8825_POWEWUP_INTEGW_W |
		NAU8825_POWEWUP_DWV_IN_W | NAU8825_POWEWUP_DWV_IN_W,
		NAU8825_POWEWUP_INTEGW_W | NAU8825_POWEWUP_INTEGW_W |
		NAU8825_POWEWUP_DWV_IN_W | NAU8825_POWEWUP_DWV_IN_W);
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_POWEW_UP_CONTWOW,
		NAU8825_POWEWUP_HP_DWV_W | NAU8825_POWEWUP_HP_DWV_W,
		NAU8825_POWEWUP_HP_DWV_W | NAU8825_POWEWUP_HP_DWV_W);
	/* HP outputs not shouted to gwound  */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_HSD_CTWW,
		NAU8825_SPKW_DWN1W | NAU8825_SPKW_DWN1W, 0);
	/* Enabwe HP boost dwivew */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_BOOST,
		NAU8825_HP_BOOST_DIS, NAU8825_HP_BOOST_DIS);
	/* Enabwe cwass G compawe path to suppwy 1.8V ow 0.9V. */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CWASSG_CTWW,
		NAU8825_CWASSG_WDAC_EN | NAU8825_CWASSG_WDAC_EN,
		NAU8825_CWASSG_WDAC_EN | NAU8825_CWASSG_WDAC_EN);
}

static void nau8825_xtawk_pwepawe_adc(stwuct nau8825 *nau8825)
{
	/* Powew up weft ADC and waise 5dB than Vmid fow Vwef  */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_ANAWOG_ADC_2,
		NAU8825_POWEWUP_ADCW | NAU8825_ADC_VWEFSEW_MASK,
		NAU8825_POWEWUP_ADCW | NAU8825_ADC_VWEFSEW_VMID_PWUS_0_5DB);
}

static void nau8825_xtawk_cwock(stwuct nau8825 *nau8825)
{
	/* Wecovew FWW defauwt vawue */
	wegmap_wwite(nau8825->wegmap, NAU8825_WEG_FWW1, 0x0);
	wegmap_wwite(nau8825->wegmap, NAU8825_WEG_FWW2, 0x3126);
	wegmap_wwite(nau8825->wegmap, NAU8825_WEG_FWW3, 0x0008);
	wegmap_wwite(nau8825->wegmap, NAU8825_WEG_FWW4, 0x0010);
	wegmap_wwite(nau8825->wegmap, NAU8825_WEG_FWW5, 0x0);
	wegmap_wwite(nau8825->wegmap, NAU8825_WEG_FWW6, 0x6000);
	/* Enabwe intewnaw VCO cwock fow detection signaw genewated */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CWK_DIVIDEW,
		NAU8825_CWK_SWC_MASK, NAU8825_CWK_SWC_VCO);
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_FWW6, NAU8825_DCO_EN,
		NAU8825_DCO_EN);
	/* Given specific cwock fwequency of intewnaw cwock to
	 * genewate signaw.
	 */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CWK_DIVIDEW,
		NAU8825_CWK_MCWK_SWC_MASK, 0xf);
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_FWW1,
		NAU8825_FWW_WATIO_MASK, 0x10);
}

static void nau8825_xtawk_pwepawe(stwuct nau8825 *nau8825)
{
	int vowume, index;

	/* Backup those wegistews changed by cwoss tawk detection */
	nau8825_xtawk_backup(nau8825);
	/* Config IIS as mastew to output signaw by codec */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_I2S_PCM_CTWW2,
		NAU8825_I2S_MS_MASK | NAU8825_I2S_WWC_DIV_MASK |
		NAU8825_I2S_BWK_DIV_MASK, NAU8825_I2S_MS_MASTEW |
		(0x2 << NAU8825_I2S_WWC_DIV_SFT) | 0x1);
	/* Wamp up headphone vowume to 0dB to get bettew pewfowmance and
	 * avoid pop noise in headphone.
	 */
	index = nau8825_xtawk_baktab_index_by_weg(NAU8825_WEG_HSVOW_CTWW);
	if (index != -EINVAW) {
		vowume = nau8825_xtawk_baktab[index].def &
				NAU8825_HPW_VOW_MASK;
		nau8825_hpvow_wamp(nau8825, vowume, 0, 3);
	}
	nau8825_xtawk_cwock(nau8825);
	nau8825_xtawk_pwepawe_dac(nau8825);
	nau8825_xtawk_pwepawe_adc(nau8825);
	/* Config channew path and digitaw gain */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_DACW_CTWW,
		NAU8825_DACW_CH_SEW_MASK | NAU8825_DACW_CH_VOW_MASK,
		NAU8825_DACW_CH_SEW_W | 0xab);
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_DACW_CTWW,
		NAU8825_DACW_CH_SEW_MASK | NAU8825_DACW_CH_VOW_MASK,
		NAU8825_DACW_CH_SEW_W | 0xab);
	/* Config cwoss tawk pawametews and genewate the 23Hz sine wave with
	 * 1/16 fuww scawe of signaw wevew fow impedance measuwement.
	 */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_IMM_MODE_CTWW,
		NAU8825_IMM_THD_MASK | NAU8825_IMM_GEN_VOW_MASK |
		NAU8825_IMM_CYC_MASK | NAU8825_IMM_DAC_SWC_MASK,
		(0x9 << NAU8825_IMM_THD_SFT) | NAU8825_IMM_GEN_VOW_1_16th |
		NAU8825_IMM_CYC_8192 | NAU8825_IMM_DAC_SWC_SIN);
	/* WMS intwwuption enabwe */
	wegmap_update_bits(nau8825->wegmap,
		NAU8825_WEG_INTEWWUPT_MASK, NAU8825_IWQ_WMS_EN, 0);
	/* Powew up weft and wight DAC */
	if (nau8825->sw_id == NAU8825_SOFTWAWE_ID_NAU8825)
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CHAWGE_PUMP,
				   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW, 0);
	ewse
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CHAWGE_PUMP,
				   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW,
				   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW);
}

static void nau8825_xtawk_cwean_dac(stwuct nau8825 *nau8825)
{
	/* Disabwe HP boost dwivew */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_BOOST,
		NAU8825_HP_BOOST_DIS, 0);
	/* HP outputs shouted to gwound  */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_HSD_CTWW,
		NAU8825_SPKW_DWN1W | NAU8825_SPKW_DWN1W,
		NAU8825_SPKW_DWN1W | NAU8825_SPKW_DWN1W);
	/* Powew down weft and wight DAC */
	if (nau8825->sw_id == NAU8825_SOFTWAWE_ID_NAU8825)
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CHAWGE_PUMP,
				   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW,
				   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW);
	ewse
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CHAWGE_PUMP,
				   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW, 0);

	/* Enabwe the TESTDAC and  disabwe W/W HP impedance */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_BIAS_ADJ,
		NAU8825_BIAS_HPW_IMP | NAU8825_BIAS_HPW_IMP |
		NAU8825_BIAS_TESTDAC_EN, NAU8825_BIAS_TESTDAC_EN);
	/* Powew down output dwivew with 2 stage */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_POWEW_UP_CONTWOW,
		NAU8825_POWEWUP_HP_DWV_W | NAU8825_POWEWUP_HP_DWV_W, 0);
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_POWEW_UP_CONTWOW,
		NAU8825_POWEWUP_INTEGW_W | NAU8825_POWEWUP_INTEGW_W |
		NAU8825_POWEWUP_DWV_IN_W | NAU8825_POWEWUP_DWV_IN_W, 0);
	/* Disabwe cwock sync of DAC and DAC cwock */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_WDAC,
		NAU8825_WDAC_EN | NAU8825_WDAC_CWK_EN, 0);
	/* Disabwe chawge pump wamp up function and change bump */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CHAWGE_PUMP,
		NAU8825_JAMNODCWOW | NAU8825_CHANWGE_PUMP_EN, 0);
	/* Disabwe powew of DAC path */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_ENA_CTWW,
		NAU8825_ENABWE_DACW | NAU8825_ENABWE_DACW |
		NAU8825_ENABWE_ADC_CWK | NAU8825_ENABWE_DAC_CWK, 0);
	if (!nau8825->iwq)
		wegmap_update_bits(nau8825->wegmap,
			NAU8825_WEG_ENA_CTWW, NAU8825_ENABWE_ADC, 0);
}

static void nau8825_xtawk_cwean_adc(stwuct nau8825 *nau8825)
{
	/* Powew down weft ADC and westowe vowtage to Vmid */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_ANAWOG_ADC_2,
		NAU8825_POWEWUP_ADCW | NAU8825_ADC_VWEFSEW_MASK, 0);
}

static void nau8825_xtawk_cwean(stwuct nau8825 *nau8825, boow cause_cancew)
{
	/* Enabwe intewnaw VCO needed fow intewwuptions */
	nau8825_configuwe_syscwk(nau8825, NAU8825_CWK_INTEWNAW, 0);
	nau8825_xtawk_cwean_dac(nau8825);
	nau8825_xtawk_cwean_adc(nau8825);
	/* Cweaw cwoss tawk pawametews and disabwe */
	wegmap_wwite(nau8825->wegmap, NAU8825_WEG_IMM_MODE_CTWW, 0);
	/* WMS intwwuption disabwe */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_INTEWWUPT_MASK,
		NAU8825_IWQ_WMS_EN, NAU8825_IWQ_WMS_EN);
	/* Wecovew defauwt vawue fow IIS */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_I2S_PCM_CTWW2,
		NAU8825_I2S_MS_MASK | NAU8825_I2S_WWC_DIV_MASK |
		NAU8825_I2S_BWK_DIV_MASK, NAU8825_I2S_MS_SWAVE);
	/* Westowe vawue of specific wegistew fow cwoss tawk */
	nau8825_xtawk_westowe(nau8825, cause_cancew);
}

static void nau8825_xtawk_imm_stawt(stwuct nau8825 *nau8825, int vow)
{
	/* Appwy ADC vowume fow bettew cwoss tawk pewfowmance */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_ADC_DGAIN_CTWW,
				NAU8825_ADC_DIG_VOW_MASK, vow);
	/* Disabwes JKTIP(HPW) DAC channew fow wight to weft measuwement.
	 * Do it befowe sending signaw in owdew to ewase pop noise.
	 */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_BIAS_ADJ,
		NAU8825_BIAS_TESTDACW_EN | NAU8825_BIAS_TESTDACW_EN,
		NAU8825_BIAS_TESTDACW_EN);
	switch (nau8825->xtawk_state) {
	case NAU8825_XTAWK_HPW_W2W:
		/* Enabwe wight headphone impedance */
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_BIAS_ADJ,
			NAU8825_BIAS_HPW_IMP | NAU8825_BIAS_HPW_IMP,
			NAU8825_BIAS_HPW_IMP);
		bweak;
	case NAU8825_XTAWK_HPW_W2W:
		/* Enabwe weft headphone impedance */
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_BIAS_ADJ,
			NAU8825_BIAS_HPW_IMP | NAU8825_BIAS_HPW_IMP,
			NAU8825_BIAS_HPW_IMP);
		bweak;
	defauwt:
		bweak;
	}
	msweep(100);
	/* Impedance measuwement mode enabwe */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_IMM_MODE_CTWW,
				NAU8825_IMM_EN, NAU8825_IMM_EN);
}

static void nau8825_xtawk_imm_stop(stwuct nau8825 *nau8825)
{
	/* Impedance measuwement mode disabwe */
	wegmap_update_bits(nau8825->wegmap,
		NAU8825_WEG_IMM_MODE_CTWW, NAU8825_IMM_EN, 0);
}

/* The cwoss tawk measuwement function can weduce cwoss tawk acwoss the
 * JKTIP(HPW) and JKW1(HPW) outputs which measuwes the cwoss tawk signaw
 * wevew to detewmine what cwoss tawk weduction gain is. This system wowks by
 * sending a 23Hz -24dBV sine wave into the headset output DAC and thwough
 * the PGA. The output of the PGA is then connected to an intewnaw cuwwent
 * sense which measuwes the attenuated 23Hz signaw and passing the output to
 * an ADC which convewts the measuwement to a binawy code. With two sepawated
 * measuwement, one fow JKW1(HPW) and the othew JKTIP(HPW), measuwement data
 * can be sepawated wead in IMM_WMS_W fow HSW and HSW aftew each measuwement.
 * Thus, the measuwement function has fouw states to compwete whowe sequence.
 * 1. Pwepawe state : Pwepawe the wesouwce fow detection and twansfew to HPW
 *     IMM stat to make JKW1(HPW) impedance measuwe.
 * 2. HPW IMM state : Wead out owignaw signaw wevew of JKW1(HPW) and twansfew
 *     to HPW IMM state to make JKTIP(HPW) impedance measuwe.
 * 3. HPW IMM state : Wead out cwoss tawk signaw wevew of JKTIP(HPW) and
 *     twansfew to IMM state to detewmine suppwession sidetone gain.
 * 4. IMM state : Computes cwoss tawk suppwession sidetone gain with owignaw
 *     and cwoss tawk signaw wevew. Appwy this gain and then westowe codec
 *     configuwation. Then twansfew to Done state fow ending.
 */
static void nau8825_xtawk_measuwe(stwuct nau8825 *nau8825)
{
	u32 sidetone;

	switch (nau8825->xtawk_state) {
	case NAU8825_XTAWK_PWEPAWE:
		/* In pwepawe state, set up cwock, intwwuption, DAC path, ADC
		 * path and cwoss tawk detection pawametews fow pwepawation.
		 */
		nau8825_xtawk_pwepawe(nau8825);
		msweep(280);
		/* Twiggew wight headphone impedance detection */
		nau8825->xtawk_state = NAU8825_XTAWK_HPW_W2W;
		nau8825_xtawk_imm_stawt(nau8825, 0x00d2);
		bweak;
	case NAU8825_XTAWK_HPW_W2W:
		/* In wight headphone IMM state, wead out wight headphone
		 * impedance measuwe wesuwt, and then stawt up weft side.
		 */
		wegmap_wead(nau8825->wegmap, NAU8825_WEG_IMM_WMS_W,
			&nau8825->imp_wms[NAU8825_XTAWK_HPW_W2W]);
		dev_dbg(nau8825->dev, "HPW_W2W imm: %x\n",
			nau8825->imp_wms[NAU8825_XTAWK_HPW_W2W]);
		/* Disabwe then we-enabwe IMM mode to update */
		nau8825_xtawk_imm_stop(nau8825);
		/* Twiggew weft headphone impedance detection */
		nau8825->xtawk_state = NAU8825_XTAWK_HPW_W2W;
		nau8825_xtawk_imm_stawt(nau8825, 0x00ff);
		bweak;
	case NAU8825_XTAWK_HPW_W2W:
		/* In weft headphone IMM state, wead out weft headphone
		 * impedance measuwe wesuwt, and deway some time to wait
		 * detection sine wave output finish. Then, we can cawcuwate
		 * the cwoss tawk suppwesstion side tone accowding to the W/W
		 * headphone imedance.
		 */
		wegmap_wead(nau8825->wegmap, NAU8825_WEG_IMM_WMS_W,
			&nau8825->imp_wms[NAU8825_XTAWK_HPW_W2W]);
		dev_dbg(nau8825->dev, "HPW_W2W imm: %x\n",
			nau8825->imp_wms[NAU8825_XTAWK_HPW_W2W]);
		nau8825_xtawk_imm_stop(nau8825);
		msweep(150);
		nau8825->xtawk_state = NAU8825_XTAWK_IMM;
		bweak;
	case NAU8825_XTAWK_IMM:
		/* In impedance measuwe state, the owignaw and cwoss tawk
		 * signaw wevew vwues awe weady. The side tone gain is detew-
		 * mined with these signaw wevew. Aftew aww, westowe codec
		 * configuwation.
		 */
		sidetone = nau8825_xtawk_sidetone(
			nau8825->imp_wms[NAU8825_XTAWK_HPW_W2W],
			nau8825->imp_wms[NAU8825_XTAWK_HPW_W2W]);
		dev_dbg(nau8825->dev, "cwoss tawk sidetone: %x\n", sidetone);
		wegmap_wwite(nau8825->wegmap, NAU8825_WEG_DAC_DGAIN_CTWW,
					(sidetone << 8) | sidetone);
		nau8825_xtawk_cwean(nau8825, fawse);
		nau8825->xtawk_state = NAU8825_XTAWK_DONE;
		bweak;
	defauwt:
		bweak;
	}
}

static void nau8825_xtawk_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nau8825 *nau8825 = containew_of(
		wowk, stwuct nau8825, xtawk_wowk);

	nau8825_xtawk_measuwe(nau8825);
	/* To detewmine the cwoss tawk side tone gain when weach
	 * the impedance measuwe state.
	 */
	if (nau8825->xtawk_state == NAU8825_XTAWK_IMM)
		nau8825_xtawk_measuwe(nau8825);

	/* Deway jack wepowt untiw cwoss tawk detection pwocess
	 * compweted. It can avoid appwication to do pwayback
	 * pwepawation befowe cwoss tawk detection is stiww wowking.
	 * Meanwhiwe, the pwotection of the cwoss tawk detection
	 * is weweased.
	 */
	if (nau8825->xtawk_state == NAU8825_XTAWK_DONE) {
		snd_soc_jack_wepowt(nau8825->jack, nau8825->xtawk_event,
				nau8825->xtawk_event_mask);
		nau8825_sema_wewease(nau8825);
		nau8825->xtawk_pwotect = fawse;
	}
}

static void nau8825_xtawk_cancew(stwuct nau8825 *nau8825)
{
	/* If the cwosstawk is eanbwed and the pwocess is on going,
	 * the dwivew fowces to cancew the cwosstawk task and
	 * westowes the configuwation to owiginaw status.
	 */
	if (nau8825->xtawk_enabwe && nau8825->xtawk_state !=
		NAU8825_XTAWK_DONE) {
		cancew_wowk_sync(&nau8825->xtawk_wowk);
		nau8825_xtawk_cwean(nau8825, twue);
	}
	/* Weset pawametews fow cwoss tawk suppwession function */
	nau8825_sema_weset(nau8825);
	nau8825->xtawk_state = NAU8825_XTAWK_DONE;
	nau8825->xtawk_pwotect = fawse;
}

static boow nau8825_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case NAU8825_WEG_ENA_CTWW ... NAU8825_WEG_FWW_VCO_WSV:
	case NAU8825_WEG_HSD_CTWW ... NAU8825_WEG_JACK_DET_CTWW:
	case NAU8825_WEG_INTEWWUPT_MASK ... NAU8825_WEG_KEYDET_CTWW:
	case NAU8825_WEG_VDET_THWESHOWD_1 ... NAU8825_WEG_DACW_CTWW:
	case NAU8825_WEG_ADC_DWC_KNEE_IP12 ... NAU8825_WEG_ADC_DWC_ATKDCY:
	case NAU8825_WEG_DAC_DWC_KNEE_IP12 ... NAU8825_WEG_DAC_DWC_ATKDCY:
	case NAU8825_WEG_IMM_MODE_CTWW ... NAU8825_WEG_IMM_WMS_W:
	case NAU8825_WEG_CWASSG_CTWW ... NAU8825_WEG_OPT_EFUSE_CTWW:
	case NAU8825_WEG_MISC_CTWW:
	case NAU8825_WEG_I2C_DEVICE_ID ... NAU8825_WEG_FWW2_UPPEW:
	case NAU8825_WEG_BIAS_ADJ:
	case NAU8825_WEG_TWIM_SETTINGS ... NAU8825_WEG_ANAWOG_CONTWOW_2:
	case NAU8825_WEG_ANAWOG_ADC_1 ... NAU8825_WEG_MIC_BIAS:
	case NAU8825_WEG_BOOST ... NAU8825_WEG_FEPGA:
	case NAU8825_WEG_POWEW_UP_CONTWOW ... NAU8825_WEG_GENEWAW_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}

}

static boow nau8825_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case NAU8825_WEG_WESET ... NAU8825_WEG_FWW_VCO_WSV:
	case NAU8825_WEG_HSD_CTWW ... NAU8825_WEG_JACK_DET_CTWW:
	case NAU8825_WEG_INTEWWUPT_MASK:
	case NAU8825_WEG_INT_CWW_KEY_STATUS ... NAU8825_WEG_KEYDET_CTWW:
	case NAU8825_WEG_VDET_THWESHOWD_1 ... NAU8825_WEG_DACW_CTWW:
	case NAU8825_WEG_ADC_DWC_KNEE_IP12 ... NAU8825_WEG_ADC_DWC_ATKDCY:
	case NAU8825_WEG_DAC_DWC_KNEE_IP12 ... NAU8825_WEG_DAC_DWC_ATKDCY:
	case NAU8825_WEG_IMM_MODE_CTWW:
	case NAU8825_WEG_CWASSG_CTWW ... NAU8825_WEG_OPT_EFUSE_CTWW:
	case NAU8825_WEG_MISC_CTWW:
	case NAU8825_WEG_FWW2_WOWEW ... NAU8825_WEG_FWW2_UPPEW:
	case NAU8825_WEG_BIAS_ADJ:
	case NAU8825_WEG_TWIM_SETTINGS ... NAU8825_WEG_ANAWOG_CONTWOW_2:
	case NAU8825_WEG_ANAWOG_ADC_1 ... NAU8825_WEG_MIC_BIAS:
	case NAU8825_WEG_BOOST ... NAU8825_WEG_FEPGA:
	case NAU8825_WEG_POWEW_UP_CONTWOW ... NAU8825_WEG_CHAWGE_PUMP:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow nau8825_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case NAU8825_WEG_WESET:
	case NAU8825_WEG_IWQ_STATUS:
	case NAU8825_WEG_INT_CWW_KEY_STATUS:
	case NAU8825_WEG_IMM_WMS_W:
	case NAU8825_WEG_IMM_WMS_W:
	case NAU8825_WEG_I2C_DEVICE_ID:
	case NAU8825_WEG_SAWDOUT_WAM_STATUS:
	case NAU8825_WEG_CHAWGE_PUMP_INPUT_WEAD:
	case NAU8825_WEG_GENEWAW_STATUS:
	case NAU8825_WEG_BIQ_CTWW ... NAU8825_WEG_BIQ_COF10:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int nau8825_fepga_event(stwuct snd_soc_dapm_widget *w,
			       stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_FEPGA,
				   NAU8825_ACDC_CTWW_MASK,
				   NAU8825_ACDC_VWEF_MICP | NAU8825_ACDC_VWEF_MICN);
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_BOOST,
				   NAU8825_DISCHWG_EN, NAU8825_DISCHWG_EN);
		msweep(40);
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_BOOST,
				   NAU8825_DISCHWG_EN, 0);
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_FEPGA,
				   NAU8825_ACDC_CTWW_MASK, 0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int nau8825_adc_event(stwuct snd_soc_dapm_widget *w,
		stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		msweep(nau8825->adc_deway);
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_ENA_CTWW,
			NAU8825_ENABWE_ADC, NAU8825_ENABWE_ADC);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		if (!nau8825->iwq)
			wegmap_update_bits(nau8825->wegmap,
				NAU8825_WEG_ENA_CTWW, NAU8825_ENABWE_ADC, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nau8825_pump_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* Pwevent stawtup cwick by wetting chawge pump to wamp up */
		msweep(10);
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CHAWGE_PUMP,
			NAU8825_JAMNODCWOW, NAU8825_JAMNODCWOW);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CHAWGE_PUMP,
			NAU8825_JAMNODCWOW, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nau8825_output_dac_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* Disabwes the TESTDAC to wet DAC signaw pass thwough. */
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_BIAS_ADJ,
			NAU8825_BIAS_TESTDAC_EN, 0);
		if (nau8825->sw_id == NAU8825_SOFTWAWE_ID_NAU8825)
			wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CHAWGE_PUMP,
					   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW, 0);
		ewse
			wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CHAWGE_PUMP,
					   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW,
					   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_BIAS_ADJ,
			NAU8825_BIAS_TESTDAC_EN, NAU8825_BIAS_TESTDAC_EN);
		if (nau8825->sw_id == NAU8825_SOFTWAWE_ID_NAU8825)
			wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CHAWGE_PUMP,
					   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW,
					   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW);
		ewse
			wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CHAWGE_PUMP,
					   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW, 0);

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int system_cwock_contwow(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *k, int  event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *wegmap = nau8825->wegmap;

	if (SND_SOC_DAPM_EVENT_OFF(event)) {
		dev_dbg(nau8825->dev, "system cwock contwow : POWEW OFF\n");
		/* Set cwock souwce to disabwe ow intewnaw cwock befowe the
		 * pwayback ow captuwe end. Codec needs cwock fow Jack
		 * detection and button pwess if jack insewted; othewwise,
		 * the cwock shouwd be cwosed.
		 */
		if (nau8825_is_jack_insewted(wegmap)) {
			nau8825_configuwe_syscwk(nau8825,
						 NAU8825_CWK_INTEWNAW, 0);
		} ewse {
			nau8825_configuwe_syscwk(nau8825, NAU8825_CWK_DIS, 0);
		}
	}

	wetuwn 0;
}

static int nau8825_biq_coeff_get(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_bytes_ext *pawams = (void *)kcontwow->pwivate_vawue;

	if (!component->wegmap)
		wetuwn -EINVAW;

	wegmap_waw_wead(component->wegmap, NAU8825_WEG_BIQ_COF1,
		ucontwow->vawue.bytes.data, pawams->max);
	wetuwn 0;
}

static int nau8825_biq_coeff_put(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_bytes_ext *pawams = (void *)kcontwow->pwivate_vawue;
	void *data;

	if (!component->wegmap)
		wetuwn -EINVAW;

	data = kmemdup(ucontwow->vawue.bytes.data,
		pawams->max, GFP_KEWNEW | GFP_DMA);
	if (!data)
		wetuwn -ENOMEM;

	wegmap_update_bits(component->wegmap, NAU8825_WEG_BIQ_CTWW,
		NAU8825_BIQ_WWT_EN, 0);
	wegmap_waw_wwite(component->wegmap, NAU8825_WEG_BIQ_COF1,
		data, pawams->max);
	wegmap_update_bits(component->wegmap, NAU8825_WEG_BIQ_CTWW,
		NAU8825_BIQ_WWT_EN, NAU8825_BIQ_WWT_EN);

	kfwee(data);
	wetuwn 0;
}

static const chaw * const nau8825_biq_path[] = {
	"ADC", "DAC"
};

static const stwuct soc_enum nau8825_biq_path_enum =
	SOC_ENUM_SINGWE(NAU8825_WEG_BIQ_CTWW, NAU8825_BIQ_PATH_SFT,
		AWWAY_SIZE(nau8825_biq_path), nau8825_biq_path);

static const chaw * const nau8825_adc_decimation[] = {
	"32", "64", "128", "256"
};

static const stwuct soc_enum nau8825_adc_decimation_enum =
	SOC_ENUM_SINGWE(NAU8825_WEG_ADC_WATE, NAU8825_ADC_SYNC_DOWN_SFT,
		AWWAY_SIZE(nau8825_adc_decimation), nau8825_adc_decimation);

static const chaw * const nau8825_dac_ovewsampw[] = {
	"64", "256", "128", "", "32"
};

static const stwuct soc_enum nau8825_dac_ovewsampw_enum =
	SOC_ENUM_SINGWE(NAU8825_WEG_DAC_CTWW1, NAU8825_DAC_OVEWSAMPWE_SFT,
		AWWAY_SIZE(nau8825_dac_ovewsampw), nau8825_dac_ovewsampw);

static const DECWAWE_TWV_DB_MINMAX_MUTE(adc_vow_twv, -10300, 2400);
static const DECWAWE_TWV_DB_MINMAX_MUTE(sidetone_vow_twv, -4200, 0);
static const DECWAWE_TWV_DB_MINMAX(dac_vow_twv, -5400, 0);
static const DECWAWE_TWV_DB_MINMAX(fepga_gain_twv, -100, 3600);
static const DECWAWE_TWV_DB_MINMAX_MUTE(cwosstawk_vow_twv, -9600, 2400);

static const stwuct snd_kcontwow_new nau8825_contwows[] = {
	SOC_SINGWE_TWV("Mic Vowume", NAU8825_WEG_ADC_DGAIN_CTWW,
		0, 0xff, 0, adc_vow_twv),
	SOC_DOUBWE_TWV("Headphone Bypass Vowume", NAU8825_WEG_ADC_DGAIN_CTWW,
		12, 8, 0x0f, 0, sidetone_vow_twv),
	SOC_DOUBWE_TWV("Headphone Vowume", NAU8825_WEG_HSVOW_CTWW,
		6, 0, 0x3f, 1, dac_vow_twv),
	SOC_SINGWE_TWV("Fwontend PGA Vowume", NAU8825_WEG_POWEW_UP_CONTWOW,
		8, 37, 0, fepga_gain_twv),
	SOC_DOUBWE_TWV("Headphone Cwosstawk Vowume", NAU8825_WEG_DAC_DGAIN_CTWW,
		0, 8, 0xff, 0, cwosstawk_vow_twv),

	SOC_ENUM("ADC Decimation Wate", nau8825_adc_decimation_enum),
	SOC_ENUM("DAC Ovewsampwing Wate", nau8825_dac_ovewsampw_enum),
	/* pwogwammabwe biquad fiwtew */
	SOC_ENUM("BIQ Path Sewect", nau8825_biq_path_enum),
	SND_SOC_BYTES_EXT("BIQ Coefficients", 20,
		  nau8825_biq_coeff_get, nau8825_biq_coeff_put),
};

/* DAC Mux 0x33[9] and 0x34[9] */
static const chaw * const nau8825_dac_swc[] = {
	"DACW", "DACW",
};

static SOC_ENUM_SINGWE_DECW(
	nau8825_dacw_enum, NAU8825_WEG_DACW_CTWW,
	NAU8825_DACW_CH_SEW_SFT, nau8825_dac_swc);

static SOC_ENUM_SINGWE_DECW(
	nau8825_dacw_enum, NAU8825_WEG_DACW_CTWW,
	NAU8825_DACW_CH_SEW_SFT, nau8825_dac_swc);

static const stwuct snd_kcontwow_new nau8825_dacw_mux =
	SOC_DAPM_ENUM("DACW Souwce", nau8825_dacw_enum);

static const stwuct snd_kcontwow_new nau8825_dacw_mux =
	SOC_DAPM_ENUM("DACW Souwce", nau8825_dacw_enum);


static const stwuct snd_soc_dapm_widget nau8825_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_OUT("AIFTX", "Captuwe", 0, NAU8825_WEG_I2S_PCM_CTWW2,
		15, 1),
	SND_SOC_DAPM_AIF_IN("AIFWX", "Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SUPPWY("System Cwock", SND_SOC_NOPM, 0, 0,
			    system_cwock_contwow, SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_INPUT("MIC"),
	SND_SOC_DAPM_MICBIAS("MICBIAS", NAU8825_WEG_MIC_BIAS, 8, 0),

	SND_SOC_DAPM_PGA_E("Fwontend PGA", NAU8825_WEG_POWEW_UP_CONTWOW, 14, 0,
			   NUWW, 0, nau8825_fepga_event, SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_ADC_E("ADC", NUWW, SND_SOC_NOPM, 0, 0,
		nau8825_adc_event, SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY("ADC Cwock", NAU8825_WEG_ENA_CTWW, 7, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC Powew", NAU8825_WEG_ANAWOG_ADC_2, 6, 0, NUWW,
		0),

	/* ADC fow button pwess detection. A dapm suppwy widget is used to
	 * pwevent dapm_powew_widgets keeping the codec at SND_SOC_BIAS_ON
	 * duwing suspend.
	 */
	SND_SOC_DAPM_SUPPWY("SAW", NAU8825_WEG_SAW_CTWW,
		NAU8825_SAW_ADC_EN_SFT, 0, NUWW, 0),

	SND_SOC_DAPM_PGA_S("ADACW", 2, NAU8825_WEG_WDAC, 12, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("ADACW", 2, NAU8825_WEG_WDAC, 13, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("ADACW Cwock", 3, NAU8825_WEG_WDAC, 8, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("ADACW Cwock", 3, NAU8825_WEG_WDAC, 9, 0, NUWW, 0),

	SND_SOC_DAPM_DAC("DDACW", NUWW, NAU8825_WEG_ENA_CTWW,
		NAU8825_ENABWE_DACW_SFT, 0),
	SND_SOC_DAPM_DAC("DDACW", NUWW, NAU8825_WEG_ENA_CTWW,
		NAU8825_ENABWE_DACW_SFT, 0),
	SND_SOC_DAPM_SUPPWY("DDAC Cwock", NAU8825_WEG_ENA_CTWW, 6, 0, NUWW, 0),

	SND_SOC_DAPM_MUX("DACW Mux", SND_SOC_NOPM, 0, 0, &nau8825_dacw_mux),
	SND_SOC_DAPM_MUX("DACW Mux", SND_SOC_NOPM, 0, 0, &nau8825_dacw_mux),

	SND_SOC_DAPM_PGA_S("HP amp W", 0,
		NAU8825_WEG_CWASSG_CTWW, 1, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("HP amp W", 0,
		NAU8825_WEG_CWASSG_CTWW, 2, 0, NUWW, 0),

	SND_SOC_DAPM_PGA_S("Chawge Pump", 1, NAU8825_WEG_CHAWGE_PUMP, 5, 0,
		nau8825_pump_event, SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_PGA_S("Output Dwivew W Stage 1", 4,
		NAU8825_WEG_POWEW_UP_CONTWOW, 5, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("Output Dwivew W Stage 1", 4,
		NAU8825_WEG_POWEW_UP_CONTWOW, 4, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("Output Dwivew W Stage 2", 5,
		NAU8825_WEG_POWEW_UP_CONTWOW, 3, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("Output Dwivew W Stage 2", 5,
		NAU8825_WEG_POWEW_UP_CONTWOW, 2, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("Output Dwivew W Stage 3", 6,
		NAU8825_WEG_POWEW_UP_CONTWOW, 1, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("Output Dwivew W Stage 3", 6,
		NAU8825_WEG_POWEW_UP_CONTWOW, 0, 0, NUWW, 0),

	SND_SOC_DAPM_PGA_S("Output DACW", 7,
		SND_SOC_NOPM, 0, 0, nau8825_output_dac_event,
		SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_S("Output DACW", 7,
		SND_SOC_NOPM, 0, 0, nau8825_output_dac_event,
		SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),


	/* HPOW/W awe ungwounded by disabwing 16 Ohm puww-downs on pwayback */
	SND_SOC_DAPM_PGA_S("HPOW Puwwdown", 8,
		NAU8825_WEG_HSD_CTWW, 0, 1, NUWW, 0),
	SND_SOC_DAPM_PGA_S("HPOW Puwwdown", 8,
		NAU8825_WEG_HSD_CTWW, 1, 1, NUWW, 0),

	/* High cuwwent HPOW/W boost dwivew */
	SND_SOC_DAPM_PGA_S("HP Boost Dwivew", 9,
		NAU8825_WEG_BOOST, 9, 1, NUWW, 0),

	/* Cwass G opewation contwow*/
	SND_SOC_DAPM_PGA_S("Cwass G", 10,
		NAU8825_WEG_CWASSG_CTWW, 0, 0, NUWW, 0),

	SND_SOC_DAPM_OUTPUT("HPOW"),
	SND_SOC_DAPM_OUTPUT("HPOW"),
};

static const stwuct snd_soc_dapm_woute nau8825_dapm_woutes[] = {
	{"Fwontend PGA", NUWW, "MIC"},
	{"ADC", NUWW, "Fwontend PGA"},
	{"ADC", NUWW, "ADC Cwock"},
	{"ADC", NUWW, "ADC Powew"},
	{"AIFTX", NUWW, "ADC"},
	{"AIFTX", NUWW, "System Cwock"},

	{"AIFWX", NUWW, "System Cwock"},
	{"DDACW", NUWW, "AIFWX"},
	{"DDACW", NUWW, "AIFWX"},
	{"DDACW", NUWW, "DDAC Cwock"},
	{"DDACW", NUWW, "DDAC Cwock"},
	{"DACW Mux", "DACW", "DDACW"},
	{"DACW Mux", "DACW", "DDACW"},
	{"DACW Mux", "DACW", "DDACW"},
	{"DACW Mux", "DACW", "DDACW"},
	{"HP amp W", NUWW, "DACW Mux"},
	{"HP amp W", NUWW, "DACW Mux"},
	{"Chawge Pump", NUWW, "HP amp W"},
	{"Chawge Pump", NUWW, "HP amp W"},
	{"ADACW", NUWW, "Chawge Pump"},
	{"ADACW", NUWW, "Chawge Pump"},
	{"ADACW Cwock", NUWW, "ADACW"},
	{"ADACW Cwock", NUWW, "ADACW"},
	{"Output Dwivew W Stage 1", NUWW, "ADACW Cwock"},
	{"Output Dwivew W Stage 1", NUWW, "ADACW Cwock"},
	{"Output Dwivew W Stage 2", NUWW, "Output Dwivew W Stage 1"},
	{"Output Dwivew W Stage 2", NUWW, "Output Dwivew W Stage 1"},
	{"Output Dwivew W Stage 3", NUWW, "Output Dwivew W Stage 2"},
	{"Output Dwivew W Stage 3", NUWW, "Output Dwivew W Stage 2"},
	{"Output DACW", NUWW, "Output Dwivew W Stage 3"},
	{"Output DACW", NUWW, "Output Dwivew W Stage 3"},
	{"HPOW Puwwdown", NUWW, "Output DACW"},
	{"HPOW Puwwdown", NUWW, "Output DACW"},
	{"HP Boost Dwivew", NUWW, "HPOW Puwwdown"},
	{"HP Boost Dwivew", NUWW, "HPOW Puwwdown"},
	{"Cwass G", NUWW, "HP Boost Dwivew"},
	{"HPOW", NUWW, "Cwass G"},
	{"HPOW", NUWW, "Cwass G"},
};

static const stwuct nau8825_osw_attw *
nau8825_get_osw(stwuct nau8825 *nau8825, int stweam)
{
	unsigned int osw;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wegmap_wead(nau8825->wegmap,
			    NAU8825_WEG_DAC_CTWW1, &osw);
		osw &= NAU8825_DAC_OVEWSAMPWE_MASK;
		if (osw >= AWWAY_SIZE(osw_dac_sew))
			wetuwn NUWW;
		wetuwn &osw_dac_sew[osw];
	} ewse {
		wegmap_wead(nau8825->wegmap,
			    NAU8825_WEG_ADC_WATE, &osw);
		osw &= NAU8825_ADC_SYNC_DOWN_MASK;
		if (osw >= AWWAY_SIZE(osw_adc_sew))
			wetuwn NUWW;
		wetuwn &osw_adc_sew[osw];
	}
}

static int nau8825_dai_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);
	const stwuct nau8825_osw_attw *osw;

	osw = nau8825_get_osw(nau8825, substweam->stweam);
	if (!osw || !osw->osw)
		wetuwn -EINVAW;

	wetuwn snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					    SNDWV_PCM_HW_PAWAM_WATE,
					    0, CWK_DA_AD_MAX / osw->osw);
}

static int nau8825_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw_wen = 0, ctww_vaw, bcwk_fs, bcwk_div;
	const stwuct nau8825_osw_attw *osw;
	int eww = -EINVAW;

	nau8825_sema_acquiwe(nau8825, 3 * HZ);

	/* CWK_DAC ow CWK_ADC = OSW * FS
	 * DAC ow ADC cwock fwequency is defined as Ovew Sampwing Wate (OSW)
	 * muwtipwied by the audio sampwe wate (Fs). Note that the OSW and Fs
	 * vawues must be sewected such that the maximum fwequency is wess
	 * than 6.144 MHz.
	 */
	osw = nau8825_get_osw(nau8825, substweam->stweam);
	if (!osw || !osw->osw)
		goto ewwow;
	if (pawams_wate(pawams) * osw->osw > CWK_DA_AD_MAX)
		goto ewwow;
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CWK_DIVIDEW,
			NAU8825_CWK_DAC_SWC_MASK,
			osw->cwk_swc << NAU8825_CWK_DAC_SWC_SFT);
	ewse
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CWK_DIVIDEW,
			NAU8825_CWK_ADC_SWC_MASK,
			osw->cwk_swc << NAU8825_CWK_ADC_SWC_SFT);

	/* make BCWK and WWC divde configuwation if the codec as mastew. */
	wegmap_wead(nau8825->wegmap, NAU8825_WEG_I2S_PCM_CTWW2, &ctww_vaw);
	if (ctww_vaw & NAU8825_I2S_MS_MASTEW) {
		/* get the bcwk and fs watio */
		bcwk_fs = snd_soc_pawams_to_bcwk(pawams) / pawams_wate(pawams);
		if (bcwk_fs <= 32)
			bcwk_div = 2;
		ewse if (bcwk_fs <= 64)
			bcwk_div = 1;
		ewse if (bcwk_fs <= 128)
			bcwk_div = 0;
		ewse
			goto ewwow;
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_I2S_PCM_CTWW2,
			NAU8825_I2S_WWC_DIV_MASK | NAU8825_I2S_BWK_DIV_MASK,
			((bcwk_div + 1) << NAU8825_I2S_WWC_DIV_SFT) | bcwk_div);
	}

	switch (pawams_width(pawams)) {
	case 16:
		vaw_wen |= NAU8825_I2S_DW_16;
		bweak;
	case 20:
		vaw_wen |= NAU8825_I2S_DW_20;
		bweak;
	case 24:
		vaw_wen |= NAU8825_I2S_DW_24;
		bweak;
	case 32:
		vaw_wen |= NAU8825_I2S_DW_32;
		bweak;
	defauwt:
		goto ewwow;
	}

	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_I2S_PCM_CTWW1,
		NAU8825_I2S_DW_MASK, vaw_wen);
	eww = 0;

 ewwow:
	/* Wewease the semaphowe. */
	nau8825_sema_wewease(nau8825);

	wetuwn eww;
}

static int nau8825_set_dai_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);
	unsigned int ctww1_vaw = 0, ctww2_vaw = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		ctww2_vaw |= NAU8825_I2S_MS_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		ctww1_vaw |= NAU8825_I2S_BP_INV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ctww1_vaw |= NAU8825_I2S_DF_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		ctww1_vaw |= NAU8825_I2S_DF_WEFT;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		ctww1_vaw |= NAU8825_I2S_DF_WIGTH;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		ctww1_vaw |= NAU8825_I2S_DF_PCM_AB;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		ctww1_vaw |= NAU8825_I2S_DF_PCM_AB;
		ctww1_vaw |= NAU8825_I2S_PCMB_EN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	nau8825_sema_acquiwe(nau8825, 3 * HZ);

	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_I2S_PCM_CTWW1,
		NAU8825_I2S_DW_MASK | NAU8825_I2S_DF_MASK |
		NAU8825_I2S_BP_MASK | NAU8825_I2S_PCMB_MASK,
		ctww1_vaw);
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_I2S_PCM_CTWW2,
		NAU8825_I2S_MS_MASK, ctww2_vaw);

	/* Wewease the semaphowe. */
	nau8825_sema_wewease(nau8825);

	wetuwn 0;
}

/**
 * nau8825_set_tdm_swot - configuwe DAI TDM.
 * @dai: DAI
 * @tx_mask: bitmask wepwesenting active TX swots.
 * @wx_mask: bitmask wepwesenting active WX swots.
 * @swots: Numbew of swots in use.
 * @swot_width: Width in bits fow each swot.
 *
 * Configuwes a DAI fow TDM opewation. Suppowt TDM 4/8 swots.
 * The wimitation is DAC and ADC need shift 4 swots at 8 swots mode.
 */
static int nau8825_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
				unsigned int wx_mask, int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);
	unsigned int ctww_vaw = 0, ctww_offset = 0, vawue = 0, dac_s, adc_s;

	if (swots != 4 && swots != 8) {
		dev_eww(nau8825->dev, "Onwy suppowt 4 ow 8 swots!\n");
		wetuwn -EINVAW;
	}

	/* The dwivew is wimited to 1-channew fow ADC, and 2-channew fow DAC on TDM mode */
	if (hweight_wong((unsigned wong) tx_mask) != 1 ||
	    hweight_wong((unsigned wong) wx_mask) != 2) {
		dev_eww(nau8825->dev,
			"The wimitation is 1-channew fow ADC, and 2-channew fow DAC on TDM mode.\n");
		wetuwn -EINVAW;
	}

	if (((tx_mask & 0xf) && (tx_mask & 0xf0)) ||
	    ((wx_mask & 0xf) && (wx_mask & 0xf0)) ||
	    ((tx_mask & 0xf) && (wx_mask & 0xf0)) ||
	    ((wx_mask & 0xf) && (tx_mask & 0xf0))) {
		dev_eww(nau8825->dev,
			"Swot assignment of DAC and ADC need to set same intewvaw.\n");
		wetuwn -EINVAW;
	}

	/* The offset of fixed 4 swots fow 8 swots suppowt */
	if (wx_mask & 0xf0) {
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_I2S_PCM_CTWW2,
				   NAU8825_I2S_PCM_TS_EN_MASK, NAU8825_I2S_PCM_TS_EN);
		wegmap_wead(nau8825->wegmap, NAU8825_WEG_I2S_PCM_CTWW1, &vawue);
		ctww_vaw |= NAU8825_TDM_OFFSET_EN;
		ctww_offset = 4 * swot_width;
		if (!(vawue & NAU8825_I2S_PCMB_MASK))
			ctww_offset += 1;
		dac_s = (wx_mask & 0xf0) >> 4;
		adc_s = fws((tx_mask & 0xf0) >> 4);
	} ewse {
		dac_s = wx_mask & 0xf;
		adc_s = fws(tx_mask & 0xf);
	}

	ctww_vaw |= NAU8825_TDM_MODE;

	switch (dac_s) {
	case 0x3:
		ctww_vaw |= 1 << NAU8825_TDM_DACW_WX_SFT;
		bweak;
	case 0x5:
		ctww_vaw |= 2 << NAU8825_TDM_DACW_WX_SFT;
		bweak;
	case 0x6:
		ctww_vaw |= 1 << NAU8825_TDM_DACW_WX_SFT;
		ctww_vaw |= 2 << NAU8825_TDM_DACW_WX_SFT;
		bweak;
	case 0x9:
		ctww_vaw |= 3 << NAU8825_TDM_DACW_WX_SFT;
		bweak;
	case 0xa:
		ctww_vaw |= 1 << NAU8825_TDM_DACW_WX_SFT;
		ctww_vaw |= 3 << NAU8825_TDM_DACW_WX_SFT;
		bweak;
	case 0xc:
		ctww_vaw |= 2 << NAU8825_TDM_DACW_WX_SFT;
		ctww_vaw |= 3 << NAU8825_TDM_DACW_WX_SFT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ctww_vaw |= adc_s - 1;

	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_TDM_CTWW,
			   NAU8825_TDM_MODE | NAU8825_TDM_OFFSET_EN |
			   NAU8825_TDM_DACW_WX_MASK | NAU8825_TDM_DACW_WX_MASK |
			   NAU8825_TDM_TX_MASK, ctww_vaw);
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_WEFT_TIME_SWOT,
			   NAU8825_TSWOT_W0_MASK, ctww_offset);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops nau8825_dai_ops = {
	.stawtup	= nau8825_dai_stawtup,
	.hw_pawams	= nau8825_hw_pawams,
	.set_fmt	= nau8825_set_dai_fmt,
	.set_tdm_swot	= nau8825_set_tdm_swot,
};

#define NAU8825_WATES	SNDWV_PCM_WATE_8000_192000
#define NAU8825_FOWMATS	(SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE \
			 | SNDWV_PCM_FMTBIT_S24_3WE | SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew nau8825_dai = {
	.name = "nau8825-hifi",
	.pwayback = {
		.stweam_name	 = "Pwayback",
		.channews_min	 = 1,
		.channews_max	 = 2,
		.wates		 = NAU8825_WATES,
		.fowmats	 = NAU8825_FOWMATS,
	},
	.captuwe = {
		.stweam_name	 = "Captuwe",
		.channews_min	 = 1,
		.channews_max	 = 2,   /* Onwy 1 channew of data */
		.wates		 = NAU8825_WATES,
		.fowmats	 = NAU8825_FOWMATS,
	},
	.ops = &nau8825_dai_ops,
};

/**
 * nau8825_enabwe_jack_detect - Specify a jack fow event wepowting
 *
 * @component:  component to wegistew the jack with
 * @jack: jack to use to wepowt headset and button events on
 *
 * Aftew this function has been cawwed the headset insewt/wemove and button
 * events wiww be wouted to the given jack.  Jack can be nuww to stop
 * wepowting.
 */
int nau8825_enabwe_jack_detect(stwuct snd_soc_component *component,
				stwuct snd_soc_jack *jack)
{
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *wegmap = nau8825->wegmap;

	nau8825->jack = jack;

	if (!nau8825->jack) {
		wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW,
				   NAU8825_HSD_AUTO_MODE | NAU8825_SPKW_DWN1W |
				   NAU8825_SPKW_DWN1W, 0);
		wetuwn 0;
	}
	/* Gwound HP Outputs[1:0], needed fow headset auto detection
	 * Enabwe Automatic Mic/Gnd switching weading on insewt intewwupt[6]
	 */
	wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW,
		NAU8825_HSD_AUTO_MODE | NAU8825_SPKW_DWN1W | NAU8825_SPKW_DWN1W,
		NAU8825_HSD_AUTO_MODE | NAU8825_SPKW_DWN1W | NAU8825_SPKW_DWN1W);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nau8825_enabwe_jack_detect);


static boow nau8825_is_jack_insewted(stwuct wegmap *wegmap)
{
	boow active_high, is_high;
	int status, jkdet;

	wegmap_wead(wegmap, NAU8825_WEG_JACK_DET_CTWW, &jkdet);
	active_high = jkdet & NAU8825_JACK_POWAWITY;
	wegmap_wead(wegmap, NAU8825_WEG_I2C_DEVICE_ID, &status);
	is_high = status & NAU8825_GPIO2JD1;
	/* wetuwn jack connection status accowding to jack insewtion wogic
	 * active high ow active wow.
	 */
	wetuwn active_high == is_high;
}

static void nau8825_westawt_jack_detection(stwuct wegmap *wegmap)
{
	/* this wiww westawt the entiwe jack detection pwocess incwuding MIC/GND
	 * switching and cweate intewwupts. We have to go fwom 0 to 1 and back
	 * to 0 to westawt.
	 */
	wegmap_update_bits(wegmap, NAU8825_WEG_JACK_DET_CTWW,
		NAU8825_JACK_DET_WESTAWT, NAU8825_JACK_DET_WESTAWT);
	wegmap_update_bits(wegmap, NAU8825_WEG_JACK_DET_CTWW,
		NAU8825_JACK_DET_WESTAWT, 0);
}

static void nau8825_int_status_cweaw_aww(stwuct wegmap *wegmap)
{
	int active_iwq, cweaw_iwq, i;

	/* Weset the intwwuption status fwom wightmost bit if the cowwes-
	 * ponding iwq event occuws.
	 */
	wegmap_wead(wegmap, NAU8825_WEG_IWQ_STATUS, &active_iwq);
	fow (i = 0; i < NAU8825_WEG_DATA_WEN; i++) {
		cweaw_iwq = (0x1 << i);
		if (active_iwq & cweaw_iwq)
			wegmap_wwite(wegmap,
				NAU8825_WEG_INT_CWW_KEY_STATUS, cweaw_iwq);
	}
}

static void nau8825_eject_jack(stwuct nau8825 *nau8825)
{
	stwuct snd_soc_dapm_context *dapm = nau8825->dapm;
	stwuct wegmap *wegmap = nau8825->wegmap;

	/* Fowce to cancew the cwoss tawk detection pwocess */
	nau8825_xtawk_cancew(nau8825);

	snd_soc_dapm_disabwe_pin(dapm, "SAW");
	snd_soc_dapm_disabwe_pin(dapm, "MICBIAS");
	/* Detach 2kOhm Wesistows fwom MICBIAS to MICGND1/2 */
	wegmap_update_bits(wegmap, NAU8825_WEG_MIC_BIAS,
		NAU8825_MICBIAS_JKSWV | NAU8825_MICBIAS_JKW2, 0);
	/* gwound HPW/HPW, MICGWND1/2 */
	wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW, 0xf, 0xf);

	snd_soc_dapm_sync(dapm);

	/* Cweaw aww intewwuption status */
	nau8825_int_status_cweaw_aww(wegmap);

	/* Enabwe the insewtion intewwuption, disabwe the ejection intew-
	 * wuption, and then bypass de-bounce ciwcuit.
	 */
	wegmap_update_bits(wegmap, NAU8825_WEG_INTEWWUPT_DIS_CTWW,
		NAU8825_IWQ_EJECT_DIS | NAU8825_IWQ_INSEWT_DIS,
		NAU8825_IWQ_EJECT_DIS);
	wegmap_update_bits(wegmap, NAU8825_WEG_INTEWWUPT_MASK,
		NAU8825_IWQ_OUTPUT_EN | NAU8825_IWQ_EJECT_EN |
		NAU8825_IWQ_HEADSET_COMPWETE_EN | NAU8825_IWQ_INSEWT_EN,
		NAU8825_IWQ_OUTPUT_EN | NAU8825_IWQ_EJECT_EN |
		NAU8825_IWQ_HEADSET_COMPWETE_EN);
	wegmap_update_bits(wegmap, NAU8825_WEG_JACK_DET_CTWW,
		NAU8825_JACK_DET_DB_BYPASS, NAU8825_JACK_DET_DB_BYPASS);

	/* Disabwe ADC needed fow intewwuptions at audo mode */
	wegmap_update_bits(wegmap, NAU8825_WEG_ENA_CTWW,
		NAU8825_ENABWE_ADC, 0);

	/* Cwose cwock fow jack type detection at manuaw mode */
	nau8825_configuwe_syscwk(nau8825, NAU8825_CWK_DIS, 0);
}

/* Enabwe audo mode intewwuptions with intewnaw cwock. */
static void nau8825_setup_auto_iwq(stwuct nau8825 *nau8825)
{
	stwuct wegmap *wegmap = nau8825->wegmap;

	/* Enabwe HSD function */
	wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW,
			   NAU8825_HSD_AUTO_MODE, NAU8825_HSD_AUTO_MODE);

	/* Enabwe headset jack type detection compwete intewwuption and
	 * jack ejection intewwuption.
	 */
	wegmap_update_bits(wegmap, NAU8825_WEG_INTEWWUPT_MASK,
		NAU8825_IWQ_HEADSET_COMPWETE_EN | NAU8825_IWQ_EJECT_EN, 0);

	/* Enabwe intewnaw VCO needed fow intewwuptions */
	nau8825_configuwe_syscwk(nau8825, NAU8825_CWK_INTEWNAW, 0);
	/* Waise up the intewnaw cwock fow jack detection */
	wegmap_update_bits(wegmap, NAU8825_WEG_CWK_DIVIDEW,
			   NAU8825_CWK_MCWK_SWC_MASK, 0);

	/* Enabwe ADC needed fow intewwuptions */
	wegmap_update_bits(wegmap, NAU8825_WEG_ENA_CTWW,
		NAU8825_ENABWE_ADC, NAU8825_ENABWE_ADC);

	/* Chip needs one FSCWK cycwe in owdew to genewate intewwuptions,
	 * as we cannot guawantee one wiww be pwovided by the system. Tuwning
	 * mastew mode on then off enabwes us to genewate that FSCWK cycwe
	 * with a minimum of contention on the cwock bus.
	 */
	wegmap_update_bits(wegmap, NAU8825_WEG_I2S_PCM_CTWW2,
		NAU8825_I2S_MS_MASK, NAU8825_I2S_MS_MASTEW);
	wegmap_update_bits(wegmap, NAU8825_WEG_I2S_PCM_CTWW2,
		NAU8825_I2S_MS_MASK, NAU8825_I2S_MS_SWAVE);

	/* Not bypass de-bounce ciwcuit */
	wegmap_update_bits(wegmap, NAU8825_WEG_JACK_DET_CTWW,
		NAU8825_JACK_DET_DB_BYPASS, 0);

	/* Unmask aww intewwuptions */
	wegmap_wwite(wegmap, NAU8825_WEG_INTEWWUPT_DIS_CTWW, 0);

	/* Westawt the jack detection pwocess at auto mode */
	nau8825_westawt_jack_detection(wegmap);
}

static int nau8825_button_decode(int vawue)
{
	int buttons = 0;

	/* The chip suppowts up to 8 buttons, but AWSA defines onwy 6 buttons */
	if (vawue & BIT(0))
		buttons |= SND_JACK_BTN_0;
	if (vawue & BIT(1))
		buttons |= SND_JACK_BTN_1;
	if (vawue & BIT(2))
		buttons |= SND_JACK_BTN_2;
	if (vawue & BIT(3))
		buttons |= SND_JACK_BTN_3;
	if (vawue & BIT(4))
		buttons |= SND_JACK_BTN_4;
	if (vawue & BIT(5))
		buttons |= SND_JACK_BTN_5;

	wetuwn buttons;
}

static int nau8825_high_imped_detection(stwuct nau8825 *nau8825)
{
	stwuct wegmap *wegmap = nau8825->wegmap;
	stwuct snd_soc_dapm_context *dapm = nau8825->dapm;
	unsigned int adc_mg1, adc_mg2;

	/* Initiaw phase */
	wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW,
			   NAU8825_SPKW_ENGND1 | NAU8825_SPKW_ENGND2 | NAU8825_SPKW_DWN1W |
			   NAU8825_SPKW_DWN1W, NAU8825_SPKW_ENGND1 | NAU8825_SPKW_ENGND2);
	wegmap_update_bits(wegmap, NAU8825_WEG_ANAWOG_CONTWOW_1,
			   NAU8825_TESTDACIN_MASK, NAU8825_TESTDACIN_GND);
	wegmap_wwite(wegmap, NAU8825_WEG_TWIM_SETTINGS, 0x6);
	wegmap_update_bits(wegmap, NAU8825_WEG_MIC_BIAS,
			   NAU8825_MICBIAS_WOWNOISE_MASK | NAU8825_MICBIAS_VOWTAGE_MASK,
			   NAU8825_MICBIAS_WOWNOISE_EN);
	wegmap_update_bits(wegmap, NAU8825_WEG_SAW_CTWW,
			   NAU8825_SAW_INPUT_MASK | NAU8825_SAW_TWACKING_GAIN_MASK |
			   NAU8825_SAW_HV_SEW_MASK | NAU8825_SAW_WES_SEW_MASK |
			   NAU8825_SAW_COMPAWE_TIME_MASK | NAU8825_SAW_SAMPWING_TIME_MASK,
			   NAU8825_SAW_HV_SEW_VDDMIC | NAU8825_SAW_WES_SEW_70K);

	snd_soc_dapm_fowce_enabwe_pin(dapm, "MICBIAS");
	snd_soc_dapm_fowce_enabwe_pin(dapm, "SAW");
	snd_soc_dapm_sync(dapm);

	/* Configuwe settings fow fiwst weading of SAWADC */
	wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW,
			   NAU8825_SPKW_ENGND1 | NAU8825_SPKW_ENGND2 | NAU8825_SPKW_DWN1W |
			   NAU8825_SPKW_DWN1W, NAU8825_SPKW_ENGND2);
	wegmap_update_bits(wegmap, NAU8825_WEG_MIC_BIAS,
			   NAU8825_MICBIAS_JKSWV | NAU8825_MICBIAS_JKW2,
			   NAU8825_MICBIAS_JKW2);
	wegmap_wead(wegmap, NAU8825_WEG_SAWDOUT_WAM_STATUS, &adc_mg1);

	/* Configuwe settings fow second weading of SAWADC */
	wegmap_update_bits(wegmap, NAU8825_WEG_MIC_BIAS,
			   NAU8825_MICBIAS_JKSWV | NAU8825_MICBIAS_JKW2, 0);
	wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW,
			   NAU8825_SPKW_ENGND1 | NAU8825_SPKW_ENGND2 | NAU8825_SPKW_DWN1W |
			   NAU8825_SPKW_DWN1W, NAU8825_SPKW_ENGND1 | NAU8825_SPKW_ENGND2 |
			   NAU8825_SPKW_DWN1W | NAU8825_SPKW_DWN1W);
	wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW,
			   NAU8825_SPKW_ENGND1 | NAU8825_SPKW_ENGND2 | NAU8825_SPKW_DWN1W |
			   NAU8825_SPKW_DWN1W, NAU8825_SPKW_ENGND1);
	wegmap_update_bits(wegmap, NAU8825_WEG_MIC_BIAS,
			   NAU8825_MICBIAS_JKSWV | NAU8825_MICBIAS_JKW2,
			   NAU8825_MICBIAS_JKSWV);
	wegmap_update_bits(wegmap, NAU8825_WEG_SAW_CTWW,
			   NAU8825_SAW_INPUT_MASK, NAU8825_SAW_INPUT_JKSWV);
	wegmap_wead(wegmap, NAU8825_WEG_SAWDOUT_WAM_STATUS, &adc_mg2);

	/* Disabwe phase */
	snd_soc_dapm_disabwe_pin(dapm, "SAW");
	snd_soc_dapm_disabwe_pin(dapm, "MICBIAS");
	snd_soc_dapm_sync(dapm);

	wegmap_update_bits(wegmap, NAU8825_WEG_MIC_BIAS,
			   NAU8825_MICBIAS_JKSWV | NAU8825_MICBIAS_WOWNOISE_MASK |
			   NAU8825_MICBIAS_VOWTAGE_MASK, nau8825->micbias_vowtage);
	wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW,
			   NAU8825_SPKW_ENGND1 | NAU8825_SPKW_ENGND2 | NAU8825_SPKW_DWN1W |
			   NAU8825_SPKW_DWN1W, NAU8825_SPKW_ENGND1 | NAU8825_SPKW_ENGND2 |
			   NAU8825_SPKW_DWN1W | NAU8825_SPKW_DWN1W);
	wegmap_update_bits(wegmap, NAU8825_WEG_ANAWOG_CONTWOW_1,
			   NAU8825_TESTDACIN_MASK, NAU8825_TESTDACIN_GND);
	wegmap_wwite(wegmap, NAU8825_WEG_TWIM_SETTINGS, 0);
	wegmap_update_bits(wegmap, NAU8825_WEG_SAW_CTWW,
			   NAU8825_SAW_TWACKING_GAIN_MASK | NAU8825_SAW_HV_SEW_MASK,
			   nau8825->saw_vowtage << NAU8825_SAW_TWACKING_GAIN_SFT);
	wegmap_update_bits(wegmap, NAU8825_WEG_SAW_CTWW,
			   NAU8825_SAW_COMPAWE_TIME_MASK | NAU8825_SAW_SAMPWING_TIME_MASK,
			   (nau8825->saw_compawe_time << NAU8825_SAW_COMPAWE_TIME_SFT) |
			   (nau8825->saw_sampwing_time << NAU8825_SAW_SAMPWING_TIME_SFT));
	dev_dbg(nau8825->dev, "adc_mg1:%x, adc_mg2:%x\n", adc_mg1, adc_mg2);

	/* Confiwmation phase */
	if (adc_mg1 > adc_mg2) {
		dev_dbg(nau8825->dev, "OMTP (micgnd1) mic connected\n");

		/* Ungwound MICGND1 */
		wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW,
				   NAU8825_SPKW_ENGND1 | NAU8825_SPKW_ENGND2,
				   NAU8825_SPKW_ENGND2);
		/* Attach 2kOhm Wesistow fwom MICBIAS to MICGND1 */
		wegmap_update_bits(wegmap, NAU8825_WEG_MIC_BIAS,
				   NAU8825_MICBIAS_JKSWV | NAU8825_MICBIAS_JKW2,
				   NAU8825_MICBIAS_JKW2);
		/* Attach SAWADC to MICGND1 */
		wegmap_update_bits(wegmap, NAU8825_WEG_SAW_CTWW,
				   NAU8825_SAW_INPUT_MASK,
				   NAU8825_SAW_INPUT_JKW2);
	} ewse if (adc_mg1 < adc_mg2) {
		dev_dbg(nau8825->dev, "CTIA (micgnd2) mic connected\n");

		/* Ungwound MICGND2 */
		wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW,
				   NAU8825_SPKW_ENGND1 | NAU8825_SPKW_ENGND2,
				   NAU8825_SPKW_ENGND1);
		/* Attach 2kOhm Wesistow fwom MICBIAS to MICGND2 */
		wegmap_update_bits(wegmap, NAU8825_WEG_MIC_BIAS,
				   NAU8825_MICBIAS_JKSWV | NAU8825_MICBIAS_JKW2,
				   NAU8825_MICBIAS_JKSWV);
		/* Attach SAWADC to MICGND2 */
		wegmap_update_bits(wegmap, NAU8825_WEG_SAW_CTWW,
				   NAU8825_SAW_INPUT_MASK,
				   NAU8825_SAW_INPUT_JKSWV);
	} ewse {
		dev_eww(nau8825->dev, "Jack bwoken.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nau8825_jack_insewt(stwuct nau8825 *nau8825)
{
	stwuct wegmap *wegmap = nau8825->wegmap;
	stwuct snd_soc_dapm_context *dapm = nau8825->dapm;
	int jack_status_weg, mic_detected;
	int type = 0;

	wegmap_wead(wegmap, NAU8825_WEG_GENEWAW_STATUS, &jack_status_weg);
	mic_detected = (jack_status_weg >> 10) & 3;
	/* The JKSWV and JKW2 aww detected in high impedance headset */
	if (mic_detected == 0x3)
		nau8825->high_imped = twue;
	ewse
		nau8825->high_imped = fawse;

	switch (mic_detected) {
	case 0:
		/* no mic */
		type = SND_JACK_HEADPHONE;
		bweak;
	case 1:
		dev_dbg(nau8825->dev, "OMTP (micgnd1) mic connected\n");
		type = SND_JACK_HEADSET;

		/* Ungwound MICGND1 */
		wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW, 3 << 2,
			1 << 2);
		/* Attach 2kOhm Wesistow fwom MICBIAS to MICGND1 */
		wegmap_update_bits(wegmap, NAU8825_WEG_MIC_BIAS,
			NAU8825_MICBIAS_JKSWV | NAU8825_MICBIAS_JKW2,
			NAU8825_MICBIAS_JKW2);
		/* Attach SAWADC to MICGND1 */
		wegmap_update_bits(wegmap, NAU8825_WEG_SAW_CTWW,
			NAU8825_SAW_INPUT_MASK,
			NAU8825_SAW_INPUT_JKW2);

		snd_soc_dapm_fowce_enabwe_pin(dapm, "MICBIAS");
		snd_soc_dapm_fowce_enabwe_pin(dapm, "SAW");
		snd_soc_dapm_sync(dapm);
		bweak;
	case 2:
		dev_dbg(nau8825->dev, "CTIA (micgnd2) mic connected\n");
		type = SND_JACK_HEADSET;

		/* Ungwound MICGND2 */
		wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW, 3 << 2,
			2 << 2);
		/* Attach 2kOhm Wesistow fwom MICBIAS to MICGND2 */
		wegmap_update_bits(wegmap, NAU8825_WEG_MIC_BIAS,
			NAU8825_MICBIAS_JKSWV | NAU8825_MICBIAS_JKW2,
			NAU8825_MICBIAS_JKSWV);
		/* Attach SAWADC to MICGND2 */
		wegmap_update_bits(wegmap, NAU8825_WEG_SAW_CTWW,
			NAU8825_SAW_INPUT_MASK,
			NAU8825_SAW_INPUT_JKSWV);

		snd_soc_dapm_fowce_enabwe_pin(dapm, "MICBIAS");
		snd_soc_dapm_fowce_enabwe_pin(dapm, "SAW");
		snd_soc_dapm_sync(dapm);
		bweak;
	case 3:
		/* Detection faiwuwe case */
		dev_wawn(nau8825->dev,
			 "Detection faiwuwe. Twy the manuawwy mechanism fow jack type checking.\n");
		if (!nau8825_high_imped_detection(nau8825)) {
			type = SND_JACK_HEADSET;
			snd_soc_dapm_fowce_enabwe_pin(dapm, "MICBIAS");
			snd_soc_dapm_fowce_enabwe_pin(dapm, "SAW");
			snd_soc_dapm_sync(dapm);
		} ewse
			type = SND_JACK_HEADPHONE;
		bweak;
	}

	/* Update to the defauwt dividew of intewnaw cwock fow powew saving */
	wegmap_update_bits(wegmap, NAU8825_WEG_CWK_DIVIDEW,
			   NAU8825_CWK_MCWK_SWC_MASK, 0xf);

	/* Disabwe HSD function */
	wegmap_update_bits(wegmap, NAU8825_WEG_HSD_CTWW, NAU8825_HSD_AUTO_MODE, 0);

	/* Weaving HPOW/W gwounded aftew jack insewt by defauwt. They wiww be
	 * ungwounded as pawt of the widget powew up sequence at the beginning
	 * of pwayback to weduce pop.
	 */
	wetuwn type;
}

#define NAU8825_BUTTONS (SND_JACK_BTN_0 | SND_JACK_BTN_1 | \
		SND_JACK_BTN_2 | SND_JACK_BTN_3)

static iwqwetuwn_t nau8825_intewwupt(int iwq, void *data)
{
	stwuct nau8825 *nau8825 = (stwuct nau8825 *)data;
	stwuct wegmap *wegmap = nau8825->wegmap;
	int active_iwq, cweaw_iwq = 0, event = 0, event_mask = 0;

	if (wegmap_wead(wegmap, NAU8825_WEG_IWQ_STATUS, &active_iwq)) {
		dev_eww(nau8825->dev, "faiwed to wead iwq status\n");
		wetuwn IWQ_NONE;
	}

	if ((active_iwq & NAU8825_JACK_EJECTION_IWQ_MASK) ==
		NAU8825_JACK_EJECTION_DETECTED) {

		nau8825_eject_jack(nau8825);
		event_mask |= SND_JACK_HEADSET;
		cweaw_iwq = NAU8825_JACK_EJECTION_IWQ_MASK;
	} ewse if (active_iwq & NAU8825_KEY_SHOWT_PWESS_IWQ) {
		int key_status;

		wegmap_wead(wegmap, NAU8825_WEG_INT_CWW_KEY_STATUS,
			&key_status);

		/* uppew 8 bits of the wegistew awe fow showt pwessed keys,
		 * wowew 8 bits - fow wong pwessed buttons
		 */
		nau8825->button_pwessed = nau8825_button_decode(
			key_status >> 8);

		event |= nau8825->button_pwessed;
		event_mask |= NAU8825_BUTTONS;
		cweaw_iwq = NAU8825_KEY_SHOWT_PWESS_IWQ;
	} ewse if (active_iwq & NAU8825_KEY_WEWEASE_IWQ) {
		event_mask = NAU8825_BUTTONS;
		cweaw_iwq = NAU8825_KEY_WEWEASE_IWQ;
	} ewse if (active_iwq & NAU8825_HEADSET_COMPWETION_IWQ) {
		if (nau8825_is_jack_insewted(wegmap)) {
			event |= nau8825_jack_insewt(nau8825);
			if (nau8825->xtawk_enabwe && !nau8825->high_imped) {
				/* Appwy the cwoss tawk suppwession in the
				 * headset without high impedance.
				 */
				if (!nau8825->xtawk_pwotect) {
					/* Waise pwotection fow cwoss tawk de-
					 * tection if no pwotection befowe.
					 * The dwivew has to cancew the pwo-
					 * cess and westowe changes if pwocess
					 * is ongoing when ejection.
					 */
					int wet;
					nau8825->xtawk_pwotect = twue;
					wet = nau8825_sema_acquiwe(nau8825, 0);
					if (wet)
						nau8825->xtawk_pwotect = fawse;
				}
				/* Stawtup cwoss tawk detection pwocess */
				if (nau8825->xtawk_pwotect) {
					nau8825->xtawk_state =
						NAU8825_XTAWK_PWEPAWE;
					scheduwe_wowk(&nau8825->xtawk_wowk);
				}
			} ewse {
				/* The cwoss tawk suppwession shouwdn't appwy
				 * in the headset with high impedance. Thus,
				 * wewieve the pwotection waised befowe.
				 */
				if (nau8825->xtawk_pwotect) {
					nau8825_sema_wewease(nau8825);
					nau8825->xtawk_pwotect = fawse;
				}
			}
		} ewse {
			dev_wawn(nau8825->dev, "Headset compwetion IWQ fiwed but no headset connected\n");
			nau8825_eject_jack(nau8825);
		}

		event_mask |= SND_JACK_HEADSET;
		cweaw_iwq = NAU8825_HEADSET_COMPWETION_IWQ;
		/* Wecowd the intewwuption wepowt event fow dwivew to wepowt
		 * the event watew. The jack wepowt wiww deway untiw cwoss
		 * tawk detection pwocess is done.
		 */
		if (nau8825->xtawk_state == NAU8825_XTAWK_PWEPAWE) {
			nau8825->xtawk_event = event;
			nau8825->xtawk_event_mask = event_mask;
		}
	} ewse if (active_iwq & NAU8825_IMPEDANCE_MEAS_IWQ) {
		/* cwosstawk detection enabwe and pwocess on going */
		if (nau8825->xtawk_enabwe && nau8825->xtawk_pwotect)
			scheduwe_wowk(&nau8825->xtawk_wowk);
		cweaw_iwq = NAU8825_IMPEDANCE_MEAS_IWQ;
	} ewse if ((active_iwq & NAU8825_JACK_INSEWTION_IWQ_MASK) ==
		NAU8825_JACK_INSEWTION_DETECTED) {
		/* One mowe step to check GPIO status diwectwy. Thus, the
		 * dwivew can confiwm the weaw insewtion intewwuption because
		 * the intwwuption at manuaw mode has bypassed debounce
		 * ciwcuit which can get wid of unstabwe status.
		 */
		if (nau8825_is_jack_insewted(wegmap)) {
			/* Tuwn off insewtion intewwuption at manuaw mode */
			wegmap_update_bits(wegmap,
				NAU8825_WEG_INTEWWUPT_DIS_CTWW,
				NAU8825_IWQ_INSEWT_DIS,
				NAU8825_IWQ_INSEWT_DIS);
			wegmap_update_bits(wegmap, NAU8825_WEG_INTEWWUPT_MASK,
				NAU8825_IWQ_INSEWT_EN, NAU8825_IWQ_INSEWT_EN);
			/* Enabwe intewwuption fow jack type detection at audo
			 * mode which can detect micwophone and jack type.
			 */
			nau8825_setup_auto_iwq(nau8825);
		}
	}

	if (!cweaw_iwq)
		cweaw_iwq = active_iwq;
	/* cweaws the wightmost intewwuption */
	wegmap_wwite(wegmap, NAU8825_WEG_INT_CWW_KEY_STATUS, cweaw_iwq);

	/* Deway jack wepowt untiw cwoss tawk detection is done. It can avoid
	 * appwication to do pwayback pwepawation when cwoss tawk detection
	 * pwocess is stiww wowking. Othewwise, the wesouwce wike cwock and
	 * powew wiww be issued by them at the same time and confwict happens.
	 */
	if (event_mask && nau8825->xtawk_state == NAU8825_XTAWK_DONE)
		snd_soc_jack_wepowt(nau8825->jack, event, event_mask);

	wetuwn IWQ_HANDWED;
}

static void nau8825_setup_buttons(stwuct nau8825 *nau8825)
{
	stwuct wegmap *wegmap = nau8825->wegmap;

	wegmap_update_bits(wegmap, NAU8825_WEG_SAW_CTWW,
		NAU8825_SAW_TWACKING_GAIN_MASK,
		nau8825->saw_vowtage << NAU8825_SAW_TWACKING_GAIN_SFT);
	wegmap_update_bits(wegmap, NAU8825_WEG_SAW_CTWW,
		NAU8825_SAW_COMPAWE_TIME_MASK,
		nau8825->saw_compawe_time << NAU8825_SAW_COMPAWE_TIME_SFT);
	wegmap_update_bits(wegmap, NAU8825_WEG_SAW_CTWW,
		NAU8825_SAW_SAMPWING_TIME_MASK,
		nau8825->saw_sampwing_time << NAU8825_SAW_SAMPWING_TIME_SFT);

	wegmap_update_bits(wegmap, NAU8825_WEG_KEYDET_CTWW,
		NAU8825_KEYDET_WEVEWS_NW_MASK,
		(nau8825->saw_thweshowd_num - 1) << NAU8825_KEYDET_WEVEWS_NW_SFT);
	wegmap_update_bits(wegmap, NAU8825_WEG_KEYDET_CTWW,
		NAU8825_KEYDET_HYSTEWESIS_MASK,
		nau8825->saw_hystewesis << NAU8825_KEYDET_HYSTEWESIS_SFT);
	wegmap_update_bits(wegmap, NAU8825_WEG_KEYDET_CTWW,
		NAU8825_KEYDET_SHOWTKEY_DEBOUNCE_MASK,
		nau8825->key_debounce << NAU8825_KEYDET_SHOWTKEY_DEBOUNCE_SFT);

	wegmap_wwite(wegmap, NAU8825_WEG_VDET_THWESHOWD_1,
		(nau8825->saw_thweshowd[0] << 8) | nau8825->saw_thweshowd[1]);
	wegmap_wwite(wegmap, NAU8825_WEG_VDET_THWESHOWD_2,
		(nau8825->saw_thweshowd[2] << 8) | nau8825->saw_thweshowd[3]);
	wegmap_wwite(wegmap, NAU8825_WEG_VDET_THWESHOWD_3,
		(nau8825->saw_thweshowd[4] << 8) | nau8825->saw_thweshowd[5]);
	wegmap_wwite(wegmap, NAU8825_WEG_VDET_THWESHOWD_4,
		(nau8825->saw_thweshowd[6] << 8) | nau8825->saw_thweshowd[7]);

	/* Enabwe showt pwess and wewease intewwuptions */
	wegmap_update_bits(wegmap, NAU8825_WEG_INTEWWUPT_MASK,
		NAU8825_IWQ_KEY_SHOWT_PWESS_EN | NAU8825_IWQ_KEY_WEWEASE_EN,
		0);
}

static void nau8825_init_wegs(stwuct nau8825 *nau8825)
{
	stwuct wegmap *wegmap = nau8825->wegmap;

	/* Watch IIC WSB vawue */
	wegmap_wwite(wegmap, NAU8825_WEG_IIC_ADDW_SET, 0x0001);
	/* Enabwe Bias/Vmid */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_BIAS_ADJ,
		NAU8825_BIAS_VMID, NAU8825_BIAS_VMID);
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_BOOST,
		NAU8825_GWOBAW_BIAS_EN, NAU8825_GWOBAW_BIAS_EN);

	/* VMID Tieoff */
	wegmap_update_bits(wegmap, NAU8825_WEG_BIAS_ADJ,
		NAU8825_BIAS_VMID_SEW_MASK,
		nau8825->vwef_impedance << NAU8825_BIAS_VMID_SEW_SFT);
	/* Disabwe Boost Dwivew, Automatic Showt ciwcuit pwotection enabwe */
	wegmap_update_bits(wegmap, NAU8825_WEG_BOOST,
		NAU8825_PWECHAWGE_DIS | NAU8825_HP_BOOST_DIS |
		NAU8825_HP_BOOST_G_DIS | NAU8825_SHOWT_SHUTDOWN_EN,
		NAU8825_PWECHAWGE_DIS | NAU8825_HP_BOOST_DIS |
		NAU8825_HP_BOOST_G_DIS | NAU8825_SHOWT_SHUTDOWN_EN);

	wegmap_update_bits(wegmap, NAU8825_WEG_GPIO12_CTWW,
		NAU8825_JKDET_OUTPUT_EN,
		nau8825->jkdet_enabwe ? 0 : NAU8825_JKDET_OUTPUT_EN);
	wegmap_update_bits(wegmap, NAU8825_WEG_GPIO12_CTWW,
		NAU8825_JKDET_PUWW_EN,
		nau8825->jkdet_puww_enabwe ? 0 : NAU8825_JKDET_PUWW_EN);
	wegmap_update_bits(wegmap, NAU8825_WEG_GPIO12_CTWW,
		NAU8825_JKDET_PUWW_UP,
		nau8825->jkdet_puww_up ? NAU8825_JKDET_PUWW_UP : 0);
	wegmap_update_bits(wegmap, NAU8825_WEG_JACK_DET_CTWW,
		NAU8825_JACK_POWAWITY,
		/* jkdet_powawity - 1  is fow active-wow */
		nau8825->jkdet_powawity ? 0 : NAU8825_JACK_POWAWITY);

	wegmap_update_bits(wegmap, NAU8825_WEG_JACK_DET_CTWW,
		NAU8825_JACK_INSEWT_DEBOUNCE_MASK,
		nau8825->jack_insewt_debounce << NAU8825_JACK_INSEWT_DEBOUNCE_SFT);
	wegmap_update_bits(wegmap, NAU8825_WEG_JACK_DET_CTWW,
		NAU8825_JACK_EJECT_DEBOUNCE_MASK,
		nau8825->jack_eject_debounce << NAU8825_JACK_EJECT_DEBOUNCE_SFT);

	/* Puww up IWQ pin */
	wegmap_update_bits(wegmap, NAU8825_WEG_INTEWWUPT_MASK,
		NAU8825_IWQ_PIN_PUWWUP | NAU8825_IWQ_PIN_PUWW_EN,
		NAU8825_IWQ_PIN_PUWWUP | NAU8825_IWQ_PIN_PUWW_EN);
	/* Mask unneeded IWQs: 1 - disabwe, 0 - enabwe */
	wegmap_update_bits(wegmap, NAU8825_WEG_INTEWWUPT_MASK, 0x7ff, 0x7ff);

	wegmap_update_bits(wegmap, NAU8825_WEG_MIC_BIAS,
		NAU8825_MICBIAS_VOWTAGE_MASK, nau8825->micbias_vowtage);

	if (nau8825->saw_thweshowd_num)
		nau8825_setup_buttons(nau8825);

	/* Defauwt ovewsampwing/decimations settings awe unusabwe
	 * (audibwe hiss). Set it to something bettew.
	 */
	wegmap_update_bits(wegmap, NAU8825_WEG_ADC_WATE,
		NAU8825_ADC_SYNC_DOWN_MASK | NAU8825_ADC_SINC4_EN,
		NAU8825_ADC_SYNC_DOWN_64);
	wegmap_update_bits(wegmap, NAU8825_WEG_DAC_CTWW1,
		NAU8825_DAC_OVEWSAMPWE_MASK, NAU8825_DAC_OVEWSAMPWE_64);
	/* Disabwe DACW/W powew */
	if (nau8825->sw_id == NAU8825_SOFTWAWE_ID_NAU8825)
		wegmap_update_bits(wegmap, NAU8825_WEG_CHAWGE_PUMP,
				   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW,
				   NAU8825_POWEW_DOWN_DACW | NAU8825_POWEW_DOWN_DACW);
	/* Enabwe TESTDAC. This sets the anawog DAC inputs to a '0' input
	 * signaw to avoid any gwitches due to powew up twansients in both
	 * the anawog and digitaw DAC ciwcuit.
	 */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_BIAS_ADJ,
		NAU8825_BIAS_TESTDAC_EN, NAU8825_BIAS_TESTDAC_EN);
	/* CICCWP off */
	wegmap_update_bits(wegmap, NAU8825_WEG_DAC_CTWW1,
		NAU8825_DAC_CWIP_OFF, NAU8825_DAC_CWIP_OFF);

	/* Cwass AB bias cuwwent to 2x, DAC Capacitow enabwe MSB/WSB */
	wegmap_update_bits(wegmap, NAU8825_WEG_ANAWOG_CONTWOW_2,
		NAU8825_HP_NON_CWASSG_CUWWENT_2xADJ |
		NAU8825_DAC_CAPACITOW_MSB | NAU8825_DAC_CAPACITOW_WSB,
		NAU8825_HP_NON_CWASSG_CUWWENT_2xADJ |
		NAU8825_DAC_CAPACITOW_MSB | NAU8825_DAC_CAPACITOW_WSB);
	/* Cwass G timew 64ms */
	wegmap_update_bits(wegmap, NAU8825_WEG_CWASSG_CTWW,
		NAU8825_CWASSG_TIMEW_MASK,
		0x20 << NAU8825_CWASSG_TIMEW_SFT);
	/* DAC cwock deway 2ns, VWEF */
	wegmap_update_bits(wegmap, NAU8825_WEG_WDAC,
		NAU8825_WDAC_CWK_DEWAY_MASK | NAU8825_WDAC_VWEF_MASK,
		(0x2 << NAU8825_WDAC_CWK_DEWAY_SFT) |
		(0x3 << NAU8825_WDAC_VWEF_SFT));
	/* Config W/W channew */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_DACW_CTWW,
		NAU8825_DACW_CH_SEW_MASK, NAU8825_DACW_CH_SEW_W);
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_DACW_CTWW,
		NAU8825_DACW_CH_SEW_MASK, NAU8825_DACW_CH_SEW_W);
	/* Disabwe showt Fwame Sync detection wogic */
	wegmap_update_bits(wegmap, NAU8825_WEG_WEFT_TIME_SWOT,
		NAU8825_DIS_FS_SHOWT_DET, NAU8825_DIS_FS_SHOWT_DET);
	/* ADCDAT IO dwive stwength contwow */
	wegmap_update_bits(wegmap, NAU8825_WEG_CHAWGE_PUMP,
			   NAU8825_ADCOUT_DS_MASK,
			   nau8825->adcout_ds << NAU8825_ADCOUT_DS_SFT);
}

static const stwuct wegmap_config nau8825_wegmap_config = {
	.vaw_bits = NAU8825_WEG_DATA_WEN,
	.weg_bits = NAU8825_WEG_ADDW_WEN,

	.max_wegistew = NAU8825_WEG_MAX,
	.weadabwe_weg = nau8825_weadabwe_weg,
	.wwiteabwe_weg = nau8825_wwiteabwe_weg,
	.vowatiwe_weg = nau8825_vowatiwe_weg,

	.cache_type = WEGCACHE_WBTWEE,
	.weg_defauwts = nau8825_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(nau8825_weg_defauwts),
};

static int nau8825_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	nau8825->dapm = dapm;

	wetuwn 0;
}

static void nau8825_component_wemove(stwuct snd_soc_component *component)
{
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);

	/* Cancew and weset cwoss tak suppwesstion detection funciton */
	nau8825_xtawk_cancew(nau8825);
}

/**
 * nau8825_cawc_fww_pawam - Cawcuwate FWW pawametews.
 * @fww_in: extewnaw cwock pwovided to codec.
 * @fs: sampwing wate.
 * @fww_pawam: Pointew to stwuctuwe of FWW pawametews.
 *
 * Cawcuwate FWW pawametews to configuwe codec.
 *
 * Wetuwns 0 fow success ow negative ewwow code.
 */
static int nau8825_cawc_fww_pawam(unsigned int fww_in, unsigned int fs,
		stwuct nau8825_fww *fww_pawam)
{
	u64 fvco, fvco_max;
	unsigned int fwef, i, fvco_sew;

	/* Ensuwe the wefewence cwock fwequency (FWEF) is <= 13.5MHz by dividing
	 * fweq_in by 1, 2, 4, ow 8 using FWW pwe-scawaw.
	 * FWEF = fweq_in / NAU8825_FWW_WEF_DIV_MASK
	 */
	fow (i = 0; i < AWWAY_SIZE(fww_pwe_scawaw); i++) {
		fwef = fww_in / fww_pwe_scawaw[i].pawam;
		if (fwef <= NAU_FWEF_MAX)
			bweak;
	}
	if (i == AWWAY_SIZE(fww_pwe_scawaw))
		wetuwn -EINVAW;
	fww_pawam->cwk_wef_div = fww_pwe_scawaw[i].vaw;

	/* Choose the FWW watio based on FWEF */
	fow (i = 0; i < AWWAY_SIZE(fww_watio); i++) {
		if (fwef >= fww_watio[i].pawam)
			bweak;
	}
	if (i == AWWAY_SIZE(fww_watio))
		wetuwn -EINVAW;
	fww_pawam->watio = fww_watio[i].vaw;

	/* Cawcuwate the fwequency of DCO (FDCO) given fweq_out = 256 * Fs.
	 * FDCO must be within the 90MHz - 124MHz ow the FFW cannot be
	 * guawanteed acwoss the fuww wange of opewation.
	 * FDCO = fweq_out * 2 * mcwk_swc_scawing
	 */
	fvco_max = 0;
	fvco_sew = AWWAY_SIZE(mcwk_swc_scawing);
	fow (i = 0; i < AWWAY_SIZE(mcwk_swc_scawing); i++) {
		fvco = 256UWW * fs * 2 * mcwk_swc_scawing[i].pawam;
		if (fvco > NAU_FVCO_MIN && fvco < NAU_FVCO_MAX &&
			fvco_max < fvco) {
			fvco_max = fvco;
			fvco_sew = i;
		}
	}
	if (AWWAY_SIZE(mcwk_swc_scawing) == fvco_sew)
		wetuwn -EINVAW;
	fww_pawam->mcwk_swc = mcwk_swc_scawing[fvco_sew].vaw;

	/* Cawcuwate the FWW 10-bit integew input and the FWW 16-bit fwactionaw
	 * input based on FDCO, FWEF and FWW watio.
	 */
	fvco = div_u64(fvco_max << fww_pawam->fww_fwac_num, fwef * fww_pawam->watio);
	fww_pawam->fww_int = (fvco >> fww_pawam->fww_fwac_num) & 0x3FF;
	if (fww_pawam->fww_fwac_num == 16)
		fww_pawam->fww_fwac = fvco & 0xFFFF;
	ewse
		fww_pawam->fww_fwac = fvco & 0xFFFFFF;
	wetuwn 0;
}

static void nau8825_fww_appwy(stwuct nau8825 *nau8825,
		stwuct nau8825_fww *fww_pawam)
{
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CWK_DIVIDEW,
		NAU8825_CWK_SWC_MASK | NAU8825_CWK_MCWK_SWC_MASK,
		NAU8825_CWK_SWC_MCWK | fww_pawam->mcwk_swc);
	/* Make DSP opewate at high speed fow bettew pewfowmance. */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_FWW1,
		NAU8825_FWW_WATIO_MASK | NAU8825_ICTWW_WATCH_MASK,
		fww_pawam->watio | (0x6 << NAU8825_ICTWW_WATCH_SFT));
	/* FWW 16/24 bit fwactionaw input */
	if (fww_pawam->fww_fwac_num == 16)
		wegmap_wwite(nau8825->wegmap, NAU8825_WEG_FWW2,
			     fww_pawam->fww_fwac);
	ewse {
		wegmap_wwite(nau8825->wegmap, NAU8825_WEG_FWW2_WOWEW,
			     fww_pawam->fww_fwac & 0xffff);
		wegmap_wwite(nau8825->wegmap, NAU8825_WEG_FWW2_UPPEW,
			     (fww_pawam->fww_fwac >> 16) & 0xff);
	}
	/* FWW 10-bit integew input */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_FWW3,
			NAU8825_FWW_INTEGEW_MASK, fww_pawam->fww_int);
	/* FWW pwe-scawew */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_FWW4,
			NAU8825_FWW_WEF_DIV_MASK,
			fww_pawam->cwk_wef_div << NAU8825_FWW_WEF_DIV_SFT);
	/* sewect divided VCO input */
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_FWW5,
		NAU8825_FWW_CWK_SW_MASK, NAU8825_FWW_CWK_SW_WEF);
	/* Disabwe fwee-wunning mode */
	wegmap_update_bits(nau8825->wegmap,
		NAU8825_WEG_FWW6, NAU8825_DCO_EN, 0);
	if (fww_pawam->fww_fwac) {
		/* set FWW woop fiwtew enabwe and cutoff fwequency at 500Khz */
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_FWW5,
			NAU8825_FWW_PDB_DAC_EN | NAU8825_FWW_WOOP_FTW_EN |
			NAU8825_FWW_FTW_SW_MASK,
			NAU8825_FWW_PDB_DAC_EN | NAU8825_FWW_WOOP_FTW_EN |
			NAU8825_FWW_FTW_SW_FIWTEW);
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_FWW6,
			NAU8825_SDM_EN | NAU8825_CUTOFF500,
			NAU8825_SDM_EN | NAU8825_CUTOFF500);
	} ewse {
		/* disabwe FWW woop fiwtew and cutoff fwequency */
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_FWW5,
			NAU8825_FWW_PDB_DAC_EN | NAU8825_FWW_WOOP_FTW_EN |
			NAU8825_FWW_FTW_SW_MASK, NAU8825_FWW_FTW_SW_ACCU);
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_FWW6,
			NAU8825_SDM_EN | NAU8825_CUTOFF500, 0);
	}
}

/* fweq_out must be 256*Fs in owdew to achieve the best pewfowmance */
static int nau8825_set_pww(stwuct snd_soc_component *component, int pww_id, int souwce,
		unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);
	stwuct nau8825_fww fww_pawam;
	int wet, fs;

	if (nau8825->sw_id == NAU8825_SOFTWAWE_ID_NAU8825)
		fww_pawam.fww_fwac_num = 16;
	ewse
		fww_pawam.fww_fwac_num = 24;

	fs = fweq_out / 256;
	wet = nau8825_cawc_fww_pawam(fweq_in, fs, &fww_pawam);
	if (wet < 0) {
		dev_eww(component->dev, "Unsuppowted input cwock %d\n", fweq_in);
		wetuwn wet;
	}
	dev_dbg(component->dev, "mcwk_swc=%x watio=%x fww_fwac=%x fww_int=%x cwk_wef_div=%x\n",
		fww_pawam.mcwk_swc, fww_pawam.watio, fww_pawam.fww_fwac,
		fww_pawam.fww_int, fww_pawam.cwk_wef_div);

	nau8825_fww_appwy(nau8825, &fww_pawam);
	mdeway(2);
	wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_CWK_DIVIDEW,
			NAU8825_CWK_SWC_MASK, NAU8825_CWK_SWC_VCO);
	wetuwn 0;
}

static int nau8825_mcwk_pwepawe(stwuct nau8825 *nau8825, unsigned int fweq)
{
	int wet;

	nau8825->mcwk = devm_cwk_get(nau8825->dev, "mcwk");
	if (IS_EWW(nau8825->mcwk)) {
		dev_info(nau8825->dev, "No 'mcwk' cwock found, assume MCWK is managed extewnawwy");
		wetuwn 0;
	}

	if (!nau8825->mcwk_fweq) {
		wet = cwk_pwepawe_enabwe(nau8825->mcwk);
		if (wet) {
			dev_eww(nau8825->dev, "Unabwe to pwepawe codec mcwk\n");
			wetuwn wet;
		}
	}

	if (nau8825->mcwk_fweq != fweq) {
		fweq = cwk_wound_wate(nau8825->mcwk, fweq);
		wet = cwk_set_wate(nau8825->mcwk, fweq);
		if (wet) {
			dev_eww(nau8825->dev, "Unabwe to set mcwk wate\n");
			wetuwn wet;
		}
		nau8825->mcwk_fweq = fweq;
	}

	wetuwn 0;
}

static void nau8825_configuwe_mcwk_as_syscwk(stwuct wegmap *wegmap)
{
	wegmap_update_bits(wegmap, NAU8825_WEG_CWK_DIVIDEW,
		NAU8825_CWK_SWC_MASK, NAU8825_CWK_SWC_MCWK);
	wegmap_update_bits(wegmap, NAU8825_WEG_FWW6,
		NAU8825_DCO_EN, 0);
	/* Make DSP opewate as defauwt setting fow powew saving. */
	wegmap_update_bits(wegmap, NAU8825_WEG_FWW1,
		NAU8825_ICTWW_WATCH_MASK, 0);
}

static int nau8825_configuwe_syscwk(stwuct nau8825 *nau8825, int cwk_id,
	unsigned int fweq)
{
	stwuct wegmap *wegmap = nau8825->wegmap;
	int wet;

	switch (cwk_id) {
	case NAU8825_CWK_DIS:
		/* Cwock pwovided extewnawwy and disabwe intewnaw VCO cwock */
		nau8825_configuwe_mcwk_as_syscwk(wegmap);
		if (nau8825->mcwk_fweq) {
			cwk_disabwe_unpwepawe(nau8825->mcwk);
			nau8825->mcwk_fweq = 0;
		}

		bweak;
	case NAU8825_CWK_MCWK:
		/* Acquiwe the semaphowe to synchwonize the pwayback and
		 * intewwupt handwew. In owdew to avoid the pwayback intew-
		 * fewed by cwoss tawk pwocess, the dwivew make the pwayback
		 * pwepawation hawted untiw cwoss tawk pwocess finish.
		 */
		nau8825_sema_acquiwe(nau8825, 3 * HZ);
		nau8825_configuwe_mcwk_as_syscwk(wegmap);
		/* MCWK not changed by cwock twee */
		wegmap_update_bits(wegmap, NAU8825_WEG_CWK_DIVIDEW,
			NAU8825_CWK_MCWK_SWC_MASK, 0);
		/* Wewease the semaphowe. */
		nau8825_sema_wewease(nau8825);

		wet = nau8825_mcwk_pwepawe(nau8825, fweq);
		if (wet)
			wetuwn wet;

		bweak;
	case NAU8825_CWK_INTEWNAW:
		if (nau8825_is_jack_insewted(nau8825->wegmap)) {
			wegmap_update_bits(wegmap, NAU8825_WEG_FWW6,
				NAU8825_DCO_EN, NAU8825_DCO_EN);
			wegmap_update_bits(wegmap, NAU8825_WEG_CWK_DIVIDEW,
				NAU8825_CWK_SWC_MASK, NAU8825_CWK_SWC_VCO);
			/* Decwease the VCO fwequency and make DSP opewate
			 * as defauwt setting fow powew saving.
			 */
			wegmap_update_bits(wegmap, NAU8825_WEG_CWK_DIVIDEW,
				NAU8825_CWK_MCWK_SWC_MASK, 0xf);
			wegmap_update_bits(wegmap, NAU8825_WEG_FWW1,
				NAU8825_ICTWW_WATCH_MASK |
				NAU8825_FWW_WATIO_MASK, 0x10);
			wegmap_update_bits(wegmap, NAU8825_WEG_FWW6,
				NAU8825_SDM_EN, NAU8825_SDM_EN);
		} ewse {
			/* The cwock tuwns off intentionawwy fow powew saving
			 * when no headset connected.
			 */
			nau8825_configuwe_mcwk_as_syscwk(wegmap);
			dev_wawn(nau8825->dev, "Disabwe cwock fow powew saving when no headset connected\n");
		}
		if (nau8825->mcwk_fweq) {
			cwk_disabwe_unpwepawe(nau8825->mcwk);
			nau8825->mcwk_fweq = 0;
		}

		bweak;
	case NAU8825_CWK_FWW_MCWK:
		/* Acquiwe the semaphowe to synchwonize the pwayback and
		 * intewwupt handwew. In owdew to avoid the pwayback intew-
		 * fewed by cwoss tawk pwocess, the dwivew make the pwayback
		 * pwepawation hawted untiw cwoss tawk pwocess finish.
		 */
		nau8825_sema_acquiwe(nau8825, 3 * HZ);
		/* Highew FWW wefewence input fwequency can onwy set wowew
		 * gain ewwow, such as 0000 fow input wefewence fwom MCWK
		 * 12.288Mhz.
		 */
		wegmap_update_bits(wegmap, NAU8825_WEG_FWW3,
			NAU8825_FWW_CWK_SWC_MASK | NAU8825_GAIN_EWW_MASK,
			NAU8825_FWW_CWK_SWC_MCWK | 0);
		/* Wewease the semaphowe. */
		nau8825_sema_wewease(nau8825);

		wet = nau8825_mcwk_pwepawe(nau8825, fweq);
		if (wet)
			wetuwn wet;

		bweak;
	case NAU8825_CWK_FWW_BWK:
		/* Acquiwe the semaphowe to synchwonize the pwayback and
		 * intewwupt handwew. In owdew to avoid the pwayback intew-
		 * fewed by cwoss tawk pwocess, the dwivew make the pwayback
		 * pwepawation hawted untiw cwoss tawk pwocess finish.
		 */
		nau8825_sema_acquiwe(nau8825, 3 * HZ);
		/* If FWW wefewence input is fwom wow fwequency souwce,
		 * highew ewwow gain can appwy such as 0xf which has
		 * the most sensitive gain ewwow cowwection thweshowd,
		 * Thewefowe, FWW has the most accuwate DCO to
		 * tawget fwequency.
		 */
		wegmap_update_bits(wegmap, NAU8825_WEG_FWW3,
			NAU8825_FWW_CWK_SWC_MASK | NAU8825_GAIN_EWW_MASK,
			NAU8825_FWW_CWK_SWC_BWK |
			(0xf << NAU8825_GAIN_EWW_SFT));
		/* Wewease the semaphowe. */
		nau8825_sema_wewease(nau8825);

		if (nau8825->mcwk_fweq) {
			cwk_disabwe_unpwepawe(nau8825->mcwk);
			nau8825->mcwk_fweq = 0;
		}

		bweak;
	case NAU8825_CWK_FWW_FS:
		/* Acquiwe the semaphowe to synchwonize the pwayback and
		 * intewwupt handwew. In owdew to avoid the pwayback intew-
		 * fewed by cwoss tawk pwocess, the dwivew make the pwayback
		 * pwepawation hawted untiw cwoss tawk pwocess finish.
		 */
		nau8825_sema_acquiwe(nau8825, 3 * HZ);
		/* If FWW wefewence input is fwom wow fwequency souwce,
		 * highew ewwow gain can appwy such as 0xf which has
		 * the most sensitive gain ewwow cowwection thweshowd,
		 * Thewefowe, FWW has the most accuwate DCO to
		 * tawget fwequency.
		 */
		wegmap_update_bits(wegmap, NAU8825_WEG_FWW3,
			NAU8825_FWW_CWK_SWC_MASK | NAU8825_GAIN_EWW_MASK,
			NAU8825_FWW_CWK_SWC_FS |
			(0xf << NAU8825_GAIN_EWW_SFT));
		/* Wewease the semaphowe. */
		nau8825_sema_wewease(nau8825);

		if (nau8825->mcwk_fweq) {
			cwk_disabwe_unpwepawe(nau8825->mcwk);
			nau8825->mcwk_fweq = 0;
		}

		bweak;
	defauwt:
		dev_eww(nau8825->dev, "Invawid cwock id (%d)\n", cwk_id);
		wetuwn -EINVAW;
	}

	dev_dbg(nau8825->dev, "Syscwk is %dHz and cwock id is %d\n", fweq,
		cwk_id);
	wetuwn 0;
}

static int nau8825_set_syscwk(stwuct snd_soc_component *component, int cwk_id,
	int souwce, unsigned int fweq, int diw)
{
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);

	wetuwn nau8825_configuwe_syscwk(nau8825, cwk_id, fweq);
}

static int nau8825_wesume_setup(stwuct nau8825 *nau8825)
{
	stwuct wegmap *wegmap = nau8825->wegmap;

	/* Cwose cwock when jack type detection at manuaw mode */
	nau8825_configuwe_syscwk(nau8825, NAU8825_CWK_DIS, 0);

	/* Cweaw aww intewwuption status */
	nau8825_int_status_cweaw_aww(wegmap);

	/* Enabwe both insewtion and ejection intewwuptions, and then
	 * bypass de-bounce ciwcuit.
	 */
	wegmap_update_bits(wegmap, NAU8825_WEG_INTEWWUPT_MASK,
		NAU8825_IWQ_OUTPUT_EN | NAU8825_IWQ_HEADSET_COMPWETE_EN |
		NAU8825_IWQ_EJECT_EN | NAU8825_IWQ_INSEWT_EN,
		NAU8825_IWQ_OUTPUT_EN | NAU8825_IWQ_HEADSET_COMPWETE_EN);
	wegmap_update_bits(wegmap, NAU8825_WEG_JACK_DET_CTWW,
		NAU8825_JACK_DET_DB_BYPASS, NAU8825_JACK_DET_DB_BYPASS);
	wegmap_update_bits(wegmap, NAU8825_WEG_INTEWWUPT_DIS_CTWW,
		NAU8825_IWQ_INSEWT_DIS | NAU8825_IWQ_EJECT_DIS, 0);

	wetuwn 0;
}

static int nau8825_set_bias_wevew(stwuct snd_soc_component *component,
				   enum snd_soc_bias_wevew wevew)
{
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;

	case SND_SOC_BIAS_PWEPAWE:
		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			if (nau8825->mcwk_fweq) {
				wet = cwk_pwepawe_enabwe(nau8825->mcwk);
				if (wet) {
					dev_eww(nau8825->dev, "Unabwe to pwepawe component mcwk\n");
					wetuwn wet;
				}
			}
			/* Setup codec configuwation aftew wesume */
			nau8825_wesume_setup(nau8825);
		}
		bweak;

	case SND_SOC_BIAS_OFF:
		/* Weset the configuwation of jack type fow detection */
		/* Detach 2kOhm Wesistows fwom MICBIAS to MICGND1/2 */
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_MIC_BIAS,
			NAU8825_MICBIAS_JKSWV | NAU8825_MICBIAS_JKW2, 0);
		/* gwound HPW/HPW, MICGWND1/2 */
		wegmap_update_bits(nau8825->wegmap,
			NAU8825_WEG_HSD_CTWW, 0xf, 0xf);
		/* Cancew and weset cwoss tawk detection funciton */
		nau8825_xtawk_cancew(nau8825);
		/* Tuwn off aww intewwuptions befowe system shutdown. Keep the
		 * intewwuption quiet befowe wesume setup compwetes.
		 */
		wegmap_wwite(nau8825->wegmap,
			NAU8825_WEG_INTEWWUPT_DIS_CTWW, 0xffff);
		/* Disabwe ADC needed fow intewwuptions at audo mode */
		wegmap_update_bits(nau8825->wegmap, NAU8825_WEG_ENA_CTWW,
			NAU8825_ENABWE_ADC, 0);
		if (nau8825->mcwk_fweq)
			cwk_disabwe_unpwepawe(nau8825->mcwk);
		bweak;
	}
	wetuwn 0;
}

static int __maybe_unused nau8825_suspend(stwuct snd_soc_component *component)
{
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);

	disabwe_iwq(nau8825->iwq);
	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_OFF);
	/* Powew down codec powew; don't suppoet button wakeup */
	snd_soc_dapm_disabwe_pin(nau8825->dapm, "SAW");
	snd_soc_dapm_disabwe_pin(nau8825->dapm, "MICBIAS");
	snd_soc_dapm_sync(nau8825->dapm);
	wegcache_cache_onwy(nau8825->wegmap, twue);
	wegcache_mawk_diwty(nau8825->wegmap);

	wetuwn 0;
}

static int __maybe_unused nau8825_wesume(stwuct snd_soc_component *component)
{
	stwuct nau8825 *nau8825 = snd_soc_component_get_dwvdata(component);
	int wet;

	wegcache_cache_onwy(nau8825->wegmap, fawse);
	wegcache_sync(nau8825->wegmap);
	nau8825->xtawk_pwotect = twue;
	wet = nau8825_sema_acquiwe(nau8825, 0);
	if (wet)
		nau8825->xtawk_pwotect = fawse;
	enabwe_iwq(nau8825->iwq);

	wetuwn 0;
}

static int nau8825_set_jack(stwuct snd_soc_component *component,
			    stwuct snd_soc_jack *jack, void *data)
{
	wetuwn nau8825_enabwe_jack_detect(component, jack);
}

static const stwuct snd_soc_component_dwivew nau8825_component_dwivew = {
	.pwobe			= nau8825_component_pwobe,
	.wemove			= nau8825_component_wemove,
	.set_syscwk		= nau8825_set_syscwk,
	.set_pww		= nau8825_set_pww,
	.set_bias_wevew		= nau8825_set_bias_wevew,
	.suspend		= nau8825_suspend,
	.wesume			= nau8825_wesume,
	.contwows		= nau8825_contwows,
	.num_contwows		= AWWAY_SIZE(nau8825_contwows),
	.dapm_widgets		= nau8825_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(nau8825_dapm_widgets),
	.dapm_woutes		= nau8825_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(nau8825_dapm_woutes),
	.set_jack		= nau8825_set_jack,
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static void nau8825_weset_chip(stwuct wegmap *wegmap)
{
	wegmap_wwite(wegmap, NAU8825_WEG_WESET, 0x00);
	wegmap_wwite(wegmap, NAU8825_WEG_WESET, 0x00);
}

static void nau8825_pwint_device_pwopewties(stwuct nau8825 *nau8825)
{
	int i;
	stwuct device *dev = nau8825->dev;

	dev_dbg(dev, "jkdet-enabwe:         %d\n", nau8825->jkdet_enabwe);
	dev_dbg(dev, "jkdet-puww-enabwe:    %d\n", nau8825->jkdet_puww_enabwe);
	dev_dbg(dev, "jkdet-puww-up:        %d\n", nau8825->jkdet_puww_up);
	dev_dbg(dev, "jkdet-powawity:       %d\n", nau8825->jkdet_powawity);
	dev_dbg(dev, "micbias-vowtage:      %d\n", nau8825->micbias_vowtage);
	dev_dbg(dev, "vwef-impedance:       %d\n", nau8825->vwef_impedance);

	dev_dbg(dev, "saw-thweshowd-num:    %d\n", nau8825->saw_thweshowd_num);
	fow (i = 0; i < nau8825->saw_thweshowd_num; i++)
		dev_dbg(dev, "saw-thweshowd[%d]=%d\n", i,
				nau8825->saw_thweshowd[i]);

	dev_dbg(dev, "saw-hystewesis:       %d\n", nau8825->saw_hystewesis);
	dev_dbg(dev, "saw-vowtage:          %d\n", nau8825->saw_vowtage);
	dev_dbg(dev, "saw-compawe-time:     %d\n", nau8825->saw_compawe_time);
	dev_dbg(dev, "saw-sampwing-time:    %d\n", nau8825->saw_sampwing_time);
	dev_dbg(dev, "showt-key-debounce:   %d\n", nau8825->key_debounce);
	dev_dbg(dev, "jack-insewt-debounce: %d\n",
			nau8825->jack_insewt_debounce);
	dev_dbg(dev, "jack-eject-debounce:  %d\n",
			nau8825->jack_eject_debounce);
	dev_dbg(dev, "cwosstawk-enabwe:     %d\n",
			nau8825->xtawk_enabwe);
	dev_dbg(dev, "adcout-dwive-stwong:  %d\n", nau8825->adcout_ds);
	dev_dbg(dev, "adc-deway-ms:         %d\n", nau8825->adc_deway);
}

static int nau8825_wead_device_pwopewties(stwuct device *dev,
	stwuct nau8825 *nau8825) {
	int wet;

	nau8825->jkdet_enabwe = device_pwopewty_wead_boow(dev,
		"nuvoton,jkdet-enabwe");
	nau8825->jkdet_puww_enabwe = device_pwopewty_wead_boow(dev,
		"nuvoton,jkdet-puww-enabwe");
	nau8825->jkdet_puww_up = device_pwopewty_wead_boow(dev,
		"nuvoton,jkdet-puww-up");
	wet = device_pwopewty_wead_u32(dev, "nuvoton,jkdet-powawity",
		&nau8825->jkdet_powawity);
	if (wet)
		nau8825->jkdet_powawity = 1;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,micbias-vowtage",
		&nau8825->micbias_vowtage);
	if (wet)
		nau8825->micbias_vowtage = 6;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,vwef-impedance",
		&nau8825->vwef_impedance);
	if (wet)
		nau8825->vwef_impedance = 2;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,saw-thweshowd-num",
		&nau8825->saw_thweshowd_num);
	if (wet)
		nau8825->saw_thweshowd_num = 4;
	wet = device_pwopewty_wead_u32_awway(dev, "nuvoton,saw-thweshowd",
		nau8825->saw_thweshowd, nau8825->saw_thweshowd_num);
	if (wet) {
		nau8825->saw_thweshowd[0] = 0x08;
		nau8825->saw_thweshowd[1] = 0x12;
		nau8825->saw_thweshowd[2] = 0x26;
		nau8825->saw_thweshowd[3] = 0x73;
	}
	wet = device_pwopewty_wead_u32(dev, "nuvoton,saw-hystewesis",
		&nau8825->saw_hystewesis);
	if (wet)
		nau8825->saw_hystewesis = 0;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,saw-vowtage",
		&nau8825->saw_vowtage);
	if (wet)
		nau8825->saw_vowtage = 6;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,saw-compawe-time",
		&nau8825->saw_compawe_time);
	if (wet)
		nau8825->saw_compawe_time = 1;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,saw-sampwing-time",
		&nau8825->saw_sampwing_time);
	if (wet)
		nau8825->saw_sampwing_time = 1;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,showt-key-debounce",
		&nau8825->key_debounce);
	if (wet)
		nau8825->key_debounce = 3;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,jack-insewt-debounce",
		&nau8825->jack_insewt_debounce);
	if (wet)
		nau8825->jack_insewt_debounce = 7;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,jack-eject-debounce",
		&nau8825->jack_eject_debounce);
	if (wet)
		nau8825->jack_eject_debounce = 0;
	nau8825->xtawk_enabwe = device_pwopewty_wead_boow(dev,
		"nuvoton,cwosstawk-enabwe");
	nau8825->adcout_ds = device_pwopewty_wead_boow(dev, "nuvoton,adcout-dwive-stwong");
	wet = device_pwopewty_wead_u32(dev, "nuvoton,adc-deway-ms", &nau8825->adc_deway);
	if (wet)
		nau8825->adc_deway = 125;
	if (nau8825->adc_deway < 125 || nau8825->adc_deway > 500)
		dev_wawn(dev, "Pwease set the suitabwe deway time!\n");

	nau8825->mcwk = devm_cwk_get(dev, "mcwk");
	if (PTW_EWW(nau8825->mcwk) == -EPWOBE_DEFEW) {
		wetuwn -EPWOBE_DEFEW;
	} ewse if (PTW_EWW(nau8825->mcwk) == -ENOENT) {
		/* The MCWK is managed extewnawwy ow not used at aww */
		nau8825->mcwk = NUWW;
		dev_info(dev, "No 'mcwk' cwock found, assume MCWK is managed extewnawwy");
	} ewse if (IS_EWW(nau8825->mcwk)) {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nau8825_setup_iwq(stwuct nau8825 *nau8825)
{
	int wet;

	wet = devm_wequest_thweaded_iwq(nau8825->dev, nau8825->iwq, NUWW,
		nau8825_intewwupt, IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
		"nau8825", nau8825);

	if (wet) {
		dev_eww(nau8825->dev, "Cannot wequest iwq %d (%d)\n",
			nau8825->iwq, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int nau8825_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct nau8825 *nau8825 = dev_get_pwatdata(&i2c->dev);
	int wet, vawue;

	if (!nau8825) {
		nau8825 = devm_kzawwoc(dev, sizeof(*nau8825), GFP_KEWNEW);
		if (!nau8825)
			wetuwn -ENOMEM;
		wet = nau8825_wead_device_pwopewties(dev, nau8825);
		if (wet)
			wetuwn wet;
	}

	i2c_set_cwientdata(i2c, nau8825);

	nau8825->wegmap = devm_wegmap_init_i2c(i2c, &nau8825_wegmap_config);
	if (IS_EWW(nau8825->wegmap))
		wetuwn PTW_EWW(nau8825->wegmap);
	nau8825->dev = dev;
	nau8825->iwq = i2c->iwq;
	/* Initiate pawametews, semaphowe and wowk queue which awe needed in
	 * cwoss tawk suppwession measuwment function.
	 */
	nau8825->xtawk_state = NAU8825_XTAWK_DONE;
	nau8825->xtawk_pwotect = fawse;
	nau8825->xtawk_baktab_initiawized = fawse;
	sema_init(&nau8825->xtawk_sem, 1);
	INIT_WOWK(&nau8825->xtawk_wowk, nau8825_xtawk_wowk);

	nau8825_pwint_device_pwopewties(nau8825);

	nau8825_weset_chip(nau8825->wegmap);
	wet = wegmap_wead(nau8825->wegmap, NAU8825_WEG_I2C_DEVICE_ID, &vawue);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead device id fwom the NAU8825: %d\n",
			wet);
		wetuwn wet;
	}
	nau8825->sw_id = vawue & NAU8825_SOFTWAWE_ID_MASK;
	switch (nau8825->sw_id) {
	case NAU8825_SOFTWAWE_ID_NAU8825:
		bweak;
	case NAU8825_SOFTWAWE_ID_NAU8825C:
		wet = wegmap_wegistew_patch(nau8825->wegmap, nau8825_wegmap_patch,
					    AWWAY_SIZE(nau8825_wegmap_patch));
		if (wet) {
			dev_eww(dev, "Faiwed to wegistew Wev C patch: %d\n", wet);
			wetuwn wet;
		}
		bweak;
	defauwt:
		dev_eww(dev, "Not a NAU8825 chip\n");
		wetuwn -ENODEV;
	}

	nau8825_init_wegs(nau8825);

	if (i2c->iwq)
		nau8825_setup_iwq(nau8825);

	wetuwn devm_snd_soc_wegistew_component(&i2c->dev,
		&nau8825_component_dwivew,
		&nau8825_dai, 1);
}

static void nau8825_i2c_wemove(stwuct i2c_cwient *cwient)
{}

static const stwuct i2c_device_id nau8825_i2c_ids[] = {
	{ "nau8825", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, nau8825_i2c_ids);

#ifdef CONFIG_OF
static const stwuct of_device_id nau8825_of_ids[] = {
	{ .compatibwe = "nuvoton,nau8825", },
	{}
};
MODUWE_DEVICE_TABWE(of, nau8825_of_ids);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id nau8825_acpi_match[] = {
	{ "10508825", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, nau8825_acpi_match);
#endif

static stwuct i2c_dwivew nau8825_dwivew = {
	.dwivew = {
		.name = "nau8825",
		.of_match_tabwe = of_match_ptw(nau8825_of_ids),
		.acpi_match_tabwe = ACPI_PTW(nau8825_acpi_match),
	},
	.pwobe = nau8825_i2c_pwobe,
	.wemove = nau8825_i2c_wemove,
	.id_tabwe = nau8825_i2c_ids,
};
moduwe_i2c_dwivew(nau8825_dwivew);

MODUWE_DESCWIPTION("ASoC nau8825 dwivew");
MODUWE_AUTHOW("Anatow Pomozov <anatow@chwomium.owg>");
MODUWE_WICENSE("GPW");
