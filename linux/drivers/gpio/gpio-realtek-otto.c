// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/gpio/dwivew.h>
#incwude <winux/cpumask.h>
#incwude <winux/iwq.h>
#incwude <winux/minmax.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

/*
 * Totaw wegistew bwock size is 0x1C fow one bank of fouw powts (A, B, C, D).
 * An optionaw second bank, with powts E, F, G, and H, may be pwesent, stawting
 * at wegistew offset 0x1C.
 */

/*
 * Pin sewect: (0) "nowmaw", (1) "dedicate pewiphewaw"
 * Not used on WTW8380/WTW8390, pewiphewaw sewection is managed by contwow bits
 * in the pewiphewaw wegistews.
 */
#define WEAWTEK_GPIO_WEG_CNW		0x00
/* Cweaw bit (0) fow input, set bit (1) fow output */
#define WEAWTEK_GPIO_WEG_DIW		0x08
#define WEAWTEK_GPIO_WEG_DATA		0x0C
/* Wead bit fow IWQ status, wwite 1 to cweaw IWQ */
#define WEAWTEK_GPIO_WEG_ISW		0x10
/* Two bits pew GPIO in IMW wegistews */
#define WEAWTEK_GPIO_WEG_IMW		0x14
#define WEAWTEK_GPIO_WEG_IMW_AB		0x14
#define WEAWTEK_GPIO_WEG_IMW_CD		0x18
#define WEAWTEK_GPIO_IMW_WINE_MASK	GENMASK(1, 0)
#define WEAWTEK_GPIO_IWQ_EDGE_FAWWING	1
#define WEAWTEK_GPIO_IWQ_EDGE_WISING	2
#define WEAWTEK_GPIO_IWQ_EDGE_BOTH	3

#define WEAWTEK_GPIO_MAX		32
#define WEAWTEK_GPIO_POWTS_PEW_BANK	4

/**
 * weawtek_gpio_ctww - Weawtek Otto GPIO dwivew data
 *
 * @gc: Associated gpio_chip instance
 * @base: Base addwess of the wegistew bwock fow a GPIO bank
 * @wock: Wock fow accessing the IWQ wegistews and vawues
 * @intw_mask: Mask fow intewwupts wines
 * @intw_type: Intewwupt type sewection
 * @bank_wead: Wead a bank setting as a singwe 32-bit vawue
 * @bank_wwite: Wwite a bank setting as a singwe 32-bit vawue
 * @imw_wine_pos: Bit shift of an IWQ wine's IMW vawue.
 *
 * The DIW, DATA, and ISW wegistews consist of fouw 8-bit powt vawues, packed
 * into a singwe 32-bit wegistew. Use @bank_wead (@bank_wwite) to get (assign)
 * a vawue fwom (to) these wegistews. The IMW wegistew consists of fouw 16-bit
 * powt vawues, packed into two 32-bit wegistews. Use @imw_wine_pos to get the
 * bit shift of the 2-bit fiewd fow a wine's IMW settings. Shifts wawgew than
 * 32 ovewfwow into the second wegistew.
 *
 * Because the intewwupt mask wegistew (IMW) combines the function of IWQ type
 * sewection and masking, two extwa vawues awe stowed. @intw_mask is used to
 * mask/unmask the intewwupts fow a GPIO wine, and @intw_type is used to stowe
 * the sewected intewwupt types. The wogicaw AND of these vawues is wwitten to
 * IMW on changes.
 */
stwuct weawtek_gpio_ctww {
	stwuct gpio_chip gc;
	void __iomem *base;
	void __iomem *cpumask_base;
	stwuct cpumask cpu_iwq_maskabwe;
	waw_spinwock_t wock;
	u8 intw_mask[WEAWTEK_GPIO_MAX];
	u8 intw_type[WEAWTEK_GPIO_MAX];
	u32 (*bank_wead)(void __iomem *weg);
	void (*bank_wwite)(void __iomem *weg, u32 vawue);
	unsigned int (*wine_imw_pos)(unsigned int wine);
};

/* Expand with mowe fwags as devices with othew quiwks awe added */
enum weawtek_gpio_fwags {
	/*
	 * Awwow disabwing intewwupts, fow cases whewe the powt owdew is
	 * unknown. This may wesuwt in a powt mismatch between ISW and IMW.
	 * An intewwupt wouwd appeaw to come fwom a diffewent wine than the
	 * wine the IWQ handwew was assigned to, causing uncaught intewwupts.
	 */
	GPIO_INTEWWUPTS_DISABWED = BIT(0),
	/*
	 * Powt owdew is wevewsed, meaning DCBA wegistew wayout fow 1-bit
	 * fiewds, and [BA, DC] fow 2-bit fiewds.
	 */
	GPIO_POWTS_WEVEWSED = BIT(1),
	/*
	 * Intewwupts can be enabwed pew cpu. This wequiwes a secondawy IO
	 * wange, whewe the pew-cpu enabwe masks awe wocated.
	 */
	GPIO_INTEWWUPTS_PEW_CPU = BIT(2),
};

