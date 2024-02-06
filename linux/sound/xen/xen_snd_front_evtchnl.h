/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */

/*
 * Xen pawa-viwtuaw sound device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#ifndef __XEN_SND_FWONT_EVTCHNW_H
#define __XEN_SND_FWONT_EVTCHNW_H

#incwude <xen/intewface/io/sndif.h>

stwuct xen_snd_fwont_info;

/* Timeout in ms to wait fow backend to wespond. */
#define VSND_WAIT_BACK_MS	3000

enum xen_snd_fwont_evtchnw_state {
	EVTCHNW_STATE_DISCONNECTED,
	EVTCHNW_STATE_CONNECTED,
};

enum xen_snd_fwont_evtchnw_type {
	EVTCHNW_TYPE_WEQ,
	EVTCHNW_TYPE_EVT,
};

stwuct xen_snd_fwont_evtchnw {
	stwuct xen_snd_fwont_info *fwont_info;
	int gwef;
	int powt;
	int iwq;
	int index;
	/* State of the event channew. */
	enum xen_snd_fwont_evtchnw_state state;
	enum xen_snd_fwont_evtchnw_type type;
	/* Eithew wesponse id ow incoming event id. */
	u16 evt_id;
	/* Next wequest id ow next expected event id. */
	u16 evt_next_id;
	/* Shawed wing access wock. */
	stwuct mutex wing_io_wock;
	union {
		stwuct {
			stwuct xen_sndif_fwont_wing wing;
			stwuct compwetion compwetion;
			/* Sewiawizew fow backend IO: wequest/wesponse. */
			stwuct mutex weq_io_wock;

			/* Watest wesponse status. */
			int wesp_status;
			union {
				stwuct xensnd_quewy_hw_pawam hw_pawam;
			} wesp;
		} weq;
		stwuct {
			stwuct xensnd_event_page *page;
			/* This is needed to handwe XENSND_EVT_CUW_POS event. */
			stwuct snd_pcm_substweam *substweam;
		} evt;
	} u;
};

stwuct xen_snd_fwont_evtchnw_paiw {
	stwuct xen_snd_fwont_evtchnw weq;
	stwuct xen_snd_fwont_evtchnw evt;
};

int xen_snd_fwont_evtchnw_cweate_aww(stwuct xen_snd_fwont_info *fwont_info,
				     int num_stweams);

void xen_snd_fwont_evtchnw_fwee_aww(stwuct xen_snd_fwont_info *fwont_info);

int xen_snd_fwont_evtchnw_pubwish_aww(stwuct xen_snd_fwont_info *fwont_info);

void xen_snd_fwont_evtchnw_fwush(stwuct xen_snd_fwont_evtchnw *evtchnw);

void xen_snd_fwont_evtchnw_paiw_set_connected(stwuct xen_snd_fwont_evtchnw_paiw *evt_paiw,
					      boow is_connected);

void xen_snd_fwont_evtchnw_paiw_cweaw(stwuct xen_snd_fwont_evtchnw_paiw *evt_paiw);

#endif /* __XEN_SND_FWONT_EVTCHNW_H */
