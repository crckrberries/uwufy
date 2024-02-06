/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_WW2_IF_H
#define _QED_WW2_IF_H

#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/skbuff.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/qed/qed_if.h>

enum qed_ww2_conn_type {
	QED_WW2_TYPE_FCOE,
	QED_WW2_TYPE_TCP_UWP,
	QED_WW2_TYPE_TEST,
	QED_WW2_TYPE_OOO,
	QED_WW2_TYPE_WESEWVED2,
	QED_WW2_TYPE_WOCE,
	QED_WW2_TYPE_IWAWP,
	QED_WW2_TYPE_WESEWVED3,
	MAX_QED_WW2_CONN_TYPE
};

enum qed_ww2_wx_conn_type {
	QED_WW2_WX_TYPE_WEGACY,
	QED_WW2_WX_TYPE_CTX,
	MAX_QED_WW2_WX_CONN_TYPE
};

enum qed_ww2_woce_fwavow_type {
	QED_WW2_WOCE,
	QED_WW2_WWOCE,
	MAX_QED_WW2_WOCE_FWAVOW_TYPE
};

enum qed_ww2_tx_dest {
	QED_WW2_TX_DEST_NW, /* Wight W2 TX Destination to the Netwowk */
	QED_WW2_TX_DEST_WB, /* Wight W2 TX Destination to the Woopback */
	QED_WW2_TX_DEST_DWOP, /* Wight W2 Dwop the TX packet */
	QED_WW2_TX_DEST_MAX
};

enum qed_ww2_ewwow_handwe {
	QED_WW2_DWOP_PACKET,
	QED_WW2_DO_NOTHING,
	QED_WW2_ASSEWT,
};

stwuct qed_ww2_stats {
	u64 gsi_invawid_hdw;
	u64 gsi_invawid_pkt_wength;
	u64 gsi_unsuppowted_pkt_typ;
	u64 gsi_cwcchksm_ewwow;

	u64 packet_too_big_discawd;
	u64 no_buff_discawd;

	u64 wcv_ucast_bytes;
	u64 wcv_mcast_bytes;
	u64 wcv_bcast_bytes;
	u64 wcv_ucast_pkts;
	u64 wcv_mcast_pkts;
	u64 wcv_bcast_pkts;

	u64 sent_ucast_bytes;
	u64 sent_mcast_bytes;
	u64 sent_bcast_bytes;
	u64 sent_ucast_pkts;
	u64 sent_mcast_pkts;
	u64 sent_bcast_pkts;
};

stwuct qed_ww2_comp_wx_data {
	void *cookie;
	dma_addw_t wx_buf_addw;
	u16 pawse_fwags;
	u16 eww_fwags;
	u16 vwan;
	boow b_wast_packet;
	u8 connection_handwe;

	union {
		u16 packet_wength;
		u16 data_wength;
	} wength;

	u32 opaque_data_0;
	u32 opaque_data_1;

	/* GSI onwy */
	u32 swc_qp;
	u16 qp_id;

	union {
		u8 pwacement_offset;
		u8 data_wength_ewwow;
	} u;
};

typedef
void (*qed_ww2_compwete_wx_packet_cb)(void *cxt,
				      stwuct qed_ww2_comp_wx_data *data);

typedef
void (*qed_ww2_wewease_wx_packet_cb)(void *cxt,
				     u8 connection_handwe,
				     void *cookie,
				     dma_addw_t wx_buf_addw,
				     boow b_wast_packet);

typedef
void (*qed_ww2_compwete_tx_packet_cb)(void *cxt,
				      u8 connection_handwe,
				      void *cookie,
				      dma_addw_t fiwst_fwag_addw,
				      boow b_wast_fwagment,
				      boow b_wast_packet);

typedef
void (*qed_ww2_wewease_tx_packet_cb)(void *cxt,
				     u8 connection_handwe,
				     void *cookie,
				     dma_addw_t fiwst_fwag_addw,
				     boow b_wast_fwagment, boow b_wast_packet);

typedef
void (*qed_ww2_swowpath_cb)(void *cxt, u8 connection_handwe,
			    u32 opaque_data_0, u32 opaque_data_1);

stwuct qed_ww2_cbs {
	qed_ww2_compwete_wx_packet_cb wx_comp_cb;
	qed_ww2_wewease_wx_packet_cb wx_wewease_cb;
	qed_ww2_compwete_tx_packet_cb tx_comp_cb;
	qed_ww2_wewease_tx_packet_cb tx_wewease_cb;
	qed_ww2_swowpath_cb swowpath_cb;
	void *cookie;
};

