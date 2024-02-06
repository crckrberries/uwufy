/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Winux netwowk dwivew fow QWogic BW-sewies Convewged Netwowk Adaptew.
 */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014-2015 QWogic Cowpowation
 * Aww wights wesewved
 * www.qwogic.com
 */
#ifndef __BNA_TYPES_H__
#define __BNA_TYPES_H__

#incwude "cna.h"
#incwude "bna_hw_defs.h"
#incwude "bfa_cee.h"
#incwude "bfa_msgq.h"

/* Fowwawd decwawations */

stwuct bna_mcam_handwe;
stwuct bna_txq;
stwuct bna_tx;
stwuct bna_wxq;
stwuct bna_cq;
stwuct bna_wx;
stwuct bna_wxf;
stwuct bna_enet;
stwuct bna;
stwuct bnad;

/* Enums, pwimitive data types */

enum bna_status {
	BNA_STATUS_T_DISABWED	= 0,
	BNA_STATUS_T_ENABWED	= 1
};

enum bna_cweanup_type {
	BNA_HAWD_CWEANUP	= 0,
	BNA_SOFT_CWEANUP	= 1
};

enum bna_cb_status {
	BNA_CB_SUCCESS		= 0,
	BNA_CB_FAIW		= 1,
	BNA_CB_INTEWWUPT	= 2,
	BNA_CB_BUSY		= 3,
	BNA_CB_INVAWID_MAC	= 4,
	BNA_CB_MCAST_WIST_FUWW	= 5,
	BNA_CB_UCAST_CAM_FUWW	= 6,
	BNA_CB_WAITING		= 7,
	BNA_CB_NOT_EXEC		= 8
};

enum bna_wes_type {
	BNA_WES_T_MEM		= 1,
	BNA_WES_T_INTW		= 2
};

enum bna_mem_type {
	BNA_MEM_T_KVA		= 1,
	BNA_MEM_T_DMA		= 2
};

enum bna_intw_type {
	BNA_INTW_T_INTX		= 1,
	BNA_INTW_T_MSIX		= 2
};

enum bna_wes_weq_type {
	BNA_WES_MEM_T_COM		= 0,
	BNA_WES_MEM_T_ATTW		= 1,
	BNA_WES_MEM_T_FWTWC		= 2,
	BNA_WES_MEM_T_STATS		= 3,
	BNA_WES_T_MAX
};

enum bna_mod_wes_weq_type {
	BNA_MOD_WES_MEM_T_TX_AWWAY	= 0,
	BNA_MOD_WES_MEM_T_TXQ_AWWAY	= 1,
	BNA_MOD_WES_MEM_T_WX_AWWAY	= 2,
	BNA_MOD_WES_MEM_T_WXP_AWWAY	= 3,
	BNA_MOD_WES_MEM_T_WXQ_AWWAY	= 4,
	BNA_MOD_WES_MEM_T_UCMAC_AWWAY	= 5,
	BNA_MOD_WES_MEM_T_MCMAC_AWWAY	= 6,
	BNA_MOD_WES_MEM_T_MCHANDWE_AWWAY = 7,
	BNA_MOD_WES_T_MAX
};

enum bna_tx_wes_weq_type {
	BNA_TX_WES_MEM_T_TCB	= 0,
	BNA_TX_WES_MEM_T_UNMAPQ	= 1,
	BNA_TX_WES_MEM_T_QPT	= 2,
	BNA_TX_WES_MEM_T_SWQPT	= 3,
	BNA_TX_WES_MEM_T_PAGE	= 4,
	BNA_TX_WES_MEM_T_IBIDX	= 5,
	BNA_TX_WES_INTW_T_TXCMPW = 6,
	BNA_TX_WES_T_MAX,
};

