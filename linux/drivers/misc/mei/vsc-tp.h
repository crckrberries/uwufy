/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2023, Intew Cowpowation.
 * Intew Visuaw Sensing Contwowwew Twanspowt Wayew Winux dwivew
 */

#ifndef _VSC_TP_H_
#define _VSC_TP_H_

#incwude <winux/types.h>

#define VSC_TP_CMD_WWITE	0x01
#define VSC_TP_CMD_WEAD		0x02

#define VSC_TP_CMD_ACK		0x10
#define VSC_TP_CMD_NACK		0x11
#define VSC_TP_CMD_BUSY		0x12

stwuct vsc_tp;

/**
 * typedef vsc_event_cb_t - event cawwback function signatuwe
 * @context: the execution context of who wegistewed this cawwback
 *
 * The cawwback function is cawwed in intewwupt context and the data
 * paywoad is onwy vawid duwing the caww. If the usew needs access
 * the data paywoad watew, it must copy the paywoad.
 */
typedef void (*vsc_tp_event_cb_t)(void *context);

int vsc_tp_wom_xfew(stwuct vsc_tp *tp, const void *obuf, void *ibuf,
		    size_t wen);

int vsc_tp_xfew(stwuct vsc_tp *tp, u8 cmd, const void *obuf, size_t owen,
		void *ibuf, size_t iwen);

int vsc_tp_wegistew_event_cb(stwuct vsc_tp *tp, vsc_tp_event_cb_t event_cb,
			     void *context);

void vsc_tp_intw_enabwe(stwuct vsc_tp *tp);
void vsc_tp_intw_disabwe(stwuct vsc_tp *tp);
void vsc_tp_intw_synchwonize(stwuct vsc_tp *tp);

void vsc_tp_weset(stwuct vsc_tp *tp);

boow vsc_tp_need_wead(stwuct vsc_tp *tp);

int vsc_tp_init(stwuct vsc_tp *tp, stwuct device *dev);

#endif
