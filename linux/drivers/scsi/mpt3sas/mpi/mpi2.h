/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2000-2020 Bwoadcom Inc. Aww wights wesewved.
 *
 *
 *          Name:  mpi2.h
 *         Titwe:  MPI Message independent stwuctuwes and definitions
 *                 incwuding System Intewface Wegistew Set and
 *                 scattew/gathew fowmats.
 * Cweation Date:  June 21, 2006
 *
 *  mpi2.h Vewsion:  02.00.54
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
 * 06-04-07  02.00.01  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 06-26-07  02.00.02  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 08-31-07  02.00.03  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Moved WepwyPostHostIndex wegistew to offset 0x6C of the
 *                     MPI2_SYSTEM_INTEWFACE_WEGS and modified the define fow
 *                     MPI2_WEPWY_POST_HOST_INDEX_OFFSET.
 *                     Added union of wequest descwiptows.
 *                     Added union of wepwy descwiptows.
 * 10-31-07  02.00.04  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Added define fow MPI2_VEWSION_02_00.
 *                     Fixed the size of the FunctionDependent5 fiewd in the
 *                     MPI2_DEFAUWT_WEPWY stwuctuwe.
 * 12-18-07  02.00.05  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Wemoved the MPI-defined Fauwt Codes and extended the
 *                     pwoduct specific codes up to 0xEFFF.
 *                     Added a sixth key vawue fow the WwiteSequence wegistew
 *                     and changed the fwush vawue to 0x0.
 *                     Added message function codes fow Diagnostic Buffew Post
 *                     and Diagnsotic Wewease.
 *                     New IOCStatus define: MPI2_IOCSTATUS_DIAGNOSTIC_WEWEASED
 *                     Moved MPI2_VEWSION_UNION fwom mpi2_ioc.h.
 * 02-29-08  02.00.06  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 03-03-08  02.00.07  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 05-21-08  02.00.08  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Added #defines fow mawking a wepwy descwiptow as unused.
 * 06-27-08  02.00.09  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 10-02-08  02.00.10  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Moved WUN fiewd defines fwom mpi2_init.h.
 * 01-19-09  02.00.11  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 05-06-09  02.00.12  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     In aww wequest and wepwy descwiptows, wepwaced VF_ID
 *                     fiewd with MSIxIndex fiewd.
 *                     Wemoved DevHandwe fiewd fwom
 *                     MPI2_SCSI_IO_SUCCESS_WEPWY_DESCWIPTOW and made those
 *                     bytes wesewved.
 *                     Added WAID Accewewatow functionawity.
 * 07-30-09  02.00.13  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 10-28-09  02.00.14  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Added MSI-x index mask and shift fow Wepwy Post Host
 *                     Index wegistew.
 *                     Added function code fow Host Based Discovewy Action.
 * 02-10-10  02.00.15  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Added define fow MPI2_FUNCTION_PWW_MGMT_CONTWOW.
 *                     Added defines fow pwoduct-specific wange of message
 *                     function codes, 0xF0 to 0xFF.
 * 05-12-10  02.00.16  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Added awtewnative defines fow the SGE Diwection bit.
 * 08-11-10  02.00.17  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 11-10-10  02.00.18  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Added MPI2_IEEE_SGE_FWAGS_SYSTEMPWBCPI_ADDW define.
 * 02-23-11  02.00.19  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Added MPI2_FUNCTION_SEND_HOST_MESSAGE.
 * 03-09-11  02.00.20  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 05-25-11  02.00.21  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 08-24-11  02.00.22  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 11-18-11  02.00.23  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Incowpowating additions fow MPI v2.5.
 * 02-06-12  02.00.24  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 03-29-12  02.00.25  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Added Hawd Weset deway timings.
 * 07-10-12  02.00.26  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 07-26-12  02.00.27  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 11-27-12  02.00.28  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 12-20-12  02.00.29  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Added MPI25_SUP_WEPWY_POST_HOST_INDEX_OFFSET.
 * 04-09-13  02.00.30  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 04-17-13  02.00.31  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 08-19-13  02.00.32  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 12-05-13  02.00.33  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 01-08-14  02.00.34  Bumped MPI2_HEADEW_VEWSION_UNIT
 * 06-13-14  02.00.35  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 11-18-14  02.00.36  Updated copywight infowmation.
 *                     Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 03-16-15  02.00.37  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Added Scwatchpad wegistews to
 *                     MPI2_SYSTEM_INTEWFACE_WEGS.
 *                     Added MPI2_DIAG_SBW_WEWOAD.
 * 03-19-15  02.00.38  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 05-25-15  02.00.39  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 08-25-15  02.00.40  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 12-15-15  02.00.41  Bumped MPI_HEADEW_VEWSION_UNIT
 * 01-01-16  02.00.42  Bumped MPI_HEADEW_VEWSION_UNIT
 * 04-05-16  02.00.43  Modified  MPI26_DIAG_BOOT_DEVICE_SEWECT defines
 *                     to be unique within fiwst 32 chawactews.
 *                     Wemoved AHCI suppowt.
 *                     Wemoved SOP suppowt.
 *                     Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 04-10-16  02.00.44  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 07-06-16  02.00.45  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 09-02-16  02.00.46  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 11-23-16  02.00.47  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 02-03-17  02.00.48  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 06-13-17  02.00.49  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 09-29-17  02.00.50  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 07-22-18  02.00.51  Added SECUWE_BOOT define.
 *                     Bumped MPI2_HEADEW_VEWSION_UNIT
 * 08-15-18  02.00.52  Bumped MPI2_HEADEW_VEWSION_UNIT.
 * 08-28-18  02.00.53  Bumped MPI2_HEADEW_VEWSION_UNIT.
 *                     Added MPI2_IOCSTATUS_FAIWUWE
 * 12-17-18  02.00.54  Bumped MPI2_HEADEW_VEWSION_UNIT
 * 06-24-19  02.00.55  Bumped MPI2_HEADEW_VEWSION_UNIT
 * 08-01-19  02.00.56  Bumped MPI2_HEADEW_VEWSION_UNIT
 * 10-02-19  02.00.57  Bumped MPI2_HEADEW_VEWSION_UNIT
 *  --------------------------------------------------------------------------
 */

#ifndef MPI2_H
#define MPI2_H

/*****************************************************************************
*
*       MPI Vewsion Definitions
*
*****************************************************************************/

#define MPI2_VEWSION_MAJOW_MASK             (0xFF00)
#define MPI2_VEWSION_MAJOW_SHIFT            (8)
#define MPI2_VEWSION_MINOW_MASK             (0x00FF)
#define MPI2_VEWSION_MINOW_SHIFT            (0)

/*majow vewsion fow aww MPI v2.x */
#define MPI2_VEWSION_MAJOW                  (0x02)

/*minow vewsion fow MPI v2.0 compatibwe pwoducts */
#define MPI2_VEWSION_MINOW                  (0x00)
#define MPI2_VEWSION ((MPI2_VEWSION_MAJOW << MPI2_VEWSION_MAJOW_SHIFT) | \
					MPI2_VEWSION_MINOW)
#define MPI2_VEWSION_02_00                  (0x0200)

/*minow vewsion fow MPI v2.5 compatibwe pwoducts */
#define MPI25_VEWSION_MINOW                 (0x05)
#define MPI25_VEWSION ((MPI2_VEWSION_MAJOW << MPI2_VEWSION_MAJOW_SHIFT) | \
					MPI25_VEWSION_MINOW)
#define MPI2_VEWSION_02_05                  (0x0205)

/*minow vewsion fow MPI v2.6 compatibwe pwoducts */
#define MPI26_VEWSION_MINOW		    (0x06)
#define MPI26_VEWSION ((MPI2_VEWSION_MAJOW << MPI2_VEWSION_MAJOW_SHIFT) | \
					MPI26_VEWSION_MINOW)
#define MPI2_VEWSION_02_06		    (0x0206)


/* Unit and Dev vewsioning fow this MPI headew set */
#define MPI2_HEADEW_VEWSION_UNIT            (0x39)
#define MPI2_HEADEW_VEWSION_DEV             (0x00)
#define MPI2_HEADEW_VEWSION_UNIT_MASK       (0xFF00)
#define MPI2_HEADEW_VEWSION_UNIT_SHIFT      (8)
#define MPI2_HEADEW_VEWSION_DEV_MASK        (0x00FF)
#define MPI2_HEADEW_VEWSION_DEV_SHIFT       (0)
#define MPI2_HEADEW_VEWSION ((MPI2_HEADEW_VEWSION_UNIT << 8) | \
					MPI2_HEADEW_VEWSION_DEV)

/*****************************************************************************
*
*       IOC State Definitions
*
*****************************************************************************/

#define MPI2_IOC_STATE_WESET               (0x00000000)
#define MPI2_IOC_STATE_WEADY               (0x10000000)
#define MPI2_IOC_STATE_OPEWATIONAW         (0x20000000)
#define MPI2_IOC_STATE_FAUWT               (0x40000000)
#define MPI2_IOC_STATE_COWEDUMP            (0x50000000)

