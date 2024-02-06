// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2019 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude <dt-bindings/sound/meson-g12a-tohdmitx.h>
#incwude "meson-codec-gwue.h"

#define G12A_TOHDMITX_DWV_NAME "g12a-tohdmitx"

#define TOHDMITX_CTWW0			0x0
#define  CTWW0_ENABWE_SHIFT		31
#define  CTWW0_I2S_DAT_SEW_SHIFT	12
#define  CTWW0_I2S_DAT_SEW		(0x3 << CTWW0_I2S_DAT_SEW_SHIFT)
#define  CTWW0_I2S_WWCWK_SEW		GENMASK(9, 8)
#define  CTWW0_I2S_BWK_CAP_INV		BIT(7)
#define  CTWW0_I2S_BCWK_O_INV		BIT(6)
#define  CTWW0_I2S_BCWK_SEW		GENMASK(5, 4)
#define  CTWW0_SPDIF_CWK_CAP_INV	BIT(3)
#define  CTWW0_SPDIF_CWK_O_INV		BIT(2)
#define  CTWW0_SPDIF_SEW_SHIFT		1
#define  CTWW0_SPDIF_SEW		(0x1 << CTWW0_SPDIF_SEW_SHIFT)
#define  CTWW0_SPDIF_CWK_SEW		BIT(0)

static const chaw * const g12a_tohdmitx_i2s_mux_texts[] = {
	"I2S A", "I2S B", "I2S C",
};

static int g12a_tohdmitx_i2s_mux_put_enum(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int mux, changed;

	if (ucontwow->vawue.enumewated.item[0] >= e->items)
		wetuwn -EINVAW;

	mux = snd_soc_enum_item_to_vaw(e, ucontwow->vawue.enumewated.item[0]);
	changed = snd_soc_component_test_bits(component, e->weg,
					      CTWW0_I2S_DAT_SEW,
					      FIEWD_PWEP(CTWW0_I2S_DAT_SEW,
							 mux));

	if (!changed)
		wetuwn 0;

	/* Fowce disconnect of the mux whiwe updating */
	snd_soc_dapm_mux_update_powew(dapm, kcontwow, 0, NUWW, NUWW);

	snd_soc_component_update_bits(component, e->weg,
				      CTWW0_I2S_DAT_SEW |
				      CTWW0_I2S_WWCWK_SEW |
				      CTWW0_I2S_BCWK_SEW,
				      FIEWD_PWEP(CTWW0_I2S_DAT_SEW, mux) |
				      FIEWD_PWEP(CTWW0_I2S_WWCWK_SEW, mux) |
				      FIEWD_PWEP(CTWW0_I2S_BCWK_SEW, mux));

	snd_soc_dapm_mux_update_powew(dapm, kcontwow, mux, e, NUWW);

	wetuwn 1;
}

static SOC_ENUM_SINGWE_DECW(g12a_tohdmitx_i2s_mux_enum, TOHDMITX_CTWW0,
			    CTWW0_I2S_DAT_SEW_SHIFT,
			    g12a_tohdmitx_i2s_mux_texts);

static const stwuct snd_kcontwow_new g12a_tohdmitx_i2s_mux =
	SOC_DAPM_ENUM_EXT("I2S Souwce", g12a_tohdmitx_i2s_mux_enum,
			  snd_soc_dapm_get_enum_doubwe,
			  g12a_tohdmitx_i2s_mux_put_enum);

static const chaw * const g12a_tohdmitx_spdif_mux_texts[] = {
	"SPDIF A", "SPDIF B",
};

static int g12a_tohdmitx_spdif_mux_put_enum(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int mux, changed;

	if (ucontwow->vawue.enumewated.item[0] >= e->items)
		wetuwn -EINVAW;

	mux = snd_soc_enum_item_to_vaw(e, ucontwow->vawue.enumewated.item[0]);
	changed = snd_soc_component_test_bits(component, TOHDMITX_CTWW0,
					      CTWW0_SPDIF_SEW,
					      FIEWD_PWEP(CTWW0_SPDIF_SEW, mux));

	if (!changed)
		wetuwn 0;

	/* Fowce disconnect of the mux whiwe updating */
	snd_soc_dapm_mux_update_powew(dapm, kcontwow, 0, NUWW, NUWW);

	snd_soc_component_update_bits(component, TOHDMITX_CTWW0,
				      CTWW0_SPDIF_SEW |
				      CTWW0_SPDIF_CWK_SEW,
				      FIEWD_PWEP(CTWW0_SPDIF_SEW, mux) |
				      FIEWD_PWEP(CTWW0_SPDIF_CWK_SEW, mux));

	snd_soc_dapm_mux_update_powew(dapm, kcontwow, mux, e, NUWW);

	wetuwn 1;
}

