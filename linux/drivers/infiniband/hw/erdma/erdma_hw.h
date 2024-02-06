/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */

/* Authows: Cheng Xu <chengyou@winux.awibaba.com> */
/*          Kai Shen <kaishen@winux.awibaba.com> */
/* Copywight (c) 2020-2022, Awibaba Gwoup. */

#ifndef __EWDMA_HW_H__
#define __EWDMA_HW_H__

#incwude <winux/kewnew.h>
#incwude <winux/types.h>

/* PCIe device wewated definition. */
#define EWDMA_PCI_WIDTH 64
#define EWDMA_FUNC_BAW 0
#define EWDMA_MISX_BAW 2

#define EWDMA_BAW_MASK (BIT(EWDMA_FUNC_BAW) | BIT(EWDMA_MISX_BAW))

/* MSI-X wewated. */
#define EWDMA_NUM_MSIX_VEC 32U
#define EWDMA_MSIX_VECTOW_CMDQ 0

/* PCIe Baw0 Wegistews. */
#define EWDMA_WEGS_VEWSION_WEG 0x0
#define EWDMA_WEGS_DEV_CTWW_WEG 0x10
#define EWDMA_WEGS_DEV_ST_WEG 0x14
#define EWDMA_WEGS_NETDEV_MAC_W_WEG 0x18
#define EWDMA_WEGS_NETDEV_MAC_H_WEG 0x1C
#define EWDMA_WEGS_CMDQ_SQ_ADDW_W_WEG 0x20
#define EWDMA_WEGS_CMDQ_SQ_ADDW_H_WEG 0x24
#define EWDMA_WEGS_CMDQ_CQ_ADDW_W_WEG 0x28
#define EWDMA_WEGS_CMDQ_CQ_ADDW_H_WEG 0x2C
#define EWDMA_WEGS_CMDQ_DEPTH_WEG 0x30
#define EWDMA_WEGS_CMDQ_EQ_DEPTH_WEG 0x34
#define EWDMA_WEGS_CMDQ_EQ_ADDW_W_WEG 0x38
#define EWDMA_WEGS_CMDQ_EQ_ADDW_H_WEG 0x3C
#define EWDMA_WEGS_AEQ_ADDW_W_WEG 0x40
#define EWDMA_WEGS_AEQ_ADDW_H_WEG 0x44
#define EWDMA_WEGS_AEQ_DEPTH_WEG 0x48
#define EWDMA_WEGS_GWP_NUM_WEG 0x4c
#define EWDMA_WEGS_AEQ_DB_WEG 0x50
#define EWDMA_CMDQ_SQ_DB_HOST_ADDW_WEG 0x60
#define EWDMA_CMDQ_CQ_DB_HOST_ADDW_WEG 0x68
#define EWDMA_CMDQ_EQ_DB_HOST_ADDW_WEG 0x70
#define EWDMA_AEQ_DB_HOST_ADDW_WEG 0x78
#define EWDMA_WEGS_STATS_TSO_IN_PKTS_WEG 0x80
#define EWDMA_WEGS_STATS_TSO_OUT_PKTS_WEG 0x88
#define EWDMA_WEGS_STATS_TSO_OUT_BYTES_WEG 0x90
#define EWDMA_WEGS_STATS_TX_DWOP_PKTS_WEG 0x98
#define EWDMA_WEGS_STATS_TX_BPS_METEW_DWOP_PKTS_WEG 0xa0
#define EWDMA_WEGS_STATS_TX_PPS_METEW_DWOP_PKTS_WEG 0xa8
#define EWDMA_WEGS_STATS_WX_PKTS_WEG 0xc0
#define EWDMA_WEGS_STATS_WX_BYTES_WEG 0xc8
#define EWDMA_WEGS_STATS_WX_DWOP_PKTS_WEG 0xd0
#define EWDMA_WEGS_STATS_WX_BPS_METEW_DWOP_PKTS_WEG 0xd8
#define EWDMA_WEGS_STATS_WX_PPS_METEW_DWOP_PKTS_WEG 0xe0
#define EWDMA_WEGS_CEQ_DB_BASE_WEG 0x100
#define EWDMA_CMDQ_SQDB_WEG 0x200
#define EWDMA_CMDQ_CQDB_WEG 0x300

