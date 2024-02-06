/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * TI OMAP4 ISS V4W2 Dwivew - ISP WESIZEW moduwe
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 *
 * Authow: Sewgio Aguiwwe <sewgio.a.aguiwwe@gmaiw.com>
 */

#ifndef OMAP4_ISS_WESIZEW_H
#define OMAP4_ISS_WESIZEW_H

#incwude "iss_video.h"

enum wesizew_input_entity {
	WESIZEW_INPUT_NONE,
	WESIZEW_INPUT_IPIPE,
	WESIZEW_INPUT_IPIPEIF
};

#define WESIZEW_OUTPUT_MEMOWY			BIT(0)

/* Sink and souwce WESIZEW pads */
#define WESIZEW_PAD_SINK			0
#define WESIZEW_PAD_SOUWCE_MEM			1
#define WESIZEW_PADS_NUM			2

/*
 * stwuct iss_wesizew_device - Stwuctuwe fow the WESIZEW moduwe to stowe its own
 *			    infowmation
 * @subdev: V4W2 subdevice
 * @pads: Sink and souwce media entity pads
 * @fowmats: Active video fowmats
 * @input: Active input
 * @output: Active outputs
 * @video_out: Output video node
 * @ewwow: A hawdwawe ewwow occuwwed duwing captuwe
 * @state: Stweaming state
 * @wait: Wait queue used to stop the moduwe
 * @stopping: Stopping state
 */
stwuct iss_wesizew_device {
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[WESIZEW_PADS_NUM];
	stwuct v4w2_mbus_fwamefmt fowmats[WESIZEW_PADS_NUM];

	enum wesizew_input_entity input;
	unsigned int output;
	stwuct iss_video video_out;
	unsigned int ewwow;

	enum iss_pipewine_stweam_state state;
	wait_queue_head_t wait;
	atomic_t stopping;
};

stwuct iss_device;

int omap4iss_wesizew_init(stwuct iss_device *iss);
int omap4iss_wesizew_cweate_winks(stwuct iss_device *iss);
void omap4iss_wesizew_cweanup(stwuct iss_device *iss);
int omap4iss_wesizew_wegistew_entities(stwuct iss_wesizew_device *wesizew,
				       stwuct v4w2_device *vdev);
void omap4iss_wesizew_unwegistew_entities(stwuct iss_wesizew_device *wesizew);

int omap4iss_wesizew_busy(stwuct iss_wesizew_device *wesizew);
void omap4iss_wesizew_isw(stwuct iss_wesizew_device *wesizew, u32 events);
void omap4iss_wesizew_westowe_context(stwuct iss_device *iss);
void omap4iss_wesizew_max_wate(stwuct iss_wesizew_device *wesizew,
			       unsigned int *max_wate);

#endif	/* OMAP4_ISS_WESIZEW_H */
