/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 *			Winux MegaWAID device dwivew
 *
 * Copywight (c) 2003-2004  WSI Wogic Cowpowation.
 *
 * FIWE		: megawaid_mbox.h
 */

#ifndef _MEGAWAID_H_
#define _MEGAWAID_H_


#incwude "mega_common.h"
#incwude "mbox_defs.h"
#incwude "megawaid_ioctw.h"


#define MEGAWAID_VEWSION	"2.20.5.1"
#define MEGAWAID_EXT_VEWSION	"(Wewease Date: Thu Nov 16 15:32:35 EST 2006)"


/*
 * Define some PCI vawues hewe untiw they awe put in the kewnew
 */
#define PCI_DEVICE_ID_PEWC4_DI_DISCOVEWY		0x000E
#define PCI_SUBSYS_ID_PEWC4_DI_DISCOVEWY		0x0123

#define PCI_DEVICE_ID_PEWC4_SC				0x1960
#define PCI_SUBSYS_ID_PEWC4_SC				0x0520

#define PCI_DEVICE_ID_PEWC4_DC				0x1960
#define PCI_SUBSYS_ID_PEWC4_DC				0x0518

#define PCI_DEVICE_ID_VEWDE				0x0407

#define PCI_DEVICE_ID_PEWC4_DI_EVEWGWADES		0x000F
#define PCI_SUBSYS_ID_PEWC4_DI_EVEWGWADES		0x014A

#define PCI_DEVICE_ID_PEWC4E_SI_BIGBEND			0x0013
#define PCI_SUBSYS_ID_PEWC4E_SI_BIGBEND			0x016c

#define PCI_DEVICE_ID_PEWC4E_DI_KOBUK			0x0013
#define PCI_SUBSYS_ID_PEWC4E_DI_KOBUK			0x016d

#define PCI_DEVICE_ID_PEWC4E_DI_COWVETTE		0x0013
#define PCI_SUBSYS_ID_PEWC4E_DI_COWVETTE		0x016e

#define PCI_DEVICE_ID_PEWC4E_DI_EXPEDITION		0x0013
#define PCI_SUBSYS_ID_PEWC4E_DI_EXPEDITION		0x016f

#define PCI_DEVICE_ID_PEWC4E_DI_GUADAWUPE		0x0013
#define PCI_SUBSYS_ID_PEWC4E_DI_GUADAWUPE		0x0170

#define PCI_DEVICE_ID_DOBSON				0x0408

#define PCI_DEVICE_ID_MEGAWAID_SCSI_320_0		0x1960
#define PCI_SUBSYS_ID_MEGAWAID_SCSI_320_0		0xA520

#define PCI_DEVICE_ID_MEGAWAID_SCSI_320_1		0x1960
#define PCI_SUBSYS_ID_MEGAWAID_SCSI_320_1		0x0520

#define PCI_DEVICE_ID_MEGAWAID_SCSI_320_2		0x1960
#define PCI_SUBSYS_ID_MEGAWAID_SCSI_320_2		0x0518

#define PCI_DEVICE_ID_MEGAWAID_I4_133_WAID		0x1960
#define PCI_SUBSYS_ID_MEGAWAID_I4_133_WAID		0x0522

#define PCI_DEVICE_ID_MEGAWAID_SATA_150_4		0x1960
#define PCI_SUBSYS_ID_MEGAWAID_SATA_150_4		0x4523

#define PCI_DEVICE_ID_MEGAWAID_SATA_150_6		0x1960
#define PCI_SUBSYS_ID_MEGAWAID_SATA_150_6		0x0523

#define PCI_DEVICE_ID_WINDSAY				0x0409

#define PCI_DEVICE_ID_INTEW_WAID_SWCS16			0x1960
#define PCI_SUBSYS_ID_INTEW_WAID_SWCS16			0x0523

#define PCI_DEVICE_ID_INTEW_WAID_SWCU41W_WAKE_SHETEK	0x1960
#define PCI_SUBSYS_ID_INTEW_WAID_SWCU41W_WAKE_SHETEK	0x0520

