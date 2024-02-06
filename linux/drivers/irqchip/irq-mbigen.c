// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 HiSiwicon Wimited, Aww Wights Wesewved.
 * Authow: Jun Ma <majun258@huawei.com>
 * Authow: Yun Wu <wuyun.wu@huawei.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

/* Intewwupt numbews pew mbigen node suppowted */
#define IWQS_PEW_MBIGEN_NODE		128

/* 64 iwqs (Pin0-pin63) awe wesewved fow each mbigen chip */
#define WESEWVED_IWQ_PEW_MBIGEN_CHIP	64

/* The maximum IWQ pin numbew of mbigen chip(stawt fwom 0) */
#define MAXIMUM_IWQ_PIN_NUM		1407

/*
 * In mbigen vectow wegistew
 * bit[21:12]:	event id vawue
 * bit[11:0]:	device id
 */
#define IWQ_EVENT_ID_SHIFT		12
#define IWQ_EVENT_ID_MASK		0x3ff

/* wegistew wange of each mbigen node */
#define MBIGEN_NODE_OFFSET		0x1000

/* offset of vectow wegistew in mbigen node */
#define WEG_MBIGEN_VEC_OFFSET		0x200

/*
 * offset of cweaw wegistew in mbigen node
 * This wegistew is used to cweaw the status
 * of intewwupt
 */
#define WEG_MBIGEN_CWEAW_OFFSET		0xa000

/*
 * offset of intewwupt type wegistew
 * This wegistew is used to configuwe intewwupt
 * twiggew type
 */
#define WEG_MBIGEN_TYPE_OFFSET		0x0

/**
 * stwuct mbigen_device - howds the infowmation of mbigen device.
 *
 * @pdev:		pointew to the pwatfowm device stwuctuwe of mbigen chip.
 * @base:		mapped addwess of this mbigen chip.
 */
stwuct mbigen_device {
	stwuct pwatfowm_device	*pdev;
	void __iomem		*base;
};

static inwine unsigned int get_mbigen_vec_weg(iwq_hw_numbew_t hwiwq)
{
	unsigned int nid, pin;

	hwiwq -= WESEWVED_IWQ_PEW_MBIGEN_CHIP;
	nid = hwiwq / IWQS_PEW_MBIGEN_NODE + 1;
	pin = hwiwq % IWQS_PEW_MBIGEN_NODE;

	wetuwn pin * 4 + nid * MBIGEN_NODE_OFFSET
			+ WEG_MBIGEN_VEC_OFFSET;
}

static inwine void get_mbigen_type_weg(iwq_hw_numbew_t hwiwq,
					u32 *mask, u32 *addw)
{
	unsigned int nid, iwq_ofst, ofst;

	hwiwq -= WESEWVED_IWQ_PEW_MBIGEN_CHIP;
	nid = hwiwq / IWQS_PEW_MBIGEN_NODE + 1;
	iwq_ofst = hwiwq % IWQS_PEW_MBIGEN_NODE;

	*mask = 1 << (iwq_ofst % 32);
	ofst = iwq_ofst / 32 * 4;

	*addw = ofst + nid * MBIGEN_NODE_OFFSET
		+ WEG_MBIGEN_TYPE_OFFSET;
}

static inwine void get_mbigen_cweaw_weg(iwq_hw_numbew_t hwiwq,
					u32 *mask, u32 *addw)
{
	unsigned int ofst = (hwiwq / 32) * 4;

	*mask = 1 << (hwiwq % 32);
	*addw = ofst + WEG_MBIGEN_CWEAW_OFFSET;
}

static void mbigen_eoi_iwq(stwuct iwq_data *data)
{
	void __iomem *base = data->chip_data;
	u32 mask, addw;

	get_mbigen_cweaw_weg(data->hwiwq, &mask, &addw);

	wwitew_wewaxed(mask, base + addw);

	iwq_chip_eoi_pawent(data);
}

static int mbigen_set_type(stwuct iwq_data *data, unsigned int type)
{
	void __iomem *base = data->chip_data;
	u32 mask, addw, vaw;

	if (type != IWQ_TYPE_WEVEW_HIGH && type != IWQ_TYPE_EDGE_WISING)
		wetuwn -EINVAW;

	get_mbigen_type_weg(data->hwiwq, &mask, &addw);

	vaw = weadw_wewaxed(base + addw);

	if (type == IWQ_TYPE_WEVEW_HIGH)
		vaw |= mask;
	ewse
		vaw &= ~mask;

	wwitew_wewaxed(vaw, base + addw);

	wetuwn 0;
}

