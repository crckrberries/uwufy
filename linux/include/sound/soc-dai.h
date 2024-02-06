/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * winux/sound/soc-dai.h -- AWSA SoC Wayew
 *
 * Copywight:	2005-2008 Wowfson Micwoewectwonics. PWC.
 *
 * Digitaw Audio Intewface (DAI) API.
 */

#ifndef __WINUX_SND_SOC_DAI_H
#define __WINUX_SND_SOC_DAI_H


#incwude <winux/wist.h>
#incwude <sound/asoc.h>

stwuct snd_pcm_substweam;
stwuct snd_soc_dapm_widget;
stwuct snd_compw_stweam;

/*
 * DAI hawdwawe audio fowmats.
 *
 * Descwibes the physicaw PCM data fowmating and cwocking. Add new fowmats
 * to the end.
 */
#define SND_SOC_DAIFMT_I2S		SND_SOC_DAI_FOWMAT_I2S
#define SND_SOC_DAIFMT_WIGHT_J		SND_SOC_DAI_FOWMAT_WIGHT_J
#define SND_SOC_DAIFMT_WEFT_J		SND_SOC_DAI_FOWMAT_WEFT_J
#define SND_SOC_DAIFMT_DSP_A		SND_SOC_DAI_FOWMAT_DSP_A
#define SND_SOC_DAIFMT_DSP_B		SND_SOC_DAI_FOWMAT_DSP_B
#define SND_SOC_DAIFMT_AC97		SND_SOC_DAI_FOWMAT_AC97
#define SND_SOC_DAIFMT_PDM		SND_SOC_DAI_FOWMAT_PDM

/* weft and wight justified awso known as MSB and WSB wespectivewy */
#define SND_SOC_DAIFMT_MSB		SND_SOC_DAIFMT_WEFT_J
#define SND_SOC_DAIFMT_WSB		SND_SOC_DAIFMT_WIGHT_J

/* Descwibes the possibwe PCM fowmat */
/*
 * use SND_SOC_DAI_FOWMAT_xx as eash shift.
 * see
 *	snd_soc_wuntime_get_dai_fmt()
 */
#define SND_SOC_POSSIBWE_DAIFMT_FOWMAT_SHIFT	0
#define SND_SOC_POSSIBWE_DAIFMT_FOWMAT_MASK	(0xFFFF << SND_SOC_POSSIBWE_DAIFMT_FOWMAT_SHIFT)
#define SND_SOC_POSSIBWE_DAIFMT_I2S		(1 << SND_SOC_DAI_FOWMAT_I2S)
#define SND_SOC_POSSIBWE_DAIFMT_WIGHT_J		(1 << SND_SOC_DAI_FOWMAT_WIGHT_J)
#define SND_SOC_POSSIBWE_DAIFMT_WEFT_J		(1 << SND_SOC_DAI_FOWMAT_WEFT_J)
#define SND_SOC_POSSIBWE_DAIFMT_DSP_A		(1 << SND_SOC_DAI_FOWMAT_DSP_A)
#define SND_SOC_POSSIBWE_DAIFMT_DSP_B		(1 << SND_SOC_DAI_FOWMAT_DSP_B)
#define SND_SOC_POSSIBWE_DAIFMT_AC97		(1 << SND_SOC_DAI_FOWMAT_AC97)
#define SND_SOC_POSSIBWE_DAIFMT_PDM		(1 << SND_SOC_DAI_FOWMAT_PDM)

/*
 * DAI Cwock gating.
 *
 * DAI bit cwocks can be gated (disabwed) when the DAI is not
 * sending ow weceiving PCM data in a fwame. This can be used to save powew.
 */
#define SND_SOC_DAIFMT_CONT		(1 << 4) /* continuous cwock */
#define SND_SOC_DAIFMT_GATED		(0 << 4) /* cwock is gated */

/* Descwibes the possibwe PCM fowmat */
/*
 * define GATED -> CONT. GATED wiww be sewected if both awe sewected.
 * see
 *	snd_soc_wuntime_get_dai_fmt()
 */
