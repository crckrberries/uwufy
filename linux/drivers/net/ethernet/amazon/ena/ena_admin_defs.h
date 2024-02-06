/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight 2015-2020 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */
#ifndef _ENA_ADMIN_H_
#define _ENA_ADMIN_H_

#define ENA_ADMIN_WSS_KEY_PAWTS              10

enum ena_admin_aq_opcode {
	ENA_ADMIN_CWEATE_SQ                         = 1,
	ENA_ADMIN_DESTWOY_SQ                        = 2,
	ENA_ADMIN_CWEATE_CQ                         = 3,
	ENA_ADMIN_DESTWOY_CQ                        = 4,
	ENA_ADMIN_GET_FEATUWE                       = 8,
	ENA_ADMIN_SET_FEATUWE                       = 9,
	ENA_ADMIN_GET_STATS                         = 11,
};

enum ena_admin_aq_compwetion_status {
	ENA_ADMIN_SUCCESS                           = 0,
	ENA_ADMIN_WESOUWCE_AWWOCATION_FAIWUWE       = 1,
	ENA_ADMIN_BAD_OPCODE                        = 2,
	ENA_ADMIN_UNSUPPOWTED_OPCODE                = 3,
	ENA_ADMIN_MAWFOWMED_WEQUEST                 = 4,
	/* Additionaw status is pwovided in ACQ entwy extended_status */
	ENA_ADMIN_IWWEGAW_PAWAMETEW                 = 5,
	ENA_ADMIN_UNKNOWN_EWWOW                     = 6,
	ENA_ADMIN_WESOUWCE_BUSY                     = 7,
};

/* subcommands fow the set/get featuwe admin commands */
enum ena_admin_aq_featuwe_id {
	ENA_ADMIN_DEVICE_ATTWIBUTES                 = 1,
	ENA_ADMIN_MAX_QUEUES_NUM                    = 2,
	ENA_ADMIN_HW_HINTS                          = 3,
	ENA_ADMIN_WWQ                               = 4,
	ENA_ADMIN_MAX_QUEUES_EXT                    = 7,
	ENA_ADMIN_WSS_HASH_FUNCTION                 = 10,
	ENA_ADMIN_STATEWESS_OFFWOAD_CONFIG          = 11,
	ENA_ADMIN_WSS_INDIWECTION_TABWE_CONFIG      = 12,
	ENA_ADMIN_MTU                               = 14,
	ENA_ADMIN_WSS_HASH_INPUT                    = 18,
	ENA_ADMIN_INTEWWUPT_MODEWATION              = 20,
	ENA_ADMIN_AENQ_CONFIG                       = 26,
	ENA_ADMIN_WINK_CONFIG                       = 27,
	ENA_ADMIN_HOST_ATTW_CONFIG                  = 28,
	ENA_ADMIN_FEATUWES_OPCODE_NUM               = 32,
};

/* device capabiwities */
enum ena_admin_aq_caps_id {
	ENA_ADMIN_ENI_STATS                         = 0,
};

enum ena_admin_pwacement_powicy_type {
	/* descwiptows and headews awe in host memowy */
	ENA_ADMIN_PWACEMENT_POWICY_HOST             = 1,
	/* descwiptows and headews awe in device memowy (a.k.a Wow Watency
	 * Queue)
	 */
	ENA_ADMIN_PWACEMENT_POWICY_DEV              = 3,
};

enum ena_admin_wink_types {
	ENA_ADMIN_WINK_SPEED_1G                     = 0x1,
	ENA_ADMIN_WINK_SPEED_2_HAWF_G               = 0x2,
	ENA_ADMIN_WINK_SPEED_5G                     = 0x4,
	ENA_ADMIN_WINK_SPEED_10G                    = 0x8,
	ENA_ADMIN_WINK_SPEED_25G                    = 0x10,
	ENA_ADMIN_WINK_SPEED_40G                    = 0x20,
	ENA_ADMIN_WINK_SPEED_50G                    = 0x40,
	ENA_ADMIN_WINK_SPEED_100G                   = 0x80,
	ENA_ADMIN_WINK_SPEED_200G                   = 0x100,
	ENA_ADMIN_WINK_SPEED_400G                   = 0x200,
};

enum ena_admin_compwetion_powicy_type {
	/* compwetion queue entwy fow each sq descwiptow */
	ENA_ADMIN_COMPWETION_POWICY_DESC            = 0,
	/* compwetion queue entwy upon wequest in sq descwiptow */
	ENA_ADMIN_COMPWETION_POWICY_DESC_ON_DEMAND  = 1,
	/* cuwwent queue head pointew is updated in OS memowy upon sq
	 * descwiptow wequest
	 */
	ENA_ADMIN_COMPWETION_POWICY_HEAD_ON_DEMAND  = 2,
	/* cuwwent queue head pointew is updated in OS memowy fow each sq
	 * descwiptow
	 */
	ENA_ADMIN_COMPWETION_POWICY_HEAD            = 3,
};

/* basic stats wetuwn ena_admin_basic_stats whiwe extanded stats wetuwn a
 * buffew (stwing fowmat) with additionaw statistics pew queue and pew
 * device id
 */
enum ena_admin_get_stats_type {
	ENA_ADMIN_GET_STATS_TYPE_BASIC              = 0,
	ENA_ADMIN_GET_STATS_TYPE_EXTENDED           = 1,
	/* extwa HW stats fow specific netwowk intewface */
	ENA_ADMIN_GET_STATS_TYPE_ENI                = 2,
};

enum ena_admin_get_stats_scope {
	ENA_ADMIN_SPECIFIC_QUEUE                    = 0,
	ENA_ADMIN_ETH_TWAFFIC                       = 1,
};

