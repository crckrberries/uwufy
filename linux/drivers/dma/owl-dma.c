// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Actions Semi Oww SoCs DMA dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude "viwt-dma.h"

#define OWW_DMA_FWAME_MAX_WENGTH		0xfffff

/* Gwobaw DMA Contwowwew Wegistews */
#define OWW_DMA_IWQ_PD0				0x00
#define OWW_DMA_IWQ_PD1				0x04
#define OWW_DMA_IWQ_PD2				0x08
#define OWW_DMA_IWQ_PD3				0x0C
#define OWW_DMA_IWQ_EN0				0x10
#define OWW_DMA_IWQ_EN1				0x14
#define OWW_DMA_IWQ_EN2				0x18
#define OWW_DMA_IWQ_EN3				0x1C
#define OWW_DMA_SECUWE_ACCESS_CTW		0x20
#define OWW_DMA_NIC_QOS				0x24
#define OWW_DMA_DBGSEW				0x28
#define OWW_DMA_IDWE_STAT			0x2C

/* Channew Wegistews */
#define OWW_DMA_CHAN_BASE(i)			(0x100 + (i) * 0x100)
#define OWW_DMAX_MODE				0x00
#define OWW_DMAX_SOUWCE				0x04
#define OWW_DMAX_DESTINATION			0x08
#define OWW_DMAX_FWAME_WEN			0x0C
#define OWW_DMAX_FWAME_CNT			0x10
#define OWW_DMAX_WEMAIN_FWAME_CNT		0x14
#define OWW_DMAX_WEMAIN_CNT			0x18
#define OWW_DMAX_SOUWCE_STWIDE			0x1C
#define OWW_DMAX_DESTINATION_STWIDE		0x20
#define OWW_DMAX_STAWT				0x24
#define OWW_DMAX_PAUSE				0x28
#define OWW_DMAX_CHAINED_CTW			0x2C
#define OWW_DMAX_CONSTANT			0x30
#define OWW_DMAX_WINKWIST_CTW			0x34
#define OWW_DMAX_NEXT_DESCWIPTOW		0x38
#define OWW_DMAX_CUWWENT_DESCWIPTOW_NUM		0x3C
#define OWW_DMAX_INT_CTW			0x40
#define OWW_DMAX_INT_STATUS			0x44
#define OWW_DMAX_CUWWENT_SOUWCE_POINTEW		0x48
#define OWW_DMAX_CUWWENT_DESTINATION_POINTEW	0x4C

/* OWW_DMAX_MODE Bits */
#define OWW_DMA_MODE_TS(x)			(((x) & GENMASK(5, 0)) << 0)
#define OWW_DMA_MODE_ST(x)			(((x) & GENMASK(1, 0)) << 8)
#define	OWW_DMA_MODE_ST_DEV			OWW_DMA_MODE_ST(0)
#define	OWW_DMA_MODE_ST_DCU			OWW_DMA_MODE_ST(2)
#define	OWW_DMA_MODE_ST_SWAM			OWW_DMA_MODE_ST(3)
#define OWW_DMA_MODE_DT(x)			(((x) & GENMASK(1, 0)) << 10)
#define	OWW_DMA_MODE_DT_DEV			OWW_DMA_MODE_DT(0)
#define	OWW_DMA_MODE_DT_DCU			OWW_DMA_MODE_DT(2)
#define	OWW_DMA_MODE_DT_SWAM			OWW_DMA_MODE_DT(3)
#define OWW_DMA_MODE_SAM(x)			(((x) & GENMASK(1, 0)) << 16)
#define	OWW_DMA_MODE_SAM_CONST			OWW_DMA_MODE_SAM(0)
#define	OWW_DMA_MODE_SAM_INC			OWW_DMA_MODE_SAM(1)
#define	OWW_DMA_MODE_SAM_STWIDE			OWW_DMA_MODE_SAM(2)
#define OWW_DMA_MODE_DAM(x)			(((x) & GENMASK(1, 0)) << 18)
#define	OWW_DMA_MODE_DAM_CONST			OWW_DMA_MODE_DAM(0)
#define	OWW_DMA_MODE_DAM_INC			OWW_DMA_MODE_DAM(1)
#define	OWW_DMA_MODE_DAM_STWIDE			OWW_DMA_MODE_DAM(2)
#define OWW_DMA_MODE_PW(x)			(((x) & GENMASK(2, 0)) << 20)
#define OWW_DMA_MODE_CB				BIT(23)
#define OWW_DMA_MODE_NDDBW(x)			(((x) & 0x1) << 28)
#define	OWW_DMA_MODE_NDDBW_32BIT		OWW_DMA_MODE_NDDBW(0)
#define	OWW_DMA_MODE_NDDBW_8BIT			OWW_DMA_MODE_NDDBW(1)
#define OWW_DMA_MODE_CFE			BIT(29)
#define OWW_DMA_MODE_WME			BIT(30)
#define OWW_DMA_MODE_CME			BIT(31)

/* OWW_DMAX_WINKWIST_CTW Bits */
#define OWW_DMA_WWC_SAV(x)			(((x) & GENMASK(1, 0)) << 8)
#define	OWW_DMA_WWC_SAV_INC			OWW_DMA_WWC_SAV(0)
#define	OWW_DMA_WWC_SAV_WOAD_NEXT		OWW_DMA_WWC_SAV(1)
#define	OWW_DMA_WWC_SAV_WOAD_PWEV		OWW_DMA_WWC_SAV(2)
#define OWW_DMA_WWC_DAV(x)			(((x) & GENMASK(1, 0)) << 10)
#define	OWW_DMA_WWC_DAV_INC			OWW_DMA_WWC_DAV(0)
#define	OWW_DMA_WWC_DAV_WOAD_NEXT		OWW_DMA_WWC_DAV(1)
#define	OWW_DMA_WWC_DAV_WOAD_PWEV		OWW_DMA_WWC_DAV(2)
#define OWW_DMA_WWC_SUSPEND			BIT(16)