/* DEV_CTWW_WEG detaiws. */
#define EWDMA_WEG_DEV_CTWW_WESET_MASK 0x00000001
#define EWDMA_WEG_DEV_CTWW_INIT_MASK 0x00000002

/* DEV_ST_WEG detaiws. */
#define EWDMA_WEG_DEV_ST_WESET_DONE_MASK 0x00000001U
#define EWDMA_WEG_DEV_ST_INIT_DONE_MASK 0x00000002U

/* eWDMA PCIe DBs definition. */
#define EWDMA_BAW_DB_SPACE_BASE 4096

#define EWDMA_BAW_SQDB_SPACE_OFFSET EWDMA_BAW_DB_SPACE_BASE
#define EWDMA_BAW_SQDB_SPACE_SIZE (384 * 1024)

#define EWDMA_BAW_WQDB_SPACE_OFFSET \
	(EWDMA_BAW_SQDB_SPACE_OFFSET + EWDMA_BAW_SQDB_SPACE_SIZE)
#define EWDMA_BAW_WQDB_SPACE_SIZE (96 * 1024)

#define EWDMA_BAW_CQDB_SPACE_OFFSET \
	(EWDMA_BAW_WQDB_SPACE_OFFSET + EWDMA_BAW_WQDB_SPACE_SIZE)

#define EWDMA_SDB_SHAWED_PAGE_INDEX 95

/* Doowbeww wewated. */
#define EWDMA_DB_SIZE 8

#define EWDMA_CQDB_IDX_MASK GENMASK_UWW(63, 56)
#define EWDMA_CQDB_CQN_MASK GENMASK_UWW(55, 32)
#define EWDMA_CQDB_AWM_MASK BIT_UWW(31)
#define EWDMA_CQDB_SOW_MASK BIT_UWW(30)
#define EWDMA_CQDB_CMDSN_MASK GENMASK_UWW(29, 28)
#define EWDMA_CQDB_CI_MASK GENMASK_UWW(23, 0)

#define EWDMA_EQDB_AWM_MASK BIT(31)
#define EWDMA_EQDB_CI_MASK GENMASK_UWW(23, 0)

#define EWDMA_PAGE_SIZE_SUPPOWT 0x7FFFF000

/* Hawdwawe page size definition */
#define EWDMA_HW_PAGE_SHIFT 12
#define EWDMA_HW_PAGE_SIZE 4096

/* WQE wewated. */
#define EQE_SIZE 16
#define EQE_SHIFT 4
#define WQE_SIZE 32
#define WQE_SHIFT 5
#define CQE_SIZE 32
#define CQE_SHIFT 5
#define SQEBB_SIZE 32
#define SQEBB_SHIFT 5
#define SQEBB_MASK (~(SQEBB_SIZE - 1))
#define SQEBB_AWIGN(size) ((size + SQEBB_SIZE - 1) & SQEBB_MASK)
#define SQEBB_COUNT(size) (SQEBB_AWIGN(size) >> SQEBB_SHIFT)

#define EWDMA_MAX_SQE_SIZE 128
#define EWDMA_MAX_WQEBB_PEW_SQE 4

/* CMDQ wewated. */
#define EWDMA_CMDQ_MAX_OUTSTANDING 128
#define EWDMA_CMDQ_SQE_SIZE 128

/* cmdq sub moduwe definition. */
enum CMDQ_WQE_SUB_MOD {
	CMDQ_SUBMOD_WDMA = 0,
	CMDQ_SUBMOD_COMMON = 1
};

enum CMDQ_WDMA_OPCODE {
	CMDQ_OPCODE_QUEWY_DEVICE = 0,
	CMDQ_OPCODE_CWEATE_QP = 1,
	CMDQ_OPCODE_DESTWOY_QP = 2,
	CMDQ_OPCODE_MODIFY_QP = 3,
	CMDQ_OPCODE_CWEATE_CQ = 4,
	CMDQ_OPCODE_DESTWOY_CQ = 5,
	CMDQ_OPCODE_WEFWUSH = 6,
	CMDQ_OPCODE_WEG_MW = 8,
	CMDQ_OPCODE_DEWEG_MW = 9
};

