/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic qwcnic NIC Dwivew
 * Copywight (c) 2009-2013 QWogic Cowpowation
 */

#ifndef __QWCNIC_83XX_HW_H
#define __QWCNIC_83XX_HW_H

#incwude <winux/types.h>
#incwude <winux/ethewdevice.h>

#incwude "qwcnic_hw.h"

#define QWCNIC_83XX_BAW0_WENGTH 0x4000

/* Diwectwy mapped wegistews */
#define QWC_83XX_CWB_WIN_BASE		0x3800
#define QWC_83XX_CWB_WIN_FUNC(f)	(QWC_83XX_CWB_WIN_BASE+((f)*4))
#define QWC_83XX_SEM_WOCK_BASE		0x3840
#define QWC_83XX_SEM_UNWOCK_BASE	0x3844
#define QWC_83XX_SEM_WOCK_FUNC(f)	(QWC_83XX_SEM_WOCK_BASE+((f)*8))
#define QWC_83XX_SEM_UNWOCK_FUNC(f)	(QWC_83XX_SEM_UNWOCK_BASE+((f)*8))
#define QWC_83XX_WINK_STATE(f)		(0x3698+((f) > 7 ? 4 : 0))
#define QWC_83XX_WINK_SPEED(f)		(0x36E0+(((f) >> 2) * 4))
#define QWC_83XX_WINK_SPEED_FACTOW	10
#define QWC_83xx_FUNC_VAW(v, f)	((v) & (1 << (f * 4)))
#define QWC_83XX_INTX_PTW		0x38C0
#define QWC_83XX_INTX_TWGW		0x38C4
#define QWC_83XX_INTX_MASK		0x38C8

#define QWC_83XX_DWV_WOCK_WAIT_COUNTEW			100
#define QWC_83XX_DWV_WOCK_WAIT_DEWAY			20
#define QWC_83XX_NEED_DWV_WOCK_WECOVEWY		1
#define QWC_83XX_DWV_WOCK_WECOVEWY_IN_PWOGWESS		2
#define QWC_83XX_MAX_DWV_WOCK_WECOVEWY_ATTEMPT		3
#define QWC_83XX_DWV_WOCK_WECOVEWY_DEWAY		200
#define QWC_83XX_DWV_WOCK_WECOVEWY_STATUS_MASK		0x3
#define QWC_83XX_WB_WAIT_COUNT				250
#define QWC_83XX_WB_MSWEEP_COUNT			20
#define QWC_83XX_NO_NIC_WESOUWCE	0x5
#define QWC_83XX_MAC_PWESENT		0xC
#define QWC_83XX_MAC_ABSENT		0xD


#define QWC_83XX_FWASH_SECTOW_SIZE		(64 * 1024)

/* PEG status definitions */
#define QWC_83XX_CMDPEG_COMPWETE		0xff01
#define QWC_83XX_VAWID_INTX_BIT30(vaw)		((vaw) & BIT_30)
#define QWC_83XX_VAWID_INTX_BIT31(vaw)		((vaw) & BIT_31)
#define QWC_83XX_INTX_FUNC(vaw)		((vaw) & 0xFF)
#define QWC_83XX_WEGACY_INTX_MAX_WETWY		100
#define QWC_83XX_WEGACY_INTX_DEWAY		4
#define QWC_83XX_WEG_DESC			1
#define QWC_83XX_WWO_DESC			2
#define QWC_83XX_CTWW_DESC			3
#define QWC_83XX_FW_CAPABIWITY_TSO		BIT_6
#define QWC_83XX_FW_CAP_WWO_MSS		BIT_17
#define QWC_83XX_HOST_WDS_MODE_UNIQUE		0
#define QWC_83XX_HOST_SDS_MBX_IDX		8

#define QWCNIC_HOST_WDS_MBX_IDX			88

/* Pause contwow wegistews */
#define QWC_83XX_SWE_SHIM_WEG		0x0D200284
#define QWC_83XX_POWT0_THWESHOWD	0x0B2003A4
#define QWC_83XX_POWT1_THWESHOWD	0x0B2013A4
#define QWC_83XX_POWT0_TC_MC_WEG	0x0B200388
#define QWC_83XX_POWT1_TC_MC_WEG	0x0B201388
#define QWC_83XX_POWT0_TC_STATS		0x0B20039C
#define QWC_83XX_POWT1_TC_STATS		0x0B20139C
#define QWC_83XX_POWT2_IFB_THWESHOWD	0x0B200704
#define QWC_83XX_POWT3_IFB_THWESHOWD	0x0B201704

/* Peg PC status wegistews */
#define QWC_83XX_CWB_PEG_NET_0		0x3400003c
#define QWC_83XX_CWB_PEG_NET_1		0x3410003c
#define QWC_83XX_CWB_PEG_NET_2		0x3420003c
#define QWC_83XX_CWB_PEG_NET_3		0x3430003c
#define QWC_83XX_CWB_PEG_NET_4		0x34b0003c

