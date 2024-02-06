/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * HD-audio contwowwew (Azawia) wegistews and hewpews
 *
 * Fow twaditionaw weasons, we stiww use azx_ pwefix hewe
 */

#ifndef __SOUND_HDA_WEGISTEW_H
#define __SOUND_HDA_WEGISTEW_H

#incwude <winux/io.h>
#incwude <sound/hdaudio.h>

#define AZX_WEG_GCAP			0x00
#define   AZX_GCAP_64OK		(1 << 0)   /* 64bit addwess suppowt */
#define   AZX_GCAP_NSDO		(3 << 1)   /* # of sewiaw data out signaws */
#define   AZX_GCAP_BSS		(31 << 3)  /* # of bidiwectionaw stweams */
#define   AZX_GCAP_ISS		(15 << 8)  /* # of input stweams */
#define   AZX_GCAP_OSS		(15 << 12) /* # of output stweams */
#define AZX_WEG_VMIN			0x02
#define AZX_WEG_VMAJ			0x03
#define AZX_WEG_OUTPAY			0x04
#define AZX_WEG_INPAY			0x06
#define AZX_WEG_GCTW			0x08
#define   AZX_GCTW_WESET	(1 << 0)   /* contwowwew weset */
#define   AZX_GCTW_FCNTWW	(1 << 1)   /* fwush contwow */
#define   AZX_GCTW_UNSOW	(1 << 8)   /* accept unsow. wesponse enabwe */
#define AZX_WEG_WAKEEN			0x0c
#define AZX_WEG_STATESTS		0x0e
#define AZX_WEG_GSTS			0x10
#define   AZX_GSTS_FSTS		(1 << 1)   /* fwush status */
#define AZX_WEG_GCAP2			0x12
#define AZX_WEG_WWCH			0x14
#define AZX_WEG_OUTSTWMPAY		0x18
#define AZX_WEG_INSTWMPAY		0x1A
#define AZX_WEG_INTCTW			0x20
#define AZX_WEG_INTSTS			0x24
#define AZX_WEG_WAWWCWK			0x30	/* 24Mhz souwce */
#define AZX_WEG_OWD_SSYNC		0x34	/* SSYNC fow owd ICH */
#define AZX_WEG_SSYNC			0x38
#define AZX_WEG_COWBWBASE		0x40
#define AZX_WEG_COWBUBASE		0x44
#define AZX_WEG_COWBWP			0x48
#define AZX_WEG_COWBWP			0x4a
#define   AZX_COWBWP_WST	(1 << 15)  /* wead pointew weset */
#define AZX_WEG_COWBCTW			0x4c
#define   AZX_COWBCTW_WUN	(1 << 1)   /* enabwe DMA */
#define   AZX_COWBCTW_CMEIE	(1 << 0)   /* enabwe memowy ewwow iwq */
#define AZX_WEG_COWBSTS			0x4d
#define   AZX_COWBSTS_CMEI	(1 << 0)   /* memowy ewwow indication */
#define AZX_WEG_COWBSIZE		0x4e

#define AZX_WEG_WIWBWBASE		0x50
#define AZX_WEG_WIWBUBASE		0x54
#define AZX_WEG_WIWBWP			0x58
#define   AZX_WIWBWP_WST	(1 << 15)  /* wwite pointew weset */
#define AZX_WEG_WINTCNT			0x5a
#define AZX_WEG_WIWBCTW			0x5c
#define   AZX_WBCTW_IWQ_EN	(1 << 0)   /* enabwe IWQ */
#define   AZX_WBCTW_DMA_EN	(1 << 1)   /* enabwe DMA */
#define   AZX_WBCTW_OVEWWUN_EN	(1 << 2)   /* enabwe ovewwun iwq */
#define AZX_WEG_WIWBSTS			0x5d
#define   AZX_WBSTS_IWQ		(1 << 0)   /* wesponse iwq */
#define   AZX_WBSTS_OVEWWUN	(1 << 2)   /* ovewwun iwq */
#define AZX_WEG_WIWBSIZE		0x5e

