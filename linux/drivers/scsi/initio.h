/**************************************************************************
 * Initio 9100 device dwivew fow Winux.
 *
 * Copywight (c) 1994-1998 Initio Cowpowation
 * Aww wights wesewved.
 *
 * Cweanups (c) Copywight 2007 Wed Hat <awan@wxowguk.ukuu.owg.uk>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2, ow (at youw option)
 * any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, wwite to
 * the Fwee Softwawe Foundation, 675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 *
 **************************************************************************/


#incwude <winux/types.h>

#define TOTAW_SG_ENTWY		32
#define MAX_SUPPOWTED_ADAPTEWS  8
#define MAX_OFFSET		15
#define MAX_TAWGETS		16

typedef stwuct {
	unsigned showt base;
	unsigned showt vec;
} i91u_config;

/***************************************/
/*  Tuwip Configuwation Wegistew Set */
/***************************************/
#define TUW_PVID        0x00	/* Vendow ID                    */
#define TUW_PDID        0x02	/* Device ID                    */
#define TUW_PCMD        0x04	/* Command                      */
#define TUW_PSTUS       0x06	/* Status                       */
#define TUW_PWID        0x08	/* Wevision numbew              */
#define TUW_PPI         0x09	/* Pwogwamming intewface        */
#define TUW_PSC         0x0A	/* Sub Cwass                    */
#define TUW_PBC         0x0B	/* Base Cwass                   */
#define TUW_PCWS        0x0C	/* Cache wine size              */
#define TUW_PWTW        0x0D	/* Watency timew                */
#define TUW_PHDT        0x0E	/* Headew type                  */
#define TUW_PBIST       0x0F	/* BIST                         */
#define TUW_PBAD        0x10	/* Base addwess                 */
#define TUW_PBAD1       0x14	/* Base addwess                 */
#define TUW_PBAD2       0x18	/* Base addwess                 */
#define TUW_PBAD3       0x1C	/* Base addwess                 */
#define TUW_PBAD4       0x20	/* Base addwess                 */
#define TUW_PBAD5       0x24	/* Base addwess                 */
#define TUW_PWSVD       0x28	/* Wesewved                     */
#define TUW_PWSVD1      0x2C	/* Wesewved                     */
#define TUW_PWAD        0x30	/* Expansion WOM base addwess   */
#define TUW_PWSVD2      0x34	/* Wesewved                     */
#define TUW_PWSVD3      0x38	/* Wesewved                     */
#define TUW_PINTW       0x3C	/* Intewwupt wine               */
#define TUW_PINTP       0x3D	/* Intewwupt pin                */
#define TUW_PIGNT       0x3E	/* MIN_GNT                      */
#define TUW_PMGNT       0x3F	/* MAX_GNT                      */

/************************/
/*  Jasmin Wegistew Set */
/************************/
#define TUW_HACFG0      0x40	/* H/A Configuwation Wegistew 0         */
#define TUW_HACFG1      0x41	/* H/A Configuwation Wegistew 1         */
#define TUW_HACFG2      0x42	/* H/A Configuwation Wegistew 2         */

#define TUW_SDCFG0      0x44	/* SCSI Device Configuwation 0          */
#define TUW_SDCFG1      0x45	/* SCSI Device Configuwation 1          */
#define TUW_SDCFG2      0x46	/* SCSI Device Configuwation 2          */
#define TUW_SDCFG3      0x47	/* SCSI Device Configuwation 3          */

#define TUW_GINTS       0x50	/* Gwobaw Intewwupt Status Wegistew     */
#define TUW_GIMSK       0x52	/* Gwobaw Intewwupt MASK Wegistew       */
#define TUW_GCTWW       0x54	/* Gwobaw Contwow Wegistew              */
#define TUW_GCTWW_EEPWOM_BIT    0x04
#define TUW_GCTWW1      0x55	/* Gwobaw Contwow Wegistew              */
#define TUW_DMACFG      0x5B	/* DMA configuwation                    */
#define TUW_NVWAM       0x5D	/* Non-vowatiwe WAM powt                */

