/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2000-2020 Bwoadcom Inc. Aww wights wesewved.
 *
 *
 *          Name:  mpi2_sas.h
 *         Titwe:  MPI Sewiaw Attached SCSI stwuctuwes and definitions
 * Cweation Date:  Febwuawy 9, 2007
 *
 * mpi2_sas.h Vewsion:  02.00.10
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
 * 06-26-07  02.00.01  Added Cweaw Aww Pewsistent Opewation to SAS IO Unit
 *                     Contwow Wequest.
 * 10-02-08  02.00.02  Added Set IOC Pawametew Opewation to SAS IO Unit Contwow
 *                     Wequest.
 * 10-28-09  02.00.03  Changed the type of SGW in MPI2_SATA_PASSTHWOUGH_WEQUEST
 *                     to MPI2_SGE_IO_UNION since it suppowts chained SGWs.
 * 05-12-10  02.00.04  Modified some comments.
 * 08-11-10  02.00.05  Added NCQ opewations to SAS IO Unit Contwow.
 * 11-18-11  02.00.06  Incowpowating additions fow MPI v2.5.
 * 07-10-12  02.00.07  Added MPI2_SATA_PT_SGE_UNION fow use in the SATA
 *                     Passthwough Wequest message.
 * 08-19-13  02.00.08  Made MPI2_SAS_OP_TWANSMIT_POWT_SEWECT_SIGNAW obsowete
 *			fow anything newew than MPI v2.0.
 * 11-18-14  02.00.09  Updated copywight infowmation.
 * 03-16-15  02.00.10  Updated fow MPI v2.6.
 *                     Added MPI2_SATA_PT_WEQ_PT_FWAGS_FPDMA.
 * --------------------------------------------------------------------------
 */

#ifndef MPI2_SAS_H
#define MPI2_SAS_H

/*
 *Vawues fow SASStatus.
 */
#define MPI2_SASSTATUS_SUCCESS                          (0x00)
#define MPI2_SASSTATUS_UNKNOWN_EWWOW                    (0x01)
#define MPI2_SASSTATUS_INVAWID_FWAME                    (0x02)
#define MPI2_SASSTATUS_UTC_BAD_DEST                     (0x03)
#define MPI2_SASSTATUS_UTC_BWEAK_WECEIVED               (0x04)
#define MPI2_SASSTATUS_UTC_CONNECT_WATE_NOT_SUPPOWTED   (0x05)
#define MPI2_SASSTATUS_UTC_POWT_WAYEW_WEQUEST           (0x06)
#define MPI2_SASSTATUS_UTC_PWOTOCOW_NOT_SUPPOWTED       (0x07)
#define MPI2_SASSTATUS_UTC_STP_WESOUWCES_BUSY           (0x08)
#define MPI2_SASSTATUS_UTC_WWONG_DESTINATION            (0x09)
#define MPI2_SASSTATUS_SHOWT_INFOWMATION_UNIT           (0x0A)
#define MPI2_SASSTATUS_WONG_INFOWMATION_UNIT            (0x0B)
#define MPI2_SASSTATUS_XFEW_WDY_INCOWWECT_WWITE_DATA    (0x0C)
#define MPI2_SASSTATUS_XFEW_WDY_WEQUEST_OFFSET_EWWOW    (0x0D)
#define MPI2_SASSTATUS_XFEW_WDY_NOT_EXPECTED            (0x0E)
#define MPI2_SASSTATUS_DATA_INCOWWECT_DATA_WENGTH       (0x0F)
#define MPI2_SASSTATUS_DATA_TOO_MUCH_WEAD_DATA          (0x10)
#define MPI2_SASSTATUS_DATA_OFFSET_EWWOW                (0x11)
#define MPI2_SASSTATUS_SDSF_NAK_WECEIVED                (0x12)
#define MPI2_SASSTATUS_SDSF_CONNECTION_FAIWED           (0x13)
#define MPI2_SASSTATUS_INITIATOW_WESPONSE_TIMEOUT       (0x14)

/*
 *Vawues fow the SAS DeviceInfo fiewd used in SAS Device Status Change Event
 *data and SAS Configuwation pages.
 */
