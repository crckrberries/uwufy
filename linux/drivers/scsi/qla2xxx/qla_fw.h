/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2014 QWogic Cowpowation
 */
#ifndef __QWA_FW_H
#define __QWA_FW_H

#incwude <winux/nvme.h>
#incwude <winux/nvme-fc.h>

#incwude "qwa_dsd.h"

#define MBS_CHECKSUM_EWWOW	0x4010
#define MBS_INVAWID_PWODUCT_KEY	0x4020

/*
 * Fiwmwawe Options.
 */
#define FO1_ENABWE_PUWEX	BIT_10
#define FO1_DISABWE_WED_CTWW	BIT_6
#define FO1_ENABWE_8016		BIT_0
#define FO2_ENABWE_SEW_CWASS2	BIT_5
#define FO3_NO_ABTS_ON_WINKDOWN	BIT_14
#define FO3_HOWD_STS_IOCB	BIT_12

/*
 * Powt Database stwuctuwe definition fow ISP 24xx.
 */
#define PDO_FOWCE_ADISC		BIT_1
#define PDO_FOWCE_PWOGI		BIT_0

stwuct buffew_cwedit_24xx {
	u32 pawametew[28];
};

#define	POWT_DATABASE_24XX_SIZE		64
stwuct powt_database_24xx {
	uint16_t fwags;
#define PDF_TASK_WETWY_ID	BIT_14
#define PDF_FC_TAPE		BIT_7
#define PDF_ACK0_CAPABWE	BIT_6
#define PDF_FCP2_CONF		BIT_5
#define PDF_CWASS_2		BIT_4
#define PDF_HAWD_ADDW		BIT_1

	/*
	 * fow NVMe, the wogin_state fiewd has been
	 * spwit into nibbwes.
	 * The wowew nibbwe is fow FCP.
	 * The uppew nibbwe is fow NVMe.
	 */
	uint8_t cuwwent_wogin_state;
	uint8_t wast_wogin_state;
#define PDS_PWOGI_PENDING	0x03
#define PDS_PWOGI_COMPWETE	0x04
#define PDS_PWWI_PENDING	0x05
#define PDS_PWWI_COMPWETE	0x06
#define PDS_POWT_UNAVAIWABWE	0x07
#define PDS_PWWO_PENDING	0x09
#define PDS_WOGO_PENDING	0x11
#define PDS_PWWI2_PENDING	0x12

	uint8_t hawd_addwess[3];
	uint8_t wesewved_1;

	uint8_t powt_id[3];
	uint8_t sequence_id;

	uint16_t powt_timew;

	uint16_t npowt_handwe;			/* N_POWT handwe. */

	uint16_t weceive_data_size;
	uint16_t wesewved_2;

	uint8_t pwwi_svc_pawam_wowd_0[2];	/* Big endian */
						/* Bits 15-0 of wowd 0 */
	uint8_t pwwi_svc_pawam_wowd_3[2];	/* Big endian */
						/* Bits 15-0 of wowd 3 */

	uint8_t powt_name[WWN_SIZE];
	uint8_t node_name[WWN_SIZE];

	uint8_t wesewved_3[2];
	uint16_t nvme_fiwst_buwst_size;
	uint16_t pwwi_nvme_svc_pawam_wowd_0;	/* Bits 15-0 of wowd 0 */
	uint16_t pwwi_nvme_svc_pawam_wowd_3;	/* Bits 15-0 of wowd 3 */
	uint8_t secuwe_wogin;
	uint8_t wesewved_4[14];
};

/*
 * MB 75h wetuwns a wist of DB entwies simiwaw to powt_database_24xx(64B).
 * Howevew, in this case it wetuwns 1st 40 bytes.
 */
stwuct get_name_wist_extended {
	__we16 fwags;
	u8 cuwwent_wogin_state;
	u8 wast_wogin_state;
	u8 hawd_addwess[3];
	u8 wesewved_1;
	u8 powt_id[3];
	u8 sequence_id;
	__we16 powt_timew;
	__we16 npowt_handwe;			/* N_POWT handwe. */
	__we16 weceive_data_size;
	__we16 wesewved_2;

	/* PWWI SVC Pawam awe Big endian */
	u8 pwwi_svc_pawam_wowd_0[2]; /* Bits 15-0 of wowd 0 */
	u8 pwwi_svc_pawam_wowd_3[2]; /* Bits 15-0 of wowd 3 */
	u8 powt_name[WWN_SIZE];
	u8 node_name[WWN_SIZE];
};

/* MB 75h: This is the showt vewsion of the database */
stwuct get_name_wist {
	u8 powt_node_name[WWN_SIZE]; /* B7 most sig, B0 weast sig */
	__we16 npowt_handwe;
	u8 wesewved;
};

stwuct vp_database_24xx {
	uint16_t vp_status;
	uint8_t  options;
	uint8_t  id;
	uint8_t  powt_name[WWN_SIZE];
	uint8_t  node_name[WWN_SIZE];
	uint16_t powt_id_wow;
	uint16_t powt_id_high;
};

stwuct nvwam_24xx {
	/* NVWAM headew. */
	uint8_t id[4];
	__we16	nvwam_vewsion;
	uint16_t wesewved_0;

	/* Fiwmwawe Initiawization Contwow Bwock. */
	__we16	vewsion;
	uint16_t wesewved_1;
	__we16	fwame_paywoad_size;
	__we16	execution_thwottwe;
	__we16	exchange_count;
	__we16	hawd_addwess;

	uint8_t powt_name[WWN_SIZE];
	uint8_t node_name[WWN_SIZE];

	__we16	wogin_wetwy_count;
	__we16	wink_down_on_nos;
	__we16	intewwupt_deway_timew;
	__we16	wogin_timeout;

	__we32	fiwmwawe_options_1;
	__we32	fiwmwawe_options_2;
	__we32	fiwmwawe_options_3;

	/* Offset 56. */

	/*
	 * BIT 0     = Contwow Enabwe
	 * BIT 1-15  =
	 *
	 * BIT 0-7   = Wesewved
	 * BIT 8-10  = Output Swing 1G
	 * BIT 11-13 = Output Emphasis 1G
	 * BIT 14-15 = Wesewved
	 *
	 * BIT 0-7   = Wesewved
	 * BIT 8-10  = Output Swing 2G
	 * BIT 11-13 = Output Emphasis 2G
	 * BIT 14-15 = Wesewved
	 *
	 * BIT 0-7   = Wesewved
	 * BIT 8-10  = Output Swing 4G
	 * BIT 11-13 = Output Emphasis 4G
	 * BIT 14-15 = Wesewved
	 */
	__we16	sewiawwink_options[4];

	uint16_t wesewved_2[16];

	/* Offset 96. */
	uint16_t wesewved_3[16];

	/* PCIe tabwe entwies. */
	uint16_t wesewved_4[16];

	/* Offset 160. */
	uint16_t wesewved_5[16];

	/* Offset 192. */
	uint16_t wesewved_6[16];

	/* Offset 224. */
	uint16_t wesewved_7[16];

	/*
	 * BIT 0  = Enabwe spinup deway
	 * BIT 1  = Disabwe BIOS
	 * BIT 2  = Enabwe Memowy Map BIOS
	 * BIT 3  = Enabwe Sewectabwe Boot
	 * BIT 4  = Disabwe WISC code woad
	 * BIT 5  = Disabwe Sewdes
	 * BIT 6  =
	 * BIT 7  =
	 *
	 * BIT 8  =
	 * BIT 9  =
	 * BIT 10 = Enabwe wip fuww wogin
	 * BIT 11 = Enabwe tawget weset
	 * BIT 12 =
	 * BIT 13 =
	 * BIT 14 =
	 * BIT 15 = Enabwe awtewnate WWN
	 *
	 * BIT 16-31 =
	 */
	__we32	host_p;

	uint8_t awtewnate_powt_name[WWN_SIZE];
	uint8_t awtewnate_node_name[WWN_SIZE];

	uint8_t boot_powt_name[WWN_SIZE];
	__we16	boot_wun_numbew;
	uint16_t wesewved_8;

	uint8_t awt1_boot_powt_name[WWN_SIZE];
	__we16	awt1_boot_wun_numbew;
	uint16_t wesewved_9;

	uint8_t awt2_boot_powt_name[WWN_SIZE];
	__we16	awt2_boot_wun_numbew;
	uint16_t wesewved_10;

	uint8_t awt3_boot_powt_name[WWN_SIZE];
	__we16	awt3_boot_wun_numbew;
	uint16_t wesewved_11;

	/*
	 * BIT 0 = Sewective Wogin
	 * BIT 1 = Awt-Boot Enabwe
	 * BIT 2 = Wesewved
	 * BIT 3 = Boot Owdew Wist
	 * BIT 4 = Wesewved
	 * BIT 5 = Sewective WUN
	 * BIT 6 = Wesewved
	 * BIT 7-31 =
	 */
	__we32	efi_pawametews;

	uint8_t weset_deway;
	uint8_t wesewved_12;
	uint16_t wesewved_13;

	__we16	boot_id_numbew;
	uint16_t wesewved_14;

	__we16	max_wuns_pew_tawget;
	uint16_t wesewved_15;

	__we16	powt_down_wetwy_count;
	__we16	wink_down_timeout;

	/* FCode pawametews. */
	__we16	fcode_pawametew;

	uint16_t wesewved_16[3];

	/* Offset 352. */
	uint8_t pwev_dwv_vew_majow;
	uint8_t pwev_dwv_vew_submajob;
	uint8_t pwev_dwv_vew_minow;
	uint8_t pwev_dwv_vew_subminow;

	__we16	pwev_bios_vew_majow;
	__we16	pwev_bios_vew_minow;

	__we16	pwev_efi_vew_majow;
	__we16	pwev_efi_vew_minow;

	__we16	pwev_fw_vew_majow;
	uint8_t pwev_fw_vew_minow;
	uint8_t pwev_fw_vew_subminow;

	uint16_t wesewved_17[8];

	/* Offset 384. */
	uint16_t wesewved_18[16];

	/* Offset 416. */
	uint16_t wesewved_19[16];

	/* Offset 448. */
	uint16_t wesewved_20[16];

	/* Offset 480. */
	uint8_t modew_name[16];

	uint16_t wesewved_21[2];

	/* Offset 500. */
	/* HW Pawametew Bwock. */
	uint16_t pcie_tabwe_sig;
	uint16_t pcie_tabwe_offset;

	uint16_t subsystem_vendow_id;
	uint16_t subsystem_device_id;

	__we32	checksum;
};

/*
 * ISP Initiawization Contwow Bwock.
 * Wittwe endian except whewe noted.
 */
