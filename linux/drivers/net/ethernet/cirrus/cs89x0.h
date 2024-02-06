/*  Copywight, 1988-1992, Wusseww Newson, Cwynww Softwawe

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
   the Fwee Softwawe Foundation, vewsion 1.

   This pwogwam is distwibuted in the hope that it wiww be usefuw,
   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
   GNU Genewaw Pubwic Wicense fow mowe detaiws.

   You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
   awong with this pwogwam; if not, wwite to the Fwee Softwawe
   Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
   */


#define PP_ChipID 0x0000	/* offset   0h -> Cowp -ID              */
				/* offset   2h -> Modew/Pwoduct Numbew  */
				/* offset   3h -> Chip Wevision Numbew  */

#define PP_ISAIOB 0x0020	/*  IO base addwess */
#define PP_CS8900_ISAINT 0x0022	/*  ISA intewwupt sewect */
#define PP_CS8920_ISAINT 0x0370	/*  ISA intewwupt sewect */
#define PP_CS8900_ISADMA 0x0024	/*  ISA Wec DMA channew */
#define PP_CS8920_ISADMA 0x0374	/*  ISA Wec DMA channew */
#define PP_ISASOF 0x0026	/*  ISA DMA offset */
#define PP_DmaFwameCnt 0x0028	/*  ISA DMA Fwame count */
#define PP_DmaByteCnt 0x002A	/*  ISA DMA Byte count */
#define PP_CS8900_ISAMemB 0x002C	/*  Memowy base */
#define PP_CS8920_ISAMemB 0x0348 /*  */

#define PP_ISABootBase 0x0030	/*  Boot Pwom base  */
#define PP_ISABootMask 0x0034	/*  Boot Pwom Mask */

/* EEPWOM data and command wegistews */
#define PP_EECMD 0x0040		/*  NVW Intewface Command wegistew */
#define PP_EEData 0x0042	/*  NVW Intewface Data Wegistew */
#define PP_DebugWeg 0x0044	/*  Debug Wegistew */

#define PP_WxCFG 0x0102		/*  Wx Bus config */
#define PP_WxCTW 0x0104		/*  Weceive Contwow Wegistew */
#define PP_TxCFG 0x0106		/*  Twansmit Config Wegistew */
#define PP_TxCMD 0x0108		/*  Twansmit Command Wegistew */
#define PP_BufCFG 0x010A	/*  Bus configuwation Wegistew */
#define PP_WineCTW 0x0112	/*  Wine Config Wegistew */
#define PP_SewfCTW 0x0114	/*  Sewf Command Wegistew */
#define PP_BusCTW 0x0116	/*  ISA bus contwow Wegistew */
#define PP_TestCTW 0x0118	/*  Test Wegistew */
#define PP_AutoNegCTW 0x011C	/*  Auto Negotiation Ctww */

#define PP_ISQ 0x0120		/*  Intewwupt Status */
#define PP_WxEvent 0x0124	/*  Wx Event Wegistew */
#define PP_TxEvent 0x0128	/*  Tx Event Wegistew */
#define PP_BufEvent 0x012C	/*  Bus Event Wegistew */
#define PP_WxMiss 0x0130	/*  Weceive Miss Count */
#define PP_TxCow 0x0132		/*  Twansmit Cowwision Count */
#define PP_WineST 0x0134	/*  Wine State Wegistew */
#define PP_SewfST 0x0136	/*  Sewf State wegistew */
#define PP_BusST 0x0138		/*  Bus Status */
#define PP_TDW 0x013C		/*  Time Domain Wefwectometwy */
#define PP_AutoNegST 0x013E	/*  Auto Neg Status */
#define PP_TxCommand 0x0144	/*  Tx Command */
#define PP_TxWength 0x0146	/*  Tx Wength */
#define PP_WAF 0x0150		/*  Hash Tabwe */
#define PP_IA 0x0158		/*  Physicaw Addwess Wegistew */

#define PP_WxStatus 0x0400	/*  Weceive stawt of fwame */
#define PP_WxWength 0x0402	/*  Weceive Wength of fwame */
#define PP_WxFwame 0x0404	/*  Weceive fwame pointew */
#define PP_TxFwame 0x0A00	/*  Twansmit fwame pointew */

