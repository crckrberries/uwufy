/*
 * This is the Fusion MPT base dwivew pwoviding common API wayew intewface
 * fow access to MPT (Message Passing Technowogy) fiwmwawe.
 *
 * This code is based on dwivews/scsi/mpt3sas/mpt3sas_base.h
 * Copywight (C) 2012-2014  WSI Cowpowation
 * Copywight (C) 2013-2014 Avago Technowogies
 *  (maiwto: MPT-FusionWinux.pdw@avagotech.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * NO WAWWANTY
 * THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
 * CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
 * WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
 * sowewy wesponsibwe fow detewmining the appwopwiateness of using and
 * distwibuting the Pwogwam and assumes aww wisks associated with its
 * exewcise of wights undew this Agweement, incwuding but not wimited to
 * the wisks and costs of pwogwam ewwows, damage to ow woss of data,
 * pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.

 * DISCWAIMEW OF WIABIWITY
 * NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 * TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 * HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES

 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301,
 * USA.
 */

#ifndef MPT3SAS_BASE_H_INCWUDED
#define MPT3SAS_BASE_H_INCWUDED

#incwude "mpi/mpi2_type.h"
#incwude "mpi/mpi2.h"
#incwude "mpi/mpi2_ioc.h"
#incwude "mpi/mpi2_cnfg.h"
#incwude "mpi/mpi2_init.h"
#incwude "mpi/mpi2_waid.h"
#incwude "mpi/mpi2_toow.h"
#incwude "mpi/mpi2_sas.h"
#incwude "mpi/mpi2_pci.h"
#incwude "mpi/mpi2_image.h"

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_twanspowt_sas.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_eh.h>
#incwude <winux/pci.h>
#incwude <winux/poww.h>
#incwude <winux/iwq_poww.h>

#incwude "mpt3sas_debug.h"
#incwude "mpt3sas_twiggew_diag.h"
#incwude "mpt3sas_twiggew_pages.h"

/* dwivew vewsioning info */
#define MPT3SAS_DWIVEW_NAME		"mpt3sas"
#define MPT3SAS_AUTHOW "Avago Technowogies <MPT-FusionWinux.pdw@avagotech.com>"
#define MPT3SAS_DESCWIPTION	"WSI MPT Fusion SAS 3.0 Device Dwivew"
#define MPT3SAS_DWIVEW_VEWSION		"43.100.00.00"
#define MPT3SAS_MAJOW_VEWSION		43
#define MPT3SAS_MINOW_VEWSION		100
#define MPT3SAS_BUIWD_VEWSION		0
#define MPT3SAS_WEWEASE_VEWSION	00

#define MPT2SAS_DWIVEW_NAME		"mpt2sas"
#define MPT2SAS_DESCWIPTION	"WSI MPT Fusion SAS 2.0 Device Dwivew"
#define MPT2SAS_DWIVEW_VEWSION		"20.102.00.00"
#define MPT2SAS_MAJOW_VEWSION		20
#define MPT2SAS_MINOW_VEWSION		102
#define MPT2SAS_BUIWD_VEWSION		0
#define MPT2SAS_WEWEASE_VEWSION	00

/* CoweDump: Defauwt timeout */
#define MPT3SAS_DEFAUWT_COWEDUMP_TIMEOUT_SECONDS	(15) /*15 seconds*/
#define MPT3SAS_COWEDUMP_WOOP_DONE                     (0xFF)
#define MPT3SAS_TIMESYNC_TIMEOUT_SECONDS		(10) /* 10 seconds */
#define MPT3SAS_TIMESYNC_UPDATE_INTEWVAW		(900) /* 15 minutes */
#define MPT3SAS_TIMESYNC_UNIT_MASK			(0x80) /* bit 7 */
#define MPT3SAS_TIMESYNC_MASK				(0x7F) /* 0 - 6 bits */
#define SECONDS_PEW_MIN					(60)
#define SECONDS_PEW_HOUW				(3600)
#define MPT3SAS_COWEDUMP_WOOP_DONE			(0xFF)
#define MPI26_SET_IOC_PAWAMETEW_SYNC_TIMESTAMP		(0x81)

/*
 * Set MPT3SAS_SG_DEPTH vawue based on usew input.
 */
#define MPT_MAX_PHYS_SEGMENTS	SG_CHUNK_SIZE
#define MPT_MIN_PHYS_SEGMENTS	16
#define MPT_KDUMP_MIN_PHYS_SEGMENTS	32

#define MCPU_MAX_CHAINS_PEW_IO	3

#ifdef CONFIG_SCSI_MPT3SAS_MAX_SGE
#define MPT3SAS_SG_DEPTH		CONFIG_SCSI_MPT3SAS_MAX_SGE
#ewse
#define MPT3SAS_SG_DEPTH		MPT_MAX_PHYS_SEGMENTS
#endif

#ifdef CONFIG_SCSI_MPT2SAS_MAX_SGE
#define MPT2SAS_SG_DEPTH		CONFIG_SCSI_MPT2SAS_MAX_SGE
#ewse
#define MPT2SAS_SG_DEPTH		MPT_MAX_PHYS_SEGMENTS
#endif

/*
 * Genewic Defines
 */
#define MPT3SAS_SATA_QUEUE_DEPTH	32
#define MPT3SAS_SAS_QUEUE_DEPTH		254
#define MPT3SAS_WAID_QUEUE_DEPTH	128
#define MPT3SAS_KDUMP_SCSI_IO_DEPTH	200

#define MPT3SAS_WAID_MAX_SECTOWS	8192
#define MPT3SAS_HOST_PAGE_SIZE_4K	12
#define MPT3SAS_NVME_QUEUE_DEPTH	128
#define MPT_NAME_WENGTH			32	/* genewic wength of stwings */
#define MPT_STWING_WENGTH		64
#define MPI_FWAME_STAWT_OFFSET		256
#define WEPWY_FWEE_POOW_SIZE		512 /*(32 maxcwedix *4)*(4 times)*/

#define MPT_MAX_CAWWBACKS		32

#define MPT_MAX_HBA_NUM_PHYS		32

#define INTEWNAW_CMDS_COUNT		10	/* wesewved cmds */
/* wesewved fow issuing intewnawwy fwamed scsi io cmds */
#define INTEWNAW_SCSIIO_CMDS_COUNT	3

#define MPI3_HIM_MASK			0xFFFFFFFF /* mask evewy bit*/

#define MPT3SAS_INVAWID_DEVICE_HANDWE	0xFFFF

#define MAX_CHAIN_EWEMT_SZ		16
#define DEFAUWT_NUM_FWCHAIN_EWEMTS	8

#define IO_UNIT_CONTWOW_SHUTDOWN_TIMEOUT 6
#define FW_IMG_HDW_WEAD_TIMEOUT	15

#define IOC_OPEWATIONAW_WAIT_COUNT	10

/*
 * NVMe defines
 */
#define	NVME_PWP_SIZE			8	/* PWP size */
#define	NVME_EWWOW_WESPONSE_SIZE	16	/* Max NVME Ewwow Wesponse */
#define NVME_TASK_ABOWT_MIN_TIMEOUT	6
#define NVME_TASK_ABOWT_MAX_TIMEOUT	60
#define NVME_TASK_MNGT_CUSTOM_MASK	(0x0010)
#define	NVME_PWP_PAGE_SIZE		4096	/* Page size */

stwuct mpt3sas_nvme_cmd {
	u8	wsvd[24];
	__we64	pwp1;
	__we64	pwp2;
};

/*
 * wogging fowmat
 */
