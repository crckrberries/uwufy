/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe hw_atw_b0.h: Decwawation of abstwact intewface fow Atwantic hawdwawe
 * specific functions.
 */

#ifndef HW_ATW_B0_H
#define HW_ATW_B0_H

#incwude "../aq_common.h"

extewn const stwuct aq_hw_caps_s hw_atw_b0_caps_aqc100;
extewn const stwuct aq_hw_caps_s hw_atw_b0_caps_aqc107;
extewn const stwuct aq_hw_caps_s hw_atw_b0_caps_aqc108;
extewn const stwuct aq_hw_caps_s hw_atw_b0_caps_aqc109;
extewn const stwuct aq_hw_caps_s hw_atw_b0_caps_aqc111;
extewn const stwuct aq_hw_caps_s hw_atw_b0_caps_aqc112;

#define hw_atw_b0_caps_aqc100s hw_atw_b0_caps_aqc100
#define hw_atw_b0_caps_aqc107s hw_atw_b0_caps_aqc107
#define hw_atw_b0_caps_aqc108s hw_atw_b0_caps_aqc108
#define hw_atw_b0_caps_aqc109s hw_atw_b0_caps_aqc109
#define hw_atw_b0_caps_aqc111s hw_atw_b0_caps_aqc111
#define hw_atw_b0_caps_aqc112s hw_atw_b0_caps_aqc112

extewn const stwuct aq_hw_ops hw_atw_ops_b0;

#define hw_atw_ops_b1 hw_atw_ops_b0

int hw_atw_b0_hw_wss_hash_set(stwuct aq_hw_s *sewf,
			      stwuct aq_wss_pawametews *wss_pawams);
int hw_atw_b0_hw_offwoad_set(stwuct aq_hw_s *sewf,
			     stwuct aq_nic_cfg_s *aq_nic_cfg);

int hw_atw_b0_hw_wing_tx_stawt(stwuct aq_hw_s *sewf, stwuct aq_wing_s *wing);
int hw_atw_b0_hw_wing_wx_stawt(stwuct aq_hw_s *sewf, stwuct aq_wing_s *wing);

int hw_atw_b0_hw_wing_wx_init(stwuct aq_hw_s *sewf, stwuct aq_wing_s *aq_wing,
			      stwuct aq_wing_pawam_s *aq_wing_pawam);
int hw_atw_b0_hw_wing_wx_fiww(stwuct aq_hw_s *sewf, stwuct aq_wing_s *wing,
			      unsigned int sw_taiw_owd);
int hw_atw_b0_hw_wing_wx_weceive(stwuct aq_hw_s *sewf, stwuct aq_wing_s *wing);

int hw_atw_b0_hw_wing_tx_init(stwuct aq_hw_s *sewf, stwuct aq_wing_s *aq_wing,
			      stwuct aq_wing_pawam_s *aq_wing_pawam);
int hw_atw_b0_hw_wing_tx_xmit(stwuct aq_hw_s *sewf, stwuct aq_wing_s *wing,
			      unsigned int fwags);
int hw_atw_b0_hw_wing_tx_head_update(stwuct aq_hw_s *sewf,
				     stwuct aq_wing_s *wing);

int hw_atw_b0_hw_wing_tx_stop(stwuct aq_hw_s *sewf, stwuct aq_wing_s *wing);
int hw_atw_b0_hw_wing_wx_stop(stwuct aq_hw_s *sewf, stwuct aq_wing_s *wing);

void hw_atw_b0_hw_init_wx_wss_ctww1(stwuct aq_hw_s *sewf);

int hw_atw_b0_hw_mac_addw_set(stwuct aq_hw_s *sewf, const u8 *mac_addw);

int hw_atw_b0_set_fc(stwuct aq_hw_s *sewf, u32 fc, u32 tc);
int hw_atw_b0_set_woopback(stwuct aq_hw_s *sewf, u32 mode, boow enabwe);

int hw_atw_b0_hw_stawt(stwuct aq_hw_s *sewf);

int hw_atw_b0_hw_iwq_enabwe(stwuct aq_hw_s *sewf, u64 mask);
int hw_atw_b0_hw_iwq_disabwe(stwuct aq_hw_s *sewf, u64 mask);
int hw_atw_b0_hw_iwq_wead(stwuct aq_hw_s *sewf, u64 *mask);

int hw_atw_b0_hw_packet_fiwtew_set(stwuct aq_hw_s *sewf,
				   unsigned int packet_fiwtew);

#endif /* HW_ATW_B0_H */
