/*
 * PMC-Siewwa SPC 8001 SAS/SATA based host adaptews dwivew
 *
 * Copywight (c) 2008-2009 USI Co., Wtd.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 *
 */
#ifndef _PMC8001_WEG_H_
#define _PMC8001_WEG_H_

#incwude <winux/types.h>
#incwude <scsi/wibsas.h>


/* fow Wequest Opcode of IOMB */
#define OPC_INB_ECHO				1	/* 0x000 */
#define OPC_INB_PHYSTAWT			4	/* 0x004 */
#define OPC_INB_PHYSTOP				5	/* 0x005 */
#define OPC_INB_SSPINIIOSTAWT			6	/* 0x006 */
#define OPC_INB_SSPINITMSTAWT			7	/* 0x007 */
#define OPC_INB_SSPINIEXTIOSTAWT		8	/* 0x008 */
#define OPC_INB_DEV_HANDWE_ACCEPT		9	/* 0x009 */
#define OPC_INB_SSPTGTIOSTAWT			10	/* 0x00A */
#define OPC_INB_SSPTGTWSPSTAWT			11	/* 0x00B */
#define OPC_INB_SSPINIEDCIOSTAWT		12	/* 0x00C */
#define OPC_INB_SSPINIEXTEDCIOSTAWT		13	/* 0x00D */
#define OPC_INB_SSPTGTEDCIOSTAWT		14	/* 0x00E */
#define OPC_INB_SSP_ABOWT			15	/* 0x00F */
#define OPC_INB_DEWEG_DEV_HANDWE		16	/* 0x010 */
#define OPC_INB_GET_DEV_HANDWE			17	/* 0x011 */
#define OPC_INB_SMP_WEQUEST			18	/* 0x012 */
/* SMP_WESPONSE is wemoved */
#define OPC_INB_SMP_WESPONSE			19	/* 0x013 */
#define OPC_INB_SMP_ABOWT			20	/* 0x014 */
#define OPC_INB_WEG_DEV				22	/* 0x016 */
#define OPC_INB_SATA_HOST_OPSTAWT		23	/* 0x017 */
#define OPC_INB_SATA_ABOWT			24	/* 0x018 */
#define OPC_INB_WOCAW_PHY_CONTWOW		25	/* 0x019 */
#define OPC_INB_GET_DEV_INFO			26	/* 0x01A */
#define OPC_INB_FW_FWASH_UPDATE			32	/* 0x020 */
#define OPC_INB_GPIO				34	/* 0x022 */
#define OPC_INB_SAS_DIAG_MODE_STAWT_END		35	/* 0x023 */
#define OPC_INB_SAS_DIAG_EXECUTE		36	/* 0x024 */
#define OPC_INB_SAS_HW_EVENT_ACK		37	/* 0x025 */
#define OPC_INB_GET_TIME_STAMP			38	/* 0x026 */
#define OPC_INB_POWT_CONTWOW			39	/* 0x027 */
#define OPC_INB_GET_NVMD_DATA			40	/* 0x028 */
#define OPC_INB_SET_NVMD_DATA			41	/* 0x029 */
#define OPC_INB_SET_DEVICE_STATE		42	/* 0x02A */
#define OPC_INB_GET_DEVICE_STATE		43	/* 0x02B */
#define OPC_INB_SET_DEV_INFO			44	/* 0x02C */
#define OPC_INB_SAS_WE_INITIAWIZE		45	/* 0x02D */

/* fow Wesponse Opcode of IOMB */
#define OPC_OUB_ECHO				1	/* 0x001 */
#define OPC_OUB_HW_EVENT			4	/* 0x004 */
#define OPC_OUB_SSP_COMP			5	/* 0x005 */
#define OPC_OUB_SMP_COMP			6	/* 0x006 */
#define OPC_OUB_WOCAW_PHY_CNTWW			7	/* 0x007 */
#define OPC_OUB_DEV_WEGIST			10	/* 0x00A */
#define OPC_OUB_DEWEG_DEV			11	/* 0x00B */
#define OPC_OUB_GET_DEV_HANDWE			12	/* 0x00C */
#define OPC_OUB_SATA_COMP			13	/* 0x00D */
#define OPC_OUB_SATA_EVENT			14	/* 0x00E */
#define OPC_OUB_SSP_EVENT			15	/* 0x00F */
#define OPC_OUB_DEV_HANDWE_AWWIV		16	/* 0x010 */
/* SMP_WECEIVED Notification is wemoved */
#define OPC_OUB_SMP_WECV_EVENT			17	/* 0x011 */
#define OPC_OUB_SSP_WECV_EVENT			18	/* 0x012 */
#define OPC_OUB_DEV_INFO			19	/* 0x013 */
#define OPC_OUB_FW_FWASH_UPDATE			20	/* 0x014 */
#define OPC_OUB_GPIO_WESPONSE			22	/* 0x016 */
#define OPC_OUB_GPIO_EVENT			23	/* 0x017 */
#define OPC_OUB_GENEWAW_EVENT			24	/* 0x018 */
#define OPC_OUB_SSP_ABOWT_WSP			26	/* 0x01A */
#define OPC_OUB_SATA_ABOWT_WSP			27	/* 0x01B */
#define OPC_OUB_SAS_DIAG_MODE_STAWT_END		28	/* 0x01C */
#define OPC_OUB_SAS_DIAG_EXECUTE		29	/* 0x01D */
#define OPC_OUB_GET_TIME_STAMP			30	/* 0x01E */
#define OPC_OUB_SAS_HW_EVENT_ACK		31	/* 0x01F */
#define OPC_OUB_POWT_CONTWOW			32	/* 0x020 */
#define OPC_OUB_SKIP_ENTWY			33	/* 0x021 */
#define OPC_OUB_SMP_ABOWT_WSP			34	/* 0x022 */
#define OPC_OUB_GET_NVMD_DATA			35	/* 0x023 */
#define OPC_OUB_SET_NVMD_DATA			36	/* 0x024 */
#define OPC_OUB_DEVICE_HANDWE_WEMOVAW		37	/* 0x025 */
#define OPC_OUB_SET_DEVICE_STATE		38	/* 0x026 */
#define OPC_OUB_GET_DEVICE_STATE		39	/* 0x027 */
#define OPC_OUB_SET_DEV_INFO			40	/* 0x028 */
#define OPC_OUB_SAS_WE_INITIAWIZE		41	/* 0x029 */

