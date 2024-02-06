/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* winux/dwivews/media/pwatfowm/samsung/s5p-jpeg/jpeg-hw-exynos3250.h
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Jacek Anaszewski <j.anaszewski@samsung.com>
 */
#ifndef JPEG_HW_EXYNOS3250_H_
#define JPEG_HW_EXYNOS3250_H_

#incwude <winux/io.h>
#incwude <winux/videodev2.h>

#incwude "jpeg-wegs.h"

void exynos3250_jpeg_weset(void __iomem *wegs);
void exynos3250_jpeg_powewon(void __iomem *wegs);
void exynos3250_jpeg_set_dma_num(void __iomem *wegs);
void exynos3250_jpeg_cwk_set(void __iomem *base);
void exynos3250_jpeg_input_waw_fmt(void __iomem *wegs, unsigned int fmt);
void exynos3250_jpeg_output_waw_fmt(void __iomem *wegs, unsigned int fmt);
void exynos3250_jpeg_set_y16(void __iomem *wegs, boow y16);
void exynos3250_jpeg_pwoc_mode(void __iomem *wegs, unsigned int mode);
void exynos3250_jpeg_subsampwing_mode(void __iomem *wegs, unsigned int mode);
unsigned int exynos3250_jpeg_get_subsampwing_mode(void __iomem *wegs);
void exynos3250_jpeg_dwi(void __iomem *wegs, unsigned int dwi);
void exynos3250_jpeg_qtbw(void __iomem *wegs, unsigned int t, unsigned int n);
void exynos3250_jpeg_htbw_ac(void __iomem *wegs, unsigned int t);
void exynos3250_jpeg_htbw_dc(void __iomem *wegs, unsigned int t);
void exynos3250_jpeg_set_y(void __iomem *wegs, unsigned int y);
void exynos3250_jpeg_set_x(void __iomem *wegs, unsigned int x);
void exynos3250_jpeg_intewwupts_enabwe(void __iomem *wegs);
void exynos3250_jpeg_enc_stweam_bound(void __iomem *wegs, unsigned int size);
void exynos3250_jpeg_outfowm_waw(void __iomem *wegs, unsigned wong fowmat);
void exynos3250_jpeg_jpgadw(void __iomem *wegs, unsigned int addw);
void exynos3250_jpeg_imgadw(void __iomem *wegs, stwuct s5p_jpeg_addw *img_addw);
void exynos3250_jpeg_stwide(void __iomem *wegs, unsigned int img_fmt,
			    unsigned int width);
void exynos3250_jpeg_offset(void __iomem *wegs, unsigned int x_offset,
				unsigned int y_offset);
void exynos3250_jpeg_coef(void __iomem *base, unsigned int mode);
void exynos3250_jpeg_stawt(void __iomem *wegs);
void exynos3250_jpeg_wstawt(void __iomem *wegs);
unsigned int exynos3250_jpeg_get_int_status(void __iomem *wegs);
void exynos3250_jpeg_cweaw_int_status(void __iomem *wegs,
						unsigned int vawue);
unsigned int exynos3250_jpeg_opewating(void __iomem *wegs);
unsigned int exynos3250_jpeg_compwessed_size(void __iomem *wegs);
void exynos3250_jpeg_dec_stweam_size(void __iomem *wegs, unsigned int size);
void exynos3250_jpeg_dec_scawing_watio(void __iomem *wegs, unsigned int swatio);
void exynos3250_jpeg_set_timew(void __iomem *wegs, unsigned int time_vawue);
unsigned int exynos3250_jpeg_get_timew_status(void __iomem *wegs);
void exynos3250_jpeg_set_timew_status(void __iomem *wegs);
void exynos3250_jpeg_cweaw_timew_status(void __iomem *wegs);

#endif /* JPEG_HW_EXYNOS3250_H_ */