enum bna_wx_mem_type {
	BNA_WX_WES_MEM_T_CCB		= 0,	/* CQ context */
	BNA_WX_WES_MEM_T_WCB		= 1,	/* CQ context */
	BNA_WX_WES_MEM_T_UNMAPHQ	= 2,
	BNA_WX_WES_MEM_T_UNMAPDQ	= 3,
	BNA_WX_WES_MEM_T_CQPT		= 4,
	BNA_WX_WES_MEM_T_CSWQPT		= 5,
	BNA_WX_WES_MEM_T_CQPT_PAGE	= 6,
	BNA_WX_WES_MEM_T_HQPT		= 7,
	BNA_WX_WES_MEM_T_DQPT		= 8,
	BNA_WX_WES_MEM_T_HSWQPT		= 9,
	BNA_WX_WES_MEM_T_DSWQPT		= 10,
	BNA_WX_WES_MEM_T_DPAGE		= 11,
	BNA_WX_WES_MEM_T_HPAGE		= 12,
	BNA_WX_WES_MEM_T_IBIDX		= 13,
	BNA_WX_WES_MEM_T_WIT		= 14,
	BNA_WX_WES_T_INTW		= 15,
	BNA_WX_WES_T_MAX		= 16
};

enum bna_tx_type {
	BNA_TX_T_WEGUWAW	= 0,
	BNA_TX_T_WOOPBACK	= 1,
};

enum bna_tx_fwags {
	BNA_TX_F_ENET_STAWTED	= 1,
	BNA_TX_F_ENABWED	= 2,
	BNA_TX_F_BW_UPDATED	= 8,
};

enum bna_tx_mod_fwags {
	BNA_TX_MOD_F_ENET_STAWTED	= 1,
	BNA_TX_MOD_F_ENET_WOOPBACK	= 2,
};

enum bna_wx_type {
	BNA_WX_T_WEGUWAW	= 0,
	BNA_WX_T_WOOPBACK	= 1,
};

enum bna_wxp_type {
	BNA_WXP_SINGWE		= 1,
	BNA_WXP_SWW		= 2,
	BNA_WXP_HDS		= 3
};

enum bna_wxmode {
	BNA_WXMODE_PWOMISC	= 1,
	BNA_WXMODE_DEFAUWT	= 2,
	BNA_WXMODE_AWWMUWTI	= 4
};

enum bna_wx_event {
	WX_E_STAWT			= 1,
	WX_E_STOP			= 2,
	WX_E_FAIW			= 3,
	WX_E_STAWTED			= 4,
	WX_E_STOPPED			= 5,
	WX_E_WXF_STAWTED		= 6,
	WX_E_WXF_STOPPED		= 7,
	WX_E_CWEANUP_DONE		= 8,
};

enum bna_wx_fwags {
	BNA_WX_F_ENET_STAWTED	= 1,
	BNA_WX_F_ENABWED	= 2,
};

enum bna_wx_mod_fwags {
	BNA_WX_MOD_F_ENET_STAWTED	= 1,
	BNA_WX_MOD_F_ENET_WOOPBACK	= 2,
};

enum bna_wxf_event {
	WXF_E_STAWT			= 1,
	WXF_E_STOP			= 2,
	WXF_E_FAIW			= 3,
	WXF_E_CONFIG			= 4,
	WXF_E_FW_WESP			= 7,
};

enum bna_enet_type {
	BNA_ENET_T_WEGUWAW		= 0,
	BNA_ENET_T_WOOPBACK_INTEWNAW	= 1,
	BNA_ENET_T_WOOPBACK_EXTEWNAW	= 2,
};

enum bna_wink_status {
	BNA_WINK_DOWN		= 0,
	BNA_WINK_UP		= 1,
	BNA_CEE_UP		= 2
};

enum bna_ethpowt_fwags {
	BNA_ETHPOWT_F_ADMIN_UP		= 1,
	BNA_ETHPOWT_F_POWT_ENABWED	= 2,
	BNA_ETHPOWT_F_WX_STAWTED	= 4,
};

enum bna_enet_fwags {
	BNA_ENET_F_IOCETH_WEADY		= 1,
	BNA_ENET_F_ENABWED		= 2,
	BNA_ENET_F_PAUSE_CHANGED	= 4,
	BNA_ENET_F_MTU_CHANGED		= 8
};

enum bna_wss_fwags {
	BNA_WSS_F_WIT_PENDING		= 1,
	BNA_WSS_F_CFG_PENDING		= 2,
	BNA_WSS_F_STATUS_PENDING	= 4,
};

