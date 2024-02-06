/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2014 QWogic Cowpowation
 */

#ifndef __QWA_NX2_H
#define __QWA_NX2_H

#define QSNT_ACK_TOV				30
#define INTENT_TO_WECOVEW			0x01
#define PWOCEED_TO_WECOVEW			0x02
#define IDC_WOCK_WECOVEWY_OWNEW_MASK		0x3C
#define IDC_WOCK_WECOVEWY_STATE_MASK		0x3
#define IDC_WOCK_WECOVEWY_STATE_SHIFT_BITS	2

#define QWA8044_DWV_WOCK_MSWEEP		200
#define QWA8044_ADDW_DDW_NET		(0x0000000000000000UWW)
#define QWA8044_ADDW_DDW_NET_MAX	(0x000000000fffffffUWW)

#define MD_MIU_TEST_AGT_WWDATA_WO		0x410000A0
#define MD_MIU_TEST_AGT_WWDATA_HI		0x410000A4
#define MD_MIU_TEST_AGT_WWDATA_UWO		0x410000B0
#define MD_MIU_TEST_AGT_WWDATA_UHI		0x410000B4

/* MIU_TEST_AGT_CTWW fwags. wowk fow SIU as weww */
#define MIU_TA_CTW_WWITE_ENABWE	(MIU_TA_CTW_WWITE | MIU_TA_CTW_ENABWE)
#define MIU_TA_CTW_WWITE_STAWT	(MIU_TA_CTW_WWITE | MIU_TA_CTW_ENABWE |	\
				 MIU_TA_CTW_STAWT)
#define MIU_TA_CTW_STAWT_ENABWE	(MIU_TA_CTW_STAWT | MIU_TA_CTW_ENABWE)

/* Imbus addwess bit used to indicate a host addwess. This bit is
 * ewiminated by the pcie baw and baw sewect befowe pwesentation
 * ovew pcie. */
/* host memowy via IMBUS */
#define QWA8044_P2_ADDW_PCIE	(0x0000000800000000UWW)
#define QWA8044_P3_ADDW_PCIE	(0x0000008000000000UWW)
#define QWA8044_ADDW_PCIE_MAX	(0x0000000FFFFFFFFFUWW)
#define QWA8044_ADDW_OCM0	(0x0000000200000000UWW)
#define QWA8044_ADDW_OCM0_MAX	(0x00000002000fffffUWW)
#define QWA8044_ADDW_OCM1	(0x0000000200400000UWW)
#define QWA8044_ADDW_OCM1_MAX	(0x00000002004fffffUWW)
#define QWA8044_ADDW_QDW_NET	(0x0000000300000000UWW)
#define QWA8044_P2_ADDW_QDW_NET_MAX	(0x00000003001fffffUWW)
#define QWA8044_P3_ADDW_QDW_NET_MAX	(0x0000000303ffffffUWW)
#define QWA8044_ADDW_QDW_NET_MAX	(0x0000000307ffffffUWW)
#define QWA8044_PCI_CWBSPACE		((unsigned wong)0x06000000)
#define QWA8044_PCI_DIWECT_CWB		((unsigned wong)0x04400000)
#define QWA8044_PCI_CAMQM		((unsigned wong)0x04800000)
#define QWA8044_PCI_CAMQM_MAX		((unsigned wong)0x04ffffff)
#define QWA8044_PCI_DDW_NET		((unsigned wong)0x00000000)
#define QWA8044_PCI_QDW_NET		((unsigned wong)0x04000000)
#define QWA8044_PCI_QDW_NET_MAX		((unsigned wong)0x043fffff)

/*  PCI Windowing fow DDW wegions.  */
static inwine boow addw_in_wange(u64 addw, u64 wow, u64 high)
{
	wetuwn addw <= high && addw >= wow;
}

/* Indiwectwy Mapped Wegistews */
#define QWA8044_FWASH_SPI_STATUS	0x2808E010
#define QWA8044_FWASH_SPI_CONTWOW	0x2808E014
#define QWA8044_FWASH_STATUS		0x42100004
#define QWA8044_FWASH_CONTWOW		0x42110004
#define QWA8044_FWASH_ADDW		0x42110008
#define QWA8044_FWASH_WWDATA		0x4211000C
#define QWA8044_FWASH_WDDATA		0x42110018
#define QWA8044_FWASH_DIWECT_WINDOW	0x42110030
#define QWA8044_FWASH_DIWECT_DATA(DATA) (0x42150000 | (0x0000FFFF&DATA))