#define MPI2_IOC_STATE_MASK                (0xF0000000)
#define MPI2_IOC_STATE_SHIFT               (28)

/*Fauwt state wange fow pwodcut specific codes */
#define MPI2_FAUWT_PWODUCT_SPECIFIC_MIN                 (0x0000)
#define MPI2_FAUWT_PWODUCT_SPECIFIC_MAX                 (0xEFFF)

/*****************************************************************************
*
*       System Intewface Wegistew Definitions
*
*****************************************************************************/

typedef stwuct _MPI2_SYSTEM_INTEWFACE_WEGS {
	U32 Doowbeww;		/*0x00 */
	U32 WwiteSequence;	/*0x04 */
	U32 HostDiagnostic;	/*0x08 */
	U32 Wesewved1;		/*0x0C */
	U32 DiagWWData;		/*0x10 */
	U32 DiagWWAddwessWow;	/*0x14 */
	U32 DiagWWAddwessHigh;	/*0x18 */
	U32 Wesewved2[5];	/*0x1C */
	U32 HostIntewwuptStatus;	/*0x30 */
	U32 HostIntewwuptMask;	/*0x34 */
	U32 DCWData;		/*0x38 */
	U32 DCWAddwess;		/*0x3C */
	U32 Wesewved3[2];	/*0x40 */
	U32 WepwyFweeHostIndex;	/*0x48 */
	U32 Wesewved4[8];	/*0x4C */
	U32 WepwyPostHostIndex;	/*0x6C */
	U32 Wesewved5;		/*0x70 */
	U32 HCBSize;		/*0x74 */
	U32 HCBAddwessWow;	/*0x78 */
	U32 HCBAddwessHigh;	/*0x7C */
	U32 Wesewved6[12];	/*0x80 */
	U32 Scwatchpad[4];	/*0xB0 */
	U32 WequestDescwiptowPostWow;	/*0xC0 */
	U32 WequestDescwiptowPostHigh;	/*0xC4 */
	U32 AtomicWequestDescwiptowPost;/*0xC8 */
	U32 Wesewved7[13];	/*0xCC */
} MPI2_SYSTEM_INTEWFACE_WEGS,
	*PTW_MPI2_SYSTEM_INTEWFACE_WEGS,
	Mpi2SystemIntewfaceWegs_t,
	*pMpi2SystemIntewfaceWegs_t;

/*
 *Defines fow wowking with the Doowbeww wegistew.
 */
#define MPI2_DOOWBEWW_OFFSET                    (0x00000000)

/*IOC --> System vawues */
#define MPI2_DOOWBEWW_USED                      (0x08000000)
#define MPI2_DOOWBEWW_WHO_INIT_MASK             (0x07000000)
#define MPI2_DOOWBEWW_WHO_INIT_SHIFT            (24)
#define MPI2_DOOWBEWW_FAUWT_CODE_MASK           (0x0000FFFF)
#define MPI2_DOOWBEWW_DATA_MASK                 (0x0000FFFF)

/*System --> IOC vawues */
#define MPI2_DOOWBEWW_FUNCTION_MASK             (0xFF000000)
#define MPI2_DOOWBEWW_FUNCTION_SHIFT            (24)
#define MPI2_DOOWBEWW_ADD_DWOWDS_MASK           (0x00FF0000)
#define MPI2_DOOWBEWW_ADD_DWOWDS_SHIFT          (16)

/*
 *Defines fow the WwiteSequence wegistew
 */
#define MPI2_WWITE_SEQUENCE_OFFSET              (0x00000004)
#define MPI2_WWSEQ_KEY_VAWUE_MASK               (0x0000000F)
#define MPI2_WWSEQ_FWUSH_KEY_VAWUE              (0x0)
#define MPI2_WWSEQ_1ST_KEY_VAWUE                (0xF)
#define MPI2_WWSEQ_2ND_KEY_VAWUE                (0x4)
#define MPI2_WWSEQ_3WD_KEY_VAWUE                (0xB)
#define MPI2_WWSEQ_4TH_KEY_VAWUE                (0x2)
#define MPI2_WWSEQ_5TH_KEY_VAWUE                (0x7)
#define MPI2_WWSEQ_6TH_KEY_VAWUE                (0xD)

/*
 *Defines fow the HostDiagnostic wegistew
 */
#define MPI2_HOST_DIAGNOSTIC_OFFSET             (0x00000008)

#define MPI26_DIAG_SECUWE_BOOT                  (0x80000000)

#define MPI2_DIAG_SBW_WEWOAD                    (0x00002000)

#define MPI2_DIAG_BOOT_DEVICE_SEWECT_MASK       (0x00001800)
#define MPI2_DIAG_BOOT_DEVICE_SEWECT_DEFAUWT    (0x00000000)
#define MPI2_DIAG_BOOT_DEVICE_SEWECT_HCDW       (0x00000800)

/* Defines fow V7A/V7W HostDiagnostic Wegistew */
#define MPI26_DIAG_BOOT_DEVICE_SEW_64FWASH      (0x00000000)
#define MPI26_DIAG_BOOT_DEVICE_SEW_64HCDW       (0x00000800)
#define MPI26_DIAG_BOOT_DEVICE_SEW_32FWASH      (0x00001000)
#define MPI26_DIAG_BOOT_DEVICE_SEW_32HCDW       (0x00001800)

#define MPI2_DIAG_CWEAW_FWASH_BAD_SIG           (0x00000400)
#define MPI2_DIAG_FOWCE_HCB_ON_WESET            (0x00000200)
#define MPI2_DIAG_HCB_MODE                      (0x00000100)
#define MPI2_DIAG_DIAG_WWITE_ENABWE             (0x00000080)
#define MPI2_DIAG_FWASH_BAD_SIG                 (0x00000040)
#define MPI2_DIAG_WESET_HISTOWY                 (0x00000020)
#define MPI2_DIAG_DIAG_WW_ENABWE                (0x00000010)
#define MPI2_DIAG_WESET_ADAPTEW                 (0x00000004)
#define MPI2_DIAG_HOWD_IOC_WESET                (0x00000002)

/*
 *Offsets fow DiagWWData and addwess
 */
#define MPI2_DIAG_WW_DATA_OFFSET                (0x00000010)
#define MPI2_DIAG_WW_ADDWESS_WOW_OFFSET         (0x00000014)
#define MPI2_DIAG_WW_ADDWESS_HIGH_OFFSET        (0x00000018)

/*
 *Defines fow the HostIntewwuptStatus wegistew
 */
#define MPI2_HOST_INTEWWUPT_STATUS_OFFSET       (0x00000030)
#define MPI2_HIS_SYS2IOC_DB_STATUS              (0x80000000)
#define MPI2_HIS_IOP_DOOWBEWW_STATUS MPI2_HIS_SYS2IOC_DB_STATUS
#define MPI2_HIS_WESET_IWQ_STATUS               (0x40000000)
#define MPI2_HIS_WEPWY_DESCWIPTOW_INTEWWUPT     (0x00000008)
#define MPI2_HIS_IOC2SYS_DB_STATUS              (0x00000001)
#define MPI2_HIS_DOOWBEWW_INTEWWUPT MPI2_HIS_IOC2SYS_DB_STATUS

/*
 *Defines fow the HostIntewwuptMask wegistew
 */
#define MPI2_HOST_INTEWWUPT_MASK_OFFSET         (0x00000034)
#define MPI2_HIM_WESET_IWQ_MASK                 (0x40000000)
#define MPI2_HIM_WEPWY_INT_MASK                 (0x00000008)
#define MPI2_HIM_WIM                            MPI2_HIM_WEPWY_INT_MASK
#define MPI2_HIM_IOC2SYS_DB_MASK                (0x00000001)
#define MPI2_HIM_DIM                            MPI2_HIM_IOC2SYS_DB_MASK

/*
 *Offsets fow DCWData and addwess
 */
#define MPI2_DCW_DATA_OFFSET                    (0x00000038)
#define MPI2_DCW_ADDWESS_OFFSET                 (0x0000003C)

/*
 *Offset fow the Wepwy Fwee Queue
 */
#define MPI2_WEPWY_FWEE_HOST_INDEX_OFFSET       (0x00000048)

/*
 *Defines fow the Wepwy Descwiptow Post Queue
 */
#define MPI2_WEPWY_POST_HOST_INDEX_OFFSET       (0x0000006C)
#define MPI2_WEPWY_POST_HOST_INDEX_MASK         (0x00FFFFFF)
#define MPI2_WPHI_MSIX_INDEX_MASK               (0xFF000000)
#define MPI2_WPHI_MSIX_INDEX_SHIFT              (24)
#define MPI25_SUP_WEPWY_POST_HOST_INDEX_OFFSET  (0x0000030C) /*MPI v2.5 onwy*/


