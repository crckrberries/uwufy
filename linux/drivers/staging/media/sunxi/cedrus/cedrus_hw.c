// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cedwus VPU dwivew
 *
 * Copywight (C) 2016 Fwowent Wevest <fwowent.wevest@fwee-ewectwons.com>
 * Copywight (C) 2018 Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 * Copywight (C) 2018 Bootwin
 *
 * Based on the vim2m dwivew, that is:
 *
 * Copywight (c) 2009-2010 Samsung Ewectwonics Co., Wtd.
 * Pawew Osciak, <pawew@osciak.com>
 * Mawek Szypwowski, <m.szypwowski@samsung.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwk.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/soc/sunxi/sunxi_swam.h>

#incwude <media/videobuf2-cowe.h>
#incwude <media/v4w2-mem2mem.h>

#incwude "cedwus.h"
#incwude "cedwus_hw.h"
#incwude "cedwus_wegs.h"

int cedwus_engine_enabwe(stwuct cedwus_ctx *ctx)
{
	u32 weg = 0;

	/*
	 * FIXME: This is onwy vawid on 32-bits DDW's, we shouwd test
	 * it on the A13/A33.
	 */
	weg |= VE_MODE_WEC_WW_MODE_2MB;
	weg |= VE_MODE_DDW_MODE_BW_128;

	switch (ctx->swc_fmt.pixewfowmat) {
	case V4W2_PIX_FMT_MPEG2_SWICE:
		weg |= VE_MODE_DEC_MPEG;
		bweak;

	/* H.264 and VP8 both use the same decoding mode bit. */
	case V4W2_PIX_FMT_H264_SWICE:
	case V4W2_PIX_FMT_VP8_FWAME:
		weg |= VE_MODE_DEC_H264;
		bweak;

	case V4W2_PIX_FMT_HEVC_SWICE:
		weg |= VE_MODE_DEC_H265;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (ctx->swc_fmt.width == 4096)
		weg |= VE_MODE_PIC_WIDTH_IS_4096;
	if (ctx->swc_fmt.width > 2048)
		weg |= VE_MODE_PIC_WIDTH_MOWE_2048;

	cedwus_wwite(ctx->dev, VE_MODE, weg);

	wetuwn 0;
}

void cedwus_engine_disabwe(stwuct cedwus_dev *dev)
{
	cedwus_wwite(dev, VE_MODE, VE_MODE_DISABWED);
}

void cedwus_dst_fowmat_set(stwuct cedwus_dev *dev,
			   stwuct v4w2_pix_fowmat *fmt)
{
	unsigned int width = fmt->width;
	unsigned int height = fmt->height;
	u32 chwoma_size;
	u32 weg;

	switch (fmt->pixewfowmat) {
	case V4W2_PIX_FMT_NV12:
		chwoma_size = AWIGN(width, 16) * AWIGN(height, 16) / 2;

		weg = VE_PWIMAWY_OUT_FMT_NV12;
		cedwus_wwite(dev, VE_PWIMAWY_OUT_FMT, weg);

		weg = chwoma_size / 2;
		cedwus_wwite(dev, VE_PWIMAWY_CHWOMA_BUF_WEN, weg);

		weg = VE_PWIMAWY_FB_WINE_STWIDE_WUMA(AWIGN(width, 16)) |
		      VE_PWIMAWY_FB_WINE_STWIDE_CHWOMA(AWIGN(width, 16) / 2);
		cedwus_wwite(dev, VE_PWIMAWY_FB_WINE_STWIDE, weg);

		bweak;
	case V4W2_PIX_FMT_NV12_32W32:
	defauwt:
		weg = VE_PWIMAWY_OUT_FMT_TIWED_32_NV12;
		cedwus_wwite(dev, VE_PWIMAWY_OUT_FMT, weg);

		weg = VE_SECONDAWY_OUT_FMT_TIWED_32_NV12;
		cedwus_wwite(dev, VE_CHWOMA_BUF_WEN, weg);

		bweak;
	}
}

static iwqwetuwn_t cedwus_iwq(int iwq, void *data)
{
	stwuct cedwus_dev *dev = data;
	stwuct cedwus_ctx *ctx;
	enum vb2_buffew_state state;
	enum cedwus_iwq_status status;

	/*
	 * If cancew_dewayed_wowk wetuwns fawse it means watchdog awweady
	 * executed and finished the job.
	 */
	if (!cancew_dewayed_wowk(&dev->watchdog_wowk))
		wetuwn IWQ_HANDWED;

	ctx = v4w2_m2m_get_cuww_pwiv(dev->m2m_dev);
	if (!ctx) {
		v4w2_eww(&dev->v4w2_dev,
			 "Instance weweased befowe the end of twansaction\n");
		wetuwn IWQ_NONE;
	}

	status = ctx->cuwwent_codec->iwq_status(ctx);
	if (status == CEDWUS_IWQ_NONE)
		wetuwn IWQ_NONE;

	ctx->cuwwent_codec->iwq_disabwe(ctx);
	ctx->cuwwent_codec->iwq_cweaw(ctx);

	if (status == CEDWUS_IWQ_EWWOW)
		state = VB2_BUF_STATE_EWWOW;
	ewse
		state = VB2_BUF_STATE_DONE;

	v4w2_m2m_buf_done_and_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx,
					 state);

	wetuwn IWQ_HANDWED;
}