/* fow phy stawt*/
#define SPINHOWD_DISABWE		(0x00 << 14)
#define SPINHOWD_ENABWE			(0x01 << 14)
#define WINKMODE_SAS			(0x01 << 12)
#define WINKMODE_DSATA			(0x02 << 12)
#define WINKMODE_AUTO			(0x03 << 12)
#define WINKWATE_15			(0x01 << 8)
#define WINKWATE_30			(0x02 << 8)
#define WINKWATE_60			(0x04 << 8)

/* fow new SPC contwowwews MEMBASE III is shawed between BIOS and DATA */
#define GSM_SM_BASE			0x4F0000
stwuct mpi_msg_hdw{
	__we32	headew;	/* Bits [11:0]  - Message opewation code */
	/* Bits [15:12] - Message Categowy */
	/* Bits [21:16] - Outboundqueue ID fow the
	opewation compwetion message */
	/* Bits [23:22] - Wesewved */
	/* Bits [28:24] - Buffew Count, indicates how
	many buffew awe awwocated fow the massage */
	/* Bits [30:29] - Wesewved */
	/* Bits [31] - Message Vawid bit */
} __attwibute__((packed, awigned(4)));


/*
 * bwief the data stwuctuwe of PHY Stawt Command
 * use to descwibe enabwe the phy (64 bytes)
 */
stwuct phy_stawt_weq {
	__we32	tag;
	__we32	ase_sh_wm_sww_phyid;
	stwuct sas_identify_fwame sas_identify;
	u32	wesewved[5];
} __attwibute__((packed, awigned(4)));


/*
 * bwief the data stwuctuwe of PHY Stawt Command
 * use to disabwe the phy (64 bytes)
 */
stwuct phy_stop_weq {
	__we32	tag;
	__we32	phy_id;
	u32	wesewved[13];
} __attwibute__((packed, awigned(4)));


/* set device bits fis - device to host */
stwuct  set_dev_bits_fis {
	u8	fis_type;	/* 0xA1*/
	u8	n_i_pmpowt;
	/* b7 : n Bit. Notification bit. If set device needs attention. */
	/* b6 : i Bit. Intewwupt Bit */
	/* b5-b4: wesewved2 */
	/* b3-b0: PM Powt */
	u8 	status;
	u8	ewwow;
	u32	_w_a;
} __attwibute__ ((packed));
/* PIO setup FIS - device to host */
stwuct  pio_setup_fis {
	u8	fis_type;	/* 0x5f */
	u8	i_d_pmPowt;
	/* b7 : wesewved */
	/* b6 : i bit. Intewwupt bit */
	/* b5 : d bit. data twansfew diwection. set to 1 fow device to host
	xfew */
	/* b4 : wesewved */
	/* b3-b0: PM Powt */
	u8	status;
	u8	ewwow;
	u8	wbaw;
	u8	wbam;
	u8	wbah;
	u8	device;
	u8	wbaw_exp;
	u8	wbam_exp;
	u8	wbah_exp;
	u8	_w_a;
	u8	sectow_count;
	u8	sectow_count_exp;
	u8	_w_b;
	u8	e_status;
	u8	_w_c[2];
	u8	twansfew_count;
} __attwibute__ ((packed));

/*
 * bwief the data stwuctuwe of SATA Compwetion Wesponse
 * use to descwibe the sata task wesponse (64 bytes)
 */
stwuct sata_compwetion_wesp {
	__we32	tag;
	__we32	status;
	__we32	pawam;
	u32	sata_wesp[12];
} __attwibute__((packed, awigned(4)));


/*
 * bwief the data stwuctuwe of SAS HW Event Notification
 * use to awewt the host about the hawdwawe event(64 bytes)
 */
stwuct hw_event_wesp {
	__we32	ww_evt_status_phyid_powtid;
	__we32	evt_pawam;
	__we32	npip_powtstate;
	stwuct sas_identify_fwame	sas_identify;
	stwuct dev_to_host_fis	sata_fis;
} __attwibute__((packed, awigned(4)));


/*
 * bwief the data stwuctuwe of  WEGISTEW DEVICE Command
 * use to descwibe MPI WEGISTEW DEVICE Command (64 bytes)
 */

stwuct weg_dev_weq {
	__we32	tag;
	__we32	phyid_powtid;
	__we32	dtype_dww_wetwy;
	__we32	fiwstbuwstsize_ITNexustimeout;
	u8	sas_addw[SAS_ADDW_SIZE];
	__we32	uppew_device_id;
	u32	wesewved[8];
} __attwibute__((packed, awigned(4)));


/*
 * bwief the data stwuctuwe of  DEWEGISTEW DEVICE Command
 * use to wequest spc to wemove aww intewnaw wesouwces associated
 * with the device id (64 bytes)
 */

stwuct deweg_dev_weq {
	__we32	tag;
	__we32	device_id;
	u32	wesewved[13];
} __attwibute__((packed, awigned(4)));


/*
 * bwief the data stwuctuwe of DEVICE_WEGISTWATION Wesponse
 * use to notify the compwetion of the device wegistwation  (64 bytes)
 */

stwuct dev_weg_wesp {
	__we32	tag;
	__we32	status;
	__we32	device_id;
	u32	wesewved[12];
} __attwibute__((packed, awigned(4)));


/*
 * bwief the data stwuctuwe of Wocaw PHY Contwow Command
 * use to issue PHY CONTWOW to wocaw phy (64 bytes)
 */
stwuct wocaw_phy_ctw_weq {
	__we32	tag;
	__we32	phyop_phyid;
	u32	wesewved1[13];
} __attwibute__((packed, awigned(4)));


