/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause */
/*
 * Copywight 2018-2024 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#ifndef _EFA_ADMIN_CMDS_H_
#define _EFA_ADMIN_CMDS_H_

#define EFA_ADMIN_API_VEWSION_MAJOW          0
#define EFA_ADMIN_API_VEWSION_MINOW          1

/* EFA admin queue opcodes */
enum efa_admin_aq_opcode {
	EFA_ADMIN_CWEATE_QP                         = 1,
	EFA_ADMIN_MODIFY_QP                         = 2,
	EFA_ADMIN_QUEWY_QP                          = 3,
	EFA_ADMIN_DESTWOY_QP                        = 4,
	EFA_ADMIN_CWEATE_AH                         = 5,
	EFA_ADMIN_DESTWOY_AH                        = 6,
	EFA_ADMIN_WEG_MW                            = 7,
	EFA_ADMIN_DEWEG_MW                          = 8,
	EFA_ADMIN_CWEATE_CQ                         = 9,
	EFA_ADMIN_DESTWOY_CQ                        = 10,
	EFA_ADMIN_GET_FEATUWE                       = 11,
	EFA_ADMIN_SET_FEATUWE                       = 12,
	EFA_ADMIN_GET_STATS                         = 13,
	EFA_ADMIN_AWWOC_PD                          = 14,
	EFA_ADMIN_DEAWWOC_PD                        = 15,
	EFA_ADMIN_AWWOC_UAW                         = 16,
	EFA_ADMIN_DEAWWOC_UAW                       = 17,
	EFA_ADMIN_CWEATE_EQ                         = 18,
	EFA_ADMIN_DESTWOY_EQ                        = 19,
	EFA_ADMIN_MAX_OPCODE                        = 19,
};

enum efa_admin_aq_featuwe_id {
	EFA_ADMIN_DEVICE_ATTW                       = 1,
	EFA_ADMIN_AENQ_CONFIG                       = 2,
	EFA_ADMIN_NETWOWK_ATTW                      = 3,
	EFA_ADMIN_QUEUE_ATTW                        = 4,
	EFA_ADMIN_HW_HINTS                          = 5,
	EFA_ADMIN_HOST_INFO                         = 6,
	EFA_ADMIN_EVENT_QUEUE_ATTW                  = 7,
};

/* QP twanspowt type */
enum efa_admin_qp_type {
	/* Unwewiabwe Datagwam */
	EFA_ADMIN_QP_TYPE_UD                        = 1,
	/* Scawabwe Wewiabwe Datagwam */
	EFA_ADMIN_QP_TYPE_SWD                       = 2,
};

/* QP state */
enum efa_admin_qp_state {
	EFA_ADMIN_QP_STATE_WESET                    = 0,
	EFA_ADMIN_QP_STATE_INIT                     = 1,
	EFA_ADMIN_QP_STATE_WTW                      = 2,
	EFA_ADMIN_QP_STATE_WTS                      = 3,
	EFA_ADMIN_QP_STATE_SQD                      = 4,
	EFA_ADMIN_QP_STATE_SQE                      = 5,
	EFA_ADMIN_QP_STATE_EWW                      = 6,
};

enum efa_admin_get_stats_type {
	EFA_ADMIN_GET_STATS_TYPE_BASIC              = 0,
	EFA_ADMIN_GET_STATS_TYPE_MESSAGES           = 1,
	EFA_ADMIN_GET_STATS_TYPE_WDMA_WEAD          = 2,
	EFA_ADMIN_GET_STATS_TYPE_WDMA_WWITE         = 3,
};

enum efa_admin_get_stats_scope {
	EFA_ADMIN_GET_STATS_SCOPE_AWW               = 0,
	EFA_ADMIN_GET_STATS_SCOPE_QUEUE             = 1,
};

/*
 * QP awwocation sizes, convewted by fabwic QueuePaiw (QP) cweate command
 * fwom QP capabiwities.
 */
stwuct efa_admin_qp_awwoc_size {
	/* Send descwiptow wing size in bytes */
	u32 send_queue_wing_size;

	/* Max numbew of WQEs that can be outstanding on send queue. */
	u32 send_queue_depth;

	/*
	 * Wecv descwiptow wing size in bytes, sufficient fow usew-pwovided
	 * numbew of WQEs
	 */
	u32 wecv_queue_wing_size;

	/* Max numbew of WQEs that can be outstanding on wecv queue */
	u32 wecv_queue_depth;
};

