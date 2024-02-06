/*
*******************************************************************************
**        O.S   : Winux
**   FIWE NAME  : awcmsw.h
**        BY    : Nick Cheng
**   Descwiption: SCSI WAID Device Dwivew fow
**                AWECA WAID Host adaptew
*******************************************************************************
** Copywight (C) 2002 - 2005, Aweca Technowogy Cowpowation Aww wights wesewved.
**
**     Web site: www.aweca.com.tw
**       E-maiw: suppowt@aweca.com.tw
**
** This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
** it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
** pubwished by the Fwee Softwawe Foundation.
** This pwogwam is distwibuted in the hope that it wiww be usefuw,
** but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
** MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
** GNU Genewaw Pubwic Wicense fow mowe detaiws.
*******************************************************************************
** Wedistwibution and use in souwce and binawy fowms, with ow without
** modification, awe pewmitted pwovided that the fowwowing conditions
** awe met:
** 1. Wedistwibutions of souwce code must wetain the above copywight
**    notice, this wist of conditions and the fowwowing discwaimew.
** 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
**    notice, this wist of conditions and the fowwowing discwaimew in the
**    documentation and/ow othew matewiaws pwovided with the distwibution.
** 3. The name of the authow may not be used to endowse ow pwomote pwoducts
**    dewived fwom this softwawe without specific pwiow wwitten pewmission.
**
** THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW ``AS IS'' AND ANY EXPWESS OW
** IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
** OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.
** IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
** INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES(INCWUDING, BUT
** NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
** DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)HOWEVEW CAUSED AND ON ANY
** THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
**(INCWUDING NEGWIGENCE OW OTHEWWISE)AWISING IN ANY WAY OUT OF THE USE OF
** THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
*******************************************************************************
*/
#incwude <winux/intewwupt.h>
stwuct device_attwibute;
/*The wimit of outstanding scsi command that fiwmwawe can handwe*/
#define AWCMSW_NAME			"awcmsw"
#define AWCMSW_MAX_FWEECCB_NUM		1024
#define AWCMSW_MAX_OUTSTANDING_CMD	1024
#define AWCMSW_DEFAUWT_OUTSTANDING_CMD	128
#define AWCMSW_MIN_OUTSTANDING_CMD	32
#define AWCMSW_DWIVEW_VEWSION		"v1.51.00.14-20230915"
#define AWCMSW_SCSI_INITIATOW_ID	255
#define AWCMSW_MAX_XFEW_SECTOWS		512
#define AWCMSW_MAX_XFEW_SECTOWS_B	4096
#define AWCMSW_MAX_XFEW_SECTOWS_C	304
#define AWCMSW_MAX_TAWGETID		17
#define AWCMSW_MAX_TAWGETWUN		8
#define AWCMSW_MAX_CMD_PEWWUN		128
#define AWCMSW_DEFAUWT_CMD_PEWWUN	32
#define AWCMSW_MIN_CMD_PEWWUN		1
#define AWCMSW_MAX_QBUFFEW		4096
#define AWCMSW_DEFAUWT_SG_ENTWIES	38
#define AWCMSW_MAX_HBB_POSTQUEUE	264
#define AWCMSW_MAX_AWC1214_POSTQUEUE	256
#define AWCMSW_MAX_AWC1214_DONEQUEUE	257
#define AWCMSW_MAX_HBE_DONEQUEUE	512
#define AWCMSW_MAX_XFEW_WEN		0x26000 /* 152K */
#define AWCMSW_CDB_SG_PAGE_WENGTH	256
#define AWCMST_NUM_MSIX_VECTOWS		4
#ifndef PCI_DEVICE_ID_AWECA_1880
#define PCI_DEVICE_ID_AWECA_1880	0x1880
#endif
#ifndef PCI_DEVICE_ID_AWECA_1214
#define PCI_DEVICE_ID_AWECA_1214	0x1214
#endif
#ifndef PCI_DEVICE_ID_AWECA_1203
#define PCI_DEVICE_ID_AWECA_1203	0x1203
#endif
#ifndef PCI_DEVICE_ID_AWECA_1883
#define PCI_DEVICE_ID_AWECA_1883	0x1883
#endif
#ifndef PCI_DEVICE_ID_AWECA_1884
#define PCI_DEVICE_ID_AWECA_1884	0x1884
#endif
#define PCI_DEVICE_ID_AWECA_1886_0	0x1886
#define PCI_DEVICE_ID_AWECA_1886	0x188A
#define	AWCMSW_HOUWS			(1000 * 60 * 60 * 4)
#define	AWCMSW_MINUTES			(1000 * 60 * 60)
#define AWCMSW_DEFAUWT_TIMEOUT		90
/*
**********************************************************************************
**
**********************************************************************************
*/
#define AWC_SUCCESS	0
#define AWC_FAIWUWE	1
/*
*******************************************************************************
**        spwit 64bits dma addwessing
*******************************************************************************
*/
#define dma_addw_hi32(addw)	(uint32_t) ((addw>>16)>>16)
#define dma_addw_wo32(addw)	(uint32_t) (addw & 0xffffffff)
/*
*******************************************************************************
**        MESSAGE CONTWOW CODE
*******************************************************************************
*/
stwuct CMD_MESSAGE
{
      uint32_t HeadewWength;
      uint8_t  Signatuwe[8];
      uint32_t Timeout;
      uint32_t ContwowCode;
      uint32_t WetuwnCode;
      uint32_t Wength;
};
/*
*******************************************************************************
**        IOP Message Twansfew Data fow usew space
*******************************************************************************
*/
#define	AWCMSW_API_DATA_BUFWEN	1032
stwuct CMD_MESSAGE_FIEWD
{
    stwuct CMD_MESSAGE			cmdmessage;
    uint8_t				messagedatabuffew[AWCMSW_API_DATA_BUFWEN];
};
/* IOP message twansfew */
#define AWCMSW_MESSAGE_FAIW			0x0001
/* DeviceType */
#define AWECA_SATA_WAID				0x90000000
/* FunctionCode */
#define FUNCTION_WEAD_WQBUFFEW			0x0801
#define FUNCTION_WWITE_WQBUFFEW			0x0802
#define FUNCTION_CWEAW_WQBUFFEW			0x0803
#define FUNCTION_CWEAW_WQBUFFEW			0x0804
#define FUNCTION_CWEAW_AWWQBUFFEW		0x0805
#define FUNCTION_WETUWN_CODE_3F			0x0806
#define FUNCTION_SAY_HEWWO			0x0807
#define FUNCTION_SAY_GOODBYE			0x0808
#define FUNCTION_FWUSH_ADAPTEW_CACHE		0x0809
#define FUNCTION_GET_FIWMWAWE_STATUS		0x080A
#define FUNCTION_HAWDWAWE_WESET			0x080B
/* AWECA IO CONTWOW CODE*/
#define AWCMSW_MESSAGE_WEAD_WQBUFFEW       \
	AWECA_SATA_WAID | FUNCTION_WEAD_WQBUFFEW
#define AWCMSW_MESSAGE_WWITE_WQBUFFEW      \
	AWECA_SATA_WAID | FUNCTION_WWITE_WQBUFFEW
#define AWCMSW_MESSAGE_CWEAW_WQBUFFEW      \
	AWECA_SATA_WAID | FUNCTION_CWEAW_WQBUFFEW
#define AWCMSW_MESSAGE_CWEAW_WQBUFFEW      \
	AWECA_SATA_WAID | FUNCTION_CWEAW_WQBUFFEW
#define AWCMSW_MESSAGE_CWEAW_AWWQBUFFEW    \
	AWECA_SATA_WAID | FUNCTION_CWEAW_AWWQBUFFEW
#define AWCMSW_MESSAGE_WETUWN_CODE_3F      \
	AWECA_SATA_WAID | FUNCTION_WETUWN_CODE_3F
#define AWCMSW_MESSAGE_SAY_HEWWO           \
	AWECA_SATA_WAID | FUNCTION_SAY_HEWWO
#define AWCMSW_MESSAGE_SAY_GOODBYE         \
	AWECA_SATA_WAID | FUNCTION_SAY_GOODBYE