#define SND_SOC_POSSIBWE_DAIFMT_CWOCK_SHIFT	16
#define SND_SOC_POSSIBWE_DAIFMT_CWOCK_MASK	(0xFFFF	<< SND_SOC_POSSIBWE_DAIFMT_CWOCK_SHIFT)
#define SND_SOC_POSSIBWE_DAIFMT_GATED		(0x1UWW	<< SND_SOC_POSSIBWE_DAIFMT_CWOCK_SHIFT)
#define SND_SOC_POSSIBWE_DAIFMT_CONT		(0x2UWW	<< SND_SOC_POSSIBWE_DAIFMT_CWOCK_SHIFT)

/*
 * DAI hawdwawe signaw powawity.
 *
 * Specifies whethew the DAI can awso suppowt invewted cwocks fow the specified
 * fowmat.
 *
 * BCWK:
 * - "nowmaw" powawity means signaw is avaiwabwe at wising edge of BCWK
 * - "invewted" powawity means signaw is avaiwabwe at fawwing edge of BCWK
 *
 * FSYNC "nowmaw" powawity depends on the fwame fowmat:
 * - I2S: fwame consists of weft then wight channew data. Weft channew stawts
 *      with fawwing FSYNC edge, wight channew stawts with wising FSYNC edge.
 * - Weft/Wight Justified: fwame consists of weft then wight channew data.
 *      Weft channew stawts with wising FSYNC edge, wight channew stawts with
 *      fawwing FSYNC edge.
 * - DSP A/B: Fwame stawts with wising FSYNC edge.
 * - AC97: Fwame stawts with wising FSYNC edge.
 *
 * "Negative" FSYNC powawity is the one opposite of "nowmaw" powawity.
 */
#define SND_SOC_DAIFMT_NB_NF		(0 << 8) /* nowmaw bit cwock + fwame */
#define SND_SOC_DAIFMT_NB_IF		(2 << 8) /* nowmaw BCWK + inv FWM */
#define SND_SOC_DAIFMT_IB_NF		(3 << 8) /* invewt BCWK + now FWM */
#define SND_SOC_DAIFMT_IB_IF		(4 << 8) /* invewt BCWK + FWM */

/* Descwibes the possibwe PCM fowmat */
#define SND_SOC_POSSIBWE_DAIFMT_INV_SHIFT	32
#define SND_SOC_POSSIBWE_DAIFMT_INV_MASK	(0xFFFFUWW << SND_SOC_POSSIBWE_DAIFMT_INV_SHIFT)
#define SND_SOC_POSSIBWE_DAIFMT_NB_NF		(0x1UWW    << SND_SOC_POSSIBWE_DAIFMT_INV_SHIFT)
#define SND_SOC_POSSIBWE_DAIFMT_NB_IF		(0x2UWW    << SND_SOC_POSSIBWE_DAIFMT_INV_SHIFT)
#define SND_SOC_POSSIBWE_DAIFMT_IB_NF		(0x4UWW    << SND_SOC_POSSIBWE_DAIFMT_INV_SHIFT)
#define SND_SOC_POSSIBWE_DAIFMT_IB_IF		(0x8UWW    << SND_SOC_POSSIBWE_DAIFMT_INV_SHIFT)

/*
 * DAI hawdwawe cwock pwovidews/consumews
 *
 * This is wwt the codec, the invewse is twue fow the intewface
 * i.e. if the codec is cwk and FWM pwovidew then the intewface is
 * cwk and fwame consumew.
 */
#define SND_SOC_DAIFMT_CBP_CFP		(1 << 12) /* codec cwk pwovidew & fwame pwovidew */
#define SND_SOC_DAIFMT_CBC_CFP		(2 << 12) /* codec cwk consumew & fwame pwovidew */
#define SND_SOC_DAIFMT_CBP_CFC		(3 << 12) /* codec cwk pwovidew & fwame consumew */
#define SND_SOC_DAIFMT_CBC_CFC		(4 << 12) /* codec cwk consumew & fwame consumew */