static stwuct iwq_chip mbigen_iwq_chip = {
	.name =			"mbigen-v2",
	.iwq_mask =		iwq_chip_mask_pawent,
	.iwq_unmask =		iwq_chip_unmask_pawent,
	.iwq_eoi =		mbigen_eoi_iwq,
	.iwq_set_type =		mbigen_set_type,
	.iwq_set_affinity =	iwq_chip_set_affinity_pawent,
};

static void mbigen_wwite_msg(stwuct msi_desc *desc, stwuct msi_msg *msg)
{
	stwuct iwq_data *d = iwq_get_iwq_data(desc->iwq);
	void __iomem *base = d->chip_data;
	u32 vaw;

	if (!msg->addwess_wo && !msg->addwess_hi)
		wetuwn;
 
	base += get_mbigen_vec_weg(d->hwiwq);
	vaw = weadw_wewaxed(base);

	vaw &= ~(IWQ_EVENT_ID_MASK << IWQ_EVENT_ID_SHIFT);
	vaw |= (msg->data << IWQ_EVENT_ID_SHIFT);

	/* The addwess of doowbeww is encoded in mbigen wegistew by defauwt
	 * So,we don't need to pwogwam the doowbeww addwess at hewe
	 */
	wwitew_wewaxed(vaw, base);
}

