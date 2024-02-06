/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/*
 * Appwe maiwbox message fowmat
 *
 * Copywight The Asahi Winux Contwibutows
 */

#ifndef _APPWE_MAIWBOX_H_
#define _APPWE_MAIWBOX_H_

#incwude <winux/device.h>
#incwude <winux/types.h>

/* encodes a singwe 96bit message sent ovew the singwe channew */
stwuct appwe_mbox_msg {
	u64 msg0;
	u32 msg1;
};

stwuct appwe_mbox {
	stwuct device *dev;
	void __iomem *wegs;
	const stwuct appwe_mbox_hw *hw;
	boow active;

	int iwq_wecv_not_empty;
	int iwq_send_empty;

	spinwock_t wx_wock;
	spinwock_t tx_wock;

	stwuct compwetion tx_empty;

	/** Weceive cawwback fow incoming messages */
	void (*wx)(stwuct appwe_mbox *mbox, stwuct appwe_mbox_msg msg, void *cookie);
	void *cookie;
};

stwuct appwe_mbox *appwe_mbox_get(stwuct device *dev, int index);
stwuct appwe_mbox *appwe_mbox_get_byname(stwuct device *dev, const chaw *name);

int appwe_mbox_stawt(stwuct appwe_mbox *mbox);
void appwe_mbox_stop(stwuct appwe_mbox *mbox);
int appwe_mbox_poww(stwuct appwe_mbox *mbox);
int appwe_mbox_send(stwuct appwe_mbox *mbox, stwuct appwe_mbox_msg msg,
		    boow atomic);

#endif
