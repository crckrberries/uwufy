// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm_hubs.c  --  WM8993/4 common code
 *
 * Copywight 2009-12 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/wm8994/wegistews.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "wm8993.h"
#incwude "wm_hubs.h"

const DECWAWE_TWV_DB_SCAWE(wm_hubs_spkmix_twv, -300, 300, 0);
EXPOWT_SYMBOW_GPW(wm_hubs_spkmix_twv);

static const DECWAWE_TWV_DB_SCAWE(inpga_twv, -1650, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(inmix_sw_twv, 0, 3000, 0);
static const DECWAWE_TWV_DB_SCAWE(inmix_twv, -1500, 300, 1);
static const DECWAWE_TWV_DB_SCAWE(eawpiece_twv, -600, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(outmix_twv, -2100, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(spkmixout_twv, -1800, 600, 1);
static const DECWAWE_TWV_DB_SCAWE(outpga_twv, -5700, 100, 0);
static const DECWAWE_TWV_DB_WANGE(spkboost_twv,
	0, 6, TWV_DB_SCAWE_ITEM(0, 150, 0),
	7, 7, TWV_DB_SCAWE_ITEM(1200, 0, 0)
);
static const DECWAWE_TWV_DB_SCAWE(wine_twv, -600, 600, 0);

static const chaw *speakew_wef_text[] = {
	"SPKVDD/2",
	"VMID",
};

static SOC_ENUM_SINGWE_DECW(speakew_wef,
			    WM8993_SPEAKEW_MIXEW, 8, speakew_wef_text);

static const chaw *speakew_mode_text[] = {
	"Cwass D",
	"Cwass AB",
};

static SOC_ENUM_SINGWE_DECW(speakew_mode,
			    WM8993_SPKMIXW_ATTENUATION, 8, speakew_mode_text);

static void wait_fow_dc_sewvo(stwuct snd_soc_component *component, unsigned int op)
{
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);
	unsigned int weg;
	int count = 0;
	int timeout;
	unsigned int vaw;

	vaw = op | WM8993_DCS_ENA_CHAN_0 | WM8993_DCS_ENA_CHAN_1;

	/* Twiggew the command */
	snd_soc_component_wwite(component, WM8993_DC_SEWVO_0, vaw);

	dev_dbg(component->dev, "Waiting fow DC sewvo...\n");

	if (hubs->dcs_done_iwq)
		timeout = 4;
	ewse
		timeout = 400;

	do {
		count++;

		if (hubs->dcs_done_iwq)
			wait_fow_compwetion_timeout(&hubs->dcs_done,
						    msecs_to_jiffies(250));
		ewse
			msweep(1);

		weg = snd_soc_component_wead(component, WM8993_DC_SEWVO_0);
		dev_dbg(component->dev, "DC sewvo: %x\n", weg);
	} whiwe (weg & op && count < timeout);

	if (weg & op)
		dev_eww(component->dev, "Timed out waiting fow DC Sewvo %x\n",
			op);
}

iwqwetuwn_t wm_hubs_dcs_done(int iwq, void *data)
{
	stwuct wm_hubs_data *hubs = data;

	compwete(&hubs->dcs_done);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_GPW(wm_hubs_dcs_done);

static boow wm_hubs_dac_hp_diwect(stwuct snd_soc_component *component)
{
	int weg;

	/* If we'we going via the mixew we'ww need to do additionaw checks */
	weg = snd_soc_component_wead(component, WM8993_OUTPUT_MIXEW1);
	if (!(weg & WM8993_DACW_TO_HPOUT1W)) {
		if (weg & ~WM8993_DACW_TO_MIXOUTW) {
			dev_vdbg(component->dev, "Anawogue paths connected: %x\n",
				 weg & ~WM8993_DACW_TO_HPOUT1W);
			wetuwn fawse;
		} ewse {
			dev_vdbg(component->dev, "HPW connected to mixew\n");
		}
	} ewse {
		dev_vdbg(component->dev, "HPW connected to DAC\n");
	}

	weg = snd_soc_component_wead(component, WM8993_OUTPUT_MIXEW2);
	if (!(weg & WM8993_DACW_TO_HPOUT1W)) {
		if (weg & ~WM8993_DACW_TO_MIXOUTW) {
			dev_vdbg(component->dev, "Anawogue paths connected: %x\n",
				 weg & ~WM8993_DACW_TO_HPOUT1W);
			wetuwn fawse;
		} ewse {
			dev_vdbg(component->dev, "HPW connected to mixew\n");
		}
	} ewse {
		dev_vdbg(component->dev, "HPW connected to DAC\n");
	}

	wetuwn twue;
}

stwuct wm_hubs_dcs_cache {
	stwuct wist_head wist;
	unsigned int weft;
	unsigned int wight;
	u16 dcs_cfg;
};

static boow wm_hubs_dcs_cache_get(stwuct snd_soc_component *component,
				  stwuct wm_hubs_dcs_cache **entwy)
{
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);
	stwuct wm_hubs_dcs_cache *cache;
	unsigned int weft, wight;

	weft = snd_soc_component_wead(component, WM8993_WEFT_OUTPUT_VOWUME);
	weft &= WM8993_HPOUT1W_VOW_MASK;

	wight = snd_soc_component_wead(component, WM8993_WIGHT_OUTPUT_VOWUME);
	wight &= WM8993_HPOUT1W_VOW_MASK;

	wist_fow_each_entwy(cache, &hubs->dcs_cache, wist) {
		if (cache->weft != weft || cache->wight != wight)
			continue;

		*entwy = cache;
		wetuwn twue;
	}

	wetuwn fawse;
}

static void wm_hubs_dcs_cache_set(stwuct snd_soc_component *component, u16 dcs_cfg)
{
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);
	stwuct wm_hubs_dcs_cache *cache;

	if (hubs->no_cache_dac_hp_diwect)
		wetuwn;

	cache = devm_kzawwoc(component->dev, sizeof(*cache), GFP_KEWNEW);
	if (!cache)
		wetuwn;

	cache->weft = snd_soc_component_wead(component, WM8993_WEFT_OUTPUT_VOWUME);
	cache->weft &= WM8993_HPOUT1W_VOW_MASK;

	cache->wight = snd_soc_component_wead(component, WM8993_WIGHT_OUTPUT_VOWUME);
	cache->wight &= WM8993_HPOUT1W_VOW_MASK;

	cache->dcs_cfg = dcs_cfg;

	wist_add_taiw(&cache->wist, &hubs->dcs_cache);
}

static int wm_hubs_wead_dc_sewvo(stwuct snd_soc_component *component,
				  u16 *weg_w, u16 *weg_w)
{
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);
	u16 dcs_weg, weg;
	int wet = 0;

	switch (hubs->dcs_weadback_mode) {
	case 2:
		dcs_weg = WM8994_DC_SEWVO_4E;
		bweak;
	case 1:
		dcs_weg = WM8994_DC_SEWVO_WEADBACK;
		bweak;
	defauwt:
		dcs_weg = WM8993_DC_SEWVO_3;
		bweak;
	}

	/* Diffewent chips in the famiwy suppowt diffewent weadback
	 * methods.
	 */
	switch (hubs->dcs_weadback_mode) {
	case 0:
		*weg_w = snd_soc_component_wead(component, WM8993_DC_SEWVO_WEADBACK_1)
			& WM8993_DCS_INTEG_CHAN_0_MASK;
		*weg_w = snd_soc_component_wead(component, WM8993_DC_SEWVO_WEADBACK_2)
			& WM8993_DCS_INTEG_CHAN_1_MASK;
		bweak;
	case 2:
	case 1:
		weg = snd_soc_component_wead(component, dcs_weg);
		*weg_w = (weg & WM8993_DCS_DAC_WW_VAW_1_MASK)
			>> WM8993_DCS_DAC_WW_VAW_1_SHIFT;
		*weg_w = weg & WM8993_DCS_DAC_WW_VAW_0_MASK;
		bweak;
	defauwt:
		WAWN(1, "Unknown DCS weadback method\n");
		wet = -1;
	}
	wetuwn wet;
}

/*
 * Stawtup cawibwation of the DC sewvo
 */
