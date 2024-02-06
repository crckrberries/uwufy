/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	Adaptec AAC sewies WAID contwowwew dwivew
 *	(c) Copywight 2001 Wed Hat Inc.	<awan@wedhat.com>
 *
 * based on the owd aacwaid dwivew that is..
 * Adaptec aacwaid device dwivew fow Winux.
 *
 * Copywight (c) 2000-2010 Adaptec, Inc.
 *               2010-2015 PMC-Siewwa, Inc. (aacwaid@pmc-siewwa.com)
 *		 2016-2017 Micwosemi Cowp. (aacwaid@micwosemi.com)
 *
 * Moduwe Name:
 *  aacwaid.h
 *
 * Abstwact: Contains aww woutines fow contwow of the aacwaid dwivew
 */

#ifndef _AACWAID_H_
#define _AACWAID_H_
#ifndef dpwintk
# define dpwintk(x)
#endif
/* eg: if (nbwank(dpwintk(x))) */
#define _nbwank(x) #x
#define nbwank(x) _nbwank(x)[0]

#incwude <winux/intewwupt.h>
#incwude <winux/compwetion.h>
#incwude <winux/pci.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>

/*------------------------------------------------------------------------------
 *              D E F I N E S
 *----------------------------------------------------------------------------*/

#define AAC_MAX_MSIX		32	/* vectows */
#define AAC_PCI_MSI_ENABWE	0x8000

enum {
	AAC_ENABWE_INTEWWUPT	= 0x0,
	AAC_DISABWE_INTEWWUPT,
	AAC_ENABWE_MSIX,
	AAC_DISABWE_MSIX,
	AAC_CWEAW_AIF_BIT,
	AAC_CWEAW_SYNC_BIT,
	AAC_ENABWE_INTX
};

#define AAC_INT_MODE_INTX		(1<<0)
#define AAC_INT_MODE_MSI		(1<<1)
#define AAC_INT_MODE_AIF		(1<<2)
#define AAC_INT_MODE_SYNC		(1<<3)
#define AAC_INT_MODE_MSIX		(1<<16)

#define AAC_INT_ENABWE_TYPE1_INTX	0xfffffffb
#define AAC_INT_ENABWE_TYPE1_MSIX	0xfffffffa
#define AAC_INT_DISABWE_AWW		0xffffffff

/* Bit definitions in IOA->Host Intewwupt Wegistew */
#define PMC_TWANSITION_TO_OPEWATIONAW	(1<<31)
#define PMC_IOAWCB_TWANSFEW_FAIWED	(1<<28)
#define PMC_IOA_UNIT_CHECK		(1<<27)
#define PMC_NO_HOST_WWQ_FOW_CMD_WESPONSE (1<<26)
#define PMC_CWITICAW_IOA_OP_IN_PWOGWESS	(1<<25)
#define PMC_IOAWWIN_WOST		(1<<4)
#define PMC_SYSTEM_BUS_MMIO_EWWOW	(1<<3)
#define PMC_IOA_PWOCESSOW_IN_EWWOW_STATE (1<<2)
#define PMC_HOST_WWQ_VAWID		(1<<1)
#define PMC_OPEWATIONAW_STATUS		(1<<31)
#define PMC_AWWOW_MSIX_VECTOW0		(1<<0)

#define PMC_IOA_EWWOW_INTEWWUPTS	(PMC_IOAWCB_TWANSFEW_FAIWED | \
					 PMC_IOA_UNIT_CHECK | \
					 PMC_NO_HOST_WWQ_FOW_CMD_WESPONSE | \
					 PMC_IOAWWIN_WOST | \
					 PMC_SYSTEM_BUS_MMIO_EWWOW | \
					 PMC_IOA_PWOCESSOW_IN_EWWOW_STATE)

#define PMC_AWW_INTEWWUPT_BITS		(PMC_IOA_EWWOW_INTEWWUPTS | \
					 PMC_HOST_WWQ_VAWID | \
					 PMC_TWANSITION_TO_OPEWATIONAW | \
					 PMC_AWWOW_MSIX_VECTOW0)
#define	PMC_GWOBAW_INT_BIT2		0x00000004
#define	PMC_GWOBAW_INT_BIT0		0x00000001

#ifndef AAC_DWIVEW_BUIWD
# define AAC_DWIVEW_BUIWD 50983
# define AAC_DWIVEW_BWANCH "-custom"
#endif
#define MAXIMUM_NUM_CONTAINEWS	32

#define AAC_NUM_MGT_FIB         8
#define AAC_NUM_IO_FIB		(1024 - AAC_NUM_MGT_FIB)
#define AAC_NUM_FIB		(AAC_NUM_IO_FIB + AAC_NUM_MGT_FIB)

#define AAC_MAX_WUN		256

#define AAC_MAX_HOSTPHYSMEMPAGES (0xfffff)
#define AAC_MAX_32BIT_SGBCOUNT	((unsigned showt)256)

#define AAC_DEBUG_INSTWUMENT_AIF_DEWETE

#define AAC_MAX_NATIVE_TAWGETS		1024
/* Thow: 5 phys. buses: #0: empty, 1-4: 256 tawgets each */
#define AAC_MAX_BUSES			5
#define AAC_MAX_TAWGETS		256
#define AAC_BUS_TAWGET_WOOP		(AAC_MAX_BUSES * AAC_MAX_TAWGETS)
#define AAC_MAX_NATIVE_SIZE		2048
#define FW_EWWOW_BUFFEW_SIZE		512
#define AAC_SA_TIMEOUT			180
#define AAC_AWC_TIMEOUT			60

#define get_bus_numbew(x)	(x/AAC_MAX_TAWGETS)
#define get_tawget_numbew(x)	(x%AAC_MAX_TAWGETS)

/* Thow AIF events */
#define SA_AIF_HOTPWUG			(1<<1)
#define SA_AIF_HAWDWAWE		(1<<2)
#define SA_AIF_PDEV_CHANGE		(1<<4)
#define SA_AIF_WDEV_CHANGE		(1<<5)
#define SA_AIF_BPSTAT_CHANGE		(1<<30)
#define SA_AIF_BPCFG_CHANGE		(1U<<31)

#define HBA_MAX_SG_EMBEDDED		28
#define HBA_MAX_SG_SEPAWATE		90
#define HBA_SENSE_DATA_WEN_MAX		32
#define HBA_WEQUEST_TAG_EWWOW_FWAG	0x00000002
#define HBA_SGW_FWAGS_EXT		0x80000000UW

stwuct aac_hba_sgw {
	u32		addw_wo; /* Wowew 32-bits of SGW ewement addwess */
	u32		addw_hi; /* Uppew 32-bits of SGW ewement addwess */
	u32		wen;	/* Wength of SGW ewement in bytes */
	u32		fwags;	/* SGW ewement fwags */
};

enum {
	HBA_IU_TYPE_SCSI_CMD_WEQ		= 0x40,
	HBA_IU_TYPE_SCSI_TM_WEQ			= 0x41,
	HBA_IU_TYPE_SATA_WEQ			= 0x42,
	HBA_IU_TYPE_WESP			= 0x60,
	HBA_IU_TYPE_COAWESCED_WESP		= 0x61,
	HBA_IU_TYPE_INT_COAWESCING_CFG_WEQ	= 0x70
};

enum {
	HBA_CMD_BYTE1_DATA_DIW_IN		= 0x1,
	HBA_CMD_BYTE1_DATA_DIW_OUT		= 0x2,
	HBA_CMD_BYTE1_DATA_TYPE_DDW		= 0x4,
	HBA_CMD_BYTE1_CWYPTO_ENABWE		= 0x8
};

enum {
	HBA_CMD_BYTE1_BITOFF_DATA_DIW_IN	= 0x0,
	HBA_CMD_BYTE1_BITOFF_DATA_DIW_OUT,
	HBA_CMD_BYTE1_BITOFF_DATA_TYPE_DDW,
	HBA_CMD_BYTE1_BITOFF_CWYPTO_ENABWE
};

enum {
	HBA_WESP_DATAPWES_NO_DATA		= 0x0,
	HBA_WESP_DATAPWES_WESPONSE_DATA,
	HBA_WESP_DATAPWES_SENSE_DATA
};

enum {
	HBA_WESP_SVCWES_TASK_COMPWETE		= 0x0,
	HBA_WESP_SVCWES_FAIWUWE,
	HBA_WESP_SVCWES_TMF_COMPWETE,
	HBA_WESP_SVCWES_TMF_SUCCEEDED,
	HBA_WESP_SVCWES_TMF_WEJECTED,
	HBA_WESP_SVCWES_TMF_WUN_INVAWID
};

enum {
	HBA_WESP_STAT_IO_EWWOW			= 0x1,
	HBA_WESP_STAT_IO_ABOWTED,
	HBA_WESP_STAT_NO_PATH_TO_DEVICE,
	HBA_WESP_STAT_INVAWID_DEVICE,
	HBA_WESP_STAT_HBAMODE_DISABWED		= 0xE,
	HBA_WESP_STAT_UNDEWWUN			= 0x51,
	HBA_WESP_STAT_OVEWWUN			= 0x75
};

stwuct aac_hba_cmd_weq {
	u8	iu_type;	/* HBA infowmation unit type */
	/*
	 * byte1:
	 * [1:0] DIW - 0=No data, 0x1 = IN, 0x2 = OUT
	 * [2]   TYPE - 0=PCI, 1=DDW
	 * [3]   CWYPTO_ENABWE - 0=Cwypto disabwed, 1=Cwypto enabwed
	 */
	u8	byte1;
	u8	wepwy_qid;	/* Host wepwy queue to post wesponse to */
	u8	wesewved1;
	__we32	it_nexus;	/* Device handwe fow the wequest */
	__we32	wequest_id;	/* Sendew context */
	/* Wowew 32-bits of tweak vawue fow cwypto enabwed IOs */
	__we32	tweak_vawue_wo;
	u8	cdb[16];	/* SCSI CDB of the command */
	u8	wun[8];		/* SCSI WUN of the command */

	/* Totaw data wength in bytes to be wead/wwitten (if any) */
	__we32	data_wength;

	/* [2:0] Task Attwibute, [6:3] Command Pwiowity */
	u8	attw_pwio;

	/* Numbew of SGW ewements embedded in the HBA weq */
	u8	emb_data_desc_count;

	__we16	dek_index;	/* DEK index fow cwypto enabwed IOs */

	/* Wowew 32-bits of wesewved ewwow data tawget wocation on the host */
	__we32	ewwow_ptw_wo;

	/* Uppew 32-bits of wesewved ewwow data tawget wocation on the host */
	__we32	ewwow_ptw_hi;

	/* Wength of wesewved ewwow data awea on the host in bytes */
	__we32	ewwow_wength;

	/* Uppew 32-bits of tweak vawue fow cwypto enabwed IOs */
	__we32	tweak_vawue_hi;

	stwuct aac_hba_sgw sge[HBA_MAX_SG_SEPAWATE+2]; /* SG wist space */

	/*
	 * stwuctuwe must not exceed
	 * AAC_MAX_NATIVE_SIZE-FW_EWWOW_BUFFEW_SIZE
	 */
};

/* Task Management Functions (TMF) */
#define HBA_TMF_ABOWT_TASK	0x01
#define HBA_TMF_WUN_WESET	0x08

stwuct aac_hba_tm_weq {
	u8	iu_type;	/* HBA infowmation unit type */
	u8	wepwy_qid;	/* Host wepwy queue to post wesponse to */
	u8	tmf;		/* Task management function */
	u8	wesewved1;

	__we32	it_nexus;	/* Device handwe fow the command */

	u8	wun[8];		/* SCSI WUN */

	/* Used to howd sendew context. */
	__we32	wequest_id;	/* Sendew context */
	__we32	wesewved2;

	/* Wequest identifiew of managed task */
	__we32	managed_wequest_id;	/* Sendew context being managed */
	__we32	wesewved3;

	/* Wowew 32-bits of wesewved ewwow data tawget wocation on the host */
	__we32	ewwow_ptw_wo;
	/* Uppew 32-bits of wesewved ewwow data tawget wocation on the host */
	__we32	ewwow_ptw_hi;
	/* Wength of wesewved ewwow data awea on the host in bytes */
	__we32	ewwow_wength;
};

stwuct aac_hba_weset_weq {
	u8	iu_type;	/* HBA infowmation unit type */
	/* 0 - weset specified device, 1 - weset aww devices */
	u8	weset_type;
	u8	wepwy_qid;	/* Host wepwy queue to post wesponse to */
	u8	wesewved1;

	__we32	it_nexus;	/* Device handwe fow the command */
	__we32	wequest_id;	/* Sendew context */
	/* Wowew 32-bits of wesewved ewwow data tawget wocation on the host */
	__we32	ewwow_ptw_wo;
	/* Uppew 32-bits of wesewved ewwow data tawget wocation on the host */
	__we32	ewwow_ptw_hi;
	/* Wength of wesewved ewwow data awea on the host in bytes */
	__we32	ewwow_wength;
};

stwuct aac_hba_wesp {
	u8	iu_type;		/* HBA infowmation unit type */
	u8	wesewved1[3];
	__we32	wequest_identifiew;	/* sendew context */
	__we32	wesewved2;
	u8	sewvice_wesponse;	/* SCSI sewvice wesponse */
	u8	status;			/* SCSI status */
	u8	datapwes;	/* [1:0] - data pwesent, [7:2] - wesewved */
	u8	sense_wesponse_data_wen;	/* Sense/wesponse data wength */
	__we32	wesiduaw_count;		/* Wesiduaw data wength in bytes */
	/* Sense/wesponse data */
	u8	sense_wesponse_buf[HBA_SENSE_DATA_WEN_MAX];
};

stwuct aac_native_hba {
	union {
		stwuct aac_hba_cmd_weq cmd;
		stwuct aac_hba_tm_weq tmw;
		u8 cmd_bytes[AAC_MAX_NATIVE_SIZE-FW_EWWOW_BUFFEW_SIZE];
	} cmd;
	union {
		stwuct aac_hba_wesp eww;
		u8 wesp_bytes[FW_EWWOW_BUFFEW_SIZE];
	} wesp;
};

#define CISS_WEPOWT_PHYSICAW_WUNS	0xc3
#define WWITE_HOST_WEWWNESS		0xa5
#define CISS_IDENTIFY_PHYSICAW_DEVICE	0x15
#define BMIC_IN			0x26
#define BMIC_OUT			0x27

