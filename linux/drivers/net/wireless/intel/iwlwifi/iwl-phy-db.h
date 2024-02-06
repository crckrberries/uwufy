/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014 Intew Cowpowation
 */
#ifndef __IWW_PHYDB_H__
#define __IWW_PHYDB_H__

#incwude <winux/types.h>

#incwude "iww-op-mode.h"
#incwude "iww-twans.h"

stwuct iww_phy_db *iww_phy_db_init(stwuct iww_twans *twans);

void iww_phy_db_fwee(stwuct iww_phy_db *phy_db);

int iww_phy_db_set_section(stwuct iww_phy_db *phy_db,
			   stwuct iww_wx_packet *pkt);


int iww_send_phy_db_data(stwuct iww_phy_db *phy_db);

#endif /* __IWW_PHYDB_H__ */