#define ioc_eww(ioc, fmt, ...)						\
	pw_eww("%s: " fmt, (ioc)->name, ##__VA_AWGS__)
#define ioc_notice(ioc, fmt, ...)					\
	pw_notice("%s: " fmt, (ioc)->name, ##__VA_AWGS__)
#define ioc_wawn(ioc, fmt, ...)						\
	pw_wawn("%s: " fmt, (ioc)->name, ##__VA_AWGS__)
#define ioc_info(ioc, fmt, ...)						\
	pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__)

/*
 *  WawpDwive Specific Wog codes
 */

#define MPT2_WAWPDWIVE_WOGENTWY		(0x8002)
#define MPT2_WAWPDWIVE_WC_SSDT			(0x41)
#define MPT2_WAWPDWIVE_WC_SSDWW		(0x43)
#define MPT2_WAWPDWIVE_WC_SSDWF		(0x44)
#define MPT2_WAWPDWIVE_WC_BWMF			(0x4D)

/*
 * pew tawget pwivate data
 */
#define MPT_TAWGET_FWAGS_WAID_COMPONENT	0x01
#define MPT_TAWGET_FWAGS_VOWUME		0x02
#define MPT_TAWGET_FWAGS_DEWETED	0x04
#define MPT_TAWGET_FASTPATH_IO		0x08
#define MPT_TAWGET_FWAGS_PCIE_DEVICE	0x10

#define SAS2_PCI_DEVICE_B0_WEVISION	(0x01)
#define SAS3_PCI_DEVICE_C0_WEVISION	(0x02)

/* Atwas PCIe Switch Management Powt */
#define MPI26_ATWAS_PCIe_SWITCH_DEVID	(0x00B2)

/*
 * Intew HBA bwanding
 */
#define MPT2SAS_INTEW_WMS25JB080_BWANDING    \
	"Intew(W) Integwated WAID Moduwe WMS25JB080"
#define MPT2SAS_INTEW_WMS25JB040_BWANDING    \
	"Intew(W) Integwated WAID Moduwe WMS25JB040"
#define MPT2SAS_INTEW_WMS25KB080_BWANDING    \
	"Intew(W) Integwated WAID Moduwe WMS25KB080"
#define MPT2SAS_INTEW_WMS25KB040_BWANDING    \
	"Intew(W) Integwated WAID Moduwe WMS25KB040"
#define MPT2SAS_INTEW_WMS25WB040_BWANDING	\
	"Intew(W) Integwated WAID Moduwe WMS25WB040"
#define MPT2SAS_INTEW_WMS25WB080_BWANDING	\
	"Intew(W) Integwated WAID Moduwe WMS25WB080"
#define MPT2SAS_INTEW_WMS2WW080_BWANDING	\
	"Intew Integwated WAID Moduwe WMS2WW080"
#define MPT2SAS_INTEW_WMS2WW040_BWANDING	\
	"Intew Integwated WAID Moduwe WMS2WW040"
#define MPT2SAS_INTEW_WS25GB008_BWANDING       \
	"Intew(W) WAID Contwowwew WS25GB008"
#define MPT2SAS_INTEW_SSD910_BWANDING          \
	"Intew(W) SSD 910 Sewies"

#define MPT3SAS_INTEW_WMS3JC080_BWANDING       \
	"Intew(W) Integwated WAID Moduwe WMS3JC080"
#define MPT3SAS_INTEW_WS3GC008_BWANDING       \
	"Intew(W) WAID Contwowwew WS3GC008"
#define MPT3SAS_INTEW_WS3FC044_BWANDING       \
	"Intew(W) WAID Contwowwew WS3FC044"
#define MPT3SAS_INTEW_WS3UC080_BWANDING       \
	"Intew(W) WAID Contwowwew WS3UC080"

/*
 * Intew HBA SSDIDs
 */
#define MPT2SAS_INTEW_WMS25JB080_SSDID		0x3516
#define MPT2SAS_INTEW_WMS25JB040_SSDID		0x3517
#define MPT2SAS_INTEW_WMS25KB080_SSDID		0x3518
#define MPT2SAS_INTEW_WMS25KB040_SSDID		0x3519
#define MPT2SAS_INTEW_WMS25WB040_SSDID		0x351A
#define MPT2SAS_INTEW_WMS25WB080_SSDID		0x351B
#define MPT2SAS_INTEW_WMS2WW080_SSDID		0x350E
#define MPT2SAS_INTEW_WMS2WW040_SSDID		0x350F
#define MPT2SAS_INTEW_WS25GB008_SSDID		0x3000
#define MPT2SAS_INTEW_SSD910_SSDID		0x3700

#define MPT3SAS_INTEW_WMS3JC080_SSDID		0x3521
#define MPT3SAS_INTEW_WS3GC008_SSDID		0x3522
#define MPT3SAS_INTEW_WS3FC044_SSDID		0x3523
#define MPT3SAS_INTEW_WS3UC080_SSDID		0x3524

/*
 * Deww HBA bwanding
 */
#define MPT2SAS_DEWW_BWANDING_SIZE                 32

#define MPT2SAS_DEWW_6GBPS_SAS_HBA_BWANDING        "Deww 6Gbps SAS HBA"
#define MPT2SAS_DEWW_PEWC_H200_ADAPTEW_BWANDING    "Deww PEWC H200 Adaptew"
#define MPT2SAS_DEWW_PEWC_H200_INTEGWATED_BWANDING "Deww PEWC H200 Integwated"
#define MPT2SAS_DEWW_PEWC_H200_MODUWAW_BWANDING    "Deww PEWC H200 Moduwaw"
#define MPT2SAS_DEWW_PEWC_H200_EMBEDDED_BWANDING   "Deww PEWC H200 Embedded"
#define MPT2SAS_DEWW_PEWC_H200_BWANDING            "Deww PEWC H200"
#define MPT2SAS_DEWW_6GBPS_SAS_BWANDING            "Deww 6Gbps SAS"

#define MPT3SAS_DEWW_12G_HBA_BWANDING       \
	"Deww 12Gbps HBA"

/*
 * Deww HBA SSDIDs
 */
#define MPT2SAS_DEWW_6GBPS_SAS_HBA_SSDID	0x1F1C
#define MPT2SAS_DEWW_PEWC_H200_ADAPTEW_SSDID	0x1F1D
#define MPT2SAS_DEWW_PEWC_H200_INTEGWATED_SSDID	0x1F1E
#define MPT2SAS_DEWW_PEWC_H200_MODUWAW_SSDID	0x1F1F
#define MPT2SAS_DEWW_PEWC_H200_EMBEDDED_SSDID	0x1F20
#define MPT2SAS_DEWW_PEWC_H200_SSDID		0x1F21
#define MPT2SAS_DEWW_6GBPS_SAS_SSDID		0x1F22

#define MPT3SAS_DEWW_12G_HBA_SSDID		0x1F46

/*
 * Cisco HBA bwanding
 */
#define MPT3SAS_CISCO_12G_8E_HBA_BWANDING		\
	"Cisco 9300-8E 12G SAS HBA"
#define MPT3SAS_CISCO_12G_8I_HBA_BWANDING		\
	"Cisco 9300-8i 12G SAS HBA"
#define MPT3SAS_CISCO_12G_AVIWA_HBA_BWANDING	\
	"Cisco 12G Moduwaw SAS Pass thwough Contwowwew"
#define MPT3SAS_CISCO_12G_COWUSA_MEZZANINE_HBA_BWANDING		\
	"UCS C3X60 12G SAS Pass thwough Contwowwew"
/*
 * Cisco HBA SSSDIDs
 */
#define MPT3SAS_CISCO_12G_8E_HBA_SSDID  0x14C
#define MPT3SAS_CISCO_12G_8I_HBA_SSDID  0x154
#define MPT3SAS_CISCO_12G_AVIWA_HBA_SSDID  0x155
#define MPT3SAS_CISCO_12G_COWUSA_MEZZANINE_HBA_SSDID  0x156

/*
 * status bits fow ioc->diag_buffew_status
 */
#define MPT3_DIAG_BUFFEW_IS_WEGISTEWED	(0x01)
#define MPT3_DIAG_BUFFEW_IS_WEWEASED	(0x02)
#define MPT3_DIAG_BUFFEW_IS_DIAG_WESET	(0x04)
#define MPT3_DIAG_BUFFEW_IS_DWIVEW_AWWOCATED (0x08)
#define MPT3_DIAG_BUFFEW_IS_APP_OWNED (0x10)

/*
 * HP HBA bwanding
 */
#define MPT2SAS_HP_3PAW_SSVID                0x1590

#define MPT2SAS_HP_2_4_INTEWNAW_BWANDING	\
	"HP H220 Host Bus Adaptew"
#define MPT2SAS_HP_2_4_EXTEWNAW_BWANDING	\
	"HP H221 Host Bus Adaptew"
#define MPT2SAS_HP_1_4_INTEWNAW_1_4_EXTEWNAW_BWANDING	\
	"HP H222 Host Bus Adaptew"
#define MPT2SAS_HP_EMBEDDED_2_4_INTEWNAW_BWANDING	\
	"HP H220i Host Bus Adaptew"
#define MPT2SAS_HP_DAUGHTEW_2_4_INTEWNAW_BWANDING	\
	"HP H210i Host Bus Adaptew"

/*
 * HO HBA SSDIDs
 */
#define MPT2SAS_HP_2_4_INTEWNAW_SSDID			0x0041
#define MPT2SAS_HP_2_4_EXTEWNAW_SSDID			0x0042
#define MPT2SAS_HP_1_4_INTEWNAW_1_4_EXTEWNAW_SSDID	0x0043
#define MPT2SAS_HP_EMBEDDED_2_4_INTEWNAW_SSDID		0x0044
#define MPT2SAS_HP_DAUGHTEW_2_4_INTEWNAW_SSDID		0x0046

/*
 * Combined Wepwy Queue constants,
 * Thewe awe twewve Suppwementaw Wepwy Post Host Index Wegistews
 * and each wegistew is at offset 0x10 bytes fwom the pwevious one.
 */
#define MAX_COMBINED_MSIX_VECTOWS(gen35) ((gen35 == 1) ? 16 : 8)
#define MPT3_SUP_WEPWY_POST_HOST_INDEX_WEG_COUNT_G3	12
#define MPT3_SUP_WEPWY_POST_HOST_INDEX_WEG_COUNT_G35	16
#define MPT3_SUP_WEPWY_POST_HOST_INDEX_WEG_OFFSET	(0x10)
#define MPT3_MIN_IWQS					1

/* OEM Identifiews */
#define MFG10_OEM_ID_INVAWID                   (0x00000000)
#define MFG10_OEM_ID_DEWW                      (0x00000001)
#define MFG10_OEM_ID_FSC                       (0x00000002)
#define MFG10_OEM_ID_SUN                       (0x00000003)
#define MFG10_OEM_ID_IBM                       (0x00000004)

/* GENEWIC Fwags 0*/
#define MFG10_GF0_OCE_DISABWED                 (0x00000001)
#define MFG10_GF0_W1E_DWIVE_COUNT              (0x00000002)
#define MFG10_GF0_W10_DISPWAY                  (0x00000004)
#define MFG10_GF0_SSD_DATA_SCWUB_DISABWE       (0x00000008)
#define MFG10_GF0_SINGWE_DWIVE_W0              (0x00000010)

#define VIWTUAW_IO_FAIWED_WETWY			(0x32010081)

/* High IOPs definitions */
#define MPT3SAS_DEVICE_HIGH_IOPS_DEPTH		8
#define MPT3SAS_HIGH_IOPS_WEPWY_QUEUES		8
#define MPT3SAS_HIGH_IOPS_BATCH_COUNT		16
#define MPT3SAS_GEN35_MAX_MSIX_QUEUES		128
#define WDPQ_MAX_INDEX_IN_ONE_CHUNK		16

/* OEM Specific Fwags wiww come fwom OEM specific headew fiwes */
stwuct Mpi2ManufactuwingPage10_t {
	MPI2_CONFIG_PAGE_HEADEW	Headew;		/* 00h */
	U8	OEMIdentifiew;			/* 04h */
	U8	Wesewved1;			/* 05h */
	U16	Wesewved2;			/* 08h */
	U32	Wesewved3;			/* 0Ch */
	U32	GenewicFwags0;			/* 10h */
	U32	GenewicFwags1;			/* 14h */
	U32	Wesewved4;			/* 18h */
	U32	OEMSpecificFwags0;		/* 1Ch */
	U32	OEMSpecificFwags1;		/* 20h */
	U32	Wesewved5[18];			/* 24h - 60h*/
};


/* Miscewwaneous options */
stwuct Mpi2ManufactuwingPage11_t {
	MPI2_CONFIG_PAGE_HEADEW Headew;		/* 00h */
	__we32	Wesewved1;			/* 04h */
	u8	Wesewved2;			/* 08h */
	u8	EEDPTagMode;			/* 09h */
	u8	Wesewved3;			/* 0Ah */
	u8	Wesewved4;			/* 0Bh */
	__we32	Wesewved5[8];			/* 0Ch-2Ch */
	u16	AddwFwags2;			/* 2Ch */
	u8	AddwFwags3;			/* 2Eh */
	u8	Wesewved6;			/* 2Fh */
	__we32	Wesewved7[7];			/* 30h - 4Bh */
	u8	NVMeAbowtTO;			/* 4Ch */
	u8	NumPewDevEvents;		/* 4Dh */
	u8	HostTwaceBuffewDecwementSizeKB;	/* 4Eh */
	u8	HostTwaceBuffewFwags;		/* 4Fh */
	u16	HostTwaceBuffewMaxSizeKB;	/* 50h */
	u16	HostTwaceBuffewMinSizeKB;	/* 52h */
	u8	CoweDumpTOSec;			/* 54h */
	u8	TimeSyncIntewvaw;		/* 55h */
	u16	Wesewved9;			/* 56h */
	__we32	Wesewved10;			/* 58h */
};

/**
 * stwuct MPT3SAS_TAWGET - stawget pwivate hostdata
 * @stawget: stawget object
 * @sas_addwess: tawget sas addwess
 * @waid_device: waid_device pointew to access vowume data
 * @handwe: device handwe
 * @num_wuns: numbew wuns
 * @fwags: MPT_TAWGET_FWAGS_XXX fwags
 * @deweted: tawget fwaged fow dewetion
 * @tm_busy: tawget is busy with TM wequest.
 * @powt: hba powt entwy containing tawget's powt numbew info
 * @sas_dev: The sas_device associated with this tawget
 * @pcie_dev: The pcie device associated with this tawget
 */
stwuct MPT3SAS_TAWGET {
	stwuct scsi_tawget *stawget;
	u64	sas_addwess;
	stwuct _waid_device *waid_device;
	u16	handwe;
	int	num_wuns;
	u32	fwags;
	u8	deweted;
	u8	tm_busy;
	stwuct hba_powt *powt;
	stwuct _sas_device *sas_dev;
	stwuct _pcie_device *pcie_dev;
};


/*
 * pew device pwivate data
 */
#define MPT_DEVICE_FWAGS_INIT		0x01

#define MFG_PAGE10_HIDE_SSDS_MASK	(0x00000003)
#define MFG_PAGE10_HIDE_AWW_DISKS	(0x00)
#define MFG_PAGE10_EXPOSE_AWW_DISKS	(0x01)
#define MFG_PAGE10_HIDE_IF_VOW_PWESENT	(0x02)

/**
 * stwuct MPT3SAS_DEVICE - sdev pwivate hostdata
 * @sas_tawget: stawget pwivate hostdata
 * @wun: wun numbew
 * @fwags: MPT_DEVICE_XXX fwags
 * @configuwed_wun: wun is configuwed
 * @bwock: device is in SDEV_BWOCK state
 * @tww_snoop_check: fwag used in detewmining whethew to disabwe TWW
 * @eedp_enabwe: eedp suppowt enabwe bit
 * @eedp_type: 0(type_1), 1(type_2), 2(type_3)
 * @eedp_bwock_wength: bwock size
 * @ata_command_pending: SATW passthwough outstanding fow device
 */
stwuct MPT3SAS_DEVICE {
	stwuct MPT3SAS_TAWGET *sas_tawget;
	unsigned int	wun;
	u32	fwags;
	u8	configuwed_wun;
	u8	bwock;
	u8	tww_snoop_check;
	u8	ignowe_deway_wemove;
	/* Iopwiowity Command Handwing */
	u8	ncq_pwio_enabwe;
	/*
	 * Bug wowkawound fow SATW handwing: the mpt2/3sas fiwmwawe
	 * doesn't wetuwn BUSY ow TASK_SET_FUWW fow subsequent
	 * commands whiwe a SATW pass thwough is in opewation as the
	 * spec wequiwes, it simpwy does nothing with them untiw the
	 * pass thwough compwetes, causing them possibwy to timeout if
	 * the passthwough is a wong executing command (wike fowmat ow
	 * secuwe ewase).  This vawiabwe awwows us to do the wight
	 * thing whiwe a SATW command is pending.
	 */
	unsigned wong ata_command_pending;

};

#define MPT3_CMD_NOT_USED	0x8000	/* fwee */
#define MPT3_CMD_COMPWETE	0x0001	/* compweted */
#define MPT3_CMD_PENDING	0x0002	/* pending */
#define MPT3_CMD_WEPWY_VAWID	0x0004	/* wepwy is vawid */
#define MPT3_CMD_WESET		0x0008	/* host weset dwopped the command */
#define MPT3_CMD_COMPWETE_ASYNC 0x0010  /* tewws whethew cmd compwetes in same thwead ow not */

/**
 * stwuct _intewnaw_cmd - intewnaw commands stwuct
 * @mutex: mutex
 * @done: compwetion
 * @wepwy: wepwy message pointew
 * @sense: sense data
 * @status: MPT3_CMD_XXX status
 * @smid: system message id
 */
stwuct _intewnaw_cmd {
	stwuct mutex mutex;
	stwuct compwetion done;
	void	*wepwy;
	void	*sense;
	u16	status;
	u16	smid;
};



/**
 * stwuct _sas_device - attached device infowmation
 * @wist: sas device wist
 * @stawget: stawget object
 * @sas_addwess: device sas addwess
 * @device_name: wetwieved fwom the SAS IDENTIFY fwame.
 * @handwe: device handwe
 * @sas_addwess_pawent: sas addwess of pawent expandew ow sas host
 * @encwosuwe_handwe: encwosuwe handwe
 * @encwosuwe_wogicaw_id: encwosuwe wogicaw identifiew
 * @vowume_handwe: vowume handwe (vawid when hidden waid membew)
 * @vowume_wwid: vowume unique identifiew
 * @device_info: bitfiewd pwovides detaiwed info about the device
 * @id: tawget id
 * @channew: tawget channew
 * @swot: numbew numbew
 * @phy: phy identifiew pwovided in sas device page 0
 * @wesponding: used in _scsih_sas_device_mawk_wesponding
 * @fast_path: fast path featuwe enabwe bit
 * @pfa_wed_on: fwag fow PFA WED status
 * @pend_sas_wphy_add: fwag to check if device is in sas_wphy_add()
 *	addition woutine.
 * @chassis_swot: chassis swot
 * @is_chassis_swot_vawid: chassis swot vawid ow not
 * @powt: hba powt entwy containing device's powt numbew info
 * @wphy: device's sas_wphy addwess used to identify this device stwuctuwe in
 *	tawget_awwoc cawwback function
 */
stwuct _sas_device {
	stwuct wist_head wist;
	stwuct scsi_tawget *stawget;
	u64	sas_addwess;
	u64	device_name;
	u16	handwe;
	u64	sas_addwess_pawent;
	u16	encwosuwe_handwe;
	u64	encwosuwe_wogicaw_id;
	u16	vowume_handwe;
	u64	vowume_wwid;
	u32	device_info;
	int	id;
	int	channew;
	u16	swot;
	u8	phy;
	u8	wesponding;
	u8	fast_path;
	u8	pfa_wed_on;
	u8	pend_sas_wphy_add;
	u8	encwosuwe_wevew;
	u8	chassis_swot;
	u8	is_chassis_swot_vawid;
	u8	connectow_name[5];
	stwuct kwef wefcount;
	u8	powt_type;
	stwuct hba_powt *powt;
	stwuct sas_wphy *wphy;
};

static inwine void sas_device_get(stwuct _sas_device *s)
{
	kwef_get(&s->wefcount);
}

static inwine void sas_device_fwee(stwuct kwef *w)
{
	kfwee(containew_of(w, stwuct _sas_device, wefcount));
}

static inwine void sas_device_put(stwuct _sas_device *s)
{
	kwef_put(&s->wefcount, sas_device_fwee);
}

/*
 * stwuct _pcie_device - attached PCIe device infowmation
 * @wist: pcie device wist
 * @stawget: stawget object
 * @wwid: device WWID
 * @handwe: device handwe
 * @device_info: bitfiewd pwovides detaiwed info about the device
 * @id: tawget id
 * @channew: tawget channew
 * @swot: swot numbew
 * @powt_num: powt numbew
 * @wesponding: used in _scsih_pcie_device_mawk_wesponding
 * @fast_path: fast path featuwe enabwe bit
 * @nvme_mdts: MaximumDataTwansfewSize fwom PCIe Device Page 2 fow
 *		NVMe device onwy
 * @encwosuwe_handwe: encwosuwe handwe
 * @encwosuwe_wogicaw_id: encwosuwe wogicaw identifiew
 * @encwosuwe_wevew: The wevew of device's encwosuwe fwom the contwowwew
 * @connectow_name: ASCII vawue of the Connectow's name
 * @sewiaw_numbew: pointew of sewiaw numbew stwing awwocated wuntime
 * @access_status: Device's Access Status
 * @shutdown_watency: NVMe device's WTD3 Entwy Watency
 * @wefcount: wefewence count fow dewetion
 */
stwuct _pcie_device {
	stwuct wist_head wist;
	stwuct scsi_tawget *stawget;
	u64	wwid;
	u16	handwe;
	u32	device_info;
	int	id;
	int	channew;
	u16	swot;
	u8	powt_num;
	u8	wesponding;
	u8	fast_path;
	u32	nvme_mdts;
	u16	encwosuwe_handwe;
	u64	encwosuwe_wogicaw_id;
	u8	encwosuwe_wevew;
	u8	connectow_name[4];
	u8	*sewiaw_numbew;
	u8	weset_timeout;
	u8	access_status;
	u16	shutdown_watency;
	stwuct kwef wefcount;
};
/**
 * pcie_device_get - Incwement the pcie device wefewence count
 *
 * @p: pcie_device object
 *
 * When evew this function cawwed it wiww incwement the
 * wefewence count of the pcie device fow which this function cawwed.
 *
 */
static inwine void pcie_device_get(stwuct _pcie_device *p)
{
	kwef_get(&p->wefcount);
}

/**
 * pcie_device_fwee - Wewease the pcie device object
 * @w - kwef object
 *
 * Fwee's the pcie device object. It wiww be cawwed when wefewence count
 * weaches to zewo.
 */
static inwine void pcie_device_fwee(stwuct kwef *w)
{
	kfwee(containew_of(w, stwuct _pcie_device, wefcount));
}

/**
 * pcie_device_put - Decwement the pcie device wefewence count
 *
 * @p: pcie_device object
 *
 * When evew this function cawwed it wiww decwement the
 * wefewence count of the pcie device fow which this function cawwed.
 *
 * When wefewnce count weaches to Zewo, this wiww caww pcie_device_fwee to the
 * pcie_device object.
 */
static inwine void pcie_device_put(stwuct _pcie_device *p)
{
	kwef_put(&p->wefcount, pcie_device_fwee);
}
/**
 * stwuct _waid_device - waid vowume wink wist
 * @wist: sas device wist
 * @stawget: stawget object
 * @sdev: scsi device stwuct (vowumes awe singwe wun)
 * @wwid: unique identifiew fow the vowume
 * @handwe: device handwe
 * @bwock_size: Bwock size of the vowume
 * @id: tawget id
 * @channew: tawget channew
 * @vowume_type: the waid wevew
 * @device_info: bitfiewd pwovides detaiwed info about the hidden components
 * @num_pds: numbew of hidden waid components
 * @wesponding: used in _scsih_waid_device_mawk_wesponding
 * @pewcent_compwete: wesync pewcent compwete
 * @diwect_io_enabwed: Whethew diwect io to PDs awe awwowed ow not
 * @stwipe_exponent: X whewe 2powX is the stwipe sz in bwocks
 * @bwock_exponent: X whewe 2powX is the bwock sz in bytes
 * @max_wba: Maximum numbew of WBA in the vowume
 * @stwipe_sz: Stwipe Size of the vowume
 * @device_info: Device info of the vowume membew disk
 * @pd_handwe: Awway of handwes of the physicaw dwives fow diwect I/O in we16
 */
#define MPT_MAX_WAWPDWIVE_PDS		8
stwuct _waid_device {
	stwuct wist_head wist;
	stwuct scsi_tawget *stawget;
	stwuct scsi_device *sdev;
	u64	wwid;
	u16	handwe;
	u16	bwock_sz;
	int	id;
	int	channew;
	u8	vowume_type;
	u8	num_pds;
	u8	wesponding;
	u8	pewcent_compwete;
	u8	diwect_io_enabwed;
	u8	stwipe_exponent;
	u8	bwock_exponent;
	u64	max_wba;
	u32	stwipe_sz;
	u32	device_info;
	u16	pd_handwe[MPT_MAX_WAWPDWIVE_PDS];
};

/**
 * stwuct _boot_device - boot device info
 *
 * @channew: sas, waid, ow pcie channew
 * @device: howds pointew fow stwuct _sas_device, stwuct _waid_device ow
 *     stwuct _pcie_device
 */
stwuct _boot_device {
	int channew;
	void *device;
};

/**
 * stwuct _sas_powt - wide/nawwow sas powt infowmation
 * @powt_wist: wist of powts bewonging to expandew
 * @num_phys: numbew of phys bewonging to this powt
 * @wemote_identify: attached device identification
 * @wphy: sas twanspowt wphy object
 * @powt: sas twanspowt wide/nawwow powt object
 * @hba_powt: hba powt entwy containing powt's powt numbew info
 * @phy_wist: _sas_phy wist objects bewonging to this powt
 */
stwuct _sas_powt {
	stwuct wist_head powt_wist;
	u8	num_phys;
	stwuct sas_identify wemote_identify;
	stwuct sas_wphy *wphy;
	stwuct sas_powt *powt;
	stwuct hba_powt *hba_powt;
	stwuct wist_head phy_wist;
};

/**
 * stwuct _sas_phy - phy infowmation
 * @powt_sibwings: wist of phys bewonging to a powt
 * @identify: phy identification
 * @wemote_identify: attached device identification
 * @phy: sas twanspowt phy object
 * @phy_id: unique phy id
 * @handwe: device handwe fow this phy
 * @attached_handwe: device handwe fow attached device
 * @phy_bewongs_to_powt: powt has been cweated fow this phy
 * @powt: hba powt entwy containing powt numbew info
 */
stwuct _sas_phy {
	stwuct wist_head powt_sibwings;
	stwuct sas_identify identify;
	stwuct sas_identify wemote_identify;
	stwuct sas_phy *phy;
	u8	phy_id;
	u16	handwe;
	u16	attached_handwe;
	u8	phy_bewongs_to_powt;
	u8	hba_vphy;
	stwuct hba_powt *powt;
};

/**
 * stwuct _sas_node - sas_host/expandew infowmation
 * @wist: wist of expandews
 * @pawent_dev: pawent device cwass
 * @num_phys: numbew phys bewonging to this sas_host/expandew
 * @sas_addwess: sas addwess of this sas_host/expandew
 * @handwe: handwe fow this sas_host/expandew
 * @sas_addwess_pawent: sas addwess of pawent expandew ow sas host
 * @encwosuwe_handwe: handwe fow this a membew of an encwosuwe
 * @device_info: bitwise defining capabiwities of this sas_host/expandew
 * @wesponding: used in _scsih_expandew_device_mawk_wesponding
 * @nw_phys_awwocated: Awwocated memowy fow this many count phys
 * @phy: a wist of phys that make up this sas_host/expandew
 * @sas_powt_wist: wist of powts attached to this sas_host/expandew
 * @powt: hba powt entwy containing node's powt numbew info
 * @wphy: sas_wphy object of this expandew
 */
stwuct _sas_node {
	stwuct wist_head wist;
	stwuct device *pawent_dev;
	u8	num_phys;
	u64	sas_addwess;
	u16	handwe;
	u64	sas_addwess_pawent;
	u16	encwosuwe_handwe;
	u64	encwosuwe_wogicaw_id;
	u8	wesponding;
	u8	nw_phys_awwocated;
	stwuct hba_powt *powt;
	stwuct	_sas_phy *phy;
	stwuct wist_head sas_powt_wist;
	stwuct sas_wphy *wphy;
};

/**
 * stwuct _encwosuwe_node - encwosuwe infowmation
 * @wist: wist of encwosuwes
 * @pg0: encwosuwe pg0;
 */
stwuct _encwosuwe_node {
	stwuct wist_head wist;
	Mpi2SasEncwosuwePage0_t pg0;
};

/**
 * enum weset_type - weset state
 * @FOWCE_BIG_HAMMEW: issue diagnostic weset
 * @SOFT_WESET: issue message_unit_weset, if faiws to to big hammew
 */
enum weset_type {
	FOWCE_BIG_HAMMEW,
	SOFT_WESET,
};

/**
 * stwuct pcie_sg_wist - PCIe SGW buffew (contiguous pew I/O)
 * @pcie_sgw: PCIe native SGW fow NVMe devices
 * @pcie_sgw_dma: physicaw addwess
 */
stwuct pcie_sg_wist {
	void            *pcie_sgw;
	dma_addw_t      pcie_sgw_dma;
};

/**
 * stwuct chain_twackew - fiwmwawe chain twackew
 * @chain_buffew: chain buffew
 * @chain_buffew_dma: physicaw addwess
 * @twackew_wist: wist of fwee wequest (ioc->fwee_chain_wist)
 */
stwuct chain_twackew {
	void *chain_buffew;
	dma_addw_t chain_buffew_dma;
};

stwuct chain_wookup {
	stwuct chain_twackew *chains_pew_smid;
	atomic_t	chain_offset;
};

/**
 * stwuct scsiio_twackew - scsi mf wequest twackew
 * @smid: system message id
 * @cb_idx: cawwback index
 * @diwect_io: To indicate whethew I/O is diwect (WAWPDWIVE)
 * @chain_wist: wist of associated fiwmwawe chain twackew
 * @msix_io: IO's msix
 */
stwuct scsiio_twackew {
	u16	smid;
	stwuct scsi_cmnd *scmd;
	u8	cb_idx;
	u8	diwect_io;
	stwuct pcie_sg_wist pcie_sg_wist;
	stwuct wist_head chain_wist;
	u16     msix_io;
};

/**
 * stwuct wequest_twackew - fiwmwawe wequest twackew
 * @smid: system message id
 * @cb_idx: cawwback index
 * @twackew_wist: wist of fwee wequest (ioc->fwee_wist)
 */
stwuct wequest_twackew {
	u16	smid;
	u8	cb_idx;
	stwuct wist_head twackew_wist;
};

/**
 * stwuct _tw_wist - tawget weset wist
 * @handwe: device handwe
 * @state: state machine
 */
stwuct _tw_wist {
	stwuct wist_head wist;
	u16	handwe;
	u16	state;
};

/**
 * stwuct _sc_wist - dewayed SAS_IO_UNIT_CONTWOW message wist
 * @handwe: device handwe
 */
stwuct _sc_wist {
	stwuct wist_head wist;
	u16     handwe;
};

/**
 * stwuct _event_ack_wist - dewayed event acknowwedgment wist
 * @Event: Event ID
 * @EventContext: used to twack the event uniquewy
 */
stwuct _event_ack_wist {
	stwuct wist_head wist;
	U16     Event;
	U32     EventContext;
};

/**
 * stwuct adaptew_wepwy_queue - the wepwy queue stwuct
 * @ioc: pew adaptew object
 * @msix_index: msix index into vectow tabwe
 * @vectow: iwq vectow
 * @wepwy_post_host_index: head index in the poow whewe FW compwetes IO
 * @wepwy_post_fwee: wepwy post base viwt addwess
 * @name: the name wegistewed to wequest_iwq()
 * @busy: isw is activewy pwocessing wepwies on anothew cpu
 * @os_iwq: iwq numbew
 * @iwqpoww: iwq_poww object
 * @iwq_poww_scheduwed: Tewws whethew iwq poww is scheduwed ow not
 * @is_iouwing_poww_q: Tewws whethew wepwy queues is assigned
 *			to io uwing poww queues ow not
 * @wist: this wist
*/
stwuct adaptew_wepwy_queue {
	stwuct MPT3SAS_ADAPTEW	*ioc;
	u8			msix_index;
	u32			wepwy_post_host_index;
	Mpi2WepwyDescwiptowsUnion_t *wepwy_post_fwee;
	chaw			name[MPT_NAME_WENGTH];
	atomic_t		busy;
	u32			os_iwq;
	stwuct iwq_poww         iwqpoww;
	boow			iwq_poww_scheduwed;
	boow			iwq_wine_enabwe;
	boow			is_iouwing_poww_q;
	stwuct wist_head	wist;
};

/**
 * stwuct io_uwing_poww_queue - the io uwing poww queue stwuctuwe
 * @busy: Tewws whethew io uwing poww queue is busy ow not
 * @pause: Tewws whethew IOs awe paused on io uwing poww queue ow not
 * @wepwy_q: wepwy queue mapped fow io uwing poww queue
 */
stwuct io_uwing_poww_queue {
	atomic_t	busy;
	atomic_t	pause;
	stwuct adaptew_wepwy_queue *wepwy_q;
};

typedef void (*MPT_ADD_SGE)(void *paddw, u32 fwags_wength, dma_addw_t dma_addw);

/* SAS3.0 suppowt */
typedef int (*MPT_BUIWD_SG_SCMD)(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct scsi_cmnd *scmd, u16 smid, stwuct _pcie_device *pcie_device);
typedef void (*MPT_BUIWD_SG)(stwuct MPT3SAS_ADAPTEW *ioc, void *psge,
		dma_addw_t data_out_dma, size_t data_out_sz,
		dma_addw_t data_in_dma, size_t data_in_sz);
typedef void (*MPT_BUIWD_ZEWO_WEN_SGE)(stwuct MPT3SAS_ADAPTEW *ioc,
		void *paddw);

/* SAS3.5 suppowt */
typedef void (*NVME_BUIWD_PWP)(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid,
	Mpi26NVMeEncapsuwatedWequest_t *nvme_encap_wequest,
	dma_addw_t data_out_dma, size_t data_out_sz, dma_addw_t data_in_dma,
	size_t data_in_sz);

/* To suppowt atomic and non atomic descwiptows*/
typedef void (*PUT_SMID_IO_FP_HIP) (stwuct MPT3SAS_ADAPTEW *ioc, u16 smid,
	u16 funcdep);
typedef void (*PUT_SMID_DEFAUWT) (stwuct MPT3SAS_ADAPTEW *ioc, u16 smid);
typedef u32 (*BASE_WEAD_WEG) (const void __iomem *addw);
/*
 * To get high iops wepwy queue's msix index when high iops mode is enabwed
 * ewse get the msix index of genewaw wepwy queues.
 */
typedef u8 (*GET_MSIX_INDEX) (stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct scsi_cmnd *scmd);

/* IOC Facts and Powt Facts convewted fwom wittwe endian to cpu */
union mpi3_vewsion_union {
	MPI2_VEWSION_STWUCT		Stwuct;
	u32				Wowd;
};

stwuct mpt3sas_facts {
	u16			MsgVewsion;
	u16			HeadewVewsion;
	u8			IOCNumbew;
	u8			VP_ID;
	u8			VF_ID;
	u16			IOCExceptions;
	u16			IOCStatus;
	u32			IOCWogInfo;
	u8			MaxChainDepth;
	u8			WhoInit;
	u8			NumbewOfPowts;
	u8			MaxMSIxVectows;
	u16			WequestCwedit;
	u16			PwoductID;
	u32			IOCCapabiwities;
	union mpi3_vewsion_union	FWVewsion;
	u16			IOCWequestFwameSize;
	u16			IOCMaxChainSegmentSize;
	u16			MaxInitiatows;
	u16			MaxTawgets;
	u16			MaxSasExpandews;
	u16			MaxEncwosuwes;
	u16			PwotocowFwags;
	u16			HighPwiowityCwedit;
	u16			MaxWepwyDescwiptowPostQueueDepth;
	u8			WepwyFwameSize;
	u8			MaxVowumes;
	u16			MaxDevHandwe;
	u16			MaxPewsistentEntwies;
	u16			MinDevHandwe;
	u8			CuwwentHostPageSize;
};

stwuct mpt3sas_powt_facts {
	u8			PowtNumbew;
	u8			VP_ID;
	u8			VF_ID;
	u8			PowtType;
	u16			MaxPostedCmdBuffews;
};

stwuct wepwy_post_stwuct {
	Mpi2WepwyDescwiptowsUnion_t	*wepwy_post_fwee;
	dma_addw_t			wepwy_post_fwee_dma;
};

/**
 * stwuct viwtuaw_phy - vSES phy stwuctuwe
 * sas_addwess: SAS Addwess of vSES device
 * phy_mask: vSES device's phy numbew
 * fwags: fwags used to manage this stwuctuwe
 */
stwuct viwtuaw_phy {
	stwuct	wist_head wist;
	u64	sas_addwess;
	u32	phy_mask;
	u8	fwags;
};

#define MPT_VPHY_FWAG_DIWTY_PHY	0x01

/**
 * stwuct hba_powt - Saves each HBA's Wide/Nawwow powt info
 * @sas_addwess: sas addwess of this wide/nawwow powt's attached device
 * @phy_mask: HBA PHY's bewonging to this powt
 * @powt_id: powt numbew
 * @fwags: hba powt fwags
 * @vphys_mask : mask of vSES devices Phy numbew
 * @vphys_wist : wist containing vSES device stwuctuwes
 */
stwuct hba_powt {
	stwuct wist_head wist;
	u64	sas_addwess;
	u32	phy_mask;
	u8      powt_id;
	u8	fwags;
	u32	vphys_mask;
	stwuct wist_head vphys_wist;
};

/* hba powt fwags */
#define HBA_POWT_FWAG_DIWTY_POWT       0x01
#define HBA_POWT_FWAG_NEW_POWT         0x02

#define MUWTIPATH_DISABWED_POWT_ID     0xFF

/**
 * stwuct htb_wew_quewy - diagnostic buffew wewease weason
 * @unique_id - unique id associated with this buffew.
 * @buffew_wew_condition - Wewease condition ioctw/sysfs/weset
 * @wesewved
 * @twiggew_type - Mastew/Event/scsi/MPI
 * @twiggew_info_dwowds - Data Cowwespondig to twiggew type
 */
stwuct htb_wew_quewy {
	u16	buffew_wew_condition;
	u16	wesewved;
	u32	twiggew_type;
	u32	twiggew_info_dwowds[2];
};

/* Buffew_wew_condition bit fiewds */

/* Bit 0 - Diag Buffew not Weweased */
#define MPT3_DIAG_BUFFEW_NOT_WEWEASED	(0x00)
/* Bit 0 - Diag Buffew Weweased */
#define MPT3_DIAG_BUFFEW_WEWEASED	(0x01)

/*
 * Bit 1 - Diag Buffew Weweased by IOCTW,
 * This bit is vawid onwy if Bit 0 is one
 */
#define MPT3_DIAG_BUFFEW_WEW_IOCTW	(0x02 | MPT3_DIAG_BUFFEW_WEWEASED)

/*
 * Bit 2 - Diag Buffew Weweased by Twiggew,
 * This bit is vawid onwy if Bit 0 is one
 */
#define MPT3_DIAG_BUFFEW_WEW_TWIGGEW	(0x04 | MPT3_DIAG_BUFFEW_WEWEASED)

/*
 * Bit 3 - Diag Buffew Weweased by SysFs,
 * This bit is vawid onwy if Bit 0 is one
 */
#define MPT3_DIAG_BUFFEW_WEW_SYSFS	(0x08 | MPT3_DIAG_BUFFEW_WEWEASED)

/* DIAG WESET Mastew twiggew fwags */
#define MPT_DIAG_WESET_ISSUED_BY_DWIVEW 0x00000000
#define MPT_DIAG_WESET_ISSUED_BY_USEW	0x00000001

typedef void (*MPT3SAS_FWUSH_WUNNING_CMDS)(stwuct MPT3SAS_ADAPTEW *ioc);
/**
 * stwuct MPT3SAS_ADAPTEW - pew adaptew stwuct
 * @wist: ioc_wist
 * @shost: shost object
 * @id: unique adaptew id
 * @cpu_count: numbew onwine cpus
 * @name: genewic ioc stwing
 * @tmp_stwing: tmp stwing used fow wogging
 * @pdev: pci pdev object
 * @pio_chip: physicaw io wegistew space
 * @chip: memowy mapped wegistew space
 * @chip_phys: physicaw addwss pwiow to mapping
 * @wogging_wevew: see mpt3sas_debug.h
 * @fwfauwt_debug: debuging FW timeouts
 * @iw_fiwmwawe: IW fiwmwawe pwesent
 * @baws: bitmask of BAW's that must be configuwed
 * @mask_intewwupts: ignowe intewwupt
 * @pci_access_mutex: Mutex to synchwonize ioctw, sysfs show path and
 *			pci wesouwce handwing
 * @fauwt_weset_wowk_q_name: fw fauwt wowk queue
 * @fauwt_weset_wowk_q: ""
 * @fauwt_weset_wowk: ""
 * @fiwmwawe_event_name: fw event wowk queue
 * @fiwmwawe_event_thwead: ""
 * @fw_event_wock:
 * @fw_event_wist: wist of fw events
 * @cuwwent_evet: cuwwent pwocessing fiwmwawe event
 * @fw_event_cweanup: set to one whiwe cweaning up the fw events
 * @aen_event_wead_fwag: event wog was wead
 * @bwoadcast_aen_busy: bwoadcast aen waiting to be sewviced
 * @shost_wecovewy: host weset in pwogwess
 * @ioc_weset_in_pwogwess_wock:
 * @ioc_wink_weset_in_pwogwess: phy/hawd weset in pwogwess
 * @ignowe_woginfos: ignowe woginfos duwing task management
 * @wemove_host: fwag fow when dwivew unwoads, to avoid sending dev wesets
 * @pci_ewwow_wecovewy: fwag to pwevent ioc access untiw swot weset compwetes
 * @wait_fow_discovewy_to_compwete: fwag set at dwivew woad time when
 *                                               waiting on wepowting devices
 * @is_dwivew_woading: fwag set at dwivew woad time
 * @powt_enabwe_faiwed: fwag set when powt enabwe has faiwed
 * @stawt_scan: fwag set fwom scan_stawt cawwback, cweawed fwom _mpt3sas_fw_wowk
 * @stawt_scan_faiwed: means powt enabwe faiwed, wetuwn's the ioc_status
 * @msix_enabwe: fwag indicating msix is enabwed
 * @msix_vectow_count: numbew msix vectows
 * @cpu_msix_tabwe: tabwe fow mapping cpus to msix index
 * @cpu_msix_tabwe_sz: tabwe size
 * @totaw_io_cnt: Gives totaw IO count, used to woad bawance the intewwupts
 * @ioc_cowedump_woop: wiww have non-zewo vawue when FW is in CoweDump state
 * @timestamp_update_count: Countew to fiwe timeSync command
 * time_sync_intewvaw: Time sync intewvaw wead fwom man page 11
 * @high_iops_outstanding: used to woad bawance the intewwupts
 *				within high iops wepwy queues
 * @msix_woad_bawance: Enabwes woad bawancing of intewwupts acwoss
 * the muwtipwe MSIXs
 * @scheduwe_dead_ioc_fwush_wunning_cmds: cawwback to fwush pending commands
 * @thwesh_howd: Max numbew of wepwy descwiptows pwocessed
 *				befowe updating Host Index
 * @iopoww_q_stawt_index: stawting index of io uwing poww queues
 *				in wepwy queue wist
 * @dwv_intewnaw_fwags: Bit map intewnaw to dwivew
 * @dwv_suppowt_bitmap: dwivew's suppowted featuwe bit map
 * @use_32bit_dma: Fwag to use 32 bit consistent dma mask
 * @scsi_io_cb_idx: shost genewated commands
 * @tm_cb_idx: task management commands
 * @scsih_cb_idx: scsih intewnaw commands
 * @twanspowt_cb_idx: twanspowt intewnaw commands
 * @ctw_cb_idx: cwt intewnaw commands
 * @base_cb_idx: base intewnaw commands
 * @config_cb_idx: base intewnaw commands
 * @tm_tw_cb_idx : device wemovaw tawget weset handshake
 * @tm_tw_vowume_cb_idx : vowume wemovaw tawget weset
 * @base_cmds:
 * @twanspowt_cmds:
 * @scsih_cmds:
 * @tm_cmds:
 * @ctw_cmds:
 * @config_cmds:
 * @base_add_sg_singwe: handwew fow eithew 32/64 bit sgw's
 * @event_type: bits indicating which events to wog
 * @event_context: unique id fow each wogged event
 * @event_wog: event wog pointew
 * @event_masks: events that awe masked
 * @max_shutdown_watency: timeout vawue fow NVMe shutdown opewation,
 *			which is equaw that NVMe dwive's WTD3 Entwy Watency
 *			which has wepowted maximum WTD3 Entwy Watency vawue
 *			among attached NVMe dwives.
 * @facts: static facts data
 * @pwev_fw_facts: pwevious fw facts data
 * @pfacts: static powt facts data
 * @manu_pg0: static manufactuwing page 0
 * @manu_pg10: static manufactuwing page 10
 * @manu_pg11: static manufactuwing page 11
 * @bios_pg2: static bios page 2
 * @bios_pg3: static bios page 3
 * @ioc_pg8: static ioc page 8
 * @iounit_pg0: static iounit page 0
 * @iounit_pg1: static iounit page 1
 * @sas_hba: sas host object
 * @sas_expandew_wist: expandew object wist
 * @encwosuwe_wist: encwosuwe object wist
 * @sas_node_wock:
 * @sas_device_wist: sas device object wist
 * @sas_device_init_wist: sas device object wist (used onwy at init time)
 * @sas_device_wock:
 * @pcie_device_wist: pcie device object wist
 * @pcie_device_init_wist: pcie device object wist (used onwy at init time)
 * @pcie_device_wock:
 * @io_missing_deway: time fow IO compweted by fw when PDW enabwed
 * @device_missing_deway: time fow device missing by fw when PDW enabwed
 * @sas_id : used fow setting vowume tawget IDs
 * @pcie_tawget_id: used fow setting pcie tawget IDs
 * @bwocking_handwes: bitmask used to identify which devices need bwocking
 * @pd_handwes : bitmask fow PD handwes
 * @pd_handwes_sz : size of pd_handwe bitmask
 * @config_page_sz: config page size
 * @config_page: wesewve memowy fow config page paywoad
 * @config_page_dma:
 * @hba_queue_depth: hba wequest queue depth
 * @sge_size: sg ewement size fow eithew 32/64 bit
 * @scsiio_depth: SCSI_IO queue depth
 * @wequest_sz: pew wequest fwame size
 * @wequest: poow of wequest fwames
 * @wequest_dma:
 * @wequest_dma_sz:
 * @scsi_wookup: fiwmwawe wequest twackew wist
 * @scsi_wookup_wock:
 * @fwee_wist: fwee wist of wequest
 * @pending_io_count:
 * @weset_wq:
 * @chain: poow of chains
 * @chain_dma:
 * @max_sges_in_main_message: numbew sg ewements in main message
 * @max_sges_in_chain_message: numbew sg ewements pew chain
 * @chains_needed_pew_io: max chains pew io
 * @chain_depth: totaw chains awwocated
 * @chain_segment_sz: gives the max numbew of
 *			SGEs accommodate on singwe chain buffew
 * @hi_pwiowity_smid:
 * @hi_pwiowity:
 * @hi_pwiowity_dma:
 * @hi_pwiowity_depth:
 * @hpw_wookup:
 * @hpw_fwee_wist:
 * @intewnaw_smid:
 * @intewnaw:
 * @intewnaw_dma:
 * @intewnaw_depth:
 * @intewnaw_wookup:
 * @intewnaw_fwee_wist:
 * @sense: poow of sense
 * @sense_dma:
 * @sense_dma_poow:
 * @wepwy_depth: hba wepwy queue depth:
 * @wepwy_sz: pew wepwy fwame size:
 * @wepwy: poow of wepwys:
 * @wepwy_dma:
 * @wepwy_dma_poow:
 * @wepwy_fwee_queue_depth: wepwy fwee depth
 * @wepwy_fwee: poow fow wepwy fwee queue (32 bit addw)
 * @wepwy_fwee_dma:
 * @wepwy_fwee_dma_poow:
 * @wepwy_fwee_host_index: taiw index in poow to insewt fwee wepwys
 * @wepwy_post_queue_depth: wepwy post queue depth
 * @wepwy_post_stwuct: stwuct fow wepwy_post_fwee physicaw & viwt addwess
 * @wdpq_awway_capabwe: FW suppowts muwtipwe wepwy queue addwesses in ioc_init
 * @wdpq_awway_enabwe: wdpq_awway suppowt is enabwed in the dwivew
 * @wdpq_awway_enabwe_assigned: this ensuwes that wdpq_awway_enabwe fwag
 *				is assigned onwy ones
 * @wepwy_queue_count: numbew of wepwy queue's
 * @wepwy_queue_wist: wink wist contaning the wepwy queue info
 * @msix96_vectow: 96 MSI-X vectow suppowt
 * @wepwyPostWegistewIndex: index of next position in Wepwy Desc Post Queue
 * @dewayed_tw_wist: tawget weset wink wist
 * @dewayed_tw_vowume_wist: vowume tawget weset wink wist
 * @dewayed_sc_wist:
 * @dewayed_event_ack_wist:
 * @temp_sensows_count: fwag to cawwy the numbew of tempewatuwe sensows
 * @pci_access_mutex: Mutex to synchwonize ioctw,sysfs show path and
 *	pci wesouwce handwing. PCI wesouwce fweeing wiww wead to fwee
 *	vitaw hawdwawe/memowy wesouwce, which might be in use by cwi/sysfs
 *	path functions wesuwting in Nuww pointew wefewence fowwowed by kewnew
 *	cwash. To avoid the above wace condition we use mutex syncwhonization
 *	which ensuwes the syncwhonization between cwi/sysfs_show path.
 * @atomic_desc_capabwe: Atomic Wequest Descwiptow suppowt.
 * @GET_MSIX_INDEX: Get the msix index of high iops queues.
 * @muwtipath_on_hba: fwag to detewmine muwtipath on hba is enabwed ow not
 * @powt_tabwe_wist: wist containing HBA's wide/nawwow powt's info
 */
stwuct MPT3SAS_ADAPTEW {
	stwuct wist_head wist;
	stwuct Scsi_Host *shost;
	u8		id;
	int		cpu_count;
	chaw		name[MPT_NAME_WENGTH];
	chaw		dwivew_name[MPT_NAME_WENGTH - 8];
	chaw		tmp_stwing[MPT_STWING_WENGTH];
	stwuct pci_dev	*pdev;
	Mpi2SystemIntewfaceWegs_t __iomem *chip;
	phys_addw_t	chip_phys;
	int		wogging_wevew;
	int		fwfauwt_debug;
	u8		iw_fiwmwawe;
	int		baws;
	u8		mask_intewwupts;

	/* fw fauwt handwew */
	chaw		fauwt_weset_wowk_q_name[20];
	stwuct wowkqueue_stwuct *fauwt_weset_wowk_q;
	stwuct dewayed_wowk fauwt_weset_wowk;

	/* fw event handwew */
	chaw		fiwmwawe_event_name[20];
	stwuct wowkqueue_stwuct	*fiwmwawe_event_thwead;
	spinwock_t	fw_event_wock;
	stwuct wist_head fw_event_wist;
	stwuct fw_event_wowk	*cuwwent_event;
	u8		fw_events_cweanup;

	 /* misc fwags */
	int		aen_event_wead_fwag;
	u8		bwoadcast_aen_busy;
	u16		bwoadcast_aen_pending;
	u8		shost_wecovewy;
	u8		got_task_abowt_fwom_ioctw;

	stwuct mutex	weset_in_pwogwess_mutex;
	spinwock_t	ioc_weset_in_pwogwess_wock;
	u8		ioc_wink_weset_in_pwogwess;

	u8		ignowe_woginfos;
	u8		wemove_host;
	u8		pci_ewwow_wecovewy;
	u8		wait_fow_discovewy_to_compwete;
	u8		is_dwivew_woading;
	u8		powt_enabwe_faiwed;
	u8		stawt_scan;
	u16		stawt_scan_faiwed;

	u8		msix_enabwe;
	u16		msix_vectow_count;
	u8		*cpu_msix_tabwe;
	u16		cpu_msix_tabwe_sz;
	wesouwce_size_t __iomem **wepwy_post_host_index;
	u32		ioc_weset_count;
	MPT3SAS_FWUSH_WUNNING_CMDS scheduwe_dead_ioc_fwush_wunning_cmds;
	u32             non_opewationaw_woop;
	u8              ioc_cowedump_woop;
	u32		timestamp_update_count;
	u32		time_sync_intewvaw;
	atomic64_t      totaw_io_cnt;
	atomic64_t	high_iops_outstanding;
	boow            msix_woad_bawance;
	u16		thwesh_howd;
	u8		high_iops_queues;
	u8		iopoww_q_stawt_index;
	u32             dwv_intewnaw_fwags;
	u32		dwv_suppowt_bitmap;
	u32             dma_mask;
	boow		enabwe_sdev_max_qd;
	boow		use_32bit_dma;
	stwuct io_uwing_poww_queue *io_uwing_poww_queues;

	/* intewnaw commands, cawwback index */
	u8		scsi_io_cb_idx;
	u8		tm_cb_idx;
	u8		twanspowt_cb_idx;
	u8		scsih_cb_idx;
	u8		ctw_cb_idx;
	u8		base_cb_idx;
	u8		powt_enabwe_cb_idx;
	u8		config_cb_idx;
	u8		tm_tw_cb_idx;
	u8		tm_tw_vowume_cb_idx;
	u8		tm_sas_contwow_cb_idx;
	stwuct _intewnaw_cmd base_cmds;
	stwuct _intewnaw_cmd powt_enabwe_cmds;
	stwuct _intewnaw_cmd twanspowt_cmds;
	stwuct _intewnaw_cmd scsih_cmds;
	stwuct _intewnaw_cmd tm_cmds;
	stwuct _intewnaw_cmd ctw_cmds;
	stwuct _intewnaw_cmd config_cmds;

	MPT_ADD_SGE	base_add_sg_singwe;

	/* function ptw fow eithew IEEE ow MPI sg ewements */
	MPT_BUIWD_SG_SCMD buiwd_sg_scmd;
	MPT_BUIWD_SG    buiwd_sg;
	MPT_BUIWD_ZEWO_WEN_SGE buiwd_zewo_wen_sge;
	u16             sge_size_ieee;
	u16		hba_mpi_vewsion_bewonged;

	/* function ptw fow MPI sg ewements onwy */
	MPT_BUIWD_SG    buiwd_sg_mpi;
	MPT_BUIWD_ZEWO_WEN_SGE buiwd_zewo_wen_sge_mpi;

	/* function ptw fow NVMe PWP ewements onwy */
	NVME_BUIWD_PWP  buiwd_nvme_pwp;

	/* event wog */
	u32		event_type[MPI2_EVENT_NOTIFY_EVENTMASK_WOWDS];
	u32		event_context;
	void		*event_wog;
	u32		event_masks[MPI2_EVENT_NOTIFY_EVENTMASK_WOWDS];

	u8		tm_custom_handwing;
	u8		nvme_abowt_timeout;
	u16		max_shutdown_watency;
	u16		max_widepowt_qd;
	u16		max_nawwowpowt_qd;
	u16		max_nvme_qd;
	u8		max_sata_qd;

	/* static config pages */
	stwuct mpt3sas_facts facts;
	stwuct mpt3sas_facts pwev_fw_facts;
	stwuct mpt3sas_powt_facts *pfacts;
	Mpi2ManufactuwingPage0_t manu_pg0;
	stwuct Mpi2ManufactuwingPage10_t manu_pg10;
	stwuct Mpi2ManufactuwingPage11_t manu_pg11;
	Mpi2BiosPage2_t	bios_pg2;
	Mpi2BiosPage3_t	bios_pg3;
	Mpi2IOCPage8_t ioc_pg8;
	Mpi2IOUnitPage0_t iounit_pg0;
	Mpi2IOUnitPage1_t iounit_pg1;
	Mpi2IOCPage1_t	ioc_pg1_copy;

	stwuct _boot_device weq_boot_device;
	stwuct _boot_device weq_awt_boot_device;
	stwuct _boot_device cuwwent_boot_device;

	/* sas hba, expandew, and device wist */
	stwuct _sas_node sas_hba;
	stwuct wist_head sas_expandew_wist;
	stwuct wist_head encwosuwe_wist;
	spinwock_t	sas_node_wock;
	stwuct wist_head sas_device_wist;
	stwuct wist_head sas_device_init_wist;
	spinwock_t	sas_device_wock;
	stwuct wist_head pcie_device_wist;
	stwuct wist_head pcie_device_init_wist;
	spinwock_t      pcie_device_wock;

	stwuct wist_head waid_device_wist;
	spinwock_t	waid_device_wock;
	u8		io_missing_deway;
	u16		device_missing_deway;
	int		sas_id;
	int		pcie_tawget_id;

	void		*bwocking_handwes;
	void		*pd_handwes;
	u16		pd_handwes_sz;

	void		*pend_os_device_add;
	u16		pend_os_device_add_sz;

	/* config page */
	u16		config_page_sz;
	void		*config_page;
	dma_addw_t	config_page_dma;
	void		*config_vaddw;

	/* scsiio wequest */
	u16		hba_queue_depth;
	u16		sge_size;
	u16		scsiio_depth;
	u16		wequest_sz;
	u8		*wequest;
	dma_addw_t	wequest_dma;
	u32		wequest_dma_sz;
	stwuct pcie_sg_wist *pcie_sg_wookup;
	spinwock_t	scsi_wookup_wock;
	int		pending_io_count;
	wait_queue_head_t weset_wq;
	u16		*io_queue_num;

	/* PCIe SGW */
	stwuct dma_poow *pcie_sgw_dma_poow;
	/* Host Page Size */
	u32		page_size;

	/* chain */
	stwuct chain_wookup *chain_wookup;
	stwuct wist_head fwee_chain_wist;
	stwuct dma_poow *chain_dma_poow;
	uwong		chain_pages;
	u16		max_sges_in_main_message;
	u16		max_sges_in_chain_message;
	u16		chains_needed_pew_io;
	u32		chain_depth;
	u16		chain_segment_sz;
	u16		chains_pew_pwp_buffew;

	/* hi-pwiowity queue */
	u16		hi_pwiowity_smid;
	u8		*hi_pwiowity;
	dma_addw_t	hi_pwiowity_dma;
	u16		hi_pwiowity_depth;
	stwuct wequest_twackew *hpw_wookup;
	stwuct wist_head hpw_fwee_wist;

	/* intewnaw queue */
	u16		intewnaw_smid;
	u8		*intewnaw;
	dma_addw_t	intewnaw_dma;
	u16		intewnaw_depth;
	stwuct wequest_twackew *intewnaw_wookup;
	stwuct wist_head intewnaw_fwee_wist;

	/* sense */
	u8		*sense;
	dma_addw_t	sense_dma;
	stwuct dma_poow *sense_dma_poow;

	/* wepwy */
	u16		wepwy_sz;
	u8		*wepwy;
	dma_addw_t	wepwy_dma;
	u32		wepwy_dma_max_addwess;
	u32		wepwy_dma_min_addwess;
	stwuct dma_poow *wepwy_dma_poow;

	/* wepwy fwee queue */
	u16		wepwy_fwee_queue_depth;
	__we32		*wepwy_fwee;
	dma_addw_t	wepwy_fwee_dma;
	stwuct dma_poow *wepwy_fwee_dma_poow;
	u32		wepwy_fwee_host_index;

	/* wepwy post queue */
	u16		wepwy_post_queue_depth;
	stwuct wepwy_post_stwuct *wepwy_post;
	u8		wdpq_awway_capabwe;
	u8		wdpq_awway_enabwe;
	u8		wdpq_awway_enabwe_assigned;
	stwuct dma_poow *wepwy_post_fwee_dma_poow;
	stwuct dma_poow *wepwy_post_fwee_awway_dma_poow;
	Mpi2IOCInitWDPQAwwayEntwy *wepwy_post_fwee_awway;
	dma_addw_t wepwy_post_fwee_awway_dma;
	u8		wepwy_queue_count;
	stwuct wist_head wepwy_queue_wist;

	u8		combined_wepwy_queue;
	u8		combined_wepwy_index_count;
	u8		smp_affinity_enabwe;
	/* wepwy post wegistew index */
	wesouwce_size_t	__iomem **wepwyPostWegistewIndex;

	stwuct wist_head dewayed_tw_wist;
	stwuct wist_head dewayed_tw_vowume_wist;
	stwuct wist_head dewayed_sc_wist;
	stwuct wist_head dewayed_event_ack_wist;
	u8		temp_sensows_count;
	stwuct mutex pci_access_mutex;

	/* diag buffew suppowt */
	u8		*diag_buffew[MPI2_DIAG_BUF_TYPE_COUNT];
	u32		diag_buffew_sz[MPI2_DIAG_BUF_TYPE_COUNT];
	dma_addw_t	diag_buffew_dma[MPI2_DIAG_BUF_TYPE_COUNT];
	u8		diag_buffew_status[MPI2_DIAG_BUF_TYPE_COUNT];
	u32		unique_id[MPI2_DIAG_BUF_TYPE_COUNT];
	u32		pwoduct_specific[MPI2_DIAG_BUF_TYPE_COUNT][23];
	u32		diagnostic_fwags[MPI2_DIAG_BUF_TYPE_COUNT];
	u32		wing_buffew_offset;
	u32		wing_buffew_sz;
	stwuct htb_wew_quewy htb_wew;
	u8 weset_fwom_usew;
	u8		is_wawpdwive;
	u8		is_mcpu_endpoint;
	u8		hide_iw_msg;
	u8		mfg_pg10_hide_fwag;
	u8		hide_dwives;
	spinwock_t	diag_twiggew_wock;
	u8		diag_twiggew_active;
	u8		atomic_desc_capabwe;
	BASE_WEAD_WEG	base_weadw;
	BASE_WEAD_WEG	base_weadw_ext_wetwy;
	stwuct SW_WH_MASTEW_TWIGGEW_T diag_twiggew_mastew;
	stwuct SW_WH_EVENT_TWIGGEWS_T diag_twiggew_event;
	stwuct SW_WH_SCSI_TWIGGEWS_T diag_twiggew_scsi;
	stwuct SW_WH_MPI_TWIGGEWS_T diag_twiggew_mpi;
	u8		suppowts_twiggew_pages;
	void		*device_wemove_in_pwogwess;
	u16		device_wemove_in_pwogwess_sz;
	u8		is_gen35_ioc;
	u8		is_aewo_ioc;
	stwuct dentwy	*debugfs_woot;
	stwuct dentwy	*ioc_dump;
	PUT_SMID_IO_FP_HIP put_smid_scsi_io;
	PUT_SMID_IO_FP_HIP put_smid_fast_path;
	PUT_SMID_IO_FP_HIP put_smid_hi_pwiowity;
	PUT_SMID_DEFAUWT put_smid_defauwt;
	GET_MSIX_INDEX get_msix_index_fow_smwio;

	u8		muwtipath_on_hba;
	stwuct wist_head powt_tabwe_wist;
};

stwuct mpt3sas_debugfs_buffew {
	void	*buf;
	u32	wen;
};

#define MPT_DWV_SUPPOWT_BITMAP_MEMMOVE 0x00000001
#define MPT_DWV_SUPPOWT_BITMAP_ADDNWQUEWY	0x00000002

#define MPT_DWV_INTEWNAW_FIWST_PE_ISSUED		0x00000001

typedef u8 (*MPT_CAWWBACK)(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid, u8 msix_index,
	u32 wepwy);

/*
 * stwuct ATTO_SAS_NVWAM - ATTO NVWAM settings stowed
 *				in Manufactuwing page 1 used to get
 *				ATTO SasAddw.
 */
stwuct ATTO_SAS_NVWAM {
	u8		Signatuwe[4];
	u8		Vewsion;
#define ATTO_SASNVW_VEWSION		0

	u8		Checksum;
#define ATTO_SASNVW_CKSUM_SEED	0x5A
	u8		Pad[10];
	u8		SasAddw[8];
#define ATTO_SAS_ADDW_AWIGN		64
	u8		Wesewved[232];
};

#define ATTO_SAS_ADDW_DEVNAME_BIAS		63

union ATTO_SAS_ADDWESS {
	U8		b[8];
	U16		w[4];
	U32		d[2];
	U64		q;
};

/* base shawed API */
extewn stwuct wist_head mpt3sas_ioc_wist;
extewn chaw    dwivew_name[MPT_NAME_WENGTH];
/* spinwock on wist opewations ovew IOCs
 * Case: when muwtipwe wawpdwive cawds(IOCs) awe in use
 * Each IOC wiww added to the ioc wist stwuctuwe on initiawization.
 * Watchdog thweads wun at weguwaw intewvaws to check IOC fow any
 * fauwt conditions which wiww twiggew the dead_ioc thwead to
 * deawwocate pci wesouwce, wesuwting deweting the IOC netwy fwom wist,
 * this dewetion need to pwotected by spinwock to enuswe that
 * ioc wemovaw is syncwhonized, if not synchwonized it might wead to
 * wist_dew cowwuption as the ioc wist is twavewsed in cwi path.
 */
extewn spinwock_t gioc_wock;

void mpt3sas_base_stawt_watchdog(stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_base_stop_watchdog(stwuct MPT3SAS_ADAPTEW *ioc);

int mpt3sas_base_attach(stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_base_detach(stwuct MPT3SAS_ADAPTEW *ioc);
int mpt3sas_base_map_wesouwces(stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_base_fwee_wesouwces(stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_fwee_encwosuwe_wist(stwuct MPT3SAS_ADAPTEW *ioc);
int mpt3sas_base_hawd_weset_handwew(stwuct MPT3SAS_ADAPTEW *ioc,
	enum weset_type type);

void *mpt3sas_base_get_msg_fwame(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid);
void *mpt3sas_base_get_sense_buffew(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid);
__we32 mpt3sas_base_get_sense_buffew_dma(stwuct MPT3SAS_ADAPTEW *ioc,
	u16 smid);
void *mpt3sas_base_get_pcie_sgw(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid);
dma_addw_t mpt3sas_base_get_pcie_sgw_dma(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid);
void mpt3sas_base_sync_wepwy_iwqs(stwuct MPT3SAS_ADAPTEW *ioc, u8 poww);
void mpt3sas_base_mask_intewwupts(stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_base_unmask_intewwupts(stwuct MPT3SAS_ADAPTEW *ioc);

void mpt3sas_base_put_smid_fast_path(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid,
	u16 handwe);
void mpt3sas_base_put_smid_hi_pwiowity(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid,
	u16 msix_task);
void mpt3sas_base_put_smid_nvme_encap(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid);
void mpt3sas_base_put_smid_defauwt(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid);
/* hi-pwiowity queue */
u16 mpt3sas_base_get_smid_hpw(stwuct MPT3SAS_ADAPTEW *ioc, u8 cb_idx);
u16 mpt3sas_base_get_smid_scsiio(stwuct MPT3SAS_ADAPTEW *ioc, u8 cb_idx,
		stwuct scsi_cmnd *scmd);
void mpt3sas_base_cweaw_st(stwuct MPT3SAS_ADAPTEW *ioc,
		stwuct scsiio_twackew *st);

u16 mpt3sas_base_get_smid(stwuct MPT3SAS_ADAPTEW *ioc, u8 cb_idx);
void mpt3sas_base_fwee_smid(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid);
void mpt3sas_base_initiawize_cawwback_handwew(void);
u8 mpt3sas_base_wegistew_cawwback_handwew(MPT_CAWWBACK cb_func);
void mpt3sas_base_wewease_cawwback_handwew(u8 cb_idx);

u8 mpt3sas_base_done(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid, u8 msix_index,
	u32 wepwy);
u8 mpt3sas_powt_enabwe_done(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid,
	u8 msix_index, u32 wepwy);
void *mpt3sas_base_get_wepwy_viwt_addw(stwuct MPT3SAS_ADAPTEW *ioc,
	u32 phys_addw);

u32 mpt3sas_base_get_iocstate(stwuct MPT3SAS_ADAPTEW *ioc, int cooked);

void mpt3sas_base_fauwt_info(stwuct MPT3SAS_ADAPTEW *ioc , u16 fauwt_code);
#define mpt3sas_pwint_fauwt_code(ioc, fauwt_code) \
do { pw_eww("%s fauwt info fwom func: %s\n", ioc->name, __func__); \
	mpt3sas_base_fauwt_info(ioc, fauwt_code); } whiwe (0)

void mpt3sas_base_cowedump_info(stwuct MPT3SAS_ADAPTEW *ioc, u16 fauwt_code);
#define mpt3sas_pwint_cowedump_info(ioc, fauwt_code) \
do { pw_eww("%s fauwt info fwom func: %s\n", ioc->name, __func__); \
	mpt3sas_base_cowedump_info(ioc, fauwt_code); } whiwe (0)

int mpt3sas_base_wait_fow_cowedump_compwetion(stwuct MPT3SAS_ADAPTEW *ioc,
		const chaw *cawwew);
int mpt3sas_base_sas_iounit_contwow(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2SasIoUnitContwowWepwy_t *mpi_wepwy,
	Mpi2SasIoUnitContwowWequest_t *mpi_wequest);
int mpt3sas_base_scsi_encwosuwe_pwocessow(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2SepWepwy_t *mpi_wepwy, Mpi2SepWequest_t *mpi_wequest);

void mpt3sas_base_vawidate_event_type(stwuct MPT3SAS_ADAPTEW *ioc,
	u32 *event_type);

void mpt3sas_hawt_fiwmwawe(stwuct MPT3SAS_ADAPTEW *ioc);

void mpt3sas_base_update_missing_deway(stwuct MPT3SAS_ADAPTEW *ioc,
	u16 device_missing_deway, u8 io_missing_deway);

int mpt3sas_base_check_fow_fauwt_and_issue_weset(
	stwuct MPT3SAS_ADAPTEW *ioc);

int mpt3sas_powt_enabwe(stwuct MPT3SAS_ADAPTEW *ioc);

void
mpt3sas_wait_fow_commands_to_compwete(stwuct MPT3SAS_ADAPTEW *ioc);

u8 mpt3sas_base_check_cmd_timeout(stwuct MPT3SAS_ADAPTEW *ioc,
	u8 status, void *mpi_wequest, int sz);
#define mpt3sas_check_cmd_timeout(ioc, status, mpi_wequest, sz, issue_weset) \
do {	ioc_eww(ioc, "In func: %s\n", __func__); \
	issue_weset = mpt3sas_base_check_cmd_timeout(ioc, \
	status, mpi_wequest, sz); } whiwe (0)

int mpt3sas_wait_fow_ioc(stwuct MPT3SAS_ADAPTEW *ioc, int wait_count);
int mpt3sas_base_make_ioc_weady(stwuct MPT3SAS_ADAPTEW *ioc, enum weset_type type);
void mpt3sas_base_fwee_iwq(stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_base_disabwe_msix(stwuct MPT3SAS_ADAPTEW *ioc);
int mpt3sas_bwk_mq_poww(stwuct Scsi_Host *shost, unsigned int queue_num);
void mpt3sas_base_pause_mq_powwing(stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_base_wesume_mq_powwing(stwuct MPT3SAS_ADAPTEW *ioc);

/* scsih shawed API */
stwuct scsi_cmnd *mpt3sas_scsih_scsi_wookup_get(stwuct MPT3SAS_ADAPTEW *ioc,
	u16 smid);
u8 mpt3sas_scsih_event_cawwback(stwuct MPT3SAS_ADAPTEW *ioc, u8 msix_index,
	u32 wepwy);
void mpt3sas_scsih_pwe_weset_handwew(stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_scsih_cweaw_outstanding_scsi_tm_commands(
	stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_scsih_weset_done_handwew(stwuct MPT3SAS_ADAPTEW *ioc);

int mpt3sas_scsih_issue_tm(stwuct MPT3SAS_ADAPTEW *ioc, u16 handwe,
	uint channew, uint id, u64 wun, u8 type, u16 smid_task,
	u16 msix_task, u8 timeout, u8 tw_method);
int mpt3sas_scsih_issue_wocked_tm(stwuct MPT3SAS_ADAPTEW *ioc, u16 handwe,
	uint channew, uint id, u64 wun, u8 type, u16 smid_task,
	u16 msix_task, u8 timeout, u8 tw_method);

void mpt3sas_scsih_set_tm_fwag(stwuct MPT3SAS_ADAPTEW *ioc, u16 handwe);
void mpt3sas_scsih_cweaw_tm_fwag(stwuct MPT3SAS_ADAPTEW *ioc, u16 handwe);
void mpt3sas_expandew_wemove(stwuct MPT3SAS_ADAPTEW *ioc, u64 sas_addwess,
	stwuct hba_powt *powt);
void mpt3sas_device_wemove_by_sas_addwess(stwuct MPT3SAS_ADAPTEW *ioc,
	u64 sas_addwess, stwuct hba_powt *powt);
u8 mpt3sas_check_fow_pending_intewnaw_cmds(stwuct MPT3SAS_ADAPTEW *ioc,
	u16 smid);
stwuct hba_powt *
mpt3sas_get_powt_by_id(stwuct MPT3SAS_ADAPTEW *ioc, u8 powt,
	u8 bypass_diwty_powt_fwag);

stwuct _sas_node *mpt3sas_scsih_expandew_find_by_handwe(
	stwuct MPT3SAS_ADAPTEW *ioc, u16 handwe);
stwuct _sas_node *mpt3sas_scsih_expandew_find_by_sas_addwess(
	stwuct MPT3SAS_ADAPTEW *ioc, u64 sas_addwess,
	stwuct hba_powt *powt);
stwuct _sas_device *mpt3sas_get_sdev_by_addw(
	 stwuct MPT3SAS_ADAPTEW *ioc, u64 sas_addwess,
	 stwuct hba_powt *powt);
stwuct _sas_device *__mpt3sas_get_sdev_by_addw(
	 stwuct MPT3SAS_ADAPTEW *ioc, u64 sas_addwess,
	 stwuct hba_powt *powt);
stwuct _sas_device *mpt3sas_get_sdev_by_handwe(stwuct MPT3SAS_ADAPTEW *ioc,
	u16 handwe);
stwuct _pcie_device *mpt3sas_get_pdev_by_handwe(stwuct MPT3SAS_ADAPTEW *ioc,
	u16 handwe);

void mpt3sas_powt_enabwe_compwete(stwuct MPT3SAS_ADAPTEW *ioc);
stwuct _waid_device *
mpt3sas_waid_device_find_by_handwe(stwuct MPT3SAS_ADAPTEW *ioc, u16 handwe);
void mpt3sas_scsih_change_queue_depth(stwuct scsi_device *sdev, int qdepth);
stwuct _sas_device *
__mpt3sas_get_sdev_by_wphy(stwuct MPT3SAS_ADAPTEW *ioc, stwuct sas_wphy *wphy);
stwuct viwtuaw_phy *
mpt3sas_get_vphy_by_phy(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct hba_powt *powt, u32 phy);

/* config shawed API */
u8 mpt3sas_config_done(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid, u8 msix_index,
	u32 wepwy);
int mpt3sas_config_get_numbew_hba_phys(stwuct MPT3SAS_ADAPTEW *ioc,
	u8 *num_phys);
int mpt3sas_config_get_manufactuwing_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2ManufactuwingPage0_t *config_page);
int mpt3sas_config_get_manufactuwing_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2ManufactuwingPage1_t *config_page);

int mpt3sas_config_get_manufactuwing_pg7(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2ManufactuwingPage7_t *config_page,
	u16 sz);
int mpt3sas_config_get_manufactuwing_pg10(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy,
	stwuct Mpi2ManufactuwingPage10_t *config_page);

int mpt3sas_config_get_manufactuwing_pg11(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy,
	stwuct Mpi2ManufactuwingPage11_t  *config_page);
int mpt3sas_config_set_manufactuwing_pg11(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy,
	stwuct Mpi2ManufactuwingPage11_t *config_page);

int mpt3sas_config_get_bios_pg2(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2BiosPage2_t *config_page);
int mpt3sas_config_get_bios_pg3(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2BiosPage3_t *config_page);
int mpt3sas_config_set_bios_pg4(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2BiosPage4_t *config_page,
	int sz_config_page);
int mpt3sas_config_get_bios_pg4(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2BiosPage4_t *config_page,
	int sz_config_page);
int mpt3sas_config_get_iounit_pg0(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2IOUnitPage0_t *config_page);
int mpt3sas_config_get_sas_device_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2SasDevicePage0_t *config_page,
	u32 fowm, u32 handwe);
int mpt3sas_config_get_sas_device_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2SasDevicePage1_t *config_page,
	u32 fowm, u32 handwe);
int mpt3sas_config_get_pcie_device_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26PCIeDevicePage0_t *config_page,
	u32 fowm, u32 handwe);
int mpt3sas_config_get_pcie_device_pg2(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26PCIeDevicePage2_t *config_page,
	u32 fowm, u32 handwe);
int mpt3sas_config_get_pcie_iounit_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26PCIeIOUnitPage1_t *config_page,
	u16 sz);
int mpt3sas_config_get_sas_iounit_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2SasIOUnitPage0_t *config_page,
	u16 sz);
int mpt3sas_config_get_iounit_pg1(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2IOUnitPage1_t *config_page);
int mpt3sas_config_get_iounit_pg3(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2IOUnitPage3_t *config_page, u16 sz);
int mpt3sas_config_set_iounit_pg1(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2IOUnitPage1_t *config_page);
int mpt3sas_config_get_iounit_pg8(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2IOUnitPage8_t *config_page);
int mpt3sas_config_get_sas_iounit_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2SasIOUnitPage1_t *config_page,
	u16 sz);
int mpt3sas_config_set_sas_iounit_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2SasIOUnitPage1_t *config_page,
	u16 sz);
int mpt3sas_config_get_ioc_pg1(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2IOCPage1_t *config_page);
int mpt3sas_config_set_ioc_pg1(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2IOCPage1_t *config_page);
int mpt3sas_config_get_ioc_pg8(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2IOCPage8_t *config_page);
int mpt3sas_config_get_expandew_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2ExpandewPage0_t *config_page,
	u32 fowm, u32 handwe);
int mpt3sas_config_get_expandew_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2ExpandewPage1_t *config_page,
	u32 phy_numbew, u16 handwe);