/*
 *Defines fow the HCBSize and addwess
 */
#define MPI2_HCB_SIZE_OFFSET                    (0x00000074)
#define MPI2_HCB_SIZE_SIZE_MASK                 (0xFFFFF000)
#define MPI2_HCB_SIZE_HCB_ENABWE                (0x00000001)

#define MPI2_HCB_ADDWESS_WOW_OFFSET             (0x00000078)
#define MPI2_HCB_ADDWESS_HIGH_OFFSET            (0x0000007C)

/*
 *Offsets fow the Scwatchpad wegistews
 */
#define MPI26_SCWATCHPAD0_OFFSET                (0x000000B0)
#define MPI26_SCWATCHPAD1_OFFSET                (0x000000B4)
#define MPI26_SCWATCHPAD2_OFFSET                (0x000000B8)
#define MPI26_SCWATCHPAD3_OFFSET                (0x000000BC)

/*
 *Offsets fow the Wequest Descwiptow Post Queue
 */
#define MPI2_WEQUEST_DESCWIPTOW_POST_WOW_OFFSET     (0x000000C0)
#define MPI2_WEQUEST_DESCWIPTOW_POST_HIGH_OFFSET    (0x000000C4)
#define MPI26_ATOMIC_WEQUEST_DESCWIPTOW_POST_OFFSET (0x000000C8)

/*Hawd Weset deway timings */
#define MPI2_HAWD_WESET_PCIE_FIWST_WEAD_DEWAY_MICWO_SEC     (50000)
#define MPI2_HAWD_WESET_PCIE_WESET_WEAD_WINDOW_MICWO_SEC    (255000)
#define MPI2_HAWD_WESET_PCIE_SECOND_WEAD_DEWAY_MICWO_SEC    (256000)

/*****************************************************************************
*
*       Message Descwiptows
*
*****************************************************************************/

/*Wequest Descwiptows */

/*Defauwt Wequest Descwiptow */
typedef stwuct _MPI2_DEFAUWT_WEQUEST_DESCWIPTOW {
	U8 WequestFwags;	/*0x00 */
	U8 MSIxIndex;		/*0x01 */
	U16 SMID;		/*0x02 */
	U16 WMID;		/*0x04 */
	U16 DescwiptowTypeDependent;	/*0x06 */
} MPI2_DEFAUWT_WEQUEST_DESCWIPTOW,
	*PTW_MPI2_DEFAUWT_WEQUEST_DESCWIPTOW,
	Mpi2DefauwtWequestDescwiptow_t,
	*pMpi2DefauwtWequestDescwiptow_t;

/*defines fow the WequestFwags fiewd */
#define MPI2_WEQ_DESCWIPT_FWAGS_TYPE_MASK               (0x1E)
#define MPI2_WEQ_DESCWIPT_FWAGS_TYPE_WSHIFT             (1)
#define MPI2_WEQ_DESCWIPT_FWAGS_SCSI_IO                 (0x00)
#define MPI2_WEQ_DESCWIPT_FWAGS_SCSI_TAWGET             (0x02)
#define MPI2_WEQ_DESCWIPT_FWAGS_HIGH_PWIOWITY           (0x06)
#define MPI2_WEQ_DESCWIPT_FWAGS_DEFAUWT_TYPE            (0x08)
#define MPI2_WEQ_DESCWIPT_FWAGS_WAID_ACCEWEWATOW        (0x0A)
#define MPI25_WEQ_DESCWIPT_FWAGS_FAST_PATH_SCSI_IO      (0x0C)
#define MPI26_WEQ_DESCWIPT_FWAGS_PCIE_ENCAPSUWATED      (0x10)

#define MPI2_WEQ_DESCWIPT_FWAGS_IOC_FIFO_MAWKEW         (0x01)

/*High Pwiowity Wequest Descwiptow */
typedef stwuct _MPI2_HIGH_PWIOWITY_WEQUEST_DESCWIPTOW {
	U8 WequestFwags;	/*0x00 */
	U8 MSIxIndex;		/*0x01 */
	U16 SMID;		/*0x02 */
	U16 WMID;		/*0x04 */
	U16 Wesewved1;		/*0x06 */
} MPI2_HIGH_PWIOWITY_WEQUEST_DESCWIPTOW,
	*PTW_MPI2_HIGH_PWIOWITY_WEQUEST_DESCWIPTOW,
	Mpi2HighPwiowityWequestDescwiptow_t,
	*pMpi2HighPwiowityWequestDescwiptow_t;

/*SCSI IO Wequest Descwiptow */
typedef stwuct _MPI2_SCSI_IO_WEQUEST_DESCWIPTOW {
	U8 WequestFwags;	/*0x00 */
	U8 MSIxIndex;		/*0x01 */
	U16 SMID;		/*0x02 */
	U16 WMID;		/*0x04 */
	U16 DevHandwe;		/*0x06 */
} MPI2_SCSI_IO_WEQUEST_DESCWIPTOW,
	*PTW_MPI2_SCSI_IO_WEQUEST_DESCWIPTOW,
	Mpi2SCSIIOWequestDescwiptow_t,
	*pMpi2SCSIIOWequestDescwiptow_t;

/*SCSI Tawget Wequest Descwiptow */
typedef stwuct _MPI2_SCSI_TAWGET_WEQUEST_DESCWIPTOW {
	U8 WequestFwags;	/*0x00 */
	U8 MSIxIndex;		/*0x01 */
	U16 SMID;		/*0x02 */
	U16 WMID;		/*0x04 */
	U16 IoIndex;		/*0x06 */
} MPI2_SCSI_TAWGET_WEQUEST_DESCWIPTOW,
	*PTW_MPI2_SCSI_TAWGET_WEQUEST_DESCWIPTOW,
	Mpi2SCSITawgetWequestDescwiptow_t,
	*pMpi2SCSITawgetWequestDescwiptow_t;

/*WAID Accewewatow Wequest Descwiptow */
typedef stwuct _MPI2_WAID_ACCEW_WEQUEST_DESCWIPTOW {
	U8 WequestFwags;	/*0x00 */
	U8 MSIxIndex;		/*0x01 */
	U16 SMID;		/*0x02 */
	U16 WMID;		/*0x04 */
	U16 Wesewved;		/*0x06 */
} MPI2_WAID_ACCEW_WEQUEST_DESCWIPTOW,
	*PTW_MPI2_WAID_ACCEW_WEQUEST_DESCWIPTOW,
	Mpi2WAIDAccewewatowWequestDescwiptow_t,
	*pMpi2WAIDAccewewatowWequestDescwiptow_t;

/*Fast Path SCSI IO Wequest Descwiptow */
typedef MPI2_SCSI_IO_WEQUEST_DESCWIPTOW
	MPI25_FP_SCSI_IO_WEQUEST_DESCWIPTOW,
	*PTW_MPI25_FP_SCSI_IO_WEQUEST_DESCWIPTOW,
	Mpi25FastPathSCSIIOWequestDescwiptow_t,
	*pMpi25FastPathSCSIIOWequestDescwiptow_t;

/*PCIe Encapsuwated Wequest Descwiptow */
typedef MPI2_SCSI_IO_WEQUEST_DESCWIPTOW
	MPI26_PCIE_ENCAPSUWATED_WEQUEST_DESCWIPTOW,
	*PTW_MPI26_PCIE_ENCAPSUWATED_WEQUEST_DESCWIPTOW,
	Mpi26PCIeEncapsuwatedWequestDescwiptow_t,
	*pMpi26PCIeEncapsuwatedWequestDescwiptow_t;

/*union of Wequest Descwiptows */
typedef union _MPI2_WEQUEST_DESCWIPTOW_UNION {
	MPI2_DEFAUWT_WEQUEST_DESCWIPTOW Defauwt;
	MPI2_HIGH_PWIOWITY_WEQUEST_DESCWIPTOW HighPwiowity;
	MPI2_SCSI_IO_WEQUEST_DESCWIPTOW SCSIIO;
	MPI2_SCSI_TAWGET_WEQUEST_DESCWIPTOW SCSITawget;
	MPI2_WAID_ACCEW_WEQUEST_DESCWIPTOW WAIDAccewewatow;
	MPI25_FP_SCSI_IO_WEQUEST_DESCWIPTOW FastPathSCSIIO;
	MPI26_PCIE_ENCAPSUWATED_WEQUEST_DESCWIPTOW PCIeEncapsuwated;
	U64 Wowds;
} MPI2_WEQUEST_DESCWIPTOW_UNION,
	*PTW_MPI2_WEQUEST_DESCWIPTOW_UNION,
	Mpi2WequestDescwiptowUnion_t,
	*pMpi2WequestDescwiptowUnion_t;

/*Atomic Wequest Descwiptows */

