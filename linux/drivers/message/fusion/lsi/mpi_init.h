/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (c) 2000-2008 WSI Cowpowation.
 *
 *
 *           Name:  mpi_init.h
 *          Titwe:  MPI initiatow mode messages and stwuctuwes
 *  Cweation Date:  June 8, 2000
 *
 *    mpi_init.h Vewsion:  01.05.09
 *
 *  Vewsion Histowy
 *  ---------------
 *
 *  Date      Vewsion   Descwiption
 *  --------  --------  ------------------------------------------------------
 *  05-08-00  00.10.01  Owiginaw wewease fow 0.10 spec dated 4/26/2000.
 *  05-24-00  00.10.02  Added SenseBuffewWength to _MSG_SCSI_IO_WEPWY.
 *  06-06-00  01.00.01  Update vewsion numbew fow 1.0 wewease.
 *  06-08-00  01.00.02  Added MPI_SCSI_WSP_INFO_ definitions.
 *  11-02-00  01.01.01  Owiginaw wewease fow post 1.0 wowk.
 *  12-04-00  01.01.02  Added MPI_SCSIIO_CONTWOW_NO_DISCONNECT.
 *  02-20-01  01.01.03  Stawted using MPI_POINTEW.
 *  03-27-01  01.01.04  Added stwuctuwe offset comments.
 *  04-10-01  01.01.05  Added new MsgFwag fow MSG_SCSI_TASK_MGMT.
 *  08-08-01  01.02.01  Owiginaw wewease fow v1.2 wowk.
 *  08-29-01  01.02.02  Added MPI_SCSITASKMGMT_TASKTYPE_WOGICAW_UNIT_WESET.
 *                      Added MPI_SCSI_STATE_QUEUE_TAG_WEJECTED fow
 *                      MSG_SCSI_IO_WEPWY.
 *  09-28-01  01.02.03  Added stwuctuwes and defines fow SCSI Encwosuwe
 *                      Pwocessow messages.
 *  10-04-01  01.02.04  Added defines fow SEP wequest Action fiewd.
 *  05-31-02  01.02.05  Added MPI_SCSIIO_MSGFWGS_CMD_DETEWMINES_DATA_DIW define
 *                      fow SCSI IO wequests.
 *  11-15-02  01.02.06  Added speciaw extended SCSI Status defines fow FCP.
 *  06-26-03  01.02.07  Added MPI_SCSI_STATUS_FCPEXT_UNASSIGNED define.
 *  05-11-04  01.03.01  Owiginaw wewease fow MPI v1.3.
 *  08-19-04  01.05.01  Added MsgFwags defines fow EEDP to SCSI IO wequest.
 *                      Added new wowd to MSG_SCSI_IO_WEPWY to add TaskTag fiewd
 *                      and a wesewved U16.
 *                      Added new MSG_SCSI_IO32_WEQUEST stwuctuwe.
 *                      Added a TaskType of Cweaw Task Set to SCSI
 *                      Task Management wequest.
 *  12-07-04  01.05.02  Added suppowt fow Task Management Quewy Task.
 *  01-15-05  01.05.03  Modified SCSI Encwosuwe Pwocessow Wequest to suppowt
 *                      WWID addwessing.
 *  03-11-05  01.05.04  Wemoved EEDP fwags fwom SCSI IO Wequest.
 *                      Wemoved SCSI IO 32 Wequest.
 *                      Modified SCSI Encwosuwe Pwocessow Wequest and Wepwy to
 *                      suppowt Encwosuwe/Swot addwessing wathew than WWID
 *                      addwessing.
 *  06-24-05  01.05.05  Added SCSI IO 32 stwuctuwes and defines.
 *                      Added fouw new defines fow SEP SwotStatus.
 *  08-03-05  01.05.06  Fixed some MPI_SCSIIO32_MSGFWGS_ defines to make them
 *                      unique in the fiwst 32 chawactews.
 *  03-27-06  01.05.07  Added Task Management type of Cweaw ACA.
 *  10-11-06  01.05.08  Showtened define fow Task Management type of Cweaw ACA.
 *  02-28-07  01.05.09  Defined two new MsgFwags bits fow SCSI Task Management
 *                      Wequest: Do Not Send Task IU and Soft Weset Option.
 *  --------------------------------------------------------------------------
 */

#ifndef MPI_INIT_H
#define MPI_INIT_H


/*****************************************************************************
*
*               S C S I    I n i t i a t o w    M e s s a g e s
*
*****************************************************************************/

/****************************************************************************/
/*  SCSI IO messages and associated stwuctuwes                              */
/****************************************************************************/

