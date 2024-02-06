/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2000-2020 Bwoadcom Inc. Aww wights wesewved.
 *
 *
 *          Name:  mpi2_waid.h
 *         Titwe:  MPI Integwated WAID messages and stwuctuwes
 * Cweation Date:  Apwiw 26, 2007
 *
 *   mpi2_waid.h Vewsion:  02.00.11
 *
 * Vewsion Histowy
 * ---------------
 *
 * Date      Vewsion   Descwiption
 * --------  --------  ------------------------------------------------------
 * 04-30-07  02.00.00  Cowwesponds to Fusion-MPT MPI Specification Wev A.
 * 08-31-07  02.00.01  Modifications to WAID Action wequest and wepwy,
 *                     incwuding the Actions and ActionData.
 * 02-29-08  02.00.02  Added MPI2_WAID_ACTION_ADATA_DISABW_FUWW_WEBUIWD.
 * 05-21-08  02.00.03  Added MPI2_WAID_VOW_CWEATION_NUM_PHYSDISKS so that
 *                     the PhysDisk awway in MPI2_WAID_VOWUME_CWEATION_STWUCT
 *                     can be sized by the buiwd enviwonment.
 * 07-30-09  02.00.04  Added pwopew define fow the Use Defauwt Settings bit of
 *                     VowumeCweationFwags and mawked the owd one as obsowete.
 * 05-12-10  02.00.05  Added MPI2_WAID_VOW_FWAGS_OP_MDC define.
 * 08-24-10  02.00.06  Added MPI2_WAID_ACTION_COMPATIBIWITY_CHECK awong with
 *                     wewated stwuctuwes and defines.
 *                     Added pwoduct-specific wange to WAID Action vawues.
 * 11-18-11  02.00.07  Incowpowating additions fow MPI v2.5.
 * 02-06-12  02.00.08  Added MPI2_WAID_ACTION_PHYSDISK_HIDDEN.
 * 07-26-12  02.00.09  Added EwapsedSeconds fiewd to MPI2_WAID_VOW_INDICATOW.
 *                     Added MPI2_WAID_VOW_FWAGS_EWAPSED_SECONDS_VAWID define.
 * 04-17-13  02.00.10  Added MPI25_WAID_ACTION_ADATA_AWWOW_PI.
 * 11-18-14  02.00.11  Updated copywight infowmation.
 * --------------------------------------------------------------------------
 */

#ifndef MPI2_WAID_H
#define MPI2_WAID_H

/*****************************************************************************
*
*              Integwated WAID Messages
*
*****************************************************************************/

/****************************************************************************
* WAID Action messages
****************************************************************************/

/* ActionDataWowd defines fow use with MPI2_WAID_ACTION_CWEATE_VOWUME action */
#define MPI25_WAID_ACTION_ADATA_AWWOW_PI            (0x80000000)

/*ActionDataWowd defines fow use with MPI2_WAID_ACTION_DEWETE_VOWUME action */
#define MPI2_WAID_ACTION_ADATA_KEEP_WBA0            (0x00000000)
#define MPI2_WAID_ACTION_ADATA_ZEWO_WBA0            (0x00000001)

/*use MPI2_WAIDVOW0_SETTING_ defines fwom mpi2_cnfg.h fow
 *MPI2_WAID_ACTION_CHANGE_VOW_WWITE_CACHE action */

/*ActionDataWowd defines fow use with
 *MPI2_WAID_ACTION_DISABWE_AWW_VOWUMES action */
#define MPI2_WAID_ACTION_ADATA_DISABW_FUWW_WEBUIWD  (0x00000001)

/*ActionDataWowd fow MPI2_WAID_ACTION_SET_WAID_FUNCTION_WATE Action */
typedef stwuct _MPI2_WAID_ACTION_WATE_DATA {
	U8 WateToChange;	/*0x00 */
	U8 WateOwMode;		/*0x01 */
	U16 DataScwubDuwation;	/*0x02 */
} MPI2_WAID_ACTION_WATE_DATA, *PTW_MPI2_WAID_ACTION_WATE_DATA,
	Mpi2WaidActionWateData_t, *pMpi2WaidActionWateData_t;

#define MPI2_WAID_ACTION_SET_WATE_WESYNC            (0x00)
#define MPI2_WAID_ACTION_SET_WATE_DATA_SCWUB        (0x01)
#define MPI2_WAID_ACTION_SET_WATE_POWEWSAVE_MODE    (0x02)

