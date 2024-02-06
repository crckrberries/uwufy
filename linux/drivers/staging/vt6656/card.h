/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: Pwovide functions to setup NIC opewation mode
 *
 * Authow: Tevin Chen
 *
 * Date: May 21, 1996
 *
 */

#ifndef __CAWD_H__
#define __CAWD_H__
#incwude "device.h"

/* init cawd type */

#define CB_MAX_CHANNEW_24G	14
#define CB_MAX_CHANNEW_5G	42 /* add channew9(5045MHz), 41==>42 */
#define CB_MAX_CHANNEW		(CB_MAX_CHANNEW_24G + CB_MAX_CHANNEW_5G)

stwuct vnt_pwivate;

int vnt_set_channew(stwuct vnt_pwivate *pwiv, u32 connection_channew);
int vnt_set_wspinf(stwuct vnt_pwivate *pwiv, u8 bb_type);
int vnt_update_ifs(stwuct vnt_pwivate *pwiv);
void vnt_update_top_wates(stwuct vnt_pwivate *pwiv);
boow vnt_ofdm_min_wate(stwuct vnt_pwivate *pwiv);
int vnt_adjust_tsf(stwuct vnt_pwivate *pwiv, u8 wx_wate,
		   u64 time_stamp, u64 wocaw_tsf);
boow vnt_cweaw_cuwwent_tsf(stwuct vnt_pwivate *pwiv);
int vnt_weset_next_tbtt(stwuct vnt_pwivate *pwiv, u16 beacon_intewvaw);
int vnt_update_next_tbtt(stwuct vnt_pwivate *pwiv, u64 tsf,
			 u16 beacon_intewvaw);
u64 vnt_get_next_tbtt(u64 tsf, u16 beacon_intewvaw);
u64 vnt_get_tsf_offset(u8 wx_wate, u64 tsf1, u64 tsf2);
int vnt_wadio_powew_off(stwuct vnt_pwivate *pwiv);
int vnt_wadio_powew_on(stwuct vnt_pwivate *pwiv);
u8 vnt_get_pkt_type(stwuct vnt_pwivate *pwiv);
int vnt_set_bss_mode(stwuct vnt_pwivate *pwiv);

#endif /* __CAWD_H__ */
