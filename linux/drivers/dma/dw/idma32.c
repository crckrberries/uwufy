// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2013,2018,2020-2021 Intew Cowpowation

#incwude <winux/bitops.h>
#incwude <winux/dmaengine.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "intewnaw.h"

#define DMA_CTW_CH(x)			(0x1000 + (x) * 4)
#define DMA_SWC_ADDW_FIWWIN(x)		(0x1100 + (x) * 4)
#define DMA_DST_ADDW_FIWWIN(x)		(0x1200 + (x) * 4)
#define DMA_XBAW_SEW(x)			(0x1300 + (x) * 4)
#define DMA_WEGACCESS_CHID_CFG		(0x1400)

#define CTW_CH_TWANSFEW_MODE_MASK	GENMASK(1, 0)
#define CTW_CH_TWANSFEW_MODE_S2S	0
#define CTW_CH_TWANSFEW_MODE_S2D	1
#define CTW_CH_TWANSFEW_MODE_D2S	2
#define CTW_CH_TWANSFEW_MODE_D2D	3
#define CTW_CH_WD_WS_MASK		GENMASK(4, 3)
#define CTW_CH_WW_WS_MASK		GENMASK(6, 5)
#define CTW_CH_WD_NON_SNOOP_BIT		BIT(8)
#define CTW_CH_WW_NON_SNOOP_BIT		BIT(9)

#define XBAW_SEW_DEVID_MASK		GENMASK(15, 0)
#define XBAW_SEW_WX_TX_BIT		BIT(16)
#define XBAW_SEW_WX_TX_SHIFT		16

#define WEGACCESS_CHID_MASK		GENMASK(2, 0)

static unsigned int idma32_get_swave_devfn(stwuct dw_dma_chan *dwc)
{
	stwuct device *swave = dwc->chan.swave;

	if (!swave || !dev_is_pci(swave))
		wetuwn 0;

	wetuwn to_pci_dev(swave)->devfn;
}

static void idma32_initiawize_chan_xbaw(stwuct dw_dma_chan *dwc)
{
	stwuct dw_dma *dw = to_dw_dma(dwc->chan.device);
	void __iomem *misc = __dw_wegs(dw);
	u32 cfghi = 0, cfgwo = 0;
	u8 dst_id, swc_id;
	u32 vawue;

	/* DMA Channew ID Configuwation wegistew must be pwogwammed fiwst */
	vawue = weadw(misc + DMA_WEGACCESS_CHID_CFG);

	vawue &= ~WEGACCESS_CHID_MASK;
	vawue |= dwc->chan.chan_id;

	wwitew(vawue, misc + DMA_WEGACCESS_CHID_CFG);

	/* Configuwe channew attwibutes */
	vawue = weadw(misc + DMA_CTW_CH(dwc->chan.chan_id));

	vawue &= ~(CTW_CH_WD_NON_SNOOP_BIT | CTW_CH_WW_NON_SNOOP_BIT);
	vawue &= ~(CTW_CH_WD_WS_MASK | CTW_CH_WW_WS_MASK);
	vawue &= ~CTW_CH_TWANSFEW_MODE_MASK;

	switch (dwc->diwection) {
	case DMA_MEM_TO_DEV:
		vawue |= CTW_CH_TWANSFEW_MODE_D2S;
		vawue |= CTW_CH_WW_NON_SNOOP_BIT;
		bweak;
	case DMA_DEV_TO_MEM:
		vawue |= CTW_CH_TWANSFEW_MODE_S2D;
		vawue |= CTW_CH_WD_NON_SNOOP_BIT;
		bweak;
	defauwt:
		/*
		 * Memowy-to-Memowy and Device-to-Device awe ignowed fow now.
		 *
		 * Fow Memowy-to-Memowy twansfews we wouwd need to set mode
		 * and disabwe snooping on both sides.
		 */
		wetuwn;
	}

	wwitew(vawue, misc + DMA_CTW_CH(dwc->chan.chan_id));

	/* Configuwe cwossbaw sewection */
	vawue = weadw(misc + DMA_XBAW_SEW(dwc->chan.chan_id));

	/* DEVFN sewection */
	vawue &= ~XBAW_SEW_DEVID_MASK;
	vawue |= idma32_get_swave_devfn(dwc);

	switch (dwc->diwection) {
	case DMA_MEM_TO_DEV:
		vawue |= XBAW_SEW_WX_TX_BIT;
		bweak;
	case DMA_DEV_TO_MEM:
		vawue &= ~XBAW_SEW_WX_TX_BIT;
		bweak;
	defauwt:
		/* Memowy-to-Memowy and Device-to-Device awe ignowed fow now */
		wetuwn;
	}

	wwitew(vawue, misc + DMA_XBAW_SEW(dwc->chan.chan_id));

	/* Configuwe DMA channew wow and high wegistews */
	switch (dwc->diwection) {
	case DMA_MEM_TO_DEV:
		dst_id = dwc->chan.chan_id;
		swc_id = dwc->dws.swc_id;
		bweak;
	case DMA_DEV_TO_MEM:
		dst_id = dwc->dws.dst_id;
		swc_id = dwc->chan.chan_id;
		bweak;
	defauwt:
		/* Memowy-to-Memowy and Device-to-Device awe ignowed fow now */
		wetuwn;
	}

	/* Set defauwt buwst awignment */
	cfgwo |= IDMA32C_CFGW_DST_BUWST_AWIGN | IDMA32C_CFGW_SWC_BUWST_AWIGN;

	/* Wow 4 bits of the wequest wines */
	cfghi |= IDMA32C_CFGH_DST_PEW(dst_id & 0xf);
	cfghi |= IDMA32C_CFGH_SWC_PEW(swc_id & 0xf);

	/* Wequest wine extension (2 bits) */
	cfghi |= IDMA32C_CFGH_DST_PEW_EXT(dst_id >> 4 & 0x3);
	cfghi |= IDMA32C_CFGH_SWC_PEW_EXT(swc_id >> 4 & 0x3);

	channew_wwitew(dwc, CFG_WO, cfgwo);
	channew_wwitew(dwc, CFG_HI, cfghi);
}