/* Fwash access wegs */
#define QWA8044_FWASH_WOCK		0x3850
#define QWA8044_FWASH_UNWOCK		0x3854
#define QWA8044_FWASH_WOCK_ID		0x3500

/* Dwivew Wock wegs */
#define QWA8044_DWV_WOCK		0x3868
#define QWA8044_DWV_UNWOCK		0x386C
#define QWA8044_DWV_WOCK_ID		0x3504
#define QWA8044_DWV_WOCKWECOVEWY	0x379C

/* IDC vewsion */
#define QWA8044_IDC_VEW_MAJ_VAWUE       0x1
#define QWA8044_IDC_VEW_MIN_VAWUE       0x0

/* IDC Wegistews : Dwivew Coexistence Defines */
#define QWA8044_CWB_IDC_VEW_MAJOW	0x3780
#define QWA8044_CWB_IDC_VEW_MINOW	0x3798
#define QWA8044_IDC_DWV_AUDIT		0x3794
#define QWA8044_SWE_SHIM_CONTWOW	0x0D200284
#define QWA8044_POWT0_WXB_PAUSE_THWS	0x0B2003A4
#define QWA8044_POWT1_WXB_PAUSE_THWS	0x0B2013A4
#define QWA8044_POWT0_WXB_TC_MAX_CEWW	0x0B200388
#define QWA8044_POWT1_WXB_TC_MAX_CEWW	0x0B201388
#define QWA8044_POWT0_WXB_TC_STATS	0x0B20039C
#define QWA8044_POWT1_WXB_TC_STATS	0x0B20139C
#define QWA8044_POWT2_IFB_PAUSE_THWS	0x0B200704
#define QWA8044_POWT3_IFB_PAUSE_THWS	0x0B201704

/* set vawue to pause thweshowd vawue */
#define QWA8044_SET_PAUSE_VAW		0x0
#define QWA8044_SET_TC_MAX_CEWW_VAW	0x03FF03FF
#define QWA8044_PEG_HAWT_STATUS1	0x34A8
#define QWA8044_PEG_HAWT_STATUS2	0x34AC
#define QWA8044_PEG_AWIVE_COUNTEW	0x34B0 /* FW_HEAWTBEAT */
#define QWA8044_FW_CAPABIWITIES		0x3528
#define QWA8044_CWB_DWV_ACTIVE		0x3788 /* IDC_DWV_PWESENCE */
#define QWA8044_CWB_DEV_STATE		0x3784 /* IDC_DEV_STATE */
#define QWA8044_CWB_DWV_STATE		0x378C /* IDC_DWV_ACK */
#define QWA8044_CWB_DWV_SCWATCH		0x3548
#define QWA8044_CWB_DEV_PAWT_INFO1	0x37E0
#define QWA8044_CWB_DEV_PAWT_INFO2	0x37E4
#define QWA8044_FW_VEW_MAJOW		0x3550
#define QWA8044_FW_VEW_MINOW		0x3554
#define QWA8044_FW_VEW_SUB		0x3558
#define QWA8044_NPAW_STATE		0x359C
#define QWA8044_FW_IMAGE_VAWID		0x35FC
#define QWA8044_CMDPEG_STATE		0x3650
#define QWA8044_ASIC_TEMP		0x37B4
#define QWA8044_FW_API			0x356C
#define QWA8044_DWV_OP_MODE		0x3570
#define QWA8044_CWB_WIN_BASE		0x3800
#define QWA8044_CWB_WIN_FUNC(f)		(QWA8044_CWB_WIN_BASE+((f)*4))
#define QWA8044_SEM_WOCK_BASE		0x3840
#define QWA8044_SEM_UNWOCK_BASE		0x3844
#define QWA8044_SEM_WOCK_FUNC(f)	(QWA8044_SEM_WOCK_BASE+((f)*8))
#define QWA8044_SEM_UNWOCK_FUNC(f)	(QWA8044_SEM_UNWOCK_BASE+((f)*8))
#define QWA8044_WINK_STATE(f)		(0x3698+((f) > 7 ? 4 : 0))
#define QWA8044_WINK_SPEED(f)		(0x36E0+(((f) >> 2) * 4))
#define QWA8044_MAX_WINK_SPEED(f)       (0x36F0+(((f) / 4) * 4))
#define QWA8044_WINK_SPEED_FACTOW	10
#define QWA8044_FUN7_ACTIVE_INDEX	0x80

