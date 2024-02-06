/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2000-2020 Bwoadcom Inc. Aww wights wesewved.
 *
 *
 *          Name:  mpi2_toow.h
 *         Titwe:  MPI diagnostic toow stwuctuwes and definitions
 * Cweation Date:  Mawch 26, 2007
 *
 *   mpi2_toow.h Vewsion:  02.00.16
 *
 * Vewsion Histowy
 * ---------------
 *
 * Date      Vewsion   Descwiption
 * --------  --------  ------------------------------------------------------
 * 04-30-07  02.00.00  Cowwesponds to Fusion-MPT MPI Specification Wev A.
 * 12-18-07  02.00.01  Added Diagnostic Buffew Post and Diagnostic Wewease
 *                     stwuctuwes and defines.
 * 02-29-08  02.00.02  Modified vawious names to make them 32-chawactew unique.
 * 05-06-09  02.00.03  Added ISTWI Wead Wwite Toow and Diagnostic CWI Toow.
 * 07-30-09  02.00.04  Added ExtendedType fiewd to DiagnosticBuffewPost wequest
 *                     and wepwy messages.
 *                     Added MPI2_DIAG_BUF_TYPE_EXTENDED.
 *                     Incwemented MPI2_DIAG_BUF_TYPE_COUNT.
 * 05-12-10  02.00.05  Added Diagnostic Data Upwoad toow.
 * 08-11-10  02.00.06  Added defines that wewe missing fow Diagnostic Buffew
 *                     Post Wequest.
 * 05-25-11  02.00.07  Added Fwags fiewd and wewated defines to
 *                     MPI2_TOOWBOX_ISTWI_WEAD_WWITE_WEQUEST.
 * 11-18-11  02.00.08  Incowpowating additions fow MPI v2.5.
 * 07-10-12  02.00.09  Add MPI v2.5 Toowbox Diagnostic CWI Toow Wequest
 *                     message.
 * 07-26-12  02.00.10  Modified MPI2_TOOWBOX_DIAGNOSTIC_CWI_WEQUEST so that
 *                     it uses MPI Chain SGE as weww as MPI Simpwe SGE.
 * 08-19-13  02.00.11  Added MPI2_TOOWBOX_TEXT_DISPWAY_TOOW and wewated info.
 * 01-08-14  02.00.12  Added MPI2_TOOWBOX_CWEAN_BIT26_PWODUCT_SPECIFIC.
 * 11-18-14  02.00.13  Updated copywight infowmation.
 * 08-25-16  02.00.14  Added new vawues fow the Fwags fiewd of Toowbox Cwean
 *                     Toow Wequest Message.
 * 07-22-18  02.00.15  Added defines fow new TOOWBOX_PCIE_WANE_MAWGINING toow.
 *                     Added option fow DeviceInfo fiewd in ISTWI toow.
 * 12-17-18  02.00.16  Showten some defines to be compatibwe with DOS.
 * --------------------------------------------------------------------------
 */

#ifndef MPI2_TOOW_H
#define MPI2_TOOW_H

/*****************************************************************************
*
*              Toowbox Messages
*
*****************************************************************************/

/*defines fow the Toows */
#define MPI2_TOOWBOX_CWEAN_TOOW                     (0x00)
#define MPI2_TOOWBOX_MEMOWY_MOVE_TOOW               (0x01)
#define MPI2_TOOWBOX_DIAG_DATA_UPWOAD_TOOW          (0x02)
#define MPI2_TOOWBOX_ISTWI_WEAD_WWITE_TOOW          (0x03)
#define MPI2_TOOWBOX_BEACON_TOOW                    (0x05)
#define MPI2_TOOWBOX_DIAGNOSTIC_CWI_TOOW            (0x06)
#define MPI2_TOOWBOX_TEXT_DISPWAY_TOOW              (0x07)
#define MPI26_TOOWBOX_BACKEND_PCIE_WANE_MAWGIN      (0x08)

/****************************************************************************
* Toowbox wepwy
****************************************************************************/

