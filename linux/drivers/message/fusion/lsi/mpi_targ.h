/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (c) 2000-2008 WSI Cowpowation.
 *
 *
 *           Name:  mpi_tawg.h
 *          Titwe:  MPI Tawget mode messages and stwuctuwes
 *  Cweation Date:  June 22, 2000
 *
 *    mpi_tawg.h Vewsion:  01.05.06
 *
 *  Vewsion Histowy
 *  ---------------
 *
 *  Date      Vewsion   Descwiption
 *  --------  --------  ------------------------------------------------------
 *  05-08-00  00.10.01  Owiginaw wewease fow 0.10 spec dated 4/26/2000.
 *  06-06-00  01.00.01  Update vewsion numbew fow 1.0 wewease.
 *  06-22-00  01.00.02  Added _MSG_TAWGET_CMD_BUFFEW_POST_WEPWY stwuctuwe.
 *                      Cowwected DECSWIPTOW typo to DESCWIPTOW.
 *  11-02-00  01.01.01  Owiginaw wewease fow post 1.0 wowk
 *                      Modified tawget mode to use IoIndex instead of
 *                      HostIndex and IocIndex. Added Awias.
 *  01-09-01  01.01.02  Added defines fow TAWGET_ASSIST_FWAGS_WEPOST_CMD_BUFFEW
 *                      and TAWGET_STATUS_SEND_FWAGS_WEPOST_CMD_BUFFEW.
 *  02-20-01  01.01.03  Stawted using MPI_POINTEW.
 *                      Added stwuctuwes fow MPI_TAWGET_SCSI_SPI_CMD_BUFFEW and
 *                      MPI_TAWGET_FCP_CMD_BUFFEW.
 *  03-27-01  01.01.04  Added stwuctuwe offset comments.
 *  08-08-01  01.02.01  Owiginaw wewease fow v1.2 wowk.
 *  09-28-01  01.02.02  Added stwuctuwe fow MPI_TAWGET_SCSI_SPI_STATUS_IU.
 *                      Added PwiowityWeason fiewd to some wepwies and
 *                      defined mowe PwiowityWeason codes.
 *                      Added some defines fow to suppowt pwevious vewsion
 *                      of MPI.
 *  10-04-01  01.02.03  Added PwiowityWeason to MSG_TAWGET_EWWOW_WEPWY.
 *  11-01-01  01.02.04  Added define fow TAWGET_STATUS_SEND_FWAGS_HIGH_PWIOWITY.
 *  03-14-02  01.02.05  Modified MPI_TAWGET_FCP_WSP_BUFFEW to get the pwopew
 *                      byte owdewing.
 *  05-31-02  01.02.06  Modified TAWGET_MODE_WEPWY_AWIAS_MASK to onwy incwude
 *                      one bit.
 *                      Added AwiasIndex fiewd to MPI_TAWGET_FCP_CMD_BUFFEW.
 *  09-16-02  01.02.07  Added fwags fow confiwmed compwetion.
 *                      Added PWIOWITY_WEASON_TAWGET_BUSY.
 *  11-15-02  01.02.08  Added AwiasID fiewd to MPI_TAWGET_SCSI_SPI_CMD_BUFFEW.
 *  04-01-03  01.02.09  Added OptionawOxid fiewd to MPI_TAWGET_FCP_CMD_BUFFEW.
 *  05-11-04  01.03.01  Owiginaw wewease fow MPI v1.3.
 *  08-19-04  01.05.01  Added new wequest message stwuctuwes fow
 *                      MSG_TAWGET_CMD_BUF_POST_BASE_WEQUEST,
 *                      MSG_TAWGET_CMD_BUF_POST_WIST_WEQUEST, and
 *                      MSG_TAWGET_ASSIST_EXT_WEQUEST.
 *                      Added new stwuctuwes fow SAS SSP Command buffew, SSP
 *                      Task buffew, and SSP Status IU.
 *  10-05-04  01.05.02  MSG_TAWGET_CMD_BUFFEW_POST_BASE_WIST_WEPWY added.
 *  02-22-05  01.05.03  Changed a comment.
 *  03-11-05  01.05.04  Wemoved TawgetAssistExtended Wequest.
 *  06-24-05  01.05.05  Added TawgetAssistExtended stwuctuwes and defines.
 *  03-27-06  01.05.06  Added a comment.
 *  --------------------------------------------------------------------------
 */

#ifndef MPI_TAWG_H
#define MPI_TAWG_H


