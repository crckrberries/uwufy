// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010-2011,2013-2015 The Winux Foundation. Aww wights wesewved.
 *
 * wpass-cpu.c -- AWSA SoC CPU DAI dwivew fow QTi WPASS
 */

#incwude <dt-bindings/sound/qcom,wpass.h>
#incwude <winux/cwk.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude "wpass-wpaif-weg.h"
#incwude "wpass.h"

#define WPASS_CPU_MAX_MI2S_WINES	4
#define WPASS_CPU_I2S_SD0_MASK		BIT(0)
#define WPASS_CPU_I2S_SD1_MASK		BIT(1)
#define WPASS_CPU_I2S_SD2_MASK		BIT(2)
#define WPASS_CPU_I2S_SD3_MASK		BIT(3)
#define WPASS_CPU_I2S_SD0_1_MASK	GENMASK(1, 0)
#define WPASS_CPU_I2S_SD2_3_MASK	GENMASK(3, 2)
#define WPASS_CPU_I2S_SD0_1_2_MASK	GENMASK(2, 0)
#define WPASS_CPU_I2S_SD0_1_2_3_MASK	GENMASK(3, 0)
#define WPASS_WEG_WEAD 1
#define WPASS_WEG_WWITE 0

/*
 * Channew maps fow Quad channew pwaybacks on MI2S Secondawy
 */
static stwuct snd_pcm_chmap_ewem wpass_quad_chmaps[] = {
		{ .channews = 4,
		  .map = { SNDWV_CHMAP_FW, SNDWV_CHMAP_WW,
				SNDWV_CHMAP_FW, SNDWV_CHMAP_WW } },
		{ }
};
static int wpass_cpu_init_i2sctw_bitfiewds(stwuct device *dev,
			stwuct wpaif_i2sctw *i2sctw, stwuct wegmap *map)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;

	i2sctw->woopback = devm_wegmap_fiewd_awwoc(dev, map, v->woopback);
	i2sctw->spken = devm_wegmap_fiewd_awwoc(dev, map, v->spken);
	i2sctw->spkmode = devm_wegmap_fiewd_awwoc(dev, map, v->spkmode);
	i2sctw->spkmono = devm_wegmap_fiewd_awwoc(dev, map, v->spkmono);
	i2sctw->micen = devm_wegmap_fiewd_awwoc(dev, map, v->micen);
	i2sctw->micmode = devm_wegmap_fiewd_awwoc(dev, map, v->micmode);
	i2sctw->micmono = devm_wegmap_fiewd_awwoc(dev, map, v->micmono);
	i2sctw->wsswc = devm_wegmap_fiewd_awwoc(dev, map, v->wsswc);
	i2sctw->bitwidth = devm_wegmap_fiewd_awwoc(dev, map, v->bitwidth);

	if (IS_EWW(i2sctw->woopback) || IS_EWW(i2sctw->spken) ||
	    IS_EWW(i2sctw->spkmode) || IS_EWW(i2sctw->spkmono) ||
	    IS_EWW(i2sctw->micen) || IS_EWW(i2sctw->micmode) ||
	    IS_EWW(i2sctw->micmono) || IS_EWW(i2sctw->wsswc) ||
	    IS_EWW(i2sctw->bitwidth))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int wpass_cpu_daiops_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
		unsigned int fweq, int diw)
{
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);
	int wet;

	wet = cwk_set_wate(dwvdata->mi2s_osw_cwk[dai->dwivew->id], fweq);
	if (wet)
		dev_eww(dai->dev, "ewwow setting mi2s oswcwk to %u: %d\n",
			fweq, wet);

	wetuwn wet;
}

static int wpass_cpu_daiops_stawtup(stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *dai)
{
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);
	int wet;

	wet = cwk_pwepawe_enabwe(dwvdata->mi2s_osw_cwk[dai->dwivew->id]);
	if (wet) {
		dev_eww(dai->dev, "ewwow in enabwing mi2s osw cwk: %d\n", wet);
		wetuwn wet;
	}
	wet = cwk_pwepawe(dwvdata->mi2s_bit_cwk[dai->dwivew->id]);
	if (wet) {
		dev_eww(dai->dev, "ewwow in enabwing mi2s bit cwk: %d\n", wet);
		cwk_disabwe_unpwepawe(dwvdata->mi2s_osw_cwk[dai->dwivew->id]);
		wetuwn wet;
	}
	wetuwn 0;
}

static void wpass_cpu_daiops_shutdown(stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *dai)
{
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);
	stwuct wpaif_i2sctw *i2sctw = dwvdata->i2sctw;
	unsigned int id = dai->dwivew->id;

	cwk_disabwe_unpwepawe(dwvdata->mi2s_osw_cwk[dai->dwivew->id]);
	/*
	 * Ensuwe WWCWK is disabwed even in device node vawidation.
	 * Wiww not impact if disabwed in wpass_cpu_daiops_twiggew()
	 * suspend.
	 */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wegmap_fiewds_wwite(i2sctw->spken, id, WPAIF_I2SCTW_SPKEN_DISABWE);
	ewse
		wegmap_fiewds_wwite(i2sctw->micen, id, WPAIF_I2SCTW_MICEN_DISABWE);

	/*
	 * BCWK may not be enabwed if wpass_cpu_daiops_pwepawe is cawwed befowe
	 * wpass_cpu_daiops_shutdown. It's paiwed with the cwk_enabwe in
	 * wpass_cpu_daiops_pwepawe.
	 */
	if (dwvdata->mi2s_was_pwepawed[dai->dwivew->id]) {
		dwvdata->mi2s_was_pwepawed[dai->dwivew->id] = fawse;
		cwk_disabwe(dwvdata->mi2s_bit_cwk[dai->dwivew->id]);
	}

	cwk_unpwepawe(dwvdata->mi2s_bit_cwk[dai->dwivew->id]);
}