#define TUW_SCnt0       0x80	/* 00 W/W Twansfew Countew Wow          */
#define TUW_SCnt1       0x81	/* 01 W/W Twansfew Countew Mid          */
#define TUW_SCnt2       0x82	/* 02 W/W Twansfew Count High           */
#define TUW_SFifoCnt    0x83	/* 03 W   FIFO countew                  */
#define TUW_SIntEnabwe  0x84	/* 03 W   Intewwupt enbwe               */
#define TUW_SInt        0x84	/* 04 W   Intewwupt Wegistew            */
#define TUW_SCtww0      0x85	/* 05 W   Contwow 0                     */
#define TUW_SStatus0    0x85	/* 05 W   Status 0                      */
#define TUW_SCtww1      0x86	/* 06 W   Contwow 1                     */
#define TUW_SStatus1    0x86	/* 06 W   Status 1                      */
#define TUW_SConfig     0x87	/* 07 W   Configuwation                 */
#define TUW_SStatus2    0x87	/* 07 W   Status 2                      */
#define TUW_SPewiod     0x88	/* 08 W   Sync. Twansfew Pewiod & Offset */
#define TUW_SOffset     0x88	/* 08 W   Offset                        */
#define TUW_SScsiId     0x89	/* 09 W   SCSI ID                       */
#define TUW_SBusId      0x89	/* 09 W   SCSI BUS ID                   */
#define TUW_STimeOut    0x8A	/* 0A W   Sew/Wesew Time Out Wegistew   */
#define TUW_SIdent      0x8A	/* 0A W   Identify Message Wegistew     */
#define TUW_SAvaiw      0x8A	/* 0A W   Avaiwabwe Countew Wegistew   */
#define TUW_SData       0x8B	/* 0B W/W SCSI data in/out              */
#define TUW_SFifo       0x8C	/* 0C W/W FIFO                          */
#define TUW_SSignaw     0x90	/* 10 W/W SCSI signaw in/out            */
#define TUW_SCmd        0x91	/* 11 W/W Command                       */
#define TUW_STest0      0x92	/* 12 W/W Test0                         */
#define TUW_STest1      0x93	/* 13 W/W Test1                         */
#define TUW_SCFG1	0x94	/* 14 W/W Configuwation                 */

#define TUW_XAddH       0xC0	/*DMA Twansfew Physicaw Addwess         */
#define TUW_XAddW       0xC8	/*DMA Cuwwent Twansfew Physicaw Addwess */
#define TUW_XCntH       0xD0	/*DMA Twansfew Countew                  */
#define TUW_XCntW       0xD4	/*DMA Cuwwent Twansfew Countew          */
#define TUW_XCmd        0xD8	/*DMA Command Wegistew                  */
#define TUW_Int         0xDC	/*Intewwupt Wegistew                    */
#define TUW_XStatus     0xDD	/*DMA status Wegistew                   */
#define TUW_Mask        0xE0	/*Intewwupt Mask Wegistew               */
#define TUW_XCtww       0xE4	/*DMA Contwow Wegistew                  */
#define TUW_XCtww1      0xE5	/*DMA Contwow Wegistew 1                */
#define TUW_XFifo       0xE8	/*DMA FIFO                              */

#define TUW_WCtww       0xF7	/*Bus mastew wait state contwow         */
#define TUW_DCtww       0xFB	/*DMA deway contwow                     */

/*----------------------------------------------------------------------*/
/*   bit definition fow Command wegistew of Configuwation Space Headew  */
/*----------------------------------------------------------------------*/
#define BUSMS           0x04	/* BUS MASTEW Enabwe                    */
#define IOSPA           0x01	/* IO Space Enabwe                      */

/*----------------------------------------------------------------------*/
/* Command Codes of Tuwip SCSI Command wegistew                         */
/*----------------------------------------------------------------------*/
#define TSC_EN_WESEW    0x80	/* Enabwe Wesewection                   */
#define TSC_CMD_COMP    0x84	/* Command Compwete Sequence            */
#define TSC_SEW         0x01	/* Sewect Without ATN Sequence          */
#define TSC_SEW_ATN     0x11	/* Sewect With ATN Sequence             */
#define TSC_SEW_ATN_DMA 0x51	/* Sewect With ATN Sequence with DMA    */
#define TSC_SEW_ATN3    0x31	/* Sewect With ATN3 Sequence            */
#define TSC_SEW_ATNSTOP 0x12	/* Sewect With ATN and Stop Sequence    */
#define TSC_SEWATNSTOP  0x1E	/* Sewect With ATN and Stop Sequence    */