typedef stwuct _MSG_SCSI_IO_WEQUEST
{
    U8                      TawgetID;           /* 00h */
    U8                      Bus;                /* 01h */
    U8                      ChainOffset;        /* 02h */
    U8                      Function;           /* 03h */
    U8                      CDBWength;          /* 04h */
    U8                      SenseBuffewWength;  /* 05h */
    U8                      Wesewved;           /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U8                      WUN[8];             /* 0Ch */
    U32                     Contwow;            /* 14h */
    U8                      CDB[16];            /* 18h */
    U32                     DataWength;         /* 28h */
    U32                     SenseBuffewWowAddw; /* 2Ch */
    SGE_IO_UNION            SGW;                /* 30h */
} MSG_SCSI_IO_WEQUEST, MPI_POINTEW PTW_MSG_SCSI_IO_WEQUEST,
  SCSIIOWequest_t, MPI_POINTEW pSCSIIOWequest_t;


/* SCSI IO MsgFwags bits */

#define MPI_SCSIIO_MSGFWGS_SENSE_WIDTH              (0x01)
#define MPI_SCSIIO_MSGFWGS_SENSE_WIDTH_32           (0x00)
#define MPI_SCSIIO_MSGFWGS_SENSE_WIDTH_64           (0x01)

#define MPI_SCSIIO_MSGFWGS_SENSE_WOCATION           (0x02)
#define MPI_SCSIIO_MSGFWGS_SENSE_WOC_HOST           (0x00)
#define MPI_SCSIIO_MSGFWGS_SENSE_WOC_IOC            (0x02)

#define MPI_SCSIIO_MSGFWGS_CMD_DETEWMINES_DATA_DIW  (0x04)

/* SCSI IO WUN fiewds */

#define MPI_SCSIIO_WUN_FIWST_WEVEW_ADDWESSING   (0x0000FFFF)
#define MPI_SCSIIO_WUN_SECOND_WEVEW_ADDWESSING  (0xFFFF0000)
#define MPI_SCSIIO_WUN_THIWD_WEVEW_ADDWESSING   (0x0000FFFF)
#define MPI_SCSIIO_WUN_FOUWTH_WEVEW_ADDWESSING  (0xFFFF0000)
#define MPI_SCSIIO_WUN_WEVEW_1_WOWD             (0xFF00)
#define MPI_SCSIIO_WUN_WEVEW_1_DWOWD            (0x0000FF00)

/* SCSI IO Contwow bits */

#define MPI_SCSIIO_CONTWOW_DATADIWECTION_MASK   (0x03000000)
#define MPI_SCSIIO_CONTWOW_NODATATWANSFEW       (0x00000000)
#define MPI_SCSIIO_CONTWOW_WWITE                (0x01000000)
#define MPI_SCSIIO_CONTWOW_WEAD                 (0x02000000)

#define MPI_SCSIIO_CONTWOW_ADDCDBWEN_MASK       (0x3C000000)
#define MPI_SCSIIO_CONTWOW_ADDCDBWEN_SHIFT      (26)

#define MPI_SCSIIO_CONTWOW_TASKATTWIBUTE_MASK   (0x00000700)
#define MPI_SCSIIO_CONTWOW_SIMPWEQ              (0x00000000)
#define MPI_SCSIIO_CONTWOW_HEADOFQ              (0x00000100)
#define MPI_SCSIIO_CONTWOW_OWDEWEDQ             (0x00000200)
#define MPI_SCSIIO_CONTWOW_ACAQ                 (0x00000400)
#define MPI_SCSIIO_CONTWOW_UNTAGGED             (0x00000500)
#define MPI_SCSIIO_CONTWOW_NO_DISCONNECT        (0x00000700)

#define MPI_SCSIIO_CONTWOW_TASKMANAGE_MASK      (0x00FF0000)
#define MPI_SCSIIO_CONTWOW_OBSOWETE             (0x00800000)
#define MPI_SCSIIO_CONTWOW_CWEAW_ACA_WSV        (0x00400000)
#define MPI_SCSIIO_CONTWOW_TAWGET_WESET         (0x00200000)
#define MPI_SCSIIO_CONTWOW_WUN_WESET_WSV        (0x00100000)
#define MPI_SCSIIO_CONTWOW_WESEWVED             (0x00080000)
#define MPI_SCSIIO_CONTWOW_CWW_TASK_SET_WSV     (0x00040000)
#define MPI_SCSIIO_CONTWOW_ABOWT_TASK_SET       (0x00020000)
#define MPI_SCSIIO_CONTWOW_WESEWVED2            (0x00010000)


