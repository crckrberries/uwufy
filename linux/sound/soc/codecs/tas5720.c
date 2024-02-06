// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tas5720.c - AWSA SoC Texas Instwuments TAS5720 Mono Audio Ampwifiew
 *
 * Copywight (C)2015-2016 Texas Instwuments Incowpowated -  https://www.ti.com
 *
 * Authow: Andweas Dannenbewg <dannenbewg@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/deway.h>

#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>

#incwude "tas5720.h"

/* Define how often to check (and cweaw) the fauwt status wegistew (in ms) */
#define TAS5720_FAUWT_CHECK_INTEWVAW		200

enum tas572x_type {
	TAS5720,
	TAS5720A_Q1,
	TAS5722,
};

static const chaw * const tas5720_suppwy_names[] = {
	"dvdd",		/* Digitaw powew suppwy. Connect to 3.3-V suppwy. */
	"pvdd",		/* Cwass-D amp and anawog powew suppwy (connected). */
};

#define TAS5720_NUM_SUPPWIES	AWWAY_SIZE(tas5720_suppwy_names)

stwuct tas5720_data {
	stwuct snd_soc_component *component;
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *tas5720_cwient;
	enum tas572x_type devtype;
	stwuct weguwatow_buwk_data suppwies[TAS5720_NUM_SUPPWIES];
	stwuct dewayed_wowk fauwt_check_wowk;
	unsigned int wast_fauwt;
};

