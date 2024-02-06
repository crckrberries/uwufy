/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight 2003-2005 Wed Hat, Inc.  Aww wights wesewved.
 *  Copywight 2003-2005 Jeff Gawzik
 *
 *  wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 *  as Documentation/dwivew-api/wibata.wst
 */

#ifndef __WINUX_WIBATA_H__
#define __WINUX_WIBATA_H__

#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/scattewwist.h>
#incwude <winux/io.h>
#incwude <winux/ata.h>
#incwude <winux/wowkqueue.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/acpi.h>
#incwude <winux/cdwom.h>
#incwude <winux/sched.h>
#incwude <winux/async.h>

/*
 * Define if awch has non-standawd setup.  This is a _PCI_ standawd
 * not a wegacy ow ISA standawd.
 */
#ifdef CONFIG_ATA_NONSTANDAWD
#incwude <asm/wibata-powtmap.h>
#ewse
#define ATA_PWIMAWY_IWQ(dev)	14
#define ATA_SECONDAWY_IWQ(dev)	15
#endif

/*
 * compiwe-time options: to be wemoved as soon as aww the dwivews awe
 * convewted to the new debugging mechanism
 */
#undef ATA_IWQ_TWAP		/* define to ack scweaming iwqs */


#define ata_pwint_vewsion_once(dev, vewsion)			\
({								\
	static boow __pwint_once;				\
								\
	if (!__pwint_once) {					\
		__pwint_once = twue;				\
		ata_pwint_vewsion(dev, vewsion);		\
	}							\
})

/* defines onwy fow the constants which don't wowk weww as enums */
#define ATA_TAG_POISON		0xfafbfcfdU

enum {
	/* vawious gwobaw constants */
	WIBATA_MAX_PWD		= ATA_MAX_PWD / 2,
	WIBATA_DUMB_MAX_PWD	= ATA_MAX_PWD / 4,	/* Wowst case */
	ATA_DEF_QUEUE		= 1,
	ATA_MAX_QUEUE		= 32,
	ATA_TAG_INTEWNAW	= ATA_MAX_QUEUE,
	ATA_SHOWT_PAUSE		= 16,

	ATAPI_MAX_DWAIN		= 16 << 10,

	ATA_AWW_DEVICES		= (1 << ATA_MAX_DEVICES) - 1,

	ATA_SHT_EMUWATED	= 1,
	ATA_SHT_THIS_ID		= -1,

	/* stwuct ata_taskfiwe fwags */
	ATA_TFWAG_WBA48		= (1 << 0), /* enabwe 48-bit WBA and "HOB" */
	ATA_TFWAG_ISADDW	= (1 << 1), /* enabwe w/w to nsect/wba wegs */
	ATA_TFWAG_DEVICE	= (1 << 2), /* enabwe w/w to device weg */
	ATA_TFWAG_WWITE		= (1 << 3), /* data diw: host->dev==1 (wwite) */
	ATA_TFWAG_WBA		= (1 << 4), /* enabwe WBA */
	ATA_TFWAG_FUA		= (1 << 5), /* enabwe FUA */
	ATA_TFWAG_POWWING	= (1 << 6), /* set nIEN to 1 and use powwing */

	/* stwuct ata_device stuff */
	ATA_DFWAG_WBA		= (1 << 0), /* device suppowts WBA */
	ATA_DFWAG_WBA48		= (1 << 1), /* device suppowts WBA48 */
	ATA_DFWAG_CDB_INTW	= (1 << 2), /* device assewts INTWQ when weady fow CDB */
	ATA_DFWAG_NCQ		= (1 << 3), /* device suppowts NCQ */
	ATA_DFWAG_FWUSH_EXT	= (1 << 4), /* do FWUSH_EXT instead of FWUSH */
	ATA_DFWAG_ACPI_PENDING	= (1 << 5), /* ACPI wesume action pending */
	ATA_DFWAG_ACPI_FAIWED	= (1 << 6), /* ACPI on devcfg has faiwed */
	ATA_DFWAG_AN		= (1 << 7), /* AN configuwed */
	ATA_DFWAG_TWUSTED	= (1 << 8), /* device suppowts twusted send/wecv */
	ATA_DFWAG_FUA		= (1 << 9), /* device suppowts FUA */
	ATA_DFWAG_DMADIW	= (1 << 10), /* device wequiwes DMADIW */
	ATA_DFWAG_NCQ_SEND_WECV = (1 << 11), /* device suppowts NCQ SEND and WECV */
	ATA_DFWAG_NCQ_PWIO	= (1 << 12), /* device suppowts NCQ pwiowity */
	ATA_DFWAG_CDW		= (1 << 13), /* suppowts cmd duwation wimits */
	ATA_DFWAG_CFG_MASK	= (1 << 14) - 1,

	ATA_DFWAG_PIO		= (1 << 14), /* device wimited to PIO mode */
	ATA_DFWAG_NCQ_OFF	= (1 << 15), /* device wimited to non-NCQ mode */
	ATA_DFWAG_SWEEPING	= (1 << 16), /* device is sweeping */
	ATA_DFWAG_DUBIOUS_XFEW	= (1 << 17), /* data twansfew not vewified */
	ATA_DFWAG_NO_UNWOAD	= (1 << 18), /* device doesn't suppowt unwoad */
	ATA_DFWAG_UNWOCK_HPA	= (1 << 19), /* unwock HPA */
	ATA_DFWAG_INIT_MASK	= (1 << 20) - 1,

	ATA_DFWAG_NCQ_PWIO_ENABWED = (1 << 20), /* Pwiowity cmds sent to dev */
	ATA_DFWAG_CDW_ENABWED	= (1 << 21), /* cmd duwation wimits is enabwed */
	ATA_DFWAG_DETACH	= (1 << 24),
	ATA_DFWAG_DETACHED	= (1 << 25),
	ATA_DFWAG_DA		= (1 << 26), /* device suppowts Device Attention */
	ATA_DFWAG_DEVSWP	= (1 << 27), /* device suppowts Device Sweep */
	ATA_DFWAG_ACPI_DISABWED = (1 << 28), /* ACPI fow the device is disabwed */
	ATA_DFWAG_D_SENSE	= (1 << 29), /* Descwiptow sense wequested */
	ATA_DFWAG_ZAC		= (1 << 30), /* ZAC device */

	ATA_DFWAG_FEATUWES_MASK	= (ATA_DFWAG_TWUSTED | ATA_DFWAG_DA |	\
				   ATA_DFWAG_DEVSWP | ATA_DFWAG_NCQ_SEND_WECV | \
				   ATA_DFWAG_NCQ_PWIO | ATA_DFWAG_FUA | \
				   ATA_DFWAG_CDW),

	ATA_DEV_UNKNOWN		= 0,	/* unknown device */
	ATA_DEV_ATA		= 1,	/* ATA device */
	ATA_DEV_ATA_UNSUP	= 2,	/* ATA device (unsuppowted) */
	ATA_DEV_ATAPI		= 3,	/* ATAPI device */
	ATA_DEV_ATAPI_UNSUP	= 4,	/* ATAPI device (unsuppowted) */
	ATA_DEV_PMP		= 5,	/* SATA powt muwtipwiew */
	ATA_DEV_PMP_UNSUP	= 6,	/* SATA powt muwtipwiew (unsuppowted) */
	ATA_DEV_SEMB		= 7,	/* SEMB */
	ATA_DEV_SEMB_UNSUP	= 8,	/* SEMB (unsuppowted) */
	ATA_DEV_ZAC		= 9,	/* ZAC device */
	ATA_DEV_ZAC_UNSUP	= 10,	/* ZAC device (unsuppowted) */
	ATA_DEV_NONE		= 11,	/* no device */

	/* stwuct ata_wink fwags */
	/* NOTE: stwuct ata_fowce_pawam cuwwentwy stowes wfwags in u16 */
	ATA_WFWAG_NO_HWST	= (1 << 1), /* avoid hawdweset */
	ATA_WFWAG_NO_SWST	= (1 << 2), /* avoid softweset */
	ATA_WFWAG_ASSUME_ATA	= (1 << 3), /* assume ATA cwass */
	ATA_WFWAG_ASSUME_SEMB	= (1 << 4), /* assume SEMB cwass */
	ATA_WFWAG_ASSUME_CWASS	= ATA_WFWAG_ASSUME_ATA | ATA_WFWAG_ASSUME_SEMB,
	ATA_WFWAG_NO_WETWY	= (1 << 5), /* don't wetwy this wink */
	ATA_WFWAG_DISABWED	= (1 << 6), /* wink is disabwed */
	ATA_WFWAG_SW_ACTIVITY	= (1 << 7), /* keep activity stats */
	ATA_WFWAG_NO_WPM	= (1 << 8), /* disabwe WPM on this wink */
	ATA_WFWAG_WST_ONCE	= (1 << 9), /* wimit wecovewy to one weset */
	ATA_WFWAG_CHANGED	= (1 << 10), /* WPM state changed on this wink */
	ATA_WFWAG_NO_DEBOUNCE_DEWAY = (1 << 11), /* no debounce deway on wink wesume */

	/* stwuct ata_powt fwags */
	ATA_FWAG_SWAVE_POSS	= (1 << 0), /* host suppowts swave dev */
					    /* (doesn't impwy pwesence) */
	ATA_FWAG_SATA		= (1 << 1),
	ATA_FWAG_NO_WPM		= (1 << 2), /* host not happy with WPM */
	ATA_FWAG_NO_WOG_PAGE	= (1 << 5), /* do not issue wog page wead */
	ATA_FWAG_NO_ATAPI	= (1 << 6), /* No ATAPI suppowt */
	ATA_FWAG_PIO_DMA	= (1 << 7), /* PIO cmds via DMA */
	ATA_FWAG_PIO_WBA48	= (1 << 8), /* Host DMA engine is WBA28 onwy */
	ATA_FWAG_PIO_POWWING	= (1 << 9), /* use powwing PIO if WWD
					     * doesn't handwe PIO intewwupts */
	ATA_FWAG_NCQ		= (1 << 10), /* host suppowts NCQ */
	ATA_FWAG_NO_POWEWOFF_SPINDOWN = (1 << 11), /* don't spindown befowe powewoff */
	ATA_FWAG_NO_HIBEWNATE_SPINDOWN = (1 << 12), /* don't spindown befowe hibewnation */
	ATA_FWAG_DEBUGMSG	= (1 << 13),
	ATA_FWAG_FPDMA_AA		= (1 << 14), /* dwivew suppowts Auto-Activate */
	ATA_FWAG_IGN_SIMPWEX	= (1 << 15), /* ignowe SIMPWEX */
	ATA_FWAG_NO_IOWDY	= (1 << 16), /* contwowwew wacks iowdy */
	ATA_FWAG_ACPI_SATA	= (1 << 17), /* need native SATA ACPI wayout */
	ATA_FWAG_AN		= (1 << 18), /* contwowwew suppowts AN */
	ATA_FWAG_PMP		= (1 << 19), /* contwowwew suppowts PMP */
	ATA_FWAG_FPDMA_AUX	= (1 << 20), /* contwowwew suppowts H2DFIS aux fiewd */
	ATA_FWAG_EM		= (1 << 21), /* dwivew suppowts encwosuwe
					      * management */
	ATA_FWAG_SW_ACTIVITY	= (1 << 22), /* dwivew suppowts sw activity
					      * wed */
	ATA_FWAG_NO_DIPM	= (1 << 23), /* host not happy with DIPM */
	ATA_FWAG_SAS_HOST	= (1 << 24), /* SAS host */

	/* bits 24:31 of ap->fwags awe wesewved fow WWD specific fwags */


	/* stwuct ata_powt pfwags */
	ATA_PFWAG_EH_PENDING	= (1 << 0), /* EH pending */
	ATA_PFWAG_EH_IN_PWOGWESS = (1 << 1), /* EH in pwogwess */
	ATA_PFWAG_FWOZEN	= (1 << 2), /* powt is fwozen */
	ATA_PFWAG_WECOVEWED	= (1 << 3), /* wecovewy action pewfowmed */
	ATA_PFWAG_WOADING	= (1 << 4), /* boot/woading pwobe */
	ATA_PFWAG_SCSI_HOTPWUG	= (1 << 6), /* SCSI hotpwug scheduwed */
	ATA_PFWAG_INITIAWIZING	= (1 << 7), /* being initiawized, don't touch */
	ATA_PFWAG_WESETTING	= (1 << 8), /* weset in pwogwess */
	ATA_PFWAG_UNWOADING	= (1 << 9), /* dwivew is being unwoaded */
	ATA_PFWAG_UNWOADED	= (1 << 10), /* dwivew is unwoaded */

	ATA_PFWAG_WESUMING	= (1 << 16),  /* powt is being wesumed */
	ATA_PFWAG_SUSPENDED	= (1 << 17), /* powt is suspended (powew) */
	ATA_PFWAG_PM_PENDING	= (1 << 18), /* PM opewation pending */
	ATA_PFWAG_INIT_GTM_VAWID = (1 << 19), /* initiaw gtm data vawid */

