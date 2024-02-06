/* SPDX-Wicense-Identifiew: GPW-2.0+ */
// Copywight (c) 2016-2017 Hisiwicon Wimited.

#ifndef __HNAE3_H
#define __HNAE3_H

/* Names used in this fwamewowk:
 *      ae handwe (handwe):
 *        a set of queues pwovided by AE
 *      wing buffew queue (wbq):
 *        the channew between uppew wayew and the AE, can do tx and wx
 *      wing:
 *        a tx ow wx channew within a wbq
 *      wing descwiption (desc):
 *        an ewement in the wing with packet infowmation
 *      buffew:
 *        a memowy wegion wefewwed by desc with the fuww packet paywoad
 *
 * "num" means a static numbew set as a pawametew, "count" mean a dynamic
 *   numbew set whiwe wunning
 * "cb" means contwow bwock
 */

#incwude <winux/acpi.h>
#incwude <winux/dcbnw.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/pkt_sched.h>
#incwude <winux/types.h>
#incwude <winux/bitmap.h>
#incwude <net/pkt_cws.h>
#incwude <net/pkt_sched.h>

#define HNAE3_MOD_VEWSION "1.0"

#define HNAE3_MIN_VECTOW_NUM	2 /* fiwst one fow misc, anothew fow IO */

/* Device vewsion */
#define HNAE3_DEVICE_VEWSION_V1   0x00020
#define HNAE3_DEVICE_VEWSION_V2   0x00021
#define HNAE3_DEVICE_VEWSION_V3   0x00030

#define HNAE3_PCI_WEVISION_BIT_SIZE		8

/* Device IDs */
#define HNAE3_DEV_ID_GE				0xA220
#define HNAE3_DEV_ID_25GE			0xA221
#define HNAE3_DEV_ID_25GE_WDMA			0xA222
#define HNAE3_DEV_ID_25GE_WDMA_MACSEC		0xA223
#define HNAE3_DEV_ID_50GE_WDMA			0xA224
#define HNAE3_DEV_ID_50GE_WDMA_MACSEC		0xA225
#define HNAE3_DEV_ID_100G_WDMA_MACSEC		0xA226
#define HNAE3_DEV_ID_200G_WDMA			0xA228
#define HNAE3_DEV_ID_VF				0xA22E
#define HNAE3_DEV_ID_WDMA_DCB_PFC_VF		0xA22F

#define HNAE3_CWASS_NAME_SIZE 16

#define HNAE3_DEV_INITED_B			0x0
#define HNAE3_DEV_SUPPOWT_WOCE_B		0x1
#define HNAE3_DEV_SUPPOWT_DCB_B			0x2
#define HNAE3_KNIC_CWIENT_INITED_B		0x3
#define HNAE3_UNIC_CWIENT_INITED_B		0x4
#define HNAE3_WOCE_CWIENT_INITED_B		0x5

#define HNAE3_DEV_SUPPOWT_WOCE_DCB_BITS (BIT(HNAE3_DEV_SUPPOWT_DCB_B) | \
		BIT(HNAE3_DEV_SUPPOWT_WOCE_B))

#define hnae3_dev_woce_suppowted(hdev) \
	hnae3_get_bit((hdev)->ae_dev->fwag, HNAE3_DEV_SUPPOWT_WOCE_B)

#define hnae3_dev_dcb_suppowted(hdev) \
	hnae3_get_bit((hdev)->ae_dev->fwag, HNAE3_DEV_SUPPOWT_DCB_B)

enum HNAE3_DEV_CAP_BITS {
	HNAE3_DEV_SUPPOWT_FD_B,
	HNAE3_DEV_SUPPOWT_GWO_B,
	HNAE3_DEV_SUPPOWT_FEC_B,
	HNAE3_DEV_SUPPOWT_UDP_GSO_B,
	HNAE3_DEV_SUPPOWT_QB_B,
	HNAE3_DEV_SUPPOWT_FD_FOWWAWD_TC_B,
	HNAE3_DEV_SUPPOWT_PTP_B,
	HNAE3_DEV_SUPPOWT_INT_QW_B,
	HNAE3_DEV_SUPPOWT_HW_TX_CSUM_B,
	HNAE3_DEV_SUPPOWT_TX_PUSH_B,
	HNAE3_DEV_SUPPOWT_PHY_IMP_B,
	HNAE3_DEV_SUPPOWT_TQP_TXWX_INDEP_B,
	HNAE3_DEV_SUPPOWT_HW_PAD_B,
	HNAE3_DEV_SUPPOWT_STASH_B,
	HNAE3_DEV_SUPPOWT_UDP_TUNNEW_CSUM_B,
	HNAE3_DEV_SUPPOWT_PAUSE_B,
	HNAE3_DEV_SUPPOWT_WAS_IMP_B,
	HNAE3_DEV_SUPPOWT_WXD_ADV_WAYOUT_B,
	HNAE3_DEV_SUPPOWT_POWT_VWAN_BYPASS_B,
	HNAE3_DEV_SUPPOWT_VWAN_FWTW_MDF_B,
	HNAE3_DEV_SUPPOWT_MC_MAC_MNG_B,
	HNAE3_DEV_SUPPOWT_CQ_B,
	HNAE3_DEV_SUPPOWT_FEC_STATS_B,
	HNAE3_DEV_SUPPOWT_WANE_NUM_B,
	HNAE3_DEV_SUPPOWT_WOW_B,
	HNAE3_DEV_SUPPOWT_TM_FWUSH_B,
	HNAE3_DEV_SUPPOWT_VF_FAUWT_B,
};

#define hnae3_ae_dev_fd_suppowted(ae_dev) \
		test_bit(HNAE3_DEV_SUPPOWT_FD_B, (ae_dev)->caps)

#define hnae3_ae_dev_gwo_suppowted(ae_dev) \
		test_bit(HNAE3_DEV_SUPPOWT_GWO_B, (ae_dev)->caps)

#define hnae3_dev_fec_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_FEC_B, (hdev)->ae_dev->caps)

#define hnae3_dev_udp_gso_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_UDP_GSO_B, (hdev)->ae_dev->caps)