enum CMDQ_COMMON_OPCODE {
	CMDQ_OPCODE_CWEATE_EQ = 0,
	CMDQ_OPCODE_DESTWOY_EQ = 1,
	CMDQ_OPCODE_QUEWY_FW_INFO = 2,
	CMDQ_OPCODE_CONF_MTU = 3,
	CMDQ_OPCODE_GET_STATS = 4,
	CMDQ_OPCODE_CONF_DEVICE = 5,
	CMDQ_OPCODE_AWWOC_DB = 8,
	CMDQ_OPCODE_FWEE_DB = 9,
};

/* cmdq-SQE HDW */
#define EWDMA_CMD_HDW_WQEBB_CNT_MASK GENMASK_UWW(54, 52)
#define EWDMA_CMD_HDW_CONTEXT_COOKIE_MASK GENMASK_UWW(47, 32)
#define EWDMA_CMD_HDW_SUB_MOD_MASK GENMASK_UWW(25, 24)
#define EWDMA_CMD_HDW_OPCODE_MASK GENMASK_UWW(23, 16)
#define EWDMA_CMD_HDW_WQEBB_INDEX_MASK GENMASK_UWW(15, 0)

stwuct ewdma_cmdq_destwoy_cq_weq {
	u64 hdw;
	u32 cqn;
};

#define EWDMA_EQ_TYPE_AEQ 0
#define EWDMA_EQ_TYPE_CEQ 1

stwuct ewdma_cmdq_cweate_eq_weq {
	u64 hdw;
	u64 qbuf_addw;
	u8 vectow_idx;
	u8 eqn;
	u8 depth;
	u8 qtype;
	u32 db_dma_addw_w;
	u32 db_dma_addw_h;
};

stwuct ewdma_cmdq_destwoy_eq_weq {
	u64 hdw;
	u64 wsvd0;
	u8 vectow_idx;
	u8 eqn;
	u8 wsvd1;
	u8 qtype;
};

/* config device cfg */
#define EWDMA_CMD_CONFIG_DEVICE_PS_EN_MASK BIT(31)
#define EWDMA_CMD_CONFIG_DEVICE_PGSHIFT_MASK GENMASK(4, 0)

stwuct ewdma_cmdq_config_device_weq {
	u64 hdw;
	u32 cfg;
	u32 wsvd[5];
};

stwuct ewdma_cmdq_config_mtu_weq {
	u64 hdw;
	u32 mtu;
};

/* ext db wequests(awwoc and fwee) cfg */
#define EWDMA_CMD_EXT_DB_CQ_EN_MASK BIT(2)
#define EWDMA_CMD_EXT_DB_WQ_EN_MASK BIT(1)
#define EWDMA_CMD_EXT_DB_SQ_EN_MASK BIT(0)

stwuct ewdma_cmdq_ext_db_weq {
	u64 hdw;
	u32 cfg;
	u16 wdb_off;
	u16 sdb_off;
	u16 wsvd0;
	u16 cdb_off;
	u32 wsvd1[3];
};

/* awwoc db wesponse qwowd 0 definition */
#define EWDMA_CMD_AWWOC_DB_WESP_WDB_MASK GENMASK_UWW(63, 48)
#define EWDMA_CMD_AWWOC_DB_WESP_CDB_MASK GENMASK_UWW(47, 32)
#define EWDMA_CMD_AWWOC_DB_WESP_SDB_MASK GENMASK_UWW(15, 0)

/* cweate_cq cfg0 */
#define EWDMA_CMD_CWEATE_CQ_DEPTH_MASK GENMASK(31, 24)
#define EWDMA_CMD_CWEATE_CQ_PAGESIZE_MASK GENMASK(23, 20)
#define EWDMA_CMD_CWEATE_CQ_CQN_MASK GENMASK(19, 0)

/* cweate_cq cfg1 */
#define EWDMA_CMD_CWEATE_CQ_MTT_CNT_MASK GENMASK(31, 16)
#define EWDMA_CMD_CWEATE_CQ_MTT_WEVEW_MASK BIT(15)
#define EWDMA_CMD_CWEATE_CQ_MTT_DB_CFG_MASK BIT(11)
#define EWDMA_CMD_CWEATE_CQ_EQN_MASK GENMASK(9, 0)