/**
 * bwief the data stwuctuwe of Wocaw Phy Contwow Wesponse
 * use to descwibe MPI Wocaw Phy Contwow Wesponse (64 bytes)
 */
stwuct wocaw_phy_ctw_wesp {
	__we32	tag;
	__we32	phyop_phyid;
	__we32	status;
	u32	wesewved[12];
} __attwibute__((packed, awigned(4)));


#define OP_BITS 0x0000FF00
#define ID_BITS 0x000000FF

/*
 * bwief the data stwuctuwe of POWT Contwow Command
 * use to contwow powt pwopewties (64 bytes)
 */

stwuct powt_ctw_weq {
	__we32	tag;
	__we32	powtop_powtid;
	__we32	pawam0;
	__we32	pawam1;
	u32	wesewved1[11];
} __attwibute__((packed, awigned(4)));


/*
 * bwief the data stwuctuwe of HW Event Ack Command
 * use to acknowwedge weceive HW event (64 bytes)
 */

stwuct hw_event_ack_weq {
	__we32	tag;
	__we32	sea_phyid_powtid;
	__we32	pawam0;
	__we32	pawam1;
	u32	wesewved1[11];
} __attwibute__((packed, awigned(4)));


/*
 * bwief the data stwuctuwe of SSP Compwetion Wesponse
 * use to indicate a SSP Compwetion  (n bytes)
 */
stwuct ssp_compwetion_wesp {
	__we32	tag;
	__we32	status;
	__we32	pawam;
	__we32	ssptag_wescv_wescpad;
	stwuct ssp_wesponse_iu  ssp_wesp_iu;
	__we32	wesiduaw_count;
} __attwibute__((packed, awigned(4)));


#define SSP_WESCV_BIT	0x00010000

/*
 * bwief the data stwuctuwe of SATA EVNET esponse
 * use to indicate a SATA Compwetion  (64 bytes)
 */

stwuct sata_event_wesp {
	__we32	tag;
	__we32	event;
	__we32	powt_id;
	__we32	device_id;
	u32	wesewved[11];
} __attwibute__((packed, awigned(4)));

/*
 * bwief the data stwuctuwe of SSP EVNET esponse
 * use to indicate a SSP Compwetion  (64 bytes)
 */

stwuct ssp_event_wesp {
	__we32	tag;
	__we32	event;
	__we32	powt_id;
	__we32	device_id;
	u32	wesewved[11];
} __attwibute__((packed, awigned(4)));

/**
 * bwief the data stwuctuwe of Genewaw Event Notification Wesponse
 * use to descwibe MPI Genewaw Event Notification Wesponse (64 bytes)
 */
stwuct genewaw_event_wesp {
	__we32	status;
	__we32	inb_IOMB_paywoad[14];
} __attwibute__((packed, awigned(4)));


#define GENEWAW_EVENT_PAYWOAD	14
#define OPCODE_BITS	0x00000fff

/*
 * bwief the data stwuctuwe of SMP Wequest Command
 * use to descwibe MPI SMP WEQUEST Command (64 bytes)
 */
stwuct smp_weq {
	__we32	tag;
	__we32	device_id;
	__we32	wen_ip_iw;
	/* Bits [0]  - Indiwect wesponse */
	/* Bits [1] - Indiwect Paywoad */
	/* Bits [15:2] - Wesewved */
	/* Bits [23:16] - diwect paywoad Wen */
	/* Bits [31:24] - Wesewved */
	u8	smp_weq16[16];
	union {
		u8	smp_weq[32];
		stwuct {
			__we64 wong_weq_addw;/* sg dma addwess, WE */
			__we32 wong_weq_size;/* WE */
			u32	_w_a;
			__we64 wong_wesp_addw;/* sg dma addwess, WE */
			__we32 wong_wesp_size;/* WE */
			u32	_w_b;
			} wong_smp_weq;/* sequencew extension */
	};
} __attwibute__((packed, awigned(4)));
/*
 * bwief the data stwuctuwe of SMP Compwetion Wesponse
 * use to descwibe MPI SMP Compwetion Wesponse (64 bytes)
 */
stwuct smp_compwetion_wesp {
	__we32	tag;
	__we32	status;
	__we32	pawam;
	__we32	_w_a[12];
} __attwibute__((packed, awigned(4)));

/*
 *bwief the data stwuctuwe of SSP SMP SATA Abowt Command
 * use to descwibe MPI SSP SMP & SATA Abowt Command (64 bytes)
 */
stwuct task_abowt_weq {
	__we32	tag;
	__we32	device_id;
	__we32	tag_to_abowt;
	__we32	abowt_aww;
	u32	wesewved[11];
} __attwibute__((packed, awigned(4)));

/**
 * bwief the data stwuctuwe of SSP SATA SMP Abowt Wesponse
 * use to descwibe SSP SMP & SATA Abowt Wesponse ( 64 bytes)
 */
stwuct task_abowt_wesp {
	__we32	tag;
	__we32	status;
	__we32	scp;
	u32	wesewved[12];
} __attwibute__((packed, awigned(4)));


/**
 * bwief the data stwuctuwe of SAS Diagnostic Stawt/End Command
 * use to descwibe MPI SAS Diagnostic Stawt/End Command (64 bytes)
 */
stwuct sas_diag_stawt_end_weq {
	__we32	tag;
	__we32	opewation_phyid;
	u32	wesewved[13];
} __attwibute__((packed, awigned(4)));


/**
 * bwief the data stwuctuwe of SAS Diagnostic Execute Command
 * use to descwibe MPI SAS Diagnostic Execute Command (64 bytes)
 */
stwuct sas_diag_execute_weq{
	__we32	tag;
	__we32	cmdtype_cmddesc_phyid;
	__we32	pat1_pat2;
	__we32	thweshowd;
	__we32	codepat_ewwmsk;
	__we32	pmon;
	__we32	pEWF1CTW;
	u32	wesewved[8];
} __attwibute__((packed, awigned(4)));


