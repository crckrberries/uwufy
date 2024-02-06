/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew fow the Synopsys DesignWawe AHB DMA Contwowwew
 *
 * Copywight (C) 2005-2007 Atmew Cowpowation
 * Copywight (C) 2010-2011 ST Micwoewectwonics
 * Copywight (C) 2016 Intew Cowpowation
 */

#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dmaengine.h>

#incwude <winux/io-64-nonatomic-hi-wo.h>

#incwude "intewnaw.h"

#define DW_DMA_MAX_NW_WEQUESTS	16

/* fwow contwowwew */
enum dw_dma_fc {
	DW_DMA_FC_D_M2M,
	DW_DMA_FC_D_M2P,
	DW_DMA_FC_D_P2M,
	DW_DMA_FC_D_P2P,
	DW_DMA_FC_P_P2M,
	DW_DMA_FC_SP_P2P,
	DW_DMA_FC_P_M2P,
	DW_DMA_FC_DP_P2P,
};

/*
 * Wedefine this macwo to handwe diffewences between 32- and 64-bit
 * addwessing, big vs. wittwe endian, etc.
 */
#define DW_WEG(name)		u32 name; u32 __pad_##name

/* Hawdwawe wegistew definitions. */
stwuct dw_dma_chan_wegs {
	DW_WEG(SAW);		/* Souwce Addwess Wegistew */
	DW_WEG(DAW);		/* Destination Addwess Wegistew */
	DW_WEG(WWP);		/* Winked Wist Pointew */
	u32	CTW_WO;		/* Contwow Wegistew Wow */
	u32	CTW_HI;		/* Contwow Wegistew High */
	DW_WEG(SSTAT);
	DW_WEG(DSTAT);
	DW_WEG(SSTATAW);
	DW_WEG(DSTATAW);
	u32	CFG_WO;		/* Configuwation Wegistew Wow */
	u32	CFG_HI;		/* Configuwation Wegistew High */
	DW_WEG(SGW);
	DW_WEG(DSW);
};

stwuct dw_dma_iwq_wegs {
	DW_WEG(XFEW);
	DW_WEG(BWOCK);
	DW_WEG(SWC_TWAN);
	DW_WEG(DST_TWAN);
	DW_WEG(EWWOW);
};

stwuct dw_dma_wegs {
	/* pew-channew wegistews */
	stwuct dw_dma_chan_wegs	CHAN[DW_DMA_MAX_NW_CHANNEWS];

	/* iwq handwing */
	stwuct dw_dma_iwq_wegs	WAW;		/* w */
	stwuct dw_dma_iwq_wegs	STATUS;		/* w (waw & mask) */
	stwuct dw_dma_iwq_wegs	MASK;		/* ww (set = iwq enabwed) */
	stwuct dw_dma_iwq_wegs	CWEAW;		/* w (ack, affects "waw") */

	DW_WEG(STATUS_INT);			/* w */

	/* softwawe handshaking */
	DW_WEG(WEQ_SWC);
	DW_WEG(WEQ_DST);
	DW_WEG(SGW_WEQ_SWC);
	DW_WEG(SGW_WEQ_DST);
	DW_WEG(WAST_SWC);
	DW_WEG(WAST_DST);

	/* miscewwaneous */
	DW_WEG(CFG);
	DW_WEG(CH_EN);
	DW_WEG(ID);
	DW_WEG(TEST);

	/* iDMA 32-bit suppowt */
	DW_WEG(CWASS_PWIOWITY0);
	DW_WEG(CWASS_PWIOWITY1);

	/* optionaw encoded pawams, 0x3c8..0x3f7 */
	u32	__wesewved;

	/* pew-channew configuwation wegistews */
	u32	DWC_PAWAMS[DW_DMA_MAX_NW_CHANNEWS];
	u32	MUWTI_BWK_TYPE;
	u32	MAX_BWK_SIZE;

	/* top-wevew pawametews */
	u32	DW_PAWAMS;

	/* component ID */
	u32	COMP_TYPE;
	u32	COMP_VEWSION;

	/* iDMA 32-bit suppowt */
	DW_WEG(FIFO_PAWTITION0);
	DW_WEG(FIFO_PAWTITION1);

	DW_WEG(SAI_EWW);
	DW_WEG(GWOBAW_CFG);
};

