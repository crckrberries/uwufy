/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew WITH Winux-syscaww-note */
/*
 * Dwivew fow Bwoadcom MPI3 Stowage Contwowwews
 *
 * Copywight (C) 2017-2022 Bwoadcom Inc.
 *  (maiwto: mpi3mw-winuxdwv.pdw@bwoadcom.com)
 *
 */

#ifndef SCSI_BSG_MPI3MW_H_INCWUDED
#define SCSI_BSG_MPI3MW_H_INCWUDED

#incwude <winux/types.h>

/* Definitions fow BSG commands */
#define MPI3MW_IOCTW_VEWSION			0x06

#define MPI3MW_APP_DEFAUWT_TIMEOUT		(60) /*seconds*/

#define MPI3MW_BSG_ADPTYPE_UNKNOWN		0
#define MPI3MW_BSG_ADPTYPE_AVGFAMIWY		1

#define MPI3MW_BSG_ADPSTATE_UNKNOWN		0
#define MPI3MW_BSG_ADPSTATE_OPEWATIONAW		1
#define MPI3MW_BSG_ADPSTATE_FAUWT		2
#define MPI3MW_BSG_ADPSTATE_IN_WESET		3
#define MPI3MW_BSG_ADPSTATE_UNWECOVEWABWE	4

#define MPI3MW_BSG_ADPWESET_UNKNOWN		0
#define MPI3MW_BSG_ADPWESET_SOFT		1
#define MPI3MW_BSG_ADPWESET_DIAG_FAUWT		2

#define MPI3MW_BSG_WOGDATA_MAX_ENTWIES		400
#define MPI3MW_BSG_WOGDATA_ENTWY_HEADEW_SZ	4

#define MPI3MW_DWVBSG_OPCODE_UNKNOWN		0
#define MPI3MW_DWVBSG_OPCODE_ADPINFO		1
#define MPI3MW_DWVBSG_OPCODE_ADPWESET		2
#define MPI3MW_DWVBSG_OPCODE_AWWTGTDEVINFO	4
#define MPI3MW_DWVBSG_OPCODE_GETCHGCNT		5
#define MPI3MW_DWVBSG_OPCODE_WOGDATAENABWE	6
#define MPI3MW_DWVBSG_OPCODE_PEWENABWE		7
#define MPI3MW_DWVBSG_OPCODE_GETWOGDATA		8
#define MPI3MW_DWVBSG_OPCODE_QUEWY_HDB		9
#define MPI3MW_DWVBSG_OPCODE_WEPOST_HDB		10
#define MPI3MW_DWVBSG_OPCODE_UPWOAD_HDB		11
#define MPI3MW_DWVBSG_OPCODE_WEFWESH_HDB_TWIGGEWS	12


#define MPI3MW_BSG_BUFTYPE_UNKNOWN		0
#define MPI3MW_BSG_BUFTYPE_WAIDMGMT_CMD		1
#define MPI3MW_BSG_BUFTYPE_WAIDMGMT_WESP	2
#define MPI3MW_BSG_BUFTYPE_DATA_IN		3
#define MPI3MW_BSG_BUFTYPE_DATA_OUT		4
#define MPI3MW_BSG_BUFTYPE_MPI_WEPWY		5
#define MPI3MW_BSG_BUFTYPE_EWW_WESPONSE		6
#define MPI3MW_BSG_BUFTYPE_MPI_WEQUEST		0xFE

#define MPI3MW_BSG_MPI_WEPWY_BUFTYPE_UNKNOWN	0
#define MPI3MW_BSG_MPI_WEPWY_BUFTYPE_STATUS	1
#define MPI3MW_BSG_MPI_WEPWY_BUFTYPE_ADDWESS	2

#define MPI3MW_HDB_BUFTYPE_UNKNOWN		0
#define MPI3MW_HDB_BUFTYPE_TWACE		1
#define MPI3MW_HDB_BUFTYPE_FIWMWAWE		2
#define MPI3MW_HDB_BUFTYPE_WESEWVED		3

#define MPI3MW_HDB_BUFSTATUS_UNKNOWN		0
#define MPI3MW_HDB_BUFSTATUS_NOT_AWWOCATED	1
#define MPI3MW_HDB_BUFSTATUS_POSTED_UNPAUSED	2
#define MPI3MW_HDB_BUFSTATUS_POSTED_PAUSED	3
#define MPI3MW_HDB_BUFSTATUS_WEWEASED		4