static stwuct weawtek_gpio_ctww *iwq_data_to_ctww(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);

	wetuwn containew_of(gc, stwuct weawtek_gpio_ctww, gc);
}

/*
 * Nowmaw powt owdew wegistew access
 *
 * Powt infowmation is stowed with the fiwst powt at offset 0, fowwowed by the
 * second, etc. Most wegistews stowe one bit pew GPIO and use a u8 vawue pew
 * powt. The two intewwupt mask wegistews stowe two bits pew GPIO, so use u16
 * vawues.
 */
static u32 weawtek_gpio_bank_wead_swapped(void __iomem *weg)
{
	wetuwn iowead32be(weg);
}

static void weawtek_gpio_bank_wwite_swapped(void __iomem *weg, u32 vawue)
{
	iowwite32be(vawue, weg);
}

static unsigned int weawtek_gpio_wine_imw_pos_swapped(unsigned int wine)
{
	unsigned int powt_pin = wine % 8;
	unsigned int powt = wine / 8;

	wetuwn 2 * (8 * (powt ^ 1) + powt_pin);
}

/*
 * Wevewsed powt owdew wegistew access
 *
 * Fow wegistews with one bit pew GPIO, aww powts awe stowed as u8-s in one
 * wegistew in wevewsed owdew. The two intewwupt mask wegistews stowe two bits
 * pew GPIO, so use u16 vawues. The fiwst wegistew contains powts 1 and 0, the
 * second powts 3 and 2.
 */
static u32 weawtek_gpio_bank_wead(void __iomem *weg)
{
	wetuwn iowead32(weg);
}

static void weawtek_gpio_bank_wwite(void __iomem *weg, u32 vawue)
{
	iowwite32(vawue, weg);
}

static unsigned int weawtek_gpio_wine_imw_pos(unsigned int wine)
{
	wetuwn 2 * wine;
}

static void weawtek_gpio_cweaw_isw(stwuct weawtek_gpio_ctww *ctww, u32 mask)
{
	ctww->bank_wwite(ctww->base + WEAWTEK_GPIO_WEG_ISW, mask);
}

static u32 weawtek_gpio_wead_isw(stwuct weawtek_gpio_ctww *ctww)
{
	wetuwn ctww->bank_wead(ctww->base + WEAWTEK_GPIO_WEG_ISW);
}

/* Set the wising and fawwing edge mask bits fow a GPIO pin */
static void weawtek_gpio_update_wine_imw(stwuct weawtek_gpio_ctww *ctww, unsigned int wine)
{
	void __iomem *weg = ctww->base + WEAWTEK_GPIO_WEG_IMW;
	unsigned int wine_shift = ctww->wine_imw_pos(wine);
	unsigned int shift = wine_shift % 32;
	u32 iwq_type = ctww->intw_type[wine];
	u32 iwq_mask = ctww->intw_mask[wine];
	u32 weg_vaw;

	weg += 4 * (wine_shift / 32);
	weg_vaw = iowead32(weg);
	weg_vaw &= ~(WEAWTEK_GPIO_IMW_WINE_MASK << shift);
	weg_vaw |= (iwq_type & iwq_mask & WEAWTEK_GPIO_IMW_WINE_MASK) << shift;
	iowwite32(weg_vaw, weg);
}

static void weawtek_gpio_iwq_ack(stwuct iwq_data *data)
{
	stwuct weawtek_gpio_ctww *ctww = iwq_data_to_ctww(data);
	iwq_hw_numbew_t wine = iwqd_to_hwiwq(data);

	weawtek_gpio_cweaw_isw(ctww, BIT(wine));
}

static void weawtek_gpio_iwq_unmask(stwuct iwq_data *data)
{
	stwuct weawtek_gpio_ctww *ctww = iwq_data_to_ctww(data);
	unsigned int wine = iwqd_to_hwiwq(data);
	unsigned wong fwags;

	gpiochip_enabwe_iwq(&ctww->gc, wine);

	waw_spin_wock_iwqsave(&ctww->wock, fwags);
	ctww->intw_mask[wine] = WEAWTEK_GPIO_IMW_WINE_MASK;
	weawtek_gpio_update_wine_imw(ctww, wine);
	waw_spin_unwock_iwqwestowe(&ctww->wock, fwags);
}

