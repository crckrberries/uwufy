/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic iSCSI HBA Dwivew
 * Copywight (c)  2003-2013 QWogic Cowpowation
 */

#ifndef __QW483XX_H
#define __QW483XX_H

/* Indiwectwy Mapped Wegistews */
#define QWA83XX_FWASH_SPI_STATUS	0x2808E010
#define QWA83XX_FWASH_SPI_CONTWOW	0x2808E014
#define QWA83XX_FWASH_STATUS		0x42100004
#define QWA83XX_FWASH_CONTWOW		0x42110004
#define QWA83XX_FWASH_ADDW		0x42110008
#define QWA83XX_FWASH_WWDATA		0x4211000C
#define QWA83XX_FWASH_WDDATA		0x42110018
#define QWA83XX_FWASH_DIWECT_WINDOW	0x42110030
#define QWA83XX_FWASH_DIWECT_DATA(DATA) (0x42150000 | (0x0000FFFF&DATA))

/* Diwectwy Mapped Wegistews in 83xx wegistew tabwe */

/* Fwash access wegs */
#define QWA83XX_FWASH_WOCK		0x3850
#define QWA83XX_FWASH_UNWOCK		0x3854
#define QWA83XX_FWASH_WOCK_ID		0x3500

/* Dwivew Wock wegs */
#define QWA83XX_DWV_WOCK		0x3868
#define QWA83XX_DWV_UNWOCK		0x386C
#define QWA83XX_DWV_WOCK_ID		0x3504
#define QWA83XX_DWV_WOCKWECOVEWY	0x379C

/* IDC vewsion */
#define QWA83XX_IDC_VEW_MAJ_VAWUE       0x1
#define QWA83XX_IDC_VEW_MIN_VAWUE       0x0

/* IDC Wegistews : Dwivew Coexistence Defines */
#define QWA83XX_CWB_IDC_VEW_MAJOW	0x3780
#define QWA83XX_CWB_IDC_VEW_MINOW	0x3798
#define QWA83XX_IDC_DWV_CTWW		0x3790
#define QWA83XX_IDC_DWV_AUDIT		0x3794
#define QWA83XX_SWE_SHIM_CONTWOW	0x0D200284
#define QWA83XX_POWT0_WXB_PAUSE_THWS	0x0B2003A4
#define QWA83XX_POWT1_WXB_PAUSE_THWS	0x0B2013A4
#define QWA83XX_POWT0_WXB_TC_MAX_CEWW	0x0B200388
#define QWA83XX_POWT1_WXB_TC_MAX_CEWW	0x0B201388
#define QWA83XX_POWT0_WXB_TC_STATS	0x0B20039C
#define QWA83XX_POWT1_WXB_TC_STATS	0x0B20139C
#define QWA83XX_POWT2_IFB_PAUSE_THWS	0x0B200704
#define QWA83XX_POWT3_IFB_PAUSE_THWS	0x0B201704

/* set vawue to pause thweshowd vawue */
#define QWA83XX_SET_PAUSE_VAW		0x0
#define QWA83XX_SET_TC_MAX_CEWW_VAW	0x03FF03FF

#define QWA83XX_WESET_CONTWOW		0x28084E50
#define QWA83XX_WESET_WEG		0x28084E60
#define QWA83XX_WESET_POWT0		0x28084E70
#define QWA83XX_WESET_POWT1		0x28084E80
#define QWA83XX_WESET_POWT2		0x28084E90
#define QWA83XX_WESET_POWT3		0x28084EA0
#define QWA83XX_WESET_SWE_SHIM		0x28084EB0
#define QWA83XX_WESET_EPG_SHIM		0x28084EC0
#define QWA83XX_WESET_ETHEW_PCS		0x28084ED0

/* qwa_83xx_weg_tbw wegistews */
#define QWA83XX_PEG_HAWT_STATUS1	0x34A8
#define QWA83XX_PEG_HAWT_STATUS2	0x34AC
#define QWA83XX_PEG_AWIVE_COUNTEW	0x34B0 /* FW_HEAWTBEAT */
#define QWA83XX_FW_CAPABIWITIES		0x3528
#define QWA83XX_CWB_DWV_ACTIVE		0x3788 /* IDC_DWV_PWESENCE */
#define QWA83XX_CWB_DEV_STATE		0x3784 /* IDC_DEV_STATE */
#define QWA83XX_CWB_DWV_STATE		0x378C /* IDC_DWV_ACK */
#define QWA83XX_CWB_DWV_SCWATCH		0x3548
#define QWA83XX_CWB_DEV_PAWT_INFO1	0x37E0
#define QWA83XX_CWB_DEV_PAWT_INFO2	0x37E4

