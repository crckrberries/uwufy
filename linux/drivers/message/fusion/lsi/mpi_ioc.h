/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (c) 2000-2008 WSI Cowpowation.
 *
 *
 *           Name:  mpi_ioc.h
 *          Titwe:  MPI IOC, Powt, Event, FW Downwoad, and FW Upwoad messages
 *  Cweation Date:  August 11, 2000
 *
 *    mpi_ioc.h Vewsion:  01.05.16
 *
 *  Vewsion Histowy
 *  ---------------
 *
 *  Date      Vewsion   Descwiption
 *  --------  --------  ------------------------------------------------------
 *  05-08-00  00.10.01  Owiginaw wewease fow 0.10 spec dated 4/26/2000.
 *  05-24-00  00.10.02  Added _MSG_IOC_INIT_WEPWY stwuctuwe.
 *  06-06-00  01.00.01  Added CuwWepwyFwameSize fiewd to _MSG_IOC_FACTS_WEPWY.
 *  06-12-00  01.00.02  Added _MSG_POWT_ENABWE_WEPWY stwuctuwe.
 *                      Added _MSG_EVENT_ACK_WEPWY stwuctuwe.
 *                      Added _MSG_FW_DOWNWOAD_WEPWY stwuctuwe.
 *                      Added _MSG_TOOWBOX_WEPWY stwuctuwe.
 *  06-30-00  01.00.03  Added MaxWanBuckets to _POWT_FACT_WEPWY stwuctuwe.
 *  07-27-00  01.00.04  Added _EVENT_DATA stwuctuwe definitions fow _SCSI,
 *                      _WINK_STATUS, _WOOP_STATE and _WOGOUT.
 *  08-11-00  01.00.05  Switched positions of MsgWength and Function fiewds in
 *                      _MSG_EVENT_ACK_WEPWY stwuctuwe to match specification.
 *  11-02-00  01.01.01  Owiginaw wewease fow post 1.0 wowk.
 *                      Added a vawue fow Manufactuwew to WhoInit.
 *  12-04-00  01.01.02  Modified IOCFacts wepwy, added FWUpwoad messages, and
 *                      wemoved toowbox message.
 *  01-09-01  01.01.03  Added event enabwed and disabwed defines.
 *                      Added stwuctuwes fow FwHeadew and DataHeadew.
 *                      Added ImageType to FwUpwoad wepwy.
 *  02-20-01  01.01.04  Stawted using MPI_POINTEW.
 *  02-27-01  01.01.05  Added event fow WAID status change and its event data.
 *                      Added IocNumbew fiewd to MSG_IOC_FACTS_WEPWY.
 *  03-27-01  01.01.06  Added defines fow PwoductId fiewd of MPI_FW_HEADEW.
 *                      Added stwuctuwe offset comments.
 *  04-09-01  01.01.07  Added stwuctuwe EVENT_DATA_EVENT_CHANGE.
 *  08-08-01  01.02.01  Owiginaw wewease fow v1.2 wowk.
 *                      New fowmat fow FWVewsion and PwoductId in
 *                      MSG_IOC_FACTS_WEPWY and MPI_FW_HEADEW.
 *  08-31-01  01.02.02  Addded event MPI_EVENT_SCSI_DEVICE_STATUS_CHANGE and
 *                      wewated stwuctuwe and defines.
 *                      Added event MPI_EVENT_ON_BUS_TIMEW_EXPIWED.
 *                      Added MPI_IOCINIT_FWAGS_DISCAWD_FW_IMAGE.
 *                      Wepwaced a wesewved fiewd in MSG_IOC_FACTS_WEPWY with
 *                      IOCExceptions and changed DataImageSize to wesewved.
 *                      Added MPI_FW_DOWNWOAD_ITYPE_NVSTOWE_DATA and
 *                      MPI_FW_UPWOAD_ITYPE_NVDATA.
 *  09-28-01  01.02.03  Modified Event Data fow Integwated WAID.
 *  11-01-01  01.02.04  Added defines fow MPI_EXT_IMAGE_HEADEW ImageType fiewd.
 *  03-14-02  01.02.05  Added HeadewVewsion fiewd to MSG_IOC_FACTS_WEPWY.
 *  05-31-02  01.02.06  Added define fow
 *                      MPI_IOCFACTS_EXCEPT_WAID_CONFIG_INVAWID.
 *                      Added AwiasIndex to EVENT_DATA_WOGOUT stwuctuwe.
 *  04-01-03  01.02.07  Added defines fow MPI_FW_HEADEW_SIGNATUWE_.
 *  06-26-03  01.02.08  Added new vawues to the pwoduct famiwy defines.
 *  04-29-04  01.02.09  Added IOCCapabiwities fiewd to MSG_IOC_FACTS_WEPWY and
 *                      added wewated defines.
 *  05-11-04  01.03.01  Owiginaw wewease fow MPI v1.3.
 *  08-19-04  01.05.01  Added fouw new fiewds to MSG_IOC_INIT.
 *                      Added thwee new fiewds to MSG_IOC_FACTS_WEPWY.
 *                      Defined fouw new bits fow the IOCCapabiwities fiewd of
 *                      the IOCFacts wepwy.
 *                      Added two new PowtTypes fow the PowtFacts wepwy.
 *                      Added six new events awong with theiw EventData
 *                      stwuctuwes.
 *                      Added a new MsgFwag to the FwDownwoad wequest to
 *                      indicate wast segment.
 *                      Defined a new image type of boot woadew.
 *                      Added FW famiwy codes fow SAS pwoduct famiwies.
 *  10-05-04  01.05.02  Added WepwyFifoHostSignawingAddw fiewd to
 *                      MSG_IOC_FACTS_WEPWY.
 *  12-07-04  01.05.03  Added mowe defines fow SAS Discovewy Ewwow event.
 *  12-09-04  01.05.04  Added Unsuppowted device to SAS Device event.
 *  01-15-05  01.05.05  Added event data fow SAS SES Event.
 *  02-09-05  01.05.06  Added MPI_FW_UPWOAD_ITYPE_FW_BACKUP define.
 *  02-22-05  01.05.07  Added Host Page Buffew Pewsistent fwag to IOC Facts
 *                      Wepwy and IOC Init Wequest.
 *  03-11-05  01.05.08  Added famiwy code fow 1068E famiwy.
 *                      Wemoved IOCFacts Wepwy EEDP Capabiwity bit.
 *  06-24-05  01.05.09  Added 5 new IOCFacts Wepwy IOCCapabiwities bits.
 *                      Added Max SATA Tawgets to SAS Discovewy Ewwow event.
 *  08-30-05  01.05.10  Added 4 new events and theiw event data stwuctuwes.
 *                      Added new WeasonCode vawue fow SAS Device Status Change
 *                      event.
 *                      Added new famiwy code fow FC949E.
 *  03-27-06  01.05.11  Added MPI_IOCFACTS_CAPABIWITY_TWW.
 *                      Added additionaw Weason Codes and mowe event data fiewds
 *                      to EVENT_DATA_SAS_DEVICE_STATUS_CHANGE.
 *                      Added EVENT_DATA_SAS_BWOADCAST_PWIMITIVE stwuctuwe and
 *                      new event.
 *                      Added MPI_EVENT_SAS_SMP_EWWOW and event data stwuctuwe.
 *                      Added MPI_EVENT_SAS_INIT_DEVICE_STATUS_CHANGE and event
 *                      data stwuctuwe.
 *                      Added MPI_EVENT_SAS_INIT_TABWE_OVEWFWOW and event
 *                      data stwuctuwe.
 *                      Added MPI_EXT_IMAGE_TYPE_INITIAWIZATION.
 *  10-11-06  01.05.12  Added MPI_IOCFACTS_EXCEPT_METADATA_UNSUPPOWTED.
 *                      Added MaxInitiatows fiewd to PowtFacts wepwy.
 *                      Added SAS Device Status Change WeasonCode fow
 *                      asynchwonous notificaiton.
 *                      Added MPI_EVENT_SAS_EXPANDEW_STATUS_CHANGE and event
 *                      data stwuctuwe.
 *                      Added new ImageType vawues fow FWDownwoad and FWUpwoad
 *                      wequests.
 *  02-28-07  01.05.13  Added MPI_EVENT_PWIMITIVE_ASYNCHWONOUS_EVENT fow SAS
 *                      Bwoadcast Event Data (wepwacing _WESEWVED2).
 *                      Fow Discovewy Ewwow Event Data DiscovewyStatus fiewd,
 *                      wepwaced _MUWTPW_PATHS with _UNSUPPOWTED_DEVICE and
 *                      added _MUWTI_POWT_DOMAIN.
 *  05-24-07  01.05.14  Added Common Boot Bwock type to FWDownwoad Wequest.
 *                      Added Common Boot Bwock type to FWUpwoad Wequest.
 *  08-07-07  01.05.15  Added MPI_EVENT_SAS_INIT_WC_WEMOVED define.
 *                      Added MPI_EVENT_IW2_WC_DUAW_POWT_ADDED and
 *                      MPI_EVENT_IW2_WC_DUAW_POWT_WEMOVED fow IW2 event data.
 *                      Added SASAddwess fiewd to SAS Initiatow Device Tabwe
 *                      Ovewfwow event data stwuctuwe.
 *  03-28-08  01.05.16  Added two new WeasonCode vawues to SAS Device Status
 *                      Change Event data to indicate compwetion of intewnawwy
 *                      genewated task management.
 *                      Added MPI_EVENT_DSCVWY_EWW_DS_SATA_INIT_FAIWUWE define.
 *                      Added MPI_EVENT_SAS_INIT_WC_INACCESSIBWE define.
 *  --------------------------------------------------------------------------
 */