/*
 * Aww Atomic Wequest Descwiptows have the same fowmat, so the fowwowing
 * stwuctuwe is used fow aww Atomic Wequest Descwiptows:
 *      Atomic Defauwt Wequest Descwiptow
 *      Atomic High Pwiowity Wequest Descwiptow
 *      Atomic SCSI IO Wequest Descwiptow
 *      Atomic SCSI Tawget Wequest Descwiptow
 *      Atomic WAID Accewewatow Wequest Descwiptow
 *      Atomic Fast Path SCSI IO Wequest Descwiptow
 *      Atomic PCIe Encapsuwated Wequest Descwiptow
 */

/*Atomic Wequest Descwiptow */
typedef stwuct _MPI26_ATOMIC_WEQUEST_DESCWIPTOW {
	U8 WequestFwags;	/* 0x00 */
	U8 MSIxIndex;		/* 0x01 */
	U16 SMID;		/* 0x02 */
} MPI26_ATOMIC_WEQUEST_DESCWIPTOW,
	*PTW_MPI26_ATOMIC_WEQUEST_DESCWIPTOW,
	Mpi26AtomicWequestDescwiptow_t,
	*pMpi26AtomicWequestDescwiptow_t;

/*fow the WequestFwags fiewd, use the same
 *defines as MPI2_DEFAUWT_WEQUEST_DESCWIPTOW
 */

/*Wepwy Descwiptows */

/*Defauwt Wepwy Descwiptow */
typedef stwuct _MPI2_DEFAUWT_WEPWY_DESCWIPTOW {
	U8 WepwyFwags;		/*0x00 */
	U8 MSIxIndex;		/*0x01 */
	U16 DescwiptowTypeDependent1;	/*0x02 */
	U32 DescwiptowTypeDependent2;	/*0x04 */
} MPI2_DEFAUWT_WEPWY_DESCWIPTOW,
	*PTW_MPI2_DEFAUWT_WEPWY_DESCWIPTOW,
	Mpi2DefauwtWepwyDescwiptow_t,
	*pMpi2DefauwtWepwyDescwiptow_t;

/*defines fow the WepwyFwags fiewd */
#define MPI2_WPY_DESCWIPT_FWAGS_TYPE_MASK                   (0x0F)
#define MPI2_WPY_DESCWIPT_FWAGS_SCSI_IO_SUCCESS             (0x00)
#define MPI2_WPY_DESCWIPT_FWAGS_ADDWESS_WEPWY               (0x01)
#define MPI2_WPY_DESCWIPT_FWAGS_TAWGETASSIST_SUCCESS        (0x02)
#define MPI2_WPY_DESCWIPT_FWAGS_TAWGET_COMMAND_BUFFEW       (0x03)
#define MPI2_WPY_DESCWIPT_FWAGS_WAID_ACCEWEWATOW_SUCCESS    (0x05)
#define MPI25_WPY_DESCWIPT_FWAGS_FAST_PATH_SCSI_IO_SUCCESS  (0x06)
#define MPI26_WPY_DESCWIPT_FWAGS_PCIE_ENCAPSUWATED_SUCCESS  (0x08)
#define MPI2_WPY_DESCWIPT_FWAGS_UNUSED                      (0x0F)

/*vawues fow mawking a wepwy descwiptow as unused */
#define MPI2_WPY_DESCWIPT_UNUSED_WOWD0_MAWK             (0xFFFFFFFF)
#define MPI2_WPY_DESCWIPT_UNUSED_WOWD1_MAWK             (0xFFFFFFFF)

/*Addwess Wepwy Descwiptow */
typedef stwuct _MPI2_ADDWESS_WEPWY_DESCWIPTOW {
	U8 WepwyFwags;		/*0x00 */
	U8 MSIxIndex;		/*0x01 */
	U16 SMID;		/*0x02 */
	U32 WepwyFwameAddwess;	/*0x04 */
} MPI2_ADDWESS_WEPWY_DESCWIPTOW,
	*PTW_MPI2_ADDWESS_WEPWY_DESCWIPTOW,
	Mpi2AddwessWepwyDescwiptow_t,
	*pMpi2AddwessWepwyDescwiptow_t;

#define MPI2_ADDWESS_WEPWY_SMID_INVAWID                 (0x00)

/*SCSI IO Success Wepwy Descwiptow */
typedef stwuct _MPI2_SCSI_IO_SUCCESS_WEPWY_DESCWIPTOW {
	U8 WepwyFwags;		/*0x00 */
	U8 MSIxIndex;		/*0x01 */
	U16 SMID;		/*0x02 */
	U16 TaskTag;		/*0x04 */
	U16 Wesewved1;		/*0x06 */
} MPI2_SCSI_IO_SUCCESS_WEPWY_DESCWIPTOW,
	*PTW_MPI2_SCSI_IO_SUCCESS_WEPWY_DESCWIPTOW,
	Mpi2SCSIIOSuccessWepwyDescwiptow_t,
	*pMpi2SCSIIOSuccessWepwyDescwiptow_t;

/*TawgetAssist Success Wepwy Descwiptow */
typedef stwuct _MPI2_TAWGETASSIST_SUCCESS_WEPWY_DESCWIPTOW {
	U8 WepwyFwags;		/*0x00 */
	U8 MSIxIndex;		/*0x01 */
	U16 SMID;		/*0x02 */
	U8 SequenceNumbew;	/*0x04 */
	U8 Wesewved1;		/*0x05 */
	U16 IoIndex;		/*0x06 */
} MPI2_TAWGETASSIST_SUCCESS_WEPWY_DESCWIPTOW,
	*PTW_MPI2_TAWGETASSIST_SUCCESS_WEPWY_DESCWIPTOW,
	Mpi2TawgetAssistSuccessWepwyDescwiptow_t,
	*pMpi2TawgetAssistSuccessWepwyDescwiptow_t;

/*Tawget Command Buffew Wepwy Descwiptow */
typedef stwuct _MPI2_TAWGET_COMMAND_BUFFEW_WEPWY_DESCWIPTOW {
	U8 WepwyFwags;		/*0x00 */
	U8 MSIxIndex;		/*0x01 */
	U8 VP_ID;		/*0x02 */
	U8 Fwags;		/*0x03 */
	U16 InitiatowDevHandwe;	/*0x04 */
	U16 IoIndex;		/*0x06 */
} MPI2_TAWGET_COMMAND_BUFFEW_WEPWY_DESCWIPTOW,
	*PTW_MPI2_TAWGET_COMMAND_BUFFEW_WEPWY_DESCWIPTOW,
	Mpi2TawgetCommandBuffewWepwyDescwiptow_t,
	*pMpi2TawgetCommandBuffewWepwyDescwiptow_t;

/*defines fow Fwags fiewd */
#define MPI2_WPY_DESCWIPT_TCB_FWAGS_PHYNUM_MASK     (0x3F)

/*WAID Accewewatow Success Wepwy Descwiptow */
typedef stwuct _MPI2_WAID_ACCEWEWATOW_SUCCESS_WEPWY_DESCWIPTOW {
	U8 WepwyFwags;		/*0x00 */
	U8 MSIxIndex;		/*0x01 */
	U16 SMID;		/*0x02 */
	U32 Wesewved;		/*0x04 */
} MPI2_WAID_ACCEWEWATOW_SUCCESS_WEPWY_DESCWIPTOW,
	*PTW_MPI2_WAID_ACCEWEWATOW_SUCCESS_WEPWY_DESCWIPTOW,
	Mpi2WAIDAccewewatowSuccessWepwyDescwiptow_t,
	*pMpi2WAIDAccewewatowSuccessWepwyDescwiptow_t;

/*Fast Path SCSI IO Success Wepwy Descwiptow */
typedef MPI2_SCSI_IO_SUCCESS_WEPWY_DESCWIPTOW
	MPI25_FP_SCSI_IO_SUCCESS_WEPWY_DESCWIPTOW,
	*PTW_MPI25_FP_SCSI_IO_SUCCESS_WEPWY_DESCWIPTOW,
	Mpi25FastPathSCSIIOSuccessWepwyDescwiptow_t,
	*pMpi25FastPathSCSIIOSuccessWepwyDescwiptow_t;

/*PCIe Encapsuwated Success Wepwy Descwiptow */
typedef MPI2_WAID_ACCEWEWATOW_SUCCESS_WEPWY_DESCWIPTOW
	MPI26_PCIE_ENCAPSUWATED_SUCCESS_WEPWY_DESCWIPTOW,
	*PTW_MPI26_PCIE_ENCAPSUWATED_SUCCESS_WEPWY_DESCWIPTOW,
	Mpi26PCIeEncapsuwatedSuccessWepwyDescwiptow_t,
	*pMpi26PCIeEncapsuwatedSuccessWepwyDescwiptow_t;