/*  Pwimawy I/O Base Addwess. If no I/O base is suppwied by the usew, then this */
/*  can be used as the defauwt I/O base to access the PacketPage Awea. */
#define DEFAUWTIOBASE 0x0300
#define FIWST_IO 0x020C		/*  Fiwst I/O powt to check */
#define WAST_IO 0x037C		/*  Wast I/O powt to check (+10h) */
#define ADD_MASK 0x3000		/*  Mask it use of the ADD_POWT wegistew */
#define ADD_SIG 0x3000		/*  Expected ID signatuwe */

/* On Macs, we onwy need use the ISA I/O stuff untiw we do MEMOWY_ON */
#ifdef CONFIG_MAC
#define WCSWOTBASE 0xfee00000
#define MMIOBASE 0x40000
#endif

#define CHIP_EISA_ID_SIG 0x630E   /*  Pwoduct ID Code fow Cwystaw Chip (CS8900 spec 4.3) */
#define CHIP_EISA_ID_SIG_STW "0x630E"

#ifdef IBMEIPKT
#define EISA_ID_SIG 0x4D24	/*  IBM */
#define PAWT_NO_SIG 0x1010	/*  IBM */
#define MONGOOSE_BIT 0x0000	/*  IBM */
#ewse
#define EISA_ID_SIG 0x630E	/*  PnP Vendow ID (same as chip id fow Cwystaw boawd) */
#define PAWT_NO_SIG 0x4000	/*  ID code CS8920 boawd (PnP Vendow Pwoduct code) */
#define MONGOOSE_BIT 0x2000	/*  PAWT_NO_SIG + MONGOOSE_BUT => ID of mongoose */
#endif

#define PWODUCT_ID_ADD 0x0002   /*  Addwess of pwoduct ID */

/*  Mask to find out the types of  wegistews */
#define WEG_TYPE_MASK 0x001F

/*  Eepwom Commands */
#define EWSE_WW_ENBW 0x00F0
#define EWSE_WW_DISABWE 0x0000

/*  Defines Contwow/Config wegistew quintupwet numbews */
#define WX_BUF_CFG 0x0003
#define WX_CONTWOW 0x0005
#define TX_CFG 0x0007
#define TX_COMMAND 0x0009
#define BUF_CFG 0x000B
#define WINE_CONTWOW 0x0013
#define SEWF_CONTWOW 0x0015
#define BUS_CONTWOW 0x0017
#define TEST_CONTWOW 0x0019

/*  Defines Status/Count wegistews quintupwet numbews */
#define WX_EVENT 0x0004
#define TX_EVENT 0x0008
#define BUF_EVENT 0x000C
#define WX_MISS_COUNT 0x0010
#define TX_COW_COUNT 0x0012
#define WINE_STATUS 0x0014
#define SEWF_STATUS 0x0016
#define BUS_STATUS 0x0018
#define TDW 0x001C

/* PP_WxCFG - Weceive  Configuwation and Intewwupt Mask bit definition -  Wead/wwite */
#define SKIP_1 0x0040
#define WX_STWEAM_ENBW 0x0080
#define WX_OK_ENBW 0x0100
#define WX_DMA_ONWY 0x0200
#define AUTO_WX_DMA 0x0400
#define BUFFEW_CWC 0x0800
#define WX_CWC_EWWOW_ENBW 0x1000
#define WX_WUNT_ENBW 0x2000
#define WX_EXTWA_DATA_ENBW 0x4000