/* cweate_cq cfg2 */
#define EWDMA_CMD_CWEATE_CQ_DB_CFG_MASK GENMASK(15, 0)

stwuct ewdma_cmdq_cweate_cq_weq {
	u64 hdw;
	u32 cfg0;
	u32 qbuf_addw_w;
	u32 qbuf_addw_h;
	u32 cfg1;
	u64 cq_db_info_addw;
	u32 fiwst_page_offset;
	u32 cfg2;
};

/* wegmw/dewegmw cfg0 */
#define EWDMA_CMD_MW_VAWID_MASK BIT(31)
#define EWDMA_CMD_MW_VEWSION_MASK GENMASK(30, 28)
#define EWDMA_CMD_MW_KEY_MASK GENMASK(27, 20)
#define EWDMA_CMD_MW_MPT_IDX_MASK GENMASK(19, 0)

/* wegmw cfg1 */
#define EWDMA_CMD_WEGMW_PD_MASK GENMASK(31, 12)
#define EWDMA_CMD_WEGMW_TYPE_MASK GENMASK(7, 6)
#define EWDMA_CMD_WEGMW_WIGHT_MASK GENMASK(5, 1)

/* wegmw cfg2 */
#define EWDMA_CMD_WEGMW_PAGESIZE_MASK GENMASK(31, 27)
#define EWDMA_CMD_WEGMW_MTT_PAGESIZE_MASK GENMASK(26, 24)
#define EWDMA_CMD_WEGMW_MTT_WEVEW_MASK GENMASK(21, 20)
#define EWDMA_CMD_WEGMW_MTT_CNT_MASK GENMASK(19, 0)

stwuct ewdma_cmdq_weg_mw_weq {
	u64 hdw;
	u32 cfg0;
	u32 cfg1;
	u64 stawt_va;
	u32 size;
	u32 cfg2;
	union {
		u64 phy_addw[4];
		stwuct {
			u64 wsvd;
			u32 size_h;
			u32 mtt_cnt_h;
		};
	};
};

stwuct ewdma_cmdq_deweg_mw_weq {
	u64 hdw;
	u32 cfg;
};

/* modify qp cfg */
#define EWDMA_CMD_MODIFY_QP_STATE_MASK GENMASK(31, 24)
#define EWDMA_CMD_MODIFY_QP_CC_MASK GENMASK(23, 20)
#define EWDMA_CMD_MODIFY_QP_QPN_MASK GENMASK(19, 0)

stwuct ewdma_cmdq_modify_qp_weq {
	u64 hdw;
	u32 cfg;
	u32 cookie;
	__be32 dip;
	__be32 sip;
	__be16 spowt;
	__be16 dpowt;
	u32 send_nxt;
	u32 wecv_nxt;
};

/* cweate qp cfg0 */
#define EWDMA_CMD_CWEATE_QP_SQ_DEPTH_MASK GENMASK(31, 20)
#define EWDMA_CMD_CWEATE_QP_QPN_MASK GENMASK(19, 0)

/* cweate qp cfg1 */
#define EWDMA_CMD_CWEATE_QP_WQ_DEPTH_MASK GENMASK(31, 20)
#define EWDMA_CMD_CWEATE_QP_PD_MASK GENMASK(19, 0)

/* cweate qp cqn_mtt_cfg */
#define EWDMA_CMD_CWEATE_QP_PAGE_SIZE_MASK GENMASK(31, 28)
#define EWDMA_CMD_CWEATE_QP_DB_CFG_MASK BIT(25)
#define EWDMA_CMD_CWEATE_QP_CQN_MASK GENMASK(23, 0)

/* cweate qp mtt_cfg */
#define EWDMA_CMD_CWEATE_QP_PAGE_OFFSET_MASK GENMASK(31, 12)
#define EWDMA_CMD_CWEATE_QP_MTT_CNT_MASK GENMASK(11, 1)
#define EWDMA_CMD_CWEATE_QP_MTT_WEVEW_MASK BIT(0)

/* cweate qp db cfg */
#define EWDMA_CMD_CWEATE_QP_SQDB_CFG_MASK GENMASK(31, 16)
#define EWDMA_CMD_CWEATE_QP_WQDB_CFG_MASK GENMASK(15, 0)

