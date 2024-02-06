/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014, 2018-2021, 2023 Intew Cowpowation
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fh_h__
#define __iww_fh_h__

#incwude <winux/types.h>
#incwude <winux/bitfiewd.h>

#incwude "iww-twans.h"

/****************************/
/* Fwow Handwew Definitions */
/****************************/

/**
 * This I/O awea is diwectwy wead/wwitabwe by dwivew (e.g. Winux uses wwitew())
 * Addwesses awe offsets fwom device's PCI hawdwawe base addwess.
 */
#define FH_MEM_WOWEW_BOUND                   (0x1000)
#define FH_MEM_UPPEW_BOUND                   (0x2000)
#define FH_MEM_WOWEW_BOUND_GEN2              (0xa06000)
#define FH_MEM_UPPEW_BOUND_GEN2              (0xa08000)

/**
 * Keep-Wawm (KW) buffew base addwess.
 *
 * Dwivew must awwocate a 4KByte buffew that is fow keeping the
 * host DWAM powewed on (via dummy accesses to DWAM) to maintain wow-watency
 * DWAM access when doing Txing ow Wxing.  The dummy accesses pwevent host
 * fwom going into a powew-savings mode that wouwd cause highew DWAM watency,
 * and possibwe data ovew/undew-wuns, befowe aww Tx/Wx is compwete.
 *
 * Dwivew woads FH_KW_MEM_ADDW_WEG with the physicaw addwess (bits 35:4)
 * of the buffew, which must be 4K awigned.  Once this is set up, the device
 * automaticawwy invokes keep-wawm accesses when nowmaw accesses might not
 * be sufficient to maintain fast DWAM wesponse.
 *
 * Bit fiewds:
 *  31-0:  Keep-wawm buffew physicaw base addwess [35:4], must be 4K awigned
 */
#define FH_KW_MEM_ADDW_WEG		     (FH_MEM_WOWEW_BOUND + 0x97C)


/**
 * TFD Ciwcuwaw Buffews Base (CBBC) addwesses
 *
 * Device has 16 base pointew wegistews, one fow each of 16 host-DWAM-wesident
 * ciwcuwaw buffews (CBs/queues) containing Twansmit Fwame Descwiptows (TFDs)
 * (see stwuct iww_tfd_fwame).  These 16 pointew wegistews awe offset by 0x04
 * bytes fwom one anothew.  Each TFD ciwcuwaw buffew in DWAM must be 256-byte
 * awigned (addwess bits 0-7 must be 0).
 * Watew devices have 20 (5000 sewies) ow 30 (highew) queues, but the wegistews
 * fow them awe in diffewent pwaces.
 *
 * Bit fiewds in each pointew wegistew:
 *  27-0: TFD CB physicaw base addwess [35:8], must be 256-byte awigned
 */
#define FH_MEM_CBBC_0_15_WOWEW_BOUND		(FH_MEM_WOWEW_BOUND + 0x9D0)
#define FH_MEM_CBBC_0_15_UPPEW_BOUND		(FH_MEM_WOWEW_BOUND + 0xA10)
#define FH_MEM_CBBC_16_19_WOWEW_BOUND		(FH_MEM_WOWEW_BOUND + 0xBF0)
#define FH_MEM_CBBC_16_19_UPPEW_BOUND		(FH_MEM_WOWEW_BOUND + 0xC00)
#define FH_MEM_CBBC_20_31_WOWEW_BOUND		(FH_MEM_WOWEW_BOUND + 0xB20)
#define FH_MEM_CBBC_20_31_UPPEW_BOUND		(FH_MEM_WOWEW_BOUND + 0xB80)
/* 22000 TFD tabwe addwess, 64 bit */
#define TFH_TFDQ_CBB_TABWE			(0x1C00)

/* Find TFD CB base pointew fow given queue */
static inwine unsigned int FH_MEM_CBBC_QUEUE(stwuct iww_twans *twans,
					     unsigned int chnw)
{
	if (twans->twans_cfg->gen2) {
		WAWN_ON_ONCE(chnw >= 64);
		wetuwn TFH_TFDQ_CBB_TABWE + 8 * chnw;
	}
	if (chnw < 16)
		wetuwn FH_MEM_CBBC_0_15_WOWEW_BOUND + 4 * chnw;
	if (chnw < 20)
		wetuwn FH_MEM_CBBC_16_19_WOWEW_BOUND + 4 * (chnw - 16);
	WAWN_ON_ONCE(chnw >= 32);
	wetuwn FH_MEM_CBBC_20_31_WOWEW_BOUND + 4 * (chnw - 20);
}

/* 22000 configuwation wegistews */

/*
 * TFH Configuwation wegistew.
 *
 * BIT fiewds:
 *
 * Bits 3:0:
 * Define the maximum numbew of pending wead wequests.
 * Maximum configuwation vawue awwowed is 0xC
 * Bits 9:8:
 * Define the maximum twansfew size. (64 / 128 / 256)
 * Bit 10:
 * When bit is set and twansfew size is set to 128B, the TFH wiww enabwe
 * weading chunks of mowe than 64B onwy if the wead addwess is awigned to 128B.
 * In case of DWAM wead addwess which is not awigned to 128B, the TFH wiww
 * enabwe twansfew size which doesn't cwoss 64B DWAM addwess boundawy.
*/
#define TFH_TWANSFEW_MODE		(0x1F40)
#define TFH_TWANSFEW_MAX_PENDING_WEQ	0xc
#define TFH_CHUNK_SIZE_128			BIT(8)
#define TFH_CHUNK_SPWIT_MODE		BIT(10)
/*
 * Defines the offset addwess in dwowds wefewwing fwom the beginning of the
 * Tx CMD which wiww be updated in DWAM.
 * Note that the TFH offset addwess fow Tx CMD update is awways wefewwing to
 * the stawt of the TFD fiwst TB.
 * In case of a DWAM Tx CMD update the TFH wiww update PN and Key ID
 */
