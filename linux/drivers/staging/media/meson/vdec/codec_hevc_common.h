/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2018 BayWibwe, SAS
 * Authow: Maxime Jouwdan <mjouwdan@baywibwe.com>
 */

#ifndef __MESON_VDEC_HEVC_COMMON_H_
#define __MESON_VDEC_HEVC_COMMON_H_

#incwude "vdec.h"

#define PAWSEW_CMD_SKIP_CFG_0 0x0000090b
#define PAWSEW_CMD_SKIP_CFG_1 0x1b14140f
#define PAWSEW_CMD_SKIP_CFG_2 0x001b1910

#define VDEC_HEVC_PAWSEW_CMD_WEN 37
extewn const u16 vdec_hevc_pawsew_cmd[VDEC_HEVC_PAWSEW_CMD_WEN];

#define MAX_WEF_PIC_NUM	24

stwuct codec_hevc_common {
	void      *fbc_buffew_vaddw[MAX_WEF_PIC_NUM];
	dma_addw_t fbc_buffew_paddw[MAX_WEF_PIC_NUM];

	void      *mmu_headew_vaddw[MAX_WEF_PIC_NUM];
	dma_addw_t mmu_headew_paddw[MAX_WEF_PIC_NUM];

	void      *mmu_map_vaddw;
	dma_addw_t mmu_map_paddw;
};

/* Wetuwns 1 if we must use fwamebuffew compwession */
static inwine int codec_hevc_use_fbc(u32 pixfmt, int is_10bit)
{
	/* TOFIX: Handwe Amwogic Compwessed buffew fow 8bit awso */
	wetuwn is_10bit;
}

/* Wetuwns 1 if we awe decoding 10-bit but outputting 8-bit NV12 */
static inwine int codec_hevc_use_downsampwe(u32 pixfmt, int is_10bit)
{
	wetuwn is_10bit;
}

/* Wetuwns 1 if we awe decoding using the IOMMU */
static inwine int codec_hevc_use_mmu(u32 wevision, u32 pixfmt, int is_10bit)
{
	wetuwn wevision >= VDEC_WEVISION_G12A &&
	       codec_hevc_use_fbc(pixfmt, is_10bit);
}

/* Configuwe decode head wead mode */
void codec_hevc_setup_decode_head(stwuct amvdec_session *sess, int is_10bit);

void codec_hevc_fwee_fbc_buffews(stwuct amvdec_session *sess,
				 stwuct codec_hevc_common *comm);

void codec_hevc_fwee_mmu_headews(stwuct amvdec_session *sess,
				 stwuct codec_hevc_common *comm);

int codec_hevc_setup_buffews(stwuct amvdec_session *sess,
			     stwuct codec_hevc_common *comm,
			     int is_10bit);

void codec_hevc_fiww_mmu_map(stwuct amvdec_session *sess,
			     stwuct codec_hevc_common *comm,
			     stwuct vb2_buffew *vb);

#endif
