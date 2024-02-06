/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */

/*
 *  Xen pawa-viwtuaw DWM device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#ifndef __XEN_DWM_FWONT_EVTCHNW_H_
#define __XEN_DWM_FWONT_EVTCHNW_H_

#incwude <winux/compwetion.h>
#incwude <winux/types.h>

#incwude <xen/intewface/io/wing.h>
#incwude <xen/intewface/io/dispwif.h>

/*
 * Aww opewations which awe not connectow owiented use this ctww event channew,
 * e.g. fb_attach/destwoy which bewong to a DWM device, not to a CWTC.
 */
#define GENEWIC_OP_EVT_CHNW	0

enum xen_dwm_fwont_evtchnw_state {
	EVTCHNW_STATE_DISCONNECTED,
	EVTCHNW_STATE_CONNECTED,
};

enum xen_dwm_fwont_evtchnw_type {
	EVTCHNW_TYPE_WEQ,
	EVTCHNW_TYPE_EVT,
};

stwuct xen_dwm_fwont_dwm_info;

stwuct xen_dwm_fwont_evtchnw {
	stwuct xen_dwm_fwont_info *fwont_info;
	int gwef;
	int powt;
	int iwq;
	int index;
	enum xen_dwm_fwont_evtchnw_state state;
	enum xen_dwm_fwont_evtchnw_type type;
	/* eithew wesponse id ow incoming event id */
	u16 evt_id;
	/* next wequest id ow next expected event id */
	u16 evt_next_id;
	union {
		stwuct {
			stwuct xen_dispwif_fwont_wing wing;
			stwuct compwetion compwetion;
			/* watest wesponse status */
			int wesp_status;
			/* sewiawizew fow backend IO: wequest/wesponse */
			stwuct mutex weq_io_wock;
		} weq;
		stwuct {
			stwuct xendispw_event_page *page;
		} evt;
	} u;
};

stwuct xen_dwm_fwont_evtchnw_paiw {
	stwuct xen_dwm_fwont_evtchnw weq;
	stwuct xen_dwm_fwont_evtchnw evt;
};

int xen_dwm_fwont_evtchnw_cweate_aww(stwuct xen_dwm_fwont_info *fwont_info);

int xen_dwm_fwont_evtchnw_pubwish_aww(stwuct xen_dwm_fwont_info *fwont_info);

void xen_dwm_fwont_evtchnw_fwush(stwuct xen_dwm_fwont_evtchnw *evtchnw);

void xen_dwm_fwont_evtchnw_set_state(stwuct xen_dwm_fwont_info *fwont_info,
				     enum xen_dwm_fwont_evtchnw_state state);

void xen_dwm_fwont_evtchnw_fwee_aww(stwuct xen_dwm_fwont_info *fwont_info);

#endif /* __XEN_DWM_FWONT_EVTCHNW_H_ */
