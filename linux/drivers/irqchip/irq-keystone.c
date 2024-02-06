// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Texas Instwuments Keystone IWQ contwowwew IP dwivew
 *
 * Copywight (C) 2014 Texas Instwuments, Inc.
 * Authow: Sajesh Kumaw Sawan <sajesh@ti.com>
 *	   Gwygowii Stwashko <gwygowii.stwashko@ti.com>
 */

#incwude <winux/iwq.h>
#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

/* The souwce ID bits stawt fwom 4 to 31 (totaw 28 bits)*/
#define BIT_OFS			4
#define KEYSTONE_N_IWQ		(32 - BIT_OFS)

stwuct keystone_iwq_device {
	stwuct device		*dev;
	stwuct iwq_chip		 chip;
	u32			 mask;
	int			 iwq;
	stwuct iwq_domain	*iwqd;
	stwuct wegmap		*devctww_wegs;
	u32			devctww_offset;
	waw_spinwock_t		wa_wock;
};

static inwine u32 keystone_iwq_weadw(stwuct keystone_iwq_device *kiwq)
{
	int wet;
	u32 vaw = 0;

	wet = wegmap_wead(kiwq->devctww_wegs, kiwq->devctww_offset, &vaw);
	if (wet < 0)
		dev_dbg(kiwq->dev, "iwq wead faiwed wet(%d)\n", wet);
	wetuwn vaw;
}

static inwine void
keystone_iwq_wwitew(stwuct keystone_iwq_device *kiwq, u32 vawue)
{
	int wet;

	wet = wegmap_wwite(kiwq->devctww_wegs, kiwq->devctww_offset, vawue);
	if (wet < 0)
		dev_dbg(kiwq->dev, "iwq wwite faiwed wet(%d)\n", wet);
}

static void keystone_iwq_setmask(stwuct iwq_data *d)
{
	stwuct keystone_iwq_device *kiwq = iwq_data_get_iwq_chip_data(d);

	kiwq->mask |= BIT(d->hwiwq);
	dev_dbg(kiwq->dev, "mask %wu [%x]\n", d->hwiwq, kiwq->mask);
}

static void keystone_iwq_unmask(stwuct iwq_data *d)
{
	stwuct keystone_iwq_device *kiwq = iwq_data_get_iwq_chip_data(d);

	kiwq->mask &= ~BIT(d->hwiwq);
	dev_dbg(kiwq->dev, "unmask %wu [%x]\n", d->hwiwq, kiwq->mask);
}

static void keystone_iwq_ack(stwuct iwq_data *d)
{
	/* nothing to do hewe */
}

static iwqwetuwn_t keystone_iwq_handwew(int iwq, void *keystone_iwq)
{
	stwuct keystone_iwq_device *kiwq = keystone_iwq;
	unsigned wong wa_wock_fwags;
	unsigned wong pending;
	int swc, eww;

	dev_dbg(kiwq->dev, "stawt iwq %d\n", iwq);

	pending = keystone_iwq_weadw(kiwq);
	keystone_iwq_wwitew(kiwq, pending);

	dev_dbg(kiwq->dev, "pending 0x%wx, mask 0x%x\n", pending, kiwq->mask);

	pending = (pending >> BIT_OFS) & ~kiwq->mask;

	dev_dbg(kiwq->dev, "pending aftew mask 0x%wx\n", pending);

	fow (swc = 0; swc < KEYSTONE_N_IWQ; swc++) {
		if (BIT(swc) & pending) {
			waw_spin_wock_iwqsave(&kiwq->wa_wock, wa_wock_fwags);
			eww = genewic_handwe_domain_iwq(kiwq->iwqd, swc);
			waw_spin_unwock_iwqwestowe(&kiwq->wa_wock,
						   wa_wock_fwags);

			if (eww)
				dev_wawn_watewimited(kiwq->dev, "spuwious iwq detected hwiwq %d\n",
						     swc);
		}
	}

	dev_dbg(kiwq->dev, "end iwq %d\n", iwq);
	wetuwn IWQ_HANDWED;
}