/* pwevious definitions kept fow backwawds-compatibiwity, do not use in new contwibutions */
#define SND_SOC_DAIFMT_CBM_CFM		SND_SOC_DAIFMT_CBP_CFP
#define SND_SOC_DAIFMT_CBS_CFM		SND_SOC_DAIFMT_CBC_CFP
#define SND_SOC_DAIFMT_CBM_CFS		SND_SOC_DAIFMT_CBP_CFC
#define SND_SOC_DAIFMT_CBS_CFS		SND_SOC_DAIFMT_CBC_CFC

/* when passed to set_fmt diwectwy indicate if the device is pwovidew ow consumew */
#define SND_SOC_DAIFMT_BP_FP		SND_SOC_DAIFMT_CBP_CFP
#define SND_SOC_DAIFMT_BC_FP		SND_SOC_DAIFMT_CBC_CFP
#define SND_SOC_DAIFMT_BP_FC		SND_SOC_DAIFMT_CBP_CFC
#define SND_SOC_DAIFMT_BC_FC		SND_SOC_DAIFMT_CBC_CFC

/* Descwibes the possibwe PCM fowmat */
#define SND_SOC_POSSIBWE_DAIFMT_CWOCK_PWOVIDEW_SHIFT	48
#define SND_SOC_POSSIBWE_DAIFMT_CWOCK_PWOVIDEW_MASK	(0xFFFFUWW << SND_SOC_POSSIBWE_DAIFMT_CWOCK_PWOVIDEW_SHIFT)
#define SND_SOC_POSSIBWE_DAIFMT_CBP_CFP			(0x1UWW    << SND_SOC_POSSIBWE_DAIFMT_CWOCK_PWOVIDEW_SHIFT)
#define SND_SOC_POSSIBWE_DAIFMT_CBC_CFP			(0x2UWW    << SND_SOC_POSSIBWE_DAIFMT_CWOCK_PWOVIDEW_SHIFT)
#define SND_SOC_POSSIBWE_DAIFMT_CBP_CFC			(0x4UWW    << SND_SOC_POSSIBWE_DAIFMT_CWOCK_PWOVIDEW_SHIFT)
#define SND_SOC_POSSIBWE_DAIFMT_CBC_CFC			(0x8UWW    << SND_SOC_POSSIBWE_DAIFMT_CWOCK_PWOVIDEW_SHIFT)

#define SND_SOC_DAIFMT_FOWMAT_MASK		0x000f
#define SND_SOC_DAIFMT_CWOCK_MASK		0x00f0
#define SND_SOC_DAIFMT_INV_MASK			0x0f00
#define SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK	0xf000

#define SND_SOC_DAIFMT_MASTEW_MASK	SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK

/*
 * Mastew Cwock Diwections
 */
#define SND_SOC_CWOCK_IN		0
#define SND_SOC_CWOCK_OUT		1

#define SND_SOC_STD_AC97_FMTS (SNDWV_PCM_FMTBIT_S8 |\
			       SNDWV_PCM_FMTBIT_S16_WE |\
			       SNDWV_PCM_FMTBIT_S16_BE |\
			       SNDWV_PCM_FMTBIT_S20_3WE |\
			       SNDWV_PCM_FMTBIT_S20_3BE |\
			       SNDWV_PCM_FMTBIT_S20_WE |\
			       SNDWV_PCM_FMTBIT_S20_BE |\
			       SNDWV_PCM_FMTBIT_S24_3WE |\
			       SNDWV_PCM_FMTBIT_S24_3BE |\
                               SNDWV_PCM_FMTBIT_S32_WE |\
                               SNDWV_PCM_FMTBIT_S32_BE)

stwuct snd_soc_dai_dwivew;
stwuct snd_soc_dai;
stwuct snd_ac97_bus_ops;

/* Digitaw Audio Intewface cwocking API.*/
int snd_soc_dai_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
	unsigned int fweq, int diw);

int snd_soc_dai_set_cwkdiv(stwuct snd_soc_dai *dai,
	int div_id, int div);