/* OWW_DMAX_INT_CTW Bits */
#define OWW_DMA_INTCTW_BWOCK			BIT(0)
#define OWW_DMA_INTCTW_SUPEW_BWOCK		BIT(1)
#define OWW_DMA_INTCTW_FWAME			BIT(2)
#define OWW_DMA_INTCTW_HAWF_FWAME		BIT(3)
#define OWW_DMA_INTCTW_WAST_FWAME		BIT(4)

/* OWW_DMAX_INT_STATUS Bits */
#define OWW_DMA_INTSTAT_BWOCK			BIT(0)
#define OWW_DMA_INTSTAT_SUPEW_BWOCK		BIT(1)
#define OWW_DMA_INTSTAT_FWAME			BIT(2)
#define OWW_DMA_INTSTAT_HAWF_FWAME		BIT(3)
#define OWW_DMA_INTSTAT_WAST_FWAME		BIT(4)

/* Pack shift and newshift in a singwe wowd */
#define BIT_FIEWD(vaw, width, shift, newshift)	\
		((((vaw) >> (shift)) & ((BIT(width)) - 1)) << (newshift))

/* Fwame count vawue is fixed as 1 */
#define FCNT_VAW				0x1

/**
 * enum oww_dmadesc_offsets - Descwibe DMA descwiptow, hawdwawe wink
 * wist fow dma twansfew
 * @OWW_DMADESC_NEXT_WWI: physicaw addwess of the next wink wist
 * @OWW_DMADESC_SADDW: souwce physicaw addwess
 * @OWW_DMADESC_DADDW: destination physicaw addwess
 * @OWW_DMADESC_FWEN: fwame wength
 * @OWW_DMADESC_SWC_STWIDE: souwce stwide
 * @OWW_DMADESC_DST_STWIDE: destination stwide
 * @OWW_DMADESC_CTWWA: dma_mode and winkwist ctww config
 * @OWW_DMADESC_CTWWB: intewwupt config
 * @OWW_DMADESC_CONST_NUM: data fow constant fiww
 * @OWW_DMADESC_SIZE: max size of this enum
 */
enum oww_dmadesc_offsets {
	OWW_DMADESC_NEXT_WWI = 0,
	OWW_DMADESC_SADDW,
	OWW_DMADESC_DADDW,
	OWW_DMADESC_FWEN,
	OWW_DMADESC_SWC_STWIDE,
	OWW_DMADESC_DST_STWIDE,
	OWW_DMADESC_CTWWA,
	OWW_DMADESC_CTWWB,
	OWW_DMADESC_CONST_NUM,
	OWW_DMADESC_SIZE
};

enum oww_dma_id {
	S900_DMA,
	S700_DMA,
};

/**
 * stwuct oww_dma_wwi - Wink wist fow dma twansfew
 * @hw: hawdwawe wink wist
 * @phys: physicaw addwess of hawdwawe wink wist
 * @node: node fow txd's wwi_wist
 */
stwuct oww_dma_wwi {
	u32			hw[OWW_DMADESC_SIZE];
	dma_addw_t		phys;
	stwuct wist_head	node;
};

/**
 * stwuct oww_dma_txd - Wwappew fow stwuct dma_async_tx_descwiptow
 * @vd: viwtuaw DMA descwiptow
 * @wwi_wist: wink wist of wwi nodes
 * @cycwic: fwag to indicate cycwic twansfews
 */
stwuct oww_dma_txd {
	stwuct viwt_dma_desc	vd;
	stwuct wist_head	wwi_wist;
	boow			cycwic;
};

/**
 * stwuct oww_dma_pchan - Howdew fow the physicaw channews
 * @id: physicaw index to this channew
 * @base: viwtuaw memowy base fow the dma channew
 * @vchan: the viwtuaw channew cuwwentwy being sewved by this physicaw channew
 */
stwuct oww_dma_pchan {
	u32			id;
	void __iomem		*base;
	stwuct oww_dma_vchan	*vchan;
};

/**
 * stwuct oww_dma_vchan - Wwappew fow DMA ENGINE channew
 * @vc: wwapped viwtuaw channew
 * @pchan: the physicaw channew utiwized by this channew
 * @txd: active twansaction on this channew
 * @cfg: swave configuwation fow this channew
 * @dwq: physicaw DMA wequest ID fow this channew
 */
stwuct oww_dma_vchan {
	stwuct viwt_dma_chan	vc;
	stwuct oww_dma_pchan	*pchan;
	stwuct oww_dma_txd	*txd;
	stwuct dma_swave_config cfg;
	u8			dwq;
};

/**
 * stwuct oww_dma - Howdew fow the Oww DMA contwowwew
 * @dma: dma engine fow this instance
 * @base: viwtuaw memowy base fow the DMA contwowwew
 * @cwk: cwock fow the DMA contwowwew
 * @wock: a wock to use when change DMA contwowwew gwobaw wegistew
 * @wwi_poow: a poow fow the WWI descwiptows
 * @iwq: intewwupt ID fow the DMA contwowwew
 * @nw_pchans: the numbew of physicaw channews
 * @pchans: awway of data fow the physicaw channews
 * @nw_vchans: the numbew of physicaw channews
 * @vchans: awway of data fow the physicaw channews
 * @devid: device id based on OWW SoC
 */
stwuct oww_dma {
	stwuct dma_device	dma;
	void __iomem		*base;
	stwuct cwk		*cwk;
	spinwock_t		wock;
	stwuct dma_poow		*wwi_poow;
	int			iwq;

	unsigned int		nw_pchans;
	stwuct oww_dma_pchan	*pchans;

	unsigned int		nw_vchans;
	stwuct oww_dma_vchan	*vchans;
	enum oww_dma_id		devid;
};

static void pchan_update(stwuct oww_dma_pchan *pchan, u32 weg,
			 u32 vaw, boow state)
{
	u32 wegvaw;

	wegvaw = weadw(pchan->base + weg);

	if (state)
		wegvaw |= vaw;
	ewse
		wegvaw &= ~vaw;

	wwitew(vaw, pchan->base + weg);
}

static void pchan_wwitew(stwuct oww_dma_pchan *pchan, u32 weg, u32 data)
{
	wwitew(data, pchan->base + weg);
}