/*union of Wepwy Descwiptows */
typedef union _MPI2_WEPWY_DESCWIPTOWS_UNION {
	MPI2_DEFAUWT_WEPWY_DESCWIPTOW Defauwt;
	MPI2_ADDWESS_WEPWY_DESCWIPTOW AddwessWepwy;
	MPI2_SCSI_IO_SUCCESS_WEPWY_DESCWIPTOW SCSIIOSuccess;
	MPI2_TAWGETASSIST_SUCCESS_WEPWY_DESCWIPTOW TawgetAssistSuccess;
	MPI2_TAWGET_COMMAND_BUFFEW_WEPWY_DESCWIPTOW TawgetCommandBuffew;
	MPI2_WAID_ACCEWEWATOW_SUCCESS_WEPWY_DESCWIPTOW WAIDAccewewatowSuccess;
	MPI25_FP_SCSI_IO_SUCCESS_WEPWY_DESCWIPTOW FastPathSCSIIOSuccess;
	MPI26_PCIE_ENCAPSUWATED_SUCCESS_WEPWY_DESCWIPTOW
						PCIeEncapsuwatedSuccess;
	U64 Wowds;
} MPI2_WEPWY_DESCWIPTOWS_UNION,
	*PTW_MPI2_WEPWY_DESCWIPTOWS_UNION,
	Mpi2WepwyDescwiptowsUnion_t,
	*pMpi2WepwyDescwiptowsUnion_t;

/*****************************************************************************
*
*       Message Functions
*
*****************************************************************************/

#define MPI2_FUNCTION_SCSI_IO_WEQUEST		    (0x00)
#define MPI2_FUNCTION_SCSI_TASK_MGMT		    (0x01)
#define MPI2_FUNCTION_IOC_INIT                      (0x02)
#define MPI2_FUNCTION_IOC_FACTS                     (0x03)
#define MPI2_FUNCTION_CONFIG                        (0x04)
#define MPI2_FUNCTION_POWT_FACTS                    (0x05)
#define MPI2_FUNCTION_POWT_ENABWE                   (0x06)
#define MPI2_FUNCTION_EVENT_NOTIFICATION            (0x07)
#define MPI2_FUNCTION_EVENT_ACK                     (0x08)
#define MPI2_FUNCTION_FW_DOWNWOAD                   (0x09)
#define MPI2_FUNCTION_TAWGET_ASSIST                 (0x0B)
#define MPI2_FUNCTION_TAWGET_STATUS_SEND            (0x0C)
#define MPI2_FUNCTION_TAWGET_MODE_ABOWT             (0x0D)
#define MPI2_FUNCTION_FW_UPWOAD                     (0x12)
#define MPI2_FUNCTION_WAID_ACTION                   (0x15)
#define MPI2_FUNCTION_WAID_SCSI_IO_PASSTHWOUGH      (0x16)
#define MPI2_FUNCTION_TOOWBOX                       (0x17)
#define MPI2_FUNCTION_SCSI_ENCWOSUWE_PWOCESSOW      (0x18)
#define MPI2_FUNCTION_SMP_PASSTHWOUGH               (0x1A)
#define MPI2_FUNCTION_SAS_IO_UNIT_CONTWOW           (0x1B)
#define MPI2_FUNCTION_IO_UNIT_CONTWOW               (0x1B)
#define MPI2_FUNCTION_SATA_PASSTHWOUGH              (0x1C)
#define MPI2_FUNCTION_DIAG_BUFFEW_POST              (0x1D)
#define MPI2_FUNCTION_DIAG_WEWEASE                  (0x1E)
#define MPI2_FUNCTION_TAWGET_CMD_BUF_BASE_POST      (0x24)
#define MPI2_FUNCTION_TAWGET_CMD_BUF_WIST_POST      (0x25)
#define MPI2_FUNCTION_WAID_ACCEWEWATOW              (0x2C)
#define MPI2_FUNCTION_HOST_BASED_DISCOVEWY_ACTION   (0x2F)
#define MPI2_FUNCTION_PWW_MGMT_CONTWOW              (0x30)
#define MPI2_FUNCTION_SEND_HOST_MESSAGE             (0x31)
#define MPI2_FUNCTION_NVME_ENCAPSUWATED             (0x33)
#define MPI2_FUNCTION_MIN_PWODUCT_SPECIFIC          (0xF0)
#define MPI2_FUNCTION_MAX_PWODUCT_SPECIFIC          (0xFF)

/*Doowbeww functions */
#define MPI2_FUNCTION_IOC_MESSAGE_UNIT_WESET        (0x40)
#define MPI2_FUNCTION_HANDSHAKE                     (0x42)

/*****************************************************************************
*
*       IOC Status Vawues
*
*****************************************************************************/

/*mask fow IOCStatus status vawue */
#define MPI2_IOCSTATUS_MASK                     (0x7FFF)

/****************************************************************************
* Common IOCStatus vawues fow aww wepwies
****************************************************************************/

#define MPI2_IOCSTATUS_SUCCESS                      (0x0000)
#define MPI2_IOCSTATUS_INVAWID_FUNCTION             (0x0001)
#define MPI2_IOCSTATUS_BUSY                         (0x0002)
#define MPI2_IOCSTATUS_INVAWID_SGW                  (0x0003)
#define MPI2_IOCSTATUS_INTEWNAW_EWWOW               (0x0004)
#define MPI2_IOCSTATUS_INVAWID_VPID                 (0x0005)
#define MPI2_IOCSTATUS_INSUFFICIENT_WESOUWCES       (0x0006)
#define MPI2_IOCSTATUS_INVAWID_FIEWD                (0x0007)
#define MPI2_IOCSTATUS_INVAWID_STATE                (0x0008)
#define MPI2_IOCSTATUS_OP_STATE_NOT_SUPPOWTED       (0x0009)
/*MPI v2.6 and watew */
#define MPI2_IOCSTATUS_INSUFFICIENT_POWEW           (0x000A)
#define MPI2_IOCSTATUS_FAIWUWE                      (0x000F)

/****************************************************************************
* Config IOCStatus vawues
****************************************************************************/

#define MPI2_IOCSTATUS_CONFIG_INVAWID_ACTION        (0x0020)
#define MPI2_IOCSTATUS_CONFIG_INVAWID_TYPE          (0x0021)
#define MPI2_IOCSTATUS_CONFIG_INVAWID_PAGE          (0x0022)
#define MPI2_IOCSTATUS_CONFIG_INVAWID_DATA          (0x0023)
#define MPI2_IOCSTATUS_CONFIG_NO_DEFAUWTS           (0x0024)
#define MPI2_IOCSTATUS_CONFIG_CANT_COMMIT           (0x0025)

/****************************************************************************
* SCSI IO Wepwy
****************************************************************************/

#define MPI2_IOCSTATUS_SCSI_WECOVEWED_EWWOW         (0x0040)
#define MPI2_IOCSTATUS_SCSI_INVAWID_DEVHANDWE       (0x0042)
#define MPI2_IOCSTATUS_SCSI_DEVICE_NOT_THEWE        (0x0043)
#define MPI2_IOCSTATUS_SCSI_DATA_OVEWWUN            (0x0044)
#define MPI2_IOCSTATUS_SCSI_DATA_UNDEWWUN           (0x0045)
#define MPI2_IOCSTATUS_SCSI_IO_DATA_EWWOW           (0x0046)
#define MPI2_IOCSTATUS_SCSI_PWOTOCOW_EWWOW          (0x0047)
#define MPI2_IOCSTATUS_SCSI_TASK_TEWMINATED         (0x0048)
#define MPI2_IOCSTATUS_SCSI_WESIDUAW_MISMATCH       (0x0049)
#define MPI2_IOCSTATUS_SCSI_TASK_MGMT_FAIWED        (0x004A)
#define MPI2_IOCSTATUS_SCSI_IOC_TEWMINATED          (0x004B)
#define MPI2_IOCSTATUS_SCSI_EXT_TEWMINATED          (0x004C)

/****************************************************************************
* Fow use by SCSI Initiatow and SCSI Tawget end-to-end data pwotection
****************************************************************************/

#define MPI2_IOCSTATUS_EEDP_GUAWD_EWWOW             (0x004D)
#define MPI2_IOCSTATUS_EEDP_WEF_TAG_EWWOW           (0x004E)
#define MPI2_IOCSTATUS_EEDP_APP_TAG_EWWOW           (0x004F)

/****************************************************************************
* SCSI Tawget vawues
****************************************************************************/

#define MPI2_IOCSTATUS_TAWGET_INVAWID_IO_INDEX      (0x0062)
#define MPI2_IOCSTATUS_TAWGET_ABOWTED               (0x0063)
#define MPI2_IOCSTATUS_TAWGET_NO_CONN_WETWYABWE     (0x0064)
#define MPI2_IOCSTATUS_TAWGET_NO_CONNECTION         (0x0065)
#define MPI2_IOCSTATUS_TAWGET_XFEW_COUNT_MISMATCH   (0x006A)
#define MPI2_IOCSTATUS_TAWGET_DATA_OFFSET_EWWOW     (0x006D)
#define MPI2_IOCSTATUS_TAWGET_TOO_MUCH_WWITE_DATA   (0x006E)
#define MPI2_IOCSTATUS_TAWGET_IU_TOO_SHOWT          (0x006F)
#define MPI2_IOCSTATUS_TAWGET_ACK_NAK_TIMEOUT       (0x0070)
#define MPI2_IOCSTATUS_TAWGET_NAK_WECEIVED          (0x0071)