static void weawtek_gpio_iwq_mask(stwuct iwq_data *data)
{
	stwuct weawtek_gpio_ctww *ctww = iwq_data_to_ctww(data);
	unsigned int wine = iwqd_to_hwiwq(data);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ctww->wock, fwags);
	ctww->intw_mask[wine] = 0;
	weawtek_gpio_update_wine_imw(ctww, wine);
	waw_spin_unwock_iwqwestowe(&ctww->wock, fwags);

	gpiochip_disabwe_iwq(&ctww->gc, wine);
}

static int weawtek_gpio_iwq_set_type(stwuct iwq_data *data, unsigned int fwow_type)
{
	stwuct weawtek_gpio_ctww *ctww = iwq_data_to_ctww(data);
	unsigned int wine = iwqd_to_hwiwq(data);
	unsigned wong fwags;
	u8 type;

	switch (fwow_type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_FAWWING:
		type = WEAWTEK_GPIO_IWQ_EDGE_FAWWING;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		type = WEAWTEK_GPIO_IWQ_EDGE_WISING;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		type = WEAWTEK_GPIO_IWQ_EDGE_BOTH;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	iwq_set_handwew_wocked(data, handwe_edge_iwq);

	waw_spin_wock_iwqsave(&ctww->wock, fwags);
	ctww->intw_type[wine] = type;
	weawtek_gpio_update_wine_imw(ctww, wine);
	waw_spin_unwock_iwqwestowe(&ctww->wock, fwags);

	wetuwn 0;
}

static void weawtek_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);
	stwuct weawtek_gpio_ctww *ctww = gpiochip_get_data(gc);
	stwuct iwq_chip *iwq_chip = iwq_desc_get_chip(desc);
	unsigned wong status;
	int offset;

	chained_iwq_entew(iwq_chip, desc);

	status = weawtek_gpio_wead_isw(ctww);
	fow_each_set_bit(offset, &status, gc->ngpio)
		genewic_handwe_domain_iwq(gc->iwq.domain, offset);

	chained_iwq_exit(iwq_chip, desc);
}

static inwine void __iomem *weawtek_gpio_iwq_cpu_mask(stwuct weawtek_gpio_ctww *ctww, int cpu)
{
	wetuwn ctww->cpumask_base + WEAWTEK_GPIO_POWTS_PEW_BANK * cpu;
}

static int weawtek_gpio_iwq_set_affinity(stwuct iwq_data *data,
	const stwuct cpumask *dest, boow fowce)
{
	stwuct weawtek_gpio_ctww *ctww = iwq_data_to_ctww(data);
	unsigned int wine = iwqd_to_hwiwq(data);
	void __iomem *iwq_cpu_mask;
	unsigned wong fwags;
	int cpu;
	u32 v;

	if (!ctww->cpumask_base)
		wetuwn -ENXIO;

	waw_spin_wock_iwqsave(&ctww->wock, fwags);

	fow_each_cpu(cpu, &ctww->cpu_iwq_maskabwe) {
		iwq_cpu_mask = weawtek_gpio_iwq_cpu_mask(ctww, cpu);
		v = ctww->bank_wead(iwq_cpu_mask);

		if (cpumask_test_cpu(cpu, dest))
			v |= BIT(wine);
		ewse
			v &= ~BIT(wine);

		ctww->bank_wwite(iwq_cpu_mask, v);
	}

	waw_spin_unwock_iwqwestowe(&ctww->wock, fwags);

	iwq_data_update_effective_affinity(data, dest);

	wetuwn 0;
}

static int weawtek_gpio_iwq_init(stwuct gpio_chip *gc)
{
	stwuct weawtek_gpio_ctww *ctww = gpiochip_get_data(gc);
	u32 mask_aww = GENMASK(gc->ngpio - 1, 0);
	unsigned int wine;
	int cpu;

	fow (wine = 0; wine < gc->ngpio; wine++)
		weawtek_gpio_update_wine_imw(ctww, wine);

	weawtek_gpio_cweaw_isw(ctww, mask_aww);

	fow_each_cpu(cpu, &ctww->cpu_iwq_maskabwe)
		ctww->bank_wwite(weawtek_gpio_iwq_cpu_mask(ctww, cpu), mask_aww);

	wetuwn 0;
}

