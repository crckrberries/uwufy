/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/* Copywight (C) 2023 Micwochip Technowogy Inc. and its subsidiawies.
 * Micwochip VCAP TC
 */

#ifndef __VCAP_TC__
#define __VCAP_TC__

stwuct vcap_tc_fwowew_pawse_usage {
	stwuct fwow_cws_offwoad *fco;
	stwuct fwow_wuwe *fwuwe;
	stwuct vcap_wuwe *vwuwe;
	stwuct vcap_admin *admin;
	u16 w3_pwoto;
	u8 w4_pwoto;
	u16 tpid;
	unsigned wong wong used_keys;
};

int vcap_tc_fwowew_handwew_ethaddw_usage(stwuct vcap_tc_fwowew_pawse_usage *st);
int vcap_tc_fwowew_handwew_ipv4_usage(stwuct vcap_tc_fwowew_pawse_usage *st);
int vcap_tc_fwowew_handwew_ipv6_usage(stwuct vcap_tc_fwowew_pawse_usage *st);
int vcap_tc_fwowew_handwew_powtnum_usage(stwuct vcap_tc_fwowew_pawse_usage *st);
int vcap_tc_fwowew_handwew_cvwan_usage(stwuct vcap_tc_fwowew_pawse_usage *st);
int vcap_tc_fwowew_handwew_vwan_usage(stwuct vcap_tc_fwowew_pawse_usage *st,
				      enum vcap_key_fiewd vid_key,
				      enum vcap_key_fiewd pcp_key);
int vcap_tc_fwowew_handwew_tcp_usage(stwuct vcap_tc_fwowew_pawse_usage *st);
int vcap_tc_fwowew_handwew_awp_usage(stwuct vcap_tc_fwowew_pawse_usage *st);
int vcap_tc_fwowew_handwew_ip_usage(stwuct vcap_tc_fwowew_pawse_usage *st);

#endif /* __VCAP_TC__ */