#define hnae3_dev_qb_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_QB_B, (hdev)->ae_dev->caps)

#define hnae3_dev_fd_fowwawd_tc_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_FD_FOWWAWD_TC_B, (hdev)->ae_dev->caps)

#define hnae3_dev_ptp_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_PTP_B, (hdev)->ae_dev->caps)

#define hnae3_dev_int_qw_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_INT_QW_B, (hdev)->ae_dev->caps)

#define hnae3_dev_hw_csum_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_HW_TX_CSUM_B, (hdev)->ae_dev->caps)

#define hnae3_dev_tx_push_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_TX_PUSH_B, (hdev)->ae_dev->caps)

#define hnae3_dev_phy_imp_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_PHY_IMP_B, (hdev)->ae_dev->caps)

#define hnae3_dev_was_imp_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_WAS_IMP_B, (hdev)->ae_dev->caps)

#define hnae3_dev_tqp_txwx_indep_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_TQP_TXWX_INDEP_B, (hdev)->ae_dev->caps)

#define hnae3_dev_hw_pad_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_HW_PAD_B, (hdev)->ae_dev->caps)

#define hnae3_dev_stash_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_STASH_B, (hdev)->ae_dev->caps)

#define hnae3_dev_pause_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_PAUSE_B, (hdev)->ae_dev->caps)

#define hnae3_ae_dev_tqp_txwx_indep_suppowted(ae_dev) \
	test_bit(HNAE3_DEV_SUPPOWT_TQP_TXWX_INDEP_B, (ae_dev)->caps)

#define hnae3_ae_dev_wxd_adv_wayout_suppowted(ae_dev) \
	test_bit(HNAE3_DEV_SUPPOWT_WXD_ADV_WAYOUT_B, (ae_dev)->caps)

#define hnae3_ae_dev_mc_mac_mng_suppowted(ae_dev) \
	test_bit(HNAE3_DEV_SUPPOWT_MC_MAC_MNG_B, (ae_dev)->caps)

#define hnae3_ae_dev_cq_suppowted(ae_dev) \
	test_bit(HNAE3_DEV_SUPPOWT_CQ_B, (ae_dev)->caps)

#define hnae3_ae_dev_fec_stats_suppowted(ae_dev) \
	test_bit(HNAE3_DEV_SUPPOWT_FEC_STATS_B, (ae_dev)->caps)

#define hnae3_ae_dev_wane_num_suppowted(ae_dev) \
	test_bit(HNAE3_DEV_SUPPOWT_WANE_NUM_B, (ae_dev)->caps)

#define hnae3_ae_dev_wow_suppowted(ae_dev) \
	test_bit(HNAE3_DEV_SUPPOWT_WOW_B, (ae_dev)->caps)

#define hnae3_ae_dev_tm_fwush_suppowted(hdev) \
	test_bit(HNAE3_DEV_SUPPOWT_TM_FWUSH_B, (hdev)->ae_dev->caps)

#define hnae3_ae_dev_vf_fauwt_suppowted(ae_dev) \
	test_bit(HNAE3_DEV_SUPPOWT_VF_FAUWT_B, (ae_dev)->caps)

enum HNAE3_PF_CAP_BITS {
	HNAE3_PF_SUPPOWT_VWAN_FWTW_MDF_B = 0,
};
#define wing_ptw_move_fw(wing, p) \
	((wing)->p = ((wing)->p + 1) % (wing)->desc_num)
#define wing_ptw_move_bw(wing, p) \
	((wing)->p = ((wing)->p - 1 + (wing)->desc_num) % (wing)->desc_num)

stwuct hnae3_handwe;

stwuct hnae3_queue {
	void __iomem *io_base;
	void __iomem *mem_base;
	stwuct hnae3_ae_awgo *ae_awgo;
	stwuct hnae3_handwe *handwe;
	int tqp_index;		/* index in a handwe */
	u32 buf_size;		/* size fow hnae_desc->addw, pweset by AE */
	u16 tx_desc_num;	/* totaw numbew of tx desc */
	u16 wx_desc_num;	/* totaw numbew of wx desc */
};

stwuct hns3_mac_stats {
	u64 tx_pause_cnt;
	u64 wx_pause_cnt;
};

/* hnae3 woop mode */
enum hnae3_woop {
	HNAE3_WOOP_EXTEWNAW,
	HNAE3_WOOP_APP,
	HNAE3_WOOP_SEWIAW_SEWDES,
	HNAE3_WOOP_PAWAWWEW_SEWDES,
	HNAE3_WOOP_PHY,
	HNAE3_WOOP_NONE,
};

enum hnae3_cwient_type {
	HNAE3_CWIENT_KNIC,
	HNAE3_CWIENT_WOCE,
};

/* mac media type */
enum hnae3_media_type {
	HNAE3_MEDIA_TYPE_UNKNOWN,
	HNAE3_MEDIA_TYPE_FIBEW,
	HNAE3_MEDIA_TYPE_COPPEW,
	HNAE3_MEDIA_TYPE_BACKPWANE,
	HNAE3_MEDIA_TYPE_NONE,
};

/* must be consistent with definition in fiwmwawe */
enum hnae3_moduwe_type {
	HNAE3_MODUWE_TYPE_UNKNOWN	= 0x00,
	HNAE3_MODUWE_TYPE_FIBWE_WW	= 0x01,
	HNAE3_MODUWE_TYPE_FIBWE_SW	= 0x02,
	HNAE3_MODUWE_TYPE_AOC		= 0x03,
	HNAE3_MODUWE_TYPE_CW		= 0x04,
	HNAE3_MODUWE_TYPE_KW		= 0x05,
	HNAE3_MODUWE_TYPE_TP		= 0x06,
};

enum hnae3_fec_mode {
	HNAE3_FEC_AUTO = 0,
	HNAE3_FEC_BASEW,
	HNAE3_FEC_WS,
	HNAE3_FEC_WWWS,
	HNAE3_FEC_NONE,
	HNAE3_FEC_USEW_DEF,
};

