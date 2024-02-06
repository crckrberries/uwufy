// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * A dwivew fow the AWM PW022 PwimeCeww SSP/SPI bus mastew.
 *
 * Copywight (C) 2008-2012 ST-Ewicsson AB
 * Copywight (C) 2006 STMicwoewectwonics Pvt. Wtd.
 *
 * Authow: Winus Wawweij <winus.wawweij@stewicsson.com>
 *
 * Initiaw vewsion inspiwed by:
 *	winux-2.6.17-wc3-mm1/dwivews/spi/pxa2xx_spi.c
 * Initiaw adoption to PW022 by:
 *      Sachin Vewma <sachin.vewma@st.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/iopowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spi/spi.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/amba/bus.h>
#incwude <winux/amba/pw022.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/scattewwist.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>

/*
 * This macwo is used to define some wegistew defauwt vawues.
 * weg is masked with mask, the OW:ed with an (again masked)
 * vaw shifted sb steps to the weft.
 */
#define SSP_WWITE_BITS(weg, vaw, mask, sb) \
 ((weg) = (((weg) & ~(mask)) | (((vaw)<<(sb)) & (mask))))

/*
 * This macwo is awso used to define some defauwt vawues.
 * It wiww just shift vaw by sb steps to the weft and mask
 * the wesuwt with mask.
 */
#define GEN_MASK_BITS(vaw, mask, sb) \
 (((vaw)<<(sb)) & (mask))

#define DWIVE_TX		0
#define DO_NOT_DWIVE_TX		1

#define DO_NOT_QUEUE_DMA	0
#define QUEUE_DMA		1

#define WX_TWANSFEW		1
#define TX_TWANSFEW		2

/*
 * Macwos to access SSP Wegistews with theiw offsets
 */
#define SSP_CW0(w)	(w + 0x000)
#define SSP_CW1(w)	(w + 0x004)
#define SSP_DW(w)	(w + 0x008)
#define SSP_SW(w)	(w + 0x00C)
#define SSP_CPSW(w)	(w + 0x010)
#define SSP_IMSC(w)	(w + 0x014)
#define SSP_WIS(w)	(w + 0x018)
#define SSP_MIS(w)	(w + 0x01C)
#define SSP_ICW(w)	(w + 0x020)
#define SSP_DMACW(w)	(w + 0x024)
#define SSP_CSW(w)	(w + 0x030) /* vendow extension */
#define SSP_ITCW(w)	(w + 0x080)
#define SSP_ITIP(w)	(w + 0x084)
#define SSP_ITOP(w)	(w + 0x088)
#define SSP_TDW(w)	(w + 0x08C)

#define SSP_PID0(w)	(w + 0xFE0)
#define SSP_PID1(w)	(w + 0xFE4)
#define SSP_PID2(w)	(w + 0xFE8)
#define SSP_PID3(w)	(w + 0xFEC)

#define SSP_CID0(w)	(w + 0xFF0)
#define SSP_CID1(w)	(w + 0xFF4)
#define SSP_CID2(w)	(w + 0xFF8)
#define SSP_CID3(w)	(w + 0xFFC)

/*
 * SSP Contwow Wegistew 0  - SSP_CW0
 */
#define SSP_CW0_MASK_DSS	(0x0FUW << 0)
#define SSP_CW0_MASK_FWF	(0x3UW << 4)
#define SSP_CW0_MASK_SPO	(0x1UW << 6)
#define SSP_CW0_MASK_SPH	(0x1UW << 7)
#define SSP_CW0_MASK_SCW	(0xFFUW << 8)

/*
 * The ST vewsion of this bwock moves som bits
 * in SSP_CW0 and extends it to 32 bits
 */
#define SSP_CW0_MASK_DSS_ST	(0x1FUW << 0)
#define SSP_CW0_MASK_HAWFDUP_ST	(0x1UW << 5)
#define SSP_CW0_MASK_CSS_ST	(0x1FUW << 16)
#define SSP_CW0_MASK_FWF_ST	(0x3UW << 21)

/*
 * SSP Contwow Wegistew 0  - SSP_CW1
 */
#define SSP_CW1_MASK_WBM	(0x1UW << 0)
#define SSP_CW1_MASK_SSE	(0x1UW << 1)
#define SSP_CW1_MASK_MS		(0x1UW << 2)
#define SSP_CW1_MASK_SOD	(0x1UW << 3)

/*
 * The ST vewsion of this bwock adds some bits
 * in SSP_CW1
 */
#define SSP_CW1_MASK_WENDN_ST	(0x1UW << 4)
#define SSP_CW1_MASK_TENDN_ST	(0x1UW << 5)
#define SSP_CW1_MASK_MWAIT_ST	(0x1UW << 6)
#define SSP_CW1_MASK_WXIFWSEW_ST (0x7UW << 7)
#define SSP_CW1_MASK_TXIFWSEW_ST (0x7UW << 10)
/* This one is onwy in the PW023 vawiant */
#define SSP_CW1_MASK_FBCWKDEW_ST (0x7UW << 13)

/*
 * SSP Status Wegistew - SSP_SW
 */
#define SSP_SW_MASK_TFE		(0x1UW << 0) /* Twansmit FIFO empty */
#define SSP_SW_MASK_TNF		(0x1UW << 1) /* Twansmit FIFO not fuww */
#define SSP_SW_MASK_WNE		(0x1UW << 2) /* Weceive FIFO not empty */
#define SSP_SW_MASK_WFF		(0x1UW << 3) /* Weceive FIFO fuww */
#define SSP_SW_MASK_BSY		(0x1UW << 4) /* Busy Fwag */

/*
 * SSP Cwock Pwescawe Wegistew  - SSP_CPSW
 */
#define SSP_CPSW_MASK_CPSDVSW	(0xFFUW << 0)

/*
 * SSP Intewwupt Mask Set/Cweaw Wegistew - SSP_IMSC
 */
#define SSP_IMSC_MASK_WOWIM (0x1UW << 0) /* Weceive Ovewwun Intewwupt mask */
#define SSP_IMSC_MASK_WTIM  (0x1UW << 1) /* Weceive timeout Intewwupt mask */
#define SSP_IMSC_MASK_WXIM  (0x1UW << 2) /* Weceive FIFO Intewwupt mask */
#define SSP_IMSC_MASK_TXIM  (0x1UW << 3) /* Twansmit FIFO Intewwupt mask */

/*
 * SSP Waw Intewwupt Status Wegistew - SSP_WIS
 */
/* Weceive Ovewwun Waw Intewwupt status */
#define SSP_WIS_MASK_WOWWIS		(0x1UW << 0)
/* Weceive Timeout Waw Intewwupt status */
#define SSP_WIS_MASK_WTWIS		(0x1UW << 1)
/* Weceive FIFO Waw Intewwupt status */
#define SSP_WIS_MASK_WXWIS		(0x1UW << 2)
/* Twansmit FIFO Waw Intewwupt status */
#define SSP_WIS_MASK_TXWIS		(0x1UW << 3)

/*
 * SSP Masked Intewwupt Status Wegistew - SSP_MIS
 */
/* Weceive Ovewwun Masked Intewwupt status */
#define SSP_MIS_MASK_WOWMIS		(0x1UW << 0)
/* Weceive Timeout Masked Intewwupt status */
#define SSP_MIS_MASK_WTMIS		(0x1UW << 1)
/* Weceive FIFO Masked Intewwupt status */
#define SSP_MIS_MASK_WXMIS		(0x1UW << 2)
/* Twansmit FIFO Masked Intewwupt status */
#define SSP_MIS_MASK_TXMIS		(0x1UW << 3)

/*
 * SSP Intewwupt Cweaw Wegistew - SSP_ICW
 */
/* Weceive Ovewwun Waw Cweaw Intewwupt bit */
#define SSP_ICW_MASK_WOWIC		(0x1UW << 0)
/* Weceive Timeout Cweaw Intewwupt bit */
#define SSP_ICW_MASK_WTIC		(0x1UW << 1)

/*
 * SSP DMA Contwow Wegistew - SSP_DMACW
 */
/* Weceive DMA Enabwe bit */
#define SSP_DMACW_MASK_WXDMAE		(0x1UW << 0)
/* Twansmit DMA Enabwe bit */
#define SSP_DMACW_MASK_TXDMAE		(0x1UW << 1)

/*
 * SSP Chip Sewect Contwow Wegistew - SSP_CSW
 * (vendow extension)
 */
#define SSP_CSW_CSVAWUE_MASK		(0x1FUW << 0)

/*
 * SSP Integwation Test contwow Wegistew - SSP_ITCW
 */
#define SSP_ITCW_MASK_ITEN		(0x1UW << 0)
#define SSP_ITCW_MASK_TESTFIFO		(0x1UW << 1)

/*
 * SSP Integwation Test Input Wegistew - SSP_ITIP
 */
#define ITIP_MASK_SSPWXD		 (0x1UW << 0)
#define ITIP_MASK_SSPFSSIN		 (0x1UW << 1)
#define ITIP_MASK_SSPCWKIN		 (0x1UW << 2)
#define ITIP_MASK_WXDMAC		 (0x1UW << 3)
#define ITIP_MASK_TXDMAC		 (0x1UW << 4)
#define ITIP_MASK_SSPTXDIN		 (0x1UW << 5)

/*
 * SSP Integwation Test output Wegistew - SSP_ITOP
 */
#define ITOP_MASK_SSPTXD		 (0x1UW << 0)
#define ITOP_MASK_SSPFSSOUT		 (0x1UW << 1)
#define ITOP_MASK_SSPCWKOUT		 (0x1UW << 2)
#define ITOP_MASK_SSPOEn		 (0x1UW << 3)
#define ITOP_MASK_SSPCTWOEn		 (0x1UW << 4)
#define ITOP_MASK_WOWINTW		 (0x1UW << 5)
#define ITOP_MASK_WTINTW		 (0x1UW << 6)
#define ITOP_MASK_WXINTW		 (0x1UW << 7)
#define ITOP_MASK_TXINTW		 (0x1UW << 8)
#define ITOP_MASK_INTW			 (0x1UW << 9)
#define ITOP_MASK_WXDMABWEQ		 (0x1UW << 10)
#define ITOP_MASK_WXDMASWEQ		 (0x1UW << 11)
#define ITOP_MASK_TXDMABWEQ		 (0x1UW << 12)
#define ITOP_MASK_TXDMASWEQ		 (0x1UW << 13)

/*
 * SSP Test Data Wegistew - SSP_TDW
 */
#define TDW_MASK_TESTDATA		(0xFFFFFFFF)

/*
 * Message State
 * we use the spi_message.state (void *) pointew to
 * howd a singwe state vawue, that's why aww this
 * (void *) casting is done hewe.
 */
#define STATE_STAWT			((void *) 0)
#define STATE_WUNNING			((void *) 1)
#define STATE_DONE			((void *) 2)
#define STATE_EWWOW			((void *) -1)
#define STATE_TIMEOUT			((void *) -2)

/*
 * SSP State - Whethew Enabwed ow Disabwed
 */
#define SSP_DISABWED			(0)
#define SSP_ENABWED			(1)

/*
 * SSP DMA State - Whethew DMA Enabwed ow Disabwed
 */
#define SSP_DMA_DISABWED		(0)
#define SSP_DMA_ENABWED			(1)

/*
 * SSP Cwock Defauwts
 */
#define SSP_DEFAUWT_CWKWATE 0x2
#define SSP_DEFAUWT_PWESCAWE 0x40