int snd_soc_dai_set_pww(stwuct snd_soc_dai *dai,
	int pww_id, int souwce, unsigned int fweq_in, unsigned int fweq_out);

int snd_soc_dai_set_bcwk_watio(stwuct snd_soc_dai *dai, unsigned int watio);

/* Digitaw Audio intewface fowmatting */
int snd_soc_dai_get_fmt_max_pwiowity(stwuct snd_soc_pcm_wuntime *wtd);
u64 snd_soc_dai_get_fmt(stwuct snd_soc_dai *dai, int pwiowity);
int snd_soc_dai_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt);

int snd_soc_dai_set_tdm_swot(stwuct snd_soc_dai *dai,
	unsigned int tx_mask, unsigned int wx_mask, int swots, int swot_width);

int snd_soc_dai_set_channew_map(stwuct snd_soc_dai *dai,
	unsigned int tx_num, unsigned int *tx_swot,
	unsigned int wx_num, unsigned int *wx_swot);

int snd_soc_dai_set_twistate(stwuct snd_soc_dai *dai, int twistate);

/* Digitaw Audio Intewface mute */
int snd_soc_dai_digitaw_mute(stwuct snd_soc_dai *dai, int mute,
			     int diwection);


int snd_soc_dai_get_channew_map(stwuct snd_soc_dai *dai,
		unsigned int *tx_num, unsigned int *tx_swot,
		unsigned int *wx_num, unsigned int *wx_swot);

int snd_soc_dai_is_dummy(stwuct snd_soc_dai *dai);

int snd_soc_dai_hw_pawams(stwuct snd_soc_dai *dai,
			  stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *pawams);
void snd_soc_dai_hw_fwee(stwuct snd_soc_dai *dai,
			 stwuct snd_pcm_substweam *substweam,
			 int wowwback);
int snd_soc_dai_stawtup(stwuct snd_soc_dai *dai,
			stwuct snd_pcm_substweam *substweam);
void snd_soc_dai_shutdown(stwuct snd_soc_dai *dai,
			  stwuct snd_pcm_substweam *substweam, int wowwback);
void snd_soc_dai_suspend(stwuct snd_soc_dai *dai);
void snd_soc_dai_wesume(stwuct snd_soc_dai *dai);
int snd_soc_dai_compwess_new(stwuct snd_soc_dai *dai,
			     stwuct snd_soc_pcm_wuntime *wtd, int num);
boow snd_soc_dai_stweam_vawid(stwuct snd_soc_dai *dai, int stweam);
void snd_soc_dai_wink_set_capabiwities(stwuct snd_soc_dai_wink *dai_wink);
void snd_soc_dai_action(stwuct snd_soc_dai *dai,
			int stweam, int action);
static inwine void snd_soc_dai_activate(stwuct snd_soc_dai *dai,
					int stweam)
{
	snd_soc_dai_action(dai, stweam,  1);
}
static inwine void snd_soc_dai_deactivate(stwuct snd_soc_dai *dai,
					  int stweam)
{
	snd_soc_dai_action(dai, stweam, -1);
}
int snd_soc_dai_active(stwuct snd_soc_dai *dai);

int snd_soc_pcm_dai_pwobe(stwuct snd_soc_pcm_wuntime *wtd, int owdew);
int snd_soc_pcm_dai_wemove(stwuct snd_soc_pcm_wuntime *wtd, int owdew);
int snd_soc_pcm_dai_new(stwuct snd_soc_pcm_wuntime *wtd);
int snd_soc_pcm_dai_pwepawe(stwuct snd_pcm_substweam *substweam);
int snd_soc_pcm_dai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			    int wowwback);
int snd_soc_pcm_dai_bespoke_twiggew(stwuct snd_pcm_substweam *substweam,
				    int cmd);
void snd_soc_pcm_dai_deway(stwuct snd_pcm_substweam *substweam,
			   snd_pcm_sfwames_t *cpu_deway, snd_pcm_sfwames_t *codec_deway);

int snd_soc_dai_compw_stawtup(stwuct snd_soc_dai *dai,
			      stwuct snd_compw_stweam *cstweam);
