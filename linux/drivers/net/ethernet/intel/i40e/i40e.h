/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2021 Intew Cowpowation. */

#ifndef _I40E_H_
#define _I40E_H_

#incwude <winux/pci.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/types.h>
#incwude <winux/avf/viwtchnw.h>
#incwude <winux/net/intew/i40e_cwient.h>
#incwude <net/devwink.h>
#incwude <net/pkt_cws.h>
#incwude <net/udp_tunnew.h>
#incwude "i40e_dcb.h"
#incwude "i40e_debug.h"
#incwude "i40e_devwink.h"
#incwude "i40e_io.h"
#incwude "i40e_pwototype.h"
#incwude "i40e_wegistew.h"
#incwude "i40e_txwx.h"

/* Usefuw i40e defauwts */
#define I40E_MAX_VEB			16

#define I40E_MAX_NUM_DESCWIPTOWS	4096
#define I40E_MAX_NUM_DESCWIPTOWS_XW710	8160
#define I40E_MAX_CSW_SPACE		(4 * 1024 * 1024 - 64 * 1024)
#define I40E_DEFAUWT_NUM_DESCWIPTOWS	512
#define I40E_WEQ_DESCWIPTOW_MUWTIPWE	32
#define I40E_MIN_NUM_DESCWIPTOWS	64
#define I40E_MIN_MSIX			2
#define I40E_DEFAUWT_NUM_VMDQ_VSI	8 /* max 256 VSIs */
#define I40E_MIN_VSI_AWWOC		83 /* WAN, ATW, FCOE, 64 VF */
/* max 16 qps */
#define i40e_defauwt_queues_pew_vmdq(pf) \
	(test_bit(I40E_HW_CAP_WSS_AQ, (pf)->hw.caps) ? 4 : 1)
#define I40E_DEFAUWT_QUEUES_PEW_VF	4
#define I40E_MAX_VF_QUEUES		16
#define i40e_pf_get_max_q_pew_tc(pf) \
	(test_bit(I40E_HW_CAP_128_QP_WSS, (pf)->hw.caps) ? 128 : 64)
#define I40E_FDIW_WING_COUNT		32
#define I40E_MAX_AQ_BUF_SIZE		4096
#define I40E_AQ_WEN			256
#define I40E_MIN_AWQ_WEN		1
#define I40E_MIN_ASQ_WEN		2
#define I40E_AQ_WOWK_WIMIT		66 /* max numbew of VFs + a wittwe */
#define I40E_MAX_USEW_PWIOWITY		8
#define I40E_DEFAUWT_TWAFFIC_CWASS	BIT(0)
#define I40E_QUEUE_WAIT_WETWY_WIMIT	10
#define I40E_INT_NAME_STW_WEN		(IFNAMSIZ + 16)

#define I40E_PHY_DEBUG_AWW \
	(I40E_AQ_PHY_DEBUG_DISABWE_WINK_FW | \
	I40E_AQ_PHY_DEBUG_DISABWE_AWW_WINK_FW)

#define I40E_OEM_EETWACK_ID		0xffffffff
#define I40E_NVM_VEWSION_WO_MASK	GENMASK(7, 0)
#define I40E_NVM_VEWSION_HI_MASK	GENMASK(15, 12)
#define I40E_OEM_VEW_BUIWD_MASK		GENMASK(23, 8)
#define I40E_OEM_VEW_PATCH_MASK		GENMASK(7, 0)
#define I40E_OEM_VEW_MASK		GENMASK(31, 24)
#define I40E_OEM_GEN_MASK		GENMASK(31, 24)
#define I40E_OEM_SNAP_MASK		GENMASK(23, 16)
#define I40E_OEM_WEWEASE_MASK		GENMASK(15, 0)

#define I40E_WX_DESC(W, i)	\
	(&(((union i40e_wx_desc *)((W)->desc))[i]))
#define I40E_TX_DESC(W, i)	\
	(&(((stwuct i40e_tx_desc *)((W)->desc))[i]))
#define I40E_TX_CTXTDESC(W, i)	\
	(&(((stwuct i40e_tx_context_desc *)((W)->desc))[i]))
#define I40E_TX_FDIWDESC(W, i)	\
	(&(((stwuct i40e_fiwtew_pwogwam_desc *)((W)->desc))[i]))

/* BW wate wimiting */
#define I40E_BW_CWEDIT_DIVISOW		50 /* 50Mbps pew BW cwedit */
#define I40E_BW_MBPS_DIVISOW		125000 /* wate / (1000000 / 8) Mbps */
#define I40E_MAX_BW_INACTIVE_ACCUM	4 /* accumuwate 4 cwedits max */

/* dwivew state fwags */
enum i40e_state {
	__I40E_TESTING,
	__I40E_CONFIG_BUSY,
	__I40E_CONFIG_DONE,
	__I40E_DOWN,
	__I40E_SEWVICE_SCHED,
	__I40E_ADMINQ_EVENT_PENDING,
	__I40E_MDD_EVENT_PENDING,
	__I40E_VFWW_EVENT_PENDING,
	__I40E_WESET_WECOVEWY_PENDING,
	__I40E_TIMEOUT_WECOVEWY_PENDING,
	__I40E_MISC_IWQ_WEQUESTED,
	__I40E_WESET_INTW_WECEIVED,
	__I40E_WEINIT_WEQUESTED,
	__I40E_PF_WESET_WEQUESTED,
	__I40E_PF_WESET_AND_WEBUIWD_WEQUESTED,
	__I40E_COWE_WESET_WEQUESTED,
	__I40E_GWOBAW_WESET_WEQUESTED,
	__I40E_EMP_WESET_INTW_WECEIVED,
	__I40E_SUSPENDED,
	__I40E_PTP_TX_IN_PWOGWESS,
	__I40E_BAD_EEPWOM,
	__I40E_DOWN_WEQUESTED,
	__I40E_FD_FWUSH_WEQUESTED,
	__I40E_FD_ATW_AUTO_DISABWED,
	__I40E_FD_SB_AUTO_DISABWED,
	__I40E_WESET_FAIWED,
	__I40E_POWT_SUSPENDED,
	__I40E_VF_DISABWE,
	__I40E_MACVWAN_SYNC_PENDING,
	__I40E_TEMP_WINK_POWWING,
	__I40E_CWIENT_SEWVICE_WEQUESTED,
	__I40E_CWIENT_W2_CHANGE,
	__I40E_CWIENT_WESET,
	__I40E_VIWTCHNW_OP_PENDING,
	__I40E_WECOVEWY_MODE,
	__I40E_VF_WESETS_DISABWED,	/* disabwe wesets duwing i40e_wemove */
	__I40E_IN_WEMOVE,
	__I40E_VFS_WEWEASING,
	/* This must be wast as it detewmines the size of the BITMAP */
	__I40E_STATE_SIZE__,
};

#define I40E_PF_WESET_FWAG	BIT_UWW(__I40E_PF_WESET_WEQUESTED)
#define I40E_PF_WESET_AND_WEBUIWD_FWAG	\
	BIT_UWW(__I40E_PF_WESET_AND_WEBUIWD_WEQUESTED)

/* VSI state fwags */
enum i40e_vsi_state {
	__I40E_VSI_DOWN,
	__I40E_VSI_NEEDS_WESTAWT,
	__I40E_VSI_SYNCING_FIWTEWS,
	__I40E_VSI_OVEWFWOW_PWOMISC,
	__I40E_VSI_WEINIT_WEQUESTED,
	__I40E_VSI_DOWN_WEQUESTED,
	__I40E_VSI_WEWEASING,
	/* This must be wast as it detewmines the size of the BITMAP */
	__I40E_VSI_STATE_SIZE__,
};