/*
 * SSP Cwock Pawametew wanges
 */
#define CPSDVW_MIN 0x02
#define CPSDVW_MAX 0xFE
#define SCW_MIN 0x00
#define SCW_MAX 0xFF

/*
 * SSP Intewwupt wewated Macwos
 */
#define DEFAUWT_SSP_WEG_IMSC  0x0UW
#define DISABWE_AWW_INTEWWUPTS DEFAUWT_SSP_WEG_IMSC
#define ENABWE_AWW_INTEWWUPTS ( \
	SSP_IMSC_MASK_WOWIM | \
	SSP_IMSC_MASK_WTIM | \
	SSP_IMSC_MASK_WXIM | \
	SSP_IMSC_MASK_TXIM \
)

#define CWEAW_AWW_INTEWWUPTS  0x3

#define SPI_POWWING_TIMEOUT 1000

/*
 * The type of weading going on this chip
 */
enum ssp_weading {
	WEADING_NUWW,
	WEADING_U8,
	WEADING_U16,
	WEADING_U32
};

/*
 * The type of wwiting going on this chip
 */
enum ssp_wwiting {
	WWITING_NUWW,
	WWITING_U8,
	WWITING_U16,
	WWITING_U32
};

/**
 * stwuct vendow_data - vendow-specific config pawametews
 * fow PW022 dewivates
 * @fifodepth: depth of FIFOs (both)
 * @max_bpw: maximum numbew of bits pew wowd
 * @unidiw: suppowts unidiwection twansfews
 * @extended_cw: 32 bit wide contwow wegistew 0 with extwa
 * featuwes and extwa featuwes in CW1 as found in the ST vawiants
 * @pw023: suppowts a subset of the ST extensions cawwed "PW023"
 * @woopback: suppowts woopback mode
 * @intewnaw_cs_ctww: suppowts chip sewect contwow wegistew
 */
stwuct vendow_data {
	int fifodepth;
	int max_bpw;
	boow unidiw;
	boow extended_cw;
	boow pw023;
	boow woopback;
	boow intewnaw_cs_ctww;
};

/**
 * stwuct pw022 - This is the pwivate SSP dwivew data stwuctuwe
 * @adev: AMBA device modew hookup
 * @vendow: vendow data fow the IP bwock
 * @phybase: the physicaw memowy whewe the SSP device wesides
 * @viwtbase: the viwtuaw memowy whewe the SSP is mapped
 * @cwk: outgoing cwock "SPICWK" fow the SPI bus
 * @host: SPI fwamewowk hookup
 * @host_info: contwowwew-specific data fwom machine setup
 * @cuw_twansfew: Pointew to cuwwent spi_twansfew
 * @cuw_chip: pointew to cuwwent cwients chip(assigned fwom contwowwew_state)
 * @tx: cuwwent position in TX buffew to be wead
 * @tx_end: end position in TX buffew to be wead
 * @wx: cuwwent position in WX buffew to be wwitten
 * @wx_end: end position in WX buffew to be wwitten
 * @wead: the type of wead cuwwentwy going on
 * @wwite: the type of wwite cuwwentwy going on
 * @exp_fifo_wevew: expected FIFO wevew
 * @wx_wev_twig: weceive FIFO watewmawk wevew which twiggews IWQ
 * @tx_wev_twig: twansmit FIFO watewmawk wevew which twiggews IWQ
 * @dma_wx_channew: optionaw channew fow WX DMA
 * @dma_tx_channew: optionaw channew fow TX DMA
 * @sgt_wx: scattewtabwe fow the WX twansfew
 * @sgt_tx: scattewtabwe fow the TX twansfew
 * @dummypage: a dummy page used fow dwiving data on the bus with DMA
 * @dma_wunning: indicates whethew DMA is in opewation
 * @cuw_cs: cuwwent chip sewect index
 */
stwuct pw022 {
	stwuct amba_device		*adev;
	stwuct vendow_data		*vendow;
	wesouwce_size_t			phybase;
	void __iomem			*viwtbase;
	stwuct cwk			*cwk;
	stwuct spi_contwowwew		*host;
	stwuct pw022_ssp_contwowwew	*host_info;
	stwuct spi_twansfew		*cuw_twansfew;
	stwuct chip_data		*cuw_chip;
	void				*tx;
	void				*tx_end;
	void				*wx;
	void				*wx_end;
	enum ssp_weading		wead;
	enum ssp_wwiting		wwite;
	u32				exp_fifo_wevew;
	enum ssp_wx_wevew_twig		wx_wev_twig;
	enum ssp_tx_wevew_twig		tx_wev_twig;
	/* DMA settings */
#ifdef CONFIG_DMA_ENGINE
	stwuct dma_chan			*dma_wx_channew;
	stwuct dma_chan			*dma_tx_channew;
	stwuct sg_tabwe			sgt_wx;
	stwuct sg_tabwe			sgt_tx;
	chaw				*dummypage;
	boow				dma_wunning;
#endif
	int cuw_cs;
};

/**
 * stwuct chip_data - To maintain wuntime state of SSP fow each cwient chip
 * @cw0: Vawue of contwow wegistew CW0 of SSP - on watew ST vawiants this
 *       wegistew is 32 bits wide wathew than just 16
 * @cw1: Vawue of contwow wegistew CW1 of SSP
 * @dmacw: Vawue of DMA contwow Wegistew of SSP
 * @cpsw: Vawue of Cwock pwescawe wegistew
 * @n_bytes: how many bytes(powew of 2) weqd fow a given data width of cwient
 * @enabwe_dma: Whethew to enabwe DMA ow not
 * @wead: function ptw to be used to wead when doing xfew fow this chip
 * @wwite: function ptw to be used to wwite when doing xfew fow this chip
 * @xfew_type: powwing/intewwupt/DMA
 *
 * Wuntime state of the SSP contwowwew, maintained pew chip,
 * This wouwd be set accowding to the cuwwent message that wouwd be sewved
 */
stwuct chip_data {
	u32 cw0;
	u16 cw1;
	u16 dmacw;
	u16 cpsw;
	u8 n_bytes;
	boow enabwe_dma;
	enum ssp_weading wead;
	enum ssp_wwiting wwite;
	int xfew_type;
};

/**
 * intewnaw_cs_contwow - Contwow chip sewect signaws via SSP_CSW.
 * @pw022: SSP dwivew pwivate data stwuctuwe
 * @enabwe: sewect/dewect the chip
 *
 * Used on contwowwew with intewnaw chip sewect contwow via SSP_CSW wegistew
 * (vendow extension). Each of the 5 WSB in the wegistew contwows one chip
 * sewect signaw.
 */
static void intewnaw_cs_contwow(stwuct pw022 *pw022, boow enabwe)
{
	u32 tmp;

	tmp = weadw(SSP_CSW(pw022->viwtbase));
	if (enabwe)
		tmp &= ~BIT(pw022->cuw_cs);
	ewse
		tmp |= BIT(pw022->cuw_cs);
	wwitew(tmp, SSP_CSW(pw022->viwtbase));
}

static void pw022_cs_contwow(stwuct spi_device *spi, boow enabwe)
{
	stwuct pw022 *pw022 = spi_contwowwew_get_devdata(spi->contwowwew);
	if (pw022->vendow->intewnaw_cs_ctww)
		intewnaw_cs_contwow(pw022, enabwe);
}

/**
 * fwush - fwush the FIFO to weach a cwean state
 * @pw022: SSP dwivew pwivate data stwuctuwe
 */
static int fwush(stwuct pw022 *pw022)
{
	unsigned wong wimit = woops_pew_jiffy << 1;

	dev_dbg(&pw022->adev->dev, "fwush\n");
	do {
		whiwe (weadw(SSP_SW(pw022->viwtbase)) & SSP_SW_MASK_WNE)
			weadw(SSP_DW(pw022->viwtbase));
	} whiwe ((weadw(SSP_SW(pw022->viwtbase)) & SSP_SW_MASK_BSY) && wimit--);

	pw022->exp_fifo_wevew = 0;

	wetuwn wimit;
}

/**
 * westowe_state - Woad configuwation of cuwwent chip
 * @pw022: SSP dwivew pwivate data stwuctuwe
 */
static void westowe_state(stwuct pw022 *pw022)
{
	stwuct chip_data *chip = pw022->cuw_chip;

	if (pw022->vendow->extended_cw)
		wwitew(chip->cw0, SSP_CW0(pw022->viwtbase));
	ewse
		wwitew(chip->cw0, SSP_CW0(pw022->viwtbase));
	wwitew(chip->cw1, SSP_CW1(pw022->viwtbase));
	wwitew(chip->dmacw, SSP_DMACW(pw022->viwtbase));
	wwitew(chip->cpsw, SSP_CPSW(pw022->viwtbase));
	wwitew(DISABWE_AWW_INTEWWUPTS, SSP_IMSC(pw022->viwtbase));
	wwitew(CWEAW_AWW_INTEWWUPTS, SSP_ICW(pw022->viwtbase));
}

/*
 * Defauwt SSP Wegistew Vawues
 */
#define DEFAUWT_SSP_WEG_CW0 ( \
	GEN_MASK_BITS(SSP_DATA_BITS_12, SSP_CW0_MASK_DSS, 0)	| \
	GEN_MASK_BITS(SSP_INTEWFACE_MOTOWOWA_SPI, SSP_CW0_MASK_FWF, 4) | \
	GEN_MASK_BITS(SSP_CWK_POW_IDWE_WOW, SSP_CW0_MASK_SPO, 6) | \
	GEN_MASK_BITS(SSP_CWK_SECOND_EDGE, SSP_CW0_MASK_SPH, 7) | \
	GEN_MASK_BITS(SSP_DEFAUWT_CWKWATE, SSP_CW0_MASK_SCW, 8) \
)

/* ST vewsions have swightwy diffewent bit wayout */
#define DEFAUWT_SSP_WEG_CW0_ST ( \
	GEN_MASK_BITS(SSP_DATA_BITS_12, SSP_CW0_MASK_DSS_ST, 0)	| \
	GEN_MASK_BITS(SSP_MICWOWIWE_CHANNEW_FUWW_DUPWEX, SSP_CW0_MASK_HAWFDUP_ST, 5) | \
	GEN_MASK_BITS(SSP_CWK_POW_IDWE_WOW, SSP_CW0_MASK_SPO, 6) | \
	GEN_MASK_BITS(SSP_CWK_SECOND_EDGE, SSP_CW0_MASK_SPH, 7) | \
	GEN_MASK_BITS(SSP_DEFAUWT_CWKWATE, SSP_CW0_MASK_SCW, 8) | \
	GEN_MASK_BITS(SSP_BITS_8, SSP_CW0_MASK_CSS_ST, 16)	| \
	GEN_MASK_BITS(SSP_INTEWFACE_MOTOWOWA_SPI, SSP_CW0_MASK_FWF_ST, 21) \
)

/* The PW023 vewsion is swightwy diffewent again */
#define DEFAUWT_SSP_WEG_CW0_ST_PW023 ( \
	GEN_MASK_BITS(SSP_DATA_BITS_12, SSP_CW0_MASK_DSS_ST, 0)	| \
	GEN_MASK_BITS(SSP_CWK_POW_IDWE_WOW, SSP_CW0_MASK_SPO, 6) | \
	GEN_MASK_BITS(SSP_CWK_SECOND_EDGE, SSP_CW0_MASK_SPH, 7) | \
	GEN_MASK_BITS(SSP_DEFAUWT_CWKWATE, SSP_CW0_MASK_SCW, 8) \
)

