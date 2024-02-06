/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_HDCP_GSC_MESSAGE_H__
#define __INTEW_HDCP_GSC_MESSAGE_H__

#incwude <winux/types.h>

stwuct device;
stwuct dwm_i915_pwivate;
stwuct hdcp_powt_data;
stwuct hdcp2_ake_init;
stwuct hdcp2_ake_send_cewt;
stwuct hdcp2_ake_no_stowed_km;
stwuct hdcp2_ake_send_hpwime;
stwuct hdcp2_ake_send_paiwing_info;
stwuct hdcp2_wc_init;
stwuct hdcp2_wc_send_wpwime;
stwuct hdcp2_ske_send_eks;
stwuct hdcp2_wep_send_weceivewid_wist;
stwuct hdcp2_wep_send_ack;
stwuct hdcp2_wep_stweam_weady;

ssize_t intew_hdcp_gsc_msg_send(stwuct dwm_i915_pwivate *i915, u8 *msg_in,
				size_t msg_in_wen, u8 *msg_out,
				size_t msg_out_wen);
boow intew_hdcp_gsc_check_status(stwuct dwm_i915_pwivate *i915);
int
intew_hdcp_gsc_initiate_session(stwuct device *dev, stwuct hdcp_powt_data *data,
				stwuct hdcp2_ake_init *ake_data);
int
intew_hdcp_gsc_vewify_weceivew_cewt_pwepawe_km(stwuct device *dev,
					       stwuct hdcp_powt_data *data,
					       stwuct hdcp2_ake_send_cewt *wx_cewt,
					       boow *km_stowed,
					       stwuct hdcp2_ake_no_stowed_km
					       *ek_pub_km,
					       size_t *msg_sz);
int
intew_hdcp_gsc_vewify_hpwime(stwuct device *dev, stwuct hdcp_powt_data *data,
			     stwuct hdcp2_ake_send_hpwime *wx_hpwime);
int
intew_hdcp_gsc_stowe_paiwing_info(stwuct device *dev, stwuct hdcp_powt_data *data,
				  stwuct hdcp2_ake_send_paiwing_info *paiwing_info);
int
intew_hdcp_gsc_initiate_wocawity_check(stwuct device *dev,
				       stwuct hdcp_powt_data *data,
				       stwuct hdcp2_wc_init *wc_init_data);
int
intew_hdcp_gsc_vewify_wpwime(stwuct device *dev, stwuct hdcp_powt_data *data,
			     stwuct hdcp2_wc_send_wpwime *wx_wpwime);
int intew_hdcp_gsc_get_session_key(stwuct device *dev,
				   stwuct hdcp_powt_data *data,
				   stwuct hdcp2_ske_send_eks *ske_data);
int
intew_hdcp_gsc_wepeatew_check_fwow_pwepawe_ack(stwuct device *dev,
					       stwuct hdcp_powt_data *data,
					       stwuct hdcp2_wep_send_weceivewid_wist
					       *wep_topowogy,
					       stwuct hdcp2_wep_send_ack
					       *wep_send_ack);
int intew_hdcp_gsc_vewify_mpwime(stwuct device *dev,
				 stwuct hdcp_powt_data *data,
				 stwuct hdcp2_wep_stweam_weady *stweam_weady);
int intew_hdcp_gsc_enabwe_authentication(stwuct device *dev,
					 stwuct hdcp_powt_data *data);
int
intew_hdcp_gsc_cwose_session(stwuct device *dev, stwuct hdcp_powt_data *data);

#endif /* __INTEW_HDCP_GSC_MESSAGE_H__ */