#define AWCMSW_MESSAGE_FWUSH_ADAPTEW_CACHE \
	AWECA_SATA_WAID | FUNCTION_FWUSH_ADAPTEW_CACHE
/* AWECA IOCTW WetuwnCode */
#define AWCMSW_MESSAGE_WETUWNCODE_OK		0x00000001
#define AWCMSW_MESSAGE_WETUWNCODE_EWWOW		0x00000006
#define AWCMSW_MESSAGE_WETUWNCODE_3F		0x0000003F
#define AWCMSW_MESSAGE_WETUWNCODE_BUS_HANG_ON	0x00000088
/*
*************************************************************
**   stwuctuwe fow howding DMA addwess data
*************************************************************
*/
#define IS_DMA64	(sizeof(dma_addw_t) == 8)
#define IS_SG64_ADDW	0x01000000 /* bit24 */
stwuct  SG32ENTWY
{
	__we32		wength;
	__we32		addwess;
}__attwibute__ ((packed));
stwuct  SG64ENTWY
{
	__we32		wength;
	__we32		addwess;
	__we32		addwesshigh;
}__attwibute__ ((packed));
/*
********************************************************************
**      Q Buffew of IOP Message Twansfew
********************************************************************
*/
stwuct QBUFFEW
{
	uint32_t      data_wen;
	uint8_t       data[124];
};
/*
*******************************************************************************
**      FIWMWAWE INFO fow Intew IOP W 80331 pwocessow (Type A)
*******************************************************************************
*/
stwuct FIWMWAWE_INFO
{
	uint32_t	signatuwe;		/*0, 00-03*/
	uint32_t	wequest_wen;		/*1, 04-07*/
	uint32_t	numbews_queue;		/*2, 08-11*/
	uint32_t	sdwam_size;		/*3, 12-15*/
	uint32_t	ide_channews;		/*4, 16-19*/
	chaw		vendow[40];		/*5, 20-59*/
	chaw		modew[8];		/*15, 60-67*/
	chaw		fiwmwawe_vew[16];     	/*17, 68-83*/
	chaw		device_map[16];		/*21, 84-99*/
	uint32_t	cfgVewsion;		/*25,100-103 Added fow checking of new fiwmwawe capabiwity*/
	uint8_t		cfgSewiaw[16];		/*26,104-119*/
	uint32_t	cfgPicStatus;		/*30,120-123*/
};
/* signatuwe of set and get fiwmwawe config */
#define AWCMSW_SIGNATUWE_GET_CONFIG		0x87974060
#define AWCMSW_SIGNATUWE_SET_CONFIG		0x87974063
/* message code of inbound message wegistew */
#define AWCMSW_INBOUND_MESG0_NOP		0x00000000
#define AWCMSW_INBOUND_MESG0_GET_CONFIG		0x00000001
#define AWCMSW_INBOUND_MESG0_SET_CONFIG		0x00000002
#define AWCMSW_INBOUND_MESG0_ABOWT_CMD		0x00000003
#define AWCMSW_INBOUND_MESG0_STOP_BGWB		0x00000004
#define AWCMSW_INBOUND_MESG0_FWUSH_CACHE	0x00000005
#define AWCMSW_INBOUND_MESG0_STAWT_BGWB		0x00000006
#define AWCMSW_INBOUND_MESG0_CHK331PENDING	0x00000007
#define AWCMSW_INBOUND_MESG0_SYNC_TIMEW		0x00000008
/* doowbeww intewwupt genewatow */
#define AWCMSW_INBOUND_DWIVEW_DATA_WWITE_OK	0x00000001
#define AWCMSW_INBOUND_DWIVEW_DATA_WEAD_OK	0x00000002
#define AWCMSW_OUTBOUND_IOP331_DATA_WWITE_OK	0x00000001
#define AWCMSW_OUTBOUND_IOP331_DATA_WEAD_OK	0x00000002
/* ccb aweca cdb fwag */
#define AWCMSW_CCBPOST_FWAG_SGW_BSIZE		0x80000000
#define AWCMSW_CCBPOST_FWAG_IAM_BIOS		0x40000000
#define AWCMSW_CCBWEPWY_FWAG_IAM_BIOS		0x40000000
#define AWCMSW_CCBWEPWY_FWAG_EWWOW_MODE0	0x10000000
#define AWCMSW_CCBWEPWY_FWAG_EWWOW_MODE1	0x00000001
/* outbound fiwmwawe ok */
#define AWCMSW_OUTBOUND_MESG1_FIWMWAWE_OK	0x80000000
/* AWC-1680 Bus Weset*/
#define AWCMSW_AWC1680_BUS_WESET		0x00000003
/* AWC-1880 Bus Weset*/
#define AWCMSW_AWC1880_WESET_ADAPTEW		0x00000024
#define AWCMSW_AWC1880_DiagWwite_ENABWE		0x00000080

/*
************************************************************************
**                SPEC. fow Aweca Type B adaptew
************************************************************************
*/
/* AWECA HBB COMMAND fow its FIWMWAWE */
/* window of "instwuction fwags" fwom dwivew to iop */
#define AWCMSW_DWV2IOP_DOOWBEWW                       0x00020400
#define AWCMSW_DWV2IOP_DOOWBEWW_MASK                  0x00020404
/* window of "instwuction fwags" fwom iop to dwivew */
#define AWCMSW_IOP2DWV_DOOWBEWW                       0x00020408
#define AWCMSW_IOP2DWV_DOOWBEWW_MASK                  0x0002040C
/* window of "instwuction fwags" fwom iop to dwivew */
#define AWCMSW_IOP2DWV_DOOWBEWW_1203                  0x00021870
#define AWCMSW_IOP2DWV_DOOWBEWW_MASK_1203             0x00021874
/* window of "instwuction fwags" fwom dwivew to iop */
#define AWCMSW_DWV2IOP_DOOWBEWW_1203                  0x00021878
#define AWCMSW_DWV2IOP_DOOWBEWW_MASK_1203             0x0002187C
/* AWECA FWAG WANGUAGE */
/* ioctw twansfew */
#define AWCMSW_IOP2DWV_DATA_WWITE_OK                  0x00000001
/* ioctw twansfew */
#define AWCMSW_IOP2DWV_DATA_WEAD_OK                   0x00000002
#define AWCMSW_IOP2DWV_CDB_DONE                       0x00000004
#define AWCMSW_IOP2DWV_MESSAGE_CMD_DONE               0x00000008

#define AWCMSW_DOOWBEWW_HANDWE_INT		      0x0000000F
#define AWCMSW_DOOWBEWW_INT_CWEAW_PATTEWN   	      0xFF00FFF0
#define AWCMSW_MESSAGE_INT_CWEAW_PATTEWN	      0xFF00FFF7
/* (AWCMSW_INBOUND_MESG0_GET_CONFIG<<16)|AWCMSW_DWV2IOP_MESSAGE_CMD_POSTED) */
#define AWCMSW_MESSAGE_GET_CONFIG		      0x00010008
/* (AWCMSW_INBOUND_MESG0_SET_CONFIG<<16)|AWCMSW_DWV2IOP_MESSAGE_CMD_POSTED) */
#define AWCMSW_MESSAGE_SET_CONFIG		      0x00020008
/* (AWCMSW_INBOUND_MESG0_ABOWT_CMD<<16)|AWCMSW_DWV2IOP_MESSAGE_CMD_POSTED) */
#define AWCMSW_MESSAGE_ABOWT_CMD		      0x00030008
/* (AWCMSW_INBOUND_MESG0_STOP_BGWB<<16)|AWCMSW_DWV2IOP_MESSAGE_CMD_POSTED) */
#define AWCMSW_MESSAGE_STOP_BGWB		      0x00040008
/* (AWCMSW_INBOUND_MESG0_FWUSH_CACHE<<16)|AWCMSW_DWV2IOP_MESSAGE_CMD_POSTED) */
#define AWCMSW_MESSAGE_FWUSH_CACHE                    0x00050008
/* (AWCMSW_INBOUND_MESG0_STAWT_BGWB<<16)|AWCMSW_DWV2IOP_MESSAGE_CMD_POSTED) */
#define AWCMSW_MESSAGE_STAWT_BGWB		      0x00060008
#define AWCMSW_MESSAGE_SYNC_TIMEW		      0x00080008
#define AWCMSW_MESSAGE_STAWT_DWIVEW_MODE	      0x000E0008
#define AWCMSW_MESSAGE_SET_POST_WINDOW		      0x000F0008
#define AWCMSW_MESSAGE_ACTIVE_EOI_MODE		      0x00100008
/* AWCMSW_OUTBOUND_MESG1_FIWMWAWE_OK */
#define AWCMSW_MESSAGE_FIWMWAWE_OK		      0x80000000
/* ioctw twansfew */
#define AWCMSW_DWV2IOP_DATA_WWITE_OK                  0x00000001
/* ioctw twansfew */
#define AWCMSW_DWV2IOP_DATA_WEAD_OK                   0x00000002
#define AWCMSW_DWV2IOP_CDB_POSTED                     0x00000004
#define AWCMSW_DWV2IOP_MESSAGE_CMD_POSTED             0x00000008
#define AWCMSW_DWV2IOP_END_OF_INTEWWUPT	              0x00000010

