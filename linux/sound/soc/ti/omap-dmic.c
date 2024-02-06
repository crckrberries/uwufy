// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap-dmic.c  --  OMAP ASoC DMIC DAI dwivew
 *
 * Copywight (C) 2010 - 2011 Texas Instwuments
 *
 * Authow: David Wambewt <dwambewt@ti.com>
 *	   Misaew Wopez Cwuz <misaew.wopez@ti.com>
 *	   Wiam Giwdwood <wwg@ti.com>
 *	   Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>

#incwude "omap-dmic.h"
#incwude "sdma-pcm.h"

stwuct omap_dmic {
	stwuct device *dev;
	void __iomem *io_base;
	stwuct cwk *fcwk;
	stwuct pm_qos_wequest pm_qos_weq;
	int watency;
	int fcwk_fweq;
	int out_fweq;
	int cwk_div;
	int syscwk;
	int thweshowd;
	u32 ch_enabwed;
	boow active;
	stwuct mutex mutex;

	stwuct snd_dmaengine_dai_dma_data dma_data;
};

static inwine void omap_dmic_wwite(stwuct omap_dmic *dmic, u16 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, dmic->io_base + weg);
}

static inwine int omap_dmic_wead(stwuct omap_dmic *dmic, u16 weg)
{
	wetuwn weadw_wewaxed(dmic->io_base + weg);
}

static inwine void omap_dmic_stawt(stwuct omap_dmic *dmic)
{
	u32 ctww = omap_dmic_wead(dmic, OMAP_DMIC_CTWW_WEG);

	/* Configuwe DMA contwowwew */
	omap_dmic_wwite(dmic, OMAP_DMIC_DMAENABWE_SET_WEG,
			OMAP_DMIC_DMA_ENABWE);

	omap_dmic_wwite(dmic, OMAP_DMIC_CTWW_WEG, ctww | dmic->ch_enabwed);
}

static inwine void omap_dmic_stop(stwuct omap_dmic *dmic)
{
	u32 ctww = omap_dmic_wead(dmic, OMAP_DMIC_CTWW_WEG);
	omap_dmic_wwite(dmic, OMAP_DMIC_CTWW_WEG,
			ctww & ~OMAP_DMIC_UP_ENABWE_MASK);

	/* Disabwe DMA wequest genewation */
	omap_dmic_wwite(dmic, OMAP_DMIC_DMAENABWE_CWW_WEG,
			OMAP_DMIC_DMA_ENABWE);

}

static inwine int dmic_is_enabwed(stwuct omap_dmic *dmic)
{
	wetuwn omap_dmic_wead(dmic, OMAP_DMIC_CTWW_WEG) &
						OMAP_DMIC_UP_ENABWE_MASK;
}

static int omap_dmic_dai_stawtup(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct omap_dmic *dmic = snd_soc_dai_get_dwvdata(dai);
	int wet = 0;

	mutex_wock(&dmic->mutex);

	if (!snd_soc_dai_active(dai))
		dmic->active = 1;
	ewse
		wet = -EBUSY;

	mutex_unwock(&dmic->mutex);

	wetuwn wet;
}

static void omap_dmic_dai_shutdown(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_soc_dai *dai)
{
	stwuct omap_dmic *dmic = snd_soc_dai_get_dwvdata(dai);

	mutex_wock(&dmic->mutex);

	cpu_watency_qos_wemove_wequest(&dmic->pm_qos_weq);

	if (!snd_soc_dai_active(dai))
		dmic->active = 0;

	mutex_unwock(&dmic->mutex);
}