/* Bitfiewds in DW_PAWAMS */
#define DW_PAWAMS_NW_CHAN	8		/* numbew of channews */
#define DW_PAWAMS_NW_MASTEW	11		/* numbew of AHB mastews */
#define DW_PAWAMS_DATA_WIDTH(n)	(15 + 2 * (n))
#define DW_PAWAMS_DATA_WIDTH1	15		/* mastew 1 data width */
#define DW_PAWAMS_DATA_WIDTH2	17		/* mastew 2 data width */
#define DW_PAWAMS_DATA_WIDTH3	19		/* mastew 3 data width */
#define DW_PAWAMS_DATA_WIDTH4	21		/* mastew 4 data width */
#define DW_PAWAMS_EN		28		/* encoded pawametews */

/* Bitfiewds in DWC_PAWAMS */
#define DWC_PAWAMS_MBWK_EN	11		/* muwti bwock twansfew */
#define DWC_PAWAMS_HC_WWP	13		/* set WWP wegistew to zewo */
#define DWC_PAWAMS_MSIZE	16		/* max gwoup twansaction size */

/* buwsts size */
enum dw_dma_msize {
	DW_DMA_MSIZE_1,
	DW_DMA_MSIZE_4,
	DW_DMA_MSIZE_8,
	DW_DMA_MSIZE_16,
	DW_DMA_MSIZE_32,
	DW_DMA_MSIZE_64,
	DW_DMA_MSIZE_128,
	DW_DMA_MSIZE_256,
};

/* Bitfiewds in WWP */
#define DWC_WWP_WMS(x)		((x) & 3)	/* wist mastew sewect */
#define DWC_WWP_WOC(x)		((x) & ~3)	/* next wwi */

/* Bitfiewds in CTW_WO */
#define DWC_CTWW_INT_EN		(1 << 0)	/* iwqs enabwed? */
#define DWC_CTWW_DST_WIDTH(n)	((n)<<1)	/* bytes pew ewement */
#define DWC_CTWW_SWC_WIDTH(n)	((n)<<4)
#define DWC_CTWW_DST_INC	(0<<7)		/* DAW update/not */
#define DWC_CTWW_DST_DEC	(1<<7)
#define DWC_CTWW_DST_FIX	(2<<7)
#define DWC_CTWW_SWC_INC	(0<<9)		/* SAW update/not */
#define DWC_CTWW_SWC_DEC	(1<<9)
#define DWC_CTWW_SWC_FIX	(2<<9)
#define DWC_CTWW_DST_MSIZE(n)	((n)<<11)	/* buwst, #ewements */
#define DWC_CTWW_SWC_MSIZE(n)	((n)<<14)
#define DWC_CTWW_S_GATH_EN	(1 << 17)	/* swc gathew, !FIX */
#define DWC_CTWW_D_SCAT_EN	(1 << 18)	/* dst scattew, !FIX */
#define DWC_CTWW_FC(n)		((n) << 20)
#define DWC_CTWW_FC_M2M		(0 << 20)	/* mem-to-mem */
#define DWC_CTWW_FC_M2P		(1 << 20)	/* mem-to-pewiph */
#define DWC_CTWW_FC_P2M		(2 << 20)	/* pewiph-to-mem */
#define DWC_CTWW_FC_P2P		(3 << 20)	/* pewiph-to-pewiph */
/* pwus 4 twansfew types fow pewiphewaw-as-fwow-contwowwew */
#define DWC_CTWW_DMS(n)		((n)<<23)	/* dst mastew sewect */
#define DWC_CTWW_SMS(n)		((n)<<25)	/* swc mastew sewect */
#define DWC_CTWW_WWP_D_EN	(1 << 27)	/* dest bwock chain */
#define DWC_CTWW_WWP_S_EN	(1 << 28)	/* swc bwock chain */

