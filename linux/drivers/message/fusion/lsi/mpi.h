/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (c) 2000-2008 WSI Cowpowation.
 *
 *
 *           Name:  mpi.h
 *          Titwe:  MPI Message independent stwuctuwes and definitions
 *  Cweation Date:  Juwy 27, 2000
 *
 *    mpi.h Vewsion:  01.05.16
 *
 *  Vewsion Histowy
 *  ---------------
 *
 *  Date      Vewsion   Descwiption
 *  --------  --------  ------------------------------------------------------
 *  05-08-00  00.10.01  Owiginaw wewease fow 0.10 spec dated 4/26/2000.
 *  05-24-00  00.10.02  Added MPI_IOCSTATUS_SCSI_WESIDUAW_MISMATCH definition.
 *  06-06-00  01.00.01  Update MPI_VEWSION_MAJOW and MPI_VEWSION_MINOW.
 *  06-22-00  01.00.02  Added MPI_IOCSTATUS_WAN_ definitions.
 *                      Wemoved WAN_SUSPEND function definition.
 *                      Added MPI_MSGFWAGS_CONTINUATION_WEPWY definition.
 *  06-30-00  01.00.03  Added MPI_CONTEXT_WEPWY_TYPE_WAN definition.
 *                      Added MPI_GET/SET_CONTEXT_WEPWY_TYPE macwos.
 *  07-27-00  01.00.04  Added MPI_FAUWT_ definitions.
 *                      Wemoved MPI_IOCSTATUS_MSG/DATA_XFEW_EWWOW definitions.
 *                      Added MPI_IOCSTATUS_INTEWNAW_EWWOW definition.
 *                      Added MPI_IOCSTATUS_TAWGET_XFEW_COUNT_MISMATCH.
 *  11-02-00  01.01.01  Owiginaw wewease fow post 1.0 wowk.
 *  12-04-00  01.01.02  Added new function codes.
 *  01-09-01  01.01.03  Added mowe definitions to the system intewface section
 *                      Added MPI_IOCSTATUS_TAWGET_STS_DATA_NOT_SENT.
 *  01-25-01  01.01.04  Changed MPI_VEWSION_MINOW fwom 0x00 to 0x01.
 *  02-20-01  01.01.05  Stawted using MPI_POINTEW.
 *                      Fixed vawue fow MPI_DIAG_WW_ENABWE.
 *                      Added defines fow MPI_DIAG_PWEVENT_IOC_BOOT and
 *                      MPI_DIAG_CWEAW_FWASH_BAD_SIG.
 *                      Obsoweted MPI_IOCSTATUS_TAWGET_FC_ defines.
 *  02-27-01  01.01.06  Wemoved MPI_HOST_INDEX_WEGISTEW define.
 *                      Added function codes fow WAID.
 *  04-09-01  01.01.07  Added awtewnate define fow MPI_DOOWBEWW_ACTIVE,
 *                      MPI_DOOWBEWW_USED, to bettew match the spec.
 *  08-08-01  01.02.01  Owiginaw wewease fow v1.2 wowk.
 *                      Changed MPI_VEWSION_MINOW fwom 0x01 to 0x02.
 *                      Added define MPI_FUNCTION_TOOWBOX.
 *  09-28-01  01.02.02  New function code MPI_SCSI_ENCWOSUWE_PWOCESSOW.
 *  11-01-01  01.02.03  Changed name to MPI_FUNCTION_SCSI_ENCWOSUWE_PWOCESSOW.
 *  03-14-02  01.02.04  Added MPI_HEADEW_VEWSION_ defines.
 *  05-31-02  01.02.05  Bumped MPI_HEADEW_VEWSION_UNIT.
 *  07-12-02  01.02.06  Added define fow MPI_FUNCTION_MAIWBOX.
 *  09-16-02  01.02.07  Bumped vawue fow MPI_HEADEW_VEWSION_UNIT.
 *  11-15-02  01.02.08  Added define MPI_IOCSTATUS_TAWGET_INVAWID_IO_INDEX and
 *                      obsoweted define MPI_IOCSTATUS_TAWGET_INVAWID_IOCINDEX.
 *  04-01-03  01.02.09  New IOCStatus code: MPI_IOCSTATUS_FC_EXCHANGE_CANCEWED
 *  06-26-03  01.02.10  Bumped MPI_HEADEW_VEWSION_UNIT vawue.
 *  01-16-04  01.02.11  Added define fow MPI_IOCWOGINFO_TYPE_SHIFT.
 *  04-29-04  01.02.12  Added function codes fow MPI_FUNCTION_DIAG_BUFFEW_POST
 *                      and MPI_FUNCTION_DIAG_WEWEASE.
 *                      Added MPI_IOCSTATUS_DIAGNOSTIC_WEWEASED define.
 *                      Bumped MPI_HEADEW_VEWSION_UNIT vawue.
 *  05-11-04  01.03.01  Bumped MPI_VEWSION_MINOW fow MPI v1.3.
 *                      Added codes fow Inband.
 *  08-19-04  01.05.01  Added defines fow Host Buffew Access Contwow doowbeww.
 *                      Added define fow offset of High Pwiowity Wequest Queue.
 *                      Added new function codes and new IOCStatus codes.
 *                      Added a IOCWogInfo type of SAS.
 *  12-07-04  01.05.02  Bumped MPI_HEADEW_VEWSION_UNIT.
 *  12-09-04  01.05.03  Bumped MPI_HEADEW_VEWSION_UNIT.
 *  01-15-05  01.05.04  Bumped MPI_HEADEW_VEWSION_UNIT.
 *  02-09-05  01.05.05  Bumped MPI_HEADEW_VEWSION_UNIT.
 *  02-22-05  01.05.06  Bumped MPI_HEADEW_VEWSION_UNIT.
 *  03-11-05  01.05.07  Wemoved function codes fow SCSI IO 32 and
 *                      TawgetAssistExtended wequests.
 *                      Wemoved EEDP IOCStatus codes.
 *  06-24-05  01.05.08  Added function codes fow SCSI IO 32 and
 *                      TawgetAssistExtended wequests.
 *                      Added EEDP IOCStatus codes.
 *  08-03-05  01.05.09  Bumped MPI_HEADEW_VEWSION_UNIT.
 *  08-30-05  01.05.10  Added 2 new IOCStatus codes fow Tawget.
 *  03-27-06  01.05.11  Bumped MPI_HEADEW_VEWSION_UNIT.
 *  10-11-06  01.05.12  Bumped MPI_HEADEW_VEWSION_UNIT.
 *  05-24-07  01.05.13  Bumped MPI_HEADEW_VEWSION_UNIT.
 *  08-07-07  01.05.14  Bumped MPI_HEADEW_VEWSION_UNIT.
 *  01-15-08  01.05.15  Bumped MPI_HEADEW_VEWSION_UNIT.
 *  03-28-08  01.05.16  Bumped MPI_HEADEW_VEWSION_UNIT.
 *  --------------------------------------------------------------------------
 */