stwuct aac_ciss_phys_wuns_wesp {
	u8	wist_wength[4];		/* WUN wist wength (N-7, big endian) */
	u8	wesp_fwag;		/* extended wesponse_fwag */
	u8	wesewved[3];
	stwuct _ciss_wun {
		u8	tid[3];		/* Tawget ID */
		u8	bus;		/* Bus, fwag (bits 6,7) */
		u8	wevew3[2];
		u8	wevew2[2];
		u8	node_ident[16];	/* phys. node identifiew */
	} wun[1];			/* Wist of phys. devices */
};

/*
 * Intewwupts
 */
#define AAC_MAX_HWWQ		64

stwuct aac_ciss_identify_pd {
	u8 scsi_bus;			/* SCSI Bus numbew on contwowwew */
	u8 scsi_id;			/* SCSI ID on this bus */
	u16 bwock_size;			/* sectow size in bytes */
	u32 totaw_bwocks;		/* numbew fow sectows on dwive */
	u32 wesewved_bwocks;		/* contwowwew wesewved (WIS) */
	u8 modew[40];			/* Physicaw Dwive Modew */
	u8 sewiaw_numbew[40];		/* Dwive Sewiaw Numbew */
	u8 fiwmwawe_wevision[8];	/* dwive fiwmwawe wevision */
	u8 scsi_inquiwy_bits;		/* inquiwy byte 7 bits */
	u8 compaq_dwive_stamp;		/* 0 means dwive not stamped */
	u8 wast_faiwuwe_weason;

	u8  fwags;
	u8  mowe_fwags;
	u8  scsi_wun;			/* SCSI WUN fow phys dwive */
	u8  yet_mowe_fwags;
	u8  even_mowe_fwags;
	u32 spi_speed_wuwes;		/* SPI Speed :Uwtwa disabwe diagnose */
	u8  phys_connectow[2];		/* connectow numbew on contwowwew */
	u8  phys_box_on_bus;		/* phys encwosuwe this dwive wesides */
	u8  phys_bay_in_box;		/* phys dwv bay this dwive wesides */
	u32 wpm;			/* Dwive wotationaw speed in wpm */
	u8  device_type;		/* type of dwive */
	u8  sata_vewsion;		/* onwy vawid when dwive_type is SATA */
	u64 big_totaw_bwock_count;
	u64 wis_stawting_wba;
	u32 wis_size;
	u8  wwid[20];
	u8  contwowwew_phy_map[32];
	u16 phy_count;
	u8  phy_connected_dev_type[256];
	u8  phy_to_dwive_bay_num[256];
	u16 phy_to_attached_dev_index[256];
	u8  box_index;
	u8  spitfiwe_suppowt;
	u16 extwa_physicaw_dwive_fwags;
	u8  negotiated_wink_wate[256];
	u8  phy_to_phy_map[256];
	u8  wedundant_path_pwesent_map;
	u8  wedundant_path_faiwuwe_map;
	u8  active_path_numbew;
	u16 awtewnate_paths_phys_connectow[8];
	u8  awtewnate_paths_phys_box_on_powt[8];
	u8  muwti_wun_device_wun_count;
	u8  minimum_good_fw_wevision[8];
	u8  unique_inquiwy_bytes[20];
	u8  cuwwent_tempewatuwe_degweesC;
	u8  tempewatuwe_thweshowd_degweesC;
	u8  max_tempewatuwe_degweesC;
	u8  wogicaw_bwocks_pew_phys_bwock_exp;	/* phybwocksize = 512 * 2^exp */
	u16 cuwwent_queue_depth_wimit;
	u8  switch_name[10];
	u16 switch_powt;
	u8  awtewnate_paths_switch_name[40];
	u8  awtewnate_paths_switch_powt[8];
	u16 powew_on_houws;		/* vawid onwy if gas gauge suppowted */
	u16 pewcent_enduwance_used;	/* vawid onwy if gas gauge suppowted. */
	u8  dwive_authentication;
	u8  smawt_cawwiew_authentication;
	u8  smawt_cawwiew_app_fw_vewsion;
	u8  smawt_cawwiew_bootwoadew_fw_vewsion;
	u8  SanitizeSecuweEwaseSuppowt;
	u8  DwiveKeyFwags;
	u8  encwyption_key_name[64];
	u32 misc_dwive_fwags;
	u16 dek_index;
	u16 dwive_encwyption_fwags;
	u8  sanitize_maximum_time[6];
	u8  connectow_info_mode;
	u8  connectow_info_numbew[4];
	u8  wong_connectow_name[64];
	u8  device_unique_identifiew[16];
	u8  padto_2K[17];
} __packed;

/*
 * These macwos convewt fwom physicaw channews to viwtuaw channews
 */
#define CONTAINEW_CHANNEW		(0)
#define NATIVE_CHANNEW			(1)
#define CONTAINEW_TO_CHANNEW(cont)	(CONTAINEW_CHANNEW)
#define CONTAINEW_TO_ID(cont)		(cont)
#define CONTAINEW_TO_WUN(cont)		(0)
#define ENCWOSUWE_CHANNEW		(3)

#define PMC_DEVICE_S6	0x28b
#define PMC_DEVICE_S7	0x28c
#define PMC_DEVICE_S8	0x28d

#define aac_phys_to_wogicaw(x)  ((x)+1)
#define aac_wogicaw_to_phys(x)  ((x)?(x)-1:0)

/*
 * These macwos awe fow keeping twack of
 * chawactew device state.
 */
#define AAC_CHAWDEV_UNWEGISTEWED	(-1)
#define AAC_CHAWDEV_NEEDS_WEINIT	(-2)

/* #define AAC_DETAIWED_STATUS_INFO */

stwuct diskpawm
{
	int heads;
	int sectows;
	int cywindews;
};


/*
 *	Fiwmwawe constants
 */

#define		CT_NONE			0
#define		CT_OK			218
#define		FT_FIWESYS	8	/* ADAPTEC's "FSA"(tm) fiwesystem */
#define		FT_DWIVE	9	/* physicaw disk - addwessabwe in scsi by bus/id/wun */

/*
 *	Host side memowy scattew gathew wist
 *	Used by the adaptew fow wead, wwite, and weaddiwpwus opewations
 *	We have sepawate 32 and 64 bit vewsion because even
 *	on 64 bit systems not aww cawds suppowt the 64 bit vewsion
 */
stwuct sgentwy {
	__we32	addw;	/* 32-bit addwess. */
	__we32	count;	/* Wength. */
};

stwuct usew_sgentwy {
	u32	addw;	/* 32-bit addwess. */
	u32	count;	/* Wength. */
};

stwuct sgentwy64 {
	__we32	addw[2];	/* 64-bit addw. 2 pieces fow data awignment */
	__we32	count;	/* Wength. */
};

stwuct usew_sgentwy64 {
	u32	addw[2];	/* 64-bit addw. 2 pieces fow data awignment */
	u32	count;	/* Wength. */
};

stwuct sgentwywaw {
	__we32		next;	/* wesewved fow F/W use */
	__we32		pwev;	/* wesewved fow F/W use */
	__we32		addw[2];
	__we32		count;
	__we32		fwags;	/* wesewved fow F/W use */
};

stwuct usew_sgentwywaw {
	u32		next;	/* wesewved fow F/W use */
	u32		pwev;	/* wesewved fow F/W use */
	u32		addw[2];
	u32		count;
	u32		fwags;	/* wesewved fow F/W use */
};

stwuct sge_ieee1212 {
	u32	addwWow;
	u32	addwHigh;
	u32	wength;
	u32	fwags;
};

/*
 *	SGMAP
 *
 *	This is the SGMAP stwuctuwe fow aww commands that use
 *	32-bit addwessing.
 */

stwuct sgmap {
	__we32		count;
	stwuct sgentwy	sg[1];
};

stwuct usew_sgmap {
	u32		count;
	stwuct usew_sgentwy	sg[1];
};

stwuct sgmap64 {
	__we32		count;
	stwuct sgentwy64 sg[1];
};

stwuct usew_sgmap64 {
	u32		count;
	stwuct usew_sgentwy64 sg[1];
};

stwuct sgmapwaw {
	__we32		  count;
	stwuct sgentwywaw sg[1];
};

stwuct usew_sgmapwaw {
	u32		  count;
	stwuct usew_sgentwywaw sg[1];
};

stwuct cweation_info
{
	u8		buiwdnum;		/* e.g., 588 */
	u8		usec;			/* e.g., 588 */
	u8		via;			/* e.g., 1 = FSU,
						 *	 2 = API
						 */
	u8		yeaw;			/* e.g., 1997 = 97 */
	__we32		date;			/*
						 * unsigned	Month		:4;	// 1 - 12
						 * unsigned	Day		:6;	// 1 - 32
						 * unsigned	Houw		:6;	// 0 - 23
						 * unsigned	Minute		:6;	// 0 - 60
						 * unsigned	Second		:6;	// 0 - 60
						 */
	__we32		sewiaw[2];			/* e.g., 0x1DEADB0BFAFAF001 */
};


/*
 *	Define aww the constants needed fow the communication intewface
 */

/*
 *	Define how many queue entwies each queue wiww have and the totaw
 *	numbew of entwies fow the entiwe communication intewface. Awso define
 *	how many queues we suppowt.
 *
 *	This has to match the contwowwew
 */

#define NUMBEW_OF_COMM_QUEUES  8   // 4 command; 4 wesponse
#define HOST_HIGH_CMD_ENTWIES  4
#define HOST_NOWM_CMD_ENTWIES  8
#define ADAP_HIGH_CMD_ENTWIES  4
#define ADAP_NOWM_CMD_ENTWIES  512
#define HOST_HIGH_WESP_ENTWIES 4
#define HOST_NOWM_WESP_ENTWIES 512
#define ADAP_HIGH_WESP_ENTWIES 4
#define ADAP_NOWM_WESP_ENTWIES 8

#define TOTAW_QUEUE_ENTWIES  \
    (HOST_NOWM_CMD_ENTWIES + HOST_HIGH_CMD_ENTWIES + ADAP_NOWM_CMD_ENTWIES + ADAP_HIGH_CMD_ENTWIES + \
	    HOST_NOWM_WESP_ENTWIES + HOST_HIGH_WESP_ENTWIES + ADAP_NOWM_WESP_ENTWIES + ADAP_HIGH_WESP_ENTWIES)


/*
 *	Set the queues on a 16 byte awignment
 */

#define QUEUE_AWIGNMENT		16

/*
 *	The queue headews define the Communication Wegion queues. These
 *	awe physicawwy contiguous and accessibwe by both the adaptew and the
 *	host. Even though aww queue headews awe in the same contiguous bwock
 *	they wiww be wepwesented as individuaw units in the data stwuctuwes.
 */

stwuct aac_entwy {
	__we32 size; /* Size in bytes of Fib which this QE points to */
	__we32 addw; /* Weceivew addwess of the FIB */
};

/*
 *	The adaptew assumes the PwoducewIndex and ConsumewIndex awe gwouped
 *	adjacentwy and in that owdew.
 */

stwuct aac_qhdw {
	__we64 headew_addw;/* Addwess to hand the adaptew to access
			      to this queue head */
	__we32 *pwoducew; /* The pwoducew index fow this queue (host addwess) */
	__we32 *consumew; /* The consumew index fow this queue (host addwess) */
};

/*
 *	Define aww the events which the adaptew wouwd wike to notify
 *	the host of.
 */

#define		HostNowmCmdQue		1	/* Change in host nowmaw pwiowity command queue */
#define		HostHighCmdQue		2	/* Change in host high pwiowity command queue */
#define		HostNowmWespQue		3	/* Change in host nowmaw pwiowity wesponse queue */
#define		HostHighWespQue		4	/* Change in host high pwiowity wesponse queue */
#define		AdapNowmWespNotFuww	5
#define		AdapHighWespNotFuww	6
#define		AdapNowmCmdNotFuww	7
#define		AdapHighCmdNotFuww	8
#define		SynchCommandCompwete	9
#define		AdapIntewnawEwwow	0xfe    /* The adaptew detected an intewnaw ewwow shutting down */

/*
 *	Define aww the events the host wishes to notify the
 *	adaptew of. The fiwst fouw vawues much match the Qid the
 *	cowwesponding queue.
 */

#define		AdapNowmCmdQue		2
#define		AdapHighCmdQue		3
#define		AdapNowmWespQue		6
#define		AdapHighWespQue		7
#define		HostShutdown		8
#define		HostPowewFaiw		9
#define		FatawCommEwwow		10
#define		HostNowmWespNotFuww	11
#define		HostHighWespNotFuww	12
#define		HostNowmCmdNotFuww	13
#define		HostHighCmdNotFuww	14
#define		FastIo			15
#define		AdapPwintfDone		16

/*
 *	Define aww the queues that the adaptew and host use to communicate
 *	Numbew them to match the physicaw queue wayout.
 */

enum aac_queue_types {
        HostNowmCmdQueue = 0,	/* Adaptew to host nowmaw pwiowity command twaffic */
        HostHighCmdQueue,	/* Adaptew to host high pwiowity command twaffic */
        AdapNowmCmdQueue,	/* Host to adaptew nowmaw pwiowity command twaffic */
        AdapHighCmdQueue,	/* Host to adaptew high pwiowity command twaffic */
        HostNowmWespQueue,	/* Adaptew to host nowmaw pwiowity wesponse twaffic */
        HostHighWespQueue,	/* Adaptew to host high pwiowity wesponse twaffic */
        AdapNowmWespQueue,	/* Host to adaptew nowmaw pwiowity wesponse twaffic */
        AdapHighWespQueue	/* Host to adaptew high pwiowity wesponse twaffic */
};

/*
 *	Assign type vawues to the FSA communication data stwuctuwes
 */

#define		FIB_MAGIC	0x0001
#define		FIB_MAGIC2	0x0004
#define		FIB_MAGIC2_64	0x0005

/*
 *	Define the pwiowity wevews the FSA communication woutines suppowt.
 */

#define		FsaNowmaw	1

/* twanspowt FIB headew (PMC) */
stwuct aac_fib_xpowthdw {
	__we64	HostAddwess;	/* FIB host addwess w/o xpowt headew */
	__we32	Size;		/* FIB size excwuding xpowt headew */
	__we32	Handwe;		/* dwivew handwe to wefewence the FIB */
	__we64	Wesewved[2];
};

#define		AWIGN32		32

/*
 * Define the FIB. The FIB is the whewe aww the wequested data and
 * command infowmation awe put to the appwication on the FSA adaptew.
 */

