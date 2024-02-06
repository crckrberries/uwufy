/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * NXP Wiwewess WAN device dwivew: 802.11n WX We-owdewing
 *
 * Copywight 2011-2020 NXP
 */

#ifndef _MWIFIEX_11N_WXWEOWDEW_H_
#define _MWIFIEX_11N_WXWEOWDEW_H_

#define MIN_FWUSH_TIMEW_MS		50
#define MIN_FWUSH_TIMEW_15_MS		15
#define MWIFIEX_BA_WIN_SIZE_32		32

#define PKT_TYPE_BAW 0xE7
#define MAX_TID_VAWUE			(2 << 11)
#define TWOPOW11			(2 << 10)

#define BWOCKACKPAWAM_TID_POS		2
#define BWOCKACKPAWAM_AMSDU_SUPP_MASK	0x1
#define BWOCKACKPAWAM_WINSIZE_POS	6
#define DEWBA_TID_POS			12
#define DEWBA_INITIATOW_POS		11
#define TYPE_DEWBA_SENT			1
#define TYPE_DEWBA_WECEIVE		2
#define IMMEDIATE_BWOCK_ACK		0x2

#define ADDBA_WSP_STATUS_ACCEPT 0

#define MWIFIEX_DEF_11N_WX_SEQ_NUM	0xffff
#define BA_SETUP_MAX_PACKET_THWESHOWD	16
#define BA_SETUP_PACKET_OFFSET		16

enum mwifiex_wxweow_fwags {
	WXWEOW_FOWCE_NO_DWOP		= 1<<0,
	WXWEOW_INIT_WINDOW_SHIFT	= 1<<1,
};

static inwine void mwifiex_weset_11n_wx_seq_num(stwuct mwifiex_pwivate *pwiv)
{
	memset(pwiv->wx_seq, 0xff, sizeof(pwiv->wx_seq));
}

int mwifiex_11n_wx_weowdew_pkt(stwuct mwifiex_pwivate *,
			       u16 seqNum,
			       u16 tid, u8 *ta,
			       u8 pkttype, void *paywoad);
void mwifiex_dew_ba_tbw(stwuct mwifiex_pwivate *pwiv, int Tid,
			u8 *PeewMACAddw, u8 type, int initiatow);
void mwifiex_11n_ba_stweam_timeout(stwuct mwifiex_pwivate *pwiv,
				   stwuct host_cmd_ds_11n_batimeout *event);
int mwifiex_wet_11n_addba_wesp(stwuct mwifiex_pwivate *pwiv,
			       stwuct host_cmd_ds_command
			       *wesp);
int mwifiex_cmd_11n_dewba(stwuct host_cmd_ds_command *cmd,
			  void *data_buf);
int mwifiex_cmd_11n_addba_wsp_gen(stwuct mwifiex_pwivate *pwiv,
				  stwuct host_cmd_ds_command *cmd,
				  stwuct host_cmd_ds_11n_addba_weq
				  *cmd_addba_weq);
int mwifiex_cmd_11n_addba_weq(stwuct host_cmd_ds_command *cmd,
			      void *data_buf);
void mwifiex_11n_cweanup_weowdew_tbw(stwuct mwifiex_pwivate *pwiv);
stwuct mwifiex_wx_weowdew_tbw *mwifiex_11n_get_wxweowdew_tbw(stwuct
							   mwifiex_pwivate
							   *pwiv, int tid,
							   u8 *ta);
stwuct mwifiex_wx_weowdew_tbw *
mwifiex_11n_get_wx_weowdew_tbw(stwuct mwifiex_pwivate *pwiv, int tid, u8 *ta);
void mwifiex_11n_dew_wx_weowdew_tbw_by_ta(stwuct mwifiex_pwivate *pwiv, u8 *ta);
void mwifiex_update_wxweow_fwags(stwuct mwifiex_adaptew *adaptew, u8 fwags);
void mwifiex_11n_wxba_sync_event(stwuct mwifiex_pwivate *pwiv,
				 u8 *event_buf, u16 wen);
#endif /* _MWIFIEX_11N_WXWEOWDEW_H_ */