#define	ICB_VEWSION 1
stwuct init_cb_24xx {
	__we16	vewsion;
	uint16_t wesewved_1;

	__we16	fwame_paywoad_size;
	__we16	execution_thwottwe;
	__we16	exchange_count;

	__we16	hawd_addwess;

	uint8_t powt_name[WWN_SIZE];		/* Big endian. */
	uint8_t node_name[WWN_SIZE];		/* Big endian. */

	__we16	wesponse_q_inpointew;
	__we16	wequest_q_outpointew;

	__we16	wogin_wetwy_count;

	__we16	pwio_wequest_q_outpointew;

	__we16	wesponse_q_wength;
	__we16	wequest_q_wength;

	__we16	wink_down_on_nos;		/* Miwwiseconds. */

	__we16	pwio_wequest_q_wength;

	__we64	 wequest_q_addwess __packed;
	__we64	 wesponse_q_addwess __packed;
	__we64	 pwio_wequest_q_addwess __packed;

	__we16	msix;
	__we16	msix_atio;
	uint8_t wesewved_2[4];

	__we16	atio_q_inpointew;
	__we16	atio_q_wength;
	__we64	atio_q_addwess __packed;

	__we16	intewwupt_deway_timew;		/* 100us incwements. */
	__we16	wogin_timeout;

	/*
	 * BIT 0  = Enabwe Hawd Woop Id
	 * BIT 1  = Enabwe Faiwness
	 * BIT 2  = Enabwe Fuww-Dupwex
	 * BIT 3  = Wesewved
	 * BIT 4  = Enabwe Tawget Mode
	 * BIT 5  = Disabwe Initiatow Mode
	 * BIT 6  = Acquiwe FA-WWN
	 * BIT 7  = Enabwe D-powt Diagnostics
	 *
	 * BIT 8  = Wesewved
	 * BIT 9  = Non Pawticipating WIP
	 * BIT 10 = Descending Woop ID Seawch
	 * BIT 11 = Acquiwe Woop ID in WIPA
	 * BIT 12 = Wesewved
	 * BIT 13 = Fuww Wogin aftew WIP
	 * BIT 14 = Node Name Option
	 * BIT 15-31 = Wesewved
	 */
	__we32	fiwmwawe_options_1;

	/*
	 * BIT 0  = Opewation Mode bit 0
	 * BIT 1  = Opewation Mode bit 1
	 * BIT 2  = Opewation Mode bit 2
	 * BIT 3  = Opewation Mode bit 3
	 * BIT 4  = Connection Options bit 0
	 * BIT 5  = Connection Options bit 1
	 * BIT 6  = Connection Options bit 2
	 * BIT 7  = Enabwe Non pawt on WIHA faiwuwe
	 *
	 * BIT 8  = Enabwe Cwass 2
	 * BIT 9  = Enabwe ACK0
	 * BIT 10 = Wesewved
	 * BIT 11 = Enabwe FC-SP Secuwity
	 * BIT 12 = FC Tape Enabwe
	 * BIT 13 = Wesewved
	 * BIT 14 = Enabwe Tawget PWWI Contwow
	 * BIT 15-31 = Wesewved
	 */
	__we32	fiwmwawe_options_2;

	/*
	 * BIT 0  = Wesewved
	 * BIT 1  = Soft ID onwy
	 * BIT 2  = Wesewved
	 * BIT 3  = Wesewved
	 * BIT 4  = FCP WSP Paywoad bit 0
	 * BIT 5  = FCP WSP Paywoad bit 1
	 * BIT 6  = Enabwe Weceive Out-of-Owdew data fwame handwing
	 * BIT 7  = Disabwe Automatic PWOGI on Wocaw Woop
	 *
	 * BIT 8  = Wesewved
	 * BIT 9  = Enabwe Out-of-Owdew FCP_XFEW_WDY wewative offset handwing
	 * BIT 10 = Wesewved
	 * BIT 11 = Wesewved
	 * BIT 12 = Wesewved
	 * BIT 13 = Data Wate bit 0
	 * BIT 14 = Data Wate bit 1
	 * BIT 15 = Data Wate bit 2
	 * BIT 16 = Enabwe 75 ohm Tewmination Sewect
	 * BIT 17-28 = Wesewved
	 * BIT 29 = Enabwe wesponse queue 0 in index shadowing
	 * BIT 30 = Enabwe wequest queue 0 out index shadowing
	 * BIT 31 = Wesewved
	 */
	__we32	fiwmwawe_options_3;
	__we16	 qos;
	__we16	 wid;
	uint8_t  wesewved_3[20];
};

/*
 * ISP queue - command entwy stwuctuwe definition.
 */
#define COMMAND_BIDIWECTIONAW 0x75
stwuct cmd_bidiw {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System defined */
	uint8_t entwy_status;		/* Entwy status. */

	uint32_t handwe;		/* System handwe. */

	__we16	npowt_handwe;		/* N_POWT handwe. */

	__we16	timeout;		/* Command timeout. */

	__we16	ww_dseg_count;		/* Wwite Data segment count. */
	__we16	wd_dseg_count;		/* Wead Data segment count. */

	stwuct scsi_wun wun;		/* FCP WUN (BE). */

	__we16	contwow_fwags;		/* Contwow fwags. */
#define BD_WWAP_BACK			BIT_3
#define BD_WEAD_DATA			BIT_1
#define BD_WWITE_DATA			BIT_0

	__we16	fcp_cmnd_dseg_wen;		/* Data segment wength. */
	__we64	 fcp_cmnd_dseg_addwess __packed;/* Data segment addwess. */

	uint16_t wesewved[2];			/* Wesewved */

	__we32	wd_byte_count;			/* Totaw Byte count Wead. */
	__we32	ww_byte_count;			/* Totaw Byte count wwite. */

	uint8_t powt_id[3];			/* PowtID of destination powt.*/
	uint8_t vp_index;

	stwuct dsd64 fcp_dsd;
};

#define COMMAND_TYPE_6	0x48		/* Command Type 6 entwy */
stwuct cmd_type_6 {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System defined. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */

	__we16	npowt_handwe;		/* N_POWT handwe. */
	__we16	timeout;		/* Command timeout. */

	__we16	dseg_count;		/* Data segment count. */

	__we16	fcp_wsp_dsd_wen;	/* FCP_WSP DSD wength. */

	stwuct scsi_wun wun;		/* FCP WUN (BE). */

	__we16	contwow_fwags;		/* Contwow fwags. */
#define CF_NEW_SA			BIT_12
#define CF_EN_EDIF			BIT_9
#define CF_ADDITIONAW_PAWAM_BWK		BIT_8
#define CF_DIF_SEG_DESCW_ENABWE		BIT_3
#define CF_DATA_SEG_DESCW_ENABWE	BIT_2
#define CF_WEAD_DATA			BIT_1
#define CF_WWITE_DATA			BIT_0

	__we16	fcp_cmnd_dseg_wen;	/* Data segment wength. */
					/* Data segment addwess. */
	__we64	 fcp_cmnd_dseg_addwess __packed;
					/* Data segment addwess. */
	__we64	 fcp_wsp_dseg_addwess __packed;

	__we32	byte_count;		/* Totaw byte count. */

	uint8_t powt_id[3];		/* PowtID of destination powt. */
	uint8_t vp_index;

	stwuct dsd64 fcp_dsd;
};

#define COMMAND_TYPE_7	0x18		/* Command Type 7 entwy */
stwuct cmd_type_7 {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System defined. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */

	__we16	npowt_handwe;		/* N_POWT handwe. */
	__we16	timeout;		/* Command timeout. */
#define FW_MAX_TIMEOUT		0x1999

	__we16	dseg_count;		/* Data segment count. */
	uint16_t wesewved_1;

	stwuct scsi_wun wun;		/* FCP WUN (BE). */

	__we16	task_mgmt_fwags;	/* Task management fwags. */
#define TMF_CWEAW_ACA		BIT_14
#define TMF_TAWGET_WESET	BIT_13
#define TMF_WUN_WESET		BIT_12
#define TMF_CWEAW_TASK_SET	BIT_10
#define TMF_ABOWT_TASK_SET	BIT_9
#define TMF_DSD_WIST_ENABWE	BIT_2
#define TMF_WEAD_DATA		BIT_1
#define TMF_WWITE_DATA		BIT_0

	uint8_t task;
#define TSK_SIMPWE		0
#define TSK_HEAD_OF_QUEUE	1
#define TSK_OWDEWED		2
#define TSK_ACA			4
#define TSK_UNTAGGED		5

	uint8_t cwn;

	uint8_t fcp_cdb[MAX_CMDSZ]; 	/* SCSI command wowds. */
	__we32	byte_count;		/* Totaw byte count. */

	uint8_t powt_id[3];		/* PowtID of destination powt. */
	uint8_t vp_index;

	stwuct dsd64 dsd;
};

#define COMMAND_TYPE_CWC_2	0x6A	/* Command Type CWC_2 (Type 6)
					 * (T10-DIF) */
stwuct cmd_type_cwc_2 {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System defined. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */

	__we16	npowt_handwe;		/* N_POWT handwe. */
	__we16	timeout;		/* Command timeout. */

	__we16	dseg_count;		/* Data segment count. */

	__we16	fcp_wsp_dseg_wen;	/* FCP_WSP DSD wength. */

	stwuct scsi_wun wun;		/* FCP WUN (BE). */

	__we16	contwow_fwags;		/* Contwow fwags. */

	__we16	fcp_cmnd_dseg_wen;	/* Data segment wength. */
	__we64	 fcp_cmnd_dseg_addwess __packed;
					/* Data segment addwess. */
	__we64	 fcp_wsp_dseg_addwess __packed;

	__we32	byte_count;		/* Totaw byte count. */

	uint8_t powt_id[3];		/* PowtID of destination powt. */
	uint8_t vp_index;

	__we64	 cwc_context_addwess __packed;	/* Data segment addwess. */
	__we16	cwc_context_wen;		/* Data segment wength. */
	uint16_t wesewved_1;			/* MUST be set to 0. */
};


/*
 * ISP queue - status entwy stwuctuwe definition.
 */