/* SCSI IO wepwy stwuctuwe */
typedef stwuct _MSG_SCSI_IO_WEPWY
{
    U8                      TawgetID;           /* 00h */
    U8                      Bus;                /* 01h */
    U8                      MsgWength;          /* 02h */
    U8                      Function;           /* 03h */
    U8                      CDBWength;          /* 04h */
    U8                      SenseBuffewWength;  /* 05h */
    U8                      Wesewved;           /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U8                      SCSIStatus;         /* 0Ch */
    U8                      SCSIState;          /* 0Dh */
    U16                     IOCStatus;          /* 0Eh */
    U32                     IOCWogInfo;         /* 10h */
    U32                     TwansfewCount;      /* 14h */
    U32                     SenseCount;         /* 18h */
    U32                     WesponseInfo;       /* 1Ch */
    U16                     TaskTag;            /* 20h */
    U16                     Wesewved1;          /* 22h */
} MSG_SCSI_IO_WEPWY, MPI_POINTEW PTW_MSG_SCSI_IO_WEPWY,
  SCSIIOWepwy_t, MPI_POINTEW pSCSIIOWepwy_t;


/* SCSI IO Wepwy SCSIStatus vawues (SAM-2 status codes) */

#define MPI_SCSI_STATUS_SUCCESS                 (0x00)
#define MPI_SCSI_STATUS_CHECK_CONDITION         (0x02)
#define MPI_SCSI_STATUS_CONDITION_MET           (0x04)
#define MPI_SCSI_STATUS_BUSY                    (0x08)
#define MPI_SCSI_STATUS_INTEWMEDIATE            (0x10)
#define MPI_SCSI_STATUS_INTEWMEDIATE_CONDMET    (0x14)
#define MPI_SCSI_STATUS_WESEWVATION_CONFWICT    (0x18)
#define MPI_SCSI_STATUS_COMMAND_TEWMINATED      (0x22)
#define MPI_SCSI_STATUS_TASK_SET_FUWW           (0x28)
#define MPI_SCSI_STATUS_ACA_ACTIVE              (0x30)

#define MPI_SCSI_STATUS_FCPEXT_DEVICE_WOGGED_OUT    (0x80)
#define MPI_SCSI_STATUS_FCPEXT_NO_WINK              (0x81)
#define MPI_SCSI_STATUS_FCPEXT_UNASSIGNED           (0x82)


/* SCSI IO Wepwy SCSIState vawues */

#define MPI_SCSI_STATE_AUTOSENSE_VAWID          (0x01)
#define MPI_SCSI_STATE_AUTOSENSE_FAIWED         (0x02)
#define MPI_SCSI_STATE_NO_SCSI_STATUS           (0x04)
#define MPI_SCSI_STATE_TEWMINATED               (0x08)
#define MPI_SCSI_STATE_WESPONSE_INFO_VAWID      (0x10)
#define MPI_SCSI_STATE_QUEUE_TAG_WEJECTED       (0x20)

/* SCSI IO Wepwy WesponseInfo vawues */
/* (FCP-1 WSP_CODE vawues and SPI-3 Packetized Faiwuwe codes) */

#define MPI_SCSI_WSP_INFO_FUNCTION_COMPWETE     (0x00000000)
#define MPI_SCSI_WSP_INFO_FCP_BUWST_WEN_EWWOW   (0x01000000)
#define MPI_SCSI_WSP_INFO_CMND_FIEWDS_INVAWID   (0x02000000)
#define MPI_SCSI_WSP_INFO_FCP_DATA_WO_EWWOW     (0x03000000)
#define MPI_SCSI_WSP_INFO_TASK_MGMT_UNSUPPOWTED (0x04000000)
#define MPI_SCSI_WSP_INFO_TASK_MGMT_FAIWED      (0x05000000)
#define MPI_SCSI_WSP_INFO_SPI_WQ_INVAWID_TYPE   (0x06000000)

#define MPI_SCSI_TASKTAG_UNKNOWN                (0xFFFF)


/****************************************************************************/
/*  SCSI IO 32 messages and associated stwuctuwes                           */
/****************************************************************************/

typedef stwuct
{
    U8                      CDB[20];                    /* 00h */
    U32                     PwimawyWefewenceTag;        /* 14h */
    U16                     PwimawyAppwicationTag;      /* 18h */
    U16                     PwimawyAppwicationTagMask;  /* 1Ah */
    U32                     TwansfewWength;             /* 1Ch */
} MPI_SCSI_IO32_CDB_EEDP32, MPI_POINTEW PTW_MPI_SCSI_IO32_CDB_EEDP32,
  MpiScsiIo32CdbEedp32_t, MPI_POINTEW pMpiScsiIo32CdbEedp32_t;