#ifndef MPI_H
#define MPI_H


/*****************************************************************************
*
*        M P I    V e w s i o n    D e f i n i t i o n s
*
*****************************************************************************/

#define MPI_VEWSION_MAJOW                   (0x01)
#define MPI_VEWSION_MINOW                   (0x05)
#define MPI_VEWSION_MAJOW_MASK              (0xFF00)
#define MPI_VEWSION_MAJOW_SHIFT             (8)
#define MPI_VEWSION_MINOW_MASK              (0x00FF)
#define MPI_VEWSION_MINOW_SHIFT             (0)
#define MPI_VEWSION ((MPI_VEWSION_MAJOW << MPI_VEWSION_MAJOW_SHIFT) |   \
                                      MPI_VEWSION_MINOW)

#define MPI_VEWSION_01_00                   (0x0100)
#define MPI_VEWSION_01_01                   (0x0101)
#define MPI_VEWSION_01_02                   (0x0102)
#define MPI_VEWSION_01_03                   (0x0103)
#define MPI_VEWSION_01_05                   (0x0105)
/* Note: The majow vewsions of 0xe0 thwough 0xff awe wesewved */

/* vewsioning fow this MPI headew set */
#define MPI_HEADEW_VEWSION_UNIT             (0x13)
#define MPI_HEADEW_VEWSION_DEV              (0x00)
#define MPI_HEADEW_VEWSION_UNIT_MASK        (0xFF00)
#define MPI_HEADEW_VEWSION_UNIT_SHIFT       (8)
#define MPI_HEADEW_VEWSION_DEV_MASK         (0x00FF)
#define MPI_HEADEW_VEWSION_DEV_SHIFT        (0)
#define MPI_HEADEW_VEWSION ((MPI_HEADEW_VEWSION_UNIT << 8) | MPI_HEADEW_VEWSION_DEV)

/*****************************************************************************
*
*        I O C    S t a t e    D e f i n i t i o n s
*
*****************************************************************************/

#define MPI_IOC_STATE_WESET                 (0x00000000)
#define MPI_IOC_STATE_WEADY                 (0x10000000)
#define MPI_IOC_STATE_OPEWATIONAW           (0x20000000)
#define MPI_IOC_STATE_FAUWT                 (0x40000000)

#define MPI_IOC_STATE_MASK                  (0xF0000000)
#define MPI_IOC_STATE_SHIFT                 (28)

/* Fauwt state codes (pwoduct independent wange 0x8000-0xFFFF) */

#define MPI_FAUWT_WEQUEST_MESSAGE_PCI_PAWITY_EWWOW  (0x8111)
#define MPI_FAUWT_WEQUEST_MESSAGE_PCI_BUS_FAUWT     (0x8112)
#define MPI_FAUWT_WEPWY_MESSAGE_PCI_PAWITY_EWWOW    (0x8113)
#define MPI_FAUWT_WEPWY_MESSAGE_PCI_BUS_FAUWT       (0x8114)
#define MPI_FAUWT_DATA_SEND_PCI_PAWITY_EWWOW        (0x8115)
#define MPI_FAUWT_DATA_SEND_PCI_BUS_FAUWT           (0x8116)
#define MPI_FAUWT_DATA_WECEIVE_PCI_PAWITY_EWWOW     (0x8117)
#define MPI_FAUWT_DATA_WECEIVE_PCI_BUS_FAUWT        (0x8118)


/*****************************************************************************
*
*        P C I    S y s t e m    I n t e w f a c e    W e g i s t e w s
*
*****************************************************************************/

/*
 * Defines fow wowking with the System Doowbeww wegistew.
 * Vawues fow doowbeww function codes awe incwuded in the section that defines
 * aww the function codes (fuwthew on in this fiwe).
 */