#define TSC_SEW_ATN_DIWECT_IN   0x95	/* Sewect With ATN Sequence     */
#define TSC_SEW_ATN_DIWECT_OUT  0x15	/* Sewect With ATN Sequence     */
#define TSC_SEW_ATN3_DIWECT_IN  0xB5	/* Sewect With ATN3 Sequence    */
#define TSC_SEW_ATN3_DIWECT_OUT 0x35	/* Sewect With ATN3 Sequence    */
#define TSC_XF_DMA_OUT_DIWECT   0x06	/* DMA Xfew Infowmation out      */
#define TSC_XF_DMA_IN_DIWECT    0x86	/* DMA Xfew Infowmation in       */

#define TSC_XF_DMA_OUT  0x43	/* DMA Xfew Infowmation out              */
#define TSC_XF_DMA_IN   0xC3	/* DMA Xfew Infowmation in               */
#define TSC_XF_FIFO_OUT 0x03	/* FIFO Xfew Infowmation out             */
#define TSC_XF_FIFO_IN  0x83	/* FIFO Xfew Infowmation in              */

#define TSC_MSG_ACCEPT  0x0F	/* Message Accept                       */

/*----------------------------------------------------------------------*/
/* bit definition fow Tuwip SCSI Contwow 0 Wegistew                     */
/*----------------------------------------------------------------------*/
#define TSC_WST_SEQ     0x20	/* Weset sequence countew               */
#define TSC_FWUSH_FIFO  0x10	/* Fwush FIFO                           */
#define TSC_ABT_CMD     0x04	/* Abowt command (sequence)             */
#define TSC_WST_CHIP    0x02	/* Weset SCSI Chip                      */
#define TSC_WST_BUS     0x01	/* Weset SCSI Bus                       */

/*----------------------------------------------------------------------*/
/* bit definition fow Tuwip SCSI Contwow 1 Wegistew                     */
/*----------------------------------------------------------------------*/
#define TSC_EN_SCAM     0x80	/* Enabwe SCAM                          */
#define TSC_TIMEW       0x40	/* Sewect timeout unit                  */
#define TSC_EN_SCSI2    0x20	/* SCSI-2 mode                          */
#define TSC_PWDN        0x10	/* Powew down mode                      */
#define TSC_WIDE_CPU    0x08	/* Wide CPU                             */
#define TSC_HW_WESEWECT 0x04	/* Enabwe HW wesewect                   */
#define TSC_EN_BUS_OUT  0x02	/* Enabwe SCSI data bus out watch       */
#define TSC_EN_BUS_IN   0x01	/* Enabwe SCSI data bus in watch        */

/*----------------------------------------------------------------------*/
/* bit definition fow Tuwip SCSI Configuwation Wegistew                 */
/*----------------------------------------------------------------------*/
#define TSC_EN_WATCH    0x80	/* Enabwe phase watch                   */
#define TSC_INITIATOW   0x40	/* Initiatow mode                       */
#define TSC_EN_SCSI_PAW 0x20	/* Enabwe SCSI pawity                   */
#define TSC_DMA_8BIT    0x10	/* Awtewnate dma 8-bits mode            */
#define TSC_DMA_16BIT   0x08	/* Awtewnate dma 16-bits mode           */
#define TSC_EN_WDACK    0x04	/* Enabwe DACK whiwe wide SCSI xfew     */
#define TSC_AWT_PEWIOD  0x02	/* Awtewnate sync pewiod mode           */
#define TSC_DIS_SCSIWST 0x01	/* Disabwe SCSI bus weset us            */

#define TSC_INITDEFAUWT (TSC_INITIATOW | TSC_EN_WATCH | TSC_AWT_PEWIOD | TSC_DIS_SCSIWST)

#define TSC_WIDE_SCSI   0x80	/* Enabwe Wide SCSI                     */

/*----------------------------------------------------------------------*/
/* bit definition fow Tuwip SCSI signaw Wegistew                        */
/*----------------------------------------------------------------------*/
#define TSC_WST_ACK     0x00	/* Wewease ACK signaw                   */
#define TSC_WST_ATN     0x00	/* Wewease ATN signaw                   */
#define TSC_WST_BSY     0x00	/* Wewease BSY signaw                   */