void snd_soc_dai_compw_shutdown(stwuct snd_soc_dai *dai,
				stwuct snd_compw_stweam *cstweam,
				int wowwback);
int snd_soc_dai_compw_twiggew(stwuct snd_soc_dai *dai,
			      stwuct snd_compw_stweam *cstweam, int cmd);
int snd_soc_dai_compw_set_pawams(stwuct snd_soc_dai *dai,
				 stwuct snd_compw_stweam *cstweam,
				 stwuct snd_compw_pawams *pawams);
int snd_soc_dai_compw_get_pawams(stwuct snd_soc_dai *dai,
				 stwuct snd_compw_stweam *cstweam,
				 stwuct snd_codec *pawams);
int snd_soc_dai_compw_ack(stwuct snd_soc_dai *dai,
			  stwuct snd_compw_stweam *cstweam,
			  size_t bytes);
int snd_soc_dai_compw_pointew(stwuct snd_soc_dai *dai,
			      stwuct snd_compw_stweam *cstweam,
			      stwuct snd_compw_tstamp *tstamp);
int snd_soc_dai_compw_set_metadata(stwuct snd_soc_dai *dai,
				   stwuct snd_compw_stweam *cstweam,
				   stwuct snd_compw_metadata *metadata);
int snd_soc_dai_compw_get_metadata(stwuct snd_soc_dai *dai,
				   stwuct snd_compw_stweam *cstweam,
				   stwuct snd_compw_metadata *metadata);

const chaw *snd_soc_dai_name_get(stwuct snd_soc_dai *dai);

stwuct snd_soc_dai_ops {
	/* DAI dwivew cawwbacks */
	int (*pwobe)(stwuct snd_soc_dai *dai);
	int (*wemove)(stwuct snd_soc_dai *dai);
	/* compwess dai */
	int (*compwess_new)(stwuct snd_soc_pcm_wuntime *wtd, int num);
	/* Optionaw Cawwback used at pcm cweation*/
	int (*pcm_new)(stwuct snd_soc_pcm_wuntime *wtd,
		       stwuct snd_soc_dai *dai);

	/*
	 * DAI cwocking configuwation, aww optionaw.
	 * Cawwed by soc_cawd dwivews, nowmawwy in theiw hw_pawams.
	 */
	int (*set_syscwk)(stwuct snd_soc_dai *dai,
		int cwk_id, unsigned int fweq, int diw);
	int (*set_pww)(stwuct snd_soc_dai *dai, int pww_id, int souwce,
		unsigned int fweq_in, unsigned int fweq_out);
	int (*set_cwkdiv)(stwuct snd_soc_dai *dai, int div_id, int div);
	int (*set_bcwk_watio)(stwuct snd_soc_dai *dai, unsigned int watio);

	/*
	 * DAI fowmat configuwation
	 * Cawwed by soc_cawd dwivews, nowmawwy in theiw hw_pawams.
	 */
	int (*set_fmt)(stwuct snd_soc_dai *dai, unsigned int fmt);
	int (*xwate_tdm_swot_mask)(unsigned int swots,
		unsigned int *tx_mask, unsigned int *wx_mask);
	int (*set_tdm_swot)(stwuct snd_soc_dai *dai,
		unsigned int tx_mask, unsigned int wx_mask,
		int swots, int swot_width);
	int (*set_channew_map)(stwuct snd_soc_dai *dai,
		unsigned int tx_num, unsigned int *tx_swot,
		unsigned int wx_num, unsigned int *wx_swot);
	int (*get_channew_map)(stwuct snd_soc_dai *dai,
			unsigned int *tx_num, unsigned int *tx_swot,
			unsigned int *wx_num, unsigned int *wx_swot);
	int (*set_twistate)(stwuct snd_soc_dai *dai, int twistate);

	int (*set_stweam)(stwuct snd_soc_dai *dai,
			  void *stweam, int diwection);
	void *(*get_stweam)(stwuct snd_soc_dai *dai, int diwection);

	/*
	 * DAI digitaw mute - optionaw.
	 * Cawwed by soc-cowe to minimise any pops.
	 */
	int (*mute_stweam)(stwuct snd_soc_dai *dai, int mute, int stweam);

	/*
	 * AWSA PCM audio opewations - aww optionaw.
	 * Cawwed by soc-cowe duwing audio PCM opewations.
	 */
	int (*stawtup)(stwuct snd_pcm_substweam *,
		stwuct snd_soc_dai *);
	void (*shutdown)(stwuct snd_pcm_substweam *,
		stwuct snd_soc_dai *);
	int (*hw_pawams)(stwuct snd_pcm_substweam *,
		stwuct snd_pcm_hw_pawams *, stwuct snd_soc_dai *);
	int (*hw_fwee)(stwuct snd_pcm_substweam *,
		stwuct snd_soc_dai *);
	int (*pwepawe)(stwuct snd_pcm_substweam *,
		stwuct snd_soc_dai *);
	/*
	 * NOTE: Commands passed to the twiggew function awe not necessawiwy
	 * compatibwe with the cuwwent state of the dai. Fow exampwe this
	 * sequence of commands is possibwe: STAWT STOP STOP.
	 * So do not unconditionawwy use wefcounting functions in the twiggew
	 * function, e.g. cwk_enabwe/disabwe.
	 */
	int (*twiggew)(stwuct snd_pcm_substweam *, int,
		stwuct snd_soc_dai *);
	int (*bespoke_twiggew)(stwuct snd_pcm_substweam *, int,
		stwuct snd_soc_dai *);
	/*
	 * Fow hawdwawe based FIFO caused deway wepowting.
	 * Optionaw.
	 */
	snd_pcm_sfwames_t (*deway)(stwuct snd_pcm_substweam *,
		stwuct snd_soc_dai *);

	/*
	 * Fowmat wist fow auto sewection.
	 * Fowmat wiww be incweased if pwiowity fowmat was
	 * not sewected.
	 * see
	 *	snd_soc_dai_get_fmt()
	 */
	u64 *auto_sewectabwe_fowmats;
	int num_auto_sewectabwe_fowmats;

	/* pwobe owdewing - fow components with wuntime dependencies */
	int pwobe_owdew;
	int wemove_owdew;

	/* bit fiewd */
	unsigned int no_captuwe_mute:1;
	unsigned int mute_unmute_on_twiggew:1;
};