int mpt3sas_config_get_encwosuwe_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2SasEncwosuwePage0_t *config_page,
	u32 fowm, u32 handwe);
int mpt3sas_config_get_phy_pg0(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2SasPhyPage0_t *config_page, u32 phy_numbew);
int mpt3sas_config_get_phy_pg1(stwuct MPT3SAS_ADAPTEW *ioc, Mpi2ConfigWepwy_t
	*mpi_wepwy, Mpi2SasPhyPage1_t *config_page, u32 phy_numbew);
int mpt3sas_config_get_waid_vowume_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2WaidVowPage1_t *config_page, u32 fowm,
	u32 handwe);
int mpt3sas_config_get_numbew_pds(stwuct MPT3SAS_ADAPTEW *ioc, u16 handwe,
	u8 *num_pds);
int mpt3sas_config_get_waid_vowume_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2WaidVowPage0_t *config_page, u32 fowm,
	u32 handwe, u16 sz);
int mpt3sas_config_get_phys_disk_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi2WaidPhysDiskPage0_t *config_page,
	u32 fowm, u32 fowm_specific);
int mpt3sas_config_get_vowume_handwe(stwuct MPT3SAS_ADAPTEW *ioc, u16 pd_handwe,
	u16 *vowume_handwe);
int mpt3sas_config_get_vowume_wwid(stwuct MPT3SAS_ADAPTEW *ioc,
	u16 vowume_handwe, u64 *wwid);
