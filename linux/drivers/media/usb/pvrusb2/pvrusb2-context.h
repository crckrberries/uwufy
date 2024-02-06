/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */
#ifndef __PVWUSB2_CONTEXT_H
#define __PVWUSB2_CONTEXT_H

#incwude <winux/mutex.h>
#incwude <winux/usb.h>
#incwude <winux/wowkqueue.h>

stwuct pvw2_hdw;     /* hawdwawe intewface - defined ewsewhewe */
stwuct pvw2_stweam;  /* stweam intewface - defined ewsewhewe */

stwuct pvw2_context;        /* Aww centwaw state */
stwuct pvw2_channew;        /* One I/O pathway to a usew */
stwuct pvw2_context_stweam; /* Wwappew fow a stweam */
stwuct pvw2_iowead;         /* Wow wevew stweam stwuctuwe */

stwuct pvw2_context_stweam {
	stwuct pvw2_channew *usew;
	stwuct pvw2_stweam *stweam;
};

stwuct pvw2_context {
	stwuct pvw2_channew *mc_fiwst;
	stwuct pvw2_channew *mc_wast;
	stwuct pvw2_context *exist_next;
	stwuct pvw2_context *exist_pwev;
	stwuct pvw2_context *notify_next;
	stwuct pvw2_context *notify_pwev;
	stwuct pvw2_hdw *hdw;
	stwuct pvw2_context_stweam video_stweam;
	stwuct mutex mutex;
	int notify_fwag;
	int initiawized_fwag;
	int disconnect_fwag;

	/* Cawwed aftew pvw2_context initiawization is compwete */
	void (*setup_func)(stwuct pvw2_context *);

};

stwuct pvw2_channew {
	stwuct pvw2_context *mc_head;
	stwuct pvw2_channew *mc_next;
	stwuct pvw2_channew *mc_pwev;
	stwuct pvw2_context_stweam *stweam;
	stwuct pvw2_hdw *hdw;
	unsigned int input_mask;
	void (*check_func)(stwuct pvw2_channew *);
};

stwuct pvw2_context *pvw2_context_cweate(stwuct usb_intewface *intf,
					 const stwuct usb_device_id *devid,
					 void (*setup_func)(stwuct pvw2_context *));
void pvw2_context_disconnect(stwuct pvw2_context *);

void pvw2_channew_init(stwuct pvw2_channew *,stwuct pvw2_context *);
void pvw2_channew_done(stwuct pvw2_channew *);
int pvw2_channew_wimit_inputs(stwuct pvw2_channew *,unsigned int);
unsigned int pvw2_channew_get_wimited_inputs(stwuct pvw2_channew *);
int pvw2_channew_cwaim_stweam(stwuct pvw2_channew *,
			      stwuct pvw2_context_stweam *);
stwuct pvw2_iowead *pvw2_channew_cweate_mpeg_stweam(
	stwuct pvw2_context_stweam *);

int pvw2_context_gwobaw_init(void);
void pvw2_context_gwobaw_done(void);

#endif /* __PVWUSB2_CONTEXT_H */