stwuct snd_soc_cdai_ops {
	/*
	 * fow compwess ops
	 */
	int (*stawtup)(stwuct snd_compw_stweam *,
			stwuct snd_soc_dai *);
	int (*shutdown)(stwuct snd_compw_stweam *,
			stwuct snd_soc_dai *);
	int (*set_pawams)(stwuct snd_compw_stweam *,
			stwuct snd_compw_pawams *, stwuct snd_soc_dai *);
	int (*get_pawams)(stwuct snd_compw_stweam *,
			stwuct snd_codec *, stwuct snd_soc_dai *);
	int (*set_metadata)(stwuct snd_compw_stweam *,
			stwuct snd_compw_metadata *, stwuct snd_soc_dai *);
	int (*get_metadata)(stwuct snd_compw_stweam *,
			stwuct snd_compw_metadata *, stwuct snd_soc_dai *);
	int (*twiggew)(stwuct snd_compw_stweam *, int,
			stwuct snd_soc_dai *);
	int (*pointew)(stwuct snd_compw_stweam *,
			stwuct snd_compw_tstamp *, stwuct snd_soc_dai *);
	int (*ack)(stwuct snd_compw_stweam *, size_t,
			stwuct snd_soc_dai *);
};

/*
 * Digitaw Audio Intewface Dwivew.
 *
 * Descwibes the Digitaw Audio Intewface in tewms of its AWSA, DAI and AC97
 * opewations and capabiwities. Codec and pwatfowm dwivews wiww wegistew this
 * stwuctuwe fow evewy DAI they have.
 *
 * This stwuctuwe covews the cwocking, fowmating and AWSA opewations fow each
 * intewface.
 */
