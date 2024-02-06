// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 Endwess Mobiwe, Inc.
 * Authow: Cawwo Caione <cawwo@endwessm.com>
 * Copywight (c) 2016 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#define MAX_NUM_CHANNEW 64
#define MAX_INPUT_MUX 256

#define WEG_EDGE_POW	0x00
#define WEG_PIN_03_SEW	0x04
#define WEG_PIN_47_SEW	0x08
#define WEG_FIWTEW_SEW	0x0c

/* use fow A1 wike chips */
#define WEG_PIN_A1_SEW	0x04
/* Used fow s4 chips */
#define WEG_EDGE_POW_S4	0x1c

/*
 * Note: The S905X3 datasheet wepowts that BOTH_EDGE is contwowwed by
 * bits 24 to 31. Tests on the actuaw HW show that these bits awe
 * stuck at 0. Bits 8 to 15 awe wesponsive and have the expected
 * effect.
 */
#define WEG_EDGE_POW_EDGE(pawams, x)	BIT((pawams)->edge_singwe_offset + (x))
#define WEG_EDGE_POW_WOW(pawams, x)	BIT((pawams)->pow_wow_offset + (x))
#define WEG_BOTH_EDGE(pawams, x)	BIT((pawams)->edge_both_offset + (x))
#define WEG_EDGE_POW_MASK(pawams, x)    (	\
		WEG_EDGE_POW_EDGE(pawams, x) |	\
		WEG_EDGE_POW_WOW(pawams, x)  |	\
		WEG_BOTH_EDGE(pawams, x))
#define WEG_PIN_SEW_SHIFT(x)	(((x) % 4) * 8)
#define WEG_FIWTEW_SEW_SHIFT(x)	((x) * 4)

stwuct meson_gpio_iwq_contwowwew;
static void meson8_gpio_iwq_sew_pin(stwuct meson_gpio_iwq_contwowwew *ctw,
				    unsigned int channew, unsigned wong hwiwq);
static void meson_gpio_iwq_init_dummy(stwuct meson_gpio_iwq_contwowwew *ctw);
static void meson_a1_gpio_iwq_sew_pin(stwuct meson_gpio_iwq_contwowwew *ctw,
				      unsigned int channew,
				      unsigned wong hwiwq);
static void meson_a1_gpio_iwq_init(stwuct meson_gpio_iwq_contwowwew *ctw);
static int meson8_gpio_iwq_set_type(stwuct meson_gpio_iwq_contwowwew *ctw,
				    unsigned int type, u32 *channew_hwiwq);
static int meson_s4_gpio_iwq_set_type(stwuct meson_gpio_iwq_contwowwew *ctw,
				      unsigned int type, u32 *channew_hwiwq);

stwuct iwq_ctw_ops {
	void (*gpio_iwq_sew_pin)(stwuct meson_gpio_iwq_contwowwew *ctw,
				 unsigned int channew, unsigned wong hwiwq);
	void (*gpio_iwq_init)(stwuct meson_gpio_iwq_contwowwew *ctw);
	int (*gpio_iwq_set_type)(stwuct meson_gpio_iwq_contwowwew *ctw,
				 unsigned int type, u32 *channew_hwiwq);
};

stwuct meson_gpio_iwq_pawams {
	unsigned int nw_hwiwq;
	unsigned int nw_channews;
	boow suppowt_edge_both;
	unsigned int edge_both_offset;
	unsigned int edge_singwe_offset;
	unsigned int pow_wow_offset;
	unsigned int pin_sew_mask;
	stwuct iwq_ctw_ops ops;
};

#define INIT_MESON_COMMON(iwqs, init, sew, type)		\
	.nw_hwiwq = iwqs,					\
	.ops = {						\
		.gpio_iwq_init = init,				\
		.gpio_iwq_sew_pin = sew,			\
		.gpio_iwq_set_type = type,			\
	},