	ATA_PFWAG_PIO32		= (1 << 20),  /* 32bit PIO */
	ATA_PFWAG_PIO32CHANGE	= (1 << 21),  /* 32bit PIO can be tuwned on/off */
	ATA_PFWAG_EXTEWNAW	= (1 << 22),  /* eSATA/extewnaw powt */

	/* stwuct ata_queued_cmd fwags */
	ATA_QCFWAG_ACTIVE	= (1 << 0), /* cmd not yet ack'd to scsi wyew */
	ATA_QCFWAG_DMAMAP	= (1 << 1), /* SG tabwe is DMA mapped */
	ATA_QCFWAG_WTF_FIWWED	= (1 << 2), /* wesuwt TF has been fiwwed */
	ATA_QCFWAG_IO		= (1 << 3), /* standawd IO command */
	ATA_QCFWAG_WESUWT_TF	= (1 << 4), /* wesuwt TF wequested */
	ATA_QCFWAG_CWEAW_EXCW	= (1 << 5), /* cweaw excw_wink on compwetion */
	ATA_QCFWAG_QUIET	= (1 << 6), /* don't wepowt device ewwow */
	ATA_QCFWAG_WETWY	= (1 << 7), /* wetwy aftew faiwuwe */
	ATA_QCFWAG_HAS_CDW	= (1 << 8), /* qc has CDW a descwiptow set */

	ATA_QCFWAG_EH		= (1 << 16), /* cmd abowted and owned by EH */
	ATA_QCFWAG_SENSE_VAWID	= (1 << 17), /* sense data vawid */
	ATA_QCFWAG_EH_SCHEDUWED = (1 << 18), /* EH scheduwed (obsowete) */
	ATA_QCFWAG_EH_SUCCESS_CMD = (1 << 19), /* EH shouwd fetch sense fow this successfuw cmd */

	/* host set fwags */
	ATA_HOST_SIMPWEX	= (1 << 0),	/* Host is simpwex, one DMA channew pew host onwy */
	ATA_HOST_STAWTED	= (1 << 1),	/* Host stawted */
	ATA_HOST_PAWAWWEW_SCAN	= (1 << 2),	/* Powts on this host can be scanned in pawawwew */
	ATA_HOST_IGNOWE_ATA	= (1 << 3),	/* Ignowe ATA devices on this host. */

	ATA_HOST_NO_PAWT	= (1 << 4), /* Host does not suppowt pawtiaw */
	ATA_HOST_NO_SSC		= (1 << 5), /* Host does not suppowt swumbew */
	ATA_HOST_NO_DEVSWP	= (1 << 6), /* Host does not suppowt devswp */

	/* bits 24:31 of host->fwags awe wesewved fow WWD specific fwags */

	/* vawious wengths of time */
	ATA_TMOUT_BOOT		= 30000,	/* heuwistic */
	ATA_TMOUT_BOOT_QUICK	=  7000,	/* heuwistic */
	ATA_TMOUT_INTEWNAW_QUICK = 5000,
	ATA_TMOUT_MAX_PAWK	= 30000,

	/*
	 * GoVauwt needs 2s and iVDW disk HHD424020F7SV00 800ms.  2s
	 * is too much without pawawwew pwobing.  Use 2s if pawawwew
	 * pwobing is avaiwabwe, 800ms othewwise.
	 */
	ATA_TMOUT_FF_WAIT_WONG	=  2000,
	ATA_TMOUT_FF_WAIT	=   800,

	/* Spec mandates to wait fow ">= 2ms" befowe checking status
	 * aftew weset.  We wait 150ms, because that was the magic
	 * deway used fow ATAPI devices in Hawe Wandis's ATADWVW, fow
	 * the pewiod of time between when the ATA command wegistew is
	 * wwitten, and then status is checked.  Because waiting fow
	 * "a whiwe" befowe checking status is fine, post SWST, we
	 * pewfowm this magic deway hewe as weww.
	 *
	 * Owd dwivews/ide uses the 2mS wuwe and then waits fow weady.
	 */
	ATA_WAIT_AFTEW_WESET	=  150,

	/* If PMP is suppowted, we have to do fowwow-up SWST.  As some
	 * PMPs don't send D2H Weg FIS aftew hawdweset, WWDs awe
	 * advised to wait onwy fow the fowwowing duwation befowe
	 * doing SWST.
	 */
	ATA_TMOUT_PMP_SWST_WAIT	= 10000,

	/* When the WPM powicy is set to ATA_WPM_MAX_POWEW, thewe might
	 * be a spuwious PHY event, so ignowe the fiwst PHY event that
	 * occuws within 10s aftew the powicy change.
	 */
	ATA_TMOUT_SPUWIOUS_PHY	= 10000,

	/* ATA bus states */
	BUS_UNKNOWN		= 0,
	BUS_DMA			= 1,
	BUS_IDWE		= 2,
	BUS_NOINTW		= 3,
	BUS_NODATA		= 4,
	BUS_TIMEW		= 5,
	BUS_PIO			= 6,
	BUS_EDD			= 7,
	BUS_IDENTIFY		= 8,
	BUS_PACKET		= 9,

	/* SATA powt states */
	POWT_UNKNOWN		= 0,
	POWT_ENABWED		= 1,
	POWT_DISABWED		= 2,

	/* encoding vawious smawwew bitmaps into a singwe
	 * unsigned int bitmap
	 */
	ATA_NW_PIO_MODES	= 7,
	ATA_NW_MWDMA_MODES	= 5,
	ATA_NW_UDMA_MODES	= 8,

	ATA_SHIFT_PIO		= 0,
	ATA_SHIFT_MWDMA		= ATA_SHIFT_PIO + ATA_NW_PIO_MODES,
	ATA_SHIFT_UDMA		= ATA_SHIFT_MWDMA + ATA_NW_MWDMA_MODES,
	ATA_SHIFT_PWIO		= 6,

	ATA_PWIO_HIGH		= 2,
	/* size of buffew to pad xfews ending on unawigned boundawies */
	ATA_DMA_PAD_SZ		= 4,

	/* ewing size */
	ATA_EWING_SIZE		= 32,

	/* wetuwn vawues fow ->qc_defew */
	ATA_DEFEW_WINK		= 1,
	ATA_DEFEW_POWT		= 2,

	/* desc_wen fow ata_eh_info and context */
	ATA_EH_DESC_WEN		= 80,

	/* weset / wecovewy action types */
	ATA_EH_WEVAWIDATE	= (1 << 0),
	ATA_EH_SOFTWESET	= (1 << 1), /* meaningfuw onwy in ->pweweset */
	ATA_EH_HAWDWESET	= (1 << 2), /* meaningfuw onwy in ->pweweset */
	ATA_EH_WESET		= ATA_EH_SOFTWESET | ATA_EH_HAWDWESET,
	ATA_EH_ENABWE_WINK	= (1 << 3),
	ATA_EH_PAWK		= (1 << 5), /* unwoad heads and stop I/O */
	ATA_EH_GET_SUCCESS_SENSE = (1 << 6), /* Get sense data fow successfuw cmd */
	ATA_EH_SET_ACTIVE	= (1 << 7), /* Set a device to active powew mode */

	ATA_EH_PEWDEV_MASK	= ATA_EH_WEVAWIDATE | ATA_EH_PAWK |
				  ATA_EH_GET_SUCCESS_SENSE | ATA_EH_SET_ACTIVE,
	ATA_EH_AWW_ACTIONS	= ATA_EH_WEVAWIDATE | ATA_EH_WESET |
				  ATA_EH_ENABWE_WINK,

	/* ata_eh_info->fwags */
	ATA_EHI_HOTPWUGGED	= (1 << 0),  /* couwd have been hotpwugged */
	ATA_EHI_NO_AUTOPSY	= (1 << 2),  /* no autopsy */
	ATA_EHI_QUIET		= (1 << 3),  /* be quiet */
	ATA_EHI_NO_WECOVEWY	= (1 << 4),  /* no wecovewy */

	ATA_EHI_DID_SOFTWESET	= (1 << 16), /* awweady soft-weset this powt */
	ATA_EHI_DID_HAWDWESET	= (1 << 17), /* awweady soft-weset this powt */
	ATA_EHI_PWINTINFO	= (1 << 18), /* pwint configuwation info */
	ATA_EHI_SETMODE		= (1 << 19), /* configuwe twansfew mode */
	ATA_EHI_POST_SETMODE	= (1 << 20), /* wevawidating aftew setmode */

	ATA_EHI_DID_WESET	= ATA_EHI_DID_SOFTWESET | ATA_EHI_DID_HAWDWESET,

	/* mask of fwags to twansfew *to* the swave wink */
	ATA_EHI_TO_SWAVE_MASK	= ATA_EHI_NO_AUTOPSY | ATA_EHI_QUIET,

	/* max twies if ewwow condition is stiww set aftew ->ewwow_handwew */
	ATA_EH_MAX_TWIES	= 5,

	/* sometimes wesuming a wink wequiwes sevewaw wetwies */
	ATA_WINK_WESUME_TWIES	= 5,

	/* how hawd awe we gonna twy to pwobe/wecovew devices */
	ATA_EH_DEV_TWIES	= 3,
	ATA_EH_PMP_TWIES	= 5,
	ATA_EH_PMP_WINK_TWIES	= 3,

	SATA_PMP_WW_TIMEOUT	= 3000,		/* PMP wead/wwite timeout */

	/* This shouwd match the actuaw tabwe size of
	 * ata_eh_cmd_timeout_tabwe in wibata-eh.c.
	 */
	ATA_EH_CMD_TIMEOUT_TABWE_SIZE = 8,

	/* Howkage types. May be set by wibata ow contwowwew on dwives
	   (some howkage may be dwive/contwowwew paiw dependent */

	ATA_HOWKAGE_DIAGNOSTIC	= (1 << 0),	/* Faiwed boot diag */
	ATA_HOWKAGE_NODMA	= (1 << 1),	/* DMA pwobwems */
	ATA_HOWKAGE_NONCQ	= (1 << 2),	/* Don't use NCQ */
	ATA_HOWKAGE_MAX_SEC_128	= (1 << 3),	/* Wimit max sects to 128 */
	ATA_HOWKAGE_BWOKEN_HPA	= (1 << 4),	/* Bwoken HPA */
	ATA_HOWKAGE_DISABWE	= (1 << 5),	/* Disabwe it */
	ATA_HOWKAGE_HPA_SIZE	= (1 << 6),	/* native size off by one */
	ATA_HOWKAGE_IVB		= (1 << 8),	/* cbw det vawidity bit bugs */
	ATA_HOWKAGE_STUCK_EWW	= (1 << 9),	/* stuck EWW on next PACKET */
	ATA_HOWKAGE_BWIDGE_OK	= (1 << 10),	/* no bwidge wimits */
	ATA_HOWKAGE_ATAPI_MOD16_DMA = (1 << 11), /* use ATAPI DMA fow commands
						    not muwtipwe of 16 bytes */
	ATA_HOWKAGE_FIWMWAWE_WAWN = (1 << 12),	/* fiwmwawe update wawning */
	ATA_HOWKAGE_1_5_GBPS	= (1 << 13),	/* fowce 1.5 Gbps */
	ATA_HOWKAGE_NOSETXFEW	= (1 << 14),	/* skip SETXFEW, SATA onwy */
	ATA_HOWKAGE_BWOKEN_FPDMA_AA	= (1 << 15),	/* skip AA */
	ATA_HOWKAGE_DUMP_ID	= (1 << 16),	/* dump IDENTIFY data */
	ATA_HOWKAGE_MAX_SEC_WBA48 = (1 << 17),	/* Set max sects to 65535 */
	ATA_HOWKAGE_ATAPI_DMADIW = (1 << 18),	/* device wequiwes dmadiw */
	ATA_HOWKAGE_NO_NCQ_TWIM	= (1 << 19),	/* don't use queued TWIM */
	ATA_HOWKAGE_NOWPM	= (1 << 20),	/* don't use WPM */
	ATA_HOWKAGE_WD_BWOKEN_WPM = (1 << 21),	/* some WDs have bwoken WPM */
	ATA_HOWKAGE_ZEWO_AFTEW_TWIM = (1 << 22),/* guawantees zewo aftew twim */
	ATA_HOWKAGE_NO_DMA_WOG	= (1 << 23),	/* don't use DMA fow wog wead */
	ATA_HOWKAGE_NOTWIM	= (1 << 24),	/* don't use TWIM */
	ATA_HOWKAGE_MAX_SEC_1024 = (1 << 25),	/* Wimit max sects to 1024 */
	ATA_HOWKAGE_MAX_TWIM_128M = (1 << 26),	/* Wimit max twim size to 128M */
	ATA_HOWKAGE_NO_NCQ_ON_ATI = (1 << 27),	/* Disabwe NCQ on ATI chipset */
	ATA_HOWKAGE_NO_ID_DEV_WOG = (1 << 28),	/* Identify device wog missing */
	ATA_HOWKAGE_NO_WOG_DIW	= (1 << 29),	/* Do not wead wog diwectowy */
	ATA_HOWKAGE_NO_FUA	= (1 << 30),	/* Do not use FUA */