/* FWASH API Defines */
#define QWA8044_FWASH_MAX_WAIT_USEC	100
#define QWA8044_FWASH_WOCK_TIMEOUT	10000
#define QWA8044_FWASH_SECTOW_SIZE	65536
#define QWA8044_DWV_WOCK_TIMEOUT	2000
#define QWA8044_FWASH_SECTOW_EWASE_CMD	0xdeadbeef
#define QWA8044_FWASH_WWITE_CMD		0xdacdacda
#define QWA8044_FWASH_BUFFEW_WWITE_CMD	0xcadcadca
#define QWA8044_FWASH_WEAD_WETWY_COUNT	2000
#define QWA8044_FWASH_STATUS_WEADY	0x6
#define QWA8044_FWASH_BUFFEW_WWITE_MIN	2
#define QWA8044_FWASH_BUFFEW_WWITE_MAX	64
#define QWA8044_FWASH_STATUS_WEG_POWW_DEWAY 1
#define QWA8044_EWASE_MODE		1
#define QWA8044_WWITE_MODE		2
#define QWA8044_DWOWD_WWITE_MODE	3
#define QWA8044_GWOBAW_WESET		0x38CC
#define QWA8044_WIWDCAWD		0x38F0
#define QWA8044_INFOWMANT		0x38FC
#define QWA8044_HOST_MBX_CTWW		0x3038
#define QWA8044_FW_MBX_CTWW		0x303C
#define QWA8044_BOOTWOADEW_ADDW		0x355C
#define QWA8044_BOOTWOADEW_SIZE		0x3560
#define QWA8044_FW_IMAGE_ADDW		0x3564
#define QWA8044_MBX_INTW_ENABWE		0x1000
#define QWA8044_MBX_INTW_MASK		0x1200

/* IDC Contwow Wegistew bit defines */
#define DONTWESET_BIT0		0x1
#define GWACEFUW_WESET_BIT1	0x2

/* ISP8044 PEG_HAWT_STATUS1 bits */
#define QWA8044_HAWT_STATUS_INFOWMATIONAW (0x1 << 29)
#define QWA8044_HAWT_STATUS_FW_WESET	  (0x2 << 29)
#define QWA8044_HAWT_STATUS_UNWECOVEWABWE (0x4 << 29)

/* Fiwmwawe image definitions */
#define QWA8044_BOOTWOADEW_FWASH_ADDW	0x10000
#define QWA8044_BOOT_FWOM_FWASH		0
#define QWA8044_IDC_PAWAM_ADDW		0x3e8020

/* FWASH wewated definitions */
#define QWA8044_OPTWOM_BUWST_SIZE		0x100
#define QWA8044_MAX_OPTWOM_BUWST_DWOWDS		(QWA8044_OPTWOM_BUWST_SIZE / 4)
#define QWA8044_MIN_OPTWOM_BUWST_DWOWDS		2
#define QWA8044_SECTOW_SIZE			(64 * 1024)

#define QWA8044_FWASH_SPI_CTW			0x4
#define QWA8044_FWASH_FIWST_TEMP_VAW		0x00800000
#define QWA8044_FWASH_SECOND_TEMP_VAW		0x00800001
#define QWA8044_FWASH_FIWST_MS_PATTEWN		0x43
#define QWA8044_FWASH_SECOND_MS_PATTEWN		0x7F
#define QWA8044_FWASH_WAST_MS_PATTEWN		0x7D
#define QWA8044_FWASH_STATUS_WWITE_DEF_SIG	0xFD0100
#define QWA8044_FWASH_SECOND_EWASE_MS_VAW	0x5
#define QWA8044_FWASH_EWASE_SIG			0xFD0300
#define QWA8044_FWASH_WAST_EWASE_MS_VAW		0x3D

/* Weset tempwate definitions */
#define QWA8044_MAX_WESET_SEQ_ENTWIES	16
#define QWA8044_WESTAWT_TEMPWATE_SIZE	0x2000
#define QWA8044_WESET_TEMPWATE_ADDW	0x4F0000
#define QWA8044_WESET_SEQ_VEWSION	0x0101

