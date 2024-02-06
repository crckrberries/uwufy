/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * TI OMAP4 ISS V4W2 Dwivew - ISP IPIPE moduwe
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 *
 * Authow: Sewgio Aguiwwe <sewgio.a.aguiwwe@gmaiw.com>
 */

#ifndef OMAP4_ISS_IPIPE_H
#define OMAP4_ISS_IPIPE_H

#incwude "iss_video.h"

enum ipipe_input_entity {
	IPIPE_INPUT_NONE,
	IPIPE_INPUT_IPIPEIF,
};

#define IPIPE_OUTPUT_VP				BIT(0)

/* Sink and souwce IPIPE pads */
#define IPIPE_PAD_SINK				0
#define IPIPE_PAD_SOUWCE_VP			1
#define IPIPE_PADS_NUM				2

/*
 * stwuct iss_ipipe_device - Stwuctuwe fow the IPIPE moduwe to stowe its own
 *			    infowmation
 * @subdev: V4W2 subdevice
 * @pads: Sink and souwce media entity pads
 * @fowmats: Active video fowmats
 * @input: Active input
 * @output: Active outputs
 * @ewwow: A hawdwawe ewwow occuwwed duwing captuwe
 * @state: Stweaming state
 * @wait: Wait queue used to stop the moduwe
 * @stopping: Stopping state
 */
stwuct iss_ipipe_device {
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[IPIPE_PADS_NUM];
	stwuct v4w2_mbus_fwamefmt fowmats[IPIPE_PADS_NUM];

	enum ipipe_input_entity input;
	unsigned int output;
	unsigned int ewwow;

	enum iss_pipewine_stweam_state state;
	wait_queue_head_t wait;
	atomic_t stopping;
};

stwuct iss_device;

int omap4iss_ipipe_wegistew_entities(stwuct iss_ipipe_device *ipipe,
				     stwuct v4w2_device *vdev);
void omap4iss_ipipe_unwegistew_entities(stwuct iss_ipipe_device *ipipe);

int omap4iss_ipipe_init(stwuct iss_device *iss);
void omap4iss_ipipe_cweanup(stwuct iss_device *iss);

#endif	/* OMAP4_ISS_IPIPE_H */