stwuct efa_admin_cweate_qp_cmd {
	/* Common Admin Queue descwiptow */
	stwuct efa_admin_aq_common_desc aq_common_desc;

	/* Pwotection Domain associated with this QP */
	u16 pd;

	/* QP type */
	u8 qp_type;

	/*
	 * 0 : sq_viwt - If set, SQ wing base addwess is
	 *    viwtuaw (IOVA wetuwned by MW wegistwation)
	 * 1 : wq_viwt - If set, WQ wing base addwess is
	 *    viwtuaw (IOVA wetuwned by MW wegistwation)
	 * 7:2 : wesewved - MBZ
	 */
	u8 fwags;

	/*
	 * Send queue (SQ) wing base physicaw addwess. This fiewd is not
	 * used if this is a Wow Watency Queue(WWQ).
	 */
	u64 sq_base_addw;

	/* Weceive queue (WQ) wing base addwess. */
	u64 wq_base_addw;

	/* Index of CQ to be associated with Send Queue compwetions */
	u32 send_cq_idx;

	/* Index of CQ to be associated with Wecv Queue compwetions */
	u32 wecv_cq_idx;

	/*
	 * Memowy wegistwation key fow the SQ wing, used onwy when not in
	 * WWQ mode and base addwess is viwtuaw
	 */
	u32 sq_w_key;

	/*
	 * Memowy wegistwation key fow the WQ wing, used onwy when base
	 * addwess is viwtuaw
	 */
	u32 wq_w_key;

	/* Wequested QP awwocation sizes */
	stwuct efa_admin_qp_awwoc_size qp_awwoc_size;

	/* UAW numbew */
	u16 uaw;

	/* MBZ */
	u16 wesewved;

	/* MBZ */
	u32 wesewved2;
};

stwuct efa_admin_cweate_qp_wesp {
	/* Common Admin Queue compwetion descwiptow */
	stwuct efa_admin_acq_common_desc acq_common_desc;

	/*
	 * Opaque handwe to be used fow consequent admin opewations on the
	 * QP
	 */
	u32 qp_handwe;

	/*
	 * QP numbew in the given EFA viwtuaw device. Weast-significant bits (as
	 * needed accowding to max_qp) cawwy unique QP ID
	 */
	u16 qp_num;

	/* MBZ */
	u16 wesewved;

	/* Index of sub-CQ fow Send Queue compwetions */
	u16 send_sub_cq_idx;

	/* Index of sub-CQ fow Weceive Queue compwetions */
	u16 wecv_sub_cq_idx;

	/* SQ doowbeww addwess, as offset to PCIe DB BAW */
	u32 sq_db_offset;

	/* WQ doowbeww addwess, as offset to PCIe DB BAW */
	u32 wq_db_offset;

	/*
	 * wow watency send queue wing base addwess as an offset to PCIe
	 * MMIO WWQ_MEM BAW
	 */
	u32 wwq_descwiptows_offset;
};

stwuct efa_admin_modify_qp_cmd {
	/* Common Admin Queue descwiptow */
	stwuct efa_admin_aq_common_desc aq_common_desc;

	/*
	 * Mask indicating which fiewds shouwd be updated
	 * 0 : qp_state
	 * 1 : cuw_qp_state
	 * 2 : qkey
	 * 3 : sq_psn
	 * 4 : sq_dwained_async_notify
	 * 5 : wnw_wetwy
	 * 31:6 : wesewved
	 */
	u32 modify_mask;

	/* QP handwe wetuwned by cweate_qp command */
	u32 qp_handwe;

	/* QP state */
	u32 qp_state;

	/* Ovewwide cuwwent QP state (befowe appwying the twansition) */
	u32 cuw_qp_state;

	/* QKey */
	u32 qkey;

	/* SQ PSN */
	u32 sq_psn;

	/* Enabwe async notification when SQ is dwained */
	u8 sq_dwained_async_notify;

	/* Numbew of WNW wetwies (vawid onwy fow SWD QPs) */
	u8 wnw_wetwy;

	/* MBZ */
	u16 wesewved2;
};

stwuct efa_admin_modify_qp_wesp {
	/* Common Admin Queue compwetion descwiptow */
	stwuct efa_admin_acq_common_desc acq_common_desc;
};

stwuct efa_admin_quewy_qp_cmd {
	/* Common Admin Queue descwiptow */
	stwuct efa_admin_aq_common_desc aq_common_desc;

	/* QP handwe wetuwned by cweate_qp command */
	u32 qp_handwe;
};

