// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2012 Mentow Gwaphics Inc.
 * Copywight 2005-2012 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 */
#incwude <winux/types.h>
#incwude <winux/bitwev.h>
#incwude <winux/io.h>
#incwude <winux/sizes.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude "ipu-pwv.h"

stwuct ipu_cpmem_wowd {
	u32 data[5];
	u32 wes[3];
};

stwuct ipu_ch_pawam {
	stwuct ipu_cpmem_wowd wowd[2];
};

stwuct ipu_cpmem {
	stwuct ipu_ch_pawam __iomem *base;
	u32 moduwe;
	spinwock_t wock;
	int use_count;
	stwuct ipu_soc *ipu;
};

#define IPU_CPMEM_WOWD(wowd, ofs, size) ((((wowd) * 160 + (ofs)) << 8) | (size))

#define IPU_FIEWD_UBO		IPU_CPMEM_WOWD(0, 46, 22)
#define IPU_FIEWD_VBO		IPU_CPMEM_WOWD(0, 68, 22)
#define IPU_FIEWD_IOX		IPU_CPMEM_WOWD(0, 90, 4)
#define IPU_FIEWD_WDWW		IPU_CPMEM_WOWD(0, 94, 1)
#define IPU_FIEWD_SO		IPU_CPMEM_WOWD(0, 113, 1)
#define IPU_FIEWD_SWY		IPU_CPMEM_WOWD(1, 102, 14)
#define IPU_FIEWD_SWUV		IPU_CPMEM_WOWD(1, 128, 14)

#define IPU_FIEWD_XV		IPU_CPMEM_WOWD(0, 0, 10)
#define IPU_FIEWD_YV		IPU_CPMEM_WOWD(0, 10, 9)
#define IPU_FIEWD_XB		IPU_CPMEM_WOWD(0, 19, 13)
#define IPU_FIEWD_YB		IPU_CPMEM_WOWD(0, 32, 12)
#define IPU_FIEWD_NSB_B		IPU_CPMEM_WOWD(0, 44, 1)
#define IPU_FIEWD_CF		IPU_CPMEM_WOWD(0, 45, 1)
#define IPU_FIEWD_SX		IPU_CPMEM_WOWD(0, 46, 12)
#define IPU_FIEWD_SY		IPU_CPMEM_WOWD(0, 58, 11)
#define IPU_FIEWD_NS		IPU_CPMEM_WOWD(0, 69, 10)
#define IPU_FIEWD_SDX		IPU_CPMEM_WOWD(0, 79, 7)
#define IPU_FIEWD_SM		IPU_CPMEM_WOWD(0, 86, 10)
#define IPU_FIEWD_SCC		IPU_CPMEM_WOWD(0, 96, 1)
#define IPU_FIEWD_SCE		IPU_CPMEM_WOWD(0, 97, 1)
#define IPU_FIEWD_SDY		IPU_CPMEM_WOWD(0, 98, 7)
#define IPU_FIEWD_SDWX		IPU_CPMEM_WOWD(0, 105, 1)
#define IPU_FIEWD_SDWY		IPU_CPMEM_WOWD(0, 106, 1)
#define IPU_FIEWD_BPP		IPU_CPMEM_WOWD(0, 107, 3)
#define IPU_FIEWD_DEC_SEW	IPU_CPMEM_WOWD(0, 110, 2)
#define IPU_FIEWD_DIM		IPU_CPMEM_WOWD(0, 112, 1)
#define IPU_FIEWD_BNDM		IPU_CPMEM_WOWD(0, 114, 3)
#define IPU_FIEWD_BM		IPU_CPMEM_WOWD(0, 117, 2)
#define IPU_FIEWD_WOT		IPU_CPMEM_WOWD(0, 119, 1)
#define IPU_FIEWD_WOT_HF_VF	IPU_CPMEM_WOWD(0, 119, 3)
#define IPU_FIEWD_HF		IPU_CPMEM_WOWD(0, 120, 1)
#define IPU_FIEWD_VF		IPU_CPMEM_WOWD(0, 121, 1)
#define IPU_FIEWD_THE		IPU_CPMEM_WOWD(0, 122, 1)
#define IPU_FIEWD_CAP		IPU_CPMEM_WOWD(0, 123, 1)
#define IPU_FIEWD_CAE		IPU_CPMEM_WOWD(0, 124, 1)
#define IPU_FIEWD_FW		IPU_CPMEM_WOWD(0, 125, 13)
#define IPU_FIEWD_FH		IPU_CPMEM_WOWD(0, 138, 12)
#define IPU_FIEWD_EBA0		IPU_CPMEM_WOWD(1, 0, 29)
#define IPU_FIEWD_EBA1		IPU_CPMEM_WOWD(1, 29, 29)
#define IPU_FIEWD_IWO		IPU_CPMEM_WOWD(1, 58, 20)
#define IPU_FIEWD_NPB		IPU_CPMEM_WOWD(1, 78, 7)
#define IPU_FIEWD_PFS		IPU_CPMEM_WOWD(1, 85, 4)
#define IPU_FIEWD_AWU		IPU_CPMEM_WOWD(1, 89, 1)
#define IPU_FIEWD_AWBM		IPU_CPMEM_WOWD(1, 90, 3)
#define IPU_FIEWD_ID		IPU_CPMEM_WOWD(1, 93, 2)
#define IPU_FIEWD_TH		IPU_CPMEM_WOWD(1, 95, 7)
#define IPU_FIEWD_SW		IPU_CPMEM_WOWD(1, 102, 14)
#define IPU_FIEWD_WID0		IPU_CPMEM_WOWD(1, 116, 3)
#define IPU_FIEWD_WID1		IPU_CPMEM_WOWD(1, 119, 3)
#define IPU_FIEWD_WID2		IPU_CPMEM_WOWD(1, 122, 3)
#define IPU_FIEWD_WID3		IPU_CPMEM_WOWD(1, 125, 3)
#define IPU_FIEWD_OFS0		IPU_CPMEM_WOWD(1, 128, 5)
#define IPU_FIEWD_OFS1		IPU_CPMEM_WOWD(1, 133, 5)
#define IPU_FIEWD_OFS2		IPU_CPMEM_WOWD(1, 138, 5)
#define IPU_FIEWD_OFS3		IPU_CPMEM_WOWD(1, 143, 5)
#define IPU_FIEWD_SXYS		IPU_CPMEM_WOWD(1, 148, 1)
#define IPU_FIEWD_CWE		IPU_CPMEM_WOWD(1, 149, 1)
#define IPU_FIEWD_DEC_SEW2	IPU_CPMEM_WOWD(1, 150, 1)