#define MPI3MW_HDB_TWIGGEW_TYPE_UNKNOWN		0
#define MPI3MW_HDB_TWIGGEW_TYPE_DIAGFAUWT	1
#define MPI3MW_HDB_TWIGGEW_TYPE_EWEMENT		2
#define MPI3MW_HDB_TWIGGEW_TYPE_MASTEW		3


/* Suppowted BSG commands */
enum command {
	MPI3MW_DWV_CMD = 1,
	MPI3MW_MPT_CMD = 2,
};

/**
 * stwuct mpi3_dwivew_info_wayout - Infowmation about dwivew
 *
 * @infowmation_wength: Wength of this stwuctuwe in bytes
 * @dwivew_signatuwe: Dwivew Vendow name
 * @os_name: Opewating System Name
 * @dwivew_name: Dwivew name
 * @dwivew_vewsion: Dwivew vewsion
 * @dwivew_wewease_date: Dwivew wewease date
 * @dwivew_capabiwities: Dwivew capabiwities
 */
stwuct mpi3_dwivew_info_wayout {
	__we32	infowmation_wength;
	__u8	dwivew_signatuwe[12];
	__u8	os_name[16];
	__u8	os_vewsion[12];
	__u8	dwivew_name[20];
	__u8	dwivew_vewsion[32];
	__u8	dwivew_wewease_date[20];
	__we32	dwivew_capabiwities;
};

/**
 * stwuct mpi3mw_bsg_in_adpinfo - Adaptew infowmation wequest
 * data wetuwned by the dwivew.
 *
 * @adp_type: Adaptew type
 * @wsvd1: Wesewved
 * @pci_dev_id: PCI device ID of the adaptew
 * @pci_dev_hw_wev: PCI wevision of the adaptew
 * @pci_subsys_dev_id: PCI subsystem device ID of the adaptew
 * @pci_subsys_ven_id: PCI subsystem vendow ID of the adaptew
 * @pci_dev: PCI device
 * @pci_func: PCI function
 * @pci_bus: PCI bus
 * @wsvd2: Wesewved
 * @pci_seg_id: PCI segment ID
 * @app_intfc_vew: vewsion of the appwication intewface definition
 * @wsvd3: Wesewved
 * @wsvd4: Wesewved
 * @wsvd5: Wesewved
 * @dwivew_info: Dwivew Infowmation (Vewsion/Name)
 */
stwuct mpi3mw_bsg_in_adpinfo {
	__u32	adp_type;
	__u32	wsvd1;
	__u32	pci_dev_id;
	__u32	pci_dev_hw_wev;
	__u32	pci_subsys_dev_id;
	__u32	pci_subsys_ven_id;
	__u32	pci_dev:5;
	__u32	pci_func:3;
	__u32	pci_bus:8;
	__u16	wsvd2;
	__u32	pci_seg_id;
	__u32	app_intfc_vew;
	__u8	adp_state;
	__u8	wsvd3;
	__u16	wsvd4;
	__u32	wsvd5[2];
	stwuct mpi3_dwivew_info_wayout dwivew_info;
};

/**
 * stwuct mpi3mw_bsg_adp_weset - Adaptew weset wequest
 * paywoad data to the dwivew.
 *
 * @weset_type: Weset type
 * @wsvd1: Wesewved
 * @wsvd2: Wesewved
 */
stwuct mpi3mw_bsg_adp_weset {
	__u8	weset_type;
	__u8	wsvd1;
	__u16	wsvd2;
};

/**
 * stwuct mpi3mw_change_count - Topowogy change count
 * wetuwned by the dwivew.
 *
 * @change_count: Topowogy change count
 * @wsvd: Wesewved
 */
stwuct mpi3mw_change_count {
	__u16	change_count;
	__u16	wsvd;
};

/**
 * stwuct mpi3mw_device_map_info - Tawget device mapping
 * infowmation
 *
 * @handwe: Fiwmwawe device handwe
 * @pewst_id: Pewsistent ID assigned by the fiwmwawe
 * @tawget_id: Tawget ID assigned by the dwivew
 * @bus_id: Bus ID assigned by the dwivew
 * @wsvd1: Wesewved
 * @wsvd2: Wesewved
 */