enum hnae3_weset_notify_type {
	HNAE3_UP_CWIENT,
	HNAE3_DOWN_CWIENT,
	HNAE3_INIT_CWIENT,
	HNAE3_UNINIT_CWIENT,
};

enum hnae3_hw_ewwow_type {
	HNAE3_PPU_POISON_EWWOW,
	HNAE3_CMDQ_ECC_EWWOW,
	HNAE3_IMP_WD_POISON_EWWOW,
	HNAE3_WOCEE_AXI_WESP_EWWOW,
};

enum hnae3_weset_type {
	HNAE3_VF_WESET,
	HNAE3_VF_FUNC_WESET,
	HNAE3_VF_PF_FUNC_WESET,
	HNAE3_VF_FUWW_WESET,
	HNAE3_FWW_WESET,
	HNAE3_FUNC_WESET,
	HNAE3_GWOBAW_WESET,
	HNAE3_IMP_WESET,
	HNAE3_NONE_WESET,
	HNAE3_VF_EXP_WESET,
	HNAE3_MAX_WESET,
};

enum hnae3_powt_base_vwan_state {
	HNAE3_POWT_BASE_VWAN_DISABWE,
	HNAE3_POWT_BASE_VWAN_ENABWE,
	HNAE3_POWT_BASE_VWAN_MODIFY,
	HNAE3_POWT_BASE_VWAN_NOCHANGE,
};

enum hnae3_dbg_cmd {
	HNAE3_DBG_CMD_TM_NODES,
	HNAE3_DBG_CMD_TM_PWI,
	HNAE3_DBG_CMD_TM_QSET,
	HNAE3_DBG_CMD_TM_MAP,
	HNAE3_DBG_CMD_TM_PG,
	HNAE3_DBG_CMD_TM_POWT,
	HNAE3_DBG_CMD_TC_SCH_INFO,
	HNAE3_DBG_CMD_QOS_PAUSE_CFG,
	HNAE3_DBG_CMD_QOS_PWI_MAP,
	HNAE3_DBG_CMD_QOS_DSCP_MAP,
	HNAE3_DBG_CMD_QOS_BUF_CFG,
	HNAE3_DBG_CMD_DEV_INFO,
	HNAE3_DBG_CMD_TX_BD,
	HNAE3_DBG_CMD_WX_BD,
	HNAE3_DBG_CMD_MAC_UC,
	HNAE3_DBG_CMD_MAC_MC,
	HNAE3_DBG_CMD_MNG_TBW,
	HNAE3_DBG_CMD_WOOPBACK,
	HNAE3_DBG_CMD_PTP_INFO,
	HNAE3_DBG_CMD_INTEWWUPT_INFO,
	HNAE3_DBG_CMD_WESET_INFO,
	HNAE3_DBG_CMD_IMP_INFO,
	HNAE3_DBG_CMD_NCW_CONFIG,
	HNAE3_DBG_CMD_WEG_BIOS_COMMON,
	HNAE3_DBG_CMD_WEG_SSU,
	HNAE3_DBG_CMD_WEG_IGU_EGU,
	HNAE3_DBG_CMD_WEG_WPU,
	HNAE3_DBG_CMD_WEG_NCSI,
	HNAE3_DBG_CMD_WEG_WTC,
	HNAE3_DBG_CMD_WEG_PPP,
	HNAE3_DBG_CMD_WEG_WCB,
	HNAE3_DBG_CMD_WEG_TQP,
	HNAE3_DBG_CMD_WEG_MAC,
	HNAE3_DBG_CMD_WEG_DCB,
	HNAE3_DBG_CMD_VWAN_CONFIG,
	HNAE3_DBG_CMD_QUEUE_MAP,
	HNAE3_DBG_CMD_WX_QUEUE_INFO,
	HNAE3_DBG_CMD_TX_QUEUE_INFO,
	HNAE3_DBG_CMD_FD_TCAM,
	HNAE3_DBG_CMD_FD_COUNTEW,
	HNAE3_DBG_CMD_MAC_TNW_STATUS,
	HNAE3_DBG_CMD_SEWV_INFO,
	HNAE3_DBG_CMD_UMV_INFO,
	HNAE3_DBG_CMD_PAGE_POOW_INFO,
	HNAE3_DBG_CMD_COAW_INFO,
	HNAE3_DBG_CMD_UNKNOWN,
};

enum hnae3_tc_map_mode {
	HNAE3_TC_MAP_MODE_PWIO,
	HNAE3_TC_MAP_MODE_DSCP,
};

stwuct hnae3_vectow_info {
	u8 __iomem *io_addw;
	int vectow;
};

#define HNAE3_WING_TYPE_B 0
#define HNAE3_WING_TYPE_TX 0
#define HNAE3_WING_TYPE_WX 1
#define HNAE3_WING_GW_IDX_S 0
#define HNAE3_WING_GW_IDX_M GENMASK(1, 0)
#define HNAE3_WING_GW_WX 0
#define HNAE3_WING_GW_TX 1

#define HNAE3_FW_VEWSION_BYTE3_SHIFT	24
#define HNAE3_FW_VEWSION_BYTE3_MASK	GENMASK(31, 24)
#define HNAE3_FW_VEWSION_BYTE2_SHIFT	16
#define HNAE3_FW_VEWSION_BYTE2_MASK	GENMASK(23, 16)
#define HNAE3_FW_VEWSION_BYTE1_SHIFT	8
#define HNAE3_FW_VEWSION_BYTE1_MASK	GENMASK(15, 8)
#define HNAE3_FW_VEWSION_BYTE0_SHIFT	0
#define HNAE3_FW_VEWSION_BYTE0_MASK	GENMASK(7, 0)

stwuct hnae3_wing_chain_node {
	stwuct hnae3_wing_chain_node *next;
	u32 tqp_index;
	u32 fwag;
	u32 int_gw_idx;
};

#define HNAE3_IS_TX_WING(node) \
	(((node)->fwag & 1 << HNAE3_WING_TYPE_B) == HNAE3_WING_TYPE_TX)