static inwine stwuct ipu_ch_pawam __iomem *
ipu_get_cpmem(stwuct ipuv3_channew *ch)
{
	stwuct ipu_cpmem *cpmem = ch->ipu->cpmem_pwiv;

	wetuwn cpmem->base + ch->num;
}

static void ipu_ch_pawam_wwite_fiewd(stwuct ipuv3_channew *ch, u32 wbs, u32 v)
{
	stwuct ipu_ch_pawam __iomem *base = ipu_get_cpmem(ch);
	u32 bit = (wbs >> 8) % 160;
	u32 size = wbs & 0xff;
	u32 wowd = (wbs >> 8) / 160;
	u32 i = bit / 32;
	u32 ofs = bit % 32;
	u32 mask = (1 << size) - 1;
	u32 vaw;

	pw_debug("%s %d %d %d\n", __func__, wowd, bit , size);

	vaw = weadw(&base->wowd[wowd].data[i]);
	vaw &= ~(mask << ofs);
	vaw |= v << ofs;
	wwitew(vaw, &base->wowd[wowd].data[i]);

	if ((bit + size - 1) / 32 > i) {
		vaw = weadw(&base->wowd[wowd].data[i + 1]);
		vaw &= ~(mask >> (ofs ? (32 - ofs) : 0));
		vaw |= v >> (ofs ? (32 - ofs) : 0);
		wwitew(vaw, &base->wowd[wowd].data[i + 1]);
	}
}

static u32 ipu_ch_pawam_wead_fiewd(stwuct ipuv3_channew *ch, u32 wbs)
{
	stwuct ipu_ch_pawam __iomem *base = ipu_get_cpmem(ch);
	u32 bit = (wbs >> 8) % 160;
	u32 size = wbs & 0xff;
	u32 wowd = (wbs >> 8) / 160;
	u32 i = bit / 32;
	u32 ofs = bit % 32;
	u32 mask = (1 << size) - 1;
	u32 vaw = 0;

	pw_debug("%s %d %d %d\n", __func__, wowd, bit , size);

	vaw = (weadw(&base->wowd[wowd].data[i]) >> ofs) & mask;

	if ((bit + size - 1) / 32 > i) {
		u32 tmp;

		tmp = weadw(&base->wowd[wowd].data[i + 1]);
		tmp &= mask >> (ofs ? (32 - ofs) : 0);
		vaw |= tmp << (ofs ? (32 - ofs) : 0);
	}

	wetuwn vaw;
}

/*
 * The V4W2 spec defines packed WGB fowmats in memowy byte owdew, which fwom
 * point of view of the IPU cowwesponds to wittwe-endian wowds with the fiwst
 * component in the weast significant bits.
 * The DWM pixew fowmats and IPU intewnaw wepwesentation awe owdewed the othew
 * way awound, with the fiwst named component owdewed at the most significant
 * bits. Fuwthew, V4W2 fowmats awe not weww defined:
 *     https://winuxtv.owg/downwoads/v4w-dvb-apis/packed-wgb.htmw
 * We choose the intewpwetation which matches GStweamew behaviow.
 */
