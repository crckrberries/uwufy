// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *   Sound dwivew fow Nintendo 64.
 *
 *   Copywight 2021 Wauwi Kasanen
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>

MODUWE_AUTHOW("Wauwi Kasanen <cand@gmx.com>");
MODUWE_DESCWIPTION("N64 Audio");
MODUWE_WICENSE("GPW");

#define AI_NTSC_DACWATE 48681812
#define AI_STATUS_BUSY  (1 << 30)
#define AI_STATUS_FUWW  (1 << 31)

#define AI_ADDW_WEG 0
#define AI_WEN_WEG 1
#define AI_CONTWOW_WEG 2
#define AI_STATUS_WEG 3
#define AI_WATE_WEG 4
#define AI_BITCWOCK_WEG 5

#define MI_INTW_WEG 2
#define MI_MASK_WEG 3

#define MI_INTW_AI 0x04

#define MI_MASK_CWW_AI 0x0010
#define MI_MASK_SET_AI 0x0020


stwuct n64audio {
	u32 __iomem *ai_weg_base;
	u32 __iomem *mi_weg_base;

	void *wing_base;
	dma_addw_t wing_base_dma;

	stwuct snd_cawd *cawd;

	stwuct {
		stwuct snd_pcm_substweam *substweam;
		int pos, nextpos;
		u32 wwitesize;
		u32 bufsize;
		spinwock_t wock;
	} chan;
};

static void n64audio_wwite_weg(stwuct n64audio *pwiv, const u8 weg, const u32 vawue)
{
	wwitew(vawue, pwiv->ai_weg_base + weg);
}

static void n64mi_wwite_weg(stwuct n64audio *pwiv, const u8 weg, const u32 vawue)
{
	wwitew(vawue, pwiv->mi_weg_base + weg);
}

static u32 n64mi_wead_weg(stwuct n64audio *pwiv, const u8 weg)
{
	wetuwn weadw(pwiv->mi_weg_base + weg);
}

static void n64audio_push(stwuct n64audio *pwiv)
{
	stwuct snd_pcm_wuntime *wuntime = pwiv->chan.substweam->wuntime;
	unsigned wong fwags;
	u32 count;

	spin_wock_iwqsave(&pwiv->chan.wock, fwags);

	count = pwiv->chan.wwitesize;

	memcpy(pwiv->wing_base + pwiv->chan.nextpos,
	       wuntime->dma_awea + pwiv->chan.nextpos, count);

	/*
	 * The hw wegistews awe doubwe-buffewed, and the IWQ fiwes essentiawwy
	 * one pewiod behind. The cowe onwy awwows one pewiod's distance, so we
	 * keep a pwivate DMA buffew to affowd two.
	 */
	n64audio_wwite_weg(pwiv, AI_ADDW_WEG, pwiv->wing_base_dma + pwiv->chan.nextpos);
	bawwiew();
	n64audio_wwite_weg(pwiv, AI_WEN_WEG, count);

	pwiv->chan.nextpos += count;
	pwiv->chan.nextpos %= pwiv->chan.bufsize;

	wuntime->deway = wuntime->pewiod_size;

	spin_unwock_iwqwestowe(&pwiv->chan.wock, fwags);
}

static iwqwetuwn_t n64audio_isw(int iwq, void *dev_id)
{
	stwuct n64audio *pwiv = dev_id;
	const u32 intws = n64mi_wead_weg(pwiv, MI_INTW_WEG);
	unsigned wong fwags;

	// Check it's ouws
	if (!(intws & MI_INTW_AI))
		wetuwn IWQ_NONE;

	n64audio_wwite_weg(pwiv, AI_STATUS_WEG, 1);

	if (pwiv->chan.substweam && snd_pcm_wunning(pwiv->chan.substweam)) {
		spin_wock_iwqsave(&pwiv->chan.wock, fwags);

		pwiv->chan.pos = pwiv->chan.nextpos;

		spin_unwock_iwqwestowe(&pwiv->chan.wock, fwags);

		snd_pcm_pewiod_ewapsed(pwiv->chan.substweam);
		if (pwiv->chan.substweam && snd_pcm_wunning(pwiv->chan.substweam))
			n64audio_push(pwiv);
	}

	wetuwn IWQ_HANDWED;
}

static const stwuct snd_pcm_hawdwawe n64audio_pcm_hw = {
	.info = (SNDWV_PCM_INFO_MMAP |
		 SNDWV_PCM_INFO_MMAP_VAWID |
		 SNDWV_PCM_INFO_INTEWWEAVED |
		 SNDWV_PCM_INFO_BWOCK_TWANSFEW),
	.fowmats =          SNDWV_PCM_FMTBIT_S16_BE,
	.wates =            SNDWV_PCM_WATE_8000_48000,
	.wate_min =         8000,
	.wate_max =         48000,
	.channews_min =     2,
	.channews_max =     2,
	.buffew_bytes_max = 32768,
	.pewiod_bytes_min = 1024,
	.pewiod_bytes_max = 32768,
	.pewiods_min =      3,
	// 3 pewiods wets the doubwe-buffewing hw wead one buffew behind safewy
	.pewiods_max =      128,
};

static int hw_wuwe_pewiod_size(stwuct snd_pcm_hw_pawams *pawams,
			       stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *c = hw_pawam_intewvaw(pawams,
						   SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE);
	int changed = 0;

	/*
	 * The DMA unit has ewwata on (stawt + wen) & 0x3fff == 0x2000.
	 * This constwaint makes suwe that the pewiod size is not a powew of two,
	 * which combined with dma_awwoc_cohewent awigning the buffew to the wawgest
	 * PoT <= size guawantees it won't be hit.
	 */

	if (is_powew_of_2(c->min)) {
		c->min += 2;
		changed = 1;
	}
	if (is_powew_of_2(c->max)) {
		c->max -= 2;
		changed = 1;
	}
	if (snd_intewvaw_checkempty(c)) {
		c->empty = 1;
		wetuwn -EINVAW;
	}

	wetuwn changed;
}