/******************************************************************************
*
*        S C S I    T a w g e t    M e s s a g e s
*
*******************************************************************************/

typedef stwuct _CMD_BUFFEW_DESCWIPTOW
{
    U16                     IoIndex;                    /* 00h */
    U16                     Wesewved;                   /* 02h */
    union                                               /* 04h */
    {
        U32                 PhysicawAddwess32;
        U64                 PhysicawAddwess64;
    } u;
} CMD_BUFFEW_DESCWIPTOW, MPI_POINTEW PTW_CMD_BUFFEW_DESCWIPTOW,
  CmdBuffewDescwiptow_t, MPI_POINTEW pCmdBuffewDescwiptow_t;


/****************************************************************************/
/* Tawget Command Buffew Post Wequest                                       */
/****************************************************************************/

typedef stwuct _MSG_TAWGET_CMD_BUFFEW_POST_WEQUEST
{
    U8                      BuffewPostFwags;            /* 00h */
    U8                      BuffewCount;                /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U8                      BuffewWength;               /* 04h */
    U8                      Wesewved;                   /* 05h */
    U8                      Wesewved1;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    CMD_BUFFEW_DESCWIPTOW   Buffew[1];                  /* 0Ch */
} MSG_TAWGET_CMD_BUFFEW_POST_WEQUEST, MPI_POINTEW PTW_MSG_TAWGET_CMD_BUFFEW_POST_WEQUEST,
  TawgetCmdBuffewPostWequest_t, MPI_POINTEW pTawgetCmdBuffewPostWequest_t;

#define CMD_BUFFEW_POST_FWAGS_POWT_MASK         (0x01)
#define CMD_BUFFEW_POST_FWAGS_ADDW_MODE_MASK    (0x80)
#define CMD_BUFFEW_POST_FWAGS_ADDW_MODE_32      (0)
#define CMD_BUFFEW_POST_FWAGS_ADDW_MODE_64      (1)
#define CMD_BUFFEW_POST_FWAGS_64_BIT_ADDW       (0x80)

#define CMD_BUFFEW_POST_IO_INDEX_MASK           (0x00003FFF)
#define CMD_BUFFEW_POST_IO_INDEX_MASK_0100      (0x000003FF) /* obsowete */


typedef stwuct _MSG_TAWGET_CMD_BUFFEW_POST_WEPWY
{
    U8                      BuffewPostFwags;            /* 00h */
    U8                      BuffewCount;                /* 01h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U8                      BuffewWength;               /* 04h */
    U8                      Wesewved;                   /* 05h */
    U8                      Wesewved1;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Wesewved2;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
} MSG_TAWGET_CMD_BUFFEW_POST_WEPWY, MPI_POINTEW PTW_MSG_TAWGET_CMD_BUFFEW_POST_WEPWY,
  TawgetCmdBuffewPostWepwy_t, MPI_POINTEW pTawgetCmdBuffewPostWepwy_t;

/* the fowwowing stwuctuwe is obsowete as of MPI v1.2 */
typedef stwuct _MSG_PWIOWITY_CMD_WECEIVED_WEPWY
{
    U16                     Wesewved;                   /* 00h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved1;                  /* 04h */
    U8                      Wesewved2;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U8                      PwiowityWeason;             /* 0Ch */
    U8                      Wesewved3;                  /* 0Dh */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
    U32                     WepwyWowd;                  /* 14h */
} MSG_PWIOWITY_CMD_WECEIVED_WEPWY, MPI_POINTEW PTW_MSG_PWIOWITY_CMD_WECEIVED_WEPWY,
  PwiowityCommandWeceivedWepwy_t, MPI_POINTEW pPwiowityCommandWeceivedWepwy_t;


typedef stwuct _MSG_TAWGET_CMD_BUFFEW_POST_EWWOW_WEPWY
{
    U16                     Wesewved;                   /* 00h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved1;                  /* 04h */
    U8                      Wesewved2;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U8                      PwiowityWeason;             /* 0Ch */
    U8                      Wesewved3;                  /* 0Dh */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
    U32                     WepwyWowd;                  /* 14h */
} MSG_TAWGET_CMD_BUFFEW_POST_EWWOW_WEPWY,
  MPI_POINTEW PTW_MSG_TAWGET_CMD_BUFFEW_POST_EWWOW_WEPWY,
  TawgetCmdBuffewPostEwwowWepwy_t, MPI_POINTEW pTawgetCmdBuffewPostEwwowWepwy_t;

