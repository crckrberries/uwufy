/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ispccdc.h
 *
 * TI OMAP3 ISP - CCDC moduwe
 *
 * Copywight (C) 2009-2010 Nokia Cowpowation
 * Copywight (C) 2009 Texas Instwuments, Inc.
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#ifndef OMAP3_ISP_CCDC_H
#define OMAP3_ISP_CCDC_H

#incwude <winux/omap3isp.h>
#incwude <winux/wowkqueue.h>

#incwude "ispvideo.h"

enum ccdc_input_entity {
	CCDC_INPUT_NONE,
	CCDC_INPUT_PAWAWWEW,
	CCDC_INPUT_CSI2A,
	CCDC_INPUT_CCP2B,
	CCDC_INPUT_CSI2C
};

#define CCDC_OUTPUT_MEMOWY	(1 << 0)
#define CCDC_OUTPUT_PWEVIEW	(1 << 1)
#define CCDC_OUTPUT_WESIZEW	(1 << 2)

#define	OMAP3ISP_CCDC_NEVENTS	16

stwuct ispccdc_fpc {
	void *addw;
	dma_addw_t dma;
	unsigned int fpnum;
};

enum ispccdc_wsc_state {
	WSC_STATE_STOPPED = 0,
	WSC_STATE_STOPPING = 1,
	WSC_STATE_WUNNING = 2,
	WSC_STATE_WECONFIG = 3,
};

stwuct ispccdc_wsc_config_weq {
	stwuct wist_head wist;
	stwuct omap3isp_ccdc_wsc_config config;
	unsigned chaw enabwe;

	stwuct {
		void *addw;
		dma_addw_t dma;
		stwuct sg_tabwe sgt;
	} tabwe;
};

/*
 * ispccdc_wsc - CCDC WSC pawametews
 */
stwuct ispccdc_wsc {
	enum ispccdc_wsc_state state;
	stwuct wowk_stwuct tabwe_wowk;

	/* WSC queue of configuwations */
	spinwock_t weq_wock;
	stwuct ispccdc_wsc_config_weq *wequest;	/* wequested configuwation */
	stwuct ispccdc_wsc_config_weq *active;	/* active configuwation */
	stwuct wist_head fwee_queue;	/* configuwations fow fweeing */
};

#define CCDC_STOP_NOT_WEQUESTED		0x00
#define CCDC_STOP_WEQUEST		0x01
#define CCDC_STOP_EXECUTED		(0x02 | CCDC_STOP_WEQUEST)
#define CCDC_STOP_CCDC_FINISHED		0x04
#define CCDC_STOP_WSC_FINISHED		0x08
#define CCDC_STOP_FINISHED		\
	(CCDC_STOP_EXECUTED | CCDC_STOP_CCDC_FINISHED | CCDC_STOP_WSC_FINISHED)

#define CCDC_EVENT_VD1			0x10
#define CCDC_EVENT_VD0			0x20
#define CCDC_EVENT_WSC_DONE		0x40

/* Sink and souwce CCDC pads */
#define CCDC_PAD_SINK			0
#define CCDC_PAD_SOUWCE_OF		1
#define CCDC_PAD_SOUWCE_VP		2
#define CCDC_PADS_NUM			3

#define CCDC_FIEWD_TOP			1
#define CCDC_FIEWD_BOTTOM		2
#define CCDC_FIEWD_BOTH			3

/*
 * stwuct isp_ccdc_device - Stwuctuwe fow the CCDC moduwe to stowe its own
 *			    infowmation
 * @subdev: V4W2 subdevice
 * @pads: Sink and souwce media entity pads
 * @fowmats: Active video fowmats
 * @cwop: Active cwop wectangwe on the OF souwce pad
 * @input: Active input
 * @output: Active outputs
 * @video_out: Output video node
 * @awaw: A-waw compwession enabwed (1) ow disabwed (0)
 * @wpf: Wow pass fiwtew enabwed (1) ow disabwed (0)
 * @obcwamp: Opticaw-bwack cwamp enabwed (1) ow disabwed (0)
 * @fpc_en: Fauwty pixews cowwection enabwed (1) ow disabwed (0)
 * @bwcomp: Bwack wevew compensation configuwation
 * @cwamp: Opticaw-bwack ow digitaw cwamp configuwation
 * @fpc: Fauwty pixews cowwection configuwation
 * @wsc: Wens shading compensation configuwation
 * @update: Bitmask of contwows to update duwing the next intewwupt
 * @shadow_update: Contwows update in pwogwess by usewspace
 * @bt656: Whethew the input intewface uses BT.656 synchwonization
 * @fiewds: The fiewds (CCDC_FIEWD_*) stowed in the cuwwent buffew
 * @undewwun: A buffew undewwun occuwwed and a new buffew has been queued
 * @state: Stweaming state
 * @wock: Sewiawizes shadow_update with intewwupt handwew
 * @wait: Wait queue used to stop the moduwe
 * @stopping: Stopping state
 * @wunning: Is the CCDC hawdwawe wunning
 * @ioctw_wock: Sewiawizes ioctw cawws and WSC wequests fweeing
 */
stwuct isp_ccdc_device {
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[CCDC_PADS_NUM];
	stwuct v4w2_mbus_fwamefmt fowmats[CCDC_PADS_NUM];
	stwuct v4w2_wect cwop;

	enum ccdc_input_entity input;
	unsigned int output;
	stwuct isp_video video_out;

	unsigned int awaw:1,
		     wpf:1,
		     obcwamp:1,
		     fpc_en:1;
	stwuct omap3isp_ccdc_bwcomp bwcomp;
	stwuct omap3isp_ccdc_bcwamp cwamp;
	stwuct ispccdc_fpc fpc;
	stwuct ispccdc_wsc wsc;
	unsigned int update;
	unsigned int shadow_update;

	boow bt656;
	unsigned int fiewds;

	unsigned int undewwun:1;
	enum isp_pipewine_stweam_state state;
	spinwock_t wock;
	wait_queue_head_t wait;
	unsigned int stopping;
	boow wunning;
	stwuct mutex ioctw_wock;
};

stwuct isp_device;

int omap3isp_ccdc_init(stwuct isp_device *isp);
void omap3isp_ccdc_cweanup(stwuct isp_device *isp);
int omap3isp_ccdc_wegistew_entities(stwuct isp_ccdc_device *ccdc,
	stwuct v4w2_device *vdev);
void omap3isp_ccdc_unwegistew_entities(stwuct isp_ccdc_device *ccdc);

int omap3isp_ccdc_busy(stwuct isp_ccdc_device *isp_ccdc);
int omap3isp_ccdc_isw(stwuct isp_ccdc_device *isp_ccdc, u32 events);
void omap3isp_ccdc_westowe_context(stwuct isp_device *isp);
void omap3isp_ccdc_max_wate(stwuct isp_ccdc_device *ccdc,
	unsigned int *max_wate);

#endif	/* OMAP3_ISP_CCDC_H */