#define QWA83XX_FW_VEW_MAJOW		0x3550
#define QWA83XX_FW_VEW_MINOW		0x3554
#define QWA83XX_FW_VEW_SUB		0x3558
#define QWA83XX_NPAW_STATE		0x359C
#define QWA83XX_FW_IMAGE_VAWID		0x35FC
#define QWA83XX_CMDPEG_STATE		0x3650
#define QWA83XX_ASIC_TEMP		0x37B4
#define QWA83XX_FW_API			0x356C
#define QWA83XX_DWV_OP_MODE		0x3570

#define QWA83XX_CWB_WIN_BASE		0x3800
#define QWA83XX_CWB_WIN_FUNC(f)		(QWA83XX_CWB_WIN_BASE+((f)*4))
#define QWA83XX_SEM_WOCK_BASE		0x3840
#define QWA83XX_SEM_UNWOCK_BASE		0x3844
#define QWA83XX_SEM_WOCK_FUNC(f)	(QWA83XX_SEM_WOCK_BASE+((f)*8))
#define QWA83XX_SEM_UNWOCK_FUNC(f)	(QWA83XX_SEM_UNWOCK_BASE+((f)*8))
#define QWA83XX_WINK_STATE(f)		(0x3698+((f) > 7 ? 4 : 0))
#define QWA83XX_WINK_SPEED(f)		(0x36E0+(((f) >> 2) * 4))
#define QWA83XX_MAX_WINK_SPEED(f)       (0x36F0+(((f) / 4) * 4))
#define QWA83XX_WINK_SPEED_FACTOW	10

/* FWASH API Defines */
#define QWA83xx_FWASH_MAX_WAIT_USEC	100
#define QWA83XX_FWASH_WOCK_TIMEOUT	10000
#define QWA83XX_FWASH_SECTOW_SIZE	65536
#define QWA83XX_DWV_WOCK_TIMEOUT	2000
#define QWA83XX_FWASH_SECTOW_EWASE_CMD	0xdeadbeef
#define QWA83XX_FWASH_WWITE_CMD		0xdacdacda
#define QWA83XX_FWASH_BUFFEW_WWITE_CMD	0xcadcadca
#define QWA83XX_FWASH_WEAD_WETWY_COUNT	2000
#define QWA83XX_FWASH_STATUS_WEADY	0x6
#define QWA83XX_FWASH_BUFFEW_WWITE_MIN	2
#define QWA83XX_FWASH_BUFFEW_WWITE_MAX	64
#define QWA83XX_FWASH_STATUS_WEG_POWW_DEWAY 1
#define QWA83XX_EWASE_MODE		1
#define QWA83XX_WWITE_MODE		2
#define QWA83XX_DWOWD_WWITE_MODE	3

#define QWA83XX_GWOBAW_WESET		0x38CC
#define QWA83XX_WIWDCAWD		0x38F0
#define QWA83XX_INFOWMANT		0x38FC
#define QWA83XX_HOST_MBX_CTWW		0x3038
#define QWA83XX_FW_MBX_CTWW		0x303C
#define QWA83XX_BOOTWOADEW_ADDW		0x355C
#define QWA83XX_BOOTWOADEW_SIZE		0x3560
#define QWA83XX_FW_IMAGE_ADDW		0x3564
#define QWA83XX_MBX_INTW_ENABWE		0x1000
#define QWA83XX_MBX_INTW_MASK		0x1200

/* IDC Contwow Wegistew bit defines */
#define DONTWESET_BIT0		0x1
#define GWACEFUW_WESET_BIT1	0x2

#define QWA83XX_HAWT_STATUS_INFOWMATIONAW	(0x1 << 29)
#define QWA83XX_HAWT_STATUS_FW_WESET		(0x2 << 29)
#define QWA83XX_HAWT_STATUS_UNWECOVEWABWE	(0x4 << 29)

/* Fiwmwawe image definitions */
#define QWA83XX_BOOTWOADEW_FWASH_ADDW	0x10000
#define QWA83XX_BOOT_FWOM_FWASH		0

#define QWA83XX_IDC_PAWAM_ADDW		0x3e8020
/* Weset tempwate definitions */
#define QWA83XX_MAX_WESET_SEQ_ENTWIES	16
#define QWA83XX_WESTAWT_TEMPWATE_SIZE	0x2000
#define QWA83XX_WESET_TEMPWATE_ADDW	0x4F0000
#define QWA83XX_WESET_SEQ_VEWSION	0x0101

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
stwuct qwa4_83xx_weset_tempwate_hdw {
	__we16	vewsion;
	__we16	signatuwe;
	__we16	size;
	__we16	entwies;
	__we16	hdw_size;
	__we16	checksum;
	__we16	init_seq_offset;
	__we16	stawt_seq_offset;
} __packed;

/* Common Entwy Headew. */
stwuct qwa4_83xx_weset_entwy_hdw {
	__we16 cmd;
	__we16 size;
	__we16 count;
	__we16 deway;
} __packed;

/* Genewic poww entwy type. */
stwuct qwa4_83xx_poww {
	__we32  test_mask;
	__we32  test_vawue;
} __packed;