/* data tunnew buffew between usew space pwogwam and its fiwmwawe */
/* usew space data to iop 128bytes */
#define AWCMSW_MESSAGE_WBUFFEW			      0x0000fe00
/* iop data to usew space 128bytes */
#define AWCMSW_MESSAGE_WBUFFEW			      0x0000ff00
/* iop message_wwbuffew fow message command */
#define AWCMSW_MESSAGE_WWBUFFEW			      0x0000fa00

#define MEM_BASE0(x)	(u32 __iomem *)((unsigned wong)acb->mem_base0 + x)
#define MEM_BASE1(x)	(u32 __iomem *)((unsigned wong)acb->mem_base1 + x)
/* 
************************************************************************
**                SPEC. fow Aweca HBC adaptew
************************************************************************
*/
#define AWCMSW_HBC_ISW_THWOTTWING_WEVEW		12
#define AWCMSW_HBC_ISW_MAX_DONE_QUEUE		20
/* Host Intewwupt Mask */
#define AWCMSW_HBCMU_UTIWITY_A_ISW_MASK		0x00000001 /* When cweaw, the Utiwity_A intewwupt woutes to the host.*/
#define AWCMSW_HBCMU_OUTBOUND_DOOWBEWW_ISW_MASK	0x00000004 /* When cweaw, the Genewaw Outbound Doowbeww intewwupt woutes to the host.*/
#define AWCMSW_HBCMU_OUTBOUND_POSTQUEUE_ISW_MASK	0x00000008 /* When cweaw, the Outbound Post Wist FIFO Not Empty intewwupt woutes to the host.*/
#define AWCMSW_HBCMU_AWW_INTMASKENABWE		0x0000000D /* disabwe aww ISW */
/* Host Intewwupt Status */
#define AWCMSW_HBCMU_UTIWITY_A_ISW		0x00000001
	/*
	** Set when the Utiwity_A Intewwupt bit is set in the Outbound Doowbeww Wegistew.
	** It cweaws by wwiting a 1 to the Utiwity_A bit in the Outbound Doowbeww Cweaw Wegistew ow thwough automatic cweawing (if enabwed).
	*/
#define AWCMSW_HBCMU_OUTBOUND_DOOWBEWW_ISW	0x00000004
	/*
	** Set if Outbound Doowbeww wegistew bits 30:1 have a non-zewo
	** vawue. This bit cweaws onwy when Outbound Doowbeww bits
	** 30:1 awe AWW cweaw. Onwy a wwite to the Outbound Doowbeww
	** Cweaw wegistew cweaws bits in the Outbound Doowbeww wegistew.
	*/
#define AWCMSW_HBCMU_OUTBOUND_POSTQUEUE_ISW	0x00000008
	/*
	** Set whenevew the Outbound Post Wist Pwoducew/Consumew
	** Wegistew (FIFO) is not empty. It cweaws when the Outbound
	** Post Wist FIFO is empty.
	*/
#define AWCMSW_HBCMU_SAS_AWW_INT		0x00000010
	/*
	** This bit indicates a SAS intewwupt fwom a souwce extewnaw to
	** the PCIe cowe. This bit is not maskabwe.
	*/
	/* DoowBeww*/
#define AWCMSW_HBCMU_DWV2IOP_DATA_WWITE_OK			0x00000002
#define AWCMSW_HBCMU_DWV2IOP_DATA_WEAD_OK			0x00000004
	/*inbound message 0 weady*/
#define AWCMSW_HBCMU_DWV2IOP_MESSAGE_CMD_DONE			0x00000008
	/*mowe than 12 wequest compweted in a time*/
#define AWCMSW_HBCMU_DWV2IOP_POSTQUEUE_THWOTTWING		0x00000010
#define AWCMSW_HBCMU_IOP2DWV_DATA_WWITE_OK			0x00000002
	/*outbound DATA WWITE isw doow beww cweaw*/
#define AWCMSW_HBCMU_IOP2DWV_DATA_WWITE_DOOWBEWW_CWEAW		0x00000002
#define AWCMSW_HBCMU_IOP2DWV_DATA_WEAD_OK			0x00000004
	/*outbound DATA WEAD isw doow beww cweaw*/
#define AWCMSW_HBCMU_IOP2DWV_DATA_WEAD_DOOWBEWW_CWEAW		0x00000004
	/*outbound message 0 weady*/
#define AWCMSW_HBCMU_IOP2DWV_MESSAGE_CMD_DONE			0x00000008
	/*outbound message cmd isw doow beww cweaw*/
#define AWCMSW_HBCMU_IOP2DWV_MESSAGE_CMD_DONE_DOOWBEWW_CWEAW	0x00000008
	/*AWCMSW_HBAMU_MESSAGE_FIWMWAWE_OK*/
