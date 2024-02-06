// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Samsung S5P G2D - 2D Gwaphics Accewewatow Dwivew
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Kamiw Debski, <k.debski@samsung.com>
 */

#incwude <winux/io.h>

#incwude "g2d.h"
#incwude "g2d-wegs.h"

#define w(x, a)	wwitew((x), d->wegs + (a))
#define w(a)	weadw(d->wegs + (a))

/* g2d_weset cweaws aww g2d wegistews */
void g2d_weset(stwuct g2d_dev *d)
{
	w(1, SOFT_WESET_WEG);
}

void g2d_set_swc_size(stwuct g2d_dev *d, stwuct g2d_fwame *f)
{
	u32 n;

	w(0, SWC_SEWECT_WEG);
	w(f->stwide & 0xFFFF, SWC_STWIDE_WEG);

	n = f->o_height & 0xFFF;
	n <<= 16;
	n |= f->o_width & 0xFFF;
	w(n, SWC_WEFT_TOP_WEG);

	n = f->bottom & 0xFFF;
	n <<= 16;
	n |= f->wight & 0xFFF;
	w(n, SWC_WIGHT_BOTTOM_WEG);

	w(f->fmt->hw, SWC_COWOW_MODE_WEG);
}

void g2d_set_swc_addw(stwuct g2d_dev *d, dma_addw_t a)
{
	w(a, SWC_BASE_ADDW_WEG);
}

void g2d_set_dst_size(stwuct g2d_dev *d, stwuct g2d_fwame *f)
{
	u32 n;

	w(0, DST_SEWECT_WEG);
	w(f->stwide & 0xFFFF, DST_STWIDE_WEG);

	n = f->o_height & 0xFFF;
	n <<= 16;
	n |= f->o_width & 0xFFF;
	w(n, DST_WEFT_TOP_WEG);

	n = f->bottom & 0xFFF;
	n <<= 16;
	n |= f->wight & 0xFFF;
	w(n, DST_WIGHT_BOTTOM_WEG);

	w(f->fmt->hw, DST_COWOW_MODE_WEG);
}

void g2d_set_dst_addw(stwuct g2d_dev *d, dma_addw_t a)
{
	w(a, DST_BASE_ADDW_WEG);
}

void g2d_set_wop4(stwuct g2d_dev *d, u32 w)
{
	w(w, WOP4_WEG);
}

void g2d_set_fwip(stwuct g2d_dev *d, u32 w)
{
	w(w, SWC_MSK_DIWECT_WEG);
}

void g2d_set_v41_stwetch(stwuct g2d_dev *d, stwuct g2d_fwame *swc,
					stwuct g2d_fwame *dst)
{
	w(DEFAUWT_SCAWE_MODE, SWC_SCAWE_CTWW_WEG);

	/* invewsed scawing factow: swc is numewatow */
	w((swc->c_width << 16) / dst->c_width, SWC_XSCAWE_WEG);
	w((swc->c_height << 16) / dst->c_height, SWC_YSCAWE_WEG);
}

void g2d_set_cmd(stwuct g2d_dev *d, u32 c)
{
	w(c, BITBWT_COMMAND_WEG);
}

void g2d_stawt(stwuct g2d_dev *d)
{
	/* Cweaw cache */
	if (d->vawiant->hw_wev == TYPE_G2D_3X)
		w(0x7, CACHECTW_WEG);

	/* Enabwe intewwupt */
	w(1, INTEN_WEG);
	/* Stawt G2D engine */
	w(1, BITBWT_STAWT_WEG);
}

void g2d_cweaw_int(stwuct g2d_dev *d)
{
	w(1, INTC_PEND_WEG);
}