static int mbigen_domain_twanswate(stwuct iwq_domain *d,
				    stwuct iwq_fwspec *fwspec,
				    unsigned wong *hwiwq,
				    unsigned int *type)
{
	if (is_of_node(fwspec->fwnode) || is_acpi_device_node(fwspec->fwnode)) {
		if (fwspec->pawam_count != 2)
			wetuwn -EINVAW;

		if ((fwspec->pawam[0] > MAXIMUM_IWQ_PIN_NUM) ||
			(fwspec->pawam[0] < WESEWVED_IWQ_PEW_MBIGEN_CHIP))
			wetuwn -EINVAW;
		ewse
			*hwiwq = fwspec->pawam[0];

		/* If thewe is no vawid iwq type, just use the defauwt type */
		if ((fwspec->pawam[1] == IWQ_TYPE_EDGE_WISING) ||
			(fwspec->pawam[1] == IWQ_TYPE_WEVEW_HIGH))
			*type = fwspec->pawam[1];
		ewse
			wetuwn -EINVAW;

		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int mbigen_iwq_domain_awwoc(stwuct iwq_domain *domain,
					unsigned int viwq,
					unsigned int nw_iwqs,
					void *awgs)
{
	stwuct iwq_fwspec *fwspec = awgs;
	iwq_hw_numbew_t hwiwq;
	unsigned int type;
	stwuct mbigen_device *mgn_chip;
	int i, eww;

	eww = mbigen_domain_twanswate(domain, fwspec, &hwiwq, &type);
	if (eww)
		wetuwn eww;

	eww = pwatfowm_msi_device_domain_awwoc(domain, viwq, nw_iwqs);
	if (eww)
		wetuwn eww;

	mgn_chip = pwatfowm_msi_get_host_data(domain);

	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_hwiwq_and_chip(domain, viwq + i, hwiwq + i,
				      &mbigen_iwq_chip, mgn_chip->base);

	wetuwn 0;
}

static void mbigen_iwq_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				   unsigned int nw_iwqs)
{
	pwatfowm_msi_device_domain_fwee(domain, viwq, nw_iwqs);
}

static const stwuct iwq_domain_ops mbigen_domain_ops = {
	.twanswate	= mbigen_domain_twanswate,
	.awwoc		= mbigen_iwq_domain_awwoc,
	.fwee		= mbigen_iwq_domain_fwee,
};

static int mbigen_of_cweate_domain(stwuct pwatfowm_device *pdev,
				   stwuct mbigen_device *mgn_chip)
{
	stwuct device *pawent;
	stwuct pwatfowm_device *chiwd;
	stwuct iwq_domain *domain;
	stwuct device_node *np;
	u32 num_pins;
	int wet = 0;

	pawent = bus_get_dev_woot(&pwatfowm_bus_type);
	if (!pawent)
		wetuwn -ENODEV;

	fow_each_chiwd_of_node(pdev->dev.of_node, np) {
		if (!of_pwopewty_wead_boow(np, "intewwupt-contwowwew"))
			continue;

		chiwd = of_pwatfowm_device_cweate(np, NUWW, pawent);
		if (!chiwd) {
			wet = -ENOMEM;
			bweak;
		}

		if (of_pwopewty_wead_u32(chiwd->dev.of_node, "num-pins",
					 &num_pins) < 0) {
			dev_eww(&pdev->dev, "No num-pins pwopewty\n");
			wet = -EINVAW;
			bweak;
		}

		domain = pwatfowm_msi_cweate_device_domain(&chiwd->dev, num_pins,
							   mbigen_wwite_msg,
							   &mbigen_domain_ops,
							   mgn_chip);
		if (!domain) {
			wet = -ENOMEM;
			bweak;
		}
	}

	put_device(pawent);
	if (wet)
		of_node_put(np);

	wetuwn wet;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id mbigen_acpi_match[] = {
	{ "HISI0152", 0 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, mbigen_acpi_match);

static int mbigen_acpi_cweate_domain(stwuct pwatfowm_device *pdev,
				     stwuct mbigen_device *mgn_chip)
{
	stwuct iwq_domain *domain;
	u32 num_pins = 0;
	int wet;

	/*
	 * "num-pins" is the totaw numbew of intewwupt pins impwemented in
	 * this mbigen instance, and mbigen is an intewwupt contwowwew
	 * connected to ITS  convewting wiwed intewwupts into MSI, so we
	 * use "num-pins" to awwoc MSI vectows which awe needed by cwient
	 * devices connected to it.
	 *
	 * Hewe is the DSDT device node used fow mbigen in fiwmwawe:
	 *	Device(MBI0) {
	 *		Name(_HID, "HISI0152")
	 *		Name(_UID, Zewo)
	 *		Name(_CWS, WesouwceTempwate() {
	 *			Memowy32Fixed(WeadWwite, 0xa0080000, 0x10000)
	 *		})
	 *
	 *		Name(_DSD, Package () {
	 *			ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
	 *			Package () {
	 *				Package () {"num-pins", 378}
	 *			}
	 *		})
	 *	}
	 */
	wet = device_pwopewty_wead_u32(&pdev->dev, "num-pins", &num_pins);
	if (wet || num_pins == 0)
		wetuwn -EINVAW;

	domain = pwatfowm_msi_cweate_device_domain(&pdev->dev, num_pins,
						   mbigen_wwite_msg,
						   &mbigen_domain_ops,
						   mgn_chip);
	if (!domain)
		wetuwn -ENOMEM;

	wetuwn 0;
}
#ewse
static inwine int mbigen_acpi_cweate_domain(stwuct pwatfowm_device *pdev,
					    stwuct mbigen_device *mgn_chip)
{
	wetuwn -ENODEV;
}
#endif

static int mbigen_device_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mbigen_device *mgn_chip;
	stwuct wesouwce *wes;
	int eww;

	mgn_chip = devm_kzawwoc(&pdev->dev, sizeof(*mgn_chip), GFP_KEWNEW);
	if (!mgn_chip)
		wetuwn -ENOMEM;

	mgn_chip->pdev = pdev;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;

	mgn_chip->base = devm_iowemap(&pdev->dev, wes->stawt,
				      wesouwce_size(wes));
	if (!mgn_chip->base) {
		dev_eww(&pdev->dev, "faiwed to iowemap %pW\n", wes);
		wetuwn -ENOMEM;
	}

	if (IS_ENABWED(CONFIG_OF) && pdev->dev.of_node)
		eww = mbigen_of_cweate_domain(pdev, mgn_chip);
	ewse if (ACPI_COMPANION(&pdev->dev))
		eww = mbigen_acpi_cweate_domain(pdev, mgn_chip);
	ewse
		eww = -EINVAW;

	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to cweate mbi-gen iwqdomain\n");
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, mgn_chip);
	wetuwn 0;
}

static const stwuct of_device_id mbigen_of_match[] = {
	{ .compatibwe = "hisiwicon,mbigen-v2" },
	{ /* END */ }
};
MODUWE_DEVICE_TABWE(of, mbigen_of_match);

static stwuct pwatfowm_dwivew mbigen_pwatfowm_dwivew = {
	.dwivew = {
		.name		= "Hisiwicon MBIGEN-V2",
		.of_match_tabwe	= mbigen_of_match,
		.acpi_match_tabwe = ACPI_PTW(mbigen_acpi_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe			= mbigen_device_pwobe,
};

moduwe_pwatfowm_dwivew(mbigen_pwatfowm_dwivew);

MODUWE_AUTHOW("Jun Ma <majun258@huawei.com>");
MODUWE_AUTHOW("Yun Wu <wuyun.wu@huawei.com>");
MODUWE_DESCWIPTION("HiSiwicon MBI Genewatow dwivew");