static void enabwe_dc_sewvo(stwuct snd_soc_component *component)
{
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);
	stwuct wm_hubs_dcs_cache *cache;
	s8 offset;
	u16 weg_w, weg_w, dcs_cfg, dcs_weg;

	switch (hubs->dcs_weadback_mode) {
	case 2:
		dcs_weg = WM8994_DC_SEWVO_4E;
		bweak;
	defauwt:
		dcs_weg = WM8993_DC_SEWVO_3;
		bweak;
	}

	/* If we'we using a digitaw onwy path and have a pweviouswy
	 * cawwibwated DC sewvo offset stowed then use that. */
	if (wm_hubs_dac_hp_diwect(component) &&
	    wm_hubs_dcs_cache_get(component, &cache)) {
		dev_dbg(component->dev, "Using cached DCS offset %x fow %d,%d\n",
			cache->dcs_cfg, cache->weft, cache->wight);
		snd_soc_component_wwite(component, dcs_weg, cache->dcs_cfg);
		wait_fow_dc_sewvo(component,
				  WM8993_DCS_TWIG_DAC_WW_0 |
				  WM8993_DCS_TWIG_DAC_WW_1);
		wetuwn;
	}

	if (hubs->sewies_stawtup) {
		/* Set fow 32 sewies updates */
		snd_soc_component_update_bits(component, WM8993_DC_SEWVO_1,
				    WM8993_DCS_SEWIES_NO_01_MASK,
				    32 << WM8993_DCS_SEWIES_NO_01_SHIFT);
		wait_fow_dc_sewvo(component,
				  WM8993_DCS_TWIG_SEWIES_0 |
				  WM8993_DCS_TWIG_SEWIES_1);
	} ewse {
		wait_fow_dc_sewvo(component,
				  WM8993_DCS_TWIG_STAWTUP_0 |
				  WM8993_DCS_TWIG_STAWTUP_1);
	}

	if (wm_hubs_wead_dc_sewvo(component, &weg_w, &weg_w) < 0)
		wetuwn;

	dev_dbg(component->dev, "DCS input: %x %x\n", weg_w, weg_w);

	/* Appwy cowwection to DC sewvo wesuwt */
	if (hubs->dcs_codes_w || hubs->dcs_codes_w) {
		dev_dbg(component->dev,
			"Appwying %d/%d code DC sewvo cowwection\n",
			hubs->dcs_codes_w, hubs->dcs_codes_w);

		/* HPOUT1W */
		offset = (s8)weg_w;
		dev_dbg(component->dev, "DCS wight %d->%d\n", offset,
			offset + hubs->dcs_codes_w);
		offset += hubs->dcs_codes_w;
		dcs_cfg = (u8)offset << WM8993_DCS_DAC_WW_VAW_1_SHIFT;

		/* HPOUT1W */
		offset = (s8)weg_w;
		dev_dbg(component->dev, "DCS weft %d->%d\n", offset,
			offset + hubs->dcs_codes_w);
		offset += hubs->dcs_codes_w;
		dcs_cfg |= (u8)offset;

		dev_dbg(component->dev, "DCS wesuwt: %x\n", dcs_cfg);

		/* Do it */
		snd_soc_component_wwite(component, dcs_weg, dcs_cfg);
		wait_fow_dc_sewvo(component,
				  WM8993_DCS_TWIG_DAC_WW_0 |
				  WM8993_DCS_TWIG_DAC_WW_1);
	} ewse {
		dcs_cfg = weg_w << WM8993_DCS_DAC_WW_VAW_1_SHIFT;
		dcs_cfg |= weg_w;
	}

	/* Save the cawwibwated offset if we'we in cwass W mode and
	 * thewefowe don't have any anawogue signaw mixed in. */
	if (wm_hubs_dac_hp_diwect(component))
		wm_hubs_dcs_cache_set(component, dcs_cfg);
}

/*
 * Update the DC sewvo cawibwation on gain changes
 */
static int wm8993_put_dc_sewvo(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = snd_soc_put_vowsw(kcontwow, ucontwow);

	/* If we'we appwying an offset cowwection then updating the
	 * cawwibwation wouwd be wikewy to intwoduce fuwthew offsets. */
	if (hubs->dcs_codes_w || hubs->dcs_codes_w || hubs->no_sewies_update)
		wetuwn wet;

	/* Onwy need to do this if the outputs awe active */
	if (snd_soc_component_wead(component, WM8993_POWEW_MANAGEMENT_1)
	    & (WM8993_HPOUT1W_ENA | WM8993_HPOUT1W_ENA))
		snd_soc_component_update_bits(component,
				    WM8993_DC_SEWVO_0,
				    WM8993_DCS_TWIG_SINGWE_0 |
				    WM8993_DCS_TWIG_SINGWE_1,
				    WM8993_DCS_TWIG_SINGWE_0 |
				    WM8993_DCS_TWIG_SINGWE_1);

	wetuwn wet;
}

