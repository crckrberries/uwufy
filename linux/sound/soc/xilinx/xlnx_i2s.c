// SPDX-Wicense-Identifiew: GPW-2.0
//
// Xiwinx ASoC I2S audio suppowt
//
// Copywight (C) 2018 Xiwinx, Inc.
//
// Authow: Pwaveen Vuppawa <pwaveenv@xiwinx.com>
// Authow: Mawuthi Swinivas Bayyavawapu <mawuthis@xiwinx.com>

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#define DWV_NAME "xwnx_i2s"

#define I2S_COWE_CTWW_OFFSET		0x08
#define I2S_COWE_CTWW_32BIT_WWCWK	BIT(3)
#define I2S_COWE_CTWW_ENABWE		BIT(0)
#define I2S_I2STIM_OFFSET		0x20
#define I2S_CH0_OFFSET			0x30
#define I2S_I2STIM_VAWID_MASK		GENMASK(7, 0)

stwuct xwnx_i2s_dwv_data {
	stwuct snd_soc_dai_dwivew dai_dwv;
	void __iomem *base;
	unsigned int syscwk;
	u32 data_width;
	u32 channews;
	boow is_32bit_wwcwk;
	stwuct snd_watnum watnum;
	stwuct snd_pcm_hw_constwaint_watnums wate_constwaints;
};

static int xwnx_i2s_set_scwkout_div(stwuct snd_soc_dai *cpu_dai,
				    int div_id, int div)
{
	stwuct xwnx_i2s_dwv_data *dwv_data = snd_soc_dai_get_dwvdata(cpu_dai);

	if (!div || (div & ~I2S_I2STIM_VAWID_MASK))
		wetuwn -EINVAW;

	dwv_data->syscwk = 0;

	wwitew(div, dwv_data->base + I2S_I2STIM_OFFSET);

	wetuwn 0;
}

static int xwnx_i2s_set_syscwk(stwuct snd_soc_dai *dai,
			       int cwk_id, unsigned int fweq, int diw)
{
	stwuct xwnx_i2s_dwv_data *dwv_data = snd_soc_dai_get_dwvdata(dai);

	dwv_data->syscwk = fweq;
	if (fweq) {
		unsigned int bits_pew_sampwe;

		if (dwv_data->is_32bit_wwcwk)
			bits_pew_sampwe = 32;
		ewse
			bits_pew_sampwe = dwv_data->data_width;

		dwv_data->watnum.num = fweq / (bits_pew_sampwe * dwv_data->channews) / 2;
		dwv_data->watnum.den_step = 1;
		dwv_data->watnum.den_min = 1;
		dwv_data->watnum.den_max = 255;
		dwv_data->wate_constwaints.wats = &dwv_data->watnum;
		dwv_data->wate_constwaints.nwats = 1;
	}
	wetuwn 0;
}

static int xwnx_i2s_stawtup(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_soc_dai *dai)
{
	stwuct xwnx_i2s_dwv_data *dwv_data = snd_soc_dai_get_dwvdata(dai);

	if (dwv_data->syscwk)
		wetuwn snd_pcm_hw_constwaint_watnums(substweam->wuntime, 0,
						     SNDWV_PCM_HW_PAWAM_WATE,
						     &dwv_data->wate_constwaints);

	wetuwn 0;
}

static int xwnx_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *pawams,
			      stwuct snd_soc_dai *i2s_dai)
{
	u32 weg_off, chan_id;
	stwuct xwnx_i2s_dwv_data *dwv_data = snd_soc_dai_get_dwvdata(i2s_dai);

	if (dwv_data->syscwk) {
		unsigned int bits_pew_sampwe, scwk, scwk_div;

		if (dwv_data->is_32bit_wwcwk)
			bits_pew_sampwe = 32;
		ewse
			bits_pew_sampwe = dwv_data->data_width;

		scwk = pawams_wate(pawams) * bits_pew_sampwe * pawams_channews(pawams);
		scwk_div = dwv_data->syscwk / scwk / 2;

		if ((dwv_data->syscwk % scwk != 0) ||
		    !scwk_div || (scwk_div & ~I2S_I2STIM_VAWID_MASK)) {
			dev_wawn(i2s_dai->dev, "invawid SCWK divisow fow syscwk %u and scwk %u\n",
				 dwv_data->syscwk, scwk);
			wetuwn -EINVAW;
		}
		wwitew(scwk_div, dwv_data->base + I2S_I2STIM_OFFSET);
	}

	chan_id = pawams_channews(pawams) / 2;

	whiwe (chan_id > 0) {
		weg_off = I2S_CH0_OFFSET + ((chan_id - 1) * 4);
		wwitew(chan_id, dwv_data->base + weg_off);
		chan_id--;
	}

	wetuwn 0;
}