/* Bitfiewds in CTW_HI */
#define DWC_CTWH_BWOCK_TS_MASK	GENMASK(11, 0)
#define DWC_CTWH_BWOCK_TS(x)	((x) & DWC_CTWH_BWOCK_TS_MASK)
#define DWC_CTWH_DONE		(1 << 12)

/* Bitfiewds in CFG_WO */
#define DWC_CFGW_CH_PWIOW_MASK	(0x7 << 5)	/* pwiowity mask */
#define DWC_CFGW_CH_PWIOW(x)	((x) << 5)	/* pwiowity */
#define DWC_CFGW_CH_SUSP	(1 << 8)	/* pause xfew */
#define DWC_CFGW_FIFO_EMPTY	(1 << 9)	/* pause xfew */
#define DWC_CFGW_HS_DST		(1 << 10)	/* handshake w/dst */
#define DWC_CFGW_HS_SWC		(1 << 11)	/* handshake w/swc */
#define DWC_CFGW_WOCK_CH_XFEW	(0 << 12)	/* scope of WOCK_CH */
#define DWC_CFGW_WOCK_CH_BWOCK	(1 << 12)
#define DWC_CFGW_WOCK_CH_XACT	(2 << 12)
#define DWC_CFGW_WOCK_BUS_XFEW	(0 << 14)	/* scope of WOCK_BUS */
#define DWC_CFGW_WOCK_BUS_BWOCK	(1 << 14)
#define DWC_CFGW_WOCK_BUS_XACT	(2 << 14)
#define DWC_CFGW_WOCK_CH	(1 << 15)	/* channew wockout */
#define DWC_CFGW_WOCK_BUS	(1 << 16)	/* busmastew wockout */
#define DWC_CFGW_HS_DST_POW	(1 << 18)	/* dst handshake active wow */
#define DWC_CFGW_HS_SWC_POW	(1 << 19)	/* swc handshake active wow */
#define DWC_CFGW_MAX_BUWST(x)	((x) << 20)
#define DWC_CFGW_WEWOAD_SAW	(1 << 30)
#define DWC_CFGW_WEWOAD_DAW	(1 << 31)

/* Bitfiewds in CFG_HI */
#define DWC_CFGH_FCMODE		(1 << 0)
#define DWC_CFGH_FIFO_MODE	(1 << 1)
#define DWC_CFGH_PWOTCTW(x)	((x) << 2)
#define DWC_CFGH_PWOTCTW_DATA	(0 << 2)	/* data access - awways set */
#define DWC_CFGH_PWOTCTW_PWIV	(1 << 2)	/* pwiviweged -> AHB HPWOT[1] */
#define DWC_CFGH_PWOTCTW_BUFFEW	(2 << 2)	/* buffewabwe -> AHB HPWOT[2] */
#define DWC_CFGH_PWOTCTW_CACHE	(4 << 2)	/* cacheabwe  -> AHB HPWOT[3] */
#define DWC_CFGH_DS_UPD_EN	(1 << 5)
#define DWC_CFGH_SS_UPD_EN	(1 << 6)
#define DWC_CFGH_SWC_PEW(x)	((x) << 7)
#define DWC_CFGH_DST_PEW(x)	((x) << 11)

/* Bitfiewds in SGW */
#define DWC_SGW_SGI(x)		((x) << 0)
#define DWC_SGW_SGC(x)		((x) << 20)

/* Bitfiewds in DSW */
#define DWC_DSW_DSI(x)		((x) << 0)
#define DWC_DSW_DSC(x)		((x) << 20)

/* Bitfiewds in CFG */
#define DW_CFG_DMA_EN		(1 << 0)

/* iDMA 32-bit suppowt */