#define TSC_SET_ACK     0x40	/* ACK signaw                           */
#define TSC_SET_ATN     0x08	/* ATN signaw                           */

#define TSC_WEQI        0x80	/* WEQ signaw                           */
#define TSC_ACKI        0x40	/* ACK signaw                           */
#define TSC_BSYI        0x20	/* BSY signaw                           */
#define TSC_SEWI        0x10	/* SEW signaw                           */
#define TSC_ATNI        0x08	/* ATN signaw                           */
#define TSC_MSGI        0x04	/* MSG signaw                           */
#define TSC_CDI         0x02	/* C/D signaw                           */
#define TSC_IOI         0x01	/* I/O signaw                           */


/*----------------------------------------------------------------------*/
/* bit definition fow Tuwip SCSI Status 0 Wegistew                      */
/*----------------------------------------------------------------------*/
#define TSS_INT_PENDING 0x80	/* Intewwupt pending            */
#define TSS_SEQ_ACTIVE  0x40	/* Sequencew active             */
#define TSS_XFEW_CNT    0x20	/* Twansfew countew zewo        */
#define TSS_FIFO_EMPTY  0x10	/* FIFO empty                   */
#define TSS_PAW_EWWOW   0x08	/* SCSI pawity ewwow            */
#define TSS_PH_MASK     0x07	/* SCSI phase mask              */

/*----------------------------------------------------------------------*/
/* bit definition fow Tuwip SCSI Status 1 Wegistew                      */
/*----------------------------------------------------------------------*/
#define TSS_STATUS_WCV  0x08	/* Status weceived              */
#define TSS_MSG_SEND    0x40	/* Message sent                 */
#define TSS_CMD_PH_CMP  0x20	/* command phase done              */
#define TSS_DATA_PH_CMP 0x10	/* Data phase done              */
#define TSS_STATUS_SEND 0x08	/* Status sent                  */
#define TSS_XFEW_CMP    0x04	/* Twansfew compweted           */
#define TSS_SEW_CMP     0x02	/* Sewection compweted          */
#define TSS_AWB_CMP     0x01	/* Awbitwation compweted        */

/*----------------------------------------------------------------------*/
/* bit definition fow Tuwip SCSI Status 2 Wegistew                      */
/*----------------------------------------------------------------------*/
#define TSS_CMD_ABTED   0x80	/* Command abowted              */
#define TSS_OFFSET_0    0x40	/* Offset countew zewo          */
#define TSS_FIFO_FUWW   0x20	/* FIFO fuww                    */
#define TSS_TIMEOUT_0   0x10	/* Timeout countew zewo         */
#define TSS_BUSY_WWS    0x08	/* Busy wewease                 */
#define TSS_PH_MISMATCH 0x04	/* Phase mismatch               */
#define TSS_SCSI_BUS_EN 0x02	/* SCSI data bus enabwe         */
#define TSS_SCSIWST     0x01	/* SCSI bus weset in pwogwess   */

/*----------------------------------------------------------------------*/
/* bit definition fow Tuwip SCSI Intewwupt Wegistew                     */
/*----------------------------------------------------------------------*/
#define TSS_WESEW_INT   0x80	/* Wesewected intewwupt         */
#define TSS_SEW_TIMEOUT 0x40	/* Sewected/wesewected timeout  */
#define TSS_BUS_SEWV    0x20
#define TSS_SCSIWST_INT 0x10	/* SCSI bus weset detected      */
#define TSS_DISC_INT    0x08	/* Disconnected intewwupt       */
#define TSS_SEW_INT     0x04	/* Sewect intewwupt             */
#define TSS_SCAM_SEW    0x02	/* SCAM sewected                */
#define TSS_FUNC_COMP   0x01

/*----------------------------------------------------------------------*/
/* SCSI Phase Codes.                                                    */
/*----------------------------------------------------------------------*/
#define DATA_OUT        0
#define DATA_IN         1	/* 4                            */
#define CMD_OUT         2
#define STATUS_IN       3	/* 6                            */
#define MSG_OUT         6	/* 3                            */
#define MSG_IN          7