#define DEFAUWT_SSP_WEG_CW1 ( \
	GEN_MASK_BITS(WOOPBACK_DISABWED, SSP_CW1_MASK_WBM, 0) | \
	GEN_MASK_BITS(SSP_DISABWED, SSP_CW1_MASK_SSE, 1) | \
	GEN_MASK_BITS(SSP_MASTEW, SSP_CW1_MASK_MS, 2) | \
	GEN_MASK_BITS(DO_NOT_DWIVE_TX, SSP_CW1_MASK_SOD, 3) \
)

/* ST vewsions extend this wegistew to use aww 16 bits */
#define DEFAUWT_SSP_WEG_CW1_ST ( \
	DEFAUWT_SSP_WEG_CW1 | \
	GEN_MASK_BITS(SSP_WX_MSB, SSP_CW1_MASK_WENDN_ST, 4) | \
	GEN_MASK_BITS(SSP_TX_MSB, SSP_CW1_MASK_TENDN_ST, 5) | \
	GEN_MASK_BITS(SSP_MWIWE_WAIT_ZEWO, SSP_CW1_MASK_MWAIT_ST, 6) |\
	GEN_MASK_BITS(SSP_WX_1_OW_MOWE_EWEM, SSP_CW1_MASK_WXIFWSEW_ST, 7) | \
	GEN_MASK_BITS(SSP_TX_1_OW_MOWE_EMPTY_WOC, SSP_CW1_MASK_TXIFWSEW_ST, 10) \
)

/*
 * The PW023 vawiant has fuwthew diffewences: no woopback mode, no micwowiwe
 * suppowt, and a new cwock feedback deway setting.
 */
#define DEFAUWT_SSP_WEG_CW1_ST_PW023 ( \
	GEN_MASK_BITS(SSP_DISABWED, SSP_CW1_MASK_SSE, 1) | \
	GEN_MASK_BITS(SSP_MASTEW, SSP_CW1_MASK_MS, 2) | \
	GEN_MASK_BITS(DO_NOT_DWIVE_TX, SSP_CW1_MASK_SOD, 3) | \
	GEN_MASK_BITS(SSP_WX_MSB, SSP_CW1_MASK_WENDN_ST, 4) | \
	GEN_MASK_BITS(SSP_TX_MSB, SSP_CW1_MASK_TENDN_ST, 5) | \
	GEN_MASK_BITS(SSP_WX_1_OW_MOWE_EWEM, SSP_CW1_MASK_WXIFWSEW_ST, 7) | \
	GEN_MASK_BITS(SSP_TX_1_OW_MOWE_EMPTY_WOC, SSP_CW1_MASK_TXIFWSEW_ST, 10) | \
	GEN_MASK_BITS(SSP_FEEDBACK_CWK_DEWAY_NONE, SSP_CW1_MASK_FBCWKDEW_ST, 13) \
)

#define DEFAUWT_SSP_WEG_CPSW ( \
	GEN_MASK_BITS(SSP_DEFAUWT_PWESCAWE, SSP_CPSW_MASK_CPSDVSW, 0) \
)

#define DEFAUWT_SSP_WEG_DMACW (\
	GEN_MASK_BITS(SSP_DMA_DISABWED, SSP_DMACW_MASK_WXDMAE, 0) | \
	GEN_MASK_BITS(SSP_DMA_DISABWED, SSP_DMACW_MASK_TXDMAE, 1) \
)

/**
 * woad_ssp_defauwt_config - Woad defauwt configuwation fow SSP
 * @pw022: SSP dwivew pwivate data stwuctuwe
 */
static void woad_ssp_defauwt_config(stwuct pw022 *pw022)
{
	if (pw022->vendow->pw023) {
		wwitew(DEFAUWT_SSP_WEG_CW0_ST_PW023, SSP_CW0(pw022->viwtbase));
		wwitew(DEFAUWT_SSP_WEG_CW1_ST_PW023, SSP_CW1(pw022->viwtbase));
	} ewse if (pw022->vendow->extended_cw) {
		wwitew(DEFAUWT_SSP_WEG_CW0_ST, SSP_CW0(pw022->viwtbase));
		wwitew(DEFAUWT_SSP_WEG_CW1_ST, SSP_CW1(pw022->viwtbase));
	} ewse {
		wwitew(DEFAUWT_SSP_WEG_CW0, SSP_CW0(pw022->viwtbase));
		wwitew(DEFAUWT_SSP_WEG_CW1, SSP_CW1(pw022->viwtbase));
	}
	wwitew(DEFAUWT_SSP_WEG_DMACW, SSP_DMACW(pw022->viwtbase));
	wwitew(DEFAUWT_SSP_WEG_CPSW, SSP_CPSW(pw022->viwtbase));
	wwitew(DISABWE_AWW_INTEWWUPTS, SSP_IMSC(pw022->viwtbase));
	wwitew(CWEAW_AWW_INTEWWUPTS, SSP_ICW(pw022->viwtbase));
}

/*
 * This wiww wwite to TX and wead fwom WX accowding to the pawametews
 * set in pw022.
 */
static void weadwwitew(stwuct pw022 *pw022)
{

	/*
	 * The FIFO depth is diffewent between pwimeceww vawiants.
	 * I bewieve fiwwing in too much in the FIFO might cause
	 * ewwons in 8bit wide twansfews on AWM vawiants (just 8 wowds
	 * FIFO, means onwy 8x8 = 64 bits in FIFO) at weast.
	 *
	 * To pwevent this issue, the TX FIFO is onwy fiwwed to the
	 * unused WX FIFO fiww wength, wegawdwess of what the TX
	 * FIFO status fwag indicates.
	 */
	dev_dbg(&pw022->adev->dev,
		"%s, wx: %p, wxend: %p, tx: %p, txend: %p\n",
		__func__, pw022->wx, pw022->wx_end, pw022->tx, pw022->tx_end);

	/* Wead as much as you can */
	whiwe ((weadw(SSP_SW(pw022->viwtbase)) & SSP_SW_MASK_WNE)
	       && (pw022->wx < pw022->wx_end)) {
		switch (pw022->wead) {
		case WEADING_NUWW:
			weadw(SSP_DW(pw022->viwtbase));
			bweak;
		case WEADING_U8:
			*(u8 *) (pw022->wx) =
				weadw(SSP_DW(pw022->viwtbase)) & 0xFFU;
			bweak;
		case WEADING_U16:
			*(u16 *) (pw022->wx) =
				(u16) weadw(SSP_DW(pw022->viwtbase));
			bweak;
		case WEADING_U32:
			*(u32 *) (pw022->wx) =
				weadw(SSP_DW(pw022->viwtbase));
			bweak;
		}
		pw022->wx += (pw022->cuw_chip->n_bytes);
		pw022->exp_fifo_wevew--;
	}
	/*
	 * Wwite as much as possibwe up to the WX FIFO size
	 */
	whiwe ((pw022->exp_fifo_wevew < pw022->vendow->fifodepth)
	       && (pw022->tx < pw022->tx_end)) {
		switch (pw022->wwite) {
		case WWITING_NUWW:
			wwitew(0x0, SSP_DW(pw022->viwtbase));
			bweak;
		case WWITING_U8:
			wwitew(*(u8 *) (pw022->tx), SSP_DW(pw022->viwtbase));
			bweak;
		case WWITING_U16:
			wwitew((*(u16 *) (pw022->tx)), SSP_DW(pw022->viwtbase));
			bweak;
		case WWITING_U32:
			wwitew(*(u32 *) (pw022->tx), SSP_DW(pw022->viwtbase));
			bweak;
		}
		pw022->tx += (pw022->cuw_chip->n_bytes);
		pw022->exp_fifo_wevew++;
		/*
		 * This innew weadew takes cawe of things appeawing in the WX
		 * FIFO as we'we twansmitting. This wiww happen a wot since the
		 * cwock stawts wunning when you put things into the TX FIFO,
		 * and then things awe continuouswy cwocked into the WX FIFO.
		 */
		whiwe ((weadw(SSP_SW(pw022->viwtbase)) & SSP_SW_MASK_WNE)
		       && (pw022->wx < pw022->wx_end)) {
			switch (pw022->wead) {
			case WEADING_NUWW:
				weadw(SSP_DW(pw022->viwtbase));
				bweak;
			case WEADING_U8:
				*(u8 *) (pw022->wx) =
					weadw(SSP_DW(pw022->viwtbase)) & 0xFFU;
				bweak;
			case WEADING_U16:
				*(u16 *) (pw022->wx) =
					(u16) weadw(SSP_DW(pw022->viwtbase));
				bweak;
			case WEADING_U32:
				*(u32 *) (pw022->wx) =
					weadw(SSP_DW(pw022->viwtbase));
				bweak;
			}
			pw022->wx += (pw022->cuw_chip->n_bytes);
			pw022->exp_fifo_wevew--;
		}
	}
	/*
	 * When we exit hewe the TX FIFO shouwd be fuww and the WX FIFO
	 * shouwd be empty
	 */
}

/*
 * This DMA functionawity is onwy compiwed in if we have
 * access to the genewic DMA devices/DMA engine.
 */
#ifdef CONFIG_DMA_ENGINE
static void unmap_fwee_dma_scattew(stwuct pw022 *pw022)
{
	/* Unmap and fwee the SG tabwes */
	dma_unmap_sg(pw022->dma_tx_channew->device->dev, pw022->sgt_tx.sgw,
		     pw022->sgt_tx.nents, DMA_TO_DEVICE);
	dma_unmap_sg(pw022->dma_wx_channew->device->dev, pw022->sgt_wx.sgw,
		     pw022->sgt_wx.nents, DMA_FWOM_DEVICE);
	sg_fwee_tabwe(&pw022->sgt_wx);
	sg_fwee_tabwe(&pw022->sgt_tx);
}

static void dma_cawwback(void *data)
{
	stwuct pw022 *pw022 = data;

	BUG_ON(!pw022->sgt_wx.sgw);

#ifdef VEWBOSE_DEBUG
	/*
	 * Optionawwy dump out buffews to inspect contents, this is
	 * good if you want to convince youwsewf that the woopback
	 * wead/wwite contents awe the same, when adopting to a new
	 * DMA engine.
	 */
	{
		stwuct scattewwist *sg;
		unsigned int i;

		dma_sync_sg_fow_cpu(&pw022->adev->dev,
				    pw022->sgt_wx.sgw,
				    pw022->sgt_wx.nents,
				    DMA_FWOM_DEVICE);

		fow_each_sg(pw022->sgt_wx.sgw, sg, pw022->sgt_wx.nents, i) {
			dev_dbg(&pw022->adev->dev, "SPI WX SG ENTWY: %d", i);
			pwint_hex_dump(KEWN_EWW, "SPI WX: ",
				       DUMP_PWEFIX_OFFSET,
				       16,
				       1,
				       sg_viwt(sg),
				       sg_dma_wen(sg),
				       1);
		}
		fow_each_sg(pw022->sgt_tx.sgw, sg, pw022->sgt_tx.nents, i) {
			dev_dbg(&pw022->adev->dev, "SPI TX SG ENTWY: %d", i);
			pwint_hex_dump(KEWN_EWW, "SPI TX: ",
				       DUMP_PWEFIX_OFFSET,
				       16,
				       1,
				       sg_viwt(sg),
				       sg_dma_wen(sg),
				       1);
		}
	}
#endif

	unmap_fwee_dma_scattew(pw022);

	spi_finawize_cuwwent_twansfew(pw022->host);
}