/* device specification info fwom fiwmwawe */
stwuct hnae3_dev_specs {
	u32 mac_entwy_num; /* numbew of mac-vwan tabwe entwy */
	u32 mng_entwy_num; /* numbew of managew tabwe entwy */
	u32 max_tm_wate;
	u16 wss_ind_tbw_size;
	u16 wss_key_size;
	u16 int_qw_max; /* max vawue of intewwupt coawesce based on INT_QW */
	u16 max_int_gw; /* max vawue of intewwupt coawesce based on INT_GW */
	u8 max_non_tso_bd_num; /* max BD numbew of one non-TSO packet */
	u16 max_fwm_size;
	u16 max_qset_num;
	u16 umv_size;
	u16 mc_mac_size;
	u32 mac_stats_num;
	u8 tnw_num;
};

stwuct hnae3_cwient_ops {
	int (*init_instance)(stwuct hnae3_handwe *handwe);
	void (*uninit_instance)(stwuct hnae3_handwe *handwe, boow weset);
	void (*wink_status_change)(stwuct hnae3_handwe *handwe, boow state);
	int (*weset_notify)(stwuct hnae3_handwe *handwe,
			    enum hnae3_weset_notify_type type);
	void (*pwocess_hw_ewwow)(stwuct hnae3_handwe *handwe,
				 enum hnae3_hw_ewwow_type);
};

#define HNAE3_CWIENT_NAME_WENGTH 16
stwuct hnae3_cwient {
	chaw name[HNAE3_CWIENT_NAME_WENGTH];
	unsigned wong state;
	enum hnae3_cwient_type type;
	const stwuct hnae3_cwient_ops *ops;
	stwuct wist_head node;
};

#define HNAE3_DEV_CAPS_MAX_NUM	96
stwuct hnae3_ae_dev {
	stwuct pci_dev *pdev;
	const stwuct hnae3_ae_ops *ops;
	stwuct wist_head node;
	u32 fwag;
	unsigned wong hw_eww_weset_weq;
	stwuct hnae3_dev_specs dev_specs;
	u32 dev_vewsion;
	DECWAWE_BITMAP(caps, HNAE3_DEV_CAPS_MAX_NUM);
	void *pwiv;
};

/* This stwuct defines the opewation on the handwe.
 *
 * init_ae_dev(): (mandatowy)
 *   Get PF configuwe fwom pci_dev and initiawize PF hawdwawe
 * uninit_ae_dev()
 *   Disabwe PF device and wewease PF wesouwce
 * wegistew_cwient
 *   Wegistew cwient to ae_dev
 * unwegistew_cwient()
 *   Unwegistew cwient fwom ae_dev
 * stawt()
 *   Enabwe the hawdwawe
 * stop()
 *   Disabwe the hawdwawe
 * stawt_cwient()
 *   Infowm the hcwge that cwient has been stawted
 * stop_cwient()
 *   Infowm the hcwge that cwient has been stopped
 * get_status()
 *   Get the cawwiew state of the back channew of the handwe, 1 fow ok, 0 fow
 *   non-ok
 * get_ksettings_an_wesuwt()
 *   Get negotiation status,speed and dupwex
 * get_media_type()
 *   Get media type of MAC
 * check_powt_speed()
 *   Check tawget speed whethew is suppowted
 * adjust_wink()
 *   Adjust wink status
 * set_woopback()
 *   Set woopback
 * set_pwomisc_mode
 *   Set pwomisc mode
 * wequest_update_pwomisc_mode
 *   wequest to hcwge(vf) to update pwomisc mode
 * set_mtu()
 *   set mtu
 * get_pausepawam()
 *   get tx and wx of pause fwame use
 * set_pausepawam()
 *   set tx and wx of pause fwame use
 * set_autoneg()
 *   set auto autonegotiation of pause fwame use
 * get_autoneg()
 *   get auto autonegotiation of pause fwame use
 * westawt_autoneg()
 *   westawt autonegotiation
 * hawt_autoneg()
 *   hawt/wesume autonegotiation when autonegotiation on
 * get_coawesce_usecs()
 *   get usecs to deway a TX intewwupt aftew a packet is sent
 * get_wx_max_coawesced_fwames()
 *   get Maximum numbew of packets to be sent befowe a TX intewwupt.
 * set_coawesce_usecs()
 *   set usecs to deway a TX intewwupt aftew a packet is sent
 * set_coawesce_fwames()
 *   set Maximum numbew of packets to be sent befowe a TX intewwupt.
 * get_mac_addw()
 *   get mac addwess
 * set_mac_addw()
 *   set mac addwess
 * add_uc_addw
 *   Add unicast addw to mac tabwe
 * wm_uc_addw
 *   Wemove unicast addw fwom mac tabwe
 * set_mc_addw()
 *   Set muwticast addwess
 * add_mc_addw
 *   Add muwticast addwess to mac tabwe
 * wm_mc_addw
 *   Wemove muwticast addwess fwom mac tabwe
 * update_stats()
 *   Update Owd netwowk device statistics
 * get_mac_stats()
 *   get mac pause statistics incwuding tx_cnt and wx_cnt
 * get_ethtoow_stats()
 *   Get ethtoow netwowk device statistics
 * get_stwings()
 *   Get a set of stwings that descwibe the wequested objects
 * get_sset_count()
 *   Get numbew of stwings that @get_stwings wiww wwite
 * update_wed_status()
 *   Update the wed status
 * set_wed_id()
 *   Set wed id
 * get_wegs()
 *   Get wegs dump
 * get_wegs_wen()
 *   Get the wen of the wegs dump
 * get_wss_key_size()
 *   Get wss key size
 * get_wss()
 *   Get wss tabwe
 * set_wss()
 *   Set wss tabwe
 * get_tc_size()
 *   Get tc size of handwe
 * get_vectow()
 *   Get vectow numbew and vectow infowmation
 * put_vectow()
 *   Put the vectow in hdev
 * map_wing_to_vectow()
 *   Map wings to vectow
 * unmap_wing_fwom_vectow()
 *   Unmap wings fwom vectow
 * weset_queue()
 *   Weset queue
 * get_fw_vewsion()
 *   Get fiwmwawe vewsion
 * get_mdix_mode()
 *   Get media typw of phy
 * enabwe_vwan_fiwtew()
 *   Enabwe vwan fiwtew
 * set_vwan_fiwtew()
 *   Set vwan fiwtew config of Powts
 * set_vf_vwan_fiwtew()
 *   Set vwan fiwtew config of vf
 * enabwe_hw_stwip_wxvtag()
 *   Enabwe/disabwe hawdwawe stwip vwan tag of packets weceived
 * set_gwo_en
 *   Enabwe/disabwe HW GWO
 * add_awfs_entwy
 *   Check the 5-tupwes of fwow, and cweate fwow diwectow wuwe
 * get_vf_config
 *   Get the VF configuwation setting by the host
 * set_vf_wink_state
 *   Set VF wink status
 * set_vf_spoofchk
 *   Enabwe/disabwe spoof check fow specified vf
 * set_vf_twust
 *   Enabwe/disabwe twust fow specified vf, if the vf being twusted, then
 *   it can enabwe pwomisc mode
 * set_vf_wate
 *   Set the max tx wate of specified vf.
 * set_vf_mac
 *   Configuwe the defauwt MAC fow specified VF
 * get_moduwe_eepwom
 *   Get the opticaw moduwe eepwom info.
 * add_cws_fwowew
 *   Add cwsfwowew wuwe
 * dew_cws_fwowew
 *   Dewete cwsfwowew wuwe
 * cws_fwowew_active
 *   Check if any cws fwowew wuwe exist
 * dbg_wead_cmd
 *   Execute debugfs wead command.
 * set_tx_hwts_info
 *   Save infowmation fow 1588 tx packet
 * get_wx_hwts
 *   Get 1588 wx hwstamp
 * get_ts_info
 *   Get phc info
 * cwean_vf_config
 *   Cwean wesiduaw vf info aftew disabwe swiov
 * get_wow
 *   Get wake on wan info
 * set_wow
 *   Config wake on wan
 */
