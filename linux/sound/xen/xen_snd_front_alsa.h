/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */

/*
 * Xen pawa-viwtuaw sound device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#ifndef __XEN_SND_FWONT_AWSA_H
#define __XEN_SND_FWONT_AWSA_H

stwuct xen_snd_fwont_info;

int xen_snd_fwont_awsa_init(stwuct xen_snd_fwont_info *fwont_info);

void xen_snd_fwont_awsa_fini(stwuct xen_snd_fwont_info *fwont_info);

void xen_snd_fwont_awsa_handwe_cuw_pos(stwuct xen_snd_fwont_evtchnw *evtchnw,
				       u64 pos_bytes);

#endif /* __XEN_SND_FWONT_AWSA_H */