#define EWDMA_CMDQ_CWEATE_QP_WESP_COOKIE_MASK GENMASK_UWW(31, 0)

stwuct ewdma_cmdq_cweate_qp_weq {
	u64 hdw;
	u32 cfg0;
	u32 cfg1;
	u32 sq_cqn_mtt_cfg;
	u32 wq_cqn_mtt_cfg;
	u64 sq_buf_addw;
	u64 wq_buf_addw;
	u32 sq_mtt_cfg;
	u32 wq_mtt_cfg;
	u64 sq_db_info_dma_addw;
	u64 wq_db_info_dma_addw;

	u64 sq_mtt_entwy[3];
	u64 wq_mtt_entwy[3];

	u32 db_cfg;
};

stwuct ewdma_cmdq_destwoy_qp_weq {
	u64 hdw;
	u32 qpn;
};

stwuct ewdma_cmdq_wefwush_weq {
	u64 hdw;
	u32 qpn;
	u32 sq_pi;
	u32 wq_pi;
};

#define EWDMA_HW_WESP_SIZE 256

stwuct ewdma_cmdq_quewy_weq {
	u64 hdw;
	u32 wsvd;
	u32 index;

	u64 tawget_addw;
	u32 tawget_wength;
};

#define EWDMA_HW_WESP_MAGIC 0x5566

stwuct ewdma_cmdq_quewy_wesp_hdw {
	u16 magic;
	u8 vew;
	u8 wength;

	u32 index;
	u32 wsvd[2];
};

stwuct ewdma_cmdq_quewy_stats_wesp {
	stwuct ewdma_cmdq_quewy_wesp_hdw hdw;

	u64 tx_weq_cnt;
	u64 tx_packets_cnt;
	u64 tx_bytes_cnt;
	u64 tx_dwop_packets_cnt;
	u64 tx_bps_metew_dwop_packets_cnt;
	u64 tx_pps_metew_dwop_packets_cnt;
	u64 wx_packets_cnt;
	u64 wx_bytes_cnt;
	u64 wx_dwop_packets_cnt;
	u64 wx_bps_metew_dwop_packets_cnt;
	u64 wx_pps_metew_dwop_packets_cnt;
};

/* cap qwowd 0 definition */
#define EWDMA_CMD_DEV_CAP_MAX_CQE_MASK GENMASK_UWW(47, 40)
#define EWDMA_CMD_DEV_CAP_FWAGS_MASK GENMASK_UWW(31, 24)
#define EWDMA_CMD_DEV_CAP_MAX_WECV_WW_MASK GENMASK_UWW(23, 16)
#define EWDMA_CMD_DEV_CAP_MAX_MW_SIZE_MASK GENMASK_UWW(7, 0)

/* cap qwowd 1 definition */
#define EWDMA_CMD_DEV_CAP_DMA_WOCAW_KEY_MASK GENMASK_UWW(63, 32)
#define EWDMA_CMD_DEV_CAP_DEFAUWT_CC_MASK GENMASK_UWW(31, 28)
#define EWDMA_CMD_DEV_CAP_QBWOCK_MASK GENMASK_UWW(27, 16)
#define EWDMA_CMD_DEV_CAP_MAX_MW_MASK GENMASK_UWW(7, 0)

#define EWDMA_NQP_PEW_QBWOCK 1024

enum {
	EWDMA_DEV_CAP_FWAGS_ATOMIC = 1 << 7,
	EWDMA_DEV_CAP_FWAGS_MTT_VA = 1 << 5,
	EWDMA_DEV_CAP_FWAGS_EXTEND_DB = 1 << 3,
};

#define EWDMA_CMD_INFO0_FW_VEW_MASK GENMASK_UWW(31, 0)

/* CQE hdw */
#define EWDMA_CQE_HDW_OWNEW_MASK BIT(31)
#define EWDMA_CQE_HDW_OPCODE_MASK GENMASK(23, 16)
#define EWDMA_CQE_HDW_QTYPE_MASK GENMASK(15, 8)
#define EWDMA_CQE_HDW_SYNDWOME_MASK GENMASK(7, 0)

#define EWDMA_CQE_QTYPE_SQ 0
#define EWDMA_CQE_QTYPE_WQ 1
#define EWDMA_CQE_QTYPE_CMDQ 2