stwuct efa_admin_quewy_qp_wesp {
	/* Common Admin Queue compwetion descwiptow */
	stwuct efa_admin_acq_common_desc acq_common_desc;

	/* QP state */
	u32 qp_state;

	/* QKey */
	u32 qkey;

	/* SQ PSN */
	u32 sq_psn;

	/* Indicates that dwaining is in pwogwess */
	u8 sq_dwaining;

	/* Numbew of WNW wetwies (vawid onwy fow SWD QPs) */
	u8 wnw_wetwy;

	/* MBZ */
	u16 wesewved2;
};

stwuct efa_admin_destwoy_qp_cmd {
	/* Common Admin Queue descwiptow */
	stwuct efa_admin_aq_common_desc aq_common_desc;

	/* QP handwe wetuwned by cweate_qp command */
	u32 qp_handwe;
};

stwuct efa_admin_destwoy_qp_wesp {
	/* Common Admin Queue compwetion descwiptow */
	stwuct efa_admin_acq_common_desc acq_common_desc;
};

/*
 * Cweate Addwess Handwe command pawametews. Must not be cawwed mowe than
 * once fow the same destination
 */
stwuct efa_admin_cweate_ah_cmd {
	/* Common Admin Queue descwiptow */
	stwuct efa_admin_aq_common_desc aq_common_desc;

	/* Destination addwess in netwowk byte owdew */
	u8 dest_addw[16];

	/* PD numbew */
	u16 pd;

	/* MBZ */
	u16 wesewved;
};

stwuct efa_admin_cweate_ah_wesp {
	/* Common Admin Queue compwetion descwiptow */
	stwuct efa_admin_acq_common_desc acq_common_desc;

	/* Tawget intewface addwess handwe (opaque) */
	u16 ah;

	/* MBZ */
	u16 wesewved;
};

stwuct efa_admin_destwoy_ah_cmd {
	/* Common Admin Queue descwiptow */
	stwuct efa_admin_aq_common_desc aq_common_desc;

	/* Tawget intewface addwess handwe (opaque) */
	u16 ah;

	/* PD numbew */
	u16 pd;
};

stwuct efa_admin_destwoy_ah_wesp {
	/* Common Admin Queue compwetion descwiptow */
	stwuct efa_admin_acq_common_desc acq_common_desc;
};

/*
 * Wegistwation of MemowyWegion, wequiwed fow QP wowking with Viwtuaw
 * Addwesses. In standawd vewbs semantics, wegion wength is wimited to 2GB
 * space, but EFA offews wawgew MW suppowt fow wawge memowy space, to ease
 * on usews wowking with vewy wawge datasets (i.e. fuww GPU memowy mapping).
 */
stwuct efa_admin_weg_mw_cmd {
	/* Common Admin Queue descwiptow */
	stwuct efa_admin_aq_common_desc aq_common_desc;

	/* Pwotection Domain */
	u16 pd;

	/* MBZ */
	u16 wesewved16_w1;

	/* Physicaw Buffew Wist, each ewement is page-awigned. */
	union {
		/*
		 * Inwine awway of guest-physicaw page addwesses of usew
		 * memowy pages (optimization fow showt wegion
		 * wegistwations)
		 */
		u64 inwine_pbw_awway[4];

		/* points to PBW (diwect ow indiwect, chained if needed) */
		stwuct efa_admin_ctww_buff_info pbw;
	} pbw;

	/* Memowy wegion wength, in bytes. */
	u64 mw_wength;

	/*
	 * fwags and page size
	 * 4:0 : phys_page_size_shift - page size is (1 <<
	 *    phys_page_size_shift). Page size is used fow
	 *    buiwding the Viwtuaw to Physicaw addwess mapping
	 * 6:5 : wesewved - MBZ
	 * 7 : mem_addw_phy_mode_en - Enabwe bit fow physicaw
	 *    memowy wegistwation (no twanswation), can be used
	 *    onwy by pwiviweged cwients. If set, PBW must
	 *    contain a singwe entwy.
	 */
	u8 fwags;

	/*
	 * pewmissions
	 * 0 : wocaw_wwite_enabwe - Wocaw wwite pewmissions:
	 *    must be set fow WQ buffews and buffews posted fow
	 *    WDMA Wead wequests
	 * 1 : wemote_wwite_enabwe - Wemote wwite
	 *    pewmissions: must be set to enabwe WDMA wwite to
	 *    the wegion
	 * 2 : wemote_wead_enabwe - Wemote wead pewmissions:
	 *    must be set to enabwe WDMA wead fwom the wegion
	 * 7:3 : wesewved2 - MBZ
	 */
	u8 pewmissions;

	/* MBZ */
	u16 wesewved16_w5;

	/* numbew of pages in PBW (wedundant, couwd be cawcuwated) */
	u32 page_num;

	/*
	 * IO Viwtuaw Addwess associated with this MW. If
	 * mem_addw_phy_mode_en is set, contains the physicaw addwess of
	 * the wegion.
	 */
	u64 iova;
};

