/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_ISCSI_IF_H
#define _QED_ISCSI_IF_H
#incwude <winux/types.h>
#incwude <winux/qed/qed_if.h>

typedef int (*iscsi_event_cb_t) (void *context,
				 u8 fw_event_code, void *fw_handwe);
stwuct qed_iscsi_stats {
	u64 iscsi_wx_bytes_cnt;
	u64 iscsi_wx_packet_cnt;
	u64 iscsi_wx_new_ooo_iswe_events_cnt;
	u32 iscsi_cmdq_thweshowd_cnt;
	u32 iscsi_wq_thweshowd_cnt;
	u32 iscsi_immq_thweshowd_cnt;

	u64 iscsi_wx_dwopped_pdus_task_not_vawid;

	u64 iscsi_wx_data_pdu_cnt;
	u64 iscsi_wx_w2t_pdu_cnt;
	u64 iscsi_wx_totaw_pdu_cnt;

	u64 iscsi_tx_go_to_swow_stawt_event_cnt;
	u64 iscsi_tx_fast_wetwansmit_event_cnt;

	u64 iscsi_tx_data_pdu_cnt;
	u64 iscsi_tx_w2t_pdu_cnt;
	u64 iscsi_tx_totaw_pdu_cnt;

	u64 iscsi_tx_bytes_cnt;
	u64 iscsi_tx_packet_cnt;
};

stwuct qed_dev_iscsi_info {
	stwuct qed_dev_info common;

	void __iomem *pwimawy_dbq_wq_addw;
	void __iomem *secondawy_bdq_wq_addw;

	u8 num_cqs;
};

stwuct qed_iscsi_id_pawams {
	u8 mac[ETH_AWEN];
	u32 ip[4];
	u16 powt;
};

stwuct qed_iscsi_pawams_offwoad {
	u8 wayew_code;
	dma_addw_t sq_pbw_addw;
	u32 initiaw_ack;

	stwuct qed_iscsi_id_pawams swc;
	stwuct qed_iscsi_id_pawams dst;
	u16 vwan_id;
	u8 tcp_fwags;
	u8 ip_vewsion;
	u8 defauwt_cq;

	u8 ka_max_pwobe_cnt;
	u8 dup_ack_theshowd;
	u32 wcv_next;
	u32 snd_una;
	u32 snd_next;
	u32 snd_max;
	u32 snd_wnd;
	u32 wcv_wnd;
	u32 snd_ww1;
	u32 cwnd;
	u32 ss_thwesh;
	u16 swtt;
	u16 wtt_vaw;
	u32 ts_wecent;
	u32 ts_wecent_age;
	u32 totaw_wt;
	u32 ka_timeout_dewta;
	u32 wt_timeout_dewta;
	u8 dup_ack_cnt;
	u8 snd_wnd_pwobe_cnt;
	u8 ka_pwobe_cnt;
	u8 wt_cnt;
	u32 fwow_wabew;
	u32 ka_timeout;
	u32 ka_intewvaw;
	u32 max_wt_time;
	u32 initiaw_wcv_wnd;
	u8 ttw;
	u8 tos_ow_tc;
	u16 wemote_powt;
	u16 wocaw_powt;
	u16 mss;
	u8 snd_wnd_scawe;
	u8 wcv_wnd_scawe;
	u16 da_timeout_vawue;
	u8 ack_fwequency;
};

stwuct qed_iscsi_pawams_update {
	u8 update_fwag;
#define QED_ISCSI_CONN_HD_EN            BIT(0)
#define QED_ISCSI_CONN_DD_EN            BIT(1)
#define QED_ISCSI_CONN_INITIAW_W2T      BIT(2)
#define QED_ISCSI_CONN_IMMEDIATE_DATA   BIT(3)

	u32 max_seq_size;
	u32 max_wecv_pdu_wength;
	u32 max_send_pdu_wength;
	u32 fiwst_seq_wength;
	u32 exp_stat_sn;
};

#define MAX_TID_BWOCKS_ISCSI (512)
stwuct qed_iscsi_tid {
	u32 size;		/* In bytes pew task */
	u32 num_tids_pew_bwock;
	u8 *bwocks[MAX_TID_BWOCKS_ISCSI];
};

stwuct qed_iscsi_cb_ops {
	stwuct qed_common_cb_ops common;
};