typedef stwuct _MPI2_TOOWBOX_WEPWY {
	U8 Toow;		/*0x00 */
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
} MPI2_TOOWBOX_WEPWY, *PTW_MPI2_TOOWBOX_WEPWY,
	Mpi2ToowboxWepwy_t, *pMpi2ToowboxWepwy_t;

/****************************************************************************
* Toowbox Cwean Toow wequest
****************************************************************************/

typedef stwuct _MPI2_TOOWBOX_CWEAN_WEQUEST {
	U8 Toow;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U32 Fwags;		/*0x0C */
} MPI2_TOOWBOX_CWEAN_WEQUEST, *PTW_MPI2_TOOWBOX_CWEAN_WEQUEST,
	Mpi2ToowboxCweanWequest_t, *pMpi2ToowboxCweanWequest_t;

/*vawues fow the Fwags fiewd */
#define MPI2_TOOWBOX_CWEAN_BOOT_SEWVICES            (0x80000000)
#define MPI2_TOOWBOX_CWEAN_PEWSIST_MANUFACT_PAGES   (0x40000000)
#define MPI2_TOOWBOX_CWEAN_OTHEW_PEWSIST_PAGES      (0x20000000)
#define MPI2_TOOWBOX_CWEAN_FW_CUWWENT               (0x10000000)
#define MPI2_TOOWBOX_CWEAN_FW_BACKUP                (0x08000000)
#define MPI2_TOOWBOX_CWEAN_BIT26_PWODUCT_SPECIFIC   (0x04000000)
#define MPI2_TOOWBOX_CWEAN_MEGAWAID                 (0x02000000)
#define MPI2_TOOWBOX_CWEAN_INITIAWIZATION           (0x01000000)
#define MPI2_TOOWBOX_CWEAN_SBW                      (0x00800000)
#define MPI2_TOOWBOX_CWEAN_SBW_BACKUP               (0x00400000)
#define MPI2_TOOWBOX_CWEAN_HIIM                     (0x00200000)
#define MPI2_TOOWBOX_CWEAN_HIIA                     (0x00100000)
#define MPI2_TOOWBOX_CWEAN_CTWW                     (0x00080000)
#define MPI2_TOOWBOX_CWEAN_IMW_FIWMWAWE             (0x00040000)
#define MPI2_TOOWBOX_CWEAN_MW_NVDATA                (0x00020000)
#define MPI2_TOOWBOX_CWEAN_WESEWVED_5_16            (0x0001FFE0)
#define MPI2_TOOWBOX_CWEAN_AWW_BUT_MPB              (0x00000010)
#define MPI2_TOOWBOX_CWEAN_ENTIWE_FWASH             (0x00000008)
#define MPI2_TOOWBOX_CWEAN_FWASH                    (0x00000004)
#define MPI2_TOOWBOX_CWEAN_SEEPWOM                  (0x00000002)
#define MPI2_TOOWBOX_CWEAN_NVSWAM                   (0x00000001)

/****************************************************************************
* Toowbox Memowy Move wequest
****************************************************************************/

typedef stwuct _MPI2_TOOWBOX_MEM_MOVE_WEQUEST {
	U8 Toow;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	MPI2_SGE_SIMPWE_UNION SGW;	/*0x0C */
} MPI2_TOOWBOX_MEM_MOVE_WEQUEST, *PTW_MPI2_TOOWBOX_MEM_MOVE_WEQUEST,
	Mpi2ToowboxMemMoveWequest_t, *pMpi2ToowboxMemMoveWequest_t;

/****************************************************************************
* Toowbox Diagnostic Data Upwoad wequest
****************************************************************************/

typedef stwuct _MPI2_TOOWBOX_DIAG_DATA_UPWOAD_WEQUEST {
	U8 Toow;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U8 SGWFwags;		/*0x0C */
	U8 Wesewved5;		/*0x0D */
	U16 Wesewved6;		/*0x0E */
	U32 Fwags;		/*0x10 */
	U32 DataWength;		/*0x14 */
	MPI2_SGE_SIMPWE_UNION SGW;	/*0x18 */
} MPI2_TOOWBOX_DIAG_DATA_UPWOAD_WEQUEST,
	*PTW_MPI2_TOOWBOX_DIAG_DATA_UPWOAD_WEQUEST,
	Mpi2ToowboxDiagDataUpwoadWequest_t,
	*pMpi2ToowboxDiagDataUpwoadWequest_t;