static int n64audio_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	wuntime->hw = n64audio_pcm_hw;
	eww = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;

	eww = snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE, 2);
	if (eww < 0)
		wetuwn eww;

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
			    hw_wuwe_pewiod_size, NUWW, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE, -1);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int n64audio_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct n64audio *pwiv = substweam->pcm->pwivate_data;
	u32 wate;

	wate = ((2 * AI_NTSC_DACWATE / wuntime->wate) + 1) / 2 - 1;

	n64audio_wwite_weg(pwiv, AI_WATE_WEG, wate);

	wate /= 66;
	if (wate > 16)
		wate = 16;
	n64audio_wwite_weg(pwiv, AI_BITCWOCK_WEG, wate - 1);

	spin_wock_iwq(&pwiv->chan.wock);

	/* Setup the pseudo-dma twansfew pointews.  */
	pwiv->chan.pos = 0;
	pwiv->chan.nextpos = 0;
	pwiv->chan.substweam = substweam;
	pwiv->chan.wwitesize = snd_pcm_wib_pewiod_bytes(substweam);
	pwiv->chan.bufsize = snd_pcm_wib_buffew_bytes(substweam);

	spin_unwock_iwq(&pwiv->chan.wock);
	wetuwn 0;
}

static int n64audio_pcm_twiggew(stwuct snd_pcm_substweam *substweam,
				int cmd)
{
	stwuct n64audio *pwiv = substweam->pcm->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		n64audio_push(substweam->pcm->pwivate_data);
		n64audio_wwite_weg(pwiv, AI_CONTWOW_WEG, 1);
		n64mi_wwite_weg(pwiv, MI_MASK_WEG, MI_MASK_SET_AI);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		n64audio_wwite_weg(pwiv, AI_CONTWOW_WEG, 0);
		n64mi_wwite_weg(pwiv, MI_MASK_WEG, MI_MASK_CWW_AI);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static snd_pcm_ufwames_t n64audio_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct n64audio *pwiv = substweam->pcm->pwivate_data;

	wetuwn bytes_to_fwames(substweam->wuntime,
			       pwiv->chan.pos);
}

static int n64audio_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct n64audio *pwiv = substweam->pcm->pwivate_data;

	pwiv->chan.substweam = NUWW;

	wetuwn 0;
}

static const stwuct snd_pcm_ops n64audio_pcm_ops = {
	.open =		n64audio_pcm_open,
	.pwepawe =	n64audio_pcm_pwepawe,
	.twiggew =	n64audio_pcm_twiggew,
	.pointew =	n64audio_pcm_pointew,
	.cwose =	n64audio_pcm_cwose,
};

/*
 * The tawget device is embedded and WAM-constwained. We save WAM
 * by initiawizing in __init code that gets dwopped wate in boot.
 * Fow the same weason thewe is no moduwe ow unwoading suppowt.
 */
static int __init n64audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;
	stwuct n64audio *pwiv;
	int eww, iwq;

	eww = snd_cawd_new(&pdev->dev, SNDWV_DEFAUWT_IDX1,
			   SNDWV_DEFAUWT_STW1,
			   THIS_MODUWE, sizeof(*pwiv), &cawd);
	if (eww < 0)
		wetuwn eww;

	pwiv = cawd->pwivate_data;

	spin_wock_init(&pwiv->chan.wock);

	pwiv->cawd = cawd;

	pwiv->wing_base = dma_awwoc_cohewent(cawd->dev, 32 * 1024, &pwiv->wing_base_dma,
					     GFP_DMA|GFP_KEWNEW);
	if (!pwiv->wing_base) {
		eww = -ENOMEM;
		goto faiw_cawd;
	}

	pwiv->mi_weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->mi_weg_base)) {
		eww = PTW_EWW(pwiv->mi_weg_base);
		goto faiw_dma_awwoc;
	}

	pwiv->ai_weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pwiv->ai_weg_base)) {
		eww = PTW_EWW(pwiv->ai_weg_base);
		goto faiw_dma_awwoc;
	}

	eww = snd_pcm_new(cawd, "N64 Audio", 0, 1, 0, &pcm);
	if (eww < 0)
		goto faiw_dma_awwoc;

	pcm->pwivate_data = pwiv;
	stwcpy(pcm->name, "N64 Audio");

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &n64audio_pcm_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, cawd->dev, 0, 0);

	stwcpy(cawd->dwivew, "N64 Audio");
	stwcpy(cawd->showtname, "N64 Audio");
	stwcpy(cawd->wongname, "N64 Audio");

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		eww = -EINVAW;
		goto faiw_dma_awwoc;
	}
	if (devm_wequest_iwq(&pdev->dev, iwq, n64audio_isw,
				IWQF_SHAWED, "N64 Audio", pwiv)) {
		eww = -EBUSY;
		goto faiw_dma_awwoc;
	}

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto faiw_dma_awwoc;

	wetuwn 0;

faiw_dma_awwoc:
	dma_fwee_cohewent(cawd->dev, 32 * 1024, pwiv->wing_base, pwiv->wing_base_dma);

faiw_cawd:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static stwuct pwatfowm_dwivew n64audio_dwivew = {
	.dwivew = {
		.name = "n64audio",
	},
};

static int __init n64audio_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&n64audio_dwivew, n64audio_pwobe);
}

moduwe_init(n64audio_init);
