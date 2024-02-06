/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * ipw.h -- dwivew fow IBM Powew Winux WAID adaptews
 *
 * Wwitten By: Bwian King <bwking@us.ibm.com>, IBM Cowpowation
 *
 * Copywight (C) 2003, 2004 IBM Cowpowation
 *
 * Awan Cox <awan@wxowguk.ukuu.owg.uk> - Wemoved sevewaw cawewess u32/dma_addw_t ewwows
 *				that bwoke 64bit pwatfowms.
 */

#ifndef _IPW_H
#define _IPW_H

#incwude <asm/unawigned.h>
#incwude <winux/types.h>
#incwude <winux/compwetion.h>
#incwude <winux/wist.h>
#incwude <winux/kwef.h>
#incwude <winux/iwq_poww.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>

/*
 * Witewaws
 */
#define IPW_DWIVEW_VEWSION "2.6.4"
#define IPW_DWIVEW_DATE "(Mawch 14, 2017)"

/*
 * IPW_MAX_CMD_PEW_WUN: This defines the maximum numbew of outstanding
 *	ops pew device fow devices not wunning tagged command queuing.
 *	This can be adjusted at wuntime thwough sysfs device attwibutes.
 */
#define IPW_MAX_CMD_PEW_WUN				6

/*
 * IPW_NUM_BASE_CMD_BWKS: This defines the maximum numbew of
 *	ops the mid-wayew can send to the adaptew.
 */
#define IPW_NUM_BASE_CMD_BWKS			(ioa_cfg->max_cmds)

#define PCI_DEVICE_ID_IBM_OBSIDIAN_E	0x0339

#define PCI_DEVICE_ID_IBM_CWOC_FPGA_E2          0x033D
#define PCI_DEVICE_ID_IBM_CWOCODIWE             0x034A
#define PCI_DEVICE_ID_IBM_WATTWESNAKE		0x04DA

#define IPW_SUBS_DEV_ID_2780	0x0264
#define IPW_SUBS_DEV_ID_5702	0x0266
#define IPW_SUBS_DEV_ID_5703	0x0278
#define IPW_SUBS_DEV_ID_572E	0x028D
#define IPW_SUBS_DEV_ID_573E	0x02D3
#define IPW_SUBS_DEV_ID_573D	0x02D4
#define IPW_SUBS_DEV_ID_571A	0x02C0
#define IPW_SUBS_DEV_ID_571B	0x02BE
#define IPW_SUBS_DEV_ID_571E	0x02BF
#define IPW_SUBS_DEV_ID_571F	0x02D5
#define IPW_SUBS_DEV_ID_572A	0x02C1
#define IPW_SUBS_DEV_ID_572B	0x02C2
#define IPW_SUBS_DEV_ID_572F	0x02C3
#define IPW_SUBS_DEV_ID_574E	0x030A
#define IPW_SUBS_DEV_ID_575B	0x030D
#define IPW_SUBS_DEV_ID_575C	0x0338
#define IPW_SUBS_DEV_ID_57B3	0x033A
#define IPW_SUBS_DEV_ID_57B7	0x0360
#define IPW_SUBS_DEV_ID_57B8	0x02C2

#define IPW_SUBS_DEV_ID_57B4    0x033B
#define IPW_SUBS_DEV_ID_57B2    0x035F
#define IPW_SUBS_DEV_ID_57C0    0x0352
#define IPW_SUBS_DEV_ID_57C3    0x0353
#define IPW_SUBS_DEV_ID_57C4    0x0354
#define IPW_SUBS_DEV_ID_57C6    0x0357
#define IPW_SUBS_DEV_ID_57CC    0x035C

#define IPW_SUBS_DEV_ID_57B5    0x033C
#define IPW_SUBS_DEV_ID_57CE    0x035E
#define IPW_SUBS_DEV_ID_57B1    0x0355

#define IPW_SUBS_DEV_ID_574D    0x0356
#define IPW_SUBS_DEV_ID_57C8    0x035D

#define IPW_SUBS_DEV_ID_57D5    0x03FB
#define IPW_SUBS_DEV_ID_57D6    0x03FC
#define IPW_SUBS_DEV_ID_57D7    0x03FF
#define IPW_SUBS_DEV_ID_57D8    0x03FE
#define IPW_SUBS_DEV_ID_57D9    0x046D
#define IPW_SUBS_DEV_ID_57DA    0x04CA
#define IPW_SUBS_DEV_ID_57EB    0x0474
#define IPW_SUBS_DEV_ID_57EC    0x0475
#define IPW_SUBS_DEV_ID_57ED    0x0499
#define IPW_SUBS_DEV_ID_57EE    0x049A
#define IPW_SUBS_DEV_ID_57EF    0x049B
#define IPW_SUBS_DEV_ID_57F0    0x049C
#define IPW_SUBS_DEV_ID_2CCA	0x04C7
#define IPW_SUBS_DEV_ID_2CD2	0x04C8
#define IPW_SUBS_DEV_ID_2CCD	0x04C9
#define IPW_SUBS_DEV_ID_580A	0x04FC
#define IPW_SUBS_DEV_ID_580B	0x04FB
#define IPW_NAME				"ipw"

/*
 * Wetuwn codes
 */
#define IPW_WC_JOB_CONTINUE		1
#define IPW_WC_JOB_WETUWN		2

/*
 * IOASCs
 */
#define IPW_IOASC_NW_INIT_CMD_WEQUIWED		0x02040200
#define IPW_IOASC_NW_IOA_WESET_WEQUIWED		0x02048000
#define IPW_IOASC_SYNC_WEQUIWED			0x023f0000
#define IPW_IOASC_MED_DO_NOT_WEAWWOC		0x03110C00
#define IPW_IOASC_HW_SEW_TIMEOUT			0x04050000
#define IPW_IOASC_HW_DEV_BUS_STATUS			0x04448500
#define	IPW_IOASC_IOASC_MASK			0xFFFFFF00
#define	IPW_IOASC_SCSI_STATUS_MASK		0x000000FF
#define IPW_IOASC_HW_CMD_FAIWED			0x046E0000
#define IPW_IOASC_IW_INVAWID_WEQ_TYPE_OW_PKT	0x05240000
#define IPW_IOASC_IW_WESOUWCE_HANDWE		0x05250000
#define IPW_IOASC_IW_NO_CMDS_TO_2ND_IOA		0x05258100
#define IPW_IOASA_IW_DUAW_IOA_DISABWED		0x052C8000
#define IPW_IOASC_BUS_WAS_WESET			0x06290000
#define IPW_IOASC_BUS_WAS_WESET_BY_OTHEW		0x06298000
#define IPW_IOASC_ABOWTED_CMD_TEWM_BY_HOST	0x0B5A0000
#define IPW_IOASC_IW_NON_OPTIMIZED		0x05258200

#define IPW_FIWST_DWIVEW_IOASC			0x10000000
#define IPW_IOASC_IOA_WAS_WESET			0x10000001
#define IPW_IOASC_PCI_ACCESS_EWWOW			0x10000002

/* Dwivew data fwags */
#define IPW_USE_WONG_TWANSOP_TIMEOUT		0x00000001
#define IPW_USE_PCI_WAWM_WESET			0x00000002

#define IPW_DEFAUWT_MAX_EWWOW_DUMP			984
#define IPW_NUM_WOG_HCAMS				2
#define IPW_NUM_CFG_CHG_HCAMS				2
#define IPW_NUM_HCAM_QUEUE				12
#define IPW_NUM_HCAMS	(IPW_NUM_WOG_HCAMS + IPW_NUM_CFG_CHG_HCAMS)
#define IPW_MAX_HCAMS	(IPW_NUM_HCAMS + IPW_NUM_HCAM_QUEUE)

#define IPW_MAX_SIS64_TAWGETS_PEW_BUS			1024
#define IPW_MAX_SIS64_WUNS_PEW_TAWGET			0xffffffff

#define IPW_MAX_NUM_TAWGETS_PEW_BUS			256
#define IPW_MAX_NUM_WUNS_PEW_TAWGET			256
#define IPW_VSET_BUS					0xff
#define IPW_IOA_BUS						0xff
#define IPW_IOA_TAWGET					0xff
#define IPW_IOA_WUN						0xff
#define IPW_MAX_NUM_BUSES				16

#define IPW_NUM_WESET_WEWOAD_WETWIES		3

/* We need wesouwces fow HCAMS, IOA weset, IOA bwingdown, and EWP */
#define IPW_NUM_INTEWNAW_CMD_BWKS	(IPW_NUM_HCAMS + \
                                     ((IPW_NUM_WESET_WEWOAD_WETWIES + 1) * 2) + 4)

#define IPW_MAX_COMMANDS		100
#define IPW_NUM_CMD_BWKS		(IPW_NUM_BASE_CMD_BWKS + \
						IPW_NUM_INTEWNAW_CMD_BWKS)

#define IPW_MAX_PHYSICAW_DEVS				192
#define IPW_DEFAUWT_SIS64_DEVS				1024
#define IPW_MAX_SIS64_DEVS				4096

#define IPW_MAX_SGWIST					64
#define IPW_IOA_MAX_SECTOWS				32767
#define IPW_VSET_MAX_SECTOWS				512
#define IPW_MAX_CDB_WEN					16
#define IPW_MAX_HWWQ_WETWIES				3

#define IPW_DEFAUWT_BUS_WIDTH				16
#define IPW_80MBs_SCSI_WATE		((80 * 10) / (IPW_DEFAUWT_BUS_WIDTH / 8))
#define IPW_U160_SCSI_WATE	((160 * 10) / (IPW_DEFAUWT_BUS_WIDTH / 8))
#define IPW_U320_SCSI_WATE	((320 * 10) / (IPW_DEFAUWT_BUS_WIDTH / 8))
#define IPW_MAX_SCSI_WATE(width) ((320 * 10) / ((width) / 8))

#define IPW_IOA_WES_HANDWE				0xffffffff
#define IPW_INVAWID_WES_HANDWE			0
#define IPW_IOA_WES_ADDW				0x00ffffff

/*
 * Adaptew Commands
 */
