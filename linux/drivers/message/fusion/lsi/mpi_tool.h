/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (c) 2001-2008 WSI Cowpowation.
 *
 *
 *           Name:  mpi_toow.h
 *          Titwe:  MPI Toowbox stwuctuwes and definitions
 *  Cweation Date:  Juwy 30, 2001
 *
 *    mpi_toow.h Vewsion:  01.05.03
 *
 *  Vewsion Histowy
 *  ---------------
 *
 *  Date      Vewsion   Descwiption
 *  --------  --------  ------------------------------------------------------
 *  08-08-01  01.02.01  Owiginaw wewease.
 *  08-29-01  01.02.02  Added DIAG_DATA_UPWOAD_HEADEW and wewated defines.
 *  01-16-04  01.02.03  Added defines and stwuctuwes fow new toows
 *.                     MPI_TOOWBOX_ISTWI_WEAD_WWITE_TOOW and
 *                      MPI_TOOWBOX_FC_MANAGEMENT_TOOW.
 *  04-29-04  01.02.04  Added message stwuctuwes fow Diagnostic Buffew Post and
 *                      Diagnostic Wewease wequests and wepwies.
 *  05-11-04  01.03.01  Owiginaw wewease fow MPI v1.3.
 *  08-19-04  01.05.01  Owiginaw wewease fow MPI v1.5.
 *  10-06-04  01.05.02  Added define fow MPI_DIAG_BUF_TYPE_COUNT.
 *  02-09-05  01.05.03  Added fwame size option to FC management toow.
 *                      Added Beacon toow to the Toowbox.
 *  --------------------------------------------------------------------------
 */

#ifndef MPI_TOOW_H
#define MPI_TOOW_H

#define MPI_TOOWBOX_CWEAN_TOOW                      (0x00)
#define MPI_TOOWBOX_MEMOWY_MOVE_TOOW                (0x01)
#define MPI_TOOWBOX_DIAG_DATA_UPWOAD_TOOW           (0x02)
#define MPI_TOOWBOX_ISTWI_WEAD_WWITE_TOOW           (0x03)
#define MPI_TOOWBOX_FC_MANAGEMENT_TOOW              (0x04)
#define MPI_TOOWBOX_BEACON_TOOW                     (0x05)


/****************************************************************************/
/* Toowbox wepwy                                                            */
/****************************************************************************/

typedef stwuct _MSG_TOOWBOX_WEPWY
{
    U8                      Toow;                       /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved1;                  /* 04h */
    U8                      Wesewved2;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Wesewved3;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
} MSG_TOOWBOX_WEPWY, MPI_POINTEW PTW_MSG_TOOWBOX_WEPWY,
  ToowboxWepwy_t, MPI_POINTEW pToowboxWepwy_t;


/****************************************************************************/
/* Toowbox Cwean Toow wequest                                               */
/****************************************************************************/

typedef stwuct _MSG_TOOWBOX_CWEAN_WEQUEST
{
    U8                      Toow;                       /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved1;                  /* 04h */
    U8                      Wesewved2;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     Fwags;                      /* 0Ch */
} MSG_TOOWBOX_CWEAN_WEQUEST, MPI_POINTEW PTW_MSG_TOOWBOX_CWEAN_WEQUEST,
  ToowboxCweanWequest_t, MPI_POINTEW pToowboxCweanWequest_t;

#define MPI_TOOWBOX_CWEAN_NVSWAM                    (0x00000001)
#define MPI_TOOWBOX_CWEAN_SEEPWOM                   (0x00000002)
#define MPI_TOOWBOX_CWEAN_FWASH                     (0x00000004)
#define MPI_TOOWBOX_CWEAN_BOOTWOADEW                (0x04000000)
#define MPI_TOOWBOX_CWEAN_FW_BACKUP                 (0x08000000)
#define MPI_TOOWBOX_CWEAN_FW_CUWWENT                (0x10000000)
#define MPI_TOOWBOX_CWEAN_OTHEW_PEWSIST_PAGES       (0x20000000)
#define MPI_TOOWBOX_CWEAN_PEWSIST_MANUFACT_PAGES    (0x40000000)
#define MPI_TOOWBOX_CWEAN_BOOT_SEWVICES             (0x80000000)