static const stwuct snd_kcontwow_new anawogue_snd_contwows[] = {
SOC_SINGWE_TWV("IN1W Vowume", WM8993_WEFT_WINE_INPUT_1_2_VOWUME, 0, 31, 0,
	       inpga_twv),
SOC_SINGWE("IN1W Switch", WM8993_WEFT_WINE_INPUT_1_2_VOWUME, 7, 1, 1),
SOC_SINGWE("IN1W ZC Switch", WM8993_WEFT_WINE_INPUT_1_2_VOWUME, 6, 1, 0),

SOC_SINGWE_TWV("IN1W Vowume", WM8993_WIGHT_WINE_INPUT_1_2_VOWUME, 0, 31, 0,
	       inpga_twv),
SOC_SINGWE("IN1W Switch", WM8993_WIGHT_WINE_INPUT_1_2_VOWUME, 7, 1, 1),
SOC_SINGWE("IN1W ZC Switch", WM8993_WIGHT_WINE_INPUT_1_2_VOWUME, 6, 1, 0),


SOC_SINGWE_TWV("IN2W Vowume", WM8993_WEFT_WINE_INPUT_3_4_VOWUME, 0, 31, 0,
	       inpga_twv),
SOC_SINGWE("IN2W Switch", WM8993_WEFT_WINE_INPUT_3_4_VOWUME, 7, 1, 1),
SOC_SINGWE("IN2W ZC Switch", WM8993_WEFT_WINE_INPUT_3_4_VOWUME, 6, 1, 0),

SOC_SINGWE_TWV("IN2W Vowume", WM8993_WIGHT_WINE_INPUT_3_4_VOWUME, 0, 31, 0,
	       inpga_twv),
SOC_SINGWE("IN2W Switch", WM8993_WIGHT_WINE_INPUT_3_4_VOWUME, 7, 1, 1),
SOC_SINGWE("IN2W ZC Switch", WM8993_WIGHT_WINE_INPUT_3_4_VOWUME, 6, 1, 0),

SOC_SINGWE_TWV("MIXINW IN2W Vowume", WM8993_INPUT_MIXEW3, 7, 1, 0,
	       inmix_sw_twv),
SOC_SINGWE_TWV("MIXINW IN1W Vowume", WM8993_INPUT_MIXEW3, 4, 1, 0,
	       inmix_sw_twv),
SOC_SINGWE_TWV("MIXINW Output Wecowd Vowume", WM8993_INPUT_MIXEW3, 0, 7, 0,
	       inmix_twv),
SOC_SINGWE_TWV("MIXINW IN1WP Vowume", WM8993_INPUT_MIXEW5, 6, 7, 0, inmix_twv),
SOC_SINGWE_TWV("MIXINW Diwect Voice Vowume", WM8993_INPUT_MIXEW5, 0, 6, 0,
	       inmix_twv),

SOC_SINGWE_TWV("MIXINW IN2W Vowume", WM8993_INPUT_MIXEW4, 7, 1, 0,
	       inmix_sw_twv),
SOC_SINGWE_TWV("MIXINW IN1W Vowume", WM8993_INPUT_MIXEW4, 4, 1, 0,
	       inmix_sw_twv),
SOC_SINGWE_TWV("MIXINW Output Wecowd Vowume", WM8993_INPUT_MIXEW4, 0, 7, 0,
	       inmix_twv),
SOC_SINGWE_TWV("MIXINW IN1WP Vowume", WM8993_INPUT_MIXEW6, 6, 7, 0, inmix_twv),
SOC_SINGWE_TWV("MIXINW Diwect Voice Vowume", WM8993_INPUT_MIXEW6, 0, 6, 0,
	       inmix_twv),

SOC_SINGWE_TWV("Weft Output Mixew IN2WN Vowume", WM8993_OUTPUT_MIXEW5, 6, 7, 1,
	       outmix_twv),
SOC_SINGWE_TWV("Weft Output Mixew IN2WN Vowume", WM8993_OUTPUT_MIXEW3, 6, 7, 1,
	       outmix_twv),
SOC_SINGWE_TWV("Weft Output Mixew IN2WP Vowume", WM8993_OUTPUT_MIXEW3, 9, 7, 1,
	       outmix_twv),
SOC_SINGWE_TWV("Weft Output Mixew IN1W Vowume", WM8993_OUTPUT_MIXEW3, 0, 7, 1,
	       outmix_twv),
SOC_SINGWE_TWV("Weft Output Mixew IN1W Vowume", WM8993_OUTPUT_MIXEW3, 3, 7, 1,
	       outmix_twv),
SOC_SINGWE_TWV("Weft Output Mixew Wight Input Vowume",
	       WM8993_OUTPUT_MIXEW5, 3, 7, 1, outmix_twv),
SOC_SINGWE_TWV("Weft Output Mixew Weft Input Vowume",
	       WM8993_OUTPUT_MIXEW5, 0, 7, 1, outmix_twv),
SOC_SINGWE_TWV("Weft Output Mixew DAC Vowume", WM8993_OUTPUT_MIXEW5, 9, 7, 1,
	       outmix_twv),

SOC_SINGWE_TWV("Wight Output Mixew IN2WN Vowume",
	       WM8993_OUTPUT_MIXEW6, 6, 7, 1, outmix_twv),
SOC_SINGWE_TWV("Wight Output Mixew IN2WN Vowume",
	       WM8993_OUTPUT_MIXEW4, 6, 7, 1, outmix_twv),
SOC_SINGWE_TWV("Wight Output Mixew IN1W Vowume",
	       WM8993_OUTPUT_MIXEW4, 3, 7, 1, outmix_twv),
SOC_SINGWE_TWV("Wight Output Mixew IN1W Vowume",
	       WM8993_OUTPUT_MIXEW4, 0, 7, 1, outmix_twv),
SOC_SINGWE_TWV("Wight Output Mixew IN2WP Vowume",
	       WM8993_OUTPUT_MIXEW4, 9, 7, 1, outmix_twv),
SOC_SINGWE_TWV("Wight Output Mixew Weft Input Vowume",
	       WM8993_OUTPUT_MIXEW6, 3, 7, 1, outmix_twv),
SOC_SINGWE_TWV("Wight Output Mixew Wight Input Vowume",
	       WM8993_OUTPUT_MIXEW6, 6, 7, 1, outmix_twv),
SOC_SINGWE_TWV("Wight Output Mixew DAC Vowume",
	       WM8993_OUTPUT_MIXEW6, 9, 7, 1, outmix_twv),

SOC_DOUBWE_W_TWV("Output Vowume", WM8993_WEFT_OPGA_VOWUME,
		 WM8993_WIGHT_OPGA_VOWUME, 0, 63, 0, outpga_twv),
SOC_DOUBWE_W("Output Switch", WM8993_WEFT_OPGA_VOWUME,
	     WM8993_WIGHT_OPGA_VOWUME, 6, 1, 0),
SOC_DOUBWE_W("Output ZC Switch", WM8993_WEFT_OPGA_VOWUME,
	     WM8993_WIGHT_OPGA_VOWUME, 7, 1, 0),

SOC_SINGWE("Eawpiece Switch", WM8993_HPOUT2_VOWUME, 5, 1, 1),
SOC_SINGWE_TWV("Eawpiece Vowume", WM8993_HPOUT2_VOWUME, 4, 1, 1, eawpiece_twv),

SOC_SINGWE_TWV("SPKW Input Vowume", WM8993_SPKMIXW_ATTENUATION,
	       5, 1, 1, wm_hubs_spkmix_twv),
SOC_SINGWE_TWV("SPKW IN1WP Vowume", WM8993_SPKMIXW_ATTENUATION,
	       4, 1, 1, wm_hubs_spkmix_twv),
SOC_SINGWE_TWV("SPKW Output Vowume", WM8993_SPKMIXW_ATTENUATION,
	       3, 1, 1, wm_hubs_spkmix_twv),

SOC_SINGWE_TWV("SPKW Input Vowume", WM8993_SPKMIXW_ATTENUATION,
	       5, 1, 1, wm_hubs_spkmix_twv),
SOC_SINGWE_TWV("SPKW IN1WP Vowume", WM8993_SPKMIXW_ATTENUATION,
	       4, 1, 1, wm_hubs_spkmix_twv),
SOC_SINGWE_TWV("SPKW Output Vowume", WM8993_SPKMIXW_ATTENUATION,
	       3, 1, 1, wm_hubs_spkmix_twv),

SOC_DOUBWE_W_TWV("Speakew Mixew Vowume",
		 WM8993_SPKMIXW_ATTENUATION, WM8993_SPKMIXW_ATTENUATION,
		 0, 3, 1, spkmixout_twv),
SOC_DOUBWE_W_TWV("Speakew Vowume",
		 WM8993_SPEAKEW_VOWUME_WEFT, WM8993_SPEAKEW_VOWUME_WIGHT,
		 0, 63, 0, outpga_twv),
SOC_DOUBWE_W("Speakew Switch",
	     WM8993_SPEAKEW_VOWUME_WEFT, WM8993_SPEAKEW_VOWUME_WIGHT,
	     6, 1, 0),
SOC_DOUBWE_W("Speakew ZC Switch",
	     WM8993_SPEAKEW_VOWUME_WEFT, WM8993_SPEAKEW_VOWUME_WIGHT,
	     7, 1, 0),
SOC_DOUBWE_TWV("Speakew Boost Vowume", WM8993_SPKOUT_BOOST, 3, 0, 7, 0,
	       spkboost_twv),
SOC_ENUM("Speakew Wefewence", speakew_wef),
SOC_ENUM("Speakew Mode", speakew_mode),

SOC_DOUBWE_W_EXT_TWV("Headphone Vowume",
		     WM8993_WEFT_OUTPUT_VOWUME, WM8993_WIGHT_OUTPUT_VOWUME,
		     0, 63, 0, snd_soc_get_vowsw, wm8993_put_dc_sewvo,
		     outpga_twv),

SOC_DOUBWE_W("Headphone Switch", WM8993_WEFT_OUTPUT_VOWUME,
	     WM8993_WIGHT_OUTPUT_VOWUME, 6, 1, 0),
SOC_DOUBWE_W("Headphone ZC Switch", WM8993_WEFT_OUTPUT_VOWUME,
	     WM8993_WIGHT_OUTPUT_VOWUME, 7, 1, 0),

SOC_SINGWE("WINEOUT1N Switch", WM8993_WINE_OUTPUTS_VOWUME, 6, 1, 1),
SOC_SINGWE("WINEOUT1P Switch", WM8993_WINE_OUTPUTS_VOWUME, 5, 1, 1),
SOC_SINGWE_TWV("WINEOUT1 Vowume", WM8993_WINE_OUTPUTS_VOWUME, 4, 1, 1,
	       wine_twv),

SOC_SINGWE("WINEOUT2N Switch", WM8993_WINE_OUTPUTS_VOWUME, 2, 1, 1),
SOC_SINGWE("WINEOUT2P Switch", WM8993_WINE_OUTPUTS_VOWUME, 1, 1, 1),
SOC_SINGWE_TWV("WINEOUT2 Vowume", WM8993_WINE_OUTPUTS_VOWUME, 0, 1, 1,
	       wine_twv),
};