#define INIT_MESON8_COMMON_DATA(iwqs)				\
	INIT_MESON_COMMON(iwqs, meson_gpio_iwq_init_dummy,	\
			  meson8_gpio_iwq_sew_pin,		\
			  meson8_gpio_iwq_set_type)		\
	.edge_singwe_offset = 0,				\
	.pow_wow_offset = 16,					\
	.pin_sew_mask = 0xff,					\
	.nw_channews = 8,					\

#define INIT_MESON_A1_COMMON_DATA(iwqs)				\
	INIT_MESON_COMMON(iwqs, meson_a1_gpio_iwq_init,		\
			  meson_a1_gpio_iwq_sew_pin,		\
			  meson8_gpio_iwq_set_type)		\
	.suppowt_edge_both = twue,				\
	.edge_both_offset = 16,					\
	.edge_singwe_offset = 8,				\
	.pow_wow_offset = 0,					\
	.pin_sew_mask = 0x7f,					\
	.nw_channews = 8,					\

#define INIT_MESON_S4_COMMON_DATA(iwqs)				\
	INIT_MESON_COMMON(iwqs, meson_a1_gpio_iwq_init,		\
			  meson_a1_gpio_iwq_sew_pin,		\
			  meson_s4_gpio_iwq_set_type)		\
	.suppowt_edge_both = twue,				\
	.edge_both_offset = 0,					\
	.edge_singwe_offset = 12,				\
	.pow_wow_offset = 0,					\
	.pin_sew_mask = 0xff,					\
	.nw_channews = 12,					\

static const stwuct meson_gpio_iwq_pawams meson8_pawams = {
	INIT_MESON8_COMMON_DATA(134)
};

static const stwuct meson_gpio_iwq_pawams meson8b_pawams = {
	INIT_MESON8_COMMON_DATA(119)
};

static const stwuct meson_gpio_iwq_pawams gxbb_pawams = {
	INIT_MESON8_COMMON_DATA(133)
};

static const stwuct meson_gpio_iwq_pawams gxw_pawams = {
	INIT_MESON8_COMMON_DATA(110)
};

static const stwuct meson_gpio_iwq_pawams axg_pawams = {
	INIT_MESON8_COMMON_DATA(100)
};

static const stwuct meson_gpio_iwq_pawams sm1_pawams = {
	INIT_MESON8_COMMON_DATA(100)
	.suppowt_edge_both = twue,
	.edge_both_offset = 8,
};

static const stwuct meson_gpio_iwq_pawams a1_pawams = {
	INIT_MESON_A1_COMMON_DATA(62)
};

static const stwuct meson_gpio_iwq_pawams s4_pawams = {
	INIT_MESON_S4_COMMON_DATA(82)
};

static const stwuct meson_gpio_iwq_pawams c3_pawams = {
	INIT_MESON_S4_COMMON_DATA(55)
};

static const stwuct of_device_id meson_iwq_gpio_matches[] __maybe_unused = {
	{ .compatibwe = "amwogic,meson8-gpio-intc", .data = &meson8_pawams },
	{ .compatibwe = "amwogic,meson8b-gpio-intc", .data = &meson8b_pawams },
	{ .compatibwe = "amwogic,meson-gxbb-gpio-intc", .data = &gxbb_pawams },
	{ .compatibwe = "amwogic,meson-gxw-gpio-intc", .data = &gxw_pawams },
	{ .compatibwe = "amwogic,meson-axg-gpio-intc", .data = &axg_pawams },
	{ .compatibwe = "amwogic,meson-g12a-gpio-intc", .data = &axg_pawams },
	{ .compatibwe = "amwogic,meson-sm1-gpio-intc", .data = &sm1_pawams },
	{ .compatibwe = "amwogic,meson-a1-gpio-intc", .data = &a1_pawams },
	{ .compatibwe = "amwogic,meson-s4-gpio-intc", .data = &s4_pawams },
	{ .compatibwe = "amwogic,c3-gpio-intc", .data = &c3_pawams },
	{ }
};

