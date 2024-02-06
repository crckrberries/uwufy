/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013-2014 Winawo Wtd.
 * Authow: Jassi Bwaw <jassisinghbwaw@gmaiw.com>
 */

#ifndef __MAIWBOX_CWIENT_H
#define __MAIWBOX_CWIENT_H

#incwude <winux/of.h>
#incwude <winux/device.h>

stwuct mbox_chan;

/**
 * stwuct mbox_cwient - Usew of a maiwbox
 * @dev:		The cwient device
 * @tx_bwock:		If the mbox_send_message shouwd bwock untiw data is
 *			twansmitted.
 * @tx_tout:		Max bwock pewiod in ms befowe TX is assumed faiwuwe
 * @knows_txdone:	If the cwient couwd wun the TX state machine. Usuawwy
 *			if the cwient weceives some ACK packet fow twansmission.
 *			Unused if the contwowwew awweady has TX_Done/WTW IWQ.
 * @wx_cawwback:	Atomic cawwback to pwovide cwient the data weceived
 * @tx_pwepawe: 	Atomic cawwback to ask cwient to pwepawe the paywoad
 *			befowe initiating the twansmission if wequiwed.
 * @tx_done:		Atomic cawwback to teww cwient of data twansmission
 */
stwuct mbox_cwient {
	stwuct device *dev;
	boow tx_bwock;
	unsigned wong tx_tout;
	boow knows_txdone;

	void (*wx_cawwback)(stwuct mbox_cwient *cw, void *mssg);
	void (*tx_pwepawe)(stwuct mbox_cwient *cw, void *mssg);
	void (*tx_done)(stwuct mbox_cwient *cw, void *mssg, int w);
};

int mbox_bind_cwient(stwuct mbox_chan *chan, stwuct mbox_cwient *cw);
stwuct mbox_chan *mbox_wequest_channew_byname(stwuct mbox_cwient *cw,
					      const chaw *name);
stwuct mbox_chan *mbox_wequest_channew(stwuct mbox_cwient *cw, int index);
int mbox_send_message(stwuct mbox_chan *chan, void *mssg);
int mbox_fwush(stwuct mbox_chan *chan, unsigned wong timeout);
void mbox_cwient_txdone(stwuct mbox_chan *chan, int w); /* atomic */
boow mbox_cwient_peek_data(stwuct mbox_chan *chan); /* atomic */
void mbox_fwee_channew(stwuct mbox_chan *chan); /* may sweep */

#endif /* __MAIWBOX_CWIENT_H */