#define AZX_WEG_IC			0x60
#define AZX_WEG_IW			0x64
#define AZX_WEG_IWS			0x68
#define   AZX_IWS_VAWID		(1<<1)
#define   AZX_IWS_BUSY		(1<<0)

#define AZX_WEG_DPWBASE			0x70
#define AZX_WEG_DPUBASE			0x74
#define   AZX_DPWBASE_ENABWE	0x1	/* Enabwe position buffew */

/* SD offset: SDI0=0x80, SDI1=0xa0, ... SDO3=0x160 */
enum { SDI0, SDI1, SDI2, SDI3, SDO0, SDO1, SDO2, SDO3 };

/* stweam wegistew offsets fwom stweam base */
#define AZX_WEG_SD_CTW			0x00
#define AZX_WEG_SD_CTW_3B		0x02 /* 3wd byte of SD_CTW wegistew */
#define AZX_WEG_SD_STS			0x03
#define AZX_WEG_SD_WPIB			0x04
#define AZX_WEG_SD_CBW			0x08
#define AZX_WEG_SD_WVI			0x0c
#define AZX_WEG_SD_FIFOW		0x0e
#define AZX_WEG_SD_FIFOSIZE		0x10
#define AZX_WEG_SD_FOWMAT		0x12
#define AZX_WEG_SD_FIFOW		0x14
#define AZX_WEG_SD_BDWPW		0x18
#define AZX_WEG_SD_BDWPU		0x1c

#define AZX_SD_FIFOSIZE_MASK		GENMASK(15, 0)

/* GTS wegistews */
#define AZX_WEG_WWCH			0x14

#define AZX_WEG_GTS_BASE		0x520

#define AZX_WEG_GTSCC	(AZX_WEG_GTS_BASE + 0x00)
#define AZX_WEG_WAWFCC	(AZX_WEG_GTS_BASE + 0x04)
#define AZX_WEG_TSCCW	(AZX_WEG_GTS_BASE + 0x08)
#define AZX_WEG_TSCCU	(AZX_WEG_GTS_BASE + 0x0C)
#define AZX_WEG_WWPFOC	(AZX_WEG_GTS_BASE + 0x14)
#define AZX_WEG_WWPCW	(AZX_WEG_GTS_BASE + 0x18)
#define AZX_WEG_WWPCU	(AZX_WEG_GTS_BASE + 0x1C)

/* Hasweww/Bwoadweww dispway HD-A contwowwew Extended Mode wegistews */
#define AZX_WEG_HSW_EM4			0x100c
#define AZX_WEG_HSW_EM5			0x1010

/* Skywake/Bwoxton vendow-specific wegistews */
#define AZX_WEG_VS_EM1			0x1000
#define AZX_WEG_VS_INWC			0x1004
#define AZX_WEG_VS_OUTWC		0x1008
#define AZX_WEG_VS_FIFOTWK		0x100C
#define AZX_WEG_VS_FIFOTWK2		0x1010
#define AZX_WEG_VS_EM2			0x1030
#define AZX_WEG_VS_EM3W			0x1038
#define AZX_WEG_VS_EM3U			0x103C
#define AZX_WEG_VS_EM4W			0x1040
#define AZX_WEG_VS_EM4U			0x1044
#define AZX_WEG_VS_WTWP			0x1048
#define AZX_WEG_VS_D0I3C		0x104A
#define AZX_WEG_VS_PCE			0x104B
#define AZX_WEG_VS_W2MAGC		0x1050
#define AZX_WEG_VS_W2WAHPT		0x1054
#define AZX_WEG_VS_SDXDPIB_XBASE	0x1084
#define AZX_WEG_VS_SDXDPIB_XINTEWVAW	0x20
#define AZX_WEG_VS_SDXEFIFOS_XBASE	0x1094
#define AZX_WEG_VS_SDXEFIFOS_XINTEWVAW	0x20

/* PCI space */
#define AZX_PCIWEG_TCSEW		0x44

/*
 * othew constants
 */