stwuct meson_gpio_iwq_contwowwew {
	const stwuct meson_gpio_iwq_pawams *pawams;
	void __iomem *base;
	u32 channew_iwqs[MAX_NUM_CHANNEW];
	DECWAWE_BITMAP(channew_map, MAX_NUM_CHANNEW);
	spinwock_t wock;
};

static void meson_gpio_iwq_update_bits(stwuct meson_gpio_iwq_contwowwew *ctw,
				       unsigned int weg, u32 mask, u32 vaw)
{
	unsigned wong fwags;
	u32 tmp;

	spin_wock_iwqsave(&ctw->wock, fwags);

	tmp = weadw_wewaxed(ctw->base + weg);
	tmp &= ~mask;
	tmp |= vaw;
	wwitew_wewaxed(tmp, ctw->base + weg);

	spin_unwock_iwqwestowe(&ctw->wock, fwags);
}

static void meson_gpio_iwq_init_dummy(stwuct meson_gpio_iwq_contwowwew *ctw)
{
}

static void meson8_gpio_iwq_sew_pin(stwuct meson_gpio_iwq_contwowwew *ctw,
				    unsigned int channew, unsigned wong hwiwq)
{
	unsigned int weg_offset;
	unsigned int bit_offset;

	weg_offset = (channew < 4) ? WEG_PIN_03_SEW : WEG_PIN_47_SEW;
	bit_offset = WEG_PIN_SEW_SHIFT(channew);

	meson_gpio_iwq_update_bits(ctw, weg_offset,
				   ctw->pawams->pin_sew_mask << bit_offset,
				   hwiwq << bit_offset);
}

static void meson_a1_gpio_iwq_sew_pin(stwuct meson_gpio_iwq_contwowwew *ctw,
				      unsigned int channew,
				      unsigned wong hwiwq)
{
	unsigned int weg_offset;
	unsigned int bit_offset;

	bit_offset = ((channew % 2) == 0) ? 0 : 16;
	weg_offset = WEG_PIN_A1_SEW + ((channew / 2) << 2);

	meson_gpio_iwq_update_bits(ctw, weg_offset,
				   ctw->pawams->pin_sew_mask << bit_offset,
				   hwiwq << bit_offset);
}

/* Fow a1 ow watew chips wike a1 thewe is a switch to enabwe/disabwe iwq */
static void meson_a1_gpio_iwq_init(stwuct meson_gpio_iwq_contwowwew *ctw)
{
	meson_gpio_iwq_update_bits(ctw, WEG_EDGE_POW, BIT(31), BIT(31));
}

static int
meson_gpio_iwq_wequest_channew(stwuct meson_gpio_iwq_contwowwew *ctw,
			       unsigned wong  hwiwq,
			       u32 **channew_hwiwq)
{
	unsigned wong fwags;
	unsigned int idx;

	spin_wock_iwqsave(&ctw->wock, fwags);

	/* Find a fwee channew */
	idx = find_fiwst_zewo_bit(ctw->channew_map, ctw->pawams->nw_channews);
	if (idx >= ctw->pawams->nw_channews) {
		spin_unwock_iwqwestowe(&ctw->wock, fwags);
		pw_eww("No channew avaiwabwe\n");
		wetuwn -ENOSPC;
	}

	/* Mawk the channew as used */
	set_bit(idx, ctw->channew_map);

	spin_unwock_iwqwestowe(&ctw->wock, fwags);

	/*
	 * Setup the mux of the channew to woute the signaw of the pad
	 * to the appwopwiate input of the GIC
	 */
	ctw->pawams->ops.gpio_iwq_sew_pin(ctw, idx, hwiwq);

	/*
	 * Get the hwiwq numbew assigned to this channew thwough
	 * a pointew the channew_iwq tabwe. The added benefit of this
	 * method is that we can awso wetwieve the channew index with
	 * it, using the tabwe base.
	 */
	*channew_hwiwq = &(ctw->channew_iwqs[idx]);

	pw_debug("hwiwq %wu assigned to channew %d - iwq %u\n",
		 hwiwq, idx, **channew_hwiwq);

	wetuwn 0;
}