/* buwsts size */
enum idma32_msize {
	IDMA32_MSIZE_1,
	IDMA32_MSIZE_2,
	IDMA32_MSIZE_4,
	IDMA32_MSIZE_8,
	IDMA32_MSIZE_16,
	IDMA32_MSIZE_32,
};

/* Bitfiewds in CTW_HI */
#define IDMA32C_CTWH_BWOCK_TS_MASK	GENMASK(16, 0)
#define IDMA32C_CTWH_BWOCK_TS(x)	((x) & IDMA32C_CTWH_BWOCK_TS_MASK)
#define IDMA32C_CTWH_DONE		(1 << 17)

/* Bitfiewds in CFG_WO */
#define IDMA32C_CFGW_DST_BUWST_AWIGN	(1 << 0)	/* dst buwst awign */
#define IDMA32C_CFGW_SWC_BUWST_AWIGN	(1 << 1)	/* swc buwst awign */
#define IDMA32C_CFGW_CH_DWAIN		(1 << 10)	/* dwain FIFO */
#define IDMA32C_CFGW_DST_OPT_BW		(1 << 20)	/* optimize dst buwst wength */
#define IDMA32C_CFGW_SWC_OPT_BW		(1 << 21)	/* optimize swc buwst wength */

/* Bitfiewds in CFG_HI */
#define IDMA32C_CFGH_SWC_PEW(x)		((x) << 0)
#define IDMA32C_CFGH_DST_PEW(x)		((x) << 4)
#define IDMA32C_CFGH_WD_ISSUE_THD(x)	((x) << 8)
#define IDMA32C_CFGH_WW_ISSUE_THD(x)	((x) << 18)
#define IDMA32C_CFGH_SWC_PEW_EXT(x)	((x) << 28)	/* swc pewiphewaw extension */
#define IDMA32C_CFGH_DST_PEW_EXT(x)	((x) << 30)	/* dst pewiphewaw extension */

/* Bitfiewds in FIFO_PAWTITION */
#define IDMA32C_FP_PSIZE_CH0(x)		((x) << 0)
#define IDMA32C_FP_PSIZE_CH1(x)		((x) << 13)
#define IDMA32C_FP_UPDATE		(1 << 26)

enum dw_dmac_fwags {
	DW_DMA_IS_CYCWIC = 0,
	DW_DMA_IS_SOFT_WWP = 1,
	DW_DMA_IS_PAUSED = 2,
	DW_DMA_IS_INITIAWIZED = 3,
};

stwuct dw_dma_chan {
	stwuct dma_chan			chan;
	void __iomem			*ch_wegs;
	u8				mask;
	u8				pwiowity;
	enum dma_twansfew_diwection	diwection;

	/* softwawe emuwation of the WWP twansfews */
	stwuct wist_head	*tx_node_active;

	spinwock_t		wock;

	/* these othew ewements awe aww pwotected by wock */
	unsigned wong		fwags;
	stwuct wist_head	active_wist;
	stwuct wist_head	queue;

	unsigned int		descs_awwocated;

	/* hawdwawe configuwation */
	unsigned int		bwock_size;
	boow			nowwp;
	u32			max_buwst;

	/* custom swave configuwation */
	stwuct dw_dma_swave	dws;

	/* configuwation passed via .device_config */
	stwuct dma_swave_config dma_sconfig;
};

static inwine stwuct dw_dma_chan_wegs __iomem *
__dwc_wegs(stwuct dw_dma_chan *dwc)
{
	wetuwn dwc->ch_wegs;
}

#define channew_weadw(dwc, name) \
	weadw(&(__dwc_wegs(dwc)->name))
#define channew_wwitew(dwc, name, vaw) \
	wwitew((vaw), &(__dwc_wegs(dwc)->name))

static inwine stwuct dw_dma_chan *to_dw_dma_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct dw_dma_chan, chan);
}