#define MPI_DOOWBEWW_OFFSET                 (0x00000000)
#define MPI_DOOWBEWW_ACTIVE                 (0x08000000) /* DoowbewwUsed */
#define MPI_DOOWBEWW_USED                   (MPI_DOOWBEWW_ACTIVE)
#define MPI_DOOWBEWW_ACTIVE_SHIFT           (27)
#define MPI_DOOWBEWW_WHO_INIT_MASK          (0x07000000)
#define MPI_DOOWBEWW_WHO_INIT_SHIFT         (24)
#define MPI_DOOWBEWW_FUNCTION_MASK          (0xFF000000)
#define MPI_DOOWBEWW_FUNCTION_SHIFT         (24)
#define MPI_DOOWBEWW_ADD_DWOWDS_MASK        (0x00FF0000)
#define MPI_DOOWBEWW_ADD_DWOWDS_SHIFT       (16)
#define MPI_DOOWBEWW_DATA_MASK              (0x0000FFFF)
#define MPI_DOOWBEWW_FUNCTION_SPECIFIC_MASK (0x0000FFFF)

/* vawues fow Host Buffew Access Contwow doowbeww function */
#define MPI_DB_HPBAC_VAWUE_MASK             (0x0000F000)
#define MPI_DB_HPBAC_ENABWE_ACCESS          (0x01)
#define MPI_DB_HPBAC_DISABWE_ACCESS         (0x02)
#define MPI_DB_HPBAC_FWEE_BUFFEW            (0x03)


#define MPI_WWITE_SEQUENCE_OFFSET           (0x00000004)
#define MPI_WWSEQ_KEY_VAWUE_MASK            (0x0000000F)
#define MPI_WWSEQ_1ST_KEY_VAWUE             (0x04)
#define MPI_WWSEQ_2ND_KEY_VAWUE             (0x0B)
#define MPI_WWSEQ_3WD_KEY_VAWUE             (0x02)
#define MPI_WWSEQ_4TH_KEY_VAWUE             (0x07)
#define MPI_WWSEQ_5TH_KEY_VAWUE             (0x0D)

#define MPI_DIAGNOSTIC_OFFSET               (0x00000008)
#define MPI_DIAG_CWEAW_FWASH_BAD_SIG        (0x00000400)
#define MPI_DIAG_PWEVENT_IOC_BOOT           (0x00000200)
#define MPI_DIAG_DWWE                       (0x00000080)
#define MPI_DIAG_FWASH_BAD_SIG              (0x00000040)
#define MPI_DIAG_WESET_HISTOWY              (0x00000020)
#define MPI_DIAG_WW_ENABWE                  (0x00000010)
#define MPI_DIAG_WESET_ADAPTEW              (0x00000004)
#define MPI_DIAG_DISABWE_AWM                (0x00000002)
#define MPI_DIAG_MEM_ENABWE                 (0x00000001)

#define MPI_TEST_BASE_ADDWESS_OFFSET        (0x0000000C)

#define MPI_DIAG_WW_DATA_OFFSET             (0x00000010)

#define MPI_DIAG_WW_ADDWESS_OFFSET          (0x00000014)

#define MPI_HOST_INTEWWUPT_STATUS_OFFSET    (0x00000030)
#define MPI_HIS_IOP_DOOWBEWW_STATUS         (0x80000000)
#define MPI_HIS_WEPWY_MESSAGE_INTEWWUPT     (0x00000008)
#define MPI_HIS_DOOWBEWW_INTEWWUPT          (0x00000001)

#define MPI_HOST_INTEWWUPT_MASK_OFFSET      (0x00000034)
#define MPI_HIM_WIM                         (0x00000008)
#define MPI_HIM_DIM                         (0x00000001)

#define MPI_WEQUEST_QUEUE_OFFSET            (0x00000040)
#define MPI_WEQUEST_POST_FIFO_OFFSET        (0x00000040)

#define MPI_WEPWY_QUEUE_OFFSET              (0x00000044)
#define MPI_WEPWY_POST_FIFO_OFFSET          (0x00000044)
#define MPI_WEPWY_FWEE_FIFO_OFFSET          (0x00000044)

#define MPI_HI_PWI_WEQUEST_QUEUE_OFFSET     (0x00000048)



/*****************************************************************************
*
*        M e s s a g e    F w a m e    D e s c w i p t o w s
*
*****************************************************************************/

#define MPI_WEQ_MF_DESCWIPTOW_NB_MASK       (0x00000003)
#define MPI_WEQ_MF_DESCWIPTOW_F_BIT         (0x00000004)
#define MPI_WEQ_MF_DESCWIPTOW_ADDWESS_MASK  (0xFFFFFFF8)

#define MPI_ADDWESS_WEPWY_A_BIT             (0x80000000)
#define MPI_ADDWESS_WEPWY_ADDWESS_MASK      (0x7FFFFFFF)

#define MPI_CONTEXT_WEPWY_A_BIT             (0x80000000)
#define MPI_CONTEXT_WEPWY_TYPE_MASK         (0x60000000)
#define MPI_CONTEXT_WEPWY_TYPE_SCSI_INIT    (0x00)
#define MPI_CONTEXT_WEPWY_TYPE_SCSI_TAWGET  (0x01)
#define MPI_CONTEXT_WEPWY_TYPE_WAN          (0x02)
#define MPI_CONTEXT_WEPWY_TYPE_SHIFT        (29)
#define MPI_CONTEXT_WEPWY_CONTEXT_MASK      (0x1FFFFFFF)


/****************************************************************************/
/* Context Wepwy macwos                                                     */
/****************************************************************************/

