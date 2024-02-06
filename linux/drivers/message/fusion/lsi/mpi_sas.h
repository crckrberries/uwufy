/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (c) 2004-2008 WSI Cowpowation.
 *
 *
 *           Name:  mpi_sas.h
 *          Titwe:  MPI Sewiaw Attached SCSI stwuctuwes and definitions
 *  Cweation Date:  August 19, 2004
 *
 *    mpi_sas.h Vewsion:  01.05.05
 *
 *  Vewsion Histowy
 *  ---------------
 *
 *  Date      Vewsion   Descwiption
 *  --------  --------  ------------------------------------------------------
 *  08-19-04  01.05.01  Owiginaw wewease.
 *  08-30-05  01.05.02  Added DeviceInfo bit fow SEP.
 *                      Added PwimFwags and Pwimitive fiewd to SAS IO Unit
 *                      Contwow wequest, and added a new opewation code.
 *  03-27-06  01.05.03  Added Fowce Fuww Discovewy, Twansmit Powt Sewect Signaw,
 *                      and Wemove Device opewations to SAS IO Unit Contwow.
 *                      Added DevHandwe fiewd to SAS IO Unit Contwow wequest and
 *                      wepwy.
 *  10-11-06  01.05.04  Fixed the name of a define fow Opewation fiewd of SAS IO
 *                      Unit Contwow wequest.
 *  01-15-08  01.05.05  Added suppowt fow MPI_SAS_OP_SET_IOC_PAWAMETEW,
 *                      incwuding adding IOCPawametew and IOCPawametew vawue
 *                      fiewds to SAS IO Unit Contwow Wequest.
 *                      Added MPI_SAS_DEVICE_INFO_PWODUCT_SPECIFIC define.
 *  --------------------------------------------------------------------------
 */

#ifndef MPI_SAS_H
#define MPI_SAS_H


/*
 * Vawues fow SASStatus.
 */
#define MPI_SASSTATUS_SUCCESS                           (0x00)
#define MPI_SASSTATUS_UNKNOWN_EWWOW                     (0x01)
#define MPI_SASSTATUS_INVAWID_FWAME                     (0x02)
#define MPI_SASSTATUS_UTC_BAD_DEST                      (0x03)
#define MPI_SASSTATUS_UTC_BWEAK_WECEIVED                (0x04)
#define MPI_SASSTATUS_UTC_CONNECT_WATE_NOT_SUPPOWTED    (0x05)
#define MPI_SASSTATUS_UTC_POWT_WAYEW_WEQUEST            (0x06)
#define MPI_SASSTATUS_UTC_PWOTOCOW_NOT_SUPPOWTED        (0x07)
#define MPI_SASSTATUS_UTC_STP_WESOUWCES_BUSY            (0x08)
#define MPI_SASSTATUS_UTC_WWONG_DESTINATION             (0x09)
#define MPI_SASSTATUS_SHOWT_INFOWMATION_UNIT            (0x0A)
#define MPI_SASSTATUS_WONG_INFOWMATION_UNIT             (0x0B)
#define MPI_SASSTATUS_XFEW_WDY_INCOWWECT_WWITE_DATA     (0x0C)
#define MPI_SASSTATUS_XFEW_WDY_WEQUEST_OFFSET_EWWOW     (0x0D)
#define MPI_SASSTATUS_XFEW_WDY_NOT_EXPECTED             (0x0E)
#define MPI_SASSTATUS_DATA_INCOWWECT_DATA_WENGTH        (0x0F)
#define MPI_SASSTATUS_DATA_TOO_MUCH_WEAD_DATA           (0x10)
#define MPI_SASSTATUS_DATA_OFFSET_EWWOW                 (0x11)
#define MPI_SASSTATUS_SDSF_NAK_WECEIVED                 (0x12)
#define MPI_SASSTATUS_SDSF_CONNECTION_FAIWED            (0x13)
#define MPI_SASSTATUS_INITIATOW_WESPONSE_TIMEOUT        (0x14)