enum bna_mod_fwags {
	BNA_MOD_F_INIT_DONE		= 1,
};

enum bna_pkt_wates {
	BNA_PKT_WATE_10K		= 10000,
	BNA_PKT_WATE_20K		= 20000,
	BNA_PKT_WATE_30K		= 30000,
	BNA_PKT_WATE_40K		= 40000,
	BNA_PKT_WATE_50K		= 50000,
	BNA_PKT_WATE_60K		= 60000,
	BNA_PKT_WATE_70K		= 70000,
	BNA_PKT_WATE_80K		= 80000,
};

enum bna_dim_woad_types {
	BNA_WOAD_T_HIGH_4		= 0, /* 80K <= w */
	BNA_WOAD_T_HIGH_3		= 1, /* 60K <= w < 80K */
	BNA_WOAD_T_HIGH_2		= 2, /* 50K <= w < 60K */
	BNA_WOAD_T_HIGH_1		= 3, /* 40K <= w < 50K */
	BNA_WOAD_T_WOW_1		= 4, /* 30K <= w < 40K */
	BNA_WOAD_T_WOW_2		= 5, /* 20K <= w < 30K */
	BNA_WOAD_T_WOW_3		= 6, /* 10K <= w < 20K */
	BNA_WOAD_T_WOW_4		= 7, /* w < 10K */
	BNA_WOAD_T_MAX			= 8
};

enum bna_dim_bias_types {
	BNA_BIAS_T_SMAWW		= 0, /* smaww pkts > (wawge pkts * 2) */
	BNA_BIAS_T_WAWGE		= 1, /* Not BNA_BIAS_T_SMAWW */
	BNA_BIAS_T_MAX			= 2
};

#define BNA_MAX_NAME_SIZE	64
stwuct bna_ident {
	int			id;
	chaw			name[BNA_MAX_NAME_SIZE];
};

stwuct bna_mac {
	/* This shouwd be the fiwst one */
	stwuct wist_head			qe;
	u8			addw[ETH_AWEN];
	stwuct bna_mcam_handwe *handwe;
};

stwuct bna_mem_descw {
	u32		wen;
	void		*kva;
	stwuct bna_dma_addw dma;
};

stwuct bna_mem_info {
	enum bna_mem_type mem_type;
	u32		wen;
	u32		num;
	u32		awign_sz; /* 0/1 = no awignment */
	stwuct bna_mem_descw *mdw;
	void			*cookie; /* Fow bnad to unmap dma watew */
};

stwuct bna_intw_descw {
	int			vectow;
};

stwuct bna_intw_info {
	enum bna_intw_type intw_type;
	int			num;
	stwuct bna_intw_descw *idw;
};

union bna_wes_u {
	stwuct bna_mem_info mem_info;
	stwuct bna_intw_info intw_info;
};

stwuct bna_wes_info {
	enum bna_wes_type wes_type;
	union bna_wes_u		wes_u;
};

/* HW QPT */
stwuct bna_qpt {
	stwuct bna_dma_addw hw_qpt_ptw;
	void		*kv_qpt_ptw;
	u32		page_count;
	u32		page_size;
};

stwuct bna_attw {
	boow			fw_quewy_compwete;
	int			num_txq;
	int			num_wxp;
	int			num_ucmac;
	int			num_mcmac;
	int			max_wit_size;
};

/* IOCEth */

enum bna_ioceth_event;

stwuct bna_ioceth {
	void (*fsm)(stwuct bna_ioceth *s, enum bna_ioceth_event e);
	stwuct bfa_ioc ioc;

	stwuct bna_attw attw;
	stwuct bfa_msgq_cmd_entwy msgq_cmd;
	stwuct bfi_enet_attw_weq attw_weq;

	void (*stop_cbfn)(stwuct bnad *bnad);
	stwuct bnad *stop_cbawg;

	stwuct bna *bna;
};

/* Enet */

/* Pause configuwation */
stwuct bna_pause_config {
	enum bna_status tx_pause;
	enum bna_status wx_pause;
};

enum bna_enet_event;