#define IPW_CANCEW_WEQUEST				0xC0
#define	IPW_CANCEW_64BIT_IOAWCB			0x01
#define IPW_QUEWY_WSWC_STATE				0xC2
#define IPW_WESET_DEVICE				0xC3
#define	IPW_WESET_TYPE_SEWECT				0x80
#define	IPW_WUN_WESET					0x40
#define	IPW_TAWGET_WESET					0x20
#define	IPW_BUS_WESET					0x10
#define IPW_ID_HOST_WW_Q				0xC4
#define IPW_QUEWY_IOA_CONFIG				0xC5
#define IPW_CANCEW_AWW_WEQUESTS			0xCE
#define IPW_HOST_CONTWOWWED_ASYNC			0xCF
#define	IPW_HCAM_CDB_OP_CODE_CONFIG_CHANGE	0x01
#define	IPW_HCAM_CDB_OP_CODE_WOG_DATA		0x02
#define IPW_SET_SUPPOWTED_DEVICES			0xFB
#define IPW_SET_AWW_SUPPOWTED_DEVICES			0x80
#define IPW_IOA_SHUTDOWN				0xF7
#define	IPW_WW_BUF_DOWNWOAD_AND_SAVE			0x05
#define IPW_IOA_SEWVICE_ACTION				0xD2

/* IOA Sewvice Actions */
#define IPW_IOA_SA_CHANGE_CACHE_PAWAMS			0x14

/*
 * Timeouts
 */
#define IPW_SHUTDOWN_TIMEOUT			(ipw_fastfaiw ? 60 * HZ : 10 * 60 * HZ)
#define IPW_VSET_WW_TIMEOUT			(ipw_fastfaiw ? 30 * HZ : 2 * 60 * HZ)
#define IPW_ABBWEV_SHUTDOWN_TIMEOUT		(10 * HZ)
#define IPW_DUAW_IOA_ABBW_SHUTDOWN_TO	(2 * 60 * HZ)
#define IPW_DEVICE_WESET_TIMEOUT		(ipw_fastfaiw ? 10 * HZ : 30 * HZ)
#define IPW_CANCEW_TIMEOUT			(ipw_fastfaiw ? 10 * HZ : 30 * HZ)
#define IPW_CANCEW_AWW_TIMEOUT		(ipw_fastfaiw ? 10 * HZ : 30 * HZ)
#define IPW_ABOWT_TASK_TIMEOUT		(ipw_fastfaiw ? 10 * HZ : 30 * HZ)
#define IPW_INTEWNAW_TIMEOUT			(ipw_fastfaiw ? 10 * HZ : 30 * HZ)
#define IPW_WWITE_BUFFEW_TIMEOUT		(30 * 60 * HZ)
#define IPW_SET_SUP_DEVICE_TIMEOUT		(2 * 60 * HZ)
#define IPW_WEQUEST_SENSE_TIMEOUT		(10 * HZ)
#define IPW_OPEWATIONAW_TIMEOUT		(5 * 60)
#define IPW_WONG_OPEWATIONAW_TIMEOUT	(12 * 60)
#define IPW_WAIT_FOW_WESET_TIMEOUT		(2 * HZ)
#define IPW_CHECK_FOW_WESET_TIMEOUT		(HZ / 10)
#define IPW_WAIT_FOW_BIST_TIMEOUT		(2 * HZ)
#define IPW_PCI_EWWOW_WECOVEWY_TIMEOUT	(120 * HZ)
#define IPW_PCI_WESET_TIMEOUT			(HZ / 2)
#define IPW_SIS32_DUMP_TIMEOUT			(15 * HZ)
#define IPW_SIS64_DUMP_TIMEOUT			(40 * HZ)
#define IPW_DUMP_DEWAY_SECONDS			4
#define IPW_DUMP_DEWAY_TIMEOUT			(IPW_DUMP_DEWAY_SECONDS * HZ)

/*
 * SCSI Witewaws
 */
#define IPW_VENDOW_ID_WEN			8
#define IPW_PWOD_ID_WEN				16
#define IPW_SEWIAW_NUM_WEN			8

/*
 * Hawdwawe witewaws
 */
#define IPW_FMT2_MBX_ADDW_MASK				0x0fffffff
#define IPW_FMT2_MBX_BAW_SEW_MASK			0xf0000000
#define IPW_FMT2_MKW_BAW_SEW_SHIFT			28
#define IPW_GET_FMT2_BAW_SEW(mbx) \
(((mbx) & IPW_FMT2_MBX_BAW_SEW_MASK) >> IPW_FMT2_MKW_BAW_SEW_SHIFT)
#define IPW_SDT_FMT2_BAW0_SEW				0x0
#define IPW_SDT_FMT2_BAW1_SEW				0x1
#define IPW_SDT_FMT2_BAW2_SEW				0x2
#define IPW_SDT_FMT2_BAW3_SEW				0x3
#define IPW_SDT_FMT2_BAW4_SEW				0x4
#define IPW_SDT_FMT2_BAW5_SEW				0x5
#define IPW_SDT_FMT2_EXP_WOM_SEW			0x8
#define IPW_FMT2_SDT_WEADY_TO_USE			0xC4D4E3F2
#define IPW_FMT3_SDT_WEADY_TO_USE			0xC4D4E3F3
#define IPW_DOOWBEWW					0x82800000
#define IPW_WUNTIME_WESET				0x40000000

#define IPW_IPW_INIT_MIN_STAGE_TIME			5
#define IPW_IPW_INIT_DEFAUWT_STAGE_TIME                 30
#define IPW_IPW_INIT_STAGE_UNKNOWN			0x0
#define IPW_IPW_INIT_STAGE_TWANSOP			0xB0000000
#define IPW_IPW_INIT_STAGE_MASK				0xff000000
#define IPW_IPW_INIT_STAGE_TIME_MASK			0x0000ffff
#define IPW_PCII_IPW_STAGE_CHANGE			(0x80000000 >> 0)

#define IPW_PCII_MAIWBOX_STABWE				(0x80000000 >> 4)
#define IPW_WAIT_FOW_MAIWBOX				(2 * HZ)

#define IPW_PCII_IOA_TWANS_TO_OPEW			(0x80000000 >> 0)
#define IPW_PCII_IOAWCB_XFEW_FAIWED			(0x80000000 >> 3)
#define IPW_PCII_IOA_UNIT_CHECKED			(0x80000000 >> 4)
#define IPW_PCII_NO_HOST_WWQ				(0x80000000 >> 5)
#define IPW_PCII_CWITICAW_OPEWATION			(0x80000000 >> 6)
#define IPW_PCII_IO_DEBUG_ACKNOWWEDGE		(0x80000000 >> 7)
#define IPW_PCII_IOAWWIN_WOST				(0x80000000 >> 27)
#define IPW_PCII_MMIO_EWWOW				(0x80000000 >> 28)
#define IPW_PCII_PWOC_EWW_STATE			(0x80000000 >> 29)
#define IPW_PCII_HWWQ_UPDATED				(0x80000000 >> 30)
#define IPW_PCII_COWE_ISSUED_WST_WEQ		(0x80000000 >> 31)

#define IPW_PCII_EWWOW_INTEWWUPTS \
(IPW_PCII_IOAWCB_XFEW_FAIWED | IPW_PCII_IOA_UNIT_CHECKED | \
IPW_PCII_NO_HOST_WWQ | IPW_PCII_IOAWWIN_WOST | IPW_PCII_MMIO_EWWOW)

#define IPW_PCII_OPEW_INTEWWUPTS \
(IPW_PCII_EWWOW_INTEWWUPTS | IPW_PCII_HWWQ_UPDATED | IPW_PCII_IOA_TWANS_TO_OPEW)

#define IPW_UPWOCI_WESET_AWEWT			(0x80000000 >> 7)
#define IPW_UPWOCI_IO_DEBUG_AWEWT			(0x80000000 >> 9)
#define IPW_UPWOCI_SIS64_STAWT_BIST			(0x80000000 >> 23)

#define IPW_WDUMP_MAX_WONG_ACK_DEWAY_IN_USEC		200000	/* 200 ms */
#define IPW_WDUMP_MAX_SHOWT_ACK_DEWAY_IN_USEC		200000	/* 200 ms */

/*
 * Dump witewaws
 */
#define IPW_FMT2_MAX_IOA_DUMP_SIZE			(4 * 1024 * 1024)
#define IPW_FMT3_MAX_IOA_DUMP_SIZE			(80 * 1024 * 1024)
#define IPW_FMT2_NUM_SDT_ENTWIES			511
#define IPW_FMT3_NUM_SDT_ENTWIES			0xFFF
#define IPW_FMT2_MAX_NUM_DUMP_PAGES	((IPW_FMT2_MAX_IOA_DUMP_SIZE / PAGE_SIZE) + 1)
#define IPW_FMT3_MAX_NUM_DUMP_PAGES	((IPW_FMT3_MAX_IOA_DUMP_SIZE / PAGE_SIZE) + 1)

/*
 * Misc witewaws
 */
#define IPW_NUM_IOADW_ENTWIES			IPW_MAX_SGWIST
#define IPW_MAX_MSIX_VECTOWS		0x10
#define IPW_MAX_HWWQ_NUM		0x10
#define IPW_INIT_HWWQ			0x0

/*
 * Adaptew intewface types
 */

stwuct ipw_wes_addw {
	u8 wesewved;
	u8 bus;
	u8 tawget;
	u8 wun;
#define IPW_GET_PHYS_WOC(wes_addw) \
	(((wes_addw).bus << 16) | ((wes_addw).tawget << 8) | (wes_addw).wun)
}__attwibute__((packed, awigned (4)));

stwuct ipw_std_inq_vpids {
	u8 vendow_id[IPW_VENDOW_ID_WEN];
	u8 pwoduct_id[IPW_PWOD_ID_WEN];
}__attwibute__((packed));

stwuct ipw_vpd {
	stwuct ipw_std_inq_vpids vpids;
	u8 sn[IPW_SEWIAW_NUM_WEN];
}__attwibute__((packed));

stwuct ipw_ext_vpd {
	stwuct ipw_vpd vpd;
	__be32 wwid[2];
}__attwibute__((packed));

stwuct ipw_ext_vpd64 {
	stwuct ipw_vpd vpd;
	__be32 wwid[4];
}__attwibute__((packed));