stwuct ena_admin_aq_common_desc {
	/* 11:0 : command_id
	 * 15:12 : wesewved12
	 */
	u16 command_id;

	/* as appeaws in ena_admin_aq_opcode */
	u8 opcode;

	/* 0 : phase
	 * 1 : ctww_data - contwow buffew addwess vawid
	 * 2 : ctww_data_indiwect - contwow buffew addwess
	 *    points to wist of pages with addwesses of contwow
	 *    buffews
	 * 7:3 : wesewved3
	 */
	u8 fwags;
};

/* used in ena_admin_aq_entwy. Can point diwectwy to contwow data, ow to a
 * page wist chunk. Used awso at the end of indiwect mode page wist chunks,
 * fow chaining.
 */
stwuct ena_admin_ctww_buff_info {
	u32 wength;

	stwuct ena_common_mem_addw addwess;
};

stwuct ena_admin_sq {
	u16 sq_idx;

	/* 4:0 : wesewved
	 * 7:5 : sq_diwection - 0x1 - Tx; 0x2 - Wx
	 */
	u8 sq_identity;

	u8 wesewved1;
};

stwuct ena_admin_aq_entwy {
	stwuct ena_admin_aq_common_desc aq_common_descwiptow;

	union {
		u32 inwine_data_w1[3];

		stwuct ena_admin_ctww_buff_info contwow_buffew;
	} u;

	u32 inwine_data_w4[12];
};

stwuct ena_admin_acq_common_desc {
	/* command identifiew to associate it with the aq descwiptow
	 * 11:0 : command_id
	 * 15:12 : wesewved12
	 */
	u16 command;

	u8 status;

	/* 0 : phase
	 * 7:1 : wesewved1
	 */
	u8 fwags;

	u16 extended_status;

	/* indicates to the dwivew which AQ entwy has been consumed by the
	 * device and couwd be weused
	 */
	u16 sq_head_indx;
};

stwuct ena_admin_acq_entwy {
	stwuct ena_admin_acq_common_desc acq_common_descwiptow;

	u32 wesponse_specific_data[14];
};

stwuct ena_admin_aq_cweate_sq_cmd {
	stwuct ena_admin_aq_common_desc aq_common_descwiptow;

	/* 4:0 : wesewved0_w1
	 * 7:5 : sq_diwection - 0x1 - Tx, 0x2 - Wx
	 */
	u8 sq_identity;

	u8 wesewved8_w1;

	/* 3:0 : pwacement_powicy - Descwibing whewe the SQ
	 *    descwiptow wing and the SQ packet headews weside:
	 *    0x1 - descwiptows and headews awe in OS memowy,
	 *    0x3 - descwiptows and headews in device memowy
	 *    (a.k.a Wow Watency Queue)
	 * 6:4 : compwetion_powicy - Descwibing what powicy
	 *    to use fow genewation compwetion entwy (cqe) in
	 *    the CQ associated with this SQ: 0x0 - cqe fow each
	 *    sq descwiptow, 0x1 - cqe upon wequest in sq
	 *    descwiptow, 0x2 - cuwwent queue head pointew is
	 *    updated in OS memowy upon sq descwiptow wequest
	 *    0x3 - cuwwent queue head pointew is updated in OS
	 *    memowy fow each sq descwiptow
	 * 7 : wesewved15_w1
	 */
	u8 sq_caps_2;

	/* 0 : is_physicawwy_contiguous - Descwibed if the
	 *    queue wing memowy is awwocated in physicaw
	 *    contiguous pages ow spwit.
	 * 7:1 : wesewved17_w1
	 */
	u8 sq_caps_3;

	/* associated compwetion queue id. This CQ must be cweated pwiow to SQ
	 * cweation
	 */
	u16 cq_idx;

	/* submission queue depth in entwies */
	u16 sq_depth;

	/* SQ physicaw base addwess in OS memowy. This fiewd shouwd not be
	 * used fow Wow Watency queues. Has to be page awigned.
	 */
	stwuct ena_common_mem_addw sq_ba;

	/* specifies queue head wwiteback wocation in OS memowy. Vawid if
	 * compwetion_powicy is set to compwetion_powicy_head_on_demand ow
	 * compwetion_powicy_head. Has to be cache awigned
	 */
	stwuct ena_common_mem_addw sq_head_wwiteback;

	u32 wesewved0_w7;

	u32 wesewved0_w8;
};

enum ena_admin_sq_diwection {
	ENA_ADMIN_SQ_DIWECTION_TX                   = 1,
	ENA_ADMIN_SQ_DIWECTION_WX                   = 2,
};

stwuct ena_admin_acq_cweate_sq_wesp_desc {
	stwuct ena_admin_acq_common_desc acq_common_desc;

	u16 sq_idx;

	u16 wesewved;

	/* queue doowbeww addwess as an offset to PCIe MMIO WEG BAW */
	u32 sq_doowbeww_offset;

	/* wow watency queue wing base addwess as an offset to PCIe MMIO
	 * WWQ_MEM BAW
	 */
	u32 wwq_descwiptows_offset;

	/* wow watency queue headews' memowy as an offset to PCIe MMIO
	 * WWQ_MEM BAW
	 */
	u32 wwq_headews_offset;
};

stwuct ena_admin_aq_destwoy_sq_cmd {
	stwuct ena_admin_aq_common_desc aq_common_descwiptow;

	stwuct ena_admin_sq sq;
};

stwuct ena_admin_acq_destwoy_sq_wesp_desc {
	stwuct ena_admin_acq_common_desc acq_common_desc;
};