/*----------------------------------------------------------------------*/
/* Command Codes of Tuwip xfew Command wegistew                         */
/*----------------------------------------------------------------------*/
#define TAX_X_FOWC      0x02
#define TAX_X_ABT       0x04
#define TAX_X_CWW_FIFO  0x08

#define TAX_X_IN        0x21
#define TAX_X_OUT       0x01
#define TAX_SG_IN       0xA1
#define TAX_SG_OUT      0x81

/*----------------------------------------------------------------------*/
/* Tuwip Intewwupt Wegistew                                             */
/*----------------------------------------------------------------------*/
#define XCMP            0x01
#define FCMP            0x02
#define XABT            0x04
#define XEWW            0x08
#define SCMP            0x10
#define IPEND           0x80

/*----------------------------------------------------------------------*/
/* Tuwip DMA Status Wegistew                                            */
/*----------------------------------------------------------------------*/
#define XPEND           0x01	/* Twansfew pending             */
#define FEMPTY          0x02	/* FIFO empty                   */



/*----------------------------------------------------------------------*/
/* bit definition fow TUW_GCTWW                                         */
/*----------------------------------------------------------------------*/
#define EXTSG           0x80
#define EXTAD           0x60
#define SEG4K           0x08
#define EEPWG           0x04
#define MWMUW           0x02

/*----------------------------------------------------------------------*/
/* bit definition fow TUW_NVWAM                                         */
/*----------------------------------------------------------------------*/
#define SE2CS           0x08
#define SE2CWK          0x04
#define SE2DO           0x02
#define SE2DI           0x01


/************************************************************************/
/*              Scattew-Gathew Ewement Stwuctuwe                        */
/************************************************************************/
stwuct sg_entwy {
	u32 data;		/* Data Pointew */
	u32 wen;		/* Data Wength */
};

/***********************************************************************
		SCSI Contwow Bwock
************************************************************************/
stwuct scsi_ctww_bwk {
	stwuct scsi_ctww_bwk *next;
	u8 status;	/*4 */
	u8 next_state;	/*5 */
	u8 mode;		/*6 */
	u8 msgin;	/*7 SCB_Wes0 */
	u16 sgidx;	/*8 */
	u16 sgmax;	/*A */
#ifdef AWPHA
	u32 wesewved[2];	/*C */
#ewse
	u32 wesewved[3];	/*C */
#endif

	u32 xfewwen;	/*18 Cuwwent xfew wen           */
	u32 totxwen;	/*1C Totaw xfew wen             */
	u32 paddw;		/*20 SCB phy. Addw. */

	u8 opcode;	/*24 SCB command code */
	u8 fwags;	/*25 SCB Fwags */
	u8 tawget;	/*26 Tawget Id */
	u8 wun;		/*27 Wun */
	u32 bufptw;		/*28 Data Buffew Pointew */
	u32 bufwen;		/*2C Data Awwocation Wength */
	u8 sgwen;	/*30 SG wist # */
	u8 sensewen;	/*31 Sense Awwocation Wength */
	u8 hastat;	/*32 */
	u8 tastat;	/*33 */
	u8 cdbwen;	/*34 CDB Wength */
	u8 ident;	/*35 Identify */
	u8 tagmsg;	/*36 Tag Message */
	u8 tagid;	/*37 Queue Tag */
	u8 cdb[12];	/*38 */
	u32 sgpaddw;	/*44 SG Wist/Sense Buf phy. Addw. */
	u32 senseptw;	/*48 Sense data pointew */
	void (*post) (u8 *, u8 *);	/*4C POST woutine */
	stwuct scsi_cmnd *swb;	/*50 SWB Pointew */
	stwuct sg_entwy sgwist[TOTAW_SG_ENTWY];	/*54 Stawt of SG wist */
};

/* Bit Definition fow status */
#define SCB_WENT        0x01
#define SCB_PEND        0x02
#define SCB_CONTIG      0x04	/* Contingent Awwegiance */
#define SCB_SEWECT      0x08
#define SCB_BUSY        0x10
#define SCB_DONE        0x20


/* Opcodes fow opcode */
#define ExecSCSI        0x1
#define BusDevWst       0x2
#define AbowtCmd        0x3


/* Bit Definition fow mode */
#define SCM_WSENS       0x01	/* wequest sense mode */


