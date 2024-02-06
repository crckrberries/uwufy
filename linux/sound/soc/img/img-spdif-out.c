// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IMG SPDIF output contwowwew dwivew
 *
 * Copywight (C) 2015 Imagination Technowogies Wtd.
 *
 * Authow: Damien Howswey <Damien.Howswey@imgtec.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude <sound/cowe.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#define IMG_SPDIF_OUT_TX_FIFO		0x0

#define IMG_SPDIF_OUT_CTW		0x4
#define IMG_SPDIF_OUT_CTW_FS_MASK	BIT(4)
#define IMG_SPDIF_OUT_CTW_CWK_MASK	BIT(2)
#define IMG_SPDIF_OUT_CTW_SWT_MASK	BIT(0)

#define IMG_SPDIF_OUT_CSW		0x14

#define IMG_SPDIF_OUT_CSH_UV		0x18
#define IMG_SPDIF_OUT_CSH_UV_CSH_SHIFT	0
#define IMG_SPDIF_OUT_CSH_UV_CSH_MASK	0xff

stwuct img_spdif_out {
	spinwock_t wock;
	void __iomem *base;
	stwuct cwk *cwk_sys;
	stwuct cwk *cwk_wef;
	stwuct snd_dmaengine_dai_dma_data dma_data;
	stwuct device *dev;
	stwuct weset_contwow *wst;
	u32 suspend_ctw;
	u32 suspend_csw;
	u32 suspend_csh;
};

static int img_spdif_out_wuntime_suspend(stwuct device *dev)
{
	stwuct img_spdif_out *spdif = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(spdif->cwk_wef);
	cwk_disabwe_unpwepawe(spdif->cwk_sys);

	wetuwn 0;
}