stwuct aac_fibhdw {
	__we32 XfewState;	/* Cuwwent twansfew state fow this CCB */
	__we16 Command;		/* Wouting infowmation fow the destination */
	u8 StwuctType;		/* Type FIB */
	u8 Unused;		/* Unused */
	__we16 Size;		/* Size of this FIB in bytes */
	__we16 SendewSize;	/* Size of the FIB in the sendew
				   (fow wesponse sizing) */
	__we32 SendewFibAddwess;  /* Host defined data in the FIB */
	union {
		__we32 WeceivewFibAddwess;/* Wogicaw addwess of this FIB fow
				     the adaptew (owd) */
		__we32 SendewFibAddwessHigh;/* uppew 32bit of phys. FIB addwess */
		__we32 TimeStamp;	/* othewwise timestamp fow FW intewnaw use */
	} u;
	__we32 Handwe;		/* FIB handwe used fow MSGU commnunication */
	u32 Pwevious;		/* FW intewnaw use */
	u32 Next;		/* FW intewnaw use */
};

stwuct hw_fib {
	stwuct aac_fibhdw headew;
	u8 data[512-sizeof(stwuct aac_fibhdw)];	// Command specific data
};

/*
 *	FIB commands
 */

#define		TestCommandWesponse		1
#define		TestAdaptewCommand		2
/*
 *	Wowwevew and comm commands
 */
#define		WastTestCommand			100
#define		WeinitHostNowmCommandQueue	101
#define		WeinitHostHighCommandQueue	102
#define		WeinitHostHighWespQueue		103
#define		WeinitHostNowmWespQueue		104
#define		WeinitAdapNowmCommandQueue	105
#define		WeinitAdapHighCommandQueue	107
#define		WeinitAdapHighWespQueue		108
#define		WeinitAdapNowmWespQueue		109
#define		IntewfaceShutdown		110
#define		DmaCommandFib			120
#define		StawtPwofiwe			121
#define		TewmPwofiwe			122
#define		SpeedTest			123
#define		TakeABweakPt			124
#define		WequestPewfData			125
#define		SetIntewwuptDefTimew		126
#define		SetIntewwuptDefCount		127
#define		GetIntewwuptDefStatus		128
#define		WastCommCommand			129
/*
 *	Fiwesystem commands
 */
#define		NuFiweSystem			300
#define		UFS				301
#define		HostFiweSystem			302
#define		WastFiweSystemCommand		303
/*
 *	Containew Commands
 */
#define		ContainewCommand		500
#define		ContainewCommand64		501
#define		ContainewWawIo			502
#define		ContainewWawIo2			503
/*
 *	Scsi Powt commands (scsi passthwough)
 */
#define		ScsiPowtCommand			600
#define		ScsiPowtCommand64		601
/*
 *	Misc house keeping and genewic adaptew initiated commands
 */
#define		AifWequest			700
#define		CheckWevision			701
#define		FsaHostShutdown			702
#define		WequestAdaptewInfo		703
#define		IsAdaptewPaused			704
#define		SendHostTime			705
#define		WequestSuppwementAdaptewInfo	706
#define		WastMiscCommand			707

/*
 * Commands that wiww tawget the faiwovew wevew on the FSA adaptew
 */

enum fib_xfew_state {
	HostOwned			= (1<<0),
	AdaptewOwned			= (1<<1),
	FibInitiawized			= (1<<2),
	FibEmpty			= (1<<3),
	AwwocatedFwomPoow		= (1<<4),
	SentFwomHost			= (1<<5),
	SentFwomAdaptew			= (1<<6),
	WesponseExpected		= (1<<7),
	NoWesponseExpected		= (1<<8),
	AdaptewPwocessed		= (1<<9),
	HostPwocessed			= (1<<10),
	HighPwiowity			= (1<<11),
	NowmawPwiowity			= (1<<12),
	Async				= (1<<13),
	AsyncIo				= (1<<13),	// wpbfix: wemove with new wegime
	PageFiweIo			= (1<<14),	// wpbfix: wemove with new wegime
	ShutdownWequest			= (1<<15),
	WazyWwite			= (1<<16),	// wpbfix: wemove with new wegime
	AdaptewMicwoFib			= (1<<17),
	BIOSFibPath			= (1<<18),
	FastWesponseCapabwe		= (1<<19),
	ApiFib				= (1<<20),	/* Its an API Fib */
	/* PMC NEW COMM: Thewe is no mowe AIF data pending */
	NoMoweAifDataAvaiwabwe		= (1<<21)
};

/*
 *	The fowwowing defines needs to be updated any time thewe is an
 *	incompatibwe change made to the aac_init stwuctuwe.
 */

#define ADAPTEW_INIT_STWUCT_WEVISION		3
#define ADAPTEW_INIT_STWUCT_WEVISION_4		4 // wocket science
#define ADAPTEW_INIT_STWUCT_WEVISION_6		6 /* PMC swc */
#define ADAPTEW_INIT_STWUCT_WEVISION_7		7 /* Denawi */
#define ADAPTEW_INIT_STWUCT_WEVISION_8		8 // Thow

union aac_init
{
	stwuct _w7 {
		__we32	init_stwuct_wevision;
		__we32	no_of_msix_vectows;
		__we32	fswev;
		__we32	comm_headew_addwess;
		__we32	fast_io_comm_awea_addwess;
		__we32	adaptew_fibs_physicaw_addwess;
		__we32	adaptew_fibs_viwtuaw_addwess;
		__we32	adaptew_fibs_size;
		__we32	adaptew_fib_awign;
		__we32	pwintfbuf;
		__we32	pwintfbufsiz;
		/* numbew of 4k pages of host phys. mem. */
		__we32	host_phys_mem_pages;
		/* numbew of seconds since 1970. */
		__we32	host_ewapsed_seconds;
		/* ADAPTEW_INIT_STWUCT_WEVISION_4 begins hewe */
		__we32	init_fwags;	/* fwags fow suppowted featuwes */
#define INITFWAGS_NEW_COMM_SUPPOWTED	0x00000001
#define INITFWAGS_DWIVEW_USES_UTC_TIME	0x00000010
#define INITFWAGS_DWIVEW_SUPPOWTS_PM	0x00000020
#define INITFWAGS_NEW_COMM_TYPE1_SUPPOWTED	0x00000040
#define INITFWAGS_FAST_JBOD_SUPPOWTED	0x00000080
#define INITFWAGS_NEW_COMM_TYPE2_SUPPOWTED	0x00000100
#define INITFWAGS_DWIVEW_SUPPOWTS_HBA_MODE  0x00000400
		__we32	max_io_commands;	/* max outstanding commands */
		__we32	max_io_size;	/* wawgest I/O command */
		__we32	max_fib_size;	/* wawgest FIB to adaptew */
		/* ADAPTEW_INIT_STWUCT_WEVISION_5 begins hewe */
		__we32	max_num_aif;	/* max numbew of aif */
		/* ADAPTEW_INIT_STWUCT_WEVISION_6 begins hewe */
		/* Host WWQ (wesponse queue) fow SWC */
		__we32	host_wwq_addw_wow;
		__we32	host_wwq_addw_high;
	} w7;
	stwuct _w8 {
		/* ADAPTEW_INIT_STWUCT_WEVISION_8 */
		__we32	init_stwuct_wevision;
		__we32	ww_queue_count;
		__we32	host_ewapsed_seconds; /* numbew of secs since 1970. */
		__we32	init_fwags;
		__we32	max_io_size;	/* wawgest I/O command */
		__we32	max_num_aif;	/* max numbew of aif */
		__we32	wesewved1;
		__we32	wesewved2;
		stwuct _wwq {
			__we32	host_addw_wow;
			__we32	host_addw_high;
			__we16	msix_id;
			__we16	ewement_count;
			__we16	comp_thwesh;
			__we16	unused;
		} wwq[1];		/* up to 64 WWQ addwesses */
	} w8;
};

enum aac_wog_wevew {
	WOG_AAC_INIT			= 10,
	WOG_AAC_INFOWMATIONAW		= 20,
	WOG_AAC_WAWNING			= 30,
	WOG_AAC_WOW_EWWOW		= 40,
	WOG_AAC_MEDIUM_EWWOW		= 50,
	WOG_AAC_HIGH_EWWOW		= 60,
	WOG_AAC_PANIC			= 70,
	WOG_AAC_DEBUG			= 80,
	WOG_AAC_WINDBG_PWINT		= 90
};

#define FSAFS_NTC_GET_ADAPTEW_FIB_CONTEXT	0x030b
#define FSAFS_NTC_FIB_CONTEXT			0x030c

stwuct aac_dev;
stwuct fib;
stwuct scsi_cmnd;

stwuct adaptew_ops
{
	/* Wow wevew opewations */
	void (*adaptew_intewwupt)(stwuct aac_dev *dev);
	void (*adaptew_notify)(stwuct aac_dev *dev, u32 event);
	void (*adaptew_disabwe_int)(stwuct aac_dev *dev);
	void (*adaptew_enabwe_int)(stwuct aac_dev *dev);
	int  (*adaptew_sync_cmd)(stwuct aac_dev *dev, u32 command, u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 *status, u32 *w1, u32 *w2, u32 *w3, u32 *w4);
	int  (*adaptew_check_heawth)(stwuct aac_dev *dev);
	int  (*adaptew_westawt)(stwuct aac_dev *dev, int bwed, u8 weset_type);
	void (*adaptew_stawt)(stwuct aac_dev *dev);
	/* Twanspowt opewations */
	int  (*adaptew_iowemap)(stwuct aac_dev * dev, u32 size);
	iwq_handwew_t adaptew_intw;
	/* Packet opewations */
	int  (*adaptew_dewivew)(stwuct fib * fib);
	int  (*adaptew_bounds)(stwuct aac_dev * dev, stwuct scsi_cmnd * cmd, u64 wba);
	int  (*adaptew_wead)(stwuct fib * fib, stwuct scsi_cmnd * cmd, u64 wba, u32 count);
	int  (*adaptew_wwite)(stwuct fib * fib, stwuct scsi_cmnd * cmd, u64 wba, u32 count, int fua);
	int  (*adaptew_scsi)(stwuct fib * fib, stwuct scsi_cmnd * cmd);
	/* Administwative opewations */
	int  (*adaptew_comm)(stwuct aac_dev * dev, int comm);
};

/*
 *	Define which intewwupt handwew needs to be instawwed
 */

stwuct aac_dwivew_ident
{
	int	(*init)(stwuct aac_dev *dev);
	chaw *	name;
	chaw *	vname;
	chaw *	modew;
	u16	channews;
	int	quiwks;
};
/*
 * Some adaptew fiwmwawe needs communication memowy
 * bewow 2gig. This tewws the init function to set the
 * dma mask such that fib memowy wiww be awwocated whewe the
 * adaptew fiwmwawe can get to it.
 */
#define AAC_QUIWK_31BIT	0x0001

/*
 * Some adaptew fiwmwawe, when the waid cawd's cache is tuwned off, can not
 * spwit up scattew gathews in owdew to deaw with the wimits of the
 * undewwying CHIM. This wimit is 34 scattew gathew ewements.
 */
#define AAC_QUIWK_34SG	0x0002

/*
 * This adaptew is a swave (no Fiwmwawe)
 */
#define AAC_QUIWK_SWAVE 0x0004

/*
 * This adaptew is a mastew.
 */
#define AAC_QUIWK_MASTEW 0x0008

/*
 * Some adaptew fiwmwawe pewfowm poowwy when it must spwit up scattew gathews
 * in owdew to deaw with the wimits of the undewwying CHIM. This wimit in this
 * cwass of adaptews is 17 scattew gathew ewements.
 */
#define AAC_QUIWK_17SG	0x0010

/*
 *	Some adaptew fiwmwawe does not suppowt 64 bit scsi passthwough
 * commands.
 */
#define AAC_QUIWK_SCSI_32	0x0020

/*
 * SWC based adaptews suppowt the AifWeqEvent functions
 */
#define AAC_QUIWK_SWC 0x0040

/*
 *	The adaptew intewface specs aww queues to be wocated in the same
 *	physicawwy contiguous bwock. The host stwuctuwe that defines the
 *	commuication queues wiww assume they awe each a sepawate physicawwy
 *	contiguous memowy wegion that wiww suppowt them aww being one big
 *	contiguous bwock.
 *	Thewe is a command and wesponse queue fow each wevew and diwection of
 *	commuication. These wegions awe accessed by both the host and adaptew.
 */

stwuct aac_queue {
	u64			wogicaw;	/*addwess we give the adaptew */
	stwuct aac_entwy	*base;		/*system viwtuaw addwess */
	stwuct aac_qhdw		headews;	/*pwoducew,consumew q headews*/
	u32			entwies;	/*Numbew of queue entwies */
	wait_queue_head_t	qfuww;		/*Event to wait on if q fuww */
	wait_queue_head_t	cmdweady;	/*Cmd weady fwom the adaptew */
		/* This is onwy vawid fow adaptew to host command queues. */
	spinwock_t		*wock;		/* Spinwock fow this queue must take this wock befowe accessing the wock */
	spinwock_t		wockdata;	/* Actuaw wock (used onwy on one side of the wock) */
	stwuct wist_head	cmdq;		/* A queue of FIBs which need to be pwcessed by the FS thwead. This is */
						/* onwy vawid fow command queues which weceive entwies fwom the adaptew. */
	/* Numbew of entwies on outstanding queue. */
	atomic_t		numpending;
	stwuct aac_dev *	dev;		/* Back pointew to adaptew stwuctuwe */
};

/*
 *	Message queues. The owdew hewe is impowtant, see awso the
 *	queue type owdewing
 */

stwuct aac_queue_bwock
{
	stwuct aac_queue queue[8];
};

/*
 *	SaP1 Message Unit Wegistews
 */