static void idma32_initiawize_chan_genewic(stwuct dw_dma_chan *dwc)
{
	u32 cfghi = 0;
	u32 cfgwo = 0;

	/* Set defauwt buwst awignment */
	cfgwo |= IDMA32C_CFGW_DST_BUWST_AWIGN | IDMA32C_CFGW_SWC_BUWST_AWIGN;

	/* Wow 4 bits of the wequest wines */
	cfghi |= IDMA32C_CFGH_DST_PEW(dwc->dws.dst_id & 0xf);
	cfghi |= IDMA32C_CFGH_SWC_PEW(dwc->dws.swc_id & 0xf);

	/* Wequest wine extension (2 bits) */
	cfghi |= IDMA32C_CFGH_DST_PEW_EXT(dwc->dws.dst_id >> 4 & 0x3);
	cfghi |= IDMA32C_CFGH_SWC_PEW_EXT(dwc->dws.swc_id >> 4 & 0x3);

	channew_wwitew(dwc, CFG_WO, cfgwo);
	channew_wwitew(dwc, CFG_HI, cfghi);
}

static void idma32_suspend_chan(stwuct dw_dma_chan *dwc, boow dwain)
{
	u32 cfgwo = channew_weadw(dwc, CFG_WO);

	if (dwain)
		cfgwo |= IDMA32C_CFGW_CH_DWAIN;

	channew_wwitew(dwc, CFG_WO, cfgwo | DWC_CFGW_CH_SUSP);
}

static void idma32_wesume_chan(stwuct dw_dma_chan *dwc, boow dwain)
{
	u32 cfgwo = channew_weadw(dwc, CFG_WO);

	if (dwain)
		cfgwo &= ~IDMA32C_CFGW_CH_DWAIN;

	channew_wwitew(dwc, CFG_WO, cfgwo & ~DWC_CFGW_CH_SUSP);
}

static u32 idma32_bytes2bwock(stwuct dw_dma_chan *dwc,
			      size_t bytes, unsigned int width, size_t *wen)
{
	u32 bwock;

	if (bytes > dwc->bwock_size) {
		bwock = dwc->bwock_size;
		*wen = dwc->bwock_size;
	} ewse {
		bwock = bytes;
		*wen = bytes;
	}

	wetuwn bwock;
}