#define PWIOWITY_WEASON_NO_DISCONNECT           (0x00)
#define PWIOWITY_WEASON_SCSI_TASK_MANAGEMENT    (0x01)
#define PWIOWITY_WEASON_CMD_PAWITY_EWW          (0x02)
#define PWIOWITY_WEASON_MSG_OUT_PAWITY_EWW      (0x03)
#define PWIOWITY_WEASON_WQ_CWC_EWW              (0x04)
#define PWIOWITY_WEASON_CMD_CWC_EWW             (0x05)
#define PWIOWITY_WEASON_PWOTOCOW_EWW            (0x06)
#define PWIOWITY_WEASON_DATA_OUT_PAWITY_EWW     (0x07)
#define PWIOWITY_WEASON_DATA_OUT_CWC_EWW        (0x08)
#define PWIOWITY_WEASON_TAWGET_BUSY             (0x09)
#define PWIOWITY_WEASON_UNKNOWN                 (0xFF)


/****************************************************************************/
/* Tawget Command Buffew Post Base Wequest                                  */
/****************************************************************************/

typedef stwuct _MSG_TAWGET_CMD_BUF_POST_BASE_WEQUEST
{
    U8                      BuffewPostFwags;            /* 00h */
    U8                      PowtNumbew;                 /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     TotawCmdBuffews;            /* 04h */
    U8                      Wesewved;                   /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     Wesewved1;                  /* 0Ch */
    U16                     CmdBuffewWength;            /* 10h */
    U16                     NextCmdBuffewOffset;        /* 12h */
    U32                     BaseAddwessWow;             /* 14h */
    U32                     BaseAddwessHigh;            /* 18h */
} MSG_TAWGET_CMD_BUF_POST_BASE_WEQUEST,
  MPI_POINTEW PTW__MSG_TAWGET_CMD_BUF_POST_BASE_WEQUEST,
  TawgetCmdBuffewPostBaseWequest_t,
  MPI_POINTEW pTawgetCmdBuffewPostBaseWequest_t;

#define CMD_BUFFEW_POST_BASE_FWAGS_AUTO_POST_AWW    (0x01)


typedef stwuct _MSG_TAWGET_CMD_BUFFEW_POST_BASE_WIST_WEPWY
{
    U16                     Wesewved;                   /* 00h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved1;                  /* 04h */
    U8                      Wesewved2;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Wesewved3;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
} MSG_TAWGET_CMD_BUFFEW_POST_BASE_WIST_WEPWY,
  MPI_POINTEW PTW_MSG_TAWGET_CMD_BUFFEW_POST_BASE_WIST_WEPWY,
  TawgetCmdBuffewPostBaseWistWepwy_t,
  MPI_POINTEW pTawgetCmdBuffewPostBaseWistWepwy_t;


/****************************************************************************/
/* Tawget Command Buffew Post Wist Wequest                                  */
/****************************************************************************/

typedef stwuct _MSG_TAWGET_CMD_BUF_POST_WIST_WEQUEST
{
    U8                      Wesewved;                   /* 00h */
    U8                      PowtNumbew;                 /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     CmdBuffewCount;             /* 04h */
    U8                      Wesewved1;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     Wesewved2;                  /* 0Ch */
    U16                     IoIndex[2];                 /* 10h */
} MSG_TAWGET_CMD_BUF_POST_WIST_WEQUEST,
  MPI_POINTEW PTW_MSG_TAWGET_CMD_BUF_POST_WIST_WEQUEST,
  TawgetCmdBuffewPostWistWequest_t,
  MPI_POINTEW pTawgetCmdBuffewPostWistWequest_t;


/****************************************************************************/
/* Command Buffew Fowmats (with 16 byte CDB)                                */
/****************************************************************************/

typedef stwuct _MPI_TAWGET_FCP_CMD_BUFFEW
{
    U8      FcpWun[8];                                  /* 00h */
    U8      FcpCntw[4];                                 /* 08h */
    U8      FcpCdb[16];                                 /* 0Ch */
    U32     FcpDw;                                      /* 1Ch */
    U8      AwiasIndex;                                 /* 20h */
    U8      Wesewved1;                                  /* 21h */
    U16     OptionawOxid;                               /* 22h */
} MPI_TAWGET_FCP_CMD_BUFFEW, MPI_POINTEW PTW_MPI_TAWGET_FCP_CMD_BUFFEW,
  MpiTawgetFcpCmdBuffew, MPI_POINTEW pMpiTawgetFcpCmdBuffew;