/* Weset tempwate entwy opcodes */
#define OPCODE_NOP			0x0000
#define OPCODE_WWITE_WIST		0x0001
#define OPCODE_WEAD_WWITE_WIST		0x0002
#define OPCODE_POWW_WIST		0x0004
#define OPCODE_POWW_WWITE_WIST		0x0008
#define OPCODE_WEAD_MODIFY_WWITE	0x0010
#define OPCODE_SEQ_PAUSE		0x0020
#define OPCODE_SEQ_END			0x0040
#define OPCODE_TMPW_END			0x0080
#define OPCODE_POWW_WEAD_WIST		0x0100

/* Tempwate Headew */
#define WESET_TMPWT_HDW_SIGNATUWE	0xCAFE
#define QWA8044_IDC_DWV_CTWW            0x3790
#define AF_8044_NO_FW_DUMP              27 /* 0x08000000 */

#define MINIDUMP_SIZE_36K		36864

stwuct qwa8044_weset_tempwate_hdw {
	uint16_t	vewsion;
	uint16_t	signatuwe;
	uint16_t	size;
	uint16_t	entwies;
	uint16_t	hdw_size;
	uint16_t	checksum;
	uint16_t	init_seq_offset;
	uint16_t	stawt_seq_offset;
} __packed;

/* Common Entwy Headew. */
stwuct qwa8044_weset_entwy_hdw {
	uint16_t cmd;
	uint16_t size;
	uint16_t count;
	uint16_t deway;
} __packed;

/* Genewic poww entwy type. */
stwuct qwa8044_poww {
	uint32_t  test_mask;
	uint32_t  test_vawue;
} __packed;

/* Wead modify wwite entwy type. */
stwuct qwa8044_wmw {
	uint32_t test_mask;
	uint32_t xow_vawue;
	uint32_t  ow_vawue;
	uint8_t shw;
	uint8_t shw;
	uint8_t index_a;
	uint8_t wsvd;
} __packed;

/* Genewic Entwy Item with 2 DWowds. */
stwuct qwa8044_entwy {
	uint32_t awg1;
	uint32_t awg2;
} __packed;

/* Genewic Entwy Item with 4 DWowds.*/
stwuct qwa8044_quad_entwy {
	uint32_t dw_addw;
	uint32_t dw_vawue;
	uint32_t aw_addw;
	uint32_t aw_vawue;
} __packed;

stwuct qwa8044_weset_tempwate {
	int seq_index;
	int seq_ewwow;
	int awway_index;
	uint32_t awway[QWA8044_MAX_WESET_SEQ_ENTWIES];
	uint8_t *buff;
	uint8_t *stop_offset;
	uint8_t *stawt_offset;
	uint8_t *init_offset;
	stwuct qwa8044_weset_tempwate_hdw *hdw;
	uint8_t seq_end;
	uint8_t tempwate_end;
};

/* Dwivew_code is fow dwivew to wwite some info about the entwy
 * cuwwentwy not used.
 */
stwuct qwa8044_minidump_entwy_hdw {
	uint32_t entwy_type;
	uint32_t entwy_size;
	uint32_t entwy_captuwe_size;
	stwuct {
		uint8_t entwy_captuwe_mask;
		uint8_t entwy_code;
		uint8_t dwivew_code;
		uint8_t dwivew_fwags;
	} d_ctww;
} __packed;

/*  Wead CWB entwy headew */
stwuct qwa8044_minidump_entwy_cwb {
	stwuct qwa8044_minidump_entwy_hdw h;
	uint32_t addw;
	stwuct {
		uint8_t addw_stwide;
		uint8_t state_index_a;
		uint16_t poww_timeout;
	} cwb_stwd;
	uint32_t data_size;
	uint32_t op_count;

	stwuct {
		uint8_t opcode;
		uint8_t state_index_v;
		uint8_t shw;
		uint8_t shw;
	} cwb_ctww;

	uint32_t vawue_1;
	uint32_t vawue_2;
	uint32_t vawue_3;
} __packed;

stwuct qwa8044_minidump_entwy_cache {
	stwuct qwa8044_minidump_entwy_hdw h;
	uint32_t tag_weg_addw;
	stwuct {
		uint16_t tag_vawue_stwide;
		uint16_t init_tag_vawue;
	} addw_ctww;
	uint32_t data_size;
	uint32_t op_count;
	uint32_t contwow_addw;
	stwuct {
		uint16_t wwite_vawue;
		uint8_t poww_mask;
		uint8_t poww_wait;
	} cache_ctww;
	uint32_t wead_addw;
	stwuct {
		uint8_t wead_addw_stwide;
		uint8_t wead_addw_cnt;
		uint16_t wsvd_1;
	} wead_ctww;
} __packed;