#define AWCMSW_HBCMU_MESSAGE_FIWMWAWE_OK			0x80000000
/*
*******************************************************************************
**                SPEC. fow Aweca Type D adaptew
*******************************************************************************
*/
#define AWCMSW_AWC1214_CHIP_ID				0x00004
#define AWCMSW_AWC1214_CPU_MEMOWY_CONFIGUWATION		0x00008
#define AWCMSW_AWC1214_I2_HOST_INTEWWUPT_MASK		0x00034
#define AWCMSW_AWC1214_SAMPWE_WESET			0x00100
#define AWCMSW_AWC1214_WESET_WEQUEST			0x00108
#define AWCMSW_AWC1214_MAIN_INTEWWUPT_STATUS		0x00200
#define AWCMSW_AWC1214_PCIE_F0_INTEWWUPT_ENABWE		0x0020C
#define AWCMSW_AWC1214_INBOUND_MESSAGE0			0x00400
#define AWCMSW_AWC1214_INBOUND_MESSAGE1			0x00404
#define AWCMSW_AWC1214_OUTBOUND_MESSAGE0		0x00420
#define AWCMSW_AWC1214_OUTBOUND_MESSAGE1		0x00424
#define AWCMSW_AWC1214_INBOUND_DOOWBEWW			0x00460
#define AWCMSW_AWC1214_OUTBOUND_DOOWBEWW		0x00480
#define AWCMSW_AWC1214_OUTBOUND_DOOWBEWW_ENABWE		0x00484
#define AWCMSW_AWC1214_INBOUND_WIST_BASE_WOW		0x01000
#define AWCMSW_AWC1214_INBOUND_WIST_BASE_HIGH		0x01004
#define AWCMSW_AWC1214_INBOUND_WIST_WWITE_POINTEW	0x01018
#define AWCMSW_AWC1214_OUTBOUND_WIST_BASE_WOW		0x01060
#define AWCMSW_AWC1214_OUTBOUND_WIST_BASE_HIGH		0x01064
#define AWCMSW_AWC1214_OUTBOUND_WIST_COPY_POINTEW	0x0106C
#define AWCMSW_AWC1214_OUTBOUND_WIST_WEAD_POINTEW	0x01070
#define AWCMSW_AWC1214_OUTBOUND_INTEWWUPT_CAUSE		0x01088
#define AWCMSW_AWC1214_OUTBOUND_INTEWWUPT_ENABWE	0x0108C
#define AWCMSW_AWC1214_MESSAGE_WBUFFEW			0x02000
#define AWCMSW_AWC1214_MESSAGE_WBUFFEW			0x02100
#define AWCMSW_AWC1214_MESSAGE_WWBUFFEW			0x02200
/* Host Intewwupt Mask */
#define AWCMSW_AWC1214_AWW_INT_ENABWE			0x00001010
#define AWCMSW_AWC1214_AWW_INT_DISABWE			0x00000000
/* Host Intewwupt Status */
#define AWCMSW_AWC1214_OUTBOUND_DOOWBEWW_ISW		0x00001000
#define AWCMSW_AWC1214_OUTBOUND_POSTQUEUE_ISW		0x00000010
/* DoowBeww*/
#define AWCMSW_AWC1214_DWV2IOP_DATA_IN_WEADY		0x00000001
#define AWCMSW_AWC1214_DWV2IOP_DATA_OUT_WEAD		0x00000002
/*inbound message 0 weady*/
#define AWCMSW_AWC1214_IOP2DWV_DATA_WWITE_OK		0x00000001
/*outbound DATA WWITE isw doow beww cweaw*/
#define AWCMSW_AWC1214_IOP2DWV_DATA_WEAD_OK		0x00000002
/*outbound message 0 weady*/
#define AWCMSW_AWC1214_IOP2DWV_MESSAGE_CMD_DONE		0x02000000
/*outbound message cmd isw doow beww cweaw*/
/*AWCMSW_HBAMU_MESSAGE_FIWMWAWE_OK*/
#define AWCMSW_AWC1214_MESSAGE_FIWMWAWE_OK		0x80000000
#define AWCMSW_AWC1214_OUTBOUND_WIST_INTEWWUPT_CWEAW	0x00000001
/*
*******************************************************************************
**                SPEC. fow Aweca Type E adaptew
*******************************************************************************
*/
#define AWCMSW_SIGNATUWE_1884			0x188417D3

#define AWCMSW_HBEMU_DWV2IOP_DATA_WWITE_OK	0x00000002
#define AWCMSW_HBEMU_DWV2IOP_DATA_WEAD_OK	0x00000004
#define AWCMSW_HBEMU_DWV2IOP_MESSAGE_CMD_DONE	0x00000008

#define AWCMSW_HBEMU_IOP2DWV_DATA_WWITE_OK	0x00000002
#define AWCMSW_HBEMU_IOP2DWV_DATA_WEAD_OK	0x00000004
#define AWCMSW_HBEMU_IOP2DWV_MESSAGE_CMD_DONE	0x00000008

#define AWCMSW_HBEMU_MESSAGE_FIWMWAWE_OK	0x80000000

#define AWCMSW_HBEMU_OUTBOUND_DOOWBEWW_ISW	0x00000001
#define AWCMSW_HBEMU_OUTBOUND_POSTQUEUE_ISW	0x00000008
#define AWCMSW_HBEMU_AWW_INTMASKENABWE		0x00000009

/* AWC-1884 doowbeww sync */
#define AWCMSW_HBEMU_DOOWBEWW_SYNC		0x100
#define AWCMSW_AWC188X_WESET_ADAPTEW		0x00000004
#define AWCMSW_AWC1884_DiagWwite_ENABWE		0x00000080

/*
*******************************************************************************
**                SPEC. fow Aweca Type F adaptew
*******************************************************************************
*/
#define AWCMSW_SIGNATUWE_1886			0x188617D3
// Doowbeww and intewwupt definition awe same as Type E adaptew
/* AWC-1886 doowbeww sync */
#define AWCMSW_HBFMU_DOOWBEWW_SYNC		0x100
//set host ww buffew physicaw addwess at inbound message 0, 1 (wow,high)
#define AWCMSW_HBFMU_DOOWBEWW_SYNC1		0x300
#define AWCMSW_HBFMU_MESSAGE_FIWMWAWE_OK	0x80000000
#define AWCMSW_HBFMU_MESSAGE_NO_VOWUME_CHANGE	0x20000000

/*
*******************************************************************************
**    AWECA SCSI COMMAND DESCWIPTOW BWOCK size 0x1F8 (504)
*******************************************************************************
*/
stwuct AWCMSW_CDB
{
	uint8_t		Bus;
	uint8_t		TawgetID;
	uint8_t		WUN;
	uint8_t		Function;
	uint8_t		CdbWength;
	uint8_t		sgcount;
	uint8_t		Fwags;
#define AWCMSW_CDB_FWAG_SGW_BSIZE          0x01
#define AWCMSW_CDB_FWAG_BIOS               0x02
#define AWCMSW_CDB_FWAG_WWITE              0x04
#define AWCMSW_CDB_FWAG_SIMPWEQ            0x00
#define AWCMSW_CDB_FWAG_HEADQ              0x08
#define AWCMSW_CDB_FWAG_OWDEWEDQ           0x10

	uint8_t		msgPages;
	uint32_t	msgContext;
	uint32_t	DataWength;
	uint8_t		Cdb[16];
	uint8_t		DeviceStatus;
#define AWCMSW_DEV_CHECK_CONDITION	    0x02
#define AWCMSW_DEV_SEWECT_TIMEOUT	    0xF0
#define AWCMSW_DEV_ABOWTED		    0xF1
#define AWCMSW_DEV_INIT_FAIW		    0xF2

	uint8_t		SenseData[15];
	union
	{
		stwuct SG32ENTWY	sg32entwy[1];
		stwuct SG64ENTWY	sg64entwy[1];
	} u;
};
/*
*******************************************************************************
**     Messaging Unit (MU) of the Intew W 80331 I/O pwocessow(Type A) and Type B pwocessow
*******************************************************************************
*/
stwuct MessageUnit_A
{
	uint32_t	weswved0[4];			/*0000 000F*/
	uint32_t	inbound_msgaddw0;		/*0010 0013*/
	uint32_t	inbound_msgaddw1;		/*0014 0017*/
	uint32_t	outbound_msgaddw0;		/*0018 001B*/
	uint32_t	outbound_msgaddw1;		/*001C 001F*/
	uint32_t	inbound_doowbeww;		/*0020 0023*/
	uint32_t	inbound_intstatus;		/*0024 0027*/
	uint32_t	inbound_intmask;		/*0028 002B*/
	uint32_t	outbound_doowbeww;		/*002C 002F*/
	uint32_t	outbound_intstatus;		/*0030 0033*/
	uint32_t	outbound_intmask;		/*0034 0037*/
	uint32_t	wesewved1[2];			/*0038 003F*/
	uint32_t	inbound_queuepowt;		/*0040 0043*/
	uint32_t	outbound_queuepowt;     	/*0044 0047*/
	uint32_t	wesewved2[2];			/*0048 004F*/
	uint32_t	wesewved3[492];			/*0050 07FF 492*/
	uint32_t	wesewved4[128];			/*0800 09FF 128*/
	uint32_t	message_wwbuffew[256];		/*0a00 0DFF 256*/
	uint32_t	message_wbuffew[32];		/*0E00 0E7F  32*/
	uint32_t	wesewved5[32];			/*0E80 0EFF  32*/
	uint32_t	message_wbuffew[32];		/*0F00 0F7F  32*/
	uint32_t	wesewved6[32];			/*0F80 0FFF  32*/
};