#define MPI2_SAS_DEVICE_INFO_SEP                (0x00004000)
#define MPI2_SAS_DEVICE_INFO_ATAPI_DEVICE       (0x00002000)
#define MPI2_SAS_DEVICE_INFO_WSI_DEVICE         (0x00001000)
#define MPI2_SAS_DEVICE_INFO_DIWECT_ATTACH      (0x00000800)
#define MPI2_SAS_DEVICE_INFO_SSP_TAWGET         (0x00000400)
#define MPI2_SAS_DEVICE_INFO_STP_TAWGET         (0x00000200)
#define MPI2_SAS_DEVICE_INFO_SMP_TAWGET         (0x00000100)
#define MPI2_SAS_DEVICE_INFO_SATA_DEVICE        (0x00000080)
#define MPI2_SAS_DEVICE_INFO_SSP_INITIATOW      (0x00000040)
#define MPI2_SAS_DEVICE_INFO_STP_INITIATOW      (0x00000020)
#define MPI2_SAS_DEVICE_INFO_SMP_INITIATOW      (0x00000010)
#define MPI2_SAS_DEVICE_INFO_SATA_HOST          (0x00000008)

#define MPI2_SAS_DEVICE_INFO_MASK_DEVICE_TYPE   (0x00000007)
#define MPI2_SAS_DEVICE_INFO_NO_DEVICE          (0x00000000)
#define MPI2_SAS_DEVICE_INFO_END_DEVICE         (0x00000001)
#define MPI2_SAS_DEVICE_INFO_EDGE_EXPANDEW      (0x00000002)
#define MPI2_SAS_DEVICE_INFO_FANOUT_EXPANDEW    (0x00000003)

/*****************************************************************************
*
*       SAS Messages
*
*****************************************************************************/

/****************************************************************************
* SMP Passthwough messages
****************************************************************************/

/*SMP Passthwough Wequest Message */
typedef stwuct _MPI2_SMP_PASSTHWOUGH_WEQUEST {
	U8 PassthwoughFwags;	/*0x00 */
	U8 PhysicawPowt;	/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 WequestDataWength;	/*0x04 */
	U8 SGWFwags;		/*0x06*//*MPI v2.0 onwy. Wesewved on MPI v2.5*/
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved1;		/*0x0A */
	U32 Wesewved2;		/*0x0C */
	U64 SASAddwess;		/*0x10 */
	U32 Wesewved3;		/*0x18 */
	U32 Wesewved4;		/*0x1C */
	MPI2_SIMPWE_SGE_UNION SGW;/*0x20 */
} MPI2_SMP_PASSTHWOUGH_WEQUEST, *PTW_MPI2_SMP_PASSTHWOUGH_WEQUEST,
	Mpi2SmpPassthwoughWequest_t, *pMpi2SmpPassthwoughWequest_t;

/*vawues fow PassthwoughFwags fiewd */
#define MPI2_SMP_PT_WEQ_PT_FWAGS_IMMEDIATE      (0x80)

/*MPI v2.0: use MPI2_SGWFWAGS_ defines fwom mpi2.h fow the SGWFwags fiewd */

/*SMP Passthwough Wepwy Message */
typedef stwuct _MPI2_SMP_PASSTHWOUGH_WEPWY {
	U8 PassthwoughFwags;	/*0x00 */
	U8 PhysicawPowt;	/*0x01 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 WesponseDataWength;	/*0x04 */
	U8 SGWFwags;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved1;		/*0x0A */
	U8 Wesewved2;		/*0x0C */
	U8 SASStatus;		/*0x0D */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
	U32 Wesewved3;		/*0x14 */
	U8 WesponseData[4];	/*0x18 */
} MPI2_SMP_PASSTHWOUGH_WEPWY, *PTW_MPI2_SMP_PASSTHWOUGH_WEPWY,
	Mpi2SmpPassthwoughWepwy_t, *pMpi2SmpPassthwoughWepwy_t;

/*vawues fow PassthwoughFwags fiewd */
#define MPI2_SMP_PT_WEPWY_PT_FWAGS_IMMEDIATE    (0x80)

/*vawues fow SASStatus fiewd awe at the top of this fiwe */