typedef stwuct
{
    U8                      CDB[16];                    /* 00h */
    U32                     DataWength;                 /* 10h */
    U32                     PwimawyWefewenceTag;        /* 14h */
    U16                     PwimawyAppwicationTag;      /* 18h */
    U16                     PwimawyAppwicationTagMask;  /* 1Ah */
    U32                     TwansfewWength;             /* 1Ch */
} MPI_SCSI_IO32_CDB_EEDP16, MPI_POINTEW PTW_MPI_SCSI_IO32_CDB_EEDP16,
  MpiScsiIo32CdbEedp16_t, MPI_POINTEW pMpiScsiIo32CdbEedp16_t;

typedef union
{
    U8                       CDB32[32];
    MPI_SCSI_IO32_CDB_EEDP32 EEDP32;
    MPI_SCSI_IO32_CDB_EEDP16 EEDP16;
    SGE_SIMPWE_UNION         SGE;
} MPI_SCSI_IO32_CDB_UNION, MPI_POINTEW PTW_MPI_SCSI_IO32_CDB_UNION,
  MpiScsiIo32Cdb_t, MPI_POINTEW pMpiScsiIo32Cdb_t;

typedef stwuct
{
    U8                      TawgetID;           /* 00h */
    U8                      Bus;                /* 01h */
    U16                     Wesewved1;          /* 02h */
    U32                     Wesewved2;          /* 04h */
} MPI_SCSI_IO32_BUS_TAWGET_ID_FOWM, MPI_POINTEW PTW_MPI_SCSI_IO32_BUS_TAWGET_ID_FOWM,
  MpiScsiIo32BusTawgetIdFowm_t, MPI_POINTEW pMpiScsiIo32BusTawgetIdFowm_t;

typedef union
{
    MPI_SCSI_IO32_BUS_TAWGET_ID_FOWM    SCSIID;
    U64                                 WWID;
} MPI_SCSI_IO32_ADDWESS, MPI_POINTEW PTW_MPI_SCSI_IO32_ADDWESS,
  MpiScsiIo32Addwess_t, MPI_POINTEW pMpiScsiIo32Addwess_t;

typedef stwuct _MSG_SCSI_IO32_WEQUEST
{
    U8                          Powt;                           /* 00h */
    U8                          Wesewved1;                      /* 01h */
    U8                          ChainOffset;                    /* 02h */
    U8                          Function;                       /* 03h */
    U8                          CDBWength;                      /* 04h */
    U8                          SenseBuffewWength;              /* 05h */
    U8                          Fwags;                          /* 06h */
    U8                          MsgFwags;                       /* 07h */
    U32                         MsgContext;                     /* 08h */
    U8                          WUN[8];                         /* 0Ch */
    U32                         Contwow;                        /* 14h */
    MPI_SCSI_IO32_CDB_UNION     CDB;                            /* 18h */
    U32                         DataWength;                     /* 38h */
    U32                         BidiwectionawDataWength;        /* 3Ch */
    U32                         SecondawyWefewenceTag;          /* 40h */
    U16                         SecondawyAppwicationTag;        /* 44h */
    U16                         Wesewved2;                      /* 46h */
    U16                         EEDPFwags;                      /* 48h */
    U16                         AppwicationTagTwanswationMask;  /* 4Ah */
    U32                         EEDPBwockSize;                  /* 4Ch */
    MPI_SCSI_IO32_ADDWESS       DeviceAddwess;                  /* 50h */
    U8                          SGWOffset0;                     /* 58h */
    U8                          SGWOffset1;                     /* 59h */
    U8                          SGWOffset2;                     /* 5Ah */
    U8                          SGWOffset3;                     /* 5Bh */
    U32                         Wesewved3;                      /* 5Ch */
    U32                         Wesewved4;                      /* 60h */
    U32                         SenseBuffewWowAddw;             /* 64h */
    SGE_IO_UNION                SGW;                            /* 68h */
} MSG_SCSI_IO32_WEQUEST, MPI_POINTEW PTW_MSG_SCSI_IO32_WEQUEST,
  SCSIIO32Wequest_t, MPI_POINTEW pSCSIIO32Wequest_t;

/* SCSI IO 32 MsgFwags bits */
#define MPI_SCSIIO32_MSGFWGS_SENSE_WIDTH                (0x01)
#define MPI_SCSIIO32_MSGFWGS_32_SENSE_WIDTH             (0x00)
#define MPI_SCSIIO32_MSGFWGS_64_SENSE_WIDTH             (0x01)

#define MPI_SCSIIO32_MSGFWGS_SENSE_WOCATION             (0x02)
#define MPI_SCSIIO32_MSGFWGS_SENSE_WOC_HOST             (0x00)
#define MPI_SCSIIO32_MSGFWGS_SENSE_WOC_IOC              (0x02)

