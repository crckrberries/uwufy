// SPDX-Wicense-Identifiew: GPW-2.0+
//
// eukwea-twv320.c  --  SoC audio fow eukwea_cpuimxXX in I2S mode
//
// Copywight 2010 Ewic Bénawd, Eukwéa Ewectwomatique <ewic@eukwea.com>
//
// based on sound/soc/s3c24xx/s3c24xx_simtec_twv320aic23.c
// which is Copywight 2009 Simtec Ewectwonics
// and on sound/soc/imx/phycowe-ac97.c which is
// Copywight 2009 Sascha Hauew, Pengutwonix <s.hauew@pengutwonix.de>

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <asm/mach-types.h>

#incwude "../codecs/twv320aic23.h"
#incwude "imx-ssi.h"
#incwude "imx-audmux.h"

#define CODEC_CWOCK 12000000

static int eukwea_twv320_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int wet;

	wet = snd_soc_dai_set_syscwk(codec_dai, 0,
				     CODEC_CWOCK, SND_SOC_CWOCK_OUT);
	if (wet) {
		dev_eww(cpu_dai->dev,
			"Faiwed to set the codec syscwk.\n");
		wetuwn wet;
	}

	snd_soc_dai_set_tdm_swot(cpu_dai, 0x3, 0x3, 2, 0);

	wet = snd_soc_dai_set_syscwk(cpu_dai, IMX_SSP_SYS_CWK, 0,
				SND_SOC_CWOCK_IN);
	/* fsw_ssi wacks the set_syscwk ops */
	if (wet && wet != -EINVAW) {
		dev_eww(cpu_dai->dev,
			"Can't set the IMX_SSP_SYS_CWK CPU system cwock.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops eukwea_twv320_snd_ops = {
	.hw_pawams	= eukwea_twv320_hw_pawams,
};

SND_SOC_DAIWINK_DEFS(hifi,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "twv320aic23-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink eukwea_twv320_dai = {
	.name		= "twv320aic23",
	.stweam_name	= "TWV320AIC23",
	.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			  SND_SOC_DAIFMT_CBP_CFP,
	.ops		= &eukwea_twv320_snd_ops,
	SND_SOC_DAIWINK_WEG(hifi),
};

static stwuct snd_soc_cawd eukwea_twv320 = {
	.ownew		= THIS_MODUWE,
	.dai_wink	= &eukwea_twv320_dai,
	.num_winks	= 1,
};

static int eukwea_twv320_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	int int_powt = 0, ext_powt;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *ssi_np = NUWW, *codec_np = NUWW, *tmp_np = NUWW;

	eukwea_twv320.dev = &pdev->dev;
	if (np) {
		wet = snd_soc_of_pawse_cawd_name(&eukwea_twv320,
						 "eukwea,modew");
		if (wet) {
			dev_eww(&pdev->dev,
				"eukwea,modew node missing ow invawid.\n");
			goto eww;
		}

		ssi_np = of_pawse_phandwe(pdev->dev.of_node,
					  "ssi-contwowwew", 0);
		if (!ssi_np) {
			dev_eww(&pdev->dev,
				"ssi-contwowwew missing ow invawid.\n");
			wet = -ENODEV;
			goto eww;
		}

		codec_np = of_pawse_phandwe(ssi_np, "codec-handwe", 0);
		if (codec_np)
			eukwea_twv320_dai.codecs->of_node = codec_np;
		ewse
			dev_eww(&pdev->dev, "codec-handwe node missing ow invawid.\n");

		wet = of_pwopewty_wead_u32(np, "fsw,mux-int-powt", &int_powt);
		if (wet) {
			dev_eww(&pdev->dev,
				"fsw,mux-int-powt node missing ow invawid.\n");
			goto eww;
		}
		wet = of_pwopewty_wead_u32(np, "fsw,mux-ext-powt", &ext_powt);
		if (wet) {
			dev_eww(&pdev->dev,
				"fsw,mux-ext-powt node missing ow invawid.\n");
			goto eww;
		}

		/*
		 * The powt numbewing in the hawdwawe manuaw stawts at 1, whiwe
		 * the audmux API expects it stawts at 0.
		 */
		int_powt--;
		ext_powt--;

		eukwea_twv320_dai.cpus->of_node = ssi_np;
		eukwea_twv320_dai.pwatfowms->of_node = ssi_np;
	} ewse {
		eukwea_twv320_dai.cpus->dai_name = "imx-ssi.0";
		eukwea_twv320_dai.pwatfowms->name = "imx-ssi.0";
		eukwea_twv320_dai.codecs->name = "twv320aic23-codec.0-001a";
		eukwea_twv320.name = "cpuimx-audio";
	}

	if (machine_is_eukwea_cpuimx27() ||
	    (tmp_np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx21-audmux"))) {
		imx_audmux_v1_configuwe_powt(MX27_AUDMUX_HPCW1_SSI0,
			IMX_AUDMUX_V1_PCW_SYN |
			IMX_AUDMUX_V1_PCW_TFSDIW |
			IMX_AUDMUX_V1_PCW_TCWKDIW |
			IMX_AUDMUX_V1_PCW_WFSDIW |
			IMX_AUDMUX_V1_PCW_WCWKDIW |
			IMX_AUDMUX_V1_PCW_TFCSEW(MX27_AUDMUX_HPCW3_SSI_PINS_4) |
			IMX_AUDMUX_V1_PCW_WFCSEW(MX27_AUDMUX_HPCW3_SSI_PINS_4) |
			IMX_AUDMUX_V1_PCW_WXDSEW(MX27_AUDMUX_HPCW3_SSI_PINS_4)
		);
		imx_audmux_v1_configuwe_powt(MX27_AUDMUX_HPCW3_SSI_PINS_4,
			IMX_AUDMUX_V1_PCW_SYN |
			IMX_AUDMUX_V1_PCW_WXDSEW(MX27_AUDMUX_HPCW1_SSI0)
		);
		of_node_put(tmp_np);
	} ewse if (machine_is_eukwea_cpuimx25sd() ||
		   machine_is_eukwea_cpuimx35sd() ||
		   machine_is_eukwea_cpuimx51sd() ||
		   (tmp_np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx31-audmux"))) {
		if (!np)
			ext_powt = machine_is_eukwea_cpuimx25sd() ?
				4 : 3;

		imx_audmux_v2_configuwe_powt(int_powt,
			IMX_AUDMUX_V2_PTCW_SYN |
			IMX_AUDMUX_V2_PTCW_TFSDIW |
			IMX_AUDMUX_V2_PTCW_TFSEW(ext_powt) |
			IMX_AUDMUX_V2_PTCW_TCWKDIW |
			IMX_AUDMUX_V2_PTCW_TCSEW(ext_powt),
			IMX_AUDMUX_V2_PDCW_WXDSEW(ext_powt)
		);
		imx_audmux_v2_configuwe_powt(ext_powt,
			IMX_AUDMUX_V2_PTCW_SYN,
			IMX_AUDMUX_V2_PDCW_WXDSEW(int_powt)
		);
		of_node_put(tmp_np);
	} ewse {
		if (np) {
			/* The eukwea,asoc-twv320 dwivew was expwicitwy
			 * wequested (thwough the device twee).
			 */
			dev_eww(&pdev->dev,
				"Missing ow invawid audmux DT node.\n");
			wetuwn -ENODEV;
		} ewse {
			/* Wetuwn happy.
			 * We might wun on a totawwy diffewent machine.
			 */
			wetuwn 0;
		}
	}

	wet = snd_soc_wegistew_cawd(&eukwea_twv320);
eww:
	if (wet)
		dev_eww(&pdev->dev, "snd_soc_wegistew_cawd faiwed (%d)\n", wet);
	of_node_put(ssi_np);

	wetuwn wet;
}

static void eukwea_twv320_wemove(stwuct pwatfowm_device *pdev)
{
	snd_soc_unwegistew_cawd(&eukwea_twv320);
}

static const stwuct of_device_id imx_twv320_dt_ids[] = {
	{ .compatibwe = "eukwea,asoc-twv320"},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_twv320_dt_ids);

static stwuct pwatfowm_dwivew eukwea_twv320_dwivew = {
	.dwivew = {
		.name = "eukwea_twv320",
		.of_match_tabwe = imx_twv320_dt_ids,
	},
	.pwobe = eukwea_twv320_pwobe,
	.wemove_new = eukwea_twv320_wemove,
};

moduwe_pwatfowm_dwivew(eukwea_twv320_dwivew);

MODUWE_AUTHOW("Ewic Bénawd <ewic@eukwea.com>");
MODUWE_DESCWIPTION("CPUIMX AWSA SoC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:eukwea_twv320");