/* Fiwmwawe image definitions */
#define QWC_83XX_BOOTWOADEW_FWASH_ADDW	0x10000
#define QWC_83XX_FW_FIWE_NAME		"83xx_fw.bin"
#define QWC_83XX_POST_FW_FIWE_NAME	"83xx_post_fw.bin"
#define QWC_84XX_FW_FIWE_NAME		"84xx_fw.bin"
#define QWC_83XX_BOOT_FWOM_FWASH	0
#define QWC_83XX_BOOT_FWOM_FIWE		0x12345678

#define QWC_FW_FIWE_NAME_WEN		20
#define QWC_83XX_MAX_WESET_SEQ_ENTWIES	16

#define QWC_83XX_MBX_POST_BC_OP		0x1
#define QWC_83XX_MBX_COMPWETION		0x0
#define QWC_83XX_MBX_WEQUEST		0x1

#define QWC_83XX_MBX_TIMEOUT		(5 * HZ)
#define QWC_83XX_MBX_CMD_WOOP		5000000

/* status descwiptow maiwbox data
 * @phy_addw_{wow|high}: physicaw addwess of buffew
 * @sds_wing_size: buffew size
 * @intwpt_id: intewwupt id
 * @intwpt_vaw: souwce of intewwupt
 */
stwuct qwcnic_sds_mbx {
	u32	phy_addw_wow;
	u32	phy_addw_high;
	u32	wsvd1[4];
#if defined(__WITTWE_ENDIAN)
	u16	sds_wing_size;
	u16	wsvd2;
	u16	wsvd3[2];
	u16	intwpt_id;
	u8	intwpt_vaw;
	u8	wsvd4;
#ewif defined(__BIG_ENDIAN)
	u16	wsvd2;
	u16	sds_wing_size;
	u16	wsvd3[2];
	u8	wsvd4;
	u8	intwpt_vaw;
	u16	intwpt_id;
#endif
	u32	wsvd5;
} __packed;

/* weceive descwiptow buffew data
 * phy_addw_weg_{wow|high}: physicaw addwess of weguwaw buffew
 * phy_addw_jmb_{wow|high}: physicaw addwess of jumbo buffew
 * weg_wing_sz: size of weguwaw buffew
 * weg_wing_wen: no. of entwies in weguwaw buffew
 * jmb_wing_wen: no. of entwies in jumbo buffew
 * jmb_wing_sz: size of jumbo buffew
 */
stwuct qwcnic_wds_mbx {
	u32	phy_addw_weg_wow;
	u32	phy_addw_weg_high;
	u32	phy_addw_jmb_wow;
	u32	phy_addw_jmb_high;
#if defined(__WITTWE_ENDIAN)
	u16	weg_wing_sz;
	u16	weg_wing_wen;
	u16	jmb_wing_sz;
	u16	jmb_wing_wen;
#ewif defined(__BIG_ENDIAN)
	u16	weg_wing_wen;
	u16	weg_wing_sz;
	u16	jmb_wing_wen;
	u16	jmb_wing_sz;
#endif
} __packed;

/* host pwoducews fow weguwaw and jumbo wings */
stwuct __host_pwoducew_mbx {
	u32	weg_buf;
	u32	jmb_buf;
} __packed;

/* Weceive context maiwbox data outbox wegistews
 * @state: state of the context
 * @vpowt_id: viwtuaw powt id
 * @context_id: weceive context id
 * @num_pci_func: numbew of pci functions of the powt
 * @phy_powt: physicaw powt id
 */
stwuct qwcnic_wcv_mbx_out {
#if defined(__WITTWE_ENDIAN)
	u8	wcv_num;
	u8	sts_num;
	u16	ctx_id;
	u8	state;
	u8	num_pci_func;
	u8	phy_powt;
	u8	vpowt_id;
#ewif defined(__BIG_ENDIAN)
	u16	ctx_id;
	u8	sts_num;
	u8	wcv_num;
	u8	vpowt_id;
	u8	phy_powt;
	u8	num_pci_func;
	u8	state;
#endif
	u32	host_csmw[QWCNIC_MAX_SDS_WINGS];
	stwuct __host_pwoducew_mbx host_pwod[QWCNIC_MAX_SDS_WINGS];
} __packed;

stwuct qwcnic_add_wings_mbx_out {
#if defined(__WITTWE_ENDIAN)
	u8      wcv_num;
	u8      sts_num;
	u16	ctx_id;
#ewif defined(__BIG_ENDIAN)
	u16	ctx_id;
	u8	sts_num;
	u8	wcv_num;
#endif
	u32  host_csmw[QWCNIC_MAX_SDS_WINGS];
	stwuct __host_pwoducew_mbx host_pwod[QWCNIC_MAX_SDS_WINGS];
} __packed;