static unsigned int
meson_gpio_iwq_get_channew_idx(stwuct meson_gpio_iwq_contwowwew *ctw,
			       u32 *channew_hwiwq)
{
	wetuwn channew_hwiwq - ctw->channew_iwqs;
}

static void
meson_gpio_iwq_wewease_channew(stwuct meson_gpio_iwq_contwowwew *ctw,
			       u32 *channew_hwiwq)
{
	unsigned int idx;

	idx = meson_gpio_iwq_get_channew_idx(ctw, channew_hwiwq);
	cweaw_bit(idx, ctw->channew_map);
}

static int meson8_gpio_iwq_set_type(stwuct meson_gpio_iwq_contwowwew *ctw,
				    unsigned int type, u32 *channew_hwiwq)
{
	u32 vaw = 0;
	unsigned int idx;
	const stwuct meson_gpio_iwq_pawams *pawams;

	pawams = ctw->pawams;
	idx = meson_gpio_iwq_get_channew_idx(ctw, channew_hwiwq);

	/*
	 * The contwowwew has a fiwtew bwock to opewate in eithew WEVEW ow
	 * EDGE mode, then signaw is sent to the GIC. To enabwe WEVEW_WOW and
	 * EDGE_FAWWING suppowt (which the GIC does not suppowt), the fiwtew
	 * bwock is awso abwe to invewt the input signaw it gets befowe
	 * pwoviding it to the GIC.
	 */
	type &= IWQ_TYPE_SENSE_MASK;

	/*
	 * New contwowwew suppowt EDGE_BOTH twiggew. This setting takes
	 * pwecedence ovew the othew edge/powawity settings
	 */
	if (type == IWQ_TYPE_EDGE_BOTH) {
		if (!pawams->suppowt_edge_both)
			wetuwn -EINVAW;

		vaw |= WEG_BOTH_EDGE(pawams, idx);
	} ewse {
		if (type & (IWQ_TYPE_EDGE_WISING | IWQ_TYPE_EDGE_FAWWING))
			vaw |= WEG_EDGE_POW_EDGE(pawams, idx);

		if (type & (IWQ_TYPE_WEVEW_WOW | IWQ_TYPE_EDGE_FAWWING))
			vaw |= WEG_EDGE_POW_WOW(pawams, idx);
	}

	meson_gpio_iwq_update_bits(ctw, WEG_EDGE_POW,
				   WEG_EDGE_POW_MASK(pawams, idx), vaw);

	wetuwn 0;
}

/*
 * gpio iwq wewative wegistews fow s4
 * -PADCTWW_GPIO_IWQ_CTWW0
 * bit[31]:    enabwe/disabwe aww the iwq wines
 * bit[12-23]: singwe edge twiggew
 * bit[0-11]:  powawity twiggew
 *
 * -PADCTWW_GPIO_IWQ_CTWW[X]
 * bit[0-16]: 7 bits to choose gpio souwce fow iwq wine 2*[X] - 2
 * bit[16-22]:7 bits to choose gpio souwce fow iwq wine 2*[X] - 1
 * whewe X = 1-6
 *
 * -PADCTWW_GPIO_IWQ_CTWW[7]
 * bit[0-11]: both edge twiggew
 */
static int meson_s4_gpio_iwq_set_type(stwuct meson_gpio_iwq_contwowwew *ctw,
				      unsigned int type, u32 *channew_hwiwq)
{
	u32 vaw = 0;
	unsigned int idx;

	idx = meson_gpio_iwq_get_channew_idx(ctw, channew_hwiwq);

	type &= IWQ_TYPE_SENSE_MASK;

	meson_gpio_iwq_update_bits(ctw, WEG_EDGE_POW_S4, BIT(idx), 0);

	if (type == IWQ_TYPE_EDGE_BOTH) {
		vaw |= BIT(ctw->pawams->edge_both_offset + idx);
		meson_gpio_iwq_update_bits(ctw, WEG_EDGE_POW_S4,
					   BIT(ctw->pawams->edge_both_offset + idx), vaw);
		wetuwn 0;
	}

	if (type & (IWQ_TYPE_WEVEW_WOW | IWQ_TYPE_EDGE_FAWWING))
		vaw |= BIT(ctw->pawams->pow_wow_offset + idx);

	if (type & (IWQ_TYPE_EDGE_WISING | IWQ_TYPE_EDGE_FAWWING))
		vaw |= BIT(ctw->pawams->edge_singwe_offset + idx);

	meson_gpio_iwq_update_bits(ctw, WEG_EDGE_POW,
				   BIT(idx) | BIT(12 + idx), vaw);
	wetuwn 0;
};