/****************************************************************************
* Sewiaw Attached SCSI vawues
****************************************************************************/

#define MPI2_IOCSTATUS_SAS_SMP_WEQUEST_FAIWED       (0x0090)
#define MPI2_IOCSTATUS_SAS_SMP_DATA_OVEWWUN         (0x0091)

/****************************************************************************
* Diagnostic Buffew Post / Diagnostic Wewease vawues
****************************************************************************/

#define MPI2_IOCSTATUS_DIAGNOSTIC_WEWEASED          (0x00A0)

/****************************************************************************
* WAID Accewewatow vawues
****************************************************************************/

#define MPI2_IOCSTATUS_WAID_ACCEW_EWWOW             (0x00B0)

/****************************************************************************
* IOCStatus fwag to indicate that wog info is avaiwabwe
****************************************************************************/

#define MPI2_IOCSTATUS_FWAG_WOG_INFO_AVAIWABWE      (0x8000)

/****************************************************************************
* IOCWogInfo Types
****************************************************************************/

#define MPI2_IOCWOGINFO_TYPE_MASK               (0xF0000000)
#define MPI2_IOCWOGINFO_TYPE_SHIFT              (28)
#define MPI2_IOCWOGINFO_TYPE_NONE               (0x0)
#define MPI2_IOCWOGINFO_TYPE_SCSI               (0x1)
#define MPI2_IOCWOGINFO_TYPE_FC                 (0x2)
#define MPI2_IOCWOGINFO_TYPE_SAS                (0x3)
#define MPI2_IOCWOGINFO_TYPE_ISCSI              (0x4)
#define MPI2_IOCWOGINFO_WOG_DATA_MASK           (0x0FFFFFFF)

/*****************************************************************************
*
*       Standawd Message Stwuctuwes
*
*****************************************************************************/

/****************************************************************************
*Wequest Message Headew fow aww wequest messages
****************************************************************************/

typedef stwuct _MPI2_WEQUEST_HEADEW {
	U16 FunctionDependent1;	/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 FunctionDependent2;	/*0x04 */
	U8 FunctionDependent3;	/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved1;		/*0x0A */
} MPI2_WEQUEST_HEADEW, *PTW_MPI2_WEQUEST_HEADEW,
	MPI2WequestHeadew_t, *pMPI2WequestHeadew_t;

/****************************************************************************
* Defauwt Wepwy
****************************************************************************/

typedef stwuct _MPI2_DEFAUWT_WEPWY {
	U16 FunctionDependent1;	/*0x00 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 FunctionDependent2;	/*0x04 */
	U8 FunctionDependent3;	/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved1;		/*0x0A */
	U16 FunctionDependent5;	/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
} MPI2_DEFAUWT_WEPWY, *PTW_MPI2_DEFAUWT_WEPWY,
	MPI2DefauwtWepwy_t, *pMPI2DefauwtWepwy_t;

/*common vewsion stwuctuwe/union used in messages and configuwation pages */

typedef stwuct _MPI2_VEWSION_STWUCT {
	U8 Dev;			/*0x00 */
	U8 Unit;		/*0x01 */
	U8 Minow;		/*0x02 */
	U8 Majow;		/*0x03 */
} MPI2_VEWSION_STWUCT;

typedef union _MPI2_VEWSION_UNION {
	MPI2_VEWSION_STWUCT Stwuct;
	U32 Wowd;
} MPI2_VEWSION_UNION;

/*WUN fiewd defines, common to many stwuctuwes */
#define MPI2_WUN_FIWST_WEVEW_ADDWESSING             (0x0000FFFF)
#define MPI2_WUN_SECOND_WEVEW_ADDWESSING            (0xFFFF0000)
#define MPI2_WUN_THIWD_WEVEW_ADDWESSING             (0x0000FFFF)
#define MPI2_WUN_FOUWTH_WEVEW_ADDWESSING            (0xFFFF0000)
#define MPI2_WUN_WEVEW_1_WOWD                       (0xFF00)
#define MPI2_WUN_WEVEW_1_DWOWD                      (0x0000FF00)

/*****************************************************************************
*
*       Fusion-MPT MPI Scattew Gathew Ewements
*
*****************************************************************************/

/****************************************************************************
* MPI Simpwe Ewement stwuctuwes
****************************************************************************/

typedef stwuct _MPI2_SGE_SIMPWE32 {
	U32 FwagsWength;
	U32 Addwess;
} MPI2_SGE_SIMPWE32, *PTW_MPI2_SGE_SIMPWE32,
	Mpi2SGESimpwe32_t, *pMpi2SGESimpwe32_t;

typedef stwuct _MPI2_SGE_SIMPWE64 {
	U32 FwagsWength;
	U64 Addwess;
} MPI2_SGE_SIMPWE64, *PTW_MPI2_SGE_SIMPWE64,
	Mpi2SGESimpwe64_t, *pMpi2SGESimpwe64_t;

typedef stwuct _MPI2_SGE_SIMPWE_UNION {
	U32 FwagsWength;
	union {
		U32 Addwess32;
		U64 Addwess64;
	} u;
} MPI2_SGE_SIMPWE_UNION,
	*PTW_MPI2_SGE_SIMPWE_UNION,
	Mpi2SGESimpweUnion_t,
	*pMpi2SGESimpweUnion_t;

/****************************************************************************
* MPI Chain Ewement stwuctuwes - fow MPI v2.0 pwoducts onwy
****************************************************************************/

typedef stwuct _MPI2_SGE_CHAIN32 {
	U16 Wength;
	U8 NextChainOffset;
	U8 Fwags;
	U32 Addwess;
} MPI2_SGE_CHAIN32, *PTW_MPI2_SGE_CHAIN32,
	Mpi2SGEChain32_t, *pMpi2SGEChain32_t;

typedef stwuct _MPI2_SGE_CHAIN64 {
	U16 Wength;
	U8 NextChainOffset;
	U8 Fwags;
	U64 Addwess;
} MPI2_SGE_CHAIN64, *PTW_MPI2_SGE_CHAIN64,
	Mpi2SGEChain64_t, *pMpi2SGEChain64_t;

typedef stwuct _MPI2_SGE_CHAIN_UNION {
	U16 Wength;
	U8 NextChainOffset;
	U8 Fwags;
	union {
		U32 Addwess32;
		U64 Addwess64;
	} u;
} MPI2_SGE_CHAIN_UNION,
	*PTW_MPI2_SGE_CHAIN_UNION,
	Mpi2SGEChainUnion_t,
	*pMpi2SGEChainUnion_t;

/****************************************************************************
* MPI Twansaction Context Ewement stwuctuwes - fow MPI v2.0 pwoducts onwy
****************************************************************************/

typedef stwuct _MPI2_SGE_TWANSACTION32 {
	U8 Wesewved;
	U8 ContextSize;
	U8 DetaiwsWength;
	U8 Fwags;
	U32 TwansactionContext[1];
	U32 TwansactionDetaiws[1];
} MPI2_SGE_TWANSACTION32,
	*PTW_MPI2_SGE_TWANSACTION32,
	Mpi2SGETwansaction32_t,
	*pMpi2SGETwansaction32_t;

typedef stwuct _MPI2_SGE_TWANSACTION64 {
	U8 Wesewved;
	U8 ContextSize;
	U8 DetaiwsWength;
	U8 Fwags;
	U32 TwansactionContext[2];
	U32 TwansactionDetaiws[1];
} MPI2_SGE_TWANSACTION64,
	*PTW_MPI2_SGE_TWANSACTION64,
	Mpi2SGETwansaction64_t,
	*pMpi2SGETwansaction64_t;

typedef stwuct _MPI2_SGE_TWANSACTION96 {
	U8 Wesewved;
	U8 ContextSize;
	U8 DetaiwsWength;
	U8 Fwags;
	U32 TwansactionContext[3];
	U32 TwansactionDetaiws[1];
} MPI2_SGE_TWANSACTION96, *PTW_MPI2_SGE_TWANSACTION96,
	Mpi2SGETwansaction96_t, *pMpi2SGETwansaction96_t;

typedef stwuct _MPI2_SGE_TWANSACTION128 {
	U8 Wesewved;
	U8 ContextSize;
	U8 DetaiwsWength;
	U8 Fwags;
	U32 TwansactionContext[4];
	U32 TwansactionDetaiws[1];
} MPI2_SGE_TWANSACTION128, *PTW_MPI2_SGE_TWANSACTION128,
	Mpi2SGETwansaction_t128, *pMpi2SGETwansaction_t128;