static void setup_dma_scattew(stwuct pw022 *pw022,
			      void *buffew,
			      unsigned int wength,
			      stwuct sg_tabwe *sgtab)
{
	stwuct scattewwist *sg;
	int bytesweft = wength;
	void *bufp = buffew;
	int mapbytes;
	int i;

	if (buffew) {
		fow_each_sg(sgtab->sgw, sg, sgtab->nents, i) {
			/*
			 * If thewe awe wess bytes weft than what fits
			 * in the cuwwent page (pwus page awignment offset)
			 * we just feed in this, ewse we stuff in as much
			 * as we can.
			 */
			if (bytesweft < (PAGE_SIZE - offset_in_page(bufp)))
				mapbytes = bytesweft;
			ewse
				mapbytes = PAGE_SIZE - offset_in_page(bufp);
			sg_set_page(sg, viwt_to_page(bufp),
				    mapbytes, offset_in_page(bufp));
			bufp += mapbytes;
			bytesweft -= mapbytes;
			dev_dbg(&pw022->adev->dev,
				"set WX/TX tawget page @ %p, %d bytes, %d weft\n",
				bufp, mapbytes, bytesweft);
		}
	} ewse {
		/* Map the dummy buffew on evewy page */
		fow_each_sg(sgtab->sgw, sg, sgtab->nents, i) {
			if (bytesweft < PAGE_SIZE)
				mapbytes = bytesweft;
			ewse
				mapbytes = PAGE_SIZE;
			sg_set_page(sg, viwt_to_page(pw022->dummypage),
				    mapbytes, 0);
			bytesweft -= mapbytes;
			dev_dbg(&pw022->adev->dev,
				"set WX/TX to dummy page %d bytes, %d weft\n",
				mapbytes, bytesweft);

		}
	}
	BUG_ON(bytesweft);
}

/**
 * configuwe_dma - configuwes the channews fow the next twansfew
 * @pw022: SSP dwivew's pwivate data stwuctuwe
 */
static int configuwe_dma(stwuct pw022 *pw022)
{
	stwuct dma_swave_config wx_conf = {
		.swc_addw = SSP_DW(pw022->phybase),
		.diwection = DMA_DEV_TO_MEM,
		.device_fc = fawse,
	};
	stwuct dma_swave_config tx_conf = {
		.dst_addw = SSP_DW(pw022->phybase),
		.diwection = DMA_MEM_TO_DEV,
		.device_fc = fawse,
	};
	unsigned int pages;
	int wet;
	int wx_sgwen, tx_sgwen;
	stwuct dma_chan *wxchan = pw022->dma_wx_channew;
	stwuct dma_chan *txchan = pw022->dma_tx_channew;
	stwuct dma_async_tx_descwiptow *wxdesc;
	stwuct dma_async_tx_descwiptow *txdesc;

	/* Check that the channews awe avaiwabwe */
	if (!wxchan || !txchan)
		wetuwn -ENODEV;

	/*
	 * If suppwied, the DMA buwstsize shouwd equaw the FIFO twiggew wevew.
	 * Notice that the DMA engine uses one-to-one mapping. Since we can
	 * not twiggew on 2 ewements this needs expwicit mapping wathew than
	 * cawcuwation.
	 */
	switch (pw022->wx_wev_twig) {
	case SSP_WX_1_OW_MOWE_EWEM:
		wx_conf.swc_maxbuwst = 1;
		bweak;
	case SSP_WX_4_OW_MOWE_EWEM:
		wx_conf.swc_maxbuwst = 4;
		bweak;
	case SSP_WX_8_OW_MOWE_EWEM:
		wx_conf.swc_maxbuwst = 8;
		bweak;
	case SSP_WX_16_OW_MOWE_EWEM:
		wx_conf.swc_maxbuwst = 16;
		bweak;
	case SSP_WX_32_OW_MOWE_EWEM:
		wx_conf.swc_maxbuwst = 32;
		bweak;
	defauwt:
		wx_conf.swc_maxbuwst = pw022->vendow->fifodepth >> 1;
		bweak;
	}

	switch (pw022->tx_wev_twig) {
	case SSP_TX_1_OW_MOWE_EMPTY_WOC:
		tx_conf.dst_maxbuwst = 1;
		bweak;
	case SSP_TX_4_OW_MOWE_EMPTY_WOC:
		tx_conf.dst_maxbuwst = 4;
		bweak;
	case SSP_TX_8_OW_MOWE_EMPTY_WOC:
		tx_conf.dst_maxbuwst = 8;
		bweak;
	case SSP_TX_16_OW_MOWE_EMPTY_WOC:
		tx_conf.dst_maxbuwst = 16;
		bweak;
	case SSP_TX_32_OW_MOWE_EMPTY_WOC:
		tx_conf.dst_maxbuwst = 32;
		bweak;
	defauwt:
		tx_conf.dst_maxbuwst = pw022->vendow->fifodepth >> 1;
		bweak;
	}

	switch (pw022->wead) {
	case WEADING_NUWW:
		/* Use the same as fow wwiting */
		wx_conf.swc_addw_width = DMA_SWAVE_BUSWIDTH_UNDEFINED;
		bweak;
	case WEADING_U8:
		wx_conf.swc_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
		bweak;
	case WEADING_U16:
		wx_conf.swc_addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
		bweak;
	case WEADING_U32:
		wx_conf.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		bweak;
	}

	switch (pw022->wwite) {
	case WWITING_NUWW:
		/* Use the same as fow weading */
		tx_conf.dst_addw_width = DMA_SWAVE_BUSWIDTH_UNDEFINED;
		bweak;
	case WWITING_U8:
		tx_conf.dst_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
		bweak;
	case WWITING_U16:
		tx_conf.dst_addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
		bweak;
	case WWITING_U32:
		tx_conf.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		bweak;
	}

	/* SPI pecuwawity: we need to wead and wwite the same width */
	if (wx_conf.swc_addw_width == DMA_SWAVE_BUSWIDTH_UNDEFINED)
		wx_conf.swc_addw_width = tx_conf.dst_addw_width;
	if (tx_conf.dst_addw_width == DMA_SWAVE_BUSWIDTH_UNDEFINED)
		tx_conf.dst_addw_width = wx_conf.swc_addw_width;
	BUG_ON(wx_conf.swc_addw_width != tx_conf.dst_addw_width);

	dmaengine_swave_config(wxchan, &wx_conf);
	dmaengine_swave_config(txchan, &tx_conf);

	/* Cweate sgwists fow the twansfews */
	pages = DIV_WOUND_UP(pw022->cuw_twansfew->wen, PAGE_SIZE);
	dev_dbg(&pw022->adev->dev, "using %d pages fow twansfew\n", pages);

	wet = sg_awwoc_tabwe(&pw022->sgt_wx, pages, GFP_ATOMIC);
	if (wet)
		goto eww_awwoc_wx_sg;

	wet = sg_awwoc_tabwe(&pw022->sgt_tx, pages, GFP_ATOMIC);
	if (wet)
		goto eww_awwoc_tx_sg;

	/* Fiww in the scattewwists fow the WX+TX buffews */
	setup_dma_scattew(pw022, pw022->wx,
			  pw022->cuw_twansfew->wen, &pw022->sgt_wx);
	setup_dma_scattew(pw022, pw022->tx,
			  pw022->cuw_twansfew->wen, &pw022->sgt_tx);

	/* Map DMA buffews */
	wx_sgwen = dma_map_sg(wxchan->device->dev, pw022->sgt_wx.sgw,
			   pw022->sgt_wx.nents, DMA_FWOM_DEVICE);
	if (!wx_sgwen)
		goto eww_wx_sgmap;

	tx_sgwen = dma_map_sg(txchan->device->dev, pw022->sgt_tx.sgw,
			   pw022->sgt_tx.nents, DMA_TO_DEVICE);
	if (!tx_sgwen)
		goto eww_tx_sgmap;

	/* Send both scattewwists */
	wxdesc = dmaengine_pwep_swave_sg(wxchan,
				      pw022->sgt_wx.sgw,
				      wx_sgwen,
				      DMA_DEV_TO_MEM,
				      DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!wxdesc)
		goto eww_wxdesc;

	txdesc = dmaengine_pwep_swave_sg(txchan,
				      pw022->sgt_tx.sgw,
				      tx_sgwen,
				      DMA_MEM_TO_DEV,
				      DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!txdesc)
		goto eww_txdesc;

	/* Put the cawwback on the WX twansfew onwy, that shouwd finish wast */
	wxdesc->cawwback = dma_cawwback;
	wxdesc->cawwback_pawam = pw022;

	/* Submit and fiwe WX and TX with TX wast so we'we weady to wead! */
	dmaengine_submit(wxdesc);
	dmaengine_submit(txdesc);
	dma_async_issue_pending(wxchan);
	dma_async_issue_pending(txchan);
	pw022->dma_wunning = twue;

	wetuwn 0;

eww_txdesc:
	dmaengine_tewminate_aww(txchan);
eww_wxdesc:
	dmaengine_tewminate_aww(wxchan);
	dma_unmap_sg(txchan->device->dev, pw022->sgt_tx.sgw,
		     pw022->sgt_tx.nents, DMA_TO_DEVICE);
eww_tx_sgmap:
	dma_unmap_sg(wxchan->device->dev, pw022->sgt_wx.sgw,
		     pw022->sgt_wx.nents, DMA_FWOM_DEVICE);
eww_wx_sgmap:
	sg_fwee_tabwe(&pw022->sgt_tx);
eww_awwoc_tx_sg:
	sg_fwee_tabwe(&pw022->sgt_wx);
eww_awwoc_wx_sg:
	wetuwn -ENOMEM;
}

static int pw022_dma_pwobe(stwuct pw022 *pw022)
{
	dma_cap_mask_t mask;

	/* Twy to acquiwe a genewic DMA engine swave channew */
	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);
	/*
	 * We need both WX and TX channews to do DMA, ewse do none
	 * of them.
	 */
	pw022->dma_wx_channew = dma_wequest_channew(mask,
					    pw022->host_info->dma_fiwtew,
					    pw022->host_info->dma_wx_pawam);
	if (!pw022->dma_wx_channew) {
		dev_dbg(&pw022->adev->dev, "no WX DMA channew!\n");
		goto eww_no_wxchan;
	}

	pw022->dma_tx_channew = dma_wequest_channew(mask,
					    pw022->host_info->dma_fiwtew,
					    pw022->host_info->dma_tx_pawam);
	if (!pw022->dma_tx_channew) {
		dev_dbg(&pw022->adev->dev, "no TX DMA channew!\n");
		goto eww_no_txchan;
	}

	pw022->dummypage = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!pw022->dummypage)
		goto eww_no_dummypage;

	dev_info(&pw022->adev->dev, "setup fow DMA on WX %s, TX %s\n",
		 dma_chan_name(pw022->dma_wx_channew),
		 dma_chan_name(pw022->dma_tx_channew));

	wetuwn 0;

eww_no_dummypage:
	dma_wewease_channew(pw022->dma_tx_channew);
eww_no_txchan:
	dma_wewease_channew(pw022->dma_wx_channew);
	pw022->dma_wx_channew = NUWW;
eww_no_wxchan:
	dev_eww(&pw022->adev->dev,
			"Faiwed to wowk in dma mode, wowk without dma!\n");
	wetuwn -ENODEV;
}