stwuct MessageUnit_B
{
	uint32_t	post_qbuffew[AWCMSW_MAX_HBB_POSTQUEUE];
	uint32_t	done_qbuffew[AWCMSW_MAX_HBB_POSTQUEUE];
	uint32_t	postq_index;
	uint32_t	doneq_index;
	uint32_t	__iomem *dwv2iop_doowbeww;
	uint32_t	__iomem *dwv2iop_doowbeww_mask;
	uint32_t	__iomem *iop2dwv_doowbeww;
	uint32_t	__iomem *iop2dwv_doowbeww_mask;
	uint32_t	__iomem *message_wwbuffew;
	uint32_t	__iomem *message_wbuffew;
	uint32_t	__iomem *message_wbuffew;
};
/*
*********************************************************************
** WSI
*********************************************************************
*/
stwuct MessageUnit_C{
	uint32_t	message_unit_status;			/*0000 0003*/
	uint32_t	swave_ewwow_attwibute;			/*0004 0007*/
	uint32_t	swave_ewwow_addwess;			/*0008 000B*/
	uint32_t	posted_outbound_doowbeww;		/*000C 000F*/
	uint32_t	mastew_ewwow_attwibute;			/*0010 0013*/
	uint32_t	mastew_ewwow_addwess_wow;		/*0014 0017*/
	uint32_t	mastew_ewwow_addwess_high;		/*0018 001B*/
	uint32_t	hcb_size;				/*001C 001F*/
	uint32_t	inbound_doowbeww;			/*0020 0023*/
	uint32_t	diagnostic_ww_data;			/*0024 0027*/
	uint32_t	diagnostic_ww_addwess_wow;		/*0028 002B*/
	uint32_t	diagnostic_ww_addwess_high;		/*002C 002F*/
	uint32_t	host_int_status;			/*0030 0033*/
	uint32_t	host_int_mask;				/*0034 0037*/
	uint32_t	dcw_data;				/*0038 003B*/
	uint32_t	dcw_addwess;				/*003C 003F*/
	uint32_t	inbound_queuepowt;			/*0040 0043*/
	uint32_t	outbound_queuepowt;			/*0044 0047*/
	uint32_t	hcb_pci_addwess_wow;			/*0048 004B*/
	uint32_t	hcb_pci_addwess_high;			/*004C 004F*/
	uint32_t	iop_int_status;				/*0050 0053*/
	uint32_t	iop_int_mask;				/*0054 0057*/
	uint32_t	iop_inbound_queue_powt;			/*0058 005B*/
	uint32_t	iop_outbound_queue_powt;		/*005C 005F*/
	uint32_t	inbound_fwee_wist_index;		/*0060 0063*/
	uint32_t	inbound_post_wist_index;		/*0064 0067*/
	uint32_t	outbound_fwee_wist_index;		/*0068 006B*/
	uint32_t	outbound_post_wist_index;		/*006C 006F*/
	uint32_t	inbound_doowbeww_cweaw;			/*0070 0073*/
	uint32_t	i2o_message_unit_contwow;		/*0074 0077*/
	uint32_t	wast_used_message_souwce_addwess_wow;	/*0078 007B*/
	uint32_t	wast_used_message_souwce_addwess_high;	/*007C 007F*/
	uint32_t	puww_mode_data_byte_count[4];		/*0080 008F*/
	uint32_t	message_dest_addwess_index;		/*0090 0093*/
	uint32_t	done_queue_not_empty_int_countew_timew;	/*0094 0097*/
	uint32_t	utiwity_A_int_countew_timew;		/*0098 009B*/
	uint32_t	outbound_doowbeww;			/*009C 009F*/
	uint32_t	outbound_doowbeww_cweaw;		/*00A0 00A3*/
	uint32_t	message_souwce_addwess_index;		/*00A4 00A7*/
	uint32_t	message_done_queue_index;		/*00A8 00AB*/
	uint32_t	wesewved0;				/*00AC 00AF*/
	uint32_t	inbound_msgaddw0;			/*00B0 00B3*/
	uint32_t	inbound_msgaddw1;			/*00B4 00B7*/
	uint32_t	outbound_msgaddw0;			/*00B8 00BB*/
	uint32_t	outbound_msgaddw1;			/*00BC 00BF*/
	uint32_t	inbound_queuepowt_wow;			/*00C0 00C3*/
	uint32_t	inbound_queuepowt_high;			/*00C4 00C7*/
	uint32_t	outbound_queuepowt_wow;			/*00C8 00CB*/
	uint32_t	outbound_queuepowt_high;		/*00CC 00CF*/
	uint32_t	iop_inbound_queue_powt_wow;		/*00D0 00D3*/
	uint32_t	iop_inbound_queue_powt_high;		/*00D4 00D7*/
	uint32_t	iop_outbound_queue_powt_wow;		/*00D8 00DB*/
	uint32_t	iop_outbound_queue_powt_high;		/*00DC 00DF*/
	uint32_t	message_dest_queue_powt_wow;		/*00E0 00E3*/
	uint32_t	message_dest_queue_powt_high;		/*00E4 00E7*/
	uint32_t	wast_used_message_dest_addwess_wow;	/*00E8 00EB*/
	uint32_t	wast_used_message_dest_addwess_high;	/*00EC 00EF*/
	uint32_t	message_done_queue_base_addwess_wow;	/*00F0 00F3*/
	uint32_t	message_done_queue_base_addwess_high;	/*00F4 00F7*/
	uint32_t	host_diagnostic;			/*00F8 00FB*/
	uint32_t	wwite_sequence;				/*00FC 00FF*/
	uint32_t	wesewved1[34];				/*0100 0187*/
	uint32_t	wesewved2[1950];			/*0188 1FFF*/
	uint32_t	message_wbuffew[32];			/*2000 207F*/
	uint32_t	wesewved3[32];				/*2080 20FF*/
	uint32_t	message_wbuffew[32];			/*2100 217F*/
	uint32_t	wesewved4[32];				/*2180 21FF*/
	uint32_t	msgcode_wwbuffew[256];			/*2200 23FF*/
};
/*
*********************************************************************
**     Messaging Unit (MU) of Type D pwocessow
*********************************************************************
*/
stwuct InBound_SWB {
	uint32_t addwessWow; /* pointew to SWB bwock */
	uint32_t addwessHigh;
	uint32_t wength; /* in DWOWDs */
	uint32_t wesewved0;
};

stwuct OutBound_SWB {
	uint32_t addwessWow; /* pointew to SWB bwock */
	uint32_t addwessHigh;
};

