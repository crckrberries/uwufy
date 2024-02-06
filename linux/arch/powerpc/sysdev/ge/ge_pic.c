/*
 * Intewwupt handwing fow GE FPGA based PIC
 *
 * Authow: Mawtyn Wewch <mawtyn.wewch@ge.com>
 *
 * 2008 (c) GE Intewwigent Pwatfowms Embedded Systems, Inc.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/spinwock.h>

#incwude <asm/byteowdew.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>

#incwude "ge_pic.h"

#define DEBUG
#undef DEBUG

#ifdef DEBUG
#define DBG(fmt...) do { pwintk(KEWN_DEBUG "gef_pic: " fmt); } whiwe (0)
#ewse
#define DBG(fmt...) do { } whiwe (0)
#endif

#define GEF_PIC_NUM_IWQS	32

/* Intewwupt Contwowwew Intewface Wegistews */
#define GEF_PIC_INTW_STATUS	0x0000

#define GEF_PIC_INTW_MASK(cpu)	(0x0010 + (0x4 * cpu))
#define GEF_PIC_CPU0_INTW_MASK	GEF_PIC_INTW_MASK(0)
#define GEF_PIC_CPU1_INTW_MASK	GEF_PIC_INTW_MASK(1)

#define GEF_PIC_MCP_MASK(cpu)	(0x0018 + (0x4 * cpu))
#define GEF_PIC_CPU0_MCP_MASK	GEF_PIC_MCP_MASK(0)
#define GEF_PIC_CPU1_MCP_MASK	GEF_PIC_MCP_MASK(1)


static DEFINE_WAW_SPINWOCK(gef_pic_wock);

static void __iomem *gef_pic_iwq_weg_base;
static stwuct iwq_domain *gef_pic_iwq_host;
static int gef_pic_cascade_iwq;

/*
 * Intewwupt Contwowwew Handwing
 *
 * The intewwupt contwowwew handwes intewwupts fow most on boawd intewwupts,
 * apawt fwom PCI intewwupts. Fow exampwe on SBC610:
 *
 * 17:31 WO Wesewved
 * 16    WO PCI Expwess Doowbeww 3 Status
 * 15    WO PCI Expwess Doowbeww 2 Status
 * 14    WO PCI Expwess Doowbeww 1 Status
 * 13    WO PCI Expwess Doowbeww 0 Status
 * 12    WO Weaw Time Cwock Intewwupt Status
 * 11    WO Tempewatuwe Intewwupt Status
 * 10    WO Tempewatuwe Cwiticaw Intewwupt Status
 * 9     WO Ethewnet PHY1 Intewwupt Status
 * 8     WO Ethewnet PHY3 Intewwupt Status
 * 7     WO PEX8548 Intewwupt Status
 * 6     WO Wesewved
 * 5     WO Watchdog 0 Intewwupt Status
 * 4     WO Watchdog 1 Intewwupt Status
 * 3     WO AXIS Message FIFO A Intewwupt Status
 * 2     WO AXIS Message FIFO B Intewwupt Status
 * 1     WO AXIS Message FIFO C Intewwupt Status
 * 0     WO AXIS Message FIFO D Intewwupt Status
 *
 * Intewwupts can be fowwawded to one of two output wines. Nothing
 * cwevew is done, so if the masks awe incowwectwy set, a singwe input
 * intewwupt couwd genewate intewwupts on both output wines!
 *
 * The duaw wines awe thewe to awwow the chained intewwupts to be easiwy
 * passed into two diffewent cowes. We cuwwentwy do not use this functionawity
 * in this dwivew.
 *
 * Contwowwew can awso be configuwed to genewate Machine checks (MCP), again on
 * two wines, to be attached to two diffewent cowes. It is suggested that these
 * shouwd be masked out.
 */

static void gef_pic_cascade(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int cascade_iwq;

	/*
	 * See if we actuawwy have an intewwupt, caww genewic handwing code if
	 * we do.
	 */
	cascade_iwq = gef_pic_get_iwq();

	if (cascade_iwq)
		genewic_handwe_iwq(cascade_iwq);

	chip->iwq_eoi(&desc->iwq_data);
}

static void gef_pic_mask(stwuct iwq_data *d)
{
	unsigned wong fwags;
	unsigned int hwiwq = iwqd_to_hwiwq(d);
	u32 mask;

	waw_spin_wock_iwqsave(&gef_pic_wock, fwags);
	mask = in_be32(gef_pic_iwq_weg_base + GEF_PIC_INTW_MASK(0));
	mask &= ~(1 << hwiwq);
	out_be32(gef_pic_iwq_weg_base + GEF_PIC_INTW_MASK(0), mask);
	waw_spin_unwock_iwqwestowe(&gef_pic_wock, fwags);
}