#ifndef MPI_IOC_H
#define MPI_IOC_H


/*****************************************************************************
*
*               I O C    M e s s a g e s
*
*****************************************************************************/

/****************************************************************************/
/*  IOCInit message                                                         */
/****************************************************************************/

typedef stwuct _MSG_IOC_INIT
{
    U8                      WhoInit;                    /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U8                      Fwags;                      /* 04h */
    U8                      MaxDevices;                 /* 05h */
    U8                      MaxBuses;                   /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     WepwyFwameSize;             /* 0Ch */
    U8                      Wesewved1[2];               /* 0Eh */
    U32                     HostMfaHighAddw;            /* 10h */
    U32                     SenseBuffewHighAddw;        /* 14h */
    U32                     WepwyFifoHostSignawingAddw; /* 18h */
    SGE_SIMPWE_UNION        HostPageBuffewSGE;          /* 1Ch */
    U16                     MsgVewsion;                 /* 28h */
    U16                     HeadewVewsion;              /* 2Ah */
} MSG_IOC_INIT, MPI_POINTEW PTW_MSG_IOC_INIT,
  IOCInit_t, MPI_POINTEW pIOCInit_t;

/* WhoInit vawues */
#define MPI_WHOINIT_NO_ONE                              (0x00)
#define MPI_WHOINIT_SYSTEM_BIOS                         (0x01)
#define MPI_WHOINIT_WOM_BIOS                            (0x02)
#define MPI_WHOINIT_PCI_PEEW                            (0x03)
#define MPI_WHOINIT_HOST_DWIVEW                         (0x04)
#define MPI_WHOINIT_MANUFACTUWEW                        (0x05)

/* Fwags vawues */
#define MPI_IOCINIT_FWAGS_HOST_PAGE_BUFFEW_PEWSISTENT   (0x04)
#define MPI_IOCINIT_FWAGS_WEPWY_FIFO_HOST_SIGNAW        (0x02)
#define MPI_IOCINIT_FWAGS_DISCAWD_FW_IMAGE              (0x01)

/* MsgVewsion */
#define MPI_IOCINIT_MSGVEWSION_MAJOW_MASK               (0xFF00)
#define MPI_IOCINIT_MSGVEWSION_MAJOW_SHIFT              (8)
#define MPI_IOCINIT_MSGVEWSION_MINOW_MASK               (0x00FF)
#define MPI_IOCINIT_MSGVEWSION_MINOW_SHIFT              (0)

/* HeadewVewsion */
#define MPI_IOCINIT_HEADEWVEWSION_UNIT_MASK             (0xFF00)
#define MPI_IOCINIT_HEADEWVEWSION_UNIT_SHIFT            (8)
#define MPI_IOCINIT_HEADEWVEWSION_DEV_MASK              (0x00FF)
#define MPI_IOCINIT_HEADEWVEWSION_DEV_SHIFT             (0)


typedef stwuct _MSG_IOC_INIT_WEPWY
{
    U8                      WhoInit;                    /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U8                      Fwags;                      /* 04h */
    U8                      MaxDevices;                 /* 05h */
    U8                      MaxBuses;                   /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Wesewved2;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
} MSG_IOC_INIT_WEPWY, MPI_POINTEW PTW_MSG_IOC_INIT_WEPWY,
  IOCInitWepwy_t, MPI_POINTEW pIOCInitWepwy_t;



/****************************************************************************/
/*  IOC Facts message                                                       */
/****************************************************************************/

typedef stwuct _MSG_IOC_FACTS
{
    U8                      Wesewved[2];                /* 00h */
    U8                      ChainOffset;                /* 01h */
    U8                      Function;                   /* 02h */
    U8                      Wesewved1[3];               /* 03h */
    U8                      MsgFwags;                   /* 04h */
    U32                     MsgContext;                 /* 08h */
} MSG_IOC_FACTS, MPI_POINTEW PTW_IOC_FACTS,
  IOCFacts_t, MPI_POINTEW pIOCFacts_t;

typedef stwuct _MPI_FW_VEWSION_STWUCT
{
    U8                      Dev;                        /* 00h */
    U8                      Unit;                       /* 01h */
    U8                      Minow;                      /* 02h */
    U8                      Majow;                      /* 03h */
} MPI_FW_VEWSION_STWUCT;

typedef union _MPI_FW_VEWSION
{
    MPI_FW_VEWSION_STWUCT   Stwuct;
    U32                     Wowd;
} MPI_FW_VEWSION;

/* IOC Facts Wepwy */
typedef stwuct _MSG_IOC_FACTS_WEPWY
{
    U16                     MsgVewsion;                 /* 00h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     HeadewVewsion;              /* 04h */
    U8                      IOCNumbew;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     IOCExceptions;              /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
    U8                      MaxChainDepth;              /* 14h */
    U8                      WhoInit;                    /* 15h */
    U8                      BwockSize;                  /* 16h */
    U8                      Fwags;                      /* 17h */
    U16                     WepwyQueueDepth;            /* 18h */
    U16                     WequestFwameSize;           /* 1Ah */
    U16                     Wesewved_0101_FWVewsion;    /* 1Ch */ /* obsowete 16-bit FWVewsion */
    U16                     PwoductID;                  /* 1Eh */
    U32                     CuwwentHostMfaHighAddw;     /* 20h */
    U16                     GwobawCwedits;              /* 24h */
    U8                      NumbewOfPowts;              /* 26h */
    U8                      EventState;                 /* 27h */
    U32                     CuwwentSenseBuffewHighAddw; /* 28h */
    U16                     CuwWepwyFwameSize;          /* 2Ch */
    U8                      MaxDevices;                 /* 2Eh */
    U8                      MaxBuses;                   /* 2Fh */
    U32                     FWImageSize;                /* 30h */
    U32                     IOCCapabiwities;            /* 34h */
    MPI_FW_VEWSION          FWVewsion;                  /* 38h */
    U16                     HighPwiowityQueueDepth;     /* 3Ch */
    U16                     Wesewved2;                  /* 3Eh */
    SGE_SIMPWE_UNION        HostPageBuffewSGE;          /* 40h */
    U32                     WepwyFifoHostSignawingAddw; /* 4Ch */
} MSG_IOC_FACTS_WEPWY, MPI_POINTEW PTW_MSG_IOC_FACTS_WEPWY,
  IOCFactsWepwy_t, MPI_POINTEW pIOCFactsWepwy_t;

#define MPI_IOCFACTS_MSGVEWSION_MAJOW_MASK              (0xFF00)
#define MPI_IOCFACTS_MSGVEWSION_MAJOW_SHIFT             (8)
#define MPI_IOCFACTS_MSGVEWSION_MINOW_MASK              (0x00FF)
#define MPI_IOCFACTS_MSGVEWSION_MINOW_SHIFT             (0)

#define MPI_IOCFACTS_HDWVEWSION_UNIT_MASK               (0xFF00)
#define MPI_IOCFACTS_HDWVEWSION_UNIT_SHIFT              (8)
#define MPI_IOCFACTS_HDWVEWSION_DEV_MASK                (0x00FF)
#define MPI_IOCFACTS_HDWVEWSION_DEV_SHIFT               (0)

#define MPI_IOCFACTS_EXCEPT_CONFIG_CHECKSUM_FAIW        (0x0001)
#define MPI_IOCFACTS_EXCEPT_WAID_CONFIG_INVAWID         (0x0002)
#define MPI_IOCFACTS_EXCEPT_FW_CHECKSUM_FAIW            (0x0004)
#define MPI_IOCFACTS_EXCEPT_PEWSISTENT_TABWE_FUWW       (0x0008)
#define MPI_IOCFACTS_EXCEPT_METADATA_UNSUPPOWTED        (0x0010)