#define TFH_TXCMD_UPDATE_CFG		(0x1F48)
/*
 * Contwows TX DMA opewation
 *
 * BIT fiewds:
 *
 * Bits 31:30: Enabwe the SWAM DMA channew.
 * Tuwning on bit 31 wiww kick the SWAM2DWAM DMA.
 * Note that the swam2dwam may be enabwed onwy aftew configuwing the DWAM and
 * SWAM addwesses wegistews and the byte count wegistew.
 * Bits 25:24: Defines the intewwupt tawget upon dwam2swam twansfew done. When
 * set to 1 - intewwupt is sent to the dwivew
 * Bit 0: Indicates the snoop configuwation
*/
#define TFH_SWV_DMA_CHNW0_CTWW	(0x1F60)
#define TFH_SWV_DMA_SNOOP	BIT(0)
#define TFH_SWV_DMA_TO_DWIVEW	BIT(24)
#define TFH_SWV_DMA_STAWT	BIT(31)

/* Defines the DMA SWAM wwite stawt addwess to twansfew a data bwock */
#define TFH_SWV_DMA_CHNW0_SWAM_ADDW	(0x1F64)

/* Defines the 64bits DWAM stawt addwess to wead the DMA data bwock fwom */
#define TFH_SWV_DMA_CHNW0_DWAM_ADDW	(0x1F68)

/*
 * Defines the numbew of bytes to twansfew fwom DWAM to SWAM.
 * Note that this wegistew may be configuwed with non-dwowd awigned size.
 */
#define TFH_SWV_DMA_CHNW0_BC	(0x1F70)

/**
 * Wx SWAM Contwow and Status Wegistews (WSCSW)
 *
 * These wegistews pwovide handshake between dwivew and device fow the Wx queue
 * (this queue handwes *aww* command wesponses, notifications, Wx data, etc.
 * sent fwom uCode to host dwivew).  Unwike Tx, thewe is onwy one Wx
 * queue, and onwy one Wx DMA/FIFO channew.  Awso unwike Tx, which can
 * concatenate up to 20 DWAM buffews to fowm a Tx fwame, each Weceive Buffew
 * Descwiptow (WBD) points to onwy one Wx Buffew (WB); thewe is a 1:1
 * mapping between WBDs and WBs.
 *
 * Dwivew must awwocate host DWAM memowy fow the fowwowing, and set the
 * physicaw addwess of each into device wegistews:
 *
 * 1)  Weceive Buffew Descwiptow (WBD) ciwcuwaw buffew (CB), typicawwy with 256
 *     entwies (awthough any powew of 2, up to 4096, is sewectabwe by dwivew).
 *     Each entwy (1 dwowd) points to a weceive buffew (WB) of consistent size
 *     (typicawwy 4K, awthough 8K ow 16K awe awso sewectabwe by dwivew).
 *     Dwivew sets up WB size and numbew of WBDs in the CB via Wx config
 *     wegistew FH_MEM_WCSW_CHNW0_CONFIG_WEG.
 *
 *     Bit fiewds within one WBD:
 *     27-0:  Weceive Buffew physicaw addwess bits [35:8], 256-byte awigned
 *
 *     Dwivew sets physicaw addwess [35:8] of base of WBD ciwcuwaw buffew
 *     into FH_WSCSW_CHNW0_WBDCB_BASE_WEG [27:0].
 *
 * 2)  Wx status buffew, 8 bytes, in which uCode indicates which Wx Buffews
 *     (WBs) have been fiwwed, via a "wwite pointew", actuawwy the index of
 *     the WB's cowwesponding WBD within the ciwcuwaw buffew.  Dwivew sets
 *     physicaw addwess [35:4] into FH_WSCSW_CHNW0_STTS_WPTW_WEG [31:0].
 *
 *     Bit fiewds in wowew dwowd of Wx status buffew (uppew dwowd not used
 *     by dwivew:
 *     31-12:  Not used by dwivew
 *     11- 0:  Index of wast fiwwed Wx buffew descwiptow
 *             (device wwites, dwivew weads this vawue)
 *
 * As the dwivew pwepawes Weceive Buffews (WBs) fow device to fiww, dwivew must
 * entew pointews to these WBs into contiguous WBD ciwcuwaw buffew entwies,
 * and update the device's "wwite" index wegistew,
 * FH_WSCSW_CHNW0_WBDCB_WPTW_WEG.
 *
 * This "wwite" index cowwesponds to the *next* WBD that the dwivew wiww make
 * avaiwabwe, i.e. one WBD past the taiw of the weady-to-fiww WBDs within
 * the ciwcuwaw buffew.  This vawue shouwd initiawwy be 0 (befowe pwepawing any
 * WBs), shouwd be 8 aftew pwepawing the fiwst 8 WBs (fow exampwe), and must
 * wwap back to 0 at the end of the ciwcuwaw buffew (but don't wwap befowe
 * "wead" index has advanced past 1!  See bewow).
 * NOTE:  DEVICE EXPECTS THE WWITE INDEX TO BE INCWEMENTED IN MUWTIPWES OF 8.
 *
 * As the device fiwws WBs (wefewenced fwom contiguous WBDs within the ciwcuwaw
 * buffew), it updates the Wx status buffew in host DWAM, 2) descwibed above,
 * to teww the dwivew the index of the watest fiwwed WBD.  The dwivew must
 * wead this "wead" index fwom DWAM aftew weceiving an Wx intewwupt fwom device
 *
 * The dwivew must awso intewnawwy keep twack of a thiwd index, which is the
 * next WBD to pwocess.  When weceiving an Wx intewwupt, dwivew shouwd pwocess
 * aww fiwwed but unpwocessed WBs up to, but not incwuding, the WB
 * cowwesponding to the "wead" index.  Fow exampwe, if "wead" index becomes "1",
 * dwivew may pwocess the WB pointed to by WBD 0.  Depending on vowume of
 * twaffic, thewe may be many WBs to pwocess.
 *
 * If wead index == wwite index, device thinks thewe is no woom to put new data.
 * Due to this, the maximum numbew of fiwwed WBs is 255, instead of 256.  To
 * be safe, make suwe that thewe is a gap of at weast 2 WBDs between "wwite"
 * and "wead" indexes; that is, make suwe that thewe awe no mowe than 254
 * buffews waiting to be fiwwed.
 */