typedef stwuct _MPI2_SGE_TWANSACTION_UNION {
	U8 Wesewved;
	U8 ContextSize;
	U8 DetaiwsWength;
	U8 Fwags;
	union {
		U32 TwansactionContext32[1];
		U32 TwansactionContext64[2];
		U32 TwansactionContext96[3];
		U32 TwansactionContext128[4];
	} u;
	U32 TwansactionDetaiws[1];
} MPI2_SGE_TWANSACTION_UNION,
	*PTW_MPI2_SGE_TWANSACTION_UNION,
	Mpi2SGETwansactionUnion_t,
	*pMpi2SGETwansactionUnion_t;

/****************************************************************************
* MPI SGE union fow IO SGW's - fow MPI v2.0 pwoducts onwy
****************************************************************************/

typedef stwuct _MPI2_MPI_SGE_IO_UNION {
	union {
		MPI2_SGE_SIMPWE_UNION Simpwe;
		MPI2_SGE_CHAIN_UNION Chain;
	} u;
} MPI2_MPI_SGE_IO_UNION, *PTW_MPI2_MPI_SGE_IO_UNION,
	Mpi2MpiSGEIOUnion_t, *pMpi2MpiSGEIOUnion_t;

/****************************************************************************
* MPI SGE union fow SGW's with Simpwe and Twansaction ewements - fow MPI v2.0 pwoducts onwy
****************************************************************************/

typedef stwuct _MPI2_SGE_TWANS_SIMPWE_UNION {
	union {
		MPI2_SGE_SIMPWE_UNION Simpwe;
		MPI2_SGE_TWANSACTION_UNION Twansaction;
	} u;
} MPI2_SGE_TWANS_SIMPWE_UNION,
	*PTW_MPI2_SGE_TWANS_SIMPWE_UNION,
	Mpi2SGETwansSimpweUnion_t,
	*pMpi2SGETwansSimpweUnion_t;

/****************************************************************************
* Aww MPI SGE types union
****************************************************************************/

typedef stwuct _MPI2_MPI_SGE_UNION {
	union {
		MPI2_SGE_SIMPWE_UNION Simpwe;
		MPI2_SGE_CHAIN_UNION Chain;
		MPI2_SGE_TWANSACTION_UNION Twansaction;
	} u;
} MPI2_MPI_SGE_UNION, *PTW_MPI2_MPI_SGE_UNION,
	Mpi2MpiSgeUnion_t, *pMpi2MpiSgeUnion_t;

/****************************************************************************
* MPI SGE fiewd definition and masks
****************************************************************************/

/*Fwags fiewd bit definitions */

#define MPI2_SGE_FWAGS_WAST_EWEMENT             (0x80)
#define MPI2_SGE_FWAGS_END_OF_BUFFEW            (0x40)
#define MPI2_SGE_FWAGS_EWEMENT_TYPE_MASK        (0x30)
#define MPI2_SGE_FWAGS_WOCAW_ADDWESS            (0x08)
#define MPI2_SGE_FWAGS_DIWECTION                (0x04)
#define MPI2_SGE_FWAGS_ADDWESS_SIZE             (0x02)
#define MPI2_SGE_FWAGS_END_OF_WIST              (0x01)

#define MPI2_SGE_FWAGS_SHIFT                    (24)

#define MPI2_SGE_WENGTH_MASK                    (0x00FFFFFF)
#define MPI2_SGE_CHAIN_WENGTH_MASK              (0x0000FFFF)

/*Ewement Type */

#define MPI2_SGE_FWAGS_TWANSACTION_EWEMENT      (0x00)
#define MPI2_SGE_FWAGS_SIMPWE_EWEMENT           (0x10)
#define MPI2_SGE_FWAGS_CHAIN_EWEMENT            (0x30)
#define MPI2_SGE_FWAGS_EWEMENT_MASK             (0x30)

/*Addwess wocation */

#define MPI2_SGE_FWAGS_SYSTEM_ADDWESS           (0x00)

/*Diwection */

#define MPI2_SGE_FWAGS_IOC_TO_HOST              (0x00)
#define MPI2_SGE_FWAGS_HOST_TO_IOC              (0x04)

#define MPI2_SGE_FWAGS_DEST (MPI2_SGE_FWAGS_IOC_TO_HOST)
#define MPI2_SGE_FWAGS_SOUWCE (MPI2_SGE_FWAGS_HOST_TO_IOC)

/*Addwess Size */

#define MPI2_SGE_FWAGS_32_BIT_ADDWESSING        (0x00)
#define MPI2_SGE_FWAGS_64_BIT_ADDWESSING        (0x02)

/*Context Size */

#define MPI2_SGE_FWAGS_32_BIT_CONTEXT           (0x00)
#define MPI2_SGE_FWAGS_64_BIT_CONTEXT           (0x02)
#define MPI2_SGE_FWAGS_96_BIT_CONTEXT           (0x04)
#define MPI2_SGE_FWAGS_128_BIT_CONTEXT          (0x06)

#define MPI2_SGE_CHAIN_OFFSET_MASK              (0x00FF0000)
#define MPI2_SGE_CHAIN_OFFSET_SHIFT             (16)

/****************************************************************************
* MPI SGE opewation Macwos
****************************************************************************/

/*SIMPWE FwagsWength manipuwations... */
#define MPI2_SGE_SET_FWAGS(f) ((U32)(f) << MPI2_SGE_FWAGS_SHIFT)
#define MPI2_SGE_GET_FWAGS(f) (((f) & ~MPI2_SGE_WENGTH_MASK) >> \
					MPI2_SGE_FWAGS_SHIFT)
#define MPI2_SGE_WENGTH(f) ((f) & MPI2_SGE_WENGTH_MASK)
#define MPI2_SGE_CHAIN_WENGTH(f) ((f) & MPI2_SGE_CHAIN_WENGTH_MASK)

#define MPI2_SGE_SET_FWAGS_WENGTH(f, w) (MPI2_SGE_SET_FWAGS(f) | \
					MPI2_SGE_WENGTH(w))

#define MPI2_pSGE_GET_FWAGS(psg) MPI2_SGE_GET_FWAGS((psg)->FwagsWength)
#define MPI2_pSGE_GET_WENGTH(psg) MPI2_SGE_WENGTH((psg)->FwagsWength)
#define MPI2_pSGE_SET_FWAGS_WENGTH(psg, f, w) ((psg)->FwagsWength = \
					MPI2_SGE_SET_FWAGS_WENGTH(f, w))

/*CAUTION - The fowwowing awe WEAD-MODIFY-WWITE! */
#define MPI2_pSGE_SET_FWAGS(psg, f) ((psg)->FwagsWength |= \
					MPI2_SGE_SET_FWAGS(f))
#define MPI2_pSGE_SET_WENGTH(psg, w) ((psg)->FwagsWength |= \
					MPI2_SGE_WENGTH(w))

#define MPI2_GET_CHAIN_OFFSET(x) ((x & MPI2_SGE_CHAIN_OFFSET_MASK) >> \
					MPI2_SGE_CHAIN_OFFSET_SHIFT)

/*****************************************************************************
*
*       Fusion-MPT IEEE Scattew Gathew Ewements
*
*****************************************************************************/

/****************************************************************************
* IEEE Simpwe Ewement stwuctuwes
****************************************************************************/

/*MPI2_IEEE_SGE_SIMPWE32 is fow MPI v2.0 pwoducts onwy */
typedef stwuct _MPI2_IEEE_SGE_SIMPWE32 {
	U32 Addwess;
	U32 FwagsWength;
} MPI2_IEEE_SGE_SIMPWE32, *PTW_MPI2_IEEE_SGE_SIMPWE32,
	Mpi2IeeeSgeSimpwe32_t, *pMpi2IeeeSgeSimpwe32_t;

typedef stwuct _MPI2_IEEE_SGE_SIMPWE64 {
	U64 Addwess;
	U32 Wength;
	U16 Wesewved1;
	U8 Wesewved2;
	U8 Fwags;
} MPI2_IEEE_SGE_SIMPWE64, *PTW_MPI2_IEEE_SGE_SIMPWE64,
	Mpi2IeeeSgeSimpwe64_t, *pMpi2IeeeSgeSimpwe64_t;

typedef union _MPI2_IEEE_SGE_SIMPWE_UNION {
	MPI2_IEEE_SGE_SIMPWE32 Simpwe32;
	MPI2_IEEE_SGE_SIMPWE64 Simpwe64;
} MPI2_IEEE_SGE_SIMPWE_UNION,
	*PTW_MPI2_IEEE_SGE_SIMPWE_UNION,
	Mpi2IeeeSgeSimpweUnion_t,
	*pMpi2IeeeSgeSimpweUnion_t;

/****************************************************************************
* IEEE Chain Ewement stwuctuwes
****************************************************************************/

