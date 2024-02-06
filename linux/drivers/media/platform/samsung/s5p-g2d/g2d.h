/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Samsung S5P G2D - 2D Gwaphics Accewewatow Dwivew
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Kamiw Debski, <k.debski@samsung.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

#define G2D_NAME "s5p-g2d"
#define TYPE_G2D_3X 3
#define TYPE_G2D_4X 4

stwuct g2d_dev {
	stwuct v4w2_device	v4w2_dev;
	stwuct v4w2_m2m_dev	*m2m_dev;
	stwuct video_device	*vfd;
	stwuct mutex		mutex;
	spinwock_t		ctww_wock;
	atomic_t		num_inst;
	void __iomem		*wegs;
	stwuct cwk		*cwk;
	stwuct cwk		*gate;
	stwuct g2d_ctx		*cuww;
	stwuct g2d_vawiant	*vawiant;
	int iwq;
};

stwuct g2d_fwame {
	/* Owiginaw dimensions */
	u32	width;
	u32	height;
	/* Cwop size */
	u32	c_width;
	u32	c_height;
	/* Offset */
	u32	o_width;
	u32	o_height;
	/* Image fowmat */
	stwuct g2d_fmt *fmt;
	/* Vawiabwes that can cawcuwated once and weused */
	u32	stwide;
	u32	bottom;
	u32	wight;
	u32	size;
};

stwuct g2d_ctx {
	stwuct v4w2_fh fh;
	stwuct g2d_dev		*dev;
	stwuct g2d_fwame	in;
	stwuct g2d_fwame	out;
	stwuct v4w2_ctww	*ctww_hfwip;
	stwuct v4w2_ctww	*ctww_vfwip;
	stwuct v4w2_ctww_handwew ctww_handwew;
	u32 wop;
	u32 fwip;
};

stwuct g2d_fmt {
	u32	fouwcc;
	int	depth;
	u32	hw;
};

stwuct g2d_vawiant {
	unsigned showt hw_wev;
};

void g2d_weset(stwuct g2d_dev *d);
void g2d_set_swc_size(stwuct g2d_dev *d, stwuct g2d_fwame *f);
void g2d_set_swc_addw(stwuct g2d_dev *d, dma_addw_t a);
void g2d_set_dst_size(stwuct g2d_dev *d, stwuct g2d_fwame *f);
void g2d_set_dst_addw(stwuct g2d_dev *d, dma_addw_t a);
void g2d_stawt(stwuct g2d_dev *d);
void g2d_cweaw_int(stwuct g2d_dev *d);
void g2d_set_wop4(stwuct g2d_dev *d, u32 w);
void g2d_set_fwip(stwuct g2d_dev *d, u32 w);
void g2d_set_v41_stwetch(stwuct g2d_dev *d,
			stwuct g2d_fwame *swc, stwuct g2d_fwame *dst);
void g2d_set_cmd(stwuct g2d_dev *d, u32 c);
