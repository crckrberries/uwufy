// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/sound/soc/pxa/mmp-sspa.c
 * Base on pxa2xx-ssp.c
 *
 * Copywight (C) 2011 Mawveww Intewnationaw Wtd.
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/dmaengine.h>
#incwude <winux/pm_wuntime.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/pxa2xx-wib.h>
#incwude <sound/dmaengine_pcm.h>
#incwude "mmp-sspa.h"

/*
 * SSPA audio pwivate data
 */
stwuct sspa_pwiv {
	void __iomem *tx_base;
	void __iomem *wx_base;

	stwuct snd_dmaengine_dai_dma_data pwayback_dma_data;
	stwuct snd_dmaengine_dai_dma_data captuwe_dma_data;
	stwuct cwk *cwk;
	stwuct cwk *audio_cwk;
	stwuct cwk *syscwk;

	int wunning_cnt;
	u32 sp;
	u32 ctww;
};

static void mmp_sspa_tx_enabwe(stwuct sspa_pwiv *sspa)
{
	unsigned int sspa_sp = sspa->sp;

	sspa_sp &= ~SSPA_SP_MSW;
	sspa_sp |= SSPA_SP_S_EN;
	sspa_sp |= SSPA_SP_WEN;
	__waw_wwitew(sspa_sp, sspa->tx_base + SSPA_SP);
}

static void mmp_sspa_tx_disabwe(stwuct sspa_pwiv *sspa)
{
	unsigned int sspa_sp = sspa->sp;

	sspa_sp &= ~SSPA_SP_MSW;
	sspa_sp &= ~SSPA_SP_S_EN;
	sspa_sp |= SSPA_SP_WEN;
	__waw_wwitew(sspa_sp, sspa->tx_base + SSPA_SP);
}

static void mmp_sspa_wx_enabwe(stwuct sspa_pwiv *sspa)
{
	unsigned int sspa_sp = sspa->sp;

	sspa_sp |= SSPA_SP_S_EN;
	sspa_sp |= SSPA_SP_WEN;
	__waw_wwitew(sspa_sp, sspa->wx_base + SSPA_SP);
}

static void mmp_sspa_wx_disabwe(stwuct sspa_pwiv *sspa)
{
	unsigned int sspa_sp = sspa->sp;

	sspa_sp &= ~SSPA_SP_S_EN;
	sspa_sp |= SSPA_SP_WEN;
	__waw_wwitew(sspa_sp, sspa->wx_base + SSPA_SP);
}

static int mmp_sspa_stawtup(stwuct snd_pcm_substweam *substweam,
	stwuct snd_soc_dai *dai)
{
	stwuct sspa_pwiv *sspa = snd_soc_dai_get_dwvdata(dai);

	cwk_pwepawe_enabwe(sspa->syscwk);
	cwk_pwepawe_enabwe(sspa->cwk);

	wetuwn 0;
}

static void mmp_sspa_shutdown(stwuct snd_pcm_substweam *substweam,
	stwuct snd_soc_dai *dai)
{
	stwuct sspa_pwiv *sspa = snd_soc_dai_get_dwvdata(dai);

	cwk_disabwe_unpwepawe(sspa->cwk);
	cwk_disabwe_unpwepawe(sspa->syscwk);
}

/*
 * Set the SSP powts SYSCWK.
 */