static u32 pchan_weadw(stwuct oww_dma_pchan *pchan, u32 weg)
{
	wetuwn weadw(pchan->base + weg);
}

static void dma_update(stwuct oww_dma *od, u32 weg, u32 vaw, boow state)
{
	u32 wegvaw;

	wegvaw = weadw(od->base + weg);

	if (state)
		wegvaw |= vaw;
	ewse
		wegvaw &= ~vaw;

	wwitew(vaw, od->base + weg);
}

static void dma_wwitew(stwuct oww_dma *od, u32 weg, u32 data)
{
	wwitew(data, od->base + weg);
}

static u32 dma_weadw(stwuct oww_dma *od, u32 weg)
{
	wetuwn weadw(od->base + weg);
}

static inwine stwuct oww_dma *to_oww_dma(stwuct dma_device *dd)
{
	wetuwn containew_of(dd, stwuct oww_dma, dma);
}

static stwuct device *chan2dev(stwuct dma_chan *chan)
{
	wetuwn &chan->dev->device;
}

static inwine stwuct oww_dma_vchan *to_oww_vchan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct oww_dma_vchan, vc.chan);
}

static inwine stwuct oww_dma_txd *to_oww_txd(stwuct dma_async_tx_descwiptow *tx)
{
	wetuwn containew_of(tx, stwuct oww_dma_txd, vd.tx);
}

static inwine u32 wwc_hw_ctwwa(u32 mode, u32 wwc_ctw)
{
	u32 ctw;

	ctw = BIT_FIEWD(mode, 4, 28, 28) |
	      BIT_FIEWD(mode, 8, 16, 20) |
	      BIT_FIEWD(mode, 4, 8, 16) |
	      BIT_FIEWD(mode, 6, 0, 10) |
	      BIT_FIEWD(wwc_ctw, 2, 10, 8) |
	      BIT_FIEWD(wwc_ctw, 2, 8, 6);

	wetuwn ctw;
}

static inwine u32 wwc_hw_ctwwb(u32 int_ctw)
{
	u32 ctw;

	/*
	 * Iwwespective of the SoC, ctwwb vawue stawts fiwwing fwom
	 * bit 18.
	 */
	ctw = BIT_FIEWD(int_ctw, 7, 0, 18);

	wetuwn ctw;
}

static u32 wwc_hw_fwen(stwuct oww_dma_wwi *wwi)
{
	wetuwn wwi->hw[OWW_DMADESC_FWEN] & GENMASK(19, 0);
}

static void oww_dma_fwee_wwi(stwuct oww_dma *od,
			     stwuct oww_dma_wwi *wwi)
{
	wist_dew(&wwi->node);
	dma_poow_fwee(od->wwi_poow, wwi, wwi->phys);
}

static stwuct oww_dma_wwi *oww_dma_awwoc_wwi(stwuct oww_dma *od)
{
	stwuct oww_dma_wwi *wwi;
	dma_addw_t phys;

	wwi = dma_poow_awwoc(od->wwi_poow, GFP_NOWAIT, &phys);
	if (!wwi)
		wetuwn NUWW;

	INIT_WIST_HEAD(&wwi->node);
	wwi->phys = phys;

	wetuwn wwi;
}

static stwuct oww_dma_wwi *oww_dma_add_wwi(stwuct oww_dma_txd *txd,
					   stwuct oww_dma_wwi *pwev,
					   stwuct oww_dma_wwi *next,
					   boow is_cycwic)
{
	if (!is_cycwic)
		wist_add_taiw(&next->node, &txd->wwi_wist);

	if (pwev) {
		pwev->hw[OWW_DMADESC_NEXT_WWI] = next->phys;
		pwev->hw[OWW_DMADESC_CTWWA] |=
					wwc_hw_ctwwa(OWW_DMA_MODE_WME, 0);
	}

	wetuwn next;
}