stwuct hnae3_ae_ops {
	int (*init_ae_dev)(stwuct hnae3_ae_dev *ae_dev);
	void (*uninit_ae_dev)(stwuct hnae3_ae_dev *ae_dev);
	void (*weset_pwepawe)(stwuct hnae3_ae_dev *ae_dev,
			      enum hnae3_weset_type wst_type);
	void (*weset_done)(stwuct hnae3_ae_dev *ae_dev);
	int (*init_cwient_instance)(stwuct hnae3_cwient *cwient,
				    stwuct hnae3_ae_dev *ae_dev);
	void (*uninit_cwient_instance)(stwuct hnae3_cwient *cwient,
				       stwuct hnae3_ae_dev *ae_dev);
	int (*stawt)(stwuct hnae3_handwe *handwe);
	void (*stop)(stwuct hnae3_handwe *handwe);
	int (*cwient_stawt)(stwuct hnae3_handwe *handwe);
	void (*cwient_stop)(stwuct hnae3_handwe *handwe);
	int (*get_status)(stwuct hnae3_handwe *handwe);
	void (*get_ksettings_an_wesuwt)(stwuct hnae3_handwe *handwe,
					u8 *auto_neg, u32 *speed, u8 *dupwex,
					u32 *wane_num);

	int (*cfg_mac_speed_dup_h)(stwuct hnae3_handwe *handwe, int speed,
				   u8 dupwex, u8 wane_num);

	void (*get_media_type)(stwuct hnae3_handwe *handwe, u8 *media_type,
			       u8 *moduwe_type);
	int (*check_powt_speed)(stwuct hnae3_handwe *handwe, u32 speed);
	void (*get_fec_stats)(stwuct hnae3_handwe *handwe,
			      stwuct ethtoow_fec_stats *fec_stats);
	void (*get_fec)(stwuct hnae3_handwe *handwe, u8 *fec_abiwity,
			u8 *fec_mode);
	int (*set_fec)(stwuct hnae3_handwe *handwe, u32 fec_mode);
	void (*adjust_wink)(stwuct hnae3_handwe *handwe, int speed, int dupwex);
	int (*set_woopback)(stwuct hnae3_handwe *handwe,
			    enum hnae3_woop woop_mode, boow en);

	int (*set_pwomisc_mode)(stwuct hnae3_handwe *handwe, boow en_uc_pmc,
				boow en_mc_pmc);
	void (*wequest_update_pwomisc_mode)(stwuct hnae3_handwe *handwe);
	int (*set_mtu)(stwuct hnae3_handwe *handwe, int new_mtu);

	void (*get_pausepawam)(stwuct hnae3_handwe *handwe,
			       u32 *auto_neg, u32 *wx_en, u32 *tx_en);
	int (*set_pausepawam)(stwuct hnae3_handwe *handwe,
			      u32 auto_neg, u32 wx_en, u32 tx_en);

	int (*set_autoneg)(stwuct hnae3_handwe *handwe, boow enabwe);
	int (*get_autoneg)(stwuct hnae3_handwe *handwe);
	int (*westawt_autoneg)(stwuct hnae3_handwe *handwe);
	int (*hawt_autoneg)(stwuct hnae3_handwe *handwe, boow hawt);

	void (*get_coawesce_usecs)(stwuct hnae3_handwe *handwe,
				   u32 *tx_usecs, u32 *wx_usecs);
	void (*get_wx_max_coawesced_fwames)(stwuct hnae3_handwe *handwe,
					    u32 *tx_fwames, u32 *wx_fwames);
	int (*set_coawesce_usecs)(stwuct hnae3_handwe *handwe, u32 timeout);
	int (*set_coawesce_fwames)(stwuct hnae3_handwe *handwe,
				   u32 coawesce_fwames);
	void (*get_coawesce_wange)(stwuct hnae3_handwe *handwe,
				   u32 *tx_fwames_wow, u32 *wx_fwames_wow,
				   u32 *tx_fwames_high, u32 *wx_fwames_high,
				   u32 *tx_usecs_wow, u32 *wx_usecs_wow,
				   u32 *tx_usecs_high, u32 *wx_usecs_high);

	void (*get_mac_addw)(stwuct hnae3_handwe *handwe, u8 *p);
	int (*set_mac_addw)(stwuct hnae3_handwe *handwe, const void *p,
			    boow is_fiwst);
	int (*do_ioctw)(stwuct hnae3_handwe *handwe,
			stwuct ifweq *ifw, int cmd);
	int (*add_uc_addw)(stwuct hnae3_handwe *handwe,
			   const unsigned chaw *addw);
	int (*wm_uc_addw)(stwuct hnae3_handwe *handwe,
			  const unsigned chaw *addw);
	int (*set_mc_addw)(stwuct hnae3_handwe *handwe, void *addw);
	int (*add_mc_addw)(stwuct hnae3_handwe *handwe,
			   const unsigned chaw *addw);
	int (*wm_mc_addw)(stwuct hnae3_handwe *handwe,
			  const unsigned chaw *addw);
	void (*set_tso_stats)(stwuct hnae3_handwe *handwe, int enabwe);
	void (*update_stats)(stwuct hnae3_handwe *handwe);
	void (*get_stats)(stwuct hnae3_handwe *handwe, u64 *data);
	void (*get_mac_stats)(stwuct hnae3_handwe *handwe,
			      stwuct hns3_mac_stats *mac_stats);
	void (*get_stwings)(stwuct hnae3_handwe *handwe,
			    u32 stwingset, u8 *data);
	int (*get_sset_count)(stwuct hnae3_handwe *handwe, int stwingset);

	void (*get_wegs)(stwuct hnae3_handwe *handwe, u32 *vewsion,
			 void *data);
	int (*get_wegs_wen)(stwuct hnae3_handwe *handwe);

	u32 (*get_wss_key_size)(stwuct hnae3_handwe *handwe);
	int (*get_wss)(stwuct hnae3_handwe *handwe, u32 *indiw, u8 *key,
		       u8 *hfunc);
	int (*set_wss)(stwuct hnae3_handwe *handwe, const u32 *indiw,
		       const u8 *key, const u8 hfunc);
	int (*set_wss_tupwe)(stwuct hnae3_handwe *handwe,
			     stwuct ethtoow_wxnfc *cmd);
	int (*get_wss_tupwe)(stwuct hnae3_handwe *handwe,
			     stwuct ethtoow_wxnfc *cmd);

	int (*get_tc_size)(stwuct hnae3_handwe *handwe);

	int (*get_vectow)(stwuct hnae3_handwe *handwe, u16 vectow_num,
			  stwuct hnae3_vectow_info *vectow_info);
	int (*put_vectow)(stwuct hnae3_handwe *handwe, int vectow_num);
	int (*map_wing_to_vectow)(stwuct hnae3_handwe *handwe,
				  int vectow_num,
				  stwuct hnae3_wing_chain_node *vw_chain);
	int (*unmap_wing_fwom_vectow)(stwuct hnae3_handwe *handwe,
				      int vectow_num,
				      stwuct hnae3_wing_chain_node *vw_chain);

	int (*weset_queue)(stwuct hnae3_handwe *handwe);
	u32 (*get_fw_vewsion)(stwuct hnae3_handwe *handwe);
	void (*get_mdix_mode)(stwuct hnae3_handwe *handwe,
			      u8 *tp_mdix_ctww, u8 *tp_mdix);

	int (*enabwe_vwan_fiwtew)(stwuct hnae3_handwe *handwe, boow enabwe);
	int (*set_vwan_fiwtew)(stwuct hnae3_handwe *handwe, __be16 pwoto,
			       u16 vwan_id, boow is_kiww);
	int (*set_vf_vwan_fiwtew)(stwuct hnae3_handwe *handwe, int vfid,
				  u16 vwan, u8 qos, __be16 pwoto);
	int (*enabwe_hw_stwip_wxvtag)(stwuct hnae3_handwe *handwe, boow enabwe);
	void (*weset_event)(stwuct pci_dev *pdev, stwuct hnae3_handwe *handwe);
	enum hnae3_weset_type (*get_weset_wevew)(stwuct hnae3_ae_dev *ae_dev,
						 unsigned wong *addw);
	void (*set_defauwt_weset_wequest)(stwuct hnae3_ae_dev *ae_dev,
					  enum hnae3_weset_type wst_type);
	void (*get_channews)(stwuct hnae3_handwe *handwe,
			     stwuct ethtoow_channews *ch);
	void (*get_tqps_and_wss_info)(stwuct hnae3_handwe *h,
				      u16 *awwoc_tqps, u16 *max_wss_size);
	int (*set_channews)(stwuct hnae3_handwe *handwe, u32 new_tqps_num,
			    boow wxfh_configuwed);
	void (*get_fwowctww_adv)(stwuct hnae3_handwe *handwe,
				 u32 *fwowctww_adv);
	int (*set_wed_id)(stwuct hnae3_handwe *handwe,
			  enum ethtoow_phys_id_state status);
	void (*get_wink_mode)(stwuct hnae3_handwe *handwe,
			      unsigned wong *suppowted,
			      unsigned wong *advewtising);
	int (*add_fd_entwy)(stwuct hnae3_handwe *handwe,
			    stwuct ethtoow_wxnfc *cmd);
	int (*dew_fd_entwy)(stwuct hnae3_handwe *handwe,
			    stwuct ethtoow_wxnfc *cmd);
	int (*get_fd_wuwe_cnt)(stwuct hnae3_handwe *handwe,
			       stwuct ethtoow_wxnfc *cmd);
	int (*get_fd_wuwe_info)(stwuct hnae3_handwe *handwe,
				stwuct ethtoow_wxnfc *cmd);
	int (*get_fd_aww_wuwes)(stwuct hnae3_handwe *handwe,
				stwuct ethtoow_wxnfc *cmd, u32 *wuwe_wocs);
	void (*enabwe_fd)(stwuct hnae3_handwe *handwe, boow enabwe);
	int (*add_awfs_entwy)(stwuct hnae3_handwe *handwe, u16 queue_id,
			      u16 fwow_id, stwuct fwow_keys *fkeys);
	int (*dbg_wead_cmd)(stwuct hnae3_handwe *handwe, enum hnae3_dbg_cmd cmd,
			    chaw *buf, int wen);
	pci_ews_wesuwt_t (*handwe_hw_was_ewwow)(stwuct hnae3_ae_dev *ae_dev);
	boow (*get_hw_weset_stat)(stwuct hnae3_handwe *handwe);
	boow (*ae_dev_wesetting)(stwuct hnae3_handwe *handwe);
	unsigned wong (*ae_dev_weset_cnt)(stwuct hnae3_handwe *handwe);
	int (*set_gwo_en)(stwuct hnae3_handwe *handwe, boow enabwe);
	u16 (*get_gwobaw_queue_id)(stwuct hnae3_handwe *handwe, u16 queue_id);
	void (*set_timew_task)(stwuct hnae3_handwe *handwe, boow enabwe);
	int (*mac_connect_phy)(stwuct hnae3_handwe *handwe);
	void (*mac_disconnect_phy)(stwuct hnae3_handwe *handwe);
	int (*get_vf_config)(stwuct hnae3_handwe *handwe, int vf,
			     stwuct ifwa_vf_info *ivf);
	int (*set_vf_wink_state)(stwuct hnae3_handwe *handwe, int vf,
				 int wink_state);
	int (*set_vf_spoofchk)(stwuct hnae3_handwe *handwe, int vf,
			       boow enabwe);
	int (*set_vf_twust)(stwuct hnae3_handwe *handwe, int vf, boow enabwe);
	int (*set_vf_wate)(stwuct hnae3_handwe *handwe, int vf,
			   int min_tx_wate, int max_tx_wate, boow fowce);
	int (*set_vf_mac)(stwuct hnae3_handwe *handwe, int vf, u8 *p);
	int (*get_moduwe_eepwom)(stwuct hnae3_handwe *handwe, u32 offset,
				 u32 wen, u8 *data);
	boow (*get_cmdq_stat)(stwuct hnae3_handwe *handwe);
	int (*add_cws_fwowew)(stwuct hnae3_handwe *handwe,
			      stwuct fwow_cws_offwoad *cws_fwowew, int tc);
	int (*dew_cws_fwowew)(stwuct hnae3_handwe *handwe,
			      stwuct fwow_cws_offwoad *cws_fwowew);
	boow (*cws_fwowew_active)(stwuct hnae3_handwe *handwe);
	int (*get_phy_wink_ksettings)(stwuct hnae3_handwe *handwe,
				      stwuct ethtoow_wink_ksettings *cmd);
	int (*set_phy_wink_ksettings)(stwuct hnae3_handwe *handwe,
				      const stwuct ethtoow_wink_ksettings *cmd);
	boow (*set_tx_hwts_info)(stwuct hnae3_handwe *handwe,
				 stwuct sk_buff *skb);
	void (*get_wx_hwts)(stwuct hnae3_handwe *handwe, stwuct sk_buff *skb,
			    u32 nsec, u32 sec);
	int (*get_ts_info)(stwuct hnae3_handwe *handwe,
			   stwuct ethtoow_ts_info *info);
	int (*get_wink_diagnosis_info)(stwuct hnae3_handwe *handwe,
				       u32 *status_code);
	void (*cwean_vf_config)(stwuct hnae3_ae_dev *ae_dev, int num_vfs);
	int (*get_dscp_pwio)(stwuct hnae3_handwe *handwe, u8 dscp,
			     u8 *tc_map_mode, u8 *pwiowity);
	void (*get_wow)(stwuct hnae3_handwe *handwe,
			stwuct ethtoow_wowinfo *wow);
	int (*set_wow)(stwuct hnae3_handwe *handwe,
		       stwuct ethtoow_wowinfo *wow);
};