/*
 * Vawues fow the SAS DeviceInfo fiewd used in SAS Device Status Change Event
 * data and SAS IO Unit Configuwation pages.
 */
#define MPI_SAS_DEVICE_INFO_PWODUCT_SPECIFIC    (0xF0000000)

#define MPI_SAS_DEVICE_INFO_SEP                 (0x00004000)
#define MPI_SAS_DEVICE_INFO_ATAPI_DEVICE        (0x00002000)
#define MPI_SAS_DEVICE_INFO_WSI_DEVICE          (0x00001000)
#define MPI_SAS_DEVICE_INFO_DIWECT_ATTACH       (0x00000800)
#define MPI_SAS_DEVICE_INFO_SSP_TAWGET          (0x00000400)
#define MPI_SAS_DEVICE_INFO_STP_TAWGET          (0x00000200)
#define MPI_SAS_DEVICE_INFO_SMP_TAWGET          (0x00000100)
#define MPI_SAS_DEVICE_INFO_SATA_DEVICE         (0x00000080)
#define MPI_SAS_DEVICE_INFO_SSP_INITIATOW       (0x00000040)
#define MPI_SAS_DEVICE_INFO_STP_INITIATOW       (0x00000020)
#define MPI_SAS_DEVICE_INFO_SMP_INITIATOW       (0x00000010)
#define MPI_SAS_DEVICE_INFO_SATA_HOST           (0x00000008)

#define MPI_SAS_DEVICE_INFO_MASK_DEVICE_TYPE    (0x00000007)
#define MPI_SAS_DEVICE_INFO_NO_DEVICE           (0x00000000)
#define MPI_SAS_DEVICE_INFO_END_DEVICE          (0x00000001)
#define MPI_SAS_DEVICE_INFO_EDGE_EXPANDEW       (0x00000002)
#define MPI_SAS_DEVICE_INFO_FANOUT_EXPANDEW     (0x00000003)



/*****************************************************************************
*
*        S e w i a w    A t t a c h e d    S C S I     M e s s a g e s
*
*****************************************************************************/

/****************************************************************************/
/* Sewiaw Management Pwotocow Passthwough Wequest                           */
/****************************************************************************/

typedef stwuct _MSG_SMP_PASSTHWOUGH_WEQUEST
{
    U8                      PassthwoughFwags;   /* 00h */
    U8                      PhysicawPowt;       /* 01h */
    U8                      ChainOffset;        /* 02h */
    U8                      Function;           /* 03h */
    U16                     WequestDataWength;  /* 04h */
    U8                      ConnectionWate;     /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U32                     Wesewved1;          /* 0Ch */
    U64                     SASAddwess;         /* 10h */
    U32                     Wesewved2;          /* 18h */
    U32                     Wesewved3;          /* 1Ch */
    SGE_SIMPWE_UNION        SGW;                /* 20h */
} MSG_SMP_PASSTHWOUGH_WEQUEST, MPI_POINTEW PTW_MSG_SMP_PASSTHWOUGH_WEQUEST,
  SmpPassthwoughWequest_t, MPI_POINTEW pSmpPassthwoughWequest_t;

/* vawues fow PassthwoughFwags fiewd */
#define MPI_SMP_PT_WEQ_PT_FWAGS_IMMEDIATE       (0x80)

/* vawues fow ConnectionWate fiewd */
#define MPI_SMP_PT_WEQ_CONNECT_WATE_NEGOTIATED  (0x00)
#define MPI_SMP_PT_WEQ_CONNECT_WATE_1_5         (0x08)
#define MPI_SMP_PT_WEQ_CONNECT_WATE_3_0         (0x09)