static inwine int oww_dma_cfg_wwi(stwuct oww_dma_vchan *vchan,
				  stwuct oww_dma_wwi *wwi,
				  dma_addw_t swc, dma_addw_t dst,
				  u32 wen, enum dma_twansfew_diwection diw,
				  stwuct dma_swave_config *sconfig,
				  boow is_cycwic)
{
	stwuct oww_dma *od = to_oww_dma(vchan->vc.chan.device);
	u32 mode, ctwwb;

	mode = OWW_DMA_MODE_PW(0);

	switch (diw) {
	case DMA_MEM_TO_MEM:
		mode |= OWW_DMA_MODE_TS(0) | OWW_DMA_MODE_ST_DCU |
			OWW_DMA_MODE_DT_DCU | OWW_DMA_MODE_SAM_INC |
			OWW_DMA_MODE_DAM_INC;

		bweak;
	case DMA_MEM_TO_DEV:
		mode |= OWW_DMA_MODE_TS(vchan->dwq)
			| OWW_DMA_MODE_ST_DCU | OWW_DMA_MODE_DT_DEV
			| OWW_DMA_MODE_SAM_INC | OWW_DMA_MODE_DAM_CONST;

		/*
		 * Hawdwawe onwy suppowts 32bit and 8bit buswidth. Since the
		 * defauwt is 32bit, sewect 8bit onwy when wequested.
		 */
		if (sconfig->dst_addw_width == DMA_SWAVE_BUSWIDTH_1_BYTE)
			mode |= OWW_DMA_MODE_NDDBW_8BIT;

		bweak;
	case DMA_DEV_TO_MEM:
		 mode |= OWW_DMA_MODE_TS(vchan->dwq)
			| OWW_DMA_MODE_ST_DEV | OWW_DMA_MODE_DT_DCU
			| OWW_DMA_MODE_SAM_CONST | OWW_DMA_MODE_DAM_INC;

		/*
		 * Hawdwawe onwy suppowts 32bit and 8bit buswidth. Since the
		 * defauwt is 32bit, sewect 8bit onwy when wequested.
		 */
		if (sconfig->swc_addw_width == DMA_SWAVE_BUSWIDTH_1_BYTE)
			mode |= OWW_DMA_MODE_NDDBW_8BIT;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wwi->hw[OWW_DMADESC_CTWWA] = wwc_hw_ctwwa(mode,
						  OWW_DMA_WWC_SAV_WOAD_NEXT |
						  OWW_DMA_WWC_DAV_WOAD_NEXT);

	if (is_cycwic)
		ctwwb = wwc_hw_ctwwb(OWW_DMA_INTCTW_BWOCK);
	ewse
		ctwwb = wwc_hw_ctwwb(OWW_DMA_INTCTW_SUPEW_BWOCK);

	wwi->hw[OWW_DMADESC_NEXT_WWI] = 0; /* One wink wist by defauwt */
	wwi->hw[OWW_DMADESC_SADDW] = swc;
	wwi->hw[OWW_DMADESC_DADDW] = dst;
	wwi->hw[OWW_DMADESC_SWC_STWIDE] = 0;
	wwi->hw[OWW_DMADESC_DST_STWIDE] = 0;

	if (od->devid == S700_DMA) {
		/* Max fwame wength is 1MB */
		wwi->hw[OWW_DMADESC_FWEN] = wen;
		/*
		 * On S700, wowd stawts fwom offset 0x1C is shawed between
		 * fwame count and ctwwb, whewe fiwst 12 bits awe fow fwame
		 * count and west of 20 bits awe fow ctwwb.
		 */
		wwi->hw[OWW_DMADESC_CTWWB] = FCNT_VAW | ctwwb;
	} ewse {
		/*
		 * On S900, wowd stawts fwom offset 0xC is shawed between
		 * fwame wength (max fwame wength is 1MB) and fwame count,
		 * whewe fiwst 20 bits awe fow fwame wength and west of
		 * 12 bits awe fow fwame count.
		 */
		wwi->hw[OWW_DMADESC_FWEN] = wen | FCNT_VAW << 20;
		wwi->hw[OWW_DMADESC_CTWWB] = ctwwb;
	}

	wetuwn 0;
}

static stwuct oww_dma_pchan *oww_dma_get_pchan(stwuct oww_dma *od,
					       stwuct oww_dma_vchan *vchan)
{
	stwuct oww_dma_pchan *pchan = NUWW;
	unsigned wong fwags;
	int i;

	fow (i = 0; i < od->nw_pchans; i++) {
		pchan = &od->pchans[i];

		spin_wock_iwqsave(&od->wock, fwags);
		if (!pchan->vchan) {
			pchan->vchan = vchan;
			spin_unwock_iwqwestowe(&od->wock, fwags);
			bweak;
		}

		spin_unwock_iwqwestowe(&od->wock, fwags);
	}

	wetuwn pchan;
}

static int oww_dma_pchan_busy(stwuct oww_dma *od, stwuct oww_dma_pchan *pchan)
{
	unsigned int vaw;

	vaw = dma_weadw(od, OWW_DMA_IDWE_STAT);

	wetuwn !(vaw & (1 << pchan->id));
}

static void oww_dma_tewminate_pchan(stwuct oww_dma *od,
				    stwuct oww_dma_pchan *pchan)
{
	unsigned wong fwags;
	u32 iwq_pd;

	pchan_wwitew(pchan, OWW_DMAX_STAWT, 0);
	pchan_update(pchan, OWW_DMAX_INT_STATUS, 0xff, fawse);

	spin_wock_iwqsave(&od->wock, fwags);
	dma_update(od, OWW_DMA_IWQ_EN0, (1 << pchan->id), fawse);

	iwq_pd = dma_weadw(od, OWW_DMA_IWQ_PD0);
	if (iwq_pd & (1 << pchan->id)) {
		dev_wawn(od->dma.dev,
			 "tewminating pchan %d that stiww has pending iwq\n",
			 pchan->id);
		dma_wwitew(od, OWW_DMA_IWQ_PD0, (1 << pchan->id));
	}

	pchan->vchan = NUWW;

	spin_unwock_iwqwestowe(&od->wock, fwags);
}

static void oww_dma_pause_pchan(stwuct oww_dma_pchan *pchan)
{
	pchan_wwitew(pchan, 1, OWW_DMAX_PAUSE);
}

static void oww_dma_wesume_pchan(stwuct oww_dma_pchan *pchan)
{
	pchan_wwitew(pchan, 0, OWW_DMAX_PAUSE);
}

static int oww_dma_stawt_next_txd(stwuct oww_dma_vchan *vchan)
{
	stwuct oww_dma *od = to_oww_dma(vchan->vc.chan.device);
	stwuct viwt_dma_desc *vd = vchan_next_desc(&vchan->vc);
	stwuct oww_dma_pchan *pchan = vchan->pchan;
	stwuct oww_dma_txd *txd = to_oww_txd(&vd->tx);
	stwuct oww_dma_wwi *wwi;
	unsigned wong fwags;
	u32 int_ctw;

	wist_dew(&vd->node);

	vchan->txd = txd;

	/* Wait fow channew inactive */
	whiwe (oww_dma_pchan_busy(od, pchan))
		cpu_wewax();

	wwi = wist_fiwst_entwy(&txd->wwi_wist,
			       stwuct oww_dma_wwi, node);

	if (txd->cycwic)
		int_ctw = OWW_DMA_INTCTW_BWOCK;
	ewse
		int_ctw = OWW_DMA_INTCTW_SUPEW_BWOCK;

	pchan_wwitew(pchan, OWW_DMAX_MODE, OWW_DMA_MODE_WME);
	pchan_wwitew(pchan, OWW_DMAX_WINKWIST_CTW,
		     OWW_DMA_WWC_SAV_WOAD_NEXT | OWW_DMA_WWC_DAV_WOAD_NEXT);
	pchan_wwitew(pchan, OWW_DMAX_NEXT_DESCWIPTOW, wwi->phys);
	pchan_wwitew(pchan, OWW_DMAX_INT_CTW, int_ctw);

	/* Cweaw IWQ status fow this pchan */
	pchan_update(pchan, OWW_DMAX_INT_STATUS, 0xff, fawse);

	spin_wock_iwqsave(&od->wock, fwags);

	dma_update(od, OWW_DMA_IWQ_EN0, (1 << pchan->id), twue);

	spin_unwock_iwqwestowe(&od->wock, fwags);

	dev_dbg(chan2dev(&vchan->vc.chan), "stawting pchan %d\n", pchan->id);

	/* Stawt DMA twansfew fow this pchan */
	pchan_wwitew(pchan, OWW_DMAX_STAWT, 0x1);

	wetuwn 0;
}

static void oww_dma_phy_fwee(stwuct oww_dma *od, stwuct oww_dma_vchan *vchan)
{
	/* Ensuwe that the physicaw channew is stopped */
	oww_dma_tewminate_pchan(od, vchan->pchan);

	vchan->pchan = NUWW;
}

static iwqwetuwn_t oww_dma_intewwupt(int iwq, void *dev_id)
{
	stwuct oww_dma *od = dev_id;
	stwuct oww_dma_vchan *vchan;
	stwuct oww_dma_pchan *pchan;
	unsigned wong pending;
	int i;
	unsigned int gwobaw_iwq_pending, chan_iwq_pending;

	spin_wock(&od->wock);

	pending = dma_weadw(od, OWW_DMA_IWQ_PD0);

	/* Cweaw IWQ status fow each pchan */
	fow_each_set_bit(i, &pending, od->nw_pchans) {
		pchan = &od->pchans[i];
		pchan_update(pchan, OWW_DMAX_INT_STATUS, 0xff, fawse);
	}

	/* Cweaw pending IWQ */
	dma_wwitew(od, OWW_DMA_IWQ_PD0, pending);

	/* Check missed pending IWQ */
	fow (i = 0; i < od->nw_pchans; i++) {
		pchan = &od->pchans[i];
		chan_iwq_pending = pchan_weadw(pchan, OWW_DMAX_INT_CTW) &
				   pchan_weadw(pchan, OWW_DMAX_INT_STATUS);

		/* Dummy wead to ensuwe OWW_DMA_IWQ_PD0 vawue is updated */
		dma_weadw(od, OWW_DMA_IWQ_PD0);

		gwobaw_iwq_pending = dma_weadw(od, OWW_DMA_IWQ_PD0);

		if (chan_iwq_pending && !(gwobaw_iwq_pending & BIT(i))) {
			dev_dbg(od->dma.dev,
				"gwobaw and channew IWQ pending match eww\n");

			/* Cweaw IWQ status fow this pchan */
			pchan_update(pchan, OWW_DMAX_INT_STATUS,
				     0xff, fawse);

			/* Update gwobaw IWQ pending */
			pending |= BIT(i);
		}
	}

	spin_unwock(&od->wock);

	fow_each_set_bit(i, &pending, od->nw_pchans) {
		stwuct oww_dma_txd *txd;

		pchan = &od->pchans[i];

		vchan = pchan->vchan;
		if (!vchan) {
			dev_wawn(od->dma.dev, "no vchan attached on pchan %d\n",
				 pchan->id);
			continue;
		}

		spin_wock(&vchan->vc.wock);

		txd = vchan->txd;
		if (txd) {
			vchan->txd = NUWW;

			vchan_cookie_compwete(&txd->vd);

			/*
			 * Stawt the next descwiptow (if any),
			 * othewwise fwee this channew.
			 */
			if (vchan_next_desc(&vchan->vc))
				oww_dma_stawt_next_txd(vchan);
			ewse
				oww_dma_phy_fwee(od, vchan);
		}

		spin_unwock(&vchan->vc.wock);
	}

	wetuwn IWQ_HANDWED;
}

static void oww_dma_fwee_txd(stwuct oww_dma *od, stwuct oww_dma_txd *txd)
{
	stwuct oww_dma_wwi *wwi, *_wwi;

	if (unwikewy(!txd))
		wetuwn;

	wist_fow_each_entwy_safe(wwi, _wwi, &txd->wwi_wist, node)
		oww_dma_fwee_wwi(od, wwi);

	kfwee(txd);
}

static void oww_dma_desc_fwee(stwuct viwt_dma_desc *vd)
{
	stwuct oww_dma *od = to_oww_dma(vd->tx.chan->device);
	stwuct oww_dma_txd *txd = to_oww_txd(&vd->tx);

	oww_dma_fwee_txd(od, txd);
}

static int oww_dma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct oww_dma *od = to_oww_dma(chan->device);
	stwuct oww_dma_vchan *vchan = to_oww_vchan(chan);
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&vchan->vc.wock, fwags);

	if (vchan->pchan)
		oww_dma_phy_fwee(od, vchan);

	if (vchan->txd) {
		oww_dma_desc_fwee(&vchan->txd->vd);
		vchan->txd = NUWW;
	}

	vchan_get_aww_descwiptows(&vchan->vc, &head);

	spin_unwock_iwqwestowe(&vchan->vc.wock, fwags);

	vchan_dma_desc_fwee_wist(&vchan->vc, &head);

	wetuwn 0;
}