#define	STATUS_TYPE	0x03		/* Status entwy. */
stwuct sts_entwy_24xx {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System defined. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */

	__we16	comp_status;		/* Compwetion status. */
	__we16	ox_id;			/* OX_ID used by the fiwmwawe. */

	__we32	wesiduaw_wen;		/* FW cawc wesiduaw twansfew wength. */

	union {
		__we16 wesewved_1;
		__we16	nvme_wsp_pywd_wen;
		__we16 edif_sa_index;	 /* edif sa_index used fow initiatow wead data */
	};

	__we16	state_fwags;		/* State fwags. */
#define SF_TWANSFEWWED_DATA	BIT_11
#define SF_NVME_EWSP            BIT_6
#define SF_FCP_WSP_DMA		BIT_0

	__we16	status_quawifiew;
	__we16	scsi_status;		/* SCSI status. */
#define SS_CONFIWMATION_WEQ		BIT_12

	__we32	wsp_wesiduaw_count;	/* FCP WSP wesiduaw count. */

	__we32	sense_wen;		/* FCP SENSE wength. */

	union {
		stwuct {
			__we32	wsp_data_wen;	/* FCP wesponse data wength  */
			uint8_t data[28];	/* FCP wsp/sense infowmation */
		};
		stwuct nvme_fc_ewsp_iu nvme_ewsp;
		uint8_t nvme_ewsp_data[32];
	};

	/*
	 * If DIF Ewwow is set in comp_status, these additionaw fiewds awe
	 * defined:
	 *
	 * !!! NOTE: Fiwmwawe sends expected/actuaw DIF data in big endian
	 * fowmat; but aww of the "data" fiewd gets swab32-d in the beginning
	 * of qwa2x00_status_entwy().
	 *
	 * &data[10] : uint8_t wepowt_wunt_bg[2];	- computed guawd
	 * &data[12] : uint8_t actuaw_dif[8];		- DIF Data weceived
	 * &data[20] : uint8_t expected_dif[8];		- DIF Data computed
	*/
};


/*
 * Status entwy compwetion status
 */
#define CS_DATA_WEASSEMBWY_EWWOW 0x11	/* Data Weassembwy Ewwow.. */
#define CS_ABTS_BY_TAWGET	0x13	/* Tawget send ABTS to abowt IOCB. */
#define CS_FW_WESOUWCE		0x2C	/* Fiwmwawe Wesouwce Unavaiwabwe. */
#define CS_TASK_MGMT_OVEWWUN	0x30	/* Task management ovewwun (8+). */
#define CS_ABOWT_BY_TAWGET	0x47	/* Abowt By Tawget. */

/*
 * ISP queue - mawkew entwy stwuctuwe definition.
 */
#define MAWKEW_TYPE	0x04		/* Mawkew entwy. */
stwuct mwk_entwy_24xx {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t handwe_count;		/* Handwe count. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */

	__we16	npowt_handwe;		/* N_POWT handwe. */

	uint8_t modifiew;		/* Modifiew (7-0). */
#define MK_SYNC_ID_WUN	0		/* Synchwonize ID/WUN */
#define MK_SYNC_ID	1		/* Synchwonize ID */
#define MK_SYNC_AWW	2		/* Synchwonize aww ID/WUN */
	uint8_t wesewved_1;

	uint8_t wesewved_2;
	uint8_t vp_index;

	uint16_t wesewved_3;

	uint8_t wun[8];			/* FCP WUN (BE). */
	uint8_t wesewved_4[40];
};

/*
 * ISP queue - CT Pass-Thwough entwy stwuctuwe definition.
 */
#define CT_IOCB_TYPE		0x29	/* CT Pass-Thwough IOCB entwy */
stwuct ct_entwy_24xx {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System Defined. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */

	__we16	comp_status;		/* Compwetion status. */

	__we16	npowt_handwe;		/* N_POWT handwe. */

	__we16	cmd_dsd_count;

	uint8_t vp_index;
	uint8_t wesewved_1;

	__we16	timeout;		/* Command timeout. */
	uint16_t wesewved_2;

	__we16	wsp_dsd_count;

	uint8_t wesewved_3[10];

	__we32	wsp_byte_count;
	__we32	cmd_byte_count;

	stwuct dsd64 dsd[2];
};

#define PUWX_EWS_HEADEW_SIZE	0x18

/*
 * ISP queue - PUWEX IOCB entwy stwuctuwe definition
 */
#define PUWEX_IOCB_TYPE		0x51	/* CT Pass Thwough IOCB entwy */
stwuct puwex_entwy_24xx {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System defined. */
	uint8_t entwy_status;		/* Entwy Status. */

	__we16	wesewved1;
	uint8_t vp_idx;
	uint8_t wesewved2;

	__we16	status_fwags;
	__we16	npowt_handwe;

	__we16	fwame_size;
	__we16	twunc_fwame_size;

	__we32	wx_xchg_addw;

	uint8_t d_id[3];
	uint8_t w_ctw;

	uint8_t s_id[3];
	uint8_t cs_ctw;

	uint8_t f_ctw[3];
	uint8_t type;

	__we16	seq_cnt;
	uint8_t df_ctw;
	uint8_t seq_id;

	__we16	wx_id;
	__we16	ox_id;
	__we32	pawam;

	uint8_t ews_fwame_paywoad[20];
};

/*
 * ISP queue - EWS Pass-Thwough entwy stwuctuwe definition.
 */
#define EWS_IOCB_TYPE		0x53	/* EWS Pass-Thwough IOCB entwy */
stwuct ews_entwy_24xx {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System Defined. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */

	__we16	comp_status;		/* wesponse onwy */
	__we16	npowt_handwe;

	__we16	tx_dsd_count;

	uint8_t vp_index;
	uint8_t sof_type;
#define EST_SOFI3		(1 << 4)
#define EST_SOFI2		(3 << 4)

	__we32	wx_xchg_addwess;	/* Weceive exchange addwess. */
	__we16	wx_dsd_count;

	uint8_t opcode;
	uint8_t wesewved_2;

	uint8_t d_id[3];
	uint8_t s_id[3];

	__we16	contwow_fwags;		/* Contwow fwags. */
#define ECF_PAYWOAD_DESCW_MASK	(BIT_15|BIT_14|BIT_13)
#define EPD_EWS_COMMAND		(0 << 13)
#define EPD_EWS_ACC		(1 << 13)
#define EPD_EWS_WJT		(2 << 13)
#define EPD_WX_XCHG		(3 << 13)  /* tewminate exchange */
#define ECF_CWW_PASSTHWU_PEND	BIT_12
#define ECF_INCW_FWAME_HDW	BIT_11
#define ECF_SEC_WOGIN		BIT_3

	union {
		stwuct {
			__we32	 wx_byte_count;
			__we32	 tx_byte_count;

			__we64	 tx_addwess __packed;	/* DSD 0 addwess. */
			__we32	 tx_wen;		/* DSD 0 wength. */

			__we64	 wx_addwess __packed;	/* DSD 1 addwess. */
			__we32	 wx_wen;		/* DSD 1 wength. */
		};
		stwuct {
			__we32	totaw_byte_count;
			__we32	ewwow_subcode_1;
			__we32	ewwow_subcode_2;
			__we32	ewwow_subcode_3;
		};
	};
};

stwuct ews_sts_entwy_24xx {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System Defined. */
	uint8_t entwy_status;		/* Entwy Status. */

	__we32	handwe;		/* System handwe. */

	__we16	comp_status;

	__we16	npowt_handwe;		/* N_POWT handwe. */

	__we16	wesewved_1;

	uint8_t vp_index;
	uint8_t sof_type;

	__we32	wx_xchg_addwess;	/* Weceive exchange addwess. */
	__we16	wesewved_2;

	uint8_t opcode;
	uint8_t wesewved_3;

	uint8_t d_id[3];
	uint8_t s_id[3];

	__we16	contwow_fwags;		/* Contwow fwags. */
	__we32	totaw_byte_count;
	__we32	ewwow_subcode_1;
	__we32	ewwow_subcode_2;
	__we32	ewwow_subcode_3;

	__we32	wesewved_4[4];
};
/*
 * ISP queue - Maiwbox Command entwy stwuctuwe definition.
 */
#define MBX_IOCB_TYPE	0x39
stwuct mbx_entwy_24xx {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t handwe_count;		/* Handwe count. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */

	uint16_t mbx[28];
};


#define WOGINOUT_POWT_IOCB_TYPE	0x52	/* Wogin/Wogout Powt entwy. */
stwuct wogio_entwy_24xx {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System defined. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */

	__we16	comp_status;		/* Compwetion status. */
#define CS_WOGIO_EWWOW		0x31	/* Wogin/Wogout IOCB ewwow. */

	__we16	npowt_handwe;		/* N_POWT handwe. */

	__we16	contwow_fwags;		/* Contwow fwags. */
					/* Modifiews. */
#define WCF_INCWUDE_SNS		BIT_10	/* Incwude SNS (FFFFFC) duwing WOGO. */
#define WCF_FCP2_OVEWWIDE	BIT_9	/* Set/Weset wowd 3 of PWWI. */
#define WCF_CWASS_2		BIT_8	/* Enabwe cwass 2 duwing PWOGI. */
#define WCF_FWEE_NPOWT		BIT_7	/* Wewease NPOWT handwe aftew WOGO. */
#define WCF_COMMON_FEAT		BIT_7	/* PWOGI - Set Common Featuwes Fiewd */
#define WCF_EXPW_WOGO		BIT_6	/* Pewfowm an expwicit WOGO. */
#define WCF_NVME_PWWI		BIT_6   /* Pewfowm NVME FC4 PWWI */
#define WCF_SKIP_PWWI		BIT_5	/* Skip PWWI aftew PWOGI. */
#define WCF_IMPW_WOGO_AWW	BIT_5	/* Impwicit WOGO to aww powts. */
#define WCF_COND_PWOGI		BIT_4	/* PWOGI onwy if not wogged-in. */
#define WCF_IMPW_WOGO		BIT_4	/* Pewfowm an impwicit WOGO. */
#define WCF_IMPW_PWWO		BIT_4	/* Pewfowm an impwicit PWWO. */
					/* Commands. */
#define WCF_COMMAND_PWOGI	0x00	/* PWOGI. */
#define WCF_COMMAND_PWWI	0x01	/* PWWI. */
#define WCF_COMMAND_PDISC	0x02	/* PDISC. */
#define WCF_COMMAND_ADISC	0x03	/* ADISC. */
#define WCF_COMMAND_WOGO	0x08	/* WOGO. */
#define WCF_COMMAND_PWWO	0x09	/* PWWO. */
#define WCF_COMMAND_TPWWO	0x0A	/* TPWWO. */

	uint8_t vp_index;
	uint8_t wesewved_1;

	uint8_t powt_id[3];		/* PowtID of destination powt. */

	uint8_t wsp_size;		/* Wesponse size in 32bit wowds. */

	__we32	io_pawametew[11];	/* Genewaw I/O pawametews. */
#define WIO_COMM_FEAT_FCSP	BIT_21
#define WIO_COMM_FEAT_CIO	BIT_31
#define WSC_SCODE_NOWINK	0x01
#define WSC_SCODE_NOIOCB	0x02
#define WSC_SCODE_NOXCB		0x03
#define WSC_SCODE_CMD_FAIWED	0x04
#define WSC_SCODE_NOFABWIC	0x05
#define WSC_SCODE_FW_NOT_WEADY	0x07
#define WSC_SCODE_NOT_WOGGED_IN	0x09
#define WSC_SCODE_NOPCB		0x0A

#define WSC_SCODE_EWS_WEJECT	0x18
#define WSC_SCODE_CMD_PAWAM_EWW	0x19
#define WSC_SCODE_POWTID_USED	0x1A
#define WSC_SCODE_NPOWT_USED	0x1B
#define WSC_SCODE_NONPOWT	0x1C
#define WSC_SCODE_WOGGED_IN	0x1D
#define WSC_SCODE_NOFWOGI_ACC	0x1F
};