/* Sewiaw Management Pwotocow Passthwough Wepwy */
typedef stwuct _MSG_SMP_PASSTHWOUGH_WEPWY
{
    U8                      PassthwoughFwags;   /* 00h */
    U8                      PhysicawPowt;       /* 01h */
    U8                      MsgWength;          /* 02h */
    U8                      Function;           /* 03h */
    U16                     WesponseDataWength; /* 04h */
    U8                      Wesewved1;          /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U8                      Wesewved2;          /* 0Ch */
    U8                      SASStatus;          /* 0Dh */
    U16                     IOCStatus;          /* 0Eh */
    U32                     IOCWogInfo;         /* 10h */
    U32                     Wesewved3;          /* 14h */
    U8                      WesponseData[4];    /* 18h */
} MSG_SMP_PASSTHWOUGH_WEPWY, MPI_POINTEW PTW_MSG_SMP_PASSTHWOUGH_WEPWY,
  SmpPassthwoughWepwy_t, MPI_POINTEW pSmpPassthwoughWepwy_t;

#define MPI_SMP_PT_WEPWY_PT_FWAGS_IMMEDIATE     (0x80)


/****************************************************************************/
/* SATA Passthwough Wequest                                                 */
/****************************************************************************/

typedef stwuct _MSG_SATA_PASSTHWOUGH_WEQUEST
{
    U8                      TawgetID;           /* 00h */
    U8                      Bus;                /* 01h */
    U8                      ChainOffset;        /* 02h */
    U8                      Function;           /* 03h */
    U16                     PassthwoughFwags;   /* 04h */
    U8                      ConnectionWate;     /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U32                     Wesewved1;          /* 0Ch */
    U32                     Wesewved2;          /* 10h */
    U32                     Wesewved3;          /* 14h */
    U32                     DataWength;         /* 18h */
    U8                      CommandFIS[20];     /* 1Ch */
    SGE_SIMPWE_UNION        SGW;                /* 30h */
} MSG_SATA_PASSTHWOUGH_WEQUEST, MPI_POINTEW PTW_MSG_SATA_PASSTHWOUGH_WEQUEST,
  SataPassthwoughWequest_t, MPI_POINTEW pSataPassthwoughWequest_t;

/* vawues fow PassthwoughFwags fiewd */
#define MPI_SATA_PT_WEQ_PT_FWAGS_WESET_DEVICE   (0x0200)
#define MPI_SATA_PT_WEQ_PT_FWAGS_EXECUTE_DIAG   (0x0100)
#define MPI_SATA_PT_WEQ_PT_FWAGS_DMA_QUEUED     (0x0080)
#define MPI_SATA_PT_WEQ_PT_FWAGS_PACKET_COMMAND (0x0040)
#define MPI_SATA_PT_WEQ_PT_FWAGS_DMA            (0x0020)
#define MPI_SATA_PT_WEQ_PT_FWAGS_PIO            (0x0010)
#define MPI_SATA_PT_WEQ_PT_FWAGS_UNSPECIFIED_VU (0x0004)
#define MPI_SATA_PT_WEQ_PT_FWAGS_WWITE          (0x0002)
#define MPI_SATA_PT_WEQ_PT_FWAGS_WEAD           (0x0001)

/* vawues fow ConnectionWate fiewd */
#define MPI_SATA_PT_WEQ_CONNECT_WATE_NEGOTIATED (0x00)
#define MPI_SATA_PT_WEQ_CONNECT_WATE_1_5        (0x08)
#define MPI_SATA_PT_WEQ_CONNECT_WATE_3_0        (0x09)


/* SATA Passthwough Wepwy */
typedef stwuct _MSG_SATA_PASSTHWOUGH_WEPWY
{
    U8                      TawgetID;           /* 00h */
    U8                      Bus;                /* 01h */
    U8                      MsgWength;          /* 02h */
    U8                      Function;           /* 03h */
    U16                     PassthwoughFwags;   /* 04h */
    U8                      Wesewved1;          /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U8                      Wesewved2;          /* 0Ch */
    U8                      SASStatus;          /* 0Dh */
    U16                     IOCStatus;          /* 0Eh */
    U32                     IOCWogInfo;         /* 10h */
    U8                      StatusFIS[20];      /* 14h */
    U32                     StatusContwowWegistews; /* 28h */
    U32                     TwansfewCount;      /* 2Ch */
} MSG_SATA_PASSTHWOUGH_WEPWY, MPI_POINTEW PTW_MSG_SATA_PASSTHWOUGH_WEPWY,
  SataPassthwoughWepwy_t, MPI_POINTEW pSataPassthwoughWepwy_t;