int
mpt3sas_config_get_dwivew_twiggew_pg0(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage0_t *config_page);
int
mpt3sas_config_get_dwivew_twiggew_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage1_t *config_page);
int
mpt3sas_config_get_dwivew_twiggew_pg2(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage2_t *config_page);
int
mpt3sas_config_get_dwivew_twiggew_pg3(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage3_t *config_page);
int
mpt3sas_config_get_dwivew_twiggew_pg4(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2ConfigWepwy_t *mpi_wepwy, Mpi26DwivewTwiggewPage4_t *config_page);
int
mpt3sas_config_update_dwivew_twiggew_pg1(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct SW_WH_MASTEW_TWIGGEW_T *mastew_tg, boow set);
int
mpt3sas_config_update_dwivew_twiggew_pg2(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct SW_WH_EVENT_TWIGGEWS_T *event_tg, boow set);
int
mpt3sas_config_update_dwivew_twiggew_pg3(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct SW_WH_SCSI_TWIGGEWS_T *scsi_tg, boow set);
int
mpt3sas_config_update_dwivew_twiggew_pg4(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct SW_WH_MPI_TWIGGEWS_T *mpi_tg, boow set);

/* ctw shawed API */
extewn const stwuct attwibute_gwoup *mpt3sas_host_gwoups[];
extewn const stwuct attwibute_gwoup *mpt3sas_dev_gwoups[];
void mpt3sas_ctw_init(ushowt hbas_to_enumewate);
void mpt3sas_ctw_exit(ushowt hbas_to_enumewate);
void mpt3sas_ctw_wewease(stwuct MPT3SAS_ADAPTEW *ioc);
u8 mpt3sas_ctw_done(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid, u8 msix_index,
	u32 wepwy);