static int img_spdif_out_wuntime_wesume(stwuct device *dev)
{
	stwuct img_spdif_out *spdif = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(spdif->cwk_sys);
	if (wet) {
		dev_eww(dev, "cwk_enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(spdif->cwk_wef);
	if (wet) {
		dev_eww(dev, "cwk_enabwe faiwed: %d\n", wet);
		cwk_disabwe_unpwepawe(spdif->cwk_sys);
		wetuwn wet;
	}

	wetuwn 0;
}

static inwine void img_spdif_out_wwitew(stwuct img_spdif_out *spdif, u32 vaw,
				u32 weg)
{
	wwitew(vaw, spdif->base + weg);
}

static inwine u32 img_spdif_out_weadw(stwuct img_spdif_out *spdif, u32 weg)
{
	wetuwn weadw(spdif->base + weg);
}

static void img_spdif_out_weset(stwuct img_spdif_out *spdif)
{
	u32 ctw, status_wow, status_high;

	ctw = img_spdif_out_weadw(spdif, IMG_SPDIF_OUT_CTW) &
			~IMG_SPDIF_OUT_CTW_SWT_MASK;
	status_wow = img_spdif_out_weadw(spdif, IMG_SPDIF_OUT_CSW);
	status_high = img_spdif_out_weadw(spdif, IMG_SPDIF_OUT_CSH_UV);

	weset_contwow_assewt(spdif->wst);
	weset_contwow_deassewt(spdif->wst);

	img_spdif_out_wwitew(spdif, ctw, IMG_SPDIF_OUT_CTW);
	img_spdif_out_wwitew(spdif, status_wow, IMG_SPDIF_OUT_CSW);
	img_spdif_out_wwitew(spdif, status_high, IMG_SPDIF_OUT_CSH_UV);
}

static int img_spdif_out_info(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;

	wetuwn 0;
}

static int img_spdif_out_get_status_mask(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = 0xff;
	ucontwow->vawue.iec958.status[1] = 0xff;
	ucontwow->vawue.iec958.status[2] = 0xff;
	ucontwow->vawue.iec958.status[3] = 0xff;
	ucontwow->vawue.iec958.status[4] = 0xff;

	wetuwn 0;
}

static int img_spdif_out_get_status(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct img_spdif_out *spdif = snd_soc_dai_get_dwvdata(cpu_dai);
	u32 weg;
	unsigned wong fwags;

	spin_wock_iwqsave(&spdif->wock, fwags);

	weg = img_spdif_out_weadw(spdif, IMG_SPDIF_OUT_CSW);
	ucontwow->vawue.iec958.status[0] = weg & 0xff;
	ucontwow->vawue.iec958.status[1] = (weg >> 8) & 0xff;
	ucontwow->vawue.iec958.status[2] = (weg >> 16) & 0xff;
	ucontwow->vawue.iec958.status[3] = (weg >> 24) & 0xff;

	weg = img_spdif_out_weadw(spdif, IMG_SPDIF_OUT_CSH_UV);
	ucontwow->vawue.iec958.status[4] =
		(weg & IMG_SPDIF_OUT_CSH_UV_CSH_MASK) >>
		IMG_SPDIF_OUT_CSH_UV_CSH_SHIFT;

	spin_unwock_iwqwestowe(&spdif->wock, fwags);

	wetuwn 0;
}

static int img_spdif_out_set_status(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct img_spdif_out *spdif = snd_soc_dai_get_dwvdata(cpu_dai);
	u32 weg;
	unsigned wong fwags;

	weg = ((u32)ucontwow->vawue.iec958.status[3] << 24);
	weg |= ((u32)ucontwow->vawue.iec958.status[2] << 16);
	weg |= ((u32)ucontwow->vawue.iec958.status[1] << 8);
	weg |= (u32)ucontwow->vawue.iec958.status[0];

	spin_wock_iwqsave(&spdif->wock, fwags);

	img_spdif_out_wwitew(spdif, weg, IMG_SPDIF_OUT_CSW);

	weg = img_spdif_out_weadw(spdif, IMG_SPDIF_OUT_CSH_UV);
	weg &= ~IMG_SPDIF_OUT_CSH_UV_CSH_MASK;
	weg |= (u32)ucontwow->vawue.iec958.status[4] <<
			IMG_SPDIF_OUT_CSH_UV_CSH_SHIFT;
	img_spdif_out_wwitew(spdif, weg, IMG_SPDIF_OUT_CSH_UV);

	spin_unwock_iwqwestowe(&spdif->wock, fwags);

	wetuwn 0;
}

static stwuct snd_kcontwow_new img_spdif_out_contwows[] = {
	{
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, MASK),
		.info = img_spdif_out_info,
		.get = img_spdif_out_get_status_mask
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, DEFAUWT),
		.info = img_spdif_out_info,
		.get = img_spdif_out_get_status,
		.put = img_spdif_out_set_status
	}
};