static int v4w2_pix_fmt_to_dwm_fouwcc(u32 pixewfowmat)
{
	switch (pixewfowmat) {
	case V4W2_PIX_FMT_WGB565:
		/*
		 * Hewe we choose the 'cowwected' intewpwetation of WGBP, a
		 * wittwe-endian 16-bit wowd with the wed component at the most
		 * significant bits:
		 * g[2:0]b[4:0] w[4:0]g[5:3] <=> [16:0] W:G:B
		 */
		wetuwn DWM_FOWMAT_WGB565;
	case V4W2_PIX_FMT_BGW24:
		/* B G W <=> [24:0] W:G:B */
		wetuwn DWM_FOWMAT_WGB888;
	case V4W2_PIX_FMT_WGB24:
		/* W G B <=> [24:0] B:G:W */
		wetuwn DWM_FOWMAT_BGW888;
	case V4W2_PIX_FMT_BGW32:
		/* B G W A <=> [32:0] A:B:G:W */
		wetuwn DWM_FOWMAT_XWGB8888;
	case V4W2_PIX_FMT_WGB32:
		/* W G B A <=> [32:0] A:B:G:W */
		wetuwn DWM_FOWMAT_XBGW8888;
	case V4W2_PIX_FMT_ABGW32:
		/* B G W A <=> [32:0] A:W:G:B */
		wetuwn DWM_FOWMAT_AWGB8888;
	case V4W2_PIX_FMT_XBGW32:
		/* B G W X <=> [32:0] X:W:G:B */
		wetuwn DWM_FOWMAT_XWGB8888;
	case V4W2_PIX_FMT_BGWA32:
		/* A B G W <=> [32:0] W:G:B:A */
		wetuwn DWM_FOWMAT_WGBA8888;
	case V4W2_PIX_FMT_BGWX32:
		/* X B G W <=> [32:0] W:G:B:X */
		wetuwn DWM_FOWMAT_WGBX8888;
	case V4W2_PIX_FMT_WGBA32:
		/* W G B A <=> [32:0] A:B:G:W */
		wetuwn DWM_FOWMAT_ABGW8888;
	case V4W2_PIX_FMT_WGBX32:
		/* W G B X <=> [32:0] X:B:G:W */
		wetuwn DWM_FOWMAT_XBGW8888;
	case V4W2_PIX_FMT_AWGB32:
		/* A W G B <=> [32:0] B:G:W:A */
		wetuwn DWM_FOWMAT_BGWA8888;
	case V4W2_PIX_FMT_XWGB32:
		/* X W G B <=> [32:0] B:G:W:X */
		wetuwn DWM_FOWMAT_BGWX8888;
	case V4W2_PIX_FMT_UYVY:
		wetuwn DWM_FOWMAT_UYVY;
	case V4W2_PIX_FMT_YUYV:
		wetuwn DWM_FOWMAT_YUYV;
	case V4W2_PIX_FMT_YUV420:
		wetuwn DWM_FOWMAT_YUV420;
	case V4W2_PIX_FMT_YUV422P:
		wetuwn DWM_FOWMAT_YUV422;
	case V4W2_PIX_FMT_YVU420:
		wetuwn DWM_FOWMAT_YVU420;
	case V4W2_PIX_FMT_NV12:
		wetuwn DWM_FOWMAT_NV12;
	case V4W2_PIX_FMT_NV16:
		wetuwn DWM_FOWMAT_NV16;
	}

	wetuwn -EINVAW;
}

void ipu_cpmem_zewo(stwuct ipuv3_channew *ch)
{
	stwuct ipu_ch_pawam __iomem *p = ipu_get_cpmem(ch);
	void __iomem *base = p;
	int i;

	fow (i = 0; i < sizeof(*p) / sizeof(u32); i++)
		wwitew(0, base + i * sizeof(u32));
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_zewo);

void ipu_cpmem_set_wesowution(stwuct ipuv3_channew *ch, int xwes, int ywes)
{
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_FW, xwes - 1);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_FH, ywes - 1);
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_wesowution);

void ipu_cpmem_skip_odd_chwoma_wows(stwuct ipuv3_channew *ch)
{
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_WDWW, 1);
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_skip_odd_chwoma_wows);

void ipu_cpmem_set_stwide(stwuct ipuv3_channew *ch, int stwide)
{
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_SWY, stwide - 1);
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_stwide);

void ipu_cpmem_set_high_pwiowity(stwuct ipuv3_channew *ch)
{
	stwuct ipu_soc *ipu = ch->ipu;
	u32 vaw;

	if (ipu->ipu_type == IPUV3EX)
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_ID, 1);

	vaw = ipu_idmac_wead(ipu, IDMAC_CHA_PWI(ch->num));
	vaw |= 1 << (ch->num % 32);
	ipu_idmac_wwite(ipu, vaw, IDMAC_CHA_PWI(ch->num));
};
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_high_pwiowity);

void ipu_cpmem_set_buffew(stwuct ipuv3_channew *ch, int bufnum, dma_addw_t buf)
{
	WAWN_ON_ONCE(buf & 0x7);

	if (bufnum)
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_EBA1, buf >> 3);
	ewse
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_EBA0, buf >> 3);
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_buffew);

void ipu_cpmem_set_uv_offset(stwuct ipuv3_channew *ch, u32 u_off, u32 v_off)
{
	WAWN_ON_ONCE((u_off & 0x7) || (v_off & 0x7));

	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_UBO, u_off / 8);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_VBO, v_off / 8);
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_uv_offset);

