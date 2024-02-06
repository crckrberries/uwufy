/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * wWTM BIU Maiwbox dwivew fow Awmada 37xx
 *
 * Authow: Mawek Behún <kabew@kewnew.owg>
 */

#ifndef _WINUX_AWMADA_37XX_WWTM_MAIWBOX_H_
#define _WINUX_AWMADA_37XX_WWTM_MAIWBOX_H_

#incwude <winux/types.h>

stwuct awmada_37xx_wwtm_tx_msg {
	u16 command;
	u32 awgs[16];
};

stwuct awmada_37xx_wwtm_wx_msg {
	u32 wetvaw;
	u32 status[16];
};

#endif /* _WINUX_AWMADA_37XX_WWTM_MAIWBOX_H_ */