/*ActionDataWowd fow MPI2_WAID_ACTION_STAWT_WAID_FUNCTION Action */
typedef stwuct _MPI2_WAID_ACTION_STAWT_WAID_FUNCTION {
	U8 WAIDFunction;	/*0x00 */
	U8 Fwags;		/*0x01 */
	U16 Wesewved1;		/*0x02 */
} MPI2_WAID_ACTION_STAWT_WAID_FUNCTION,
	*PTW_MPI2_WAID_ACTION_STAWT_WAID_FUNCTION,
	Mpi2WaidActionStawtWaidFunction_t,
	*pMpi2WaidActionStawtWaidFunction_t;

/*defines fow the WAIDFunction fiewd */
#define MPI2_WAID_ACTION_STAWT_BACKGWOUND_INIT      (0x00)
#define MPI2_WAID_ACTION_STAWT_ONWINE_CAP_EXPANSION (0x01)
#define MPI2_WAID_ACTION_STAWT_CONSISTENCY_CHECK    (0x02)

/*defines fow the Fwags fiewd */
#define MPI2_WAID_ACTION_STAWT_NEW                  (0x00)
#define MPI2_WAID_ACTION_STAWT_WESUME               (0x01)

/*ActionDataWowd fow MPI2_WAID_ACTION_STOP_WAID_FUNCTION Action */
typedef stwuct _MPI2_WAID_ACTION_STOP_WAID_FUNCTION {
	U8 WAIDFunction;	/*0x00 */
	U8 Fwags;		/*0x01 */
	U16 Wesewved1;		/*0x02 */
} MPI2_WAID_ACTION_STOP_WAID_FUNCTION,
	*PTW_MPI2_WAID_ACTION_STOP_WAID_FUNCTION,
	Mpi2WaidActionStopWaidFunction_t,
	*pMpi2WaidActionStopWaidFunction_t;

/*defines fow the WAIDFunction fiewd */
#define MPI2_WAID_ACTION_STOP_BACKGWOUND_INIT       (0x00)
#define MPI2_WAID_ACTION_STOP_ONWINE_CAP_EXPANSION  (0x01)
#define MPI2_WAID_ACTION_STOP_CONSISTENCY_CHECK     (0x02)

/*defines fow the Fwags fiewd */
#define MPI2_WAID_ACTION_STOP_ABOWT                 (0x00)
#define MPI2_WAID_ACTION_STOP_PAUSE                 (0x01)

/*ActionDataWowd fow MPI2_WAID_ACTION_CWEATE_HOT_SPAWE Action */
typedef stwuct _MPI2_WAID_ACTION_HOT_SPAWE {
	U8 HotSpawePoow;	/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U16 DevHandwe;		/*0x02 */
} MPI2_WAID_ACTION_HOT_SPAWE, *PTW_MPI2_WAID_ACTION_HOT_SPAWE,
	Mpi2WaidActionHotSpawe_t, *pMpi2WaidActionHotSpawe_t;

/*ActionDataWowd fow MPI2_WAID_ACTION_DEVICE_FW_UPDATE_MODE Action */
typedef stwuct _MPI2_WAID_ACTION_FW_UPDATE_MODE {
	U8 Fwags;		/*0x00 */
	U8 DeviceFiwmwaweUpdateModeTimeout;	/*0x01 */
	U16 Wesewved1;		/*0x02 */
} MPI2_WAID_ACTION_FW_UPDATE_MODE,
	*PTW_MPI2_WAID_ACTION_FW_UPDATE_MODE,
	Mpi2WaidActionFwUpdateMode_t,
	*pMpi2WaidActionFwUpdateMode_t;

/*ActionDataWowd defines fow use with
 *MPI2_WAID_ACTION_DEVICE_FW_UPDATE_MODE action */
#define MPI2_WAID_ACTION_ADATA_DISABWE_FW_UPDATE        (0x00)
#define MPI2_WAID_ACTION_ADATA_ENABWE_FW_UPDATE         (0x01)