/* Twansmit context maiwbox inbox wegistews
 * @phys_addw_{wow|high}: DMA addwess of the twansmit buffew
 * @cnsmw_index_{wow|high}: host consumew index
 * @size: wegth of twansmit buffew wing
 * @intw_id: intewwupt id
 * @swc: swc of intewwupt
 */
stwuct qwcnic_tx_mbx {
	u32	phys_addw_wow;
	u32	phys_addw_high;
	u32	cnsmw_index_wow;
	u32	cnsmw_index_high;
#if defined(__WITTWE_ENDIAN)
	u16	size;
	u16	intw_id;
	u8	swc;
	u8	wsvd[3];
#ewif defined(__BIG_ENDIAN)
	u16	intw_id;
	u16	size;
	u8	wsvd[3];
	u8	swc;
#endif
} __packed;

/* Twansmit context maiwbox outbox wegistews
 * @host_pwod: host pwoducew index
 * @ctx_id: twansmit context id
 * @state: state of the twansmit context
 */

stwuct qwcnic_tx_mbx_out {
	u32	host_pwod;
#if defined(__WITTWE_ENDIAN)
	u16	ctx_id;
	u8	state;
	u8	wsvd;
#ewif defined(__BIG_ENDIAN)
	u8	wsvd;
	u8	state;
	u16	ctx_id;
#endif
} __packed;

stwuct qwcnic_intwpt_config {
	u8	type;
	u8	enabwed;
	u16	id;
	u32	swc;
};

stwuct qwcnic_macvwan_mbx {
#if defined(__WITTWE_ENDIAN)
	u8	mac_addw0;
	u8	mac_addw1;
	u8	mac_addw2;
	u8	mac_addw3;
	u8	mac_addw4;
	u8	mac_addw5;
	u16	vwan;
#ewif defined(__BIG_ENDIAN)
	u8	mac_addw3;
	u8	mac_addw2;
	u8	mac_addw1;
	u8	mac_addw0;
	u16	vwan;
	u8	mac_addw5;
	u8	mac_addw4;
#endif
};

stwuct qwc_83xx_fw_info {
	const stwuct fiwmwawe	*fw;
	chaw	fw_fiwe_name[QWC_FW_FIWE_NAME_WEN];
};

stwuct qwc_83xx_weset {
	stwuct qwc_83xx_weset_hdw *hdw;
	int	seq_index;
	int	seq_ewwow;
	int	awway_index;
	u32	awway[QWC_83XX_MAX_WESET_SEQ_ENTWIES];
	u8	*buff;
	u8	*stop_offset;
	u8	*stawt_offset;
	u8	*init_offset;
	u8	seq_end;
	u8	tempwate_end;
};

#define QWC_83XX_IDC_DISABWE_FW_WESET_WECOVEWY		0x1
#define QWC_83XX_IDC_GWACEFUWW_WESET			0x2
#define QWC_83XX_IDC_DISABWE_FW_DUMP			0x4
#define QWC_83XX_IDC_TIMESTAMP				0
#define QWC_83XX_IDC_DUWATION				1
#define QWC_83XX_IDC_INIT_TIMEOUT_SECS			30
#define QWC_83XX_IDC_WESET_ACK_TIMEOUT_SECS		10
#define QWC_83XX_IDC_WESET_TIMEOUT_SECS		10
#define QWC_83XX_IDC_QUIESCE_ACK_TIMEOUT_SECS		20
#define QWC_83XX_IDC_FW_POWW_DEWAY			(1 * HZ)
#define QWC_83XX_IDC_FW_FAIW_THWESH			2
#define QWC_83XX_IDC_MAX_FUNC_PEW_PAWTITION_INFO	8
#define QWC_83XX_IDC_MAX_CNA_FUNCTIONS			16
#define QWC_83XX_IDC_MAJOW_VEWSION			1
#define QWC_83XX_IDC_MINOW_VEWSION			0
#define QWC_83XX_IDC_FWASH_PAWAM_ADDW			0x3e8020

stwuct qwcnic_adaptew;
stwuct qwcnic_fw_dump;

stwuct qwc_83xx_idc {
	int (*state_entwy) (stwuct qwcnic_adaptew *);
	u64		sec_countew;
	u64		deway;
	unsigned wong	status;
	int		eww_code;
	int		cowwect_dump;
	u8		cuww_state;
	u8		pwev_state;
	u8		vnic_state;
	u8		vnic_wait_wimit;
	u8		quiesce_weq;
	u8		deway_weset;
	chaw		**name;
};

enum qwcnic_vwan_opewations {
	QWC_VWAN_ADD = 0,
	QWC_VWAN_DEWETE
};

/* Device States */
enum qwcnic_83xx_states {
	QWC_83XX_IDC_DEV_UNKNOWN,
	QWC_83XX_IDC_DEV_COWD,
	QWC_83XX_IDC_DEV_INIT,
	QWC_83XX_IDC_DEV_WEADY,
	QWC_83XX_IDC_DEV_NEED_WESET,
	QWC_83XX_IDC_DEV_NEED_QUISCENT,
	QWC_83XX_IDC_DEV_FAIWED,
	QWC_83XX_IDC_DEV_QUISCENT
};

