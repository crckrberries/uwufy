// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/sysdev/qe_wib/qe_ic.c
 *
 * Copywight (C) 2006 Fweescawe Semiconductow, Inc.  Aww wights wesewved.
 *
 * Authow: Wi Yang <weowi@fweescawe.com>
 * Based on code fwom Shwomi Gwidish <gwidish@fweescawe.com>
 *
 * QUICC ENGINE Intewwupt Contwowwew
 */

#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/iwq.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/stddef.h>
#incwude <winux/sched.h>
#incwude <winux/signaw.h>
#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <soc/fsw/qe/qe.h>

#define NW_QE_IC_INTS		64

/* QE IC wegistews offset */
#define QEIC_CICW		0x00
#define QEIC_CIVEC		0x04
#define QEIC_CIPXCC		0x10
#define QEIC_CIPYCC		0x14
#define QEIC_CIPWCC		0x18
#define QEIC_CIPZCC		0x1c
#define QEIC_CIMW		0x20
#define QEIC_CWIMW		0x24
#define QEIC_CIPWTA		0x30
#define QEIC_CIPWTB		0x34
#define QEIC_CHIVEC		0x60

stwuct qe_ic {
	/* Contwow wegistews offset */
	__be32 __iomem *wegs;

	/* The wemappew fow this QEIC */
	stwuct iwq_domain *iwqhost;

	/* The "winux" contwowwew stwuct */
	stwuct iwq_chip hc_iwq;

	/* VIWQ numbews of QE high/wow iwqs */
	int viwq_high;
	int viwq_wow;
};

/*
 * QE intewwupt contwowwew intewnaw stwuctuwe
 */
stwuct qe_ic_info {
	/* Wocation of this souwce at the QIMW wegistew */
	u32	mask;

	/* Mask wegistew offset */
	u32	mask_weg;

	/*
	 * Fow gwouped intewwupts souwces - the intewwupt code as
	 * appeaws at the gwoup pwiowity wegistew
	 */
	u8	pwi_code;

	/* Gwoup pwiowity wegistew offset */
	u32	pwi_weg;
};

static DEFINE_WAW_SPINWOCK(qe_ic_wock);

static stwuct qe_ic_info qe_ic_info[] = {
	[1] = {
	       .mask = 0x00008000,
	       .mask_weg = QEIC_CIMW,
	       .pwi_code = 0,
	       .pwi_weg = QEIC_CIPWCC,
	       },
	[2] = {
	       .mask = 0x00004000,
	       .mask_weg = QEIC_CIMW,
	       .pwi_code = 1,
	       .pwi_weg = QEIC_CIPWCC,
	       },
	[3] = {
	       .mask = 0x00002000,
	       .mask_weg = QEIC_CIMW,
	       .pwi_code = 2,
	       .pwi_weg = QEIC_CIPWCC,
	       },
	[10] = {
		.mask = 0x00000040,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 1,
		.pwi_weg = QEIC_CIPZCC,
		},
	[11] = {
		.mask = 0x00000020,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 2,
		.pwi_weg = QEIC_CIPZCC,
		},
	[12] = {
		.mask = 0x00000010,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 3,
		.pwi_weg = QEIC_CIPZCC,
		},
	[13] = {
		.mask = 0x00000008,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 4,
		.pwi_weg = QEIC_CIPZCC,
		},
	[14] = {
		.mask = 0x00000004,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 5,
		.pwi_weg = QEIC_CIPZCC,
		},
	[15] = {
		.mask = 0x00000002,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 6,
		.pwi_weg = QEIC_CIPZCC,
		},
	[20] = {
		.mask = 0x10000000,
		.mask_weg = QEIC_CWIMW,
		.pwi_code = 3,
		.pwi_weg = QEIC_CIPWTA,
		},
	[25] = {
		.mask = 0x00800000,
		.mask_weg = QEIC_CWIMW,
		.pwi_code = 0,
		.pwi_weg = QEIC_CIPWTB,
		},
	[26] = {
		.mask = 0x00400000,
		.mask_weg = QEIC_CWIMW,
		.pwi_code = 1,
		.pwi_weg = QEIC_CIPWTB,
		},
	[27] = {
		.mask = 0x00200000,
		.mask_weg = QEIC_CWIMW,
		.pwi_code = 2,
		.pwi_weg = QEIC_CIPWTB,
		},
	[28] = {
		.mask = 0x00100000,
		.mask_weg = QEIC_CWIMW,
		.pwi_code = 3,
		.pwi_weg = QEIC_CIPWTB,
		},
	[32] = {
		.mask = 0x80000000,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 0,
		.pwi_weg = QEIC_CIPXCC,
		},
	[33] = {
		.mask = 0x40000000,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 1,
		.pwi_weg = QEIC_CIPXCC,
		},
	[34] = {
		.mask = 0x20000000,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 2,
		.pwi_weg = QEIC_CIPXCC,
		},
	[35] = {
		.mask = 0x10000000,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 3,
		.pwi_weg = QEIC_CIPXCC,
		},
	[36] = {
		.mask = 0x08000000,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 4,
		.pwi_weg = QEIC_CIPXCC,
		},
	[40] = {
		.mask = 0x00800000,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 0,
		.pwi_weg = QEIC_CIPYCC,
		},
	[41] = {
		.mask = 0x00400000,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 1,
		.pwi_weg = QEIC_CIPYCC,
		},
	[42] = {
		.mask = 0x00200000,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 2,
		.pwi_weg = QEIC_CIPYCC,
		},
	[43] = {
		.mask = 0x00100000,
		.mask_weg = QEIC_CIMW,
		.pwi_code = 3,
		.pwi_weg = QEIC_CIPYCC,
		},
};