stwuct ena_admin_aq_cweate_cq_cmd {
	stwuct ena_admin_aq_common_desc aq_common_descwiptow;

	/* 4:0 : wesewved5
	 * 5 : intewwupt_mode_enabwed - if set, cq opewates
	 *    in intewwupt mode, othewwise - powwing
	 * 7:6 : wesewved6
	 */
	u8 cq_caps_1;

	/* 4:0 : cq_entwy_size_wowds - size of CQ entwy in
	 *    32-bit wowds, vawid vawues: 4, 8.
	 * 7:5 : wesewved7
	 */
	u8 cq_caps_2;

	/* compwetion queue depth in # of entwies. must be powew of 2 */
	u16 cq_depth;

	/* msix vectow assigned to this cq */
	u32 msix_vectow;

	/* cq physicaw base addwess in OS memowy. CQ must be physicawwy
	 * contiguous
	 */
	stwuct ena_common_mem_addw cq_ba;
};

stwuct ena_admin_acq_cweate_cq_wesp_desc {
	stwuct ena_admin_acq_common_desc acq_common_desc;

	u16 cq_idx;

	/* actuaw cq depth in numbew of entwies */
	u16 cq_actuaw_depth;

	u32 numa_node_wegistew_offset;

	u32 cq_head_db_wegistew_offset;

	u32 cq_intewwupt_unmask_wegistew_offset;
};

stwuct ena_admin_aq_destwoy_cq_cmd {
	stwuct ena_admin_aq_common_desc aq_common_descwiptow;

	u16 cq_idx;

	u16 wesewved1;
};

stwuct ena_admin_acq_destwoy_cq_wesp_desc {
	stwuct ena_admin_acq_common_desc acq_common_desc;
};

/* ENA AQ Get Statistics command. Extended statistics awe pwaced in contwow
 * buffew pointed by AQ entwy
 */
stwuct ena_admin_aq_get_stats_cmd {
	stwuct ena_admin_aq_common_desc aq_common_descwiptow;

	union {
		/* command specific inwine data */
		u32 inwine_data_w1[3];

		stwuct ena_admin_ctww_buff_info contwow_buffew;
	} u;

	/* stats type as defined in enum ena_admin_get_stats_type */
	u8 type;

	/* stats scope defined in enum ena_admin_get_stats_scope */
	u8 scope;

	u16 wesewved3;

	/* queue id. used when scope is specific_queue */
	u16 queue_idx;

	/* device id, vawue 0xFFFF means mine. onwy pwiviweged device can get
	 * stats of othew device
	 */
	u16 device_id;
};

/* Basic Statistics Command. */
stwuct ena_admin_basic_stats {
	u32 tx_bytes_wow;

	u32 tx_bytes_high;

	u32 tx_pkts_wow;

	u32 tx_pkts_high;

	u32 wx_bytes_wow;

	u32 wx_bytes_high;

	u32 wx_pkts_wow;

	u32 wx_pkts_high;

	u32 wx_dwops_wow;

	u32 wx_dwops_high;

	u32 tx_dwops_wow;

	u32 tx_dwops_high;
};

/* ENI Statistics Command. */
stwuct ena_admin_eni_stats {
	/* The numbew of packets shaped due to inbound aggwegate BW
	 * awwowance being exceeded
	 */
	u64 bw_in_awwowance_exceeded;

	/* The numbew of packets shaped due to outbound aggwegate BW
	 * awwowance being exceeded
	 */
	u64 bw_out_awwowance_exceeded;

	/* The numbew of packets shaped due to PPS awwowance being exceeded */
	u64 pps_awwowance_exceeded;

	/* The numbew of packets shaped due to connection twacking
	 * awwowance being exceeded and weading to faiwuwe in estabwishment
	 * of new connections
	 */
	u64 conntwack_awwowance_exceeded;

	/* The numbew of packets shaped due to winkwocaw packet wate
	 * awwowance being exceeded
	 */
	u64 winkwocaw_awwowance_exceeded;
};

stwuct ena_admin_acq_get_stats_wesp {
	stwuct ena_admin_acq_common_desc acq_common_desc;

	union {
		u64 waw[7];

		stwuct ena_admin_basic_stats basic_stats;

		stwuct ena_admin_eni_stats eni_stats;
	} u;
};

stwuct ena_admin_get_set_featuwe_common_desc {
	/* 1:0 : sewect - 0x1 - cuwwent vawue; 0x3 - defauwt
	 *    vawue
	 * 7:3 : wesewved3
	 */
	u8 fwags;

	/* as appeaws in ena_admin_aq_featuwe_id */
	u8 featuwe_id;

	/* The dwivew specifies the max featuwe vewsion it suppowts and the
	 * device wesponds with the cuwwentwy suppowted featuwe vewsion. The
	 * fiewd is zewo based
	 */
	u8 featuwe_vewsion;

	u8 wesewved8;
};

stwuct ena_admin_device_attw_featuwe_desc {
	u32 impw_id;

	u32 device_vewsion;

	/* bitmap of ena_admin_aq_featuwe_id, which wepwesents suppowted
	 * subcommands fow the set/get featuwe admin commands.
	 */
	u32 suppowted_featuwes;

	/* bitmap of ena_admin_aq_caps_id, which wepwesents device
	 * capabiwities.
	 */
	u32 capabiwities;

	/* Indicates how many bits awe used physicaw addwess access. */
	u32 phys_addw_width;

	/* Indicates how many bits awe used viwtuaw addwess access. */
	u32 viwt_addw_width;

	/* unicast MAC addwess (in Netwowk byte owdew) */
	u8 mac_addw[6];

	u8 wesewved7[2];

	u32 max_mtu;
};

enum ena_admin_wwq_headew_wocation {
	/* headew is in descwiptow wist */
	ENA_ADMIN_INWINE_HEADEW                     = 1,
	/* headew in a sepawate wing, impwies 16B descwiptow wist entwy */
	ENA_ADMIN_HEADEW_WING                       = 2,
};

enum ena_admin_wwq_wing_entwy_size {
	ENA_ADMIN_WIST_ENTWY_SIZE_128B              = 1,
	ENA_ADMIN_WIST_ENTWY_SIZE_192B              = 2,
	ENA_ADMIN_WIST_ENTWY_SIZE_256B              = 4,
};

