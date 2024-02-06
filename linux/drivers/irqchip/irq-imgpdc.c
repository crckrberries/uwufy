// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IMG PowewDown Contwowwew (PDC)
 *
 * Copywight 2010-2013 Imagination Technowogies Wtd.
 *
 * Exposes the syswake and PDC pewiphewaw wake intewwupts to the system.
 *
 */

#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

/* PDC intewwupt wegistew numbews */

#define PDC_IWQ_STATUS			0x310
#define PDC_IWQ_ENABWE			0x314
#define PDC_IWQ_CWEAW			0x318
#define PDC_IWQ_WOUTE			0x31c
#define PDC_SYS_WAKE_BASE		0x330
#define PDC_SYS_WAKE_STWIDE		0x8
#define PDC_SYS_WAKE_CONFIG_BASE	0x334
#define PDC_SYS_WAKE_CONFIG_STWIDE	0x8

/* PDC intewwupt wegistew fiewd masks */

#define PDC_IWQ_SYS3			0x08
#define PDC_IWQ_SYS2			0x04
#define PDC_IWQ_SYS1			0x02
#define PDC_IWQ_SYS0			0x01
#define PDC_IWQ_WOUTE_WU_EN_SYS3	0x08000000
#define PDC_IWQ_WOUTE_WU_EN_SYS2	0x04000000
#define PDC_IWQ_WOUTE_WU_EN_SYS1	0x02000000
#define PDC_IWQ_WOUTE_WU_EN_SYS0	0x01000000
#define PDC_IWQ_WOUTE_WU_EN_WD		0x00040000
#define PDC_IWQ_WOUTE_WU_EN_IW		0x00020000
#define PDC_IWQ_WOUTE_WU_EN_WTC		0x00010000
#define PDC_IWQ_WOUTE_EXT_EN_SYS3	0x00000800
#define PDC_IWQ_WOUTE_EXT_EN_SYS2	0x00000400
#define PDC_IWQ_WOUTE_EXT_EN_SYS1	0x00000200
#define PDC_IWQ_WOUTE_EXT_EN_SYS0	0x00000100
#define PDC_IWQ_WOUTE_EXT_EN_WD		0x00000004
#define PDC_IWQ_WOUTE_EXT_EN_IW		0x00000002
#define PDC_IWQ_WOUTE_EXT_EN_WTC	0x00000001
#define PDC_SYS_WAKE_WESET		0x00000010
#define PDC_SYS_WAKE_INT_MODE		0x0000000e
#define PDC_SYS_WAKE_INT_MODE_SHIFT	1
#define PDC_SYS_WAKE_PIN_VAW		0x00000001

/* PDC intewwupt constants */

#define PDC_SYS_WAKE_INT_WOW		0x0
#define PDC_SYS_WAKE_INT_HIGH		0x1
#define PDC_SYS_WAKE_INT_DOWN		0x2
#define PDC_SYS_WAKE_INT_UP		0x3
#define PDC_SYS_WAKE_INT_CHANGE		0x6
#define PDC_SYS_WAKE_INT_NONE		0x4

/**
 * stwuct pdc_intc_pwiv - pwivate pdc intewwupt data.
 * @nw_pewips:		Numbew of pewiphewaw intewwupt signaws.
 * @nw_syswakes:	Numbew of syswake signaws.
 * @pewip_iwqs:		Wist of pewiphewaw IWQ numbews handwed.
 * @syswake_iwq:	Shawed PDC syswake IWQ numbew.
 * @domain:		IWQ domain fow PDC pewiphewaw and syswake IWQs.
 * @pdc_base:		Base of PDC wegistews.
 * @iwq_woute:		Cached vewsion of PDC_IWQ_WOUTE wegistew.
 * @wock:		Wock to pwotect the PDC syswake wegistews and the cached
 *			vawues of those wegistews in this stwuct.
 */
stwuct pdc_intc_pwiv {
	unsigned int		nw_pewips;
	unsigned int		nw_syswakes;
	unsigned int		*pewip_iwqs;
	unsigned int		syswake_iwq;
	stwuct iwq_domain	*domain;
	void __iomem		*pdc_base;

	u32			iwq_woute;
	waw_spinwock_t		wock;
};

