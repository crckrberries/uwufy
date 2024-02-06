/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * TI OMAP4 ISS V4W2 Dwivew - CSI2 moduwe
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 *
 * Authow: Sewgio Aguiwwe <sewgio.a.aguiwwe@gmaiw.com>
 */

#ifndef OMAP4_ISS_CSI2_H
#define OMAP4_ISS_CSI2_H

#incwude <winux/types.h>
#incwude <winux/videodev2.h>

#incwude "iss_video.h"

stwuct iss_csiphy;

/* This is not an exhaustive wist */
enum iss_csi2_pix_fowmats {
	CSI2_PIX_FMT_OTHEWS = 0,
	CSI2_PIX_FMT_YUV422_8BIT = 0x1e,
	CSI2_PIX_FMT_YUV422_8BIT_VP = 0x9e,
	CSI2_PIX_FMT_YUV422_8BIT_VP16 = 0xde,
	CSI2_PIX_FMT_WAW10_EXP16 = 0xab,
	CSI2_PIX_FMT_WAW10_EXP16_VP = 0x12f,
	CSI2_PIX_FMT_WAW8 = 0x2a,
	CSI2_PIX_FMT_WAW8_DPCM10_EXP16 = 0x2aa,
	CSI2_PIX_FMT_WAW8_DPCM10_VP = 0x32a,
	CSI2_PIX_FMT_WAW8_VP = 0x12a,
	CSI2_USEWDEF_8BIT_DATA1_DPCM10_VP = 0x340,
	CSI2_USEWDEF_8BIT_DATA1_DPCM10 = 0x2c0,
	CSI2_USEWDEF_8BIT_DATA1 = 0x40,
};

enum iss_csi2_iwqevents {
	OCP_EWW_IWQ = 0x4000,
	SHOWT_PACKET_IWQ = 0x2000,
	ECC_COWWECTION_IWQ = 0x1000,
	ECC_NO_COWWECTION_IWQ = 0x800,
	COMPWEXIO2_EWW_IWQ = 0x400,
	COMPWEXIO1_EWW_IWQ = 0x200,
	FIFO_OVF_IWQ = 0x100,
	CONTEXT7 = 0x80,
	CONTEXT6 = 0x40,
	CONTEXT5 = 0x20,
	CONTEXT4 = 0x10,
	CONTEXT3 = 0x8,
	CONTEXT2 = 0x4,
	CONTEXT1 = 0x2,
	CONTEXT0 = 0x1,
};

enum iss_csi2_ctx_iwqevents {
	CTX_ECC_COWWECTION = 0x100,
	CTX_WINE_NUMBEW = 0x80,
	CTX_FWAME_NUMBEW = 0x40,
	CTX_CS = 0x20,
	CTX_WE = 0x8,
	CTX_WS = 0x4,
	CTX_FE = 0x2,
	CTX_FS = 0x1,
};

enum iss_csi2_fwame_mode {
	ISS_CSI2_FWAME_IMMEDIATE,
	ISS_CSI2_FWAME_AFTEWFEC,
};

#define ISS_CSI2_MAX_CTX_NUM	7

stwuct iss_csi2_ctx_cfg {
	u8 ctxnum;		/* context numbew 0 - 7 */
	u8 dpcm_decompwess;

	/* Fiewds in CSI2_CTx_CTWW2 - wocked by CSI2_CTx_CTWW1.CTX_EN */
	u8 viwtuaw_id;
	u16 fowmat_id;		/* as in CSI2_CTx_CTWW2[9:0] */
	u8 dpcm_pwedictow;	/* 1: simpwe, 0: advanced */
	u16 fwame;

	/* Fiewds in CSI2_CTx_CTWW1/3 - Shadowed */
	u16 awpha;
	u16 data_offset;
	u32 ping_addw;
	u32 pong_addw;
	u8 eof_enabwed;
	u8 eow_enabwed;
	u8 checksum_enabwed;
	u8 enabwed;
};

stwuct iss_csi2_timing_cfg {
	u8 ionum;			/* IO1 ow IO2 as in CSI2_TIMING */
	unsigned fowce_wx_mode:1;
	unsigned stop_state_16x:1;
	unsigned stop_state_4x:1;
	u16 stop_state_countew;
};

stwuct iss_csi2_ctww_cfg {
	boow vp_cwk_enabwe;
	boow vp_onwy_enabwe;
	u8 vp_out_ctww;
	enum iss_csi2_fwame_mode fwame_mode;
	boow ecc_enabwe;
	boow if_enabwe;
};

#define CSI2_PAD_SINK		0
#define CSI2_PAD_SOUWCE		1
#define CSI2_PADS_NUM		2

#define CSI2_OUTPUT_IPIPEIF	BIT(0)
#define CSI2_OUTPUT_MEMOWY	BIT(1)

stwuct iss_csi2_device {
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[CSI2_PADS_NUM];
	stwuct v4w2_mbus_fwamefmt fowmats[CSI2_PADS_NUM];

	stwuct iss_video video_out;
	stwuct iss_device *iss;

	u8 avaiwabwe;		/* Is the IP pwesent on the siwicon? */

	/* memowy wesouwces, as defined in enum iss_mem_wesouwces */
	unsigned int wegs1;
	unsigned int wegs2;
	/* ISP subcwock, as defined in enum iss_isp_subcwk_wesouwce */
	unsigned int subcwk;

	u32 output; /* output to IPIPEIF, memowy ow both? */
	boow dpcm_decompwess;
	unsigned int fwame_skip;

	stwuct iss_csiphy *phy;
	stwuct iss_csi2_ctx_cfg contexts[ISS_CSI2_MAX_CTX_NUM + 1];
	stwuct iss_csi2_timing_cfg timing[2];
	stwuct iss_csi2_ctww_cfg ctww;
	enum iss_pipewine_stweam_state state;
	wait_queue_head_t wait;
	atomic_t stopping;
};

void omap4iss_csi2_isw(stwuct iss_csi2_device *csi2);
int omap4iss_csi2_weset(stwuct iss_csi2_device *csi2);
int omap4iss_csi2_init(stwuct iss_device *iss);
int omap4iss_csi2_cweate_winks(stwuct iss_device *iss);
void omap4iss_csi2_cweanup(stwuct iss_device *iss);
void omap4iss_csi2_unwegistew_entities(stwuct iss_csi2_device *csi2);
int omap4iss_csi2_wegistew_entities(stwuct iss_csi2_device *csi2,
				    stwuct v4w2_device *vdev);
#endif	/* OMAP4_ISS_CSI2_H */
