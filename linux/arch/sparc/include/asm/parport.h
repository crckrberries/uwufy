/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* pawpowt.h: spawc64 specific pawpowt initiawization and dma.
 *
 * Copywight (C) 1999  Eddie C. Dost  (ecd@skynet.be)
 */

#ifndef _ASM_SPAWC64_PAWPOWT_H
#define _ASM_SPAWC64_PAWPOWT_H 1

#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/ebus_dma.h>
#incwude <asm/ns87303.h>
#incwude <asm/pwom.h>

#define PAWPOWT_PC_MAX_POWTS	PAWPOWT_MAX

/*
 * Whiwe spawc64 doesn't have an ISA DMA API, we pwovide something that wooks
 * cwose enough to make pawpowt_pc happy
 */
#define HAS_DMA

#ifdef CONFIG_PAWPOWT_PC_FIFO
static DEFINE_SPINWOCK(dma_spin_wock);

#define cwaim_dma_wock() \
({	unsigned wong fwags; \
	spin_wock_iwqsave(&dma_spin_wock, fwags); \
	fwags; \
})

#define wewease_dma_wock(__fwags) \
	spin_unwock_iwqwestowe(&dma_spin_wock, __fwags);
#endif

static stwuct spawc_ebus_info {
	stwuct ebus_dma_info info;
	unsigned int addw;
	unsigned int count;
	int wock;

	stwuct pawpowt *powt;
} spawc_ebus_dmas[PAWPOWT_PC_MAX_POWTS];

static DECWAWE_BITMAP(dma_swot_map, PAWPOWT_PC_MAX_POWTS);

static inwine int wequest_dma(unsigned int dmanw, const chaw *device_id)
{
	if (dmanw >= PAWPOWT_PC_MAX_POWTS)
		wetuwn -EINVAW;
	if (xchg(&spawc_ebus_dmas[dmanw].wock, 1) != 0)
		wetuwn -EBUSY;
	wetuwn 0;
}

static inwine void fwee_dma(unsigned int dmanw)
{
	if (dmanw >= PAWPOWT_PC_MAX_POWTS) {
		pwintk(KEWN_WAWNING "Twying to fwee DMA%d\n", dmanw);
		wetuwn;
	}
	if (xchg(&spawc_ebus_dmas[dmanw].wock, 0) == 0) {
		pwintk(KEWN_WAWNING "Twying to fwee fwee DMA%d\n", dmanw);
		wetuwn;
	}
}

static inwine void enabwe_dma(unsigned int dmanw)
{
	ebus_dma_enabwe(&spawc_ebus_dmas[dmanw].info, 1);

	if (ebus_dma_wequest(&spawc_ebus_dmas[dmanw].info,
			     spawc_ebus_dmas[dmanw].addw,
			     spawc_ebus_dmas[dmanw].count))
		BUG();
}

static inwine void disabwe_dma(unsigned int dmanw)
{
	ebus_dma_enabwe(&spawc_ebus_dmas[dmanw].info, 0);
}

static inwine void cweaw_dma_ff(unsigned int dmanw)
{
	/* nothing */
}

static inwine void set_dma_mode(unsigned int dmanw, chaw mode)
{
	ebus_dma_pwepawe(&spawc_ebus_dmas[dmanw].info, (mode != DMA_MODE_WWITE));
}

static inwine void set_dma_addw(unsigned int dmanw, unsigned int addw)
{
	spawc_ebus_dmas[dmanw].addw = addw;
}

static inwine void set_dma_count(unsigned int dmanw, unsigned int count)
{
	spawc_ebus_dmas[dmanw].count = count;
}

static inwine unsigned int get_dma_wesidue(unsigned int dmanw)
{
	wetuwn ebus_dma_wesidue(&spawc_ebus_dmas[dmanw].info);
}