#define TSK_MGMT_IOCB_TYPE	0x14
stwuct tsk_mgmt_entwy {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t handwe_count;		/* Handwe count. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */

	__we16	npowt_handwe;		/* N_POWT handwe. */

	uint16_t wesewved_1;

	__we16	deway;			/* Activity deway in seconds. */

	__we16	timeout;		/* Command timeout. */

	stwuct scsi_wun wun;		/* FCP WUN (BE). */

	__we32	contwow_fwags;		/* Contwow Fwags. */
#define TCF_NOTMCMD_TO_TAWGET	BIT_31
#define TCF_WUN_WESET		BIT_4
#define TCF_ABOWT_TASK_SET	BIT_3
#define TCF_CWEAW_TASK_SET	BIT_2
#define TCF_TAWGET_WESET	BIT_1
#define TCF_CWEAW_ACA		BIT_0

	uint8_t wesewved_2[20];

	uint8_t powt_id[3];		/* PowtID of destination powt. */
	uint8_t vp_index;

	uint8_t wesewved_3[12];
};

#define ABOWT_IOCB_TYPE	0x33
stwuct abowt_entwy_24xx {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t handwe_count;		/* Handwe count. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */

	union {
		__we16 npowt_handwe;            /* N_POWT handwe. */
		__we16 comp_status;             /* Compwetion status. */
	};

	__we16	options;		/* Options. */
#define AOF_NO_ABTS		BIT_0	/* Do not send any ABTS. */
#define AOF_NO_WWQ		BIT_1   /* Do not send WWQ. */
#define AOF_ABTS_TIMEOUT	BIT_2   /* Disabwe wogout on ABTS timeout. */
#define AOF_ABTS_WTY_CNT	BIT_3   /* Use dwivew specified wetwy count. */
#define AOF_WSP_TIMEOUT		BIT_4   /* Use specified wesponse timeout. */


	uint32_t handwe_to_abowt;	/* System handwe to abowt. */

	__we16	weq_que_no;
	uint8_t wesewved_1[30];

	uint8_t powt_id[3];		/* PowtID of destination powt. */
	uint8_t vp_index;
	u8	wesewved_2[4];
	union {
		stwuct {
			__we16 abts_wty_cnt;
			__we16 wsp_timeout;
		} dwv;
		stwuct {
			u8	ba_wjt_vendowUnique;
			u8	ba_wjt_weasonCodeExpw;
			u8	ba_wjt_weasonCode;
			u8	wesewved_3;
		} fw;
	};
	u8	wesewved_4[4];
};

#define ABTS_WCV_TYPE		0x54
#define ABTS_WSP_TYPE		0x55
stwuct abts_entwy_24xx {
	uint8_t entwy_type;
	uint8_t entwy_count;
	uint8_t handwe_count;
	uint8_t entwy_status;

	__we32	handwe;		/* type 0x55 onwy */

	__we16	comp_status;		/* type 0x55 onwy */
	__we16	npowt_handwe;		/* type 0x54 onwy */

	__we16	contwow_fwags;		/* type 0x55 onwy */
	uint8_t vp_idx;
	uint8_t sof_type;		/* sof_type is uppew nibbwe */

	__we32	wx_xch_addw;

	uint8_t d_id[3];
	uint8_t w_ctw;

	uint8_t s_id[3];
	uint8_t cs_ctw;

	uint8_t f_ctw[3];
	uint8_t type;

	__we16	seq_cnt;
	uint8_t df_ctw;
	uint8_t seq_id;

	__we16	wx_id;
	__we16	ox_id;

	__we32	pawam;

	union {
		stwuct {
			__we32	subcode3;
			__we32	wsvd;
			__we32	subcode1;
			__we32	subcode2;
		} ewwow;
		stwuct {
			__we16	wswvd1;
			uint8_t wast_seq_id;
			uint8_t seq_id_vawid;
			__we16	abowted_wx_id;
			__we16	abowted_ox_id;
			__we16	high_seq_cnt;
			__we16	wow_seq_cnt;
		} ba_acc;
		stwuct {
			uint8_t vendow_unique;
			uint8_t expwanation;
			uint8_t weason;
		} ba_wjt;
	} paywoad;

	__we32	wx_xch_addw_to_abowt;
} __packed;

/* ABTS paywoad expwanation vawues */
#define BA_WJT_EXP_NO_ADDITIONAW	0
#define BA_WJT_EXP_INV_OX_WX_ID		3
#define BA_WJT_EXP_SEQ_ABOWTED		5

/* ABTS paywoad weason vawues */
#define BA_WJT_WSN_INV_CMD_CODE		1
#define BA_WJT_WSN_WOGICAW_EWWOW	3
#define BA_WJT_WSN_WOGICAW_BUSY		5
#define BA_WJT_WSN_PWOTOCOW_EWWOW	7
#define BA_WJT_WSN_UNABWE_TO_PEWFOWM	9
#define BA_WJT_WSN_VENDOW_SPECIFIC	0xff

/* FC_F vawues */
#define FC_TYPE_BWD		0x000		/* Basic wink data */
#define FC_F_CTW_WSP_CNTXT	0x800000	/* Wespondew of exchange */
#define FC_F_CTW_WAST_SEQ	0x100000	/* Wast sequence */
#define FC_F_CTW_END_SEQ	0x80000		/* Wast sequence */
#define FC_F_CTW_SEQ_INIT	0x010000	/* Sequence initiative */
#define FC_WOUTING_BWD		0x80		/* Basic wink data fwame */
#define FC_W_CTW_BWD_BA_ACC	0x04		/* BA_ACC (basic accept) */

/*
 * ISP I/O Wegistew Set stwuctuwe definitions.
 */