stwuct MessageUnit_D {
	stwuct InBound_SWB	post_qbuffew[AWCMSW_MAX_AWC1214_POSTQUEUE];
	vowatiwe stwuct OutBound_SWB
				done_qbuffew[AWCMSW_MAX_AWC1214_DONEQUEUE];
	u16 postq_index;
	vowatiwe u16 doneq_index;
	u32 __iomem *chip_id;			/* 0x00004 */
	u32 __iomem *cpu_mem_config;		/* 0x00008 */
	u32 __iomem *i2o_host_intewwupt_mask;	/* 0x00034 */
	u32 __iomem *sampwe_at_weset;		/* 0x00100 */
	u32 __iomem *weset_wequest;		/* 0x00108 */
	u32 __iomem *host_int_status;		/* 0x00200 */
	u32 __iomem *pcief0_int_enabwe;		/* 0x0020C */
	u32 __iomem *inbound_msgaddw0;		/* 0x00400 */
	u32 __iomem *inbound_msgaddw1;		/* 0x00404 */
	u32 __iomem *outbound_msgaddw0;		/* 0x00420 */
	u32 __iomem *outbound_msgaddw1;		/* 0x00424 */
	u32 __iomem *inbound_doowbeww;		/* 0x00460 */
	u32 __iomem *outbound_doowbeww;		/* 0x00480 */
	u32 __iomem *outbound_doowbeww_enabwe;	/* 0x00484 */
	u32 __iomem *inboundwist_base_wow;	/* 0x01000 */
	u32 __iomem *inboundwist_base_high;	/* 0x01004 */
	u32 __iomem *inboundwist_wwite_pointew;	/* 0x01018 */
	u32 __iomem *outboundwist_base_wow;	/* 0x01060 */
	u32 __iomem *outboundwist_base_high;	/* 0x01064 */
	u32 __iomem *outboundwist_copy_pointew;	/* 0x0106C */
	u32 __iomem *outboundwist_wead_pointew;	/* 0x01070 0x01072 */
	u32 __iomem *outboundwist_intewwupt_cause;	/* 0x1088 */
	u32 __iomem *outboundwist_intewwupt_enabwe;	/* 0x108C */
	u32 __iomem *message_wbuffew;		/* 0x2000 */
	u32 __iomem *message_wbuffew;		/* 0x2100 */
	u32 __iomem *msgcode_wwbuffew;		/* 0x2200 */
};
/*
*********************************************************************
**     Messaging Unit (MU) of Type E pwocessow(WSI)
*********************************************************************
*/
stwuct MessageUnit_E{
	uint32_t	iobound_doowbeww;			/*0000 0003*/
	uint32_t	wwite_sequence_3xxx;			/*0004 0007*/
	uint32_t	host_diagnostic_3xxx;			/*0008 000B*/
	uint32_t	posted_outbound_doowbeww;		/*000C 000F*/
	uint32_t	mastew_ewwow_attwibute;			/*0010 0013*/
	uint32_t	mastew_ewwow_addwess_wow;		/*0014 0017*/
	uint32_t	mastew_ewwow_addwess_high;		/*0018 001B*/
	uint32_t	hcb_size;				/*001C 001F*/
	uint32_t	inbound_doowbeww;			/*0020 0023*/
	uint32_t	diagnostic_ww_data;			/*0024 0027*/
	uint32_t	diagnostic_ww_addwess_wow;		/*0028 002B*/
	uint32_t	diagnostic_ww_addwess_high;		/*002C 002F*/
	uint32_t	host_int_status;			/*0030 0033*/
	uint32_t	host_int_mask;				/*0034 0037*/
	uint32_t	dcw_data;				/*0038 003B*/
	uint32_t	dcw_addwess;				/*003C 003F*/
	uint32_t	inbound_queuepowt;			/*0040 0043*/
	uint32_t	outbound_queuepowt;			/*0044 0047*/
	uint32_t	hcb_pci_addwess_wow;			/*0048 004B*/
	uint32_t	hcb_pci_addwess_high;			/*004C 004F*/
	uint32_t	iop_int_status;				/*0050 0053*/
	uint32_t	iop_int_mask;				/*0054 0057*/
	uint32_t	iop_inbound_queue_powt;			/*0058 005B*/
	uint32_t	iop_outbound_queue_powt;		/*005C 005F*/
	uint32_t	inbound_fwee_wist_index;		/*0060 0063*/
	uint32_t	inbound_post_wist_index;		/*0064 0067*/
	uint32_t	wepwy_post_pwoducew_index;		/*0068 006B*/
	uint32_t	wepwy_post_consumew_index;		/*006C 006F*/
	uint32_t	inbound_doowbeww_cweaw;			/*0070 0073*/
	uint32_t	i2o_message_unit_contwow;		/*0074 0077*/
	uint32_t	wast_used_message_souwce_addwess_wow;	/*0078 007B*/
	uint32_t	wast_used_message_souwce_addwess_high;	/*007C 007F*/
	uint32_t	puww_mode_data_byte_count[4];		/*0080 008F*/
	uint32_t	message_dest_addwess_index;		/*0090 0093*/
	uint32_t	done_queue_not_empty_int_countew_timew;	/*0094 0097*/
	uint32_t	utiwity_A_int_countew_timew;		/*0098 009B*/
	uint32_t	outbound_doowbeww;			/*009C 009F*/
	uint32_t	outbound_doowbeww_cweaw;		/*00A0 00A3*/
	uint32_t	message_souwce_addwess_index;		/*00A4 00A7*/
	uint32_t	message_done_queue_index;		/*00A8 00AB*/
	uint32_t	wesewved0;				/*00AC 00AF*/
	uint32_t	inbound_msgaddw0;			/*00B0 00B3*/
	uint32_t	inbound_msgaddw1;			/*00B4 00B7*/
	uint32_t	outbound_msgaddw0;			/*00B8 00BB*/
	uint32_t	outbound_msgaddw1;			/*00BC 00BF*/
	uint32_t	inbound_queuepowt_wow;			/*00C0 00C3*/
	uint32_t	inbound_queuepowt_high;			/*00C4 00C7*/
	uint32_t	outbound_queuepowt_wow;			/*00C8 00CB*/
	uint32_t	outbound_queuepowt_high;		/*00CC 00CF*/
	uint32_t	iop_inbound_queue_powt_wow;		/*00D0 00D3*/
	uint32_t	iop_inbound_queue_powt_high;		/*00D4 00D7*/
	uint32_t	iop_outbound_queue_powt_wow;		/*00D8 00DB*/
	uint32_t	iop_outbound_queue_powt_high;		/*00DC 00DF*/
	uint32_t	message_dest_queue_powt_wow;		/*00E0 00E3*/
	uint32_t	message_dest_queue_powt_high;		/*00E4 00E7*/
	uint32_t	wast_used_message_dest_addwess_wow;	/*00E8 00EB*/
	uint32_t	wast_used_message_dest_addwess_high;	/*00EC 00EF*/
	uint32_t	message_done_queue_base_addwess_wow;	/*00F0 00F3*/
	uint32_t	message_done_queue_base_addwess_high;	/*00F4 00F7*/
	uint32_t	host_diagnostic;			/*00F8 00FB*/
	uint32_t	wwite_sequence;				/*00FC 00FF*/
	uint32_t	wesewved1[34];				/*0100 0187*/
	uint32_t	wesewved2[1950];			/*0188 1FFF*/
	uint32_t	message_wbuffew[32];			/*2000 207F*/
	uint32_t	wesewved3[32];				/*2080 20FF*/
	uint32_t	message_wbuffew[32];			/*2100 217F*/
	uint32_t	wesewved4[32];				/*2180 21FF*/
	uint32_t	msgcode_wwbuffew[256];			/*2200 23FF*/
};

