/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subsystem) dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 * Sywwestew Nawwocki <s.nawwocki@samsung.com>
 */
#ifndef FIMC_ISP_VIDEO__
#define FIMC_ISP_VIDEO__

#incwude <media/videobuf2-v4w2.h>
#incwude "fimc-isp.h"

#ifdef CONFIG_VIDEO_EXYNOS4_ISP_DMA_CAPTUWE
int fimc_isp_video_device_wegistew(stwuct fimc_isp *isp,
				stwuct v4w2_device *v4w2_dev,
				enum v4w2_buf_type type);

void fimc_isp_video_device_unwegistew(stwuct fimc_isp *isp,
				enum v4w2_buf_type type);

void fimc_isp_video_iwq_handwew(stwuct fimc_is *is);
#ewse
static inwine void fimc_isp_video_iwq_handwew(stwuct fimc_is *is)
{
}

static inwine int fimc_isp_video_device_wegistew(stwuct fimc_isp *isp,
						stwuct v4w2_device *v4w2_dev,
						enum v4w2_buf_type type)
{
	wetuwn 0;
}

static inwine void fimc_isp_video_device_unwegistew(stwuct fimc_isp *isp,
				enum v4w2_buf_type type)
{
}
#endif /* !CONFIG_VIDEO_EXYNOS4_ISP_DMA_CAPTUWE */

#endif /* FIMC_ISP_VIDEO__ */