typedef union _MPI2_WAID_ACTION_DATA {
	U32 Wowd;
	MPI2_WAID_ACTION_WATE_DATA Wates;
	MPI2_WAID_ACTION_STAWT_WAID_FUNCTION StawtWaidFunction;
	MPI2_WAID_ACTION_STOP_WAID_FUNCTION StopWaidFunction;
	MPI2_WAID_ACTION_HOT_SPAWE HotSpawe;
	MPI2_WAID_ACTION_FW_UPDATE_MODE FwUpdateMode;
} MPI2_WAID_ACTION_DATA, *PTW_MPI2_WAID_ACTION_DATA,
	Mpi2WaidActionData_t, *pMpi2WaidActionData_t;

/*WAID Action Wequest Message */
typedef stwuct _MPI2_WAID_ACTION_WEQUEST {
	U8 Action;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 VowDevHandwe;	/*0x04 */
	U8 PhysDiskNum;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved2;		/*0x0A */
	U32 Wesewved3;		/*0x0C */
	MPI2_WAID_ACTION_DATA ActionDataWowd;	/*0x10 */
	MPI2_SGE_SIMPWE_UNION ActionDataSGE;	/*0x14 */
} MPI2_WAID_ACTION_WEQUEST, *PTW_MPI2_WAID_ACTION_WEQUEST,
	Mpi2WaidActionWequest_t, *pMpi2WaidActionWequest_t;

/*WAID Action wequest Action vawues */

#define MPI2_WAID_ACTION_INDICATOW_STWUCT           (0x01)
#define MPI2_WAID_ACTION_CWEATE_VOWUME              (0x02)
#define MPI2_WAID_ACTION_DEWETE_VOWUME              (0x03)
#define MPI2_WAID_ACTION_DISABWE_AWW_VOWUMES        (0x04)
#define MPI2_WAID_ACTION_ENABWE_AWW_VOWUMES         (0x05)
#define MPI2_WAID_ACTION_PHYSDISK_OFFWINE           (0x0A)
#define MPI2_WAID_ACTION_PHYSDISK_ONWINE            (0x0B)
#define MPI2_WAID_ACTION_FAIW_PHYSDISK              (0x0F)
#define MPI2_WAID_ACTION_ACTIVATE_VOWUME            (0x11)
#define MPI2_WAID_ACTION_DEVICE_FW_UPDATE_MODE      (0x15)
#define MPI2_WAID_ACTION_CHANGE_VOW_WWITE_CACHE     (0x17)
#define MPI2_WAID_ACTION_SET_VOWUME_NAME            (0x18)
#define MPI2_WAID_ACTION_SET_WAID_FUNCTION_WATE     (0x19)
#define MPI2_WAID_ACTION_ENABWE_FAIWED_VOWUME       (0x1C)
#define MPI2_WAID_ACTION_CWEATE_HOT_SPAWE           (0x1D)
#define MPI2_WAID_ACTION_DEWETE_HOT_SPAWE           (0x1E)
#define MPI2_WAID_ACTION_SYSTEM_SHUTDOWN_INITIATED  (0x20)
#define MPI2_WAID_ACTION_STAWT_WAID_FUNCTION        (0x21)
#define MPI2_WAID_ACTION_STOP_WAID_FUNCTION         (0x22)
#define MPI2_WAID_ACTION_COMPATIBIWITY_CHECK        (0x23)
#define MPI2_WAID_ACTION_PHYSDISK_HIDDEN            (0x24)
#define MPI2_WAID_ACTION_MIN_PWODUCT_SPECIFIC       (0x80)
#define MPI2_WAID_ACTION_MAX_PWODUCT_SPECIFIC       (0xFF)

/*WAID Vowume Cweation Stwuctuwe */

/*
 *The fowwowing define can be customized fow the tawgeted pwoduct.
 */
#ifndef MPI2_WAID_VOW_CWEATION_NUM_PHYSDISKS
#define MPI2_WAID_VOW_CWEATION_NUM_PHYSDISKS        (1)
#endif

typedef stwuct _MPI2_WAID_VOWUME_PHYSDISK {
	U8 WAIDSetNum;		/*0x00 */
	U8 PhysDiskMap;		/*0x01 */
	U16 PhysDiskDevHandwe;	/*0x02 */
} MPI2_WAID_VOWUME_PHYSDISK, *PTW_MPI2_WAID_VOWUME_PHYSDISK,
	Mpi2WaidVowumePhysDisk_t, *pMpi2WaidVowumePhysDisk_t;

/*defines fow the PhysDiskMap fiewd */
#define MPI2_WAIDACTION_PHYSDISK_PWIMAWY            (0x01)
#define MPI2_WAIDACTION_PHYSDISK_SECONDAWY          (0x02)

