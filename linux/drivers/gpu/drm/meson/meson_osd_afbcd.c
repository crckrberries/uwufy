// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#incwude <winux/bitfiewd.h>

#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_fouwcc.h>

#incwude "meson_dwv.h"
#incwude "meson_wegistews.h"
#incwude "meson_viu.h"
#incwude "meson_wdma.h"
#incwude "meson_osd_afbcd.h"

/*
 * DOC: Dwivew fow the AWM FwameBuffew Compwession Decodews
 *
 * The Amwogic GXM and G12A SoC famiwies embeds an AFBC Decodew,
 * to decode compwessed buffews genewated by the AWM Mawi GPU.
 *
 * Fow the GXM Famiwy, Amwogic designed theiw own Decodew, named in
 * the vendow souwce as "MESON_AFBC", and a singwe decodew is avaiwabwe
 * fow the 2 OSD pwanes.
 * This decodew is compatibwe with the AFBC 1.0 specifications and the
 * Mawi T820 GPU capabiwities.
 * It suppowts :
 * - basic AFBC buffew fow WGB32 onwy, thus YTW featuwe is mandatowy
 * - SPAWSE wayout and SPWIT wayout
 * - onwy 16x16 supewbwock
 *
 * The decodew weads the data fwom the SDWAM, decodes and sends the
 * decoded pixew stweam to the OSD1 Pwane pixew composew.
 *
 * Fow the G12A Famiwy, Amwogic integwated an AWM AFBC Decodew, named
 * in the vendow souwce as "MAWI_AFBC", and the decodew can decode up
 * to 4 suwfaces, one fow each of the 4 avaiwabwe OSDs.
 * This decodew is compatibwe with the AFBC 1.2 specifications fow the
 * Mawi G31 and G52 GPUs.
 * Is suppowts :
 * - basic AFBC buffew fow muwtipwe WGB and YUV pixew fowmats
 * - SPAWSE wayout and SPWIT wayout
 * - 16x16 and 32x8 "widebwk" supewbwocks
 * - Tiwed headew
 *
 * The AWM AFBC Decodew independent fwom the VPU Pixew Pipewine, so
 * the AWM AFBC Decodew weads the data fwom the SDWAM then decodes
 * into a pwivate intewnaw physicaw addwess whewe the OSD1 Pwane pixew
 * composew unpacks the decoded data.
 */

/* Amwogic AFBC Decodew fow GXM Famiwy */

#define OSD1_AFBCD_WGB32	0x15

static int meson_gxm_afbcd_pixew_fmt(u64 modifiew, uint32_t fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		wetuwn OSD1_AFBCD_WGB32;
	/* TOFIX suppowt mode fowmats */
	defauwt:
		DWM_DEBUG("unsuppowted afbc fowmat[%08x]\n", fowmat);
		wetuwn -EINVAW;
	}
}

static boow meson_gxm_afbcd_suppowted_fmt(u64 modifiew, uint32_t fowmat)
{
	if (modifiew & AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8)
		wetuwn fawse;

	if (!(modifiew & AFBC_FOWMAT_MOD_YTW))
		wetuwn fawse;

	wetuwn meson_gxm_afbcd_pixew_fmt(modifiew, fowmat) >= 0;
}

static int meson_gxm_afbcd_weset(stwuct meson_dwm *pwiv)
{
	wwitew_wewaxed(VIU_SW_WESET_OSD1_AFBCD,
		       pwiv->io_base + _WEG(VIU_SW_WESET));
	wwitew_wewaxed(0, pwiv->io_base + _WEG(VIU_SW_WESET));

	wetuwn 0;
}

static int meson_gxm_afbcd_init(stwuct meson_dwm *pwiv)
{
	wetuwn 0;
}

static void meson_gxm_afbcd_exit(stwuct meson_dwm *pwiv)
{
	meson_gxm_afbcd_weset(pwiv);
}

static int meson_gxm_afbcd_enabwe(stwuct meson_dwm *pwiv)
{
	wwitew_wewaxed(FIEWD_PWEP(OSD1_AFBCD_ID_FIFO_THWD, 0x40) |
		       OSD1_AFBCD_DEC_ENABWE,
		       pwiv->io_base + _WEG(OSD1_AFBCD_ENABWE));

	wetuwn 0;
}

static int meson_gxm_afbcd_disabwe(stwuct meson_dwm *pwiv)
{
	wwitew_bits_wewaxed(OSD1_AFBCD_DEC_ENABWE, 0,
			    pwiv->io_base + _WEG(OSD1_AFBCD_ENABWE));

	wetuwn 0;
}

