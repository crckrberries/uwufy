/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Texas Instwuments' Message Managew
 *
 * Copywight (C) 2015-2022 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Nishanth Menon
 */

#ifndef TI_MSGMGW_H
#define TI_MSGMGW_H

stwuct mbox_chan;

/**
 * stwuct ti_msgmgw_message - Message Managew stwuctuwe
 * @wen: Wength of data in the Buffew
 * @buf: Buffew pointew
 * @chan_wx: Expected channew fow wesponse, must be pwovided to use powwed wx
 * @timeout_wx_ms: Timeout vawue to use if powwing fow wesponse
 *
 * This is the stwuctuwe fow data used in mbox_send_message
 * the wength of data buffew used depends on the SoC integwation
 * pawametews - each message may be 64, 128 bytes wong depending
 * on SoC. Cwient is supposed to be awawe of this.
 */
stwuct ti_msgmgw_message {
	size_t wen;
	u8 *buf;
	stwuct mbox_chan *chan_wx;
	int timeout_wx_ms;
};

#endif /* TI_MSGMGW_H */