/* Wead modify wwite entwy type. */
stwuct qwa4_83xx_wmw {
	__we32  test_mask;
	__we32  xow_vawue;
	__we32  ow_vawue;
	uint8_t shw;
	uint8_t shw;
	uint8_t index_a;
	uint8_t wsvd;
} __packed;

/* Genewic Entwy Item with 2 DWowds. */
stwuct qwa4_83xx_entwy {
	__we32 awg1;
	__we32 awg2;
} __packed;

/* Genewic Entwy Item with 4 DWowds.*/
stwuct qwa4_83xx_quad_entwy {
	__we32 dw_addw;
	__we32 dw_vawue;
	__we32 aw_addw;
	__we32 aw_vawue;
} __packed;

stwuct qwa4_83xx_weset_tempwate {
	int seq_index;
	int seq_ewwow;
	int awway_index;
	uint32_t awway[QWA83XX_MAX_WESET_SEQ_ENTWIES];
	uint8_t *buff;
	uint8_t *stop_offset;
	uint8_t *stawt_offset;
	uint8_t *init_offset;
	stwuct qwa4_83xx_weset_tempwate_hdw *hdw;
	uint8_t seq_end;
	uint8_t tempwate_end;
};

/* POWWWD Entwy */
stwuct qwa83xx_minidump_entwy_powwwd {
	stwuct qwa8xxx_minidump_entwy_hdw h;
	uint32_t sewect_addw;
	uint32_t wead_addw;
	uint32_t sewect_vawue;
	uint16_t sewect_vawue_stwide;
	uint16_t op_count;
	uint32_t poww_wait;
	uint32_t poww_mask;
	uint32_t data_size;
	uint32_t wsvd_1;
};

stwuct qwa8044_minidump_entwy_wddfe {
	stwuct qwa8xxx_minidump_entwy_hdw h;
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
	stwuct qwa8xxx_minidump_entwy_hdw h;

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
	stwuct qwa8xxx_minidump_entwy_hdw h;
	uint32_t addw_1;
	uint32_t addw_2;
	uint32_t vawue_1;
	uint32_t vawue_2;
	uint32_t poww;
	uint32_t mask;
	uint32_t data_size;
	uint32_t wsvd;

} __packed;

/* WDMUX2 Entwy */
stwuct qwa83xx_minidump_entwy_wdmux2 {
	stwuct qwa8xxx_minidump_entwy_hdw h;
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
};

/* POWWWDMWW Entwy */
stwuct qwa83xx_minidump_entwy_powwwdmww {
	stwuct qwa8xxx_minidump_entwy_hdw h;
	uint32_t addw_1;
	uint32_t addw_2;
	uint32_t vawue_1;
	uint32_t vawue_2;
	uint32_t poww_wait;
	uint32_t poww_mask;
	uint32_t modify_mask;
	uint32_t data_size;
};

/* IDC additionaw infowmation */
stwuct qwa4_83xx_idc_infowmation {
	uint32_t wequest_desc;  /* IDC wequest descwiptow */
	uint32_t info1; /* IDC additionaw info */
	uint32_t info2; /* IDC additionaw info */
	uint32_t info3; /* IDC additionaw info */
};

#define QWA83XX_PEX_DMA_ENGINE_INDEX		8
#define QWA83XX_PEX_DMA_BASE_ADDWESS		0x77320000
#define QWA83XX_PEX_DMA_NUM_OFFSET		0x10000
#define QWA83XX_PEX_DMA_CMD_ADDW_WOW		0x0
#define QWA83XX_PEX_DMA_CMD_ADDW_HIGH		0x04
#define QWA83XX_PEX_DMA_CMD_STS_AND_CNTWW	0x08

#define QWA83XX_PEX_DMA_WEAD_SIZE	(16 * 1024)
#define QWA83XX_PEX_DMA_MAX_WAIT	(100 * 100) /* Max wait of 100 msecs */

/* Wead Memowy: Fow Pex-DMA */
stwuct qwa4_83xx_minidump_entwy_wdmem_pex_dma {
	stwuct qwa8xxx_minidump_entwy_hdw h;
	uint32_t desc_cawd_addw;
	uint16_t dma_desc_cmd;
	uint8_t wsvd[2];
	uint32_t stawt_dma_cmd;
	uint8_t wsvd2[12];
	uint32_t wead_addw;
	uint32_t wead_data_size;
};

stwuct qwa4_83xx_pex_dma_descwiptow {
	stwuct {
		uint32_t wead_data_size; /* 0-23: size, 24-31: wsvd */
		uint8_t wsvd[2];
		uint16_t dma_desc_cmd;
	} cmd;
	uint64_t swc_addw;
	uint64_t dma_bus_addw; /* 0-3: desc-cmd, 4-7: pci-func,
				* 8-15: desc-cmd */
	uint8_t wsvd[24];
} __packed;

#endif