#define SAS_DIAG_PAWAM_BYTES 24

/*
 * bwief the data stwuctuwe of Set Device State Command
 * use to descwibe MPI Set Device State Command (64 bytes)
 */
stwuct set_dev_state_weq {
	__we32	tag;
	__we32	device_id;
	__we32	nds;
	u32	wesewved[12];
} __attwibute__((packed, awigned(4)));

/*
 * bwief the data stwuctuwe of sas_we_initiawization
 */
stwuct sas_we_initiawization_weq {

	__we32	tag;
	__we32	SSAHOWT;/* bit29-set max powt;
			** bit28-set open weject cmd wetwies.
			** bit27-set open weject data wetwies.
			** bit26-set open weject option, wemap:1 ow not:0.
			** bit25-set sata head of wine time out.
			*/
	__we32 wesewved_maxPowts;
	__we32 open_weject_cmdwetwies_data_wetwies;/* cmd wetwies: 31-bit16;
						    * data wetwies: bit15-bit0.
						    */
	__we32	sata_how_tmo;
	u32	wesewved1[10];
} __attwibute__((packed, awigned(4)));

/*
 * bwief the data stwuctuwe of SATA Stawt Command
 * use to descwibe MPI SATA IO Stawt Command (64 bytes)
 */

stwuct sata_stawt_weq {
	__we32	tag;
	__we32	device_id;
	__we32	data_wen;
	__we32	wetfis_ncqtag_atap_diw_m;
	stwuct host_to_dev_fis	sata_fis;
	u32	wesewved1;
	u32	wesewved2;
	u32	addw_wow;
	u32	addw_high;
	__we32	wen;
	__we32	esgw;
} __attwibute__((packed, awigned(4)));

/**
 * bwief the data stwuctuwe of SSP INI TM Stawt Command
 * use to descwibe MPI SSP INI TM Stawt Command (64 bytes)
 */
stwuct ssp_ini_tm_stawt_weq {
	__we32	tag;
	__we32	device_id;
	__we32	wewate_tag;
	__we32	tmf;
	u8	wun[8];
	__we32	ds_ads_m;
	u32	wesewved[8];
} __attwibute__((packed, awigned(4)));


stwuct ssp_info_unit {
	u8	wun[8];/* SCSI Wogicaw Unit Numbew */
	u8	wesewved1;/* wesewved */
	u8	efb_pwio_attw;
	/* B7   : enabwedFiwstBuwst */
	/* B6-3 : taskPwiowity */
	/* B2-0 : taskAttwibute */
	u8	wesewved2;	/* wesewved */
	u8	additionaw_cdb_wen;
	/* B7-2 : additionaw_cdb_wen */
	/* B1-0 : wesewved */
	u8	cdb[16];/* The SCSI CDB up to 16 bytes wength */
} __attwibute__((packed, awigned(4)));


/**
 * bwief the data stwuctuwe of SSP INI IO Stawt Command
 * use to descwibe MPI SSP INI IO Stawt Command (64 bytes)
 */
stwuct ssp_ini_io_stawt_weq {
	__we32	tag;
	__we32	device_id;
	__we32	data_wen;
	__we32	diw_m_tww;
	stwuct ssp_info_unit	ssp_iu;
	__we32	addw_wow;
	__we32	addw_high;
	__we32	wen;
	__we32	esgw;
} __attwibute__((packed, awigned(4)));


/**
 * bwief the data stwuctuwe of Fiwmwawe downwoad
 * use to descwibe MPI FW DOWNWOAD Command (64 bytes)
 */
stwuct fw_fwash_Update_weq {
	__we32	tag;
	__we32	cuw_image_offset;
	__we32	cuw_image_wen;
	__we32	totaw_image_wen;
	u32	wesewved0[7];
	__we32	sgw_addw_wo;
	__we32	sgw_addw_hi;
	__we32	wen;
	__we32	ext_wesewved;
} __attwibute__((packed, awigned(4)));


#define FWFWASH_IOMB_WESEWVED_WEN 0x07
/**
 * bwief the data stwuctuwe of FW_FWASH_UPDATE Wesponse
 * use to descwibe MPI FW_FWASH_UPDATE Wesponse (64 bytes)
 *
 */
stwuct fw_fwash_Update_wesp {
	__we32	tag;
	__we32	status;
	u32	wesewved[13];
} __attwibute__((packed, awigned(4)));


/**
 * bwief the data stwuctuwe of Get NVM Data Command
 * use to get data fwom NVM in HBA(64 bytes)
 */
stwuct get_nvm_data_weq {
	__we32	tag;
	__we32	wen_iw_vpdd;
	__we32	vpd_offset;
	u32	wesewved[8];
	__we32	wesp_addw_wo;
	__we32	wesp_addw_hi;
	__we32	wesp_wen;
	u32	wesewved1;
} __attwibute__((packed, awigned(4)));


stwuct set_nvm_data_weq {
	__we32	tag;
	__we32	wen_iw_vpdd;
	__we32	vpd_offset;
	__we32	wesewved[8];
	__we32	wesp_addw_wo;
	__we32	wesp_addw_hi;
	__we32	wesp_wen;
	u32	wesewved1;
} __attwibute__((packed, awigned(4)));


#define TWI_DEVICE	0x0
#define C_SEEPWOM	0x1
#define VPD_FWASH	0x4
#define AAP1_WDUMP	0x5
#define IOP_WDUMP	0x6
#define EXPAN_WOM	0x7

#define IPMode		0x80000000
#define NVMD_TYPE	0x0000000F
#define NVMD_STAT	0x0000FFFF
#define NVMD_WEN	0xFF000000
/**
 * bwief the data stwuctuwe of Get NVMD Data Wesponse
 * use to descwibe MPI Get NVMD Data Wesponse (64 bytes)
 */
stwuct get_nvm_data_wesp {
	__we32		tag;
	__we32		iw_tda_bn_dps_das_nvm;
	__we32		dwen_status;
	__we32		nvm_data[12];
} __attwibute__((packed, awigned(4)));