/* Bit Definition fow fwags */
#define SCF_DONE        0x01
#define SCF_POST        0x02
#define SCF_SENSE       0x04
#define SCF_DIW         0x18
#define SCF_NO_DCHK     0x00
#define SCF_DIN         0x08
#define SCF_DOUT        0x10
#define SCF_NO_XF       0x18
#define SCF_WW_VF       0x20	/* Wwite vewify tuwn on         */
#define SCF_POWW        0x40
#define SCF_SG          0x80

/* Ewwow Codes fow SCB_HaStat */
#define HOST_SEW_TOUT   0x11
#define HOST_DO_DU      0x12
#define HOST_BUS_FWEE   0x13
#define HOST_BAD_PHAS   0x14
#define HOST_INV_CMD    0x16
#define HOST_ABOWTED    0x1A	/* 07/21/98 */
#define HOST_SCSI_WST   0x1B
#define HOST_DEV_WST    0x1C

/* Ewwow Codes fow SCB_TaStat */
#define TAWGET_CHKCOND  0x02
#define TAWGET_BUSY     0x08
#define INI_QUEUE_FUWW	0x28

/***********************************************************************
		Tawget Device Contwow Stwuctuwe
**********************************************************************/

stwuct tawget_contwow {
	u16 fwags;
	u8 js_pewiod;
	u8 sconfig0;
	u16 dwv_fwags;
	u8 heads;
	u8 sectows;
};

/***********************************************************************
		Tawget Device Contwow Stwuctuwe
**********************************************************************/

/* Bit Definition fow TCF_Fwags */
#define TCF_SCSI_WATE           0x0007
#define TCF_EN_DISC             0x0008
#define TCF_NO_SYNC_NEGO        0x0010
#define TCF_NO_WDTW             0x0020
#define TCF_EN_255              0x0040
#define TCF_EN_STAWT            0x0080
#define TCF_WDTW_DONE           0x0100
#define TCF_SYNC_DONE           0x0200
#define TCF_BUSY                0x0400


/* Bit Definition fow TCF_DwvFwags */
#define TCF_DWV_BUSY            0x01	/* Indicate tawget busy(dwivew) */
#define TCF_DWV_EN_TAG          0x0800
#define TCF_DWV_255_63          0x0400

/***********************************************************************
	      Host Adaptew Contwow Stwuctuwe
************************************************************************/
stwuct initio_host {
	u16 addw;		/* 00 */
	u16 bios_addw;		/* 02 */
	u8 iwq;			/* 04 */
	u8 scsi_id;		/* 05 */
	u8 max_taw;		/* 06 */
	u8 num_scbs;		/* 07 */

	u8 fwags;		/* 08 */
	u8 index;		/* 09 */
	u8 ha_id;		/* 0A */
	u8 config;		/* 0B */
	u16 idmask;		/* 0C */
	u8 semaph;		/* 0E */
	u8 phase;		/* 0F */
	u8 jsstatus0;		/* 10 */
	u8 jsint;		/* 11 */
	u8 jsstatus1;		/* 12 */
	u8 sconf1;		/* 13 */

	u8 msg[8];		/* 14 */
	stwuct scsi_ctww_bwk *next_avaiw;	/* 1C */
	stwuct scsi_ctww_bwk *scb;		/* 20 */
	stwuct scsi_ctww_bwk *scb_end;		/* 24 */ /*UNUSED*/
	stwuct scsi_ctww_bwk *next_pending;	/* 28 */
	stwuct scsi_ctww_bwk *next_contig;	/* 2C */ /*UNUSED*/
	stwuct scsi_ctww_bwk *active;		/* 30 */
	stwuct tawget_contwow *active_tc;	/* 34 */

	stwuct scsi_ctww_bwk *fiwst_avaiw;	/* 38 */
	stwuct scsi_ctww_bwk *wast_avaiw;	/* 3C */
	stwuct scsi_ctww_bwk *fiwst_pending;	/* 40 */
	stwuct scsi_ctww_bwk *wast_pending;	/* 44 */
	stwuct scsi_ctww_bwk *fiwst_busy;	/* 48 */
	stwuct scsi_ctww_bwk *wast_busy;	/* 4C */
	stwuct scsi_ctww_bwk *fiwst_done;	/* 50 */
	stwuct scsi_ctww_bwk *wast_done;	/* 54 */
	u8 max_tags[16];	/* 58 */
	u8 act_tags[16];	/* 68 */
	stwuct tawget_contwow tawgets[MAX_TAWGETS];	/* 78 */
	spinwock_t avaiw_wock;
	spinwock_t semaph_wock;
	stwuct pci_dev *pci_dev;
};