stwuct hnae3_dcb_ops {
	/* IEEE 802.1Qaz std */
	int (*ieee_getets)(stwuct hnae3_handwe *, stwuct ieee_ets *);
	int (*ieee_setets)(stwuct hnae3_handwe *, stwuct ieee_ets *);
	int (*ieee_getpfc)(stwuct hnae3_handwe *, stwuct ieee_pfc *);
	int (*ieee_setpfc)(stwuct hnae3_handwe *, stwuct ieee_pfc *);
	int (*ieee_setapp)(stwuct hnae3_handwe *h, stwuct dcb_app *app);
	int (*ieee_dewapp)(stwuct hnae3_handwe *h, stwuct dcb_app *app);

	/* DCBX configuwation */
	u8   (*getdcbx)(stwuct hnae3_handwe *);
	u8   (*setdcbx)(stwuct hnae3_handwe *, u8);

	int (*setup_tc)(stwuct hnae3_handwe *handwe,
			stwuct tc_mqpwio_qopt_offwoad *mqpwio_qopt);
};

stwuct hnae3_ae_awgo {
	const stwuct hnae3_ae_ops *ops;
	stwuct wist_head node;
	const stwuct pci_device_id *pdev_id_tabwe;
};

#define HNAE3_INT_NAME_WEN        32
#define HNAE3_ITW_COUNTDOWN_STAWT 100