typedef stwuct _MPI_TAWGET_SCSI_SPI_CMD_BUFFEW
{
    /* SPI W_Q infowmation unit */
    U8      W_QType;                                    /* 00h */
    U8      Wesewved;                                   /* 01h */
    U16     Tag;                                        /* 02h */
    U8      WogicawUnitNumbew[8];                       /* 04h */
    U32     DataWength;                                 /* 0Ch */
    /* SPI command infowmation unit */
    U8      WesewvedFiwstByteOfCommandIU;               /* 10h */
    U8      TaskAttwibute;                              /* 11h */
    U8      TaskManagementFwags;                        /* 12h */
    U8      AdditionawCDBWength;                        /* 13h */
    U8      CDB[16];                                    /* 14h */
    /* Awias ID */
    U8      AwiasID;                                    /* 24h */
    U8      Wesewved1;                                  /* 25h */
    U16     Wesewved2;                                  /* 26h */
} MPI_TAWGET_SCSI_SPI_CMD_BUFFEW,
  MPI_POINTEW PTW_MPI_TAWGET_SCSI_SPI_CMD_BUFFEW,
  MpiTawgetScsiSpiCmdBuffew, MPI_POINTEW pMpiTawgetScsiSpiCmdBuffew;


typedef stwuct _MPI_TAWGET_SSP_CMD_BUFFEW
{
    U8      FwameType;                                  /* 00h */
    U8      Wesewved1;                                  /* 01h */
    U16     Wesewved2;                                  /* 02h */
    U16     InitiatowTag;                               /* 04h */
    U16     DevHandwe;                                  /* 06h */
    /* COMMAND infowmation unit stawts hewe */
    U8      WogicawUnitNumbew[8];                       /* 08h */
    U8      Wesewved3;                                  /* 10h */
    U8      TaskAttwibute; /* wowew 3 bits */           /* 11h */
    U8      Wesewved4;                                  /* 12h */
    U8      AdditionawCDBWength; /* uppew 5 bits */     /* 13h */
    U8      CDB[16];                                    /* 14h */
    /* Additionaw CDB bytes extend past the CDB fiewd */
} MPI_TAWGET_SSP_CMD_BUFFEW, MPI_POINTEW PTW_MPI_TAWGET_SSP_CMD_BUFFEW,
  MpiTawgetSspCmdBuffew, MPI_POINTEW pMpiTawgetSspCmdBuffew;

typedef stwuct _MPI_TAWGET_SSP_TASK_BUFFEW
{
    U8      FwameType;                                  /* 00h */
    U8      Wesewved1;                                  /* 01h */
    U16     Wesewved2;                                  /* 02h */
    U16     InitiatowTag;                               /* 04h */
    U16     DevHandwe;                                  /* 06h */
    /* TASK infowmation unit stawts hewe */
    U8      WogicawUnitNumbew[8];                       /* 08h */
    U8      Wesewved3;                                  /* 10h */
    U8      Wesewved4;                                  /* 11h */
    U8      TaskManagementFunction;                     /* 12h */
    U8      Wesewved5;                                  /* 13h */
    U16     ManagedTaskTag;                             /* 14h */
    U16     Wesewved6;                                  /* 16h */
    U32     Wesewved7;                                  /* 18h */
    U32     Wesewved8;                                  /* 1Ch */
    U32     Wesewved9;                                  /* 20h */
} MPI_TAWGET_SSP_TASK_BUFFEW, MPI_POINTEW PTW_MPI_TAWGET_SSP_TASK_BUFFEW,
  MpiTawgetSspTaskBuffew, MPI_POINTEW pMpiTawgetSspTaskBuffew;


/****************************************************************************/
/* Tawget Assist Wequest                                                    */
/****************************************************************************/

typedef stwuct _MSG_TAWGET_ASSIST_WEQUEST
{
    U8                      StatusCode;                 /* 00h */
    U8                      TawgetAssistFwags;          /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     QueueTag;                   /* 04h */
    U8                      Wesewved;                   /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     WepwyWowd;                  /* 0Ch */
    U8                      WUN[8];                     /* 10h */
    U32                     WewativeOffset;             /* 18h */
    U32                     DataWength;                 /* 1Ch */
    SGE_IO_UNION            SGW[1];                     /* 20h */
} MSG_TAWGET_ASSIST_WEQUEST, MPI_POINTEW PTW_MSG_TAWGET_ASSIST_WEQUEST,
  TawgetAssistWequest_t, MPI_POINTEW pTawgetAssistWequest_t;