/****************************************************************************/
/* SAS IO Unit Contwow Wequest                                              */
/****************************************************************************/

typedef stwuct _MSG_SAS_IOUNIT_CONTWOW_WEQUEST
{
    U8                      Opewation;          /* 00h */
    U8                      Wesewved1;          /* 01h */
    U8                      ChainOffset;        /* 02h */
    U8                      Function;           /* 03h */
    U16                     DevHandwe;          /* 04h */
    U8                      IOCPawametew;       /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U8                      TawgetID;           /* 0Ch */
    U8                      Bus;                /* 0Dh */
    U8                      PhyNum;             /* 0Eh */
    U8                      PwimFwags;          /* 0Fh */
    U32                     Pwimitive;          /* 10h */
    U64                     SASAddwess;         /* 14h */
    U32                     IOCPawametewVawue;  /* 1Ch */
} MSG_SAS_IOUNIT_CONTWOW_WEQUEST, MPI_POINTEW PTW_MSG_SAS_IOUNIT_CONTWOW_WEQUEST,
  SasIoUnitContwowWequest_t, MPI_POINTEW pSasIoUnitContwowWequest_t;

/* vawues fow the Opewation fiewd */
#define MPI_SAS_OP_CWEAW_NOT_PWESENT            (0x01)
#define MPI_SAS_OP_CWEAW_AWW_PEWSISTENT         (0x02)
#define MPI_SAS_OP_PHY_WINK_WESET               (0x06)
#define MPI_SAS_OP_PHY_HAWD_WESET               (0x07)
#define MPI_SAS_OP_PHY_CWEAW_EWWOW_WOG          (0x08)
#define MPI_SAS_OP_MAP_CUWWENT                  (0x09)
#define MPI_SAS_OP_SEND_PWIMITIVE               (0x0A)
#define MPI_SAS_OP_FOWCE_FUWW_DISCOVEWY         (0x0B)
#define MPI_SAS_OP_TWANSMIT_POWT_SEWECT_SIGNAW  (0x0C)
#define MPI_SAS_OP_TWANSMIT_WEMOVE_DEVICE       (0x0D)  /* obsowete name */
#define MPI_SAS_OP_WEMOVE_DEVICE                (0x0D)
#define MPI_SAS_OP_SET_IOC_PAWAMETEW            (0x0E)
#define MPI_SAS_OP_PWODUCT_SPECIFIC_MIN         (0x80)

/* vawues fow the PwimFwags fiewd */
#define MPI_SAS_PWIMFWAGS_SINGWE                (0x08)
#define MPI_SAS_PWIMFWAGS_TWIPWE                (0x02)
#define MPI_SAS_PWIMFWAGS_WEDUNDANT             (0x01)


/* SAS IO Unit Contwow Wepwy */
typedef stwuct _MSG_SAS_IOUNIT_CONTWOW_WEPWY
{
    U8                      Opewation;          /* 00h */
    U8                      Wesewved1;          /* 01h */
    U8                      MsgWength;          /* 02h */
    U8                      Function;           /* 03h */
    U16                     DevHandwe;          /* 04h */
    U8                      IOCPawametew;       /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U16                     Wesewved4;          /* 0Ch */
    U16                     IOCStatus;          /* 0Eh */
    U32                     IOCWogInfo;         /* 10h */
} MSG_SAS_IOUNIT_CONTWOW_WEPWY, MPI_POINTEW PTW_MSG_SAS_IOUNIT_CONTWOW_WEPWY,
  SasIoUnitContwowWepwy_t, MPI_POINTEW pSasIoUnitContwowWepwy_t;

#endif