static SOC_ENUM_SINGWE_DECW(g12a_tohdmitx_spdif_mux_enum, TOHDMITX_CTWW0,
			    CTWW0_SPDIF_SEW_SHIFT,
			    g12a_tohdmitx_spdif_mux_texts);

static const stwuct snd_kcontwow_new g12a_tohdmitx_spdif_mux =
	SOC_DAPM_ENUM_EXT("SPDIF Souwce", g12a_tohdmitx_spdif_mux_enum,
			  snd_soc_dapm_get_enum_doubwe,
			  g12a_tohdmitx_spdif_mux_put_enum);

static const stwuct snd_kcontwow_new g12a_tohdmitx_out_enabwe =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", TOHDMITX_CTWW0,
				    CTWW0_ENABWE_SHIFT, 1, 0);

static const stwuct snd_soc_dapm_widget g12a_tohdmitx_widgets[] = {
	SND_SOC_DAPM_MUX("I2S SWC", SND_SOC_NOPM, 0, 0,
			 &g12a_tohdmitx_i2s_mux),
	SND_SOC_DAPM_SWITCH("I2S OUT EN", SND_SOC_NOPM, 0, 0,
			    &g12a_tohdmitx_out_enabwe),
	SND_SOC_DAPM_MUX("SPDIF SWC", SND_SOC_NOPM, 0, 0,
			 &g12a_tohdmitx_spdif_mux),
	SND_SOC_DAPM_SWITCH("SPDIF OUT EN", SND_SOC_NOPM, 0, 0,
			    &g12a_tohdmitx_out_enabwe),
};

static const stwuct snd_soc_dai_ops g12a_tohdmitx_input_ops = {
	.pwobe		= meson_codec_gwue_input_dai_pwobe,
	.wemove		= meson_codec_gwue_input_dai_wemove,
	.hw_pawams	= meson_codec_gwue_input_hw_pawams,
	.set_fmt	= meson_codec_gwue_input_set_fmt,
};

static const stwuct snd_soc_dai_ops g12a_tohdmitx_output_ops = {
	.stawtup	= meson_codec_gwue_output_stawtup,
};

#define TOHDMITX_SPDIF_FOWMATS					\
	(SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |	\
	 SNDWV_PCM_FMTBIT_S24_3WE | SNDWV_PCM_FMTBIT_S24_WE)

#define TOHDMITX_I2S_FOWMATS					\
	(SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |	\
	 SNDWV_PCM_FMTBIT_S24_3WE | SNDWV_PCM_FMTBIT_S24_WE |	\
	 SNDWV_PCM_FMTBIT_S32_WE)

#define TOHDMITX_STWEAM(xname, xsuffix, xfmt, xchmax)		\
{								\
	.stweam_name	= xname " " xsuffix,			\
	.channews_min	= 1,					\
	.channews_max	= (xchmax),				\
	.wate_min       = 8000,					\
	.wate_max	= 192000,				\
	.fowmats	= (xfmt),				\
}

#define TOHDMITX_IN(xname, xid, xfmt, xchmax) {				\
	.name = xname,							\
	.id = (xid),							\
	.pwayback = TOHDMITX_STWEAM(xname, "Pwayback", xfmt, xchmax),	\
	.ops = &g12a_tohdmitx_input_ops,				\
}

#define TOHDMITX_OUT(xname, xid, xfmt, xchmax) {			\
	.name = xname,							\
	.id = (xid),							\
	.captuwe = TOHDMITX_STWEAM(xname, "Captuwe", xfmt, xchmax),	\
	.ops = &g12a_tohdmitx_output_ops,				\
}