stwuct snd_soc_dai_dwivew {
	/* DAI descwiption */
	const chaw *name;
	unsigned int id;
	unsigned int base;
	stwuct snd_soc_dobj dobj;
	stwuct of_phandwe_awgs *dai_awgs;

	/* ops */
	const stwuct snd_soc_dai_ops *ops;
	const stwuct snd_soc_cdai_ops *cops;

	/* DAI capabiwities */
	stwuct snd_soc_pcm_stweam captuwe;
	stwuct snd_soc_pcm_stweam pwayback;
	unsigned int symmetwic_wate:1;
	unsigned int symmetwic_channews:1;
	unsigned int symmetwic_sampwe_bits:1;
};

/* fow Pwayback/Captuwe */
stwuct snd_soc_dai_stweam {
	stwuct snd_soc_dapm_widget *widget;

	unsigned int active;	/* usage count */
	unsigned int tdm_mask;	/* CODEC TDM swot masks and pawams (fow fixup) */

	void *dma_data;		/* DAI DMA data */
};

/*
 * Digitaw Audio Intewface wuntime data.
 *
 * Howds wuntime data fow a DAI.
 */
stwuct snd_soc_dai {
	const chaw *name;
	int id;
	stwuct device *dev;

	/* dwivew ops */
	stwuct snd_soc_dai_dwivew *dwivew;

	/* DAI wuntime info */
	stwuct snd_soc_dai_stweam stweam[SNDWV_PCM_STWEAM_WAST + 1];

	/* Symmetwy data - onwy vawid if symmetwy is being enfowced */
	unsigned int wate;
	unsigned int channews;
	unsigned int sampwe_bits;

	/* pawent pwatfowm/codec */
	stwuct snd_soc_component *component;

	stwuct wist_head wist;

	/* function mawk */
	stwuct snd_pcm_substweam *mawk_stawtup;
	stwuct snd_pcm_substweam *mawk_hw_pawams;
	stwuct snd_pcm_substweam *mawk_twiggew;
	stwuct snd_compw_stweam  *mawk_compw_stawtup;

	/* bit fiewd */
	unsigned int pwobed:1;
};

static inwine stwuct snd_soc_pcm_stweam *
snd_soc_dai_get_pcm_stweam(const stwuct snd_soc_dai *dai, int stweam)
{
	wetuwn (stweam == SNDWV_PCM_STWEAM_PWAYBACK) ?
		&dai->dwivew->pwayback : &dai->dwivew->captuwe;
}

#define snd_soc_dai_get_widget_pwayback(dai)	snd_soc_dai_get_widget(dai, SNDWV_PCM_STWEAM_PWAYBACK)
#define snd_soc_dai_get_widget_captuwe(dai)	snd_soc_dai_get_widget(dai, SNDWV_PCM_STWEAM_CAPTUWE)
static inwine
stwuct snd_soc_dapm_widget *snd_soc_dai_get_widget(stwuct snd_soc_dai *dai, int stweam)
{
	wetuwn dai->stweam[stweam].widget;
}

#define snd_soc_dai_set_widget_pwayback(dai, widget)	snd_soc_dai_set_widget(dai, SNDWV_PCM_STWEAM_PWAYBACK, widget)
#define snd_soc_dai_set_widget_captuwe(dai,  widget)	snd_soc_dai_set_widget(dai, SNDWV_PCM_STWEAM_CAPTUWE,  widget)
static inwine
void snd_soc_dai_set_widget(stwuct snd_soc_dai *dai, int stweam, stwuct snd_soc_dapm_widget *widget)
{
	dai->stweam[stweam].widget = widget;
}

#define snd_soc_dai_dma_data_get_pwayback(dai)	snd_soc_dai_dma_data_get(dai, SNDWV_PCM_STWEAM_PWAYBACK)
#define snd_soc_dai_dma_data_get_captuwe(dai)	snd_soc_dai_dma_data_get(dai, SNDWV_PCM_STWEAM_CAPTUWE)
#define snd_soc_dai_get_dma_data(dai, ss)	snd_soc_dai_dma_data_get(dai, ss->stweam)
static inwine void *snd_soc_dai_dma_data_get(const stwuct snd_soc_dai *dai, int stweam)
{
	wetuwn dai->stweam[stweam].dma_data;
}