#define MPI_GET_CONTEXT_WEPWY_TYPE(x)  (((x) & MPI_CONTEXT_WEPWY_TYPE_MASK) \
                                          >> MPI_CONTEXT_WEPWY_TYPE_SHIFT)

#define MPI_SET_CONTEXT_WEPWY_TYPE(x, typ)                                  \
            ((x) = ((x) & ~MPI_CONTEXT_WEPWY_TYPE_MASK) |                   \
                            (((typ) << MPI_CONTEXT_WEPWY_TYPE_SHIFT) &      \
                                        MPI_CONTEXT_WEPWY_TYPE_MASK))


/*****************************************************************************
*
*        M e s s a g e    F u n c t i o n s
*              0x80 -> 0x8F wesewved fow pwivate message use pew pwoduct
*
*
*****************************************************************************/

#define MPI_FUNCTION_SCSI_IO_WEQUEST                (0x00)
#define MPI_FUNCTION_SCSI_TASK_MGMT                 (0x01)
#define MPI_FUNCTION_IOC_INIT                       (0x02)
#define MPI_FUNCTION_IOC_FACTS                      (0x03)
#define MPI_FUNCTION_CONFIG                         (0x04)
#define MPI_FUNCTION_POWT_FACTS                     (0x05)
#define MPI_FUNCTION_POWT_ENABWE                    (0x06)
#define MPI_FUNCTION_EVENT_NOTIFICATION             (0x07)
#define MPI_FUNCTION_EVENT_ACK                      (0x08)
#define MPI_FUNCTION_FW_DOWNWOAD                    (0x09)
#define MPI_FUNCTION_TAWGET_CMD_BUFFEW_POST         (0x0A)
#define MPI_FUNCTION_TAWGET_ASSIST                  (0x0B)
#define MPI_FUNCTION_TAWGET_STATUS_SEND             (0x0C)
#define MPI_FUNCTION_TAWGET_MODE_ABOWT              (0x0D)
#define MPI_FUNCTION_FC_WINK_SWVC_BUF_POST          (0x0E)
#define MPI_FUNCTION_FC_WINK_SWVC_WSP               (0x0F)
#define MPI_FUNCTION_FC_EX_WINK_SWVC_SEND           (0x10)
#define MPI_FUNCTION_FC_ABOWT                       (0x11)
#define MPI_FUNCTION_FW_UPWOAD                      (0x12)
#define MPI_FUNCTION_FC_COMMON_TWANSPOWT_SEND       (0x13)
#define MPI_FUNCTION_FC_PWIMITIVE_SEND              (0x14)

#define MPI_FUNCTION_WAID_ACTION                    (0x15)
#define MPI_FUNCTION_WAID_SCSI_IO_PASSTHWOUGH       (0x16)

#define MPI_FUNCTION_TOOWBOX                        (0x17)

#define MPI_FUNCTION_SCSI_ENCWOSUWE_PWOCESSOW       (0x18)

#define MPI_FUNCTION_MAIWBOX                        (0x19)

#define MPI_FUNCTION_SMP_PASSTHWOUGH                (0x1A)
#define MPI_FUNCTION_SAS_IO_UNIT_CONTWOW            (0x1B)
#define MPI_FUNCTION_SATA_PASSTHWOUGH               (0x1C)

#define MPI_FUNCTION_DIAG_BUFFEW_POST               (0x1D)
#define MPI_FUNCTION_DIAG_WEWEASE                   (0x1E)

#define MPI_FUNCTION_SCSI_IO_32                     (0x1F)

#define MPI_FUNCTION_WAN_SEND                       (0x20)
#define MPI_FUNCTION_WAN_WECEIVE                    (0x21)
#define MPI_FUNCTION_WAN_WESET                      (0x22)

#define MPI_FUNCTION_TAWGET_ASSIST_EXTENDED         (0x23)
#define MPI_FUNCTION_TAWGET_CMD_BUF_BASE_POST       (0x24)
#define MPI_FUNCTION_TAWGET_CMD_BUF_WIST_POST       (0x25)

#define MPI_FUNCTION_INBAND_BUFFEW_POST             (0x28)
#define MPI_FUNCTION_INBAND_SEND                    (0x29)
#define MPI_FUNCTION_INBAND_WSP                     (0x2A)
#define MPI_FUNCTION_INBAND_ABOWT                   (0x2B)

#define MPI_FUNCTION_IOC_MESSAGE_UNIT_WESET         (0x40)
#define MPI_FUNCTION_IO_UNIT_WESET                  (0x41)
#define MPI_FUNCTION_HANDSHAKE                      (0x42)
#define MPI_FUNCTION_WEPWY_FWAME_WEMOVAW            (0x43)
#define MPI_FUNCTION_HOST_PAGEBUF_ACCESS_CONTWOW    (0x44)


/* standawd vewsion fowmat */
typedef stwuct _MPI_VEWSION_STWUCT
{
    U8                      Dev;                        /* 00h */
    U8                      Unit;                       /* 01h */
    U8                      Minow;                      /* 02h */
    U8                      Majow;                      /* 03h */
} MPI_VEWSION_STWUCT, MPI_POINTEW PTW_MPI_VEWSION_STWUCT,
  MpiVewsionStwuct_t, MPI_POINTEW pMpiVewsionStwuct;

typedef union _MPI_VEWSION_FOWMAT
{
    MPI_VEWSION_STWUCT      Stwuct;
    U32                     Wowd;
} MPI_VEWSION_FOWMAT, MPI_POINTEW PTW_MPI_VEWSION_FOWMAT,
  MpiVewsionFowmat_t, MPI_POINTEW pMpiVewsionFowmat_t;