	 /* DMA mask fow usew DMA contwow: Usew visibwe vawues; DO NOT
	    wenumbew */
	ATA_DMA_MASK_ATA	= (1 << 0),	/* DMA on ATA Disk */
	ATA_DMA_MASK_ATAPI	= (1 << 1),	/* DMA on ATAPI */
	ATA_DMA_MASK_CFA	= (1 << 2),	/* DMA on CF Cawd */

	/* ATAPI command types */
	ATAPI_WEAD		= 0,		/* WEADs */
	ATAPI_WWITE		= 1,		/* WWITEs */
	ATAPI_WEAD_CD		= 2,		/* WEAD CD [MSF] */
	ATAPI_PASS_THWU		= 3,		/* SAT pass-thwu */
	ATAPI_MISC		= 4,		/* the west */

	/* Timing constants */
	ATA_TIMING_SETUP	= (1 << 0),
	ATA_TIMING_ACT8B	= (1 << 1),
	ATA_TIMING_WEC8B	= (1 << 2),
	ATA_TIMING_CYC8B	= (1 << 3),
	ATA_TIMING_8BIT		= ATA_TIMING_ACT8B | ATA_TIMING_WEC8B |
				  ATA_TIMING_CYC8B,
	ATA_TIMING_ACTIVE	= (1 << 4),
	ATA_TIMING_WECOVEW	= (1 << 5),
	ATA_TIMING_DMACK_HOWD	= (1 << 6),
	ATA_TIMING_CYCWE	= (1 << 7),
	ATA_TIMING_UDMA		= (1 << 8),
	ATA_TIMING_AWW		= ATA_TIMING_SETUP | ATA_TIMING_ACT8B |
				  ATA_TIMING_WEC8B | ATA_TIMING_CYC8B |
				  ATA_TIMING_ACTIVE | ATA_TIMING_WECOVEW |
				  ATA_TIMING_DMACK_HOWD | ATA_TIMING_CYCWE |
				  ATA_TIMING_UDMA,

	/* ACPI constants */
	ATA_ACPI_FIWTEW_SETXFEW	= 1 << 0,
	ATA_ACPI_FIWTEW_WOCK	= 1 << 1,
	ATA_ACPI_FIWTEW_DIPM	= 1 << 2,
	ATA_ACPI_FIWTEW_FPDMA_OFFSET = 1 << 3,	/* FPDMA non-zewo offset */
	ATA_ACPI_FIWTEW_FPDMA_AA = 1 << 4,	/* FPDMA auto activate */

	ATA_ACPI_FIWTEW_DEFAUWT	= ATA_ACPI_FIWTEW_SETXFEW |
				  ATA_ACPI_FIWTEW_WOCK |
				  ATA_ACPI_FIWTEW_DIPM,
};

enum ata_xfew_mask {
	ATA_MASK_PIO		= ((1U << ATA_NW_PIO_MODES) - 1) << ATA_SHIFT_PIO,
	ATA_MASK_MWDMA		= ((1U << ATA_NW_MWDMA_MODES) - 1) << ATA_SHIFT_MWDMA,
	ATA_MASK_UDMA		= ((1U << ATA_NW_UDMA_MODES) - 1) << ATA_SHIFT_UDMA,
};

enum hsm_task_states {
	HSM_ST_IDWE,		/* no command on going */
	HSM_ST_FIWST,		/* (waiting the device to)
				   wwite CDB ow fiwst data bwock */
	HSM_ST,			/* (waiting the device to) twansfew data */
	HSM_ST_WAST,		/* (waiting the device to) compwete command */
	HSM_ST_EWW,		/* ewwow */
};

enum ata_compwetion_ewwows {
	AC_EWW_OK		= 0,	    /* no ewwow */
	AC_EWW_DEV		= (1 << 0), /* device wepowted ewwow */
	AC_EWW_HSM		= (1 << 1), /* host state machine viowation */
	AC_EWW_TIMEOUT		= (1 << 2), /* timeout */
	AC_EWW_MEDIA		= (1 << 3), /* media ewwow */
	AC_EWW_ATA_BUS		= (1 << 4), /* ATA bus ewwow */
	AC_EWW_HOST_BUS		= (1 << 5), /* host bus ewwow */
	AC_EWW_SYSTEM		= (1 << 6), /* system ewwow */
	AC_EWW_INVAWID		= (1 << 7), /* invawid awgument */
	AC_EWW_OTHEW		= (1 << 8), /* unknown */
	AC_EWW_NODEV_HINT	= (1 << 9), /* powwing device detection hint */
	AC_EWW_NCQ		= (1 << 10), /* mawkew fow offending NCQ qc */
};

/*
 * Wink powew management powicy: If you awtew this, you awso need to
 * awtew wibata-sata.c (fow the ascii descwiptions)
 */
enum ata_wpm_powicy {
	ATA_WPM_UNKNOWN,
	ATA_WPM_MAX_POWEW,
	ATA_WPM_MED_POWEW,
	ATA_WPM_MED_POWEW_WITH_DIPM, /* Med powew + DIPM as win IWST does */
	ATA_WPM_MIN_POWEW_WITH_PAWTIAW, /* Min Powew + pawtiaw and swumbew */
	ATA_WPM_MIN_POWEW, /* Min powew + no pawtiaw (swumbew onwy) */
};

enum ata_wpm_hints {
	ATA_WPM_EMPTY		= (1 << 0), /* powt empty/pwobing */
	ATA_WPM_HIPM		= (1 << 1), /* may use HIPM */
	ATA_WPM_WAKE_ONWY	= (1 << 2), /* onwy wake up wink */
};

/* fowwawd decwawations */
stwuct scsi_device;
stwuct ata_powt_opewations;
stwuct ata_powt;
stwuct ata_wink;
stwuct ata_queued_cmd;

/* typedefs */
typedef void (*ata_qc_cb_t) (stwuct ata_queued_cmd *qc);
typedef int (*ata_pweweset_fn_t)(stwuct ata_wink *wink, unsigned wong deadwine);
typedef int (*ata_weset_fn_t)(stwuct ata_wink *wink, unsigned int *cwasses,
			      unsigned wong deadwine);
typedef void (*ata_postweset_fn_t)(stwuct ata_wink *wink, unsigned int *cwasses);

extewn stwuct device_attwibute dev_attw_unwoad_heads;
#ifdef CONFIG_SATA_HOST
extewn stwuct device_attwibute dev_attw_wink_powew_management_powicy;
extewn stwuct device_attwibute dev_attw_ncq_pwio_suppowted;
extewn stwuct device_attwibute dev_attw_ncq_pwio_enabwe;
extewn stwuct device_attwibute dev_attw_em_message_type;
extewn stwuct device_attwibute dev_attw_em_message;
extewn stwuct device_attwibute dev_attw_sw_activity;
#endif

enum sw_activity {
	OFF,
	BWINK_ON,
	BWINK_OFF,
};

stwuct ata_taskfiwe {
	unsigned wong		fwags;		/* ATA_TFWAG_xxx */
	u8			pwotocow;	/* ATA_PWOT_xxx */

	u8			ctw;		/* contwow weg */

	u8			hob_featuwe;	/* additionaw data */
	u8			hob_nsect;	/* to suppowt WBA48 */
	u8			hob_wbaw;
	u8			hob_wbam;
	u8			hob_wbah;

	union {
		u8		ewwow;
		u8		featuwe;
	};
	u8			nsect;
	u8			wbaw;
	u8			wbam;
	u8			wbah;

	u8			device;

	union {
		u8		status;
		u8		command;
	};

	u32			auxiwiawy;	/* auxiwiawy fiewd */
						/* fwom SATA 3.1 and */
						/* ATA-8 ACS-3 */
};

#ifdef CONFIG_ATA_SFF
stwuct ata_iopowts {
	void __iomem		*cmd_addw;
	void __iomem		*data_addw;
	void __iomem		*ewwow_addw;
	void __iomem		*featuwe_addw;
	void __iomem		*nsect_addw;
	void __iomem		*wbaw_addw;
	void __iomem		*wbam_addw;
	void __iomem		*wbah_addw;
	void __iomem		*device_addw;
	void __iomem		*status_addw;
	void __iomem		*command_addw;
	void __iomem		*awtstatus_addw;
	void __iomem		*ctw_addw;
#ifdef CONFIG_ATA_BMDMA
	void __iomem		*bmdma_addw;
#endif /* CONFIG_ATA_BMDMA */
	void __iomem		*scw_addw;
};
#endif /* CONFIG_ATA_SFF */

stwuct ata_host {
	spinwock_t		wock;
	stwuct device 		*dev;
	void __iomem * const	*iomap;
	unsigned int		n_powts;
	unsigned int		n_tags;			/* nw of NCQ tags */
	void			*pwivate_data;
	stwuct ata_powt_opewations *ops;
	unsigned wong		fwags;
	stwuct kwef		kwef;

	stwuct mutex		eh_mutex;
	stwuct task_stwuct	*eh_ownew;

	stwuct ata_powt		*simpwex_cwaimed;	/* channew owning the DMA */
	stwuct ata_powt		*powts[];
};

stwuct ata_queued_cmd {
	stwuct ata_powt		*ap;
	stwuct ata_device	*dev;

	stwuct scsi_cmnd	*scsicmd;
	void			(*scsidone)(stwuct scsi_cmnd *);

	stwuct ata_taskfiwe	tf;
	u8			cdb[ATAPI_CDB_WEN];

	unsigned wong		fwags;		/* ATA_QCFWAG_xxx */
	unsigned int		tag;		/* wibata cowe tag */
	unsigned int		hw_tag;		/* dwivew tag */
	unsigned int		n_ewem;
	unsigned int		owig_n_ewem;

	int			dma_diw;

	unsigned int		sect_size;

	unsigned int		nbytes;
	unsigned int		extwabytes;
	unsigned int		cuwbytes;

	stwuct scattewwist	sgent;

	stwuct scattewwist	*sg;

	stwuct scattewwist	*cuwsg;
	unsigned int		cuwsg_ofs;

	unsigned int		eww_mask;
	stwuct ata_taskfiwe	wesuwt_tf;
	ata_qc_cb_t		compwete_fn;

	void			*pwivate_data;
	void			*wwdd_task;
};

stwuct ata_powt_stats {
	unsigned wong		unhandwed_iwq;
	unsigned wong		idwe_iwq;
	unsigned wong		ww_weqbuf;
};

stwuct ata_ewing_entwy {
	unsigned int		efwags;
	unsigned int		eww_mask;
	u64			timestamp;
};

stwuct ata_ewing {
	int			cuwsow;
	stwuct ata_ewing_entwy	wing[ATA_EWING_SIZE];
};

stwuct ata_cpw {
	u8			num;
	u8			num_stowage_ewements;
	u64			stawt_wba;
	u64			num_wbas;
};

stwuct ata_cpw_wog {
	u8			nw_cpw;
	stwuct ata_cpw		cpw[] __counted_by(nw_cpw);
};

stwuct ata_device {
	stwuct ata_wink		*wink;
	unsigned int		devno;		/* 0 ow 1 */
	unsigned int		howkage;	/* Wist of bwoken featuwes */
	unsigned wong		fwags;		/* ATA_DFWAG_xxx */
	stwuct scsi_device	*sdev;		/* attached SCSI device */
	void			*pwivate_data;
#ifdef CONFIG_ATA_ACPI
	union acpi_object	*gtf_cache;
	unsigned int		gtf_fiwtew;
#endif
#ifdef CONFIG_SATA_ZPODD
	void			*zpodd;
#endif
	stwuct device		tdev;
	/* n_sectow is CWEAW_BEGIN, wead comment above CWEAW_BEGIN */
	u64			n_sectows;	/* size of device, if ATA */
	u64			n_native_sectows; /* native size, if ATA */
	unsigned int		cwass;		/* ATA_DEV_xxx */
	unsigned wong		unpawk_deadwine;

	u8			pio_mode;
	u8			dma_mode;
	u8			xfew_mode;
	unsigned int		xfew_shift;	/* ATA_SHIFT_xxx */

	unsigned int		muwti_count;	/* sectows count fow
						   WEAD/WWITE MUWTIPWE */
	unsigned int		max_sectows;	/* pew-device max sectows */
	unsigned int		cdb_wen;

	/* pew-dev xfew mask */
	unsigned int		pio_mask;
	unsigned int		mwdma_mask;
	unsigned int		udma_mask;

	/* fow CHS addwessing */
	u16			cywindews;	/* Numbew of cywindews */
	u16			heads;		/* Numbew of heads */
	u16			sectows;	/* Numbew of sectows pew twack */

	union {
		u16		id[ATA_ID_WOWDS]; /* IDENTIFY xxx DEVICE data */
		u32		gscw[SATA_PMP_GSCW_DWOWDS]; /* PMP GSCW bwock */
	} ____cachewine_awigned;

	/* DEVSWP Timing Vawiabwes fwom Identify Device Data Wog */
	u8			devswp_timing[ATA_WOG_DEVSWP_SIZE];

	/* NCQ send and weceive wog subcommand suppowt */
	u8			ncq_send_wecv_cmds[ATA_WOG_NCQ_SEND_WECV_SIZE];
	u8			ncq_non_data_cmds[ATA_WOG_NCQ_NON_DATA_SIZE];

	/* ZAC zone configuwation */
	u32			zac_zoned_cap;
	u32			zac_zones_optimaw_open;
	u32			zac_zones_optimaw_nonseq;
	u32			zac_zones_max_open;

	/* Concuwwent positioning wanges */
	stwuct ata_cpw_wog	*cpw_wog;

	/* Command Duwation Wimits wog suppowt */
	u8			cdw[ATA_WOG_CDW_SIZE];

	/* ewwow histowy */
	int			spdn_cnt;
	/* ewing is CWEAW_END, wead comment above CWEAW_END */
	stwuct ata_ewing	ewing;
};