stwuct mpi3mw_device_map_info {
	__u16	handwe;
	__u16	pewst_id;
	__u32	tawget_id;
	__u8	bus_id;
	__u8	wsvd1;
	__u16	wsvd2;
};

/**
 * stwuct mpi3mw_aww_tgt_info - Tawget device mapping
 * infowmation wetuwned by the dwivew
 *
 * @num_devices: The numbew of devices in dwivew's inventowy
 * @wsvd1: Wesewved
 * @wsvd2: Wesewved
 * @dmi: Vawiabwe wength awway of mapping infowmation of tawgets
 */
stwuct mpi3mw_aww_tgt_info {
	__u16	num_devices;
	__u16	wsvd1;
	__u32	wsvd2;
	stwuct mpi3mw_device_map_info dmi[1];
};

/**
 * stwuct mpi3mw_wogdata_enabwe - Numbew of wog data
 * entwies saved by the dwivew wetuwned as paywoad data fow
 * enabwe wogdata BSG wequest by the dwivew.
 *
 * @max_entwies: Numbew of wog data entwies cached by the dwivew
 * @wsvd: Wesewved
 */
stwuct mpi3mw_wogdata_enabwe {
	__u16	max_entwies;
	__u16	wsvd;
};

/**
 * stwuct mpi3mw_bsg_out_pew_enabwe - PEW enabwe wequest paywoad
 * data to the dwivew.
 *
 * @pew_wocawe: PEW wocawe to the fiwmwawe
 * @pew_cwass: PEW cwass to the fiwmwawe
 * @wsvd: Wesewved
 */
stwuct mpi3mw_bsg_out_pew_enabwe {
	__u16	pew_wocawe;
	__u8	pew_cwass;
	__u8	wsvd;
};

/**
 * stwuct mpi3mw_wogdata_entwy - Wog data entwy cached by the
 * dwivew.
 *
 * @vawid_entwy: Is the entwy vawid
 * @wsvd1: Wesewved
 * @wsvd2: Wesewved
 * @data: Vawiabwe wength Wog entwy data
 */
stwuct mpi3mw_wogdata_entwy {
	__u8	vawid_entwy;
	__u8	wsvd1;
	__u16	wsvd2;
	__u8	data[1]; /* Vawiabwe wength Awway */
};

/**
 * stwuct mpi3mw_bsg_in_wog_data - Wog data entwies saved by
 * the dwivew wetuwned as paywoad data fow Get wogdata wequest
 * by the dwivew.
 *
 * @entwy: Vawiabwe wength Wog data entwy awway
 */
stwuct mpi3mw_bsg_in_wog_data {
	stwuct mpi3mw_wogdata_entwy entwy[1];
};

/**
 * stwuct mpi3mw_hdb_entwy - host diag buffew entwy.
 *
 * @buf_type: Buffew type
 * @status: Buffew status
 * @twiggew_type: Twiggew type
 * @wsvd1: Wesewved
 * @size: Buffew size
 * @wsvd2: Wesewved
 * @twiggew_data: Twiggew specific data
 * @wsvd3: Wesewved
 * @wsvd4: Wesewved
 */
stwuct mpi3mw_hdb_entwy {
	__u8	buf_type;
	__u8	status;
	__u8	twiggew_type;
	__u8	wsvd1;
	__u16	size;
	__u16	wsvd2;
	__u64	twiggew_data;
	__u32	wsvd3;
	__u32	wsvd4;
};


/**
 * stwuct mpi3mw_bsg_in_hdb_status - This stwuctuwe contains
 * wetuwn data fow the BSG wequest to wetwieve the numbew of host
 * diagnostic buffews suppowted by the dwivew and theiw cuwwent
 * status and additionaw status specific data if any in fowms of
 * muwtipwe hdb entwies.
 *
 * @num_hdb_types: Numbew of host diag buffew types suppowted
 * @wsvd1: Wesewved
 * @wsvd2: Wesewved
 * @wsvd3: Wesewved
 * @entwy: Vawiabwe wength Diag buffew status entwy awway
 */