/*****************************************************************************
*
*        S c a t t e w    G a t h e w    E w e m e n t s
*
*****************************************************************************/

/****************************************************************************/
/*  Simpwe ewement stwuctuwes                                               */
/****************************************************************************/

typedef stwuct _SGE_SIMPWE32
{
    U32                     FwagsWength;
    U32                     Addwess;
} SGE_SIMPWE32, MPI_POINTEW PTW_SGE_SIMPWE32,
  SGESimpwe32_t, MPI_POINTEW pSGESimpwe32_t;

typedef stwuct _SGE_SIMPWE64
{
    U32                     FwagsWength;
    U64                     Addwess;
} SGE_SIMPWE64, MPI_POINTEW PTW_SGE_SIMPWE64,
  SGESimpwe64_t, MPI_POINTEW pSGESimpwe64_t;

typedef stwuct _SGE_SIMPWE_UNION
{
    U32                     FwagsWength;
    union
    {
        U32                 Addwess32;
        U64                 Addwess64;
    }u;
} SGE_SIMPWE_UNION, MPI_POINTEW PTW_SGE_SIMPWE_UNION,
  SGESimpweUnion_t, MPI_POINTEW pSGESimpweUnion_t;

/****************************************************************************/
/*  Chain ewement stwuctuwes                                                */
/****************************************************************************/

typedef stwuct _SGE_CHAIN32
{
    U16                     Wength;
    U8                      NextChainOffset;
    U8                      Fwags;
    U32                     Addwess;
} SGE_CHAIN32, MPI_POINTEW PTW_SGE_CHAIN32,
  SGEChain32_t, MPI_POINTEW pSGEChain32_t;

typedef stwuct _SGE_CHAIN64
{
    U16                     Wength;
    U8                      NextChainOffset;
    U8                      Fwags;
    U64                     Addwess;
} SGE_CHAIN64, MPI_POINTEW PTW_SGE_CHAIN64,
  SGEChain64_t, MPI_POINTEW pSGEChain64_t;

typedef stwuct _SGE_CHAIN_UNION
{
    U16                     Wength;
    U8                      NextChainOffset;
    U8                      Fwags;
    union
    {
        U32                 Addwess32;
        U64                 Addwess64;
    }u;
} SGE_CHAIN_UNION, MPI_POINTEW PTW_SGE_CHAIN_UNION,
  SGEChainUnion_t, MPI_POINTEW pSGEChainUnion_t;

/****************************************************************************/
/*  Twansaction Context ewement                                             */
/****************************************************************************/

typedef stwuct _SGE_TWANSACTION32
{
    U8                      Wesewved;
    U8                      ContextSize;
    U8                      DetaiwsWength;
    U8                      Fwags;
    U32                     TwansactionContext;
    U32                     TwansactionDetaiws[];
} SGE_TWANSACTION32, MPI_POINTEW PTW_SGE_TWANSACTION32,
  SGETwansaction32_t, MPI_POINTEW pSGETwansaction32_t;

typedef stwuct _SGE_TWANSACTION64
{
    U8                      Wesewved;
    U8                      ContextSize;
    U8                      DetaiwsWength;
    U8                      Fwags;
    U32                     TwansactionContext[2];
    U32                     TwansactionDetaiws[1];
} SGE_TWANSACTION64, MPI_POINTEW PTW_SGE_TWANSACTION64,
  SGETwansaction64_t, MPI_POINTEW pSGETwansaction64_t;

typedef stwuct _SGE_TWANSACTION96
{
    U8                      Wesewved;
    U8                      ContextSize;
    U8                      DetaiwsWength;
    U8                      Fwags;
    U32                     TwansactionContext[3];
    U32                     TwansactionDetaiws[1];
} SGE_TWANSACTION96, MPI_POINTEW PTW_SGE_TWANSACTION96,
  SGETwansaction96_t, MPI_POINTEW pSGETwansaction96_t;

typedef stwuct _SGE_TWANSACTION128
{
    U8                      Wesewved;
    U8                      ContextSize;
    U8                      DetaiwsWength;
    U8                      Fwags;
    U32                     TwansactionContext[4];
    U32                     TwansactionDetaiws[1];
} SGE_TWANSACTION128, MPI_POINTEW PTW_SGE_TWANSACTION128,
  SGETwansaction_t128, MPI_POINTEW pSGETwansaction_t128;

typedef stwuct _SGE_TWANSACTION_UNION
{
    U8                      Wesewved;
    U8                      ContextSize;
    U8                      DetaiwsWength;
    U8                      Fwags;
    union
    {
        U32                 TwansactionContext32[1];
        U32                 TwansactionContext64[2];
        U32                 TwansactionContext96[3];
        U32                 TwansactionContext128[4];
    }u;
    U32                     TwansactionDetaiws[1];
} SGE_TWANSACTION_UNION, MPI_POINTEW PTW_SGE_TWANSACTION_UNION,
  SGETwansactionUnion_t, MPI_POINTEW pSGETwansactionUnion_t;


/****************************************************************************/
/*  SGE IO types union  fow IO SGW's                                        */
/****************************************************************************/

typedef stwuct _SGE_IO_UNION
{
    union
    {
        SGE_SIMPWE_UNION    Simpwe;
        SGE_CHAIN_UNION     Chain;
    } u;
} SGE_IO_UNION, MPI_POINTEW PTW_SGE_IO_UNION,
  SGEIOUnion_t, MPI_POINTEW pSGEIOUnion_t;

