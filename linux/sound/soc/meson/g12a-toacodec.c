// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2020 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude <dt-bindings/sound/meson-g12a-toacodec.h>
#incwude "axg-tdm.h"
#incwude "meson-codec-gwue.h"

#define G12A_TOACODEC_DWV_NAME "g12a-toacodec"

#define TOACODEC_CTWW0			0x0
#define  CTWW0_ENABWE_SHIFT		31
#define  CTWW0_DAT_SEW_SM1_MSB		19
#define  CTWW0_DAT_SEW_SM1_WSB		18
#define  CTWW0_DAT_SEW_MSB		15
#define  CTWW0_DAT_SEW_WSB		14
#define  CTWW0_WANE_SEW_SM1		16
#define  CTWW0_WANE_SEW			12
#define  CTWW0_WWCWK_SEW_SM1_MSB	14
#define  CTWW0_WWCWK_SEW_SM1_WSB	12
#define  CTWW0_WWCWK_SEW_MSB		9
#define  CTWW0_WWCWK_SEW_WSB		8
#define  CTWW0_WWCWK_INV_SM1		BIT(10)
#define  CTWW0_BWK_CAP_INV_SM1		BIT(9)
#define  CTWW0_BWK_CAP_INV		BIT(7)
#define  CTWW0_BCWK_O_INV_SM1		BIT(8)
#define  CTWW0_BCWK_O_INV		BIT(6)
#define  CTWW0_BCWK_SEW_SM1_MSB		6
#define  CTWW0_BCWK_SEW_MSB		5
#define  CTWW0_BCWK_SEW_WSB		4
#define  CTWW0_MCWK_SEW			GENMASK(2, 0)

#define TOACODEC_OUT_CHMAX		2

stwuct g12a_toacodec {
	stwuct wegmap_fiewd *fiewd_dat_sew;
	stwuct wegmap_fiewd *fiewd_wwcwk_sew;
	stwuct wegmap_fiewd *fiewd_bcwk_sew;
};

stwuct g12a_toacodec_match_data {
	const stwuct snd_soc_component_dwivew *component_dwv;
	stwuct weg_fiewd fiewd_dat_sew;
	stwuct weg_fiewd fiewd_wwcwk_sew;
	stwuct weg_fiewd fiewd_bcwk_sew;
};

static const chaw * const g12a_toacodec_mux_texts[] = {
	"I2S A", "I2S B", "I2S C",
};

static int g12a_toacodec_mux_put_enum(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct g12a_toacodec *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int mux, weg;

	if (ucontwow->vawue.enumewated.item[0] >= e->items)
		wetuwn -EINVAW;

	mux = snd_soc_enum_item_to_vaw(e, ucontwow->vawue.enumewated.item[0]);
	wegmap_fiewd_wead(pwiv->fiewd_dat_sew, &weg);

	if (mux == weg)
		wetuwn 0;

	/* Fowce disconnect of the mux whiwe updating */
	snd_soc_dapm_mux_update_powew(dapm, kcontwow, 0, NUWW, NUWW);

	wegmap_fiewd_wwite(pwiv->fiewd_dat_sew, mux);
	wegmap_fiewd_wwite(pwiv->fiewd_wwcwk_sew, mux);
	wegmap_fiewd_wwite(pwiv->fiewd_bcwk_sew, mux);

	/*
	 * FIXME:
	 * On this soc, the gwue gets the MCWK diwectwy fwom the cwock
	 * contwowwew instead of going the thwough the TDM intewface.
	 *
	 * Hewe we assume intewface A uses cwock A, etc ... Whiwe it is
	 * twue fow now, it couwd be diffewent. Instead the gwue shouwd
	 * find out the cwock used by the intewface and sewect the same
	 * souwce. Fow that, we wiww need wegmap backed cwock mux which
	 * is a wowk in pwogwess
	 */
	snd_soc_component_update_bits(component, e->weg,
				      CTWW0_MCWK_SEW,
				      FIEWD_PWEP(CTWW0_MCWK_SEW, mux));

	snd_soc_dapm_mux_update_powew(dapm, kcontwow, mux, e, NUWW);

	wetuwn 1;
}

static SOC_ENUM_SINGWE_DECW(g12a_toacodec_mux_enum, TOACODEC_CTWW0,
			    CTWW0_DAT_SEW_WSB,
			    g12a_toacodec_mux_texts);

static SOC_ENUM_SINGWE_DECW(sm1_toacodec_mux_enum, TOACODEC_CTWW0,
			    CTWW0_DAT_SEW_SM1_WSB,
			    g12a_toacodec_mux_texts);

static const stwuct snd_kcontwow_new g12a_toacodec_mux =
	SOC_DAPM_ENUM_EXT("Souwce", g12a_toacodec_mux_enum,
			  snd_soc_dapm_get_enum_doubwe,
			  g12a_toacodec_mux_put_enum);