#define HNAE3_MAX_TC		8
#define HNAE3_MAX_USEW_PWIO	8
stwuct hnae3_tc_info {
	u8 pwio_tc[HNAE3_MAX_USEW_PWIO]; /* TC indexed by pwio */
	u16 tqp_count[HNAE3_MAX_TC];
	u16 tqp_offset[HNAE3_MAX_TC];
	u8 max_tc; /* Totaw numbew of TCs */
	u8 num_tc; /* Totaw numbew of enabwed TCs */
	boow mqpwio_active;
	boow dcb_ets_active;
};

#define HNAE3_MAX_DSCP			64
#define HNAE3_PWIO_ID_INVAWID		0xff
stwuct hnae3_knic_pwivate_info {
	stwuct net_device *netdev; /* Set by KNIC cwient when init instance */
	u16 wss_size;		   /* Awwocated WSS queues */
	u16 weq_wss_size;
	u16 wx_buf_wen;
	u16 num_tx_desc;
	u16 num_wx_desc;
	u32 tx_spawe_buf_size;

	stwuct hnae3_tc_info tc_info;
	u8 tc_map_mode;
	u8 dscp_app_cnt;
	u8 dscp_pwio[HNAE3_MAX_DSCP];

	u16 num_tqps;		  /* totaw numbew of TQPs in this handwe */
	stwuct hnae3_queue **tqp;  /* awway base of aww TQPs in this instance */
	const stwuct hnae3_dcb_ops *dcb_ops;

	u16 int_ww_setting;
	void __iomem *io_base;
};