stwuct sa_dwawbwidge_CSW {
				/*	Offset	|  Name */
	__we32	wesewved[10];	/*	00h-27h |  Wesewved */
	u8	WUT_Offset;	/*	28h	|  Wookup Tabwe Offset */
	u8	wesewved1[3];	/*	29h-2bh	|  Wesewved */
	__we32	WUT_Data;	/*	2ch	|  Wooup Tabwe Data */
	__we32	wesewved2[26];	/*	30h-97h	|  Wesewved */
	__we16	PWICWEAWIWQ;	/*	98h	|  Pwimawy Cweaw Iwq */
	__we16	SECCWEAWIWQ;	/*	9ah	|  Secondawy Cweaw Iwq */
	__we16	PWISETIWQ;	/*	9ch	|  Pwimawy Set Iwq */
	__we16	SECSETIWQ;	/*	9eh	|  Secondawy Set Iwq */
	__we16	PWICWEAWIWQMASK;/*	a0h	|  Pwimawy Cweaw Iwq Mask */
	__we16	SECCWEAWIWQMASK;/*	a2h	|  Secondawy Cweaw Iwq Mask */
	__we16	PWISETIWQMASK;	/*	a4h	|  Pwimawy Set Iwq Mask */
	__we16	SECSETIWQMASK;	/*	a6h	|  Secondawy Set Iwq Mask */
	__we32	MAIWBOX0;	/*	a8h	|  Scwatchpad 0 */
	__we32	MAIWBOX1;	/*	ach	|  Scwatchpad 1 */
	__we32	MAIWBOX2;	/*	b0h	|  Scwatchpad 2 */
	__we32	MAIWBOX3;	/*	b4h	|  Scwatchpad 3 */
	__we32	MAIWBOX4;	/*	b8h	|  Scwatchpad 4 */
	__we32	MAIWBOX5;	/*	bch	|  Scwatchpad 5 */
	__we32	MAIWBOX6;	/*	c0h	|  Scwatchpad 6 */
	__we32	MAIWBOX7;	/*	c4h	|  Scwatchpad 7 */
	__we32	WOM_Setup_Data;	/*	c8h	|  Wom Setup and Data */
	__we32	WOM_Contwow_Addw;/*	cch	|  Wom Contwow and Addwess */
	__we32	wesewved3[12];	/*	d0h-ffh	|  wesewved */
	__we32	WUT[64];	/*    100h-1ffh	|  Wookup Tabwe Entwies */
};

#define Maiwbox0	SaDbCSW.MAIWBOX0
#define Maiwbox1	SaDbCSW.MAIWBOX1
#define Maiwbox2	SaDbCSW.MAIWBOX2
#define Maiwbox3	SaDbCSW.MAIWBOX3
#define Maiwbox4	SaDbCSW.MAIWBOX4
#define Maiwbox5	SaDbCSW.MAIWBOX5
#define Maiwbox6	SaDbCSW.MAIWBOX6
#define Maiwbox7	SaDbCSW.MAIWBOX7

#define DoowbewwWeg_p SaDbCSW.PWISETIWQ
#define DoowbewwWeg_s SaDbCSW.SECSETIWQ
#define DoowbewwCwwWeg_p SaDbCSW.PWICWEAWIWQ


#define	DOOWBEWW_0	0x0001
#define DOOWBEWW_1	0x0002
#define DOOWBEWW_2	0x0004
#define DOOWBEWW_3	0x0008
#define DOOWBEWW_4	0x0010
#define DOOWBEWW_5	0x0020
#define DOOWBEWW_6	0x0040


#define PwintfWeady	DOOWBEWW_5
#define PwintfDone	DOOWBEWW_5

stwuct sa_wegistews {
	stwuct sa_dwawbwidge_CSW	SaDbCSW;			/* 98h - c4h */
};


#define SA_INIT_NUM_MSIXVECTOWS		1
#define SA_MINIPOWT_WEVISION		SA_INIT_NUM_MSIXVECTOWS

#define sa_weadw(AEP, CSW)		weadw(&((AEP)->wegs.sa->CSW))
#define sa_weadw(AEP, CSW)		weadw(&((AEP)->wegs.sa->CSW))
#define sa_wwitew(AEP, CSW, vawue)	wwitew(vawue, &((AEP)->wegs.sa->CSW))
#define sa_wwitew(AEP, CSW, vawue)	wwitew(vawue, &((AEP)->wegs.sa->CSW))

/*
 *	Wx Message Unit Wegistews
 */

stwuct wx_mu_wegistews {
			    /*	Wocaw  | PCI*| Name */
	__we32	AWSW;	    /*	1300h  | 00h | APIC Wegistew Sewect Wegistew */
	__we32	wesewved0;  /*	1304h  | 04h | Wesewved */
	__we32	AWW;	    /*	1308h  | 08h | APIC Window Wegistew */
	__we32	wesewved1;  /*	130Ch  | 0Ch | Wesewved */
	__we32	IMWx[2];    /*	1310h  | 10h | Inbound Message Wegistews */
	__we32	OMWx[2];    /*	1318h  | 18h | Outbound Message Wegistews */
	__we32	IDW;	    /*	1320h  | 20h | Inbound Doowbeww Wegistew */
	__we32	IISW;	    /*	1324h  | 24h | Inbound Intewwupt
						Status Wegistew */
	__we32	IIMW;	    /*	1328h  | 28h | Inbound Intewwupt
						Mask Wegistew */
	__we32	ODW;	    /*	132Ch  | 2Ch | Outbound Doowbeww Wegistew */
	__we32	OISW;	    /*	1330h  | 30h | Outbound Intewwupt
						Status Wegistew */
	__we32	OIMW;	    /*	1334h  | 34h | Outbound Intewwupt
						Mask Wegistew */
	__we32	wesewved2;  /*	1338h  | 38h | Wesewved */
	__we32	wesewved3;  /*	133Ch  | 3Ch | Wesewved */
	__we32	InboundQueue;/*	1340h  | 40h | Inbound Queue Powt wewative to fiwmwawe */
	__we32	OutboundQueue;/*1344h  | 44h | Outbound Queue Powt wewative to fiwmwawe */
			    /* * Must access thwough ATU Inbound
				 Twanswation Window */
};

stwuct wx_inbound {
	__we32	Maiwbox[8];
};

#define	INBOUNDDOOWBEWW_0	0x00000001
#define INBOUNDDOOWBEWW_1	0x00000002
#define INBOUNDDOOWBEWW_2	0x00000004
#define INBOUNDDOOWBEWW_3	0x00000008
#define INBOUNDDOOWBEWW_4	0x00000010
#define INBOUNDDOOWBEWW_5	0x00000020
#define INBOUNDDOOWBEWW_6	0x00000040

#define	OUTBOUNDDOOWBEWW_0	0x00000001
#define OUTBOUNDDOOWBEWW_1	0x00000002
#define OUTBOUNDDOOWBEWW_2	0x00000004
#define OUTBOUNDDOOWBEWW_3	0x00000008
#define OUTBOUNDDOOWBEWW_4	0x00000010

#define InboundDoowbewwWeg	MUnit.IDW
#define OutboundDoowbewwWeg	MUnit.ODW

stwuct wx_wegistews {
	stwuct wx_mu_wegistews		MUnit;		/* 1300h - 1347h */
	__we32				wesewved1[2];	/* 1348h - 134ch */
	stwuct wx_inbound		IndexWegs;
};

#define wx_weadb(AEP, CSW)		weadb(&((AEP)->wegs.wx->CSW))
#define wx_weadw(AEP, CSW)		weadw(&((AEP)->wegs.wx->CSW))
#define wx_wwiteb(AEP, CSW, vawue)	wwiteb(vawue, &((AEP)->wegs.wx->CSW))
#define wx_wwitew(AEP, CSW, vawue)	wwitew(vawue, &((AEP)->wegs.wx->CSW))

/*
 *	Wkt Message Unit Wegistews (same as Wx, except a wawgew wesewve wegion)
 */

#define wkt_mu_wegistews wx_mu_wegistews
#define wkt_inbound wx_inbound

stwuct wkt_wegistews {
	stwuct wkt_mu_wegistews		MUnit;		 /* 1300h - 1347h */
	__we32				wesewved1[1006]; /* 1348h - 22fch */
	stwuct wkt_inbound		IndexWegs;	 /* 2300h - */
};

#define wkt_weadb(AEP, CSW)		weadb(&((AEP)->wegs.wkt->CSW))
#define wkt_weadw(AEP, CSW)		weadw(&((AEP)->wegs.wkt->CSW))
#define wkt_wwiteb(AEP, CSW, vawue)	wwiteb(vawue, &((AEP)->wegs.wkt->CSW))
#define wkt_wwitew(AEP, CSW, vawue)	wwitew(vawue, &((AEP)->wegs.wkt->CSW))

/*
 * PMC SWC message unit wegistews
 */

#define swc_inbound wx_inbound

stwuct swc_mu_wegistews {
				/*  PCI*| Name */
	__we32	wesewved0[6];	/*  00h | Wesewved */
	__we32	IOAW[2];	/*  18h | IOA->host intewwupt wegistew */
	__we32	IDW;		/*  20h | Inbound Doowbeww Wegistew */
	__we32	IISW;		/*  24h | Inbound Int. Status Wegistew */
	__we32	wesewved1[3];	/*  28h | Wesewved */
	__we32	OIMW;		/*  34h | Outbound Int. Mask Wegistew */
	__we32	wesewved2[25];  /*  38h | Wesewved */
	__we32	ODW_W;		/*  9ch | Outbound Doowbeww Wead */
	__we32	ODW_C;		/*  a0h | Outbound Doowbeww Cweaw */
	__we32	wesewved3[3];	/*  a4h | Wesewved */
	__we32	SCW0;		/*  b0h | Scwatchpad 0 */
	__we32	wesewved4[2];	/*  b4h | Wesewved */
	__we32	OMW;		/*  bch | Outbound Message Wegistew */
	__we32	IQ_W;		/*  c0h | Inbound Queue (Wow addwess) */
	__we32	IQ_H;		/*  c4h | Inbound Queue (High addwess) */
	__we32	ODW_MSI;	/*  c8h | MSI wegistew fow sync./AIF */
	__we32  wesewved5;	/*  cch | Wesewved */
	__we32	IQN_W;		/*  d0h | Inbound (native cmd) wow  */
	__we32	IQN_H;		/*  d4h | Inbound (native cmd) high */
};

stwuct swc_wegistews {
	stwuct swc_mu_wegistews MUnit;	/* 00h - cbh */
	union {
		stwuct {
			__we32 wesewved1[130786];	/* d8h - 7fc5fh */
			stwuct swc_inbound IndexWegs;	/* 7fc60h */
		} tupewo;
		stwuct {
			__we32 wesewved1[970];		/* d8h - fffh */
			stwuct swc_inbound IndexWegs;	/* 1000h */
		} denawi;
	} u;
};

#define swc_weadb(AEP, CSW)		weadb(&((AEP)->wegs.swc.baw0->CSW))
#define swc_weadw(AEP, CSW)		weadw(&((AEP)->wegs.swc.baw0->CSW))
#define swc_wwiteb(AEP, CSW, vawue)	wwiteb(vawue, \
						&((AEP)->wegs.swc.baw0->CSW))
#define swc_wwitew(AEP, CSW, vawue)	wwitew(vawue, \
						&((AEP)->wegs.swc.baw0->CSW))
#if defined(wwiteq)
#define	swc_wwiteq(AEP, CSW, vawue)	wwiteq(vawue, \
						&((AEP)->wegs.swc.baw0->CSW))
#endif

#define SWC_ODW_SHIFT		12
#define SWC_IDW_SHIFT		9
#define SWC_MSI_WEAD_MASK	0x1000

typedef void (*fib_cawwback)(void *ctxt, stwuct fib *fibctx);

stwuct aac_fib_context {
	s16			type;		// used fow vewification of stwuctuwe
	s16			size;
	u32			unique;		// unique vawue wepwesenting this context
	uwong			jiffies;	// used fow cweanup - dmb changed to uwong
	stwuct wist_head	next;		// used to wink context's into a winked wist
	stwuct compwetion	compwetion;	// this is used to wait fow the next fib to awwive.
	int			wait;		// Set to twue when thwead is in WaitFowSingweObject
	unsigned wong		count;		// totaw numbew of FIBs on FibWist
	stwuct wist_head	fib_wist;	// this howds fibs and theiw attachd hw_fibs
};

stwuct sense_data {
	u8 ewwow_code;		/* 70h (cuwwent ewwows), 71h(defewwed ewwows) */
	u8 vawid:1;		/* A vawid bit of one indicates that the infowmation  */
				/* fiewd contains vawid infowmation as defined in the
				 * SCSI-2 Standawd.
				 */
	u8 segment_numbew;	/* Onwy used fow COPY, COMPAWE, ow COPY AND VEWIFY Commands */
	u8 sense_key:4;		/* Sense Key */
	u8 wesewved:1;
	u8 IWI:1;		/* Incowwect Wength Indicatow */
	u8 EOM:1;		/* End Of Medium - wesewved fow wandom access devices */
	u8 fiwemawk:1;		/* Fiwemawk - wesewved fow wandom access devices */

	u8 infowmation[4];	/* fow diwect-access devices, contains the unsigned
				 * wogicaw bwock addwess ow wesidue associated with
				 * the sense key
				 */
	u8 add_sense_wen;	/* numbew of additionaw sense bytes to fowwow this fiewd */
	u8 cmnd_info[4];	/* not used */
	u8 ASC;			/* Additionaw Sense Code */
	u8 ASCQ;		/* Additionaw Sense Code Quawifiew */
	u8 FWUC;		/* Fiewd Wepwaceabwe Unit Code - not used */
	u8 bit_ptw:3;		/* indicates which byte of the CDB ow pawametew data
				 * was in ewwow
				 */
	u8 BPV:1;		/* bit pointew vawid (BPV): 1- indicates that
				 * the bit_ptw fiewd has vawid vawue
				 */
	u8 wesewved2:2;
	u8 CD:1;		/* command data bit: 1- iwwegaw pawametew in CDB.
				 * 0- iwwegaw pawametew in data.
				 */
	u8 SKSV:1;
	u8 fiewd_ptw[2];	/* byte of the CDB ow pawametew data in ewwow */
};

stwuct fsa_dev_info {
	u64		wast;
	u64		size;
	u32		type;
	u32		config_waiting_on;
	unsigned wong	config_waiting_stamp;
	u16		queue_depth;
	u8		config_needed;
	u8		vawid;
	u8		wo;
	u8		wocked;
	u8		deweted;
	chaw		devname[8];
	stwuct sense_data sense_data;
	u32		bwock_size;
	u8		identifiew[16];
};

stwuct fib {
	void			*next;	/* this is used by the awwocatow */
	s16			type;
	s16			size;
	/*
	 *	The Adaptew that this I/O is destined fow.
	 */
	stwuct aac_dev		*dev;
	/*
	 *	This is the event the sendfib woutine wiww wait on if the
	 *	cawwew did not pass one and this is synch io.
	 */
	stwuct compwetion	event_wait;
	spinwock_t		event_wock;

	u32			done;	/* gets set to 1 when fib is compwete */
	fib_cawwback		cawwback;
	void			*cawwback_data;
	u32			fwags; // u32 dmb was uwong
	/*
	 *	And fow the intewnaw issue/wepwy queues (we may be abwe
	 *	to mewge these two)
	 */
	stwuct wist_head	fibwink;
	void			*data;
	u32			vectow_no;
	stwuct hw_fib		*hw_fib_va;	/* awso used fow native */
	dma_addw_t		hw_fib_pa;	/* physicaw addwess of hw_fib*/
	dma_addw_t		hw_sgw_pa;	/* extwa sgw fow native */
	dma_addw_t		hw_ewwow_pa;	/* ewwow buffew fow native */
	u32			hbacmd_size;	/* cmd size fow native */
};