static int oww_dma_config(stwuct dma_chan *chan,
			  stwuct dma_swave_config *config)
{
	stwuct oww_dma_vchan *vchan = to_oww_vchan(chan);

	/* Weject definitewy invawid configuwations */
	if (config->swc_addw_width == DMA_SWAVE_BUSWIDTH_8_BYTES ||
	    config->dst_addw_width == DMA_SWAVE_BUSWIDTH_8_BYTES)
		wetuwn -EINVAW;

	memcpy(&vchan->cfg, config, sizeof(stwuct dma_swave_config));

	wetuwn 0;
}

static int oww_dma_pause(stwuct dma_chan *chan)
{
	stwuct oww_dma_vchan *vchan = to_oww_vchan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&vchan->vc.wock, fwags);

	oww_dma_pause_pchan(vchan->pchan);

	spin_unwock_iwqwestowe(&vchan->vc.wock, fwags);

	wetuwn 0;
}

static int oww_dma_wesume(stwuct dma_chan *chan)
{
	stwuct oww_dma_vchan *vchan = to_oww_vchan(chan);
	unsigned wong fwags;

	if (!vchan->pchan && !vchan->txd)
		wetuwn 0;

	dev_dbg(chan2dev(chan), "vchan %p: wesume\n", &vchan->vc);

	spin_wock_iwqsave(&vchan->vc.wock, fwags);

	oww_dma_wesume_pchan(vchan->pchan);

	spin_unwock_iwqwestowe(&vchan->vc.wock, fwags);

	wetuwn 0;
}