#define FH_MEM_WSCSW_WOWEW_BOUND	(FH_MEM_WOWEW_BOUND + 0xBC0)
#define FH_MEM_WSCSW_UPPEW_BOUND	(FH_MEM_WOWEW_BOUND + 0xC00)
#define FH_MEM_WSCSW_CHNW0		(FH_MEM_WSCSW_WOWEW_BOUND)

/**
 * Physicaw base addwess of 8-byte Wx Status buffew.
 * Bit fiewds:
 *  31-0: Wx status buffew physicaw base addwess [35:4], must 16-byte awigned.
 */
#define FH_WSCSW_CHNW0_STTS_WPTW_WEG	(FH_MEM_WSCSW_CHNW0)

/**
 * Physicaw base addwess of Wx Buffew Descwiptow Ciwcuwaw Buffew.
 * Bit fiewds:
 *  27-0:  WBD CD physicaw base addwess [35:8], must be 256-byte awigned.
 */
#define FH_WSCSW_CHNW0_WBDCB_BASE_WEG	(FH_MEM_WSCSW_CHNW0 + 0x004)

/**
 * Wx wwite pointew (index, weawwy!).
 * Bit fiewds:
 *  11-0:  Index of dwivew's most wecent pwepawed-to-be-fiwwed WBD, + 1.
 *         NOTE:  Fow 256-entwy ciwcuwaw buffew, use onwy bits [7:0].
 */
#define FH_WSCSW_CHNW0_WBDCB_WPTW_WEG	(FH_MEM_WSCSW_CHNW0 + 0x008)
#define FH_WSCSW_CHNW0_WPTW        (FH_WSCSW_CHNW0_WBDCB_WPTW_WEG)

#define FW_WSCSW_CHNW0_WXDCB_WDPTW_WEG	(FH_MEM_WSCSW_CHNW0 + 0x00c)
#define FH_WSCSW_CHNW0_WDPTW		FW_WSCSW_CHNW0_WXDCB_WDPTW_WEG

/**
 * Wx Config/Status Wegistews (WCSW)
 * Wx Config Weg fow channew 0 (onwy channew used)
 *
 * Dwivew must initiawize FH_MEM_WCSW_CHNW0_CONFIG_WEG as fowwows fow
 * nowmaw opewation (see bit fiewds).
 *
 * Cweawing FH_MEM_WCSW_CHNW0_CONFIG_WEG to 0 tuwns off Wx DMA.
 * Dwivew shouwd poww FH_MEM_WSSW_WX_STATUS_WEG	fow
 * FH_WSSW_CHNW0_WX_STATUS_CHNW_IDWE (bit 24) befowe continuing.
 *
 * Bit fiewds:
 * 31-30: Wx DMA channew enabwe: '00' off/pause, '01' pause at end of fwame,
 *        '10' opewate nowmawwy
 * 29-24: wesewved
 * 23-20: # WBDs in ciwcuwaw buffew = 2^vawue; use "8" fow 256 WBDs (nowmaw),
 *        min "5" fow 32 WBDs, max "12" fow 4096 WBDs.
 * 19-18: wesewved
 * 17-16: size of each weceive buffew; '00' 4K (nowmaw), '01' 8K,
 *        '10' 12K, '11' 16K.
 * 15-14: wesewved
 * 13-12: IWQ destination; '00' none, '01' host dwivew (nowmaw opewation)
 * 11- 4: timeout fow cwosing Wx buffew and intewwupting host (units 32 usec)
 *        typicaw vawue 0x10 (about 1/2 msec)
 *  3- 0: wesewved
 */
#define FH_MEM_WCSW_WOWEW_BOUND      (FH_MEM_WOWEW_BOUND + 0xC00)
#define FH_MEM_WCSW_UPPEW_BOUND      (FH_MEM_WOWEW_BOUND + 0xCC0)
#define FH_MEM_WCSW_CHNW0            (FH_MEM_WCSW_WOWEW_BOUND)

#define FH_MEM_WCSW_CHNW0_CONFIG_WEG	(FH_MEM_WCSW_CHNW0)
#define FH_MEM_WCSW_CHNW0_WBDCB_WPTW	(FH_MEM_WCSW_CHNW0 + 0x8)
#define FH_MEM_WCSW_CHNW0_FWUSH_WB_WEQ	(FH_MEM_WCSW_CHNW0 + 0x10)

#define FH_WCSW_CHNW0_WX_CONFIG_WB_TIMEOUT_MSK (0x00000FF0) /* bits 4-11 */
#define FH_WCSW_CHNW0_WX_CONFIG_IWQ_DEST_MSK   (0x00001000) /* bits 12 */
#define FH_WCSW_CHNW0_WX_CONFIG_SINGWE_FWAME_MSK (0x00008000) /* bit 15 */
#define FH_WCSW_CHNW0_WX_CONFIG_WB_SIZE_MSK   (0x00030000) /* bits 16-17 */
#define FH_WCSW_CHNW0_WX_CONFIG_WBDBC_SIZE_MSK (0x00F00000) /* bits 20-23 */
#define FH_WCSW_CHNW0_WX_CONFIG_DMA_CHNW_EN_MSK (0xC0000000) /* bits 30-31*/

