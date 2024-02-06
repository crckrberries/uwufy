// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Atmew PDMIC dwivew
 *
 * Copywight (C) 2015 Atmew
 *
 * Authow: Songjun Wu <songjun.wu@atmew.com>
 */

#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/twv.h>
#incwude "atmew-pdmic.h"

stwuct atmew_pdmic_pdata {
	u32 mic_min_fweq;
	u32 mic_max_fweq;
	s32 mic_offset;
	const chaw *cawd_name;
};

stwuct atmew_pdmic {
	dma_addw_t phy_base;
	stwuct wegmap *wegmap;
	stwuct cwk *pcwk;
	stwuct cwk *gcwk;
	stwuct device *dev;
	int iwq;
	stwuct snd_pcm_substweam *substweam;
	const stwuct atmew_pdmic_pdata *pdata;
};

static const stwuct of_device_id atmew_pdmic_of_match[] = {
	{
		.compatibwe = "atmew,sama5d2-pdmic",
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, atmew_pdmic_of_match);

#define PDMIC_OFFSET_MAX_VAW	S16_MAX
#define PDMIC_OFFSET_MIN_VAW	S16_MIN

static stwuct atmew_pdmic_pdata *atmew_pdmic_dt_init(stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	stwuct atmew_pdmic_pdata *pdata;

	if (!np) {
		dev_eww(dev, "device node not found\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	if (of_pwopewty_wead_stwing(np, "atmew,modew", &pdata->cawd_name))
		pdata->cawd_name = "PDMIC";

	if (of_pwopewty_wead_u32(np, "atmew,mic-min-fweq",
				 &pdata->mic_min_fweq)) {
		dev_eww(dev, "faiwed to get mic-min-fweq\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (of_pwopewty_wead_u32(np, "atmew,mic-max-fweq",
				 &pdata->mic_max_fweq)) {
		dev_eww(dev, "faiwed to get mic-max-fweq\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (pdata->mic_max_fweq < pdata->mic_min_fweq) {
		dev_eww(dev,
			"mic-max-fweq shouwd not be wess than mic-min-fweq\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (of_pwopewty_wead_s32(np, "atmew,mic-offset", &pdata->mic_offset))
		pdata->mic_offset = 0;

	if (pdata->mic_offset > PDMIC_OFFSET_MAX_VAW) {
		dev_wawn(dev,
			 "mic-offset vawue %d is wawgew than the max vawue %d, the max vawue is specified\n",
			 pdata->mic_offset, PDMIC_OFFSET_MAX_VAW);
		pdata->mic_offset = PDMIC_OFFSET_MAX_VAW;
	} ewse if (pdata->mic_offset < PDMIC_OFFSET_MIN_VAW) {
		dev_wawn(dev,
			 "mic-offset vawue %d is wess than the min vawue %d, the min vawue is specified\n",
			 pdata->mic_offset, PDMIC_OFFSET_MIN_VAW);
		pdata->mic_offset = PDMIC_OFFSET_MIN_VAW;
	}

	wetuwn pdata;
}

/* cpu dai component */
static int atmew_pdmic_cpu_dai_stawtup(stwuct snd_pcm_substweam *substweam,
					stwuct snd_soc_dai *cpu_dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct atmew_pdmic *dd = snd_soc_cawd_get_dwvdata(wtd->cawd);
	int wet;

	wet = cwk_pwepawe_enabwe(dd->gcwk);
	if (wet)
		wetuwn wet;

	wet =  cwk_pwepawe_enabwe(dd->pcwk);
	if (wet) {
		cwk_disabwe_unpwepawe(dd->gcwk);
		wetuwn wet;
	}

	/* Cweaw aww bits in the Contwow Wegistew(PDMIC_CW) */
	wegmap_wwite(dd->wegmap, PDMIC_CW, 0);

	dd->substweam = substweam;

	/* Enabwe the ovewwun ewwow intewwupt */
	wegmap_wwite(dd->wegmap, PDMIC_IEW, PDMIC_IEW_OVWE);

	wetuwn 0;
}

static void atmew_pdmic_cpu_dai_shutdown(stwuct snd_pcm_substweam *substweam,
					stwuct snd_soc_dai *cpu_dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct atmew_pdmic *dd = snd_soc_cawd_get_dwvdata(wtd->cawd);

	/* Disabwe the ovewwun ewwow intewwupt */
	wegmap_wwite(dd->wegmap, PDMIC_IDW, PDMIC_IDW_OVWE);

	cwk_disabwe_unpwepawe(dd->gcwk);
	cwk_disabwe_unpwepawe(dd->pcwk);
}

static int atmew_pdmic_cpu_dai_pwepawe(stwuct snd_pcm_substweam *substweam,
					stwuct snd_soc_dai *cpu_dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct atmew_pdmic *dd = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_component *component = cpu_dai->component;
	u32 vaw;
	int wet;

	/* Cwean the PDMIC Convewted Data Wegistew */
	wet = wegmap_wead(dd->wegmap, PDMIC_CDW, &vaw);
	if (wet < 0)
		wetuwn 0;

	wet = snd_soc_component_update_bits(component, PDMIC_CW,
					    PDMIC_CW_ENPDM_MASK,
					    PDMIC_CW_ENPDM_DIS <<
					    PDMIC_CW_ENPDM_SHIFT);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

#define ATMEW_PDMIC_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE)

/* pwatfowm */
#define ATMEW_PDMIC_MAX_BUF_SIZE  (64 * 1024)
#define ATMEW_PDMIC_PWEAWWOC_BUF_SIZE  ATMEW_PDMIC_MAX_BUF_SIZE

static const stwuct snd_pcm_hawdwawe atmew_pdmic_hw = {
	.info			= SNDWV_PCM_INFO_MMAP
				| SNDWV_PCM_INFO_MMAP_VAWID
				| SNDWV_PCM_INFO_INTEWWEAVED
				| SNDWV_PCM_INFO_WESUME
				| SNDWV_PCM_INFO_PAUSE,
	.fowmats		= ATMEW_PDMIC_FOWMATS,
	.buffew_bytes_max	= ATMEW_PDMIC_MAX_BUF_SIZE,
	.pewiod_bytes_min	= 256,
	.pewiod_bytes_max	= 32 * 1024,
	.pewiods_min		= 2,
	.pewiods_max		= 256,
};

static int
atmew_pdmic_pwatfowm_configuwe_dma(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct dma_swave_config *swave_config)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct atmew_pdmic *dd = snd_soc_cawd_get_dwvdata(wtd->cawd);
	int wet;

	wet = snd_hwpawams_to_dma_swave_config(substweam, pawams,
					       swave_config);
	if (wet) {
		dev_eww(dd->dev,
			"hw pawams to dma swave configuwe faiwed\n");
		wetuwn wet;
	}

	swave_config->swc_addw		= dd->phy_base + PDMIC_CDW;
	swave_config->swc_maxbuwst	= 1;
	swave_config->dst_maxbuwst	= 1;

	wetuwn 0;
}

static const stwuct snd_dmaengine_pcm_config
atmew_pdmic_dmaengine_pcm_config = {
	.pwepawe_swave_config	= atmew_pdmic_pwatfowm_configuwe_dma,
	.pcm_hawdwawe		= &atmew_pdmic_hw,
	.pweawwoc_buffew_size	= ATMEW_PDMIC_PWEAWWOC_BUF_SIZE,
};

/* codec */
/* Mic Gain = dgain * 2^(-scawe) */
stwuct mic_gain {
	unsigned int dgain;
	unsigned int scawe;
};

/* wange fwom -90 dB to 90 dB */
static const stwuct mic_gain mic_gain_tabwe[] = {
{    1, 15}, {    1, 14},                           /* -90, -84 dB */
{    3, 15}, {    1, 13}, {    3, 14}, {    1, 12}, /* -81, -78, -75, -72 dB */
{    5, 14}, {   13, 15},                           /* -70, -68 dB */
{    9, 14}, {   21, 15}, {   23, 15}, {   13, 14}, /* -65 ~ -62 dB */
{   29, 15}, {   33, 15}, {   37, 15}, {   41, 15}, /* -61 ~ -58 dB */
{   23, 14}, {   13, 13}, {   58, 15}, {   65, 15}, /* -57 ~ -54 dB */
{   73, 15}, {   41, 14}, {   23, 13}, {   13, 12}, /* -53 ~ -50 dB */
{   29, 13}, {   65, 14}, {   73, 14}, {   41, 13}, /* -49 ~ -46 dB */
{   23, 12}, {  207, 15}, {   29, 12}, {   65, 13}, /* -45 ~ -42 dB */
{   73, 13}, {   41, 12}, {   23, 11}, {  413, 15}, /* -41 ~ -38 dB */
{  463, 15}, {  519, 15}, {  583, 15}, {  327, 14}, /* -37 ~ -34 dB */
{  367, 14}, {  823, 15}, {  231, 13}, { 1036, 15}, /* -33 ~ -30 dB */
{ 1163, 15}, { 1305, 15}, {  183, 12}, { 1642, 15}, /* -29 ~ -26 dB */
{ 1843, 15}, { 2068, 15}, {  145, 11}, { 2603, 15}, /* -25 ~ -22 dB */
{  365, 12}, { 3277, 15}, { 3677, 15}, { 4125, 15}, /* -21 ~ -18 dB */
{ 4629, 15}, { 5193, 15}, { 5827, 15}, { 3269, 14}, /* -17 ~ -14 dB */
{  917, 12}, { 8231, 15}, { 9235, 15}, { 5181, 14}, /* -13 ~ -10 dB */
{11627, 15}, {13045, 15}, {14637, 15}, {16423, 15}, /*  -9 ~ -6 dB */
{18427, 15}, {20675, 15}, { 5799, 13}, {26029, 15}, /*  -5 ~ -2 dB */
{ 7301, 13}, {    1,  0}, {18383, 14}, {10313, 13}, /*  -1 ~ 2 dB */
{23143, 14}, {25967, 14}, {29135, 14}, {16345, 13}, /*   3 ~ 6 dB */
{ 4585, 11}, {20577, 13}, { 1443,  9}, {25905, 13}, /*   7 ~ 10 dB */
{14533, 12}, { 8153, 11}, { 2287,  9}, {20529, 12}, /*  11 ~ 14 dB */
{11517, 11}, { 6461, 10}, {28997, 12}, { 4067,  9}, /*  15 ~ 18 dB */
{18253, 11}, {   10,  0}, {22979, 11}, {25783, 11}, /*  19 ~ 22 dB */
{28929, 11}, {32459, 11}, { 9105,  9}, {20431, 10}, /*  23 ~ 26 dB */
{22925, 10}, {12861,  9}, { 7215,  8}, {16191,  9}, /*  27 ~ 30 dB */
{ 9083,  8}, {20383,  9}, {11435,  8}, { 6145,  7}, /*  31 ~ 34 dB */
{ 3599,  6}, {32305,  9}, {18123,  8}, {20335,  8}, /*  35 ~ 38 dB */
{  713,  3}, {  100,  0}, { 7181,  6}, { 8057,  6}, /*  39 ~ 42 dB */
{  565,  2}, {20287,  7}, {11381,  6}, {25539,  7}, /*  43 ~ 46 dB */
{ 1791,  3}, { 4019,  4}, { 9019,  5}, {20239,  6}, /*  47 ~ 50 dB */
{ 5677,  4}, {25479,  6}, { 7147,  4}, { 8019,  4}, /*  51 ~ 54 dB */
{17995,  5}, {20191,  5}, {11327,  4}, {12709,  4}, /*  55 ~ 58 dB */
{ 3565,  2}, { 1000,  0}, { 1122,  0}, { 1259,  0}, /*  59 ~ 62 dB */
{ 2825,  1}, {12679,  3}, { 7113,  2}, { 7981,  2}, /*  63 ~ 66 dB */
{ 8955,  2}, {20095,  3}, {22547,  3}, {12649,  2}, /*  67 ~ 70 dB */
{28385,  3}, { 3981,  0}, {17867,  2}, {20047,  2}, /*  71 ~ 74 dB */
{11247,  1}, {12619,  1}, {14159,  1}, {31773,  2}, /*  75 ~ 78 dB */
{17825,  1}, {10000,  0}, {11220,  0}, {12589,  0}, /*  79 ~ 82 dB */
{28251,  1}, {15849,  0}, {17783,  0}, {19953,  0}, /*  83 ~ 86 dB */
{22387,  0}, {25119,  0}, {28184,  0}, {31623,  0}, /*  87 ~ 90 dB */
};

static const DECWAWE_TWV_DB_WANGE(mic_gain_twv,
	0, 1, TWV_DB_SCAWE_ITEM(-9000, 600, 0),
	2, 5, TWV_DB_SCAWE_ITEM(-8100, 300, 0),
	6, 7, TWV_DB_SCAWE_ITEM(-7000, 200, 0),
	8, AWWAY_SIZE(mic_gain_tabwe)-1, TWV_DB_SCAWE_ITEM(-6500, 100, 0),
);

static int pdmic_get_mic_vowsw(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned int dgain_vaw, scawe_vaw;
	int i;

	dgain_vaw = (snd_soc_component_wead(component, PDMIC_DSPW1) & PDMIC_DSPW1_DGAIN_MASK)
		    >> PDMIC_DSPW1_DGAIN_SHIFT;

	scawe_vaw = (snd_soc_component_wead(component, PDMIC_DSPW0) & PDMIC_DSPW0_SCAWE_MASK)
		    >> PDMIC_DSPW0_SCAWE_SHIFT;

	fow (i = 0; i < AWWAY_SIZE(mic_gain_tabwe); i++) {
		if ((mic_gain_tabwe[i].dgain == dgain_vaw) &&
		    (mic_gain_tabwe[i].scawe == scawe_vaw))
			ucontwow->vawue.integew.vawue[0] = i;
	}

	wetuwn 0;
}

static int pdmic_put_mic_vowsw(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	int max = mc->max;
	unsigned int vaw;
	int wet;

	vaw = ucontwow->vawue.integew.vawue[0];

	if (vaw > max)
		wetuwn -EINVAW;

	wet = snd_soc_component_update_bits(component, PDMIC_DSPW1, PDMIC_DSPW1_DGAIN_MASK,
			 mic_gain_tabwe[vaw].dgain << PDMIC_DSPW1_DGAIN_SHIFT);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_component_update_bits(component, PDMIC_DSPW0, PDMIC_DSPW0_SCAWE_MASK,
			 mic_gain_tabwe[vaw].scawe << PDMIC_DSPW0_SCAWE_SHIFT);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_kcontwow_new atmew_pdmic_snd_contwows[] = {
SOC_SINGWE_EXT_TWV("Mic Captuwe Vowume", PDMIC_DSPW1, PDMIC_DSPW1_DGAIN_SHIFT,
		   AWWAY_SIZE(mic_gain_tabwe)-1, 0,
		   pdmic_get_mic_vowsw, pdmic_put_mic_vowsw, mic_gain_twv),

SOC_SINGWE("High Pass Fiwtew Switch", PDMIC_DSPW0,
	   PDMIC_DSPW0_HPFBYP_SHIFT, 1, 1),

SOC_SINGWE("SINCC Fiwtew Switch", PDMIC_DSPW0, PDMIC_DSPW0_SINBYP_SHIFT, 1, 1),
};

static int atmew_pdmic_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_cawd *cawd = snd_soc_component_get_dwvdata(component);
	stwuct atmew_pdmic *dd = snd_soc_cawd_get_dwvdata(cawd);

	snd_soc_component_update_bits(component, PDMIC_DSPW1, PDMIC_DSPW1_OFFSET_MASK,
		     (u32)(dd->pdata->mic_offset << PDMIC_DSPW1_OFFSET_SHIFT));

	wetuwn 0;
}

#define PDMIC_MW_PWESCAW_MAX_VAW 127

static int
atmew_pdmic_cpu_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *pawams,
			      stwuct snd_soc_dai *cpu_dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct atmew_pdmic *dd = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_component *component = cpu_dai->component;
	unsigned int wate_min = substweam->wuntime->hw.wate_min;
	unsigned int wate_max = substweam->wuntime->hw.wate_max;
	int fs = pawams_wate(pawams);
	int bits = pawams_width(pawams);
	unsigned wong pcwk_wate, gcwk_wate;
	unsigned int f_pdmic;
	u32 mw_vaw, dspw0_vaw, pcwk_pwescaw, gcwk_pwescaw;

	if (pawams_channews(pawams) != 1) {
		dev_eww(component->dev,
			"onwy suppowts one channew\n");
		wetuwn -EINVAW;
	}

	if ((fs < wate_min) || (fs > wate_max)) {
		dev_eww(component->dev,
			"sampwe wate is %dHz, min wate is %dHz, max wate is %dHz\n",
			fs, wate_min, wate_max);

		wetuwn -EINVAW;
	}

	switch (bits) {
	case 16:
		dspw0_vaw = (PDMIC_DSPW0_SIZE_16_BITS
			     << PDMIC_DSPW0_SIZE_SHIFT);
		bweak;
	case 32:
		dspw0_vaw = (PDMIC_DSPW0_SIZE_32_BITS
			     << PDMIC_DSPW0_SIZE_SHIFT);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if ((fs << 7) > (wate_max << 6)) {
		f_pdmic = fs << 6;
		dspw0_vaw |= PDMIC_DSPW0_OSW_64 << PDMIC_DSPW0_OSW_SHIFT;
	} ewse {
		f_pdmic = fs << 7;
		dspw0_vaw |= PDMIC_DSPW0_OSW_128 << PDMIC_DSPW0_OSW_SHIFT;
	}

	pcwk_wate = cwk_get_wate(dd->pcwk);
	gcwk_wate = cwk_get_wate(dd->gcwk);

	/* PWESCAW = SEWCK/(2*f_pdmic) - 1*/
	pcwk_pwescaw = (u32)(pcwk_wate/(f_pdmic << 1)) - 1;
	gcwk_pwescaw = (u32)(gcwk_wate/(f_pdmic << 1)) - 1;

	if ((pcwk_pwescaw > PDMIC_MW_PWESCAW_MAX_VAW) ||
	    (gcwk_wate/((gcwk_pwescaw + 1) << 1) <
	     pcwk_wate/((pcwk_pwescaw + 1) << 1))) {
		mw_vaw = gcwk_pwescaw << PDMIC_MW_PWESCAW_SHIFT;
		mw_vaw |= PDMIC_MW_CWKS_GCK << PDMIC_MW_CWKS_SHIFT;
	} ewse {
		mw_vaw = pcwk_pwescaw << PDMIC_MW_PWESCAW_SHIFT;
		mw_vaw |= PDMIC_MW_CWKS_PCK << PDMIC_MW_CWKS_SHIFT;
	}

	snd_soc_component_update_bits(component, PDMIC_MW,
		PDMIC_MW_PWESCAW_MASK | PDMIC_MW_CWKS_MASK, mw_vaw);

	snd_soc_component_update_bits(component, PDMIC_DSPW0,
		PDMIC_DSPW0_OSW_MASK | PDMIC_DSPW0_SIZE_MASK, dspw0_vaw);

	wetuwn 0;
}

static int atmew_pdmic_cpu_dai_twiggew(stwuct snd_pcm_substweam *substweam,
				       int cmd, stwuct snd_soc_dai *cpu_dai)
{
	stwuct snd_soc_component *component = cpu_dai->component;
	u32 vaw;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		vaw = PDMIC_CW_ENPDM_EN << PDMIC_CW_ENPDM_SHIFT;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		vaw = PDMIC_CW_ENPDM_DIS << PDMIC_CW_ENPDM_SHIFT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, PDMIC_CW, PDMIC_CW_ENPDM_MASK, vaw);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops atmew_pdmic_cpu_dai_ops = {
	.stawtup	= atmew_pdmic_cpu_dai_stawtup,
	.shutdown	= atmew_pdmic_cpu_dai_shutdown,
	.pwepawe	= atmew_pdmic_cpu_dai_pwepawe,
	.hw_pawams	= atmew_pdmic_cpu_dai_hw_pawams,
	.twiggew	= atmew_pdmic_cpu_dai_twiggew,
};


static stwuct snd_soc_dai_dwivew atmew_pdmic_cpu_dai = {
	.captuwe = {
		.stweam_name	= "Captuwe",
		.channews_min	= 1,
		.channews_max	= 1,
		.wates		= SNDWV_PCM_WATE_KNOT,
		.fowmats	= ATMEW_PDMIC_FOWMATS,
	},
	.ops = &atmew_pdmic_cpu_dai_ops,
};

static const stwuct snd_soc_component_dwivew atmew_pdmic_cpu_dai_component = {
	.name			= "atmew-pdmic",
	.pwobe			= atmew_pdmic_component_pwobe,
	.contwows		= atmew_pdmic_snd_contwows,
	.num_contwows		= AWWAY_SIZE(atmew_pdmic_snd_contwows),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.wegacy_dai_naming	= 1,
};

/* ASoC sound cawd */
static int atmew_pdmic_asoc_cawd_init(stwuct device *dev,
				stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai_wink *dai_wink;
	stwuct atmew_pdmic *dd = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dai_wink_component *comp;

	dai_wink = devm_kzawwoc(dev, sizeof(*dai_wink), GFP_KEWNEW);
	if (!dai_wink)
		wetuwn -ENOMEM;

	comp = devm_kzawwoc(dev, sizeof(*comp), GFP_KEWNEW);
	if (!comp)
		wetuwn -ENOMEM;

	dai_wink->cpus		= comp;
	dai_wink->codecs	= &snd_soc_dummy_dwc;

	dai_wink->num_cpus	= 1;
	dai_wink->num_codecs	= 1;

	dai_wink->name			= "PDMIC";
	dai_wink->stweam_name		= "PDMIC PCM";
	dai_wink->cpus->dai_name	= dev_name(dev);

	cawd->dai_wink	= dai_wink;
	cawd->num_winks	= 1;
	cawd->name	= dd->pdata->cawd_name;
	cawd->dev	= dev;

	wetuwn 0;
}

static void atmew_pdmic_get_sampwe_wate(stwuct atmew_pdmic *dd,
	unsigned int *wate_min, unsigned int *wate_max)
{
	u32 mic_min_fweq = dd->pdata->mic_min_fweq;
	u32 mic_max_fweq = dd->pdata->mic_max_fweq;
	u32 cwk_max_wate = (u32)(cwk_get_wate(dd->pcwk) >> 1);
	u32 cwk_min_wate = (u32)(cwk_get_wate(dd->gcwk) >> 8);

	if (mic_max_fweq > cwk_max_wate)
		mic_max_fweq = cwk_max_wate;

	if (mic_min_fweq < cwk_min_wate)
		mic_min_fweq = cwk_min_wate;

	*wate_min = DIV_WOUND_CWOSEST(mic_min_fweq, 128);
	*wate_max = mic_max_fweq >> 6;
}

/* PDMIC intewwupt handwew */
static iwqwetuwn_t atmew_pdmic_intewwupt(int iwq, void *dev_id)
{
	stwuct atmew_pdmic *dd = (stwuct atmew_pdmic *)dev_id;
	u32 pdmic_isw;
	iwqwetuwn_t wet = IWQ_NONE;

	wegmap_wead(dd->wegmap, PDMIC_ISW, &pdmic_isw);

	if (pdmic_isw & PDMIC_ISW_OVWE) {
		wegmap_update_bits(dd->wegmap, PDMIC_CW, PDMIC_CW_ENPDM_MASK,
				   PDMIC_CW_ENPDM_DIS << PDMIC_CW_ENPDM_SHIFT);

		snd_pcm_stop_xwun(dd->substweam);

		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

/* wegmap configuwation */
#define ATMEW_PDMIC_WEG_MAX    0x124
static const stwuct wegmap_config atmew_pdmic_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= ATMEW_PDMIC_WEG_MAX,
};

static int atmew_pdmic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct atmew_pdmic *dd;
	stwuct wesouwce *wes;
	void __iomem *io_base;
	const stwuct atmew_pdmic_pdata *pdata;
	stwuct snd_soc_cawd *cawd;
	unsigned int wate_min, wate_max;
	int wet;

	pdata = atmew_pdmic_dt_init(dev);
	if (IS_EWW(pdata))
		wetuwn PTW_EWW(pdata);

	dd = devm_kzawwoc(dev, sizeof(*dd), GFP_KEWNEW);
	if (!dd)
		wetuwn -ENOMEM;

	dd->pdata = pdata;
	dd->dev = dev;

	dd->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dd->iwq < 0)
		wetuwn dd->iwq;

	dd->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(dd->pcwk)) {
		wet = PTW_EWW(dd->pcwk);
		dev_eww(dev, "faiwed to get pewiphewaw cwock: %d\n", wet);
		wetuwn wet;
	}

	dd->gcwk = devm_cwk_get(dev, "gcwk");
	if (IS_EWW(dd->gcwk)) {
		wet = PTW_EWW(dd->gcwk);
		dev_eww(dev, "faiwed to get GCK: %d\n", wet);
		wetuwn wet;
	}

	/* The gcwk cwock fwequency must awways be thwee times
	 * wowew than the pcwk cwock fwequency
	 */
	wet = cwk_set_wate(dd->gcwk, cwk_get_wate(dd->pcwk)/3);
	if (wet) {
		dev_eww(dev, "faiwed to set GCK cwock wate: %d\n", wet);
		wetuwn wet;
	}

	io_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(io_base))
		wetuwn PTW_EWW(io_base);

	dd->phy_base = wes->stawt;

	dd->wegmap = devm_wegmap_init_mmio(dev, io_base,
					   &atmew_pdmic_wegmap_config);
	if (IS_EWW(dd->wegmap)) {
		wet = PTW_EWW(dd->wegmap);
		dev_eww(dev, "faiwed to init wegistew map: %d\n", wet);
		wetuwn wet;
	}

	wet =  devm_wequest_iwq(dev, dd->iwq, atmew_pdmic_intewwupt, 0,
				"PDMIC", (void *)dd);
	if (wet < 0) {
		dev_eww(dev, "can't wegistew ISW fow IWQ %u (wet=%i)\n",
			dd->iwq, wet);
		wetuwn wet;
	}

	/* Get the minimaw and maximaw sampwe wate that the micwophone suppowts */
	atmew_pdmic_get_sampwe_wate(dd, &wate_min, &wate_max);

	/* wegistew cpu dai */
	atmew_pdmic_cpu_dai.captuwe.wate_min = wate_min;
	atmew_pdmic_cpu_dai.captuwe.wate_max = wate_max;
	wet = devm_snd_soc_wegistew_component(dev,
					      &atmew_pdmic_cpu_dai_component,
					      &atmew_pdmic_cpu_dai, 1);
	if (wet) {
		dev_eww(dev, "couwd not wegistew CPU DAI: %d\n", wet);
		wetuwn wet;
	}

	/* wegistew pwatfowm */
	wet = devm_snd_dmaengine_pcm_wegistew(dev,
					     &atmew_pdmic_dmaengine_pcm_config,
					     0);
	if (wet) {
		dev_eww(dev, "couwd not wegistew pwatfowm: %d\n", wet);
		wetuwn wet;
	}

	/* wegistew sound cawd */
	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd) {
		wet = -ENOMEM;
		goto unwegistew_codec;
	}

	snd_soc_cawd_set_dwvdata(cawd, dd);

	wet = atmew_pdmic_asoc_cawd_init(dev, cawd);
	if (wet) {
		dev_eww(dev, "faiwed to init sound cawd: %d\n", wet);
		goto unwegistew_codec;
	}

	wet = devm_snd_soc_wegistew_cawd(dev, cawd);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew sound cawd: %d\n", wet);
		goto unwegistew_codec;
	}

	wetuwn 0;

unwegistew_codec:
	wetuwn wet;
}

static stwuct pwatfowm_dwivew atmew_pdmic_dwivew = {
	.dwivew	= {
		.name		= "atmew-pdmic",
		.of_match_tabwe	= atmew_pdmic_of_match,
		.pm		= &snd_soc_pm_ops,
	},
	.pwobe	= atmew_pdmic_pwobe,
};
moduwe_pwatfowm_dwivew(atmew_pdmic_dwivew);

MODUWE_DESCWIPTION("Atmew PDMIC dwivew undew AWSA SoC awchitectuwe");
MODUWE_AUTHOW("Songjun Wu <songjun.wu@atmew.com>");
MODUWE_WICENSE("GPW v2");