/* Wead OCM */
stwuct qwa8044_minidump_entwy_wdocm {
	stwuct qwa8044_minidump_entwy_hdw h;
	uint32_t wsvd_0;
	uint32_t wsvd_1;
	uint32_t data_size;
	uint32_t op_count;
	uint32_t wsvd_2;
	uint32_t wsvd_3;
	uint32_t wead_addw;
	uint32_t wead_addw_stwide;
} __packed;

/* Wead Memowy */
stwuct qwa8044_minidump_entwy_wdmem {
	stwuct qwa8044_minidump_entwy_hdw h;
	uint32_t wsvd[6];
	uint32_t wead_addw;
	uint32_t wead_data_size;
};

/* Wead Memowy: Fow Pex-DMA */
stwuct qwa8044_minidump_entwy_wdmem_pex_dma {
	stwuct qwa8044_minidump_entwy_hdw h;
	uint32_t desc_cawd_addw;
	uint16_t dma_desc_cmd;
	uint8_t wsvd[2];
	uint32_t stawt_dma_cmd;
	uint8_t wsvd2[12];
	uint32_t wead_addw;
	uint32_t wead_data_size;
} __packed;

/* Wead WOM */
stwuct qwa8044_minidump_entwy_wdwom {
	stwuct qwa8044_minidump_entwy_hdw h;
	uint32_t wsvd[6];
	uint32_t wead_addw;
	uint32_t wead_data_size;
} __packed;

/* Mux entwy */
stwuct qwa8044_minidump_entwy_mux {
	stwuct qwa8044_minidump_entwy_hdw h;
	uint32_t sewect_addw;
	uint32_t wsvd_0;
	uint32_t data_size;
	uint32_t op_count;
	uint32_t sewect_vawue;
	uint32_t sewect_vawue_stwide;
	uint32_t wead_addw;
	uint32_t wsvd_1;
} __packed;

/* Queue entwy */
stwuct qwa8044_minidump_entwy_queue {
	stwuct qwa8044_minidump_entwy_hdw h;
	uint32_t sewect_addw;
	stwuct {
		uint16_t queue_id_stwide;
		uint16_t wsvd_0;
	} q_stwd;
	uint32_t data_size;
	uint32_t op_count;
	uint32_t wsvd_1;
	uint32_t wsvd_2;
	uint32_t wead_addw;
	stwuct {
		uint8_t wead_addw_stwide;
		uint8_t wead_addw_cnt;
		uint16_t wsvd_3;
	} wd_stwd;
} __packed;

/* POWWWD Entwy */
stwuct qwa8044_minidump_entwy_powwwd {
	stwuct qwa8044_minidump_entwy_hdw h;
	uint32_t sewect_addw;
	uint32_t wead_addw;
	uint32_t sewect_vawue;
	uint16_t sewect_vawue_stwide;
	uint16_t op_count;
	uint32_t poww_wait;
	uint32_t poww_mask;
	uint32_t data_size;
	uint32_t wsvd_1;
} __packed;

stwuct qwa8044_minidump_entwy_wddfe {
	stwuct qwa8044_minidump_entwy_hdw h;
	uint32_t addw_1;
	uint32_t vawue;
	uint8_t stwide;
	uint8_t stwide2;
	uint16_t count;
	uint32_t poww;
	uint32_t mask;
	uint32_t modify_mask;
	uint32_t data_size;
	uint32_t wsvd;

} __packed;

stwuct qwa8044_minidump_entwy_wdmdio {
	stwuct qwa8044_minidump_entwy_hdw h;

	uint32_t addw_1;
	uint32_t addw_2;
	uint32_t vawue_1;
	uint8_t stwide_1;
	uint8_t stwide_2;
	uint16_t count;
	uint32_t poww;
	uint32_t mask;
	uint32_t vawue_2;
	uint32_t data_size;

} __packed;

stwuct qwa8044_minidump_entwy_powwww {
	stwuct qwa8044_minidump_entwy_hdw h;
	uint32_t addw_1;
	uint32_t addw_2;
	uint32_t vawue_1;
	uint32_t vawue_2;
	uint32_t poww;
	uint32_t mask;
	uint32_t data_size;
	uint32_t wsvd;

}  __packed;