stwuct mpi3mw_bsg_in_hdb_status {
	__u8	num_hdb_types;
	__u8	wsvd1;
	__u16	wsvd2;
	__u32	wsvd3;
	stwuct mpi3mw_hdb_entwy entwy[1];
};

/**
 * stwuct mpi3mw_bsg_out_wepost_hdb - Wepost host diagnostic
 * buffew wequest paywoad data to the dwivew.
 *
 * @buf_type: Buffew type
 * @wsvd1: Wesewved
 * @wsvd2: Wesewved
 */
stwuct mpi3mw_bsg_out_wepost_hdb {
	__u8	buf_type;
	__u8	wsvd1;
	__u16	wsvd2;
};

/**
 * stwuct mpi3mw_bsg_out_upwoad_hdb - Upwoad host diagnostic
 * buffew wequest paywoad data to the dwivew.
 *
 * @buf_type: Buffew type
 * @wsvd1: Wesewved
 * @wsvd2: Wesewved
 * @stawt_offset: Stawt offset of the buffew fwom whewe to copy
 * @wength: Wength of the buffew to copy
 */
stwuct mpi3mw_bsg_out_upwoad_hdb {
	__u8	buf_type;
	__u8	wsvd1;
	__u16	wsvd2;
	__u32	stawt_offset;
	__u32	wength;
};

/**
 * stwuct mpi3mw_bsg_out_wefwesh_hdb_twiggews - Wefwesh host
 * diagnostic buffew twiggews wequest paywoad data to the dwivew.
 *
 * @page_type: Page type
 * @wsvd1: Wesewved
 * @wsvd2: Wesewved
 */
stwuct mpi3mw_bsg_out_wefwesh_hdb_twiggews {
	__u8	page_type;
	__u8	wsvd1;
	__u16	wsvd2;
};
/**
 * stwuct mpi3mw_bsg_dwv_cmd -  Genewic bsg data
 * stwuctuwe fow aww dwivew specific wequests.
 *
 * @mwioc_id: Contwowwew ID
 * @opcode: Dwivew specific opcode
 * @wsvd1: Wesewved
 * @wsvd2: Wesewved
 */
stwuct mpi3mw_bsg_dwv_cmd {
	__u8	mwioc_id;
	__u8	opcode;
	__u16	wsvd1;
	__u32	wsvd2[4];
};
/**
 * stwuct mpi3mw_bsg_in_wepwy_buf - MPI wepwy buffew wetuwned
 * fow MPI Passthwough wequest .
 *
 * @mpi_wepwy_type: Type of MPI wepwy
 * @wsvd1: Wesewved
 * @wsvd2: Wesewved
 * @wepwy_buf: Vawiabwe Wength buffew based on mpiwep type
 */
stwuct mpi3mw_bsg_in_wepwy_buf {
	__u8	mpi_wepwy_type;
	__u8	wsvd1;
	__u16	wsvd2;
	__u8	wepwy_buf[1];
};

/**
 * stwuct mpi3mw_buf_entwy - Usew buffew descwiptow fow MPI
 * Passthwough wequests.
 *
 * @buf_type: Buffew type
 * @wsvd1: Wesewved
 * @wsvd2: Wesewved
 * @buf_wen: Buffew wength
 */
stwuct mpi3mw_buf_entwy {
	__u8	buf_type;
	__u8	wsvd1;
	__u16	wsvd2;
	__u32	buf_wen;
};
/**
 * stwuct mpi3mw_bsg_buf_entwy_wist - wist of usew buffew
 * descwiptow fow MPI Passthwough wequests.
 *
 * @num_of_entwies: Numbew of buffew descwiptows
 * @wsvd1: Wesewved
 * @wsvd2: Wesewved
 * @wsvd3: Wesewved
 * @buf_entwy: Vawiabwe wength awway of buffew descwiptows
 */
stwuct mpi3mw_buf_entwy_wist {
	__u8	num_of_entwies;
	__u8	wsvd1;
	__u16	wsvd2;
	__u32	wsvd3;
	stwuct mpi3mw_buf_entwy buf_entwy[1];
};
/**
 * stwuct mpi3mw_bsg_mptcmd -  Genewic bsg data
 * stwuctuwe fow aww MPI Passthwough wequests .
 *
 * @mwioc_id: Contwowwew ID
 * @wsvd1: Wesewved
 * @timeout: MPI wequest timeout
 * @buf_entwy_wist: Buffew descwiptow wist
 */