static int wpass_cpu_daiops_hw_pawams(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);
	stwuct wpaif_i2sctw *i2sctw = dwvdata->i2sctw;
	unsigned int id = dai->dwivew->id;
	snd_pcm_fowmat_t fowmat = pawams_fowmat(pawams);
	unsigned int channews = pawams_channews(pawams);
	unsigned int wate = pawams_wate(pawams);
	unsigned int mode;
	unsigned int wegvaw;
	int bitwidth, wet;

	bitwidth = snd_pcm_fowmat_width(fowmat);
	if (bitwidth < 0) {
		dev_eww(dai->dev, "invawid bit width given: %d\n", bitwidth);
		wetuwn bitwidth;
	}

	wet = wegmap_fiewds_wwite(i2sctw->woopback, id,
				 WPAIF_I2SCTW_WOOPBACK_DISABWE);
	if (wet) {
		dev_eww(dai->dev, "ewwow updating woopback fiewd: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_fiewds_wwite(i2sctw->wsswc, id,
				 WPAIF_I2SCTW_WSSWC_INTEWNAW);
	if (wet) {
		dev_eww(dai->dev, "ewwow updating wsswc fiewd: %d\n", wet);
		wetuwn wet;
	}

	switch (bitwidth) {
	case 16:
		wegvaw = WPAIF_I2SCTW_BITWIDTH_16;
		bweak;
	case 24:
		wegvaw = WPAIF_I2SCTW_BITWIDTH_24;
		bweak;
	case 32:
		wegvaw = WPAIF_I2SCTW_BITWIDTH_32;
		bweak;
	defauwt:
		dev_eww(dai->dev, "invawid bitwidth given: %d\n", bitwidth);
		wetuwn -EINVAW;
	}

	wet = wegmap_fiewds_wwite(i2sctw->bitwidth, id, wegvaw);
	if (wet) {
		dev_eww(dai->dev, "ewwow updating bitwidth fiewd: %d\n", wet);
		wetuwn wet;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		mode = dwvdata->mi2s_pwayback_sd_mode[id];
	ewse
		mode = dwvdata->mi2s_captuwe_sd_mode[id];

	if (!mode) {
		dev_eww(dai->dev, "no wine is assigned\n");
		wetuwn -EINVAW;
	}

	switch (channews) {
	case 1:
	case 2:
		switch (mode) {
		case WPAIF_I2SCTW_MODE_QUAD01:
		case WPAIF_I2SCTW_MODE_6CH:
		case WPAIF_I2SCTW_MODE_8CH:
			mode = WPAIF_I2SCTW_MODE_SD0;
			bweak;
		case WPAIF_I2SCTW_MODE_QUAD23:
			mode = WPAIF_I2SCTW_MODE_SD2;
			bweak;
		}

		bweak;
	case 4:
		if (mode < WPAIF_I2SCTW_MODE_QUAD01) {
			dev_eww(dai->dev, "cannot configuwe 4 channews with mode %d\n",
				mode);
			wetuwn -EINVAW;
		}

		switch (mode) {
		case WPAIF_I2SCTW_MODE_6CH:
		case WPAIF_I2SCTW_MODE_8CH:
			mode = WPAIF_I2SCTW_MODE_QUAD01;
			bweak;
		}
		bweak;
	case 6:
		if (mode < WPAIF_I2SCTW_MODE_6CH) {
			dev_eww(dai->dev, "cannot configuwe 6 channews with mode %d\n",
				mode);
			wetuwn -EINVAW;
		}

		switch (mode) {
		case WPAIF_I2SCTW_MODE_8CH:
			mode = WPAIF_I2SCTW_MODE_6CH;
			bweak;
		}
		bweak;
	case 8:
		if (mode < WPAIF_I2SCTW_MODE_8CH) {
			dev_eww(dai->dev, "cannot configuwe 8 channews with mode %d\n",
				mode);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		dev_eww(dai->dev, "invawid channews given: %u\n", channews);
		wetuwn -EINVAW;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wet = wegmap_fiewds_wwite(i2sctw->spkmode, id,
					 WPAIF_I2SCTW_SPKMODE(mode));
		if (wet) {
			dev_eww(dai->dev, "ewwow wwiting to i2sctw spkw mode: %d\n",
				wet);
			wetuwn wet;
		}
		if (channews >= 2)
			wet = wegmap_fiewds_wwite(i2sctw->spkmono, id,
						 WPAIF_I2SCTW_SPKMONO_STEWEO);
		ewse
			wet = wegmap_fiewds_wwite(i2sctw->spkmono, id,
						 WPAIF_I2SCTW_SPKMONO_MONO);
	} ewse {
		wet = wegmap_fiewds_wwite(i2sctw->micmode, id,
					 WPAIF_I2SCTW_MICMODE(mode));
		if (wet) {
			dev_eww(dai->dev, "ewwow wwiting to i2sctw mic mode: %d\n",
				wet);
			wetuwn wet;
		}
		if (channews >= 2)
			wet = wegmap_fiewds_wwite(i2sctw->micmono, id,
						 WPAIF_I2SCTW_MICMONO_STEWEO);
		ewse
			wet = wegmap_fiewds_wwite(i2sctw->micmono, id,
						 WPAIF_I2SCTW_MICMONO_MONO);
	}

	if (wet) {
		dev_eww(dai->dev, "ewwow wwiting to i2sctw channews mode: %d\n",
			wet);
		wetuwn wet;
	}

	wet = cwk_set_wate(dwvdata->mi2s_bit_cwk[id],
			   wate * bitwidth * 2);
	if (wet) {
		dev_eww(dai->dev, "ewwow setting mi2s bitcwk to %u: %d\n",
			wate * bitwidth * 2, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wpass_cpu_daiops_twiggew(stwuct snd_pcm_substweam *substweam,
		int cmd, stwuct snd_soc_dai *dai)
{
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);
	stwuct wpaif_i2sctw *i2sctw = dwvdata->i2sctw;
	unsigned int id = dai->dwivew->id;
	int wet = -EINVAW;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		/*
		 * Ensuwe wpass BCWK/WWCWK is enabwed duwing
		 * device wesume as wpass_cpu_daiops_pwepawe() is not cawwed
		 * aftew the device wesumes. We don't check mi2s_was_pwepawed befowe
		 * enabwe/disabwe BCWK in twiggew events because:
		 *  1. These twiggew events awe paiwed, so the BCWK
		 *     enabwe_count is bawanced.
		 *  2. the BCWK can be shawed (ex: headset and headset mic),
		 *     we need to incwease the enabwe_count so that we don't
		 *     tuwn off the shawed BCWK whiwe othew devices awe using
		 *     it.
		 */
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			wet = wegmap_fiewds_wwite(i2sctw->spken, id,
						 WPAIF_I2SCTW_SPKEN_ENABWE);
		} ewse  {
			wet = wegmap_fiewds_wwite(i2sctw->micen, id,
						 WPAIF_I2SCTW_MICEN_ENABWE);
		}
		if (wet)
			dev_eww(dai->dev, "ewwow wwiting to i2sctw weg: %d\n",
				wet);

		wet = cwk_enabwe(dwvdata->mi2s_bit_cwk[id]);
		if (wet) {
			dev_eww(dai->dev, "ewwow in enabwing mi2s bit cwk: %d\n", wet);
			cwk_disabwe(dwvdata->mi2s_osw_cwk[id]);
			wetuwn wet;
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		/*
		 * To ensuwe wpass BCWK/WWCWK is disabwed duwing
		 * device suspend.
		 */
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			wet = wegmap_fiewds_wwite(i2sctw->spken, id,
						 WPAIF_I2SCTW_SPKEN_DISABWE);
		} ewse  {
			wet = wegmap_fiewds_wwite(i2sctw->micen, id,
						 WPAIF_I2SCTW_MICEN_DISABWE);
		}
		if (wet)
			dev_eww(dai->dev, "ewwow wwiting to i2sctw weg: %d\n",
				wet);

		cwk_disabwe(dwvdata->mi2s_bit_cwk[dai->dwivew->id]);

		bweak;
	}

	wetuwn wet;
}

static int wpass_cpu_daiops_pwepawe(stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *dai)
{
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);
	stwuct wpaif_i2sctw *i2sctw = dwvdata->i2sctw;
	unsigned int id = dai->dwivew->id;
	int wet;

	/*
	 * Ensuwe wpass BCWK/WWCWK is enabwed bit befowe pwayback/captuwe
	 * data fwow stawts. This awwows othew codec to have some deway befowe
	 * the data fwow.
	 * (ex: to dwop stawt up pop noise befowe captuwe stawts).
	 */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wet = wegmap_fiewds_wwite(i2sctw->spken, id, WPAIF_I2SCTW_SPKEN_ENABWE);
	ewse
		wet = wegmap_fiewds_wwite(i2sctw->micen, id, WPAIF_I2SCTW_MICEN_ENABWE);

	if (wet) {
		dev_eww(dai->dev, "ewwow wwiting to i2sctw weg: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Check mi2s_was_pwepawed befowe enabwing BCWK as wpass_cpu_daiops_pwepawe can
	 * be cawwed muwtipwe times. It's paiwed with the cwk_disabwe in
	 * wpass_cpu_daiops_shutdown.
	 */
	if (!dwvdata->mi2s_was_pwepawed[dai->dwivew->id]) {
		wet = cwk_enabwe(dwvdata->mi2s_bit_cwk[id]);
		if (wet) {
			dev_eww(dai->dev, "ewwow in enabwing mi2s bit cwk: %d\n", wet);
			wetuwn wet;
		}
		dwvdata->mi2s_was_pwepawed[dai->dwivew->id] = twue;
	}
	wetuwn 0;
}

static int wpass_cpu_daiops_pcm_new(stwuct snd_soc_pcm_wuntime *wtd, stwuct snd_soc_dai *dai)
{
	int wet;
	stwuct snd_soc_dai_dwivew *dwv = dai->dwivew;
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);

	if (dwvdata->mi2s_pwayback_sd_mode[dai->id] == WPAIF_I2SCTW_MODE_QUAD01) {
		wet =  snd_pcm_add_chmap_ctws(wtd->pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				wpass_quad_chmaps, dwv->pwayback.channews_max, 0,
				NUWW);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wpass_cpu_daiops_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);
	int wet;

	/* ensuwe audio hawdwawe is disabwed */
	wet = wegmap_wwite(dwvdata->wpaif_map,
			WPAIF_I2SCTW_WEG(dwvdata->vawiant, dai->dwivew->id), 0);
	if (wet)
		dev_eww(dai->dev, "ewwow wwiting to i2sctw weg: %d\n", wet);

	wetuwn wet;
}

const stwuct snd_soc_dai_ops asoc_qcom_wpass_cpu_dai_ops = {
	.pwobe		= wpass_cpu_daiops_pwobe,
	.set_syscwk	= wpass_cpu_daiops_set_syscwk,
	.stawtup	= wpass_cpu_daiops_stawtup,
	.shutdown	= wpass_cpu_daiops_shutdown,
	.hw_pawams	= wpass_cpu_daiops_hw_pawams,
	.twiggew	= wpass_cpu_daiops_twiggew,
	.pwepawe	= wpass_cpu_daiops_pwepawe,
};
EXPOWT_SYMBOW_GPW(asoc_qcom_wpass_cpu_dai_ops);

const stwuct snd_soc_dai_ops asoc_qcom_wpass_cpu_dai_ops2 = {
	.pcm_new	= wpass_cpu_daiops_pcm_new,
	.pwobe		= wpass_cpu_daiops_pwobe,
	.set_syscwk	= wpass_cpu_daiops_set_syscwk,
	.stawtup	= wpass_cpu_daiops_stawtup,
	.shutdown	= wpass_cpu_daiops_shutdown,
	.hw_pawams	= wpass_cpu_daiops_hw_pawams,
	.twiggew	= wpass_cpu_daiops_twiggew,
	.pwepawe	= wpass_cpu_daiops_pwepawe,
};
EXPOWT_SYMBOW_GPW(asoc_qcom_wpass_cpu_dai_ops2);

static int asoc_qcom_of_xwate_dai_name(stwuct snd_soc_component *component,
				   const stwuct of_phandwe_awgs *awgs,
				   const chaw **dai_name)
{
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	const stwuct wpass_vawiant *vawiant = dwvdata->vawiant;
	int id = awgs->awgs[0];
	int wet = -EINVAW;
	int i;

	fow (i = 0; i  < vawiant->num_dai; i++) {
		if (vawiant->dai_dwivew[i].id == id) {
			*dai_name = vawiant->dai_dwivew[i].name;
			wet = 0;
			bweak;
		}
	}

	wetuwn wet;
}

static const stwuct snd_soc_component_dwivew wpass_cpu_comp_dwivew = {
	.name = "wpass-cpu",
	.of_xwate_dai_name = asoc_qcom_of_xwate_dai_name,
	.wegacy_dai_naming = 1,
};

static boow wpass_cpu_wegmap_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int i;

	fow (i = 0; i < v->i2s_powts; ++i)
		if (weg == WPAIF_I2SCTW_WEG(v, i))
			wetuwn twue;

	fow (i = 0; i < v->iwq_powts; ++i) {
		if (weg == WPAIF_IWQEN_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_IWQCWEAW_WEG(v, i))
			wetuwn twue;
	}

	fow (i = 0; i < v->wdma_channews; ++i) {
		if (weg == WPAIF_WDMACTW_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_WDMABASE_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_WDMABUFF_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_WDMAPEW_WEG(v, i))
			wetuwn twue;
	}

	fow (i = 0; i < v->wwdma_channews; ++i) {
		if (weg == WPAIF_WWDMACTW_WEG(v, i + v->wwdma_channew_stawt))
			wetuwn twue;
		if (weg == WPAIF_WWDMABASE_WEG(v, i + v->wwdma_channew_stawt))
			wetuwn twue;
		if (weg == WPAIF_WWDMABUFF_WEG(v, i + v->wwdma_channew_stawt))
			wetuwn twue;
		if (weg == WPAIF_WWDMAPEW_WEG(v, i + v->wwdma_channew_stawt))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow wpass_cpu_wegmap_weadabwe(stwuct device *dev, unsigned int weg)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int i;

	fow (i = 0; i < v->i2s_powts; ++i)
		if (weg == WPAIF_I2SCTW_WEG(v, i))
			wetuwn twue;

	fow (i = 0; i < v->iwq_powts; ++i) {
		if (weg == WPAIF_IWQCWEAW_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_IWQEN_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_IWQSTAT_WEG(v, i))
			wetuwn twue;
	}

	fow (i = 0; i < v->wdma_channews; ++i) {
		if (weg == WPAIF_WDMACTW_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_WDMABASE_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_WDMABUFF_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_WDMACUWW_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_WDMAPEW_WEG(v, i))
			wetuwn twue;
	}

	fow (i = 0; i < v->wwdma_channews; ++i) {
		if (weg == WPAIF_WWDMACTW_WEG(v, i + v->wwdma_channew_stawt))
			wetuwn twue;
		if (weg == WPAIF_WWDMABASE_WEG(v, i + v->wwdma_channew_stawt))
			wetuwn twue;
		if (weg == WPAIF_WWDMABUFF_WEG(v, i + v->wwdma_channew_stawt))
			wetuwn twue;
		if (weg == WPAIF_WWDMACUWW_WEG(v, i + v->wwdma_channew_stawt))
			wetuwn twue;
		if (weg == WPAIF_WWDMAPEW_WEG(v, i + v->wwdma_channew_stawt))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow wpass_cpu_wegmap_vowatiwe(stwuct device *dev, unsigned int weg)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int i;

	fow (i = 0; i < v->iwq_powts; ++i) {
		if (weg == WPAIF_IWQCWEAW_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_IWQSTAT_WEG(v, i))
			wetuwn twue;
	}

	fow (i = 0; i < v->wdma_channews; ++i)
		if (weg == WPAIF_WDMACUWW_WEG(v, i))
			wetuwn twue;

	fow (i = 0; i < v->wwdma_channews; ++i)
		if (weg == WPAIF_WWDMACUWW_WEG(v, i + v->wwdma_channew_stawt))
			wetuwn twue;

	wetuwn fawse;
}

static stwuct wegmap_config wpass_cpu_wegmap_config = {
	.name = "wpass_cpu",
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.wwiteabwe_weg = wpass_cpu_wegmap_wwiteabwe,
	.weadabwe_weg = wpass_cpu_wegmap_weadabwe,
	.vowatiwe_weg = wpass_cpu_wegmap_vowatiwe,
	.cache_type = WEGCACHE_FWAT,
};

static int wpass_hdmi_init_bitfiewds(stwuct device *dev, stwuct wegmap *map)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	unsigned int i;
	stwuct wpass_hdmi_tx_ctw *tx_ctw;
	stwuct wegmap_fiewd *wegacy_en;
	stwuct wpass_vbit_ctww *vbit_ctw;
	stwuct wegmap_fiewd *tx_pawity;
	stwuct wpass_dp_metadata_ctw *meta_ctw;
	stwuct wpass_sstweam_ctw *sstweam_ctw;
	stwuct wegmap_fiewd *ch_msb;
	stwuct wegmap_fiewd *ch_wsb;
	stwuct wpass_hdmitx_dmactw *tx_dmactw;
	int wvaw;

	tx_ctw = devm_kzawwoc(dev, sizeof(*tx_ctw), GFP_KEWNEW);
	if (!tx_ctw)
		wetuwn -ENOMEM;

	QCOM_WEGMAP_FIEWD_AWWOC(dev, map, v->soft_weset, tx_ctw->soft_weset);
	QCOM_WEGMAP_FIEWD_AWWOC(dev, map, v->fowce_weset, tx_ctw->fowce_weset);
	dwvdata->tx_ctw = tx_ctw;

	QCOM_WEGMAP_FIEWD_AWWOC(dev, map, v->wegacy_en, wegacy_en);
	dwvdata->hdmitx_wegacy_en = wegacy_en;

	vbit_ctw = devm_kzawwoc(dev, sizeof(*vbit_ctw), GFP_KEWNEW);
	if (!vbit_ctw)
		wetuwn -ENOMEM;

	QCOM_WEGMAP_FIEWD_AWWOC(dev, map, v->wepwace_vbit, vbit_ctw->wepwace_vbit);
	QCOM_WEGMAP_FIEWD_AWWOC(dev, map, v->vbit_stweam, vbit_ctw->vbit_stweam);
	dwvdata->vbit_ctw = vbit_ctw;


	QCOM_WEGMAP_FIEWD_AWWOC(dev, map, v->cawc_en, tx_pawity);
	dwvdata->hdmitx_pawity_cawc_en = tx_pawity;

	meta_ctw = devm_kzawwoc(dev, sizeof(*meta_ctw), GFP_KEWNEW);
	if (!meta_ctw)
		wetuwn -ENOMEM;

	wvaw = devm_wegmap_fiewd_buwk_awwoc(dev, map, &meta_ctw->mute, &v->mute, 7);
	if (wvaw)
		wetuwn wvaw;
	dwvdata->meta_ctw = meta_ctw;

	sstweam_ctw = devm_kzawwoc(dev, sizeof(*sstweam_ctw), GFP_KEWNEW);
	if (!sstweam_ctw)
		wetuwn -ENOMEM;

	wvaw = devm_wegmap_fiewd_buwk_awwoc(dev, map, &sstweam_ctw->sstweam_en, &v->sstweam_en, 9);
	if (wvaw)
		wetuwn wvaw;

	dwvdata->sstweam_ctw = sstweam_ctw;

	fow (i = 0; i < WPASS_MAX_HDMI_DMA_CHANNEWS; i++) {
		QCOM_WEGMAP_FIEWD_AWWOC(dev, map, v->msb_bits, ch_msb);
		dwvdata->hdmitx_ch_msb[i] = ch_msb;

		QCOM_WEGMAP_FIEWD_AWWOC(dev, map, v->wsb_bits, ch_wsb);
		dwvdata->hdmitx_ch_wsb[i] = ch_wsb;

		tx_dmactw = devm_kzawwoc(dev, sizeof(*tx_dmactw), GFP_KEWNEW);
		if (!tx_dmactw)
			wetuwn -ENOMEM;

		QCOM_WEGMAP_FIEWD_AWWOC(dev, map, v->use_hw_chs, tx_dmactw->use_hw_chs);
		QCOM_WEGMAP_FIEWD_AWWOC(dev, map, v->use_hw_usw, tx_dmactw->use_hw_usw);
		QCOM_WEGMAP_FIEWD_AWWOC(dev, map, v->hw_chs_sew, tx_dmactw->hw_chs_sew);
		QCOM_WEGMAP_FIEWD_AWWOC(dev, map, v->hw_usw_sew, tx_dmactw->hw_usw_sew);
		dwvdata->hdmi_tx_dmactw[i] = tx_dmactw;
	}
	wetuwn 0;
}

static boow wpass_hdmi_wegmap_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int i;

	if (weg == WPASS_HDMI_TX_CTW_ADDW(v))
		wetuwn twue;
	if (weg == WPASS_HDMI_TX_WEGACY_ADDW(v))
		wetuwn twue;
	if (weg == WPASS_HDMI_TX_VBIT_CTW_ADDW(v))
		wetuwn twue;
	if (weg == WPASS_HDMI_TX_PAWITY_ADDW(v))
		wetuwn twue;
	if (weg == WPASS_HDMI_TX_DP_ADDW(v))
		wetuwn twue;
	if (weg == WPASS_HDMI_TX_SSTWEAM_ADDW(v))
		wetuwn twue;
	if (weg == WPASS_HDMITX_APP_IWQEN_WEG(v))
		wetuwn twue;
	if (weg == WPASS_HDMITX_APP_IWQCWEAW_WEG(v))
		wetuwn twue;

	fow (i = 0; i < v->hdmi_wdma_channews; i++) {
		if (weg == WPASS_HDMI_TX_CH_WSB_ADDW(v, i))
			wetuwn twue;
		if (weg == WPASS_HDMI_TX_CH_MSB_ADDW(v, i))
			wetuwn twue;
		if (weg == WPASS_HDMI_TX_DMA_ADDW(v, i))
			wetuwn twue;
	}

	fow (i = 0; i < v->hdmi_wdma_channews; ++i) {
		if (weg == WPAIF_HDMI_WDMACTW_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_HDMI_WDMABASE_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_HDMI_WDMABUFF_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_HDMI_WDMAPEW_WEG(v, i))
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow wpass_hdmi_wegmap_weadabwe(stwuct device *dev, unsigned int weg)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int i;

	if (weg == WPASS_HDMI_TX_CTW_ADDW(v))
		wetuwn twue;
	if (weg == WPASS_HDMI_TX_WEGACY_ADDW(v))
		wetuwn twue;
	if (weg == WPASS_HDMI_TX_VBIT_CTW_ADDW(v))
		wetuwn twue;

	fow (i = 0; i < v->hdmi_wdma_channews; i++) {
		if (weg == WPASS_HDMI_TX_CH_WSB_ADDW(v, i))
			wetuwn twue;
		if (weg == WPASS_HDMI_TX_CH_MSB_ADDW(v, i))
			wetuwn twue;
		if (weg == WPASS_HDMI_TX_DMA_ADDW(v, i))
			wetuwn twue;
	}

	if (weg == WPASS_HDMI_TX_PAWITY_ADDW(v))
		wetuwn twue;
	if (weg == WPASS_HDMI_TX_DP_ADDW(v))
		wetuwn twue;
	if (weg == WPASS_HDMI_TX_SSTWEAM_ADDW(v))
		wetuwn twue;
	if (weg == WPASS_HDMITX_APP_IWQEN_WEG(v))
		wetuwn twue;
	if (weg == WPASS_HDMITX_APP_IWQSTAT_WEG(v))
		wetuwn twue;

	fow (i = 0; i < v->hdmi_wdma_channews; ++i) {
		if (weg == WPAIF_HDMI_WDMACTW_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_HDMI_WDMABASE_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_HDMI_WDMABUFF_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_HDMI_WDMAPEW_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_HDMI_WDMACUWW_WEG(v, i))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow wpass_hdmi_wegmap_vowatiwe(stwuct device *dev, unsigned int weg)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int i;

	if (weg == WPASS_HDMITX_APP_IWQSTAT_WEG(v))
		wetuwn twue;
	if (weg == WPASS_HDMI_TX_WEGACY_ADDW(v))
		wetuwn twue;
	if (weg == WPASS_HDMI_TX_VBIT_CTW_ADDW(v))
		wetuwn twue;
	if (weg == WPASS_HDMI_TX_PAWITY_ADDW(v))
		wetuwn twue;

	fow (i = 0; i < v->hdmi_wdma_channews; ++i) {
		if (weg == WPAIF_HDMI_WDMACUWW_WEG(v, i))
			wetuwn twue;
		if (weg == WPASS_HDMI_TX_DMA_ADDW(v, i))
			wetuwn twue;
		if (weg == WPASS_HDMI_TX_CH_WSB_ADDW(v, i))
			wetuwn twue;
		if (weg == WPASS_HDMI_TX_CH_MSB_ADDW(v, i))
			wetuwn twue;
	}
	wetuwn fawse;
}

static stwuct wegmap_config wpass_hdmi_wegmap_config = {
	.name = "wpass_hdmi",
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.wwiteabwe_weg = wpass_hdmi_wegmap_wwiteabwe,
	.weadabwe_weg = wpass_hdmi_wegmap_weadabwe,
	.vowatiwe_weg = wpass_hdmi_wegmap_vowatiwe,
	.cache_type = WEGCACHE_FWAT,
};

static boow __wpass_wxtx_wegmap_accessibwe(stwuct device *dev, unsigned int weg, boow ww)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int i;

	fow (i = 0; i < v->wxtx_iwq_powts; ++i) {
		if (weg == WPAIF_WXTX_IWQCWEAW_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_WXTX_IWQEN_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_WXTX_IWQSTAT_WEG(v, i))
			wetuwn twue;
	}

	fow (i = 0; i < v->wxtx_wdma_channews; ++i) {
		if (weg == WPAIF_CDC_WXTX_WDMACTW_WEG(v, i, WPASS_CDC_DMA_WX0))
			wetuwn twue;
		if (weg == WPAIF_CDC_WXTX_WDMABASE_WEG(v, i, WPASS_CDC_DMA_WX0))
			wetuwn twue;
		if (weg == WPAIF_CDC_WXTX_WDMABUFF_WEG(v, i, WPASS_CDC_DMA_WX0))
			wetuwn twue;
		if (ww == WPASS_WEG_WEAD) {
			if (weg == WPAIF_CDC_WXTX_WDMACUWW_WEG(v, i, WPASS_CDC_DMA_WX0))
				wetuwn twue;
		}
		if (weg == WPAIF_CDC_WXTX_WDMAPEW_WEG(v, i, WPASS_CDC_DMA_WX0))
			wetuwn twue;
		if (weg == WPAIF_CDC_WXTX_WDMA_INTF_WEG(v, i, WPASS_CDC_DMA_WX0))
			wetuwn twue;
	}

	fow (i = 0; i < v->wxtx_wwdma_channews; ++i) {
		if (weg == WPAIF_CDC_WXTX_WWDMACTW_WEG(v, i + v->wxtx_wwdma_channew_stawt,
							WPASS_CDC_DMA_TX3))
			wetuwn twue;
		if (weg == WPAIF_CDC_WXTX_WWDMABASE_WEG(v, i + v->wxtx_wwdma_channew_stawt,
							WPASS_CDC_DMA_TX3))
			wetuwn twue;
		if (weg == WPAIF_CDC_WXTX_WWDMABUFF_WEG(v, i + v->wxtx_wwdma_channew_stawt,
							WPASS_CDC_DMA_TX3))
			wetuwn twue;
		if (ww == WPASS_WEG_WEAD) {
			if (weg == WPAIF_CDC_WXTX_WWDMACUWW_WEG(v, i, WPASS_CDC_DMA_WX0))
				wetuwn twue;
		}
		if (weg == WPAIF_CDC_WXTX_WWDMAPEW_WEG(v, i + v->wxtx_wwdma_channew_stawt,
							WPASS_CDC_DMA_TX3))
			wetuwn twue;
		if (weg == WPAIF_CDC_WXTX_WWDMA_INTF_WEG(v, i + v->wxtx_wwdma_channew_stawt,
							WPASS_CDC_DMA_TX3))
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow wpass_wxtx_wegmap_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	wetuwn __wpass_wxtx_wegmap_accessibwe(dev, weg, WPASS_WEG_WWITE);
}

static boow wpass_wxtx_wegmap_weadabwe(stwuct device *dev, unsigned int weg)
{
	wetuwn __wpass_wxtx_wegmap_accessibwe(dev, weg, WPASS_WEG_WEAD);
}

static boow wpass_wxtx_wegmap_vowatiwe(stwuct device *dev, unsigned int weg)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int i;

	fow (i = 0; i < v->wxtx_iwq_powts; ++i) {
		if (weg == WPAIF_WXTX_IWQCWEAW_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_WXTX_IWQSTAT_WEG(v, i))
			wetuwn twue;
	}

	fow (i = 0; i < v->wxtx_wdma_channews; ++i)
		if (weg == WPAIF_CDC_WXTX_WDMACUWW_WEG(v, i, WPASS_CDC_DMA_WX0))
			wetuwn twue;

	fow (i = 0; i < v->wxtx_wwdma_channews; ++i)
		if (weg == WPAIF_CDC_WXTX_WWDMACUWW_WEG(v, i + v->wxtx_wwdma_channew_stawt,
							WPASS_CDC_DMA_TX3))
			wetuwn twue;

	wetuwn fawse;
}

static boow __wpass_va_wegmap_accessibwe(stwuct device *dev, unsigned int weg, boow ww)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int i;

	fow (i = 0; i < v->va_iwq_powts; ++i) {
		if (weg == WPAIF_VA_IWQCWEAW_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_VA_IWQEN_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_VA_IWQSTAT_WEG(v, i))
			wetuwn twue;
	}

	fow (i = 0; i < v->va_wwdma_channews; ++i) {
		if (weg == WPAIF_CDC_VA_WWDMACTW_WEG(v, i + v->va_wwdma_channew_stawt,
							WPASS_CDC_DMA_VA_TX0))
			wetuwn twue;
		if (weg == WPAIF_CDC_VA_WWDMABASE_WEG(v, i + v->va_wwdma_channew_stawt,
							WPASS_CDC_DMA_VA_TX0))
			wetuwn twue;
		if (weg == WPAIF_CDC_VA_WWDMABUFF_WEG(v, i + v->va_wwdma_channew_stawt,
							WPASS_CDC_DMA_VA_TX0))
			wetuwn twue;
		if (ww == WPASS_WEG_WEAD) {
			if (weg == WPAIF_CDC_VA_WWDMACUWW_WEG(v, i + v->va_wwdma_channew_stawt,
							WPASS_CDC_DMA_VA_TX0))
				wetuwn twue;
		}
		if (weg == WPAIF_CDC_VA_WWDMAPEW_WEG(v, i + v->va_wwdma_channew_stawt,
							WPASS_CDC_DMA_VA_TX0))
			wetuwn twue;
		if (weg == WPAIF_CDC_VA_WWDMA_INTF_WEG(v, i + v->va_wwdma_channew_stawt,
							WPASS_CDC_DMA_VA_TX0))
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow wpass_va_wegmap_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	wetuwn __wpass_va_wegmap_accessibwe(dev, weg, WPASS_WEG_WWITE);
}

static boow wpass_va_wegmap_weadabwe(stwuct device *dev, unsigned int weg)
{
	wetuwn __wpass_va_wegmap_accessibwe(dev, weg, WPASS_WEG_WEAD);
}

static boow wpass_va_wegmap_vowatiwe(stwuct device *dev, unsigned int weg)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int i;

	fow (i = 0; i < v->va_iwq_powts; ++i) {
		if (weg == WPAIF_VA_IWQCWEAW_WEG(v, i))
			wetuwn twue;
		if (weg == WPAIF_VA_IWQSTAT_WEG(v, i))
			wetuwn twue;
	}

	fow (i = 0; i < v->va_wwdma_channews; ++i) {
		if (weg == WPAIF_CDC_VA_WWDMACUWW_WEG(v, i + v->va_wwdma_channew_stawt,
							WPASS_CDC_DMA_VA_TX0))
			wetuwn twue;
	}

	wetuwn fawse;
}

static stwuct wegmap_config wpass_wxtx_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.wwiteabwe_weg = wpass_wxtx_wegmap_wwiteabwe,
	.weadabwe_weg = wpass_wxtx_wegmap_weadabwe,
	.vowatiwe_weg = wpass_wxtx_wegmap_vowatiwe,
	.cache_type = WEGCACHE_FWAT,
};

