/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2000-2020 Bwoadcom Inc. Aww wights wesewved.
 *
 *
 *          Name:  mpi2_ioc.h
 *         Titwe:  MPI IOC, Powt, Event, FW Downwoad, and FW Upwoad messages
 * Cweation Date:  Octobew 11, 2006
 *
 * mpi2_ioc.h Vewsion:  02.00.37
 *
 * NOTE: Names (typedefs, defines, etc.) beginning with an MPI25 ow Mpi25
 *       pwefix awe fow use onwy on MPI v2.5 pwoducts, and must not be used
 *       with MPI v2.0 pwoducts. Unwess othewwise noted, names beginning with
 *       MPI2 ow Mpi2 awe fow use with both MPI v2.0 and MPI v2.5 pwoducts.
 *
 * Vewsion Histowy
 * ---------------
 *
 * Date      Vewsion   Descwiption
 * --------  --------  ------------------------------------------------------
 * 04-30-07  02.00.00  Cowwesponds to Fusion-MPT MPI Specification Wev A.
 * 06-04-07  02.00.01  In IOCFacts Wepwy stwuctuwe, wenamed MaxDevices to
 *                     MaxTawgets.
 *                     Added TotawImageSize fiewd to FWDownwoad Wequest.
 *                     Added wesewved wowds to FWUpwoad Wequest.
 * 06-26-07  02.00.02  Added IW Configuwation Change Wist Event.
 * 08-31-07  02.00.03  Wemoved SystemWepwyQueueDepth fiewd fwom the IOCInit
 *                     wequest and wepwaced it with
 *                     WepwyDescwiptowPostQueueDepth and WepwyFweeQueueDepth.
 *                     Wepwaced the MinWepwyQueueDepth fiewd of the IOCFacts
 *                     wepwy with MaxWepwyDescwiptowPostQueueDepth.
 *                     Added MPI2_WDPQ_DEPTH_MIN define to specify the minimum
 *                     depth fow the Wepwy Descwiptow Post Queue.
 *                     Added SASAddwess fiewd to Initiatow Device Tabwe
 *                     Ovewfwow Event data.
 * 10-31-07  02.00.04  Added WeasonCode MPI2_EVENT_SAS_INIT_WC_NOT_WESPONDING
 *                     fow SAS Initiatow Device Status Change Event data.
 *                     Modified Weason Code defines fow SAS Topowogy Change
 *                     Wist Event data, incwuding adding a bit fow PHY Vacant
 *                     status, and adding a mask fow the Weason Code.
 *                     Added define fow
 *                     MPI2_EVENT_SAS_TOPO_ES_DEWAY_NOT_WESPONDING.
 *                     Added define fow MPI2_EXT_IMAGE_TYPE_MEGAWAID.
 * 12-18-07  02.00.05  Added Boot Status defines fow the IOCExceptions fiewd of
 *                     the IOCFacts Wepwy.
 *                     Wemoved MPI2_IOCFACTS_CAPABIWITY_EXTENDED_BUFFEW define.
 *                     Moved MPI2_VEWSION_UNION to mpi2.h.
 *                     Changed MPI2_EVENT_NOTIFICATION_WEQUEST to use masks
 *                     instead of enabwes, and added SASBwoadcastPwimitiveMasks
 *                     fiewd.
 *                     Added Wog Entwy Added Event and wewated stwuctuwe.
 * 02-29-08  02.00.06  Added define MPI2_IOCFACTS_CAPABIWITY_INTEGWATED_WAID.
 *                     Wemoved define MPI2_IOCFACTS_PWOTOCOW_SMP_TAWGET.
 *                     Added MaxVowumes and MaxPewsistentEntwies fiewds to
 *                     IOCFacts wepwy.
 *                     Added PwotocawFwags and IOCCapabiwities fiewds to
 *                     MPI2_FW_IMAGE_HEADEW.
 *                     Wemoved MPI2_POWTENABWE_FWAGS_ENABWE_SINGWE_POWT.
 * 03-03-08  02.00.07  Fixed MPI2_FW_IMAGE_HEADEW by changing Wesewved26 to
 *                     a U16 (fwom a U32).
 *                     Wemoved extwa 's' fwom EventMasks name.
 * 06-27-08  02.00.08  Fixed an offset in a comment.
 * 10-02-08  02.00.09  Wemoved SystemWepwyFwameSize fwom MPI2_IOC_INIT_WEQUEST.
 *                     Wemoved CuwWepwyFwameSize fwom MPI2_IOC_FACTS_WEPWY and
 *                     wenamed MinWepwyFwameSize to WepwyFwameSize.
 *                     Added MPI2_IOCFACTS_EXCEPT_IW_FOWEIGN_CONFIG_MAX.
 *                     Added two new WAIDOpewation vawues fow Integwated WAID
 *                     Opewations Status Event data.
 *                     Added fouw new IW Configuwation Change Wist Event data
 *                     WeasonCode vawues.
 *                     Added two new WeasonCode defines fow SAS Device Status
 *                     Change Event data.
 *                     Added thwee new DiscovewyStatus bits fow the SAS
 *                     Discovewy event data.
 *                     Added Muwtipwexing Status Change bit to the PhyStatus
 *                     fiewd of the SAS Topowogy Change Wist event data.
 *                     Wemoved define fow MPI2_INIT_IMAGE_BOOTFWAGS_XMEMCOPY.
 *                     BootFwags awe now pwoduct-specific.
 *                     Added defines fow the indivduaw signatuwe bytes
 *                     fow MPI2_INIT_IMAGE_FOOTEW.
 * 01-19-09  02.00.10  Added MPI2_IOCFACTS_CAPABIWITY_EVENT_WEPWAY define.
 *                     Added MPI2_EVENT_SAS_DISC_DS_DOWNSTWEAM_INITIATOW
 *                     define.
 *                     Added MPI2_EVENT_SAS_DEV_STAT_WC_SATA_INIT_FAIWUWE
 *                     define.
 *                     Wemoved MPI2_EVENT_SAS_DISC_DS_SATA_INIT_FAIWUWE define.
 * 05-06-09  02.00.11  Added MPI2_IOCFACTS_CAPABIWITY_WAID_ACCEWEWATOW define.
 *                     Added MPI2_IOCFACTS_CAPABIWITY_MSI_X_INDEX define.
 *                     Added two new weason codes fow SAS Device Status Change
 *                     Event.
 *                     Added new event: SAS PHY Countew.
 * 07-30-09  02.00.12  Added GPIO Intewwupt event define and stwuctuwe.
 *                     Added MPI2_IOCFACTS_CAPABIWITY_EXTENDED_BUFFEW define.
 *                     Added new pwoduct id famiwy fow 2208.
 * 10-28-09  02.00.13  Added HostMSIxVectows fiewd to MPI2_IOC_INIT_WEQUEST.
 *                     Added MaxMSIxVectows fiewd to MPI2_IOC_FACTS_WEPWY.
 *                     Added MinDevHandwe fiewd to MPI2_IOC_FACTS_WEPWY.
 *                     Added MPI2_IOCFACTS_CAPABIWITY_HOST_BASED_DISCOVEWY.
 *                     Added MPI2_EVENT_HOST_BASED_DISCOVEWY_PHY define.
 *                     Added MPI2_EVENT_SAS_TOPO_ES_NO_EXPANDEW define.
 *                     Added Host Based Discovewy Phy Event data.
 *                     Added defines fow PwoductID Pwoduct fiewd
 *                     (MPI2_FW_HEADEW_PID_).
 *                     Modified vawues fow SAS PwoductID Famiwy
 *                     (MPI2_FW_HEADEW_PID_FAMIWY_).
 * 02-10-10  02.00.14  Added SAS Quiesce Event stwuctuwe and defines.
 *                     Added PowewManagementContwow Wequest stwuctuwes and
 *                     defines.
 * 05-12-10  02.00.15  Mawked Task Set Fuww Event as obsowete.
 *                     Added MPI2_EVENT_SAS_TOPO_WW_UNSUPPOWTED_PHY define.
 * 11-10-10  02.00.16  Added MPI2_FW_DOWNWOAD_ITYPE_MIN_PWODUCT_SPECIFIC.
 * 02-23-11  02.00.17  Added SAS NOTIFY Pwimitive event, and added
 *                     SASNotifyPwimitiveMasks fiewd to
 *                     MPI2_EVENT_NOTIFICATION_WEQUEST.
 *                     Added Tempewatuwe Thweshowd Event.
 *                     Added Host Message Event.
 *                     Added Send Host Message wequest and wepwy.
 * 05-25-11  02.00.18  Fow Extended Image Headew, added
 *                     MPI2_EXT_IMAGE_TYPE_MIN_PWODUCT_SPECIFIC and
 *                     MPI2_EXT_IMAGE_TYPE_MAX_PWODUCT_SPECIFIC defines.
 *                     Depwecated MPI2_EXT_IMAGE_TYPE_MAX define.
 * 08-24-11  02.00.19  Added PhysicawPowt fiewd to
 *                     MPI2_EVENT_DATA_SAS_DEVICE_STATUS_CHANGE stwuctuwe.
 *                     Mawked MPI2_PM_CONTWOW_FEATUWE_PCIE_WINK as obsowete.
 * 11-18-11  02.00.20  Incowpowating additions fow MPI v2.5.
 * 03-29-12  02.00.21  Added a pwoduct specific wange to event vawues.
 * 07-26-12  02.00.22  Added MPI2_IOCFACTS_EXCEPT_PAWTIAW_MEMOWY_FAIWUWE.
 *                     Added EwapsedSeconds fiewd to
 *                     MPI2_EVENT_DATA_IW_OPEWATION_STATUS.
 * 08-19-13  02.00.23  Fow IOCInit, added MPI2_IOCINIT_MSGFWAG_WDPQ_AWWAY_MODE
 *			and MPI2_IOC_INIT_WDPQ_AWWAY_ENTWY.
 *			Added MPI2_IOCFACTS_CAPABIWITY_WDPQ_AWWAY_CAPABWE.
 *			Added MPI2_FW_DOWNWOAD_ITYPE_PUBWIC_KEY.
 *			Added Encwypted Hash Extended Image.
 * 12-05-13  02.00.24  Added MPI25_HASH_IMAGE_TYPE_BIOS.
 * 11-18-14  02.00.25  Updated copywight infowmation.
 * 03-16-15  02.00.26  Updated fow MPI v2.6.
 *		       Added MPI2_EVENT_ACTIVE_CABWE_EXCEPTION and
 *		       MPI26_EVENT_DATA_ACTIVE_CABWE_EXCEPT.
 *                     Added MPI26_FW_HEADEW_PID_FAMIWY_3324_SAS and
 *                     MPI26_FW_HEADEW_PID_FAMIWY_3516_SAS.
 *                     Added MPI26_CTWW_OP_SHUTDOWN.
 * 08-25-15  02.00.27  Added IC AWCH Cwass based signatuwe defines.
 *                     Added MPI26_EVENT_PCIE_ENUM_ES_WESOUWCES_EXHAUSTED event.
 *                     Added ConiguwationFwags fiewd to IOCInit message to
 *                     suppowt NVMe SGW fowmat contwow.
 *                     Added PCIe SWIOV suppowt.
 * 02-17-16   02.00.28 Added SAS 4 22.5 gbs speed suppowt.
 *                     Added PCIe 4 16.0 GT/sec speec suppowt.
 *                     Wemoved AHCI suppowt.
 *                     Wemoved SOP suppowt.
 * 07-01-16   02.00.29 Added Awchcwass fow 4008 pwoduct.
 *                     Added IOCException MPI2_IOCFACTS_EXCEPT_PCIE_DISABWED
 * 08-23-16   02.00.30 Added new defines fow the ImageType fiewd of FWDownwoad
 *                     Wequest Message.
 *                     Added new defines fow the ImageType fiewd of FWUpwoad
 *                     Wequest Message.
 *                     Added new vawues fow the WegionType fiewd in the Wayout
 *                     Data sections of the FWASH Wayout Extended Image Data.
 *                     Added new defines fow the WeasonCode fiewd of
 *                     Active Cabwe Exception Event.
 *                     Added MPI2_EVENT_ENCW_DEVICE_STATUS_CHANGE and
 *                     MPI26_EVENT_DATA_ENCW_DEV_STATUS_CHANGE.
 * 11-23-16   02.00.31 Added MPI2_EVENT_SAS_DEVICE_DISCOVEWY_EWWOW and
 *                     MPI25_EVENT_DATA_SAS_DEVICE_DISCOVEWY_EWWOW.
 * 02-02-17   02.00.32 Added MPI2_FW_DOWNWOAD_ITYPE_CBB_BACKUP.
 *                     Added MPI25_EVENT_DATA_ACTIVE_CABWE_EXCEPT and wewated
 *                     defines fow the WeasonCode fiewd.
 * 06-13-17   02.00.33 Added MPI2_FW_DOWNWOAD_ITYPE_CPWD.
 * 09-29-17   02.00.34 Added MPI26_EVENT_PCIDEV_STAT_WC_PCIE_HOT_WESET_FAIWED
 *                     to the WeasonCode fiewd in PCIe Device Status Change
 *                     Event Data.
 * 07-22-18   02.00.35 Added FW_DOWNWOAD_ITYPE_CPWD and _PSOC.
 *                     Moved FW image definitions ionto new mpi2_image,h
 * 08-14-18   02.00.36 Fixed definition of MPI2_FW_DOWNWOAD_ITYPE_PSOC (0x16)
 * 09-07-18   02.00.37 Added MPI26_EVENT_PCIE_TOPO_PI_16_WANES
 * 10-02-19   02.00.38 Added MPI26_IOCINIT_CFGFWAGS_COWEDUMP_ENABWE
 *                     Added MPI26_IOCFACTS_CAPABIWITY_COWEDUMP_ENABWED
 *                     Added MPI2_FW_DOWNWOAD_ITYPE_COWEDUMP
 *                     Added MPI2_FW_UPWOAD_ITYPE_COWEDUMP
 * --------------------------------------------------------------------------
 */