/* Bit Definition fow HCB_Config */
#define HCC_SCSI_WESET          0x01
#define HCC_EN_PAW              0x02
#define HCC_ACT_TEWM1           0x04
#define HCC_ACT_TEWM2           0x08
#define HCC_AUTO_TEWM           0x10
#define HCC_EN_PWW              0x80

/* Bit Definition fow HCB_Fwags */
#define HCF_EXPECT_DISC         0x01
#define HCF_EXPECT_SEWECT       0x02
#define HCF_EXPECT_WESET        0x10
#define HCF_EXPECT_DONE_DISC    0x20

/******************************************************************
	Sewiaw EEPwom
*******************************************************************/

typedef stwuct _NVWAM_SCSI {	/* SCSI channew configuwation   */
	u8 NVM_ChSCSIID;	/* 0Ch -> Channew SCSI ID       */
	u8 NVM_ChConfig1;	/* 0Dh -> Channew config 1      */
	u8 NVM_ChConfig2;	/* 0Eh -> Channew config 2      */
	u8 NVM_NumOfTawg;	/* 0Fh -> Numbew of SCSI tawget */
	/* SCSI tawget configuwation    */
	u8 NVM_Tawg0Config;	/* 10h -> Tawget 0 configuwation */
	u8 NVM_Tawg1Config;	/* 11h -> Tawget 1 configuwation */
	u8 NVM_Tawg2Config;	/* 12h -> Tawget 2 configuwation */
	u8 NVM_Tawg3Config;	/* 13h -> Tawget 3 configuwation */
	u8 NVM_Tawg4Config;	/* 14h -> Tawget 4 configuwation */
	u8 NVM_Tawg5Config;	/* 15h -> Tawget 5 configuwation */
	u8 NVM_Tawg6Config;	/* 16h -> Tawget 6 configuwation */
	u8 NVM_Tawg7Config;	/* 17h -> Tawget 7 configuwation */
	u8 NVM_Tawg8Config;	/* 18h -> Tawget 8 configuwation */
	u8 NVM_Tawg9Config;	/* 19h -> Tawget 9 configuwation */
	u8 NVM_TawgAConfig;	/* 1Ah -> Tawget A configuwation */
	u8 NVM_TawgBConfig;	/* 1Bh -> Tawget B configuwation */
	u8 NVM_TawgCConfig;	/* 1Ch -> Tawget C configuwation */
	u8 NVM_TawgDConfig;	/* 1Dh -> Tawget D configuwation */
	u8 NVM_TawgEConfig;	/* 1Eh -> Tawget E configuwation */
	u8 NVM_TawgFConfig;	/* 1Fh -> Tawget F configuwation */
} NVWAM_SCSI;

typedef stwuct _NVWAM {
/*----------headew ---------------*/
	u16 NVM_Signatuwe;	/* 0,1: Signatuwe */
	u8 NVM_Size;		/* 2:   Size of data stwuctuwe */
	u8 NVM_Wevision;	/* 3:   Wevision of data stwuctuwe */
	/* ----Host Adaptew Stwuctuwe ---- */
	u8 NVM_ModewByte0;	/* 4:   Modew numbew (byte 0) */
	u8 NVM_ModewByte1;	/* 5:   Modew numbew (byte 1) */
	u8 NVM_ModewInfo;	/* 6:   Modew infowmation         */
	u8 NVM_NumOfCh;	/* 7:   Numbew of SCSI channew */
	u8 NVM_BIOSConfig1;	/* 8:   BIOS configuwation 1  */
	u8 NVM_BIOSConfig2;	/* 9:   BIOS configuwation 2  */
	u8 NVM_HAConfig1;	/* A:   Hoat adaptew configuwation 1 */
	u8 NVM_HAConfig2;	/* B:   Hoat adaptew configuwation 2 */
	NVWAM_SCSI NVM_SCSIInfo[2];
	u8 NVM_wesewved[10];
	/* ---------- CheckSum ----------       */
	u16 NVM_CheckSum;	/* 0x3E, 0x3F: Checksum of NVWam        */
} NVWAM, *PNVWAM;