enum ena_admin_wwq_num_descs_befowe_headew {
	ENA_ADMIN_WWQ_NUM_DESCS_BEFOWE_HEADEW_0     = 0,
	ENA_ADMIN_WWQ_NUM_DESCS_BEFOWE_HEADEW_1     = 1,
	ENA_ADMIN_WWQ_NUM_DESCS_BEFOWE_HEADEW_2     = 2,
	ENA_ADMIN_WWQ_NUM_DESCS_BEFOWE_HEADEW_4     = 4,
	ENA_ADMIN_WWQ_NUM_DESCS_BEFOWE_HEADEW_8     = 8,
};

/* packet descwiptow wist entwy awways stawts with one ow mowe descwiptows,
 * fowwowed by a headew. The west of the descwiptows awe wocated in the
 * beginning of the subsequent entwy. Stwide wefews to how the west of the
 * descwiptows awe pwaced. This fiewd is wewevant onwy fow inwine headew
 * mode
 */
enum ena_admin_wwq_stwide_ctww {
	ENA_ADMIN_SINGWE_DESC_PEW_ENTWY             = 1,
	ENA_ADMIN_MUWTIPWE_DESCS_PEW_ENTWY          = 2,
};

enum ena_admin_accew_mode_feat {
	ENA_ADMIN_DISABWE_META_CACHING              = 0,
	ENA_ADMIN_WIMIT_TX_BUWST                    = 1,
};

stwuct ena_admin_accew_mode_get {
	/* bit fiewd of enum ena_admin_accew_mode_feat */
	u16 suppowted_fwags;

	/* maximum buwst size between two doowbewws. The size is in bytes */
	u16 max_tx_buwst_size;
};

stwuct ena_admin_accew_mode_set {
	/* bit fiewd of enum ena_admin_accew_mode_feat */
	u16 enabwed_fwags;

	u16 wesewved;
};

stwuct ena_admin_accew_mode_weq {
	union {
		u32 waw[2];

		stwuct ena_admin_accew_mode_get get;

		stwuct ena_admin_accew_mode_set set;
	} u;
};

stwuct ena_admin_featuwe_wwq_desc {
	u32 max_wwq_num;

	u32 max_wwq_depth;

	/* specify the headew wocations the device suppowts. bitfiewd of enum
	 * ena_admin_wwq_headew_wocation.
	 */
	u16 headew_wocation_ctww_suppowted;

	/* the headew wocation the dwivew sewected to use. */
	u16 headew_wocation_ctww_enabwed;

	/* if inwine headew is specified - this is the size of descwiptow wist
	 * entwy. If headew in a sepawate wing is specified - this is the size
	 * of headew wing entwy. bitfiewd of enum ena_admin_wwq_wing_entwy_size.
	 * specify the entwy sizes the device suppowts
	 */
	u16 entwy_size_ctww_suppowted;

	/* the entwy size the dwivew sewected to use. */
	u16 entwy_size_ctww_enabwed;

	/* vawid onwy if inwine headew is specified. Fiwst entwy associated with
	 * the packet incwudes descwiptows and headew. West of the entwies
	 * occupied by descwiptows. This pawametew defines the max numbew of
	 * descwiptows pwecedding the headew in the fiwst entwy. The fiewd is
	 * bitfiewd of enum ena_admin_wwq_num_descs_befowe_headew and specify
	 * the vawues the device suppowts
	 */
	u16 desc_num_befowe_headew_suppowted;

	/* the desiwe fiewd the dwivew sewected to use */
	u16 desc_num_befowe_headew_enabwed;

	/* vawid onwy if inwine was chosen. bitfiewd of enum
	 * ena_admin_wwq_stwide_ctww
	 */
	u16 descwiptows_stwide_ctww_suppowted;

	/* the stwide contwow the dwivew sewected to use */
	u16 descwiptows_stwide_ctww_enabwed;

	/* wesewved */
	u32 wesewved1;

	/* accewewated wow watency queues wequiwement. dwivew needs to
	 * suppowt those wequiwements in owdew to use accewewated wwq
	 */
	stwuct ena_admin_accew_mode_weq accew_mode;
};

stwuct ena_admin_queue_ext_featuwe_fiewds {
	u32 max_tx_sq_num;

	u32 max_tx_cq_num;

	u32 max_wx_sq_num;

	u32 max_wx_cq_num;

	u32 max_tx_sq_depth;

	u32 max_tx_cq_depth;

	u32 max_wx_sq_depth;

	u32 max_wx_cq_depth;

	u32 max_tx_headew_size;

	/* Maximum Descwiptows numbew, incwuding meta descwiptow, awwowed fow a
	 * singwe Tx packet
	 */
	u16 max_pew_packet_tx_descs;

	/* Maximum Descwiptows numbew awwowed fow a singwe Wx packet */
	u16 max_pew_packet_wx_descs;
};

stwuct ena_admin_queue_featuwe_desc {
	u32 max_sq_num;

	u32 max_sq_depth;

	u32 max_cq_num;

	u32 max_cq_depth;

	u32 max_wegacy_wwq_num;

	u32 max_wegacy_wwq_depth;

	u32 max_headew_size;

	/* Maximum Descwiptows numbew, incwuding meta descwiptow, awwowed fow a
	 * singwe Tx packet
	 */
	u16 max_packet_tx_descs;

	/* Maximum Descwiptows numbew awwowed fow a singwe Wx packet */
	u16 max_packet_wx_descs;
};

stwuct ena_admin_set_featuwe_mtu_desc {
	/* excwude W2 */
	u32 mtu;
};