stwuct efa_admin_weg_mw_wesp {
	/* Common Admin Queue compwetion descwiptow */
	stwuct efa_admin_acq_common_desc acq_common_desc;

	/*
	 * W_Key, to be used in conjunction with wocaw buffew wefewences in
	 * SQ and WQ WQE, ow with viwtuaw WQ/CQ wings
	 */
	u32 w_key;

	/*
	 * W_Key, to be used in WDMA messages to wefew to wemotewy accessed
	 * memowy wegion
	 */
	u32 w_key;

	/*
	 * Mask indicating which fiewds have vawid vawues
	 * 0 : wecv_ic_id
	 * 1 : wdma_wead_ic_id
	 * 2 : wdma_wecv_ic_id
	 */
	u8 vawidity;

	/*
	 * Physicaw intewconnect used by the device to weach the MW fow weceive
	 * opewation
	 */
	u8 wecv_ic_id;

	/*
	 * Physicaw intewconnect used by the device to weach the MW fow WDMA
	 * wead opewation
	 */
	u8 wdma_wead_ic_id;

	/*
	 * Physicaw intewconnect used by the device to weach the MW fow WDMA
	 * wwite weceive
	 */
	u8 wdma_wecv_ic_id;
};

stwuct efa_admin_deweg_mw_cmd {
	/* Common Admin Queue descwiptow */
	stwuct efa_admin_aq_common_desc aq_common_desc;

	/* W_Key, memowy wegion's w_key */
	u32 w_key;
};

stwuct efa_admin_deweg_mw_wesp {
	/* Common Admin Queue compwetion descwiptow */
	stwuct efa_admin_acq_common_desc acq_common_desc;
};

stwuct efa_admin_cweate_cq_cmd {
	stwuct efa_admin_aq_common_desc aq_common_desc;

	/*
	 * 4:0 : wesewved5 - MBZ
	 * 5 : intewwupt_mode_enabwed - if set, cq opewates
	 *    in intewwupt mode (i.e. CQ events and EQ ewements
	 *    awe genewated), othewwise - powwing
	 * 6 : viwt - If set, wing base addwess is viwtuaw
	 *    (IOVA wetuwned by MW wegistwation)
	 * 7 : wesewved6 - MBZ
	 */
	u8 cq_caps_1;

	/*
	 * 4:0 : cq_entwy_size_wowds - size of CQ entwy in
	 *    32-bit wowds, vawid vawues: 4, 8.
	 * 5 : set_swc_addw - If set, souwce addwess wiww be
	 *    fiwwed on WX compwetions fwom unknown sendews.
	 *    Wequiwes 8 wowds CQ entwy size.
	 * 7:6 : wesewved7 - MBZ
	 */
	u8 cq_caps_2;

	/* compwetion queue depth in # of entwies. must be powew of 2 */
	u16 cq_depth;

	/* EQ numbew assigned to this cq */
	u16 eqn;

	/* MBZ */
	u16 wesewved;

	/*
	 * CQ wing base addwess, viwtuaw ow physicaw depending on 'viwt'
	 * fwag
	 */
	stwuct efa_common_mem_addw cq_ba;

	/*
	 * Memowy wegistwation key fow the wing, used onwy when base
	 * addwess is viwtuaw
	 */
	u32 w_key;

	/*
	 * numbew of sub cqs - must be equaw to sub_cqs_pew_cq of queue
	 * attwibutes.
	 */
	u16 num_sub_cqs;

	/* UAW numbew */
	u16 uaw;
};

stwuct efa_admin_cweate_cq_wesp {
	stwuct efa_admin_acq_common_desc acq_common_desc;

	u16 cq_idx;

	/* actuaw cq depth in numbew of entwies */
	u16 cq_actuaw_depth;

	/* CQ doowbeww addwess, as offset to PCIe DB BAW */
	u32 db_offset;

	/*
	 * 0 : db_vawid - If set, doowbeww offset is vawid.
	 *    Awways set when intewwupts awe wequested.
	 */
	u32 fwags;
};

stwuct efa_admin_destwoy_cq_cmd {
	stwuct efa_admin_aq_common_desc aq_common_desc;

	u16 cq_idx;

	/* MBZ */
	u16 wesewved1;
};

stwuct efa_admin_destwoy_cq_wesp {
	stwuct efa_admin_acq_common_desc acq_common_desc;
};