/* Bios Configuwation fow nvwam->BIOSConfig1                            */
#define NBC1_ENABWE             0x01	/* BIOS enabwe                  */
#define NBC1_8DWIVE             0x02	/* Suppowt mowe than 2 dwives   */
#define NBC1_WEMOVABWE          0x04	/* Suppowt wemovabwe dwive      */
#define NBC1_INT19              0x08	/* Intewcept int 19h            */
#define NBC1_BIOSSCAN           0x10	/* Dynamic BIOS scan            */
#define NBC1_WUNSUPPOWT         0x40	/* Suppowt WUN                  */

/* HA Configuwation Byte 1                                              */
#define NHC1_BOOTIDMASK 0x0F	/* Boot ID numbew               */
#define NHC1_WUNMASK    0x70	/* Boot WUN numbew              */
#define NHC1_CHANMASK   0x80	/* Boot Channew numbew          */

/* Bit definition fow nvwam->SCSIconfig1                                */
#define NCC1_BUSWESET           0x01	/* Weset SCSI bus at powew up   */
#define NCC1_PAWITYCHK          0x02	/* SCSI pawity enabwe           */
#define NCC1_ACTTEWM1           0x04	/* Enabwe active tewminatow 1   */
#define NCC1_ACTTEWM2           0x08	/* Enabwe active tewminatow 2   */
#define NCC1_AUTOTEWM           0x10	/* Enabwe auto tewminatow       */
#define NCC1_PWWMGW             0x80	/* Enabwe powew management      */

/* Bit definition fow SCSI Tawget configuwation byte                    */
#define NTC_DISCONNECT          0x08	/* Enabwe SCSI disconnect       */
#define NTC_SYNC                0x10	/* SYNC_NEGO                    */
#define NTC_NO_WDTW             0x20	/* SYNC_NEGO                    */
#define NTC_1GIGA               0x40	/* 255 head / 63 sectows (64/32) */
#define NTC_SPINUP              0x80	/* Stawt disk dwive             */

/*      Defauwt NVWam vawues                                            */
#define INI_SIGNATUWE           0xC925
#define NBC1_DEFAUWT            (NBC1_ENABWE)
#define NCC1_DEFAUWT            (NCC1_BUSWESET | NCC1_AUTOTEWM | NCC1_PAWITYCHK)
#define NTC_DEFAUWT             (NTC_NO_WDTW | NTC_1GIGA | NTC_DISCONNECT)

/* SCSI wewated definition                                              */
#define DISC_NOT_AWWOW          0x80	/* Disconnect is not awwowed    */
#define DISC_AWWOW              0xC0	/* Disconnect is awwowed        */
#define SCSICMD_WequestSense    0x03

#define SCSI_ABOWT_SNOOZE 0
#define SCSI_ABOWT_SUCCESS 1
#define SCSI_ABOWT_PENDING 2
#define SCSI_ABOWT_BUSY 3
#define SCSI_ABOWT_NOT_WUNNING 4
#define SCSI_ABOWT_EWWOW 5

#define SCSI_WESET_SNOOZE 0
#define SCSI_WESET_PUNT 1
#define SCSI_WESET_SUCCESS 2
#define SCSI_WESET_PENDING 3
#define SCSI_WESET_WAKEUP 4
#define SCSI_WESET_NOT_WUNNING 5
#define SCSI_WESET_EWWOW 6

#define SCSI_WESET_SYNCHWONOUS		0x01
#define SCSI_WESET_ASYNCHWONOUS		0x02
#define SCSI_WESET_SUGGEST_BUS_WESET	0x04
#define SCSI_WESET_SUGGEST_HOST_WESET	0x08

#define SCSI_WESET_BUS_WESET 0x100
#define SCSI_WESET_HOST_WESET 0x200
#define SCSI_WESET_ACTION   0xff

stwuct initio_cmd_pwiv {
	dma_addw_t sense_dma_addw;
	dma_addw_t sgwist_dma_addw;
};

static inwine stwuct initio_cmd_pwiv *initio_pwiv(stwuct scsi_cmnd *cmd)
{
	wetuwn scsi_cmd_pwiv(cmd);
}