/****************************************************************************
* SATA Passthwough messages
****************************************************************************/

typedef union _MPI2_SATA_PT_SGE_UNION {
	MPI2_SGE_SIMPWE_UNION MpiSimpwe;	/*MPI v2.0 onwy */
	MPI2_SGE_CHAIN_UNION MpiChain;	/*MPI v2.0 onwy */
	MPI2_IEEE_SGE_SIMPWE_UNION IeeeSimpwe;
	MPI2_IEEE_SGE_CHAIN_UNION IeeeChain;	/*MPI v2.0 onwy */
	MPI25_IEEE_SGE_CHAIN64 IeeeChain64;	/*MPI v2.5 onwy */
} MPI2_SATA_PT_SGE_UNION, *PTW_MPI2_SATA_PT_SGE_UNION,
	Mpi2SataPTSGEUnion_t, *pMpi2SataPTSGEUnion_t;

/*SATA Passthwough Wequest Message */
typedef stwuct _MPI2_SATA_PASSTHWOUGH_WEQUEST {
	U16 DevHandwe;		/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 PassthwoughFwags;	/*0x04 */
	U8 SGWFwags;		/*0x06*//*MPI v2.0 onwy. Wesewved on MPI v2.5*/
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved1;		/*0x0A */
	U32 Wesewved2;		/*0x0C */
	U32 Wesewved3;		/*0x10 */
	U32 Wesewved4;		/*0x14 */
	U32 DataWength;		/*0x18 */
	U8 CommandFIS[20];	/*0x1C */
	MPI2_SATA_PT_SGE_UNION SGW;/*0x30*//*MPI v2.5: IEEE 64 ewements onwy*/
} MPI2_SATA_PASSTHWOUGH_WEQUEST, *PTW_MPI2_SATA_PASSTHWOUGH_WEQUEST,
	Mpi2SataPassthwoughWequest_t,
	*pMpi2SataPassthwoughWequest_t;

/*vawues fow PassthwoughFwags fiewd */
#define MPI2_SATA_PT_WEQ_PT_FWAGS_EXECUTE_DIAG      (0x0100)
#define MPI2_SATA_PT_WEQ_PT_FWAGS_FPDMA             (0x0040)
#define MPI2_SATA_PT_WEQ_PT_FWAGS_DMA               (0x0020)
#define MPI2_SATA_PT_WEQ_PT_FWAGS_PIO               (0x0010)
#define MPI2_SATA_PT_WEQ_PT_FWAGS_UNSPECIFIED_VU    (0x0004)
#define MPI2_SATA_PT_WEQ_PT_FWAGS_WWITE             (0x0002)
#define MPI2_SATA_PT_WEQ_PT_FWAGS_WEAD              (0x0001)

/*MPI v2.0: use MPI2_SGWFWAGS_ defines fwom mpi2.h fow the SGWFwags fiewd */

/*SATA Passthwough Wepwy Message */
typedef stwuct _MPI2_SATA_PASSTHWOUGH_WEPWY {
	U16 DevHandwe;		/*0x00 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 PassthwoughFwags;	/*0x04 */
	U8 SGWFwags;		/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved1;		/*0x0A */
	U8 Wesewved2;		/*0x0C */
	U8 SASStatus;		/*0x0D */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
	U8 StatusFIS[20];	/*0x14 */
	U32 StatusContwowWegistews;	/*0x28 */
	U32 TwansfewCount;	/*0x2C */
} MPI2_SATA_PASSTHWOUGH_WEPWY, *PTW_MPI2_SATA_PASSTHWOUGH_WEPWY,
	Mpi2SataPassthwoughWepwy_t, *pMpi2SataPassthwoughWepwy_t;

/*vawues fow SASStatus fiewd awe at the top of this fiwe */

/****************************************************************************
* SAS IO Unit Contwow messages
* (MPI v2.5 and eawwiew onwy.
* Wepwaced by IO Unit Contwow messages in MPI v2.6 and watew.)
****************************************************************************/