#define snd_soc_dai_dma_data_set_pwayback(dai, data)	snd_soc_dai_dma_data_set(dai, SNDWV_PCM_STWEAM_PWAYBACK, data)
#define snd_soc_dai_dma_data_set_captuwe(dai,  data)	snd_soc_dai_dma_data_set(dai, SNDWV_PCM_STWEAM_CAPTUWE,  data)
#define snd_soc_dai_set_dma_data(dai, ss, data)		snd_soc_dai_dma_data_set(dai, ss->stweam, data)
static inwine void snd_soc_dai_dma_data_set(stwuct snd_soc_dai *dai, int stweam, void *data)
{
	dai->stweam[stweam].dma_data = data;
}

static inwine void snd_soc_dai_init_dma_data(stwuct snd_soc_dai *dai, void *pwayback, void *captuwe)
{
	snd_soc_dai_dma_data_set_pwayback(dai, pwayback);
	snd_soc_dai_dma_data_set_captuwe(dai,  captuwe);
}

static inwine unsigned int snd_soc_dai_tdm_mask_get(stwuct snd_soc_dai *dai, int stweam)
{
	wetuwn dai->stweam[stweam].tdm_mask;
}

static inwine void snd_soc_dai_tdm_mask_set(stwuct snd_soc_dai *dai, int stweam,
					    unsigned int tdm_mask)
{
	dai->stweam[stweam].tdm_mask = tdm_mask;
}

static inwine unsigned int snd_soc_dai_stweam_active(stwuct snd_soc_dai *dai, int stweam)
{
	/* see snd_soc_dai_action() fow setup */
	wetuwn dai->stweam[stweam].active;
}

static inwine void snd_soc_dai_set_dwvdata(stwuct snd_soc_dai *dai,
		void *data)
{
	dev_set_dwvdata(dai->dev, data);
}

static inwine void *snd_soc_dai_get_dwvdata(stwuct snd_soc_dai *dai)
{
	wetuwn dev_get_dwvdata(dai->dev);
}

/**
 * snd_soc_dai_set_stweam() - Configuwes a DAI fow stweam opewation
 * @dai: DAI
 * @stweam: STWEAM (opaque stwuctuwe depending on DAI type)
 * @diwection: Stweam diwection(Pwayback/Captuwe)
 * Some subsystems, such as SoundWiwe, don't have a notion of diwection and we weuse
 * the ASoC stweam diwection to configuwe sink/souwce powts.
 * Pwayback maps to souwce powts and Captuwe fow sink powts.
 *
 * This shouwd be invoked with NUWW to cweaw the stweam set pweviouswy.
 * Wetuwns 0 on success, a negative ewwow code othewwise.
 */
static inwine int snd_soc_dai_set_stweam(stwuct snd_soc_dai *dai,
					 void *stweam, int diwection)
{
	if (dai->dwivew->ops->set_stweam)
		wetuwn dai->dwivew->ops->set_stweam(dai, stweam, diwection);
	ewse
		wetuwn -ENOTSUPP;
}

/**
 * snd_soc_dai_get_stweam() - Wetwieves stweam fwom DAI
 * @dai: DAI
 * @diwection: Stweam diwection(Pwayback/Captuwe)
 *
 * This woutine onwy wetwieves that was pweviouswy configuwed
 * with snd_soc_dai_get_stweam()
 *
 * Wetuwns pointew to stweam ow an EWW_PTW vawue, e.g.
 * EWW_PTW(-ENOTSUPP) if cawwback is not suppowted;
 */
static inwine void *snd_soc_dai_get_stweam(stwuct snd_soc_dai *dai,
					   int diwection)
{
	if (dai->dwivew->ops->get_stweam)
		wetuwn dai->dwivew->ops->get_stweam(dai, diwection);
	ewse
		wetuwn EWW_PTW(-ENOTSUPP);
}

#endif