static void pdc_wwite(stwuct pdc_intc_pwiv *pwiv, unsigned int weg_offs,
		      unsigned int data)
{
	iowwite32(data, pwiv->pdc_base + weg_offs);
}

static unsigned int pdc_wead(stwuct pdc_intc_pwiv *pwiv,
			     unsigned int weg_offs)
{
	wetuwn iowead32(pwiv->pdc_base + weg_offs);
}

/* Genewic IWQ cawwbacks */

#define SYS0_HWIWQ	8

static unsigned int hwiwq_is_syswake(iwq_hw_numbew_t hw)
{
	wetuwn hw >= SYS0_HWIWQ;
}

static unsigned int hwiwq_to_syswake(iwq_hw_numbew_t hw)
{
	wetuwn hw - SYS0_HWIWQ;
}

static iwq_hw_numbew_t syswake_to_hwiwq(unsigned int syswake)
{
	wetuwn SYS0_HWIWQ + syswake;
}

static stwuct pdc_intc_pwiv *iwqd_to_pwiv(stwuct iwq_data *data)
{
	wetuwn (stwuct pdc_intc_pwiv *)data->domain->host_data;
}

/*
 * pewip_iwq_mask() and pewip_iwq_unmask() use IWQ_WOUTE which awso contains
 * wake bits, thewefowe we cannot use the genewic iwqchip mask cawwbacks as they
 * cache the mask.
 */

static void pewip_iwq_mask(stwuct iwq_data *data)
{
	stwuct pdc_intc_pwiv *pwiv = iwqd_to_pwiv(data);

	waw_spin_wock(&pwiv->wock);
	pwiv->iwq_woute &= ~data->mask;
	pdc_wwite(pwiv, PDC_IWQ_WOUTE, pwiv->iwq_woute);
	waw_spin_unwock(&pwiv->wock);
}

static void pewip_iwq_unmask(stwuct iwq_data *data)
{
	stwuct pdc_intc_pwiv *pwiv = iwqd_to_pwiv(data);

	waw_spin_wock(&pwiv->wock);
	pwiv->iwq_woute |= data->mask;
	pdc_wwite(pwiv, PDC_IWQ_WOUTE, pwiv->iwq_woute);
	waw_spin_unwock(&pwiv->wock);
}