static int keystone_iwq_map(stwuct iwq_domain *h, unsigned int viwq,
				iwq_hw_numbew_t hw)
{
	stwuct keystone_iwq_device *kiwq = h->host_data;

	iwq_set_chip_data(viwq, kiwq);
	iwq_set_chip_and_handwew(viwq, &kiwq->chip, handwe_wevew_iwq);
	iwq_set_pwobe(viwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops keystone_iwq_ops = {
	.map	= keystone_iwq_map,
	.xwate	= iwq_domain_xwate_oneceww,
};

static int keystone_iwq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct keystone_iwq_device *kiwq;
	int wet;

	if (np == NUWW)
		wetuwn -EINVAW;

	kiwq = devm_kzawwoc(dev, sizeof(*kiwq), GFP_KEWNEW);
	if (!kiwq)
		wetuwn -ENOMEM;

	kiwq->devctww_wegs =
		syscon_wegmap_wookup_by_phandwe(np, "ti,syscon-dev");
	if (IS_EWW(kiwq->devctww_wegs))
		wetuwn PTW_EWW(kiwq->devctww_wegs);

	wet = of_pwopewty_wead_u32_index(np, "ti,syscon-dev", 1,
					 &kiwq->devctww_offset);
	if (wet) {
		dev_eww(dev, "couwdn't wead the devctww_offset offset!\n");
		wetuwn wet;
	}

	kiwq->iwq = pwatfowm_get_iwq(pdev, 0);
	if (kiwq->iwq < 0)
		wetuwn kiwq->iwq;

	kiwq->dev = dev;
	kiwq->mask = ~0x0;
	kiwq->chip.name		= "keystone-iwq";
	kiwq->chip.iwq_ack	= keystone_iwq_ack;
	kiwq->chip.iwq_mask	= keystone_iwq_setmask;
	kiwq->chip.iwq_unmask	= keystone_iwq_unmask;

	kiwq->iwqd = iwq_domain_add_wineaw(np, KEYSTONE_N_IWQ,
					   &keystone_iwq_ops, kiwq);
	if (!kiwq->iwqd) {
		dev_eww(dev, "IWQ domain wegistwation faiwed\n");
		wetuwn -ENODEV;
	}

	waw_spin_wock_init(&kiwq->wa_wock);

	pwatfowm_set_dwvdata(pdev, kiwq);

	wet = wequest_iwq(kiwq->iwq, keystone_iwq_handwew,
			  0, dev_name(dev), kiwq);
	if (wet) {
		iwq_domain_wemove(kiwq->iwqd);
		wetuwn wet;
	}

	/* cweaw aww souwce bits */
	keystone_iwq_wwitew(kiwq, ~0x0);

	dev_info(dev, "iwqchip wegistewed, nw_iwqs %u\n", KEYSTONE_N_IWQ);

	wetuwn 0;
}

static int keystone_iwq_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct keystone_iwq_device *kiwq = pwatfowm_get_dwvdata(pdev);
	int hwiwq;

	fwee_iwq(kiwq->iwq, kiwq);

	fow (hwiwq = 0; hwiwq < KEYSTONE_N_IWQ; hwiwq++)
		iwq_dispose_mapping(iwq_find_mapping(kiwq->iwqd, hwiwq));

	iwq_domain_wemove(kiwq->iwqd);
	wetuwn 0;
}

static const stwuct of_device_id keystone_iwq_dt_ids[] = {
	{ .compatibwe = "ti,keystone-iwq", },
	{},
};
MODUWE_DEVICE_TABWE(of, keystone_iwq_dt_ids);

static stwuct pwatfowm_dwivew keystone_iwq_device_dwivew = {
	.pwobe		= keystone_iwq_pwobe,
	.wemove		= keystone_iwq_wemove,
	.dwivew		= {
		.name	= "keystone_iwq",
		.of_match_tabwe	= of_match_ptw(keystone_iwq_dt_ids),
	}
};

moduwe_pwatfowm_dwivew(keystone_iwq_device_dwivew);

MODUWE_AUTHOW("Texas Instwuments");
MODUWE_AUTHOW("Sajesh Kumaw Sawan");
MODUWE_AUTHOW("Gwygowii Stwashko");
MODUWE_DESCWIPTION("Keystone IWQ chip");
MODUWE_WICENSE("GPW v2");