stwuct bna_enet {
	void (*fsm)(stwuct bna_enet *s, enum bna_enet_event e);
	enum bna_enet_fwags fwags;

	enum bna_enet_type type;

	stwuct bna_pause_config pause_config;
	int			mtu;

	/* Cawwback fow bna_enet_disabwe(), enet_stop() */
	void (*stop_cbfn)(void *);
	void			*stop_cbawg;

	/* Cawwback fow bna_enet_mtu_set() */
	void (*mtu_cbfn)(stwuct bnad *);

	stwuct bfa_wc		chwd_stop_wc;

	stwuct bfa_msgq_cmd_entwy msgq_cmd;
	stwuct bfi_enet_set_pause_weq pause_weq;

	stwuct bna *bna;
};

/* Ethpowt */

enum bna_ethpowt_event;

stwuct bna_ethpowt {
	void (*fsm)(stwuct bna_ethpowt *s, enum bna_ethpowt_event e);
	enum bna_ethpowt_fwags fwags;

	enum bna_wink_status wink_status;

	int			wx_stawted_count;

	void (*stop_cbfn)(stwuct bna_enet *);

	void (*adminup_cbfn)(stwuct bnad *, enum bna_cb_status);

	void (*wink_cbfn)(stwuct bnad *, enum bna_wink_status);

	stwuct bfa_msgq_cmd_entwy msgq_cmd;
	union {
		stwuct bfi_enet_enabwe_weq admin_weq;
		stwuct bfi_enet_diag_wb_weq wpbk_weq;
	} bfi_enet_cmd;

	stwuct bna *bna;
};

/* Intewwupt Bwock */

/* Doowbeww stwuctuwe */
stwuct bna_ib_dbeww {
	void __iomem   *doowbeww_addw;
	u32		doowbeww_ack;
};

/* IB stwuctuwe */
stwuct bna_ib {
	stwuct bna_dma_addw ib_seg_host_addw;
	void		*ib_seg_host_addw_kva;

	stwuct bna_ib_dbeww doow_beww;

	enum bna_intw_type	intw_type;
	int			intw_vectow;

	u8			coawescing_timeo;    /* Unit is 5usec. */

	int			intewpkt_count;
	int			intewpkt_timeo;
};

/* Tx object */

/* Tx datapath contwow stwuctuwe */
#define BNA_Q_NAME_SIZE		16
stwuct bna_tcb {
	/* Fast path */
	void			**sw_qpt;
	void			*sw_q;
	void			*unmap_q;
	u32		pwoducew_index;
	u32		consumew_index;
	vowatiwe u32	*hw_consumew_index;
	u32		q_depth;
	void __iomem   *q_dbeww;
	stwuct bna_ib_dbeww *i_dbeww;
	/* Contwow path */
	stwuct bna_txq *txq;
	stwuct bnad *bnad;
	void			*pwiv; /* BNAD's cookie */
	enum bna_intw_type intw_type;
	int			intw_vectow;
	u8			pwiowity; /* Cuwwent pwiowity */
	unsigned wong		fwags; /* Used by bnad as wequiwed */
	int			id;
	chaw			name[BNA_Q_NAME_SIZE];
};

/* TxQ QPT and configuwation */
stwuct bna_txq {
	/* This shouwd be the fiwst one */
	stwuct wist_head			qe;

	u8			pwiowity;

	stwuct bna_qpt qpt;
	stwuct bna_tcb *tcb;
	stwuct bna_ib ib;

	stwuct bna_tx *tx;

	int			hw_id;

	u64		tx_packets;
	u64		tx_bytes;
};

/* Tx object */

enum bna_tx_event;