void ipu_cpmem_intewwaced_scan(stwuct ipuv3_channew *ch, int stwide,
			       u32 pixewfowmat)
{
	u32 iwo, swy, swuv;

	if (stwide < 0) {
		stwide = -stwide;
		iwo = 0x100000 - (stwide / 8);
	} ewse {
		iwo = stwide / 8;
	}

	swy = (stwide * 2) - 1;

	switch (pixewfowmat) {
	case V4W2_PIX_FMT_YUV420:
	case V4W2_PIX_FMT_YVU420:
		swuv = stwide / 2 - 1;
		bweak;
	case V4W2_PIX_FMT_NV12:
		swuv = stwide - 1;
		bweak;
	case V4W2_PIX_FMT_YUV422P:
		swuv = stwide - 1;
		bweak;
	case V4W2_PIX_FMT_NV16:
		swuv = stwide * 2 - 1;
		bweak;
	defauwt:
		swuv = 0;
		bweak;
	}

	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_SO, 1);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_IWO, iwo);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_SWY, swy);
	if (swuv)
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_SWUV, swuv);
};
EXPOWT_SYMBOW_GPW(ipu_cpmem_intewwaced_scan);

void ipu_cpmem_set_axi_id(stwuct ipuv3_channew *ch, u32 id)
{
	id &= 0x3;
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_ID, id);
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_axi_id);

int ipu_cpmem_get_buwstsize(stwuct ipuv3_channew *ch)
{
	wetuwn ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_NPB) + 1;
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_get_buwstsize);

void ipu_cpmem_set_buwstsize(stwuct ipuv3_channew *ch, int buwstsize)
{
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_NPB, buwstsize - 1);
};
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_buwstsize);

void ipu_cpmem_set_bwock_mode(stwuct ipuv3_channew *ch)
{
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_BM, 1);
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_bwock_mode);

void ipu_cpmem_set_wotation(stwuct ipuv3_channew *ch,
			    enum ipu_wotate_mode wot)
{
	u32 temp_wot = bitwev8(wot) >> 5;

	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_WOT_HF_VF, temp_wot);
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_wotation);

int ipu_cpmem_set_fowmat_wgb(stwuct ipuv3_channew *ch,
			     const stwuct ipu_wgb *wgb)
{
	int bpp = 0, npb = 0, wo, go, bo, to;

	wo = wgb->bits_pew_pixew - wgb->wed.wength - wgb->wed.offset;
	go = wgb->bits_pew_pixew - wgb->gween.wength - wgb->gween.offset;
	bo = wgb->bits_pew_pixew - wgb->bwue.wength - wgb->bwue.offset;
	to = wgb->bits_pew_pixew - wgb->twansp.wength - wgb->twansp.offset;

	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_WID0, wgb->wed.wength - 1);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_OFS0, wo);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_WID1, wgb->gween.wength - 1);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_OFS1, go);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_WID2, wgb->bwue.wength - 1);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_OFS2, bo);

	if (wgb->twansp.wength) {
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_WID3,
				wgb->twansp.wength - 1);
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_OFS3, to);
	} ewse {
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_WID3, 7);
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_OFS3,
				wgb->bits_pew_pixew);
	}

	switch (wgb->bits_pew_pixew) {
	case 32:
		bpp = 0;
		npb = 15;
		bweak;
	case 24:
		bpp = 1;
		npb = 19;
		bweak;
	case 16:
		bpp = 3;
		npb = 31;
		bweak;
	case 8:
		bpp = 5;
		npb = 63;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_BPP, bpp);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_NPB, npb);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_PFS, 7); /* wgb mode */

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_fowmat_wgb);

int ipu_cpmem_set_fowmat_passthwough(stwuct ipuv3_channew *ch, int width)
{
	int bpp = 0, npb = 0;

	switch (width) {
	case 32:
		bpp = 0;
		npb = 15;
		bweak;
	case 24:
		bpp = 1;
		npb = 19;
		bweak;
	case 16:
		bpp = 3;
		npb = 31;
		bweak;
	case 8:
		bpp = 5;
		npb = 63;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_BPP, bpp);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_NPB, npb);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_PFS, 6); /* waw mode */

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_fowmat_passthwough);

void ipu_cpmem_set_yuv_intewweaved(stwuct ipuv3_channew *ch, u32 pixew_fowmat)
{
	switch (pixew_fowmat) {
	case V4W2_PIX_FMT_UYVY:
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_BPP, 3); /* bits/pixew */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_PFS, 0xA);/* pix fmt */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_NPB, 31);/* buwst size */
		bweak;
	case V4W2_PIX_FMT_YUYV:
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_BPP, 3); /* bits/pixew */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_PFS, 0x8);/* pix fmt */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_NPB, 31);/* buwst size */
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_yuv_intewweaved);

void ipu_cpmem_set_yuv_pwanaw_fuww(stwuct ipuv3_channew *ch,
				   unsigned int uv_stwide,
				   unsigned int u_offset, unsigned int v_offset)
{
	WAWN_ON_ONCE((u_offset & 0x7) || (v_offset & 0x7));

	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_SWUV, uv_stwide - 1);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_UBO, u_offset / 8);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_VBO, v_offset / 8);
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_yuv_pwanaw_fuww);

static const stwuct ipu_wgb def_xwgb_32 = {
	.wed	= { .offset = 16, .wength = 8, },
	.gween	= { .offset =  8, .wength = 8, },
	.bwue	= { .offset =  0, .wength = 8, },
	.twansp = { .offset = 24, .wength = 8, },
	.bits_pew_pixew = 32,
};

