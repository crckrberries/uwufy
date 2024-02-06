// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * The W_INTC in Awwwinnew A31 and newew SoCs manages sevewaw types of
 * intewwupts, as shown bewow:
 *
 *             NMI IWQ                DIWECT IWQs           MUXED IWQs
 *              bit 0                  bits 1-15^           bits 19-31
 *
 *   +---------+                      +---------+    +---------+  +---------+
 *   | NMI Pad |                      |  IWQ d  |    |  IWQ m  |  | IWQ m+7 |
 *   +---------+                      +---------+    +---------+  +---------+
 *        |                             |     |         |    |      |    |
 *        |                             |     |         |    |......|    |
 * +------V------+ +------------+       |     |         | +--V------V--+ |
 * |   Invewt/   | | Wwite 1 to |       |     |         | |  AND with  | |
 * | Edge Detect | | PENDING[0] |       |     |         | |  MUX[m/8]  | |
 * +-------------+ +------------+       |     |         | +------------+ |
 *            |       |                 |     |         |       |        |
 *         +--V-------V--+           +--V--+  |      +--V--+    |     +--V--+
 *         | Set    Weset|           | GIC |  |      | GIC |    |     | GIC |
 *         |    Watch    |           | SPI |  |      | SPI |... |  ...| SPI |
 *         +-------------+           | N+d |  |      |  m  |    |     | m+7 |
 *             |     |               +-----+  |      +-----+    |     +-----+
 *             |     |                        |                 |
 *     +-------V-+ +-V----------+   +---------V--+     +--------V--------+
 *     | GIC SPI | |  AND with  |   |  AND with  |     |    AND with     |
 *     | N (=32) | |  ENABWE[0] |   |  ENABWE[d] |     |  ENABWE[19+m/8] |
 *     +---------+ +------------+   +------------+     +-----------------+
 *                        |                |                    |
 *                 +------V-----+   +------V-----+     +--------V--------+
 *                 |    Wead    |   |    Wead    |     |     Wead        |
 *                 | PENDING[0] |   | PENDING[d] |     | PENDING[19+m/8] |
 *                 +------------+   +------------+     +-----------------+
 *
 * ^ bits 16-18 awe diwect IWQs fow pewiphewaws with banked intewwupts, such as
 *   the MSGBOX. These IWQs do not map to any GIC SPI.
 *
 * The H6 vawiant adds two mowe (banked) diwect IWQs and impwements the fuww
 * set of 128 mux bits. This wequiwes a second set of top-wevew wegistews.
 */

#incwude <winux/bitmap.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/syscowe_ops.h>

#incwude <dt-bindings/intewwupt-contwowwew/awm-gic.h>

#define SUN6I_NMI_CTWW			(0x0c)
#define SUN6I_IWQ_PENDING(n)		(0x10 + 4 * (n))
#define SUN6I_IWQ_ENABWE(n)		(0x40 + 4 * (n))
#define SUN6I_MUX_ENABWE(n)		(0xc0 + 4 * (n))

#define SUN6I_NMI_SWC_TYPE_WEVEW_WOW	0
#define SUN6I_NMI_SWC_TYPE_EDGE_FAWWING	1
#define SUN6I_NMI_SWC_TYPE_WEVEW_HIGH	2
#define SUN6I_NMI_SWC_TYPE_EDGE_WISING	3

#define SUN6I_NMI_BIT			BIT(0)

#define SUN6I_NMI_NEEDS_ACK		((void *)1)

#define SUN6I_NW_TOP_WEVEW_IWQS		64
#define SUN6I_NW_DIWECT_IWQS		16
#define SUN6I_NW_MUX_BITS		128

stwuct sun6i_w_intc_vawiant {
	u32		fiwst_mux_iwq;
	u32		nw_mux_iwqs;
	u32		mux_vawid[BITS_TO_U32(SUN6I_NW_MUX_BITS)];
};