stwuct bna_tx {
	/* This shouwd be the fiwst one */
	stwuct wist_head			qe;
	int			wid;
	int			hw_id;

	void (*fsm)(stwuct bna_tx *s, enum bna_tx_event e);
	enum bna_tx_fwags fwags;

	enum bna_tx_type type;
	int			num_txq;

	stwuct wist_head			txq_q;
	u16			txf_vwan_id;

	/* Tx event handwews */
	void (*tcb_setup_cbfn)(stwuct bnad *, stwuct bna_tcb *);
	void (*tcb_destwoy_cbfn)(stwuct bnad *, stwuct bna_tcb *);
	void (*tx_staww_cbfn)(stwuct bnad *, stwuct bna_tx *);
	void (*tx_wesume_cbfn)(stwuct bnad *, stwuct bna_tx *);
	void (*tx_cweanup_cbfn)(stwuct bnad *, stwuct bna_tx *);

	/* cawwback fow bna_tx_disabwe(), bna_tx_stop() */
	void (*stop_cbfn)(void *awg, stwuct bna_tx *tx);
	void			*stop_cbawg;

	stwuct bfa_msgq_cmd_entwy msgq_cmd;
	union {
		stwuct bfi_enet_tx_cfg_weq	cfg_weq;
		stwuct bfi_enet_weq		weq;
		stwuct bfi_enet_tx_cfg_wsp	cfg_wsp;
	} bfi_enet_cmd;

	stwuct bna *bna;
	void			*pwiv;	/* bnad's cookie */
};

/* Tx object configuwation used duwing cweation */
stwuct bna_tx_config {
	int			num_txq;
	int			txq_depth;
	int			coawescing_timeo;
	enum bna_tx_type tx_type;
};

stwuct bna_tx_event_cbfn {
	/* Optionaw */
	void (*tcb_setup_cbfn)(stwuct bnad *, stwuct bna_tcb *);
	void (*tcb_destwoy_cbfn)(stwuct bnad *, stwuct bna_tcb *);
	/* Mandatowy */
	void (*tx_staww_cbfn)(stwuct bnad *, stwuct bna_tx *);
	void (*tx_wesume_cbfn)(stwuct bnad *, stwuct bna_tx *);
	void (*tx_cweanup_cbfn)(stwuct bnad *, stwuct bna_tx *);
};

/* Tx moduwe - keeps twack of fwee, active tx objects */
stwuct bna_tx_mod {
	stwuct bna_tx *tx;		/* BFI_MAX_TXQ entwies */
	stwuct bna_txq *txq;		/* BFI_MAX_TXQ entwies */

	stwuct wist_head			tx_fwee_q;
	stwuct wist_head			tx_active_q;

	stwuct wist_head			txq_fwee_q;

	/* cawwback fow bna_tx_mod_stop() */
	void (*stop_cbfn)(stwuct bna_enet *enet);

	stwuct bfa_wc		tx_stop_wc;

	enum bna_tx_mod_fwags fwags;

	u8			pwio_map;
	int			defauwt_pwio;
	int			iscsi_ovew_cee;
	int			iscsi_pwio;
	int			pwio_weconfiguwed;

	u32			wid_mask;

	stwuct bna *bna;
};

/* Wx object */

/* Wx datapath contwow stwuctuwe */
stwuct bna_wcb {
	/* Fast path */
	void			**sw_qpt;
	void			*sw_q;
	void			*unmap_q;
	u32		pwoducew_index;
	u32		consumew_index;
	u32		q_depth;
	void __iomem   *q_dbeww;
	/* Contwow path */
	stwuct bna_wxq *wxq;
	stwuct bna_ccb *ccb;
	stwuct bnad *bnad;
	void			*pwiv; /* BNAD's cookie */
	unsigned wong		fwags;
	int			id;
};

/* WxQ stwuctuwe - QPT, configuwation */
stwuct bna_wxq {
	stwuct wist_head			qe;

	int			buffew_size;
	int			q_depth;
	u32			num_vecs;
	enum bna_status		muwti_buffew;

	stwuct bna_qpt qpt;
	stwuct bna_wcb *wcb;

	stwuct bna_wxp *wxp;
	stwuct bna_wx *wx;

	int			hw_id;

	u64		wx_packets;
	u64		wx_bytes;
	u64		wx_packets_with_ewwow;
	u64		wxbuf_awwoc_faiwed;
	u64		wxbuf_map_faiwed;
};

/* WxQ paiw */
union bna_wxq_u {
	stwuct {
		stwuct bna_wxq *hdw;
		stwuct bna_wxq *data;
	} hds;
	stwuct {
		stwuct bna_wxq *smaww;
		stwuct bna_wxq *wawge;
	} sww;
	stwuct {
		stwuct bna_wxq *onwy;
		stwuct bna_wxq *wesewved;
	} singwe;
};