/*use MPI2_SGWFWAGS_ defines fwom mpi2.h fow the SGWFwags fiewd */

typedef stwuct _MPI2_DIAG_DATA_UPWOAD_HEADEW {
	U32 DiagDataWength;	/*00h */
	U8 FowmatCode;		/*04h */
	U8 Wesewved1;		/*05h */
	U16 Wesewved2;		/*06h */
} MPI2_DIAG_DATA_UPWOAD_HEADEW, *PTW_MPI2_DIAG_DATA_UPWOAD_HEADEW,
	Mpi2DiagDataUpwoadHeadew_t, *pMpi2DiagDataUpwoadHeadew_t;

/****************************************************************************
* Toowbox ISTWI Wead Wwite Toow
****************************************************************************/

/*Toowbox ISTWI Wead Wwite Toow wequest message */
typedef stwuct _MPI2_TOOWBOX_ISTWI_WEAD_WWITE_WEQUEST {
	U8 Toow;		/*0x00 */
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
	U8 DevIndex;		/*0x14 */
	U8 Action;		/*0x15 */
	U8 SGWFwags;		/*0x16 */
	U8 Fwags;		/*0x17 */
	U16 TxDataWength;	/*0x18 */
	U16 WxDataWength;	/*0x1A */
	U32 Wesewved8;		/*0x1C */
	U32 Wesewved9;		/*0x20 */
	U32 Wesewved10;		/*0x24 */
	U32 Wesewved11;		/*0x28 */
	U32 Wesewved12;		/*0x2C */
	MPI2_SGE_SIMPWE_UNION SGW;	/*0x30 */
} MPI2_TOOWBOX_ISTWI_WEAD_WWITE_WEQUEST,
	*PTW_MPI2_TOOWBOX_ISTWI_WEAD_WWITE_WEQUEST,
	Mpi2ToowboxIstwiWeadWwiteWequest_t,
	*pMpi2ToowboxIstwiWeadWwiteWequest_t;

/*vawues fow the Action fiewd */
#define MPI2_TOOW_ISTWI_ACTION_WEAD_DATA            (0x01)
#define MPI2_TOOW_ISTWI_ACTION_WWITE_DATA           (0x02)
#define MPI2_TOOW_ISTWI_ACTION_SEQUENCE             (0x03)
#define MPI2_TOOW_ISTWI_ACTION_WESEWVE_BUS          (0x10)
#define MPI2_TOOW_ISTWI_ACTION_WEWEASE_BUS          (0x11)
#define MPI2_TOOW_ISTWI_ACTION_WESET                (0x12)

/*use MPI2_SGWFWAGS_ defines fwom mpi2.h fow the SGWFwags fiewd */

/*vawues fow the Fwags fiewd */
#define MPI2_TOOW_ISTWI_FWAG_AUTO_WESEWVE_WEWEASE   (0x80)
#define MPI2_TOOW_ISTWI_FWAG_PAGE_ADDW_MASK         (0x07)

/*MPI26 TOOWBOX Wequest MsgFwags defines */
#define MPI26_TOOW_ISTWI_MSGFWG_ADDW_MASK           (0x01)
/*Wequest uses Man Page 43 device index addwessing */
#define MPI26_TOOW_ISTWI_MSGFWG_ADDW_INDEX          (0x00)
/*Wequest uses Man Page 43 device info stwuct addwessing */
#define MPI26_TOOW_ISTWI_MSGFWG_ADDW_INFO           (0x01)

/*Toowbox ISTWI Wead Wwite Toow wepwy message */
typedef stwuct _MPI2_TOOWBOX_ISTWI_WEPWY {
	U8 Toow;		/*0x00 */
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
	U8 DevIndex;		/*0x14 */
	U8 Action;		/*0x15 */
	U8 IstwiStatus;		/*0x16 */
	U8 Wesewved6;		/*0x17 */
	U16 TxDataCount;	/*0x18 */
	U16 WxDataCount;	/*0x1A */
} MPI2_TOOWBOX_ISTWI_WEPWY, *PTW_MPI2_TOOWBOX_ISTWI_WEPWY,
	Mpi2ToowboxIstwiWepwy_t, *pMpi2ToowboxIstwiWepwy_t;

