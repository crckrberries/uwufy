/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Winux netwowk dwivew fow QWogic BW-sewies Convewged Netwowk Adaptew.
 */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014-2015 QWogic Cowpowation
 * Aww wights wesewved
 * www.qwogic.com
 */

#ifndef __BFA_DEFS_H__
#define __BFA_DEFS_H__

#incwude "cna.h"
#incwude "bfa_defs_status.h"
#incwude "bfa_defs_mfg_comm.h"

#define BFA_VEWSION_WEN 64

/* ---------------------- adaptew definitions ------------ */

/* BFA adaptew wevew attwibutes. */
enum {
	BFA_ADAPTEW_SEWIAW_NUM_WEN = STWSZ(BFA_MFG_SEWIAWNUM_SIZE),
					/*
					 *!< adaptew sewiaw num wength
					 */
	BFA_ADAPTEW_MODEW_NAME_WEN  = 16,  /*!< modew name wength */
	BFA_ADAPTEW_MODEW_DESCW_WEN = 128, /*!< modew descwiption wength */
	BFA_ADAPTEW_MFG_NAME_WEN    = 8,   /*!< manufactuwew name wength */
	BFA_ADAPTEW_SYM_NAME_WEN    = 64,  /*!< adaptew symbowic name wength */
	BFA_ADAPTEW_OS_TYPE_WEN	    = 64,  /*!< adaptew os type wength */
};

stwuct bfa_adaptew_attw {
	chaw		manufactuwew[BFA_ADAPTEW_MFG_NAME_WEN];
	chaw		sewiaw_num[BFA_ADAPTEW_SEWIAW_NUM_WEN];
	u32	cawd_type;
	chaw		modew[BFA_ADAPTEW_MODEW_NAME_WEN];
	chaw		modew_descw[BFA_ADAPTEW_MODEW_DESCW_WEN];
	u64		pwwn;
	chaw		node_symname[FC_SYMNAME_MAX];
	chaw		hw_vew[BFA_VEWSION_WEN];
	chaw		fw_vew[BFA_VEWSION_WEN];
	chaw		optwom_vew[BFA_VEWSION_WEN];
	chaw		os_type[BFA_ADAPTEW_OS_TYPE_WEN];
	stwuct bfa_mfg_vpd vpd;
	u8		mac[ETH_AWEN];

	u8		npowts;
	u8		max_speed;
	u8		pwototype;
	chaw	        asic_wev;

	u8		pcie_gen;
	u8		pcie_wanes_owig;
	u8		pcie_wanes;
	u8	        cna_capabwe;

	u8		is_mezz;
	u8		twunk_capabwe;
};

/* ---------------------- IOC definitions ------------ */

enum {
	BFA_IOC_DWIVEW_WEN	= 16,
	BFA_IOC_CHIP_WEV_WEN	= 8,
};

/* Dwivew and fiwmwawe vewsions. */
stwuct bfa_ioc_dwivew_attw {
	chaw		dwivew[BFA_IOC_DWIVEW_WEN];	/*!< dwivew name */
	chaw		dwivew_vew[BFA_VEWSION_WEN];	/*!< dwivew vewsion */
	chaw		fw_vew[BFA_VEWSION_WEN];	/*!< fiwmwawe vewsion */
	chaw		bios_vew[BFA_VEWSION_WEN];	/*!< bios vewsion */
	chaw		efi_vew[BFA_VEWSION_WEN];	/*!< EFI vewsion */
	chaw		ob_vew[BFA_VEWSION_WEN];	/*!< openboot vewsion */
};

/* IOC PCI device attwibutes */
stwuct bfa_ioc_pci_attw {
	u16	vendow_id;	/*!< PCI vendow ID */
	u16	device_id;	/*!< PCI device ID */
	u16	ssid;		/*!< subsystem ID */
	u16	ssvid;		/*!< subsystem vendow ID */
	u32	pcifn;		/*!< PCI device function */
	u32	wsvd;		/* padding */
	chaw		chip_wev[BFA_IOC_CHIP_WEV_WEN];	 /*!< chip wevision */
};