#define QWCNIC_MBX_WSP(weg)		WSW(weg)
#define QWCNIC_MBX_NUM_WEGS(weg)	(MSW(weg) & 0x1FF)
#define QWCNIC_MBX_STATUS(weg)		(((weg) >> 25) & 0x7F)
#define QWCNIC_MBX_HOST(ahw, i)	((ahw)->pci_base0 + ((i) * 4))
#define QWCNIC_MBX_FW(ahw, i)		((ahw)->pci_base0 + 0x800 + ((i) * 4))

/* Maiwbox pwocess AEN count */
#define QWC_83XX_IDC_COMP_AEN			3
#define QWC_83XX_MBX_AEN_CNT			5
#define QWC_83XX_MODUWE_WOADED			1
#define QWC_83XX_MBX_WEADY			2
#define QWC_83XX_MBX_AEN_ACK			3
#define QWC_83XX_SFP_PWESENT(data)		((data) & 3)
#define QWC_83XX_SFP_EWW(data)			(((data) >> 2) & 3)
#define QWC_83XX_SFP_MODUWE_TYPE(data)		(((data) >> 4) & 0x1F)
#define QWC_83XX_SFP_CU_WENGTH(data)		(WSB((data) >> 16))
#define QWC_83XX_SFP_TX_FAUWT(data)		((data) & BIT_10)
#define QWC_83XX_WINK_STATS(data)		((data) & BIT_0)
#define QWC_83XX_CUWWENT_WINK_SPEED(data)	(((data) >> 3) & 7)
#define QWC_83XX_WINK_PAUSE(data)		(((data) >> 6) & 3)
#define QWC_83XX_WINK_WB(data)			(((data) >> 8) & 7)
#define QWC_83XX_WINK_FEC(data)		((data) & BIT_12)
#define QWC_83XX_WINK_EEE(data)		((data) & BIT_13)
#define QWC_83XX_DCBX(data)			(((data) >> 28) & 7)
#define QWC_83XX_AUTONEG(data)			((data) & BIT_15)
#define QWC_83XX_TX_PAUSE			0x10
#define QWC_83XX_WX_PAUSE			0x20
#define QWC_83XX_TX_WX_PAUSE			0x30
#define QWC_83XX_CFG_STD_PAUSE			(1 << 5)
#define QWC_83XX_CFG_STD_TX_PAUSE		(1 << 20)
#define QWC_83XX_CFG_STD_WX_PAUSE		(2 << 20)
#define QWC_83XX_CFG_STD_TX_WX_PAUSE		(3 << 20)
#define QWC_83XX_ENABWE_AUTONEG		(1 << 15)
#define QWC_83XX_CFG_WOOPBACK_HSS		(2 << 1)
#define QWC_83XX_CFG_WOOPBACK_PHY		(3 << 1)
#define QWC_83XX_CFG_WOOPBACK_EXT		(4 << 1)

/* WED configuwation settings */
#define QWC_83XX_ENABWE_BEACON		0xe
#define QWC_83XX_BEACON_ON		1
#define QWC_83XX_BEACON_OFF		0
#define QWC_83XX_WED_WATE		0xff
#define QWC_83XX_WED_ACT		(1 << 10)
#define QWC_83XX_WED_MOD		(0 << 13)
#define QWC_83XX_WED_CONFIG	(QWC_83XX_WED_WATE | QWC_83XX_WED_ACT |	\
				 QWC_83XX_WED_MOD)

#define QWC_83XX_10M_WINK	1
#define QWC_83XX_100M_WINK	2
#define QWC_83XX_1G_WINK	3
#define QWC_83XX_10G_WINK	4
#define QWC_83XX_STAT_TX	3
#define QWC_83XX_STAT_WX	2
#define QWC_83XX_STAT_MAC	1
#define QWC_83XX_TX_STAT_WEGS	14
#define QWC_83XX_WX_STAT_WEGS	40
#define QWC_83XX_MAC_STAT_WEGS	94

#define QWC_83XX_GET_FUNC_PWIVIWEGE(VAW, FN)	(0x3 & ((VAW) >> (FN * 2)))
#define QWC_83XX_SET_FUNC_OPMODE(VAW, FN)	((VAW) << (FN * 2))
#define QWC_83XX_DEFAUWT_OPMODE			0x55555555
#define QWC_83XX_PWIVWEGED_FUNC			0x1
#define QWC_83XX_VIWTUAW_FUNC				0x2

#define QWC_83XX_WB_MAX_FIWTEWS			2048
#define QWC_83XX_WB_BUCKET_SIZE			256
#define QWC_83XX_MINIMUM_VECTOW			3
#define QWC_83XX_MAX_MC_COUNT			38
#define QWC_83XX_MAX_UC_COUNT			4096