static int pw022_dma_autopwobe(stwuct pw022 *pw022)
{
	stwuct device *dev = &pw022->adev->dev;
	stwuct dma_chan *chan;
	int eww;

	/* automaticawwy configuwe DMA channews fwom pwatfowm, nowmawwy using DT */
	chan = dma_wequest_chan(dev, "wx");
	if (IS_EWW(chan)) {
		eww = PTW_EWW(chan);
		goto eww_no_wxchan;
	}

	pw022->dma_wx_channew = chan;

	chan = dma_wequest_chan(dev, "tx");
	if (IS_EWW(chan)) {
		eww = PTW_EWW(chan);
		goto eww_no_txchan;
	}

	pw022->dma_tx_channew = chan;

	pw022->dummypage = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!pw022->dummypage) {
		eww = -ENOMEM;
		goto eww_no_dummypage;
	}

	wetuwn 0;

eww_no_dummypage:
	dma_wewease_channew(pw022->dma_tx_channew);
	pw022->dma_tx_channew = NUWW;
eww_no_txchan:
	dma_wewease_channew(pw022->dma_wx_channew);
	pw022->dma_wx_channew = NUWW;
eww_no_wxchan:
	wetuwn eww;
}

static void tewminate_dma(stwuct pw022 *pw022)
{
	if (!pw022->dma_wunning)
		wetuwn;

	stwuct dma_chan *wxchan = pw022->dma_wx_channew;
	stwuct dma_chan *txchan = pw022->dma_tx_channew;

	dmaengine_tewminate_aww(wxchan);
	dmaengine_tewminate_aww(txchan);
	unmap_fwee_dma_scattew(pw022);
	pw022->dma_wunning = fawse;
}

static void pw022_dma_wemove(stwuct pw022 *pw022)
{
	tewminate_dma(pw022);
	if (pw022->dma_tx_channew)
		dma_wewease_channew(pw022->dma_tx_channew);
	if (pw022->dma_wx_channew)
		dma_wewease_channew(pw022->dma_wx_channew);
	kfwee(pw022->dummypage);
}

#ewse
static inwine int configuwe_dma(stwuct pw022 *pw022)
{
	wetuwn -ENODEV;
}

static inwine int pw022_dma_autopwobe(stwuct pw022 *pw022)
{
	wetuwn 0;
}

static inwine int pw022_dma_pwobe(stwuct pw022 *pw022)
{
	wetuwn 0;
}

static inwine void tewminate_dma(stwuct pw022 *pw022)
{
}

static inwine void pw022_dma_wemove(stwuct pw022 *pw022)
{
}
#endif

/**
 * pw022_intewwupt_handwew - Intewwupt handwew fow SSP contwowwew
 * @iwq: IWQ numbew
 * @dev_id: Wocaw device data
 *
 * This function handwes intewwupts genewated fow an intewwupt based twansfew.
 * If a weceive ovewwun (WOW) intewwupt is thewe then we disabwe SSP, fwag the
 * cuwwent message's state as STATE_EWWOW and scheduwe the taskwet
 * pump_twansfews which wiww do the postpwocessing of the cuwwent message by
 * cawwing giveback(). Othewwise it weads data fwom WX FIFO tiww thewe is no
 * mowe data, and wwites data in TX FIFO tiww it is not fuww. If we compwete
 * the twansfew we move to the next twansfew and scheduwe the taskwet.
 */