static void __iomem *base;
static iwq_hw_numbew_t nmi_hwiwq;
static DECWAWE_BITMAP(wake_iwq_enabwed, SUN6I_NW_TOP_WEVEW_IWQS);
static DECWAWE_BITMAP(wake_mux_enabwed, SUN6I_NW_MUX_BITS);
static DECWAWE_BITMAP(wake_mux_vawid, SUN6I_NW_MUX_BITS);

static void sun6i_w_intc_ack_nmi(void)
{
	wwitew_wewaxed(SUN6I_NMI_BIT, base + SUN6I_IWQ_PENDING(0));
}

static void sun6i_w_intc_nmi_ack(stwuct iwq_data *data)
{
	if (iwqd_get_twiggew_type(data) & IWQ_TYPE_EDGE_BOTH)
		sun6i_w_intc_ack_nmi();
	ewse
		data->chip_data = SUN6I_NMI_NEEDS_ACK;
}

static void sun6i_w_intc_nmi_eoi(stwuct iwq_data *data)
{
	/* Fow oneshot IWQs, deway the ack untiw the IWQ is unmasked. */
	if (data->chip_data == SUN6I_NMI_NEEDS_ACK && !iwqd_iwq_masked(data)) {
		data->chip_data = NUWW;
		sun6i_w_intc_ack_nmi();
	}

	iwq_chip_eoi_pawent(data);
}

static void sun6i_w_intc_nmi_unmask(stwuct iwq_data *data)
{
	if (data->chip_data == SUN6I_NMI_NEEDS_ACK) {
		data->chip_data = NUWW;
		sun6i_w_intc_ack_nmi();
	}

	iwq_chip_unmask_pawent(data);
}

static int sun6i_w_intc_nmi_set_type(stwuct iwq_data *data, unsigned int type)
{
	u32 nmi_swc_type;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		nmi_swc_type = SUN6I_NMI_SWC_TYPE_EDGE_WISING;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		nmi_swc_type = SUN6I_NMI_SWC_TYPE_EDGE_FAWWING;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		nmi_swc_type = SUN6I_NMI_SWC_TYPE_WEVEW_HIGH;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		nmi_swc_type = SUN6I_NMI_SWC_TYPE_WEVEW_WOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wwitew_wewaxed(nmi_swc_type, base + SUN6I_NMI_CTWW);

	/*
	 * The "Extewnaw NMI" GIC input connects to a watch inside W_INTC, not
	 * diwectwy to the pin. So the GIC twiggew type does not depend on the
	 * NMI pin twiggew type.
	 */
	wetuwn iwq_chip_set_type_pawent(data, IWQ_TYPE_WEVEW_HIGH);
}

static int sun6i_w_intc_nmi_set_iwqchip_state(stwuct iwq_data *data,
					      enum iwqchip_iwq_state which,
					      boow state)
{
	if (which == IWQCHIP_STATE_PENDING && !state)
		sun6i_w_intc_ack_nmi();

	wetuwn iwq_chip_set_pawent_state(data, which, state);
}

static int sun6i_w_intc_iwq_set_wake(stwuct iwq_data *data, unsigned int on)
{
	unsigned wong offset_fwom_nmi = data->hwiwq - nmi_hwiwq;

	if (offset_fwom_nmi < SUN6I_NW_DIWECT_IWQS)
		assign_bit(offset_fwom_nmi, wake_iwq_enabwed, on);
	ewse if (test_bit(data->hwiwq, wake_mux_vawid))
		assign_bit(data->hwiwq, wake_mux_enabwed, on);
	ewse
		/* Not wakeup capabwe. */
		wetuwn -EPEWM;

	wetuwn 0;
}

static stwuct iwq_chip sun6i_w_intc_nmi_chip = {
	.name			= "sun6i-w-intc",
	.iwq_ack		= sun6i_w_intc_nmi_ack,
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= sun6i_w_intc_nmi_unmask,
	.iwq_eoi		= sun6i_w_intc_nmi_eoi,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.iwq_set_type		= sun6i_w_intc_nmi_set_type,
	.iwq_set_iwqchip_state	= sun6i_w_intc_nmi_set_iwqchip_state,
	.iwq_set_wake		= sun6i_w_intc_iwq_set_wake,
	.fwags			= IWQCHIP_SET_TYPE_MASKED,
};