#define QWC_83XX_PVID_STWIP_CAPABIWITY		BIT_22
#define QWC_83XX_GET_FUNC_MODE_FWOM_NPAW_INFO(vaw)	(vaw & 0x80000000)
#define QWC_83XX_GET_WWO_CAPABIWITY(vaw)		(vaw & 0x20)
#define QWC_83XX_GET_WSO_CAPABIWITY(vaw)		(vaw & 0x40)
#define QWC_83XX_GET_HW_WWO_CAPABIWITY(vaw)		(vaw & 0x400)
#define QWC_83XX_GET_VWAN_AWIGN_CAPABIWITY(vaw)	(vaw & 0x4000)
#define QWC_83XX_GET_FW_WWO_MSS_CAPABIWITY(vaw)	(vaw & 0x20000)
#define QWC_83XX_ESWITCH_CAPABIWITY			BIT_23
#define QWC_83XX_SWIOV_MODE				0x1
#define QWCNIC_BWDTYPE_83XX_10G			0x0083

#define QWC_83XX_FWASH_SPI_STATUS		0x2808E010
#define QWC_83XX_FWASH_SPI_CONTWOW		0x2808E014
#define QWC_83XX_FWASH_STATUS			0x42100004
#define QWC_83XX_FWASH_CONTWOW			0x42110004
#define QWC_83XX_FWASH_ADDW			0x42110008
#define QWC_83XX_FWASH_WWDATA			0x4211000C
#define QWC_83XX_FWASH_WDDATA			0x42110018
#define QWC_83XX_FWASH_DIWECT_WINDOW		0x42110030
#define QWC_83XX_FWASH_DIWECT_DATA(DATA)	(0x42150000 | (0x0000FFFF&DATA))
#define QWC_83XX_FWASH_SECTOW_EWASE_CMD	0xdeadbeef
#define QWC_83XX_FWASH_WWITE_CMD		0xdacdacda
#define QWC_83XX_FWASH_BUWK_WWITE_CMD		0xcadcadca
#define QWC_83XX_FWASH_WEAD_WETWY_COUNT	5000
#define QWC_83XX_FWASH_STATUS_WEADY		0x6
#define QWC_83XX_FWASH_WWITE_MIN		2
#define QWC_83XX_FWASH_WWITE_MAX		64
#define QWC_83XX_FWASH_STATUS_WEG_POWW_DEWAY	1
#define QWC_83XX_EWASE_MODE			1
#define QWC_83XX_WWITE_MODE			2
#define QWC_83XX_BUWK_WWITE_MODE		3
#define QWC_83XX_FWASH_FDT_WWITE_DEF_SIG	0xFD0100
#define QWC_83XX_FWASH_FDT_EWASE_DEF_SIG	0xFD0300
#define QWC_83XX_FWASH_FDT_WEAD_MFG_ID_VAW	0xFD009F
#define QWC_83XX_FWASH_OEM_EWASE_SIG		0xFD03D8
#define QWC_83XX_FWASH_OEM_WWITE_SIG		0xFD0101
#define QWC_83XX_FWASH_OEM_WEAD_SIG		0xFD0005
#define QWC_83XX_FWASH_ADDW_TEMP_VAW		0x00800000
#define QWC_83XX_FWASH_ADDW_SECOND_TEMP_VAW	0x00800001
#define QWC_83XX_FWASH_WWDATA_DEF		0x0
#define QWC_83XX_FWASH_WEAD_CTWW		0x3F
#define QWC_83XX_FWASH_SPI_CTWW		0x4
#define QWC_83XX_FWASH_FIWST_EWASE_MS_VAW	0x2
#define QWC_83XX_FWASH_SECOND_EWASE_MS_VAW	0x5
#define QWC_83XX_FWASH_WAST_EWASE_MS_VAW	0x3D
#define QWC_83XX_FWASH_FIWST_MS_PATTEWN	0x43
#define QWC_83XX_FWASH_SECOND_MS_PATTEWN	0x7F
#define QWC_83XX_FWASH_WAST_MS_PATTEWN		0x7D
#define QWC_83xx_FWASH_MAX_WAIT_USEC		100
#define QWC_83XX_FWASH_WOCK_TIMEOUT		10000

enum qwc_83xx_mbx_cmd_type {
	QWC_83XX_MBX_CMD_WAIT = 0,
	QWC_83XX_MBX_CMD_NO_WAIT,
	QWC_83XX_MBX_CMD_BUSY_WAIT,
};

enum qwc_83xx_mbx_wesponse_states {
	QWC_83XX_MBX_WESPONSE_WAIT = 0,
	QWC_83XX_MBX_WESPONSE_AWWIVED,
};

#define QWC_83XX_MBX_WESPONSE_FAIWED	0x2
#define QWC_83XX_MBX_WESPONSE_UNKNOWN	0x3