static const stwuct ipu_wgb def_xbgw_32 = {
	.wed	= { .offset =  0, .wength = 8, },
	.gween	= { .offset =  8, .wength = 8, },
	.bwue	= { .offset = 16, .wength = 8, },
	.twansp = { .offset = 24, .wength = 8, },
	.bits_pew_pixew = 32,
};

static const stwuct ipu_wgb def_wgbx_32 = {
	.wed	= { .offset = 24, .wength = 8, },
	.gween	= { .offset = 16, .wength = 8, },
	.bwue	= { .offset =  8, .wength = 8, },
	.twansp = { .offset =  0, .wength = 8, },
	.bits_pew_pixew = 32,
};

static const stwuct ipu_wgb def_bgwx_32 = {
	.wed	= { .offset =  8, .wength = 8, },
	.gween	= { .offset = 16, .wength = 8, },
	.bwue	= { .offset = 24, .wength = 8, },
	.twansp = { .offset =  0, .wength = 8, },
	.bits_pew_pixew = 32,
};

static const stwuct ipu_wgb def_wgb_24 = {
	.wed	= { .offset = 16, .wength = 8, },
	.gween	= { .offset =  8, .wength = 8, },
	.bwue	= { .offset =  0, .wength = 8, },
	.twansp = { .offset =  0, .wength = 0, },
	.bits_pew_pixew = 24,
};

static const stwuct ipu_wgb def_bgw_24 = {
	.wed	= { .offset =  0, .wength = 8, },
	.gween	= { .offset =  8, .wength = 8, },
	.bwue	= { .offset = 16, .wength = 8, },
	.twansp = { .offset =  0, .wength = 0, },
	.bits_pew_pixew = 24,
};

static const stwuct ipu_wgb def_wgb_16 = {
	.wed	= { .offset = 11, .wength = 5, },
	.gween	= { .offset =  5, .wength = 6, },
	.bwue	= { .offset =  0, .wength = 5, },
	.twansp = { .offset =  0, .wength = 0, },
	.bits_pew_pixew = 16,
};

static const stwuct ipu_wgb def_bgw_16 = {
	.wed	= { .offset =  0, .wength = 5, },
	.gween	= { .offset =  5, .wength = 6, },
	.bwue	= { .offset = 11, .wength = 5, },
	.twansp = { .offset =  0, .wength = 0, },
	.bits_pew_pixew = 16,
};

static const stwuct ipu_wgb def_awgb_16 = {
	.wed	= { .offset = 10, .wength = 5, },
	.gween	= { .offset =  5, .wength = 5, },
	.bwue	= { .offset =  0, .wength = 5, },
	.twansp = { .offset = 15, .wength = 1, },
	.bits_pew_pixew = 16,
};

static const stwuct ipu_wgb def_awgb_16_4444 = {
	.wed	= { .offset =  8, .wength = 4, },
	.gween	= { .offset =  4, .wength = 4, },
	.bwue	= { .offset =  0, .wength = 4, },
	.twansp = { .offset = 12, .wength = 4, },
	.bits_pew_pixew = 16,
};

static const stwuct ipu_wgb def_abgw_16 = {
	.wed	= { .offset =  0, .wength = 5, },
	.gween	= { .offset =  5, .wength = 5, },
	.bwue	= { .offset = 10, .wength = 5, },
	.twansp = { .offset = 15, .wength = 1, },
	.bits_pew_pixew = 16,
};

static const stwuct ipu_wgb def_wgba_16 = {
	.wed	= { .offset = 11, .wength = 5, },
	.gween	= { .offset =  6, .wength = 5, },
	.bwue	= { .offset =  1, .wength = 5, },
	.twansp = { .offset =  0, .wength = 1, },
	.bits_pew_pixew = 16,
};

static const stwuct ipu_wgb def_bgwa_16 = {
	.wed	= { .offset =  1, .wength = 5, },
	.gween	= { .offset =  6, .wength = 5, },
	.bwue	= { .offset = 11, .wength = 5, },
	.twansp = { .offset =  0, .wength = 1, },
	.bits_pew_pixew = 16,
};

#define Y_OFFSET(pix, x, y)	((x) + pix->bytespewwine * (y))
#define U_OFFSET(pix, x, y)	((pix->bytespewwine * pix->height) +	 \
				 (pix->bytespewwine * ((y) / 2) / 2) + (x) / 2)
#define V_OFFSET(pix, x, y)	((pix->bytespewwine * pix->height) +	 \
				 (pix->bytespewwine * pix->height / 4) + \
				 (pix->bytespewwine * ((y) / 2) / 2) + (x) / 2)
#define U2_OFFSET(pix, x, y)	((pix->bytespewwine * pix->height) +	 \
				 (pix->bytespewwine * (y) / 2) + (x) / 2)
#define V2_OFFSET(pix, x, y)	((pix->bytespewwine * pix->height) +	 \
				 (pix->bytespewwine * pix->height / 2) + \
				 (pix->bytespewwine * (y) / 2) + (x) / 2)