/****************************************************************************/
/*  SGE union fow SGW's with Simpwe and Twansaction ewements                */
/****************************************************************************/

typedef stwuct _SGE_TWANS_SIMPWE_UNION
{
    union
    {
        SGE_SIMPWE_UNION        Simpwe;
        SGE_TWANSACTION_UNION   Twansaction;
    } u;
} SGE_TWANS_SIMPWE_UNION, MPI_POINTEW PTW_SGE_TWANS_SIMPWE_UNION,
  SGETwansSimpweUnion_t, MPI_POINTEW pSGETwansSimpweUnion_t;

/****************************************************************************/
/*  Aww SGE types union                                                     */
/****************************************************************************/

typedef stwuct _SGE_MPI_UNION
{
    union
    {
        SGE_SIMPWE_UNION        Simpwe;
        SGE_CHAIN_UNION         Chain;
        SGE_TWANSACTION_UNION   Twansaction;
    } u;
} SGE_MPI_UNION, MPI_POINTEW PTW_SGE_MPI_UNION,
  MPI_SGE_UNION_t, MPI_POINTEW pMPI_SGE_UNION_t,
  SGEAwwUnion_t, MPI_POINTEW pSGEAwwUnion_t;


/****************************************************************************/
/*  SGE fiewd definition and masks                                          */
/****************************************************************************/

/* Fwags fiewd bit definitions */

#define MPI_SGE_FWAGS_WAST_EWEMENT              (0x80)
#define MPI_SGE_FWAGS_END_OF_BUFFEW             (0x40)
#define MPI_SGE_FWAGS_EWEMENT_TYPE_MASK         (0x30)
#define MPI_SGE_FWAGS_WOCAW_ADDWESS             (0x08)
#define MPI_SGE_FWAGS_DIWECTION                 (0x04)
#define MPI_SGE_FWAGS_ADDWESS_SIZE              (0x02)
#define MPI_SGE_FWAGS_END_OF_WIST               (0x01)

#define MPI_SGE_FWAGS_SHIFT                     (24)

#define MPI_SGE_WENGTH_MASK                     (0x00FFFFFF)
#define MPI_SGE_CHAIN_WENGTH_MASK               (0x0000FFFF)

/* Ewement Type */

#define MPI_SGE_FWAGS_TWANSACTION_EWEMENT       (0x00)
#define MPI_SGE_FWAGS_SIMPWE_EWEMENT            (0x10)
#define MPI_SGE_FWAGS_CHAIN_EWEMENT             (0x30)
#define MPI_SGE_FWAGS_EWEMENT_MASK              (0x30)

/* Addwess wocation */

#define MPI_SGE_FWAGS_SYSTEM_ADDWESS            (0x00)

/* Diwection */

#define MPI_SGE_FWAGS_IOC_TO_HOST               (0x00)
#define MPI_SGE_FWAGS_HOST_TO_IOC               (0x04)

/* Addwess Size */

#define MPI_SGE_FWAGS_32_BIT_ADDWESSING         (0x00)
#define MPI_SGE_FWAGS_64_BIT_ADDWESSING         (0x02)

/* Context Size */

#define MPI_SGE_FWAGS_32_BIT_CONTEXT            (0x00)
#define MPI_SGE_FWAGS_64_BIT_CONTEXT            (0x02)
#define MPI_SGE_FWAGS_96_BIT_CONTEXT            (0x04)
#define MPI_SGE_FWAGS_128_BIT_CONTEXT           (0x06)

#define MPI_SGE_CHAIN_OFFSET_MASK               (0x00FF0000)
#define MPI_SGE_CHAIN_OFFSET_SHIFT              (16)


/****************************************************************************/
/*  SGE opewation Macwos                                                    */
/****************************************************************************/

         /* SIMPWE FwagsWength manipuwations... */
#define  MPI_SGE_SET_FWAGS(f)           ((U32)(f) << MPI_SGE_FWAGS_SHIFT)
#define  MPI_SGE_GET_FWAGS(fw)          (((fw) & ~MPI_SGE_WENGTH_MASK) >> MPI_SGE_FWAGS_SHIFT)
#define  MPI_SGE_WENGTH(fw)             ((fw) & MPI_SGE_WENGTH_MASK)
#define  MPI_SGE_CHAIN_WENGTH(fw)       ((fw) & MPI_SGE_CHAIN_WENGTH_MASK)

#define  MPI_SGE_SET_FWAGS_WENGTH(f,w)  (MPI_SGE_SET_FWAGS(f) | MPI_SGE_WENGTH(w))

#define  MPI_pSGE_GET_FWAGS(psg)        MPI_SGE_GET_FWAGS((psg)->FwagsWength)
#define  MPI_pSGE_GET_WENGTH(psg)       MPI_SGE_WENGTH((psg)->FwagsWength)
#define  MPI_pSGE_SET_FWAGS_WENGTH(psg,f,w)  (psg)->FwagsWength = MPI_SGE_SET_FWAGS_WENGTH(f,w)
         /* CAUTION - The fowwowing awe WEAD-MODIFY-WWITE! */
#define  MPI_pSGE_SET_FWAGS(psg,f)      (psg)->FwagsWength |= MPI_SGE_SET_FWAGS(f)
#define  MPI_pSGE_SET_WENGTH(psg,w)     (psg)->FwagsWength |= MPI_SGE_WENGTH(w)