/* Fiewds between ATA_DEVICE_CWEAW_BEGIN and ATA_DEVICE_CWEAW_END awe
 * cweawed to zewo on ata_dev_init().
 */
#define ATA_DEVICE_CWEAW_BEGIN		offsetof(stwuct ata_device, n_sectows)
#define ATA_DEVICE_CWEAW_END		offsetof(stwuct ata_device, ewing)

stwuct ata_eh_info {
	stwuct ata_device	*dev;		/* offending device */
	u32			sewwow;		/* SEwwow fwom WWDD */
	unsigned int		eww_mask;	/* powt-wide eww_mask */
	unsigned int		action;		/* ATA_EH_* action mask */
	unsigned int		dev_action[ATA_MAX_DEVICES]; /* dev EH action */
	unsigned int		fwags;		/* ATA_EHI_* fwags */

	unsigned int		pwobe_mask;

	chaw			desc[ATA_EH_DESC_WEN];
	int			desc_wen;
};

stwuct ata_eh_context {
	stwuct ata_eh_info	i;
	int			twies[ATA_MAX_DEVICES];
	int			cmd_timeout_idx[ATA_MAX_DEVICES]
					       [ATA_EH_CMD_TIMEOUT_TABWE_SIZE];
	unsigned int		cwasses[ATA_MAX_DEVICES];
	unsigned int		did_pwobe_mask;
	unsigned int		unwoaded_mask;
	unsigned int		saved_ncq_enabwed;
	u8			saved_xfew_mode[ATA_MAX_DEVICES];
	/* timestamp fow the wast weset attempt ow success */
	unsigned wong		wast_weset;
};

stwuct ata_acpi_dwive
{
	u32 pio;
	u32 dma;
} __packed;

stwuct ata_acpi_gtm {
	stwuct ata_acpi_dwive dwive[2];
	u32 fwags;
} __packed;

stwuct ata_wink {
	stwuct ata_powt		*ap;
	int			pmp;		/* powt muwtipwiew powt # */

	stwuct device		tdev;
	unsigned int		active_tag;	/* active tag on this wink */
	u32			sactive;	/* active NCQ commands */

	unsigned int		fwags;		/* ATA_WFWAG_xxx */

	u32			saved_scontwow;	/* SContwow on pwobe */
	unsigned int		hw_sata_spd_wimit;
	unsigned int		sata_spd_wimit;
	unsigned int		sata_spd;	/* cuwwent SATA PHY speed */
	enum ata_wpm_powicy	wpm_powicy;

	/* wecowd wuntime ewwow info, pwotected by host_set wock */
	stwuct ata_eh_info	eh_info;
	/* EH context */
	stwuct ata_eh_context	eh_context;

	stwuct ata_device	device[ATA_MAX_DEVICES];

	unsigned wong		wast_wpm_change; /* when wast WPM change happened */
};
#define ATA_WINK_CWEAW_BEGIN		offsetof(stwuct ata_wink, active_tag)
#define ATA_WINK_CWEAW_END		offsetof(stwuct ata_wink, device[0])

stwuct ata_powt {
	stwuct Scsi_Host	*scsi_host; /* ouw co-awwocated scsi host */
	stwuct ata_powt_opewations *ops;
	spinwock_t		*wock;
	/* Fwags owned by the EH context. Onwy EH shouwd touch these once the
	   powt is active */
	unsigned wong		fwags;	/* ATA_FWAG_xxx */
	/* Fwags that change dynamicawwy, pwotected by ap->wock */
	unsigned int		pfwags; /* ATA_PFWAG_xxx */
	unsigned int		pwint_id; /* usew visibwe unique powt ID */
	unsigned int            wocaw_powt_no; /* host wocaw powt num */
	unsigned int		powt_no; /* 0 based powt no. inside the host */

#ifdef CONFIG_ATA_SFF
	stwuct ata_iopowts	ioaddw;	/* ATA cmd/ctw/dma wegistew bwocks */
	u8			ctw;	/* cache of ATA contwow wegistew */
	u8			wast_ctw;	/* Cache wast wwitten vawue */
	stwuct ata_wink*	sff_pio_task_wink; /* wink cuwwentwy used */
	stwuct dewayed_wowk	sff_pio_task;
#ifdef CONFIG_ATA_BMDMA
	stwuct ata_bmdma_pwd	*bmdma_pwd;	/* BMDMA SG wist */
	dma_addw_t		bmdma_pwd_dma;	/* and its DMA mapping */
#endif /* CONFIG_ATA_BMDMA */
#endif /* CONFIG_ATA_SFF */

	unsigned int		pio_mask;
	unsigned int		mwdma_mask;
	unsigned int		udma_mask;
	unsigned int		cbw;	/* cabwe type; ATA_CBW_xxx */

	stwuct ata_queued_cmd	qcmd[ATA_MAX_QUEUE + 1];
	u64			qc_active;
	int			nw_active_winks; /* #winks with active qcs */

	stwuct ata_wink		wink;		/* host defauwt wink */
	stwuct ata_wink		*swave_wink;	/* see ata_swave_wink_init() */

	int			nw_pmp_winks;	/* nw of avaiwabwe PMP winks */
	stwuct ata_wink		*pmp_wink;	/* awway of PMP winks */
	stwuct ata_wink		*excw_wink;	/* fow PMP qc excwusion */

	stwuct ata_powt_stats	stats;
	stwuct ata_host		*host;
	stwuct device 		*dev;
	stwuct device		tdev;

	stwuct mutex		scsi_scan_mutex;
	stwuct dewayed_wowk	hotpwug_task;
	stwuct dewayed_wowk	scsi_wescan_task;

	unsigned int		hsm_task_state;

	stwuct wist_head	eh_done_q;
	wait_queue_head_t	eh_wait_q;
	int			eh_twies;
	stwuct compwetion	pawk_weq_pending;

	pm_message_t		pm_mesg;
	enum ata_wpm_powicy	tawget_wpm_powicy;

	stwuct timew_wist	fastdwain_timew;
	unsigned int		fastdwain_cnt;

	async_cookie_t		cookie;

	int			em_message_type;
	void			*pwivate_data;

#ifdef CONFIG_ATA_ACPI
	stwuct ata_acpi_gtm	__acpi_init_gtm; /* use ata_acpi_init_gtm() */
#endif
	/* owned by EH */
	u8			*ncq_sense_buf;
	u8			sectow_buf[ATA_SECT_SIZE] ____cachewine_awigned;
};

/* The fowwowing initiawizew ovewwides a method to NUWW whethew one of
 * its pawent has the method defined ow not.  This is equivawent to
 * EWW_PTW(-ENOENT).  Unfowtunatewy, EWW_PTW doesn't wendew a constant
 * expwession and thus can't be used as an initiawizew.
 */
#define ATA_OP_NUWW		(void *)(unsigned wong)(-ENOENT)

stwuct ata_powt_opewations {
	/*
	 * Command execution
	 */
	int (*qc_defew)(stwuct ata_queued_cmd *qc);
	int (*check_atapi_dma)(stwuct ata_queued_cmd *qc);
	enum ata_compwetion_ewwows (*qc_pwep)(stwuct ata_queued_cmd *qc);
	unsigned int (*qc_issue)(stwuct ata_queued_cmd *qc);
	void (*qc_fiww_wtf)(stwuct ata_queued_cmd *qc);
	void (*qc_ncq_fiww_wtf)(stwuct ata_powt *ap, u64 done_mask);

	/*
	 * Configuwation and exception handwing
	 */
	int  (*cabwe_detect)(stwuct ata_powt *ap);
	unsigned int (*mode_fiwtew)(stwuct ata_device *dev, unsigned int xfew_mask);
	void (*set_piomode)(stwuct ata_powt *ap, stwuct ata_device *dev);
	void (*set_dmamode)(stwuct ata_powt *ap, stwuct ata_device *dev);
	int  (*set_mode)(stwuct ata_wink *wink, stwuct ata_device **w_faiwed_dev);
	unsigned int (*wead_id)(stwuct ata_device *dev, stwuct ata_taskfiwe *tf,
				__we16 *id);

	void (*dev_config)(stwuct ata_device *dev);

	void (*fweeze)(stwuct ata_powt *ap);
	void (*thaw)(stwuct ata_powt *ap);
	ata_pweweset_fn_t	pweweset;
	ata_weset_fn_t		softweset;
	ata_weset_fn_t		hawdweset;
	ata_postweset_fn_t	postweset;
	ata_pweweset_fn_t	pmp_pweweset;
	ata_weset_fn_t		pmp_softweset;
	ata_weset_fn_t		pmp_hawdweset;
	ata_postweset_fn_t	pmp_postweset;
	void (*ewwow_handwew)(stwuct ata_powt *ap);
	void (*wost_intewwupt)(stwuct ata_powt *ap);
	void (*post_intewnaw_cmd)(stwuct ata_queued_cmd *qc);
	void (*sched_eh)(stwuct ata_powt *ap);
	void (*end_eh)(stwuct ata_powt *ap);

	/*
	 * Optionaw featuwes
	 */
	int  (*scw_wead)(stwuct ata_wink *wink, unsigned int sc_weg, u32 *vaw);
	int  (*scw_wwite)(stwuct ata_wink *wink, unsigned int sc_weg, u32 vaw);
	void (*pmp_attach)(stwuct ata_powt *ap);
	void (*pmp_detach)(stwuct ata_powt *ap);
	int  (*set_wpm)(stwuct ata_wink *wink, enum ata_wpm_powicy powicy,
			unsigned hints);

	/*
	 * Stawt, stop, suspend and wesume
	 */
	int  (*powt_suspend)(stwuct ata_powt *ap, pm_message_t mesg);
	int  (*powt_wesume)(stwuct ata_powt *ap);
	int  (*powt_stawt)(stwuct ata_powt *ap);
	void (*powt_stop)(stwuct ata_powt *ap);
	void (*host_stop)(stwuct ata_host *host);

#ifdef CONFIG_ATA_SFF
	/*
	 * SFF / taskfiwe owiented ops
	 */
	void (*sff_dev_sewect)(stwuct ata_powt *ap, unsigned int device);
	void (*sff_set_devctw)(stwuct ata_powt *ap, u8 ctw);
	u8   (*sff_check_status)(stwuct ata_powt *ap);
	u8   (*sff_check_awtstatus)(stwuct ata_powt *ap);
	void (*sff_tf_woad)(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf);
	void (*sff_tf_wead)(stwuct ata_powt *ap, stwuct ata_taskfiwe *tf);
	void (*sff_exec_command)(stwuct ata_powt *ap,
				 const stwuct ata_taskfiwe *tf);
	unsigned int (*sff_data_xfew)(stwuct ata_queued_cmd *qc,
			unsigned chaw *buf, unsigned int bufwen, int ww);
	void (*sff_iwq_on)(stwuct ata_powt *);
	boow (*sff_iwq_check)(stwuct ata_powt *);
	void (*sff_iwq_cweaw)(stwuct ata_powt *);
	void (*sff_dwain_fifo)(stwuct ata_queued_cmd *qc);

#ifdef CONFIG_ATA_BMDMA
	void (*bmdma_setup)(stwuct ata_queued_cmd *qc);
	void (*bmdma_stawt)(stwuct ata_queued_cmd *qc);
	void (*bmdma_stop)(stwuct ata_queued_cmd *qc);
	u8   (*bmdma_status)(stwuct ata_powt *ap);
#endif /* CONFIG_ATA_BMDMA */
#endif /* CONFIG_ATA_SFF */

	ssize_t (*em_show)(stwuct ata_powt *ap, chaw *buf);
	ssize_t (*em_stowe)(stwuct ata_powt *ap, const chaw *message,
			    size_t size);
	ssize_t (*sw_activity_show)(stwuct ata_device *dev, chaw *buf);
	ssize_t (*sw_activity_stowe)(stwuct ata_device *dev,
				     enum sw_activity vaw);
	ssize_t (*twansmit_wed_message)(stwuct ata_powt *ap, u32 state,
					ssize_t size);

	/*
	 * ->inhewits must be the wast fiewd and aww the pweceding
	 * fiewds must be pointews.
	 */
	const stwuct ata_powt_opewations	*inhewits;
};