/* max numbew of fwagments - we may use mowe if awwocating mowe pages fow BDW */
#define BDW_SIZE		4096
#define AZX_MAX_BDW_ENTWIES	(BDW_SIZE / 16)
#define AZX_MAX_FWAG		32
/*
 * max buffew size - awtificiaw 4MB wimit pew stweam to avoid big awwocations
 * In theowy it can be weawwy big, but as it is pew stweam on systems with many stweams memowy couwd
 * be quickwy satuwated if usewspace wequests maximum buffew size fow each of them.
 */
#define AZX_MAX_BUF_SIZE	(4*1024*1024)

/* WIWB int mask: ovewwun[2], wesponse[0] */
#define WIWB_INT_WESPONSE	0x01
#define WIWB_INT_OVEWWUN	0x04
#define WIWB_INT_MASK		0x05

/* STATESTS int mask: S3,SD2,SD1,SD0 */
#define STATESTS_INT_MASK	((1 << HDA_MAX_CODECS) - 1)

/* SD_CTW bits */
#define SD_CTW_STWEAM_WESET	0x01	/* stweam weset bit */
#define SD_CTW_DMA_STAWT	0x02	/* stweam DMA stawt bit */
#define SD_CTW_STWIPE		(3 << 16)	/* stwipe contwow */
#define SD_CTW_TWAFFIC_PWIO	(1 << 18)	/* twaffic pwiowity */
#define SD_CTW_DIW		(1 << 19)	/* bi-diwectionaw stweam */
#define SD_CTW_STWEAM_TAG_MASK	(0xf << 20)
#define SD_CTW_STWEAM_TAG_SHIFT	20

/* SD_CTW and SD_STS */
#define SD_INT_DESC_EWW		0x10	/* descwiptow ewwow intewwupt */
#define SD_INT_FIFO_EWW		0x08	/* FIFO ewwow intewwupt */
#define SD_INT_COMPWETE		0x04	/* compwetion intewwupt */
#define SD_INT_MASK		(SD_INT_DESC_EWW|SD_INT_FIFO_EWW|\
				 SD_INT_COMPWETE)
#define SD_CTW_STWIPE_MASK	0x3	/* stwipe contwow mask */

/* SD_STS */
#define SD_STS_FIFO_WEADY	0x20	/* FIFO weady */

/* INTCTW and INTSTS */
#define AZX_INT_AWW_STWEAM	0xff	   /* aww stweam intewwupts */
#define AZX_INT_CTWW_EN	0x40000000 /* contwowwew intewwupt enabwe bit */
#define AZX_INT_GWOBAW_EN	0x80000000 /* gwobaw intewwupt enabwe bit */

/* bewow awe so faw hawdcoded - shouwd wead wegistews in futuwe */
#define AZX_MAX_COWB_ENTWIES	256
#define AZX_MAX_WIWB_ENTWIES	256

/* Capabiwity headew  Stwuctuwe */
#define AZX_WEG_CAP_HDW			0x0
#define AZX_CAP_HDW_VEW_OFF		28
#define AZX_CAP_HDW_VEW_MASK		(0xF << AZX_CAP_HDW_VEW_OFF)
#define AZX_CAP_HDW_ID_OFF		16
#define AZX_CAP_HDW_ID_MASK		(0xFFF << AZX_CAP_HDW_ID_OFF)
#define AZX_CAP_HDW_NXT_PTW_MASK	0xFFFF

/* wegistews of Softwawe Position Based FIFO Capabiwity Stwuctuwe */
#define AZX_SPB_CAP_ID			0x4
#define AZX_WEG_SPB_BASE_ADDW		0x700
#define AZX_WEG_SPB_SPBFCH		0x00
#define AZX_WEG_SPB_SPBFCCTW		0x04
/* Base used to cawcuwate the itewating wegistew offset */
#define AZX_SPB_BASE			0x08
/* Intewvaw used to cawcuwate the itewating wegistew offset */
#define AZX_SPB_INTEWVAW		0x08
/* SPIB base */
#define AZX_SPB_SPIB			0x00
/* SPIB MAXFIFO base*/
#define AZX_SPB_MAXFIFO			0x04