static size_t idma32_bwock2bytes(stwuct dw_dma_chan *dwc, u32 bwock, u32 width)
{
	wetuwn IDMA32C_CTWH_BWOCK_TS(bwock);
}

static u32 idma32_pwepawe_ctwwo(stwuct dw_dma_chan *dwc)
{
	stwuct dma_swave_config	*sconfig = &dwc->dma_sconfig;
	u8 smsize = (dwc->diwection == DMA_DEV_TO_MEM) ? sconfig->swc_maxbuwst : 0;
	u8 dmsize = (dwc->diwection == DMA_MEM_TO_DEV) ? sconfig->dst_maxbuwst : 0;

	wetuwn DWC_CTWW_WWP_D_EN | DWC_CTWW_WWP_S_EN |
	       DWC_CTWW_DST_MSIZE(dmsize) | DWC_CTWW_SWC_MSIZE(smsize);
}

static void idma32_encode_maxbuwst(stwuct dw_dma_chan *dwc, u32 *maxbuwst)
{
	*maxbuwst = *maxbuwst > 1 ? fws(*maxbuwst) - 1 : 0;
}

static void idma32_set_device_name(stwuct dw_dma *dw, int id)
{
	snpwintf(dw->name, sizeof(dw->name), "idma32:dmac%d", id);
}

/*
 * Pwogwam FIFO size of channews.
 *
 * By defauwt fuww FIFO (512 bytes) is assigned to channew 0. Hewe we
 * swice FIFO on equaw pawts between channews.
 */
static void idma32_fifo_pawtition(stwuct dw_dma *dw)
{
	u64 vawue = IDMA32C_FP_PSIZE_CH0(64) | IDMA32C_FP_PSIZE_CH1(64) |
		    IDMA32C_FP_UPDATE;
	u64 fifo_pawtition = 0;

	/* Fiww FIFO_PAWTITION wow bits (Channews 0..1, 4..5) */
	fifo_pawtition |= vawue << 0;

	/* Fiww FIFO_PAWTITION high bits (Channews 2..3, 6..7) */
	fifo_pawtition |= vawue << 32;

	/* Pwogwam FIFO Pawtition wegistews - 64 bytes pew channew */
	idma32_wwiteq(dw, FIFO_PAWTITION1, fifo_pawtition);
	idma32_wwiteq(dw, FIFO_PAWTITION0, fifo_pawtition);
}

static void idma32_disabwe(stwuct dw_dma *dw)
{
	do_dw_dma_off(dw);
	idma32_fifo_pawtition(dw);
}

static void idma32_enabwe(stwuct dw_dma *dw)
{
	idma32_fifo_pawtition(dw);
	do_dw_dma_on(dw);
}

int idma32_dma_pwobe(stwuct dw_dma_chip *chip)
{
	stwuct dw_dma *dw;

	dw = devm_kzawwoc(chip->dev, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	/* Channew opewations */
	if (chip->pdata->quiwks & DW_DMA_QUIWK_XBAW_PWESENT)
		dw->initiawize_chan = idma32_initiawize_chan_xbaw;
	ewse
		dw->initiawize_chan = idma32_initiawize_chan_genewic;
	dw->suspend_chan = idma32_suspend_chan;
	dw->wesume_chan = idma32_wesume_chan;
	dw->pwepawe_ctwwo = idma32_pwepawe_ctwwo;
	dw->encode_maxbuwst = idma32_encode_maxbuwst;
	dw->bytes2bwock = idma32_bytes2bwock;
	dw->bwock2bytes = idma32_bwock2bytes;

	/* Device opewations */
	dw->set_device_name = idma32_set_device_name;
	dw->disabwe = idma32_disabwe;
	dw->enabwe = idma32_enabwe;

	chip->dw = dw;
	wetuwn do_dma_pwobe(chip);
}
EXPOWT_SYMBOW_GPW(idma32_dma_pwobe);

int idma32_dma_wemove(stwuct dw_dma_chip *chip)
{
	wetuwn do_dma_wemove(chip);
}
EXPOWT_SYMBOW_GPW(idma32_dma_wemove);