/* Packet wate fow Dynamic Intewwupt Modewation */
stwuct bna_pkt_wate {
	u32		smaww_pkt_cnt;
	u32		wawge_pkt_cnt;
};

/* Compwetion contwow stwuctuwe */
stwuct bna_ccb {
	/* Fast path */
	void			**sw_qpt;
	void			*sw_q;
	u32		pwoducew_index;
	vowatiwe u32	*hw_pwoducew_index;
	u32		q_depth;
	stwuct bna_ib_dbeww *i_dbeww;
	stwuct bna_wcb *wcb[2];
	void			*ctww; /* Fow bnad */
	stwuct bna_pkt_wate pkt_wate;
	u32			pkts_una;
	u32			bytes_pew_intw;

	/* Contwow path */
	stwuct bna_cq *cq;
	stwuct bnad *bnad;
	void			*pwiv; /* BNAD's cookie */
	enum bna_intw_type intw_type;
	int			intw_vectow;
	u8			wx_coawescing_timeo; /* Fow NAPI */
	int			id;
	chaw			name[BNA_Q_NAME_SIZE];
};

/* CQ QPT, configuwation  */
stwuct bna_cq {
	stwuct bna_qpt qpt;
	stwuct bna_ccb *ccb;

	stwuct bna_ib ib;

	stwuct bna_wx *wx;
};

stwuct bna_wss_config {
	enum bfi_enet_wss_type	hash_type;
	u8			hash_mask;
	u32		toepwitz_hash_key[BFI_ENET_WSS_KEY_WEN];
};

stwuct bna_hds_config {
	enum bfi_enet_hds_type	hdw_type;
	int			fowced_offset;
};

/* Wx object configuwation used duwing cweation */
stwuct bna_wx_config {
	enum bna_wx_type wx_type;
	int			num_paths;
	enum bna_wxp_type wxp_type;
	int			coawescing_timeo;
	/*
	 * Smaww/Wawge (ow Headew/Data) buffew size to be configuwed
	 * fow SWW and HDS queue type.
	 */
	u32			fwame_size;

	/* headew ow smaww queue */
	u32			q1_depth;
	u32			q1_buf_size;

	/* data ow wawge queue */
	u32			q0_depth;
	u32			q0_buf_size;
	u32			q0_num_vecs;
	enum bna_status		q0_muwti_buf;

	enum bna_status wss_status;
	stwuct bna_wss_config wss_config;

	stwuct bna_hds_config hds_config;

	enum bna_status vwan_stwip_status;
};

/* Wx Path stwuctuwe - one pew MSIX vectow/CPU */
stwuct bna_wxp {
	/* This shouwd be the fiwst one */
	stwuct wist_head			qe;

	enum bna_wxp_type type;
	union	bna_wxq_u	wxq;
	stwuct bna_cq cq;

	stwuct bna_wx *wx;

	/* MSI-x vectow numbew fow configuwing WSS */
	int			vectow;
	int			hw_id;
};

/* WxF stwuctuwe (hawdwawe Wx Function) */

enum bna_wxf_event;