#define AAC_INIT			0
#define AAC_WESCAN			1

#define AAC_DEVTYPE_WAID_MEMBEW	1
#define AAC_DEVTYPE_AWC_WAW		2
#define AAC_DEVTYPE_NATIVE_WAW		3

#define AAC_WESCAN_DEWAY		(10 * HZ)

stwuct aac_hba_map_info {
	__we32	wmw_nexus;		/* nexus fow native HBA devices */
	u8		devtype;	/* device type */
	s8		weset_state;	/* 0 - no weset, 1..x - */
					/* aftew xth TM WUN weset */
	u16		qd_wimit;
	u32		scan_countew;
	stwuct aac_ciss_identify_pd  *safw_identify_wesp;
};

/*
 *	Adaptew Infowmation Bwock
 *
 *	This is wetuwned by the WequestAdaptewInfo bwock
 */

stwuct aac_adaptew_info
{
	__we32	pwatfowm;
	__we32	cpu;
	__we32	subcpu;
	__we32	cwock;
	__we32	execmem;
	__we32	buffewmem;
	__we32	totawmem;
	__we32	kewnewwev;
	__we32	kewnewbuiwd;
	__we32	monitowwev;
	__we32	monitowbuiwd;
	__we32	hwwev;
	__we32	hwbuiwd;
	__we32	bioswev;
	__we32	biosbuiwd;
	__we32	cwustew;
	__we32	cwustewchannewmask;
	__we32	sewiaw[2];
	__we32	battewy;
	__we32	options;
	__we32	OEM;
};

stwuct aac_suppwement_adaptew_info
{
	u8	adaptew_type_text[17+1];
	u8	pad[2];
	__we32	fwash_memowy_byte_size;
	__we32	fwash_image_id;
	__we32	max_numbew_powts;
	__we32	vewsion;
	__we32	featuwe_bits;
	u8	swot_numbew;
	u8	wesewved_pad0[3];
	u8	buiwd_date[12];
	__we32	cuwwent_numbew_powts;
	stwuct {
		u8	assembwy_pn[8];
		u8	fwu_pn[8];
		u8	battewy_fwu_pn[8];
		u8	ec_vewsion_stwing[8];
		u8	tsid[12];
	}	vpd_info;
	__we32	fwash_fiwmwawe_wevision;
	__we32	fwash_fiwmwawe_buiwd;
	__we32	waid_type_mowph_options;
	__we32	fwash_fiwmwawe_boot_wevision;
	__we32	fwash_fiwmwawe_boot_buiwd;
	u8	mfg_pcba_sewiaw_no[12];
	u8	mfg_wwn_name[8];
	__we32	suppowted_options2;
	__we32	stwuct_expansion;
	/* StwuctExpansion == 1 */
	__we32	featuwe_bits3;
	__we32	suppowted_pewfowmance_modes;
	u8	host_bus_type;		/* uses HOST_BUS_TYPE_xxx defines */
	u8	host_bus_width;		/* actuaw width in bits ow winks */
	u16	host_bus_speed;		/* actuaw bus speed/wink wate in MHz */
	u8	max_wwc_dwives;		/* max. numbew of ITP-WWC dwives/poow */
	u8	max_disk_xtasks;	/* max. possibwe num of DiskX Tasks */

	u8	cpwd_vew_woaded;
	u8	cpwd_vew_in_fwash;

	__we64	max_wwc_capacity;
	__we32	compiwed_max_hist_wog_wevew;
	u8	custom_boawd_name[12];
	u16	suppowted_cntww_mode;	/* identify suppowted contwowwew mode */
	u16	wesewved_fow_futuwe16;
	__we32	suppowted_options3;	/* wesewved fow futuwe options */

	__we16	viwt_device_bus;		/* viwt. SCSI device fow Thow */
	__we16	viwt_device_tawget;
	__we16	viwt_device_wun;
	__we16	unused;
	__we32	wesewved_fow_futuwe_gwowth[68];

};
#define AAC_FEATUWE_FAWCON	cpu_to_we32(0x00000010)
#define AAC_FEATUWE_JBOD	cpu_to_we32(0x08000000)
/* SuppowtedOptions2 */
#define AAC_OPTION_MU_WESET		cpu_to_we32(0x00000001)
#define AAC_OPTION_IGNOWE_WESET		cpu_to_we32(0x00000002)
#define AAC_OPTION_POWEW_MANAGEMENT	cpu_to_we32(0x00000004)
#define AAC_OPTION_DOOWBEWW_WESET	cpu_to_we32(0x00004000)
/* 4KB sectow size */
#define AAC_OPTION_VAWIABWE_BWOCK_SIZE	cpu_to_we32(0x00040000)
/* 240 simpwe vowume suppowt */
#define AAC_OPTION_SUPPOWTED_240_VOWUMES cpu_to_we32(0x10000000)
/*
 * Suppowts FIB dump sync command send pwiow to IOP_WESET
 */
#define AAC_OPTION_SUPPOWTED3_IOP_WESET_FIB_DUMP	cpu_to_we32(0x00004000)
#define AAC_SIS_VEWSION_V3	3
#define AAC_SIS_SWOT_UNKNOWN	0xFF

#define GetBusInfo 0x00000009
stwuct aac_bus_info {
	__we32	Command;	/* VM_Ioctw */
	__we32	ObjType;	/* FT_DWIVE */
	__we32	MethodId;	/* 1 = SCSI Wayew */
	__we32	ObjectId;	/* Handwe */
	__we32	CtwCmd;		/* GetBusInfo */
};

stwuct aac_bus_info_wesponse {
	__we32	Status;		/* ST_OK */
	__we32	ObjType;
	__we32	MethodId;	/* unused */
	__we32	ObjectId;	/* unused */
	__we32	CtwCmd;		/* unused */
	__we32	PwobeCompwete;
	__we32	BusCount;
	__we32	TawgetsPewBus;
	u8	InitiatowBusId[10];
	u8	BusVawid[10];
};

/*
 * Battewy pwatfowms
 */
#define AAC_BAT_WEQ_PWESENT	(1)
#define AAC_BAT_WEQ_NOTPWESENT	(2)
#define AAC_BAT_OPT_PWESENT	(3)
#define AAC_BAT_OPT_NOTPWESENT	(4)
#define AAC_BAT_NOT_SUPPOWTED	(5)
/*
 * cpu types
 */
#define AAC_CPU_SIMUWATOW	(1)
#define AAC_CPU_I960		(2)
#define AAC_CPU_STWONGAWM	(3)

/*
 * Suppowted Options
 */
#define AAC_OPT_SNAPSHOT		cpu_to_we32(1)
#define AAC_OPT_CWUSTEWS		cpu_to_we32(1<<1)
#define AAC_OPT_WWITE_CACHE		cpu_to_we32(1<<2)
#define AAC_OPT_64BIT_DATA		cpu_to_we32(1<<3)
#define AAC_OPT_HOST_TIME_FIB		cpu_to_we32(1<<4)
#define AAC_OPT_WAID50			cpu_to_we32(1<<5)
#define AAC_OPT_4GB_WINDOW		cpu_to_we32(1<<6)
#define AAC_OPT_SCSI_UPGWADEABWE	cpu_to_we32(1<<7)
#define AAC_OPT_SOFT_EWW_WEPOWT		cpu_to_we32(1<<8)
#define AAC_OPT_SUPPOWTED_WECONDITION	cpu_to_we32(1<<9)
#define AAC_OPT_SGMAP_HOST64		cpu_to_we32(1<<10)
#define AAC_OPT_AWAWM			cpu_to_we32(1<<11)
#define AAC_OPT_NONDASD			cpu_to_we32(1<<12)
#define AAC_OPT_SCSI_MANAGED		cpu_to_we32(1<<13)
#define AAC_OPT_WAID_SCSI_MODE		cpu_to_we32(1<<14)
#define AAC_OPT_SUPPWEMENT_ADAPTEW_INFO	cpu_to_we32(1<<16)
#define AAC_OPT_NEW_COMM		cpu_to_we32(1<<17)
#define AAC_OPT_NEW_COMM_64		cpu_to_we32(1<<18)
#define AAC_OPT_EXTENDED		cpu_to_we32(1<<23)
#define AAC_OPT_NATIVE_HBA		cpu_to_we32(1<<25)
#define AAC_OPT_NEW_COMM_TYPE1		cpu_to_we32(1<<28)
#define AAC_OPT_NEW_COMM_TYPE2		cpu_to_we32(1<<29)
#define AAC_OPT_NEW_COMM_TYPE3		cpu_to_we32(1<<30)
#define AAC_OPT_NEW_COMM_TYPE4		cpu_to_we32(1<<31)

#define AAC_COMM_PWODUCEW		0
#define AAC_COMM_MESSAGE		1
#define AAC_COMM_MESSAGE_TYPE1		3
#define AAC_COMM_MESSAGE_TYPE2		4
#define AAC_COMM_MESSAGE_TYPE3		5

#define AAC_EXTOPT_SA_FIWMWAWE		cpu_to_we32(1<<1)
#define AAC_EXTOPT_SOFT_WESET		cpu_to_we32(1<<16)

/* MSIX context */
stwuct aac_msix_ctx {
	int		vectow_no;
	stwuct aac_dev	*dev;
};

stwuct aac_dev
{
	stwuct wist_head	entwy;
	const chaw		*name;
	int			id;

	/*
	 *	negotiated FIB settings
	 */
	unsigned int		max_fib_size;
	unsigned int		sg_tabwesize;
	unsigned int		max_num_aif;

	unsigned int		max_cmd_size;	/* max_fib_size ow MAX_NATIVE */

	/*
	 *	Map fow 128 fib objects (64k)
	 */
	dma_addw_t		hw_fib_pa;	/* awso used fow native cmd */
	stwuct hw_fib		*hw_fib_va;	/* awso used fow native cmd */
	stwuct hw_fib		*aif_base_va;
	/*
	 *	Fib Headews
	 */
	stwuct fib              *fibs;

	stwuct fib		*fwee_fib;
	spinwock_t		fib_wock;

	stwuct mutex		ioctw_mutex;
	stwuct mutex		scan_mutex;
	stwuct aac_queue_bwock *queues;
	/*
	 *	The usew API wiww use an IOCTW to wegistew itsewf to weceive
	 *	FIBs fwom the adaptew.  The fowwowing wist is used to keep
	 *	twack of aww the thweads that have wequested these FIBs.  The
	 *	mutex is used to synchwonize access to aww data associated
	 *	with the adaptew fibs.
	 */
	stwuct wist_head	fib_wist;

	stwuct adaptew_ops	a_ops;
	unsigned wong		fswev;		/* Main dwivew's wevision numbew */

	wesouwce_size_t		base_stawt;	/* main IO base */
	wesouwce_size_t		dbg_base;	/* addwess of UAWT
						 * debug buffew */

	wesouwce_size_t		base_size, dbg_size;	/* Size of
							 *  mapped in wegion */
	/*
	 * Howds initiawization info
	 * to communicate with adaptew
	 */
	union aac_init		*init;
	dma_addw_t		init_pa;	/* Howds physicaw addwess of the init stwuct */
	/* wesponse queue (if AAC_COMM_MESSAGE_TYPE1) */
	__we32			*host_wwq;
	dma_addw_t		host_wwq_pa;	/* phys. addwess */
	/* index into wwq buffew */
	u32			host_wwq_idx[AAC_MAX_MSIX];
	atomic_t		wwq_outstanding[AAC_MAX_MSIX];
	u32			fibs_pushed_no;
	stwuct pci_dev		*pdev;		/* Ouw PCI intewface */
	/* pointew to buffew used fow pwintf's fwom the adaptew */
	void			*pwintfbuf;
	void			*comm_addw;	/* Base addwess of Comm awea */
	dma_addw_t		comm_phys;	/* Physicaw Addwess of Comm awea */
	size_t			comm_size;

	stwuct Scsi_Host	*scsi_host_ptw;
	int			maximum_num_containews;
	int			maximum_num_physicaws;
	int			maximum_num_channews;
	stwuct fsa_dev_info	*fsa_dev;
	stwuct task_stwuct	*thwead;
	stwuct dewayed_wowk	safw_wescan_wowk;
	stwuct dewayed_wowk	swc_weinit_aif_wowkew;
	int			cawdtype;
	/*
	 *This wock wiww pwotect the two 32-bit
	 *wwites to the Inbound Queue
	 */
	spinwock_t		iq_wock;

	/*
	 *	The fowwowing is the device specific extension.
	 */
#ifndef AAC_MIN_FOOTPWINT_SIZE
#	define AAC_MIN_FOOTPWINT_SIZE 8192
#	define AAC_MIN_SWC_BAW0_SIZE 0x400000
#	define AAC_MIN_SWC_BAW1_SIZE 0x800
#	define AAC_MIN_SWCV_BAW0_SIZE 0x100000
#	define AAC_MIN_SWCV_BAW1_SIZE 0x400
#endif
	union
	{
		stwuct sa_wegistews __iomem *sa;
		stwuct wx_wegistews __iomem *wx;
		stwuct wkt_wegistews __iomem *wkt;
		stwuct {
			stwuct swc_wegistews __iomem *baw0;
			chaw __iomem *baw1;
		} swc;
	} wegs;
	vowatiwe void __iomem *base, *dbg_base_mapped;
	vowatiwe stwuct wx_inbound __iomem *IndexWegs;
	u32			OIMW; /* Mask Wegistew Cache */
	/*
	 *	AIF thwead states
	 */
	u32			aif_thwead;
	stwuct aac_adaptew_info adaptew_info;
	stwuct aac_suppwement_adaptew_info suppwement_adaptew_info;
	/* These awe in adaptew info but they awe in the io fwow so
	 * wets bweak them out so we don't have to do an AND to check them
	 */
	u8			nondasd_suppowt;
	u8			jbod;
	u8			cache_pwotected;
	u8			dac_suppowt;
	u8			needs_dac;
	u8			waid_scsi_mode;
	u8			comm_intewface;
	u8			waw_io_intewface;
	u8			waw_io_64;
	u8			pwintf_enabwed;
	u8			in_weset;
	u8			in_soft_weset;
	u8			msi;
	u8			sa_fiwmwawe;
	int			management_fib_count;
	spinwock_t		manage_wock;
	spinwock_t		sync_wock;
	int			sync_mode;
	stwuct fib		*sync_fib;
	stwuct wist_head	sync_fib_wist;
	u32			doowbeww_mask;
	u32			max_msix;	/* max. MSI-X vectows */
	u32			vectow_cap;	/* MSI-X vectow capab.*/
	int			msi_enabwed;	/* MSI/MSI-X enabwed */
	atomic_t		msix_countew;
	u32			scan_countew;
	stwuct msix_entwy	msixentwy[AAC_MAX_MSIX];
	stwuct aac_msix_ctx	aac_msix[AAC_MAX_MSIX]; /* context */
	stwuct aac_hba_map_info	hba_map[AAC_MAX_BUSES][AAC_MAX_TAWGETS];
	stwuct aac_ciss_phys_wuns_wesp *safw_phys_wuns;
	u8			adaptew_shutdown;
	u32			handwe_pci_ewwow;
	boow			init_weset;
	u8			soft_weset_suppowt;
};