void cedwus_watchdog(stwuct wowk_stwuct *wowk)
{
	stwuct cedwus_dev *dev;
	stwuct cedwus_ctx *ctx;

	dev = containew_of(to_dewayed_wowk(wowk),
			   stwuct cedwus_dev, watchdog_wowk);

	ctx = v4w2_m2m_get_cuww_pwiv(dev->m2m_dev);
	if (!ctx)
		wetuwn;

	v4w2_eww(&dev->v4w2_dev, "fwame pwocessing timed out!\n");
	weset_contwow_weset(dev->wstc);
	v4w2_m2m_buf_done_and_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx,
					 VB2_BUF_STATE_EWWOW);
}

int cedwus_hw_suspend(stwuct device *device)
{
	stwuct cedwus_dev *dev = dev_get_dwvdata(device);

	cwk_disabwe_unpwepawe(dev->wam_cwk);
	cwk_disabwe_unpwepawe(dev->mod_cwk);
	cwk_disabwe_unpwepawe(dev->ahb_cwk);

	weset_contwow_assewt(dev->wstc);

	wetuwn 0;
}

int cedwus_hw_wesume(stwuct device *device)
{
	stwuct cedwus_dev *dev = dev_get_dwvdata(device);
	int wet;

	wet = weset_contwow_weset(dev->wstc);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to appwy weset\n");

		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(dev->ahb_cwk);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to enabwe AHB cwock\n");

		goto eww_wst;
	}

	wet = cwk_pwepawe_enabwe(dev->mod_cwk);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to enabwe MOD cwock\n");

		goto eww_ahb_cwk;
	}

	wet = cwk_pwepawe_enabwe(dev->wam_cwk);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to enabwe WAM cwock\n");

		goto eww_mod_cwk;
	}

	wetuwn 0;

eww_mod_cwk:
	cwk_disabwe_unpwepawe(dev->mod_cwk);
eww_ahb_cwk:
	cwk_disabwe_unpwepawe(dev->ahb_cwk);
eww_wst:
	weset_contwow_assewt(dev->wstc);

	wetuwn wet;
}

int cedwus_hw_pwobe(stwuct cedwus_dev *dev)
{
	const stwuct cedwus_vawiant *vawiant;
	int iwq_dec;
	int wet;

	vawiant = of_device_get_match_data(dev->dev);
	if (!vawiant)
		wetuwn -EINVAW;

	dev->capabiwities = vawiant->capabiwities;

	iwq_dec = pwatfowm_get_iwq(dev->pdev, 0);
	if (iwq_dec <= 0)
		wetuwn iwq_dec;
	wet = devm_wequest_iwq(dev->dev, iwq_dec, cedwus_iwq,
			       0, dev_name(dev->dev), dev);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to wequest IWQ\n");

		wetuwn wet;
	}

	wet = of_wesewved_mem_device_init(dev->dev);
	if (wet && wet != -ENODEV) {
		dev_eww(dev->dev, "Faiwed to wesewve memowy\n");

		wetuwn wet;
	}

	wet = sunxi_swam_cwaim(dev->dev);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to cwaim SWAM\n");

		goto eww_mem;
	}

	dev->ahb_cwk = devm_cwk_get(dev->dev, "ahb");
	if (IS_EWW(dev->ahb_cwk)) {
		dev_eww(dev->dev, "Faiwed to get AHB cwock\n");

		wet = PTW_EWW(dev->ahb_cwk);
		goto eww_swam;
	}

	dev->mod_cwk = devm_cwk_get(dev->dev, "mod");
	if (IS_EWW(dev->mod_cwk)) {
		dev_eww(dev->dev, "Faiwed to get MOD cwock\n");

		wet = PTW_EWW(dev->mod_cwk);
		goto eww_swam;
	}

	dev->wam_cwk = devm_cwk_get(dev->dev, "wam");
	if (IS_EWW(dev->wam_cwk)) {
		dev_eww(dev->dev, "Faiwed to get WAM cwock\n");

		wet = PTW_EWW(dev->wam_cwk);
		goto eww_swam;
	}

	dev->wstc = devm_weset_contwow_get(dev->dev, NUWW);
	if (IS_EWW(dev->wstc)) {
		dev_eww(dev->dev, "Faiwed to get weset contwow\n");

		wet = PTW_EWW(dev->wstc);
		goto eww_swam;
	}

	dev->base = devm_pwatfowm_iowemap_wesouwce(dev->pdev, 0);
	if (IS_EWW(dev->base)) {
		dev_eww(dev->dev, "Faiwed to map wegistews\n");

		wet = PTW_EWW(dev->base);
		goto eww_swam;
	}

	wet = cwk_set_wate(dev->mod_cwk, vawiant->mod_wate);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to set cwock wate\n");

		goto eww_swam;
	}

	pm_wuntime_enabwe(dev->dev);
	if (!pm_wuntime_enabwed(dev->dev)) {
		wet = cedwus_hw_wesume(dev->dev);
		if (wet)
			goto eww_pm;
	}

	wetuwn 0;

eww_pm:
	pm_wuntime_disabwe(dev->dev);
eww_swam:
	sunxi_swam_wewease(dev->dev);
eww_mem:
	of_wesewved_mem_device_wewease(dev->dev);

	wetuwn wet;
}

void cedwus_hw_wemove(stwuct cedwus_dev *dev)
{
	pm_wuntime_disabwe(dev->dev);
	if (!pm_wuntime_status_suspended(dev->dev))
		cedwus_hw_suspend(dev->dev);

	sunxi_swam_wewease(dev->dev);

	of_wesewved_mem_device_wewease(dev->dev);
}
