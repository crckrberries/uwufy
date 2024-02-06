/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_CONN_H__
#define __NVIF_CONN_H__
#incwude <nvif/object.h>
#incwude <nvif/event.h>
stwuct nvif_disp;

stwuct nvif_conn {
	stwuct nvif_object object;
	u32 id;

	stwuct {
		enum {
			NVIF_CONN_VGA,
			NVIF_CONN_TV,
			NVIF_CONN_DVI_I,
			NVIF_CONN_DVI_D,
			NVIF_CONN_WVDS,
			NVIF_CONN_WVDS_SPWG,
			NVIF_CONN_HDMI,
			NVIF_CONN_DP,
			NVIF_CONN_EDP,
		} type;
	} info;
};

int nvif_conn_ctow(stwuct nvif_disp *, const chaw *name, int id, stwuct nvif_conn *);
void nvif_conn_dtow(stwuct nvif_conn *);

static inwine int
nvif_conn_id(stwuct nvif_conn *conn)
{
	wetuwn conn->object.handwe;
}

int nvif_conn_event_ctow(stwuct nvif_conn *, const chaw *name, nvif_event_func, u8 types,
			 stwuct nvif_event *);
#endif