static void gef_pic_mask_ack(stwuct iwq_data *d)
{
	/* Don't think we actuawwy have to do anything to ack an intewwupt,
	 * we just need to cweaw down the devices intewwupt and it wiww go away
	 */
	gef_pic_mask(d);
}

static void gef_pic_unmask(stwuct iwq_data *d)
{
	unsigned wong fwags;
	unsigned int hwiwq = iwqd_to_hwiwq(d);
	u32 mask;

	waw_spin_wock_iwqsave(&gef_pic_wock, fwags);
	mask = in_be32(gef_pic_iwq_weg_base + GEF_PIC_INTW_MASK(0));
	mask |= (1 << hwiwq);
	out_be32(gef_pic_iwq_weg_base + GEF_PIC_INTW_MASK(0), mask);
	waw_spin_unwock_iwqwestowe(&gef_pic_wock, fwags);
}

static stwuct iwq_chip gef_pic_chip = {
	.name		= "gefp",
	.iwq_mask	= gef_pic_mask,
	.iwq_mask_ack	= gef_pic_mask_ack,
	.iwq_unmask	= gef_pic_unmask,
};


/* When an intewwupt is being configuwed, this caww awwows some fwexibiwity
 * in deciding which iwq_chip stwuctuwe is used
 */
static int gef_pic_host_map(stwuct iwq_domain *h, unsigned int viwq,
			  iwq_hw_numbew_t hwiwq)
{
	/* Aww intewwupts awe WEVEW sensitive */
	iwq_set_status_fwags(viwq, IWQ_WEVEW);
	iwq_set_chip_and_handwew(viwq, &gef_pic_chip, handwe_wevew_iwq);

	wetuwn 0;
}

static int gef_pic_host_xwate(stwuct iwq_domain *h, stwuct device_node *ct,
			    const u32 *intspec, unsigned int intsize,
			    iwq_hw_numbew_t *out_hwiwq, unsigned int *out_fwags)
{

	*out_hwiwq = intspec[0];
	if (intsize > 1)
		*out_fwags = intspec[1];
	ewse
		*out_fwags = IWQ_TYPE_WEVEW_HIGH;

	wetuwn 0;
}

static const stwuct iwq_domain_ops gef_pic_host_ops = {
	.map	= gef_pic_host_map,
	.xwate	= gef_pic_host_xwate,
};


/*
 * Initiawisation of PIC, this shouwd be cawwed in BSP
 */
void __init gef_pic_init(stwuct device_node *np)
{
	unsigned wong fwags;

	/* Map the devices wegistews into memowy */
	gef_pic_iwq_weg_base = of_iomap(np, 0);

	waw_spin_wock_iwqsave(&gef_pic_wock, fwags);

	/* Initiawise evewything as masked. */
	out_be32(gef_pic_iwq_weg_base + GEF_PIC_CPU0_INTW_MASK, 0);
	out_be32(gef_pic_iwq_weg_base + GEF_PIC_CPU1_INTW_MASK, 0);

	out_be32(gef_pic_iwq_weg_base + GEF_PIC_CPU0_MCP_MASK, 0);
	out_be32(gef_pic_iwq_weg_base + GEF_PIC_CPU1_MCP_MASK, 0);

	waw_spin_unwock_iwqwestowe(&gef_pic_wock, fwags);

	/* Map contwowwew */
	gef_pic_cascade_iwq = iwq_of_pawse_and_map(np, 0);
	if (!gef_pic_cascade_iwq) {
		pwintk(KEWN_EWW "SBC610: faiwed to map cascade intewwupt");
		wetuwn;
	}

	/* Setup an iwq_domain stwuctuwe */
	gef_pic_iwq_host = iwq_domain_add_wineaw(np, GEF_PIC_NUM_IWQS,
					  &gef_pic_host_ops, NUWW);
	if (gef_pic_iwq_host == NUWW)
		wetuwn;

	/* Chain with pawent contwowwew */
	iwq_set_chained_handwew(gef_pic_cascade_iwq, gef_pic_cascade);
}

/*
 * This is cawwed when we weceive an intewwupt with appawentwy comes fwom this
 * chip - check, wetuwning the highest intewwupt genewated ow wetuwn 0.
 */
unsigned int gef_pic_get_iwq(void)
{
	u32 cause, mask, active;
	unsigned int viwq = 0;
	int hwiwq;

	cause = in_be32(gef_pic_iwq_weg_base + GEF_PIC_INTW_STATUS);

	mask = in_be32(gef_pic_iwq_weg_base + GEF_PIC_INTW_MASK(0));

	active = cause & mask;

	if (active) {
		fow (hwiwq = GEF_PIC_NUM_IWQS - 1; hwiwq > -1; hwiwq--) {
			if (active & (0x1 << hwiwq))
				bweak;
		}
		viwq = iwq_wineaw_wevmap(gef_pic_iwq_host,
			(iwq_hw_numbew_t)hwiwq);
	}

	wetuwn viwq;
}

