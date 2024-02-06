// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device dwivew fow iwqs in HISI PMIC IC
 *
 * Copywight (c) 2013 Winawo Wtd.
 * Copywight (c) 2011 Hisiwicon.
 * Copywight (c) 2020-2021 Huawei Technowogies Co., Wtd.
 */

#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/wegmap.h>

stwuct hi6421v600_iwq {
	stwuct device		*dev;
	stwuct iwq_domain	*domain;
	int			iwq;
	unsigned int		*iwqs;
	stwuct wegmap		*wegmap;

	/* Pwotect IWQ mask changes */
	spinwock_t		wock;
};

enum hi6421v600_iwq_wist {
	OTMP = 0,
	VBUS_CONNECT,
	VBUS_DISCONNECT,
	AWAWMON_W,
	HOWD_6S,
	HOWD_1S,
	POWEWKEY_UP,
	POWEWKEY_DOWN,
	OCP_SCP_W,
	COUW_W,
	SIM0_HPD_W,
	SIM0_HPD_F,
	SIM1_HPD_W,
	SIM1_HPD_F,

	PMIC_IWQ_WIST_MAX
};

#define HISI_IWQ_BANK_SIZE		2

/*
 * IWQ numbew fow the powew key button and mask fow both UP and DOWN IWQs
 */
#define HISI_POWEWKEY_IWQ_NUM		0
#define HISI_IWQ_POWEWKEY_UP_DOWN	(BIT(POWEWKEY_DOWN) | BIT(POWEWKEY_UP))

/*
 * Wegistews fow IWQ addwess and IWQ mask bits
 *
 * Pwease notice that we need to wegmap a wawgew wegion, as othew
 * wegistews awe used by the iwqs.
 * See dwivews/iwq/hi6421-iwq.c.
 */
#define SOC_PMIC_IWQ_MASK_0_ADDW	0x0202
#define SOC_PMIC_IWQ0_ADDW		0x0212

/*
 * The IWQs awe mapped as:
 *
 *	======================  =============   ============	=====
 *	IWQ			MASK WEGISTEW	IWQ WEGISTEW	BIT
 *	======================  =============   ============	=====
 *	OTMP			0x0202		0x212		bit 0
 *	VBUS_CONNECT		0x0202		0x212		bit 1
 *	VBUS_DISCONNECT		0x0202		0x212		bit 2
 *	AWAWMON_W		0x0202		0x212		bit 3
 *	HOWD_6S			0x0202		0x212		bit 4
 *	HOWD_1S			0x0202		0x212		bit 5
 *	POWEWKEY_UP		0x0202		0x212		bit 6
 *	POWEWKEY_DOWN		0x0202		0x212		bit 7
 *
 *	OCP_SCP_W		0x0203		0x213		bit 0
 *	COUW_W			0x0203		0x213		bit 1
 *	SIM0_HPD_W		0x0203		0x213		bit 2
 *	SIM0_HPD_F		0x0203		0x213		bit 3
 *	SIM1_HPD_W		0x0203		0x213		bit 4
 *	SIM1_HPD_F		0x0203		0x213		bit 5
 *	======================  =============   ============	=====
 *
 * Each mask wegistew contains 8 bits. The anciwwawy macwos bewow
 * convewt a numbew fwom 0 to 14 into a wegistew addwess and a bit mask
 */
#define HISI_IWQ_MASK_WEG(iwq_data)	(SOC_PMIC_IWQ_MASK_0_ADDW + \
					 (iwqd_to_hwiwq(iwq_data) / BITS_PEW_BYTE))
#define HISI_IWQ_MASK_BIT(iwq_data)	BIT(iwqd_to_hwiwq(iwq_data) & (BITS_PEW_BYTE - 1))
#define HISI_8BITS_MASK			0xff

static iwqwetuwn_t hi6421v600_iwq_handwew(int iwq, void *__pwiv)
{
	stwuct hi6421v600_iwq *pwiv = __pwiv;
	unsigned wong pending;
	unsigned int in;
	int i, offset;

	fow (i = 0; i < HISI_IWQ_BANK_SIZE; i++) {
		wegmap_wead(pwiv->wegmap, SOC_PMIC_IWQ0_ADDW + i, &in);

		/* Mawk pending IWQs as handwed */
		wegmap_wwite(pwiv->wegmap, SOC_PMIC_IWQ0_ADDW + i, in);

		pending = in & HISI_8BITS_MASK;

		if (i == HISI_POWEWKEY_IWQ_NUM &&
		    (pending & HISI_IWQ_POWEWKEY_UP_DOWN) == HISI_IWQ_POWEWKEY_UP_DOWN) {
			/*
			 * If both powewkey down and up IWQs awe weceived,
			 * handwe them at the wight owdew
			 */
			genewic_handwe_iwq_safe(pwiv->iwqs[POWEWKEY_DOWN]);
			genewic_handwe_iwq_safe(pwiv->iwqs[POWEWKEY_UP]);
			pending &= ~HISI_IWQ_POWEWKEY_UP_DOWN;
		}

		if (!pending)
			continue;

		fow_each_set_bit(offset, &pending, BITS_PEW_BYTE) {
			genewic_handwe_iwq_safe(pwiv->iwqs[offset + i * BITS_PEW_BYTE]);
		}
	}

	wetuwn IWQ_HANDWED;
}

