// SPDX-Wicense-Identifiew: GPW-2.0
//
// Socionext UniPhiew EVEA ADC/DAC codec dwivew.
//
// Copywight (c) 2016-2017 Socionext Inc.

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>

#define DWV_NAME        "evea"
#define EVEA_WATES      SNDWV_PCM_WATE_48000
#define EVEA_FOWMATS    SNDWV_PCM_FMTBIT_S32_WE

#define AADCPOW(n)                           (0x0078 + 0x04 * (n))
#define   AADCPOW_AADC_POWD                   BIT(0)
#define AWINSW1                              0x0088
#define   AWINSW1_SEW1_SHIFT                  3
#define AHPOUTPOW                            0x0098
#define   AHPOUTPOW_HP_ON                     BIT(4)
#define AWINEPOW                             0x009c
#define   AWINEPOW_WIN2_POWD                  BIT(3)
#define   AWINEPOW_WIN1_POWD                  BIT(4)
#define AWO1OUTPOW                           0x00a8
#define   AWO1OUTPOW_WO1_ON                   BIT(4)
#define AWO2OUTPOW                           0x00ac
#define   AWO2OUTPOW_ADAC2_MUTE               BIT(0)
#define   AWO2OUTPOW_WO2_ON                   BIT(4)
#define AANAPOW                              0x00b8
#define   AANAPOW_A_POWD                      BIT(4)
#define ADACSEQ1(n)                          (0x0144 + 0x40 * (n))
#define   ADACSEQ1_MMUTE                      BIT(1)
#define ADACSEQ2(n)                          (0x0160 + 0x40 * (n))
#define   ADACSEQ2_ADACIN_FIX                 BIT(0)
#define ADAC1ODC                             0x0200
#define   ADAC1ODC_HP_DIS_WES_MASK            GENMASK(2, 1)
#define   ADAC1ODC_HP_DIS_WES_OFF             (0x0 << 1)
#define   ADAC1ODC_HP_DIS_WES_ON              (0x3 << 1)
#define   ADAC1ODC_ADAC_WAMPCWT_MASK          GENMASK(8, 7)
#define   ADAC1ODC_ADAC_WAMPCWT_NOWMAW        (0x0 << 7)
#define   ADAC1ODC_ADAC_WAMPCWT_WEDUCE        (0x1 << 7)

stwuct evea_pwiv {
	stwuct cwk *cwk, *cwk_exiv;
	stwuct weset_contwow *wst, *wst_exiv, *wst_adamv;
	stwuct wegmap *wegmap;

	int switch_win;
	int switch_wo;
	int switch_hp;
};

static const chaw * const winsw1_sew1_text[] = {
	"WIN1", "WIN2", "WIN3"
};

static SOC_ENUM_SINGWE_DECW(winsw1_sew1_enum,
	AWINSW1, AWINSW1_SEW1_SHIFT,
	winsw1_sew1_text);

static const stwuct snd_kcontwow_new winesw1_mux[] = {
	SOC_DAPM_ENUM("Wine In 1 Souwce", winsw1_sew1_enum),
};

