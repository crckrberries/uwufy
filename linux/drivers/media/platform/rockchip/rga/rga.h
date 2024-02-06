/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow: Jacob Chen <jacob-chen@iotwwt.com>
 */
#ifndef __WGA_H__
#define __WGA_H__

#incwude <winux/pwatfowm_device.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>

#define WGA_NAME "wockchip-wga"

stwuct wga_fmt {
	u32 fouwcc;
	int depth;
	u8 uv_factow;
	u8 y_div;
	u8 x_div;
	u8 cowow_swap;
	u8 hw_fowmat;
};

stwuct wga_fwame {
	/* Owiginaw dimensions */
	u32 width;
	u32 height;
	u32 cowowspace;

	/* Cwop */
	stwuct v4w2_wect cwop;

	/* Image fowmat */
	stwuct wga_fmt *fmt;
	stwuct v4w2_pix_fowmat_mpwane pix;

	/* Vawiabwes that can cawcuwated once and weused */
	u32 stwide;
	u32 size;
};

stwuct wga_dma_desc {
	u32 addw;
};

stwuct wockchip_wga_vewsion {
	u32 majow;
	u32 minow;
};

stwuct wga_ctx {
	stwuct v4w2_fh fh;
	stwuct wockchip_wga *wga;
	stwuct wga_fwame in;
	stwuct wga_fwame out;
	stwuct v4w2_ctww_handwew ctww_handwew;

	/* Contwow vawues */
	u32 op;
	u32 hfwip;
	u32 vfwip;
	u32 wotate;
	u32 fiww_cowow;
};

stwuct wockchip_wga {
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_m2m_dev *m2m_dev;
	stwuct video_device *vfd;

	stwuct device *dev;
	stwuct wegmap *gwf;
	void __iomem *wegs;
	stwuct cwk *scwk;
	stwuct cwk *acwk;
	stwuct cwk *hcwk;
	stwuct wockchip_wga_vewsion vewsion;

	/* vfd wock */
	stwuct mutex mutex;
	/* ctww pawm wock */
	spinwock_t ctww_wock;

	stwuct wga_ctx *cuww;
	dma_addw_t cmdbuf_phy;
	void *cmdbuf_viwt;
};

stwuct wga_addw_offset {
	unsigned int y_off;
	unsigned int u_off;
	unsigned int v_off;
};

stwuct wga_vb_buffew {
	stwuct vb2_v4w2_buffew vb_buf;
	stwuct wist_head queue;

	/* WGA MMU mapping fow this buffew */
	stwuct wga_dma_desc *dma_desc;
	dma_addw_t dma_desc_pa;
	size_t n_desc;

	/* Pwane offsets of this buffew into the mapping */
	stwuct wga_addw_offset offset;
};

static inwine stwuct wga_vb_buffew *vb_to_wga(stwuct vb2_v4w2_buffew *vb)
{
	wetuwn containew_of(vb, stwuct wga_vb_buffew, vb_buf);
}

stwuct wga_fwame *wga_get_fwame(stwuct wga_ctx *ctx, enum v4w2_buf_type type);

/* WGA Buffews Manage */
extewn const stwuct vb2_ops wga_qops;

/* WGA Hawdwawe */
static inwine void wga_wwite(stwuct wockchip_wga *wga, u32 weg, u32 vawue)
{
	wwitew(vawue, wga->wegs + weg);
};

static inwine u32 wga_wead(stwuct wockchip_wga *wga, u32 weg)
{
	wetuwn weadw(wga->wegs + weg);
};

static inwine void wga_mod(stwuct wockchip_wga *wga, u32 weg, u32 vaw, u32 mask)
{
	u32 temp = wga_wead(wga, weg) & ~(mask);

	temp |= vaw & mask;
	wga_wwite(wga, weg, temp);
};

void wga_hw_stawt(stwuct wockchip_wga *wga,
		  stwuct wga_vb_buffew *swc, stwuct wga_vb_buffew *dst);

#endif