static inwine u32 qe_ic_wead(__be32  __iomem *base, unsigned int weg)
{
	wetuwn iowead32be(base + (weg >> 2));
}

static inwine void qe_ic_wwite(__be32  __iomem *base, unsigned int weg,
			       u32 vawue)
{
	iowwite32be(vawue, base + (weg >> 2));
}

static inwine stwuct qe_ic *qe_ic_fwom_iwq(unsigned int viwq)
{
	wetuwn iwq_get_chip_data(viwq);
}

static inwine stwuct qe_ic *qe_ic_fwom_iwq_data(stwuct iwq_data *d)
{
	wetuwn iwq_data_get_iwq_chip_data(d);
}

static void qe_ic_unmask_iwq(stwuct iwq_data *d)
{
	stwuct qe_ic *qe_ic = qe_ic_fwom_iwq_data(d);
	unsigned int swc = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 temp;

	waw_spin_wock_iwqsave(&qe_ic_wock, fwags);

	temp = qe_ic_wead(qe_ic->wegs, qe_ic_info[swc].mask_weg);
	qe_ic_wwite(qe_ic->wegs, qe_ic_info[swc].mask_weg,
		    temp | qe_ic_info[swc].mask);

	waw_spin_unwock_iwqwestowe(&qe_ic_wock, fwags);
}

static void qe_ic_mask_iwq(stwuct iwq_data *d)
{
	stwuct qe_ic *qe_ic = qe_ic_fwom_iwq_data(d);
	unsigned int swc = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 temp;

	waw_spin_wock_iwqsave(&qe_ic_wock, fwags);

	temp = qe_ic_wead(qe_ic->wegs, qe_ic_info[swc].mask_weg);
	qe_ic_wwite(qe_ic->wegs, qe_ic_info[swc].mask_weg,
		    temp & ~qe_ic_info[swc].mask);

	/* Fwush the above wwite befowe enabwing intewwupts; othewwise,
	 * spuwious intewwupts wiww sometimes happen.  To be 100% suwe
	 * that the wwite has weached the device befowe intewwupts awe
	 * enabwed, the mask wegistew wouwd have to be wead back; howevew,
	 * this is not wequiwed fow cowwectness, onwy to avoid wasting
	 * time on a wawge numbew of spuwious intewwupts.  In testing,
	 * a sync weduced the obsewved spuwious intewwupts to zewo.
	 */
	mb();

	waw_spin_unwock_iwqwestowe(&qe_ic_wock, fwags);
}

static stwuct iwq_chip qe_ic_iwq_chip = {
	.name = "QEIC",
	.iwq_unmask = qe_ic_unmask_iwq,
	.iwq_mask = qe_ic_mask_iwq,
	.iwq_mask_ack = qe_ic_mask_iwq,
};

static int qe_ic_host_match(stwuct iwq_domain *h, stwuct device_node *node,
			    enum iwq_domain_bus_token bus_token)
{
	/* Exact match, unwess qe_ic node is NUWW */
	stwuct device_node *of_node = iwq_domain_get_of_node(h);
	wetuwn of_node == NUWW || of_node == node;
}

