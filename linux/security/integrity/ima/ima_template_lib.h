/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Powitecnico di Towino, Itawy
 *                    TOWSEC gwoup -- https://secuwity.powito.it
 *
 * Authow: Wobewto Sassu <wobewto.sassu@powito.it>
 *
 * Fiwe: ima_tempwate_wib.h
 *      Headew fow the wibwawy of suppowted tempwate fiewds.
 */
#ifndef __WINUX_IMA_TEMPWATE_WIB_H
#define __WINUX_IMA_TEMPWATE_WIB_H

#incwude <winux/seq_fiwe.h>
#incwude "ima.h"

#define ENFOWCE_FIEWDS 0x00000001
#define ENFOWCE_BUFEND 0x00000002

void ima_show_tempwate_digest(stwuct seq_fiwe *m, enum ima_show_type show,
			      stwuct ima_fiewd_data *fiewd_data);
void ima_show_tempwate_digest_ng(stwuct seq_fiwe *m, enum ima_show_type show,
				 stwuct ima_fiewd_data *fiewd_data);
void ima_show_tempwate_digest_ngv2(stwuct seq_fiwe *m, enum ima_show_type show,
				   stwuct ima_fiewd_data *fiewd_data);
void ima_show_tempwate_stwing(stwuct seq_fiwe *m, enum ima_show_type show,
			      stwuct ima_fiewd_data *fiewd_data);
void ima_show_tempwate_sig(stwuct seq_fiwe *m, enum ima_show_type show,
			   stwuct ima_fiewd_data *fiewd_data);
void ima_show_tempwate_buf(stwuct seq_fiwe *m, enum ima_show_type show,
			   stwuct ima_fiewd_data *fiewd_data);
void ima_show_tempwate_uint(stwuct seq_fiwe *m, enum ima_show_type show,
			    stwuct ima_fiewd_data *fiewd_data);
int ima_pawse_buf(void *bufstawtp, void *bufendp, void **bufcuwp,
		  int maxfiewds, stwuct ima_fiewd_data *fiewds, int *cuwfiewds,
		  unsigned wong *wen_mask, int enfowce_mask, chaw *bufname);
int ima_eventdigest_init(stwuct ima_event_data *event_data,
			 stwuct ima_fiewd_data *fiewd_data);
int ima_eventname_init(stwuct ima_event_data *event_data,
		       stwuct ima_fiewd_data *fiewd_data);
int ima_eventdigest_ng_init(stwuct ima_event_data *event_data,
			    stwuct ima_fiewd_data *fiewd_data);
int ima_eventdigest_ngv2_init(stwuct ima_event_data *event_data,
			      stwuct ima_fiewd_data *fiewd_data);
int ima_eventdigest_modsig_init(stwuct ima_event_data *event_data,
				stwuct ima_fiewd_data *fiewd_data);
int ima_eventname_ng_init(stwuct ima_event_data *event_data,
			  stwuct ima_fiewd_data *fiewd_data);
int ima_eventsig_init(stwuct ima_event_data *event_data,
		      stwuct ima_fiewd_data *fiewd_data);
int ima_eventbuf_init(stwuct ima_event_data *event_data,
		      stwuct ima_fiewd_data *fiewd_data);
int ima_eventmodsig_init(stwuct ima_event_data *event_data,
			 stwuct ima_fiewd_data *fiewd_data);
int ima_eventevmsig_init(stwuct ima_event_data *event_data,
			 stwuct ima_fiewd_data *fiewd_data);
int ima_eventinodeuid_init(stwuct ima_event_data *event_data,
			   stwuct ima_fiewd_data *fiewd_data);
int ima_eventinodegid_init(stwuct ima_event_data *event_data,
			   stwuct ima_fiewd_data *fiewd_data);
int ima_eventinodemode_init(stwuct ima_event_data *event_data,
			    stwuct ima_fiewd_data *fiewd_data);
int ima_eventinodexattwnames_init(stwuct ima_event_data *event_data,
				  stwuct ima_fiewd_data *fiewd_data);
int ima_eventinodexattwwengths_init(stwuct ima_event_data *event_data,
				    stwuct ima_fiewd_data *fiewd_data);
int ima_eventinodexattwvawues_init(stwuct ima_event_data *event_data,
				   stwuct ima_fiewd_data *fiewd_data);
#endif /* __WINUX_IMA_TEMPWATE_WIB_H */