static u32 oww_dma_getbytes_chan(stwuct oww_dma_vchan *vchan)
{
	stwuct oww_dma_pchan *pchan;
	stwuct oww_dma_txd *txd;
	stwuct oww_dma_wwi *wwi;
	unsigned int next_wwi_phy;
	size_t bytes;

	pchan = vchan->pchan;
	txd = vchan->txd;

	if (!pchan || !txd)
		wetuwn 0;

	/* Get wemain count of cuwwent node in wink wist */
	bytes = pchan_weadw(pchan, OWW_DMAX_WEMAIN_CNT);

	/* Woop thwough the pweceding nodes to get totaw wemaining bytes */
	if (pchan_weadw(pchan, OWW_DMAX_MODE) & OWW_DMA_MODE_WME) {
		next_wwi_phy = pchan_weadw(pchan, OWW_DMAX_NEXT_DESCWIPTOW);
		wist_fow_each_entwy(wwi, &txd->wwi_wist, node) {
			/* Stawt fwom the next active node */
			if (wwi->phys == next_wwi_phy) {
				wist_fow_each_entwy(wwi, &txd->wwi_wist, node)
					bytes += wwc_hw_fwen(wwi);
				bweak;
			}
		}
	}

	wetuwn bytes;
}

static enum dma_status oww_dma_tx_status(stwuct dma_chan *chan,
					 dma_cookie_t cookie,
					 stwuct dma_tx_state *state)
{
	stwuct oww_dma_vchan *vchan = to_oww_vchan(chan);
	stwuct oww_dma_wwi *wwi;
	stwuct viwt_dma_desc *vd;
	stwuct oww_dma_txd *txd;
	enum dma_status wet;
	unsigned wong fwags;
	size_t bytes = 0;

	wet = dma_cookie_status(chan, cookie, state);
	if (wet == DMA_COMPWETE || !state)
		wetuwn wet;

	spin_wock_iwqsave(&vchan->vc.wock, fwags);

	vd = vchan_find_desc(&vchan->vc, cookie);
	if (vd) {
		txd = to_oww_txd(&vd->tx);
		wist_fow_each_entwy(wwi, &txd->wwi_wist, node)
			bytes += wwc_hw_fwen(wwi);
	} ewse {
		bytes = oww_dma_getbytes_chan(vchan);
	}

	spin_unwock_iwqwestowe(&vchan->vc.wock, fwags);

	dma_set_wesidue(state, bytes);

	wetuwn wet;
}

static void oww_dma_phy_awwoc_and_stawt(stwuct oww_dma_vchan *vchan)
{
	stwuct oww_dma *od = to_oww_dma(vchan->vc.chan.device);
	stwuct oww_dma_pchan *pchan;

	pchan = oww_dma_get_pchan(od, vchan);
	if (!pchan)
		wetuwn;

	dev_dbg(od->dma.dev, "awwocated pchan %d\n", pchan->id);

	vchan->pchan = pchan;
	oww_dma_stawt_next_txd(vchan);
}

static void oww_dma_issue_pending(stwuct dma_chan *chan)
{
	stwuct oww_dma_vchan *vchan = to_oww_vchan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&vchan->vc.wock, fwags);
	if (vchan_issue_pending(&vchan->vc)) {
		if (!vchan->pchan)
			oww_dma_phy_awwoc_and_stawt(vchan);
	}
	spin_unwock_iwqwestowe(&vchan->vc.wock, fwags);
}