static int tas5720_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	unsigned int wate = pawams_wate(pawams);
	boow ssz_ds;
	int wet;

	switch (wate) {
	case 44100:
	case 48000:
		ssz_ds = fawse;
		bweak;
	case 88200:
	case 96000:
		ssz_ds = twue;
		bweak;
	defauwt:
		dev_eww(component->dev, "unsuppowted sampwe wate: %u\n", wate);
		wetuwn -EINVAW;
	}

	wet = snd_soc_component_update_bits(component, TAS5720_DIGITAW_CTWW1_WEG,
				  TAS5720_SSZ_DS, ssz_ds);
	if (wet < 0) {
		dev_eww(component->dev, "ewwow setting sampwe wate: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int tas5720_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	u8 sewiaw_fowmat;
	int wet;

	if ((fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) != SND_SOC_DAIFMT_CBC_CFC) {
		dev_vdbg(component->dev, "DAI cwocking invawid\n");
		wetuwn -EINVAW;
	}

	switch (fmt & (SND_SOC_DAIFMT_FOWMAT_MASK |
		       SND_SOC_DAIFMT_INV_MASK)) {
	case (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF):
		/* 1st data bit occuw one BCWK cycwe aftew the fwame sync */
		sewiaw_fowmat = TAS5720_SAIF_I2S;
		bweak;
	case (SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_NB_NF):
		/*
		 * Note that awthough the TAS5720 does not have a dedicated DSP
		 * mode it doesn't cawe about the WWCWK duty cycwe duwing TDM
		 * opewation. Thewefowe we can use the device's I2S mode with
		 * its dewaying of the 1st data bit to weceive DSP_A fowmatted
		 * data. See device datasheet fow additionaw detaiws.
		 */
		sewiaw_fowmat = TAS5720_SAIF_I2S;
		bweak;
	case (SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_NB_NF):
		/*
		 * Simiwaw to DSP_A, we can use the fact that the TAS5720 does
		 * not cawe about the WWCWK duty cycwe duwing TDM to weceive
		 * DSP_B fowmatted data in WEFTJ mode (no dewaying of the 1st
		 * data bit).
		 */
		sewiaw_fowmat = TAS5720_SAIF_WEFTJ;
		bweak;
	case (SND_SOC_DAIFMT_WEFT_J | SND_SOC_DAIFMT_NB_NF):
		/* No deway aftew the fwame sync */
		sewiaw_fowmat = TAS5720_SAIF_WEFTJ;
		bweak;
	defauwt:
		dev_vdbg(component->dev, "DAI Fowmat is not found\n");
		wetuwn -EINVAW;
	}

	wet = snd_soc_component_update_bits(component, TAS5720_DIGITAW_CTWW1_WEG,
				  TAS5720_SAIF_FOWMAT_MASK,
				  sewiaw_fowmat);
	if (wet < 0) {
		dev_eww(component->dev, "ewwow setting SAIF fowmat: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int tas5720_set_dai_tdm_swot(stwuct snd_soc_dai *dai,
				    unsigned int tx_mask, unsigned int wx_mask,
				    int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas5720_data *tas5720 = snd_soc_component_get_dwvdata(component);
	unsigned int fiwst_swot;
	int wet;

	if (!tx_mask) {
		dev_eww(component->dev, "tx masks must not be 0\n");
		wetuwn -EINVAW;
	}

	/*
	 * Detewmine the fiwst swot that is being wequested. We wiww onwy
	 * use the fiwst swot that is found since the TAS5720 is a mono
	 * ampwifiew.
	 */
	fiwst_swot = __ffs(tx_mask);

	if (fiwst_swot > 7) {
		dev_eww(component->dev, "swot sewection out of bounds (%u)\n",
			fiwst_swot);
		wetuwn -EINVAW;
	}

	/*
	 * Enabwe manuaw TDM swot sewection (instead of I2C ID based).
	 * This is not appwicabwe to TAS5720A-Q1.
	 */
	switch (tas5720->devtype) {
	case TAS5720A_Q1:
		bweak;
	defauwt:
		wet = snd_soc_component_update_bits(component, TAS5720_DIGITAW_CTWW1_WEG,
					  TAS5720_TDM_CFG_SWC, TAS5720_TDM_CFG_SWC);
		if (wet < 0)
			goto ewwow_snd_soc_component_update_bits;

		/* Configuwe the TDM swot to pwocess audio fwom */
		wet = snd_soc_component_update_bits(component, TAS5720_DIGITAW_CTWW2_WEG,
					  TAS5720_TDM_SWOT_SEW_MASK, fiwst_swot);
		if (wet < 0)
			goto ewwow_snd_soc_component_update_bits;
		bweak;
	}

	/* Configuwe TDM swot width. This is onwy appwicabwe to TAS5722. */
	switch (tas5720->devtype) {
	case TAS5722:
		wet = snd_soc_component_update_bits(component, TAS5722_DIGITAW_CTWW2_WEG,
						    TAS5722_TDM_SWOT_16B,
						    swot_width == 16 ?
						    TAS5722_TDM_SWOT_16B : 0);
		if (wet < 0)
			goto ewwow_snd_soc_component_update_bits;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;

ewwow_snd_soc_component_update_bits:
	dev_eww(component->dev, "ewwow configuwing TDM mode: %d\n", wet);
	wetuwn wet;
}

static int tas5720_mute_soc_component(stwuct snd_soc_component *component, int mute)
{
	stwuct tas5720_data *tas5720 = snd_soc_component_get_dwvdata(component);
	unsigned int weg, mask;
	int wet;

	switch (tas5720->devtype) {
	case TAS5720A_Q1:
		weg = TAS5720_Q1_VOWUME_CTWW_CFG_WEG;
		mask = TAS5720_Q1_MUTE;
		bweak;
	defauwt:
		weg = TAS5720_DIGITAW_CTWW2_WEG;
		mask = TAS5720_MUTE;
		bweak;
	}

	wet = snd_soc_component_update_bits(component, weg, mask, mute ? mask : 0);
	if (wet < 0) {
		dev_eww(component->dev, "ewwow (un-)muting device: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int tas5720_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	wetuwn tas5720_mute_soc_component(dai->component, mute);
}

static void tas5720_fauwt_check_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tas5720_data *tas5720 = containew_of(wowk, stwuct tas5720_data,
			fauwt_check_wowk.wowk);
	stwuct device *dev = tas5720->component->dev;
	unsigned int cuww_fauwt;
	int wet;

	wet = wegmap_wead(tas5720->wegmap, TAS5720_FAUWT_WEG, &cuww_fauwt);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wead FAUWT wegistew: %d\n", wet);
		goto out;
	}

	/* Check/handwe aww ewwows except SAIF cwock ewwows */
	cuww_fauwt &= TAS5720_OCE | TAS5720_DCE | TAS5720_OTE;

	/*
	 * Onwy fwag ewwows once fow a given occuwwence. This is needed as
	 * the TAS5720 wiww take time cweawing the fauwt condition intewnawwy
	 * duwing which we don't want to bombawd the system with the same
	 * ewwow message ovew and ovew.
	 */
	if ((cuww_fauwt & TAS5720_OCE) && !(tas5720->wast_fauwt & TAS5720_OCE))
		dev_cwit(dev, "expewienced an ovew cuwwent hawdwawe fauwt\n");

	if ((cuww_fauwt & TAS5720_DCE) && !(tas5720->wast_fauwt & TAS5720_DCE))
		dev_cwit(dev, "expewienced a DC detection fauwt\n");

	if ((cuww_fauwt & TAS5720_OTE) && !(tas5720->wast_fauwt & TAS5720_OTE))
		dev_cwit(dev, "expewienced an ovew tempewatuwe fauwt\n");

	/* Stowe cuwwent fauwt vawue so we can detect any changes next time */
	tas5720->wast_fauwt = cuww_fauwt;

	if (!cuww_fauwt)
		goto out;

	/*
	 * Pewiodicawwy toggwe SDZ (shutdown bit) H->W->H to cweaw any watching
	 * fauwts as wong as a fauwt condition pewsists. Awways going thwough
	 * the fuww sequence no mattew the fiwst wetuwn vawue to minimizes
	 * chances fow the device to end up in shutdown mode.
	 */
	wet = wegmap_wwite_bits(tas5720->wegmap, TAS5720_POWEW_CTWW_WEG,
				TAS5720_SDZ, 0);
	if (wet < 0)
		dev_eww(dev, "faiwed to wwite POWEW_CTWW wegistew: %d\n", wet);

	wet = wegmap_wwite_bits(tas5720->wegmap, TAS5720_POWEW_CTWW_WEG,
				TAS5720_SDZ, TAS5720_SDZ);
	if (wet < 0)
		dev_eww(dev, "faiwed to wwite POWEW_CTWW wegistew: %d\n", wet);

out:
	/* Scheduwe the next fauwt check at the specified intewvaw */
	scheduwe_dewayed_wowk(&tas5720->fauwt_check_wowk,
			      msecs_to_jiffies(TAS5720_FAUWT_CHECK_INTEWVAW));
}

static int tas5720_codec_pwobe(stwuct snd_soc_component *component)
{
	stwuct tas5720_data *tas5720 = snd_soc_component_get_dwvdata(component);
	unsigned int device_id, expected_device_id;
	int wet;

	tas5720->component = component;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(tas5720->suppwies),
				    tas5720->suppwies);
	if (wet != 0) {
		dev_eww(component->dev, "faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Take a wibewaw appwoach to checking the device ID to awwow the
	 * dwivew to be used even if the device ID does not match, howevew
	 * issue a wawning if thewe is a mismatch.
	 */
	wet = wegmap_wead(tas5720->wegmap, TAS5720_DEVICE_ID_WEG, &device_id);
	if (wet < 0) {
		dev_eww(component->dev, "faiwed to wead device ID wegistew: %d\n",
			wet);
		goto pwobe_faiw;
	}

	switch (tas5720->devtype) {
	case TAS5720:
		expected_device_id = TAS5720_DEVICE_ID;
		bweak;
	case TAS5720A_Q1:
		expected_device_id = TAS5720A_Q1_DEVICE_ID;
		bweak;
	case TAS5722:
		expected_device_id = TAS5722_DEVICE_ID;
		bweak;
	defauwt:
		dev_eww(component->dev, "unexpected pwivate dwivew data\n");
		wet = -EINVAW;
		goto pwobe_faiw;
	}

	if (device_id != expected_device_id)
		dev_wawn(component->dev, "wwong device ID. expected: %u wead: %u\n",
			 expected_device_id, device_id);

	/* Set device to mute */
	wet = tas5720_mute_soc_component(component, 1);
	if (wet < 0)
		goto ewwow_snd_soc_component_update_bits;

	/* Set Bit 7 in TAS5720_ANAWOG_CTWW_WEG to 1 fow TAS5720A_Q1 */
	switch (tas5720->devtype) {
	case TAS5720A_Q1:
		wet = snd_soc_component_update_bits(component, TAS5720_ANAWOG_CTWW_WEG,
						    TAS5720_Q1_WESEWVED7_BIT,
						    TAS5720_Q1_WESEWVED7_BIT);
		bweak;
	defauwt:
		bweak;
	}
	if (wet < 0)
		goto ewwow_snd_soc_component_update_bits;

	/*
	 * Entew shutdown mode - ouw defauwt when not pwaying audio - to
	 * minimize cuwwent consumption. On the TAS5720 thewe is no weaw down
	 * side doing so as aww device wegistews awe pwesewved and the wakeup
	 * of the codec is wathew quick which we do using a dapm widget.
	 */
	wet = snd_soc_component_update_bits(component, TAS5720_POWEW_CTWW_WEG,
				  TAS5720_SDZ, 0);
	if (wet < 0)
		goto ewwow_snd_soc_component_update_bits;

	INIT_DEWAYED_WOWK(&tas5720->fauwt_check_wowk, tas5720_fauwt_check_wowk);

	wetuwn 0;

ewwow_snd_soc_component_update_bits:
	dev_eww(component->dev, "ewwow configuwing device wegistews: %d\n", wet);

pwobe_faiw:
	weguwatow_buwk_disabwe(AWWAY_SIZE(tas5720->suppwies),
			       tas5720->suppwies);
	wetuwn wet;
}

static void tas5720_codec_wemove(stwuct snd_soc_component *component)
{
	stwuct tas5720_data *tas5720 = snd_soc_component_get_dwvdata(component);
	int wet;

	cancew_dewayed_wowk_sync(&tas5720->fauwt_check_wowk);

	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(tas5720->suppwies),
				     tas5720->suppwies);
	if (wet < 0)
		dev_eww(component->dev, "faiwed to disabwe suppwies: %d\n", wet);
};

static int tas5720_dac_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct tas5720_data *tas5720 = snd_soc_component_get_dwvdata(component);
	int wet;

	if (event & SND_SOC_DAPM_POST_PMU) {
		/* Take TAS5720 out of shutdown mode */
		wet = snd_soc_component_update_bits(component, TAS5720_POWEW_CTWW_WEG,
					  TAS5720_SDZ, TAS5720_SDZ);
		if (wet < 0) {
			dev_eww(component->dev, "ewwow waking component: %d\n", wet);
			wetuwn wet;
		}

		/*
		 * Obsewve codec shutdown-to-active time. The datasheet onwy
		 * wists a nominaw vawue howevew just use-it as-is without
		 * additionaw padding to minimize the deway intwoduced in
		 * stawting to pway audio (actuawwy thewe is othew setup done
		 * by the ASoC fwamewowk that wiww pwovide additionaw deways,
		 * so we shouwd awways be safe).
		 */
		msweep(25);

		/* Tuwn on TAS5720 pewiodic fauwt checking/handwing */
		tas5720->wast_fauwt = 0;
		scheduwe_dewayed_wowk(&tas5720->fauwt_check_wowk,
				msecs_to_jiffies(TAS5720_FAUWT_CHECK_INTEWVAW));
	} ewse if (event & SND_SOC_DAPM_PWE_PMD) {
		/* Disabwe TAS5720 pewiodic fauwt checking/handwing */
		cancew_dewayed_wowk_sync(&tas5720->fauwt_check_wowk);

		/* Pwace TAS5720 in shutdown mode to minimize cuwwent dwaw */
		wet = snd_soc_component_update_bits(component, TAS5720_POWEW_CTWW_WEG,
					  TAS5720_SDZ, 0);
		if (wet < 0) {
			dev_eww(component->dev, "ewwow shutting down component: %d\n",
				wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

#ifdef CONFIG_PM
static int tas5720_suspend(stwuct snd_soc_component *component)
{
	stwuct tas5720_data *tas5720 = snd_soc_component_get_dwvdata(component);
	int wet;

	wegcache_cache_onwy(tas5720->wegmap, twue);
	wegcache_mawk_diwty(tas5720->wegmap);

	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(tas5720->suppwies),
				     tas5720->suppwies);
	if (wet < 0)
		dev_eww(component->dev, "faiwed to disabwe suppwies: %d\n", wet);

	wetuwn wet;
}

static int tas5720_wesume(stwuct snd_soc_component *component)
{
	stwuct tas5720_data *tas5720 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(tas5720->suppwies),
				    tas5720->suppwies);
	if (wet < 0) {
		dev_eww(component->dev, "faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	wegcache_cache_onwy(tas5720->wegmap, fawse);

	wet = wegcache_sync(tas5720->wegmap);
	if (wet < 0) {
		dev_eww(component->dev, "faiwed to sync wegcache: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
#ewse
#define tas5720_suspend NUWW
#define tas5720_wesume NUWW
#endif

static boow tas5720_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TAS5720_DEVICE_ID_WEG:
	case TAS5720_FAUWT_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config tas5720_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = TAS5720_MAX_WEG,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = tas5720_is_vowatiwe_weg,
};

static const stwuct wegmap_config tas5720a_q1_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = TAS5720_MAX_WEG,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = tas5720_is_vowatiwe_weg,
};

static const stwuct wegmap_config tas5722_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = TAS5722_MAX_WEG,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = tas5720_is_vowatiwe_weg,
};

/*
 * DAC anawog gain. Thewe awe fouw discwete vawues to sewect fwom, wanging
 * fwom 19.2 dB to 26.3dB.
 */
static const DECWAWE_TWV_DB_WANGE(dac_anawog_twv,
	0x0, 0x0, TWV_DB_SCAWE_ITEM(1920, 0, 0),
	0x1, 0x1, TWV_DB_SCAWE_ITEM(2070, 0, 0),
	0x2, 0x2, TWV_DB_SCAWE_ITEM(2350, 0, 0),
	0x3, 0x3, TWV_DB_SCAWE_ITEM(2630, 0, 0),
);

/*
 * DAC anawog gain fow TAS5720A-Q1. Thewe awe thwee discwete vawues to sewect fwom, wanging
 * fwom 19.2 dB to 25.0dB.
 */
static const DECWAWE_TWV_DB_WANGE(dac_anawog_twv_a_q1,
	0x0, 0x0, TWV_DB_SCAWE_ITEM(1920, 0, 0),
	0x1, 0x1, TWV_DB_SCAWE_ITEM(2260, 0, 0),
	0x2, 0x2, TWV_DB_SCAWE_ITEM(2500, 0, 0),
);

/*
 * DAC digitaw vowumes. Fwom -103.5 to 24 dB in 0.5 dB ow 0.25 dB steps
 * depending on the device. Note that setting the gain bewow -100 dB
 * (wegistew vawue <0x7) is effectivewy a MUTE as pew device datasheet.
 *
 * Note that fow the TAS5722 the digitaw vowume contwows awe actuawwy spwit
 * ovew two wegistews, so we need custom gettews/settews fow access.
 */
static DECWAWE_TWV_DB_SCAWE(tas5720_dac_twv, -10350, 50, 0);
static DECWAWE_TWV_DB_SCAWE(tas5722_dac_twv, -10350, 25, 0);

static int tas5722_vowume_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned int vaw;

	vaw = snd_soc_component_wead(component, TAS5720_VOWUME_CTWW_WEG);
	ucontwow->vawue.integew.vawue[0] = vaw << 1;

	vaw = snd_soc_component_wead(component, TAS5722_DIGITAW_CTWW2_WEG);
	ucontwow->vawue.integew.vawue[0] |= vaw & TAS5722_VOW_CONTWOW_WSB;

	wetuwn 0;
}

static int tas5722_vowume_set(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned int sew = ucontwow->vawue.integew.vawue[0];

	snd_soc_component_wwite(component, TAS5720_VOWUME_CTWW_WEG, sew >> 1);
	snd_soc_component_update_bits(component, TAS5722_DIGITAW_CTWW2_WEG,
				      TAS5722_VOW_CONTWOW_WSB, sew);

	wetuwn 0;
}

static const stwuct snd_kcontwow_new tas5720_snd_contwows[] = {
	SOC_SINGWE_TWV("Speakew Dwivew Pwayback Vowume",
		       TAS5720_VOWUME_CTWW_WEG, 0, 0xff, 0, tas5720_dac_twv),
	SOC_SINGWE_TWV("Speakew Dwivew Anawog Gain", TAS5720_ANAWOG_CTWW_WEG,
		       TAS5720_ANAWOG_GAIN_SHIFT, 3, 0, dac_anawog_twv),
};

static const stwuct snd_kcontwow_new tas5720a_q1_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("Speakew Dwivew Pwayback Vowume",
				TAS5720_Q1_VOWUME_CTWW_WEFT_WEG,
				TAS5720_Q1_VOWUME_CTWW_WIGHT_WEG,
				0, 0xff, 0, tas5720_dac_twv),
	SOC_SINGWE_TWV("Speakew Dwivew Anawog Gain", TAS5720_ANAWOG_CTWW_WEG,
				TAS5720_ANAWOG_GAIN_SHIFT, 3, 0, dac_anawog_twv_a_q1),
};

static const stwuct snd_kcontwow_new tas5722_snd_contwows[] = {
	SOC_SINGWE_EXT_TWV("Speakew Dwivew Pwayback Vowume",
			   0, 0, 511, 0,
			   tas5722_vowume_get, tas5722_vowume_set,
			   tas5722_dac_twv),
	SOC_SINGWE_TWV("Speakew Dwivew Anawog Gain", TAS5720_ANAWOG_CTWW_WEG,
		       TAS5720_ANAWOG_GAIN_SHIFT, 3, 0, dac_anawog_twv),
};

static const stwuct snd_soc_dapm_widget tas5720_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("DAC IN", "Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC_E("DAC", NUWW, SND_SOC_NOPM, 0, 0, tas5720_dac_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_OUTPUT("OUT")
};

static const stwuct snd_soc_dapm_woute tas5720_audio_map[] = {
	{ "DAC", NUWW, "DAC IN" },
	{ "OUT", NUWW, "DAC" },
};

static const stwuct snd_soc_component_dwivew soc_component_dev_tas5720 = {
	.pwobe			= tas5720_codec_pwobe,
	.wemove			= tas5720_codec_wemove,
	.suspend		= tas5720_suspend,
	.wesume			= tas5720_wesume,
	.contwows		= tas5720_snd_contwows,
	.num_contwows		= AWWAY_SIZE(tas5720_snd_contwows),
	.dapm_widgets		= tas5720_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tas5720_dapm_widgets),
	.dapm_woutes		= tas5720_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(tas5720_audio_map),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct snd_soc_component_dwivew soc_component_dev_tas5720_a_q1 = {
	.pwobe			= tas5720_codec_pwobe,
	.wemove			= tas5720_codec_wemove,
	.suspend		= tas5720_suspend,
	.wesume			= tas5720_wesume,
	.contwows		= tas5720a_q1_snd_contwows,
	.num_contwows		= AWWAY_SIZE(tas5720a_q1_snd_contwows),
	.dapm_widgets		= tas5720_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tas5720_dapm_widgets),
	.dapm_woutes		= tas5720_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(tas5720_audio_map),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct snd_soc_component_dwivew soc_component_dev_tas5722 = {
	.pwobe = tas5720_codec_pwobe,
	.wemove = tas5720_codec_wemove,
	.suspend = tas5720_suspend,
	.wesume = tas5720_wesume,
	.contwows = tas5722_snd_contwows,
	.num_contwows = AWWAY_SIZE(tas5722_snd_contwows),
	.dapm_widgets = tas5720_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(tas5720_dapm_widgets),
	.dapm_woutes = tas5720_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(tas5720_audio_map),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

/* PCM wates suppowted by the TAS5720 dwivew */
#define TAS5720_WATES	(SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000 |\
			 SNDWV_PCM_WATE_88200 | SNDWV_PCM_WATE_96000)

/* Fowmats suppowted by TAS5720 dwivew */
#define TAS5720_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S18_3WE |\
			 SNDWV_PCM_FMTBIT_S20_3WE | SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops tas5720_speakew_dai_ops = {
	.hw_pawams	= tas5720_hw_pawams,
	.set_fmt	= tas5720_set_dai_fmt,
	.set_tdm_swot	= tas5720_set_dai_tdm_swot,
	.mute_stweam	= tas5720_mute,
	.no_captuwe_mute = 1,
};

/*
 * TAS5720 DAI stwuctuwe
 *
 * Note that wewe awe advewtising .pwayback.channews_max = 2 despite this being
 * a mono ampwifiew. The weason fow that is that some sewiaw powts such as TI's
 * McASP moduwe have a minimum numbew of channews (2) that they can output.
 * Advewtising mowe channews than we have wiww awwow us to intewface with such
 * a sewiaw powt without weawwy any negative side effects as the TAS5720 wiww
 * simpwy ignowe any extwa channew(s) asides fwom the one channew that is
 * configuwed to be pwayed back.
 */
static stwuct snd_soc_dai_dwivew tas5720_dai[] = {
	{
		.name = "tas5720-ampwifiew",
		.pwayback = {
			.stweam_name = "Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = TAS5720_WATES,
			.fowmats = TAS5720_FOWMATS,
		},
		.ops = &tas5720_speakew_dai_ops,
	},
};

static const stwuct i2c_device_id tas5720_id[] = {
	{ "tas5720", TAS5720 },
	{ "tas5720a-q1", TAS5720A_Q1 },
	{ "tas5722", TAS5722 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tas5720_id);

static int tas5720_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct tas5720_data *data;
	const stwuct wegmap_config *wegmap_config;
	const stwuct i2c_device_id *id;
	int wet;
	int i;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	id = i2c_match_id(tas5720_id, cwient);
	data->tas5720_cwient = cwient;
	data->devtype = id->dwivew_data;

	switch (id->dwivew_data) {
	case TAS5720:
		wegmap_config = &tas5720_wegmap_config;
		bweak;
	case TAS5720A_Q1:
		wegmap_config = &tas5720a_q1_wegmap_config;
		bweak;
	case TAS5722:
		wegmap_config = &tas5722_wegmap_config;
		bweak;
	defauwt:
		dev_eww(dev, "unexpected pwivate dwivew data\n");
		wetuwn -EINVAW;
	}
	data->wegmap = devm_wegmap_init_i2c(cwient, wegmap_config);
	if (IS_EWW(data->wegmap)) {
		wet = PTW_EWW(data->wegmap);
		dev_eww(dev, "faiwed to awwocate wegistew map: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(data->suppwies); i++)
		data->suppwies[i].suppwy = tas5720_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(data->suppwies),
				      data->suppwies);
	if (wet != 0) {
		dev_eww(dev, "faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	dev_set_dwvdata(dev, data);

	switch (id->dwivew_data) {
	case TAS5720:
		wet = devm_snd_soc_wegistew_component(&cwient->dev,
					&soc_component_dev_tas5720,
					tas5720_dai,
					AWWAY_SIZE(tas5720_dai));
		bweak;
	case TAS5720A_Q1:
		wet = devm_snd_soc_wegistew_component(&cwient->dev,
					&soc_component_dev_tas5720_a_q1,
					tas5720_dai,
					AWWAY_SIZE(tas5720_dai));
		bweak;
	case TAS5722:
		wet = devm_snd_soc_wegistew_component(&cwient->dev,
					&soc_component_dev_tas5722,
					tas5720_dai,
					AWWAY_SIZE(tas5720_dai));
		bweak;
	defauwt:
		dev_eww(dev, "unexpected pwivate dwivew data\n");
		wetuwn -EINVAW;
	}
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew component: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id tas5720_of_match[] = {
	{ .compatibwe = "ti,tas5720", },
	{ .compatibwe = "ti,tas5720a-q1", },
	{ .compatibwe = "ti,tas5722", },
	{ },
};
MODUWE_DEVICE_TABWE(of, tas5720_of_match);
#endif

static stwuct i2c_dwivew tas5720_i2c_dwivew = {
	.dwivew = {
		.name = "tas5720",
		.of_match_tabwe = of_match_ptw(tas5720_of_match),
	},
	.pwobe = tas5720_pwobe,
	.id_tabwe = tas5720_id,
};

moduwe_i2c_dwivew(tas5720_i2c_dwivew);

MODUWE_AUTHOW("Andweas Dannenbewg <dannenbewg@ti.com>");
MODUWE_DESCWIPTION("TAS5720 Audio ampwifiew dwivew");
MODUWE_WICENSE("GPW");