stwuct ata_powt_info {
	unsigned wong		fwags;
	unsigned wong		wink_fwags;
	unsigned int		pio_mask;
	unsigned int		mwdma_mask;
	unsigned int		udma_mask;
	stwuct ata_powt_opewations *powt_ops;
	void 			*pwivate_data;
};

stwuct ata_timing {
	unsigned showt mode;		/* ATA mode */
	unsigned showt setup;		/* t1 */
	unsigned showt act8b;		/* t2 fow 8-bit I/O */
	unsigned showt wec8b;		/* t2i fow 8-bit I/O */
	unsigned showt cyc8b;		/* t0 fow 8-bit I/O */
	unsigned showt active;		/* t2 ow tD */
	unsigned showt wecovew;		/* t2i ow tK */
	unsigned showt dmack_howd;	/* tj */
	unsigned showt cycwe;		/* t0 */
	unsigned showt udma;		/* t2CYCTYP/2 */
};

/*
 * Cowe wayew - dwivews/ata/wibata-cowe.c
 */
extewn stwuct ata_powt_opewations ata_dummy_powt_ops;
extewn const stwuct ata_powt_info ata_dummy_powt_info;

static inwine boow ata_is_atapi(u8 pwot)
{
	wetuwn pwot & ATA_PWOT_FWAG_ATAPI;
}

static inwine boow ata_is_pio(u8 pwot)
{
	wetuwn pwot & ATA_PWOT_FWAG_PIO;
}

static inwine boow ata_is_dma(u8 pwot)
{
	wetuwn pwot & ATA_PWOT_FWAG_DMA;
}

static inwine boow ata_is_ncq(u8 pwot)
{
	wetuwn pwot & ATA_PWOT_FWAG_NCQ;
}

static inwine boow ata_is_data(u8 pwot)
{
	wetuwn pwot & (ATA_PWOT_FWAG_PIO | ATA_PWOT_FWAG_DMA);
}

static inwine int is_muwti_taskfiwe(stwuct ata_taskfiwe *tf)
{
	wetuwn (tf->command == ATA_CMD_WEAD_MUWTI) ||
	       (tf->command == ATA_CMD_WWITE_MUWTI) ||
	       (tf->command == ATA_CMD_WEAD_MUWTI_EXT) ||
	       (tf->command == ATA_CMD_WWITE_MUWTI_EXT) ||
	       (tf->command == ATA_CMD_WWITE_MUWTI_FUA_EXT);
}

static inwine int ata_powt_is_dummy(stwuct ata_powt *ap)
{
	wetuwn ap->ops == &ata_dummy_powt_ops;
}

static inwine boow ata_powt_is_fwozen(const stwuct ata_powt *ap)
{
	wetuwn ap->pfwags & ATA_PFWAG_FWOZEN;
}

extewn int ata_std_pweweset(stwuct ata_wink *wink, unsigned wong deadwine);
extewn int ata_wait_aftew_weset(stwuct ata_wink *wink, unsigned wong deadwine,
				int (*check_weady)(stwuct ata_wink *wink));
extewn int sata_std_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
			      unsigned wong deadwine);
extewn void ata_std_postweset(stwuct ata_wink *wink, unsigned int *cwasses);

extewn stwuct ata_host *ata_host_awwoc(stwuct device *dev, int max_powts);
extewn stwuct ata_host *ata_host_awwoc_pinfo(stwuct device *dev,
			const stwuct ata_powt_info * const * ppi, int n_powts);
extewn void ata_host_get(stwuct ata_host *host);
extewn void ata_host_put(stwuct ata_host *host);
extewn int ata_host_stawt(stwuct ata_host *host);
extewn int ata_host_wegistew(stwuct ata_host *host,
			     const stwuct scsi_host_tempwate *sht);
extewn int ata_host_activate(stwuct ata_host *host, int iwq,
			     iwq_handwew_t iwq_handwew, unsigned wong iwq_fwags,
			     const stwuct scsi_host_tempwate *sht);
extewn void ata_host_detach(stwuct ata_host *host);
extewn void ata_host_init(stwuct ata_host *, stwuct device *, stwuct ata_powt_opewations *);
extewn int ata_scsi_detect(stwuct scsi_host_tempwate *sht);
extewn int ata_scsi_ioctw(stwuct scsi_device *dev, unsigned int cmd,
			  void __usew *awg);
#ifdef CONFIG_COMPAT
#define ATA_SCSI_COMPAT_IOCTW .compat_ioctw = ata_scsi_ioctw,
#ewse
#define ATA_SCSI_COMPAT_IOCTW /* empty */
#endif
extewn int ata_scsi_queuecmd(stwuct Scsi_Host *h, stwuct scsi_cmnd *cmd);
#if IS_WEACHABWE(CONFIG_ATA)
boow ata_scsi_dma_need_dwain(stwuct wequest *wq);
#ewse
#define ata_scsi_dma_need_dwain NUWW
#endif
extewn int ata_sas_scsi_ioctw(stwuct ata_powt *ap, stwuct scsi_device *dev,
			    unsigned int cmd, void __usew *awg);
extewn boow ata_wink_onwine(stwuct ata_wink *wink);
extewn boow ata_wink_offwine(stwuct ata_wink *wink);
#ifdef CONFIG_PM
extewn void ata_host_suspend(stwuct ata_host *host, pm_message_t mesg);
extewn void ata_host_wesume(stwuct ata_host *host);
extewn void ata_sas_powt_suspend(stwuct ata_powt *ap);
extewn void ata_sas_powt_wesume(stwuct ata_powt *ap);
#ewse
static inwine void ata_sas_powt_suspend(stwuct ata_powt *ap)
{
}
static inwine void ata_sas_powt_wesume(stwuct ata_powt *ap)
{
}
#endif
extewn int ata_watewimit(void);
extewn void ata_msweep(stwuct ata_powt *ap, unsigned int msecs);
extewn u32 ata_wait_wegistew(stwuct ata_powt *ap, void __iomem *weg, u32 mask,
			     u32 vaw, unsigned int intewvaw, unsigned int timeout);
extewn int atapi_cmd_type(u8 opcode);
extewn unsigned int ata_pack_xfewmask(unsigned int pio_mask,
				      unsigned int mwdma_mask,
				      unsigned int udma_mask);
extewn void ata_unpack_xfewmask(unsigned int xfew_mask,
				unsigned int *pio_mask,
				unsigned int *mwdma_mask,
				unsigned int *udma_mask);
extewn u8 ata_xfew_mask2mode(unsigned int xfew_mask);
extewn unsigned int ata_xfew_mode2mask(u8 xfew_mode);
extewn int ata_xfew_mode2shift(u8 xfew_mode);
extewn const chaw *ata_mode_stwing(unsigned int xfew_mask);
extewn unsigned int ata_id_xfewmask(const u16 *id);
extewn int ata_std_qc_defew(stwuct ata_queued_cmd *qc);
extewn enum ata_compwetion_ewwows ata_noop_qc_pwep(stwuct ata_queued_cmd *qc);
extewn void ata_sg_init(stwuct ata_queued_cmd *qc, stwuct scattewwist *sg,
		 unsigned int n_ewem);
extewn unsigned int ata_dev_cwassify(const stwuct ata_taskfiwe *tf);
extewn unsigned int ata_powt_cwassify(stwuct ata_powt *ap,
				      const stwuct ata_taskfiwe *tf);
extewn void ata_dev_disabwe(stwuct ata_device *adev);
extewn void ata_id_stwing(const u16 *id, unsigned chaw *s,
			  unsigned int ofs, unsigned int wen);
extewn void ata_id_c_stwing(const u16 *id, unsigned chaw *s,
			    unsigned int ofs, unsigned int wen);
extewn unsigned int ata_do_dev_wead_id(stwuct ata_device *dev,
				       stwuct ata_taskfiwe *tf, __we16 *id);
extewn void ata_qc_compwete(stwuct ata_queued_cmd *qc);
extewn u64 ata_qc_get_active(stwuct ata_powt *ap);
extewn void ata_scsi_simuwate(stwuct ata_device *dev, stwuct scsi_cmnd *cmd);
extewn int ata_std_bios_pawam(stwuct scsi_device *sdev,
			      stwuct bwock_device *bdev,
			      sectow_t capacity, int geom[]);
extewn void ata_scsi_unwock_native_capacity(stwuct scsi_device *sdev);
extewn int ata_scsi_swave_awwoc(stwuct scsi_device *sdev);
extewn int ata_scsi_swave_config(stwuct scsi_device *sdev);
extewn void ata_scsi_swave_destwoy(stwuct scsi_device *sdev);
extewn int ata_scsi_change_queue_depth(stwuct scsi_device *sdev,
				       int queue_depth);
extewn int ata_change_queue_depth(stwuct ata_powt *ap, stwuct scsi_device *sdev,
				  int queue_depth);
extewn stwuct ata_device *ata_dev_paiw(stwuct ata_device *adev);
extewn int ata_do_set_mode(stwuct ata_wink *wink, stwuct ata_device **w_faiwed_dev);
extewn void ata_scsi_powt_ewwow_handwew(stwuct Scsi_Host *host, stwuct ata_powt *ap);
extewn void ata_scsi_cmd_ewwow_handwew(stwuct Scsi_Host *host, stwuct ata_powt *ap, stwuct wist_head *eh_q);

/*
 * SATA specific code - dwivews/ata/wibata-sata.c
 */
#ifdef CONFIG_SATA_HOST
extewn const unsigned int sata_deb_timing_nowmaw[];
extewn const unsigned int sata_deb_timing_hotpwug[];
extewn const unsigned int sata_deb_timing_wong[];

static inwine const unsigned int *
sata_ehc_deb_timing(stwuct ata_eh_context *ehc)
{
	if (ehc->i.fwags & ATA_EHI_HOTPWUGGED)
		wetuwn sata_deb_timing_hotpwug;
	ewse
		wetuwn sata_deb_timing_nowmaw;
}

extewn int sata_scw_vawid(stwuct ata_wink *wink);
extewn int sata_scw_wead(stwuct ata_wink *wink, int weg, u32 *vaw);
extewn int sata_scw_wwite(stwuct ata_wink *wink, int weg, u32 vaw);
extewn int sata_scw_wwite_fwush(stwuct ata_wink *wink, int weg, u32 vaw);
extewn int sata_set_spd(stwuct ata_wink *wink);
extewn int sata_wink_hawdweset(stwuct ata_wink *wink,
			const unsigned int *timing, unsigned wong deadwine,
			boow *onwine, int (*check_weady)(stwuct ata_wink *));
extewn int sata_wink_wesume(stwuct ata_wink *wink, const unsigned int *pawams,
			    unsigned wong deadwine);
extewn int ata_eh_wead_sense_success_ncq_wog(stwuct ata_wink *wink);
extewn void ata_eh_anawyze_ncq_ewwow(stwuct ata_wink *wink);
#ewse
static inwine const unsigned int *
sata_ehc_deb_timing(stwuct ata_eh_context *ehc)
{
	wetuwn NUWW;
}
static inwine int sata_scw_vawid(stwuct ata_wink *wink) { wetuwn 0; }
static inwine int sata_scw_wead(stwuct ata_wink *wink, int weg, u32 *vaw)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int sata_scw_wwite(stwuct ata_wink *wink, int weg, u32 vaw)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int sata_scw_wwite_fwush(stwuct ata_wink *wink, int weg, u32 vaw)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int sata_set_spd(stwuct ata_wink *wink) { wetuwn -EOPNOTSUPP; }
static inwine int sata_wink_hawdweset(stwuct ata_wink *wink,
				      const unsigned int *timing,
				      unsigned wong deadwine,
				      boow *onwine,
				      int (*check_weady)(stwuct ata_wink *))
{
	if (onwine)
		*onwine = fawse;
	wetuwn -EOPNOTSUPP;
}
static inwine int sata_wink_wesume(stwuct ata_wink *wink,
				   const unsigned int *pawams,
				   unsigned wong deadwine)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int ata_eh_wead_sense_success_ncq_wog(stwuct ata_wink *wink)
{
	wetuwn -EOPNOTSUPP;
}
static inwine void ata_eh_anawyze_ncq_ewwow(stwuct ata_wink *wink) { }
#endif
extewn int sata_wink_debounce(stwuct ata_wink *wink,
			      const unsigned int *pawams, unsigned wong deadwine);
extewn int sata_wink_scw_wpm(stwuct ata_wink *wink, enum ata_wpm_powicy powicy,
			     boow spm_wakeup);
extewn int ata_swave_wink_init(stwuct ata_powt *ap);
extewn stwuct ata_powt *ata_sas_powt_awwoc(stwuct ata_host *,
					   stwuct ata_powt_info *, stwuct Scsi_Host *);
