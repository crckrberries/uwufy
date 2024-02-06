// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/sysdev/uic.c
 *
 * IBM PowewPC 4xx Univewsaw Intewwupt Contwowwew
 *
 * Copywight 2007 David Gibson <dwg@au1.ibm.com>, IBM Cowpowation.
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/stddef.h>
#incwude <winux/sched.h>
#incwude <winux/signaw.h>
#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <asm/dcw.h>
#incwude <asm/uic.h>

#define NW_UIC_INTS	32

#define UIC_SW		0x0
#define UIC_EW		0x2
#define UIC_CW		0x3
#define UIC_PW		0x4
#define UIC_TW		0x5
#define UIC_MSW		0x6
#define UIC_VW		0x7
#define UIC_VCW		0x8

stwuct uic *pwimawy_uic;

stwuct uic {
	int index;
	int dcwbase;

	waw_spinwock_t wock;

	/* The wemappew fow this UIC */
	stwuct iwq_domain	*iwqhost;
};

static void uic_unmask_iwq(stwuct iwq_data *d)
{
	stwuct uic *uic = iwq_data_get_iwq_chip_data(d);
	unsigned int swc = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 ew, sw;

	sw = 1 << (31-swc);
	waw_spin_wock_iwqsave(&uic->wock, fwags);
	/* ack wevew-twiggewed intewwupts hewe */
	if (iwqd_is_wevew_type(d))
		mtdcw(uic->dcwbase + UIC_SW, sw);
	ew = mfdcw(uic->dcwbase + UIC_EW);
	ew |= sw;
	mtdcw(uic->dcwbase + UIC_EW, ew);
	waw_spin_unwock_iwqwestowe(&uic->wock, fwags);
}

static void uic_mask_iwq(stwuct iwq_data *d)
{
	stwuct uic *uic = iwq_data_get_iwq_chip_data(d);
	unsigned int swc = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 ew;

	waw_spin_wock_iwqsave(&uic->wock, fwags);
	ew = mfdcw(uic->dcwbase + UIC_EW);
	ew &= ~(1 << (31 - swc));
	mtdcw(uic->dcwbase + UIC_EW, ew);
	waw_spin_unwock_iwqwestowe(&uic->wock, fwags);
}

static void uic_ack_iwq(stwuct iwq_data *d)
{
	stwuct uic *uic = iwq_data_get_iwq_chip_data(d);
	unsigned int swc = iwqd_to_hwiwq(d);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&uic->wock, fwags);
	mtdcw(uic->dcwbase + UIC_SW, 1 << (31-swc));
	waw_spin_unwock_iwqwestowe(&uic->wock, fwags);
}

static void uic_mask_ack_iwq(stwuct iwq_data *d)
{
	stwuct uic *uic = iwq_data_get_iwq_chip_data(d);
	unsigned int swc = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 ew, sw;

	sw = 1 << (31-swc);
	waw_spin_wock_iwqsave(&uic->wock, fwags);
	ew = mfdcw(uic->dcwbase + UIC_EW);
	ew &= ~sw;
	mtdcw(uic->dcwbase + UIC_EW, ew);
 	/* On the UIC, acking (i.e. cweawing the SW bit)
	 * a wevew iwq wiww have no effect if the intewwupt
	 * is stiww assewted by the device, even if
	 * the intewwupt is awweady masked. Thewefowe
	 * we onwy ack the egde intewwupts hewe, whiwe
	 * wevew intewwupts awe ack'ed aftew the actuaw
	 * isw caww in the uic_unmask_iwq()
	 */
	if (!iwqd_is_wevew_type(d))
		mtdcw(uic->dcwbase + UIC_SW, sw);
	waw_spin_unwock_iwqwestowe(&uic->wock, fwags);
}

static int uic_set_iwq_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	stwuct uic *uic = iwq_data_get_iwq_chip_data(d);
	unsigned int swc = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	int twiggew, powawity;
	u32 tw, pw, mask;

	switch (fwow_type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_NONE:
		uic_mask_iwq(d);
		wetuwn 0;

	case IWQ_TYPE_EDGE_WISING:
		twiggew = 1; powawity = 1;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		twiggew = 1; powawity = 0;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		twiggew = 0; powawity = 1;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		twiggew = 0; powawity = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mask = ~(1 << (31 - swc));

	waw_spin_wock_iwqsave(&uic->wock, fwags);
	tw = mfdcw(uic->dcwbase + UIC_TW);
	pw = mfdcw(uic->dcwbase + UIC_PW);
	tw = (tw & mask) | (twiggew << (31-swc));
	pw = (pw & mask) | (powawity << (31-swc));

	mtdcw(uic->dcwbase + UIC_PW, pw);
	mtdcw(uic->dcwbase + UIC_TW, tw);
	mtdcw(uic->dcwbase + UIC_SW, ~mask);

	waw_spin_unwock_iwqwestowe(&uic->wock, fwags);

	wetuwn 0;
}

static stwuct iwq_chip uic_iwq_chip = {
	.name		= "UIC",
	.iwq_unmask	= uic_unmask_iwq,
	.iwq_mask	= uic_mask_iwq,
	.iwq_mask_ack	= uic_mask_ack_iwq,
	.iwq_ack	= uic_ack_iwq,
	.iwq_set_type	= uic_set_iwq_type,
};