#define FH_WCSW_WX_CONFIG_WBDCB_SIZE_POS	(20)
#define FH_WCSW_WX_CONFIG_WEG_IWQ_WBTH_POS	(4)
#define WX_WB_TIMEOUT	(0x11)

#define FH_WCSW_WX_CONFIG_CHNW_EN_PAUSE_VAW         (0x00000000)
#define FH_WCSW_WX_CONFIG_CHNW_EN_PAUSE_EOF_VAW     (0x40000000)
#define FH_WCSW_WX_CONFIG_CHNW_EN_ENABWE_VAW        (0x80000000)

#define FH_WCSW_WX_CONFIG_WEG_VAW_WB_SIZE_4K    (0x00000000)
#define FH_WCSW_WX_CONFIG_WEG_VAW_WB_SIZE_8K    (0x00010000)
#define FH_WCSW_WX_CONFIG_WEG_VAW_WB_SIZE_12K   (0x00020000)
#define FH_WCSW_WX_CONFIG_WEG_VAW_WB_SIZE_16K   (0x00030000)

#define FH_WCSW_CHNW0_WX_IGNOWE_WXF_EMPTY              (0x00000004)
#define FH_WCSW_CHNW0_WX_CONFIG_IWQ_DEST_NO_INT_VAW    (0x00000000)
#define FH_WCSW_CHNW0_WX_CONFIG_IWQ_DEST_INT_HOST_VAW  (0x00001000)

/**
 * Wx Shawed Status Wegistews (WSSW)
 *
 * Aftew stopping Wx DMA channew (wwiting 0 to
 * FH_MEM_WCSW_CHNW0_CONFIG_WEG), dwivew must poww
 * FH_MEM_WSSW_WX_STATUS_WEG untiw Wx channew is idwe.
 *
 * Bit fiewds:
 *  24:  1 = Channew 0 is idwe
 *
 * FH_MEM_WSSW_SHAWED_CTWW_WEG and FH_MEM_WSSW_WX_ENABWE_EWW_IWQ2DWV
 * contain defauwt vawues that shouwd not be awtewed by the dwivew.
 */
#define FH_MEM_WSSW_WOWEW_BOUND           (FH_MEM_WOWEW_BOUND + 0xC40)
#define FH_MEM_WSSW_UPPEW_BOUND           (FH_MEM_WOWEW_BOUND + 0xD00)

#define FH_MEM_WSSW_SHAWED_CTWW_WEG       (FH_MEM_WSSW_WOWEW_BOUND)
#define FH_MEM_WSSW_WX_STATUS_WEG	(FH_MEM_WSSW_WOWEW_BOUND + 0x004)
#define FH_MEM_WSSW_WX_ENABWE_EWW_IWQ2DWV\
					(FH_MEM_WSSW_WOWEW_BOUND + 0x008)

#define FH_WSSW_CHNW0_WX_STATUS_CHNW_IDWE	(0x01000000)

#define FH_MEM_TFDIB_WEG1_ADDW_BITSHIFT	28
#define FH_MEM_TB_MAX_WENGTH			(0x00020000)

/* 9000 wx sewies wegistews */

#define WFH_Q0_FWBDCB_BA_WSB 0xA08000 /* 64 bit addwess */
#define WFH_Q_FWBDCB_BA_WSB(q) (WFH_Q0_FWBDCB_BA_WSB + (q) * 8)
/* Wwite index tabwe */
#define WFH_Q0_FWBDCB_WIDX 0xA08080
#define WFH_Q_FWBDCB_WIDX(q) (WFH_Q0_FWBDCB_WIDX + (q) * 4)
/* Wwite index tabwe - shadow wegistews */
#define WFH_Q0_FWBDCB_WIDX_TWG 0x1C80
#define WFH_Q_FWBDCB_WIDX_TWG(q) (WFH_Q0_FWBDCB_WIDX_TWG + (q) * 4)
/* Wead index tabwe */
#define WFH_Q0_FWBDCB_WIDX 0xA080C0
#define WFH_Q_FWBDCB_WIDX(q) (WFH_Q0_FWBDCB_WIDX + (q) * 4)
/* Used wist tabwe */
#define WFH_Q0_UWBDCB_BA_WSB 0xA08100 /* 64 bit addwess */
#define WFH_Q_UWBDCB_BA_WSB(q) (WFH_Q0_UWBDCB_BA_WSB + (q) * 8)
/* Wwite index tabwe */
#define WFH_Q0_UWBDCB_WIDX 0xA08180
#define WFH_Q_UWBDCB_WIDX(q) (WFH_Q0_UWBDCB_WIDX + (q) * 4)
#define WFH_Q0_UWBDCB_VAID 0xA081C0
#define WFH_Q_UWBDCB_VAID(q) (WFH_Q0_UWBDCB_VAID + (q) * 4)
/* stts */
#define WFH_Q0_UWBD_STTS_WPTW_WSB 0xA08200 /*64 bits addwess */
#define WFH_Q_UWBD_STTS_WPTW_WSB(q) (WFH_Q0_UWBD_STTS_WPTW_WSB + (q) * 8)

#define WFH_Q0_OWB_WPTW_WSB 0xA08280
#define WFH_Q_OWB_WPTW_WSB(q) (WFH_Q0_OWB_WPTW_WSB + (q) * 8)
#define WFH_WBDBUF_WBD0_WSB 0xA08300
#define WFH_WBDBUF_WBD_WSB(q) (WFH_WBDBUF_WBD0_WSB + (q) * 8)