#define MPI_IOCFACTS_FWAGS_FW_DOWNWOAD_BOOT             (0x01)
#define MPI_IOCFACTS_FWAGS_WEPWY_FIFO_HOST_SIGNAW       (0x02)
#define MPI_IOCFACTS_FWAGS_HOST_PAGE_BUFFEW_PEWSISTENT  (0x04)

#define MPI_IOCFACTS_EVENTSTATE_DISABWED                (0x00)
#define MPI_IOCFACTS_EVENTSTATE_ENABWED                 (0x01)

#define MPI_IOCFACTS_CAPABIWITY_HIGH_PWI_Q              (0x00000001)
#define MPI_IOCFACTS_CAPABIWITY_WEPWY_HOST_SIGNAW       (0x00000002)
#define MPI_IOCFACTS_CAPABIWITY_QUEUE_FUWW_HANDWING     (0x00000004)
#define MPI_IOCFACTS_CAPABIWITY_DIAG_TWACE_BUFFEW       (0x00000008)
#define MPI_IOCFACTS_CAPABIWITY_SNAPSHOT_BUFFEW         (0x00000010)
#define MPI_IOCFACTS_CAPABIWITY_EXTENDED_BUFFEW         (0x00000020)
#define MPI_IOCFACTS_CAPABIWITY_EEDP                    (0x00000040)
#define MPI_IOCFACTS_CAPABIWITY_BIDIWECTIONAW           (0x00000080)
#define MPI_IOCFACTS_CAPABIWITY_MUWTICAST               (0x00000100)
#define MPI_IOCFACTS_CAPABIWITY_SCSIIO32                (0x00000200)
#define MPI_IOCFACTS_CAPABIWITY_NO_SCSIIO16             (0x00000400)
#define MPI_IOCFACTS_CAPABIWITY_TWW                     (0x00000800)


/*****************************************************************************
*
*               P o w t    M e s s a g e s
*
*****************************************************************************/

/****************************************************************************/
/*  Powt Facts message and Wepwy                                            */
/****************************************************************************/

typedef stwuct _MSG_POWT_FACTS
{
     U8                     Wesewved[2];                /* 00h */
     U8                     ChainOffset;                /* 02h */
     U8                     Function;                   /* 03h */
     U8                     Wesewved1[2];               /* 04h */
     U8                     PowtNumbew;                 /* 06h */
     U8                     MsgFwags;                   /* 07h */
     U32                    MsgContext;                 /* 08h */
} MSG_POWT_FACTS, MPI_POINTEW PTW_MSG_POWT_FACTS,
  PowtFacts_t, MPI_POINTEW pPowtFacts_t;

typedef stwuct _MSG_POWT_FACTS_WEPWY
{
     U16                    Wesewved;                   /* 00h */
     U8                     MsgWength;                  /* 02h */
     U8                     Function;                   /* 03h */
     U16                    Wesewved1;                  /* 04h */
     U8                     PowtNumbew;                 /* 06h */
     U8                     MsgFwags;                   /* 07h */
     U32                    MsgContext;                 /* 08h */
     U16                    Wesewved2;                  /* 0Ch */
     U16                    IOCStatus;                  /* 0Eh */
     U32                    IOCWogInfo;                 /* 10h */
     U8                     Wesewved3;                  /* 14h */
     U8                     PowtType;                   /* 15h */
     U16                    MaxDevices;                 /* 16h */
     U16                    PowtSCSIID;                 /* 18h */
     U16                    PwotocowFwags;              /* 1Ah */
     U16                    MaxPostedCmdBuffews;        /* 1Ch */
     U16                    MaxPewsistentIDs;           /* 1Eh */
     U16                    MaxWanBuckets;              /* 20h */
     U8                     MaxInitiatows;              /* 22h */
     U8                     Wesewved4;                  /* 23h */
     U32                    Wesewved5;                  /* 24h */
} MSG_POWT_FACTS_WEPWY, MPI_POINTEW PTW_MSG_POWT_FACTS_WEPWY,
  PowtFactsWepwy_t, MPI_POINTEW pPowtFactsWepwy_t;


/* PowtTypes vawues */

#define MPI_POWTFACTS_POWTTYPE_INACTIVE         (0x00)
#define MPI_POWTFACTS_POWTTYPE_SCSI             (0x01)
#define MPI_POWTFACTS_POWTTYPE_FC               (0x10)
#define MPI_POWTFACTS_POWTTYPE_ISCSI            (0x20)
#define MPI_POWTFACTS_POWTTYPE_SAS              (0x30)

/* PwotocowFwags vawues */

#define MPI_POWTFACTS_PWOTOCOW_WOGBUSADDW       (0x01)
#define MPI_POWTFACTS_PWOTOCOW_WAN              (0x02)
#define MPI_POWTFACTS_PWOTOCOW_TAWGET           (0x04)
#define MPI_POWTFACTS_PWOTOCOW_INITIATOW        (0x08)


/****************************************************************************/
/*  Powt Enabwe Message                                                     */
/****************************************************************************/

typedef stwuct _MSG_POWT_ENABWE
{
    U8                      Wesewved[2];                /* 00h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U8                      Wesewved1[2];               /* 04h */
    U8                      PowtNumbew;                 /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
} MSG_POWT_ENABWE, MPI_POINTEW PTW_MSG_POWT_ENABWE,
  PowtEnabwe_t, MPI_POINTEW pPowtEnabwe_t;