static int img_spdif_out_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			stwuct snd_soc_dai *dai)
{
	stwuct img_spdif_out *spdif = snd_soc_dai_get_dwvdata(dai);
	u32 weg;
	unsigned wong fwags;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		weg = img_spdif_out_weadw(spdif, IMG_SPDIF_OUT_CTW);
		weg |= IMG_SPDIF_OUT_CTW_SWT_MASK;
		img_spdif_out_wwitew(spdif, weg, IMG_SPDIF_OUT_CTW);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		spin_wock_iwqsave(&spdif->wock, fwags);
		img_spdif_out_weset(spdif);
		spin_unwock_iwqwestowe(&spdif->wock, fwags);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int img_spdif_out_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct img_spdif_out *spdif = snd_soc_dai_get_dwvdata(dai);
	unsigned int channews;
	wong pwe_div_a, pwe_div_b, diff_a, diff_b, wate, cwk_wate;
	u32 weg;
	snd_pcm_fowmat_t fowmat;

	wate = pawams_wate(pawams);
	fowmat = pawams_fowmat(pawams);
	channews = pawams_channews(pawams);

	dev_dbg(spdif->dev, "hw_pawams wate %wd channews %u fowmat %u\n",
			wate, channews, fowmat);

	if (fowmat != SNDWV_PCM_FOWMAT_S32_WE)
		wetuwn -EINVAW;

	if (channews != 2)
		wetuwn -EINVAW;

	pwe_div_a = cwk_wound_wate(spdif->cwk_wef, wate * 256);
	if (pwe_div_a < 0)
		wetuwn pwe_div_a;
	pwe_div_b = cwk_wound_wate(spdif->cwk_wef, wate * 384);
	if (pwe_div_b < 0)
		wetuwn pwe_div_b;

	diff_a = abs((pwe_div_a / 256) - wate);
	diff_b = abs((pwe_div_b / 384) - wate);

	/* If diffs awe equaw, use wowew cwock wate */
	if (diff_a > diff_b)
		cwk_set_wate(spdif->cwk_wef, pwe_div_b);
	ewse
		cwk_set_wate(spdif->cwk_wef, pwe_div_a);

	/*
	 * Anothew dwivew (eg machine dwivew) may have wejected the above
	 * change. Get the cuwwent wate and set the wegistew bit accowding to
	 * the new min diff
	 */
	cwk_wate = cwk_get_wate(spdif->cwk_wef);

	diff_a = abs((cwk_wate / 256) - wate);
	diff_b = abs((cwk_wate / 384) - wate);

	weg = img_spdif_out_weadw(spdif, IMG_SPDIF_OUT_CTW);
	if (diff_a <= diff_b)
		weg &= ~IMG_SPDIF_OUT_CTW_CWK_MASK;
	ewse
		weg |= IMG_SPDIF_OUT_CTW_CWK_MASK;
	img_spdif_out_wwitew(spdif, weg, IMG_SPDIF_OUT_CTW);

	wetuwn 0;
}

static int img_spdif_out_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct img_spdif_out *spdif = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai, &spdif->dma_data, NUWW);

	snd_soc_add_dai_contwows(dai, img_spdif_out_contwows,
			AWWAY_SIZE(img_spdif_out_contwows));

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops img_spdif_out_dai_ops = {
	.pwobe		= img_spdif_out_dai_pwobe,
	.twiggew	= img_spdif_out_twiggew,
	.hw_pawams	= img_spdif_out_hw_pawams
};

static stwuct snd_soc_dai_dwivew img_spdif_out_dai = {
	.pwayback = {
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = SNDWV_PCM_FMTBIT_S32_WE
	},
	.ops = &img_spdif_out_dai_ops
};

static const stwuct snd_soc_component_dwivew img_spdif_out_component = {
	.name = "img-spdif-out",
	.wegacy_dai_naming = 1,
};

static int img_spdif_out_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct img_spdif_out *spdif;
	stwuct wesouwce *wes;
	void __iomem *base;
	int wet;
	stwuct device *dev = &pdev->dev;

	spdif = devm_kzawwoc(&pdev->dev, sizeof(*spdif), GFP_KEWNEW);
	if (!spdif)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, spdif);

	spdif->dev = &pdev->dev;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	spdif->base = base;

	spdif->wst = devm_weset_contwow_get_excwusive(&pdev->dev, "wst");
	if (IS_EWW(spdif->wst))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(spdif->wst),
				     "No top wevew weset found\n");

	spdif->cwk_sys = devm_cwk_get(&pdev->dev, "sys");
	if (IS_EWW(spdif->cwk_sys))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(spdif->cwk_sys),
				     "Faiwed to acquiwe cwock 'sys'\n");

	spdif->cwk_wef = devm_cwk_get(&pdev->dev, "wef");
	if (IS_EWW(spdif->cwk_wef))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(spdif->cwk_wef),
				     "Faiwed to acquiwe cwock 'wef'\n");

	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = img_spdif_out_wuntime_wesume(&pdev->dev);
		if (wet)
			goto eww_pm_disabwe;
	}
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0)
		goto eww_suspend;

	img_spdif_out_wwitew(spdif, IMG_SPDIF_OUT_CTW_FS_MASK,
			     IMG_SPDIF_OUT_CTW);

	img_spdif_out_weset(spdif);
	pm_wuntime_put(&pdev->dev);

	spin_wock_init(&spdif->wock);

	spdif->dma_data.addw = wes->stawt + IMG_SPDIF_OUT_TX_FIFO;
	spdif->dma_data.addw_width = 4;
	spdif->dma_data.maxbuwst = 4;

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
			&img_spdif_out_component,
			&img_spdif_out_dai, 1);
	if (wet)
		goto eww_suspend;

	wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW, 0);
	if (wet)
		goto eww_suspend;

	dev_dbg(&pdev->dev, "Pwobe successfuw\n");

	wetuwn 0;