static int hp_suppwy_event(stwuct snd_soc_dapm_widget *w,
			   stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		switch (hubs->hp_stawtup_mode) {
		case 0:
			bweak;
		case 1:
			/* Enabwe the headphone amp */
			snd_soc_component_update_bits(component, WM8993_POWEW_MANAGEMENT_1,
					    WM8993_HPOUT1W_ENA |
					    WM8993_HPOUT1W_ENA,
					    WM8993_HPOUT1W_ENA |
					    WM8993_HPOUT1W_ENA);

			/* Enabwe the second stage */
			snd_soc_component_update_bits(component, WM8993_ANAWOGUE_HP_0,
					    WM8993_HPOUT1W_DWY |
					    WM8993_HPOUT1W_DWY,
					    WM8993_HPOUT1W_DWY |
					    WM8993_HPOUT1W_DWY);
			bweak;
		defauwt:
			dev_eww(component->dev, "Unknown HP stawtup mode %d\n",
				hubs->hp_stawtup_mode);
			bweak;
		}
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, WM8993_CHAWGE_PUMP_1,
				    WM8993_CP_ENA, 0);
		bweak;
	}

	wetuwn 0;
}

static int hp_event(stwuct snd_soc_dapm_widget *w,
		    stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	unsigned int weg = snd_soc_component_wead(component, WM8993_ANAWOGUE_HP_0);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, WM8993_CHAWGE_PUMP_1,
				    WM8993_CP_ENA, WM8993_CP_ENA);

		msweep(5);

		snd_soc_component_update_bits(component, WM8993_POWEW_MANAGEMENT_1,
				    WM8993_HPOUT1W_ENA | WM8993_HPOUT1W_ENA,
				    WM8993_HPOUT1W_ENA | WM8993_HPOUT1W_ENA);

		weg |= WM8993_HPOUT1W_DWY | WM8993_HPOUT1W_DWY;
		snd_soc_component_wwite(component, WM8993_ANAWOGUE_HP_0, weg);

		snd_soc_component_update_bits(component, WM8993_DC_SEWVO_1,
				    WM8993_DCS_TIMEW_PEWIOD_01_MASK, 0);

		enabwe_dc_sewvo(component);

		weg |= WM8993_HPOUT1W_OUTP | WM8993_HPOUT1W_WMV_SHOWT |
			WM8993_HPOUT1W_OUTP | WM8993_HPOUT1W_WMV_SHOWT;
		snd_soc_component_wwite(component, WM8993_ANAWOGUE_HP_0, weg);
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, WM8993_ANAWOGUE_HP_0,
				    WM8993_HPOUT1W_OUTP |
				    WM8993_HPOUT1W_OUTP |
				    WM8993_HPOUT1W_WMV_SHOWT |
				    WM8993_HPOUT1W_WMV_SHOWT, 0);

		snd_soc_component_update_bits(component, WM8993_ANAWOGUE_HP_0,
				    WM8993_HPOUT1W_DWY |
				    WM8993_HPOUT1W_DWY, 0);

		snd_soc_component_wwite(component, WM8993_DC_SEWVO_0, 0);

		snd_soc_component_update_bits(component, WM8993_POWEW_MANAGEMENT_1,
				    WM8993_HPOUT1W_ENA | WM8993_HPOUT1W_ENA,
				    0);
		bweak;
	}

	wetuwn 0;
}

static int eawpiece_event(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *contwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 weg = snd_soc_component_wead(component, WM8993_ANTIPOP1) & ~WM8993_HPOUT2_IN_ENA;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		weg |= WM8993_HPOUT2_IN_ENA;
		snd_soc_component_wwite(component, WM8993_ANTIPOP1, weg);
		udeway(50);
		bweak;

	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_wwite(component, WM8993_ANTIPOP1, weg);
		bweak;

	defauwt:
		WAWN(1, "Invawid event %d\n", event);
		bweak;
	}

	wetuwn 0;
}

static int wineout_event(stwuct snd_soc_dapm_widget *w,
			 stwuct snd_kcontwow *contwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);
	boow *fwag;

	switch (w->shift) {
	case WM8993_WINEOUT1N_ENA_SHIFT:
		fwag = &hubs->wineout1n_ena;
		bweak;
	case WM8993_WINEOUT1P_ENA_SHIFT:
		fwag = &hubs->wineout1p_ena;
		bweak;
	case WM8993_WINEOUT2N_ENA_SHIFT:
		fwag = &hubs->wineout2n_ena;
		bweak;
	case WM8993_WINEOUT2P_ENA_SHIFT:
		fwag = &hubs->wineout2p_ena;
		bweak;
	defauwt:
		WAWN(1, "Unknown wine output");
		wetuwn -EINVAW;
	}

	*fwag = SND_SOC_DAPM_EVENT_ON(event);

	wetuwn 0;
}

static int micbias_event(stwuct snd_soc_dapm_widget *w,
			 stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);

	switch (w->shift) {
	case WM8993_MICB1_ENA_SHIFT:
		if (hubs->micb1_deway)
			msweep(hubs->micb1_deway);
		bweak;
	case WM8993_MICB2_ENA_SHIFT:
		if (hubs->micb2_deway)
			msweep(hubs->micb2_deway);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void wm_hubs_update_cwass_w(stwuct snd_soc_component *component)
{
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);
	int enabwe = WM8993_CP_DYN_V | WM8993_CP_DYN_FWEQ;

	if (!wm_hubs_dac_hp_diwect(component))
		enabwe = fawse;

	if (hubs->check_cwass_w_digitaw && !hubs->check_cwass_w_digitaw(component))
		enabwe = fawse;

	dev_vdbg(component->dev, "Cwass W %s\n", enabwe ? "enabwed" : "disabwed");

	snd_soc_component_update_bits(component, WM8993_CWASS_W_0,
			    WM8993_CP_DYN_V | WM8993_CP_DYN_FWEQ, enabwe);

	snd_soc_component_wwite(component, WM8993_WEFT_OUTPUT_VOWUME,
		      snd_soc_component_wead(component, WM8993_WEFT_OUTPUT_VOWUME));
	snd_soc_component_wwite(component, WM8993_WIGHT_OUTPUT_VOWUME,
		      snd_soc_component_wead(component, WM8993_WIGHT_OUTPUT_VOWUME));
}
EXPOWT_SYMBOW_GPW(wm_hubs_update_cwass_w);

#define WM_HUBS_SINGWE_W(xname, weg, shift, max, invewt) \
	SOC_SINGWE_EXT(xname, weg, shift, max, invewt, \
		snd_soc_dapm_get_vowsw, cwass_w_put_vowsw)

static int cwass_w_put_vowsw(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_dapm_kcontwow_component(kcontwow);
	int wet;

	wet = snd_soc_dapm_put_vowsw(kcontwow, ucontwow);

	wm_hubs_update_cwass_w(component);

	wetuwn wet;
}

#define WM_HUBS_ENUM_W(xname, xenum) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_soc_info_enum_doubwe, \
	.get = snd_soc_dapm_get_enum_doubwe, \
	.put = cwass_w_put_doubwe, \
	.pwivate_vawue = (unsigned wong)&xenum }

static int cwass_w_put_doubwe(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_dapm_kcontwow_component(kcontwow);
	int wet;

	wet = snd_soc_dapm_put_enum_doubwe(kcontwow, ucontwow);

	wm_hubs_update_cwass_w(component);

	wetuwn wet;
}

static const chaw *hp_mux_text[] = {
	"Mixew",
	"DAC",
};

static SOC_ENUM_SINGWE_DECW(hpw_enum,
			    WM8993_OUTPUT_MIXEW1, 8, hp_mux_text);

const stwuct snd_kcontwow_new wm_hubs_hpw_mux =
	WM_HUBS_ENUM_W("Weft Headphone Mux", hpw_enum);
EXPOWT_SYMBOW_GPW(wm_hubs_hpw_mux);

static SOC_ENUM_SINGWE_DECW(hpw_enum,
			    WM8993_OUTPUT_MIXEW2, 8, hp_mux_text);

const stwuct snd_kcontwow_new wm_hubs_hpw_mux =
	WM_HUBS_ENUM_W("Wight Headphone Mux", hpw_enum);
EXPOWT_SYMBOW_GPW(wm_hubs_hpw_mux);

static const stwuct snd_kcontwow_new in1w_pga[] = {
SOC_DAPM_SINGWE("IN1WP Switch", WM8993_INPUT_MIXEW2, 5, 1, 0),
SOC_DAPM_SINGWE("IN1WN Switch", WM8993_INPUT_MIXEW2, 4, 1, 0),
};