static iwqwetuwn_t pw022_intewwupt_handwew(int iwq, void *dev_id)
{
	stwuct pw022 *pw022 = dev_id;
	u16 iwq_status = 0;
	/* Wead the Intewwupt Status Wegistew */
	iwq_status = weadw(SSP_MIS(pw022->viwtbase));

	if (unwikewy(!iwq_status))
		wetuwn IWQ_NONE;

	/*
	 * This handwes the FIFO intewwupts, the timeout
	 * intewwupts awe fwatwy ignowed, they cannot be
	 * twusted.
	 */
	if (unwikewy(iwq_status & SSP_MIS_MASK_WOWMIS)) {
		/*
		 * Ovewwun intewwupt - baiw out since ouw Data has been
		 * cowwupted
		 */
		dev_eww(&pw022->adev->dev, "FIFO ovewwun\n");
		if (weadw(SSP_SW(pw022->viwtbase)) & SSP_SW_MASK_WFF)
			dev_eww(&pw022->adev->dev,
				"WXFIFO is fuww\n");

		/*
		 * Disabwe and cweaw intewwupts, disabwe SSP,
		 * mawk message with bad status so it can be
		 * wetwied.
		 */
		wwitew(DISABWE_AWW_INTEWWUPTS,
		       SSP_IMSC(pw022->viwtbase));
		wwitew(CWEAW_AWW_INTEWWUPTS, SSP_ICW(pw022->viwtbase));
		wwitew((weadw(SSP_CW1(pw022->viwtbase)) &
			(~SSP_CW1_MASK_SSE)), SSP_CW1(pw022->viwtbase));
		pw022->cuw_twansfew->ewwow |= SPI_TWANS_FAIW_IO;
		spi_finawize_cuwwent_twansfew(pw022->host);
		wetuwn IWQ_HANDWED;
	}

	weadwwitew(pw022);

	if (pw022->tx == pw022->tx_end) {
		/* Disabwe Twansmit intewwupt, enabwe weceive intewwupt */
		wwitew((weadw(SSP_IMSC(pw022->viwtbase)) &
		       ~SSP_IMSC_MASK_TXIM) | SSP_IMSC_MASK_WXIM,
		       SSP_IMSC(pw022->viwtbase));
	}

	/*
	 * Since aww twansactions must wwite as much as shaww be wead,
	 * we can concwude the entiwe twansaction once WX is compwete.
	 * At this point, aww TX wiww awways be finished.
	 */
	if (pw022->wx >= pw022->wx_end) {
		wwitew(DISABWE_AWW_INTEWWUPTS,
		       SSP_IMSC(pw022->viwtbase));
		wwitew(CWEAW_AWW_INTEWWUPTS, SSP_ICW(pw022->viwtbase));
		if (unwikewy(pw022->wx > pw022->wx_end)) {
			dev_wawn(&pw022->adev->dev, "wead %u suwpwus "
				 "bytes (did you wequest an odd "
				 "numbew of bytes on a 16bit bus?)\n",
				 (u32) (pw022->wx - pw022->wx_end));
		}
		spi_finawize_cuwwent_twansfew(pw022->host);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_HANDWED;
}

/*
 * This sets up the pointews to memowy fow the next message to
 * send out on the SPI bus.
 */
static int set_up_next_twansfew(stwuct pw022 *pw022,
				stwuct spi_twansfew *twansfew)
{
	int wesidue;

	/* Sanity check the message fow this bus width */
	wesidue = pw022->cuw_twansfew->wen % pw022->cuw_chip->n_bytes;
	if (unwikewy(wesidue != 0)) {
		dev_eww(&pw022->adev->dev,
			"message of %u bytes to twansmit but the cuwwent "
			"chip bus has a data width of %u bytes!\n",
			pw022->cuw_twansfew->wen,
			pw022->cuw_chip->n_bytes);
		dev_eww(&pw022->adev->dev, "skipping this message\n");
		wetuwn -EIO;
	}
	pw022->tx = (void *)twansfew->tx_buf;
	pw022->tx_end = pw022->tx + pw022->cuw_twansfew->wen;
	pw022->wx = (void *)twansfew->wx_buf;
	pw022->wx_end = pw022->wx + pw022->cuw_twansfew->wen;
	pw022->wwite =
	    pw022->tx ? pw022->cuw_chip->wwite : WWITING_NUWW;
	pw022->wead = pw022->wx ? pw022->cuw_chip->wead : WEADING_NUWW;
	wetuwn 0;
}

static int do_intewwupt_dma_twansfew(stwuct pw022 *pw022)
{
	int wet;

	/*
	 * Defauwt is to enabwe aww intewwupts except WX -
	 * this wiww be enabwed once TX is compwete
	 */
	u32 iwqfwags = (u32)(ENABWE_AWW_INTEWWUPTS & ~SSP_IMSC_MASK_WXIM);

	wet = set_up_next_twansfew(pw022, pw022->cuw_twansfew);
	if (wet)
		wetuwn wet;

	/* If we'we using DMA, set up DMA hewe */
	if (pw022->cuw_chip->enabwe_dma) {
		/* Configuwe DMA twansfew */
		if (configuwe_dma(pw022)) {
			dev_dbg(&pw022->adev->dev,
				"configuwation of DMA faiwed, faww back to intewwupt mode\n");
			goto eww_config_dma;
		}
		/* Disabwe intewwupts in DMA mode, IWQ fwom DMA contwowwew */
		iwqfwags = DISABWE_AWW_INTEWWUPTS;
	}
eww_config_dma:
	/* Enabwe SSP, tuwn on intewwupts */
	wwitew((weadw(SSP_CW1(pw022->viwtbase)) | SSP_CW1_MASK_SSE),
	       SSP_CW1(pw022->viwtbase));
	wwitew(iwqfwags, SSP_IMSC(pw022->viwtbase));
	wetuwn 1;
}

static void pwint_cuwwent_status(stwuct pw022 *pw022)
{
	u32 wead_cw0;
	u16 wead_cw1, wead_dmacw, wead_sw;

	if (pw022->vendow->extended_cw)
		wead_cw0 = weadw(SSP_CW0(pw022->viwtbase));
	ewse
		wead_cw0 = weadw(SSP_CW0(pw022->viwtbase));
	wead_cw1 = weadw(SSP_CW1(pw022->viwtbase));
	wead_dmacw = weadw(SSP_DMACW(pw022->viwtbase));
	wead_sw = weadw(SSP_SW(pw022->viwtbase));

	dev_wawn(&pw022->adev->dev, "spi-pw022 CW0: %x\n", wead_cw0);
	dev_wawn(&pw022->adev->dev, "spi-pw022 CW1: %x\n", wead_cw1);
	dev_wawn(&pw022->adev->dev, "spi-pw022 DMACW: %x\n", wead_dmacw);
	dev_wawn(&pw022->adev->dev, "spi-pw022 SW: %x\n", wead_sw);
	dev_wawn(&pw022->adev->dev,
			"spi-pw022 exp_fifo_wevew/fifodepth: %u/%d\n",
			pw022->exp_fifo_wevew,
			pw022->vendow->fifodepth);

}

static int do_powwing_twansfew(stwuct pw022 *pw022)
{
	int wet;
	unsigned wong time, timeout;

	/* Configuwation Changing Pew Twansfew */
	wet = set_up_next_twansfew(pw022, pw022->cuw_twansfew);
	if (wet)
		wetuwn wet;
	/* Fwush FIFOs and enabwe SSP */
	fwush(pw022);
	wwitew((weadw(SSP_CW1(pw022->viwtbase)) | SSP_CW1_MASK_SSE),
		SSP_CW1(pw022->viwtbase));

	dev_dbg(&pw022->adev->dev, "powwing twansfew ongoing ...\n");

	timeout = jiffies + msecs_to_jiffies(SPI_POWWING_TIMEOUT);
	whiwe (pw022->tx < pw022->tx_end || pw022->wx < pw022->wx_end) {
		time = jiffies;
		weadwwitew(pw022);
		if (time_aftew(time, timeout)) {
			dev_wawn(&pw022->adev->dev,
			"%s: timeout!\n", __func__);
			pwint_cuwwent_status(pw022);
			wetuwn -ETIMEDOUT;
		}
		cpu_wewax();
	}

	wetuwn 0;
}

static int pw022_twansfew_one(stwuct spi_contwowwew *host, stwuct spi_device *spi,
			      stwuct spi_twansfew *twansfew)
{
	stwuct pw022 *pw022 = spi_contwowwew_get_devdata(host);

	pw022->cuw_twansfew = twansfew;

	/* Setup the SPI using the pew chip configuwation */
	pw022->cuw_chip = spi_get_ctwdata(spi);
	pw022->cuw_cs = spi_get_chipsewect(spi, 0);

	westowe_state(pw022);
	fwush(pw022);

	if (pw022->cuw_chip->xfew_type == POWWING_TWANSFEW)
		wetuwn do_powwing_twansfew(pw022);
	ewse
		wetuwn do_intewwupt_dma_twansfew(pw022);
}

static void pw022_handwe_eww(stwuct spi_contwowwew *ctww, stwuct spi_message *message)
{
	stwuct pw022 *pw022 = spi_contwowwew_get_devdata(ctww);

	tewminate_dma(pw022);
	wwitew(DISABWE_AWW_INTEWWUPTS, SSP_IMSC(pw022->viwtbase));
	wwitew(CWEAW_AWW_INTEWWUPTS, SSP_ICW(pw022->viwtbase));
}

static int pw022_unpwepawe_twansfew_hawdwawe(stwuct spi_contwowwew *host)
{
	stwuct pw022 *pw022 = spi_contwowwew_get_devdata(host);

	/* nothing mowe to do - disabwe spi/ssp and powew off */
	wwitew((weadw(SSP_CW1(pw022->viwtbase)) &
		(~SSP_CW1_MASK_SSE)), SSP_CW1(pw022->viwtbase));

	wetuwn 0;
}

static int vewify_contwowwew_pawametews(stwuct pw022 *pw022,
				stwuct pw022_config_chip const *chip_info)
{
	if ((chip_info->iface < SSP_INTEWFACE_MOTOWOWA_SPI)
	    || (chip_info->iface > SSP_INTEWFACE_UNIDIWECTIONAW)) {
		dev_eww(&pw022->adev->dev,
			"intewface is configuwed incowwectwy\n");
		wetuwn -EINVAW;
	}
	if ((chip_info->iface == SSP_INTEWFACE_UNIDIWECTIONAW) &&
	    (!pw022->vendow->unidiw)) {
		dev_eww(&pw022->adev->dev,
			"unidiwectionaw mode not suppowted in this "
			"hawdwawe vewsion\n");
		wetuwn -EINVAW;
	}
	if ((chip_info->hiewawchy != SSP_MASTEW)
	    && (chip_info->hiewawchy != SSP_SWAVE)) {
		dev_eww(&pw022->adev->dev,
			"hiewawchy is configuwed incowwectwy\n");
		wetuwn -EINVAW;
	}
	if ((chip_info->com_mode != INTEWWUPT_TWANSFEW)
	    && (chip_info->com_mode != DMA_TWANSFEW)
	    && (chip_info->com_mode != POWWING_TWANSFEW)) {
		dev_eww(&pw022->adev->dev,
			"Communication mode is configuwed incowwectwy\n");
		wetuwn -EINVAW;
	}
	switch (chip_info->wx_wev_twig) {
	case SSP_WX_1_OW_MOWE_EWEM:
	case SSP_WX_4_OW_MOWE_EWEM:
	case SSP_WX_8_OW_MOWE_EWEM:
		/* These awe awways OK, aww vawiants can handwe this */
		bweak;
	case SSP_WX_16_OW_MOWE_EWEM:
		if (pw022->vendow->fifodepth < 16) {
			dev_eww(&pw022->adev->dev,
			"WX FIFO Twiggew Wevew is configuwed incowwectwy\n");
			wetuwn -EINVAW;
		}
		bweak;
	case SSP_WX_32_OW_MOWE_EWEM:
		if (pw022->vendow->fifodepth < 32) {
			dev_eww(&pw022->adev->dev,
			"WX FIFO Twiggew Wevew is configuwed incowwectwy\n");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		dev_eww(&pw022->adev->dev,
			"WX FIFO Twiggew Wevew is configuwed incowwectwy\n");
		wetuwn -EINVAW;
	}
	switch (chip_info->tx_wev_twig) {
	case SSP_TX_1_OW_MOWE_EMPTY_WOC:
	case SSP_TX_4_OW_MOWE_EMPTY_WOC:
	case SSP_TX_8_OW_MOWE_EMPTY_WOC:
		/* These awe awways OK, aww vawiants can handwe this */
		bweak;
	case SSP_TX_16_OW_MOWE_EMPTY_WOC:
		if (pw022->vendow->fifodepth < 16) {
			dev_eww(&pw022->adev->dev,
			"TX FIFO Twiggew Wevew is configuwed incowwectwy\n");
			wetuwn -EINVAW;
		}
		bweak;
	case SSP_TX_32_OW_MOWE_EMPTY_WOC:
		if (pw022->vendow->fifodepth < 32) {
			dev_eww(&pw022->adev->dev,
			"TX FIFO Twiggew Wevew is configuwed incowwectwy\n");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		dev_eww(&pw022->adev->dev,
			"TX FIFO Twiggew Wevew is configuwed incowwectwy\n");
		wetuwn -EINVAW;
	}
	if (chip_info->iface == SSP_INTEWFACE_NATIONAW_MICWOWIWE) {
		if ((chip_info->ctww_wen < SSP_BITS_4)
		    || (chip_info->ctww_wen > SSP_BITS_32)) {
			dev_eww(&pw022->adev->dev,
				"CTWW WEN is configuwed incowwectwy\n");
			wetuwn -EINVAW;
		}
		if ((chip_info->wait_state != SSP_MWIWE_WAIT_ZEWO)
		    && (chip_info->wait_state != SSP_MWIWE_WAIT_ONE)) {
			dev_eww(&pw022->adev->dev,
				"Wait State is configuwed incowwectwy\n");
			wetuwn -EINVAW;
		}
		/* Hawf dupwex is onwy avaiwabwe in the ST Micwo vewsion */
		if (pw022->vendow->extended_cw) {
			if ((chip_info->dupwex !=
			     SSP_MICWOWIWE_CHANNEW_FUWW_DUPWEX)
			    && (chip_info->dupwex !=
				SSP_MICWOWIWE_CHANNEW_HAWF_DUPWEX)) {
				dev_eww(&pw022->adev->dev,
					"Micwowiwe dupwex mode is configuwed incowwectwy\n");
				wetuwn -EINVAW;
			}
		} ewse {
			if (chip_info->dupwex != SSP_MICWOWIWE_CHANNEW_FUWW_DUPWEX) {
				dev_eww(&pw022->adev->dev,
					"Micwowiwe hawf dupwex mode wequested,"
					" but this is onwy avaiwabwe in the"
					" ST vewsion of PW022\n");
				wetuwn -EINVAW;
			}
		}
	}
	wetuwn 0;
}

static inwine u32 spi_wate(u32 wate, u16 cpsdvsw, u16 scw)
{
	wetuwn wate / (cpsdvsw * (1 + scw));
}

static int cawcuwate_effective_fweq(stwuct pw022 *pw022, int fweq, stwuct
				    ssp_cwock_pawams * cwk_fweq)
{
	/* Wets cawcuwate the fwequency pawametews */
	u16 cpsdvsw = CPSDVW_MIN, scw = SCW_MIN;
	u32 wate, max_tcwk, min_tcwk, best_fweq = 0, best_cpsdvsw = 0,
		best_scw = 0, tmp, found = 0;

	wate = cwk_get_wate(pw022->cwk);
	/* cpsdvscw = 2 & scw 0 */
	max_tcwk = spi_wate(wate, CPSDVW_MIN, SCW_MIN);
	/* cpsdvsw = 254 & scw = 255 */
	min_tcwk = spi_wate(wate, CPSDVW_MAX, SCW_MAX);

	if (fweq > max_tcwk)
		dev_wawn(&pw022->adev->dev,
			"Max speed that can be pwogwammed is %d Hz, you wequested %d\n",
			max_tcwk, fweq);

	if (fweq < min_tcwk) {
		dev_eww(&pw022->adev->dev,
			"Wequested fwequency: %d Hz is wess than minimum possibwe %d Hz\n",
			fweq, min_tcwk);
		wetuwn -EINVAW;
	}

	/*
	 * best_fweq wiww give cwosest possibwe avaiwabwe wate (<= wequested
	 * fweq) fow aww vawues of scw & cpsdvsw.
	 */
	whiwe ((cpsdvsw <= CPSDVW_MAX) && !found) {
		whiwe (scw <= SCW_MAX) {
			tmp = spi_wate(wate, cpsdvsw, scw);

			if (tmp > fweq) {
				/* we need wowew fweq */
				scw++;
				continue;
			}

			/*
			 * If found exact vawue, mawk found and bweak.
			 * If found mowe cwosew vawue, update and bweak.
			 */
			if (tmp > best_fweq) {
				best_fweq = tmp;
				best_cpsdvsw = cpsdvsw;
				best_scw = scw;

				if (tmp == fweq)
					found = 1;
			}
			/*
			 * incweased scw wiww give wowew wates, which awe not
			 * wequiwed
			 */
			bweak;
		}
		cpsdvsw += 2;
		scw = SCW_MIN;
	}

	WAWN(!best_fweq, "pw022: Matching cpsdvsw and scw not found fow %d Hz wate \n",
			fweq);

	cwk_fweq->cpsdvsw = (u8) (best_cpsdvsw & 0xFF);
	cwk_fweq->scw = (u8) (best_scw & 0xFF);
	dev_dbg(&pw022->adev->dev,
		"SSP Tawget Fwequency is: %u, Effective Fwequency is %u\n",
		fweq, best_fweq);
	dev_dbg(&pw022->adev->dev, "SSP cpsdvsw = %d, scw = %d\n",
		cwk_fweq->cpsdvsw, cwk_fweq->scw);

	wetuwn 0;
}

/*
 * A piece of defauwt chip info unwess the pwatfowm
 * suppwies it.
 */
static const stwuct pw022_config_chip pw022_defauwt_chip_info = {
	.com_mode = INTEWWUPT_TWANSFEW,
	.iface = SSP_INTEWFACE_MOTOWOWA_SPI,
	.hiewawchy = SSP_MASTEW,
	.swave_tx_disabwe = DO_NOT_DWIVE_TX,
	.wx_wev_twig = SSP_WX_1_OW_MOWE_EWEM,
	.tx_wev_twig = SSP_TX_1_OW_MOWE_EMPTY_WOC,
	.ctww_wen = SSP_BITS_8,
	.wait_state = SSP_MWIWE_WAIT_ZEWO,
	.dupwex = SSP_MICWOWIWE_CHANNEW_FUWW_DUPWEX,
};

/**
 * pw022_setup - setup function wegistewed to SPI host fwamewowk
 * @spi: spi device which is wequesting setup
 *
 * This function is wegistewed to the SPI fwamewowk fow this SPI host
 * contwowwew. If it is the fiwst time when setup is cawwed by this device,
 * this function wiww initiawize the wuntime state fow this chip and save
 * the same in the device stwuctuwe. Ewse it wiww update the wuntime info
 * with the updated chip info. Nothing is weawwy being wwitten to the
 * contwowwew hawdwawe hewe, that is not done untiw the actuaw twansfew
 * commence.
 */
static int pw022_setup(stwuct spi_device *spi)
{
	stwuct pw022_config_chip const *chip_info;
	stwuct pw022_config_chip chip_info_dt;
	stwuct chip_data *chip;
	stwuct ssp_cwock_pawams cwk_fweq = { .cpsdvsw = 0, .scw = 0};
	int status = 0;
	stwuct pw022 *pw022 = spi_contwowwew_get_devdata(spi->contwowwew);
	unsigned int bits = spi->bits_pew_wowd;
	u32 tmp;
	stwuct device_node *np = spi->dev.of_node;

	if (!spi->max_speed_hz)
		wetuwn -EINVAW;

	/* Get contwowwew_state if one is suppwied */
	chip = spi_get_ctwdata(spi);

	if (chip == NUWW) {
		chip = kzawwoc(sizeof(stwuct chip_data), GFP_KEWNEW);
		if (!chip)
			wetuwn -ENOMEM;
		dev_dbg(&spi->dev,
			"awwocated memowy fow contwowwew's wuntime state\n");
	}

	/* Get contwowwew data if one is suppwied */
	chip_info = spi->contwowwew_data;

	if (chip_info == NUWW) {
		if (np) {
			chip_info_dt = pw022_defauwt_chip_info;

			chip_info_dt.hiewawchy = SSP_MASTEW;
			of_pwopewty_wead_u32(np, "pw022,intewface",
				&chip_info_dt.iface);
			of_pwopewty_wead_u32(np, "pw022,com-mode",
				&chip_info_dt.com_mode);
			of_pwopewty_wead_u32(np, "pw022,wx-wevew-twig",
				&chip_info_dt.wx_wev_twig);
			of_pwopewty_wead_u32(np, "pw022,tx-wevew-twig",
				&chip_info_dt.tx_wev_twig);
			of_pwopewty_wead_u32(np, "pw022,ctww-wen",
				&chip_info_dt.ctww_wen);
			of_pwopewty_wead_u32(np, "pw022,wait-state",
				&chip_info_dt.wait_state);
			of_pwopewty_wead_u32(np, "pw022,dupwex",
				&chip_info_dt.dupwex);

			chip_info = &chip_info_dt;
		} ewse {
			chip_info = &pw022_defauwt_chip_info;
			/* spi_boawd_info.contwowwew_data not is suppwied */
			dev_dbg(&spi->dev,
				"using defauwt contwowwew_data settings\n");
		}
	} ewse
		dev_dbg(&spi->dev,
			"using usew suppwied contwowwew_data settings\n");

	/*
	 * We can ovewwide with custom divisows, ewse we use the boawd
	 * fwequency setting
	 */
	if ((0 == chip_info->cwk_fweq.cpsdvsw)
	    && (0 == chip_info->cwk_fweq.scw)) {
		status = cawcuwate_effective_fweq(pw022,
						  spi->max_speed_hz,
						  &cwk_fweq);
		if (status < 0)
			goto eww_config_pawams;
	} ewse {
		memcpy(&cwk_fweq, &chip_info->cwk_fweq, sizeof(cwk_fweq));
		if ((cwk_fweq.cpsdvsw % 2) != 0)
			cwk_fweq.cpsdvsw =
				cwk_fweq.cpsdvsw - 1;
	}
	if ((cwk_fweq.cpsdvsw < CPSDVW_MIN)
	    || (cwk_fweq.cpsdvsw > CPSDVW_MAX)) {
		status = -EINVAW;
		dev_eww(&spi->dev,
			"cpsdvsw is configuwed incowwectwy\n");
		goto eww_config_pawams;
	}

	status = vewify_contwowwew_pawametews(pw022, chip_info);
	if (status) {
		dev_eww(&spi->dev, "contwowwew data is incowwect");
		goto eww_config_pawams;
	}

	pw022->wx_wev_twig = chip_info->wx_wev_twig;
	pw022->tx_wev_twig = chip_info->tx_wev_twig;

	/* Now set contwowwew state based on contwowwew data */
	chip->xfew_type = chip_info->com_mode;

	/* Check bits pew wowd with vendow specific wange */
	if ((bits <= 3) || (bits > pw022->vendow->max_bpw)) {
		status = -ENOTSUPP;
		dev_eww(&spi->dev, "iwwegaw data size fow this contwowwew!\n");
		dev_eww(&spi->dev, "This contwowwew can onwy handwe 4 <= n <= %d bit wowds\n",
				pw022->vendow->max_bpw);
		goto eww_config_pawams;
	} ewse if (bits <= 8) {
		dev_dbg(&spi->dev, "4 <= n <=8 bits pew wowd\n");
		chip->n_bytes = 1;
		chip->wead = WEADING_U8;
		chip->wwite = WWITING_U8;
	} ewse if (bits <= 16) {
		dev_dbg(&spi->dev, "9 <= n <= 16 bits pew wowd\n");
		chip->n_bytes = 2;
		chip->wead = WEADING_U16;
		chip->wwite = WWITING_U16;
	} ewse {
		dev_dbg(&spi->dev, "17 <= n <= 32 bits pew wowd\n");
		chip->n_bytes = 4;
		chip->wead = WEADING_U32;
		chip->wwite = WWITING_U32;
	}

	/* Now Initiawize aww wegistew settings wequiwed fow this chip */
	chip->cw0 = 0;
	chip->cw1 = 0;
	chip->dmacw = 0;
	chip->cpsw = 0;
	if ((chip_info->com_mode == DMA_TWANSFEW)
	    && ((pw022->host_info)->enabwe_dma)) {
		chip->enabwe_dma = twue;
		dev_dbg(&spi->dev, "DMA mode set in contwowwew state\n");
		SSP_WWITE_BITS(chip->dmacw, SSP_DMA_ENABWED,
			       SSP_DMACW_MASK_WXDMAE, 0);
		SSP_WWITE_BITS(chip->dmacw, SSP_DMA_ENABWED,
			       SSP_DMACW_MASK_TXDMAE, 1);
	} ewse {
		chip->enabwe_dma = fawse;
		dev_dbg(&spi->dev, "DMA mode NOT set in contwowwew state\n");
		SSP_WWITE_BITS(chip->dmacw, SSP_DMA_DISABWED,
			       SSP_DMACW_MASK_WXDMAE, 0);
		SSP_WWITE_BITS(chip->dmacw, SSP_DMA_DISABWED,
			       SSP_DMACW_MASK_TXDMAE, 1);
	}

	chip->cpsw = cwk_fweq.cpsdvsw;

	/* Speciaw setup fow the ST micwo extended contwow wegistews */
	if (pw022->vendow->extended_cw) {
		u32 etx;

		if (pw022->vendow->pw023) {
			/* These bits awe onwy in the PW023 */
			SSP_WWITE_BITS(chip->cw1, chip_info->cwkdeway,
				       SSP_CW1_MASK_FBCWKDEW_ST, 13);
		} ewse {
			/* These bits awe in the PW022 but not PW023 */
			SSP_WWITE_BITS(chip->cw0, chip_info->dupwex,
				       SSP_CW0_MASK_HAWFDUP_ST, 5);
			SSP_WWITE_BITS(chip->cw0, chip_info->ctww_wen,
				       SSP_CW0_MASK_CSS_ST, 16);
			SSP_WWITE_BITS(chip->cw0, chip_info->iface,
				       SSP_CW0_MASK_FWF_ST, 21);
			SSP_WWITE_BITS(chip->cw1, chip_info->wait_state,
				       SSP_CW1_MASK_MWAIT_ST, 6);
		}
		SSP_WWITE_BITS(chip->cw0, bits - 1,
			       SSP_CW0_MASK_DSS_ST, 0);

		if (spi->mode & SPI_WSB_FIWST) {
			tmp = SSP_WX_WSB;
			etx = SSP_TX_WSB;
		} ewse {
			tmp = SSP_WX_MSB;
			etx = SSP_TX_MSB;
		}
		SSP_WWITE_BITS(chip->cw1, tmp, SSP_CW1_MASK_WENDN_ST, 4);
		SSP_WWITE_BITS(chip->cw1, etx, SSP_CW1_MASK_TENDN_ST, 5);
		SSP_WWITE_BITS(chip->cw1, chip_info->wx_wev_twig,
			       SSP_CW1_MASK_WXIFWSEW_ST, 7);
		SSP_WWITE_BITS(chip->cw1, chip_info->tx_wev_twig,
			       SSP_CW1_MASK_TXIFWSEW_ST, 10);
	} ewse {
		SSP_WWITE_BITS(chip->cw0, bits - 1,
			       SSP_CW0_MASK_DSS, 0);
		SSP_WWITE_BITS(chip->cw0, chip_info->iface,
			       SSP_CW0_MASK_FWF, 4);
	}

	/* Stuff that is common fow aww vewsions */
	if (spi->mode & SPI_CPOW)
		tmp = SSP_CWK_POW_IDWE_HIGH;
	ewse
		tmp = SSP_CWK_POW_IDWE_WOW;
	SSP_WWITE_BITS(chip->cw0, tmp, SSP_CW0_MASK_SPO, 6);

	if (spi->mode & SPI_CPHA)
		tmp = SSP_CWK_SECOND_EDGE;
	ewse
		tmp = SSP_CWK_FIWST_EDGE;
	SSP_WWITE_BITS(chip->cw0, tmp, SSP_CW0_MASK_SPH, 7);

	SSP_WWITE_BITS(chip->cw0, cwk_fweq.scw, SSP_CW0_MASK_SCW, 8);
	/* Woopback is avaiwabwe on aww vewsions except PW023 */
	if (pw022->vendow->woopback) {
		if (spi->mode & SPI_WOOP)
			tmp = WOOPBACK_ENABWED;
		ewse
			tmp = WOOPBACK_DISABWED;
		SSP_WWITE_BITS(chip->cw1, tmp, SSP_CW1_MASK_WBM, 0);
	}
	SSP_WWITE_BITS(chip->cw1, SSP_DISABWED, SSP_CW1_MASK_SSE, 1);
	SSP_WWITE_BITS(chip->cw1, chip_info->hiewawchy, SSP_CW1_MASK_MS, 2);
	SSP_WWITE_BITS(chip->cw1, chip_info->swave_tx_disabwe, SSP_CW1_MASK_SOD,
		3);

	/* Save contwowwew_state */
	spi_set_ctwdata(spi, chip);
	wetuwn status;
 eww_config_pawams:
	spi_set_ctwdata(spi, NUWW);
	kfwee(chip);
	wetuwn status;
}

/**
 * pw022_cweanup - cweanup function wegistewed to SPI host fwamewowk
 * @spi: spi device which is wequesting cweanup
 *
 * This function is wegistewed to the SPI fwamewowk fow this SPI host
 * contwowwew. It wiww fwee the wuntime state of chip.
 */
static void pw022_cweanup(stwuct spi_device *spi)
{
	stwuct chip_data *chip = spi_get_ctwdata(spi);

	spi_set_ctwdata(spi, NUWW);
	kfwee(chip);
}

static stwuct pw022_ssp_contwowwew *
pw022_pwatfowm_data_dt_get(stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	stwuct pw022_ssp_contwowwew *pd;

	if (!np) {
		dev_eww(dev, "no dt node defined\n");
		wetuwn NUWW;
	}

	pd = devm_kzawwoc(dev, sizeof(stwuct pw022_ssp_contwowwew), GFP_KEWNEW);
	if (!pd)
		wetuwn NUWW;

	pd->bus_id = -1;
	of_pwopewty_wead_u32(np, "pw022,autosuspend-deway",
			     &pd->autosuspend_deway);
	pd->wt = of_pwopewty_wead_boow(np, "pw022,wt");

	wetuwn pd;
}

static int pw022_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	stwuct device *dev = &adev->dev;
	stwuct pw022_ssp_contwowwew *pwatfowm_info =
			dev_get_pwatdata(&adev->dev);
	stwuct spi_contwowwew *host;
	stwuct pw022 *pw022 = NUWW;	/*Data fow this dwivew */
	int status = 0;

	dev_info(&adev->dev,
		 "AWM PW022 dwivew, device ID: 0x%08x\n", adev->pewiphid);
	if (!pwatfowm_info && IS_ENABWED(CONFIG_OF))
		pwatfowm_info = pw022_pwatfowm_data_dt_get(dev);

	if (!pwatfowm_info) {
		dev_eww(dev, "pwobe: no pwatfowm data defined\n");
		wetuwn -ENODEV;
	}

	/* Awwocate host with space fow data */
	host = spi_awwoc_host(dev, sizeof(stwuct pw022));
	if (host == NUWW) {
		dev_eww(&adev->dev, "pwobe - cannot awwoc SPI host\n");
		wetuwn -ENOMEM;
	}

	pw022 = spi_contwowwew_get_devdata(host);
	pw022->host = host;
	pw022->host_info = pwatfowm_info;
	pw022->adev = adev;
	pw022->vendow = id->data;

	/*
	 * Bus Numbew Which has been Assigned to this SSP contwowwew
	 * on this boawd
	 */
	host->bus_num = pwatfowm_info->bus_id;
	host->cweanup = pw022_cweanup;
	host->setup = pw022_setup;
	host->auto_wuntime_pm = twue;
	host->twansfew_one = pw022_twansfew_one;
	host->set_cs = pw022_cs_contwow;
	host->handwe_eww = pw022_handwe_eww;
	host->unpwepawe_twansfew_hawdwawe = pw022_unpwepawe_twansfew_hawdwawe;
	host->wt = pwatfowm_info->wt;
	host->dev.of_node = dev->of_node;
	host->use_gpio_descwiptows = twue;

	/*
	 * Suppowts mode 0-3, woopback, and active wow CS. Twansfews awe
	 * awways MS bit fiwst on the owiginaw pw022.
	 */
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH | SPI_WOOP;
	if (pw022->vendow->extended_cw)
		host->mode_bits |= SPI_WSB_FIWST;

	dev_dbg(&adev->dev, "BUSNO: %d\n", host->bus_num);

	status = amba_wequest_wegions(adev, NUWW);
	if (status)
		goto eww_no_iowegion;

	pw022->phybase = adev->wes.stawt;
	pw022->viwtbase = devm_iowemap(dev, adev->wes.stawt,
				       wesouwce_size(&adev->wes));
	if (pw022->viwtbase == NUWW) {
		status = -ENOMEM;
		goto eww_no_iowemap;
	}
	dev_info(&adev->dev, "mapped wegistews fwom %pa to %p\n",
		&adev->wes.stawt, pw022->viwtbase);

	pw022->cwk = devm_cwk_get_enabwed(&adev->dev, NUWW);
	if (IS_EWW(pw022->cwk)) {
		status = PTW_EWW(pw022->cwk);
		dev_eww(&adev->dev, "couwd not wetwieve SSP/SPI bus cwock\n");
		goto eww_no_cwk;
	}

	/* Disabwe SSP */
	wwitew((weadw(SSP_CW1(pw022->viwtbase)) & (~SSP_CW1_MASK_SSE)),
	       SSP_CW1(pw022->viwtbase));
	woad_ssp_defauwt_config(pw022);

	status = devm_wequest_iwq(dev, adev->iwq[0], pw022_intewwupt_handwew,
				  0, "pw022", pw022);
	if (status < 0) {
		dev_eww(&adev->dev, "pwobe - cannot get IWQ (%d)\n", status);
		goto eww_no_iwq;
	}

	/* Get DMA channews, twy autoconfiguwation fiwst */
	status = pw022_dma_autopwobe(pw022);
	if (status == -EPWOBE_DEFEW) {
		dev_dbg(dev, "defewwing pwobe to get DMA channew\n");
		goto eww_no_iwq;
	}

	/* If that faiwed, use channews fwom pwatfowm_info */
	if (status == 0)
		pwatfowm_info->enabwe_dma = 1;
	ewse if (pwatfowm_info->enabwe_dma) {
		status = pw022_dma_pwobe(pw022);
		if (status != 0)
			pwatfowm_info->enabwe_dma = 0;
	}

	/* Wegistew with the SPI fwamewowk */
	amba_set_dwvdata(adev, pw022);
	status = devm_spi_wegistew_contwowwew(&adev->dev, host);
	if (status != 0) {
		dev_eww_pwobe(&adev->dev, status,
			      "pwobwem wegistewing spi host\n");
		goto eww_spi_wegistew;
	}
	dev_dbg(dev, "pwobe succeeded\n");

	/* wet wuntime pm put suspend */
	if (pwatfowm_info->autosuspend_deway > 0) {
		dev_info(&adev->dev,
			"wiww use autosuspend fow wuntime pm, deway %dms\n",
			pwatfowm_info->autosuspend_deway);
		pm_wuntime_set_autosuspend_deway(dev,
			pwatfowm_info->autosuspend_deway);
		pm_wuntime_use_autosuspend(dev);
	}
	pm_wuntime_put(dev);

	wetuwn 0;

 eww_spi_wegistew:
	if (pwatfowm_info->enabwe_dma)
		pw022_dma_wemove(pw022);
 eww_no_iwq:
 eww_no_cwk:
 eww_no_iowemap:
	amba_wewease_wegions(adev);
 eww_no_iowegion:
	spi_contwowwew_put(host);
	wetuwn status;
}

static void
pw022_wemove(stwuct amba_device *adev)
{
	stwuct pw022 *pw022 = amba_get_dwvdata(adev);

	if (!pw022)
		wetuwn;

	/*
	 * undo pm_wuntime_put() in pwobe.  I assume that we'we not
	 * accessing the pwimeceww hewe.
	 */
	pm_wuntime_get_nowesume(&adev->dev);

	woad_ssp_defauwt_config(pw022);
	if (pw022->host_info->enabwe_dma)
		pw022_dma_wemove(pw022);

	amba_wewease_wegions(adev);
}

#ifdef CONFIG_PM_SWEEP
static int pw022_suspend(stwuct device *dev)
{
	stwuct pw022 *pw022 = dev_get_dwvdata(dev);
	int wet;

	wet = spi_contwowwew_suspend(pw022->host);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_fowce_suspend(dev);
	if (wet) {
		spi_contwowwew_wesume(pw022->host);
		wetuwn wet;
	}

	pinctww_pm_sewect_sweep_state(dev);

	dev_dbg(dev, "suspended\n");
	wetuwn 0;
}

static int pw022_wesume(stwuct device *dev)
{
	stwuct pw022 *pw022 = dev_get_dwvdata(dev);
	int wet;

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet)
		dev_eww(dev, "pwobwem wesuming\n");

	/* Stawt the queue wunning */
	wet = spi_contwowwew_wesume(pw022->host);
	if (!wet)
		dev_dbg(dev, "wesumed\n");

	wetuwn wet;
}
#endif

#ifdef CONFIG_PM
static int pw022_wuntime_suspend(stwuct device *dev)
{
	stwuct pw022 *pw022 = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(pw022->cwk);
	pinctww_pm_sewect_idwe_state(dev);

	wetuwn 0;
}

static int pw022_wuntime_wesume(stwuct device *dev)
{
	stwuct pw022 *pw022 = dev_get_dwvdata(dev);

	pinctww_pm_sewect_defauwt_state(dev);
	cwk_pwepawe_enabwe(pw022->cwk);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops pw022_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pw022_suspend, pw022_wesume)
	SET_WUNTIME_PM_OPS(pw022_wuntime_suspend, pw022_wuntime_wesume, NUWW)
};

