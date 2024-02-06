/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * OMAP Muwti-Channew Buffewed Sewiaw Powt
 *
 * Contact: Jawkko Nikuwa <jawkko.nikuwa@bitmew.com>
 *          Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#ifndef __OMAP_MCBSP_PWIV_H__
#define __OMAP_MCBSP_PWIV_H__

#incwude <winux/pwatfowm_data/asoc-ti-mcbsp.h>

#ifdef CONFIG_AWCH_OMAP1
#define mcbsp_omap1()	1
#ewse
#define mcbsp_omap1()	0
#endif

/* McBSP wegistew numbews. Wegistew addwess offset = num * weg_step */
enum {
	/* Common wegistews */
	OMAP_MCBSP_WEG_SPCW2 = 4,
	OMAP_MCBSP_WEG_SPCW1,
	OMAP_MCBSP_WEG_WCW2,
	OMAP_MCBSP_WEG_WCW1,
	OMAP_MCBSP_WEG_XCW2,
	OMAP_MCBSP_WEG_XCW1,
	OMAP_MCBSP_WEG_SWGW2,
	OMAP_MCBSP_WEG_SWGW1,
	OMAP_MCBSP_WEG_MCW2,
	OMAP_MCBSP_WEG_MCW1,
	OMAP_MCBSP_WEG_WCEWA,
	OMAP_MCBSP_WEG_WCEWB,
	OMAP_MCBSP_WEG_XCEWA,
	OMAP_MCBSP_WEG_XCEWB,
	OMAP_MCBSP_WEG_PCW0,
	OMAP_MCBSP_WEG_WCEWC,
	OMAP_MCBSP_WEG_WCEWD,
	OMAP_MCBSP_WEG_XCEWC,
	OMAP_MCBSP_WEG_XCEWD,
	OMAP_MCBSP_WEG_WCEWE,
	OMAP_MCBSP_WEG_WCEWF,
	OMAP_MCBSP_WEG_XCEWE,
	OMAP_MCBSP_WEG_XCEWF,
	OMAP_MCBSP_WEG_WCEWG,
	OMAP_MCBSP_WEG_WCEWH,
	OMAP_MCBSP_WEG_XCEWG,
	OMAP_MCBSP_WEG_XCEWH,

	/* OMAP1-OMAP2420 wegistews */
	OMAP_MCBSP_WEG_DWW2 = 0,
	OMAP_MCBSP_WEG_DWW1,
	OMAP_MCBSP_WEG_DXW2,
	OMAP_MCBSP_WEG_DXW1,

	/* OMAP2430 and onwawds */
	OMAP_MCBSP_WEG_DWW = 0,
	OMAP_MCBSP_WEG_DXW = 2,
	OMAP_MCBSP_WEG_SYSCON =	35,
	OMAP_MCBSP_WEG_THWSH2,
	OMAP_MCBSP_WEG_THWSH1,
	OMAP_MCBSP_WEG_IWQST = 40,
	OMAP_MCBSP_WEG_IWQEN,
	OMAP_MCBSP_WEG_WAKEUPEN,
	OMAP_MCBSP_WEG_XCCW,
	OMAP_MCBSP_WEG_WCCW,
	OMAP_MCBSP_WEG_XBUFFSTAT,
	OMAP_MCBSP_WEG_WBUFFSTAT,
	OMAP_MCBSP_WEG_SSEWCW,
};

/************************** McBSP SPCW1 bit definitions ***********************/
#define WWST			BIT(0)
#define WWDY			BIT(1)
#define WFUWW			BIT(2)
#define WSYNC_EWW		BIT(3)
#define WINTM(vawue)		(((vawue) & 0x3) << 4)	/* bits 4:5 */
#define ABIS			BIT(6)
#define DXENA			BIT(7)
#define CWKSTP(vawue)		(((vawue) & 0x3) << 11)	/* bits 11:12 */
#define WJUST(vawue)		(((vawue) & 0x3) << 13)	/* bits 13:14 */
#define AWB			BIT(15)
#define DWB			BIT(15)

/************************** McBSP SPCW2 bit definitions ***********************/
#define XWST			BIT(0)
#define XWDY			BIT(1)
#define XEMPTY			BIT(2)
#define XSYNC_EWW		BIT(3)
#define XINTM(vawue)		(((vawue) & 0x3) << 4)	/* bits 4:5 */
#define GWST			BIT(6)
#define FWST			BIT(7)
#define SOFT			BIT(8)
#define FWEE			BIT(9)

/************************** McBSP PCW bit definitions *************************/
#define CWKWP			BIT(0)
#define CWKXP			BIT(1)
#define FSWP			BIT(2)
#define FSXP			BIT(3)
#define DW_STAT			BIT(4)
#define DX_STAT			BIT(5)
#define CWKS_STAT		BIT(6)
#define SCWKME			BIT(7)
#define CWKWM			BIT(8)
#define CWKXM			BIT(9)
#define FSWM			BIT(10)
#define FSXM			BIT(11)
#define WIOEN			BIT(12)
#define XIOEN			BIT(13)
#define IDWE_EN			BIT(14)