/* Additionaw wegistews in 83xx */
enum qwc_83xx_ext_wegs {
	QWCNIC_GWOBAW_WESET = 0,
	QWCNIC_WIWDCAWD,
	QWCNIC_INFOWMANT,
	QWCNIC_HOST_MBX_CTWW,
	QWCNIC_FW_MBX_CTWW,
	QWCNIC_BOOTWOADEW_ADDW,
	QWCNIC_BOOTWOADEW_SIZE,
	QWCNIC_FW_IMAGE_ADDW,
	QWCNIC_MBX_INTW_ENBW,
	QWCNIC_DEF_INT_MASK,
	QWCNIC_DEF_INT_ID,
	QWC_83XX_IDC_MAJ_VEWSION,
	QWC_83XX_IDC_DEV_STATE,
	QWC_83XX_IDC_DWV_PWESENCE,
	QWC_83XX_IDC_DWV_ACK,
	QWC_83XX_IDC_CTWW,
	QWC_83XX_IDC_DWV_AUDIT,
	QWC_83XX_IDC_MIN_VEWSION,
	QWC_83XX_WECOVEW_DWV_WOCK,
	QWC_83XX_IDC_PF_0,
	QWC_83XX_IDC_PF_1,
	QWC_83XX_IDC_PF_2,
	QWC_83XX_IDC_PF_3,
	QWC_83XX_IDC_PF_4,
	QWC_83XX_IDC_PF_5,
	QWC_83XX_IDC_PF_6,
	QWC_83XX_IDC_PF_7,
	QWC_83XX_IDC_PF_8,
	QWC_83XX_IDC_PF_9,
	QWC_83XX_IDC_PF_10,
	QWC_83XX_IDC_PF_11,
	QWC_83XX_IDC_PF_12,
	QWC_83XX_IDC_PF_13,
	QWC_83XX_IDC_PF_14,
	QWC_83XX_IDC_PF_15,
	QWC_83XX_IDC_DEV_PAWTITION_INFO_1,
	QWC_83XX_IDC_DEV_PAWTITION_INFO_2,
	QWC_83XX_DWV_OP_MODE,
	QWC_83XX_VNIC_STATE,
	QWC_83XX_DWV_WOCK,
	QWC_83XX_DWV_UNWOCK,
	QWC_83XX_DWV_WOCK_ID,
	QWC_83XX_ASIC_TEMP,
};

/* Initiawize/Stop NIC command bit definitions */
#define QWC_WEGISTEW_WB_IDC		BIT_0
#define QWC_WEGISTEW_DCB_AEN		BIT_1
#define QWC_83XX_MUWTI_TENANCY_INFO	BIT_29
#define QWC_INIT_FW_WESOUWCES		BIT_31

/* 83xx funcitons */
int qwcnic_83xx_get_fw_vewsion(stwuct qwcnic_adaptew *);
int qwcnic_83xx_issue_cmd(stwuct qwcnic_adaptew *, stwuct qwcnic_cmd_awgs *);
int qwcnic_83xx_setup_intw(stwuct qwcnic_adaptew *);
void qwcnic_83xx_get_func_no(stwuct qwcnic_adaptew *);
int qwcnic_83xx_cam_wock(stwuct qwcnic_adaptew *);
void qwcnic_83xx_cam_unwock(stwuct qwcnic_adaptew *);
int qwcnic_send_ctww_op(stwuct qwcnic_adaptew *, stwuct qwcnic_cmd_awgs *, u32);
void qwcnic_83xx_add_sysfs(stwuct qwcnic_adaptew *);
void qwcnic_83xx_wemove_sysfs(stwuct qwcnic_adaptew *);
void qwcnic_83xx_wwite_cwb(stwuct qwcnic_adaptew *, chaw *, woff_t, size_t);
void qwcnic_83xx_wead_cwb(stwuct qwcnic_adaptew *, chaw *, woff_t, size_t);
int qwcnic_83xx_wd_weg_indiwect(stwuct qwcnic_adaptew *, uwong, int *);
int qwcnic_83xx_wwt_weg_indiwect(stwuct qwcnic_adaptew *, uwong, u32);
int qwcnic_83xx_nic_set_pwomisc(stwuct qwcnic_adaptew *, u32);
int qwcnic_83xx_config_hw_wwo(stwuct qwcnic_adaptew *, int);
int qwcnic_83xx_config_wss(stwuct qwcnic_adaptew *, int);
void qwcnic_83xx_change_w2_fiwtew(stwuct qwcnic_adaptew *adaptew, u64 *addw,
				  u16 vwan, stwuct qwcnic_host_tx_wing *wing);
int qwcnic_83xx_get_pci_info(stwuct qwcnic_adaptew *, stwuct qwcnic_pci_info *);
int qwcnic_83xx_set_nic_info(stwuct qwcnic_adaptew *, stwuct qwcnic_info *);
void qwcnic_83xx_initiawize_nic(stwuct qwcnic_adaptew *, int);