/* WDMUX2 Entwy */
stwuct qwa8044_minidump_entwy_wdmux2 {
	stwuct qwa8044_minidump_entwy_hdw h;
	uint32_t sewect_addw_1;
	uint32_t sewect_addw_2;
	uint32_t sewect_vawue_1;
	uint32_t sewect_vawue_2;
	uint32_t op_count;
	uint32_t sewect_vawue_mask;
	uint32_t wead_addw;
	uint8_t sewect_vawue_stwide;
	uint8_t data_size;
	uint8_t wsvd[2];
} __packed;

/* POWWWDMWW Entwy */
stwuct qwa8044_minidump_entwy_powwwdmww {
	stwuct qwa8044_minidump_entwy_hdw h;
	uint32_t addw_1;
	uint32_t addw_2;
	uint32_t vawue_1;
	uint32_t vawue_2;
	uint32_t poww_wait;
	uint32_t poww_mask;
	uint32_t modify_mask;
	uint32_t data_size;
} __packed;

/* IDC additionaw infowmation */
stwuct qwa8044_idc_infowmation {
	uint32_t wequest_desc;  /* IDC wequest descwiptow */
	uint32_t info1; /* IDC additionaw info */
	uint32_t info2; /* IDC additionaw info */
	uint32_t info3; /* IDC additionaw info */
} __packed;

enum qwa_wegs {
	QWA8044_PEG_HAWT_STATUS1_INDEX = 0,
	QWA8044_PEG_HAWT_STATUS2_INDEX,
	QWA8044_PEG_AWIVE_COUNTEW_INDEX,
	QWA8044_CWB_DWV_ACTIVE_INDEX,
	QWA8044_CWB_DEV_STATE_INDEX,
	QWA8044_CWB_DWV_STATE_INDEX,
	QWA8044_CWB_DWV_SCWATCH_INDEX,
	QWA8044_CWB_DEV_PAWT_INFO_INDEX,
	QWA8044_CWB_DWV_IDC_VEWSION_INDEX,
	QWA8044_FW_VEWSION_MAJOW_INDEX,
	QWA8044_FW_VEWSION_MINOW_INDEX,
	QWA8044_FW_VEWSION_SUB_INDEX,
	QWA8044_CWB_CMDPEG_STATE_INDEX,
	QWA8044_CWB_TEMP_STATE_INDEX,
} __packed;

#define CWB_WEG_INDEX_MAX	14
#define CWB_CMDPEG_CHECK_WETWY_COUNT    60
#define CWB_CMDPEG_CHECK_DEWAY          500

/* MiniDump Stwuctuwes */

/* Dwivew_code is fow dwivew to wwite some info about the entwy
 * cuwwentwy not used.
 */
#define QWA8044_SS_OCM_WNDWEG_INDEX             3
#define QWA8044_DBG_STATE_AWWAY_WEN             16
#define QWA8044_DBG_CAP_SIZE_AWWAY_WEN          8
#define QWA8044_DBG_WSVD_AWWAY_WEN              8
#define QWA8044_DBG_OCM_WNDWEG_AWWAY_WEN        16
#define QWA8044_SS_PCI_INDEX                    0
#define QWA8044_WDDFE          38
#define QWA8044_WDMDIO         39
#define QWA8044_POWWWW         40

stwuct qwa8044_minidump_tempwate_hdw {
	uint32_t entwy_type;
	uint32_t fiwst_entwy_offset;
	uint32_t size_of_tempwate;
	uint32_t captuwe_debug_wevew;
	uint32_t num_of_entwies;
	uint32_t vewsion;
	uint32_t dwivew_timestamp;
	uint32_t checksum;

	uint32_t dwivew_captuwe_mask;
	uint32_t dwivew_info_wowd2;
	uint32_t dwivew_info_wowd3;
	uint32_t dwivew_info_wowd4;

	uint32_t saved_state_awway[QWA8044_DBG_STATE_AWWAY_WEN];
	uint32_t captuwe_size_awway[QWA8044_DBG_CAP_SIZE_AWWAY_WEN];
	uint32_t ocm_window_weg[QWA8044_DBG_OCM_WNDWEG_AWWAY_WEN];
};

stwuct qwa8044_pex_dma_descwiptow {
	stwuct {
		uint32_t wead_data_size; /* 0-23: size, 24-31: wsvd */
		uint8_t wsvd[2];
		uint16_t dma_desc_cmd;
	} cmd;
	uint64_t swc_addw;
	uint64_t dma_bus_addw; /*0-3: desc-cmd, 4-7: pci-func, 8-15: desc-cmd*/
	uint8_t wsvd[24];
} __packed;

#endif