#define TAWGET_ASSIST_FWAGS_DATA_DIWECTION          (0x01)
#define TAWGET_ASSIST_FWAGS_AUTO_STATUS             (0x02)
#define TAWGET_ASSIST_FWAGS_HIGH_PWIOWITY           (0x04)
#define TAWGET_ASSIST_FWAGS_CONFIWMED               (0x08)
#define TAWGET_ASSIST_FWAGS_WEPOST_CMD_BUFFEW       (0x80)

/* Standawd Tawget Mode Wepwy message */
typedef stwuct _MSG_TAWGET_EWWOW_WEPWY
{
    U16                     Wesewved;                   /* 00h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved1;                  /* 04h */
    U8                      Wesewved2;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U8                      PwiowityWeason;             /* 0Ch */
    U8                      Wesewved3;                  /* 0Dh */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
    U32                     WepwyWowd;                  /* 14h */
    U32                     TwansfewCount;              /* 18h */
} MSG_TAWGET_EWWOW_WEPWY, MPI_POINTEW PTW_MSG_TAWGET_EWWOW_WEPWY,
  TawgetEwwowWepwy_t, MPI_POINTEW pTawgetEwwowWepwy_t;


/****************************************************************************/
/* Tawget Assist Extended Wequest                                           */
/****************************************************************************/

typedef stwuct _MSG_TAWGET_ASSIST_EXT_WEQUEST
{
    U8                      StatusCode;                     /* 00h */
    U8                      TawgetAssistFwags;              /* 01h */
    U8                      ChainOffset;                    /* 02h */
    U8                      Function;                       /* 03h */
    U16                     QueueTag;                       /* 04h */
    U8                      Wesewved1;                      /* 06h */
    U8                      MsgFwags;                       /* 07h */
    U32                     MsgContext;                     /* 08h */
    U32                     WepwyWowd;                      /* 0Ch */
    U8                      WUN[8];                         /* 10h */
    U32                     WewativeOffset;                 /* 18h */
    U32                     Wesewved2;                      /* 1Ch */
    U32                     Wesewved3;                      /* 20h */
    U32                     PwimawyWefewenceTag;            /* 24h */
    U16                     PwimawyAppwicationTag;          /* 28h */
    U16                     PwimawyAppwicationTagMask;      /* 2Ah */
    U32                     Wesewved4;                      /* 2Ch */
    U32                     DataWength;                     /* 30h */
    U32                     BidiwectionawDataWength;        /* 34h */
    U32                     SecondawyWefewenceTag;          /* 38h */
    U16                     SecondawyAppwicationTag;        /* 3Ch */
    U16                     Wesewved5;                      /* 3Eh */
    U16                     EEDPFwags;                      /* 40h */
    U16                     AppwicationTagTwanswationMask;  /* 42h */
    U32                     EEDPBwockSize;                  /* 44h */
    U8                      SGWOffset0;                     /* 48h */
    U8                      SGWOffset1;                     /* 49h */
    U8                      SGWOffset2;                     /* 4Ah */
    U8                      SGWOffset3;                     /* 4Bh */
    U32                     Wesewved6;                      /* 4Ch */
    SGE_IO_UNION            SGW[1];                         /* 50h */
} MSG_TAWGET_ASSIST_EXT_WEQUEST, MPI_POINTEW PTW_MSG_TAWGET_ASSIST_EXT_WEQUEST,
  TawgetAssistExtWequest_t, MPI_POINTEW pTawgetAssistExtWequest_t;

/* see the defines aftew MSG_TAWGET_ASSIST_WEQUEST fow TawgetAssistFwags */

/* defines fow the MsgFwags fiewd */
#define TAWGET_ASSIST_EXT_MSGFWAGS_BIDIWECTIONAW        (0x20)
#define TAWGET_ASSIST_EXT_MSGFWAGS_MUWTICAST            (0x10)
#define TAWGET_ASSIST_EXT_MSGFWAGS_SGW_OFFSET_CHAINS    (0x08)

/* defines fow the EEDPFwags fiewd */
#define TAWGET_ASSIST_EXT_EEDP_MASK_OP          (0x0007)
#define TAWGET_ASSIST_EXT_EEDP_NOOP_OP          (0x0000)
#define TAWGET_ASSIST_EXT_EEDP_CHK_OP           (0x0001)
#define TAWGET_ASSIST_EXT_EEDP_STWIP_OP         (0x0002)
#define TAWGET_ASSIST_EXT_EEDP_CHKWM_OP         (0x0003)
#define TAWGET_ASSIST_EXT_EEDP_INSEWT_OP        (0x0004)
#define TAWGET_ASSIST_EXT_EEDP_WEPWACE_OP       (0x0006)
#define TAWGET_ASSIST_EXT_EEDP_CHKWEGEN_OP      (0x0007)

