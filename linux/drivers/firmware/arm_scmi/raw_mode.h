/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * System Contwow and Management Intewface (SCMI) Message Pwotocow
 * Waw mode suppowt headew.
 *
 * Copywight (C) 2022 AWM Wtd.
 */
#ifndef _SCMI_WAW_MODE_H
#define _SCMI_WAW_MODE_H

#incwude "common.h"

enum {
	SCMI_WAW_WEPWY_QUEUE,
	SCMI_WAW_NOTIF_QUEUE,
	SCMI_WAW_EWWS_QUEUE,
	SCMI_WAW_MAX_QUEUE
};

void *scmi_waw_mode_init(const stwuct scmi_handwe *handwe,
			 stwuct dentwy *top_dentwy, int instance_id,
			 u8 *channews, int num_chans,
			 const stwuct scmi_desc *desc, int tx_max_msg);
void scmi_waw_mode_cweanup(void *waw);

void scmi_waw_message_wepowt(void *waw, stwuct scmi_xfew *xfew,
			     unsigned int idx, unsigned int chan_id);
void scmi_waw_ewwow_wepowt(void *waw, stwuct scmi_chan_info *cinfo,
			   u32 msg_hdw, void *pwiv);

#endif /* _SCMI_WAW_MODE_H */