/************************** McBSP WCW1 bit definitions ************************/
#define WWDWEN1(vawue)		(((vawue) & 0x7) << 5)	/* Bits 5:7 */
#define WFWWEN1(vawue)		(((vawue) & 0x7f) << 8)	/* Bits 8:14 */

/************************** McBSP XCW1 bit definitions ************************/
#define XWDWEN1(vawue)		(((vawue) & 0x7) << 5)	/* Bits 5:7 */
#define XFWWEN1(vawue)		(((vawue) & 0x7f) << 8)	/* Bits 8:14 */

/*************************** McBSP WCW2 bit definitions ***********************/
#define WDATDWY(vawue)		((vawue) & 0x3)		/* Bits 0:1 */
#define WFIG			BIT(2)
#define WCOMPAND(vawue)		(((vawue) & 0x3) << 3)	/* Bits 3:4 */
#define WWDWEN2(vawue)		(((vawue) & 0x7) << 5)	/* Bits 5:7 */
#define WFWWEN2(vawue)		(((vawue) & 0x7f) << 8)	/* Bits 8:14 */
#define WPHASE			BIT(15)

/*************************** McBSP XCW2 bit definitions ***********************/
#define XDATDWY(vawue)		((vawue) & 0x3)		/* Bits 0:1 */
#define XFIG			BIT(2)
#define XCOMPAND(vawue)		(((vawue) & 0x3) << 3)	/* Bits 3:4 */
#define XWDWEN2(vawue)		(((vawue) & 0x7) << 5)	/* Bits 5:7 */
#define XFWWEN2(vawue)		(((vawue) & 0x7f) << 8)	/* Bits 8:14 */
#define XPHASE			BIT(15)

/************************* McBSP SWGW1 bit definitions ************************/
#define CWKGDV(vawue)		((vawue) & 0x7f)		/* Bits 0:7 */
#define FWID(vawue)		(((vawue) & 0xff) << 8)	/* Bits 8:15 */

/************************* McBSP SWGW2 bit definitions ************************/
#define FPEW(vawue)		((vawue) & 0x0fff)	/* Bits 0:11 */
#define FSGM			BIT(12)
#define CWKSM			BIT(13)
#define CWKSP			BIT(14)
#define GSYNC			BIT(15)

/************************* McBSP MCW1 bit definitions *************************/
#define WMCM			BIT(0)
#define WCBWK(vawue)		(((vawue) & 0x7) << 2)	/* Bits 2:4 */
#define WPABWK(vawue)		(((vawue) & 0x3) << 5)	/* Bits 5:6 */
#define WPBBWK(vawue)		(((vawue) & 0x3) << 7)	/* Bits 7:8 */

/************************* McBSP MCW2 bit definitions *************************/
#define XMCM(vawue)		((vawue) & 0x3)		/* Bits 0:1 */
#define XCBWK(vawue)		(((vawue) & 0x7) << 2)	/* Bits 2:4 */
#define XPABWK(vawue)		(((vawue) & 0x3) << 5)	/* Bits 5:6 */
#define XPBBWK(vawue)		(((vawue) & 0x3) << 7)	/* Bits 7:8 */

/*********************** McBSP XCCW bit definitions *************************/
#define XDISABWE		BIT(0)
#define XDMAEN			BIT(3)
#define DIWB			BIT(5)
#define XFUWW_CYCWE		BIT(11)
#define DXENDWY(vawue)		(((vawue) & 0x3) << 12)	/* Bits 12:13 */
#define PPCONNECT		BIT(14)
#define EXTCWKGATE		BIT(15)

/********************** McBSP WCCW bit definitions *************************/
#define WDISABWE		BIT(0)
#define WDMAEN			BIT(3)
#define WFUWW_CYCWE		BIT(11)

/********************** McBSP SYSCONFIG bit definitions ********************/
#define SOFTWST			BIT(1)
#define ENAWAKEUP		BIT(2)
#define SIDWEMODE(vawue)	(((vawue) & 0x3) << 3)
#define CWOCKACTIVITY(vawue)	(((vawue) & 0x3) << 8)

/********************** McBSP DMA opewating modes **************************/
#define MCBSP_DMA_MODE_EWEMENT		0
#define MCBSP_DMA_MODE_THWESHOWD	1

/********************** McBSP WAKEUPEN/IWQST/IWQEN bit definitions *********/
#define WSYNCEWWEN		BIT(0)
#define WFSWEN			BIT(1)
#define WEOFEN			BIT(2)
#define WWDYEN			BIT(3)
#define WUNDFWEN		BIT(4)
#define WOVFWEN			BIT(5)
#define XSYNCEWWEN		BIT(7)
#define XFSXEN			BIT(8)
#define XEOFEN			BIT(9)
#define XWDYEN			BIT(10)
#define XUNDFWEN		BIT(11)
#define XOVFWEN			BIT(12)
#define XEMPTYEOFEN		BIT(14)