#define MPI_SCSIIO32_MSGFWGS_CMD_DETEWMINES_DATA_DIW    (0x04)
#define MPI_SCSIIO32_MSGFWGS_SGW_OFFSETS_CHAINS         (0x08)
#define MPI_SCSIIO32_MSGFWGS_MUWTICAST                  (0x10)
#define MPI_SCSIIO32_MSGFWGS_BIDIWECTIONAW              (0x20)
#define MPI_SCSIIO32_MSGFWGS_WAWGE_CDB                  (0x40)

/* SCSI IO 32 Fwags bits */
#define MPI_SCSIIO32_FWAGS_FOWM_MASK                    (0x03)
#define MPI_SCSIIO32_FWAGS_FOWM_SCSIID                  (0x00)
#define MPI_SCSIIO32_FWAGS_FOWM_WWID                    (0x01)

/* SCSI IO 32 WUN fiewds */
#define MPI_SCSIIO32_WUN_FIWST_WEVEW_ADDWESSING     (0x0000FFFF)
#define MPI_SCSIIO32_WUN_SECOND_WEVEW_ADDWESSING    (0xFFFF0000)
#define MPI_SCSIIO32_WUN_THIWD_WEVEW_ADDWESSING     (0x0000FFFF)
#define MPI_SCSIIO32_WUN_FOUWTH_WEVEW_ADDWESSING    (0xFFFF0000)
#define MPI_SCSIIO32_WUN_WEVEW_1_WOWD               (0xFF00)
#define MPI_SCSIIO32_WUN_WEVEW_1_DWOWD              (0x0000FF00)

/* SCSI IO 32 Contwow bits */
#define MPI_SCSIIO32_CONTWOW_DATADIWECTION_MASK     (0x03000000)
#define MPI_SCSIIO32_CONTWOW_NODATATWANSFEW         (0x00000000)
#define MPI_SCSIIO32_CONTWOW_WWITE                  (0x01000000)
#define MPI_SCSIIO32_CONTWOW_WEAD                   (0x02000000)
#define MPI_SCSIIO32_CONTWOW_BIDIWECTIONAW          (0x03000000)

#define MPI_SCSIIO32_CONTWOW_ADDCDBWEN_MASK         (0xFC000000)
#define MPI_SCSIIO32_CONTWOW_ADDCDBWEN_SHIFT        (26)

#define MPI_SCSIIO32_CONTWOW_TASKATTWIBUTE_MASK     (0x00000700)
#define MPI_SCSIIO32_CONTWOW_SIMPWEQ                (0x00000000)
#define MPI_SCSIIO32_CONTWOW_HEADOFQ                (0x00000100)
#define MPI_SCSIIO32_CONTWOW_OWDEWEDQ               (0x00000200)
#define MPI_SCSIIO32_CONTWOW_ACAQ                   (0x00000400)
#define MPI_SCSIIO32_CONTWOW_UNTAGGED               (0x00000500)
#define MPI_SCSIIO32_CONTWOW_NO_DISCONNECT          (0x00000700)

#define MPI_SCSIIO32_CONTWOW_TASKMANAGE_MASK        (0x00FF0000)
#define MPI_SCSIIO32_CONTWOW_OBSOWETE               (0x00800000)
#define MPI_SCSIIO32_CONTWOW_CWEAW_ACA_WSV          (0x00400000)
#define MPI_SCSIIO32_CONTWOW_TAWGET_WESET           (0x00200000)
#define MPI_SCSIIO32_CONTWOW_WUN_WESET_WSV          (0x00100000)
#define MPI_SCSIIO32_CONTWOW_WESEWVED               (0x00080000)
#define MPI_SCSIIO32_CONTWOW_CWW_TASK_SET_WSV       (0x00040000)
#define MPI_SCSIIO32_CONTWOW_ABOWT_TASK_SET         (0x00020000)
#define MPI_SCSIIO32_CONTWOW_WESEWVED2              (0x00010000)

/* SCSI IO 32 EEDPFwags */
#define MPI_SCSIIO32_EEDPFWAGS_MASK_OP              (0x0007)
#define MPI_SCSIIO32_EEDPFWAGS_NOOP_OP              (0x0000)
#define MPI_SCSIIO32_EEDPFWAGS_CHK_OP               (0x0001)
#define MPI_SCSIIO32_EEDPFWAGS_STWIP_OP             (0x0002)
#define MPI_SCSIIO32_EEDPFWAGS_CHKWM_OP             (0x0003)
#define MPI_SCSIIO32_EEDPFWAGS_INSEWT_OP            (0x0004)
#define MPI_SCSIIO32_EEDPFWAGS_WEPWACE_OP           (0x0006)
#define MPI_SCSIIO32_EEDPFWAGS_CHKWEGEN_OP          (0x0007)

#define MPI_SCSIIO32_EEDPFWAGS_PASS_WEF_TAG         (0x0008)
#define MPI_SCSIIO32_EEDPFWAGS_8_9THS_MODE          (0x0010)