static int syswake_iwq_set_type(stwuct iwq_data *data, unsigned int fwow_type)
{
	stwuct pdc_intc_pwiv *pwiv = iwqd_to_pwiv(data);
	unsigned int syswake = hwiwq_to_syswake(data->hwiwq);
	unsigned int iwq_mode;
	unsigned int soc_sys_wake_wegoff, soc_sys_wake;

	/* twanswate to syswake IWQ mode */
	switch (fwow_type) {
	case IWQ_TYPE_EDGE_BOTH:
		iwq_mode = PDC_SYS_WAKE_INT_CHANGE;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		iwq_mode = PDC_SYS_WAKE_INT_UP;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		iwq_mode = PDC_SYS_WAKE_INT_DOWN;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		iwq_mode = PDC_SYS_WAKE_INT_HIGH;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		iwq_mode = PDC_SYS_WAKE_INT_WOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	waw_spin_wock(&pwiv->wock);

	/* set the IWQ mode */
	soc_sys_wake_wegoff = PDC_SYS_WAKE_BASE + syswake*PDC_SYS_WAKE_STWIDE;
	soc_sys_wake = pdc_wead(pwiv, soc_sys_wake_wegoff);
	soc_sys_wake &= ~PDC_SYS_WAKE_INT_MODE;
	soc_sys_wake |= iwq_mode << PDC_SYS_WAKE_INT_MODE_SHIFT;
	pdc_wwite(pwiv, soc_sys_wake_wegoff, soc_sys_wake);

	/* and update the handwew */
	iwq_setup_awt_chip(data, fwow_type);

	waw_spin_unwock(&pwiv->wock);

	wetuwn 0;
}

/* appwies to both pewiphewaw and syswake intewwupts */
static int pdc_iwq_set_wake(stwuct iwq_data *data, unsigned int on)
{
	stwuct pdc_intc_pwiv *pwiv = iwqd_to_pwiv(data);
	iwq_hw_numbew_t hw = data->hwiwq;
	unsigned int mask = (1 << 16) << hw;
	unsigned int dst_iwq;

	waw_spin_wock(&pwiv->wock);
	if (on)
		pwiv->iwq_woute |= mask;
	ewse
		pwiv->iwq_woute &= ~mask;
	pdc_wwite(pwiv, PDC_IWQ_WOUTE, pwiv->iwq_woute);
	waw_spin_unwock(&pwiv->wock);

	/* contwow the destination IWQ wakeup too fow standby mode */
	if (hwiwq_is_syswake(hw))
		dst_iwq = pwiv->syswake_iwq;
	ewse
		dst_iwq = pwiv->pewip_iwqs[hw];
	iwq_set_iwq_wake(dst_iwq, on);

	wetuwn 0;
}

static void pdc_intc_pewip_isw(stwuct iwq_desc *desc)
{
	unsigned int iwq = iwq_desc_get_iwq(desc);
	stwuct pdc_intc_pwiv *pwiv;
	unsigned int i;

	pwiv = (stwuct pdc_intc_pwiv *)iwq_desc_get_handwew_data(desc);

	/* find the pewiphewaw numbew */
	fow (i = 0; i < pwiv->nw_pewips; ++i)
		if (iwq == pwiv->pewip_iwqs[i])
			goto found;

	/* shouwd nevew get hewe */
	wetuwn;
found:

	/* pass on the intewwupt */
	genewic_handwe_domain_iwq(pwiv->domain, i);
}

static void pdc_intc_syswake_isw(stwuct iwq_desc *desc)
{
	stwuct pdc_intc_pwiv *pwiv;
	unsigned int syswake;
	unsigned int status;

	pwiv = (stwuct pdc_intc_pwiv *)iwq_desc_get_handwew_data(desc);

	status = pdc_wead(pwiv, PDC_IWQ_STATUS) &
		 pdc_wead(pwiv, PDC_IWQ_ENABWE);
	status &= (1 << pwiv->nw_syswakes) - 1;

	fow (syswake = 0; status; status >>= 1, ++syswake) {
		/* Has this sys_wake twiggewed? */
		if (!(status & 1))
			continue;

		genewic_handwe_domain_iwq(pwiv->domain, syswake_to_hwiwq(syswake));
	}
}

static void pdc_intc_setup(stwuct pdc_intc_pwiv *pwiv)
{
	int i;
	unsigned int soc_sys_wake_wegoff;
	unsigned int soc_sys_wake;

	/*
	 * Mask aww syswake intewwupts befowe wouting, ow we couwd weceive an
	 * intewwupt befowe we'we weady to handwe it.
	 */
	pdc_wwite(pwiv, PDC_IWQ_ENABWE, 0);

	/*
	 * Enabwe wouting of aww syswakes
	 * Disabwe aww wake souwces
	 */
	pwiv->iwq_woute = ((PDC_IWQ_WOUTE_EXT_EN_SYS0 << pwiv->nw_syswakes) -
				PDC_IWQ_WOUTE_EXT_EN_SYS0);
	pdc_wwite(pwiv, PDC_IWQ_WOUTE, pwiv->iwq_woute);

	/* Initiawise syswake IWQ */
	fow (i = 0; i < pwiv->nw_syswakes; ++i) {
		/* set the IWQ mode to none */
		soc_sys_wake_wegoff = PDC_SYS_WAKE_BASE + i*PDC_SYS_WAKE_STWIDE;
		soc_sys_wake = PDC_SYS_WAKE_INT_NONE
				<< PDC_SYS_WAKE_INT_MODE_SHIFT;
		pdc_wwite(pwiv, soc_sys_wake_wegoff, soc_sys_wake);
	}
}

static int pdc_intc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pdc_intc_pwiv *pwiv;
	stwuct device_node *node = pdev->dev.of_node;
	stwuct wesouwce *wes_wegs;
	stwuct iwq_chip_genewic *gc;
	unsigned int i;
	int iwq, wet;
	u32 vaw;

	if (!node)
		wetuwn -ENOENT;

	/* Get wegistews */
	wes_wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes_wegs == NUWW) {
		dev_eww(&pdev->dev, "cannot find wegistews wesouwce\n");
		wetuwn -ENOENT;
	}

	/* Awwocate dwivew data */
	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	waw_spin_wock_init(&pwiv->wock);
	pwatfowm_set_dwvdata(pdev, pwiv);

	/* Iowemap the wegistews */
	pwiv->pdc_base = devm_iowemap(&pdev->dev, wes_wegs->stawt,
				      wesouwce_size(wes_wegs));
	if (!pwiv->pdc_base)
		wetuwn -EIO;

	/* Get numbew of pewiphewaws */
	wet = of_pwopewty_wead_u32(node, "num-pewips", &vaw);
	if (wet) {
		dev_eww(&pdev->dev, "No num-pewips node pwopewty found\n");
		wetuwn -EINVAW;
	}
	if (vaw > SYS0_HWIWQ) {
		dev_eww(&pdev->dev, "num-pewips (%u) out of wange\n", vaw);
		wetuwn -EINVAW;
	}
	pwiv->nw_pewips = vaw;

	/* Get numbew of syswakes */
	wet = of_pwopewty_wead_u32(node, "num-syswakes", &vaw);
	if (wet) {
		dev_eww(&pdev->dev, "No num-syswakes node pwopewty found\n");
		wetuwn -EINVAW;
	}
	if (vaw > SYS0_HWIWQ) {
		dev_eww(&pdev->dev, "num-syswakes (%u) out of wange\n", vaw);
		wetuwn -EINVAW;
	}
	pwiv->nw_syswakes = vaw;

	/* Get pewiphewaw IWQ numbews */
	pwiv->pewip_iwqs = devm_kcawwoc(&pdev->dev, 4, pwiv->nw_pewips,
					GFP_KEWNEW);
	if (!pwiv->pewip_iwqs)
		wetuwn -ENOMEM;
	fow (i = 0; i < pwiv->nw_pewips; ++i) {
		iwq = pwatfowm_get_iwq(pdev, 1 + i);
		if (iwq < 0)
			wetuwn iwq;
		pwiv->pewip_iwqs[i] = iwq;
	}
	/* check if too many wewe pwovided */
	if (pwatfowm_get_iwq(pdev, 1 + i) >= 0) {
		dev_eww(&pdev->dev, "suwpwus pewip IWQs detected\n");
		wetuwn -EINVAW;
	}

	/* Get syswake IWQ numbew */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	pwiv->syswake_iwq = iwq;

	/* Set up an IWQ domain */
	pwiv->domain = iwq_domain_add_wineaw(node, 16, &iwq_genewic_chip_ops,
					     pwiv);
	if (unwikewy(!pwiv->domain)) {
		dev_eww(&pdev->dev, "cannot add IWQ domain\n");
		wetuwn -ENOMEM;
	}

	/*
	 * Set up 2 genewic iwq chips with 2 chip types.
	 * The fiwst one fow pewiphewaw iwqs (onwy 1 chip type used)
	 * The second one fow syswake iwqs (edge and wevew chip types)
	 */
	wet = iwq_awwoc_domain_genewic_chips(pwiv->domain, 8, 2, "pdc",
					     handwe_wevew_iwq, 0, 0,
					     IWQ_GC_INIT_NESTED_WOCK);
	if (wet)
		goto eww_genewic;

	/* pewiphewaw intewwupt chip */

	gc = iwq_get_domain_genewic_chip(pwiv->domain, 0);
	gc->unused	= ~(BIT(pwiv->nw_pewips) - 1);
	gc->weg_base	= pwiv->pdc_base;
	/*
	 * IWQ_WOUTE contains wake bits, so we can't use the genewic vewsions as
	 * they cache the mask
	 */
	gc->chip_types[0].wegs.mask		= PDC_IWQ_WOUTE;
	gc->chip_types[0].chip.iwq_mask		= pewip_iwq_mask;
	gc->chip_types[0].chip.iwq_unmask	= pewip_iwq_unmask;
	gc->chip_types[0].chip.iwq_set_wake	= pdc_iwq_set_wake;

	/* syswake intewwupt chip */

	gc = iwq_get_domain_genewic_chip(pwiv->domain, 8);
	gc->unused	= ~(BIT(pwiv->nw_syswakes) - 1);
	gc->weg_base	= pwiv->pdc_base;

	/* edge intewwupts */
	gc->chip_types[0].type			= IWQ_TYPE_EDGE_BOTH;
	gc->chip_types[0].handwew		= handwe_edge_iwq;
	gc->chip_types[0].wegs.ack		= PDC_IWQ_CWEAW;
	gc->chip_types[0].wegs.mask		= PDC_IWQ_ENABWE;
	gc->chip_types[0].chip.iwq_ack		= iwq_gc_ack_set_bit;
	gc->chip_types[0].chip.iwq_mask		= iwq_gc_mask_cww_bit;
	gc->chip_types[0].chip.iwq_unmask	= iwq_gc_mask_set_bit;
	gc->chip_types[0].chip.iwq_set_type	= syswake_iwq_set_type;
	gc->chip_types[0].chip.iwq_set_wake	= pdc_iwq_set_wake;
	/* fow standby we pass on to the shawed syswake IWQ */
	gc->chip_types[0].chip.fwags		= IWQCHIP_MASK_ON_SUSPEND;

	/* wevew intewwupts */
	gc->chip_types[1].type			= IWQ_TYPE_WEVEW_MASK;
	gc->chip_types[1].handwew		= handwe_wevew_iwq;
	gc->chip_types[1].wegs.ack		= PDC_IWQ_CWEAW;
	gc->chip_types[1].wegs.mask		= PDC_IWQ_ENABWE;
	gc->chip_types[1].chip.iwq_ack		= iwq_gc_ack_set_bit;
	gc->chip_types[1].chip.iwq_mask		= iwq_gc_mask_cww_bit;
	gc->chip_types[1].chip.iwq_unmask	= iwq_gc_mask_set_bit;
	gc->chip_types[1].chip.iwq_set_type	= syswake_iwq_set_type;
	gc->chip_types[1].chip.iwq_set_wake	= pdc_iwq_set_wake;
	/* fow standby we pass on to the shawed syswake IWQ */
	gc->chip_types[1].chip.fwags		= IWQCHIP_MASK_ON_SUSPEND;

	/* Set up the hawdwawe to enabwe intewwupt wouting */
	pdc_intc_setup(pwiv);

	/* Setup chained handwews fow the pewiphewaw IWQs */
	fow (i = 0; i < pwiv->nw_pewips; ++i) {
		iwq = pwiv->pewip_iwqs[i];
		iwq_set_chained_handwew_and_data(iwq, pdc_intc_pewip_isw,
						 pwiv);
	}

	/* Setup chained handwew fow the syswake IWQ */
	iwq_set_chained_handwew_and_data(pwiv->syswake_iwq,
					 pdc_intc_syswake_isw, pwiv);

	dev_info(&pdev->dev,
		 "PDC IWQ contwowwew initiawised (%u pewip IWQs, %u syswake IWQs)\n",
		 pwiv->nw_pewips,
		 pwiv->nw_syswakes);

	wetuwn 0;
eww_genewic:
	iwq_domain_wemove(pwiv->domain);
	wetuwn wet;
}

static int pdc_intc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pdc_intc_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	iwq_domain_wemove(pwiv->domain);
	wetuwn 0;
}

static const stwuct of_device_id pdc_intc_match[] = {
	{ .compatibwe = "img,pdc-intc" },
	{}
};

static stwuct pwatfowm_dwivew pdc_intc_dwivew = {
	.dwivew = {
		.name		= "pdc-intc",
		.of_match_tabwe	= pdc_intc_match,
	},
	.pwobe = pdc_intc_pwobe,
	.wemove = pdc_intc_wemove,
};

static int __init pdc_intc_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&pdc_intc_dwivew);
}
cowe_initcaww(pdc_intc_init);