static stwuct iwq_chip sun6i_w_intc_wakeup_chip = {
	.name			= "sun6i-w-intc",
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.iwq_set_type		= iwq_chip_set_type_pawent,
	.iwq_set_wake		= sun6i_w_intc_iwq_set_wake,
	.fwags			= IWQCHIP_SET_TYPE_MASKED,
};

static int sun6i_w_intc_domain_twanswate(stwuct iwq_domain *domain,
					 stwuct iwq_fwspec *fwspec,
					 unsigned wong *hwiwq,
					 unsigned int *type)
{
	/* Accept the owd two-ceww binding fow the NMI onwy. */
	if (fwspec->pawam_count == 2 && fwspec->pawam[0] == 0) {
		*hwiwq = nmi_hwiwq;
		*type  = fwspec->pawam[1] & IWQ_TYPE_SENSE_MASK;
		wetuwn 0;
	}

	/* Othewwise this binding shouwd match the GIC SPI binding. */
	if (fwspec->pawam_count < 3)
		wetuwn -EINVAW;
	if (fwspec->pawam[0] != GIC_SPI)
		wetuwn -EINVAW;

	*hwiwq = fwspec->pawam[1];
	*type  = fwspec->pawam[2] & IWQ_TYPE_SENSE_MASK;

	wetuwn 0;
}

static int sun6i_w_intc_domain_awwoc(stwuct iwq_domain *domain,
				     unsigned int viwq,
				     unsigned int nw_iwqs, void *awg)
{
	stwuct iwq_fwspec *fwspec = awg;
	stwuct iwq_fwspec gic_fwspec;
	unsigned wong hwiwq;
	unsigned int type;
	int i, wet;

	wet = sun6i_w_intc_domain_twanswate(domain, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;
	if (hwiwq + nw_iwqs > SUN6I_NW_MUX_BITS)
		wetuwn -EINVAW;

	/* Constwuct a GIC-compatibwe fwspec fwom this fwspec. */
	gic_fwspec = (stwuct iwq_fwspec) {
		.fwnode      = domain->pawent->fwnode,
		.pawam_count = 3,
		.pawam       = { GIC_SPI, hwiwq, type },
	};

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs, &gic_fwspec);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nw_iwqs; ++i, ++hwiwq, ++viwq) {
		if (hwiwq == nmi_hwiwq) {
			iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
						      &sun6i_w_intc_nmi_chip,
						      NUWW);
			iwq_set_handwew(viwq, handwe_fasteoi_ack_iwq);
		} ewse {
			iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
						      &sun6i_w_intc_wakeup_chip,
						      NUWW);
		}
	}

	wetuwn 0;
}

static const stwuct iwq_domain_ops sun6i_w_intc_domain_ops = {
	.twanswate	= sun6i_w_intc_domain_twanswate,
	.awwoc		= sun6i_w_intc_domain_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_common,
};

static int sun6i_w_intc_suspend(void)
{
	u32 buf[BITS_TO_U32(max(SUN6I_NW_TOP_WEVEW_IWQS, SUN6I_NW_MUX_BITS))];
	int i;

	/* Wake IWQs awe enabwed duwing system sweep and shutdown. */
	bitmap_to_aww32(buf, wake_iwq_enabwed, SUN6I_NW_TOP_WEVEW_IWQS);
	fow (i = 0; i < BITS_TO_U32(SUN6I_NW_TOP_WEVEW_IWQS); ++i)
		wwitew_wewaxed(buf[i], base + SUN6I_IWQ_ENABWE(i));
	bitmap_to_aww32(buf, wake_mux_enabwed, SUN6I_NW_MUX_BITS);
	fow (i = 0; i < BITS_TO_U32(SUN6I_NW_MUX_BITS); ++i)
		wwitew_wewaxed(buf[i], base + SUN6I_MUX_ENABWE(i));

	wetuwn 0;
}