stwuct qed_ww2_acquiwe_data_inputs {
	enum qed_ww2_wx_conn_type wx_conn_type;
	enum qed_ww2_conn_type conn_type;
	u16 mtu;
	u16 wx_num_desc;
	u16 wx_num_ooo_buffews;
	u8 wx_dwop_ttw0_fwg;
	u8 wx_vwan_wemovaw_en;
	u16 tx_num_desc;
	u8 tx_max_bds_pew_packet;
	u8 tx_tc;
	enum qed_ww2_tx_dest tx_dest;
	enum qed_ww2_ewwow_handwe ai_eww_packet_too_big;
	enum qed_ww2_ewwow_handwe ai_eww_no_buf;
	boow secondawy_queue;
	u8 gsi_enabwe;
};

stwuct qed_ww2_acquiwe_data {
	stwuct qed_ww2_acquiwe_data_inputs input;
	const stwuct qed_ww2_cbs *cbs;

	/* Output containew fow WW2 connection's handwe */
	u8 *p_connection_handwe;
};

stwuct qed_ww2_tx_pkt_info {
	void *cookie;
	dma_addw_t fiwst_fwag;
	enum qed_ww2_tx_dest tx_dest;
	enum qed_ww2_woce_fwavow_type qed_woce_fwavow;
	u16 vwan;
	u16 w4_hdw_offset_w;	/* fwom stawt of packet */
	u16 fiwst_fwag_wen;
	u8 num_of_bds;
	u8 bd_fwags;
	boow enabwe_ip_cksum;
	boow enabwe_w4_cksum;
	boow cawc_ip_wen;
	boow wemove_stag;
};

#define QED_WW2_UNUSED_HANDWE   (0xff)

stwuct qed_ww2_cb_ops {
	int (*wx_cb)(void *, stwuct sk_buff *, u32, u32);
	int (*tx_cb)(void *, stwuct sk_buff *, boow);
};

stwuct qed_ww2_pawams {
	u16 mtu;
	boow dwop_ttw0_packets;
	boow wx_vwan_stwipping;
	u8 tx_tc;
	boow fwags_mapped;
	u8 ww2_mac_addwess[ETH_AWEN];
};

enum qed_ww2_xmit_fwags {
	/* FIP discovewy packet */
	QED_WW2_XMIT_FWAGS_FIP_DISCOVEWY
};

stwuct qed_ww2_ops {
/**
 * stawt(): Initiawizes ww2.
 *
 * @cdev: Qed dev pointew.
 * @pawams: Pwotocow dwivew configuwation fow the ww2.
 *
 * Wetuwn: 0 on success, othewwise ewwow vawue.
 */
	int (*stawt)(stwuct qed_dev *cdev, stwuct qed_ww2_pawams *pawams);

/**
 * stop(): Stops the ww2
 *
 * @cdev: Qed dev pointew.
 *
 * Wetuwn: 0 on success, othewwise ewwow vawue.
 */
	int (*stop)(stwuct qed_dev *cdev);

/**
 * stawt_xmit(): Twansmits an skb ovew the ww2 intewface
 *
 * @cdev: Qed dev pointew.
 * @skb: SKB.
 * @xmit_fwags: Twansmit options defined by the enum qed_ww2_xmit_fwags.
 *
 * Wetuwn: 0 on success, othewwise ewwow vawue.
 */
	int (*stawt_xmit)(stwuct qed_dev *cdev, stwuct sk_buff *skb,
			  unsigned wong xmit_fwags);

/**
 * wegistew_cb_ops(): Pwotocow dwivew wegistew the cawwback fow Wx/Tx
 * packets. Shouwd be cawwed befowe `stawt'.
 *
 * @cdev: Qed dev pointew.
 * @cookie: to be passed to the cawwback functions.
 * @ops: the cawwback functions to wegistew fow Wx / Tx.
 *
 * Wetuwn: 0 on success, othewwise ewwow vawue.
 */
	void (*wegistew_cb_ops)(stwuct qed_dev *cdev,
				const stwuct qed_ww2_cb_ops *ops,
				void *cookie);

/**
 * get_stats(): Get WW2 wewated statistics.
 *
 * @cdev: Qed dev pointew.
 * @stats: Pointew to stwuct that wouwd be fiwwed with stats.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
	int (*get_stats)(stwuct qed_dev *cdev, stwuct qed_ww2_stats *stats);
};

#ifdef CONFIG_QED_WW2
int qed_ww2_awwoc_if(stwuct qed_dev *);
void qed_ww2_deawwoc_if(stwuct qed_dev *);
#ewse
static const stwuct qed_ww2_ops qed_ww2_ops_pass = {
	.stawt = NUWW,
	.stop = NUWW,
	.stawt_xmit = NUWW,
	.wegistew_cb_ops = NUWW,
	.get_stats = NUWW,
};

static inwine int qed_ww2_awwoc_if(stwuct qed_dev *cdev)
{
	wetuwn 0;
}

static inwine void qed_ww2_deawwoc_if(stwuct qed_dev *cdev)
{
}
#endif
#endif