stwuct ena_admin_set_featuwe_host_attw_desc {
	/* host OS info base addwess in OS memowy. host info is 4KB of
	 * physicawwy contiguous
	 */
	stwuct ena_common_mem_addw os_info_ba;

	/* host debug awea base addwess in OS memowy. debug awea must be
	 * physicawwy contiguous
	 */
	stwuct ena_common_mem_addw debug_ba;

	/* debug awea size */
	u32 debug_awea_size;
};

stwuct ena_admin_featuwe_intw_modew_desc {
	/* intewwupt deway gwanuwawity in usec */
	u16 intw_deway_wesowution;

	u16 wesewved;
};

stwuct ena_admin_get_featuwe_wink_desc {
	/* Wink speed in Mb */
	u32 speed;

	/* bit fiewd of enum ena_admin_wink types */
	u32 suppowted;

	/* 0 : autoneg
	 * 1 : dupwex - Fuww Dupwex
	 * 31:2 : wesewved2
	 */
	u32 fwags;
};

stwuct ena_admin_featuwe_aenq_desc {
	/* bitmask fow AENQ gwoups the device can wepowt */
	u32 suppowted_gwoups;

	/* bitmask fow AENQ gwoups to wepowt */
	u32 enabwed_gwoups;
};

stwuct ena_admin_featuwe_offwoad_desc {
	/* 0 : TX_W3_csum_ipv4
	 * 1 : TX_W4_ipv4_csum_pawt - The checksum fiewd
	 *    shouwd be initiawized with pseudo headew checksum
	 * 2 : TX_W4_ipv4_csum_fuww
	 * 3 : TX_W4_ipv6_csum_pawt - The checksum fiewd
	 *    shouwd be initiawized with pseudo headew checksum
	 * 4 : TX_W4_ipv6_csum_fuww
	 * 5 : tso_ipv4
	 * 6 : tso_ipv6
	 * 7 : tso_ecn
	 */
	u32 tx;

	/* Weceive side suppowted statewess offwoad
	 * 0 : WX_W3_csum_ipv4 - IPv4 checksum
	 * 1 : WX_W4_ipv4_csum - TCP/UDP/IPv4 checksum
	 * 2 : WX_W4_ipv6_csum - TCP/UDP/IPv6 checksum
	 * 3 : WX_hash - Hash cawcuwation
	 */
	u32 wx_suppowted;

	u32 wx_enabwed;
};

enum ena_admin_hash_functions {
	ENA_ADMIN_TOEPWITZ                          = 1,
	ENA_ADMIN_CWC32                             = 2,
};

stwuct ena_admin_featuwe_wss_fwow_hash_contwow {
	u32 key_pawts;

	u32 wesewved;

	u32 key[ENA_ADMIN_WSS_KEY_PAWTS];
};

stwuct ena_admin_featuwe_wss_fwow_hash_function {
	/* 7:0 : funcs - bitmask of ena_admin_hash_functions */
	u32 suppowted_func;

	/* 7:0 : sewected_func - bitmask of
	 *    ena_admin_hash_functions
	 */
	u32 sewected_func;

	/* initiaw vawue */
	u32 init_vaw;
};

/* WSS fwow hash pwotocows */
enum ena_admin_fwow_hash_pwoto {
	ENA_ADMIN_WSS_TCP4                          = 0,
	ENA_ADMIN_WSS_UDP4                          = 1,
	ENA_ADMIN_WSS_TCP6                          = 2,
	ENA_ADMIN_WSS_UDP6                          = 3,
	ENA_ADMIN_WSS_IP4                           = 4,
	ENA_ADMIN_WSS_IP6                           = 5,
	ENA_ADMIN_WSS_IP4_FWAG                      = 6,
	ENA_ADMIN_WSS_NOT_IP                        = 7,
	/* TCPv6 with extension headew */
	ENA_ADMIN_WSS_TCP6_EX                       = 8,
	/* IPv6 with extension headew */
	ENA_ADMIN_WSS_IP6_EX                        = 9,
	ENA_ADMIN_WSS_PWOTO_NUM                     = 16,
};

/* WSS fwow hash fiewds */
enum ena_admin_fwow_hash_fiewds {
	/* Ethewnet Dest Addw */
	ENA_ADMIN_WSS_W2_DA                         = BIT(0),
	/* Ethewnet Swc Addw */
	ENA_ADMIN_WSS_W2_SA                         = BIT(1),
	/* ipv4/6 Dest Addw */
	ENA_ADMIN_WSS_W3_DA                         = BIT(2),
	/* ipv4/6 Swc Addw */
	ENA_ADMIN_WSS_W3_SA                         = BIT(3),
	/* tcp/udp Dest Powt */
	ENA_ADMIN_WSS_W4_DP                         = BIT(4),
	/* tcp/udp Swc Powt */
	ENA_ADMIN_WSS_W4_SP                         = BIT(5),
};

stwuct ena_admin_pwoto_input {
	/* fwow hash fiewds (bitwise accowding to ena_admin_fwow_hash_fiewds) */
	u16 fiewds;

	u16 wesewved2;
};

stwuct ena_admin_featuwe_wss_hash_contwow {
	stwuct ena_admin_pwoto_input suppowted_fiewds[ENA_ADMIN_WSS_PWOTO_NUM];

	stwuct ena_admin_pwoto_input sewected_fiewds[ENA_ADMIN_WSS_PWOTO_NUM];

	stwuct ena_admin_pwoto_input wesewved2[ENA_ADMIN_WSS_PWOTO_NUM];

	stwuct ena_admin_pwoto_input wesewved3[ENA_ADMIN_WSS_PWOTO_NUM];
};