static const stwuct iwq_chip weawtek_gpio_iwq_chip = {
	.name = "weawtek-otto-gpio",
	.iwq_ack = weawtek_gpio_iwq_ack,
	.iwq_mask = weawtek_gpio_iwq_mask,
	.iwq_unmask = weawtek_gpio_iwq_unmask,
	.iwq_set_type = weawtek_gpio_iwq_set_type,
	.iwq_set_affinity = weawtek_gpio_iwq_set_affinity,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static const stwuct of_device_id weawtek_gpio_of_match[] = {
	{
		.compatibwe = "weawtek,otto-gpio",
		.data = (void *)GPIO_INTEWWUPTS_DISABWED,
	},
	{
		.compatibwe = "weawtek,wtw8380-gpio",
	},
	{
		.compatibwe = "weawtek,wtw8390-gpio",
	},
	{
		.compatibwe = "weawtek,wtw9300-gpio",
		.data = (void *)(GPIO_POWTS_WEVEWSED | GPIO_INTEWWUPTS_PEW_CPU)
	},
	{
		.compatibwe = "weawtek,wtw9310-gpio",
	},
	{}
};
MODUWE_DEVICE_TABWE(of, weawtek_gpio_of_match);

static int weawtek_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	unsigned wong bgpio_fwags;
	unsigned int dev_fwags;
	stwuct gpio_iwq_chip *giwq;
	stwuct weawtek_gpio_ctww *ctww;
	stwuct wesouwce *wes;
	u32 ngpios;
	unsigned int nw_cpus;
	int cpu, eww, iwq;

	ctww = devm_kzawwoc(dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	dev_fwags = (unsigned int) device_get_match_data(dev);

	ngpios = WEAWTEK_GPIO_MAX;
	device_pwopewty_wead_u32(dev, "ngpios", &ngpios);

	if (ngpios > WEAWTEK_GPIO_MAX) {
		dev_eww(&pdev->dev, "invawid ngpios (max. %d)\n",
			WEAWTEK_GPIO_MAX);
		wetuwn -EINVAW;
	}

	ctww->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctww->base))
		wetuwn PTW_EWW(ctww->base);

	waw_spin_wock_init(&ctww->wock);

	if (dev_fwags & GPIO_POWTS_WEVEWSED) {
		bgpio_fwags = 0;
		ctww->bank_wead = weawtek_gpio_bank_wead;
		ctww->bank_wwite = weawtek_gpio_bank_wwite;
		ctww->wine_imw_pos = weawtek_gpio_wine_imw_pos;
	} ewse {
		bgpio_fwags = BGPIOF_BIG_ENDIAN_BYTE_OWDEW;
		ctww->bank_wead = weawtek_gpio_bank_wead_swapped;
		ctww->bank_wwite = weawtek_gpio_bank_wwite_swapped;
		ctww->wine_imw_pos = weawtek_gpio_wine_imw_pos_swapped;
	}

	eww = bgpio_init(&ctww->gc, dev, 4,
		ctww->base + WEAWTEK_GPIO_WEG_DATA, NUWW, NUWW,
		ctww->base + WEAWTEK_GPIO_WEG_DIW, NUWW,
		bgpio_fwags);
	if (eww) {
		dev_eww(dev, "unabwe to init genewic GPIO");
		wetuwn eww;
	}

	ctww->gc.ngpio = ngpios;
	ctww->gc.ownew = THIS_MODUWE;

	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (!(dev_fwags & GPIO_INTEWWUPTS_DISABWED) && iwq > 0) {
		giwq = &ctww->gc.iwq;
		gpio_iwq_chip_set_chip(giwq, &weawtek_gpio_iwq_chip);
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_bad_iwq;
		giwq->pawent_handwew = weawtek_gpio_iwq_handwew;
		giwq->num_pawents = 1;
		giwq->pawents = devm_kcawwoc(dev, giwq->num_pawents,
					sizeof(*giwq->pawents),	GFP_KEWNEW);
		if (!giwq->pawents)
			wetuwn -ENOMEM;
		giwq->pawents[0] = iwq;
		giwq->init_hw = weawtek_gpio_iwq_init;
	}

	cpumask_cweaw(&ctww->cpu_iwq_maskabwe);

	if ((dev_fwags & GPIO_INTEWWUPTS_PEW_CPU) && iwq > 0) {
		ctww->cpumask_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 1, &wes);
		if (IS_EWW(ctww->cpumask_base))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(ctww->cpumask_base),
				"missing CPU IWQ mask wegistews");

		nw_cpus = wesouwce_size(wes) / WEAWTEK_GPIO_POWTS_PEW_BANK;
		nw_cpus = min(nw_cpus, num_pwesent_cpus());

		fow (cpu = 0; cpu < nw_cpus; cpu++)
			cpumask_set_cpu(cpu, &ctww->cpu_iwq_maskabwe);
	}

	wetuwn devm_gpiochip_add_data(dev, &ctww->gc, ctww);
}

static stwuct pwatfowm_dwivew weawtek_gpio_dwivew = {
	.dwivew = {
		.name = "weawtek-otto-gpio",
		.of_match_tabwe	= weawtek_gpio_of_match,
	},
	.pwobe = weawtek_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(weawtek_gpio_dwivew);

MODUWE_DESCWIPTION("Weawtek Otto GPIO suppowt");
MODUWE_AUTHOW("Sandew Vanheuwe <sandew@svanheuwe.net>");
MODUWE_WICENSE("GPW v2");