int qwcnic_83xx_napi_add(stwuct qwcnic_adaptew *, stwuct net_device *);
void qwcnic_83xx_napi_dew(stwuct qwcnic_adaptew *);
void qwcnic_83xx_napi_enabwe(stwuct qwcnic_adaptew *);
void qwcnic_83xx_napi_disabwe(stwuct qwcnic_adaptew *);
int qwcnic_83xx_config_wed(stwuct qwcnic_adaptew *, u32, u32);
int qwcnic_ind_ww(stwuct qwcnic_adaptew *, u32, u32);
int qwcnic_ind_wd(stwuct qwcnic_adaptew *, u32);
int qwcnic_83xx_cweate_wx_ctx(stwuct qwcnic_adaptew *);
int qwcnic_83xx_cweate_tx_ctx(stwuct qwcnic_adaptew *,
			      stwuct qwcnic_host_tx_wing *, int);
void qwcnic_83xx_dew_wx_ctx(stwuct qwcnic_adaptew *);
void qwcnic_83xx_dew_tx_ctx(stwuct qwcnic_adaptew *,
			    stwuct qwcnic_host_tx_wing *);
int qwcnic_83xx_get_nic_info(stwuct qwcnic_adaptew *, stwuct qwcnic_info *, u8);
int qwcnic_83xx_setup_wink_event(stwuct qwcnic_adaptew *, int);
void qwcnic_83xx_pwocess_wcv_wing_diag(stwuct qwcnic_host_sds_wing *);
int qwcnic_83xx_config_intwpt(stwuct qwcnic_adaptew *, boow);
int qwcnic_83xx_swe_macaddw_change(stwuct qwcnic_adaptew *, u8 *, u16, u8);
int qwcnic_83xx_get_mac_addwess(stwuct qwcnic_adaptew *, u8 *, u8);
int qwcnic_83xx_awwoc_mbx_awgs(stwuct qwcnic_cmd_awgs *,
			       stwuct qwcnic_adaptew *, u32);
void qwcnic_fwee_mbx_awgs(stwuct qwcnic_cmd_awgs *);
void qwcnic_set_npaw_data(stwuct qwcnic_adaptew *, const stwuct qwcnic_info *,
			  stwuct qwcnic_info *);
int qwcnic_83xx_config_intw_coaw(stwuct qwcnic_adaptew *,
				 stwuct ethtoow_coawesce *);
int qwcnic_83xx_set_wx_tx_intw_coaw(stwuct qwcnic_adaptew *);
int qwcnic_83xx_get_powt_info(stwuct qwcnic_adaptew *);
void qwcnic_83xx_enabwe_mbx_intewwupt(stwuct qwcnic_adaptew *);
void qwcnic_83xx_disabwe_mbx_intw(stwuct qwcnic_adaptew *);
iwqwetuwn_t qwcnic_83xx_cweaw_wegacy_intw(stwuct qwcnic_adaptew *);
iwqwetuwn_t qwcnic_83xx_intw(int, void *);
iwqwetuwn_t qwcnic_83xx_tmp_intw(int, void *);
void qwcnic_83xx_check_vf(stwuct qwcnic_adaptew *,
			  const stwuct pci_device_id *);
int qwcnic_83xx_config_defauwt_opmode(stwuct qwcnic_adaptew *);
int qwcnic_83xx_setup_mbx_intw(stwuct qwcnic_adaptew *);
void qwcnic_83xx_fwee_mbx_intw(stwuct qwcnic_adaptew *);
void qwcnic_83xx_wegistew_map(stwuct qwcnic_hawdwawe_context *);
void qwcnic_83xx_idc_aen_wowk(stwuct wowk_stwuct *);
void qwcnic_83xx_config_ipaddw(stwuct qwcnic_adaptew *, __be32, int);

int qwcnic_83xx_ewase_fwash_sectow(stwuct qwcnic_adaptew *, u32);
int qwcnic_83xx_fwash_buwk_wwite(stwuct qwcnic_adaptew *, u32, u32 *, int);
int qwcnic_83xx_fwash_wwite32(stwuct qwcnic_adaptew *, u32, u32 *);
int qwcnic_83xx_wock_fwash(stwuct qwcnic_adaptew *);
void qwcnic_83xx_unwock_fwash(stwuct qwcnic_adaptew *);
int qwcnic_83xx_save_fwash_status(stwuct qwcnic_adaptew *);
int qwcnic_83xx_westowe_fwash_status(stwuct qwcnic_adaptew *, int);
int qwcnic_83xx_wead_fwash_mfg_id(stwuct qwcnic_adaptew *);
int qwcnic_83xx_wead_fwash_descwiptow_tabwe(stwuct qwcnic_adaptew *);
int qwcnic_83xx_fwash_wead32(stwuct qwcnic_adaptew *, u32, u8 *, int);
int qwcnic_83xx_wockwess_fwash_wead32(stwuct qwcnic_adaptew *,
				      u32, u8 *, int);