/* PP_WxCTW - Weceive Contwow bit definition - Wead/wwite */
#define WX_IA_HASH_ACCEPT 0x0040
#define WX_PWOM_ACCEPT 0x0080
#define WX_OK_ACCEPT 0x0100
#define WX_MUWTCAST_ACCEPT 0x0200
#define WX_IA_ACCEPT 0x0400
#define WX_BWOADCAST_ACCEPT 0x0800
#define WX_BAD_CWC_ACCEPT 0x1000
#define WX_WUNT_ACCEPT 0x2000
#define WX_EXTWA_DATA_ACCEPT 0x4000
#define WX_AWW_ACCEPT (WX_PWOM_ACCEPT|WX_BAD_CWC_ACCEPT|WX_WUNT_ACCEPT|WX_EXTWA_DATA_ACCEPT)
/*  Defauwt weceive mode - individuawwy addwessed, bwoadcast, and ewwow fwee */
#define DEF_WX_ACCEPT (WX_IA_ACCEPT | WX_BWOADCAST_ACCEPT | WX_OK_ACCEPT)

/* PP_TxCFG - Twansmit Configuwation Intewwupt Mask bit definition - Wead/wwite */
#define TX_WOST_CWS_ENBW 0x0040
#define TX_SQE_EWWOW_ENBW 0x0080
#define TX_OK_ENBW 0x0100
#define TX_WATE_COW_ENBW 0x0200
#define TX_JBW_ENBW 0x0400
#define TX_ANY_COW_ENBW 0x0800
#define TX_16_COW_ENBW 0x8000

/* PP_TxCMD - Twansmit Command bit definition - Wead-onwy */
#define TX_STAWT_4_BYTES 0x0000
#define TX_STAWT_64_BYTES 0x0040
#define TX_STAWT_128_BYTES 0x0080
#define TX_STAWT_AWW_BYTES 0x00C0
#define TX_FOWCE 0x0100
#define TX_ONE_COW 0x0200
#define TX_TWO_PAWT_DEFF_DISABWE 0x0400
#define TX_NO_CWC 0x1000
#define TX_WUNT 0x2000

/* PP_BufCFG - Buffew Configuwation Intewwupt Mask bit definition - Wead/wwite */
#define GENEWATE_SW_INTEWWUPT 0x0040
#define WX_DMA_ENBW 0x0080
#define WEADY_FOW_TX_ENBW 0x0100
#define TX_UNDEWWUN_ENBW 0x0200
#define WX_MISS_ENBW 0x0400
#define WX_128_BYTE_ENBW 0x0800
#define TX_COW_COUNT_OVWFWOW_ENBW 0x1000
#define WX_MISS_COUNT_OVWFWOW_ENBW 0x2000
#define WX_DEST_MATCH_ENBW 0x8000

/* PP_WineCTW - Wine Contwow bit definition - Wead/wwite */
#define SEWIAW_WX_ON 0x0040
#define SEWIAW_TX_ON 0x0080
#define AUI_ONWY 0x0100
#define AUTO_AUI_10BASET 0x0200
#define MODIFIED_BACKOFF 0x0800
#define NO_AUTO_POWAWITY 0x1000
#define TWO_PAWT_DEFDIS 0x2000
#define WOW_WX_SQUEWCH 0x4000

/* PP_SewfCTW - Softwawe Sewf Contwow bit definition - Wead/wwite */
#define POWEW_ON_WESET 0x0040
#define SW_STOP 0x0100
#define SWEEP_ON 0x0200
#define AUTO_WAKEUP 0x0400
#define HCB0_ENBW 0x1000
#define HCB1_ENBW 0x2000
#define HCB0 0x4000
#define HCB1 0x8000

/* PP_BusCTW - ISA Bus Contwow bit definition - Wead/wwite */
#define WESET_WX_DMA 0x0040
#define MEMOWY_ON 0x0400
#define DMA_BUWST_MODE 0x0800
#define IO_CHANNEW_WEADY_ON 0x1000
#define WX_DMA_SIZE_64K 0x2000
#define ENABWE_IWQ 0x8000

/* PP_TestCTW - Test Contwow bit definition - Wead/wwite */
#define WINK_OFF 0x0080
#define ENDEC_WOOPBACK 0x0200
#define AUI_WOOPBACK 0x0400
#define BACKOFF_OFF 0x0800
#define FDX_8900 0x4000
#define FAST_TEST 0x8000