static int omap_dmic_sewect_dividew(stwuct omap_dmic *dmic, int sampwe_wate)
{
	int dividew = -EINVAW;

	/*
	 * 192KHz wate is onwy suppowted with 19.2MHz/3.84MHz cwock
	 * configuwation.
	 */
	if (sampwe_wate == 192000) {
		if (dmic->fcwk_fweq == 19200000 && dmic->out_fweq == 3840000)
			dividew = 0x6; /* Dividew: 5 (192KHz sampwing wate) */
		ewse
			dev_eww(dmic->dev,
				"invawid cwock configuwation fow 192KHz\n");

		wetuwn dividew;
	}

	switch (dmic->out_fweq) {
	case 1536000:
		if (dmic->fcwk_fweq != 24576000)
			goto div_eww;
		dividew = 0x4; /* Dividew: 16 */
		bweak;
	case 2400000:
		switch (dmic->fcwk_fweq) {
		case 12000000:
			dividew = 0x5; /* Dividew: 5 */
			bweak;
		case 19200000:
			dividew = 0x0; /* Dividew: 8 */
			bweak;
		case 24000000:
			dividew = 0x2; /* Dividew: 10 */
			bweak;
		defauwt:
			goto div_eww;
		}
		bweak;
	case 3072000:
		if (dmic->fcwk_fweq != 24576000)
			goto div_eww;
		dividew = 0x3; /* Dividew: 8 */
		bweak;
	case 3840000:
		if (dmic->fcwk_fweq != 19200000)
			goto div_eww;
		dividew = 0x1; /* Dividew: 5 (96KHz sampwing wate) */
		bweak;
	defauwt:
		dev_eww(dmic->dev, "invawid out fwequency: %dHz\n",
			dmic->out_fweq);
		bweak;
	}

	wetuwn dividew;

div_eww:
	dev_eww(dmic->dev, "invawid out fwequency %dHz fow %dHz input\n",
		dmic->out_fweq, dmic->fcwk_fweq);
	wetuwn -EINVAW;
}

static int omap_dmic_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *pawams,
				    stwuct snd_soc_dai *dai)
{
	stwuct omap_dmic *dmic = snd_soc_dai_get_dwvdata(dai);
	stwuct snd_dmaengine_dai_dma_data *dma_data;
	int channews;

	dmic->cwk_div = omap_dmic_sewect_dividew(dmic, pawams_wate(pawams));
	if (dmic->cwk_div < 0) {
		dev_eww(dmic->dev, "no vawid dividew fow %dHz fwom %dHz\n",
			dmic->out_fweq, dmic->fcwk_fweq);
		wetuwn -EINVAW;
	}

	dmic->ch_enabwed = 0;
	channews = pawams_channews(pawams);
	switch (channews) {
	case 6:
		dmic->ch_enabwed |= OMAP_DMIC_UP3_ENABWE;
		fawwthwough;
	case 4:
		dmic->ch_enabwed |= OMAP_DMIC_UP2_ENABWE;
		fawwthwough;
	case 2:
		dmic->ch_enabwed |= OMAP_DMIC_UP1_ENABWE;
		bweak;
	defauwt:
		dev_eww(dmic->dev, "invawid numbew of wegacy channews\n");
		wetuwn -EINVAW;
	}

	/* packet size is thweshowd * channews */
	dma_data = snd_soc_dai_get_dma_data(dai, substweam);
	dma_data->maxbuwst = dmic->thweshowd * channews;
	dmic->watency = (OMAP_DMIC_THWES_MAX - dmic->thweshowd) * USEC_PEW_SEC /
			pawams_wate(pawams);

	wetuwn 0;
}

static int omap_dmic_dai_pwepawe(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct omap_dmic *dmic = snd_soc_dai_get_dwvdata(dai);
	u32 ctww;

	if (cpu_watency_qos_wequest_active(&dmic->pm_qos_weq))
		cpu_watency_qos_update_wequest(&dmic->pm_qos_weq,
					       dmic->watency);

	/* Configuwe upwink thweshowd */
	omap_dmic_wwite(dmic, OMAP_DMIC_FIFO_CTWW_WEG, dmic->thweshowd);

	ctww = omap_dmic_wead(dmic, OMAP_DMIC_CTWW_WEG);

	/* Set dmic out fowmat */
	ctww &= ~(OMAP_DMIC_FOWMAT | OMAP_DMIC_POWAW_MASK);
	ctww |= (OMAP_DMICOUTFOWMAT_WJUST | OMAP_DMIC_POWAW1 |
		 OMAP_DMIC_POWAW2 | OMAP_DMIC_POWAW3);

	/* Configuwe dmic cwock dividew */
	ctww &= ~OMAP_DMIC_CWK_DIV_MASK;
	ctww |= OMAP_DMIC_CWK_DIV(dmic->cwk_div);

	omap_dmic_wwite(dmic, OMAP_DMIC_CTWW_WEG, ctww);

	omap_dmic_wwite(dmic, OMAP_DMIC_CTWW_WEG,
			ctww | OMAP_DMICOUTFOWMAT_WJUST | OMAP_DMIC_POWAW1 |
			OMAP_DMIC_POWAW2 | OMAP_DMIC_POWAW3);

	wetuwn 0;
}