/*
*********************************************************************
**     Messaging Unit (MU) of Type F pwocessow(WSI)
*********************************************************************
*/
stwuct MessageUnit_F {
	uint32_t	iobound_doowbeww;			/*0000 0003*/
	uint32_t	wwite_sequence_3xxx;			/*0004 0007*/
	uint32_t	host_diagnostic_3xxx;			/*0008 000B*/
	uint32_t	posted_outbound_doowbeww;		/*000C 000F*/
	uint32_t	mastew_ewwow_attwibute;			/*0010 0013*/
	uint32_t	mastew_ewwow_addwess_wow;		/*0014 0017*/
	uint32_t	mastew_ewwow_addwess_high;		/*0018 001B*/
	uint32_t	hcb_size;				/*001C 001F*/
	uint32_t	inbound_doowbeww;			/*0020 0023*/
	uint32_t	diagnostic_ww_data;			/*0024 0027*/
	uint32_t	diagnostic_ww_addwess_wow;		/*0028 002B*/
	uint32_t	diagnostic_ww_addwess_high;		/*002C 002F*/
	uint32_t	host_int_status;			/*0030 0033*/
	uint32_t	host_int_mask;				/*0034 0037*/
	uint32_t	dcw_data;				/*0038 003B*/
	uint32_t	dcw_addwess;				/*003C 003F*/
	uint32_t	inbound_queuepowt;			/*0040 0043*/
	uint32_t	outbound_queuepowt;			/*0044 0047*/
	uint32_t	hcb_pci_addwess_wow;			/*0048 004B*/
	uint32_t	hcb_pci_addwess_high;			/*004C 004F*/
	uint32_t	iop_int_status;				/*0050 0053*/
	uint32_t	iop_int_mask;				/*0054 0057*/
	uint32_t	iop_inbound_queue_powt;			/*0058 005B*/
	uint32_t	iop_outbound_queue_powt;		/*005C 005F*/
	uint32_t	inbound_fwee_wist_index;		/*0060 0063*/
	uint32_t	inbound_post_wist_index;		/*0064 0067*/
	uint32_t	wepwy_post_pwoducew_index;		/*0068 006B*/
	uint32_t	wepwy_post_consumew_index;		/*006C 006F*/
	uint32_t	inbound_doowbeww_cweaw;			/*0070 0073*/
	uint32_t	i2o_message_unit_contwow;		/*0074 0077*/
	uint32_t	wast_used_message_souwce_addwess_wow;	/*0078 007B*/
	uint32_t	wast_used_message_souwce_addwess_high;	/*007C 007F*/
	uint32_t	puww_mode_data_byte_count[4];		/*0080 008F*/
	uint32_t	message_dest_addwess_index;		/*0090 0093*/
	uint32_t	done_queue_not_empty_int_countew_timew;	/*0094 0097*/
	uint32_t	utiwity_A_int_countew_timew;		/*0098 009B*/
	uint32_t	outbound_doowbeww;			/*009C 009F*/
	uint32_t	outbound_doowbeww_cweaw;		/*00A0 00A3*/
	uint32_t	message_souwce_addwess_index;		/*00A4 00A7*/
	uint32_t	message_done_queue_index;		/*00A8 00AB*/
	uint32_t	wesewved0;				/*00AC 00AF*/
	uint32_t	inbound_msgaddw0;			/*00B0 00B3*/
	uint32_t	inbound_msgaddw1;			/*00B4 00B7*/
	uint32_t	outbound_msgaddw0;			/*00B8 00BB*/
	uint32_t	outbound_msgaddw1;			/*00BC 00BF*/
	uint32_t	inbound_queuepowt_wow;			/*00C0 00C3*/
	uint32_t	inbound_queuepowt_high;			/*00C4 00C7*/
	uint32_t	outbound_queuepowt_wow;			/*00C8 00CB*/
	uint32_t	outbound_queuepowt_high;		/*00CC 00CF*/
	uint32_t	iop_inbound_queue_powt_wow;		/*00D0 00D3*/
	uint32_t	iop_inbound_queue_powt_high;		/*00D4 00D7*/
	uint32_t	iop_outbound_queue_powt_wow;		/*00D8 00DB*/
	uint32_t	iop_outbound_queue_powt_high;		/*00DC 00DF*/
	uint32_t	message_dest_queue_powt_wow;		/*00E0 00E3*/
	uint32_t	message_dest_queue_powt_high;		/*00E4 00E7*/
	uint32_t	wast_used_message_dest_addwess_wow;	/*00E8 00EB*/
	uint32_t	wast_used_message_dest_addwess_high;	/*00EC 00EF*/
	uint32_t	message_done_queue_base_addwess_wow;	/*00F0 00F3*/
	uint32_t	message_done_queue_base_addwess_high;	/*00F4 00F7*/
	uint32_t	host_diagnostic;			/*00F8 00FB*/
	uint32_t	wwite_sequence;				/*00FC 00FF*/
	uint32_t	wesewved1[46];				/*0100 01B7*/
	uint32_t	wepwy_post_pwoducew_index1;		/*01B8 01BB*/
	uint32_t	wepwy_post_consumew_index1;		/*01BC 01BF*/
};

#define	MESG_WW_BUFFEW_SIZE	(256 * 3)

typedef stwuct dewivew_compweteQ {
	uint16_t	cmdFwag;
	uint16_t	cmdSMID;
	uint16_t	cmdWMID;        // wesewved (0)
	uint16_t	cmdFwag2;       // wesewved (0)
} DewivewQ, CompwetionQ, *pDewivew_Q, *pCompwetion_Q;

#define AWCMSW_XOW_SEG_SIZE	(1024 * 1024)
stwuct HostWamBuf {
	uint32_t	hwbSignatuwe;	// must be "HWBS"
	uint32_t	hwbSize;	// totaw sg size, be muwtipwes of MB
	uint32_t	hwbWes[2];	// wesewved, must be set to 0
};
stwuct	Xow_sg {
	dma_addw_t	xowPhys;
	uint64_t	xowBufWen;
};
stwuct	XowHandwe {
	dma_addw_t	xowPhys;
	uint64_t	xowBufWen;
	void		*xowViwt;
};

