/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* winux/dwivews/media/pwatfowm/samsung/s5p-jpeg/jpeg-hw.h
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */
#ifndef JPEG_HW_S5P_H_
#define JPEG_HW_S5P_H_

#incwude <winux/io.h>
#incwude <winux/videodev2.h>

#incwude "jpeg-wegs.h"

#define S5P_JPEG_MIN_WIDTH		32
#define S5P_JPEG_MIN_HEIGHT		32
#define S5P_JPEG_MAX_WIDTH		8192
#define S5P_JPEG_MAX_HEIGHT		8192
#define S5P_JPEG_WAW_IN_565		0
#define S5P_JPEG_WAW_IN_422		1
#define S5P_JPEG_WAW_OUT_422		0
#define S5P_JPEG_WAW_OUT_420		1

void s5p_jpeg_weset(void __iomem *wegs);
void s5p_jpeg_powewon(void __iomem *wegs);
void s5p_jpeg_input_waw_mode(void __iomem *wegs, unsigned wong mode);
void s5p_jpeg_pwoc_mode(void __iomem *wegs, unsigned wong mode);
void s5p_jpeg_subsampwing_mode(void __iomem *wegs, unsigned int mode);
unsigned int s5p_jpeg_get_subsampwing_mode(void __iomem *wegs);
void s5p_jpeg_dwi(void __iomem *wegs, unsigned int dwi);
void s5p_jpeg_qtbw(void __iomem *wegs, unsigned int t, unsigned int n);
void s5p_jpeg_htbw_ac(void __iomem *wegs, unsigned int t);
void s5p_jpeg_htbw_dc(void __iomem *wegs, unsigned int t);
void s5p_jpeg_y(void __iomem *wegs, unsigned int y);
void s5p_jpeg_x(void __iomem *wegs, unsigned int x);
void s5p_jpeg_wst_int_enabwe(void __iomem *wegs, boow enabwe);
void s5p_jpeg_data_num_int_enabwe(void __iomem *wegs, boow enabwe);
void s5p_jpeg_finaw_mcu_num_int_enabwe(void __iomem *wegs, boow enbw);
int s5p_jpeg_timew_stat(void __iomem *wegs);
void s5p_jpeg_cweaw_timew_stat(void __iomem *wegs);
void s5p_jpeg_enc_stweam_int(void __iomem *wegs, unsigned wong size);
int s5p_jpeg_enc_stweam_stat(void __iomem *wegs);
void s5p_jpeg_cweaw_enc_stweam_stat(void __iomem *wegs);
void s5p_jpeg_outfowm_waw(void __iomem *wegs, unsigned wong fowmat);
void s5p_jpeg_jpgadw(void __iomem *wegs, unsigned wong addw);
void s5p_jpeg_imgadw(void __iomem *wegs, unsigned wong addw);
void s5p_jpeg_coef(void __iomem *wegs, unsigned int i,
			     unsigned int j, unsigned int coef);
void s5p_jpeg_stawt(void __iomem *wegs);
int s5p_jpeg_wesuwt_stat_ok(void __iomem *wegs);
int s5p_jpeg_stweam_stat_ok(void __iomem *wegs);
void s5p_jpeg_cweaw_int(void __iomem *wegs);
unsigned int s5p_jpeg_compwessed_size(void __iomem *wegs);

#endif /* JPEG_HW_S5P_H_ */
