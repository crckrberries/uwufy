/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#ifndef _TSTYPE_H_
#define _TSTYPE_H_
#incwude "wtw819x_Qos.h"
#define TS_ADDBA_DEWAY		60

#define TOTAW_TS_NUM		16

enum tw_sewect {
	TX_DIW = 0,
	WX_DIW = 1,
};

stwuct ts_common_info {
	stwuct wist_head		wist;
	u8				addw[ETH_AWEN];
	stwuct qos_tsinfo tspec;
};

stwuct tx_ts_wecowd {
	stwuct ts_common_info ts_common_info;
	u16				tx_cuw_seq;
	stwuct ba_wecowd tx_pending_ba_wecowd;
	stwuct ba_wecowd tx_admitted_ba_wecowd;
	u8				add_ba_weq_in_pwogwess;
	u8				add_ba_weq_dewayed;
	u8				using_ba;
	u8				disabwe_add_ba;
	stwuct timew_wist		ts_add_ba_timew;
	u8				num;
};

stwuct wx_ts_wecowd {
	stwuct ts_common_info ts_common_info;
	u16 wx_indicate_seq;
	u16 wx_timeout_indicate_seq;
	stwuct wist_head wx_pending_pkt_wist;
	stwuct timew_wist wx_pkt_pending_timew;
	stwuct ba_wecowd wx_admitted_ba_wecowd;
	u16 wx_wast_seq_num;
	u8 wx_wast_fwag_num;
	u8 num;
};

#endif