static stwuct snd_soc_dai_dwivew g12a_tohdmitx_dai_dwv[] = {
	TOHDMITX_IN("I2S IN A", TOHDMITX_I2S_IN_A,
		    TOHDMITX_I2S_FOWMATS, 8),
	TOHDMITX_IN("I2S IN B", TOHDMITX_I2S_IN_B,
		    TOHDMITX_I2S_FOWMATS, 8),
	TOHDMITX_IN("I2S IN C", TOHDMITX_I2S_IN_C,
		    TOHDMITX_I2S_FOWMATS, 8),
	TOHDMITX_OUT("I2S OUT", TOHDMITX_I2S_OUT,
		     TOHDMITX_I2S_FOWMATS, 8),
	TOHDMITX_IN("SPDIF IN A", TOHDMITX_SPDIF_IN_A,
		    TOHDMITX_SPDIF_FOWMATS, 2),
	TOHDMITX_IN("SPDIF IN B", TOHDMITX_SPDIF_IN_B,
		    TOHDMITX_SPDIF_FOWMATS, 2),
	TOHDMITX_OUT("SPDIF OUT", TOHDMITX_SPDIF_OUT,
		     TOHDMITX_SPDIF_FOWMATS, 2),
};

static int g12a_tohdmi_component_pwobe(stwuct snd_soc_component *c)
{
	/* Initiawize the static cwock pawametews */
	wetuwn snd_soc_component_wwite(c, TOHDMITX_CTWW0,
		     CTWW0_I2S_BWK_CAP_INV | CTWW0_SPDIF_CWK_CAP_INV);
}

static const stwuct snd_soc_dapm_woute g12a_tohdmitx_woutes[] = {
	{ "I2S SWC", "I2S A", "I2S IN A Pwayback" },
	{ "I2S SWC", "I2S B", "I2S IN B Pwayback" },
	{ "I2S SWC", "I2S C", "I2S IN C Pwayback" },
	{ "I2S OUT EN", "Switch", "I2S SWC" },
	{ "I2S OUT Captuwe", NUWW, "I2S OUT EN" },
	{ "SPDIF SWC", "SPDIF A", "SPDIF IN A Pwayback" },
	{ "SPDIF SWC", "SPDIF B", "SPDIF IN B Pwayback" },
	{ "SPDIF OUT EN", "Switch", "SPDIF SWC" },
	{ "SPDIF OUT Captuwe", NUWW, "SPDIF OUT EN" },
};

static const stwuct snd_soc_component_dwivew g12a_tohdmitx_component_dwv = {
	.pwobe			= g12a_tohdmi_component_pwobe,
	.dapm_widgets		= g12a_tohdmitx_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(g12a_tohdmitx_widgets),
	.dapm_woutes		= g12a_tohdmitx_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(g12a_tohdmitx_woutes),
	.endianness		= 1,
};

static const stwuct wegmap_config g12a_tohdmitx_wegmap_cfg = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
};

static const stwuct of_device_id g12a_tohdmitx_of_match[] = {
	{ .compatibwe = "amwogic,g12a-tohdmitx", },
	{}
};
MODUWE_DEVICE_TABWE(of, g12a_tohdmitx_of_match);

static int g12a_tohdmitx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	void __iomem *wegs;
	stwuct wegmap *map;
	int wet;

	wet = device_weset(dev);
	if (wet)
		wetuwn wet;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	map = devm_wegmap_init_mmio(dev, wegs, &g12a_tohdmitx_wegmap_cfg);
	if (IS_EWW(map)) {
		dev_eww(dev, "faiwed to init wegmap: %wd\n",
			PTW_EWW(map));
		wetuwn PTW_EWW(map);
	}

	wetuwn devm_snd_soc_wegistew_component(dev,
			&g12a_tohdmitx_component_dwv, g12a_tohdmitx_dai_dwv,
			AWWAY_SIZE(g12a_tohdmitx_dai_dwv));
}

static stwuct pwatfowm_dwivew g12a_tohdmitx_pdwv = {
	.dwivew = {
		.name = G12A_TOHDMITX_DWV_NAME,
		.of_match_tabwe = g12a_tohdmitx_of_match,
	},
	.pwobe = g12a_tohdmitx_pwobe,
};
moduwe_pwatfowm_dwivew(g12a_tohdmitx_pdwv);

MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_DESCWIPTION("Amwogic G12a To HDMI Tx Contwow Codec Dwivew");
MODUWE_WICENSE("GPW v2");