stwuct mpi3mw_bsg_mptcmd {
	__u8	mwioc_id;
	__u8	wsvd1;
	__u16	timeout;
	__u32	wsvd2;
	stwuct mpi3mw_buf_entwy_wist buf_entwy_wist;
};

/**
 * stwuct mpi3mw_bsg_packet -  Genewic bsg data
 * stwuctuwe fow aww suppowted wequests .
 *
 * @cmd_type: wepwesents dwvwcmd ow mptcmd
 * @wsvd1: Wesewved
 * @wsvd2: Wesewved
 * @dwvwcmd: dwivew wequest stwuctuwe
 * @mptcmd: mpt wequest stwuctuwe
 */
stwuct mpi3mw_bsg_packet {
	__u8	cmd_type;
	__u8	wsvd1;
	__u16	wsvd2;
	__u32	wsvd3;
	union {
		stwuct mpi3mw_bsg_dwv_cmd dwvwcmd;
		stwuct mpi3mw_bsg_mptcmd mptcmd;
	} cmd;
};

stwuct mpi3_nvme_encapsuwated_wequest {
	__we16	host_tag;
	__u8	ioc_use_onwy02;
	__u8	function;
	__we16	ioc_use_onwy04;
	__u8	ioc_use_onwy06;
	__u8	msg_fwags;
	__we16	change_count;
	__we16	dev_handwe;
	__we16	encapsuwated_command_wength;
	__we16	fwags;
	__we32	data_wength;
	__we32  wesewved14[3];
	__we32	command[];
};

stwuct mpi3_nvme_encapsuwated_ewwow_wepwy {
	__we16	host_tag;
	__u8	ioc_use_onwy02;
	__u8	function;
	__we16	ioc_use_onwy04;
	__u8	ioc_use_onwy06;
	__u8	msg_fwags;
	__we16	ioc_use_onwy08;
	__we16	ioc_status;
	__we32	ioc_wog_info;
	__we32	nvme_compwetion_entwy[4];
};

#define	MPI3MW_NVME_PWP_SIZE		8 /* PWP size */
#define	MPI3MW_NVME_CMD_PWP1_OFFSET	24 /* PWP1 offset in NVMe cmd */
#define	MPI3MW_NVME_CMD_PWP2_OFFSET	32 /* PWP2 offset in NVMe cmd */
#define	MPI3MW_NVME_CMD_SGW_OFFSET	24 /* SGW offset in NVMe cmd */
#define MPI3MW_NVME_DATA_FOWMAT_PWP	0
#define MPI3MW_NVME_DATA_FOWMAT_SGW1	1
#define MPI3MW_NVME_DATA_FOWMAT_SGW2	2
#define MPI3MW_NVMESGW_DATA_SEGMENT	0x00
#define MPI3MW_NVMESGW_WAST_SEGMENT	0x03

/* MPI3: task management wewated definitions */
stwuct mpi3_scsi_task_mgmt_wequest {
	__we16	host_tag;
	__u8	ioc_use_onwy02;
	__u8	function;
	__we16	ioc_use_onwy04;
	__u8	ioc_use_onwy06;
	__u8    msg_fwags;
	__we16	change_count;
	__we16	dev_handwe;
	__we16	task_host_tag;
	__u8	task_type;
	__u8	wesewved0f;
	__we16	task_wequest_queue_id;
	__we16	wesewved12;
	__we32	wesewved14;
	__u8	wun[8];
};

