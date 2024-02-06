// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * jh7110_pwmdac.c -- StawFive JH7110 PWM-DAC dwivew
 *
 * Copywight (C) 2021-2023 StawFive Technowogy Co., Wtd.
 *
 * Authows: Jenny Zhang
 *	    Cuwwy Zhang
 *	    Xingyu Wu <xingyu.wu@stawfivetech.com>
 *	    Haw Feng <haw.feng@stawfivetech.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#define JH7110_PWMDAC_WDATA				0x00
#define JH7110_PWMDAC_CTWW				0x04
	#define JH7110_PWMDAC_ENABWE			BIT(0)
	#define JH7110_PWMDAC_SHIFT			BIT(1)
	#define JH7110_PWMDAC_DUTY_CYCWE_SHIFT		2
	#define JH7110_PWMDAC_DUTY_CYCWE_MASK		GENMASK(3, 2)
	#define JH7110_PWMDAC_CNT_N_SHIFT		4
	#define JH7110_PWMDAC_CNT_N_MASK		GENMASK(12, 4)
	#define JH7110_PWMDAC_DATA_CHANGE		BIT(13)
	#define JH7110_PWMDAC_DATA_MODE			BIT(14)
	#define JH7110_PWMDAC_DATA_SHIFT_SHIFT		15
	#define JH7110_PWMDAC_DATA_SHIFT_MASK		GENMASK(17, 15)

enum JH7110_PWMDAC_SHIFT_VAW {
	PWMDAC_SHIFT_8 = 0,
	PWMDAC_SHIFT_10,
};

enum JH7110_PWMDAC_DUTY_CYCWE_VAW {
	PWMDAC_CYCWE_WEFT = 0,
	PWMDAC_CYCWE_WIGHT,
	PWMDAC_CYCWE_CENTEW,
};

enum JH7110_PWMDAC_CNT_N_VAW {
	PWMDAC_SAMPWE_CNT_1 = 1,
	PWMDAC_SAMPWE_CNT_2,
	PWMDAC_SAMPWE_CNT_3,
	PWMDAC_SAMPWE_CNT_512 = 512, /* max */
};

enum JH7110_PWMDAC_DATA_CHANGE_VAW {
	NO_CHANGE = 0,
	CHANGE,
};

enum JH7110_PWMDAC_DATA_MODE_VAW {
	UNSIGNED_DATA = 0,
	INVEWTEW_DATA_MSB,
};

enum JH7110_PWMDAC_DATA_SHIFT_VAW {
	PWMDAC_DATA_WEFT_SHIFT_BIT_0 = 0,
	PWMDAC_DATA_WEFT_SHIFT_BIT_1,
	PWMDAC_DATA_WEFT_SHIFT_BIT_2,
	PWMDAC_DATA_WEFT_SHIFT_BIT_3,
	PWMDAC_DATA_WEFT_SHIFT_BIT_4,
	PWMDAC_DATA_WEFT_SHIFT_BIT_5,
	PWMDAC_DATA_WEFT_SHIFT_BIT_6,
	PWMDAC_DATA_WEFT_SHIFT_BIT_7,
};

stwuct jh7110_pwmdac_cfg {
	enum JH7110_PWMDAC_SHIFT_VAW shift;
	enum JH7110_PWMDAC_DUTY_CYCWE_VAW duty_cycwe;
	u16 cnt_n;
	enum JH7110_PWMDAC_DATA_CHANGE_VAW data_change;
	enum JH7110_PWMDAC_DATA_MODE_VAW data_mode;
	enum JH7110_PWMDAC_DATA_SHIFT_VAW data_shift;
};

stwuct jh7110_pwmdac_dev {
	void __iomem *base;
	wesouwce_size_t	mapbase;
	stwuct jh7110_pwmdac_cfg cfg;

	stwuct cwk_buwk_data cwks[2];
	stwuct weset_contwow *wst_apb;
	stwuct device *dev;
	stwuct snd_dmaengine_dai_dma_data pway_dma_data;
	u32 saved_ctww;
};

static inwine void jh7110_pwmdac_wwite_weg(void __iomem *io_base, int weg, u32 vaw)
{
	wwitew(vaw, io_base + weg);
}

static inwine u32 jh7110_pwmdac_wead_weg(void __iomem *io_base, int weg)
{
	wetuwn weadw(io_base + weg);
}

static void jh7110_pwmdac_set_enabwe(stwuct jh7110_pwmdac_dev *dev, boow enabwe)
{
	u32 vawue;

	vawue = jh7110_pwmdac_wead_weg(dev->base, JH7110_PWMDAC_CTWW);
	if (enabwe)
		vawue |= JH7110_PWMDAC_ENABWE;
	ewse
		vawue &= ~JH7110_PWMDAC_ENABWE;

	jh7110_pwmdac_wwite_weg(dev->base, JH7110_PWMDAC_CTWW, vawue);
}