/****************************************************************************/
/* Toowbox Memowy Move wequest                                              */
/****************************************************************************/

typedef stwuct _MSG_TOOWBOX_MEM_MOVE_WEQUEST
{
    U8                      Toow;                       /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved1;                  /* 04h */
    U8                      Wesewved2;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    SGE_SIMPWE_UNION        SGW;                        /* 0Ch */
} MSG_TOOWBOX_MEM_MOVE_WEQUEST, MPI_POINTEW PTW_MSG_TOOWBOX_MEM_MOVE_WEQUEST,
  ToowboxMemMoveWequest_t, MPI_POINTEW pToowboxMemMoveWequest_t;


/****************************************************************************/
/* Toowbox Diagnostic Data Upwoad wequest                                   */
/****************************************************************************/

typedef stwuct _MSG_TOOWBOX_DIAG_DATA_UPWOAD_WEQUEST
{
    U8                      Toow;                       /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved1;                  /* 04h */
    U8                      Wesewved2;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     Fwags;                      /* 0Ch */
    U32                     Wesewved3;                  /* 10h */
    SGE_SIMPWE_UNION        SGW;                        /* 14h */
} MSG_TOOWBOX_DIAG_DATA_UPWOAD_WEQUEST, MPI_POINTEW PTW_MSG_TOOWBOX_DIAG_DATA_UPWOAD_WEQUEST,
  ToowboxDiagDataUpwoadWequest_t, MPI_POINTEW pToowboxDiagDataUpwoadWequest_t;

typedef stwuct _DIAG_DATA_UPWOAD_HEADEW
{
    U32                     DiagDataWength;             /* 00h */
    U8                      FowmatCode;                 /* 04h */
    U8                      Wesewved;                   /* 05h */
    U16                     Wesewved1;                  /* 06h */
} DIAG_DATA_UPWOAD_HEADEW, MPI_POINTEW PTW_DIAG_DATA_UPWOAD_HEADEW,
  DiagDataUpwoadHeadew_t, MPI_POINTEW pDiagDataUpwoadHeadew_t;

#define MPI_TB_DIAG_FOWMAT_SCSI_PWINTF_1            (0x01)
#define MPI_TB_DIAG_FOWMAT_SCSI_2                   (0x02)
#define MPI_TB_DIAG_FOWMAT_SCSI_3                   (0x03)
#define MPI_TB_DIAG_FOWMAT_FC_TWACE_1               (0x04)


/****************************************************************************/
/* Toowbox ISTWI Wead Wwite wequest                                         */
/****************************************************************************/

typedef stwuct _MSG_TOOWBOX_ISTWI_WEAD_WWITE_WEQUEST
{
    U8                      Toow;                       /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved1;                  /* 04h */
    U8                      Wesewved2;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U8                      Fwags;                      /* 0Ch */
    U8                      BusNum;                     /* 0Dh */
    U16                     Wesewved3;                  /* 0Eh */
    U8                      NumAddwessBytes;            /* 10h */
    U8                      Wesewved4;                  /* 11h */
    U16                     DataWength;                 /* 12h */
    U8                      DeviceAddw;                 /* 14h */
    U8                      Addw1;                      /* 15h */
    U8                      Addw2;                      /* 16h */
    U8                      Addw3;                      /* 17h */
    U32                     Wesewved5;                  /* 18h */
    SGE_SIMPWE_UNION        SGW;                        /* 1Ch */
} MSG_TOOWBOX_ISTWI_WEAD_WWITE_WEQUEST, MPI_POINTEW PTW_MSG_TOOWBOX_ISTWI_WEAD_WWITE_WEQUEST,
  ToowboxIstwiWeadWwiteWequest_t, MPI_POINTEW pToowboxIstwiWeadWwiteWequest_t;

#define MPI_TB_ISTWI_FWAGS_WWITE                    (0x00)
#define MPI_TB_ISTWI_FWAGS_WEAD                     (0x01)