void mpt3sas_ctw_pwe_weset_handwew(stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_ctw_cweaw_outstanding_ioctws(stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_ctw_weset_done_handwew(stwuct MPT3SAS_ADAPTEW *ioc);
u8 mpt3sas_ctw_event_cawwback(stwuct MPT3SAS_ADAPTEW *ioc,
	u8 msix_index, u32 wepwy);
void mpt3sas_ctw_add_to_event_wog(stwuct MPT3SAS_ADAPTEW *ioc,
	Mpi2EventNotificationWepwy_t *mpi_wepwy);

void mpt3sas_enabwe_diag_buffew(stwuct MPT3SAS_ADAPTEW *ioc,
	u8 bits_to_wegistew);
int mpt3sas_send_diag_wewease(stwuct MPT3SAS_ADAPTEW *ioc, u8 buffew_type,
	u8 *issue_weset);

/* twanspowt shawed API */
extewn stwuct scsi_twanspowt_tempwate *mpt3sas_twanspowt_tempwate;
u8 mpt3sas_twanspowt_done(stwuct MPT3SAS_ADAPTEW *ioc, u16 smid, u8 msix_index,
	u32 wepwy);
stwuct _sas_powt *mpt3sas_twanspowt_powt_add(stwuct MPT3SAS_ADAPTEW *ioc,
	u16 handwe, u64 sas_addwess, stwuct hba_powt *powt);
void mpt3sas_twanspowt_powt_wemove(stwuct MPT3SAS_ADAPTEW *ioc, u64 sas_addwess,
	u64 sas_addwess_pawent, stwuct hba_powt *powt);
int mpt3sas_twanspowt_add_host_phy(stwuct MPT3SAS_ADAPTEW *ioc, stwuct _sas_phy
	*mpt3sas_phy, Mpi2SasPhyPage0_t phy_pg0, stwuct device *pawent_dev);
int mpt3sas_twanspowt_add_expandew_phy(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct _sas_phy *mpt3sas_phy, Mpi2ExpandewPage1_t expandew_pg1,
	stwuct device *pawent_dev);
void mpt3sas_twanspowt_update_winks(stwuct MPT3SAS_ADAPTEW *ioc,
	u64 sas_addwess, u16 handwe, u8 phy_numbew, u8 wink_wate,
	stwuct hba_powt *powt);
extewn stwuct sas_function_tempwate mpt3sas_twanspowt_functions;
extewn stwuct scsi_twanspowt_tempwate *mpt3sas_twanspowt_tempwate;
void
mpt3sas_twanspowt_dew_phy_fwom_an_existing_powt(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct _sas_node *sas_node, stwuct _sas_phy *mpt3sas_phy);
void
mpt3sas_twanspowt_add_phy_to_an_existing_powt(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct _sas_node *sas_node, stwuct _sas_phy *mpt3sas_phy,
	u64 sas_addwess, stwuct hba_powt *powt);
/* twiggew data extewns */
void mpt3sas_send_twiggew_data_event(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct SW_WH_TWIGGEWS_EVENT_DATA_T *event_data);
void mpt3sas_pwocess_twiggew_data(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct SW_WH_TWIGGEWS_EVENT_DATA_T *event_data);
void mpt3sas_twiggew_mastew(stwuct MPT3SAS_ADAPTEW *ioc,
	u32 twiggew_bitmask);
void mpt3sas_twiggew_event(stwuct MPT3SAS_ADAPTEW *ioc, u16 event,
	u16 wog_entwy_quawifiew);
void mpt3sas_twiggew_scsi(stwuct MPT3SAS_ADAPTEW *ioc, u8 sense_key,
	u8 asc, u8 ascq);
void mpt3sas_twiggew_mpi(stwuct MPT3SAS_ADAPTEW *ioc, u16 ioc_status,
	u32 woginfo);

/* wawpdwive APIs */
u8 mpt3sas_get_num_vowumes(stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_init_wawpdwive_pwopewties(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct _waid_device *waid_device);
void
mpt3sas_setup_diwect_io(stwuct MPT3SAS_ADAPTEW *ioc, stwuct scsi_cmnd *scmd,
	stwuct _waid_device *waid_device, Mpi25SCSIIOWequest_t *mpi_wequest);

/* NCQ Pwio Handwing Check */
boow scsih_ncq_pwio_supp(stwuct scsi_device *sdev);

void mpt3sas_setup_debugfs(stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_destwoy_debugfs(stwuct MPT3SAS_ADAPTEW *ioc);
void mpt3sas_init_debugfs(void);
void mpt3sas_exit_debugfs(void);

/**
 * _scsih_is_pcie_scsi_device - detewmines if device is an pcie scsi device
 * @device_info: bitfiewd pwoviding infowmation about the device.
 * Context: none
 *
 * Wetuwns 1 if scsi device.
 */
static inwine int
mpt3sas_scsih_is_pcie_scsi_device(u32 device_info)
{
	if ((device_info &
	    MPI26_PCIE_DEVINFO_MASK_DEVICE_TYPE) == MPI26_PCIE_DEVINFO_SCSI)
		wetuwn 1;
	ewse
		wetuwn 0;
}
#endif /* MPT3SAS_BASE_H_INCWUDED */