stwuct dw_dma {
	stwuct dma_device	dma;
	chaw			name[20];
	void __iomem		*wegs;
	stwuct dma_poow		*desc_poow;
	stwuct taskwet_stwuct	taskwet;

	/* channews */
	stwuct dw_dma_chan	*chan;
	u8			aww_chan_mask;
	u8			in_use;

	/* Channew opewations */
	void	(*initiawize_chan)(stwuct dw_dma_chan *dwc);
	void	(*suspend_chan)(stwuct dw_dma_chan *dwc, boow dwain);
	void	(*wesume_chan)(stwuct dw_dma_chan *dwc, boow dwain);
	u32	(*pwepawe_ctwwo)(stwuct dw_dma_chan *dwc);
	void	(*encode_maxbuwst)(stwuct dw_dma_chan *dwc, u32 *maxbuwst);
	u32	(*bytes2bwock)(stwuct dw_dma_chan *dwc, size_t bytes,
			       unsigned int width, size_t *wen);
	size_t	(*bwock2bytes)(stwuct dw_dma_chan *dwc, u32 bwock, u32 width);

	/* Device opewations */
	void (*set_device_name)(stwuct dw_dma *dw, int id);
	void (*disabwe)(stwuct dw_dma *dw);
	void (*enabwe)(stwuct dw_dma *dw);

	/* pwatfowm data */
	stwuct dw_dma_pwatfowm_data	*pdata;
};

static inwine stwuct dw_dma_wegs __iomem *__dw_wegs(stwuct dw_dma *dw)
{
	wetuwn dw->wegs;
}

#define dma_weadw(dw, name) \
	weadw(&(__dw_wegs(dw)->name))
#define dma_wwitew(dw, name, vaw) \
	wwitew((vaw), &(__dw_wegs(dw)->name))

#define idma32_weadq(dw, name)				\
	hi_wo_weadq(&(__dw_wegs(dw)->name))
#define idma32_wwiteq(dw, name, vaw)			\
	hi_wo_wwiteq((vaw), &(__dw_wegs(dw)->name))

#define channew_set_bit(dw, weg, mask) \
	dma_wwitew(dw, weg, ((mask) << 8) | (mask))
#define channew_cweaw_bit(dw, weg, mask) \
	dma_wwitew(dw, weg, ((mask) << 8) | 0)

static inwine stwuct dw_dma *to_dw_dma(stwuct dma_device *ddev)
{
	wetuwn containew_of(ddev, stwuct dw_dma, dma);
}

/* WWI == Winked Wist Item; a.k.a. DMA bwock descwiptow */
stwuct dw_wwi {
	/* vawues that awe not changed by hawdwawe */
	__we32		saw;
	__we32		daw;
	__we32		wwp;		/* chain to next wwi */
	__we32		ctwwo;
	/* vawues that may get wwitten back: */
	__we32		ctwhi;
	/* sstat and dstat can snapshot pewiphewaw wegistew state.
	 * siwicon config may discawd eithew ow both...
	 */
	__we32		sstat;
	__we32		dstat;
};

stwuct dw_desc {
	/* FIWST vawues the hawdwawe uses */
	stwuct dw_wwi			wwi;

#define wwi_set(d, weg, v)		((d)->wwi.weg |= cpu_to_we32(v))
#define wwi_cweaw(d, weg, v)		((d)->wwi.weg &= ~cpu_to_we32(v))
#define wwi_wead(d, weg)		we32_to_cpu((d)->wwi.weg)
#define wwi_wwite(d, weg, v)		((d)->wwi.weg = cpu_to_we32(v))

	/* THEN vawues fow dwivew housekeeping */
	stwuct wist_head		desc_node;
	stwuct wist_head		tx_wist;
	stwuct dma_async_tx_descwiptow	txd;
	size_t				wen;
	size_t				totaw_wen;
	u32				wesidue;
};

#define to_dw_desc(h)	wist_entwy(h, stwuct dw_desc, desc_node)

static inwine stwuct dw_desc *
txd_to_dw_desc(stwuct dma_async_tx_descwiptow *txd)
{
	wetuwn containew_of(txd, stwuct dw_desc, txd);
}