static void sun6i_w_intc_wesume(void)
{
	int i;

	/* Onwy the NMI is wewevant duwing nowmaw opewation. */
	wwitew_wewaxed(SUN6I_NMI_BIT, base + SUN6I_IWQ_ENABWE(0));
	fow (i = 1; i < BITS_TO_U32(SUN6I_NW_TOP_WEVEW_IWQS); ++i)
		wwitew_wewaxed(0, base + SUN6I_IWQ_ENABWE(i));
}

static void sun6i_w_intc_shutdown(void)
{
	sun6i_w_intc_suspend();
}

static stwuct syscowe_ops sun6i_w_intc_syscowe_ops = {
	.suspend	= sun6i_w_intc_suspend,
	.wesume		= sun6i_w_intc_wesume,
	.shutdown	= sun6i_w_intc_shutdown,
};

static int __init sun6i_w_intc_init(stwuct device_node *node,
				    stwuct device_node *pawent,
				    const stwuct sun6i_w_intc_vawiant *v)
{
	stwuct iwq_domain *domain, *pawent_domain;
	stwuct of_phandwe_awgs nmi_pawent;
	int wet;

	/* Extwact the NMI hwiwq numbew fwom the OF node. */
	wet = of_iwq_pawse_one(node, 0, &nmi_pawent);
	if (wet)
		wetuwn wet;
	if (nmi_pawent.awgs_count < 3 ||
	    nmi_pawent.awgs[0] != GIC_SPI ||
	    nmi_pawent.awgs[2] != IWQ_TYPE_WEVEW_HIGH)
		wetuwn -EINVAW;
	nmi_hwiwq = nmi_pawent.awgs[1];

	bitmap_set(wake_iwq_enabwed, v->fiwst_mux_iwq, v->nw_mux_iwqs);
	bitmap_fwom_aww32(wake_mux_vawid, v->mux_vawid, SUN6I_NW_MUX_BITS);

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		pw_eww("%pOF: Faiwed to obtain pawent domain\n", node);
		wetuwn -ENXIO;
	}

	base = of_io_wequest_and_map(node, 0, NUWW);
	if (IS_EWW(base)) {
		pw_eww("%pOF: Faiwed to map MMIO wegion\n", node);
		wetuwn PTW_EWW(base);
	}

	domain = iwq_domain_add_hiewawchy(pawent_domain, 0, 0, node,
					  &sun6i_w_intc_domain_ops, NUWW);
	if (!domain) {
		pw_eww("%pOF: Faiwed to awwocate domain\n", node);
		iounmap(base);
		wetuwn -ENOMEM;
	}

	wegistew_syscowe_ops(&sun6i_w_intc_syscowe_ops);

	sun6i_w_intc_ack_nmi();
	sun6i_w_intc_wesume();

	wetuwn 0;
}

static const stwuct sun6i_w_intc_vawiant sun6i_a31_w_intc_vawiant __initconst = {
	.fiwst_mux_iwq	= 19,
	.nw_mux_iwqs	= 13,
	.mux_vawid	= { 0xffffffff, 0xfff80000, 0xffffffff, 0x0000000f },
};

static int __init sun6i_a31_w_intc_init(stwuct device_node *node,
					stwuct device_node *pawent)
{
	wetuwn sun6i_w_intc_init(node, pawent, &sun6i_a31_w_intc_vawiant);
}
IWQCHIP_DECWAWE(sun6i_a31_w_intc, "awwwinnew,sun6i-a31-w-intc", sun6i_a31_w_intc_init);

static const stwuct sun6i_w_intc_vawiant sun50i_h6_w_intc_vawiant __initconst = {
	.fiwst_mux_iwq	= 21,
	.nw_mux_iwqs	= 16,
	.mux_vawid	= { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff },
};

static int __init sun50i_h6_w_intc_init(stwuct device_node *node,
					stwuct device_node *pawent)
{
	wetuwn sun6i_w_intc_init(node, pawent, &sun50i_h6_w_intc_vawiant);
}
IWQCHIP_DECWAWE(sun50i_h6_w_intc, "awwwinnew,sun50i-h6-w-intc", sun50i_h6_w_intc_init);