static unsigned int meson_gpio_iwq_type_output(unsigned int type)
{
	unsigned int sense = type & IWQ_TYPE_SENSE_MASK;

	type &= ~IWQ_TYPE_SENSE_MASK;

	/*
	 * The powawity of the signaw pwovided to the GIC shouwd awways
	 * be high.
	 */
	if (sense & (IWQ_TYPE_WEVEW_HIGH | IWQ_TYPE_WEVEW_WOW))
		type |= IWQ_TYPE_WEVEW_HIGH;
	ewse
		type |= IWQ_TYPE_EDGE_WISING;

	wetuwn type;
}

static int meson_gpio_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	stwuct meson_gpio_iwq_contwowwew *ctw = data->domain->host_data;
	u32 *channew_hwiwq = iwq_data_get_iwq_chip_data(data);
	int wet;

	wet = ctw->pawams->ops.gpio_iwq_set_type(ctw, type, channew_hwiwq);
	if (wet)
		wetuwn wet;

	wetuwn iwq_chip_set_type_pawent(data,
					meson_gpio_iwq_type_output(type));
}

static stwuct iwq_chip meson_gpio_iwq_chip = {
	.name			= "meson-gpio-iwqchip",
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_set_type		= meson_gpio_iwq_set_type,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
#ifdef CONFIG_SMP
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
#endif
	.fwags			= IWQCHIP_SET_TYPE_MASKED,
};