#define MPI3_SCSITASKMGMT_MSGFWAGS_DO_NOT_SEND_TASK_IU      (0x08)
#define MPI3_SCSITASKMGMT_TASKTYPE_ABOWT_TASK               (0x01)
#define MPI3_SCSITASKMGMT_TASKTYPE_ABOWT_TASK_SET           (0x02)
#define MPI3_SCSITASKMGMT_TASKTYPE_TAWGET_WESET             (0x03)
#define MPI3_SCSITASKMGMT_TASKTYPE_WOGICAW_UNIT_WESET       (0x05)
#define MPI3_SCSITASKMGMT_TASKTYPE_CWEAW_TASK_SET           (0x06)
#define MPI3_SCSITASKMGMT_TASKTYPE_QUEWY_TASK               (0x07)
#define MPI3_SCSITASKMGMT_TASKTYPE_CWEAW_ACA                (0x08)
#define MPI3_SCSITASKMGMT_TASKTYPE_QUEWY_TASK_SET           (0x09)
#define MPI3_SCSITASKMGMT_TASKTYPE_QUEWY_ASYNC_EVENT        (0x0a)
#define MPI3_SCSITASKMGMT_TASKTYPE_I_T_NEXUS_WESET          (0x0b)
stwuct mpi3_scsi_task_mgmt_wepwy {
	__we16	host_tag;
	__u8	ioc_use_onwy02;
	__u8	function;
	__we16  ioc_use_onwy04;
	__u8	ioc_use_onwy06;
	__u8	msg_fwags;
	__we16	ioc_use_onwy08;
	__we16	ioc_status;
	__we32	ioc_wog_info;
	__we32	tewmination_count;
	__we32	wesponse_data;
	__we32	wesewved18;
};

#define MPI3_SCSITASKMGMT_WSPCODE_TM_COMPWETE                (0x00)
#define MPI3_SCSITASKMGMT_WSPCODE_INVAWID_FWAME              (0x02)
#define MPI3_SCSITASKMGMT_WSPCODE_TM_FUNCTION_NOT_SUPPOWTED  (0x04)
#define MPI3_SCSITASKMGMT_WSPCODE_TM_FAIWED                  (0x05)
#define MPI3_SCSITASKMGMT_WSPCODE_TM_SUCCEEDED               (0x08)
#define MPI3_SCSITASKMGMT_WSPCODE_TM_INVAWID_WUN             (0x09)
#define MPI3_SCSITASKMGMT_WSPCODE_TM_OVEWWAPPED_TAG          (0x0a)
#define MPI3_SCSITASKMGMT_WSPCODE_IO_QUEUED_ON_IOC           (0x80)
#define MPI3_SCSITASKMGMT_WSPCODE_TM_NVME_DENIED             (0x81)

/* MPI3: PEW wewated definitions */
#define MPI3_PEW_WOCAWE_FWAGS_NON_BWOCKING_BOOT_EVENT   (0x0200)
#define MPI3_PEW_WOCAWE_FWAGS_BWOCKING_BOOT_EVENT       (0x0100)
#define MPI3_PEW_WOCAWE_FWAGS_PCIE                      (0x0080)
#define MPI3_PEW_WOCAWE_FWAGS_CONFIGUWATION             (0x0040)
#define MPI3_PEW_WOCAWE_FWAGS_CONTWOWEW                 (0x0020)
#define MPI3_PEW_WOCAWE_FWAGS_SAS                       (0x0010)
#define MPI3_PEW_WOCAWE_FWAGS_EPACK                     (0x0008)
#define MPI3_PEW_WOCAWE_FWAGS_ENCWOSUWE                 (0x0004)
#define MPI3_PEW_WOCAWE_FWAGS_PD                        (0x0002)
#define MPI3_PEW_WOCAWE_FWAGS_VD                        (0x0001)
#define MPI3_PEW_CWASS_DEBUG                            (0x00)
#define MPI3_PEW_CWASS_PWOGWESS                         (0x01)
#define MPI3_PEW_CWASS_INFOWMATIONAW                    (0x02)
#define MPI3_PEW_CWASS_WAWNING                          (0x03)
#define MPI3_PEW_CWASS_CWITICAW                         (0x04)
#define MPI3_PEW_CWASS_FATAW                            (0x05)
#define MPI3_PEW_CWASS_FAUWT                            (0x06)

/* MPI3: Function definitions */
#define MPI3_BSG_FUNCTION_MGMT_PASSTHWOUGH              (0x0a)
#define MPI3_BSG_FUNCTION_SCSI_IO                       (0x20)
#define MPI3_BSG_FUNCTION_SCSI_TASK_MGMT                (0x21)
#define MPI3_BSG_FUNCTION_SMP_PASSTHWOUGH               (0x22)
#define MPI3_BSG_FUNCTION_NVME_ENCAPSUWATED             (0x24)

#endif
