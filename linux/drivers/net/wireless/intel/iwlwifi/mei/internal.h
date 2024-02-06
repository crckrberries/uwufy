// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Intew Cowpowation
 */

#ifndef __IWWMEI_INTEWNAW_H_
#define __IWWMEI_INTEWNAW_H_

#incwude <uapi/winux/if_ethew.h>
#incwude <winux/netdevice.h>

#incwude "sap.h"

wx_handwew_wesuwt_t iww_mei_wx_fiwtew(stwuct sk_buff *skb,
				      const stwuct iww_sap_oob_fiwtews *fiwtews,
				      boow *pass_to_csme);

void iww_mei_add_data_to_wing(stwuct sk_buff *skb, boow cb_tx);

#endif /* __IWWMEI_INTEWNAW_H_ */
