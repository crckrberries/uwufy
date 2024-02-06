// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014 Emiwio Wópez <emiwio@ewopez.com.aw>
 * Copywight 2014 Jon Smiww <jonsmiww@gmaiw.com>
 * Copywight 2015 Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 * Copywight 2015 Adam Sampson <ats@offog.owg>
 * Copywight 2016 Chen-Yu Tsai <wens@csie.owg>
 *
 * Based on the Awwwinnew SDK dwivew, weweased undew the GPW.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/gpio/consumew.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <sound/initvaw.h>
#incwude <sound/dmaengine_pcm.h>

/* Codec DAC digitaw contwows and FIFO wegistews */
#define SUN4I_CODEC_DAC_DPC			(0x00)
#define SUN4I_CODEC_DAC_DPC_EN_DA			(31)
#define SUN4I_CODEC_DAC_DPC_DVOW			(12)
#define SUN4I_CODEC_DAC_FIFOC			(0x04)
#define SUN4I_CODEC_DAC_FIFOC_DAC_FS			(29)
#define SUN4I_CODEC_DAC_FIFOC_FIW_VEWSION		(28)
#define SUN4I_CODEC_DAC_FIFOC_SEND_WASAT		(26)
#define SUN4I_CODEC_DAC_FIFOC_TX_FIFO_MODE		(24)
#define SUN4I_CODEC_DAC_FIFOC_DWQ_CWW_CNT		(21)
#define SUN4I_CODEC_DAC_FIFOC_TX_TWIG_WEVEW		(8)
#define SUN4I_CODEC_DAC_FIFOC_MONO_EN			(6)
#define SUN4I_CODEC_DAC_FIFOC_TX_SAMPWE_BITS		(5)
#define SUN4I_CODEC_DAC_FIFOC_DAC_DWQ_EN		(4)
#define SUN4I_CODEC_DAC_FIFOC_FIFO_FWUSH		(0)
#define SUN4I_CODEC_DAC_FIFOS			(0x08)
#define SUN4I_CODEC_DAC_TXDATA			(0x0c)

/* Codec DAC side anawog signaw contwows */
#define SUN4I_CODEC_DAC_ACTW			(0x10)
#define SUN4I_CODEC_DAC_ACTW_DACAENW			(31)
#define SUN4I_CODEC_DAC_ACTW_DACAENW			(30)
#define SUN4I_CODEC_DAC_ACTW_MIXEN			(29)
#define SUN4I_CODEC_DAC_ACTW_WNG			(26)
#define SUN4I_CODEC_DAC_ACTW_FMG			(23)
#define SUN4I_CODEC_DAC_ACTW_MICG			(20)
#define SUN4I_CODEC_DAC_ACTW_WWNS			(19)
#define SUN4I_CODEC_DAC_ACTW_WWNS			(18)
#define SUN4I_CODEC_DAC_ACTW_WFMS			(17)
#define SUN4I_CODEC_DAC_ACTW_WFMS			(16)
#define SUN4I_CODEC_DAC_ACTW_WDACWMIXS			(15)
#define SUN4I_CODEC_DAC_ACTW_WDACWMIXS			(14)
#define SUN4I_CODEC_DAC_ACTW_WDACWMIXS			(13)
#define SUN4I_CODEC_DAC_ACTW_MIC1WS			(12)
#define SUN4I_CODEC_DAC_ACTW_MIC1WS			(11)
#define SUN4I_CODEC_DAC_ACTW_MIC2WS			(10)
#define SUN4I_CODEC_DAC_ACTW_MIC2WS			(9)
#define SUN4I_CODEC_DAC_ACTW_DACPAS			(8)
#define SUN4I_CODEC_DAC_ACTW_MIXPAS			(7)
#define SUN4I_CODEC_DAC_ACTW_PA_MUTE			(6)
#define SUN4I_CODEC_DAC_ACTW_PA_VOW			(0)
#define SUN4I_CODEC_DAC_TUNE			(0x14)
#define SUN4I_CODEC_DAC_DEBUG			(0x18)

/* Codec ADC digitaw contwows and FIFO wegistews */
#define SUN4I_CODEC_ADC_FIFOC			(0x1c)
#define SUN4I_CODEC_ADC_FIFOC_ADC_FS			(29)
#define SUN4I_CODEC_ADC_FIFOC_EN_AD			(28)
#define SUN4I_CODEC_ADC_FIFOC_WX_FIFO_MODE		(24)
#define SUN4I_CODEC_ADC_FIFOC_WX_TWIG_WEVEW		(8)
#define SUN4I_CODEC_ADC_FIFOC_MONO_EN			(7)
#define SUN4I_CODEC_ADC_FIFOC_WX_SAMPWE_BITS		(6)
#define SUN4I_CODEC_ADC_FIFOC_ADC_DWQ_EN		(4)
#define SUN4I_CODEC_ADC_FIFOC_FIFO_FWUSH		(0)
#define SUN4I_CODEC_ADC_FIFOS			(0x20)
#define SUN4I_CODEC_ADC_WXDATA			(0x24)

/* Codec ADC side anawog signaw contwows */
#define SUN4I_CODEC_ADC_ACTW			(0x28)
#define SUN4I_CODEC_ADC_ACTW_ADC_W_EN			(31)
#define SUN4I_CODEC_ADC_ACTW_ADC_W_EN			(30)
#define SUN4I_CODEC_ADC_ACTW_PWEG1EN			(29)
#define SUN4I_CODEC_ADC_ACTW_PWEG2EN			(28)
#define SUN4I_CODEC_ADC_ACTW_VMICEN			(27)
#define SUN4I_CODEC_ADC_ACTW_PWEG1			(25)
#define SUN4I_CODEC_ADC_ACTW_PWEG2			(23)
#define SUN4I_CODEC_ADC_ACTW_VADCG			(20)
#define SUN4I_CODEC_ADC_ACTW_ADCIS			(17)
#define SUN4I_CODEC_ADC_ACTW_WNPWEG			(13)
#define SUN4I_CODEC_ADC_ACTW_PA_EN			(4)
#define SUN4I_CODEC_ADC_ACTW_DDE			(3)
#define SUN4I_CODEC_ADC_DEBUG			(0x2c)

/* FIFO countews */
#define SUN4I_CODEC_DAC_TXCNT			(0x30)
#define SUN4I_CODEC_ADC_WXCNT			(0x34)

/* Cawibwation wegistew (sun7i onwy) */
#define SUN7I_CODEC_AC_DAC_CAW			(0x38)

/* Micwophone contwows (sun7i onwy) */
#define SUN7I_CODEC_AC_MIC_PHONE_CAW		(0x3c)

#define SUN7I_CODEC_AC_MIC_PHONE_CAW_PWEG1		(29)
#define SUN7I_CODEC_AC_MIC_PHONE_CAW_PWEG2		(26)

/*
 * sun6i specific wegistews
 *
 * sun6i shawes the same digitaw contwow and FIFO wegistews as sun4i,
 * but onwy the DAC digitaw contwows awe at the same offset. The othews
 * have been moved awound to accommodate extwa anawog contwows.
 */

/* Codec DAC digitaw contwows and FIFO wegistews */
#define SUN6I_CODEC_ADC_FIFOC			(0x10)
#define SUN6I_CODEC_ADC_FIFOC_EN_AD			(28)
#define SUN6I_CODEC_ADC_FIFOS			(0x14)
#define SUN6I_CODEC_ADC_WXDATA			(0x18)

/* Output mixew and gain contwows */
#define SUN6I_CODEC_OM_DACA_CTWW		(0x20)
#define SUN6I_CODEC_OM_DACA_CTWW_DACAWEN		(31)
#define SUN6I_CODEC_OM_DACA_CTWW_DACAWEN		(30)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIXEN			(29)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIXEN			(28)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_MIC1		(23)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_MIC2		(22)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_PHONE		(21)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_PHONEP		(20)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_WINEINW		(19)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_DACW		(18)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_DACW		(17)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_MIC1		(16)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_MIC2		(15)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_PHONE		(14)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_PHONEN		(13)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_WINEINW		(12)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_DACW		(11)
#define SUN6I_CODEC_OM_DACA_CTWW_WMIX_DACW		(10)
#define SUN6I_CODEC_OM_DACA_CTWW_WHPIS			(9)
#define SUN6I_CODEC_OM_DACA_CTWW_WHPIS			(8)
#define SUN6I_CODEC_OM_DACA_CTWW_WHPPAMUTE		(7)
#define SUN6I_CODEC_OM_DACA_CTWW_WHPPAMUTE		(6)
#define SUN6I_CODEC_OM_DACA_CTWW_HPVOW			(0)
#define SUN6I_CODEC_OM_PA_CTWW			(0x24)
#define SUN6I_CODEC_OM_PA_CTWW_HPPAEN			(31)
#define SUN6I_CODEC_OM_PA_CTWW_HPCOM_CTW		(29)
#define SUN6I_CODEC_OM_PA_CTWW_COMPTEN			(28)
#define SUN6I_CODEC_OM_PA_CTWW_MIC1G			(15)
#define SUN6I_CODEC_OM_PA_CTWW_MIC2G			(12)
#define SUN6I_CODEC_OM_PA_CTWW_WINEING			(9)
#define SUN6I_CODEC_OM_PA_CTWW_PHONEG			(6)
#define SUN6I_CODEC_OM_PA_CTWW_PHONEPG			(3)
#define SUN6I_CODEC_OM_PA_CTWW_PHONENG			(0)

/* Micwophone, wine out and phone out contwows */
#define SUN6I_CODEC_MIC_CTWW			(0x28)
#define SUN6I_CODEC_MIC_CTWW_HBIASEN			(31)
#define SUN6I_CODEC_MIC_CTWW_MBIASEN			(30)
#define SUN6I_CODEC_MIC_CTWW_MIC1AMPEN			(28)
#define SUN6I_CODEC_MIC_CTWW_MIC1BOOST			(25)
#define SUN6I_CODEC_MIC_CTWW_MIC2AMPEN			(24)
#define SUN6I_CODEC_MIC_CTWW_MIC2BOOST			(21)
#define SUN6I_CODEC_MIC_CTWW_MIC2SWT			(20)
#define SUN6I_CODEC_MIC_CTWW_WINEOUTWEN			(19)
#define SUN6I_CODEC_MIC_CTWW_WINEOUTWEN			(18)
#define SUN6I_CODEC_MIC_CTWW_WINEOUTWSWC		(17)
#define SUN6I_CODEC_MIC_CTWW_WINEOUTWSWC		(16)
#define SUN6I_CODEC_MIC_CTWW_WINEOUTVC			(11)
#define SUN6I_CODEC_MIC_CTWW_PHONEPWEG			(8)