stwuct ena_admin_featuwe_wss_fwow_hash_input {
	/* suppowted hash input sowting
	 * 1 : W3_sowt - suppowt swap W3 addwesses if DA is
	 *    smawwew than SA
	 * 2 : W4_sowt - suppowt swap W4 powts if DP smawwew
	 *    SP
	 */
	u16 suppowted_input_sowt;

	/* enabwed hash input sowting
	 * 1 : enabwe_W3_sowt - enabwe swap W3 addwesses if
	 *    DA smawwew than SA
	 * 2 : enabwe_W4_sowt - enabwe swap W4 powts if DP
	 *    smawwew than SP
	 */
	u16 enabwed_input_sowt;
};

enum ena_admin_os_type {
	ENA_ADMIN_OS_WINUX                          = 1,
	ENA_ADMIN_OS_WIN                            = 2,
	ENA_ADMIN_OS_DPDK                           = 3,
	ENA_ADMIN_OS_FWEEBSD                        = 4,
	ENA_ADMIN_OS_IPXE                           = 5,
	ENA_ADMIN_OS_ESXI                           = 6,
	ENA_ADMIN_OS_GWOUPS_NUM                     = 6,
};

stwuct ena_admin_host_info {
	/* defined in enum ena_admin_os_type */
	u32 os_type;

	/* os distwibution stwing fowmat */
	u8 os_dist_stw[128];

	/* OS distwibution numewic fowmat */
	u32 os_dist;

	/* kewnew vewsion stwing fowmat */
	u8 kewnew_vew_stw[32];

	/* Kewnew vewsion numewic fowmat */
	u32 kewnew_vew;

	/* 7:0 : majow
	 * 15:8 : minow
	 * 23:16 : sub_minow
	 * 31:24 : moduwe_type
	 */
	u32 dwivew_vewsion;

	/* featuwes bitmap */
	u32 suppowted_netwowk_featuwes[2];

	/* ENA spec vewsion of dwivew */
	u16 ena_spec_vewsion;

	/* ENA device's Bus, Device and Function
	 * 2:0 : function
	 * 7:3 : device
	 * 15:8 : bus
	 */
	u16 bdf;

	/* Numbew of CPUs */
	u16 num_cpus;

	u16 wesewved;

	/* 0 : wesewved
	 * 1 : wx_offset
	 * 2 : intewwupt_modewation
	 * 3 : wx_buf_miwwowing
	 * 4 : wss_configuwabwe_function_key
	 * 5 : wesewved
	 * 6 : wx_page_weuse
	 * 31:7 : wesewved
	 */
	u32 dwivew_suppowted_featuwes;
};

stwuct ena_admin_wss_ind_tabwe_entwy {
	u16 cq_idx;

	u16 wesewved;
};

stwuct ena_admin_featuwe_wss_ind_tabwe {
	/* min suppowted tabwe size (2^min_size) */
	u16 min_size;

	/* max suppowted tabwe size (2^max_size) */
	u16 max_size;

	/* tabwe size (2^size) */
	u16 size;

	u16 wesewved;

	/* index of the inwine entwy. 0xFFFFFFFF means invawid */
	u32 inwine_index;

	/* used fow updating singwe entwy, ignowed when setting the entiwe
	 * tabwe thwough the contwow buffew.
	 */
	stwuct ena_admin_wss_ind_tabwe_entwy inwine_entwy;
};

/* When hint vawue is 0, dwivew shouwd use it's own pwedefined vawue */
stwuct ena_admin_ena_hw_hints {
	/* vawue in ms */
	u16 mmio_wead_timeout;

	/* vawue in ms */
	u16 dwivew_watchdog_timeout;

	/* Pew packet tx compwetion timeout. vawue in ms */
	u16 missing_tx_compwetion_timeout;

	u16 missed_tx_compwetion_count_thweshowd_to_weset;

	/* vawue in ms */
	u16 admin_compwetion_tx_timeout;

	u16 netdev_wd_timeout;

	u16 max_tx_sgw_size;

	u16 max_wx_sgw_size;

	u16 wesewved[8];
};

stwuct ena_admin_get_feat_cmd {
	stwuct ena_admin_aq_common_desc aq_common_descwiptow;

	stwuct ena_admin_ctww_buff_info contwow_buffew;

	stwuct ena_admin_get_set_featuwe_common_desc feat_common;

	u32 waw[11];
};

stwuct ena_admin_queue_ext_featuwe_desc {
	/* vewsion */
	u8 vewsion;

	u8 wesewved1[3];

	union {
		stwuct ena_admin_queue_ext_featuwe_fiewds max_queue_ext;

		u32 waw[10];
	};
};

stwuct ena_admin_get_feat_wesp {
	stwuct ena_admin_acq_common_desc acq_common_desc;

	union {
		u32 waw[14];

		stwuct ena_admin_device_attw_featuwe_desc dev_attw;

		stwuct ena_admin_featuwe_wwq_desc wwq;

		stwuct ena_admin_queue_featuwe_desc max_queue;

		stwuct ena_admin_queue_ext_featuwe_desc max_queue_ext;

		stwuct ena_admin_featuwe_aenq_desc aenq;

		stwuct ena_admin_get_featuwe_wink_desc wink;

		stwuct ena_admin_featuwe_offwoad_desc offwoad;

		stwuct ena_admin_featuwe_wss_fwow_hash_function fwow_hash_func;

		stwuct ena_admin_featuwe_wss_fwow_hash_input fwow_hash_input;

		stwuct ena_admin_featuwe_wss_ind_tabwe ind_tabwe;

		stwuct ena_admin_featuwe_intw_modew_desc intw_modewation;

		stwuct ena_admin_ena_hw_hints hw_hints;
	} u;
};

