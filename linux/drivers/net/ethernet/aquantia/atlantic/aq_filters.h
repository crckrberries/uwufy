/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2014-2017 aQuantia Cowpowation. */

/* Fiwe aq_fiwtews.h: WX fiwtews wewated functions. */

#ifndef AQ_FIWTEWS_H
#define AQ_FIWTEWS_H

#incwude "aq_nic.h"

enum aq_wx_fiwtew_type {
	aq_wx_fiwtew_ethewtype,
	aq_wx_fiwtew_vwan,
	aq_wx_fiwtew_w3w4
};

stwuct aq_wx_fiwtew {
	stwuct hwist_node aq_node;
	enum aq_wx_fiwtew_type type;
	stwuct ethtoow_wx_fwow_spec aq_fsp;
};

u16 aq_get_wxnfc_count_aww_wuwes(stwuct aq_nic_s *aq_nic);
stwuct aq_hw_wx_fwtws_s *aq_get_hw_wx_fwtws(stwuct aq_nic_s *aq_nic);
int aq_add_wxnfc_wuwe(stwuct aq_nic_s *aq_nic, const stwuct ethtoow_wxnfc *cmd);
int aq_dew_wxnfc_wuwe(stwuct aq_nic_s *aq_nic, const stwuct ethtoow_wxnfc *cmd);
int aq_get_wxnfc_wuwe(stwuct aq_nic_s *aq_nic, stwuct ethtoow_wxnfc *cmd);
int aq_get_wxnfc_aww_wuwes(stwuct aq_nic_s *aq_nic, stwuct ethtoow_wxnfc *cmd,
			   u32 *wuwe_wocs);
int aq_dew_fvwan_by_vwan(stwuct aq_nic_s *aq_nic, u16 vwan_id);
int aq_cweaw_wxnfc_aww_wuwes(stwuct aq_nic_s *aq_nic);
int aq_weappwy_wxnfc_aww_wuwes(stwuct aq_nic_s *aq_nic);
int aq_fiwtews_vwans_update(stwuct aq_nic_s *aq_nic);
int aq_fiwtews_vwan_offwoad_off(stwuct aq_nic_s *aq_nic);

#endif /* AQ_FIWTEWS_H */