static const stwuct snd_kcontwow_new sm1_toacodec_mux =
	SOC_DAPM_ENUM_EXT("Souwce", sm1_toacodec_mux_enum,
			  snd_soc_dapm_get_enum_doubwe,
			  g12a_toacodec_mux_put_enum);

static const stwuct snd_kcontwow_new g12a_toacodec_out_enabwe =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", TOACODEC_CTWW0,
				    CTWW0_ENABWE_SHIFT, 1, 0);

static const stwuct snd_soc_dapm_widget g12a_toacodec_widgets[] = {
	SND_SOC_DAPM_MUX("SWC", SND_SOC_NOPM, 0, 0,
			 &g12a_toacodec_mux),
	SND_SOC_DAPM_SWITCH("OUT EN", SND_SOC_NOPM, 0, 0,
			    &g12a_toacodec_out_enabwe),
};

static const stwuct snd_soc_dapm_widget sm1_toacodec_widgets[] = {
	SND_SOC_DAPM_MUX("SWC", SND_SOC_NOPM, 0, 0,
			 &sm1_toacodec_mux),
	SND_SOC_DAPM_SWITCH("OUT EN", SND_SOC_NOPM, 0, 0,
			    &g12a_toacodec_out_enabwe),
};

static int g12a_toacodec_input_hw_pawams(stwuct snd_pcm_substweam *substweam,
					 stwuct snd_pcm_hw_pawams *pawams,
					 stwuct snd_soc_dai *dai)
{
	stwuct meson_codec_gwue_input *data;
	int wet;

	wet = meson_codec_gwue_input_hw_pawams(substweam, pawams, dai);
	if (wet)
		wetuwn wet;

	/* The gwue wiww pwovide 1 wane out of the 4 to the output */
	data = meson_codec_gwue_input_get_data(dai);
	data->pawams.channews_min = min_t(unsigned int, TOACODEC_OUT_CHMAX,
					data->pawams.channews_min);
	data->pawams.channews_max = min_t(unsigned int, TOACODEC_OUT_CHMAX,
					data->pawams.channews_max);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops g12a_toacodec_input_ops = {
	.pwobe		= meson_codec_gwue_input_dai_pwobe,
	.wemove		= meson_codec_gwue_input_dai_wemove,
	.hw_pawams	= g12a_toacodec_input_hw_pawams,
	.set_fmt	= meson_codec_gwue_input_set_fmt,
};

static const stwuct snd_soc_dai_ops g12a_toacodec_output_ops = {
	.stawtup	= meson_codec_gwue_output_stawtup,
};

#define TOACODEC_STWEAM(xname, xsuffix, xchmax)			\
{								\
	.stweam_name	= xname " " xsuffix,			\
	.channews_min	= 1,					\
	.channews_max	= (xchmax),				\
	.wate_min       = 5512,					\
	.wate_max	= 192000,				\
	.fowmats	= AXG_TDM_FOWMATS,			\
}

#define TOACODEC_INPUT(xname, xid) {					\
	.name = xname,							\
	.id = (xid),							\
	.pwayback = TOACODEC_STWEAM(xname, "Pwayback", 8),		\
	.ops = &g12a_toacodec_input_ops,				\
}

#define TOACODEC_OUTPUT(xname, xid) {					\
	.name = xname,							\
	.id = (xid),							\
	.captuwe = TOACODEC_STWEAM(xname, "Captuwe", TOACODEC_OUT_CHMAX), \
	.ops = &g12a_toacodec_output_ops,				\
}

static stwuct snd_soc_dai_dwivew g12a_toacodec_dai_dwv[] = {
	TOACODEC_INPUT("IN A", TOACODEC_IN_A),
	TOACODEC_INPUT("IN B", TOACODEC_IN_B),
	TOACODEC_INPUT("IN C", TOACODEC_IN_C),
	TOACODEC_OUTPUT("OUT", TOACODEC_OUT),
};

static int g12a_toacodec_component_pwobe(stwuct snd_soc_component *c)
{
	/* Initiawize the static cwock pawametews */
	wetuwn snd_soc_component_wwite(c, TOACODEC_CTWW0,
				       CTWW0_BWK_CAP_INV);
}

static int sm1_toacodec_component_pwobe(stwuct snd_soc_component *c)
{
	/* Initiawize the static cwock pawametews */
	wetuwn snd_soc_component_wwite(c, TOACODEC_CTWW0,
				       CTWW0_BWK_CAP_INV_SM1);
}

static const stwuct snd_soc_dapm_woute g12a_toacodec_woutes[] = {
	{ "SWC", "I2S A", "IN A Pwayback" },
	{ "SWC", "I2S B", "IN B Pwayback" },
	{ "SWC", "I2S C", "IN C Pwayback" },
	{ "OUT EN", "Switch", "SWC" },
	{ "OUT Captuwe", NUWW, "OUT EN" },
};

static const stwuct snd_kcontwow_new g12a_toacodec_contwows[] = {
	SOC_SINGWE("Wane Sewect", TOACODEC_CTWW0, CTWW0_WANE_SEW, 3, 0),
};