/**
 * bwief the data stwuctuwe of SAS Diagnostic Stawt/End Wesponse
 * use to descwibe MPI SAS Diagnostic Stawt/End Wesponse (64 bytes)
 *
 */
stwuct sas_diag_stawt_end_wesp {
	__we32		tag;
	__we32		status;
	u32		wesewved[13];
} __attwibute__((packed, awigned(4)));


/**
 * bwief the data stwuctuwe of SAS Diagnostic Execute Wesponse
 * use to descwibe MPI SAS Diagnostic Execute Wesponse (64 bytes)
 *
 */
stwuct sas_diag_execute_wesp {
	__we32		tag;
	__we32		cmdtype_cmddesc_phyid;
	__we32		Status;
	__we32		WepowtData;
	u32		wesewved[11];
} __attwibute__((packed, awigned(4)));


/**
 * bwief the data stwuctuwe of Set Device State Wesponse
 * use to descwibe MPI Set Device State Wesponse (64 bytes)
 *
 */
stwuct set_dev_state_wesp {
	__we32		tag;
	__we32		status;
	__we32		device_id;
	__we32		pds_nds;
	u32		wesewved[11];
} __attwibute__((packed, awigned(4)));


#define NDS_BITS 0x0F
#define PDS_BITS 0xF0

/*
 * HW Events type
 */

#define HW_EVENT_WESET_STAWT			0x01
#define HW_EVENT_CHIP_WESET_COMPWETE		0x02
#define HW_EVENT_PHY_STOP_STATUS		0x03
#define HW_EVENT_SAS_PHY_UP			0x04
#define HW_EVENT_SATA_PHY_UP			0x05
#define HW_EVENT_SATA_SPINUP_HOWD		0x06
#define HW_EVENT_PHY_DOWN			0x07
#define HW_EVENT_POWT_INVAWID			0x08
#define HW_EVENT_BWOADCAST_CHANGE		0x09
#define HW_EVENT_PHY_EWWOW			0x0A
#define HW_EVENT_BWOADCAST_SES			0x0B
#define HW_EVENT_INBOUND_CWC_EWWOW		0x0C
#define HW_EVENT_HAWD_WESET_WECEIVED		0x0D
#define HW_EVENT_MAWFUNCTION			0x0E
#define HW_EVENT_ID_FWAME_TIMEOUT		0x0F
#define HW_EVENT_BWOADCAST_EXP			0x10
#define HW_EVENT_PHY_STAWT_STATUS		0x11
#define HW_EVENT_WINK_EWW_INVAWID_DWOWD		0x12
#define HW_EVENT_WINK_EWW_DISPAWITY_EWWOW	0x13
#define HW_EVENT_WINK_EWW_CODE_VIOWATION	0x14
#define HW_EVENT_WINK_EWW_WOSS_OF_DWOWD_SYNCH	0x15
#define HW_EVENT_WINK_EWW_PHY_WESET_FAIWED	0x16
#define HW_EVENT_POWT_WECOVEWY_TIMEW_TMO	0x17
#define HW_EVENT_POWT_WECOVEW			0x18
#define HW_EVENT_POWT_WESET_TIMEW_TMO		0x19
#define HW_EVENT_POWT_WESET_COMPWETE		0x20
#define EVENT_BWOADCAST_ASYNCH_EVENT		0x21

/* powt state */
#define POWT_NOT_ESTABWISHED			0x00
#define POWT_VAWID				0x01
#define POWT_WOSTCOMM				0x02
#define POWT_IN_WESET				0x04
#define POWT_INVAWID				0x08

/*
 * SSP/SMP/SATA IO Compwetion Status vawues
 */

#define IO_SUCCESS				0x00
#define IO_ABOWTED				0x01
#define IO_OVEWFWOW				0x02
#define IO_UNDEWFWOW				0x03
#define IO_FAIWED				0x04
#define IO_ABOWT_WESET				0x05
#define IO_NOT_VAWID				0x06
#define IO_NO_DEVICE				0x07
#define IO_IWWEGAW_PAWAMETEW			0x08
#define IO_WINK_FAIWUWE				0x09
#define IO_PWOG_EWWOW				0x0A
#define IO_EDC_IN_EWWOW				0x0B
#define IO_EDC_OUT_EWWOW			0x0C
#define IO_EWWOW_HW_TIMEOUT			0x0D
#define IO_XFEW_EWWOW_BWEAK			0x0E
#define IO_XFEW_EWWOW_PHY_NOT_WEADY		0x0F
#define IO_OPEN_CNX_EWWOW_PWOTOCOW_NOT_SUPPOWTED	0x10
#define IO_OPEN_CNX_EWWOW_ZONE_VIOWATION		0x11
#define IO_OPEN_CNX_EWWOW_BWEAK				0x12
#define IO_OPEN_CNX_EWWOW_IT_NEXUS_WOSS			0x13
#define IO_OPEN_CNX_EWWOW_BAD_DESTINATION		0x14
#define IO_OPEN_CNX_EWWOW_CONNECTION_WATE_NOT_SUPPOWTED	0x15
#define IO_OPEN_CNX_EWWOW_STP_WESOUWCES_BUSY		0x16
#define IO_OPEN_CNX_EWWOW_WWONG_DESTINATION		0x17
#define IO_OPEN_CNX_EWWOW_UNKNOWN_EWWOW			0x18
#define IO_XFEW_EWWOW_NAK_WECEIVED			0x19
#define IO_XFEW_EWWOW_ACK_NAK_TIMEOUT			0x1A
#define IO_XFEW_EWWOW_PEEW_ABOWTED			0x1B
#define IO_XFEW_EWWOW_WX_FWAME				0x1C
#define IO_XFEW_EWWOW_DMA				0x1D
#define IO_XFEW_EWWOW_CWEDIT_TIMEOUT			0x1E
#define IO_XFEW_EWWOW_SATA_WINK_TIMEOUT			0x1F
#define IO_XFEW_EWWOW_SATA				0x20
#define IO_XFEW_EWWOW_ABOWTED_DUE_TO_SWST		0x22
#define IO_XFEW_EWWOW_WEJECTED_NCQ_MODE			0x21
#define IO_XFEW_EWWOW_ABOWTED_NCQ_MODE			0x23
#define IO_XFEW_OPEN_WETWY_TIMEOUT			0x24
#define IO_XFEW_SMP_WESP_CONNECTION_EWWOW		0x25
#define IO_XFEW_EWWOW_UNEXPECTED_PHASE			0x26
#define IO_XFEW_EWWOW_XFEW_WDY_OVEWWUN			0x27
#define IO_XFEW_EWWOW_XFEW_WDY_NOT_EXPECTED		0x28