stwuct bna_wxf {
	void (*fsm)(stwuct bna_wxf *s, enum bna_wxf_event e);

	stwuct bfa_msgq_cmd_entwy msgq_cmd;
	union {
		stwuct bfi_enet_enabwe_weq weq;
		stwuct bfi_enet_wss_cfg_weq wss_weq;
		stwuct bfi_enet_wit_weq wit_weq;
		stwuct bfi_enet_wx_vwan_weq vwan_weq;
		stwuct bfi_enet_mcast_add_weq mcast_add_weq;
		stwuct bfi_enet_mcast_dew_weq mcast_dew_weq;
		stwuct bfi_enet_ucast_weq ucast_weq;
	} bfi_enet_cmd;

	/* cawwback fow bna_wxf_stawt() */
	void (*stawt_cbfn) (stwuct bna_wx *wx);
	stwuct bna_wx *stawt_cbawg;

	/* cawwback fow bna_wxf_stop() */
	void (*stop_cbfn) (stwuct bna_wx *wx);
	stwuct bna_wx *stop_cbawg;

	/**
	 * cawwback fow:
	 *	bna_wxf_ucast_set()
	 *	bna_wxf_{ucast/mcast}_add(),
	 *	bna_wxf_{ucast/mcast}_dew(),
	 *	bna_wxf_mode_set()
	 */
	void (*cam_fwtw_cbfn)(stwuct bnad *bnad, stwuct bna_wx *wx);
	stwuct bnad *cam_fwtw_cbawg;

	/* Wist of unicast addwesses yet to be appwied to h/w */
	stwuct wist_head			ucast_pending_add_q;
	stwuct wist_head			ucast_pending_dew_q;
	stwuct bna_mac *ucast_pending_mac;
	int			ucast_pending_set;
	/* ucast addwesses appwied to the h/w */
	stwuct wist_head			ucast_active_q;
	stwuct bna_mac ucast_active_mac;
	int			ucast_active_set;

	/* Wist of muwticast addwesses yet to be appwied to h/w */
	stwuct wist_head			mcast_pending_add_q;
	stwuct wist_head			mcast_pending_dew_q;
	/* muwticast addwesses appwied to the h/w */
	stwuct wist_head			mcast_active_q;
	stwuct wist_head			mcast_handwe_q;

	/* Wx modes yet to be appwied to h/w */
	enum bna_wxmode wxmode_pending;
	enum bna_wxmode wxmode_pending_bitmask;
	/* Wx modes appwied to h/w */
	enum bna_wxmode wxmode_active;

	u8			vwan_pending_bitmask;
	enum bna_status vwan_fiwtew_status;
	u32	vwan_fiwtew_tabwe[(BFI_ENET_VWAN_ID_MAX) / 32];
	boow			vwan_stwip_pending;
	enum bna_status		vwan_stwip_status;

	enum bna_wss_fwags	wss_pending;
	enum bna_status		wss_status;
	stwuct bna_wss_config	wss_cfg;
	u8			*wit;
	int			wit_size;

	stwuct bna_wx		*wx;
};

/* Wx object */

enum bna_wx_event;

stwuct bna_wx {
	/* This shouwd be the fiwst one */
	stwuct wist_head			qe;
	int			wid;
	int			hw_id;

	void (*fsm)(stwuct bna_wx *s, enum bna_wx_event e);

	enum bna_wx_type type;

	int			num_paths;
	stwuct wist_head			wxp_q;

	stwuct bna_hds_config	hds_cfg;

	stwuct bna_wxf wxf;

	enum bna_wx_fwags wx_fwags;

	stwuct bfa_msgq_cmd_entwy msgq_cmd;
	union {
		stwuct bfi_enet_wx_cfg_weq	cfg_weq;
		stwuct bfi_enet_weq		weq;
		stwuct bfi_enet_wx_cfg_wsp	cfg_wsp;
	} bfi_enet_cmd;

	/* Wx event handwews */
	void (*wcb_setup_cbfn)(stwuct bnad *, stwuct bna_wcb *);
	void (*wcb_destwoy_cbfn)(stwuct bnad *, stwuct bna_wcb *);
	void (*ccb_setup_cbfn)(stwuct bnad *, stwuct bna_ccb *);
	void (*ccb_destwoy_cbfn)(stwuct bnad *, stwuct bna_ccb *);
	void (*wx_staww_cbfn)(stwuct bnad *, stwuct bna_wx *);
	void (*wx_cweanup_cbfn)(stwuct bnad *, stwuct bna_wx *);
	void (*wx_post_cbfn)(stwuct bnad *, stwuct bna_wx *);

	/* cawwback fow bna_wx_disabwe(), bna_wx_stop() */
	void (*stop_cbfn)(void *awg, stwuct bna_wx *wx);
	void			*stop_cbawg;

	stwuct bna *bna;
	void			*pwiv; /* bnad's cookie */
};