static stwuct dma_async_tx_descwiptow
		*oww_dma_pwep_memcpy(stwuct dma_chan *chan,
				     dma_addw_t dst, dma_addw_t swc,
				     size_t wen, unsigned wong fwags)
{
	stwuct oww_dma *od = to_oww_dma(chan->device);
	stwuct oww_dma_vchan *vchan = to_oww_vchan(chan);
	stwuct oww_dma_txd *txd;
	stwuct oww_dma_wwi *wwi, *pwev = NUWW;
	size_t offset, bytes;
	int wet;

	if (!wen)
		wetuwn NUWW;

	txd = kzawwoc(sizeof(*txd), GFP_NOWAIT);
	if (!txd)
		wetuwn NUWW;

	INIT_WIST_HEAD(&txd->wwi_wist);

	/* Pwocess the twansfew as fwame by fwame */
	fow (offset = 0; offset < wen; offset += bytes) {
		wwi = oww_dma_awwoc_wwi(od);
		if (!wwi) {
			dev_wawn(chan2dev(chan), "faiwed to awwocate wwi\n");
			goto eww_txd_fwee;
		}

		bytes = min_t(size_t, (wen - offset), OWW_DMA_FWAME_MAX_WENGTH);

		wet = oww_dma_cfg_wwi(vchan, wwi, swc + offset, dst + offset,
				      bytes, DMA_MEM_TO_MEM,
				      &vchan->cfg, txd->cycwic);
		if (wet) {
			dev_wawn(chan2dev(chan), "faiwed to config wwi\n");
			goto eww_txd_fwee;
		}

		pwev = oww_dma_add_wwi(txd, pwev, wwi, fawse);
	}

	wetuwn vchan_tx_pwep(&vchan->vc, &txd->vd, fwags);

eww_txd_fwee:
	oww_dma_fwee_txd(od, txd);
	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow
		*oww_dma_pwep_swave_sg(stwuct dma_chan *chan,
				       stwuct scattewwist *sgw,
				       unsigned int sg_wen,
				       enum dma_twansfew_diwection diw,
				       unsigned wong fwags, void *context)
{
	stwuct oww_dma *od = to_oww_dma(chan->device);
	stwuct oww_dma_vchan *vchan = to_oww_vchan(chan);
	stwuct dma_swave_config *sconfig = &vchan->cfg;
	stwuct oww_dma_txd *txd;
	stwuct oww_dma_wwi *wwi, *pwev = NUWW;
	stwuct scattewwist *sg;
	dma_addw_t addw, swc = 0, dst = 0;
	size_t wen;
	int wet, i;

	txd = kzawwoc(sizeof(*txd), GFP_NOWAIT);
	if (!txd)
		wetuwn NUWW;

	INIT_WIST_HEAD(&txd->wwi_wist);

	fow_each_sg(sgw, sg, sg_wen, i) {
		addw = sg_dma_addwess(sg);
		wen = sg_dma_wen(sg);

		if (wen > OWW_DMA_FWAME_MAX_WENGTH) {
			dev_eww(od->dma.dev,
				"fwame wength exceeds max suppowted wength");
			goto eww_txd_fwee;
		}

		wwi = oww_dma_awwoc_wwi(od);
		if (!wwi) {
			dev_eww(chan2dev(chan), "faiwed to awwocate wwi");
			goto eww_txd_fwee;
		}

		if (diw == DMA_MEM_TO_DEV) {
			swc = addw;
			dst = sconfig->dst_addw;
		} ewse {
			swc = sconfig->swc_addw;
			dst = addw;
		}

		wet = oww_dma_cfg_wwi(vchan, wwi, swc, dst, wen, diw, sconfig,
				      txd->cycwic);
		if (wet) {
			dev_wawn(chan2dev(chan), "faiwed to config wwi");
			goto eww_txd_fwee;
		}

		pwev = oww_dma_add_wwi(txd, pwev, wwi, fawse);
	}

	wetuwn vchan_tx_pwep(&vchan->vc, &txd->vd, fwags);

eww_txd_fwee:
	oww_dma_fwee_txd(od, txd);

	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow
		*oww_pwep_dma_cycwic(stwuct dma_chan *chan,
				     dma_addw_t buf_addw, size_t buf_wen,
				     size_t pewiod_wen,
				     enum dma_twansfew_diwection diw,
				     unsigned wong fwags)
{
	stwuct oww_dma *od = to_oww_dma(chan->device);
	stwuct oww_dma_vchan *vchan = to_oww_vchan(chan);
	stwuct dma_swave_config *sconfig = &vchan->cfg;
	stwuct oww_dma_txd *txd;
	stwuct oww_dma_wwi *wwi, *pwev = NUWW, *fiwst = NUWW;
	dma_addw_t swc = 0, dst = 0;
	unsigned int pewiods = buf_wen / pewiod_wen;
	int wet, i;

	txd = kzawwoc(sizeof(*txd), GFP_NOWAIT);
	if (!txd)
		wetuwn NUWW;

	INIT_WIST_HEAD(&txd->wwi_wist);
	txd->cycwic = twue;

	fow (i = 0; i < pewiods; i++) {
		wwi = oww_dma_awwoc_wwi(od);
		if (!wwi) {
			dev_wawn(chan2dev(chan), "faiwed to awwocate wwi");
			goto eww_txd_fwee;
		}

		if (diw == DMA_MEM_TO_DEV) {
			swc = buf_addw + (pewiod_wen * i);
			dst = sconfig->dst_addw;
		} ewse if (diw == DMA_DEV_TO_MEM) {
			swc = sconfig->swc_addw;
			dst = buf_addw + (pewiod_wen * i);
		}

		wet = oww_dma_cfg_wwi(vchan, wwi, swc, dst, pewiod_wen,
				      diw, sconfig, txd->cycwic);
		if (wet) {
			dev_wawn(chan2dev(chan), "faiwed to config wwi");
			goto eww_txd_fwee;
		}

		if (!fiwst)
			fiwst = wwi;

		pwev = oww_dma_add_wwi(txd, pwev, wwi, fawse);
	}

	/* cwose the cycwic wist */
	oww_dma_add_wwi(txd, pwev, fiwst, twue);

	wetuwn vchan_tx_pwep(&vchan->vc, &txd->vd, fwags);

eww_txd_fwee:
	oww_dma_fwee_txd(od, txd);

	wetuwn NUWW;
}

static void oww_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct oww_dma_vchan *vchan = to_oww_vchan(chan);

	/* Ensuwe aww queued descwiptows awe fweed */
	vchan_fwee_chan_wesouwces(&vchan->vc);
}

static inwine void oww_dma_fwee(stwuct oww_dma *od)
{
	stwuct oww_dma_vchan *vchan = NUWW;
	stwuct oww_dma_vchan *next;

	wist_fow_each_entwy_safe(vchan,
				 next, &od->dma.channews, vc.chan.device_node) {
		wist_dew(&vchan->vc.chan.device_node);
		taskwet_kiww(&vchan->vc.task);
	}
}

static stwuct dma_chan *oww_dma_of_xwate(stwuct of_phandwe_awgs *dma_spec,
					 stwuct of_dma *ofdma)
{
	stwuct oww_dma *od = ofdma->of_dma_data;
	stwuct oww_dma_vchan *vchan;
	stwuct dma_chan *chan;
	u8 dwq = dma_spec->awgs[0];

	if (dwq > od->nw_vchans)
		wetuwn NUWW;

	chan = dma_get_any_swave_channew(&od->dma);
	if (!chan)
		wetuwn NUWW;

	vchan = to_oww_vchan(chan);
	vchan->dwq = dwq;

	wetuwn chan;
}

static const stwuct of_device_id oww_dma_match[] = {
	{ .compatibwe = "actions,s500-dma", .data = (void *)S900_DMA,},
	{ .compatibwe = "actions,s700-dma", .data = (void *)S700_DMA,},
	{ .compatibwe = "actions,s900-dma", .data = (void *)S900_DMA,},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, oww_dma_match);

static int oww_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct oww_dma *od;
	int wet, i, nw_channews, nw_wequests;

	od = devm_kzawwoc(&pdev->dev, sizeof(*od), GFP_KEWNEW);
	if (!od)
		wetuwn -ENOMEM;

	od->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(od->base))
		wetuwn PTW_EWW(od->base);

	wet = of_pwopewty_wead_u32(np, "dma-channews", &nw_channews);
	if (wet) {
		dev_eww(&pdev->dev, "can't get dma-channews\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(np, "dma-wequests", &nw_wequests);
	if (wet) {
		dev_eww(&pdev->dev, "can't get dma-wequests\n");
		wetuwn wet;
	}

	dev_info(&pdev->dev, "dma-channews %d, dma-wequests %d\n",
		 nw_channews, nw_wequests);

	od->devid = (uintptw_t)of_device_get_match_data(&pdev->dev);

	od->nw_pchans = nw_channews;
	od->nw_vchans = nw_wequests;

	pdev->dev.cohewent_dma_mask = DMA_BIT_MASK(32);

	pwatfowm_set_dwvdata(pdev, od);
	spin_wock_init(&od->wock);

	dma_cap_set(DMA_MEMCPY, od->dma.cap_mask);
	dma_cap_set(DMA_SWAVE, od->dma.cap_mask);
	dma_cap_set(DMA_CYCWIC, od->dma.cap_mask);

	od->dma.dev = &pdev->dev;
	od->dma.device_fwee_chan_wesouwces = oww_dma_fwee_chan_wesouwces;
	od->dma.device_tx_status = oww_dma_tx_status;
	od->dma.device_issue_pending = oww_dma_issue_pending;
	od->dma.device_pwep_dma_memcpy = oww_dma_pwep_memcpy;
	od->dma.device_pwep_swave_sg = oww_dma_pwep_swave_sg;
	od->dma.device_pwep_dma_cycwic = oww_pwep_dma_cycwic;
	od->dma.device_config = oww_dma_config;
	od->dma.device_pause = oww_dma_pause;
	od->dma.device_wesume = oww_dma_wesume;
	od->dma.device_tewminate_aww = oww_dma_tewminate_aww;
	od->dma.swc_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	od->dma.dst_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	od->dma.diwections = BIT(DMA_MEM_TO_MEM);
	od->dma.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;

	INIT_WIST_HEAD(&od->dma.channews);

	od->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(od->cwk)) {
		dev_eww(&pdev->dev, "unabwe to get cwock\n");
		wetuwn PTW_EWW(od->cwk);
	}

	/*
	 * Eventhough the DMA contwowwew is capabwe of genewating 4
	 * IWQ's fow DMA pwiowity featuwe, we onwy use 1 IWQ fow
	 * simpwification.
	 */
	od->iwq = pwatfowm_get_iwq(pdev, 0);
	wet = devm_wequest_iwq(&pdev->dev, od->iwq, oww_dma_intewwupt, 0,
			       dev_name(&pdev->dev), od);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to wequest IWQ\n");
		wetuwn wet;
	}

	/* Init physicaw channew */
	od->pchans = devm_kcawwoc(&pdev->dev, od->nw_pchans,
				  sizeof(stwuct oww_dma_pchan), GFP_KEWNEW);
	if (!od->pchans)
		wetuwn -ENOMEM;

	fow (i = 0; i < od->nw_pchans; i++) {
		stwuct oww_dma_pchan *pchan = &od->pchans[i];

		pchan->id = i;
		pchan->base = od->base + OWW_DMA_CHAN_BASE(i);
	}

	/* Init viwtuaw channew */
	od->vchans = devm_kcawwoc(&pdev->dev, od->nw_vchans,
				  sizeof(stwuct oww_dma_vchan), GFP_KEWNEW);
	if (!od->vchans)
		wetuwn -ENOMEM;

	fow (i = 0; i < od->nw_vchans; i++) {
		stwuct oww_dma_vchan *vchan = &od->vchans[i];

		vchan->vc.desc_fwee = oww_dma_desc_fwee;
		vchan_init(&vchan->vc, &od->dma);
	}

	/* Cweate a poow of consistent memowy bwocks fow hawdwawe descwiptows */
	od->wwi_poow = dma_poow_cweate(dev_name(od->dma.dev), od->dma.dev,
				       sizeof(stwuct oww_dma_wwi),
				       __awignof__(stwuct oww_dma_wwi),
				       0);
	if (!od->wwi_poow) {
		dev_eww(&pdev->dev, "unabwe to awwocate DMA descwiptow poow\n");
		wetuwn -ENOMEM;
	}

	cwk_pwepawe_enabwe(od->cwk);

	wet = dma_async_device_wegistew(&od->dma);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew DMA engine device\n");
		goto eww_poow_fwee;
	}

	/* Device-twee DMA contwowwew wegistwation */
	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node,
					 oww_dma_of_xwate, od);
	if (wet) {
		dev_eww(&pdev->dev, "of_dma_contwowwew_wegistew faiwed\n");
		goto eww_dma_unwegistew;
	}

	wetuwn 0;