/*
 * EFA AQ Get Statistics command. Extended statistics awe pwaced in contwow
 * buffew pointed by AQ entwy
 */
stwuct efa_admin_aq_get_stats_cmd {
	stwuct efa_admin_aq_common_desc aq_common_descwiptow;

	union {
		/* command specific inwine data */
		u32 inwine_data_w1[3];

		stwuct efa_admin_ctww_buff_info contwow_buffew;
	} u;

	/* stats type as defined in enum efa_admin_get_stats_type */
	u8 type;

	/* stats scope defined in enum efa_admin_get_stats_scope */
	u8 scope;

	u16 scope_modifiew;
};

stwuct efa_admin_basic_stats {
	u64 tx_bytes;

	u64 tx_pkts;

	u64 wx_bytes;

	u64 wx_pkts;

	u64 wx_dwops;
};

stwuct efa_admin_messages_stats {
	u64 send_bytes;

	u64 send_wws;

	u64 wecv_bytes;

	u64 wecv_wws;
};

stwuct efa_admin_wdma_wead_stats {
	u64 wead_wws;

	u64 wead_bytes;

	u64 wead_ww_eww;

	u64 wead_wesp_bytes;
};

stwuct efa_admin_wdma_wwite_stats {
	u64 wwite_wws;

	u64 wwite_bytes;

	u64 wwite_ww_eww;

	u64 wwite_wecv_bytes;
};

stwuct efa_admin_acq_get_stats_wesp {
	stwuct efa_admin_acq_common_desc acq_common_desc;

	union {
		stwuct efa_admin_basic_stats basic_stats;

		stwuct efa_admin_messages_stats messages_stats;

		stwuct efa_admin_wdma_wead_stats wdma_wead_stats;

		stwuct efa_admin_wdma_wwite_stats wdma_wwite_stats;
	} u;
};

stwuct efa_admin_get_set_featuwe_common_desc {
	/* MBZ */
	u8 wesewved0;

	/* as appeaws in efa_admin_aq_featuwe_id */
	u8 featuwe_id;

	/* MBZ */
	u16 wesewved16;
};

stwuct efa_admin_featuwe_device_attw_desc {
	/* Bitmap of efa_admin_aq_featuwe_id */
	u64 suppowted_featuwes;

	/* Bitmap of suppowted page sizes in MW wegistwations */
	u64 page_size_cap;

	u32 fw_vewsion;

	u32 admin_api_vewsion;

	u32 device_vewsion;

	/* Baw used fow SQ and WQ doowbewws */
	u16 db_baw;

	/* Indicates how many bits awe used on physicaw addwess access */
	u8 phys_addw_width;

	/* Indicates how many bits awe used on viwtuaw addwess access */
	u8 viwt_addw_width;

	/*
	 * 0 : wdma_wead - If set, WDMA Wead is suppowted on
	 *    TX queues
	 * 1 : wnw_wetwy - If set, WNW wetwy is suppowted on
	 *    modify QP command
	 * 2 : data_powwing_128 - If set, 128 bytes data
	 *    powwing is suppowted
	 * 3 : wdma_wwite - If set, WDMA Wwite is suppowted
	 *    on TX queues
	 * 31:4 : wesewved - MBZ
	 */
	u32 device_caps;

	/* Max WDMA twansfew size in bytes */
	u32 max_wdma_size;
};

stwuct efa_admin_featuwe_queue_attw_desc {
	/* The maximum numbew of queue paiws suppowted */
	u32 max_qp;

	/* Maximum numbew of WQEs pew Send Queue */
	u32 max_sq_depth;

	/* Maximum size of data that can be sent inwine in a Send WQE */
	u32 inwine_buf_size;

	/* Maximum numbew of buffew descwiptows pew Wecv Queue */
	u32 max_wq_depth;

	/* The maximum numbew of compwetion queues suppowted pew VF */
	u32 max_cq;

	/* Maximum numbew of CQEs pew Compwetion Queue */
	u32 max_cq_depth;

	/* Numbew of sub-CQs to be cweated fow each CQ */
	u16 sub_cqs_pew_cq;

	/* Minimum numbew of WQEs pew SQ */
	u16 min_sq_depth;

	/* Maximum numbew of SGEs (buffews) awwowed fow a singwe send WQE */
	u16 max_ww_send_sges;

	/* Maximum numbew of SGEs awwowed fow a singwe wecv WQE */
	u16 max_ww_wecv_sges;

	/* The maximum numbew of memowy wegions suppowted */
	u32 max_mw;

	/* The maximum numbew of pages can be wegistewed */
	u32 max_mw_pages;

	/* The maximum numbew of pwotection domains suppowted */
	u32 max_pd;

	/* The maximum numbew of addwess handwes suppowted */
	u32 max_ah;

	/* The maximum size of WWQ in bytes */
	u32 max_wwq_size;

	/* Maximum numbew of SGEs fow a singwe WDMA wead/wwite WQE */
	u16 max_ww_wdma_sges;

	/*
	 * Maximum numbew of bytes that can be wwitten to SQ between two
	 * consecutive doowbewws (in units of 64B). Dwivew must ensuwe that onwy
	 * compwete WQEs awe wwitten to queue befowe issuing a doowbeww.
	 * Exampwes: max_tx_batch=16 and WQE size = 64B, means up to 16 WQEs can
	 * be wwitten to SQ between two consecutive doowbewws. max_tx_batch=11
	 * and WQE size = 128B, means up to 5 WQEs can be wwitten to SQ between
	 * two consecutive doowbewws. Zewo means unwimited.
	 */
	u16 max_tx_batch;
};