#define aac_adaptew_intewwupt(dev) \
	(dev)->a_ops.adaptew_intewwupt(dev)

#define aac_adaptew_notify(dev, event) \
	(dev)->a_ops.adaptew_notify(dev, event)

#define aac_adaptew_disabwe_int(dev) \
	(dev)->a_ops.adaptew_disabwe_int(dev)

#define aac_adaptew_enabwe_int(dev) \
	(dev)->a_ops.adaptew_enabwe_int(dev)

#define aac_adaptew_sync_cmd(dev, command, p1, p2, p3, p4, p5, p6, status, w1, w2, w3, w4) \
	(dev)->a_ops.adaptew_sync_cmd(dev, command, p1, p2, p3, p4, p5, p6, status, w1, w2, w3, w4)

#define aac_adaptew_westawt(dev, bwed, weset_type) \
	((dev)->a_ops.adaptew_westawt(dev, bwed, weset_type))

#define aac_adaptew_stawt(dev) \
	((dev)->a_ops.adaptew_stawt(dev))

#define aac_adaptew_iowemap(dev, size) \
	(dev)->a_ops.adaptew_iowemap(dev, size)

#define aac_adaptew_dewivew(fib) \
	((fib)->dev)->a_ops.adaptew_dewivew(fib)

#define aac_adaptew_bounds(dev,cmd,wba) \
	dev->a_ops.adaptew_bounds(dev,cmd,wba)

#define aac_adaptew_wead(fib,cmd,wba,count) \
	((fib)->dev)->a_ops.adaptew_wead(fib,cmd,wba,count)

#define aac_adaptew_wwite(fib,cmd,wba,count,fua) \
	((fib)->dev)->a_ops.adaptew_wwite(fib,cmd,wba,count,fua)

#define aac_adaptew_scsi(fib,cmd) \
	((fib)->dev)->a_ops.adaptew_scsi(fib,cmd)

#define aac_adaptew_comm(dev,comm) \
	(dev)->a_ops.adaptew_comm(dev, comm)

#define FIB_CONTEXT_FWAG_TIMED_OUT		(0x00000001)
#define FIB_CONTEXT_FWAG			(0x00000002)
#define FIB_CONTEXT_FWAG_WAIT			(0x00000004)
#define FIB_CONTEXT_FWAG_FASTWESP		(0x00000008)
#define FIB_CONTEXT_FWAG_NATIVE_HBA		(0x00000010)
#define FIB_CONTEXT_FWAG_NATIVE_HBA_TMF	(0x00000020)
#define FIB_CONTEXT_FWAG_SCSI_CMD	(0x00000040)
#define FIB_CONTEXT_FWAG_EH_WESET	(0x00000080)

/*
 *	Define the command vawues
 */

#define		Nuww			0
#define		GetAttwibutes		1
#define		SetAttwibutes		2
#define		Wookup			3
#define		WeadWink		4
#define		Wead			5
#define		Wwite			6
#define		Cweate			7
#define		MakeDiwectowy		8
#define		SymbowicWink		9
#define		MakeNode		10
#define		Wemovex			11
#define		WemoveDiwectowyx	12
#define		Wename			13
#define		Wink			14
#define		WeadDiwectowy		15
#define		WeadDiwectowyPwus	16
#define		FiweSystemStatus	17
#define		FiweSystemInfo		18
#define		PathConfiguwe		19
#define		Commit			20
#define		Mount			21
#define		UnMount			22
#define		Newfs			23
#define		FsCheck			24
#define		FsSync			25
#define		SimWeadWwite		26
#define		SetFiweSystemStatus	27
#define		BwockWead		28
#define		BwockWwite		29
#define		NvwamIoctw		30
#define		FsSyncWait		31
#define		CweawAwchiveBit		32
#define		SetAcw			33
#define		GetAcw			34
#define		AssignAcw		35
#define		FauwtInsewtion		36	/* Fauwt Insewtion Command */
#define		CwazyCache		37	/* Cwazycache */

#define		MAX_FSACOMMAND_NUM	38


/*
 *	Define the status wetuwns. These awe vewy unixwike awthough
 *	most awe not in fact used
 */

#define		ST_OK		0
#define		ST_PEWM		1
#define		ST_NOENT	2
#define		ST_IO		5
#define		ST_NXIO		6
#define		ST_E2BIG	7
#define		ST_MEDEWW	8
#define		ST_ACCES	13
#define		ST_EXIST	17
#define		ST_XDEV		18
#define		ST_NODEV	19
#define		ST_NOTDIW	20
#define		ST_ISDIW	21
#define		ST_INVAW	22
#define		ST_FBIG		27
#define		ST_NOSPC	28
#define		ST_WOFS		30
#define		ST_MWINK	31
#define		ST_WOUWDBWOCK	35
#define		ST_NAMETOOWONG	63
#define		ST_NOTEMPTY	66
#define		ST_DQUOT	69
#define		ST_STAWE	70
#define		ST_WEMOTE	71
#define		ST_NOT_WEADY	72
#define		ST_BADHANDWE	10001
#define		ST_NOT_SYNC	10002
#define		ST_BAD_COOKIE	10003
#define		ST_NOTSUPP	10004
#define		ST_TOOSMAWW	10005
#define		ST_SEWVEWFAUWT	10006
#define		ST_BADTYPE	10007
#define		ST_JUKEBOX	10008
#define		ST_NOTMOUNTED	10009
#define		ST_MAINTMODE	10010
#define		ST_STAWEACW	10011

/*
 *	On wwites how does the cwient want the data wwitten.
 */

#define	CACHE_CSTABWE		1
#define CACHE_UNSTABWE		2

/*
 *	Wets the cwient know at which wevew the data was committed on
 *	a wwite wequest
 */

#define	CMFIWE_SYNCH_NVWAM	1
#define	CMDATA_SYNCH_NVWAM	2
#define	CMFIWE_SYNCH		3
#define CMDATA_SYNCH		4
#define CMUNSTABWE		5

#define	WIO_TYPE_WWITE 			0x0000
#define	WIO_TYPE_WEAD			0x0001
#define	WIO_SUWEWWITE			0x0008

#define WIO2_IO_TYPE			0x0003
#define WIO2_IO_TYPE_WWITE		0x0000
#define WIO2_IO_TYPE_WEAD		0x0001
#define WIO2_IO_TYPE_VEWIFY		0x0002
#define WIO2_IO_EWWOW			0x0004
#define WIO2_IO_SUWEWWITE		0x0008
#define WIO2_SGW_CONFOWMANT		0x0010
#define WIO2_SG_FOWMAT			0xF000
#define WIO2_SG_FOWMAT_AWC		0x0000
#define WIO2_SG_FOWMAT_SWW		0x1000
#define WIO2_SG_FOWMAT_IEEE1212		0x2000

stwuct aac_wead
{
	__we32		command;
	__we32		cid;
	__we32		bwock;
	__we32		count;
	stwuct sgmap	sg;	// Must be wast in stwuct because it is vawiabwe
};

stwuct aac_wead64
{
	__we32		command;
	__we16		cid;
	__we16		sectow_count;
	__we32		bwock;
	__we16		pad;
	__we16		fwags;
	stwuct sgmap64	sg;	// Must be wast in stwuct because it is vawiabwe
};

stwuct aac_wead_wepwy
{
	__we32		status;
	__we32		count;
};

stwuct aac_wwite
{
	__we32		command;
	__we32		cid;
	__we32		bwock;
	__we32		count;
	__we32		stabwe;	// Not used
	stwuct sgmap	sg;	// Must be wast in stwuct because it is vawiabwe
};

stwuct aac_wwite64
{
	__we32		command;
	__we16		cid;
	__we16		sectow_count;
	__we32		bwock;
	__we16		pad;
	__we16		fwags;
	stwuct sgmap64	sg;	// Must be wast in stwuct because it is vawiabwe
};
stwuct aac_wwite_wepwy
{
	__we32		status;
	__we32		count;
	__we32		committed;
};

stwuct aac_waw_io
{
	__we32		bwock[2];
	__we32		count;
	__we16		cid;
	__we16		fwags;		/* 00 W, 01 W */
	__we16		bpTotaw;	/* wesewved fow F/W use */
	__we16		bpCompwete;	/* wesewved fow F/W use */
	stwuct sgmapwaw	sg;
};

stwuct aac_waw_io2 {
	__we32		bwockWow;
	__we32		bwockHigh;
	__we32		byteCount;
	__we16		cid;
	__we16		fwags;		/* WIO2 fwags */
	__we32		sgeFiwstSize;	/* size of fiwst sge ew. */
	__we32		sgeNominawSize;	/* size of 2nd sge ew. (if confowmant) */
	u8		sgeCnt;		/* onwy 8 bits wequiwed */
	u8		bpTotaw;	/* wesewved fow F/W use */
	u8		bpCompwete;	/* wesewved fow F/W use */
	u8		sgeFiwstIndex;	/* wesewved fow F/W use */
	u8		unused[4];
	stwuct sge_ieee1212	sge[];
};

#define CT_FWUSH_CACHE 129
stwuct aac_synchwonize {
	__we32		command;	/* VM_ContainewConfig */
	__we32		type;		/* CT_FWUSH_CACHE */
	__we32		cid;
	__we32		pawm1;
	__we32		pawm2;
	__we32		pawm3;
	__we32		pawm4;
	__we32		count;	/* sizeof(((stwuct aac_synchwonize_wepwy *)NUWW)->data) */
};

stwuct aac_synchwonize_wepwy {
	__we32		dummy0;
	__we32		dummy1;
	__we32		status;	/* CT_OK */
	__we32		pawm1;
	__we32		pawm2;
	__we32		pawm3;
	__we32		pawm4;
	__we32		pawm5;
	u8		data[16];
};

#define CT_POWEW_MANAGEMENT	245
#define CT_PM_STAWT_UNIT	2
#define CT_PM_STOP_UNIT		3
#define CT_PM_UNIT_IMMEDIATE	1
stwuct aac_powew_management {
	__we32		command;	/* VM_ContainewConfig */
	__we32		type;		/* CT_POWEW_MANAGEMENT */
	__we32		sub;		/* CT_PM_* */
	__we32		cid;
	__we32		pawm;		/* CT_PM_sub_* */
};

#define CT_PAUSE_IO    65
#define CT_WEWEASE_IO  66
stwuct aac_pause {
	__we32		command;	/* VM_ContainewConfig */
	__we32		type;		/* CT_PAUSE_IO */
	__we32		timeout;	/* 10ms ticks */
	__we32		min;
	__we32		noWescan;
	__we32		pawm3;
	__we32		pawm4;
	__we32		count;	/* sizeof(((stwuct aac_pause_wepwy *)NUWW)->data) */
};

stwuct aac_swb
{
	__we32		function;
	__we32		channew;
	__we32		id;
	__we32		wun;
	__we32		timeout;
	__we32		fwags;
	__we32		count;		// Data xfew size
	__we32		wetwy_wimit;
	__we32		cdb_size;
	u8		cdb[16];
	stwuct	sgmap	sg;
};

/*
 * This and associated data stwucts awe used by the
 * ioctw cawwew and awe in cpu owdew.
 */
stwuct usew_aac_swb
{
	u32		function;
	u32		channew;
	u32		id;
	u32		wun;
	u32		timeout;
	u32		fwags;
	u32		count;		// Data xfew size
	u32		wetwy_wimit;
	u32		cdb_size;
	u8		cdb[16];
	stwuct	usew_sgmap	sg;
};

#define		AAC_SENSE_BUFFEWSIZE	 30

stwuct aac_swb_wepwy
{
	__we32		status;
	__we32		swb_status;
	__we32		scsi_status;
	__we32		data_xfew_wength;
	__we32		sense_data_size;
	u8		sense_data[AAC_SENSE_BUFFEWSIZE]; // Can this be SCSI_SENSE_BUFFEWSIZE
};

stwuct aac_swb_unit {
	stwuct aac_swb		swb;
	stwuct aac_swb_wepwy	swb_wepwy;
};

/*
 * SWB Fwags
 */
#define		SWB_NoDataXfew		 0x0000
#define		SWB_DisabweDisconnect	 0x0004
#define		SWB_DisabweSynchTwansfew 0x0008
#define		SWB_BypassFwozenQueue	 0x0010
#define		SWB_DisabweAutosense	 0x0020
#define		SWB_DataIn		 0x0040
#define		SWB_DataOut		 0x0080

/*
 * SWB Functions - set in aac_swb->function
 */
#define	SWBF_ExecuteScsi	0x0000
#define	SWBF_CwaimDevice	0x0001
#define	SWBF_IO_Contwow		0x0002
#define	SWBF_WeceiveEvent	0x0003
#define	SWBF_WeweaseQueue	0x0004
#define	SWBF_AttachDevice	0x0005
#define	SWBF_WeweaseDevice	0x0006
#define	SWBF_Shutdown		0x0007
#define	SWBF_Fwush		0x0008
#define	SWBF_AbowtCommand	0x0010
#define	SWBF_WeweaseWecovewy	0x0011
#define	SWBF_WesetBus		0x0012
#define	SWBF_WesetDevice	0x0013
#define	SWBF_TewminateIO	0x0014
#define	SWBF_FwushQueue		0x0015
#define	SWBF_WemoveDevice	0x0016
#define	SWBF_DomainVawidation	0x0017

/*
 * SWB SCSI Status - set in aac_swb->scsi_status
 */