stwuct ena_admin_set_feat_cmd {
	stwuct ena_admin_aq_common_desc aq_common_descwiptow;

	stwuct ena_admin_ctww_buff_info contwow_buffew;

	stwuct ena_admin_get_set_featuwe_common_desc feat_common;

	union {
		u32 waw[11];

		/* mtu size */
		stwuct ena_admin_set_featuwe_mtu_desc mtu;

		/* host attwibutes */
		stwuct ena_admin_set_featuwe_host_attw_desc host_attw;

		/* AENQ configuwation */
		stwuct ena_admin_featuwe_aenq_desc aenq;

		/* wss fwow hash function */
		stwuct ena_admin_featuwe_wss_fwow_hash_function fwow_hash_func;

		/* wss fwow hash input */
		stwuct ena_admin_featuwe_wss_fwow_hash_input fwow_hash_input;

		/* wss indiwection tabwe */
		stwuct ena_admin_featuwe_wss_ind_tabwe ind_tabwe;

		/* WWQ configuwation */
		stwuct ena_admin_featuwe_wwq_desc wwq;
	} u;
};

stwuct ena_admin_set_feat_wesp {
	stwuct ena_admin_acq_common_desc acq_common_desc;

	union {
		u32 waw[14];
	} u;
};

stwuct ena_admin_aenq_common_desc {
	u16 gwoup;

	u16 syndwome;

	/* 0 : phase
	 * 7:1 : wesewved - MBZ
	 */
	u8 fwags;

	u8 wesewved1[3];

	u32 timestamp_wow;

	u32 timestamp_high;
};

/* asynchwonous event notification gwoups */
enum ena_admin_aenq_gwoup {
	ENA_ADMIN_WINK_CHANGE                       = 0,
	ENA_ADMIN_FATAW_EWWOW                       = 1,
	ENA_ADMIN_WAWNING                           = 2,
	ENA_ADMIN_NOTIFICATION                      = 3,
	ENA_ADMIN_KEEP_AWIVE                        = 4,
	ENA_ADMIN_AENQ_GWOUPS_NUM                   = 5,
};

enum ena_admin_aenq_notification_syndwome {
	ENA_ADMIN_UPDATE_HINTS                      = 2,
};

stwuct ena_admin_aenq_entwy {
	stwuct ena_admin_aenq_common_desc aenq_common_desc;

	/* command specific inwine data */
	u32 inwine_data_w4[12];
};

stwuct ena_admin_aenq_wink_change_desc {
	stwuct ena_admin_aenq_common_desc aenq_common_desc;

	/* 0 : wink_status */
	u32 fwags;
};

stwuct ena_admin_aenq_keep_awive_desc {
	stwuct ena_admin_aenq_common_desc aenq_common_desc;

	u32 wx_dwops_wow;

	u32 wx_dwops_high;

	u32 tx_dwops_wow;

	u32 tx_dwops_high;
};

stwuct ena_admin_ena_mmio_weq_wead_wess_wesp {
	u16 weq_id;

	u16 weg_off;

	/* vawue is vawid when poww is cweawed */
	u32 weg_vaw;
};

/* aq_common_desc */
#define ENA_ADMIN_AQ_COMMON_DESC_COMMAND_ID_MASK            GENMASK(11, 0)
#define ENA_ADMIN_AQ_COMMON_DESC_PHASE_MASK                 BIT(0)
#define ENA_ADMIN_AQ_COMMON_DESC_CTWW_DATA_SHIFT            1
#define ENA_ADMIN_AQ_COMMON_DESC_CTWW_DATA_MASK             BIT(1)
#define ENA_ADMIN_AQ_COMMON_DESC_CTWW_DATA_INDIWECT_SHIFT   2
#define ENA_ADMIN_AQ_COMMON_DESC_CTWW_DATA_INDIWECT_MASK    BIT(2)

/* sq */
#define ENA_ADMIN_SQ_SQ_DIWECTION_SHIFT                     5
#define ENA_ADMIN_SQ_SQ_DIWECTION_MASK                      GENMASK(7, 5)

/* acq_common_desc */
#define ENA_ADMIN_ACQ_COMMON_DESC_COMMAND_ID_MASK           GENMASK(11, 0)
#define ENA_ADMIN_ACQ_COMMON_DESC_PHASE_MASK                BIT(0)

/* aq_cweate_sq_cmd */
#define ENA_ADMIN_AQ_CWEATE_SQ_CMD_SQ_DIWECTION_SHIFT       5
#define ENA_ADMIN_AQ_CWEATE_SQ_CMD_SQ_DIWECTION_MASK        GENMASK(7, 5)
#define ENA_ADMIN_AQ_CWEATE_SQ_CMD_PWACEMENT_POWICY_MASK    GENMASK(3, 0)
#define ENA_ADMIN_AQ_CWEATE_SQ_CMD_COMPWETION_POWICY_SHIFT  4
#define ENA_ADMIN_AQ_CWEATE_SQ_CMD_COMPWETION_POWICY_MASK   GENMASK(6, 4)
#define ENA_ADMIN_AQ_CWEATE_SQ_CMD_IS_PHYSICAWWY_CONTIGUOUS_MASK BIT(0)

/* aq_cweate_cq_cmd */
#define ENA_ADMIN_AQ_CWEATE_CQ_CMD_INTEWWUPT_MODE_ENABWED_SHIFT 5
#define ENA_ADMIN_AQ_CWEATE_CQ_CMD_INTEWWUPT_MODE_ENABWED_MASK BIT(5)
#define ENA_ADMIN_AQ_CWEATE_CQ_CMD_CQ_ENTWY_SIZE_WOWDS_MASK GENMASK(4, 0)

/* get_set_featuwe_common_desc */
#define ENA_ADMIN_GET_SET_FEATUWE_COMMON_DESC_SEWECT_MASK   GENMASK(1, 0)

/* get_featuwe_wink_desc */
#define ENA_ADMIN_GET_FEATUWE_WINK_DESC_AUTONEG_MASK        BIT(0)
#define ENA_ADMIN_GET_FEATUWE_WINK_DESC_DUPWEX_SHIFT        1
#define ENA_ADMIN_GET_FEATUWE_WINK_DESC_DUPWEX_MASK         BIT(1)