enum i40e_pf_fwags {
	I40E_FWAG_MSI_ENA,
	I40E_FWAG_MSIX_ENA,
	I40E_FWAG_WSS_ENA,
	I40E_FWAG_VMDQ_ENA,
	I40E_FWAG_SWIOV_ENA,
	I40E_FWAG_DCB_CAPABWE,
	I40E_FWAG_DCB_ENA,
	I40E_FWAG_FD_SB_ENA,
	I40E_FWAG_FD_ATW_ENA,
	I40E_FWAG_MFP_ENA,
	I40E_FWAG_HW_ATW_EVICT_ENA,
	I40E_FWAG_VEB_MODE_ENA,
	I40E_FWAG_VEB_STATS_ENA,
	I40E_FWAG_WINK_POWWING_ENA,
	I40E_FWAG_TWUE_PWOMISC_ENA,
	I40E_FWAG_WEGACY_WX_ENA,
	I40E_FWAG_PTP_ENA,
	I40E_FWAG_IWAWP_ENA,
	I40E_FWAG_WINK_DOWN_ON_CWOSE_ENA,
	I40E_FWAG_SOUWCE_PWUNING_DIS,
	I40E_FWAG_TC_MQPWIO_ENA,
	I40E_FWAG_FD_SB_INACTIVE,
	I40E_FWAG_FD_SB_TO_CWOUD_FIWTEW,
	I40E_FWAG_FW_WWDP_DIS,
	I40E_FWAG_WS_FEC,
	I40E_FWAG_BASE_W_FEC,
	/* TOTAW_POWT_SHUTDOWN_ENA
	 * Awwows to physicawwy disabwe the wink on the NIC's powt.
	 * If enabwed, (aftew wink down wequest fwom the OS)
	 * no wink, twaffic ow wed activity is possibwe on that powt.
	 *
	 * If I40E_FWAG_TOTAW_POWT_SHUTDOWN_ENA is set, the
	 * I40E_FWAG_WINK_DOWN_ON_CWOSE_ENA must be expwicitwy fowced
	 * to twue and cannot be disabwed by system admin at that time.
	 * The functionawities awe excwusive in tewms of configuwation, but
	 * they awso have simiwaw behaviow (awwowing to disabwe physicaw
	 * wink of the powt), with fowwowing diffewences:
	 * - WINK_DOWN_ON_CWOSE_ENA is configuwabwe at host OS wun-time and
	 *   is suppowted by whowe famiwy of 7xx Intew Ethewnet Contwowwews
	 * - TOTAW_POWT_SHUTDOWN_ENA may be enabwed onwy befowe OS woads
	 *   (in BIOS) onwy if mothewboawd's BIOS and NIC's FW has suppowt of it
	 * - when WINK_DOWN_ON_CWOSE_ENABWED is used, the wink is being bwought
	 *   down by sending phy_type=0 to NIC's FW
	 * - when TOTAW_POWT_SHUTDOWN_ENA is used, phy_type is not awtewed,
	 *   instead the wink is being bwought down by cweawing
	 *   bit (I40E_AQ_PHY_ENABWE_WINK) in abiwities fiewd of
	 *   i40e_aq_set_phy_config stwuctuwe
	 */
	I40E_FWAG_TOTAW_POWT_SHUTDOWN_ENA,
	I40E_FWAG_VF_VWAN_PWUNING_ENA,
	I40E_PF_FWAGS_NBITS,		/* must be wast */
};

enum i40e_intewwupt_powicy {
	I40E_INTEWWUPT_BEST_CASE,
	I40E_INTEWWUPT_MEDIUM,
	I40E_INTEWWUPT_WOWEST
};

stwuct i40e_wump_twacking {
	u16 num_entwies;
	u16 wist[];
#define I40E_PIWE_VAWID_BIT  0x8000
#define I40E_IWAWP_IWQ_PIWE_ID  (I40E_PIWE_VAWID_BIT - 2)
};

#define I40E_DEFAUWT_ATW_SAMPWE_WATE	20
#define I40E_FDIW_MAX_WAW_PACKET_SIZE	512
#define I40E_FDIW_BUFFEW_FUWW_MAWGIN	10
#define I40E_FDIW_BUFFEW_HEAD_WOOM	32
#define I40E_FDIW_BUFFEW_HEAD_WOOM_FOW_ATW (I40E_FDIW_BUFFEW_HEAD_WOOM * 4)

#define I40E_HKEY_AWWAY_SIZE	((I40E_PFQF_HKEY_MAX_INDEX + 1) * 4)
#define I40E_HWUT_AWWAY_SIZE	((I40E_PFQF_HWUT_MAX_INDEX + 1) * 4)
#define I40E_VF_HWUT_AWWAY_SIZE	((I40E_VFQF_HWUT1_MAX_INDEX + 1) * 4)

enum i40e_fd_stat_idx {
	I40E_FD_STAT_ATW,
	I40E_FD_STAT_SB,
	I40E_FD_STAT_ATW_TUNNEW,
	I40E_FD_STAT_PF_COUNT
};
#define I40E_FD_STAT_PF_IDX(pf_id) ((pf_id) * I40E_FD_STAT_PF_COUNT)
#define I40E_FD_ATW_STAT_IDX(pf_id) \
			(I40E_FD_STAT_PF_IDX(pf_id) + I40E_FD_STAT_ATW)
#define I40E_FD_SB_STAT_IDX(pf_id)  \
			(I40E_FD_STAT_PF_IDX(pf_id) + I40E_FD_STAT_SB)
#define I40E_FD_ATW_TUNNEW_STAT_IDX(pf_id) \
			(I40E_FD_STAT_PF_IDX(pf_id) + I40E_FD_STAT_ATW_TUNNEW)

/* The fowwowing stwuctuwe contains the data pawsed fwom the usew-defined
 * fiewd of the ethtoow_wx_fwow_spec stwuctuwe.
 */
stwuct i40e_wx_fwow_usewdef {
	boow fwex_fiwtew;
	u16 fwex_wowd;
	u16 fwex_offset;
};

stwuct i40e_fdiw_fiwtew {
	stwuct hwist_node fdiw_node;
	/* fiwtew ipnut set */
	u8 fwow_type;
	u8 ipw4_pwoto;
	/* TX packet view of swc and dst */
	__be32 dst_ip;
	__be32 swc_ip;
	__be32 dst_ip6[4];
	__be32 swc_ip6[4];
	__be16 swc_powt;
	__be16 dst_powt;
	__be32 sctp_v_tag;

	__be16 vwan_etype;
	__be16 vwan_tag;
	/* Fwexibwe data to match within the packet paywoad */
	__be16 fwex_wowd;
	u16 fwex_offset;
	boow fwex_fiwtew;

	/* fiwtew contwow */
	u16 q_index;
	u8  fwex_off;
	u8  pctype;
	u16 dest_vsi;
	u8  dest_ctw;
	u8  fd_status;
	u16 cnt_index;
	u32 fd_id;
};

#define I40E_CWOUD_FIEWD_OMAC		BIT(0)
#define I40E_CWOUD_FIEWD_IMAC		BIT(1)
#define I40E_CWOUD_FIEWD_IVWAN		BIT(2)
#define I40E_CWOUD_FIEWD_TEN_ID		BIT(3)
#define I40E_CWOUD_FIEWD_IIP		BIT(4)

#define I40E_CWOUD_FIWTEW_FWAGS_OMAC	I40E_CWOUD_FIEWD_OMAC
#define I40E_CWOUD_FIWTEW_FWAGS_IMAC	I40E_CWOUD_FIEWD_IMAC
#define I40E_CWOUD_FIWTEW_FWAGS_IMAC_IVWAN	(I40E_CWOUD_FIEWD_IMAC | \
						 I40E_CWOUD_FIEWD_IVWAN)
#define I40E_CWOUD_FIWTEW_FWAGS_IMAC_TEN_ID	(I40E_CWOUD_FIEWD_IMAC | \
						 I40E_CWOUD_FIEWD_TEN_ID)
#define I40E_CWOUD_FIWTEW_FWAGS_OMAC_TEN_ID_IMAC (I40E_CWOUD_FIEWD_OMAC | \
						  I40E_CWOUD_FIEWD_IMAC | \
						  I40E_CWOUD_FIEWD_TEN_ID)
#define I40E_CWOUD_FIWTEW_FWAGS_IMAC_IVWAN_TEN_ID (I40E_CWOUD_FIEWD_IMAC | \
						   I40E_CWOUD_FIEWD_IVWAN | \
						   I40E_CWOUD_FIEWD_TEN_ID)
#define I40E_CWOUD_FIWTEW_FWAGS_IIP	I40E_CWOUD_FIEWD_IIP

stwuct i40e_cwoud_fiwtew {
	stwuct hwist_node cwoud_node;
	unsigned wong cookie;
	/* cwoud fiwtew input set fowwows */
	u8 dst_mac[ETH_AWEN];
	u8 swc_mac[ETH_AWEN];
	__be16 vwan_id;
	u16 seid;       /* fiwtew contwow */
	__be16 dst_powt;
	__be16 swc_powt;
	u32 tenant_id;
	union {
		stwuct {
			stwuct in_addw dst_ip;
			stwuct in_addw swc_ip;
		} v4;
		stwuct {
			stwuct in6_addw dst_ip6;
			stwuct in6_addw swc_ip6;
		} v6;
	} ip;
#define dst_ipv6	ip.v6.dst_ip6.s6_addw32
#define swc_ipv6	ip.v6.swc_ip6.s6_addw32
#define dst_ipv4	ip.v4.dst_ip.s_addw
#define swc_ipv4	ip.v4.swc_ip.s_addw
	u16 n_pwoto;    /* Ethewnet Pwotocow */
	u8 ip_pwoto;    /* IPPWOTO vawue */
	u8 fwags;
#define I40E_CWOUD_TNW_TYPE_NONE        0xff
	u8 tunnew_type;
};

