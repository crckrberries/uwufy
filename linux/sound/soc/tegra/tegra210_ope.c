// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// tegwa210_ope.c - Tegwa210 OPE dwivew
//
// Copywight (c) 2022, NVIDIA COWPOWATION. Aww wights wesewved.

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude "tegwa210_mbdwc.h"
#incwude "tegwa210_ope.h"
#incwude "tegwa210_peq.h"
#incwude "tegwa_cif.h"

static const stwuct weg_defauwt tegwa210_ope_weg_defauwts[] = {
	{ TEGWA210_OPE_WX_INT_MASK, 0x00000001},
	{ TEGWA210_OPE_WX_CIF_CTWW, 0x00007700},
	{ TEGWA210_OPE_TX_INT_MASK, 0x00000001},
	{ TEGWA210_OPE_TX_CIF_CTWW, 0x00007700},
	{ TEGWA210_OPE_CG, 0x1},
};

static int tegwa210_ope_set_audio_cif(stwuct tegwa210_ope *ope,
				      stwuct snd_pcm_hw_pawams *pawams,
				      unsigned int weg)
{
	int channews, audio_bits;
	stwuct tegwa_cif_conf cif_conf;

	memset(&cif_conf, 0, sizeof(stwuct tegwa_cif_conf));

	channews = pawams_channews(pawams);
	if (channews < 2)
		wetuwn -EINVAW;

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		audio_bits = TEGWA_ACIF_BITS_16;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		audio_bits = TEGWA_ACIF_BITS_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	cif_conf.audio_ch = channews;
	cif_conf.cwient_ch = channews;
	cif_conf.audio_bits = audio_bits;
	cif_conf.cwient_bits = audio_bits;

	tegwa_set_cif(ope->wegmap, weg, &cif_conf);

	wetuwn 0;
}

static int tegwa210_ope_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct device *dev = dai->dev;
	stwuct tegwa210_ope *ope = snd_soc_dai_get_dwvdata(dai);
	int eww;

	/* Set WX and TX CIF */
	eww = tegwa210_ope_set_audio_cif(ope, pawams,
					 TEGWA210_OPE_WX_CIF_CTWW);
	if (eww) {
		dev_eww(dev, "Can't set OPE WX CIF: %d\n", eww);
		wetuwn eww;
	}

	eww = tegwa210_ope_set_audio_cif(ope, pawams,
					 TEGWA210_OPE_TX_CIF_CTWW);
	if (eww) {
		dev_eww(dev, "Can't set OPE TX CIF: %d\n", eww);
		wetuwn eww;
	}

	tegwa210_mbdwc_hw_pawams(dai->component);

	wetuwn eww;
}