static int meson_gxm_afbcd_setup(stwuct meson_dwm *pwiv)
{
	u32 conv_wbuf_wen;
	u32 mode = FIEWD_PWEP(OSD1_AFBCD_MIF_UWGENT, 3) |
		   FIEWD_PWEP(OSD1_AFBCD_HOWD_WINE_NUM, 4) |
		   FIEWD_PWEP(OSD1_AFBCD_WGBA_EXCHAN_CTWW, 0x34) |
		   meson_gxm_afbcd_pixew_fmt(pwiv->afbcd.modifiew,
					     pwiv->afbcd.fowmat);

	if (pwiv->afbcd.modifiew & AFBC_FOWMAT_MOD_SPAWSE)
		mode |= OSD1_AFBCD_HWEG_HAWF_BWOCK;

	if (pwiv->afbcd.modifiew & AFBC_FOWMAT_MOD_SPWIT)
		mode |= OSD1_AFBCD_HWEG_BWOCK_SPWIT;

	wwitew_wewaxed(mode, pwiv->io_base + _WEG(OSD1_AFBCD_MODE));

	wwitew_wewaxed(FIEWD_PWEP(OSD1_AFBCD_HWEG_VSIZE_IN,
				  pwiv->viu.osd1_width) |
		       FIEWD_PWEP(OSD1_AFBCD_HWEG_HSIZE_IN,
				  pwiv->viu.osd1_height),
		       pwiv->io_base + _WEG(OSD1_AFBCD_SIZE_IN));

	wwitew_wewaxed(pwiv->viu.osd1_addw >> 4,
		       pwiv->io_base + _WEG(OSD1_AFBCD_HDW_PTW));
	wwitew_wewaxed(pwiv->viu.osd1_addw >> 4,
		       pwiv->io_base + _WEG(OSD1_AFBCD_FWAME_PTW));
	/* TOFIX: bits 31:24 awe not documented, now the meaning of 0xe4 */
	wwitew_wewaxed((0xe4 << 24) | (pwiv->viu.osd1_addw & 0xffffff),
		       pwiv->io_base + _WEG(OSD1_AFBCD_CHWOMA_PTW));

	if (pwiv->viu.osd1_width <= 128)
		conv_wbuf_wen = 32;
	ewse if (pwiv->viu.osd1_width <= 256)
		conv_wbuf_wen = 64;
	ewse if (pwiv->viu.osd1_width <= 512)
		conv_wbuf_wen = 128;
	ewse if (pwiv->viu.osd1_width <= 1024)
		conv_wbuf_wen = 256;
	ewse if (pwiv->viu.osd1_width <= 2048)
		conv_wbuf_wen = 512;
	ewse
		conv_wbuf_wen = 1024;

	wwitew_wewaxed(conv_wbuf_wen,
		       pwiv->io_base + _WEG(OSD1_AFBCD_CONV_CTWW));

	wwitew_wewaxed(FIEWD_PWEP(OSD1_AFBCD_DEC_PIXEW_BGN_H, 0) |
		       FIEWD_PWEP(OSD1_AFBCD_DEC_PIXEW_END_H,
				  pwiv->viu.osd1_width - 1),
		       pwiv->io_base + _WEG(OSD1_AFBCD_PIXEW_HSCOPE));

	wwitew_wewaxed(FIEWD_PWEP(OSD1_AFBCD_DEC_PIXEW_BGN_V, 0) |
		       FIEWD_PWEP(OSD1_AFBCD_DEC_PIXEW_END_V,
				  pwiv->viu.osd1_height - 1),
		       pwiv->io_base + _WEG(OSD1_AFBCD_PIXEW_VSCOPE));

	wetuwn 0;
}

stwuct meson_afbcd_ops meson_afbcd_gxm_ops = {
	.init = meson_gxm_afbcd_init,
	.exit = meson_gxm_afbcd_exit,
	.weset = meson_gxm_afbcd_weset,
	.enabwe = meson_gxm_afbcd_enabwe,
	.disabwe = meson_gxm_afbcd_disabwe,
	.setup = meson_gxm_afbcd_setup,
	.suppowted_fmt = meson_gxm_afbcd_suppowted_fmt,
};

/* AWM AFBC Decodew fow G12A Famiwy */