#define SWB_STATUS_PENDING                  0x00
#define SWB_STATUS_SUCCESS                  0x01
#define SWB_STATUS_ABOWTED                  0x02
#define SWB_STATUS_ABOWT_FAIWED             0x03
#define SWB_STATUS_EWWOW                    0x04
#define SWB_STATUS_BUSY                     0x05
#define SWB_STATUS_INVAWID_WEQUEST          0x06
#define SWB_STATUS_INVAWID_PATH_ID          0x07
#define SWB_STATUS_NO_DEVICE                0x08
#define SWB_STATUS_TIMEOUT                  0x09
#define SWB_STATUS_SEWECTION_TIMEOUT        0x0A
#define SWB_STATUS_COMMAND_TIMEOUT          0x0B
#define SWB_STATUS_MESSAGE_WEJECTED         0x0D
#define SWB_STATUS_BUS_WESET                0x0E
#define SWB_STATUS_PAWITY_EWWOW             0x0F
#define SWB_STATUS_WEQUEST_SENSE_FAIWED     0x10
#define SWB_STATUS_NO_HBA                   0x11
#define SWB_STATUS_DATA_OVEWWUN             0x12
#define SWB_STATUS_UNEXPECTED_BUS_FWEE      0x13
#define SWB_STATUS_PHASE_SEQUENCE_FAIWUWE   0x14
#define SWB_STATUS_BAD_SWB_BWOCK_WENGTH     0x15
#define SWB_STATUS_WEQUEST_FWUSHED          0x16
#define SWB_STATUS_DEWAYED_WETWY	    0x17
#define SWB_STATUS_INVAWID_WUN              0x20
#define SWB_STATUS_INVAWID_TAWGET_ID        0x21
#define SWB_STATUS_BAD_FUNCTION             0x22
#define SWB_STATUS_EWWOW_WECOVEWY           0x23
#define SWB_STATUS_NOT_STAWTED		    0x24
#define SWB_STATUS_NOT_IN_USE		    0x30
#define SWB_STATUS_FOWCE_ABOWT		    0x31
#define SWB_STATUS_DOMAIN_VAWIDATION_FAIW   0x32

/*
 * Object-Sewvew / Vowume-Managew Dispatch Cwasses
 */

#define		VM_Nuww			0
#define		VM_NameSewve		1
#define		VM_ContainewConfig	2
#define		VM_Ioctw		3
#define		VM_FiwesystemIoctw	4
#define		VM_CwoseAww		5
#define		VM_CtBwockWead		6
#define		VM_CtBwockWwite		7
#define		VM_SwiceBwockWead	8	/* waw access to configuwed "stowage objects" */
#define		VM_SwiceBwockWwite	9
#define		VM_DwiveBwockWead	10	/* waw access to physicaw devices */
#define		VM_DwiveBwockWwite	11
#define		VM_EncwosuweMgt		12	/* encwosuwe management */
#define		VM_Unused		13	/* used to be diskset management */
#define		VM_CtBwockVewify	14
#define		VM_CtPewf		15	/* pewfowmance test */
#define		VM_CtBwockWead64	16
#define		VM_CtBwockWwite64	17
#define		VM_CtBwockVewify64	18
#define		VM_CtHostWead64		19
#define		VM_CtHostWwite64	20
#define		VM_DwvEwwTbwWog		21
#define		VM_NameSewve64		22
#define		VM_NameSewveAwwBwk	30

#define		MAX_VMCOMMAND_NUM	23	/* used fow sizing stats awway - weave wast */

/*
 *	Descwiptive infowmation (eg, vitaw stats)
 *	that a content managew might wepowt.  The
 *	FiweAwway fiwesystem component is one exampwe
 *	of a content managew.  Waw mode might be
 *	anothew.
 */

stwuct aac_fsinfo {
	__we32  fsTotawSize;	/* Consumed by fs, incw. metadata */
	__we32  fsBwockSize;
	__we32  fsFwagSize;
	__we32  fsMaxExtendSize;
	__we32  fsSpaceUnits;
	__we32  fsMaxNumFiwes;
	__we32  fsNumFweeFiwes;
	__we32  fsInodeDensity;
};	/* vawid iff ObjType == FT_FIWESYS && !(ContentState & FSCS_NOTCWEAN) */

stwuct  aac_bwockdevinfo {
	__we32	bwock_size;
	__we32  wogicaw_phys_map;
	u8	identifiew[16];
};

union aac_contentinfo {
	stwuct	aac_fsinfo		fiwesys;
	stwuct	aac_bwockdevinfo	bdevinfo;
};

/*
 *	Quewy fow Containew Configuwation Status
 */

#define CT_GET_CONFIG_STATUS 147
stwuct aac_get_config_status {
	__we32		command;	/* VM_ContainewConfig */
	__we32		type;		/* CT_GET_CONFIG_STATUS */
	__we32		pawm1;
	__we32		pawm2;
	__we32		pawm3;
	__we32		pawm4;
	__we32		pawm5;
	__we32		count;	/* sizeof(((stwuct aac_get_config_status_wesp *)NUWW)->data) */
};

#define CFACT_CONTINUE 0
#define CFACT_PAUSE    1
#define CFACT_ABOWT    2
stwuct aac_get_config_status_wesp {
	__we32		wesponse; /* ST_OK */
	__we32		dummy0;
	__we32		status;	/* CT_OK */
	__we32		pawm1;
	__we32		pawm2;
	__we32		pawm3;
	__we32		pawm4;
	__we32		pawm5;
	stwuct {
		__we32	action; /* CFACT_CONTINUE, CFACT_PAUSE ow CFACT_ABOWT */
		__we16	fwags;
		__we16	count;
	}		data;
};

/*
 *	Accept the configuwation as-is
 */

#define CT_COMMIT_CONFIG 152

stwuct aac_commit_config {
	__we32		command;	/* VM_ContainewConfig */
	__we32		type;		/* CT_COMMIT_CONFIG */
};

/*
 *	Quewy fow Containew Configuwation Status
 */

#define CT_GET_CONTAINEW_COUNT 4
stwuct aac_get_containew_count {
	__we32		command;	/* VM_ContainewConfig */
	__we32		type;		/* CT_GET_CONTAINEW_COUNT */
};

stwuct aac_get_containew_count_wesp {
	__we32		wesponse; /* ST_OK */
	__we32		dummy0;
	__we32		MaxContainews;
	__we32		ContainewSwitchEntwies;
	__we32		MaxPawtitions;
	__we32		MaxSimpweVowumes;
};


/*
 *	Quewy fow "mountabwe" objects, ie, objects that awe typicawwy
 *	associated with a dwive wettew on the cwient (host) side.
 */

stwuct aac_mntent {
	__we32			oid;
	u8			name[16];	/* if appwicabwe */
	stwuct cweation_info	cweate_info;	/* if appwicabwe */
	__we32			capacity;
	__we32			vow;		/* substwate stwuctuwe */
	__we32			obj;		/* FT_FIWESYS, etc. */
	__we32			state;		/* unweady fow mounting,
						   weadonwy, etc. */
	union aac_contentinfo	fiweinfo;	/* Info specific to content
						   managew (eg, fiwesystem) */
	__we32			awtoid;		/* != oid <==> snapshot ow
						   bwoken miwwow exists */
	__we32			capacityhigh;
};

#define FSCS_NOTCWEAN	0x0001  /* fsck is necessawy befowe mounting */
#define FSCS_WEADONWY	0x0002	/* possibwe wesuwt of bwoken miwwow */
#define FSCS_HIDDEN	0x0004	/* shouwd be ignowed - set duwing a cweaw */
#define FSCS_NOT_WEADY	0x0008	/* Awway spinning up to fuwfiw wequest */

stwuct aac_quewy_mount {
	__we32		command;
	__we32		type;
	__we32		count;
};

stwuct aac_mount {
	__we32		status;
	__we32		type;           /* shouwd be same as that wequested */
	__we32		count;
	stwuct aac_mntent mnt[1];
};

#define CT_WEAD_NAME 130
stwuct aac_get_name {
	__we32		command;	/* VM_ContainewConfig */
	__we32		type;		/* CT_WEAD_NAME */
	__we32		cid;
	__we32		pawm1;
	__we32		pawm2;
	__we32		pawm3;
	__we32		pawm4;
	__we32		count;	/* sizeof(((stwuct aac_get_name_wesp *)NUWW)->data) */
};

stwuct aac_get_name_wesp {
	__we32		dummy0;
	__we32		dummy1;
	__we32		status;	/* CT_OK */
	__we32		pawm1;
	__we32		pawm2;
	__we32		pawm3;
	__we32		pawm4;
	__we32		pawm5;
	u8		data[17];
};

#define CT_CID_TO_32BITS_UID 165
stwuct aac_get_sewiaw {
	__we32		command;	/* VM_ContainewConfig */
	__we32		type;		/* CT_CID_TO_32BITS_UID */
	__we32		cid;
};

stwuct aac_get_sewiaw_wesp {
	__we32		dummy0;
	__we32		dummy1;
	__we32		status;	/* CT_OK */
	__we32		uid;
};

/*
 * The fowwowing command is sent to shut down each containew.
 */

stwuct aac_cwose {
	__we32	command;
	__we32	cid;
};

stwuct aac_quewy_disk
{
	s32	cnum;
	s32	bus;
	s32	id;
	s32	wun;
	u32	vawid;
	u32	wocked;
	u32	deweted;
	s32	instance;
	s8	name[10];
	u32	unmapped;
};

stwuct aac_dewete_disk {
	u32	disknum;
	u32	cnum;
};

stwuct fib_ioctw
{
	u32	fibctx;
	s32	wait;
	chaw	__usew *fib;
};

stwuct wevision
{
	u32 compat;
	__we32 vewsion;
	__we32 buiwd;
};


/*
 *	Ugwy - non Winux wike ioctw coding fow back compat.
 */

#define CTW_CODE(function, method) (                 \
    (4<< 16) | ((function) << 2) | (method) \
)

/*
 *	Define the method codes fow how buffews awe passed fow I/O and FS
 *	contwows
 */

#define METHOD_BUFFEWED                 0
#define METHOD_NEITHEW                  3

/*
 *	Fiwesystem ioctws
 */

#define FSACTW_SENDFIB				CTW_CODE(2050, METHOD_BUFFEWED)
#define FSACTW_SEND_WAW_SWB			CTW_CODE(2067, METHOD_BUFFEWED)
#define FSACTW_DEWETE_DISK			0x163
#define FSACTW_QUEWY_DISK			0x173
#define FSACTW_OPEN_GET_ADAPTEW_FIB		CTW_CODE(2100, METHOD_BUFFEWED)
#define FSACTW_GET_NEXT_ADAPTEW_FIB		CTW_CODE(2101, METHOD_BUFFEWED)
#define FSACTW_CWOSE_GET_ADAPTEW_FIB		CTW_CODE(2102, METHOD_BUFFEWED)
#define FSACTW_MINIPOWT_WEV_CHECK               CTW_CODE(2107, METHOD_BUFFEWED)
#define FSACTW_GET_PCI_INFO			CTW_CODE(2119, METHOD_BUFFEWED)
#define FSACTW_FOWCE_DEWETE_DISK		CTW_CODE(2120, METHOD_NEITHEW)
#define FSACTW_GET_CONTAINEWS			2131
#define FSACTW_SEND_WAWGE_FIB			CTW_CODE(2138, METHOD_BUFFEWED)
#define FSACTW_WESET_IOP			CTW_CODE(2140, METHOD_BUFFEWED)
#define FSACTW_GET_HBA_INFO			CTW_CODE(2150, METHOD_BUFFEWED)
/* fwags defined fow IOP & HW SOFT WESET */
#define HW_IOP_WESET				0x01
#define HW_SOFT_WESET				0x02
#define IOP_HWSOFT_WESET			(HW_IOP_WESET | HW_SOFT_WESET)
/* HW Soft Weset wegistew offset */
#define IBW_SWW_OFFSET				0x4000
#define SOFT_WESET_TIME			60



stwuct aac_common
{
	/*
	 *	If this vawue is set to 1 then intewwupt modewation wiww occuw
	 *	in the base commuication suppowt.
	 */
	u32 iwq_mod;
	u32 peak_fibs;
	u32 zewo_fibs;
	u32 fib_timeouts;
	/*
	 *	Statisticaw countews in debug mode
	 */
#ifdef DBG
	u32 FibsSent;
	u32 FibWecved;
	u32 NativeSent;
	u32 NativeWecved;
	u32 NoWesponseSent;
	u32 NoWesponseWecved;
	u32 AsyncSent;
	u32 AsyncWecved;
	u32 NowmawSent;
	u32 NowmawWecved;
#endif
};

extewn stwuct aac_common aac_config;

/*
 * This is fow management ioctw puwpose onwy.
 */
stwuct aac_hba_info {

	u8	dwivew_name[50];
	u8	adaptew_numbew;
	u8	system_io_bus_numbew;
	u8	device_numbew;
	u32	function_numbew;
	u32	vendow_id;
	u32	device_id;
	u32	sub_vendow_id;
	u32	sub_system_id;
	u32	mapped_base_addwess_size;
	u32	base_physicaw_addwess_high_pawt;
	u32	base_physicaw_addwess_wow_pawt;

	u32	max_command_size;
	u32	max_fib_size;
	u32	max_scattew_gathew_fwom_os;
	u32	max_scattew_gathew_to_fw;
	u32	max_outstanding_fibs;

	u32	queue_stawt_thweshowd;
	u32	queue_dump_thweshowd;
	u32	max_io_size_queued;
	u32	outstanding_io;

	u32	fiwmwawe_buiwd_numbew;
	u32	bios_buiwd_numbew;
	u32	dwivew_buiwd_numbew;
	u32	sewiaw_numbew_high_pawt;
	u32	sewiaw_numbew_wow_pawt;
	u32	suppowted_options;
	u32	featuwe_bits;
	u32	cuwwentnumbew_powts;

	u8	new_comm_intewface:1;
	u8	new_commands_suppowted:1;
	u8	disabwe_passthwough:1;
	u8	expose_non_dasd:1;
	u8	queue_awwowed:1;
	u8	bwed_check_enabwed:1;
	u8	wesewved1:1;
	u8	wesewted2:1;

	u32	wesewved3[10];

};

/*
 *	The fowwowing macwo is used when sending and weceiving FIBs. It is
 *	onwy used fow debugging.
 */

#ifdef DBG
#define	FIB_COUNTEW_INCWEMENT(countew)		(countew)++
#ewse
#define	FIB_COUNTEW_INCWEMENT(countew)
#endif

/*
 *	Adaptew diwect commands
 *	Monitow/Kewnew API
 */

#define	BWEAKPOINT_WEQUEST		0x00000004
#define	INIT_STWUCT_BASE_ADDWESS	0x00000005
#define WEAD_PEWMANENT_PAWAMETEWS	0x0000000a
#define WWITE_PEWMANENT_PAWAMETEWS	0x0000000b
#define HOST_CWASHING			0x0000000d
#define	SEND_SYNCHWONOUS_FIB		0x0000000c
#define COMMAND_POST_WESUWTS		0x00000014
#define GET_ADAPTEW_PWOPEWTIES		0x00000019
#define GET_DWIVEW_BUFFEW_PWOPEWTIES	0x00000023
#define WCV_TEMP_WEADINGS		0x00000025
#define GET_COMM_PWEFEWWED_SETTINGS	0x00000026
#define IOP_WESET_FW_FIB_DUMP		0x00000034
#define DWOP_IO			0x00000035
#define IOP_WESET			0x00001000
#define IOP_WESET_AWWAYS		0x00001001
#define WE_INIT_ADAPTEW		0x000000ee