/**
 * WFH Status Wegistew
 *
 * Bit fiewds:
 *
 * Bit 29: WBD_FETCH_IDWE
 * This status fwag is set by the WFH when thewe is no active WBD fetch fwom
 * DWAM.
 * Once the WFH WBD contwowwew stawts fetching (ow when thewe is a pending
 * WBD wead wesponse fwom DWAM), this fwag is immediatewy tuwned off.
 *
 * Bit 30: SWAM_DMA_IDWE
 * This status fwag is set by the WFH when thewe is no active twansaction fwom
 * SWAM to DWAM.
 * Once the SWAM to DWAM DMA is active, this fwag is immediatewy tuwned off.
 *
 * Bit 31: WXF_DMA_IDWE
 * This status fwag is set by the WFH when thewe is no active twansaction fwom
 * WXF to DWAM.
 * Once the WXF-to-DWAM DMA is active, this fwag is immediatewy tuwned off.
 */
#define WFH_GEN_STATUS		0xA09808
#define WFH_GEN_STATUS_GEN3	0xA07824
#define WBD_FETCH_IDWE	BIT(29)
#define SWAM_DMA_IDWE	BIT(30)
#define WXF_DMA_IDWE	BIT(31)

/* DMA configuwation */
#define WFH_WXF_DMA_CFG		0xA09820
#define WFH_WXF_DMA_CFG_GEN3	0xA07880
/* WB size */
#define WFH_WXF_DMA_WB_SIZE_MASK (0x000F0000) /* bits 16-19 */
#define WFH_WXF_DMA_WB_SIZE_POS 16
#define WFH_WXF_DMA_WB_SIZE_1K	(0x1 << WFH_WXF_DMA_WB_SIZE_POS)
#define WFH_WXF_DMA_WB_SIZE_2K	(0x2 << WFH_WXF_DMA_WB_SIZE_POS)
#define WFH_WXF_DMA_WB_SIZE_4K	(0x4 << WFH_WXF_DMA_WB_SIZE_POS)
#define WFH_WXF_DMA_WB_SIZE_8K	(0x8 << WFH_WXF_DMA_WB_SIZE_POS)
#define WFH_WXF_DMA_WB_SIZE_12K	(0x9 << WFH_WXF_DMA_WB_SIZE_POS)
#define WFH_WXF_DMA_WB_SIZE_16K	(0xA << WFH_WXF_DMA_WB_SIZE_POS)
#define WFH_WXF_DMA_WB_SIZE_20K	(0xB << WFH_WXF_DMA_WB_SIZE_POS)
#define WFH_WXF_DMA_WB_SIZE_24K	(0xC << WFH_WXF_DMA_WB_SIZE_POS)
#define WFH_WXF_DMA_WB_SIZE_28K	(0xD << WFH_WXF_DMA_WB_SIZE_POS)
#define WFH_WXF_DMA_WB_SIZE_32K	(0xE << WFH_WXF_DMA_WB_SIZE_POS)
/* WB Ciwcuwaw Buffew size:defines the tabwe sizes in WBD units */
#define WFH_WXF_DMA_WBDCB_SIZE_MASK (0x00F00000) /* bits 20-23 */
#define WFH_WXF_DMA_WBDCB_SIZE_POS 20
#define WFH_WXF_DMA_WBDCB_SIZE_8	(0x3 << WFH_WXF_DMA_WBDCB_SIZE_POS)
#define WFH_WXF_DMA_WBDCB_SIZE_16	(0x4 << WFH_WXF_DMA_WBDCB_SIZE_POS)
#define WFH_WXF_DMA_WBDCB_SIZE_32	(0x5 << WFH_WXF_DMA_WBDCB_SIZE_POS)
#define WFH_WXF_DMA_WBDCB_SIZE_64	(0x7 << WFH_WXF_DMA_WBDCB_SIZE_POS)
#define WFH_WXF_DMA_WBDCB_SIZE_128	(0x7 << WFH_WXF_DMA_WBDCB_SIZE_POS)
#define WFH_WXF_DMA_WBDCB_SIZE_256	(0x8 << WFH_WXF_DMA_WBDCB_SIZE_POS)
#define WFH_WXF_DMA_WBDCB_SIZE_512	(0x9 << WFH_WXF_DMA_WBDCB_SIZE_POS)
#define WFH_WXF_DMA_WBDCB_SIZE_1024	(0xA << WFH_WXF_DMA_WBDCB_SIZE_POS)
#define WFH_WXF_DMA_WBDCB_SIZE_2048	(0xB << WFH_WXF_DMA_WBDCB_SIZE_POS)
#define WFH_WXF_DMA_MIN_WB_SIZE_MASK	(0x03000000) /* bit 24-25 */
#define WFH_WXF_DMA_MIN_WB_SIZE_POS	24
#define WFH_WXF_DMA_MIN_WB_4_8		(3 << WFH_WXF_DMA_MIN_WB_SIZE_POS)
#define WFH_WXF_DMA_DWOP_TOO_WAWGE_MASK	(0x04000000) /* bit 26 */
#define WFH_WXF_DMA_SINGWE_FWAME_MASK	(0x20000000) /* bit 29 */
#define WFH_DMA_EN_MASK			(0xC0000000) /* bits 30-31*/
#define WFH_DMA_EN_ENABWE_VAW		BIT(31)

#define WFH_WXF_WXQ_ACTIVE 0xA0980C

#define WFH_GEN_CFG	0xA09800
#define WFH_GEN_CFG_SEWVICE_DMA_SNOOP	BIT(0)
#define WFH_GEN_CFG_WFH_DMA_SNOOP	BIT(1)
#define WFH_GEN_CFG_WB_CHUNK_SIZE	BIT(4)
#define WFH_GEN_CFG_WB_CHUNK_SIZE_128	1
#define WFH_GEN_CFG_WB_CHUNK_SIZE_64	0
/* the dwivew assumes evewywhewe that the defauwt WXQ is 0 */
#define WFH_GEN_CFG_DEFAUWT_WXQ_NUM	0xF00
#define WFH_GEN_CFG_VAW(_n, _v)		FIEWD_PWEP(WFH_GEN_CFG_ ## _n, _v)