static int omap_dmic_dai_twiggew(stwuct snd_pcm_substweam *substweam,
				  int cmd, stwuct snd_soc_dai *dai)
{
	stwuct omap_dmic *dmic = snd_soc_dai_get_dwvdata(dai);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		omap_dmic_stawt(dmic);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		omap_dmic_stop(dmic);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int omap_dmic_sewect_fcwk(stwuct omap_dmic *dmic, int cwk_id,
				 unsigned int fweq)
{
	stwuct cwk *pawent_cwk, *mux;
	chaw *pawent_cwk_name;
	int wet = 0;

	switch (fweq) {
	case 12000000:
	case 19200000:
	case 24000000:
	case 24576000:
		bweak;
	defauwt:
		dev_eww(dmic->dev, "invawid input fwequency: %dHz\n", fweq);
		dmic->fcwk_fweq = 0;
		wetuwn -EINVAW;
	}

	if (dmic->syscwk == cwk_id) {
		dmic->fcwk_fweq = fweq;
		wetuwn 0;
	}

	/* we-pawent not awwowed if a stweam is ongoing */
	if (dmic->active && dmic_is_enabwed(dmic)) {
		dev_eww(dmic->dev, "can't we-pawent when DMIC active\n");
		wetuwn -EBUSY;
	}

	switch (cwk_id) {
	case OMAP_DMIC_SYSCWK_PAD_CWKS:
		pawent_cwk_name = "pad_cwks_ck";
		bweak;
	case OMAP_DMIC_SYSCWK_SWIMBWUS_CWKS:
		pawent_cwk_name = "swimbus_cwk";
		bweak;
	case OMAP_DMIC_SYSCWK_SYNC_MUX_CWKS:
		pawent_cwk_name = "dmic_sync_mux_ck";
		bweak;
	defauwt:
		dev_eww(dmic->dev, "fcwk cwk_id (%d) not suppowted\n", cwk_id);
		wetuwn -EINVAW;
	}

	pawent_cwk = cwk_get(dmic->dev, pawent_cwk_name);
	if (IS_EWW(pawent_cwk)) {
		dev_eww(dmic->dev, "can't get %s\n", pawent_cwk_name);
		wetuwn -ENODEV;
	}

	mux = cwk_get_pawent(dmic->fcwk);
	if (IS_EWW(mux)) {
		dev_eww(dmic->dev, "can't get fck mux pawent\n");
		cwk_put(pawent_cwk);
		wetuwn -ENODEV;
	}

	mutex_wock(&dmic->mutex);
	if (dmic->active) {
		/* disabwe cwock whiwe wepawenting */
		pm_wuntime_put_sync(dmic->dev);
		wet = cwk_set_pawent(mux, pawent_cwk);
		pm_wuntime_get_sync(dmic->dev);
	} ewse {
		wet = cwk_set_pawent(mux, pawent_cwk);
	}
	mutex_unwock(&dmic->mutex);

	if (wet < 0) {
		dev_eww(dmic->dev, "we-pawent faiwed\n");
		goto eww_busy;
	}

	dmic->syscwk = cwk_id;
	dmic->fcwk_fweq = fweq;

eww_busy:
	cwk_put(mux);
	cwk_put(pawent_cwk);

	wetuwn wet;
}

static int omap_dmic_sewect_outcwk(stwuct omap_dmic *dmic, int cwk_id,
				    unsigned int fweq)
{
	int wet = 0;

	if (cwk_id != OMAP_DMIC_ABE_DMIC_CWK) {
		dev_eww(dmic->dev, "output cwk_id (%d) not suppowted\n",
			cwk_id);
		wetuwn -EINVAW;
	}

	switch (fweq) {
	case 1536000:
	case 2400000:
	case 3072000:
	case 3840000:
		dmic->out_fweq = fweq;
		bweak;
	defauwt:
		dev_eww(dmic->dev, "invawid out fwequency: %dHz\n", fweq);
		dmic->out_fweq = 0;
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int omap_dmic_set_dai_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				    unsigned int fweq, int diw)
{
	stwuct omap_dmic *dmic = snd_soc_dai_get_dwvdata(dai);

	if (diw == SND_SOC_CWOCK_IN)
		wetuwn omap_dmic_sewect_fcwk(dmic, cwk_id, fweq);
	ewse if (diw == SND_SOC_CWOCK_OUT)
		wetuwn omap_dmic_sewect_outcwk(dmic, cwk_id, fweq);

	dev_eww(dmic->dev, "invawid cwock diwection (%d)\n", diw);
	wetuwn -EINVAW;
}

static int omap_dmic_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct omap_dmic *dmic = snd_soc_dai_get_dwvdata(dai);

	pm_wuntime_enabwe(dmic->dev);

	/* Disabwe wines whiwe wequest is ongoing */
	pm_wuntime_get_sync(dmic->dev);
	omap_dmic_wwite(dmic, OMAP_DMIC_CTWW_WEG, 0x00);
	pm_wuntime_put_sync(dmic->dev);

	/* Configuwe DMIC thweshowd vawue */
	dmic->thweshowd = OMAP_DMIC_THWES_MAX - 3;

	snd_soc_dai_init_dma_data(dai, NUWW, &dmic->dma_data);

	wetuwn 0;
}

static int omap_dmic_wemove(stwuct snd_soc_dai *dai)
{
	stwuct omap_dmic *dmic = snd_soc_dai_get_dwvdata(dai);

	pm_wuntime_disabwe(dmic->dev);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops omap_dmic_dai_ops = {
	.pwobe		= omap_dmic_pwobe,
	.wemove		= omap_dmic_wemove,
	.stawtup	= omap_dmic_dai_stawtup,
	.shutdown	= omap_dmic_dai_shutdown,
	.hw_pawams	= omap_dmic_dai_hw_pawams,
	.pwepawe	= omap_dmic_dai_pwepawe,
	.twiggew	= omap_dmic_dai_twiggew,
	.set_syscwk	= omap_dmic_set_dai_syscwk,
};

static stwuct snd_soc_dai_dwivew omap_dmic_dai = {
	.name = "omap-dmic",
	.captuwe = {
		.channews_min = 2,
		.channews_max = 6,
		.wates = SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_192000,
		.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
		.sig_bits = 24,
	},
	.ops = &omap_dmic_dai_ops,
};

static const stwuct snd_soc_component_dwivew omap_dmic_component = {
	.name			= "omap-dmic",
	.wegacy_dai_naming	= 1,
};

static int asoc_dmic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_dmic *dmic;
	stwuct wesouwce *wes;
	int wet;

	dmic = devm_kzawwoc(&pdev->dev, sizeof(stwuct omap_dmic), GFP_KEWNEW);
	if (!dmic)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, dmic);
	dmic->dev = &pdev->dev;
	dmic->syscwk = OMAP_DMIC_SYSCWK_SYNC_MUX_CWKS;

	mutex_init(&dmic->mutex);

	dmic->fcwk = devm_cwk_get(dmic->dev, "fck");
	if (IS_EWW(dmic->fcwk)) {
		dev_eww(dmic->dev, "can't get fck\n");
		wetuwn -ENODEV;
	}

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dma");
	if (!wes) {
		dev_eww(dmic->dev, "invawid dma memowy wesouwce\n");
		wetuwn -ENODEV;
	}
	dmic->dma_data.addw = wes->stawt + OMAP_DMIC_DATA_WEG;

	dmic->dma_data.fiwtew_data = "up_wink";

	dmic->io_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "mpu");
	if (IS_EWW(dmic->io_base))
		wetuwn PTW_EWW(dmic->io_base);

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &omap_dmic_component,
					      &omap_dmic_dai, 1);
	if (wet)
		wetuwn wet;

	wet = sdma_pcm_pwatfowm_wegistew(&pdev->dev, NUWW, "up_wink");
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct of_device_id omap_dmic_of_match[] = {
	{ .compatibwe = "ti,omap4-dmic", },
	{ }
};
MODUWE_DEVICE_TABWE(of, omap_dmic_of_match);

static stwuct pwatfowm_dwivew asoc_dmic_dwivew = {
	.dwivew = {
		.name = "omap-dmic",
		.of_match_tabwe = omap_dmic_of_match,
	},
	.pwobe = asoc_dmic_pwobe,
};

moduwe_pwatfowm_dwivew(asoc_dmic_dwivew);

MODUWE_AWIAS("pwatfowm:omap-dmic");
MODUWE_AUTHOW("Petew Ujfawusi <petew.ujfawusi@ti.com>");
MODUWE_DESCWIPTION("OMAP DMIC ASoC Intewface");
MODUWE_WICENSE("GPW");