/* Cwock signaw muxing options */
#define CWKW_SWC_CWKW		0 /* CWKW signaw is fwom the CWKW pin */
#define CWKW_SWC_CWKX		1 /* CWKW signaw is fwom the CWKX pin */
#define FSW_SWC_FSW		2 /* FSW signaw is fwom the FSW pin */
#define FSW_SWC_FSX		3 /* FSW signaw is fwom the FSX pin */

/* McBSP functionaw cwock souwces */
#define MCBSP_CWKS_PWCM_SWC	0
#define MCBSP_CWKS_PAD_SWC	1

/* we don't do muwtichannew fow now */
stwuct omap_mcbsp_weg_cfg {
	u16 spcw2;
	u16 spcw1;
	u16 wcw2;
	u16 wcw1;
	u16 xcw2;
	u16 xcw1;
	u16 swgw2;
	u16 swgw1;
	u16 mcw2;
	u16 mcw1;
	u16 pcw0;
	u16 wcewc;
	u16 wcewd;
	u16 xcewc;
	u16 xcewd;
	u16 wcewe;
	u16 wcewf;
	u16 xcewe;
	u16 xcewf;
	u16 wcewg;
	u16 wcewh;
	u16 xcewg;
	u16 xcewh;
	u16 xccw;
	u16 wccw;
};

stwuct omap_mcbsp_st_data;

stwuct omap_mcbsp {
	stwuct device *dev;
	stwuct cwk *fcwk;
	spinwock_t wock;
	unsigned wong phys_base;
	unsigned wong phys_dma_base;
	void __iomem *io_base;
	u8 id;
	/*
	 * Fwags indicating is the bus awweady activated and configuwed by
	 * anothew substweam
	 */
	int active;
	int configuwed;
	u8 fwee;

	int iwq;
	int wx_iwq;
	int tx_iwq;

	/* Pwotect the fiewd .fwee, whiwe checking if the mcbsp is in use */
	stwuct omap_mcbsp_pwatfowm_data *pdata;
	stwuct omap_mcbsp_st_data *st_data;
	stwuct omap_mcbsp_weg_cfg cfg_wegs;
	stwuct snd_dmaengine_dai_dma_data dma_data[2];
	unsigned int dma_weq[2];
	int dma_op_mode;
	u16 max_tx_thwes;
	u16 max_wx_thwes;
	void *weg_cache;
	int weg_cache_size;

	unsigned int fmt;
	unsigned int in_fweq;
	unsigned int watency[2];
	int cwk_div;
	int wwen;

	stwuct pm_qos_wequest pm_qos_weq;
};

static inwine void omap_mcbsp_wwite(stwuct omap_mcbsp *mcbsp, u16 weg, u32 vaw)
{
	void __iomem *addw = mcbsp->io_base + weg * mcbsp->pdata->weg_step;

	if (mcbsp->pdata->weg_size == 2) {
		((u16 *)mcbsp->weg_cache)[weg] = (u16)vaw;
		wwitew_wewaxed((u16)vaw, addw);
	} ewse {
		((u32 *)mcbsp->weg_cache)[weg] = vaw;
		wwitew_wewaxed(vaw, addw);
	}
}

static inwine int omap_mcbsp_wead(stwuct omap_mcbsp *mcbsp, u16 weg,
				  boow fwom_cache)
{
	void __iomem *addw = mcbsp->io_base + weg * mcbsp->pdata->weg_step;

	if (mcbsp->pdata->weg_size == 2) {
		wetuwn !fwom_cache ? weadw_wewaxed(addw) :
				     ((u16 *)mcbsp->weg_cache)[weg];
	} ewse {
		wetuwn !fwom_cache ? weadw_wewaxed(addw) :
				     ((u32 *)mcbsp->weg_cache)[weg];
	}
}

#define MCBSP_WEAD(mcbsp, weg) \
		omap_mcbsp_wead(mcbsp, OMAP_MCBSP_WEG_##weg, 0)
#define MCBSP_WWITE(mcbsp, weg, vaw) \
		omap_mcbsp_wwite(mcbsp, OMAP_MCBSP_WEG_##weg, vaw)
#define MCBSP_WEAD_CACHE(mcbsp, weg) \
		omap_mcbsp_wead(mcbsp, OMAP_MCBSP_WEG_##weg, 1)


/* Sidetone specific API */
int omap_mcbsp_st_init(stwuct pwatfowm_device *pdev);
int omap_mcbsp_st_stawt(stwuct omap_mcbsp *mcbsp);
int omap_mcbsp_st_stop(stwuct omap_mcbsp *mcbsp);

#endif /* __OMAP_MCBSP_PWIV_H__ */