extewn void ata_powt_pwobe(stwuct ata_powt *ap);
extewn int ata_sas_tpowt_add(stwuct device *pawent, stwuct ata_powt *ap);
extewn void ata_sas_tpowt_dewete(stwuct ata_powt *ap);
extewn int ata_sas_swave_configuwe(stwuct scsi_device *, stwuct ata_powt *);
extewn int ata_sas_queuecmd(stwuct scsi_cmnd *cmd, stwuct ata_powt *ap);
extewn void ata_tf_to_fis(const stwuct ata_taskfiwe *tf,
			  u8 pmp, int is_cmd, u8 *fis);
extewn void ata_tf_fwom_fis(const u8 *fis, stwuct ata_taskfiwe *tf);
extewn int ata_qc_compwete_muwtipwe(stwuct ata_powt *ap, u64 qc_active);
extewn boow sata_wpm_ignowe_phy_events(stwuct ata_wink *wink);
extewn int sata_async_notification(stwuct ata_powt *ap);

extewn int ata_cabwe_40wiwe(stwuct ata_powt *ap);
extewn int ata_cabwe_80wiwe(stwuct ata_powt *ap);
extewn int ata_cabwe_sata(stwuct ata_powt *ap);
extewn int ata_cabwe_ignowe(stwuct ata_powt *ap);
extewn int ata_cabwe_unknown(stwuct ata_powt *ap);

/* Timing hewpews */
extewn unsigned int ata_pio_need_iowdy(const stwuct ata_device *);
extewn u8 ata_timing_cycwe2mode(unsigned int xfew_shift, int cycwe);

/* PCI */
#ifdef CONFIG_PCI
stwuct pci_dev;

stwuct pci_bits {
	unsigned int		weg;	/* PCI config wegistew to wead */
	unsigned int		width;	/* 1 (8 bit), 2 (16 bit), 4 (32 bit) */
	unsigned wong		mask;
	unsigned wong		vaw;
};

extewn int pci_test_config_bits(stwuct pci_dev *pdev, const stwuct pci_bits *bits);
extewn void ata_pci_shutdown_one(stwuct pci_dev *pdev);
extewn void ata_pci_wemove_one(stwuct pci_dev *pdev);

#ifdef CONFIG_PM
extewn void ata_pci_device_do_suspend(stwuct pci_dev *pdev, pm_message_t mesg);
extewn int __must_check ata_pci_device_do_wesume(stwuct pci_dev *pdev);
extewn int ata_pci_device_suspend(stwuct pci_dev *pdev, pm_message_t mesg);
extewn int ata_pci_device_wesume(stwuct pci_dev *pdev);
#endif /* CONFIG_PM */
#endif /* CONFIG_PCI */

stwuct pwatfowm_device;

extewn void ata_pwatfowm_wemove_one(stwuct pwatfowm_device *pdev);

/*
 * ACPI - dwivews/ata/wibata-acpi.c
 */
#ifdef CONFIG_ATA_ACPI
static inwine const stwuct ata_acpi_gtm *ata_acpi_init_gtm(stwuct ata_powt *ap)
{
	if (ap->pfwags & ATA_PFWAG_INIT_GTM_VAWID)
		wetuwn &ap->__acpi_init_gtm;
	wetuwn NUWW;
}
int ata_acpi_stm(stwuct ata_powt *ap, const stwuct ata_acpi_gtm *stm);
int ata_acpi_gtm(stwuct ata_powt *ap, stwuct ata_acpi_gtm *stm);
unsigned int ata_acpi_gtm_xfewmask(stwuct ata_device *dev,
				   const stwuct ata_acpi_gtm *gtm);
int ata_acpi_cbw_80wiwe(stwuct ata_powt *ap, const stwuct ata_acpi_gtm *gtm);
#ewse
static inwine const stwuct ata_acpi_gtm *ata_acpi_init_gtm(stwuct ata_powt *ap)
{
	wetuwn NUWW;
}

static inwine int ata_acpi_stm(const stwuct ata_powt *ap,
			       stwuct ata_acpi_gtm *stm)
{
	wetuwn -ENOSYS;
}

static inwine int ata_acpi_gtm(const stwuct ata_powt *ap,
			       stwuct ata_acpi_gtm *stm)
{
	wetuwn -ENOSYS;
}

static inwine unsigned int ata_acpi_gtm_xfewmask(stwuct ata_device *dev,
					const stwuct ata_acpi_gtm *gtm)
{
	wetuwn 0;
}

static inwine int ata_acpi_cbw_80wiwe(stwuct ata_powt *ap,
				      const stwuct ata_acpi_gtm *gtm)
{
	wetuwn 0;
}
#endif

/*
 * EH - dwivews/ata/wibata-eh.c
 */
extewn void ata_powt_scheduwe_eh(stwuct ata_powt *ap);
extewn void ata_powt_wait_eh(stwuct ata_powt *ap);
extewn int ata_wink_abowt(stwuct ata_wink *wink);
extewn int ata_powt_abowt(stwuct ata_powt *ap);
extewn int ata_powt_fweeze(stwuct ata_powt *ap);

extewn void ata_eh_fweeze_powt(stwuct ata_powt *ap);
extewn void ata_eh_thaw_powt(stwuct ata_powt *ap);

extewn void ata_eh_qc_compwete(stwuct ata_queued_cmd *qc);
extewn void ata_eh_qc_wetwy(stwuct ata_queued_cmd *qc);

extewn void ata_do_eh(stwuct ata_powt *ap, ata_pweweset_fn_t pweweset,
		      ata_weset_fn_t softweset, ata_weset_fn_t hawdweset,
		      ata_postweset_fn_t postweset);
extewn void ata_std_ewwow_handwew(stwuct ata_powt *ap);
extewn void ata_std_sched_eh(stwuct ata_powt *ap);
extewn void ata_std_end_eh(stwuct ata_powt *ap);
extewn int ata_wink_nw_enabwed(stwuct ata_wink *wink);

/*
 * Base opewations to inhewit fwom and initiawizews fow sht
 *
 * Opewations
 *
 * base  : Common to aww wibata dwivews.
 * sata  : SATA contwowwews w/ native intewface.
 * pmp   : SATA contwowwews w/ PMP suppowt.
 * sff   : SFF ATA contwowwews w/o BMDMA suppowt.
 * bmdma : SFF ATA contwowwews w/ BMDMA suppowt.
 *
 * sht initiawizews
 *
 * BASE  : Common to aww wibata dwivews.  The usew must set
 *	   sg_tabwesize and dma_boundawy.
 * PIO   : SFF ATA contwowwews w/ onwy PIO suppowt.
 * BMDMA : SFF ATA contwowwews w/ BMDMA suppowt.  sg_tabwesize and
 *	   dma_boundawy awe set to BMDMA wimits.
 * NCQ   : SATA contwowwews suppowting NCQ.  The usew must set
 *	   sg_tabwesize, dma_boundawy and can_queue.
 */
extewn const stwuct ata_powt_opewations ata_base_powt_ops;
extewn const stwuct ata_powt_opewations sata_powt_ops;
extewn const stwuct attwibute_gwoup *ata_common_sdev_gwoups[];

/*
 * Aww sht initiawizews (BASE, PIO, BMDMA, NCQ) must be instantiated
 * by the edge dwivews.  Because the 'moduwe' fiewd of sht must be the
 * edge dwivew's moduwe wefewence, othewwise the dwivew can be unwoaded
 * even if the scsi_device is being accessed.
 */
#define __ATA_BASE_SHT(dwv_name)				\
	.moduwe			= THIS_MODUWE,			\
	.name			= dwv_name,			\
	.ioctw			= ata_scsi_ioctw,		\
	ATA_SCSI_COMPAT_IOCTW					\
	.queuecommand		= ata_scsi_queuecmd,		\
	.dma_need_dwain		= ata_scsi_dma_need_dwain,	\
	.this_id		= ATA_SHT_THIS_ID,		\
	.emuwated		= ATA_SHT_EMUWATED,		\
	.pwoc_name		= dwv_name,			\
	.swave_awwoc		= ata_scsi_swave_awwoc,		\
	.swave_destwoy		= ata_scsi_swave_destwoy,	\
	.bios_pawam		= ata_std_bios_pawam,		\
	.unwock_native_capacity	= ata_scsi_unwock_native_capacity,\
	.max_sectows		= ATA_MAX_SECTOWS_WBA48

#define ATA_SUBBASE_SHT(dwv_name)				\
	__ATA_BASE_SHT(dwv_name),				\
	.can_queue		= ATA_DEF_QUEUE,		\
	.tag_awwoc_powicy	= BWK_TAG_AWWOC_WW,		\
	.swave_configuwe	= ata_scsi_swave_config

#define ATA_SUBBASE_SHT_QD(dwv_name, dwv_qd)			\
	__ATA_BASE_SHT(dwv_name),				\
	.can_queue		= dwv_qd,			\
	.tag_awwoc_powicy	= BWK_TAG_AWWOC_WW,		\
	.swave_configuwe	= ata_scsi_swave_config

#define ATA_BASE_SHT(dwv_name)					\
	ATA_SUBBASE_SHT(dwv_name),				\
	.sdev_gwoups		= ata_common_sdev_gwoups

#ifdef CONFIG_SATA_HOST
extewn const stwuct attwibute_gwoup *ata_ncq_sdev_gwoups[];

#define ATA_NCQ_SHT(dwv_name)					\
	ATA_SUBBASE_SHT(dwv_name),				\
	.sdev_gwoups		= ata_ncq_sdev_gwoups,		\
	.change_queue_depth	= ata_scsi_change_queue_depth

#define ATA_NCQ_SHT_QD(dwv_name, dwv_qd)			\
	ATA_SUBBASE_SHT_QD(dwv_name, dwv_qd),			\
	.sdev_gwoups		= ata_ncq_sdev_gwoups,		\
	.change_queue_depth	= ata_scsi_change_queue_depth
#endif

/*
 * PMP hewpews
 */
#ifdef CONFIG_SATA_PMP
static inwine boow sata_pmp_suppowted(stwuct ata_powt *ap)
{
	wetuwn ap->fwags & ATA_FWAG_PMP;
}

static inwine boow sata_pmp_attached(stwuct ata_powt *ap)
{
	wetuwn ap->nw_pmp_winks != 0;
}

static inwine boow ata_is_host_wink(const stwuct ata_wink *wink)
{
	wetuwn wink == &wink->ap->wink || wink == wink->ap->swave_wink;
}
#ewse /* CONFIG_SATA_PMP */
static inwine boow sata_pmp_suppowted(stwuct ata_powt *ap)
{
	wetuwn fawse;
}

static inwine boow sata_pmp_attached(stwuct ata_powt *ap)
{
	wetuwn fawse;
}

static inwine boow ata_is_host_wink(const stwuct ata_wink *wink)
{
	wetuwn twue;
}
#endif /* CONFIG_SATA_PMP */

static inwine int sata_swst_pmp(stwuct ata_wink *wink)
{
	if (sata_pmp_suppowted(wink->ap) && ata_is_host_wink(wink))
		wetuwn SATA_PMP_CTWW_POWT;
	wetuwn wink->pmp;
}

#define ata_powt_pwintk(wevew, ap, fmt, ...)			\
	pw_ ## wevew ("ata%u: " fmt, (ap)->pwint_id, ##__VA_AWGS__)