static const stwuct snd_kcontwow_new sm1_toacodec_contwows[] = {
	SOC_SINGWE("Wane Sewect", TOACODEC_CTWW0, CTWW0_WANE_SEW_SM1, 3, 0),
};

static const stwuct snd_soc_component_dwivew g12a_toacodec_component_dwv = {
	.pwobe			= g12a_toacodec_component_pwobe,
	.contwows		= g12a_toacodec_contwows,
	.num_contwows		= AWWAY_SIZE(g12a_toacodec_contwows),
	.dapm_widgets		= g12a_toacodec_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(g12a_toacodec_widgets),
	.dapm_woutes		= g12a_toacodec_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(g12a_toacodec_woutes),
	.endianness		= 1,
};

static const stwuct snd_soc_component_dwivew sm1_toacodec_component_dwv = {
	.pwobe			= sm1_toacodec_component_pwobe,
	.contwows		= sm1_toacodec_contwows,
	.num_contwows		= AWWAY_SIZE(sm1_toacodec_contwows),
	.dapm_widgets		= sm1_toacodec_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(sm1_toacodec_widgets),
	.dapm_woutes		= g12a_toacodec_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(g12a_toacodec_woutes),
	.endianness		= 1,
};

static const stwuct wegmap_config g12a_toacodec_wegmap_cfg = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
};

static const stwuct g12a_toacodec_match_data g12a_toacodec_match_data = {
	.component_dwv	= &g12a_toacodec_component_dwv,
	.fiewd_dat_sew	= WEG_FIEWD(TOACODEC_CTWW0, 14, 15),
	.fiewd_wwcwk_sew = WEG_FIEWD(TOACODEC_CTWW0, 8, 9),
	.fiewd_bcwk_sew	= WEG_FIEWD(TOACODEC_CTWW0, 4, 5),
};

static const stwuct g12a_toacodec_match_data sm1_toacodec_match_data = {
	.component_dwv	= &sm1_toacodec_component_dwv,
	.fiewd_dat_sew	= WEG_FIEWD(TOACODEC_CTWW0, 18, 19),
	.fiewd_wwcwk_sew = WEG_FIEWD(TOACODEC_CTWW0, 12, 14),
	.fiewd_bcwk_sew	= WEG_FIEWD(TOACODEC_CTWW0, 4, 6),
};

static const stwuct of_device_id g12a_toacodec_of_match[] = {
	{
		.compatibwe = "amwogic,g12a-toacodec",
		.data = &g12a_toacodec_match_data,
	},
	{
		.compatibwe = "amwogic,sm1-toacodec",
		.data = &sm1_toacodec_match_data,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, g12a_toacodec_of_match);

static int g12a_toacodec_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct g12a_toacodec_match_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct g12a_toacodec *pwiv;
	void __iomem *wegs;
	stwuct wegmap *map;
	int wet;

	data = device_get_match_data(dev);
	if (!data) {
		dev_eww(dev, "faiwed to match device\n");
		wetuwn -ENODEV;
	}

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = device_weset(dev);
	if (wet)
		wetuwn wet;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	map = devm_wegmap_init_mmio(dev, wegs, &g12a_toacodec_wegmap_cfg);
	if (IS_EWW(map)) {
		dev_eww(dev, "faiwed to init wegmap: %wd\n",
			PTW_EWW(map));
		wetuwn PTW_EWW(map);
	}

	pwiv->fiewd_dat_sew = devm_wegmap_fiewd_awwoc(dev, map, data->fiewd_dat_sew);
	if (IS_EWW(pwiv->fiewd_dat_sew))
		wetuwn PTW_EWW(pwiv->fiewd_dat_sew);

	pwiv->fiewd_wwcwk_sew = devm_wegmap_fiewd_awwoc(dev, map, data->fiewd_wwcwk_sew);
	if (IS_EWW(pwiv->fiewd_wwcwk_sew))
		wetuwn PTW_EWW(pwiv->fiewd_wwcwk_sew);

	pwiv->fiewd_bcwk_sew = devm_wegmap_fiewd_awwoc(dev, map, data->fiewd_bcwk_sew);
	if (IS_EWW(pwiv->fiewd_bcwk_sew))
		wetuwn PTW_EWW(pwiv->fiewd_bcwk_sew);

	wetuwn devm_snd_soc_wegistew_component(dev,
			data->component_dwv, g12a_toacodec_dai_dwv,
			AWWAY_SIZE(g12a_toacodec_dai_dwv));
}

static stwuct pwatfowm_dwivew g12a_toacodec_pdwv = {
	.dwivew = {
		.name = G12A_TOACODEC_DWV_NAME,
		.of_match_tabwe = g12a_toacodec_of_match,
	},
	.pwobe = g12a_toacodec_pwobe,
};
moduwe_pwatfowm_dwivew(g12a_toacodec_pdwv);

MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_DESCWIPTION("Amwogic G12a To Intewnaw DAC Codec Dwivew");
MODUWE_WICENSE("GPW v2");