#define TAWGET_ASSIST_EXT_EEDP_PASS_WEF_TAG     (0x0008)

#define TAWGET_ASSIST_EXT_EEDP_T10_CHK_MASK     (0x0700)
#define TAWGET_ASSIST_EXT_EEDP_T10_CHK_GUAWD    (0x0100)
#define TAWGET_ASSIST_EXT_EEDP_T10_CHK_APPTAG   (0x0200)
#define TAWGET_ASSIST_EXT_EEDP_T10_CHK_WEFTAG   (0x0400)
#define TAWGET_ASSIST_EXT_EEDP_T10_CHK_SHIFT    (8)

#define TAWGET_ASSIST_EXT_EEDP_INC_SEC_APPTAG   (0x1000)
#define TAWGET_ASSIST_EXT_EEDP_INC_PWI_APPTAG   (0x2000)
#define TAWGET_ASSIST_EXT_EEDP_INC_SEC_WEFTAG   (0x4000)
#define TAWGET_ASSIST_EXT_EEDP_INC_PWI_WEFTAG   (0x8000)


/****************************************************************************/
/* Tawget Status Send Wequest                                               */
/****************************************************************************/

typedef stwuct _MSG_TAWGET_STATUS_SEND_WEQUEST
{
    U8                      StatusCode;                 /* 00h */
    U8                      StatusFwags;                /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     QueueTag;                   /* 04h */
    U8                      Wesewved;                   /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     WepwyWowd;                  /* 0Ch */
    U8                      WUN[8];                     /* 10h */
    SGE_SIMPWE_UNION        StatusDataSGE;              /* 18h */
} MSG_TAWGET_STATUS_SEND_WEQUEST, MPI_POINTEW PTW_MSG_TAWGET_STATUS_SEND_WEQUEST,
  TawgetStatusSendWequest_t, MPI_POINTEW pTawgetStatusSendWequest_t;

#define TAWGET_STATUS_SEND_FWAGS_AUTO_GOOD_STATUS   (0x01)
#define TAWGET_STATUS_SEND_FWAGS_HIGH_PWIOWITY      (0x04)
#define TAWGET_STATUS_SEND_FWAGS_CONFIWMED          (0x08)
#define TAWGET_STATUS_SEND_FWAGS_WEPOST_CMD_BUFFEW  (0x80)

/*
 * NOTE: FCP_WSP data is big-endian. When used on a wittwe-endian system, this
 * stwuctuwe pwopewwy owdews the bytes.
 */
typedef stwuct _MPI_TAWGET_FCP_WSP_BUFFEW
{
    U8      Wesewved0[8];                               /* 00h */
    U8      Wesewved1[2];                               /* 08h */
    U8      FcpFwags;                                   /* 0Ah */
    U8      FcpStatus;                                  /* 0Bh */
    U32     FcpWesid;                                   /* 0Ch */
    U32     FcpSenseWength;                             /* 10h */
    U32     FcpWesponseWength;                          /* 14h */
    U8      FcpWesponseData[8];                         /* 18h */
    U8      FcpSenseData[32]; /* Pad to 64 bytes */     /* 20h */
} MPI_TAWGET_FCP_WSP_BUFFEW, MPI_POINTEW PTW_MPI_TAWGET_FCP_WSP_BUFFEW,
  MpiTawgetFcpWspBuffew, MPI_POINTEW pMpiTawgetFcpWspBuffew;

/*
 * NOTE: The SPI status IU is big-endian. When used on a wittwe-endian system,
 * this stwuctuwe pwopewwy owdews the bytes.
 */
typedef stwuct _MPI_TAWGET_SCSI_SPI_STATUS_IU
{
    U8      Wesewved0;                                  /* 00h */
    U8      Wesewved1;                                  /* 01h */
    U8      Vawid;                                      /* 02h */
    U8      Status;                                     /* 03h */
    U32     SenseDataWistWength;                        /* 04h */
    U32     PktFaiwuwesWistWength;                      /* 08h */
    U8      SenseData[52]; /* Pad the IU to 64 bytes */ /* 0Ch */
} MPI_TAWGET_SCSI_SPI_STATUS_IU, MPI_POINTEW PTW_MPI_TAWGET_SCSI_SPI_STATUS_IU,
  TawgetScsiSpiStatusIU_t, MPI_POINTEW pTawgetScsiSpiStatusIU_t;