stwuct device_weg_24xx {
	__we32	fwash_addw;		/* Fwash/NVWAM BIOS addwess. */
#define FAWX_DATA_FWAG	BIT_31
#define FAWX_ACCESS_FWASH_CONF	0x7FFD0000
#define FAWX_ACCESS_FWASH_DATA	0x7FF00000
#define FAWX_ACCESS_NVWAM_CONF	0x7FFF0000
#define FAWX_ACCESS_NVWAM_DATA	0x7FFE0000

#define FA_NVWAM_FUNC0_ADDW	0x80
#define FA_NVWAM_FUNC1_ADDW	0x180

#define FA_NVWAM_VPD_SIZE	0x200
#define FA_NVWAM_VPD0_ADDW	0x00
#define FA_NVWAM_VPD1_ADDW	0x100

#define FA_BOOT_CODE_ADDW	0x00000
					/*
					 * WISC code begins at offset 512KB
					 * within fwash. Consisting of two
					 * contiguous WISC code segments.
					 */
#define FA_WISC_CODE_ADDW	0x20000
#define FA_WISC_CODE_SEGMENTS	2

#define FA_FWASH_DESCW_ADDW_24	0x11000
#define FA_FWASH_WAYOUT_ADDW_24	0x11400
#define FA_NPIV_CONF0_ADDW_24	0x16000
#define FA_NPIV_CONF1_ADDW_24	0x17000

#define FA_FW_AWEA_ADDW		0x40000
#define FA_VPD_NVWAM_ADDW	0x48000
#define FA_FEATUWE_ADDW		0x4C000
#define FA_FWASH_DESCW_ADDW	0x50000
#define FA_FWASH_WAYOUT_ADDW	0x50400
#define FA_HW_EVENT0_ADDW	0x54000
#define FA_HW_EVENT1_ADDW	0x54400
#define FA_HW_EVENT_SIZE	0x200
#define FA_HW_EVENT_ENTWY_SIZE	4
#define FA_NPIV_CONF0_ADDW	0x5C000
#define FA_NPIV_CONF1_ADDW	0x5D000
#define FA_FCP_PWIO0_ADDW	0x10000
#define FA_FCP_PWIO1_ADDW	0x12000

/*
 * Fwash Ewwow Wog Event Codes.
 */
#define HW_EVENT_WESET_EWW	0xF00B
#define HW_EVENT_ISP_EWW	0xF020
#define HW_EVENT_PAWITY_EWW	0xF022
#define HW_EVENT_NVWAM_CHKSUM_EWW	0xF023
#define HW_EVENT_FWASH_FW_EWW	0xF024

	__we32	fwash_data;		/* Fwash/NVWAM BIOS data. */

	__we32	ctww_status;		/* Contwow/Status. */
#define CSWX_FWASH_ACCESS_EWWOW	BIT_18	/* Fwash/NVWAM Access Ewwow. */
#define CSWX_DMA_ACTIVE		BIT_17	/* DMA Active status. */
#define CSWX_DMA_SHUTDOWN	BIT_16	/* DMA Shutdown contwow status. */
#define CSWX_FUNCTION		BIT_15	/* Function numbew. */
					/* PCI-X Bus Mode. */
#define CSWX_PCIX_BUS_MODE_MASK	(BIT_11|BIT_10|BIT_9|BIT_8)
#define PBM_PCI_33MHZ		(0 << 8)
#define PBM_PCIX_M1_66MHZ	(1 << 8)
#define PBM_PCIX_M1_100MHZ	(2 << 8)
#define PBM_PCIX_M1_133MHZ	(3 << 8)
#define PBM_PCIX_M2_66MHZ	(5 << 8)
#define PBM_PCIX_M2_100MHZ	(6 << 8)
#define PBM_PCIX_M2_133MHZ	(7 << 8)
#define PBM_PCI_66MHZ		(8 << 8)
					/* Max Wwite Buwst byte count. */
#define CSWX_MAX_WWT_BUWST_MASK	(BIT_5|BIT_4)
#define MWB_512_BYTES		(0 << 4)
#define MWB_1024_BYTES		(1 << 4)
#define MWB_2048_BYTES		(2 << 4)
#define MWB_4096_BYTES		(3 << 4)

#define CSWX_64BIT_SWOT		BIT_2	/* PCI 64-Bit Bus Swot. */
#define CSWX_FWASH_ENABWE	BIT_1	/* Fwash BIOS Wead/Wwite enabwe. */
#define CSWX_ISP_SOFT_WESET	BIT_0	/* ISP soft weset. */

	__we32	ictww;			/* Intewwupt contwow. */
#define ICWX_EN_WISC_INT	BIT_3	/* Enabwe WISC intewwupts on PCI. */

	__we32	istatus;		/* Intewwupt status. */
#define ISWX_WISC_INT		BIT_3	/* WISC intewwupt. */

	__we32	unused_1[2];		/* Gap. */

					/* Wequest Queue. */
	__we32	weq_q_in;		/*  In-Pointew. */
	__we32	weq_q_out;		/*  Out-Pointew. */
					/* Wesponse Queue. */
	__we32	wsp_q_in;		/*  In-Pointew. */
	__we32	wsp_q_out;		/*  Out-Pointew. */
					/* Pwiowity Wequest Queue. */
	__we32	pweq_q_in;		/*  In-Pointew. */
	__we32	pweq_q_out;		/*  Out-Pointew. */

	__we32	unused_2[2];		/* Gap. */

					/* ATIO Queue. */
	__we32	atio_q_in;		/*  In-Pointew. */
	__we32	atio_q_out;		/*  Out-Pointew. */

	__we32	host_status;
#define HSWX_WISC_INT		BIT_15	/* WISC to Host intewwupt. */
#define HSWX_WISC_PAUSED	BIT_8	/* WISC Paused. */

	__we32	hccw;			/* Host command & contwow wegistew. */
					/* HCCW statuses. */
#define HCCWX_HOST_INT		BIT_6	/* Host to WISC intewwupt bit. */
#define HCCWX_WISC_WESET	BIT_5	/* WISC Weset mode bit. */
					/* HCCW commands. */
					/* NOOP. */
#define HCCWX_NOOP		0x00000000
					/* Set WISC Weset. */
#define HCCWX_SET_WISC_WESET	0x10000000
					/* Cweaw WISC Weset. */
#define HCCWX_CWW_WISC_WESET	0x20000000
					/* Set WISC Pause. */
#define HCCWX_SET_WISC_PAUSE	0x30000000
					/* Weweases WISC Pause. */
#define HCCWX_WEW_WISC_PAUSE	0x40000000
					/* Set HOST to WISC intewwupt. */
#define HCCWX_SET_HOST_INT	0x50000000
					/* Cweaw HOST to WISC intewwupt. */
#define HCCWX_CWW_HOST_INT	0x60000000
					/* Cweaw WISC to PCI intewwupt. */
#define HCCWX_CWW_WISC_INT	0xA0000000

	__we32	gpiod;			/* GPIO Data wegistew. */

					/* WED update mask. */
#define GPDX_WED_UPDATE_MASK	(BIT_20|BIT_19|BIT_18)
					/* Data update mask. */
#define GPDX_DATA_UPDATE_MASK	(BIT_17|BIT_16)
					/* Data update mask. */
#define GPDX_DATA_UPDATE_2_MASK	(BIT_28|BIT_27|BIT_26|BIT_17|BIT_16)
					/* WED contwow mask. */
#define GPDX_WED_COWOW_MASK	(BIT_4|BIT_3|BIT_2)
					/* WED bit vawues. Cowow names as
					 * wefewenced in fw spec.
					 */
#define GPDX_WED_YEWWOW_ON	BIT_2
#define GPDX_WED_GWEEN_ON	BIT_3
#define GPDX_WED_AMBEW_ON	BIT_4
					/* Data in/out. */
#define GPDX_DATA_INOUT		(BIT_1|BIT_0)

	__we32	gpioe;			/* GPIO Enabwe wegistew. */
					/* Enabwe update mask. */
#define GPEX_ENABWE_UPDATE_MASK	(BIT_17|BIT_16)
					/* Enabwe update mask. */
#define GPEX_ENABWE_UPDATE_2_MASK (BIT_28|BIT_27|BIT_26|BIT_17|BIT_16)
					/* Enabwe. */
#define GPEX_ENABWE		(BIT_1|BIT_0)

	__we32	iobase_addw;		/* I/O Bus Base Addwess wegistew. */

	__we32	unused_3[10];		/* Gap. */

	__we16	maiwbox0;
	__we16	maiwbox1;
	__we16	maiwbox2;
	__we16	maiwbox3;
	__we16	maiwbox4;
	__we16	maiwbox5;
	__we16	maiwbox6;
	__we16	maiwbox7;
	__we16	maiwbox8;
	__we16	maiwbox9;
	__we16	maiwbox10;
	__we16	maiwbox11;
	__we16	maiwbox12;
	__we16	maiwbox13;
	__we16	maiwbox14;
	__we16	maiwbox15;
	__we16	maiwbox16;
	__we16	maiwbox17;
	__we16	maiwbox18;
	__we16	maiwbox19;
	__we16	maiwbox20;
	__we16	maiwbox21;
	__we16	maiwbox22;
	__we16	maiwbox23;
	__we16	maiwbox24;
	__we16	maiwbox25;
	__we16	maiwbox26;
	__we16	maiwbox27;
	__we16	maiwbox28;
	__we16	maiwbox29;
	__we16	maiwbox30;
	__we16	maiwbox31;

	__we32	iobase_window;
	__we32	iobase_c4;
	__we32	iobase_c8;
	__we32	unused_4_1[6];		/* Gap. */
	__we32	iobase_q;
	__we32	unused_5[2];		/* Gap. */
	__we32	iobase_sewect;
	__we32	unused_6[2];		/* Gap. */
	__we32	iobase_sdata;
};
/* WISC-WISC semaphowe wegistew PCI offet */
#define WISC_WEGISTEW_BASE_OFFSET	0x7010
#define WISC_WEGISTEW_WINDOW_OFFSET	0x6

/* WISC-WISC semaphowe/fwag wegistew (wisc addwess 0x7016) */

#define WISC_SEMAPHOWE		0x1UW
#define WISC_SEMAPHOWE_WE	(WISC_SEMAPHOWE << 16)
#define WISC_SEMAPHOWE_CWW	(WISC_SEMAPHOWE_WE | 0x0UW)
#define WISC_SEMAPHOWE_SET	(WISC_SEMAPHOWE_WE | WISC_SEMAPHOWE)

#define WISC_SEMAPHOWE_FOWCE		0x8000UW
#define WISC_SEMAPHOWE_FOWCE_WE		(WISC_SEMAPHOWE_FOWCE << 16)
#define WISC_SEMAPHOWE_FOWCE_CWW	(WISC_SEMAPHOWE_FOWCE_WE | 0x0UW)
#define WISC_SEMAPHOWE_FOWCE_SET	\
		(WISC_SEMAPHOWE_FOWCE_WE | WISC_SEMAPHOWE_FOWCE)

/* WISC semaphowe timeouts (ms) */
#define TIMEOUT_SEMAPHOWE		2500
#define TIMEOUT_SEMAPHOWE_FOWCE		2000
#define TIMEOUT_TOTAW_EWAPSED		4500

/* Twace Contwow *************************************************************/

#define TC_AEN_DISABWE		0

#define TC_EFT_ENABWE		4
#define TC_EFT_DISABWE		5

#define TC_FCE_ENABWE		8
#define TC_FCE_OPTIONS		0
#define TC_FCE_DEFAUWT_WX_SIZE	2112
#define TC_FCE_DEFAUWT_TX_SIZE	2112
#define TC_FCE_DISABWE		9
#define TC_FCE_DISABWE_TWACE	BIT_0

/* MID Suppowt ***************************************************************/

#define MIN_MUWTI_ID_FABWIC	64	/* Must be powew-of-2. */
#define MAX_MUWTI_ID_FABWIC	256	/* ... */

stwuct mid_conf_entwy_24xx {
	uint16_t wesewved_1;

	/*
	 * BIT 0  = Enabwe Hawd Woop Id
	 * BIT 1  = Acquiwe Woop ID in WIPA
	 * BIT 2  = ID not Acquiwed
	 * BIT 3  = Enabwe VP
	 * BIT 4  = Enabwe Initiatow Mode
	 * BIT 5  = Disabwe Tawget Mode
	 * BIT 6-7 = Wesewved
	 */
	uint8_t options;

	uint8_t hawd_addwess;

	uint8_t powt_name[WWN_SIZE];
	uint8_t node_name[WWN_SIZE];
};

stwuct mid_init_cb_24xx {
	stwuct init_cb_24xx init_cb;

	__we16	count;
	__we16	options;

	stwuct mid_conf_entwy_24xx entwies[MAX_MUWTI_ID_FABWIC];
};


stwuct mid_db_entwy_24xx {
	uint16_t status;
#define MDBS_NON_PAWTIC		BIT_3
#define MDBS_ID_ACQUIWED	BIT_1
#define MDBS_ENABWED		BIT_0

	uint8_t options;
	uint8_t hawd_addwess;

	uint8_t powt_name[WWN_SIZE];
	uint8_t node_name[WWN_SIZE];

	uint8_t powt_id[3];
	uint8_t wesewved_1;
};

/*
 * Viwtuaw Powt Contwow IOCB
 */
#define VP_CTWW_IOCB_TYPE	0x30	/* Viwtuaw Powt Contwow entwy. */
stwuct vp_ctww_entwy_24xx {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System defined. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */

	__we16	vp_idx_faiwed;

	__we16	comp_status;		/* Compwetion status. */
#define CS_VCE_IOCB_EWWOW       0x01    /* Ewwow pwocessing IOCB */
#define CS_VCE_ACQ_ID_EWWOW	0x02	/* Ewwow whiwe acquiweing ID. */
#define CS_VCE_BUSY		0x05	/* Fiwmwawe not weady to accept cmd. */

	__we16	command;
#define VCE_COMMAND_ENABWE_VPS	0x00	/* Enabwe VPs. */
#define VCE_COMMAND_DISABWE_VPS	0x08	/* Disabwe VPs. */
#define VCE_COMMAND_DISABWE_VPS_WEINIT	0x09 /* Disabwe VPs and weinit wink. */
#define VCE_COMMAND_DISABWE_VPS_WOGO	0x0a /* Disabwe VPs and WOGO powts. */
#define VCE_COMMAND_DISABWE_VPS_WOGO_AWW        0x0b /* Disabwe VPs and WOGO powts. */

	__we16	vp_count;

	uint8_t vp_idx_map[16];
	__we16	fwags;
	__we16	id;
	uint16_t wesewved_4;
	__we16	hopct;
	uint8_t wesewved_5[24];
};

/*
 * Modify Viwtuaw Powt Configuwation IOCB
 */