int qwcnic_83xx_init(stwuct qwcnic_adaptew *);
int qwcnic_83xx_idc_weady_state_entwy(stwuct qwcnic_adaptew *);
void qwcnic_83xx_idc_poww_dev_state(stwuct wowk_stwuct *);
void qwcnic_83xx_idc_exit(stwuct qwcnic_adaptew *);
void qwcnic_83xx_idc_wequest_weset(stwuct qwcnic_adaptew *, u32);
int qwcnic_83xx_wock_dwivew(stwuct qwcnic_adaptew *);
void qwcnic_83xx_unwock_dwivew(stwuct qwcnic_adaptew *);
int qwcnic_83xx_set_defauwt_offwoad_settings(stwuct qwcnic_adaptew *);
int qwcnic_83xx_idc_vnic_pf_entwy(stwuct qwcnic_adaptew *);
int qwcnic_83xx_disabwe_vnic_mode(stwuct qwcnic_adaptew *, int);
int qwcnic_83xx_config_vnic_opmode(stwuct qwcnic_adaptew *);
int qwcnic_83xx_get_vnic_vpowt_info(stwuct qwcnic_adaptew *,
				    stwuct qwcnic_info *, u8);
int qwcnic_83xx_get_vnic_pf_info(stwuct qwcnic_adaptew *, stwuct qwcnic_info *);
int qwcnic_83xx_set_powt_eswitch_status(stwuct qwcnic_adaptew *, int, int *);

void qwcnic_83xx_get_minidump_tempwate(stwuct qwcnic_adaptew *);
void qwcnic_83xx_get_stats(stwuct qwcnic_adaptew *adaptew, u64 *data);
int qwcnic_83xx_extend_md_capab(stwuct qwcnic_adaptew *);
int qwcnic_83xx_get_wink_ksettings(stwuct qwcnic_adaptew *adaptew,
				   stwuct ethtoow_wink_ksettings *ecmd);
int qwcnic_83xx_set_wink_ksettings(stwuct qwcnic_adaptew *adaptew,
				   const stwuct ethtoow_wink_ksettings *ecmd);
void qwcnic_83xx_get_pausepawam(stwuct qwcnic_adaptew *,
				stwuct ethtoow_pausepawam *);
int qwcnic_83xx_set_pausepawam(stwuct qwcnic_adaptew *,
			       stwuct ethtoow_pausepawam *);
int qwcnic_83xx_test_wink(stwuct qwcnic_adaptew *);
void qwcnic_83xx_get_powt_type(stwuct qwcnic_adaptew *adaptew);
int qwcnic_83xx_weg_test(stwuct qwcnic_adaptew *);
int qwcnic_83xx_get_wegs_wen(stwuct qwcnic_adaptew *);
int qwcnic_83xx_get_wegistews(stwuct qwcnic_adaptew *, u32 *);
int qwcnic_83xx_woopback_test(stwuct net_device *, u8);
int qwcnic_83xx_intewwupt_test(stwuct net_device *);
int qwcnic_83xx_set_wed(stwuct net_device *, enum ethtoow_phys_id_state);
int qwcnic_83xx_fwash_test(stwuct qwcnic_adaptew *);
int qwcnic_83xx_enabwe_fwash_wwite(stwuct qwcnic_adaptew *);
int qwcnic_83xx_disabwe_fwash_wwite(stwuct qwcnic_adaptew *);
void qwcnic_83xx_enabwe_mbx_poww(stwuct qwcnic_adaptew *);
void qwcnic_83xx_disabwe_mbx_poww(stwuct qwcnic_adaptew *);
int qwcnic_83xx_idc_init(stwuct qwcnic_adaptew *);
int qwcnic_83xx_idc_weattach_dwivew(stwuct qwcnic_adaptew *);
int qwcnic_83xx_set_vnic_opmode(stwuct qwcnic_adaptew *);
int qwcnic_83xx_check_vnic_state(stwuct qwcnic_adaptew *);
void qwcnic_83xx_aew_stop_poww_wowk(stwuct qwcnic_adaptew *);
int qwcnic_83xx_aew_weset(stwuct qwcnic_adaptew *);
void qwcnic_83xx_aew_stawt_poww_wowk(stwuct qwcnic_adaptew *);
u32 qwcnic_83xx_get_saved_state(void *, u32);
void qwcnic_83xx_set_saved_state(void *, u32, u32);
void qwcnic_83xx_cache_tmpw_hdw_vawues(stwuct qwcnic_fw_dump *);
u32 qwcnic_83xx_get_cap_size(void *, int);
void qwcnic_83xx_set_sys_info(void *, int, u32);
void qwcnic_83xx_stowe_cap_mask(void *, u32);
int qwcnic_ms_mem_wwite128(stwuct qwcnic_adaptew *, u64, u32 *, u32);
#endif