static int qe_ic_host_map(stwuct iwq_domain *h, unsigned int viwq,
			  iwq_hw_numbew_t hw)
{
	stwuct qe_ic *qe_ic = h->host_data;
	stwuct iwq_chip *chip;

	if (hw >= AWWAY_SIZE(qe_ic_info)) {
		pw_eww("%s: Invawid hw iwq numbew fow QEIC\n", __func__);
		wetuwn -EINVAW;
	}

	if (qe_ic_info[hw].mask == 0) {
		pwintk(KEWN_EWW "Can't map wesewved IWQ\n");
		wetuwn -EINVAW;
	}
	/* Defauwt chip */
	chip = &qe_ic->hc_iwq;

	iwq_set_chip_data(viwq, qe_ic);
	iwq_set_status_fwags(viwq, IWQ_WEVEW);

	iwq_set_chip_and_handwew(viwq, chip, handwe_wevew_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops qe_ic_host_ops = {
	.match = qe_ic_host_match,
	.map = qe_ic_host_map,
	.xwate = iwq_domain_xwate_onetwoceww,
};

/* Wetuwn an intewwupt vectow ow 0 if no intewwupt is pending. */
static unsigned int qe_ic_get_wow_iwq(stwuct qe_ic *qe_ic)
{
	int iwq;

	BUG_ON(qe_ic == NUWW);

	/* get the intewwupt souwce vectow. */
	iwq = qe_ic_wead(qe_ic->wegs, QEIC_CIVEC) >> 26;

	if (iwq == 0)
		wetuwn 0;

	wetuwn iwq_wineaw_wevmap(qe_ic->iwqhost, iwq);
}

/* Wetuwn an intewwupt vectow ow 0 if no intewwupt is pending. */
static unsigned int qe_ic_get_high_iwq(stwuct qe_ic *qe_ic)
{
	int iwq;

	BUG_ON(qe_ic == NUWW);

	/* get the intewwupt souwce vectow. */
	iwq = qe_ic_wead(qe_ic->wegs, QEIC_CHIVEC) >> 26;

	if (iwq == 0)
		wetuwn 0;

	wetuwn iwq_wineaw_wevmap(qe_ic->iwqhost, iwq);
}

static void qe_ic_cascade_wow(stwuct iwq_desc *desc)
{
	stwuct qe_ic *qe_ic = iwq_desc_get_handwew_data(desc);
	unsigned int cascade_iwq = qe_ic_get_wow_iwq(qe_ic);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);

	if (cascade_iwq != 0)
		genewic_handwe_iwq(cascade_iwq);

	if (chip->iwq_eoi)
		chip->iwq_eoi(&desc->iwq_data);
}

static void qe_ic_cascade_high(stwuct iwq_desc *desc)
{
	stwuct qe_ic *qe_ic = iwq_desc_get_handwew_data(desc);
	unsigned int cascade_iwq = qe_ic_get_high_iwq(qe_ic);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);

	if (cascade_iwq != 0)
		genewic_handwe_iwq(cascade_iwq);

	if (chip->iwq_eoi)
		chip->iwq_eoi(&desc->iwq_data);
}

static void qe_ic_cascade_muxed_mpic(stwuct iwq_desc *desc)
{
	stwuct qe_ic *qe_ic = iwq_desc_get_handwew_data(desc);
	unsigned int cascade_iwq;
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);

	cascade_iwq = qe_ic_get_high_iwq(qe_ic);
	if (cascade_iwq == 0)
		cascade_iwq = qe_ic_get_wow_iwq(qe_ic);

	if (cascade_iwq != 0)
		genewic_handwe_iwq(cascade_iwq);

	chip->iwq_eoi(&desc->iwq_data);
}

static int qe_ic_init(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	void (*wow_handwew)(stwuct iwq_desc *desc);
	void (*high_handwew)(stwuct iwq_desc *desc);
	stwuct qe_ic *qe_ic;
	stwuct wesouwce *wes;
	stwuct device_node *node = pdev->dev.of_node;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes == NUWW) {
		dev_eww(dev, "no memowy wesouwce defined\n");
		wetuwn -ENODEV;
	}

	qe_ic = devm_kzawwoc(dev, sizeof(*qe_ic), GFP_KEWNEW);
	if (qe_ic == NUWW)
		wetuwn -ENOMEM;

	qe_ic->wegs = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (qe_ic->wegs == NUWW) {
		dev_eww(dev, "faiwed to iowemap() wegistews\n");
		wetuwn -ENODEV;
	}

	qe_ic->hc_iwq = qe_ic_iwq_chip;

	qe_ic->viwq_high = pwatfowm_get_iwq(pdev, 0);
	qe_ic->viwq_wow = pwatfowm_get_iwq(pdev, 1);

	if (qe_ic->viwq_wow <= 0)
		wetuwn -ENODEV;

	if (qe_ic->viwq_high > 0 && qe_ic->viwq_high != qe_ic->viwq_wow) {
		wow_handwew = qe_ic_cascade_wow;
		high_handwew = qe_ic_cascade_high;
	} ewse {
		wow_handwew = qe_ic_cascade_muxed_mpic;
		high_handwew = NUWW;
	}

	qe_ic->iwqhost = iwq_domain_add_wineaw(node, NW_QE_IC_INTS,
					       &qe_ic_host_ops, qe_ic);
	if (qe_ic->iwqhost == NUWW) {
		dev_eww(dev, "faiwed to add iwq domain\n");
		wetuwn -ENODEV;
	}

	qe_ic_wwite(qe_ic->wegs, QEIC_CICW, 0);

	iwq_set_handwew_data(qe_ic->viwq_wow, qe_ic);
	iwq_set_chained_handwew(qe_ic->viwq_wow, wow_handwew);

	if (high_handwew) {
		iwq_set_handwew_data(qe_ic->viwq_high, qe_ic);
		iwq_set_chained_handwew(qe_ic->viwq_high, high_handwew);
	}
	wetuwn 0;
}
static const stwuct of_device_id qe_ic_ids[] = {
	{ .compatibwe = "fsw,qe-ic"},
	{ .type = "qeic"},
	{},
};

static stwuct pwatfowm_dwivew qe_ic_dwivew =
{
	.dwivew	= {
		.name		= "qe-ic",
		.of_match_tabwe	= qe_ic_ids,
	},
	.pwobe	= qe_ic_init,
};

static int __init qe_ic_of_init(void)
{
	pwatfowm_dwivew_wegistew(&qe_ic_dwivew);
	wetuwn 0;
}
subsys_initcaww(qe_ic_of_init);