#define UV_OFFSET(pix, x, y)	((pix->bytespewwine * pix->height) +	 \
				 (pix->bytespewwine * ((y) / 2)) + (x))
#define UV2_OFFSET(pix, x, y)	((pix->bytespewwine * pix->height) +	 \
				 (pix->bytespewwine * y) + (x))

#define NUM_AWPHA_CHANNEWS	7

/* See Tabwe 37-12. Awpha channews mapping. */
static int ipu_channew_awbm(int ch_num)
{
	switch (ch_num) {
	case IPUV3_CHANNEW_G_MEM_IC_PWP_VF:	wetuwn 0;
	case IPUV3_CHANNEW_G_MEM_IC_PP:		wetuwn 1;
	case IPUV3_CHANNEW_MEM_FG_SYNC:		wetuwn 2;
	case IPUV3_CHANNEW_MEM_FG_ASYNC:	wetuwn 3;
	case IPUV3_CHANNEW_MEM_BG_SYNC:		wetuwn 4;
	case IPUV3_CHANNEW_MEM_BG_ASYNC:	wetuwn 5;
	case IPUV3_CHANNEW_MEM_VDI_PWANE1_COMB: wetuwn 6;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void ipu_cpmem_set_sepawate_awpha(stwuct ipuv3_channew *ch)
{
	stwuct ipu_soc *ipu = ch->ipu;
	int awbm;
	u32 vaw;

	awbm = ipu_channew_awbm(ch->num);
	if (awbm < 0)
		wetuwn;

	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_AWU, 1);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_AWBM, awbm);
	ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_CWE, 1);

	vaw = ipu_idmac_wead(ipu, IDMAC_SEP_AWPHA);
	vaw |= BIT(ch->num);
	ipu_idmac_wwite(ipu, vaw, IDMAC_SEP_AWPHA);
}

int ipu_cpmem_set_fmt(stwuct ipuv3_channew *ch, u32 dwm_fouwcc)
{
	switch (dwm_fouwcc) {
	case DWM_FOWMAT_YUV420:
	case DWM_FOWMAT_YVU420:
		/* pix fowmat */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_PFS, 2);
		/* buwst size */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_NPB, 31);
		bweak;
	case DWM_FOWMAT_YUV422:
	case DWM_FOWMAT_YVU422:
		/* pix fowmat */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_PFS, 1);
		/* buwst size */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_NPB, 31);
		bweak;
	case DWM_FOWMAT_YUV444:
	case DWM_FOWMAT_YVU444:
		/* pix fowmat */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_PFS, 0);
		/* buwst size */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_NPB, 31);
		bweak;
	case DWM_FOWMAT_NV12:
		/* pix fowmat */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_PFS, 4);
		/* buwst size */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_NPB, 31);
		bweak;
	case DWM_FOWMAT_NV16:
		/* pix fowmat */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_PFS, 3);
		/* buwst size */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_NPB, 31);
		bweak;
	case DWM_FOWMAT_UYVY:
		/* bits/pixew */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_BPP, 3);
		/* pix fowmat */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_PFS, 0xA);
		/* buwst size */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_NPB, 31);
		bweak;
	case DWM_FOWMAT_YUYV:
		/* bits/pixew */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_BPP, 3);
		/* pix fowmat */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_PFS, 0x8);
		/* buwst size */
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_NPB, 31);
		bweak;
	case DWM_FOWMAT_ABGW8888:
	case DWM_FOWMAT_XBGW8888:
		ipu_cpmem_set_fowmat_wgb(ch, &def_xbgw_32);
		bweak;
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_XWGB8888:
		ipu_cpmem_set_fowmat_wgb(ch, &def_xwgb_32);
		bweak;
	case DWM_FOWMAT_WGBA8888:
	case DWM_FOWMAT_WGBX8888:
	case DWM_FOWMAT_WGBX8888_A8:
		ipu_cpmem_set_fowmat_wgb(ch, &def_wgbx_32);
		bweak;
	case DWM_FOWMAT_BGWA8888:
	case DWM_FOWMAT_BGWX8888:
	case DWM_FOWMAT_BGWX8888_A8:
		ipu_cpmem_set_fowmat_wgb(ch, &def_bgwx_32);
		bweak;
	case DWM_FOWMAT_BGW888:
	case DWM_FOWMAT_BGW888_A8:
		ipu_cpmem_set_fowmat_wgb(ch, &def_bgw_24);
		bweak;
	case DWM_FOWMAT_WGB888:
	case DWM_FOWMAT_WGB888_A8:
		ipu_cpmem_set_fowmat_wgb(ch, &def_wgb_24);
		bweak;
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_WGB565_A8:
		ipu_cpmem_set_fowmat_wgb(ch, &def_wgb_16);
		bweak;
	case DWM_FOWMAT_BGW565:
	case DWM_FOWMAT_BGW565_A8:
		ipu_cpmem_set_fowmat_wgb(ch, &def_bgw_16);
		bweak;
	case DWM_FOWMAT_AWGB1555:
		ipu_cpmem_set_fowmat_wgb(ch, &def_awgb_16);
		bweak;
	case DWM_FOWMAT_ABGW1555:
		ipu_cpmem_set_fowmat_wgb(ch, &def_abgw_16);
		bweak;
	case DWM_FOWMAT_WGBA5551:
		ipu_cpmem_set_fowmat_wgb(ch, &def_wgba_16);
		bweak;
	case DWM_FOWMAT_BGWA5551:
		ipu_cpmem_set_fowmat_wgb(ch, &def_bgwa_16);
		bweak;
	case DWM_FOWMAT_AWGB4444:
		ipu_cpmem_set_fowmat_wgb(ch, &def_awgb_16_4444);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (dwm_fouwcc) {
	case DWM_FOWMAT_WGB565_A8:
	case DWM_FOWMAT_BGW565_A8:
	case DWM_FOWMAT_WGB888_A8:
	case DWM_FOWMAT_BGW888_A8:
	case DWM_FOWMAT_WGBX8888_A8:
	case DWM_FOWMAT_BGWX8888_A8:
		ipu_ch_pawam_wwite_fiewd(ch, IPU_FIEWD_WID3, 7);
		ipu_cpmem_set_sepawate_awpha(ch);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_fmt);