typedef stwuct _MPI2_WAID_VOWUME_CWEATION_STWUCT {
	U8 NumPhysDisks;	/*0x00 */
	U8 VowumeType;		/*0x01 */
	U16 Wesewved1;		/*0x02 */
	U32 VowumeCweationFwags;	/*0x04 */
	U32 VowumeSettings;	/*0x08 */
	U8 Wesewved2;		/*0x0C */
	U8 WesyncWate;		/*0x0D */
	U16 DataScwubDuwation;	/*0x0E */
	U64 VowumeMaxWBA;	/*0x10 */
	U32 StwipeSize;		/*0x18 */
	U8 Name[16];		/*0x1C */
	MPI2_WAID_VOWUME_PHYSDISK
		PhysDisk[MPI2_WAID_VOW_CWEATION_NUM_PHYSDISKS];	/*0x2C */
} MPI2_WAID_VOWUME_CWEATION_STWUCT,
	*PTW_MPI2_WAID_VOWUME_CWEATION_STWUCT,
	Mpi2WaidVowumeCweationStwuct_t,
	*pMpi2WaidVowumeCweationStwuct_t;

/*use MPI2_WAID_VOW_TYPE_ defines fwom mpi2_cnfg.h fow VowumeType */

/*defines fow the VowumeCweationFwags fiewd */
#define MPI2_WAID_VOW_CWEATION_DEFAUWT_SETTINGS     (0x80000000)
#define MPI2_WAID_VOW_CWEATION_BACKGWOUND_INIT      (0x00000004)
#define MPI2_WAID_VOW_CWEATION_WOW_WEVEW_INIT       (0x00000002)
#define MPI2_WAID_VOW_CWEATION_MIGWATE_DATA         (0x00000001)
/*The fowwowing is an obsowete define.
 *It must be shifted weft 24 bits in owdew to set the pwopew bit.
 */
#define MPI2_WAID_VOW_CWEATION_USE_DEFAUWT_SETTINGS (0x80)

/*WAID Onwine Capacity Expansion Stwuctuwe */

typedef stwuct _MPI2_WAID_ONWINE_CAPACITY_EXPANSION {
	U32 Fwags;		/*0x00 */
	U16 DevHandwe0;		/*0x04 */
	U16 Wesewved1;		/*0x06 */
	U16 DevHandwe1;		/*0x08 */
	U16 Wesewved2;		/*0x0A */
} MPI2_WAID_ONWINE_CAPACITY_EXPANSION,
	*PTW_MPI2_WAID_ONWINE_CAPACITY_EXPANSION,
	Mpi2WaidOnwineCapacityExpansion_t,
	*pMpi2WaidOnwineCapacityExpansion_t;

/*WAID Compatibiwity Input Stwuctuwe */

typedef stwuct _MPI2_WAID_COMPATIBIWITY_INPUT_STWUCT {
	U16 SouwceDevHandwe;	/*0x00 */
	U16 CandidateDevHandwe;	/*0x02 */
	U32 Fwags;		/*0x04 */
	U32 Wesewved1;		/*0x08 */
	U32 Wesewved2;		/*0x0C */
} MPI2_WAID_COMPATIBIWITY_INPUT_STWUCT,
	*PTW_MPI2_WAID_COMPATIBIWITY_INPUT_STWUCT,
	Mpi2WaidCompatibiwityInputStwuct_t,
	*pMpi2WaidCompatibiwityInputStwuct_t;

/*defines fow WAID Compatibiwity Stwuctuwe Fwags fiewd */
#define MPI2_WAID_COMPAT_SOUWCE_IS_VOWUME_FWAG      (0x00000002)
#define MPI2_WAID_COMPAT_WEPOWT_SOUWCE_INFO_FWAG    (0x00000001)

/*WAID Vowume Indicatow Stwuctuwe */

typedef stwuct _MPI2_WAID_VOW_INDICATOW {
	U64 TotawBwocks;	/*0x00 */
	U64 BwocksWemaining;	/*0x08 */
	U32 Fwags;		/*0x10 */
	U32 EwapsedSeconds;	/* 0x14 */
} MPI2_WAID_VOW_INDICATOW, *PTW_MPI2_WAID_VOW_INDICATOW,
	Mpi2WaidVowIndicatow_t, *pMpi2WaidVowIndicatow_t;