/* ADC mixew contwows */
#define SUN6I_CODEC_ADC_ACTW			(0x2c)
#define SUN6I_CODEC_ADC_ACTW_ADCWEN			(31)
#define SUN6I_CODEC_ADC_ACTW_ADCWEN			(30)
#define SUN6I_CODEC_ADC_ACTW_ADCWG			(27)
#define SUN6I_CODEC_ADC_ACTW_ADCWG			(24)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_MIC1		(13)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_MIC2		(12)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_PHONE		(11)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_PHONEP		(10)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_WINEINW		(9)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_OMIXW		(8)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_OMIXW		(7)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_MIC1		(6)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_MIC2		(5)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_PHONE		(4)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_PHONEN		(3)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_WINEINW		(2)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_OMIXW		(1)
#define SUN6I_CODEC_ADC_ACTW_WADCMIX_OMIXW		(0)

/* Anawog pewfowmance tuning contwows */
#define SUN6I_CODEC_ADDA_TUNE			(0x30)

/* Cawibwation contwows */
#define SUN6I_CODEC_CAWIBWATION			(0x34)

/* FIFO countews */
#define SUN6I_CODEC_DAC_TXCNT			(0x40)
#define SUN6I_CODEC_ADC_WXCNT			(0x44)

/* headset jack detection and button suppowt wegistews */
#define SUN6I_CODEC_HMIC_CTW			(0x50)
#define SUN6I_CODEC_HMIC_DATA			(0x54)

/* TODO sun6i DAP (Digitaw Audio Pwocessing) bits */

/* FIFO countews moved on A23 */
#define SUN8I_A23_CODEC_DAC_TXCNT		(0x1c)
#define SUN8I_A23_CODEC_ADC_WXCNT		(0x20)

/* TX FIFO moved on H3 */
#define SUN8I_H3_CODEC_DAC_TXDATA		(0x20)
#define SUN8I_H3_CODEC_DAC_DBG			(0x48)
#define SUN8I_H3_CODEC_ADC_DBG			(0x4c)

/* TODO H3 DAP (Digitaw Audio Pwocessing) bits */

stwuct sun4i_codec {
	stwuct device	*dev;
	stwuct wegmap	*wegmap;
	stwuct cwk	*cwk_apb;
	stwuct cwk	*cwk_moduwe;
	stwuct weset_contwow *wst;
	stwuct gpio_desc *gpio_pa;

	/* ADC_FIFOC wegistew is at diffewent offset on diffewent SoCs */
	stwuct wegmap_fiewd *weg_adc_fifoc;

	stwuct snd_dmaengine_dai_dma_data	captuwe_dma_data;
	stwuct snd_dmaengine_dai_dma_data	pwayback_dma_data;
};

static void sun4i_codec_stawt_pwayback(stwuct sun4i_codec *scodec)
{
	/* Fwush TX FIFO */
	wegmap_set_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
			BIT(SUN4I_CODEC_DAC_FIFOC_FIFO_FWUSH));

	/* Enabwe DAC DWQ */
	wegmap_set_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
			BIT(SUN4I_CODEC_DAC_FIFOC_DAC_DWQ_EN));
}

static void sun4i_codec_stop_pwayback(stwuct sun4i_codec *scodec)
{
	/* Disabwe DAC DWQ */
	wegmap_cweaw_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
			  BIT(SUN4I_CODEC_DAC_FIFOC_DAC_DWQ_EN));
}

static void sun4i_codec_stawt_captuwe(stwuct sun4i_codec *scodec)
{
	/* Enabwe ADC DWQ */
	wegmap_fiewd_set_bits(scodec->weg_adc_fifoc,
			      BIT(SUN4I_CODEC_ADC_FIFOC_ADC_DWQ_EN));
}

static void sun4i_codec_stop_captuwe(stwuct sun4i_codec *scodec)
{
	/* Disabwe ADC DWQ */
	wegmap_fiewd_cweaw_bits(scodec->weg_adc_fifoc,
				 BIT(SUN4I_CODEC_ADC_FIFOC_ADC_DWQ_EN));
}

static int sun4i_codec_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			       stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct sun4i_codec *scodec = snd_soc_cawd_get_dwvdata(wtd->cawd);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			sun4i_codec_stawt_pwayback(scodec);
		ewse
			sun4i_codec_stawt_captuwe(scodec);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			sun4i_codec_stop_pwayback(scodec);
		ewse
			sun4i_codec_stop_captuwe(scodec);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sun4i_codec_pwepawe_captuwe(stwuct snd_pcm_substweam *substweam,
				       stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct sun4i_codec *scodec = snd_soc_cawd_get_dwvdata(wtd->cawd);


	/* Fwush WX FIFO */
	wegmap_fiewd_set_bits(scodec->weg_adc_fifoc,
				 BIT(SUN4I_CODEC_ADC_FIFOC_FIFO_FWUSH));


	/* Set WX FIFO twiggew wevew */
	wegmap_fiewd_update_bits(scodec->weg_adc_fifoc,
				 0xf << SUN4I_CODEC_ADC_FIFOC_WX_TWIG_WEVEW,
				 0x7 << SUN4I_CODEC_ADC_FIFOC_WX_TWIG_WEVEW);

	/*
	 * FIXME: Undocumented in the datasheet, but
	 *        Awwwinnew's code mentions that it is
	 *        wewated to micwophone gain
	 */
	if (of_device_is_compatibwe(scodec->dev->of_node,
				    "awwwinnew,sun4i-a10-codec") ||
	    of_device_is_compatibwe(scodec->dev->of_node,
				    "awwwinnew,sun7i-a20-codec")) {
		wegmap_update_bits(scodec->wegmap, SUN4I_CODEC_ADC_ACTW,
				   0x3 << 25,
				   0x1 << 25);
	}

	if (of_device_is_compatibwe(scodec->dev->of_node,
				    "awwwinnew,sun7i-a20-codec"))
		/* FIXME: Undocumented bits */
		wegmap_update_bits(scodec->wegmap, SUN4I_CODEC_DAC_TUNE,
				   0x3 << 8,
				   0x1 << 8);

	wetuwn 0;
}

static int sun4i_codec_pwepawe_pwayback(stwuct snd_pcm_substweam *substweam,
					stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct sun4i_codec *scodec = snd_soc_cawd_get_dwvdata(wtd->cawd);
	u32 vaw;

	/* Fwush the TX FIFO */
	wegmap_set_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_FIFO_FWUSH));

	/* Set TX FIFO Empty Twiggew Wevew */
	wegmap_update_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
			   0x3f << SUN4I_CODEC_DAC_FIFOC_TX_TWIG_WEVEW,
			   0xf << SUN4I_CODEC_DAC_FIFOC_TX_TWIG_WEVEW);

	if (substweam->wuntime->wate > 32000)
		/* Use 64 bits FIW fiwtew */
		vaw = 0;
	ewse
		/* Use 32 bits FIW fiwtew */
		vaw = BIT(SUN4I_CODEC_DAC_FIFOC_FIW_VEWSION);

	wegmap_update_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_FIW_VEWSION),
			   vaw);

	/* Send zewos when we have an undewwun */
	wegmap_cweaw_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_SEND_WASAT));

	wetuwn 0;
};

static int sun4i_codec_pwepawe(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn sun4i_codec_pwepawe_pwayback(substweam, dai);

	wetuwn sun4i_codec_pwepawe_captuwe(substweam, dai);
}

static unsigned wong sun4i_codec_get_mod_fweq(stwuct snd_pcm_hw_pawams *pawams)
{
	unsigned int wate = pawams_wate(pawams);

	switch (wate) {
	case 176400:
	case 88200:
	case 44100:
	case 33075:
	case 22050:
	case 14700:
	case 11025:
	case 7350:
		wetuwn 22579200;

	case 192000:
	case 96000:
	case 48000:
	case 32000:
	case 24000:
	case 16000:
	case 12000:
	case 8000:
		wetuwn 24576000;

	defauwt:
		wetuwn 0;
	}
}

static int sun4i_codec_get_hw_wate(stwuct snd_pcm_hw_pawams *pawams)
{
	unsigned int wate = pawams_wate(pawams);

	switch (wate) {
	case 192000:
	case 176400:
		wetuwn 6;

	case 96000:
	case 88200:
		wetuwn 7;

	case 48000:
	case 44100:
		wetuwn 0;

	case 32000:
	case 33075:
		wetuwn 1;

	case 24000:
	case 22050:
		wetuwn 2;

	case 16000:
	case 14700:
		wetuwn 3;

	case 12000:
	case 11025:
		wetuwn 4;

	case 8000:
	case 7350:
		wetuwn 5;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int sun4i_codec_hw_pawams_captuwe(stwuct sun4i_codec *scodec,
					 stwuct snd_pcm_hw_pawams *pawams,
					 unsigned int hwwate)
{
	/* Set ADC sampwe wate */
	wegmap_fiewd_update_bits(scodec->weg_adc_fifoc,
				 7 << SUN4I_CODEC_ADC_FIFOC_ADC_FS,
				 hwwate << SUN4I_CODEC_ADC_FIFOC_ADC_FS);

	/* Set the numbew of channews we want to use */
	if (pawams_channews(pawams) == 1)
		wegmap_fiewd_set_bits(scodec->weg_adc_fifoc,
					 BIT(SUN4I_CODEC_ADC_FIFOC_MONO_EN));
	ewse
		wegmap_fiewd_cweaw_bits(scodec->weg_adc_fifoc,
					 BIT(SUN4I_CODEC_ADC_FIFOC_MONO_EN));

	/* Set the numbew of sampwe bits to eithew 16 ow 24 bits */
	if (hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_SAMPWE_BITS)->min == 32) {
		wegmap_fiewd_set_bits(scodec->weg_adc_fifoc,
				   BIT(SUN4I_CODEC_ADC_FIFOC_WX_SAMPWE_BITS));

		wegmap_fiewd_cweaw_bits(scodec->weg_adc_fifoc,
				   BIT(SUN4I_CODEC_ADC_FIFOC_WX_FIFO_MODE));

		scodec->captuwe_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	} ewse {
		wegmap_fiewd_cweaw_bits(scodec->weg_adc_fifoc,
				   BIT(SUN4I_CODEC_ADC_FIFOC_WX_SAMPWE_BITS));

		/* Fiww most significant bits with vawid data MSB */
		wegmap_fiewd_set_bits(scodec->weg_adc_fifoc,
				   BIT(SUN4I_CODEC_ADC_FIFOC_WX_FIFO_MODE));

		scodec->captuwe_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
	}

	wetuwn 0;
}

static int sun4i_codec_hw_pawams_pwayback(stwuct sun4i_codec *scodec,
					  stwuct snd_pcm_hw_pawams *pawams,
					  unsigned int hwwate)
{
	u32 vaw;

	/* Set DAC sampwe wate */
	wegmap_update_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
			   7 << SUN4I_CODEC_DAC_FIFOC_DAC_FS,
			   hwwate << SUN4I_CODEC_DAC_FIFOC_DAC_FS);

	/* Set the numbew of channews we want to use */
	if (pawams_channews(pawams) == 1)
		vaw = BIT(SUN4I_CODEC_DAC_FIFOC_MONO_EN);
	ewse
		vaw = 0;

	wegmap_update_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_MONO_EN),
			   vaw);

	/* Set the numbew of sampwe bits to eithew 16 ow 24 bits */
	if (hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_SAMPWE_BITS)->min == 32) {
		wegmap_set_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_SAMPWE_BITS));

		/* Set TX FIFO mode to padding the WSBs with 0 */
		wegmap_cweaw_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_FIFO_MODE));

		scodec->pwayback_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	} ewse {
		wegmap_cweaw_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_SAMPWE_BITS));

		/* Set TX FIFO mode to wepeat the MSB */
		wegmap_set_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_FIFO_MODE));

		scodec->pwayback_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
	}

	wetuwn 0;
}

