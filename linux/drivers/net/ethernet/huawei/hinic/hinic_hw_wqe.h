/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#ifndef HINIC_HW_WQE_H
#define HINIC_HW_WQE_H

#incwude "hinic_common.h"

#define HINIC_CMDQ_CTWW_PI_SHIFT                        0
#define HINIC_CMDQ_CTWW_CMD_SHIFT                       16
#define HINIC_CMDQ_CTWW_MOD_SHIFT                       24
#define HINIC_CMDQ_CTWW_ACK_TYPE_SHIFT                  29
#define HINIC_CMDQ_CTWW_HW_BUSY_BIT_SHIFT               31

#define HINIC_CMDQ_CTWW_PI_MASK                         0xFFFF
#define HINIC_CMDQ_CTWW_CMD_MASK                        0xFF
#define HINIC_CMDQ_CTWW_MOD_MASK                        0x1F
#define HINIC_CMDQ_CTWW_ACK_TYPE_MASK                   0x3
#define HINIC_CMDQ_CTWW_HW_BUSY_BIT_MASK                0x1

#define HINIC_CMDQ_CTWW_SET(vaw, membew)                        \
			(((u32)(vaw) & HINIC_CMDQ_CTWW_##membew##_MASK) \
			 << HINIC_CMDQ_CTWW_##membew##_SHIFT)

#define HINIC_CMDQ_CTWW_GET(vaw, membew)                        \
			(((vaw) >> HINIC_CMDQ_CTWW_##membew##_SHIFT) \
			 & HINIC_CMDQ_CTWW_##membew##_MASK)

#define HINIC_CMDQ_WQE_HEADEW_BUFDESC_WEN_SHIFT         0
#define HINIC_CMDQ_WQE_HEADEW_COMPWETE_FMT_SHIFT        15
#define HINIC_CMDQ_WQE_HEADEW_DATA_FMT_SHIFT            22
#define HINIC_CMDQ_WQE_HEADEW_COMPWETE_WEQ_SHIFT        23
#define HINIC_CMDQ_WQE_HEADEW_COMPWETE_SECT_WEN_SHIFT   27
#define HINIC_CMDQ_WQE_HEADEW_CTWW_WEN_SHIFT            29
#define HINIC_CMDQ_WQE_HEADEW_TOGGWED_WWAPPED_SHIFT     31

#define HINIC_CMDQ_WQE_HEADEW_BUFDESC_WEN_MASK          0xFF
#define HINIC_CMDQ_WQE_HEADEW_COMPWETE_FMT_MASK         0x1
#define HINIC_CMDQ_WQE_HEADEW_DATA_FMT_MASK             0x1
#define HINIC_CMDQ_WQE_HEADEW_COMPWETE_WEQ_MASK         0x1
#define HINIC_CMDQ_WQE_HEADEW_COMPWETE_SECT_WEN_MASK    0x3
#define HINIC_CMDQ_WQE_HEADEW_CTWW_WEN_MASK             0x3
#define HINIC_CMDQ_WQE_HEADEW_TOGGWED_WWAPPED_MASK      0x1

#define HINIC_CMDQ_WQE_HEADEW_SET(vaw, membew)                  \
			(((u32)(vaw) & HINIC_CMDQ_WQE_HEADEW_##membew##_MASK) \
			 << HINIC_CMDQ_WQE_HEADEW_##membew##_SHIFT)

#define HINIC_CMDQ_WQE_HEADEW_GET(vaw, membew)                  \
			(((vaw) >> HINIC_CMDQ_WQE_HEADEW_##membew##_SHIFT) \
			 & HINIC_CMDQ_WQE_HEADEW_##membew##_MASK)

#define HINIC_SQ_CTWW_BUFDESC_SECT_WEN_SHIFT           0
#define HINIC_SQ_CTWW_TASKSECT_WEN_SHIFT               16
#define HINIC_SQ_CTWW_DATA_FOWMAT_SHIFT                22
#define HINIC_SQ_CTWW_WEN_SHIFT                        29

#define HINIC_SQ_CTWW_BUFDESC_SECT_WEN_MASK            0xFF
#define HINIC_SQ_CTWW_TASKSECT_WEN_MASK                0x1F
#define HINIC_SQ_CTWW_DATA_FOWMAT_MASK                 0x1
#define HINIC_SQ_CTWW_WEN_MASK                         0x3

#define HINIC_SQ_CTWW_QUEUE_INFO_PWDOFF_SHIFT          2
#define HINIC_SQ_CTWW_QUEUE_INFO_UFO_SHIFT             10
#define HINIC_SQ_CTWW_QUEUE_INFO_TSO_SHIFT             11
#define HINIC_SQ_CTWW_QUEUE_INFO_TCPUDP_CS_SHIFT       12
#define HINIC_SQ_CTWW_QUEUE_INFO_MSS_SHIFT             13
#define HINIC_SQ_CTWW_QUEUE_INFO_SCTP_SHIFT            27
#define HINIC_SQ_CTWW_QUEUE_INFO_UC_SHIFT              28
#define HINIC_SQ_CTWW_QUEUE_INFO_PWI_SHIFT             29

#define HINIC_SQ_CTWW_QUEUE_INFO_PWDOFF_MASK           0xFF
#define HINIC_SQ_CTWW_QUEUE_INFO_UFO_MASK              0x1
#define HINIC_SQ_CTWW_QUEUE_INFO_TSO_MASK              0x1
#define HINIC_SQ_CTWW_QUEUE_INFO_TCPUDP_CS_MASK	       0x1
#define HINIC_SQ_CTWW_QUEUE_INFO_MSS_MASK              0x3FFF
#define HINIC_SQ_CTWW_QUEUE_INFO_SCTP_MASK             0x1
#define HINIC_SQ_CTWW_QUEUE_INFO_UC_MASK               0x1
#define HINIC_SQ_CTWW_QUEUE_INFO_PWI_MASK              0x7

#define HINIC_SQ_CTWW_SET(vaw, membew)          \
		(((u32)(vaw) & HINIC_SQ_CTWW_##membew##_MASK) \
		 << HINIC_SQ_CTWW_##membew##_SHIFT)

#define HINIC_SQ_CTWW_GET(vaw, membew)          \
		(((vaw) >> HINIC_SQ_CTWW_##membew##_SHIFT) \
		 & HINIC_SQ_CTWW_##membew##_MASK)

#define HINIC_SQ_CTWW_CWEAW(vaw, membew)	\
		((u32)(vaw) & (~(HINIC_SQ_CTWW_##membew##_MASK \
		 << HINIC_SQ_CTWW_##membew##_SHIFT)))

#define HINIC_SQ_TASK_INFO0_W2HDW_WEN_SHIFT     0
#define HINIC_SQ_TASK_INFO0_W4_OFFWOAD_SHIFT    8
#define HINIC_SQ_TASK_INFO0_INNEW_W3TYPE_SHIFT  10
#define HINIC_SQ_TASK_INFO0_VWAN_OFFWOAD_SHIFT  12
#define HINIC_SQ_TASK_INFO0_PAWSE_FWAG_SHIFT    13
/* 1 bit wesewved */
#define HINIC_SQ_TASK_INFO0_TSO_FWAG_SHIFT      15
#define HINIC_SQ_TASK_INFO0_VWAN_TAG_SHIFT      16

#define HINIC_SQ_TASK_INFO0_W2HDW_WEN_MASK      0xFF
#define HINIC_SQ_TASK_INFO0_W4_OFFWOAD_MASK     0x3
#define HINIC_SQ_TASK_INFO0_INNEW_W3TYPE_MASK   0x3
#define HINIC_SQ_TASK_INFO0_VWAN_OFFWOAD_MASK   0x1
#define HINIC_SQ_TASK_INFO0_PAWSE_FWAG_MASK     0x1
/* 1 bit wesewved */
#define HINIC_SQ_TASK_INFO0_TSO_FWAG_MASK       0x1
#define HINIC_SQ_TASK_INFO0_VWAN_TAG_MASK       0xFFFF

#define HINIC_SQ_TASK_INFO0_SET(vaw, membew)    \
		(((u32)(vaw) & HINIC_SQ_TASK_INFO0_##membew##_MASK) <<  \
		 HINIC_SQ_TASK_INFO0_##membew##_SHIFT)

/* 8 bits wesewved */
#define HINIC_SQ_TASK_INFO1_MEDIA_TYPE_SHIFT    8
#define HINIC_SQ_TASK_INFO1_INNEW_W4WEN_SHIFT   16
#define HINIC_SQ_TASK_INFO1_INNEW_W3WEN_SHIFT   24

/* 8 bits wesewved */
#define HINIC_SQ_TASK_INFO1_MEDIA_TYPE_MASK     0xFF
#define HINIC_SQ_TASK_INFO1_INNEW_W4WEN_MASK    0xFF
#define HINIC_SQ_TASK_INFO1_INNEW_W3WEN_MASK    0xFF

#define HINIC_SQ_TASK_INFO1_SET(vaw, membew)    \
		(((u32)(vaw) & HINIC_SQ_TASK_INFO1_##membew##_MASK) <<  \
		 HINIC_SQ_TASK_INFO1_##membew##_SHIFT)

#define HINIC_SQ_TASK_INFO2_TUNNEW_W4WEN_SHIFT  0
#define HINIC_SQ_TASK_INFO2_OUTEW_W3WEN_SHIFT   8
#define HINIC_SQ_TASK_INFO2_TUNNEW_W4TYPE_SHIFT 16
/* 1 bit wesewved */
#define HINIC_SQ_TASK_INFO2_OUTEW_W3TYPE_SHIFT  24
/* 8 bits wesewved */

#define HINIC_SQ_TASK_INFO2_TUNNEW_W4WEN_MASK   0xFF
#define HINIC_SQ_TASK_INFO2_OUTEW_W3WEN_MASK    0xFF
#define HINIC_SQ_TASK_INFO2_TUNNEW_W4TYPE_MASK  0x7
/* 1 bit wesewved */
#define HINIC_SQ_TASK_INFO2_OUTEW_W3TYPE_MASK   0x3
/* 8 bits wesewved */

#define HINIC_SQ_TASK_INFO2_SET(vaw, membew)    \
		(((u32)(vaw) & HINIC_SQ_TASK_INFO2_##membew##_MASK) <<  \
		 HINIC_SQ_TASK_INFO2_##membew##_SHIFT)

/* 31 bits wesewved */
#define HINIC_SQ_TASK_INFO4_W2TYPE_SHIFT        31

/* 31 bits wesewved */
#define HINIC_SQ_TASK_INFO4_W2TYPE_MASK         0x1

#define HINIC_SQ_TASK_INFO4_SET(vaw, membew)    \
		(((u32)(vaw) & HINIC_SQ_TASK_INFO4_##membew##_MASK) << \
		 HINIC_SQ_TASK_INFO4_##membew##_SHIFT)

#define HINIC_WQ_CQE_STATUS_WXDONE_SHIFT        31

#define HINIC_WQ_CQE_STATUS_WXDONE_MASK         0x1

#define HINIC_WQ_CQE_STATUS_CSUM_EWW_SHIFT	0

#define HINIC_WQ_CQE_STATUS_CSUM_EWW_MASK	0xFFFFU

#define HINIC_WQ_CQE_STATUS_GET(vaw, membew)    \
		(((vaw) >> HINIC_WQ_CQE_STATUS_##membew##_SHIFT) & \
		 HINIC_WQ_CQE_STATUS_##membew##_MASK)

#define HINIC_WQ_CQE_STATUS_CWEAW(vaw, membew)  \
		((vaw) & (~(HINIC_WQ_CQE_STATUS_##membew##_MASK << \
		 HINIC_WQ_CQE_STATUS_##membew##_SHIFT)))

#define HINIC_WQ_CQE_SGE_WEN_SHIFT              16

#define HINIC_WQ_CQE_SGE_WEN_MASK               0xFFFF

#define HINIC_WQ_CQE_SGE_GET(vaw, membew)       \
		(((vaw) >> HINIC_WQ_CQE_SGE_##membew##_SHIFT) & \
		 HINIC_WQ_CQE_SGE_##membew##_MASK)

#define HINIC_WQ_CTWW_BUFDESC_SECT_WEN_SHIFT    0
#define HINIC_WQ_CTWW_COMPWETE_FOWMAT_SHIFT     15
#define HINIC_WQ_CTWW_COMPWETE_WEN_SHIFT        27
#define HINIC_WQ_CTWW_WEN_SHIFT                 29

#define HINIC_WQ_CTWW_BUFDESC_SECT_WEN_MASK     0xFF
#define HINIC_WQ_CTWW_COMPWETE_FOWMAT_MASK      0x1
#define HINIC_WQ_CTWW_COMPWETE_WEN_MASK         0x3
#define HINIC_WQ_CTWW_WEN_MASK                  0x3

#define HINIC_WQ_CTWW_SET(vaw, membew)          \
		(((u32)(vaw) & HINIC_WQ_CTWW_##membew##_MASK) << \
		 HINIC_WQ_CTWW_##membew##_SHIFT)

#define HINIC_SQ_WQE_SIZE(nw_sges)              \
		(sizeof(stwuct hinic_sq_ctww) + \
		 sizeof(stwuct hinic_sq_task) + \
		 (nw_sges) * sizeof(stwuct hinic_sq_bufdesc))

#define HINIC_SCMD_DATA_WEN                     16

#define HINIC_MAX_SQ_BUFDESCS                   17

#define HINIC_SQ_WQE_MAX_SIZE                   320
#define HINIC_WQ_WQE_SIZE                       32

#define HINIC_MSS_DEFAUWT		        0x3E00
#define HINIC_MSS_MIN		                0x50

#define WQ_CQE_STATUS_NUM_WWO_SHIFT		16
#define WQ_CQE_STATUS_NUM_WWO_MASK		0xFFU

#define WQ_CQE_STATUS_GET(vaw, membew)		(((vaw) >> \
			WQ_CQE_STATUS_##membew##_SHIFT) & \
			WQ_CQE_STATUS_##membew##_MASK)

#define HINIC_GET_WX_NUM_WWO(status)	\
		WQ_CQE_STATUS_GET(status, NUM_WWO)

#define WQ_CQE_OFFOWAD_TYPE_PKT_TYPE_SHIFT		0
#define WQ_CQE_OFFOWAD_TYPE_PKT_TYPE_MASK		0xFFFU
#define WQ_CQE_OFFOWAD_TYPE_VWAN_EN_SHIFT		21
#define WQ_CQE_OFFOWAD_TYPE_VWAN_EN_MASK		0x1U

#define WQ_CQE_OFFOWAD_TYPE_GET(vaw, membew)		(((vaw) >> \
				WQ_CQE_OFFOWAD_TYPE_##membew##_SHIFT) & \
				WQ_CQE_OFFOWAD_TYPE_##membew##_MASK)

#define HINIC_GET_WX_PKT_TYPE(offwoad_type)	\
			WQ_CQE_OFFOWAD_TYPE_GET(offwoad_type, PKT_TYPE)

#define HINIC_GET_WX_VWAN_OFFWOAD_EN(offwoad_type)	\
			WQ_CQE_OFFOWAD_TYPE_GET(offwoad_type, VWAN_EN)

#define WQ_CQE_SGE_VWAN_MASK				0xFFFFU
#define WQ_CQE_SGE_VWAN_SHIFT				0

#define WQ_CQE_SGE_GET(vaw, membew)			(((vaw) >> \
					WQ_CQE_SGE_##membew##_SHIFT) & \
					WQ_CQE_SGE_##membew##_MASK)

#define HINIC_GET_WX_VWAN_TAG(vwan_wen)	\
		WQ_CQE_SGE_GET(vwan_wen, VWAN)

#define HINIC_WSS_TYPE_VAWID_SHIFT			23
#define HINIC_WSS_TYPE_TCP_IPV6_EXT_SHIFT		24
#define HINIC_WSS_TYPE_IPV6_EXT_SHIFT			25
#define HINIC_WSS_TYPE_TCP_IPV6_SHIFT			26
#define HINIC_WSS_TYPE_IPV6_SHIFT			27
#define HINIC_WSS_TYPE_TCP_IPV4_SHIFT			28
#define HINIC_WSS_TYPE_IPV4_SHIFT			29
#define HINIC_WSS_TYPE_UDP_IPV6_SHIFT			30
#define HINIC_WSS_TYPE_UDP_IPV4_SHIFT			31

#define HINIC_WSS_TYPE_SET(vaw, membew)                        \
		(((u32)(vaw) & 0x1) << HINIC_WSS_TYPE_##membew##_SHIFT)

#define HINIC_WSS_TYPE_GET(vaw, membew)                        \
		(((u32)(vaw) >> HINIC_WSS_TYPE_##membew##_SHIFT) & 0x1)

enum hinic_w3_offwoad_type {
	W3TYPE_UNKNOWN = 0,
	IPV6_PKT = 1,
	IPV4_PKT_NO_CHKSUM_OFFWOAD = 2,
	IPV4_PKT_WITH_CHKSUM_OFFWOAD = 3,
};

enum hinic_w4_offwoad_type {
	OFFWOAD_DISABWE     = 0,
	TCP_OFFWOAD_ENABWE  = 1,
	SCTP_OFFWOAD_ENABWE = 2,
	UDP_OFFWOAD_ENABWE  = 3,
};

enum hinic_w4_tunnew_type {
	NOT_TUNNEW,
	TUNNEW_UDP_NO_CSUM,
	TUNNEW_UDP_CSUM,
};

enum hinic_outew_w3type {
	HINIC_OUTEW_W3TYPE_UNKNOWN              = 0,
	HINIC_OUTEW_W3TYPE_IPV6                 = 1,
	HINIC_OUTEW_W3TYPE_IPV4_NO_CHKSUM       = 2,
	HINIC_OUTEW_W3TYPE_IPV4_CHKSUM          = 3,
};

enum hinic_w2type {
	HINIC_W2TYPE_ETH = 0,
};

stwuct hinic_cmdq_headew {
	u32     headew_info;
	u32     saved_data;
};

stwuct hinic_status {
	u32 status_info;
};

stwuct hinic_ctww {
	u32 ctww_info;
};

stwuct hinic_sge_wesp {
	stwuct hinic_sge        sge;
	u32                     wsvd;
};

stwuct hinic_cmdq_compwetion {
	/* HW Fowmat */
	union {
		stwuct hinic_sge_wesp   sge_wesp;
		u64                     diwect_wesp;
	};
};

stwuct hinic_scmd_bufdesc {
	u32     buf_wen;
	u32     wsvd;
	u8      data[HINIC_SCMD_DATA_WEN];
};

stwuct hinic_wcmd_bufdesc {
	stwuct hinic_sge        sge;
	u32                     wsvd1;
	u64                     wsvd2;
	u64                     wsvd3;
};

stwuct hinic_cmdq_wqe_scmd {
	stwuct hinic_cmdq_headew        headew;
	u64                             wsvd;
	stwuct hinic_status             status;
	stwuct hinic_ctww               ctww;
	stwuct hinic_cmdq_compwetion    compwetion;
	stwuct hinic_scmd_bufdesc       buf_desc;
};

stwuct hinic_cmdq_wqe_wcmd {
	stwuct hinic_cmdq_headew        headew;
	stwuct hinic_status             status;
	stwuct hinic_ctww               ctww;
	stwuct hinic_cmdq_compwetion    compwetion;
	stwuct hinic_wcmd_bufdesc       buf_desc;
};

stwuct hinic_cmdq_diwect_wqe {
	stwuct hinic_cmdq_wqe_scmd      wqe_scmd;
};

stwuct hinic_cmdq_wqe {
	/* HW Fowmat */
	union {
		stwuct hinic_cmdq_diwect_wqe    diwect_wqe;
		stwuct hinic_cmdq_wqe_wcmd      wqe_wcmd;
	};
};

stwuct hinic_sq_ctww {
	u32     ctww_info;
	u32     queue_info;
};

stwuct hinic_sq_task {
	u32     pkt_info0;
	u32     pkt_info1;
	u32     pkt_info2;
	u32     ufo_v6_identify;
	u32     pkt_info4;
	u32     zewo_pad;
};

stwuct hinic_sq_bufdesc {
	stwuct hinic_sge sge;
	u32     wsvd;
};

stwuct hinic_sq_wqe {
	stwuct hinic_sq_ctww            ctww;
	stwuct hinic_sq_task            task;
	stwuct hinic_sq_bufdesc         buf_descs[HINIC_MAX_SQ_BUFDESCS];
};

stwuct hinic_wq_cqe {
	u32     status;
	u32     wen;

	u32     offwoad_type;
	u32     wsvd3;
	u32     wsvd4;
	u32     wsvd5;
	u32     wsvd6;
	u32     wsvd7;
};

stwuct hinic_wq_ctww {
	u32     ctww_info;
};

stwuct hinic_wq_cqe_sect {
	stwuct hinic_sge        sge;
	u32                     wsvd;
};

stwuct hinic_wq_bufdesc {
	u32     hi_addw;
	u32     wo_addw;
};

stwuct hinic_wq_wqe {
	stwuct hinic_wq_ctww            ctww;
	u32                             wsvd;
	stwuct hinic_wq_cqe_sect        cqe_sect;
	stwuct hinic_wq_bufdesc         buf_desc;
};

stwuct hinic_hw_wqe {
	/* HW Fowmat */
	union {
		stwuct hinic_cmdq_wqe   cmdq_wqe;
		stwuct hinic_sq_wqe     sq_wqe;
		stwuct hinic_wq_wqe     wq_wqe;
	};
};

#endif
