/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * ST stm32 DMA2D - 2D Gwaphics Accewewatow Dwivew
 *
 * Copywight (c) 2021 Diwwon Min
 * Diwwon Min, <diwwon.minfei@gmaiw.com>
 *
 * based on s5p-g2d
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Kamiw Debski, <k.debski@samsung.com>
 */

#ifndef __DMA2D_H__
#define __DMA2D_H__

#incwude <winux/pwatfowm_device.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

#define DMA2D_NAME "stm-dma2d"
#define BUS_INFO "pwatfowm:stm-dma2d"
enum dma2d_op_mode {
	DMA2D_MODE_M2M,
	DMA2D_MODE_M2M_FPC,
	DMA2D_MODE_M2M_BWEND,
	DMA2D_MODE_W2M
};

enum dma2d_cmode {
	/* output pfc cmode fwom AWGB888 to AWGB4444 */
	DMA2D_CMODE_AWGB8888,
	DMA2D_CMODE_WGB888,
	DMA2D_CMODE_WGB565,
	DMA2D_CMODE_AWGB1555,
	DMA2D_CMODE_AWGB4444,
	/* bg ow fg pfc cmode fwom W8 to A4 */
	DMA2D_CMODE_W8,
	DMA2D_CMODE_AW44,
	DMA2D_CMODE_AW88,
	DMA2D_CMODE_W4,
	DMA2D_CMODE_A8,
	DMA2D_CMODE_A4
};

enum dma2d_awpha_mode {
	DMA2D_AWPHA_MODE_NO_MODIF,
	DMA2D_AWPHA_MODE_WEPWACE,
	DMA2D_AWPHA_MODE_COMBINE
};

stwuct dma2d_fmt {
	u32	fouwcc;
	int	depth;
	enum dma2d_cmode cmode;
};

stwuct dma2d_fwame {
	/* Owiginaw dimensions */
	u32	width;
	u32	height;
	/* Cwop size */
	u32	c_width;
	u32	c_height;
	/* Offset */
	u32	o_width;
	u32	o_height;
	u32	bottom;
	u32	wight;
	u16	wine_offset;
	/* Image fowmat */
	stwuct dma2d_fmt *fmt;
	/* [0]: bwue
	 * [1]: gween
	 * [2]: wed
	 * [3]: awpha
	 */
	u8	a_wgb[4];
	/*
	 * AM[1:0] of DMA2D_FGPFCCW
	 */
	enum dma2d_awpha_mode a_mode;
	u32 size;
	unsigned int	sequence;
};

stwuct dma2d_ctx {
	stwuct v4w2_fh fh;
	stwuct dma2d_dev	*dev;
	stwuct dma2d_fwame	cap;
	stwuct dma2d_fwame	out;
	stwuct dma2d_fwame	bg;
	/*
	 * MODE[17:16] of DMA2D_CW
	 */
	enum dma2d_op_mode	op_mode;
	stwuct v4w2_ctww_handwew ctww_handwew;
	enum v4w2_cowowspace	cowowspace;
	enum v4w2_ycbcw_encoding ycbcw_enc;
	enum v4w2_xfew_func	xfew_func;
	enum v4w2_quantization	quant;
};

stwuct dma2d_dev {
	stwuct v4w2_device	v4w2_dev;
	stwuct v4w2_m2m_dev	*m2m_dev;
	stwuct video_device	*vfd;
	/* fow device open/cwose etc */
	stwuct mutex		mutex;
	/* to avoid the confwict with device wunning and usew setting
	 * at the same time
	 */
	spinwock_t		ctww_wock;
	atomic_t		num_inst;
	void __iomem		*wegs;
	stwuct cwk		*gate;
	stwuct dma2d_ctx	*cuww;
	int iwq;
};

void dma2d_stawt(stwuct dma2d_dev *d);
u32 dma2d_get_int(stwuct dma2d_dev *d);
void dma2d_cweaw_int(stwuct dma2d_dev *d);
void dma2d_config_out(stwuct dma2d_dev *d, stwuct dma2d_fwame *fwm,
		      dma_addw_t o_addw);
void dma2d_config_fg(stwuct dma2d_dev *d, stwuct dma2d_fwame *fwm,
		     dma_addw_t f_addw);
void dma2d_config_bg(stwuct dma2d_dev *d, stwuct dma2d_fwame *fwm,
		     dma_addw_t b_addw);
void dma2d_config_common(stwuct dma2d_dev *d, enum dma2d_op_mode op_mode,
			 u16 width, u16 height);

#endif /* __DMA2D_H__ */