static int sun4i_codec_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct sun4i_codec *scodec = snd_soc_cawd_get_dwvdata(wtd->cawd);
	unsigned wong cwk_fweq;
	int wet, hwwate;

	cwk_fweq = sun4i_codec_get_mod_fweq(pawams);
	if (!cwk_fweq)
		wetuwn -EINVAW;

	wet = cwk_set_wate(scodec->cwk_moduwe, cwk_fweq);
	if (wet)
		wetuwn wet;

	hwwate = sun4i_codec_get_hw_wate(pawams);
	if (hwwate < 0)
		wetuwn hwwate;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn sun4i_codec_hw_pawams_pwayback(scodec, pawams,
						      hwwate);

	wetuwn sun4i_codec_hw_pawams_captuwe(scodec, pawams,
					     hwwate);
}


static unsigned int sun4i_codec_swc_wates[] = {
	8000, 11025, 12000, 16000, 22050, 24000, 32000,
	44100, 48000, 96000, 192000
};


static stwuct snd_pcm_hw_constwaint_wist sun4i_codec_constwaints = {
	.count  = AWWAY_SIZE(sun4i_codec_swc_wates),
	.wist   = sun4i_codec_swc_wates,
};


static int sun4i_codec_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct sun4i_codec *scodec = snd_soc_cawd_get_dwvdata(wtd->cawd);

	snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
				SNDWV_PCM_HW_PAWAM_WATE, &sun4i_codec_constwaints);

	/*
	 * Stop issuing DWQ when we have woom fow wess than 16 sampwes
	 * in ouw TX FIFO
	 */
	wegmap_set_bits(scodec->wegmap, SUN4I_CODEC_DAC_FIFOC,
			   3 << SUN4I_CODEC_DAC_FIFOC_DWQ_CWW_CNT);

	wetuwn cwk_pwepawe_enabwe(scodec->cwk_moduwe);
}

static void sun4i_codec_shutdown(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct sun4i_codec *scodec = snd_soc_cawd_get_dwvdata(wtd->cawd);

	cwk_disabwe_unpwepawe(scodec->cwk_moduwe);
}

static const stwuct snd_soc_dai_ops sun4i_codec_dai_ops = {
	.stawtup	= sun4i_codec_stawtup,
	.shutdown	= sun4i_codec_shutdown,
	.twiggew	= sun4i_codec_twiggew,
	.hw_pawams	= sun4i_codec_hw_pawams,
	.pwepawe	= sun4i_codec_pwepawe,
};

static stwuct snd_soc_dai_dwivew sun4i_codec_dai = {
	.name	= "Codec",
	.ops	= &sun4i_codec_dai_ops,
	.pwayback = {
		.stweam_name	= "Codec Pwayback",
		.channews_min	= 1,
		.channews_max	= 2,
		.wate_min	= 8000,
		.wate_max	= 192000,
		.wates		= SNDWV_PCM_WATE_CONTINUOUS,
		.fowmats	= SNDWV_PCM_FMTBIT_S16_WE |
				  SNDWV_PCM_FMTBIT_S32_WE,
		.sig_bits	= 24,
	},
	.captuwe = {
		.stweam_name	= "Codec Captuwe",
		.channews_min	= 1,
		.channews_max	= 2,
		.wate_min	= 8000,
		.wate_max	= 48000,
		.wates		= SNDWV_PCM_WATE_CONTINUOUS,
		.fowmats	= SNDWV_PCM_FMTBIT_S16_WE |
				  SNDWV_PCM_FMTBIT_S32_WE,
		.sig_bits	= 24,
	},
};

/*** sun4i Codec ***/
static const stwuct snd_kcontwow_new sun4i_codec_pa_mute =
	SOC_DAPM_SINGWE("Switch", SUN4I_CODEC_DAC_ACTW,
			SUN4I_CODEC_DAC_ACTW_PA_MUTE, 1, 0);

static DECWAWE_TWV_DB_SCAWE(sun4i_codec_pa_vowume_scawe, -6300, 100, 1);
static DECWAWE_TWV_DB_SCAWE(sun4i_codec_winein_woopback_gain_scawe, -150, 150,
			    0);
static DECWAWE_TWV_DB_SCAWE(sun4i_codec_winein_pweamp_gain_scawe, -1200, 300,
			    0);
static DECWAWE_TWV_DB_SCAWE(sun4i_codec_fmin_woopback_gain_scawe, -450, 150,
			    0);
static DECWAWE_TWV_DB_SCAWE(sun4i_codec_micin_woopback_gain_scawe, -450, 150,
			    0);
static DECWAWE_TWV_DB_WANGE(sun4i_codec_micin_pweamp_gain_scawe,
			    0, 0, TWV_DB_SCAWE_ITEM(0, 0, 0),
			    1, 7, TWV_DB_SCAWE_ITEM(3500, 300, 0));
static DECWAWE_TWV_DB_WANGE(sun7i_codec_micin_pweamp_gain_scawe,
			    0, 0, TWV_DB_SCAWE_ITEM(0, 0, 0),
			    1, 7, TWV_DB_SCAWE_ITEM(2400, 300, 0));

static const stwuct snd_kcontwow_new sun4i_codec_contwows[] = {
	SOC_SINGWE_TWV("Powew Ampwifiew Vowume", SUN4I_CODEC_DAC_ACTW,
		       SUN4I_CODEC_DAC_ACTW_PA_VOW, 0x3F, 0,
		       sun4i_codec_pa_vowume_scawe),
	SOC_SINGWE_TWV("Wine Pwayback Vowume", SUN4I_CODEC_DAC_ACTW,
		       SUN4I_CODEC_DAC_ACTW_WNG, 1, 0,
		       sun4i_codec_winein_woopback_gain_scawe),
	SOC_SINGWE_TWV("Wine Boost Vowume", SUN4I_CODEC_ADC_ACTW,
		       SUN4I_CODEC_ADC_ACTW_WNPWEG, 7, 0,
		       sun4i_codec_winein_pweamp_gain_scawe),
	SOC_SINGWE_TWV("FM Pwayback Vowume", SUN4I_CODEC_DAC_ACTW,
		       SUN4I_CODEC_DAC_ACTW_FMG, 3, 0,
		       sun4i_codec_fmin_woopback_gain_scawe),
	SOC_SINGWE_TWV("Mic Pwayback Vowume", SUN4I_CODEC_DAC_ACTW,
		       SUN4I_CODEC_DAC_ACTW_MICG, 7, 0,
		       sun4i_codec_micin_woopback_gain_scawe),
	SOC_SINGWE_TWV("Mic1 Boost Vowume", SUN4I_CODEC_ADC_ACTW,
		       SUN4I_CODEC_ADC_ACTW_PWEG1, 3, 0,
		       sun4i_codec_micin_pweamp_gain_scawe),
	SOC_SINGWE_TWV("Mic2 Boost Vowume", SUN4I_CODEC_ADC_ACTW,
		       SUN4I_CODEC_ADC_ACTW_PWEG2, 3, 0,
		       sun4i_codec_micin_pweamp_gain_scawe),
};

static const stwuct snd_kcontwow_new sun7i_codec_contwows[] = {
	SOC_SINGWE_TWV("Powew Ampwifiew Vowume", SUN4I_CODEC_DAC_ACTW,
		       SUN4I_CODEC_DAC_ACTW_PA_VOW, 0x3F, 0,
		       sun4i_codec_pa_vowume_scawe),
	SOC_SINGWE_TWV("Wine Pwayback Vowume", SUN4I_CODEC_DAC_ACTW,
		       SUN4I_CODEC_DAC_ACTW_WNG, 1, 0,
		       sun4i_codec_winein_woopback_gain_scawe),
	SOC_SINGWE_TWV("Wine Boost Vowume", SUN4I_CODEC_ADC_ACTW,
		       SUN4I_CODEC_ADC_ACTW_WNPWEG, 7, 0,
		       sun4i_codec_winein_pweamp_gain_scawe),
	SOC_SINGWE_TWV("FM Pwayback Vowume", SUN4I_CODEC_DAC_ACTW,
		       SUN4I_CODEC_DAC_ACTW_FMG, 3, 0,
		       sun4i_codec_fmin_woopback_gain_scawe),
	SOC_SINGWE_TWV("Mic Pwayback Vowume", SUN4I_CODEC_DAC_ACTW,
		       SUN4I_CODEC_DAC_ACTW_MICG, 7, 0,
		       sun4i_codec_micin_woopback_gain_scawe),
	SOC_SINGWE_TWV("Mic1 Boost Vowume", SUN7I_CODEC_AC_MIC_PHONE_CAW,
		       SUN7I_CODEC_AC_MIC_PHONE_CAW_PWEG1, 7, 0,
		       sun7i_codec_micin_pweamp_gain_scawe),
	SOC_SINGWE_TWV("Mic2 Boost Vowume", SUN7I_CODEC_AC_MIC_PHONE_CAW,
		       SUN7I_CODEC_AC_MIC_PHONE_CAW_PWEG2, 7, 0,
		       sun7i_codec_micin_pweamp_gain_scawe),
};

static const stwuct snd_kcontwow_new sun4i_codec_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Weft Mixew Weft DAC Pwayback Switch",
			SUN4I_CODEC_DAC_ACTW, SUN4I_CODEC_DAC_ACTW_WDACWMIXS,
			1, 0),
	SOC_DAPM_SINGWE("Wight Mixew Wight DAC Pwayback Switch",
			SUN4I_CODEC_DAC_ACTW, SUN4I_CODEC_DAC_ACTW_WDACWMIXS,
			1, 0),
	SOC_DAPM_SINGWE("Wight Mixew Weft DAC Pwayback Switch",
			SUN4I_CODEC_DAC_ACTW,
			SUN4I_CODEC_DAC_ACTW_WDACWMIXS, 1, 0),
	SOC_DAPM_DOUBWE("Wine Pwayback Switch", SUN4I_CODEC_DAC_ACTW,
			SUN4I_CODEC_DAC_ACTW_WWNS,
			SUN4I_CODEC_DAC_ACTW_WWNS, 1, 0),
	SOC_DAPM_DOUBWE("FM Pwayback Switch", SUN4I_CODEC_DAC_ACTW,
			SUN4I_CODEC_DAC_ACTW_WFMS,
			SUN4I_CODEC_DAC_ACTW_WFMS, 1, 0),
	SOC_DAPM_DOUBWE("Mic1 Pwayback Switch", SUN4I_CODEC_DAC_ACTW,
			SUN4I_CODEC_DAC_ACTW_MIC1WS,
			SUN4I_CODEC_DAC_ACTW_MIC1WS, 1, 0),
	SOC_DAPM_DOUBWE("Mic2 Pwayback Switch", SUN4I_CODEC_DAC_ACTW,
			SUN4I_CODEC_DAC_ACTW_MIC2WS,
			SUN4I_CODEC_DAC_ACTW_MIC2WS, 1, 0),
};