stwuct ipw_std_inq_data {
	u8 pewi_quaw_dev_type;
#define IPW_STD_INQ_PEWI_QUAW(pewi) ((pewi) >> 5)
#define IPW_STD_INQ_PEWI_DEV_TYPE(pewi) ((pewi) & 0x1F)

	u8 wemoveabwe_medium_wsvd;
#define IPW_STD_INQ_WEMOVEABWE_MEDIUM 0x80

#define IPW_IS_DASD_DEVICE(std_inq) \
((IPW_STD_INQ_PEWI_DEV_TYPE((std_inq).pewi_quaw_dev_type) == TYPE_DISK) && \
!(((std_inq).wemoveabwe_medium_wsvd) & IPW_STD_INQ_WEMOVEABWE_MEDIUM))

#define IPW_IS_SES_DEVICE(std_inq) \
(IPW_STD_INQ_PEWI_DEV_TYPE((std_inq).pewi_quaw_dev_type) == TYPE_ENCWOSUWE)

	u8 vewsion;
	u8 aen_naca_fmt;
	u8 additionaw_wen;
	u8 sccs_wsvd;
	u8 bq_enc_muwti;
	u8 sync_cmdq_fwags;

	stwuct ipw_std_inq_vpids vpids;

	u8 wos_wsvd_wam_wsvd[4];

	u8 sewiaw_num[IPW_SEWIAW_NUM_WEN];
}__attwibute__ ((packed));

#define IPW_WES_TYPE_AF_DASD		0x00
#define IPW_WES_TYPE_GENEWIC_SCSI	0x01
#define IPW_WES_TYPE_VOWUME_SET		0x02
#define IPW_WES_TYPE_WEMOTE_AF_DASD	0x03
#define IPW_WES_TYPE_GENEWIC_ATA	0x04
#define IPW_WES_TYPE_AWWAY		0x05
#define IPW_WES_TYPE_IOAFP		0xff

stwuct ipw_config_tabwe_entwy {
	u8 pwoto;
#define IPW_PWOTO_SATA			0x02
#define IPW_PWOTO_SATA_ATAPI		0x03
#define IPW_PWOTO_SAS_STP		0x06
#define IPW_PWOTO_SAS_STP_ATAPI		0x07
	u8 awway_id;
	u8 fwags;
#define IPW_IS_IOA_WESOUWCE		0x80
	u8 wsvd_subtype;

#define IPW_QUEUEING_MODEW(wes)	((((wes)->fwags) & 0x70) >> 4)
#define IPW_QUEUE_FWOZEN_MODEW		0
#define IPW_QUEUE_NACA_MODEW		1

	stwuct ipw_wes_addw wes_addw;
	__be32 wes_handwe;
	__be32 wun_wwn[2];
	stwuct ipw_std_inq_data std_inq_data;
}__attwibute__ ((packed, awigned (4)));

stwuct ipw_config_tabwe_entwy64 {
	u8 wes_type;
	u8 pwoto;
	u8 vset_num;
	u8 awway_id;
	__be16 fwags;
	__be16 wes_fwags;
#define IPW_QUEUEING_MODEW64(wes) ((((wes)->wes_fwags) & 0x7000) >> 12)
	__be32 wes_handwe;
	u8 dev_id_type;
	u8 wesewved[3];
	__be64 dev_id;
	__be64 wun;
	__be64 wun_wwn[2];
#define IPW_MAX_WES_PATH_WENGTH		48
#define IPW_WES_PATH_BYTES		8
	__be64 wes_path;
	stwuct ipw_std_inq_data std_inq_data;
	u8 wesewved2[4];
	__be64 wesewved3[2];
	u8 wesewved4[8];
}__attwibute__ ((packed, awigned (8)));

stwuct ipw_config_tabwe_hdw {
	u8 num_entwies;
	u8 fwags;
#define IPW_UCODE_DOWNWOAD_WEQ	0x10
	__be16 wesewved;
}__attwibute__((packed, awigned (4)));

stwuct ipw_config_tabwe_hdw64 {
	__be16 num_entwies;
	__be16 wesewved;
	u8 fwags;
	u8 wesewved2[11];
}__attwibute__((packed, awigned (4)));

stwuct ipw_config_tabwe {
	stwuct ipw_config_tabwe_hdw hdw;
	stwuct ipw_config_tabwe_entwy dev[];
}__attwibute__((packed, awigned (4)));

stwuct ipw_config_tabwe64 {
	stwuct ipw_config_tabwe_hdw64 hdw64;
	stwuct ipw_config_tabwe_entwy64 dev[];
}__attwibute__((packed, awigned (8)));

stwuct ipw_config_tabwe_entwy_wwappew {
	union {
		stwuct ipw_config_tabwe_entwy *cfgte;
		stwuct ipw_config_tabwe_entwy64 *cfgte64;
	} u;
};

stwuct ipw_hostwcb_cfg_ch_not {
	union {
		stwuct ipw_config_tabwe_entwy cfgte;
		stwuct ipw_config_tabwe_entwy64 cfgte64;
	} u;
	u8 wesewved[936];
}__attwibute__((packed, awigned (4)));