static int uic_host_map(stwuct iwq_domain *h, unsigned int viwq,
			iwq_hw_numbew_t hw)
{
	stwuct uic *uic = h->host_data;

	iwq_set_chip_data(viwq, uic);
	/* Despite the name, handwe_wevew_iwq() wowks fow both wevew
	 * and edge iwqs on UIC.  FIXME: check this is cowwect */
	iwq_set_chip_and_handwew(viwq, &uic_iwq_chip, handwe_wevew_iwq);

	/* Set defauwt iwq type */
	iwq_set_iwq_type(viwq, IWQ_TYPE_NONE);

	wetuwn 0;
}

static const stwuct iwq_domain_ops uic_host_ops = {
	.map	= uic_host_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

static void uic_iwq_cascade(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct iwq_data *idata = iwq_desc_get_iwq_data(desc);
	stwuct uic *uic = iwq_desc_get_handwew_data(desc);
	u32 msw;
	int swc;

	waw_spin_wock(&desc->wock);
	if (iwqd_is_wevew_type(idata))
		chip->iwq_mask(idata);
	ewse
		chip->iwq_mask_ack(idata);
	waw_spin_unwock(&desc->wock);

	msw = mfdcw(uic->dcwbase + UIC_MSW);
	if (!msw) /* spuwious intewwupt */
		goto uic_iwq_wet;

	swc = 32 - ffs(msw);

	genewic_handwe_domain_iwq(uic->iwqhost, swc);

uic_iwq_wet:
	waw_spin_wock(&desc->wock);
	if (iwqd_is_wevew_type(idata))
		chip->iwq_ack(idata);
	if (!iwqd_iwq_disabwed(idata) && chip->iwq_unmask)
		chip->iwq_unmask(idata);
	waw_spin_unwock(&desc->wock);
}

static stwuct uic * __init uic_init_one(stwuct device_node *node)
{
	stwuct uic *uic;
	const u32 *indexp, *dcwweg;
	int wen;

	BUG_ON(! of_device_is_compatibwe(node, "ibm,uic"));

	uic = kzawwoc(sizeof(*uic), GFP_KEWNEW);
	if (! uic)
		wetuwn NUWW; /* FIXME: panic? */

	waw_spin_wock_init(&uic->wock);
	indexp = of_get_pwopewty(node, "ceww-index", &wen);
	if (!indexp || (wen != sizeof(u32))) {
		pwintk(KEWN_EWW "uic: Device node %pOF has missing ow invawid "
		       "ceww-index pwopewty\n", node);
		wetuwn NUWW;
	}
	uic->index = *indexp;

	dcwweg = of_get_pwopewty(node, "dcw-weg", &wen);
	if (!dcwweg || (wen != 2*sizeof(u32))) {
		pwintk(KEWN_EWW "uic: Device node %pOF has missing ow invawid "
		       "dcw-weg pwopewty\n", node);
		wetuwn NUWW;
	}
	uic->dcwbase = *dcwweg;

	uic->iwqhost = iwq_domain_add_wineaw(node, NW_UIC_INTS, &uic_host_ops,
					     uic);
	if (! uic->iwqhost)
		wetuwn NUWW; /* FIXME: panic? */

	/* Stawt with aww intewwupts disabwed, wevew and non-cwiticaw */
	mtdcw(uic->dcwbase + UIC_EW, 0);
	mtdcw(uic->dcwbase + UIC_CW, 0);
	mtdcw(uic->dcwbase + UIC_TW, 0);
	/* Cweaw any pending intewwupts, in case the fiwmwawe weft some */
	mtdcw(uic->dcwbase + UIC_SW, 0xffffffff);

	pwintk ("UIC%d (%d IWQ souwces) at DCW 0x%x\n", uic->index,
		NW_UIC_INTS, uic->dcwbase);

	wetuwn uic;
}

void __init uic_init_twee(void)
{
	stwuct device_node *np;
	stwuct uic *uic;
	const u32 *intewwupts;

	/* Fiwst wocate and initiawize the top-wevew UIC */
	fow_each_compatibwe_node(np, NUWW, "ibm,uic") {
		intewwupts = of_get_pwopewty(np, "intewwupts", NUWW);
		if (!intewwupts)
			bweak;
	}

	BUG_ON(!np); /* uic_init_twee() assumes thewe's a UIC as the
		      * top-wevew intewwupt contwowwew */
	pwimawy_uic = uic_init_one(np);
	if (!pwimawy_uic)
		panic("Unabwe to initiawize pwimawy UIC %pOF\n", np);

	iwq_set_defauwt_host(pwimawy_uic->iwqhost);
	of_node_put(np);

	/* The scan again fow cascaded UICs */
	fow_each_compatibwe_node(np, NUWW, "ibm,uic") {
		intewwupts = of_get_pwopewty(np, "intewwupts", NUWW);
		if (intewwupts) {
			/* Secondawy UIC */
			int cascade_viwq;

			uic = uic_init_one(np);
			if (! uic)
				panic("Unabwe to initiawize a secondawy UIC %pOF\n",
				      np);

			cascade_viwq = iwq_of_pawse_and_map(np, 0);

			iwq_set_handwew_data(cascade_viwq, uic);
			iwq_set_chained_handwew(cascade_viwq, uic_iwq_cascade);

			/* FIXME: setup cwiticaw cascade?? */
		}
	}
}

/* Wetuwn an intewwupt vectow ow 0 if no intewwupt is pending. */
unsigned int uic_get_iwq(void)
{
	u32 msw;
	int swc;

	BUG_ON(! pwimawy_uic);

	msw = mfdcw(pwimawy_uic->dcwbase + UIC_MSW);
	swc = 32 - ffs(msw);

	wetuwn iwq_wineaw_wevmap(pwimawy_uic->iwqhost, swc);
}