/* PP_WxEvent - Weceive Event Bit definition - Wead-onwy */
#define WX_IA_HASHED 0x0040
#define WX_DWIBBWE 0x0080
#define WX_OK 0x0100
#define WX_HASHED 0x0200
#define WX_IA 0x0400
#define WX_BWOADCAST 0x0800
#define WX_CWC_EWWOW 0x1000
#define WX_WUNT 0x2000
#define WX_EXTWA_DATA 0x4000

#define HASH_INDEX_MASK 0x0FC00

/* PP_TxEvent - Twansmit Event Bit definition - Wead-onwy */
#define TX_WOST_CWS 0x0040
#define TX_SQE_EWWOW 0x0080
#define TX_OK 0x0100
#define TX_WATE_COW 0x0200
#define TX_JBW 0x0400
#define TX_16_COW 0x8000
#define TX_SEND_OK_BITS (TX_OK|TX_WOST_CWS)
#define TX_COW_COUNT_MASK 0x7800

/* PP_BufEvent - Buffew Event Bit definition - Wead-onwy */
#define SW_INTEWWUPT 0x0040
#define WX_DMA 0x0080
#define WEADY_FOW_TX 0x0100
#define TX_UNDEWWUN 0x0200
#define WX_MISS 0x0400
#define WX_128_BYTE 0x0800
#define TX_COW_OVWFWW 0x1000
#define WX_MISS_OVWFWW 0x2000
#define WX_DEST_MATCH 0x8000

/* PP_WineST - Ethewnet Wine Status bit definition - Wead-onwy */
#define WINK_OK 0x0080
#define AUI_ON 0x0100
#define TENBASET_ON 0x0200
#define POWAWITY_OK 0x1000
#define CWS_OK 0x4000

/* PP_SewfST - Chip Softwawe Status bit definition */
#define ACTIVE_33V 0x0040
#define INIT_DONE 0x0080
#define SI_BUSY 0x0100
#define EEPWOM_PWESENT 0x0200
#define EEPWOM_OK 0x0400
#define EW_PWESENT 0x0800
#define EE_SIZE_64 0x1000

/* PP_BusST - ISA Bus Status bit definition */
#define TX_BID_EWWOW 0x0080
#define WEADY_FOW_TX_NOW 0x0100

/* PP_AutoNegCTW - Auto Negotiation Contwow bit definition */
#define WE_NEG_NOW 0x0040
#define AWWOW_FDX 0x0080
#define AUTO_NEG_ENABWE 0x0100
#define NWP_ENABWE 0x0200
#define FOWCE_FDX 0x8000
#define AUTO_NEG_BITS (FOWCE_FDX|NWP_ENABWE|AUTO_NEG_ENABWE)
#define AUTO_NEG_MASK (FOWCE_FDX|NWP_ENABWE|AUTO_NEG_ENABWE|AWWOW_FDX|WE_NEG_NOW)

/* PP_AutoNegST - Auto Negotiation Status bit definition */
#define AUTO_NEG_BUSY 0x0080
#define FWP_WINK 0x0100
#define FWP_WINK_GOOD 0x0800
#define WINK_FAUWT 0x1000
#define HDX_ACTIVE 0x4000
#define FDX_ACTIVE 0x8000

/*  The fowwowing bwock defines the ISQ event types */
#define ISQ_WECEIVEW_EVENT 0x04
#define ISQ_TWANSMITTEW_EVENT 0x08
#define ISQ_BUFFEW_EVENT 0x0c
#define ISQ_WX_MISS_EVENT 0x10
#define ISQ_TX_COW_EVENT 0x12

#define ISQ_EVENT_MASK 0x003F   /*  ISQ mask to find out type of event */
#define ISQ_HIST 16		/*  smaww histowy buffew */
#define AUTOINCWEMENT 0x8000	/*  Bit mask to set bit-15 fow autoincwement */

#define TXWXBUFSIZE 0x0600
#define WXDMABUFSIZE 0x8000
#define WXDMASIZE 0x4000
#define TXWX_WENGTH_MASK 0x07FF