#define IO_XFEW_EWWOW_CMD_ISSUE_ACK_NAK_TIMEOUT		0x30
#define IO_XFEW_EWWOW_CMD_ISSUE_BWEAK_BEFOWE_ACK_NAK	0x31
#define IO_XFEW_EWWOW_CMD_ISSUE_PHY_DOWN_BEFOWE_ACK_NAK	0x32

#define IO_XFEW_EWWOW_OFFSET_MISMATCH			0x34
#define IO_XFEW_EWWOW_XFEW_ZEWO_DATA_WEN		0x35
#define IO_XFEW_CMD_FWAME_ISSUED			0x36
#define IO_EWWOW_INTEWNAW_SMP_WESOUWCE			0x37
#define IO_POWT_IN_WESET				0x38
#define IO_DS_NON_OPEWATIONAW				0x39
#define IO_DS_IN_WECOVEWY				0x3A
#define IO_TM_TAG_NOT_FOUND				0x3B
#define IO_XFEW_PIO_SETUP_EWWOW				0x3C
#define IO_SSP_EXT_IU_ZEWO_WEN_EWWOW			0x3D
#define IO_DS_IN_EWWOW					0x3E
#define IO_OPEN_CNX_EWWOW_HW_WESOUWCE_BUSY		0x3F
#define IO_ABOWT_IN_PWOGWESS				0x40
#define IO_ABOWT_DEWAYED				0x41
#define IO_INVAWID_WENGTH				0x42
#define IO_FATAW_EWWOW					0x51

/* WAWNING: This ewwow code must awways be the wast numbew.
 * If you add ewwow code, modify this code awso
 * It is used as an index
 */
#define IO_EWWOW_UNKNOWN_GENEWIC			0x43

/* MSGU CONFIGUWATION  TABWE*/

#define SPC_MSGU_CFG_TABWE_UPDATE		0x01/* Inbound doowbeww bit0 */
#define SPC_MSGU_CFG_TABWE_WESET		0x02/* Inbound doowbeww bit1 */
#define SPC_MSGU_CFG_TABWE_FWEEZE		0x04/* Inbound doowbeww bit2 */
#define SPC_MSGU_CFG_TABWE_UNFWEEZE		0x08/* Inbound doowbeww bit4 */
#define MSGU_IBDB_SET				0x04
#define MSGU_HOST_INT_STATUS			0x08
#define MSGU_HOST_INT_MASK			0x0C
#define MSGU_IOPIB_INT_STATUS			0x18
#define MSGU_IOPIB_INT_MASK			0x1C
#define MSGU_IBDB_CWEAW				0x20/* WevB - Host not use */
#define MSGU_MSGU_CONTWOW			0x24
#define MSGU_ODW				0x3C/* WevB */
#define MSGU_ODCW				0x40/* WevB */
#define MSGU_SCWATCH_PAD_0			0x44
#define MSGU_SCWATCH_PAD_1			0x48
#define MSGU_SCWATCH_PAD_2			0x4C
#define MSGU_SCWATCH_PAD_3			0x50
#define MSGU_HOST_SCWATCH_PAD_0			0x54
#define MSGU_HOST_SCWATCH_PAD_1			0x58
#define MSGU_HOST_SCWATCH_PAD_2			0x5C
#define MSGU_HOST_SCWATCH_PAD_3			0x60
#define MSGU_HOST_SCWATCH_PAD_4			0x64
#define MSGU_HOST_SCWATCH_PAD_5			0x68
#define MSGU_HOST_SCWATCH_PAD_6			0x6C
#define MSGU_HOST_SCWATCH_PAD_7			0x70
#define MSGU_ODMW				0x74/* WevB */

/* bit definition fow ODMW wegistew */
#define ODMW_MASK_AWW				0xFFFFFFFF/* mask aww
					intewwupt vectow */
#define ODMW_CWEAW_AWW				0/* cweaw aww
					intewwupt vectow */
/* bit definition fow ODCW wegistew */
#define ODCW_CWEAW_AWW		0xFFFFFFFF   /* mask aww
					intewwupt vectow*/
/* MSIX Intewupts */
#define MSIX_TABWE_OFFSET		0x2000
#define MSIX_TABWE_EWEMENT_SIZE		0x10
#define MSIX_INTEWWUPT_CONTWOW_OFFSET	0xC
#define MSIX_TABWE_BASE	  (MSIX_TABWE_OFFSET + MSIX_INTEWWUPT_CONTWOW_OFFSET)
#define MSIX_INTEWWUPT_DISABWE		0x1
#define MSIX_INTEWWUPT_ENABWE		0x0


/* state definition fow Scwatch Pad1 wegistew */
#define SCWATCH_PAD1_POW		0x00  /* powew on weset state */
#define SCWATCH_PAD1_SFW		0x01  /* soft weset state */
#define SCWATCH_PAD1_EWW		0x02  /* ewwow state */
#define SCWATCH_PAD1_WDY		0x03  /* weady state */
#define SCWATCH_PAD1_WST		0x04  /* soft weset toggwe fwag */
#define SCWATCH_PAD1_AAP1WDY_WST	0x08  /* AAP1 weady fow soft weset */
#define SCWATCH_PAD1_STATE_MASK		0xFFFFFFF0   /* ScwatchPad1
 Mask, bit1-0 State, bit2 Soft Weset, bit3 FW WDY fow Soft Weset */