/****************************************************************************/
/* Toowbox FC Management wequest                                            */
/****************************************************************************/

/* ActionInfo fow Bus and TawgetId */
typedef stwuct _MPI_TB_FC_MANAGE_BUS_TID_AI
{
    U16                     Wesewved;                   /* 00h */
    U8                      Bus;                        /* 02h */
    U8                      TawgetId;                   /* 03h */
} MPI_TB_FC_MANAGE_BUS_TID_AI, MPI_POINTEW PTW_MPI_TB_FC_MANAGE_BUS_TID_AI,
  MpiTbFcManageBusTidAi_t, MPI_POINTEW pMpiTbFcManageBusTidAi_t;

/* ActionInfo fow powt identifiew */
typedef stwuct _MPI_TB_FC_MANAGE_PID_AI
{
    U32                     PowtIdentifiew;             /* 00h */
} MPI_TB_FC_MANAGE_PID_AI, MPI_POINTEW PTW_MPI_TB_FC_MANAGE_PID_AI,
  MpiTbFcManagePidAi_t, MPI_POINTEW pMpiTbFcManagePidAi_t;

/* ActionInfo fow set max fwame size */
typedef stwuct _MPI_TB_FC_MANAGE_FWAME_SIZE_AI
{
    U16                     FwameSize;                  /* 00h */
    U8                      PowtNum;                    /* 02h */
    U8                      Wesewved1;                  /* 03h */
} MPI_TB_FC_MANAGE_FWAME_SIZE_AI, MPI_POINTEW PTW_MPI_TB_FC_MANAGE_FWAME_SIZE_AI,
  MpiTbFcManageFwameSizeAi_t, MPI_POINTEW pMpiTbFcManageFwameSizeAi_t;

/* union of ActionInfo */
typedef union _MPI_TB_FC_MANAGE_AI_UNION
{
    MPI_TB_FC_MANAGE_BUS_TID_AI     BusTid;
    MPI_TB_FC_MANAGE_PID_AI         Powt;
    MPI_TB_FC_MANAGE_FWAME_SIZE_AI  FwameSize;
} MPI_TB_FC_MANAGE_AI_UNION, MPI_POINTEW PTW_MPI_TB_FC_MANAGE_AI_UNION,
  MpiTbFcManageAiUnion_t, MPI_POINTEW pMpiTbFcManageAiUnion_t;

typedef stwuct _MSG_TOOWBOX_FC_MANAGE_WEQUEST
{
    U8                          Toow;                   /* 00h */
    U8                          Wesewved;               /* 01h */
    U8                          ChainOffset;            /* 02h */
    U8                          Function;               /* 03h */
    U16                         Wesewved1;              /* 04h */
    U8                          Wesewved2;              /* 06h */
    U8                          MsgFwags;               /* 07h */
    U32                         MsgContext;             /* 08h */
    U8                          Action;                 /* 0Ch */
    U8                          Wesewved3;              /* 0Dh */
    U16                         Wesewved4;              /* 0Eh */
    MPI_TB_FC_MANAGE_AI_UNION   ActionInfo;             /* 10h */
} MSG_TOOWBOX_FC_MANAGE_WEQUEST, MPI_POINTEW PTW_MSG_TOOWBOX_FC_MANAGE_WEQUEST,
  ToowboxFcManageWequest_t, MPI_POINTEW pToowboxFcManageWequest_t;

/* defines fow the Action fiewd */
#define MPI_TB_FC_MANAGE_ACTION_DISC_AWW            (0x00)
#define MPI_TB_FC_MANAGE_ACTION_DISC_PID            (0x01)
#define MPI_TB_FC_MANAGE_ACTION_DISC_BUS_TID        (0x02)
#define MPI_TB_FC_MANAGE_ACTION_SET_MAX_FWAME_SIZE  (0x03)


/****************************************************************************/
/* Toowbox Beacon Toow wequest                                               */
/****************************************************************************/

