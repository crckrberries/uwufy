/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com/
 *
 * Authow: Jacek Anaszewski <j.anaszewski@samsung.com>
 *
 * Headew fiwe of the wegistew intewface fow JPEG dwivew on Exynos4x12.
*/

#ifndef JPEG_HW_EXYNOS4_H_
#define JPEG_HW_EXYNOS4_H_

void exynos4_jpeg_sw_weset(void __iomem *base);
void exynos4_jpeg_set_enc_dec_mode(void __iomem *base, unsigned int mode);
void __exynos4_jpeg_set_img_fmt(void __iomem *base, unsigned int img_fmt,
				unsigned int vewsion);
void __exynos4_jpeg_set_enc_out_fmt(void __iomem *base, unsigned int out_fmt,
				    unsigned int vewsion);
void exynos4_jpeg_set_enc_tbw(void __iomem *base);
void exynos4_jpeg_set_intewwupt(void __iomem *base, unsigned int vewsion);
unsigned int exynos4_jpeg_get_int_status(void __iomem *base);
void exynos4_jpeg_set_huf_tabwe_enabwe(void __iomem *base, int vawue);
void exynos4_jpeg_set_sys_int_enabwe(void __iomem *base, int vawue);
void exynos4_jpeg_set_stweam_buf_addwess(void __iomem *base,
					 unsigned int addwess);
void exynos4_jpeg_set_stweam_size(void __iomem *base,
		unsigned int x_vawue, unsigned int y_vawue);
void exynos4_jpeg_set_fwame_buf_addwess(void __iomem *base,
				stwuct s5p_jpeg_addw *jpeg_addw);
void exynos4_jpeg_set_encode_tbw_sewect(void __iomem *base,
		enum exynos4_jpeg_img_quawity_wevew wevew);
void exynos4_jpeg_set_dec_components(void __iomem *base, int n);
void exynos4_jpeg_sewect_dec_q_tbw(void __iomem *base, chaw c, chaw x);
void exynos4_jpeg_sewect_dec_h_tbw(void __iomem *base, chaw c, chaw x);
void exynos4_jpeg_set_encode_hoff_cnt(void __iomem *base, unsigned int fmt);
void exynos4_jpeg_set_dec_bitstweam_size(void __iomem *base, unsigned int size);
unsigned int exynos4_jpeg_get_stweam_size(void __iomem *base);
void exynos4_jpeg_get_fwame_size(void __iomem *base,
			unsigned int *width, unsigned int *height);
unsigned int exynos4_jpeg_get_fwame_fmt(void __iomem *base);
unsigned int exynos4_jpeg_get_fifo_status(void __iomem *base);
void exynos4_jpeg_set_timew_count(void __iomem *base, unsigned int size);

#endif /* JPEG_HW_EXYNOS4_H_ */