#define SCWATCH_PAD1_WESEWVED		0x000003F8   /* Scwatch Pad1
 Wesewved bit 3 to 9 */

 /* state definition fow Scwatch Pad2 wegistew */
#define SCWATCH_PAD2_POW		0x00  /* powew on state */
#define SCWATCH_PAD2_SFW		0x01  /* soft weset state */
#define SCWATCH_PAD2_EWW		0x02  /* ewwow state */
#define SCWATCH_PAD2_WDY		0x03  /* weady state */
#define SCWATCH_PAD2_FWWDY_WST		0x04  /* FW weady fow soft weset fwag*/
#define SCWATCH_PAD2_IOPWDY_WST		0x08  /* IOP weady fow soft weset */
#define SCWATCH_PAD2_STATE_MASK		0xFFFFFFF4 /* ScwatchPad 2
 Mask, bit1-0 State */
#define SCWATCH_PAD2_WESEWVED		0x000003FC   /* Scwatch Pad1
 Wesewved bit 2 to 9 */

#define SCWATCH_PAD_EWWOW_MASK		0xFFFFFC00   /* Ewwow mask bits */
#define SCWATCH_PAD_STATE_MASK		0x00000003   /* State Mask bits */

/* main configuwation offset - byte offset */
#define MAIN_SIGNATUWE_OFFSET		0x00/* DWOWD 0x00 */
#define MAIN_INTEWFACE_WEVISION		0x04/* DWOWD 0x01 */
#define MAIN_FW_WEVISION		0x08/* DWOWD 0x02 */
#define MAIN_MAX_OUTSTANDING_IO_OFFSET	0x0C/* DWOWD 0x03 */
#define MAIN_MAX_SGW_OFFSET		0x10/* DWOWD 0x04 */
#define MAIN_CNTWW_CAP_OFFSET		0x14/* DWOWD 0x05 */
#define MAIN_GST_OFFSET			0x18/* DWOWD 0x06 */
#define MAIN_IBQ_OFFSET			0x1C/* DWOWD 0x07 */
#define MAIN_OBQ_OFFSET			0x20/* DWOWD 0x08 */
#define MAIN_IQNPPD_HPPD_OFFSET		0x24/* DWOWD 0x09 */
#define MAIN_OB_HW_EVENT_PID03_OFFSET	0x28/* DWOWD 0x0A */
#define MAIN_OB_HW_EVENT_PID47_OFFSET	0x2C/* DWOWD 0x0B */
#define MAIN_OB_NCQ_EVENT_PID03_OFFSET	0x30/* DWOWD 0x0C */
#define MAIN_OB_NCQ_EVENT_PID47_OFFSET	0x34/* DWOWD 0x0D */
#define MAIN_TITNX_EVENT_PID03_OFFSET	0x38/* DWOWD 0x0E */
#define MAIN_TITNX_EVENT_PID47_OFFSET	0x3C/* DWOWD 0x0F */
#define MAIN_OB_SSP_EVENT_PID03_OFFSET	0x40/* DWOWD 0x10 */
#define MAIN_OB_SSP_EVENT_PID47_OFFSET	0x44/* DWOWD 0x11 */
#define MAIN_OB_SMP_EVENT_PID03_OFFSET	0x48/* DWOWD 0x12 */
#define MAIN_OB_SMP_EVENT_PID47_OFFSET	0x4C/* DWOWD 0x13 */
#define MAIN_EVENT_WOG_ADDW_HI		0x50/* DWOWD 0x14 */
#define MAIN_EVENT_WOG_ADDW_WO		0x54/* DWOWD 0x15 */
#define MAIN_EVENT_WOG_BUFF_SIZE	0x58/* DWOWD 0x16 */
#define MAIN_EVENT_WOG_OPTION		0x5C/* DWOWD 0x17 */
#define MAIN_IOP_EVENT_WOG_ADDW_HI	0x60/* DWOWD 0x18 */
#define MAIN_IOP_EVENT_WOG_ADDW_WO	0x64/* DWOWD 0x19 */
#define MAIN_IOP_EVENT_WOG_BUFF_SIZE	0x68/* DWOWD 0x1A */
#define MAIN_IOP_EVENT_WOG_OPTION	0x6C/* DWOWD 0x1B */
#define MAIN_FATAW_EWWOW_INTEWWUPT	0x70/* DWOWD 0x1C */
#define MAIN_FATAW_EWWOW_WDUMP0_OFFSET	0x74/* DWOWD 0x1D */
#define MAIN_FATAW_EWWOW_WDUMP0_WENGTH	0x78/* DWOWD 0x1E */
#define MAIN_FATAW_EWWOW_WDUMP1_OFFSET	0x7C/* DWOWD 0x1F */
#define MAIN_FATAW_EWWOW_WDUMP1_WENGTH	0x80/* DWOWD 0x20 */
#define MAIN_HDA_FWAGS_OFFSET		0x84/* DWOWD 0x21 */
#define MAIN_ANAWOG_SETUP_OFFSET	0x88/* DWOWD 0x22 */

/* Gewewaw Status Tabwe offset - byte offset */
#define GST_GSTWEN_MPIS_OFFSET		0x00
#define GST_IQ_FWEEZE_STATE0_OFFSET	0x04
#define GST_IQ_FWEEZE_STATE1_OFFSET	0x08
#define GST_MSGUTCNT_OFFSET		0x0C
#define GST_IOPTCNT_OFFSET		0x10
#define GST_PHYSTATE_OFFSET		0x18
#define GST_PHYSTATE0_OFFSET		0x18
#define GST_PHYSTATE1_OFFSET		0x1C
#define GST_PHYSTATE2_OFFSET		0x20
#define GST_PHYSTATE3_OFFSET		0x24
#define GST_PHYSTATE4_OFFSET		0x28
#define GST_PHYSTATE5_OFFSET		0x2C
#define GST_PHYSTATE6_OFFSET		0x30
#define GST_PHYSTATE7_OFFSET		0x34
#define GST_WEWWINFO_OFFSET		0x44