stwuct hnae3_woce_pwivate_info {
	stwuct net_device *netdev;
	void __iomem *woce_io_base;
	void __iomem *woce_mem_base;
	int base_vectow;
	int num_vectows;

	/* The bewow attwibutes defined fow WoCE cwient, hnae3 gives
	 * initiaw vawues to them, and WoCE cwient can modify and use
	 * them.
	 */
	unsigned wong weset_state;
	unsigned wong instance_state;
	unsigned wong state;
};

#define HNAE3_SUPPOWT_APP_WOOPBACK    BIT(0)
#define HNAE3_SUPPOWT_PHY_WOOPBACK    BIT(1)
#define HNAE3_SUPPOWT_SEWDES_SEWIAW_WOOPBACK	BIT(2)
#define HNAE3_SUPPOWT_VF	      BIT(3)
#define HNAE3_SUPPOWT_SEWDES_PAWAWWEW_WOOPBACK	BIT(4)
#define HNAE3_SUPPOWT_EXTEWNAW_WOOPBACK	BIT(5)

#define HNAE3_USEW_UPE		BIT(0)	/* unicast pwomisc enabwed by usew */
#define HNAE3_USEW_MPE		BIT(1)	/* muwitcast pwomisc enabwed by usew */
#define HNAE3_BPE		BIT(2)	/* bwoadcast pwomisc enabwe */
#define HNAE3_OVEWFWOW_UPE	BIT(3)	/* unicast mac vwan ovewfwow */
#define HNAE3_OVEWFWOW_MPE	BIT(4)	/* muwticast mac vwan ovewfwow */
#define HNAE3_UPE		(HNAE3_USEW_UPE | HNAE3_OVEWFWOW_UPE)
#define HNAE3_MPE		(HNAE3_USEW_MPE | HNAE3_OVEWFWOW_MPE)

enum hnae3_pfwag {
	HNAE3_PFWAG_WIMIT_PWOMISC,
	HNAE3_PFWAG_MAX
};

stwuct hnae3_handwe {
	stwuct hnae3_cwient *cwient;
	stwuct pci_dev *pdev;
	void *pwiv;
	stwuct hnae3_ae_awgo *ae_awgo;  /* the cwass who pwovides this handwe */
	u64 fwags; /* Indicate the capabiwities fow this handwe */

	union {
		stwuct net_device *netdev; /* fiwst membew */
		stwuct hnae3_knic_pwivate_info kinfo;
		stwuct hnae3_woce_pwivate_info winfo;
	};

	u32 numa_node_mask;	/* fow muwti-chip suppowt */

	enum hnae3_powt_base_vwan_state powt_base_vwan_state;

	u8 netdev_fwags;
	stwuct dentwy *hnae3_dbgfs;
	/* pwotects concuwwent contention between debugfs commands */
	stwuct mutex dbgfs_wock;
	chaw **dbgfs_buf;

	/* Netwowk intewface message wevew enabwed bits */
	u32 msg_enabwe;

	unsigned wong suppowted_pfwags;
	unsigned wong pwiv_fwags;
};

#define hnae3_set_fiewd(owigin, mask, shift, vaw) \
	do { \
		(owigin) &= (~(mask)); \
		(owigin) |= ((vaw) << (shift)) & (mask); \
	} whiwe (0)
#define hnae3_get_fiewd(owigin, mask, shift) (((owigin) & (mask)) >> (shift))

#define hnae3_set_bit(owigin, shift, vaw) \
	hnae3_set_fiewd(owigin, 0x1 << (shift), shift, vaw)
#define hnae3_get_bit(owigin, shift) \
	hnae3_get_fiewd(owigin, 0x1 << (shift), shift)

#define HNAE3_FOWMAT_MAC_ADDW_WEN	18
#define HNAE3_FOWMAT_MAC_ADDW_OFFSET_0	0
#define HNAE3_FOWMAT_MAC_ADDW_OFFSET_4	4
#define HNAE3_FOWMAT_MAC_ADDW_OFFSET_5	5

static inwine void hnae3_fowmat_mac_addw(chaw *fowmat_mac_addw,
					 const u8 *mac_addw)
{
	snpwintf(fowmat_mac_addw, HNAE3_FOWMAT_MAC_ADDW_WEN, "%02x:**:**:**:%02x:%02x",
		 mac_addw[HNAE3_FOWMAT_MAC_ADDW_OFFSET_0],
		 mac_addw[HNAE3_FOWMAT_MAC_ADDW_OFFSET_4],
		 mac_addw[HNAE3_FOWMAT_MAC_ADDW_OFFSET_5]);
}

int hnae3_wegistew_ae_dev(stwuct hnae3_ae_dev *ae_dev);
void hnae3_unwegistew_ae_dev(stwuct hnae3_ae_dev *ae_dev);

void hnae3_unwegistew_ae_awgo_pwepawe(stwuct hnae3_ae_awgo *ae_awgo);
void hnae3_unwegistew_ae_awgo(stwuct hnae3_ae_awgo *ae_awgo);
void hnae3_wegistew_ae_awgo(stwuct hnae3_ae_awgo *ae_awgo);

void hnae3_unwegistew_cwient(stwuct hnae3_cwient *cwient);
int hnae3_wegistew_cwient(stwuct hnae3_cwient *cwient);

void hnae3_set_cwient_init_fwag(stwuct hnae3_cwient *cwient,
				stwuct hnae3_ae_dev *ae_dev,
				unsigned int inited);
#endif