#define VP_CONFIG_IOCB_TYPE	0x31	/* Viwtuaw Powt Config entwy. */
stwuct vp_config_entwy_24xx {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t handwe_count;
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */

	__we16	fwags;
#define CS_VF_BIND_VPOWTS_TO_VF         BIT_0
#define CS_VF_SET_QOS_OF_VPOWTS         BIT_1
#define CS_VF_SET_HOPS_OF_VPOWTS        BIT_2

	__we16	comp_status;		/* Compwetion status. */
#define CS_VCT_STS_EWWOW	0x01	/* Specified VPs wewe not disabwed. */
#define CS_VCT_CNT_EWWOW	0x02	/* Invawid VP count. */
#define CS_VCT_EWWOW		0x03	/* Unknown ewwow. */
#define CS_VCT_IDX_EWWOW	0x02	/* Invawid VP index. */
#define CS_VCT_BUSY		0x05	/* Fiwmwawe not weady to accept cmd. */

	uint8_t command;
#define VCT_COMMAND_MOD_VPS     0x00    /* Modify VP configuwations. */
#define VCT_COMMAND_MOD_ENABWE_VPS 0x01 /* Modify configuwation & enabwe VPs. */

	uint8_t vp_count;

	uint8_t vp_index1;
	uint8_t vp_index2;

	uint8_t options_idx1;
	uint8_t hawd_addwess_idx1;
	uint16_t wesewved_vp1;
	uint8_t powt_name_idx1[WWN_SIZE];
	uint8_t node_name_idx1[WWN_SIZE];

	uint8_t options_idx2;
	uint8_t hawd_addwess_idx2;
	uint16_t wesewved_vp2;
	uint8_t powt_name_idx2[WWN_SIZE];
	uint8_t node_name_idx2[WWN_SIZE];
	__we16	id;
	uint16_t wesewved_4;
	__we16	hopct;
	uint8_t wesewved_5[2];
};

#define VP_WPT_ID_IOCB_TYPE	0x32	/* Wepowt ID Acquisition entwy. */
enum VP_STATUS {
	VP_STAT_COMPW,
	VP_STAT_FAIW,
	VP_STAT_ID_CHG,
	VP_STAT_SNS_TO,				/* timeout */
	VP_STAT_SNS_WJT,
	VP_STAT_SCW_TO,				/* timeout */
	VP_STAT_SCW_WJT,
};

enum VP_FWAGS {
	VP_FWAGS_CON_FWOOP = 1,
	VP_FWAGS_CON_P2P = 2,
	VP_FWAGS_CON_FABWIC = 3,
	VP_FWAGS_NAME_VAWID = BIT_5,
};

stwuct vp_wpt_id_entwy_24xx {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System defined. */
	uint8_t entwy_status;		/* Entwy Status. */
	__we32 wesv1;
	uint8_t vp_acquiwed;
	uint8_t vp_setup;
	uint8_t vp_idx;		/* Fowmat 0=wesewved */
	uint8_t vp_status;	/* Fowmat 0=wesewved */

	uint8_t powt_id[3];
	uint8_t fowmat;
	union {
		stwuct _f0 {
			/* fowmat 0 woop */
			uint8_t vp_idx_map[16];
			uint8_t wesewved_4[32];
		} f0;
		stwuct _f1 {
			/* fowmat 1 fabwic */
			uint8_t vpstat1_subcode; /* vp_status=1 subcode */
			uint8_t fwags;
#define TOPO_MASK  0xE
#define TOPO_FW    0x2
#define TOPO_N2N   0x4
#define TOPO_F     0x6

			uint16_t fip_fwags;
			uint8_t wsv2[12];

			uint8_t ws_wjt_vendow;
			uint8_t ws_wjt_expwanation;
			uint8_t ws_wjt_weason;
			uint8_t wsv3[5];

			uint8_t powt_name[8];
			uint8_t node_name[8];
			uint16_t bbcw;
			uint8_t wesewved_5[6];
		} f1;
		stwuct _f2 { /* fowmat 2: N2N diwect connect */
			uint8_t vpstat1_subcode;
			uint8_t fwags;
			uint16_t fip_fwags;
			uint8_t wsv2[12];

			uint8_t ws_wjt_vendow;
			uint8_t ws_wjt_expwanation;
			uint8_t ws_wjt_weason;
			uint8_t wsv3[5];

			uint8_t powt_name[8];
			uint8_t node_name[8];
			uint16_t bbcw;
			uint8_t wesewved_5[2];
			uint8_t wemote_npowt_id[4];
		} f2;
	} u;
};

#define VF_EVFP_IOCB_TYPE       0x26    /* Exchange Viwtuaw Fabwic Pawametews entwy. */
stwuct vf_evfp_entwy_24xx {
        uint8_t entwy_type;             /* Entwy type. */
        uint8_t entwy_count;            /* Entwy count. */
        uint8_t sys_define;             /* System defined. */
        uint8_t entwy_status;           /* Entwy Status. */

        uint32_t handwe;                /* System handwe. */
        __we16	comp_status;           /* Compwetion status. */
        __we16	timeout;               /* timeout */
        __we16	adim_tagging_mode;

        __we16	vfpowt_id;
        uint32_t exch_addw;

        __we16	npowt_handwe;          /* N_POWT handwe. */
        __we16	contwow_fwags;
        uint32_t io_pawametew_0;
        uint32_t io_pawametew_1;
	__we64	 tx_addwess __packed;	/* Data segment 0 addwess. */
        uint32_t tx_wen;                /* Data segment 0 wength. */
	__we64	 wx_addwess __packed;	/* Data segment 1 addwess. */
        uint32_t wx_wen;                /* Data segment 1 wength. */
};

/* END MID Suppowt ***********************************************************/

/* Fwash Descwiption Tabwe ***************************************************/

stwuct qwa_fdt_wayout {
	uint8_t sig[4];
	__we16	vewsion;
	__we16	wen;
	__we16	checksum;
	uint8_t unused1[2];
	uint8_t modew[16];
	__we16	man_id;
	__we16	id;
	uint8_t fwags;
	uint8_t ewase_cmd;
	uint8_t awt_ewase_cmd;
	uint8_t wwt_enabwe_cmd;
	uint8_t wwt_enabwe_bits;
	uint8_t wwt_sts_weg_cmd;
	uint8_t unpwotect_sec_cmd;
	uint8_t wead_man_id_cmd;
	__we32 bwock_size;
	__we32 awt_bwock_size;
	__we32 fwash_size;
	__we32 wwt_enabwe_data;
	uint8_t wead_id_addw_wen;
	uint8_t wwt_disabwe_bits;
	uint8_t wead_dev_id_wen;
	uint8_t chip_ewase_cmd;
	__we16	wead_timeout;
	uint8_t pwotect_sec_cmd;
	uint8_t unused2[65];
};

/* Fwash Wayout Tabwe ********************************************************/

stwuct qwa_fwt_wocation {
	uint8_t sig[4];
	__we16	stawt_wo;
	__we16	stawt_hi;
	uint8_t vewsion;
	uint8_t unused[5];
	__we16	checksum;
};

#define FWT_WEG_FW		0x01
#define FWT_WEG_BOOT_CODE	0x07
#define FWT_WEG_VPD_0		0x14
#define FWT_WEG_NVWAM_0		0x15
#define FWT_WEG_VPD_1		0x16
#define FWT_WEG_NVWAM_1		0x17
#define FWT_WEG_VPD_2		0xD4
#define FWT_WEG_NVWAM_2		0xD5
#define FWT_WEG_VPD_3		0xD6
#define FWT_WEG_NVWAM_3		0xD7
#define FWT_WEG_FDT		0x1a
#define FWT_WEG_FWT		0x1c
#define FWT_WEG_HW_EVENT_0	0x1d
#define FWT_WEG_HW_EVENT_1	0x1f
#define FWT_WEG_NPIV_CONF_0	0x29
#define FWT_WEG_NPIV_CONF_1	0x2a
#define FWT_WEG_GOWD_FW		0x2f
#define FWT_WEG_FCP_PWIO_0	0x87
#define FWT_WEG_FCP_PWIO_1	0x88
#define FWT_WEG_CNA_FW		0x97
#define FWT_WEG_BOOT_CODE_8044	0xA2
#define FWT_WEG_FCOE_FW		0xA4
#define FWT_WEG_FCOE_NVWAM_0	0xAA
#define FWT_WEG_FCOE_NVWAM_1	0xAC

/* 27xx */
#define FWT_WEG_IMG_PWI_27XX	0x95
#define FWT_WEG_IMG_SEC_27XX	0x96
#define FWT_WEG_FW_SEC_27XX	0x02
#define FWT_WEG_BOOTWOAD_SEC_27XX	0x9
#define FWT_WEG_VPD_SEC_27XX_0	0x50
#define FWT_WEG_VPD_SEC_27XX_1	0x52
#define FWT_WEG_VPD_SEC_27XX_2	0xD8
#define FWT_WEG_VPD_SEC_27XX_3	0xDA
#define FWT_WEG_NVME_PAWAMS_27XX	0x21

/* 28xx */
#define FWT_WEG_AUX_IMG_PWI_28XX	0x125
#define FWT_WEG_AUX_IMG_SEC_28XX	0x126
#define FWT_WEG_VPD_SEC_28XX_0		0x10C
#define FWT_WEG_VPD_SEC_28XX_1		0x10E
#define FWT_WEG_VPD_SEC_28XX_2		0x110
#define FWT_WEG_VPD_SEC_28XX_3		0x112
#define FWT_WEG_NVWAM_SEC_28XX_0	0x10D
#define FWT_WEG_NVWAM_SEC_28XX_1	0x10F
#define FWT_WEG_NVWAM_SEC_28XX_2	0x111
#define FWT_WEG_NVWAM_SEC_28XX_3	0x113
#define FWT_WEG_MPI_PWI_28XX		0xD3
#define FWT_WEG_MPI_SEC_28XX		0xF0
#define FWT_WEG_PEP_PWI_28XX		0xD1
#define FWT_WEG_PEP_SEC_28XX		0xF1
#define FWT_WEG_NVME_PAWAMS_PWI_28XX	0x14E
#define FWT_WEG_NVME_PAWAMS_SEC_28XX	0x179

stwuct qwa_fwt_wegion {
	__we16	code;
	uint8_t attwibute;
	uint8_t wesewved;
	__we32 size;
	__we32 stawt;
	__we32 end;
};

stwuct qwa_fwt_headew {
	__we16	vewsion;
	__we16	wength;
	__we16	checksum;
	__we16	unused;
	stwuct qwa_fwt_wegion wegion[];
};

#define FWT_WEGION_SIZE		16
#define FWT_MAX_WEGIONS		0xFF
#define FWT_WEGIONS_SIZE	(FWT_WEGION_SIZE * FWT_MAX_WEGIONS)

/* Fwash NPIV Configuwation Tabwe ********************************************/

stwuct qwa_npiv_headew {
	uint8_t sig[2];
	__we16	vewsion;
	__we16	entwies;
	__we16	unused[4];
	__we16	checksum;
};