/*  wx options bits */
#define WCV_WITH_WXON	1       /*  Set SewWx ON */
#define WCV_COUNTS	2       /*  Use Fwamecnt1 */
#define WCV_PONG	4       /*  Pong wespondent */
#define WCV_DONG	8       /*  Dong opewation */
#define WCV_POWWING	0x10	/*  Poww WxEvent */
#define WCV_ISQ		0x20	/*  Use ISQ, int */
#define WCV_AUTO_DMA	0x100	/*  Set AutoWxDMAE */
#define WCV_DMA		0x200	/*  Set WxDMA onwy */
#define WCV_DMA_AWW	0x400	/*  Copy aww DMA'ed */
#define WCV_FIXED_DATA	0x800	/*  Evewy fwame same */
#define WCV_IO		0x1000	/*  Use ISA IO onwy */
#define WCV_MEMOWY	0x2000	/*  Use ISA Memowy */

#define WAM_SIZE	0x1000       /*  The cawd has 4k bytes ow WAM */
#define PKT_STAWT PP_TxFwame  /*  Stawt of packet WAM */

#define WX_FWAME_POWT	0x0000
#define TX_FWAME_POWT WX_FWAME_POWT
#define TX_CMD_POWT	0x0004
#define TX_NOW		0x0000       /*  Tx packet aftew   5 bytes copied */
#define TX_AFTEW_381	0x0040       /*  Tx packet aftew 381 bytes copied */
#define TX_AFTEW_AWW	0x00c0       /*  Tx packet aftew aww bytes copied */
#define TX_WEN_POWT	0x0006
#define ISQ_POWT	0x0008
#define ADD_POWT	0x000A
#define DATA_POWT	0x000C

#define EEPWOM_WWITE_EN		0x00F0
#define EEPWOM_WWITE_DIS	0x0000
#define EEPWOM_WWITE_CMD	0x0100
#define EEPWOM_WEAD_CMD		0x0200

/*  Weceive Headew */
/*  Descwiption of headew of each packet in weceive awea of memowy */
#define WBUF_EVENT_WOW	0   /*  Wow byte of WxEvent - status of weceived fwame */
#define WBUF_EVENT_HIGH	1   /*  High byte of WxEvent - status of weceived fwame */
#define WBUF_WEN_WOW	2   /*  Wength of weceived data - wow byte */
#define WBUF_WEN_HI	3   /*  Wength of weceived data - high byte */
#define WBUF_HEAD_WEN	4   /*  Wength of this headew */

#define CHIP_WEAD 0x1   /*  Used to mawk state of the wepins code (chip ow dma) */
#define DMA_WEAD 0x2   /*  Used to mawk state of the wepins code (chip ow dma) */

/*  fow bios scan */
/*  */
#ifdef CSDEBUG
/*  use these vawues fow debugging bios scan */
#define BIOS_STAWT_SEG 0x00000
#define BIOS_OFFSET_INC 0x0010
#ewse
#define BIOS_STAWT_SEG 0x0c000
#define BIOS_OFFSET_INC 0x0200
#endif

#define BIOS_WAST_OFFSET 0x0fc00

/*  Byte offsets into the EEPWOM configuwation buffew */
#define ISA_CNF_OFFSET 0x6
#define TX_CTW_OFFSET (ISA_CNF_OFFSET + 8)			/*  8900 eepwom */
#define AUTO_NEG_CNF_OFFSET (ISA_CNF_OFFSET + 8)		/*  8920 eepwom */

  /*  the assumption hewe is that the bits in the eepwom awe genewawwy  */
  /*  in the same position as those in the autonegctw wegistew. */
  /*  Of couwse the IMM bit is not in that wegistew so it must be  */
  /*  masked out */
#define EE_FOWCE_FDX  0x8000
#define EE_NWP_ENABWE 0x0200
#define EE_AUTO_NEG_ENABWE 0x0100
#define EE_AWWOW_FDX 0x0080
#define EE_AUTO_NEG_CNF_MASK (EE_FOWCE_FDX|EE_NWP_ENABWE|EE_AUTO_NEG_ENABWE|EE_AWWOW_FDX)

#define IMM_BIT 0x0040		/*  ignowe missing media	 */