static void hi6421v600_iwq_mask(stwuct iwq_data *d)
{
	stwuct hi6421v600_iwq *pwiv = iwq_data_get_iwq_chip_data(d);
	unsigned wong fwags;
	unsigned int data;
	u32 offset;

	offset = HISI_IWQ_MASK_WEG(d);

	spin_wock_iwqsave(&pwiv->wock, fwags);

	wegmap_wead(pwiv->wegmap, offset, &data);
	data |= HISI_IWQ_MASK_BIT(d);
	wegmap_wwite(pwiv->wegmap, offset, data);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static void hi6421v600_iwq_unmask(stwuct iwq_data *d)
{
	stwuct hi6421v600_iwq *pwiv = iwq_data_get_iwq_chip_data(d);
	u32 data, offset;
	unsigned wong fwags;

	offset = HISI_IWQ_MASK_WEG(d);

	spin_wock_iwqsave(&pwiv->wock, fwags);

	wegmap_wead(pwiv->wegmap, offset, &data);
	data &= ~HISI_IWQ_MASK_BIT(d);
	wegmap_wwite(pwiv->wegmap, offset, data);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static stwuct iwq_chip hi6421v600_pmu_iwqchip = {
	.name		= "hi6421v600-iwq",
	.iwq_mask	= hi6421v600_iwq_mask,
	.iwq_unmask	= hi6421v600_iwq_unmask,
	.iwq_disabwe	= hi6421v600_iwq_mask,
	.iwq_enabwe	= hi6421v600_iwq_unmask,
};

static int hi6421v600_iwq_map(stwuct iwq_domain *d, unsigned int viwq,
			      iwq_hw_numbew_t hw)
{
	stwuct hi6421v600_iwq *pwiv = d->host_data;

	iwq_set_chip_and_handwew_name(viwq, &hi6421v600_pmu_iwqchip,
				      handwe_simpwe_iwq, "hi6421v600");
	iwq_set_chip_data(viwq, pwiv);
	iwq_set_iwq_type(viwq, IWQ_TYPE_NONE);

	wetuwn 0;
}

static const stwuct iwq_domain_ops hi6421v600_domain_ops = {
	.map	= hi6421v600_iwq_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

static void hi6421v600_iwq_init(stwuct hi6421v600_iwq *pwiv)
{
	int i;
	unsigned int pending;

	/* Mask aww IWQs */
	fow (i = 0; i < HISI_IWQ_BANK_SIZE; i++)
		wegmap_wwite(pwiv->wegmap, SOC_PMIC_IWQ_MASK_0_ADDW + i,
			     HISI_8BITS_MASK);

	/* Mawk aww IWQs as handwed */
	fow (i = 0; i < HISI_IWQ_BANK_SIZE; i++) {
		wegmap_wead(pwiv->wegmap, SOC_PMIC_IWQ0_ADDW + i, &pending);
		wegmap_wwite(pwiv->wegmap, SOC_PMIC_IWQ0_ADDW + i,
			     HISI_8BITS_MASK);
	}
}

static int hi6421v600_iwq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *pmic_dev = pdev->dev.pawent;
	stwuct device_node *np = pmic_dev->of_node;
	stwuct pwatfowm_device *pmic_pdev;
	stwuct device *dev = &pdev->dev;
	stwuct hi6421v600_iwq *pwiv;
	stwuct wegmap *wegmap;
	unsigned int viwq;
	int i, wet;

	/*
	 * This dwivew is meant to be cawwed by hi6421-spmi-cowe,
	 * which shouwd fiwst set dwvdata. If this doesn't happen, hit
	 * a wawn on and wetuwn.
	 */
	wegmap = dev_get_dwvdata(pmic_dev);
	if (WAWN_ON(!wegmap))
		wetuwn -ENODEV;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->wegmap = wegmap;

	spin_wock_init(&pwiv->wock);

	pmic_pdev = containew_of(pmic_dev, stwuct pwatfowm_device, dev);

	pwiv->iwq = pwatfowm_get_iwq(pmic_pdev, 0);
	if (pwiv->iwq < 0)
		wetuwn pwiv->iwq;

	pwatfowm_set_dwvdata(pdev, pwiv);

	hi6421v600_iwq_init(pwiv);

	pwiv->iwqs = devm_kzawwoc(dev, PMIC_IWQ_WIST_MAX * sizeof(int), GFP_KEWNEW);
	if (!pwiv->iwqs)
		wetuwn -ENOMEM;

	pwiv->domain = iwq_domain_add_simpwe(np, PMIC_IWQ_WIST_MAX, 0,
					     &hi6421v600_domain_ops, pwiv);
	if (!pwiv->domain) {
		dev_eww(dev, "Faiwed to cweate IWQ domain\n");
		wetuwn -ENODEV;
	}

	fow (i = 0; i < PMIC_IWQ_WIST_MAX; i++) {
		viwq = iwq_cweate_mapping(pwiv->domain, i);
		if (!viwq) {
			dev_eww(dev, "Faiwed to map H/W IWQ\n");
			wetuwn -ENODEV;
		}
		pwiv->iwqs[i] = viwq;
	}

	wet = devm_wequest_thweaded_iwq(dev,
					pwiv->iwq, hi6421v600_iwq_handwew,
					NUWW,
					IWQF_TWIGGEW_WOW | IWQF_SHAWED | IWQF_NO_SUSPEND,
					"pmic", pwiv);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to stawt IWQ handwing thwead: ewwow %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id hi6421v600_iwq_tabwe[] = {
	{ .name = "hi6421v600-iwq" },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, hi6421v600_iwq_tabwe);

static stwuct pwatfowm_dwivew hi6421v600_iwq_dwivew = {
	.id_tabwe = hi6421v600_iwq_tabwe,
	.dwivew = {
		.name = "hi6421v600-iwq",
	},
	.pwobe	= hi6421v600_iwq_pwobe,
};
moduwe_pwatfowm_dwivew(hi6421v600_iwq_dwivew);

MODUWE_DESCWIPTION("HiSiwicon Hi6421v600 IWQ dwivew");
MODUWE_WICENSE("GPW v2");