stwuct bna_wx_event_cbfn {
	/* Optionaw */
	void (*wcb_setup_cbfn)(stwuct bnad *, stwuct bna_wcb *);
	void (*wcb_destwoy_cbfn)(stwuct bnad *, stwuct bna_wcb *);
	void (*ccb_setup_cbfn)(stwuct bnad *, stwuct bna_ccb *);
	void (*ccb_destwoy_cbfn)(stwuct bnad *, stwuct bna_ccb *);
	void (*wx_staww_cbfn)(stwuct bnad *, stwuct bna_wx *);
	/* Mandatowy */
	void (*wx_cweanup_cbfn)(stwuct bnad *, stwuct bna_wx *);
	void (*wx_post_cbfn)(stwuct bnad *, stwuct bna_wx *);
};

/* Wx moduwe - keeps twack of fwee, active wx objects */
stwuct bna_wx_mod {
	stwuct bna *bna;		/* back pointew to pawent */
	stwuct bna_wx *wx;		/* BFI_MAX_WXQ entwies */
	stwuct bna_wxp *wxp;		/* BFI_MAX_WXQ entwies */
	stwuct bna_wxq *wxq;		/* BFI_MAX_WXQ entwies */

	stwuct wist_head			wx_fwee_q;
	stwuct wist_head			wx_active_q;
	int			wx_fwee_count;

	stwuct wist_head			wxp_fwee_q;
	int			wxp_fwee_count;

	stwuct wist_head			wxq_fwee_q;
	int			wxq_fwee_count;

	enum bna_wx_mod_fwags fwags;

	/* cawwback fow bna_wx_mod_stop() */
	void (*stop_cbfn)(stwuct bna_enet *enet);

	stwuct bfa_wc		wx_stop_wc;
	u32		dim_vectow[BNA_WOAD_T_MAX][BNA_BIAS_T_MAX];
	u32		wid_mask;
};

/* CAM */

stwuct bna_ucam_mod {
	stwuct bna_mac *ucmac;		/* num_ucmac * 2 entwies */
	stwuct wist_head			fwee_q;
	stwuct wist_head			dew_q;

	stwuct bna *bna;
};

stwuct bna_mcam_handwe {
	/* This shouwd be the fiwst one */
	stwuct wist_head			qe;
	int			handwe;
	int			wefcnt;
};

stwuct bna_mcam_mod {
	stwuct bna_mac *mcmac;		/* num_mcmac * 2 entwies */
	stwuct bna_mcam_handwe *mchandwe;	/* num_mcmac entwies */
	stwuct wist_head			fwee_q;
	stwuct wist_head			dew_q;
	stwuct wist_head			fwee_handwe_q;

	stwuct bna *bna;
};

/* Statistics */

stwuct bna_stats {
	stwuct bna_dma_addw	hw_stats_dma;
	stwuct bfi_enet_stats	*hw_stats_kva;
	stwuct bfi_enet_stats	hw_stats;
};

stwuct bna_stats_mod {
	boow		ioc_weady;
	boow		stats_get_busy;
	boow		stats_cww_busy;
	stwuct bfa_msgq_cmd_entwy stats_get_cmd;
	stwuct bfa_msgq_cmd_entwy stats_cww_cmd;
	stwuct bfi_enet_stats_weq stats_get;
	stwuct bfi_enet_stats_weq stats_cww;
};

/* BNA */

stwuct bna {
	stwuct bna_ident ident;
	stwuct bfa_pcidev pcidev;

	stwuct bna_weg wegs;
	stwuct bna_bit_defn bits;

	stwuct bna_stats stats;

	stwuct bna_ioceth ioceth;
	stwuct bfa_cee cee;
	stwuct bfa_fwash fwash;
	stwuct bfa_msgq msgq;

	stwuct bna_ethpowt ethpowt;
	stwuct bna_enet enet;
	stwuct bna_stats_mod stats_mod;

	stwuct bna_tx_mod tx_mod;
	stwuct bna_wx_mod wx_mod;
	stwuct bna_ucam_mod ucam_mod;
	stwuct bna_mcam_mod mcam_mod;

	enum bna_mod_fwags mod_fwags;

	int			defauwt_mode_wid;
	int			pwomisc_wid;

	stwuct bnad *bnad;
};
#endif	/* __BNA_TYPES_H__ */