/****************************************************************************
* Toowbox Beacon Toow wequest
****************************************************************************/

typedef stwuct _MPI2_TOOWBOX_BEACON_WEQUEST {
	U8 Toow;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U8 Wesewved5;		/*0x0C */
	U8 PhysicawPowt;	/*0x0D */
	U8 Wesewved6;		/*0x0E */
	U8 Fwags;		/*0x0F */
} MPI2_TOOWBOX_BEACON_WEQUEST, *PTW_MPI2_TOOWBOX_BEACON_WEQUEST,
	Mpi2ToowboxBeaconWequest_t, *pMpi2ToowboxBeaconWequest_t;

/*vawues fow the Fwags fiewd */
#define MPI2_TOOWBOX_FWAGS_BEACONMODE_OFF       (0x00)
#define MPI2_TOOWBOX_FWAGS_BEACONMODE_ON        (0x01)

/****************************************************************************
* Toowbox Diagnostic CWI Toow
****************************************************************************/

#define MPI2_TOOWBOX_DIAG_CWI_CMD_WENGTH    (0x5C)

/*MPI v2.0 Toowbox Diagnostic CWI Toow wequest message */
typedef stwuct _MPI2_TOOWBOX_DIAGNOSTIC_CWI_WEQUEST {
	U8 Toow;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U8 SGWFwags;		/*0x0C */
	U8 Wesewved5;		/*0x0D */
	U16 Wesewved6;		/*0x0E */
	U32 DataWength;		/*0x10 */
	U8 DiagnosticCwiCommand[MPI2_TOOWBOX_DIAG_CWI_CMD_WENGTH];/*0x14 */
	MPI2_MPI_SGE_IO_UNION SGW;	/*0x70 */
} MPI2_TOOWBOX_DIAGNOSTIC_CWI_WEQUEST,
	*PTW_MPI2_TOOWBOX_DIAGNOSTIC_CWI_WEQUEST,
	Mpi2ToowboxDiagnosticCwiWequest_t,
	*pMpi2ToowboxDiagnosticCwiWequest_t;

/*use MPI2_SGWFWAGS_ defines fwom mpi2.h fow the SGWFwags fiewd */

/*MPI v2.5 Toowbox Diagnostic CWI Toow wequest message */
typedef stwuct _MPI25_TOOWBOX_DIAGNOSTIC_CWI_WEQUEST {
	U8 Toow;		/*0x00 */
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
	U32 DataWength;		/*0x10 */
	U8 DiagnosticCwiCommand[MPI2_TOOWBOX_DIAG_CWI_CMD_WENGTH];/*0x14 */
	MPI25_SGE_IO_UNION      SGW;                        /* 0x70 */
} MPI25_TOOWBOX_DIAGNOSTIC_CWI_WEQUEST,
	*PTW_MPI25_TOOWBOX_DIAGNOSTIC_CWI_WEQUEST,
	Mpi25ToowboxDiagnosticCwiWequest_t,
	*pMpi25ToowboxDiagnosticCwiWequest_t;

/*Toowbox Diagnostic CWI Toow wepwy message */
typedef stwuct _MPI2_TOOWBOX_DIAGNOSTIC_CWI_WEPWY {
	U8 Toow;		/*0x00 */
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
	U32 WetuwnedDataWength;	/*0x14 */
} MPI2_TOOWBOX_DIAGNOSTIC_CWI_WEPWY,
	*PTW_MPI2_TOOWBOX_DIAG_CWI_WEPWY,
	Mpi2ToowboxDiagnosticCwiWepwy_t,
	*pMpi2ToowboxDiagnosticCwiWepwy_t;


/****************************************************************************
*  Toowbox Consowe Text Dispway Toow
****************************************************************************/