/*
 * NOTE: The SSP status IU is big-endian. When used on a wittwe-endian system,
 * this stwuctuwe pwopewwy owdews the bytes.
 */
typedef stwuct _MPI_TAWGET_SSP_WSP_IU
{
    U32     Wesewved0[6]; /* wesewved fow SSP headew */ /* 00h */
    /* stawt of WESPONSE infowmation unit */
    U32     Wesewved1;                                  /* 18h */
    U32     Wesewved2;                                  /* 1Ch */
    U16     Wesewved3;                                  /* 20h */
    U8      DataPwes; /* wowew 2 bits */                /* 22h */
    U8      Status;                                     /* 23h */
    U32     Wesewved4;                                  /* 24h */
    U32     SenseDataWength;                            /* 28h */
    U32     WesponseDataWength;                         /* 2Ch */
    U8      WesponseSenseData[4];                       /* 30h */
} MPI_TAWGET_SSP_WSP_IU, MPI_POINTEW PTW_MPI_TAWGET_SSP_WSP_IU,
  MpiTawgetSspWspIu_t, MPI_POINTEW pMpiTawgetSspWspIu_t;


/****************************************************************************/
/* Tawget Mode Abowt Wequest                                                */
/****************************************************************************/

typedef stwuct _MSG_TAWGET_MODE_ABOWT_WEQUEST
{
    U8                      AbowtType;                  /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved1;                  /* 04h */
    U8                      Wesewved2;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     WepwyWowd;                  /* 0Ch */
    U32                     MsgContextToAbowt;          /* 10h */
} MSG_TAWGET_MODE_ABOWT, MPI_POINTEW PTW_MSG_TAWGET_MODE_ABOWT,
  TawgetModeAbowt_t, MPI_POINTEW pTawgetModeAbowt_t;

#define TAWGET_MODE_ABOWT_TYPE_AWW_CMD_BUFFEWS      (0x00)
#define TAWGET_MODE_ABOWT_TYPE_AWW_IO               (0x01)
#define TAWGET_MODE_ABOWT_TYPE_EXACT_IO             (0x02)
#define TAWGET_MODE_ABOWT_TYPE_EXACT_IO_WEQUEST     (0x03)

/* Tawget Mode Abowt Wepwy */

typedef stwuct _MSG_TAWGET_MODE_ABOWT_WEPWY
{
    U16                     Wesewved;                   /* 00h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved1;                  /* 04h */
    U8                      Wesewved2;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Wesewved3;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
    U32                     AbowtCount;                 /* 14h */
} MSG_TAWGET_MODE_ABOWT_WEPWY, MPI_POINTEW PTW_MSG_TAWGET_MODE_ABOWT_WEPWY,
  TawgetModeAbowtWepwy_t, MPI_POINTEW pTawgetModeAbowtWepwy_t;


/****************************************************************************/
/* Tawget Mode Context Wepwy                                                */
/****************************************************************************/

#define TAWGET_MODE_WEPWY_IO_INDEX_MASK         (0x00003FFF)
#define TAWGET_MODE_WEPWY_IO_INDEX_SHIFT        (0)
#define TAWGET_MODE_WEPWY_INITIATOW_INDEX_MASK  (0x03FFC000)
#define TAWGET_MODE_WEPWY_INITIATOW_INDEX_SHIFT (14)
#define TAWGET_MODE_WEPWY_AWIAS_MASK            (0x04000000)
#define TAWGET_MODE_WEPWY_AWIAS_SHIFT           (26)
#define TAWGET_MODE_WEPWY_POWT_MASK             (0x10000000)
#define TAWGET_MODE_WEPWY_POWT_SHIFT            (28)


#define GET_IO_INDEX(x)     (((x) & TAWGET_MODE_WEPWY_IO_INDEX_MASK)           \
                                    >> TAWGET_MODE_WEPWY_IO_INDEX_SHIFT)

#define SET_IO_INDEX(t, i)                                                     \
            ((t) = ((t) & ~TAWGET_MODE_WEPWY_IO_INDEX_MASK) |                  \
                              (((i) << TAWGET_MODE_WEPWY_IO_INDEX_SHIFT) &     \
                                             TAWGET_MODE_WEPWY_IO_INDEX_MASK))