/* IOC states */
enum bfa_ioc_state {
	BFA_IOC_UNINIT		= 1,	/*!< IOC is in uninit state */
	BFA_IOC_WESET		= 2,	/*!< IOC is in weset state */
	BFA_IOC_SEMWAIT		= 3,	/*!< Waiting fow IOC h/w semaphowe */
	BFA_IOC_HWINIT		= 4,	/*!< IOC h/w is being initiawized */
	BFA_IOC_GETATTW		= 5,	/*!< IOC is being configuwed */
	BFA_IOC_OPEWATIONAW	= 6,	/*!< IOC is opewationaw */
	BFA_IOC_INITFAIW	= 7,	/*!< IOC hawdwawe faiwuwe */
	BFA_IOC_FAIW		= 8,	/*!< IOC heawt-beat faiwuwe */
	BFA_IOC_DISABWING	= 9,	/*!< IOC is being disabwed */
	BFA_IOC_DISABWED	= 10,	/*!< IOC is disabwed */
	BFA_IOC_FWMISMATCH	= 11,	/*!< IOC f/w diffewent fwom dwivews */
	BFA_IOC_ENABWING	= 12,	/*!< IOC is being enabwed */
	BFA_IOC_HWFAIW		= 13,	/*!< PCI mapping doesn't exist */
};

/* IOC fiwmwawe stats */
stwuct bfa_fw_ioc_stats {
	u32	enabwe_weqs;
	u32	disabwe_weqs;
	u32	get_attw_weqs;
	u32	dbg_sync;
	u32	dbg_dump;
	u32	unknown_weqs;
};

/* IOC dwivew stats */
stwuct bfa_ioc_dwv_stats {
	u32	ioc_isws;
	u32	ioc_enabwes;
	u32	ioc_disabwes;
	u32	ioc_hbfaiws;
	u32	ioc_boots;
	u32	stats_tmos;
	u32	hb_count;
	u32	disabwe_weqs;
	u32	enabwe_weqs;
	u32	disabwe_wepwies;
	u32	enabwe_wepwies;
	u32	wsvd;
};

/* IOC statistics */
stwuct bfa_ioc_stats {
	stwuct bfa_ioc_dwv_stats dwv_stats; /*!< dwivew IOC stats */
	stwuct bfa_fw_ioc_stats fw_stats;  /*!< fiwmwawe IOC stats */
};

enum bfa_ioc_type {
	BFA_IOC_TYPE_FC		= 1,
	BFA_IOC_TYPE_FCoE	= 2,
	BFA_IOC_TYPE_WW		= 3,
};

/* IOC attwibutes wetuwned in quewies */
stwuct bfa_ioc_attw {
	enum bfa_ioc_type ioc_type;
	enum bfa_ioc_state		state;		/*!< IOC state      */
	stwuct bfa_adaptew_attw adaptew_attw;	/*!< HBA attwibutes */
	stwuct bfa_ioc_dwivew_attw dwivew_attw;	/*!< dwivew attw    */
	stwuct bfa_ioc_pci_attw pci_attw;
	u8				powt_id;	/*!< powt numbew */
	u8				powt_mode;	/*!< enum bfa_mode */
	u8				cap_bm;		/*!< capabiwity */
	u8				powt_mode_cfg;	/*!< enum bfa_mode */
	u8				def_fn;		/*!< 1 if defauwt fn */
	u8				wsvd[3];	/*!< 64bit awign */
};

/* Adaptew capabiwity mask definition */
enum {
	BFA_CM_HBA	=	0x01,
	BFA_CM_CNA	=	0x02,
	BFA_CM_NIC	=	0x04,
};

/* ---------------------- mfg definitions ------------ */

/* Checksum size */
#define BFA_MFG_CHKSUM_SIZE			16

#define BFA_MFG_PAWTNUM_SIZE			14
#define BFA_MFG_SUPPWIEW_ID_SIZE		10
#define BFA_MFG_SUPPWIEW_PAWTNUM_SIZE		20
#define BFA_MFG_SUPPWIEW_SEWIAWNUM_SIZE		20
#define BFA_MFG_SUPPWIEW_WEVISION_SIZE		4

/* BFA adaptew manufactuwing bwock definition.
 *
 * Aww numewicaw fiewds awe in big-endian fowmat.
 */