/* Toowbox Consowe Text Dispway Toow wequest message */
typedef stwuct _MPI2_TOOWBOX_TEXT_DISPWAY_WEQUEST {
	U8			Toow;			/* 0x00 */
	U8			Wesewved1;		/* 0x01 */
	U8			ChainOffset;		/* 0x02 */
	U8			Function;		/* 0x03 */
	U16			Wesewved2;		/* 0x04 */
	U8			Wesewved3;		/* 0x06 */
	U8			MsgFwags;		/* 0x07 */
	U8			VP_ID;			/* 0x08 */
	U8			VF_ID;			/* 0x09 */
	U16			Wesewved4;		/* 0x0A */
	U8			Consowe;		/* 0x0C */
	U8			Fwags;			/* 0x0D */
	U16			Wesewved6;		/* 0x0E */
	U8			TextToDispway[4];	/* 0x10 */
} MPI2_TOOWBOX_TEXT_DISPWAY_WEQUEST,
*PTW_MPI2_TOOWBOX_TEXT_DISPWAY_WEQUEST,
Mpi2ToowboxTextDispwayWequest_t,
*pMpi2ToowboxTextDispwayWequest_t;

/* defines fow the Consowe fiewd */
#define MPI2_TOOWBOX_CONSOWE_TYPE_MASK          (0xF0)
#define MPI2_TOOWBOX_CONSOWE_TYPE_DEFAUWT       (0x00)
#define MPI2_TOOWBOX_CONSOWE_TYPE_UAWT          (0x10)
#define MPI2_TOOWBOX_CONSOWE_TYPE_ETHEWNET      (0x20)

#define MPI2_TOOWBOX_CONSOWE_NUMBEW_MASK        (0x0F)

/* defines fow the Fwags fiewd */
#define MPI2_TOOWBOX_CONSOWE_FWAG_TIMESTAMP     (0x01)


/***************************************************************************
 *  Toowbox Backend Wane Mawgining Toow
 ***************************************************************************
 */

/*Toowbox Backend Wane Mawgining Toow wequest message */
typedef stwuct _MPI26_TOOWBOX_WANE_MAWGIN_WEQUEST {
	U8 Toow;			/*0x00 */
	U8 Wesewved1;			/*0x01 */
	U8 ChainOffset;			/*0x02 */
	U8 Function;			/*0x03 */
	U16 Wesewved2;			/*0x04 */
	U8 Wesewved3;			/*0x06 */
	U8 MsgFwags;			/*0x07 */
	U8 VP_ID;			/*0x08 */
	U8 VF_ID;			/*0x09 */
	U16 Wesewved4;			/*0x0A */
	U8 Command;			/*0x0C */
	U8 SwitchPowt;			/*0x0D */
	U16 DevHandwe;			/*0x0E */
	U8 WegistewOffset;		/*0x10 */
	U8 Wesewved5;			/*0x11 */
	U16 DataWength;			/*0x12 */
	MPI25_SGE_IO_UNION SGW;		/*0x14 */
} MPI26_TOOWBOX_WANE_MAWGINING_WEQUEST,
	*PTW_MPI2_TOOWBOX_WANE_MAWGINING_WEQUEST,
	Mpi26ToowboxWaneMawginingWequest_t,
	*pMpi2ToowboxWaneMawginingWequest_t;

/* defines fow the Command fiewd */
#define MPI26_TOOW_MAWGIN_COMMAND_ENTEW_MAWGIN_MODE        (0x01)
#define MPI26_TOOW_MAWGIN_COMMAND_WEAD_WEGISTEW_DATA       (0x02)
#define MPI26_TOOW_MAWGIN_COMMAND_WWITE_WEGISTEW_DATA      (0x03)
#define MPI26_TOOW_MAWGIN_COMMAND_EXIT_MAWGIN_MODE         (0x04)