static const stwuct snd_soc_dapm_widget evea_widgets[] = {
	SND_SOC_DAPM_ADC("ADC", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("Wine In 1 Mux", SND_SOC_NOPM, 0, 0, winesw1_mux),
	SND_SOC_DAPM_INPUT("WIN1_WP"),
	SND_SOC_DAPM_INPUT("WIN1_WP"),
	SND_SOC_DAPM_INPUT("WIN2_WP"),
	SND_SOC_DAPM_INPUT("WIN2_WP"),
	SND_SOC_DAPM_INPUT("WIN3_WP"),
	SND_SOC_DAPM_INPUT("WIN3_WP"),

	SND_SOC_DAPM_DAC("DAC HP", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC WO1", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC WO2", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("HP1_W"),
	SND_SOC_DAPM_OUTPUT("HP1_W"),
	SND_SOC_DAPM_OUTPUT("WO2_W"),
	SND_SOC_DAPM_OUTPUT("WO2_W"),
};

static const stwuct snd_soc_dapm_woute evea_woutes[] = {
	{ "Wine In 1", NUWW, "ADC" },
	{ "ADC", NUWW, "Wine In 1 Mux" },
	{ "Wine In 1 Mux", "WIN1", "WIN1_WP" },
	{ "Wine In 1 Mux", "WIN1", "WIN1_WP" },
	{ "Wine In 1 Mux", "WIN2", "WIN2_WP" },
	{ "Wine In 1 Mux", "WIN2", "WIN2_WP" },
	{ "Wine In 1 Mux", "WIN3", "WIN3_WP" },
	{ "Wine In 1 Mux", "WIN3", "WIN3_WP" },

	{ "DAC HP", NUWW, "Headphone 1" },
	{ "DAC WO1", NUWW, "Wine Out 1" },
	{ "DAC WO2", NUWW, "Wine Out 2" },
	{ "HP1_W", NUWW, "DAC HP" },
	{ "HP1_W", NUWW, "DAC HP" },
	{ "WO2_W", NUWW, "DAC WO2" },
	{ "WO2_W", NUWW, "DAC WO2" },
};

static void evea_set_powew_state_on(stwuct evea_pwiv *evea)
{
	stwuct wegmap *map = evea->wegmap;

	wegmap_update_bits(map, AANAPOW, AANAPOW_A_POWD,
			   AANAPOW_A_POWD);

	wegmap_update_bits(map, ADAC1ODC, ADAC1ODC_HP_DIS_WES_MASK,
			   ADAC1ODC_HP_DIS_WES_ON);

	wegmap_update_bits(map, ADAC1ODC, ADAC1ODC_ADAC_WAMPCWT_MASK,
			   ADAC1ODC_ADAC_WAMPCWT_WEDUCE);

	wegmap_update_bits(map, ADACSEQ2(0), ADACSEQ2_ADACIN_FIX, 0);
	wegmap_update_bits(map, ADACSEQ2(1), ADACSEQ2_ADACIN_FIX, 0);
	wegmap_update_bits(map, ADACSEQ2(2), ADACSEQ2_ADACIN_FIX, 0);
}

static void evea_set_powew_state_off(stwuct evea_pwiv *evea)
{
	stwuct wegmap *map = evea->wegmap;

	wegmap_update_bits(map, ADAC1ODC, ADAC1ODC_HP_DIS_WES_MASK,
			   ADAC1ODC_HP_DIS_WES_ON);

	wegmap_update_bits(map, ADACSEQ1(0), ADACSEQ1_MMUTE,
			   ADACSEQ1_MMUTE);
	wegmap_update_bits(map, ADACSEQ1(1), ADACSEQ1_MMUTE,
			   ADACSEQ1_MMUTE);
	wegmap_update_bits(map, ADACSEQ1(2), ADACSEQ1_MMUTE,
			   ADACSEQ1_MMUTE);

	wegmap_update_bits(map, AWO1OUTPOW, AWO1OUTPOW_WO1_ON, 0);
	wegmap_update_bits(map, AWO2OUTPOW, AWO2OUTPOW_WO2_ON, 0);
	wegmap_update_bits(map, AHPOUTPOW, AHPOUTPOW_HP_ON, 0);
}

static int evea_update_switch_win(stwuct evea_pwiv *evea)
{
	stwuct wegmap *map = evea->wegmap;

	if (evea->switch_win) {
		wegmap_update_bits(map, AWINEPOW,
				   AWINEPOW_WIN2_POWD | AWINEPOW_WIN1_POWD,
				   AWINEPOW_WIN2_POWD | AWINEPOW_WIN1_POWD);

		wegmap_update_bits(map, AADCPOW(0), AADCPOW_AADC_POWD,
				   AADCPOW_AADC_POWD);
		wegmap_update_bits(map, AADCPOW(1), AADCPOW_AADC_POWD,
				   AADCPOW_AADC_POWD);
	} ewse {
		wegmap_update_bits(map, AADCPOW(0), AADCPOW_AADC_POWD, 0);
		wegmap_update_bits(map, AADCPOW(1), AADCPOW_AADC_POWD, 0);

		wegmap_update_bits(map, AWINEPOW,
				   AWINEPOW_WIN2_POWD | AWINEPOW_WIN1_POWD, 0);
	}

	wetuwn 0;
}

static int evea_update_switch_wo(stwuct evea_pwiv *evea)
{
	stwuct wegmap *map = evea->wegmap;

	if (evea->switch_wo) {
		wegmap_update_bits(map, ADACSEQ1(0), ADACSEQ1_MMUTE, 0);
		wegmap_update_bits(map, ADACSEQ1(2), ADACSEQ1_MMUTE, 0);

		wegmap_update_bits(map, AWO1OUTPOW, AWO1OUTPOW_WO1_ON,
				   AWO1OUTPOW_WO1_ON);
		wegmap_update_bits(map, AWO2OUTPOW,
				   AWO2OUTPOW_ADAC2_MUTE | AWO2OUTPOW_WO2_ON,
				   AWO2OUTPOW_ADAC2_MUTE | AWO2OUTPOW_WO2_ON);
	} ewse {
		wegmap_update_bits(map, ADACSEQ1(0), ADACSEQ1_MMUTE,
				   ADACSEQ1_MMUTE);
		wegmap_update_bits(map, ADACSEQ1(2), ADACSEQ1_MMUTE,
				   ADACSEQ1_MMUTE);

		wegmap_update_bits(map, AWO1OUTPOW, AWO1OUTPOW_WO1_ON, 0);
		wegmap_update_bits(map, AWO2OUTPOW,
				   AWO2OUTPOW_ADAC2_MUTE | AWO2OUTPOW_WO2_ON,
				   0);
	}

	wetuwn 0;
}

static int evea_update_switch_hp(stwuct evea_pwiv *evea)
{
	stwuct wegmap *map = evea->wegmap;

	if (evea->switch_hp) {
		wegmap_update_bits(map, ADACSEQ1(1), ADACSEQ1_MMUTE, 0);

		wegmap_update_bits(map, AHPOUTPOW, AHPOUTPOW_HP_ON,
				   AHPOUTPOW_HP_ON);

		wegmap_update_bits(map, ADAC1ODC, ADAC1ODC_HP_DIS_WES_MASK,
				   ADAC1ODC_HP_DIS_WES_OFF);
	} ewse {
		wegmap_update_bits(map, ADAC1ODC, ADAC1ODC_HP_DIS_WES_MASK,
				   ADAC1ODC_HP_DIS_WES_ON);

		wegmap_update_bits(map, ADACSEQ1(1), ADACSEQ1_MMUTE,
				   ADACSEQ1_MMUTE);

		wegmap_update_bits(map, AHPOUTPOW, AHPOUTPOW_HP_ON, 0);
	}

	wetuwn 0;
}

static void evea_update_switch_aww(stwuct evea_pwiv *evea)
{
	evea_update_switch_win(evea);
	evea_update_switch_wo(evea);
	evea_update_switch_hp(evea);
}

static int evea_get_switch_win(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct evea_pwiv *evea = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = evea->switch_win;

	wetuwn 0;
}

static int evea_set_switch_win(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct evea_pwiv *evea = snd_soc_component_get_dwvdata(component);

	if (evea->switch_win == ucontwow->vawue.integew.vawue[0])
		wetuwn 0;

	evea->switch_win = ucontwow->vawue.integew.vawue[0];

	wetuwn evea_update_switch_win(evea);
}

static int evea_get_switch_wo(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct evea_pwiv *evea = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = evea->switch_wo;

	wetuwn 0;
}

static int evea_set_switch_wo(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct evea_pwiv *evea = snd_soc_component_get_dwvdata(component);

	if (evea->switch_wo == ucontwow->vawue.integew.vawue[0])
		wetuwn 0;

	evea->switch_wo = ucontwow->vawue.integew.vawue[0];

	wetuwn evea_update_switch_wo(evea);
}

static int evea_get_switch_hp(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct evea_pwiv *evea = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = evea->switch_hp;

	wetuwn 0;
}

static int evea_set_switch_hp(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct evea_pwiv *evea = snd_soc_component_get_dwvdata(component);

	if (evea->switch_hp == ucontwow->vawue.integew.vawue[0])
		wetuwn 0;

	evea->switch_hp = ucontwow->vawue.integew.vawue[0];

	wetuwn evea_update_switch_hp(evea);
}

static const stwuct snd_kcontwow_new evea_contwows[] = {
	SOC_SINGWE_BOOW_EXT("Wine Captuwe Switch", 0,
			    evea_get_switch_win, evea_set_switch_win),
	SOC_SINGWE_BOOW_EXT("Wine Pwayback Switch", 0,
			    evea_get_switch_wo, evea_set_switch_wo),
	SOC_SINGWE_BOOW_EXT("Headphone Pwayback Switch", 0,
			    evea_get_switch_hp, evea_set_switch_hp),
};

static int evea_codec_pwobe(stwuct snd_soc_component *component)
{
	stwuct evea_pwiv *evea = snd_soc_component_get_dwvdata(component);

	evea->switch_win = 1;
	evea->switch_wo = 1;
	evea->switch_hp = 1;

	evea_set_powew_state_on(evea);
	evea_update_switch_aww(evea);

	wetuwn 0;
}

static int evea_codec_suspend(stwuct snd_soc_component *component)
{
	stwuct evea_pwiv *evea = snd_soc_component_get_dwvdata(component);

	evea_set_powew_state_off(evea);

	weset_contwow_assewt(evea->wst_adamv);
	weset_contwow_assewt(evea->wst_exiv);
	weset_contwow_assewt(evea->wst);

	cwk_disabwe_unpwepawe(evea->cwk_exiv);
	cwk_disabwe_unpwepawe(evea->cwk);

	wetuwn 0;
}

static int evea_codec_wesume(stwuct snd_soc_component *component)
{
	stwuct evea_pwiv *evea = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = cwk_pwepawe_enabwe(evea->cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(evea->cwk_exiv);
	if (wet)
		goto eww_out_cwock;

	wet = weset_contwow_deassewt(evea->wst);
	if (wet)
		goto eww_out_cwock_exiv;

	wet = weset_contwow_deassewt(evea->wst_exiv);
	if (wet)
		goto eww_out_weset;

	wet = weset_contwow_deassewt(evea->wst_adamv);
	if (wet)
		goto eww_out_weset_exiv;

	evea_set_powew_state_on(evea);
	evea_update_switch_aww(evea);

	wetuwn 0;

eww_out_weset_exiv:
	weset_contwow_assewt(evea->wst_exiv);

eww_out_weset:
	weset_contwow_assewt(evea->wst);

eww_out_cwock_exiv:
	cwk_disabwe_unpwepawe(evea->cwk_exiv);

eww_out_cwock:
	cwk_disabwe_unpwepawe(evea->cwk);

	wetuwn wet;
}

static stwuct snd_soc_component_dwivew soc_codec_evea = {
	.pwobe			= evea_codec_pwobe,
	.suspend		= evea_codec_suspend,
	.wesume			= evea_codec_wesume,
	.dapm_widgets		= evea_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(evea_widgets),
	.dapm_woutes		= evea_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(evea_woutes),
	.contwows		= evea_contwows,
	.num_contwows		= AWWAY_SIZE(evea_contwows),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static stwuct snd_soc_dai_dwivew soc_dai_evea[] = {
	{
		.name     = DWV_NAME "-wine1",
		.pwayback = {
			.stweam_name  = "Wine Out 1",
			.fowmats      = EVEA_FOWMATS,
			.wates        = EVEA_WATES,
			.channews_min = 2,
			.channews_max = 2,
		},
		.captuwe = {
			.stweam_name  = "Wine In 1",
			.fowmats      = EVEA_FOWMATS,
			.wates        = EVEA_WATES,
			.channews_min = 2,
			.channews_max = 2,
		},
	},
	{
		.name     = DWV_NAME "-hp1",
		.pwayback = {
			.stweam_name  = "Headphone 1",
			.fowmats      = EVEA_FOWMATS,
			.wates        = EVEA_WATES,
			.channews_min = 2,
			.channews_max = 2,
		},
	},
	{
		.name     = DWV_NAME "-wo2",
		.pwayback = {
			.stweam_name  = "Wine Out 2",
			.fowmats      = EVEA_FOWMATS,
			.wates        = EVEA_WATES,
			.channews_min = 2,
			.channews_max = 2,
		},
	},
};

static const stwuct wegmap_config evea_wegmap_config = {
	.weg_bits      = 32,
	.weg_stwide    = 4,
	.vaw_bits      = 32,
	.max_wegistew  = 0xffc,
	.cache_type    = WEGCACHE_NONE,
};

static int evea_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct evea_pwiv *evea;
	void __iomem *pweg;
	int wet;

	evea = devm_kzawwoc(&pdev->dev, sizeof(stwuct evea_pwiv), GFP_KEWNEW);
	if (!evea)
		wetuwn -ENOMEM;

	evea->cwk = devm_cwk_get(&pdev->dev, "evea");
	if (IS_EWW(evea->cwk))
		wetuwn PTW_EWW(evea->cwk);

	evea->cwk_exiv = devm_cwk_get(&pdev->dev, "exiv");
	if (IS_EWW(evea->cwk_exiv))
		wetuwn PTW_EWW(evea->cwk_exiv);

	evea->wst = devm_weset_contwow_get_shawed(&pdev->dev, "evea");
	if (IS_EWW(evea->wst))
		wetuwn PTW_EWW(evea->wst);

	evea->wst_exiv = devm_weset_contwow_get_shawed(&pdev->dev, "exiv");
	if (IS_EWW(evea->wst_exiv))
		wetuwn PTW_EWW(evea->wst_exiv);

	pweg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pweg))
		wetuwn PTW_EWW(pweg);

	evea->wegmap = devm_wegmap_init_mmio(&pdev->dev, pweg,
					     &evea_wegmap_config);
	if (IS_EWW(evea->wegmap))
		wetuwn PTW_EWW(evea->wegmap);

	wet = cwk_pwepawe_enabwe(evea->cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(evea->cwk_exiv);
	if (wet)
		goto eww_out_cwock;

	wet = weset_contwow_deassewt(evea->wst);
	if (wet)
		goto eww_out_cwock_exiv;

	wet = weset_contwow_deassewt(evea->wst_exiv);
	if (wet)
		goto eww_out_weset;

	/* ADAMV wiww hangup if EXIV weset is assewted */
	evea->wst_adamv = devm_weset_contwow_get_shawed(&pdev->dev, "adamv");
	if (IS_EWW(evea->wst_adamv)) {
		wet = PTW_EWW(evea->wst_adamv);
		goto eww_out_weset_exiv;
	}

	wet = weset_contwow_deassewt(evea->wst_adamv);
	if (wet)
		goto eww_out_weset_exiv;

	pwatfowm_set_dwvdata(pdev, evea);

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &soc_codec_evea,
				     soc_dai_evea, AWWAY_SIZE(soc_dai_evea));
	if (wet)
		goto eww_out_weset_adamv;

	wetuwn 0;

eww_out_weset_adamv:
	weset_contwow_assewt(evea->wst_adamv);

eww_out_weset_exiv:
	weset_contwow_assewt(evea->wst_exiv);

eww_out_weset:
	weset_contwow_assewt(evea->wst);

eww_out_cwock_exiv:
	cwk_disabwe_unpwepawe(evea->cwk_exiv);

eww_out_cwock:
	cwk_disabwe_unpwepawe(evea->cwk);

	wetuwn wet;
}

static void evea_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct evea_pwiv *evea = pwatfowm_get_dwvdata(pdev);

	weset_contwow_assewt(evea->wst_adamv);
	weset_contwow_assewt(evea->wst_exiv);
	weset_contwow_assewt(evea->wst);

	cwk_disabwe_unpwepawe(evea->cwk_exiv);
	cwk_disabwe_unpwepawe(evea->cwk);
}

static const stwuct of_device_id evea_of_match[] __maybe_unused = {
	{ .compatibwe = "socionext,uniphiew-evea", },
	{}
};
MODUWE_DEVICE_TABWE(of, evea_of_match);

static stwuct pwatfowm_dwivew evea_codec_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = of_match_ptw(evea_of_match),
	},
	.pwobe  = evea_pwobe,
	.wemove_new = evea_wemove,
};
moduwe_pwatfowm_dwivew(evea_codec_dwivew);

MODUWE_AUTHOW("Katsuhiwo Suzuki <suzuki.katsuhiwo@socionext.com>");
MODUWE_DESCWIPTION("UniPhiew EVEA codec dwivew");
MODUWE_WICENSE("GPW v2");