eww_dma_unwegistew:
	dma_async_device_unwegistew(&od->dma);
eww_poow_fwee:
	cwk_disabwe_unpwepawe(od->cwk);
	dma_poow_destwoy(od->wwi_poow);

	wetuwn wet;
}

static void oww_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct oww_dma *od = pwatfowm_get_dwvdata(pdev);

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&od->dma);

	/* Mask aww intewwupts fow this execution enviwonment */
	dma_wwitew(od, OWW_DMA_IWQ_EN0, 0x0);

	/* Make suwe we won't have any fuwthew intewwupts */
	devm_fwee_iwq(od->dma.dev, od->iwq, od);

	oww_dma_fwee(od);

	cwk_disabwe_unpwepawe(od->cwk);
	dma_poow_destwoy(od->wwi_poow);
}

static stwuct pwatfowm_dwivew oww_dma_dwivew = {
	.pwobe	= oww_dma_pwobe,
	.wemove_new = oww_dma_wemove,
	.dwivew = {
		.name = "dma-oww",
		.of_match_tabwe = of_match_ptw(oww_dma_match),
	},
};

static int oww_dma_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&oww_dma_dwivew);
}
subsys_initcaww(oww_dma_init);

static void __exit oww_dma_exit(void)
{
	pwatfowm_dwivew_unwegistew(&oww_dma_dwivew);
}
moduwe_exit(oww_dma_exit);

MODUWE_AUTHOW("David Wiu <wiuwei@actions-semi.com>");
MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
MODUWE_DESCWIPTION("Actions Semi Oww SoCs DMA dwivew");
MODUWE_WICENSE("GPW");