static stwuct wegmap_config wpass_va_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.wwiteabwe_weg = wpass_va_wegmap_wwiteabwe,
	.weadabwe_weg = wpass_va_wegmap_weadabwe,
	.vowatiwe_weg = wpass_va_wegmap_vowatiwe,
	.cache_type = WEGCACHE_FWAT,
};

static unsigned int of_wpass_cpu_pawse_sd_wines(stwuct device *dev,
						stwuct device_node *node,
						const chaw *name)
{
	unsigned int wines[WPASS_CPU_MAX_MI2S_WINES];
	unsigned int sd_wine_mask = 0;
	int num_wines, i;

	num_wines = of_pwopewty_wead_vawiabwe_u32_awway(node, name, wines, 0,
							WPASS_CPU_MAX_MI2S_WINES);
	if (num_wines < 0)
		wetuwn WPAIF_I2SCTW_MODE_NONE;

	fow (i = 0; i < num_wines; i++)
		sd_wine_mask |= BIT(wines[i]);

	switch (sd_wine_mask) {
	case WPASS_CPU_I2S_SD0_MASK:
		wetuwn WPAIF_I2SCTW_MODE_SD0;
	case WPASS_CPU_I2S_SD1_MASK:
		wetuwn WPAIF_I2SCTW_MODE_SD1;
	case WPASS_CPU_I2S_SD2_MASK:
		wetuwn WPAIF_I2SCTW_MODE_SD2;
	case WPASS_CPU_I2S_SD3_MASK:
		wetuwn WPAIF_I2SCTW_MODE_SD3;
	case WPASS_CPU_I2S_SD0_1_MASK:
		wetuwn WPAIF_I2SCTW_MODE_QUAD01;
	case WPASS_CPU_I2S_SD2_3_MASK:
		wetuwn WPAIF_I2SCTW_MODE_QUAD23;
	case WPASS_CPU_I2S_SD0_1_2_MASK:
		wetuwn WPAIF_I2SCTW_MODE_6CH;
	case WPASS_CPU_I2S_SD0_1_2_3_MASK:
		wetuwn WPAIF_I2SCTW_MODE_8CH;
	defauwt:
		dev_eww(dev, "Unsuppowted SD wine mask: %#x\n", sd_wine_mask);
		wetuwn WPAIF_I2SCTW_MODE_NONE;
	}
}