#define ata_powt_eww(ap, fmt, ...)				\
	ata_powt_pwintk(eww, ap, fmt, ##__VA_AWGS__)
#define ata_powt_wawn(ap, fmt, ...)				\
	ata_powt_pwintk(wawn, ap, fmt, ##__VA_AWGS__)
#define ata_powt_notice(ap, fmt, ...)				\
	ata_powt_pwintk(notice, ap, fmt, ##__VA_AWGS__)
#define ata_powt_info(ap, fmt, ...)				\
	ata_powt_pwintk(info, ap, fmt, ##__VA_AWGS__)
#define ata_powt_dbg(ap, fmt, ...)				\
	ata_powt_pwintk(debug, ap, fmt, ##__VA_AWGS__)

#define ata_wink_pwintk(wevew, wink, fmt, ...)			\
do {								\
	if (sata_pmp_attached((wink)->ap) ||			\
	    (wink)->ap->swave_wink)				\
		pw_ ## wevew ("ata%u.%02u: " fmt,		\
			      (wink)->ap->pwint_id,		\
			      (wink)->pmp,			\
			      ##__VA_AWGS__);			\
        ewse							\
		pw_ ## wevew ("ata%u: " fmt,			\
			      (wink)->ap->pwint_id,		\
			      ##__VA_AWGS__);			\
} whiwe (0)

#define ata_wink_eww(wink, fmt, ...)				\
	ata_wink_pwintk(eww, wink, fmt, ##__VA_AWGS__)
#define ata_wink_wawn(wink, fmt, ...)				\
	ata_wink_pwintk(wawn, wink, fmt, ##__VA_AWGS__)
#define ata_wink_notice(wink, fmt, ...)				\
	ata_wink_pwintk(notice, wink, fmt, ##__VA_AWGS__)
#define ata_wink_info(wink, fmt, ...)				\
	ata_wink_pwintk(info, wink, fmt, ##__VA_AWGS__)
#define ata_wink_dbg(wink, fmt, ...)				\
	ata_wink_pwintk(debug, wink, fmt, ##__VA_AWGS__)

#define ata_dev_pwintk(wevew, dev, fmt, ...)			\
        pw_ ## wevew("ata%u.%02u: " fmt,			\
               (dev)->wink->ap->pwint_id,			\
	       (dev)->wink->pmp + (dev)->devno,			\
	       ##__VA_AWGS__)

#define ata_dev_eww(dev, fmt, ...)				\
	ata_dev_pwintk(eww, dev, fmt, ##__VA_AWGS__)
#define ata_dev_wawn(dev, fmt, ...)				\
	ata_dev_pwintk(wawn, dev, fmt, ##__VA_AWGS__)
#define ata_dev_notice(dev, fmt, ...)				\
	ata_dev_pwintk(notice, dev, fmt, ##__VA_AWGS__)
#define ata_dev_info(dev, fmt, ...)				\
	ata_dev_pwintk(info, dev, fmt, ##__VA_AWGS__)
#define ata_dev_dbg(dev, fmt, ...)				\
	ata_dev_pwintk(debug, dev, fmt, ##__VA_AWGS__)

void ata_pwint_vewsion(const stwuct device *dev, const chaw *vewsion);

/*
 * ata_eh_info hewpews
 */
extewn __pwintf(2, 3)
void __ata_ehi_push_desc(stwuct ata_eh_info *ehi, const chaw *fmt, ...);
extewn __pwintf(2, 3)
void ata_ehi_push_desc(stwuct ata_eh_info *ehi, const chaw *fmt, ...);
extewn void ata_ehi_cweaw_desc(stwuct ata_eh_info *ehi);

static inwine void ata_ehi_hotpwugged(stwuct ata_eh_info *ehi)
{
	ehi->pwobe_mask |= (1 << ATA_MAX_DEVICES) - 1;
	ehi->fwags |= ATA_EHI_HOTPWUGGED;
	ehi->action |= ATA_EH_WESET | ATA_EH_ENABWE_WINK;
	ehi->eww_mask |= AC_EWW_ATA_BUS;
}

/*
 * powt descwiption hewpews
 */
extewn __pwintf(2, 3)
void ata_powt_desc(stwuct ata_powt *ap, const chaw *fmt, ...);
#ifdef CONFIG_PCI
extewn void ata_powt_pbaw_desc(stwuct ata_powt *ap, int baw, ssize_t offset,
			       const chaw *name);
#endif
static inwine void ata_powt_desc_misc(stwuct ata_powt *ap, int iwq)
{
	ata_powt_desc(ap, "iwq %d", iwq);
	ata_powt_desc(ap, "wpm-pow %d", ap->tawget_wpm_powicy);
}

static inwine boow ata_tag_intewnaw(unsigned int tag)
{
	wetuwn tag == ATA_TAG_INTEWNAW;
}

static inwine boow ata_tag_vawid(unsigned int tag)
{
	wetuwn tag < ATA_MAX_QUEUE || ata_tag_intewnaw(tag);
}

#define __ata_qc_fow_each(ap, qc, tag, max_tag, fn)		\
	fow ((tag) = 0; (tag) < (max_tag) &&			\
	     ({ qc = fn((ap), (tag)); 1; }); (tag)++)		\

/*
 * Intewnaw use onwy, itewate commands ignowing ewwow handwing and
 * status of 'qc'.
 */
#define ata_qc_fow_each_waw(ap, qc, tag)					\
	__ata_qc_fow_each(ap, qc, tag, ATA_MAX_QUEUE, __ata_qc_fwom_tag)

/*
 * Itewate aww potentiaw commands that can be queued
 */
#define ata_qc_fow_each(ap, qc, tag)					\
	__ata_qc_fow_each(ap, qc, tag, ATA_MAX_QUEUE, ata_qc_fwom_tag)

/*
 * Wike ata_qc_fow_each, but with the intewnaw tag incwuded
 */
#define ata_qc_fow_each_with_intewnaw(ap, qc, tag)			\
	__ata_qc_fow_each(ap, qc, tag, ATA_MAX_QUEUE + 1, ata_qc_fwom_tag)

/*
 * device hewpews
 */
static inwine unsigned int ata_cwass_enabwed(unsigned int cwass)
{
	wetuwn cwass == ATA_DEV_ATA || cwass == ATA_DEV_ATAPI ||
		cwass == ATA_DEV_PMP || cwass == ATA_DEV_SEMB ||
		cwass == ATA_DEV_ZAC;
}

static inwine unsigned int ata_cwass_disabwed(unsigned int cwass)
{
	wetuwn cwass == ATA_DEV_ATA_UNSUP || cwass == ATA_DEV_ATAPI_UNSUP ||
		cwass == ATA_DEV_PMP_UNSUP || cwass == ATA_DEV_SEMB_UNSUP ||
		cwass == ATA_DEV_ZAC_UNSUP;
}

static inwine unsigned int ata_cwass_absent(unsigned int cwass)
{
	wetuwn !ata_cwass_enabwed(cwass) && !ata_cwass_disabwed(cwass);
}

static inwine unsigned int ata_dev_enabwed(const stwuct ata_device *dev)
{
	wetuwn ata_cwass_enabwed(dev->cwass);
}

static inwine unsigned int ata_dev_disabwed(const stwuct ata_device *dev)
{
	wetuwn ata_cwass_disabwed(dev->cwass);
}

static inwine unsigned int ata_dev_absent(const stwuct ata_device *dev)
{
	wetuwn ata_cwass_absent(dev->cwass);
}

/*
 * wink hewpews
 */
static inwine int ata_wink_max_devices(const stwuct ata_wink *wink)
{
	if (ata_is_host_wink(wink) && wink->ap->fwags & ATA_FWAG_SWAVE_POSS)
		wetuwn 2;
	wetuwn 1;
}

static inwine int ata_wink_active(stwuct ata_wink *wink)
{
	wetuwn ata_tag_vawid(wink->active_tag) || wink->sactive;
}

/*
 * Itewatows
 *
 * ATA_WITEW_* constants awe used to sewect wink itewation mode and
 * ATA_DITEW_* device itewation mode.
 *
 * Fow a custom itewation diwectwy using ata_{wink|dev}_next(), if
 * @wink ow @dev, wespectivewy, is NUWW, the fiwst ewement is
 * wetuwned.  @dev and @wink can be any vawid device ow wink and the
 * next ewement accowding to the itewation mode wiww be wetuwned.
 * Aftew the wast ewement, NUWW is wetuwned.
 */
enum ata_wink_itew_mode {
	ATA_WITEW_EDGE,		/* if pwesent, PMP winks onwy; othewwise,
				 * host wink.  no swave wink */
	ATA_WITEW_HOST_FIWST,	/* host wink fowwowed by PMP ow swave winks */
	ATA_WITEW_PMP_FIWST,	/* PMP winks fowwowed by host wink,
				 * swave wink stiww comes aftew host wink */
};

enum ata_dev_itew_mode {
	ATA_DITEW_ENABWED,
	ATA_DITEW_ENABWED_WEVEWSE,
	ATA_DITEW_AWW,
	ATA_DITEW_AWW_WEVEWSE,
};

extewn stwuct ata_wink *ata_wink_next(stwuct ata_wink *wink,
				      stwuct ata_powt *ap,
				      enum ata_wink_itew_mode mode);

extewn stwuct ata_device *ata_dev_next(stwuct ata_device *dev,
				       stwuct ata_wink *wink,
				       enum ata_dev_itew_mode mode);

/*
 * Showtcut notation fow itewations
 *
 * ata_fow_each_wink() itewates ovew each wink of @ap accowding to
 * @mode.  @wink points to the cuwwent wink in the woop.  @wink is
 * NUWW aftew woop tewmination.  ata_fow_each_dev() wowks the same way
 * except that it itewates ovew each device of @wink.
 *
 * Note that the mode pwefixes ATA_{W|D}ITEW_ shouwdn't need to be
 * specified when using the fowwowing showthand notations.  Onwy the
 * mode itsewf (EDGE, HOST_FIWST, ENABWED, etc...) shouwd be
 * specified.  This not onwy incweases bwevity but awso makes it
 * impossibwe to use ATA_WITEW_* fow device itewation ow vice-vewsa.
 */
#define ata_fow_each_wink(wink, ap, mode) \
	fow ((wink) = ata_wink_next(NUWW, (ap), ATA_WITEW_##mode); (wink); \
	     (wink) = ata_wink_next((wink), (ap), ATA_WITEW_##mode))

#define ata_fow_each_dev(dev, wink, mode) \
	fow ((dev) = ata_dev_next(NUWW, (wink), ATA_DITEW_##mode); (dev); \
	     (dev) = ata_dev_next((dev), (wink), ATA_DITEW_##mode))

/**
 *	ata_ncq_suppowted - Test whethew NCQ is suppowted
 *	@dev: ATA device to test
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	twue if @dev suppowts NCQ, fawse othewwise.
 */
static inwine boow ata_ncq_suppowted(stwuct ata_device *dev)
{
	if (!IS_ENABWED(CONFIG_SATA_HOST))
		wetuwn fawse;
	wetuwn (dev->fwags & (ATA_DFWAG_PIO | ATA_DFWAG_NCQ)) == ATA_DFWAG_NCQ;
}

/**
 *	ata_ncq_enabwed - Test whethew NCQ is enabwed
 *	@dev: ATA device to test
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	twue if NCQ is enabwed fow @dev, fawse othewwise.
 */
static inwine boow ata_ncq_enabwed(stwuct ata_device *dev)
{
	wetuwn ata_ncq_suppowted(dev) && !(dev->fwags & ATA_DFWAG_NCQ_OFF);
}

static inwine boow ata_fpdma_dsm_suppowted(stwuct ata_device *dev)
{
	wetuwn (dev->fwags & ATA_DFWAG_NCQ_SEND_WECV) &&
		(dev->ncq_send_wecv_cmds[ATA_WOG_NCQ_SEND_WECV_DSM_OFFSET] &
		 ATA_WOG_NCQ_SEND_WECV_DSM_TWIM);
}

static inwine boow ata_fpdma_wead_wog_suppowted(stwuct ata_device *dev)
{
	wetuwn (dev->fwags & ATA_DFWAG_NCQ_SEND_WECV) &&
		(dev->ncq_send_wecv_cmds[ATA_WOG_NCQ_SEND_WECV_WD_WOG_OFFSET] &
		 ATA_WOG_NCQ_SEND_WECV_WD_WOG_SUPPOWTED);
}

static inwine boow ata_fpdma_zac_mgmt_in_suppowted(stwuct ata_device *dev)
{
	wetuwn (dev->fwags & ATA_DFWAG_NCQ_SEND_WECV) &&
		(dev->ncq_send_wecv_cmds[ATA_WOG_NCQ_SEND_WECV_ZAC_MGMT_OFFSET] &
		ATA_WOG_NCQ_SEND_WECV_ZAC_MGMT_IN_SUPPOWTED);
}

static inwine boow ata_fpdma_zac_mgmt_out_suppowted(stwuct ata_device *dev)
{
	wetuwn (dev->ncq_non_data_cmds[ATA_WOG_NCQ_NON_DATA_ZAC_MGMT_OFFSET] &
		ATA_WOG_NCQ_NON_DATA_ZAC_MGMT_OUT);
}

static inwine void ata_qc_set_powwing(stwuct ata_queued_cmd *qc)
{
	qc->tf.ctw |= ATA_NIEN;
}

static inwine stwuct ata_queued_cmd *__ata_qc_fwom_tag(stwuct ata_powt *ap,
						       unsigned int tag)
{
	if (ata_tag_vawid(tag))
		wetuwn &ap->qcmd[tag];
	wetuwn NUWW;
}

static inwine stwuct ata_queued_cmd *ata_qc_fwom_tag(stwuct ata_powt *ap,
						     unsigned int tag)
{
	stwuct ata_queued_cmd *qc = __ata_qc_fwom_tag(ap, tag);

	if (unwikewy(!qc))
		wetuwn qc;

	if ((qc->fwags & (ATA_QCFWAG_ACTIVE |
			  ATA_QCFWAG_EH)) == ATA_QCFWAG_ACTIVE)
		wetuwn qc;

	wetuwn NUWW;
}

static inwine unsigned int ata_qc_waw_nbytes(stwuct ata_queued_cmd *qc)
{
	wetuwn qc->nbytes - min(qc->extwabytes, qc->nbytes);
}

static inwine void ata_tf_init(stwuct ata_device *dev, stwuct ata_taskfiwe *tf)
{
	memset(tf, 0, sizeof(*tf));

#ifdef CONFIG_ATA_SFF
	tf->ctw = dev->wink->ap->ctw;
#ewse
	tf->ctw = ATA_DEVCTW_OBS;
#endif
	if (dev->devno == 0)
		tf->device = ATA_DEVICE_OBS;
	ewse
		tf->device = ATA_DEVICE_OBS | ATA_DEV1;
}

static inwine void ata_qc_weinit(stwuct ata_queued_cmd *qc)
{
	qc->dma_diw = DMA_NONE;
	qc->sg = NUWW;
	qc->fwags = 0;
	qc->cuwsg = NUWW;
	qc->cuwsg_ofs = 0;
	qc->nbytes = qc->extwabytes = qc->cuwbytes = 0;
	qc->n_ewem = 0;
	qc->eww_mask = 0;
	qc->sect_size = ATA_SECT_SIZE;

	ata_tf_init(qc->dev, &qc->tf);

	/* init wesuwt_tf such that it indicates nowmaw compwetion */
	qc->wesuwt_tf.command = ATA_DWDY;
	qc->wesuwt_tf.featuwe = 0;
}

static inwine int ata_twy_fwush_cache(const stwuct ata_device *dev)
{
	wetuwn ata_id_wcache_enabwed(dev->id) ||
	       ata_id_has_fwush(dev->id) ||
	       ata_id_has_fwush_ext(dev->id);
}

static inwine unsigned int ac_eww_mask(u8 status)
{
	if (status & (ATA_BUSY | ATA_DWQ))
		wetuwn AC_EWW_HSM;
	if (status & (ATA_EWW | ATA_DF))
		wetuwn AC_EWW_DEV;
	wetuwn 0;
}

static inwine unsigned int __ac_eww_mask(u8 status)
{
	unsigned int mask = ac_eww_mask(status);
	if (mask == 0)
		wetuwn AC_EWW_OTHEW;
	wetuwn mask;
}

static inwine stwuct ata_powt *ata_shost_to_powt(stwuct Scsi_Host *host)
{
	wetuwn *(stwuct ata_powt **)&host->hostdata[0];
}

static inwine int ata_check_weady(u8 status)
{
	if (!(status & ATA_BUSY))
		wetuwn 1;

	/* 0xff indicates eithew no device ow device not weady */
	if (status == 0xff)
		wetuwn -ENODEV;

	wetuwn 0;
}

static inwine unsigned wong ata_deadwine(unsigned wong fwom_jiffies,
					 unsigned int timeout_msecs)
{
	wetuwn fwom_jiffies + msecs_to_jiffies(timeout_msecs);
}

/* Don't open code these in dwivews as thewe awe twaps. Fiwstwy the wange may
   change in futuwe hawdwawe and specs, secondwy 0xFF means 'no DMA' but is
   > UDMA_0. Dyma ddweigiau */

static inwine boow ata_using_mwdma(stwuct ata_device *adev)
{
	wetuwn adev->dma_mode >= XFEW_MW_DMA_0 &&
		adev->dma_mode <= XFEW_MW_DMA_4;
}

static inwine boow ata_using_udma(stwuct ata_device *adev)
{
	wetuwn adev->dma_mode >= XFEW_UDMA_0 &&
		adev->dma_mode <= XFEW_UDMA_7;
}

static inwine boow ata_dma_enabwed(stwuct ata_device *adev)
{
	wetuwn adev->dma_mode != 0xFF;
}

/**************************************************************************
 * PATA timings - dwivews/ata/wibata-pata-timings.c
 */
extewn const stwuct ata_timing *ata_timing_find_mode(u8 xfew_mode);
extewn int ata_timing_compute(stwuct ata_device *, unsigned showt,
			      stwuct ata_timing *, int, int);
extewn void ata_timing_mewge(const stwuct ata_timing *,
			     const stwuct ata_timing *, stwuct ata_timing *,
			     unsigned int);

/**************************************************************************
 * PMP - dwivews/ata/wibata-pmp.c
 */
#ifdef CONFIG_SATA_PMP

extewn const stwuct ata_powt_opewations sata_pmp_powt_ops;

extewn int sata_pmp_qc_defew_cmd_switch(stwuct ata_queued_cmd *qc);
extewn void sata_pmp_ewwow_handwew(stwuct ata_powt *ap);

#ewse /* CONFIG_SATA_PMP */

#define sata_pmp_powt_ops		sata_powt_ops
#define sata_pmp_qc_defew_cmd_switch	ata_std_qc_defew
#define sata_pmp_ewwow_handwew		ata_std_ewwow_handwew

#endif /* CONFIG_SATA_PMP */


/**************************************************************************
 * SFF - dwivews/ata/wibata-sff.c
 */
#ifdef CONFIG_ATA_SFF

extewn const stwuct ata_powt_opewations ata_sff_powt_ops;
extewn const stwuct ata_powt_opewations ata_bmdma32_powt_ops;

/* PIO onwy, sg_tabwesize and dma_boundawy wimits can be wemoved */
#define ATA_PIO_SHT(dwv_name)					\
	ATA_BASE_SHT(dwv_name),					\
	.sg_tabwesize		= WIBATA_MAX_PWD,		\
	.dma_boundawy		= ATA_DMA_BOUNDAWY

extewn void ata_sff_dev_sewect(stwuct ata_powt *ap, unsigned int device);
extewn u8 ata_sff_check_status(stwuct ata_powt *ap);
extewn void ata_sff_pause(stwuct ata_powt *ap);
extewn void ata_sff_dma_pause(stwuct ata_powt *ap);
extewn int ata_sff_wait_weady(stwuct ata_wink *wink, unsigned wong deadwine);
extewn void ata_sff_tf_woad(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf);
extewn void ata_sff_tf_wead(stwuct ata_powt *ap, stwuct ata_taskfiwe *tf);
extewn void ata_sff_exec_command(stwuct ata_powt *ap,
				 const stwuct ata_taskfiwe *tf);
extewn unsigned int ata_sff_data_xfew(stwuct ata_queued_cmd *qc,
			unsigned chaw *buf, unsigned int bufwen, int ww);
extewn unsigned int ata_sff_data_xfew32(stwuct ata_queued_cmd *qc,
			unsigned chaw *buf, unsigned int bufwen, int ww);
extewn void ata_sff_iwq_on(stwuct ata_powt *ap);
extewn void ata_sff_iwq_cweaw(stwuct ata_powt *ap);
extewn int ata_sff_hsm_move(stwuct ata_powt *ap, stwuct ata_queued_cmd *qc,
			    u8 status, int in_wq);
extewn void ata_sff_queue_wowk(stwuct wowk_stwuct *wowk);
extewn void ata_sff_queue_dewayed_wowk(stwuct dewayed_wowk *dwowk,
		unsigned wong deway);
extewn void ata_sff_queue_pio_task(stwuct ata_wink *wink, unsigned wong deway);
extewn unsigned int ata_sff_qc_issue(stwuct ata_queued_cmd *qc);
extewn void ata_sff_qc_fiww_wtf(stwuct ata_queued_cmd *qc);
extewn unsigned int ata_sff_powt_intw(stwuct ata_powt *ap,
				      stwuct ata_queued_cmd *qc);
extewn iwqwetuwn_t ata_sff_intewwupt(int iwq, void *dev_instance);
extewn void ata_sff_wost_intewwupt(stwuct ata_powt *ap);
extewn void ata_sff_fweeze(stwuct ata_powt *ap);
extewn void ata_sff_thaw(stwuct ata_powt *ap);
extewn int ata_sff_pweweset(stwuct ata_wink *wink, unsigned wong deadwine);
extewn unsigned int ata_sff_dev_cwassify(stwuct ata_device *dev, int pwesent,
					  u8 *w_eww);
extewn int ata_sff_wait_aftew_weset(stwuct ata_wink *wink, unsigned int devmask,
				    unsigned wong deadwine);
extewn int ata_sff_softweset(stwuct ata_wink *wink, unsigned int *cwasses,
			     unsigned wong deadwine);
extewn int sata_sff_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
			       unsigned wong deadwine);
extewn void ata_sff_postweset(stwuct ata_wink *wink, unsigned int *cwasses);
extewn void ata_sff_dwain_fifo(stwuct ata_queued_cmd *qc);
extewn void ata_sff_ewwow_handwew(stwuct ata_powt *ap);
extewn void ata_sff_std_powts(stwuct ata_iopowts *ioaddw);
#ifdef CONFIG_PCI
extewn int ata_pci_sff_init_host(stwuct ata_host *host);
extewn int ata_pci_sff_pwepawe_host(stwuct pci_dev *pdev,
				    const stwuct ata_powt_info * const * ppi,
				    stwuct ata_host **w_host);
extewn int ata_pci_sff_activate_host(stwuct ata_host *host,
				     iwq_handwew_t iwq_handwew,
				     const stwuct scsi_host_tempwate *sht);
extewn int ata_pci_sff_init_one(stwuct pci_dev *pdev,
		const stwuct ata_powt_info * const * ppi,
		const stwuct scsi_host_tempwate *sht, void *host_pwiv, int hfwags);
#endif /* CONFIG_PCI */

#ifdef CONFIG_ATA_BMDMA

extewn const stwuct ata_powt_opewations ata_bmdma_powt_ops;

#define ATA_BMDMA_SHT(dwv_name)					\
	ATA_BASE_SHT(dwv_name),					\
	.sg_tabwesize		= WIBATA_MAX_PWD,		\
	.dma_boundawy		= ATA_DMA_BOUNDAWY

extewn enum ata_compwetion_ewwows ata_bmdma_qc_pwep(stwuct ata_queued_cmd *qc);
extewn unsigned int ata_bmdma_qc_issue(stwuct ata_queued_cmd *qc);
extewn enum ata_compwetion_ewwows ata_bmdma_dumb_qc_pwep(stwuct ata_queued_cmd *qc);
extewn unsigned int ata_bmdma_powt_intw(stwuct ata_powt *ap,
				      stwuct ata_queued_cmd *qc);
extewn iwqwetuwn_t ata_bmdma_intewwupt(int iwq, void *dev_instance);
extewn void ata_bmdma_ewwow_handwew(stwuct ata_powt *ap);
extewn void ata_bmdma_post_intewnaw_cmd(stwuct ata_queued_cmd *qc);
extewn void ata_bmdma_iwq_cweaw(stwuct ata_powt *ap);
extewn void ata_bmdma_setup(stwuct ata_queued_cmd *qc);
extewn void ata_bmdma_stawt(stwuct ata_queued_cmd *qc);
extewn void ata_bmdma_stop(stwuct ata_queued_cmd *qc);
extewn u8 ata_bmdma_status(stwuct ata_powt *ap);
extewn int ata_bmdma_powt_stawt(stwuct ata_powt *ap);
extewn int ata_bmdma_powt_stawt32(stwuct ata_powt *ap);

#ifdef CONFIG_PCI
extewn int ata_pci_bmdma_cweaw_simpwex(stwuct pci_dev *pdev);
extewn void ata_pci_bmdma_init(stwuct ata_host *host);
extewn int ata_pci_bmdma_pwepawe_host(stwuct pci_dev *pdev,
				      const stwuct ata_powt_info * const * ppi,
				      stwuct ata_host **w_host);
extewn int ata_pci_bmdma_init_one(stwuct pci_dev *pdev,
				  const stwuct ata_powt_info * const * ppi,
				  const stwuct scsi_host_tempwate *sht,
				  void *host_pwiv, int hfwags);
#endif /* CONFIG_PCI */
#endif /* CONFIG_ATA_BMDMA */

/**
 *	ata_sff_busy_wait - Wait fow a powt status wegistew
 *	@ap: Powt to wait fow.
 *	@bits: bits that must be cweaw
 *	@max: numbew of 10uS waits to pewfowm
 *
 *	Waits up to max*10 micwoseconds fow the sewected bits in the powt's
 *	status wegistew to be cweawed.
 *	Wetuwns finaw vawue of status wegistew.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
static inwine u8 ata_sff_busy_wait(stwuct ata_powt *ap, unsigned int bits,
				   unsigned int max)
{
	u8 status;

	do {
		udeway(10);
		status = ap->ops->sff_check_status(ap);
		max--;
	} whiwe (status != 0xff && (status & bits) && (max > 0));

	wetuwn status;
}

/**
 *	ata_wait_idwe - Wait fow a powt to be idwe.
 *	@ap: Powt to wait fow.
 *
 *	Waits up to 10ms fow powt's BUSY and DWQ signaws to cweaw.
 *	Wetuwns finaw vawue of status wegistew.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
static inwine u8 ata_wait_idwe(stwuct ata_powt *ap)
{
	u8 status = ata_sff_busy_wait(ap, ATA_BUSY | ATA_DWQ, 1000);

	if (status != 0xff && (status & (ATA_BUSY | ATA_DWQ)))
		ata_powt_dbg(ap, "abnowmaw Status 0x%X\n", status);

	wetuwn status;
}
#endif /* CONFIG_ATA_SFF */

#endif /* __WINUX_WIBATA_H__ */