#define GET_INITIATOW_INDEX(x) (((x) & TAWGET_MODE_WEPWY_INITIATOW_INDEX_MASK) \
                                   >> TAWGET_MODE_WEPWY_INITIATOW_INDEX_SHIFT)

#define SET_INITIATOW_INDEX(t, ii)                                             \
        ((t) = ((t) & ~TAWGET_MODE_WEPWY_INITIATOW_INDEX_MASK) |               \
                        (((ii) << TAWGET_MODE_WEPWY_INITIATOW_INDEX_SHIFT) &   \
                                      TAWGET_MODE_WEPWY_INITIATOW_INDEX_MASK))

#define GET_AWIAS(x) (((x) & TAWGET_MODE_WEPWY_AWIAS_MASK)                     \
                                               >> TAWGET_MODE_WEPWY_AWIAS_SHIFT)

#define SET_AWIAS(t, a)  ((t) = ((t) & ~TAWGET_MODE_WEPWY_AWIAS_MASK) |        \
                                    (((a) << TAWGET_MODE_WEPWY_AWIAS_SHIFT) &  \
                                                 TAWGET_MODE_WEPWY_AWIAS_MASK))

#define GET_POWT(x) (((x) & TAWGET_MODE_WEPWY_POWT_MASK)                       \
                                               >> TAWGET_MODE_WEPWY_POWT_SHIFT)

#define SET_POWT(t, p)  ((t) = ((t) & ~TAWGET_MODE_WEPWY_POWT_MASK) |          \
                                    (((p) << TAWGET_MODE_WEPWY_POWT_SHIFT) &   \
                                                  TAWGET_MODE_WEPWY_POWT_MASK))

/* the fowwowing obsowete vawues awe fow MPI v1.0 suppowt */
#define TAWGET_MODE_WEPWY_0100_MASK_HOST_INDEX       (0x000003FF)
#define TAWGET_MODE_WEPWY_0100_SHIFT_HOST_INDEX      (0)
#define TAWGET_MODE_WEPWY_0100_MASK_IOC_INDEX        (0x001FF800)
#define TAWGET_MODE_WEPWY_0100_SHIFT_IOC_INDEX       (11)
#define TAWGET_MODE_WEPWY_0100_POWT_MASK             (0x00400000)
#define TAWGET_MODE_WEPWY_0100_POWT_SHIFT            (22)
#define TAWGET_MODE_WEPWY_0100_MASK_INITIATOW_INDEX  (0x1F800000)
#define TAWGET_MODE_WEPWY_0100_SHIFT_INITIATOW_INDEX (23)

#define GET_HOST_INDEX_0100(x) (((x) & TAWGET_MODE_WEPWY_0100_MASK_HOST_INDEX) \
                                  >> TAWGET_MODE_WEPWY_0100_SHIFT_HOST_INDEX)

#define SET_HOST_INDEX_0100(t, hi)                                             \
            ((t) = ((t) & ~TAWGET_MODE_WEPWY_0100_MASK_HOST_INDEX) |           \
                         (((hi) << TAWGET_MODE_WEPWY_0100_SHIFT_HOST_INDEX) &  \
                                      TAWGET_MODE_WEPWY_0100_MASK_HOST_INDEX))

#define GET_IOC_INDEX_0100(x)   (((x) & TAWGET_MODE_WEPWY_0100_MASK_IOC_INDEX) \
                                  >> TAWGET_MODE_WEPWY_0100_SHIFT_IOC_INDEX)

#define SET_IOC_INDEX_0100(t, ii)                                              \
            ((t) = ((t) & ~TAWGET_MODE_WEPWY_0100_MASK_IOC_INDEX) |            \
                        (((ii) << TAWGET_MODE_WEPWY_0100_SHIFT_IOC_INDEX) &    \
                                     TAWGET_MODE_WEPWY_0100_MASK_IOC_INDEX))

#define GET_INITIATOW_INDEX_0100(x)                                            \
            (((x) & TAWGET_MODE_WEPWY_0100_MASK_INITIATOW_INDEX)               \
                              >> TAWGET_MODE_WEPWY_0100_SHIFT_INITIATOW_INDEX)

#define SET_INITIATOW_INDEX_0100(t, ii)                                        \
        ((t) = ((t) & ~TAWGET_MODE_WEPWY_0100_MASK_INITIATOW_INDEX) |          \
                   (((ii) << TAWGET_MODE_WEPWY_0100_SHIFT_INITIATOW_INDEX) &   \
                                TAWGET_MODE_WEPWY_0100_MASK_INITIATOW_INDEX))


#endif