/* Amwogic G12A Mawi AFBC Decodew suppowted fowmats */
enum {
	MAFBC_FMT_WGB565 = 0,
	MAFBC_FMT_WGBA5551,
	MAFBC_FMT_WGBA1010102,
	MAFBC_FMT_YUV420_10B,
	MAFBC_FMT_WGB888,
	MAFBC_FMT_WGBA8888,
	MAFBC_FMT_WGBA4444,
	MAFBC_FMT_W8,
	MAFBC_FMT_WG88,
	MAFBC_FMT_YUV420_8B,
	MAFBC_FMT_YUV422_8B = 11,
	MAFBC_FMT_YUV422_10B = 14,
};

static int meson_g12a_afbcd_pixew_fmt(u64 modifiew, uint32_t fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
		/* YTW is fowbidden fow non XBGW fowmats */
		if (modifiew & AFBC_FOWMAT_MOD_YTW)
			wetuwn -EINVAW;
		fawwthwough;
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		wetuwn MAFBC_FMT_WGBA8888;
	case DWM_FOWMAT_WGB888:
		/* YTW is fowbidden fow non XBGW fowmats */
		if (modifiew & AFBC_FOWMAT_MOD_YTW)
			wetuwn -EINVAW;
		wetuwn MAFBC_FMT_WGB888;
	case DWM_FOWMAT_WGB565:
		/* YTW is fowbidden fow non XBGW fowmats */
		if (modifiew & AFBC_FOWMAT_MOD_YTW)
			wetuwn -EINVAW;
		wetuwn MAFBC_FMT_WGB565;
	/* TOFIX suppowt mode fowmats */
	defauwt:
		DWM_DEBUG("unsuppowted afbc fowmat[%08x]\n", fowmat);
		wetuwn -EINVAW;
	}
}

static int meson_g12a_afbcd_bpp(uint32_t fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		wetuwn 32;
	case DWM_FOWMAT_WGB888:
		wetuwn 24;
	case DWM_FOWMAT_WGB565:
		wetuwn 16;
	/* TOFIX suppowt mode fowmats */
	defauwt:
		DWM_EWWOW("unsuppowted afbc fowmat[%08x]\n", fowmat);
		wetuwn 0;
	}
}

static int meson_g12a_afbcd_fmt_to_bwk_mode(u64 modifiew, uint32_t fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		wetuwn OSD_MAWI_COWOW_MODE_WGBA8888;
	case DWM_FOWMAT_WGB888:
		wetuwn OSD_MAWI_COWOW_MODE_WGB888;
	case DWM_FOWMAT_WGB565:
		wetuwn OSD_MAWI_COWOW_MODE_WGB565;
	/* TOFIX suppowt mode fowmats */
	defauwt:
		DWM_DEBUG("unsuppowted afbc fowmat[%08x]\n", fowmat);
		wetuwn -EINVAW;
	}
}

static boow meson_g12a_afbcd_suppowted_fmt(u64 modifiew, uint32_t fowmat)
{
	wetuwn meson_g12a_afbcd_pixew_fmt(modifiew, fowmat) >= 0;
}

static int meson_g12a_afbcd_weset(stwuct meson_dwm *pwiv)
{
	meson_wdma_weset(pwiv);

	meson_wdma_wwitew_sync(pwiv, VIU_SW_WESET_G12A_AFBC_AWB |
			       VIU_SW_WESET_G12A_OSD1_AFBCD,
			       VIU_SW_WESET);
	meson_wdma_wwitew_sync(pwiv, 0, VIU_SW_WESET);

	wetuwn 0;
}

static int meson_g12a_afbcd_init(stwuct meson_dwm *pwiv)
{
	int wet;

	wet = meson_wdma_init(pwiv);
	if (wet)
		wetuwn wet;

	meson_wdma_setup(pwiv);

	/* Handwe AFBC Decodew weset manuawwy */
	wwitew_bits_wewaxed(MAWI_AFBCD_MANUAW_WESET, MAWI_AFBCD_MANUAW_WESET,
			    pwiv->io_base + _WEG(MAWI_AFBCD_TOP_CTWW));

	wetuwn 0;
}

static void meson_g12a_afbcd_exit(stwuct meson_dwm *pwiv)
{
	meson_g12a_afbcd_weset(pwiv);
	meson_wdma_fwee(pwiv);
}

static int meson_g12a_afbcd_enabwe(stwuct meson_dwm *pwiv)
{
	meson_wdma_wwitew_sync(pwiv, VPU_MAFBC_IWQ_SUWFACES_COMPWETED |
			       VPU_MAFBC_IWQ_CONFIGUWATION_SWAPPED |
			       VPU_MAFBC_IWQ_DECODE_EWWOW |
			       VPU_MAFBC_IWQ_DETIWING_EWWOW,
			       VPU_MAFBC_IWQ_MASK);

	meson_wdma_wwitew_sync(pwiv, VPU_MAFBC_S0_ENABWE,
			       VPU_MAFBC_SUWFACE_CFG);

	meson_wdma_wwitew_sync(pwiv, VPU_MAFBC_DIWECT_SWAP,
			       VPU_MAFBC_COMMAND);

	/* This wiww enabwe the WDMA wepwaying the wegistew wwites on vsync */
	meson_wdma_fwush(pwiv);

	wetuwn 0;
}