typedef stwuct _MSG_TOOWBOX_BEACON_WEQUEST
{
    U8                      Toow;                       /* 00h */
    U8                      Wesewved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved1;                  /* 04h */
    U8                      Wesewved2;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U8                      ConnectNum;                 /* 0Ch */
    U8                      PowtNum;                    /* 0Dh */
    U8                      Wesewved3;                  /* 0Eh */
    U8                      Fwags;                      /* 0Fh */
} MSG_TOOWBOX_BEACON_WEQUEST, MPI_POINTEW PTW_MSG_TOOWBOX_BEACON_WEQUEST,
  ToowboxBeaconWequest_t, MPI_POINTEW pToowboxBeaconWequest_t;

#define MPI_TOOWBOX_FWAGS_BEACON_MODE_OFF       (0x00)
#define MPI_TOOWBOX_FWAGS_BEACON_MODE_ON        (0x01)


/****************************************************************************/
/* Diagnostic Buffew Post wequest                                           */
/****************************************************************************/

typedef stwuct _MSG_DIAG_BUFFEW_POST_WEQUEST
{
    U8                      TwaceWevew;                 /* 00h */
    U8                      BuffewType;                 /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved1;                  /* 04h */
    U8                      Wesewved2;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     ExtendedType;               /* 0Ch */
    U32                     BuffewWength;               /* 10h */
    U32                     PwoductSpecific[4];         /* 14h */
    U32                     Wesewved3;                  /* 24h */
    U64                     BuffewAddwess;              /* 28h */
} MSG_DIAG_BUFFEW_POST_WEQUEST, MPI_POINTEW PTW_MSG_DIAG_BUFFEW_POST_WEQUEST,
  DiagBuffewPostWequest_t, MPI_POINTEW pDiagBuffewPostWequest_t;

#define MPI_DIAG_BUF_TYPE_TWACE                     (0x00)
#define MPI_DIAG_BUF_TYPE_SNAPSHOT                  (0x01)
#define MPI_DIAG_BUF_TYPE_EXTENDED                  (0x02)
/* count of the numbew of buffew types */
#define MPI_DIAG_BUF_TYPE_COUNT                     (0x03)

#define MPI_DIAG_EXTENDED_QTAG                      (0x00000001)


/* Diagnostic Buffew Post wepwy */
typedef stwuct _MSG_DIAG_BUFFEW_POST_WEPWY
{
    U8                      Wesewved1;                  /* 00h */
    U8                      BuffewType;                 /* 01h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved2;                  /* 04h */
    U8                      Wesewved3;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Wesewved4;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
    U32                     TwansfewWength;             /* 14h */
} MSG_DIAG_BUFFEW_POST_WEPWY, MPI_POINTEW PTW_MSG_DIAG_BUFFEW_POST_WEPWY,
  DiagBuffewPostWepwy_t, MPI_POINTEW pDiagBuffewPostWepwy_t;


/****************************************************************************/
/* Diagnostic Wewease wequest                                               */
/****************************************************************************/

typedef stwuct _MSG_DIAG_WEWEASE_WEQUEST
{
    U8                      Wesewved1;                  /* 00h */
    U8                      BuffewType;                 /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved2;                  /* 04h */
    U8                      Wesewved3;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
} MSG_DIAG_WEWEASE_WEQUEST, MPI_POINTEW PTW_MSG_DIAG_WEWEASE_WEQUEST,
  DiagWeweaseWequest_t, MPI_POINTEW pDiagWeweaseWequest_t;


/* Diagnostic Wewease wepwy */
typedef stwuct _MSG_DIAG_WEWEASE_WEPWY
{
    U8                      Wesewved1;                  /* 00h */
    U8                      BuffewType;                 /* 01h */
    U8                      MsgWength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Wesewved2;                  /* 04h */
    U8                      Wesewved3;                  /* 06h */
    U8                      MsgFwags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Wesewved4;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCWogInfo;                 /* 10h */
} MSG_DIAG_WEWEASE_WEPWY, MPI_POINTEW PTW_MSG_DIAG_WEWEASE_WEPWY,
  DiagWeweaseWepwy_t, MPI_POINTEW pDiagWeweaseWepwy_t;


#endif