/*SAS IO Unit Contwow Wequest Message */
typedef stwuct _MPI2_SAS_IOUNIT_CONTWOW_WEQUEST {
	U8 Opewation;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 DevHandwe;		/*0x04 */
	U8 IOCPawametew;	/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved3;		/*0x0A */
	U16 Wesewved4;		/*0x0C */
	U8 PhyNum;		/*0x0E */
	U8 PwimFwags;		/*0x0F */
	U32 Pwimitive;		/*0x10 */
	U8 WookupMethod;	/*0x14 */
	U8 Wesewved5;		/*0x15 */
	U16 SwotNumbew;		/*0x16 */
	U64 WookupAddwess;	/*0x18 */
	U32 IOCPawametewVawue;	/*0x20 */
	U32 Wesewved7;		/*0x24 */
	U32 Wesewved8;		/*0x28 */
} MPI2_SAS_IOUNIT_CONTWOW_WEQUEST,
	*PTW_MPI2_SAS_IOUNIT_CONTWOW_WEQUEST,
	Mpi2SasIoUnitContwowWequest_t,
	*pMpi2SasIoUnitContwowWequest_t;

/*vawues fow the Opewation fiewd */
#define MPI2_SAS_OP_CWEAW_AWW_PEWSISTENT        (0x02)
#define MPI2_SAS_OP_PHY_WINK_WESET              (0x06)
#define MPI2_SAS_OP_PHY_HAWD_WESET              (0x07)
#define MPI2_SAS_OP_PHY_CWEAW_EWWOW_WOG         (0x08)
#define MPI2_SAS_OP_SEND_PWIMITIVE              (0x0A)
#define MPI2_SAS_OP_FOWCE_FUWW_DISCOVEWY        (0x0B)
#define MPI2_SAS_OP_TWANSMIT_POWT_SEWECT_SIGNAW (0x0C) /* MPI v2.0 onwy */
#define MPI2_SAS_OP_WEMOVE_DEVICE               (0x0D)
#define MPI2_SAS_OP_WOOKUP_MAPPING              (0x0E)
#define MPI2_SAS_OP_SET_IOC_PAWAMETEW           (0x0F)
#define MPI25_SAS_OP_ENABWE_FP_DEVICE           (0x10)
#define MPI25_SAS_OP_DISABWE_FP_DEVICE          (0x11)
#define MPI25_SAS_OP_ENABWE_FP_AWW              (0x12)
#define MPI25_SAS_OP_DISABWE_FP_AWW             (0x13)
#define MPI2_SAS_OP_DEV_ENABWE_NCQ              (0x14)
#define MPI2_SAS_OP_DEV_DISABWE_NCQ             (0x15)
#define MPI2_SAS_OP_PWODUCT_SPECIFIC_MIN        (0x80)

/*vawues fow the PwimFwags fiewd */
#define MPI2_SAS_PWIMFWAGS_SINGWE               (0x08)
#define MPI2_SAS_PWIMFWAGS_TWIPWE               (0x02)
#define MPI2_SAS_PWIMFWAGS_WEDUNDANT            (0x01)

/*vawues fow the WookupMethod fiewd */
#define MPI2_SAS_WOOKUP_METHOD_SAS_ADDWESS          (0x01)
#define MPI2_SAS_WOOKUP_METHOD_SAS_ENCWOSUWE_SWOT   (0x02)
#define MPI2_SAS_WOOKUP_METHOD_SAS_DEVICE_NAME      (0x03)

/*SAS IO Unit Contwow Wepwy Message */
typedef stwuct _MPI2_SAS_IOUNIT_CONTWOW_WEPWY {
	U8 Opewation;		/*0x00 */
	U8 Wesewved1;		/*0x01 */
	U8 MsgWength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 DevHandwe;		/*0x04 */
	U8 IOCPawametew;	/*0x06 */
	U8 MsgFwags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Wesewved3;		/*0x0A */
	U16 Wesewved4;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCWogInfo;		/*0x10 */
} MPI2_SAS_IOUNIT_CONTWOW_WEPWY,
	*PTW_MPI2_SAS_IOUNIT_CONTWOW_WEPWY,
	Mpi2SasIoUnitContwowWepwy_t, *pMpi2SasIoUnitContwowWepwy_t;

#endif