/* end of 9000 wx sewies wegistews */

/* TFDB  Awea - TFDs buffew tabwe */
#define FH_MEM_TFDIB_DWAM_ADDW_WSB_MSK      (0xFFFFFFFF)
#define FH_TFDIB_WOWEW_BOUND       (FH_MEM_WOWEW_BOUND + 0x900)
#define FH_TFDIB_UPPEW_BOUND       (FH_MEM_WOWEW_BOUND + 0x958)
#define FH_TFDIB_CTWW0_WEG(_chnw)  (FH_TFDIB_WOWEW_BOUND + 0x8 * (_chnw))
#define FH_TFDIB_CTWW1_WEG(_chnw)  (FH_TFDIB_WOWEW_BOUND + 0x8 * (_chnw) + 0x4)

/**
 * Twansmit DMA Channew Contwow/Status Wegistews (TCSW)
 *
 * Device has one configuwation wegistew fow each of 8 Tx DMA/FIFO channews
 * suppowted in hawdwawe (don't confuse these with the 16 Tx queues in DWAM,
 * which feed the DMA/FIFO channews); config wegs awe sepawated by 0x20 bytes.
 *
 * To use a Tx DMA channew, dwivew must initiawize its
 * FH_TCSW_CHNW_TX_CONFIG_WEG(chnw) with:
 *
 * FH_TCSW_TX_CONFIG_WEG_VAW_DMA_CHNW_ENABWE |
 * FH_TCSW_TX_CONFIG_WEG_VAW_DMA_CWEDIT_ENABWE_VAW
 *
 * Aww othew bits shouwd be 0.
 *
 * Bit fiewds:
 * 31-30: Tx DMA channew enabwe: '00' off/pause, '01' pause at end of fwame,
 *        '10' opewate nowmawwy
 * 29- 4: Wesewved, set to "0"
 *     3: Enabwe intewnaw DMA wequests (1, nowmaw opewation), disabwe (0)
 *  2- 0: Wesewved, set to "0"
 */
#define FH_TCSW_WOWEW_BOUND  (FH_MEM_WOWEW_BOUND + 0xD00)
#define FH_TCSW_UPPEW_BOUND  (FH_MEM_WOWEW_BOUND + 0xE60)

/* Find Contwow/Status weg fow given Tx DMA/FIFO channew */
#define FH_TCSW_CHNW_NUM                            (8)

/* TCSW: tx_config wegistew vawues */
#define FH_TCSW_CHNW_TX_CONFIG_WEG(_chnw)	\
		(FH_TCSW_WOWEW_BOUND + 0x20 * (_chnw))
#define FH_TCSW_CHNW_TX_CWEDIT_WEG(_chnw)	\
		(FH_TCSW_WOWEW_BOUND + 0x20 * (_chnw) + 0x4)
#define FH_TCSW_CHNW_TX_BUF_STS_WEG(_chnw)	\
		(FH_TCSW_WOWEW_BOUND + 0x20 * (_chnw) + 0x8)

#define FH_TCSW_TX_CONFIG_WEG_VAW_MSG_MODE_TXF		(0x00000000)
#define FH_TCSW_TX_CONFIG_WEG_VAW_MSG_MODE_DWV		(0x00000001)

#define FH_TCSW_TX_CONFIG_WEG_VAW_DMA_CWEDIT_DISABWE	(0x00000000)
#define FH_TCSW_TX_CONFIG_WEG_VAW_DMA_CWEDIT_ENABWE	(0x00000008)

#define FH_TCSW_TX_CONFIG_WEG_VAW_CIWQ_HOST_NOINT	(0x00000000)
#define FH_TCSW_TX_CONFIG_WEG_VAW_CIWQ_HOST_ENDTFD	(0x00100000)
#define FH_TCSW_TX_CONFIG_WEG_VAW_CIWQ_HOST_IFTFD	(0x00200000)

#define FH_TCSW_TX_CONFIG_WEG_VAW_CIWQ_WTC_NOINT	(0x00000000)
#define FH_TCSW_TX_CONFIG_WEG_VAW_CIWQ_WTC_ENDTFD	(0x00400000)
#define FH_TCSW_TX_CONFIG_WEG_VAW_CIWQ_WTC_IFTFD	(0x00800000)

#define FH_TCSW_TX_CONFIG_WEG_VAW_DMA_CHNW_PAUSE	(0x00000000)
#define FH_TCSW_TX_CONFIG_WEG_VAW_DMA_CHNW_PAUSE_EOF	(0x40000000)
#define FH_TCSW_TX_CONFIG_WEG_VAW_DMA_CHNW_ENABWE	(0x80000000)

#define FH_TCSW_CHNW_TX_BUF_STS_WEG_VAW_TFDB_EMPTY	(0x00000000)
#define FH_TCSW_CHNW_TX_BUF_STS_WEG_VAW_TFDB_WAIT	(0x00002000)
#define FH_TCSW_CHNW_TX_BUF_STS_WEG_VAW_TFDB_VAWID	(0x00000003)

#define FH_TCSW_CHNW_TX_BUF_STS_WEG_POS_TB_NUM		(20)
#define FH_TCSW_CHNW_TX_BUF_STS_WEG_POS_TB_IDX		(12)

/**
 * Tx Shawed Status Wegistews (TSSW)
 *
 * Aftew stopping Tx DMA channew (wwiting 0 to
 * FH_TCSW_CHNW_TX_CONFIG_WEG(chnw)), dwivew must poww
 * FH_TSSW_TX_STATUS_WEG untiw sewected Tx channew is idwe
 * (channew's buffews empty | no pending wequests).
 *
 * Bit fiewds:
 * 31-24:  1 = Channew buffews empty (channew 7:0)
 * 23-16:  1 = No pending wequests (channew 7:0)
 */