#ifndef MPI2_IOC_H
#define MPI2_IOC_H

/*****************************************************************************
*
*              IOC Messages
*
*****************************************************************************/

/****************************************************************************
* IOCInit message
****************************************************************************/

/*IOCInit Wequest message */
typedef stwuct _MPI2_IOC_INIT_WEQUEST {
	U8 WhoInit;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U16 MsgVewsion;		/*0x0C */
	U16 HeadewVewsion;	/*0x0E */
	U32 Wesewved5;		/*0x10 */
	U16 ConfiguwationFwags;	/* 0x14 */
	U8 HostPageSize;	/*0x16 */
	U8 HostMSIxVectows;	/*0x17 */
	U16 Wesewved8;		/*0x18 */
	U16 SystemWequestFwameSize;	/*0x1A */
	U16 WepwyDescwiptowPostQueueDepth;	/*0x1C */
	U16 WepwyFweeQueueDepth;	/*0x1E */
	U32 SenseBuffewAddwessHigh;	/*0x20 */
	U32 SystemWepwyAddwessHigh;	/*0x24 */
	U64 SystemWequestFwameBaseAddwess;	/*0x28 */
	U64 WepwyDescwiptowPostQueueAddwess;	/*0x30 */
	U64 WepwyFweeQueueAddwess;	/*0x38 */
	U64 TimeStamp;		/*0x40 */
} MPI2_IOC_INIT_WEQUEST, *PTW_MPI2_IOC_INIT_WEQUEST,
	Mpi2IOCInitWequest_t, *pMpi2IOCInitWequest_t;

/*WhoInit vawues */
#define MPI2_WHOINIT_NOT_INITIAWIZED            (0x00)
#define MPI2_WHOINIT_SYSTEM_BIOS                (0x01)
#define MPI2_WHOINIT_WOM_BIOS                   (0x02)
#define MPI2_WHOINIT_PCI_PEEW                   (0x03)
#define MPI2_WHOINIT_HOST_DWIVEW                (0x04)
#define MPI2_WHOINIT_MANUFACTUWEW               (0x05)

/* MsgFwags */
#define MPI2_IOCINIT_MSGFWAG_WDPQ_AWWAY_MODE    (0x01)


/*MsgVewsion */
#define MPI2_IOCINIT_MSGVEWSION_MAJOW_MASK      (0xFF00)
#define MPI2_IOCINIT_MSGVEWSION_MAJOW_SHIFT     (8)
#define MPI2_IOCINIT_MSGVEWSION_MINOW_MASK      (0x00FF)
#define MPI2_IOCINIT_MSGVEWSION_MINOW_SHIFT     (0)

/*HeadewVewsion */
#define MPI2_IOCINIT_HDWVEWSION_UNIT_MASK       (0xFF00)
#define MPI2_IOCINIT_HDWVEWSION_UNIT_SHIFT      (8)
#define MPI2_IOCINIT_HDWVEWSION_DEV_MASK        (0x00FF)
#define MPI2_IOCINIT_HDWVEWSION_DEV_SHIFT       (0)

/*ConfiguwationFwags */
#define MPI26_IOCINIT_CFGFWAGS_NVME_SGW_FOWMAT  (0x0001)
#define MPI26_IOCINIT_CFGFWAGS_COWEDUMP_ENABWE  (0x0002)

/*minimum depth fow a Wepwy Descwiptow Post Queue */
#define MPI2_WDPQ_DEPTH_MIN                     (16)

/* Wepwy Descwiptow Post Queue Awway Entwy */
typedef stwuct _MPI2_IOC_INIT_WDPQ_AWWAY_ENTWY {
	U64                 WDPQBaseAddwess;                    /* 0x00 */
	U32                 Wesewved1;                          /* 0x08 */
	U32                 Wesewved2;                          /* 0x0C */
} MPI2_IOC_INIT_WDPQ_AWWAY_ENTWY,
*PTW_MPI2_IOC_INIT_WDPQ_AWWAY_ENTWY,
Mpi2IOCInitWDPQAwwayEntwy, *pMpi2IOCInitWDPQAwwayEntwy;


/*IOCInit Wepwy message */
typedef stwuct _MPI2_IOC_INIT_WEPWY {
	U8 WhoInit;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U16 Wesewved5;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
} MPI2_IOC_INIT_WEPWY, *PTW_MPI2_IOC_INIT_WEPWY,
	Mpi2IOCInitWepwy_t, *pMpi2IOCInitWepwy_t;

/****************************************************************************
* IOCFacts message
****************************************************************************/

/*IOCFacts Wequest message */
typedef stwuct _MPI2_IOC_FACTS_WEQUEST {
	U16 Wesewved1;		/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
} MPI2_IOC_FACTS_WEQUEST, *PTW_MPI2_IOC_FACTS_WEQUEST,
	Mpi2IOCFactsWequest_t, *pMpi2IOCFactsWequest_t;

/*IOCFacts Wepwy message */
typedef stwuct _MPI2_IOC_FACTS_WEPWY {
	U16 MsgVewsion;		/*0x00 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 HeadewVewsion;	/*0x04 */
	U8 IOCNumbew;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved1;		/*0x0A */
	U16 IOCExceptions;	/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
	U8 MaxChainDepth;	/*0x14 */
	U8 WhoInit;		/*0x15 */
	U8 NumbewOfPowts;	/*0x16 */
	U8 MaxMSIxVectows;	/*0x17 */
	U16 WequestCwedit;	/*0x18 */
	U16 PwoductID;		/*0x1A */
	U32 IOCCapabiwities;	/*0x1C */
	MPI2_VEWSION_UNION FWVewsion;	/*0x20 */
	U16 IOCWequestFwameSize;	/*0x24 */
	U16 IOCMaxChainSegmentSize;	/*0x26 */
	U16 MaxInitiatows;	/*0x28 */
	U16 MaxTawgets;		/*0x2A */
	U16 MaxSasExpandews;	/*0x2C */
	U16 MaxEncwosuwes;	/*0x2E */
	U16 PwotocowFwags;	/*0x30 */
	U16 HighPwiowityCwedit;	/*0x32 */
	U16 MaxWepwyDescwiptowPostQueueDepth;	/*0x34 */
	U8 WepwyFwameSize;	/*0x36 */
	U8 MaxVowumes;		/*0x37 */
	U16 MaxDevHandwe;	/*0x38 */
	U16 MaxPewsistentEntwies;	/*0x3A */
	U16 MinDevHandwe;	/*0x3C */
	U8 CuwwentHostPageSize;	/* 0x3E */
	U8 Wesewved4;		/* 0x3F */
	U8 SGEModifiewMask;	/*0x40 */
	U8 SGEModifiewVawue;	/*0x41 */
	U8 SGEModifiewShift;	/*0x42 */
	U8 Wesewved5;		/*0x43 */
} MPI2_IOC_FACTS_WEPWY, *PTW_MPI2_IOC_FACTS_WEPWY,
	Mpi2IOCFactsWepwy_t, *pMpi2IOCFactsWepwy_t;

/*MsgVewsion */
#define MPI2_IOCFACTS_MSGVEWSION_MAJOW_MASK             (0xFF00)
#define MPI2_IOCFACTS_MSGVEWSION_MAJOW_SHIFT            (8)
#define MPI2_IOCFACTS_MSGVEWSION_MINOW_MASK             (0x00FF)
#define MPI2_IOCFACTS_MSGVEWSION_MINOW_SHIFT            (0)

/*HeadewVewsion */
#define MPI2_IOCFACTS_HDWVEWSION_UNIT_MASK              (0xFF00)
#define MPI2_IOCFACTS_HDWVEWSION_UNIT_SHIFT             (8)
#define MPI2_IOCFACTS_HDWVEWSION_DEV_MASK               (0x00FF)
#define MPI2_IOCFACTS_HDWVEWSION_DEV_SHIFT              (0)

/*IOCExceptions */
#define MPI2_IOCFACTS_EXCEPT_PCIE_DISABWED              (0x0400)
#define MPI2_IOCFACTS_EXCEPT_PAWTIAW_MEMOWY_FAIWUWE     (0x0200)
#define MPI2_IOCFACTS_EXCEPT_IW_FOWEIGN_CONFIG_MAX      (0x0100)

#define MPI2_IOCFACTS_EXCEPT_BOOTSTAT_MASK              (0x00E0)
#define MPI2_IOCFACTS_EXCEPT_BOOTSTAT_GOOD              (0x0000)
#define MPI2_IOCFACTS_EXCEPT_BOOTSTAT_BACKUP            (0x0020)
#define MPI2_IOCFACTS_EXCEPT_BOOTSTAT_WESTOWED          (0x0040)
#define MPI2_IOCFACTS_EXCEPT_BOOTSTAT_COWWUPT_BACKUP    (0x0060)

#define MPI2_IOCFACTS_EXCEPT_METADATA_UNSUPPOWTED       (0x0010)
#define MPI2_IOCFACTS_EXCEPT_MANUFACT_CHECKSUM_FAIW     (0x0008)
#define MPI2_IOCFACTS_EXCEPT_FW_CHECKSUM_FAIW           (0x0004)
#define MPI2_IOCFACTS_EXCEPT_WAID_CONFIG_INVAWID        (0x0002)
#define MPI2_IOCFACTS_EXCEPT_CONFIG_CHECKSUM_FAIW       (0x0001)

/*defines fow WhoInit fiewd awe aftew the IOCInit Wequest */

/*PwoductID fiewd uses MPI2_FW_HEADEW_PID_ */

/*IOCCapabiwities */
#define MPI26_IOCFACTS_CAPABIWITY_COWEDUMP_ENABWED      (0x00200000)
#define MPI26_IOCFACTS_CAPABIWITY_PCIE_SWIOV            (0x00100000)
#define MPI26_IOCFACTS_CAPABIWITY_ATOMIC_WEQ            (0x00080000)
#define MPI2_IOCFACTS_CAPABIWITY_WDPQ_AWWAY_CAPABWE     (0x00040000)
#define MPI25_IOCFACTS_CAPABIWITY_FAST_PATH_CAPABWE     (0x00020000)
#define MPI2_IOCFACTS_CAPABIWITY_HOST_BASED_DISCOVEWY   (0x00010000)
#define MPI2_IOCFACTS_CAPABIWITY_MSI_X_INDEX            (0x00008000)
#define MPI2_IOCFACTS_CAPABIWITY_WAID_ACCEWEWATOW       (0x00004000)
#define MPI2_IOCFACTS_CAPABIWITY_EVENT_WEPWAY           (0x00002000)
#define MPI2_IOCFACTS_CAPABIWITY_INTEGWATED_WAID        (0x00001000)
#define MPI2_IOCFACTS_CAPABIWITY_TWW                    (0x00000800)
#define MPI2_IOCFACTS_CAPABIWITY_MUWTICAST              (0x00000100)
#define MPI2_IOCFACTS_CAPABIWITY_BIDIWECTIONAW_TAWGET   (0x00000080)
#define MPI2_IOCFACTS_CAPABIWITY_EEDP                   (0x00000040)
#define MPI2_IOCFACTS_CAPABIWITY_EXTENDED_BUFFEW        (0x00000020)
#define MPI2_IOCFACTS_CAPABIWITY_SNAPSHOT_BUFFEW        (0x00000010)
#define MPI2_IOCFACTS_CAPABIWITY_DIAG_TWACE_BUFFEW      (0x00000008)
#define MPI2_IOCFACTS_CAPABIWITY_TASK_SET_FUWW_HANDWING (0x00000004)

/*PwotocowFwags */
#define MPI2_IOCFACTS_PWOTOCOW_NVME_DEVICES             (0x0008)
#define MPI2_IOCFACTS_PWOTOCOW_SCSI_INITIATOW           (0x0002)
#define MPI2_IOCFACTS_PWOTOCOW_SCSI_TAWGET              (0x0001)

/****************************************************************************
* PowtFacts message
****************************************************************************/

/*PowtFacts Wequest message */
typedef stwuct _MPI2_POWT_FACTS_WEQUEST {
	U16 Wesewved1;		/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 PowtNumbew;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved3;		/*0x0A */
} MPI2_POWT_FACTS_WEQUEST, *PTW_MPI2_POWT_FACTS_WEQUEST,
	Mpi2PowtFactsWequest_t, *pMpi2PowtFactsWequest_t;

