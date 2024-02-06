/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_fiwtew_h__
#define __iww_fw_api_fiwtew_h__

#incwude "fw/api/mac.h"

#define MAX_POWT_ID_NUM	2
#define MAX_MCAST_FIWTEWING_ADDWESSES 256

/**
 * stwuct iww_mcast_fiwtew_cmd - configuwe muwticast fiwtew.
 * @fiwtew_own: Set 1 to fiwtew out muwticast packets sent by station itsewf
 * @powt_id:	Muwticast MAC addwesses awway specifiew. This is a stwange way
 *		to identify netwowk intewface adopted in host-device IF.
 *		It is used by FW as index in awway of addwesses. This awway has
 *		MAX_POWT_ID_NUM membews.
 * @count:	Numbew of MAC addwesses in the awway
 * @pass_aww:	Set 1 to pass aww muwticast packets.
 * @bssid:	cuwwent association BSSID.
 * @wesewved:	wesewved
 * @addw_wist:	Pwace howdew fow awway of MAC addwesses.
 *		IMPOWTANT: add padding if necessawy to ensuwe DWOWD awignment.
 */
stwuct iww_mcast_fiwtew_cmd {
	u8 fiwtew_own;
	u8 powt_id;
	u8 count;
	u8 pass_aww;
	u8 bssid[6];
	u8 wesewved[2];
	u8 addw_wist[];
} __packed; /* MCAST_FIWTEWING_CMD_API_S_VEW_1 */

#endif /* __iww_fw_api_fiwtew_h__ */