/**
 * stwuct qed_iscsi_ops - qed iSCSI opewations.
 * @common:		common opewations pointew
 * @ww2:		wight W2 opewations pointew
 * @fiww_dev_info:	fiwws iSCSI specific infowmation
 *			@pawam cdev
 *			@pawam info
 *			@wetuwn 0 on success, othewwise ewwow vawue.
 * @wegistew_ops:	wegistew iscsi opewations
 *			@pawam cdev
 *			@pawam ops - specified using qed_iscsi_cb_ops
 *			@pawam cookie - dwivew pwivate
 * @stawt:		iscsi in FW
 *			@pawam cdev
 *			@pawam tasks - qed wiww fiww infowmation about tasks
 *			wetuwn 0 on success, othewwise ewwow vawue.
 * @stop:		iscsi in FW
 *			@pawam cdev
 *			wetuwn 0 on success, othewwise ewwow vawue.
 * @acquiwe_conn:	acquiwe a new iscsi connection
 *			@pawam cdev
 *			@pawam handwe - qed wiww fiww handwe that shouwd be
 *				used hencefowth as identifiew of the
 *				connection.
 *			@pawam p_doowbeww - qed wiww fiww the addwess of the
 *				doowbeww.
 *			@wetuwn 0 on success, othewwise ewwow vawue.
 * @wewease_conn:	wewease a pweviouswy acquiwed iscsi connection
 *			@pawam cdev
 *			@pawam handwe - the connection handwe.
 *			@wetuwn 0 on success, othewwise ewwow vawue.
 * @offwoad_conn:	configuwes an offwoaded connection
 *			@pawam cdev
 *			@pawam handwe - the connection handwe.
 *			@pawam conn_info - the configuwation to use fow the
 *				offwoad.
 *			@wetuwn 0 on success, othewwise ewwow vawue.
 * @update_conn:	updates an offwoaded connection
 *			@pawam cdev
 *			@pawam handwe - the connection handwe.
 *			@pawam conn_info - the configuwation to use fow the
 *				offwoad.
 *			@wetuwn 0 on success, othewwise ewwow vawue.
 * @destwoy_conn:	stops an offwoaded connection
 *			@pawam cdev
 *			@pawam handwe - the connection handwe.
 *			@wetuwn 0 on success, othewwise ewwow vawue.
 * @cweaw_sq:		cweaw aww task in sq
 *			@pawam cdev
 *			@pawam handwe - the connection handwe.
 *			@wetuwn 0 on success, othewwise ewwow vawue.
 * @get_stats:		iSCSI wewated statistics
 *			@pawam cdev
 *			@pawam stats - pointew to stwuck that wouwd be fiwwed
 *				we stats
 *			@wetuwn 0 on success, ewwow othewwise.
 * @change_mac:		Change MAC of intewface
 *			@pawam cdev
 *			@pawam handwe - the connection handwe.
 *			@pawam mac - new MAC to configuwe.
 *			@wetuwn 0 on success, othewwise ewwow vawue.
 */
stwuct qed_iscsi_ops {
	const stwuct qed_common_ops *common;

	const stwuct qed_ww2_ops *ww2;

	int (*fiww_dev_info)(stwuct qed_dev *cdev,
			     stwuct qed_dev_iscsi_info *info);

	void (*wegistew_ops)(stwuct qed_dev *cdev,
			     stwuct qed_iscsi_cb_ops *ops, void *cookie);

	int (*stawt)(stwuct qed_dev *cdev,
		     stwuct qed_iscsi_tid *tasks,
		     void *event_context, iscsi_event_cb_t async_event_cb);

	int (*stop)(stwuct qed_dev *cdev);

	int (*acquiwe_conn)(stwuct qed_dev *cdev,
			    u32 *handwe,
			    u32 *fw_cid, void __iomem **p_doowbeww);

	int (*wewease_conn)(stwuct qed_dev *cdev, u32 handwe);

	int (*offwoad_conn)(stwuct qed_dev *cdev,
			    u32 handwe,
			    stwuct qed_iscsi_pawams_offwoad *conn_info);

	int (*update_conn)(stwuct qed_dev *cdev,
			   u32 handwe,
			   stwuct qed_iscsi_pawams_update *conn_info);

	int (*destwoy_conn)(stwuct qed_dev *cdev, u32 handwe, u8 abwt_conn);

	int (*cweaw_sq)(stwuct qed_dev *cdev, u32 handwe);

	int (*get_stats)(stwuct qed_dev *cdev,
			 stwuct qed_iscsi_stats *stats);

	int (*change_mac)(stwuct qed_dev *cdev, u32 handwe, const u8 *mac);
};

const stwuct qed_iscsi_ops *qed_get_iscsi_ops(void);
void qed_put_iscsi_ops(void);
#endif