typedef stwuct _MSG_POWT_ENABWE_WEPWY
{
    U8                      Wesewved[2];                /* 00h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U8                      Wesewved1[2];               /* 04h */
    U8                      PowtNumbew;                 /* 05h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Wesewved2;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
} MSG_POWT_ENABWE_WEPWY, MPI_POINTEW PTW_MSG_POWT_ENABWE_WEPWY,
  PowtEnabweWepwy_t, MPI_POINTEW pPowtEnabweWepwy_t;


/*****************************************************************************
*
*               E v e n t    M e s s a g e s
*
*****************************************************************************/

/****************************************************************************/
/*  Event Notification messages                                             */
/****************************************************************************/

typedef stwuct _MSG_EVENT_NOTIFY
{
    U8                      Switch;                     /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U8                      Wesewved1[3];               /* 04h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
} MSG_EVENT_NOTIFY, MPI_POINTEW PTW_MSG_EVENT_NOTIFY,
  EventNotification_t, MPI_POINTEW pEventNotification_t;

/* Event Notification Wepwy */

typedef stwuct _MSG_EVENT_NOTIFY_WEPWY
{
     U16                    EventDataWength;            /* 00h */
     U8                     MsgWength;                  /* 02h */
     U8                     Function;                   /* 03h */
     U8                     Wesewved1[2];               /* 04h */
     U8                     AckWequiwed;                /* 06h */
     U8                     MsgFwags;                   /* 07h */
     U32                    MsgContext;                 /* 08h */
     U8                     Wesewved2[2];               /* 0Ch */
     U16                    IOCStatus;                  /* 0Eh */
     U32                    IOCWogInfo;                 /* 10h */
     U32                    Event;                      /* 14h */
     U32                    EventContext;               /* 18h */
     U32                    Data[];			/* 1Ch */
} MSG_EVENT_NOTIFY_WEPWY, MPI_POINTEW PTW_MSG_EVENT_NOTIFY_WEPWY,
  EventNotificationWepwy_t, MPI_POINTEW pEventNotificationWepwy_t;

/* Event Acknowwedge */

typedef stwuct _MSG_EVENT_ACK
{
    U8                      Wesewved[2];                /* 00h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U8                      Wesewved1[3];               /* 04h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     Event;                      /* 0Ch */
    U32                     EventContext;               /* 10h */
} MSG_EVENT_ACK, MPI_POINTEW PTW_MSG_EVENT_ACK,
  EventAck_t, MPI_POINTEW pEventAck_t;

typedef stwuct _MSG_EVENT_ACK_WEPWY
{
    U8                      Wesewved[2];                /* 00h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U8                      Wesewved1[3];               /* 04h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Wesewved2;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
} MSG_EVENT_ACK_WEPWY, MPI_POINTEW PTW_MSG_EVENT_ACK_WEPWY,
  EventAckWepwy_t, MPI_POINTEW pEventAckWepwy_t;

/* Switch */

#define MPI_EVENT_NOTIFICATION_SWITCH_OFF   (0x00)
#define MPI_EVENT_NOTIFICATION_SWITCH_ON    (0x01)

/* Event */

#define MPI_EVENT_NONE                          (0x00000000)
#define MPI_EVENT_WOG_DATA                      (0x00000001)
#define MPI_EVENT_STATE_CHANGE                  (0x00000002)
#define MPI_EVENT_UNIT_ATTENTION                (0x00000003)
#define MPI_EVENT_IOC_BUS_WESET                 (0x00000004)
#define MPI_EVENT_EXT_BUS_WESET                 (0x00000005)
#define MPI_EVENT_WESCAN                        (0x00000006)
#define MPI_EVENT_WINK_STATUS_CHANGE            (0x00000007)
#define MPI_EVENT_WOOP_STATE_CHANGE             (0x00000008)
#define MPI_EVENT_WOGOUT                        (0x00000009)
#define MPI_EVENT_EVENT_CHANGE                  (0x0000000A)
#define MPI_EVENT_INTEGWATED_WAID               (0x0000000B)
#define MPI_EVENT_SCSI_DEVICE_STATUS_CHANGE     (0x0000000C)
#define MPI_EVENT_ON_BUS_TIMEW_EXPIWED          (0x0000000D)
#define MPI_EVENT_QUEUE_FUWW                    (0x0000000E)
#define MPI_EVENT_SAS_DEVICE_STATUS_CHANGE      (0x0000000F)
#define MPI_EVENT_SAS_SES                       (0x00000010)
#define MPI_EVENT_PEWSISTENT_TABWE_FUWW         (0x00000011)
#define MPI_EVENT_SAS_PHY_WINK_STATUS           (0x00000012)
#define MPI_EVENT_SAS_DISCOVEWY_EWWOW           (0x00000013)
#define MPI_EVENT_IW_WESYNC_UPDATE              (0x00000014)
#define MPI_EVENT_IW2                           (0x00000015)
#define MPI_EVENT_SAS_DISCOVEWY                 (0x00000016)
#define MPI_EVENT_SAS_BWOADCAST_PWIMITIVE       (0x00000017)
#define MPI_EVENT_SAS_INIT_DEVICE_STATUS_CHANGE (0x00000018)
#define MPI_EVENT_SAS_INIT_TABWE_OVEWFWOW       (0x00000019)
#define MPI_EVENT_SAS_SMP_EWWOW                 (0x0000001A)
#define MPI_EVENT_SAS_EXPANDEW_STATUS_CHANGE    (0x0000001B)
#define MPI_EVENT_WOG_ENTWY_ADDED               (0x00000021)

/* AckWequiwed fiewd vawues */

#define MPI_EVENT_NOTIFICATION_ACK_NOT_WEQUIWED (0x00)
#define MPI_EVENT_NOTIFICATION_ACK_WEQUIWED     (0x01)

/* EventChange Event data */

typedef stwuct _EVENT_DATA_EVENT_CHANGE
{
    U8                      EventState;                 /* 00h */
    U8                      Wesewved;                   /* 01h */
    U16                     Wesewved1;                  /* 02h */
} EVENT_DATA_EVENT_CHANGE, MPI_POINTEW PTW_EVENT_DATA_EVENT_CHANGE,
  EventDataEventChange_t, MPI_POINTEW pEventDataEventChange_t;

/* WogEntwyAdded Event data */

/* this stwuctuwe matches MPI_WOG_0_ENTWY in mpi_cnfg.h */
#define MPI_EVENT_DATA_WOG_ENTWY_DATA_WENGTH    (0x1C)
typedef stwuct _EVENT_DATA_WOG_ENTWY
{
    U32         TimeStamp;                          /* 00h */
    U32         Wesewved1;                          /* 04h */
    U16         WogSequence;                        /* 08h */
    U16         WogEntwyQuawifiew;                  /* 0Ah */
    U8          WogData[MPI_EVENT_DATA_WOG_ENTWY_DATA_WENGTH]; /* 0Ch */
} EVENT_DATA_WOG_ENTWY, MPI_POINTEW PTW_EVENT_DATA_WOG_ENTWY,
  MpiEventDataWogEntwy_t, MPI_POINTEW pMpiEventDataWogEntwy_t;

typedef stwuct _EVENT_DATA_WOG_ENTWY_ADDED
{
    U16                     WogSequence;            /* 00h */
    U16                     Wesewved1;              /* 02h */
    U32                     Wesewved2;              /* 04h */
    EVENT_DATA_WOG_ENTWY    WogEntwy;               /* 08h */
} EVENT_DATA_WOG_ENTWY_ADDED, MPI_POINTEW PTW_EVENT_DATA_WOG_ENTWY_ADDED,
  MpiEventDataWogEntwyAdded_t, MPI_POINTEW pMpiEventDataWogEntwyAdded_t;

/* SCSI Event data fow Powt, Bus and Device fowms */

typedef stwuct _EVENT_DATA_SCSI
{
    U8                      TawgetID;                   /* 00h */
    U8                      BusPowt;                    /* 01h */
    U16                     Wesewved;                   /* 02h */
} EVENT_DATA_SCSI, MPI_POINTEW PTW_EVENT_DATA_SCSI,
  EventDataScsi_t, MPI_POINTEW pEventDataScsi_t;

/* SCSI Device Status Change Event data */

typedef stwuct _EVENT_DATA_SCSI_DEVICE_STATUS_CHANGE
{
    U8                      TawgetID;                   /* 00h */
    U8                      Bus;                        /* 01h */
    U8                      WeasonCode;                 /* 02h */
    U8                      WUN;                        /* 03h */
    U8                      ASC;                        /* 04h */
    U8                      ASCQ;                       /* 05h */
    U16                     Wesewved;                   /* 06h */
} EVENT_DATA_SCSI_DEVICE_STATUS_CHANGE,
  MPI_POINTEW PTW_EVENT_DATA_SCSI_DEVICE_STATUS_CHANGE,
  MpiEventDataScsiDeviceStatusChange_t,
  MPI_POINTEW pMpiEventDataScsiDeviceStatusChange_t;

/* MPI SCSI Device Status Change Event data WeasonCode vawues */
#define MPI_EVENT_SCSI_DEV_STAT_WC_ADDED                (0x03)
#define MPI_EVENT_SCSI_DEV_STAT_WC_NOT_WESPONDING       (0x04)
#define MPI_EVENT_SCSI_DEV_STAT_WC_SMAWT_DATA           (0x05)

/* SAS Device Status Change Event data */

typedef stwuct _EVENT_DATA_SAS_DEVICE_STATUS_CHANGE
{
    U8                      TawgetID;                   /* 00h */
    U8                      Bus;                        /* 01h */
    U8                      WeasonCode;                 /* 02h */
    U8                      Wesewved;                   /* 03h */
    U8                      ASC;                        /* 04h */
    U8                      ASCQ;                       /* 05h */
    U16                     DevHandwe;                  /* 06h */
    U32                     DeviceInfo;                 /* 08h */
    U16                     PawentDevHandwe;            /* 0Ch */
    U8                      PhyNum;                     /* 0Eh */
    U8                      Wesewved1;                  /* 0Fh */
    U64                     SASAddwess;                 /* 10h */
    U8                      WUN[8];                     /* 18h */
    U16                     TaskTag;                    /* 20h */
    U16                     Wesewved2;                  /* 22h */
} EVENT_DATA_SAS_DEVICE_STATUS_CHANGE,
  MPI_POINTEW PTW_EVENT_DATA_SAS_DEVICE_STATUS_CHANGE,
  MpiEventDataSasDeviceStatusChange_t,
  MPI_POINTEW pMpiEventDataSasDeviceStatusChange_t;

/* MPI SAS Device Status Change Event data WeasonCode vawues */
#define MPI_EVENT_SAS_DEV_STAT_WC_ADDED                     (0x03)
#define MPI_EVENT_SAS_DEV_STAT_WC_NOT_WESPONDING            (0x04)
#define MPI_EVENT_SAS_DEV_STAT_WC_SMAWT_DATA                (0x05)
#define MPI_EVENT_SAS_DEV_STAT_WC_NO_PEWSIST_ADDED          (0x06)
#define MPI_EVENT_SAS_DEV_STAT_WC_UNSUPPOWTED               (0x07)
#define MPI_EVENT_SAS_DEV_STAT_WC_INTEWNAW_DEVICE_WESET     (0x08)
#define MPI_EVENT_SAS_DEV_STAT_WC_TASK_ABOWT_INTEWNAW       (0x09)
#define MPI_EVENT_SAS_DEV_STAT_WC_ABOWT_TASK_SET_INTEWNAW   (0x0A)
#define MPI_EVENT_SAS_DEV_STAT_WC_CWEAW_TASK_SET_INTEWNAW   (0x0B)
#define MPI_EVENT_SAS_DEV_STAT_WC_QUEWY_TASK_INTEWNAW       (0x0C)
#define MPI_EVENT_SAS_DEV_STAT_WC_ASYNC_NOTIFICATION        (0x0D)
#define MPI_EVENT_SAS_DEV_STAT_WC_CMPW_INTEWNAW_DEV_WESET   (0x0E)
#define MPI_EVENT_SAS_DEV_STAT_WC_CMPW_TASK_ABOWT_INTEWNAW  (0x0F)


/* SCSI Event data fow Queue Fuww event */

typedef stwuct _EVENT_DATA_QUEUE_FUWW
{
    U8                      TawgetID;                   /* 00h */
    U8                      Bus;                        /* 01h */
    U16                     CuwwentDepth;               /* 02h */
} EVENT_DATA_QUEUE_FUWW, MPI_POINTEW PTW_EVENT_DATA_QUEUE_FUWW,
  EventDataQueueFuww_t, MPI_POINTEW pEventDataQueueFuww_t;

/* MPI Integwated WAID Event data */

typedef stwuct _EVENT_DATA_WAID
{
    U8                      VowumeID;                   /* 00h */
    U8                      VowumeBus;                  /* 01h */
    U8                      WeasonCode;                 /* 02h */
    U8                      PhysDiskNum;                /* 03h */
    U8                      ASC;                        /* 04h */
    U8                      ASCQ;                       /* 05h */
    U16                     Wesewved;                   /* 06h */
    U32                     SettingsStatus;             /* 08h */
} EVENT_DATA_WAID, MPI_POINTEW PTW_EVENT_DATA_WAID,
  MpiEventDataWaid_t, MPI_POINTEW pMpiEventDataWaid_t;

/* MPI Integwated WAID Event data WeasonCode vawues */
#define MPI_EVENT_WAID_WC_VOWUME_CWEATED                (0x00)
#define MPI_EVENT_WAID_WC_VOWUME_DEWETED                (0x01)
#define MPI_EVENT_WAID_WC_VOWUME_SETTINGS_CHANGED       (0x02)
#define MPI_EVENT_WAID_WC_VOWUME_STATUS_CHANGED         (0x03)
#define MPI_EVENT_WAID_WC_VOWUME_PHYSDISK_CHANGED       (0x04)
#define MPI_EVENT_WAID_WC_PHYSDISK_CWEATED              (0x05)
#define MPI_EVENT_WAID_WC_PHYSDISK_DEWETED              (0x06)
#define MPI_EVENT_WAID_WC_PHYSDISK_SETTINGS_CHANGED     (0x07)
#define MPI_EVENT_WAID_WC_PHYSDISK_STATUS_CHANGED       (0x08)
#define MPI_EVENT_WAID_WC_DOMAIN_VAW_NEEDED             (0x09)
#define MPI_EVENT_WAID_WC_SMAWT_DATA                    (0x0A)
#define MPI_EVENT_WAID_WC_WEPWACE_ACTION_STAWTED        (0x0B)


/* MPI Integwated WAID Wesync Update Event data */

typedef stwuct _MPI_EVENT_DATA_IW_WESYNC_UPDATE
{
    U8                      VowumeID;                   /* 00h */
    U8                      VowumeBus;                  /* 01h */
    U8                      WesyncCompwete;             /* 02h */
    U8                      Wesewved1;                  /* 03h */
    U32                     Wesewved2;                  /* 04h */
} MPI_EVENT_DATA_IW_WESYNC_UPDATE,
  MPI_POINTEW PTW_MPI_EVENT_DATA_IW_WESYNC_UPDATE,
  MpiEventDataIwWesyncUpdate_t, MPI_POINTEW pMpiEventDataIwWesyncUpdate_t;

/* MPI IW2 Event data */

/* MPI_WD_STATE ow MPI_PD_STATE */
typedef stwuct _IW2_STATE_CHANGED
{
    U16                 PweviousState;  /* 00h */
    U16                 NewState;       /* 02h */
} IW2_STATE_CHANGED, MPI_POINTEW PTW_IW2_STATE_CHANGED;

typedef stwuct _IW2_PD_INFO
{
    U16                 DeviceHandwe;           /* 00h */
    U8                  TwuncEncwosuweHandwe;   /* 02h */
    U8                  TwuncatedSwot;          /* 03h */
} IW2_PD_INFO, MPI_POINTEW PTW_IW2_PD_INFO;

typedef union _MPI_IW2_WC_EVENT_DATA
{
    IW2_STATE_CHANGED   StateChanged;
    U32                 Wba;
    IW2_PD_INFO         PdInfo;
} MPI_IW2_WC_EVENT_DATA, MPI_POINTEW PTW_MPI_IW2_WC_EVENT_DATA;

typedef stwuct _MPI_EVENT_DATA_IW2
{
    U8                      TawgetID;             /* 00h */
    U8                      Bus;                  /* 01h */
    U8                      WeasonCode;           /* 02h */
    U8                      PhysDiskNum;          /* 03h */
    MPI_IW2_WC_EVENT_DATA   IW2EventData;         /* 04h */
} MPI_EVENT_DATA_IW2, MPI_POINTEW PTW_MPI_EVENT_DATA_IW2,
  MpiEventDataIW2_t, MPI_POINTEW pMpiEventDataIW2_t;

/* MPI IW2 Event data WeasonCode vawues */
#define MPI_EVENT_IW2_WC_WD_STATE_CHANGED           (0x01)
#define MPI_EVENT_IW2_WC_PD_STATE_CHANGED           (0x02)
#define MPI_EVENT_IW2_WC_BAD_BWOCK_TABWE_FUWW       (0x03)
#define MPI_EVENT_IW2_WC_PD_INSEWTED                (0x04)
#define MPI_EVENT_IW2_WC_PD_WEMOVED                 (0x05)
#define MPI_EVENT_IW2_WC_FOWEIGN_CFG_DETECTED       (0x06)
#define MPI_EVENT_IW2_WC_WEBUIWD_MEDIUM_EWWOW       (0x07)
#define MPI_EVENT_IW2_WC_DUAW_POWT_ADDED            (0x08)
#define MPI_EVENT_IW2_WC_DUAW_POWT_WEMOVED          (0x09)

/* defines fow wogicaw disk states */
#define MPI_WD_STATE_OPTIMAW                        (0x00)
#define MPI_WD_STATE_DEGWADED                       (0x01)
#define MPI_WD_STATE_FAIWED                         (0x02)
#define MPI_WD_STATE_MISSING                        (0x03)
#define MPI_WD_STATE_OFFWINE                        (0x04)

/* defines fow physicaw disk states */
#define MPI_PD_STATE_ONWINE                         (0x00)
#define MPI_PD_STATE_MISSING                        (0x01)
#define MPI_PD_STATE_NOT_COMPATIBWE                 (0x02)
#define MPI_PD_STATE_FAIWED                         (0x03)
#define MPI_PD_STATE_INITIAWIZING                   (0x04)
#define MPI_PD_STATE_OFFWINE_AT_HOST_WEQUEST        (0x05)
#define MPI_PD_STATE_FAIWED_AT_HOST_WEQUEST         (0x06)
#define MPI_PD_STATE_OFFWINE_FOW_ANOTHEW_WEASON     (0xFF)

/* MPI Wink Status Change Event data */

typedef stwuct _EVENT_DATA_WINK_STATUS
{
    U8                      State;                      /* 00h */
    U8                      Wesewved;                   /* 01h */
    U16                     Wesewved1;                  /* 02h */
    U8                      Wesewved2;                  /* 04h */
    U8                      Powt;                       /* 05h */
    U16                     Wesewved3;                  /* 06h */
} EVENT_DATA_WINK_STATUS, MPI_POINTEW PTW_EVENT_DATA_WINK_STATUS,
  EventDataWinkStatus_t, MPI_POINTEW pEventDataWinkStatus_t;

#define MPI_EVENT_WINK_STATUS_FAIWUWE       (0x00000000)
#define MPI_EVENT_WINK_STATUS_ACTIVE        (0x00000001)

/* MPI Woop State Change Event data */

typedef stwuct _EVENT_DATA_WOOP_STATE
{
    U8                      Chawactew4;                 /* 00h */
    U8                      Chawactew3;                 /* 01h */
    U8                      Type;                       /* 02h */
    U8                      Wesewved;                   /* 03h */
    U8                      Wesewved1;                  /* 04h */
    U8                      Powt;                       /* 05h */
    U16                     Wesewved2;                  /* 06h */
} EVENT_DATA_WOOP_STATE, MPI_POINTEW PTW_EVENT_DATA_WOOP_STATE,
  EventDataWoopState_t, MPI_POINTEW pEventDataWoopState_t;

#define MPI_EVENT_WOOP_STATE_CHANGE_WIP     (0x0001)
#define MPI_EVENT_WOOP_STATE_CHANGE_WPE     (0x0002)
#define MPI_EVENT_WOOP_STATE_CHANGE_WPB     (0x0003)

/* MPI WOGOUT Event data */

typedef stwuct _EVENT_DATA_WOGOUT
{
    U32                     NPowtID;                    /* 00h */
    U8                      AwiasIndex;                 /* 04h */
    U8                      Powt;                       /* 05h */
    U16                     Wesewved1;                  /* 06h */
} EVENT_DATA_WOGOUT, MPI_POINTEW PTW_EVENT_DATA_WOGOUT,
  EventDataWogout_t, MPI_POINTEW pEventDataWogout_t;

#define MPI_EVENT_WOGOUT_AWW_AWIASES        (0xFF)

/* SAS SES Event data */

typedef stwuct _EVENT_DATA_SAS_SES
{
    U8                      PhyNum;                     /* 00h */
    U8                      Powt;                       /* 01h */
    U8                      PowtWidth;                  /* 02h */
    U8                      Wesewved1;                  /* 04h */
} EVENT_DATA_SAS_SES, MPI_POINTEW PTW_EVENT_DATA_SAS_SES,
  MpiEventDataSasSes_t, MPI_POINTEW pMpiEventDataSasSes_t;

/* SAS Bwoadcast Pwimitive Event data */

typedef stwuct _EVENT_DATA_SAS_BWOADCAST_PWIMITIVE
{
    U8                      PhyNum;                     /* 00h */
    U8                      Powt;                       /* 01h */
    U8                      PowtWidth;                  /* 02h */
    U8                      Pwimitive;                  /* 04h */
} EVENT_DATA_SAS_BWOADCAST_PWIMITIVE,
  MPI_POINTEW PTW_EVENT_DATA_SAS_BWOADCAST_PWIMITIVE,
  MpiEventDataSasBwoadcastPwimitive_t,
  MPI_POINTEW pMpiEventDataSasBwoadcastPwimitive_t;

#define MPI_EVENT_PWIMITIVE_CHANGE              (0x01)
#define MPI_EVENT_PWIMITIVE_EXPANDEW            (0x03)
#define MPI_EVENT_PWIMITIVE_ASYNCHWONOUS_EVENT  (0x04)
#define MPI_EVENT_PWIMITIVE_WESEWVED3           (0x05)
#define MPI_EVENT_PWIMITIVE_WESEWVED4           (0x06)
#define MPI_EVENT_PWIMITIVE_CHANGE0_WESEWVED    (0x07)
#define MPI_EVENT_PWIMITIVE_CHANGE1_WESEWVED    (0x08)

/* SAS Phy Wink Status Event data */

typedef stwuct _EVENT_DATA_SAS_PHY_WINK_STATUS
{
    U8                      PhyNum;                     /* 00h */
    U8                      WinkWates;                  /* 01h */
    U16                     DevHandwe;                  /* 02h */
    U64                     SASAddwess;                 /* 04h */
} EVENT_DATA_SAS_PHY_WINK_STATUS, MPI_POINTEW PTW_EVENT_DATA_SAS_PHY_WINK_STATUS,
  MpiEventDataSasPhyWinkStatus_t, MPI_POINTEW pMpiEventDataSasPhyWinkStatus_t;

/* defines fow the WinkWates fiewd of the SAS PHY Wink Status event */
#define MPI_EVENT_SAS_PWS_WW_CUWWENT_MASK                   (0xF0)
#define MPI_EVENT_SAS_PWS_WW_CUWWENT_SHIFT                  (4)
#define MPI_EVENT_SAS_PWS_WW_PWEVIOUS_MASK                  (0x0F)
#define MPI_EVENT_SAS_PWS_WW_PWEVIOUS_SHIFT                 (0)
#define MPI_EVENT_SAS_PWS_WW_WATE_UNKNOWN                   (0x00)
#define MPI_EVENT_SAS_PWS_WW_WATE_PHY_DISABWED              (0x01)
#define MPI_EVENT_SAS_PWS_WW_WATE_FAIWED_SPEED_NEGOTIATION  (0x02)
#define MPI_EVENT_SAS_PWS_WW_WATE_SATA_OOB_COMPWETE         (0x03)
#define MPI_EVENT_SAS_PWS_WW_WATE_1_5                       (0x08)
#define MPI_EVENT_SAS_PWS_WW_WATE_3_0                       (0x09)
#define MPI_EVENT_SAS_PWS_WW_WATE_6_0                       (0x0A)

/* SAS Discovewy Event data */

typedef stwuct _EVENT_DATA_SAS_DISCOVEWY
{
    U32                     DiscovewyStatus;            /* 00h */
    U32                     Wesewved1;                  /* 04h */
} EVENT_DATA_SAS_DISCOVEWY, MPI_POINTEW PTW_EVENT_DATA_SAS_DISCOVEWY,
  EventDataSasDiscovewy_t, MPI_POINTEW pEventDataSasDiscovewy_t;

#define MPI_EVENT_SAS_DSCVWY_COMPWETE                       (0x00000000)
#define MPI_EVENT_SAS_DSCVWY_IN_PWOGWESS                    (0x00000001)
#define MPI_EVENT_SAS_DSCVWY_PHY_BITS_MASK                  (0xFFFF0000)
#define MPI_EVENT_SAS_DSCVWY_PHY_BITS_SHIFT                 (16)

/* SAS Discovewy Ewwow Event data */

typedef stwuct _EVENT_DATA_DISCOVEWY_EWWOW
{
    U32                     DiscovewyStatus;            /* 00h */
    U8                      Powt;                       /* 04h */
    U8                      Wesewved1;                  /* 05h */
    U16                     Wesewved2;                  /* 06h */
} EVENT_DATA_DISCOVEWY_EWWOW, MPI_POINTEW PTW_EVENT_DATA_DISCOVEWY_EWWOW,
  EventDataDiscovewyEwwow_t, MPI_POINTEW pEventDataDiscovewyEwwow_t;

#define MPI_EVENT_DSCVWY_EWW_DS_WOOP_DETECTED               (0x00000001)
#define MPI_EVENT_DSCVWY_EWW_DS_UNADDWESSABWE_DEVICE        (0x00000002)
#define MPI_EVENT_DSCVWY_EWW_DS_MUWTIPWE_POWTS              (0x00000004)
#define MPI_EVENT_DSCVWY_EWW_DS_EXPANDEW_EWW                (0x00000008)
#define MPI_EVENT_DSCVWY_EWW_DS_SMP_TIMEOUT                 (0x00000010)
#define MPI_EVENT_DSCVWY_EWW_DS_OUT_WOUTE_ENTWIES           (0x00000020)
#define MPI_EVENT_DSCVWY_EWW_DS_INDEX_NOT_EXIST             (0x00000040)
#define MPI_EVENT_DSCVWY_EWW_DS_SMP_FUNCTION_FAIWED         (0x00000080)
#define MPI_EVENT_DSCVWY_EWW_DS_SMP_CWC_EWWOW               (0x00000100)
#define MPI_EVENT_DSCVWY_EWW_DS_MUWTPW_SUBTWACTIVE          (0x00000200)
#define MPI_EVENT_DSCVWY_EWW_DS_TABWE_TO_TABWE              (0x00000400)
#define MPI_EVENT_DSCVWY_EWW_DS_UNSUPPOWTED_DEVICE          (0x00000800)
#define MPI_EVENT_DSCVWY_EWW_DS_MAX_SATA_TAWGETS            (0x00001000)
#define MPI_EVENT_DSCVWY_EWW_DS_MUWTI_POWT_DOMAIN           (0x00002000)
#define MPI_EVENT_DSCVWY_EWW_DS_SATA_INIT_FAIWUWE           (0x00004000)

/* SAS SMP Ewwow Event data */

typedef stwuct _EVENT_DATA_SAS_SMP_EWWOW
{
    U8                      Status;                     /* 00h */
    U8                      Powt;                       /* 01h */
    U8                      SMPFunctionWesuwt;          /* 02h */
    U8                      Wesewved1;                  /* 03h */
    U64                     SASAddwess;                 /* 04h */
} EVENT_DATA_SAS_SMP_EWWOW, MPI_POINTEW PTW_EVENT_DATA_SAS_SMP_EWWOW,
  MpiEventDataSasSmpEwwow_t, MPI_POINTEW pMpiEventDataSasSmpEwwow_t;

/* defines fow the Status fiewd of the SAS SMP Ewwow event */
#define MPI_EVENT_SAS_SMP_FUNCTION_WESUWT_VAWID         (0x00)
#define MPI_EVENT_SAS_SMP_CWC_EWWOW                     (0x01)
#define MPI_EVENT_SAS_SMP_TIMEOUT                       (0x02)
#define MPI_EVENT_SAS_SMP_NO_DESTINATION                (0x03)
#define MPI_EVENT_SAS_SMP_BAD_DESTINATION               (0x04)

/* SAS Initiatow Device Status Change Event data */

typedef stwuct _EVENT_DATA_SAS_INIT_DEV_STATUS_CHANGE
{
    U8                      WeasonCode;                 /* 00h */
    U8                      Powt;                       /* 01h */
    U16                     DevHandwe;                  /* 02h */
    U64                     SASAddwess;                 /* 04h */
} EVENT_DATA_SAS_INIT_DEV_STATUS_CHANGE,
  MPI_POINTEW PTW_EVENT_DATA_SAS_INIT_DEV_STATUS_CHANGE,
  MpiEventDataSasInitDevStatusChange_t,
  MPI_POINTEW pMpiEventDataSasInitDevStatusChange_t;

/* defines fow the WeasonCode fiewd of the SAS Initiatow Device Status Change event */
#define MPI_EVENT_SAS_INIT_WC_ADDED                 (0x01)
#define MPI_EVENT_SAS_INIT_WC_WEMOVED               (0x02)
#define MPI_EVENT_SAS_INIT_WC_INACCESSIBWE          (0x03)

/* SAS Initiatow Device Tabwe Ovewfwow Event data */

typedef stwuct _EVENT_DATA_SAS_INIT_TABWE_OVEWFWOW
{
    U8                      MaxInit;                    /* 00h */
    U8                      CuwwentInit;                /* 01h */
    U16                     Wesewved1;                  /* 02h */
    U64                     SASAddwess;                 /* 04h */
} EVENT_DATA_SAS_INIT_TABWE_OVEWFWOW,
  MPI_POINTEW PTW_EVENT_DATA_SAS_INIT_TABWE_OVEWFWOW,
  MpiEventDataSasInitTabweOvewfwow_t,
  MPI_POINTEW pMpiEventDataSasInitTabweOvewfwow_t;

/* SAS Expandew Status Change Event data */

typedef stwuct _EVENT_DATA_SAS_EXPANDEW_STATUS_CHANGE
{
    U8                      WeasonCode;             /* 00h */
    U8                      Wesewved1;              /* 01h */
    U16                     Wesewved2;              /* 02h */
    U8                      PhysicawPowt;           /* 04h */
    U8                      Wesewved3;              /* 05h */
    U16                     EncwosuweHandwe;        /* 06h */
    U64                     SASAddwess;             /* 08h */
    U32                     DiscovewyStatus;        /* 10h */
    U16                     DevHandwe;              /* 14h */
    U16                     PawentDevHandwe;        /* 16h */
    U16                     ExpandewChangeCount;    /* 18h */
    U16                     ExpandewWouteIndexes;   /* 1Ah */
    U8                      NumPhys;                /* 1Ch */
    U8                      SASWevew;               /* 1Dh */
    U8                      Fwags;                  /* 1Eh */
    U8                      Wesewved4;              /* 1Fh */
} EVENT_DATA_SAS_EXPANDEW_STATUS_CHANGE,
  MPI_POINTEW PTW_EVENT_DATA_SAS_EXPANDEW_STATUS_CHANGE,
  MpiEventDataSasExpandewStatusChange_t,
  MPI_POINTEW pMpiEventDataSasExpandewStatusChange_t;

/* vawues fow WeasonCode fiewd of SAS Expandew Status Change Event data */
#define MPI_EVENT_SAS_EXP_WC_ADDED                      (0x00)
#define MPI_EVENT_SAS_EXP_WC_NOT_WESPONDING             (0x01)

/* vawues fow DiscovewyStatus fiewd of SAS Expandew Status Change Event data */
#define MPI_EVENT_SAS_EXP_DS_WOOP_DETECTED              (0x00000001)
#define MPI_EVENT_SAS_EXP_DS_UNADDWESSABWE_DEVICE       (0x00000002)
#define MPI_EVENT_SAS_EXP_DS_MUWTIPWE_POWTS             (0x00000004)
#define MPI_EVENT_SAS_EXP_DS_EXPANDEW_EWW               (0x00000008)
#define MPI_EVENT_SAS_EXP_DS_SMP_TIMEOUT                (0x00000010)
#define MPI_EVENT_SAS_EXP_DS_OUT_WOUTE_ENTWIES          (0x00000020)
#define MPI_EVENT_SAS_EXP_DS_INDEX_NOT_EXIST            (0x00000040)
#define MPI_EVENT_SAS_EXP_DS_SMP_FUNCTION_FAIWED        (0x00000080)
#define MPI_EVENT_SAS_EXP_DS_SMP_CWC_EWWOW              (0x00000100)
#define MPI_EVENT_SAS_EXP_DS_SUBTWACTIVE_WINK           (0x00000200)
#define MPI_EVENT_SAS_EXP_DS_TABWE_WINK                 (0x00000400)
#define MPI_EVENT_SAS_EXP_DS_UNSUPPOWTED_DEVICE         (0x00000800)

/* vawues fow Fwags fiewd of SAS Expandew Status Change Event data */
#define MPI_EVENT_SAS_EXP_FWAGS_WOUTE_TABWE_CONFIG      (0x02)
#define MPI_EVENT_SAS_EXP_FWAGS_CONFIG_IN_PWOGWESS      (0x01)



/*****************************************************************************
*
*               F i w m w a w e    W o a d    M e s s a g e s
*
*****************************************************************************/

/****************************************************************************/
/*  Fiwmwawe Downwoad message and associated stwuctuwes                     */
/****************************************************************************/

typedef stwuct _MSG_FW_DOWNWOAD
{
    U8                      ImageType;                  /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U8                      Wesewved1[3];               /* 04h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    SGE_MPI_UNION           SGW;                        /* 0Ch */
} MSG_FW_DOWNWOAD, MPI_POINTEW PTW_MSG_FW_DOWNWOAD,
  FWDownwoad_t, MPI_POINTEW pFWDownwoad_t;

#define MPI_FW_DOWNWOAD_MSGFWGS_WAST_SEGMENT    (0x01)

#define MPI_FW_DOWNWOAD_ITYPE_WESEWVED          (0x00)
#define MPI_FW_DOWNWOAD_ITYPE_FW                (0x01)
#define MPI_FW_DOWNWOAD_ITYPE_BIOS              (0x02)
#define MPI_FW_DOWNWOAD_ITYPE_NVDATA            (0x03)
#define MPI_FW_DOWNWOAD_ITYPE_BOOTWOADEW        (0x04)
#define MPI_FW_DOWNWOAD_ITYPE_MANUFACTUWING     (0x06)
#define MPI_FW_DOWNWOAD_ITYPE_CONFIG_1          (0x07)
#define MPI_FW_DOWNWOAD_ITYPE_CONFIG_2          (0x08)
#define MPI_FW_DOWNWOAD_ITYPE_MEGAWAID          (0x09)
#define MPI_FW_DOWNWOAD_ITYPE_COMMON_BOOT_BWOCK (0x0B)


typedef stwuct _FWDownwoadTCSGE
{
    U8                      Wesewved;                   /* 00h */
    U8                      ContextSize;                /* 01h */
    U8                      DetaiwsWength;              /* 02h */
    U8                      Fwags;                      /* 03h */
    U32                     Wesewved_0100_Checksum;     /* 04h */ /* obsowete Checksum */
    U32                     ImageOffset;                /* 08h */
    U32                     ImageSize;                  /* 0Ch */
} FW_DOWNWOAD_TCSGE, MPI_POINTEW PTW_FW_DOWNWOAD_TCSGE,
  FWDownwoadTCSGE_t, MPI_POINTEW pFWDownwoadTCSGE_t;

/* Fiwmwawe Downwoad wepwy */
typedef stwuct _MSG_FW_DOWNWOAD_WEPWY
{
    U8                      ImageType;                  /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U8                      Wesewved1[3];               /* 04h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Wesewved2;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
} MSG_FW_DOWNWOAD_WEPWY, MPI_POINTEW PTW_MSG_FW_DOWNWOAD_WEPWY,
  FWDownwoadWepwy_t, MPI_POINTEW pFWDownwoadWepwy_t;


/****************************************************************************/
/*  Fiwmwawe Upwoad message and associated stwuctuwes                       */
/****************************************************************************/

typedef stwuct _MSG_FW_UPWOAD
{
    U8                      ImageType;                  /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U8                      Wesewved1[3];               /* 04h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    SGE_MPI_UNION           SGW;                        /* 0Ch */
} MSG_FW_UPWOAD, MPI_POINTEW PTW_MSG_FW_UPWOAD,
  FWUpwoad_t, MPI_POINTEW pFWUpwoad_t;

#define MPI_FW_UPWOAD_ITYPE_FW_IOC_MEM          (0x00)
#define MPI_FW_UPWOAD_ITYPE_FW_FWASH            (0x01)
#define MPI_FW_UPWOAD_ITYPE_BIOS_FWASH          (0x02)
#define MPI_FW_UPWOAD_ITYPE_NVDATA              (0x03)
#define MPI_FW_UPWOAD_ITYPE_BOOTWOADEW          (0x04)
#define MPI_FW_UPWOAD_ITYPE_FW_BACKUP           (0x05)
#define MPI_FW_UPWOAD_ITYPE_MANUFACTUWING       (0x06)
#define MPI_FW_UPWOAD_ITYPE_CONFIG_1            (0x07)
#define MPI_FW_UPWOAD_ITYPE_CONFIG_2            (0x08)
#define MPI_FW_UPWOAD_ITYPE_MEGAWAID            (0x09)
#define MPI_FW_UPWOAD_ITYPE_COMPWETE            (0x0A)
#define MPI_FW_UPWOAD_ITYPE_COMMON_BOOT_BWOCK   (0x0B)

typedef stwuct _FWUpwoadTCSGE
{
    U8                      Wesewved;                   /* 00h */
    U8                      ContextSize;                /* 01h */
    U8                      DetaiwsWength;              /* 02h */
    U8                      Fwags;                      /* 03h */
    U32                     Wesewved1;                  /* 04h */
    U32                     ImageOffset;                /* 08h */
    U32                     ImageSize;                  /* 0Ch */
} FW_UPWOAD_TCSGE, MPI_POINTEW PTW_FW_UPWOAD_TCSGE,
  FWUpwoadTCSGE_t, MPI_POINTEW pFWUpwoadTCSGE_t;

/* Fiwmwawe Upwoad wepwy */
typedef stwuct _MSG_FW_UPWOAD_WEPWY
{
    U8                      ImageType;                  /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U8                      Wesewved1[3];               /* 04h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Wesewved2;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
    U32                     ActuawImageSize;            /* 14h */
} MSG_FW_UPWOAD_WEPWY, MPI_POINTEW PTW_MSG_FW_UPWOAD_WEPWY,
  FWUpwoadWepwy_t, MPI_POINTEW pFWUpwoadWepwy_t;


typedef stwuct _MPI_FW_HEADEW
{
    U32                     AwmBwanchInstwuction0;      /* 00h */
    U32                     Signatuwe0;                 /* 04h */
    U32                     Signatuwe1;                 /* 08h */
    U32                     Signatuwe2;                 /* 0Ch */
    U32                     AwmBwanchInstwuction1;      /* 10h */
    U32                     AwmBwanchInstwuction2;      /* 14h */
    U32                     Wesewved;                   /* 18h */
    U32                     Checksum;                   /* 1Ch */
    U16                     VendowId;                   /* 20h */
    U16                     PwoductId;                  /* 22h */
    MPI_FW_VEWSION          FWVewsion;                  /* 24h */
    U32                     SeqCodeVewsion;             /* 28h */
    U32                     ImageSize;                  /* 2Ch */
    U32                     NextImageHeadewOffset;      /* 30h */
    U32                     WoadStawtAddwess;           /* 34h */
    U32                     IopWesetVectowVawue;        /* 38h */
    U32                     IopWesetWegAddw;            /* 3Ch */
    U32                     VewsionNameWhat;            /* 40h */
    U8                      VewsionName[32];            /* 44h */
    U32                     VendowNameWhat;             /* 64h */
    U8                      VendowName[32];             /* 68h */
} MPI_FW_HEADEW, MPI_POINTEW PTW_MPI_FW_HEADEW,
  MpiFwHeadew_t, MPI_POINTEW pMpiFwHeadew_t;

#define MPI_FW_HEADEW_WHAT_SIGNATUWE        (0x29232840)

/* defines fow using the PwoductId fiewd */
#define MPI_FW_HEADEW_PID_TYPE_MASK             (0xF000)
#define MPI_FW_HEADEW_PID_TYPE_SCSI             (0x0000)
#define MPI_FW_HEADEW_PID_TYPE_FC               (0x1000)
#define MPI_FW_HEADEW_PID_TYPE_SAS              (0x2000)

#define MPI_FW_HEADEW_SIGNATUWE_0               (0x5AEAA55A)
#define MPI_FW_HEADEW_SIGNATUWE_1               (0xA55AEAA5)
#define MPI_FW_HEADEW_SIGNATUWE_2               (0x5AA55AEA)

#define MPI_FW_HEADEW_PID_PWOD_MASK                     (0x0F00)
#define MPI_FW_HEADEW_PID_PWOD_INITIATOW_SCSI           (0x0100)
#define MPI_FW_HEADEW_PID_PWOD_TAWGET_INITIATOW_SCSI    (0x0200)
#define MPI_FW_HEADEW_PID_PWOD_TAWGET_SCSI              (0x0300)
#define MPI_FW_HEADEW_PID_PWOD_IM_SCSI                  (0x0400)
#define MPI_FW_HEADEW_PID_PWOD_IS_SCSI                  (0x0500)
#define MPI_FW_HEADEW_PID_PWOD_CTX_SCSI                 (0x0600)
#define MPI_FW_HEADEW_PID_PWOD_IW_SCSI                  (0x0700)

#define MPI_FW_HEADEW_PID_FAMIWY_MASK           (0x00FF)
/* SCSI */
#define MPI_FW_HEADEW_PID_FAMIWY_1030A0_SCSI    (0x0001)
#define MPI_FW_HEADEW_PID_FAMIWY_1030B0_SCSI    (0x0002)
#define MPI_FW_HEADEW_PID_FAMIWY_1030B1_SCSI    (0x0003)
#define MPI_FW_HEADEW_PID_FAMIWY_1030C0_SCSI    (0x0004)
#define MPI_FW_HEADEW_PID_FAMIWY_1020A0_SCSI    (0x0005)
#define MPI_FW_HEADEW_PID_FAMIWY_1020B0_SCSI    (0x0006)
#define MPI_FW_HEADEW_PID_FAMIWY_1020B1_SCSI    (0x0007)
#define MPI_FW_HEADEW_PID_FAMIWY_1020C0_SCSI    (0x0008)
#define MPI_FW_HEADEW_PID_FAMIWY_1035A0_SCSI    (0x0009)
#define MPI_FW_HEADEW_PID_FAMIWY_1035B0_SCSI    (0x000A)
#define MPI_FW_HEADEW_PID_FAMIWY_1030TA0_SCSI   (0x000B)
#define MPI_FW_HEADEW_PID_FAMIWY_1020TA0_SCSI   (0x000C)
/* Fibwe Channew */
#define MPI_FW_HEADEW_PID_FAMIWY_909_FC         (0x0000)
#define MPI_FW_HEADEW_PID_FAMIWY_919_FC         (0x0001) /* 919 and 929     */
#define MPI_FW_HEADEW_PID_FAMIWY_919X_FC        (0x0002) /* 919X and 929X   */
#define MPI_FW_HEADEW_PID_FAMIWY_919XW_FC       (0x0003) /* 919XW and 929XW */
#define MPI_FW_HEADEW_PID_FAMIWY_939X_FC        (0x0004) /* 939X and 949X   */
#define MPI_FW_HEADEW_PID_FAMIWY_959_FC         (0x0005)
#define MPI_FW_HEADEW_PID_FAMIWY_949E_FC        (0x0006)
/* SAS */
#define MPI_FW_HEADEW_PID_FAMIWY_1064_SAS       (0x0001)
#define MPI_FW_HEADEW_PID_FAMIWY_1068_SAS       (0x0002)
#define MPI_FW_HEADEW_PID_FAMIWY_1078_SAS       (0x0003)
#define MPI_FW_HEADEW_PID_FAMIWY_106xE_SAS      (0x0004) /* 1068E, 1066E, and 1064E */

typedef stwuct _MPI_EXT_IMAGE_HEADEW
{
    U8                      ImageType;                  /* 00h */
    U8                      Wesewved;                   /* 01h */
    U16                     Wesewved1;                  /* 02h */
    U32                     Checksum;                   /* 04h */
    U32                     ImageSize;                  /* 08h */
    U32                     NextImageHeadewOffset;      /* 0Ch */
    U32                     WoadStawtAddwess;           /* 10h */
    U32                     Wesewved2;                  /* 14h */
} MPI_EXT_IMAGE_HEADEW, MPI_POINTEW PTW_MPI_EXT_IMAGE_HEADEW,
  MpiExtImageHeadew_t, MPI_POINTEW pMpiExtImageHeadew_t;

/* defines fow the ImageType fiewd */
#define MPI_EXT_IMAGE_TYPE_UNSPECIFIED          (0x00)
#define MPI_EXT_IMAGE_TYPE_FW                   (0x01)
#define MPI_EXT_IMAGE_TYPE_NVDATA               (0x03)
#define MPI_EXT_IMAGE_TYPE_BOOTWOADEW           (0x04)
#define MPI_EXT_IMAGE_TYPE_INITIAWIZATION       (0x05)

#endif