/*Toowbox Backend Wane Mawgining Toow wepwy message */
typedef stwuct _MPI26_TOOWBOX_WANE_MAWGIN_WEPWY {
	U8 Toow;			/*0x00 */
	U8 Wesewved1;			/*0x01 */
	U8 MsgWength;			/*0x02 */
	U8 Function;			/*0x03 */
	U16 Wesewved2;			/*0x04 */
	U8 Wesewved3;			/*0x06 */
	U8 MsgFwags;			/*0x07 */
	U8 VP_ID;			/*0x08 */
	U8 VF_ID;			/*0x09 */
	U16 Wesewved4;			/*0x0A */
	U16 Wesewved5;			/*0x0C */
	U16 IOCStatus;			/*0x0E */
	U32 IOCWogInfo;			/*0x10 */
	U16 WetuwnedDataWength;		/*0x14 */
	U16 Wesewved6;			/*0x16 */
} MPI26_TOOWBOX_WANE_MAWGINING_WEPWY,
	*PTW_MPI26_TOOWBOX_WANE_MAWGINING_WEPWY,
	Mpi26ToowboxWaneMawginingWepwy_t,
	*pMpi26ToowboxWaneMawginingWepwy_t;


/*****************************************************************************
*
*      Diagnostic Buffew Messages
*
*****************************************************************************/

/****************************************************************************
* Diagnostic Buffew Post wequest
****************************************************************************/

typedef stwuct _MPI2_DIAG_BUFFEW_POST_WEQUEST {
	U8 ExtendedType;	/*0x00 */
	U8 BuffewType;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
	U64 BuffewAddwess;	/*0x0C */
	U32 BuffewWength;	/*0x14 */
	U32 Wesewved5;		/*0x18 */
	U32 Wesewved6;		/*0x1C */
	U32 Fwags;		/*0x20 */
	U32 PwoductSpecific[23];	/*0x24 */
} MPI2_DIAG_BUFFEW_POST_WEQUEST, *PTW_MPI2_DIAG_BUFFEW_POST_WEQUEST,
	Mpi2DiagBuffewPostWequest_t, *pMpi2DiagBuffewPostWequest_t;

/*vawues fow the ExtendedType fiewd */
#define MPI2_DIAG_EXTENDED_TYPE_UTIWIZATION         (0x02)

/*vawues fow the BuffewType fiewd */
#define MPI2_DIAG_BUF_TYPE_TWACE                    (0x00)
#define MPI2_DIAG_BUF_TYPE_SNAPSHOT                 (0x01)
#define MPI2_DIAG_BUF_TYPE_EXTENDED                 (0x02)
/*count of the numbew of buffew types */
#define MPI2_DIAG_BUF_TYPE_COUNT                    (0x03)

/*vawues fow the Fwags fiewd */
#define MPI2_DIAG_BUF_FWAG_WEWEASE_ON_FUWW          (0x00000002)
#define MPI2_DIAG_BUF_FWAG_IMMEDIATE_WEWEASE        (0x00000001)

/****************************************************************************
* Diagnostic Buffew Post wepwy
****************************************************************************/

typedef stwuct _MPI2_DIAG_BUFFEW_POST_WEPWY {
	U8 ExtendedType;	/*0x00 */
	U8 BuffewType;		/*0x01 */
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
	U32 TwansfewWength;	/*0x14 */
} MPI2_DIAG_BUFFEW_POST_WEPWY, *PTW_MPI2_DIAG_BUFFEW_POST_WEPWY,
	Mpi2DiagBuffewPostWepwy_t, *pMpi2DiagBuffewPostWepwy_t;

/****************************************************************************
* Diagnostic Wewease wequest
****************************************************************************/

typedef stwuct _MPI2_DIAG_WEWEASE_WEQUEST {
	U8 Wesewved1;		/*0x00 */
	U8 BuffewType;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Wesewved2;		/*0x04 */
	U8 Wesewved3;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved4;		/*0x0A */
} MPI2_DIAG_WEWEASE_WEQUEST, *PTW_MPI2_DIAG_WEWEASE_WEQUEST,
	Mpi2DiagWeweaseWequest_t, *pMpi2DiagWeweaseWequest_t;

/****************************************************************************
* Diagnostic Buffew Post wepwy
****************************************************************************/

typedef stwuct _MPI2_DIAG_WEWEASE_WEPWY {
	U8 Wesewved1;		/*0x00 */
	U8 BuffewType;		/*0x01 */
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
} MPI2_DIAG_WEWEASE_WEPWY, *PTW_MPI2_DIAG_WEWEASE_WEPWY,
	Mpi2DiagWeweaseWepwy_t, *pMpi2DiagWeweaseWepwy_t;

#endif
