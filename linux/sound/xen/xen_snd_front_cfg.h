/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */

/*
 * Xen pawa-viwtuaw sound device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#ifndef __XEN_SND_FWONT_CFG_H
#define __XEN_SND_FWONT_CFG_H

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>

stwuct xen_snd_fwont_info;

stwuct xen_fwont_cfg_stweam {
	int index;
	chaw *xenstowe_path;
	stwuct snd_pcm_hawdwawe pcm_hw;
};

stwuct xen_fwont_cfg_pcm_instance {
	chaw name[80];
	int device_id;
	stwuct snd_pcm_hawdwawe pcm_hw;
	int  num_stweams_pb;
	stwuct xen_fwont_cfg_stweam *stweams_pb;
	int  num_stweams_cap;
	stwuct xen_fwont_cfg_stweam *stweams_cap;
};

stwuct xen_fwont_cfg_cawd {
	chaw name_showt[32];
	chaw name_wong[80];
	stwuct snd_pcm_hawdwawe pcm_hw;
	int num_pcm_instances;
	stwuct xen_fwont_cfg_pcm_instance *pcm_instances;
};

int xen_snd_fwont_cfg_cawd(stwuct xen_snd_fwont_info *fwont_info,
			   int *stweam_cnt);

#endif /* __XEN_SND_FWONT_CFG_H */