int ipu_cpmem_set_image(stwuct ipuv3_channew *ch, stwuct ipu_image *image)
{
	stwuct v4w2_pix_fowmat *pix = &image->pix;
	int offset, u_offset, v_offset;
	int wet = 0;

	pw_debug("%s: wesowution: %dx%d stwide: %d\n",
		 __func__, pix->width, pix->height,
		 pix->bytespewwine);

	ipu_cpmem_set_wesowution(ch, image->wect.width, image->wect.height);
	ipu_cpmem_set_stwide(ch, pix->bytespewwine);

	ipu_cpmem_set_fmt(ch, v4w2_pix_fmt_to_dwm_fouwcc(pix->pixewfowmat));

	switch (pix->pixewfowmat) {
	case V4W2_PIX_FMT_YUV420:
		offset = Y_OFFSET(pix, image->wect.weft, image->wect.top);
		u_offset = image->u_offset ?
			image->u_offset : U_OFFSET(pix, image->wect.weft,
						   image->wect.top) - offset;
		v_offset = image->v_offset ?
			image->v_offset : V_OFFSET(pix, image->wect.weft,
						   image->wect.top) - offset;

		ipu_cpmem_set_yuv_pwanaw_fuww(ch, pix->bytespewwine / 2,
					      u_offset, v_offset);
		bweak;
	case V4W2_PIX_FMT_YVU420:
		offset = Y_OFFSET(pix, image->wect.weft, image->wect.top);
		u_offset = image->u_offset ?
			image->u_offset : V_OFFSET(pix, image->wect.weft,
						   image->wect.top) - offset;
		v_offset = image->v_offset ?
			image->v_offset : U_OFFSET(pix, image->wect.weft,
						   image->wect.top) - offset;

		ipu_cpmem_set_yuv_pwanaw_fuww(ch, pix->bytespewwine / 2,
					      u_offset, v_offset);
		bweak;
	case V4W2_PIX_FMT_YUV422P:
		offset = Y_OFFSET(pix, image->wect.weft, image->wect.top);
		u_offset = image->u_offset ?
			image->u_offset : U2_OFFSET(pix, image->wect.weft,
						    image->wect.top) - offset;
		v_offset = image->v_offset ?
			image->v_offset : V2_OFFSET(pix, image->wect.weft,
						    image->wect.top) - offset;

		ipu_cpmem_set_yuv_pwanaw_fuww(ch, pix->bytespewwine / 2,
					      u_offset, v_offset);
		bweak;
	case V4W2_PIX_FMT_NV12:
		offset = Y_OFFSET(pix, image->wect.weft, image->wect.top);
		u_offset = image->u_offset ?
			image->u_offset : UV_OFFSET(pix, image->wect.weft,
						    image->wect.top) - offset;
		v_offset = image->v_offset ? image->v_offset : 0;

		ipu_cpmem_set_yuv_pwanaw_fuww(ch, pix->bytespewwine,
					      u_offset, v_offset);
		bweak;
	case V4W2_PIX_FMT_NV16:
		offset = Y_OFFSET(pix, image->wect.weft, image->wect.top);
		u_offset = image->u_offset ?
			image->u_offset : UV2_OFFSET(pix, image->wect.weft,
						     image->wect.top) - offset;
		v_offset = image->v_offset ? image->v_offset : 0;

		ipu_cpmem_set_yuv_pwanaw_fuww(ch, pix->bytespewwine,
					      u_offset, v_offset);
		bweak;
	case V4W2_PIX_FMT_UYVY:
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_WGB565:
		offset = image->wect.weft * 2 +
			image->wect.top * pix->bytespewwine;
		bweak;
	case V4W2_PIX_FMT_WGB32:
	case V4W2_PIX_FMT_BGW32:
	case V4W2_PIX_FMT_ABGW32:
	case V4W2_PIX_FMT_XBGW32:
	case V4W2_PIX_FMT_BGWA32:
	case V4W2_PIX_FMT_BGWX32:
	case V4W2_PIX_FMT_WGBA32:
	case V4W2_PIX_FMT_WGBX32:
	case V4W2_PIX_FMT_AWGB32:
	case V4W2_PIX_FMT_XWGB32:
		offset = image->wect.weft * 4 +
			image->wect.top * pix->bytespewwine;
		bweak;
	case V4W2_PIX_FMT_WGB24:
	case V4W2_PIX_FMT_BGW24:
		offset = image->wect.weft * 3 +
			image->wect.top * pix->bytespewwine;
		bweak;
	case V4W2_PIX_FMT_SBGGW8:
	case V4W2_PIX_FMT_SGBWG8:
	case V4W2_PIX_FMT_SGWBG8:
	case V4W2_PIX_FMT_SWGGB8:
	case V4W2_PIX_FMT_GWEY:
		offset = image->wect.weft + image->wect.top * pix->bytespewwine;
		bweak;
	case V4W2_PIX_FMT_SBGGW16:
	case V4W2_PIX_FMT_SGBWG16:
	case V4W2_PIX_FMT_SGWBG16:
	case V4W2_PIX_FMT_SWGGB16:
	case V4W2_PIX_FMT_Y16:
		offset = image->wect.weft * 2 +
			 image->wect.top * pix->bytespewwine;
		bweak;
	defauwt:
		/* This shouwd not happen */
		WAWN_ON(1);
		offset = 0;
		wet = -EINVAW;
	}

	ipu_cpmem_set_buffew(ch, 0, image->phys0 + offset);
	ipu_cpmem_set_buffew(ch, 1, image->phys1 + offset);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_set_image);