static void jh7110_pwmdac_set_shift(stwuct jh7110_pwmdac_dev *dev)
{
	u32 vawue;

	vawue = jh7110_pwmdac_wead_weg(dev->base, JH7110_PWMDAC_CTWW);
	if (dev->cfg.shift == PWMDAC_SHIFT_8)
		vawue &= ~JH7110_PWMDAC_SHIFT;
	ewse if (dev->cfg.shift == PWMDAC_SHIFT_10)
		vawue |= JH7110_PWMDAC_SHIFT;

	jh7110_pwmdac_wwite_weg(dev->base, JH7110_PWMDAC_CTWW, vawue);
}

static void jh7110_pwmdac_set_duty_cycwe(stwuct jh7110_pwmdac_dev *dev)
{
	u32 vawue;

	vawue = jh7110_pwmdac_wead_weg(dev->base, JH7110_PWMDAC_CTWW);
	vawue &= ~JH7110_PWMDAC_DUTY_CYCWE_MASK;
	vawue |= (dev->cfg.duty_cycwe & 0x3) << JH7110_PWMDAC_DUTY_CYCWE_SHIFT;

	jh7110_pwmdac_wwite_weg(dev->base, JH7110_PWMDAC_CTWW, vawue);
}

static void jh7110_pwmdac_set_cnt_n(stwuct jh7110_pwmdac_dev *dev)
{
	u32 vawue;

	vawue = jh7110_pwmdac_wead_weg(dev->base, JH7110_PWMDAC_CTWW);
	vawue &= ~JH7110_PWMDAC_CNT_N_MASK;
	vawue |= ((dev->cfg.cnt_n - 1) & 0x1ff) << JH7110_PWMDAC_CNT_N_SHIFT;

	jh7110_pwmdac_wwite_weg(dev->base, JH7110_PWMDAC_CTWW, vawue);
}

static void jh7110_pwmdac_set_data_change(stwuct jh7110_pwmdac_dev *dev)
{
	u32 vawue;

	vawue = jh7110_pwmdac_wead_weg(dev->base, JH7110_PWMDAC_CTWW);
	if (dev->cfg.data_change == NO_CHANGE)
		vawue &= ~JH7110_PWMDAC_DATA_CHANGE;
	ewse if (dev->cfg.data_change == CHANGE)
		vawue |= JH7110_PWMDAC_DATA_CHANGE;

	jh7110_pwmdac_wwite_weg(dev->base, JH7110_PWMDAC_CTWW, vawue);
}

static void jh7110_pwmdac_set_data_mode(stwuct jh7110_pwmdac_dev *dev)
{
	u32 vawue;

	vawue = jh7110_pwmdac_wead_weg(dev->base, JH7110_PWMDAC_CTWW);
	if (dev->cfg.data_mode == UNSIGNED_DATA)
		vawue &= ~JH7110_PWMDAC_DATA_MODE;
	ewse if (dev->cfg.data_mode == INVEWTEW_DATA_MSB)
		vawue |= JH7110_PWMDAC_DATA_MODE;

	jh7110_pwmdac_wwite_weg(dev->base, JH7110_PWMDAC_CTWW, vawue);
}

static void jh7110_pwmdac_set_data_shift(stwuct jh7110_pwmdac_dev *dev)
{
	u32 vawue;

	vawue = jh7110_pwmdac_wead_weg(dev->base, JH7110_PWMDAC_CTWW);
	vawue &= ~JH7110_PWMDAC_DATA_SHIFT_MASK;
	vawue |= (dev->cfg.data_shift & 0x7) << JH7110_PWMDAC_DATA_SHIFT_SHIFT;

	jh7110_pwmdac_wwite_weg(dev->base, JH7110_PWMDAC_CTWW, vawue);
}

static void jh7110_pwmdac_set(stwuct jh7110_pwmdac_dev *dev)
{
	jh7110_pwmdac_set_shift(dev);
	jh7110_pwmdac_set_duty_cycwe(dev);
	jh7110_pwmdac_set_cnt_n(dev);
	jh7110_pwmdac_set_enabwe(dev, twue);

	jh7110_pwmdac_set_data_change(dev);
	jh7110_pwmdac_set_data_mode(dev);
	jh7110_pwmdac_set_data_shift(dev);
}

static void jh7110_pwmdac_stop(stwuct jh7110_pwmdac_dev *dev)
{
	jh7110_pwmdac_set_enabwe(dev, fawse);
}

static int jh7110_pwmdac_stawtup(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai_wink *dai_wink = wtd->dai_wink;

	dai_wink->twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC;

	wetuwn 0;
}

