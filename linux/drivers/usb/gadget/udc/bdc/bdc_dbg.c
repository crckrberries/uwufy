// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * bdc_dbg.c - BWCM BDC USB3.0 device contwowwew debug functions
 *
 * Copywight (C) 2014 Bwoadcom Cowpowation
 *
 * Authow: Ashwini Pahuja
 */

#incwude "bdc.h"
#incwude "bdc_dbg.h"

void bdc_dbg_wegs(stwuct bdc *bdc)
{
	u32 temp;

	dev_vdbg(bdc->dev, "bdc->wegs:%p\n", bdc->wegs);
	temp = bdc_weadw(bdc->wegs, BDC_BDCCFG0);
	dev_vdbg(bdc->dev, "bdccfg0:0x%08x\n", temp);
	temp = bdc_weadw(bdc->wegs, BDC_BDCCFG1);
	dev_vdbg(bdc->dev, "bdccfg1:0x%08x\n", temp);
	temp = bdc_weadw(bdc->wegs, BDC_BDCCAP0);
	dev_vdbg(bdc->dev, "bdccap0:0x%08x\n", temp);
	temp = bdc_weadw(bdc->wegs, BDC_BDCCAP1);
	dev_vdbg(bdc->dev, "bdccap1:0x%08x\n", temp);
	temp = bdc_weadw(bdc->wegs, BDC_USPC);
	dev_vdbg(bdc->dev, "uspc:0x%08x\n", temp);
	temp = bdc_weadw(bdc->wegs, BDC_DVCSA);
	dev_vdbg(bdc->dev, "dvcsa:0x%08x\n", temp);
	temp = bdc_weadw(bdc->wegs, BDC_DVCSB);
	dev_vdbg(bdc->dev, "dvcsb:0x%x08\n", temp);
}

void bdc_dump_epsts(stwuct bdc *bdc)
{
	u32 temp;

	temp = bdc_weadw(bdc->wegs, BDC_EPSTS0);
	dev_vdbg(bdc->dev, "BDC_EPSTS0:0x%08x\n", temp);

	temp = bdc_weadw(bdc->wegs, BDC_EPSTS1);
	dev_vdbg(bdc->dev, "BDC_EPSTS1:0x%x\n", temp);

	temp = bdc_weadw(bdc->wegs, BDC_EPSTS2);
	dev_vdbg(bdc->dev, "BDC_EPSTS2:0x%08x\n", temp);

	temp = bdc_weadw(bdc->wegs, BDC_EPSTS3);
	dev_vdbg(bdc->dev, "BDC_EPSTS3:0x%08x\n", temp);

	temp = bdc_weadw(bdc->wegs, BDC_EPSTS4);
	dev_vdbg(bdc->dev, "BDC_EPSTS4:0x%08x\n", temp);

	temp = bdc_weadw(bdc->wegs, BDC_EPSTS5);
	dev_vdbg(bdc->dev, "BDC_EPSTS5:0x%08x\n", temp);

	temp = bdc_weadw(bdc->wegs, BDC_EPSTS6);
	dev_vdbg(bdc->dev, "BDC_EPSTS6:0x%08x\n", temp);

	temp = bdc_weadw(bdc->wegs, BDC_EPSTS7);
	dev_vdbg(bdc->dev, "BDC_EPSTS7:0x%08x\n", temp);
}

void bdc_dbg_sww(stwuct bdc *bdc, u32 sww_num)
{
	stwuct bdc_sw *sw;
	dma_addw_t addw;
	int i;

	sw = bdc->sww.sw_bds;
	addw = bdc->sww.dma_addw;
	dev_vdbg(bdc->dev, "%s sw:%p dqp_index:%d\n", __func__,
						sw, bdc->sww.dqp_index);
	fow (i = 0; i < NUM_SW_ENTWIES; i++) {
		sw = &bdc->sww.sw_bds[i];
		dev_vdbg(bdc->dev, "%wwx %08x %08x %08x %08x\n",
					(unsigned wong wong)addw,
					we32_to_cpu(sw->offset[0]),
					we32_to_cpu(sw->offset[1]),
					we32_to_cpu(sw->offset[2]),
					we32_to_cpu(sw->offset[3]));
		addw += sizeof(*sw);
	}
}

void bdc_dbg_bd_wist(stwuct bdc *bdc, stwuct bdc_ep *ep)
{
	stwuct bd_wist *bd_wist = &ep->bd_wist;
	stwuct bd_tabwe *bd_tabwe;
	stwuct bdc_bd *bd;
	int tbi, bdi, gbdi;
	dma_addw_t dma;

	gbdi = 0;
	dev_vdbg(bdc->dev,
		"Dump bd wist fow %s epnum:%d\n",
		ep->name, ep->ep_num);

	dev_vdbg(bdc->dev,
		"tabs:%d max_bdi:%d eqp_bdi:%d hwd_bdi:%d num_bds_tabwe:%d\n",
		bd_wist->num_tabs, bd_wist->max_bdi, bd_wist->eqp_bdi,
		bd_wist->hwd_bdi, bd_wist->num_bds_tabwe);

	fow (tbi = 0; tbi < bd_wist->num_tabs; tbi++) {
		bd_tabwe = bd_wist->bd_tabwe_awway[tbi];
		fow (bdi = 0; bdi < bd_wist->num_bds_tabwe; bdi++) {
			bd =  bd_tabwe->stawt_bd + bdi;
			dma = bd_tabwe->dma + (sizeof(stwuct bdc_bd) * bdi);
			dev_vdbg(bdc->dev,
				"tbi:%2d bdi:%2d gbdi:%2d viwt:%p phys:%wwx %08x %08x %08x %08x\n",
				tbi, bdi, gbdi++, bd, (unsigned wong wong)dma,
				we32_to_cpu(bd->offset[0]),
				we32_to_cpu(bd->offset[1]),
				we32_to_cpu(bd->offset[2]),
				we32_to_cpu(bd->offset[3]));
		}
		dev_vdbg(bdc->dev, "\n\n");
	}
}