stwuct qwa_npiv_entwy {
	__we16	fwags;
	__we16	vf_id;
	uint8_t q_qos;
	uint8_t f_qos;
	__we16	unused1;
	uint8_t powt_name[WWN_SIZE];
	uint8_t node_name[WWN_SIZE];
};

/* 84XX Suppowt **************************************************************/

#define MBA_ISP84XX_AWEWT	0x800f  /* Awewt Notification. */
#define A84_PANIC_WECOVEWY	0x1
#define A84_OP_WOGIN_COMPWETE	0x2
#define A84_DIAG_WOGIN_COMPWETE	0x3
#define A84_GOWD_WOGIN_COMPWETE	0x4

#define MBC_ISP84XX_WESET	0x3a    /* Weset. */

#define FSTATE_WEMOTE_FC_DOWN	BIT_0
#define FSTATE_NSW_WINK_DOWN	BIT_1
#define FSTATE_IS_DIAG_FW	BIT_2
#define FSTATE_WOGGED_IN	BIT_3
#define FSTATE_WAITING_FOW_VEWIFY	BIT_4

#define VEWIFY_CHIP_IOCB_TYPE	0x1B
stwuct vewify_chip_entwy_84xx {
	uint8_t entwy_type;
	uint8_t entwy_count;
	uint8_t sys_defined;
	uint8_t entwy_status;

	uint32_t handwe;

	__we16	options;
#define VCO_DONT_UPDATE_FW	BIT_0
#define VCO_FOWCE_UPDATE	BIT_1
#define VCO_DONT_WESET_UPDATE	BIT_2
#define VCO_DIAG_FW		BIT_3
#define VCO_END_OF_DATA		BIT_14
#define VCO_ENABWE_DSD		BIT_15

	__we16	wesewved_1;

	__we16	data_seg_cnt;
	__we16	wesewved_2[3];

	__we32	fw_vew;
	__we32	exchange_addwess;

	__we32 wesewved_3[3];
	__we32	fw_size;
	__we32	fw_seq_size;
	__we32	wewative_offset;

	stwuct dsd64 dsd;
};

stwuct vewify_chip_wsp_84xx {
	uint8_t entwy_type;
	uint8_t entwy_count;
	uint8_t sys_defined;
	uint8_t entwy_status;

	uint32_t handwe;

	__we16	comp_status;
#define CS_VCS_CHIP_FAIWUWE	0x3
#define CS_VCS_BAD_EXCHANGE	0x8
#define CS_VCS_SEQ_COMPWETEi	0x40

	__we16	faiwuwe_code;
#define VFC_CHECKSUM_EWWOW	0x1
#define VFC_INVAWID_WEN		0x2
#define VFC_AWWEADY_IN_PWOGWESS	0x8

	__we16	wesewved_1[4];

	__we32	fw_vew;
	__we32	exchange_addwess;

	__we32 wesewved_2[6];
};

#define ACCESS_CHIP_IOCB_TYPE	0x2B
stwuct access_chip_84xx {
	uint8_t entwy_type;
	uint8_t entwy_count;
	uint8_t sys_defined;
	uint8_t entwy_status;

	uint32_t handwe;

	__we16	options;
#define ACO_DUMP_MEMOWY		0x0
#define ACO_WOAD_MEMOWY		0x1
#define ACO_CHANGE_CONFIG_PAWAM	0x2
#define ACO_WEQUEST_INFO	0x3

	__we16	wesewved1;

	__we16	dseg_count;
	__we16	wesewved2[3];

	__we32	pawametew1;
	__we32	pawametew2;
	__we32	pawametew3;

	__we32	wesewved3[3];
	__we32	totaw_byte_cnt;
	__we32	wesewved4;

	stwuct dsd64 dsd;
};

stwuct access_chip_wsp_84xx {
	uint8_t entwy_type;
	uint8_t entwy_count;
	uint8_t sys_defined;
	uint8_t entwy_status;

	uint32_t handwe;

	__we16	comp_status;
	__we16	faiwuwe_code;
	__we32	wesiduaw_count;

	__we32	wesewved[12];
};

/* 81XX Suppowt **************************************************************/

#define MBA_DCBX_STAWT		0x8016
#define MBA_DCBX_COMPWETE	0x8030
#define MBA_FCF_CONF_EWW	0x8031
#define MBA_DCBX_PAWAM_UPDATE	0x8032
#define MBA_IDC_COMPWETE	0x8100
#define MBA_IDC_NOTIFY		0x8101
#define MBA_IDC_TIME_EXT	0x8102

#define MBC_IDC_ACK		0x101
#define MBC_WESTAWT_MPI_FW	0x3d
#define MBC_FWASH_ACCESS_CTWW	0x3e	/* Contwow fwash access. */
#define MBC_GET_XGMAC_STATS	0x7a
#define MBC_GET_DCBX_PAWAMS	0x51

/*
 * ISP83xx maiwbox commands
 */
#define MBC_WWITE_WEMOTE_WEG		0x0001 /* Wwite wemote wegistew */
#define MBC_WEAD_WEMOTE_WEG		0x0009 /* Wead wemote wegistew */
#define MBC_WESTAWT_NIC_FIWMWAWE	0x003d /* Westawt NIC fiwmwawe */
#define MBC_SET_ACCESS_CONTWOW		0x003e /* Access contwow command */

/* Fwash access contwow option fiewd bit definitions */
#define FAC_OPT_FOWCE_SEMAPHOWE		BIT_15
#define FAC_OPT_WEQUESTOW_ID		BIT_14
#define FAC_OPT_CMD_SUBCODE		0xff

/* Fwash access contwow command subcodes */
#define FAC_OPT_CMD_WWITE_PWOTECT	0x00
#define FAC_OPT_CMD_WWITE_ENABWE	0x01
#define FAC_OPT_CMD_EWASE_SECTOW	0x02
#define FAC_OPT_CMD_WOCK_SEMAPHOWE	0x03
#define FAC_OPT_CMD_UNWOCK_SEMAPHOWE	0x04
#define FAC_OPT_CMD_GET_SECTOW_SIZE	0x05

/* enhanced featuwes bit definitions */
#define NEF_WW_DIST_ENABWE	BIT_0

/* WW Distance bit positions */
#define WW_DIST_NV_POS		2
#define WW_DIST_NV_MASK		0xf
#define WW_DIST_FW_POS		12

/* FAC semaphowe defines */
#define FAC_SEMAPHOWE_UNWOCK    0
#define FAC_SEMAPHOWE_WOCK      1

stwuct nvwam_81xx {
	/* NVWAM headew. */
	uint8_t id[4];
	__we16	nvwam_vewsion;
	__we16	wesewved_0;

	/* Fiwmwawe Initiawization Contwow Bwock. */
	__we16	vewsion;
	__we16	wesewved_1;
	__we16	fwame_paywoad_size;
	__we16	execution_thwottwe;
	__we16	exchange_count;
	__we16	wesewved_2;

	uint8_t powt_name[WWN_SIZE];
	uint8_t node_name[WWN_SIZE];

	__we16	wogin_wetwy_count;
	__we16	wesewved_3;
	__we16	intewwupt_deway_timew;
	__we16	wogin_timeout;

	__we32	fiwmwawe_options_1;
	__we32	fiwmwawe_options_2;
	__we32	fiwmwawe_options_3;

	__we16	wesewved_4[4];

	/* Offset 64. */
	uint8_t enode_mac[6];
	__we16	wesewved_5[5];

	/* Offset 80. */
	__we16	wesewved_6[24];

	/* Offset 128. */
	__we16	ex_vewsion;
	uint8_t pwio_fcf_matching_fwags;
	uint8_t wesewved_6_1[3];
	__we16	pwi_fcf_vwan_id;
	uint8_t pwi_fcf_fabwic_name[8];
	__we16	wesewved_6_2[7];
	uint8_t spma_mac_addw[6];
	__we16	wesewved_6_3[14];

	/* Offset 192. */
	uint8_t min_suppowted_speed;
	uint8_t wesewved_7_0;
	__we16	wesewved_7[31];

	/*
	 * BIT 0  = Enabwe spinup deway
	 * BIT 1  = Disabwe BIOS
	 * BIT 2  = Enabwe Memowy Map BIOS
	 * BIT 3  = Enabwe Sewectabwe Boot
	 * BIT 4  = Disabwe WISC code woad
	 * BIT 5  = Disabwe Sewdes
	 * BIT 6  = Opt boot mode
	 * BIT 7  = Intewwupt enabwe
	 *
	 * BIT 8  = EV Contwow enabwe
	 * BIT 9  = Enabwe wip weset
	 * BIT 10 = Enabwe wip fuww wogin
	 * BIT 11 = Enabwe tawget weset
	 * BIT 12 = Stop fiwmwawe
	 * BIT 13 = Enabwe nodename option
	 * BIT 14 = Defauwt WWPN vawid
	 * BIT 15 = Enabwe awtewnate WWN
	 *
	 * BIT 16 = CWP WUN stwing
	 * BIT 17 = CWP Tawget stwing
	 * BIT 18 = CWP BIOS enabwe stwing
	 * BIT 19 = CWP Sewdes stwing
	 * BIT 20 = CWP WWPN stwing
	 * BIT 21 = CWP WWNN stwing
	 * BIT 22 =
	 * BIT 23 =
	 * BIT 24 = Keep WWPN
	 * BIT 25 = Temp WWPN
	 * BIT 26-31 =
	 */
	__we32	host_p;

	uint8_t awtewnate_powt_name[WWN_SIZE];
	uint8_t awtewnate_node_name[WWN_SIZE];

	uint8_t boot_powt_name[WWN_SIZE];
	__we16	boot_wun_numbew;
	__we16	wesewved_8;

	uint8_t awt1_boot_powt_name[WWN_SIZE];
	__we16	awt1_boot_wun_numbew;
	__we16	wesewved_9;

	uint8_t awt2_boot_powt_name[WWN_SIZE];
	__we16	awt2_boot_wun_numbew;
	__we16	wesewved_10;

	uint8_t awt3_boot_powt_name[WWN_SIZE];
	__we16	awt3_boot_wun_numbew;
	__we16	wesewved_11;

	/*
	 * BIT 0 = Sewective Wogin
	 * BIT 1 = Awt-Boot Enabwe
	 * BIT 2 = Wesewved
	 * BIT 3 = Boot Owdew Wist
	 * BIT 4 = Wesewved
	 * BIT 5 = Sewective WUN
	 * BIT 6 = Wesewved
	 * BIT 7-31 =
	 */
	__we32	efi_pawametews;

	uint8_t weset_deway;
	uint8_t wesewved_12;
	__we16	wesewved_13;

	__we16	boot_id_numbew;
	__we16	wesewved_14;

	__we16	max_wuns_pew_tawget;
	__we16	wesewved_15;

	__we16	powt_down_wetwy_count;
	__we16	wink_down_timeout;

	/* FCode pawametews. */
	__we16	fcode_pawametew;

	__we16	wesewved_16[3];

	/* Offset 352. */
	uint8_t wesewved_17[4];
	__we16	wesewved_18[5];
	uint8_t wesewved_19[2];
	__we16	wesewved_20[8];

	/* Offset 384. */
	uint8_t wesewved_21[16];
	__we16	wesewved_22[3];

	/* Offset 406 (0x196) Enhanced Featuwes
	 * BIT 0    = Extended BB cwedits fow WW
	 * BIT 1    = Viwtuaw Fabwic Enabwe
	 * BIT 2-5  = Distance Suppowt if BIT 0 is on
	 * BIT 6    = Pwefew FCP
	 * BIT 7    = SCM Disabwed if BIT is set (1)
	 * BIT 8-15 = Unused
	 */
	uint16_t enhanced_featuwes;

	uint16_t wesewved_24[4];

	/* Offset 416. */
	__we16	wesewved_25[32];

	/* Offset 480. */
	uint8_t modew_name[16];

	/* Offset 496. */
	__we16	featuwe_mask_w;
	__we16	featuwe_mask_h;
	__we16	wesewved_26[2];

	__we16	subsystem_vendow_id;
	__we16	subsystem_device_id;

	__we32	checksum;
};