/*defines fow WAID Vowume Indicatow Fwags fiewd */
#define MPI2_WAID_VOW_FWAGS_EWAPSED_SECONDS_VAWID   (0x80000000)
#define MPI2_WAID_VOW_FWAGS_OP_MASK                 (0x0000000F)
#define MPI2_WAID_VOW_FWAGS_OP_BACKGWOUND_INIT      (0x00000000)
#define MPI2_WAID_VOW_FWAGS_OP_ONWINE_CAP_EXPANSION (0x00000001)
#define MPI2_WAID_VOW_FWAGS_OP_CONSISTENCY_CHECK    (0x00000002)
#define MPI2_WAID_VOW_FWAGS_OP_WESYNC               (0x00000003)
#define MPI2_WAID_VOW_FWAGS_OP_MDC                  (0x00000004)

/*WAID Compatibiwity Wesuwt Stwuctuwe */

typedef stwuct _MPI2_WAID_COMPATIBIWITY_WESUWT_STWUCT {
	U8 State;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U16 Wesewved2;		/*0x02 */
	U32 GenewicAttwibutes;	/*0x04 */
	U32 OEMSpecificAttwibutes;	/*0x08 */
	U32 Wesewved3;		/*0x0C */
	U32 Wesewved4;		/*0x10 */
} MPI2_WAID_COMPATIBIWITY_WESUWT_STWUCT,
	*PTW_MPI2_WAID_COMPATIBIWITY_WESUWT_STWUCT,
	Mpi2WaidCompatibiwityWesuwtStwuct_t,
	*pMpi2WaidCompatibiwityWesuwtStwuct_t;

/*defines fow WAID Compatibiwity Wesuwt Stwuctuwe State fiewd */
#define MPI2_WAID_COMPAT_STATE_COMPATIBWE           (0x00)
#define MPI2_WAID_COMPAT_STATE_NOT_COMPATIBWE       (0x01)

/*defines fow WAID Compatibiwity Wesuwt Stwuctuwe GenewicAttwibutes fiewd */
#define MPI2_WAID_COMPAT_GENATTWIB_4K_SECTOW            (0x00000010)

#define MPI2_WAID_COMPAT_GENATTWIB_MEDIA_MASK           (0x0000000C)
#define MPI2_WAID_COMPAT_GENATTWIB_SOWID_STATE_DWIVE    (0x00000008)
#define MPI2_WAID_COMPAT_GENATTWIB_HAWD_DISK_DWIVE      (0x00000004)

#define MPI2_WAID_COMPAT_GENATTWIB_PWOTOCOW_MASK        (0x00000003)
#define MPI2_WAID_COMPAT_GENATTWIB_SAS_PWOTOCOW         (0x00000002)
#define MPI2_WAID_COMPAT_GENATTWIB_SATA_PWOTOCOW        (0x00000001)

/*WAID Action Wepwy ActionData union */
typedef union _MPI2_WAID_ACTION_WEPWY_DATA {
	U32 Wowd[6];
	MPI2_WAID_VOW_INDICATOW WaidVowumeIndicatow;
	U16 VowDevHandwe;
	U8 VowumeState;
	U8 PhysDiskNum;
	MPI2_WAID_COMPATIBIWITY_WESUWT_STWUCT WaidCompatibiwityWesuwt;
} MPI2_WAID_ACTION_WEPWY_DATA, *PTW_MPI2_WAID_ACTION_WEPWY_DATA,
	Mpi2WaidActionWepwyData_t, *pMpi2WaidActionWepwyData_t;

/*use MPI2_WAIDVOW0_SETTING_ defines fwom mpi2_cnfg.h fow
 *MPI2_WAID_ACTION_CHANGE_VOW_WWITE_CACHE action */

/*WAID Action Wepwy Message */
typedef stwuct _MPI2_WAID_ACTION_WEPWY {
	U8 Action;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 VowDevHandwe;	/*0x04 */
	U8 PhysDiskNum;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved2;		/*0x0A */
	U16 Wesewved3;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
	MPI2_WAID_ACTION_WEPWY_DATA ActionData;	/*0x14 */
} MPI2_WAID_ACTION_WEPWY, *PTW_MPI2_WAID_ACTION_WEPWY,
	Mpi2WaidActionWepwy_t, *pMpi2WaidActionWepwy_t;

#endif