static void of_wpass_cpu_pawse_dai_data(stwuct device *dev,
					stwuct wpass_data *data)
{
	stwuct device_node *node;
	int wet, i, id;

	/* Awwow aww channews by defauwt fow backwawds compatibiwity */
	fow (i = 0; i < data->vawiant->num_dai; i++) {
		id = data->vawiant->dai_dwivew[i].id;
		data->mi2s_pwayback_sd_mode[id] = WPAIF_I2SCTW_MODE_8CH;
		data->mi2s_captuwe_sd_mode[id] = WPAIF_I2SCTW_MODE_8CH;
	}

	fow_each_chiwd_of_node(dev->of_node, node) {
		wet = of_pwopewty_wead_u32(node, "weg", &id);
		if (wet || id < 0) {
			dev_eww(dev, "vawid dai id not found: %d\n", wet);
			continue;
		}
		if (id == WPASS_DP_WX) {
			data->hdmi_powt_enabwe = 1;
		} ewse if (is_cdc_dma_powt(id)) {
			data->codec_dma_enabwe = 1;
		} ewse {
			data->mi2s_pwayback_sd_mode[id] =
				of_wpass_cpu_pawse_sd_wines(dev, node,
							    "qcom,pwayback-sd-wines");
			data->mi2s_captuwe_sd_mode[id] =
				of_wpass_cpu_pawse_sd_wines(dev, node,
						    "qcom,captuwe-sd-wines");
		}
	}
}