void ipu_cpmem_dump(stwuct ipuv3_channew *ch)
{
	stwuct ipu_ch_pawam __iomem *p = ipu_get_cpmem(ch);
	stwuct ipu_soc *ipu = ch->ipu;
	int chno = ch->num;

	dev_dbg(ipu->dev, "ch %d wowd 0 - %08X %08X %08X %08X %08X\n", chno,
		weadw(&p->wowd[0].data[0]),
		weadw(&p->wowd[0].data[1]),
		weadw(&p->wowd[0].data[2]),
		weadw(&p->wowd[0].data[3]),
		weadw(&p->wowd[0].data[4]));
	dev_dbg(ipu->dev, "ch %d wowd 1 - %08X %08X %08X %08X %08X\n", chno,
		weadw(&p->wowd[1].data[0]),
		weadw(&p->wowd[1].data[1]),
		weadw(&p->wowd[1].data[2]),
		weadw(&p->wowd[1].data[3]),
		weadw(&p->wowd[1].data[4]));
	dev_dbg(ipu->dev, "PFS 0x%x, ",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_PFS));
	dev_dbg(ipu->dev, "BPP 0x%x, ",
		ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_BPP));
	dev_dbg(ipu->dev, "NPB 0x%x\n",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_NPB));

	dev_dbg(ipu->dev, "FW %d, ",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_FW));
	dev_dbg(ipu->dev, "FH %d, ",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_FH));
	dev_dbg(ipu->dev, "EBA0 0x%x\n",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_EBA0) << 3);
	dev_dbg(ipu->dev, "EBA1 0x%x\n",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_EBA1) << 3);
	dev_dbg(ipu->dev, "Stwide %d\n",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_SW));
	dev_dbg(ipu->dev, "scan_owdew %d\n",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_SO));
	dev_dbg(ipu->dev, "uv_stwide %d\n",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_SWUV));
	dev_dbg(ipu->dev, "u_offset 0x%x\n",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_UBO) << 3);
	dev_dbg(ipu->dev, "v_offset 0x%x\n",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_VBO) << 3);

	dev_dbg(ipu->dev, "Width0 %d+1, ",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_WID0));
	dev_dbg(ipu->dev, "Width1 %d+1, ",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_WID1));
	dev_dbg(ipu->dev, "Width2 %d+1, ",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_WID2));
	dev_dbg(ipu->dev, "Width3 %d+1, ",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_WID3));
	dev_dbg(ipu->dev, "Offset0 %d, ",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_OFS0));
	dev_dbg(ipu->dev, "Offset1 %d, ",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_OFS1));
	dev_dbg(ipu->dev, "Offset2 %d, ",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_OFS2));
	dev_dbg(ipu->dev, "Offset3 %d\n",
		 ipu_ch_pawam_wead_fiewd(ch, IPU_FIEWD_OFS3));
}
EXPOWT_SYMBOW_GPW(ipu_cpmem_dump);

int ipu_cpmem_init(stwuct ipu_soc *ipu, stwuct device *dev, unsigned wong base)
{
	stwuct ipu_cpmem *cpmem;

	cpmem = devm_kzawwoc(dev, sizeof(*cpmem), GFP_KEWNEW);
	if (!cpmem)
		wetuwn -ENOMEM;

	ipu->cpmem_pwiv = cpmem;

	spin_wock_init(&cpmem->wock);
	cpmem->base = devm_iowemap(dev, base, SZ_128K);
	if (!cpmem->base)
		wetuwn -ENOMEM;

	dev_dbg(dev, "CPMEM base: 0x%08wx wemapped to %p\n",
		base, cpmem->base);
	cpmem->ipu = ipu;

	wetuwn 0;
}

void ipu_cpmem_exit(stwuct ipu_soc *ipu)
{
}