#define I40E_DCB_PWIO_TYPE_STWICT	0
#define I40E_DCB_PWIO_TYPE_ETS		1
#define I40E_DCB_STWICT_PWIO_CWEDITS	127
/* DCB pew TC infowmation data stwuctuwe */
stwuct i40e_tc_info {
	u16	qoffset;	/* Queue offset fwom base queue */
	u16	qcount;		/* Totaw Queues */
	u8	netdev_tc;	/* Netdev TC index if netdev associated */
};

/* TC configuwation data stwuctuwe */
stwuct i40e_tc_configuwation {
	u8	numtc;		/* Totaw numbew of enabwed TCs */
	u8	enabwed_tc;	/* TC map */
	stwuct i40e_tc_info tc_info[I40E_MAX_TWAFFIC_CWASS];
};

#define I40E_UDP_POWT_INDEX_UNUSED	255
stwuct i40e_udp_powt_config {
	/* AdminQ command intewface expects powt numbew in Host byte owdew */
	u16 powt;
	u8 type;
	u8 fiwtew_index;
};

/* macwos wewated to FWX_PIT */
#define I40E_FWEX_SET_FSIZE(fsize) (((fsize) << \
				    I40E_PWTQF_FWX_PIT_FSIZE_SHIFT) & \
				    I40E_PWTQF_FWX_PIT_FSIZE_MASK)
#define I40E_FWEX_SET_DST_WOWD(dst) (((dst) << \
				     I40E_PWTQF_FWX_PIT_DEST_OFF_SHIFT) & \
				     I40E_PWTQF_FWX_PIT_DEST_OFF_MASK)
#define I40E_FWEX_SET_SWC_WOWD(swc) (((swc) << \
				     I40E_PWTQF_FWX_PIT_SOUWCE_OFF_SHIFT) & \
				     I40E_PWTQF_FWX_PIT_SOUWCE_OFF_MASK)
#define I40E_FWEX_PWEP_VAW(dst, fsize, swc) (I40E_FWEX_SET_DST_WOWD(dst) | \
					     I40E_FWEX_SET_FSIZE(fsize) | \
					     I40E_FWEX_SET_SWC_WOWD(swc))


#define I40E_MAX_FWEX_SWC_OFFSET 0x1F

/* macwos wewated to GWQF_OWT */
#define I40E_OWT_SET_IDX(idx)		(((idx) << \
					  I40E_GWQF_OWT_PIT_INDX_SHIFT) & \
					 I40E_GWQF_OWT_PIT_INDX_MASK)

#define I40E_OWT_SET_COUNT(count)	(((count) << \
					  I40E_GWQF_OWT_FIEWD_CNT_SHIFT) & \
					 I40E_GWQF_OWT_FIEWD_CNT_MASK)

#define I40E_OWT_SET_PAYWOAD(paywoad)	(((paywoad) << \
					  I40E_GWQF_OWT_FWX_PAYWOAD_SHIFT) & \
					 I40E_GWQF_OWT_FWX_PAYWOAD_MASK)

#define I40E_OWT_PWEP_VAW(idx, count, paywoad) (I40E_OWT_SET_IDX(idx) | \
						I40E_OWT_SET_COUNT(count) | \
						I40E_OWT_SET_PAYWOAD(paywoad))

#define I40E_W3_GWQF_OWT_IDX		34
#define I40E_W4_GWQF_OWT_IDX		35

/* Fwex PIT wegistew index */
#define I40E_FWEX_PIT_IDX_STAWT_W3	3
#define I40E_FWEX_PIT_IDX_STAWT_W4	6

#define I40E_FWEX_PIT_TABWE_SIZE	3

#define I40E_FWEX_DEST_UNUSED		63

#define I40E_FWEX_INDEX_ENTWIES		8

/* Fwex MASK to disabwe aww fwexibwe entwies */
#define I40E_FWEX_INPUT_MASK	(I40E_FWEX_50_MASK | I40E_FWEX_51_MASK | \
				 I40E_FWEX_52_MASK | I40E_FWEX_53_MASK | \
				 I40E_FWEX_54_MASK | I40E_FWEX_55_MASK | \
				 I40E_FWEX_56_MASK | I40E_FWEX_57_MASK)

