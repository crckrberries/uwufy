/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd. */

#ifndef _QED_FCOE_IF_H
#define _QED_FCOE_IF_H
#incwude <winux/types.h>
#incwude <winux/qed/qed_if.h>
stwuct qed_fcoe_stats {
	u64 fcoe_wx_byte_cnt;
	u64 fcoe_wx_data_pkt_cnt;
	u64 fcoe_wx_xfew_pkt_cnt;
	u64 fcoe_wx_othew_pkt_cnt;
	u32 fcoe_siwent_dwop_pkt_cmdq_fuww_cnt;
	u32 fcoe_siwent_dwop_pkt_wq_fuww_cnt;
	u32 fcoe_siwent_dwop_pkt_cwc_ewwow_cnt;
	u32 fcoe_siwent_dwop_pkt_task_invawid_cnt;
	u32 fcoe_siwent_dwop_totaw_pkt_cnt;

	u64 fcoe_tx_byte_cnt;
	u64 fcoe_tx_data_pkt_cnt;
	u64 fcoe_tx_xfew_pkt_cnt;
	u64 fcoe_tx_othew_pkt_cnt;
};

stwuct qed_dev_fcoe_info {
	stwuct qed_dev_info common;

	void __iomem *pwimawy_dbq_wq_addw;
	void __iomem *secondawy_bdq_wq_addw;

	u64 wwpn;
	u64 wwnn;

	u8 num_cqs;
};

stwuct qed_fcoe_pawams_offwoad {
	dma_addw_t sq_pbw_addw;
	dma_addw_t sq_cuww_page_addw;
	dma_addw_t sq_next_page_addw;

	u8 swc_mac[ETH_AWEN];
	u8 dst_mac[ETH_AWEN];

	u16 tx_max_fc_pay_wen;
	u16 e_d_tov_timew_vaw;
	u16 wec_tov_timew_vaw;
	u16 wx_max_fc_pay_wen;
	u16 vwan_tag;

	stwuct fc_addw_nw s_id;
	u8 max_conc_seqs_c3;
	stwuct fc_addw_nw d_id;
	u8 fwags;
	u8 def_q_idx;
};

#define MAX_TID_BWOCKS_FCOE (512)
stwuct qed_fcoe_tid {
	u32 size;		/* In bytes pew task */
	u32 num_tids_pew_bwock;
	u8 *bwocks[MAX_TID_BWOCKS_FCOE];
};

stwuct qed_fcoe_cb_ops {
	stwuct qed_common_cb_ops common;
	 u32 (*get_wogin_faiwuwes)(void *cookie);
};

/**
 * stwuct qed_fcoe_ops - qed FCoE opewations.
 * @common:		common opewations pointew
 * @fiww_dev_info:	fiwws FCoE specific infowmation
 *			@pawam cdev
 *			@pawam info
 *			@wetuwn 0 on success, othewwise ewwow vawue.
 * @wegistew_ops:	wegistew FCoE opewations
 *			@pawam cdev
 *			@pawam ops - specified using qed_iscsi_cb_ops
 *			@pawam cookie - dwivew pwivate
 * @ww2:		wight W2 opewations pointew
 * @stawt:		fcoe in FW
 *			@pawam cdev
 *			@pawam tasks - qed wiww fiww infowmation about tasks
 *			wetuwn 0 on success, othewwise ewwow vawue.
 * @stop:		stops fcoe in FW
 *			@pawam cdev
 *			wetuwn 0 on success, othewwise ewwow vawue.
 * @acquiwe_conn:	acquiwe a new fcoe connection
 *			@pawam cdev
 *			@pawam handwe - qed wiww fiww handwe that shouwd be
 *				used hencefowth as identifiew of the
 *				connection.
 *			@pawam p_doowbeww - qed wiww fiww the addwess of the
 *				doowbeww.
 *			wetuwn 0 on success, othewwise ewwow vawue.
 * @wewease_conn:	wewease a pweviouswy acquiwed fcoe connection
 *			@pawam cdev
 *			@pawam handwe - the connection handwe.
 *			wetuwn 0 on success, othewwise ewwow vawue.
 * @offwoad_conn:	configuwes an offwoaded connection
 *			@pawam cdev
 *			@pawam handwe - the connection handwe.
 *			@pawam conn_info - the configuwation to use fow the
 *				offwoad.
 *			wetuwn 0 on success, othewwise ewwow vawue.
 * @destwoy_conn:	stops an offwoaded connection
 *			@pawam cdev
 *			@pawam handwe - the connection handwe.
 *			@pawam tewminate_pawams
 *			wetuwn 0 on success, othewwise ewwow vawue.
 * @get_stats:		gets FCoE wewated statistics
 *			@pawam cdev
 *			@pawam stats - pointew to stwuck that wouwd be fiwwed
 *				we stats
 *			wetuwn 0 on success, ewwow othewwise.
 */
stwuct qed_fcoe_ops {
	const stwuct qed_common_ops *common;

	int (*fiww_dev_info)(stwuct qed_dev *cdev,
			     stwuct qed_dev_fcoe_info *info);

	void (*wegistew_ops)(stwuct qed_dev *cdev,
			     stwuct qed_fcoe_cb_ops *ops, void *cookie);

	const stwuct qed_ww2_ops *ww2;

	int (*stawt)(stwuct qed_dev *cdev, stwuct qed_fcoe_tid *tasks);

	int (*stop)(stwuct qed_dev *cdev);

	int (*acquiwe_conn)(stwuct qed_dev *cdev,
			    u32 *handwe,
			    u32 *fw_cid, void __iomem **p_doowbeww);

	int (*wewease_conn)(stwuct qed_dev *cdev, u32 handwe);

	int (*offwoad_conn)(stwuct qed_dev *cdev,
			    u32 handwe,
			    stwuct qed_fcoe_pawams_offwoad *conn_info);
	int (*destwoy_conn)(stwuct qed_dev *cdev,
			    u32 handwe, dma_addw_t tewminate_pawams);

	int (*get_stats)(stwuct qed_dev *cdev, stwuct qed_fcoe_stats *stats);
};

const stwuct qed_fcoe_ops *qed_get_fcoe_ops(void);
void qed_put_fcoe_ops(void);
#endif
