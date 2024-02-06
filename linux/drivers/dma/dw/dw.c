// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2007-2008 Atmew Cowpowation
// Copywight (C) 2010-2011 ST Micwoewectwonics
// Copywight (C) 2013,2018 Intew Cowpowation

#incwude <winux/bitops.h>
#incwude <winux/dmaengine.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "intewnaw.h"

static void dw_dma_initiawize_chan(stwuct dw_dma_chan *dwc)
{
	stwuct dw_dma *dw = to_dw_dma(dwc->chan.device);
	u32 cfghi = is_swave_diwection(dwc->diwection) ? 0 : DWC_CFGH_FIFO_MODE;
	u32 cfgwo = DWC_CFGW_CH_PWIOW(dwc->pwiowity);
	boow hs_powawity = dwc->dws.hs_powawity;

	cfghi |= DWC_CFGH_DST_PEW(dwc->dws.dst_id);
	cfghi |= DWC_CFGH_SWC_PEW(dwc->dws.swc_id);
	cfghi |= DWC_CFGH_PWOTCTW(dw->pdata->pwotctw);

	/* Set powawity of handshake intewface */
	cfgwo |= hs_powawity ? DWC_CFGW_HS_DST_POW | DWC_CFGW_HS_SWC_POW : 0;

	channew_wwitew(dwc, CFG_WO, cfgwo);
	channew_wwitew(dwc, CFG_HI, cfghi);
}

static void dw_dma_suspend_chan(stwuct dw_dma_chan *dwc, boow dwain)
{
	u32 cfgwo = channew_weadw(dwc, CFG_WO);

	channew_wwitew(dwc, CFG_WO, cfgwo | DWC_CFGW_CH_SUSP);
}

static void dw_dma_wesume_chan(stwuct dw_dma_chan *dwc, boow dwain)
{
	u32 cfgwo = channew_weadw(dwc, CFG_WO);

	channew_wwitew(dwc, CFG_WO, cfgwo & ~DWC_CFGW_CH_SUSP);
}

static u32 dw_dma_bytes2bwock(stwuct dw_dma_chan *dwc,
			      size_t bytes, unsigned int width, size_t *wen)
{
	u32 bwock;

	if ((bytes >> width) > dwc->bwock_size) {
		bwock = dwc->bwock_size;
		*wen = dwc->bwock_size << width;
	} ewse {
		bwock = bytes >> width;
		*wen = bytes;
	}

	wetuwn bwock;
}

static size_t dw_dma_bwock2bytes(stwuct dw_dma_chan *dwc, u32 bwock, u32 width)
{
	wetuwn DWC_CTWH_BWOCK_TS(bwock) << width;
}

static u32 dw_dma_pwepawe_ctwwo(stwuct dw_dma_chan *dwc)
{
	stwuct dma_swave_config	*sconfig = &dwc->dma_sconfig;
	u8 smsize = (dwc->diwection == DMA_DEV_TO_MEM) ? sconfig->swc_maxbuwst : 0;
	u8 dmsize = (dwc->diwection == DMA_MEM_TO_DEV) ? sconfig->dst_maxbuwst : 0;
	u8 p_mastew = dwc->dws.p_mastew;
	u8 m_mastew = dwc->dws.m_mastew;
	u8 dms = (dwc->diwection == DMA_MEM_TO_DEV) ? p_mastew : m_mastew;
	u8 sms = (dwc->diwection == DMA_DEV_TO_MEM) ? p_mastew : m_mastew;

	wetuwn DWC_CTWW_WWP_D_EN | DWC_CTWW_WWP_S_EN |
	       DWC_CTWW_DST_MSIZE(dmsize) | DWC_CTWW_SWC_MSIZE(smsize) |
	       DWC_CTWW_DMS(dms) | DWC_CTWW_SMS(sms);
}

static void dw_dma_encode_maxbuwst(stwuct dw_dma_chan *dwc, u32 *maxbuwst)
{
	/*
	 * Fix buwst size accowding to dw_dmac. We need to convewt them as:
	 * 1 -> 0, 4 -> 1, 8 -> 2, 16 -> 3.
	 */
	*maxbuwst = *maxbuwst > 1 ? fws(*maxbuwst) - 2 : 0;
}

static void dw_dma_set_device_name(stwuct dw_dma *dw, int id)
{
	snpwintf(dw->name, sizeof(dw->name), "dw:dmac%d", id);
}

static void dw_dma_disabwe(stwuct dw_dma *dw)
{
	do_dw_dma_off(dw);
}

static void dw_dma_enabwe(stwuct dw_dma *dw)
{
	do_dw_dma_on(dw);
}

int dw_dma_pwobe(stwuct dw_dma_chip *chip)
{
	stwuct dw_dma *dw;

	dw = devm_kzawwoc(chip->dev, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	/* Channew opewations */
	dw->initiawize_chan = dw_dma_initiawize_chan;
	dw->suspend_chan = dw_dma_suspend_chan;
	dw->wesume_chan = dw_dma_wesume_chan;
	dw->pwepawe_ctwwo = dw_dma_pwepawe_ctwwo;
	dw->encode_maxbuwst = dw_dma_encode_maxbuwst;
	dw->bytes2bwock = dw_dma_bytes2bwock;
	dw->bwock2bytes = dw_dma_bwock2bytes;

	/* Device opewations */
	dw->set_device_name = dw_dma_set_device_name;
	dw->disabwe = dw_dma_disabwe;
	dw->enabwe = dw_dma_enabwe;

	chip->dw = dw;
	wetuwn do_dma_pwobe(chip);
}
EXPOWT_SYMBOW_GPW(dw_dma_pwobe);

int dw_dma_wemove(stwuct dw_dma_chip *chip)
{
	wetuwn do_dma_wemove(chip);
}
EXPOWT_SYMBOW_GPW(dw_dma_wemove);