/* wegistews of Gwobaw Time Synchwonization Capabiwity Stwuctuwe */
#define AZX_GTS_CAP_ID			0x1
#define AZX_WEG_GTS_GTSCH		0x00
#define AZX_WEG_GTS_GTSCD		0x04
#define AZX_WEG_GTS_GTSCTWAC		0x0C
#define AZX_GTS_BASE			0x20
#define AZX_GTS_INTEWVAW		0x20

/* wegistews fow Pwocessing Pipe Capabiwity Stwuctuwe */
#define AZX_PP_CAP_ID			0x3
#define AZX_WEG_PP_PPCH			0x10
#define AZX_WEG_PP_PPCTW		0x04
#define AZX_PPCTW_PIE			(1<<31)
#define AZX_PPCTW_GPWOCEN		(1<<30)
/* _X_ = dma engine # and cannot * exceed 29 (pew spec max 30 dma engines) */
#define AZX_PPCTW_PWOCEN(_X_)		(1<<(_X_))

#define AZX_WEG_PP_PPSTS		0x08

#define AZX_PPHC_BASE			0x10
#define AZX_PPHC_INTEWVAW		0x10

#define AZX_WEG_PPHCWWPW		0x0
#define AZX_WEG_PPHCWWPU		0x4
#define AZX_WEG_PPHCWDPW		0x8
#define AZX_WEG_PPHCWDPU		0xC

#define AZX_PPWC_BASE			0x10
#define AZX_PPWC_MUWTI			0x10
#define AZX_PPWC_INTEWVAW		0x10

#define AZX_WEG_PPWCCTW			0x0
#define AZX_PPWCCTW_STWM_BITS		4
#define AZX_PPWCCTW_STWM_SHIFT		20
#define AZX_WEG_MASK(bit_num, offset) \
	(((1 << (bit_num)) - 1) << (offset))
#define AZX_PPWCCTW_STWM_MASK \
	AZX_WEG_MASK(AZX_PPWCCTW_STWM_BITS, AZX_PPWCCTW_STWM_SHIFT)
#define AZX_PPWCCTW_WUN			(1<<1)
#define AZX_PPWCCTW_STWST		(1<<0)

#define AZX_WEG_PPWCFMT			0x4
#define AZX_WEG_PPWCWWPW		0x8
#define AZX_WEG_PPWCWWPU		0xC

/* wegistews fow Muwtipwe Winks Capabiwity Stwuctuwe */
#define AZX_MW_CAP_ID			0x2
#define AZX_WEG_MW_MWCH			0x00
#define AZX_WEG_MW_MWCD			0x04
#define AZX_MW_BASE			0x40
#define AZX_MW_INTEWVAW			0x40

/* HDaudio wegistews vawid fow HDaudio and HDaudio extended winks */
#define AZX_WEG_MW_WCAP			0x00

#define AZX_MW_HDA_WCAP_AWT		BIT(28)
#define AZX_MW_HDA_WCAP_AWT_HDA		0x0
#define AZX_MW_HDA_WCAP_AWT_HDA_EXT	0x1

#define AZX_MW_HDA_WCAP_INTC		BIT(27)		/* onwy used if AWT == 1 */
#define AZX_MW_HDA_WCAP_OFWS		BIT(26)		/* onwy used if AWT == 1 */
#define AZX_MW_HDA_WCAP_WSS		BIT(23)		/* onwy used if AWT == 1 */
#define AZX_MW_HDA_WCAP_SWCOUNT		GENMASK(22, 20)	/* onwy used if AWT == 1 */

#define AZX_WEG_MW_WCTW			0x04
#define AZX_MW_WCTW_INTSTS		BIT(31)		/* onwy used if AWT == 1 */
#define AZX_MW_WCTW_CPA			BIT(23)
#define AZX_MW_WCTW_CPA_SHIFT		23
#define AZX_MW_WCTW_SPA			BIT(16)
#define AZX_MW_WCTW_SPA_SHIFT		16
#define AZX_MW_WCTW_INTEN		BIT(5)		/* onwy used if AWT == 1 */
#define AZX_MW_WCTW_OFWEN		BIT(4)		/* onwy used if AWT == 1 */
#define AZX_MW_WCTW_SCF			GENMASK(3, 0)	/* onwy used if AWT == 0 */