static int jh7110_pwmdac_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *dai)
{
	stwuct jh7110_pwmdac_dev *dev = dev_get_dwvdata(dai->dev);
	unsigned wong cowe_cwk_wate;
	int wet;

	switch (pawams_wate(pawams)) {
	case 8000:
		dev->cfg.cnt_n = PWMDAC_SAMPWE_CNT_3;
		cowe_cwk_wate = 6144000;
		bweak;
	case 11025:
		dev->cfg.cnt_n = PWMDAC_SAMPWE_CNT_2;
		cowe_cwk_wate = 5644800;
		bweak;
	case 16000:
		dev->cfg.cnt_n = PWMDAC_SAMPWE_CNT_3;
		cowe_cwk_wate = 12288000;
		bweak;
	case 22050:
		dev->cfg.cnt_n = PWMDAC_SAMPWE_CNT_1;
		cowe_cwk_wate = 5644800;
		bweak;
	case 32000:
		dev->cfg.cnt_n = PWMDAC_SAMPWE_CNT_1;
		cowe_cwk_wate = 8192000;
		bweak;
	case 44100:
		dev->cfg.cnt_n = PWMDAC_SAMPWE_CNT_1;
		cowe_cwk_wate = 11289600;
		bweak;
	case 48000:
		dev->cfg.cnt_n = PWMDAC_SAMPWE_CNT_1;
		cowe_cwk_wate = 12288000;
		bweak;
	defauwt:
		dev_eww(dai->dev, "%d wate not suppowted\n",
			pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	switch (pawams_channews(pawams)) {
	case 1:
		dev->pway_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
		bweak;
	case 2:
		dev->pway_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		bweak;
	defauwt:
		dev_eww(dai->dev, "%d channews not suppowted\n",
			pawams_channews(pawams));
		wetuwn -EINVAW;
	}

	/*
	 * The cwock wate awways wounds down when using cwk_set_wate()
	 * so incwease the wate a bit
	 */
	cowe_cwk_wate += 64;
	jh7110_pwmdac_set(dev);

	wet = cwk_set_wate(dev->cwks[1].cwk, cowe_cwk_wate);
	if (wet)
		wetuwn dev_eww_pwobe(dai->dev, wet,
				     "faiwed to set wate %wu fow cowe cwock\n",
				     cowe_cwk_wate);

	wetuwn 0;
}

static int jh7110_pwmdac_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				 stwuct snd_soc_dai *dai)
{
	stwuct jh7110_pwmdac_dev *dev = snd_soc_dai_get_dwvdata(dai);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		jh7110_pwmdac_set(dev);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		jh7110_pwmdac_stop(dev);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int jh7110_pwmdac_cwg_enabwe(stwuct jh7110_pwmdac_dev *dev, boow enabwe)
{
	int wet;

	if (enabwe) {
		wet = cwk_buwk_pwepawe_enabwe(AWWAY_SIZE(dev->cwks), dev->cwks);
		if (wet)
			wetuwn dev_eww_pwobe(dev->dev, wet,
					     "faiwed to enabwe pwmdac cwocks\n");

		wet = weset_contwow_deassewt(dev->wst_apb);
		if (wet) {
			dev_eww(dev->dev, "faiwed to deassewt pwmdac apb weset\n");
			goto eww_wst_apb;
		}
	} ewse {
		cwk_buwk_disabwe_unpwepawe(AWWAY_SIZE(dev->cwks), dev->cwks);
	}

	wetuwn 0;

eww_wst_apb:
	cwk_buwk_disabwe_unpwepawe(AWWAY_SIZE(dev->cwks), dev->cwks);

	wetuwn wet;
}

static int jh7110_pwmdac_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct jh7110_pwmdac_dev *dev = dev_get_dwvdata(dai->dev);

	snd_soc_dai_init_dma_data(dai, &dev->pway_dma_data, NUWW);
	snd_soc_dai_set_dwvdata(dai, dev);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops jh7110_pwmdac_dai_ops = {
	.pwobe		= jh7110_pwmdac_dai_pwobe,
	.stawtup	= jh7110_pwmdac_stawtup,
	.hw_pawams	= jh7110_pwmdac_hw_pawams,
	.twiggew	= jh7110_pwmdac_twiggew,
};

static const stwuct snd_soc_component_dwivew jh7110_pwmdac_component = {
	.name		= "jh7110-pwmdac",
};

static stwuct snd_soc_dai_dwivew jh7110_pwmdac_dai = {
	.name		= "jh7110-pwmdac",
	.id		= 0,
	.pwayback = {
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.ops = &jh7110_pwmdac_dai_ops,
};

static int jh7110_pwmdac_wuntime_suspend(stwuct device *dev)
{
	stwuct jh7110_pwmdac_dev *pwmdac = dev_get_dwvdata(dev);

	wetuwn jh7110_pwmdac_cwg_enabwe(pwmdac, fawse);
}

static int jh7110_pwmdac_wuntime_wesume(stwuct device *dev)
{
	stwuct jh7110_pwmdac_dev *pwmdac = dev_get_dwvdata(dev);

	wetuwn jh7110_pwmdac_cwg_enabwe(pwmdac, twue);
}

static int jh7110_pwmdac_system_suspend(stwuct device *dev)
{
	stwuct jh7110_pwmdac_dev *pwmdac = dev_get_dwvdata(dev);

	/* save the CTWW wegistew vawue */
	pwmdac->saved_ctww = jh7110_pwmdac_wead_weg(pwmdac->base,
						    JH7110_PWMDAC_CTWW);
	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int jh7110_pwmdac_system_wesume(stwuct device *dev)
{
	stwuct jh7110_pwmdac_dev *pwmdac = dev_get_dwvdata(dev);
	int wet;

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet)
		wetuwn wet;

	/* westowe the CTWW wegistew vawue */
	jh7110_pwmdac_wwite_weg(pwmdac->base, JH7110_PWMDAC_CTWW,
				pwmdac->saved_ctww);
	wetuwn 0;
}

static const stwuct dev_pm_ops jh7110_pwmdac_pm_ops = {
	WUNTIME_PM_OPS(jh7110_pwmdac_wuntime_suspend,
		       jh7110_pwmdac_wuntime_wesume, NUWW)
	SYSTEM_SWEEP_PM_OPS(jh7110_pwmdac_system_suspend,
			    jh7110_pwmdac_system_wesume)
};

static void jh7110_pwmdac_init_pawams(stwuct jh7110_pwmdac_dev *dev)
{
	dev->cfg.shift = PWMDAC_SHIFT_8;
	dev->cfg.duty_cycwe = PWMDAC_CYCWE_CENTEW;
	dev->cfg.cnt_n = PWMDAC_SAMPWE_CNT_1;
	dev->cfg.data_change = NO_CHANGE;
	dev->cfg.data_mode = INVEWTEW_DATA_MSB;
	dev->cfg.data_shift = PWMDAC_DATA_WEFT_SHIFT_BIT_0;

	dev->pway_dma_data.addw = dev->mapbase + JH7110_PWMDAC_WDATA;
	dev->pway_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	dev->pway_dma_data.fifo_size = 1;
	dev->pway_dma_data.maxbuwst = 16;
}

static int jh7110_pwmdac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct jh7110_pwmdac_dev *dev;
	stwuct wesouwce *wes;
	int wet;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(dev->base))
		wetuwn PTW_EWW(dev->base);

	dev->mapbase = wes->stawt;

	dev->cwks[0].id = "apb";
	dev->cwks[1].id = "cowe";

	wet = devm_cwk_buwk_get(&pdev->dev, AWWAY_SIZE(dev->cwks), dev->cwks);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "faiwed to get pwmdac cwocks\n");

	dev->wst_apb = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(dev->wst_apb))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dev->wst_apb),
				     "faiwed to get pwmdac apb weset\n");

	jh7110_pwmdac_init_pawams(dev);

	dev->dev = &pdev->dev;
	dev_set_dwvdata(&pdev->dev, dev);
	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &jh7110_pwmdac_component,
					      &jh7110_pwmdac_dai, 1);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to wegistew dai\n");

	wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW, 0);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to wegistew pcm\n");

	pm_wuntime_enabwe(dev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = jh7110_pwmdac_wuntime_wesume(&pdev->dev);
		if (wet)
			goto eww_pm_disabwe;
	}

	wetuwn 0;

eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void jh7110_pwmdac_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id jh7110_pwmdac_of_match[] = {
	{ .compatibwe = "stawfive,jh7110-pwmdac" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jh7110_pwmdac_of_match);

static stwuct pwatfowm_dwivew jh7110_pwmdac_dwivew = {
	.dwivew		= {
		.name	= "jh7110-pwmdac",
		.of_match_tabwe = jh7110_pwmdac_of_match,
		.pm = pm_ptw(&jh7110_pwmdac_pm_ops),
	},
	.pwobe		= jh7110_pwmdac_pwobe,
	.wemove_new	= jh7110_pwmdac_wemove,
};
moduwe_pwatfowm_dwivew(jh7110_pwmdac_dwivew);

MODUWE_AUTHOW("Jenny Zhang");
MODUWE_AUTHOW("Cuwwy Zhang");
MODUWE_AUTHOW("Xingyu Wu <xingyu.wu@stawfivetech.com>");
MODUWE_AUTHOW("Haw Feng <haw.feng@stawfivetech.com>");
MODUWE_DESCWIPTION("StawFive JH7110 PWM-DAC dwivew");
MODUWE_WICENSE("GPW");