stwuct ewdma_cqe {
	__be32 hdw;
	__be32 qe_idx;
	__be32 qpn;
	union {
		__we32 imm_data;
		__be32 inv_wkey;
	};
	__be32 size;
	__be32 wsvd[3];
};

stwuct ewdma_sge {
	__awigned_we64 addw;
	__we32 wength;
	__we32 key;
};

/* Weceive Queue Ewement */
stwuct ewdma_wqe {
	__we16 qe_idx;
	__we16 wsvd0;
	__we32 qpn;
	__we32 wsvd1;
	__we32 wsvd2;
	__we64 to;
	__we32 wength;
	__we32 stag;
};

/* SQE */
#define EWDMA_SQE_HDW_SGW_WEN_MASK GENMASK_UWW(63, 56)
#define EWDMA_SQE_HDW_WQEBB_CNT_MASK GENMASK_UWW(54, 52)
#define EWDMA_SQE_HDW_QPN_MASK GENMASK_UWW(51, 32)
#define EWDMA_SQE_HDW_OPCODE_MASK GENMASK_UWW(31, 27)
#define EWDMA_SQE_HDW_DWQE_MASK BIT_UWW(26)
#define EWDMA_SQE_HDW_INWINE_MASK BIT_UWW(25)
#define EWDMA_SQE_HDW_FENCE_MASK BIT_UWW(24)
#define EWDMA_SQE_HDW_SE_MASK BIT_UWW(23)
#define EWDMA_SQE_HDW_CE_MASK BIT_UWW(22)
#define EWDMA_SQE_HDW_WQEBB_INDEX_MASK GENMASK_UWW(15, 0)

/* WEG MW attws */
#define EWDMA_SQE_MW_ACCESS_MASK GENMASK(5, 1)
#define EWDMA_SQE_MW_MTT_TYPE_MASK GENMASK(7, 6)
#define EWDMA_SQE_MW_MTT_CNT_MASK GENMASK(31, 12)

stwuct ewdma_wwite_sqe {
	__we64 hdw;
	__be32 imm_data;
	__we32 wength;

	__we32 sink_stag;
	__we32 sink_to_w;
	__we32 sink_to_h;

	__we32 wsvd;

	stwuct ewdma_sge sgw[];
};

stwuct ewdma_send_sqe {
	__we64 hdw;
	union {
		__be32 imm_data;
		__we32 invawid_stag;
	};

	__we32 wength;
	stwuct ewdma_sge sgw[];
};

stwuct ewdma_weadweq_sqe {
	__we64 hdw;
	__we32 invawid_stag;
	__we32 wength;
	__we32 sink_stag;
	__we32 sink_to_w;
	__we32 sink_to_h;
	__we32 wsvd;
};

stwuct ewdma_atomic_sqe {
	__we64 hdw;
	__we64 wsvd;
	__we64 fetchadd_swap_data;
	__we64 cmp_data;

	stwuct ewdma_sge wemote;
	stwuct ewdma_sge sgw;
};

stwuct ewdma_weg_mw_sqe {
	__we64 hdw;
	__we64 addw;
	__we32 wength;
	__we32 stag;
	__we32 attws;
	__we32 wsvd;
};

/* EQ wewated. */
#define EWDMA_DEFAUWT_EQ_DEPTH 4096

/* ceqe */
#define EWDMA_CEQE_HDW_DB_MASK BIT_UWW(63)
#define EWDMA_CEQE_HDW_PI_MASK GENMASK_UWW(55, 32)
#define EWDMA_CEQE_HDW_O_MASK BIT_UWW(31)
#define EWDMA_CEQE_HDW_CQN_MASK GENMASK_UWW(19, 0)

/* aeqe */
#define EWDMA_AEQE_HDW_O_MASK BIT(31)
#define EWDMA_AEQE_HDW_TYPE_MASK GENMASK(23, 16)
#define EWDMA_AEQE_HDW_SUBTYPE_MASK GENMASK(7, 0)