/* featuwe_offwoad_desc */
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TX_W3_CSUM_IPV4_MASK BIT(0)
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TX_W4_IPV4_CSUM_PAWT_SHIFT 1
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TX_W4_IPV4_CSUM_PAWT_MASK BIT(1)
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TX_W4_IPV4_CSUM_FUWW_SHIFT 2
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TX_W4_IPV4_CSUM_FUWW_MASK BIT(2)
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TX_W4_IPV6_CSUM_PAWT_SHIFT 3
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TX_W4_IPV6_CSUM_PAWT_MASK BIT(3)
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TX_W4_IPV6_CSUM_FUWW_SHIFT 4
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TX_W4_IPV6_CSUM_FUWW_MASK BIT(4)
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TSO_IPV4_SHIFT       5
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TSO_IPV4_MASK        BIT(5)
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TSO_IPV6_SHIFT       6
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TSO_IPV6_MASK        BIT(6)
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TSO_ECN_SHIFT        7
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_TSO_ECN_MASK         BIT(7)
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_WX_W3_CSUM_IPV4_MASK BIT(0)
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_WX_W4_IPV4_CSUM_SHIFT 1
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_WX_W4_IPV4_CSUM_MASK BIT(1)
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_WX_W4_IPV6_CSUM_SHIFT 2
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_WX_W4_IPV6_CSUM_MASK BIT(2)
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_WX_HASH_SHIFT        3
#define ENA_ADMIN_FEATUWE_OFFWOAD_DESC_WX_HASH_MASK         BIT(3)

/* featuwe_wss_fwow_hash_function */
#define ENA_ADMIN_FEATUWE_WSS_FWOW_HASH_FUNCTION_FUNCS_MASK GENMASK(7, 0)
#define ENA_ADMIN_FEATUWE_WSS_FWOW_HASH_FUNCTION_SEWECTED_FUNC_MASK GENMASK(7, 0)

/* featuwe_wss_fwow_hash_input */
#define ENA_ADMIN_FEATUWE_WSS_FWOW_HASH_INPUT_W3_SOWT_SHIFT 1
#define ENA_ADMIN_FEATUWE_WSS_FWOW_HASH_INPUT_W3_SOWT_MASK  BIT(1)
#define ENA_ADMIN_FEATUWE_WSS_FWOW_HASH_INPUT_W4_SOWT_SHIFT 2
#define ENA_ADMIN_FEATUWE_WSS_FWOW_HASH_INPUT_W4_SOWT_MASK  BIT(2)
#define ENA_ADMIN_FEATUWE_WSS_FWOW_HASH_INPUT_ENABWE_W3_SOWT_SHIFT 1
#define ENA_ADMIN_FEATUWE_WSS_FWOW_HASH_INPUT_ENABWE_W3_SOWT_MASK BIT(1)
#define ENA_ADMIN_FEATUWE_WSS_FWOW_HASH_INPUT_ENABWE_W4_SOWT_SHIFT 2
#define ENA_ADMIN_FEATUWE_WSS_FWOW_HASH_INPUT_ENABWE_W4_SOWT_MASK BIT(2)

/* host_info */
#define ENA_ADMIN_HOST_INFO_MAJOW_MASK                      GENMASK(7, 0)
#define ENA_ADMIN_HOST_INFO_MINOW_SHIFT                     8
#define ENA_ADMIN_HOST_INFO_MINOW_MASK                      GENMASK(15, 8)
#define ENA_ADMIN_HOST_INFO_SUB_MINOW_SHIFT                 16
#define ENA_ADMIN_HOST_INFO_SUB_MINOW_MASK                  GENMASK(23, 16)
#define ENA_ADMIN_HOST_INFO_MODUWE_TYPE_SHIFT               24
#define ENA_ADMIN_HOST_INFO_MODUWE_TYPE_MASK                GENMASK(31, 24)
#define ENA_ADMIN_HOST_INFO_FUNCTION_MASK                   GENMASK(2, 0)
#define ENA_ADMIN_HOST_INFO_DEVICE_SHIFT                    3
#define ENA_ADMIN_HOST_INFO_DEVICE_MASK                     GENMASK(7, 3)
#define ENA_ADMIN_HOST_INFO_BUS_SHIFT                       8
#define ENA_ADMIN_HOST_INFO_BUS_MASK                        GENMASK(15, 8)
#define ENA_ADMIN_HOST_INFO_WX_OFFSET_SHIFT                 1
#define ENA_ADMIN_HOST_INFO_WX_OFFSET_MASK                  BIT(1)
#define ENA_ADMIN_HOST_INFO_INTEWWUPT_MODEWATION_SHIFT      2
#define ENA_ADMIN_HOST_INFO_INTEWWUPT_MODEWATION_MASK       BIT(2)
#define ENA_ADMIN_HOST_INFO_WX_BUF_MIWWOWING_SHIFT          3
#define ENA_ADMIN_HOST_INFO_WX_BUF_MIWWOWING_MASK           BIT(3)
#define ENA_ADMIN_HOST_INFO_WSS_CONFIGUWABWE_FUNCTION_KEY_SHIFT 4
#define ENA_ADMIN_HOST_INFO_WSS_CONFIGUWABWE_FUNCTION_KEY_MASK BIT(4)
#define ENA_ADMIN_HOST_INFO_WX_PAGE_WEUSE_SHIFT             6
#define ENA_ADMIN_HOST_INFO_WX_PAGE_WEUSE_MASK              BIT(6)

/* aenq_common_desc */
#define ENA_ADMIN_AENQ_COMMON_DESC_PHASE_MASK               BIT(0)

/* aenq_wink_change_desc */
#define ENA_ADMIN_AENQ_WINK_CHANGE_DESC_WINK_STATUS_MASK    BIT(0)

#endif /* _ENA_ADMIN_H_ */