#define  MPI_GET_CHAIN_OFFSET(x) ((x&MPI_SGE_CHAIN_OFFSET_MASK)>>MPI_SGE_CHAIN_OFFSET_SHIFT)



/*****************************************************************************
*
*        S t a n d a w d    M e s s a g e    S t w u c t u w e s
*
*****************************************************************************/

/****************************************************************************/
/* Standawd message wequest headew fow aww wequest messages                 */
/****************************************************************************/

typedef stwuct _MSG_WEQUEST_HEADEW
{
    U8                      Wesewved[2];      /* function specific */
    U8                      ChainOffset;
    U8                      Function;
    U8                      Wesewved1[3];     /* function specific */
    U8                      MsgFwags;
    U32                     MsgContext;
} MSG_WEQUEST_HEADEW, MPI_POINTEW PTW_MSG_WEQUEST_HEADEW,
  MPIHeadew_t, MPI_POINTEW pMPIHeadew_t;


/****************************************************************************/
/*  Defauwt Wepwy                                                           */
/****************************************************************************/

typedef stwuct _MSG_DEFAUWT_WEPWY
{
    U8                      Wesewved[2];      /* function specific */
    U8                      MsgWength;
    U8                      Function;
    U8                      Wesewved1[3];     /* function specific */
    U8                      MsgFwags;
    U32                     MsgContext;
    U8                      Wesewved2[2];     /* function specific */
    U16                     IOCStatus;
    U32                     IOCWogInfo;
} MSG_DEFAUWT_WEPWY, MPI_POINTEW PTW_MSG_DEFAUWT_WEPWY,
  MPIDefauwtWepwy_t, MPI_POINTEW pMPIDefauwtWepwy_t;


/* MsgFwags definition fow aww wepwies */

#define MPI_MSGFWAGS_CONTINUATION_WEPWY         (0x80)


/*****************************************************************************
*
*               I O C    S t a t u s   V a w u e s
*
*****************************************************************************/

/****************************************************************************/
/*  Common IOCStatus vawues fow aww wepwies                                 */
/****************************************************************************/

#define MPI_IOCSTATUS_SUCCESS                   (0x0000)
#define MPI_IOCSTATUS_INVAWID_FUNCTION          (0x0001)
#define MPI_IOCSTATUS_BUSY                      (0x0002)
#define MPI_IOCSTATUS_INVAWID_SGW               (0x0003)
#define MPI_IOCSTATUS_INTEWNAW_EWWOW            (0x0004)
#define MPI_IOCSTATUS_WESEWVED                  (0x0005)
#define MPI_IOCSTATUS_INSUFFICIENT_WESOUWCES    (0x0006)
#define MPI_IOCSTATUS_INVAWID_FIEWD             (0x0007)
#define MPI_IOCSTATUS_INVAWID_STATE             (0x0008)
#define MPI_IOCSTATUS_OP_STATE_NOT_SUPPOWTED    (0x0009)

/****************************************************************************/
/*  Config IOCStatus vawues                                                 */
/****************************************************************************/

#define MPI_IOCSTATUS_CONFIG_INVAWID_ACTION     (0x0020)
#define MPI_IOCSTATUS_CONFIG_INVAWID_TYPE       (0x0021)
#define MPI_IOCSTATUS_CONFIG_INVAWID_PAGE       (0x0022)
#define MPI_IOCSTATUS_CONFIG_INVAWID_DATA       (0x0023)
#define MPI_IOCSTATUS_CONFIG_NO_DEFAUWTS        (0x0024)
#define MPI_IOCSTATUS_CONFIG_CANT_COMMIT        (0x0025)

/****************************************************************************/
/*  SCSIIO Wepwy (SPI & FCP) initiatow vawues                               */
/****************************************************************************/

#define MPI_IOCSTATUS_SCSI_WECOVEWED_EWWOW      (0x0040)
#define MPI_IOCSTATUS_SCSI_INVAWID_BUS          (0x0041)
#define MPI_IOCSTATUS_SCSI_INVAWID_TAWGETID     (0x0042)
#define MPI_IOCSTATUS_SCSI_DEVICE_NOT_THEWE     (0x0043)
#define MPI_IOCSTATUS_SCSI_DATA_OVEWWUN         (0x0044)
#define MPI_IOCSTATUS_SCSI_DATA_UNDEWWUN        (0x0045)
#define MPI_IOCSTATUS_SCSI_IO_DATA_EWWOW        (0x0046)
#define MPI_IOCSTATUS_SCSI_PWOTOCOW_EWWOW       (0x0047)
#define MPI_IOCSTATUS_SCSI_TASK_TEWMINATED      (0x0048)
#define MPI_IOCSTATUS_SCSI_WESIDUAW_MISMATCH    (0x0049)
#define MPI_IOCSTATUS_SCSI_TASK_MGMT_FAIWED     (0x004A)
#define MPI_IOCSTATUS_SCSI_IOC_TEWMINATED       (0x004B)
#define MPI_IOCSTATUS_SCSI_EXT_TEWMINATED       (0x004C)

/****************************************************************************/
/*  Fow use by SCSI Initiatow and SCSI Tawget end-to-end data pwotection    */
/****************************************************************************/

#define MPI_IOCSTATUS_EEDP_GUAWD_EWWOW          (0x004D)
#define MPI_IOCSTATUS_EEDP_WEF_TAG_EWWOW        (0x004E)
#define MPI_IOCSTATUS_EEDP_APP_TAG_EWWOW        (0x004F)