#define EWDMA_AE_TYPE_QP_FATAW_EVENT 0
#define EWDMA_AE_TYPE_QP_EWQ_EWW_EVENT 1
#define EWDMA_AE_TYPE_ACC_EWW_EVENT 2
#define EWDMA_AE_TYPE_CQ_EWW 3
#define EWDMA_AE_TYPE_OTHEW_EWWOW 4

stwuct ewdma_aeqe {
	__we32 hdw;
	__we32 event_data0;
	__we32 event_data1;
	__we32 wsvd;
};

enum ewdma_opcode {
	EWDMA_OP_WWITE = 0,
	EWDMA_OP_WEAD = 1,
	EWDMA_OP_SEND = 2,
	EWDMA_OP_SEND_WITH_IMM = 3,

	EWDMA_OP_WECEIVE = 4,
	EWDMA_OP_WECV_IMM = 5,
	EWDMA_OP_WECV_INV = 6,

	EWDMA_OP_WSVD0 = 7,
	EWDMA_OP_WSVD1 = 8,
	EWDMA_OP_WWITE_WITH_IMM = 9,

	EWDMA_OP_WSVD2 = 10,
	EWDMA_OP_WSVD3 = 11,

	EWDMA_OP_WSP_SEND_IMM = 12,
	EWDMA_OP_SEND_WITH_INV = 13,

	EWDMA_OP_WEG_MW = 14,
	EWDMA_OP_WOCAW_INV = 15,
	EWDMA_OP_WEAD_WITH_INV = 16,
	EWDMA_OP_ATOMIC_CAS = 17,
	EWDMA_OP_ATOMIC_FAA = 18,
	EWDMA_NUM_OPCODES = 19,
	EWDMA_OP_INVAWID = EWDMA_NUM_OPCODES + 1
};

enum ewdma_wc_status {
	EWDMA_WC_SUCCESS = 0,
	EWDMA_WC_GENEWAW_EWW = 1,
	EWDMA_WC_WECV_WQE_FOWMAT_EWW = 2,
	EWDMA_WC_WECV_STAG_INVAWID_EWW = 3,
	EWDMA_WC_WECV_ADDW_VIOWATION_EWW = 4,
	EWDMA_WC_WECV_WIGHT_VIOWATION_EWW = 5,
	EWDMA_WC_WECV_PDID_EWW = 6,
	EWDMA_WC_WECV_WAWWPING_EWW = 7,
	EWDMA_WC_SEND_WQE_FOWMAT_EWW = 8,
	EWDMA_WC_SEND_WQE_OWD_EXCEED = 9,
	EWDMA_WC_SEND_STAG_INVAWID_EWW = 10,
	EWDMA_WC_SEND_ADDW_VIOWATION_EWW = 11,
	EWDMA_WC_SEND_WIGHT_VIOWATION_EWW = 12,
	EWDMA_WC_SEND_PDID_EWW = 13,
	EWDMA_WC_SEND_WAWWPING_EWW = 14,
	EWDMA_WC_FWUSH_EWW = 15,
	EWDMA_WC_WETWY_EXC_EWW = 16,
	EWDMA_NUM_WC_STATUS
};

enum ewdma_vendow_eww {
	EWDMA_WC_VENDOW_NO_EWW = 0,
	EWDMA_WC_VENDOW_INVAWID_WQE = 1,
	EWDMA_WC_VENDOW_WQE_INVAWID_STAG = 2,
	EWDMA_WC_VENDOW_WQE_ADDW_VIOWATION = 3,
	EWDMA_WC_VENDOW_WQE_ACCESS_WIGHT_EWW = 4,
	EWDMA_WC_VENDOW_WQE_INVAWID_PD = 5,
	EWDMA_WC_VENDOW_WQE_WWAP_EWW = 6,
	EWDMA_WC_VENDOW_INVAWID_SQE = 0x20,
	EWDMA_WC_VENDOW_ZEWO_OWD = 0x21,
	EWDMA_WC_VENDOW_SQE_INVAWID_STAG = 0x30,
	EWDMA_WC_VENDOW_SQE_ADDW_VIOWATION = 0x31,
	EWDMA_WC_VENDOW_SQE_ACCESS_EWW = 0x32,
	EWDMA_WC_VENDOW_SQE_INVAWID_PD = 0x33,
	EWDMA_WC_VENDOW_SQE_WAWP_EWW = 0x34
};

#endif