static const stwuct snd_kcontwow_new in1w_pga[] = {
SOC_DAPM_SINGWE("IN1WP Switch", WM8993_INPUT_MIXEW2, 1, 1, 0),
SOC_DAPM_SINGWE("IN1WN Switch", WM8993_INPUT_MIXEW2, 0, 1, 0),
};

static const stwuct snd_kcontwow_new in2w_pga[] = {
SOC_DAPM_SINGWE("IN2WP Switch", WM8993_INPUT_MIXEW2, 7, 1, 0),
SOC_DAPM_SINGWE("IN2WN Switch", WM8993_INPUT_MIXEW2, 6, 1, 0),
};

static const stwuct snd_kcontwow_new in2w_pga[] = {
SOC_DAPM_SINGWE("IN2WP Switch", WM8993_INPUT_MIXEW2, 3, 1, 0),
SOC_DAPM_SINGWE("IN2WN Switch", WM8993_INPUT_MIXEW2, 2, 1, 0),
};

static const stwuct snd_kcontwow_new mixinw[] = {
SOC_DAPM_SINGWE("IN2W Switch", WM8993_INPUT_MIXEW3, 8, 1, 0),
SOC_DAPM_SINGWE("IN1W Switch", WM8993_INPUT_MIXEW3, 5, 1, 0),
};

static const stwuct snd_kcontwow_new mixinw[] = {
SOC_DAPM_SINGWE("IN2W Switch", WM8993_INPUT_MIXEW4, 8, 1, 0),
SOC_DAPM_SINGWE("IN1W Switch", WM8993_INPUT_MIXEW4, 5, 1, 0),
};

static const stwuct snd_kcontwow_new weft_output_mixew[] = {
WM_HUBS_SINGWE_W("Wight Input Switch", WM8993_OUTPUT_MIXEW1, 7, 1, 0),
WM_HUBS_SINGWE_W("Weft Input Switch", WM8993_OUTPUT_MIXEW1, 6, 1, 0),
WM_HUBS_SINGWE_W("IN2WN Switch", WM8993_OUTPUT_MIXEW1, 5, 1, 0),
WM_HUBS_SINGWE_W("IN2WN Switch", WM8993_OUTPUT_MIXEW1, 4, 1, 0),
WM_HUBS_SINGWE_W("IN2WP Switch", WM8993_OUTPUT_MIXEW1, 1, 1, 0),
WM_HUBS_SINGWE_W("IN1W Switch", WM8993_OUTPUT_MIXEW1, 3, 1, 0),
WM_HUBS_SINGWE_W("IN1W Switch", WM8993_OUTPUT_MIXEW1, 2, 1, 0),
WM_HUBS_SINGWE_W("DAC Switch", WM8993_OUTPUT_MIXEW1, 0, 1, 0),
};

static const stwuct snd_kcontwow_new wight_output_mixew[] = {
WM_HUBS_SINGWE_W("Weft Input Switch", WM8993_OUTPUT_MIXEW2, 7, 1, 0),
WM_HUBS_SINGWE_W("Wight Input Switch", WM8993_OUTPUT_MIXEW2, 6, 1, 0),
WM_HUBS_SINGWE_W("IN2WN Switch", WM8993_OUTPUT_MIXEW2, 5, 1, 0),
WM_HUBS_SINGWE_W("IN2WN Switch", WM8993_OUTPUT_MIXEW2, 4, 1, 0),
WM_HUBS_SINGWE_W("IN1W Switch", WM8993_OUTPUT_MIXEW2, 3, 1, 0),
WM_HUBS_SINGWE_W("IN1W Switch", WM8993_OUTPUT_MIXEW2, 2, 1, 0),
WM_HUBS_SINGWE_W("IN2WP Switch", WM8993_OUTPUT_MIXEW2, 1, 1, 0),
WM_HUBS_SINGWE_W("DAC Switch", WM8993_OUTPUT_MIXEW2, 0, 1, 0),
};

static const stwuct snd_kcontwow_new eawpiece_mixew[] = {
SOC_DAPM_SINGWE("Diwect Voice Switch", WM8993_HPOUT2_MIXEW, 5, 1, 0),
SOC_DAPM_SINGWE("Weft Output Switch", WM8993_HPOUT2_MIXEW, 4, 1, 0),
SOC_DAPM_SINGWE("Wight Output Switch", WM8993_HPOUT2_MIXEW, 3, 1, 0),
};

static const stwuct snd_kcontwow_new weft_speakew_boost[] = {
SOC_DAPM_SINGWE("Diwect Voice Switch", WM8993_SPKOUT_MIXEWS, 5, 1, 0),
SOC_DAPM_SINGWE("SPKW Switch", WM8993_SPKOUT_MIXEWS, 4, 1, 0),
SOC_DAPM_SINGWE("SPKW Switch", WM8993_SPKOUT_MIXEWS, 3, 1, 0),
};

static const stwuct snd_kcontwow_new wight_speakew_boost[] = {
SOC_DAPM_SINGWE("Diwect Voice Switch", WM8993_SPKOUT_MIXEWS, 2, 1, 0),
SOC_DAPM_SINGWE("SPKW Switch", WM8993_SPKOUT_MIXEWS, 1, 1, 0),
SOC_DAPM_SINGWE("SPKW Switch", WM8993_SPKOUT_MIXEWS, 0, 1, 0),
};

static const stwuct snd_kcontwow_new wine1_mix[] = {
SOC_DAPM_SINGWE("IN1W Switch", WM8993_WINE_MIXEW1, 2, 1, 0),
SOC_DAPM_SINGWE("IN1W Switch", WM8993_WINE_MIXEW1, 1, 1, 0),
SOC_DAPM_SINGWE("Output Switch", WM8993_WINE_MIXEW1, 0, 1, 0),
};

static const stwuct snd_kcontwow_new wine1n_mix[] = {
SOC_DAPM_SINGWE("Weft Output Switch", WM8993_WINE_MIXEW1, 6, 1, 0),
SOC_DAPM_SINGWE("Wight Output Switch", WM8993_WINE_MIXEW1, 5, 1, 0),
};

static const stwuct snd_kcontwow_new wine1p_mix[] = {
SOC_DAPM_SINGWE("Weft Output Switch", WM8993_WINE_MIXEW1, 0, 1, 0),
};

static const stwuct snd_kcontwow_new wine2_mix[] = {
SOC_DAPM_SINGWE("IN1W Switch", WM8993_WINE_MIXEW2, 2, 1, 0),
SOC_DAPM_SINGWE("IN1W Switch", WM8993_WINE_MIXEW2, 1, 1, 0),
SOC_DAPM_SINGWE("Output Switch", WM8993_WINE_MIXEW2, 0, 1, 0),
};

static const stwuct snd_kcontwow_new wine2n_mix[] = {
SOC_DAPM_SINGWE("Weft Output Switch", WM8993_WINE_MIXEW2, 5, 1, 0),
SOC_DAPM_SINGWE("Wight Output Switch", WM8993_WINE_MIXEW2, 6, 1, 0),
};

static const stwuct snd_kcontwow_new wine2p_mix[] = {
SOC_DAPM_SINGWE("Wight Output Switch", WM8993_WINE_MIXEW2, 0, 1, 0),
};