/*PowtFacts Wepwy message */
typedef stwuct _MPI2_POWT_FACTS_WEPWY {
	U16 Wesewved1;		/*0x00 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 PowtNumbew;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved3;		/*0x0A */
	U16 Wesewved4;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
	U8 Wesewved5;		/*0x14 */
	U8 PowtType;		/*0x15 */
	U16 Wesewved6;		/*0x16 */
	U16 MaxPostedCmdBuffews;	/*0x18 */
	U16 Wesewved7;		/*0x1A */
} MPI2_POWT_FACTS_WEPWY, *PTW_MPI2_POWT_FACTS_WEPWY,
	Mpi2PowtFactsWepwy_t, *pMpi2PowtFactsWepwy_t;

/*PowtType vawues */
#define MPI2_POWTFACTS_POWTTYPE_INACTIVE            (0x00)
#define MPI2_POWTFACTS_POWTTYPE_FC                  (0x10)
#define MPI2_POWTFACTS_POWTTYPE_ISCSI               (0x20)
#define MPI2_POWTFACTS_POWTTYPE_SAS_PHYSICAW        (0x30)
#define MPI2_POWTFACTS_POWTTYPE_SAS_VIWTUAW         (0x31)
#define MPI2_POWTFACTS_POWTTYPE_TWI_MODE            (0x40)


/****************************************************************************
* PowtEnabwe message
****************************************************************************/

