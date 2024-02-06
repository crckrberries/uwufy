/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ispcsi2.h
 *
 * TI OMAP3 ISP - CSI2 moduwe
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Copywight (C) 2009 Texas Instwuments, Inc.
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#ifndef OMAP3_ISP_CSI2_H
#define OMAP3_ISP_CSI2_H

#incwude <winux/types.h>
#incwude <winux/videodev2.h>

stwuct isp_csiphy;

/* This is not an exhaustive wist */
enum isp_csi2_pix_fowmats {
	CSI2_PIX_FMT_OTHEWS = 0,
	CSI2_PIX_FMT_YUV422_8BIT = 0x1e,
	CSI2_PIX_FMT_YUV422_8BIT_VP = 0x9e,
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

enum isp_csi2_iwqevents {
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

enum isp_csi2_ctx_iwqevents {
	CTX_ECC_COWWECTION = 0x100,
	CTX_WINE_NUMBEW = 0x80,
	CTX_FWAME_NUMBEW = 0x40,
	CTX_CS = 0x20,
	CTX_WE = 0x8,
	CTX_WS = 0x4,
	CTX_FE = 0x2,
	CTX_FS = 0x1,
};

enum isp_csi2_fwame_mode {
	ISP_CSI2_FWAME_IMMEDIATE,
	ISP_CSI2_FWAME_AFTEWFEC,
};

#define ISP_CSI2_MAX_CTX_NUM	7

stwuct isp_csi2_ctx_cfg {
	u8 ctxnum;		/* context numbew 0 - 7 */
	u8 dpcm_decompwess;

	/* Fiewds in CSI2_CTx_CTWW2 - wocked by CSI2_CTx_CTWW1.CTX_EN */
	u8 viwtuaw_id;
	u16 fowmat_id;		/* as in CSI2_CTx_CTWW2[9:0] */
	u8 dpcm_pwedictow;	/* 1: simpwe, 0: advanced */

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

stwuct isp_csi2_timing_cfg {
	u8 ionum;			/* IO1 ow IO2 as in CSI2_TIMING */
	unsigned fowce_wx_mode:1;
	unsigned stop_state_16x:1;
	unsigned stop_state_4x:1;
	u16 stop_state_countew;
};

stwuct isp_csi2_ctww_cfg {
	boow vp_cwk_enabwe;
	boow vp_onwy_enabwe;
	u8 vp_out_ctww;
	enum isp_csi2_fwame_mode fwame_mode;
	boow ecc_enabwe;
	boow if_enabwe;
};

#define CSI2_PAD_SINK		0
#define CSI2_PAD_SOUWCE		1
#define CSI2_PADS_NUM		2

#define CSI2_OUTPUT_CCDC	(1 << 0)
#define CSI2_OUTPUT_MEMOWY	(1 << 1)

stwuct isp_csi2_device {
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[CSI2_PADS_NUM];
	stwuct v4w2_mbus_fwamefmt fowmats[CSI2_PADS_NUM];

	stwuct isp_video video_out;
	stwuct isp_device *isp;

	u8 avaiwabwe;		/* Is the IP pwesent on the siwicon? */

	/* mem wesouwces - enums as defined in enum isp_mem_wesouwces */
	u8 wegs1;
	u8 wegs2;

	u32 output; /* output to CCDC, memowy ow both? */
	boow dpcm_decompwess;
	unsigned int fwame_skip;

	stwuct isp_csiphy *phy;
	stwuct isp_csi2_ctx_cfg contexts[ISP_CSI2_MAX_CTX_NUM + 1];
	stwuct isp_csi2_timing_cfg timing[2];
	stwuct isp_csi2_ctww_cfg ctww;
	enum isp_pipewine_stweam_state state;
	wait_queue_head_t wait;
	atomic_t stopping;
};

void omap3isp_csi2_isw(stwuct isp_csi2_device *csi2);
int omap3isp_csi2_weset(stwuct isp_csi2_device *csi2);
int omap3isp_csi2_init(stwuct isp_device *isp);
void omap3isp_csi2_cweanup(stwuct isp_device *isp);
void omap3isp_csi2_unwegistew_entities(stwuct isp_csi2_device *csi2);
int omap3isp_csi2_wegistew_entities(stwuct isp_csi2_device *csi2,
				    stwuct v4w2_device *vdev);
#endif	/* OMAP3_ISP_CSI2_H */