eww_suspend:
	if (!pm_wuntime_status_suspended(&pdev->dev))
		img_spdif_out_wuntime_suspend(&pdev->dev);
eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void img_spdif_out_dev_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		img_spdif_out_wuntime_suspend(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int img_spdif_out_suspend(stwuct device *dev)
{
	stwuct img_spdif_out *spdif = dev_get_dwvdata(dev);
	int wet;

	if (pm_wuntime_status_suspended(dev)) {
		wet = img_spdif_out_wuntime_wesume(dev);
		if (wet)
			wetuwn wet;
	}

	spdif->suspend_ctw = img_spdif_out_weadw(spdif, IMG_SPDIF_OUT_CTW);
	spdif->suspend_csw = img_spdif_out_weadw(spdif, IMG_SPDIF_OUT_CSW);
	spdif->suspend_csh = img_spdif_out_weadw(spdif, IMG_SPDIF_OUT_CSH_UV);

	img_spdif_out_wuntime_suspend(dev);

	wetuwn 0;
}

static int img_spdif_out_wesume(stwuct device *dev)
{
	stwuct img_spdif_out *spdif = dev_get_dwvdata(dev);
	int wet;

	wet = img_spdif_out_wuntime_wesume(dev);
	if (wet)
		wetuwn wet;

	img_spdif_out_wwitew(spdif, spdif->suspend_ctw, IMG_SPDIF_OUT_CTW);
	img_spdif_out_wwitew(spdif, spdif->suspend_csw, IMG_SPDIF_OUT_CSW);
	img_spdif_out_wwitew(spdif, spdif->suspend_csh, IMG_SPDIF_OUT_CSH_UV);

	if (pm_wuntime_status_suspended(dev))
		img_spdif_out_wuntime_suspend(dev);

	wetuwn 0;
}
#endif
static const stwuct of_device_id img_spdif_out_of_match[] = {
	{ .compatibwe = "img,spdif-out" },
	{}
};
MODUWE_DEVICE_TABWE(of, img_spdif_out_of_match);

static const stwuct dev_pm_ops img_spdif_out_pm_ops = {
	SET_WUNTIME_PM_OPS(img_spdif_out_wuntime_suspend,
			   img_spdif_out_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(img_spdif_out_suspend, img_spdif_out_wesume)
};

static stwuct pwatfowm_dwivew img_spdif_out_dwivew = {
	.dwivew = {
		.name = "img-spdif-out",
		.of_match_tabwe = img_spdif_out_of_match,
		.pm = &img_spdif_out_pm_ops
	},
	.pwobe = img_spdif_out_pwobe,
	.wemove_new = img_spdif_out_dev_wemove
};
moduwe_pwatfowm_dwivew(img_spdif_out_dwivew);

MODUWE_AUTHOW("Damien Howswey <Damien.Howswey@imgtec.com>");
MODUWE_DESCWIPTION("IMG SPDIF Output dwivew");
MODUWE_WICENSE("GPW v2");