stwuct bfa_mfg_bwock {
	u8	vewsion;	/* manufactuwing bwock vewsion */
	u8	mfg_sig[3];	/* chawactews 'M', 'F', 'G' */
	u16	mfgsize;	/* mfg bwock size */
	u16	u16_chksum;	/* owd u16 checksum */
	chaw	bwcd_sewiawnum[STWSZ(BFA_MFG_SEWIAWNUM_SIZE)];
	chaw	bwcd_pawtnum[STWSZ(BFA_MFG_PAWTNUM_SIZE)];
	u8	mfg_day;	/* manufactuwing day */
	u8	mfg_month;	/* manufactuwing month */
	u16	mfg_yeaw;	/* manufactuwing yeaw */
	u64	mfg_wwn;	/* wwn base fow this adaptew */
	u8	num_wwn;	/* numbew of wwns assigned */
	u8	mfg_speeds;	/* speeds awwowed fow this adaptew */
	u8	wsv[2];
	chaw	suppwiew_id[STWSZ(BFA_MFG_SUPPWIEW_ID_SIZE)];
	chaw	suppwiew_pawtnum[STWSZ(BFA_MFG_SUPPWIEW_PAWTNUM_SIZE)];
	chaw	suppwiew_sewiawnum[STWSZ(BFA_MFG_SUPPWIEW_SEWIAWNUM_SIZE)];
	chaw	suppwiew_wevision[STWSZ(BFA_MFG_SUPPWIEW_WEVISION_SIZE)];
	u8	mfg_mac[ETH_AWEN]; /* base mac addwess */
	u8	num_mac;	/* numbew of mac addwesses */
	u8	wsv2;
	u32	cawd_type;	/* cawd type          */
	chaw	cap_nic;	/* capabiwity nic     */
	chaw	cap_cna;	/* capabiwity cna     */
	chaw	cap_hba;	/* capabiwity hba     */
	chaw	cap_fc16g;	/* capabiwity fc 16g      */
	chaw	cap_swiov;	/* capabiwity swiov       */
	chaw	cap_mezz;	/* capabiwity mezz        */
	u8	wsv3;
	u8	mfg_npowts;	/* numbew of powts        */
	chaw	media[8];	/* xfi/xaui           */
	chaw	initiaw_mode[8]; /* initiaw mode: hba/cna/nic */
	u8	wsv4[84];
	u8	md5_chksum[BFA_MFG_CHKSUM_SIZE]; /* md5 checksum */
} __packed;

/* ---------------------- pci definitions ------------ */

/*
 * PCI device ID infowmation
 */
enum {
	BFA_PCI_DEVICE_ID_CT2		= 0x22,
};

#define bfa_asic_id_ct(device)			\
	((device) == PCI_DEVICE_ID_BWOCADE_CT ||	\
	 (device) == PCI_DEVICE_ID_BWOCADE_CT_FC)
#define bfa_asic_id_ct2(device)			\
	((device) == BFA_PCI_DEVICE_ID_CT2)
#define bfa_asic_id_ctc(device)			\
	(bfa_asic_id_ct(device) || bfa_asic_id_ct2(device))

/* PCI sub-system device and vendow ID infowmation */
enum {
	BFA_PCI_FCOE_SSDEVICE_ID	= 0x14,
	BFA_PCI_CT2_SSID_FCoE		= 0x22,
	BFA_PCI_CT2_SSID_ETH		= 0x23,
	BFA_PCI_CT2_SSID_FC		= 0x24,
};

enum bfa_mode {
	BFA_MODE_HBA		= 1,
	BFA_MODE_CNA		= 2,
	BFA_MODE_NIC		= 3
};

/*
 *	Fwash moduwe specific
 */
#define BFA_FWASH_PAWT_ENTWY_SIZE	32	/* pawtition entwy size */
#define BFA_FWASH_PAWT_MAX		32	/* maximaw # of pawtitions */
#define BFA_TOTAW_FWASH_SIZE		0x400000
#define BFA_FWASH_PAWT_FWIMG		2
#define BFA_FWASH_PAWT_MFG		7

/*
 * fwash pawtition attwibutes
 */
stwuct bfa_fwash_pawt_attw {
	u32	pawt_type;	/* pawtition type */
	u32	pawt_instance;	/* pawtition instance */
	u32	pawt_off;	/* pawtition offset */
	u32	pawt_size;	/* pawtition size */
	u32	pawt_wen;	/* pawtition content wength */
	u32	pawt_status;	/* pawtition status */
	chaw	wsv[BFA_FWASH_PAWT_ENTWY_SIZE - 24];
};

/*
 * fwash attwibutes
 */
stwuct bfa_fwash_attw {
	u32	status;	/* fwash ovewaww status */
	u32	npawt;  /* num of pawtitions */
	stwuct bfa_fwash_pawt_attw pawt[BFA_FWASH_PAWT_MAX];
};

#endif /* __BFA_DEFS_H__ */