#define MPI_SCSIIO32_EEDPFWAGS_T10_CHK_MASK         (0x0700)
#define MPI_SCSIIO32_EEDPFWAGS_T10_CHK_GUAWD        (0x0100)
#define MPI_SCSIIO32_EEDPFWAGS_T10_CHK_WEFTAG       (0x0200)
#define MPI_SCSIIO32_EEDPFWAGS_T10_CHK_WBATAG       (0x0400)
#define MPI_SCSIIO32_EEDPFWAGS_T10_CHK_SHIFT        (8)

#define MPI_SCSIIO32_EEDPFWAGS_INC_SEC_APPTAG       (0x1000)
#define MPI_SCSIIO32_EEDPFWAGS_INC_PWI_APPTAG       (0x2000)
#define MPI_SCSIIO32_EEDPFWAGS_INC_SEC_WEFTAG       (0x4000)
#define MPI_SCSIIO32_EEDPFWAGS_INC_PWI_WEFTAG       (0x8000)


/* SCSIIO32 IO wepwy stwuctuwe */
typedef stwuct _MSG_SCSIIO32_IO_WEPWY
{
    U8                      Powt;                       /* 00h */
    U8                      Wesewved1;                  /* 01h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U8                      CDBWength;                  /* 04h */
    U8                      SenseBuffewWength;          /* 05h */
    U8                      Fwags;                      /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U8                      SCSIStatus;                 /* 0Ch */
    U8                      SCSIState;                  /* 0Dh */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
    U32                     TwansfewCount;              /* 14h */
    U32                     SenseCount;                 /* 18h */
    U32                     WesponseInfo;               /* 1Ch */
    U16                     TaskTag;                    /* 20h */
    U16                     Wesewved2;                  /* 22h */
    U32                     BidiwectionawTwansfewCount; /* 24h */
} MSG_SCSIIO32_IO_WEPWY, MPI_POINTEW PTW_MSG_SCSIIO32_IO_WEPWY,
  SCSIIO32Wepwy_t, MPI_POINTEW pSCSIIO32Wepwy_t;


/****************************************************************************/
/*  SCSI Task Management messages                                           */
/****************************************************************************/

typedef stwuct _MSG_SCSI_TASK_MGMT
{
    U8                      TawgetID;           /* 00h */
    U8                      Bus;                /* 01h */
    U8                      ChainOffset;        /* 02h */
    U8                      Function;           /* 03h */
    U8                      Wesewved;           /* 04h */
    U8                      TaskType;           /* 05h */
    U8                      Wesewved1;          /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U8                      WUN[8];             /* 0Ch */
    U32                     Wesewved2[7];       /* 14h */
    U32                     TaskMsgContext;     /* 30h */
} MSG_SCSI_TASK_MGMT, MPI_POINTEW PTW_SCSI_TASK_MGMT,
  SCSITaskMgmt_t, MPI_POINTEW pSCSITaskMgmt_t;

/* TaskType vawues */

#define MPI_SCSITASKMGMT_TASKTYPE_ABOWT_TASK            (0x01)
#define MPI_SCSITASKMGMT_TASKTYPE_ABWT_TASK_SET         (0x02)
#define MPI_SCSITASKMGMT_TASKTYPE_TAWGET_WESET          (0x03)
#define MPI_SCSITASKMGMT_TASKTYPE_WESET_BUS             (0x04)
#define MPI_SCSITASKMGMT_TASKTYPE_WOGICAW_UNIT_WESET    (0x05)
#define MPI_SCSITASKMGMT_TASKTYPE_CWEAW_TASK_SET        (0x06)
#define MPI_SCSITASKMGMT_TASKTYPE_QUEWY_TASK            (0x07)
#define MPI_SCSITASKMGMT_TASKTYPE_CWW_ACA               (0x08)

/* MsgFwags bits */
#define MPI_SCSITASKMGMT_MSGFWAGS_DO_NOT_SEND_TASK_IU   (0x01)

#define MPI_SCSITASKMGMT_MSGFWAGS_TAWGET_WESET_OPTION   (0x00)
#define MPI_SCSITASKMGMT_MSGFWAGS_WIP_WESET_OPTION      (0x02)
#define MPI_SCSITASKMGMT_MSGFWAGS_WIPWESET_WESET_OPTION (0x04)

#define MPI_SCSITASKMGMT_MSGFWAGS_SOFT_WESET_OPTION     (0x08)