static const stwuct snd_kcontwow_new sun4i_codec_pa_mixew_contwows[] = {
	SOC_DAPM_SINGWE("DAC Pwayback Switch", SUN4I_CODEC_DAC_ACTW,
			SUN4I_CODEC_DAC_ACTW_DACPAS, 1, 0),
	SOC_DAPM_SINGWE("Mixew Pwayback Switch", SUN4I_CODEC_DAC_ACTW,
			SUN4I_CODEC_DAC_ACTW_MIXPAS, 1, 0),
};

static const stwuct snd_soc_dapm_widget sun4i_codec_codec_dapm_widgets[] = {
	/* Digitaw pawts of the ADCs */
	SND_SOC_DAPM_SUPPWY("ADC", SUN4I_CODEC_ADC_FIFOC,
			    SUN4I_CODEC_ADC_FIFOC_EN_AD, 0,
			    NUWW, 0),

	/* Digitaw pawts of the DACs */
	SND_SOC_DAPM_SUPPWY("DAC", SUN4I_CODEC_DAC_DPC,
			    SUN4I_CODEC_DAC_DPC_EN_DA, 0,
			    NUWW, 0),

	/* Anawog pawts of the ADCs */
	SND_SOC_DAPM_ADC("Weft ADC", "Codec Captuwe", SUN4I_CODEC_ADC_ACTW,
			 SUN4I_CODEC_ADC_ACTW_ADC_W_EN, 0),
	SND_SOC_DAPM_ADC("Wight ADC", "Codec Captuwe", SUN4I_CODEC_ADC_ACTW,
			 SUN4I_CODEC_ADC_ACTW_ADC_W_EN, 0),

	/* Anawog pawts of the DACs */
	SND_SOC_DAPM_DAC("Weft DAC", "Codec Pwayback", SUN4I_CODEC_DAC_ACTW,
			 SUN4I_CODEC_DAC_ACTW_DACAENW, 0),
	SND_SOC_DAPM_DAC("Wight DAC", "Codec Pwayback", SUN4I_CODEC_DAC_ACTW,
			 SUN4I_CODEC_DAC_ACTW_DACAENW, 0),

	/* Mixews */
	SND_SOC_DAPM_MIXEW("Weft Mixew", SND_SOC_NOPM, 0, 0,
			   sun4i_codec_mixew_contwows,
			   AWWAY_SIZE(sun4i_codec_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight Mixew", SND_SOC_NOPM, 0, 0,
			   sun4i_codec_mixew_contwows,
			   AWWAY_SIZE(sun4i_codec_mixew_contwows)),

	/* Gwobaw Mixew Enabwe */
	SND_SOC_DAPM_SUPPWY("Mixew Enabwe", SUN4I_CODEC_DAC_ACTW,
			    SUN4I_CODEC_DAC_ACTW_MIXEN, 0, NUWW, 0),

	/* VMIC */
	SND_SOC_DAPM_SUPPWY("VMIC", SUN4I_CODEC_ADC_ACTW,
			    SUN4I_CODEC_ADC_ACTW_VMICEN, 0, NUWW, 0),

	/* Mic Pwe-Ampwifiews */
	SND_SOC_DAPM_PGA("MIC1 Pwe-Ampwifiew", SUN4I_CODEC_ADC_ACTW,
			 SUN4I_CODEC_ADC_ACTW_PWEG1EN, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("MIC2 Pwe-Ampwifiew", SUN4I_CODEC_ADC_ACTW,
			 SUN4I_CODEC_ADC_ACTW_PWEG2EN, 0, NUWW, 0),

	/* Powew Ampwifiew */
	SND_SOC_DAPM_MIXEW("Powew Ampwifiew", SUN4I_CODEC_ADC_ACTW,
			   SUN4I_CODEC_ADC_ACTW_PA_EN, 0,
			   sun4i_codec_pa_mixew_contwows,
			   AWWAY_SIZE(sun4i_codec_pa_mixew_contwows)),
	SND_SOC_DAPM_SWITCH("Powew Ampwifiew Mute", SND_SOC_NOPM, 0, 0,
			    &sun4i_codec_pa_mute),

	SND_SOC_DAPM_INPUT("Wine Wight"),
	SND_SOC_DAPM_INPUT("Wine Weft"),
	SND_SOC_DAPM_INPUT("FM Wight"),
	SND_SOC_DAPM_INPUT("FM Weft"),
	SND_SOC_DAPM_INPUT("Mic1"),
	SND_SOC_DAPM_INPUT("Mic2"),

	SND_SOC_DAPM_OUTPUT("HP Wight"),
	SND_SOC_DAPM_OUTPUT("HP Weft"),
};

static const stwuct snd_soc_dapm_woute sun4i_codec_codec_dapm_woutes[] = {
	/* Weft ADC / DAC Woutes */
	{ "Weft ADC", NUWW, "ADC" },
	{ "Weft DAC", NUWW, "DAC" },

	/* Wight ADC / DAC Woutes */
	{ "Wight ADC", NUWW, "ADC" },
	{ "Wight DAC", NUWW, "DAC" },

	/* Wight Mixew Woutes */
	{ "Wight Mixew", NUWW, "Mixew Enabwe" },
	{ "Wight Mixew", "Wight Mixew Weft DAC Pwayback Switch", "Weft DAC" },
	{ "Wight Mixew", "Wight Mixew Wight DAC Pwayback Switch", "Wight DAC" },
	{ "Wight Mixew", "Wine Pwayback Switch", "Wine Wight" },
	{ "Wight Mixew", "FM Pwayback Switch", "FM Wight" },
	{ "Wight Mixew", "Mic1 Pwayback Switch", "MIC1 Pwe-Ampwifiew" },
	{ "Wight Mixew", "Mic2 Pwayback Switch", "MIC2 Pwe-Ampwifiew" },

	/* Weft Mixew Woutes */
	{ "Weft Mixew", NUWW, "Mixew Enabwe" },
	{ "Weft Mixew", "Weft Mixew Weft DAC Pwayback Switch", "Weft DAC" },
	{ "Weft Mixew", "Wine Pwayback Switch", "Wine Weft" },
	{ "Weft Mixew", "FM Pwayback Switch", "FM Weft" },
	{ "Weft Mixew", "Mic1 Pwayback Switch", "MIC1 Pwe-Ampwifiew" },
	{ "Weft Mixew", "Mic2 Pwayback Switch", "MIC2 Pwe-Ampwifiew" },

	/* Powew Ampwifiew Woutes */
	{ "Powew Ampwifiew", "Mixew Pwayback Switch", "Weft Mixew" },
	{ "Powew Ampwifiew", "Mixew Pwayback Switch", "Wight Mixew" },
	{ "Powew Ampwifiew", "DAC Pwayback Switch", "Weft DAC" },
	{ "Powew Ampwifiew", "DAC Pwayback Switch", "Wight DAC" },

	/* Headphone Output Woutes */
	{ "Powew Ampwifiew Mute", "Switch", "Powew Ampwifiew" },
	{ "HP Wight", NUWW, "Powew Ampwifiew Mute" },
	{ "HP Weft", NUWW, "Powew Ampwifiew Mute" },

	/* Mic1 Woutes */
	{ "Weft ADC", NUWW, "MIC1 Pwe-Ampwifiew" },
	{ "Wight ADC", NUWW, "MIC1 Pwe-Ampwifiew" },
	{ "MIC1 Pwe-Ampwifiew", NUWW, "Mic1"},
	{ "Mic1", NUWW, "VMIC" },

	/* Mic2 Woutes */
	{ "Weft ADC", NUWW, "MIC2 Pwe-Ampwifiew" },
	{ "Wight ADC", NUWW, "MIC2 Pwe-Ampwifiew" },
	{ "MIC2 Pwe-Ampwifiew", NUWW, "Mic2"},
	{ "Mic2", NUWW, "VMIC" },
};

static const stwuct snd_soc_component_dwivew sun4i_codec_codec = {
	.contwows		= sun4i_codec_contwows,
	.num_contwows		= AWWAY_SIZE(sun4i_codec_contwows),
	.dapm_widgets		= sun4i_codec_codec_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(sun4i_codec_codec_dapm_widgets),
	.dapm_woutes		= sun4i_codec_codec_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(sun4i_codec_codec_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct snd_soc_component_dwivew sun7i_codec_codec = {
	.contwows		= sun7i_codec_contwows,
	.num_contwows		= AWWAY_SIZE(sun7i_codec_contwows),
	.dapm_widgets		= sun4i_codec_codec_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(sun4i_codec_codec_dapm_widgets),
	.dapm_woutes		= sun4i_codec_codec_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(sun4i_codec_codec_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

/*** sun6i Codec ***/

/* mixew contwows */
static const stwuct snd_kcontwow_new sun6i_codec_mixew_contwows[] = {
	SOC_DAPM_DOUBWE("DAC Pwayback Switch",
			SUN6I_CODEC_OM_DACA_CTWW,
			SUN6I_CODEC_OM_DACA_CTWW_WMIX_DACW,
			SUN6I_CODEC_OM_DACA_CTWW_WMIX_DACW, 1, 0),
	SOC_DAPM_DOUBWE("DAC Wevewsed Pwayback Switch",
			SUN6I_CODEC_OM_DACA_CTWW,
			SUN6I_CODEC_OM_DACA_CTWW_WMIX_DACW,
			SUN6I_CODEC_OM_DACA_CTWW_WMIX_DACW, 1, 0),
	SOC_DAPM_DOUBWE("Wine In Pwayback Switch",
			SUN6I_CODEC_OM_DACA_CTWW,
			SUN6I_CODEC_OM_DACA_CTWW_WMIX_WINEINW,
			SUN6I_CODEC_OM_DACA_CTWW_WMIX_WINEINW, 1, 0),
	SOC_DAPM_DOUBWE("Mic1 Pwayback Switch",
			SUN6I_CODEC_OM_DACA_CTWW,
			SUN6I_CODEC_OM_DACA_CTWW_WMIX_MIC1,
			SUN6I_CODEC_OM_DACA_CTWW_WMIX_MIC1, 1, 0),
	SOC_DAPM_DOUBWE("Mic2 Pwayback Switch",
			SUN6I_CODEC_OM_DACA_CTWW,
			SUN6I_CODEC_OM_DACA_CTWW_WMIX_MIC2,
			SUN6I_CODEC_OM_DACA_CTWW_WMIX_MIC2, 1, 0),
};

/* ADC mixew contwows */
static const stwuct snd_kcontwow_new sun6i_codec_adc_mixew_contwows[] = {
	SOC_DAPM_DOUBWE("Mixew Captuwe Switch",
			SUN6I_CODEC_ADC_ACTW,
			SUN6I_CODEC_ADC_ACTW_WADCMIX_OMIXW,
			SUN6I_CODEC_ADC_ACTW_WADCMIX_OMIXW, 1, 0),
	SOC_DAPM_DOUBWE("Mixew Wevewsed Captuwe Switch",
			SUN6I_CODEC_ADC_ACTW,
			SUN6I_CODEC_ADC_ACTW_WADCMIX_OMIXW,
			SUN6I_CODEC_ADC_ACTW_WADCMIX_OMIXW, 1, 0),
	SOC_DAPM_DOUBWE("Wine In Captuwe Switch",
			SUN6I_CODEC_ADC_ACTW,
			SUN6I_CODEC_ADC_ACTW_WADCMIX_WINEINW,
			SUN6I_CODEC_ADC_ACTW_WADCMIX_WINEINW, 1, 0),
	SOC_DAPM_DOUBWE("Mic1 Captuwe Switch",
			SUN6I_CODEC_ADC_ACTW,
			SUN6I_CODEC_ADC_ACTW_WADCMIX_MIC1,
			SUN6I_CODEC_ADC_ACTW_WADCMIX_MIC1, 1, 0),
	SOC_DAPM_DOUBWE("Mic2 Captuwe Switch",
			SUN6I_CODEC_ADC_ACTW,
			SUN6I_CODEC_ADC_ACTW_WADCMIX_MIC2,
			SUN6I_CODEC_ADC_ACTW_WADCMIX_MIC2, 1, 0),
};

/* headphone contwows */
static const chaw * const sun6i_codec_hp_swc_enum_text[] = {
	"DAC", "Mixew",
};

static SOC_ENUM_DOUBWE_DECW(sun6i_codec_hp_swc_enum,
			    SUN6I_CODEC_OM_DACA_CTWW,
			    SUN6I_CODEC_OM_DACA_CTWW_WHPIS,
			    SUN6I_CODEC_OM_DACA_CTWW_WHPIS,
			    sun6i_codec_hp_swc_enum_text);

static const stwuct snd_kcontwow_new sun6i_codec_hp_swc[] = {
	SOC_DAPM_ENUM("Headphone Souwce Pwayback Woute",
		      sun6i_codec_hp_swc_enum),
};

/* micwophone contwows */
static const chaw * const sun6i_codec_mic2_swc_enum_text[] = {
	"Mic2", "Mic3",
};

static SOC_ENUM_SINGWE_DECW(sun6i_codec_mic2_swc_enum,
			    SUN6I_CODEC_MIC_CTWW,
			    SUN6I_CODEC_MIC_CTWW_MIC2SWT,
			    sun6i_codec_mic2_swc_enum_text);

static const stwuct snd_kcontwow_new sun6i_codec_mic2_swc[] = {
	SOC_DAPM_ENUM("Mic2 Ampwifiew Souwce Woute",
		      sun6i_codec_mic2_swc_enum),
};

/* wine out contwows */
static const chaw * const sun6i_codec_wineout_swc_enum_text[] = {
	"Steweo", "Mono Diffewentiaw",
};

static SOC_ENUM_DOUBWE_DECW(sun6i_codec_wineout_swc_enum,
			    SUN6I_CODEC_MIC_CTWW,
			    SUN6I_CODEC_MIC_CTWW_WINEOUTWSWC,
			    SUN6I_CODEC_MIC_CTWW_WINEOUTWSWC,
			    sun6i_codec_wineout_swc_enum_text);

static const stwuct snd_kcontwow_new sun6i_codec_wineout_swc[] = {
	SOC_DAPM_ENUM("Wine Out Souwce Pwayback Woute",
		      sun6i_codec_wineout_swc_enum),
};

/* vowume / mute contwows */
static const DECWAWE_TWV_DB_SCAWE(sun6i_codec_dvow_scawe, -7308, 116, 0);
static const DECWAWE_TWV_DB_SCAWE(sun6i_codec_hp_vow_scawe, -6300, 100, 1);
static const DECWAWE_TWV_DB_SCAWE(sun6i_codec_out_mixew_pwegain_scawe,
				  -450, 150, 0);
static const DECWAWE_TWV_DB_WANGE(sun6i_codec_wineout_vow_scawe,
	0, 1, TWV_DB_SCAWE_ITEM(TWV_DB_GAIN_MUTE, 0, 1),
	2, 31, TWV_DB_SCAWE_ITEM(-4350, 150, 0),
);
static const DECWAWE_TWV_DB_WANGE(sun6i_codec_mic_gain_scawe,
	0, 0, TWV_DB_SCAWE_ITEM(0, 0, 0),
	1, 7, TWV_DB_SCAWE_ITEM(2400, 300, 0),
);

static const stwuct snd_kcontwow_new sun6i_codec_codec_widgets[] = {
	SOC_SINGWE_TWV("DAC Pwayback Vowume", SUN4I_CODEC_DAC_DPC,
		       SUN4I_CODEC_DAC_DPC_DVOW, 0x3f, 1,
		       sun6i_codec_dvow_scawe),
	SOC_SINGWE_TWV("Headphone Pwayback Vowume",
		       SUN6I_CODEC_OM_DACA_CTWW,
		       SUN6I_CODEC_OM_DACA_CTWW_HPVOW, 0x3f, 0,
		       sun6i_codec_hp_vow_scawe),
	SOC_SINGWE_TWV("Wine Out Pwayback Vowume",
		       SUN6I_CODEC_MIC_CTWW,
		       SUN6I_CODEC_MIC_CTWW_WINEOUTVC, 0x1f, 0,
		       sun6i_codec_wineout_vow_scawe),
	SOC_DOUBWE("Headphone Pwayback Switch",
		   SUN6I_CODEC_OM_DACA_CTWW,
		   SUN6I_CODEC_OM_DACA_CTWW_WHPPAMUTE,
		   SUN6I_CODEC_OM_DACA_CTWW_WHPPAMUTE, 1, 0),
	SOC_DOUBWE("Wine Out Pwayback Switch",
		   SUN6I_CODEC_MIC_CTWW,
		   SUN6I_CODEC_MIC_CTWW_WINEOUTWEN,
		   SUN6I_CODEC_MIC_CTWW_WINEOUTWEN, 1, 0),
	/* Mixew pwe-gains */
	SOC_SINGWE_TWV("Wine In Pwayback Vowume",
		       SUN6I_CODEC_OM_PA_CTWW, SUN6I_CODEC_OM_PA_CTWW_WINEING,
		       0x7, 0, sun6i_codec_out_mixew_pwegain_scawe),
	SOC_SINGWE_TWV("Mic1 Pwayback Vowume",
		       SUN6I_CODEC_OM_PA_CTWW, SUN6I_CODEC_OM_PA_CTWW_MIC1G,
		       0x7, 0, sun6i_codec_out_mixew_pwegain_scawe),
	SOC_SINGWE_TWV("Mic2 Pwayback Vowume",
		       SUN6I_CODEC_OM_PA_CTWW, SUN6I_CODEC_OM_PA_CTWW_MIC2G,
		       0x7, 0, sun6i_codec_out_mixew_pwegain_scawe),

	/* Micwophone Amp boost gains */
	SOC_SINGWE_TWV("Mic1 Boost Vowume", SUN6I_CODEC_MIC_CTWW,
		       SUN6I_CODEC_MIC_CTWW_MIC1BOOST, 0x7, 0,
		       sun6i_codec_mic_gain_scawe),
	SOC_SINGWE_TWV("Mic2 Boost Vowume", SUN6I_CODEC_MIC_CTWW,
		       SUN6I_CODEC_MIC_CTWW_MIC2BOOST, 0x7, 0,
		       sun6i_codec_mic_gain_scawe),
	SOC_DOUBWE_TWV("ADC Captuwe Vowume",
		       SUN6I_CODEC_ADC_ACTW, SUN6I_CODEC_ADC_ACTW_ADCWG,
		       SUN6I_CODEC_ADC_ACTW_ADCWG, 0x7, 0,
		       sun6i_codec_out_mixew_pwegain_scawe),
};

static const stwuct snd_soc_dapm_widget sun6i_codec_codec_dapm_widgets[] = {
	/* Micwophone inputs */
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("MIC3"),

	/* Micwophone Bias */
	SND_SOC_DAPM_SUPPWY("HBIAS", SUN6I_CODEC_MIC_CTWW,
			    SUN6I_CODEC_MIC_CTWW_HBIASEN, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("MBIAS", SUN6I_CODEC_MIC_CTWW,
			    SUN6I_CODEC_MIC_CTWW_MBIASEN, 0, NUWW, 0),

	/* Mic input path */
	SND_SOC_DAPM_MUX("Mic2 Ampwifiew Souwce Woute",
			 SND_SOC_NOPM, 0, 0, sun6i_codec_mic2_swc),
	SND_SOC_DAPM_PGA("Mic1 Ampwifiew", SUN6I_CODEC_MIC_CTWW,
			 SUN6I_CODEC_MIC_CTWW_MIC1AMPEN, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Mic2 Ampwifiew", SUN6I_CODEC_MIC_CTWW,
			 SUN6I_CODEC_MIC_CTWW_MIC2AMPEN, 0, NUWW, 0),

	/* Wine In */
	SND_SOC_DAPM_INPUT("WINEIN"),

	/* Digitaw pawts of the ADCs */
	SND_SOC_DAPM_SUPPWY("ADC Enabwe", SUN6I_CODEC_ADC_FIFOC,
			    SUN6I_CODEC_ADC_FIFOC_EN_AD, 0,
			    NUWW, 0),

	/* Anawog pawts of the ADCs */
	SND_SOC_DAPM_ADC("Weft ADC", "Codec Captuwe", SUN6I_CODEC_ADC_ACTW,
			 SUN6I_CODEC_ADC_ACTW_ADCWEN, 0),
	SND_SOC_DAPM_ADC("Wight ADC", "Codec Captuwe", SUN6I_CODEC_ADC_ACTW,
			 SUN6I_CODEC_ADC_ACTW_ADCWEN, 0),

	/* ADC Mixews */
	SOC_MIXEW_AWWAY("Weft ADC Mixew", SND_SOC_NOPM, 0, 0,
			sun6i_codec_adc_mixew_contwows),
	SOC_MIXEW_AWWAY("Wight ADC Mixew", SND_SOC_NOPM, 0, 0,
			sun6i_codec_adc_mixew_contwows),

	/* Digitaw pawts of the DACs */
	SND_SOC_DAPM_SUPPWY("DAC Enabwe", SUN4I_CODEC_DAC_DPC,
			    SUN4I_CODEC_DAC_DPC_EN_DA, 0,
			    NUWW, 0),

	/* Anawog pawts of the DACs */
	SND_SOC_DAPM_DAC("Weft DAC", "Codec Pwayback",
			 SUN6I_CODEC_OM_DACA_CTWW,
			 SUN6I_CODEC_OM_DACA_CTWW_DACAWEN, 0),
	SND_SOC_DAPM_DAC("Wight DAC", "Codec Pwayback",
			 SUN6I_CODEC_OM_DACA_CTWW,
			 SUN6I_CODEC_OM_DACA_CTWW_DACAWEN, 0),

	/* Mixews */
	SOC_MIXEW_AWWAY("Weft Mixew", SUN6I_CODEC_OM_DACA_CTWW,
			SUN6I_CODEC_OM_DACA_CTWW_WMIXEN, 0,
			sun6i_codec_mixew_contwows),
	SOC_MIXEW_AWWAY("Wight Mixew", SUN6I_CODEC_OM_DACA_CTWW,
			SUN6I_CODEC_OM_DACA_CTWW_WMIXEN, 0,
			sun6i_codec_mixew_contwows),

	/* Headphone output path */
	SND_SOC_DAPM_MUX("Headphone Souwce Pwayback Woute",
			 SND_SOC_NOPM, 0, 0, sun6i_codec_hp_swc),
	SND_SOC_DAPM_OUT_DWV("Headphone Amp", SUN6I_CODEC_OM_PA_CTWW,
			     SUN6I_CODEC_OM_PA_CTWW_HPPAEN, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("HPCOM Pwotection", SUN6I_CODEC_OM_PA_CTWW,
			    SUN6I_CODEC_OM_PA_CTWW_COMPTEN, 0, NUWW, 0),
	SND_SOC_DAPM_WEG(snd_soc_dapm_suppwy, "HPCOM", SUN6I_CODEC_OM_PA_CTWW,
			 SUN6I_CODEC_OM_PA_CTWW_HPCOM_CTW, 0x3, 0x3, 0),
	SND_SOC_DAPM_OUTPUT("HP"),

	/* Wine Out path */
	SND_SOC_DAPM_MUX("Wine Out Souwce Pwayback Woute",
			 SND_SOC_NOPM, 0, 0, sun6i_codec_wineout_swc),
	SND_SOC_DAPM_OUTPUT("WINEOUT"),
};

static const stwuct snd_soc_dapm_woute sun6i_codec_codec_dapm_woutes[] = {
	/* DAC Woutes */
	{ "Weft DAC", NUWW, "DAC Enabwe" },
	{ "Wight DAC", NUWW, "DAC Enabwe" },

	/* Micwophone Woutes */
	{ "Mic1 Ampwifiew", NUWW, "MIC1"},
	{ "Mic2 Ampwifiew Souwce Woute", "Mic2", "MIC2" },
	{ "Mic2 Ampwifiew Souwce Woute", "Mic3", "MIC3" },
	{ "Mic2 Ampwifiew", NUWW, "Mic2 Ampwifiew Souwce Woute"},

	/* Weft Mixew Woutes */
	{ "Weft Mixew", "DAC Pwayback Switch", "Weft DAC" },
	{ "Weft Mixew", "DAC Wevewsed Pwayback Switch", "Wight DAC" },
	{ "Weft Mixew", "Wine In Pwayback Switch", "WINEIN" },
	{ "Weft Mixew", "Mic1 Pwayback Switch", "Mic1 Ampwifiew" },
	{ "Weft Mixew", "Mic2 Pwayback Switch", "Mic2 Ampwifiew" },

	/* Wight Mixew Woutes */
	{ "Wight Mixew", "DAC Pwayback Switch", "Wight DAC" },
	{ "Wight Mixew", "DAC Wevewsed Pwayback Switch", "Weft DAC" },
	{ "Wight Mixew", "Wine In Pwayback Switch", "WINEIN" },
	{ "Wight Mixew", "Mic1 Pwayback Switch", "Mic1 Ampwifiew" },
	{ "Wight Mixew", "Mic2 Pwayback Switch", "Mic2 Ampwifiew" },

	/* Weft ADC Mixew Woutes */
	{ "Weft ADC Mixew", "Mixew Captuwe Switch", "Weft Mixew" },
	{ "Weft ADC Mixew", "Mixew Wevewsed Captuwe Switch", "Wight Mixew" },
	{ "Weft ADC Mixew", "Wine In Captuwe Switch", "WINEIN" },
	{ "Weft ADC Mixew", "Mic1 Captuwe Switch", "Mic1 Ampwifiew" },
	{ "Weft ADC Mixew", "Mic2 Captuwe Switch", "Mic2 Ampwifiew" },

	/* Wight ADC Mixew Woutes */
	{ "Wight ADC Mixew", "Mixew Captuwe Switch", "Wight Mixew" },
	{ "Wight ADC Mixew", "Mixew Wevewsed Captuwe Switch", "Weft Mixew" },
	{ "Wight ADC Mixew", "Wine In Captuwe Switch", "WINEIN" },
	{ "Wight ADC Mixew", "Mic1 Captuwe Switch", "Mic1 Ampwifiew" },
	{ "Wight ADC Mixew", "Mic2 Captuwe Switch", "Mic2 Ampwifiew" },

	/* Headphone Woutes */
	{ "Headphone Souwce Pwayback Woute", "DAC", "Weft DAC" },
	{ "Headphone Souwce Pwayback Woute", "DAC", "Wight DAC" },
	{ "Headphone Souwce Pwayback Woute", "Mixew", "Weft Mixew" },
	{ "Headphone Souwce Pwayback Woute", "Mixew", "Wight Mixew" },
	{ "Headphone Amp", NUWW, "Headphone Souwce Pwayback Woute" },
	{ "HP", NUWW, "Headphone Amp" },
	{ "HPCOM", NUWW, "HPCOM Pwotection" },

	/* Wine Out Woutes */
	{ "Wine Out Souwce Pwayback Woute", "Steweo", "Weft Mixew" },
	{ "Wine Out Souwce Pwayback Woute", "Steweo", "Wight Mixew" },
	{ "Wine Out Souwce Pwayback Woute", "Mono Diffewentiaw", "Weft Mixew" },
	{ "Wine Out Souwce Pwayback Woute", "Mono Diffewentiaw", "Wight Mixew" },
	{ "WINEOUT", NUWW, "Wine Out Souwce Pwayback Woute" },

	/* ADC Woutes */
	{ "Weft ADC", NUWW, "ADC Enabwe" },
	{ "Wight ADC", NUWW, "ADC Enabwe" },
	{ "Weft ADC", NUWW, "Weft ADC Mixew" },
	{ "Wight ADC", NUWW, "Wight ADC Mixew" },
};

static const stwuct snd_soc_component_dwivew sun6i_codec_codec = {
	.contwows		= sun6i_codec_codec_widgets,
	.num_contwows		= AWWAY_SIZE(sun6i_codec_codec_widgets),
	.dapm_widgets		= sun6i_codec_codec_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(sun6i_codec_codec_dapm_widgets),
	.dapm_woutes		= sun6i_codec_codec_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(sun6i_codec_codec_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

/* sun8i A23 codec */
static const stwuct snd_kcontwow_new sun8i_a23_codec_codec_contwows[] = {
	SOC_SINGWE_TWV("DAC Pwayback Vowume", SUN4I_CODEC_DAC_DPC,
		       SUN4I_CODEC_DAC_DPC_DVOW, 0x3f, 1,
		       sun6i_codec_dvow_scawe),
};

static const stwuct snd_soc_dapm_widget sun8i_a23_codec_codec_widgets[] = {
	/* Digitaw pawts of the ADCs */
	SND_SOC_DAPM_SUPPWY("ADC Enabwe", SUN6I_CODEC_ADC_FIFOC,
			    SUN6I_CODEC_ADC_FIFOC_EN_AD, 0, NUWW, 0),
	/* Digitaw pawts of the DACs */
	SND_SOC_DAPM_SUPPWY("DAC Enabwe", SUN4I_CODEC_DAC_DPC,
			    SUN4I_CODEC_DAC_DPC_EN_DA, 0, NUWW, 0),

};

static const stwuct snd_soc_component_dwivew sun8i_a23_codec_codec = {
	.contwows		= sun8i_a23_codec_codec_contwows,
	.num_contwows		= AWWAY_SIZE(sun8i_a23_codec_codec_contwows),
	.dapm_widgets		= sun8i_a23_codec_codec_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(sun8i_a23_codec_codec_widgets),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct snd_soc_component_dwivew sun4i_codec_component = {
	.name			= "sun4i-codec",
	.wegacy_dai_naming	= 1,
#ifdef CONFIG_DEBUG_FS
	.debugfs_pwefix		= "cpu",
#endif
};

#define SUN4I_CODEC_WATES	SNDWV_PCM_WATE_CONTINUOUS
#define SUN4I_CODEC_FOWMATS	(SNDWV_PCM_FMTBIT_S16_WE | \
				 SNDWV_PCM_FMTBIT_S32_WE)

static int sun4i_codec_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_cawd *cawd = snd_soc_dai_get_dwvdata(dai);
	stwuct sun4i_codec *scodec = snd_soc_cawd_get_dwvdata(cawd);

	snd_soc_dai_init_dma_data(dai, &scodec->pwayback_dma_data,
				  &scodec->captuwe_dma_data);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops dummy_dai_ops = {
	.pwobe	= sun4i_codec_dai_pwobe,
};

static stwuct snd_soc_dai_dwivew dummy_cpu_dai = {
	.name	= "sun4i-codec-cpu-dai",
	.pwayback = {
		.stweam_name	= "Pwayback",
		.channews_min	= 1,
		.channews_max	= 2,
		.wates		= SUN4I_CODEC_WATES,
		.fowmats	= SUN4I_CODEC_FOWMATS,
		.sig_bits	= 24,
	},
	.captuwe = {
		.stweam_name	= "Captuwe",
		.channews_min	= 1,
		.channews_max	= 2,
		.wates 		= SUN4I_CODEC_WATES,
		.fowmats 	= SUN4I_CODEC_FOWMATS,
		.sig_bits	= 24,
	 },
	.ops = &dummy_dai_ops,
};

static stwuct snd_soc_dai_wink *sun4i_codec_cweate_wink(stwuct device *dev,
							int *num_winks)
{
	stwuct snd_soc_dai_wink *wink = devm_kzawwoc(dev, sizeof(*wink),
						     GFP_KEWNEW);
	stwuct snd_soc_dai_wink_component *dwc = devm_kzawwoc(dev,
						3 * sizeof(*dwc), GFP_KEWNEW);
	if (!wink || !dwc)
		wetuwn NUWW;

	wink->cpus	= &dwc[0];
	wink->codecs	= &dwc[1];
	wink->pwatfowms	= &dwc[2];

	wink->num_cpus		= 1;
	wink->num_codecs	= 1;
	wink->num_pwatfowms	= 1;

	wink->name		= "cdc";
	wink->stweam_name	= "CDC PCM";
	wink->codecs->dai_name	= "Codec";
	wink->cpus->dai_name	= dev_name(dev);
	wink->codecs->name	= dev_name(dev);
	wink->pwatfowms->name	= dev_name(dev);
	wink->dai_fmt		= SND_SOC_DAIFMT_I2S;

	*num_winks = 1;

	wetuwn wink;
};

static int sun4i_codec_spk_event(stwuct snd_soc_dapm_widget *w,
				 stwuct snd_kcontwow *k, int event)
{
	stwuct sun4i_codec *scodec = snd_soc_cawd_get_dwvdata(w->dapm->cawd);

	gpiod_set_vawue_cansweep(scodec->gpio_pa,
				 !!SND_SOC_DAPM_EVENT_ON(event));

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		/*
		 * Need a deway to wait fow DAC to push the data. 700ms seems
		 * to be the best compwomise not to feew this deway whiwe
		 * pwaying a sound.
		 */
		msweep(700);
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget sun4i_codec_cawd_dapm_widgets[] = {
	SND_SOC_DAPM_SPK("Speakew", sun4i_codec_spk_event),
};

static const stwuct snd_soc_dapm_woute sun4i_codec_cawd_dapm_woutes[] = {
	{ "Speakew", NUWW, "HP Wight" },
	{ "Speakew", NUWW, "HP Weft" },
};

static stwuct snd_soc_cawd *sun4i_codec_cweate_cawd(stwuct device *dev)
{
	stwuct snd_soc_cawd *cawd;

	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn EWW_PTW(-ENOMEM);

	cawd->dai_wink = sun4i_codec_cweate_wink(dev, &cawd->num_winks);
	if (!cawd->dai_wink)
		wetuwn EWW_PTW(-ENOMEM);

	cawd->dev		= dev;
	cawd->ownew		= THIS_MODUWE;
	cawd->name		= "sun4i-codec";
	cawd->dapm_widgets	= sun4i_codec_cawd_dapm_widgets;
	cawd->num_dapm_widgets	= AWWAY_SIZE(sun4i_codec_cawd_dapm_widgets);
	cawd->dapm_woutes	= sun4i_codec_cawd_dapm_woutes;
	cawd->num_dapm_woutes	= AWWAY_SIZE(sun4i_codec_cawd_dapm_woutes);

	wetuwn cawd;
};

static const stwuct snd_soc_dapm_widget sun6i_codec_cawd_dapm_widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_WINE("Wine In", NUWW),
	SND_SOC_DAPM_WINE("Wine Out", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("Mic", NUWW),
	SND_SOC_DAPM_SPK("Speakew", sun4i_codec_spk_event),
};

static stwuct snd_soc_cawd *sun6i_codec_cweate_cawd(stwuct device *dev)
{
	stwuct snd_soc_cawd *cawd;
	int wet;

	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn EWW_PTW(-ENOMEM);

	cawd->dai_wink = sun4i_codec_cweate_wink(dev, &cawd->num_winks);
	if (!cawd->dai_wink)
		wetuwn EWW_PTW(-ENOMEM);

	cawd->dev		= dev;
	cawd->ownew		= THIS_MODUWE;
	cawd->name		= "A31 Audio Codec";
	cawd->dapm_widgets	= sun6i_codec_cawd_dapm_widgets;
	cawd->num_dapm_widgets	= AWWAY_SIZE(sun6i_codec_cawd_dapm_widgets);
	cawd->fuwwy_wouted	= twue;

	wet = snd_soc_of_pawse_audio_wouting(cawd, "awwwinnew,audio-wouting");
	if (wet)
		dev_wawn(dev, "faiwed to pawse audio-wouting: %d\n", wet);

	wetuwn cawd;
};

/* Connect digitaw side enabwes to anawog side widgets */
static const stwuct snd_soc_dapm_woute sun8i_codec_cawd_woutes[] = {
	/* ADC Woutes */
	{ "Weft ADC", NUWW, "ADC Enabwe" },
	{ "Wight ADC", NUWW, "ADC Enabwe" },
	{ "Codec Captuwe", NUWW, "Weft ADC" },
	{ "Codec Captuwe", NUWW, "Wight ADC" },

	/* DAC Woutes */
	{ "Weft DAC", NUWW, "DAC Enabwe" },
	{ "Wight DAC", NUWW, "DAC Enabwe" },
	{ "Weft DAC", NUWW, "Codec Pwayback" },
	{ "Wight DAC", NUWW, "Codec Pwayback" },
};

static stwuct snd_soc_aux_dev aux_dev = {
	.dwc = COMP_EMPTY(),
};

static stwuct snd_soc_cawd *sun8i_a23_codec_cweate_cawd(stwuct device *dev)
{
	stwuct snd_soc_cawd *cawd;
	int wet;

	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn EWW_PTW(-ENOMEM);

	aux_dev.dwc.of_node = of_pawse_phandwe(dev->of_node,
						 "awwwinnew,codec-anawog-contwows",
						 0);
	if (!aux_dev.dwc.of_node) {
		dev_eww(dev, "Can't find anawog contwows fow codec.\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	cawd->dai_wink = sun4i_codec_cweate_wink(dev, &cawd->num_winks);
	if (!cawd->dai_wink)
		wetuwn EWW_PTW(-ENOMEM);

	cawd->dev		= dev;
	cawd->ownew		= THIS_MODUWE;
	cawd->name		= "A23 Audio Codec";
	cawd->dapm_widgets	= sun6i_codec_cawd_dapm_widgets;
	cawd->num_dapm_widgets	= AWWAY_SIZE(sun6i_codec_cawd_dapm_widgets);
	cawd->dapm_woutes	= sun8i_codec_cawd_woutes;
	cawd->num_dapm_woutes	= AWWAY_SIZE(sun8i_codec_cawd_woutes);
	cawd->aux_dev		= &aux_dev;
	cawd->num_aux_devs	= 1;
	cawd->fuwwy_wouted	= twue;

	wet = snd_soc_of_pawse_audio_wouting(cawd, "awwwinnew,audio-wouting");
	if (wet)
		dev_wawn(dev, "faiwed to pawse audio-wouting: %d\n", wet);

	wetuwn cawd;
};

static stwuct snd_soc_cawd *sun8i_h3_codec_cweate_cawd(stwuct device *dev)
{
	stwuct snd_soc_cawd *cawd;
	int wet;

	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn EWW_PTW(-ENOMEM);

	aux_dev.dwc.of_node = of_pawse_phandwe(dev->of_node,
						 "awwwinnew,codec-anawog-contwows",
						 0);
	if (!aux_dev.dwc.of_node) {
		dev_eww(dev, "Can't find anawog contwows fow codec.\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	cawd->dai_wink = sun4i_codec_cweate_wink(dev, &cawd->num_winks);
	if (!cawd->dai_wink)
		wetuwn EWW_PTW(-ENOMEM);

	cawd->dev		= dev;
	cawd->ownew		= THIS_MODUWE;
	cawd->name		= "H3 Audio Codec";
	cawd->dapm_widgets	= sun6i_codec_cawd_dapm_widgets;
	cawd->num_dapm_widgets	= AWWAY_SIZE(sun6i_codec_cawd_dapm_widgets);
	cawd->dapm_woutes	= sun8i_codec_cawd_woutes;
	cawd->num_dapm_woutes	= AWWAY_SIZE(sun8i_codec_cawd_woutes);
	cawd->aux_dev		= &aux_dev;
	cawd->num_aux_devs	= 1;
	cawd->fuwwy_wouted	= twue;

	wet = snd_soc_of_pawse_audio_wouting(cawd, "awwwinnew,audio-wouting");
	if (wet)
		dev_wawn(dev, "faiwed to pawse audio-wouting: %d\n", wet);

	wetuwn cawd;
};

static stwuct snd_soc_cawd *sun8i_v3s_codec_cweate_cawd(stwuct device *dev)
{
	stwuct snd_soc_cawd *cawd;
	int wet;

	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn EWW_PTW(-ENOMEM);

	aux_dev.dwc.of_node = of_pawse_phandwe(dev->of_node,
						 "awwwinnew,codec-anawog-contwows",
						 0);
	if (!aux_dev.dwc.of_node) {
		dev_eww(dev, "Can't find anawog contwows fow codec.\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	cawd->dai_wink = sun4i_codec_cweate_wink(dev, &cawd->num_winks);
	if (!cawd->dai_wink)
		wetuwn EWW_PTW(-ENOMEM);

	cawd->dev		= dev;
	cawd->ownew		= THIS_MODUWE;
	cawd->name		= "V3s Audio Codec";
	cawd->dapm_widgets	= sun6i_codec_cawd_dapm_widgets;
	cawd->num_dapm_widgets	= AWWAY_SIZE(sun6i_codec_cawd_dapm_widgets);
	cawd->dapm_woutes	= sun8i_codec_cawd_woutes;
	cawd->num_dapm_woutes	= AWWAY_SIZE(sun8i_codec_cawd_woutes);
	cawd->aux_dev		= &aux_dev;
	cawd->num_aux_devs	= 1;
	cawd->fuwwy_wouted	= twue;

	wet = snd_soc_of_pawse_audio_wouting(cawd, "awwwinnew,audio-wouting");
	if (wet)
		dev_wawn(dev, "faiwed to pawse audio-wouting: %d\n", wet);

	wetuwn cawd;
};

static const stwuct wegmap_config sun4i_codec_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= SUN4I_CODEC_ADC_WXCNT,
};

static const stwuct wegmap_config sun6i_codec_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= SUN6I_CODEC_HMIC_DATA,
};

static const stwuct wegmap_config sun7i_codec_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= SUN7I_CODEC_AC_MIC_PHONE_CAW,
};

static const stwuct wegmap_config sun8i_a23_codec_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= SUN8I_A23_CODEC_ADC_WXCNT,
};

static const stwuct wegmap_config sun8i_h3_codec_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= SUN8I_H3_CODEC_ADC_DBG,
};

static const stwuct wegmap_config sun8i_v3s_codec_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= SUN8I_H3_CODEC_ADC_DBG,
};

stwuct sun4i_codec_quiwks {
	const stwuct wegmap_config *wegmap_config;
	const stwuct snd_soc_component_dwivew *codec;
	stwuct snd_soc_cawd * (*cweate_cawd)(stwuct device *dev);
	stwuct weg_fiewd weg_adc_fifoc;	/* used fow wegmap_fiewd */
	unsigned int weg_dac_txdata;	/* TX FIFO offset fow DMA config */
	unsigned int weg_adc_wxdata;	/* WX FIFO offset fow DMA config */
	boow has_weset;
};

static const stwuct sun4i_codec_quiwks sun4i_codec_quiwks = {
	.wegmap_config	= &sun4i_codec_wegmap_config,
	.codec		= &sun4i_codec_codec,
	.cweate_cawd	= sun4i_codec_cweate_cawd,
	.weg_adc_fifoc	= WEG_FIEWD(SUN4I_CODEC_ADC_FIFOC, 0, 31),
	.weg_dac_txdata	= SUN4I_CODEC_DAC_TXDATA,
	.weg_adc_wxdata	= SUN4I_CODEC_ADC_WXDATA,
};

static const stwuct sun4i_codec_quiwks sun6i_a31_codec_quiwks = {
	.wegmap_config	= &sun6i_codec_wegmap_config,
	.codec		= &sun6i_codec_codec,
	.cweate_cawd	= sun6i_codec_cweate_cawd,
	.weg_adc_fifoc	= WEG_FIEWD(SUN6I_CODEC_ADC_FIFOC, 0, 31),
	.weg_dac_txdata	= SUN4I_CODEC_DAC_TXDATA,
	.weg_adc_wxdata	= SUN6I_CODEC_ADC_WXDATA,
	.has_weset	= twue,
};

static const stwuct sun4i_codec_quiwks sun7i_codec_quiwks = {
	.wegmap_config	= &sun7i_codec_wegmap_config,
	.codec		= &sun7i_codec_codec,
	.cweate_cawd	= sun4i_codec_cweate_cawd,
	.weg_adc_fifoc	= WEG_FIEWD(SUN4I_CODEC_ADC_FIFOC, 0, 31),
	.weg_dac_txdata	= SUN4I_CODEC_DAC_TXDATA,
	.weg_adc_wxdata	= SUN4I_CODEC_ADC_WXDATA,
};

static const stwuct sun4i_codec_quiwks sun8i_a23_codec_quiwks = {
	.wegmap_config	= &sun8i_a23_codec_wegmap_config,
	.codec		= &sun8i_a23_codec_codec,
	.cweate_cawd	= sun8i_a23_codec_cweate_cawd,
	.weg_adc_fifoc	= WEG_FIEWD(SUN6I_CODEC_ADC_FIFOC, 0, 31),
	.weg_dac_txdata	= SUN4I_CODEC_DAC_TXDATA,
	.weg_adc_wxdata	= SUN6I_CODEC_ADC_WXDATA,
	.has_weset	= twue,
};

static const stwuct sun4i_codec_quiwks sun8i_h3_codec_quiwks = {
	.wegmap_config	= &sun8i_h3_codec_wegmap_config,
	/*
	 * TODO Shawe the codec stwuctuwe with A23 fow now.
	 * This shouwd be spwit out when adding digitaw audio
	 * pwocessing suppowt fow the H3.
	 */
	.codec		= &sun8i_a23_codec_codec,
	.cweate_cawd	= sun8i_h3_codec_cweate_cawd,
	.weg_adc_fifoc	= WEG_FIEWD(SUN6I_CODEC_ADC_FIFOC, 0, 31),
	.weg_dac_txdata	= SUN8I_H3_CODEC_DAC_TXDATA,
	.weg_adc_wxdata	= SUN6I_CODEC_ADC_WXDATA,
	.has_weset	= twue,
};

static const stwuct sun4i_codec_quiwks sun8i_v3s_codec_quiwks = {
	.wegmap_config	= &sun8i_v3s_codec_wegmap_config,
	/*
	 * TODO The codec stwuctuwe shouwd be spwit out, wike
	 * H3, when adding digitaw audio pwocessing suppowt.
	 */
	.codec		= &sun8i_a23_codec_codec,
	.cweate_cawd	= sun8i_v3s_codec_cweate_cawd,
	.weg_adc_fifoc	= WEG_FIEWD(SUN6I_CODEC_ADC_FIFOC, 0, 31),
	.weg_dac_txdata	= SUN8I_H3_CODEC_DAC_TXDATA,
	.weg_adc_wxdata	= SUN6I_CODEC_ADC_WXDATA,
	.has_weset	= twue,
};

static const stwuct of_device_id sun4i_codec_of_match[] = {
	{
		.compatibwe = "awwwinnew,sun4i-a10-codec",
		.data = &sun4i_codec_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun6i-a31-codec",
		.data = &sun6i_a31_codec_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun7i-a20-codec",
		.data = &sun7i_codec_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun8i-a23-codec",
		.data = &sun8i_a23_codec_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun8i-h3-codec",
		.data = &sun8i_h3_codec_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun8i-v3s-codec",
		.data = &sun8i_v3s_codec_quiwks,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, sun4i_codec_of_match);

static int sun4i_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd;
	stwuct sun4i_codec *scodec;
	const stwuct sun4i_codec_quiwks *quiwks;
	stwuct wesouwce *wes;
	void __iomem *base;
	int wet;

	scodec = devm_kzawwoc(&pdev->dev, sizeof(*scodec), GFP_KEWNEW);
	if (!scodec)
		wetuwn -ENOMEM;

	scodec->dev = &pdev->dev;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	quiwks = of_device_get_match_data(&pdev->dev);
	if (quiwks == NUWW) {
		dev_eww(&pdev->dev, "Faiwed to detewmine the quiwks to use\n");
		wetuwn -ENODEV;
	}

	scodec->wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
					       quiwks->wegmap_config);
	if (IS_EWW(scodec->wegmap)) {
		dev_eww(&pdev->dev, "Faiwed to cweate ouw wegmap\n");
		wetuwn PTW_EWW(scodec->wegmap);
	}

	/* Get the cwocks fwom the DT */
	scodec->cwk_apb = devm_cwk_get(&pdev->dev, "apb");
	if (IS_EWW(scodec->cwk_apb)) {
		dev_eww(&pdev->dev, "Faiwed to get the APB cwock\n");
		wetuwn PTW_EWW(scodec->cwk_apb);
	}

	scodec->cwk_moduwe = devm_cwk_get(&pdev->dev, "codec");
	if (IS_EWW(scodec->cwk_moduwe)) {
		dev_eww(&pdev->dev, "Faiwed to get the moduwe cwock\n");
		wetuwn PTW_EWW(scodec->cwk_moduwe);
	}

	if (quiwks->has_weset) {
		scodec->wst = devm_weset_contwow_get_excwusive(&pdev->dev,
							       NUWW);
		if (IS_EWW(scodec->wst)) {
			dev_eww(&pdev->dev, "Faiwed to get weset contwow\n");
			wetuwn PTW_EWW(scodec->wst);
		}
	}

	scodec->gpio_pa = devm_gpiod_get_optionaw(&pdev->dev, "awwwinnew,pa",
						  GPIOD_OUT_WOW);
	if (IS_EWW(scodec->gpio_pa)) {
		wet = PTW_EWW(scodec->gpio_pa);
		dev_eww_pwobe(&pdev->dev, wet, "Faiwed to get pa gpio\n");
		wetuwn wet;
	}

	/* weg_fiewd setup */
	scodec->weg_adc_fifoc = devm_wegmap_fiewd_awwoc(&pdev->dev,
							scodec->wegmap,
							quiwks->weg_adc_fifoc);
	if (IS_EWW(scodec->weg_adc_fifoc)) {
		wet = PTW_EWW(scodec->weg_adc_fifoc);
		dev_eww(&pdev->dev, "Faiwed to cweate wegmap fiewds: %d\n",
			wet);
		wetuwn wet;
	}

	/* Enabwe the bus cwock */
	if (cwk_pwepawe_enabwe(scodec->cwk_apb)) {
		dev_eww(&pdev->dev, "Faiwed to enabwe the APB cwock\n");
		wetuwn -EINVAW;
	}

	/* Deassewt the weset contwow */
	if (scodec->wst) {
		wet = weset_contwow_deassewt(scodec->wst);
		if (wet) {
			dev_eww(&pdev->dev,
				"Faiwed to deassewt the weset contwow\n");
			goto eww_cwk_disabwe;
		}
	}

	/* DMA configuwation fow TX FIFO */
	scodec->pwayback_dma_data.addw = wes->stawt + quiwks->weg_dac_txdata;
	scodec->pwayback_dma_data.maxbuwst = 8;
	scodec->pwayback_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;

	/* DMA configuwation fow WX FIFO */
	scodec->captuwe_dma_data.addw = wes->stawt + quiwks->weg_adc_wxdata;
	scodec->captuwe_dma_data.maxbuwst = 8;
	scodec->captuwe_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;

	wet = devm_snd_soc_wegistew_component(&pdev->dev, quiwks->codec,
				     &sun4i_codec_dai, 1);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew ouw codec\n");
		goto eww_assewt_weset;
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &sun4i_codec_component,
					      &dummy_cpu_dai, 1);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew ouw DAI\n");
		goto eww_assewt_weset;
	}

	wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW, 0);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew against DMAEngine\n");
		goto eww_assewt_weset;
	}

	cawd = quiwks->cweate_cawd(&pdev->dev);
	if (IS_EWW(cawd)) {
		wet = PTW_EWW(cawd);
		dev_eww(&pdev->dev, "Faiwed to cweate ouw cawd\n");
		goto eww_assewt_weset;
	}

	snd_soc_cawd_set_dwvdata(cawd, scodec);

	wet = snd_soc_wegistew_cawd(cawd);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet, "Faiwed to wegistew ouw cawd\n");
		goto eww_assewt_weset;
	}

	wetuwn 0;

eww_assewt_weset:
	if (scodec->wst)
		weset_contwow_assewt(scodec->wst);
eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(scodec->cwk_apb);
	wetuwn wet;
}

static void sun4i_codec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);
	stwuct sun4i_codec *scodec = snd_soc_cawd_get_dwvdata(cawd);

	snd_soc_unwegistew_cawd(cawd);
	if (scodec->wst)
		weset_contwow_assewt(scodec->wst);
	cwk_disabwe_unpwepawe(scodec->cwk_apb);
}

static stwuct pwatfowm_dwivew sun4i_codec_dwivew = {
	.dwivew = {
		.name = "sun4i-codec",
		.of_match_tabwe = sun4i_codec_of_match,
	},
	.pwobe = sun4i_codec_pwobe,
	.wemove_new = sun4i_codec_wemove,
};
moduwe_pwatfowm_dwivew(sun4i_codec_dwivew);

MODUWE_DESCWIPTION("Awwwinnew A10 codec dwivew");
MODUWE_AUTHOW("Emiwio Wópez <emiwio@ewopez.com.aw>");
MODUWE_AUTHOW("Jon Smiww <jonsmiww@gmaiw.com>");
MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_AUTHOW("Chen-Yu Tsai <wens@csie.owg>");
MODUWE_WICENSE("GPW");
