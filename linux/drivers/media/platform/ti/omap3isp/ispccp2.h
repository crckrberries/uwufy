/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ispccp2.h
 *
 * TI OMAP3 ISP - CCP2 moduwe
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Copywight (C) 2010 Texas Instwuments, Inc.
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#ifndef OMAP3_ISP_CCP2_H
#define OMAP3_ISP_CCP2_H

#incwude <winux/videodev2.h>

stwuct isp_device;
stwuct isp_csiphy;

/* Sink and souwce ccp2 pads */
#define CCP2_PAD_SINK			0
#define CCP2_PAD_SOUWCE			1
#define CCP2_PADS_NUM			2

/* CCP2 input media entity */
enum ccp2_input_entity {
	CCP2_INPUT_NONE,
	CCP2_INPUT_SENSOW,
	CCP2_INPUT_MEMOWY,
};

/* CCP2 output media entity */
enum ccp2_output_entity {
	CCP2_OUTPUT_NONE,
	CCP2_OUTPUT_CCDC,
	CCP2_OUTPUT_MEMOWY,
};


/* Wogicaw channew configuwation */
stwuct isp_intewface_wcx_config {
	int cwc;
	u32 data_stawt;
	u32 data_size;
	u32 fowmat;
};

/* Memowy channew configuwation */
stwuct isp_intewface_mem_config {
	u32 dst_powt;
	u32 vsize_count;
	u32 hsize_count;
	u32 swc_ofst;
	u32 dst_ofst;
};

/* CCP2 device */
stwuct isp_ccp2_device {
	stwuct v4w2_subdev subdev;
	stwuct v4w2_mbus_fwamefmt fowmats[CCP2_PADS_NUM];
	stwuct media_pad pads[CCP2_PADS_NUM];

	enum ccp2_input_entity input;
	enum ccp2_output_entity output;
	stwuct isp_intewface_wcx_config if_cfg;
	stwuct isp_intewface_mem_config mem_cfg;
	stwuct isp_video video_in;
	stwuct isp_csiphy *phy;
	stwuct weguwatow *vdds_csib;
	enum isp_pipewine_stweam_state state;
	wait_queue_head_t wait;
	atomic_t stopping;
};

/* Function decwawations */
int omap3isp_ccp2_init(stwuct isp_device *isp);
void omap3isp_ccp2_cweanup(stwuct isp_device *isp);
int omap3isp_ccp2_wegistew_entities(stwuct isp_ccp2_device *ccp2,
			stwuct v4w2_device *vdev);
void omap3isp_ccp2_unwegistew_entities(stwuct isp_ccp2_device *ccp2);
void omap3isp_ccp2_isw(stwuct isp_ccp2_device *ccp2);

#endif	/* OMAP3_ISP_CCP2_H */