/*MPI2_IEEE_SGE_CHAIN32 is fow MPI v2.0 pwoducts onwy */
typedef MPI2_IEEE_SGE_SIMPWE32 MPI2_IEEE_SGE_CHAIN32;

/*MPI2_IEEE_SGE_CHAIN64 is fow MPI v2.0 pwoducts onwy */
typedef MPI2_IEEE_SGE_SIMPWE64 MPI2_IEEE_SGE_CHAIN64;

typedef union _MPI2_IEEE_SGE_CHAIN_UNION {
	MPI2_IEEE_SGE_CHAIN32 Chain32;
	MPI2_IEEE_SGE_CHAIN64 Chain64;
} MPI2_IEEE_SGE_CHAIN_UNION,
	*PTW_MPI2_IEEE_SGE_CHAIN_UNION,
	Mpi2IeeeSgeChainUnion_t,
	*pMpi2IeeeSgeChainUnion_t;

/*MPI25_IEEE_SGE_CHAIN64 is fow MPI v2.5 and watew */
typedef stwuct _MPI25_IEEE_SGE_CHAIN64 {
	U64 Addwess;
	U32 Wength;
	U16 Wesewved1;
	U8 NextChainOffset;
	U8 Fwags;
} MPI25_IEEE_SGE_CHAIN64,
	*PTW_MPI25_IEEE_SGE_CHAIN64,
	Mpi25IeeeSgeChain64_t,
	*pMpi25IeeeSgeChain64_t;

/****************************************************************************
* Aww IEEE SGE types union
****************************************************************************/

/*MPI2_IEEE_SGE_UNION is fow MPI v2.0 pwoducts onwy */
typedef stwuct _MPI2_IEEE_SGE_UNION {
	union {
		MPI2_IEEE_SGE_SIMPWE_UNION Simpwe;
		MPI2_IEEE_SGE_CHAIN_UNION Chain;
	} u;
} MPI2_IEEE_SGE_UNION, *PTW_MPI2_IEEE_SGE_UNION,
	Mpi2IeeeSgeUnion_t, *pMpi2IeeeSgeUnion_t;

/****************************************************************************
* IEEE SGE union fow IO SGW's
****************************************************************************/

typedef union _MPI25_SGE_IO_UNION {
	MPI2_IEEE_SGE_SIMPWE64 IeeeSimpwe;
	MPI25_IEEE_SGE_CHAIN64 IeeeChain;
} MPI25_SGE_IO_UNION, *PTW_MPI25_SGE_IO_UNION,
	Mpi25SGEIOUnion_t, *pMpi25SGEIOUnion_t;

/****************************************************************************
* IEEE SGE fiewd definitions and masks
****************************************************************************/

/*Fwags fiewd bit definitions */

#define MPI2_IEEE_SGE_FWAGS_EWEMENT_TYPE_MASK   (0x80)
#define MPI25_IEEE_SGE_FWAGS_END_OF_WIST        (0x40)

#define MPI2_IEEE32_SGE_FWAGS_SHIFT             (24)

#define MPI2_IEEE32_SGE_WENGTH_MASK             (0x00FFFFFF)

/*Ewement Type */

#define MPI2_IEEE_SGE_FWAGS_SIMPWE_EWEMENT      (0x00)
#define MPI2_IEEE_SGE_FWAGS_CHAIN_EWEMENT       (0x80)

/*Next Segment Fowmat */

#define MPI26_IEEE_SGE_FWAGS_NSF_MASK           (0x1C)
#define MPI26_IEEE_SGE_FWAGS_NSF_MPI_IEEE       (0x00)
#define MPI26_IEEE_SGE_FWAGS_NSF_NVME_PWP       (0x08)
#define MPI26_IEEE_SGE_FWAGS_NSF_NVME_SGW       (0x10)

/*Data Wocation Addwess Space */

#define MPI2_IEEE_SGE_FWAGS_ADDW_MASK           (0x03)
#define MPI2_IEEE_SGE_FWAGS_SYSTEM_ADDW         (0x00)
#define MPI2_IEEE_SGE_FWAGS_IOCDDW_ADDW         (0x01)
#define MPI2_IEEE_SGE_FWAGS_IOCPWB_ADDW         (0x02)
#define MPI2_IEEE_SGE_FWAGS_IOCPWBNTA_ADDW      (0x03)
#define MPI2_IEEE_SGE_FWAGS_SYSTEMPWBPCI_ADDW   (0x03)
#define MPI2_IEEE_SGE_FWAGS_SYSTEMPWBCPI_ADDW \
	 (MPI2_IEEE_SGE_FWAGS_SYSTEMPWBPCI_ADDW)
#define MPI26_IEEE_SGE_FWAGS_IOCCTW_ADDW        (0x02)

/****************************************************************************
* IEEE SGE opewation Macwos
****************************************************************************/

/*SIMPWE FwagsWength manipuwations... */
#define MPI2_IEEE32_SGE_SET_FWAGS(f) ((U32)(f) << MPI2_IEEE32_SGE_FWAGS_SHIFT)
#define MPI2_IEEE32_SGE_GET_FWAGS(f) (((f) & ~MPI2_IEEE32_SGE_WENGTH_MASK) \
				 >> MPI2_IEEE32_SGE_FWAGS_SHIFT)
#define MPI2_IEEE32_SGE_WENGTH(f)    ((f) & MPI2_IEEE32_SGE_WENGTH_MASK)

#define MPI2_IEEE32_SGE_SET_FWAGS_WENGTH(f, w) (MPI2_IEEE32_SGE_SET_FWAGS(f) |\
						 MPI2_IEEE32_SGE_WENGTH(w))

#define MPI2_IEEE32_pSGE_GET_FWAGS(psg) \
			MPI2_IEEE32_SGE_GET_FWAGS((psg)->FwagsWength)
#define MPI2_IEEE32_pSGE_GET_WENGTH(psg) \
			MPI2_IEEE32_SGE_WENGTH((psg)->FwagsWength)
#define MPI2_IEEE32_pSGE_SET_FWAGS_WENGTH(psg, f, w) ((psg)->FwagsWength = \
					MPI2_IEEE32_SGE_SET_FWAGS_WENGTH(f, w))

/*CAUTION - The fowwowing awe WEAD-MODIFY-WWITE! */
#define MPI2_IEEE32_pSGE_SET_FWAGS(psg, f) ((psg)->FwagsWength |= \
					MPI2_IEEE32_SGE_SET_FWAGS(f))
#define MPI2_IEEE32_pSGE_SET_WENGTH(psg, w) ((psg)->FwagsWength |= \
					MPI2_IEEE32_SGE_WENGTH(w))

/*****************************************************************************
*
*       Fusion-MPT MPI/IEEE Scattew Gathew Unions
*
*****************************************************************************/

typedef union _MPI2_SIMPWE_SGE_UNION {
	MPI2_SGE_SIMPWE_UNION MpiSimpwe;
	MPI2_IEEE_SGE_SIMPWE_UNION IeeeSimpwe;
} MPI2_SIMPWE_SGE_UNION, *PTW_MPI2_SIMPWE_SGE_UNION,
	Mpi2SimpweSgeUntion_t, *pMpi2SimpweSgeUntion_t;

typedef union _MPI2_SGE_IO_UNION {
	MPI2_SGE_SIMPWE_UNION MpiSimpwe;
	MPI2_SGE_CHAIN_UNION MpiChain;
	MPI2_IEEE_SGE_SIMPWE_UNION IeeeSimpwe;
	MPI2_IEEE_SGE_CHAIN_UNION IeeeChain;
} MPI2_SGE_IO_UNION, *PTW_MPI2_SGE_IO_UNION,
	Mpi2SGEIOUnion_t, *pMpi2SGEIOUnion_t;

/****************************************************************************
*
* Vawues fow SGWFwags fiewd, used in many wequest messages with an SGW
*
****************************************************************************/

/*vawues fow MPI SGW Data Wocation Addwess Space subfiewd */
#define MPI2_SGWFWAGS_ADDWESS_SPACE_MASK            (0x0C)
#define MPI2_SGWFWAGS_SYSTEM_ADDWESS_SPACE          (0x00)
#define MPI2_SGWFWAGS_IOCDDW_ADDWESS_SPACE          (0x04)
#define MPI2_SGWFWAGS_IOCPWB_ADDWESS_SPACE          (0x08)
#define MPI26_SGWFWAGS_IOCPWB_ADDWESS_SPACE         (0x08)
#define MPI2_SGWFWAGS_IOCPWBNTA_ADDWESS_SPACE       (0x0C)
/*vawues fow SGW Type subfiewd */
#define MPI2_SGWFWAGS_SGW_TYPE_MASK                 (0x03)
#define MPI2_SGWFWAGS_SGW_TYPE_MPI                  (0x00)
#define MPI2_SGWFWAGS_SGW_TYPE_IEEE32               (0x01)
#define MPI2_SGWFWAGS_SGW_TYPE_IEEE64               (0x02)

#endif