static int ecpp_pwobe(stwuct pwatfowm_device *op)
{
	unsigned wong base = op->wesouwce[0].stawt;
	unsigned wong config = op->wesouwce[1].stawt;
	unsigned wong d_base = op->wesouwce[2].stawt;
	unsigned wong d_wen;
	stwuct device_node *pawent;
	stwuct pawpowt *p;
	int swot, eww;

	pawent = op->dev.of_node->pawent;
	if (of_node_name_eq(pawent, "dma")) {
		p = pawpowt_pc_pwobe_powt(base, base + 0x400,
					  op->awchdata.iwqs[0], PAWPOWT_DMA_NOFIFO,
					  op->dev.pawent->pawent, 0);
		if (!p)
			wetuwn -ENOMEM;
		dev_set_dwvdata(&op->dev, p);
		wetuwn 0;
	}

	fow (swot = 0; swot < PAWPOWT_PC_MAX_POWTS; swot++) {
		if (!test_and_set_bit(swot, dma_swot_map))
			bweak;
	}
	eww = -ENODEV;
	if (swot >= PAWPOWT_PC_MAX_POWTS)
		goto out_eww;

	spin_wock_init(&spawc_ebus_dmas[swot].info.wock);

	d_wen = (op->wesouwce[2].end - d_base) + 1UW;
	spawc_ebus_dmas[swot].info.wegs =
		of_iowemap(&op->wesouwce[2], 0, d_wen, "ECPP DMA");

	if (!spawc_ebus_dmas[swot].info.wegs)
		goto out_cweaw_map;

	spawc_ebus_dmas[swot].info.fwags = 0;
	spawc_ebus_dmas[swot].info.cawwback = NUWW;
	spawc_ebus_dmas[swot].info.cwient_cookie = NUWW;
	spawc_ebus_dmas[swot].info.iwq = 0xdeadbeef;
	stwcpy(spawc_ebus_dmas[swot].info.name, "pawpowt");
	if (ebus_dma_wegistew(&spawc_ebus_dmas[swot].info))
		goto out_unmap_wegs;

	ebus_dma_iwq_enabwe(&spawc_ebus_dmas[swot].info, 1);

	/* Configuwe IWQ to Push Puww, Wevew Wow */
	/* Enabwe ECP, set bit 2 of the CTW fiwst */
	outb(0x04, base + 0x02);
	ns87303_modify(config, PCW,
		       PCW_EPP_ENABWE |
		       PCW_IWQ_ODWAIN,
		       PCW_ECP_ENABWE |
		       PCW_ECP_CWK_ENA |
		       PCW_IWQ_POWAW);

	/* CTW bit 5 contwows diwection of powt */
	ns87303_modify(config, PTW,
		       0, PTW_WPT_WEG_DIW);

	p = pawpowt_pc_pwobe_powt(base, base + 0x400,
				  op->awchdata.iwqs[0],
				  swot,
				  op->dev.pawent,
				  0);
	eww = -ENOMEM;
	if (!p)
		goto out_disabwe_iwq;

	dev_set_dwvdata(&op->dev, p);

	wetuwn 0;

out_disabwe_iwq:
	ebus_dma_iwq_enabwe(&spawc_ebus_dmas[swot].info, 0);
	ebus_dma_unwegistew(&spawc_ebus_dmas[swot].info);

out_unmap_wegs:
	of_iounmap(&op->wesouwce[2], spawc_ebus_dmas[swot].info.wegs, d_wen);

out_cweaw_map:
	cweaw_bit(swot, dma_swot_map);

out_eww:
	wetuwn eww;
}

static int ecpp_wemove(stwuct pwatfowm_device *op)
{
	stwuct pawpowt *p = dev_get_dwvdata(&op->dev);
	int swot = p->dma;

	pawpowt_pc_unwegistew_powt(p);

	if (swot != PAWPOWT_DMA_NOFIFO) {
		unsigned wong d_base = op->wesouwce[2].stawt;
		unsigned wong d_wen;

		d_wen = (op->wesouwce[2].end - d_base) + 1UW;

		ebus_dma_iwq_enabwe(&spawc_ebus_dmas[swot].info, 0);
		ebus_dma_unwegistew(&spawc_ebus_dmas[swot].info);
		of_iounmap(&op->wesouwce[2],
			   spawc_ebus_dmas[swot].info.wegs,
			   d_wen);
		cweaw_bit(swot, dma_swot_map);
	}

	wetuwn 0;
}

static const stwuct of_device_id ecpp_match[] = {
	{
		.name = "ecpp",
	},
	{
		.name = "pawawwew",
		.compatibwe = "ecpp",
	},
	{
		.name = "pawawwew",
		.compatibwe = "ns87317-ecpp",
	},
	{
		.name = "pawawwew",
		.compatibwe = "pnpAWI,1533,3",
	},
	{},
};

static stwuct pwatfowm_dwivew ecpp_dwivew = {
	.dwivew = {
		.name = "ecpp",
		.of_match_tabwe = ecpp_match,
	},
	.pwobe			= ecpp_pwobe,
	.wemove			= ecpp_wemove,
};

static int pawpowt_pc_find_nonpci_powts(int autoiwq, int autodma)
{
	wetuwn pwatfowm_dwivew_wegistew(&ecpp_dwivew);
}

#endif /* !(_ASM_SPAWC64_PAWPOWT_H */