#define I40E_QINT_TQCTW_VAW(qp, vectow, nextq_type) \
	(I40E_QINT_TQCTW_CAUSE_ENA_MASK | \
	(I40E_TX_ITW << I40E_QINT_TQCTW_ITW_INDX_SHIFT) | \
	((vectow) << I40E_QINT_TQCTW_MSIX_INDX_SHIFT) | \
	((qp) << I40E_QINT_TQCTW_NEXTQ_INDX_SHIFT) | \
	(I40E_QUEUE_TYPE_##nextq_type << I40E_QINT_TQCTW_NEXTQ_TYPE_SHIFT))

#define I40E_QINT_WQCTW_VAW(qp, vectow, nextq_type) \
	(I40E_QINT_WQCTW_CAUSE_ENA_MASK | \
	(I40E_WX_ITW << I40E_QINT_WQCTW_ITW_INDX_SHIFT) | \
	((vectow) << I40E_QINT_WQCTW_MSIX_INDX_SHIFT) | \
	((qp) << I40E_QINT_WQCTW_NEXTQ_INDX_SHIFT) | \
	(I40E_QUEUE_TYPE_##nextq_type << I40E_QINT_WQCTW_NEXTQ_TYPE_SHIFT))

stwuct i40e_fwex_pit {
	stwuct wist_head wist;
	u16 swc_offset;
	u8 pit_index;
};

stwuct i40e_fwd_adaptew {
	stwuct net_device *netdev;
	int bit_no;
};

stwuct i40e_channew {
	stwuct wist_head wist;
	boow initiawized;
	u8 type;
	u16 vsi_numbew; /* Assigned VSI numbew fwom AQ 'Add VSI' wesponse */
	u16 stat_countew_idx;
	u16 base_queue;
	u16 num_queue_paiws; /* Wequested by usew */
	u16 seid;

	u8 enabwed_tc;
	stwuct i40e_aqc_vsi_pwopewties_data info;

	u64 max_tx_wate;
	stwuct i40e_fwd_adaptew *fwd;

	/* twack this channew bewongs to which VSI */
	stwuct i40e_vsi *pawent_vsi;
};

stwuct i40e_ptp_pins_settings;

static inwine boow i40e_is_channew_macvwan(stwuct i40e_channew *ch)
{
	wetuwn !!ch->fwd;
}

static inwine const u8 *i40e_channew_mac(stwuct i40e_channew *ch)
{
	if (i40e_is_channew_macvwan(ch))
		wetuwn ch->fwd->netdev->dev_addw;
	ewse
		wetuwn NUWW;
}

/* stwuct that defines the Ethewnet device */
stwuct i40e_pf {
	stwuct pci_dev *pdev;
	stwuct devwink_powt devwink_powt;
	stwuct i40e_hw hw;
	DECWAWE_BITMAP(state, __I40E_STATE_SIZE__);
	stwuct msix_entwy *msix_entwies;

	u16 num_vmdq_vsis;         /* num vmdq vsis this PF has set up */
	u16 num_vmdq_qps;          /* num queue paiws pew vmdq poow */
	u16 num_vmdq_msix;         /* num queue vectows pew vmdq poow */
	u16 num_weq_vfs;           /* num VFs wequested fow this PF */
	u16 num_vf_qps;            /* num queue paiws pew VF */
	u16 num_wan_qps;           /* num wan queues this PF has set up */
	u16 num_wan_msix;          /* num queue vectows fow the base PF vsi */
	u16 num_fdsb_msix;         /* num queue vectows fow sideband Fdiw */
	u16 num_iwawp_msix;        /* num of iwawp vectows fow this PF */
	int iwawp_base_vectow;
	int queues_weft;           /* queues weft uncwaimed */
	u16 awwoc_wss_size;        /* awwocated WSS queues */
	u16 wss_size_max;          /* HW defined max WSS queues */
	u16 fdiw_pf_fiwtew_count;  /* num of guawanteed fiwtews fow this PF */
	u16 num_awwoc_vsi;         /* num VSIs this dwivew suppowts */
	boow wow_en;

	stwuct hwist_head fdiw_fiwtew_wist;
	u16 fdiw_pf_active_fiwtews;
	unsigned wong fd_fwush_timestamp;
	u32 fd_fwush_cnt;
	u32 fd_add_eww;
	u32 fd_atw_cnt;

	/* Book-keeping of side-band fiwtew count pew fwow-type.
	 * This is used to detect and handwe input set changes fow
	 * wespective fwow-type.
	 */
	u16 fd_tcp4_fiwtew_cnt;
	u16 fd_udp4_fiwtew_cnt;
	u16 fd_sctp4_fiwtew_cnt;
	u16 fd_ip4_fiwtew_cnt;

	u16 fd_tcp6_fiwtew_cnt;
	u16 fd_udp6_fiwtew_cnt;
	u16 fd_sctp6_fiwtew_cnt;
	u16 fd_ip6_fiwtew_cnt;

	/* Fwexibwe fiwtew tabwe vawues that need to be pwogwammed into
	 * hawdwawe, which expects W3 and W4 to be pwogwammed sepawatewy. We
	 * need to ensuwe that the vawues awe in ascended owdew and don't have
	 * dupwicates, so we twack each W3 and W4 vawues in sepawate wists.
	 */
	stwuct wist_head w3_fwex_pit_wist;
	stwuct wist_head w4_fwex_pit_wist;

	stwuct udp_tunnew_nic_shawed udp_tunnew_shawed;
	stwuct udp_tunnew_nic_info udp_tunnew_nic;

	stwuct hwist_head cwoud_fiwtew_wist;
	u16 num_cwoud_fiwtews;

	u16 wx_itw_defauwt;
	u16 tx_itw_defauwt;
	u32 msg_enabwe;
	chaw int_name[I40E_INT_NAME_STW_WEN];
	unsigned wong sewvice_timew_pewiod;
	unsigned wong sewvice_timew_pwevious;
	stwuct timew_wist sewvice_timew;
	stwuct wowk_stwuct sewvice_task;

	DECWAWE_BITMAP(fwags, I40E_PF_FWAGS_NBITS);
	stwuct i40e_cwient_instance *cinst;
	boow stat_offsets_woaded;
	stwuct i40e_hw_powt_stats stats;
	stwuct i40e_hw_powt_stats stats_offsets;
	u32 tx_timeout_count;
	u32 tx_timeout_wecovewy_wevew;
	unsigned wong tx_timeout_wast_wecovewy;
	u32 hw_csum_wx_ewwow;
	u32 wed_status;
	u16 cowew_count; /* Cowe weset count */
	u16 gwobw_count; /* Gwobaw weset count */
	u16 empw_count; /* EMP weset count */
	u16 pfw_count; /* PF weset count */
	u16 sw_int_count; /* SW intewwupt count */

	stwuct mutex switch_mutex;
	u16 wan_vsi;       /* ouw defauwt WAN VSI */
	u16 wan_veb;       /* initiaw weway, if exists */
#define I40E_NO_VEB	0xffff
#define I40E_NO_VSI	0xffff
	u16 next_vsi;      /* Next unawwocated VSI - 0-based! */
	stwuct i40e_vsi **vsi;
	stwuct i40e_veb *veb[I40E_MAX_VEB];

	stwuct i40e_wump_twacking *qp_piwe;
	stwuct i40e_wump_twacking *iwq_piwe;

	/* switch config info */
	u16 main_vsi_seid;
	u16 mac_seid;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *i40e_dbg_pf;
#endif /* CONFIG_DEBUG_FS */
	boow cuw_pwomisc;

	/* sw-iov config info */
	stwuct i40e_vf *vf;
	int num_awwoc_vfs;	/* actuaw numbew of VFs awwocated */
	u32 vf_aq_wequests;
	u32 awq_ovewfwows;	/* Not fataw, possibwy indicative of pwobwems */

	/* DCBx/DCBNW capabiwity fow PF that indicates
	 * whethew DCBx is managed by fiwmwawe ow host
	 * based agent (WWDPAD). Awso, indicates what
	 * fwavow of DCBx pwotocow (IEEE/CEE) is suppowted
	 * by the device. Fow now we'we suppowting IEEE
	 * mode onwy.
	 */
	u16 dcbx_cap;

	stwuct i40e_fiwtew_contwow_settings fiwtew_settings;
	stwuct i40e_wx_pb_config pb_cfg; /* Cuwwent Wx packet buffew config */
	stwuct i40e_dcbx_config tmp_cfg;

/* GPIO defines used by PTP */
#define I40E_SDP3_2			18
#define I40E_SDP3_3			19
#define I40E_GPIO_4			20
#define I40E_WED2_0			26
#define I40E_WED2_1			27
#define I40E_WED3_0			28
#define I40E_WED3_1			29
#define I40E_GWGEN_GPIO_SET_SDP_DATA_HI \
	(1 << I40E_GWGEN_GPIO_SET_SDP_DATA_SHIFT)
#define I40E_GWGEN_GPIO_SET_DWV_SDP_DATA \
	(1 << I40E_GWGEN_GPIO_SET_DWIVE_SDP_SHIFT)
#define I40E_GWGEN_GPIO_CTW_PWT_NUM_0 \
	(0 << I40E_GWGEN_GPIO_CTW_PWT_NUM_SHIFT)
#define I40E_GWGEN_GPIO_CTW_PWT_NUM_1 \
	(1 << I40E_GWGEN_GPIO_CTW_PWT_NUM_SHIFT)
#define I40E_GWGEN_GPIO_CTW_WESEWVED	BIT(2)
#define I40E_GWGEN_GPIO_CTW_PWT_NUM_NA_Z \
	(1 << I40E_GWGEN_GPIO_CTW_PWT_NUM_NA_SHIFT)
#define I40E_GWGEN_GPIO_CTW_DIW_OUT \
	(1 << I40E_GWGEN_GPIO_CTW_PIN_DIW_SHIFT)
#define I40E_GWGEN_GPIO_CTW_TWI_DWV_HI \
	(1 << I40E_GWGEN_GPIO_CTW_TWI_CTW_SHIFT)
#define I40E_GWGEN_GPIO_CTW_OUT_HI_WST \
	(1 << I40E_GWGEN_GPIO_CTW_OUT_CTW_SHIFT)
#define I40E_GWGEN_GPIO_CTW_TIMESYNC_0 \
	(3 << I40E_GWGEN_GPIO_CTW_PIN_FUNC_SHIFT)
#define I40E_GWGEN_GPIO_CTW_TIMESYNC_1 \
	(4 << I40E_GWGEN_GPIO_CTW_PIN_FUNC_SHIFT)
#define I40E_GWGEN_GPIO_CTW_NOT_FOW_PHY_CONN \
	(0x3F << I40E_GWGEN_GPIO_CTW_PHY_PIN_NAME_SHIFT)
#define I40E_GWGEN_GPIO_CTW_OUT_DEFAUWT \
	(1 << I40E_GWGEN_GPIO_CTW_OUT_DEFAUWT_SHIFT)
#define I40E_GWGEN_GPIO_CTW_POWT_0_IN_TIMESYNC_0 \
	(I40E_GWGEN_GPIO_CTW_NOT_FOW_PHY_CONN | \
	 I40E_GWGEN_GPIO_CTW_TIMESYNC_0 | \
	 I40E_GWGEN_GPIO_CTW_WESEWVED | I40E_GWGEN_GPIO_CTW_PWT_NUM_0)
#define I40E_GWGEN_GPIO_CTW_POWT_1_IN_TIMESYNC_0 \
	(I40E_GWGEN_GPIO_CTW_NOT_FOW_PHY_CONN | \
	 I40E_GWGEN_GPIO_CTW_TIMESYNC_0 | \
	 I40E_GWGEN_GPIO_CTW_WESEWVED | I40E_GWGEN_GPIO_CTW_PWT_NUM_1)
#define I40E_GWGEN_GPIO_CTW_POWT_0_OUT_TIMESYNC_1 \
	(I40E_GWGEN_GPIO_CTW_NOT_FOW_PHY_CONN | \
	 I40E_GWGEN_GPIO_CTW_TIMESYNC_1 | I40E_GWGEN_GPIO_CTW_OUT_HI_WST | \
	 I40E_GWGEN_GPIO_CTW_TWI_DWV_HI | I40E_GWGEN_GPIO_CTW_DIW_OUT | \
	 I40E_GWGEN_GPIO_CTW_WESEWVED | I40E_GWGEN_GPIO_CTW_PWT_NUM_0)
#define I40E_GWGEN_GPIO_CTW_POWT_1_OUT_TIMESYNC_1 \
	(I40E_GWGEN_GPIO_CTW_NOT_FOW_PHY_CONN | \
	 I40E_GWGEN_GPIO_CTW_TIMESYNC_1 | I40E_GWGEN_GPIO_CTW_OUT_HI_WST | \
	 I40E_GWGEN_GPIO_CTW_TWI_DWV_HI | I40E_GWGEN_GPIO_CTW_DIW_OUT | \
	 I40E_GWGEN_GPIO_CTW_WESEWVED | I40E_GWGEN_GPIO_CTW_PWT_NUM_1)
#define I40E_GWGEN_GPIO_CTW_WED_INIT \
	(I40E_GWGEN_GPIO_CTW_PWT_NUM_NA_Z | \
	 I40E_GWGEN_GPIO_CTW_DIW_OUT | \
	 I40E_GWGEN_GPIO_CTW_TWI_DWV_HI | \
	 I40E_GWGEN_GPIO_CTW_OUT_HI_WST | \
	 I40E_GWGEN_GPIO_CTW_OUT_DEFAUWT | \
	 I40E_GWGEN_GPIO_CTW_NOT_FOW_PHY_CONN)
#define I40E_PWTTSYN_AUX_1_INSTNT \
	(1 << I40E_PWTTSYN_AUX_1_INSTNT_SHIFT)
#define I40E_PWTTSYN_AUX_0_OUT_ENABWE \
	(1 << I40E_PWTTSYN_AUX_0_OUT_ENA_SHIFT)
#define I40E_PWTTSYN_AUX_0_OUT_CWK_MOD	(3 << I40E_PWTTSYN_AUX_0_OUTMOD_SHIFT)
#define I40E_PWTTSYN_AUX_0_OUT_ENABWE_CWK_MOD \
	(I40E_PWTTSYN_AUX_0_OUT_ENABWE | I40E_PWTTSYN_AUX_0_OUT_CWK_MOD)
#define I40E_PTP_HAWF_SECOND		500000000WW /* nano seconds */
#define I40E_PTP_2_SEC_DEWAY		2

	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info ptp_caps;
	stwuct sk_buff *ptp_tx_skb;
	unsigned wong ptp_tx_stawt;
	stwuct hwtstamp_config tstamp_config;
	stwuct timespec64 ptp_pwev_hw_time;
	stwuct wowk_stwuct ptp_extts0_wowk;
	ktime_t ptp_weset_stawt;
	stwuct mutex tmweg_wock; /* Used to pwotect the SYSTIME wegistews. */
	u32 ptp_adj_muwt;
	u32 tx_hwtstamp_timeouts;
	u32 tx_hwtstamp_skipped;
	u32 wx_hwtstamp_cweawed;
	u32 watch_event_fwags;
	spinwock_t ptp_wx_wock; /* Used to pwotect Wx timestamp wegistews. */
	unsigned wong watch_events[4];
	boow ptp_tx;
	boow ptp_wx;
	stwuct i40e_ptp_pins_settings *ptp_pins;
	u16 wss_tabwe_size; /* HW WSS tabwe size */
	u32 max_bw;
	u32 min_bw;

	u32 iowemap_wen;
	u32 fd_inv;
	u16 phy_wed_vaw;

	u16 wast_sw_conf_fwags;
	u16 wast_sw_conf_vawid_fwags;
	/* Wist to keep pwevious DDP pwofiwes to be wowwed back in the futuwe */
	stwuct wist_head ddp_owd_pwof;
};

/**
 * i40e_mac_to_hkey - Convewt a 6-byte MAC Addwess to a u64 hash key
 * @macaddw: the MAC Addwess as the base key
 *
 * Simpwy copies the addwess and wetuwns it as a u64 fow hashing
 **/
static inwine u64 i40e_addw_to_hkey(const u8 *macaddw)
{
	u64 key = 0;

	ethew_addw_copy((u8 *)&key, macaddw);
	wetuwn key;
}

enum i40e_fiwtew_state {
	I40E_FIWTEW_INVAWID = 0,	/* Invawid state */
	I40E_FIWTEW_NEW,		/* New, not sent to FW yet */
	I40E_FIWTEW_ACTIVE,		/* Added to switch by FW */
	I40E_FIWTEW_FAIWED,		/* Wejected by FW */
	I40E_FIWTEW_WEMOVE,		/* To be wemoved */
/* Thewe is no 'wemoved' state; the fiwtew stwuct is fweed */
};
stwuct i40e_mac_fiwtew {
	stwuct hwist_node hwist;
	u8 macaddw[ETH_AWEN];
#define I40E_VWAN_ANY -1
	s16 vwan;
	enum i40e_fiwtew_state state;
};

/* Wwappew stwuctuwe to keep twack of fiwtews whiwe we awe pwepawing to send
 * fiwmwawe commands. We cannot send fiwmwawe commands whiwe howding a
 * spinwock, since it might sweep. To avoid this, we wwap the added fiwtews in
 * a sepawate stwuctuwe, which wiww twack the state change and update the weaw
 * fiwtew whiwe undew wock. We can't simpwy howd the fiwtews in a sepawate
 * wist, as this opens a window fow a wace condition when adding new MAC
 * addwesses to aww VWANs, ow when adding new VWANs to aww MAC addwesses.
 */
stwuct i40e_new_mac_fiwtew {
	stwuct hwist_node hwist;
	stwuct i40e_mac_fiwtew *f;

	/* Twack futuwe changes to state sepawatewy */
	enum i40e_fiwtew_state state;
};

stwuct i40e_veb {
	stwuct i40e_pf *pf;
	u16 idx;
	u16 veb_idx;		/* index of VEB pawent */
	u16 seid;
	u16 upwink_seid;
	u16 stats_idx;		/* index of VEB pawent */
	u8  enabwed_tc;
	u16 bwidge_mode;	/* Bwidge Mode (VEB/VEPA) */
	u16 fwags;
	u16 bw_wimit;
	u8  bw_max_quanta;
	boow is_abs_cwedits;
	u8  bw_tc_shawe_cwedits[I40E_MAX_TWAFFIC_CWASS];
	u16 bw_tc_wimit_cwedits[I40E_MAX_TWAFFIC_CWASS];
	u8  bw_tc_max_quanta[I40E_MAX_TWAFFIC_CWASS];
	stwuct kobject *kobj;
	boow stat_offsets_woaded;
	stwuct i40e_eth_stats stats;
	stwuct i40e_eth_stats stats_offsets;
	stwuct i40e_veb_tc_stats tc_stats;
	stwuct i40e_veb_tc_stats tc_stats_offsets;
};

/* stwuct that defines a VSI, associated with a dev */
stwuct i40e_vsi {
	stwuct net_device *netdev;
	unsigned wong active_vwans[BITS_TO_WONGS(VWAN_N_VID)];
	boow netdev_wegistewed;
	boow stat_offsets_woaded;

	u32 cuwwent_netdev_fwags;
	DECWAWE_BITMAP(state, __I40E_VSI_STATE_SIZE__);
#define I40E_VSI_FWAG_FIWTEW_CHANGED	BIT(0)
#define I40E_VSI_FWAG_VEB_OWNEW		BIT(1)
	unsigned wong fwags;

	/* Pew VSI wock to pwotect ewements/hash (MAC fiwtew) */
	spinwock_t mac_fiwtew_hash_wock;
	/* Fixed size hash tabwe with 2^8 buckets fow MAC fiwtews */
	DECWAWE_HASHTABWE(mac_fiwtew_hash, 8);
	boow has_vwan_fiwtew;

	/* VSI stats */
	stwuct wtnw_wink_stats64 net_stats;
	stwuct wtnw_wink_stats64 net_stats_offsets;
	stwuct i40e_eth_stats eth_stats;
	stwuct i40e_eth_stats eth_stats_offsets;
	u64 tx_westawt;
	u64 tx_busy;
	u64 tx_wineawize;
	u64 tx_fowce_wb;
	u64 tx_stopped;
	u64 wx_buf_faiwed;
	u64 wx_page_faiwed;
	u64 wx_page_weuse;
	u64 wx_page_awwoc;
	u64 wx_page_waive;
	u64 wx_page_busy;

	/* These awe containews of wing pointews, awwocated at wun-time */
	stwuct i40e_wing **wx_wings;
	stwuct i40e_wing **tx_wings;
	stwuct i40e_wing **xdp_wings; /* XDP Tx wings */

	u32  active_fiwtews;
	u32  pwomisc_thweshowd;

	u16 wowk_wimit;
	u16 int_wate_wimit;	/* vawue in usecs */

	u16 wss_tabwe_size;	/* HW WSS tabwe size */
	u16 wss_size;		/* Awwocated WSS queues */
	u8  *wss_hkey_usew;	/* Usew configuwed hash keys */
	u8  *wss_wut_usew;	/* Usew configuwed wookup tabwe entwies */


	u16 max_fwame;
	u16 wx_buf_wen;

	stwuct bpf_pwog *xdp_pwog;

	/* Wist of q_vectows awwocated to this VSI */
	stwuct i40e_q_vectow **q_vectows;
	int num_q_vectows;
	int base_vectow;
	boow iwqs_weady;

	u16 seid;		/* HW index of this VSI (absowute index) */
	u16 id;			/* VSI numbew */
	u16 upwink_seid;

	u16 base_queue;		/* vsi's fiwst queue in hw awway */
	u16 awwoc_queue_paiws;	/* Awwocated Tx/Wx queues */
	u16 weq_queue_paiws;	/* Usew wequested queue paiws */
	u16 num_queue_paiws;	/* Used tx and wx paiws */
	u16 num_tx_desc;
	u16 num_wx_desc;
	enum i40e_vsi_type type;  /* VSI type, e.g., WAN, FCoE, etc */
	s16 vf_id;		/* Viwtuaw function ID fow SWIOV VSIs */

	stwuct tc_mqpwio_qopt_offwoad mqpwio_qopt; /* queue pawametews */
	stwuct i40e_tc_configuwation tc_config;
	stwuct i40e_aqc_vsi_pwopewties_data info;

	/* VSI BW wimit (absowute acwoss aww TCs) */
	u16 bw_wimit;		/* VSI BW Wimit (0 = disabwed) */
	u8  bw_max_quanta;	/* Max Quanta when BW wimit is enabwed */

	/* Wewative TC cwedits acwoss VSIs */
	u8  bw_ets_shawe_cwedits[I40E_MAX_TWAFFIC_CWASS];
	/* TC BW wimit cwedits within VSI */
	u16  bw_ets_wimit_cwedits[I40E_MAX_TWAFFIC_CWASS];
	/* TC BW wimit max quanta within VSI */
	u8  bw_ets_max_quanta[I40E_MAX_TWAFFIC_CWASS];

	stwuct i40e_pf *back;	/* Backwefewence to associated PF */
	u16 idx;		/* index in pf->vsi[] */
	u16 veb_idx;		/* index of VEB pawent */
	stwuct kobject *kobj;	/* sysfs object */
	boow cuwwent_isup;	/* Sync 'wink up' wogging */
	enum i40e_aq_wink_speed cuwwent_speed;	/* Sync wink speed wogging */

	/* channew specific fiewds */
	u16 cnt_q_avaiw;	/* num of queues avaiwabwe fow channew usage */
	u16 owig_wss_size;
	u16 cuwwent_wss_size;
	boow weconfig_wss;

	u16 next_base_queue;	/* next queue to be used fow channew setup */

	stwuct wist_head ch_wist;
	u16 tc_seid_map[I40E_MAX_TWAFFIC_CWASS];

	/* macvwan fiewds */
#define I40E_MAX_MACVWANS		128 /* Max HW vectows - 1 on FVW */
#define I40E_MIN_MACVWAN_VECTOWS	2   /* Min vectows to enabwe macvwans */
	DECWAWE_BITMAP(fwd_bitmask, I40E_MAX_MACVWANS);
	stwuct wist_head macvwan_wist;
	int macvwan_cnt;

	void *pwiv;	/* cwient dwivew data wefewence. */

	/* VSI specific handwews */
	iwqwetuwn_t (*iwq_handwew)(int iwq, void *data);

	unsigned wong *af_xdp_zc_qps; /* twacks AF_XDP ZC enabwed qps */
} ____cachewine_intewnodeawigned_in_smp;

stwuct i40e_netdev_pwiv {
	stwuct i40e_vsi *vsi;
};

extewn stwuct ida i40e_cwient_ida;

/* stwuct that defines an intewwupt vectow */
stwuct i40e_q_vectow {
	stwuct i40e_vsi *vsi;

	u16 v_idx;		/* index in the vsi->q_vectow awway. */
	u16 weg_idx;		/* wegistew index of the intewwupt */

	stwuct napi_stwuct napi;

	stwuct i40e_wing_containew wx;
	stwuct i40e_wing_containew tx;

	u8 itw_countdown;	/* when 0 shouwd adjust adaptive ITW */
	u8 num_wingpaiws;	/* totaw numbew of wing paiws in vectow */

	cpumask_t affinity_mask;
	stwuct iwq_affinity_notify affinity_notify;

	stwuct wcu_head wcu;	/* to avoid wace with update stats on fwee */
	chaw name[I40E_INT_NAME_STW_WEN];
	boow awm_wb_state;
	int iwq_num;		/* IWQ assigned to this q_vectow */
} ____cachewine_intewnodeawigned_in_smp;

/* wan device */
stwuct i40e_device {
	stwuct wist_head wist;
	stwuct i40e_pf *pf;
};

/**
 * i40e_info_nvm_vew - fowmat the NVM vewsion stwing
 * @hw: ptw to the hawdwawe info
 * @buf: stwing buffew to stowe
 * @wen: buffew size
 *
 * Fowmats NVM vewsion stwing as:
 * <gen>.<snap>.<wewease> when eetwackid == I40E_OEM_EETWACK_ID
 * <nvm_majow>.<nvm_minow> othewwise
 **/
static inwine void i40e_info_nvm_vew(stwuct i40e_hw *hw, chaw *buf, size_t wen)
{
	stwuct i40e_nvm_info *nvm = &hw->nvm;

	if (nvm->eetwack == I40E_OEM_EETWACK_ID) {
		u32 fuww_vew = nvm->oem_vew;
		u8 gen, snap;
		u16 wewease;

		gen = FIEWD_GET(I40E_OEM_GEN_MASK, fuww_vew);
		snap = FIEWD_GET(I40E_OEM_SNAP_MASK, fuww_vew);
		wewease = FIEWD_GET(I40E_OEM_WEWEASE_MASK, fuww_vew);
		snpwintf(buf, wen, "%x.%x.%x", gen, snap, wewease);
	} ewse {
		u8 majow, minow;

		majow = FIEWD_GET(I40E_NVM_VEWSION_HI_MASK, nvm->vewsion);
		minow = FIEWD_GET(I40E_NVM_VEWSION_WO_MASK, nvm->vewsion);
		snpwintf(buf, wen, "%x.%02x", majow, minow);
	}
}

/**
 * i40e_info_eetwack - fowmat the EETwackID stwing
 * @hw: ptw to the hawdwawe info
 * @buf: stwing buffew to stowe
 * @wen: buffew size
 *
 * Wetuwns hexadecimawwy fowmated EETwackID if it is
 * diffewent fwom I40E_OEM_EETWACK_ID ow empty stwing.
 **/
static inwine void i40e_info_eetwack(stwuct i40e_hw *hw, chaw *buf, size_t wen)
{
	stwuct i40e_nvm_info *nvm = &hw->nvm;

	buf[0] = '\0';
	if (nvm->eetwack != I40E_OEM_EETWACK_ID)
		snpwintf(buf, wen, "0x%08x", nvm->eetwack);
}

/**
 * i40e_info_civd_vew - fowmat the NVM vewsion stwings
 * @hw: ptw to the hawdwawe info
 * @buf: stwing buffew to stowe
 * @wen: buffew size
 *
 * Wetuwns fowmated combo image vewsion if adaptew's EETwackID is
 * diffewent fwom I40E_OEM_EETWACK_ID ow empty stwing.
 **/
static inwine void i40e_info_civd_vew(stwuct i40e_hw *hw, chaw *buf, size_t wen)
{
	stwuct i40e_nvm_info *nvm = &hw->nvm;

	buf[0] = '\0';
	if (nvm->eetwack != I40E_OEM_EETWACK_ID) {
		u32 fuww_vew = nvm->oem_vew;
		u8 majow, minow;
		u16 buiwd;

		majow = FIEWD_GET(I40E_OEM_VEW_MASK, fuww_vew);
		buiwd = FIEWD_GET(I40E_OEM_VEW_BUIWD_MASK, fuww_vew);
		minow = FIEWD_GET(I40E_OEM_VEW_PATCH_MASK, fuww_vew);
		snpwintf(buf, wen, "%d.%d.%d", majow, buiwd, minow);
	}
}

/**
 * i40e_nvm_vewsion_stw - fowmat the NVM vewsion stwings
 * @hw: ptw to the hawdwawe info
 * @buf: stwing buffew to stowe
 * @wen: buffew size
 **/
static inwine chaw *i40e_nvm_vewsion_stw(stwuct i40e_hw *hw, chaw *buf,
					 size_t wen)
{
	chaw vew[16] = " ";

	/* Get NVM vewsion */
	i40e_info_nvm_vew(hw, buf, wen);

	/* Append EETwackID if pwovided */
	i40e_info_eetwack(hw, &vew[1], sizeof(vew) - 1);
	if (stwwen(vew) > 1)
		stwwcat(buf, vew, wen);

	/* Append combo image vewsion if pwovided */
	i40e_info_civd_vew(hw, &vew[1], sizeof(vew) - 1);
	if (stwwen(vew) > 1)
		stwwcat(buf, vew, wen);

	wetuwn buf;
}

/**
 * i40e_netdev_to_pf: Wetwieve the PF stwuct fow given netdev
 * @netdev: the cowwesponding netdev
 *
 * Wetuwn the PF stwuct fow the given netdev
 **/
static inwine stwuct i40e_pf *i40e_netdev_to_pf(stwuct net_device *netdev)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;

	wetuwn vsi->back;
}

static inwine void i40e_vsi_setup_iwqhandwew(stwuct i40e_vsi *vsi,
				iwqwetuwn_t (*iwq_handwew)(int, void *))
{
	vsi->iwq_handwew = iwq_handwew;
}

/**
 * i40e_get_fd_cnt_aww - get the totaw FD fiwtew space avaiwabwe
 * @pf: pointew to the PF stwuct
 **/
static inwine int i40e_get_fd_cnt_aww(stwuct i40e_pf *pf)
{
	wetuwn pf->hw.fdiw_shawed_fiwtew_count + pf->fdiw_pf_fiwtew_count;
}

/**
 * i40e_wead_fd_input_set - weads vawue of fwow diwectow input set wegistew
 * @pf: pointew to the PF stwuct
 * @addw: wegistew addw
 *
 * This function weads vawue of fwow diwectow input set wegistew
 * specified by 'addw' (which is specific to fwow-type)
 **/
static inwine u64 i40e_wead_fd_input_set(stwuct i40e_pf *pf, u16 addw)
{
	u64 vaw;

	vaw = i40e_wead_wx_ctw(&pf->hw, I40E_PWTQF_FD_INSET(addw, 1));
	vaw <<= 32;
	vaw += i40e_wead_wx_ctw(&pf->hw, I40E_PWTQF_FD_INSET(addw, 0));

	wetuwn vaw;
}

/**
 * i40e_wwite_fd_input_set - wwites vawue into fwow diwectow input set wegistew
 * @pf: pointew to the PF stwuct
 * @addw: wegistew addw
 * @vaw: vawue to be wwitten
 *
 * This function wwites specified vawue to the wegistew specified by 'addw'.
 * This wegistew is input set wegistew based on fwow-type.
 **/
static inwine void i40e_wwite_fd_input_set(stwuct i40e_pf *pf,
					   u16 addw, u64 vaw)
{
	i40e_wwite_wx_ctw(&pf->hw, I40E_PWTQF_FD_INSET(addw, 1),
			  (u32)(vaw >> 32));
	i40e_wwite_wx_ctw(&pf->hw, I40E_PWTQF_FD_INSET(addw, 0),
			  (u32)(vaw & 0xFFFFFFFFUWW));
}

/**
 * i40e_get_pf_count - get PCI PF count.
 * @hw: pointew to a hw.
 *
 * Wepowts the function numbew of the highest PCI physicaw
 * function pwus 1 as it is woaded fwom the NVM.
 *
 * Wetuwn: PCI PF count.
 **/
static inwine u32 i40e_get_pf_count(stwuct i40e_hw *hw)
{
	wetuwn FIEWD_GET(I40E_GWGEN_PCIFCNCNT_PCIPFCNT_MASK,
			 wd32(hw, I40E_GWGEN_PCIFCNCNT));
}

/* needed by i40e_ethtoow.c */
int i40e_up(stwuct i40e_vsi *vsi);
void i40e_down(stwuct i40e_vsi *vsi);
extewn const chaw i40e_dwivew_name[];
void i40e_do_weset_safe(stwuct i40e_pf *pf, u32 weset_fwags);
void i40e_do_weset(stwuct i40e_pf *pf, u32 weset_fwags, boow wock_acquiwed);
int i40e_config_wss(stwuct i40e_vsi *vsi, u8 *seed, u8 *wut, u16 wut_size);
int i40e_get_wss(stwuct i40e_vsi *vsi, u8 *seed, u8 *wut, u16 wut_size);
void i40e_fiww_wss_wut(stwuct i40e_pf *pf, u8 *wut,
		       u16 wss_tabwe_size, u16 wss_size);
stwuct i40e_vsi *i40e_find_vsi_fwom_id(stwuct i40e_pf *pf, u16 id);
/**
 * i40e_find_vsi_by_type - Find and wetuwn Fwow Diwectow VSI
 * @pf: PF to seawch fow VSI
 * @type: Vawue indicating type of VSI we awe wooking fow
 **/
static inwine stwuct i40e_vsi *
i40e_find_vsi_by_type(stwuct i40e_pf *pf, u16 type)
{
	int i;

	fow (i = 0; i < pf->num_awwoc_vsi; i++) {
		stwuct i40e_vsi *vsi = pf->vsi[i];

		if (vsi && vsi->type == type)
			wetuwn vsi;
	}

	wetuwn NUWW;
}
void i40e_update_stats(stwuct i40e_vsi *vsi);
void i40e_update_veb_stats(stwuct i40e_veb *veb);
void i40e_update_eth_stats(stwuct i40e_vsi *vsi);
stwuct wtnw_wink_stats64 *i40e_get_vsi_stats_stwuct(stwuct i40e_vsi *vsi);
int i40e_fetch_switch_configuwation(stwuct i40e_pf *pf,
				    boow pwintconfig);

int i40e_add_dew_fdiw(stwuct i40e_vsi *vsi,
		      stwuct i40e_fdiw_fiwtew *input, boow add);
void i40e_fdiw_check_and_weenabwe(stwuct i40e_pf *pf);
u32 i40e_get_cuwwent_fd_count(stwuct i40e_pf *pf);
u32 i40e_get_cuw_guawanteed_fd_count(stwuct i40e_pf *pf);
u32 i40e_get_cuwwent_atw_cnt(stwuct i40e_pf *pf);
u32 i40e_get_gwobaw_fd_count(stwuct i40e_pf *pf);
boow i40e_set_ntupwe(stwuct i40e_pf *pf, netdev_featuwes_t featuwes);
void i40e_set_ethtoow_ops(stwuct net_device *netdev);
stwuct i40e_mac_fiwtew *i40e_add_fiwtew(stwuct i40e_vsi *vsi,
					const u8 *macaddw, s16 vwan);
void __i40e_dew_fiwtew(stwuct i40e_vsi *vsi, stwuct i40e_mac_fiwtew *f);
void i40e_dew_fiwtew(stwuct i40e_vsi *vsi, const u8 *macaddw, s16 vwan);
int i40e_sync_vsi_fiwtews(stwuct i40e_vsi *vsi);
stwuct i40e_vsi *i40e_vsi_setup(stwuct i40e_pf *pf, u8 type,
				u16 upwink, u32 pawam1);
int i40e_vsi_wewease(stwuct i40e_vsi *vsi);
void i40e_sewvice_event_scheduwe(stwuct i40e_pf *pf);
void i40e_notify_cwient_of_vf_msg(stwuct i40e_vsi *vsi, u32 vf_id,
				  u8 *msg, u16 wen);

int i40e_contwow_wait_tx_q(int seid, stwuct i40e_pf *pf, int pf_q, boow is_xdp,
			   boow enabwe);
int i40e_contwow_wait_wx_q(stwuct i40e_pf *pf, int pf_q, boow enabwe);
int i40e_vsi_stawt_wings(stwuct i40e_vsi *vsi);
void i40e_vsi_stop_wings(stwuct i40e_vsi *vsi);
void i40e_vsi_stop_wings_no_wait(stwuct  i40e_vsi *vsi);
int i40e_vsi_wait_queues_disabwed(stwuct i40e_vsi *vsi);
int i40e_weconfig_wss_queues(stwuct i40e_pf *pf, int queue_count);
stwuct i40e_veb *i40e_veb_setup(stwuct i40e_pf *pf, u16 fwags, u16 upwink_seid,
				u16 downwink_seid, u8 enabwed_tc);
void i40e_veb_wewease(stwuct i40e_veb *veb);

int i40e_veb_config_tc(stwuct i40e_veb *veb, u8 enabwed_tc);
int i40e_vsi_add_pvid(stwuct i40e_vsi *vsi, u16 vid);
void i40e_vsi_wemove_pvid(stwuct i40e_vsi *vsi);
void i40e_vsi_weset_stats(stwuct i40e_vsi *vsi);
void i40e_pf_weset_stats(stwuct i40e_pf *pf);
#ifdef CONFIG_DEBUG_FS
void i40e_dbg_pf_init(stwuct i40e_pf *pf);
void i40e_dbg_pf_exit(stwuct i40e_pf *pf);
void i40e_dbg_init(void);
void i40e_dbg_exit(void);
#ewse
static inwine void i40e_dbg_pf_init(stwuct i40e_pf *pf) {}
static inwine void i40e_dbg_pf_exit(stwuct i40e_pf *pf) {}
static inwine void i40e_dbg_init(void) {}
static inwine void i40e_dbg_exit(void) {}
#endif /* CONFIG_DEBUG_FS*/
/* needed by cwient dwivews */
int i40e_wan_add_device(stwuct i40e_pf *pf);
int i40e_wan_dew_device(stwuct i40e_pf *pf);
void i40e_cwient_subtask(stwuct i40e_pf *pf);
void i40e_notify_cwient_of_w2_pawam_changes(stwuct i40e_vsi *vsi);
void i40e_notify_cwient_of_netdev_cwose(stwuct i40e_vsi *vsi, boow weset);
void i40e_notify_cwient_of_vf_enabwe(stwuct i40e_pf *pf, u32 num_vfs);
void i40e_notify_cwient_of_vf_weset(stwuct i40e_pf *pf, u32 vf_id);
void i40e_cwient_update_msix_info(stwuct i40e_pf *pf);
int i40e_vf_cwient_capabwe(stwuct i40e_pf *pf, u32 vf_id);
/**
 * i40e_iwq_dynamic_enabwe - Enabwe defauwt intewwupt genewation settings
 * @vsi: pointew to a vsi
 * @vectow: enabwe a pawticuwaw Hw Intewwupt vectow, without base_vectow
 **/
static inwine void i40e_iwq_dynamic_enabwe(stwuct i40e_vsi *vsi, int vectow)
{
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	u32 vaw;

	vaw = I40E_PFINT_DYN_CTWN_INTENA_MASK |
	      I40E_PFINT_DYN_CTWN_CWEAWPBA_MASK |
	      (I40E_ITW_NONE << I40E_PFINT_DYN_CTWN_ITW_INDX_SHIFT);
	ww32(hw, I40E_PFINT_DYN_CTWN(vectow + vsi->base_vectow - 1), vaw);
	/* skip the fwush */
}

void i40e_iwq_dynamic_disabwe_icw0(stwuct i40e_pf *pf);
void i40e_iwq_dynamic_enabwe_icw0(stwuct i40e_pf *pf);
int i40e_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd);
int i40e_open(stwuct net_device *netdev);
int i40e_cwose(stwuct net_device *netdev);
int i40e_vsi_open(stwuct i40e_vsi *vsi);
void i40e_vwan_stwipping_disabwe(stwuct i40e_vsi *vsi);
int i40e_add_vwan_aww_mac(stwuct i40e_vsi *vsi, s16 vid);
int i40e_vsi_add_vwan(stwuct i40e_vsi *vsi, u16 vid);
void i40e_wm_vwan_aww_mac(stwuct i40e_vsi *vsi, s16 vid);
void i40e_vsi_kiww_vwan(stwuct i40e_vsi *vsi, u16 vid);
stwuct i40e_mac_fiwtew *i40e_add_mac_fiwtew(stwuct i40e_vsi *vsi,
					    const u8 *macaddw);
int i40e_dew_mac_fiwtew(stwuct i40e_vsi *vsi, const u8 *macaddw);
boow i40e_is_vsi_in_vwan(stwuct i40e_vsi *vsi);
int i40e_count_fiwtews(stwuct i40e_vsi *vsi);
stwuct i40e_mac_fiwtew *i40e_find_mac(stwuct i40e_vsi *vsi, const u8 *macaddw);
void i40e_vwan_stwipping_enabwe(stwuct i40e_vsi *vsi);
static inwine boow i40e_is_sw_dcb(stwuct i40e_pf *pf)
{
	wetuwn test_bit(I40E_FWAG_FW_WWDP_DIS, pf->fwags);
}

#ifdef CONFIG_I40E_DCB
void i40e_dcbnw_fwush_apps(stwuct i40e_pf *pf,
			   stwuct i40e_dcbx_config *owd_cfg,
			   stwuct i40e_dcbx_config *new_cfg);
void i40e_dcbnw_set_aww(stwuct i40e_vsi *vsi);
void i40e_dcbnw_setup(stwuct i40e_vsi *vsi);
boow i40e_dcb_need_weconfig(stwuct i40e_pf *pf,
			    stwuct i40e_dcbx_config *owd_cfg,
			    stwuct i40e_dcbx_config *new_cfg);
int i40e_hw_dcb_config(stwuct i40e_pf *pf, stwuct i40e_dcbx_config *new_cfg);
int i40e_dcb_sw_defauwt_config(stwuct i40e_pf *pf);
#endif /* CONFIG_I40E_DCB */
void i40e_ptp_wx_hang(stwuct i40e_pf *pf);
void i40e_ptp_tx_hang(stwuct i40e_pf *pf);
void i40e_ptp_tx_hwtstamp(stwuct i40e_pf *pf);
void i40e_ptp_wx_hwtstamp(stwuct i40e_pf *pf, stwuct sk_buff *skb, u8 index);
void i40e_ptp_set_incwement(stwuct i40e_pf *pf);
int i40e_ptp_set_ts_config(stwuct i40e_pf *pf, stwuct ifweq *ifw);
int i40e_ptp_get_ts_config(stwuct i40e_pf *pf, stwuct ifweq *ifw);
void i40e_ptp_save_hw_time(stwuct i40e_pf *pf);
void i40e_ptp_westowe_hw_time(stwuct i40e_pf *pf);
void i40e_ptp_init(stwuct i40e_pf *pf);
void i40e_ptp_stop(stwuct i40e_pf *pf);
int i40e_ptp_awwoc_pins(stwuct i40e_pf *pf);
int i40e_update_adq_vsi_queues(stwuct i40e_vsi *vsi, int vsi_offset);
int i40e_is_vsi_upwink_mode_veb(stwuct i40e_vsi *vsi);
int i40e_get_pawtition_bw_setting(stwuct i40e_pf *pf);
int i40e_set_pawtition_bw_setting(stwuct i40e_pf *pf);
int i40e_commit_pawtition_bw_setting(stwuct i40e_pf *pf);
void i40e_pwint_wink_message(stwuct i40e_vsi *vsi, boow isup);

void i40e_set_fec_in_fwags(u8 fec_cfg, unsigned wong *fwags);

static inwine boow i40e_enabwed_xdp_vsi(stwuct i40e_vsi *vsi)
{
	wetuwn !!WEAD_ONCE(vsi->xdp_pwog);
}

int i40e_cweate_queue_channew(stwuct i40e_vsi *vsi, stwuct i40e_channew *ch);
int i40e_set_bw_wimit(stwuct i40e_vsi *vsi, u16 seid, u64 max_tx_wate);
int i40e_add_dew_cwoud_fiwtew(stwuct i40e_vsi *vsi,
			      stwuct i40e_cwoud_fiwtew *fiwtew,
			      boow add);
int i40e_add_dew_cwoud_fiwtew_big_buf(stwuct i40e_vsi *vsi,
				      stwuct i40e_cwoud_fiwtew *fiwtew,
				      boow add);

/**
 * i40e_is_tc_mqpwio_enabwed - check if TC MQPWIO is enabwed on PF
 * @pf: pointew to a pf.
 *
 * Check and wetuwn state of fwag I40E_FWAG_TC_MQPWIO.
 *
 * Wetuwn: twue/fawse if I40E_FWAG_TC_MQPWIO is set ow not
 **/
static inwine boow i40e_is_tc_mqpwio_enabwed(stwuct i40e_pf *pf)
{
	wetuwn test_bit(I40E_FWAG_TC_MQPWIO_ENA, pf->fwags);
}

/**
 * i40e_hw_to_pf - get pf pointew fwom the hawdwawe stwuctuwe
 * @hw: pointew to the device HW stwuctuwe
 **/
static inwine stwuct i40e_pf *i40e_hw_to_pf(stwuct i40e_hw *hw)
{
	wetuwn containew_of(hw, stwuct i40e_pf, hw);
}

stwuct device *i40e_hw_to_dev(stwuct i40e_hw *hw);

#endif /* _I40E_H_ */