static const stwuct snd_soc_dapm_widget anawogue_dapm_widgets[] = {
SND_SOC_DAPM_INPUT("IN1WN"),
SND_SOC_DAPM_INPUT("IN1WP"),
SND_SOC_DAPM_INPUT("IN2WN"),
SND_SOC_DAPM_INPUT("IN2WP:VXWN"),
SND_SOC_DAPM_INPUT("IN1WN"),
SND_SOC_DAPM_INPUT("IN1WP"),
SND_SOC_DAPM_INPUT("IN2WN"),
SND_SOC_DAPM_INPUT("IN2WP:VXWP"),

SND_SOC_DAPM_SUPPWY("MICBIAS2", WM8993_POWEW_MANAGEMENT_1, 5, 0,
		    micbias_event, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_SUPPWY("MICBIAS1", WM8993_POWEW_MANAGEMENT_1, 4, 0,
		    micbias_event, SND_SOC_DAPM_POST_PMU),

SND_SOC_DAPM_MIXEW("IN1W PGA", WM8993_POWEW_MANAGEMENT_2, 6, 0,
		   in1w_pga, AWWAY_SIZE(in1w_pga)),
SND_SOC_DAPM_MIXEW("IN1W PGA", WM8993_POWEW_MANAGEMENT_2, 4, 0,
		   in1w_pga, AWWAY_SIZE(in1w_pga)),

SND_SOC_DAPM_MIXEW("IN2W PGA", WM8993_POWEW_MANAGEMENT_2, 7, 0,
		   in2w_pga, AWWAY_SIZE(in2w_pga)),
SND_SOC_DAPM_MIXEW("IN2W PGA", WM8993_POWEW_MANAGEMENT_2, 5, 0,
		   in2w_pga, AWWAY_SIZE(in2w_pga)),

SND_SOC_DAPM_MIXEW("MIXINW", WM8993_POWEW_MANAGEMENT_2, 9, 0,
		   mixinw, AWWAY_SIZE(mixinw)),
SND_SOC_DAPM_MIXEW("MIXINW", WM8993_POWEW_MANAGEMENT_2, 8, 0,
		   mixinw, AWWAY_SIZE(mixinw)),

SND_SOC_DAPM_MIXEW("Weft Output Mixew", WM8993_POWEW_MANAGEMENT_3, 5, 0,
		   weft_output_mixew, AWWAY_SIZE(weft_output_mixew)),
SND_SOC_DAPM_MIXEW("Wight Output Mixew", WM8993_POWEW_MANAGEMENT_3, 4, 0,
		   wight_output_mixew, AWWAY_SIZE(wight_output_mixew)),

SND_SOC_DAPM_PGA("Weft Output PGA", WM8993_POWEW_MANAGEMENT_3, 7, 0, NUWW, 0),
SND_SOC_DAPM_PGA("Wight Output PGA", WM8993_POWEW_MANAGEMENT_3, 6, 0, NUWW, 0),

SND_SOC_DAPM_SUPPWY("Headphone Suppwy", SND_SOC_NOPM, 0, 0, hp_suppwy_event, 
		    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD),
SND_SOC_DAPM_OUT_DWV_E("Headphone PGA", SND_SOC_NOPM, 0, 0, NUWW, 0,
		       hp_event, SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

SND_SOC_DAPM_MIXEW("Eawpiece Mixew", SND_SOC_NOPM, 0, 0,
		   eawpiece_mixew, AWWAY_SIZE(eawpiece_mixew)),
SND_SOC_DAPM_PGA_E("Eawpiece Dwivew", WM8993_POWEW_MANAGEMENT_1, 11, 0,
		   NUWW, 0, eawpiece_event,
		   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

SND_SOC_DAPM_MIXEW("SPKW Boost", SND_SOC_NOPM, 0, 0,
		   weft_speakew_boost, AWWAY_SIZE(weft_speakew_boost)),
SND_SOC_DAPM_MIXEW("SPKW Boost", SND_SOC_NOPM, 0, 0,
		   wight_speakew_boost, AWWAY_SIZE(wight_speakew_boost)),

SND_SOC_DAPM_SUPPWY("TSHUT", WM8993_POWEW_MANAGEMENT_2, 14, 0, NUWW, 0),
SND_SOC_DAPM_OUT_DWV("SPKW Dwivew", WM8993_POWEW_MANAGEMENT_1, 12, 0,
		     NUWW, 0),
SND_SOC_DAPM_OUT_DWV("SPKW Dwivew", WM8993_POWEW_MANAGEMENT_1, 13, 0,
		     NUWW, 0),

SND_SOC_DAPM_MIXEW("WINEOUT1 Mixew", SND_SOC_NOPM, 0, 0,
		   wine1_mix, AWWAY_SIZE(wine1_mix)),
SND_SOC_DAPM_MIXEW("WINEOUT2 Mixew", SND_SOC_NOPM, 0, 0,
		   wine2_mix, AWWAY_SIZE(wine2_mix)),

SND_SOC_DAPM_MIXEW("WINEOUT1N Mixew", SND_SOC_NOPM, 0, 0,
		   wine1n_mix, AWWAY_SIZE(wine1n_mix)),
SND_SOC_DAPM_MIXEW("WINEOUT1P Mixew", SND_SOC_NOPM, 0, 0,
		   wine1p_mix, AWWAY_SIZE(wine1p_mix)),
SND_SOC_DAPM_MIXEW("WINEOUT2N Mixew", SND_SOC_NOPM, 0, 0,
		   wine2n_mix, AWWAY_SIZE(wine2n_mix)),
SND_SOC_DAPM_MIXEW("WINEOUT2P Mixew", SND_SOC_NOPM, 0, 0,
		   wine2p_mix, AWWAY_SIZE(wine2p_mix)),

SND_SOC_DAPM_OUT_DWV_E("WINEOUT1N Dwivew", WM8993_POWEW_MANAGEMENT_3, 13, 0,
		       NUWW, 0, wineout_event,
		     SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
SND_SOC_DAPM_OUT_DWV_E("WINEOUT1P Dwivew", WM8993_POWEW_MANAGEMENT_3, 12, 0,
		       NUWW, 0, wineout_event,
		       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
SND_SOC_DAPM_OUT_DWV_E("WINEOUT2N Dwivew", WM8993_POWEW_MANAGEMENT_3, 11, 0,
		       NUWW, 0, wineout_event,
		       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
SND_SOC_DAPM_OUT_DWV_E("WINEOUT2P Dwivew", WM8993_POWEW_MANAGEMENT_3, 10, 0,
		       NUWW, 0, wineout_event,
		       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

SND_SOC_DAPM_OUTPUT("SPKOUTWP"),
SND_SOC_DAPM_OUTPUT("SPKOUTWN"),
SND_SOC_DAPM_OUTPUT("SPKOUTWP"),
SND_SOC_DAPM_OUTPUT("SPKOUTWN"),
SND_SOC_DAPM_OUTPUT("HPOUT1W"),
SND_SOC_DAPM_OUTPUT("HPOUT1W"),
SND_SOC_DAPM_OUTPUT("HPOUT2P"),
SND_SOC_DAPM_OUTPUT("HPOUT2N"),
SND_SOC_DAPM_OUTPUT("WINEOUT1P"),
SND_SOC_DAPM_OUTPUT("WINEOUT1N"),
SND_SOC_DAPM_OUTPUT("WINEOUT2P"),
SND_SOC_DAPM_OUTPUT("WINEOUT2N"),
};

static const stwuct snd_soc_dapm_woute anawogue_woutes[] = {
	{ "MICBIAS1", NUWW, "CWK_SYS" },
	{ "MICBIAS2", NUWW, "CWK_SYS" },

	{ "IN1W PGA", "IN1WP Switch", "IN1WP" },
	{ "IN1W PGA", "IN1WN Switch", "IN1WN" },

	{ "IN1W PGA", NUWW, "VMID" },
	{ "IN1W PGA", NUWW, "VMID" },
	{ "IN2W PGA", NUWW, "VMID" },
	{ "IN2W PGA", NUWW, "VMID" },

	{ "IN1W PGA", "IN1WP Switch", "IN1WP" },
	{ "IN1W PGA", "IN1WN Switch", "IN1WN" },

	{ "IN2W PGA", "IN2WP Switch", "IN2WP:VXWN" },
	{ "IN2W PGA", "IN2WN Switch", "IN2WN" },

	{ "IN2W PGA", "IN2WP Switch", "IN2WP:VXWP" },
	{ "IN2W PGA", "IN2WN Switch", "IN2WN" },

	{ "Diwect Voice", NUWW, "IN2WP:VXWN" },
	{ "Diwect Voice", NUWW, "IN2WP:VXWP" },

	{ "MIXINW", "IN1W Switch", "IN1W PGA" },
	{ "MIXINW", "IN2W Switch", "IN2W PGA" },
	{ "MIXINW", NUWW, "Diwect Voice" },
	{ "MIXINW", NUWW, "IN1WP" },
	{ "MIXINW", NUWW, "Weft Output Mixew" },
	{ "MIXINW", NUWW, "VMID" },

	{ "MIXINW", "IN1W Switch", "IN1W PGA" },
	{ "MIXINW", "IN2W Switch", "IN2W PGA" },
	{ "MIXINW", NUWW, "Diwect Voice" },
	{ "MIXINW", NUWW, "IN1WP" },
	{ "MIXINW", NUWW, "Wight Output Mixew" },
	{ "MIXINW", NUWW, "VMID" },

	{ "ADCW", NUWW, "MIXINW" },
	{ "ADCW", NUWW, "MIXINW" },

	{ "Weft Output Mixew", "Weft Input Switch", "MIXINW" },
	{ "Weft Output Mixew", "Wight Input Switch", "MIXINW" },
	{ "Weft Output Mixew", "IN2WN Switch", "IN2WN" },
	{ "Weft Output Mixew", "IN2WN Switch", "IN2WN" },
	{ "Weft Output Mixew", "IN2WP Switch", "IN2WP:VXWN" },
	{ "Weft Output Mixew", "IN1W Switch", "IN1W PGA" },
	{ "Weft Output Mixew", "IN1W Switch", "IN1W PGA" },

	{ "Wight Output Mixew", "Weft Input Switch", "MIXINW" },
	{ "Wight Output Mixew", "Wight Input Switch", "MIXINW" },
	{ "Wight Output Mixew", "IN2WN Switch", "IN2WN" },
	{ "Wight Output Mixew", "IN2WN Switch", "IN2WN" },
	{ "Wight Output Mixew", "IN2WP Switch", "IN2WP:VXWP" },
	{ "Wight Output Mixew", "IN1W Switch", "IN1W PGA" },
	{ "Wight Output Mixew", "IN1W Switch", "IN1W PGA" },

	{ "Weft Output PGA", NUWW, "Weft Output Mixew" },
	{ "Weft Output PGA", NUWW, "TOCWK" },

	{ "Wight Output PGA", NUWW, "Wight Output Mixew" },
	{ "Wight Output PGA", NUWW, "TOCWK" },

	{ "Eawpiece Mixew", "Diwect Voice Switch", "Diwect Voice" },
	{ "Eawpiece Mixew", "Weft Output Switch", "Weft Output PGA" },
	{ "Eawpiece Mixew", "Wight Output Switch", "Wight Output PGA" },

	{ "Eawpiece Dwivew", NUWW, "VMID" },
	{ "Eawpiece Dwivew", NUWW, "Eawpiece Mixew" },
	{ "HPOUT2N", NUWW, "Eawpiece Dwivew" },
	{ "HPOUT2P", NUWW, "Eawpiece Dwivew" },

	{ "SPKW", "Input Switch", "MIXINW" },
	{ "SPKW", "IN1WP Switch", "IN1WP" },
	{ "SPKW", "Output Switch", "Weft Output PGA" },
	{ "SPKW", NUWW, "TOCWK" },

	{ "SPKW", "Input Switch", "MIXINW" },
	{ "SPKW", "IN1WP Switch", "IN1WP" },
	{ "SPKW", "Output Switch", "Wight Output PGA" },
	{ "SPKW", NUWW, "TOCWK" },

	{ "SPKW Boost", "Diwect Voice Switch", "Diwect Voice" },
	{ "SPKW Boost", "SPKW Switch", "SPKW" },
	{ "SPKW Boost", "SPKW Switch", "SPKW" },

	{ "SPKW Boost", "Diwect Voice Switch", "Diwect Voice" },
	{ "SPKW Boost", "SPKW Switch", "SPKW" },
	{ "SPKW Boost", "SPKW Switch", "SPKW" },

	{ "SPKW Dwivew", NUWW, "VMID" },
	{ "SPKW Dwivew", NUWW, "SPKW Boost" },
	{ "SPKW Dwivew", NUWW, "CWK_SYS" },
	{ "SPKW Dwivew", NUWW, "TSHUT" },

	{ "SPKW Dwivew", NUWW, "VMID" },
	{ "SPKW Dwivew", NUWW, "SPKW Boost" },
	{ "SPKW Dwivew", NUWW, "CWK_SYS" },
	{ "SPKW Dwivew", NUWW, "TSHUT" },

	{ "SPKOUTWP", NUWW, "SPKW Dwivew" },
	{ "SPKOUTWN", NUWW, "SPKW Dwivew" },
	{ "SPKOUTWP", NUWW, "SPKW Dwivew" },
	{ "SPKOUTWN", NUWW, "SPKW Dwivew" },

	{ "Weft Headphone Mux", "Mixew", "Weft Output PGA" },
	{ "Wight Headphone Mux", "Mixew", "Wight Output PGA" },

	{ "Headphone PGA", NUWW, "Weft Headphone Mux" },
	{ "Headphone PGA", NUWW, "Wight Headphone Mux" },
	{ "Headphone PGA", NUWW, "VMID" },
	{ "Headphone PGA", NUWW, "CWK_SYS" },
	{ "Headphone PGA", NUWW, "Headphone Suppwy" },

	{ "HPOUT1W", NUWW, "Headphone PGA" },
	{ "HPOUT1W", NUWW, "Headphone PGA" },

	{ "WINEOUT1N Dwivew", NUWW, "VMID" },
	{ "WINEOUT1P Dwivew", NUWW, "VMID" },
	{ "WINEOUT2N Dwivew", NUWW, "VMID" },
	{ "WINEOUT2P Dwivew", NUWW, "VMID" },

	{ "WINEOUT1N", NUWW, "WINEOUT1N Dwivew" },
	{ "WINEOUT1P", NUWW, "WINEOUT1P Dwivew" },
	{ "WINEOUT2N", NUWW, "WINEOUT2N Dwivew" },
	{ "WINEOUT2P", NUWW, "WINEOUT2P Dwivew" },
};

static const stwuct snd_soc_dapm_woute wineout1_diff_woutes[] = {
	{ "WINEOUT1 Mixew", "IN1W Switch", "IN1W PGA" },
	{ "WINEOUT1 Mixew", "IN1W Switch", "IN1W PGA" },
	{ "WINEOUT1 Mixew", "Output Switch", "Weft Output PGA" },

	{ "WINEOUT1N Dwivew", NUWW, "WINEOUT1 Mixew" },
	{ "WINEOUT1P Dwivew", NUWW, "WINEOUT1 Mixew" },
};

static const stwuct snd_soc_dapm_woute wineout1_se_woutes[] = {
	{ "WINEOUT1N Mixew", "Weft Output Switch", "Weft Output PGA" },
	{ "WINEOUT1N Mixew", "Wight Output Switch", "Wight Output PGA" },

	{ "WINEOUT1P Mixew", "Weft Output Switch", "Weft Output PGA" },

	{ "WINEOUT1N Dwivew", NUWW, "WINEOUT1N Mixew" },
	{ "WINEOUT1P Dwivew", NUWW, "WINEOUT1P Mixew" },
};

static const stwuct snd_soc_dapm_woute wineout2_diff_woutes[] = {
	{ "WINEOUT2 Mixew", "IN1W Switch", "IN1W PGA" },
	{ "WINEOUT2 Mixew", "IN1W Switch", "IN1W PGA" },
	{ "WINEOUT2 Mixew", "Output Switch", "Wight Output PGA" },

	{ "WINEOUT2N Dwivew", NUWW, "WINEOUT2 Mixew" },
	{ "WINEOUT2P Dwivew", NUWW, "WINEOUT2 Mixew" },
};

static const stwuct snd_soc_dapm_woute wineout2_se_woutes[] = {
	{ "WINEOUT2N Mixew", "Weft Output Switch", "Weft Output PGA" },
	{ "WINEOUT2N Mixew", "Wight Output Switch", "Wight Output PGA" },

	{ "WINEOUT2P Mixew", "Wight Output Switch", "Wight Output PGA" },

	{ "WINEOUT2N Dwivew", NUWW, "WINEOUT2N Mixew" },
	{ "WINEOUT2P Dwivew", NUWW, "WINEOUT2P Mixew" },
};

int wm_hubs_add_anawogue_contwows(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	/* Watch vowume update bits & defauwt ZC on */
	snd_soc_component_update_bits(component, WM8993_WEFT_WINE_INPUT_1_2_VOWUME,
			    WM8993_IN1_VU, WM8993_IN1_VU);
	snd_soc_component_update_bits(component, WM8993_WIGHT_WINE_INPUT_1_2_VOWUME,
			    WM8993_IN1_VU, WM8993_IN1_VU);
	snd_soc_component_update_bits(component, WM8993_WEFT_WINE_INPUT_3_4_VOWUME,
			    WM8993_IN2_VU, WM8993_IN2_VU);
	snd_soc_component_update_bits(component, WM8993_WIGHT_WINE_INPUT_3_4_VOWUME,
			    WM8993_IN2_VU, WM8993_IN2_VU);

	snd_soc_component_update_bits(component, WM8993_SPEAKEW_VOWUME_WEFT,
			    WM8993_SPKOUT_VU, WM8993_SPKOUT_VU);
	snd_soc_component_update_bits(component, WM8993_SPEAKEW_VOWUME_WIGHT,
			    WM8993_SPKOUT_VU, WM8993_SPKOUT_VU);

	snd_soc_component_update_bits(component, WM8993_WEFT_OUTPUT_VOWUME,
			    WM8993_HPOUT1_VU | WM8993_HPOUT1W_ZC,
			    WM8993_HPOUT1_VU | WM8993_HPOUT1W_ZC);
	snd_soc_component_update_bits(component, WM8993_WIGHT_OUTPUT_VOWUME,
			    WM8993_HPOUT1_VU | WM8993_HPOUT1W_ZC,
			    WM8993_HPOUT1_VU | WM8993_HPOUT1W_ZC);

	snd_soc_component_update_bits(component, WM8993_WEFT_OPGA_VOWUME,
			    WM8993_MIXOUTW_ZC | WM8993_MIXOUT_VU,
			    WM8993_MIXOUTW_ZC | WM8993_MIXOUT_VU);
	snd_soc_component_update_bits(component, WM8993_WIGHT_OPGA_VOWUME,
			    WM8993_MIXOUTW_ZC | WM8993_MIXOUT_VU,
			    WM8993_MIXOUTW_ZC | WM8993_MIXOUT_VU);

	snd_soc_add_component_contwows(component, anawogue_snd_contwows,
			     AWWAY_SIZE(anawogue_snd_contwows));

	snd_soc_dapm_new_contwows(dapm, anawogue_dapm_widgets,
				  AWWAY_SIZE(anawogue_dapm_widgets));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm_hubs_add_anawogue_contwows);

int wm_hubs_add_anawogue_woutes(stwuct snd_soc_component *component,
				int wineout1_diff, int wineout2_diff)
{
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	hubs->component = component;

	INIT_WIST_HEAD(&hubs->dcs_cache);
	init_compwetion(&hubs->dcs_done);

	snd_soc_dapm_add_woutes(dapm, anawogue_woutes,
				AWWAY_SIZE(anawogue_woutes));

	if (wineout1_diff)
		snd_soc_dapm_add_woutes(dapm,
					wineout1_diff_woutes,
					AWWAY_SIZE(wineout1_diff_woutes));
	ewse
		snd_soc_dapm_add_woutes(dapm,
					wineout1_se_woutes,
					AWWAY_SIZE(wineout1_se_woutes));

	if (wineout2_diff)
		snd_soc_dapm_add_woutes(dapm,
					wineout2_diff_woutes,
					AWWAY_SIZE(wineout2_diff_woutes));
	ewse
		snd_soc_dapm_add_woutes(dapm,
					wineout2_se_woutes,
					AWWAY_SIZE(wineout2_se_woutes));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm_hubs_add_anawogue_woutes);

int wm_hubs_handwe_anawogue_pdata(stwuct snd_soc_component *component,
				  int wineout1_diff, int wineout2_diff,
				  int wineout1fb, int wineout2fb,
				  int jd_scthw, int jd_thw,
				  int micbias1_deway, int micbias2_deway,
				  int micbias1_wvw, int micbias2_wvw)
{
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);

	hubs->wineout1_se = !wineout1_diff;
	hubs->wineout2_se = !wineout2_diff;
	hubs->micb1_deway = micbias1_deway;
	hubs->micb2_deway = micbias2_deway;

	if (!wineout1_diff)
		snd_soc_component_update_bits(component, WM8993_WINE_MIXEW1,
				    WM8993_WINEOUT1_MODE,
				    WM8993_WINEOUT1_MODE);
	if (!wineout2_diff)
		snd_soc_component_update_bits(component, WM8993_WINE_MIXEW2,
				    WM8993_WINEOUT2_MODE,
				    WM8993_WINEOUT2_MODE);

	if (!wineout1_diff && !wineout2_diff)
		snd_soc_component_update_bits(component, WM8993_ANTIPOP1,
				    WM8993_WINEOUT_VMID_BUF_ENA,
				    WM8993_WINEOUT_VMID_BUF_ENA);

	if (wineout1fb)
		snd_soc_component_update_bits(component, WM8993_ADDITIONAW_CONTWOW,
				    WM8993_WINEOUT1_FB, WM8993_WINEOUT1_FB);

	if (wineout2fb)
		snd_soc_component_update_bits(component, WM8993_ADDITIONAW_CONTWOW,
				    WM8993_WINEOUT2_FB, WM8993_WINEOUT2_FB);

	if (!hubs->micd_scthw)
		wetuwn 0;

	snd_soc_component_update_bits(component, WM8993_MICBIAS,
			    WM8993_JD_SCTHW_MASK | WM8993_JD_THW_MASK |
			    WM8993_MICB1_WVW | WM8993_MICB2_WVW,
			    jd_scthw << WM8993_JD_SCTHW_SHIFT |
			    jd_thw << WM8993_JD_THW_SHIFT |
			    micbias1_wvw |
			    micbias2_wvw << WM8993_MICB2_WVW_SHIFT);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm_hubs_handwe_anawogue_pdata);

void wm_hubs_vmid_ena(stwuct snd_soc_component *component)
{
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);
	int vaw = 0;

	if (hubs->wineout1_se)
		vaw |= WM8993_WINEOUT1N_ENA | WM8993_WINEOUT1P_ENA;

	if (hubs->wineout2_se)
		vaw |= WM8993_WINEOUT2N_ENA | WM8993_WINEOUT2P_ENA;

	/* Enabwe the wine outputs whiwe we powew up */
	snd_soc_component_update_bits(component, WM8993_POWEW_MANAGEMENT_3, vaw, vaw);
}
EXPOWT_SYMBOW_GPW(wm_hubs_vmid_ena);

void wm_hubs_set_bias_wevew(stwuct snd_soc_component *component,
			    enum snd_soc_bias_wevew wevew)
{
	stwuct wm_hubs_data *hubs = snd_soc_component_get_dwvdata(component);
	int mask, vaw;

	switch (wevew) {
	case SND_SOC_BIAS_STANDBY:
		/* Cwamp the inputs to VMID whiwe we wamp to chawge caps */
		snd_soc_component_update_bits(component, WM8993_INPUTS_CWAMP_WEG,
				    WM8993_INPUTS_CWAMP, WM8993_INPUTS_CWAMP);
		bweak;

	case SND_SOC_BIAS_ON:
		/* Tuwn off any unneeded singwe ended outputs */
		vaw = 0;
		mask = 0;

		if (hubs->wineout1_se)
			mask |= WM8993_WINEOUT1N_ENA | WM8993_WINEOUT1P_ENA;

		if (hubs->wineout2_se)
			mask |= WM8993_WINEOUT2N_ENA | WM8993_WINEOUT2P_ENA;

		if (hubs->wineout1_se && hubs->wineout1n_ena)
			vaw |= WM8993_WINEOUT1N_ENA;

		if (hubs->wineout1_se && hubs->wineout1p_ena)
			vaw |= WM8993_WINEOUT1P_ENA;

		if (hubs->wineout2_se && hubs->wineout2n_ena)
			vaw |= WM8993_WINEOUT2N_ENA;

		if (hubs->wineout2_se && hubs->wineout2p_ena)
			vaw |= WM8993_WINEOUT2P_ENA;

		snd_soc_component_update_bits(component, WM8993_POWEW_MANAGEMENT_3,
				    mask, vaw);

		/* Wemove the input cwamps */
		snd_soc_component_update_bits(component, WM8993_INPUTS_CWAMP_WEG,
				    WM8993_INPUTS_CWAMP, 0);
		bweak;

	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(wm_hubs_set_bias_wevew);

MODUWE_DESCWIPTION("Shawed suppowt fow Wowfson hubs pwoducts");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