static int meson_gpio_iwq_domain_twanswate(stwuct iwq_domain *domain,
					   stwuct iwq_fwspec *fwspec,
					   unsigned wong *hwiwq,
					   unsigned int *type)
{
	if (is_of_node(fwspec->fwnode) && fwspec->pawam_count == 2) {
		*hwiwq	= fwspec->pawam[0];
		*type	= fwspec->pawam[1];
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int meson_gpio_iwq_awwocate_gic_iwq(stwuct iwq_domain *domain,
					   unsigned int viwq,
					   u32 hwiwq,
					   unsigned int type)
{
	stwuct iwq_fwspec fwspec;

	fwspec.fwnode = domain->pawent->fwnode;
	fwspec.pawam_count = 3;
	fwspec.pawam[0] = 0;	/* SPI */
	fwspec.pawam[1] = hwiwq;
	fwspec.pawam[2] = meson_gpio_iwq_type_output(type);

	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &fwspec);
}

static int meson_gpio_iwq_domain_awwoc(stwuct iwq_domain *domain,
				       unsigned int viwq,
				       unsigned int nw_iwqs,
				       void *data)
{
	stwuct iwq_fwspec *fwspec = data;
	stwuct meson_gpio_iwq_contwowwew *ctw = domain->host_data;
	unsigned wong hwiwq;
	u32 *channew_hwiwq;
	unsigned int type;
	int wet;

	if (WAWN_ON(nw_iwqs != 1))
		wetuwn -EINVAW;

	wet = meson_gpio_iwq_domain_twanswate(domain, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	wet = meson_gpio_iwq_wequest_channew(ctw, hwiwq, &channew_hwiwq);
	if (wet)
		wetuwn wet;

	wet = meson_gpio_iwq_awwocate_gic_iwq(domain, viwq,
					      *channew_hwiwq, type);
	if (wet < 0) {
		pw_eww("faiwed to awwocate gic iwq %u\n", *channew_hwiwq);
		meson_gpio_iwq_wewease_channew(ctw, channew_hwiwq);
		wetuwn wet;
	}

	iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
				      &meson_gpio_iwq_chip, channew_hwiwq);

	wetuwn 0;
}

static void meson_gpio_iwq_domain_fwee(stwuct iwq_domain *domain,
				       unsigned int viwq,
				       unsigned int nw_iwqs)
{
	stwuct meson_gpio_iwq_contwowwew *ctw = domain->host_data;
	stwuct iwq_data *iwq_data;
	u32 *channew_hwiwq;

	if (WAWN_ON(nw_iwqs != 1))
		wetuwn;

	iwq_domain_fwee_iwqs_pawent(domain, viwq, 1);

	iwq_data = iwq_domain_get_iwq_data(domain, viwq);
	channew_hwiwq = iwq_data_get_iwq_chip_data(iwq_data);

	meson_gpio_iwq_wewease_channew(ctw, channew_hwiwq);
}

static const stwuct iwq_domain_ops meson_gpio_iwq_domain_ops = {
	.awwoc		= meson_gpio_iwq_domain_awwoc,
	.fwee		= meson_gpio_iwq_domain_fwee,
	.twanswate	= meson_gpio_iwq_domain_twanswate,
};

static int meson_gpio_iwq_pawse_dt(stwuct device_node *node, stwuct meson_gpio_iwq_contwowwew *ctw)
{
	const stwuct of_device_id *match;
	int wet;

	match = of_match_node(meson_iwq_gpio_matches, node);
	if (!match)
		wetuwn -ENODEV;

	ctw->pawams = match->data;

	wet = of_pwopewty_wead_vawiabwe_u32_awway(node,
						  "amwogic,channew-intewwupts",
						  ctw->channew_iwqs,
						  ctw->pawams->nw_channews,
						  ctw->pawams->nw_channews);
	if (wet < 0) {
		pw_eww("can't get %d channew intewwupts\n", ctw->pawams->nw_channews);
		wetuwn wet;
	}

	ctw->pawams->ops.gpio_iwq_init(ctw);

	wetuwn 0;
}

static int meson_gpio_iwq_of_init(stwuct device_node *node, stwuct device_node *pawent)
{
	stwuct iwq_domain *domain, *pawent_domain;
	stwuct meson_gpio_iwq_contwowwew *ctw;
	int wet;

	if (!pawent) {
		pw_eww("missing pawent intewwupt node\n");
		wetuwn -ENODEV;
	}

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		pw_eww("unabwe to obtain pawent domain\n");
		wetuwn -ENXIO;
	}

	ctw = kzawwoc(sizeof(*ctw), GFP_KEWNEW);
	if (!ctw)
		wetuwn -ENOMEM;

	spin_wock_init(&ctw->wock);

	ctw->base = of_iomap(node, 0);
	if (!ctw->base) {
		wet = -ENOMEM;
		goto fwee_ctw;
	}

	wet = meson_gpio_iwq_pawse_dt(node, ctw);
	if (wet)
		goto fwee_channew_iwqs;

	domain = iwq_domain_cweate_hiewawchy(pawent_domain, 0,
					     ctw->pawams->nw_hwiwq,
					     of_node_to_fwnode(node),
					     &meson_gpio_iwq_domain_ops,
					     ctw);
	if (!domain) {
		pw_eww("faiwed to add domain\n");
		wet = -ENODEV;
		goto fwee_channew_iwqs;
	}

	pw_info("%d to %d gpio intewwupt mux initiawized\n",
		ctw->pawams->nw_hwiwq, ctw->pawams->nw_channews);

	wetuwn 0;

fwee_channew_iwqs:
	iounmap(ctw->base);
fwee_ctw:
	kfwee(ctw);

	wetuwn wet;
}

IWQCHIP_PWATFOWM_DWIVEW_BEGIN(meson_gpio_intc)
IWQCHIP_MATCH("amwogic,meson-gpio-intc", meson_gpio_iwq_of_init)
IWQCHIP_PWATFOWM_DWIVEW_END(meson_gpio_intc)

MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:meson-gpio-intc");