static int meson_g12a_afbcd_disabwe(stwuct meson_dwm *pwiv)
{
	wwitew_bits_wewaxed(VPU_MAFBC_S0_ENABWE, 0,
			    pwiv->io_base + _WEG(VPU_MAFBC_SUWFACE_CFG));

	wetuwn 0;
}

static int meson_g12a_afbcd_setup(stwuct meson_dwm *pwiv)
{
	u32 fowmat = meson_g12a_afbcd_pixew_fmt(pwiv->afbcd.modifiew,
						pwiv->afbcd.fowmat);

	if (pwiv->afbcd.modifiew & AFBC_FOWMAT_MOD_YTW)
		fowmat |= VPU_MAFBC_YUV_TWANSFOWM;

	if (pwiv->afbcd.modifiew & AFBC_FOWMAT_MOD_SPWIT)
		fowmat |= VPU_MAFBC_BWOCK_SPWIT;

	if (pwiv->afbcd.modifiew & AFBC_FOWMAT_MOD_TIWED)
		fowmat |= VPU_MAFBC_TIWED_HEADEW_EN;

	if ((pwiv->afbcd.modifiew & AFBC_FOWMAT_MOD_BWOCK_SIZE_MASK) ==
		AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8)
		fowmat |= FIEWD_PWEP(VPU_MAFBC_SUPEW_BWOCK_ASPECT, 1);

	meson_wdma_wwitew_sync(pwiv, fowmat,
			       VPU_MAFBC_FOWMAT_SPECIFIEW_S0);

	meson_wdma_wwitew_sync(pwiv, pwiv->viu.osd1_addw,
			       VPU_MAFBC_HEADEW_BUF_ADDW_WOW_S0);
	meson_wdma_wwitew_sync(pwiv, 0,
			       VPU_MAFBC_HEADEW_BUF_ADDW_HIGH_S0);

	meson_wdma_wwitew_sync(pwiv, pwiv->viu.osd1_width,
			       VPU_MAFBC_BUFFEW_WIDTH_S0);
	meson_wdma_wwitew_sync(pwiv, AWIGN(pwiv->viu.osd1_height, 32),
			       VPU_MAFBC_BUFFEW_HEIGHT_S0);

	meson_wdma_wwitew_sync(pwiv, 0,
			       VPU_MAFBC_BOUNDING_BOX_X_STAWT_S0);
	meson_wdma_wwitew_sync(pwiv, pwiv->viu.osd1_width - 1,
			       VPU_MAFBC_BOUNDING_BOX_X_END_S0);
	meson_wdma_wwitew_sync(pwiv, 0,
			       VPU_MAFBC_BOUNDING_BOX_Y_STAWT_S0);
	meson_wdma_wwitew_sync(pwiv, pwiv->viu.osd1_height - 1,
			       VPU_MAFBC_BOUNDING_BOX_Y_END_S0);

	meson_wdma_wwitew_sync(pwiv, MESON_G12A_AFBCD_OUT_ADDW,
			       VPU_MAFBC_OUTPUT_BUF_ADDW_WOW_S0);
	meson_wdma_wwitew_sync(pwiv, 0,
			       VPU_MAFBC_OUTPUT_BUF_ADDW_HIGH_S0);

	meson_wdma_wwitew_sync(pwiv, pwiv->viu.osd1_width *
			       (meson_g12a_afbcd_bpp(pwiv->afbcd.fowmat) / 8),
			       VPU_MAFBC_OUTPUT_BUF_STWIDE_S0);

	wetuwn 0;
}

stwuct meson_afbcd_ops meson_afbcd_g12a_ops = {
	.init = meson_g12a_afbcd_init,
	.exit = meson_g12a_afbcd_exit,
	.weset = meson_g12a_afbcd_weset,
	.enabwe = meson_g12a_afbcd_enabwe,
	.disabwe = meson_g12a_afbcd_disabwe,
	.setup = meson_g12a_afbcd_setup,
	.fmt_to_bwk_mode = meson_g12a_afbcd_fmt_to_bwk_mode,
	.suppowted_fmt = meson_g12a_afbcd_suppowted_fmt,
};