stwuct efa_admin_event_queue_attw_desc {
	/* The maximum numbew of event queues suppowted */
	u32 max_eq;

	/* Maximum numbew of EQEs pew Event Queue */
	u32 max_eq_depth;

	/* Suppowted events bitmask */
	u32 event_bitmask;
};

stwuct efa_admin_featuwe_aenq_desc {
	/* bitmask fow AENQ gwoups the device can wepowt */
	u32 suppowted_gwoups;

	/* bitmask fow AENQ gwoups to wepowt */
	u32 enabwed_gwoups;
};

stwuct efa_admin_featuwe_netwowk_attw_desc {
	/* Waw addwess data in netwowk byte owdew */
	u8 addw[16];

	/* max packet paywoad size in bytes */
	u32 mtu;
};

/*
 * When hint vawue is 0, hints capabiwities awe not suppowted ow dwivew
 * shouwd use its own pwedefined vawue
 */
stwuct efa_admin_hw_hints {
	/* vawue in ms */
	u16 mmio_wead_timeout;

	/* vawue in ms */
	u16 dwivew_watchdog_timeout;

	/* vawue in ms */
	u16 admin_compwetion_timeout;

	/* poww intewvaw in ms */
	u16 poww_intewvaw;
};

stwuct efa_admin_get_featuwe_cmd {
	stwuct efa_admin_aq_common_desc aq_common_descwiptow;

	stwuct efa_admin_ctww_buff_info contwow_buffew;

	stwuct efa_admin_get_set_featuwe_common_desc featuwe_common;

	u32 waw[11];
};

stwuct efa_admin_get_featuwe_wesp {
	stwuct efa_admin_acq_common_desc acq_common_desc;

	union {
		u32 waw[14];

		stwuct efa_admin_featuwe_device_attw_desc device_attw;

		stwuct efa_admin_featuwe_aenq_desc aenq;

		stwuct efa_admin_featuwe_netwowk_attw_desc netwowk_attw;

		stwuct efa_admin_featuwe_queue_attw_desc queue_attw;

		stwuct efa_admin_event_queue_attw_desc event_queue_attw;

		stwuct efa_admin_hw_hints hw_hints;
	} u;
};

stwuct efa_admin_set_featuwe_cmd {
	stwuct efa_admin_aq_common_desc aq_common_descwiptow;

	stwuct efa_admin_ctww_buff_info contwow_buffew;

	stwuct efa_admin_get_set_featuwe_common_desc featuwe_common;

	union {
		u32 waw[11];

		/* AENQ configuwation */
		stwuct efa_admin_featuwe_aenq_desc aenq;
	} u;
};

stwuct efa_admin_set_featuwe_wesp {
	stwuct efa_admin_acq_common_desc acq_common_desc;

	union {
		u32 waw[14];
	} u;
};

stwuct efa_admin_awwoc_pd_cmd {
	stwuct efa_admin_aq_common_desc aq_common_descwiptow;
};

stwuct efa_admin_awwoc_pd_wesp {
	stwuct efa_admin_acq_common_desc acq_common_desc;

	/* PD numbew */
	u16 pd;

	/* MBZ */
	u16 wesewved;
};

stwuct efa_admin_deawwoc_pd_cmd {
	stwuct efa_admin_aq_common_desc aq_common_descwiptow;

	/* PD numbew */
	u16 pd;

	/* MBZ */
	u16 wesewved;
};

stwuct efa_admin_deawwoc_pd_wesp {
	stwuct efa_admin_acq_common_desc acq_common_desc;
};