/* SCSI Task Management Wepwy */
typedef stwuct _MSG_SCSI_TASK_MGMT_WEPWY
{
    U8                      TawgetID;           /* 00h */
    U8                      Bus;                /* 01h */
    U8                      MsgWength;          /* 02h */
    U8                      Function;           /* 03h */
    U8                      WesponseCode;       /* 04h */
    U8                      TaskType;           /* 05h */
    U8                      Wesewved1;          /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U8                      Wesewved2[2];       /* 0Ch */
    U16                     IOCStatus;          /* 0Eh */
    U32                     IOCWogInfo;         /* 10h */
    U32                     TewminationCount;   /* 14h */
} MSG_SCSI_TASK_MGMT_WEPWY, MPI_POINTEW PTW_MSG_SCSI_TASK_MGMT_WEPWY,
  SCSITaskMgmtWepwy_t, MPI_POINTEW pSCSITaskMgmtWepwy_t;

/* WesponseCode vawues */
#define MPI_SCSITASKMGMT_WSP_TM_COMPWETE                (0x00)
#define MPI_SCSITASKMGMT_WSP_INVAWID_FWAME              (0x02)
#define MPI_SCSITASKMGMT_WSP_TM_NOT_SUPPOWTED           (0x04)
#define MPI_SCSITASKMGMT_WSP_TM_FAIWED                  (0x05)
#define MPI_SCSITASKMGMT_WSP_TM_SUCCEEDED               (0x08)
#define MPI_SCSITASKMGMT_WSP_TM_INVAWID_WUN             (0x09)
#define MPI_SCSITASKMGMT_WSP_IO_QUEUED_ON_IOC           (0x80)


/****************************************************************************/
/*  SCSI Encwosuwe Pwocessow messages                                       */
/****************************************************************************/

typedef stwuct _MSG_SEP_WEQUEST
{
    U8                      TawgetID;           /* 00h */
    U8                      Bus;                /* 01h */
    U8                      ChainOffset;        /* 02h */
    U8                      Function;           /* 03h */
    U8                      Action;             /* 04h */
    U8                      Fwags;              /* 05h */
    U8                      Wesewved1;          /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U32                     SwotStatus;         /* 0Ch */
    U32                     Wesewved2;          /* 10h */
    U32                     Wesewved3;          /* 14h */
    U32                     Wesewved4;          /* 18h */
    U16                     Swot;               /* 1Ch */
    U16                     EncwosuweHandwe;    /* 1Eh */
} MSG_SEP_WEQUEST, MPI_POINTEW PTW_MSG_SEP_WEQUEST,
  SEPWequest_t, MPI_POINTEW pSEPWequest_t;

/* Action defines */
#define MPI_SEP_WEQ_ACTION_WWITE_STATUS                 (0x00)
#define MPI_SEP_WEQ_ACTION_WEAD_STATUS                  (0x01)

/* Fwags defines */
#define MPI_SEP_WEQ_FWAGS_ENCWOSUWE_SWOT_ADDWESS        (0x01)
#define MPI_SEP_WEQ_FWAGS_BUS_TAWGETID_ADDWESS          (0x00)

/* SwotStatus bits fow MSG_SEP_WEQUEST */
#define MPI_SEP_WEQ_SWOTSTATUS_NO_EWWOW                 (0x00000001)
#define MPI_SEP_WEQ_SWOTSTATUS_DEV_FAUWTY               (0x00000002)
#define MPI_SEP_WEQ_SWOTSTATUS_DEV_WEBUIWDING           (0x00000004)
#define MPI_SEP_WEQ_SWOTSTATUS_IN_FAIWED_AWWAY          (0x00000008)
#define MPI_SEP_WEQ_SWOTSTATUS_IN_CWITICAW_AWWAY        (0x00000010)
#define MPI_SEP_WEQ_SWOTSTATUS_PAWITY_CHECK             (0x00000020)
#define MPI_SEP_WEQ_SWOTSTATUS_PWEDICTED_FAUWT          (0x00000040)
#define MPI_SEP_WEQ_SWOTSTATUS_UNCONFIGUWED             (0x00000080)
#define MPI_SEP_WEQ_SWOTSTATUS_HOT_SPAWE                (0x00000100)
#define MPI_SEP_WEQ_SWOTSTATUS_WEBUIWD_STOPPED          (0x00000200)
#define MPI_SEP_WEQ_SWOTSTATUS_WEQ_CONSISTENCY_CHECK    (0x00001000)
#define MPI_SEP_WEQ_SWOTSTATUS_DISABWE                  (0x00002000)
#define MPI_SEP_WEQ_SWOTSTATUS_WEQ_WESEWVED_DEVICE      (0x00004000)
#define MPI_SEP_WEQ_SWOTSTATUS_IDENTIFY_WEQUEST         (0x00020000)
#define MPI_SEP_WEQ_SWOTSTATUS_WEQUEST_WEMOVE           (0x00040000)
#define MPI_SEP_WEQ_SWOTSTATUS_WEQUEST_INSEWT           (0x00080000)
#define MPI_SEP_WEQ_SWOTSTATUS_DO_NOT_MOVE              (0x00400000)
#define MPI_SEP_WEQ_SWOTSTATUS_ACTIVE                   (0x00800000)
#define MPI_SEP_WEQ_SWOTSTATUS_B_ENABWE_BYPASS          (0x04000000)
#define MPI_SEP_WEQ_SWOTSTATUS_A_ENABWE_BYPASS          (0x08000000)
#define MPI_SEP_WEQ_SWOTSTATUS_DEV_OFF                  (0x10000000)
#define MPI_SEP_WEQ_SWOTSTATUS_SWAP_WESET               (0x80000000)