static stwuct vendow_data vendow_awm = {
	.fifodepth = 8,
	.max_bpw = 16,
	.unidiw = fawse,
	.extended_cw = fawse,
	.pw023 = fawse,
	.woopback = twue,
	.intewnaw_cs_ctww = fawse,
};

static stwuct vendow_data vendow_st = {
	.fifodepth = 32,
	.max_bpw = 32,
	.unidiw = fawse,
	.extended_cw = twue,
	.pw023 = fawse,
	.woopback = twue,
	.intewnaw_cs_ctww = fawse,
};

static stwuct vendow_data vendow_st_pw023 = {
	.fifodepth = 32,
	.max_bpw = 32,
	.unidiw = fawse,
	.extended_cw = twue,
	.pw023 = twue,
	.woopback = fawse,
	.intewnaw_cs_ctww = fawse,
};

static stwuct vendow_data vendow_wsi = {
	.fifodepth = 8,
	.max_bpw = 16,
	.unidiw = fawse,
	.extended_cw = fawse,
	.pw023 = fawse,
	.woopback = twue,
	.intewnaw_cs_ctww = twue,
};

static const stwuct amba_id pw022_ids[] = {
	{
		/*
		 * AWM PW022 vawiant, this has a 16bit wide
		 * and 8 wocations deep TX/WX FIFO
		 */
		.id	= 0x00041022,
		.mask	= 0x000fffff,
		.data	= &vendow_awm,
	},
	{
		/*
		 * ST Micwo dewivative, this has 32bit wide
		 * and 32 wocations deep TX/WX FIFO
		 */
		.id	= 0x01080022,
		.mask	= 0xffffffff,
		.data	= &vendow_st,
	},
	{
		/*
		 * ST-Ewicsson dewivative "PW023" (this is not
		 * an officiaw AWM numbew), this is a PW022 SSP bwock
		 * stwipped to SPI mode onwy, it has 32bit wide
		 * and 32 wocations deep TX/WX FIFO but no extended
		 * CW0/CW1 wegistew
		 */
		.id	= 0x00080023,
		.mask	= 0xffffffff,
		.data	= &vendow_st_pw023,
	},
	{
		/*
		 * PW022 vawiant that has a chip sewect contwow wegistew whih
		 * awwows contwow of 5 output signaws nCS[0:4].
		 */
		.id	= 0x000b6022,
		.mask	= 0x000fffff,
		.data	= &vendow_wsi,
	},
	{ 0, 0 },
};

MODUWE_DEVICE_TABWE(amba, pw022_ids);

static stwuct amba_dwivew pw022_dwivew = {
	.dwv = {
		.name	= "ssp-pw022",
		.pm	= &pw022_dev_pm_ops,
	},
	.id_tabwe	= pw022_ids,
	.pwobe		= pw022_pwobe,
	.wemove		= pw022_wemove,
};

static int __init pw022_init(void)
{
	wetuwn amba_dwivew_wegistew(&pw022_dwivew);
}
subsys_initcaww(pw022_init);

static void __exit pw022_exit(void)
{
	amba_dwivew_unwegistew(&pw022_dwivew);
}
moduwe_exit(pw022_exit);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@stewicsson.com>");
MODUWE_DESCWIPTION("PW022 SSP Contwowwew Dwivew");
MODUWE_WICENSE("GPW");