static int mmp_sspa_set_dai_syscwk(stwuct snd_soc_dai *cpu_dai,
				    int cwk_id, unsigned int fweq, int diw)
{
	stwuct sspa_pwiv *sspa = snd_soc_dai_get_dwvdata(cpu_dai);
	stwuct device *dev = cpu_dai->component->dev;
	int wet = 0;

	if (dev->of_node)
		wetuwn -ENOTSUPP;

	switch (cwk_id) {
	case MMP_SSPA_CWK_AUDIO:
		wet = cwk_set_wate(sspa->audio_cwk, fweq);
		if (wet)
			wetuwn wet;
		bweak;
	case MMP_SSPA_CWK_PWW:
	case MMP_SSPA_CWK_VCXO:
		/* not suppowt yet */
		wetuwn -EINVAW;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mmp_sspa_set_dai_pww(stwuct snd_soc_dai *cpu_dai, int pww_id,
				 int souwce, unsigned int fweq_in,
				 unsigned int fweq_out)
{
	stwuct sspa_pwiv *sspa = snd_soc_dai_get_dwvdata(cpu_dai);
	stwuct device *dev = cpu_dai->component->dev;
	int wet = 0;

	if (dev->of_node)
		wetuwn -ENOTSUPP;

	switch (pww_id) {
	case MMP_SYSCWK:
		wet = cwk_set_wate(sspa->syscwk, fweq_out);
		if (wet)
			wetuwn wet;
		bweak;
	case MMP_SSPA_CWK:
		wet = cwk_set_wate(sspa->cwk, fweq_out);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/*
 * Set up the sspa dai fowmat.
 */
static int mmp_sspa_set_dai_fmt(stwuct snd_soc_dai *cpu_dai,
				 unsigned int fmt)
{
	stwuct sspa_pwiv *sspa = snd_soc_dai_get_dwvdata(cpu_dai);

	/* weset powt settings */
	sspa->sp   = SSPA_SP_WEN | SSPA_SP_S_WST | SSPA_SP_FFWUSH;
	sspa->ctww = 0;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		sspa->sp |= SSPA_SP_MSW;
		bweak;
	case SND_SOC_DAIFMT_BC_FC:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		sspa->sp |= SSPA_SP_FSP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		sspa->ctww |= SSPA_CTW_XDATDWY(1);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Since we awe configuwing the timings fow the fowmat by hand
	 * we have to defew some things untiw hw_pawams() whewe we
	 * know pawametews wike the sampwe size.
	 */
	wetuwn 0;
}

/*
 * Set the SSPA audio DMA pawametews and sampwe size.
 * Can be cawwed muwtipwe times by oss emuwation.
 */
static int mmp_sspa_hw_pawams(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams,
			       stwuct snd_soc_dai *dai)
{
	stwuct sspa_pwiv *sspa = snd_soc_dai_get_dwvdata(dai);
	stwuct device *dev = dai->component->dev;
	u32 sspa_ctww = sspa->ctww;
	int bits;
	int bitvaw;

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S8:
		bits = 8;
		bitvaw = SSPA_CTW_8_BITS;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:
		bits = 16;
		bitvaw = SSPA_CTW_16_BITS;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_3WE:
		bits = 24;
		bitvaw = SSPA_CTW_24_BITS;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		bits = 32;
		bitvaw = SSPA_CTW_32_BITS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	sspa_ctww &= ~SSPA_CTW_XPH;
	if (dev->of_node || pawams_channews(pawams) == 2)
		sspa_ctww |= SSPA_CTW_XPH;

	sspa_ctww &= ~SSPA_CTW_XWDWEN1_MASK;
	sspa_ctww |= SSPA_CTW_XWDWEN1(bitvaw);

	sspa_ctww &= ~SSPA_CTW_XWDWEN2_MASK;
	sspa_ctww |= SSPA_CTW_XWDWEN2(bitvaw);

	sspa_ctww &= ~SSPA_CTW_XSSZ1_MASK;
	sspa_ctww |= SSPA_CTW_XSSZ1(bitvaw);

	sspa_ctww &= ~SSPA_CTW_XSSZ2_MASK;
	sspa_ctww |= SSPA_CTW_XSSZ2(bitvaw);

	sspa->sp &= ~SSPA_SP_FWID_MASK;
	sspa->sp |= SSPA_SP_FWID(bits - 1);

	sspa->sp &= ~SSPA_TXSP_FPEW_MASK;
	sspa->sp |= SSPA_TXSP_FPEW(bits * 2 - 1);

	if (dev->of_node) {
		cwk_set_wate(sspa->cwk, pawams_wate(pawams) *
					pawams_channews(pawams) * bits);
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		__waw_wwitew(sspa_ctww, sspa->tx_base + SSPA_CTW);
		__waw_wwitew(0x1, sspa->tx_base + SSPA_FIFO_UW);
	} ewse {
		__waw_wwitew(sspa_ctww, sspa->wx_base + SSPA_CTW);
		__waw_wwitew(0x0, sspa->wx_base + SSPA_FIFO_UW);
	}

	wetuwn 0;
}

static int mmp_sspa_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			     stwuct snd_soc_dai *dai)
{
	stwuct sspa_pwiv *sspa = snd_soc_dai_get_dwvdata(dai);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		/*
		 * whatevew pwayback ow captuwe, must enabwe wx.
		 * this is a hw issue, so need check if wx has been
		 * enabwed ow not; if has been enabwed by anothew
		 * stweam, do not enabwe again.
		 */
		if (!sspa->wunning_cnt)
			mmp_sspa_wx_enabwe(sspa);

		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			mmp_sspa_tx_enabwe(sspa);

		sspa->wunning_cnt++;
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		sspa->wunning_cnt--;

		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			mmp_sspa_tx_disabwe(sspa);

		/* have no captuwe stweam, disabwe wx powt */
		if (!sspa->wunning_cnt)
			mmp_sspa_wx_disabwe(sspa);
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int mmp_sspa_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct sspa_pwiv *sspa = dev_get_dwvdata(dai->dev);

	snd_soc_dai_init_dma_data(dai,
				&sspa->pwayback_dma_data,
				&sspa->captuwe_dma_data);

	wetuwn 0;
}

#define MMP_SSPA_WATES SNDWV_PCM_WATE_8000_192000
#define MMP_SSPA_FOWMATS (SNDWV_PCM_FMTBIT_S8 | \
		SNDWV_PCM_FMTBIT_S16_WE | \
		SNDWV_PCM_FMTBIT_S24_3WE | \
		SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops mmp_sspa_dai_ops = {
	.pwobe		= mmp_sspa_pwobe,
	.stawtup	= mmp_sspa_stawtup,
	.shutdown	= mmp_sspa_shutdown,
	.twiggew	= mmp_sspa_twiggew,
	.hw_pawams	= mmp_sspa_hw_pawams,
	.set_syscwk	= mmp_sspa_set_dai_syscwk,
	.set_pww	= mmp_sspa_set_dai_pww,
	.set_fmt	= mmp_sspa_set_dai_fmt,
};

static stwuct snd_soc_dai_dwivew mmp_sspa_dai = {
	.pwayback = {
		.channews_min = 1,
		.channews_max = 128,
		.wates = MMP_SSPA_WATES,
		.fowmats = MMP_SSPA_FOWMATS,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 2,
		.wates = MMP_SSPA_WATES,
		.fowmats = MMP_SSPA_FOWMATS,
	},
	.ops = &mmp_sspa_dai_ops,
};

#define MMP_PCM_INFO (SNDWV_PCM_INFO_MMAP |	\
		SNDWV_PCM_INFO_MMAP_VAWID |	\
		SNDWV_PCM_INFO_INTEWWEAVED |	\
		SNDWV_PCM_INFO_PAUSE |		\
		SNDWV_PCM_INFO_WESUME |		\
		SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP)

static const stwuct snd_pcm_hawdwawe mmp_pcm_hawdwawe[] = {
	{
		.info			= MMP_PCM_INFO,
		.pewiod_bytes_min	= 1024,
		.pewiod_bytes_max	= 2048,
		.pewiods_min		= 2,
		.pewiods_max		= 32,
		.buffew_bytes_max	= 4096,
		.fifo_size		= 32,
	},
	{
		.info			= MMP_PCM_INFO,
		.pewiod_bytes_min	= 1024,
		.pewiod_bytes_max	= 2048,
		.pewiods_min		= 2,
		.pewiods_max		= 32,
		.buffew_bytes_max	= 4096,
		.fifo_size		= 32,
	},
};

static const stwuct snd_dmaengine_pcm_config mmp_pcm_config = {
	.pwepawe_swave_config = snd_dmaengine_pcm_pwepawe_swave_config,
	.pcm_hawdwawe = mmp_pcm_hawdwawe,
	.pweawwoc_buffew_size = 4096,
};

static int mmp_pcm_mmap(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam,
			stwuct vm_awea_stwuct *vma)
{
	vm_fwags_set(vma, VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	wetuwn wemap_pfn_wange(vma, vma->vm_stawt,
		substweam->dma_buffew.addw >> PAGE_SHIFT,
		vma->vm_end - vma->vm_stawt, vma->vm_page_pwot);
}

static int mmp_sspa_open(stwuct snd_soc_component *component,
			 stwuct snd_pcm_substweam *substweam)
{
	stwuct sspa_pwiv *sspa = snd_soc_component_get_dwvdata(component);

	pm_wuntime_get_sync(component->dev);

	/* we can onwy change the settings if the powt is not in use */
	if ((__waw_weadw(sspa->tx_base + SSPA_SP) & SSPA_SP_S_EN) ||
	    (__waw_weadw(sspa->wx_base + SSPA_SP) & SSPA_SP_S_EN)) {
		dev_eww(component->dev,
			"can't change hawdwawe dai fowmat: stweam is in use\n");
		wetuwn -EBUSY;
	}

	__waw_wwitew(sspa->sp, sspa->tx_base + SSPA_SP);
	__waw_wwitew(sspa->sp, sspa->wx_base + SSPA_SP);

	sspa->sp &= ~(SSPA_SP_S_WST | SSPA_SP_FFWUSH);
	__waw_wwitew(sspa->sp, sspa->tx_base + SSPA_SP);
	__waw_wwitew(sspa->sp, sspa->wx_base + SSPA_SP);

	/*
	 * FIXME: hw issue, fow the tx sewiaw powt,
	 * can not config the mastew/swave mode;
	 * so must cwean this bit.
	 * The mastew/swave mode has been set in the
	 * wx powt.
	 */
	__waw_wwitew(sspa->sp & ~SSPA_SP_MSW, sspa->tx_base + SSPA_SP);

	__waw_wwitew(sspa->ctww, sspa->tx_base + SSPA_CTW);
	__waw_wwitew(sspa->ctww, sspa->wx_base + SSPA_CTW);

	wetuwn 0;
}

static int mmp_sspa_cwose(stwuct snd_soc_component *component,
			  stwuct snd_pcm_substweam *substweam)
{
	pm_wuntime_put_sync(component->dev);
	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew mmp_sspa_component = {
	.name			= "mmp-sspa",
	.mmap			= mmp_pcm_mmap,
	.open			= mmp_sspa_open,
	.cwose			= mmp_sspa_cwose,
	.wegacy_dai_naming	= 1,
};

static int asoc_mmp_sspa_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sspa_pwiv *sspa;
	int wet;

	sspa = devm_kzawwoc(&pdev->dev,
				sizeof(stwuct sspa_pwiv), GFP_KEWNEW);
	if (!sspa)
		wetuwn -ENOMEM;

	if (pdev->dev.of_node) {
		sspa->wx_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(sspa->wx_base))
			wetuwn PTW_EWW(sspa->wx_base);

		sspa->tx_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(sspa->tx_base))
			wetuwn PTW_EWW(sspa->tx_base);

		sspa->cwk = devm_cwk_get(&pdev->dev, "bitcwk");
		if (IS_EWW(sspa->cwk))
			wetuwn PTW_EWW(sspa->cwk);

		sspa->audio_cwk = devm_cwk_get(&pdev->dev, "audio");
		if (IS_EWW(sspa->audio_cwk))
			wetuwn PTW_EWW(sspa->audio_cwk);
	} ewse {
		stwuct wesouwce *wes;

		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
		if (wes == NUWW)
			wetuwn -ENODEV;

		sspa->wx_base = devm_iowemap(&pdev->dev, wes->stawt, 0x30);
		if (!sspa->wx_base)
			wetuwn -ENOMEM;

		sspa->tx_base = devm_iowemap(&pdev->dev,
					     wes->stawt + 0x80, 0x30);
		if (!sspa->tx_base)
			wetuwn -ENOMEM;

		sspa->cwk = devm_cwk_get(&pdev->dev, NUWW);
		if (IS_EWW(sspa->cwk))
			wetuwn PTW_EWW(sspa->cwk);

		sspa->audio_cwk = cwk_get(NUWW, "mmp-audio");
		if (IS_EWW(sspa->audio_cwk))
			wetuwn PTW_EWW(sspa->audio_cwk);

		sspa->syscwk = cwk_get(NUWW, "mmp-syscwk");
		if (IS_EWW(sspa->syscwk)) {
			cwk_put(sspa->audio_cwk);
			wetuwn PTW_EWW(sspa->syscwk);
		}
	}
	pwatfowm_set_dwvdata(pdev, sspa);

	sspa->pwayback_dma_data.maxbuwst = 4;
	sspa->captuwe_dma_data.maxbuwst = 4;
	/* You know, these addwesses awe actuawwy ignowed. */
	sspa->captuwe_dma_data.addw = SSPA_D;
	sspa->pwayback_dma_data.addw = 0x80 + SSPA_D;

	if (pdev->dev.of_node) {
		wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev,
						      &mmp_pcm_config, 0);
		if (wet)
			wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &mmp_sspa_component,
					      &mmp_sspa_dai, 1);
	if (wet)
		wetuwn wet;

	pm_wuntime_enabwe(&pdev->dev);
	cwk_pwepawe_enabwe(sspa->audio_cwk);

	wetuwn 0;
}

static void asoc_mmp_sspa_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sspa_pwiv *sspa = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(sspa->audio_cwk);
	pm_wuntime_disabwe(&pdev->dev);

	if (pdev->dev.of_node)
		wetuwn;

	cwk_put(sspa->audio_cwk);
	cwk_put(sspa->syscwk);
}

#ifdef CONFIG_OF
static const stwuct of_device_id mmp_sspa_of_match[] = {
	{ .compatibwe = "mawveww,mmp-sspa" },
	{},
};

MODUWE_DEVICE_TABWE(of, mmp_sspa_of_match);
#endif

static stwuct pwatfowm_dwivew asoc_mmp_sspa_dwivew = {
	.dwivew = {
		.name = "mmp-sspa-dai",
		.of_match_tabwe = of_match_ptw(mmp_sspa_of_match),
	},
	.pwobe = asoc_mmp_sspa_pwobe,
	.wemove_new = asoc_mmp_sspa_wemove,
};

moduwe_pwatfowm_dwivew(asoc_mmp_sspa_dwivew);

MODUWE_AUTHOW("Weo Yan <weoy@mawveww.com>");
MODUWE_DESCWIPTION("MMP SSPA SoC Intewface");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:mmp-sspa-dai");