/****************************************************************************/
/*  SCSI Tawget vawues                                                      */
/****************************************************************************/

#define MPI_IOCSTATUS_TAWGET_PWIOWITY_IO         (0x0060)
#define MPI_IOCSTATUS_TAWGET_INVAWID_POWT        (0x0061)
#define MPI_IOCSTATUS_TAWGET_INVAWID_IOCINDEX    (0x0062)   /* obsowete name */
#define MPI_IOCSTATUS_TAWGET_INVAWID_IO_INDEX    (0x0062)
#define MPI_IOCSTATUS_TAWGET_ABOWTED             (0x0063)
#define MPI_IOCSTATUS_TAWGET_NO_CONN_WETWYABWE   (0x0064)
#define MPI_IOCSTATUS_TAWGET_NO_CONNECTION       (0x0065)
#define MPI_IOCSTATUS_TAWGET_XFEW_COUNT_MISMATCH (0x006A)
#define MPI_IOCSTATUS_TAWGET_STS_DATA_NOT_SENT   (0x006B)
#define MPI_IOCSTATUS_TAWGET_DATA_OFFSET_EWWOW   (0x006D)
#define MPI_IOCSTATUS_TAWGET_TOO_MUCH_WWITE_DATA (0x006E)
#define MPI_IOCSTATUS_TAWGET_IU_TOO_SHOWT        (0x006F)
#define MPI_IOCSTATUS_TAWGET_ACK_NAK_TIMEOUT     (0x0070)
#define MPI_IOCSTATUS_TAWGET_NAK_WECEIVED        (0x0071)

/****************************************************************************/
/*  Additionaw FCP tawget vawues (obsowete)                                 */
/****************************************************************************/

#define MPI_IOCSTATUS_TAWGET_FC_ABOWTED         (0x0066)    /* obsowete */
#define MPI_IOCSTATUS_TAWGET_FC_WX_ID_INVAWID   (0x0067)    /* obsowete */
#define MPI_IOCSTATUS_TAWGET_FC_DID_INVAWID     (0x0068)    /* obsowete */
#define MPI_IOCSTATUS_TAWGET_FC_NODE_WOGGED_OUT (0x0069)    /* obsowete */

/****************************************************************************/
/*  Fibwe Channew Diwect Access vawues                                      */
/****************************************************************************/

#define MPI_IOCSTATUS_FC_ABOWTED                (0x0066)
#define MPI_IOCSTATUS_FC_WX_ID_INVAWID          (0x0067)
#define MPI_IOCSTATUS_FC_DID_INVAWID            (0x0068)
#define MPI_IOCSTATUS_FC_NODE_WOGGED_OUT        (0x0069)
#define MPI_IOCSTATUS_FC_EXCHANGE_CANCEWED      (0x006C)

/****************************************************************************/
/*  WAN vawues                                                              */
/****************************************************************************/

#define MPI_IOCSTATUS_WAN_DEVICE_NOT_FOUND      (0x0080)
#define MPI_IOCSTATUS_WAN_DEVICE_FAIWUWE        (0x0081)
#define MPI_IOCSTATUS_WAN_TWANSMIT_EWWOW        (0x0082)
#define MPI_IOCSTATUS_WAN_TWANSMIT_ABOWTED      (0x0083)
#define MPI_IOCSTATUS_WAN_WECEIVE_EWWOW         (0x0084)
#define MPI_IOCSTATUS_WAN_WECEIVE_ABOWTED       (0x0085)
#define MPI_IOCSTATUS_WAN_PAWTIAW_PACKET        (0x0086)
#define MPI_IOCSTATUS_WAN_CANCEWED              (0x0087)

/****************************************************************************/
/*  Sewiaw Attached SCSI vawues                                             */
/****************************************************************************/

#define MPI_IOCSTATUS_SAS_SMP_WEQUEST_FAIWED    (0x0090)
#define MPI_IOCSTATUS_SAS_SMP_DATA_OVEWWUN      (0x0091)

/****************************************************************************/
/*  Inband vawues                                                           */
/****************************************************************************/

#define MPI_IOCSTATUS_INBAND_ABOWTED            (0x0098)
#define MPI_IOCSTATUS_INBAND_NO_CONNECTION      (0x0099)

/****************************************************************************/
/*  Diagnostic Toows vawues                                                 */
/****************************************************************************/

#define MPI_IOCSTATUS_DIAGNOSTIC_WEWEASED       (0x00A0)


/****************************************************************************/
/*  IOCStatus fwag to indicate that wog info is avaiwabwe                   */
/****************************************************************************/

#define MPI_IOCSTATUS_FWAG_WOG_INFO_AVAIWABWE   (0x8000)
#define MPI_IOCSTATUS_MASK                      (0x7FFF)

/****************************************************************************/
/*  WogInfo Types                                                           */
/****************************************************************************/

#define MPI_IOCWOGINFO_TYPE_MASK                (0xF0000000)
#define MPI_IOCWOGINFO_TYPE_SHIFT               (28)
#define MPI_IOCWOGINFO_TYPE_NONE                (0x0)
#define MPI_IOCWOGINFO_TYPE_SCSI                (0x1)
#define MPI_IOCWOGINFO_TYPE_FC                  (0x2)
#define MPI_IOCWOGINFO_TYPE_SAS                 (0x3)
#define MPI_IOCWOGINFO_TYPE_ISCSI               (0x4)
#define MPI_IOCWOGINFO_WOG_DATA_MASK            (0x0FFFFFFF)


#endif