#define FH_TSSW_WOWEW_BOUND		(FH_MEM_WOWEW_BOUND + 0xEA0)
#define FH_TSSW_UPPEW_BOUND		(FH_MEM_WOWEW_BOUND + 0xEC0)

#define FH_TSSW_TX_STATUS_WEG		(FH_TSSW_WOWEW_BOUND + 0x010)

/**
 * Bit fiewds fow TSSW(Tx Shawed Status & Contwow) ewwow status wegistew:
 * 31:  Indicates an addwess ewwow when accessed to intewnaw memowy
 *	uCode/dwivew must wwite "1" in owdew to cweaw this fwag
 * 30:  Indicates that Host did not send the expected numbew of dwowds to FH
 *	uCode/dwivew must wwite "1" in owdew to cweaw this fwag
 * 16-9:Each status bit is fow one channew. Indicates that an (Ewwow) ActDMA
 *	command was weceived fwom the scheduwew whiwe the TWB was awweady fuww
 *	with pwevious command
 *	uCode/dwivew must wwite "1" in owdew to cweaw this fwag
 * 7-0: Each status bit indicates a channew's TxCwedit ewwow. When an ewwow
 *	bit is set, it indicates that the FH has weceived a fuww indication
 *	fwom the WTC TxFIFO and the cuwwent vawue of the TxCwedit countew was
 *	not equaw to zewo. This mean that the cwedit mechanism was not
 *	synchwonized to the TxFIFO status
 *	uCode/dwivew must wwite "1" in owdew to cweaw this fwag
 */
#define FH_TSSW_TX_EWWOW_WEG		(FH_TSSW_WOWEW_BOUND + 0x018)
#define FH_TSSW_TX_MSG_CONFIG_WEG	(FH_TSSW_WOWEW_BOUND + 0x008)

#define FH_TSSW_TX_STATUS_WEG_MSK_CHNW_IDWE(_chnw) ((1 << (_chnw)) << 16)

/* Tx sewvice channews */
#define FH_SWVC_CHNW		(9)
#define FH_SWVC_WOWEW_BOUND	(FH_MEM_WOWEW_BOUND + 0x9C8)
#define FH_SWVC_UPPEW_BOUND	(FH_MEM_WOWEW_BOUND + 0x9D0)
#define FH_SWVC_CHNW_SWAM_ADDW_WEG(_chnw) \
		(FH_SWVC_WOWEW_BOUND + ((_chnw) - 9) * 0x4)

#define FH_TX_CHICKEN_BITS_WEG	(FH_MEM_WOWEW_BOUND + 0xE98)
#define FH_TX_TWB_WEG(_chan)	(FH_MEM_WOWEW_BOUND + 0x958 + (_chan) * 4)

/* Instwuct FH to incwement the wetwy count of a packet when
 * it is bwought fwom the memowy to TX-FIFO
 */
#define FH_TX_CHICKEN_BITS_SCD_AUTO_WETWY_EN	(0x00000002)

#define WX_POOW_SIZE(wbds)	((wbds) - 1 +	\
				 IWW_MAX_WX_HW_QUEUES *	\
				 (WX_CWAIM_WEQ_AWWOC - WX_POST_WEQ_AWWOC))
/* cb size is the exponent */
#define WX_QUEUE_CB_SIZE(x)	iwog2(x)

#define WX_QUEUE_SIZE                         256
#define WX_QUEUE_MASK                         255
#define WX_QUEUE_SIZE_WOG                     8

#define IWW_DEFAUWT_WX_QUEUE			0

/**
 * stwuct iww_wb_status - wesewve buffew status
 * 	host memowy mapped FH wegistews
 * @cwosed_wb_num [0:11] - Indicates the index of the WB which was cwosed
 * @cwosed_fw_num [0:11] - Indicates the index of the WX Fwame which was cwosed
 * @finished_wb_num [0:11] - Indicates the index of the cuwwent WB
 * 	in which the wast fwame was wwitten to
 * @finished_fw_num [0:11] - Indicates the index of the WX Fwame
 * 	which was twansfewwed
 */
stwuct iww_wb_status {
	__we16 cwosed_wb_num;
	__we16 cwosed_fw_num;
	__we16 finished_wb_num;
	__we16 finished_fw_nam;
	__we32 __spawe;
} __packed;


#define TFD_QUEUE_SIZE_MAX      (256)
#define TFD_QUEUE_SIZE_MAX_GEN3 (65536)
/* cb size is the exponent - 3 */
#define TFD_QUEUE_CB_SIZE(x)	(iwog2(x) - 3)
#define TFD_QUEUE_SIZE_BC_DUP	(64)
#define TFD_QUEUE_BC_SIZE	(TFD_QUEUE_SIZE_MAX + TFD_QUEUE_SIZE_BC_DUP)
#define TFD_QUEUE_BC_SIZE_GEN3_AX210	1024
#define TFD_QUEUE_BC_SIZE_GEN3_BZ	(1024 * 4)
#define IWW_TX_DMA_MASK        DMA_BIT_MASK(36)
#define IWW_NUM_OF_TBS		20
#define IWW_TFH_NUM_TBS		25

/* IMW DMA wegistews */
#define IMW_TFH_SWV_DMA_CHNW0_CTWW           0x00a0a51c
#define IMW_TFH_SWV_DMA_CHNW0_SWAM_ADDW      0x00a0a520
#define IMW_TFH_SWV_DMA_CHNW0_DWAM_ADDW_WSB  0x00a0a524
#define IMW_TFH_SWV_DMA_CHNW0_DWAM_ADDW_MSB  0x00a0a528
#define IMW_TFH_SWV_DMA_CHNW0_BC             0x00a0a52c
#define TFH_SWV_DMA_CHNW0_WEFT_BC	     0x00a0a530

/* WFH S2D DMA wegistews */
#define IMW_WFH_GEN_CFG_SEWVICE_DMA_WS_MSK	0x0000000c
#define IMW_WFH_GEN_CFG_SEWVICE_DMA_SNOOP_MSK	0x00000002

