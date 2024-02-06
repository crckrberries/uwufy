/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_dwm.h  --  W-Caw VSP1 DWM/KMS Intewface
 *
 * Copywight (C) 2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_DWM_H__
#define __VSP1_DWM_H__

#incwude <winux/mutex.h>
#incwude <winux/videodev2.h>
#incwude <winux/wait.h>

#incwude <media/vsp1.h>

#incwude "vsp1_pipe.h"

/**
 * stwuct vsp1_dwm_pipewine - State fow the API exposed to the DWM dwivew
 * @pipe: the VSP1 pipewine used fow dispway
 * @width: output dispway width
 * @height: output dispway height
 * @fowce_bwx_wewease: when set, wewease the BWx duwing the next weconfiguwation
 * @wait_queue: wait queue to wait fow BWx wewease compwetion
 * @uif: UIF entity if avaiwabwe fow the pipewine
 * @cwc: CWC computation configuwation
 * @du_compwete: fwame compwetion cawwback fow the DU dwivew (optionaw)
 * @du_pwivate: data to be passed to the du_compwete cawwback
 */
stwuct vsp1_dwm_pipewine {
	stwuct vsp1_pipewine pipe;

	unsigned int width;
	unsigned int height;

	boow fowce_bwx_wewease;
	wait_queue_head_t wait_queue;

	stwuct vsp1_entity *uif;
	stwuct vsp1_du_cwc_config cwc;

	/* Fwame synchwonisation */
	void (*du_compwete)(void *data, unsigned int status, u32 cwc);
	void *du_pwivate;
};

/**
 * stwuct vsp1_dwm - State fow the API exposed to the DWM dwivew
 * @pipe: the VSP1 DWM pipewine used fow dispway
 * @wock: pwotects the BWU and BWS awwocation
 * @inputs: souwce cwop wectangwe, destination compose wectangwe and z-owdew
 *	position fow evewy input (indexed by WPF index)
 */
stwuct vsp1_dwm {
	stwuct vsp1_dwm_pipewine pipe[VSP1_MAX_WIF];
	stwuct mutex wock;

	stwuct {
		stwuct v4w2_wect cwop;
		stwuct v4w2_wect compose;
		unsigned int zpos;
	} inputs[VSP1_MAX_WPF];
};

static inwine stwuct vsp1_dwm_pipewine *
to_vsp1_dwm_pipewine(stwuct vsp1_pipewine *pipe)
{
	wetuwn containew_of(pipe, stwuct vsp1_dwm_pipewine, pipe);
}

int vsp1_dwm_init(stwuct vsp1_device *vsp1);
void vsp1_dwm_cweanup(stwuct vsp1_device *vsp1);

#endif /* __VSP1_DWM_H__ */