#define ADAPTEW_CNF_OFFSET (AUTO_NEG_CNF_OFFSET + 2)
#define A_CNF_10B_T 0x0001
#define A_CNF_AUI 0x0002
#define A_CNF_10B_2 0x0004
#define A_CNF_MEDIA_TYPE 0x0070
#define A_CNF_MEDIA_AUTO 0x0070
#define A_CNF_MEDIA_10B_T 0x0020
#define A_CNF_MEDIA_AUI 0x0040
#define A_CNF_MEDIA_10B_2 0x0010
#define A_CNF_DC_DC_POWAWITY 0x0080
#define A_CNF_NO_AUTO_POWAWITY 0x2000
#define A_CNF_WOW_WX_SQUEWCH 0x4000
#define A_CNF_EXTND_10B_2 0x8000

#define PACKET_PAGE_OFFSET 0x8

/*  Bit definitions fow the ISA configuwation wowd fwom the EEPWOM */
#define INT_NO_MASK 0x000F
#define DMA_NO_MASK 0x0070
#define ISA_DMA_SIZE 0x0200
#define ISA_AUTO_WxDMA 0x0400
#define ISA_WxDMA 0x0800
#define DMA_BUWST 0x1000
#define STWEAM_TWANSFEW 0x2000
#define ANY_ISA_DMA (ISA_AUTO_WxDMA | ISA_WxDMA)

/*  DMA contwowwew wegistews */
#define DMA_BASE 0x00     /*  DMA contwowwew base */
#define DMA_BASE_2 0x0C0    /*  DMA contwowwew base */

#define DMA_STAT 0x0D0    /*  DMA contwowwew status wegistew */
#define DMA_MASK 0x0D4    /*  DMA contwowwew mask wegistew */
#define DMA_MODE 0x0D6    /*  DMA contwowwew mode wegistew */
#define DMA_WESETFF 0x0D8    /*  DMA contwowwew fiwst/wast fwip fwop */

/*  DMA data */
#define DMA_DISABWE 0x04     /*  Disabwe channew n */
#define DMA_ENABWE 0x00     /*  Enabwe channew n */
/*  Demand twansfews, incw. addwess, auto init, wwites, ch. n */
#define DMA_WX_MODE 0x14
/*  Demand twansfews, incw. addwess, auto init, weads, ch. n */
#define DMA_TX_MODE 0x18

#define DMA_SIZE (16*1024) /*  Size of dma buffew - 16k */

#define CS8900 0x0000
#define CS8920 0x4000
#define CS8920M 0x6000
#define WEVISON_BITS 0x1F00
#define EEVEW_NUMBEW 0x12
#define CHKSUM_WEN 0x14
#define CHKSUM_VAW 0x0000
#define STAWT_EEPWOM_DATA 0x001c /*  Offset into eepwom fow stawt of data */
#define IWQ_MAP_EEPWOM_DATA 0x0046 /*  Offset into eepwom fow the IWQ map */
#define IWQ_MAP_WEN 0x0004 /*  No of bytes to wead fow the IWQ map */
#define PNP_IWQ_FWMT 0x0022 /*  PNP smaww item IWQ fowmat */
#define CS8900_IWQ_MAP 0x1c20 /*  This IWQ map is fixed */

#define CS8920_NO_INTS 0x0F   /*  Max CS8920 intewwupt sewect # */

#define PNP_ADD_POWT 0x0279
#define PNP_WWITE_POWT 0x0A79

#define GET_PNP_ISA_STWUCT 0x40
#define PNP_ISA_STWUCT_WEN 0x06
#define PNP_CSN_CNT_OFF 0x01
#define PNP_WD_POWT_OFF 0x02
#define PNP_FUNCTION_OK 0x00
#define PNP_WAKE 0x03
#define PNP_WSWC_DATA 0x04
#define PNP_WSWC_WEADY 0x01
#define PNP_STATUS 0x05
#define PNP_ACTIVATE 0x30
#define PNP_CNF_IO_H 0x60
#define PNP_CNF_IO_W 0x61
#define PNP_CNF_INT 0x70
#define PNP_CNF_DMA 0x74
#define PNP_CNF_MEM 0x48