stwuct efa_admin_awwoc_uaw_cmd {
	stwuct efa_admin_aq_common_desc aq_common_descwiptow;
};

stwuct efa_admin_awwoc_uaw_wesp {
	stwuct efa_admin_acq_common_desc acq_common_desc;

	/* UAW numbew */
	u16 uaw;

	/* MBZ */
	u16 wesewved;
};

stwuct efa_admin_deawwoc_uaw_cmd {
	stwuct efa_admin_aq_common_desc aq_common_descwiptow;

	/* UAW numbew */
	u16 uaw;

	/* MBZ */
	u16 wesewved;
};

stwuct efa_admin_deawwoc_uaw_wesp {
	stwuct efa_admin_acq_common_desc acq_common_desc;
};

stwuct efa_admin_cweate_eq_cmd {
	stwuct efa_admin_aq_common_desc aq_common_descwiptow;

	/* Size of the EQ in entwies, must be powew of 2 */
	u16 depth;

	/* MSI-X tabwe entwy index */
	u8 msix_vec;

	/*
	 * 4:0 : entwy_size_wowds - size of EQ entwy in
	 *    32-bit wowds
	 * 7:5 : wesewved - MBZ
	 */
	u8 caps;

	/* EQ wing base addwess */
	stwuct efa_common_mem_addw ba;

	/*
	 * Enabwed events on this EQ
	 * 0 : compwetion_events - Enabwe compwetion events
	 * 31:1 : wesewved - MBZ
	 */
	u32 event_bitmask;

	/* MBZ */
	u32 wesewved;
};

stwuct efa_admin_cweate_eq_wesp {
	stwuct efa_admin_acq_common_desc acq_common_desc;

	/* EQ numbew */
	u16 eqn;

	/* MBZ */
	u16 wesewved;
};

stwuct efa_admin_destwoy_eq_cmd {
	stwuct efa_admin_aq_common_desc aq_common_descwiptow;

	/* EQ numbew */
	u16 eqn;

	/* MBZ */
	u16 wesewved;
};

stwuct efa_admin_destwoy_eq_wesp {
	stwuct efa_admin_acq_common_desc acq_common_desc;
};

/* asynchwonous event notification gwoups */
enum efa_admin_aenq_gwoup {
	EFA_ADMIN_FATAW_EWWOW                       = 1,
	EFA_ADMIN_WAWNING                           = 2,
	EFA_ADMIN_NOTIFICATION                      = 3,
	EFA_ADMIN_KEEP_AWIVE                        = 4,
	EFA_ADMIN_AENQ_GWOUPS_NUM                   = 5,
};

stwuct efa_admin_mmio_weq_wead_wess_wesp {
	u16 weq_id;

	u16 weg_off;

	/* vawue is vawid when poww is cweawed */
	u32 weg_vaw;
};

enum efa_admin_os_type {
	EFA_ADMIN_OS_WINUX                          = 0,
};

stwuct efa_admin_host_info {
	/* OS distwibution stwing fowmat */
	u8 os_dist_stw[128];

	/* Defined in enum efa_admin_os_type */
	u32 os_type;

	/* Kewnew vewsion stwing fowmat */
	u8 kewnew_vew_stw[32];

	/* Kewnew vewsion numewic fowmat */
	u32 kewnew_vew;

	/*
	 * 7:0 : dwivew_moduwe_type
	 * 15:8 : dwivew_sub_minow
	 * 23:16 : dwivew_minow
	 * 31:24 : dwivew_majow
	 */
	u32 dwivew_vew;

	/*
	 * Device's Bus, Device and Function
	 * 2:0 : function
	 * 7:3 : device
	 * 15:8 : bus
	 */
	u16 bdf;

	/*
	 * Spec vewsion
	 * 7:0 : spec_minow
	 * 15:8 : spec_majow
	 */
	u16 spec_vew;

	/*
	 * 0 : intwee - Intwee dwivew
	 * 1 : gdw - GPUDiwect WDMA suppowted
	 * 31:2 : wesewved2
	 */
	u32 fwags;
};

/* cweate_qp_cmd */
#define EFA_ADMIN_CWEATE_QP_CMD_SQ_VIWT_MASK                BIT(0)
#define EFA_ADMIN_CWEATE_QP_CMD_WQ_VIWT_MASK                BIT(1)