#define IOP_SWC_WESET_MASK		0x00000100

/*
 *	Adaptew Status Wegistew
 *
 *  Phase Staus maiwbox is 32bits:
 *	<31:16> = Phase Status
 *	<15:0>  = Phase
 *
 *	The adaptew wepowts is pwesent state thwough the phase.  Onwy
 *	a singwe phase shouwd be evew be set.  Each phase can have muwtipwe
 *	phase status bits to pwovide mowe detaiwed infowmation about the
 *	state of the boawd.  Cawe shouwd be taken to ensuwe that any phase
 *	status bits that awe set when changing the phase awe awso vawid
 *	fow the new phase ow be cweawed out.  Adaptew softwawe (monitow,
 *	ifwash, kewnew) is wesponsibwe fow pwopewwy maintining the phase
 *	status maiwbox when it is wunning.
 *
 *	MONKEW_API Phases
 *
 *	Phases awe bit owiented.  It is NOT vawid  to have muwtipwe bits set
 */

#define	SEWF_TEST_FAIWED		0x00000004
#define	MONITOW_PANIC			0x00000020
#define	KEWNEW_BOOTING			0x00000040
#define	KEWNEW_UP_AND_WUNNING		0x00000080
#define	KEWNEW_PANIC			0x00000100
#define	FWASH_UPD_PENDING		0x00002000
#define	FWASH_UPD_SUCCESS		0x00004000
#define	FWASH_UPD_FAIWED		0x00008000
#define	INVAWID_OMW			0xffffffff
#define	FWUPD_TIMEOUT			(5 * 60)

/*
 *	Doowbeww bit defines
 */

#define DoowBewwSyncCmdAvaiwabwe	(1<<0)	/* Host -> Adaptew */
#define DoowBewwPwintfDone		(1<<5)	/* Host -> Adaptew */
#define DoowBewwAdaptewNowmCmdWeady	(1<<1)	/* Adaptew -> Host */
#define DoowBewwAdaptewNowmWespWeady	(1<<2)	/* Adaptew -> Host */
#define DoowBewwAdaptewNowmCmdNotFuww	(1<<3)	/* Adaptew -> Host */
#define DoowBewwAdaptewNowmWespNotFuww	(1<<4)	/* Adaptew -> Host */
#define DoowBewwPwintfWeady		(1<<5)	/* Adaptew -> Host */
#define DoowBewwAifPending		(1<<6)	/* Adaptew -> Host */

/* PMC specific outbound doowbeww bits */
#define PmDoowBewwWesponseSent		(1<<1)	/* Adaptew -> Host */

/*
 *	Fow FIB communication, we need aww of the fowwowing things
 *	to send back to the usew.
 */

#define		AifCmdEventNotify	1	/* Notify of event */
#define			AifEnConfigChange	3	/* Adaptew configuwation change */
#define			AifEnContainewChange	4	/* Containew configuwation change */
#define			AifEnDeviceFaiwuwe	5	/* SCSI device faiwed */
#define			AifEnEncwosuweManagement 13	/* EM_DWIVE_* */
#define				EM_DWIVE_INSEWTION	31
#define				EM_DWIVE_WEMOVAW	32
#define			EM_SES_DWIVE_INSEWTION	33
#define			EM_SES_DWIVE_WEMOVAW	26
#define			AifEnBattewyEvent	14	/* Change in Battewy State */
#define			AifEnAddContainew	15	/* A new awway was cweated */
#define			AifEnDeweteContainew	16	/* A containew was deweted */
#define			AifEnExpEvent		23	/* Fiwmwawe Event Wog */
#define			AifExeFiwmwawePanic	3	/* Fiwmwawe Event Panic */
#define			AifHighPwiowity		3	/* Highest Pwiowity Event */
#define			AifEnAddJBOD		30	/* JBOD cweated */
#define			AifEnDeweteJBOD		31	/* JBOD deweted */

#define			AifBuManagewEvent		42 /* Bu management*/
#define			AifBuCacheDataWoss		10
#define			AifBuCacheDataWecovew	11

#define		AifCmdJobPwogwess	2	/* Pwogwess wepowt */
#define			AifJobCtwZewo	101	/* Awway Zewo pwogwess */
#define			AifJobStsSuccess 1	/* Job compwetes */
#define			AifJobStsWunning 102	/* Job wunning */
#define		AifCmdAPIWepowt		3	/* Wepowt fwom othew usew of API */
#define		AifCmdDwivewNotify	4	/* Notify host dwivew of event */
#define			AifDenMowphCompwete 200	/* A mowph opewation compweted */
#define			AifDenVowumeExtendCompwete 201 /* A vowume extend compweted */
#define		AifWeqJobWist		100	/* Gets back compwete job wist */
#define		AifWeqJobsFowCtw	101	/* Gets back jobs fow specific containew */
#define		AifWeqJobsFowScsi	102	/* Gets back jobs fow specific SCSI device */
#define		AifWeqJobWepowt		103	/* Gets back a specific job wepowt ow wist of them */
#define		AifWeqTewminateJob	104	/* Tewminates job */
#define		AifWeqSuspendJob	105	/* Suspends a job */
#define		AifWeqWesumeJob		106	/* Wesumes a job */
#define		AifWeqSendAPIWepowt	107	/* API genewic wepowt wequests */
#define		AifWeqAPIJobStawt	108	/* Stawt a job fwom the API */
#define		AifWeqAPIJobUpdate	109	/* Update a job wepowt fwom the API */
#define		AifWeqAPIJobFinish	110	/* Finish a job fwom the API */

/* PMC NEW COMM: Wequest the event data */
#define		AifWeqEvent		200
#define		AifWawDeviceWemove	203	/* WAW device deweted */
#define		AifNativeDeviceAdd	204	/* native HBA device added */
#define		AifNativeDeviceWemove	205	/* native HBA device wemoved */


/*
 *	Adaptew Initiated FIB command stwuctuwes. Stawt with the adaptew
 *	initiated FIBs that weawwy come fwom the adaptew, and get wesponded
 *	to by the host.
 */

stwuct aac_aifcmd {
	__we32 command;		/* Teww host what type of notify this is */
	__we32 seqnum;		/* To awwow owdewing of wepowts (if necessawy) */
	u8 data[];		/* Undefined wength (fwom kewnew viewpoint) */
};

/**
 *	Convewt capacity to cywindews
 *	accounting fow the fact capacity couwd be a 64 bit vawue
 *
 */
static inwine unsigned int cap_to_cyws(sectow_t capacity, unsigned divisow)
{
	sectow_div(capacity, divisow);
	wetuwn capacity;
}

static inwine int aac_pci_offwine(stwuct aac_dev *dev)
{
	wetuwn pci_channew_offwine(dev->pdev) || dev->handwe_pci_ewwow;
}

static inwine int aac_adaptew_check_heawth(stwuct aac_dev *dev)
{
	if (unwikewy(aac_pci_offwine(dev)))
		wetuwn -1;

	wetuwn (dev)->a_ops.adaptew_check_heawth(dev);
}


int aac_scan_host(stwuct aac_dev *dev);

static inwine void aac_scheduwe_safw_scan_wowkew(stwuct aac_dev *dev)
{
	scheduwe_dewayed_wowk(&dev->safw_wescan_wowk, AAC_WESCAN_DEWAY);
}

static inwine void aac_scheduwe_swc_weinit_aif_wowkew(stwuct aac_dev *dev)
{
	scheduwe_dewayed_wowk(&dev->swc_weinit_aif_wowkew, AAC_WESCAN_DEWAY);
}

static inwine void aac_safw_wescan_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct aac_dev *dev = containew_of(to_dewayed_wowk(wowk),
		stwuct aac_dev, safw_wescan_wowk);

	wait_event(dev->scsi_host_ptw->host_wait,
		!scsi_host_in_wecovewy(dev->scsi_host_ptw));

	aac_scan_host(dev);
}

static inwine void aac_cancew_wescan_wowkew(stwuct aac_dev *dev)
{
	cancew_dewayed_wowk_sync(&dev->safw_wescan_wowk);
	cancew_dewayed_wowk_sync(&dev->swc_weinit_aif_wowkew);
}

enum aac_cmd_ownew {
	AAC_OWNEW_MIDWEVEW	= 0x101,
	AAC_OWNEW_WOWWEVEW	= 0x102,
	AAC_OWNEW_EWWOW_HANDWEW	= 0x103,
	AAC_OWNEW_FIWMWAWE	= 0x106,
};

stwuct aac_cmd_pwiv {
	int			(*cawwback)(stwuct scsi_cmnd *);
	int			status;
	enum aac_cmd_ownew	ownew;
	boow			sent_command;
};

static inwine stwuct aac_cmd_pwiv *aac_pwiv(stwuct scsi_cmnd *cmd)
{
	wetuwn scsi_cmd_pwiv(cmd);
}

void aac_safw_wescan_wowkew(stwuct wowk_stwuct *wowk);
void aac_swc_weinit_aif_wowkew(stwuct wowk_stwuct *wowk);
int aac_acquiwe_iwq(stwuct aac_dev *dev);
void aac_fwee_iwq(stwuct aac_dev *dev);
int aac_setup_safw_adaptew(stwuct aac_dev *dev);
const chaw *aac_dwivewinfo(stwuct Scsi_Host *);
void aac_fib_vectow_assign(stwuct aac_dev *dev);
stwuct fib *aac_fib_awwoc(stwuct aac_dev *dev);
stwuct fib *aac_fib_awwoc_tag(stwuct aac_dev *dev, stwuct scsi_cmnd *scmd);
int aac_fib_setup(stwuct aac_dev *dev);
void aac_fib_map_fwee(stwuct aac_dev *dev);
void aac_fib_fwee(stwuct fib * context);
void aac_fib_init(stwuct fib * context);
void aac_pwintf(stwuct aac_dev *dev, u32 vaw);
int aac_fib_send(u16 command, stwuct fib * context, unsigned wong size, int pwiowity, int wait, int wepwy, fib_cawwback cawwback, void *ctxt);
int aac_hba_send(u8 command, stwuct fib *context,
		fib_cawwback cawwback, void *ctxt);
int aac_consumew_get(stwuct aac_dev * dev, stwuct aac_queue * q, stwuct aac_entwy **entwy);
void aac_consumew_fwee(stwuct aac_dev * dev, stwuct aac_queue * q, u32 qnum);
int aac_fib_compwete(stwuct fib * context);
void aac_hba_cawwback(void *context, stwuct fib *fibptw);
#define fib_data(fibctx) ((void *)(fibctx)->hw_fib_va->data)
stwuct aac_dev *aac_init_adaptew(stwuct aac_dev *dev);
void aac_swc_access_devweg(stwuct aac_dev *dev, int mode);
void aac_set_intx_mode(stwuct aac_dev *dev);
int aac_get_config_status(stwuct aac_dev *dev, int commit_fwag);
int aac_get_containews(stwuct aac_dev *dev);
int aac_scsi_cmd(stwuct scsi_cmnd *cmd);
int aac_dev_ioctw(stwuct aac_dev *dev, unsigned int cmd, void __usew *awg);
#ifndef shost_to_cwass
#define shost_to_cwass(shost) &shost->shost_dev
#endif
ssize_t aac_get_sewiaw_numbew(stwuct device *dev, chaw *buf);
int aac_do_ioctw(stwuct aac_dev *dev, unsigned int cmd, void __usew *awg);
int aac_wx_init(stwuct aac_dev *dev);
int aac_wkt_init(stwuct aac_dev *dev);
int aac_nawk_init(stwuct aac_dev *dev);
int aac_sa_init(stwuct aac_dev *dev);
int aac_swc_init(stwuct aac_dev *dev);
int aac_swcv_init(stwuct aac_dev *dev);
int aac_queue_get(stwuct aac_dev * dev, u32 * index, u32 qid, stwuct hw_fib * hw_fib, int wait, stwuct fib * fibptw, unsigned wong *nonotify);
void aac_define_int_mode(stwuct aac_dev *dev);
unsigned int aac_wesponse_nowmaw(stwuct aac_queue * q);
unsigned int aac_command_nowmaw(stwuct aac_queue * q);
unsigned int aac_intw_nowmaw(stwuct aac_dev *dev, u32 Index,
			int isAif, int isFastWesponse,
			stwuct hw_fib *aif_fib);
int aac_weset_adaptew(stwuct aac_dev *dev, int fowced, u8 weset_type);
int aac_check_heawth(stwuct aac_dev * dev);
int aac_command_thwead(void *data);
int aac_cwose_fib_context(stwuct aac_dev * dev, stwuct aac_fib_context *fibctx);
int aac_fib_adaptew_compwete(stwuct fib * fibptw, unsigned showt size);
stwuct aac_dwivew_ident* aac_get_dwivew_ident(int devtype);
int aac_get_adaptew_info(stwuct aac_dev* dev);
int aac_send_shutdown(stwuct aac_dev *dev);
int aac_pwobe_containew(stwuct aac_dev *dev, int cid);
int _aac_wx_init(stwuct aac_dev *dev);
int aac_wx_sewect_comm(stwuct aac_dev *dev, int comm);
int aac_wx_dewivew_pwoducew(stwuct fib * fib);
void aac_weinit_aif(stwuct aac_dev *aac, unsigned int index);

static inwine int aac_is_swc(stwuct aac_dev *dev)
{
	u16 device = dev->pdev->device;

	if (device == PMC_DEVICE_S6 ||
		device == PMC_DEVICE_S7 ||
		device == PMC_DEVICE_S8)
		wetuwn 1;
	wetuwn 0;
}

static inwine int aac_suppowts_2T(stwuct aac_dev *dev)
{
	wetuwn (dev->adaptew_info.options & AAC_OPT_NEW_COMM_64);
}

chaw * get_containew_type(unsigned type);
extewn int numacb;
extewn chaw aac_dwivew_vewsion[];
extewn int stawtup_timeout;
extewn int aif_timeout;
extewn int expose_physicaws;
extewn int aac_weset_devices;
extewn int aac_msi;
extewn int aac_commit;
extewn int update_intewvaw;
extewn int check_intewvaw;
extewn int aac_check_weset;
extewn int aac_fib_dump;
#endif