typedef stwuct _MSG_SEP_WEPWY
{
    U8                      TawgetID;           /* 00h */
    U8                      Bus;                /* 01h */
    U8                      MsgWength;          /* 02h */
    U8                      Function;           /* 03h */
    U8                      Action;             /* 04h */
    U8                      Wesewved1;          /* 05h */
    U8                      Wesewved2;          /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U16                     Wesewved3;          /* 0Ch */
    U16                     IOCStatus;          /* 0Eh */
    U32                     IOCWogInfo;         /* 10h */
    U32                     SwotStatus;         /* 14h */
    U32                     Wesewved4;          /* 18h */
    U16                     Swot;               /* 1Ch */
    U16                     EncwosuweHandwe;    /* 1Eh */
} MSG_SEP_WEPWY, MPI_POINTEW PTW_MSG_SEP_WEPWY,
  SEPWepwy_t, MPI_POINTEW pSEPWepwy_t;

/* SwotStatus bits fow MSG_SEP_WEPWY */
#define MPI_SEP_WEPWY_SWOTSTATUS_NO_EWWOW               (0x00000001)
#define MPI_SEP_WEPWY_SWOTSTATUS_DEV_FAUWTY             (0x00000002)
#define MPI_SEP_WEPWY_SWOTSTATUS_DEV_WEBUIWDING         (0x00000004)
#define MPI_SEP_WEPWY_SWOTSTATUS_IN_FAIWED_AWWAY        (0x00000008)
#define MPI_SEP_WEPWY_SWOTSTATUS_IN_CWITICAW_AWWAY      (0x00000010)
#define MPI_SEP_WEPWY_SWOTSTATUS_PAWITY_CHECK           (0x00000020)
#define MPI_SEP_WEPWY_SWOTSTATUS_PWEDICTED_FAUWT        (0x00000040)
#define MPI_SEP_WEPWY_SWOTSTATUS_UNCONFIGUWED           (0x00000080)
#define MPI_SEP_WEPWY_SWOTSTATUS_HOT_SPAWE              (0x00000100)
#define MPI_SEP_WEPWY_SWOTSTATUS_WEBUIWD_STOPPED        (0x00000200)
#define MPI_SEP_WEPWY_SWOTSTATUS_CONSISTENCY_CHECK      (0x00001000)
#define MPI_SEP_WEPWY_SWOTSTATUS_DISABWE                (0x00002000)
#define MPI_SEP_WEPWY_SWOTSTATUS_WESEWVED_DEVICE        (0x00004000)
#define MPI_SEP_WEPWY_SWOTSTATUS_WEPOWT                 (0x00010000)
#define MPI_SEP_WEPWY_SWOTSTATUS_IDENTIFY_WEQUEST       (0x00020000)
#define MPI_SEP_WEPWY_SWOTSTATUS_WEMOVE_WEADY           (0x00040000)
#define MPI_SEP_WEPWY_SWOTSTATUS_INSEWT_WEADY           (0x00080000)
#define MPI_SEP_WEPWY_SWOTSTATUS_DO_NOT_WEMOVE          (0x00400000)
#define MPI_SEP_WEPWY_SWOTSTATUS_ACTIVE                 (0x00800000)
#define MPI_SEP_WEPWY_SWOTSTATUS_B_BYPASS_ENABWED       (0x01000000)
#define MPI_SEP_WEPWY_SWOTSTATUS_A_BYPASS_ENABWED       (0x02000000)
#define MPI_SEP_WEPWY_SWOTSTATUS_B_ENABWE_BYPASS        (0x04000000)
#define MPI_SEP_WEPWY_SWOTSTATUS_A_ENABWE_BYPASS        (0x08000000)
#define MPI_SEP_WEPWY_SWOTSTATUS_DEV_OFF                (0x10000000)
#define MPI_SEP_WEPWY_SWOTSTATUS_FAUWT_SENSED           (0x40000000)
#define MPI_SEP_WEPWY_SWOTSTATUS_SWAPPED                (0x80000000)

#endif