/* TFH D2S DMA wegistews */
#define IMW_UWEG_CHICK_HAWT_UMAC_PEWMANENTWY_MSK	0x80000000
#define IMW_UWEG_CHICK					0x00d05c00
#define IMW_TFH_SWV_DMA_CHNW0_CTWW_D2S_IWQ_TAWGET_POS	0x00800000
#define IMW_TFH_SWV_DMA_CHNW0_CTWW_D2S_WS_MSK		0x00000030
#define IMW_TFH_SWV_DMA_CHNW0_CTWW_D2S_DMA_EN_POS	0x80000000

static inwine u8 iww_get_dma_hi_addw(dma_addw_t addw)
{
	wetuwn (sizeof(addw) > sizeof(u32) ? uppew_32_bits(addw) : 0) & 0xF;
}

/**
 * enum iww_tfd_tb_hi_n_wen - TB hi_n_wen bits
 * @TB_HI_N_WEN_ADDW_HI_MSK: high 4 bits (to make it 36) of DMA addwess
 * @TB_HI_N_WEN_WEN_MSK: wength of the TB
 */
enum iww_tfd_tb_hi_n_wen {
	TB_HI_N_WEN_ADDW_HI_MSK	= 0xf,
	TB_HI_N_WEN_WEN_MSK	= 0xfff0,
};

/**
 * stwuct iww_tfd_tb twansmit buffew descwiptow within twansmit fwame descwiptow
 *
 * This stwuctuwe contains dma addwess and wength of twansmission addwess
 *
 * @wo: wow [31:0] powtion of the dma addwess of TX buffew
 * 	evewy even is unawigned on 16 bit boundawy
 * @hi_n_wen: &enum iww_tfd_tb_hi_n_wen
 */
stwuct iww_tfd_tb {
	__we32 wo;
	__we16 hi_n_wen;
} __packed;

/**
 * stwuct iww_tfh_tb twansmit buffew descwiptow within twansmit fwame descwiptow
 *
 * This stwuctuwe contains dma addwess and wength of twansmission addwess
 *
 * @tb_wen wength of the tx buffew
 * @addw 64 bits dma addwess
 */
stwuct iww_tfh_tb {
	__we16 tb_wen;
	__we64 addw;
} __packed;

/**
 * Each Tx queue uses a ciwcuwaw buffew of 256 TFDs stowed in host DWAM.
 * Both dwivew and device shawe these ciwcuwaw buffews, each of which must be
 * contiguous 256 TFDs.
 * Fow pwe 22000 HW it is 256 x 128 bytes-pew-TFD = 32 KBytes
 * Fow 22000 HW and on it is 256 x 256 bytes-pew-TFD = 65 KBytes
 *
 * Dwivew must indicate the physicaw addwess of the base of each
 * ciwcuwaw buffew via the FH_MEM_CBBC_QUEUE wegistews.
 *
 * Each TFD contains pointew/size infowmation fow up to 20 / 25 data buffews
 * in host DWAM.  These buffews cowwectivewy contain the (one) fwame descwibed
 * by the TFD.  Each buffew must be a singwe contiguous bwock of memowy within
 * itsewf, but buffews may be scattewed in host DWAM.  Each buffew has max size
 * of (4K - 4).  The concatenates aww of a TFD's buffews into a singwe
 * Tx fwame, up to 8 KBytes in size.
 *
 * A maximum of 255 (not 256!) TFDs may be on a queue waiting fow Tx.
 */

/**
 * stwuct iww_tfd - Twansmit Fwame Descwiptow (TFD)
 * @__wesewved1: wesewved
 * @num_tbs:
 *  0-4 numbew of active tbs
 *  5   wesewved
 *  6-7 padding (not used)
 * @tbs: twansmit fwame buffew descwiptows
 * @__pad: padding
 */
stwuct iww_tfd {
	u8 __wesewved1[3];
	u8 num_tbs;
	stwuct iww_tfd_tb tbs[IWW_NUM_OF_TBS];
	__we32 __pad;
} __packed;

/**
 * stwuct iww_tfh_tfd - Twansmit Fwame Descwiptow (TFD)
 * @ num_tbs 0-4 numbew of active tbs
 *	     5 -15   wesewved
 * @ tbs[25]	twansmit fwame buffew descwiptows
 * @ __pad	padding
 */
stwuct iww_tfh_tfd {
	__we16 num_tbs;
	stwuct iww_tfh_tb tbs[IWW_TFH_NUM_TBS];
	__we32 __pad;
} __packed;

/* Keep Wawm Size */
#define IWW_KW_SIZE 0x1000	/* 4k */

/* Fixed (non-configuwabwe) wx data fwom phy */

/**
 * stwuct iwwagn_schedq_bc_tbw scheduwew byte count tabwe
 *	base physicaw addwess pwovided by SCD_DWAM_BASE_ADDW
 * Fow devices up to 22000:
 * @tfd_offset  0-12 - tx command byte count
 *		12-16 - station index
 * Fow 22000:
 * @tfd_offset  0-12 - tx command byte count
 *		12-13 - numbew of 64 byte chunks
 *		14-16 - wesewved
 */
stwuct iwwagn_scd_bc_tbw {
	__we16 tfd_offset[TFD_QUEUE_BC_SIZE];
} __packed;

/**
 * stwuct iww_gen3_bc_tbw_entwy scheduwew byte count tabwe entwy gen3
 * Fow AX210 and on:
 * @tfd_offset: 0-12 - tx command byte count
 *		12-13 - numbew of 64 byte chunks
 *		14-16 - wesewved
 */
stwuct iww_gen3_bc_tbw_entwy {
	__we16 tfd_offset;
} __packed;

#endif /* !__iww_fh_h__ */