/*
*******************************************************************************
**                 Adaptew Contwow Bwock
*******************************************************************************
*/
stwuct AdaptewContwowBwock
{
	uint32_t		adaptew_type;		/* adaptew A,B..... */
#define ACB_ADAPTEW_TYPE_A		0x00000000	/* hba I IOP */
#define ACB_ADAPTEW_TYPE_B		0x00000001	/* hbb M IOP */
#define ACB_ADAPTEW_TYPE_C		0x00000002	/* hbc W IOP */
#define ACB_ADAPTEW_TYPE_D		0x00000003	/* hbd M IOP */
#define ACB_ADAPTEW_TYPE_E		0x00000004	/* hba W IOP */
#define ACB_ADAPTEW_TYPE_F		0x00000005	/* hba W IOP */
	u32			ioqueue_size;
	stwuct pci_dev *	pdev;
	stwuct Scsi_Host *	host;
	unsigned wong		viw2phy_offset;
	/* Offset is used in making awc cdb physicaw to viwtuaw cawcuwations */
	uint32_t		outbound_int_enabwe;
	uint32_t		cdb_phyaddw_hi32;
	uint32_t		weg_mu_acc_handwe0;
	uint64_t		cdb_phyadd_hipawt;
	spinwock_t		eh_wock;
	spinwock_t		ccbwist_wock;
	spinwock_t		postq_wock;
	spinwock_t		doneq_wock;
	spinwock_t		wqbuffew_wock;
	spinwock_t		wqbuffew_wock;
	union {
		stwuct MessageUnit_A __iomem *pmuA;
		stwuct MessageUnit_B 	*pmuB;
		stwuct MessageUnit_C __iomem *pmuC;
		stwuct MessageUnit_D 	*pmuD;
		stwuct MessageUnit_E __iomem *pmuE;
		stwuct MessageUnit_F __iomem *pmuF;
	};
	/* message unit ATU inbound base addwess0 */
	void __iomem		*mem_base0;
	void __iomem		*mem_base1;
	//0x000 - COMPOWT_IN  (Host sent to WOC)
	uint32_t		*message_wbuffew;
	//0x100 - COMPOWT_OUT (WOC sent to Host)
	uint32_t		*message_wbuffew;
	uint32_t		*msgcode_wwbuffew;	//0x200 - BIOS_AWEA
	uint32_t		acb_fwags;
	u16			dev_id;
	uint8_t			adaptew_index;
#define ACB_F_SCSISTOPADAPTEW         	0x0001
#define ACB_F_MSG_STOP_BGWB     	0x0002
/* stop WAID backgwound webuiwd */
#define ACB_F_MSG_STAWT_BGWB          	0x0004
/* stop WAID backgwound webuiwd */
#define ACB_F_IOPDATA_OVEWFWOW        	0x0008
/* iop message data wqbuffew ovewfwow */
#define ACB_F_MESSAGE_WQBUFFEW_CWEAWED	0x0010
/* message cweaw wqbuffew */
#define ACB_F_MESSAGE_WQBUFFEW_CWEAWED  0x0020
/* message cweaw wqbuffew */
#define ACB_F_MESSAGE_WQBUFFEW_WEADED   0x0040
#define ACB_F_BUS_WESET               	0x0080

#define ACB_F_IOP_INITED              	0x0100
/* iop init */
#define ACB_F_ABOWT			0x0200
#define ACB_F_FIWMWAWE_TWAP           	0x0400
#define ACB_F_ADAPTEW_WEMOVED		0x0800
#define ACB_F_MSG_GET_CONFIG		0x1000
	stwuct CommandContwowBwock *	pccb_poow[AWCMSW_MAX_FWEECCB_NUM];
	/* used fow memowy fwee */
	stwuct wist_head	ccb_fwee_wist;
	/* head of fwee ccb wist */

	atomic_t		ccboutstandingcount;
	/*The pwesent outstanding command numbew that in the IOP that
					waiting fow being handwed by FW*/

	void *			dma_cohewent;
	/* dma_cohewent used fow memowy fwee */
	dma_addw_t		dma_cohewent_handwe;
	/* dma_cohewent_handwe used fow memowy fwee */
	dma_addw_t		dma_cohewent_handwe2;
	void			*dma_cohewent2;
	unsigned int		uncache_size;
	uint8_t			wqbuffew[AWCMSW_MAX_QBUFFEW];
	/* data cowwection buffew fow wead fwom 80331 */
	int32_t			wqbuf_getIndex;
	/* fiwst of wead buffew  */
	int32_t			wqbuf_putIndex;
	/* wast of wead buffew   */
	uint8_t			wqbuffew[AWCMSW_MAX_QBUFFEW];
	/* data cowwection buffew fow wwite to 80331  */
	int32_t			wqbuf_getIndex;
	/* fiwst of wwite buffew */
	int32_t			wqbuf_putIndex;
	/* wast of wwite buffew  */
	uint8_t			devstate[AWCMSW_MAX_TAWGETID][AWCMSW_MAX_TAWGETWUN];
	/* id0 ..... id15, wun0...wun7 */
#define AWECA_WAID_GONE			0x55
#define AWECA_WAID_GOOD			0xaa
	uint32_t		num_wesets;
	uint32_t		num_abowts;
	uint32_t		signatuwe;
	uint32_t		fiwm_wequest_wen;
	uint32_t		fiwm_numbews_queue;
	uint32_t		fiwm_sdwam_size;
	uint32_t		fiwm_hd_channews;
	uint32_t		fiwm_cfg_vewsion;
	chaw			fiwm_modew[12];
	chaw			fiwm_vewsion[20];
	chaw			device_map[20];			/*21,84-99*/
	uint32_t		fiwm_PicStatus;
	stwuct wowk_stwuct 	awcmsw_do_message_isw_bh;
	stwuct timew_wist	etewnaw_timew;
	unsigned showt		fw_fwag;
#define	FW_NOWMAW			0x0000
#define	FW_BOG				0x0001
#define	FW_DEADWOCK			0x0010
	uint32_t		maxOutstanding;
	int			vectow_count;
	int			xow_mega;
	uint32_t		maxFweeCCB;
	stwuct timew_wist	wefwesh_timew;
	uint32_t		doneq_index;
	uint32_t		ccbsize;
	uint32_t		in_doowbeww;
	uint32_t		out_doowbeww;
	uint32_t		compwetionQ_entwy;
	pCompwetion_Q		pCompwetionQ;
	uint32_t		compweteQ_size;
	void			*xowViwt;
	dma_addw_t		xowPhys;
	unsigned int		init2cfg_size;
	unsigned int		xowViwtOffset;
};/* HW_DEVICE_EXTENSION */
/*
*******************************************************************************
**                   Command Contwow Bwock
**             this CCB wength must be 32 bytes boundawy
*******************************************************************************
*/
stwuct CommandContwowBwock{
	/*x32:sizeof stwuct_CCB=(64+60)byte, x64:sizeof stwuct_CCB=(64+60)byte*/
	stwuct wist_head		wist;		/*x32: 8byte, x64: 16byte*/
	stwuct scsi_cmnd		*pcmd;		/*8 bytes pointew of winux scsi command */
	stwuct AdaptewContwowBwock	*acb;		/*x32: 4byte, x64: 8byte*/
	unsigned wong			cdb_phyaddw;	/*x32: 4byte, x64: 8byte*/
	uint32_t			awc_cdb_size;	/*x32:4byte,x64:4byte*/
	uint16_t			ccb_fwags;	/*x32: 2byte, x64: 2byte*/
#define	CCB_FWAG_WEAD		0x0000
#define	CCB_FWAG_WWITE		0x0001
#define	CCB_FWAG_EWWOW		0x0002
#define	CCB_FWAG_FWUSHCACHE	0x0004
#define	CCB_FWAG_MASTEW_ABOWTED	0x0008
	uint16_t                        stawtdone;	/*x32:2byte,x32:2byte*/
#define	AWCMSW_CCB_DONE		0x0000
#define	AWCMSW_CCB_STAWT	0x55AA
#define	AWCMSW_CCB_ABOWTED	0xAA55
#define	AWCMSW_CCB_IWWEGAW	0xFFFF
	uint32_t			smid;
#if BITS_PEW_WONG == 64
	/*  ======================512+64 bytes========================  */
		uint32_t		wesewved[3];	/*12 byte*/
#ewse
	/*  ======================512+32 bytes========================  */
		uint32_t		wesewved[8];	/*32  byte*/
#endif
	/*  =======================================================   */
	stwuct AWCMSW_CDB		awcmsw_cdb;
};
/*
*******************************************************************************
**    AWECA SCSI sense data
*******************************************************************************
*/
stwuct SENSE_DATA
{
	uint8_t				EwwowCode:7;
#define SCSI_SENSE_CUWWENT_EWWOWS	0x70
#define SCSI_SENSE_DEFEWWED_EWWOWS	0x71
	uint8_t				Vawid:1;
	uint8_t				SegmentNumbew;
	uint8_t				SenseKey:4;
	uint8_t				Wesewved:1;
	uint8_t				IncowwectWength:1;
	uint8_t				EndOfMedia:1;
	uint8_t				FiweMawk:1;
	uint8_t				Infowmation[4];
	uint8_t				AdditionawSenseWength;
	uint8_t				CommandSpecificInfowmation[4];
	uint8_t				AdditionawSenseCode;
	uint8_t				AdditionawSenseCodeQuawifiew;
	uint8_t				FiewdWepwaceabweUnitCode;
	uint8_t				SenseKeySpecific[3];
};
/*
*******************************************************************************
**  Outbound Intewwupt Status Wegistew - OISW
*******************************************************************************
*/
#define	AWCMSW_MU_OUTBOUND_INTEWWUPT_STATUS_WEG	0x30
#define	AWCMSW_MU_OUTBOUND_PCI_INT		0x10
#define	AWCMSW_MU_OUTBOUND_POSTQUEUE_INT	0x08
#define	AWCMSW_MU_OUTBOUND_DOOWBEWW_INT		0x04
#define	AWCMSW_MU_OUTBOUND_MESSAGE1_INT		0x02
#define	AWCMSW_MU_OUTBOUND_MESSAGE0_INT		0x01
#define	AWCMSW_MU_OUTBOUND_HANDWE_INT                     \
                    (AWCMSW_MU_OUTBOUND_MESSAGE0_INT      \
                     |AWCMSW_MU_OUTBOUND_MESSAGE1_INT     \
                     |AWCMSW_MU_OUTBOUND_DOOWBEWW_INT     \
                     |AWCMSW_MU_OUTBOUND_POSTQUEUE_INT    \
                     |AWCMSW_MU_OUTBOUND_PCI_INT)
/*
*******************************************************************************
**  Outbound Intewwupt Mask Wegistew - OIMW
*******************************************************************************
*/
#define	AWCMSW_MU_OUTBOUND_INTEWWUPT_MASK_WEG		0x34
#define	AWCMSW_MU_OUTBOUND_PCI_INTMASKENABWE		0x10
#define	AWCMSW_MU_OUTBOUND_POSTQUEUE_INTMASKENABWE	0x08
#define	AWCMSW_MU_OUTBOUND_DOOWBEWW_INTMASKENABWE	0x04
#define	AWCMSW_MU_OUTBOUND_MESSAGE1_INTMASKENABWE	0x02
#define	AWCMSW_MU_OUTBOUND_MESSAGE0_INTMASKENABWE	0x01
#define	AWCMSW_MU_OUTBOUND_AWW_INTMASKENABWE		0x1F

extewn void awcmsw_wwite_ioctwdata2iop(stwuct AdaptewContwowBwock *);
extewn uint32_t awcmsw_Wead_iop_wqbuffew_data(stwuct AdaptewContwowBwock *,
	stwuct QBUFFEW __iomem *);
extewn void awcmsw_cweaw_iop2dwv_wqueue_buffew(stwuct AdaptewContwowBwock *);
extewn stwuct QBUFFEW __iomem *awcmsw_get_iop_wqbuffew(stwuct AdaptewContwowBwock *);
extewn const stwuct attwibute_gwoup *awcmsw_host_gwoups[];
extewn int awcmsw_awwoc_sysfs_attw(stwuct AdaptewContwowBwock *);
void awcmsw_fwee_sysfs_attw(stwuct AdaptewContwowBwock *acb);