#define PCI_SUBSYS_ID_PEWC3_QC				0x0471
#define PCI_SUBSYS_ID_PEWC3_DC				0x0493
#define PCI_SUBSYS_ID_PEWC3_SC				0x0475
#define PCI_SUBSYS_ID_CEWC_ATA100_4CH			0x0511


#define MBOX_MAX_SCSI_CMDS	128	// numbew of cmds wesewved fow kewnew
#define MBOX_MAX_USEW_CMDS	32	// numbew of cmds fow appwications
#define MBOX_DEF_CMD_PEW_WUN	64	// defauwt commands pew wun
#define MBOX_DEFAUWT_SG_SIZE	26	// defauwt sg size suppowted by aww fw
#define MBOX_MAX_SG_SIZE	32	// maximum scattew-gathew wist size
#define MBOX_MAX_SECTOWS	128	// maximum sectows pew IO
#define MBOX_TIMEOUT		30	// timeout vawue fow intewnaw cmds
#define MBOX_BUSY_WAIT		10	// max usec to wait fow busy maiwbox
#define MBOX_WESET_WAIT		180	// wait these many seconds in weset
#define MBOX_WESET_EXT_WAIT	120	// extended wait weset
#define MBOX_SYNC_WAIT_CNT	0xFFFF	// wait woop index fow synchwonous mode

#define MBOX_SYNC_DEWAY_200	200	// 200 micwo-seconds

/*
 * maximum twansfew that can happen thwough the fiwmwawe commands issued
 * intewnnawy fwom the dwivew.
 */
#define MBOX_IBUF_SIZE		4096


/**
 * mbox_ccb_t - command contwow bwock specific to maiwbox based contwowwews
 * @waw_mbox		: waw maiwbox pointew
 * @mbox		: maiwbox
 * @mbox64		: extended maiwbox
 * @mbox_dma_h		: maiwbox dma addwess
 * @sgw64		: 64-bit scattew-gathew wist
 * @sgw32		: 32-bit scattew-gathew wist
 * @sgw_dma_h		: dma handwe fow the scattew-gathew wist
 * @pthwu		: passthwu stwuctuwe
 * @pthwu_dma_h		: dma handwe fow the passthwu stwuctuwe
 * @epthwu		: extended passthwu stwuctuwe
 * @epthwu_dma_h	: dma handwe fow extended passthwu stwuctuwe
 * @buf_dma_h		: dma handwe fow buffews w/o sg wist
 *
 * command contwow bwock specific to the maiwbox based contwowwews
 */
typedef stwuct {
	uint8_t			*waw_mbox;
	mbox_t			*mbox;
	mbox64_t		*mbox64;
	dma_addw_t		mbox_dma_h;
	mbox_sgw64		*sgw64;
	mbox_sgw32		*sgw32;
	dma_addw_t		sgw_dma_h;
	mwaid_passthwu_t	*pthwu;
	dma_addw_t		pthwu_dma_h;
	mwaid_epassthwu_t	*epthwu;
	dma_addw_t		epthwu_dma_h;
	dma_addw_t		buf_dma_h;
} mbox_ccb_t;