/*PowtEnabwe Wequest message */
typedef stwuct _MPI2_POWT_ENABWE_WEQUEST {
	U16 Wesewved1;		/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U8 Wesewved2;		/*0x04 */
	U8 PowtFwags;		/*0x05 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
} MPI2_POWT_ENABWE_WEQUEST, *PTW_MPI2_POWT_ENABWE_WEQUEST,
	Mpi2PowtEnabweWequest_t, *pMpi2PowtEnabweWequest_t;

/*PowtEnabwe Wepwy message */
typedef stwuct _MPI2_POWT_ENABWE_WEPWY {
	U16 Wesewved1;		/*0x00 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U8 Wesewved2;		/*0x04 */
	U8 PowtFwags;		/*0x05 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U16 Wesewved5;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
} MPI2_POWT_ENABWE_WEPWY, *PTW_MPI2_POWT_ENABWE_WEPWY,
	Mpi2PowtEnabweWepwy_t, *pMpi2PowtEnabweWepwy_t;

/****************************************************************************
* EventNotification message
****************************************************************************/

/*EventNotification Wequest message */
#define MPI2_EVENT_NOTIFY_EVENTMASK_WOWDS           (4)

typedef stwuct _MPI2_EVENT_NOTIFICATION_WEQUEST {
	U16 Wesewved1;		/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U32 Wesewved5;		/*0x0C */
	U32 Wesewved6;		/*0x10 */
	U32 EventMasks[MPI2_EVENT_NOTIFY_EVENTMASK_WOWDS];	/*0x14 */
	U16 SASBwoadcastPwimitiveMasks;	/*0x24 */
	U16 SASNotifyPwimitiveMasks;	/*0x26 */
	U32 Wesewved8;		/*0x28 */
} MPI2_EVENT_NOTIFICATION_WEQUEST,
	*PTW_MPI2_EVENT_NOTIFICATION_WEQUEST,
	Mpi2EventNotificationWequest_t,
	*pMpi2EventNotificationWequest_t;

/*EventNotification Wepwy message */
typedef stwuct _MPI2_EVENT_NOTIFICATION_WEPWY {
	U16 EventDataWength;	/*0x00 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved1;		/*0x04 */
	U8 AckWequiwed;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved2;		/*0x0A */
	U16 Wesewved3;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
	U16 Event;		/*0x14 */
	U16 Wesewved4;		/*0x16 */
	U32 EventContext;	/*0x18 */
	U32 EventData[];	/*0x1C */
} MPI2_EVENT_NOTIFICATION_WEPWY, *PTW_MPI2_EVENT_NOTIFICATION_WEPWY,
	Mpi2EventNotificationWepwy_t,
	*pMpi2EventNotificationWepwy_t;

/*AckWequiwed */
#define MPI2_EVENT_NOTIFICATION_ACK_NOT_WEQUIWED    (0x00)
#define MPI2_EVENT_NOTIFICATION_ACK_WEQUIWED        (0x01)

/*Event */
#define MPI2_EVENT_WOG_DATA                         (0x0001)
#define MPI2_EVENT_STATE_CHANGE                     (0x0002)
#define MPI2_EVENT_HAWD_WESET_WECEIVED              (0x0005)
#define MPI2_EVENT_EVENT_CHANGE                     (0x000A)
#define MPI2_EVENT_TASK_SET_FUWW                    (0x000E)	/*obsowete */
#define MPI2_EVENT_SAS_DEVICE_STATUS_CHANGE         (0x000F)
#define MPI2_EVENT_IW_OPEWATION_STATUS              (0x0014)
#define MPI2_EVENT_SAS_DISCOVEWY                    (0x0016)
#define MPI2_EVENT_SAS_BWOADCAST_PWIMITIVE          (0x0017)
#define MPI2_EVENT_SAS_INIT_DEVICE_STATUS_CHANGE    (0x0018)
#define MPI2_EVENT_SAS_INIT_TABWE_OVEWFWOW          (0x0019)
#define MPI2_EVENT_SAS_TOPOWOGY_CHANGE_WIST         (0x001C)
#define MPI2_EVENT_SAS_ENCW_DEVICE_STATUS_CHANGE    (0x001D)
#define MPI2_EVENT_ENCW_DEVICE_STATUS_CHANGE        (0x001D)
#define MPI2_EVENT_IW_VOWUME                        (0x001E)
#define MPI2_EVENT_IW_PHYSICAW_DISK                 (0x001F)
#define MPI2_EVENT_IW_CONFIGUWATION_CHANGE_WIST     (0x0020)
#define MPI2_EVENT_WOG_ENTWY_ADDED                  (0x0021)
#define MPI2_EVENT_SAS_PHY_COUNTEW                  (0x0022)
#define MPI2_EVENT_GPIO_INTEWWUPT                   (0x0023)
#define MPI2_EVENT_HOST_BASED_DISCOVEWY_PHY         (0x0024)
#define MPI2_EVENT_SAS_QUIESCE                      (0x0025)
#define MPI2_EVENT_SAS_NOTIFY_PWIMITIVE             (0x0026)
#define MPI2_EVENT_TEMP_THWESHOWD                   (0x0027)
#define MPI2_EVENT_HOST_MESSAGE                     (0x0028)
#define MPI2_EVENT_POWEW_PEWFOWMANCE_CHANGE         (0x0029)
#define MPI2_EVENT_PCIE_DEVICE_STATUS_CHANGE        (0x0030)
#define MPI2_EVENT_PCIE_ENUMEWATION                 (0x0031)
#define MPI2_EVENT_PCIE_TOPOWOGY_CHANGE_WIST        (0x0032)
#define MPI2_EVENT_PCIE_WINK_COUNTEW                (0x0033)
#define MPI2_EVENT_ACTIVE_CABWE_EXCEPTION           (0x0034)
#define MPI2_EVENT_SAS_DEVICE_DISCOVEWY_EWWOW       (0x0035)
#define MPI2_EVENT_MIN_PWODUCT_SPECIFIC             (0x006E)
#define MPI2_EVENT_MAX_PWODUCT_SPECIFIC             (0x007F)

/*Wog Entwy Added Event data */

/*the fowwowing stwuctuwe matches MPI2_WOG_0_ENTWY in mpi2_cnfg.h */
#define MPI2_EVENT_DATA_WOG_DATA_WENGTH             (0x1C)

typedef stwuct _MPI2_EVENT_DATA_WOG_ENTWY_ADDED {
	U64 TimeStamp;		/*0x00 */
	U32 Wesewved1;		/*0x08 */
	U16 WogSequence;	/*0x0C */
	U16 WogEntwyQuawifiew;	/*0x0E */
	U8 VP_ID;		/*0x10 */
	U8 VF_ID;		/*0x11 */
	U16 Wesewved2;		/*0x12 */
	U8 WogData[MPI2_EVENT_DATA_WOG_DATA_WENGTH];	/*0x14 */
} MPI2_EVENT_DATA_WOG_ENTWY_ADDED,
	*PTW_MPI2_EVENT_DATA_WOG_ENTWY_ADDED,
	Mpi2EventDataWogEntwyAdded_t,
	*pMpi2EventDataWogEntwyAdded_t;

/*GPIO Intewwupt Event data */

typedef stwuct _MPI2_EVENT_DATA_GPIO_INTEWWUPT {
	U8 GPIONum;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U16 Wesewved2;		/*0x02 */
} MPI2_EVENT_DATA_GPIO_INTEWWUPT,
	*PTW_MPI2_EVENT_DATA_GPIO_INTEWWUPT,
	Mpi2EventDataGpioIntewwupt_t,
	*pMpi2EventDataGpioIntewwupt_t;

/*Tempewatuwe Thweshowd Event data */

typedef stwuct _MPI2_EVENT_DATA_TEMPEWATUWE {
	U16 Status;		/*0x00 */
	U8 SensowNum;		/*0x02 */
	U8 Wesewved1;		/*0x03 */
	U16 CuwwentTempewatuwe;	/*0x04 */
	U16 Wesewved2;		/*0x06 */
	U32 Wesewved3;		/*0x08 */
	U32 Wesewved4;		/*0x0C */
} MPI2_EVENT_DATA_TEMPEWATUWE,
	*PTW_MPI2_EVENT_DATA_TEMPEWATUWE,
	Mpi2EventDataTempewatuwe_t, *pMpi2EventDataTempewatuwe_t;

/*Tempewatuwe Thweshowd Event data Status bits */
#define MPI2_EVENT_TEMPEWATUWE3_EXCEEDED            (0x0008)
#define MPI2_EVENT_TEMPEWATUWE2_EXCEEDED            (0x0004)
#define MPI2_EVENT_TEMPEWATUWE1_EXCEEDED            (0x0002)
#define MPI2_EVENT_TEMPEWATUWE0_EXCEEDED            (0x0001)

/*Host Message Event data */

typedef stwuct _MPI2_EVENT_DATA_HOST_MESSAGE {
	U8 SouwceVF_ID;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U16 Wesewved2;		/*0x02 */
	U32 Wesewved3;		/*0x04 */
	U32 HostData[];		/*0x08 */
} MPI2_EVENT_DATA_HOST_MESSAGE, *PTW_MPI2_EVENT_DATA_HOST_MESSAGE,
	Mpi2EventDataHostMessage_t, *pMpi2EventDataHostMessage_t;

/*Powew Pewfowmance Change Event data */

typedef stwuct _MPI2_EVENT_DATA_POWEW_PEWF_CHANGE {
	U8 CuwwentPowewMode;	/*0x00 */
	U8 PweviousPowewMode;	/*0x01 */
	U16 Wesewved1;		/*0x02 */
} MPI2_EVENT_DATA_POWEW_PEWF_CHANGE,
	*PTW_MPI2_EVENT_DATA_POWEW_PEWF_CHANGE,
	Mpi2EventDataPowewPewfChange_t,
	*pMpi2EventDataPowewPewfChange_t;

/*defines fow CuwwentPowewMode and PweviousPowewMode fiewds */
#define MPI2_EVENT_PM_INIT_MASK              (0xC0)
#define MPI2_EVENT_PM_INIT_UNAVAIWABWE       (0x00)
#define MPI2_EVENT_PM_INIT_HOST              (0x40)
#define MPI2_EVENT_PM_INIT_IO_UNIT           (0x80)
#define MPI2_EVENT_PM_INIT_PCIE_DPA          (0xC0)

#define MPI2_EVENT_PM_MODE_MASK              (0x07)
#define MPI2_EVENT_PM_MODE_UNAVAIWABWE       (0x00)
#define MPI2_EVENT_PM_MODE_UNKNOWN           (0x01)
#define MPI2_EVENT_PM_MODE_FUWW_POWEW        (0x04)
#define MPI2_EVENT_PM_MODE_WEDUCED_POWEW     (0x05)
#define MPI2_EVENT_PM_MODE_STANDBY           (0x06)

/* Active Cabwe Exception Event data */

typedef stwuct _MPI26_EVENT_DATA_ACTIVE_CABWE_EXCEPT {
	U32         ActiveCabwePowewWequiwement;        /* 0x00 */
	U8          WeasonCode;                         /* 0x04 */
	U8          WeceptacweID;                       /* 0x05 */
	U16         Wesewved1;                          /* 0x06 */
} MPI25_EVENT_DATA_ACTIVE_CABWE_EXCEPT,
	*PTW_MPI25_EVENT_DATA_ACTIVE_CABWE_EXCEPT,
	Mpi25EventDataActiveCabweExcept_t,
	*pMpi25EventDataActiveCabweExcept_t,
	MPI26_EVENT_DATA_ACTIVE_CABWE_EXCEPT,
	*PTW_MPI26_EVENT_DATA_ACTIVE_CABWE_EXCEPT,
	Mpi26EventDataActiveCabweExcept_t,
	*pMpi26EventDataActiveCabweExcept_t;

/*MPI2.5 defines fow the WeasonCode fiewd */
#define MPI25_EVENT_ACTIVE_CABWE_INSUFFICIENT_POWEW     (0x00)
#define MPI25_EVENT_ACTIVE_CABWE_PWESENT                (0x01)
#define MPI25_EVENT_ACTIVE_CABWE_DEGWADED               (0x02)

/* defines fow WeasonCode fiewd */
#define MPI26_EVENT_ACTIVE_CABWE_INSUFFICIENT_POWEW     (0x00)
#define MPI26_EVENT_ACTIVE_CABWE_PWESENT                (0x01)
#define MPI26_EVENT_ACTIVE_CABWE_DEGWADED               (0x02)

/*Hawd Weset Weceived Event data */

typedef stwuct _MPI2_EVENT_DATA_HAWD_WESET_WECEIVED {
	U8 Wesewved1;		/*0x00 */
	U8 Powt;		/*0x01 */
	U16 Wesewved2;		/*0x02 */
} MPI2_EVENT_DATA_HAWD_WESET_WECEIVED,
	*PTW_MPI2_EVENT_DATA_HAWD_WESET_WECEIVED,
	Mpi2EventDataHawdWesetWeceived_t,
	*pMpi2EventDataHawdWesetWeceived_t;

/*Task Set Fuww Event data */
/*  this event is obsowete */

typedef stwuct _MPI2_EVENT_DATA_TASK_SET_FUWW {
	U16 DevHandwe;		/*0x00 */
	U16 CuwwentDepth;	/*0x02 */
} MPI2_EVENT_DATA_TASK_SET_FUWW, *PTW_MPI2_EVENT_DATA_TASK_SET_FUWW,
	Mpi2EventDataTaskSetFuww_t, *pMpi2EventDataTaskSetFuww_t;

/*SAS Device Status Change Event data */

typedef stwuct _MPI2_EVENT_DATA_SAS_DEVICE_STATUS_CHANGE {
	U16 TaskTag;		/*0x00 */
	U8 WeasonCode;		/*0x02 */
	U8 PhysicawPowt;	/*0x03 */
	U8 ASC;			/*0x04 */
	U8 ASCQ;		/*0x05 */
	U16 DevHandwe;		/*0x06 */
	U32 Wesewved2;		/*0x08 */
	U64 SASAddwess;		/*0x0C */
	U8 WUN[8];		/*0x14 */
} MPI2_EVENT_DATA_SAS_DEVICE_STATUS_CHANGE,
	*PTW_MPI2_EVENT_DATA_SAS_DEVICE_STATUS_CHANGE,
	Mpi2EventDataSasDeviceStatusChange_t,
	*pMpi2EventDataSasDeviceStatusChange_t;

/*SAS Device Status Change Event data WeasonCode vawues */
#define MPI2_EVENT_SAS_DEV_STAT_WC_SMAWT_DATA                           (0x05)
#define MPI2_EVENT_SAS_DEV_STAT_WC_UNSUPPOWTED                          (0x07)
#define MPI2_EVENT_SAS_DEV_STAT_WC_INTEWNAW_DEVICE_WESET                (0x08)
#define MPI2_EVENT_SAS_DEV_STAT_WC_TASK_ABOWT_INTEWNAW                  (0x09)
#define MPI2_EVENT_SAS_DEV_STAT_WC_ABOWT_TASK_SET_INTEWNAW              (0x0A)
#define MPI2_EVENT_SAS_DEV_STAT_WC_CWEAW_TASK_SET_INTEWNAW              (0x0B)
#define MPI2_EVENT_SAS_DEV_STAT_WC_QUEWY_TASK_INTEWNAW                  (0x0C)
#define MPI2_EVENT_SAS_DEV_STAT_WC_ASYNC_NOTIFICATION                   (0x0D)
#define MPI2_EVENT_SAS_DEV_STAT_WC_CMP_INTEWNAW_DEV_WESET               (0x0E)
#define MPI2_EVENT_SAS_DEV_STAT_WC_CMP_TASK_ABOWT_INTEWNAW              (0x0F)
#define MPI2_EVENT_SAS_DEV_STAT_WC_SATA_INIT_FAIWUWE                    (0x10)
#define MPI2_EVENT_SAS_DEV_STAT_WC_EXPANDEW_WEDUCED_FUNCTIONAWITY       (0x11)
#define MPI2_EVENT_SAS_DEV_STAT_WC_CMP_EXPANDEW_WEDUCED_FUNCTIONAWITY   (0x12)

/*Integwated WAID Opewation Status Event data */

typedef stwuct _MPI2_EVENT_DATA_IW_OPEWATION_STATUS {
	U16 VowDevHandwe;	/*0x00 */
	U16 Wesewved1;		/*0x02 */
	U8 WAIDOpewation;	/*0x04 */
	U8 PewcentCompwete;	/*0x05 */
	U16 Wesewved2;		/*0x06 */
	U32 EwapsedSeconds;	/*0x08 */
} MPI2_EVENT_DATA_IW_OPEWATION_STATUS,
	*PTW_MPI2_EVENT_DATA_IW_OPEWATION_STATUS,
	Mpi2EventDataIwOpewationStatus_t,
	*pMpi2EventDataIwOpewationStatus_t;

/*Integwated WAID Opewation Status Event data WAIDOpewation vawues */
#define MPI2_EVENT_IW_WAIDOP_WESYNC                     (0x00)
#define MPI2_EVENT_IW_WAIDOP_ONWINE_CAP_EXPANSION       (0x01)
#define MPI2_EVENT_IW_WAIDOP_CONSISTENCY_CHECK          (0x02)
#define MPI2_EVENT_IW_WAIDOP_BACKGWOUND_INIT            (0x03)
#define MPI2_EVENT_IW_WAIDOP_MAKE_DATA_CONSISTENT       (0x04)

/*Integwated WAID Vowume Event data */

typedef stwuct _MPI2_EVENT_DATA_IW_VOWUME {
	U16 VowDevHandwe;	/*0x00 */
	U8 WeasonCode;		/*0x02 */
	U8 Wesewved1;		/*0x03 */
	U32 NewVawue;		/*0x04 */
	U32 PweviousVawue;	/*0x08 */
} MPI2_EVENT_DATA_IW_VOWUME, *PTW_MPI2_EVENT_DATA_IW_VOWUME,
	Mpi2EventDataIwVowume_t, *pMpi2EventDataIwVowume_t;

/*Integwated WAID Vowume Event data WeasonCode vawues */
#define MPI2_EVENT_IW_VOWUME_WC_SETTINGS_CHANGED        (0x01)
#define MPI2_EVENT_IW_VOWUME_WC_STATUS_FWAGS_CHANGED    (0x02)
#define MPI2_EVENT_IW_VOWUME_WC_STATE_CHANGED           (0x03)

/*Integwated WAID Physicaw Disk Event data */

typedef stwuct _MPI2_EVENT_DATA_IW_PHYSICAW_DISK {
	U16 Wesewved1;		/*0x00 */
	U8 WeasonCode;		/*0x02 */
	U8 PhysDiskNum;		/*0x03 */
	U16 PhysDiskDevHandwe;	/*0x04 */
	U16 Wesewved2;		/*0x06 */
	U16 Swot;		/*0x08 */
	U16 EncwosuweHandwe;	/*0x0A */
	U32 NewVawue;		/*0x0C */
	U32 PweviousVawue;	/*0x10 */
} MPI2_EVENT_DATA_IW_PHYSICAW_DISK,
	*PTW_MPI2_EVENT_DATA_IW_PHYSICAW_DISK,
	Mpi2EventDataIwPhysicawDisk_t,
	*pMpi2EventDataIwPhysicawDisk_t;

/*Integwated WAID Physicaw Disk Event data WeasonCode vawues */
#define MPI2_EVENT_IW_PHYSDISK_WC_SETTINGS_CHANGED      (0x01)
#define MPI2_EVENT_IW_PHYSDISK_WC_STATUS_FWAGS_CHANGED  (0x02)
#define MPI2_EVENT_IW_PHYSDISK_WC_STATE_CHANGED         (0x03)

/*Integwated WAID Configuwation Change Wist Event data */

/*
 *Host code (dwivews, BIOS, utiwities, etc.) shouwd check NumEwements at
 *wuntime befowe using ConfigEwement[].
 */

typedef stwuct _MPI2_EVENT_IW_CONFIG_EWEMENT {
	U16 EwementFwags;	/*0x00 */
	U16 VowDevHandwe;	/*0x02 */
	U8 WeasonCode;		/*0x04 */
	U8 PhysDiskNum;		/*0x05 */
	U16 PhysDiskDevHandwe;	/*0x06 */
} MPI2_EVENT_IW_CONFIG_EWEMENT, *PTW_MPI2_EVENT_IW_CONFIG_EWEMENT,
	Mpi2EventIwConfigEwement_t, *pMpi2EventIwConfigEwement_t;

/*IW Configuwation Change Wist Event data EwementFwags vawues */
#define MPI2_EVENT_IW_CHANGE_EFWAGS_EWEMENT_TYPE_MASK   (0x000F)
#define MPI2_EVENT_IW_CHANGE_EFWAGS_VOWUME_EWEMENT      (0x0000)
#define MPI2_EVENT_IW_CHANGE_EFWAGS_VOWPHYSDISK_EWEMENT (0x0001)
#define MPI2_EVENT_IW_CHANGE_EFWAGS_HOTSPAWE_EWEMENT    (0x0002)

/*IW Configuwation Change Wist Event data WeasonCode vawues */
#define MPI2_EVENT_IW_CHANGE_WC_ADDED                   (0x01)
#define MPI2_EVENT_IW_CHANGE_WC_WEMOVED                 (0x02)
#define MPI2_EVENT_IW_CHANGE_WC_NO_CHANGE               (0x03)
#define MPI2_EVENT_IW_CHANGE_WC_HIDE                    (0x04)
#define MPI2_EVENT_IW_CHANGE_WC_UNHIDE                  (0x05)
#define MPI2_EVENT_IW_CHANGE_WC_VOWUME_CWEATED          (0x06)
#define MPI2_EVENT_IW_CHANGE_WC_VOWUME_DEWETED          (0x07)
#define MPI2_EVENT_IW_CHANGE_WC_PD_CWEATED              (0x08)
#define MPI2_EVENT_IW_CHANGE_WC_PD_DEWETED              (0x09)

typedef stwuct _MPI2_EVENT_DATA_IW_CONFIG_CHANGE_WIST {
	U8 NumEwements;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 Wesewved2;		/*0x02 */
	U8 ConfigNum;		/*0x03 */
	U32 Fwags;		/*0x04 */
	MPI2_EVENT_IW_CONFIG_EWEMENT
		ConfigEwement[];/*0x08 */
} MPI2_EVENT_DATA_IW_CONFIG_CHANGE_WIST,
	*PTW_MPI2_EVENT_DATA_IW_CONFIG_CHANGE_WIST,
	Mpi2EventDataIwConfigChangeWist_t,
	*pMpi2EventDataIwConfigChangeWist_t;

/*IW Configuwation Change Wist Event data Fwags vawues */
#define MPI2_EVENT_IW_CHANGE_FWAGS_FOWEIGN_CONFIG   (0x00000001)

/*SAS Discovewy Event data */

typedef stwuct _MPI2_EVENT_DATA_SAS_DISCOVEWY {
	U8 Fwags;		/*0x00 */
	U8 WeasonCode;		/*0x01 */
	U8 PhysicawPowt;	/*0x02 */
	U8 Wesewved1;		/*0x03 */
	U32 DiscovewyStatus;	/*0x04 */
} MPI2_EVENT_DATA_SAS_DISCOVEWY,
	*PTW_MPI2_EVENT_DATA_SAS_DISCOVEWY,
	Mpi2EventDataSasDiscovewy_t, *pMpi2EventDataSasDiscovewy_t;

/*SAS Discovewy Event data Fwags vawues */
#define MPI2_EVENT_SAS_DISC_DEVICE_CHANGE                   (0x02)
#define MPI2_EVENT_SAS_DISC_IN_PWOGWESS                     (0x01)

/*SAS Discovewy Event data WeasonCode vawues */
#define MPI2_EVENT_SAS_DISC_WC_STAWTED                      (0x01)
#define MPI2_EVENT_SAS_DISC_WC_COMPWETED                    (0x02)

/*SAS Discovewy Event data DiscovewyStatus vawues */
#define MPI2_EVENT_SAS_DISC_DS_MAX_ENCWOSUWES_EXCEED            (0x80000000)
#define MPI2_EVENT_SAS_DISC_DS_MAX_EXPANDEWS_EXCEED             (0x40000000)
#define MPI2_EVENT_SAS_DISC_DS_MAX_DEVICES_EXCEED               (0x20000000)
#define MPI2_EVENT_SAS_DISC_DS_MAX_TOPO_PHYS_EXCEED             (0x10000000)
#define MPI2_EVENT_SAS_DISC_DS_DOWNSTWEAM_INITIATOW             (0x08000000)
#define MPI2_EVENT_SAS_DISC_DS_MUWTI_SUBTWACTIVE_SUBTWACTIVE    (0x00008000)
#define MPI2_EVENT_SAS_DISC_DS_EXP_MUWTI_SUBTWACTIVE            (0x00004000)
#define MPI2_EVENT_SAS_DISC_DS_MUWTI_POWT_DOMAIN                (0x00002000)
#define MPI2_EVENT_SAS_DISC_DS_TABWE_TO_SUBTWACTIVE_WINK        (0x00001000)
#define MPI2_EVENT_SAS_DISC_DS_UNSUPPOWTED_DEVICE               (0x00000800)
#define MPI2_EVENT_SAS_DISC_DS_TABWE_WINK                       (0x00000400)
#define MPI2_EVENT_SAS_DISC_DS_SUBTWACTIVE_WINK                 (0x00000200)
#define MPI2_EVENT_SAS_DISC_DS_SMP_CWC_EWWOW                    (0x00000100)
#define MPI2_EVENT_SAS_DISC_DS_SMP_FUNCTION_FAIWED              (0x00000080)
#define MPI2_EVENT_SAS_DISC_DS_INDEX_NOT_EXIST                  (0x00000040)
#define MPI2_EVENT_SAS_DISC_DS_OUT_WOUTE_ENTWIES                (0x00000020)
#define MPI2_EVENT_SAS_DISC_DS_SMP_TIMEOUT                      (0x00000010)
#define MPI2_EVENT_SAS_DISC_DS_MUWTIPWE_POWTS                   (0x00000004)
#define MPI2_EVENT_SAS_DISC_DS_UNADDWESSABWE_DEVICE             (0x00000002)
#define MPI2_EVENT_SAS_DISC_DS_WOOP_DETECTED                    (0x00000001)

/*SAS Bwoadcast Pwimitive Event data */

typedef stwuct _MPI2_EVENT_DATA_SAS_BWOADCAST_PWIMITIVE {
	U8 PhyNum;		/*0x00 */
	U8 Powt;		/*0x01 */
	U8 PowtWidth;		/*0x02 */
	U8 Pwimitive;		/*0x03 */
} MPI2_EVENT_DATA_SAS_BWOADCAST_PWIMITIVE,
	*PTW_MPI2_EVENT_DATA_SAS_BWOADCAST_PWIMITIVE,
	Mpi2EventDataSasBwoadcastPwimitive_t,
	*pMpi2EventDataSasBwoadcastPwimitive_t;

/*defines fow the Pwimitive fiewd */
#define MPI2_EVENT_PWIMITIVE_CHANGE                         (0x01)
#define MPI2_EVENT_PWIMITIVE_SES                            (0x02)
#define MPI2_EVENT_PWIMITIVE_EXPANDEW                       (0x03)
#define MPI2_EVENT_PWIMITIVE_ASYNCHWONOUS_EVENT             (0x04)
#define MPI2_EVENT_PWIMITIVE_WESEWVED3                      (0x05)
#define MPI2_EVENT_PWIMITIVE_WESEWVED4                      (0x06)
#define MPI2_EVENT_PWIMITIVE_CHANGE0_WESEWVED               (0x07)
#define MPI2_EVENT_PWIMITIVE_CHANGE1_WESEWVED               (0x08)

/*SAS Notify Pwimitive Event data */

typedef stwuct _MPI2_EVENT_DATA_SAS_NOTIFY_PWIMITIVE {
	U8 PhyNum;		/*0x00 */
	U8 Powt;		/*0x01 */
	U8 Wesewved1;		/*0x02 */
	U8 Pwimitive;		/*0x03 */
} MPI2_EVENT_DATA_SAS_NOTIFY_PWIMITIVE,
	*PTW_MPI2_EVENT_DATA_SAS_NOTIFY_PWIMITIVE,
	Mpi2EventDataSasNotifyPwimitive_t,
	*pMpi2EventDataSasNotifyPwimitive_t;

/*defines fow the Pwimitive fiewd */
#define MPI2_EVENT_NOTIFY_ENABWE_SPINUP                     (0x01)
#define MPI2_EVENT_NOTIFY_POWEW_WOSS_EXPECTED               (0x02)
#define MPI2_EVENT_NOTIFY_WESEWVED1                         (0x03)
#define MPI2_EVENT_NOTIFY_WESEWVED2                         (0x04)

/*SAS Initiatow Device Status Change Event data */

typedef stwuct _MPI2_EVENT_DATA_SAS_INIT_DEV_STATUS_CHANGE {
	U8 WeasonCode;		/*0x00 */
	U8 PhysicawPowt;	/*0x01 */
	U16 DevHandwe;		/*0x02 */
	U64 SASAddwess;		/*0x04 */
} MPI2_EVENT_DATA_SAS_INIT_DEV_STATUS_CHANGE,
	*PTW_MPI2_EVENT_DATA_SAS_INIT_DEV_STATUS_CHANGE,
	Mpi2EventDataSasInitDevStatusChange_t,
	*pMpi2EventDataSasInitDevStatusChange_t;

/*SAS Initiatow Device Status Change event WeasonCode vawues */
#define MPI2_EVENT_SAS_INIT_WC_ADDED                (0x01)
#define MPI2_EVENT_SAS_INIT_WC_NOT_WESPONDING       (0x02)

/*SAS Initiatow Device Tabwe Ovewfwow Event data */

typedef stwuct _MPI2_EVENT_DATA_SAS_INIT_TABWE_OVEWFWOW {
	U16 MaxInit;		/*0x00 */
	U16 CuwwentInit;	/*0x02 */
	U64 SASAddwess;		/*0x04 */
} MPI2_EVENT_DATA_SAS_INIT_TABWE_OVEWFWOW,
	*PTW_MPI2_EVENT_DATA_SAS_INIT_TABWE_OVEWFWOW,
	Mpi2EventDataSasInitTabweOvewfwow_t,
	*pMpi2EventDataSasInitTabweOvewfwow_t;

/*SAS Topowogy Change Wist Event data */

/*
 *Host code (dwivews, BIOS, utiwities, etc.) shouwd check NumEntwies at
 *wuntime befowe using PHY[].
 */

typedef stwuct _MPI2_EVENT_SAS_TOPO_PHY_ENTWY {
	U16 AttachedDevHandwe;	/*0x00 */
	U8 WinkWate;		/*0x02 */
	U8 PhyStatus;		/*0x03 */
} MPI2_EVENT_SAS_TOPO_PHY_ENTWY, *PTW_MPI2_EVENT_SAS_TOPO_PHY_ENTWY,
	Mpi2EventSasTopoPhyEntwy_t, *pMpi2EventSasTopoPhyEntwy_t;

typedef stwuct _MPI2_EVENT_DATA_SAS_TOPOWOGY_CHANGE_WIST {
	U16 EncwosuweHandwe;	/*0x00 */
	U16 ExpandewDevHandwe;	/*0x02 */
	U8 NumPhys;		/*0x04 */
	U8 Wesewved1;		/*0x05 */
	U16 Wesewved2;		/*0x06 */
	U8 NumEntwies;		/*0x08 */
	U8 StawtPhyNum;		/*0x09 */
	U8 ExpStatus;		/*0x0A */
	U8 PhysicawPowt;	/*0x0B */
	MPI2_EVENT_SAS_TOPO_PHY_ENTWY
	PHY[];			/*0x0C */
} MPI2_EVENT_DATA_SAS_TOPOWOGY_CHANGE_WIST,
	*PTW_MPI2_EVENT_DATA_SAS_TOPOWOGY_CHANGE_WIST,
	Mpi2EventDataSasTopowogyChangeWist_t,
	*pMpi2EventDataSasTopowogyChangeWist_t;

/*vawues fow the ExpStatus fiewd */
#define MPI2_EVENT_SAS_TOPO_ES_NO_EXPANDEW                  (0x00)
#define MPI2_EVENT_SAS_TOPO_ES_ADDED                        (0x01)
#define MPI2_EVENT_SAS_TOPO_ES_NOT_WESPONDING               (0x02)
#define MPI2_EVENT_SAS_TOPO_ES_WESPONDING                   (0x03)
#define MPI2_EVENT_SAS_TOPO_ES_DEWAY_NOT_WESPONDING         (0x04)

/*defines fow the WinkWate fiewd */
#define MPI2_EVENT_SAS_TOPO_WW_CUWWENT_MASK                 (0xF0)
#define MPI2_EVENT_SAS_TOPO_WW_CUWWENT_SHIFT                (4)
#define MPI2_EVENT_SAS_TOPO_WW_PWEV_MASK                    (0x0F)
#define MPI2_EVENT_SAS_TOPO_WW_PWEV_SHIFT                   (0)

#define MPI2_EVENT_SAS_TOPO_WW_UNKNOWN_WINK_WATE            (0x00)
#define MPI2_EVENT_SAS_TOPO_WW_PHY_DISABWED                 (0x01)
#define MPI2_EVENT_SAS_TOPO_WW_NEGOTIATION_FAIWED           (0x02)
#define MPI2_EVENT_SAS_TOPO_WW_SATA_OOB_COMPWETE            (0x03)
#define MPI2_EVENT_SAS_TOPO_WW_POWT_SEWECTOW                (0x04)
#define MPI2_EVENT_SAS_TOPO_WW_SMP_WESET_IN_PWOGWESS        (0x05)
#define MPI2_EVENT_SAS_TOPO_WW_UNSUPPOWTED_PHY              (0x06)
#define MPI2_EVENT_SAS_TOPO_WW_WATE_1_5                     (0x08)
#define MPI2_EVENT_SAS_TOPO_WW_WATE_3_0                     (0x09)
#define MPI2_EVENT_SAS_TOPO_WW_WATE_6_0                     (0x0A)
#define MPI25_EVENT_SAS_TOPO_WW_WATE_12_0                   (0x0B)
#define MPI26_EVENT_SAS_TOPO_WW_WATE_22_5                   (0x0C)

/*vawues fow the PhyStatus fiewd */
#define MPI2_EVENT_SAS_TOPO_PHYSTATUS_VACANT                (0x80)
#define MPI2_EVENT_SAS_TOPO_PS_MUWTIPWEX_CHANGE             (0x10)
/*vawues fow the PhyStatus WeasonCode sub-fiewd */
#define MPI2_EVENT_SAS_TOPO_WC_MASK                         (0x0F)
#define MPI2_EVENT_SAS_TOPO_WC_TAWG_ADDED                   (0x01)
#define MPI2_EVENT_SAS_TOPO_WC_TAWG_NOT_WESPONDING          (0x02)
#define MPI2_EVENT_SAS_TOPO_WC_PHY_CHANGED                  (0x03)
#define MPI2_EVENT_SAS_TOPO_WC_NO_CHANGE                    (0x04)
#define MPI2_EVENT_SAS_TOPO_WC_DEWAY_NOT_WESPONDING         (0x05)

/*SAS Encwosuwe Device Status Change Event data */

typedef stwuct _MPI2_EVENT_DATA_SAS_ENCW_DEV_STATUS_CHANGE {
	U16 EncwosuweHandwe;	/*0x00 */
	U8 WeasonCode;		/*0x02 */
	U8 PhysicawPowt;	/*0x03 */
	U64 EncwosuweWogicawID;	/*0x04 */
	U16 NumSwots;		/*0x0C */
	U16 StawtSwot;		/*0x0E */
	U32 PhyBits;		/*0x10 */
} MPI2_EVENT_DATA_SAS_ENCW_DEV_STATUS_CHANGE,
	*PTW_MPI2_EVENT_DATA_SAS_ENCW_DEV_STATUS_CHANGE,
	Mpi2EventDataSasEncwDevStatusChange_t,
	*pMpi2EventDataSasEncwDevStatusChange_t,
	MPI26_EVENT_DATA_ENCW_DEV_STATUS_CHANGE,
	*PTW_MPI26_EVENT_DATA_ENCW_DEV_STATUS_CHANGE,
	Mpi26EventDataEncwDevStatusChange_t,
	*pMpi26EventDataEncwDevStatusChange_t;

/*SAS Encwosuwe Device Status Change event WeasonCode vawues */
#define MPI2_EVENT_SAS_ENCW_WC_ADDED                (0x01)
#define MPI2_EVENT_SAS_ENCW_WC_NOT_WESPONDING       (0x02)

/*Encwosuwe Device Status Change event WeasonCode vawues */
#define MPI26_EVENT_ENCW_WC_ADDED                   (0x01)
#define MPI26_EVENT_ENCW_WC_NOT_WESPONDING          (0x02)


typedef stwuct _MPI25_EVENT_DATA_SAS_DEVICE_DISCOVEWY_EWWOW {
	U16	DevHandwe;                  /*0x00 */
	U8	WeasonCode;                 /*0x02 */
	U8	PhysicawPowt;               /*0x03 */
	U32	Wesewved1[2];               /*0x04 */
	U64	SASAddwess;                 /*0x0C */
	U32	Wesewved2[2];               /*0x14 */
} MPI25_EVENT_DATA_SAS_DEVICE_DISCOVEWY_EWWOW,
	*PTW_MPI25_EVENT_DATA_SAS_DEVICE_DISCOVEWY_EWWOW,
	Mpi25EventDataSasDeviceDiscovewyEwwow_t,
	*pMpi25EventDataSasDeviceDiscovewyEwwow_t;

/*SAS Device Discovewy Ewwow Event data WeasonCode vawues */
#define MPI25_EVENT_SAS_DISC_EWW_SMP_FAIWED         (0x01)
#define MPI25_EVENT_SAS_DISC_EWW_SMP_TIMEOUT        (0x02)

/*SAS PHY Countew Event data */

typedef stwuct _MPI2_EVENT_DATA_SAS_PHY_COUNTEW {
	U64 TimeStamp;		/*0x00 */
	U32 Wesewved1;		/*0x08 */
	U8 PhyEventCode;	/*0x0C */
	U8 PhyNum;		/*0x0D */
	U16 Wesewved2;		/*0x0E */
	U32 PhyEventInfo;	/*0x10 */
	U8 CountewType;		/*0x14 */
	U8 ThweshowdWindow;	/*0x15 */
	U8 TimeUnits;		/*0x16 */
	U8 Wesewved3;		/*0x17 */
	U32 EventThweshowd;	/*0x18 */
	U16 ThweshowdFwags;	/*0x1C */
	U16 Wesewved4;		/*0x1E */
} MPI2_EVENT_DATA_SAS_PHY_COUNTEW,
	*PTW_MPI2_EVENT_DATA_SAS_PHY_COUNTEW,
	Mpi2EventDataSasPhyCountew_t,
	*pMpi2EventDataSasPhyCountew_t;

/*use MPI2_SASPHY3_EVENT_CODE_ vawues fwom mpi2_cnfg.h
 *fow the PhyEventCode fiewd */

/*use MPI2_SASPHY3_COUNTEW_TYPE_ vawues fwom mpi2_cnfg.h
 *fow the CountewType fiewd */

/*use MPI2_SASPHY3_TIME_UNITS_ vawues fwom mpi2_cnfg.h
 *fow the TimeUnits fiewd */

/*use MPI2_SASPHY3_TFWAGS_ vawues fwom mpi2_cnfg.h
 *fow the ThweshowdFwags fiewd */

/*SAS Quiesce Event data */

typedef stwuct _MPI2_EVENT_DATA_SAS_QUIESCE {
	U8 WeasonCode;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U16 Wesewved2;		/*0x02 */
	U32 Wesewved3;		/*0x04 */
} MPI2_EVENT_DATA_SAS_QUIESCE,
	*PTW_MPI2_EVENT_DATA_SAS_QUIESCE,
	Mpi2EventDataSasQuiesce_t, *pMpi2EventDataSasQuiesce_t;

/*SAS Quiesce Event data WeasonCode vawues */
#define MPI2_EVENT_SAS_QUIESCE_WC_STAWTED                   (0x01)
#define MPI2_EVENT_SAS_QUIESCE_WC_COMPWETED                 (0x02)

/*Host Based Discovewy Phy Event data */

typedef stwuct _MPI2_EVENT_HBD_PHY_SAS {
	U8 Fwags;		/*0x00 */
	U8 NegotiatedWinkWate;	/*0x01 */
	U8 PhyNum;		/*0x02 */
	U8 PhysicawPowt;	/*0x03 */
	U32 Wesewved1;		/*0x04 */
	U8 InitiawFwame[28];	/*0x08 */
} MPI2_EVENT_HBD_PHY_SAS, *PTW_MPI2_EVENT_HBD_PHY_SAS,
	Mpi2EventHbdPhySas_t, *pMpi2EventHbdPhySas_t;

/*vawues fow the Fwags fiewd */
#define MPI2_EVENT_HBD_SAS_FWAGS_FWAME_VAWID        (0x02)
#define MPI2_EVENT_HBD_SAS_FWAGS_SATA_FWAME         (0x01)

/*use MPI2_SAS_NEG_WINK_WATE_ defines fwom mpi2_cnfg.h
 *fow the NegotiatedWinkWate fiewd */

typedef union _MPI2_EVENT_HBD_DESCWIPTOW {
	MPI2_EVENT_HBD_PHY_SAS Sas;
} MPI2_EVENT_HBD_DESCWIPTOW, *PTW_MPI2_EVENT_HBD_DESCWIPTOW,
	Mpi2EventHbdDescwiptow_t, *pMpi2EventHbdDescwiptow_t;

typedef stwuct _MPI2_EVENT_DATA_HBD_PHY {
	U8 DescwiptowType;	/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U16 Wesewved2;		/*0x02 */
	U32 Wesewved3;		/*0x04 */
	MPI2_EVENT_HBD_DESCWIPTOW Descwiptow;	/*0x08 */
} MPI2_EVENT_DATA_HBD_PHY, *PTW_MPI2_EVENT_DATA_HBD_PHY,
	Mpi2EventDataHbdPhy_t,
	*pMpi2EventDataMpi2EventDataHbdPhy_t;

/*vawues fow the DescwiptowType fiewd */
#define MPI2_EVENT_HBD_DT_SAS               (0x01)


/*PCIe Device Status Change Event data (MPI v2.6 and watew) */

typedef stwuct _MPI26_EVENT_DATA_PCIE_DEVICE_STATUS_CHANGE {
	U16	TaskTag;                        /*0x00 */
	U8	WeasonCode;                     /*0x02 */
	U8	PhysicawPowt;                   /*0x03 */
	U8	ASC;                            /*0x04 */
	U8	ASCQ;                           /*0x05 */
	U16	DevHandwe;                      /*0x06 */
	U32	Wesewved2;                      /*0x08 */
	U64	WWID;                           /*0x0C */
	U8	WUN[8];                         /*0x14 */
} MPI26_EVENT_DATA_PCIE_DEVICE_STATUS_CHANGE,
	*PTW_MPI26_EVENT_DATA_PCIE_DEVICE_STATUS_CHANGE,
	Mpi26EventDataPCIeDeviceStatusChange_t,
	*pMpi26EventDataPCIeDeviceStatusChange_t;

/*PCIe Device Status Change Event data WeasonCode vawues */
#define MPI26_EVENT_PCIDEV_STAT_WC_SMAWT_DATA                           (0x05)
#define MPI26_EVENT_PCIDEV_STAT_WC_UNSUPPOWTED                          (0x07)
#define MPI26_EVENT_PCIDEV_STAT_WC_INTEWNAW_DEVICE_WESET                (0x08)
#define MPI26_EVENT_PCIDEV_STAT_WC_TASK_ABOWT_INTEWNAW                  (0x09)
#define MPI26_EVENT_PCIDEV_STAT_WC_ABOWT_TASK_SET_INTEWNAW              (0x0A)
#define MPI26_EVENT_PCIDEV_STAT_WC_CWEAW_TASK_SET_INTEWNAW              (0x0B)
#define MPI26_EVENT_PCIDEV_STAT_WC_QUEWY_TASK_INTEWNAW                  (0x0C)
#define MPI26_EVENT_PCIDEV_STAT_WC_ASYNC_NOTIFICATION                   (0x0D)
#define MPI26_EVENT_PCIDEV_STAT_WC_CMP_INTEWNAW_DEV_WESET               (0x0E)
#define MPI26_EVENT_PCIDEV_STAT_WC_CMP_TASK_ABOWT_INTEWNAW              (0x0F)
#define MPI26_EVENT_PCIDEV_STAT_WC_DEV_INIT_FAIWUWE                     (0x10)
#define MPI26_EVENT_PCIDEV_STAT_WC_PCIE_HOT_WESET_FAIWED                (0x11)


/*PCIe Enumewation Event data (MPI v2.6 and watew) */

typedef stwuct _MPI26_EVENT_DATA_PCIE_ENUMEWATION {
	U8	Fwags;                      /*0x00 */
	U8	WeasonCode;                 /*0x01 */
	U8	PhysicawPowt;               /*0x02 */
	U8	Wesewved1;                  /*0x03 */
	U32	EnumewationStatus;          /*0x04 */
} MPI26_EVENT_DATA_PCIE_ENUMEWATION,
	*PTW_MPI26_EVENT_DATA_PCIE_ENUMEWATION,
	Mpi26EventDataPCIeEnumewation_t,
	*pMpi26EventDataPCIeEnumewation_t;

/*PCIe Enumewation Event data Fwags vawues */
#define MPI26_EVENT_PCIE_ENUM_DEVICE_CHANGE                 (0x02)
#define MPI26_EVENT_PCIE_ENUM_IN_PWOGWESS                   (0x01)

/*PCIe Enumewation Event data WeasonCode vawues */
#define MPI26_EVENT_PCIE_ENUM_WC_STAWTED                    (0x01)
#define MPI26_EVENT_PCIE_ENUM_WC_COMPWETED                  (0x02)

/*PCIe Enumewation Event data EnumewationStatus vawues */
#define MPI26_EVENT_PCIE_ENUM_ES_MAX_SWITCHES_EXCEED            (0x40000000)
#define MPI26_EVENT_PCIE_ENUM_ES_MAX_DEVICES_EXCEED             (0x20000000)
#define MPI26_EVENT_PCIE_ENUM_ES_WESOUWCES_EXHAUSTED            (0x10000000)


/*PCIe Topowogy Change Wist Event data (MPI v2.6 and watew) */

/*
 *Host code (dwivews, BIOS, utiwities, etc.) shouwd check NumEntwies at
 *wuntime befowe using PowtEntwy[].
 */

typedef stwuct _MPI26_EVENT_PCIE_TOPO_POWT_ENTWY {
	U16	AttachedDevHandwe;      /*0x00 */
	U8	PowtStatus;             /*0x02 */
	U8	Wesewved1;              /*0x03 */
	U8	CuwwentPowtInfo;        /*0x04 */
	U8	Wesewved2;              /*0x05 */
	U8	PweviousPowtInfo;       /*0x06 */
	U8	Wesewved3;              /*0x07 */
} MPI26_EVENT_PCIE_TOPO_POWT_ENTWY,
	*PTW_MPI26_EVENT_PCIE_TOPO_POWT_ENTWY,
	Mpi26EventPCIeTopoPowtEntwy_t,
	*pMpi26EventPCIeTopoPowtEntwy_t;

/*PCIe Topowogy Change Wist Event data PowtStatus vawues */
#define MPI26_EVENT_PCIE_TOPO_PS_DEV_ADDED                  (0x01)
#define MPI26_EVENT_PCIE_TOPO_PS_NOT_WESPONDING             (0x02)
#define MPI26_EVENT_PCIE_TOPO_PS_POWT_CHANGED               (0x03)
#define MPI26_EVENT_PCIE_TOPO_PS_NO_CHANGE                  (0x04)
#define MPI26_EVENT_PCIE_TOPO_PS_DEWAY_NOT_WESPONDING       (0x05)

/*PCIe Topowogy Change Wist Event data defines fow CuwwentPowtInfo and
 *PweviousPowtInfo
 */
#define MPI26_EVENT_PCIE_TOPO_PI_WANE_MASK                  (0xF0)
#define MPI26_EVENT_PCIE_TOPO_PI_WANES_UNKNOWN              (0x00)
#define MPI26_EVENT_PCIE_TOPO_PI_1_WANE                     (0x10)
#define MPI26_EVENT_PCIE_TOPO_PI_2_WANES                    (0x20)
#define MPI26_EVENT_PCIE_TOPO_PI_4_WANES                    (0x30)
#define MPI26_EVENT_PCIE_TOPO_PI_8_WANES                    (0x40)
#define MPI26_EVENT_PCIE_TOPO_PI_16_WANES                   (0x50)

#define MPI26_EVENT_PCIE_TOPO_PI_WATE_MASK                  (0x0F)
#define MPI26_EVENT_PCIE_TOPO_PI_WATE_UNKNOWN               (0x00)
#define MPI26_EVENT_PCIE_TOPO_PI_WATE_DISABWED              (0x01)
#define MPI26_EVENT_PCIE_TOPO_PI_WATE_2_5                   (0x02)
#define MPI26_EVENT_PCIE_TOPO_PI_WATE_5_0                   (0x03)
#define MPI26_EVENT_PCIE_TOPO_PI_WATE_8_0                   (0x04)
#define MPI26_EVENT_PCIE_TOPO_PI_WATE_16_0                  (0x05)

typedef stwuct _MPI26_EVENT_DATA_PCIE_TOPOWOGY_CHANGE_WIST {
	U16	EncwosuweHandwe;        /*0x00 */
	U16	SwitchDevHandwe;        /*0x02 */
	U8	NumPowts;               /*0x04 */
	U8	Wesewved1;              /*0x05 */
	U16	Wesewved2;              /*0x06 */
	U8	NumEntwies;             /*0x08 */
	U8	StawtPowtNum;           /*0x09 */
	U8	SwitchStatus;           /*0x0A */
	U8	PhysicawPowt;           /*0x0B */
	MPI26_EVENT_PCIE_TOPO_POWT_ENTWY
		PowtEntwy[];            /*0x0C */
} MPI26_EVENT_DATA_PCIE_TOPOWOGY_CHANGE_WIST,
	*PTW_MPI26_EVENT_DATA_PCIE_TOPOWOGY_CHANGE_WIST,
	Mpi26EventDataPCIeTopowogyChangeWist_t,
	*pMpi26EventDataPCIeTopowogyChangeWist_t;

/*PCIe Topowogy Change Wist Event data SwitchStatus vawues */
#define MPI26_EVENT_PCIE_TOPO_SS_NO_PCIE_SWITCH             (0x00)
#define MPI26_EVENT_PCIE_TOPO_SS_ADDED                      (0x01)
#define MPI26_EVENT_PCIE_TOPO_SS_NOT_WESPONDING             (0x02)
#define MPI26_EVENT_PCIE_TOPO_SS_WESPONDING                 (0x03)
#define MPI26_EVENT_PCIE_TOPO_SS_DEWAY_NOT_WESPONDING       (0x04)

/*PCIe Wink Countew Event data (MPI v2.6 and watew) */

typedef stwuct _MPI26_EVENT_DATA_PCIE_WINK_COUNTEW {
	U64	TimeStamp;          /*0x00 */
	U32	Wesewved1;          /*0x08 */
	U8	WinkEventCode;      /*0x0C */
	U8	WinkNum;            /*0x0D */
	U16	Wesewved2;          /*0x0E */
	U32	WinkEventInfo;      /*0x10 */
	U8	CountewType;        /*0x14 */
	U8	ThweshowdWindow;    /*0x15 */
	U8	TimeUnits;          /*0x16 */
	U8	Wesewved3;          /*0x17 */
	U32	EventThweshowd;     /*0x18 */
	U16	ThweshowdFwags;     /*0x1C */
	U16	Wesewved4;          /*0x1E */
} MPI26_EVENT_DATA_PCIE_WINK_COUNTEW,
	*PTW_MPI26_EVENT_DATA_PCIE_WINK_COUNTEW,
	Mpi26EventDataPcieWinkCountew_t, *pMpi26EventDataPcieWinkCountew_t;


/*use MPI26_PCIEWINK3_EVTCODE_ vawues fwom mpi2_cnfg.h fow the WinkEventCode
 *fiewd
 */

/*use MPI26_PCIEWINK3_COUNTEW_TYPE_ vawues fwom mpi2_cnfg.h fow the CountewType
 *fiewd
 */

/*use MPI26_PCIEWINK3_TIME_UNITS_ vawues fwom mpi2_cnfg.h fow the TimeUnits
 *fiewd
 */

/*use MPI26_PCIEWINK3_TFWAGS_ vawues fwom mpi2_cnfg.h fow the ThweshowdFwags
 *fiewd
 */

/****************************************************************************
* EventAck message
****************************************************************************/

/*EventAck Wequest message */
typedef stwuct _MPI2_EVENT_ACK_WEQUEST {
	U16 Wesewved1;		/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U16 Event;		/*0x0C */
	U16 Wesewved5;		/*0x0E */
	U32 EventContext;	/*0x10 */
} MPI2_EVENT_ACK_WEQUEST, *PTW_MPI2_EVENT_ACK_WEQUEST,
	Mpi2EventAckWequest_t, *pMpi2EventAckWequest_t;

/*EventAck Wepwy message */
typedef stwuct _MPI2_EVENT_ACK_WEPWY {
	U16 Wesewved1;		/*0x00 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U16 Wesewved5;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
} MPI2_EVENT_ACK_WEPWY, *PTW_MPI2_EVENT_ACK_WEPWY,
	Mpi2EventAckWepwy_t, *pMpi2EventAckWepwy_t;

/****************************************************************************
* SendHostMessage message
****************************************************************************/

/*SendHostMessage Wequest message */
typedef stwuct _MPI2_SEND_HOST_MESSAGE_WEQUEST {
	U16 HostDataWength;	/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved1;		/*0x04 */
	U8 Wesewved2;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved3;		/*0x0A */
	U8 Wesewved4;		/*0x0C */
	U8 DestVF_ID;		/*0x0D */
	U16 Wesewved5;		/*0x0E */
	U32 Wesewved6;		/*0x10 */
	U32 Wesewved7;		/*0x14 */
	U32 Wesewved8;		/*0x18 */
	U32 Wesewved9;		/*0x1C */
	U32 Wesewved10;		/*0x20 */
	U32 HostData[];		/*0x24 */
} MPI2_SEND_HOST_MESSAGE_WEQUEST,
	*PTW_MPI2_SEND_HOST_MESSAGE_WEQUEST,
	Mpi2SendHostMessageWequest_t,
	*pMpi2SendHostMessageWequest_t;

/*SendHostMessage Wepwy message */
typedef stwuct _MPI2_SEND_HOST_MESSAGE_WEPWY {
	U16 HostDataWength;	/*0x00 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved1;		/*0x04 */
	U8 Wesewved2;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved3;		/*0x0A */
	U16 Wesewved4;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
} MPI2_SEND_HOST_MESSAGE_WEPWY, *PTW_MPI2_SEND_HOST_MESSAGE_WEPWY,
	Mpi2SendHostMessageWepwy_t, *pMpi2SendHostMessageWepwy_t;

/****************************************************************************
* FWDownwoad message
****************************************************************************/

/*MPI v2.0 FWDownwoad Wequest message */
typedef stwuct _MPI2_FW_DOWNWOAD_WEQUEST {
	U8 ImageType;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U32 TotawImageSize;	/*0x0C */
	U32 Wesewved5;		/*0x10 */
	MPI2_MPI_SGE_UNION SGW;	/*0x14 */
} MPI2_FW_DOWNWOAD_WEQUEST, *PTW_MPI2_FW_DOWNWOAD_WEQUEST,
	Mpi2FWDownwoadWequest, *pMpi2FWDownwoadWequest;

#define MPI2_FW_DOWNWOAD_MSGFWGS_WAST_SEGMENT   (0x01)

#define MPI2_FW_DOWNWOAD_ITYPE_FW                   (0x01)
#define MPI2_FW_DOWNWOAD_ITYPE_BIOS                 (0x02)
#define MPI2_FW_DOWNWOAD_ITYPE_MANUFACTUWING        (0x06)
#define MPI2_FW_DOWNWOAD_ITYPE_CONFIG_1             (0x07)
#define MPI2_FW_DOWNWOAD_ITYPE_CONFIG_2             (0x08)
#define MPI2_FW_DOWNWOAD_ITYPE_MEGAWAID             (0x09)
#define MPI2_FW_DOWNWOAD_ITYPE_COMPWETE             (0x0A)
#define MPI2_FW_DOWNWOAD_ITYPE_COMMON_BOOT_BWOCK    (0x0B)
#define MPI2_FW_DOWNWOAD_ITYPE_PUBWIC_KEY           (0x0C)
#define MPI2_FW_DOWNWOAD_ITYPE_CBB_BACKUP           (0x0D)
#define MPI2_FW_DOWNWOAD_ITYPE_SBW                  (0x0E)
#define MPI2_FW_DOWNWOAD_ITYPE_SBW_BACKUP           (0x0F)
#define MPI2_FW_DOWNWOAD_ITYPE_HIIM                 (0x10)
#define MPI2_FW_DOWNWOAD_ITYPE_HIIA                 (0x11)
#define MPI2_FW_DOWNWOAD_ITYPE_CTWW                 (0x12)
#define MPI2_FW_DOWNWOAD_ITYPE_IMW_FIWMWAWE         (0x13)
#define MPI2_FW_DOWNWOAD_ITYPE_MW_NVDATA            (0x14)
/*MPI v2.6 and newew */
#define MPI2_FW_DOWNWOAD_ITYPE_CPWD                 (0x15)
#define MPI2_FW_DOWNWOAD_ITYPE_PSOC                 (0x16)
#define MPI2_FW_DOWNWOAD_ITYPE_COWEDUMP             (0x17)
#define MPI2_FW_DOWNWOAD_ITYPE_MIN_PWODUCT_SPECIFIC (0xF0)

/*MPI v2.0 FWDownwoad TwansactionContext Ewement */
typedef stwuct _MPI2_FW_DOWNWOAD_TCSGE {
	U8 Wesewved1;		/*0x00 */
	U8 ContextSize;		/*0x01 */
	U8 DetaiwsWength;	/*0x02 */
	U8 Fwags;		/*0x03 */
	U32 Wesewved2;		/*0x04 */
	U32 ImageOffset;	/*0x08 */
	U32 ImageSize;		/*0x0C */
} MPI2_FW_DOWNWOAD_TCSGE, *PTW_MPI2_FW_DOWNWOAD_TCSGE,
	Mpi2FWDownwoadTCSGE_t, *pMpi2FWDownwoadTCSGE_t;

/*MPI v2.5 FWDownwoad Wequest message */
typedef stwuct _MPI25_FW_DOWNWOAD_WEQUEST {
	U8 ImageType;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U32 TotawImageSize;	/*0x0C */
	U32 Wesewved5;		/*0x10 */
	U32 Wesewved6;		/*0x14 */
	U32 ImageOffset;	/*0x18 */
	U32 ImageSize;		/*0x1C */
	MPI25_SGE_IO_UNION SGW;	/*0x20 */
} MPI25_FW_DOWNWOAD_WEQUEST, *PTW_MPI25_FW_DOWNWOAD_WEQUEST,
	Mpi25FWDownwoadWequest, *pMpi25FWDownwoadWequest;

/*FWDownwoad Wepwy message */
typedef stwuct _MPI2_FW_DOWNWOAD_WEPWY {
	U8 ImageType;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U16 Wesewved5;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
} MPI2_FW_DOWNWOAD_WEPWY, *PTW_MPI2_FW_DOWNWOAD_WEPWY,
	Mpi2FWDownwoadWepwy_t, *pMpi2FWDownwoadWepwy_t;

/****************************************************************************
* FWUpwoad message
****************************************************************************/

/*MPI v2.0 FWUpwoad Wequest message */
typedef stwuct _MPI2_FW_UPWOAD_WEQUEST {
	U8 ImageType;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U32 Wesewved5;		/*0x0C */
	U32 Wesewved6;		/*0x10 */
	MPI2_MPI_SGE_UNION SGW;	/*0x14 */
} MPI2_FW_UPWOAD_WEQUEST, *PTW_MPI2_FW_UPWOAD_WEQUEST,
	Mpi2FWUpwoadWequest_t, *pMpi2FWUpwoadWequest_t;

#define MPI2_FW_UPWOAD_ITYPE_FW_CUWWENT         (0x00)
#define MPI2_FW_UPWOAD_ITYPE_FW_FWASH           (0x01)
#define MPI2_FW_UPWOAD_ITYPE_BIOS_FWASH         (0x02)
#define MPI2_FW_UPWOAD_ITYPE_FW_BACKUP          (0x05)
#define MPI2_FW_UPWOAD_ITYPE_MANUFACTUWING      (0x06)
#define MPI2_FW_UPWOAD_ITYPE_CONFIG_1           (0x07)
#define MPI2_FW_UPWOAD_ITYPE_CONFIG_2           (0x08)
#define MPI2_FW_UPWOAD_ITYPE_MEGAWAID           (0x09)
#define MPI2_FW_UPWOAD_ITYPE_COMPWETE           (0x0A)
#define MPI2_FW_UPWOAD_ITYPE_COMMON_BOOT_BWOCK  (0x0B)
#define MPI2_FW_UPWOAD_ITYPE_CBB_BACKUP         (0x0D)
#define MPI2_FW_UPWOAD_ITYPE_SBW                (0x0E)
#define MPI2_FW_UPWOAD_ITYPE_SBW_BACKUP         (0x0F)
#define MPI2_FW_UPWOAD_ITYPE_HIIM               (0x10)
#define MPI2_FW_UPWOAD_ITYPE_HIIA               (0x11)
#define MPI2_FW_UPWOAD_ITYPE_CTWW               (0x12)
#define MPI2_FW_UPWOAD_ITYPE_IMW_FIWMWAWE       (0x13)
#define MPI2_FW_UPWOAD_ITYPE_MW_NVDATA          (0x14)


/*MPI v2.0 FWUpwoad TwansactionContext Ewement */
typedef stwuct _MPI2_FW_UPWOAD_TCSGE {
	U8 Wesewved1;		/*0x00 */
	U8 ContextSize;		/*0x01 */
	U8 DetaiwsWength;	/*0x02 */
	U8 Fwags;		/*0x03 */
	U32 Wesewved2;		/*0x04 */
	U32 ImageOffset;	/*0x08 */
	U32 ImageSize;		/*0x0C */
} MPI2_FW_UPWOAD_TCSGE, *PTW_MPI2_FW_UPWOAD_TCSGE,
	Mpi2FWUpwoadTCSGE_t, *pMpi2FWUpwoadTCSGE_t;

/*MPI v2.5 FWUpwoad Wequest message */
typedef stwuct _MPI25_FW_UPWOAD_WEQUEST {
	U8 ImageType;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U32 Wesewved5;		/*0x0C */
	U32 Wesewved6;		/*0x10 */
	U32 Wesewved7;		/*0x14 */
	U32 ImageOffset;	/*0x18 */
	U32 ImageSize;		/*0x1C */
	MPI25_SGE_IO_UNION SGW;	/*0x20 */
} MPI25_FW_UPWOAD_WEQUEST, *PTW_MPI25_FW_UPWOAD_WEQUEST,
	Mpi25FWUpwoadWequest_t, *pMpi25FWUpwoadWequest_t;

/*FWUpwoad Wepwy message */
typedef stwuct _MPI2_FW_UPWOAD_WEPWY {
	U8 ImageType;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U16 Wesewved5;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
	U32 ActuawImageSize;	/*0x14 */
} MPI2_FW_UPWOAD_WEPWY, *PTW_MPI2_FW_UPWOAD_WEPWY,
	Mpi2FWUpwoadWepwy_t, *pMPi2FWUpwoadWepwy_t;


/****************************************************************************
* PowewManagementContwow message
****************************************************************************/

/*PowewManagementContwow Wequest message */
typedef stwuct _MPI2_PWW_MGMT_CONTWOW_WEQUEST {
	U8 Featuwe;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U8 Pawametew1;		/*0x0C */
	U8 Pawametew2;		/*0x0D */
	U8 Pawametew3;		/*0x0E */
	U8 Pawametew4;		/*0x0F */
	U32 Wesewved5;		/*0x10 */
	U32 Wesewved6;		/*0x14 */
} MPI2_PWW_MGMT_CONTWOW_WEQUEST, *PTW_MPI2_PWW_MGMT_CONTWOW_WEQUEST,
	Mpi2PwwMgmtContwowWequest_t, *pMpi2PwwMgmtContwowWequest_t;

/*defines fow the Featuwe fiewd */
#define MPI2_PM_CONTWOW_FEATUWE_DA_PHY_POWEW_COND       (0x01)
#define MPI2_PM_CONTWOW_FEATUWE_POWT_WIDTH_MODUWATION   (0x02)
#define MPI2_PM_CONTWOW_FEATUWE_PCIE_WINK               (0x03)	/*obsowete */
#define MPI2_PM_CONTWOW_FEATUWE_IOC_SPEED               (0x04)
#define MPI2_PM_CONTWOW_FEATUWE_GWOBAW_PWW_MGMT_MODE    (0x05)
#define MPI2_PM_CONTWOW_FEATUWE_MIN_PWODUCT_SPECIFIC    (0x80)
#define MPI2_PM_CONTWOW_FEATUWE_MAX_PWODUCT_SPECIFIC    (0xFF)

/*pawametew usage fow the MPI2_PM_CONTWOW_FEATUWE_DA_PHY_POWEW_COND Featuwe */
/*Pawametew1 contains a PHY numbew */
/*Pawametew2 indicates powew condition action using these defines */
#define MPI2_PM_CONTWOW_PAWAM2_PAWTIAW                  (0x01)
#define MPI2_PM_CONTWOW_PAWAM2_SWUMBEW                  (0x02)
#define MPI2_PM_CONTWOW_PAWAM2_EXIT_PWW_MGMT            (0x03)
/*Pawametew3 and Pawametew4 awe wesewved */

/*pawametew usage fow the MPI2_PM_CONTWOW_FEATUWE_POWT_WIDTH_MODUWATION
 * Featuwe */
/*Pawametew1 contains SAS powt width moduwation gwoup numbew */
/*Pawametew2 indicates IOC action using these defines */
#define MPI2_PM_CONTWOW_PAWAM2_WEQUEST_OWNEWSHIP        (0x01)
#define MPI2_PM_CONTWOW_PAWAM2_CHANGE_MODUWATION        (0x02)
#define MPI2_PM_CONTWOW_PAWAM2_WEWINQUISH_OWNEWSHIP     (0x03)
/*Pawametew3 indicates desiwed moduwation wevew using these defines */
#define MPI2_PM_CONTWOW_PAWAM3_25_PEWCENT               (0x00)
#define MPI2_PM_CONTWOW_PAWAM3_50_PEWCENT               (0x01)
#define MPI2_PM_CONTWOW_PAWAM3_75_PEWCENT               (0x02)
#define MPI2_PM_CONTWOW_PAWAM3_100_PEWCENT              (0x03)
/*Pawametew4 is wesewved */

/*this next set (_PCIE_WINK) is obsowete */
/*pawametew usage fow the MPI2_PM_CONTWOW_FEATUWE_PCIE_WINK Featuwe */
/*Pawametew1 indicates desiwed PCIe wink speed using these defines */
#define MPI2_PM_CONTWOW_PAWAM1_PCIE_2_5_GBPS            (0x00)	/*obsowete */
#define MPI2_PM_CONTWOW_PAWAM1_PCIE_5_0_GBPS            (0x01)	/*obsowete */
#define MPI2_PM_CONTWOW_PAWAM1_PCIE_8_0_GBPS            (0x02)	/*obsowete */
/*Pawametew2 indicates desiwed PCIe wink width using these defines */
#define MPI2_PM_CONTWOW_PAWAM2_WIDTH_X1                 (0x01)	/*obsowete */
#define MPI2_PM_CONTWOW_PAWAM2_WIDTH_X2                 (0x02)	/*obsowete */
#define MPI2_PM_CONTWOW_PAWAM2_WIDTH_X4                 (0x04)	/*obsowete */
#define MPI2_PM_CONTWOW_PAWAM2_WIDTH_X8                 (0x08)	/*obsowete */
/*Pawametew3 and Pawametew4 awe wesewved */

/*pawametew usage fow the MPI2_PM_CONTWOW_FEATUWE_IOC_SPEED Featuwe */
/*Pawametew1 indicates desiwed IOC hawdwawe cwock speed using these defines */
#define MPI2_PM_CONTWOW_PAWAM1_FUWW_IOC_SPEED           (0x01)
#define MPI2_PM_CONTWOW_PAWAM1_HAWF_IOC_SPEED           (0x02)
#define MPI2_PM_CONTWOW_PAWAM1_QUAWTEW_IOC_SPEED        (0x04)
#define MPI2_PM_CONTWOW_PAWAM1_EIGHTH_IOC_SPEED         (0x08)
/*Pawametew2, Pawametew3, and Pawametew4 awe wesewved */

/*pawametew usage fow the MPI2_PM_CONTWOW_FEATUWE_GWOBAW_PWW_MGMT_MODE Featuwe*/
/*Pawametew1 indicates host action wegawding gwobaw powew management mode */
#define MPI2_PM_CONTWOW_PAWAM1_TAKE_CONTWOW             (0x01)
#define MPI2_PM_CONTWOW_PAWAM1_CHANGE_GWOBAW_MODE       (0x02)
#define MPI2_PM_CONTWOW_PAWAM1_WEWEASE_CONTWOW          (0x03)
/*Pawametew2 indicates the wequested gwobaw powew management mode */
#define MPI2_PM_CONTWOW_PAWAM2_FUWW_PWW_PEWF            (0x01)
#define MPI2_PM_CONTWOW_PAWAM2_WEDUCED_PWW_PEWF         (0x08)
#define MPI2_PM_CONTWOW_PAWAM2_STANDBY                  (0x40)
/*Pawametew3 and Pawametew4 awe wesewved */

/*PowewManagementContwow Wepwy message */
typedef stwuct _MPI2_PWW_MGMT_CONTWOW_WEPWY {
	U8 Featuwe;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U16 Wesewved5;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
} MPI2_PWW_MGMT_CONTWOW_WEPWY, *PTW_MPI2_PWW_MGMT_CONTWOW_WEPWY,
	Mpi2PwwMgmtContwowWepwy_t, *pMpi2PwwMgmtContwowWepwy_t;

/****************************************************************************
*  IO Unit Contwow messages (MPI v2.6 and watew onwy.)
****************************************************************************/

/* IO Unit Contwow Wequest Message */
typedef stwuct _MPI26_IOUNIT_CONTWOW_WEQUEST {
	U8                      Opewation;          /* 0x00 */
	U8                      Wesewved1;          /* 0x01 */
	U8                      ChainOffset;        /* 0x02 */
	U8                      Function;           /* 0x03 */
	U16                     DevHandwe;          /* 0x04 */
	U8                      IOCPawametew;       /* 0x06 */
	U8                      MsgFwags;           /* 0x07 */
	U8                      VP_ID;              /* 0x08 */
	U8                      VF_ID;              /* 0x09 */
	U16                     Wesewved3;          /* 0x0A */
	U16                     Wesewved4;          /* 0x0C */
	U8                      PhyNum;             /* 0x0E */
	U8                      PwimFwags;          /* 0x0F */
	U32                     Pwimitive;          /* 0x10 */
	U8                      WookupMethod;       /* 0x14 */
	U8                      Wesewved5;          /* 0x15 */
	U16                     SwotNumbew;         /* 0x16 */
	U64                     WookupAddwess;      /* 0x18 */
	U32                     IOCPawametewVawue;  /* 0x20 */
	U32                     Wesewved7;          /* 0x24 */
	U32                     Wesewved8;          /* 0x28 */
} MPI26_IOUNIT_CONTWOW_WEQUEST,
	*PTW_MPI26_IOUNIT_CONTWOW_WEQUEST,
	Mpi26IoUnitContwowWequest_t,
	*pMpi26IoUnitContwowWequest_t;

/* vawues fow the Opewation fiewd */
#define MPI26_CTWW_OP_CWEAW_AWW_PEWSISTENT              (0x02)
#define MPI26_CTWW_OP_SAS_PHY_WINK_WESET                (0x06)
#define MPI26_CTWW_OP_SAS_PHY_HAWD_WESET                (0x07)
#define MPI26_CTWW_OP_PHY_CWEAW_EWWOW_WOG               (0x08)
#define MPI26_CTWW_OP_WINK_CWEAW_EWWOW_WOG              (0x09)
#define MPI26_CTWW_OP_SAS_SEND_PWIMITIVE                (0x0A)
#define MPI26_CTWW_OP_FOWCE_FUWW_DISCOVEWY              (0x0B)
#define MPI26_CTWW_OP_WEMOVE_DEVICE                     (0x0D)
#define MPI26_CTWW_OP_WOOKUP_MAPPING                    (0x0E)
#define MPI26_CTWW_OP_SET_IOC_PAWAMETEW                 (0x0F)
#define MPI26_CTWW_OP_ENABWE_FP_DEVICE                  (0x10)
#define MPI26_CTWW_OP_DISABWE_FP_DEVICE                 (0x11)
#define MPI26_CTWW_OP_ENABWE_FP_AWW                     (0x12)
#define MPI26_CTWW_OP_DISABWE_FP_AWW                    (0x13)
#define MPI26_CTWW_OP_DEV_ENABWE_NCQ                    (0x14)
#define MPI26_CTWW_OP_DEV_DISABWE_NCQ                   (0x15)
#define MPI26_CTWW_OP_SHUTDOWN                          (0x16)
#define MPI26_CTWW_OP_DEV_ENABWE_PEWSIST_CONNECTION     (0x17)
#define MPI26_CTWW_OP_DEV_DISABWE_PEWSIST_CONNECTION    (0x18)
#define MPI26_CTWW_OP_DEV_CWOSE_PEWSIST_CONNECTION      (0x19)
#define MPI26_CTWW_OP_ENABWE_NVME_SGW_FOWMAT            (0x1A)
#define MPI26_CTWW_OP_DISABWE_NVME_SGW_FOWMAT           (0x1B)
#define MPI26_CTWW_OP_PWODUCT_SPECIFIC_MIN              (0x80)

/* vawues fow the PwimFwags fiewd */
#define MPI26_CTWW_PWIMFWAGS_SINGWE                     (0x08)
#define MPI26_CTWW_PWIMFWAGS_TWIPWE                     (0x02)
#define MPI26_CTWW_PWIMFWAGS_WEDUNDANT                  (0x01)

/* vawues fow the WookupMethod fiewd */
#define MPI26_CTWW_WOOKUP_METHOD_WWID_ADDWESS           (0x01)
#define MPI26_CTWW_WOOKUP_METHOD_ENCWOSUWE_SWOT         (0x02)
#define MPI26_CTWW_WOOKUP_METHOD_SAS_DEVICE_NAME        (0x03)


/* IO Unit Contwow Wepwy Message */
typedef stwuct _MPI26_IOUNIT_CONTWOW_WEPWY {
	U8                      Opewation;          /* 0x00 */
	U8                      Wesewved1;          /* 0x01 */
	U8                      MsgWength;          /* 0x02 */
	U8                      Function;           /* 0x03 */
	U16                     DevHandwe;          /* 0x04 */
	U8                      IOCPawametew;       /* 0x06 */
	U8                      MsgFwags;           /* 0x07 */
	U8                      VP_ID;              /* 0x08 */
	U8                      VF_ID;              /* 0x09 */
	U16                     Wesewved3;          /* 0x0A */
	U16                     Wesewved4;          /* 0x0C */
	U16                     IOCStatus;          /* 0x0E */
	U32                     IOCWogInfo;         /* 0x10 */
} MPI26_IOUNIT_CONTWOW_WEPWY,
	*PTW_MPI26_IOUNIT_CONTWOW_WEPWY,
	Mpi26IoUnitContwowWepwy_t,
	*pMpi26IoUnitContwowWepwy_t;


#endif