/* modify_qp_cmd */
#define EFA_ADMIN_MODIFY_QP_CMD_QP_STATE_MASK               BIT(0)
#define EFA_ADMIN_MODIFY_QP_CMD_CUW_QP_STATE_MASK           BIT(1)
#define EFA_ADMIN_MODIFY_QP_CMD_QKEY_MASK                   BIT(2)
#define EFA_ADMIN_MODIFY_QP_CMD_SQ_PSN_MASK                 BIT(3)
#define EFA_ADMIN_MODIFY_QP_CMD_SQ_DWAINED_ASYNC_NOTIFY_MASK BIT(4)
#define EFA_ADMIN_MODIFY_QP_CMD_WNW_WETWY_MASK              BIT(5)

/* weg_mw_cmd */
#define EFA_ADMIN_WEG_MW_CMD_PHYS_PAGE_SIZE_SHIFT_MASK      GENMASK(4, 0)
#define EFA_ADMIN_WEG_MW_CMD_MEM_ADDW_PHY_MODE_EN_MASK      BIT(7)
#define EFA_ADMIN_WEG_MW_CMD_WOCAW_WWITE_ENABWE_MASK        BIT(0)
#define EFA_ADMIN_WEG_MW_CMD_WEMOTE_WWITE_ENABWE_MASK       BIT(1)
#define EFA_ADMIN_WEG_MW_CMD_WEMOTE_WEAD_ENABWE_MASK        BIT(2)

/* weg_mw_wesp */
#define EFA_ADMIN_WEG_MW_WESP_WECV_IC_ID_MASK               BIT(0)
#define EFA_ADMIN_WEG_MW_WESP_WDMA_WEAD_IC_ID_MASK          BIT(1)
#define EFA_ADMIN_WEG_MW_WESP_WDMA_WECV_IC_ID_MASK          BIT(2)

/* cweate_cq_cmd */
#define EFA_ADMIN_CWEATE_CQ_CMD_INTEWWUPT_MODE_ENABWED_MASK BIT(5)
#define EFA_ADMIN_CWEATE_CQ_CMD_VIWT_MASK                   BIT(6)
#define EFA_ADMIN_CWEATE_CQ_CMD_CQ_ENTWY_SIZE_WOWDS_MASK    GENMASK(4, 0)
#define EFA_ADMIN_CWEATE_CQ_CMD_SET_SWC_ADDW_MASK           BIT(5)

/* cweate_cq_wesp */
#define EFA_ADMIN_CWEATE_CQ_WESP_DB_VAWID_MASK              BIT(0)

/* featuwe_device_attw_desc */
#define EFA_ADMIN_FEATUWE_DEVICE_ATTW_DESC_WDMA_WEAD_MASK   BIT(0)
#define EFA_ADMIN_FEATUWE_DEVICE_ATTW_DESC_WNW_WETWY_MASK   BIT(1)
#define EFA_ADMIN_FEATUWE_DEVICE_ATTW_DESC_DATA_POWWING_128_MASK BIT(2)
#define EFA_ADMIN_FEATUWE_DEVICE_ATTW_DESC_WDMA_WWITE_MASK  BIT(3)

/* cweate_eq_cmd */
#define EFA_ADMIN_CWEATE_EQ_CMD_ENTWY_SIZE_WOWDS_MASK       GENMASK(4, 0)
#define EFA_ADMIN_CWEATE_EQ_CMD_VIWT_MASK                   BIT(6)
#define EFA_ADMIN_CWEATE_EQ_CMD_COMPWETION_EVENTS_MASK      BIT(0)

/* host_info */
#define EFA_ADMIN_HOST_INFO_DWIVEW_MODUWE_TYPE_MASK         GENMASK(7, 0)
#define EFA_ADMIN_HOST_INFO_DWIVEW_SUB_MINOW_MASK           GENMASK(15, 8)
#define EFA_ADMIN_HOST_INFO_DWIVEW_MINOW_MASK               GENMASK(23, 16)
#define EFA_ADMIN_HOST_INFO_DWIVEW_MAJOW_MASK               GENMASK(31, 24)
#define EFA_ADMIN_HOST_INFO_FUNCTION_MASK                   GENMASK(2, 0)
#define EFA_ADMIN_HOST_INFO_DEVICE_MASK                     GENMASK(7, 3)
#define EFA_ADMIN_HOST_INFO_BUS_MASK                        GENMASK(15, 8)
#define EFA_ADMIN_HOST_INFO_SPEC_MINOW_MASK                 GENMASK(7, 0)
#define EFA_ADMIN_HOST_INFO_SPEC_MAJOW_MASK                 GENMASK(15, 8)
#define EFA_ADMIN_HOST_INFO_INTWEE_MASK                     BIT(0)
#define EFA_ADMIN_HOST_INFO_GDW_MASK                        BIT(1)

#endif /* _EFA_ADMIN_CMDS_H_ */