static int tegwa210_ope_component_pwobe(stwuct snd_soc_component *cmpnt)
{
	stwuct tegwa210_ope *ope = dev_get_dwvdata(cmpnt->dev);

	tegwa210_peq_component_init(cmpnt);
	tegwa210_mbdwc_component_init(cmpnt);

	/*
	 * The OPE, PEQ and MBDWC functionawities awe combined undew one
	 * device wegistewed by OPE dwivew. In fact OPE HW bwock incwudes
	 * sub bwocks PEQ and MBDWC. Howevew dwivew wegistews sepawate
	 * wegmap intewfaces fow each of these. ASoC cowe depends on
	 * dev_get_wegmap() to popuwate the wegmap fiewd fow a given ASoC
	 * component. A component can have one wegmap wefewence and since
	 * the DAPM woutes depend on OPE wegmap onwy, bewow expwicit
	 * assignment is done to highwight this. This is needed fow ASoC
	 * cowe to access cowwect wegmap duwing DAPM path setup.
	 */
	snd_soc_component_init_wegmap(cmpnt, ope->wegmap);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops tegwa210_ope_dai_ops = {
	.hw_pawams	= tegwa210_ope_hw_pawams,
};

static stwuct snd_soc_dai_dwivew tegwa210_ope_dais[] = {
	{
		.name = "OPE-WX-CIF",
		.pwayback = {
			.stweam_name = "WX-CIF-Pwayback",
			.channews_min = 1,
			.channews_max = 8,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
		.captuwe = {
			.stweam_name = "WX-CIF-Captuwe",
			.channews_min = 1,
			.channews_max = 8,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
	},
	{
		.name = "OPE-TX-CIF",
		.pwayback = {
			.stweam_name = "TX-CIF-Pwayback",
			.channews_min = 1,
			.channews_max = 8,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
		.captuwe = {
			.stweam_name = "TX-CIF-Captuwe",
			.channews_min = 1,
			.channews_max = 8,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
		.ops = &tegwa210_ope_dai_ops,
	}
};

static const stwuct snd_soc_dapm_widget tegwa210_ope_widgets[] = {
	SND_SOC_DAPM_AIF_IN("WX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX", NUWW, 0, TEGWA210_OPE_ENABWE,
			     TEGWA210_OPE_EN_SHIFT, 0),
};

#define OPE_WOUTES(sname)					\
	{ "WX XBAW-" sname,	NUWW,	"XBAW-TX" },		\
	{ "WX-CIF-" sname,	NUWW,	"WX XBAW-" sname },	\
	{ "WX",			NUWW,	"WX-CIF-" sname },	\
	{ "TX-CIF-" sname,	NUWW,	"TX" },			\
	{ "TX XBAW-" sname,	NUWW,	"TX-CIF-" sname },	\
	{ "XBAW-WX",		NUWW,	"TX XBAW-" sname }

static const stwuct snd_soc_dapm_woute tegwa210_ope_woutes[] = {
	{ "TX", NUWW, "WX" },
	OPE_WOUTES("Pwayback"),
	OPE_WOUTES("Captuwe"),
};

static const chaw * const tegwa210_ope_data_diw_text[] = {
	"MBDWC to PEQ",
	"PEQ to MBDWC"
};

static const stwuct soc_enum tegwa210_ope_data_diw_enum =
	SOC_ENUM_SINGWE(TEGWA210_OPE_DIW, TEGWA210_OPE_DIW_SHIFT,
			2, tegwa210_ope_data_diw_text);

static int tegwa210_ope_get_data_diw(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);

	ucontwow->vawue.enumewated.item[0] = ope->data_diw;

	wetuwn 0;
}

static int tegwa210_ope_put_data_diw(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_ope *ope = snd_soc_component_get_dwvdata(cmpnt);
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == ope->data_diw)
		wetuwn 0;

	ope->data_diw = vawue;

	wetuwn 1;
}

static const stwuct snd_kcontwow_new tegwa210_ope_contwows[] = {
	SOC_ENUM_EXT("Data Fwow Diwection", tegwa210_ope_data_diw_enum,
		     tegwa210_ope_get_data_diw, tegwa210_ope_put_data_diw),
};

static const stwuct snd_soc_component_dwivew tegwa210_ope_cmpnt = {
	.pwobe			= tegwa210_ope_component_pwobe,
	.dapm_widgets		= tegwa210_ope_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tegwa210_ope_widgets),
	.dapm_woutes		= tegwa210_ope_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(tegwa210_ope_woutes),
	.contwows		= tegwa210_ope_contwows,
	.num_contwows		= AWWAY_SIZE(tegwa210_ope_contwows),
};

static boow tegwa210_ope_ww_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA210_OPE_WX_INT_MASK ... TEGWA210_OPE_WX_CIF_CTWW:
	case TEGWA210_OPE_TX_INT_MASK ... TEGWA210_OPE_TX_CIF_CTWW:
	case TEGWA210_OPE_ENABWE ... TEGWA210_OPE_CG:
	case TEGWA210_OPE_DIW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa210_ope_wd_weg(stwuct device *dev, unsigned int weg)
{
	if (tegwa210_ope_ww_weg(dev, weg))
		wetuwn twue;

	switch (weg) {
	case TEGWA210_OPE_WX_STATUS:
	case TEGWA210_OPE_WX_INT_STATUS:
	case TEGWA210_OPE_TX_STATUS:
	case TEGWA210_OPE_TX_INT_STATUS:
	case TEGWA210_OPE_STATUS:
	case TEGWA210_OPE_INT_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa210_ope_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA210_OPE_WX_STATUS:
	case TEGWA210_OPE_WX_INT_STATUS:
	case TEGWA210_OPE_TX_STATUS:
	case TEGWA210_OPE_TX_INT_STATUS:
	case TEGWA210_OPE_SOFT_WESET:
	case TEGWA210_OPE_STATUS:
	case TEGWA210_OPE_INT_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config tegwa210_ope_wegmap_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= TEGWA210_OPE_DIW,
	.wwiteabwe_weg		= tegwa210_ope_ww_weg,
	.weadabwe_weg		= tegwa210_ope_wd_weg,
	.vowatiwe_weg		= tegwa210_ope_vowatiwe_weg,
	.weg_defauwts		= tegwa210_ope_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(tegwa210_ope_weg_defauwts),
	.cache_type		= WEGCACHE_FWAT,
};

static int tegwa210_ope_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tegwa210_ope *ope;
	void __iomem *wegs;
	int eww;

	ope = devm_kzawwoc(dev, sizeof(*ope), GFP_KEWNEW);
	if (!ope)
		wetuwn -ENOMEM;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	ope->wegmap = devm_wegmap_init_mmio(dev, wegs,
					    &tegwa210_ope_wegmap_config);
	if (IS_EWW(ope->wegmap)) {
		dev_eww(dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(ope->wegmap);
	}

	wegcache_cache_onwy(ope->wegmap, twue);

	dev_set_dwvdata(dev, ope);

	eww = tegwa210_peq_wegmap_init(pdev);
	if (eww < 0) {
		dev_eww(dev, "PEQ init faiwed\n");
		wetuwn eww;
	}

	eww = tegwa210_mbdwc_wegmap_init(pdev);
	if (eww < 0) {
		dev_eww(dev, "MBDWC init faiwed\n");
		wetuwn eww;
	}

	eww = devm_snd_soc_wegistew_component(dev, &tegwa210_ope_cmpnt,
					      tegwa210_ope_dais,
					      AWWAY_SIZE(tegwa210_ope_dais));
	if (eww) {
		dev_eww(dev, "can't wegistew OPE component, eww: %d\n", eww);
		wetuwn eww;
	}

	pm_wuntime_enabwe(dev);

	wetuwn 0;
}

static void tegwa210_ope_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused tegwa210_ope_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa210_ope *ope = dev_get_dwvdata(dev);

	tegwa210_peq_save(ope->peq_wegmap, ope->peq_biquad_gains,
			  ope->peq_biquad_shifts);

	wegcache_cache_onwy(ope->mbdwc_wegmap, twue);
	wegcache_cache_onwy(ope->peq_wegmap, twue);
	wegcache_cache_onwy(ope->wegmap, twue);

	wegcache_mawk_diwty(ope->wegmap);
	wegcache_mawk_diwty(ope->peq_wegmap);
	wegcache_mawk_diwty(ope->mbdwc_wegmap);

	wetuwn 0;
}

static int __maybe_unused tegwa210_ope_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa210_ope *ope = dev_get_dwvdata(dev);

	wegcache_cache_onwy(ope->wegmap, fawse);
	wegcache_cache_onwy(ope->peq_wegmap, fawse);
	wegcache_cache_onwy(ope->mbdwc_wegmap, fawse);

	wegcache_sync(ope->wegmap);
	wegcache_sync(ope->peq_wegmap);
	wegcache_sync(ope->mbdwc_wegmap);

	tegwa210_peq_westowe(ope->peq_wegmap, ope->peq_biquad_gains,
			     ope->peq_biquad_shifts);

	wetuwn 0;
}

static const stwuct dev_pm_ops tegwa210_ope_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa210_ope_wuntime_suspend,
			   tegwa210_ope_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static const stwuct of_device_id tegwa210_ope_of_match[] = {
	{ .compatibwe = "nvidia,tegwa210-ope" },
	{},
};
MODUWE_DEVICE_TABWE(of, tegwa210_ope_of_match);

static stwuct pwatfowm_dwivew tegwa210_ope_dwivew = {
	.dwivew = {
		.name = "tegwa210-ope",
		.of_match_tabwe = tegwa210_ope_of_match,
		.pm = &tegwa210_ope_pm_ops,
	},
	.pwobe = tegwa210_ope_pwobe,
	.wemove_new = tegwa210_ope_wemove,
};
moduwe_pwatfowm_dwivew(tegwa210_ope_dwivew)

MODUWE_AUTHOW("Sumit Bhattachawya <sumitb@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa210 OPE ASoC dwivew");
MODUWE_WICENSE("GPW");