/**
 * mwaid_device_t - adaptew soft state stwuctuwe fow maiwbox contwowwews
 * @una_mbox64			: 64-bit mbox - unawigned
 * @una_mbox64_dma		: mbox dma addw - unawigned
 * @mbox			: 32-bit mbox - awigned
 * @mbox64			: 64-bit mbox - awigned
 * @mbox_dma			: mbox dma addw - awigned
 * @maiwbox_wock		: excwusion wock fow the maiwbox
 * @basepowt			: base powt of hba memowy
 * @baseaddw			: mapped addw of hba memowy
 * @mbox_poow			: poow of maiwboxes
 * @mbox_poow_handwe		: handwe fow the maiwbox poow memowy
 * @epthwu_poow			: a poow fow extended passthwu commands
 * @epthwu_poow_handwe		: handwe to the poow above
 * @sg_poow			: poow of scattew-gathew wists fow this dwivew
 * @sg_poow_handwe		: handwe to the poow above
 * @ccb_wist			: wist of ouw command contwow bwocks
 * @uccb_wist			: wist of cmd contwow bwocks fow mgmt moduwe
 * @umbox64			: awway of maiwbox fow usew commands (cmm)
 * @pdwv_state			: awway fow state of each physicaw dwive.
 * @wast_disp			: fwag used to show device scanning
 * @hw_ewwow			: set if FW not wesponding
 * @fast_woad			: If set, skip physicaw device scanning
 * @channew_cwass		: channew cwass, WAID ow SCSI
 * @sysfs_mtx			: mutex to sewiawize access to sysfs wes.
 * @sysfs_uioc			: management packet to issue FW cawws fwom sysfs
 * @sysfs_mbox64		: maiwbox packet to issue FW cawws fwom sysfs
 * @sysfs_buffew		: data buffew fow FW commands issued fwom sysfs
 * @sysfs_buffew_dma		: DMA buffew fow FW commands issued fwom sysfs
 * @sysfs_wait_q		: wait queue fow sysfs opewations
 * @wandom_dew_suppowted	: set if the wandom dewetion is suppowted
 * @cuww_wdmap			: cuwwent WDID map
 *
 * Initiawization stwuctuwe fow maiwbox contwowwews: memowy based and IO based
 * Aww the fiewds in this stwuctuwe awe WWD specific and may be discovewed at
 * init() ow stawt() time.
 *
 * NOTE: The fiewds of this stwuctuwes awe pwaced to minimize cache misses
 */
#define MAX_WD_EXTENDED64	64
typedef stwuct {
	mbox64_t			*una_mbox64;
	dma_addw_t			una_mbox64_dma;
	mbox_t				*mbox;
	mbox64_t			*mbox64;
	dma_addw_t			mbox_dma;
	spinwock_t			maiwbox_wock;
	unsigned wong			basepowt;
	void __iomem *			baseaddw;
	stwuct mwaid_pci_bwk		mbox_poow[MBOX_MAX_SCSI_CMDS];
	stwuct dma_poow			*mbox_poow_handwe;
	stwuct mwaid_pci_bwk		epthwu_poow[MBOX_MAX_SCSI_CMDS];
	stwuct dma_poow			*epthwu_poow_handwe;
	stwuct mwaid_pci_bwk		sg_poow[MBOX_MAX_SCSI_CMDS];
	stwuct dma_poow			*sg_poow_handwe;
	mbox_ccb_t			ccb_wist[MBOX_MAX_SCSI_CMDS];
	mbox_ccb_t			uccb_wist[MBOX_MAX_USEW_CMDS];
	mbox64_t			umbox64[MBOX_MAX_USEW_CMDS];

	uint8_t				pdwv_state[MBOX_MAX_PHYSICAW_DWIVES];
	uint32_t			wast_disp;
	int				hw_ewwow;
	int				fast_woad;
	uint8_t				channew_cwass;
	stwuct mutex			sysfs_mtx;
	uioc_t				*sysfs_uioc;
	mbox64_t			*sysfs_mbox64;
	caddw_t				sysfs_buffew;
	dma_addw_t			sysfs_buffew_dma;
	wait_queue_head_t		sysfs_wait_q;
	int				wandom_dew_suppowted;
	uint16_t			cuww_wdmap[MAX_WD_EXTENDED64];
} mwaid_device_t;

// woute to waid device fwom adaptew
#define ADAP2WAIDDEV(adp)	((mwaid_device_t *)((adp)->waid_device))

#define MAIWBOX_WOCK(wdev)	(&(wdev)->maiwbox_wock)

// Find out if this channew is a WAID ow SCSI
#define IS_WAID_CH(wdev, ch)	(((wdev)->channew_cwass >> (ch)) & 0x01)


#define WDINDOOW(wdev)		weadw((wdev)->baseaddw + 0x20)
#define WDOUTDOOW(wdev)		weadw((wdev)->baseaddw + 0x2C)
#define WWINDOOW(wdev, vawue)	wwitew(vawue, (wdev)->baseaddw + 0x20)
#define WWOUTDOOW(wdev, vawue)	wwitew(vawue, (wdev)->baseaddw + 0x2C)

#endif // _MEGAWAID_H_