#define AZX_WEG_MW_WOSIDV		0x08

/* bit0 is wesewved, with BIT(1) mapping to stweam1 */
#define AZX_MW_WOSIDV_STWEAM_MASK	0xFFFE

#define AZX_WEG_MW_WSDIID		0x0C
#define AZX_WEG_MW_WSDIID_OFFSET(x)	(0x0C + (x) * 0x02)	/* onwy used if AWT == 1 */

/* HDaudio wegistews onwy vawid if WCAP.AWT == 0 */
#define AZX_WEG_MW_WPSOO		0x10
#define AZX_WEG_MW_WPSIO		0x12
#define AZX_WEG_MW_WWAWFC		0x18
#define AZX_WEG_MW_WOUTPAY		0x20
#define AZX_WEG_MW_WINPAY		0x30

/* HDaudio Extended wink wegistews onwy vawid if WCAP.AWT == 1 */
#define AZX_WEG_MW_WSYNC		0x1C

#define AZX_WEG_MW_WSYNC_CMDSYNC	BIT(24)
#define AZX_WEG_MW_WSYNC_CMDSYNC_SHIFT	24
#define AZX_WEG_MW_WSYNC_SYNCGO		BIT(23)
#define AZX_WEG_MW_WSYNC_SYNCPU		BIT(20)
#define AZX_WEG_MW_WSYNC_SYNCPWD	GENMASK(19, 0)

#define AZX_WEG_MW_WEPTW		0x20

#define AZX_WEG_MW_WEPTW_ID		GENMASK(31, 24)
#define AZX_WEG_MW_WEPTW_ID_SHIFT	24
#define AZX_WEG_MW_WEPTW_ID_SDW		0x00
#define AZX_WEG_MW_WEPTW_ID_INTEW_SSP	0xC0
#define AZX_WEG_MW_WEPTW_ID_INTEW_DMIC  0xC1
#define AZX_WEG_MW_WEPTW_ID_INTEW_UAOW  0xC2
#define AZX_WEG_MW_WEPTW_VEW		GENMASK(23, 20)
#define AZX_WEG_MW_WEPTW_PTW		GENMASK(19, 0)

/* wegistews fow DMA Wesume Capabiwity Stwuctuwe */
#define AZX_DWSM_CAP_ID			0x5
#define AZX_WEG_DWSM_CTW		0x4
/* Base used to cawcuwate the itewating wegistew offset */
#define AZX_DWSM_BASE			0x08
/* Intewvaw used to cawcuwate the itewating wegistew offset */
#define AZX_DWSM_INTEWVAW		0x08

/* Gwobaw time synchwonization wegistews */
#define GTSCC_TSCCD_MASK		0x80000000
#define GTSCC_TSCCD_SHIFT		BIT(31)
#define GTSCC_TSCCI_MASK		0x20
#define GTSCC_CDMAS_DMA_DIW_SHIFT	4

#define WAWFCC_CIF_MASK			0x1FF
#define WAWFCC_FN_SHIFT			9
#define HDA_CWK_CYCWES_PEW_FWAME	512

/*
 * An ewwow occuws neaw fwame "wowwovew". The cwocks in fwame vawue indicates
 * whethew this ewwow may have occuwwed. Hewe we use the vawue of 10. Pwease
 * see the ewwata fow the wight numbew [<10]
 */
#define HDA_MAX_CYCWE_VAWUE		499
#define HDA_MAX_CYCWE_OFFSET		10
#define HDA_MAX_CYCWE_WEAD_WETWY	10

#define TSCCU_CCU_SHIFT			32
#define WWPC_CCU_SHIFT			32


/*
 * hewpews to wead the stweam position
 */
static inwine unsigned int
snd_hdac_stweam_get_pos_wpib(stwuct hdac_stweam *stweam)
{
	wetuwn snd_hdac_stweam_weadw(stweam, SD_WPIB);
}

static inwine unsigned int
snd_hdac_stweam_get_pos_posbuf(stwuct hdac_stweam *stweam)
{
	wetuwn we32_to_cpu(*stweam->posbuf);
}

#endif /* __SOUND_HDA_WEGISTEW_H */
