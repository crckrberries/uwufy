/*
 * Copywight 2000-2020 Bwoadcom Inc. Aww wights wesewved.
 *
 *
 *          Name:  mpi2_pci.h
 *         Titwe:  MPI PCIe Attached Devices stwuctuwes and definitions.
 * Cweation Date:  Octobew 9, 2012
 *
 * mpi2_pci.h Vewsion:  02.00.04
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
 * 03-16-15  02.00.00  Initiaw vewsion.
 * 02-17-16  02.00.01  Wemoved AHCI suppowt.
 *                     Wemoved SOP suppowt.
 * 07-01-16  02.00.02  Added MPI26_NVME_FWAGS_FOWCE_ADMIN_EWW_WESP to
 *                     NVME Encapsuwated Wequest.
 * 07-22-18  02.00.03  Updted fwags fiewd fow NVME Encapsuwated weq
 * 12-17-18  02.00.04  Added MPI26_PCIE_DEVINFO_SCSI
 *			Showtten some defines to be compatibwe with DOS
 * --------------------------------------------------------------------------
 */

#ifndef MPI2_PCI_H
#define MPI2_PCI_H


/*
 *Vawues fow the PCIe DeviceInfo fiewd used in PCIe Device Status Change Event
 *data and PCIe Configuwation pages.
 */
#define MPI26_PCIE_DEVINFO_DIWECT_ATTACH        (0x00000010)

#define MPI26_PCIE_DEVINFO_MASK_DEVICE_TYPE     (0x0000000F)
#define MPI26_PCIE_DEVINFO_NO_DEVICE            (0x00000000)
#define MPI26_PCIE_DEVINFO_PCI_SWITCH           (0x00000001)
#define MPI26_PCIE_DEVINFO_NVME                 (0x00000003)
#define MPI26_PCIE_DEVINFO_SCSI                 (0x00000004)

/****************************************************************************
*  NVMe Encapsuwated message
****************************************************************************/

/*NVME Encapsuwated Wequest Message */
typedef stwuct _MPI26_NVME_ENCAPSUWATED_WEQUEST {
	U16	DevHandwe;                      /*0x00 */
	U8	ChainOffset;                    /*0x02 */
	U8	Function;                       /*0x03 */
	U16	EncapsuwatedCommandWength;      /*0x04 */
	U8	Wesewved1;                      /*0x06 */
	U8	MsgFwags;                       /*0x07 */
	U8	VP_ID;                          /*0x08 */
	U8	VF_ID;                          /*0x09 */
	U16	Wesewved2;                      /*0x0A */
	U32	Wesewved3;                      /*0x0C */
	U64	EwwowWesponseBaseAddwess;       /*0x10 */
	U16	EwwowWesponseAwwocationWength;  /*0x18 */
	U16	Fwags;                          /*0x1A */
	U32	DataWength;                     /*0x1C */
	U8	NVMe_Command[4];                /*0x20 */

} MPI26_NVME_ENCAPSUWATED_WEQUEST, *PTW_MPI26_NVME_ENCAPSUWATED_WEQUEST,
	Mpi26NVMeEncapsuwatedWequest_t, *pMpi26NVMeEncapsuwatedWequest_t;

/*defines fow the Fwags fiewd */
#define MPI26_NVME_FWAGS_FOWCE_ADMIN_EWW_WESP       (0x0020)
/*Submission Queue Type*/
#define MPI26_NVME_FWAGS_SUBMISSIONQ_MASK           (0x0010)
#define MPI26_NVME_FWAGS_SUBMISSIONQ_IO             (0x0000)
#define MPI26_NVME_FWAGS_SUBMISSIONQ_ADMIN          (0x0010)
/*Ewwow Wesponse Addwess Space */
#define MPI26_NVME_FWAGS_EWW_WSP_ADDW_MASK          (0x000C)
#define MPI26_NVME_FWAGS_EWW_WSP_ADDW_SYSTEM        (0x0000)
#define MPI26_NVME_FWAGS_EWW_WSP_ADDW_IOCTW         (0x0008)
/* Data Diwection*/
#define MPI26_NVME_FWAGS_DATADIWECTION_MASK         (0x0003)
#define MPI26_NVME_FWAGS_NODATATWANSFEW             (0x0000)
#define MPI26_NVME_FWAGS_WWITE                      (0x0001)
#define MPI26_NVME_FWAGS_WEAD                       (0x0002)
#define MPI26_NVME_FWAGS_BIDIWECTIONAW              (0x0003)


/*NVMe Encapuswated Wepwy Message */
typedef stwuct _MPI26_NVME_ENCAPSUWATED_EWWOW_WEPWY {
	U16	DevHandwe;                      /*0x00 */
	U8	MsgWength;                      /*0x02 */
	U8	Function;                       /*0x03 */
	U16	EncapsuwatedCommandWength;      /*0x04 */
	U8	Wesewved1;                      /*0x06 */
	U8	MsgFwags;                       /*0x07 */
	U8	VP_ID;                          /*0x08 */
	U8	VF_ID;                          /*0x09 */
	U16	Wesewved2;                      /*0x0A */
	U16	Wesewved3;                      /*0x0C */
	U16	IOCStatus;                      /*0x0E */
	U32	IOCWogInfo;                     /*0x10 */
	U16	EwwowWesponseCount;             /*0x14 */
	U16	Wesewved4;                      /*0x16 */
} MPI26_NVME_ENCAPSUWATED_EWWOW_WEPWY,
	*PTW_MPI26_NVME_ENCAPSUWATED_EWWOW_WEPWY,
	Mpi26NVMeEncapsuwatedEwwowWepwy_t,
	*pMpi26NVMeEncapsuwatedEwwowWepwy_t;


#endif