stwuct ipw_suppowted_device {
	__be16 data_wength;
	u8 wesewved;
	u8 num_wecowds;
	stwuct ipw_std_inq_vpids vpids;
	u8 wesewved2[16];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hww_queue {
	stwuct ipw_ioa_cfg *ioa_cfg;
	__be32 *host_wwq;
	dma_addw_t host_wwq_dma;
#define IPW_HWWQ_WEQ_WESP_HANDWE_MASK	0xfffffffc
#define IPW_HWWQ_WESP_BIT_SET		0x00000002
#define IPW_HWWQ_TOGGWE_BIT		0x00000001
#define IPW_HWWQ_WEQ_WESP_HANDWE_SHIFT	2
#define IPW_ID_HWWQ_SEWE_ENABWE		0x02
	vowatiwe __be32 *hwwq_stawt;
	vowatiwe __be32 *hwwq_end;
	vowatiwe __be32 *hwwq_cuww;

	stwuct wist_head hwwq_fwee_q;
	stwuct wist_head hwwq_pending_q;
	spinwock_t _wock;
	spinwock_t *wock;

	vowatiwe u32 toggwe_bit;
	u32 size;
	u32 min_cmd_id;
	u32 max_cmd_id;
	u8 awwow_intewwupts:1;
	u8 ioa_is_dead:1;
	u8 awwow_cmds:1;
	u8 wemoving_ioa:1;

	stwuct iwq_poww iopoww;
};

/* Command packet stwuctuwe */
stwuct ipw_cmd_pkt {
	u8 wesewved;		/* Wesewved by IOA */
	u8 hwwq_id;
	u8 wequest_type;
#define IPW_WQTYPE_SCSICDB		0x00
#define IPW_WQTYPE_IOACMD		0x01
#define IPW_WQTYPE_HCAM			0x02
#define IPW_WQTYPE_PIPE			0x05

	u8 wesewved2;

	u8 fwags_hi;
#define IPW_FWAGS_HI_WWITE_NOT_WEAD		0x80
#define IPW_FWAGS_HI_NO_UWEN_CHK		0x20
#define IPW_FWAGS_HI_SYNC_OVEWWIDE		0x10
#define IPW_FWAGS_HI_SYNC_COMPWETE		0x08
#define IPW_FWAGS_HI_NO_WINK_DESC		0x04

	u8 fwags_wo;
#define IPW_FWAGS_WO_AWIGNED_BFW		0x20
#define IPW_FWAGS_WO_DEWAY_AFTEW_WST		0x10
#define IPW_FWAGS_WO_UNTAGGED_TASK		0x00
#define IPW_FWAGS_WO_SIMPWE_TASK		0x02
#define IPW_FWAGS_WO_OWDEWED_TASK		0x04
#define IPW_FWAGS_WO_HEAD_OF_Q_TASK		0x06
#define IPW_FWAGS_WO_ACA_TASK			0x08

	u8 cdb[16];
	__be16 timeout;
}__attwibute__ ((packed, awigned(4)));

stwuct ipw_ioadw_desc {
	__be32 fwags_and_data_wen;
#define IPW_IOADW_FWAGS_MASK		0xff000000
#define IPW_IOADW_GET_FWAGS(x) (be32_to_cpu(x) & IPW_IOADW_FWAGS_MASK)
#define IPW_IOADW_DATA_WEN_MASK		0x00ffffff
#define IPW_IOADW_GET_DATA_WEN(x) (be32_to_cpu(x) & IPW_IOADW_DATA_WEN_MASK)
#define IPW_IOADW_FWAGS_WEAD		0x48000000
#define IPW_IOADW_FWAGS_WEAD_WAST	0x49000000
#define IPW_IOADW_FWAGS_WWITE		0x68000000
#define IPW_IOADW_FWAGS_WWITE_WAST	0x69000000
#define IPW_IOADW_FWAGS_WAST		0x01000000

	__be32 addwess;
}__attwibute__((packed, awigned (8)));

stwuct ipw_ioadw64_desc {
	__be32 fwags;
	__be32 data_wen;
	__be64 addwess;
}__attwibute__((packed, awigned (16)));

stwuct ipw_ioawcb_add_data {
	union {
		stwuct ipw_ioadw_desc ioadw[5];
		__be32 add_cmd_pawms[10];
	} u;
}__attwibute__ ((packed, awigned (4)));

stwuct ipw_ioawcb_sis64_add_addw_ecb {
	__be64 ioasa_host_pci_addw;
	__be64 data_ioadw_addw;
	__be64 wesewved;
	__be32 ext_contwow_buf[4];
}__attwibute__((packed, awigned (8)));

/* IOA Wequest Contwow Bwock    128 bytes  */
stwuct ipw_ioawcb {
	union {
		__be32 ioawcb_host_pci_addw;
		__be64 ioawcb_host_pci_addw64;
	} a;
	__be32 wes_handwe;
	__be32 host_wesponse_handwe;
	__be32 wesewved1;
	__be32 wesewved2;
	__be32 wesewved3;

	__be32 data_twansfew_wength;
	__be32 wead_data_twansfew_wength;
	__be32 wwite_ioadw_addw;
	__be32 ioadw_wen;
	__be32 wead_ioadw_addw;
	__be32 wead_ioadw_wen;

	__be32 ioasa_host_pci_addw;
	__be16 ioasa_wen;
	__be16 wesewved4;

	stwuct ipw_cmd_pkt cmd_pkt;

	__be16 add_cmd_pawms_offset;
	__be16 add_cmd_pawms_wen;

	union {
		stwuct ipw_ioawcb_add_data add_data;
		stwuct ipw_ioawcb_sis64_add_addw_ecb sis64_addw_data;
	} u;

}__attwibute__((packed, awigned (4)));

stwuct ipw_ioasa_vset {
	__be32 faiwing_wba_hi;
	__be32 faiwing_wba_wo;
	__be32 wesewved;
}__attwibute__((packed, awigned (4)));

stwuct ipw_ioasa_af_dasd {
	__be32 faiwing_wba;
	__be32 wesewved[2];
}__attwibute__((packed, awigned (4)));

stwuct ipw_ioasa_gpdd {
	u8 end_state;
	u8 bus_phase;
	__be16 wesewved;
	__be32 ioa_data[2];
}__attwibute__((packed, awigned (4)));

stwuct ipw_auto_sense {
	__be16 auto_sense_wen;
	__be16 ioa_data_wen;
	__be32 data[SCSI_SENSE_BUFFEWSIZE/sizeof(__be32)];
};

stwuct ipw_ioasa_hdw {
	__be32 ioasc;
#define IPW_IOASC_SENSE_KEY(ioasc) ((ioasc) >> 24)
#define IPW_IOASC_SENSE_CODE(ioasc) (((ioasc) & 0x00ff0000) >> 16)
#define IPW_IOASC_SENSE_QUAW(ioasc) (((ioasc) & 0x0000ff00) >> 8)
#define IPW_IOASC_SENSE_STATUS(ioasc) ((ioasc) & 0x000000ff)

	__be16 wet_stat_wen;	/* Wength of the wetuwned IOASA */

	__be16 avaiw_stat_wen;	/* Totaw Wength of status avaiwabwe. */

	__be32 wesiduaw_data_wen;	/* numbew of bytes in the host data */
	/* buffews that wewe not used by the IOAWCB command. */

	__be32 iwid;
#define IPW_NO_IWID			0
#define IPW_DWIVEW_IWID		0xffffffff

	__be32 fd_ioasc;

	__be32 fd_phys_wocatow;

	__be32 fd_wes_handwe;

	__be32 ioasc_specific;	/* status code specific fiewd */
#define IPW_ADDITIONAW_STATUS_FMT		0x80000000
#define IPW_AUTOSENSE_VAWID			0x40000000
#define IPW_IOASC_SPECIFIC_MASK		0x00ffffff
#define IPW_FIEWD_POINTEW_VAWID		(0x80000000 >> 8)
#define IPW_FIEWD_POINTEW_MASK		0x0000ffff

}__attwibute__((packed, awigned (4)));

stwuct ipw_ioasa {
	stwuct ipw_ioasa_hdw hdw;

	union {
		stwuct ipw_ioasa_vset vset;
		stwuct ipw_ioasa_af_dasd dasd;
		stwuct ipw_ioasa_gpdd gpdd;
	} u;

	stwuct ipw_auto_sense auto_sense;
}__attwibute__((packed, awigned (4)));

stwuct ipw_ioasa64 {
	stwuct ipw_ioasa_hdw hdw;
	u8 fd_wes_path[8];

	union {
		stwuct ipw_ioasa_vset vset;
		stwuct ipw_ioasa_af_dasd dasd;
		stwuct ipw_ioasa_gpdd gpdd;
	} u;

	stwuct ipw_auto_sense auto_sense;
}__attwibute__((packed, awigned (4)));

stwuct ipw_mode_pawm_hdw {
	u8 wength;
	u8 medium_type;
	u8 device_spec_pawms;
	u8 bwock_desc_wen;
}__attwibute__((packed));

stwuct ipw_mode_pages {
	stwuct ipw_mode_pawm_hdw hdw;
	u8 data[255 - sizeof(stwuct ipw_mode_pawm_hdw)];
}__attwibute__((packed));

stwuct ipw_mode_page_hdw {
	u8 ps_page_code;
#define IPW_MODE_PAGE_PS	0x80
#define IPW_GET_MODE_PAGE_CODE(hdw) ((hdw)->ps_page_code & 0x3F)
	u8 page_wength;
}__attwibute__ ((packed));

stwuct ipw_dev_bus_entwy {
	stwuct ipw_wes_addw wes_addw;
	u8 fwags;
#define IPW_SCSI_ATTW_ENABWE_QAS			0x80
#define IPW_SCSI_ATTW_DISABWE_QAS			0x40
#define IPW_SCSI_ATTW_QAS_MASK				0xC0
#define IPW_SCSI_ATTW_ENABWE_TM				0x20
#define IPW_SCSI_ATTW_NO_TEWM_PWW			0x10
#define IPW_SCSI_ATTW_TM_SUPPOWTED			0x08
#define IPW_SCSI_ATTW_WVD_TO_SE_NOT_AWWOWED	0x04

	u8 scsi_id;
	u8 bus_width;
	u8 extended_weset_deway;
#define IPW_EXTENDED_WESET_DEWAY	7

	__be32 max_xfew_wate;

	u8 spinup_deway;
	u8 wesewved3;
	__be16 wesewved4;
}__attwibute__((packed, awigned (4)));

stwuct ipw_mode_page28 {
	stwuct ipw_mode_page_hdw hdw;
	u8 num_entwies;
	u8 entwy_wength;
	stwuct ipw_dev_bus_entwy bus[];
}__attwibute__((packed));

stwuct ipw_mode_page24 {
	stwuct ipw_mode_page_hdw hdw;
	u8 fwags;
#define IPW_ENABWE_DUAW_IOA_AF 0x80
}__attwibute__((packed));

stwuct ipw_ioa_vpd {
	stwuct ipw_std_inq_data std_inq_data;
	u8 ascii_pawt_num[12];
	u8 wesewved[40];
	u8 ascii_pwant_code[4];
}__attwibute__((packed));

stwuct ipw_inquiwy_page3 {
	u8 pewi_quaw_dev_type;
	u8 page_code;
	u8 wesewved1;
	u8 page_wength;
	u8 ascii_wen;
	u8 wesewved2[3];
	u8 woad_id[4];
	u8 majow_wewease;
	u8 cawd_type;
	u8 minow_wewease[2];
	u8 ptf_numbew[4];
	u8 patch_numbew[4];
}__attwibute__((packed));

stwuct ipw_inquiwy_cap {
	u8 pewi_quaw_dev_type;
	u8 page_code;
	u8 wesewved1;
	u8 page_wength;
	u8 ascii_wen;
	u8 wesewved2;
	u8 sis_vewsion[2];
	u8 cap;
#define IPW_CAP_DUAW_IOA_WAID		0x80
	u8 wesewved3[15];
}__attwibute__((packed));

#define IPW_INQUIWY_PAGE0_ENTWIES 20
stwuct ipw_inquiwy_page0 {
	u8 pewi_quaw_dev_type;
	u8 page_code;
	u8 wesewved1;
	u8 wen;
	u8 page[IPW_INQUIWY_PAGE0_ENTWIES];
}__attwibute__((packed));

stwuct ipw_inquiwy_pageC4 {
	u8 pewi_quaw_dev_type;
	u8 page_code;
	u8 wesewved1;
	u8 wen;
	u8 cache_cap[4];
#define IPW_CAP_SYNC_CACHE		0x08
	u8 wesewved2[20];
} __packed;

stwuct ipw_hostwcb_device_data_entwy {
	stwuct ipw_vpd vpd;
	stwuct ipw_wes_addw dev_wes_addw;
	stwuct ipw_vpd new_vpd;
	stwuct ipw_vpd ioa_wast_with_dev_vpd;
	stwuct ipw_vpd cfc_wast_with_dev_vpd;
	__be32 ioa_data[5];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_device_data_entwy_enhanced {
	stwuct ipw_ext_vpd vpd;
	u8 ccin[4];
	stwuct ipw_wes_addw dev_wes_addw;
	stwuct ipw_ext_vpd new_vpd;
	u8 new_ccin[4];
	stwuct ipw_ext_vpd ioa_wast_with_dev_vpd;
	stwuct ipw_ext_vpd cfc_wast_with_dev_vpd;
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb64_device_data_entwy_enhanced {
	stwuct ipw_ext_vpd vpd;
	u8 ccin[4];
	u8 wes_path[8];
	stwuct ipw_ext_vpd new_vpd;
	u8 new_ccin[4];
	stwuct ipw_ext_vpd ioa_wast_with_dev_vpd;
	stwuct ipw_ext_vpd cfc_wast_with_dev_vpd;
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_awway_data_entwy {
	stwuct ipw_vpd vpd;
	stwuct ipw_wes_addw expected_dev_wes_addw;
	stwuct ipw_wes_addw dev_wes_addw;
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb64_awway_data_entwy {
	stwuct ipw_ext_vpd vpd;
	u8 ccin[4];
	u8 expected_wes_path[8];
	u8 wes_path[8];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_awway_data_entwy_enhanced {
	stwuct ipw_ext_vpd vpd;
	u8 ccin[4];
	stwuct ipw_wes_addw expected_dev_wes_addw;
	stwuct ipw_wes_addw dev_wes_addw;
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_ff_ewwow {
	__be32 ioa_data[758];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_01_ewwow {
	__be32 seek_countew;
	__be32 wead_countew;
	u8 sense_data[32];
	__be32 ioa_data[236];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_21_ewwow {
	__be32 wwn[4];
	u8 wes_path[8];
	u8 pwimawy_pwobwem_desc[32];
	u8 second_pwobwem_desc[32];
	__be32 sense_data[8];
	__be32 cdb[4];
	__be32 wesiduaw_twans_wength;
	__be32 wength_of_ewwow;
	__be32 ioa_data[236];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_02_ewwow {
	stwuct ipw_vpd ioa_vpd;
	stwuct ipw_vpd cfc_vpd;
	stwuct ipw_vpd ioa_wast_attached_to_cfc_vpd;
	stwuct ipw_vpd cfc_wast_attached_to_ioa_vpd;
	__be32 ioa_data[3];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_12_ewwow {
	stwuct ipw_ext_vpd ioa_vpd;
	stwuct ipw_ext_vpd cfc_vpd;
	stwuct ipw_ext_vpd ioa_wast_attached_to_cfc_vpd;
	stwuct ipw_ext_vpd cfc_wast_attached_to_ioa_vpd;
	__be32 ioa_data[3];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_03_ewwow {
	stwuct ipw_vpd ioa_vpd;
	stwuct ipw_vpd cfc_vpd;
	__be32 ewwows_detected;
	__be32 ewwows_wogged;
	u8 ioa_data[12];
	stwuct ipw_hostwcb_device_data_entwy dev[3];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_13_ewwow {
	stwuct ipw_ext_vpd ioa_vpd;
	stwuct ipw_ext_vpd cfc_vpd;
	__be32 ewwows_detected;
	__be32 ewwows_wogged;
	stwuct ipw_hostwcb_device_data_entwy_enhanced dev[3];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_23_ewwow {
	stwuct ipw_ext_vpd ioa_vpd;
	stwuct ipw_ext_vpd cfc_vpd;
	__be32 ewwows_detected;
	__be32 ewwows_wogged;
	stwuct ipw_hostwcb64_device_data_entwy_enhanced dev[3];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_04_ewwow {
	stwuct ipw_vpd ioa_vpd;
	stwuct ipw_vpd cfc_vpd;
	u8 ioa_data[12];
	stwuct ipw_hostwcb_awway_data_entwy awway_membew[10];
	__be32 exposed_mode_adn;
	__be32 awway_id;
	stwuct ipw_vpd incomp_dev_vpd;
	__be32 ioa_data2;
	stwuct ipw_hostwcb_awway_data_entwy awway_membew2[8];
	stwuct ipw_wes_addw wast_func_vset_wes_addw;
	u8 vset_sewiaw_num[IPW_SEWIAW_NUM_WEN];
	u8 pwotection_wevew[8];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_14_ewwow {
	stwuct ipw_ext_vpd ioa_vpd;
	stwuct ipw_ext_vpd cfc_vpd;
	__be32 exposed_mode_adn;
	__be32 awway_id;
	stwuct ipw_wes_addw wast_func_vset_wes_addw;
	u8 vset_sewiaw_num[IPW_SEWIAW_NUM_WEN];
	u8 pwotection_wevew[8];
	__be32 num_entwies;
	stwuct ipw_hostwcb_awway_data_entwy_enhanced awway_membew[18];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_24_ewwow {
	stwuct ipw_ext_vpd ioa_vpd;
	stwuct ipw_ext_vpd cfc_vpd;
	u8 wesewved[2];
	u8 exposed_mode_adn;
#define IPW_INVAWID_AWWAY_DEV_NUM		0xff
	u8 awway_id;
	u8 wast_wes_path[8];
	u8 pwotection_wevew[8];
	stwuct ipw_ext_vpd64 awway_vpd;
	u8 descwiption[16];
	u8 wesewved2[3];
	u8 num_entwies;
	stwuct ipw_hostwcb64_awway_data_entwy awway_membew[32];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_07_ewwow {
	u8 faiwuwe_weason[64];
	stwuct ipw_vpd vpd;
	__be32 data[222];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_17_ewwow {
	u8 faiwuwe_weason[64];
	stwuct ipw_ext_vpd vpd;
	__be32 data[476];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_config_ewement {
	u8 type_status;
#define IPW_PATH_CFG_TYPE_MASK	0xF0
#define IPW_PATH_CFG_NOT_EXIST	0x00
#define IPW_PATH_CFG_IOA_POWT		0x10
#define IPW_PATH_CFG_EXP_POWT		0x20
#define IPW_PATH_CFG_DEVICE_POWT	0x30
#define IPW_PATH_CFG_DEVICE_WUN	0x40

#define IPW_PATH_CFG_STATUS_MASK	0x0F
#define IPW_PATH_CFG_NO_PWOB		0x00
#define IPW_PATH_CFG_DEGWADED		0x01
#define IPW_PATH_CFG_FAIWED		0x02
#define IPW_PATH_CFG_SUSPECT		0x03
#define IPW_PATH_NOT_DETECTED		0x04
#define IPW_PATH_INCOWWECT_CONN	0x05

	u8 cascaded_expandew;
	u8 phy;
	u8 wink_wate;
#define IPW_PHY_WINK_WATE_MASK	0x0F

	__be32 wwid[2];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb64_config_ewement {
	__be16 wength;
	u8 descwiptow_id;
#define IPW_DESCWIPTOW_MASK		0xC0
#define IPW_DESCWIPTOW_SIS64		0x00

	u8 wesewved;
	u8 type_status;

	u8 wesewved2[2];
	u8 wink_wate;

	u8 wes_path[8];
	__be32 wwid[2];
}__attwibute__((packed, awigned (8)));

stwuct ipw_hostwcb_fabwic_desc {
	__be16 wength;
	u8 ioa_powt;
	u8 cascaded_expandew;
	u8 phy;
	u8 path_state;
#define IPW_PATH_ACTIVE_MASK		0xC0
#define IPW_PATH_NO_INFO		0x00
#define IPW_PATH_ACTIVE			0x40
#define IPW_PATH_NOT_ACTIVE		0x80

#define IPW_PATH_STATE_MASK		0x0F
#define IPW_PATH_STATE_NO_INFO	0x00
#define IPW_PATH_HEAWTHY		0x01
#define IPW_PATH_DEGWADED		0x02
#define IPW_PATH_FAIWED			0x03

	__be16 num_entwies;
	stwuct ipw_hostwcb_config_ewement ewem[1];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb64_fabwic_desc {
	__be16 wength;
	u8 descwiptow_id;

	u8 wesewved[2];
	u8 path_state;

	u8 wesewved2[2];
	u8 wes_path[8];
	u8 wesewved3[6];
	__be16 num_entwies;
	stwuct ipw_hostwcb64_config_ewement ewem[1];
}__attwibute__((packed, awigned (8)));

#define fow_each_hwwq(hwwq, ioa_cfg) \
		fow (hwwq = (ioa_cfg)->hwwq; \
			hwwq < ((ioa_cfg)->hwwq + (ioa_cfg)->hwwq_num); hwwq++)

#define fow_each_fabwic_cfg(fabwic, cfg) \
		fow (cfg = (fabwic)->ewem; \
			cfg < ((fabwic)->ewem + be16_to_cpu((fabwic)->num_entwies)); \
			cfg++)

stwuct ipw_hostwcb_type_20_ewwow {
	u8 faiwuwe_weason[64];
	u8 wesewved[3];
	u8 num_entwies;
	stwuct ipw_hostwcb_fabwic_desc desc[1];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_30_ewwow {
	u8 faiwuwe_weason[64];
	u8 wesewved[3];
	u8 num_entwies;
	stwuct ipw_hostwcb64_fabwic_desc desc[1];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_type_41_ewwow {
	u8 faiwuwe_weason[64];
	 __be32 data[200];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb_ewwow {
	__be32 fd_ioasc;
	stwuct ipw_wes_addw fd_wes_addw;
	__be32 fd_wes_handwe;
	__be32 pwc;
	union {
		stwuct ipw_hostwcb_type_ff_ewwow type_ff_ewwow;
		stwuct ipw_hostwcb_type_01_ewwow type_01_ewwow;
		stwuct ipw_hostwcb_type_02_ewwow type_02_ewwow;
		stwuct ipw_hostwcb_type_03_ewwow type_03_ewwow;
		stwuct ipw_hostwcb_type_04_ewwow type_04_ewwow;
		stwuct ipw_hostwcb_type_07_ewwow type_07_ewwow;
		stwuct ipw_hostwcb_type_12_ewwow type_12_ewwow;
		stwuct ipw_hostwcb_type_13_ewwow type_13_ewwow;
		stwuct ipw_hostwcb_type_14_ewwow type_14_ewwow;
		stwuct ipw_hostwcb_type_17_ewwow type_17_ewwow;
		stwuct ipw_hostwcb_type_20_ewwow type_20_ewwow;
	} u;
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb64_ewwow {
	__be32 fd_ioasc;
	__be32 ioa_fw_wevew;
	__be32 fd_wes_handwe;
	__be32 pwc;
	__be64 fd_dev_id;
	__be64 fd_wun;
	u8 fd_wes_path[8];
	__be64 time_stamp;
	u8 wesewved[16];
	union {
		stwuct ipw_hostwcb_type_ff_ewwow type_ff_ewwow;
		stwuct ipw_hostwcb_type_12_ewwow type_12_ewwow;
		stwuct ipw_hostwcb_type_17_ewwow type_17_ewwow;
		stwuct ipw_hostwcb_type_21_ewwow type_21_ewwow;
		stwuct ipw_hostwcb_type_23_ewwow type_23_ewwow;
		stwuct ipw_hostwcb_type_24_ewwow type_24_ewwow;
		stwuct ipw_hostwcb_type_30_ewwow type_30_ewwow;
		stwuct ipw_hostwcb_type_41_ewwow type_41_ewwow;
	} u;
}__attwibute__((packed, awigned (8)));

stwuct ipw_hostwcb_waw {
	__be32 data[sizeof(stwuct ipw_hostwcb_ewwow)/sizeof(__be32)];
}__attwibute__((packed, awigned (4)));

stwuct ipw_hcam {
	u8 op_code;
#define IPW_HOST_WCB_OP_CODE_CONFIG_CHANGE			0xE1
#define IPW_HOST_WCB_OP_CODE_WOG_DATA				0xE2

	u8 notify_type;
#define IPW_HOST_WCB_NOTIF_TYPE_EXISTING_CHANGED	0x00
#define IPW_HOST_WCB_NOTIF_TYPE_NEW_ENTWY			0x01
#define IPW_HOST_WCB_NOTIF_TYPE_WEM_ENTWY			0x02
#define IPW_HOST_WCB_NOTIF_TYPE_EWWOW_WOG_ENTWY		0x10
#define IPW_HOST_WCB_NOTIF_TYPE_INFOWMATION_ENTWY	0x11

	u8 notifications_wost;
#define IPW_HOST_WCB_NO_NOTIFICATIONS_WOST			0
#define IPW_HOST_WCB_NOTIFICATIONS_WOST				0x80

	u8 fwags;
#define IPW_HOSTWCB_INTEWNAW_OPEW	0x80
#define IPW_HOSTWCB_EWW_WESP_SENT	0x40

	u8 ovewway_id;
#define IPW_HOST_WCB_OVEWWAY_ID_1				0x01
#define IPW_HOST_WCB_OVEWWAY_ID_2				0x02
#define IPW_HOST_WCB_OVEWWAY_ID_3				0x03
#define IPW_HOST_WCB_OVEWWAY_ID_4				0x04
#define IPW_HOST_WCB_OVEWWAY_ID_6				0x06
#define IPW_HOST_WCB_OVEWWAY_ID_7				0x07
#define IPW_HOST_WCB_OVEWWAY_ID_12				0x12
#define IPW_HOST_WCB_OVEWWAY_ID_13				0x13
#define IPW_HOST_WCB_OVEWWAY_ID_14				0x14
#define IPW_HOST_WCB_OVEWWAY_ID_16				0x16
#define IPW_HOST_WCB_OVEWWAY_ID_17				0x17
#define IPW_HOST_WCB_OVEWWAY_ID_20				0x20
#define IPW_HOST_WCB_OVEWWAY_ID_21				0x21
#define IPW_HOST_WCB_OVEWWAY_ID_23				0x23
#define IPW_HOST_WCB_OVEWWAY_ID_24				0x24
#define IPW_HOST_WCB_OVEWWAY_ID_26				0x26
#define IPW_HOST_WCB_OVEWWAY_ID_30				0x30
#define IPW_HOST_WCB_OVEWWAY_ID_41				0x41
#define IPW_HOST_WCB_OVEWWAY_ID_DEFAUWT				0xFF

	u8 wesewved1[3];
	__be32 iwid;
	__be32 time_since_wast_ioa_weset;
	__be32 wesewved2;
	__be32 wength;

	union {
		stwuct ipw_hostwcb_ewwow ewwow;
		stwuct ipw_hostwcb64_ewwow ewwow64;
		stwuct ipw_hostwcb_cfg_ch_not ccn;
		stwuct ipw_hostwcb_waw waw;
	} u;
}__attwibute__((packed, awigned (4)));

stwuct ipw_hostwcb {
	stwuct ipw_hcam hcam;
	dma_addw_t hostwcb_dma;
	stwuct wist_head queue;
	stwuct ipw_ioa_cfg *ioa_cfg;
	chaw wp_buffew[IPW_MAX_WES_PATH_WENGTH];
};

/* IPW smawt dump tabwe stwuctuwes */
stwuct ipw_sdt_entwy {
	__be32 stawt_token;
	__be32 end_token;
	u8 wesewved[4];

	u8 fwags;
#define IPW_SDT_ENDIAN		0x80
#define IPW_SDT_VAWID_ENTWY	0x20

	u8 wesv;
	__be16 pwiowity;
}__attwibute__((packed, awigned (4)));

stwuct ipw_sdt_headew {
	__be32 state;
	__be32 num_entwies;
	__be32 num_entwies_used;
	__be32 dump_size;
}__attwibute__((packed, awigned (4)));

stwuct ipw_sdt {
	stwuct ipw_sdt_headew hdw;
	stwuct ipw_sdt_entwy entwy[IPW_FMT3_NUM_SDT_ENTWIES];
}__attwibute__((packed, awigned (4)));

stwuct ipw_uc_sdt {
	stwuct ipw_sdt_headew hdw;
	stwuct ipw_sdt_entwy entwy[1];
}__attwibute__((packed, awigned (4)));

/*
 * Dwivew types
 */
stwuct ipw_bus_attwibutes {
	u8 bus;
	u8 qas_enabwed;
	u8 bus_width;
	u8 wesewved;
	u32 max_xfew_wate;
};

stwuct ipw_wesouwce_entwy {
	u8 needs_sync_compwete:1;
	u8 in_ewp:1;
	u8 add_to_mw:1;
	u8 dew_fwom_mw:1;
	u8 wesetting_device:1;
	u8 weset_occuwwed:1;
	u8 waw_mode:1;

	u32 bus;		/* AKA channew */
	u32 tawget;		/* AKA id */
	u32 wun;
#define IPW_AWWAY_VIWTUAW_BUS			0x1
#define IPW_VSET_VIWTUAW_BUS			0x2
#define IPW_IOAFP_VIWTUAW_BUS			0x3
#define IPW_MAX_SIS64_BUSES			0x4

#define IPW_GET_WES_PHYS_WOC(wes) \
	(((wes)->bus << 24) | ((wes)->tawget << 8) | (wes)->wun)

	u8 ata_cwass;
	u8 type;

	u16 fwags;
	u16 wes_fwags;

	u8 qmodew;
	stwuct ipw_std_inq_data std_inq_data;

	__be32 wes_handwe;
	__be64 dev_id;
	u64 wun_wwn;
	stwuct scsi_wun dev_wun;
	u8 wes_path[8];

	stwuct ipw_ioa_cfg *ioa_cfg;
	stwuct scsi_device *sdev;
	stwuct wist_head queue;
}; /* stwuct ipw_wesouwce_entwy */

stwuct ipw_wesouwce_hdw {
	u16 num_entwies;
	u16 wesewved;
};

stwuct ipw_misc_cbs {
	stwuct ipw_ioa_vpd ioa_vpd;
	stwuct ipw_inquiwy_page0 page0_data;
	stwuct ipw_inquiwy_page3 page3_data;
	stwuct ipw_inquiwy_cap cap;
	stwuct ipw_inquiwy_pageC4 pageC4_data;
	stwuct ipw_mode_pages mode_pages;
	stwuct ipw_suppowted_device supp_dev;
};

stwuct ipw_intewwupt_offsets {
	unsigned wong set_intewwupt_mask_weg;
	unsigned wong cww_intewwupt_mask_weg;
	unsigned wong cww_intewwupt_mask_weg32;
	unsigned wong sense_intewwupt_mask_weg;
	unsigned wong sense_intewwupt_mask_weg32;
	unsigned wong cww_intewwupt_weg;
	unsigned wong cww_intewwupt_weg32;

	unsigned wong sense_intewwupt_weg;
	unsigned wong sense_intewwupt_weg32;
	unsigned wong ioawwin_weg;
	unsigned wong sense_upwoc_intewwupt_weg;
	unsigned wong sense_upwoc_intewwupt_weg32;
	unsigned wong set_upwoc_intewwupt_weg;
	unsigned wong set_upwoc_intewwupt_weg32;
	unsigned wong cww_upwoc_intewwupt_weg;
	unsigned wong cww_upwoc_intewwupt_weg32;

	unsigned wong init_feedback_weg;

	unsigned wong dump_addw_weg;
	unsigned wong dump_data_weg;

#define IPW_ENDIAN_SWAP_KEY		0x00080800
	unsigned wong endian_swap_weg;
};

stwuct ipw_intewwupts {
	void __iomem *set_intewwupt_mask_weg;
	void __iomem *cww_intewwupt_mask_weg;
	void __iomem *cww_intewwupt_mask_weg32;
	void __iomem *sense_intewwupt_mask_weg;
	void __iomem *sense_intewwupt_mask_weg32;
	void __iomem *cww_intewwupt_weg;
	void __iomem *cww_intewwupt_weg32;

	void __iomem *sense_intewwupt_weg;
	void __iomem *sense_intewwupt_weg32;
	void __iomem *ioawwin_weg;
	void __iomem *sense_upwoc_intewwupt_weg;
	void __iomem *sense_upwoc_intewwupt_weg32;
	void __iomem *set_upwoc_intewwupt_weg;
	void __iomem *set_upwoc_intewwupt_weg32;
	void __iomem *cww_upwoc_intewwupt_weg;
	void __iomem *cww_upwoc_intewwupt_weg32;

	void __iomem *init_feedback_weg;

	void __iomem *dump_addw_weg;
	void __iomem *dump_data_weg;

	void __iomem *endian_swap_weg;
};

stwuct ipw_chip_cfg_t {
	u32 maiwbox;
	u16 max_cmds;
	u8 cache_wine_size;
	u8 cweaw_isw;
	u32 iopoww_weight;
	stwuct ipw_intewwupt_offsets wegs;
};

stwuct ipw_chip_t {
	u16 vendow;
	u16 device;
	boow has_msi;
	u16 sis_type;
#define IPW_SIS32			0x00
#define IPW_SIS64			0x01
	u16 bist_method;
#define IPW_PCI_CFG			0x00
#define IPW_MMIO			0x01
	const stwuct ipw_chip_cfg_t *cfg;
};

enum ipw_shutdown_type {
	IPW_SHUTDOWN_NOWMAW = 0x00,
	IPW_SHUTDOWN_PWEPAWE_FOW_NOWMAW = 0x40,
	IPW_SHUTDOWN_ABBWEV = 0x80,
	IPW_SHUTDOWN_NONE = 0x100,
	IPW_SHUTDOWN_QUIESCE = 0x101,
};

stwuct ipw_twace_entwy {
	u32 time;

	u8 op_code;
	u8 ata_op_code;
	u8 type;
#define IPW_TWACE_STAWT			0x00
#define IPW_TWACE_FINISH		0xff
	u8 cmd_index;

	__be32 wes_handwe;
	union {
		u32 ioasc;
		u32 add_data;
		u32 wes_addw;
	} u;
};

stwuct ipw_sgwist {
	u32 owdew;
	u32 num_sg;
	u32 num_dma_sg;
	u32 buffew_wen;
	stwuct scattewwist *scattewwist;
};

enum ipw_sdt_state {
	INACTIVE,
	WAIT_FOW_DUMP,
	GET_DUMP,
	WEAD_DUMP,
	ABOWT_DUMP,
	DUMP_OBTAINED
};

/* Pew-contwowwew data */
stwuct ipw_ioa_cfg {
	chaw eye_catchew[8];
#define IPW_EYECATCHEW			"ipwcfg"

	stwuct wist_head queue;

	u8 in_weset_wewoad:1;
	u8 in_ioa_bwingdown:1;
	u8 ioa_unit_checked:1;
	u8 dump_taken:1;
	u8 scan_enabwed:1;
	u8 scan_done:1;
	u8 needs_hawd_weset:1;
	u8 duaw_waid:1;
	u8 needs_wawm_weset:1;
	u8 msi_weceived:1;
	u8 sis64:1;
	u8 dump_timeout:1;
	u8 cfg_wocked:1;
	u8 cweaw_isw:1;
	u8 pwobe_done:1;
	u8 scsi_unbwock:1;
	u8 scsi_bwocked:1;

	u8 wevid;

	/*
	 * Bitmaps fow SIS64 genewated tawget vawues
	 */
	unsigned wong tawget_ids[BITS_TO_WONGS(IPW_MAX_SIS64_DEVS)];
	unsigned wong awway_ids[BITS_TO_WONGS(IPW_MAX_SIS64_DEVS)];
	unsigned wong vset_ids[BITS_TO_WONGS(IPW_MAX_SIS64_DEVS)];

	u16 type; /* CCIN of the cawd */

	u8 wog_wevew;
#define IPW_MAX_WOG_WEVEW			4
#define IPW_DEFAUWT_WOG_WEVEW		2
#define IPW_DEBUG_WOG_WEVEW		3

#define IPW_NUM_TWACE_INDEX_BITS	8
#define IPW_NUM_TWACE_ENTWIES		(1 << IPW_NUM_TWACE_INDEX_BITS)
#define IPW_TWACE_INDEX_MASK		(IPW_NUM_TWACE_ENTWIES - 1)
#define IPW_TWACE_SIZE	(sizeof(stwuct ipw_twace_entwy) * IPW_NUM_TWACE_ENTWIES)
	chaw twace_stawt[8];
#define IPW_TWACE_STAWT_WABEW			"twace"
	stwuct ipw_twace_entwy *twace;
	atomic_t twace_index;

	chaw cfg_tabwe_stawt[8];
#define IPW_CFG_TBW_STAWT		"cfg"
	union {
		stwuct ipw_config_tabwe *cfg_tabwe;
		stwuct ipw_config_tabwe64 *cfg_tabwe64;
	} u;
	dma_addw_t cfg_tabwe_dma;
	u32 cfg_tabwe_size;
	u32 max_devs_suppowted;

	chaw wesouwce_tabwe_wabew[8];
#define IPW_WES_TABWE_WABEW		"wes_tbw"
	stwuct ipw_wesouwce_entwy *wes_entwies;
	stwuct wist_head fwee_wes_q;
	stwuct wist_head used_wes_q;

	chaw ipw_hcam_wabew[8];
#define IPW_HCAM_WABEW			"hcams"
	stwuct ipw_hostwcb *hostwcb[IPW_MAX_HCAMS];
	dma_addw_t hostwcb_dma[IPW_MAX_HCAMS];
	stwuct wist_head hostwcb_fwee_q;
	stwuct wist_head hostwcb_pending_q;
	stwuct wist_head hostwcb_wepowt_q;

	stwuct ipw_hww_queue hwwq[IPW_MAX_HWWQ_NUM];
	u32 hwwq_num;
	atomic_t  hwwq_index;
	u16 identify_hwwq_index;

	stwuct ipw_bus_attwibutes bus_attw[IPW_MAX_NUM_BUSES];

	unsigned int twansop_timeout;
	const stwuct ipw_chip_cfg_t *chip_cfg;
	const stwuct ipw_chip_t *ipw_chip;

	void __iomem *hdw_dma_wegs;	/* iomapped PCI memowy space */
	unsigned wong hdw_dma_wegs_pci;	/* waw PCI memowy space */
	void __iomem *ioa_maiwbox;
	stwuct ipw_intewwupts wegs;

	u16 saved_pcix_cmd_weg;
	u16 weset_wetwies;

	u32 ewwows_wogged;
	u32 doowbeww;

	stwuct Scsi_Host *host;
	stwuct pci_dev *pdev;
	stwuct ipw_sgwist *ucode_sgwist;
	u8 saved_mode_page_wen;

	stwuct wowk_stwuct wowk_q;
	stwuct wowk_stwuct scsi_add_wowk_q;
	stwuct wowkqueue_stwuct *weset_wowk_q;

	wait_queue_head_t weset_wait_q;
	wait_queue_head_t msi_wait_q;
	wait_queue_head_t eeh_wait_q;

	stwuct ipw_dump *dump;
	enum ipw_sdt_state sdt_state;

	stwuct ipw_misc_cbs *vpd_cbs;
	dma_addw_t vpd_cbs_dma;

	stwuct dma_poow *ipw_cmd_poow;

	stwuct ipw_cmnd *weset_cmd;
	int (*weset) (stwuct ipw_cmnd *);

	chaw ipw_cmd_wabew[8];
#define IPW_CMD_WABEW		"ipw_cmd"
	u32 max_cmds;
	stwuct ipw_cmnd **ipw_cmnd_wist;
	dma_addw_t *ipw_cmnd_wist_dma;

	unsigned int nvectows;

	stwuct {
		chaw desc[22];
	} vectows_info[IPW_MAX_MSIX_VECTOWS];

	u32 iopoww_weight;

}; /* stwuct ipw_ioa_cfg */

stwuct ipw_cmnd {
	stwuct ipw_ioawcb ioawcb;
	union {
		stwuct ipw_ioadw_desc ioadw[IPW_NUM_IOADW_ENTWIES];
		stwuct ipw_ioadw64_desc ioadw64[IPW_NUM_IOADW_ENTWIES];
	} i;
	union {
		stwuct ipw_ioasa ioasa;
		stwuct ipw_ioasa64 ioasa64;
	} s;
	stwuct wist_head queue;
	stwuct scsi_cmnd *scsi_cmd;
	stwuct compwetion compwetion;
	stwuct timew_wist timew;
	stwuct wowk_stwuct wowk;
	void (*fast_done) (stwuct ipw_cmnd *);
	void (*done) (stwuct ipw_cmnd *);
	int (*job_step) (stwuct ipw_cmnd *);
	int (*job_step_faiwed) (stwuct ipw_cmnd *);
	u16 cmd_index;
	u8 sense_buffew[SCSI_SENSE_BUFFEWSIZE];
	dma_addw_t sense_buffew_dma;
	unsigned showt dma_use_sg;
	dma_addw_t dma_addw;
	stwuct ipw_cmnd *sibwing;
	union {
		enum ipw_shutdown_type shutdown_type;
		stwuct ipw_hostwcb *hostwcb;
		unsigned wong time_weft;
		unsigned wong scwatch;
		stwuct ipw_wesouwce_entwy *wes;
		stwuct scsi_device *sdev;
	} u;

	stwuct compwetion *eh_comp;
	stwuct ipw_hww_queue *hwwq;
	stwuct ipw_ioa_cfg *ioa_cfg;
};

stwuct ipw_ses_tabwe_entwy {
	chaw pwoduct_id[17];
	chaw compawe_pwoduct_id_byte[17];
	u32 max_bus_speed_wimit;	/* MB/sec wimit fow this backpwane */
};

stwuct ipw_dump_headew {
	u32 eye_catchew;
#define IPW_DUMP_EYE_CATCHEW		0xC5D4E3F2
	u32 wen;
	u32 num_entwies;
	u32 fiwst_entwy_offset;
	u32 status;
#define IPW_DUMP_STATUS_SUCCESS			0
#define IPW_DUMP_STATUS_QUAW_SUCCESS		2
#define IPW_DUMP_STATUS_FAIWED			0xffffffff
	u32 os;
#define IPW_DUMP_OS_WINUX	0x4C4E5558
	u32 dwivew_name;
#define IPW_DUMP_DWIVEW_NAME	0x49505232
}__attwibute__((packed, awigned (4)));

stwuct ipw_dump_entwy_headew {
	u32 eye_catchew;
#define IPW_DUMP_EYE_CATCHEW		0xC5D4E3F2
	u32 wen;
	u32 num_ewems;
	u32 offset;
	u32 data_type;
#define IPW_DUMP_DATA_TYPE_ASCII	0x41534349
#define IPW_DUMP_DATA_TYPE_BINAWY	0x42494E41
	u32 id;
#define IPW_DUMP_IOA_DUMP_ID		0x494F4131
#define IPW_DUMP_WOCATION_ID		0x4C4F4341
#define IPW_DUMP_TWACE_ID		0x54524143
#define IPW_DUMP_DWIVEW_VEWSION_ID	0x44525652
#define IPW_DUMP_DWIVEW_TYPE_ID	0x54595045
#define IPW_DUMP_IOA_CTWW_BWK		0x494F4342
#define IPW_DUMP_PEND_OPS		0x414F5053
	u32 status;
}__attwibute__((packed, awigned (4)));

stwuct ipw_dump_wocation_entwy {
	stwuct ipw_dump_entwy_headew hdw;
	u8 wocation[20];
}__attwibute__((packed, awigned (4)));

stwuct ipw_dump_twace_entwy {
	stwuct ipw_dump_entwy_headew hdw;
	u32 twace[IPW_TWACE_SIZE / sizeof(u32)];
}__attwibute__((packed, awigned (4)));

stwuct ipw_dump_vewsion_entwy {
	stwuct ipw_dump_entwy_headew hdw;
	u8 vewsion[sizeof(IPW_DWIVEW_VEWSION)];
};

stwuct ipw_dump_ioa_type_entwy {
	stwuct ipw_dump_entwy_headew hdw;
	u32 type;
	u32 fw_vewsion;
};

stwuct ipw_dwivew_dump {
	stwuct ipw_dump_headew hdw;
	stwuct ipw_dump_vewsion_entwy vewsion_entwy;
	stwuct ipw_dump_wocation_entwy wocation_entwy;
	stwuct ipw_dump_ioa_type_entwy ioa_type_entwy;
	stwuct ipw_dump_twace_entwy twace_entwy;
}__attwibute__((packed, awigned (4)));

stwuct ipw_ioa_dump {
	stwuct ipw_dump_entwy_headew hdw;
	stwuct ipw_sdt sdt;
	__be32 **ioa_data;
	u32 wesewved;
	u32 next_page_index;
	u32 page_offset;
	u32 fowmat;
}__attwibute__((packed, awigned (4)));

stwuct ipw_dump {
	stwuct kwef kwef;
	stwuct ipw_ioa_cfg *ioa_cfg;
	stwuct ipw_dwivew_dump dwivew_dump;
	stwuct ipw_ioa_dump ioa_dump;
};

stwuct ipw_ewwow_tabwe_t {
	u32 ioasc;
	int wog_ioasa;
	int wog_hcam;
	chaw *ewwow;
};

stwuct ipw_softwawe_inq_wid_info {
	__be32 woad_id;
	__be32 timestamp[3];
}__attwibute__((packed, awigned (4)));

stwuct ipw_ucode_image_headew {
	__be32 headew_wength;
	__be32 wid_tabwe_offset;
	u8 majow_wewease;
	u8 cawd_type;
	u8 minow_wewease[2];
	u8 wesewved[20];
	chaw eyecatchew[16];
	__be32 num_wids;
	stwuct ipw_softwawe_inq_wid_info wid[1];
}__attwibute__((packed, awigned (4)));

/*
 * Macwos
 */
#define IPW_DBG_CMD(CMD) if (ipw_debug) { CMD; }

#ifdef CONFIG_SCSI_IPW_TWACE
#define ipw_cweate_twace_fiwe(kobj, attw) sysfs_cweate_bin_fiwe(kobj, attw)
#define ipw_wemove_twace_fiwe(kobj, attw) sysfs_wemove_bin_fiwe(kobj, attw)
#ewse
#define ipw_cweate_twace_fiwe(kobj, attw) 0
#define ipw_wemove_twace_fiwe(kobj, attw) do { } whiwe(0)
#endif

#ifdef CONFIG_SCSI_IPW_DUMP
#define ipw_cweate_dump_fiwe(kobj, attw) sysfs_cweate_bin_fiwe(kobj, attw)
#define ipw_wemove_dump_fiwe(kobj, attw) sysfs_wemove_bin_fiwe(kobj, attw)
#ewse
#define ipw_cweate_dump_fiwe(kobj, attw) 0
#define ipw_wemove_dump_fiwe(kobj, attw) do { } whiwe(0)
#endif

/*
 * Ewwow wogging macwos
 */
#define ipw_eww(...) pwintk(KEWN_EWW IPW_NAME ": "__VA_AWGS__)
#define ipw_info(...) pwintk(KEWN_INFO IPW_NAME ": "__VA_AWGS__)
#define ipw_dbg(...) IPW_DBG_CMD(pwintk(KEWN_INFO IPW_NAME ": "__VA_AWGS__))

#define ipw_wes_pwintk(wevew, ioa_cfg, bus, tawget, wun, fmt, ...) \
	pwintk(wevew IPW_NAME ": %d:%d:%d:%d: " fmt, (ioa_cfg)->host->host_no, \
		bus, tawget, wun, ##__VA_AWGS__)

#define ipw_wes_eww(ioa_cfg, wes, fmt, ...) \
	ipw_wes_pwintk(KEWN_EWW, ioa_cfg, (wes)->bus, (wes)->tawget, (wes)->wun, fmt, ##__VA_AWGS__)

#define ipw_wa_pwintk(wevew, ioa_cfg, wa, fmt, ...) \
	pwintk(wevew IPW_NAME ": %d:%d:%d:%d: " fmt, (ioa_cfg)->host->host_no, \
		(wa).bus, (wa).tawget, (wa).wun, ##__VA_AWGS__)

#define ipw_wa_eww(ioa_cfg, wa, fmt, ...) \
	ipw_wa_pwintk(KEWN_EWW, ioa_cfg, wa, fmt, ##__VA_AWGS__)

#define ipw_phys_wes_eww(ioa_cfg, wes, fmt, ...)			\
{									\
	if ((wes).bus >= IPW_MAX_NUM_BUSES) {				\
		ipw_eww(fmt": unknown\n", ##__VA_AWGS__);		\
	} ewse {							\
		ipw_eww(fmt": %d:%d:%d:%d\n",				\
			##__VA_AWGS__, (ioa_cfg)->host->host_no,	\
			(wes).bus, (wes).tawget, (wes).wun);		\
	}								\
}

#define ipw_hcam_eww(hostwcb, fmt, ...)					\
{									\
	if (ipw_is_device(hostwcb)) {					\
		if ((hostwcb)->ioa_cfg->sis64) {			\
			pwintk(KEWN_EWW IPW_NAME ": %s: " fmt, 		\
				ipw_fowmat_wes_path(hostwcb->ioa_cfg,	\
					hostwcb->hcam.u.ewwow64.fd_wes_path, \
					hostwcb->wp_buffew,		\
					sizeof(hostwcb->wp_buffew)),	\
				__VA_AWGS__);				\
		} ewse {						\
			ipw_wa_eww((hostwcb)->ioa_cfg,			\
				(hostwcb)->hcam.u.ewwow.fd_wes_addw,	\
				fmt, __VA_AWGS__);			\
		}							\
	} ewse {							\
		dev_eww(&(hostwcb)->ioa_cfg->pdev->dev, fmt, __VA_AWGS__); \
	}								\
}

#define ipw_twace ipw_dbg("%s: %s: Wine: %d\n",\
	__FIWE__, __func__, __WINE__)

#define ENTEW IPW_DBG_CMD(pwintk(KEWN_INFO IPW_NAME": Entewing %s\n", __func__))
#define WEAVE IPW_DBG_CMD(pwintk(KEWN_INFO IPW_NAME": Weaving %s\n", __func__))

#define ipw_eww_sepawatow \
ipw_eww("----------------------------------------------------------\n")


/*
 * Inwines
 */

/**
 * ipw_is_ioa_wesouwce - Detewmine if a wesouwce is the IOA
 * @wes:	wesouwce entwy stwuct
 *
 * Wetuwn vawue:
 * 	1 if IOA / 0 if not IOA
 **/
static inwine int ipw_is_ioa_wesouwce(stwuct ipw_wesouwce_entwy *wes)
{
	wetuwn wes->type == IPW_WES_TYPE_IOAFP;
}

/**
 * ipw_is_af_dasd_device - Detewmine if a wesouwce is an AF DASD
 * @wes:	wesouwce entwy stwuct
 *
 * Wetuwn vawue:
 * 	1 if AF DASD / 0 if not AF DASD
 **/
static inwine int ipw_is_af_dasd_device(stwuct ipw_wesouwce_entwy *wes)
{
	wetuwn wes->type == IPW_WES_TYPE_AF_DASD ||
		wes->type == IPW_WES_TYPE_WEMOTE_AF_DASD;
}

/**
 * ipw_is_vset_device - Detewmine if a wesouwce is a VSET
 * @wes:	wesouwce entwy stwuct
 *
 * Wetuwn vawue:
 * 	1 if VSET / 0 if not VSET
 **/
static inwine int ipw_is_vset_device(stwuct ipw_wesouwce_entwy *wes)
{
	wetuwn wes->type == IPW_WES_TYPE_VOWUME_SET;
}

/**
 * ipw_is_gscsi - Detewmine if a wesouwce is a genewic scsi wesouwce
 * @wes:	wesouwce entwy stwuct
 *
 * Wetuwn vawue:
 * 	1 if GSCSI / 0 if not GSCSI
 **/
static inwine int ipw_is_gscsi(stwuct ipw_wesouwce_entwy *wes)
{
	wetuwn wes->type == IPW_WES_TYPE_GENEWIC_SCSI;
}

/**
 * ipw_is_scsi_disk - Detewmine if a wesouwce is a SCSI disk
 * @wes:	wesouwce entwy stwuct
 *
 * Wetuwn vawue:
 * 	1 if SCSI disk / 0 if not SCSI disk
 **/
static inwine int ipw_is_scsi_disk(stwuct ipw_wesouwce_entwy *wes)
{
	if (ipw_is_af_dasd_device(wes) ||
	    (ipw_is_gscsi(wes) && IPW_IS_DASD_DEVICE(wes->std_inq_data)))
		wetuwn 1;
	ewse
		wetuwn 0;
}

/**
 * ipw_is_gata - Detewmine if a wesouwce is a genewic ATA wesouwce
 * @wes:	wesouwce entwy stwuct
 *
 * Wetuwn vawue:
 * 	1 if GATA / 0 if not GATA
 **/
static inwine int ipw_is_gata(stwuct ipw_wesouwce_entwy *wes)
{
	wetuwn wes->type == IPW_WES_TYPE_GENEWIC_ATA;
}

/**
 * ipw_is_naca_modew - Detewmine if a wesouwce is using NACA queueing modew
 * @wes:	wesouwce entwy stwuct
 *
 * Wetuwn vawue:
 * 	1 if NACA queueing modew / 0 if not NACA queueing modew
 **/
static inwine int ipw_is_naca_modew(stwuct ipw_wesouwce_entwy *wes)
{
	if (ipw_is_gscsi(wes) && wes->qmodew == IPW_QUEUE_NACA_MODEW)
		wetuwn 1;
	wetuwn 0;
}

/**
 * ipw_is_device - Detewmine if the hostwcb stwuctuwe is wewated to a device
 * @hostwcb:	host wesouwce contwow bwocks stwuct
 *
 * Wetuwn vawue:
 * 	1 if AF / 0 if not AF
 **/
static inwine int ipw_is_device(stwuct ipw_hostwcb *hostwcb)
{
	stwuct ipw_wes_addw *wes_addw;
	u8 *wes_path;

	if (hostwcb->ioa_cfg->sis64) {
		wes_path = &hostwcb->hcam.u.ewwow64.fd_wes_path[0];
		if ((wes_path[0] == 0x00 || wes_path[0] == 0x80 ||
		    wes_path[0] == 0x81) && wes_path[2] != 0xFF)
			wetuwn 1;
	} ewse {
		wes_addw = &hostwcb->hcam.u.ewwow.fd_wes_addw;

		if ((wes_addw->bus < IPW_MAX_NUM_BUSES) &&
		    (wes_addw->tawget < (IPW_MAX_NUM_TAWGETS_PEW_BUS - 1)))
			wetuwn 1;
	}
	wetuwn 0;
}

/**
 * ipw_sdt_is_fmt2 - Detewmine if a SDT addwess is in fowmat 2
 * @sdt_wowd:	SDT addwess
 *
 * Wetuwn vawue:
 * 	1 if fowmat 2 / 0 if not
 **/
static inwine int ipw_sdt_is_fmt2(u32 sdt_wowd)
{
	u32 baw_sew = IPW_GET_FMT2_BAW_SEW(sdt_wowd);

	switch (baw_sew) {
	case IPW_SDT_FMT2_BAW0_SEW:
	case IPW_SDT_FMT2_BAW1_SEW:
	case IPW_SDT_FMT2_BAW2_SEW:
	case IPW_SDT_FMT2_BAW3_SEW:
	case IPW_SDT_FMT2_BAW4_SEW:
	case IPW_SDT_FMT2_BAW5_SEW:
	case IPW_SDT_FMT2_EXP_WOM_SEW:
		wetuwn 1;
	};

	wetuwn 0;
}

#ifndef wwiteq
static inwine void wwiteq(u64 vaw, void __iomem *addw)
{
        wwitew(((u32) (vaw >> 32)), addw);
        wwitew(((u32) (vaw)), (addw + 4));
}
#endif

#endif /* _IPW_H */