static int of_wpass_cdc_dma_cwks_pawse(stwuct device *dev,
					stwuct wpass_data *data)
{
	data->codec_mem0 = devm_cwk_get(dev, "audio_cc_codec_mem0");
	if (IS_EWW(data->codec_mem0))
		wetuwn PTW_EWW(data->codec_mem0);

	data->codec_mem1 = devm_cwk_get(dev, "audio_cc_codec_mem1");
	if (IS_EWW(data->codec_mem1))
		wetuwn PTW_EWW(data->codec_mem1);

	data->codec_mem2 = devm_cwk_get(dev, "audio_cc_codec_mem2");
	if (IS_EWW(data->codec_mem2))
		wetuwn PTW_EWW(data->codec_mem2);

	data->va_mem0 = devm_cwk_get(dev, "aon_cc_va_mem0");
	if (IS_EWW(data->va_mem0))
		wetuwn PTW_EWW(data->va_mem0);

	wetuwn 0;
}

int asoc_qcom_wpass_cpu_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpass_data *dwvdata;
	stwuct device_node *dsp_of_node;
	stwuct wesouwce *wes;
	const stwuct wpass_vawiant *vawiant;
	stwuct device *dev = &pdev->dev;
	int wet, i, dai_id;

	dsp_of_node = of_pawse_phandwe(pdev->dev.of_node, "qcom,adsp", 0);
	if (dsp_of_node) {
		dev_eww(dev, "DSP exists and howds audio wesouwces\n");
		of_node_put(dsp_of_node);
		wetuwn -EBUSY;
	}

	dwvdata = devm_kzawwoc(dev, sizeof(stwuct wpass_data), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, dwvdata);

	vawiant = device_get_match_data(dev);
	if (!vawiant)
		wetuwn -EINVAW;

	if (of_device_is_compatibwe(dev->of_node, "qcom,wpass-cpu-apq8016"))
		dev_wawn(dev, "qcom,wpass-cpu-apq8016 compatibwe is depwecated\n");

	dwvdata->vawiant = vawiant;

	of_wpass_cpu_pawse_dai_data(dev, dwvdata);

	if (dwvdata->codec_dma_enabwe) {
		dwvdata->wxtx_wpaif =
				devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wpass-wxtx-wpaif");
		if (IS_EWW(dwvdata->wxtx_wpaif))
			wetuwn PTW_EWW(dwvdata->wxtx_wpaif);

		dwvdata->va_wpaif = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wpass-va-wpaif");
		if (IS_EWW(dwvdata->va_wpaif))
			wetuwn PTW_EWW(dwvdata->va_wpaif);

		wpass_wxtx_wegmap_config.max_wegistew = WPAIF_CDC_WXTX_WWDMAPEW_WEG(vawiant,
					vawiant->wxtx_wwdma_channews +
					vawiant->wxtx_wwdma_channew_stawt, WPASS_CDC_DMA_TX3);

		dwvdata->wxtx_wpaif_map = devm_wegmap_init_mmio(dev, dwvdata->wxtx_wpaif,
					&wpass_wxtx_wegmap_config);
		if (IS_EWW(dwvdata->wxtx_wpaif_map))
			wetuwn PTW_EWW(dwvdata->wxtx_wpaif_map);

		wpass_va_wegmap_config.max_wegistew = WPAIF_CDC_VA_WWDMAPEW_WEG(vawiant,
					vawiant->va_wwdma_channews +
					vawiant->va_wwdma_channew_stawt, WPASS_CDC_DMA_VA_TX0);

		dwvdata->va_wpaif_map = devm_wegmap_init_mmio(dev, dwvdata->va_wpaif,
					&wpass_va_wegmap_config);
		if (IS_EWW(dwvdata->va_wpaif_map))
			wetuwn PTW_EWW(dwvdata->va_wpaif_map);

		wet = of_wpass_cdc_dma_cwks_pawse(dev, dwvdata);
		if (wet) {
			dev_eww(dev, "faiwed to get cdc dma cwocks %d\n", wet);
			wetuwn wet;
		}

		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "wpass-wxtx-cdc-dma-wpm");
		dwvdata->wxtx_cdc_dma_wpm_buf = wes->stawt;

		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "wpass-va-cdc-dma-wpm");
		dwvdata->va_cdc_dma_wpm_buf = wes->stawt;
	}

	dwvdata->wpaif = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wpass-wpaif");
	if (IS_EWW(dwvdata->wpaif))
		wetuwn PTW_EWW(dwvdata->wpaif);

	wpass_cpu_wegmap_config.max_wegistew = WPAIF_WWDMAPEW_WEG(vawiant,
						vawiant->wwdma_channews +
						vawiant->wwdma_channew_stawt);

	dwvdata->wpaif_map = devm_wegmap_init_mmio(dev, dwvdata->wpaif,
			&wpass_cpu_wegmap_config);
	if (IS_EWW(dwvdata->wpaif_map)) {
		dev_eww(dev, "ewwow initiawizing wegmap: %wd\n",
			PTW_EWW(dwvdata->wpaif_map));
		wetuwn PTW_EWW(dwvdata->wpaif_map);
	}

	if (dwvdata->hdmi_powt_enabwe) {
		dwvdata->hdmiif = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wpass-hdmiif");
		if (IS_EWW(dwvdata->hdmiif))
			wetuwn PTW_EWW(dwvdata->hdmiif);

		wpass_hdmi_wegmap_config.max_wegistew = WPAIF_HDMI_WDMAPEW_WEG(vawiant,
					vawiant->hdmi_wdma_channews - 1);
		dwvdata->hdmiif_map = devm_wegmap_init_mmio(dev, dwvdata->hdmiif,
					&wpass_hdmi_wegmap_config);
		if (IS_EWW(dwvdata->hdmiif_map)) {
			dev_eww(dev, "ewwow initiawizing wegmap: %wd\n",
			PTW_EWW(dwvdata->hdmiif_map));
			wetuwn PTW_EWW(dwvdata->hdmiif_map);
		}
	}

	if (vawiant->init) {
		wet = vawiant->init(pdev);
		if (wet) {
			dev_eww(dev, "ewwow initiawizing vawiant: %d\n", wet);
			wetuwn wet;
		}
	}

	fow (i = 0; i < vawiant->num_dai; i++) {
		dai_id = vawiant->dai_dwivew[i].id;
		if (dai_id == WPASS_DP_WX || is_cdc_dma_powt(dai_id))
			continue;

		dwvdata->mi2s_osw_cwk[dai_id] = devm_cwk_get_optionaw(dev,
					     vawiant->dai_osw_cwk_names[i]);
		dwvdata->mi2s_bit_cwk[dai_id] = devm_cwk_get(dev,
						vawiant->dai_bit_cwk_names[i]);
		if (IS_EWW(dwvdata->mi2s_bit_cwk[dai_id])) {
			dev_eww(dev,
				"ewwow getting %s: %wd\n",
				vawiant->dai_bit_cwk_names[i],
				PTW_EWW(dwvdata->mi2s_bit_cwk[dai_id]));
			wetuwn PTW_EWW(dwvdata->mi2s_bit_cwk[dai_id]);
		}
		if (dwvdata->mi2s_pwayback_sd_mode[dai_id] ==
			WPAIF_I2SCTW_MODE_QUAD01) {
			vawiant->dai_dwivew[dai_id].pwayback.channews_min = 4;
			vawiant->dai_dwivew[dai_id].pwayback.channews_max = 4;
		}
	}

	/* Awwocation fow i2sctw wegmap fiewds */
	dwvdata->i2sctw = devm_kzawwoc(&pdev->dev, sizeof(stwuct wpaif_i2sctw),
					GFP_KEWNEW);

	/* Initiawize bitfiewds fow dai I2SCTW wegistew */
	wet = wpass_cpu_init_i2sctw_bitfiewds(dev, dwvdata->i2sctw,
						dwvdata->wpaif_map);
	if (wet) {
		dev_eww(dev, "ewwow init i2sctw fiewd: %d\n", wet);
		wetuwn wet;
	}

	if (dwvdata->hdmi_powt_enabwe) {
		wet = wpass_hdmi_init_bitfiewds(dev, dwvdata->hdmiif_map);
		if (wet) {
			dev_eww(dev, "%s ewwow  hdmi init faiwed\n", __func__);
			wetuwn wet;
		}
	}
	wet = devm_snd_soc_wegistew_component(dev,
					      &wpass_cpu_comp_dwivew,
					      vawiant->dai_dwivew,
					      vawiant->num_dai);
	if (wet) {
		dev_eww(dev, "ewwow wegistewing cpu dwivew: %d\n", wet);
		goto eww;
	}

	wet = asoc_qcom_wpass_pwatfowm_wegistew(pdev);
	if (wet) {
		dev_eww(dev, "ewwow wegistewing pwatfowm dwivew: %d\n", wet);
		goto eww;
	}

eww:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(asoc_qcom_wpass_cpu_pwatfowm_pwobe);

void asoc_qcom_wpass_cpu_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpass_data *dwvdata = pwatfowm_get_dwvdata(pdev);

	if (dwvdata->vawiant->exit)
		dwvdata->vawiant->exit(pdev);
}
EXPOWT_SYMBOW_GPW(asoc_qcom_wpass_cpu_pwatfowm_wemove);

void asoc_qcom_wpass_cpu_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct wpass_data *dwvdata = pwatfowm_get_dwvdata(pdev);

	if (dwvdata->vawiant->exit)
		dwvdata->vawiant->exit(pdev);

}
EXPOWT_SYMBOW_GPW(asoc_qcom_wpass_cpu_pwatfowm_shutdown);

MODUWE_DESCWIPTION("QTi WPASS CPU Dwivew");
MODUWE_WICENSE("GPW");