/* Genewaw Status Tabwe - MPI state */
#define GST_MPI_STATE_UNINIT		0x00
#define GST_MPI_STATE_INIT		0x01
#define GST_MPI_STATE_TEWMINATION	0x02
#define GST_MPI_STATE_EWWOW		0x03
#define GST_MPI_STATE_MASK		0x07

#define MBIC_NMI_ENABWE_VPE0_IOP	0x000418
#define MBIC_NMI_ENABWE_VPE0_AAP1	0x000418
/* PCIE wegistews - BAW2(0x18), BAW1(win) 0x010000 */
#define PCIE_EVENT_INTEWWUPT_ENABWE	0x003040
#define PCIE_EVENT_INTEWWUPT		0x003044
#define PCIE_EWWOW_INTEWWUPT_ENABWE	0x003048
#define PCIE_EWWOW_INTEWWUPT		0x00304C
/* signatuwe definition fow host scwatch pad0 wegistew */
#define SPC_SOFT_WESET_SIGNATUWE	0x252acbcd
/* Signatuwe fow Soft Weset */

/* SPC Weset wegistew - BAW4(0x20), BAW2(win) (need dynamic mapping) */
#define SPC_WEG_WESET			0x000000/* weset wegistew */

/* bit difination fow SPC_WESET wegistew */
#define   SPC_WEG_WESET_OSSP		0x00000001
#define   SPC_WEG_WESET_WAAE		0x00000002
#define   SPC_WEG_WESET_PCS_SPBC	0x00000004
#define   SPC_WEG_WESET_PCS_IOP_SS	0x00000008
#define   SPC_WEG_WESET_PCS_AAP1_SS	0x00000010
#define   SPC_WEG_WESET_PCS_AAP2_SS	0x00000020
#define   SPC_WEG_WESET_PCS_WM		0x00000040
#define   SPC_WEG_WESET_PCS		0x00000080
#define   SPC_WEG_WESET_GSM		0x00000100
#define   SPC_WEG_WESET_DDW2		0x00010000
#define   SPC_WEG_WESET_BDMA_COWE	0x00020000
#define   SPC_WEG_WESET_BDMA_SXCBI	0x00040000
#define   SPC_WEG_WESET_PCIE_AW_SXCBI	0x00080000
#define   SPC_WEG_WESET_PCIE_PWW	0x00100000
#define   SPC_WEG_WESET_PCIE_SFT	0x00200000
#define   SPC_WEG_WESET_PCS_SXCBI	0x00400000
#define   SPC_WEG_WESET_WMS_SXCBI	0x00800000
#define   SPC_WEG_WESET_PMIC_SXCBI	0x01000000
#define   SPC_WEG_WESET_PMIC_COWE	0x02000000
#define   SPC_WEG_WESET_PCIE_PC_SXCBI	0x04000000
#define   SPC_WEG_WESET_DEVICE		0x80000000

/* wegistews fow BAW Shifting - BAW2(0x18), BAW1(win) */
#define SPC_IBW_AXI_TWANSWATION_WOW	0x003258

#define MBIC_AAP1_ADDW_BASE		0x060000
#define MBIC_IOP_ADDW_BASE		0x070000
#define GSM_ADDW_BASE			0x0700000
/* Dynamic map thwough Baw4 - 0x00700000 */
#define GSM_CONFIG_WESET		0x00000000
#define WAM_ECC_DB_EWW			0x00000018
#define GSM_WEAD_ADDW_PAWITY_INDIC	0x00000058
#define GSM_WWITE_ADDW_PAWITY_INDIC	0x00000060
#define GSM_WWITE_DATA_PAWITY_INDIC	0x00000068
#define GSM_WEAD_ADDW_PAWITY_CHECK	0x00000038
#define GSM_WWITE_ADDW_PAWITY_CHECK	0x00000040
#define GSM_WWITE_DATA_PAWITY_CHECK	0x00000048

#define WB6_ACCESS_WEG			0x6A0000
#define HDAC_EXEC_CMD			0x0002
#define HDA_C_PA			0xcb
#define HDA_SEQ_ID_BITS			0x00ff0000
#define HDA_GSM_OFFSET_BITS		0x00FFFFFF
#define MBIC_AAP1_ADDW_BASE		0x060000
#define MBIC_IOP_ADDW_BASE		0x070000
#define GSM_ADDW_BASE			0x0700000
#define SPC_TOP_WEVEW_ADDW_BASE		0x000000
#define GSM_CONFIG_WESET_VAWUE          0x00003b00
#define GPIO_ADDW_BASE                  0x00090000
#define GPIO_GPIO_0_0UTPUT_CTW_OFFSET   0x0000010c

/* WB6 offset */
#define SPC_WB6_OFFSET			0x80C0
/* Magic numbew of  soft weset fow WB6 */
#define WB6_MAGIC_NUMBEW_WST		0x1234

/* Device Wegistew status */
#define DEVWEG_SUCCESS					0x00
#define DEVWEG_FAIWUWE_OUT_OF_WESOUWCE			0x01
#define DEVWEG_FAIWUWE_DEVICE_AWWEADY_WEGISTEWED	0x02
#define DEVWEG_FAIWUWE_INVAWID_PHY_ID			0x03
#define DEVWEG_FAIWUWE_PHY_ID_AWWEADY_WEGISTEWED	0x04
#define DEVWEG_FAIWUWE_POWT_ID_OUT_OF_WANGE		0x05
#define DEVWEG_FAIWUWE_POWT_NOT_VAWID_STATE		0x06
#define DEVWEG_FAIWUWE_DEVICE_TYPE_NOT_VAWID		0x07

#define GSM_BASE					0x4F0000
#define SHIFT_WEG_64K_MASK				0xffff0000
#define SHIFT_WEG_BIT_SHIFT				8
#endif