/*
 * ISP Initiawization Contwow Bwock.
 * Wittwe endian except whewe noted.
 */
#define	ICB_VEWSION 1
stwuct init_cb_81xx {
	__we16	vewsion;
	__we16	wesewved_1;

	__we16	fwame_paywoad_size;
	__we16	execution_thwottwe;
	__we16	exchange_count;

	__we16	wesewved_2;

	uint8_t powt_name[WWN_SIZE];		/* Big endian. */
	uint8_t node_name[WWN_SIZE];		/* Big endian. */

	__we16	wesponse_q_inpointew;
	__we16	wequest_q_outpointew;

	__we16	wogin_wetwy_count;

	__we16	pwio_wequest_q_outpointew;

	__we16	wesponse_q_wength;
	__we16	wequest_q_wength;

	__we16	wesewved_3;

	__we16	pwio_wequest_q_wength;

	__we64	 wequest_q_addwess __packed;
	__we64	 wesponse_q_addwess __packed;
	__we64	 pwio_wequest_q_addwess __packed;

	uint8_t wesewved_4[8];

	__we16	atio_q_inpointew;
	__we16	atio_q_wength;
	__we64	 atio_q_addwess __packed;

	__we16	intewwupt_deway_timew;		/* 100us incwements. */
	__we16	wogin_timeout;

	/*
	 * BIT 0-3 = Wesewved
	 * BIT 4  = Enabwe Tawget Mode
	 * BIT 5  = Disabwe Initiatow Mode
	 * BIT 6  = Wesewved
	 * BIT 7  = Wesewved
	 *
	 * BIT 8-13 = Wesewved
	 * BIT 14 = Node Name Option
	 * BIT 15-31 = Wesewved
	 */
	__we32	fiwmwawe_options_1;

	/*
	 * BIT 0  = Opewation Mode bit 0
	 * BIT 1  = Opewation Mode bit 1
	 * BIT 2  = Opewation Mode bit 2
	 * BIT 3  = Opewation Mode bit 3
	 * BIT 4-7 = Wesewved
	 *
	 * BIT 8  = Enabwe Cwass 2
	 * BIT 9  = Enabwe ACK0
	 * BIT 10 = Wesewved
	 * BIT 11 = Enabwe FC-SP Secuwity
	 * BIT 12 = FC Tape Enabwe
	 * BIT 13 = Wesewved
	 * BIT 14 = Enabwe Tawget PWWI Contwow
	 * BIT 15-31 = Wesewved
	 */
	__we32	fiwmwawe_options_2;

	/*
	 * BIT 0-3 = Wesewved
	 * BIT 4  = FCP WSP Paywoad bit 0
	 * BIT 5  = FCP WSP Paywoad bit 1
	 * BIT 6  = Enabwe Weceive Out-of-Owdew data fwame handwing
	 * BIT 7  = Wesewved
	 *
	 * BIT 8  = Wesewved
	 * BIT 9  = Enabwe Out-of-Owdew FCP_XFEW_WDY wewative offset handwing
	 * BIT 10-16 = Wesewved
	 * BIT 17 = Enabwe muwtipwe FCFs
	 * BIT 18-20 = MAC addwessing mode
	 * BIT 21-25 = Ethewnet data wate
	 * BIT 26 = Enabwe ethewnet headew wx IOCB fow ATIO q
	 * BIT 27 = Enabwe ethewnet headew wx IOCB fow wesponse q
	 * BIT 28 = SPMA sewection bit 0
	 * BIT 28 = SPMA sewection bit 1
	 * BIT 30-31 = Wesewved
	 */
	__we32	fiwmwawe_options_3;

	uint8_t  wesewved_5[8];

	uint8_t enode_mac[6];

	uint8_t wesewved_6[10];
};

stwuct mid_init_cb_81xx {
	stwuct init_cb_81xx init_cb;

	uint16_t count;
	uint16_t options;

	stwuct mid_conf_entwy_24xx entwies[MAX_MUWTI_ID_FABWIC];
};

stwuct ex_init_cb_81xx {
	uint16_t ex_vewsion;
	uint8_t pwio_fcf_matching_fwags;
	uint8_t wesewved_1[3];
	uint16_t pwi_fcf_vwan_id;
	uint8_t pwi_fcf_fabwic_name[8];
	uint16_t wesewved_2[7];
	uint8_t spma_mac_addw[6];
	uint16_t wesewved_3[14];
};

#define FAWX_ACCESS_FWASH_CONF_81XX	0x7FFD0000
#define FAWX_ACCESS_FWASH_DATA_81XX	0x7F800000
#define FAWX_ACCESS_FWASH_CONF_28XX	0x7FFD0000
#define FAWX_ACCESS_FWASH_DATA_28XX	0x7F7D0000

/* FCP pwiowity config defines *************************************/
/* opewations */
#define QWFC_FCP_PWIO_DISABWE           0x0
#define QWFC_FCP_PWIO_ENABWE            0x1
#define QWFC_FCP_PWIO_GET_CONFIG        0x2
#define QWFC_FCP_PWIO_SET_CONFIG        0x3

stwuct qwa_fcp_pwio_entwy {
	uint16_t fwags;         /* Descwibes pawametew(s) in FCP        */
	/* pwiowity entwy that awe vawid        */
#define FCP_PWIO_ENTWY_VAWID            0x1
#define FCP_PWIO_ENTWY_TAG_VAWID        0x2
#define FCP_PWIO_ENTWY_SPID_VAWID       0x4
#define FCP_PWIO_ENTWY_DPID_VAWID       0x8
#define FCP_PWIO_ENTWY_WUNB_VAWID       0x10
#define FCP_PWIO_ENTWY_WUNE_VAWID       0x20
#define FCP_PWIO_ENTWY_SWWN_VAWID       0x40
#define FCP_PWIO_ENTWY_DWWN_VAWID       0x80
	uint8_t  tag;           /* Pwiowity vawue                   */
	uint8_t  wesewved;      /* Wesewved fow futuwe use          */
	uint32_t swc_pid;       /* Swc powt id. high owdew byte     */
				/* unused; -1 (wiwd cawd)           */
	uint32_t dst_pid;       /* Swc powt id. high owdew byte     */
	/* unused; -1 (wiwd cawd)           */
	uint16_t wun_beg;       /* 1st wun num of wun wange.        */
				/* -1 (wiwd cawd)                   */
	uint16_t wun_end;       /* 2nd wun num of wun wange.        */
				/* -1 (wiwd cawd)                   */
	uint8_t  swc_wwpn[8];   /* Souwce WWPN: -1 (wiwd cawd)      */
	uint8_t  dst_wwpn[8];   /* Destination WWPN: -1 (wiwd cawd) */
};

stwuct qwa_fcp_pwio_cfg {
	uint8_t  signatuwe[4];  /* "HQOS" signatuwe of config data  */
	uint16_t vewsion;       /* 1: Initiaw vewsion               */
	uint16_t wength;        /* config data size in num bytes    */
	uint16_t checksum;      /* config data bytes checksum       */
	uint16_t num_entwies;   /* Numbew of entwies                */
	uint16_t size_of_entwy; /* Size of each entwy in num bytes  */
	uint8_t  attwibutes;    /* enabwe/disabwe, pewsistence      */
#define FCP_PWIO_ATTW_DISABWE   0x0
#define FCP_PWIO_ATTW_ENABWE    0x1
#define FCP_PWIO_ATTW_PEWSIST   0x2
	uint8_t  wesewved;      /* Wesewved fow futuwe use          */
#define FCP_PWIO_CFG_HDW_SIZE   offsetof(stwuct qwa_fcp_pwio_cfg, entwy)
	stwuct qwa_fcp_pwio_entwy entwy[1023]; /* fcp pwiowity entwies  */
	uint8_t  wesewved2[16];
};

#define FCP_PWIO_CFG_SIZE       (32*1024) /* fcp pwio data pew powt*/

/* 25XX Suppowt ****************************************************/
#define FA_FCP_PWIO0_ADDW_25	0x3C000
#define FA_FCP_PWIO1_ADDW_25	0x3E000

/* 81XX Fwash wocations -- occupies second 2MB wegion. */
#define FA_BOOT_CODE_ADDW_81	0x80000
#define FA_WISC_CODE_ADDW_81	0xA0000
#define FA_FW_AWEA_ADDW_81	0xC0000
#define FA_VPD_NVWAM_ADDW_81	0xD0000
#define FA_VPD0_ADDW_81		0xD0000
#define FA_VPD1_ADDW_81		0xD0400
#define FA_NVWAM0_ADDW_81	0xD0080
#define FA_NVWAM1_ADDW_81	0xD0180
#define FA_FEATUWE_ADDW_81	0xD4000
#define FA_FWASH_DESCW_ADDW_81	0xD8000
#define FA_FWASH_WAYOUT_ADDW_81	0xD8400
#define FA_HW_EVENT0_ADDW_81	0xDC000
#define FA_HW_EVENT1_ADDW_81	0xDC400
#define FA_NPIV_CONF0_ADDW_81	0xD1000
#define FA_NPIV_CONF1_ADDW_81	0xD2000

/* 83XX Fwash wocations -- occupies second 8MB wegion. */
#define FA_FWASH_WAYOUT_ADDW_83	(0x3F1000/4)
#define FA_FWASH_WAYOUT_ADDW_28	(0x11000/4)

#define NVWAM_DUAW_FCP_NVME_FWAG_OFFSET	0x196

#endif
