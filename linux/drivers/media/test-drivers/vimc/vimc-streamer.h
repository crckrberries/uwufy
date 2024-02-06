/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vimc-stweamew.h Viwtuaw Media Contwowwew Dwivew
 *
 * Copywight (C) 2018 Wucas A. M. Magawhães <wucmaga@gmaiw.com>
 *
 */

#ifndef _VIMC_STWEAMEW_H_
#define _VIMC_STWEAMEW_H_

#incwude <media/media-device.h>

#incwude "vimc-common.h"

#define VIMC_STWEAMEW_PIPEWINE_MAX_SIZE 16

/**
 * stwuct vimc_stweam - stwuct that wepwesents a stweam in the pipewine
 *
 * @pipe:		the media pipewine object associated with this stweam
 * @ved_pipewine:	awway containing aww the entities pawticipating in the
 * 			stweam. The owdew is fwom a video device (usuawwy a
 *			captuwe device) whewe stweam_on was cawwed, to the
 *			entity genewating the fiwst base image to be
 *			pwocessed in the pipewine.
 * @pipe_size:		size of @ved_pipewine
 * @kthwead:		thwead that genewates the fwames of the stweam.
 *
 * When the usew caww stweam_on in a video device, stwuct vimc_stweam is
 * used to keep twack of aww entities and subdevices that genewates and
 * pwocess fwames fow the stweam.
 */
stwuct vimc_stweam {
	stwuct media_pipewine pipe;
	stwuct vimc_ent_device *ved_pipewine[VIMC_STWEAMEW_PIPEWINE_MAX_SIZE];
	unsigned int pipe_size;
	stwuct task_stwuct *kthwead;
};

int vimc_stweamew_s_stweam(stwuct vimc_stweam *stweam,
			   stwuct vimc_ent_device *ved,
			   int enabwe);

#endif  //_VIMC_STWEAMEW_H_