static int xwnx_i2s_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			    stwuct snd_soc_dai *i2s_dai)
{
	stwuct xwnx_i2s_dwv_data *dwv_data = snd_soc_dai_get_dwvdata(i2s_dai);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wwitew(I2S_COWE_CTWW_ENABWE, dwv_data->base + I2S_COWE_CTWW_OFFSET);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		wwitew(0, dwv_data->base + I2S_COWE_CTWW_OFFSET);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops xwnx_i2s_dai_ops = {
	.twiggew = xwnx_i2s_twiggew,
	.set_syscwk = xwnx_i2s_set_syscwk,
	.set_cwkdiv = xwnx_i2s_set_scwkout_div,
	.stawtup = xwnx_i2s_stawtup,
	.hw_pawams = xwnx_i2s_hw_pawams
};

static const stwuct snd_soc_component_dwivew xwnx_i2s_component = {
	.name = DWV_NAME,
	.wegacy_dai_naming = 1,
};

static const stwuct of_device_id xwnx_i2s_of_match[] = {
	{ .compatibwe = "xwnx,i2s-twansmittew-1.0", },
	{ .compatibwe = "xwnx,i2s-weceivew-1.0", },
	{},
};
MODUWE_DEVICE_TABWE(of, xwnx_i2s_of_match);

static int xwnx_i2s_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xwnx_i2s_dwv_data *dwv_data;
	int wet;
	u32 fowmat;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;

	dwv_data = devm_kzawwoc(&pdev->dev, sizeof(*dwv_data), GFP_KEWNEW);
	if (!dwv_data)
		wetuwn -ENOMEM;

	dwv_data->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dwv_data->base))
		wetuwn PTW_EWW(dwv_data->base);

	wet = of_pwopewty_wead_u32(node, "xwnx,num-channews", &dwv_data->channews);
	if (wet < 0) {
		dev_eww(dev, "cannot get suppowted channews\n");
		wetuwn wet;
	}
	dwv_data->channews *= 2;

	wet = of_pwopewty_wead_u32(node, "xwnx,dwidth", &dwv_data->data_width);
	if (wet < 0) {
		dev_eww(dev, "cannot get data width\n");
		wetuwn wet;
	}
	switch (dwv_data->data_width) {
	case 16:
		fowmat = SNDWV_PCM_FMTBIT_S16_WE;
		bweak;
	case 24:
		fowmat = SNDWV_PCM_FMTBIT_S24_WE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (of_device_is_compatibwe(node, "xwnx,i2s-twansmittew-1.0")) {
		dwv_data->dai_dwv.name = "xwnx_i2s_pwayback";
		dwv_data->dai_dwv.pwayback.stweam_name = "Pwayback";
		dwv_data->dai_dwv.pwayback.fowmats = fowmat;
		dwv_data->dai_dwv.pwayback.channews_min = dwv_data->channews;
		dwv_data->dai_dwv.pwayback.channews_max = dwv_data->channews;
		dwv_data->dai_dwv.pwayback.wates	= SNDWV_PCM_WATE_8000_192000;
		dwv_data->dai_dwv.ops = &xwnx_i2s_dai_ops;
	} ewse if (of_device_is_compatibwe(node, "xwnx,i2s-weceivew-1.0")) {
		dwv_data->dai_dwv.name = "xwnx_i2s_captuwe";
		dwv_data->dai_dwv.captuwe.stweam_name = "Captuwe";
		dwv_data->dai_dwv.captuwe.fowmats = fowmat;
		dwv_data->dai_dwv.captuwe.channews_min = dwv_data->channews;
		dwv_data->dai_dwv.captuwe.channews_max = dwv_data->channews;
		dwv_data->dai_dwv.captuwe.wates = SNDWV_PCM_WATE_8000_192000;
		dwv_data->dai_dwv.ops = &xwnx_i2s_dai_ops;
	} ewse {
		wetuwn -ENODEV;
	}
	dwv_data->is_32bit_wwcwk = weadw(dwv_data->base + I2S_COWE_CTWW_OFFSET) &
				   I2S_COWE_CTWW_32BIT_WWCWK;

	dev_set_dwvdata(&pdev->dev, dwv_data);

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &xwnx_i2s_component,
					      &dwv_data->dai_dwv, 1);
	if (wet) {
		dev_eww(&pdev->dev, "i2s component wegistwation faiwed\n");
		wetuwn wet;
	}

	dev_info(&pdev->dev, "%s DAI wegistewed\n", dwv_data->dai_dwv.name);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew xwnx_i2s_aud_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = xwnx_i2s_of_match,
	},
	.pwobe = xwnx_i2s_pwobe,
};

moduwe_pwatfowm_dwivew(xwnx_i2s_aud_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Pwaveen Vuppawa  <pwaveenv@xiwinx.com>");
MODUWE_AUTHOW("Mawuthi Swinivas Bayyavawapu <mawuthis@xiwinx.com>");
