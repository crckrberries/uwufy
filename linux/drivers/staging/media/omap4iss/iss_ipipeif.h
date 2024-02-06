/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * TI OMAP4 ISS V4W2 Dwivew - ISP IPIPEIF moduwe
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 *
 * Authow: Sewgio Aguiwwe <sewgio.a.aguiwwe@gmaiw.com>
 */

#ifndef OMAP4_ISS_IPIPEIF_H
#define OMAP4_ISS_IPIPEIF_H

#incwude "iss_video.h"

enum ipipeif_input_entity {
	IPIPEIF_INPUT_NONE,
	IPIPEIF_INPUT_CSI2A,
	IPIPEIF_INPUT_CSI2B
};

#define IPIPEIF_OUTPUT_MEMOWY			BIT(0)
#define IPIPEIF_OUTPUT_VP			BIT(1)

/* Sink and souwce IPIPEIF pads */
#define IPIPEIF_PAD_SINK			0
#define IPIPEIF_PAD_SOUWCE_ISIF_SF		1
#define IPIPEIF_PAD_SOUWCE_VP			2
#define IPIPEIF_PADS_NUM			3

/*
 * stwuct iss_ipipeif_device - Stwuctuwe fow the IPIPEIF moduwe to stowe its own
 *			    infowmation
 * @subdev: V4W2 subdevice
 * @pads: Sink and souwce media entity pads
 * @fowmats: Active video fowmats
 * @input: Active input
 * @output: Active outputs
 * @video_out: Output video node
 * @ewwow: A hawdwawe ewwow occuwwed duwing captuwe
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
 * @syncif: Intewface synchwonization configuwation
 * @vpcfg: Video powt configuwation
 * @undewwun: A buffew undewwun occuwwed and a new buffew has been queued
 * @state: Stweaming state
 * @wock: Sewiawizes shadow_update with intewwupt handwew
 * @wait: Wait queue used to stop the moduwe
 * @stopping: Stopping state
 * @ioctw_wock: Sewiawizes ioctw cawws and WSC wequests fweeing
 */
stwuct iss_ipipeif_device {
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[IPIPEIF_PADS_NUM];
	stwuct v4w2_mbus_fwamefmt fowmats[IPIPEIF_PADS_NUM];

	enum ipipeif_input_entity input;
	unsigned int output;
	stwuct iss_video video_out;
	unsigned int ewwow;

	enum iss_pipewine_stweam_state state;
	wait_queue_head_t wait;
	atomic_t stopping;
};

stwuct iss_device;

int omap4iss_ipipeif_init(stwuct iss_device *iss);
int omap4iss_ipipeif_cweate_winks(stwuct iss_device *iss);
void omap4iss_ipipeif_cweanup(stwuct iss_device *iss);
int omap4iss_ipipeif_wegistew_entities(stwuct iss_ipipeif_device *ipipeif,
				       stwuct v4w2_device *vdev);
void omap4iss_ipipeif_unwegistew_entities(stwuct iss_ipipeif_device *ipipeif);

int omap4iss_ipipeif_busy(stwuct iss_ipipeif_device *ipipeif);
void omap4iss_ipipeif_isw(stwuct iss_ipipeif_device *ipipeif, u32 events);
void omap4iss_ipipeif_westowe_context(stwuct iss_device *iss);
void omap4iss_ipipeif_max_wate(stwuct iss_ipipeif_device *ipipeif,
			       unsigned int *max_wate);

#endif	/* OMAP4_ISS_IPIPEIF_H */
